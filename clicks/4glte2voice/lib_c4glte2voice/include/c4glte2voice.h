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
 * @file c4glte2voice.h
 * @brief This file contains API for 4G LTE 2 Voice Click Driver.
 */

#ifndef C4GLTE2VOICE_H
#define C4GLTE2VOICE_H

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
 * @addtogroup c4glte2voice 4G LTE 2 Voice Click Driver
 * @brief API for configuring and manipulating 4G LTE 2 Voice Click driver.
 * @{
 */

/**
 * @defgroup c4glte2voice_cmd 4G LTE 2 Voice Device Settings
 * @brief Settings for registers of 4G LTE 2 Voice Click driver.
 */

/**
 * @addtogroup c4glte2voice_cmd
 * @{
 */

/**
 * @brief 4G LTE 2 Voice control commands.
 * @details Specified setting for control commands of 4G LTE 2 Voice Click driver.
 */
#define C4GLTE2VOICE_CMD_AT                             "AT"
#define C4GLTE2VOICE_CMD_ATI                            "ATI"
#define C4GLTE2VOICE_CMD_CGMR                           "AT+CGMR"
#define C4GLTE2VOICE_CMD_CFUN                           "AT+CFUN"
#define C4GLTE2VOICE_CMD_CREG                           "AT+CREG"
#define C4GLTE2VOICE_CMD_CGREG                          "AT+CGREG"
#define C4GLTE2VOICE_CMD_CGDCONT                        "AT+CGDCONT"
#define C4GLTE2VOICE_CMD_CIMI                           "AT+CIMI"
#define C4GLTE2VOICE_CMD_CMEE                           "AT+CMEE"
#define C4GLTE2VOICE_CMD_CGATT                          "AT+CGATT"
#define C4GLTE2VOICE_CMD_CSQ                            "AT+CSQ"
#define C4GLTE2VOICE_CMD_COPS                           "AT+COPS"
#define C4GLTE2VOICE_CMD_CMGS                           "AT+CMGS"
#define C4GLTE2VOICE_CMD_CMGF                           "AT+CMGF"
#define C4GLTE2VOICE_CMD_CGACT                          "AT+CGACT"
#define C4GLTE2VOICE_CMD_USOCR                          "AT+USOCR"
#define C4GLTE2VOICE_CMD_USOCO                          "AT+USOCO"
#define C4GLTE2VOICE_CMD_USOWR                          "AT+USOWR"
#define C4GLTE2VOICE_CMD_USOST                          "AT+USOST"
#define C4GLTE2VOICE_CMD_USORD                          "AT+USORD"
#define C4GLTE2VOICE_CMD_USORF                          "AT+USORF"
#define C4GLTE2VOICE_CMD_USOCL                          "AT+USOCL"
#define C4GLTE2VOICE_CMD_UGPS                           "AT+UGPS"
#define C4GLTE2VOICE_CMD_UGGGA                          "AT+UGGGA"

/**
 * @brief 4G LTE 2 Voice device response for AT commands.
 * @details Device response after commands.
 */
#define C4GLTE2VOICE_RSP_OK                             "OK"
#define C4GLTE2VOICE_RSP_ERROR                          "ERROR"

/**
 * @brief 4G LTE 2 Voice power state settings.
 * @details Specified power state settings of 4G LTE 2 Voice Click driver.
 */
#define C4GLTE2VOICE_POWER_STATE_OFF                    0
#define C4GLTE2VOICE_POWER_STATE_ON                     1

/**
 * @brief 4G LTE 2 Voice driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                                 256

/*! @} */ // c4glte2voice_cmd

/**
 * @defgroup c4glte2voice_map 4G LTE 2 Voice MikroBUS Map
 * @brief MikroBUS pin mapping of 4G LTE 2 Voice Click driver.
 */

/**
 * @addtogroup c4glte2voice_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 4G LTE 2 Voice Click to the selected MikroBUS.
 */
#define C4GLTE2VOICE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sts = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ri = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // c4glte2voice_map
/*! @} */ // c4glte2voice

/**
 * @brief 4G LTE 2 Voice Click context object.
 * @details Context object definition of 4G LTE 2 Voice Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sts;      /**< GNSS Supply enable pin. */
    digital_out_t pwr;      /**< Power-on pin. */
    digital_out_t rts;      /**< UART ready to send pin. */

    // Input pins
    digital_in_t ri;        /**< Ring indication pin. */
    digital_in_t cts;       /**< UART clear to send pin. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */

} c4glte2voice_t;

