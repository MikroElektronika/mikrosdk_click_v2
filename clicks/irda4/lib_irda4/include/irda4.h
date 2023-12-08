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
 * @file irda4.h
 * @brief This file contains API for IrDA 4 Click Driver.
 */

#ifndef IRDA4_H
#define IRDA4_H

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
 * @addtogroup irda4 IrDA 4 Click Driver
 * @brief API for configuring and manipulating IrDA 4 Click driver.
 * @{
 */

/**
 * @defgroup irda4_cmd IrDA 4 Device Settings
 * @brief Settings for registers of IrDA 4 Click driver.
 */

/**
 * @addtogroup irda4_cmd
 * @{
 */

/**
 * @brief IrDA 4 control commands.
 * @details Specified setting for control commands of IrDA 4 Click driver.
 */
#define IRDA4_SHUTDOWN_DISABLED     0x00
#define IRDA4_SHUTDOWN_ENABLED      0x01

/**
 * @brief IrDA 4 reset pin state commands.
 * @details Specified setting for reset pin state of IrDA 4 Click driver.
 */
#define IRDA4_RESET_DISABLED        0x00
#define IRDA4_RESET_ENABLED         0x01
/**
 * @brief IrDA 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define IRDA4_DRV_BUFFER_SIZE       300

/*! @} */ // irda4_cmd

/**
 * @defgroup irda4_map IrDA 4 MikroBUS Map
 * @brief MikroBUS pin mapping of IrDA 4 Click driver.
 */

/**
 * @addtogroup irda4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IrDA 4 Click to the selected MikroBUS.
 */
#define IRDA4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sd = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // irda4_map
/*! @} */ // irda4

/**
 * @brief IrDA 4 Click context object.
 * @details Context object definition of IrDA 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset pin. */
    digital_out_t sd;                           /**< TX shutdown. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ IRDA4_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ IRDA4_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} irda4_t;

/**
 * @brief IrDA 4 Click configuration object.
 * @details Configuration object definition of IrDA 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset pin. */
    pin_name_t sd;                              /**< TX shutdown. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} irda4_cfg_t;

/**
 * @brief IrDA 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRDA4_OK = 0,
    IRDA4_ERROR = -1

} irda4_return_value_t;

/*!
 * @addtogroup irda4 IrDA 4 Click Driver
 * @brief API for configuring and manipulating IrDA 4 Click driver.
 * @{
 */

/**
 * @brief IrDA 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irda4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irda4_cfg_setup ( irda4_cfg_t *cfg );

/**
 * @brief IrDA 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irda4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irda4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irda4_init ( irda4_t *ctx, irda4_cfg_t *cfg );

/**
 * @brief IrDA 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #irda4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irda4_generic_write ( irda4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief IrDA 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #irda4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irda4_generic_read ( irda4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief IrDA 4 TX shutdown function.
 * @details This function disables the transmitter mode.
 * @param[in] ctx : Click context object.
 * See #irda4_t object definition for detailed explanation.
 * @param[in] sd_state : Shutdown state.
 * @return Nothing.
 * @note None.
 */
void irda4_set_tx_shutdown ( irda4_t *ctx, uint8_t sd_state );

/**
 * @brief IrDA 4 set reset pin state function.
 * @details This function set reset pin state.
 * @param[in] ctx : Click context object.
 * See #irda4_t object definition for detailed explanation.
 * @param[in] rst_state : RST pin state.
 * @return Nothing.
 * @note None.
 */
void irda4_set_reset_state ( irda4_t *ctx, uint8_t rst_state );

/**
 * @brief IrDA 4 hardware reset function.
 * @details This function is used to perform a hardware reset.
 * @param[in] ctx : Click context object.
 * See #irda4_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void irda_hw_reset ( irda4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IRDA4_H

/*! @} */ // irda4

// ------------------------------------------------------------------------ END
