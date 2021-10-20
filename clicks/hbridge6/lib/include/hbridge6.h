/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file hbridge6.h
 * @brief This file contains API for H-Bridge 6 Click Driver.
 */

#ifndef HBRIDGE6_H
#define HBRIDGE6_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_pwm.h"
   
/*!
 * @addtogroup hbridge6 H-Bridge 6 Click Driver
 * @brief API for configuring and manipulating H-Bridge 6 Click driver.
 * @{
 */

/**
 * @defgroup hbridge6_set H-Bridge 6 Registers Settings
 * @brief Settings for registers of H-Bridge 6 Click driver.
 */

/**
 * @addtogroup hbridge6_set
 * @{
 */

/**
 * @brief H-Bridge 6 description setting.
 * @details Specified setting for description of H-Bridge 6 Click driver.
 */

/**
 * @brief H-Bridge 6 Port expander commands.
 * @details Specified setting for port expander commands of H-Bridge 6 Click driver.
 */
#define HBRIDGE6_REG_IN_PORT                                        0x00
#define HBRIDGE6_REG_OUT_PORT                                       0x01
#define HBRIDGE6_REG_POL_INV                                        0x02
#define HBRIDGE6_REG_CONFIG                                         0x03

/**
 * @brief H-Bridge 6 Pin states.
 * @details Specified pin states of H-Bridge 6 Click driver.
 */
#define HBRIDGE6_PIN_STATE_LOW                                      0x00
#define HBRIDGE6_PIN_STATE_HIGH                                     0x01

#define HBRIDGE6_IN_PORT_MULTI_SENSE_LOW                            0xFB
#define HBRIDGE6_IN_PORT_MULTI_SENSE_HIGH                           0x04

#define HBRIDGE6_IN_PORT_IN_LOW                                     0xFE
#define HBRIDGE6_IN_PORT_IN_HIGH                                    0x01

#define HBRIDGE6_MS_EN_LOW                                          0xFD
#define HBRIDGE6_MS_EN_HIGH                                         0x02

#define HBRIDGE6_DIAGNOSTIC_DISABLE                                 0x00
#define HBRIDGE6_DIAGNOSTIC_ENABLE                                  0x01

#define HBRIDGE6_DEFAULT_CFG                                        0xE0

#define HBRIDGE6_IN_PORT_SEL_BIT_MASK                               0x01
#define HBRIDGE6_IN_PORT_SEL_0                                      0x00
#define HBRIDGE6_IN_PORT_SEL_1                                      0x01

#define HBRIDGE6_NUMBER_OF_PORTS                                    0x07

/**
 * @brief H-Bridge 6 Direction.
 * @details Specified direction settings of H-Bridge 6 Click driver.
 */
#define HBRIDGE6_DIRECTION_BRAKE                                    0x00
#define HBRIDGE6_DIRECTION_CLOCKWISE                                0x01
#define HBRIDGE6_DIRECTION_COUNTERCLOCKWISE                         0x02

/**
 * @brief H-Bridge 6 device address setting.
 * @details Specified setting for device slave address selection of
 * H-Bridge 6 Click driver.
 */
#define HBRIDGE6_I2C_SLAVE_ADR_0                                    0x70
#define HBRIDGE6_I2C_SLAVE_ADR_1                                    0x71
#define HBRIDGE6_I2C_SLAVE_ADR_2                                    0x72
#define HBRIDGE6_I2C_SLAVE_ADR_3                                    0x73

/**
 * @brief H-Bridge 6 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of H-Bridge 6 Click driver.
 */
#define HBRIDGE6_DEF_FREQ                                           5000

/*! @} */ // hbridge6_set

/**
 * @defgroup hbridge6_map H-Bridge 6 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 6 Click driver.
 */

/**
 * @addtogroup hbridge6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 6 Click to the selected MikroBUS.
 */
#define HBRIDGE6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ms = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // hbridge6_map
/*! @} */ // hbridge6

/**
 * @brief H-Bridge 6 Click context object.
 * @details Context object definition of H-Bridge 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset. */
    
    // Input pins
    digital_in_t  ms;           /**< Current Sense and Diagnostic Feedback. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */
    pwm_t pwm;                  /**< PWM driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint32_t pwm_freq;          /**< PWM frequency value. */
    
} hbridge6_t;

/**
 * @brief H-Bridge 6 Click configuration object.
 * @details Configuration object definition of H-Bridge 6 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  ms;             /**< Current Sense and Diagnostic Feedback. */
    pin_name_t  rst;            /**< Reset. */
    pin_name_t  pwm;            /**< Motor Speed Control. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */
    
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */
    
    uint8_t in_out;
    uint8_t invert;
    uint8_t out_val;

} hbridge6_cfg_t;

