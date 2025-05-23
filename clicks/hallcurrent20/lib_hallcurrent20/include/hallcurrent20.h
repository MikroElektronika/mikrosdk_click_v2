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
 * @file hallcurrent20.h
 * @brief This file contains API for Hall Current 20 Click Driver.
 */

#ifndef HALLCURRENT20_H
#define HALLCURRENT20_H

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
 * @addtogroup hallcurrent20 Hall Current 20 Click Driver
 * @brief API for configuring and manipulating Hall Current 20 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent20_set Hall Current 20 Registers Settings
 * @brief Settings for registers of Hall Current 20 Click driver.
 */

/**
 * @addtogroup hallcurrent20_set
 * @{
 */

/**
 * @brief Hall Current 20 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Hall Current 20 Click driver.
 */
#define HALLCURRENT20_NUM_CONVERSIONS   200

/**
 * @brief Hall Current 20 ADC setting.
 * @details Specified settings for ADC of Hall Current 20 Click driver.
 */
#define HALLCURRENT20_ADC_RESOLUTION    0x0FFF
#define HALLCURRENT20_VREF_3V3          3.3
#define HALLCURRENT20_VREF_5V           5.0

/**
 * @brief Hall Current 20 timeout setting.
 * @details Specified setting for timeout of Hall Current 20 Click driver.
 */
#define HALLCURRENT20_TIMEOUT_MS        2000

/**
 * @brief Hall Current 20 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 20 Click driver.
 */
#define HALLCURRENT20_SET_DEV_ADDR      0x4D

/*! @} */ // hallcurrent20_set

/**
 * @defgroup hallcurrent20_map Hall Current 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 20 Click driver.
 */

/**
 * @addtogroup hallcurrent20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 20 Click to the selected MikroBUS.
 */
#define HALLCURRENT20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hallcurrent20_map
/*! @} */ // hallcurrent20

/**
 * @brief Hall Current 20 Click driver selector.
 * @details Selects target driver interface of Hall Current 20 Click driver.
 */
typedef enum
{
    HALLCURRENT20_DRV_SEL_ADC,          /**< ADC driver descriptor. */
    HALLCURRENT20_DRV_SEL_I2C           /**< I2C driver descriptor. */

} hallcurrent20_drv_t;

/**
 * @brief Hall Current 20 Click context object.
 * @details Context object definition of Hall Current 20 Click driver.
 */
typedef struct
{
    digital_in_t fault;                 /**< Overcurrent fault pin (active low). */

    analog_in_t  adc;                   /**< ADC module object. */
    i2c_master_t i2c;                   /**< I2C driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    float        vref;                  /**< ADC reference voltage. */
    float        zero_curr_offset;      /**< Voltage offset for zero current value. */
    float        data_resolution;       /**< Calibrated data resolution. */
    hallcurrent20_drv_t drv_sel;        /**< Master driver interface selector. */

} hallcurrent20_t;

/**
 * @brief Hall Current 20 Click configuration object.
 * @details Configuration object definition of Hall Current 20 Click driver.
 */
typedef struct
{
    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t fault;                   /**< Overcurrent fault pin (active low). */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;   /**< I2C serial speed. */
    uint8_t                i2c_address; /**< I2C slave address. */
    
    hallcurrent20_drv_t drv_sel;        /**< Master driver interface selector. */

} hallcurrent20_cfg_t;

/**
 * @brief Hall Current 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT20_OK = 0,
    HALLCURRENT20_ERROR = -1

} hallcurrent20_return_value_t;

/*!
 * @addtogroup hallcurrent20 Hall Current 20 Click Driver
 * @brief API for configuring and manipulating Hall Current 20 Click driver.
 * @{
 */

/**
 * @brief Hall Current 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent20_cfg_setup ( hallcurrent20_cfg_t *cfg );

/**
 * @brief Hall Current 20 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent20_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #hallcurrent20_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void hallcurrent20_drv_interface_sel ( hallcurrent20_cfg_t *cfg, hallcurrent20_drv_t drv_sel );

/**
 * @brief Hall Current 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent20_init ( hallcurrent20_t *ctx, hallcurrent20_cfg_t *cfg );

/**
 * @brief Hall Current 20 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #hallcurrent20_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent20_read_raw_adc ( hallcurrent20_t *ctx, uint16_t *raw_adc );

/**
 * @brief Hall Current 20 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent20_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent20_read_voltage ( hallcurrent20_t *ctx, float *voltage );

/**
 * @brief Hall Current 20 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent20_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent20_read_voltage_avg ( hallcurrent20_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Hall Current 20 set vref function.
 * @details This function sets the voltage reference for Hall Current 20 Click driver.
 * @param[in] ctx : Click context object.
 * See #hallcurrent20_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b hallcurrent20_init is 3.3V.
 */
err_t hallcurrent20_set_vref ( hallcurrent20_t *ctx, float vref );

/**
 * @brief Hall Current 20 get fault pin function.
 * @details This function returns the overcurrent fault pin logic state.
 * @param[in] ctx : Click context object.
 * See #hallcurrent20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hallcurrent20_get_fault_pin ( hallcurrent20_t *ctx );

/**
 * @brief Hall Current 20 calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #hallcurrent20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when no current flows through the sensor.
 */
err_t hallcurrent20_calib_offset ( hallcurrent20_t *ctx );

/**
 * @brief Hall Current 20 calib resolution function.
 * @details This function calibrates the data resolution at the known load current.
 * @param[in] ctx : Click context object.
 * See #hallcurrent20_t object definition for detailed explanation.
 * @param[in] calib_current : The known load current used for calibrating data resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when a known amount of load current flows through the sensor
 * and after calibrating zero current offset using hallcurrent20_calib_offset function.
 */
err_t hallcurrent20_calib_resolution ( hallcurrent20_t *ctx, float calib_current );

/**
 * @brief Hall Current 20 read current function.
 * @details This function reads the input current level [A].
 * @param[in] ctx : Click context object.
 * See #hallcurrent20_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero current offset and data resolution.
 * Refer to hallcurrent20_calib_offset and hallcurrent20_calib_resolution functions.
 */
err_t hallcurrent20_read_current ( hallcurrent20_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT20_H

/*! @} */ // hallcurrent20

// ------------------------------------------------------------------------ END
