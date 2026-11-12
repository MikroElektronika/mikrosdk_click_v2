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
 * @file wifi4.h
 * @brief This file contains API for WiFi 4 Click Driver.
 */

#ifndef WIFI4_H
#define WIFI4_H

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
 * @addtogroup wifi4 WiFi 4 Click Driver
 * @brief API for configuring and manipulating WiFi 4 Click driver.
 * @{
 */

/**
 * @defgroup wifi4_cmd WiFi 4 Device Settings
 * @brief Settings of WiFi 4 Click driver.
 */

/**
 * @addtogroup wifi4_cmd
 * @{
 */

/**
 * @brief WiFi 4 control commands.
 * @details Specified setting for control commands of WiFi 4 Click driver.
 */
#define WIFI4_CMD_AT                    "AT"
#define WIFI4_CMD_RESET                 "AT+CFUN"
#define WIFI4_CMD_HELP                  "AT+S.HELP"
#define WIFI4_CMD_GET_CFG               "AT+S.GCFG"
#define WIFI4_CMD_SET_CFG               "AT+S.SCFG"
#define WIFI4_CMD_SSID                  "AT+S.SSIDTXT"
#define WIFI4_CMD_SHOW_CFG              "AT&V"
#define WIFI4_CMD_FACTORY_RESET         "AT&F"
#define WIFI4_CMD_SAVE_CFG              "AT&W"
#define WIFI4_CMD_STATUS                "AT+S.STS"
#define WIFI4_CMD_WIFI                  "AT+S.WIFI"
#define WIFI4_CMD_ROAM                  "AT+S.ROAM"
#define WIFI4_CMD_SCAN                  "AT+S.SCAN"
#define WIFI4_CMD_PING                  "AT+S.PING"
#define WIFI4_CMD_SOCKET_OPEN           "AT+S.SOCKON"
#define WIFI4_CMD_SOCKET_WRITE          "AT+S.SOCKW"
#define WIFI4_CMD_SOCKET_QUERY          "AT+S.SOCKQ"
#define WIFI4_CMD_SOCKET_READ           "AT+S.SOCKR"
#define WIFI4_CMD_SOCKET_CLOSE          "AT+S.SOCKC"
#define WIFI4_CMD_SOCKET_SERVER         "AT+S.SOCKD"
#define WIFI4_CMD_HTTP_GET              "AT+S.HTTPGET"
#define WIFI4_CMD_HTTP_POST             "AT+S.HTTPPOST"
#define WIFI4_CMD_HTTP_SERVER           "AT+S.HTTPD"
#define WIFI4_CMD_GPIO_CFG              "AT+S.GPIOC"
#define WIFI4_CMD_GPIO_READ             "AT+S.GPIOR"
#define WIFI4_CMD_GPIO_WRITE            "AT+S.GPIOW"

/**
 * @brief WiFi 4 command responses and asynchronous indications.
 * @details Line prefixes distinguish responses from command echoes and network names.
 */
#define WIFI4_RSP_OK                    "\r\nOK\r\n"
#define WIFI4_RSP_ERROR                 "\r\nERROR"
#define WIFI4_RSP_CONSOLE_READY         "\r\n+WIND:0:"
#define WIFI4_RSP_WIFI_UP               "\r\n+WIND:24:"
#define WIFI4_RSP_WIFI_READY            "\r\n+WIND:32:"
#define WIFI4_RSP_WIFI_DOWN             "\r\n+WIND:38:"
#define WIFI4_RSP_SOCKET_OK             "\r\n OK\r\n"
#define WIFI4_RSP_SOCKET_ID             "ID: "
#define WIFI4_RSP_SOCKET_LENGTH         "DATALEN: "

/**
 * @brief WiFi 4 device response time for AT commands.
 * @details Polling delay budgets in milliseconds; processing and logging add execution time.
 */
#define WIFI4_MAX_AT_DEFAULT            5000ul
#define WIFI4_MAX_BOOT_GREETING         10000ul
#define WIFI4_MAX_WIFI_CONNECT          60000ul
#define WIFI4_MAX_SCAN                  30000ul
#define WIFI4_MAX_SOCKET_OPEN           30000ul

/**
 * @brief WiFi 4 socket protocols.
 * @details Protocol arguments for #WIFI4_CMD_SOCKET_OPEN.
 */
#define WIFI4_SOCKET_TCP                "t"
#define WIFI4_SOCKET_UDP                "u"

/**
 * @brief WiFi 4 configuration arguments.
 * @details Arguments for #WIFI4_CMD_SET_CFG, #WIFI4_CMD_WIFI, #WIFI4_CMD_SCAN, and #WIFI4_CMD_STATUS.
 */
#define WIFI4_CFG_FLOW_CONTROL_OFF      "console1_hwfc,0"
#define WIFI4_CFG_STATION_MODE          "wifi_mode,1"
#define WIFI4_CFG_AUTH_OPEN             "wifi_auth_type,0"
#define WIFI4_CFG_SECURITY_OPEN         "wifi_priv_mode,0"
#define WIFI4_CFG_SECURITY_WPA          "wifi_priv_mode,2"
#define WIFI4_CFG_DHCP_ON               "ip_use_dhcp,1"
#define WIFI4_CFG_WPA_PASSWORD          "wifi_wpa_psk_text,"
#define WIFI4_WIFI_DISABLE              "0"
#define WIFI4_WIFI_ENABLE               "1"
#define WIFI4_SCAN_ACTIVE               "a,s"
#define WIFI4_STATUS_VERSION            "version"
#define WIFI4_STATUS_IP                 "ip_ipaddr"
#define WIFI4_STATUS_WIFI               "wifi_state"

/**
 * @brief WiFi 4 command and network limits.
 * @details The command limit includes the terminating carriage return.
 */
#define WIFI4_CMD_MAX_SIZE              512
#define WIFI4_SSID_MAX_SIZE             32
#define WIFI4_PASSWORD_MIN_SIZE         8
#define WIFI4_PASSWORD_MAX_SIZE         63

/**
 * @brief WiFi 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define WIFI4_TX_DRV_BUFFER_SIZE        ( WIFI4_CMD_MAX_SIZE + 1 )
#define WIFI4_RX_DRV_BUFFER_SIZE        1024

/**
 * @brief WiFi 4 pin states.
 * @details Specified pin states of WiFi 4 Click driver.
 */
#define WIFI4_PIN_STATE_HIGH            0x01
#define WIFI4_PIN_STATE_LOW             0x00

/*! @} */ // wifi4_cmd

/**
 * @defgroup wifi4_map WiFi 4 MikroBUS Map
 * @brief MikroBUS pin mapping of WiFi 4 Click driver.
 */

/**
 * @addtogroup wifi4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of WiFi 4 Click to the selected MikroBUS.
 * Module RTS is a host input on CS; module CTS is a host output on INT.
 * @note The RTS and CTS solder jumpers must be closed to use these signals.
 */
#define WIFI4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // wifi4_map
/*! @} */ // wifi4

/**
 * @brief WiFi 4 Click context object.
 * @details Context object definition of WiFi 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Active-low module reset. */
    digital_out_t cts;              /**< Module CTS input; low permits module transmission. */

    // Input pins
    digital_in_t rts;               /**< Module RTS output; low indicates ready to receive. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ WIFI4_RX_DRV_BUFFER_SIZE ]; /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ WIFI4_TX_DRV_BUFFER_SIZE ]; /**< TX Buffer size. */
    char cmd_buffer[ WIFI4_CMD_MAX_SIZE + 1 ];          /**< Command buffer, including CR and null terminator. */

} wifi4_t;

