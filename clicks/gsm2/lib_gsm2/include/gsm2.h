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
 * @file gsm2.h
 * @brief This file contains API for GSM 2 Click Driver.
 */

#ifndef GSM2_H
#define GSM2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup gsm2 GSM 2 Click Driver
 * @brief API for configuring and manipulating GSM 2 Click driver.
 * @{
 */

/**
 * @defgroup gsm2_set GSM 2 Device Settings
 * @brief Settings for registers of GSM 2 Click driver.
 */

/**
 * @addtogroup gsm2_set
 * @{
 */

/**
 * @brief GSM 2 control commands.
 * @details Specified setting for control commands of GSM 2 Click driver.
 */
#define GSM2_CMD_AT                             "AT"
#define GSM2_CMD_ATI                            "ATI"
#define GSM2_CMD_CFUN                           "AT+CFUN"
#define GSM2_CMD_CREG                           "AT+CREG"
#define GSM2_CMD_CGDCONT                        "AT+CGDCONT"
#define GSM2_CMD_CSQ                            "AT+CSQ"
#define GSM2_CMD_COPS                           "AT+COPS"
#define GSM2_CMD_CMGS                           "AT+CMGS"
#define GSM2_CMD_CMGF                           "AT+CMGF"
#define GSM2_CMD_CGACT                          "AT+CGACT"
#define GSM2_CMD_QIMUX                          "AT+QIMUX"
#define GSM2_CMD_QIOPEN                         "AT+QIOPEN"
#define GSM2_CMD_QICLOSE                        "AT+QICLOSE"
#define GSM2_CMD_QISEND                         "AT+QISEND"
#define GSM2_CMD_QIRD                           "AT+QIRD"

/**
 * @brief GSM 2 device response for AT commands.
 * @details Device response after commands.
 */
#define GSM2_RSP_OK                             "OK"
#define GSM2_RSP_ERROR                          "ERROR"

/**
 * @brief GSM 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GSM2_RX_DRV_BUFFER_SIZE                 256
#define GSM2_TX_DRV_BUFFER_SIZE                 256

/*! @} */ // gsm2_set

/**
 * @defgroup gsm2_map GSM 2 MikroBUS Map
 * @brief MikroBUS pin mapping of GSM 2 Click driver.
 */

/**
 * @addtogroup gsm2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GSM 2 Click to the selected MikroBUS.
 */
#define GSM2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sta = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gsm2_map
/*! @} */ // gsm2

/**
 * @brief GSM 2 Click context object.
 * @details Context object definition of GSM 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwk;      /**< Power-up module. */
    digital_out_t rts;      /**< UART Request to Send. */

    // Input pins
    digital_in_t sta;       /**< Module status. */
    digital_in_t ring;      /**< Ring indicator. */
    digital_in_t cts;       /**< UART Clear to Send. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GSM2_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ GSM2_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} gsm2_t;

/**
 * @brief GSM 2 Click configuration object.
 * @details Configuration object definition of GSM 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t sta;         /**< Module status. */
    pin_name_t pwk;         /**< Power-up module. */ 
    pin_name_t rts;         /**< UART Request to Send. */
    pin_name_t ring;        /**< Ring indicator. */
    pin_name_t cts;         /**< UART Clear to Send. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} gsm2_cfg_t;

/**
 * @brief GSM 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GSM2_OK = 0,
    GSM2_ERROR = -1,
    GSM2_ERROR_TIMEOUT = -2,
    GSM2_ERROR_CMD = -3,
    GSM2_ERROR_UNKNOWN = -4

} gsm2_return_value_t;

/*!
 * @addtogroup gsm2 GSM 2 Click Driver
 * @brief API for configuring and manipulating GSM 2 Click driver.
 * @{
 */

/**
 * @brief GSM 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gsm2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gsm2_cfg_setup ( gsm2_cfg_t *cfg );

/**
 * @brief GSM 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gsm2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm2_init ( gsm2_t *ctx, gsm2_cfg_t *cfg );

/**
 * @brief GSM 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm2_generic_write ( gsm2_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GSM 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm2_generic_read ( gsm2_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GSM 2 set rts pin function.
 * @details This function sets the Request to Send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gsm2_set_rts_pin ( gsm2_t *ctx, uint8_t state );

/**
 * @brief GSM 2 set pwk pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gsm2_set_pwk_pin ( gsm2_t *ctx, uint8_t state );

/**
 * @brief GSM 2 get cts pin function.
 * @details This function returns the Clear to Send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gsm2_get_cts_pin ( gsm2_t *ctx );

/**
 * @brief GSM 2 get sta pin function.
 * @details This function returns the status (STA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gsm2_get_sta_pin ( gsm2_t *ctx );

/**
 * @brief GSM 2 get ring pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gsm2_get_ring_pin ( gsm2_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void gsm2_send_cmd ( gsm2_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void gsm2_send_cmd_with_par ( gsm2_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void gsm2_send_cmd_check ( gsm2_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void gsm2_send_cmd_par_check ( gsm2_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void gsm2_set_sim_apn ( gsm2_t *ctx, uint8_t *sim_apn );

/**
 * @brief GSM 2 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void gsm2_send_sms_text ( gsm2_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief GSM 2 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #gsm2_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm2_send_sms_pdu ( gsm2_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // GSM2_H

/*! @} */ // gsm2

// ------------------------------------------------------------------------ END
