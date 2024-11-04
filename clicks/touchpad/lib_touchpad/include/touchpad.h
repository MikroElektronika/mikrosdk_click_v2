/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Touchpad Click driver.
 *
 * \addtogroup touchpad Touchpad Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TOUCHPAD_H
#define TOUCHPAD_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define TOUCHPAD_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TOUCHPAD_RETVAL  uint8_t

#define TOUCHPAD_OK           0x00
#define TOUCHPAD_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define TOUCHPAD_DEVICE_SLAVE_ADDR   0x25 // Slave address
/** \} */

/**
 * \defgroup registers Registers
 * CORE RAM MEMORY MAP
 * \{
 */
#define TOUCHPAD_REG_FW_MAJOR                     0x00
#define TOUCHPAD_REG_FW_MINOR                     0x01
#define TOUCHPAD_REG_APP_ID_LSB                   0x02
#define TOUCHPAD_REG_APP_ID_MSB                   0x03
#define TOUCHPAD_REG_CMD                          0x04
#define TOUCHPAD_REG_MODE                         0x05
#define TOUCHPAD_REG_MODE_CON                     0x06

#define TOUCHPAD_REG_TOUCH_STATE                  0x10 // Touch state
#define TOUCHPAD_REG_TOUCH_X                      0x11 // Touch X
#define TOUCHPAD_REG_TOUCH_Y                      0x12 // Touch Y
#define TOUCHPAD_REG_TOUCH_LSB                    0x13 // Touch XY
#define TOUCHPAD_REG_GESTURE_STATE                0x14 // Gestrure state
#define TOUCHPAD_REG_GESTURE_DIAG                 0x15 // Gestrure diagnostic

#define TOUCHPAD_REG_NUM_OF_X_CHANNELS            0x20 // Number of x channels
#define TOUCHPAD_REG_NUM_OF_Y_CHANNELS            0x21 // Number of y channels
#define TOUCHPAD_REG_SCAN_COUNT                   0x22
#define TOUCHPAD_REG_TOUCH_THR_X                  0x23
#define TOUCHPAD_REG_TOUCH_THR_Y                  0x24

#define TOUCHPAD_REG_ACTIVE_PERIOD_LSB            0x25
#define TOUCHPAD_REG_ACTIVE_PERIOD_MSB            0x26
#define TOUCHPAD_REG_IDLE_PERIOD_LSB              0x27
#define TOUCHPAD_REG_IDLE_PERIOD_MSB              0x28
#define TOUCHPAD_REG_IDLE_TIMEOUT                 0x29
#define TOUCHPAD_REG_HYSTERESIS                   0x2A

#define TOUCHPAD_REG_DEBOUNCE_UP                  0x2B
#define TOUCHPAD_REG_DEBOUNCE_DOWN                0x2C
#define TOUCHPAD_REG_FILTER_TYPE                  0x31
#define TOUCHPAD_REG_FILTER_THR                   0x32
#define TOUCHPAD_REG_LARGE_ACTIVATION_THR_LSB     0x35
#define TOUCHPAD_REG_LARGE_ACTIVATION_THR_MSB     0x36

#define TOUCHPAD_REG_HORIZONTAL_SWIPE_DISTANCE    0x37 // Horisontal swipe distance
#define TOUCHPAD_REG_VERTICAL_SWIPE_DISTANCE      0x38 // Vertical swipe distance
#define TOUCHPAD_REG_SWIPE_HOLD_BOUNDARY          0x39 // Swipe hold boundary
#define TOUCHPAD_REG_TAP_DISTANCE                 0x3A // Tap distance
#define TOUCHPAD_REG_DISTANCE_BETWEEN_TAPS        0x3B // Distance between taps
#define TOUCHPAD_REG_TAP_HOLD_TIME_LSB            0x3C // Tap hold time (LSB)
#define TOUCHPAD_REG_TAP_HOLD_TIME_MSB            0x3D // Tap hold time (MSB)
#define TOUCHPAD_REG_GESTURE_CLICK_TIME           0x3E // Gesture Click time
#define TOUCHPAD_REG_SWIPE_HOLD_THRESHOLD         0x3F // Swipe hold treshold
#define TOUCHPAD_REG_MIN_SWIPE_VELOCITY           0x40 // Min swipe velecity
#define TOUCHPAD_REG_HORIZONTAL_GESTURE_ANGLE     0x41 // Horisontal gesture angle
#define TOUCHPAD_REG_VERTICAL_GESTURE_ANGLE       0x42 // Vertical gesture angle
/** \} */

