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
 * @file ltecat15eu.h
 * @brief This file contains API for LTE Cat.1 5 EU Click Driver.
 */

#ifndef LTECAT15EU_H
#define LTECAT15EU_H

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
 * @addtogroup ltecat15eu LTE Cat.1 5 EU Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 5 EU Click driver.
 * @{
 */

/**
 * @defgroup ltecat15eu_cmd LTE Cat.1 5 EU Device Settings
 * @brief Settings of LTE Cat.1 5 EU Click driver.
 */

/**
 * @addtogroup ltecat15eu_cmd
 * @{
 */

/**
 * @brief LTE Cat.1 5 EU control commands.
 * @details Specified setting for control commands of LTE Cat.1 5 EU Click driver.
 */
#define LTECAT15EU_CMD_AT                             "AT"
#define LTECAT15EU_CMD_GET_MODEL_ID                   "AT+CGMM"
#define LTECAT15EU_CMD_GET_SW_VERSION                 "AT+CGMR"
#define LTECAT15EU_CMD_GET_SERIAL_NUM                 "AT+CGSN"
#define LTECAT15EU_CMD_FACTORY_RESET                  "AT&F"
#define LTECAT15EU_CMD_HARD_RESET                     "AT^RESET"
#define LTECAT15EU_CMD_DISABLE_ECHO                   "ATE0"
#define LTECAT15EU_CMD_ENABLE_ECHO                    "ATE1"
#define LTECAT15EU_CMD_SET_PHONE_FUNCTIONALITY        "AT+CFUN"
#define LTECAT15EU_CMD_NETWORK_REGISTRATION           "AT+CEREG"
#define LTECAT15EU_CMD_SIGNAL_QUALITY_REPORT          "AT+CSQ"
#define LTECAT15EU_CMD_OPERATOR_SELECTION             "AT+COPS"
#define LTECAT15EU_CMD_SEND_SMS                       "AT+CMGS"
#define LTECAT15EU_CMD_SELECT_SMS_FORMAT              "AT+CMGF"
#define LTECAT15EU_CMD_DEFINE_PDP_CONTEXT             "AT+CGDCONT"
#define LTECAT15EU_CMD_ACTIVATE_PDP_CONTEXT           "AT+CGACT"
#define LTECAT15EU_CMD_SHOW_PDP_ADDRESS               "AT+CGPADDR"
#define LTECAT15EU_CMD_HW_FUNCTION_CONFIG             "AT+SQNHWCFG"
#define LTECAT15EU_CMD_SET_LED_BLINK_MODE             "AT+SQNLED"
#define LTECAT15EU_CMD_OPEN_TCP_UDP_CONNECTION        "AT+SQNSD"
#define LTECAT15EU_CMD_SEND_DATA_VIA_CONNECTION       "AT+SQNSSEND"
#define LTECAT15EU_CMD_RECEIVE_DATA_VIA_CONNECTION    "AT+SQNSRECV"
#define LTECAT15EU_CMD_CLOSE_TCP_UDP_CONNECTION       "AT+SQNSH"

/**
 * @brief LTE Cat.1 5 EU device response for AT commands.
 * @details Device response after commands.
 */
#define LTECAT15EU_RSP_OK                             "OK"
#define LTECAT15EU_RSP_ERROR                          "ERROR"

/**
 * @brief LTE Cat.1 5 EU device response time for AT commands.
 * @details Device response time after commands.
 */
#define LTECAT15EU_MAX_RSP_TIME_DEFAULT               300ul
#define LTECAT15EU_MAX_RSP_TIME_FIRST_RSP             2500ul
#define LTECAT15EU_MAX_RSP_TIME_FACT_RESET            30000ul
#define LTECAT15EU_MAX_RSP_TIME_HARD_RESET            30000ul
#define LTECAT15EU_MAX_RSP_TIME_COPS                  120000ul
#define LTECAT15EU_MAX_RSP_TIME_CFUN                  30000ul
#define LTECAT15EU_MAX_RSP_TIME_CMGS                  30000ul
#define LTECAT15EU_MAX_RSP_TIME_CGACT                 30000ul
#define LTECAT15EU_MAX_RSP_TIME_SQNSD                 90000ul
#define LTECAT15EU_MAX_RSP_TIME_SQNSSEND              90000ul

/**
 * @brief LTE Cat.1 5 EU device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define LTECAT15EU_URC_READY                          "+SYSSTART"
#define LTECAT15EU_URC_RECEIVED_DATA                  "+SQNSRING:"
#define LTECAT15EU_URC_CONNECTION_OPEN                "+SQNSD:"
#define LTECAT15EU_URC_CONNECTION_CLOSED              "+SQNSH:"
#define LTECAT15EU_URC_NETWORK_REGISTERED             "+CEREG: 2,1"
#define LTECAT15EU_URC_SMS_FORMAT_PDU                 "+CMGF: 0"
#define LTECAT15EU_URC_SMS_FORMAT_TXT                 "+CMGF: 1"

/**
 * @brief LTE Cat.1 5 EU driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTECAT15EU_TX_DRV_BUFFER_SIZE                 256
#define LTECAT15EU_RX_DRV_BUFFER_SIZE                 256

/*! @} */ // ltecat15eu_cmd

/**
 * @defgroup ltecat15eu_map LTE Cat.1 5 EU MikroBUS Map
 * @brief MikroBUS pin mapping of LTE Cat.1 5 EU Click driver.
 */

/**
 * @addtogroup ltecat15eu_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE Cat.1 5 EU Click to the selected MikroBUS.
 */
#define LTECAT15EU_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.wkp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ltecat15eu_map
/*! @} */ // ltecat15eu

/**
 * @brief LTE Cat.1 5 EU Click context object.
 * @details Context object definition of LTE Cat.1 5 EU Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wkp;              /**< Wake-up pin. */
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t rts;              /**< UART ready to send pin. */

    // Input pins
    digital_in_t ring;              /**< Ring indicator pin. */
    digital_in_t cts;               /**< UART clear to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LTECAT15EU_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LTECAT15EU_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LTECAT15EU_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} ltecat15eu_t;

/**
 * @brief LTE Cat.1 5 EU Click configuration object.
 * @details Configuration object definition of LTE Cat.1 5 EU Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t wkp;                 /**< Wake-up pin. */
    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t rts;                 /**< UART ready to send pin. */
    pin_name_t ring;                /**< Ring indicator pin. */
    pin_name_t cts;                 /**< UART clear to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} ltecat15eu_cfg_t;

/**
 * @brief LTE Cat.1 5 EU Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTECAT15EU_OK = 0,
    LTECAT15EU_ERROR = -1,
    LTECAT15EU_ERROR_TIMEOUT = -2,
    LTECAT15EU_ERROR_CMD = -3

} ltecat15eu_return_value_t;

/*!
 * @addtogroup ltecat15eu LTE Cat.1 5 EU Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 5 EU Click driver.
 * @{
 */

/**
 * @brief LTE Cat.1 5 EU configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ltecat15eu_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ltecat15eu_cfg_setup ( ltecat15eu_cfg_t *cfg );

/**
 * @brief LTE Cat.1 5 EU initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ltecat15eu_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat15eu_init ( ltecat15eu_t *ctx, ltecat15eu_cfg_t *cfg );

/**
 * @brief LTE Cat.1 5 EU data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat15eu_generic_write ( ltecat15eu_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE Cat.1 5 EU data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat15eu_generic_read ( ltecat15eu_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE Cat.1 5 EU set WKP pin function.
 * @details This function sets the WAKE0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat15eu_set_wkp_pin ( ltecat15eu_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 5 EU set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat15eu_set_rst_pin ( ltecat15eu_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 5 EU set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat15eu_set_rts_pin ( ltecat15eu_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 5 EU get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat15eu_get_ring_pin ( ltecat15eu_t *ctx );

/**
 * @brief LTE Cat.1 5 EU get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat15eu_get_cts_pin ( ltecat15eu_t *ctx );

/**
 * @brief LTE Cat.1 5 EU reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ltecat15eu_reset_device ( ltecat15eu_t *ctx );

/**
 * @brief LTE Cat.1 5 EU cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ltecat15eu_cmd_run ( ltecat15eu_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 5 EU cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void ltecat15eu_cmd_set ( ltecat15eu_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LTE Cat.1 5 EU cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ltecat15eu_cmd_get ( ltecat15eu_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 5 EU cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ltecat15eu_cmd_help ( ltecat15eu_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 5 EU set sim card APN function.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void ltecat15eu_set_sim_apn ( ltecat15eu_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE Cat.1 5 EU send SMS in text mode function.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void ltecat15eu_send_sms_text ( ltecat15eu_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE Cat.1 5 EU send SMS in PDU mode function.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #ltecat15eu_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat15eu_send_sms_pdu ( ltecat15eu_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // LTECAT15EU_H

/*! @} */ // ltecat15eu

// ------------------------------------------------------------------------ END
