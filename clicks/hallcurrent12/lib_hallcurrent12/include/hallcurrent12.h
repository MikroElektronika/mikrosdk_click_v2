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
 * @file hallcurrent12.h
 * @brief This file contains API for Hall Current 12 Click Driver.
 */

#ifndef HALLCURRENT12_H
#define HALLCURRENT12_H

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

#include "drv_i2c_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup hallcurrent12 Hall Current 12 Click Driver
 * @brief API for configuring and manipulating Hall Current 12 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent12_set Hall Current 12 Registers Settings
 * @brief Settings for registers of Hall Current 12 Click driver.
 */

/**
 * @brief Hall Current 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 12 Click driver.
 */
#define HALLCURRENT12_SET_DEV_ADDR  0x4D

/*! @} */ // hallcurrent12_set

/**
 * @defgroup hallcurrent12_map Hall Current 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 12 Click driver.
 */

/**
 * @addtogroup hallcurrent12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 12 Click to the selected MikroBUS.
 */
#define HALLCURRENT12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );   \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // hallcurrent12_map
/*! @} */ // hallcurrent12

/**
 * @brief Hall Current 12 Click driver selector.
 * @details Selects target driver interface of Hall Current 12 Click driver.
 */
typedef enum
{
   HALLCURRENT12_DRV_SEL_AN,       /**< AN driver descriptor. */
   HALLCURRENT12_DRV_SEL_I2C       /**< I2C driver descriptor. */

} hallcurrent12_drv_t;

/**
 * @brief Hall Current 12 Click driver interface.
 * @details Definition of driver interface of Hall Current 12 Click driver.
 */
typedef err_t ( *hallcurrent12_master_io_t )( struct hallcurrent12_s*, float* ); 

/**
 * @brief Hall Current 12 Click context object.
 * @details Context object definition of Hall Current 12 Click driver.
 */
typedef struct hallcurrent12_s
{
    analog_in_t  adc;                       /**< ADC module object. */

    i2c_master_t i2c;                       /**< I2C driver object. */

    uint8_t slave_address;                  /**< Device slave address (used for I2C driver). */

    hallcurrent12_drv_t  drv_sel;           /**< Master driver interface selector. */

    hallcurrent12_master_io_t  read_adc_f;  /**< Master write function. */
    
    float offset;                           /**< Calibrated voltage offset. */

} hallcurrent12_t;

/**
 * @brief Hall Current 12 Click configuration object.
 * @details Configuration object definition of Hall Current 12 Click driver.
 */
typedef struct
{
    pin_name_t  an;                         /**< Analog pin descriptor. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

    pin_name_t  scl;                        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                    /**< I2C serial speed. */
    uint8_t   i2c_address;                  /**< I2C slave address. */

    hallcurrent12_drv_t  drv_sel;           /**< Master driver interface selector. */

} hallcurrent12_cfg_t;

/**
 * @brief Hall Current 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HALLCURRENT12_OK = 0,
   HALLCURRENT12_ERROR = -1

} hallcurrent12_return_value_t;

/*!
 * @addtogroup hallcurrent12 Hall Current 12 Click Driver
 * @brief API for configuring and manipulating Hall Current 12 Click driver.
 * @{
 */

/**
 * @brief Hall Current 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent12_cfg_setup ( hallcurrent12_cfg_t *cfg );

/**
 * @brief Hall Current 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent12_init ( hallcurrent12_t *ctx, hallcurrent12_cfg_t *cfg );

/**
 * @brief Hall Current 12 get ADC function.
 * @details This function reads ADC voltage ( V )
 * of the TMCS1100 1% High-Precision, Basic Isolation Hall-Effect Current Sensor
 * on the Hall Current 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent12_t object definition for detailed explanation.
 * @param[out] adc_vtg : Output ADC voltage ( V ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent12_get_adc ( hallcurrent12_t *ctx, float *adc_vtg );

/**
 * @brief Hall Current 12 get ADC voltage function.
 * @details This function reads 12-bit ADC data and calculate ADC voltage ( V ) 
 * of the TMCS1100 1% High-Precision, Basic Isolation Hall-Effect Current Sensor
 * on the Hall Current 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent12_t object definition for detailed explanation.
 * @param[out] adc_vtg : Output ADC voltage ( V ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent12_get_adc_voltage ( hallcurrent12_t *ctx, float *adc_vtg );

/**
 * @brief Hall Current 12 get current function.
 * @details This function reads 12-bit ADC data and calculate current ( A )
 * of the TMCS1100 1% High-Precision, Basic Isolation Hall-Effect Current Sensor
 * on the Hall Current 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent12_t object definition for detailed explanation.
 * @param[out] adc_vtg : Output current ( A ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent12_get_current ( hallcurrent12_t *ctx, float *current );

/**
 * @brief Hall Current 12 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent12_t object definition for detailed explanation.
 * @param[out] adc_vtg : Output voltage level of the analog pin ( V ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent12_get_pin_voltage ( hallcurrent12_t *ctx, float *adc_vtg );

/**
 * @brief Hall Current 12 calibration function.
 * @details This function calculates voltage offset when there's no input current applied.
 * @param[in] ctx : Click context object.
 * See #hallcurrent12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent12_calibration ( hallcurrent12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT12_H

/*! @} */ // hallcurrent12

// ------------------------------------------------------------------------ END
