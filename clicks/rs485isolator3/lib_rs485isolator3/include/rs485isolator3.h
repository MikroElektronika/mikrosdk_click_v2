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
 * @file rs485isolator3.h
 * @brief This file contains API for RS485 Isolator 3 Click Driver.
 */

#ifndef RS485ISOLATOR3_H
#define RS485ISOLATOR3_H

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
 * @addtogroup rs485isolator3 RS485 Isolator 3 Click Driver
 * @brief API for configuring and manipulating RS485 Isolator 3 Click driver.
 * @{
 */

/**
 * @defgroup rs485isolator3_cmd RS485 Isolator 3 Device Settings
 * @brief Settings for registers of RS485 Isolator 3 Click driver.
 */

/**
 * @addtogroup rs485isolator3_cmd
 * @{
 */

/**
 * @brief RS485 Isolator 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RS485ISOLATOR3_TX_DRV_BUFFER_SIZE    100
#define RS485ISOLATOR3_RX_DRV_BUFFER_SIZE    300

/*! @} */ // rs485isolator3_cmd

/**
 * @defgroup rs485isolator3_map RS485 Isolator 3 MikroBUS Map
 * @brief MikroBUS pin mapping of RS485 Isolator 3 Click driver.
 */

/**
 * @addtogroup rs485isolator3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RS485 Isolator 3 Click to the selected MikroBUS.
 */
#define RS485ISOLATOR3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.re  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.de  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.inv = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // rs485isolator3_map
/*! @} */ // rs485isolator3

/**
 * @brief RS485 Isolator 3 Click context object.
 * @details Context object definition of RS485 Isolator 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t re;   /**< Receiver Enable. */
    digital_out_t de;   /**< Driver Enable. */
    digital_out_t inv;  /**< Receiver Inversion. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ RS485ISOLATOR3_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ RS485ISOLATOR3_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} rs485isolator3_t;

/**
 * @brief RS485 Isolator 3 Click configuration object.
 * @details Configuration object definition of RS485 Isolator 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t re;              /**< Receiver Enable. */
    pin_name_t de;              /**< Driver Enable. */
    pin_name_t inv;             /**< Receiver Inversion. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} rs485isolator3_cfg_t;

/**
 * @brief RS485 Isolator 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RS485ISOLATOR3_OK = 0,
    RS485ISOLATOR3_ERROR = -1

} rs485isolator3_return_value_t;

/*!
 * @addtogroup rs485isolator3 RS485 Isolator 3 Click Driver
 * @brief API for configuring and manipulating RS485 Isolator 3 Click driver.
 * @{
 */

/**
 * @brief RS485 Isolator 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rs485isolator3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rs485isolator3_cfg_setup ( rs485isolator3_cfg_t *cfg );

/**
 * @brief RS485 Isolator 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rs485isolator3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs485isolator3_init ( rs485isolator3_t *ctx, rs485isolator3_cfg_t *cfg );

/**
 * @brief RS485 Isolator 3 default configuration function.
 * @details This function executes a default configuration of RS485 Isolator 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void rs485isolator3_default_cfg ( rs485isolator3_t *ctx );

/**
 * @brief RS485 Isolator 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs485isolator3_generic_write ( rs485isolator3_t *ctx, char *data_in, uint16_t len );

/**
 * @brief RS485 Isolator 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs485isolator3_generic_read ( rs485isolator3_t *ctx, char *data_out, uint16_t len );

/**
 * @brief RS485 Isolator 3 enable receiver input function.
 * @details This function enables receiver input.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs485isolator3_enable_receiver_input ( rs485isolator3_t *ctx );

/**
 * @brief RS485 Isolator 3 disable receiver input function.
 * @details This function disables receiver input.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs485isolator3_disable_receiver_input ( rs485isolator3_t *ctx );

/**
 * @brief RS485 Isolator 3 enable output function.
 * @details This function enables output.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs485isolator3_enable_output ( rs485isolator3_t *ctx );

/**
 * @brief RS485 Isolator 3 disable output function.
 * @details This function disable output.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs485isolator3_disable_output ( rs485isolator3_t *ctx );

/**
 * @brief RS485 Isolator 3 invert output function.
 * @details This function is used to invert the A and B receiver inputs to 
 * correct for reversed cable installation.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs485isolator3_inverted_inputs ( rs485isolator3_t *ctx );

/**
 * @brief RS485 Isolator 3 not invert output function.
 * @details This function is used if the cable invert function is not used.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs485isolator3_not_inverted_inputs ( rs485isolator3_t *ctx );

/**
 * @brief RS485 Isolator 3 send data function.
 * @details This function is used to send data bit by bit with 100 mS delay.
 * @param[in] ctx : Click context object.
 * See #rs485isolator3_t object definition for detailed explanation.
 * @param[in] command : Data buffer for sending.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs485isolator3_send_bit_by_bit ( rs485isolator3_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif // RS485ISOLATOR3_H

/*! @} */ // rs485isolator3

// ------------------------------------------------------------------------ END
