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
 * @file lteiot6.h
 * @brief This file contains API for LTE IoT 6 Click Driver.
 */

#ifndef LTEIOT6_H
#define LTEIOT6_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"


/*!
 * @addtogroup lteiot6 LTE IoT 6 Click Driver
 * @brief API for configuring and manipulating LTE IoT 6 Click driver.
 * @{
 */

/**
 * @defgroup lteiot6_reg LTE IoT 6 Commands List
 * @brief List of commands of LTE IoT 6 Click driver.
 */

/**
 * @addtogroup lteiot6_cmd
 * @{
 */

/**
 * @brief LTE IoT 6 description commands.
 * @details Specified AT commands for communication with LTE IoT 6 Click driver.
 */
#define LTEIOT6_CMD_AT          "AT"
#define LTEIOT6_CMD_ATI         "ATI"
#define LTEIOT6_CMD_CGMR        "AT+CGMR"
#define LTEIOT6_CMD_CFUN        "AT+CFUN"
#define LTEIOT6_CMD_CREG        "AT+CREG"
#define LTEIOT6_CMD_CEREG       "AT+CEREG"
#define LTEIOT6_CMD_CGDCONT     "AT+CGDCONT"
#define LTEIOT6_CMD_CIMI        "AT+CIMI"
#define LTEIOT6_CMD_CGATT       "AT+CGATT"
#define LTEIOT6_CMD_CSQ         "AT+CSQ"
#define LTEIOT6_CMD_CESQ        "AT+CESQ"
#define LTEIOT6_CMD_COPS        "AT+COPS"
#define LTEIOT6_CMD_CMGF        "AT+CMGF"
#define LTEIOT6_CMD_CMGS        "AT+CMGS"
#define LTEIOT6_CMD_CSCA        "AT+CSCA"
#define LTEIOT6_CMD_SQNLED      "AT+SQNLED"

/*! @} */ // lteiot6_cmd

/**
 * @defgroup lteiot6_set LTE IoT 6 Device Settings
 * @brief Settings for registers of LTE IoT 6 Click driver.
 */

/**
 * @addtogroup lteiot6_set
 * @{
 */

/**
 * @brief LTE IoT 6 description setting.
 * @details Specified setting for description of LTE IoT 6 Click driver.
 */
#define LTEIOT6_RSP_OK          "OK"
#define LTEIOT6_RSP_ERROR       "ERROR"
#define LTEIOT6_RSP_SYSTART     "+SYSSTART"

/**
 * @brief LTE IoT 6 driver buffer size.
 * @details Specified size of driver ring buffer.
 */
#define DRV_BUFFER_SIZE                       400

/*! @} */ // lteiot6_set

/**
 * @defgroup lteiot6_map LTE IoT 6 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 6 Click driver.
 */

/**
 * @addtogroup lteiot6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 6 Click to the selected MikroBUS.
 */
#define LTEIOT6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.ri = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot6_map
/*! @} */ // lteiot6

/**
 * @brief LTE IoT 6 Click context object.
 * @details Context object definition of LTE IoT 6 Click driver.
 */
typedef struct
{
    // Output pins 
    digital_out_t pwr;
    digital_out_t rst;
    digital_out_t rts;

    // Input pins 
    digital_in_t ri;
    digital_in_t cts;
    digital_in_t rx_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];

} lteiot6_t;

/**
 * @brief LTE IoT 6 Click configuration object.
 * @details Configuration object definition of LTE IoT 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 
    pin_name_t pwr;
    pin_name_t rst;
    pin_name_t rts;
    pin_name_t ri;
    pin_name_t cts;

    // static variable 
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} lteiot6_cfg_t;

/**
 * @brief LTE IoT 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LTEIOT6_OK = 0,
   LTEIOT6_ERROR = -1,
   LTEIOT6_ERROR_TIMEOUT = -2,
   LTEIOT6_ERROR_CMD = -3,
   LTEIOT6_ERROR_UNKNOWN = -4

} lteiot8_return_value_t;

/*!
 * @addtogroup lteiot6 LTE IoT 6 Click Driver
 * @brief API for configuring and manipulating LTE IoT 6 Click driver.
 * @{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief LTE IoT 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot6_cfg_setup ( lteiot6_cfg_t *cfg );

/**
 * @brief LTE IoT 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot6_init ( lteiot6_t *ctx, lteiot6_cfg_t *cfg );

/**
 * @brief LTE IoT 6 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot6_generic_write ( lteiot6_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LTE IoT 6 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot6_generic_read ( lteiot6_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief LTE IoT 6 power on.
 * @details This function powers on the chip on LTE IoT 6 click.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @return Nothing.
 */
void lteiot6_power_on ( lteiot6_t *ctx );

/**
 * @brief LTE IoT 6 power on.
 * @details This function resets the chip on LTE IoT 6 click.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @return Nothing.
 */
void lteiot6_reset ( lteiot6_t *ctx );

/**
 * @brief Sets state of the PWR pin.
 * @details This function sets PWR pin state.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void lteiot6_set_pwr ( lteiot6_t *ctx, uint8_t state );

/**
 * @brief Sets state of the RST pin.
 * @details This function sets RST pin state.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void lteiot6_set_rst ( lteiot6_t *ctx, uint8_t state );

/**
 * @brief Sets state of the RTS pin.
 * @details This function sets RTS pin state.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void lteiot6_set_rts ( lteiot6_t *ctx, uint8_t state );

/**
 * @brief RI Pin Get function
 * @details This function allows user to check state of the RI pin.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t lteiot6_get_ri ( lteiot6_t *ctx );

/**
 * @brief CTS Pin Get function
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t lteiot6_get_cts ( lteiot6_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 * 
 * @note Example of cmd -> "AT+CFUN=1".
 */
void lteiot6_send_cmd ( lteiot6_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 * 
 * @note Example of at_cmd_buf -> "AT+CFUN".
 */
void lteiot6_send_cmd_with_parameter ( lteiot6_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 * 
 * @note Example of at_cmd_buf -> "AT+CFUN".
 */
void lteiot6_send_cmd_check ( lteiot6_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the parameters of command.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 * 
 * @note Example of at_cmd_buf -> "AT+CFUN".
 */
void lteiot6_send_cmd_parameter_check ( lteiot6_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 * 
 * @note Example of sim_apn -> "vip.mobile".
 */
void lteiot6_set_sim_apn ( lteiot6_t *ctx, char *sim_apn );

/**
 * @brief Send SMS message to number in text mode.
 * @details Send command for SIM message with function 
 * parameters for device to send SMS message.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to send message to.
 * @param[in] message_context : Content of the message.
 *
 * @return Nothing.
 * @note Device should be configured for .
 */
void lteiot6_send_text_message ( lteiot6_t *ctx, char *phone_number, char *message_content );

/**
 * @brief Send SMS message to number in pdu mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #lteiot6_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t lteiot6_send_sms_pdu ( lteiot6_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT6_H

/*! @} */ // lteiot6

// ------------------------------------------------------------------------ END
