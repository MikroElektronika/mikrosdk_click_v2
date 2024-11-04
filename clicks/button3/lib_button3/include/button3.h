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
 * @file button3.h
 * @brief This file contains API for Button 3 Click Driver.
 */

#ifndef BUTTON3_H
#define BUTTON3_H

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

/*!
 * @addtogroup button3 Button 3 Click Driver
 * @brief API for configuring and manipulating Button 3 Click driver.
 * @{
 */

/**
 * @defgroup button3_reg Button 3 Registers List
 * @brief List of registers of Button 3 Click driver.
 */

/**
 * @addtogroup button3_reg
 * @{
 */

/**
 * @brief Button 3 registers.
 * @details Specified registers of Button 3 Click driver.
 */
#define BUTTON3_REG_INPUT                   0x00
#define BUTTON3_REG_OUTPUT                  0x01
#define BUTTON3_REG_POLARITY                0x02
#define BUTTON3_REG_CONFIG                  0x03

/*! @} */ // button3_reg

/**
 * @defgroup button3_set Button 3 Registers Settings
 * @brief Settings for registers of Button 3 Click driver.
 */

/**
 * @addtogroup button3_set
 * @{
 */

/**
 * @brief Button 3 pin mask.
 * @details Specified PCA9538A pin mask of Button 3 Click driver.
 */
#define BUTTON3_PIN_RED_BUTTON              0x01
#define BUTTON3_PIN_RED_LED                 0x02
#define BUTTON3_PIN_GREEN_BUTTON            0x04
#define BUTTON3_PIN_GREEN_LED               0x08
#define BUTTON3_PIN_BLUE_LED                0x10
#define BUTTON3_PIN_BLUE_BUTTON             0x20

/**
 * @brief Button 3 pin direction config.
 * @details Specified pin direction config of Button 3 Click driver.
 */
#define BUTTON3_DEFAULT_PIN_CONFIG          0xE5

/**
 * @brief Button 3 pin logic state setting.
 * @details Specified setting for pin logic state of Button 3 Click driver.
 */
#define BUTTON3_PIN_STATE_LOW               0
#define BUTTON3_PIN_STATE_HIGH              1

/**
 * @brief Button 3 switch state setting.
 * @details Specified setting for switch state of Button 3 Click driver.
 */
#define BUTTON3_SWITCH_OFF                  0
#define BUTTON3_SWITCH_ON                   1

/**
 * @brief Button 3 button state setting.
 * @details Specified setting for button state of Button 3 Click driver.
 */
#define BUTTON3_BUTTON_PRESSED              0
#define BUTTON3_BUTTON_RELESED              1

/**
 * @brief Button 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Button 3 Click driver.
 */
#define BUTTON3_DEVICE_ADDRESS_0            0x20
#define BUTTON3_DEVICE_ADDRESS_1            0x21

/*! @} */ // button3_set

/**
 * @defgroup button3_map Button 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Button 3 Click driver.
 */

/**
 * @addtogroup button3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Button 3 Click to the selected MikroBUS.
 */
#define BUTTON3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // button3_map
/*! @} */ // button3

/**
 * @brief Button 3 Click context object.
 * @details Context object definition of Button 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} button3_t;

/**
 * @brief Button 3 Click configuration object.
 * @details Configuration object definition of Button 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} button3_cfg_t;

/**
 * @brief Button 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUTTON3_OK = 0,
    BUTTON3_ERROR = -1

} button3_return_value_t;

/*!
 * @addtogroup button3 Button 3 Click Driver
 * @brief API for configuring and manipulating Button 3 Click driver.
 * @{
 */

/**
 * @brief Button 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #button3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void button3_cfg_setup ( button3_cfg_t *cfg );

/**
 * @brief Button 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #button3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_init ( button3_t *ctx, button3_cfg_t *cfg );

/**
 * @brief Button 3 default configuration function.
 * @details This function executes a default configuration of Button 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t button3_default_cfg ( button3_t *ctx );

/**
 * @brief Button 3 write reg function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_write_reg ( button3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Button 3 read reg function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_read_reg ( button3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Button 3 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void button3_reset_device ( button3_t *ctx );

/**
 * @brief Button 3 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void button3_set_rst_pin ( button3_t *ctx, uint8_t state );

/**
 * @brief Button 3 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t button3_get_int_pin ( button3_t *ctx );

/**
 * @brief Button 3 get red button function.
 * @details This function reads the red button (R1 pin) logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Button pressed,
 *                     @li @c 1 - Button released.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_get_red_button ( button3_t *ctx, uint8_t *state );

/**
 * @brief Button 3 get green button function.
 * @details This function reads the green button (G1 pin) logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Button pressed,
 *                     @li @c 1 - Button released.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_get_green_button ( button3_t *ctx, uint8_t *state );

/**
 * @brief Button 3 get blue button function.
 * @details This function reads the blue button (B1 pin) logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Button pressed,
 *                     @li @c 1 - Button released.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_get_blue_button ( button3_t *ctx, uint8_t *state );

/**
 * @brief Button 3 get red led function.
 * @details This function reads the red LED (RK pin) logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - LED enabled,
 *                     @li @c 1 - LED disabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_get_red_led ( button3_t *ctx, uint8_t *state );

/**
 * @brief Button 3 get green led function.
 * @details This function reads the green LED (GK pin) logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - LED enabled,
 *                     @li @c 1 - LED disabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_get_green_led ( button3_t *ctx, uint8_t *state );

/**
 * @brief Button 3 get blue led function.
 * @details This function reads the blue LED (BK pin) logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - LED enabled,
 *                     @li @c 1 - LED disabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_get_blue_led ( button3_t *ctx, uint8_t *state );

/**
 * @brief Button 3 enable red led function.
 * @details This function enables the red button LED by setting the RK pin to the low logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_enable_red_led ( button3_t *ctx );

/**
 * @brief Button 3 enable green led function.
 * @details This function enables the green button LED by setting the GK pin to the low logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_enable_green_led ( button3_t *ctx );

/**
 * @brief Button 3 enable blue led function.
 * @details This function enables the blue button LED by setting the BK pin to the low logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_enable_blue_led ( button3_t *ctx );

/**
 * @brief Button 3 disable red led function.
 * @details This function disables the red button LED by setting the RK pin to the high logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_disable_red_led ( button3_t *ctx );

/**
 * @brief Button 3 disable green led function.
 * @details This function disables the green button LED by setting the GK pin to the high logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_disable_green_led ( button3_t *ctx );

/**
 * @brief Button 3 disable blue led function.
 * @details This function disables the blue button LED by setting the BK pin to the high logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_disable_blue_led ( button3_t *ctx );

/**
 * @brief Button 3 toggle red led function.
 * @details This function toggles the red button LED by toggling the RK pin logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_toggle_red_led ( button3_t *ctx );

/**
 * @brief Button 3 toggle green led function.
 * @details This function toggles the green button LED by toggling the GK pin logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_toggle_green_led ( button3_t *ctx );

/**
 * @brief Button 3 toggle blue led function.
 * @details This function toggles the blue button LED by toggling the BK pin logic state.
 * @param[in] ctx : Click context object.
 * See #button3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button3_toggle_blue_led ( button3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUTTON3_H

/*! @} */ // button3

// ------------------------------------------------------------------------ END
