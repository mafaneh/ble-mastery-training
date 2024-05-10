/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "sl_bt_ead_core.h"
#include "psa/crypto.h"
#include "app.h"

#include "sl_bt_api.h"
#include "app_log.h"

struct sl_bt_ead_key_material_s key_material = {
    .key = { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
             0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF},
    .iv =  { 0xFB, 0x56, 0xE1, 0xDA, 0xDC, 0x7E, 0xAD, 0xF5 },
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
  uint8_t system_id[8];
  struct sl_bt_ead_nonce_s nonce;

//  uint8_t app_connection;
  bd_addr *remote_address;
  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);

      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];

      sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                                   0,
                                                   sizeof(system_id),
                                                   system_id);
      app_assert_status(sc);

      sc = sl_bt_ead_session_init(&key_material, NULL, &nonce);
      app_assert_status(sc);

      app_log_info("System Boot\r\n");

      sc = sl_bt_scanner_set_parameters(sl_bt_scanner_scan_mode_passive, 200, 20);
      app_assert_status(sc);

      // start scanning
      sl_bt_scanner_start(sl_bt_scanner_scan_phy_1m,
                          sl_bt_scanner_discover_observation);
      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      sl_bt_scanner_stop();
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      sl_bt_scanner_start(sl_bt_scanner_scan_phy_1m,
                          sl_bt_scanner_discover_observation);
      break;

    case sl_bt_evt_scanner_legacy_advertisement_report_id:

      remote_address = &(evt->data.evt_scanner_legacy_advertisement_report.address);
      if (remote_address->addr[5] == 0x58 && remote_address->addr[0] == 0x8E)
        {
          app_log("Advertisement/Scan Response from %2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X\r\n",
                 remote_address->addr[5],
                 remote_address->addr[4],
                 remote_address->addr[3],
                 remote_address->addr[2],
                 remote_address->addr[1],
                 remote_address->addr[0]);

          app_log("Raw Data (RSSI = %d dBm | Length = %d bytes): \r\n",
                  evt->data.evt_scanner_legacy_advertisement_report.rssi,
                  evt->data.evt_scanner_legacy_advertisement_report.data.len);
          for(int i = 0; i< evt->data.evt_scanner_legacy_advertisement_report.data.len; i++){
             app_log("%02X ", evt->data.evt_scanner_legacy_advertisement_report.data.data[i]);
          }
          app_log("\r\n");

          if (evt->data.evt_scanner_legacy_advertisement_report.data.data[1] == 0x31)
            {
              app_log("Includes Encrypted Advertising Data (AD type = 0x31)\r\n");

              // Let's decrypt the data (using the hardcoded key material)
              uint8_t *decrypted_msg = evt->data.evt_scanner_legacy_advertisement_report.data.data;
              uint8_t msg_length = evt->data.evt_scanner_legacy_advertisement_report.data.len;

              sc = sl_bt_ead_unpack_decrypt(&key_material, &decrypted_msg, &msg_length);
              app_assert_status(sc);

              app_log("Decrypted Advertising Data: ");
              for(int i = 0; i< msg_length; i++){
                 app_log("%02X ", decrypted_msg[i]);
              }
              app_log("\r\n");
            }

          app_log("\r\n");
        }


      break;

    case sl_bt_evt_connection_phy_status_id:
      app_log_info("using PHY %d\r\n", evt->data.evt_connection_phy_status.phy );
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
