/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file hallcurrent27.h
 * @brief This file contains API for Hall Current 27 Click Driver.
 */

#ifndef HALLCURRENT27_H
#define HALLCURRENT27_H

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
 * @addtogroup hallcurrent27 Hall Current 27 Click Driver
 * @brief API for configuring and manipulating Hall Current 27 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent27_set Hall Current 27 Settings
 * @brief Settings of Hall Current 27 Click driver.
 */

/**
 * @addtogroup hallcurrent27_set
 * @{
 */

/**
 * @brief Hall Current 27 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Hall Current 27 Click driver.
 */
#define HALLCURRENT27_NUM_CONVERSIONS       200

/**
 * @brief Hall Current 27 ADC setting.
 * @details Specified settings for ADC of Hall Current 27 Click driver.
 */
#define HALLCURRENT27_ADC_RESOLUTION        0x0FFF
#define HALLCURRENT27_VREF_3V3              3.3
#define HALLCURRENT27_VREF_5V               5.0
#define HALLCURRENT27_VREF                  HALLCURRENT27_VREF_3V3

/**
 * @brief Hall Current 27 current calculation setting.
 * @details Specified settings for current calculation of Hall Current 27 Click driver.
 */
#define HALLCURRENT27_ZERO_CURR_OFFSET      1.6556
#define HALLCURRENT27_DATA_RESOLUTION       7.55

/**
 * @brief Hall Current 27 timing setting.
 * @details Specified settings for timing of Hall Current 27 Click driver.
 */
#define HALLCURRENT27_TIMEOUT_MS            2000

/**
 * @brief Hall Current 27 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 27 Click driver.
 */
#define HALLCURRENT27_DEVICE_ADDRESS        0x4D

/*! @} */ // hallcurrent27_set

/**
 * @defgroup hallcurrent27_map Hall Current 27 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 27 Click driver.
 */

/**
 * @addtogroup hallcurrent27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 27 Click to the selected MikroBUS.
 */
#define HALLCURRENT27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // hallcurrent27_map
/*! @} */ // hallcurrent27

/**
 * @brief Hall Current 27 Click driver selector.
 * @details Selects target driver interface of Hall Current 27 Click driver.
 */
typedef enum
{
    HALLCURRENT27_DRV_SEL_ADC,                      /**< ADC driver descriptor. */
    HALLCURRENT27_DRV_SEL_I2C                       /**< I2C driver descriptor. */

} hallcurrent27_drv_t;

/**
 * @brief Hall Current 27 Click context object.
 * @details Context object definition of Hall Current 27 Click driver.
 */
typedef struct
{
    analog_in_t  adc;                               /**< ADC module object. */
    i2c_master_t i2c;                               /**< I2C driver object. */

    uint8_t      slave_address;                     /**< Device slave address (used for I2C driver). */
    float        vref;                              /**< ADC reference voltage. */
    float        zero_curr_offset;                  /**< Voltage offset for zero current value. */
    float        data_resolution;                   /**< Calibrated data resolution. */
    hallcurrent27_drv_t drv_sel;                    /**< Master driver interface selector. */

} hallcurrent27_t;

/**
 * @brief Hall Current 27 Click configuration object.
 * @details Configuration object definition of Hall Current 27 Click driver.
 */
typedef struct
{
    pin_name_t an;                                  /**< Analog pin descriptor. */
    pin_name_t scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;              /**< ADC resolution. */
    float                  vref;                    /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;               /**< I2C serial speed. */
    uint8_t                i2c_address;             /**< I2C slave address. */
    
    hallcurrent27_drv_t drv_sel;                    /**< Master driver interface selector. */

} hallcurrent27_cfg_t;

/**
 * @brief Hall Current 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT27_OK = 0,
    HALLCURRENT27_ERROR = -1

} hallcurrent27_return_value_t;

/*!
 * @addtogroup hallcurrent27 Hall Current 27 Click Driver
 * @brief API for configuring and manipulating Hall Current 27 Click driver.
 * @{
 */

/**
 * @brief Hall Current 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent27_cfg_setup ( hallcurrent27_cfg_t *cfg );

/**
 * @brief Hall Current 27 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent27_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #hallcurrent27_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void hallcurrent27_drv_interface_sel ( hallcurrent27_cfg_t *cfg, hallcurrent27_drv_t drv_sel );

/**
 * @brief Hall Current 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent27_init ( hallcurrent27_t *ctx, hallcurrent27_cfg_t *cfg );

/**
 * @brief Hall Current 27 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #hallcurrent27_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent27_read_raw_adc ( hallcurrent27_t *ctx, uint16_t *raw_adc );

/**
 * @brief Hall Current 27 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent27_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent27_read_voltage ( hallcurrent27_t *ctx, float *voltage );

/**
 * @brief Hall Current 27 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent27_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent27_read_voltage_avg ( hallcurrent27_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Hall Current 27 set vref function.
 * @details This function sets the voltage reference for Hall Current 27 Click driver.
 * @param[in] ctx : Click context object.
 * See #hallcurrent27_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b hallcurrent27_init is defined in HALLCURRENT27_VREF.
 */
err_t hallcurrent27_set_vref ( hallcurrent27_t *ctx, float vref );

/**
 * @brief Hall Current 27 calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #hallcurrent27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when no current flows through the sensor.
 */
err_t hallcurrent27_calib_offset ( hallcurrent27_t *ctx );

/**
 * @brief Hall Current 27 calib resolution function.
 * @details This function calibrates the data resolution at the known load current.
 * @param[in] ctx : Click context object.
 * See #hallcurrent27_t object definition for detailed explanation.
 * @param[in] calib_current : The known load current used for calibrating data resolution [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when a known amount of load current flows through the sensor
 * and after calibrating zero current offset using hallcurrent27_calib_offset function.
 */
err_t hallcurrent27_calib_resolution ( hallcurrent27_t *ctx, float calib_current );

/**
 * @brief Hall Current 27 read current function.
 * @details This function reads the input current level [A].
 * @param[in] ctx : Click context object.
 * See #hallcurrent27_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on the calibrated zero current offset and data resolution.
 * Refer to hallcurrent27_calib_offset and hallcurrent27_calib_resolution functions.
 */
err_t hallcurrent27_read_current ( hallcurrent27_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT27_H

/*! @} */ // hallcurrent27

// ------------------------------------------------------------------------ END
