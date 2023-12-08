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
 * @file iotexpresslink2.h
 * @brief This file contains API for IoT ExpressLink 2 Click Driver.
 */

#ifndef IOTEXPRESSLINK2_H
#define IOTEXPRESSLINK2_H

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
 * @addtogroup iotexpresslink2 IoT ExpressLink 2 Click Driver
 * @brief API for configuring and manipulating IoT ExpressLink 2 Click driver.
 * @{
 */

/**
 * @defgroup iotexpresslink2_cmd IoT ExpressLink 2 Device Settings
 * @brief Settings for registers of IoT ExpressLink 2 Click driver.
 */

/**
 * @addtogroup iotexpresslink2_cmd
 * @{
 */

/**
 * @brief IoT ExpressLink 2 AT commands list.
 * @details Specified AT commands list of IoT ExpressLink 2 Click driver.
 */
#define IOTEXPRESSLINK2_CMD_AT                      "AT"
#define IOTEXPRESSLINK2_CMD_CONNECT                 "AT+CONNECT"
#define IOTEXPRESSLINK2_CMD_CONNECT_CHECK           "AT+CONNECT?"
#define IOTEXPRESSLINK2_CMD_DISCONNECT              "AT+DISCONNECT"
#define IOTEXPRESSLINK2_CMD_SLEEP                   "AT+SLEEP"
#define IOTEXPRESSLINK2_CMD_CONFMODE                "AT+CONFMODE"
#define IOTEXPRESSLINK2_CMD_RESET                   "AT+RESET"
#define IOTEXPRESSLINK2_CMD_FACTORY_RESET           "AT+FACTORY_RESET"
#define IOTEXPRESSLINK2_CMD_SEND                    "AT+SEND"
#define IOTEXPRESSLINK2_CMD_GET                     "AT+GET"
#define IOTEXPRESSLINK2_CMD_SUBSCRIBE               "AT+SUBSCRIBE"
#define IOTEXPRESSLINK2_CMD_UNSUBSCRIBE             "AT+UNSUBSCRIBE"
#define IOTEXPRESSLINK2_CMD_CONF                    "AT+CONF"
#define IOTEXPRESSLINK2_CMD_CONF_CHECK              "AT+CONF?"
#define IOTEXPRESSLINK2_CMD_EVENT                   "AT+EVENT?"
#define IOTEXPRESSLINK2_CMD_TIME                    "AT+TIME"
#define IOTEXPRESSLINK2_CMD_WHERE                   "AT+WHERE"
#define IOTEXPRESSLINK2_CMD_SEPARATOR               " "
#define IOTEXPRESSLINK2_CMD_SIGN_EQUAL              "="

/**
 * @brief IoT ExpressLink 2 config key parameters list.
 * @details Specified config key parameters list of IoT ExpressLink 2 Click driver.
 */
#define IOTEXPRESSLINK2_CONF_KEY_ABOUT              "About"
#define IOTEXPRESSLINK2_CONF_KEY_VERSION            "Version"
#define IOTEXPRESSLINK2_CONF_KEY_TECH_SPEC          "TechSpec"
#define IOTEXPRESSLINK2_CONF_KEY_THING_NAME         "ThingName"
#define IOTEXPRESSLINK2_CONF_KEY_CERTIFICATE        "Certificate"
#define IOTEXPRESSLINK2_CONF_KEY_CERTIFICATE_PEM    "Certificate pem"
#define IOTEXPRESSLINK2_CONF_KEY_CUSTOM_NAME        "CustomName"
#define IOTEXPRESSLINK2_CONF_KEY_ENDPOINT           "Endpoint"
#define IOTEXPRESSLINK2_CONF_KEY_ROOT_CA            "RootCA"
#define IOTEXPRESSLINK2_CONF_KEY_DEFENDER           "Defender"
#define IOTEXPRESSLINK2_CONF_KEY_HOTA_CERTIFICATE   "HOTAcertificate"
#define IOTEXPRESSLINK2_CONF_KEY_OTA_CERTIFICATE    "OTAcertificate"
#define IOTEXPRESSLINK2_CONF_KEY_APN                "APN"
#define IOTEXPRESSLINK2_CONF_KEY_QOS                "QOS"
#define IOTEXPRESSLINK2_CONF_KEY_TOPIC              "Topic"

/**
 * @brief IoT ExpressLink 2 device response for AT commands.
 * @details Device response after commands.
 */
#define IOTEXPRESSLINK2_RSP_OK                      "OK"
#define IOTEXPRESSLINK2_RSP_ERR                     "ERR"

/**
 * @brief IoT ExpressLink 2 timeout in milliseconds settings.
 * @details Specified timeout in milliseconds settings of IoT ExpressLink 2 Click driver.
 */
#define IOTEXPRESSLINK2_EVENT_TIMEOUT               10000ul
#define IOTEXPRESSLINK2_CONNECT_TIMEOUT             1000000ul
#define IOTEXPRESSLINK2_NORMAL_TIMEOUT              5000ul

/**
 * @brief IoT ExpressLink 2 power settings.
 * @details Specified power settings of IoT ExpressLink 2 Click driver.
 */
#define IOTEXPRESSLINK2_POWER_ON_DELAY              15
#define IOTEXPRESSLINK2_EMERGENCY_SD_DELAY          25
#define IOTEXPRESSLINK2_EMERGENCY_SD_RETRY          5

/**
 * @brief IoT ExpressLink 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define IOTEXPRESSLINK2_TX_DRV_BUFFER_SIZE          200
#define IOTEXPRESSLINK2_RX_DRV_BUFFER_SIZE          900

/*! @} */ // iotexpresslink2_cmd

/**
 * @defgroup iotexpresslink2_map IoT ExpressLink 2 MikroBUS Map
 * @brief MikroBUS pin mapping of IoT ExpressLink 2 Click driver.
 */

/**
 * @addtogroup iotexpresslink2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IoT ExpressLink 2 Click to the selected MikroBUS.
 */
#define IOTEXPRESSLINK2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wake = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.event = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // iotexpresslink2_map
/*! @} */ // iotexpresslink2

/**
 * @brief IoT ExpressLink 2 Click context object.
 * @details Context object definition of IoT ExpressLink 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;              /**< Power-on pin. */
    digital_out_t rst;              /**< Reset pin. */

    // Input pins
    digital_in_t wake;              /**< Wake pin. */
    digital_in_t event;             /**< Event pin. */
    
    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ IOTEXPRESSLINK2_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ IOTEXPRESSLINK2_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} iotexpresslink2_t;

