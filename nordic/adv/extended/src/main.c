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

// Adjust the following line to test different advertising options
#define ADV_OPTION 3

#if (ADV_OPTION == 1)
// OPTION 1: Non-connectable non-scannable
// - Includes device name in advertising data
#define ADV_TYPE (BT_LE_ADV_OPT_EXT_ADV | BT_LE_ADV_OPT_USE_NAME)

#elif (ADV_OPTION == 2)
// OPTION 2: Non-connectable scannable
// - Includes device name in advertising data
// - Requires scan response data
#define ADV_TYPE (BT_LE_ADV_OPT_EXT_ADV | BT_LE_ADV_OPT_SCANNABLE | BT_LE_ADV_OPT_USE_NAME)

// Company ID for Novel Bits (used for the manufacturer data)
#define NOVEL_BITS_COMPANY_ID 0x08D3

/* This is only used in the scannable adv mode */
static const struct bt_data sd[] = {
        BT_DATA_BYTES(BT_DATA_MANUFACTURER_DATA,
                  (NOVEL_BITS_COMPANY_ID & 0xFF),
                  ((NOVEL_BITS_COMPANY_ID >> 8) & 0xFF),
                  0x01, 0x02, 0x03, 0x04, 0x05, 0x06),
};

#elif (ADV_OPTION == 3)
// OPTION 3: Connectable non-scannable
// - Includes device name in advertising data
#define ADV_TYPE (BT_LE_ADV_OPT_EXT_ADV | BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_USE_NAME)

#endif 

struct bt_le_adv_param adv_param = {
        .id = BT_ID_DEFAULT,
        .sid = 0U, /* Supply unique SID when creating advertising set */
        .secondary_max_skip = 0U,
        // Choose one of the options above
        .options = ADV_TYPE,
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

    err = bt_le_ext_adv_create(&adv_param, NULL, &ext_adv);
    if (err) {
        printk("Failed to create advertising set (err %d)\n", err);
        return;
    }

    /* Set extended advertising data */

    // In the case of scannable advertising, the scan response data must be set
    #if (ADV_OPTION == 2)
    err = bt_le_ext_adv_set_data(ext_adv, NULL, 0, sd, ARRAY_SIZE(sd));
    if (err) {
        printk("Failed to set advertising data for set (err %d)\n", err);
        return;
    }
    #else
    err = bt_le_ext_adv_set_data(ext_adv, NULL, 0, NULL, 0);
    if (err) {
        printk("Failed to set advertising data for set (err %d)\n", err);
        return;
    }
    #endif

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
