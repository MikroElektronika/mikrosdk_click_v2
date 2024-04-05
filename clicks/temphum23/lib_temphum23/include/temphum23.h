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
 * @file temphum23.h
 * @brief This file contains API for TempHum 23 Click Driver.
 */

#ifndef TEMPHUM23_H
#define TEMPHUM23_H

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
 * @addtogroup temphum23 TempHum 23 Click Driver
 * @brief API for configuring and manipulating TempHum 23 Click driver.
 * @{
 */

/**
 * @defgroup temphum23_reg TempHum 23 Registers List
 * @brief List of registers of TempHum 23 Click driver.
 */

/**
 * @addtogroup temphum23_reg
 * @{
 */

/**
 * @brief TempHum 23 command list.
 * @details Specified command list of TempHum 23 Click driver.
 */
#define TEMPHUM23_CMD_MEAS_TH_HIGH_PREC         0xFD
#define TEMPHUM23_CMD_MEAS_TH_MED_PREC          0xF6
#define TEMPHUM23_CMD_MEAS_TH_LOW_PREC          0xE0
#define TEMPHUM23_CMD_READ_SERIAL_NUM           0x89
#define TEMPHUM23_CMD_SOFT_RESET                0x94
#define TEMPHUM23_CMD_ACT_HEATER_200mW_1S       0x39
#define TEMPHUM23_CMD_ACT_HEATER_200mW_0p1S     0x32
#define TEMPHUM23_CMD_ACT_HEATER_110mW_1S       0x2F
#define TEMPHUM23_CMD_ACT_HEATER_110mW_0p1S     0x24
#define TEMPHUM23_CMD_ACT_HEATER_20mW_1S        0x1E
#define TEMPHUM23_CMD_ACT_HEATER_20mW_0p1S      0x15

/*! @} */ // temphum23_reg

/**
 * @defgroup temphum23_set TempHum 23 Registers Settings
 * @brief Settings for registers of TempHum 23 Click driver.
 */

/**
 * @addtogroup temphum23_set
 * @{
 */

/**
 * @brief TempHum 23 temperature and humidity calculation values.
 * @details Specified temperature and humidity calculation values of TempHum 23 Click driver.
 */
#define TEMPHUM23_MAX_RH                        100.0
#define TEMPHUM23_MIN_RH                        0.0
#define TEMPHUM23_DATA_RESOLUTION               65535.0
#define TEMPHUM23_ABS_MIN_TEMP                  ( -45.0 )
#define TEMPHUM23_ABS_MAX_TEMP                  ( 130.0 )
#define TEMPHUM23_ABS_MIN_HUM                   ( -6.0 )
#define TEMPHUM23_ABS_MAX_HUM                   ( 119.0 )

/**
 * @brief TempHum 23 device address setting.
 * @details Specified setting for device slave address selection of
 * TempHum 23 Click driver.
 */
#define TEMPHUM23_DEVICE_ADDRESS                0x44

/*! @} */ // temphum23_set

/**
 * @defgroup temphum23_map TempHum 23 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 23 Click driver.
 */

/**
 * @addtogroup temphum23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 23 Click to the selected MikroBUS.
 */
#define TEMPHUM23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // temphum23_map
/*! @} */ // temphum23

/**
 * @brief TempHum 23 Click context object.
 * @details Context object definition of TempHum 23 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} temphum23_t;

/**
 * @brief TempHum 23 Click configuration object.
 * @details Configuration object definition of TempHum 23 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} temphum23_cfg_t;

/**
 * @brief TempHum 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM23_OK = 0,
    TEMPHUM23_ERROR = -1

} temphum23_return_value_t;

/*!
 * @addtogroup temphum23 TempHum 23 Click Driver
 * @brief API for configuring and manipulating TempHum 23 Click driver.
 * @{
 */

/**
 * @brief TempHum 23 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum23_cfg_setup ( temphum23_cfg_t *cfg );

/**
 * @brief TempHum 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #temphum23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum23_init ( temphum23_t *ctx, temphum23_cfg_t *cfg );

/**
 * @brief TempHum 23 send cmd function.
 * @details This function sends the selected command byte by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum23_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum23_send_cmd ( temphum23_t *ctx, uint8_t cmd );

/**
 * @brief TempHum 23 read response function.
 * @details This function reads 6 response bytes to the previously sent command
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum23_t object definition for detailed explanation.
 * @param[out] data_out : 6 response bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum23_read_response ( temphum23_t *ctx, uint8_t *data_out );

/**
 * @brief TempHum 23 soft reset function.
 * @details This function performs the software reset by sending the soft reset command.
 * @param[in] ctx : Click context object.
 * See #temphum23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum23_soft_reset ( temphum23_t *ctx );

/**
 * @brief TempHum 23 read serial num function.
 * @details This function reads the 4-bytes unique serial number by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum23_t object definition for detailed explanation.
 * @param[out] serial_num : 4-bytes unique serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum23_read_serial_num ( temphum23_t *ctx, uint32_t *serial_num );

/**
 * @brief TempHum 23 read measurement high precision function.
 * @details This function reads the temperature and humidity measurements with high precision.
 * @param[in] ctx : Click context object.
 * See #temphum23_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @param[out] hum : Relative humidity in percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum23_read_measurement_high_precision ( temphum23_t *ctx, float *temp, float *hum );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM23_H

/*! @} */ // temphum23

// ------------------------------------------------------------------------ END
