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
 * @file lteiot9.h
 * @brief This file contains API for LTE IoT 9 Click Driver.
 */

#ifndef LTEIOT9_H
#define LTEIOT9_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup lteiot9 LTE IoT 9 Click Driver
 * @brief API for configuring and manipulating LTE IoT 9 Click driver.
 * @{
 */

/**
 * @defgroup lteiot9_reg LTE IoT 9 Commands List
 * @brief List of commands of LTE IoT 9 Click driver.
 */

/**
 * @addtogroup lteiot9_reg
 * @{
 */

/**
 * @brief LTE IoT 9 description commands.
 * @details Specified AT commands for communication with LTE IoT 9 Click driver.
 */
#define LTEIOT9_CMD_AT          "AT"
#define LTEIOT9_CMD_ATI         "ATI"
#define LTEIOT9_CMD_CGMR        "AT+CGMR"
#define LTEIOT9_CMD_CFUN        "AT+CFUN"
#define LTEIOT9_CMD_CREG        "AT+CREG"
#define LTEIOT9_CMD_CEREG       "AT+CEREG"
#define LTEIOT9_CMD_CGDCONT     "AT+CGDCONT"
#define LTEIOT9_CMD_CIMI        "AT+CIMI"
#define LTEIOT9_CMD_CGATT       "AT+CGATT"
#define LTEIOT9_CMD_CSQ         "AT+CSQ"
#define LTEIOT9_CMD_CESQ        "AT+CESQ"
#define LTEIOT9_CMD_COPS        "AT+COPS"
#define LTEIOT9_CMD_URAT        "AT+URAT"
#define LTEIOT9_CMD_UBANDMASK   "AT+UBANDMASK"
#define LTEIOT9_CMD_URATCONF    "AT+URATCONF"
#define LTEIOT9_CMD_UAUTHREQ    "AT+UAUTHREQ"
#define LTEIOT9_CMD_UUICC       "AT+UUICC"
#define LTEIOT9_CMD_UCGED       "AT+UCGED"
#define LTEIOT9_CMD_UCELLINFO   "AT+UCELLINFO"
#define LTEIOT9_CMD_UANTR       "AT+UANTR"
#define LTEIOT9_CMD_CMGF        "AT+CMGF"


/*! @} */ // lteiot9_reg

/**
 * @defgroup lteiot9_set LTE IoT 9 Device Settings
 * @brief Helping defines of LTE IoT 9 Click driver.
 */

/**
 * @addtogroup lteiot9_set
 * @{
 */

/**
 * @brief LTE IoT 9 GNNS helping.
 * @details Specified command of GNSS, start of every command and command value seprator.
 */
#define LTEIOT9_GNSS_GPGGA          "GPGGA"
#define LTEIOT9_GNSS_START          '$'
#define LTEIOT9_GNSS_SEPARATOR      ','

/**
 * @brief LTE IoT 9 GPGGA value elements.
 * @details Specified element postion of GPGGA command.
 */
#define LTEIOT9_GPGGA_LATITUDE      2
#define LTEIOT9_GPGGA_LONGITUDE     4
#define LTEIOT9_GPGGA_ALTITUDE      9

/**
 * @brief LTE IoT 9 start response.
 * @details First response after device power-on/restart.
 */
#define LTEIOT9_SYSSTART            "^SYSSTART"

/**
 * @brief LTE IoT 9 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT9_RSP_OK                              "OK"
#define LTEIOT9_RSP_ERROR                           "ERROR"

/**
 * @brief LTE IoT 9 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_TX_BUFFER_SIZE          200
#define DRV_RX_BUFFER_SIZE          550

/*! @} */ // lteiot9_set

/**
 * @defgroup lteiot9_map LTE IoT 9 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 9 Click driver.
 */

/**
 * @addtogroup lteiot9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 9 Click to the selected MikroBUS.
 */
#define LTEIOT9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.smi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot9_map
/*! @} */ // lteiot9

/**
 * @brief LTE IoT 9 Click context object.
 * @details Context object definition of LTE IoT 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t smi;       /**< Description. */
    digital_out_t on;     /**< Description. */
    digital_out_t rts;       /**< Description. */

    // Input pins
    digital_in_t cts;       /**< Description. */

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];         /**< Buffer size. */

} lteiot9_t;

/**
 * @brief LTE IoT 9 Click configuration object.
 * @details Configuration object definition of LTE IoT 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t smi;          /**< Description. */
    pin_name_t on;        /**< Description. */
    pin_name_t cts;          /**< Description. */
    pin_name_t rts;        /**< Description. */

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} lteiot9_cfg_t;

/**
 * @brief LTE IoT 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTEIOT9_OK = 0,
    LTEIOT9_ERROR = -1,
    LTEIOT9_ERROR_OVERFLOW = -2,
    LTEIOT9_ERROR_TIMEOUT = -3

} lteiot9_return_value_t;

/*!
 * @addtogroup lteiot9 LTE IoT 9 Click Driver
 * @brief API for configuring and manipulating LTE IoT 9 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot9_cfg_setup ( lteiot9_cfg_t *cfg );

/**
 * @brief LTE IoT 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot9_init ( lteiot9_t *ctx, lteiot9_cfg_t *cfg );

/**
 * @brief LTE IoT 9 default configuration function.
 * @details This function executes a default configuration of LTE IoT 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lteiot9_default_cfg ( lteiot9_t *ctx );

/**
 * @brief LTE IoT 9 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot9_generic_write ( lteiot9_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LTE IoT 9 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot9_generic_read ( lteiot9_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Set ON pin state.
 * @details This function sets pin @b ON to desired state.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 *
 * @return Nothing.
 */
void lteiot9_set_pin_on ( lteiot9_t *ctx, uint8_t state );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 *
 * @return Nothing.
 */
void lteiot9_send_cmd ( lteiot9_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 *
 * @return Nothing.
 */
void lteiot9_send_cmd_with_parameter ( lteiot9_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 *
 * @return Nothing.
 */
void lteiot9_send_cmd_check ( lteiot9_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 *
 * @return Nothing.
 */
void lteiot9_send_cmd_parameter_check ( lteiot9_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 *
 * @return Nothing.
 */
void lteiot9_set_sim_apn ( lteiot9_t *ctx, char *sim_apn );

/**
 * @brief LTE IoT 9 send text message.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot9_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] message_context : Message to be sent.
 *
 * @return Nothing.
 */
void lteiot9_send_text_message ( lteiot9_t *ctx, char *phone_number, char *message_context );


#ifdef __cplusplus
}
#endif
#endif // LTEIOT9_H

/*! @} */ // lteiot9

// ------------------------------------------------------------------------ END
