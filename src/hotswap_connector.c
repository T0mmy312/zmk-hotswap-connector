#define DT_DRV_COMPAT hotswap_connector

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#include "../include/hotswap_connector.h"

LOG_MODULE_REGISTER(hotswap_connector, LOG_LEVEL_INF);

#define HOTSWAP_CONNECTOR_CONFIG_PRIORITY 24

struct hotswap_connector_config {
    struct gpio_dt_spec irq_gpios;
    unsigned int num_potential_devices;
    struct device** potential_devices;
};

struct hotswap_connector_data {
    struct device* parent;
};

static const struct sensor_driver_api hotswap_connector_api = {
    
};

void hotswap_connector_connect_ir(struct hotswap_connector_data* data) {

}

void hotswap_connector_disconnect_ir(struct hotswap_connector_data* data) {

}

static int hotswap_connector_init(const struct device *dev, void (*connect_irq_func)(const struct device *gpio_dev, struct gpio_callback *cb, uint32_t pins), void (*disconnect_irq_func)(const struct device *gpio_dev, struct gpio_callback *cb, uint32_t pins)) {
    struct hotswap_connector_data* data = (struct hotswap_connector_data*)dev->data;
    const struct hotswap_connector_config* config = (const struct hotswap_connector_config*)dev->config;

    data->parent = dev;
}

// DT_INST_FOREACH_PROP_ELEM_SEP()
// DT_INST_PHANDLE_BY_IDX()

// struct gpio_dt_spec specs[] = { DT_FOREACH_PROP_ELEM_SEP(DT_NODELABEL(n), my_gpios, GPIO_DT_SPEC_GET_BY_IDX, (,)) };

#define GET_DEVICE_FROM_PHANDLES_BY_IDX(inst, prop, idx) DEVICE_DT_GET(DT_INST_PHANDLE_BY_IDX(inst, prop, idx))

#define HOTSWAP_CONNECTOR_DEFINE(i) \
    struct device* potential_hotswap_devices##i[] = {DT_INST_FOREACH_PROP_ELEM_SEP(i, potential_devices, GET_DEVICE_FROM_PHANDLES_BY_IDX, (,))};\
    const struct hotswap_connector_config hotswap_connector_config##i = { \
        .irq_gpios = GPIO_DT_SPEC_INST_GET(i, irq_gpios), \
        .num_potential_devices = DT_INST_PROP_LEN(i, potential_devices), \
        .potential_devices = potential_hotswap_devices##i \
    }; \
    struct hotswap_connector_data hotswap_connector_data##i; \
    void hotswap_connector_connect_ir##i(const struct device *gpio_dev, struct gpio_callback *cb, uint32_t pins) { \
        hotswap_connector_connect_ir(&hotswap_connector_data##i); \
    } \
    void hotswap_connector_disconnect_ir##i(const struct device *gpio_dev, struct gpio_callback *cb, uint32_t pins) { \
        hotswap_connector_disconnect_ir(&hotswap_connector_data##i); \
    } \
    static int hotswap_connector_init##i(const struct device *dev) { \
        hotswap_connector_init(dev, hotswap_connector_connect_ir##i, hotswap_connector_disconnect_ir##i); \
    } \
    DEVICE_DT_INST_DEFINE(i, led_blink_init_##i, NULL, &data##i, &config##i, POST_KERNEL, LED_BLINK_CONFIG_PRIORITY, &led_blink_api);

DT_INST_FOREACH_STATUS_OKAY(HOTSWAP_CONNECTOR_DEFINE);