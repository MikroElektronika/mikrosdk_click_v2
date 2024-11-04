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
 * @file button2.h
 * @brief This file contains API for Button 2 Click Driver.
 */

#ifndef BUTTON2_H
#define BUTTON2_H

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

/*!
 * @addtogroup button2 Button 2 Click Driver
 * @brief API for configuring and manipulating Button 2 Click driver.
 * @{
 */

/**
 * @defgroup button2_set Button 2 Settings
 * @brief Settings of Button 2 Click driver.
 */

/**
 * @addtogroup button2_set
 * @{
 */

/**
 * @brief Button 2 switch state setting.
 * @details Specified setting for switch state of Button 2 Click driver.
 */
#define BUTTON2_SWITCH_OFF          0
#define BUTTON2_SWITCH_ON           1

/**
 * @brief Button 2 button state setting.
 * @details Specified setting for button state of Button 2 Click driver.
 */
#define BUTTON2_BUTTON_PRESSED      0
#define BUTTON2_BUTTON_RELESED      1

/*! @} */ // button2_set

/**
 * @defgroup button2_map Button 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Button 2 Click driver.
 */

/**
 * @addtogroup button2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Button 2 Click to the selected MikroBUS.
 */
#define BUTTON2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.led = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // button2_map
/*! @} */ // button2

/**
 * @brief Button 2 Click context object.
 * @details Context object definition of Button 2 Click driver.
 */
typedef struct
{
    digital_out_t led;      /**< LED enable pin (active high). */

    digital_in_t int_pin;   /**< Interrupt pin - button state (active low). */

} button2_t;

/**
 * @brief Button 2 Click configuration object.
 * @details Configuration object definition of Button 2 Click driver.
 */
typedef struct
{
    pin_name_t led;         /**< LED enable pin (active high). */
    pin_name_t int_pin;     /**< Interrupt pin - button state (active low). */

} button2_cfg_t;

/**
 * @brief Button 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUTTON2_OK = 0,
    BUTTON2_ERROR = -1

} button2_return_value_t;

/*!
 * @addtogroup button2 Button 2 Click Driver
 * @brief API for configuring and manipulating Button 2 Click driver.
 * @{
 */

/**
 * @brief Button 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #button2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void button2_cfg_setup ( button2_cfg_t *cfg );

/**
 * @brief Button 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #button2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #button2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button2_init ( button2_t *ctx, button2_cfg_t *cfg );

/**
 * @brief Button 2 enable led function.
 * @details This function enables button LED by setting the LED pin to the high logic state.
 * @param[in] ctx : Click context object.
 * See #button2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void button2_enable_led ( button2_t *ctx );

/**
 * @brief Button 2 disable led function.
 * @details This function disables button LED by setting the LED pin to the low logic state.
 * @param[in] ctx : Click context object.
 * See #button2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void button2_disable_led ( button2_t *ctx );

/**
 * @brief Button 2 toggle led function.
 * @details This function toggles the button LED state by toggling the LED pin logic state.
 * @param[in] ctx : Click context object.
 * See #button2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void button2_toggle_led ( button2_t *ctx );

/**
 * @brief Button 2 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #button2_t object definition for detailed explanation.
 * @return @li @c 0 - Button pressed,
 *         @li @c 1 - Button released.
 * @note None.
 */
uint8_t button2_get_int_pin ( button2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUTTON2_H

/*! @} */ // button2

// ------------------------------------------------------------------------ END