/**
 * @brief WiFi 4 Click configuration object.
 * @details Configuration object definition of WiFi 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Active-low reset on MikroBUS RST. */
    pin_name_t rts;                 /**< Module RTS output on MikroBUS CS. */
    pin_name_t cts;                 /**< Module CTS input on MikroBUS INT. */

    // Static variable
    uint32_t         baud_rate;     /**< UART baud rate; factory setting is 115200. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} wifi4_cfg_t;

/**
 * @brief WiFi 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WIFI4_OK = 0,
    WIFI4_ERROR = -1,
    WIFI4_ERROR_TIMEOUT = -2,
    WIFI4_ERROR_CMD = -3

} wifi4_return_value_t;

/*!
 * @addtogroup wifi4 WiFi 4 Click Driver
 * @brief API for configuring and manipulating WiFi 4 Click driver.
 * @{
 */

/**
 * @brief WiFi 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #wifi4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void wifi4_cfg_setup ( wifi4_cfg_t *cfg );

/**
 * @brief WiFi 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wifi4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Reset is held low until #wifi4_hw_reset is called.
 */
err_t wifi4_init ( wifi4_t *ctx, wifi4_cfg_t *cfg );

/**
 * @brief WiFi 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Number of bytes queued for transmission,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note Check the returned byte count; a short write does not transmit the complete buffer.
 * Hardware flow control is not managed automatically. Use the module's console1_hwfc=0 setting.
 */
