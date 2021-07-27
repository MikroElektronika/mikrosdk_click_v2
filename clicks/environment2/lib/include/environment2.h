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
 * @file environment2.h
 * @brief This file contains API for Environment 2 Click Driver.
 */

#ifndef ENVIRONMENT2_H
#define ENVIRONMENT2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup environment2 Environment 2 Click Driver
 * @brief API for configuring and manipulating Environment 2 Click driver.
 * @{
 */

/**
 * @defgroup environment2_reg Environment 2 Registers List
 * @brief List of registers of Environment 2 Click driver.
 */

/**
 * @addtogroup environment2_cmd
 * @{
 */

/**
 * @brief Environment 2 SGP40 description commands.
 * @details Specified SGP40 commands for description of Environment 2 Click driver.
 */
#define ENVIRONMENT2_SGP40_CMD_MEASURE_RAW                       0x260F
#define ENVIRONMENT2_SGP40_CMD_MEASURE_TEST                      0x280E 
#define ENVIRONMENT2_SGP40_CMD_HEATER_OFF                        0x3615
#define ENVIRONMENT2_SGP40_CMD_SOFT_RESET                        0x0006

/**
 * @brief Environment 2 SHT40 description commands.
 * @details Specified SHT40 commands for description of Environment 2 Click driver.
 */
#define ENVIRONMENT2_SHT40_CMD_MEASURE_T_RH_HIGH_PRECISION       0xFD
#define ENVIRONMENT2_SHT40_CMD_MEASURE_T_RH_MEDIUM_PRECISION     0xF6
#define ENVIRONMENT2_SHT40_CMD_MEASURE_T_RH_LOWEST_PRECISION     0xE0
#define ENVIRONMENT2_SHT40_CMD_READ_SERIAL                       0x89
#define ENVIRONMENT2_SHT40_CMD_SOFT_RESET                        0x94
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_HIGHEST_HEATER_1SEC      0x39
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_HIGHEST_HEATER_0_1SEC    0x32
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_MEDIUM_HEATER_1SEC       0x2F
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_MEDIUM_HEATER_0_1SEC     0x24
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_LOWEST_HEATER_1SEC       0x1E
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_LOWEST_HEATER_0_1SEC     0x15

/*! @} */ // environment2_cmd

/**
 * @defgroup environment2_set Environment 2 Registers Settings
 * @brief Settings for registers of Environment 2 Click driver.
 */

/**
 * @addtogroup environment2_set
 * @{
 */

/**
 * @brief Environment 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Environment 2 Click driver.
 */
#define ENVIRONMENT2_SGP40_SET_DEV_ADDR                          0x59
#define ENVIRONMENT2_SHT40_SET_DEV_ADDR                          0x44

/**
 * @brief Environment 2 device selection.
 * @details Specified selection for device slave address of
 * Environment 2 Click driver.
 */
#define ENVIRONMENT2_SEL_SGP40                                   0x00
#define ENVIRONMENT2_SEL_SHT40                                   0x01

/*! @} */ // environment2_set

/**
 * @addtogroup environment2_get
 * @{
 */

/**
 * @brief Environment 2 SGP40 description setting.
 * @details Specified SGP40 setting for description of Environment 2 Click driver.
 */
#define ENVIRONMENT2_SGP40_TEST_PASSED                           0xD400
#define ENVIRONMENT2_SGP40_TEST_FAILED                           0x4B00


/*! @} */ // environment2_get

/**
 * @defgroup environment2_map Environment 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Environment 2 Click driver.
 */

/**
 * @addtogroup environment2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Environment 2 Click to the selected MikroBUS.
 */
#define ENVIRONMENT2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // environment2_map
/*! @} */ // environment2

/**
 * @brief Environment 2 Click context object.
 * @details Context object definition of Environment 2 Click driver.
 */
typedef struct
{
    // Modules

    i2c_master_t i2c;         /**< I2C driver object. */
                              
    // I2C slave address      
                              
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
                          
} environment2_t;

/**
 * @brief Environment 2 Click configuration object.
 * @details Configuration object definition of Environment 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} environment2_cfg_t;

/**
 * @brief Environment 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ENVIRONMENT2_OK = 0,
    ENVIRONMENT2_ERROR = -1

} environment2_return_value_t;

/*!
 * @addtogroup environment2 Environment 2 Click Driver
 * @brief API for configuring and manipulating Environment 2 Click driver.
 * @{
 */

/**
 * @brief Environment 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #environment2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void environment2_cfg_setup ( environment2_cfg_t *cfg );

/**
 * @brief Environment 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #environment2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_init ( environment2_t *ctx, environment2_cfg_t *cfg );

/**
 * @brief Environment 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[in] select_device : Device selection.
 * @param[in] cmd : Command to be written.
 * @param[in] tx_buf : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_generic_write ( environment2_t *ctx, uint8_t select_device, uint16_t cmd, uint8_t *tx_buf );

/**
 * @brief Environment 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[in] select_device : Device selection.
 * @param[in] cmd : Command to be written.
 * @param[out] rx_buf : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_generic_read ( environment2_t *ctx, uint8_t select_device, uint16_t cmd, uint8_t *rx_buf );

/**
 * @brief Environment 2 get temperature and relative humidity function.
 * @details This function reads a temperature and relative humidity from the
 * SHT40 4th Generation, High-Accuracy, Ultra-Low-Power, 16-bit
 * Relative Humidity and Temperature Sensor Platform
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[out] humidity    : Relative Humidity.
 * @param[out] temperature : Temperature.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_get_temp_hum ( environment2_t *ctx, float *humidity, float *temperature );

/**
 * @brief Environment 2 get air quality data function.
 * @details This function reads a air quality SRAW data from the
 * SGP40 Indoor Air Quality Sensor for VOC Measurements
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[out] air_quality    : Air quality SRAW data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_get_air_quality ( environment2_t *ctx, uint16_t *air_quality );

/**
 * @brief Environment 2 SGP40 measurement test function.
 * @details This function triggers the built-in self-test checking
 * for integrity of both hotplate and MOX materia of the
 * SGP40 Indoor Air Quality Sensor for VOC Measurements
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @return Result of this test:
 *         @li @c 0xD400 ( ENVIRONMENT2_SGP40_TEST_PASSED ) - All tests passed successfully,
 *         @li @c 0x4B00 ( ENVIRONMENT2_SGP40_TEST_FAILED ) - One or more tests have failed.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint16_t environment2_sgp40_measure_test ( environment2_t *ctx );

/**
 * @brief Environment 2 heater off function.
 * @details This function turns the hotplate off and stops the measurement of the
 * SGP40 Indoor Air Quality Sensor for VOC Measurements
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_sgp40_heater_off ( environment2_t *ctx );

/**
 * @brief Environment 2 soft reset function.
 * @details This function general call resetting all devices connected to the same I2C bus of the
 * SGP40 Indoor Air Quality Sensor for VOC Measurements.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The first byte refers to the general call address 
 * and the second byte refers to the reset command.
 * After calling this command, the SGP40 will restart entering the idle mode.
 *
 * @endcode
 */
err_t environment2_sgp40_soft_reset ( environment2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ENVIRONMENT2_H

/*! @} */ // environment2

// ------------------------------------------------------------------------ END
