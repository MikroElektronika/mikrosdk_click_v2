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
 * @file wifly.h
 * @brief This file contains API for WiFly Click Driver.
 */

#ifndef WIFLY_H
#define WIFLY_H

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
#include "drv_uart.h"

/*!
 * @addtogroup wifly WiFly Click Driver
 * @brief API for configuring and manipulating WiFly Click driver.
 * @{
 */

/**
 * @defgroup wifly_cmd WiFly Device Settings
 * @brief Settings of WiFly Click driver.
 * @{
 */

/**
 * @brief WiFly Click UART and buffer settings.
 * @details These macros define the factory baud rate and bounded driver buffers.
 * @note The module and host baud rates must match. Hardware flow control is disabled.
 */
#define WIFLY_BAUD_RATE                 9600
#define WIFLY_TX_DRV_BUFFER_SIZE        128
#define WIFLY_RX_DRV_BUFFER_SIZE        512
#define WIFLY_COMMAND_SIZE              128
#define WIFLY_RESPONSE_SIZE             512
#define WIFLY_DATA_SIZE                 64
#define WIFLY_SSID_SIZE                 33
#define WIFLY_PASSWORD_SIZE             64

/**
 * @brief WiFly Click transport selection.
 * @details These macros select UDP or TCP in the RN-131 IP protocol register.
 */
#define WIFLY_PROTOCOL_UDP              1
#define WIFLY_PROTOCOL_TCP              2

/**
 * @brief WiFly Click response timeouts.
 * @details These macros specify maximum UART idle wait times in milliseconds.
 * @note Library polling uses fixed one-millisecond delays.
 */
#define WIFLY_COMMAND_TIMEOUT           3000
#define WIFLY_BOOT_TIMEOUT              5000
#define WIFLY_CONNECT_TIMEOUT           20000

/**
 * @brief WiFly Click commands and reply tokens.
 * @details These macros define RN-131 settings, control commands, and replies used by the driver.
 * @note Commands omit CR; the escape sequence is sent without CR or LF.
 */
#define WIFLY_CMD_SET_UART_MODE         "set uart mode 1"
#define WIFLY_CMD_SET_UART_FLOW         "set uart flow 0"
#define WIFLY_CMD_SET_WLAN_JOIN         "set wlan join 0"
#define WIFLY_CMD_SET_WLAN_CHANNEL      "set wlan channel 0"
#define WIFLY_CMD_SET_IP_DHCP           "set ip dhcp 1"
#define WIFLY_CMD_SET_IP_FLAGS          "set ip flags 0x6"
#define WIFLY_CMD_SET_SYS_AUTOCONN      "set sys autoconn 0"
#define WIFLY_CMD_SET_SYS_AUTOSLEEP     "set sys autosleep 0"
#define WIFLY_CMD_SET_SYS_SLEEP         "set sys sleep 0"
#define WIFLY_CMD_SET_COMM_IDLE         "set comm idle 0"
#define WIFLY_CMD_SET_COMM_REMOTE       "set comm remote 0"
#define WIFLY_CMD_SET_COMM_OPEN         "set comm open *OPEN*"
#define WIFLY_CMD_SET_COMM_CLOSE        "set comm close *CLOS*"
#define WIFLY_CMD_SET_COMM_TIME         "set comm time 100"
#define WIFLY_CMD_SET_COMM_MATCH        "set comm match 0"
#define WIFLY_CMD_SET_BCAST_INTERVAL    "set broadcast interval 0"
#define WIFLY_CMD_SET_SYS_PRINTLVL      "set sys printlvl 0"
#define WIFLY_CMD_SET_COMM_SIZE_PFX     "set comm size "
#define WIFLY_CMD_SET_OPT_REPLACE_PFX   "set opt replace "
#define WIFLY_CMD_SET_WLAN_SSID_PFX     "set wlan ssid "
#define WIFLY_CMD_SET_WLAN_PHRASE_PFX   "set wlan phrase "
#define WIFLY_CMD_SET_IP_PROTOCOL_PFX   "set ip protocol "
#define WIFLY_CMD_SET_IP_LOCALPORT_PFX  "set ip localport "
#define WIFLY_CMD_SET_IP_HOST_PFX       "set ip host "
#define WIFLY_CMD_SET_IP_REMOTE_PFX     "set ip remote "
#define WIFLY_CMD_OPEN_PFX              "open "
#define WIFLY_CMD_JOIN_PFX              "join "
#define WIFLY_CMD_ESCAPE                "$$$"
#define WIFLY_CMD_LEAVE                 "leave"
#define WIFLY_CMD_SHOW_NET              "show net"
#define WIFLY_CMD_CLOSE                 "close"
#define WIFLY_CMD_EXIT                  "exit"
#define WIFLY_CMD_GET_VERSION           "ver"
#define WIFLY_CMD_GET_MAC               "get mac"
#define WIFLY_CMD_GET_IP                "get ip"
#define WIFLY_REPLY_PROMPT              ">"
#define WIFLY_REPLY_AOK                 "AOK"
#define WIFLY_REPLY_CMD                 "CMD"
#define WIFLY_REPLY_EXIT                "EXIT"
#define WIFLY_REPLY_READY               "*READY*"
#define WIFLY_REPLY_OPEN                "*OPEN*"
#define WIFLY_REPLY_CLOSED              "*CLOS*"
#define WIFLY_REPLY_ERROR               "ERR:"
#define WIFLY_REPLY_ERROR_CR            "ERR\r"
#define WIFLY_STATUS_ASSOC_OK           "Assoc=OK"
#define WIFLY_STATUS_DHCP_OK            "DHCP=OK"

