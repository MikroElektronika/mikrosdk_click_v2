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
 * @file c5vto3v3.h
 * @brief This file contains API for 5V to 3V3 Click Driver.
 */

#ifndef C5VTO3V3_H
#define C5VTO3V3_H

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
 * @addtogroup c5vto3v3 5V to 3V3 Click Driver
 * @brief API for configuring and manipulating 5V to 3V3 Click driver.
 * @{
 */

/**
 * @defgroup c5vto3v3_map 5V to 3V3 MikroBUS Map
 * @brief MikroBUS pin mapping of 5V to 3V3 Click driver.
 */

/**
 * @addtogroup c5vto3v3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 5V to 3V3 Click to the selected MikroBUS.
 */
#define C5VTO3V3_MAP_MIKROBUS( cfg, mikrobus ) \
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

/*! @} */ // c5vto3v3_map
/*! @} */ // c5vto3v3

/**
 * @brief 5V to 3V3 Click context object.
 * @details Context object definition of 5V to 3V3 Click driver.
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

} c5vto3v3_t;

/**
 * @brief 5V to 3V3 Click configuration object.
 * @details Configuration object definition of 5V to 3V3 Click driver.
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

} c5vto3v3_cfg_t;

/**
 * @brief 5V to 3V3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C5VTO3V3_OK = 0,
    C5VTO3V3_ERROR = -1

} c5vto3v3_return_value_t;

/*!
 * @addtogroup c5vto3v3 5V to 3V3 Click Driver
 * @brief API for configuring and manipulating 5V to 3V3 Click driver.
 * @{
 */

/**
 * @brief 5V to 3V3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c5vto3v3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c5vto3v3_cfg_setup ( c5vto3v3_cfg_t *cfg );

/**
 * @brief 5V to 3V3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c5vto3v3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c5vto3v3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5vto3v3_init ( c5vto3v3_t *ctx, c5vto3v3_cfg_t *cfg );

/**
 * @brief 5V to 3V3 toggle all function.
 * @details This function toggles all mikroBUS pins together a desired number of times
 * with the selected delay between each toggle.
 * @param[in] ctx : Click context object.
 * See #c5vto3v3_t object definition for detailed explanation.
 * @param[in] num_toggles : Number of toggles.
 * @param[in] toggle_delay_ms : Delay in milliseconds between each toggle.
 * @return None.
 * @note None.
 */
void c5vto3v3_toggle_all ( c5vto3v3_t *ctx, uint16_t num_toggles, uint16_t toggle_delay_ms );

/**
 * @brief 5V to 3V3 toggle seq function.
 * @details This function toggles all mikroBUS pins one by one with the selected delay
 * between each toggle.
 * @param[in] ctx : Click context object.
 * See #c5vto3v3_t object definition for detailed explanation.
 * @param[in] toggle_delay_ms : Delay in milliseconds between each toggle.
 * @return None.
 * @note None.
 */
void c5vto3v3_toggle_seq ( c5vto3v3_t *ctx, uint16_t toggle_delay_ms );

#ifdef __cplusplus
}
#endif
#endif // C5VTO3V3_H

/*! @} */ // c5vto3v3

// ------------------------------------------------------------------------ END
