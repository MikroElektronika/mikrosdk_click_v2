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
 * @file c4glte3na.h
 * @brief This file contains API for 4G LTE 3 NA Click Driver.
 */

#ifndef C4GLTE3NA_H
#define C4GLTE3NA_H

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
 * @addtogroup c4glte3na 4G LTE 3 NA Click Driver
 * @brief API for configuring and manipulating 4G LTE 3 NA Click driver.
 * @{
 */

/**
 * @defgroup c4glte3na_cmd 4G LTE 3 NA Device Settings
 * @brief Settings for registers of 4G LTE 3 NA Click driver.
 */

/**
 * @addtogroup c4glte3na_cmd
 * @{
 */

/**
 * @brief 4G LTE 3 NA control commands.
 * @details Specified setting for control commands of 4G LTE 3 NA Click driver.
 */
#define C4GLTE3NA_CMD_AT                              "AT"
#define C4GLTE3NA_CMD_GET_MODEL_ID                    "AT+CGMM"
#define C4GLTE3NA_CMD_GET_SW_VERSION                  "AT+CGMR"
#define C4GLTE3NA_CMD_GET_SERIAL_NUM                  "AT+CGSN"
#define C4GLTE3NA_CMD_FACTORY_RESET                   "AT&F"
#define C4GLTE3NA_CMD_SET_MODULE_FUNCTIONALITY        "AT+CFUN"
#define C4GLTE3NA_CMD_EPS_NETWORK_REGISTRATION        "AT+CEREG"
#define C4GLTE3NA_CMD_SIGNAL_QUALITY_REPORT           "AT+CSQ"
#define C4GLTE3NA_CMD_OPERATOR_SELECTION              "AT+COPS"
#define C4GLTE3NA_CMD_SEND_SMS                        "AT+CMGS"
#define C4GLTE3NA_CMD_SELECT_SMS_FORMAT               "AT+CMGF"
#define C4GLTE3NA_CMD_DEFINE_PDP_CONTEXT              "AT+CGDCONT"
#define C4GLTE3NA_CMD_SHOW_PDP_ADDRESS                "AT+CGPADDR"
#define C4GLTE3NA_CMD_ACTIVATE_PDP_CONTEXT            "AT+CGACT"
#define C4GLTE3NA_CMD_CREATE_SOCKET                   "AT+USOCR"
#define C4GLTE3NA_CMD_CLOSE_SOCKET                    "AT+USOCL"
#define C4GLTE3NA_CMD_CONNECT_SOCKET                  "AT+USOCO"
#define C4GLTE3NA_CMD_WRITE_SOCKET_DATA               "AT+USOWR"
#define C4GLTE3NA_CMD_READ_SOCKET_DATA                "AT+USORD"
#define C4GLTE3NA_CMD_GPIO_CONFIG                     "AT+UGPIOC"

/**
 * @brief 4G LTE 3 NA device response for AT commands.
 * @details Device response after commands.
 */
#define C4GLTE3NA_RSP_OK                              "OK"
#define C4GLTE3NA_RSP_ERROR                           "ERROR"

/**
 * @brief 4G LTE 3 NA device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define C4GLTE3NA_URC_CREATE_SOCKET                   "+USOCR: "
#define C4GLTE3NA_URC_RECEIVED_DATA                   "+UUSORD: "

/**
 * @brief 4G LTE 3 NA power state settings.
 * @details Specified power state settings of 4G LTE 3 NA Click driver.
 */
#define C4GLTE3NA_POWER_STATE_OFF                     0
#define C4GLTE3NA_POWER_STATE_ON                      1
#define C4GLTE3NA_POWER_STATE_RESET                   2

/**
 * @brief 4G LTE 3 NA driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define C4GLTE3NA_TX_DRV_BUFFER_SIZE                  256
#define C4GLTE3NA_RX_DRV_BUFFER_SIZE                  256

/*! @} */ // c4glte3na_cmd

/**
 * @defgroup c4glte3na_map 4G LTE 3 NA MikroBUS Map
 * @brief MikroBUS pin mapping of 4G LTE 3 NA Click driver.
 */

/**
 * @addtogroup c4glte3na_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 4G LTE 3 NA Click to the selected MikroBUS.
 */
#define C4GLTE3NA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // c4glte3na_map
/*! @} */ // c4glte3na

/**
 * @brief 4G LTE 3 NA Click context object.
 * @details Context object definition of 4G LTE 3 NA Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;              /**< Power pin. */
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t rts;              /**< UART ready to send pin. */

    // Input pins
    digital_in_t ring;              /**< Ring indicator pin. */
    digital_in_t cts;               /**< UART clear to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ C4GLTE3NA_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ C4GLTE3NA_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ C4GLTE3NA_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} c4glte3na_t;

/**
 * @brief 4G LTE 3 NA Click configuration object.
 * @details Configuration object definition of 4G LTE 3 NA Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t pwr;                 /**< Power pin. */
    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t rts;                 /**< UART ready to send pin. */
    pin_name_t ring;                /**< Ring indicator pin. */
    pin_name_t cts;                 /**< UART clear to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} c4glte3na_cfg_t;

/**
 * @brief 4G LTE 3 NA Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C4GLTE3NA_OK = 0,
    C4GLTE3NA_ERROR = -1,
    C4GLTE3NA_ERROR_TIMEOUT = -2,
    C4GLTE3NA_ERROR_CMD = -3,
    C4GLTE3NA_ERROR_UNKNOWN = -4

} c4glte3na_return_value_t;

/*!
 * @addtogroup c4glte3na 4G LTE 3 NA Click Driver
 * @brief API for configuring and manipulating 4G LTE 3 NA Click driver.
 * @{
 */

/**
 * @brief 4G LTE 3 NA configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c4glte3na_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c4glte3na_cfg_setup ( c4glte3na_cfg_t *cfg );

/**
 * @brief 4G LTE 3 NA initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c4glte3na_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glte3na_init ( c4glte3na_t *ctx, c4glte3na_cfg_t *cfg );

/**
 * @brief 4G LTE 3 NA data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glte3na_generic_write ( c4glte3na_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief 4G LTE 3 NA data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glte3na_generic_read ( c4glte3na_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief 4G LTE 3 NA set PWR pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c4glte3na_set_pwr_pin ( c4glte3na_t *ctx, uint8_t state );

/**
 * @brief 4G LTE 3 NA set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c4glte3na_set_rst_pin ( c4glte3na_t *ctx, uint8_t state );

/**
 * @brief 4G LTE 3 NA set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void c4glte3na_set_rts_pin ( c4glte3na_t *ctx, uint8_t state );

/**
 * @brief 4G LTE 3 NA get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c4glte3na_get_ring_pin ( c4glte3na_t *ctx );

/**
 * @brief 4G LTE 3 NA get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c4glte3na_get_cts_pin ( c4glte3na_t *ctx );

/**
 * @brief 4G LTE 3 NA set power state function.
 * @details This function sets a desired power state by toggling PWR and RST pins with a specific timing.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON,
 *                    @li @c 2 - Reset.
 * @return None.
 * @note None.
 */
void c4glte3na_set_power_state ( c4glte3na_t *ctx, uint8_t state );

/**
 * @brief 4G LTE 3 NA cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void c4glte3na_cmd_run ( c4glte3na_t *ctx, uint8_t *cmd );

/**
 * @brief 4G LTE 3 NA cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void c4glte3na_cmd_set ( c4glte3na_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief 4G LTE 3 NA cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void c4glte3na_cmd_get ( c4glte3na_t *ctx, uint8_t *cmd );

/**
 * @brief 4G LTE 3 NA cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void c4glte3na_cmd_help ( c4glte3na_t *ctx, uint8_t *cmd );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void c4glte3na_set_sim_apn ( c4glte3na_t *ctx, uint8_t *sim_apn );

/**
 * @brief 4G LTE 3 NA send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void c4glte3na_send_sms_text ( c4glte3na_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief 4G LTE 3 NA send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #c4glte3na_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4glte3na_send_sms_pdu ( c4glte3na_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // C4GLTE3NA_H

/*! @} */ // c4glte3na

// ------------------------------------------------------------------------ END
