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
 * @file barometer5.h
 * @brief This file contains API for Barometer 5 Click Driver.
 */

#ifndef BAROMETER5_H
#define BAROMETER5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"


/*!
 * @addtogroup barometer5 Barometer 5 Click Driver
 * @brief API for configuring and manipulating Barometer 5 Click driver.
 * @{
 */

/**
 * @defgroup barometer5_reg Barometer 5 Command List
 * @brief List of commands of Barometer 5 Click driver.
 */

/**
 * @addtogroup barometer5_cmd
 * @{
 */

/**
 * @brief Barometer 5 description commands.
 * @details Specified commands for description of Barometer 5 Click driver.
 */
#define BAROMETER5_CMD_RESET                           0x1E
#define BAROMETER5_CMD_CONV_D1_OSR_256                 0x40
#define BAROMETER5_CMD_CONV_D1_OSR_512                 0x42
#define BAROMETER5_CMD_CONV_D1_OSR_1024                0x44
#define BAROMETER5_CMD_CONV_D1_OSR_2048                0x46
#define BAROMETER5_CMD_CONV_D1_OSR_4096                0x48
#define BAROMETER5_CMD_CONV_D2_OSR_256                 0x50
#define BAROMETER5_CMD_CONV_D2_OSR_512                 0x52
#define BAROMETER5_CMD_CONV_D2_OSR_1024                0x54
#define BAROMETER5_CMD_CONV_D2_OSR_2048                0x56
#define BAROMETER5_CMD_CONV_D2_OSR_4096                0x58
#define BAROMETER5_CMD_ADC_READ                        0x00
#define BAROMETER5_CMD_PROM_READ_START                 0xA0

/*! @} */ // barometer5_reg

/**
 * @defgroup barometer5_set Barometer 5 Registers Settings
 * @brief Settings for registers of Barometer 5 Click driver.
 */

/**
 * @addtogroup barometer5_set
 * @{
 */

/**
 * @brief Barometer 5 description setting.
 * @details Specified setting for description of Barometer 5 Click driver.
 */
#define BAROMETER5_RATIO_256                           0x00       
#define BAROMETER5_RATIO_512                           0x01
#define BAROMETER5_RATIO_1024                          0x02
#define BAROMETER5_RATIO_2048                          0x03
#define BAROMETER5_RATIO_4096                          0x04

/**
 * @brief Barometer 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 5 Click driver.
 */
#define BAROMETER5_SET_DEV_ADDR                        0x76

/*! @} */ // barometer5_set

/**
 * @defgroup barometer5_map Barometer 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 5 Click driver.
 */

/**
 * @addtogroup barometer5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 5 Click to the selected MikroBUS.
 */
#define BAROMETER5_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // barometer5_map
/*! @} */ // barometer5

/**
 * @brief Barometer 5 Click context object.
 * @details Context object definition of Barometer 5 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;             /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;        /**< Device slave address (used for I2C driver). */
    
    float sea_lvl_pressure;       /**< Sea-level pressure. */
    
    uint16_t press_sens_c1;       /**< Pressure sensitivity. */
    uint16_t press_off_c2;        /**< Pressure offset. */
    uint16_t press_tcs_c3;        /**< Temperature coefficient of pressure sensitivity. */
    uint16_t press_tco_c4;        /**< Temperature coefficient of pressure offset. */
    uint16_t press_tref_c5;       /**< Reference temperature. */
    uint16_t press_tempsens_c6;   /**< Temperature coefficient of the temperature. */
    
    uint8_t ratio_temp;           /**< Temperature ratio. */
    uint8_t ratio_press;          /**< Pressure ratio. */

} barometer5_t;

/**
 * @brief Barometer 5 Click configuration object.
 * @details Configuration object definition of Barometer 5 Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */
    
    float sea_level_pressure; /**< Sea-level pressure. */

} barometer5_cfg_t;

/**
 * @brief Barometer 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER5_OK = 0,
    BAROMETER5_ERROR = -1

} barometer5_return_value_t;

/*!
 * @addtogroup barometer5 Barometer 5 Click Driver
 * @brief API for configuring and manipulating Barometer 5 Click driver.
 * @{
 */

