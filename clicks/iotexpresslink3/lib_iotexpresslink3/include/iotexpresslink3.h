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
 * @file iotexpresslink3.h
 * @brief This file contains API for IoT ExpressLink 3 Click Driver.
 */

#ifndef IOTEXPRESSLINK3_H
#define IOTEXPRESSLINK3_H

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
 * @addtogroup iotexpresslink3 IoT ExpressLink 3 Click Driver
 * @brief API for configuring and manipulating IoT ExpressLink 3 Click driver.
 * @{
 */

/**
 * @defgroup iotexpresslink3_cmd IoT ExpressLink 3 Device Settings
 * @brief Settings for registers of IoT ExpressLink 3 Click driver.
 */

/**
 * @addtogroup iotexpresslink3_cmd
 * @{
 */

/**
 * @brief IoT ExpressLink 3 AT commands list.
 * @details Specified AT commands list of IoT ExpressLink 3 Click driver.
 */
#define IOTEXPRESSLINK3_CMD_AT                      "AT"
#define IOTEXPRESSLINK3_CMD_CONNECT                 "AT+CONNECT"
#define IOTEXPRESSLINK3_CMD_CONNECT_CHECK           "AT+CONNECT?"
#define IOTEXPRESSLINK3_CMD_DISCONNECT              "AT+DISCONNECT"
#define IOTEXPRESSLINK3_CMD_SLEEP                   "AT+SLEEP"
#define IOTEXPRESSLINK3_CMD_CONFMODE                "AT+CONFMODE"
#define IOTEXPRESSLINK3_CMD_RESET                   "AT+RESET"
#define IOTEXPRESSLINK3_CMD_FACTORY_RESET           "AT+FACTORY_RESET"
#define IOTEXPRESSLINK3_CMD_SEND                    "AT+SEND"
#define IOTEXPRESSLINK3_CMD_GET                     "AT+GET"
#define IOTEXPRESSLINK3_CMD_SUBSCRIBE               "AT+SUBSCRIBE"
#define IOTEXPRESSLINK3_CMD_UNSUBSCRIBE             "AT+UNSUBSCRIBE"
#define IOTEXPRESSLINK3_CMD_CONF                    "AT+CONF"
#define IOTEXPRESSLINK3_CMD_CONF_CHECK              "AT+CONF?"
#define IOTEXPRESSLINK3_CMD_EVENT                   "AT+EVENT?"
#define IOTEXPRESSLINK3_CMD_TIME                    "AT+TIME?"
#define IOTEXPRESSLINK3_CMD_WHERE                   "AT+WHERE?"
#define IOTEXPRESSLINK3_CMD_SEPARATOR               " "
#define IOTEXPRESSLINK3_CMD_SIGN_EQUAL              "="

/**
 * @brief IoT ExpressLink 3 config key parameters list.
 * @details Specified config key parameters list of IoT ExpressLink 3 Click driver.
 */
#define IOTEXPRESSLINK3_CONF_KEY_ABOUT              "About"
#define IOTEXPRESSLINK3_CONF_KEY_VERSION            "Version"
#define IOTEXPRESSLINK3_CONF_KEY_TECH_SPEC          "TechSpec"
#define IOTEXPRESSLINK3_CONF_KEY_THING_NAME         "ThingName"
#define IOTEXPRESSLINK3_CONF_KEY_CERTIFICATE        "Certificate"
#define IOTEXPRESSLINK3_CONF_KEY_CUSTOM_NAME        "CustomName"
#define IOTEXPRESSLINK3_CONF_KEY_ENDPOINT           "Endpoint"
#define IOTEXPRESSLINK3_CONF_KEY_ROOT_CA            "RootCA"
#define IOTEXPRESSLINK3_CONF_KEY_DEFENDER           "Defender"
#define IOTEXPRESSLINK3_CONF_KEY_HOTA_CERTIFICATE   "HOTAcertificate"
#define IOTEXPRESSLINK3_CONF_KEY_OTA_CERTIFICATE    "OTAcertificate"
#define IOTEXPRESSLINK3_CONF_KEY_SSID               "SSID"
#define IOTEXPRESSLINK3_CONF_KEY_PASSPHRASE         "Passphrase"
#define IOTEXPRESSLINK3_CONF_KEY_APN                "APN"
#define IOTEXPRESSLINK3_CONF_KEY_QOS                "QOS"
#define IOTEXPRESSLINK3_CONF_KEY_TOPIC              "Topic"

/**
 * @brief IoT ExpressLink 3 device response for AT commands.
 * @details Device response after commands.
 */
#define IOTEXPRESSLINK3_RSP_OK                      "OK"
#define IOTEXPRESSLINK3_RSP_ERR                     "ERR"

/**
 * @brief IoT ExpressLink 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define IOTEXPRESSLINK3_TX_DRV_BUFFER_SIZE          300
#define IOTEXPRESSLINK3_RX_DRV_BUFFER_SIZE          1000

/*! @} */ // iotexpresslink3_cmd

/**
 * @defgroup iotexpresslink3_map IoT ExpressLink 3 MikroBUS Map
 * @brief MikroBUS pin mapping of IoT ExpressLink 3 Click driver.
 */

/**
 * @addtogroup iotexpresslink3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IoT ExpressLink 3 Click to the selected MikroBUS.
 */
#define IOTEXPRESSLINK3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rsn = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wake = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.event = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // iotexpresslink3_map
/*! @} */ // iotexpresslink3

/**
 * @brief IoT ExpressLink 3 Click context object.
 * @details Context object definition of IoT ExpressLink 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin. */

    // Input pins
    digital_in_t event;             /**< Event pin. */
    digital_in_t wake;              /**< Wake pin. */
    digital_in_t rsn;               /**< RSN pin. */
    
    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ IOTEXPRESSLINK3_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ IOTEXPRESSLINK3_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} iotexpresslink3_t;

