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
 * @file xportedge.h
 * @brief This file contains API for XPort EDGE Click Driver.
 */

#ifndef XPORTEDGE_H
#define XPORTEDGE_H

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
 * @addtogroup xportedge XPort EDGE Click Driver
 * @brief API for configuring and manipulating XPort EDGE Click driver.
 * @{
 */

/**
 * @defgroup xportedge_cmd XPort EDGE Device Settings
 * @brief Settings of XPort EDGE Click driver.
 */

/**
 * @addtogroup xportedge_cmd
 * @{
 */

/**
 * @brief XPort EDGE control commands.
 * @details Specified setting for control commands of XPort EDGE Click driver.
 */
#define XPORTEDGE_CMD_TERMINAL                           ">"
#define XPORTEDGE_CMD_LIST_COMMANDS                      "?"
#define XPORTEDGE_CMD_ENTER                              "\r\n"
#define XPORTEDGE_CMD_EXIT                               "exit"
#define XPORTEDGE_CMD_SHOW                               "show"
#define XPORTEDGE_CMD_CONFIG                             "config"
#define XPORTEDGE_CMD_HELP                               "help"
#define XPORTEDGE_CMD_STATUS                             "status"
#define XPORTEDGE_CMD_STATUS_CLOCK                       "Clock"
#define XPORTEDGE_CMD_STATUS_DEVICE                      "Device"
#define XPORTEDGE_CMD_STATUS_DIAGNOSTICS                 "Diagnostics"
#define XPORTEDGE_CMD_STATUS_HTTP_SERVER                 "HTTP Server"
#define XPORTEDGE_CMD_STATUS_DEVICE_FACTORY_RESET        "Factory Defaults"
#define XPORTEDGE_CMD_STATUS_INTERFACE_ETH0              "Interface eth0"
#define XPORTEDGE_CMD_STATUS_DIAGNOSTICS_PING            "Ping"
#define XPORTEDGE_CMD_STATUS_DIAGNOSTICS_PING_HOST(ADR)  "ping " ADR

/**
 * @brief XPort EDGE driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define XPORTEDGE_TX_DRV_BUFFER_SIZE                     200
#define XPORTEDGE_RX_DRV_BUFFER_SIZE                     1000

/*! @} */ // xportedge_cmd

/**
 * @defgroup xportedge_map XPort EDGE MikroBUS Map
 * @brief MikroBUS pin mapping of XPort EDGE Click driver.
 */

/**
 * @addtogroup xportedge_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of XPort EDGE Click to the selected MikroBUS.
 */
#define XPORTEDGE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dtr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // xportedge_map
/*! @} */ // xportedge

/**
 * @brief XPort EDGE Click context object.
 * @details Context object definition of XPort EDGE Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< Clear to send pin. */

    // Input pins
    digital_in_t dtr;               /**< Data terminal ready pin. */
    digital_in_t rts;               /**< Request to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ XPORTEDGE_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ XPORTEDGE_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} xportedge_t;

/**
 * @brief XPort EDGE Click configuration object.
 * @details Configuration object definition of XPort EDGE Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< Clear to send pin. */
    pin_name_t dtr;                 /**< Data terminal ready pin. */
    pin_name_t rts;                 /**< Request to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} xportedge_cfg_t;

/**
 * @brief XPort EDGE Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    XPORTEDGE_OK = 0,
    XPORTEDGE_ERROR = -1,
    XPORTEDGE_ERROR_TIMEOUT = -2

} xportedge_return_value_t;

/*!
 * @addtogroup xportedge XPort EDGE Click Driver
 * @brief API for configuring and manipulating XPort EDGE Click driver.
 * @{
 */

/**
 * @brief XPort EDGE configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #xportedge_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void xportedge_cfg_setup ( xportedge_cfg_t *cfg );

/**
 * @brief XPort EDGE initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #xportedge_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xportedge_init ( xportedge_t *ctx, xportedge_cfg_t *cfg );

/**
 * @brief XPort EDGE data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xportedge_generic_write ( xportedge_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief XPort EDGE data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xportedge_generic_read ( xportedge_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief XPort EDGE send cmd function.
 * @details This function sends a command string by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @param[in] cmd : Command string to send.
 * @return None.
 * @note None.
 */
void xportedge_send_cmd ( xportedge_t *ctx, uint8_t *cmd );

/**
 * @brief XPort EDGE list commands function.
 * @details This function lists commands at current level by sending the question mark by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xportedge_list_commands ( xportedge_t *ctx );

/**
 * @brief XPort EDGE send enter function.
 * @details This function sends enter (new line) by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xportedge_send_enter ( xportedge_t *ctx );

/**
 * @brief XPort EDGE set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xportedge_set_rst_pin ( xportedge_t *ctx, uint8_t state );

/**
 * @brief XPort EDGE set CTS pin function.
 * @details This function sets the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xportedge_set_cts_pin ( xportedge_t *ctx, uint8_t state );

/**
 * @brief XPort EDGE get RTS pin function.
 * @details This function returns the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xportedge_get_rts_pin ( xportedge_t *ctx );

/**
 * @brief XPort EDGE get DTR pin function.
 * @details This function returns the DTR pin logic state.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xportedge_get_dtr_pin ( xportedge_t *ctx );

/**
 * @brief XPort EDGE reset device function.
 * @details This function resets device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xportedge_reset_device ( xportedge_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // XPORTEDGE_H

/*! @} */ // xportedge

// ------------------------------------------------------------------------ END
