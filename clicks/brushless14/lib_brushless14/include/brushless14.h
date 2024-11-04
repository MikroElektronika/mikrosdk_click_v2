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
 * @file brushless14.h
 * @brief This file contains API for Brushless 14 Click Driver.
 */

#ifndef BRUSHLESS14_H
#define BRUSHLESS14_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup brushless14 Brushless 14 Click Driver
 * @brief API for configuring and manipulating Brushless 14 Click driver.
 * @{
 */

/**
 * @defgroup brushless14_reg Brushless 14 Registers List
 * @brief List of registers of Brushless 14 Click driver.
 */

/**
 * @addtogroup brushless14_reg
 * @{
 */

/**
 * @brief Brushless 14 description register.
 * @details Specified register for description of Brushless 14 Click driver.
 */
#define BRUSHLESS14_DAC_REG_CONFIG          0x01
#define BRUSHLESS14_DAC_REG_STATUS_TRIGGER  0x02
#define BRUSHLESS14_DAC_REG_BRDCAST         0x03
#define BRUSHLESS14_DAC_REG_DAC_A_DATA      0x08
#define BRUSHLESS14_DAC_REG_DAC_B_DATA      0x09
#define BRUSHLESS14_DAC_REG_DAC_C_DATA      0x0A
#define BRUSHLESS14_DAC_REG_DAC_D_DATA      0x0B
#define BRUSHLESS14_DAC_REG_DAC_E_DATA      0x0C
#define BRUSHLESS14_DAC_REG_DAC_F_DATA      0x0D
#define BRUSHLESS14_DAC_REG_DAC_G_DATA      0x0E
#define BRUSHLESS14_DAC_REG_DAC_H_DATA      0x0F

#define BRUSHLESS14_PE_REG_INPUT_PORT       0x00
#define BRUSHLESS14_PE_REG_OUTPUT_PORT      0x01
#define BRUSHLESS14_PE_REG_POLARITY         0x02
#define BRUSHLESS14_PE_REG_CONFIGURATION    0x03

/*! @} */ // brushless14_reg

/**
 * @defgroup brushless14_set Brushless 14 Registers Settings
 * @brief Settings for registers of Brushless 14 Click driver.
 */

/**
 * @addtogroup brushless14_set
 * @{
 */

/**
 * @brief Brushless 14 DAC ID.
 * @details Specified ID for DAC IC of Brushless 14 Click driver.
 */
#define BRUSHLESS14_DAC_ID                  0x0500

/**
 * @brief Brushless 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 14 Click driver.
 */
#define BRUSHLESS14_EXPANDER_SLAVE_ADDR     0x73
#define BRUSHLESS14_DAC_SLAVE_ADDR          0x48

/**
 * @brief Brushless 14 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Brushless 14 Click driver.
 */
#define BRUSHLESS14_DEF_FREQ                5000

/*! @} */ // brushless14_set

/**
 * @defgroup brushless14_map Brushless 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 14 Click driver.
 */

/**
 * @addtogroup brushless14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 14 Click to the selected MikroBUS.
 */
#define BRUSHLESS14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless14_map
/*! @} */ // brushless14

/**
 * @brief Brushless 14 Click context object.
 * @details Context object definition of Brushless 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  dir;     /**< Description. */

    // Input pins
    digital_in_t  int_pin;  /**< Description. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */
    pwm_t pwm;              /**< PWM driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    // ctx variable
    uint32_t pwm_freq;      /**< PWM frequency value. */

} brushless14_t;

/**
 * @brief Brushless 14 Click configuration object.
 * @details Configuration object definition of Brushless 14 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  pwm;        /**< PWM pin. */

    pin_name_t  dir;        /**< Description. */
    pin_name_t  int_pin;    /**< Description. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */
    uint32_t dev_pwm_freq;  /**< PWM frequency value. */

} brushless14_cfg_t;

/**
 * @brief Brushless 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BRUSHLESS14_OK = 0,
   BRUSHLESS14_ERROR = -1

} brushless14_return_value_t;

/*!
 * @addtogroup brushless14 Brushless 14 Click Driver
 * @brief API for configuring and manipulating Brushless 14 Click driver.
 * @{
 */

