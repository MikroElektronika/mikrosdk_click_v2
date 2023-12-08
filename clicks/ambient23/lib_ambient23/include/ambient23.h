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
 * @file ambient23.h
 * @brief This file contains API for Ambient 23 Click Driver.
 */

#ifndef AMBIENT23_H
#define AMBIENT23_H

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
 * @addtogroup ambient23 Ambient 23 Click Driver
 * @brief API for configuring and manipulating Ambient 23 Click driver.
 * @{
 */

/**
 * @defgroup ambient23_reg Ambient 23 Registers List
 * @brief List of registers of Ambient 23 Click driver.
 */

/**
 * @addtogroup ambient23_reg
 * @{
 */

/**
 * @brief Ambient 23 description register.
 * @details Specified register for description of Ambient 23 Click driver.
 */
#define AMBIENT23_REG_CONFIG                    0x00
#define AMBIENT23_REG_WHITE_DATA                0x04
#define AMBIENT23_REG_ALS_DATA                  0x05
#define AMBIENT23_REG_DEVICE_ID                 0x09

/*! @} */ // ambient23_reg

/**
 * @defgroup ambient23_set Ambient 23 Registers Settings
 * @brief Settings for registers of Ambient 23 Click driver.
 */

/**
 * @addtogroup ambient23_set
 * @{
 */

/**
 * @brief Ambient 23 gain setting.
 * @details Specified gain settings for description of Ambient 23 Click driver.
 */
#define AMBIENT23_GAIN_1                    0x0000u
#define AMBIENT23_GAIN_2                    0x0800u
#define AMBIENT23_GAIN_4                    0x1800u
#define AMBIENT23_GAIN_MSK                  0x1800u

/**
 * @brief Ambient 23 data gain setting.
 * @details Specified data gain settings for description of Ambient 23 Click driver.
 */
#define AMBIENT23_DATA_GAIN_1               0x0000u
#define AMBIENT23_DATA_GAIN_2               0x2000u
#define AMBIENT23_DATA_GAIN_MASK            0x2000u

/**
 * @brief Ambient 23 shutdown setting.
 * @details Specified shutdown settings for description of Ambient 23 Click driver.
 */
#define AMBIENT23_SDO_SHUTDOWN_ON           0x8000u
#define AMBIENT23_SDO_SHUTDOWN_OFF          0x0000u
#define AMBIENT23_SHUTDOWN_ON               0x0001u
#define AMBIENT23_SHUTDOWN_OFF              0x0000u

/**
 * @brief Ambient 23 trigger setting.
 * @details Specified trigger settings for description of Ambient 23 Click driver.
 */
#define AMBIENT23_TRIGGER_ON                0x0004u
#define AMBIENT23_TRIGGER_OFF               0x0000u

/**
 * @brief Ambient 23 force mode setting.
 * @details Specified force mode settings for description of Ambient 23 Click driver.
 */
#define AMBIENT23_AUTO_FORCE_MODE           0x0800u
#define AMBIENT23_MANUAL_FORCE_MODE         0x0000u

/**
 * @brief Ambient 23 integration time setting.
 * @details Specified integration time settings for description of Ambient 23 Click driver.
 */
#define AMBIENT23_INTEGRATION_50_MS         0x0000u
#define AMBIENT23_INTEGRATION_100_MS        0x0010u
#define AMBIENT23_INTEGRATION_200_MS        0x0020u
#define AMBIENT23_INTEGRATION_400_MS        0x0030u
#define AMBIENT23_INTEGRATION_800_MS        0x0040u
#define AMBIENT23_INTEGRATION_TIME_MSK      0x0070u

/**
 * @brief Ambient 23 config register value.
 * @details Specified config register value of Ambient 23 Click driver.
 */
#define AMBIENT23_CONFIG_DEF_VAL            0x0100u

/**
 * @brief Ambient 23 device ID.
 * @details Specified device ID of Ambient 23 Click driver.
 */
#define AMBIENT23_PART_ID                   0x35

/**
 * @brief Ambient 23 typical resolution value.
 * @details Specified typical resolution value of Ambient 23 Click driver.
 */
#define AMBIENT23_TYPICAL_RESOLUTION        0.27264f

/**
 * @brief Ambient 23 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 23 Click driver.
 */
#define AMBIENT23_DEVICE_ADDRESS            0x10

/*! @} */ // ambient23_set

/**
 * @defgroup ambient23_map Ambient 23 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 23 Click driver.
 */

/**
 * @addtogroup ambient23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 23 Click to the selected MikroBUS.
 */
#define AMBIENT23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); 

/*! @} */ // ambient23_map
/*! @} */ // ambient23

/**
 * @brief Ambient 23 Click context object.
 * @details Context object definition of Ambient 23 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;            /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;       /**< Device slave address (used for I2C driver). */
    
} ambient23_t;

/**
 * @brief Ambient 23 Click configuration object.
 * @details Configuration object definition of Ambient 23 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ambient23_cfg_t;

/**
 * @brief Ambient 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT23_OK = 0,
    AMBIENT23_ERROR = -1

} ambient23_return_value_t;

/*!
 * @addtogroup ambient23 Ambient 23 Click Driver
 * @brief API for configuring and manipulating Ambient 23 Click driver.
 * @{
 */

/**
 * @brief Ambient 23 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient23_cfg_setup ( ambient23_cfg_t *cfg );

/**
 * @brief Ambient 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ambient23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient23_init ( ambient23_t *ctx, ambient23_cfg_t *cfg );

/**
 * @brief Ambient 23 default configuration function.
 * @details This function executes a default configuration of Ambient 23
 * click board.
 * @param[in] ctx : Click context object.
 * See #ambient23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient23_default_cfg ( ambient23_t *ctx );

/**
 * @brief Ambient 23 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient23_generic_write ( ambient23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Ambient 23 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient23_generic_read ( ambient23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Ambient 23 register data writing function.
 * @details This function writes a 16 bytes of data into
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient23_reg_write ( ambient23_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Ambient 23 register reading function.
 * @details This function reads a 16 bytes of data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient23_reg_read ( ambient23_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Ambient 23 get conversion data function.
 * @details This function is used to get the conversion 
 * multiplier necessary for converting raw ADC value into lux.
 * @param[in] ctx : Click context object.
 * See #ambient23_t object definition for detailed explanation.
 * @param[out] conversion_mul : Conversion multiplier.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient23_calculate_res ( ambient23_t *ctx, float *conversion_mul );

/**
 * @brief Ambient 23 get light data function.
 * @details This function is used to measure light level in lux.
 * @param[in] ctx : Click context object.
 * See #ambient23_t object definition for detailed explanation.
 * @param[out] light_data : Measured light level.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient23_read_light_data ( ambient23_t *ctx, float *light_data );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT23_H

/*! @} */ // ambient23

// ------------------------------------------------------------------------ END
