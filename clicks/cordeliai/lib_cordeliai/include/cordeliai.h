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
 * @file cordeliai.h
 * @brief This file contains API for Cordelia-I Click Driver.
 */

#ifndef CORDELIAI_H
#define CORDELIAI_H

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
 * @addtogroup cordeliai Cordelia-I Click Driver
 * @brief API for configuring and manipulating Cordelia-I Click driver.
 * @{
 */

/**
 * @defgroup cordeliai_cmd Cordelia-I Device Settings
 * @brief Settings of Cordelia-I Click driver.
 */

/**
 * @addtogroup cordeliai_cmd
 * @{
 */

/**
 * @brief Cordelia-I control commands.
 * @details Specified setting for control commands of Cordelia-I Click driver.
 */
#define CORDELIAI_CMD_START                         "AT+start"
#define CORDELIAI_CMD_STOP                          "AT+stop"
#define CORDELIAI_CMD_TEST                          "AT+test"
#define CORDELIAI_CMD_REBOOT                        "AT+reboot"
#define CORDELIAI_CMD_FACTORY_RESET                 "AT+factoryreset"
#define CORDELIAI_CMD_HIBERNATE                     "AT+hibernate"
#define CORDELIAI_CMD_GET                           "AT+get"
#define CORDELIAI_CMD_SET                           "AT+set"
#define CORDELIAI_CMD_WLAN_SCAN                     "AT+wlanScan"
#define CORDELIAI_CMD_WLAN_CONNECT                  "AT+wlanConnect"
#define CORDELIAI_CMD_WLAN_DISCONNECT               "AT+wlanDisconnect"
#define CORDELIAI_CMD_WLAN_PROFILE_ADD              "AT+wlanProfileAdd"
#define CORDELIAI_CMD_WLAN_PROFILE_GET              "AT+wlanProfileGet"
#define CORDELIAI_CMD_WLAN_PROFILE_DEL              "AT+wlanProfileDel"
#define CORDELIAI_CMD_WLAN_SET                      "AT+wlanSet"
#define CORDELIAI_CMD_WLAN_GET                      "AT+wlanGet"
#define CORDELIAI_CMD_WLAN_POLICY_SET               "AT+wlanPolicySet"
#define CORDELIAI_CMD_WLAN_POLICY_GET               "AT+wlanPolicyGet"
#define CORDELIAI_CMD_FILE_GET_FILE_LIST            "AT+fileGetFileList"
#define CORDELIAI_CMD_FILE_OPEN                     "AT+fileOpen"
#define CORDELIAI_CMD_FILE_DEL                      "AT+fileDel"
#define CORDELIAI_CMD_FILE_GET_INFO                 "AT+fileGetInfo"
#define CORDELIAI_CMD_FILE_READ                     "AT+fileRead"
#define CORDELIAI_CMD_FILE_WRITE                    "AT+fileWrite"
#define CORDELIAI_CMD_NET_APP_GET                   "AT+netAPPGet"
#define CORDELIAI_CMD_NET_APP_SET                   "AT+netAPPSet"
#define CORDELIAI_CMD_NET_CFG_SET                   "AT+netCfgSet"
#define CORDELIAI_CMD_NET_CFG_GET                   "AT+netCfgGet"
#define CORDELIAI_CMD_IOT_CONNECT                   "AT+iotconnect"
#define CORDELIAI_CMD_IOT_DISCONNECT                "AT+iotdisconnect"
#define CORDELIAI_CMD_IOT_PUBLISH                   "AT+iotpublish"
#define CORDELIAI_CMD_IOT_ENROL                     "AT+iotenrol"

/**
 * @brief Cordelia-I device response for AT commands.
 * @details Device response after commands.
 */
#define CORDELIAI_RSP_OK                            "OK"
#define CORDELIAI_RSP_ERROR                         "ERROR"

/**
 * @brief Cordelia-I device response time for AT commands.
 * @details Device response time after commands.
 */
#define CORDELIAI_MAX_RSP_TIME_DEFAULT              5000ul
#define CORDELIAI_MAX_RSP_TIME_READY                10000ul
#define CORDELIAI_MAX_RSP_TIME_FACTORY_RESET        90000ul
#define CORDELIAI_MAX_RSP_TIME_WLAN_CONNECT         30000ul
#define CORDELIAI_MAX_RSP_TIME_MQTT_CONNECT         15000ul
#define CORDELIAI_MAX_RSP_TIME_MQTT_ECHO_RECV       10000ul

/**
 * @brief Cordelia-I device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define CORDELIAI_URC_READY                         "+eventstartup"
#define CORDELIAI_URC_WLAN_CONNECTED                "+eventwlan:connect"
#define CORDELIAI_URC_MQTT_CONNECTED                "+eventmqtt:info,\"CONNACK\""
#define CORDELIAI_URC_MQTT_RECV_DATA                "+eventmqtt:recv"

/**
 * @brief Cordelia-I driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define CORDELIAI_TX_DRV_BUFFER_SIZE                256
#define CORDELIAI_RX_DRV_BUFFER_SIZE                256

/*! @} */ // cordeliai_cmd

/**
 * @defgroup cordeliai_map Cordelia-I MikroBUS Map
 * @brief MikroBUS pin mapping of Cordelia-I Click driver.
 */

/**
 * @addtogroup cordeliai_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Cordelia-I Click to the selected MikroBUS.
 */
#define CORDELIAI_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.boot = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // cordeliai_map
/*! @} */ // cordeliai

/**
 * @brief Cordelia-I Click context object.
 * @details Context object definition of Cordelia-I Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t boot;             /**< Boot application pin (active low). */
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< UART clear to send pin. */
    digital_out_t wup;              /**< Wake-up pin (optional). */

    // Input pins
    digital_in_t rts;               /**< UART ready to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ CORDELIAI_RX_DRV_BUFFER_SIZE ]; /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ CORDELIAI_TX_DRV_BUFFER_SIZE ]; /**< TX Buffer size. */
    uint8_t cmd_buffer[ CORDELIAI_TX_DRV_BUFFER_SIZE ];     /**< Command buffer. */

} cordeliai_t;