/**
 * @brief H-Bridge 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HBRIDGE6_OK = 0,
   HBRIDGE6_ERROR = -1

} hbridge6_return_value_t;

/*!
 * @addtogroup hbridge6 H-Bridge 6 Click Driver
 * @brief API for configuring and manipulating H-Bridge 6 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note The all used pins will be set to unconnected state.
 */
void hbridge6_cfg_setup ( hbridge6_cfg_t *cfg );

/**
 * @brief H-Bridge 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hbridge6_init ( hbridge6_t *ctx, hbridge6_cfg_t *cfg );

/**
 * @brief H-Bridge 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @return Nothing.
 *
 */
void hbridge6_generic_write ( hbridge6_t *ctx, uint8_t reg, uint8_t tx_buf );

/**
 * @brief H-Bridge 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @return 8-bit read data.
 */
uint8_t hbridge6_generic_read ( hbridge6_t *ctx, uint8_t reg );

/**
 * @brief H-Bridge 6 default configuration function.
 * @details This function executes a default configuration of H-Bridge 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge6_default_cfg ( hbridge6_t *ctx );

/**
 * @brief H-Bridge 6 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hbridge6_set_duty_cycle ( hbridge6_t *ctx, float duty_cycle );

/**
 * @brief H-Bridge 6 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hbridge6_pwm_stop ( hbridge6_t *ctx );

/**
 * @brief H-Bridge 6 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hbridge6_pwm_start ( hbridge6_t *ctx );

/**
 * @brief HW reset function.
 * @details The function HW reset, 
 * reset the PCA9538A Low-voltage 8-bit I2C-bus I/O port
 * on H-Bridge 6 Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @return Nothing.
**/
void hbridge6_reset ( hbridge6_t *ctx );

/**
 * @brief Set output function.
 * @details The function set output of the desired port
 * of the PCA9538A Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on H-Bridge 6 Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] n_out_port : Port number.
 * @param[in] cfg_data : Structure where configuration data be stored.
 * @return Nothing.
**/
void hbridge6_set_output ( hbridge6_t *ctx, uint8_t n_out_port, hbridge6_cfg_t cfg_data );

/**
 * @brief Get output function.
 * @details The function get output configuration data
 * of the PCA9538A Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on H-Bridge 6 Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] n_out_port : Port number.
 * @param[in] cfg_data : Pointer to the memory location where configuration data be stored.
 * @return Nothing.
**/
void hbridge6_get_output ( hbridge6_t *ctx, uint8_t n_out_port, hbridge6_cfg_t *cfg_data );

/**
 * @brief Default config function.
 * @details The function set the default config
 * of the PCA9538A Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on H-Bridge 6 Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @return Nothing.
**/
void hbridge6_default_config ( hbridge6_t *ctx );

/**
 * @brief Set input port A function.
 * @details The function set input port A
 * of the PCA9538A Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on H-Bridge 6 Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] pin_state : Input port A state.
 * @return Nothing.
**/
void hbridge6_set_input_port_a ( hbridge6_t *ctx, uint8_t pin_state );

/**
 * @brief Set input port B function.
 * @details The function set input port B
 * of the PCA9538A Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on H-Bridge 6 Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] pin_state : Input port B state.
 * @return Nothing.
**/
void hbridge6_set_input_port_b ( hbridge6_t *ctx, uint8_t pin_state );

/**
 * @brief Enable the diagnostic function.
 * @details The function enable or disable the diagnostic
 * of the PCA9538A Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on H-Bridge 6 Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] en_state : The function for enabling diagnostic.
 * @return Nothing.
**/
void hbridge6_enable_diagnostic ( hbridge6_t *ctx, uint8_t en_state );

/**
 * @brief Set multi sense function.
 * @details The function set multi sense
 * of the PCA9538A Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on H-Bridge 6 Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] sel_num : Port number.
 * @param[in] pin_state : Port pin state.
 * @return Nothing.
**/
void hbridge6_set_multi_sense ( hbridge6_t *ctx, uint8_t sel_num, uint8_t pin_state );

/**
 * @brief Adjust the direction function.
 * @details The function adjust the engine direction
 * on H-Bridge 6 Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @param[in] direction : Direction of rotation:
 * @return Nothing.
**/
void hbridge6_set_direction ( hbridge6_t *ctx, uint8_t direction );

/**
 * @brief Get diagnostic function.
 * @details The function get the diagnostic
 * on H-Bridge 6 Click board.
 *  @param[in] ctx : Click context object.
 * See #hbridge6_t object definition for detailed explanation.
 * @return State of AN pin.
**/
uint8_t hbridge6_get_an_diagnostic ( hbridge6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE6_H

/*! @} */ // hbridge6

// ------------------------------------------------------------------------ END
