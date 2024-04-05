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
 * @file hbridge13.h
 * @brief This file contains API for H-Bridge 13 Click Driver.
 */

#ifndef HBRIDGE13_H
#define HBRIDGE13_H

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
#include "drv_i2c_master.h"
#include "drv_analog_in.h"
#include "drv_pwm.h"
    
/*!
 * @addtogroup hbridge13 H-Bridge 13 Click Driver
 * @brief API for configuring and manipulating H-Bridge 13 Click driver.
 * @{
 */

/**
 * @defgroup hbridge13_reg H-Bridge 13 Registers List
 * @brief List of registers of H-Bridge 13 Click driver.
 */

/**
 * @addtogroup hbridge13_reg
 * @{
 */

/**
 * @brief H-Bridge 13 description register.
 * @details Specified register for description of H-Bridge 13 Click driver.
 */
#define HBRIDGE13_REG_INPUT_PORT                    0x00
#define HBRIDGE13_REG_OUTPUT_PORT                   0x01
#define HBRIDGE13_REG_POLARITY_INV                  0x02
#define HBRIDGE13_REG_CONFIG                        0x03

/*! @} */ // hbridge13_reg

/**
 * @defgroup hbridge13_set H-Bridge 13 Registers Settings
 * @brief Settings for registers of H-Bridge 13 Click driver.
 */

/**
 * @addtogroup hbridge13_set
 * @{
 */

/**
 * @brief H-Bridge 13 description setting.
 * @details Specified setting for description of H-Bridge 13 Click driver.
 */
#define HBRIDGE13_NONE_PIN                          0x00
#define HBRIDGE13_AIN1_IO_PIN                       0x01
#define HBRIDGE13_AIN2_IO_PIN                       0x02
#define HBRIDGE13_PWM_SW1_PIN                       0x04
#define HBRIDGE13_PWM_SW2_PIN                       0x08
#define HBRIDGE13_BIN1_IO_PIN                       0x10
#define HBRIDGE13_BIN2_IO_PIN                       0x20
#define HBRIDGE13_AN_SW_PIN                         0x40
#define HBRIDGE13_FLT_PIN                           0x80
#define HBRIDGE13_ALL_PIN                           0xFF

/**
 * @brief H-Bridge 13 direction setting.
 * @details Specified setting for direction of H-Bridge 13 Click driver.
 */
#define HBRIDGE13_DIR_FORWARD                       0x01
#define HBRIDGE13_DIR_REVERSE                       0x00

/**
 * @brief H-Bridge 13 xIPROPI selection setting.
 * @details Specified setting for xIPROPI selection of H-Bridge 13 Click driver.
 */
#define HBRIDGE13_AN_A_PIN_SEL                      0x01
#define HBRIDGE13_AN_B_PIN_SEL                      0x00

/**
 * @brief H-Bridge 13 device address setting.
 * @details Specified setting for device slave address selection of
 * H-Bridge 13 Click driver.
 */
#define HBRIDGE13_DEVICE_ADDRESS_A1A0_00            0x70
#define HBRIDGE13_DEVICE_ADDRESS_A1A0_01            0x71
#define HBRIDGE13_DEVICE_ADDRESS_A1A0_10            0x72
#define HBRIDGE13_DEVICE_ADDRESS_A1A0_11            0x73

/**
 * @brief H-Bridge 13 ADC setting.
 * @details Specified settings for ADC of H-Bridge 13 Click driver.
 */
#define HBRIDGE13_ADC_RESOLUTION                    0x0FFF
#define HBRIDGE13_VREF_3V3                          3.3
#define HBRIDGE13_VREF_5V                           5.0

/**
 * @brief H-Bridge 13 default PWM frequency.
 * @details Specified setting for default PWM frequency of H-Bridge 13 Click driver.
 */
#define HBRIDGE13_DEF_FREQ                          5000

/*! @} */ // hbridge13_set

/**
 * @defgroup hbridge13_map H-Bridge 13 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 13 Click driver.
 */

/**
 * @addtogroup hbridge13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 13 Click to the selected MikroBUS.
 */
#define HBRIDGE13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge13_map
/*! @} */ // hbridge13

