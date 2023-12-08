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
 * @file multisteppertb67s101.h
 * @brief This file contains API for Multi Stepper TB67S101 Click Driver.
 */

#ifndef MULTISTEPPERTB67S101_H
#define MULTISTEPPERTB67S101_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup multisteppertb67s101 Multi Stepper TB67S101 Click Driver
 * @brief API for configuring and manipulating Multi Stepper TB67S101 Click driver.
 * @{
 */

/**
 * @defgroup multisteppertb67s101_reg Multi Stepper TB67S101 Registers List
 * @brief List of registers of Multi Stepper TB67S101 Click driver.
 */

/**
 * @addtogroup multisteppertb67s101_reg
 * @{
 */

/**
 * @brief Multi Stepper TB67S101 PCA9538A registers.
 * @details Specified PCA9538A registers of Multi Stepper TB67S101 Click driver.
 */
#define MULTISTEPPERTB67S101_REG_INPUT                      0x00
#define MULTISTEPPERTB67S101_REG_OUTPUT                     0x01
#define MULTISTEPPERTB67S101_REG_POLARITY                   0x02
#define MULTISTEPPERTB67S101_REG_CONFIG                     0x03

/*! @} */ // multisteppertb67s101_reg

/**
 * @defgroup multisteppertb67s101_set Multi Stepper TB67S101 Registers Settings
 * @brief Settings for registers of Multi Stepper TB67S101 Click driver.
 */

/**
 * @addtogroup multisteppertb67s101_set
 * @{
 */

/**
 * @brief Multi Stepper TB67S101 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Multi Stepper TB67S101 Click driver.
 */
#define MULTISTEPPERTB67S101_PHASEA_PIN                     0x02
#define MULTISTEPPERTB67S101_PHASEB_PIN                     0x04

/**
 * @brief Multi Stepper TB67S101 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Multi Stepper TB67S101 Click driver.
 */
#define MULTISTEPPERTB67S101_DEFAULT_CONFIG                 0xF9

/**
 * @brief Multi Stepper TB67S101 direction setting.
 * @details Specified setting for direction of Multi Stepper TB67S101 Click driver.
 */
#define MULTISTEPPERTB67S101_DIR_CW                         0
#define MULTISTEPPERTB67S101_DIR_CCW                        1

/**
 * @brief Multi Stepper TB67S101 pin logic level setting.
 * @details Specified setting for pin logic level of Multi Stepper TB67S101 Click driver.
 */
#define MULTISTEPPERTB67S101_PIN_LOW_LEVEL                  0
#define MULTISTEPPERTB67S101_PIN_HIGH_LEVEL                 1

/**
 * @brief Multi Stepper TB67S101 step resolution setting.
 * @details Specified setting for step resolution of Multi Stepper TB67S101 Click driver.
 */
#define MULTISTEPPERTB67S101_MODE_FULL_STEP                 0x00
#define MULTISTEPPERTB67S101_MODE_HALF_STEP                 0x01
#define MULTISTEPPERTB67S101_MODE_QUARTER_STEP              0x02

/**
 * @brief Multi Stepper TB67S101 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define MULTISTEPPERTB67S101_SPEED_VERY_SLOW                0
#define MULTISTEPPERTB67S101_SPEED_SLOW                     1
#define MULTISTEPPERTB67S101_SPEED_MEDIUM                   2
#define MULTISTEPPERTB67S101_SPEED_FAST                     3
#define MULTISTEPPERTB67S101_SPEED_VERY_FAST                4 

/**
 * @brief Multi Stepper TB67S101 device address setting.
 * @details Specified setting for device slave address selection of
 * Multi Stepper TB67S101 Click driver.
 */
#define MULTISTEPPERTB67S101_DEVICE_ADDRESS_A1A0_00         0x70
#define MULTISTEPPERTB67S101_DEVICE_ADDRESS_A1A0_01         0x71
#define MULTISTEPPERTB67S101_DEVICE_ADDRESS_A1A0_10         0x72
#define MULTISTEPPERTB67S101_DEVICE_ADDRESS_A1A0_11         0x73

/*! @} */ // multisteppertb67s101_set

/**
 * @defgroup multisteppertb67s101_map Multi Stepper TB67S101 MikroBUS Map
 * @brief MikroBUS pin mapping of Multi Stepper TB67S101 Click driver.
 */

/**
 * @addtogroup multisteppertb67s101_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Multi Stepper TB67S101 Click to the selected MikroBUS.
 */
#define MULTISTEPPERTB67S101_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // multisteppertb67s101_map
/*! @} */ // multisteppertb67s101

/**
 * @brief Multi Stepper TB67S101 Click context object.
 * @details Context object definition of Multi Stepper TB67S101 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t an;           /**< INA1 pin. */
    digital_out_t int_pin;      /**< INA2 pin. */
    digital_out_t clk;          /**< INB1 pin. */
    digital_out_t en;           /**< INB2 pin. */
    digital_out_t rst;          /**< Standby pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t step_mode;
    uint8_t direction;

} multisteppertb67s101_t;

/**
 * @brief Multi Stepper TB67S101 Click configuration object.
 * @details Configuration object definition of Multi Stepper TB67S101 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  an;             /**< INA1 pin. */
    pin_name_t  int_pin;        /**< INA2 pin. */
    pin_name_t  clk;            /**< INB1 pin. */
    pin_name_t  en;             /**< INB2 pin. */
    pin_name_t  rst;            /**< Standby pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} multisteppertb67s101_cfg_t;

/**
 * @brief Multi Stepper TB67S101 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MULTISTEPPERTB67S101_OK = 0,
    MULTISTEPPERTB67S101_ERROR = -1

} multisteppertb67s101_return_value_t;

/*!
 * @addtogroup multisteppertb67s101 Multi Stepper TB67S101 Click Driver
 * @brief API for configuring and manipulating Multi Stepper TB67S101 Click driver.
 * @{
 */

/**
 * @brief Multi Stepper TB67S101 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #multisteppertb67s101_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void multisteppertb67s101_cfg_setup ( multisteppertb67s101_cfg_t *cfg );

/**
 * @brief Multi Stepper TB67S101 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #multisteppertb67s101_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t multisteppertb67s101_init ( multisteppertb67s101_t *ctx, multisteppertb67s101_cfg_t *cfg );

/**
 * @brief Multi Stepper TB67S101 default configuration function.
 * @details This function executes a default configuration of Multi Stepper TB67S101
 * click board.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t multisteppertb67s101_default_cfg ( multisteppertb67s101_t *ctx );

/**
 * @brief Multi Stepper TB67S101 write register function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t multisteppertb67s101_write_register ( multisteppertb67s101_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Multi Stepper TB67S101 read register function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t multisteppertb67s101_read_register ( multisteppertb67s101_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Multi Stepper TB67S101 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t multisteppertb67s101_drive_motor ( multisteppertb67s101_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Multi Stepper TB67S101 enable device function.
 * @details This function enables the device by setting the STANDBY pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void multisteppertb67s101_enable_device ( multisteppertb67s101_t *ctx );

/**
 * @brief Multi Stepper TB67S101 disable device function.
 * @details This function disables the device by setting the STANDBY pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void multisteppertb67s101_disable_device ( multisteppertb67s101_t *ctx );

/**
 * @brief Multi Stepper TB67S101 set ina1 pin function.
 * @details This function sets the INA1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void multisteppertb67s101_set_ina1_pin ( multisteppertb67s101_t *ctx, uint8_t state );

/**
 * @brief Multi Stepper TB67S101 set ina2 pin function.
 * @details This function sets the INA2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void multisteppertb67s101_set_ina2_pin ( multisteppertb67s101_t *ctx, uint8_t state );

/**
 * @brief Multi Stepper TB67S101 set inb1 pin function.
 * @details This function sets the INB1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void multisteppertb67s101_set_inb1_pin ( multisteppertb67s101_t *ctx, uint8_t state );

/**
 * @brief Multi Stepper TB67S101 set inb2 pin function.
 * @details This function sets the INB2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void multisteppertb67s101_set_inb2_pin ( multisteppertb67s101_t *ctx, uint8_t state );

/**
 * @brief Multi Stepper TB67S101 set step mode function.
 * @details This function sets the step mode resolution settings in @b ctx->step_mode.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 *                   @li @c 0 - Full step,
 *                   @li @c 1 - Half step,
 *                   @li @c 2 - Quarter step.
 * @return None.
 * @note None.
 */
void multisteppertb67s101_set_step_mode ( multisteppertb67s101_t *ctx, uint8_t mode );

/**
 * @brief Multi Stepper TB67S101 set direction function.
 * @details This function sets the motor direction to clockwise or counter-clockwise in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void multisteppertb67s101_set_direction ( multisteppertb67s101_t *ctx, uint8_t dir );

/**
 * @brief Multi Stepper TB67S101 switch direction function.
 * @details This function switches the motor direction in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void multisteppertb67s101_switch_direction ( multisteppertb67s101_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MULTISTEPPERTB67S101_H

/*! @} */ // multisteppertb67s101

// ------------------------------------------------------------------------ END