/*! @} */ // wifly_cmd

/**
 * @defgroup wifly_map WiFly MikroBUS Map
 * @brief MikroBUS pin mapping of WiFly Click driver.
 * @{
 */

/**
 * @brief WiFly Click MikroBUS pin mapping.
 * @details This macro maps WiFly Click pins to the selected MikroBUS.
 * @note AP is the RN-131 GPIO9 boot-mode input and is held low for normal operation.
 */
#define WIFLY_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wake = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ap_pin = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // wifly_map
/*! @} */ // wifly

/**
 * @brief WiFly Click context object.
 * @details This structure stores the UART driver, command buffers, and active transport state.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                      /**< Active-low module reset. */
    digital_out_t wake;                     /**< Active-high force-awake input. */
    digital_out_t ap_pin;                   /**< GPIO9 boot-mode input; keep low. */

    // UART and ring buffers
    uart_t uart;                            /**< UART driver object. */
    uint8_t uart_rx_buffer[ WIFLY_RX_DRV_BUFFER_SIZE ]; /**< Receive ring buffer. */
    uint8_t uart_tx_buffer[ WIFLY_TX_DRV_BUFFER_SIZE ]; /**< Transmit ring buffer. */

    // ASCII command state
    char command[ WIFLY_COMMAND_SIZE ];     /**< Command construction buffer. */
    char response[ WIFLY_RESPONSE_SIZE ];   /**< Last reply, always null-terminated. */
    char ssid[ WIFLY_SSID_SIZE ];           /**< SSID with spaces encoded for the RN-131. */
    uint16_t response_length;               /**< Number of stored reply bytes. */
    uint16_t local_port;                    /**< Last bound local port. */
    uint8_t protocol;                       /**< Last applied transport, or zero after reset. */
    uint8_t command_mode;                   /**< Nonzero after a confirmed CMD reply. */
    uint8_t socket_open;                    /**< Nonzero while a data session is active. */

} wifly_t;

/**
 * @brief WiFly Click configuration object.
 * @details This structure defines the pins and host UART settings of WiFly Click.
 */