/**
 * @brief Barometer 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer5_cfg_setup ( barometer5_cfg_t *cfg );

/**
 * @brief Barometer 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer5_init ( barometer5_t *ctx, barometer5_cfg_t *cfg );

/**
 * @brief Barometer 5 default configuration function.
 * @details This function executes a default configuration of Barometer 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t barometer5_default_cfg ( barometer5_t *ctx );

/**
 * @brief Barometer 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer5_generic_write ( barometer5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Barometer 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer5_generic_read ( barometer5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Barometer 5 set command function.
 * @details This function writes a desired command
 * of the MS5637 Low Voltage Barometric Pressure Sensor  
 * on the Barometer 5 click board™.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer5_set_command ( barometer5_t *ctx, uint8_t cmd );

/**
 * @brief Barometer 5 set data ratio function.
 * @details This function sets data ratio
 * of the MS5637 Low Voltage Barometric Pressure Sensor  
 * on the Barometer 5 click board™.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[in] temp_ratio : Determines oversampling ratio for temperature measurement.
 * @param[in] press_ratio : Determines oversampling ration for pressure measurement.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer5_set_ratio ( barometer5_t *ctx, uint8_t temp_ratio, uint8_t press_ratio );

/**
 * @brief Barometer 5 software reset function.
 * @details This function performs a software reset
 * of the MS5637 Low Voltage Barometric Pressure Sensor  
 * on the Barometer 5 click board™.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a reset - reload delay of the 3 milliseconds.
 */
err_t barometer5_sw_reset ( barometer5_t *ctx );

/**
 * @brief Barometer 5 get calibration data function.
 * @details This function read and store calibration data
 * of the MS5637 Low Voltage Barometric Pressure Sensor  
 * on the Barometer 5 click board™.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 10 milliseconds.
 */
err_t barometer5_get_calibration_data ( barometer5_t *ctx );

/**
 * @brief Barometer 5 get raw data function.
 * @details This function read raw temperature and pressure data
 * of the MS5637 Low Voltage Barometric Pressure Sensor  
 * on the Barometer 5 click board™.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[out] temp_data : Raw temperature data.
 * @param[out] press_data : Raw pressure data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 20 milliseconds.
 */
err_t barometer5_get_raw_data ( barometer5_t *ctx, uint32_t *temp_data, uint32_t *press_data );

/**
 * @brief Barometer 5 get temperature data function.
 * @details This function read temperature data and convert to the degree Celsius
 * of the MS5637 Low Voltage Barometric Pressure Sensor  
 * on the Barometer 5 click board™.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degree Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 10 milliseconds.
 */
err_t barometer5_get_temperature ( barometer5_t *ctx, float *temperature );

/**
 * @brief Barometer 5 get pressure data function.
 * @details This function read pressure data and convert to the mbar
 * of the MS5637 Low Voltage Barometric Pressure Sensor  
 * on the Barometer 5 click board™.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[out] pressure : Pressure in mbar.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 10 milliseconds.
 */
err_t barometer5_get_pressure ( barometer5_t *ctx, float *pressure );

/**
 * @brief Barometer 5 calculate altitude function.
 * @details This function read pressure and temperature data 
 * and calculate altitude data,
 * depending on the temperature and pressure data, function calculates altitude in meters
 * of the MS5637 Low Voltage Barometric Pressure Sensor  
 * on the Barometer 5 click board™.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[out] altitude : Altitude data in meters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 20 milliseconds.
 */
err_t barometer5_calculate_altitude ( barometer5_t *ctx, float *altitude );

/**
 * @brief Barometer 5 get data function.
 * @details This function read temperature and pressure data, 
 * convert temperature data to the degree Celsius and pressure data to the mbar 
 * of the MS5637 Low Voltage Barometric Pressure Sensor  
 * on the Barometer 5 click board™.
 * @param[in] ctx : Click context object.
 * See #barometer5_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degree Celsius.
 * @param[out] pressure : Pressure in mbar..
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Executes a ADC conversion delay of the 10 milliseconds.
 */
err_t barometer5_get_data ( barometer5_t *ctx, float *temperature, float *pressure );


#ifdef __cplusplus
}
#endif
#endif // BAROMETER5_H

/*! @} */ // barometer5

// ------------------------------------------------------------------------ END
