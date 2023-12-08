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
 * @file temphum18.h
 * @brief This file contains API for Temp&Hum 18 Click Driver.
 */

#ifndef TEMPHUM18_H
#define TEMPHUM18_H

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
 * @addtogroup temphum18 Temp&Hum 18 Click Driver
 * @brief API for configuring and manipulating Temp&Hum 18 Click driver.
 * @{
 */

/**
 * @defgroup temphum18_reg Temp&Hum 18 Registers List
 * @brief List of registers of Temp&Hum 18 Click driver.
 */

/**
 * @addtogroup temphum18_reg
 * @{
 */

/**
 * @brief Temp&Hum 18 description register.
 * @details Specified register for description of Temp&Hum 18 Click driver.
 */
#define TEMPHUM18_REG_HUMIDITY_SENSOR_RESOLUTION_READ           0x06
#define TEMPHUM18_REG_HUMIDITY_SENSOR_RESOLUTION_WRITE          0x46
#define TEMPHUM18_REG_TEMPERATURE_SENSOR_RESOLUTION_READ        0x11
#define TEMPHUM18_REG_TEMPERATURE_SENSOR_RESOLUTION_WRITE       0x51
#define TEMPHUM18_REG_SENSOR_ID_UPPER_READ                      0x1E
#define TEMPHUM18_REG_SENSOR_ID_LOWER_READ                      0x1F

/*! @} */ // temphum18_reg

/**
 * @defgroup temphum18_cmd Temp&Hum 18 Command List
 * @brief List of commands of Temp&Hum 18 Click driver.
 */

/**
 * @addtogroup temphum18_cmd
 * @{
 */

/**
 * @brief Temp&Hum 18 description command.
 * @details Specified commands for description of Temp&Hum 18 Click driver.
 */
#define TEMPHUM18_CMD_ENTER_PROGRAMMING_MODE                    0xA0
#define TEMPHUM18_CMD_DUMMY                                     0x00
#define TEMPHUM18_CMD_ENTER_MEASUREMENTS_MODE                   0x80
/*! @} */ // temphum18_cmd

/**
 * @defgroup temphum18_status Temp&Hum 18 status bits
 * @brief List of status bits of Temp&Hum 18 Click driver.
 */

/**
 * @addtogroup temphum18_status
 * @{
 */

/**
 * @brief Temp&Hum 18 description status bits.
 * @details Specified status bits for description of Temp&Hum 18 Click driver.
 */
#define TEMPHUM18_STATUS_VALID_DATA                              0x00
#define TEMPHUM18_STATUS_STALE_DATA                              0x01
/*! @} */ // temphum18_status

/**
 * @defgroup temphum18_set Temp&Hum 18 Registers Settings
 * @brief Settings for registers of Temp&Hum 18 Click driver.
 */

/**
 * @addtogroup temphum18_set
 * @{
 */

/**
 * @brief Temp&Hum 18 description setting.
 * @details Specified setting for description of Temp&Hum 18 Click driver.
 */
#define TEMPHUM18_RESOLUTION_8_BITS                             0x00
#define TEMPHUM18_RESOLUTION_10_BITS                            0x01
#define TEMPHUM18_RESOLUTION_12_BITS                            0x02
#define TEMPHUM18_RESOLUTION_14_BITS                            0x03

/**
 * @brief Temp&Hum 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Temp&Hum 18 Click driver.
 */
#define TEMPHUM18_SET_DEV_ADDR  0x44

/*! @} */ // temphum18_set

/**
 * @defgroup temphum18_map Temp&Hum 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Temp&Hum 18 Click driver.
 */

/**
 * @addtogroup temphum18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Temp&Hum 18 Click to the selected MikroBUS.
 */
#define TEMPHUM18_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // temphum18_map
/*! @} */ // temphum18

/**
 * @brief Temp&Hum 18 Click context object.
 * @details Context object definition of Temp&Hum 18 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;     /**< Device slave address (used for I2C driver). */

} temphum18_t;

