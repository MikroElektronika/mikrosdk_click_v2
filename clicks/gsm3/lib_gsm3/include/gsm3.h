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
 * @file gsm3.h
 * @brief This file contains API for GSM 3 Click Driver.
 */

#ifndef GSM3_H
#define GSM3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup gsm3 GSM 3 Click Driver
 * @brief API for configuring and manipulating GSM 3 Click driver.
 * @{
 */

/**
 * @defgroup gsm3_set GSM 3 Device Settings
 * @brief Settings for registers of GSM 3 Click driver.
 */

/**
 * @addtogroup gsm3_set
 * @{
 */

/**
 * @brief GSM 3 control commands.
 * @details Specified setting for control commands of GSM 3 Click driver.
 */
#define GSM3_CMD_AT                             "AT"
#define GSM3_CMD_CFUN                           "AT+CFUN"
#define GSM3_CMD_CREG                           "AT+CREG"
#define GSM3_CMD_CGDCONT                        "AT+CGDCONT"
#define GSM3_CMD_CSQ                            "AT+CSQ"
#define GSM3_CMD_COPS                           "AT+COPS"
#define GSM3_CMD_CMGS                           "AT+CMGS"
#define GSM3_CMD_CMGF                           "AT+CMGF"
#define GSM3_CMD_CIPMUX                         "AT+CIPMUX"
#define GSM3_CMD_CIPSTART                       "AT+CIPSTART"
#define GSM3_CMD_CIPCLOSE                       "AT+CIPCLOSE"
#define GSM3_CMD_CIPSEND                        "AT+CIPSEND"
#define GSM3_CMD_CIPHEAD                        "AT+CIPHEAD"

/**
 * @brief GSM 3 device response for AT commands.
 * @details Device response after commands.
 */
#define GSM3_RSP_OK                             "OK"
#define GSM3_RSP_ERROR                          "ERROR"

/**
 * @brief GSM 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GSM3_RX_DRV_BUFFER_SIZE                 256
#define GSM3_TX_DRV_BUFFER_SIZE                 256

/*! @} */ // gsm3_set

/**
 * @defgroup gsm3_map GSM 3 MikroBUS Map
 * @brief MikroBUS pin mapping of GSM 3 Click driver.
 */

/**
 * @addtogroup gsm3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GSM 3 Click to the selected MikroBUS.
 */
#define GSM3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sta = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gsm3_map
/*! @} */ // gsm3

/**
 * @brief GSM 3 Click context object.
 * @details Context object definition of GSM 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset pin (Active high). */
    digital_out_t pwk;      /**< PWRKEY pin. */
    digital_out_t rts;      /**< UART Request to Send. */

    // Input pins
    digital_in_t sta;       /**< Power on status. */
    digital_in_t cts;       /**< UART Clear to Send. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GSM3_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ GSM3_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} gsm3_t;

/**
 * @brief GSM 3 Click configuration object.
 * @details Configuration object definition of GSM 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;         /**< Reset pin (Active low). */
    pin_name_t pwk;         /**< PWRKEY pin. */
    pin_name_t rts;         /**< UART Request to Send. */
    pin_name_t sta;         /**< Power on status. */
    pin_name_t cts;         /**< UART Clear to Send. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} gsm3_cfg_t;

/**
 * @brief GSM 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GSM3_OK = 0,
    GSM3_ERROR = -1,
    GSM3_ERROR_TIMEOUT = -2,
    GSM3_ERROR_CMD = -3,
    GSM3_ERROR_UNKNOWN = -4

} gsm3_return_value_t;

/*!
 * @addtogroup gsm3 GSM 3 Click Driver
 * @brief API for configuring and manipulating GSM 3 Click driver.
 * @{
 */

/**
 * @brief GSM 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gsm3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gsm3_cfg_setup ( gsm3_cfg_t *cfg );

/**
 * @brief GSM 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gsm3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm3_init ( gsm3_t *ctx, gsm3_cfg_t *cfg );

/**
 * @brief GSM 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm3_generic_write ( gsm3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GSM 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm3_generic_read ( gsm3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GSM 3 set rst pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gsm3_set_rst_pin ( gsm3_t *ctx, uint8_t state );

/**
 * @brief GSM 3 set rts pin function.
 * @details This function sets the Request to Send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gsm3_set_rts_pin ( gsm3_t *ctx, uint8_t state );

/**
 * @brief GSM 3 set pwk pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gsm3_set_pwk_pin ( gsm3_t *ctx, uint8_t state );

/**
 * @brief GSM 3 get cts pin function.
 * @details This function returns the Clear to Send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gsm3_get_cts_pin ( gsm3_t *ctx );

/**
 * @brief GSM 3 get sta pin function.
 * @details This function returns the status (STA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gsm3_get_sta_pin ( gsm3_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void gsm3_send_cmd ( gsm3_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void gsm3_send_cmd_with_par ( gsm3_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void gsm3_send_cmd_check ( gsm3_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void gsm3_send_cmd_par_check ( gsm3_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void gsm3_set_sim_apn ( gsm3_t *ctx, uint8_t *sim_apn );

/**
 * @brief GSM 3 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void gsm3_send_sms_text ( gsm3_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief GSM 3 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #gsm3_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm3_send_sms_pdu ( gsm3_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // GSM3_H

/*! @} */ // gsm3

// ------------------------------------------------------------------------ END
