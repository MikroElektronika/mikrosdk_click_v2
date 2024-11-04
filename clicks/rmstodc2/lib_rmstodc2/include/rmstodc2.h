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
 * @file rmstodc2.h
 * @brief This file contains API for RMS to DC 2 Click Driver.
 */

#ifndef RMSTODC2_H
#define RMSTODC2_H

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
 * @addtogroup rmstodc2 RMS to DC 2 Click Driver
 * @brief API for configuring and manipulating RMS to DC 2 Click driver.
 * @{
 */

/**
 * @defgroup rmstodc2_set RMS to DC 2 Registers Settings
 * @brief Settings for registers of RMS to DC 2 Click driver.
 */

/**
 * @addtogroup rmstodc2_set
 * @{
 */

/**
 * @brief RMS to DC 2 RMS voltage calculation setting.
 * @details Specified setting for RMS voltage calculation of RMS to DC 2 Click driver.
 * @note This coefficient is obtained from measurements and it is valid for up to 20kHz frequency.
 */
#define RMSTODC2_RMS_VOLTAGE_COEF       1.045f

/**
 * @brief RMS to DC 2 ADC setting.
 * @details Specified settings for ADC of RMS to DC 2 Click driver.
 */
#define RMSTODC2_ADC_RESOLUTION         0x0FFF
#define RMSTODC2_VREF_3V3               3.3
#define RMSTODC2_VREF_5V                5.0

/**
 * @brief RMS to DC 2 device address setting.
 * @details Specified setting for device slave address selection of
 * RMS to DC 2 Click driver.
 */
#define RMSTODC2_SET_DEV_ADDR           0x4D

/*! @} */ // rmstodc2_set

/**
 * @defgroup rmstodc2_map RMS to DC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of RMS to DC 2 Click driver.
 */

/**
 * @addtogroup rmstodc2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RMS to DC 2 Click to the selected MikroBUS.
 */
#define RMSTODC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // rmstodc2_map
/*! @} */ // rmstodc2

/**
 * @brief RMS to DC 2 Click driver selector.
 * @details Selects target driver interface of RMS to DC 2 Click driver.
 */
typedef enum
{
    RMSTODC2_DRV_SEL_ADC,           /**< ADC driver descriptor. */
    RMSTODC2_DRV_SEL_I2C            /**< I2C driver descriptor. */

} rmstodc2_drv_t;

/**
 * @brief RMS to DC 2 Click context object.
 * @details Context object definition of RMS to DC 2 Click driver.
 */
typedef struct
{
    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    float        vref;              /**< ADC reference voltage. */
    rmstodc2_drv_t drv_sel;         /**< Master driver interface selector. */

} rmstodc2_t;

/**
 * @brief RMS to DC 2 Click configuration object.
 * @details Configuration object definition of RMS to DC 2 Click driver.
 */
typedef struct
{
    pin_name_t an;                  /**< Analog pin descriptor. */
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;      /**< ADC resolution. */
    float                  vref;            /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;       /**< I2C serial speed. */
    uint8_t                i2c_address;     /**< I2C slave address. */
    
    rmstodc2_drv_t drv_sel;         /**< Master driver interface selector. */

} rmstodc2_cfg_t;

/**
 * @brief RMS to DC 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RMSTODC2_OK = 0,
    RMSTODC2_ERROR = -1

} rmstodc2_return_value_t;

/*!
 * @addtogroup rmstodc2 RMS to DC 2 Click Driver
 * @brief API for configuring and manipulating RMS to DC 2 Click driver.
 * @{
 */

/**
 * @brief RMS to DC 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rmstodc2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rmstodc2_cfg_setup ( rmstodc2_cfg_t *cfg );

/**
 * @brief RMS to DC 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #rmstodc2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #rmstodc2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void rmstodc2_drv_interface_sel ( rmstodc2_cfg_t *cfg, rmstodc2_drv_t drv_sel );

/**
 * @brief RMS to DC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rmstodc2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rmstodc2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rmstodc2_init ( rmstodc2_t *ctx, rmstodc2_cfg_t *cfg );

/**
 * @brief RMS to DC 2 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #rmstodc2_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rmstodc2_read_raw_adc ( rmstodc2_t *ctx, uint16_t *raw_adc );

/**
 * @brief RMS to DC 2 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #rmstodc2_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t rmstodc2_read_voltage ( rmstodc2_t *ctx, float *voltage );

/**
 * @brief RMS to DC 2 set vref function.
 * @details This function sets the voltage reference for RMS to DC 2 Click driver.
 * @param[in] ctx : Click context object.
 * See #rmstodc2_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b rmstodc2_init is 3.3V.
 */
err_t rmstodc2_set_vref ( rmstodc2_t *ctx, float vref );

#ifdef __cplusplus
}
#endif
#endif // RMSTODC2_H

/*! @} */ // rmstodc2

// ------------------------------------------------------------------------ END
