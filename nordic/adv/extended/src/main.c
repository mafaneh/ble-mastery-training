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

// Advertising Interval values are in the range of 20ms to 10.24s
// The value is in units of 0.625ms (E.g., 160 -> 100ms, 320 -> 200ms, 400 -> 250ms, 1600 -> 1s, 10240 -> 10.24s)
#define ADV_INT_MIN 160
#define ADV_INT_MAX 160

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

/* Set Advertising data */
/* The device name is included in the advertising data. */
/* The device name is defined in prj.conf*/
// static const struct bt_data ad[] = {
//     BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
// };


// Company ID for Novel Bits (used for the manufacturer data)
#define NOVEL_BITS_COMPANY_ID 0x08D3

/* Set Scan Response data */
/* The manufacturer data is included in the scan response data. */
static const struct bt_data ad[] = {
        BT_DATA_BYTES(BT_DATA_MANUFACTURER_DATA,
                  (NOVEL_BITS_COMPANY_ID & 0xFF),
                  ((NOVEL_BITS_COMPANY_ID >> 8) & 0xFF),
                  0x01, 0x02, 0x03, 0x04, 0x05, 0x06),
};

struct bt_le_adv_param adv_param = {
        .id = BT_ID_DEFAULT,
        .sid = 0U, /* Supply unique SID when creating advertising set */
        .secondary_max_skip = 0U,
        .options = BT_LE_ADV_OPT_EXT_ADV | BT_LE_ADV_OPT_USE_NAME,
        .interval_min = ADV_INT_MIN,
        .interval_max = ADV_INT_MAX,
        .peer = NULL,
    };

static void bt_ready(int err)
{
    char addr_s[BT_ADDR_LE_STR_LEN];
    bt_addr_le_t addr = {0};
    size_t count = 1;
    struct bt_le_ext_adv *ext_adv;

    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }

    printk("Bluetooth initialized\n");

    /* Create a non-connectable non-scannable advertising set */
    err = bt_le_ext_adv_create(&adv_param, NULL, &ext_adv);
    if (err) {
        printk("Failed to create advertising set (err %d)\n", err);
        return;
    }

    /* Set extended advertising data */
    err = bt_le_ext_adv_set_data(ext_adv, ad, ARRAY_SIZE(ad),
                        NULL, 0);
    if (err) {
        printk("Failed to set advertising data for set "
                "(err %d)\n", err);
        return;
    }

    /* Start extended advertising set */
    err = bt_le_ext_adv_start(ext_adv, BT_LE_EXT_ADV_START_DEFAULT);
    if (err) {
        printk("Failed to start extended advertising set "
                "(err %d)\n", err);
        return;
    }

    printk("Started Extended Advertising Set 0\n");

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
