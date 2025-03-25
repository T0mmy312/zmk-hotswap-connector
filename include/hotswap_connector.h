#ifndef _HOTSWAP_CONNECTOR_H_
#define _HOTSWAP_CONNECTOR_H_

#include <zephyr/types.h>

//! THIS HAS TO BE ADDED AS THE FIRST ELEMENT OF THE DATA STRUCT OF ANY POTENTIAL HOTSWAP DEVICES OR IT WILL NOT WORK

struct hotswap_device_data {
    bool active; // sets if the current device is active or not, should not do anything if not
    uint8_t unique_reg; // the register that contains a unique value in comparison to all other potential devices
    uint8_t unique_val; // the value of that unique register
};

#endif