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
 * @file color12.h
 * @brief This file contains API for Color 12 Click Driver.
 */

#ifndef COLOR12_H
#define COLOR12_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup color12 Color 12 Click Driver
 * @brief API for configuring and manipulating Color 12 Click driver.
 * @{
 */

/**
 * @defgroup color12_reg Color 12 Registers List
 * @brief List of registers of Color 12 Click driver.
 */

/**
 * @addtogroup color12_reg
 * @{
 */

/**
 * @brief Color 12 description register.
 * @details Specified register for descriptions of Color 12 Click driver.
 */
#define COLOR12_REG_SYSTEM_CONTROL         0x40
#define COLOR12_REG_MODE_CONTROL1          0x41
#define COLOR12_REG_MODE_CONTROL2          0x42
#define COLOR12_REG_MODE_CONTROL3          0x43
#define COLOR12_REG_RED_DATA_L             0x50
#define COLOR12_REG_RED_DATA_H             0x51
#define COLOR12_REG_GREEN_DATA_L           0x52
#define COLOR12_REG_GREEN_DATA_H           0x53
#define COLOR12_REG_BLUE_DATA_L            0x54
#define COLOR12_REG_BLUE_DATA_H            0x55
#define COLOR12_REG_IR_DATA_L              0x56
#define COLOR12_REG_IR_DATA_H              0x57
#define COLOR12_REG_FLICKER_DATA_L         0x58
#define COLOR12_REG_FLICKER_DATA_H         0x59
#define COLOR12_REG_FLICKER_COUNTER        0x5A
#define COLOR12_REG_FIFO_LEVEL             0x5B
#define COLOR12_REG_FIFO_DATA_L            0x5C
#define COLOR12_REG_FIFO_DATA_H            0x5D
#define COLOR12_REG_MANUFACTURER_ID        0x92

/*! @} */ // color12_reg

/**
 * @defgroup color12_set Color 12 Registers Settings
 * @brief Settings for registers of Color 12 Click driver.
 */

/**
 * @addtogroup color12_set
 * @{
 */

/**
 * @brief Color 12 software reset data.
 * @details Software reset data of Color 12 Click driver.
 */
#define COLOR12_SET_SW_RESET               0x80

/**
 * @brief Color 12 gain setting for RGB/IR sensor.
 * @details Gain setting for RGB/IR of Color 12 Click driver.
 */
#define COLOR12_RGB_GAIN_X1                0x00
#define COLOR12_RGB_GAIN_X2                0x01
#define COLOR12_RGB_GAIN_X4                0x02
#define COLOR12_RGB_GAIN_X8                0x03
#define COLOR12_RGB_GAIN_X16               0x04
#define COLOR12_RGB_GAIN_X32               0x05

/**
 * @brief Color 12 measurement mode for RGB/IR data.
 * @details Measurement mode for RGB/IR data of Color 12 Click driver.
 */
#define COLOR12_MEAS_MODE_55MS             0x01
#define COLOR12_MEAS_MODE_100MS            0x02

/**
 * @brief Color 12 gain setting for flicker sensor.
 * @details Gain setting for flicker of Color 12 Click driver.
 */
#define COLOR12_FLC_GAIN_X1                0x00
#define COLOR12_FLC_GAIN_X2                0x01
#define COLOR12_FLC_GAIN_X4                0x02
#define COLOR12_FLC_GAIN_X8                0x03
#define COLOR12_FLC_GAIN_X16               0x04
#define COLOR12_FLC_GAIN_X32               0x05

/**
 * @brief Color 12 measurement mode for flicker data.
 * @details Measurement mode for flicker data of Color 12 Click driver.
 */
#define COLOR12_FLC_MODE_1KHZ              0x00
#define COLOR12_FLC_MODE_2KHZ              0x01

/**
 * @brief Color 12 interrupt selector data.
 * @details Interrupt selector data of Color 12 Click driver.
 */
#define COLOR12_INT_SEL_DISABLE            0x00
#define COLOR12_INT_SEL_RDY_RGB_IR         0x01
#define COLOR12_INT_SEL_RDY_FLICKER        0x02
#define COLOR12_INT_SEL_RDY_FIFO           0x03

/**
 * @brief Color 12 RGB/IR measurement mode.
 * @details RGB/IR measurement mode of Color 12 Click driver.
 */
#define COLOR12_RGB_EN_DISABLE             0x00
#define COLOR12_RGB_EN_ENABLE              0x01

/**
 * @brief Color 12 flicker measurement mode.
 * @details Flicker measurement mode of Color 12 Click driver.
 */
#define COLOR12_FLC_EN_DISABLE             0x00
#define COLOR12_FLC_EN_ENABLE              0x01

/**
 * @brief Color 12 manufacturer ID data.
 * @details Manufacturer ID data of Color 12 Click driver.
 */
#define COLOR12_MANUFACTURER_ID            0xE0

/**
 * @brief Color 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 12 Click driver.
 */
#define COLOR12_DEVICE_ADDRESS             0x38

/*! @} */ // color12_set

/**
 * @defgroup color12_map Color 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 12 Click driver.
 */

/**
 * @addtogroup color12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 12 Click to the selected MikroBUS.
 */
#define COLOR12_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color12_map
/*! @} */ // color12

/**
 * @brief Color 12 Click context object.
 * @details Context object definition of Color 12 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} color12_t;

/**
 * @brief Color 12 Click configuration object.
 * @details Configuration object definition of Color 12 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;        /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} color12_cfg_t;

/**
 * @brief Color 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COLOR12_OK = 0,
    COLOR12_ERROR = -1

} color12_return_value_t;

/**
 * @brief Color 12 Click color selection value data.
 * @details Predefined enum values for driver color selection values.
 */
typedef enum
{
    COLOR12_DATA_RED = 0,
    COLOR12_DATA_GREEN,
    COLOR12_DATA_BLUE,
    COLOR12_DATA_IR

} color12_color_sel_t;

/**
 * @brief Color 12 Click sensor configuration object.
 * @details Sensor configuration object definition of Color 12 Click driver.
 */
typedef struct
{
    uint8_t rgb_gain;     /**< Gain setting for RGB/IR Data. */
    uint8_t meas_mode;    /**< Measurement mode for RGB/IR Data. */
    uint8_t flc_gain;     /**< Gain setting for flicker sensor. */
    uint8_t flc_mode;     /**< Measurement mode for flicker Data. */
    uint8_t int_sel;      /**< Measurement completion. */
    uint8_t rgb_en;       /**< RGB/IR measurement configuration. */
    uint8_t flc_en;       /**< Flicker measurement configuration. */

} color12_config_t;

/*!
 * @addtogroup color12 Color 12 Click Driver
 * @brief API for configuring and manipulating Color 12 Click driver.
 * @{
 */

/**
 * @brief Color 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color12_cfg_setup ( color12_cfg_t *cfg );

/**
 * @brief Color 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color12_init ( color12_t *ctx, color12_cfg_t *cfg );

/**
 * @brief Color 12 default configuration function.
 * @details This function executes a default configuration of Color 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t color12_default_cfg ( color12_t *ctx );

/**
 * @brief Color 12 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color12_generic_write ( color12_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Color 12 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color12_generic_read ( color12_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Color 12 software reset function.
 * @details This function is used to perform a software reset 
 * of the BU27006MUC-Z, Digital 16bit Serial Output Type Color Sensor IC
 * on the Color 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color12_sw_reset ( color12_t *ctx );

/**
 * @brief Color 12 sets the configuration function.
 * @details This function executes a configuration
 * of the BU27006MUC-Z, Digital 16bit Serial Output Type Color Sensor IC
 * on the Color 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @param[in] config : Sensor configuration object.
 * See color12_config_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color12_set_config ( color12_t *ctx, color12_config_t config );

/**
 * @brief Color 12 gets the configuration function.
 * @details This function reads the configuration data 
 * of the BU27006MUC-Z, Digital 16bit Serial Output Type Color Sensor IC
 * on the Color 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @param[out] config : Sensor configuration object.
 * See color12_config_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color12_get_config ( color12_t *ctx, color12_config_t *config );

/**
 * @brief Color 12 gets the color measurement result function.
 * @details This function reads color measurement result data of the desired selection
 * of the BU27006MUC-Z, Digital 16bit Serial Output Type Color Sensor IC
 * on the Color 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @param[in] color_sel : Color data selector.
 * See color12_color_sel_t object definition for detailed explanation.
 * @param[out] color_data : Color measurement result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color12_get_color_data ( color12_t *ctx, color12_color_sel_t color_sel, uint16_t *color_data );

/**
 * @brief Color 12 gets the device ID function.
 * @details This function reads a manufacturers ID
 * of the BU27006MUC-Z, Digital 16bit Serial Output Type Color Sensor IC
 * on the Color 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @param[out] device_id : Manufacturer ID (0xE0).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color12_get_device_id ( color12_t *ctx, uint8_t *device_id );

/**
 * @brief Color 12 gets the interrupt function.
 * @details This function gets states of the Interrupt ( INT ) pin
 * of the BU27006MUC-Z, Digital 16bit Serial Output Type Color Sensor IC
 * on the Color 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #color12_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state
 * @note None.
 */
uint8_t color12_get_int_pin ( color12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // COLOR12_H

/*! @} */ // color12

// ------------------------------------------------------------------------ END