/**
 * \defgroup Operating_mode Operating mode descriptions
 * \{
 */
#define TOUCHPAD_MODE_STANDBY    0x00
#define TOUCHPAD_MODE_GESTURE    0x01
#define TOUCHPAD_MODE_TOUCH_ONLY 0x02
#define TOUCHPAD_MODE_FULL       0x03
#define TOUCHPAD_MODE_RAW_ADC    0x04
/** \} */

/**
 * \defgroup rawadc_mode Raw ADC mode control register
 * \{
 */
#define TOUCHPAD_RAWADC_TYPE_RES_1_2 0x00
#define TOUCHPAD_RAWADC_TYPE_RES_1   0x01
#define TOUCHPAD_RAWADC_TYPE_RES_2   0x02
/** \} */

/**
 * \defgroup command Command register
 * \{
 */
#define TOUCHPAD_CMD_NV_STORAGE_WRITE   0x80
#define TOUCHPAD_CMD_RESTORE_DEF_CONFIG 0x40
#define TOUCHPAD_CMD_CONFIG_CTRL        0x20
#define TOUCHPAD_CMD_EXECUTE_MANU_TEST  0x08
#define TOUCHPAD_CMD_FORCE_BASELINE     0x01
/** \} */

/**
 * \defgroup rate_period Example frame rate period calculations
 * \{
 */
#define TOUCHPAD_PERIOD_10ms   0x0142
#define TOUCHPAD_PERIOD_20ms   0x0284
#define TOUCHPAD_PERIOD_50ms   0x064C
#define TOUCHPAD_PERIOD_1000ms 0x0C99
/** \} */

/**
 * \defgroup touch_state Current touch state register
 * \{
 */
#define TOUCHPAD_TOUCH_IS_PRESENT      0x01
#define TOUCHPAD_GESTURE_IS_PRESENT    0x02
#define TOUCHPAD_LARGE_ACT_IS_PRESENT  0x04
/** \} */

/**
 * \defgroup gesture_state Gesture state
 * \{
 */
#define TOUCHPAD_GS_NO_GESTURE_PRESENT    0x00 // No Gesture Present
#define TOUCHPAD_GS_SINGLE_CLICK          0x10 // Single Click
#define TOUCHPAD_GS_CLICK_AND_HOLD        0x11 // Click and Hold
#define TOUCHPAD_GS_DOUBLE_CLICK          0x20 // Double Click
#define TOUCHPAD_GS_DOWN_SWIPE            0x31 // Down Swipe
#define TOUCHPAD_GS_DOWN_SWIPE_AND_HOLD   0x32 // Down Swipe and Hold
#define TOUCHPAD_GS_RIGHT_SWIPE           0x41 // Right Swipe
#define TOUCHPAD_GS_RIGHT_SWIPE_AND_HOLD  0x42 // Right Swipe and Hold
#define TOUCHPAD_GS_UP_SWIPE              0x51 // Up Swipe
#define TOUCHPAD_GS_UP_SWIPE_AND_HOLD     0x52 // Up Swipe and Hold
#define TOUCHPAD_GS_LEFT_SWIPE            0x61 // Left Swipe
#define TOUCHPAD_GS_LEFT_SWIPE_AND_HOLD   0x62 // Left Swipe and Hold
/** \} */

