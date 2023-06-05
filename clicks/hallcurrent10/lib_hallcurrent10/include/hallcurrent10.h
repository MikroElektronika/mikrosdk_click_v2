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
 * @file hallcurrent10.h
 * @brief This file contains API for Hall Current 10 Click Driver.
 */

#ifndef HALLCURRENT10_H
#define HALLCURRENT10_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup hallcurrent10 Hall Current 10 Click Driver
 * @brief API for configuring and manipulating Hall Current 10 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent10_set Hall Current 10 Registers Settings
 * @brief Settings for registers of Hall Current 10 Click driver.
 */

/**
 * @addtogroup hallcurrent10_set
 * @{
 */

/**
 * @brief Hall Current 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 10 Click driver.
 */
#define HALLCURRENT10_SET_DEV_ADDR     0x4D

/*! @} */ // hallcurrent10_set

/**
 * @defgroup hallcurrent10_map Hall Current 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 10 Click driver.
 */

/**
 * @addtogroup hallcurrent10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 10 Click to the selected MikroBUS.
 */
#define HALLCURRENT10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // hallcurrent10_map
/*! @} */ // hallcurrent10

/**
 * @brief Hall Current 10 Click context object.
 * @details Context object definition of Hall Current 10 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;     /**< Device slave address (used for I2C driver). */

} hallcurrent10_t;

/**
 * @brief Hall Current 10 Click configuration object.
 * @details Configuration object definition of Hall Current 10 Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} hallcurrent10_cfg_t;

/**
 * @brief Hall Current 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HALLCURRENT10_OK = 0,
   HALLCURRENT10_ERROR = -1

} hallcurrent10_return_value_t;

/*!
 * @addtogroup hallcurrent10 Hall Current 10 Click Driver
 * @brief API for configuring and manipulating Hall Current 10 Click driver.
 * @{
 */

/**
 * @brief Hall Current 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent10_cfg_setup ( hallcurrent10_cfg_t *cfg );

/**
 * @brief Hall Current 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent10_init ( hallcurrent10_t *ctx, hallcurrent10_cfg_t *cfg );

/**
 * @brief Hall Current 10 default configuration function.
 * @details This function executes a default configuration of Hall Current 10
 * click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hallcurrent10_default_cfg ( hallcurrent10_t *ctx );

/**
 * @brief Hall Current 10 I2C ADC reading function.
 * @details This function reads 12-bit ADC data
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallcurrent10_t object definition for detailed explanation.
 * @param[out] read_adc : Output ADC read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent10_read_adc ( hallcurrent10_t *ctx, uint16_t *read_adc );

/**
 * @brief Hall Current 10 get ADC voltage function.
 * @details This function reads 12-bit ADC data and calculate ADC voltage ( mV )
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallcurrent10_t object definition for detailed explanation.
 * @param[out] adc_vtg : Output ADC voltage ( mV ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent10_get_adc_voltage ( hallcurrent10_t *ctx, float *adc_vtg );

/**
 * @brief Hall Current 10 get current function.
 * @details This function reads 12-bit ADC data and calculate current ( mA )
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallcurrent10_t object definition for detailed explanation.
 * @param[out] current : Current ( mA ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent10_get_current ( hallcurrent10_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT10_H

/*! @} */ // hallcurrent10

// ------------------------------------------------------------------------ END
