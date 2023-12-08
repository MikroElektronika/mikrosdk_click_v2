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
 * @file pressure14.h
 * @brief This file contains API for Pressure 14 Click Driver.
 */

#ifndef PRESSURE14_H
#define PRESSURE14_H

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
 * @addtogroup pressure14 Pressure 14 Click Driver
 * @brief API for configuring and manipulating Pressure 14 Click driver.
 * @{
 */

/**
 * @defgroup pressure14_stat_reg Pressure 14 Status Registers List
 * @brief List of registers of Pressure 14 Click driver.
 */

/**
 * @addtogroup pressure14_stat_reg
 * @{
 */

/**
 * @brief Pressure 14 description status register.
 * @details Specified status register for description of Pressure 14 Click driver.
 */
#define PRESSURE14_STATUS_PWR_IND                               0x40
#define PRESSURE14_STATUS_BUSY_FLAG                             0x20
#define PRESSURE14_STATUS_ERR_FLAG                              0x04
#define PRESSURE14_STATUS_MATH_SAT                              0x01

/*! @} */ // pressure14_stat_reg

/**
 * @addtogroup pressure14_pressure_conversion_units
 * @{
 */

/**
 * @brief Pressure 14 description pressure conversion units.
 * @details Specified pressure conversion units for description of Pressure 14 Click driver.
 */
#define PRESSURE14_CONV_UNIT_PSI                                0x00
#define PRESSURE14_CONV_UNIT_PASCAL                             0x01
#define PRESSURE14_CONV_UNIT_KILOPASCAL                         0x02
#define PRESSURE14_CONV_UNIT_MMHG                               0x03
#define PRESSURE14_CONV_UNIT_INHG                               0x04
#define PRESSURE14_CONV_UNIT_ATMOSPHERIC                        0x05
#define PRESSURE14_CONV_UNIT_MILIBAR                            0x06
#define PRESSURE14_CONV_UNIT_BAR                                0x07
                                                               
/*! @} */ // pressure14_pressure_conversion_units

/**
 * @addtogroup pressure14_temperature_conversion_units
 * @{
 */
/**
 * @brief Pressure 14 description temperature conversion units.
 * @details Specified temperature conversion units for description of Pressure 14 Click driver.
 */
#define PRESSURE14_CONV_UNIT_CELSIUS                            0x00
#define PRESSURE14_CONV_UNIT_KELVIN                             0x01
#define PRESSURE14_CONV_UNIT_FAHRENHEIT                         0x02
                                                               
/*! @} */ // pressure14_temperature_conversion_units

/**
 * @addtogroup pressure14_pressure_conversion_constants
 * @{
 */

/**
 * @brief Pressure 14 description pressure conversion constants.
 * @details Specified pressure conversion constant for description of Pressure 14 Click driver.
 */
#define PRESSURE14_CONST_PSI                                    1.00000
#define PRESSURE14_CONST_PASCAL                                 6894.76
#define PRESSURE14_CONST_KILOPASCAL                             6.89476
#define PRESSURE14_CONST_MMHG                                   51.7149
#define PRESSURE14_CONST_INHG                                   2.03602
#define PRESSURE14_CONST_ATMOSPHERIC                            0.06805
#define PRESSURE14_CONST_MILIBAR                                68.9500
#define PRESSURE14_CONST_BAR                                    0.06895
                                                               
/*! @} */ // pressure14_pressure_conversion_constants

/**
 * @addtogroup pressure14_temperature_conversion_constants
 * @{
 */
/**
 * @brief Pressure 14 description temperature conversion constants.
 * @details Specified temperature conversion constant for description of Pressure 14 Click driver.
 */
#define PRESSURE14_CONST_ADDI_CELS                              0.00000
#define PRESSURE14_CONST_MULT_CELS                              1.00000
#define PRESSURE14_CONST_ADDI_KELV                              273.150
#define PRESSURE14_CONST_MULT_KELV                              1.00000
#define PRESSURE14_CONST_ADDI_FAHR                              32.0000
#define PRESSURE14_CONST_MULT_FAHR                              1.80000

/*! @} */ // pressure14_temperature_conversion_constants

/**
 * @addtogroup pressure14_general_sensor_constants
 * @{
 */
/**
 * @brief Pressure 14 description general sensor constants.
 * @details Specified general sensor constant for description of Pressure 14 Click driver.
 */
#define PRESSURE14_CONST_PRESS_OUT_MIN                          1677722.00
#define PRESSURE14_CONST_PRESS_OUT_MAX                          13421772.0
#define PRESSURE14_CONST_PRESS_VAL_MIN                          0.00000000
#define PRESSURE14_CONST_PRESS_VAL_MAX                          60.0000000
#define PRESSURE14_CONST_TEMP_MIN                               -50.000000
#define PRESSURE14_CONST_TEMP_MAX                               150.000000
#define PRESSURE14_CONST_TEMP_OUT_MAX                           16777215.0

#define PRESSURE14_CMD_OUT_MEAS                                 0xAA
#define PRESSURE14_CMD_DUMMY                                    0x00

/*! @} */ // pressure14_general_sensor_constants

/**
 * @defgroup pressure14_set Pressure 14 Registers Settings
 * @brief Settings for registers of Pressure 14 Click driver.
 */

/**
 * @addtogroup pressure14_set
 * @{
 */

/**
 * @brief Pressure 14 description setting.
 * @details Specified setting for description of Pressure 14 Click driver.
 */
//

/**
 * @brief Pressure 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 14 Click driver.
 */
#define PRESSURE14_SET_DEV_ADDR                                 0x28

/*! @} */ // pressure14_set

/**
 * @defgroup pressure14_map Pressure 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 14 Click driver.
 */

/**
 * @addtogroup pressure14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 14 Click to the selected MikroBUS.
 */
#define PRESSURE14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure14_map
/*! @} */ // pressure14

/**
 * @brief Pressure 14 Click context object.
 * @details Context object definition of Pressure 14 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;       /**< Description. */

    // Modules
    i2c_master_t i2c;            /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;       /**< Device slave address (used for I2C driver). */

} pressure14_t;