/**
 * @brief IoT ExpressLink 2 Click configuration object.
 * @details Configuration object definition of IoT ExpressLink 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t pwr;                 /**< Power-on pin. */
    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t wake;                /**< Wake pin. */
    pin_name_t event;               /**< Event pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} iotexpresslink2_cfg_t;

/**
 * @brief IoT ExpressLink 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IOTEXPRESSLINK2_OK = 0,
    IOTEXPRESSLINK2_ERROR = -1,
    IOTEXPRESSLINK2_ERROR_TIMEOUT = -2,
    IOTEXPRESSLINK2_ERROR_CMD = -3

} iotexpresslink2_return_value_t;

/*!
 * @addtogroup iotexpresslink2 IoT ExpressLink 2 Click Driver
 * @brief API for configuring and manipulating IoT ExpressLink 2 Click driver.
 * @{
 */

/**
 * @brief IoT ExpressLink 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #iotexpresslink2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void iotexpresslink2_cfg_setup ( iotexpresslink2_cfg_t *cfg );

/**
 * @brief IoT ExpressLink 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #iotexpresslink2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iotexpresslink2_init ( iotexpresslink2_t *ctx, iotexpresslink2_cfg_t *cfg );

/**
 * @brief IoT ExpressLink 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iotexpresslink2_generic_write ( iotexpresslink2_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief IoT ExpressLink 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iotexpresslink2_generic_read ( iotexpresslink2_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief IoT ExpressLink 2 send cmd function.
 * @details This function send command string by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @param[in] cmd : Command string to send.
 * @return None.
 * @note None.
 */
void iotexpresslink2_send_cmd ( iotexpresslink2_t *ctx, uint8_t *cmd );

/**
 * @brief IoT ExpressLink 2 set pwr pin function.
 * @details This function sets the PWR pin logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void iotexpresslink2_set_pwr_pin ( iotexpresslink2_t *ctx, uint8_t state );

/**
 * @brief IoT ExpressLink 2 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void iotexpresslink2_set_rst_pin ( iotexpresslink2_t *ctx, uint8_t state );

/**
 * @brief IoT ExpressLink 2 get wake pin function.
 * @details This function returns the wake pin logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t iotexpresslink2_get_wake_pin ( iotexpresslink2_t *ctx );

/**
 * @brief IoT ExpressLink 2 get event pin function.
 * @details This function returns the event pin logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t iotexpresslink2_get_event_pin ( iotexpresslink2_t *ctx );

/**
 * @brief IoT ExpressLink 2 power on function.
 * @details This function performs the power on sequence.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void iotexpresslink2_power_on ( iotexpresslink2_t *ctx );

/**
 * @brief IoT ExpressLink 2 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void iotexpresslink2_reset_device ( iotexpresslink2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IOTEXPRESSLINK2_H

/*! @} */ // iotexpresslink2

// ------------------------------------------------------------------------ END
