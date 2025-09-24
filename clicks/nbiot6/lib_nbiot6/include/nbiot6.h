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
 * @file nbiot6.h
 * @brief This file contains API for NB IoT 6 Click Driver.
 */

#ifndef NBIOT6_H
#define NBIOT6_H

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
 * @addtogroup nbiot6 NB IoT 6 Click Driver
 * @brief API for configuring and manipulating NB IoT 6 Click driver.
 * @{
 */

/**
 * @defgroup nbiot6_cmd NB IoT 6 Device Settings
 * @brief Settings for registers of NB IoT 6 Click driver.
 */

/**
 * @addtogroup nbiot6_cmd
 * @{
 */

/**
 * @brief NB IoT 6 control commands.
 * @details Specified setting for control commands of NB IoT 6 Click driver.
 */
#define NBIOT6_CMD_AT                               "AT"
#define NBIOT6_CMD_GET_MODEL_ID                     "AT+CGMM"
#define NBIOT6_CMD_GET_MANUFACTURER_REVISION        "AT+CGMR"
#define NBIOT6_CMD_GET_SERIAL_NUM                   "AT+CGSN"
#define NBIOT6_CMD_SET_UE_FUNCTIONALITY             "AT+CFUN"
#define NBIOT6_CMD_NETWORK_REGISTRATION             "AT+CEREG"
#define NBIOT6_CMD_SIGNAL_QUALITY_REPORT            "AT+CSQ"
#define NBIOT6_CMD_OPERATOR_SELECTION               "AT+COPS"
#define NBIOT6_CMD_SEND_SMS                         "AT+CMGS"
#define NBIOT6_CMD_SELECT_SMS_FORMAT                "AT+CMGF"
#define NBIOT6_CMD_DEFINE_PDP_CONTEXT               "AT+CGDCONT"
#define NBIOT6_CMD_ACTIVATE_PDP_CONTEXT             "AT+CGACT"
#define NBIOT6_CMD_SHOW_PDP_ADDRESS                 "AT+CGPADDR"
#define NBIOT6_CMD_OPEN_SOCKET                      "AT+QIOPEN"
#define NBIOT6_CMD_CLOSE_SOCKET                     "AT+QICLOSE"
#define NBIOT6_CMD_SEND_TCP_IP_TEXT_DATA            "AT+QISEND"
#define NBIOT6_CMD_RECEIVE_TCP_IP_DATA              "AT+QIRD"
#define NBIOT6_CMD_CONFIG_NETLIGHT_LED              "AT+QLEDMODE"

/**
 * @brief NB IoT 6 device response for AT commands.
 * @details Device response after commands.
 */
#define NBIOT6_RSP_OK                               "OK"
#define NBIOT6_RSP_ERROR                            "ERROR"
#define NBIOT6_RSP_CLOSE_OK                         "CLOSE OK"

/**
 * @brief NB IoT 6 device response time for AT commands.
 * @details Device response time after commands.
 */
#define NBIOT6_MAX_RSP_TIME_DEFAULT                 300ul
#define NBIOT6_MAX_RSP_TIME_COPS                    630000ul
#define NBIOT6_MAX_RSP_TIME_CGACT                   150000ul
#define NBIOT6_MAX_RSP_TIME_CFUN                    90000ul
#define NBIOT6_MAX_RSP_TIME_CMGS                    30000ul
#define NBIOT6_MAX_RSP_TIME_QICLOSE                 15000ul
#define NBIOT6_MAX_RSP_TIME_URC                     15000ul

/**
 * @brief NB IoT 6 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define NBIOT6_URC_OPEN_SOCKET                      "+QIOPEN: "
#define NBIOT6_URC_RECEIVED_DATA                    "+QIURC: \"recv\""
#define NBIOT6_URC_NETWORK_REGISTERED               "+CEREG: 2,1"
#define NBIOT6_URC_SMS_FORMAT_PDU                   "+CMGF: 0"
#define NBIOT6_URC_SMS_FORMAT_TXT                   "+CMGF: 1"

/**
 * @brief NB IoT 6 power state settings.
 * @details Specified power state settings of NB IoT 6 Click driver.
 */
#define NBIOT6_POWER_STATE_OFF                      0
#define NBIOT6_POWER_STATE_ON                       1
#define NBIOT6_POWER_STATE_RESET                    2
#define NBIOT6_POWER_STATE_WAKEUP                   3

/**
 * @brief NB IoT 6 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NBIOT6_TX_DRV_BUFFER_SIZE                   256
#define NBIOT6_RX_DRV_BUFFER_SIZE                   256

/*! @} */ // nbiot6_cmd

/**
 * @defgroup nbiot6_map NB IoT 6 MikroBUS Map
 * @brief MikroBUS pin mapping of NB IoT 6 Click driver.
 */

/**
 * @addtogroup nbiot6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NB IoT 6 Click to the selected MikroBUS.
 */
#define NBIOT6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // nbiot6_map
/*! @} */ // nbiot6

/**
 * @brief NB IoT 6 Click context object.
 * @details Context object definition of NB IoT 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wup;              /**< Wake UP pin (falling edge). */
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t pwr;              /**< PWRKEY pin (active high). */

    // Input pins
    digital_in_t ring;              /**< Ring indicator pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ NBIOT6_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ NBIOT6_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ NBIOT6_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} nbiot6_t;

/**
 * @brief NB IoT 6 Click configuration object.
 * @details Configuration object definition of NB IoT 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t wup;                 /**< Wake UP pin (falling edge). */
    pin_name_t rst;                 /**< Reset pin (active high). */
    pin_name_t pwr;                 /**< PWRKEY pin (active high). */
    pin_name_t ring;                /**< Ring indicator pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} nbiot6_cfg_t;

/**
 * @brief NB IoT 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NBIOT6_OK = 0,
    NBIOT6_ERROR = -1,
    NBIOT6_ERROR_TIMEOUT = -2,
    NBIOT6_ERROR_CMD = -3

} nbiot6_return_value_t;

/*!
 * @addtogroup nbiot6 NB IoT 6 Click Driver
 * @brief API for configuring and manipulating NB IoT 6 Click driver.
 * @{
 */

/**
 * @brief NB IoT 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nbiot6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nbiot6_cfg_setup ( nbiot6_cfg_t *cfg );

/**
 * @brief NB IoT 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nbiot6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot6_init ( nbiot6_t *ctx, nbiot6_cfg_t *cfg );

/**
 * @brief NB IoT 6 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot6_generic_write ( nbiot6_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NB IoT 6 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot6_generic_read ( nbiot6_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NB IoT 6 set PWR pin function.
 * @details This function sets the PWR (PWRKEY) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot6_set_pwr_pin ( nbiot6_t *ctx, uint8_t state );

/**
 * @brief NB IoT 6 set RST pin function.
 * @details This function sets the reset (RST) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot6_set_rst_pin ( nbiot6_t *ctx, uint8_t state );

/**
 * @brief NB IoT 6 set WUP pin function.
 * @details This function sets the wake up (WUP) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot6_set_wup_pin ( nbiot6_t *ctx, uint8_t state );

/**
 * @brief NB IoT 6 get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nbiot6_get_ring_pin ( nbiot6_t *ctx );

/**
 * @brief NB IoT 6 set power state function.
 * @details This function sets a desired power state by toggling PWR, RST, and WUP pins with a specific time frame.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON,
 *                    @li @c 2 - Reset.
 *                    @li @c 3 - Wake-up.
 * @return None.
 * @note None.
 */
void nbiot6_set_power_state ( nbiot6_t *ctx, uint8_t state );

/**
 * @brief NB IoT 6 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void nbiot6_cmd_run ( nbiot6_t *ctx, uint8_t *cmd );

/**
 * @brief NB IoT 6 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void nbiot6_cmd_set ( nbiot6_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief NB IoT 6 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void nbiot6_cmd_get ( nbiot6_t *ctx, uint8_t *cmd );

/**
 * @brief NB IoT 6 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void nbiot6_cmd_help ( nbiot6_t *ctx, uint8_t *cmd );

/**
 * @brief NB IoT 6 set sim card APN function.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void nbiot6_set_sim_apn ( nbiot6_t *ctx, uint8_t *sim_apn );

/**
 * @brief NB IoT 6 send SMS in text mode function.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void nbiot6_send_sms_text ( nbiot6_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief NB IoT 6 send SMS in PDU mode function.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot6_send_sms_pdu ( nbiot6_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // NBIOT6_H

/*! @} */ // nbiot6

// ------------------------------------------------------------------------ END
