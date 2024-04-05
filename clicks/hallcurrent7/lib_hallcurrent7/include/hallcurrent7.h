/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file hallcurrent7.h
 * @brief This file contains API for Hall Current 7 Click Driver.
 */

#ifndef HALLCURRENT7_H
#define HALLCURRENT7_H

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
 * @addtogroup hallcurrent7 Hall Current 7 Click Driver
 * @brief API for configuring and manipulating Hall Current 7 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent7_set Hall Current 7 Registers Settings
 * @brief Settings for registers of Hall Current 7 Click driver.
 */

/**
 * @addtogroup hallcurrent7_set
 * @{
 */

/**
 * @brief Hall Current 7 description setting.
 * @details Specified setting for description of Hall Current 7 Click driver.
 */
#define HALLCURRENT7_RESOLUTION                 4096
#define HALLCURRENT7_12_BIT_DATA              0x0FFF
#define HALLCURRENT7_ADC_NUM_OF_MEASURE        100.0
#define HALLCURRENT7_VREF_5000_mV             5000.0

#define HALLCURRENT7_ACS770LCB_050B_SENS        0.04

#define HALLCURRENT7_ERR_COR_FACTOR             1.05

/**
 * @brief Hall Current 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 7 Click driver.
 */
#define HALLCURRENT7_SET_DEV_ADDR              0x4D

/*! @} */ // hallcurrent7_set

/**
 * @defgroup hallcurrent7_map Hall Current 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 7 Click driver.
 */

/**
 * @addtogroup hallcurrent7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 7 Click to the selected MikroBUS.
 */
#define HALLCURRENT7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // hallcurrent7_map
/*! @} */ // hallcurrent7

/**
 * @brief Hall Current 7 Click context object.
 * @details Context object definition of Hall Current 7 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} hallcurrent7_t;

/**
 * @brief Hall Current 7 Click configuration object.
 * @details Configuration object definition of Hall Current 7 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} hallcurrent7_cfg_t;

/**
 * @brief Hall Current 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HALLCURRENT7_OK = 0,
   HALLCURRENT7_ERROR = -1

} hallcurrent7_return_value_t;

/*!
 * @addtogroup hallcurrent7 Hall Current 7 Click Driver
 * @brief API for configuring and manipulating Hall Current 7 Click driver.
 * @{
 */

/**
 * @brief Hall Current 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent7_cfg_setup ( hallcurrent7_cfg_t *cfg );

/**
 * @brief Hall Current 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hallcurrent7_init ( hallcurrent7_t *ctx, hallcurrent7_cfg_t *cfg );

/**
 * @brief Hall Current 7 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallcurrent7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hallcurrent7_generic_write ( hallcurrent7_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Hall Current 7 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallcurrent7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hallcurrent7_generic_read ( hallcurrent7_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Read data function.
 * @details Function is used to read raw data from MCP3221.
 * @param[in] ctx : Click context object.
 * See #hallcurrent7_t object definition for detailed explanation.
 * @returns Result 16-bit value that represents ADC value from output register
**/
uint16_t hallcurrent7_read_data ( hallcurrent7_t *ctx );

/**
 * @brief Read voltage function.
 * @details Function is used to calculate raw output voltage.
 * @param[in] ctx : Click context object.
 * See #hallcurrent7_t object definition for detailed explanation.
 * @param[in] v_ref : 16-bit value representing power supply voltage.
 * @returns Result 12-bit value that represents voltage in millivolts.
**/
uint16_t hallcurrent7_read_voltage ( hallcurrent7_t *ctx, uint16_t v_ref );

/**
 * @brief Calculate current function.
 * @details Function is used to calculate current.
 * @param[in] ctx : Click context object.
 * See #hallcurrent7_t object definition for detailed explanation.
 * @param[in] v_ref : 16-bit value representing power supply voltage.
 * @returns Result 16-bit value that represents current in amps.
**/
int16_t hallcurrent7_calc_current ( hallcurrent7_t *ctx, uint16_t v_ref );

/**
 * @brief Calculate Average current function.
 * @details Function is used to calculate average current and correct for output error.
 * @param[in] ctx : Click context object.
 * See #hallcurrent7_t object definition for detailed explanation.
 * @param[in] v_ref : 16-bit value representing power supply voltage.
 * @returns Result 16-bit value that represents current in amps.
**/
int16_t hallcurrent7_avg_current ( hallcurrent7_t *ctx, uint16_t v_ref );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT7_H

/*! @} */ // hallcurrent7

// ------------------------------------------------------------------------ END