typedef struct
{
    pin_name_t rx_pin;                      /**< Host UART RX pin. */
    pin_name_t tx_pin;                      /**< Host UART TX pin. */
    pin_name_t rst;                         /**< Active-low module reset pin. */
    pin_name_t wake;                        /**< Active-high force-awake pin. */
    pin_name_t ap_pin;                      /**< GPIO9 boot-mode input on MikroBUS PWM. */

    uint32_t baud_rate;                     /**< Host baud rate; factory module setting is 9600. */
    bool uart_blocking;                     /**< Raw UART blocking mode; use false with this API. */
    uart_data_bits_t data_bit;              /**< UART data bits. */
    uart_parity_t parity_bit;               /**< UART parity. */
    uart_stop_bits_t stop_bit;              /**< UART stop bits. */

} wifly_cfg_t;

/**
 * @brief WiFly Click return values.
 * @details These values distinguish command, timeout, argument, and data errors.
 */
typedef enum
{
    WIFLY_OK = 0,                           /**< Operation completed. */
    WIFLY_ERROR = -1,                       /**< UART or initialization failure. */
    WIFLY_TIMEOUT = -2,                     /**< Expected reply or echo did not arrive. */
    WIFLY_ERROR_RESPONSE = -3,              /**< Module returned ERR. */
    WIFLY_ERROR_OVERFLOW = -4,              /**< Reply or command exceeds its buffer. */
    WIFLY_ERROR_ARGUMENT = -5,              /**< Invalid argument or operation state. */
    WIFLY_ERROR_CLOSED = -6,                /**< TCP close indication received. */
    WIFLY_ERROR_DATA = -7                   /**< Received echo differs from the transmitted text. */

} wifly_return_value_t;

/*!
 * @addtogroup wifly WiFly Click Driver
 * @brief API for configuring and manipulating WiFly Click driver.
 * @{
 */

/**
 * @brief WiFly configuration object setup function.
 * @details This function initializes Click configuration structure to initial values.
 * @param[out] cfg : Click configuration structure.
 * See #wifly_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All pins are unconnected; UART defaults to 9600 baud, 8N1, and nonblocking mode.
 */
void wifly_cfg_setup ( wifly_cfg_t *cfg );

/**
 * @brief WiFly initialization function.
 * @details This function initializes all necessary pins and peripherals used for this Click board.
 * @param[out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wifly_cfg_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c <0 - Error.
 * See #wifly_return_value_t definition for detailed explanation.
 * @note Use nonblocking UART for bounded command and receive waits.
 */
err_t wifly_init ( wifly_t *ctx, wifly_cfg_t *cfg );

/**
 * @brief WiFly default configuration function.
 * @details This function resets the module and configures manual association, DHCP, and UART data transfer.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c <0 - Error.
 * See #wifly_return_value_t definition for detailed explanation.
 * @note Settings remain in RAM. No factory reset, save, or firmware update is performed.
 */
err_t wifly_default_cfg ( wifly_t *ctx );

/**
 * @brief WiFly reset function.
 * @details This function pulses the hardware reset input and waits for the module boot banner.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return @li @c 0 - Boot banner received,
 *         @li @c <0 - Error or boot timeout.
 * See #wifly_return_value_t definition for detailed explanation.
 * @note A saved quiet configuration can suppress the banner. Reset clears cached network state.
 */
err_t wifly_reset ( wifly_t *ctx );

/**
 * @brief WiFly command transmission function.
 * @details This function sends an ASCII command with a carriage return and waits for the expected reply.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[in] command : Null-terminated command without a carriage return or line feed.
 * @param[in] expected : Nonempty reply token, such as "AOK" or ">".
 * @param[in] timeout_ms : Maximum UART idle wait time in milliseconds.
 * @return @li @c 0 - Expected reply received,
 *         @li @c <0 - Error.
 * See #wifly_return_value_t definition for detailed explanation.
 * @note Command mode is required. The full reply is stored in ctx->response.
 * Use the socket functions for commands that change between Command and Data mode.
 */
err_t wifly_send_command ( wifly_t *ctx, char *command, char *expected, uint16_t timeout_ms );

