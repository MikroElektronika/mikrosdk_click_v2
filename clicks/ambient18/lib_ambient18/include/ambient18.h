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
 * @file ambient18.h
 * @brief This file contains API for Ambient 18 Click Driver.
 */

#ifndef AMBIENT18_H
#define AMBIENT18_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ambient18 Ambient 18 Click Driver
 * @brief API for configuring and manipulating Ambient 18 Click driver.
 * @{
 */

/**
 * @defgroup ambient18_set Ambient 18 Registers Settings
 * @brief Settings for registers of Ambient 18 Click driver.
 */

/**
 * @addtogroup ambient18_set
 * @{
 */

/**
 * @brief Ambient 18 mode setting.
 * @details Specified setting for mode of Ambient 18 Click driver.
 */
#define AMBIENT18_MODE_SHUTDOWN         0
#define AMBIENT18_MODE_H_GAIN           1
#define AMBIENT18_MODE_M_GAIN           2
#define AMBIENT18_MODE_L_GAIN           3

/**
 * @brief Ambient 18 ADC setting.
 * @details Specified settings for ADC of Ambient 18 Click driver.
 */
#define AMBIENT18_ADC_RESOLUTION        0x0FFF
#define AMBIENT18_VREF_3V3              3.3
#define AMBIENT18_VREF_5V               5.0

/**
 * @brief Ambient 18 ambient light constants.
 * @details Specified constants for ambient light of Ambient 18 Click driver.
 */
#define AMBIENT18_IOUT_CURRENT_H_GAIN   6.1
#define AMBIENT18_IOUT_CURRENT_M_GAIN   0.61
#define AMBIENT18_IOUT_CURRENT_L_GAIN   0.061
#define AMBIENT18_MICROAMPER_TO_AMPER   0.000001
#define AMBIENT18_IOUT_RESISTOR         5420

/**
 * @brief Ambient 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 18 Click driver.
 */
#define AMBIENT18_SET_DEV_ADDR          0x4D

/*! @} */ // ambient18_set

/**
 * @defgroup ambient18_map Ambient 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 18 Click driver.
 */

/**
 * @addtogroup ambient18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 18 Click to the selected MikroBUS.
 */
#define AMBIENT18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.gc1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gc2 = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // ambient18_map
/*! @} */ // ambient18

/**
 * @brief Ambient 18 Click driver selector.
 * @details Selects target driver interface of Ambient 18 Click driver.
 */
typedef enum
{
    AMBIENT18_DRV_SEL_ADC,       /**< ADC driver descriptor. */
    AMBIENT18_DRV_SEL_I2C        /**< I2C driver descriptor. */

} ambient18_drv_t;

/**
 * @brief Ambient 18 Click context object.
 * @details Context object definition of Ambient 18 Click driver.
 */
typedef struct
{
    digital_out_t  gc1;         /**< Mode setting pin 1. */
    digital_out_t  gc2;         /**< Mode setting pin 2. */

    analog_in_t  adc;           /**< ADC module object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    uint8_t     slave_address;  /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    float       vref;           /**< ADC reference voltage. */
    ambient18_drv_t drv_sel;    /**< Master driver interface selector. */
    uint8_t     gain_mode;      /**< Sensor gain mode. */

} ambient18_t;

/**
 * @brief Ambient 18 Click configuration object.
 * @details Configuration object definition of Ambient 18 Click driver.
 */
typedef struct
{
    pin_name_t  an;                                 /**< Analog pin descriptor. */
    pin_name_t  scl;                                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  gc1;                                /**< Mode setting pin 1. */
    pin_name_t  gc2;                                /**< Mode setting pin 2. */

    analog_in_resolution_t  resolution;             /**< ADC resolution. */
    float                   vref;                   /**< ADC reference voltage. */
    
    uint32_t                i2c_speed;              /**< I2C serial speed. */
    uint8_t                 i2c_address;            /**< I2C slave address. */
    
    ambient18_drv_t drv_sel;                        /**< Master driver interface selector. */

} ambient18_cfg_t;

/**
 * @brief Ambient 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT18_OK = 0,
    AMBIENT18_ERROR = -1

} ambient18_return_value_t;

/*!
 * @addtogroup ambient18 Ambient 18 Click Driver
 * @brief API for configuring and manipulating Ambient 18 Click driver.
 * @{
 */

/**
 * @brief Ambient 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient18_cfg_setup ( ambient18_cfg_t *cfg );

/**
 * @brief Ambient 18 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ambient18_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ambient18_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ambient18_drv_interface_selection ( ambient18_cfg_t *cfg, ambient18_drv_t drv_sel );

/**
 * @brief Ambient 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ambient18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient18_init ( ambient18_t *ctx, ambient18_cfg_t *cfg );

/**
 * @brief Ambient 18 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #ambient18_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient18_read_raw_adc ( ambient18_t *ctx, uint16_t *raw_adc );

/**
 * @brief Ambient 18 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ambient18_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t ambient18_read_voltage ( ambient18_t *ctx, float *voltage );

/**
 * @brief Ambient 18 set vref function.
 * @details This function sets the voltage reference for Ambient 18 click driver.
 * @param[in] ctx : Click context object.
 * See #ambient18_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b ambient18_init is 3.3V.
 */
err_t ambient18_set_vref ( ambient18_t *ctx, float vref );

/**
 * @brief Ambient 18 set gain mode function.
 * @details This function sets the gain mode.
 * @param[in] ctx : Click context object.
 * See #ambient18_t object definition for detailed explanation.
 * @param[in] mode : @li @c  0 - Shutdown,
 *                   @li @c  1 - H-Gain - up to 100 Lux,
 *                   @li @c  2 - M-Gain - up to 1000 Lux,
 *                   @li @c  3 - L-Gain - up to 10000 Lux.
 * @return None.
 * @note None.
 */
void ambient18_set_gain_mode ( ambient18_t *ctx, uint8_t mode );

/**
 * @brief Ambient 18 voltage to illuminance function.
 * @details This function calculates illuminance (lux) based on the @b voltage input.
 * @param[in] voltage : Voltage from IOUT (volts).
 * @return @li @c >=0 Illuminance in lux,
 *         @li @c <0  Gain mode error.
 * @note Gain mode must be set before this function call.
 */
int32_t ambient18_voltage_to_lux ( ambient18_t *ctx, float voltage );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT18_H

/*! @} */ // ambient18

// ------------------------------------------------------------------------ END
