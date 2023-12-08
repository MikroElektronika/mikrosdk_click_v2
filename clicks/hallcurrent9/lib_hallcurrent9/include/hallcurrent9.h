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
 * @file hallcurrent9.h
 * @brief This file contains API for Hall Current 9 Click Driver.
 */

#ifndef HALLCURRENT9_H
#define HALLCURRENT9_H

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
 * @addtogroup hallcurrent9 Hall Current 9 Click Driver
 * @brief API for configuring and manipulating Hall Current 9 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent9_reg Hall Current 9 Registers List
 * @brief List of registers of Hall Current 9 Click driver.
 */

/**
 * @defgroup hallcurrent9_set Hall Current 9 Registers Settings
 * @brief Settings for registers of Hall Current 9 Click driver.
 */

/**
 * @addtogroup hallcurrent9_set
 * @{
 */

/**
 * @brief Hall Current 9 description setting.
 * @details Specified setting for description of Hall Current 9 Click driver.
 */

/**
 * @brief Hall Current 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 9 Click driver.
 */
#define HALLCURRENT9_SET_DEV_ADDR    0x4D

/*! @} */ // hallcurrent9_set

/**
 * @defgroup hallcurrent9_map Hall Current 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 9 Click driver.
 */

/**
 * @addtogroup hallcurrent9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 9 Click to the selected MikroBUS.
 */
#define HALLCURRENT9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // hallcurrent9_map
/*! @} */ // hallcurrent9

/**
 * @brief Hall Current 9 Click context object.
 * @details Context object definition of Hall Current 9 Click driver.
 */
typedef struct
{
    // Input pins

    digital_in_t  an;         /**< Analog input pin. */

    // Modules

    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} hallcurrent9_t;

/**
 * @brief Hall Current 9 Click configuration object.
 * @details Configuration object definition of Hall Current 9 Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */
                              
    pin_name_t  an;           /**< Analog input pin. */
                              
    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} hallcurrent9_cfg_t;

/**
 * @brief Hall Current 9 Click calibration object.
 * @details Calibration object definition of Hall Current 9 Click driver.
 */
typedef struct
{
    uint16_t zero_adc_val;
    
} hallcurrent9_calibration_data_t;

/**
 * @brief Hall Current 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT9_OK = 0,
    HALLCURRENT9_ERROR = -1

} hallcurrent9_return_value_t;

/*!
 * @addtogroup hallcurrent9 Hall Current 9 Click Driver
 * @brief API for configuring and manipulating Hall Current 9 Click driver.
 * @{
 */

/**
 * @brief Hall Current 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void hallcurrent9_cfg_setup ( hallcurrent9_cfg_t *cfg );

/**
 * @brief Hall Current 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t hallcurrent9_init ( hallcurrent9_t *ctx, hallcurrent9_cfg_t *cfg );

/**
 * @brief Hall Current 9 I2C ADC reading function.
 * @details This function reads 12-bit ADC data 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallcurrent9_t object definition for detailed explanation.
 * @param[out] read_adc : Output ADC read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t hallcurrent9_read_adc ( hallcurrent9_t *ctx, uint16_t *read_adc );

/**
 * @brief Hall Current 9 set calibration function.
 * @details This function sets the calibration value into the calibration data structure 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adc11_t object definition for detailed explanation.
 * @param[out] adc_val : Pointer to the memory location of the structure where data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The function samples ADC 20 times in short intervals of 1 millisecond,
 * which makes the total delay in function approximately 20 millisecond.
 */
err_t hallcurrent9_set_calibration ( hallcurrent9_t *ctx, hallcurrent9_calibration_data_t *adc_val );

/**
 * @brief Hall Current 9 get current function.
 * @details This function reads 12-bit ADC data and calculate current ( mA ) 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallcurrent9_t object definition for detailed explanation.
 * @param[in] adc_val : Pointer to the memory location of the structure where data be stored.
 * @return Current (mA)
 *
 * See #err_t definition for detailed explanation.
 * @note Measurement delay of 100 milliseconds.
 *
 * @endcode
 */
float hallcurrent9_get_current ( hallcurrent9_t *ctx, hallcurrent9_calibration_data_t *adc_val );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT9_H

/*! @} */ // hallcurrent9

// ------------------------------------------------------------------------ END
