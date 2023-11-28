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
#include <stdio.h>

#include "sl_bt_api.h"
#include "sl_board_control.h"
#include "sl_sleeptimer.h"

#include "app.h"
#include "app_log.h"
#include "app_assert.h"
#include "dmd.h"
#include "glib.h"
#include "em_assert.h"

#include "app_button_press.h"
#include "sl_simple_button.h"
#include "sl_simple_button_instances.h"

#ifndef LCD_MAX_LINES
#define LCD_MAX_LINES      11
#endif

static GLIB_Context_t glibContext;
static int currentLine = 0;

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;

// Button press data (Buttons 0 and 1)
static uint8_t adv_data_button_0 = 0;      // Advertising Data for Subevent #1
static uint8_t adv_data_button_1 = 0;      // Advertising Data for Subevent #2
static uint8_t adv_data_button_0_long = 0; // Advertising Data for Subevent #3
static uint8_t adv_data_button_1_long = 0; // Advertising Data for Subevent #4

static uint8_t led1_status = 0xFF, led2_status = 0xFF, led3_status = 0xFF, led4_status = 0xFF;
static int8_t rssi1_value = 0xFF, rssi2_value = 0xFF, rssi3_value = 0xFF, rssi4_value = 0xFF;

void memlcd_app_update_led_status(void)
{
  currentLine = 0;
  GLIB_clear(&glibContext);

  char led_status_string[20], rssi_1_str[20], rssi_2_str[20], rssi_3_str[20], rssi_4_str[20];

  /* Draw text on the memory lcd display*/
    GLIB_drawStringOnLine(&glibContext,
                          "PAwR Advertiser Demo",
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          5,
                          5,
                          true);

    GLIB_drawStringOnLine(&glibContext,
                          "--------------------",
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          5,
                          5,
                          true);

    strcpy(led_status_string, "Subevent#1 LED: ");
    if (led1_status == 0xFF)
      {
        strcat(led_status_string, "N/A");
        sprintf(rssi_1_str, "RSSI #1: N/A");
      }
    else{
        strcat(led_status_string, led1_status?"On":"Off");
        sprintf(rssi_1_str, "RSSI #1: %d dBm", rssi1_value);
    }
    GLIB_drawStringOnLine(&glibContext,
                          led_status_string,
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          5,
                          5,
                          true);
    // RSSI value
    GLIB_drawStringOnLine(&glibContext,
                          rssi_1_str,
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          10,
                          5,
                          true);


    strcpy(led_status_string, "Subevent#2 LED: ");
    if (led2_status == 0xFF)
      {
        strcat(led_status_string, "N/A");
        sprintf(rssi_2_str, "RSSI #2: N/A");
      }
    else{
        strcat(led_status_string, (led2_status == 0x01)?"On":"Off");
        sprintf(rssi_2_str, "RSSI #2: %d dBm", rssi2_value);
    }
    // LED status
    GLIB_drawStringOnLine(&glibContext,
                          led_status_string,
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          5,
                          5,
                          true);
    // RSSI value
    GLIB_drawStringOnLine(&glibContext,
                          rssi_2_str,
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          10,
                          5,
                          true);

    strcpy(led_status_string, "Subevent#3 LED: ");
    if (led3_status == 0xFF)
      {
        strcat(led_status_string, "N/A");
        sprintf(rssi_3_str, "RSSI #3: N/A");
      }
    else{
        strcat(led_status_string, (led3_status == 0x01)?"On":"Off");
        sprintf(rssi_3_str, "RSSI #3: %d dBm", rssi3_value);
    }
    // LED status
    GLIB_drawStringOnLine(&glibContext,
                          led_status_string,
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          5,
                          5,
                          true);
    // RSSI value
    GLIB_drawStringOnLine(&glibContext,
                          rssi_3_str,
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          10,
                          5,
                          true);

    strcpy(led_status_string, "Subevent#4 LED: ");
    if (led4_status == 0xFF)
      {
        strcat(led_status_string, "N/A");
        sprintf(rssi_4_str, "RSSI #4: N/A");
      }
    else{
        strcat(led_status_string, (led4_status == 0x01)?"On":"Off");
        sprintf(rssi_4_str, "RSSI #4: %d dBm", rssi4_value);
    }
    // LED status
    GLIB_drawStringOnLine(&glibContext,
                          led_status_string,
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          5,
                          5,
                          true);

    // RSSI value
    GLIB_drawStringOnLine(&glibContext,
                          rssi_4_str,
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          10,
                          5,
                          true);

    GLIB_drawStringOnLine(&glibContext,
                          led_status_string,
                          currentLine++,
                          GLIB_ALIGN_LEFT,
                          5,
                          5,
                          true);

    DMD_updateDisplay();
}