/**
 * @brief IoT ExpressLink 3 Click configuration object.
 * @details Configuration object definition of IoT ExpressLink 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t event;               /**< Event pin. */
    pin_name_t wake;                /**< Wake pin. */
    pin_name_t rsn;                 /**< RSN pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} iotexpresslink3_cfg_t;

/**
 * @brief IoT ExpressLink 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IOTEXPRESSLINK3_OK = 0,
    IOTEXPRESSLINK3_ERROR = -1,
    IOTEXPRESSLINK3_ERROR_TIMEOUT = -2,
    IOTEXPRESSLINK3_ERROR_CMD = -3,
    IOTEXPRESSLINK3_ERROR_UNKNOWN = -4

} iotexpresslink3_return_value_t;

/*!
 * @addtogroup iotexpresslink3 IoT ExpressLink 3 Click Driver
 * @brief API for configuring and manipulating IoT ExpressLink 3 Click driver.
 * @{
 */

/**
 * @brief IoT ExpressLink 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #iotexpresslink3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void iotexpresslink3_cfg_setup ( iotexpresslink3_cfg_t *cfg );

/**
 * @brief IoT ExpressLink 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #iotexpresslink3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iotexpresslink3_init ( iotexpresslink3_t *ctx, iotexpresslink3_cfg_t *cfg );

/**
 * @brief IoT ExpressLink 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iotexpresslink3_generic_write ( iotexpresslink3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief IoT ExpressLink 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iotexpresslink3_generic_read ( iotexpresslink3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief IoT ExpressLink 3 send cmd function.
 * @details This function send command string by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @param[in] cmd : Command string to send.
 * @return None.
 * @note None.
 */
void iotexpresslink3_send_cmd ( iotexpresslink3_t *ctx, uint8_t *cmd );

/**
 * @brief IoT ExpressLink 3 enable device function.
 * @details This function enables device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void iotexpresslink3_enable_device ( iotexpresslink3_t *ctx );

/**
 * @brief IoT ExpressLink 3 disable device function.
 * @details This function disables device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void iotexpresslink3_disable_device ( iotexpresslink3_t *ctx );

/**
 * @brief IoT ExpressLink 3 reset device function.
 * @details This function resets device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void iotexpresslink3_reset_device ( iotexpresslink3_t *ctx );

/**
 * @brief IoT ExpressLink 3 get rsn pin function.
 * @details This function returns the RSN pin logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t iotexpresslink3_get_rsn_pin ( iotexpresslink3_t *ctx );

/**
 * @brief IoT ExpressLink 3 get event pin function.
 * @details This function returns the event pin logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t iotexpresslink3_get_event_pin ( iotexpresslink3_t *ctx );

/**
 * @brief IoT ExpressLink 3 get wake pin function.
 * @details This function returns the wake pin logic state.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t iotexpresslink3_get_wake_pin ( iotexpresslink3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IOTEXPRESSLINK3_H

/*! @} */ // iotexpresslink3

// ------------------------------------------------------------------------ END