/**
 * @brief Brushless 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless14_cfg_setup ( brushless14_cfg_t *cfg );

/**
 * @brief Brushless 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_init ( brushless14_t *ctx, brushless14_cfg_t *cfg );

/**
 * @brief Brushless 14 default configuration function.
 * @details This function executes a default configuration of Brushless 14
 * Click board.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless14_default_cfg ( brushless14_t *ctx );

/**
 * @brief Brushless 14 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_duty_cycle ( brushless14_t *ctx, float duty_cycle );

/**
 * @brief Brushless 14 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[out] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_pwm_stop ( brushless14_t *ctx );

/**
 * @brief Brushless 14 start PWM module.
 * @details This function starts the PWM module output.
 * @param[out] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_pwm_start ( brushless14_t *ctx );

/**
 * @brief DAC write function.
 * @details This function writes a word to the register for the DAC IC.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] in_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_dac_write ( brushless14_t *ctx, uint8_t reg, uint16_t in_data );

/**
 * @brief DAC reading function.
 * @details This function reads a word from the register for the DAC IC.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] out_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_dac_read ( brushless14_t *ctx, uint8_t reg, uint16_t *out_data );

/**
 * @brief Set Adjusted input 0.
 * @details This function sets adjusted input 0 voltage level.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] m_voltage : Voltage level to be set in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_adj0 ( brushless14_t *ctx, uint16_t m_voltage );

/**
 * @brief Set Adjusted input 1.
 * @details This function sets adjusted input 1 voltage level.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] m_voltage : Voltage level to be set in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_adj1 ( brushless14_t *ctx, uint16_t m_voltage );

/**
 * @brief Set Adjusted input 2.
 * @details This function sets adjusted input 2 voltage level.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] m_voltage : Voltage level to be set in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_adj2 ( brushless14_t *ctx, uint16_t m_voltage );

/**
 * @brief Set Adjusted input 3.
 * @details This function sets adjusted input 3 voltage level.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] m_voltage : Voltage level to be set in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_adj3 ( brushless14_t *ctx, uint16_t m_voltage );

/**
 * @brief Set PWM frequency select input.
 * @details This function sets PWM frequency select input voltage level.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] m_voltage : Voltage level to be set in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_fpwm ( brushless14_t *ctx, uint16_t m_voltage );

/**
 * @brief Set lead angle setting input.
 * @details This function sets lead angle setting input voltage level.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] m_voltage : Voltage level to be set in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_la ( brushless14_t *ctx, uint16_t m_voltage );

/**
 * @brief Port expander write function.
 * @details This function writes a byte to the register for the Port expander IC.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] in_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_port_expander_write ( brushless14_t *ctx, uint8_t reg, uint8_t in_data );

/**
 * @brief Port expander reading function.
 * @details This function reads a byte from the register for the Port expander IC.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] out_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_port_expander_read ( brushless14_t *ctx, uint8_t reg, uint8_t *out_data );

/**
 * @brief Set soft switching select.
 * @details This function sets soft switching select.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] state : Logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_slop ( brushless14_t *ctx, uint8_t state );

/**
 * @brief Set rotation speed of lead angle switching.
 * @details This function sets rotation speed of lead angle switching.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] state : Logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_rot ( brushless14_t *ctx, uint8_t state );

/**
 * @brief Set forced commutation frequency select.
 * @details This function sets forced commutation frequency select.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] state : Logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_fst ( brushless14_t *ctx, uint8_t state );

/**
 * @brief Set PWM duty function setting.
 * @details This function sets PWM duty function setting.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] state : Logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_sel_adj ( brushless14_t *ctx, uint8_t state );

/**
 * @brief Set overlapping commutation select.
 * @details This function sets overlapping commutation select.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] state : Logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_set_lap ( brushless14_t *ctx, uint8_t state );

/**
 * @brief Get rotation speed.
 * @details This function gets rotation speed.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] state : Logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_get_fg_out ( brushless14_t *ctx, uint8_t *state );

/**
 * @brief Get lock detection signal.
 * @details This function gets lock detection signal.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] state : Logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless14_get_ld_out ( brushless14_t *ctx, uint8_t *state );

/**
 * @brief Get port expadner interrupt.
 * @details This function gets interrupt signal from port expander pin.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @return Interrupt pin state
 */
uint8_t brushless14_get_int ( brushless14_t *ctx );

/**
 * @brief Set dirrection pin state.
 * @details This function sets CW/CCW pin state that changes rotation direction.
 * @param[in] ctx : Click context object.
 * See #brushless14_t object definition for detailed explanation.
 * @param[in] state : Logic state.
 * @return Nothing.
 */
void brushless14_set_dir ( brushless14_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS14_H

/*! @} */ // brushless14

// ------------------------------------------------------------------------ END
