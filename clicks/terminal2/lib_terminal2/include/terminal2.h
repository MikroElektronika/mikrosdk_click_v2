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
 * @file terminal2.h
 * @brief This file contains API for Terminal 2 Click Driver.
 */

#ifndef TERMINAL2_H
#define TERMINAL2_H

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
 * @addtogroup terminal2 Terminal 2 Click Driver
 * @brief API for configuring and manipulating Terminal 2 Click driver.
 * @{
 */

/**
 * @defgroup terminal2_map Terminal 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Terminal 2 Click driver.
 */

/**
 * @addtogroup terminal2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Terminal 2 Click to the selected MikroBUS.
 */
#define TERMINAL2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an      = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); \
    cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX )

/*! @} */ // terminal2_map
/*! @} */ // terminal2

/**
 * @brief Terminal 2 Click context object.
 * @details Context object definition of Terminal 2 Click driver.
 */
typedef struct
{
    digital_out_t scl;
    digital_out_t sda;
    digital_out_t sck;
    digital_out_t miso;
    digital_out_t mosi;
    digital_out_t cs;
    digital_out_t tx_pin;
    digital_out_t rx_pin;
    digital_out_t an;
    digital_out_t rst;
    digital_out_t pwm;
    digital_out_t int_pin;

} terminal2_t;

/**
 * @brief Terminal 2 Click configuration object.
 * @details Configuration object definition of Terminal 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;
    pin_name_t sda;
    pin_name_t sck;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t cs;
    pin_name_t tx_pin;
    pin_name_t rx_pin;
    pin_name_t an;
    pin_name_t rst;
    pin_name_t pwm;
    pin_name_t int_pin;

} terminal2_cfg_t;

/**
 * @brief Terminal 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TERMINAL2_OK = 0,
    TERMINAL2_ERROR = -1

} terminal2_return_value_t;

/*!
 * @addtogroup terminal2 Terminal 2 Click Driver
 * @brief API for configuring and manipulating Terminal 2 Click driver.
 * @{
 */

/**
 * @brief Terminal 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #terminal2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void terminal2_cfg_setup ( terminal2_cfg_t *cfg );

/**
 * @brief Terminal 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #terminal2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #terminal2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t terminal2_init ( terminal2_t *ctx, terminal2_cfg_t *cfg );

/**
 * @brief Terminal 2 set pin high function.
 * @details This function sets the specified pin to high logic level.
 * @param[in] pin  Pointer to digital out pin structure from Click context object.
 * See #digital_out_t object definition for detailed explanation.
 * @note The pin address should be acquired in the following way: { &click.pin }
 */
void terminal2_set_pin_high ( digital_out_t *pin );

/**
 * @brief Terminal 2 set pin low function.
 * @details This function sets the specified pin to low logic level.
 * @param[in] pin  Pointer to digital out pin structure from Click context object.
 * See #digital_out_t object definition for detailed explanation.
 * @note The pin address should be acquired in the following way: { &click.pin }
 */
void terminal2_set_pin_low ( digital_out_t *pin );

/**
 * @brief Terminal 2 toggle pin function.
 * @details This function toggles the specified pin logic level.
 * @param[in] pin  Pointer to digital out pin structure from Click context object.
 * See #digital_out_t object definition for detailed explanation.
 * @note The pin address should be acquired in the following way: { &click.pin }
 */
void terminal2_toggle_pin ( digital_out_t *pin );

/**
 * @brief Terminal 2 set all pins high function.
 * @details This function sets all terminal pins to high logic level.
 * @param[in] ctx : Click context object.
 * See #terminal2_t object definition for detailed explanation.
 * @note None.
 */
void terminal2_set_all_pins_high ( terminal2_t *ctx );

/**
 * @brief Terminal 2 set all pins low function.
 * @details This function sets all terminal pins to low logic level.
 * @param[in] ctx : Click context object.
 * See #terminal2_t object definition for detailed explanation.
 * @note None.
 */
void terminal2_set_all_pins_low ( terminal2_t *ctx );

/**
 * @brief Terminal 2 toggle all pins function.
 * @details This function toggles all terminal pins logic level.
 * @param[in] ctx : Click context object.
 * See #terminal2_t object definition for detailed explanation.
 * @note None.
 */
void terminal2_toggle_all_pins ( terminal2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TERMINAL2_H

/*! @} */ // terminal2

// ------------------------------------------------------------------------ END
