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
 * @file vacuum2.h
 * @brief This file contains API for Vacuum 2 Click Driver.
 */

#ifndef VACUUM2_H
#define VACUUM2_H

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
 * @addtogroup vacuum2 Vacuum 2 Click Driver
 * @brief API for configuring and manipulating Vacuum 2 Click driver.
 * @{
 */

/**
 * @defgroup vacuum2_set Vacuum 2 Settings
 * @brief Settings of Vacuum 2 Click driver.
 */

/**
 * @addtogroup vacuum2_set
 * @{
 */

/**
 * @brief Vacuum 2 pressure calculation setting.
 * @details Specified setting for pressure calculation of Vacuum 2 Click driver.
 */
#define VACUUM2_PRESSURE_PA_MIN     -2000
#define VACUUM2_PRESSURE_PA_MAX      2000
#define VACUUM2_PRESSURE_SENS_PA     0.001
#define VACUUM2_ADC_VOUT_MULTIPLIER  2

/**
 * @brief Vacuum 2 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Vacuum 2 Click driver.
 */
#define VACUUM2_NUM_CONVERSIONS      200

/**
 * @brief Vacuum 2 ADC setting.
 * @details Specified settings for ADC of Vacuum 2 Click driver.
 */
#define VACUUM2_ADC_RESOLUTION       0x0FFF
#define VACUUM2_VREF_3V3             3.3
#define VACUUM2_VREF_5V              5.0

/**
 * @brief Vacuum 2 timeout setting.
 * @details Specified setting for timeout of Vacuum 2 Click driver.
 */
#define VACUUM2_TIMEOUT_MS           2000

/**
 * @brief Vacuum 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Vacuum 2 Click driver.
 */
#define VACUUM2_SET_DEV_ADDR         0x4D

/*! @} */ // vacuum2_set

/**
 * @defgroup vacuum2_map Vacuum 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Vacuum 2 Click driver.
 */

/**
 * @addtogroup vacuum2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Vacuum 2 Click to the selected MikroBUS.
 */
#define VACUUM2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // vacuum2_map
/*! @} */ // vacuum2

/**
 * @brief Vacuum 2 Click driver selector.
 * @details Selects target driver interface of Vacuum 2 Click driver.
 */
typedef enum
{
    VACUUM2_DRV_SEL_ADC,                /**< ADC driver descriptor. */
    VACUUM2_DRV_SEL_I2C                 /**< I2C driver descriptor. */

} vacuum2_drv_t;

/**
 * @brief Vacuum 2 Click context object.
 * @details Context object definition of Vacuum 2 Click driver.
 */
typedef struct
{
    analog_in_t  adc;                   /**< ADC module object. */
    i2c_master_t i2c;                   /**< I2C driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    float        vref;                  /**< ADC reference voltage. */
    float        zero_press_offset;     /**< Voltage offset for zero pressure. */
    vacuum2_drv_t drv_sel;              /**< Master driver interface selector. */

} vacuum2_t;

/**
 * @brief Vacuum 2 Click configuration object.
 * @details Configuration object definition of Vacuum 2 Click driver.
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
    
    vacuum2_drv_t drv_sel;              /**< Master driver interface selector. */

} vacuum2_cfg_t;

/**
 * @brief Vacuum 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VACUUM2_OK = 0,
    VACUUM2_ERROR = -1

} vacuum2_return_value_t;

/*!
 * @addtogroup vacuum2 Vacuum 2 Click Driver
 * @brief API for configuring and manipulating Vacuum 2 Click driver.
 * @{
 */

/**
 * @brief Vacuum 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vacuum2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vacuum2_cfg_setup ( vacuum2_cfg_t *cfg );

/**
 * @brief Vacuum 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #vacuum2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #vacuum2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void vacuum2_drv_interface_sel ( vacuum2_cfg_t *cfg, vacuum2_drv_t drv_sel );

/**
 * @brief Vacuum 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #vacuum2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vacuum2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vacuum2_init ( vacuum2_t *ctx, vacuum2_cfg_t *cfg );

/**
 * @brief Vacuum 2 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #vacuum2_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vacuum2_read_adc_raw ( vacuum2_t *ctx, uint16_t *raw_adc );

/**
 * @brief Vacuum 2 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #vacuum2_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t vacuum2_read_adc_voltage ( vacuum2_t *ctx, float *voltage );

/**
 * @brief Vacuum 2 set vref function.
 * @details This function sets the voltage reference for Vacuum 2 Click driver.
 * @param[in] ctx : Click context object.
 * See #vacuum2_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b vacuum2_init is 3.3V.
 */
err_t vacuum2_set_vref ( vacuum2_t *ctx, float vref );

/**
 * @brief Vacuum 2 read vout function.
 * @details This function reads the sensor output voltage.
 * @param[in] ctx : Click context object.
 * See #vacuum2_t object definition for detailed explanation.
 * @param[out] vout : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vacuum2_read_vout ( vacuum2_t *ctx, float *vout );

/**
 * @brief Vacuum 2 read vout avg function.
 * @details This function reads a desired number of sensor voltage output samples and averages it.
 * @param[in] ctx : Click context object.
 * See #vacuum2_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] vout_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vacuum2_read_vout_avg ( vacuum2_t *ctx, uint16_t num_conv, float *vout_avg );

/**
 * @brief Vacuum 2 calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #vacuum2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when no pressure is applied to the sensor.
 */
err_t vacuum2_calib_offset ( vacuum2_t *ctx );

/**
 * @brief Vacuum 2 read pressure function.
 * @details This function reads the pressure measurement.
 * @param[in] ctx : Click context object.
 * See #vacuum2_t object definition for detailed explanation.
 * @param[out] pressure : Pressure level [Pa].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero pressure offset, see vacuum2_calib_offset function.
 */
err_t vacuum2_read_pressure ( vacuum2_t *ctx, int16_t *pressure );

#ifdef __cplusplus
}
#endif
#endif // VACUUM2_H

/*! @} */ // vacuum2

// ------------------------------------------------------------------------ END
