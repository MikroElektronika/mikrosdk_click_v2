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
 * @file forcecell.h
 * @brief This file contains API for Force Cell Click Driver.
 */

#ifndef FORCECELL_H
#define FORCECELL_H

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
 * @addtogroup forcecell Force Cell Click Driver
 * @brief API for configuring and manipulating Force Cell Click driver.
 * @{
 */

/**
 * @defgroup forcecell_set Force Cell Settings
 * @brief Settings of Force Cell Click driver.
 */

/**
 * @addtogroup forcecell_set
 * @{
 */

/**
 * @brief Force Cell force calculation setting.
 * @details Specified settings for force calculation of Force Cell Click driver.
 */
#define FORCECELL_R6_KOHM               2.7
#define FORCECELL_GAIN                  ( ( 100 / FORCECELL_R6_KOHM ) + 1 )
#define FORCECELL_SENSITIVITY_V_V       0.025
#define FORCECELL_FULL_SCALE_N          30

/**
 * @brief Force Cell default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Force Cell Click driver.
 */
#define FORCECELL_NUM_CONVERSIONS       100

/**
 * @brief Force Cell timeout setting.
 * @details Specified setting for timeout of Force Cell Click driver.
 */
#define FORCECELL_TIMEOUT_MS            2000

/**
 * @brief Force Cell ADC setting.
 * @details Specified settings for ADC of Force Cell Click driver.
 */
#define FORCECELL_ADC_RESOLUTION        0x0FFF
#define FORCECELL_VREF_3V3              3.3
#define FORCECELL_VREF_5V               5.0
#define FORCECELL_VREF                  FORCECELL_VREF_3V3

/**
 * @brief Force Cell device address setting.
 * @details Specified setting for device slave address selection of
 * Force Cell Click driver.
 */
#define FORCECELL_SET_DEV_ADDR          0x4D

/*! @} */ // forcecell_set

/**
 * @defgroup forcecell_map Force Cell MikroBUS Map
 * @brief MikroBUS pin mapping of Force Cell Click driver.
 */

/**
 * @addtogroup forcecell_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Force Cell Click to the selected MikroBUS.
 */
#define FORCECELL_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // forcecell_map
/*! @} */ // forcecell

/**
 * @brief Force Cell Click driver selector.
 * @details Selects target driver interface of Force Cell Click driver.
 */
typedef enum
{
    FORCECELL_DRV_SEL_ADC,              /**< ADC driver descriptor. */
    FORCECELL_DRV_SEL_I2C               /**< I2C driver descriptor. */

} forcecell_drv_t;

/**
 * @brief Force Cell Click context object.
 * @details Context object definition of Force Cell Click driver.
 */
typedef struct
{
    analog_in_t  adc;                   /**< ADC module object. */
    i2c_master_t i2c;                   /**< I2C driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    float        vref;                  /**< ADC reference voltage. */
    forcecell_drv_t drv_sel;            /**< Master driver interface selector. */
    float        zero_force_offset;     /**< Voltage offset for zero force value. */

} forcecell_t;

/**
 * @brief Force Cell Click configuration object.
 * @details Configuration object definition of Force Cell Click driver.
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
    
    forcecell_drv_t drv_sel;            /**< Master driver interface selector. */

} forcecell_cfg_t;

/**
 * @brief Force Cell Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FORCECELL_OK = 0,
    FORCECELL_ERROR = -1

} forcecell_return_value_t;

/*!
 * @addtogroup forcecell Force Cell Click Driver
 * @brief API for configuring and manipulating Force Cell Click driver.
 * @{
 */

/**
 * @brief Force Cell configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #forcecell_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void forcecell_cfg_setup ( forcecell_cfg_t *cfg );

/**
 * @brief Force Cell driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #forcecell_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #forcecell_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void forcecell_drv_interface_sel ( forcecell_cfg_t *cfg, forcecell_drv_t drv_sel );

/**
 * @brief Force Cell initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #forcecell_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #forcecell_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t forcecell_init ( forcecell_t *ctx, forcecell_cfg_t *cfg );

/**
 * @brief Force Cell read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #forcecell_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t forcecell_read_raw_adc ( forcecell_t *ctx, uint16_t *raw_adc );

/**
 * @brief Force Cell read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #forcecell_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t forcecell_read_voltage ( forcecell_t *ctx, float *voltage );

/**
 * @brief Force Cell read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #forcecell_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t forcecell_read_voltage_avg ( forcecell_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Force Cell set vref function.
 * @details This function sets the voltage reference for Force Cell Click driver.
 * @param[in] ctx : Click context object.
 * See #forcecell_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b forcecell_init is 3.3V.
 */
err_t forcecell_set_vref ( forcecell_t *ctx, float vref );

/**
 * @brief Force Cell calib offset function.
 * @details This function calibrates the zero force offset value.
 * @param[in] ctx : Click context object.
 * See #forcecell_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when no force is applied to the sensor.
 */
err_t forcecell_calib_offset ( forcecell_t *ctx );

/**
 * @brief Force Cell read force function.
 * @details This function reads the applied force level [N].
 * @param[in] ctx : Click context object.
 * See #forcecell_t object definition for detailed explanation.
 * @param[out] force : Applied force level [N].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero force offset.
 * Refer to forcecell_calib_offset functions.
 */
err_t forcecell_read_force ( forcecell_t *ctx, float *force );

#ifdef __cplusplus
}
#endif
#endif // FORCECELL_H

/*! @} */ // forcecell

// ------------------------------------------------------------------------ END
