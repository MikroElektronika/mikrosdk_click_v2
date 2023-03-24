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
 * @file lteiot8.h
 * @brief This file contains API for LTE IoT 8 Click Driver.
 */

#ifndef LTEIOT8_H
#define LTEIOT8_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup lteiot8 LTE IoT 8 Click Driver
 * @brief API for configuring and manipulating LTE IoT 8 Click driver.
 * @{
 */

/**
 * @defgroup lteiot8_reg LTE IoT 8 Commands List
 * @brief List of commands of LTE IoT 8 Click driver.
 */

/**
 * @addtogroup lteiot8_cmd
 * @{
 */

/**
 * @brief LTE IoT 9 description commands.
 * @details Specified AT commands for communication with LTE IoT 9 Click driver.
 */
#define LTEIOT8_CMD_AT          "AT"
#define LTEIOT8_CMD_ATI         "ATI"
#define LTEIOT8_CMD_CGMR        "AT+CGMR"
#define LTEIOT8_CMD_CFUN        "AT+CFUN"
#define LTEIOT8_CMD_CREG        "AT+CREG"
#define LTEIOT8_CMD_CEREG       "AT+CEREG"
#define LTEIOT8_CMD_CGDCONT     "AT+CGDCONT"
#define LTEIOT8_CMD_CIMI        "AT+CIMI"
#define LTEIOT8_CMD_CGATT       "AT+CGATT"
#define LTEIOT8_CMD_CSQ         "AT+CSQ"
#define LTEIOT8_CMD_CESQ        "AT+CESQ"
#define LTEIOT8_CMD_COPS        "AT+COPS"
#define LTEIOT8_CMD_CMGF        "AT+CMGF"
#define LTEIOT8_CMD_CMGS        "AT+CMGS"
#define LTEIOT8_CMD_CSCA        "AT+CSCA"
#define LTEIOT8_CMD_SQNLED      "AT+SQNLED"

/*! @} */ // lteiot8_cmd

/**
 * @defgroup lteiot8_set LTE IoT 8 Device Settings
 * @brief Settings for registers of LTE IoT 8 Click driver.
 */

/**
 * @addtogroup lteiot8_set
 * @{
 */

/**
 * @brief LTE IoT 8 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT8_RSP_OK          "OK"
#define LTEIOT8_RSP_ERROR       "ERROR"
#define LTEIOT8_RSP_SYSTART     "+SYSSTART"

/**
 * @brief LTE IoT 8 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_TX_BUFFER_SIZE      200
#define DRV_RX_BUFFER_SIZE      500

/*! @} */ // lteiot8_set

/**
 * @defgroup lteiot8_map LTE IoT 8 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 8 Click driver.
 */

/**
 * @addtogroup lteiot8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 8 Click to the selected MikroBUS.
 */
#define LTEIOT8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rng = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pst = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot8_map
/*! @} */ // lteiot8

/**
 * @brief LTE IoT 8 Click context object.
 * @details Context object definition of LTE IoT 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;     /**< Description. */
    digital_out_t cts;       /**< Description. */

    // Input pins
    digital_in_t rng;         /**< Description. */
    digital_in_t pst;       /**< Description. */
    digital_in_t rts;       /**< Description. */

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];         /**< Buffer size. */

} lteiot8_t;

/**
 * @brief LTE IoT 8 Click configuration object.
 * @details Configuration object definition of LTE IoT 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rng;          /**< Description. */
    pin_name_t rst;        /**< Description. */
    pin_name_t cts;          /**< Description. */
    pin_name_t pst;        /**< Description. */
    pin_name_t rts;        /**< Description. */

    // Static variable

    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} lteiot8_cfg_t;

/**
 * @brief LTE IoT 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LTEIOT8_OK = 0,
   LTEIOT8_ERROR = -1,
   LTEIOT8_ERROR_TIMEOUT = -2,
   LTEIOT8_ERROR_CMD = -3,
   LTEIOT8_ERROR_UNKNOWN = -4

} lteiot8_return_value_t;

/*!
 * @addtogroup lteiot8 LTE IoT 8 Click Driver
 * @brief API for configuring and manipulating LTE IoT 8 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot8_cfg_setup ( lteiot8_cfg_t *cfg );

/**
 * @brief LTE IoT 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot8_init ( lteiot8_t *ctx, lteiot8_cfg_t *cfg );

/**
 * @brief LTE IoT 8 default configuration function.
 * @details This function executes a default configuration of LTE IoT 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lteiot8_default_cfg ( lteiot8_t *ctx );

/**
 * @brief LTE IoT 8 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot8_generic_write ( lteiot8_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LTE IoT 8 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot8_generic_read ( lteiot8_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command function.
 * @details Send string byte by byte and additionaly send CR flag.
 * @param[in] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 *
 * @return Nothing.
 */
void lteiot8_send_cmd ( lteiot8_t *ctx, char *cmd );

/**
 * @brief Send command with parameters.
 * @details Send AT command (@b at_cmd_buf) with '=' and 
 * parameter(@b param_buf) to set commands value.
 * @param[in] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : AT command.
 * @param[in] param_buf : Parameter for AT command.
 *
 * @return Nothing.
 */
void lteiot8_send_cmd_with_parameter ( lteiot8_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Send command to check commands current value.
 * @details Send AT command (@b at_cmd_buf) and appends '?' to check commands value.
 * @param[in] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : AT command.
 *
 * @return Nothing.
 */
void lteiot8_send_cmd_check ( lteiot8_t *ctx, char *at_cmd_buf );

/**
 * @brief Send command to check commands available parameters.
 * @details Send AT command (@b at_cmd_buf) and appends '?' to check commands value.
 * @param[in] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : AT command.
 *
 * @return Nothing.
 */
void lteiot8_send_cmd_syntax_check ( lteiot8_t *ctx, char *at_cmd_buf );

/**
 * @brief Set SIM APN.
 * @details Send command to select SIM APN.
 * @param[in] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM APN.
 *
 * @return Nothing.
 */
void lteiot8_set_sim_apn ( lteiot8_t *ctx, char *sim_apn );

/**
 * @brief Send SMS message to number in text mode.
 * @details Send command for SIM message with function 
 * parameters for device to send SMS message.
 * @param[in] ctx : Click context object.
 * See #lteiot8_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to send message to.
 * @param[in] message_context : Content of the message.
 *
 * @return Nothing.
 * @note Device should be configured for .
 */
void lteiot8_send_text_message ( lteiot8_t *ctx, char *phone_number, char *message_content );

/**
 * @brief Send SMS message to number in pdu mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lteiot8_send_sms_pdu ( lteiot8_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT8_H

/*! @} */ // lteiot8

// ------------------------------------------------------------------------ END
