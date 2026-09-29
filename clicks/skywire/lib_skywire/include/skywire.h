/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file skywire.h
 * @brief This file contains API for Skywire Click Driver.
 */

#ifndef SKYWIRE_H
#define SKYWIRE_H

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
 * @addtogroup skywire Skywire Click Driver
 * @brief API for configuring and manipulating Skywire Click driver.
 * @{
 */

/**
 * @defgroup skywire_cmd Skywire Commands List.
 * @brief List of commands of Skywire Click driver.
 */

/**
 * @addtogroup skywire_cmd
 * @{
 */

/**
 * @brief Skywire command list.
 * @details Specified command list of Skywire Click driver.
 */
#define SKYWIRE_CMD_AT                      "AT"
#define SKYWIRE_CMD_GET_MANUFACTURER_ID     "AT+CGMI"
#define SKYWIRE_CMD_GET_MODEL_ID            "AT+CGMM"
#define SKYWIRE_CMD_GET_SW_REVISION         "AT+CGMR"
#define SKYWIRE_CMD_ENTER_PIN               "AT+CPIN"
#define SKYWIRE_CMD_REPORT_ME_ERROR         "AT+CMEE"
#define SKYWIRE_CMD_GPIO_CONTROL            "AT#GPIO"
#define SKYWIRE_CMD_STAT_LED_SETTING        "AT#SLED"
#define SKYWIRE_CMD_SW_SHUTDOWN             "AT#SHDN"
#define SKYWIRE_CMD_NETWORK_REGISTRATION    "AT+CREG"
#define SKYWIRE_CMD_OPERATOR_SELECTION      "AT+COPS"
#define SKYWIRE_CMD_SIGNAL_QUALITY          "AT+CSQ"
#define SKYWIRE_CMD_MESSAGE_FORMAT          "AT+CMGF"
#define SKYWIRE_CMD_SERVICE_CENTER_ADDRESS  "AT+CSCA"
#define SKYWIRE_CMD_SEND_SMS                "AT+CMGS"
#define SKYWIRE_CMD_DIAL                    "ATD"
#define SKYWIRE_CMD_LIST_CURRENT_CALLS      "AT+CLCC"
#define SKYWIRE_CMD_HANG_UP_CALL            "AT+CHUP"
#define SKYWIRE_CMD_DIALING_MODE            "AT#DIALMODE"
#define SKYWIRE_CMD_DEFINE_PDP_CONTEXT      "AT+CGDCONT"
#define SKYWIRE_CMD_CONTEXT_ACTIVATION      "AT#SGACT"
#define SKYWIRE_CMD_SOCKET_DIAL             "AT#SD"
#define SKYWIRE_CMD_SOCKET_SEND             "AT#SSENDEXT"
#define SKYWIRE_CMD_SOCKET_RECEIVE          "AT#SRECV"
#define SKYWIRE_CMD_SOCKET_SHUTDOWN         "AT#SH"
#define SKYWIRE_CMD_GPS_POWER               "AT$GPSP"
#define SKYWIRE_CMD_GPS_ACQUIRED_POSITION   "AT$GPSACP"

/*! @} */ // skywire_cmd

/**
 * @defgroup skywire_set Skywire Device Settings
 * @brief Settings of Skywire Click driver.
 */

/**
 * @addtogroup skywire_set
 * @{
 */

/**
 * @brief Skywire device response to AT commands setting.
 * @details Specified setting for device response to AT commands of Skywire Click driver.
 */
#define SKYWIRE_RSP_OK                      "OK"
#define SKYWIRE_RSP_ERROR                   "ERROR"
#define SKYWIRE_RSP_SIM_READY               "+CPIN: READY"
#define SKYWIRE_RSP_SIM_PIN                 "+CPIN: SIM PIN"
#define SKYWIRE_RSP_NETWORK_REGISTRATION    "+CREG:"
#define SKYWIRE_RSP_SMS_PROMPT              "> "
#define SKYWIRE_RSP_SMS_SENT                "+CMGS:"
#define SKYWIRE_RSP_GPS_POWERED_UP          "$GPSP: 1"
#define SKYWIRE_RSP_DATA_PROMPT             "> "
#define SKYWIRE_RSP_GPS_POSITION            "$GPSACP:"

/**
 * @brief Skywire device response time to AT commands setting.
 * @details Specified setting for device response time to AT commands of Skywire Click driver.
 */
#define SKYWIRE_MAX_SMS_SEND                60000
#define SKYWIRE_MAX_CALL_SETUP              30000
#define SKYWIRE_MAX_CONTEXT_ACTIVATION      150000
#define SKYWIRE_MAX_SOCKET_OPEN             90000
#define SKYWIRE_MAX_SOCKET_DATA             10000
#define SKYWIRE_MAX_AT_DEFAULT              2000
#define SKYWIRE_MAX_SIM_STATUS              5000

/**
 * @brief Skywire URC setting.
 * @details Specified setting for URC of Skywire Click driver.
 */
#define SKYWIRE_URC_SOCKET_RING             "SRING:"

/**
 * @brief Skywire SMS control characters setting.
 * @details Specified setting for SMS control characters of Skywire Click driver.
 */
#define SKYWIRE_SMS_CTRL_Z                  0x1A
#define SKYWIRE_SMS_ESC                     0x1B

/**
 * @brief Skywire pin states setting.
 * @details Specified setting for pin states of Skywire Click driver.
 */
#define SKYWIRE_PIN_STATE_HIGH              0x01
#define SKYWIRE_PIN_STATE_LOW               0x00

/**
 * @brief Skywire PDP context identifier setting.
 * @details Specified setting for PDP context identifier of Skywire Click driver.
 */
#define SKYWIRE_PDP_CONTEXT_ID              "1"

/**
 * @brief Skywire command parameter buffer size setting.
 * @details Specified setting for command parameter buffer size of Skywire Click driver.
 */
#define SKYWIRE_APN_PARAM_BUFFER_SIZE       64
#define SKYWIRE_SMS_PARAM_BUFFER_SIZE       32

/**
 * @brief Skywire driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define SKYWIRE_TX_DRV_BUFFER_SIZE          100
#define SKYWIRE_RX_DRV_BUFFER_SIZE          300

/*! @} */ // skywire_set

/**
 * @defgroup skywire_map Skywire MikroBUS Map
 * @brief MikroBUS pin mapping of Skywire Click driver.
 */

/**
 * @addtogroup skywire_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Skywire Click to the selected MikroBUS.
 */
#define SKYWIRE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ad1_j = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // skywire_map
/*! @} */ // skywire

/**
 * @brief Skywire Click context object.
 * @details Context object definition of Skywire Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;                           /**< Modem power ON/OFF pin. */
    digital_out_t rst;                          /**< Modem HW reset pin. */
    digital_out_t rts;                          /**< UART request to send pin. */

    // Input pins
    digital_in_t cts;                           /**< UART clear to send pin. */
    digital_in_t ad1_j;                         /**< Modem ADC1 or RING pin. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ SKYWIRE_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ SKYWIRE_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ SKYWIRE_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} skywire_t;

/**
 * @brief Skywire Click configuration object.
 * @details Configuration object definition of Skywire Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t en;                              /**< Modem power ON/OFF pin descriptor. */
    pin_name_t rst;                             /**< Modem HW reset pin descriptor. */
    pin_name_t rts;                             /**< UART request to send pin descriptor. */
    pin_name_t cts;                             /**< UART clear to send pin descriptor. */
    pin_name_t ad1_j;                           /**< Modem ADC1 or RING pin descriptor. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} skywire_cfg_t;

/**
 * @brief Skywire Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SKYWIRE_OK = 0,
    SKYWIRE_ERROR = -1,
    SKYWIRE_ERROR_TIMEOUT = -2,
    SKYWIRE_ERROR_CMD = -3

} skywire_return_value_t;

/*!
 * @addtogroup skywire Skywire Click Driver
 * @brief API for configuring and manipulating Skywire Click driver.
 * @{
 */

/**
 * @brief Skywire configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #skywire_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void skywire_cfg_setup ( skywire_cfg_t *cfg );

/**
 * @brief Skywire initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #skywire_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t skywire_init ( skywire_t *ctx, skywire_cfg_t *cfg );

/**
 * @brief Skywire data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t skywire_generic_write ( skywire_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Skywire data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t skywire_generic_read ( skywire_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Skywire set EN pin function.
 * @details This function sets the EN pin logic state.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void skywire_set_en_pin ( skywire_t *ctx, uint8_t state );

/**
 * @brief Skywire set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void skywire_set_rst_pin ( skywire_t *ctx, uint8_t state );

/**
 * @brief Skywire set RTS pin function.
 * @details This function sets the RTS pin logic state.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void skywire_set_rts_pin ( skywire_t *ctx, uint8_t state );

/**
 * @brief Skywire get CTS pin function.
 * @details This function returns the CTS pin logic state.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return CTS pin logic state.
 * @note None.
 */
uint8_t skywire_get_cts ( skywire_t *ctx );

/**
 * @brief Skywire power on function.
 * @details This function powers on the modem by holding the ON_OFF line low for 5.1 seconds.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return Nothing.
 * @note The pulse duration is set for the NL-SW-HSPA (Telit HE910) modem.
 */
void skywire_power_on ( skywire_t *ctx );

/**
 * @brief Skywire hardware shutdown function.
 * @details This function shuts down the modem by holding the RST low for 300 milliseconds.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void skywire_hw_shutdown ( skywire_t *ctx );

/**
 * @brief Skywire cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return Nothing.
 * @note None.
 */
void skywire_cmd_run ( skywire_t *ctx, uint8_t *cmd );

/**
 * @brief Skywire cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return Nothing.
 * @note None.
 */
void skywire_cmd_set ( skywire_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief Skywire cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return Nothing.
 * @note None.
 */
void skywire_cmd_get ( skywire_t *ctx, uint8_t *cmd );

/**
 * @brief Skywire set SIM APN function.
 * @details This function sets the APN of the SIM card.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void skywire_set_sim_apn ( skywire_t *ctx, uint8_t *sim_apn );

/**
 * @brief Skywire send SMS in text mode function.
 * @details This function sends an SMS message to the selected phone number in text mode.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number in the international format.
 * @param[in] sms_text : SMS text.
 * @return Nothing.
 * @note None.
 */
void skywire_send_sms_text ( skywire_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // SKYWIRE_H

/*! @} */ // skywire

// ------------------------------------------------------------------------ END
