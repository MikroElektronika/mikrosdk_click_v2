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
 * @file rs485isolator5.h
 * @brief This file contains API for RS485 Isolator 5 Click Driver.
 */

#ifndef RS485ISOLATOR5_H
#define RS485ISOLATOR5_H

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
#include "drv_uart.h"

/*!
 * @addtogroup rs485isolator5 RS485 Isolator 5 Click Driver
 * @brief API for configuring and manipulating RS485 Isolator 5 Click driver.
 * @{
 */

/**
 * @defgroup rs485isolator5_cmd RS485 Isolator 5 Device Settings
 * @brief Settings of RS485 Isolator 5 Click driver.
 */

/**
 * @addtogroup rs485isolator5_cmd
 * @{
 */

/**
 * @brief RS485 Isolator 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RS485ISOLATOR5_TX_DRV_BUFFER_SIZE       256
#define RS485ISOLATOR5_RX_DRV_BUFFER_SIZE       256

/*! @} */ // rs485isolator5_cmd

/**
 * @defgroup rs485isolator5_map RS485 Isolator 5 MikroBUS Map
 * @brief MikroBUS pin mapping of RS485 Isolator 5 Click driver.
 */

/**
 * @addtogroup rs485isolator5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RS485 Isolator 5 Click to the selected MikroBUS.
 */
#define RS485ISOLATOR5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.de = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.re = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // rs485isolator5_map
/*! @} */ // rs485isolator5

/**
 * @brief RS485 Isolator 5 Click context object.
 * @details Context object definition of RS485 Isolator 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t re;                   /**< Receiver enable pin (active low). */
    digital_out_t de;                   /**< Driver enable pin (active high). */

    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ RS485ISOLATOR5_RX_DRV_BUFFER_SIZE ];    /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ RS485ISOLATOR5_TX_DRV_BUFFER_SIZE ];    /**< TX Buffer size. */

} rs485isolator5_t;

/**
 * @brief RS485 Isolator 5 Click configuration object.
 * @details Configuration object definition of RS485 Isolator 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t re;                      /**< Receiver enable pin (active low). */
    pin_name_t de;                      /**< Driver enable pin (active high). */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} rs485isolator5_cfg_t;

/**
 * @brief RS485 Isolator 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RS485ISOLATOR5_OK = 0,
    RS485ISOLATOR5_ERROR = -1

} rs485isolator5_return_value_t;

/*!
 * @addtogroup rs485isolator5 RS485 Isolator 5 Click Driver
 * @brief API for configuring and manipulating RS485 Isolator 5 Click driver.
 * @{
 */

/**
 * @brief RS485 Isolator 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rs485isolator5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rs485isolator5_cfg_setup ( rs485isolator5_cfg_t *cfg );

/**
 * @brief RS485 Isolator 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rs485isolator5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rs485isolator5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs485isolator5_init ( rs485isolator5_t *ctx, rs485isolator5_cfg_t *cfg );

/**
 * @brief RS485 Isolator 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs485isolator5_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs485isolator5_generic_write ( rs485isolator5_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief RS485 Isolator 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs485isolator5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs485isolator5_generic_read ( rs485isolator5_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief RS485 Isolator 5 receiver enable function.
 * @details This function enables the receiver output by setting the RE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #rs485isolator5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rs485isolator5_receiver_enable ( rs485isolator5_t *ctx );

/**
 * @brief RS485 Isolator 5 receiver disable function.
 * @details This function disables the receiver output by setting the RE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #rs485isolator5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rs485isolator5_receiver_disable ( rs485isolator5_t *ctx );

/**
 * @brief RS485 Isolator 5 driver enable function.
 * @details This function enables the driver input by setting the DE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #rs485isolator5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rs485isolator5_driver_enable ( rs485isolator5_t *ctx );

/**
 * @brief RS485 Isolator 5 driver disable function.
 * @details This function disables the driver input by setting the DE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #rs485isolator5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rs485isolator5_driver_disable ( rs485isolator5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RS485ISOLATOR5_H

/*! @} */ // rs485isolator5

// ------------------------------------------------------------------------ END
