/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "app.h"

#include "gatt_db.h"

#include "sl_simple_led_instances.h"
#include "sl_simple_button_instances.h"

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;

static bool report_button_state = false;


/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
  ///

  sl_button_disable(SL_SIMPLE_BUTTON_INSTANCE(0));
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
  sl_status_t sc;
    if (report_button_state == true)
      {
        report_button_state = false;
        uint8_t data_tx;
        // Notify any subscribed GATT clients of the button state change
        // Write the new char value
        switch(sl_button_get_state(SL_SIMPLE_BUTTON_INSTANCE(0)))
        {
          case SL_SIMPLE_BUTTON_PRESSED:
            data_tx = 0x01;
            app_log_info("Button was pressed\n");
            break;
          case SL_SIMPLE_BUTTON_RELEASED:
            data_tx = 0x00;
            app_log_info("Button was released\n");
            break;
          default:
            // Invalid button state
            app_log_info("Invalid Button state\n");
            return;
        }
        sc = sl_bt_gatt_server_write_attribute_value(gattdb_button_char, 0, sizeof(data_tx), &data_tx);
        if (sc != SL_STATUS_OK)
          {
            app_log_error("Writing to local GATT server db failed\n");
          }
        // Send the notification
        sc = sl_bt_gatt_server_notify_all(gattdb_button_char, sizeof(data_tx), &data_tx);
        if (sc != SL_STATUS_OK)
          {
            app_log_error("Notification failed!\n");
          }
      }
}

void sl_button_on_change(const sl_button_t *handle)
{
  if (handle == SL_SIMPLE_BUTTON_INSTANCE(0))
    {
        report_button_state = true;
    }
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:

      // Log message indicating the start of the application
      app_log("BLE GATT Data Transfer Example Started!\r\n");

      // Print the Bluetooth Address (note the reversed order of the bytes)
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);

      app_log("Bluetooth Device Address: ");
      for (int i=0; i<5; i++)
        {
          app_log("%02X:", address.addr[5-i]);
        }
      app_log("%02X (%s)\r\n", address.addr[0], address_type == 0 ? "Public device address":"Static device address");

      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      app_assert_status(sc);

      // Generate data for advertising
      sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Set advertising interval to 100ms.
      sc = sl_bt_advertiser_set_timing(
        advertising_set_handle,
        160, // min. adv. interval (milliseconds * 1.6)
        160, // max. adv. interval (milliseconds * 1.6)
        0,   // adv. duration
        0);  // max. num. adv. events
      app_assert_status(sc);
      // Start advertising and enable connections.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);

      sl_button_enable(SL_SIMPLE_BUTTON_INSTANCE(0));

      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // Generate data for advertising
      sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Restart advertising after client has disconnected.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);
      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    case sl_bt_evt_gatt_server_attribute_value_id:
      if (evt->data.evt_gatt_server_attribute_value.attribute == gattdb_led_char)
        {
          uint8_t data_rx;
          size_t data_rx_len;
          app_log_info("LED char value changed from remote client\n");
          sc = sl_bt_gatt_server_read_attribute_value(gattdb_led_char, 0, sizeof(data_rx), &data_rx_len, &data_rx);
          if (sc != SL_STATUS_OK)
            {
              app_log_error("Error reading char value\n");
              break;
            }
         // Toggle LED:
         if (data_rx == 0x00){
             // Turn off LED
             sl_led_turn_off(SL_SIMPLE_LED_INSTANCE(0));
             app_log_info("Turn off LED\n");
         }
         else if (data_rx == 0x01)
         {
             // Turn on LED
             sl_led_turn_on(SL_SIMPLE_LED_INSTANCE(0));
             app_log_info("Turn on LED\n");
         }
         else
           {
             // Error
             app_log_info("Value not recognized\n");
           }
        }
      break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}