/**
 * @brief Temp&Hum 18 Click configuration object.
 * @details Configuration object definition of Temp&Hum 18 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} temphum18_cfg_t;

/**
 * @brief Temp&Hum 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM18_OK = 0,
    TEMPHUM18_ERROR = -1

} temphum18_return_value_t;

/*!
 * @addtogroup temphum18 Temp&Hum 18 Click Driver
 * @brief API for configuring and manipulating Temp&Hum 18 Click driver.
 * @{
 */

/**
 * @brief Temp&Hum 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum18_cfg_setup ( temphum18_cfg_t *cfg );

/**
 * @brief Temp&Hum 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #temphum18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum18_init ( temphum18_t *ctx, temphum18_cfg_t *cfg );

/**
 * @brief Temp&Hum 18 default configuration function.
 * @details This function executes a default configuration of Temp&Hum 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #temphum18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t temphum18_default_cfg ( temphum18_t *ctx );

/**
 * @brief Temp&Hum 18 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum18_generic_write ( temphum18_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Temp&Hum 18 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum18_generic_read ( temphum18_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Temp&Hum 18 wake up function.
 * @details This function wake up 
 * the HS3003 High Performance Relative Humidity and Temperature Sensor 
 * from its Sleep Mode.
 * @param[in] ctx : Click context object.
 * See #temphum18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum18_wake_up ( temphum18_t *ctx );

/**
 * @brief Temp&Hum 18 get raw data function.
 * @details This function get raw data 
 * of the HS3003 High Performance Relative Humidity and Temperature Sensor
 * on the  Temp&Hum 18 click board™.
 * @param[in] ctx : Click context object.
 * @param[in] resolution : 
 *         @li @c 0x00 ( TEMPHUM18_RESOLUTION_8_BITS )  - 8 bit resolution,
 *         @li @c 0x01 ( TEMPHUM18_RESOLUTION_10_BITS ) - 10 bit resolution,
 *         @li @c 0x02 ( TEMPHUM18_RESOLUTION_12_BITS ) - 12 bit resolution,
 *         @li @c 0x03 ( TEMPHUM18_RESOLUTION_14_BITS ) - 14 bit resolution.
 * @param[out] temp : Output read Temperature ( RAW ) data.
 * @param[out] hum : Output read Humidity ( RAW ) data.
 * @param[out] status :
 *        @li @c 0x00 ( TEMPHUM18_STATUS_VALID_DATA ) - Data that has not been fetched since the last measurement cycle,
 *        @li @c 0x01 ( TEMPHUM18_STATUS_STALE_DATA ) - Data that has already been fetched since the last measurement cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Status : If a data fetch is performed before or during the first measurement after power-on reset, 
 * then the stale status will be returned, 
 * but this data is actually invalid since the first measurement has not been completed.
 * The function performs a delay depending on the selected data resolution: 
 *        @li @c 14-bit resolution it is 33.90 milliseconds,
 *        @li @c 12-bit resolution it is 9.10 milliseconds,
 *        @li @c 10-bit resolution it is 2.72 milliseconds, 
 *        @li @c  8-bit resolution it is 1.20 milliseconds.
 */
err_t temphum18_get_raw_data ( temphum18_t *ctx, uint8_t resolution, int16_t *temp, uint16_t *hum, uint8_t *status );