void memlcd_app_init(void)
{
  uint32_t status;

  /* Enable the memory lcd */
  status = sl_board_enable_display();
  EFM_ASSERT(status == SL_STATUS_OK);

  /* Initialize the DMD support for memory lcd display */
  status = DMD_init(0);
  EFM_ASSERT(status == DMD_OK);

  /* Initialize the glib context */
  status = GLIB_contextInit(&glibContext);
  EFM_ASSERT(status == GLIB_OK);

  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;

  /* Fill lcd with background color */
  GLIB_clear(&glibContext);

  /* Use Narrow font */
  GLIB_setFont(&glibContext, (GLIB_Font_t *) &GLIB_FontNarrow6x8);

  /* Draw text on the memory lcd display*/
  GLIB_drawStringOnLine(&glibContext,
                        "PAwR Advertiser Demo",
                        currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);
  GLIB_drawStringOnLine(&glibContext,
                        "--------------------",
                        currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);
  GLIB_drawStringOnLine(&glibContext,
                        " Subevent#1 LED: N/A",
                        currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);
  GLIB_drawStringOnLine(&glibContext,
                        " Subevent#2 LED: N/A",
                        currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);
  GLIB_drawStringOnLine(&glibContext,
                        " Subevent#3 LED: N/A",
                        currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);
  GLIB_drawStringOnLine(&glibContext,
                        " Subevent#4 LED: N/A",
                        currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);

  DMD_updateDisplay();
}

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(void)
{
  app_log("\r\n------  BLE - PAwR LED Controller "
          "Demo: Controller Role-----\r\n");

  // Enable buttons
  sl_simple_button_enable(&sl_button_btn0);
  sl_simple_button_enable(&sl_button_btn1);

  // Wait
  sl_sleeptimer_delay_millisecond(1);

  // Enable button presses
  app_button_press_enable();

  // Clear advertising data for all subevents
  adv_data_button_0 = 0;
  adv_data_button_1 = 0;
  adv_data_button_0_long = 0;
  adv_data_button_1_long = 0;

  memlcd_app_init();
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
  DMD_updateDisplay();

}

