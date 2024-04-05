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
 * @file pot4.h
 * @brief This file contains API for POT 4 Click Driver.
 */

#ifndef POT4_H
#define POT4_H

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
 * @addtogroup pot4 POT 4 Click Driver
 * @brief API for configuring and manipulating POT 4 Click driver.
 * @{
 */

/**
 * @defgroup pot4_set POT 4 Registers Settings
 * @brief Settings for registers of POT 4 Click driver.
 */

/**
 * @addtogroup pot4_set
 * @{
 */

/**
 * @brief POT 4 potentiometer setting.
 * @details Specified setting for potentiometer of POT 4 Click driver.
 */
#define POT4_PERCENTS               100
#define POT4_ROUND_TO_NEAREST_INT   0.5

/**
 * @brief POT 4 ADC setting.
 * @details Specified settings for ADC of POT 4 Click driver.
 */
#define POT4_ADC_RESOLUTION         0x0FFF
#define POT4_VREF_3V3               3.3
#define POT4_VREF_5V                5.0

/**
 * @brief POT 4 device address setting.
 * @details Specified setting for device slave address selection of
 * POT 4 Click driver.
 */
#define POT4_SET_DEV_ADDR           0x4D

/*! @} */ // pot4_set

/**
 * @defgroup pot4_map POT 4 MikroBUS Map
 * @brief MikroBUS pin mapping of POT 4 Click driver.
 */

/**
 * @addtogroup pot4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of POT 4 Click to the selected MikroBUS.
 */
#define POT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sw = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pot4_map
/*! @} */ // pot4

/**
 * @brief POT 4 Click driver selector.
 * @details Selects target driver interface of POT 4 Click driver.
 */
typedef enum
{
    POT4_DRV_SEL_ADC,               /**< ADC driver descriptor. */
    POT4_DRV_SEL_I2C                /**< I2C driver descriptor. */

} pot4_drv_t;

/**
 * @brief POT 4 Click context object.
 * @details Context object definition of POT 4 Click driver.
 */
typedef struct
{
    digital_in_t sw;                /**< Switch pin. */

    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    float        vref;              /**< ADC reference voltage. */
    pot4_drv_t   drv_sel;           /**< Master driver interface selector. */

} pot4_t;

/**
 * @brief POT 4 Click configuration object.
 * @details Configuration object definition of POT 4 Click driver.
 */
typedef struct
{
    pin_name_t an;                  /**< Analog pin descriptor. */
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t sw;                  /**< Switch pin. */

    analog_in_resolution_t resolution;      /**< ADC resolution. */
    float                  vref;            /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;       /**< I2C serial speed. */
    uint8_t                i2c_address;     /**< I2C slave address. */
    
    pot4_drv_t drv_sel;             /**< Master driver interface selector. */

} pot4_cfg_t;

/**
 * @brief POT 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    POT4_OK = 0,
    POT4_ERROR = -1

} pot4_return_value_t;

/*!
 * @addtogroup pot4 POT 4 Click Driver
 * @brief API for configuring and manipulating POT 4 Click driver.
 * @{
 */

/**
 * @brief POT 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pot4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pot4_cfg_setup ( pot4_cfg_t *cfg );

/**
 * @brief POT 4 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #pot4_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #pot4_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void pot4_drv_interface_selection ( pot4_cfg_t *cfg, pot4_drv_t drv_sel );

/**
 * @brief POT 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pot4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pot4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pot4_init ( pot4_t *ctx, pot4_cfg_t *cfg );

/**
 * @brief POT 4 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #pot4_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pot4_read_raw_adc ( pot4_t *ctx, uint16_t *raw_adc );

/**
 * @brief POT 4 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #pot4_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t pot4_read_voltage ( pot4_t *ctx, float *voltage );

/**
 * @brief POT 4 set vref function.
 * @details This function sets the voltage reference for POT 4 click driver.
 * @param[in] ctx : Click context object.
 * See #pot4_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b pot4_init is 3.3V.
 */
err_t pot4_set_vref ( pot4_t *ctx, float vref );

/**
 * @brief POT 4 get switch pin function.
 * @details This function returns the switch (SW) pin logic state.
 * @param[in] ctx : Click context object.
 * See #pot4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t pot4_get_switch_pin ( pot4_t *ctx );

/**
 * @brief POT 4 convert voltage to percents function.
 * @details This function converts analog voltage to potentiometer position in percents.
 * @param[in] ctx : Click context object.
 * See #pot4_t object definition for detailed explanation.
 * @return Potentiometer position in percents.
 * @note None.
 */
uint8_t pot4_convert_voltage_to_percents ( pot4_t *ctx, float voltage );

#ifdef __cplusplus
}
#endif
#endif // POT4_H

/*! @} */ // pot4

// ------------------------------------------------------------------------ END
