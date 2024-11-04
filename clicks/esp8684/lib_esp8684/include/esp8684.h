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
 * @file esp8684.h
 * @brief This file contains API for ESP8684 Click Driver.
 */

#ifndef ESP8684_H
#define ESP8684_H

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
 * @addtogroup esp8684 ESP8684 Click Driver
 * @brief API for configuring and manipulating ESP8684 Click driver.
 * @{
 */

/**
 * @defgroup esp8684_cmd ESP8684 Device Settings
 * @brief Settings for registers of ESP8684 Click driver.
 */

/**
 * @addtogroup esp8684_cmd
 * @{
 */

/**
 * @brief ESP8684 control commands.
 * @details Specified setting for control commands of ESP8684 Click driver.
 */
#define ESP8684_CMD_AT                              "AT"
#define ESP8684_CMD_RST                             "AT+RST"
#define ESP8684_CMD_GMR                             "AT+GMR"
#define ESP8684_CMD_CWINIT                          "AT+CWINIT"
#define ESP8684_CMD_CWMODE                          "AT+CWMODE"
#define ESP8684_CMD_CWJAP                           "AT+CWJAP"
#define ESP8684_CMD_CWLAP                           "AT+CWLAP"
#define ESP8684_CMD_CWAP                            "AT+CWQAP"
#define ESP8684_CMD_CWSAP                           "AT+CWSAP"
#define ESP8684_CMD_CWLIF                           "AT+CWLIF"
#define ESP8684_CMD_CIPSTATE                        "AT+CIPSTATE"
#define ESP8684_CMD_CIPSTART                        "AT+CIPSTART"
#define ESP8684_CMD_CIPMODE                         "AT+CIPMODE"
#define ESP8684_CMD_CIPSEND                         "AT+CIPSEND"
#define ESP8684_CMD_CIPCLOSE                        "AT+CIPCLOSE"
#define ESP8684_CMD_CIFSR                           "AT+CIFSR"
#define ESP8684_CMD_CIPMUX                          "AT+CIPMUX"
#define ESP8684_CMD_CIPSERVER                       "AT+CIPSERVER"
#define ESP8684_CMD_CIPSTO                          "AT+CIPSTO"
#define ESP8684_CMD_CIPRECVMODE                     "AT+CIPRECVMODE"

/**
 * @brief ESP8684 commands response.
 * @details Specified setting for commands response of ESP8684 Click driver.
 */
#define ESP8684_RSP_RECEIVE                         "+IPD"
#define ESP8684_READY_FOR_SEND                      ">"
#define ESP8684_RSP_OK                              "OK"
#define ESP8684_RSP_SEND_OK                         "SEND OK"
#define ESP8684_RSP_ERROR                           "ERROR"
#define ESP8684_RSP_READY                           "ready"

/**
 * @brief ESP8684 pin state.
 * @details Specified setting for pin state of ESP8684 Click driver.
 */
#define ESP8684_PIN_STATE_HIGH                      0x01
#define ESP8684_PIN_STATE_LOW                       0x00


/**
 * @brief ESP8684 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ESP8684_TX_DRV_BUFFER_SIZE    100
#define ESP8684_RX_DRV_BUFFER_SIZE    300

/*! @} */ // esp8684_cmd

/**
 * @defgroup esp8684_map ESP8684 MikroBUS Map
 * @brief MikroBUS pin mapping of ESP8684 Click driver.
 */

/**
 * @addtogroup esp8684_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ESP8684 Click to the selected MikroBUS.
 */
#define ESP8684_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.bt = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // esp8684_map
/*! @} */ // esp8684

/**
 * @brief ESP8684 Click context object.
 * @details Context object definition of ESP8684 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t bt;       /**< Boot pin. */
    digital_out_t rst;      /**< Reset pin. */
    digital_out_t rts;       /**< Ready to send pin. */

    // Input pins
    digital_in_t cts;       /**< Clear to send pin. */
    
    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ ESP8684_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ ESP8684_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} esp8684_t;

