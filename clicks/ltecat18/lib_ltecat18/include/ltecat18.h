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
 * @file ltecat18.h
 * @brief This file contains API for LTE Cat.1 8 Click Driver.
 */

#ifndef LTECAT18_H
#define LTECAT18_H

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
 * @addtogroup ltecat18 LTE Cat.1 8 Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 8 Click driver.
 * @{
 */

/**
 * @defgroup ltecat18_cmd LTE Cat.1 8 Device Settings
 * @brief Settings for registers of LTE Cat.1 8 Click driver.
 */

/**
 * @addtogroup ltecat18_cmd
 * @{
 */

/**
 * @brief LTE Cat.1 8 control commands.
 * @details Specified setting for control commands of LTE Cat.1 8 Click driver.
 */
#define LTECAT18_CMD_AT                             "AT"
#define LTECAT18_CMD_GET_MODEL_ID                   "AT+CGMM"
#define LTECAT18_CMD_GET_SW_VERSION                 "AT+CGMR"
#define LTECAT18_CMD_GET_SERIAL_NUM                 "AT+CGSN"
#define LTECAT18_CMD_FACTORY_RESET                  "AT&F"
#define LTECAT18_CMD_SET_PHONE_FUNCTIONALITY        "AT+CFUN"
#define LTECAT18_CMD_NETWORK_REGISTRATION           "AT+CREG"
#define LTECAT18_CMD_SIGNAL_QUALITY_REPORT          "AT+CSQ"
#define LTECAT18_CMD_OPERATOR_SELECTION             "AT+COPS"
#define LTECAT18_CMD_SEND_SMS                       "AT+CMGS"
#define LTECAT18_CMD_SELECT_SMS_FORMAT              "AT+CMGF"
#define LTECAT18_CMD_DEFINE_PDP_CONTEXT             "AT+CGDCONT"
#define LTECAT18_CMD_ACTIVATE_PDP_CONTEXT           "AT+CGACT"
#define LTECAT18_CMD_SHOW_PDP_ADDRESS               "AT+CGPADDR"
#define LTECAT18_CMD_START_TCPIP_SERVICE            "AT+NETOPEN"
#define LTECAT18_CMD_OPEN_TCP_UDP_CONNECTION        "AT+CIPOPEN"
#define LTECAT18_CMD_SEND_DATA_VIA_CONNECTION       "AT+CIPSEND"
#define LTECAT18_CMD_RECEIVE_DATA_VIA_CONNECTION    "AT+CIPRXGET"
#define LTECAT18_CMD_CLOSE_TCP_UDP_CONNECTION       "AT+CIPCLOSE"

/**
 * @brief LTE Cat.1 8 device response for AT commands.
 * @details Device response after commands.
 */
#define LTECAT18_RSP_OK                             "OK"
#define LTECAT18_RSP_ERROR                          "ERROR"

/**
 * @brief LTE Cat.1 8 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define LTECAT18_URC_RECEIVED_DATA                  "+CIPRXGET:"
#define LTECAT18_URC_CONNECTION_OPEN                "+CIPOPEN:"
#define LTECAT18_URC_CONNECTION_CLOSED              "+CIPCLOSE:"

/**
 * @brief LTE Cat.1 8 power state settings.
 * @details Specified power state settings of LTE Cat.1 8 Click driver.
 */
#define LTECAT18_POWER_STATE_OFF                    0
#define LTECAT18_POWER_STATE_ON                     1
#define LTECAT18_POWER_STATE_RESET                  2

/**
 * @brief LTE Cat.1 8 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTECAT18_TX_DRV_BUFFER_SIZE                 256
#define LTECAT18_RX_DRV_BUFFER_SIZE                 256

/*! @} */ // ltecat18_cmd

/**
 * @defgroup ltecat18_map LTE Cat.1 8 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE Cat.1 8 Click driver.
 */

/**
 * @addtogroup ltecat18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE Cat.1 8 Click to the selected MikroBUS.
 */
#define LTECAT18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ltecat18_map
/*! @} */ // ltecat18

/**
 * @brief LTE Cat.1 8 Click context object.
 * @details Context object definition of LTE Cat.1 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;              /**< Power pin. */
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t rts;              /**< UART ready to send pin. */

    // Input pins
    digital_in_t ring;              /**< Ring indicator pin. */
    digital_in_t cts;               /**< UART clear to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LTECAT18_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LTECAT18_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LTECAT18_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} ltecat18_t;

/**
 * @brief LTE Cat.1 8 Click configuration object.
 * @details Configuration object definition of LTE Cat.1 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t pwr;                 /**< Power pin. */
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

} ltecat18_cfg_t;

/**
 * @brief LTE Cat.1 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTECAT18_OK = 0,
    LTECAT18_ERROR = -1,
    LTECAT18_ERROR_TIMEOUT = -2,
    LTECAT18_ERROR_CMD = -3

} ltecat18_return_value_t;

/*!
 * @addtogroup ltecat18 LTE Cat.1 8 Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 8 Click driver.
 * @{
 */

/**
 * @brief LTE Cat.1 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ltecat18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ltecat18_cfg_setup ( ltecat18_cfg_t *cfg );

/**
 * @brief LTE Cat.1 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ltecat18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat18_init ( ltecat18_t *ctx, ltecat18_cfg_t *cfg );

/**
 * @brief LTE Cat.1 8 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat18_generic_write ( ltecat18_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE Cat.1 8 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat18_generic_read ( ltecat18_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE Cat.1 8 set PWR pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat18_set_pwr_pin ( ltecat18_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 8 set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat18_set_rst_pin ( ltecat18_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 8 set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat18_set_rts_pin ( ltecat18_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 8 get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat18_get_ring_pin ( ltecat18_t *ctx );

/**
 * @brief LTE Cat.1 8 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat18_get_cts_pin ( ltecat18_t *ctx );

/**
 * @brief LTE Cat.1 8 set power state function.
 * @details This function sets a desired power state by toggling PWR and RST pins with a specific timing.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON,
 *                    @li @c 2 - Reset.
 * @return None.
 * @note None.
 */
void ltecat18_set_power_state ( ltecat18_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 8 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ltecat18_cmd_run ( ltecat18_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 8 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void ltecat18_cmd_set ( ltecat18_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LTE Cat.1 8 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ltecat18_cmd_get ( ltecat18_t *ctx, uint8_t *cmd );

/**
 * @brief LTE Cat.1 8 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ltecat18_cmd_help ( ltecat18_t *ctx, uint8_t *cmd );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void ltecat18_set_sim_apn ( ltecat18_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE Cat.1 8 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void ltecat18_send_sms_text ( ltecat18_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE Cat.1 8 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #ltecat18_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat18_send_sms_pdu ( ltecat18_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // LTECAT18_H

/*! @} */ // ltecat18

// ------------------------------------------------------------------------ END