/**
 * @brief Temp&Hum 18 get temperature and humidity function.
 * @details This function get temperature ( degree Celsius ) and humidity ( % ) 
 * of the HS3003 High Performance Relative Humidity and Temperature Sensor
 * on the  Temp&Hum 18 click board™.
 * @param[in] ctx : Click context object.
 * @param[in] resolution : 
 *         @li @c 0x00 ( TEMPHUM18_RESOLUTION_8_BITS )  - 8 bit resolution,
 *         @li @c 0x01 ( TEMPHUM18_RESOLUTION_10_BITS ) - 10 bit resolution,
 *         @li @c 0x02 ( TEMPHUM18_RESOLUTION_12_BITS ) - 12 bit resolution,
 *         @li @c 0x03 ( TEMPHUM18_RESOLUTION_14_BITS ) - 14 bit resolution.
 * @param[out] temperature : Temperature data ( degree Celsius ).
 * @param[out] humidity : Humidity data ( % ).
 * @return @li @c  0 ( TEMPHUM18_STATUS_VALID_DATA ) - Data that has not been fetched since the last measurement cycle,
 *         @li @c  1 ( TEMPHUM18_STATUS_STALE_DATA ) - Data that has already been fetched since the last measurement cycle.
 *         @li @c -1 - Communication Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Status : If a data fetch is performed before or during the first measurement after power-on reset, 
 * then the stale status will be returned, 
 * but this data is actually invalid since the first measurement has not been completed.
 * The function performs a delay depending on the selected data resolution: 
 *        @li @c 14-bit resolution it is 33.90 milliseconds,
 *        @li @c 12-bit resolution it is 9.10 milliseconds,
 *        @li @c 10-bit resolution it is 2.72 milliseconds, 
 *        @li @c  8-bit resolution it is 1.20 milliseconds.
 */
err_t temphum18_get_temp_hum ( temphum18_t *ctx, uint8_t resolution, float *temperature, float *humidity );

/**
 * @brief Temp&Hum 18 enter programming mode function.
 * @details This function enter programming mode, accessing the non-volatile memory 
 * of the HS3003 High Performance Relative Humidity and Temperature Sensor
 * on the  Temp&Hum 18 click board™.
 * @param[in] ctx : Click context object.
 * See #temphum18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note To enter the programming mode, you must call the function within 10 ms after the sensor has been powered on.
 */
err_t temphum18_enter_programming_mode ( temphum18_t *ctx );

/**
 * @brief Temp&Hum 18 enter measurements mode function.
 * @details This function enter measurements mode, exit programming mode
 * of the HS3003 High Performance Relative Humidity and Temperature Sensor
 * on the  Temp&Hum 18 click board™.
 * @param[in] ctx : Click context object.
 * See #temphum18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum18_enter_measurements_mode ( temphum18_t *ctx );

/**
 * @brief Temp&Hum 18 set relative humidity resolution function.
 * @details This function sets desired relative humidity resolution
 * of the HS3003 High Performance Relative Humidity and Temperature Sensor
 * on the  Temp&Hum 18 click board™.
 * @param[in] ctx : Click context object.
 * @param[in] resolution : 
 *         @li @c 0x00 ( TEMPHUM18_RESOLUTION_8_BITS )  - 8 bit resolution,
 *         @li @c 0x01 ( TEMPHUM18_RESOLUTION_10_BITS ) - 10 bit resolution,
 *         @li @c 0x02 ( TEMPHUM18_RESOLUTION_12_BITS ) - 12 bit resolution,
 *         @li @c 0x03 ( TEMPHUM18_RESOLUTION_14_BITS ) - 14 bit resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The function performs a delay of approximately 14 milliseconds.
 */
err_t temphum18_set_relative_humidity_resolution ( temphum18_t *ctx, uint8_t resolution );

/**
 * @brief Temp&Hum 18 set relative temperature resolution function.
 * @details This function sets desired relative temperature resolution
 * of the HS3003 High Performance Relative Humidity and Temperature Sensor
 * on the  Temp&Hum 18 click board™.
 * @param[in] ctx : Click context object.
 * @param[in] resolution : 
 *         @li @c 0x00 ( TEMPHUM18_RESOLUTION_8_BITS )  - 8 bit resolution,
 *         @li @c 0x01 ( TEMPHUM18_RESOLUTION_10_BITS ) - 10 bit resolution,
 *         @li @c 0x02 ( TEMPHUM18_RESOLUTION_12_BITS ) - 12 bit resolution,
 *         @li @c 0x03 ( TEMPHUM18_RESOLUTION_14_BITS ) - 14 bit resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The function performs a delay of approximately 14 milliseconds.
 */
err_t temphum18_set_temperature_resolution ( temphum18_t *ctx, uint8_t resolution );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM18_H

/*! @} */ // temphum18

// ------------------------------------------------------------------------ END
