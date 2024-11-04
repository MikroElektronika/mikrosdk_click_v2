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
 * @file tilt4.h
 * @brief This file contains API for Tilt 4 Click Driver.
 */

#ifndef TILT4_H
#define TILT4_H

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
 * @addtogroup tilt4 Tilt 4 Click Driver
 * @brief API for configuring and manipulating Tilt 4 Click driver.
 * @{
 */

/**
 * @addtogroup tilt4_set
 * @{
 */

/**
 * @brief Tilt 4 description setting.
 * @details Specified setting for description of Tilt 4 Click driver.
 */
#define TILT4_PIN_STATE_HIGH        0x01
#define TILT4_PIN_STATE_LOW         0x00

/**
 * @brief Tilt 4 tilt switch states.
 * @details Specified tilt switch states of Tilt 4 Click driver.
 */
#define TILT4_SWITCH_OFF            0x00
#define TILT4_SWITCH_ON             0x01

/*! @} */ // tilt4_set

/**
 * @defgroup tilt4_map Tilt 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Tilt 4 Click driver.
 */

/**
 * @addtogroup tilt4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Tilt 4 Click to the selected MikroBUS.
 */
#define TILT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.led = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tilt4_map
/*! @} */ // tilt4

/**
 * @brief Tilt 4 Click context object.
 * @details Context object definition of Tilt 4 Click driver.
 */
typedef struct
{
    digital_out_t led;          /**< Led pin. */

    digital_in_t int_pin;       /**< Interrupt pin. */

} tilt4_t;

/**
 * @brief Tilt 4 Click configuration object.
 * @details Configuration object definition of Tilt 4 Click driver.
 */
typedef struct
{
    pin_name_t led;         /**< Led pin. */
    pin_name_t int_pin;     /**< Interrupt pin. */

} tilt4_cfg_t;

/**
 * @brief Tilt 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TILT4_OK = 0,
    TILT4_ERROR = -1

} tilt4_return_value_t;

/*!
 * @addtogroup tilt4 Tilt 4 Click Driver
 * @brief API for configuring and manipulating Tilt 4 Click driver.
 * @{
 */

/**
 * @brief Tilt 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tilt4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tilt4_cfg_setup ( tilt4_cfg_t *cfg );

/**
 * @brief Tilt 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #tilt4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tilt4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tilt4_init ( tilt4_t *ctx, tilt4_cfg_t *cfg );

/**
 * @brief Tilt 4 Interrupt pin reading function.
 * @details This function reads the state of the interrupt pin of Tilt 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #tilt4_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t tilt4_read_int_state ( tilt4_t *ctx );

/**
 * @brief Tilt 4 LED pin setting function.
 * @details This function sets the LED pin on the selected level level of
 * Tilt 4 Click board.
 * @param[in] ctx : Click context object.
 * See #tilt4_t object definition for detailed explanation.
 * @param[in] pin_state : State of the LED pin.
 * @return Nothing.
 * @note None.
 */
void tilt4_set_led_state ( tilt4_t *ctx, uint8_t pin_state );

#ifdef __cplusplus
}
#endif
#endif // TILT4_H

/*! @} */ // tilt4

// ------------------------------------------------------------------------ END