/**
 * @brief H-Bridge 13 Click context object.
 * @details Context object definition of H-Bridge 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */
    pwm_t pwm;                  /**< PWM driver object. */
    analog_in_t  adc;           /**< ADC module object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    // ADC reference voltage
    float        vref;          /**< ADC reference voltage. */
    
    
    // PWM variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

} hbridge13_t;

/**
 * @brief H-Bridge 13 Click configuration object.
 * @details Configuration object definition of H-Bridge 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    
    pin_name_t pwm;                     /**< PWM pin. */

    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t rst;                     /**< Reset pin. */
    pin_name_t int_pin;                 /**< Interrupt pin. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */
    
    // Static variable
    uint32_t dev_pwm_freq;              /**< PWM frequency value. */
    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} hbridge13_cfg_t;

/**
 * @brief H-Bridge 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE13_OK = 0,
    HBRIDGE13_ERROR = -1

} hbridge13_return_value_t;

/*!
 * @addtogroup hbridge13 H-Bridge 13 Click Driver
 * @brief API for configuring and manipulating H-Bridge 13 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge13_cfg_setup ( hbridge13_cfg_t *cfg );

/**
 * @brief H-Bridge 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_init ( hbridge13_t *ctx, hbridge13_cfg_t *cfg );

/**
 * @brief H-Bridge 13 default configuration function.
 * @details This function executes a default configuration of H-Bridge 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge13_default_cfg ( hbridge13_t *ctx );

/**
 * @brief H-Bridge 13 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_generic_write ( hbridge13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief H-Bridge 13 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_generic_read ( hbridge13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief H-Bridge 13 write register function.
 * @details This function is used to write byte of data into 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_write_reg ( hbridge13_t *ctx, uint8_t reg, uint8_t data_out );

/**
 * @brief H-Bridge 13 read register function.
 * @details This function is used to read byte of data into 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_read_reg ( hbridge13_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief H-Bridge 13 set output pin state function.
 * @details This function is used to change state of the output pins.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[in] set_mask : High state pins.
 * @param[in] clr_mask : Low state pins.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_set_pins ( hbridge13_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief H-Bridge 13 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_set_duty_cycle ( hbridge13_t *ctx, float duty_cycle );

/**
 * @brief H-Bridge 13 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_pwm_stop ( hbridge13_t *ctx );

/**
 * @brief H-Bridge 13 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_pwm_start ( hbridge13_t *ctx );

/**
 * @brief H-Bridge 13 set brake function.
 * @details This function is used to place outputs into brakeing mode.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_set_brake ( hbridge13_t *ctx );

/**
 * @brief H-Bridge 13 set coast function.
 * @details This function is used to place outputs into coasting mode.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_set_coast ( hbridge13_t *ctx );

/**
 * @brief H-Bridge 13 set direction function.
 * @details This function is used to set motor direction and speed.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[in] dir_set : Direction selection.
 * @param[in] speed : Speed value in percentages.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_set_direction ( hbridge13_t *ctx, uint8_t dir_set, uint8_t speed );

/**
 * @brief H-Bridge 13 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_read_raw_adc ( hbridge13_t *ctx, uint16_t *raw_adc );

/**
 * @brief H-Bridge 13 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hbridge13_read_voltage ( hbridge13_t *ctx, float *voltage );

/**
 * @brief H-Bridge 13 set vref function.
 * @details This function sets the voltage reference for H-Bridge 13 click driver.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b hbridge13_init is 3.3V.
 */
err_t hbridge13_set_vref ( hbridge13_t *ctx, float vref );

/**
 * @brief H-Bridge 13 get xIPROPI voltage function.
 * @details This function is used to get xIPROPI voltage of H-Bridge 13 click driver.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage.
 * @param[in] an_sel : Selection between AIPROPI and BIPROPI.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_get_an_voltage ( hbridge13_t *ctx, float *voltage, uint8_t an_sel );

/**
 * @brief H-Bridge 13 get nFAULT state function.
 * @details This function is used to get state of the nFAULT pin of H-Bridge 13 click driver.
 * @param[in] ctx : Click context object.
 * See #hbridge13_t object definition for detailed explanation.
 * @param[out] pin_state : nFAULT pin state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge13_get_flt_state ( hbridge13_t *ctx, uint8_t *pin_state );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE13_H

/*! @} */ // hbridge13

// ------------------------------------------------------------------------ END
