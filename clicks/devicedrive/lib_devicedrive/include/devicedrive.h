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
 * @file devicedrive.h
 * @brief This file contains API for DeviceDrive Click Driver.
 */

#ifndef DEVICEDRIVE_H
#define DEVICEDRIVE_H

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
 * @addtogroup devicedrive DeviceDrive Click Driver
 * @brief API for configuring and manipulating DeviceDrive Click driver.
 * @{
 */

/**
 * @defgroup devicedrive_cmd DeviceDrive Device Settings
 * @brief Settings of DeviceDrive Click driver.
 */

/**
 * @addtogroup devicedrive_cmd
 * @{
 */

/**
 * @brief DeviceDrive control commands.
 * @details JSON command names understood by compatible WRF01 firmware. Command
 * availability depends on the installed firmware. Run a command without
 * parameters with devicedrive_cmd_run, or supply JSON members with devicedrive_cmd_set.
 * @note Upgrade, file transfer, and Smart LinkUp require compatible server support.
 * The upgrade command is deprecated; use check_upgrade and get_upgrade instead.
 */
#define DEVICEDRIVE_CMD_SETUP                   "setup"
#define DEVICEDRIVE_CMD_REBOOT                  "reboot"
#define DEVICEDRIVE_CMD_STATUS                  "status"
#define DEVICEDRIVE_CMD_INFO                    "info"
#define DEVICEDRIVE_CMD_INTROSPECT              "introspect"
#define DEVICEDRIVE_CMD_CLEAR                   "clear"
#define DEVICEDRIVE_CMD_FACTORY_RESET           "factory_reset"
#define DEVICEDRIVE_CMD_DEEP_SLEEP              "deep_sleep"
#define DEVICEDRIVE_CMD_GET_TIME                "get_time"
#define DEVICEDRIVE_CMD_SMART_LINKUP            "smart_linkup"
#define DEVICEDRIVE_CMD_SEND_FILE               "send_file"
#define DEVICEDRIVE_CMD_UPGRADE                 "upgrade"
#define DEVICEDRIVE_CMD_CHECK_UPGRADE           "check_upgrade"
#define DEVICEDRIVE_CMD_GET_UPGRADE             "get_upgrade"

/**
 * @brief DeviceDrive setup parameters.
 * @details Parameter names for the setup command. String values must be JSON
 * quoted; visibility, silent_connect, debug_flags, time_zone, dst_zone, power_mode,
 * and listen_interval use JSON numbers. Settings depend on the installed firmware.
 */
#define DEVICEDRIVE_PARAM_ERROR_MODE            "error_mode"
#define DEVICEDRIVE_PARAM_DEBUG_MODE            "debug_mode"
#define DEVICEDRIVE_PARAM_DEBUG_FLAGS           "debug_flags"
#define DEVICEDRIVE_PARAM_SSID_PREFIX           "ssid_prefix"
#define DEVICEDRIVE_PARAM_HOST_PREFIX           "host_prefix"
#define DEVICEDRIVE_PARAM_VISIBILITY            "visibility"
#define DEVICEDRIVE_PARAM_NETWORK_SSID          "network_ssid"
#define DEVICEDRIVE_PARAM_NETWORK_PWD           "network_pwd"
#define DEVICEDRIVE_PARAM_SILENT_CONNECT        "silent_connect"
#define DEVICEDRIVE_PARAM_TOKEN                 "token"
#define DEVICEDRIVE_PARAM_PRODUCT_KEY           "product_key"
#define DEVICEDRIVE_PARAM_VERSION               "version"
#define DEVICEDRIVE_PARAM_MASTER_URL            "master_url"
#define DEVICEDRIVE_PARAM_TIME_ZONE             "time_zone"
#define DEVICEDRIVE_PARAM_DST_ZONE              "dst_zone"
#define DEVICEDRIVE_PARAM_POWER_MODE            "power_mode"
#define DEVICEDRIVE_PARAM_LISTEN_INTERVAL       "listen_interval"

/**
 * @brief DeviceDrive serial protocol settings.
 * @details Commands and cloud payloads end with EOT. The startup sequence is STX
 * followed by ETX, without EOT. Send-only cloud transfers append ETX before EOT.
 * The message limit excludes framing bytes and the terminating null byte.
 */
#define DEVICEDRIVE_STX                         0x02
#define DEVICEDRIVE_ETX                         0x03
#define DEVICEDRIVE_EOT                         0x04
#define DEVICEDRIVE_MESSAGE_SIZE_MAX            1024
#define DEVICEDRIVE_SSID_SIZE_MAX               32
#define DEVICEDRIVE_PASSWORD_SIZE_MAX           64
#define DEVICEDRIVE_URL_SIZE_MAX                255
#define DEVICEDRIVE_SEND_RECEIVE                0
#define DEVICEDRIVE_SEND_ONLY                   1

/**
 * @brief DeviceDrive response identifiers.
 * @details Identifiers used to recognize complete WRF01 replies. A command write
 * only queues UART data; the application must read the reply before sending again.
 */
#define DEVICEDRIVE_RSP_READY                   "\x02\x03"
#define DEVICEDRIVE_RSP_OK                      "{\"devicedrive\":{\"result\":\"OK\"}}"
#define DEVICEDRIVE_RSP_ERROR                   "{\"devicedrive\":{\"error\":"
#define DEVICEDRIVE_RSP_UNKNOWN_COMMAND         "{\"devicedrive\":{\"error\":\"UNKNOWN_COMMAND\"}}"
#define DEVICEDRIVE_RSP_INFO                    "\"Version\":"
#define DEVICEDRIVE_RSP_STATUS                  "\"status\":"
#define DEVICEDRIVE_RSP_GOT_IP                  "\"connection_status\":\"GOT_IP\""

/**
 * @brief DeviceDrive driver buffer size.
 * @details TX and RX storage sizes used by the UART driver's ring buffers.
 * Increase the RX size if incoming data can arrive faster than the application reads it.
 */
#define DEVICEDRIVE_TX_DRV_BUFFER_SIZE          128
#define DEVICEDRIVE_RX_DRV_BUFFER_SIZE          2048

/*! @} */ // devicedrive_cmd

/**
 * @defgroup devicedrive_map DeviceDrive MikroBUS Map
 * @brief MikroBUS pin mapping of DeviceDrive Click driver.
 */

/**
 * @addtogroup devicedrive_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DeviceDrive Click to the selected MikroBUS.
 */
#define DEVICEDRIVE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // devicedrive_map
/*! @} */ // devicedrive

/**
 * @brief DeviceDrive Click context object.
 * @details Context object definition of DeviceDrive Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Active-low module reset. */
    digital_out_t en;               /**< Active-high module enable. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ DEVICEDRIVE_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ DEVICEDRIVE_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} devicedrive_t;

/**
 * @brief DeviceDrive Click configuration object.
 * @details Configuration object definition of DeviceDrive Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin, mapped to mikroBUS RST. */
    pin_name_t en;                  /**< Enable pin, mapped to mikroBUS CS. */

    // UART configuration
    uint32_t         baud_rate;     /**< UART baud rate. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} devicedrive_cfg_t;

/**
 * @brief DeviceDrive Click return values.
 * @details Success is zero. Errors distinguish invalid arguments or UART write
 * timeouts from response, overflow, unsupported-command, and module-restart conditions.
 */
typedef enum
{
    DEVICEDRIVE_OK = 0,                    /**< Operation completed successfully. */
    DEVICEDRIVE_ERROR = -1,                /**< General error, often an invalid argument. */
    DEVICEDRIVE_ERROR_TIMEOUT = -2,        /**< UART write did not complete before timeout. */
    DEVICEDRIVE_ERROR_RESPONSE = -3,       /**< Module returned an error response. */
    DEVICEDRIVE_ERROR_OVERFLOW = -4,       /**< Response exceeded the application buffer. */
    DEVICEDRIVE_ERROR_UNSUPPORTED = -5,    /**< Firmware does not support the command. */
    DEVICEDRIVE_ERROR_RESTARTED = -6       /**< Module restarted before replying. */

} devicedrive_return_value_t;

/*!
 * @addtogroup devicedrive DeviceDrive Click Driver
 * @brief API for configuring and manipulating DeviceDrive Click driver.
 * @{
 */

/**
 * @brief DeviceDrive configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #devicedrive_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All used pins will be set to the unconnected state.
 */
void devicedrive_cfg_setup ( devicedrive_cfg_t *cfg );

/**
 * @brief DeviceDrive initialization function.
 * @details This function opens and configures the UART, then initializes the
 * module reset and enable pins.
 * @param[out] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #devicedrive_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - UART opened and configured,
 *         @li @c -1 - UART initialization failed.
 * See #err_t definition for detailed explanation.
 * @note Call devicedrive_hw_reset and wait for DEVICEDRIVE_RSP_READY before
 * sending the first command.
 */
err_t devicedrive_init ( devicedrive_t *ctx, devicedrive_cfg_t *cfg );

/**
 * @brief DeviceDrive data writing function.
 * @details This function writes up to the requested number of bytes to the UART.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >0 - Number of data bytes written,
 *         @li @c <=0 - No data written or error.
 * See #err_t definition for detailed explanation.
 * @note A short write is possible; use the higher-level command and message
 * functions when the complete transfer must be queued.
 */
err_t devicedrive_generic_write ( devicedrive_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief DeviceDrive data reading function.
 * @details This function reads up to the requested number of bytes from the UART.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note The function returns immediately with the bytes currently available.
 */
err_t devicedrive_generic_read ( devicedrive_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief DeviceDrive hardware reset function.
 * @details This function enables the module, holds reset low for 300 ms, clears
 * the UART buffers, and releases reset.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @return Nothing.
 * @note Wait for DEVICEDRIVE_RSP_READY after reset. Saved settings are preserved.
 */
void devicedrive_hw_reset ( devicedrive_t *ctx );

/**
 * @brief DeviceDrive command running function.
 * @details This function sends a JSON command without parameters and appends EOT.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[in] command : Command name, see DEVICEDRIVE_CMD_* macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument,
 *         @li @c -2 - UART write timeout.
 * See #err_t definition for detailed explanation.
 * @note Read the module reply separately. Command availability, including info,
 * depends on the installed firmware.
 * The clear and factory_reset commands erase settings and restart the module.
 */
err_t devicedrive_cmd_run ( devicedrive_t *ctx, char *command );

/**
 * @brief DeviceDrive command setting function.
 * @details This function sends a JSON command with additional parameters and appends EOT.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[in] command : Command name, see DEVICEDRIVE_CMD_* macros.
 * @param[in] params : Compact JSON members without outer braces or a leading comma.
 * @code
 * "\"error_mode\":\"all\",\"visibility\":0"
 * @endcode
 * An empty string supplies no parameters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or message too long,
 *         @li @c -2 - UART write timeout.
 * See #err_t definition for detailed explanation.
 * @note Command names accept lowercase letters and underscores. Parameters are
 * inserted as supplied and are not validated; provide valid JSON members without
 * repeating the command member. Read the reply separately. Setup changes may be
 * saved in module flash.
 */
err_t devicedrive_cmd_set ( devicedrive_t *ctx, char *command, char *params );

/**
 * @brief DeviceDrive network setting function.
 * @details This function sends the WiFi network name and password in one setup command.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[in] ssid : Network name, from 1 to 32 UTF-8 bytes.
 * @param[in] password : Network password, up to 64 bytes; empty for an open network.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument,
 *         @li @c -2 - UART write timeout.
 * See #err_t definition for detailed explanation.
 * @note Quotes and backslashes are escaped automatically. Control characters are
 * not supported. Wait for the OK reply, then query status until GOT_IP is reported.
 */
err_t devicedrive_set_network ( devicedrive_t *ctx, char *ssid, char *password );

/**
 * @brief DeviceDrive server setting function.
 * @details This function sends the HTTPS master endpoint URL in a setup command.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[in] url : HTTPS URL, up to 255 bytes, including the request path.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument,
 *         @li @c -2 - UART write timeout.
 * See #err_t definition for detailed explanation.
 * @note Read the OK reply separately. This is an HTTP endpoint, not an MQTT broker.
 * Requests include the module MAC and saved cloud credentials in DeviceDrive-Header.
 * Clear token and product_key before using an untrusted or public endpoint.
 */
err_t devicedrive_set_server ( devicedrive_t *ctx, char *url );

/**
 * @brief DeviceDrive message sending function.
 * @details This function sends a cloud payload followed by EOT in receive mode,
 * or ETX and EOT in send-only mode.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[in] message : Nonempty, null-terminated UTF-8 payload, up to 1024 bytes.
 * @param[in] mode : DEVICEDRIVE_SEND_RECEIVE or DEVICEDRIVE_SEND_ONLY.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or message too long,
 *         @li @c -2 - UART write timeout.
 * See #err_t definition for detailed explanation.
 * @note Use compact JSON without literal control characters. Do not use the
 * reserved devicedrive command object as a cloud payload. Read the EOT-terminated
 * server response or SENT result separately before sending another message.
 */
err_t devicedrive_send_message ( devicedrive_t *ctx, char *message, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // DEVICEDRIVE_H

/*! @} */ // devicedrive

// ------------------------------------------------------------------------ END
