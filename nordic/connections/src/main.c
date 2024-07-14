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

#define ADV_TYPE BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_ONE_TIME, \
                               ADV_INT_MIN, ADV_INT_MAX, NULL)

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

/* Set Advertising data */
/* The device name is included in the advertising data. */
/* The device name is defined in prj.conf*/
static const struct bt_data ad[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static struct bt_conn *default_conn;

void connected(struct bt_conn *conn, uint8_t err)
{
    printk("Connected (err 0x%02X)\n", err);

    if (err) {
        default_conn = NULL;

        return;
    }

    default_conn = bt_conn_ref(conn);
}

void disconnected(struct bt_conn *conn, uint8_t reason)
{
    bt_conn_unref(default_conn);
    default_conn = NULL;

    printk("Disconnected (reason 0x%02X)\n", reason);
}

BT_CONN_CB_DEFINE(conn_cb) = {
    .connected = connected,
    .disconnected = disconnected,
};

static void bt_ready(int err)
{
    char addr_s[BT_ADDR_LE_STR_LEN];
    struct bt_le_oob oob;

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
     * advertising a non-resolvable private address is used;
     * there is no API to retrieve that.
     */

    /* Restore connectable if slot */
    bt_le_oob_get_local(BT_ID_DEFAULT, &oob);
    bt_addr_le_to_str(&oob.addr, addr_s, sizeof(addr_s));
    printk("Initial advertising as %s\n", addr_s);
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
