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
 * @file gnss8.h
 * @brief This file contains API for GNSS 8 Click Driver.
 */

#ifndef GNSS8_H
#define GNSS8_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/**
 * @defgroup gnss8_set GNSS 8 Device Settings
 * @brief Settings for registers of GNSS 8 Click driver.
 */

/**
 * @addtogroup gnss8_set
 * @{
 */

/**
 * @brief GNSS 8 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE_TX      100
#define DRV_BUFFER_SIZE_RX      700

/*! @} */ // gnss8_set

/**
 * @defgroup gnss8_map GNSS 8 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 8 Click driver.
 */

/**
 * @addtogroup gnss8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 8 Click to the selected MikroBUS.
 */
#define GNSS8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.req = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.apr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnss8_map
/*! @} */ // gnss8

/**
 * @brief GNSS 8 Click context object.
 * @details Context object definition of GNSS 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t apr;                          /**< AP request. */

    // Input pins
    digital_in_t rdy;                           /**< Ready. */
    digital_in_t req;                           /**< Request. */
    digital_in_t int_pin;                       /**< Interrupt. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE_RX ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE_TX ];  /**< Buffer size. */

} gnss8_t;

/**
 * @brief GNSS 8 Click configuration object.
 * @details Configuration object definition of GNSS 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rdy;                     /**< Ready. */
    pin_name_t req;                     /**< Request. */
    pin_name_t apr;                     /**< Interrupt. */
    pin_name_t int_pin;                 /**< AP request. */
                                        
    // Static variable                  
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} gnss8_cfg_t;

/**
 * @brief GNSS 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   GNSS8_OK = 0,
   GNSS8_ERROR = -1,
   GNSS8_ERROR_NO_DATA = -2,
   GNSS8_ERROR_OVERFLOW = -3

} gnss8_return_value_t;

/*!
 * @addtogroup gnss8 GNSS 8 Click Driver
 * @brief API for configuring and manipulating GNSS 8 Click driver.
 * @{
 */

/**
 * @brief GNSS 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss8_cfg_setup ( gnss8_cfg_t *cfg );

/**
 * @brief GNSS 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnss8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss8_init ( gnss8_t *ctx, gnss8_cfg_t *cfg );

/**
 * @brief Data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss8_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss8_generic_write ( gnss8_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss8_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss8_generic_read ( gnss8_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Set AP request pin state.
 * @details This function sets AP request pin to logic 1/0.
 * @param[in] ctx : Click context object.
 * See #gnss8_t object definition for detailed explanation.
 * @return Nothing.
 */
void gnss8_set_ap_req ( gnss8_t *ctx, uint8_t state );

/**
 * @brief Get request pin state.
 * @details This function reads request pin to logic 1/0.
 * @param[in] ctx : Click context object.
 * See #gnss8_t object definition for detailed explanation.
 * @return Pin state.
 */
uint8_t gnss8_get_req ( gnss8_t *ctx );

/**
 * @brief Get interrupt pin state.
 * @details This function reads interrupt pin to logic 1/0.
 * @param[in] ctx : Click context object.
 * See #gnss8_t object definition for detailed explanation.
 * @return Pin state.
 */
uint8_t gnss8_get_int ( gnss8_t *ctx );

/**
 * @brief Get ready pin state.
 * @details This function reads ready pin to logic 1/0.
 * @param[in] ctx : Click context object.
 * See #gnss8_t object definition for detailed explanation.
 * @return Pin state.
 */
uint8_t gnss8_get_rdy ( gnss8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // GNSS8_H

/*! @} */ // gnss8

// ------------------------------------------------------------------------ END