/**
 * @brief ESP8684 Click configuration object.
 * @details Configuration object definition of ESP8684 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t bt;                              /**< Boot pin. */
    pin_name_t rst;                             /**< Reset pin. */
    pin_name_t rts;                             /**< Ready to send pin. */
    pin_name_t cts;                             /**< Clear to send pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} esp8684_cfg_t;

/**
 * @brief ESP8684 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ESP8684_OK = 0,
    ESP8684_ERROR = -1,
    ESP8684_OVERFLOW = -2,
    ESP8684_TIMEOUT = -3

} esp8684_return_value_t;

/*!
 * @addtogroup esp8684 ESP8684 Click Driver
 * @brief API for configuring and manipulating ESP8684 Click driver.
 * @{
 */

/**
 * @brief ESP8684 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #esp8684_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void esp8684_cfg_setup ( esp8684_cfg_t *cfg );

/**
 * @brief ESP8684 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #esp8684_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t esp8684_init ( esp8684_t *ctx, esp8684_cfg_t *cfg );

/**
 * @brief ESP8684 default configuration function.
 * @details This function executes a default configuration of ESP8684
 * Click board.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void esp8684_default_cfg ( esp8684_t *ctx );

/**
 * @brief ESP8684 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t esp8684_generic_write ( esp8684_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ESP8684 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t esp8684_generic_read ( esp8684_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief ESP8684 set rst pin state function.
 * @details This function is used to set rst pin state.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void esp8684_set_rst_pin ( esp8684_t *ctx, uint8_t pin_state );

/**
 * @brief ESP8684 set bt pin state function.
 * @details This function is used to set bt pin state.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void esp8684_set_bt_pin ( esp8684_t *ctx, uint8_t pin_state );

/**
 * @brief ESP8684 set rts pin state function.
 * @details This function is used to set rts pin state.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void esp8684_set_rts_pin ( esp8684_t *ctx, uint8_t pin_state );

/**
 * @brief ESP8684 get cts pin state function.
 * @details This function is used to get cts pin state.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @return @li @c 1 - Pin state high,
 *         @li @c 0 - Pin state low.
 * @note None.
 */
uint8_t esp8684_get_cts_pin ( esp8684_t *ctx );

/**
 * @brief ESP8684 send command with arguments function.
 * @details This function is used to send command with arguments.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] cmd : Command to be sent.
 * @param[in] args : Command arguments.
 * @return Nothing.
 * @note None.
 */
void esp8684_send_cmd ( esp8684_t *ctx, uint8_t *cmd, uint8_t *args );

/**
 * @brief ESP8684 send query command function.
 * @details This function is used to send query command.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] cmd : Query command to be sent.
 * @return Nothing.
 * @note None.
 */
void esp8684_send_query_cmd ( esp8684_t *ctx, uint8_t *cmd );

/**
 * @brief ESP8684 test query command function.
 * @details This function is used to send test command.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] cmd : Test command to be sent.
 * @return Nothing.
 * @note None.
 */
void esp8684_send_test_cmd ( esp8684_t *ctx, uint8_t *cmd );

/**
 * @brief ESP8684 connect to network function.
 * @details This function is used to connect ESP8684 to the network.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] cmd : Test command to be sent.
 * @param[in] ssid : SSID of the targeted network.
 * @param[in] password : SSID of the targeted network.
 * @return Nothing.
 * @note None.
 */
void esp8684_connect_to_network ( esp8684_t* ctx, uint8_t *ssid, uint8_t *password );

/**
 * @brief ESP8684 connect to remote host function.
 * @details This function is used to connect ESP8684 to the remote host.
 * @param[in] ctx : Click context object.
 * See #esp8684_t object definition for detailed explanation.
 * @param[in] type : Connection type ( TCP/UDP ).
 * @param[in] link_id : Connection ID.
 * @param[in] remote_host : Remote host address.
 * @param[in] remote_port : Remote host port.
 * @return Nothing.
 * @note None.
 */
void esp8684_connect_for_trans ( esp8684_t* ctx, uint8_t *type, uint8_t *link_id, uint8_t *remote_host, uint8_t *remote_port );

#ifdef __cplusplus
}
#endif
#endif // ESP8684_H

/*! @} */ // esp8684

// ------------------------------------------------------------------------ END
