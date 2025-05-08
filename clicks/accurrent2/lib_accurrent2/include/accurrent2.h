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
 * @file accurrent2.h
 * @brief This file contains API for AC Current 2 Click Driver.
 */

#ifndef ACCURRENT2_H
#define ACCURRENT2_H

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
 * @addtogroup accurrent2 AC Current 2 Click Driver
 * @brief API for configuring and manipulating AC Current 2 Click driver.
 * @{
 */

/**
 * @defgroup accurrent2_set AC Current 2 Settings
 * @brief Settings of AC Current 2 Click driver.
 */

/**
 * @addtogroup accurrent2_set
 * @{
 */

/**
 * @brief AC Current 2 current measurement calculation values.
 * @details Specified current measurement calculation values of AC Current 2 Click driver.
 */
#define ACCURRENT2_AC_TO_DC_V_SCALE         1.8f
#define ACCURRENT2_SENSOR_RESOLUTION        30.0f

/**
 * @brief AC Current 2 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of AC Current 2 Click driver.
 */
#define ACCURRENT2_NUM_CONVERSIONS          200

/**
 * @brief AC Current 2 ADC setting.
 * @details Specified settings for ADC of AC Current 2 Click driver.
 */
#define ACCURRENT2_ADC_RESOLUTION           0x0FFF
#define ACCURRENT2_VREF_3V3                 3.3
#define ACCURRENT2_VREF_5V                  5.0

/**
 * @brief AC Current 2 timeout setting.
 * @details Specified setting for timeout of AC Current 2 Click driver.
 */
#define ACCURRENT2_TIMEOUT_MS               2000

/**
 * @brief AC Current 2 device address setting.
 * @details Specified setting for device slave address selection of
 * AC Current 2 Click driver.
 */
#define ACCURRENT2_SET_DEV_ADDR             0x4D

/*! @} */ // accurrent2_set

/**
 * @defgroup accurrent2_map AC Current 2 MikroBUS Map
 * @brief MikroBUS pin mapping of AC Current 2 Click driver.
 */

/**
 * @addtogroup accurrent2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AC Current 2 Click to the selected MikroBUS.
 */
#define ACCURRENT2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // accurrent2_map
/*! @} */ // accurrent2

/**
 * @brief AC Current 2 Click driver selector.
 * @details Selects target driver interface of AC Current 2 Click driver.
 */
typedef enum
{
    ACCURRENT2_DRV_SEL_ADC,             /**< ADC driver descriptor. */
    ACCURRENT2_DRV_SEL_I2C              /**< I2C driver descriptor. */

} accurrent2_drv_t;

/**
 * @brief AC Current 2 Click context object.
 * @details Context object definition of AC Current 2 Click driver.
 */
typedef struct
{
    analog_in_t  adc;                   /**< ADC module object. */
    i2c_master_t i2c;                   /**< I2C driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    float        vref;                  /**< ADC reference voltage. */
    accurrent2_drv_t drv_sel;           /**< Master driver interface selector. */

} accurrent2_t;

/**
 * @brief AC Current 2 Click configuration object.
 * @details Configuration object definition of AC Current 2 Click driver.
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
    
    accurrent2_drv_t drv_sel;           /**< Master driver interface selector. */

} accurrent2_cfg_t;

/**
 * @brief AC Current 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCURRENT2_OK = 0,
    ACCURRENT2_ERROR = -1

} accurrent2_return_value_t;

/*!
 * @addtogroup accurrent2 AC Current 2 Click Driver
 * @brief API for configuring and manipulating AC Current 2 Click driver.
 * @{
 */

/**
 * @brief AC Current 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accurrent2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accurrent2_cfg_setup ( accurrent2_cfg_t *cfg );

/**
 * @brief AC Current 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #accurrent2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #accurrent2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void accurrent2_drv_interface_sel ( accurrent2_cfg_t *cfg, accurrent2_drv_t drv_sel );

/**
 * @brief AC Current 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accurrent2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accurrent2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accurrent2_init ( accurrent2_t *ctx, accurrent2_cfg_t *cfg );

/**
 * @brief AC Current 2 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #accurrent2_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accurrent2_read_raw_adc ( accurrent2_t *ctx, uint16_t *raw_adc );

/**
 * @brief AC Current 2 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #accurrent2_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t accurrent2_read_voltage ( accurrent2_t *ctx, float *voltage );

/**
 * @brief AC Current 2 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #accurrent2_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t accurrent2_read_voltage_avg ( accurrent2_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief AC Current 2 set vref function.
 * @details This function sets the voltage reference for AC Current 2 Click driver.
 * @param[in] ctx : Click context object.
 * See #accurrent2_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b accurrent2_init is 3.3V.
 */
err_t accurrent2_set_vref ( accurrent2_t *ctx, float vref );

/**
 * @brief AC Current 2 read current function.
 * @details This function reads the current measurement from the AC Current sensor (30A/1V).
 * @param[in] ctx : Click context object.
 * See #accurrent2_t object definition for detailed explanation.
 * @param[out] current : Pointer to store the measured current value in Amperes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t accurrent2_read_current ( accurrent2_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // ACCURRENT2_H

/*! @} */ // accurrent2

// ------------------------------------------------------------------------ END
