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
 * @file color4.h
 * @brief This file contains API for Color 4 Click Driver.
 */

#ifndef COLOR4_H
#define COLOR4_H

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
 * @addtogroup color4 Color 4 Click Driver
 * @brief API for configuring and manipulating Color 4 Click driver.
 * @{
 */

/**
 * @defgroup color4_reg Color 4 Registers List
 * @brief List of registers of Color 4 Click driver.
 */

/**
 * @addtogroup color4_reg
 * @{
 */

/**
 * @brief Color 4 description register.
 * @details Specified register for description of Color 4 Click driver.
 */
#define COLOR4_CMD_CODE_CONF                    0x00
#define COLOR4_CMD_CODE_RED                     0x08
#define COLOR4_CMD_CODE_GREEN                   0x09
#define COLOR4_CMD_CODE_BLUE                    0x0A
#define COLOR4_CMD_CODE_WHITE                   0x0B

/*! @} */ // color4_reg

/**
 * @defgroup color4_set Color 4 Registers Settings
 * @brief Settings for registers of Color 4 Click driver.
 */

/**
 * @addtogroup color4_set
 * @{
 */

/**
 * @brief Color 4 description setting.
 * @details Specified setting for description of Color 4 Click driver.
 */
#define COLOR4_INTEGRATION_TIME_40MS            0x00
#define COLOR4_INTEGRATION_TIME_80MS            0x10
#define COLOR4_INTEGRATION_TIME_160MS           0x20
#define COLOR4_INTEGRATION_TIME_320MS           0x30
#define COLOR4_INTEGRATION_TIME_640MS           0x40
#define COLOR4_INTEGRATION_TIME_1280MS          0x50
#define COLOR4_INTEGRATION_BIT_MASK             0x70

#define COLOR4_TRIG_DISABLE                     0x00
#define COLOR4_TRIG_ENABLE                      0x04
#define COLOR4_TRIG_BIT_MASK                    0x04

#define COLOR4_AF_AUTO                          0x00
#define COLOR4_AF_FORCE                         0x02
#define COLOR4_AF_BIT_MASK                      0x02

#define COLOR4_SD_ENABLE                        0x00
#define COLOR4_SD_DISABLE                       0x01
#define COLOR4_SD_BIT_MASK                      0x01


/**
 * @brief Color 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 4 Click driver.
 */
#define COLOR4_DEVICE_ADDRESS                   0x10

/*! @} */ // color4_set

/**
 * @defgroup color4_map Color 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 4 Click driver.
 */

/**
 * @addtogroup color4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 4 Click to the selected MikroBUS.
 */
#define COLOR4_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // color4_map
/*! @} */ // color4

/**
 * @brief Color 4 Click context object.
 * @details Context object definition of Color 4 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
    
    float offset;             /**< Device offset. */

} color4_t;

/**
 * @brief Color 4 Click configuration object.
 * @details Configuration object definition of Color 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} color4_cfg_t;

/**
 * @brief Color 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COLOR4_OK = 0,
    COLOR4_ERROR = -1

} color4_return_value_t;

/**
 * @brief Color 4 Click channel selection value data.
 * @details Predefined enum values for driver channel selection values.
 */
typedef enum
{
    COLOR4_RED = 0,
    COLOR4_GREEN,
    COLOR4_BLUE,
    COLOR4_WHITE

} color4_ch_color_t;

/**
 * @brief Color 4 Click sensor configuration object.
 * @details Sensor configuration object definition of Color 4 Click driver.
 */
typedef struct
{
    uint8_t    integration_time;    /**< Integration time setting. */
    uint8_t    trig;                /**< Proceed one detecting cycle at manual force mode. */
    uint8_t    mode;                /**< Auto / manual force mode. */
    uint8_t    chip_shutdown;       /**< Chip shutdown setting. */

} color4_config_t;

/*!
 * @addtogroup color4 Color 4 Click Driver
 * @brief API for configuring and manipulating Color 4 Click driver.
 * @{
 */

/**
 * @brief Color 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color4_cfg_setup ( color4_cfg_t *cfg );

/**
 * @brief Color 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board™.
 * @param[out] ctx : Click context object.
 * See #color4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color4_init ( color4_t *ctx, color4_cfg_t *cfg );

/**
 * @brief Color 4 default configuration function.
 * @details This function executes a default configuration:
 * Integration time 320ms, no trigger, auto mode and enable color sensor
 * of Color 4 click board™.
 * @param[in] ctx : Click context object.
 * See #color4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t color4_default_cfg ( color4_t *ctx );

/**
 * @brief Color 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color4_generic_write ( color4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Color 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color4_generic_read ( color4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Color 4 set configuration function.
 * @details This function executes a configuration of the 
 * VEML6040 RGBW Color Sensor with I2C Interface
 * on the Color 4 click board™.
 * @param[in] ctx : Click context object.
 * See #color4_t object definition for detailed explanation.
 * @param[in] config : Sensor configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color4_set_config ( color4_t *ctx, color4_config_t config );

/**
 * @brief Color 4 get configuration function.
 * @details This function reads the configuration data 
 * of the VEML6040 RGBW Color Sensor with I2C Interface
 * on the Color 4 click board™.
 * @param[in] ctx : Click context object.
 * See #color4_t object definition for detailed explanation.
 * @param[out] config : Sensor configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color4_get_config ( color4_t *ctx, color4_config_t *config );

/**
 * @brief Color 4 get color data function.
 * @details This function reads color data of the desired channel 
 * from which the data will be converted
 * of the VEML6040 RGBW Color Sensor with I2C Interface
 * on the Color 4 click board™.
 * @param[in] ctx : Click context object.
 * See #color4_t object definition for detailed explanation.
 * @param[in] ch_color : Channel from which the data will be converted.
 * @param[out] color_data : Color data reads from the channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color4_get_color_data ( color4_t *ctx, color4_ch_color_t ch_color, uint16_t *color_data );

/**
 * @brief Color 4 get ambient light level function.
 * @details This function reads the ambient light data and calculate
 * of the VEML6040 RGBW Color Sensor with I2C Interface
 * on the Color 4 click board™.
 * @param[in] ctx : Click context object.
 * See #color4_t object definition for detailed explanation.
 * @param[out] ambient_light : Ambient light level in Lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For results for calculating lux see
 * “Designing the VEML6040 in application” application note (https://www.vishay.com/docs/84331/designingveml6040.pdf).
 */
err_t color4_get_ambient_light ( color4_t *ctx, float *ambient_light );

/**
 * @brief Color 4 get CCT data function.
 * @details This function reads the RGB color data 
 * and calculate the correlated color temperature (empirical approach)
 * of the VEML6040 RGBW Color Sensor with I2C Interface
 * on the Color 4 click board™.
 * @param[in] ctx : Click context object.
 * See #color4_t object definition for detailed explanation.
 * @param[out] cct : Correlated color temperature.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For results for calculating lux see, 
 * “Designing the VEML6040 in application” application note (https://www.vishay.com/docs/84331/designingveml6040.pdf).
 */
err_t color4_get_cct ( color4_t *ctx, float *cct );

#ifdef __cplusplus
}
#endif
#endif // COLOR4_H

/*! @} */ // color4

// ------------------------------------------------------------------------ END
