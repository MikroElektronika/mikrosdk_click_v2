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
 * @file iotexpresslink.h
 * @brief This file contains API for IoT ExpressLink Click Driver.
 */

#ifndef IOTEXPRESSLINK_H
#define IOTEXPRESSLINK_H

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
 * @addtogroup iotexpresslink IoT ExpressLink Click Driver
 * @brief API for configuring and manipulating IoT ExpressLink Click driver.
 * @{
 */

/**
 * @defgroup iotexpresslink_cmd IoT ExpressLink Device Settings
 * @brief Settings for registers of IoT ExpressLink Click driver.
 */

/**
 * @addtogroup iotexpresslink_cmd
 * @{
 */

/**
 * @brief IoT ExpressLink AT commands list.
 * @details Specified AT commands list of IoT ExpressLink Click driver.
 */
#define IOTEXPRESSLINK_CMD_AT                       "AT"
#define IOTEXPRESSLINK_CMD_CONNECT                  "AT+CONNECT"
#define IOTEXPRESSLINK_CMD_CONNECT_CHECK            "AT+CONNECT?"
#define IOTEXPRESSLINK_CMD_DISCONNECT               "AT+DISCONNECT"
#define IOTEXPRESSLINK_CMD_SLEEP                    "AT+SLEEP"
#define IOTEXPRESSLINK_CMD_CONFMODE                 "AT+CONFMODE"
#define IOTEXPRESSLINK_CMD_RESET                    "AT+RESET"
#define IOTEXPRESSLINK_CMD_FACTORY_RESET            "AT+FACTORY_RESET"
#define IOTEXPRESSLINK_CMD_SEND                     "AT+SEND"
#define IOTEXPRESSLINK_CMD_GET                      "AT+GET"
#define IOTEXPRESSLINK_CMD_SUBSCRIBE                "AT+SUBSCRIBE"
#define IOTEXPRESSLINK_CMD_UNSUBSCRIBE              "AT+UNSUBSCRIBE"
#define IOTEXPRESSLINK_CMD_CONF                     "AT+CONF"
#define IOTEXPRESSLINK_CMD_CONF_CHECK               "AT+CONF?"
#define IOTEXPRESSLINK_CMD_EVENT                    "AT+EVENT?"
#define IOTEXPRESSLINK_CMD_TIME                     "AT+TIME"
#define IOTEXPRESSLINK_CMD_WHERE                    "AT+WHERE"
#define IOTEXPRESSLINK_CMD_SEPARATOR                " "
#define IOTEXPRESSLINK_CMD_SIGN_EQUAL               "="

/**
 * @brief IoT ExpressLink config key parameters list.
 * @details Specified config key parameters list of IoT ExpressLink Click driver.
 */
#define IOTEXPRESSLINK_CONF_KEY_ABOUT               "About"
#define IOTEXPRESSLINK_CONF_KEY_VERSION             "Version"
#define IOTEXPRESSLINK_CONF_KEY_TECH_SPEC           "TechSpec"
#define IOTEXPRESSLINK_CONF_KEY_THING_NAME          "ThingName"
#define IOTEXPRESSLINK_CONF_KEY_CERTIFICATE         "Certificate"
#define IOTEXPRESSLINK_CONF_KEY_CUSTOM_NAME         "CustomName"
#define IOTEXPRESSLINK_CONF_KEY_ENDPOINT            "Endpoint"
#define IOTEXPRESSLINK_CONF_KEY_ROOT_CA             "RootCA"
#define IOTEXPRESSLINK_CONF_KEY_DEFENDER            "Defender"
#define IOTEXPRESSLINK_CONF_KEY_HOTA_CERTIFICATE    "HOTAcertificate"
#define IOTEXPRESSLINK_CONF_KEY_OTA_CERTIFICATE     "OTAcertificate"
#define IOTEXPRESSLINK_CONF_KEY_SSID                "SSID"
#define IOTEXPRESSLINK_CONF_KEY_PASSPHRASE          "Passphrase"
#define IOTEXPRESSLINK_CONF_KEY_APN                 "APN"
#define IOTEXPRESSLINK_CONF_KEY_QOS                 "QOS"
#define IOTEXPRESSLINK_CONF_KEY_TOPIC               "Topic"

/**
 * @brief IoT ExpressLink device response for AT commands.
 * @details Device response after commands.
 */
#define IOTEXPRESSLINK_RSP_OK                       "OK"
#define IOTEXPRESSLINK_RSP_ERR                      "ERR"

/**
 * @brief IoT ExpressLink driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define IOTEXPRESSLINK_TX_DRV_BUFFER_SIZE           300
#define IOTEXPRESSLINK_RX_DRV_BUFFER_SIZE           1000

/*! @} */ // iotexpresslink_cmd

/**
 * @defgroup iotexpresslink_map IoT ExpressLink MikroBUS Map
 * @brief MikroBUS pin mapping of IoT ExpressLink Click driver.
 */

/**
 * @addtogroup iotexpresslink_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IoT ExpressLink Click to the selected MikroBUS.
 */
#define IOTEXPRESSLINK_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wake = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.event = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // iotexpresslink_map
/*! @} */ // iotexpresslink

/**
 * @brief IoT ExpressLink Click context object.
 * @details Context object definition of IoT ExpressLink Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active low). */

    // Input pins
    digital_in_t event;         /**< Event pin. */
    digital_in_t wake;          /**< Wake pin. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ IOTEXPRESSLINK_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    uint8_t uart_tx_buffer[ IOTEXPRESSLINK_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} iotexpresslink_t;

/**
 * @brief IoT ExpressLink Click configuration object.
 * @details Configuration object definition of IoT ExpressLink Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t event;           /**< Event pin. */
    pin_name_t wake;            /**< Wake pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} iotexpresslink_cfg_t;

/**
 * @brief IoT ExpressLink Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IOTEXPRESSLINK_OK = 0,
    IOTEXPRESSLINK_ERROR = -1,
    IOTEXPRESSLINK_ERROR_TIMEOUT = -2,
    IOTEXPRESSLINK_ERROR_CMD = -3,
    IOTEXPRESSLINK_ERROR_UNKNOWN = -4

} iotexpresslink_return_value_t;

/*!
 * @addtogroup iotexpresslink IoT ExpressLink Click Driver
 * @brief API for configuring and manipulating IoT ExpressLink Click driver.
 * @{
 */

/**
 * @brief IoT ExpressLink configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #iotexpresslink_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void iotexpresslink_cfg_setup ( iotexpresslink_cfg_t *cfg );

/**
 * @brief IoT ExpressLink initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #iotexpresslink_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iotexpresslink_init ( iotexpresslink_t *ctx, iotexpresslink_cfg_t *cfg );

/**
 * @brief IoT ExpressLink data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iotexpresslink_generic_write ( iotexpresslink_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief IoT ExpressLink data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iotexpresslink_generic_read ( iotexpresslink_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief IoT ExpressLink send cmd function.
 * @details This function send command string by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @param[in] cmd : Command string to send.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void iotexpresslink_send_cmd ( iotexpresslink_t *ctx, uint8_t *cmd );

/**
 * @brief IoT ExpressLink enable device function.
 * @details This function enables device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void iotexpresslink_enable_device ( iotexpresslink_t *ctx );

/**
 * @brief IoT ExpressLink disable device function.
 * @details This function disables device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void iotexpresslink_disable_device ( iotexpresslink_t *ctx );

/**
 * @brief IoT ExpressLink reset device function.
 * @details This function resets device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void iotexpresslink_reset_device ( iotexpresslink_t *ctx );

/**
 * @brief IoT ExpressLink get event pin function.
 * @details This function returns the event pin logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t iotexpresslink_get_event_pin ( iotexpresslink_t *ctx );

/**
 * @brief IoT ExpressLink get wake pin function.
 * @details This function returns the wake pin logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t iotexpresslink_get_wake_pin ( iotexpresslink_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IOTEXPRESSLINK_H

/*! @} */ // iotexpresslink

// ------------------------------------------------------------------------ END
