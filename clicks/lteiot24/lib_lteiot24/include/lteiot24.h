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
 * @file lteiot24.h
 * @brief This file contains API for LTE IoT 24 Click Driver.
 */

#ifndef LTEIOT24_H
#define LTEIOT24_H

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
 * @addtogroup lteiot24 LTE IoT 24 Click Driver
 * @brief API for configuring and manipulating LTE IoT 24 Click driver.
 * @{
 */

/**
 * @defgroup lteiot24_cmd LTE IoT 24 Device Settings
 * @brief Settings of LTE IoT 24 Click driver.
 */

/**
 * @addtogroup lteiot24_cmd
 * @{
 */

/**
 * @brief LTE IoT 24 control commands.
 * @details Specified setting for control commands of LTE IoT 24 Click driver.
 */
#define LTEIOT24_CMD_AT                                 "AT"
#define LTEIOT24_CMD_GET_MODEL_ID                       "AT+CGMM"
#define LTEIOT24_CMD_GET_SW_VERSION                     "AT+CGMR"
#define LTEIOT24_CMD_GET_SERIAL_NUM                     "AT+CGSN"
#define LTEIOT24_CMD_FACTORY_RESET                      "AT&F"
#define LTEIOT24_CMD_SW_RESET                           "ATZ"
#define LTEIOT24_CMD_SET_PHONE_FUNCTIONALITY            "AT+CFUN"
#define LTEIOT24_CMD_NETWORK_REGISTRATION               "AT+CREG"
#define LTEIOT24_CMD_SIGNAL_QUALITY_REPORT              "AT+CSQ"
#define LTEIOT24_CMD_OPERATOR_SELECTION                 "AT+COPS"
#define LTEIOT24_CMD_SEND_SMS                           "AT+CMGS"
#define LTEIOT24_CMD_SELECT_SMS_FORMAT                  "AT+CMGF"
#define LTEIOT24_CMD_DEFINE_PDP_CONTEXT                 "AT+CGDCONT"
#define LTEIOT24_CMD_SHOW_PDP_ADDRESS                   "AT+CGPADDR"
#define LTEIOT24_CMD_ACTIVATE_PDP_CONTEXT               "AT#SGACT"
#define LTEIOT24_CMD_OPEN_SOCKET                        "AT#SD"
#define LTEIOT24_CMD_SEND_DATA                          "AT#SSENDEXT"
#define LTEIOT24_CMD_RECEIVE_DATA                       "AT#SRECV"
#define LTEIOT24_CMD_CLOSE_SOCKET                       "AT#SH"
#define LTEIOT24_CMD_GNSS_SET_POWER                     "AT$GPSP"
#define LTEIOT24_CMD_GNSS_SET_NMEA_OUTPUT               "AT$GNSSNMEA"

/**
 * @brief LTE IoT 24 response buffer commands.
 * @details Specified response buffer commands of LTE IoT 24 Click driver.
 */
#define LTEIOT24_RSP_START                              "$"
#define LTEIOT24_RSP_DELIMITER                          ","
#define LTEIOT24_RSP_END                                "\r\n"
#define LTEIOT24_RSP_GGA                                "GGA"

/**
 * @brief LTE IoT 24 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT24_RSP_OK                                 "OK"
#define LTEIOT24_RSP_ERROR                              "ERROR"

/**
 * @brief LTE IoT 24 device response time for AT commands.
 * @details Device response time after commands.
 */
#define LTEIOT24_MAX_RSP_TIME_DEFAULT                   300ul
#define LTEIOT24_MAX_RSP_TIME_COPS                      180000ul
#define LTEIOT24_MAX_RSP_TIME_SGACT                     150000ul
#define LTEIOT24_MAX_RSP_TIME_CFUN                      15000ul
#define LTEIOT24_MAX_RSP_TIME_CMGS                      120000ul
#define LTEIOT24_MAX_RSP_TIME_SH                        10000ul
#define LTEIOT24_MAX_RSP_TIME_SD                        10000ul
#define LTEIOT24_MAX_RSP_TIME_URC                       30000ul
#define LTEIOT24_MAX_RSP_TIME_GNSS                      5000ul

/**
 * @brief LTE IoT 24 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define LTEIOT24_URC_RECEIVED_DATA                      "SRING: "
#define LTEIOT24_URC_NETWORK_REGISTERED                 "+CREG: 2,1"
#define LTEIOT24_URC_SMS_FORMAT_PDU                     "+CMGF: 0"
#define LTEIOT24_URC_SMS_FORMAT_TXT                     "+CMGF: 1"

/**
 * @brief LTE IoT 24 power state settings.
 * @details Specified power state settings of LTE IoT 24 Click driver.
 */
#define LTEIOT24_POWER_STATE_OFF                        0
#define LTEIOT24_POWER_STATE_ON                         1

/**
 * @brief LTE IoT 24 GGA command elements.
 * @details Specified GGA command elements of LTE IoT 24 Click driver.
 */
#define LTEIOT24_GGA_ELEMENT_SIZE                       15
#define LTEIOT24_GGA_TIME                               1
#define LTEIOT24_GGA_LATITUDE                           2
#define LTEIOT24_GGA_LATITUDE_SIDE                      3
#define LTEIOT24_GGA_LONGITUDE                          4
#define LTEIOT24_GGA_LONGITUDE_SIDE                     5
#define LTEIOT24_GGA_QUALITY_INDICATOR                  6
#define LTEIOT24_GGA_NUMBER_OF_SATELLITES               7
#define LTEIOT24_GGA_H_DILUTION_OF_POS                  8
#define LTEIOT24_GGA_ALTITUDE                           9
#define LTEIOT24_GGA_ALTITUDE_UNIT                      10
#define LTEIOT24_GGA_GEOIDAL_SEPARATION                 11
#define LTEIOT24_GGA_GEOIDAL_SEPARATION_UNIT            12
#define LTEIOT24_GGA_TIME_SINCE_LAST_DGPS               13
#define LTEIOT24_GGA_DGPS_REFERENCE_STATION_ID          14

/**
 * @brief LTE IoT 24 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTEIOT24_TX_DRV_BUFFER_SIZE                     256
#define LTEIOT24_RX_DRV_BUFFER_SIZE                     256

/*! @} */ // lteiot24_cmd

/**
 * @defgroup lteiot24_map LTE IoT 24 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 24 Click driver.
 */

/**
 * @addtogroup lteiot24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 24 Click to the selected MikroBUS.
 */
#define LTEIOT24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot24_map
/*! @} */ // lteiot24

/**
 * @brief LTE IoT 24 Click context object.
 * @details Context object definition of LTE IoT 24 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;               /**< Power ON/OFF pin (active low). */
    digital_out_t cs;               /**< SPI Chip select pin. */
    digital_out_t rts;              /**< UART Request to send pin. */

    // Input pins
    digital_in_t cts;               /**< UART Clear to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LTEIOT24_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LTEIOT24_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LTEIOT24_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} lteiot24_t;

/**
 * @brief LTE IoT 24 Click configuration object.
 * @details Configuration object definition of LTE IoT 24 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t on;                  /**< Power ON/OFF pin (active low). */
    pin_name_t cs;                  /**< SPI Chip select pin. */
    pin_name_t rts;                 /**< UART Request to send pin. */
    pin_name_t cts;                 /**< UART Clear to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} lteiot24_cfg_t;

/**
 * @brief LTE IoT 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTEIOT24_OK = 0,
    LTEIOT24_ERROR = -1,
    LTEIOT24_ERROR_TIMEOUT = -2,
    LTEIOT24_ERROR_CMD = -3

} lteiot24_return_value_t;

/*!
 * @addtogroup lteiot24 LTE IoT 24 Click Driver
 * @brief API for configuring and manipulating LTE IoT 24 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot24_cfg_setup ( lteiot24_cfg_t *cfg );

/**
 * @brief LTE IoT 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot24_init ( lteiot24_t *ctx, lteiot24_cfg_t *cfg );

/**
 * @brief LTE IoT 24 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot24_generic_write ( lteiot24_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE IoT 24 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot24_generic_read ( lteiot24_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE IoT 24 set ON pin function.
 * @details This function sets the ON pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot24_set_on_pin ( lteiot24_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 24 set CS pin function.
 * @details This function sets the CS pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot24_set_cs_pin ( lteiot24_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 24 set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot24_set_rts_pin ( lteiot24_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 24 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot24_get_cts_pin ( lteiot24_t *ctx );

/**
 * @brief LTE IoT 24 set power state function.
 * @details This function sets a desired power state by toggling ON pin.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON.
 * @return None.
 * @note None.
 */
void lteiot24_set_power_state ( lteiot24_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 24 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot24_cmd_run ( lteiot24_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 24 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void lteiot24_cmd_set ( lteiot24_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LTE IoT 24 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot24_cmd_get ( lteiot24_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 24 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot24_cmd_help ( lteiot24_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 24 set sim card APN function.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void lteiot24_set_sim_apn ( lteiot24_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE IoT 24 send SMS in text mode function.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void lteiot24_send_sms_text ( lteiot24_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 24 send SMS in PDU mode function.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot24_send_sms_pdu ( lteiot24_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 24 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot24_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT24_H

/*! @} */ // lteiot24

// ------------------------------------------------------------------------ END
