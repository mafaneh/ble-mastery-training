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
// Change the following values to test different advertising intervals
#define ADV_INT_MIN 1600
#define ADV_INT_MAX 1600

// We are going to test the following advertising types:
// Type_1: Non-connectable undirected advertising (scannable)
#define TYPE_1 BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_ONE_TIME | BT_LE_ADV_OPT_SCANNABLE, \
                               ADV_INT_MIN, ADV_INT_MAX, NULL)

// Type_2: Non-connectable undirected advertising (scannable)
#define TYPE_2 BT_LE_ADV_PARAM(BT_LE_ADV_OPT_SCANNABLE, \
                               ADV_INT_MIN, ADV_INT_MAX, NULL)

// Type_3: Connectable undirected advertising (non-scannable)
#define TYPE_3 BT_LE_ADV_PARAM(BT_LE_ADV_OPT_NONE, \
                               ADV_INT_MIN, ADV_INT_MAX, NULL)

// TODO: Change the value of ADV_TYPE to test the different advertising types defined above
#define ADV_TYPE TYPE_1

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

/* Set Advertising data */
/* The device name is included in the advertising data. */
/* The device name is defined in prj.conf*/
static const struct bt_data ad[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

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
    err = bt_le_adv_start(ADV_TYPE, ad, ARRAY_SIZE(ad),
                  NULL, 0);
    if (err) {
        printk("Advertising failed to start (err %d)\n", err);
        return;
    }

    /* For connectable advertising you would use
     * bt_le_oob_get_local().  For non-connectable non-identity
     * advertising an non-resolvable private address is used;
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
