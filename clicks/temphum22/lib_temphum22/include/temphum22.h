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
 * @file temphum22.h
 * @brief This file contains API for TempHum 22 Click Driver.
 */

#ifndef TEMPHUM22_H
#define TEMPHUM22_H

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
 * @addtogroup temphum22 TempHum 22 Click Driver
 * @brief API for configuring and manipulating TempHum 22 Click driver.
 * @{
 */

/**
 * @defgroup temphum22_reg TempHum 22 Registers List
 * @brief List of registers of TempHum 22 Click driver.
 */

/**
 * @addtogroup temphum22_reg
 * @{
 */

/**
 * @brief TempHum 22 command list.
 * @details Specified command list of TempHum 22 Click driver.
 */
#define TEMPHUM22_CMD_MEAS_TH_HIGH_PREC         0xFD
#define TEMPHUM22_CMD_MEAS_TH_MED_PREC          0xF6
#define TEMPHUM22_CMD_MEAS_TH_LOW_PREC          0xE0
#define TEMPHUM22_CMD_READ_SERIAL_NUM           0x89
#define TEMPHUM22_CMD_SOFT_RESET                0x94
#define TEMPHUM22_CMD_ACT_HEATER_200mW_1S       0x39
#define TEMPHUM22_CMD_ACT_HEATER_200mW_0p1S     0x32
#define TEMPHUM22_CMD_ACT_HEATER_110mW_1S       0x2F
#define TEMPHUM22_CMD_ACT_HEATER_110mW_0p1S     0x24
#define TEMPHUM22_CMD_ACT_HEATER_20mW_1S        0x1E
#define TEMPHUM22_CMD_ACT_HEATER_20mW_0p1S      0x15

/*! @} */ // temphum22_reg

/**
 * @defgroup temphum22_set TempHum 22 Registers Settings
 * @brief Settings for registers of TempHum 22 Click driver.
 */

/**
 * @addtogroup temphum22_set
 * @{
 */

/**
 * @brief TempHum 22 temperature and humidity calculation values.
 * @details Specified temperature and humidity calculation values of TempHum 22 Click driver.
 */
#define TEMPHUM22_MAX_RH                        100.0
#define TEMPHUM22_MIN_RH                        0.0
#define TEMPHUM22_DATA_RESOLUTION               65535.0
#define TEMPHUM22_ABS_MIN_TEMP                  ( -45.0 )
#define TEMPHUM22_ABS_MAX_TEMP                  ( 130.0 )
#define TEMPHUM22_ABS_MIN_HUM                   ( -6.0 )
#define TEMPHUM22_ABS_MAX_HUM                   ( 119.0 )

/**
 * @brief TempHum 22 device address setting.
 * @details Specified setting for device slave address selection of
 * TempHum 22 Click driver.
 */
#define TEMPHUM22_DEVICE_ADDRESS                0x44

/*! @} */ // temphum22_set

/**
 * @defgroup temphum22_map TempHum 22 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 22 Click driver.
 */

/**
 * @addtogroup temphum22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 22 Click to the selected MikroBUS.
 */
#define TEMPHUM22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // temphum22_map
/*! @} */ // temphum22

/**
 * @brief TempHum 22 Click context object.
 * @details Context object definition of TempHum 22 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} temphum22_t;

/**
 * @brief TempHum 22 Click configuration object.
 * @details Configuration object definition of TempHum 22 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} temphum22_cfg_t;

/**
 * @brief TempHum 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM22_OK = 0,
    TEMPHUM22_ERROR = -1

} temphum22_return_value_t;

/*!
 * @addtogroup temphum22 TempHum 22 Click Driver
 * @brief API for configuring and manipulating TempHum 22 Click driver.
 * @{
 */

/**
 * @brief TempHum 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum22_cfg_setup ( temphum22_cfg_t *cfg );

/**
 * @brief TempHum 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #temphum22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum22_init ( temphum22_t *ctx, temphum22_cfg_t *cfg );

/**
 * @brief TempHum 22 send cmd function.
 * @details This function sends the selected command byte by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum22_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum22_send_cmd ( temphum22_t *ctx, uint8_t cmd );

/**
 * @brief TempHum 22 read response function.
 * @details This function reads 6 response bytes to the previously sent command
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum22_t object definition for detailed explanation.
 * @param[out] data_out : 6 response bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum22_read_response ( temphum22_t *ctx, uint8_t *data_out );

/**
 * @brief TempHum 22 soft reset function.
 * @details This function performs the software reset by sending the soft reset command.
 * @param[in] ctx : Click context object.
 * See #temphum22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum22_soft_reset ( temphum22_t *ctx );

/**
 * @brief TempHum 22 read serial num function.
 * @details This function reads the 4-bytes unique serial number by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum22_t object definition for detailed explanation.
 * @param[out] serial_num : 4-bytes unique serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum22_read_serial_num ( temphum22_t *ctx, uint32_t *serial_num );

/**
 * @brief TempHum 22 read measurement high precision function.
 * @details This function reads the temperature and humidity measurements with high precision.
 * @param[in] ctx : Click context object.
 * See #temphum22_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @param[out] hum : Relative humidity in percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum22_read_measurement_high_precision ( temphum22_t *ctx, float *temp, float *hum );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM22_H

/*! @} */ // temphum22

// ------------------------------------------------------------------------ END
