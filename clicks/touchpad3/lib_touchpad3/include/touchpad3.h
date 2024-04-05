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
 * @file touchpad3.h
 * @brief This file contains API for Touchpad 3 Click Driver.
 */

#ifndef TOUCHPAD3_H
#define TOUCHPAD3_H

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
 * @addtogroup touchpad3 Touchpad 3 Click Driver
 * @brief API for configuring and manipulating Touchpad 3 Click driver.
 * @{
 */

/**
 * @defgroup touchpad3_reg Touchpad 3 Registers List
 * @brief List of registers of Touchpad 3 Click driver.
 */

/**
 * @addtogroup touchpad3_reg
 * @{
 */

/**
 * @brief Touchpad 3 description general registers index location.
 * @details Specified general registers index location for description of Touchpad 3 Click driver.
 */
#define TOUCHPAD3_GENERAL_INDEX_LOCATION                                    0x00

/**
 * @brief Touchpad 3 description general registers adresses.
 * @details Specified general registers adresses for description of Touchpad 3 Click driver.
 */
#define TOUCHPAD3_GENERAL_RX_CH_ADD                                         0x01
#define TOUCHPAD3_GENERAL_TX_CH_ADD                                         0x02
#define TOUCHPAD3_GENERAL_RX_SC_L_ADD                                       0x04
#define TOUCHPAD3_GENERAL_RX_SC_H_ADD                                       0x05
#define TOUCHPAD3_GENERAL_TX_SC_L_ADD                                       0x06
#define TOUCHPAD3_GENERAL_TX_SC_H_ADD                                       0x07

/**
 * @brief Touchpad 3 description general registers values.
 * @details Specified general registers values for description of Touchpad 3 Click driver.
 */

#define TOUCHPAD3_GENERAL_RX_CH                                             0x05
#define TOUCHPAD3_GENERAL_TX_CH                                             0x04
#define TOUCHPAD3_GENERAL_RX_SC_L                                           0x33
#define TOUCHPAD3_GENERAL_RX_SC_H                                           0x33
#define TOUCHPAD3_GENERAL_TX_SC_L                                           0x00
#define TOUCHPAD3_GENERAL_TX_SC_H                                           0x40

/**
 * @brief Touchpad 3 description decoding registers index location
 * @details Specified decoding registers index location for description of Touchpad 3 Click driver.
 */
#define TOUCHPAD3_DECODING_INDEX_LOCATION                                   0x30

/**
 * @brief Touchpad 3 description decoding registers adresses
 * @details Specified decoding registers adresses for description of Touchpad 3 Click driver.
 */
#define TOUCHPAD3_DEC_FLIP_STATE_ADD                                        0x00
#define TOUCHPAD3_DEC_NUM_AVG_ADD                                           0x01
#define TOUCHPAD3_DEC_MIN_TOUCH_DISTANCE_ADD                                0x04

/**
 * @brief Touchpad 3 description decoding registers values
 * @details Specified decoding registers values for description of Touchpad 3 Click driver.
 */
#define TOUCHPAD3_DEC_FLIP_STATE                                            0x04
#define TOUCHPAD3_DEC_NUM_AVG                                               0x08
#define TOUCHPAD3_DEC_MIN_TOUCH_DISTANCE                                    0x01

/*! @} */ // touchpad3_reg

/**
 * @defgroup touchpad3_set Touchpad 3 Registers Settings
 * @brief Settings for registers of Touchpad 3 Click driver.
 */

/**
 * @addtogroup touchpad3_set
 * @{
 */

/**
 * @brief Touchpad 3 sensor map rx registers addresses.
 * @details Specified setting for description of sensor map rx registers addresses Touchpad 3 Click driver.
 */
#define TOUCHPAD3_REG_WRITE                                       0x55, 0x04, 0x15

#define TOUCHPAD3_RX_MAP_INDEX_ADD                                0x01
#define TOUCHPAD3_RX_CH1_ADD                                      0x00
#define TOUCHPAD3_RX_CH2_ADD                                      0x01
#define TOUCHPAD3_RX_CH3_ADD                                      0x02
#define TOUCHPAD3_RX_CH4_ADD                                      0x03
#define TOUCHPAD3_RX_CH5_ADD                                      0x04

/**
 * @brief Touchpad 3 sensor map rx values.
 * @details Specified setting for description of sensor map rx values Touchpad 3 Click driver.
 */
#define TOUCHPAD3_RX_CH1                                          0x08
#define TOUCHPAD3_RX_CH2                                          0x07
#define TOUCHPAD3_RX_CH3                                          0x06
#define TOUCHPAD3_RX_CH4                                          0x05
#define TOUCHPAD3_RX_CH5                                          0x04

/**
 * @brief Touchpad 3 sensor map tx registers addresses.
 * @details Specified setting for description of sensor map tx registers addresses Touchpad 3 Click driver.
 */
#define TOUCHPAD3_TX_MAP_INDEX_ADD                                0x02
#define TOUCHPAD3_TX_CH1_ADD                                      0x00
#define TOUCHPAD3_TX_CH2_ADD                                      0x01
#define TOUCHPAD3_TX_CH3_ADD                                      0x02
#define TOUCHPAD3_TX_CH4_ADD                                      0x03

/**
 * @brief Touchpad 3 sensor map tx values.
 * @details Specified setting for description of sensor map tx values Touchpad 3 Click driver.
 */
#define TOUCHPAD3_TX_CH1                                          0x0D
#define TOUCHPAD3_TX_CH2                                          0x06
#define TOUCHPAD3_TX_CH3                                          0x03
#define TOUCHPAD3_TX_CH4                                          0x02

/**
 * @brief Touchpad 3 command set.
 * @details Specified setting for description of command set Touchpad 3 Click driver.
 */
#define TOUCHPAD3_SET_COMMAND                                     0x55
#define TOUCHPAD3_CMD_ENABLE_TOUCH                                0x00
#define TOUCHPAD3_CMD_DISABLE_TOUCH                               0x01
#define TOUCHPAD3_CMD_SCAN_BASELINE                               0x14
#define TOUCHPAD3_CMD_WRITE_REGISTER                              0x15
#define TOUCHPAD3_CMD_READ_REGISTER                               0x16
#define TOUCHPAD3_CMD_WRITE_NVRAM                                 0x17
#define TOUCHPAD3_CMD_SOFTWARE_SLEEP                              0x18
#define TOUCHPAD3_CMD_ERASE_NVRAM                                 0x19
#define TOUCHPAD3_CMD_MANUFACTURING_TEST                          0x1A
#define TOUCHPAD3_CMD_DEVICE_ID                                   0x83

/**
 * @brief Touchpad 3 index byte.
 * @details Specified setting for description of index byte Touchpad 3 Click driver.
 */
#define TOUCHPAD3_GENERAL_INDEX_BYTE                              0x00
#define TOUCHPAD3_SENSOR_MAP_RX_INDEX_BYTE                        0x01
#define TOUCHPAD3_SENSOR_MAP_TX_INDEX_BYTE                        0x02
#define TOUCHPAD3_SELF_INDEX_BYTE                                 0x10
#define TOUCHPAD3_MUTUAL_INDEX_BYTE                               0x20
#define TOUCHPAD3_DECODING_INDEX_BYTE                             0x30
#define TOUCHPAD3_GESTURES_INDEX_BYTE                             0x50
#define TOUCHPAD3_CONFIGURATION_INDEX_BYTE                        0xF0
#define TOUCHPAD3_I_O_STATUS_INDEX_BYTE                           0xF1

/**
 * @brief Touchpad 3 offset byte - General.
 * @details Specified setting for description of offset byte - General Touchpad 3 Click driver.
 */
#define TOUCHPAD3_GENERAL_OFFSET_BYTE_RX_CHANNELS                 0x01
#define TOUCHPAD3_GENERAL_OFFSET_BYTE_TX_CHANNELS                 0x02
#define TOUCHPAD3_GENERAL_OFFSET_BYTE_RX_SCALING_LSB              0x04
#define TOUCHPAD3_GENERAL_OFFSET_BYTE_RX_SCALING_MSB              0x05
#define TOUCHPAD3_GENERAL_OFFSET_BYTE_TX_SCALING_LSB              0x06
#define TOUCHPAD3_GENERAL_OFFSET_BYTE_TX_SCALING_MSB              0x07


/**
 * @brief Touchpad 3 Offset Byte - Sensor Map RX.
 * @details Specified setting for description of Offset Byte - Sensor Map RX Touchpad 3 Click driver.
 */
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_0          0x00
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_1          0x01
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_2          0x02
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_3          0x03
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_4          0x04
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_5          0x05
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_6          0x06
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_7          0x07
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_8          0x08
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_9          0x09
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_10         0x0A
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_11         0x0B
#define TOUCHPAD3_SENSOR_MAP_RX_OFFSET_BYTE_RX_PIN_MAP_12         0x0C

/**
 * @brief Touchpad 3 Offset Byte - Sensor Map TX.
 * @details Specified setting for description of Offset Byte - Sensor Map TX Touchpad 3 Click driver.
 */
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_0          0x00
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_1          0x01
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_2          0x02
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_3          0x03
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_4          0x04
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_5          0x05
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_6          0x06
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_7          0x07
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_8          0x08
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_9          0x09
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_10         0x0A
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_11         0x0B
#define TOUCHPAD3_SENSOR_MAP_TX_OFFSET_BYTE_RX_PIN_MAP_12         0x0C

/**
 * @brief Touchpad 3 offset byte - Self.
 * @details Specified setting for description of offset byte - Self Touchpad 3 Click driver.
 */
#define TOUCHPAD3_SELF_OFFSET_BYTE_SELF_SCAN_TIME                 0x00
#define TOUCHPAD3_SELF_OFFSET_BYTE_SELF_THRESHOLD                 0x01

/**
 * @brief Touchpad 3 offset byte - Mutual.
 * @details Specified setting for description of offset byte - Mutual Touchpad 3 Click driver.
 */
#define TOUCHPAD3_MUTUAL_OFFSET_BYTE_MUTUAL_SCAN_TIME             0x00
#define TOUCHPAD3_MUTUAL_OFFSET_BYTE_MUTUAL_THRESHOLD             0x01

/**
 * @brief Touchpad 3 Offset Byte - Decoding.
 * @details Specified setting for description of Offset Byte - Decoding Touchpad 3 Click driver.
 */
#define TOUCHPAD3_DECODING_OFFSET_BYTE_FLIP_STATE                 0x00
#define TOUCHPAD3_DECODING_OFFSET_BYTE_NUMBER_OF_AVG              0x01
#define TOUCHPAD3_DECODING_OFFSET_BYTE_MIN_TOUCH_DIST             0x04
#define TOUCHPAD3_DECODING_OFFSET_BYTE_PEN_DOWN_TIMER             0x05
#define TOUCHPAD3_DECODING_OFFSET_BYTE_PEN_UP_TIMER               0x06
#define TOUCHPAD3_DECODING_OFFSET_BYTE_TOUCH_SUPPR_VALUE          0x07

/**
 * @brief Touchpad 3 Offset Byte - Gestures.
 * @details Specified setting for description of Offset Byte - Gestures Touchpad 3 Click driver.
 */
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_RX_SWIPE_LEN               0x00
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_TX_SWIPE_LEN               0x01
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_SWIPE_BOUNDARY             0x02
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_SWIPE_HOLD_THD             0x03
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_SWIPE_TIME_LSB             0x04
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_SWIPE_TIME_MSB             0x05
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_TAP_TIME_LSB               0x06
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_TAP_TIME_MSB               0x07
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_TAP_THD                    0x08
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_MIN_SWIPE_VELOCITY         0x09
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_DOUBLE_TAP_TIME_LSB        0x0A
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_DOUBLE_TAP_TIME_MSB        0x0B
#define TOUCHPAD3_GESTURES_OFFSET_BYTE_GESTURE_EDGE_KEEP_OUT      0x0C

/**
 * @brief Touchpad 3 Offset Byte - Configuration.
 * @details Specified setting for description of Offset Byte - Configuration Touchpad 3 Click driver.
 */
#define TOUCHPAD3_CONFIG_OFFSET_BYTE_SLP_LSW_LSB                  0x00
#define TOUCHPAD3_CONFIG_OFFSET_BYTE_SLP_LSW_MSB                  0x01
#define TOUCHPAD3_CONFIG_OFFSET_BYTE_SLP_MSW_LSB                  0x02
#define TOUCHPAD3_CONFIG_OFFSET_BYTE_SLP_MSW_MSB                  0x03
#define TOUCHPAD3_CONFIG_OFFSET_BYTE_TOUCH_PCK_CFG                0x07
#define TOUCHPAD3_CONFIG_OFFSET_BYTE_GESTURE_PCK_CFG              0x09
#define TOUCHPAD3_CONFIG_OFFSET_BYTE_STATUS_PCK_CFG               0x0A

/**
 * @brief Touchpad 3 Offset Byte - I/O Status.
 * @details Specified setting for description of Offset Byte - I/O Status Touchpad 3 Click driver.
 */
#define TOUCHPAD3_IOSTATUS_OFFSET_BYTE_TX_SHORT_STATUS_LSB        0x02
#define TOUCHPAD3_IOSTATUS_OFFSET_BYTE_TX_SHORT_STATUS_MSB        0x03
#define TOUCHPAD3_IOSTATUS_OFFSET_BYTE_RX_SHORT_STATUS_LSB        0x06
#define TOUCHPAD3_IOSTATUS_OFFSET_BYTE_RX_SHORT_STATUS_MSB        0x07

/**
 * @brief Touchpad 3 Configuration Enable/Disable.
 * @details Specified setting for description of Configuration Enable/Disable Touchpad 3 Click driver.
 */
#define TOUCHPAD3_CONFIG_TOUCH_GESTURE_PCK_DISABLE                0x01
#define TOUCHPAD3_CONFIG_TOUCH_GESTURE_PCK_ENABLE                 0x81

/**
 * @brief Touchpad 3 touch.
 * @details Specified setting for description of touch Touchpad 3 Click driver.
 */
#define TOUCHPAD3_TOUCH_GESTURE_DISABLE                           0x00
#define TOUCHPAD3_TOUCH_GESTURE_ENABLE                            0x01

/**
 * @brief Touchpad 3 Gesture ID.
 * @details Specified setting for description of Gesture ID Touchpad 3 Click driver.
 */
#define TOUCHPAD3_GESTURE_SINGLE_TAP                              0x10
#define TOUCHPAD3_GESTURE_SINGLE_TAP_HOLD                         0x11
#define TOUCHPAD3_GESTURE_DOUBLE_TAP                              0x20
#define TOUCHPAD3_GESTURE_UP_SWIPE                                0x31
#define TOUCHPAD3_GESTURE_UP_SWIPE_HOLD                           0x32
#define TOUCHPAD3_GESTURE_RIGHT_SWIPE                             0x41
#define TOUCHPAD3_GESTURE_RIGHT_SWIPE_HOLD                        0x42
#define TOUCHPAD3_GESTURE_DOWN_SWIPE                              0x51
#define TOUCHPAD3_GESTURE_DOWN_SWIPE_HOLD                         0x52
#define TOUCHPAD3_GESTURE_LEFT_SWIPE                              0x61
#define TOUCHPAD3_GESTURE_LEFT_SWIPE_HOLD                         0x62

/**
 * @brief Touchpad 3 command protocol status result.
 * @details Specified setting for description of command protocol status result Touchpad 3 Click driver.
 */
#define TOUCHPAD3_CMD_STATUS_SUCCESS                              0x00
#define TOUCHPAD3_CMD_STATUS_PARAM_OUT_OF_RANGE                   0x80
#define TOUCHPAD3_CMD_STATUS_TIMEOUT                              0xFE
#define TOUCHPAD3_CMD_STATUS_UNRECOGNIZED                         0xFF
#define TOUCHPAD3_CMD_STATUS_INVALID_PARAM                        0xFD
#define TOUCHPAD3_CMD_STATUS_MISSING_OR_EXTRA_PARAM               0xFC

/**
 * @brief Touchpad 3 bit mask.
 * @details Specified setting for description of bit mask Touchpad 3 Click driver.
 */
#define TOUCHPAD3_T_AND_G_ID_BIT_MASK                             0x0F
#define TOUCHPAD3_TCH_STATE_BIT_MASK                              0x01
#define TOUCHPAD3_PEN_STATE_BIT_MASK                              0x01
#define TOUCHPAD3_5_BIT_MASK                                      0x1F

/**
 * @brief Touchpad 3 interrupt status.
 * @details Specified setting for description of interrupt status Touchpad 3 Click driver.
 */
#define TOUCHPAD3_INT_STATUS_LOW                                  0x00
#define TOUCHPAD3_INT_STATUS_HIGH                                 0x01

/**
 * @brief Touchpad 3 status.
 * @details Specified setting for description of status Touchpad 3 Click driver.
 */
#define TOUCHPAD3_STATUS_ERROR                                    0x00
#define TOUCHPAD3_STATUS_SUCCESS                                  0x01

/**
 * @brief Touchpad 3 Touch or Gesture state.
 * @details Specified setting for description of touch or Gesture state Touchpad 3 Click driver.
 */
#define TOUCHPAD3_STATE_TCH                                       0x00
#define TOUCHPAD3_STATE_GST                                       0x01
#define TOUCHPAD3_LEN_TCH                                         0x05
#define TOUCHPAD3_LEN_GST                                         0x02 

/**
 * @brief Touchpad 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Touchpad 3 Click driver.
 */
#define TOUCHPAD3_SET_DEV_ADDR  0x25

/*! @} */ // touchpad3_set

/**
 * @defgroup touchpad3_map Touchpad 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Touchpad 3 Click driver.
 */

/**
 * @addtogroup touchpad3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Touchpad 3 Click to the selected MikroBUS.
 */
#define TOUCHPAD3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // touchpad3_map
/*! @} */ // touchpad3

/**
 * @brief Touchpad 3 Click context object.
 * @details Context object definition of Touchpad 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;          /**< Reset. */

    // Input pins
    digital_in_t  int_pin;       /**< Interrupt. */

    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} touchpad3_t;

