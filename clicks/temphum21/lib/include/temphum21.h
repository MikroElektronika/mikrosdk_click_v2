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
 * @file temphum21.h
 * @brief This file contains API for TempHum 21 Click Driver.
 */

#ifndef TEMPHUM21_H
#define TEMPHUM21_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup temphum21 TempHum 21 Click Driver
 * @brief API for configuring and manipulating TempHum 21 Click driver.
 * @{
 */

/**
 * @defgroup temphum21_set TempHum 21 Registers Settings
 * @brief Settings for registers of TempHum 21 Click driver.
 */

/**
 * @addtogroup temphum21_set
 * @{
 */

/**
 * @brief TempHum 21 status bits.
 * @details Specified status bits description of TempHum 21 Click driver.
 */
#define TEMPHUM21_STATUS_NORMAL_OP          0x00
#define TEMPHUM21_STATUS_STALE_DATA         0x01
#define TEMPHUM21_STATUS_COMMAND_MODE       0x02
#define TEMPHUM21_STATUS_BIT_MASK           0x03

/**
 * @brief TempHum 21 measurement calculation values.
 * @details Specified measurement calculation values of TempHum 21 Click driver.
 */
#define TEMPHUM21_DATA_RES                  0x3FFF
#define TEMPHUM21_TEMP_RES                  165.0
#define TEMPHUM21_TEMP_OFFSET               40.0
#define TEMPHUM21_HUM_RES                   100.0

/**
 * @brief TempHum 21 device address setting.
 * @details Specified setting for device slave address selection of
 * TempHum 21 Click driver.
 */
#define TEMPHUM21_SET_DEV_ADDR              0x27

/*! @} */ // temphum21_set

/**
 * @defgroup temphum21_map TempHum 21 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 21 Click driver.
 */

/**
 * @addtogroup temphum21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 21 Click to the selected MikroBUS.
 */
#define TEMPHUM21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.all = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.alh = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // temphum21_map
/*! @} */ // temphum21

/**
 * @brief TempHum 21 Click context object.
 * @details Context object definition of TempHum 21 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t all;           /**< Alarm low. */
    digital_in_t alh;           /**< Alarm high. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} temphum21_t;

/**
 * @brief TempHum 21 Click configuration object.
 * @details Configuration object definition of TempHum 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t all;             /**< Alarm low. */
    pin_name_t alh;             /**< Alarm high. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} temphum21_cfg_t;

/**
 * @brief TempHum 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM21_OK = 0,
    TEMPHUM21_ERROR = -1

} temphum21_return_value_t;

/*!
 * @addtogroup temphum21 TempHum 21 Click Driver
 * @brief API for configuring and manipulating TempHum 21 Click driver.
 * @{
 */

/**
 * @brief TempHum 21 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum21_cfg_setup ( temphum21_cfg_t *cfg );

/**
 * @brief TempHum 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #temphum21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum21_init ( temphum21_t *ctx, temphum21_cfg_t *cfg );

/**
 * @brief TempHum 21 request measurement function.
 * @details This function sends a request mesurement command.
 * @param[in] ctx : Click context object.
 * See #temphum21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum21_request_measurement ( temphum21_t *ctx );

/**
 * @brief TempHum 21 read measurement function.
 * @details This function requests measurement and waits for a measurement to complete and after that reads
 * temperature in Celsius and relative humidity in percents.
 * @param[in] ctx : Click context object.
 * See #temphum21_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @param[out] humidity : Relative humidity in Percents.
 * @return @li @c  2 - Device in Command Mode - Command Mode is used for programming the sensor.
 *         @li @c  1 - Stale Data: Data that has already been fetched since the last measurement cycle, or
 *                                 data fetched before the first measurement has been completed.
 *         @li @c  0 - Normal Operation, Valid Data that has not been fetched since the last measurement cycle.
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum21_read_measurement ( temphum21_t *ctx, float *temperature, float *humidity );

/**
 * @brief TempHum 21 get all pin function.
 * @details This function returns the alarm low (ALL) pin logic state.
 * @param[in] ctx : Click context object.
 * See #temphum21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t temphum21_get_all_pin ( temphum21_t *ctx );

/**
 * @brief TempHum 21 get alh pin function.
 * @details This function returns the alarm high (ALH) pin logic state.
 * @param[in] ctx : Click context object.
 * See #temphum21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t temphum21_get_alh_pin ( temphum21_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM21_H

/*! @} */ // temphum21

// ------------------------------------------------------------------------ END
