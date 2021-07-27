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
 * @file touchpad4.h
 * @brief This file contains API for Touchpad 4 Click Driver.
 */

#ifndef TOUCHPAD4_H
#define TOUCHPAD4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup touchpad4 Touchpad 4 Click Driver
 * @brief API for configuring and manipulating Touchpad 4 Click driver.
 * @{
 */

/**
 * @defgroup touchpad4_reg Touchpad 4 Registers List
 * @brief List of registers of Touchpad 4 Click driver.
 */

/**
 * @addtogroup touchpad4_reg
 * @{
 */

/**
 * @brief Touchpad 4 description register.
 * @details Specified register for description of Touchpad 4 Click driver.
 */
#define TOUCHPAD4_REG_INFO_FLAGS                            0x10
#define TOUCHPAD4_REG_GESTURES                              0x11
#define TOUCHPAD4_REG_RELATIVE_X                            0x12
#define TOUCHPAD4_REG_RELATIVE_Y                            0x13
#define TOUCHPAD4_REG_FINGER1_X                             0x14
#define TOUCHPAD4_REG_FINGER1_Y                             0x15
#define TOUCHPAD4_REG_FINGER1_TOUCH_STR                     0x16
#define TOUCHPAD4_REG_FINGER1_AREA                          0x17
#define TOUCHPAD4_REG_FINGER2_X                             0x18
#define TOUCHPAD4_REG_FINGER2_Y                             0x19
#define TOUCHPAD4_REG_FINGER2_TOUCH_STR                     0x1A
#define TOUCHPAD4_REG_FINGER2_AREA                          0x1B
#define TOUCHPAD4_REG_TOUCH_STATUS0                         0x20
#define TOUCHPAD4_REG_TOUCH_STATUS1                         0x21
#define TOUCHPAD4_REG_TOUCH_STATUS2                         0x22
#define TOUCHPAD4_REG_ALP_CHANNEL_COUNT                     0x23
#define TOUCHPAD4_REG_ALP_CHANNEL_LTA                       0x24
#define TOUCHPAD4_REG_ALP_COUNT_A                           0x25
#define TOUCHPAD4_REG_ALP_COUNT_B                           0x26
#define TOUCHPAD4_REG_TRACKPAD_ATI_MULT_DIV                 0x30
#define TOUCHPAD4_REG_TRACKPAD_ATI_COMP_DIV                 0x31
#define TOUCHPAD4_REG_TRACKPAD_ATI_TARGET                   0x32
#define TOUCHPAD4_REG_TRACKPAD_REF_DRIFT_LIMIT              0x33
#define TOUCHPAD4_REG_TRACKPAD_MIN_CNT_REATI_VAL            0x34
#define TOUCHPAD4_REG_REATI_RETRY_TIME                      0x35
#define TOUCHPAD4_REG_ALP_ATI_MULT_DIV                      0x36
#define TOUCHPAD4_REG_ALP_ATI_COMP_DIV                      0x37
#define TOUCHPAD4_REG_ALP_ATI_TARGET                        0x38
#define TOUCHPAD4_REG_ALP_ATI_DRIFT_LIMIT                   0x39
#define TOUCHPAD4_REG_ALP_ATI_COMP_A                        0x3A
#define TOUCHPAD4_REG_ALP_ATI_COMP_B                        0x3B
#define TOUCHPAD4_REG_ACTIVE_MODE_REPORT_RATE               0x40
#define TOUCHPAD4_REG_IDLE_TOUCH_MODE_REPORT_RATE           0x41
#define TOUCHPAD4_REG_IDLE_MODE_REPORT_RATE                 0x42
#define TOUCHPAD4_REG_LP1_MODE_REPORT_RATE                  0x43
#define TOUCHPAD4_REG_LP2_MODE_REPORT_RATE                  0x44
#define TOUCHPAD4_REG_ACTIVE_MODE_TIMEOUT                   0x45
#define TOUCHPAD4_REG_IDLE_TOUCH_MODE_TIMEOUT               0x46
#define TOUCHPAD4_REG_IDLE_MODE_TIMEOUT                     0x47
#define TOUCHPAD4_REG_LP1_MODE_TIMEOUT                      0x48
#define TOUCHPAD4_REG_REFERENCE_UPDATE_TIME                 0x49
#define TOUCHPAD4_REG_I2C_TIMEOUT                           0x4A
#define TOUCHPAD4_REG_SYSTEM_CONTROL                        0x50
#define TOUCHPAD4_REG_CONFIG_SETTINGS                       0x51
#define TOUCHPAD4_REG_OTHER_SETTINGS                        0x52
#define TOUCHPAD4_REG_TOUCH_CLEAR_SET_THRESH                0x53
#define TOUCHPAD4_REG_ALP_THRESH                            0x54
#define TOUCHPAD4_REG_ALP_CLEAR_SET_DEBOUNCE                0x56
#define TOUCHPAD4_REG_TRACKPAD_CONVER_FREQ                  0x58
#define TOUCHPAD4_REG_ALP_CONVER_FREQ                       0x59
#define TOUCHPAD4_REG_TRACKPAD_HW_SETTINGS                  0x5A
#define TOUCHPAD4_REG_ALP_HW_SETTINGS                       0x5B
#define TOUCHPAD4_REG_TOTAL_RXS_TRACKPAD_SETTINGS           0x60
#define TOUCHPAD4_REG_MAX_MULTITOUCHES_TOTAL_TXS            0x61
#define TOUCHPAD4_REG_X_RES                                 0x62
#define TOUCHPAD4_REG_Y_RES                                 0x63
#define TOUCHPAD4_REG_XY_DYNAMIC_FILTER_BOT_SPEED           0x64
#define TOUCHPAD4_REG_XY_DYNAMIC_FILTER_TOP_SPEED           0x65
#define TOUCHPAD4_REG_STATIC_FILTER_VAL_DYNAMIC_FILTER_BOT  0x66
#define TOUCHPAD4_REG_FINGER_SPLIT_STAT_TOUCH_MOVE_THRESH   0x67
#define TOUCHPAD4_REG_X_TRIM_VALUE                          0x68
#define TOUCHPAD4_REG_Y_TRIM_VALUE                          0x69
#define TOUCHPAD4_REG_ALP_COUNT_FILTER_BETA                 0x70
#define TOUCHPAD4_REG_LP2_LP1_BETA                          0x71
#define TOUCHPAD4_REG_ALP_SETUP                             0x72
#define TOUCHPAD4_REG_ALP_TX_ENABLE                         0x73
#define TOUCHPAD4_REG_SETTINGS_MAJOR_MINOR_VER              0x74
#define TOUCHPAD4_REG_GESTURE_ENABLE                        0x80
#define TOUCHPAD4_REG_TAP_TIME                              0x81
#define TOUCHPAD4_REG_TAP_DIST                              0x82
#define TOUCHPAD4_REG_HOLD_TIME                             0x83
#define TOUCHPAD4_REG_SWIPE_TIME                            0x84
#define TOUCHPAD4_REG_SWIPE_X_DIST                          0x85
#define TOUCHPAD4_REG_SWIPE_Y_DIST                          0x86
#define TOUCHPAD4_REG_SWIPE_ANGLE                           0x87
#define TOUCHPAD4_REG_RXTX_MAP_1_0                          0x90
#define TOUCHPAD4_REG_RXTX_MAP_3_2                          0x91
#define TOUCHPAD4_REG_RXTX_MAP_5_4                          0x92
#define TOUCHPAD4_REG_RXTX_MAP_7_6                          0x93
#define TOUCHPAD4_REG_RXTX_MAP_9_8                          0x94
#define TOUCHPAD4_REG_RXTX_MAP_11_10                        0x95
#define TOUCHPAD4_REG_RXTX_MAP_13_12                        0x96
#define TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE0                0xA0
#define TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE0                0xA1
#define TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE1             0xA2
#define TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE2                0xA3
#define TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE2                0xA4
#define TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE3             0xA5
#define TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE4                0xA6
#define TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE4                0xA7
#define TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE5             0xA8
#define TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE6                0xA9
#define TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE6                0xAA
#define TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE7             0xAB
#define TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE8                0xAC
#define TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE8                0xAD
#define TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE9             0xAE
#define TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE10               0xB0
#define TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE10               0xB1
#define TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE11            0xB2
#define TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE12               0xB3
#define TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE12               0xB4
#define TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE13            0xB5
#define TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE14               0xB6
#define TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE14               0xB7
#define TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE15            0xB8
#define TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE16               0xB9
#define TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE16               0xBA
#define TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE17            0xBB
#define TOUCHPAD4_REG_TRACKPAD_COUNT_VAL                    0xE0
#define TOUCHPAD4_REG_TRACKPAD_REF_VAL                      0xE1
#define TOUCHPAD4_REG_TRACKPAD_DELTA_VAL                    0xE2
#define TOUCHPAD4_REG_TRACKPAD_ATI_COMPENSATION_VAL         0xE3


/*! @} */ // touchpad4_reg

/**
 * @defgroup touchpad4_set Touchpad 4 Registers Settings
 * @brief Settings for registers of Touchpad 4 Click driver.
 */

/**
 * @addtogroup touchpad4_set
 * @{
 */

/**
 * @brief Touchpad 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Touchpad 4 Click driver.
 */
#define TOUCHPAD4_SET_DEV_ADDR  0x56

/*! @} */ // touchpad4_set

/**
 * @defgroup touchpad4_map Touchpad 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Touchpad 4 Click driver.
 */

/**
 * @addtogroup touchpad4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Touchpad 4 Click to the selected MikroBUS.
 */
#define TOUCHPAD4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.mclr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // touchpad4_map
/*! @} */ // touchpad4

/**
 * @brief Touchpad 4 Click context object.
 * @details Context object definition of Touchpad 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mclr;      /**< Reset. */
    
    // Input pins
    digital_in_t  rdy;      /**< Ready. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    uint8_t event_enabled;

} touchpad4_t;

/**
 * @brief Touchpad 4 Click configuration object.
 * @details Configuration object definition of Touchpad 4 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    
    pin_name_t  mclr;       /**< Reset. */
    pin_name_t  rdy;        /**< Ready. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} touchpad4_cfg_t;

/**
 * @brief Touchpad 4 Click touch object.
 * @details Touch parameters of Touchpad 4 Click driver.
 */
typedef struct
{
    int16_t x;          /**< X coordinate. */
    int16_t y;          /**< Y coordinate. */
    int16_t strength;   /**< Touch strength. */
    int16_t area;       /**< Touch area. */

} touchpad4_touch_t;

/**
 * @brief Touchpad 4 Click touchpad information object.
 * @details Information of touch state of Touchpad 4 Click driver.
 */
typedef struct
{
    uint8_t number_of_touches;      /**< Number of registered touches. */
    touchpad4_touch_t touches[ 4 ]; /**< Touch information. */

} touchpad4_info_t;

/**
 * @brief Touchpad 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   TOUCHPAD4_OK = 0,
   TOUCHPAD4_ERROR = -1

} touchpad4_return_value_t;

/*!
 * @addtogroup touchpad4 Touchpad 4 Click Driver
 * @brief API for configuring and manipulating Touchpad 4 Click driver.
 * @{
 */

/**
 * @brief Touchpad 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #touchpad4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void touchpad4_cfg_setup ( touchpad4_cfg_t *cfg );

/**
 * @brief Touchpad 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #touchpad4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #touchpad4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad4_init ( touchpad4_t *ctx, touchpad4_cfg_t *cfg );

/**
 * @brief Touchpad 4 default configuration function.
 * @details This function executes a default configuration of Touchpad 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #touchpad4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t touchpad4_default_cfg ( touchpad4_t *ctx );

/**
 * @brief Touchpad 4 I2C writing function.
 * @details This function writes a data to the selected register.
 * @param[in] ctx : Click context object.
 * See #touchpad4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t touchpad4_generic_write ( touchpad4_t *ctx, uint8_t reg, uint16_t tx_data );

/**
 * @brief Touchpad 4 I2C reading function.
 * @details This function reads a data from the selected register.
 * @param[in] ctx : Click context object.
 * See #touchpad4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t touchpad4_generic_read ( touchpad4_t *ctx, uint8_t reg, uint16_t *rx_data );

/**
 * @brief Get ready pin state.
 * @details This function reads logic state of the @b rdy pin.
 * @param[in] ctx : Click context object.
 * See #touchpad4_t object definition for detailed explanation.
 * @return Logic state of the pin.
 */
uint8_t touchpad4_get_ready ( touchpad4_t *ctx );

/**
 * @brief Reset function.
 * @details This function resets device.
 * @param[in] ctx : Click context object.
 * See #touchpad4_t object definition for detailed explanation.
 * @return Nothing.
 */
void touchpad4_reset ( touchpad4_t *ctx );

/**
 * @brief Read touch informations.
 * @details This function reads number of touches, touch informations and gesture.
 * @param[in] ctx : Click context object.
 * See #touchpad4_t object definition for detailed explanation.
 * @param[out] touch_info : Touch information object.
 * See #touchpad4_info_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t touchpad4_get_touch ( touchpad4_t *ctx, touchpad4_info_t *touch_info );

/**
 * @brief Read channel information.
 * @details This function reads state of the channels.
 * @param[in] ctx : Click context object.
 * See #touchpad4_t object definition for detailed explanation.
 * @param[out] channels : Channel data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t touchpad_get_channels ( touchpad4_t *ctx, uint32_t *channels );

#ifdef __cplusplus
}
#endif
#endif // TOUCHPAD4_H

/*! @} */ // touchpad4

// ------------------------------------------------------------------------ END
