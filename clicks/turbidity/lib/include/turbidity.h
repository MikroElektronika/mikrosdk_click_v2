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
 * @file turbidity.h
 * @brief This file contains API for Turbidity Click Driver.
 */

#ifndef TURBIDITY_H
#define TURBIDITY_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup turbidity Turbidity Click Driver
 * @brief API for configuring and manipulating Turbidity Click driver.
 * @{
 */

/**
 * @defgroup turbidity_reg Turbidity Registers List
 * @brief List of registers of Turbidity Click driver.
 */

/**
 * @defgroup turbidity_set Turbidity Registers Settings
 * @brief Settings for registers of Turbidity Click driver.
 */

/**
 * @addtogroup turbidity_set
 * @{
 */

/**
 * @brief Turbidity device address setting.
 * @details Specified setting for device slave address selection of
 * Turbidity Click driver.
 */
#define TURBIDITY_SET_DEV_ADDR    0x4D

/*! @} */ // turbidity_set

/**
 * @defgroup turbidity_map Turbidity MikroBUS Map
 * @brief MikroBUS pin mapping of Turbidity Click driver.
 */

/**
 * @addtogroup turbidity_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Turbidity Click to the selected MikroBUS.
 */
#define TURBIDITY_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // turbidity_map
/*! @} */ // turbidity

/**
 * @brief Turbidity Click context object.
 * @details Context object definition of Turbidity Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} turbidity_t;

/**
 * @brief Turbidity Click configuration object.
 * @details Configuration object definition of Turbidity Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} turbidity_cfg_t;

/**
 * @brief Turbidity Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TURBIDITY_OK = 0,
    TURBIDITY_ERROR = -1

} turbidity_return_value_t;

/*!
 * @addtogroup turbidity Turbidity Click Driver
 * @brief API for configuring and manipulating Turbidity Click driver.
 * @{
 */

/**
 * @brief Turbidity configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #turbidity_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void turbidity_cfg_setup ( turbidity_cfg_t *cfg );

/**
 * @brief Turbidity initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #turbidity_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #turbidity_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t turbidity_init ( turbidity_t *ctx, turbidity_cfg_t *cfg );

/**
 * @brief Turbidity default configuration function.
 * @details This function executes a default configuration of Turbidity
 * click board.
 * @param[in] ctx : Click context object.
 * See #turbidity_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t turbidity_default_cfg ( turbidity_t *ctx );

/**
 * @brief Turbidity I2C reading function.
 * @details This function reads a desired number of data bytes starting 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #turbidity_t object definition for detailed explanation.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t turbidity_generic_read ( turbidity_t *ctx, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Turbidity read ADC function.
 * @details This function reads 12-bit ADC data of the 
 * TSD-10 Turbidity Sensor on the Turbidity click board™.
 * @param[in] ctx : Click context object.
 * See #turbidity_t object definition for detailed explanation.
 * @param[out] adc_val : Output 12-bit ADC data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t turbidity_read_adc ( turbidity_t *ctx, uint16_t *adc_val );

/**
 * @brief Turbidity get voltage function.
 * @details This function reads 12-bit ADC data and calculate the voltage of the 
 * TSD-10 Turbidity Sensor on the Turbidity click board™.
 * @param[in] ctx : Click context object.
 * See #turbidity_t object definition for detailed explanation.
 * @param[out] voltage : Voltage ( mV ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t turbidity_get_adc_voltage ( turbidity_t *ctx, float *voltage );

/**
 * @brief Turbidity get NTU function.
 * @details This function reads 12-bit ADC data and 
 * calculate the Nephelometric Turbidity Units ( NTU ) of the 
 * TSD-10 Turbidity Sensor on the Turbidity click board™.
 * @param[in] ctx : Click context object.
 * See #turbidity_t object definition for detailed explanation.
 * @param[out] ntu : NTU data ( from 0 to 4000 ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t turbidity_get_ntu ( turbidity_t *ctx, float *ntu );

#ifdef __cplusplus
}
#endif
#endif // TURBIDITY_H

/*! @} */ // turbidity

// ------------------------------------------------------------------------ END
