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
 * @file currentlimit4.h
 * @brief This file contains API for Current Limit 4 Click Driver.
 */

#ifndef CURRENTLIMIT4_H
#define CURRENTLIMIT4_H

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
 * @addtogroup currentlimit4 Current Limit 4 Click Driver
 * @brief API for configuring and manipulating Current Limit 4 Click driver.
 * @{
 */

/**
 * @defgroup currentlimit4_set Current Limit 4 Settings
 * @brief Settings of Current Limit 4 Click driver.
 */

/**
 * @addtogroup currentlimit4_set
 * @{
 */

/**
 * @brief Current Limit 4 sensitivity value.
 * @details Specified sensitivity value of Current Limit 4 Click driver.
 */
#define CURRENTLIMIT4_SENSITIVITY_A_PER_V       8.0
#define CURRENTLIMIT4_RILIM_DIVIDEND            1460000.0
#define CURRENTLIMIT4_RILIM_OFFSET              110.0

/**
 * @brief Current Limit 4 ADC setting.
 * @details Specified settings for ADC of Current Limit 4 Click driver.
 */
#define CURRENTLIMIT4_ADC_RESOLUTION            0x0FFF
#define CURRENTLIMIT4_VREF_3V3                  3.3
#define CURRENTLIMIT4_VREF_5V                   5.0

/**
 * @brief Current Limit 4 digital potentiometer values.
 * @details Specified digital potentiometer values of Current Limit 4 Click driver.
 */
#define CURRENTLIMIT4_DIGIPOT_MAX               5000
#define CURRENTLIMIT4_DIGIPOT_RES               256
#define CURRENTLIMIT4_DIGIPOT_R8                330
#define CURRENTLIMIT4_DIGIPOT_OFFSET            110
#define CURRENTLIMIT4_ROUND_TO_NEAREST_INT      0.5

/**
 * @brief Current Limit 4 current limit values.
 * @details Specified current limit values of Current Limit 4 Click driver.
 */
#define CURRENTLIMIT4_ILIMIT_MIN                400
#define CURRENTLIMIT4_ILIMIT_DEFAULT            1000
#define CURRENTLIMIT4_ILIMIT_MAX                3000

/**
 * @brief Current Limit 4 current limit calculation values.
 * @details Specified current limit calculation of Current Limit 4 Click driver.
 */
#define CURRENTLIMIT4_STEP                      10
#define CURRENTLIMIT4_START_POS                 10
#define CURRENTLIMIT4_MEASURE_NUM               100

/**
 * @brief Current Limit 4 power good indication states.
 * @details Specified power good indication states of Current Limit 4 Click driver.
 */
#define CURRENTLIMIT4_POWER_GOOD                1
#define CURRENTLIMIT4_POWER_GOOD_ERROR          0

/**
 * @brief Current Limit 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Current Limit 4 Click driver.
 */
#define CURRENTLIMIT4_SET_DEV_ADDR              0x2E

/*! @} */ // currentlimit4_set

/**
 * @defgroup currentlimit4_map Current Limit 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Current Limit 4 Click driver.
 */

/**
 * @addtogroup currentlimit4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current Limit 4 Click to the selected MikroBUS.
 */
#define CURRENTLIMIT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );   \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );     \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // currentlimit4_map
/*! @} */ // currentlimit4

/**
 * @brief Current Limit 4 Click driver selector.
 * @details Selects target driver interface of Current Limit 4 Click driver.
 */
typedef enum
{
    CURRENTLIMIT4_DRV_SEL_ADC,       /**< ADC driver descriptor. */
    CURRENTLIMIT4_DRV_SEL_I2C        /**< I2C driver descriptor. */

} currentlimit4_drv_t;

/**
 * @brief Current Limit 4 Click context object.
 * @details Context object definition of Current Limit 4 Click driver.
 */
typedef struct
{
    digital_out_t en;       /**< Enable for the device. */

    digital_in_t int_pin;   /**< Power Good Indication. */

    analog_in_t  adc;       /**< ADC module object. */
    i2c_master_t i2c;       /**< I2C driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    float        vref;             /**< ADC reference voltage. */

} currentlimit4_t;

/**
 * @brief Current Limit 4 Click configuration object.
 * @details Configuration object definition of Current Limit 4 Click driver.
 */
typedef struct
{
    pin_name_t an;          /**< Analog pin descriptor. */
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t en;          /**< Enable for the device. */
    pin_name_t int_pin;     /**< Power Good Indication. */

    analog_in_resolution_t resolution;    /**< ADC resolution. */
    float                  vref;          /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;     /**< I2C serial speed. */
    uint8_t                i2c_address;   /**< I2C slave address. */

} currentlimit4_cfg_t;

/**
 * @brief Current Limit 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENTLIMIT4_OK = 0,
    CURRENTLIMIT4_ERROR = -1

} currentlimit4_return_value_t;

/*!
 * @addtogroup currentlimit4 Current Limit 4 Click Driver
 * @brief API for configuring and manipulating Current Limit 4 Click driver.
 * @{
 */

/**
 * @brief Current Limit 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #currentlimit4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void currentlimit4_cfg_setup ( currentlimit4_cfg_t *cfg );

/**
 * @brief Current Limit 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #currentlimit4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit4_init ( currentlimit4_t *ctx, currentlimit4_cfg_t *cfg );

/**
 * @brief Current Limit 4 default configuration function.
 * @details This function executes a default configuration of Current Limit 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t currentlimit4_default_cfg ( currentlimit4_t *ctx );

/**
 * @brief Current Limit 4 enable function.
 * @details This function enables the current limiting switch
 * of the TPS25980, 2.7-24V, 8A, 3m Smart eFuse - Integrated Hot-swap Protection 
 * With Adjustable Transient Fault Management on the Current Limit 4 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void currentlimit4_enable ( currentlimit4_t *ctx );

/**
 * @brief Current Limit 4 disable function.
 * @details This function disables the current limiting switch
 * of the TPS25980, 2.7-24V, 8A, 3m Smart eFuse - Integrated Hot-swap Protection 
 * With Adjustable Transient Fault Management on the Current Limit 4 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void currentlimit4_disable ( currentlimit4_t *ctx );

/**
 * @brief Current Limit 4 power good indication function.
 * @details This function is used as power good indication
 * of the TPS25980, 2.7-24V, 8A, 3m Smart eFuse - Integrated Hot-swap Protection 
 * With Adjustable Transient Fault Management on the Current Limit 4 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @return @li @c  0 - Input voltage is lower then undervoltage protection threshold [Vin < Vuvp],
 *         @li @c  1 - Normal operation.
 * @note None.
 */
uint8_t currentlimit4_get_power_good ( currentlimit4_t *ctx );

/**
 * @brief Current Limit 4 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit4_read_raw_adc ( currentlimit4_t *ctx, uint16_t *raw_adc );

/**
 * @brief Current Limit 4 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t currentlimit4_read_voltage ( currentlimit4_t *ctx, float *voltage );

/**
 * @brief Current Limit 4 set vref function.
 * @details This function sets the voltage reference for Current Limit 4 Click driver.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b currentlimit4_init is 3.3V.
 */
err_t currentlimit4_set_vref ( currentlimit4_t *ctx, float vref );

/**
 * @brief Current Limit 4 get current function.
 * @details This function reads and calculate input current value 
 * of the TPS25980, 2.7-24V, 8A, 3m Smart eFuse - Integrated Hot-swap Protection 
 * With Adjustable Transient Fault Management on the Current Limit 4 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @param[out] current : Current [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t currentlimit4_get_current ( currentlimit4_t *ctx, float *current );

/**
 * @brief Current Limit 4 set wiper position function.
 * @details This function sets the position of the wiper position
 * of the MCP4561, 8-Bit Single I2C Digital POT with Nonvolatile Memory
 * on the Current Limit 4 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position [0-256].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit4_set_wiper_pos ( currentlimit4_t *ctx, uint16_t wiper_pos );

/**
 * @brief Current Limit 4 set resistance function.
 * @details This function sets the resistance 
 * of the MCP4561, 8-Bit Single I2C Digital POT with Nonvolatile Memory
 * on the Current Limit 4 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @param[in] res_kohm : Resistance [0-5000kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit4_set_res ( currentlimit4_t *ctx, uint16_t res_ohm );

/**
 * @brief Current Limit 4 set current limit function.
 * @details This function sets the current limit 
 * of the TPS25980, 2.7-24V, 8A, 3m Smart eFuse - Integrated Hot-swap Protection 
 * With Adjustable Transient Fault Management on the Current Limit 4 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit4_t object definition for detailed explanation.
 * @param[in] current_limit : Current limit (400mA to 3700mA).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit4_set_limit ( currentlimit4_t *ctx, uint16_t ilimit_ma );

#ifdef __cplusplus
}
#endif
#endif // CURRENTLIMIT4_H

/*! @} */ // currentlimit4

// ------------------------------------------------------------------------ END
