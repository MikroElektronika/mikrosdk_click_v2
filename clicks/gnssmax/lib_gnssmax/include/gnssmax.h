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
 * @file gnssmax.h
 * @brief This file contains API for GNSS MAX Click Driver.
 */

#ifndef GNSSMAX_H
#define GNSSMAX_H

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
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup gnssmax GNSS MAX Click Driver
 * @brief API for configuring and manipulating GNSS MAX Click driver.
 * @{
 */

/**
 * @defgroup gnssmax_set GNSS MAX Device Settings
 * @brief Settings for registers of GNSS MAX Click driver.
 */

/**
 * @addtogroup gnssmax_set
 * @{
 */

/**
 * @brief GNSS MAX driver buffer size.
 * @details Specified size of driver ring buffer.
 */
#define DRV_BUFFER_SIZE_TX      100
#define DRV_BUFFER_SIZE_RX      700

/*! @} */ // gnssmax_set

/**
 * @defgroup gnssmax_map GNSS MAX MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS MAX Click driver.
 */

/**
 * @addtogroup gnssmax_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS MAX Click to the selected MikroBUS.
 */
#define GNSSMAX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ext = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pps = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnssmax_map
/*! @} */ // gnssmax

/**
 * @brief GNSS MAX Click context object.
 * @details Context object definition of GNSS MAX Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset. */
    digital_out_t ext;                          /**< External interrupt. */

    // Input pins
    digital_in_t pps;                           /**< Timestamp. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE_RX ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE_TX ];  /**< Buffer size. */

} gnssmax_t;

/**
 * @brief GNSS MAX Click configuration object.
 * @details Configuration object definition of GNSS MAX Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin. */
    pin_name_t ext;                     /**< External interrupt. */
    pin_name_t pps;                     /**< Timestamp. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} gnssmax_cfg_t;

/**
 * @brief GNSS MAX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   GNSSMAX_OK = 0,
   GNSSMAX_ERROR = -1,
   GNSSMAX_ERROR_NO_DATA = -2,
   GNSSMAX_ERROR_OVERFLOW = -3

} gnssmax_return_value_t;

/*!
 * @addtogroup gnssmax GNSS MAX Click Driver
 * @brief API for configuring and manipulating GNSS MAX Click driver.
 * @{
 */

/**
 * @brief GNSS MAX configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnssmax_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssmax_cfg_setup ( gnssmax_cfg_t *cfg );

/**
 * @brief GNSS MAX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnssmax_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnssmax_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax_init ( gnssmax_t *ctx, gnssmax_cfg_t *cfg );

/**
 * @brief GNSS MAX default configuration function.
 * @details This function executes a default configuration of GNSS MAX
 * click board.
 * @param[in] ctx : Click context object.
 * See #gnssmax_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t gnssmax_default_cfg ( gnssmax_t *ctx );

/**
 * @brief GNSS MAX data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax_generic_write ( gnssmax_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief GNSS MAX data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax_generic_read ( gnssmax_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief GNSS MAX reset function.
 * @details This function toggles reset pin to reset module.
 * @param[in] ctx : Click context object.
 * See #gnssmax_t object definition for detailed explanation.
 * @return Nothing
 */
void gnssmax_reset ( gnssmax_t *ctx );

/**
 * @brief GNSS MAX sets state of external interrupt.
 * @details This function sets logic state of @b ext_int pin.
 * @param[in] ctx : Click context object.
 * See #gnssmax_t object definition for detailed explanation.
 * @param[in] state : State of pin to set.
 * @return Nothing
 */
void gnssmax_set_external_interrupt ( gnssmax_t *ctx, uint8_t state );

/**
 * @brief GNSS MAX reads timestamp pin state.
 * @details This function reads logic state of timestamp pin.
 * @param[out] ctx : Click context object.
 * See #gnssmax_t object definition for detailed explanation.
 * @return Timestamp pin state.
 */
uint8_t gnssmax_get_pps ( gnssmax_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // GNSSMAX_H

/*! @} */ // gnssmax

// ------------------------------------------------------------------------ END