/**
 * \defgroup current_event_state CURRENT EVENT STATE REGISTER
 * \{
 */
#define TOUCHPAD_EVENT_TOUCH 1
#define TOUCHPAD_EVENT_GESTURE 2
#define TOUCHPAD_NO_EVENT 0
/** \} */

/**
 * \defgroup gesture_diagnostics GESTURE DIAGNOSTICS REGISTER
 * \{
 */
#define TOUCHPAD_GD_CLICK_TIMEOUT           0x01 // Click Timeout
#define TOUCHPAD_GD_SWIPE_TIMEOUT           0x02 // Swipe Timeout
#define TOUCHPAD_GD_GENERAL_TIMEOUT         0x03 // General Timeout
#define TOUCHPAD_GD_CLICK_THR_EXCEEDED      0x04 // Click Threshold Exceeded
#define TOUCHPAD_GD_SWIPE_THR_EXCEEDED      0x05 // Swipe Threshold Exceeded
#define TOUCHPAD_GD_SWIPE_HOLD_THR          0x06 // Swipe and Hold Threshold Exceeded
#define TOUCHPAD_GD_SWIPE_OPPOSITE_DIR_THR  0x07 // Swipe Opposite Direction Threshold Exceeded
#define TOUCHPAD_GD_SWIPE_HOLD_VALUE        0x09 // Swipe and Hold Value Exceeded
#define TOUCHPAD_GD_OUTSIDE_SWIPE           0x0A // Outside Swipe Angle
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} touchpad_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint8_t i2c_speed;
    uint32_t i2c_address;

} touchpad_cfg_t;

/**
 * @brief Coordinate structure definition.
 */
typedef struct
{
     uint16_t x;  // X position
     uint16_t y;  // Y position

} touchpad_cord_t;

/** \} */ // End types group

// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void touchpad_cfg_setup ( touchpad_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
TOUCHPAD_RETVAL touchpad_init ( touchpad_t *ctx, touchpad_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Touchpad Click.
 * @note waking up the cip and setting the RST to VDD state enter the default configuration
 */
void touchpad_default_cfg ( touchpad_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void touchpad_generic_write ( touchpad_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void touchpad_generic_read ( touchpad_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get touch coordinate
 *
 * @param ctx          Click object.
 * @param cord         A structure that contains information about touch coordinates
 *
 * @description This function reads X and Y coordinate
 */
void touchpad_get_touch_coordinate ( touchpad_t *ctx, touchpad_cord_t *cord );

/**
 * @brief Get interrupt state
 *
 * @param ctx          Click object.
 * @return Interrupt (INT) pin state
 */
uint8_t touchpad_get_interrupt_state ( touchpad_t *ctx );

/**
 * @brief Hardware Reset
 *
 * @param ctx          Click object.
 */
void touchpad_reset( touchpad_t *ctx );

/**
 * @brief Get event state
 *
 * @param ctx          Click object.
 * @return an event that occurred (touch or gesture)
 */
uint8_t touchpad_get_event_state ( touchpad_t *ctx );

/**
 * @brief Gesture type
 *
 * @param ctx          Click object.
 * @return Gesture type
 *
 * @note Gesture type options:
 * <pre>
 *      - NO_GESTURE_PRESENT
 *      - SINGLE_CLICK
 *      - CLICK_AND_HOLD
 *      - DOUBLE_CLICK
 *      - DOWN_SWIPE
 *      - DOWN_SWIPE_AND_HOLD
 *      - RIGHT_SWIPE
 *      - RIGHT_SWIPE_AND_HOLD
 *      - UP_SWIPE
 *      - UP_SWIPE_AND_HOLD
 *      - LEFT_SWIPE
 *      - LEFT_SWIPE_AND_HOLD
 * </pre>
 */
uint8_t touchpad_get_gesture_type ( touchpad_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TOUCHPAD_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
