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

#define DISPLAYONLY     sl_bt_sm_io_capability_displayonly     // 0
#define DISPLAYYESNO    sl_bt_sm_io_capability_displayyesno    // 1
#define KEYBOARDONLY    sl_bt_sm_io_capability_keyboardonly    // 2
#define NOINPUTNOOUTPUT sl_bt_sm_io_capability_noinputnooutput // 3
#define KEYBOARDDISPLAY sl_bt_sm_io_capability_keyboarddisplay // 4

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;

static bool report_button_state = false;
static uint8_t ble_bonding_handle = 0xFF;

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

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:

      // Log message indicating the start of the application
      app_log("BLE Security Example Started!\r\n");

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

      // Set up Security Manager
      //
      // 1. Flags:
      //    Bit 0: 0 -> Allow bonding without MITM protection, 1 -> Bonding requires MITM protection
      //    Bit 1: 0 -> Allow encryption without bonding, 1 -> Encryption requires bonding. Note that this setting will also enable bonding.
      //    Bit 2: 0 -> Allow bonding with legacy pairing, 1 -> Secure connections only mode
      //    Bit 3: 0 -> Bonding request does not need to be confirmed, 1 -> Bonding requests need to be confirmed. Received bonding requests are notified with sm_confirm_bonding events.
      //    Bit 4: 0 -> Allow all connections, 1 -> Allow connections only from bonded devices
      //    Bit 5-7: reserved
      //
      // 2. IO Capabilities
      //    DISPLAYONLY     0
      //    DISPLAYYESNO    1
      //    KEYBOARDONLY    2
      //    NOINPUTNOOUTPUT 3
      //    KEYBOARDDISPLAY 4

      // TODO: Test out different IO Capabilities
      // (keep in mind the actual capabilities of the dev kit)
      sc = sl_bt_sm_configure(0x00,DISPLAYONLY);
      app_assert_status(sc);

      // BAD PRACTICE!! (for demo purposes)
      sc = sl_bt_sm_set_passkey(123456);
      app_assert_status(sc);

      // Enable bonding
      sc = sl_bt_sm_set_bondable_mode(1);
      app_assert_status(sc);

      // Delete any existing bondings
      sc = sl_bt_sm_delete_bondings();
      app_assert_status(sc);
      app_log_info("All bonds deleted\r\n");

      // Start advertising and enable connections.
      sc = sl_bt_legacy_advertiser_start(advertising_set_handle,
                                         sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);

      sl_button_enable(SL_SIMPLE_BUTTON_INSTANCE(0));

      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      app_log("Connected!\n");

      ble_bonding_handle = evt->data.evt_connection_opened.bonding;
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      app_log("Disconnected!\n");

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

    // Handle the display passkey event
    case sl_bt_evt_sm_passkey_display_id:
      app_log_info("Passkey: %4lu\r\n", evt->data.evt_sm_passkey_display.passkey);
      break;

    // Bonding
    case sl_bt_evt_sm_bonded_id:
      app_log_info("bonded!\n");


      break;

    // Failed bonding
    case sl_bt_evt_sm_bonding_failed_id:
      app_log_info("Bonding failed, reason 0x%2X\r\n",
                       evt->data.evt_sm_bonding_failed.reason);

      //app_log_info("", evt->data.evt_sm_bonding_failed.connection);

      sc = sl_bt_connection_close(evt->data.evt_sm_bonding_failed.connection);
      app_assert_status(sc);

      if (ble_bonding_handle != 0xFF)
        {
          sc = sl_bt_sm_delete_bonding(ble_bonding_handle);
          app_assert_status(sc);

          app_log_info("Successfully deleted bond %d\r\n", ble_bonding_handle);
        }

      break;

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
