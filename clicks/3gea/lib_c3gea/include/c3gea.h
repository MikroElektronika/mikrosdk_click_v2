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
 * @file c3gea.h
 * @brief This file contains API for 3G-EA Click Driver.
 */

#ifndef C3GEA_H
#define C3GEA_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup c3gea 3G-EA Click Driver
 * @brief API for configuring and manipulating 3G-EA Click driver.
 * @{
 */

/**
 * @defgroup c3gea_set 3G-EA Device Settings
 * @brief Settings for registers of 3G-EA Click driver.
 */

/**
 * @addtogroup c3gea_set
 * @{
 */

/**
 * @brief 3G-EA control commands.
 * @details Specified setting for control commands of 3G-EA Click driver.
 */
#define C3GEA_CMD_AT                            "AT"
#define C3GEA_CMD_ATI                           "ATI"
#define C3GEA_CMD_CFUN                          "AT+CFUN"
#define C3GEA_CMD_CREG                          "AT+CREG"
#define C3GEA_CMD_CGDCONT                       "AT+CGDCONT"
#define C3GEA_CMD_CSQ                           "AT+CSQ"
#define C3GEA_CMD_COPS                          "AT+COPS"
#define C3GEA_CMD_CMGS                          "AT+CMGS"
#define C3GEA_CMD_CMGF                          "AT+CMGF"
#define C3GEA_CMD_QIACT                         "AT+QIACT"
#define C3GEA_CMD_QIOPEN                        "AT+QIOPEN"
#define C3GEA_CMD_QICLOSE                       "AT+QICLOSE"
#define C3GEA_CMD_QISEND                        "AT+QISEND"
#define C3GEA_CMD_QIRD                          "AT+QIRD"

/**
 * @brief 3G-EA device response for AT commands.
 * @details Device response after commands.
 */
#define C3GEA_RSP_OK                            "OK"
#define C3GEA_RSP_ERROR                         "ERROR"

/**
 * @brief 3G-EA driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define C3GEA_RX_DRV_BUFFER_SIZE                256
#define C3GEA_TX_DRV_BUFFER_SIZE                256

/*! @} */ // c3gea_set

/**
 * @defgroup c3gea_map 3G-EA MikroBUS Map
 * @brief MikroBUS pin mapping of 3G-EA Click driver.
 */

/**
 * @addtogroup c3gea_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3G-EA Click to the selected MikroBUS.
 */
#define C3GEA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sta = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3gea_map
/*! @} */ // c3gea

/**
 * @brief 3G-EA Click context object.
 * @details Context object definition of 3G-EA Click driver.
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
    char uart_rx_buffer[ C3GEA_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    char uart_tx_buffer[ C3GEA_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} c3gea_t;

/**
 * @brief 3G-EA Click configuration object.
 * @details Configuration object definition of 3G-EA Click driver.
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

} c3gea_cfg_t;

/**
 * @brief 3G-EA Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3GEA_OK = 0,
    C3GEA_ERROR = -1,
    C3GEA_ERROR_TIMEOUT = -2,
    C3GEA_ERROR_CMD = -3,
    C3GEA_ERROR_UNKNOWN = -4

} c3gea_return_value_t;

/*!
 * @addtogroup c3gea 3G-EA Click Driver
 * @brief API for configuring and manipulating 3G-EA Click driver.
 * @{
 */

/**
 * @brief 3G-EA configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3gea_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3gea_cfg_setup ( c3gea_cfg_t *cfg );

/**
 * @brief 3G-EA initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3gea_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3gea_init ( c3gea_t *ctx, c3gea_cfg_t *cfg );

/**
 * @brief 3G-EA data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3gea_generic_write ( c3gea_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief 3G-EA data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3gea_generic_read ( c3gea_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief 3G-EA set rts pin function.
 * @details This function sets the Request to Send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c3gea_set_rts_pin ( c3gea_t *ctx, uint8_t state );

/**
 * @brief 3G-EA set pwk pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c3gea_set_pwk_pin ( c3gea_t *ctx, uint8_t state );

/**
 * @brief 3G-EA get cts pin function.
 * @details This function returns the Clear to Send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3gea_get_cts_pin ( c3gea_t *ctx );

/**
 * @brief 3G-EA get sta pin function.
 * @details This function returns the status (STA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3gea_get_sta_pin ( c3gea_t *ctx );

/**
 * @brief 3G-EA get ring pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3gea_get_ring_pin ( c3gea_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void c3gea_send_cmd ( c3gea_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void c3gea_send_cmd_with_par ( c3gea_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void c3gea_send_cmd_check ( c3gea_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void c3gea_send_cmd_par_check ( c3gea_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void c3gea_set_sim_apn ( c3gea_t *ctx, uint8_t *sim_apn );

/**
 * @brief 3G-EA send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void c3gea_send_sms_text ( c3gea_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief 3G-EA send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #c3gea_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3gea_send_sms_pdu ( c3gea_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // C3GEA_H

/*! @} */ // c3gea

// ------------------------------------------------------------------------ END
