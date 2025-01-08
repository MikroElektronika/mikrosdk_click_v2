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
 * @file thermostat5.h
 * @brief This file contains API for Thermostat 5 Click Driver.
 */

#ifndef THERMOSTAT5_H
#define THERMOSTAT5_H

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
 * @addtogroup thermostat5 Thermostat 5 Click Driver
 * @brief API for configuring and manipulating Thermostat 5 Click driver.
 * @{
 */

/**
 * @defgroup thermostat5_set Thermostat 5 Registers Settings
 * @brief Settings for registers of Thermostat 5 Click driver.
 */

/**
 * @addtogroup thermostat5_set
 * @{
 */

/**
 * @brief Thermostat 5 temperature calculation data values.
 * @details Temperature calculation data values of Thermostat 5 Click driver.
 */
#define THERMOSTAT5_ROOM_TEMP_IN_K    293.15f
#define THERMOSTAT5_THERMISOR_BETA    3435.0f
#define THERMOSTAT5_INVERTED_VALUE    1.0f
#define THERMOSTAT5_TEMP_K_TO_C       273.15f

/**
 * @brief Thermostat 5 relay states.
 * @details Relay states of Thermostat 5 Click driver.
 */
#define THERMOSTAT5_RELAY_OFF         0
#define THERMOSTAT5_RELAY_ON          1

/**
 * @brief Thermostat 5 ADC setting.
 * @details Specified settings for ADC of Thermostat 5 Click driver.
 */
#define THERMOSTAT5_ADC_RESOLUTION    0x0FFFu
#define THERMOSTAT5_VREF_3V3          3.3
#define THERMOSTAT5_VREF_5V           5.0

/**
 * @brief Thermostat 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermostat 5 Click driver.
 */
#define THERMOSTAT5_SET_DEV_ADDR      0x4D

/*! @} */ // thermostat5_set

/**
 * @defgroup thermostat5_map Thermostat 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermostat 5 Click driver.
 */

/**
 * @addtogroup thermostat5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermostat 5 Click to the selected MikroBUS.
 */
#define THERMOSTAT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.on  = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // thermostat5_map
/*! @} */ // thermostat5

/**
 * @brief Thermostat 5 Click driver selector.
 * @details Selects target driver interface of Thermostat 5 Click driver.
 */
typedef enum
{
    THERMOSTAT5_DRV_SEL_ADC,       /**< ADC driver descriptor. */
    THERMOSTAT5_DRV_SEL_I2C        /**< I2C driver descriptor. */

} thermostat5_drv_t;

/**
 * @brief Thermostat 5 Click context object.
 * @details Context object definition of Thermostat 5 Click driver.
 */
typedef struct
{
    digital_out_t on;              /**< Relay control. */

    analog_in_t  adc;              /**< ADC module object. */
    i2c_master_t i2c;              /**< I2C driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    float        vref;             /**< ADC reference voltage. */
    thermostat5_drv_t drv_sel;     /**< Master driver interface selector. */

} thermostat5_t;

/**
 * @brief Thermostat 5 Click configuration object.
 * @details Configuration object definition of Thermostat 5 Click driver.
 */
typedef struct
{
    pin_name_t an;     /**< Analog pin descriptor. */
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t on;     /**< Relay control. */

    analog_in_resolution_t resolution;     /**< ADC resolution. */
    float                  vref;           /**< ADC reference voltage. */

    uint32_t               i2c_speed;      /**< I2C serial speed. */
    uint8_t                i2c_address;    /**< I2C slave address. */
    
    thermostat5_drv_t drv_sel;             /**< Master driver interface selector. */

} thermostat5_cfg_t;

/**
 * @brief Thermostat 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMOSTAT5_OK = 0,
    THERMOSTAT5_ERROR = -1

} thermostat5_return_value_t;

/*!
 * @addtogroup thermostat5 Thermostat 5 Click Driver
 * @brief API for configuring and manipulating Thermostat 5 Click driver.
 * @{
 */

/**
 * @brief Thermostat 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermostat5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermostat5_cfg_setup ( thermostat5_cfg_t *cfg );

/**
 * @brief Thermostat 5 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #thermostat5_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #thermostat5_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void thermostat5_drv_interface_sel ( thermostat5_cfg_t *cfg, thermostat5_drv_t drv_sel );

/**
 * @brief Thermostat 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermostat5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermostat5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat5_init ( thermostat5_t *ctx, thermostat5_cfg_t *cfg );

/**
 * @brief Thermostat 5 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #thermostat5_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat5_read_raw_adc ( thermostat5_t *ctx, uint16_t *raw_adc );

/**
 * @brief Thermostat 5 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #thermostat5_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t thermostat5_read_voltage ( thermostat5_t *ctx, float *voltage );

/**
 * @brief Thermostat 5 set vref function.
 * @details This function sets the voltage reference for Thermostat 5 Click driver.
 * @param[in] ctx : Click context object.
 * See #thermostat5_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b thermostat5_init is 3.3V.
 */
err_t thermostat5_set_vref ( thermostat5_t *ctx, float vref );

/**
 * @brief Thermostat 5 get temperature function.
 * @details This function reads and calculates temperature in degrees Celsius [degC] using NTC thermistors.
 * @param[in] ctx : Click context object.
 * See #thermostat5_t object definition for detailed explanation.
 * @param[out] temperature : Temperature [degC].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat5_get_temperature ( thermostat5_t *ctx, float *temperature );

/**
 * @brief Thermostat 5 set relay function.
 * @details This function controls the relay by setting the state of the ON (PWM) pin.
 * @param[in] ctx : Click context object.
 * See #thermostat5_t object definition for detailed explanation.
 * @param[out] state : Relay ON/OFF state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void thermostat5_set_relay ( thermostat5_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // THERMOSTAT5_H

/*! @} */ // thermostat5

// ------------------------------------------------------------------------ END
