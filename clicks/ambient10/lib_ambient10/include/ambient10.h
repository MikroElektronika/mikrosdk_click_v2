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
 * @file ambient10.h
 * @brief This file contains API for Ambient 10 Click Driver.
 */

#ifndef AMBIENT10_H
#define AMBIENT10_H

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
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ambient10 Ambient 10 Click Driver
 * @brief API for configuring and manipulating Ambient 10 Click driver.
 * @{
 */

/**
 * @defgroup ambient10_set Ambient 10 Settings
 * @brief Settings for Ambient 10 Click driver.
 */

/**
 * @addtogroup ambient10_set
 * @{
 */

/**
 * @brief Ambient 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 10 Click driver.
 */
#define AMBIENT10_SET_DEV_ADDR          0x4D

/**
 * @brief Ambient 10 ADC setting.
 * @details Specified settings for ADC of Ambient 10 Click driver.
 */
#define AMBIENT10_ADC_RESOLUTION        0x0FFF
#define AMBIENT10_VREF_3V3              3.3
#define AMBIENT10_VREF_5V               5.0

/**
 * @brief Ambient 10 ambient light constants.
 * @details Specified constants for ambient light of Ambient 10 Click driver.
 * @note IOUT to LUX constant is extracted from Figure 3 of APDS-9006 datasheet.
 */
#define AMBIENT10_MICROAMPER_TO_AMPER   0.000001
#define AMBIENT10_IOUT_TO_LUX           2.5
#define AMBIENT10_IOUT_RESISTOR         5100

/*! @} */ // ambient10_set

/**
 * @defgroup ambient10_map Ambient 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 10 Click driver.
 */

/**
 * @addtogroup ambient10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 10 Click to the selected MikroBUS.
 */
#define AMBIENT10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // ambient10_map
/*! @} */ // ambient10

/**
 * @brief Ambient 10 Click context object.
 * @details Context object definition of Ambient 10 Click driver.
 */
typedef struct
{
    analog_in_t  adc;           /**< ADC module object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    float   vref;               /**< ADC reference voltage. */

} ambient10_t;

/**
 * @brief Ambient 10 Click configuration object.
 * @details Configuration object definition of Ambient 10 Click driver.
 */
typedef struct
{
    pin_name_t  an;             /**< Analog pin descriptor. */
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */
    
    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} ambient10_cfg_t;

/**
 * @brief Ambient 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT10_OK = 0,
    AMBIENT10_ERROR = -1

} ambient10_return_value_t;

/*!
 * @addtogroup ambient10 Ambient 10 Click Driver
 * @brief API for configuring and manipulating Ambient 10 Click driver.
 * @{
 */

/**
 * @brief Ambient 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient10_cfg_setup ( ambient10_cfg_t *cfg );

/**
 * @brief Ambient 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ambient10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient10_init ( ambient10_t *ctx, ambient10_cfg_t *cfg );

/**
 * @brief Ambient 10 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #ambient10_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient10_read_an_pin_value ( ambient10_t *ctx, uint16_t *data_out );

/**
 * @brief Ambient 10 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ambient10_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t ambient10_read_an_pin_voltage ( ambient10_t *ctx, float *data_out );

/**
 * @brief Ambient 10 read raw ADC function.
 * @details This function reads raw 12-bit ADC data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient10_t object definition for detailed explanation.
 * @param[out] raw_adc : Raw ADC read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient10_read_raw_adc ( ambient10_t *ctx, uint16_t *raw_adc );

/**
 * @brief Ambient 10 read ADC voltage function.
 * @details This function reads raw 12-bit ADC data and converts it to voltage
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient10_t object definition for detailed explanation.
 * @param[out] voltage : Calculated ADC voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient10_read_adc_voltage ( ambient10_t *ctx, float *voltage );

/**
 * @brief Ambient 10 set vref function.
 * @details This function sets the voltage reference for Ambient 10 click driver.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b ambient10_init is 3.3V.
 */
err_t ambient10_set_vref ( ambient10_t *ctx, float vref );

/**
 * @brief Ambient 10 voltage to illuminance function.
 * @details This function calculates illuminance (lux) based on the @b voltage input.
 * @param[in] voltage : Voltage from OUT (volts).
 * @return Illuminance in lux.
 * @note None.
 */
uint16_t ambient10_voltage_to_lux ( ambient10_t *ctx, float voltage );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT10_H

/*! @} */ // ambient10

// ------------------------------------------------------------------------ END
