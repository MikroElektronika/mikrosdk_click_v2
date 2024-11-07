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
 * @file ltecat16.h
 * @brief This file contains API for LTE Cat.1 6 Click Driver.
 */

#ifndef LTECAT16_H
#define LTECAT16_H

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
 * @addtogroup ltecat16 LTE Cat.1 6 Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 6 Click driver.
 * @{
 */

/**
 * @defgroup ltecat16_cmd LTE Cat.1 6 Device Settings
 * @brief Settings for registers of LTE Cat.1 6 Click driver.
 */

/**
 * @addtogroup ltecat16_cmd
 * @{
 */

/**
 * @brief LTE Cat.1 6 control commands.
 * @details Specified setting for control commands of LTE Cat.1 6 Click driver.
 */
#define LTECAT16_CMD_AT                             "AT"
#define LTECAT16_CMD_GET_MODEL_ID                   "AT+CGMM"
#define LTECAT16_CMD_GET_SW_VERSION                 "AT+CGMR"
#define LTECAT16_CMD_GET_SERIAL_NUM                 "AT+CGSN"
#define LTECAT16_CMD_FACTORY_RESET                  "AT&F"
#define LTECAT16_CMD_SET_PHONE_FUNCTIONALITY        "AT+CFUN"
#define LTECAT16_CMD_NETWORK_REGISTRATION           "AT+CREG"
#define LTECAT16_CMD_SIGNAL_QUALITY_REPORT          "AT+CSQ"
#define LTECAT16_CMD_OPERATOR_SELECTION             "AT+COPS"
#define LTECAT16_CMD_SEND_SMS                       "AT+CMGS"
#define LTECAT16_CMD_SELECT_SMS_FORMAT              "AT+CMGF"
#define LTECAT16_CMD_DEFINE_PDP_CONTEXT             "AT+CGDCONT"
#define LTECAT16_CMD_ACTIVATE_PDP_CONTEXT           "AT+CGACT"
#define LTECAT16_CMD_SHOW_PDP_ADDRESS               "AT+CGPADDR"
#define LTECAT16_CMD_START_TCPIP_SERVICE            "AT+NETOPEN"
#define LTECAT16_CMD_OPEN_TCP_UDP_CONNECTION        "AT+CIPOPEN"
#define LTECAT16_CMD_SEND_DATA_VIA_CONNECTION       "AT+CIPSEND"
#define LTECAT16_CMD_RECEIVE_DATA_VIA_CONNECTION    "AT+CIPRXGET"
#define LTECAT16_CMD_CLOSE_TCP_UDP_CONNECTION       "AT+CIPCLOSE"

/**
 * @brief LTE Cat.1 6 device response for AT commands.
 * @details Device response after commands.
 */
#define LTECAT16_RSP_OK                             "OK"
#define LTECAT16_RSP_ERROR                          "ERROR"

/**
 * @brief LTE Cat.1 6 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define LTECAT16_URC_RECEIVED_DATA                  "+CIPRXGET:"

/**
 * @brief LTE Cat.1 6 power state settings.
 * @details Specified power state settings of LTE Cat.1 6 Click driver.
 */
#define LTECAT16_POWER_STATE_OFF                    0
#define LTECAT16_POWER_STATE_ON                     1

/**
 * @brief LTE Cat.1 6 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTECAT16_TX_DRV_BUFFER_SIZE                 256
#define LTECAT16_RX_DRV_BUFFER_SIZE                 256

/*! @} */ // ltecat16_cmd

/**
 * @defgroup ltecat16_map LTE Cat.1 6 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE Cat.1 6 Click driver.
 */

/**
 * @addtogroup ltecat16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE Cat.1 6 Click to the selected MikroBUS.
 */
#define LTECAT16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ltecat16_map
/*! @} */ // ltecat16

/**
 * @brief LTE Cat.1 6 Click context object.
 * @details Context object definition of LTE Cat.1 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;      /**< PWRKEY pin (active low). */
    digital_out_t rts;      /**< UART Request to send pin. */

    // Input pins
    digital_in_t ring;      /**< Ring indicator pin. */
    digital_in_t cts;       /**< UART Clear to send pin. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LTECAT16_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LTECAT16_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LTECAT16_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} ltecat16_t;

/**
 * @brief LTE Cat.1 6 Click configuration object.
 * @details Configuration object definition of LTE Cat.1 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t pwr;         /**< PWRKEY pin (active low). */
    pin_name_t rts;         /**< UART Request to send pin. */
    pin_name_t ring;        /**< Ring indicator pin. */
    pin_name_t cts;         /**< UART Clear to send pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} ltecat16_cfg_t;

/**
 * @brief LTE Cat.1 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTECAT16_OK = 0,
    LTECAT16_ERROR = -1,
    LTECAT16_ERROR_TIMEOUT = -2,
    LTECAT16_ERROR_CMD = -3,
    LTECAT16_ERROR_UNKNOWN = -4

} ltecat16_return_value_t;

/*!
 * @addtogroup ltecat16 LTE Cat.1 6 Click Driver
 * @brief API for configuring and manipulating LTE Cat.1 6 Click driver.
 * @{
 */

/**
 * @brief LTE Cat.1 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ltecat16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ltecat16_cfg_setup ( ltecat16_cfg_t *cfg );

/**
 * @brief LTE Cat.1 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ltecat16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat16_init ( ltecat16_t *ctx, ltecat16_cfg_t *cfg );

/**
 * @brief LTE Cat.1 6 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat16_generic_write ( ltecat16_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE Cat.1 6 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat16_generic_read ( ltecat16_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE Cat.1 6 set PWR pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat16_set_pwr_pin ( ltecat16_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 6 set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ltecat16_set_rts_pin ( ltecat16_t *ctx, uint8_t state );

/**
 * @brief LTE Cat.1 6 get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat16_get_ring_pin ( ltecat16_t *ctx );

/**
 * @brief LTE Cat.1 6 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ltecat16_get_cts_pin ( ltecat16_t *ctx );

/**
 * @brief LTE Cat.1 6 set power state function.
 * @details This function sets a desired power state by toggling PWR pin with a specific time for high state.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON.
 * @return None.
 * @note None.
 */
void ltecat16_set_power_state ( ltecat16_t *ctx, uint8_t state );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void ltecat16_send_cmd ( ltecat16_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat16_send_cmd_par ( ltecat16_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void ltecat16_send_cmd_check ( ltecat16_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void ltecat16_set_sim_apn ( ltecat16_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE Cat.1 6 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void ltecat16_send_sms_text ( ltecat16_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE Cat.1 6 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #ltecat16_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat16_send_sms_pdu ( ltecat16_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // LTECAT16_H

/*! @} */ // ltecat16

// ------------------------------------------------------------------------ END
