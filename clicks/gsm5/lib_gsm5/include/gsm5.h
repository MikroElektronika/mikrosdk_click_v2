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
 * @file gsm5.h
 * @brief This file contains API for GSM 5 Click Driver.
 */

#ifndef GSM5_H
#define GSM5_H

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
 * @addtogroup gsm5 GSM 5 Click Driver
 * @brief API for configuring and manipulating GSM 5 Click driver.
 * @{
 */

/**
 * @defgroup gsm5_cmd GSM 5 Device Settings
 * @brief Settings for registers of GSM 5 Click driver.
 */

/**
 * @addtogroup gsm5_cmd
 * @{
 */

/**
 * @brief GSM 5 control commands.
 * @details Specified setting for control commands of GSM 5 Click driver.
 */
#define GSM5_CMD_AT                 "AT"
#define GSM5_CMD_ATI                "ATI"
#define GSM5_CMD_CGMR               "AT+CGMR"
#define GSM5_CMD_CFUN               "AT+CFUN"
#define GSM5_CMD_CREG               "AT+CREG"
#define GSM5_CMD_CGREG              "AT+CGREG"
#define GSM5_CMD_CGDCONT            "AT+CGDCONT"
#define GSM5_CMD_CIMI               "AT+CIMI"
#define GSM5_CMD_CMEE               "AT+CMEE"
#define GSM5_CMD_CGATT              "AT+CGATT"
#define GSM5_CMD_CSQ                "AT+CSQ"
#define GSM5_CMD_COPS               "AT+COPS"
#define GSM5_CMD_CMGS               "AT+CMGS"
#define GSM5_CMD_CMGF               "AT+CMGF"
#define GSM5_CMD_CGACT              "AT+CGACT"
#define GSM5_CMD_UPSDA              "AT+UPSDA"
#define GSM5_CMD_USOCR              "AT+USOCR"
#define GSM5_CMD_USOCO              "AT+USOCO"
#define GSM5_CMD_USOWR              "AT+USOWR"
#define GSM5_CMD_USORD              "AT+USORD"
#define GSM5_CMD_USORF              "AT+USORF"
#define GSM5_CMD_USOCL              "AT+USOCL"

/**
 * @brief GSM 5 device response for AT commands.
 * @details Device response after commands.
 */
#define GSM5_RSP_OK                 "OK"
#define GSM5_RSP_ERROR              "ERROR"

/**
 * @brief GSM 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE             256

/*! @} */ // gsm5_cmd

/**
 * @defgroup gsm5_map GSM 5 MikroBUS Map
 * @brief MikroBUS pin mapping of GSM 5 Click driver.
 */

/**
 * @addtogroup gsm5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GSM 5 Click to the selected MikroBUS.
 */
#define GSM5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.off = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gsm5_map
/*! @} */ // gsm5

/**
 * @brief GSM 5 Click context object.
 * @details Context object definition of GSM 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;           /**< Power ON pin. */
    digital_out_t off;          /**< Power OFF pin. */
    digital_out_t rts;          /**< Request to send pin. */

    // Input pins
    digital_in_t ring;          /**< Ring indicator pin. */
    digital_in_t cts;           /**< Clear to send pin. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */

} gsm5_t;

/**
 * @brief GSM 5 Click configuration object.
 * @details Configuration object definition of GSM 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t on;              /**< Power ON pin. */
    pin_name_t off;             /**< Power OFF pin. */
    pin_name_t rts;             /**< Request to send pin. */
    pin_name_t ring;            /**< Ring indicator pin. */
    pin_name_t cts;             /**< Clear to send pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} gsm5_cfg_t;

/**
 * @brief GSM 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GSM5_OK = 0,
    GSM5_ERROR = -1,
    GSM5_ERROR_TIMEOUT = -2,
    GSM5_ERROR_CMD = -3,
    GSM5_ERROR_UNKNOWN = -4

} gsm5_return_value_t;

/*!
 * @addtogroup gsm5 GSM 5 Click Driver
 * @brief API for configuring and manipulating GSM 5 Click driver.
 * @{
 */

/**
 * @brief GSM 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gsm5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gsm5_cfg_setup ( gsm5_cfg_t *cfg );

/**
 * @brief GSM 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gsm5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm5_init ( gsm5_t *ctx, gsm5_cfg_t *cfg );

/**
 * @brief GSM 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm5_generic_write ( gsm5_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief GSM 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm5_generic_read ( gsm5_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Sets state of the ON pin.
 * @details This function sets the ON pin state.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 * @note None.
 */
void gsm5_set_on_pin ( gsm5_t *ctx, uint8_t state );

/**
 * @brief Sets state of the OFF pin.
 * @details This function sets the OFF pin state.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 * @note None.
 */
void gsm5_set_off_pin ( gsm5_t *ctx, uint8_t state );

/**
 * @brief Sets state of the RTS pin.
 * @details This function sets the RTS pin state.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 * @note None.
 */
void gsm5_set_rts_pin ( gsm5_t *ctx, uint8_t state );

/**
 * @brief RING Pin Get function.
 * @details This function allows user to check state of the RING pin.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 * @note None.
 */
uint8_t gsm5_get_ring_pin ( gsm5_t *ctx );

/**
 * @brief CTS Pin Get function.
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 * @note None.
 */
uint8_t gsm5_get_cts_pin ( gsm5_t *ctx );

/**
 * @brief Power ON the module function.
 * @details This function powers ON the module.
 * @param ctx Click object.
 * @return Nothing.
 * @note None.
 */
void gsm5_module_power_on ( gsm5_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void gsm5_send_cmd ( gsm5_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void gsm5_send_cmd_with_parameter ( gsm5_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void gsm5_send_cmd_check ( gsm5_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void gsm5_send_cmd_parameter_check ( gsm5_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void gsm5_set_sim_apn ( gsm5_t *ctx, char *sim_apn );

/**
 * @brief GSM 5 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void gsm5_send_sms_text ( gsm5_t *ctx, char *phone_number, char *sms_text );

/**
 * @brief GSM 5 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #gsm5_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsm5_send_sms_pdu ( gsm5_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

#ifdef __cplusplus
}
#endif
#endif // GSM5_H

/*! @} */ // gsm5

// ------------------------------------------------------------------------ END
