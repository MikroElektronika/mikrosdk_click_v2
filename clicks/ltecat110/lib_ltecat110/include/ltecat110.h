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
 * @file ltecat110.h
 * @brief This file contains API for LTE Cat.1 10 Click Driver.
 */

#ifndef LTECAT110_H
#define LTECAT110_H

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
 * @addtogroup ltecat110 LTE Cat.1 10 Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 10 Click driver.
 * @{
 */

/**
 * @defgroup ltecat110_cmd LTE Cat.1 10 Device Settings
 * @brief Settings of LTE Cat.1 10 Click driver.
 */

/**
 * @addtogroup ltecat110_cmd
 * @{
 */

/**
 * @brief LTE Cat.1 10 control commands.
 * @details Specified setting for control commands of LTE Cat.1 10 Click driver.
 */
#define LTECAT110_CMD_AT                            "AT"
#define LTECAT110_CMD_GET_MODEL_ID                  "AT+CGMM"
#define LTECAT110_CMD_GET_SW_VERSION                "AT+CGMR"
#define LTECAT110_CMD_GET_SERIAL_NUM                "AT+CGSN"
#define LTECAT110_CMD_FACTORY_RESET                 "AT&F"
#define LTECAT110_CMD_HARD_RESET                    "AT^RESET"
#define LTECAT110_CMD_SET_MODULE_FUNCTIONALITY      "AT+CFUN"
#define LTECAT110_CMD_EPS_NETWORK_REGISTRATION      "AT+CEREG"
#define LTECAT110_CMD_SIGNAL_QUALITY_REPORT         "AT+CSQ"
#define LTECAT110_CMD_OPERATOR_SELECTION            "AT+COPS"
#define LTECAT110_CMD_SEND_SMS                      "AT+CMGS"
#define LTECAT110_CMD_SELECT_SMS_FORMAT             "AT+CMGF"
#define LTECAT110_CMD_DEFINE_PDP_CONTEXT            "AT+CGDCONT"
#define LTECAT110_CMD_ACTIVATE_PDP_CONTEXT          "AT+CGACT"
#define LTECAT110_CMD_SHOW_PDP_ADDRESS              "AT+CGPADDR"
#define LTECAT110_CMD_START_SOCKET_SERVICE          "AT+NETOPEN"
#define LTECAT110_CMD_CONNECT_SOCKET                "AT+USOPEN"
#define LTECAT110_CMD_CLOSE_SOCKET                  "AT+USCLOSE"
#define LTECAT110_CMD_SEND_SOCKET_DATA              "AT+USSEND"
#define LTECAT110_CMD_RECEIVE_DATA_SOCKET           "AT+USGET"
#define LTECAT110_CMD_GPIO_CONFIG                   "AT+UGPIOC"

/**
 * @brief LTE Cat.1 10 device response for AT commands.
 * @details Device response after commands.
 */
#define LTECAT110_RSP_OK                            "OK"
#define LTECAT110_RSP_ERROR                         "ERROR"

/**
 * @brief LTE Cat.1 10 device response time for AT commands.
 * @details Device response time after commands.
 */
#define LTECAT110_MAX_RSP_TIME_DEFAULT              300ul
#define LTECAT110_MAX_RSP_TIME_FACTORY_RESET        30000ul
#define LTECAT110_MAX_RSP_TIME_COPS                 300000ul
#define LTECAT110_MAX_RSP_TIME_CFUN                 3000ul
#define LTECAT110_MAX_RSP_TIME_CMGS                 40000ul
#define LTECAT110_MAX_RSP_TIME_CGACT                9000ul
#define LTECAT110_MAX_RSP_TIME_UGPIOC               10000ul
#define LTECAT110_MAX_RSP_TIME_NETOPEN              120000ul
#define LTECAT110_MAX_RSP_TIME_USOPEN               120000ul
#define LTECAT110_MAX_RSP_TIME_USCLOSE              120000ul
#define LTECAT110_MAX_RSP_TIME_USSEND               120000ul
#define LTECAT110_MAX_RSP_TIME_USGET                8000ul

/**
 * @brief LTE Cat.1 10 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define LTECAT110_URC_RECEIVED_DATA                 "+USGET:"
#define LTECAT110_URC_CONNECTION_OPEN               "+USOPEN:"
#define LTECAT110_URC_CONNECTION_CLOSED             "+USCLOSE:"
#define LTECAT110_URC_NETWORK_OPEN                  "+NETOPEN: 1"
#define LTECAT110_URC_NETWORK_REGISTERED            "+CEREG: 2,1"
#define LTECAT110_URC_SMS_FORMAT_PDU                "+CMGF: 0"
#define LTECAT110_URC_SMS_FORMAT_TXT                "+CMGF: 1"

/**
 * @brief LTE Cat.1 10 power state settings.
 * @details Specified power state settings of LTE Cat.1 10 Click driver.
 */
#define LTECAT110_POWER_STATE_OFF                   0
#define LTECAT110_POWER_STATE_ON                    1
#define LTECAT110_POWER_STATE_RESET                 2

/**
 * @brief LTE Cat.1 10 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTECAT110_TX_DRV_BUFFER_SIZE                256
#define LTECAT110_RX_DRV_BUFFER_SIZE                256

/*! @} */ // ltecat110_cmd

/**
 * @defgroup ltecat110_map LTE Cat.1 10 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE Cat.1 10 Click driver.
 */

/**
 * @addtogroup ltecat110_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE Cat.1 10 Click to the selected MikroBUS.
 */
#define LTECAT110_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ltecat110_map
/*! @} */ // ltecat110

/**
 * @brief LTE Cat.1 10 Click context object.
 * @details Context object definition of LTE Cat.1 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;              /**< Power pin (active high). */
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t rts;              /**< UART ready to send pin. */

    // Input pins
    digital_in_t ring;              /**< Ring indicator pin. */
    digital_in_t cts;               /**< UART clear to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LTECAT110_RX_DRV_BUFFER_SIZE ]; /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LTECAT110_TX_DRV_BUFFER_SIZE ]; /**< TX Buffer size. */
    uint8_t cmd_buffer[ LTECAT110_TX_DRV_BUFFER_SIZE ];     /**< Command buffer. */

} ltecat110_t;