/**
 * @brief Pressure 14 Click configuration object.
 * @details Configuration object definition of Pressure 14 Click driver.
 */
typedef struct
{                               
    pin_name_t  scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;         /**< Description. */

    uint32_t  i2c_speed;         /**< I2C serial speed. */
    uint8_t   i2c_address;       /**< I2C slave address. */

} pressure14_cfg_t;

/**
 * @brief Pressure 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   PRESSURE14_OK = 0,
   PRESSURE14_ERROR = -1

} pressure14_return_value_t;

/*!
 * @addtogroup pressure14 Pressure 14 Click Driver
 * @brief API for configuring and manipulating Pressure 14 Click driver.
 * @{
 */

/**
 * @brief Pressure 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure14_cfg_setup ( pressure14_cfg_t *cfg );

/**
 * @brief Pressure 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pressure14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure14_init ( pressure14_t *ctx, pressure14_cfg_t *cfg );

/**
 * @brief Pressure 14 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure14_generic_write ( pressure14_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Pressure 14 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure14_generic_read ( pressure14_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Pressure 14 output Measurement Command function.
 * @details This function sends output measurement command that causes the
 * ABP2 series pressure sensor to exit standby mode and enter operating mode.
 * @param[in] ctx : Click context object.
 * See #pressure14_t object definition for detailed explanation.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void pressure14_measure_cmd ( pressure14_t *ctx );

/**
 * @brief Pressure 14 checks INT pin state function.
 * @details This function returns the INT pin state which indicates the
 * End-of-conversion for ABP2 series pressure sensor on Pressure 14 click board.
 * @param[in] ctx : Click context object.
 * See #pressure14_t object definition for detailed explanation.
 * @return INT pin state.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t pressure14_check_busy_flag_int ( pressure14_t *ctx );

/**
 * @brief Pressure 14 read pressure and temperature function.
 * @details This function reads 24-bit pressure, 24-bit temperature data
 * and 8-bit status register from the ABP2 series pressure sensor on Pressure 14 click board.
 * @param[in] ctx : Click context object.
 * See #pressure14_t object definition for detailed explanation.
 * @param[in] status_byte : Pointer to the memory location where the 8-bit status will be stored.
 * @param[out] pressure_data : Pointer to the memory location where the raw pressure data will be stored.
 * @param[in] temp_data : Pointer to the memory location where the raw temperature data will be stored.
 * @return Nothing.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void pressure14_read_press_and_temp ( pressure14_t *ctx, uint8_t *status_byte, uint32_t *pressure_data, uint32_t *temp_data );

/**
 * @brief Pressure 14 calculate pressure function.
 * @details This function calculates raw pressure data acquired from the
 * ABP2 series pressure sensor on Pressure 14 click board, and converts the result into preferred unit.
 * @param[in] pressure_raw : Input parameter of raw pressure to be converted into a more meaningful value.
 * @param[in] conv_unit : Preferred conversion unit for measured pressure.
 * @return The result of the calculation pressure.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
float pressure14_get_pressure ( uint32_t pressure_raw, uint8_t conv_unit );


/**
 * @brief Pressure 14 calculate temperature function.
 * @details This function calculates raw temperature data acquired from the
 * ABP2 series pressure sensor on Pressure 14 click board,
 * and converts the result into preferred unit.
 * @param[in] temperature_raw : input parameter of raw temperature to be converted into a more meaningful value.
 * @param[out] conv_unit : Preferred conversion unit for measured temperature.
 * @return The result of the calculation temperature.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
float pressure14_get_temperature ( uint32_t temperature_raw, uint8_t conv_unit );
#ifdef __cplusplus
}
#endif
#endif // PRESSURE14_H

/*! @} */ // pressure14

// ------------------------------------------------------------------------ END
