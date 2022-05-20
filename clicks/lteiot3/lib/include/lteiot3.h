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
 * @file lteiot3.h
 * @brief This file contains API for LTE IoT 3 Click Driver.
 */

#ifndef LTEIOT3_H
#define LTEIOT3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup lteiot3 LTE IoT 3 Click Driver
 * @brief API for configuring and manipulating LTE IoT 3 Click driver.
 * @{
 */

/**
 * @defgroup lteiot3_cmd LTE IoT 3 Device Settings
 * @brief Settings for registers of LTE IoT 3 Click driver.
 */

/**
 * @addtogroup lteiot3_cmd
 * @{
 */

/**
 * @brief LTE IoT 3 description commands.
 * @details Specified AT commands for communication with LTE IoT 3 Click driver.
 */
#define LTEIOT3_CMD_AT          "AT"
#define LTEIOT3_CMD_ATI         "ATI"
#define LTEIOT3_CMD_CGMR        "AT+CGMR"
#define LTEIOT3_CMD_CFUN        "AT+CFUN"
#define LTEIOT3_CMD_CREG        "AT+CREG"
#define LTEIOT3_CMD_CEREG       "AT+CEREG"
#define LTEIOT3_CMD_CGDCONT     "AT+CGDCONT"
#define LTEIOT3_CMD_CIMI        "AT+CIMI"
#define LTEIOT3_CMD_CGATT       "AT+CGATT"
#define LTEIOT3_CMD_CSQ         "AT+CSQ"
#define LTEIOT3_CMD_CESQ        "AT+CESQ"
#define LTEIOT3_CMD_COPS        "AT+COPS"
#define LTEIOT3_CMD_URAT        "AT+URAT"
#define LTEIOT3_CMD_UBANDMASK   "AT+UBANDMASK"
#define LTEIOT3_CMD_URATCONF    "AT+URATCONF"
#define LTEIOT3_CMD_UAUTHREQ    "AT+UAUTHREQ"
#define LTEIOT3_CMD_UUICC       "AT+UUICC"
#define LTEIOT3_CMD_UCGED       "AT+UCGED"
#define LTEIOT3_CMD_UCELLINFO   "AT+UCELLINFO"
#define LTEIOT3_CMD_UANTR       "AT+UANTR"
#define LTEIOT3_CMD_CMGF        "AT+CMGF"

/**
 * @brief LTE IoT 3 GNNS helping.
 * @details Specified command of GNSS, start of every command and command value seprator.
 */
#define LTEIOT3_GNSS_GPGGA          "GPGGA"
#define LTEIOT3_GNSS_START          '$'
#define LTEIOT3_GNSS_SEPARATOR      ','

/**
 * @brief LTE IoT 3 GPGGA value elements.
 * @details Specified element postion of GPGGA command.
 */
#define LTEIOT3_GPGGA_LATITUDE      2
#define LTEIOT3_GPGGA_LONGITUDE     4
#define LTEIOT3_GPGGA_ALTITUDE      9

/**
 * @brief LTE IoT 3 start response.
 * @details First response after device power-on/restart.
 */
#define LTEIOT3_SYSSTART            "^SYSSTART"

/**
 * @brief LTE IoT 3 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT3_RSP_OK                              "OK"
#define LTEIOT3_RSP_ERROR                           "ERROR"

/**
 * @brief LTE IoT 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_TX_BUFFER_SIZE          200
#define DRV_RX_BUFFER_SIZE          550

/*! @} */ // lteiot3_cmd

/**
 * @defgroup lteiot3_map LTE IoT 3 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 3 Click driver.
 */

/**
 * @addtogroup lteiot3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 3 Click to the selected MikroBUS.
 */
#define LTEIOT3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.smi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot3_map
/*! @} */ // lteiot3

/**
 * @brief LTE IoT 3 Click context object.
 * @details Context object definition of LTE IoT 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t smi;      /**< SUSPEND Mode. */
    digital_out_t on;       /**< Ignition. */
    digital_out_t cs;       /**< SPI Chip Selec. */
    digital_out_t rts;      /**< Ready to Send. */

    // Input pins
    digital_in_t cts;       /**< Clear to Send. */

    // Modules
    uart_t uart;                                        /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];          /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];          /**< Buffer size. */

} lteiot3_t;

/**
 * @brief LTE IoT 3 Click configuration object.
 * @details Configuration object definition of LTE IoT 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t smi;         /**< SUSPEND Mode. */
    pin_name_t on;          /**< Ignition. */
    pin_name_t cts;         /**< Clear to Send. */
    pin_name_t cs;          /**< SPI Chip Selec. */
    pin_name_t rts;         /**< Ready to Send. */

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} lteiot3_cfg_t;

/**
 * @brief LTE IoT 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTEIOT3_OK = 0,
    LTEIOT3_ERROR = -1,
    LTEIOT3_ERROR_OVERFLOW = -2,
    LTEIOT3_ERROR_TIMEOUT = -3

} lteiot3_return_value_t;

/*!
 * @addtogroup lteiot3 LTE IoT 3 Click Driver
 * @brief API for configuring and manipulating LTE IoT 3 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot3_cfg_setup ( lteiot3_cfg_t *cfg );

/**
 * @brief LTE IoT 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lteiot3_init ( lteiot3_t *ctx, lteiot3_cfg_t *cfg );

/**
 * @brief LTE IoT 3 default configuration function.
 * @details This function executes a default configuration of LTE IoT 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lteiot3_default_cfg ( lteiot3_t *ctx );

/**
 * @brief LTE IoT 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lteiot3_generic_write ( lteiot3_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LTE IoT 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lteiot3_generic_read ( lteiot3_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Set ON pin state.
 * @details This function sets pin @b ON to desired state.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * @return Nothing.
 */
void lteiot3_set_pin_on ( lteiot3_t *ctx, uint8_t state );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 */
void lteiot3_send_cmd ( lteiot3_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 */
void lteiot3_send_cmd_with_parameter ( lteiot3_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 */
void lteiot3_send_cmd_check ( lteiot3_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 */
void lteiot3_send_cmd_parameter_check ( lteiot3_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 */
void lteiot3_set_sim_apn ( lteiot3_t *ctx, char *sim_apn );

/**
 * @brief LTE IoT 3 send text message.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] message_context : Message to be sent.
 * @return Nothing.
 */
void lteiot3_send_text_message ( lteiot3_t *ctx, char *phone_number, char *message_context );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT3_H

/*! @} */ // lteiot3

// ------------------------------------------------------------------------ END
