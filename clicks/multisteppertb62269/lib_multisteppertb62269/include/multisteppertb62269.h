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
 * @file multisteppertb62269.h
 * @brief This file contains API for Multi Stepper TB62269 Click Driver.
 */

#ifndef MULTISTEPPERTB62269_H
#define MULTISTEPPERTB62269_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup multisteppertb62269 Multi Stepper TB62269 Click Driver
 * @brief API for configuring and manipulating Multi Stepper TB62269 Click driver.
 * @{
 */

/**
 * @defgroup multisteppertb62269_reg Multi Stepper TB62269 Registers List
 * @brief List of registers of Multi Stepper TB62269 Click driver.
 */

/**
 * @addtogroup multisteppertb62269_reg
 * @{
 */

/**
 * @brief Multi Stepper TB62269 PCA9538A registers.
 * @details Specified PCA9538A registers of Multi Stepper TB62269 Click driver.
 */
#define MULTISTEPPERTB62269_REG_INPUT                      0x00
#define MULTISTEPPERTB62269_REG_OUTPUT                     0x01
#define MULTISTEPPERTB62269_REG_POLARITY                   0x02
#define MULTISTEPPERTB62269_REG_CONFIG                     0x03

/*! @} */ // multisteppertb62269_reg

/**
 * @defgroup multisteppertb62269_set Multi Stepper TB62269 Registers Settings
 * @brief Settings for registers of Multi Stepper TB62269 Click driver.
 */

/**
 * @addtogroup multisteppertb62269_set
 * @{
 */

/**
 * @brief Multi Stepper TB62269 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Multi Stepper TB62269 Click driver.
 */
#define MULTISTEPPERTB62269_DMODE0_PIN                     0x01
#define MULTISTEPPERTB62269_DMODE1_PIN                     0x02
#define MULTISTEPPERTB62269_DMODE2_PIN                     0x04
#define MULTISTEPPERTB62269_MO_PIN                         0x40
#define MULTISTEPPERTB62269_LO_PIN                         0x80

/**
 * @brief Multi Stepper TB62269 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Multi Stepper TB62269 Click driver.
 */
#define MULTISTEPPERTB62269_DEFAULT_CONFIG                 0xF8

/**
 * @brief Multi Stepper TB62269 direction setting.
 * @details Specified setting for direction of Multi Stepper TB62269 Click driver.
 */
#define MULTISTEPPERTB62269_DIR_CW                         0
#define MULTISTEPPERTB62269_DIR_CCW                        1

/**
 * @brief Multi Stepper TB62269 pin logic level setting.
 * @details Specified setting for pin logic level of Multi Stepper TB62269 Click driver.
 */
#define MULTISTEPPERTB62269_PIN_LOW_LEVEL                  0
#define MULTISTEPPERTB62269_PIN_HIGH_LEVEL                 1

/**
 * @brief Multi Stepper TB62269 step resolution setting.
 * @details Specified setting for step resolution  of Multi Stepper TB62269 Click driver.
 */
#define MULTISTEPPERTB62269_MODE_STANDBY                   0x00
#define MULTISTEPPERTB62269_MODE_HALF_STEP_TYPE_B          0x01
#define MULTISTEPPERTB62269_MODE_HALF_STEP_TYPE_A          0x02
#define MULTISTEPPERTB62269_MODE_1_OVER_16                 0x03
#define MULTISTEPPERTB62269_MODE_FULL_STEP                 0x04
#define MULTISTEPPERTB62269_MODE_1_OVER_8                  0x05
#define MULTISTEPPERTB62269_MODE_QUARTER_STEP              0x06
#define MULTISTEPPERTB62269_MODE_1_OVER_32                 0x07
#define MULTISTEPPERTB62269_MODE_BITS_MASK                 0x07

/**
 * @brief Multi Stepper TB62269 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define MULTISTEPPERTB62269_SPEED_VERY_SLOW                0
#define MULTISTEPPERTB62269_SPEED_SLOW                     1
#define MULTISTEPPERTB62269_SPEED_MEDIUM                   2
#define MULTISTEPPERTB62269_SPEED_FAST                     3
#define MULTISTEPPERTB62269_SPEED_VERY_FAST                4 

/**
 * @brief Multi Stepper TB62269 device address setting.
 * @details Specified setting for device slave address selection of
 * Multi Stepper TB62269 Click driver.
 */
#define MULTISTEPPERTB62269_DEVICE_ADDRESS_A1A0_00         0x70
#define MULTISTEPPERTB62269_DEVICE_ADDRESS_A1A0_01         0x71
#define MULTISTEPPERTB62269_DEVICE_ADDRESS_A1A0_10         0x72
#define MULTISTEPPERTB62269_DEVICE_ADDRESS_A1A0_11         0x73

/*! @} */ // multisteppertb62269_set

/**
 * @defgroup multisteppertb62269_map Multi Stepper TB62269 MikroBUS Map
 * @brief MikroBUS pin mapping of Multi Stepper TB62269 Click driver.
 */

/**
 * @addtogroup multisteppertb62269_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Multi Stepper TB62269 Click to the selected MikroBUS.
 */
#define MULTISTEPPERTB62269_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // multisteppertb62269_map
/*! @} */ // multisteppertb62269

/**
 * @brief Multi Stepper TB62269 Click context object.
 * @details Context object definition of Multi Stepper TB62269 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable output pin. */
    digital_out_t an;           /**< Direction control pin. */
    digital_out_t rst;          /**< Electric angle reset pin. */
    digital_out_t clk;          /**< Clock signal input pin. */

    // Input pins
    digital_in_t  int_pin;      /**< Electric angle monitor pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} multisteppertb62269_t;

/**
 * @brief Multi Stepper TB62269 Click configuration object.
 * @details Configuration object definition of Multi Stepper TB62269 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;             /**< Enable output pin. */
    pin_name_t  an;             /**< Direction control pin. */
    pin_name_t  rst;            /**< Electric angle reset pin. */
    pin_name_t  clk;            /**< Clock signal input pin. */
    pin_name_t  int_pin;        /**< Electric angle monitor pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} multisteppertb62269_cfg_t;

/**
 * @brief Multi Stepper TB62269 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MULTISTEPPERTB62269_OK = 0,
    MULTISTEPPERTB62269_ERROR = -1

} multisteppertb62269_return_value_t;

/*!
 * @addtogroup multisteppertb62269 Multi Stepper TB62269 Click Driver
 * @brief API for configuring and manipulating Multi Stepper TB62269 Click driver.
 * @{
 */

/**
 * @brief Multi Stepper TB62269 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #multisteppertb62269_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void multisteppertb62269_cfg_setup ( multisteppertb62269_cfg_t *cfg );

/**
 * @brief Multi Stepper TB62269 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #multisteppertb62269_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t multisteppertb62269_init ( multisteppertb62269_t *ctx, multisteppertb62269_cfg_t *cfg );

/**
 * @brief Multi Stepper TB62269 default configuration function.
 * @details This function executes a default configuration of Multi Stepper TB62269
 * click board.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t multisteppertb62269_default_cfg ( multisteppertb62269_t *ctx );

/**
 * @brief Multi Stepper TB62269 write register function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t multisteppertb62269_write_register ( multisteppertb62269_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Multi Stepper TB62269 read register function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t multisteppertb62269_read_register ( multisteppertb62269_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Multi Stepper TB62269 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t multisteppertb62269_get_step_mode ( multisteppertb62269_t *ctx, uint8_t *mode );

/**
 * @brief Multi Stepper TB62269 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t multisteppertb62269_set_step_mode ( multisteppertb62269_t *ctx, uint8_t mode );

/**
 * @brief Multi Stepper TB62269 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast,
 * @return None.
 * @note None.
 */
void multisteppertb62269_drive_motor ( multisteppertb62269_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Multi Stepper TB62269 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void multisteppertb62269_enable_device ( multisteppertb62269_t *ctx );

/**
 * @brief Multi Stepper TB62269 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void multisteppertb62269_disable_device ( multisteppertb62269_t *ctx );

/**
 * @brief Multi Stepper TB62269 set direction function.
 * @details This function sets the motor direction by setting the AN pin logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void multisteppertb62269_set_direction ( multisteppertb62269_t *ctx, uint8_t dir );

/**
 * @brief Multi Stepper TB62269 switch direction function.
 * @details This function switches the motor direction by toggling the AN pin.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void multisteppertb62269_switch_direction ( multisteppertb62269_t *ctx );

/**
 * @brief Multi Stepper TB62269 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void multisteppertb62269_reset_device ( multisteppertb62269_t *ctx );

/**
 * @brief Multi Stepper TB62269 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t multisteppertb62269_get_int_pin ( multisteppertb62269_t *ctx );

/**
 * @brief Multi Stepper TB62269 set clk pin function.
 * @details This function sets the CLK pin logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb62269_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void multisteppertb62269_set_clk_pin ( multisteppertb62269_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // MULTISTEPPERTB62269_H

/*! @} */ // multisteppertb62269

// ------------------------------------------------------------------------ END