void app_button_press_cb(uint8_t button, uint8_t duration)
{
  // Selecting action by duration
  switch (duration)
  {
    // Handling of button presses less than 0.25s
    case APP_BUTTON_PRESS_DURATION_SHORT:
    {
      if (button == 0)
        {
          // Toggle value (0 or 1)
          adv_data_button_0 = !(adv_data_button_0 & 0x01);
          app_log("-----Sending LED ON/OFF trigger on Subevent #1-----\r\n");
        }
      else if (button == 1)
        {
          // Toggle value (0 or 1)
          adv_data_button_1 = !(adv_data_button_1 & 0x01);
          app_log("-----Sending LED ON/OFF trigger on Subevent #2-----\r\n");
        }
    } break;
    // Handling of button presses greater than 0.25s
    case APP_BUTTON_PRESS_DURATION_MEDIUM:
    case APP_BUTTON_PRESS_DURATION_LONG:
    case APP_BUTTON_PRESS_DURATION_VERYLONG:
    {
      if (button == 0)
        {
          // Toggle value (0 or 1)
          adv_data_button_0_long = !(adv_data_button_0_long & 0x01);
          app_log("-----Sending LED ON/OFF trigger on Subevent #3-----\r\n");
        }
      else if (button == 1)
        {
          // Toggle value (0 or 1)
          adv_data_button_1_long = !(adv_data_button_1_long & 0x01);
          app_log("-----Sending LED ON/OFF trigger on Subevent #4-----\r\n");
        }
    } break;
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

      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      app_assert_status(sc);

      // Start extended advertising
      sc = sl_bt_extended_advertiser_generate_data(advertising_set_handle,
                                                   sl_bt_advertiser_general_discoverable);

      app_assert_status(sc);

      // set phy
      sc = sl_bt_extended_advertiser_set_phy(advertising_set_handle,
                                             sl_bt_gap_phy_coded,
                                             sl_bt_gap_phy_coded);

      app_assert_status(sc);

      sc = sl_bt_extended_advertiser_start(advertising_set_handle,
                                           sl_bt_extended_advertiser_non_connectable,
                                           0);

      app_assert_status(sc);

      // Start periodic advertising with periodic interval 1541.25ms
      sc = sl_bt_pawr_advertiser_start(advertising_set_handle,
                                       80,  // 100 ms (1.25 ms units)
                                       80,  // 100 ms (1.25 ms units)
                                       0,
                                       5,    // sub event count = 5
                                       16,   // sub event interval = 20ms (1.25 ms units)
                                       8,    // slot delay = 10ms (1.25 ms units)
                                       8,    // slot spacing = 1ms (0.125 ms units)
                                       5);   // slot count = 5
      app_assert_status(sc);

      break;

    // -------------------------------
    // subevent_data_request event handler.
    case sl_bt_evt_pawr_advertiser_subevent_data_request_id:
      if (evt->data.evt_pawr_advertiser_subevent_data_request.subevent_start
          == 1) {
        sc = sl_bt_pawr_advertiser_set_subevent_data(
          advertising_set_handle,
          evt->data.evt_pawr_advertiser_subevent_data_request.subevent_start,
          0,
          5,
          sizeof(adv_data_button_0),
          &adv_data_button_0);
        app_assert_status(sc);
      }
      else if (evt->data.evt_pawr_advertiser_subevent_data_request.subevent_start
          == 2) {
        sc = sl_bt_pawr_advertiser_set_subevent_data(
          advertising_set_handle,
          evt->data.evt_pawr_advertiser_subevent_data_request.subevent_start,
          0,
          5,
          sizeof(adv_data_button_1),
          &adv_data_button_1);
        app_assert_status(sc);
      }
      else if (evt->data.evt_pawr_advertiser_subevent_data_request.subevent_start
          == 3) {
        sc = sl_bt_pawr_advertiser_set_subevent_data(
          advertising_set_handle,
          evt->data.evt_pawr_advertiser_subevent_data_request.subevent_start,
          0,
          5,
          sizeof(adv_data_button_0_long),
          &adv_data_button_0_long);
        app_assert_status(sc);
      }
      else if (evt->data.evt_pawr_advertiser_subevent_data_request.subevent_start
          == 4) {
        sc = sl_bt_pawr_advertiser_set_subevent_data(
          advertising_set_handle,
          evt->data.evt_pawr_advertiser_subevent_data_request.subevent_start,
          0,
          5,
          sizeof(adv_data_button_1_long),
          &adv_data_button_1_long);
        app_assert_status(sc);
      }

      break;

    // -------------------------------
    // subevent_tx_failed event handler.
    case sl_bt_evt_pawr_advertiser_subevent_tx_failed_id:
      app_log("sub event data failed \r\n");
      break;

    // -------------------------------
    // response_report event handler.
    case sl_bt_evt_pawr_advertiser_response_report_id:
      if (evt->data.evt_pawr_advertiser_response_report.data.len) {
        app_log("Data response from Subevent %d in Response_slot %d: %s\r\n",
                evt->data.evt_pawr_advertiser_response_report.subevent,
                evt->data.evt_pawr_advertiser_response_report.response_slot,
                (evt->data.evt_pawr_advertiser_response_report.data.data[0] == 0x01)?"LED is On":"LED is Off");
        app_log("\r\n");
        if (evt->data.evt_pawr_advertiser_response_report.subevent == 1)
          {
            led1_status = (evt->data.evt_pawr_advertiser_response_report.data.data[0] == 0x01)?true:false;

            rssi1_value = evt->data.evt_pawr_advertiser_response_report.rssi;
          }
        else if (evt->data.evt_pawr_advertiser_response_report.subevent == 2)
          {
            led2_status = (evt->data.evt_pawr_advertiser_response_report.data.data[0] == 0x01)?true:false;

            rssi2_value = evt->data.evt_pawr_advertiser_response_report.rssi;
          }
        else if (evt->data.evt_pawr_advertiser_response_report.subevent == 3)
          {
            led3_status = (evt->data.evt_pawr_advertiser_response_report.data.data[0] == 0x01)?true:false;

            rssi3_value = evt->data.evt_pawr_advertiser_response_report.rssi;
          }
        else if (evt->data.evt_pawr_advertiser_response_report.subevent == 4)
          {
            led4_status = (evt->data.evt_pawr_advertiser_response_report.data.data[0] == 0x01)?true:false;

            rssi4_value = evt->data.evt_pawr_advertiser_response_report.rssi;
          }
        memlcd_app_update_led_status();
      }
      break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}