/**
 * @brief 4G LTE 2 Voice Click configuration object.
 * @details Configuration object definition of 4G LTE 2 Voice Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t sts;         /**< GNSS Supply enable pin. */
    pin_name_t pwr;         /**< Power-on pin. */
    pin_name_t rts;         /**< UART ready to send pin. */
    pin_name_t ri;          /**< Ring indication pin. */
    pin_name_t cts;         /**< UART clear to send pin. */

    // Static variable
    uint32_t         baud_rate;             /**< Clock speed. */
    bool             uart_blocking;         /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;              /**< Data bits. */
    uart_parity_t    parity_bit;            /**< Parity bit. */
    uart_stop_bits_t stop_bit;              /**< Stop bits. */

} c4glte2voice_cfg_t;

/**
 * @brief 4G LTE 2 Voice Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C4GLTE2VOICE_OK = 0,
    C4GLTE2VOICE_ERROR = -1,
    C4GLTE2VOICE_ERROR_TIMEOUT = -2,
    C4GLTE2VOICE_ERROR_CMD = -3,
    C4GLTE2VOICE_ERROR_UNKNOWN = -4

} c4glte2voice_return_value_t;

/*!
 * @addtogroup c4glte2voice 4G LTE 2 Voice Click Driver
 * @brief API for configuring and manipulating 4G LTE 2 Voice Click driver.
 * @{
 */

/**
 * @brief 4G LTE 2 Voice configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c4glte2voice_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c4glte2voice_cfg_setup ( c4glte2voice_cfg_t *cfg );

/**
 * @brief 4G LTE 2 Voice initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c4glte2voice_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glte2voice_init ( c4glte2voice_t *ctx, c4glte2voice_cfg_t *cfg );

/**
 * @brief 4G LTE 2 Voice data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glte2voice_generic_write ( c4glte2voice_t *ctx, char *data_in, uint16_t len );

/**
 * @brief 4G LTE 2 Voice data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glte2voice_generic_read ( c4glte2voice_t *ctx, char *data_out, uint16_t len );

/**
 * @brief 4G LTE 2 Voice set PWR pin function.
 * @details This function sets the PWR pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c4glte2voice_set_pwr_pin ( c4glte2voice_t *ctx, uint8_t state );

/**
 * @brief 4G LTE 2 Voice set STS pin function.
 * @details This function sets the GNSS supply enable (STS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c4glte2voice_set_sts_pin ( c4glte2voice_t *ctx, uint8_t state );

/**
 * @brief 4G LTE 2 Voice set RTS pin function.
 * @details This function sets the ready to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c4glte2voice_set_rts_pin ( c4glte2voice_t *ctx, uint8_t state );

/**
 * @brief 4G LTE 2 Voice get RI pin function.
 * @details This function returns the ring indication (RI) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c4glte2voice_get_ri_pin ( c4glte2voice_t *ctx );

/**
 * @brief 4G LTE 2 Voice get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c4glte2voice_get_cts_pin ( c4glte2voice_t *ctx );

/**
 * @brief 4G LTE 2 Voice set power state function.
 * @details This function sets a desired power state by toggling PWR pin with a specific time for high state.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON.
 * @return None.
 * @note None.
 */
void c4glte2voice_set_power_state ( c4glte2voice_t *ctx, uint8_t state );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void c4glte2voice_send_cmd ( c4glte2voice_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the Click module.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void c4glte2voice_send_cmd_with_parameter ( c4glte2voice_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void c4glte2voice_send_cmd_check ( c4glte2voice_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void c4glte2voice_send_cmd_parameter_check ( c4glte2voice_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void c4glte2voice_set_sim_apn ( c4glte2voice_t *ctx, char *sim_apn );

/**
 * @brief 4G LTE 2 Voice send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void c4glte2voice_send_sms_text ( c4glte2voice_t *ctx, char *phone_number, char *sms_text );

/**
 * @brief 4G LTE 2 Voice send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #c4glte2voice_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glte2voice_send_sms_pdu ( c4glte2voice_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

#ifdef __cplusplus
}
#endif
#endif // C4GLTE2VOICE_H

/*! @} */ // c4glte2voice

// ------------------------------------------------------------------------ END
