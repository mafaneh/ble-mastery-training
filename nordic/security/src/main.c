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
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

// Include the DK LED and Button API
#include <dk_buttons_and_leds.h>

#define BUTTON_1 DK_BTN1_MSK

static bool button_1_state;

static bool notify_enabled;

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

// ---- GATT Definitions ----

// Strings for the User Description Descriptors
#define LED_1_DESCRIPTION "LED 1"
#define BUTTON_1_DESCRIPTION "Button 1"

static ssize_t read_button_1(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset)
{
    const char *value = attr->user_data;

    printk("Attribute read, handle: %u, conn: %p\n", attr->handle,
        (void *)conn);

    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                    sizeof(*value));
}

static ssize_t write_led_1(struct bt_conn *conn,
             const struct bt_gatt_attr *attr,
             const void *buf,
             uint16_t len, uint16_t offset, uint8_t flags)
{
    printk("Attribute write, handle: %u, conn: %p\n", attr->handle,
        (void *)conn);

    if (len != 1U) {
        printk("Write led: Incorrect data length\n");
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    if (offset != 0) {
        printk("Write led: Incorrect data offset\n");
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }

    // Write the value to LED 1
    uint8_t val = *((uint8_t *)buf);
    printk("Turning %s LED 1\n", val == 0 ? "off" : "on");
    dk_set_led(DK_LED1, val);

    return len;
}

static void lbslc_ccc_cfg_changed(const struct bt_gatt_attr *attr,
                  uint16_t value)
{
    notify_enabled = (value == BT_GATT_CCC_NOTIFY);
}

// Simple Service UUID: 12345678-1234-5678-1234-56789abcdef0
static struct bt_uuid_128 simple_service_uuid =
    BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0));

// ----- Characteristic UUIDs -----
// LED 1 Characteristic: 12345678-1234-5678-1234-56789abcdef1
static struct bt_uuid_128 led_1_char_uuid =
    BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1));
// Button 1 Characteristic: 12345678-1234-5678-1234-56789abcdef4
static struct bt_uuid_128 button_1_char_uuid =
    BT_UUID_INIT_128(BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef2));

BT_GATT_SERVICE_DEFINE(
    simple_svc,
    
    // Simple Service [Index 0]
    BT_GATT_PRIMARY_SERVICE(&simple_service_uuid.uuid),

    // LED 1 Characteristic  [Indexes 1 and 2]
    // Properties: Write Only
    BT_GATT_CHARACTERISTIC(&led_1_char_uuid.uuid,
                    BT_GATT_CHRC_WRITE,
                    BT_GATT_PERM_WRITE_ENCRYPT,
                    NULL, write_led_1, NULL),

    // User Description Descriptor [Index 3]
    BT_GATT_CUD(LED_1_DESCRIPTION, BT_GATT_PERM_READ),

    // Button 1 Characteristic  [Indexes 4 and 5]
    // Properties: Read & Notify
    BT_GATT_CHARACTERISTIC(&button_1_char_uuid.uuid,
                    BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                    BT_GATT_PERM_READ_AUTHEN, read_button_1, NULL, &button_1_state),

    
    // Client Characteristic Configuration Descriptor [Index 6]
    BT_GATT_CCC(lbslc_ccc_cfg_changed, BT_GATT_PERM_READ_AUTHEN | BT_GATT_PERM_WRITE_AUTHEN),    
    
    // User Description Descriptor [Index 7]       
    BT_GATT_CUD(BUTTON_1_DESCRIPTION, BT_GATT_PERM_READ)
);

static void button_changed(uint32_t button_state, uint32_t has_changed)
{
    if (has_changed & BUTTON_1)
    {
        uint32_t user_button_state = button_state & BUTTON_1;
        button_1_state = user_button_state ? true : false;

        if (!notify_enabled) {
                return;
        }

        bt_gatt_notify(NULL, &simple_svc.attrs[4], &button_1_state, sizeof(button_1_state));
    }
}

static int init_buttons_and_leds(void)
{
    int err;

    err = dk_buttons_init(button_changed);
    if (err) {
        printk("Cannot init buttons (err: %d)\n", err);
    }

    err = dk_leds_init();
    if (err) {
        printk("LEDs init failed (err %d)\n", err);
    }

    return err;
}

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

static void on_security_changed(struct bt_conn *conn, bt_security_t level,
			     enum bt_security_err err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	if (!err) {
		printk("Security changed: %s level %u\n", addr, level);
	} else {
		printk("Security failed: %s level %u err %d\n", addr, level,
			err);
	}
}


BT_CONN_CB_DEFINE(conn_cb) = {
    .connected = connected,
    .disconnected = disconnected,
    .security_changed = on_security_changed,
};

static void auth_cancel(struct bt_conn *conn)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    printk("Pairing cancelled: %s\n", addr);
}

static void passkey_display(struct bt_conn *conn, unsigned int passkey)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Passkey for %s: %06u\n", addr, passkey);
}

static struct bt_conn_auth_cb auth_cb_display = {
    // Supports display only (allows passkey entry on peer device)
    .passkey_display = passkey_display,
    // Does NOT support other input/output capabilities
    .pairing_confirm = NULL,
    .passkey_confirm = NULL,
    .passkey_entry = NULL,
    .cancel = auth_cancel,
};

static void pairing_complete(struct bt_conn *conn, bool bonded)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    printk("Pairing completed: %s, bonded: %d\n", addr, bonded);
}

static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    printk("Pairing failed conn: %s, reason %d\n", addr, reason);
}

static struct bt_conn_auth_info_cb conn_auth_info_callbacks = {
    .pairing_complete = pairing_complete,
    .pairing_failed = pairing_failed,
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

    // Register the authentication callback
    err = bt_conn_auth_cb_register(&auth_cb_display);
    if (err) {
        printk("Failed to register authorization callbacks.\n");
        return;
    }

    err = bt_conn_auth_info_cb_register(&conn_auth_info_callbacks);
    if (err) {
        printk("Failed to register authorization info callbacks.\n");
        return;
    }    
}

int main(void)
{
    int err;

    printk("Starting Advertising Demo\n");

    // Initialize the button
    err = init_buttons_and_leds();

    /* Initialize the Bluetooth Subsystem */
    err = bt_enable(bt_ready);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
    }
    return 0;
}
