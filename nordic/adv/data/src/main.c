/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>

// Uncomment the following line to enable scannability and include scan response data in the advertising packet
#define INCLUDE_SCAN_RESPONSE_DATA

// Advertising Interval values are in the range of 20ms to 10.24s
// The value is in units of 0.625ms (E.g., 160 -> 100ms, 320 -> 200ms, 400 -> 250ms, 1600 -> 1s, 10240 -> 10.24s)
#define ADV_INT_MIN 160
#define ADV_INT_MAX 160

#ifdef INCLUDE_SCAN_RESPONSE_DATA
#define ADV_TYPE BT_LE_ADV_PARAM(BT_LE_ADV_OPT_SCANNABLE, \
                               ADV_INT_MIN, ADV_INT_MAX, NULL)
#else 
#define ADV_TYPE BT_LE_ADV_PARAM(BT_LE_ADV_OPT_NONE, \
                               ADV_INT_MIN, ADV_INT_MAX, NULL)
#endif

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

/* Set Advertising data */
/* The device name is included in the advertising data. */
/* The device name is defined in prj.conf*/
static const struct bt_data ad[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

#ifdef INCLUDE_SCAN_RESPONSE_DATA

// Company ID for Novel Bits (used for the manufacturer data)
#define NOVEL_BITS_COMPANY_ID 0x08D3

/* Set Scan Response data */
/* The manufacturer data is included in the scan response data. */
static const struct bt_data sd[] = {
        BT_DATA_BYTES(BT_DATA_MANUFACTURER_DATA,
                  (NOVEL_BITS_COMPANY_ID & 0xFF),
                  ((NOVEL_BITS_COMPANY_ID >> 8) & 0xFF),
                  0x01, 0x02, 0x03, 0x04, 0x05, 0x06),
};
#endif

static void bt_ready(int err)
{
    char addr_s[BT_ADDR_LE_STR_LEN];
    bt_addr_le_t addr = {0};
    size_t count = 1;

    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }

    printk("Bluetooth initialized\n");

    /* Start advertising - */
    #ifdef INCLUDE_SCAN_RESPONSE_DATA
    err = bt_le_adv_start(ADV_TYPE, ad, ARRAY_SIZE(ad),
                  sd, ARRAY_SIZE(sd));
    #else
    err = bt_le_adv_start(ADV_TYPE, ad, ARRAY_SIZE(ad),
                  NULL, 0);
    #endif
    if (err) {
        printk("Advertising failed to start (err %d)\n", err);
        return;
    }

    /* For connectable advertising you would use
     * bt_le_oob_get_local().  For non-connectable non-identity
     * advertising a non-resolvable private address is used;
     * there is no API to retrieve that.
     */

    bt_id_get(&addr, &count);
    bt_addr_le_to_str(&addr, addr_s, sizeof(addr_s));

    printk("Advertising started as %s\n", addr_s);
}

int main(void)
{
    int err;

    printk("Starting Advertising Demo\n");

    /* Initialize the Bluetooth Subsystem */
    err = bt_enable(bt_ready);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
    }
    return 0;
}
