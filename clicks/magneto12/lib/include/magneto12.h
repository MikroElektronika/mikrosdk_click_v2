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
 * @file magneto12.h
 * @brief This file contains API for Magneto 12 Click Driver.
 */

#ifndef MAGNETO12_H
#define MAGNETO12_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup magneto12 Magneto 12 Click Driver
 * @brief API for configuring and manipulating Magneto 12 Click driver.
 * @{
 */

/**
 * @defgroup magneto12_set Magneto 12 Registers Settings
 * @brief Settings for registers of Magneto 12 Click driver.
 */

/**
 * @addtogroup magneto12_set
 * @{
 */

/**
 * @brief Magneto 12 ADC setting.
 * @details Specified settings for ADC of Magneto 12 Click driver.
 */
#define MAGNETO12_ADC_RESOLUTION    0x0FFF
#define MAGNETO12_VREF_5V           5.0
#define MAGNETO12_FULL_CIRCLE       360.0
#define MAGNETO12_SATURATION_ERROR  0.04

/**
 * @brief Magneto 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Magneto 12 Click driver.
 */
#define MAGNETO12_SET_DEV_ADDR      0x4D

/*! @} */ // magneto12_set

/**
 * @defgroup magneto12_map Magneto 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Magneto 12 Click driver.
 */

/**
 * @addtogroup magneto12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magneto 12 Click to the selected MikroBUS.
 */
#define MAGNETO12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // magneto12_map
/*! @} */ // magneto12

/**
 * @brief Magneto 12 Click driver selector.
 * @details Selects target driver interface of Magneto 12 Click driver.
 */
typedef enum
{
    MAGNETO12_DRV_SEL_ADC,                  /**< ADC driver descriptor. */
    MAGNETO12_DRV_SEL_I2C                   /**< I2C driver descriptor. */

} magneto12_drv_t;

/**
 * @brief Magneto 12 Click context object.
 * @details Context object definition of Magneto 12 Click driver.
 */
typedef struct
{
    analog_in_t  adc;                       /**< ADC module object. */
    i2c_master_t i2c;                       /**< I2C driver object. */

    uint8_t     slave_address;              /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                /**< Chip select pin descriptor (used for SPI driver). */
    float       vref;                       /**< ADC reference voltage. */
    magneto12_drv_t drv_sel;                /**< Master driver interface selector. */

} magneto12_t;

/**
 * @brief Magneto 12 Click configuration object.
 * @details Configuration object definition of Magneto 12 Click driver.
 */
typedef struct
{
    pin_name_t  an;                         /**< Analog pin descriptor. */
    pin_name_t  scl;                        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                        /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */
    
    uint32_t    i2c_speed;                  /**< I2C serial speed. */
    uint8_t     i2c_address;                /**< I2C slave address. */
    
    magneto12_drv_t drv_sel;                /**< Master driver interface selector. */

} magneto12_cfg_t;

/**
 * @brief Magneto 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETO12_OK = 0,
    MAGNETO12_ERROR = -1

} magneto12_return_value_t;

/*!
 * @addtogroup magneto12 Magneto 12 Click Driver
 * @brief API for configuring and manipulating Magneto 12 Click driver.
 * @{
 */

/**
 * @brief Magneto 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneto12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneto12_cfg_setup ( magneto12_cfg_t *cfg );

/**
 * @brief Magneto 12 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #magneto12_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #magneto12_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void magneto12_drv_interface_selection ( magneto12_cfg_t *cfg, magneto12_drv_t drv_sel );

/**
 * @brief Magneto 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magneto12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneto12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto12_init ( magneto12_t *ctx, magneto12_cfg_t *cfg );

/**
 * @brief Magneto 12 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #magneto12_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto12_read_raw_adc ( magneto12_t *ctx, uint16_t *raw_adc );

/**
 * @brief Magneto 12 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #magneto12_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t magneto12_read_voltage ( magneto12_t *ctx, float *voltage );

/**
 * @brief Magneto 12 set vref function.
 * @details This function sets the voltage reference for Magneto 12 click driver.
 * @param[in] ctx : Click context object.
 * See #magneto12_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b magneto12_init is 3.3V.
 */
err_t magneto12_set_vref ( magneto12_t *ctx, float vref );

/**
 * @brief Magneto 12 read angle function.
 * @details This function reads the sensor output voltage and converts it to 
 * angular position in degrees.
 * @param[in] ctx : Click context object.
 * See #magneto12_t object definition for detailed explanation.
 * @param[out] angle : Angle in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto12_read_angle ( magneto12_t *ctx, float *angle );

#ifdef __cplusplus
}
#endif
#endif // MAGNETO12_H

/*! @} */ // magneto12

// ------------------------------------------------------------------------ END
