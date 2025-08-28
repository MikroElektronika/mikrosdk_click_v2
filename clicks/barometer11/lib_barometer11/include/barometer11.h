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
 * @file barometer11.h
 * @brief This file contains API for Barometer 11 Click Driver.
 */

#ifndef BAROMETER11_H
#define BAROMETER11_H

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
 * @addtogroup barometer11 Barometer 11 Click Driver
 * @brief API for configuring and manipulating Barometer 11 Click driver.
 * @{
 */

/**
 * @defgroup barometer11_set Barometer 11 Registers Settings
 * @brief Settings for registers of Barometer 11 Click driver.
 */

/**
 * @addtogroup barometer11_set
 * @{
 */

/**
 * @brief Barometer 11 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Barometer 11 Click driver.
 */
#define BAROMETER11_NUM_CONVERSIONS     200

/**
 * @brief Barometer 11 ADC setting.
 * @details Specified settings for ADC of Barometer 11 Click driver.
 */
#define BAROMETER11_ADC_RESOLUTION      0x0FFF
#define BAROMETER11_VREF_3V3            3.3
#define BAROMETER11_VREF_5V             5.0

/**
 * @brief Barometer 11 timeout setting.
 * @details Specified setting for timeout of Barometer 11 Click driver.
 */
#define BAROMETER11_TIMEOUT_MS          2000

/**
 * @brief Barometer 11 pressure calculation values.
 * @details Specified pressure calculation values of Barometer 11 Click driver.
 */
#define BAROMETER11_VOLTAGE_DIVIDER     2.0
#define BAROMETER11_A_GAIN_VALUE        0.00223
#define BAROMETER11_B_OFFSET_VALUE      0.03649
#define BAROMETER11_R9_VOLTAGE_DROP_PCT 0.1
#define BAROMETER11_KPA_TO_MBAR         10.0
#define BAROMETER11_VDD                 BAROMETER11_VREF_5V

/**
 * @brief Barometer 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 11 Click driver.
 */
#define BAROMETER11_SET_DEV_ADDR        0x4D

/*! @} */ // barometer11_set

/**
 * @defgroup barometer11_map Barometer 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 11 Click driver.
 */

/**
 * @addtogroup barometer11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 11 Click to the selected MikroBUS.
 */
#define BAROMETER11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // barometer11_map
/*! @} */ // barometer11

/**
 * @brief Barometer 11 Click driver selector.
 * @details Selects target driver interface of Barometer 11 Click driver.
 */
typedef enum
{
    BAROMETER11_DRV_SEL_ADC,            /**< ADC driver descriptor. */
    BAROMETER11_DRV_SEL_I2C             /**< I2C driver descriptor. */

} barometer11_drv_t;

/**
 * @brief Barometer 11 Click context object.
 * @details Context object definition of Barometer 11 Click driver.
 */
typedef struct
{
    analog_in_t  adc;                   /**< ADC module object. */
    i2c_master_t i2c;                   /**< I2C driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    float        vref;                  /**< ADC reference voltage. */
    barometer11_drv_t drv_sel;          /**< Master driver interface selector. */

} barometer11_t;

/**
 * @brief Barometer 11 Click configuration object.
 * @details Configuration object definition of Barometer 11 Click driver.
 */
typedef struct
{
    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;   /**< I2C serial speed. */
    uint8_t                i2c_address; /**< I2C slave address. */
    
    barometer11_drv_t drv_sel;          /**< Master driver interface selector. */

} barometer11_cfg_t;

/**
 * @brief Barometer 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER11_OK = 0,
    BAROMETER11_ERROR = -1

} barometer11_return_value_t;

/*!
 * @addtogroup barometer11 Barometer 11 Click Driver
 * @brief API for configuring and manipulating Barometer 11 Click driver.
 * @{
 */

/**
 * @brief Barometer 11 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer11_cfg_setup ( barometer11_cfg_t *cfg );

/**
 * @brief Barometer 11 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #barometer11_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #barometer11_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void barometer11_drv_interface_sel ( barometer11_cfg_t *cfg, barometer11_drv_t drv_sel );

/**
 * @brief Barometer 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #barometer11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer11_init ( barometer11_t *ctx, barometer11_cfg_t *cfg );

/**
 * @brief Barometer 11 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #barometer11_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer11_read_raw_adc ( barometer11_t *ctx, uint16_t *raw_adc );

/**
 * @brief Barometer 11 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #barometer11_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t barometer11_read_voltage ( barometer11_t *ctx, float *voltage );

/**
 * @brief Barometer 11 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #barometer11_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t barometer11_read_voltage_avg ( barometer11_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Barometer 11 set vref function.
 * @details This function sets the voltage reference for Barometer 11 Click driver.
 * @param[in] ctx : Click context object.
 * See #barometer11_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b barometer11_init is 3.3V.
 */
err_t barometer11_set_vref ( barometer11_t *ctx, float vref );

/**
 * @brief Barometer 11 read pressure function.
 * @details This function reads the pressure level [mBar].
 * @param[in] ctx : Click context object.
 * See #barometer11_t object definition for detailed explanation.
 * @param[out] pressure : Pressure level [mBar].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer11_read_pressure ( barometer11_t *ctx, float *pressure );

#ifdef __cplusplus
}
#endif
#endif // BAROMETER11_H

/*! @} */ // barometer11

// ------------------------------------------------------------------------ END
