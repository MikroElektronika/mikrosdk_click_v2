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
 * @file canisolator2.h
 * @brief This file contains API for CAN Isolator 2 Click Driver.
 */

#ifndef CANISOLATOR2_H
#define CANISOLATOR2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup canisolator2 CAN Isolator 2 Click Driver
 * @brief API for configuring and manipulating CAN Isolator 2 Click driver.
 * @{
 */

/**
 * @defgroup canisolator2_set CAN Isolator 2 Device Settings
 * @brief Settings for registers of CAN Isolator 2 Click driver.
 */

/**
 * @addtogroup canisolator2_set
 * @{
 */

/**
 * @brief CAN Isolator 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // canisolator2_set

/**
 * @defgroup canisolator2_map CAN Isolator 2 MikroBUS Map
 * @brief MikroBUS pin mapping of CAN Isolator 2 Click driver.
 */

/**
 * @addtogroup canisolator2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CAN Isolator 2 Click to the selected MikroBUS.
 */
#define CANISOLATOR2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );

/*! @} */ // canisolator2_map
/*! @} */ // canisolator2

/**
 * @brief CAN Isolator 2 Click context object.
 * @details Context object definition of CAN Isolator 2 Click driver.
 */
typedef struct
{
    // Modules

    uart_t uart;                                    /**< UART driver object. */

    // Buffers

    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} canisolator2_t;

/**
 * @brief CAN Isolator 2 Click configuration object.
 * @details Configuration object definition of CAN Isolator 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t rx_pin;                              /**< RX pin. */
    pin_name_t tx_pin;                              /**< TX pin. */

    // Static variable

    uint32_t          baud_rate;                    /**< Clock speed. */
    bool              uart_blocking;                /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                     /**< Data bits. */
    uart_parity_t     parity_bit;                   /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                     /**< Stop bits. */

} canisolator2_cfg_t;

/**
 * @brief CAN Isolator 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CANISOLATOR2_OK = 0,
   CANISOLATOR2_ERROR = -1

} canisolator2_return_value_t;

/*!
 * @addtogroup canisolator2 CAN Isolator 2 Click Driver
 * @brief API for configuring and manipulating CAN Isolator 2 Click driver.
 * @{
 */

/**
 * @brief CAN Isolator 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #canisolator2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void canisolator2_cfg_setup ( canisolator2_cfg_t *cfg );

/**
 * @brief CAN Isolator 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #canisolator2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #canisolator2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canisolator2_init ( canisolator2_t *ctx, canisolator2_cfg_t *cfg );

/**
 * @brief CAN Isolator 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #canisolator2_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canisolator2_generic_write ( canisolator2_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief CAN Isolator 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #canisolator2_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canisolator2_generic_read ( canisolator2_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief CAN Isolator 2 send data function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #canisolator2_t object definition for detailed explanation.
 * @param[out] tx_data : Output read data.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canisolator2_send_data ( canisolator2_t *ctx, char *tx_data );

#ifdef __cplusplus
}
#endif
#endif // CANISOLATOR2_H

/*! @} */ // canisolator2

// ------------------------------------------------------------------------ END