/**
 * @brief WiFly WLAN connection function.
 * @details This function sets the SSID and passphrase, joins the network, and waits for DHCP.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[in] ssid : Printable ASCII network name, from 1 to 32 characters.
 * @param[in] password : WPA/WPA2 passphrase of 8 to 63 characters, or empty for an open network.
 * @return @li @c 0 - Associated and DHCP complete,
 *         @li @c <0 - Error.
 * See #wifly_return_value_t definition for detailed explanation.
 * @note Spaces are encoded using an unused replacement character. WEP and enterprise networks are unsupported.
 */
err_t wifly_connect ( wifly_t *ctx, char *ssid, char *password );

/**
 * @brief WiFly socket opening function.
 * @details This function configures the peer and opens a TCP connection or enables UDP data transfer.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[in] protocol : WIFLY_PROTOCOL_TCP or WIFLY_PROTOCOL_UDP.
 * @param[in] peer_ip : Remote IPv4 address in dotted-decimal notation.
 * @param[in] peer_port : Nonzero remote port number.
 * @param[in] local_port : Nonzero local listening port number.
 * @return @li @c 0 - Data session opened,
 *         @li @c <0 - Error.
 * See #wifly_return_value_t definition for detailed explanation.
 * @note A protocol or local-port change rejoins the WLAN to bind the new settings.
 * Call wifly_connect first and close the previous session before opening another.
 */
err_t wifly_open_socket ( wifly_t *ctx, uint8_t protocol, char *peer_ip, uint16_t peer_port, uint16_t local_port );

/**
 * @brief WiFly socket closing function.
 * @details This function closes TCP or leaves UDP Data mode and returns to Command mode.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return @li @c 0 - Session closed,
 *         @li @c <0 - Error.
 * See #wifly_return_value_t definition for detailed explanation.
 * @note UDP is connectionless; this operation ends the local data session.
 * Finish reading the expected payload before closing because command entry discards pending UART input.
 */
err_t wifly_close_socket ( wifly_t *ctx );

/**
 * @brief WiFly data transmission function.
 * @details This function queues application bytes for the active TCP or UDP data session.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[in] data_in : Input data buffer.
 * @param[in] len : Number of bytes, from 1 to WIFLY_DATA_SIZE.
 * @return @li @c 0 - All bytes queued,
 *         @li @c <0 - Error.
 * See #wifly_return_value_t definition for detailed explanation.
 * @note Success does not confirm delivery. Wait for an application reply before sending another UDP message.
 * Avoid an isolated $$$ payload because the RN-131 can interpret it as Command mode entry.
 */
err_t wifly_send ( wifly_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WiFly data reception function.
 * @details This function reads currently available bytes from the active data session.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[out] data_out : Output data buffer.
 * @param[in] capacity : Maximum number of bytes to read.
 * @return @li @c >0 - Number of bytes read,
 *         @li @c 0 - No bytes available,
 *         @li @c <0 - Error.
 * See #wifly_return_value_t definition for detailed explanation.
 * @note No terminator is added. UART reads do not preserve UDP packet boundaries.
 * TCP status strings, including *CLOS*, are delivered in the same byte stream.
 */
err_t wifly_receive ( wifly_t *ctx, uint8_t *data_out, uint16_t capacity );

/**
 * @brief WiFly generic data writing function.
 * @details This function writes a desired number of data bytes by using the UART serial interface.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return Number of bytes written, or a negative UART error.
 * @note Raw access does not track command mode or retry a partial write.
 */
err_t wifly_generic_write ( wifly_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WiFly generic data reading function.
 * @details This function reads a desired number of data bytes by using the UART serial interface.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Maximum number of bytes to read.
 * @return Number of bytes read; zero or a negative UART result when empty or on error.
 * @note Raw access does not parse responses or add a terminator.
 */
err_t wifly_generic_read ( wifly_t *ctx, uint8_t *data_out, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // WIFLY_H

/*! @} */ // wifly

// ------------------------------------------------------------------------ END