/**
 * @brief LTE Cat.1 10 Click configuration object.
 * @details Configuration object definition of LTE Cat.1 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t pwr;                 /**< Power pin (active high). */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t rts;                 /**< UART ready to send pin. */
    pin_name_t ring;                /**< Ring indicator pin. */
    pin_name_t cts;                 /**< UART clear to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} ltecat110_cfg_t;

/**
 * @brief LTE Cat.1 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTECAT110_OK = 0,
    LTECAT110_ERROR = -1,
    LTECAT110_ERROR_TIMEOUT = -2,
    LTECAT110_ERROR_CMD = -3

} ltecat110_return_value_t;

/*!
 * @addtogroup ltecat110 LTE Cat.1 10 Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 10 Click driver.
 * @{
 */

/**
 * @brief LTE Cat.1 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ltecat110_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ltecat110_cfg_setup ( ltecat110_cfg_t *cfg );

/**
 * @brief LTE Cat.1 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ltecat110_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat110_init ( ltecat110_t *ctx, ltecat110_cfg_t *cfg );

/**
 * @brief LTE Cat.1 10 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat110_generic_write ( ltecat110_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE Cat.1 10 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat110_generic_read ( ltecat110_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE Cat.1 10 set PWR pin function.
 * @details This function sets the PWR_ON pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat110_set_pwr_pin ( ltecat110_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 10 set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat110_set_rst_pin ( ltecat110_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 10 set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat110_set_rts_pin ( ltecat110_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 10 get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat110_get_ring_pin ( ltecat110_t *ctx );

/**
 * @brief LTE Cat.1 10 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat110_get_cts_pin ( ltecat110_t *ctx );

/**
 * @brief LTE Cat.1 10 set power state function.
 * @details This function sets a desired power state by toggling PWR and RST pins with a specific timing.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON,
 *                    @li @c 2 - Reset.
 * @return None.
 * @note None.
 */
void ltecat110_set_power_state ( ltecat110_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 10 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ltecat110_cmd_run ( ltecat110_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 10 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void ltecat110_cmd_set ( ltecat110_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LTE Cat.1 10 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ltecat110_cmd_get ( ltecat110_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 10 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ltecat110_cmd_help ( ltecat110_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 10 set SIM card APN function.
 * @details This function sets the APN for SIM card.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void ltecat110_set_sim_apn ( ltecat110_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE Cat.1 10 send SMS in text mode function.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void ltecat110_send_sms_text ( ltecat110_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE Cat.1 10 send SMS in PDU mode function.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #ltecat110_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat110_send_sms_pdu ( ltecat110_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // LTECAT110_H

/*! @} */ // ltecat110

// ------------------------------------------------------------------------ END
