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
 * @file hallcurrent11.h
 * @brief This file contains API for Hall Current 11 Click Driver.
 */

#ifndef HALLCURRENT11_H
#define HALLCURRENT11_H

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
 * @addtogroup hallcurrent11 Hall Current 11 Click Driver
 * @brief API for configuring and manipulating Hall Current 11 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent11_set Hall Current 11 Registers Settings
 * @brief Settings for registers of Hall Current 11 Click driver.
 */

/**
 * @addtogroup hallcurrent11_set
 * @{
 */

/**
 * @brief Hall Current 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 11 Click driver.
 */
#define HALLCURRENT11_SET_DEV_ADDR  0x4D

/*! @} */ // hallcurrent11_set

/**
 * @defgroup hallcurrent11_map Hall Current 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 11 Click driver.
 */

/**
 * @addtogroup hallcurrent11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 11 Click to the selected MikroBUS.
 */
#define HALLCURRENT11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );   \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )


/*! @} */ // hallcurrent11_map
/*! @} */ // hallcurrent11

/**
 * @brief Hall Current 11 Click driver selector.
 * @details Selects target driver interface of Hall Current 11 Click driver.
 */
typedef enum
{
   HALLCURRENT11_DRV_SEL_AN,       /**< AN driver descriptor. */
   HALLCURRENT11_DRV_SEL_I2C       /**< I2C driver descriptor. */

} hallcurrent11_drv_t;

/**
 * @brief Hall Current 11 Click driver interface.
 * @details Definition of driver interface of Hall Current 11 Click driver.
 */
typedef err_t ( *hallcurrent11_master_io_t )( struct hallcurrent11_s*, uint16_t* ); 

/**
 * @brief Hall Current 11 Click context object.
 * @details Context object definition of Hall Current 11 Click driver.
 */
typedef struct hallcurrent11_s
{   
    analog_in_t  adc;                           /**< ADC module object. */

    i2c_master_t i2c;                           /**< I2C driver object. */

    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */
    
    hallcurrent11_drv_t  drv_sel;               /**< Master driver interface selector. */
    
    hallcurrent11_master_io_t  read_adc_f;      /**< Master write function. */

} hallcurrent11_t;

/**
 * @brief Hall Current 11 Click configuration object.
 * @details Configuration object definition of Hall Current 11 Click driver.
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
    
    hallcurrent11_drv_t  drv_sel;            /**< Master driver interface selector. */

} hallcurrent11_cfg_t;

/**
 * @brief Hall Current 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HALLCURRENT11_OK = 0,
   HALLCURRENT11_ERROR = -1

} hallcurrent11_return_value_t;

/*!
 * @addtogroup hallcurrent11 Hall Current 11 Click Driver
 * @brief API for configuring and manipulating Hall Current 11 Click driver.
 * @{
 */

/**
 * @brief Hall Current 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void hallcurrent11_cfg_setup ( hallcurrent11_cfg_t *cfg );

/**
 * @brief Hall Current 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t hallcurrent11_init ( hallcurrent11_t *ctx, hallcurrent11_cfg_t *cfg );

/**
 * @brief Hall Current 11 default configuration function.
 * @details This function executes a default configuration of Hall Current 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t hallcurrent11_default_cfg ( hallcurrent11_t *ctx );

/**
 * @brief Hall Current 11 ADC reading function.
 * @details This function reads 12-bit ADC data.
 * @param[in] ctx : Click context object.
 * See #hallcurrent11_t object definition for detailed explanation.
 * @param[out] read_adc : Output ADC read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t hallcurrent11_get_adc ( hallcurrent11_t *ctx, uint16_t *data_out );

/**
 * @brief Hall Current 11 get ADC voltage function.
 * @details This function reads 12-bit ADC data and calculate ADC voltage ( mV ).
 * @param[in] ctx : Click context object.
 * See #hallcurrent11_t object definition for detailed explanation.
 * @param[out] adc_vtg : Output ADC voltage ( mV ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t hallcurrent11_get_adc_voltage ( hallcurrent11_t *ctx, float *adc_vtg );

/**
 * @brief Hall Current 11 get current function.
 * @details This function reads 12-bit ADC data and calculate current ( mA ).
 * @param[in] ctx : Click context object.
 * See #hallcurrent11_t object definition for detailed explanation.
 * @param[out] current : Current ( mA ) data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t hallcurrent11_get_current ( hallcurrent11_t *ctx, float *current );

/**
 * @brief Hall Current 11 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent11_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin ( V ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t hallcurrent11_read_an_pin_voltage ( hallcurrent11_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT11_H

/*! @} */ // hallcurrent11

// ------------------------------------------------------------------------ END
