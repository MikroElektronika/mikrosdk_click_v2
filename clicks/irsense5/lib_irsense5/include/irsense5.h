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
 * @file irsense5.h
 * @brief This file contains API for IR Sense 5 Click Driver.
 */

#ifndef IRSENSE5_H
#define IRSENSE5_H

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
 * @addtogroup irsense5 IR Sense 5 Click Driver
 * @brief API for configuring and manipulating IR Sense 5 Click driver.
 * @{
 */

/**
 * @defgroup irsense5_reg IR Sense 5 Registers List
 * @brief List of registers of IR Sense 5 Click driver.
 */

/**
 * @defgroup irsense5_set IR Sense 5 Registers Settings
 * @brief Settings for registers of IR Sense 5 Click driver.
 */

/**
 * @addtogroup irsense5_set
 * @{
 */

/**
 * @brief IR Sense 5 temperature calculation data values.
 * @details Temperature calculation data values of IR Sense 5 Click driver.
 */
#define IRSENSE5_ROOM_TEMP_IN_K    298.15f
#define IRSENSE5_THERMISOR_BETA    3960.00f
#define IRSENSE5_INVERTED_VALUE    1.0f
#define IRSENSE5_TEMP_K_TO_C       273.15f
#define IRSENSE5_VREF_GAIN_X10     10.0f
#define IRSENSE5_LIN_FUN_MULT      10.121f
#define IRSENSE5_LIN_FUN_ADD       18.818f

/**
 * @brief IR Sense 5 ADC setting.
 * @details Specified settings for ADC of IR Sense 5 Click driver.
 */
#define IRSENSE5_ADC_RESOLUTION    0x0FFF
#define IRSENSE5_VREF_3V3          3.3
#define IRSENSE5_VREF_5V           5.0

/**
 * @brief IR Sense 5 device address setting.
 * @details Specified setting for device slave address selection of
 * IR Sense 5 Click driver.
 */
#define IRSENSE5_SET_DEV_ADDR      0x4D

/*! @} */ // irsense5_set

/**
 * @defgroup irsense5_map IR Sense 5 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Sense 5 Click driver.
 */

/**
 * @addtogroup irsense5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Sense 5 Click to the selected MikroBUS.
 */
#define IRSENSE5_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // irsense5_map
/*! @} */ // irsense5

/**
 * @brief IR Sense 5 Click context object.
 * @details Context object definition of IR Sense 5 Click driver.
 */
typedef struct
{

    analog_in_t  adc;              /**< ADC module object. */
    i2c_master_t i2c;              /**< I2C driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    float        vref;             /**< ADC reference voltage. */

} irsense5_t;

/**
 * @brief IR Sense 5 Click configuration object.
 * @details Configuration object definition of IR Sense 5 Click driver.
 */
typedef struct
{
    pin_name_t an;     /**< Analog pin descriptor. */
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;     /**< ADC resolution. */
    float                  vref;           /**< ADC reference voltage. */

    uint32_t               i2c_speed;      /**< I2C serial speed. */
    uint8_t                i2c_address;    /**< I2C slave address. */

} irsense5_cfg_t;

/**
 * @brief IR Sense 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRSENSE5_OK = 0,
    IRSENSE5_ERROR = -1

} irsense5_return_value_t;

/*!
 * @addtogroup irsense5 IR Sense 5 Click Driver
 * @brief API for configuring and manipulating IR Sense 5 Click driver.
 * @{
 */

/**
 * @brief IR Sense 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irsense5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irsense5_cfg_setup ( irsense5_cfg_t *cfg );

/**
 * @brief IR Sense 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irsense5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irsense5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense5_init ( irsense5_t *ctx, irsense5_cfg_t *cfg );

/**
 * @brief IR Sense 5 read thermopile raw ADC value function.
 * @details This function reads the thermopile raw ADC value.
 * @param[in] ctx : Click context object.
 * See #irsense5_t object definition for detailed explanation.
 * @param[out] raw_adc : Thermopile ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense5_read_raw_adc_thp ( irsense5_t *ctx, uint16_t *raw_adc );

/**
 * @brief IR Sense 5 read thermistor raw ADC value function.
 * @details This function reads the thermistor raw ADC value.
 * @param[in] ctx : Click context object.
 * See #irsense5_t object definition for detailed explanation.
 * @param[out] raw_adc : Thermistor ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense5_read_raw_adc_thm ( irsense5_t *ctx, uint16_t *raw_adc );

/**
 * @brief IR Sense 5 read thermopile voltage level function.
 * @details This function reads raw ADC value and converts it to proportional thermopile voltage level.
 * @param[in] ctx : Click context object.
 * See #irsense5_t object definition for detailed explanation.
 * @param[out] voltage : Thermopile voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t irsense5_read_vtg_thp ( irsense5_t *ctx, float *voltage );

/**
 * @brief IR Sense 5 read thermistor voltage level function.
 * @details This function reads raw ADC value and converts it to proportional thermistor voltage level.
 * @param[in] ctx : Click context object.
 * See #irsense5_t object definition for detailed explanation.
 * @param[out] voltage : Thermistor voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t irsense5_read_vtg_thm ( irsense5_t *ctx, float *voltage );

/**
 * @brief IR Sense 5 set vref function.
 * @details This function sets the voltage reference for IR Sense 5 click driver.
 * @param[in] ctx : Click context object.
 * See #irsense5_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b irsense5_init is 3.3V.
 */
err_t irsense5_set_vref ( irsense5_t *ctx, float vref );

/**
 * @brief IR Sense 5 get ambient temperature function.
 * @details This function reads and calculate ambient temperature in degree Celsius [degC].
 * @param[in] ctx : Click context object.
 * See #irsense5_t object definition for detailed explanation.
 * @param[out] amb_temp : Ambient temperature [degC].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense5_get_amb_temp ( irsense5_t *ctx, float *amb_temp );

/**
 * @brief IR Sense 5 get object temperature function.
 * @details This function reads and calculate object temperature in degree Celsius [degC].
 * @param[in] ctx : Click context object.
 * See #irsense5_t object definition for detailed explanation.
 * @param[out] obj_temp : Object temperature [degC].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irsense5_get_obj_temp ( irsense5_t *ctx, float *obj_temp );

#ifdef __cplusplus
}
#endif
#endif // IRSENSE5_H

/*! @} */ // irsense5

// ------------------------------------------------------------------------ END
