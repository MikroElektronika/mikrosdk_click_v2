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
 * @file thermostat6.h
 * @brief This file contains API for Thermostat 6 Click Driver.
 */

#ifndef THERMOSTAT6_H
#define THERMOSTAT6_H

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
 * @addtogroup thermostat6 Thermostat 6 Click Driver
 * @brief API for configuring and manipulating Thermostat 6 Click driver.
 * @{
 */

/**
 * @defgroup thermostat6_set Thermostat 6 Registers Settings
 * @brief Settings for registers of Thermostat 6 Click driver.
 */

/**
 * @addtogroup thermostat6_set
 * @{
 */

/**
 * @brief Thermostat 6 ADC setting.
 * @details Specified settings for ADC of Thermostat 6 Click driver.
 */
#define THERMOSTAT6_ADC_RESOLUTION      0x0FFF
#define THERMOSTAT6_VREF_3V3            3.3
#define THERMOSTAT6_VREF_5V             5.0
#define THERMOSTAT6_ADC_NUM_SAMPLES_50  50

/**
 * @brief Thermostat 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermostat 6 Click driver.
 */
#define THERMOSTAT6_SET_DEV_ADDR        0x4D

/*! @} */ // thermostat6_set

/**
 * @defgroup thermostat6_map Thermostat 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermostat 6 Click driver.
 */

/**
 * @addtogroup thermostat6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermostat 6 Click to the selected MikroBUS.
 */
#define THERMOSTAT6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.relay = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // thermostat6_map
/*! @} */ // thermostat6

/**
 * @brief Thermostat 6 Click context object.
 * @details Context object definition of Thermostat 6 Click driver.
 */
typedef struct
{
    digital_in_t relay;             /**< Relay pin (Active high). */

    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    float        vref;              /**< ADC reference voltage. */

} thermostat6_t;

/**
 * @brief Thermostat 6 Click configuration object.
 * @details Configuration object definition of Thermostat 6 Click driver.
 */
typedef struct
{
    pin_name_t an;                  /**< Analog pin descriptor. */
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t relay;               /**< Relay pin (Active high). */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;   /**< I2C serial speed. */
    uint8_t                i2c_address; /**< I2C slave address. */

} thermostat6_cfg_t;

/**
 * @brief Thermostat 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMOSTAT6_OK = 0,
    THERMOSTAT6_ERROR = -1

} thermostat6_return_value_t;

/*!
 * @addtogroup thermostat6 Thermostat 6 Click Driver
 * @brief API for configuring and manipulating Thermostat 6 Click driver.
 * @{
 */

/**
 * @brief Thermostat 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermostat6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermostat6_cfg_setup ( thermostat6_cfg_t *cfg );

/**
 * @brief Thermostat 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermostat6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermostat6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat6_init ( thermostat6_t *ctx, thermostat6_cfg_t *cfg );

/**
 * @brief Thermostat 6 get adc voltage function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #thermostat6_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t thermostat6_get_adc_v ( thermostat6_t *ctx, float *voltage );

/**
 * @brief Thermostat 6 get adc voltage average function.
 * @details This function reads and averages the ADC voltage for a desired number of samples.
 * @param[in] ctx : Click context object.
 * See #thermostat6_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @param[in] num_samples : Number of ADC samples.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t thermostat6_get_adc_v_avg ( thermostat6_t *ctx, float *voltage, uint16_t num_samples );

/**
 * @brief Thermostat 6 get AN pin voltage function.
 * @details This function reads the voltage from AN pin.
 * @param[in] ctx : Click context object.
 * See #thermostat6_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t thermostat6_get_an_pin_v ( thermostat6_t *ctx, float *voltage );

/**
 * @brief Thermostat 6 get AN pin voltage function.
 * @details This function reads and averages the AN pin voltage for a desired number of samples.
 * @param[in] ctx : Click context object.
 * See #thermostat6_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @param[in] num_samples : Number of ADC samples.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t thermostat6_get_an_pin_v_avg ( thermostat6_t *ctx, float *voltage, uint16_t num_samples );

/**
 * @brief Thermostat 6 set vref function.
 * @details This function sets the voltage reference for Thermostat 6 Click driver.
 * @param[in] ctx : Click context object.
 * See #thermostat6_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b thermostat6_init is 3.3V.
 * The THERMOSTAT6_VREF_3V3 macro is used as AN pin reference.
 */
err_t thermostat6_set_vref ( thermostat6_t *ctx, float vref );

/**
 * @brief Thermostat 6 get relay pin function.
 * @details This function returns the relay pin logic state.
 * @param[in] ctx : Click context object.
 * See #thermostat6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thermostat6_get_relay_pin ( thermostat6_t *ctx );

/**
 * @brief Thermostat 6 get temperature function.
 * @details This function calculates temperature in degrees Celsius based on a voltage input using
 * the NTC Thermistor 10k Cylindrical Probe (B57500M0103A005) R/T characteristics map.
 * @param[in] voltage : Voltage input for temperature calculation.
 * @return Temperature in degrees Celsius.
 * @note None.
 */
float thermostat6_get_temperature ( float voltage );

#ifdef __cplusplus
}
#endif
#endif // THERMOSTAT6_H

/*! @} */ // thermostat6

// ------------------------------------------------------------------------ END