/**
 * @brief Touchpad 3 Click configuration object.
 * @details Configuration object definition of Touchpad 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;       /**< Reset. */
    pin_name_t  int_pin;   /**< Interrupt. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} touchpad3_cfg_t;

typedef struct
{
    uint8_t touch_id;
    uint8_t tch_state;
    uint8_t pen_state;
}touch_data_t;

typedef struct
{
    uint8_t cmd;
    uint8_t n_tx_bytes;
    uint8_t n_rx_bytes;
}cmd_protocol_t;

/**
 * @brief Touchpad 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   TOUCHPAD3_OK = 0,
   TOUCHPAD3_ERROR = -1

} touchpad3_return_value_t;

/*!
 * @addtogroup touchpad3 Touchpad 3 Click Driver
 * @brief API for configuring and manipulating Touchpad 3 Click driver.
 * @{
 */

/**
 * @brief Touchpad 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #touchpad3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void touchpad3_cfg_setup ( touchpad3_cfg_t *cfg );

/**
 * @brief Touchpad 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #touchpad3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad3_init ( touchpad3_t *ctx, touchpad3_cfg_t *cfg );

/**
 * @brief Touchpad 3 default configuration function.
 * @details This function executes a default configuration of Touchpad 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t touchpad3_default_cfg ( touchpad3_t *ctx );

/**
 * @brief Touchpad 3 get interrupt function..
 * @details The function get INT pin state of the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @return State of the INT pin.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t touchpad3_get_int ( touchpad3_t *ctx );

/**
 * @brief Touchpad 3 hardware reset function.
 * @details The function hardware reset the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void touchpad3_hw_reset ( touchpad3_t *ctx );

/**
 * @brief Touchpad 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void touchpad3_generic_write ( touchpad3_t *ctx,  uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Touchpad 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t touchpad3_generic_read ( touchpad3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Touchpad 3 general configuration function.
 * @details The function performs the general configuration of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @return Nothing. 
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void touchpad3_general_configuration ( touchpad3_t *ctx );

/**
 * @brief Touchpad 3 decoding configuration function.
 * @details The function performs the decoding configuration of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @return Nothing. 
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void touchpad3_decoding_configuration ( touchpad3_t *ctx );

/**
 * @brief Touchpad 3 sensor mapping configuration function.
 * @details The function configures the sensor mapping of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @return Nothing. 
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void touchpad3_sensor_mapping_configuration ( touchpad3_t *ctx );

/**
 * @brief Touchpad 3 get touch data function.
 * @details The function get touch data of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param [in] tch_data: structure where touch data be stored.
 * @param [out] x_axis: Pointer to the memory location where data be stored.
 * @param [out] y_axis: Pointer to the memory location where data be stored.
 * @return @li @c  0x00 - Success,
 *         @li @c  0x01 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t touchpad3_get_touch ( touchpad3_t *ctx, touch_data_t *tch_data,uint16_t *x_axis, uint16_t *y_axis );

/**
 * @brief Touchpad 3 get gesture data function.
 * @details The function get gesture data of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param [in] gst_data: Structure where gesture data be stored.
 * @param [out] gesture: Pointer to the memory location where data be stored.
 * @return @li @c  0x00 - Success,
 *         @li @c  0x01 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t touchpad3_get_gesture ( touchpad3_t *ctx, touch_data_t *gst_data, uint8_t *gesture );

/**
 * @brief Touchpad 3 command protocol function.
 * @details The function set the desired command to the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param [in] cmd_data: Pointer to the memory location where data be stored.
 * @param [in] p_tx_data: Pointer to the data to be written.
 * @param [in] p_rx_data: Pointer to the memory location where respond data be stored.
 * @return @li @c  0x00 - Success,
 *         @li @c  0x80 - Parameter out of range.
 *         @li @c  0xFE - Timeout (not enough bytes received).
 *         @li @c  0xFF - Unrecognized command.
 *         @li @c  0xFD - Invalid parameter.
 *         @li @c  0xFC - Missing or extra parameter.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t touchpad3_cmd_protocol ( touchpad3_t *ctx, cmd_protocol_t cmd_data, uint8_t *p_tx_data, uint8_t *p_rx_data );

/**
 * @brief Touchpad 3 write register data function.
 * @details The function writes a the byte of data to the targeted index and offset locationof the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param [in] index_loc : Index location.
 * @param [in] offset_loc : Offset location.
 * @param [in] tx_data : the data to be written.
 * @param [in] p_response : pointer to the memory location where respond data be stored.
 * @return @li @c  0x00 - Success,
 *         @li @c  0x80 - Parameter out of range.
 *         @li @c  0xFE - Timeout (not enough bytes received).
 *         @li @c  0xFF - Unrecognized command.
 *         @li @c  0xFD - Invalid parameter.
 *         @li @c  0xFC - Missing or extra parameter.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t touchpad3_write_reg ( touchpad3_t *ctx, uint8_t index_loc, uint8_t offset_loc, uint8_t tx_data, uint8_t 
*p_response );

/**
 * @brief Touchpad 3 read register data function.
 * @details The function read a the byte of data from the targeted index and offset location of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param [in] index_loc : Index location.
 * @param [in] offset_loc : Offset location.
 * @param [in] tx_data : the data to be written.
 * @param [in] p_response : pointer to the memory location where respond data be stored.
 * @return @li @c  0x00 - Success,
 *         @li @c  0x80 - Parameter out of range.
 *         @li @c  0xFE - Timeout (not enough bytes received).
 *         @li @c  0xFF - Unrecognized command.
 *         @li @c  0xFD - Invalid parameter.
 *         @li @c  0xFC - Missing or extra parameter.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t touchpad3_read_reg ( touchpad3_t *ctx, uint8_t index_loc, uint8_t offset_loc, uint8_t *read_data, uint8_t *p_response );

/**
 * @brief Touchpad 3 manufacturing test function.
 * @details The function set manufacturing test of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @return @li @c  0x00 - Success,
 *         @li @c  0x01 - I/O error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t touchpad3_manufacturing_test ( touchpad3_t *ctx );

/**
 * @brief Touchpad 3 get device id function.
 * @details The function reads device id of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @return Device id.
 * @note None.
 */
uint32_t touchpad3_get_device_id ( touchpad3_t *ctx );

/**
 * @brief Touchpad 3 configure touch function.
 * @details The function configures touch of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param[in] en_touch : Touch enable settings.
 * @return Status.
 * 
 * @note None.
 */
uint8_t touchpad3_config_touch ( touchpad3_t *ctx, uint8_t en_touch );

/**
 * @brief Touchpad 3 configure gesture function.
 * @details The function configures gesture of the MTCH6301 Projected Capacitive Touch Controller
 * on the TouchPad 3 click board.
 * @param[in] ctx : Click context object.
 * See #touchpad3_t object definition for detailed explanation.
 * @param[in] en_gesture : Gesture enable settings.
 * @return Status.
 * 
 * @note None.
 */
uint8_t touchpad3_config_gesture ( touchpad3_t *ctx, uint8_t en_gesture );

#ifdef __cplusplus
}
#endif
#endif // TOUCHPAD3_H

/*! @} */ // touchpad3

// ------------------------------------------------------------------------ END
