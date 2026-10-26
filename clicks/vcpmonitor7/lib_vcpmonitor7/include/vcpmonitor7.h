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
 * @file vcpmonitor7.h
 * @brief This file contains API for VCP Monitor 7 Click Driver.
 */

#ifndef VCPMONITOR7_H
#define VCPMONITOR7_H

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
 * @addtogroup vcpmonitor7 VCP Monitor 7 Click Driver
 * @brief API for configuring and manipulating VCP Monitor 7 Click driver.
 * @{
 */

/**
 * @defgroup vcpmonitor7_set VCP Monitor 7 Settings
 * @brief Settings of VCP Monitor 7 Click driver.
 */

/**
 * @addtogroup vcpmonitor7_set
 * @{
 */

/**
 * @brief VCP Monitor 7 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of VCP Monitor 7 Click driver.
 */
#define VCPMONITOR7_NUM_CONVERSIONS   30

/**
 * @brief VCP Monitor 7 ADC setting.
 * @details Specified settings for ADC of VCP Monitor 7 Click driver.
 */
#define VCPMONITOR7_ADC_RESOLUTION    0x0FFF
#define VCPMONITOR7_VREF_3V3          3.3
#define VCPMONITOR7_VREF_5V           5.0
#define VCPMONITOR7_VREF              VCPMONITOR7_VREF_3V3
#define VCPMONITOR7_ADC_NUM_OF_STEPS  4096.0

/**
 * @brief VCP Monitor 7 timeout setting.
 * @details Specified settings for timeout of VCP Monitor 7 Click driver.
 */
#define VCPMONITOR7_TIMEOUT_MS        2000

/**
 * @brief VCP Monitor 7 differential amplifier setting.
 * @details Specified setting for differential amplifier of VCP Monitor 7 Click driver.
 */
#define VCPMONITOR7_AMP_GAIN          0.5
#define VCPMONITOR7_MID_SUPPLY_DIV    2.0

/**
 * @brief VCP Monitor 7 device address setting.
 * @details Specified setting for device slave address selection of
 * VCP Monitor 7 Click driver.
 */
#define VCPMONITOR7_DEVICE_ADDRESS    0x4D

/*! @} */ // vcpmonitor7_set

/**
 * @defgroup vcpmonitor7_map VCP Monitor 7 MikroBUS Map
 * @brief MikroBUS pin mapping of VCP Monitor 7 Click driver.
 */

/**
 * @addtogroup vcpmonitor7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of VCP Monitor 7 Click to the selected MikroBUS.
 */
#define VCPMONITOR7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ren = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // vcpmonitor7_map
/*! @} */ // vcpmonitor7

/**
 * @brief VCP Monitor 7 Click driver selector.
 * @details Selects target driver interface of VCP Monitor 7 Click driver.
 */
typedef enum
{
    VCPMONITOR7_DRV_SEL_ADC,                        /**< ADC driver descriptor. */
    VCPMONITOR7_DRV_SEL_I2C                         /**< I2C driver descriptor. */

} vcpmonitor7_drv_t;

/**
 * @brief VCP Monitor 7 Click context object.
 * @details Context object definition of VCP Monitor 7 Click driver.
 */
typedef struct
{
    digital_out_t en;                               /**< Differential amplifier enable pin (active high). */
    digital_out_t ren;                              /**< Reference buffer enable pin (active high). */

    analog_in_t  adc;                               /**< ADC module object. */
    i2c_master_t i2c;                               /**< I2C driver object. */

    uint8_t      slave_address;                     /**< Device slave address (used for I2C driver). */
    float        vref;                              /**< ADC reference voltage. */
    vcpmonitor7_drv_t drv_sel;                      /**< Master driver interface selector. */

} vcpmonitor7_t;

/**
 * @brief VCP Monitor 7 Click configuration object.
 * @details Configuration object definition of VCP Monitor 7 Click driver.
 */
typedef struct
{
    pin_name_t an;                                  /**< Analog pin descriptor. */
    pin_name_t scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t en;                                  /**< Differential amplifier enable pin descriptor. */
    pin_name_t ren;                                 /**< Reference buffer enable pin descriptor. */

    analog_in_resolution_t resolution;              /**< ADC resolution. */
    float                  vref;                    /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;               /**< I2C serial speed. */
    uint8_t                i2c_address;             /**< I2C slave address. */
    
    vcpmonitor7_drv_t drv_sel;                      /**< Master driver interface selector. */

} vcpmonitor7_cfg_t;

/**
 * @brief VCP Monitor 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VCPMONITOR7_OK = 0,
    VCPMONITOR7_ERROR = -1

} vcpmonitor7_return_value_t;

/*!
 * @addtogroup vcpmonitor7 VCP Monitor 7 Click Driver
 * @brief API for configuring and manipulating VCP Monitor 7 Click driver.
 * @{
 */

/**
 * @brief VCP Monitor 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vcpmonitor7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vcpmonitor7_cfg_setup ( vcpmonitor7_cfg_t *cfg );

/**
 * @brief VCP Monitor 7 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #vcpmonitor7_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #vcpmonitor7_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void vcpmonitor7_drv_interface_sel ( vcpmonitor7_cfg_t *cfg, vcpmonitor7_drv_t drv_sel );

/**
 * @brief VCP Monitor 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vcpmonitor7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor7_init ( vcpmonitor7_t *ctx, vcpmonitor7_cfg_t *cfg );

/**
 * @brief VCP Monitor 7 enable device function.
 * @details This function enables the differential amplifier output stage by setting
 * the EN pin to the high logic level.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @return Nothing.
 * @note The reference buffer must be enabled before the amplifier.
 */
void vcpmonitor7_enable_device ( vcpmonitor7_t *ctx );

/**
 * @brief VCP Monitor 7 disable device function.
 * @details This function disables the differential amplifier output stage by setting
 * the EN pin to the low logic level.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void vcpmonitor7_disable_device ( vcpmonitor7_t *ctx );

/**
 * @brief VCP Monitor 7 enable ref function.
 * @details This function enables the reference buffer which generates the mid supply
 * reference voltage by setting the REN pin to the high logic level.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void vcpmonitor7_enable_ref ( vcpmonitor7_t *ctx );

/**
 * @brief VCP Monitor 7 disable ref function.
 * @details This function disables the reference buffer by setting the REN pin to
 * the low logic level.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void vcpmonitor7_disable_ref ( vcpmonitor7_t *ctx );

/**
 * @brief VCP Monitor 7 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor7_read_raw_adc ( vcpmonitor7_t *ctx, uint16_t *raw_adc );

/**
 * @brief VCP Monitor 7 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t vcpmonitor7_read_voltage ( vcpmonitor7_t *ctx, float *voltage );

/**
 * @brief VCP Monitor 7 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t vcpmonitor7_read_voltage_avg ( vcpmonitor7_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief VCP Monitor 7 read diff voltage function.
 * @details This function reads the average amplifier output voltage and converts it to
 * the differential voltage.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @param[out] diff_volt : Differential input voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vcpmonitor7_read_diff_voltage ( vcpmonitor7_t *ctx, float *diff_volt );

/**
 * @brief VCP Monitor 7 set vref function.
 * @details This function sets the voltage reference for VCP Monitor 7 Click driver.
 * @param[in] ctx : Click context object.
 * See #vcpmonitor7_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b vcpmonitor7_init is defined in VCPMONITOR7_VREF.
 */
err_t vcpmonitor7_set_vref ( vcpmonitor7_t *ctx, float vref );

#ifdef __cplusplus
}
#endif
#endif // VCPMONITOR7_H

/*! @} */ // vcpmonitor7

// ------------------------------------------------------------------------ END
