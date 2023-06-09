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
 * @defgroup nbiot4_set NB IoT 4 Device Settings
 * @brief Settings for registers of NB IoT 4 Click driver.
 */

/**
 * @addtogroup nbiot4_set
 * @{
 */

/**
 * @brief NB IoT 4 control commands.
 * @details Specified setting for control commands of NB IoT 4 Click driver.
 */
#define NBIOT4_CMD_AT                           "AT"
#define NBIOT4_CMD_ATE1                         "ATE1"
#define NBIOT4_CMD_CFUN                         "AT+CFUN"
#define NBIOT4_CMD_CREG                         "AT+CREG"
#define NBIOT4_CMD_CEREG                        "AT+CEREG"
#define NBIOT4_CMD_CGDCONT                      "AT+CGDCONT"
#define NBIOT4_CMD_CSQ                          "AT+CSQ"
#define NBIOT4_CMD_COPS                         "AT+COPS"
#define NBIOT4_CMD_CMGS                         "AT+CMGS"
#define NBIOT4_CMD_CMGF                         "AT+CMGF"
#define NBIOT4_CMD_SIMSWAP                      "AT^SIMSWAP"
#define NBIOT4_CMD_TRB                          "AT+TRB"
#define NBIOT4_CMD_CIPMUX                       "AT+CIPMUX"
#define NBIOT4_CMD_CIPSTART                     "AT+CIPSTART"
#define NBIOT4_CMD_CIPCLOSE                     "AT+CIPCLOSE"
#define NBIOT4_CMD_CIPSEND                      "AT+CIPSEND"
#define NBIOT4_CMD_CIPHEAD                      "AT+CIPHEAD"

/**
 * @brief NB IoT 4 device response for AT commands.
 * @details Device response after commands.
 */
#define NBIOT4_RSP_OK                           "OK"
#define NBIOT4_RSP_ERROR                        "ERROR"
#define NBIOT4_RSP_REBOOTING                    "REBOOTING"

/**
 * @brief NB IoT 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NBIOT4_RX_DRV_BUFFER_SIZE               256
#define NBIOT4_TX_DRV_BUFFER_SIZE               256

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
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring   = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nbiot4_map
/*! @} */ // nbiot4

/**
 * @brief NB IoT 4 Click context object.
 * @details Context object definition of NB IoT 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset pin (Active low). */
    digital_out_t cs;       /**< SPI chip select pin. */

    // Input pins
    digital_in_t ring;      /**< Ring indication pin. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ NBIOT4_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ NBIOT4_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} nbiot4_t;

/**
 * @brief NB IoT 4 Click configuration object.
 * @details Configuration object definition of NB IoT 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;         /**< Reset pin (Active low). */
    pin_name_t cs;          /**< SPI chip select pin. */
    pin_name_t ring;        /**< Ring indication pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} nbiot4_cfg_t;

/**
 * @brief NB IoT 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NBIOT4_OK = 0,
    NBIOT4_ERROR = -1,
    NBIOT4_ERROR_TIMEOUT = -2,
    NBIOT4_ERROR_CMD = -3,
    NBIOT4_ERROR_UNKNOWN = -4

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
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot4_init ( nbiot4_t *ctx, nbiot4_cfg_t *cfg );

/**
 * @brief NB IoT 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot4_generic_write ( nbiot4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NB IoT 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot4_generic_read ( nbiot4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NB IoT 4 set rst pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot4_set_rst_pin ( nbiot4_t *ctx, uint8_t state );

/**
 * @brief NB IoT 4 set cs pin function.
 * @details This function sets the SPI chip select (CS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot4_set_cs_pin ( nbiot4_t *ctx, uint8_t state );

/**
 * @brief NB IoT 4 get ring pin function.
 * @details This function returns the ring indication (RI) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nbiot4_get_ring_pin ( nbiot4_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void nbiot4_send_cmd ( nbiot4_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void nbiot4_send_cmd_with_par ( nbiot4_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void nbiot4_send_cmd_check ( nbiot4_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void nbiot4_send_cmd_par_check ( nbiot4_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void nbiot4_set_sim_apn ( nbiot4_t *ctx, uint8_t *sim_apn );

/**
 * @brief NB IoT 4 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void nbiot4_send_sms_text ( nbiot4_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief NB IoT 4 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #nbiot4_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot4_send_sms_pdu ( nbiot4_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // NBIOT4_H

/*! @} */ // nbiot4

// ------------------------------------------------------------------------ END
