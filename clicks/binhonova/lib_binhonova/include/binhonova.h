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
 * @file binhonova.h
 * @brief This file contains API for Binho Nova Click Driver.
 */

#ifndef BINHONOVA_H
#define BINHONOVA_H

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
 * @addtogroup binhonova Binho Nova Click Driver
 * @brief API for configuring and manipulating Binho Nova Click driver.
 * @{
 */

/**
 * @defgroup binhonova_cmd Binho Nova Device Settings
 * @brief Settings for registers of Binho Nova Click driver.
 */

/**
 * @addtogroup binhonova_cmd
 * @{
 */

/**
 * @brief Binho Nova driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BINHONOVA_TX_DRV_BUFFER_SIZE    100
#define BINHONOVA_RX_DRV_BUFFER_SIZE    300

/*! @} */ // binhonova_cmd

/**
 * @defgroup binhonova_map Binho Nova MikroBUS Map
 * @brief MikroBUS pin mapping of Binho Nova Click driver.
 */

/**
 * @addtogroup binhonova_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Binho Nova Click to the selected MikroBUS.
 */
#define BINHONOVA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );

/*! @} */ // binhonova_map
/*! @} */ // binhonova

/**
 * @brief Binho Nova Click context object.
 * @details Context object definition of Binho Nova Click driver.
 */
typedef struct
{
    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BINHONOVA_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ BINHONOVA_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} binhonova_t;

/**
 * @brief Binho Nova Click configuration object.
 * @details Configuration object definition of Binho Nova Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} binhonova_cfg_t;

/**
 * @brief Binho Nova Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BINHONOVA_OK = 0,
    BINHONOVA_ERROR = -1

} binhonova_return_value_t;

/*!
 * @addtogroup binhonova Binho Nova Click Driver
 * @brief API for configuring and manipulating Binho Nova Click driver.
 * @{
 */

/**
 * @brief Binho Nova configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #binhonova_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void binhonova_cfg_setup ( binhonova_cfg_t *cfg );

/**
 * @brief Binho Nova initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #binhonova_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #binhonova_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t binhonova_init ( binhonova_t *ctx, binhonova_cfg_t *cfg );

/**
 * @brief Binho Nova data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #binhonova_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t binhonova_generic_write ( binhonova_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Binho Nova data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #binhonova_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t binhonova_generic_read ( binhonova_t *ctx, uint8_t *data_out, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // BINHONOVA_H

/*! @} */ // binhonova

// ------------------------------------------------------------------------ END