err_t wifi4_generic_write ( wifi4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WiFi 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifi4_generic_read ( wifi4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief WiFi 4 set rst pin function.
 * @details This function sets the reset (RST) pin logic state.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @param[in] pin_state : Pin logic state: #WIFI4_PIN_STATE_LOW asserts reset.
 * @return Nothing.
 * @note RST is connected to the module's active-low reset input.
 */
void wifi4_set_rst_pin ( wifi4_t *ctx, uint8_t pin_state );

/**
 * @brief WiFi 4 set cts pin function.
 * @details This function sets the module CTS input on MikroBUS INT.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @param[in] pin_state : Pin logic state: low permits transmission, high requests a pause with hardware flow control.
 * @return Nothing.
 * @note Requires the CTS solder jumper to be closed.
 */
void wifi4_set_cts_pin ( wifi4_t *ctx, uint8_t pin_state );

/**
 * @brief WiFi 4 get rts pin function.
 * @details This function returns the module RTS output on MikroBUS CS.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @return @li @c 0 - Module permits transmission,
 *         @li @c 1 - Module requests a pause.
 * @note Valid when the RTS solder jumper is closed and module hardware flow control is enabled.
 */
uint8_t wifi4_get_rts_pin ( wifi4_t *ctx );

/**
 * @brief WiFi 4 hardware reset device function.
 * @details This function asserts reset for 100 ms, clears the UART buffers, and releases reset.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @return Nothing.
 * @note Pending UART transfers are discarded. Call only when no command is pending, or to recover after a timeout.
 * Read incoming bytes immediately and wait for #WIFI4_RSP_CONSOLE_READY before sending commands.
 * The module's saved configuration is retained; this function does not perform a factory reset.
 */
void wifi4_hw_reset ( wifi4_t *ctx );

/**
 * @brief WiFi 4 cmd run function.
 * @details This function sends a specified command to the Click module, followed by a carriage return.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @param[in] cmd : Null-terminated command string without CR or LF; may be ctx->cmd_buffer.
 * @return @li @c  0 - Complete command queued,
 *         @li @c -1 - Invalid command length, embedded line terminator, or UART write error.
 * See #err_t definition for detailed explanation.
 * @note Wait for the module response before sending another command. Success does not mean command acceptance.
 * The command limit is #WIFI4_CMD_MAX_SIZE bytes including CR. Hardware flow control is not managed automatically.
 * Binary payloads, such as SOCKW content, must be sent separately with #wifi4_generic_write.
 */
err_t wifi4_cmd_run ( wifi4_t *ctx, char *cmd );

/**
 * @brief WiFi 4 cmd set function.
 * @details This function appends an equals sign and a value string to a command, then sends it using #wifi4_cmd_run.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @param[in] cmd : Null-terminated command string without CR or LF.
 * @param[in] value : Null-terminated argument string without CR or LF.
 * @return @li @c  0 - Complete command queued,
 *         @li @c -1 - Invalid command length, embedded line terminator, or UART write error.
 * See #err_t definition for detailed explanation.
 * @note Input strings must not overlap ctx->cmd_buffer. Use the factory comma delimiter and console1_hwfc=0.
 * For queries, use the SPWF01SA command syntax, such as #WIFI4_CMD_GET_CFG with a variable name.
 */
err_t wifi4_cmd_set ( wifi4_t *ctx, char *cmd, char *value );

#ifdef __cplusplus
}
#endif
#endif // WIFI4_H

/*! @} */ // wifi4

// ------------------------------------------------------------------------ END
