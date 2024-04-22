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
#include "sl_bt_ead_core.h"
#include "psa/crypto.h"
#include "app.h"

#define PAYLOAD_MAX 12

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;

static struct sl_bt_ead_key_material_s key_material = {

    .key = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
            0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},

    .iv  = {0xFB, 0x56, 0xE1, 0xDA, 0xDC, 0x7E, 0xAD, 0xF5},
};

static uint8_t encyrpted_data_buffer[SL_BT_EAD_PACKET_OVERHEAD + PAYLOAD_MAX];

#define DEVICE_NAME_VALUE "Novel Bits"

typedef struct
{
  // Device Name (Complete Local Name)
  uint8_t device_name_len;
  uint8_t device_name_type;
  uint8_t device_name_value[10];

} adv_data_t;

static adv_data_t adv_data =
{
    // Device Name
    .device_name_len = 11,
    .device_name_type = 0x09, // Device Name AD Type
    .device_name_value = DEVICE_NAME_VALUE

};

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
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
  uint8_t len;
  struct sl_bt_ead_nonce_s nonce;
  sl_bt_ead_mic_t mic;

  struct sl_bt_ead_ad_structure_s ad_info = {
    sizeof(adv_data),
    SL_BT_ENCRYPTED_DATA_AD_TYPE,
    &nonce.randomizer,
    (uint8_t *)&adv_data,
    &mic
  };

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      {
        app_log("EAD Example Started!\r\n");


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

        // EAD code

        len = sizeof(adv_data_t);
        sc = sl_bt_ead_session_init(&key_material, NULL, &nonce);

        if (sc == SL_STATUS_OK) {
          sc = sl_bt_ead_encrypt(&key_material, &nonce, len, (uint8_t *)&adv_data, mic);
        }

        if (sc == SL_STATUS_OK) {
          len = sizeof(encyrpted_data_buffer);
          sc = sl_bt_ead_pack_ad_data(&ad_info, &len, encyrpted_data_buffer);
        }

        app_log("Encrypted adv data (%d): ", len);
        for (int i=0; i < len; i++)
          {
            app_log("%02X ", encyrpted_data_buffer[i]);
          }

        app_log("\r\n");

        sc = sl_bt_legacy_advertiser_set_data(advertising_set_handle, sl_bt_advertiser_advertising_data_packet, len, encyrpted_data_buffer);
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
                                           sl_bt_legacy_advertiser_connectable);
        app_assert_status(sc);
      }

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
                                         sl_bt_legacy_advertiser_connectable);
      app_assert_status(sc);
      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}
