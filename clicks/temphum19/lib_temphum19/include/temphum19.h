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
 * @file temphum19.h
 * @brief This file contains API for TempHum 19 Click Driver.
 */

#ifndef TEMPHUM19_H
#define TEMPHUM19_H

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
 * @addtogroup temphum19 TempHum 19 Click Driver
 * @brief API for configuring and manipulating TempHum 19 Click driver.
 * @{
 */

/**
 * @defgroup temphum19_reg TempHum 19 Registers List
 * @brief List of registers of TempHum 19 Click driver.
 */

/**
 * @addtogroup temphum19_reg
 * @{
 */

/**
 * @brief TempHum 19 register list.
 * @details Specified register list of TempHum 19 Click driver.
 */
#define TEMPHUM19_REG_RESET                 0x00
#define TEMPHUM19_REG_MODE                  0x01
#define TEMPHUM19_REG_ERROR                 0x03
#define TEMPHUM19_REG_HUMIDITY_LSB          0x04
#define TEMPHUM19_REG_HUMIDITY_MSB          0x05
#define TEMPHUM19_REG_TEMPERATURE_LSB       0x06
#define TEMPHUM19_REG_TEMPERATURE_MSB       0x07
#define TEMPHUM19_REG_CAPACITY_LSB          0x0A
#define TEMPHUM19_REG_CAPACITY_MSB          0x0B
#define TEMPHUM19_REG_CAPACITY_CTRL         0x2C

/*! @} */ // temphum19_reg

/**
 * @defgroup temphum19_set TempHum 19 Registers Settings
 * @brief Settings for registers of TempHum 19 Click driver.
 */

/**
 * @addtogroup temphum19_set
 * @{
 */

/**
 * @brief TempHum 19 temperature and humidity calculation setting.
 * @details Specified temperature and humidity calculation setting of TempHum 19 Click driver.
 */
#define TEMPHUM19_10BIT_RESOLUTION          0x400
#define TEMPHUM19_TEMP_DATA                 0x7FF
#define TEMPHUM19_HUM_DATA                  0x3FF
#define TEMPHUM19_TEMP_RESOLUTION           0.1
#define TEMPHUM19_HUM_RESOLUTION            100
#define TEMPHUM19_TEMP_NOMINAL              25

/**
 * @brief TempHum 19 mode register setting.
 * @details Specified setting for mode register of TempHum 19 Click driver.
 */
#define TEMPHUM19_NORMAL_OPERATION_MODE     0x00
#define TEMPHUM19_HUM_NO_AVG                0x00
#define TEMPHUM19_HUM_AVG_2                 0x08
#define TEMPHUM19_HUM_AVG_4                 0x10
#define TEMPHUM19_HUM_AVG_8                 0x20
#define TEMPHUM19_TEMP_AVG_8                0x00
#define TEMPHUM19_TEMP_AVG_16               0x04
#define TEMPHUM19_START_DETECTION           0x01
#define TEMPHUM19_STOP_DETECTION            0x00

/**
 * @brief TempHum 19 device address setting.
 * @details Specified setting for device slave address selection of
 * TempHum 19 Click driver.
 */
#define TEMPHUM19_SET_DEV_ADDR              0x7F

/*! @} */ // temphum19_set

/**
 * @defgroup temphum19_map TempHum 19 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 19 Click driver.
 */

/**
 * @addtogroup temphum19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 19 Click to the selected MikroBUS.
 */
#define TEMPHUM19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // temphum19_map
/*! @} */ // temphum19

/**
 * @brief TempHum 19 Click context object.
 * @details Context object definition of TempHum 19 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable chip pin. */

    // Modules
    i2c_master_t  i2c;          /**< I2C driver object. */
    pin_name_t    scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t    sda;          /**< Bidirectional data pin descriptor for I2C driver. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t  detection_mode;    /**< Detection mode settings. */

} temphum19_t;

/**
 * @brief TempHum 19 Click configuration object.
 * @details Configuration object definition of TempHum 19 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;             /**< Enable chip pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} temphum19_cfg_t;

/**
 * @brief TempHum 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM19_OK = 0,
    TEMPHUM19_ERROR = -1

} temphum19_return_value_t;

/*!
 * @addtogroup temphum19 TempHum 19 Click Driver
 * @brief API for configuring and manipulating TempHum 19 Click driver.
 * @{
 */

/**
 * @brief TempHum 19 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum19_cfg_setup ( temphum19_cfg_t *cfg );

/**
 * @brief TempHum 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #temphum19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum19_init ( temphum19_t *ctx, temphum19_cfg_t *cfg );

/**
 * @brief TempHum 19 default configuration function.
 * @details This function executes a default configuration of TempHum 19
 * click board.
 * @param[in] ctx : Click context object.
 * See #temphum19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t temphum19_default_cfg ( temphum19_t *ctx );

/**
 * @brief TempHum 19 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum19_generic_write ( temphum19_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief TempHum 19 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum19_generic_read ( temphum19_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief TempHum 19 enable chip function.
 * @details This function enables the chip by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #temphum19_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum19_enable_chip ( temphum19_t *ctx );

/**
 * @brief TempHum 19 disable chip function.
 * @details This function disables the chip by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #temphum19_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum19_disable_chip ( temphum19_t *ctx );

/**
 * @brief TempHum 19 restart chip function.
 * @details This function restarts the chip by toggling the EN pin state.
 * @param[in] ctx : Click context object.
 * See #temphum19_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum19_restart_chip ( temphum19_t *ctx );

/**
 * @brief TempHum 19 set mode function.
 * @details This function programs the mode register with a desired @a mode value, and stores
 * it to the @b ctx->detection_mode variable.
 * @param[in] ctx : Click context object.
 * See #temphum19_t object definition for detailed explanation.
 * @param[in] mode : Detection mode value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum19_set_mode_reg ( temphum19_t *ctx, uint8_t mode );

/**
 * @brief TempHum 19 read data function.
 * @details This function reads temperature and humidity raw data and converts them 
 * to Celsius and Percents respectfully.
 * @param[in] ctx : Click context object.
 * See #temphum19_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @param[out] humidity : Humidity in Percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note In the case of any error, this function will restart the chip.
 */
err_t temphum19_read_data ( temphum19_t *ctx, float *temperature, float *humidity );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM19_H

/*! @} */ // temphum19

// ------------------------------------------------------------------------ END
