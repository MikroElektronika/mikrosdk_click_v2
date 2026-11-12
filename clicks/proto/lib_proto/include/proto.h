/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file proto.h
 * @brief This file contains API for PROTO Click Driver.
 */

#ifndef PROTO_H
#define PROTO_H

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
 * @addtogroup proto PROTO Click Driver
 * @brief API for configuring and manipulating PROTO Click driver.
 * @{
 */

/**
 * @defgroup proto_map PROTO MikroBUS Map
 * @brief MikroBUS pin mapping of PROTO Click driver.
 */

/**
 * @addtogroup proto_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PROTO Click to the selected MikroBUS.
 */
#define PROTO_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // proto_map
/*! @} */ // proto

/**
 * @brief PROTO Click context object.
 * @details Context object definition of PROTO Click driver.
 */
typedef struct
{
    digital_out_t an;           /**< AN pin output. */
    digital_out_t rst;          /**< RST pin output. */
    digital_out_t cs;           /**< CS pin output. */
    digital_out_t sck;          /**< SCK pin output. */
    digital_out_t miso;         /**< MISO pin output. */
    digital_out_t mosi;         /**< MOSI pin output. */
    digital_out_t pwm;          /**< PWM pin output. */
    digital_out_t int_pin;      /**< INT pin output. */
    digital_out_t rx_pin;       /**< RX pin output. */
    digital_out_t tx_pin;       /**< TX pin output. */
    digital_out_t scl;          /**< SCL pin output. */
    digital_out_t sda;          /**< SDA pin output. */

} proto_t;

/**
 * @brief PROTO Click configuration object.
 * @details Configuration object definition of PROTO Click driver.
 */
typedef struct
{
    pin_name_t an;              /**< AN pin output. */
    pin_name_t rst;             /**< RST pin output. */
    pin_name_t cs;              /**< CS pin output. */
    pin_name_t sck;             /**< SCK pin output. */
    pin_name_t miso;            /**< MISO pin output. */
    pin_name_t mosi;            /**< MOSI pin output. */
    pin_name_t pwm;             /**< PWM pin output. */
    pin_name_t int_pin;         /**< INT pin output. */
    pin_name_t rx_pin;          /**< RX pin output. */
    pin_name_t tx_pin;          /**< TX pin output. */
    pin_name_t scl;             /**< SCL pin output. */
    pin_name_t sda;             /**< SDA pin output. */

} proto_cfg_t;

/**
 * @brief PROTO Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROTO_OK = 0,
    PROTO_ERROR = -1

} proto_return_value_t;

/*!
 * @addtogroup proto PROTO Click Driver
 * @brief API for configuring and manipulating PROTO Click driver.
 * @{
 */

/**
 * @brief PROTO configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proto_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proto_cfg_setup ( proto_cfg_t *cfg );

/**
 * @brief PROTO initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proto_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proto_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proto_init ( proto_t *ctx, proto_cfg_t *cfg );

/**
 * @brief PROTO set pin high function.
 * @details This function sets the specified pin to high logic level.
 * @param[in] pin  Pointer to digital out pin structure from Click context object.
 * See #digital_out_t object definition for detailed explanation.
 * @return None.
 * @note The pin address should be acquired in the following way: { &click.pin }
 */
void proto_set_pin_high ( digital_out_t *pin );

/**
 * @brief PROTO set pin low function.
 * @details This function sets the specified pin to low logic level.
 * @param[in] pin  Pointer to digital out pin structure from Click context object.
 * See #digital_out_t object definition for detailed explanation.
 * @return None.
 * @note The pin address should be acquired in the following way: { &click.pin }
 */
void proto_set_pin_low ( digital_out_t *pin );

/**
 * @brief PROTO toggle pin function.
 * @details This function toggles the specified pin logic level.
 * @param[in] pin  Pointer to digital out pin structure from Click context object.
 * See #digital_out_t object definition for detailed explanation.
 * @return None.
 * @note The pin address should be acquired in the following way: { &click.pin }
 */
void proto_toggle_pin ( digital_out_t *pin );

/**
 * @brief PROTO set all pins high function.
 * @details This function sets all mikroBUS pins to high logic level.
 * @param[in] ctx : Click context object.
 * See #proto_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proto_set_all_pins_high ( proto_t *ctx );

/**
 * @brief PROTO set all pins low function.
 * @details This function sets all mikroBUS pins to low logic level.
 * @param[in] ctx : Click context object.
 * See #proto_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proto_set_all_pins_low ( proto_t *ctx );

/**
 * @brief PROTO toggle all pins function.
 * @details This function toggles all mikroBUS pins logic level.
 * @param[in] ctx : Click context object.
 * See #proto_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proto_toggle_all_pins ( proto_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROTO_H

/*! @} */ // proto

// ------------------------------------------------------------------------ END
