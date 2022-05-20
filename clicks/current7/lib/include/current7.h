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
 * @file current7.h
 * @brief This file contains API for Current 7 Click Driver.
 */

#ifndef CURRENT7_H
#define CURRENT7_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_i2c_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup current7 Current 7 Click Driver
 * @brief API for configuring and manipulating Current 7 Click driver.
 * @{
 */

/**
 * @defgroup current7_reg Current 7 Registers List
 * @brief List of registers of Current 7 Click driver.
 */

/**
 * @defgroup current7_set Current 7 Registers Settings
 * @brief Settings for registers of Current 7 Click driver.
 */

/**
 * @addtogroup current7_set
 * @{
 */

/**
 * @brief Current 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Current 7 Click driver.
 */
#define CURRENT7_SET_DEV_ADDR             0x4D

/*! @} */ // current7_set

/**
 * @defgroup current7_map Current 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Current 7 Click driver.
 */

/**
 * @addtogroup current7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current 7 Click to the selected MikroBUS.
 */
#define CURRENT7_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // current7_map
/*! @} */ // current7

/**
 * @brief Current 7  Click driver selector.
 * @details Selects target driver interface of Current 7  Click driver.
 */
typedef enum
{
   CURRENT7_DRV_SEL_AN,      /**< AN driver descriptor. */
   CURRENT7_DRV_SEL_I2C       /**< I2C driver descriptor. */

} current7_drv_t;

/**
 * @brief Current 7  Click driver interface.
 * @details Definition of driver interface of Current 7  Click driver.
 */
typedef err_t ( *current7_master_io_t )( struct current7_s*, uint16_t* ); 

/**
 * @brief Current 7 Click context object.
 * @details Context object definition of Current 7 Click driver.
 */
typedef struct current7_s
{
    // Input pins
   analog_in_t  adc;                 /**< ADC module object. */

    // Modules
    i2c_master_t i2c;                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;            /**< Device slave address (used for I2C driver). */
    
    current7_drv_t  drv_sel;          /**< Master driver interface selector. */
    
    current7_master_io_t  read_adc_f; /**< Master write function. */
    
    uint16_t offset;                  /**< ADC offset. */

} current7_t;

/**
 * @brief Current 7 Click configuration object.
 * @details Configuration object definition of Current 7 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  an;         /**< Analog pin descriptor. */
    
    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */
    
    current7_drv_t  drv_sel;                /**< Master driver interface selector. */
    
    uint16_t adc_offset;                    /**< ADC offset. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} current7_cfg_t;

/**
 * @brief Current 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENT7_OK = 0,
    CURRENT7_ERROR = -1

} current7_return_value_t;

/*!
 * @addtogroup current7 Current 7 Click Driver
 * @brief API for configuring and manipulating Current 7 Click driver.
 * @{
 */

/**
 * @brief Current 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #current7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void current7_cfg_setup ( current7_cfg_t *cfg );

/**
 * @brief Current 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #current7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #current7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current7_init ( current7_t *ctx, current7_cfg_t *cfg );

/**
 * @brief Current 7 default configuration function.
 * @details This function executes a default configuration of Current 7
 * click board.
 * @param[in] ctx : Click context object.
 * See #current7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t current7_default_cfg ( current7_t *ctx );

/**
 * @brief Current 7 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current7_generic_write ( current7_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Current 7 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #current7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current7_generic_read ( current7_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Current 7 get ADC function.
 * @details This function reads 12-bit ADC data
 * of the INA282 High-Accuracy, Wide Common-Mode Range, Bidirectional
 * Current Shunt Monitors, Zero-Drift Series
 * on the Current 7 click board™.
 * @param[in] ctx : Click context object.
 * See #current7_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current7_get_adc ( current7_t *ctx, uint16_t *data_out );

/**
 * @brief Current 7 get ADC voltage function.
 * @details This function reads 12-bit ADC data and calculate ADC voltage ( V )
 * of the INA282 High-Accuracy, Wide Common-Mode Range, Bidirectional
 * Current Shunt Monitors, Zero-Drift Series
 * on the Current 7 click board™.
 * @param[in] ctx : Click context object.
 * See #current7_t object definition for detailed explanation.
 * @param[out] adc_vtg : Output ADC voltage ( V ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current7_get_adc_voltage ( current7_t *ctx, float *adc_vtg );

/**
 * @brief Current 7 get current function.
 * @details This function reads 12-bit ADC data and calculate current ( A )
 * of the INA282 High-Accuracy, Wide Common-Mode Range, Bidirectional
 * Current Shunt Monitors, Zero-Drift Series
 * on the Current 7 click board™.
 * @param[in] ctx : Click context object.
 * See #current7_t object definition for detailed explanation.
 * @param[out] current : Output current ( A ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current7_get_current ( current7_t *ctx, float *current );

/**
 * @brief Current 7 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #current7_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin ( V ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current7_read_an_pin_voltage ( current7_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // CURRENT7_H

/*! @} */ // current7

// ------------------------------------------------------------------------ END