/**
 * @brief Cordelia-I Click configuration object.
 * @details Configuration object definition of Cordelia-I Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t boot;                /**< Boot application pin (active low). */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< UART clear to send pin. */
    pin_name_t wup;                 /**< Wake-up pin (optional). */
    pin_name_t rts;                 /**< UART ready to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} cordeliai_cfg_t;

/**
 * @brief Cordelia-I Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CORDELIAI_OK = 0,
    CORDELIAI_ERROR = -1,
    CORDELIAI_ERROR_TIMEOUT = -2,
    CORDELIAI_ERROR_CMD = -3

} cordeliai_return_value_t;

/*!
 * @addtogroup cordeliai Cordelia-I Click Driver
 * @brief API for configuring and manipulating Cordelia-I Click driver.
 * @{
 */

/**
 * @brief Cordelia-I configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #cordeliai_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void cordeliai_cfg_setup ( cordeliai_cfg_t *cfg );

/**
 * @brief Cordelia-I initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #cordeliai_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cordeliai_init ( cordeliai_t *ctx, cordeliai_cfg_t *cfg );

/**
 * @brief Cordelia-I data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cordeliai_generic_write ( cordeliai_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Cordelia-I data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cordeliai_generic_read ( cordeliai_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Cordelia-I set BOOT pin function.
 * @details This function sets the BOOT pin logic state.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void cordeliai_set_boot_pin ( cordeliai_t *ctx, uint8_t state );

/**
 * @brief Cordelia-I set WUP pin function.
 * @details This function sets the wake-up (WUP) pin logic state.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void cordeliai_set_wup_pin ( cordeliai_t *ctx, uint8_t state );

/**
 * @brief Cordelia-I set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void cordeliai_set_rst_pin ( cordeliai_t *ctx, uint8_t state );

/**
 * @brief Cordelia-I set CTS pin function.
 * @details This function sets the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void cordeliai_set_cts_pin ( cordeliai_t *ctx, uint8_t state );

/**
 * @brief Cordelia-I get RTS pin function.
 * @details This function returns the ready to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t cordeliai_get_rts_pin ( cordeliai_t *ctx );

/**
 * @brief Cordelia-I reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void cordeliai_reset_device ( cordeliai_t *ctx );

/**
 * @brief Cordelia-I cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void cordeliai_cmd_run ( cordeliai_t *ctx, uint8_t *cmd );

/**
 * @brief Cordelia-I cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void cordeliai_cmd_set ( cordeliai_t *ctx, uint8_t *cmd, uint8_t *value );

#ifdef __cplusplus
}
#endif
#endif // CORDELIAI_H

/*! @} */ // cordeliai

// ------------------------------------------------------------------------ END
