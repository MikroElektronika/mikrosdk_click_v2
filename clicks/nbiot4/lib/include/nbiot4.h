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
 * @file nbiot4.h
 * @brief This file contains API for NB IoT 4 Click Driver.
 */

#ifndef NBIOT4_H
#define NBIOT4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup nbiot4 NB IoT 4 Click Driver
 * @brief API for configuring and manipulating NB IoT 4 Click driver.
 * @{
 */

/**
 * @defgroup nbiot4_reg NB IoT 4 Commands List
 * @brief List of commands of NB IoT 4 Click driver.
 */

/**
 * @addtogroup nbiot4_reg
 * @{
 */

/**
 * @brief NB IoT 4 description register.
 * @details Specified register for description of NB IoT 4 Click driver.
 */
#define NBIOT4_CMD_AT          "AT"
#define NBIOT4_CMD_ATI         "ATI"
#define NBIOT4_CMD_CGMR        "AT+CGMR"
#define NBIOT4_CMD_CFUN        "AT+CFUN"
#define NBIOT4_CMD_CREG        "AT+CREG"
#define NBIOT4_CMD_CEREG       "AT+CEREG"
#define NBIOT4_CMD_CGDCONT     "AT+CGDCONT"
#define NBIOT4_CMD_CIMI        "AT+CIMI"
#define NBIOT4_CMD_CGATT       "AT+CGATT"
#define NBIOT4_CMD_CSQ         "AT+CSQ"
#define NBIOT4_CMD_CESQ        "AT+CESQ"
#define NBIOT4_CMD_COPS        "AT+COPS"
#define NBIOT4_CMD_CMGF        "AT+CMGF"
#define NBIOT4_CMD_CMGS        "AT+CMGS"
#define NBIOT4_CMD_CSCA        "AT+CSCA"
#define NBIOT4_CMD_SQNLED      "AT+SQNLED"
#define NBIOT4_CMD_SIMSWAP     "AT^SIMSWAP"
#define NBIOT4_CMD_RESTART     "AT+TRB"

/*! @} */ // nbiot4_reg

/**
 * @defgroup nbiot4_set NB IoT 4 Device Settings
 * @brief Settings for registers of NB IoT 4 Click driver.
 */

/**
 * @addtogroup nbiot4_set
 * @{
 */

/**
 * @brief LTE IoT 8 device response for AT commands.
 * @details Device response after commands.
 */
#define NBIOT4_RSP_OK           "OK"
#define NBIOT4_RSP_ERROR        "ERROR"
#define NBIOT4_RSP_CMD_NO_RSP   "COMMAND NO RESPONSE!"
#define NBIOT4_RSP_NO_RSP       "NO RESPONSE!"

/**
 * @brief NB IoT 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_TX_BUFFER_SIZE      150
#define DRV_RX_BUFFER_SIZE      600

/*! @} */ // nbiot4_set

/**
 * @defgroup nbiot4_map NB IoT 4 MikroBUS Map
 * @brief MikroBUS pin mapping of NB IoT 4 Click driver.
 */

/**
 * @addtogroup nbiot4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NB IoT 4 Click to the selected MikroBUS.
 */
#define NBIOT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ri = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // nbiot4_map
/*! @} */ // nbiot4

/**
 * @brief NB IoT 4 Click context object.
 * @details Context object definition of NB IoT 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;     /**< Description. */
    digital_out_t cs;       /**< Description. */
    digital_out_t ri;     /**< Description. */

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];         /**< Buffer size. */

} nbiot4_t;

/**
 * @brief NB IoT 4 Click configuration object.
 * @details Configuration object definition of NB IoT 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
   //pin_name_t an;          /**< Description. */
    pin_name_t rst;        /**< Description. */
    pin_name_t cs;          /**< Description. */
    pin_name_t ri;        /**< Description. */

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} nbiot4_cfg_t;

/**
 * @brief NB IoT 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   NBIOT4_OK = 0,
   NBIOT4_ERROR = -1,
   NBIOT4_ERROR_CMD = -2,
   NBIOT4_ERROR_UNKNOWN = -3

} nbiot4_return_value_t;

/*!
 * @addtogroup nbiot4 NB IoT 4 Click Driver
 * @brief API for configuring and manipulating NB IoT 4 Click driver.
 * @{
 */

/**
 * @brief NB IoT 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nbiot4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nbiot4_cfg_setup ( nbiot4_cfg_t *cfg );

/**
 * @brief NB IoT 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nbiot4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot4_init ( nbiot4_t *ctx, nbiot4_cfg_t *cfg );

/**
 * @brief NB IoT 4 default configuration function.
 * @details This function executes a default configuration of NB IoT 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nbiot4_default_cfg ( nbiot4_t *ctx );

/**
 * @brief NB IoT 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot4_generic_write ( nbiot4_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief NB IoT 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot4_generic_read ( nbiot4_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command function.
 * @details Send string byte by byte and additionaly send CR flag.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 *
 * @return Nothing.
 */
void nbiot4_send_cmd ( nbiot4_t *ctx, char *cmd );

/**
 * @brief Send command with parameters.
 * @details Send AT command (@b at_cmd_buf) with '=' and 
 * parameter(@b param_buf) to set commands value.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : AT command.
 * @param[in] param_buf : Parameter for AT command.
 *
 * @return Nothing.
 */
void nbiot4_send_cmd_with_parameter ( nbiot4_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Send command to check commands current value.
 * @details Send AT command (@b at_cmd_buf) and appends '?' to check commands value.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : AT command.
 *
 * @return Nothing.
 */
void nbiot4_send_cmd_check ( nbiot4_t *ctx, char *at_cmd_buf );

/**
 * @brief Send command to check commands available parameters.
 * @details Send AT command (@b at_cmd_buf) and appends '?' to check commands value.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : AT command.
 *
 * @return Nothing.
 */
void nbiot4_send_cmd_syntax_check ( nbiot4_t *ctx, char *at_cmd_buf );

/**
 * @brief Set SIM APN.
 * @details Send command to select SIM APN.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM APN.
 *
 * @return Nothing.
 */
void nbiot4_set_sim_apn ( nbiot4_t *ctx, char *sim_apn );

/**
 * @brief Send SMS message to number in text mode.
 * @details Send command for SIM message with function 
 * parameters for device to send SMS message.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to send message to.
 * @param[in] message_context : Content of the message.
 *
 * @return Nothing.
 * @note Device should be configured for text message before sending text message.
 */
void nbiot4_send_text_message ( nbiot4_t *ctx, char *phone_number, char *message_content );

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
err_t nbiot4_send_sms_pdu ( nbiot4_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

/**
 * @brief Set reset pin state.
 * @details Set @b rst pin to the selected logic level.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] state : Logic level.
 *
 * @return Nothing.
 */
void nbiot4_set_reset ( nbiot4_t *ctx, uint8_t state );

/**
 * @brief Set ri pin state.
 * @details Set @b ri pin to the selected logic level.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] state : Logic level.
 *
 * @return Nothing.
 */
void nbiot_set_ri ( nbiot4_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // NBIOT4_H

/*! @} */ // nbiot4

// ------------------------------------------------------------------------ END
