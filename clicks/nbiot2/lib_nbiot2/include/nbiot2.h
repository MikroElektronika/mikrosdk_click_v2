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
 * @file nbiot2.h
 * @brief This file contains API for NB IoT 2 Click Driver.
 */

#ifndef NBIOT2_H
#define NBIOT2_H

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
 * @addtogroup nbiot2 NB IoT 2 Click Driver
 * @brief API for configuring and manipulating NB IoT 2 Click driver.
 * @{
 */

/**
 * @defgroup nbiot2_cmd NB IoT 2 Device Settings
 * @brief Settings for registers of NB IoT 2 Click driver.
 */

/**
 * @addtogroup nbiot2_cmd
 * @{
 */

/**
 * @brief NB IoT 2 control commands.
 * @details Specified setting for control commands of NB IoT 2 Click driver.
 */
#define NBIOT2_CMD_AT               "AT"
#define NBIOT2_CMD_ATI              "ATI"
#define NBIOT2_CMD_CGMR             "AT+CGMR"
#define NBIOT2_CMD_CFUN             "AT+CFUN"
#define NBIOT2_CMD_CREG             "AT+CREG"
#define NBIOT2_CMD_CEREG            "AT+CEREG"
#define NBIOT2_CMD_CGDCONT          "AT+CGDCONT"
#define NBIOT2_CMD_CIMI             "AT+CIMI"
#define NBIOT2_CMD_CGATT            "AT+CGATT"
#define NBIOT2_CMD_CSQ              "AT+CSQ"
#define NBIOT2_CMD_CESQ             "AT+CESQ"
#define NBIOT2_CMD_COPS             "AT+COPS"
#define NBIOT2_CMD_CSCON            "AT+CSCON"
#define NBIOT2_CMD_CMEE             "AT+CMEE"
#define NBIOT2_CMD_CMGS             "AT+CMGS"
#define NBIOT2_CMD_CGACT            "AT+CGACT"
#define NBIOT2_CMD_URAT             "AT+URAT"
#define NBIOT2_CMD_UBANDMASK        "AT+UBANDMASK"
#define NBIOT2_CMD_URATCONF         "AT+URATCONF"
#define NBIOT2_CMD_UAUTHREQ         "AT+UAUTHREQ"
#define NBIOT2_CMD_UUICC            "AT+UUICC"
#define NBIOT2_CMD_UCGED            "AT+UCGED"
#define NBIOT2_CMD_UCELLINFO        "AT+UCELLINFO"
#define NBIOT2_CMD_UANTR            "AT+UANTR"
#define NBIOT2_CMD_CMGF             "AT+CMGF"
#define NBIOT2_CMD_QSPCHSC          "AT+QSPCHSC"
#define NBIOT2_CMD_CPSMS            "AT+CPSMS"
#define NBIOT2_CMD_QRST             "AT+QRST"
#define NBIOT2_CMD_QBAND            "AT+QBAND"
#define NBIOT2_CMD_QNBIOTEVENT      "AT+QNBIOTEVENT"
#define NBIOT2_CMD_SM               "AT+SM"
#define NBIOT2_CMD_QSCLK            "AT+QSCLK"
#define NBIOT2_CMD_QIOPEN           "AT+QIOPEN"
#define NBIOT2_CMD_QISEND           "AT+QISEND"
#define NBIOT2_CMD_QIRD             "AT+QIRD"
#define NBIOT2_CMD_QICLOSE          "AT+QICLOSE"

/**
 * @brief NB IoT 2 device pin state commands.
 * @details Device pin state commands.
 */
#define NBIOT2_PIN_STATE_HIGH       0x01
#define NBIOT2_PIN_STATE_LOW        0x00

/**
 * @brief NB IoT 2 device response for AT commands.
 * @details Device response after commands.
 */
#define NBIOT2_RSP_OK               "OK"
#define NBIOT2_RSP_ERROR            "ERROR"

/**
 * @brief NB IoT 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NBIOT2_TX_DRV_BUFFER_SIZE    100
#define NBIOT2_RX_DRV_BUFFER_SIZE    300

/*! @} */ // nbiot2_cmd

/**
 * @defgroup nbiot2_map NB IoT 2 MikroBUS Map
 * @brief MikroBUS pin mapping of NB IoT 2 Click driver.
 */

/**
 * @addtogroup nbiot2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NB IoT 2 Click to the selected MikroBUS.
 */
#define NBIOT2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // nbiot2_map
/*! @} */ // nbiot2

/**
 * @brief NB IoT 2 Click context object.
 * @details Context object definition of NB IoT 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset. */
    digital_out_t wup;      /**< Wake-Up Interrupt. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ NBIOT2_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ NBIOT2_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} nbiot2_t;

/**
 * @brief NB IoT 2 Click configuration object.
 * @details Configuration object definition of NB IoT 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset. */
    pin_name_t wup;                 /**< Wake-Up Interrupt. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} nbiot2_cfg_t;

/**
 * @brief NB IoT 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NBIOT2_OK = 0,
    NBIOT2_ERROR = -1,
    NBIOT2_ERROR_OVERFLOW = -2,
    NBIOT2_ERROR_TIMEOUT = -3
    
} nbiot2_return_value_t;

/*!
 * @addtogroup nbiot2 NB IoT 2 Click Driver
 * @brief API for configuring and manipulating NB IoT 2 Click driver.
 * @{
 */

/**
 * @brief NB IoT 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nbiot2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nbiot2_cfg_setup ( nbiot2_cfg_t *cfg );

/**
 * @brief NB IoT 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nbiot2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nbiot2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot2_init ( nbiot2_t *ctx, nbiot2_cfg_t *cfg );

/**
 * @brief NB IoT 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot2_generic_write ( nbiot2_t *ctx, char *data_in, uint16_t len );

/**
 * @brief NB IoT 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot2_generic_read ( nbiot2_t *ctx, char *data_out, uint16_t len );

/**
 * @brief NB IoT 2 sets state of the RST pin.
 * @details This function sets RST pin state.
 * @param[in] ctx : Click context object.
 * See #nbiot_t object definition for detailed explanation.
 * @param[in] state : Pin state ( 1 or 0 ).
 * @return Nothing.
 * @note None.
 */
void nbiot2_set_rst_pin_state ( nbiot2_t *ctx, uint8_t state );

/**
 * @brief NB IoT 2 sets state of the WUP pin.
 * @details This function sets WUP pin state.
 * @param[in] ctx : Click context object.
 * See #nbiot_t object definition for detailed explanation.
 * @param[in] state : Pin state ( 1 or 0 ).
 * @return Nothing.
 * @note None.
 */
void nbiot2_set_wup_pin_state ( nbiot2_t *ctx, uint8_t state );

/**
 * @brief NB IoT 2 hardware reset function.
 * @details This function is used to perform hardwarre reset.
 * @param[in] ctx : Click context object.
 * See #nbiot_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void nbiot2_hw_reset ( nbiot2_t *ctx );

/**
 * @brief NB IoT 2 send command function.
 * @details This function sends the specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void nbiot2_send_cmd ( nbiot2_t *ctx, char *cmd );

/**
 * @brief NB IoT 2 send command function with parameter.
 * @details This function sends commands to the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void nbiot2_send_cmd_with_parameter ( nbiot2_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief NB IoT 2 check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #nbiot_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void nbiot2_send_cmd_check ( nbiot2_t *ctx, char *at_cmd_buf );

/**
 * @brief NB IoT 2 check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #nbiot_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void nbiot2_send_cmd_parameter_check ( nbiot2_t *ctx, char *at_cmd_buf );

/**
 * @brief NB IoT 2 set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #nbiot_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void nbiot2_set_apn( nbiot2_t *ctx, char *apn );

/**
 * @brief NB IoT 2 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See ##nbiot_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void nbiot2_send_sms_text_mode ( nbiot2_t *ctx, char *phone_number, char *message_context );

/**
 * @brief NB IoT 2 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See ##nbiot_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot2_send_sms_pdu ( nbiot2_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

#ifdef __cplusplus
}
#endif
#endif // NBIOT2_H

/*! @} */ // nbiot2

// ------------------------------------------------------------------------ END
