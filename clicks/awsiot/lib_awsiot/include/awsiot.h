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
 * @file awsiot.h
 * @brief This file contains API for AWS IoT Click Driver.
 */

#ifndef AWSIOT_H
#define AWSIOT_H

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
 * @addtogroup awsiot AWS IoT Click Driver
 * @brief API for configuring and manipulating AWS IoT Click driver.
 * @{
 */

/**
 * @defgroup awsiot_cmd AWS IoT Device Settings
 * @brief Settings for registers of AWS IoT Click driver.
 */

/**
 * @addtogroup awsiot_cmd
 * @{
 */

/**
 * @brief AWS IoT AT commands list.
 * @details Specified AT commands list of AWS IoT Click driver.
 */
#define AWSIOT_CMD_AT                       "AT"
#define AWSIOT_CMD_CONNECT                  "AT+CONNECT"
#define AWSIOT_CMD_CONNECT_CHECK            "AT+CONNECT?"
#define AWSIOT_CMD_DISCONNECT               "AT+DISCONNECT"
#define AWSIOT_CMD_SLEEP                    "AT+SLEEP"
#define AWSIOT_CMD_CONFMODE                 "AT+CONFMODE"
#define AWSIOT_CMD_RESET                    "AT+RESET"
#define AWSIOT_CMD_FACTORY_RESET            "AT+FACTORY_RESET"
#define AWSIOT_CMD_SEND                     "AT+SEND"
#define AWSIOT_CMD_GET                      "AT+GET"
#define AWSIOT_CMD_SUBSCRIBE                "AT+SUBSCRIBE"
#define AWSIOT_CMD_UNSUBSCRIBE              "AT+UNSUBSCRIBE"
#define AWSIOT_CMD_CONF                     "AT+CONF"
#define AWSIOT_CMD_CONF_CHECK               "AT+CONF?"
#define AWSIOT_CMD_EVENT                    "AT+EVENT?"
#define AWSIOT_CMD_TIME                     "AT+TIME"
#define AWSIOT_CMD_WHERE                    "AT+WHERE"
#define AWSIOT_CMD_SEPARATOR                " "
#define AWSIOT_CMD_SIGN_EQUAL               "="

/**
 * @brief AWS IoT config key parameters list.
 * @details Specified config key parameters list of AWS IoT Click driver.
 */
#define AWSIOT_CONF_KEY_ABOUT               "About"
#define AWSIOT_CONF_KEY_VERSION             "Version"
#define AWSIOT_CONF_KEY_TECH_SPEC           "TechSpec"
#define AWSIOT_CONF_KEY_THING_NAME          "ThingName"
#define AWSIOT_CONF_KEY_CERTIFICATE         "Certificate"
#define AWSIOT_CONF_KEY_CUSTOM_NAME         "CustomName"
#define AWSIOT_CONF_KEY_ENDPOINT            "Endpoint"
#define AWSIOT_CONF_KEY_ROOT_CA             "RootCA"
#define AWSIOT_CONF_KEY_DEFENDER            "Defender"
#define AWSIOT_CONF_KEY_HOTA_CERTIFICATE    "HOTAcertificate"
#define AWSIOT_CONF_KEY_OTA_CERTIFICATE     "OTAcertificate"
#define AWSIOT_CONF_KEY_SSID                "SSID"
#define AWSIOT_CONF_KEY_PASSPHRASE          "Passphrase"
#define AWSIOT_CONF_KEY_APN                 "APN"
#define AWSIOT_CONF_KEY_QOS                 "QOS"
#define AWSIOT_CONF_KEY_TOPIC               "Topic"

/**
 * @brief AWS IoT device response for AT commands.
 * @details Device response after commands.
 */
#define AWSIOT_RSP_OK                       "OK"
#define AWSIOT_RSP_ERR                      "ERR"

/**
 * @brief AWS IoT driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define AWSIOT_TX_DRV_BUFFER_SIZE           300
#define AWSIOT_RX_DRV_BUFFER_SIZE           1000

/*! @} */ // awsiot_cmd

/**
 * @defgroup awsiot_map AWS IoT MikroBUS Map
 * @brief MikroBUS pin mapping of AWS IoT Click driver.
 */

/**
 * @addtogroup awsiot_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AWS IoT Click to the selected MikroBUS.
 */
#define AWSIOT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.boot = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.event = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.wake = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // awsiot_map
/*! @} */ // awsiot

/**
 * @brief AWS IoT Click context object.
 * @details Context object definition of AWS IoT Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t boot;         /**< Boot pin (Active low). */
    digital_out_t rst;          /**< Reset pin (Active low). */

    // Input pins
    digital_in_t event;         /**< Event pin. */
    digital_in_t wake;          /**< Wake pin. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ AWSIOT_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    uint8_t uart_tx_buffer[ AWSIOT_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} awsiot_t;

/**
 * @brief AWS IoT Click configuration object.
 * @details Configuration object definition of AWS IoT Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t boot;            /**< Boot pin (Active low). */
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t event;           /**< Event pin. */
    pin_name_t wake;            /**< Wake pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} awsiot_cfg_t;

/**
 * @brief AWS IoT Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AWSIOT_OK = 0,
    AWSIOT_ERROR = -1,
    AWSIOT_ERROR_TIMEOUT = -2,
    AWSIOT_ERROR_CMD = -3,
    AWSIOT_ERROR_UNKNOWN = -4

} awsiot_return_value_t;

/*!
 * @addtogroup awsiot AWS IoT Click Driver
 * @brief API for configuring and manipulating AWS IoT Click driver.
 * @{
 */

/**
 * @brief AWS IoT configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #awsiot_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void awsiot_cfg_setup ( awsiot_cfg_t *cfg );

/**
 * @brief AWS IoT initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #awsiot_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t awsiot_init ( awsiot_t *ctx, awsiot_cfg_t *cfg );

/**
 * @brief AWS IoT data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t awsiot_generic_write ( awsiot_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief AWS IoT data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t awsiot_generic_read ( awsiot_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief AWS IoT send cmd function.
 * @details This function send command string by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @param[in] cmd : Command string to send.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void awsiot_send_cmd ( awsiot_t *ctx, uint8_t *cmd );

/**
 * @brief AWS IoT enable device function.
 * @details This function enables device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void awsiot_enable_device ( awsiot_t *ctx );

/**
 * @brief AWS IoT disable device function.
 * @details This function disables device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void awsiot_disable_device ( awsiot_t *ctx );

/**
 * @brief AWS IoT reset device function.
 * @details This function resets device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void awsiot_reset_device ( awsiot_t *ctx );

/**
 * @brief AWS IoT set boot pin function.
 * @details This function sets the boot pin logic state.
 * @param[in] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void awsiot_set_boot_pin ( awsiot_t *ctx, uint8_t state );

/**
 * @brief AWS IoT get event pin function.
 * @details This function returns the event pin logic state.
 * @param[in] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t awsiot_get_event_pin ( awsiot_t *ctx );

/**
 * @brief AWS IoT get wake pin function.
 * @details This function returns the wake pin logic state.
 * @param[in] ctx : Click context object.
 * See #awsiot_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t awsiot_get_wake_pin ( awsiot_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // AWSIOT_H

/*! @} */ // awsiot

// ------------------------------------------------------------------------ END
