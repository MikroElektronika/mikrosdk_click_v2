/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file capslider3.h
 * @brief This file contains API for Cap Slider 3 Click Driver.
 */

#ifndef CAPSLIDER3_H
#define CAPSLIDER3_H

#ifdef __cplusplus
extern "C"{
#endif

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

/*!
 * @addtogroup capslider3 Cap Slider 3 Click Driver
 * @brief API for configuring and manipulating Cap Slider 3 Click driver.
 * @{
 */

/**
 * @defgroup capslider3_reg Cap Slider 3 Registers List
 * @brief List of registers of Cap Slider 3 Click driver.
 */

/**
 * @addtogroup capslider3_reg
 * @{
 */

/**
 * @brief Cap Slider 3 register list.
 * @details Specified register list of Cap Slider 3 Click driver.
 */
#define CAPSLIDER3_REG_PROD_NUM                             0x00
#define CAPSLIDER3_REG_MAJOR_VERSION_NUM                    0x01
#define CAPSLIDER3_REG_MINOR_VERSION_NUM                    0x02
#define CAPSLIDER3_REG_SYSTEM_STATUS                        0x10
#define CAPSLIDER3_REG_GESTURES                             0x11
#define CAPSLIDER3_REG_SLIDER                               0x12
#define CAPSLIDER3_REG_CH0_COUNTS                           0x13
#define CAPSLIDER3_REG_CH0_LTA                              0x14
#define CAPSLIDER3_REG_CH1_COUNTS                           0x15
#define CAPSLIDER3_REG_CH1_LTA                              0x16
#define CAPSLIDER3_REG_CH2_COUNTS                           0x17
#define CAPSLIDER3_REG_CH2_LTA                              0x18
#define CAPSLIDER3_REG_CH0_ACT_MOVE_LTA                     0x20
#define CAPSLIDER3_REG_CH1_ACT_MOVE_LTA                     0x21
#define CAPSLIDER3_REG_CH2_ACT_MOVE_LTA                     0x22
#define CAPSLIDER3_REG_CH0_DELTA_SNAP                       0x23
#define CAPSLIDER3_REG_CH1_DELTA_SNAP                       0x24
#define CAPSLIDER3_REG_CH2_DELTA_SNAP                       0x25
#define CAPSLIDER3_REG_S0_SETUP_0                           0x30
#define CAPSLIDER3_REG_S0_CONV_FREQ_SETUP                   0x31
#define CAPSLIDER3_REG_S0_PROX_CONTROL                      0x32
#define CAPSLIDER3_REG_S0_PROX_INPUT_CONTROL                0x33
#define CAPSLIDER3_REG_S0_PATTERN_DEFINITIONS               0x34
#define CAPSLIDER3_REG_S0_PATTERN_SELECT                    0x35
#define CAPSLIDER3_REG_S0_ATI_SETUP                         0x36
#define CAPSLIDER3_REG_S0_ATI_BASE                          0x37
#define CAPSLIDER3_REG_S0_ATI_MULTI_SELECTION               0x38
#define CAPSLIDER3_REG_S0_COMPENSATION                      0x39
#define CAPSLIDER3_REG_S1_SETUP_0                           0x40
#define CAPSLIDER3_REG_S1_CONV_FREQ_SETUP                   0x41
#define CAPSLIDER3_REG_S1_PROX_CONTROL                      0x42
#define CAPSLIDER3_REG_S1_PROX_INPUT_CONTROL                0x43
#define CAPSLIDER3_REG_S1_PATTERN_DEFINITIONS               0x44
#define CAPSLIDER3_REG_S1_PATTERN_SELECT                    0x45
#define CAPSLIDER3_REG_S1_ATI_SETUP                         0x46
#define CAPSLIDER3_REG_S1_ATI_BASE                          0x47
#define CAPSLIDER3_REG_S1_ATI_MULTI_SELECTION               0x48
#define CAPSLIDER3_REG_S1_COMPENSATION                      0x49
#define CAPSLIDER3_REG_S2_SETUP_0                           0x50
#define CAPSLIDER3_REG_S2_CONV_FREQ_SETUP                   0x51
#define CAPSLIDER3_REG_S2_PROX_CONTROL                      0x52
#define CAPSLIDER3_REG_S2_PROX_INPUT_CONTROL                0x53
#define CAPSLIDER3_REG_S2_PATTERN_DEFINITIONS               0x54
#define CAPSLIDER3_REG_S2_PATTERN_SELECT                    0x55
#define CAPSLIDER3_REG_S2_ATI_SETUP                         0x56
#define CAPSLIDER3_REG_S2_ATI_BASE                          0x57
#define CAPSLIDER3_REG_S2_ATI_MULTI_SELECTION               0x58
#define CAPSLIDER3_REG_S2_COMPENSATION                      0x59
#define CAPSLIDER3_REG_CH0_SETUP_0                          0x60
#define CAPSLIDER3_REG_CH0_PROX_SETTINGS                    0x61
#define CAPSLIDER3_REG_CH0_TOUCH_SETTINGS                   0x62
#define CAPSLIDER3_REG_CH0_FOLLOWER_WEIGHT                  0x63
#define CAPSLIDER3_REG_CH0_MOVEMENT_UI                      0x64
#define CAPSLIDER3_REG_CH1_SETUP_0                          0x70
#define CAPSLIDER3_REG_CH1_PROX_SETTINGS                    0x71
#define CAPSLIDER3_REG_CH1_TOUCH_SETTINGS                   0x72
#define CAPSLIDER3_REG_CH1_FOLLOWER_WEIGHT                  0x73
#define CAPSLIDER3_REG_CH1_MOVEMENT_UI                      0x74
#define CAPSLIDER3_REG_CH2_SETUP_0                          0x80
#define CAPSLIDER3_REG_CH2_PROX_SETTINGS                    0x81
#define CAPSLIDER3_REG_CH2_TOUCH_SETTINGS                   0x82
#define CAPSLIDER3_REG_CH2_FOLLOWER_WEIGHT                  0x83
#define CAPSLIDER3_REG_CH2_MOVEMENT_UI                      0x84
#define CAPSLIDER3_REG_SLIDER_SETUP_CALIBRATION             0x90
#define CAPSLIDER3_REG_SLIDER_CALIBRATION_BOT_SPEED         0x91
#define CAPSLIDER3_REG_SLIDER_TOP_SPEED                     0x92
#define CAPSLIDER3_REG_SLIDER_RESOLUTION                    0x93
#define CAPSLIDER3_REG_SLIDER_EN_MASK                       0x94
#define CAPSLIDER3_REG_SLIDER_EN_STATUS_POINTER             0x95
#define CAPSLIDER3_REG_SLIDER_DELTA_LINK_0                  0x96
#define CAPSLIDER3_REG_SLIDER_DELTA_LINK_1                  0x97
#define CAPSLIDER3_REG_SLIDER_DELTA_LINK_2                  0x98
#define CAPSLIDER3_REG_GESTURE_ENABLE                       0xA0
#define CAPSLIDER3_REG_GESTURE_MINIMUM_TIME                 0xA1
#define CAPSLIDER3_REG_GESTURE_MAX_TAP_TIME                 0xA2
#define CAPSLIDER3_REG_GESTURE_MAX_SWIPE_TIME               0xA3
#define CAPSLIDER3_REG_GESTURE_MIN_HOLD_TIME                0xA4
#define CAPSLIDER3_REG_GESTURE_MAX_TAP_DISTANCE             0xA5
#define CAPSLIDER3_REG_GESTURE_MIN_SWIPE_DISTANCE           0xA6
#define CAPSLIDER3_REG_COUNTS_FILTER_BETA                   0xB0
#define CAPSLIDER3_REG_LTA_FILTER_BETA                      0xB1
#define CAPSLIDER3_REG_LTA_FAST_FILTER_BETA                 0xB2
#define CAPSLIDER3_REG_ACT_MOVE_LTA_FILTER_BETA             0xB3
#define CAPSLIDER3_REG_FAST_FILTER_BAND                     0xB4
#define CAPSLIDER3_REG_SYSTEM_CONTROL                       0xC0
#define CAPSLIDER3_REG_NORMAL_POWER_REPORT_RATE             0xC1
#define CAPSLIDER3_REG_LOW_POWER_REPORT_RATE                0xC2
#define CAPSLIDER3_REG_ULP_REPORT_RATE                      0xC3
#define CAPSLIDER3_REG_HALT_MODE_REPORT_RATE                0xC4
#define CAPSLIDER3_REG_POWER_MODE_TIMEOUT                   0xC5
#define CAPSLIDER3_REG_OUTA_MASK                            0xD0
#define CAPSLIDER3_REG_I2C_TRANS_TIMEOUT                    0xD1
#define CAPSLIDER3_REG_EVENT_TIMEOUTS                       0xD2
#define CAPSLIDER3_REG_EVENT_EN_ACTIVATION_THRESHOLD        0xD3
#define CAPSLIDER3_REG_RELEASE_UI_MOVE_TIMEOUT              0xD4
#define CAPSLIDER3_REG_I2C_SETUP                            0xE0
#define CAPSLIDER3_REG_HARDWARE_ID                          0xE1

/*! @} */ // capslider3_reg

/**
 * @defgroup capslider3_set Cap Slider 3 Registers Settings
 * @brief Settings for registers of Cap Slider 3 Click driver.
 */

/**
 * @addtogroup capslider3_set
 * @{
 */

/**
 * @brief Cap Slider 3 GESTURES register setting.
 * @details Specified setting for GESTURES register of Cap Slider 3 Click driver.
 */
#define CAPSLIDER3_GESTURES_BUSY                            0x0080
#define CAPSLIDER3_GESTURES_EVENT                           0x0040
#define CAPSLIDER3_GESTURES_HOLD                            0x0020
#define CAPSLIDER3_GESTURES_FLICK_NEG                       0x0010
#define CAPSLIDER3_GESTURES_FLICK_POS                       0x0008
#define CAPSLIDER3_GESTURES_SWIPE_NEG                       0x0004
#define CAPSLIDER3_GESTURES_SWIPE_POS                       0x0002
#define CAPSLIDER3_GESTURES_TAP                             0x0001

/**
 * @brief Cap Slider 3 SYSTEM_STATUS register setting.
 * @details Specified setting for SYSTEM_STATUS register of Cap Slider 3 Click driver.
 */
#define CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_NORMAL          0x0000
#define CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_LP              0x4000
#define CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_ULP             0x8000
#define CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_HALT            0xC000
#define CAPSLIDER3_SYSTEM_STATUS_POWER_MODE_MASK            0xC000
#define CAPSLIDER3_SYSTEM_STATUS_CH2_TOUCH                  0x2000
#define CAPSLIDER3_SYSTEM_STATUS_CH2_PROX                   0x1000
#define CAPSLIDER3_SYSTEM_STATUS_CH1_TOUCH                  0x0800
#define CAPSLIDER3_SYSTEM_STATUS_CH1_PROX                   0x0400
#define CAPSLIDER3_SYSTEM_STATUS_CH0_TOUCH                  0x0200
#define CAPSLIDER3_SYSTEM_STATUS_CH0_PROX                   0x0100
#define CAPSLIDER3_SYSTEM_STATUS_RESET_EVENT                0x0080
#define CAPSLIDER3_SYSTEM_STATUS_ATI_ERROR                  0x0040
#define CAPSLIDER3_SYSTEM_STATUS_ATI_ACTIVE                 0x0020
#define CAPSLIDER3_SYSTEM_STATUS_ATI_EVENT                  0x0010
#define CAPSLIDER3_SYSTEM_STATUS_POWER_EVENT                0x0008
#define CAPSLIDER3_SYSTEM_STATUS_SLIDER_EVENT               0x0004
#define CAPSLIDER3_SYSTEM_STATUS_TOUCH_EVENT                0x0002
#define CAPSLIDER3_SYSTEM_STATUS_PROX_EVENT                 0x0001

/**
 * @brief Cap Slider 3 SYSTEM_CONTROL register setting.
 * @details Specified setting for SYSTEM_CONTROL register of Cap Slider 3 Click driver.
 */
#define CAPSLIDER3_SYSTEM_CONTROL_CH2_TIMEOUT_EN            0x0000
#define CAPSLIDER3_SYSTEM_CONTROL_CH2_TIMEOUT_DIS           0x0400
#define CAPSLIDER3_SYSTEM_CONTROL_CH2_TIMEOUT_MASK          0x0400
#define CAPSLIDER3_SYSTEM_CONTROL_CH1_TIMEOUT_EN            0x0000
#define CAPSLIDER3_SYSTEM_CONTROL_CH1_TIMEOUT_DIS           0x0200
#define CAPSLIDER3_SYSTEM_CONTROL_CH1_TIMEOUT_MASK          0x0200
#define CAPSLIDER3_SYSTEM_CONTROL_CH0_TIMEOUT_EN            0x0000
#define CAPSLIDER3_SYSTEM_CONTROL_CH0_TIMEOUT_DIS           0x0100
#define CAPSLIDER3_SYSTEM_CONTROL_CH0_TIMEOUT_MASK          0x0100
#define CAPSLIDER3_SYSTEM_CONTROL_IF_TYPE_STREAM            0x0000
#define CAPSLIDER3_SYSTEM_CONTROL_IF_TYPE_EVENT             0x0080
#define CAPSLIDER3_SYSTEM_CONTROL_IF_TYPE_MASK              0x0080
#define CAPSLIDER3_SYSTEM_CONTROL_POWER_MODE_NORMAL         0x0000
#define CAPSLIDER3_SYSTEM_CONTROL_POWER_MODE_LP             0x0010
#define CAPSLIDER3_SYSTEM_CONTROL_POWER_MODE_ULP            0x0020
#define CAPSLIDER3_SYSTEM_CONTROL_POWER_MODE_HALT           0x0030
#define CAPSLIDER3_SYSTEM_CONTROL_POWER_MODE_AUTO           0x0040
#define CAPSLIDER3_SYSTEM_CONTROL_POWER_MODE_AUTO_NO_ULP    0x0050
#define CAPSLIDER3_SYSTEM_CONTROL_POWER_MODE_MASK           0x0070
#define CAPSLIDER3_SYSTEM_CONTROL_RESEED_IDLE               0x0000
#define CAPSLIDER3_SYSTEM_CONTROL_RESEED_TRIGGER            0x0008
#define CAPSLIDER3_SYSTEM_CONTROL_RESEED_MASK               0x0008
#define CAPSLIDER3_SYSTEM_CONTROL_RE_ATI_IDLE               0x0000
#define CAPSLIDER3_SYSTEM_CONTROL_RE_ATI_TRIGGER            0x0004
#define CAPSLIDER3_SYSTEM_CONTROL_RE_ATI_MASK               0x0004
#define CAPSLIDER3_SYSTEM_CONTROL_SOFT_RESET_IDLE           0x0000
#define CAPSLIDER3_SYSTEM_CONTROL_SOFT_RESET_TRIGGER        0x0002
#define CAPSLIDER3_SYSTEM_CONTROL_SOFT_RESET_MASK           0x0002
#define CAPSLIDER3_SYSTEM_CONTROL_ACK_RESET_NACK            0x0000
#define CAPSLIDER3_SYSTEM_CONTROL_ACK_RESET_ACK             0x0001
#define CAPSLIDER3_SYSTEM_CONTROL_ACK_RESET_MASK            0x0001

/**
 * @brief Cap Slider 3 SLIDER register setting.
 * @details Specified setting for SLIDER register of Cap Slider 3 Click driver.
 */
#define CAPSLIDER3_SLIDER_MAX                               2048
#define CAPSLIDER3_SLIDER_MIN                               0
#define CAPSLIDER3_SLIDER_IDLE                              65535

/**
 * @brief Cap Slider 3 default slider settings.
 * @details Specified default slider settings of Cap Slider 3 Click driver.
 */
#define CAPSLIDER3_S0_SETUP_0                               0x0201
#define CAPSLIDER3_S0_CONV_FREQ_SETUP                       0x057F
#define CAPSLIDER3_S0_PROX_CONTROL                          0x1290
#define CAPSLIDER3_S0_PROX_INPUT_CONTROL                    0x02CF
#define CAPSLIDER3_S0_PATTERN_DEFINITIONS                   0x030A
#define CAPSLIDER3_S0_PATTERN_SELECT                        0x0000
#define CAPSLIDER3_S0_ATI_SETUP                             0x03CC
#define CAPSLIDER3_S0_ATI_BASE                              0x0096
#define CAPSLIDER3_S0_ATI_MULTI_SELECTION                   0x5644
#define CAPSLIDER3_S0_COMPENSATION                          0xA3EC
#define CAPSLIDER3_S1_SETUP_0                               0x0101
#define CAPSLIDER3_S1_CONV_FREQ_SETUP                       0x057F
#define CAPSLIDER3_S1_PROX_CONTROL                          0x1290
#define CAPSLIDER3_S1_PROX_INPUT_CONTROL                    0x01CF
#define CAPSLIDER3_S1_PATTERN_DEFINITIONS                   0x030A
#define CAPSLIDER3_S1_PATTERN_SELECT                        0x0000
#define CAPSLIDER3_S1_ATI_SETUP                             0x03CC
#define CAPSLIDER3_S1_ATI_BASE                              0x0096
#define CAPSLIDER3_S1_ATI_MULTI_SELECTION                   0x5E44
#define CAPSLIDER3_S1_COMPENSATION                          0xA3DC
#define CAPSLIDER3_S2_SETUP_0                               0x0401
#define CAPSLIDER3_S2_CONV_FREQ_SETUP                       0x057F
#define CAPSLIDER3_S2_PROX_CONTROL                          0x1290
#define CAPSLIDER3_S2_PROX_INPUT_CONTROL                    0x04CF
#define CAPSLIDER3_S2_PATTERN_DEFINITIONS                   0x030A
#define CAPSLIDER3_S2_PATTERN_SELECT                        0x0000
#define CAPSLIDER3_S2_ATI_SETUP                             0x03CC
#define CAPSLIDER3_S2_ATI_BASE                              0x0096
#define CAPSLIDER3_S2_ATI_MULTI_SELECTION                   0x5844
#define CAPSLIDER3_S2_COMPENSATION                          0xABFB
#define CAPSLIDER3_CH0_SETUP_0                              0x0000
#define CAPSLIDER3_CH0_PROX_SETTINGS                        0x440A
#define CAPSLIDER3_CH0_TOUCH_SETTINGS                       0x000F
#define CAPSLIDER3_CH0_FOLLOWER_WEIGHT                      0x0000
#define CAPSLIDER3_CH1_SETUP_0                              0x0000
#define CAPSLIDER3_CH1_PROX_SETTINGS                        0x440A
#define CAPSLIDER3_CH1_TOUCH_SETTINGS                       0x000F
#define CAPSLIDER3_CH1_FOLLOWER_WEIGHT                      0x0000
#define CAPSLIDER3_CH2_SETUP_0                              0x0000
#define CAPSLIDER3_CH2_PROX_SETTINGS                        0x440A
#define CAPSLIDER3_CH2_TOUCH_SETTINGS                       0x000F
#define CAPSLIDER3_CH2_FOLLOWER_WEIGHT                      0x0000
#define CAPSLIDER3_SLIDER_SETUP_CALIBRATION                 0x000B
#define CAPSLIDER3_SLIDER_CALIBRATION_BOT_SPEED             0x1400
#define CAPSLIDER3_SLIDER_TOP_SPEED                         0x00C8
#define CAPSLIDER3_SLIDER_RESOLUTION                        0x0800
#define CAPSLIDER3_SLIDER_EN_MASK                           0x0007
#define CAPSLIDER3_SLIDER_EN_STATUS_POINTER                 0x0552
#define CAPSLIDER3_SLIDER_DELTA_LINK_0                      0x0430
#define CAPSLIDER3_SLIDER_DELTA_LINK_1                      0x0472
#define CAPSLIDER3_SLIDER_DELTA_LINK_2                      0x04B4
#define CAPSLIDER3_GESTURE_ENABLE                           0x000F
#define CAPSLIDER3_GESTURE_MINIMUM_TIME                     0x000A
#define CAPSLIDER3_GESTURE_MAX_TAP_TIME                     0x00C8
#define CAPSLIDER3_GESTURE_MAX_SWIPE_TIME                   0x012C
#define CAPSLIDER3_GESTURE_MIN_HOLD_TIME                    0x012C
#define CAPSLIDER3_GESTURE_MAX_TAP_DISTANCE                 0x00C8
#define CAPSLIDER3_GESTURE_MIN_SWIPE_DISTANCE               0x028A
#define CAPSLIDER3_COUNTS_FILTER_BETA                       0x0102
#define CAPSLIDER3_LTA_FILTER_BETA                          0x0708
#define CAPSLIDER3_LTA_FAST_FILTER_BETA                     0x0304
#define CAPSLIDER3_ACT_MOVE_LTA_FILTER_BETA                 0x0000
#define CAPSLIDER3_FAST_FILTER_BAND                         0x000F
#define CAPSLIDER3_SYSTEM_CONTROL                           0x0050
#define CAPSLIDER3_NORMAL_POWER_REPORT_RATE                 0x0010
#define CAPSLIDER3_LOW_POWER_REPORT_RATE                    0x003C
#define CAPSLIDER3_ULP_REPORT_RATE                          0x00A0
#define CAPSLIDER3_HALT_MODE_REPORT_RATE                    0x0BB8
#define CAPSLIDER3_POWER_MODE_TIMEOUT                       0x07D0
#define CAPSLIDER3_OUTA_MASK                                0x0080
#define CAPSLIDER3_I2C_TRANS_TIMEOUT                        0x00C8
#define CAPSLIDER3_EVENT_TIMEOUTS                           0x0000
#define CAPSLIDER3_EVENT_EN_ACTIVATION_THRESHOLD            0x000F
#define CAPSLIDER3_RELEASE_UI_MOVE_TIMEOUT                  0x0000

/**
 * @brief Cap Slider 3 device ID setting.
 * @details Specified setting for device ID of Cap Slider 3 Click driver.
 */
#define CAPSLIDER3_PRODUCT_NUM                              1106

/**
 * @brief Cap Slider 3 communication window timeout setting.
 * @details Specified setting for communication window timeout of Cap Slider 3 Click driver.
 */
#define CAPSLIDER3_RDY_TIMEOUT                              5000

/**
 * @brief Cap Slider 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Cap Slider 3 Click driver.
 */
#define CAPSLIDER3_DEVICE_ADDRESS                           0x44
#define CAPSLIDER3_DEVICE_ADDRESS_DEBUG                     0x45

/*! @} */ // capslider3_set

/**
 * @defgroup capslider3_map Cap Slider 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Cap Slider 3 Click driver.
 */

/**
 * @addtogroup capslider3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Cap Slider 3 Click to the selected MikroBUS.
 */
#define CAPSLIDER3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // capslider3_map
/*! @} */ // capslider3

/**
 * @brief Cap Slider 3 Click data object object.
 * @details Data object definition of Cap Slider 3 Click driver.
 */
typedef struct
{
    uint16_t sys_status;        /** Systems status. */
    uint16_t gestures;          /** Gesture status. */
    uint16_t slider;            /** Slider position value. */
    uint16_t ch0_counts;        /** Channel 0 filtered counts. */
    uint16_t ch0_lta;           /** Channel 0 long-term average. */
    uint16_t ch1_counts;        /** Channel 1 filtered counts. */
    uint16_t ch1_lta;           /** Channel 1 long-term average. */
    uint16_t ch2_counts;        /** Channel 2 filtered counts. */
    uint16_t ch2_lta;           /** Channel 2 long-term average. */

} capslider3_data_t;

/**
 * @brief Cap Slider 3 Click context object.
 * @details Context object definition of Cap Slider 3 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t rdy;           /**< Ready pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} capslider3_t;

/**
 * @brief Cap Slider 3 Click configuration object.
 * @details Configuration object definition of Cap Slider 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rdy;             /**< Ready pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} capslider3_cfg_t;

/**
 * @brief Cap Slider 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CAPSLIDER3_OK = 0,
    CAPSLIDER3_ERROR = -1

} capslider3_return_value_t;

/*!
 * @addtogroup capslider3 Cap Slider 3 Click Driver
 * @brief API for configuring and manipulating Cap Slider 3 Click driver.
 * @{
 */

/**
 * @brief Cap Slider 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #capslider3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void capslider3_cfg_setup ( capslider3_cfg_t *cfg );

/**
 * @brief Cap Slider 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #capslider3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t capslider3_init ( capslider3_t *ctx, capslider3_cfg_t *cfg );

/**
 * @brief Cap Slider 3 default configuration function.
 * @details This function executes a default configuration of Cap Slider 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t capslider3_default_cfg ( capslider3_t *ctx );

/**
 * @brief Cap Slider 3 write register function.
 * @details This function writes a 16-bit data to the specified register.
 * @param[in] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success, 
 *         @li @c -1 - Error.
 * @note None.
 */
err_t capslider3_write_reg ( capslider3_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Cap Slider 3 write registers function.
 * @details This function writes multiple 16-bit data to consecutive registers starting from the specified register address.
 * @param[in] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @param[in] reg : Starting register address.
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of 16-bit data entries to write.
 * @return @li @c  0 - Success, 
 *         @li @c -1 - Error.
 * @note None.
 */
err_t capslider3_write_regs ( capslider3_t *ctx, uint8_t reg, uint16_t *data_in, uint8_t len );

/**
 * @brief Cap Slider 3 read register function.
 * @details This function reads a 16-bit data from the specified register.
 * @param[in] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to a memory location where read data will be stored.
 * @return @li @c  0 - Success, 
 *         @li @c -1 - Error.
 * @note None.
 */
err_t capslider3_read_reg ( capslider3_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Cap Slider 3 read registers function.
 * @details This function reads multiple 16-bit data from consecutive registers starting from the specified register address.
 * @param[in] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @param[in] reg : Starting register address.
 * @param[out] data_out : Pointer to a memory location where read data will be stored.
 * @param[in] len : Number of 16-bit data entries to read.
 * @return @li @c  0 - Success, 
 *         @li @c -1 - Error.
 * @note None.
 */
err_t capslider3_read_regs ( capslider3_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len );

/**
 * @brief Cap Slider 3 get ready pin function.
 * @details This function reads the state of the RDY pin.
 * @param[in] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @return Pin logic state (0 or 1).
 * @note None.
 */
uint8_t capslider3_get_rdy_pin ( capslider3_t *ctx );

/**
 * @brief Cap Slider 3 check communication function.
 * @details This function checks the communication by reading the product number register.
 * @param[in] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @return @li @c  0 - Success, 
 *         @li @c -1 - Error.
 * @note None.
 */
err_t capslider3_check_communication ( capslider3_t *ctx );

/**
 * @brief Cap Slider 3 software reset function.
 * @details This function performs a software reset by modifying the system control register.
 * @param[in] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @return @li @c  0 - Success, 
 *         @li @c -1 - Error.
 * @note This function ensures reset acknowledgment before proceeding.
 */
err_t capslider3_sw_reset ( capslider3_t *ctx );

/**
 * @brief Cap Slider 3 read data function.
 * @details This function reads various system information and sensor data from the Click board.
 * @param[in] ctx : Click context object.
 * See #capslider3_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the structure where read data will be stored.
 * See #capslider3_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success, 
 *         @li @c -1 - Error.
 * @note None.
 */
err_t capslider3_read_data ( capslider3_t *ctx, capslider3_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // CAPSLIDER3_H

/*! @} */ // capslider3

// ------------------------------------------------------------------------ END
