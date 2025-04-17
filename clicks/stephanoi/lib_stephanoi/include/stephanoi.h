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
 * @file stephanoi.h
 * @brief This file contains API for Stephano-I Click Driver.
 */

#ifndef STEPHANOI_H
#define STEPHANOI_H

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
 * @addtogroup stephanoi Stephano-I Click Driver
 * @brief API for configuring and manipulating Stephano-I Click driver.
 * @{
 */

/**
 * @defgroup stephanoi_cmd Stephano-I Device Settings
 * @brief Settings for registers of Stephano-I Click driver.
 */

/**
 * @addtogroup stephanoi_cmd
 * @{
 */

/**
 * @brief Stephano-I control commands.
 * @details Specified setting for control commands of Stephano-I Click driver.
 */
#define STEPHANOI_CMD_AT                            "AT"
#define STEPHANOI_CMD_GET_VERSION                   "AT+GMR"
#define STEPHANOI_CMD_FACTORY_RESET                 "AT+RESTORE"
#define STEPHANOI_CMD_SET_WIFI_MODE                 "AT+CWMODE"
#define STEPHANOI_CMD_CONNECT_TO_AP                 "AT+CWJAP"
#define STEPHANOI_CMD_SET_MULTIPLE_CONNECTION_MODE  "AT+CIPMUX"
#define STEPHANOI_CMD_SET_SOCKET_RECEIVING_MODE     "AT+CIPRECVMODE"
#define STEPHANOI_CMD_ESTABLISH_TCP_UDP_CONNECTION  "AT+CIPSTART"
#define STEPHANOI_CMD_SEND_DATA_VIA_CONNECTION      "AT+CIPSEND"
#define STEPHANOI_CMD_RECEIVE_DATA_VIA_CONNECTION   "AT+CIPRECVDATA"
#define STEPHANOI_CMD_CLOSE_TCP_UDP_CONNECTION      "AT+CIPCLOSE"
#define STEPHANOI_CMD_BLE_INIT                      "AT+BLEINIT"
#define STEPHANOI_CMD_BLE_ADDRESS                   "AT+BLEADDR"
#define STEPHANOI_CMD_BLE_NAME                      "AT+BLENAME"
#define STEPHANOI_CMD_BLE_CONNECT                   "AT+BLECONN"
#define STEPHANOI_CMD_BLE_DISCONNECT                "AT+BLEDISCONN"
#define STEPHANOI_CMD_BLE_SET_ADVERTISING_DATA      "AT+BLEADVDATA"
#define STEPHANOI_CMD_BLE_START_ADVERTISING         "AT+BLEADVSTART"
#define STEPHANOI_CMD_BLE_GATTS_CREATE              "AT+BLEGATTSSRVCRE"
#define STEPHANOI_CMD_BLE_GATTS_START               "AT+BLEGATTSSRVSTART"
#define STEPHANOI_CMD_BLE_GATTS_NOTIFY              "AT+BLEGATTSNTFY"

/**
 * @brief Stephano-I device response for AT commands.
 * @details Device response after commands.
 */
#define STEPHANOI_RSP_OK                            "OK"
#define STEPHANOI_RSP_ERROR                         "ERROR"

/**
 * @brief Stephano-I device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define STEPHANOI_URC_READY                         "ready"
#define STEPHANOI_URC_RECEIVED_DATA                 "+IPD"
#define STEPHANOI_URC_BLE_CONNECTED                 "+BLECONN:"
#define STEPHANOI_URC_BLE_DISCONNECTED              "+BLEDISCONN:"

/**
 * @brief Stephano-I driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define STEPHANOI_TX_DRV_BUFFER_SIZE                256
#define STEPHANOI_RX_DRV_BUFFER_SIZE                256

/*! @} */ // stephanoi_cmd

/**
 * @defgroup stephanoi_map Stephano-I MikroBUS Map
 * @brief MikroBUS pin mapping of Stephano-I Click driver.
 */

/**
 * @addtogroup stephanoi_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stephano-I Click to the selected MikroBUS.
 */
#define STEPHANOI_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // stephanoi_map
/*! @} */ // stephanoi

/**
 * @brief Stephano-I Click context object.
 * @details Context object definition of Stephano-I Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< UART clear to send pin. */
    digital_out_t wup;              /**< Wake-up pin (optional). */

    // Input pins
    digital_in_t rts;               /**< UART ready to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ STEPHANOI_RX_DRV_BUFFER_SIZE ]; /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ STEPHANOI_TX_DRV_BUFFER_SIZE ]; /**< TX Buffer size. */
    uint8_t cmd_buffer[ STEPHANOI_TX_DRV_BUFFER_SIZE ];     /**< Command buffer. */

} stephanoi_t;

/**
 * @brief Stephano-I Click configuration object.
 * @details Configuration object definition of Stephano-I Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
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

} stephanoi_cfg_t;

/**
 * @brief Stephano-I Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPHANOI_OK = 0,
    STEPHANOI_ERROR = -1,
    STEPHANOI_ERROR_TIMEOUT = -2,
    STEPHANOI_ERROR_CMD = -3

} stephanoi_return_value_t;

/*!
 * @addtogroup stephanoi Stephano-I Click Driver
 * @brief API for configuring and manipulating Stephano-I Click driver.
 * @{
 */

/**
 * @brief Stephano-I configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stephanoi_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stephanoi_cfg_setup ( stephanoi_cfg_t *cfg );

/**
 * @brief Stephano-I initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stephanoi_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stephanoi_init ( stephanoi_t *ctx, stephanoi_cfg_t *cfg );

/**
 * @brief Stephano-I data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stephanoi_generic_write ( stephanoi_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Stephano-I data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stephanoi_generic_read ( stephanoi_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Stephano-I set WUP pin function.
 * @details This function sets the wake-up (WUP) pin logic state.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void stephanoi_set_wup_pin ( stephanoi_t *ctx, uint8_t state );

/**
 * @brief Stephano-I set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void stephanoi_set_rst_pin ( stephanoi_t *ctx, uint8_t state );

/**
 * @brief Stephano-I set CTS pin function.
 * @details This function sets the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void stephanoi_set_cts_pin ( stephanoi_t *ctx, uint8_t state );

/**
 * @brief Stephano-I get RTS pin function.
 * @details This function returns the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stephanoi_get_rts_pin ( stephanoi_t *ctx );

/**
 * @brief Stephano-I reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stephanoi_reset_device ( stephanoi_t *ctx );

/**
 * @brief Stephano-I cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void stephanoi_cmd_run ( stephanoi_t *ctx, uint8_t *cmd );

/**
 * @brief Stephano-I cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void stephanoi_cmd_set ( stephanoi_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief Stephano-I cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void stephanoi_cmd_get ( stephanoi_t *ctx, uint8_t *cmd );

/**
 * @brief Stephano-I cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #stephanoi_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void stephanoi_cmd_help ( stephanoi_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // STEPHANOI_H

/*! @} */ // stephanoi

// ------------------------------------------------------------------------ END
