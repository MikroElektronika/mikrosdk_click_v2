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
 * @file usbmux.h
 * @brief This file contains API for USB MUX Click Driver.
 */

#ifndef USBMUX_H
#define USBMUX_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup usbmux USB MUX Click Driver
 * @brief API for configuring and manipulating USB MUX Click driver.
 * @{
 */

/**
 * @addtogroup usbmux_set
 * @{
 */

/**
 * @brief USB MUX pin state setting.
 * @details Specified setting for pin state of USB MUX Click driver.
 */
#define USBMUX_PIN_STATE_LOW                0x00
#define USBMUX_PIN_STATE_HIGH               0x01

/**
 * @brief USB MUX USB output selection setting.
 * @details Specified setting for output selection of USB MUX Click driver.
 */
#define USBMUX_USB1_SELECT                  0x00
#define USBMUX_USB2_SELECT                  0x01

/*! @} */ // usbmux_set

/**
 * @defgroup usbmux_map USB MUX MikroBUS Map
 * @brief MikroBUS pin mapping of USB MUX Click driver.
 */

/**
 * @addtogroup usbmux_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB MUX Click to the selected MikroBUS.
 */
#define USBMUX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.oe = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sel = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // usbmux_map
/*! @} */ // usbmux

/**
 * @brief USB MUX Click context object.
 * @details Context object definition of USB MUX Click driver.
 */
typedef struct
{
    digital_out_t oe;       /**< Bus-switch enable. */
    digital_out_t sel;      /**< Select output. */

} usbmux_t;

/**
 * @brief USB MUX Click configuration object.
 * @details Configuration object definition of USB MUX Click driver.
 */
typedef struct
{
    pin_name_t oe;          /**< Bus-switch enable. */
    pin_name_t sel;         /**< Select output. */

} usbmux_cfg_t;

/**
 * @brief USB MUX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBMUX_OK = 0,
    USBMUX_ERROR = -1

} usbmux_return_value_t;

/*!
 * @addtogroup usbmux USB MUX Click Driver
 * @brief API for configuring and manipulating USB MUX Click driver.
 * @{
 */

/**
 * @brief USB MUX configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbmux_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbmux_cfg_setup ( usbmux_cfg_t *cfg );

/**
 * @brief USB MUX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbmux_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbmux_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbmux_init ( usbmux_t *ctx, usbmux_cfg_t *cfg );

/**
 * @brief USB MUX default configuration function.
 * @details This function executes a default configuration of USB MUX
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbmux_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void usbmux_default_cfg ( usbmux_t *ctx );

/**
 * @brief USB MUX set OE pin output function.
 * @details This function is used to set output level of the OE pin of USB MUX
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbmux_t object definition for detailed explanation.
 * @param[in] pin_state : Output pin level.
 * @return Nothing.
 * @note None.
 */
void usbmux_set_oe_pin ( usbmux_t *ctx, uint8_t pin_state );

/**
 * @brief USB MUX set SEL pin output function.
 * @details This function is used to set output level of the SEL pin of USB MUX
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbmux_t object definition for detailed explanation.
 * @param[in] pin_state : Output pin level.
 * @return Nothing.
 * @note None.
 */
void usbmux_set_sel_pin ( usbmux_t *ctx, uint8_t pin_state );

/**
 * @brief USB MUX enable output function.
 * @details This function is used to enable output of USB MUX
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbmux_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void usbmux_enable_output ( usbmux_t *ctx );

/**
 * @brief USB MUX disable output function.
 * @details This function is used to disable output of USB MUX
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbmux_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void usbmux_disable_output ( usbmux_t *ctx );

/**
 * @brief USB MUX select output function.
 * @details This function is used to select output of USB MUX
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbmux_t object definition for detailed explanation.
 * @param[in] out_sel : Output selection.
 * @return Nothing.
 * @note None.
 */
void usbmux_set_output ( usbmux_t *ctx, uint8_t out_sel );

#ifdef __cplusplus
}
#endif
#endif // USBMUX_H

/*! @} */ // usbmux

// ------------------------------------------------------------------------ END
