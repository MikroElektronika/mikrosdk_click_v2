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
 * @file lteiot7.h
 * @brief This file contains API for LTE IoT 7 Click Driver.
 */

#ifndef LTEIOT7_H
#define LTEIOT7_H

#ifdef __cplusplus
extern "C"{
#endif

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
 * @addtogroup lteiot7 LTE IoT 7 Click Driver
 * @brief API for configuring and manipulating LTE IoT 7 Click driver.
 * @{
 */

/**
 * @defgroup lteiot7_cmd LTE IoT 7 Device Settings
 * @brief Settings for registers of LTE IoT 7 Click driver.
 */

/**
 * @addtogroup lteiot7_cmd
 * @{
 */

/**
 * @brief LTE IoT 7 control commands.
 * @details Specified setting for control commands of LTE IoT 7 Click driver.
 */
#define LTEIOT7_CMD_AT                              "AT"
#define LTEIOT7_CMD_ATI                             "ATI"
#define LTEIOT7_CMD_CGMR                            "AT+CGMR"
#define LTEIOT7_CMD_CFUN                            "AT+CFUN"
#define LTEIOT7_CMD_CREG                            "AT+CREG"
#define LTEIOT7_CMD_CGREG                           "AT+CGREG"
#define LTEIOT7_CMD_CGDCONT                         "AT+CGDCONT"
#define LTEIOT7_CMD_CIMI                            "AT+CIMI"
#define LTEIOT7_CMD_CMEE                            "AT+CMEE"
#define LTEIOT7_CMD_CGATT                           "AT+CGATT"
#define LTEIOT7_CMD_CSQ                             "AT+CSQ"
#define LTEIOT7_CMD_COPS                            "AT+COPS"
#define LTEIOT7_CMD_CMGS                            "AT+CMGS"
#define LTEIOT7_CMD_CMGF                            "AT+CMGF"
#define LTEIOT7_CMD_CGACT                           "AT+CGACT"
#define LTEIOT7_CMD_USOCR                           "AT+USOCR"
#define LTEIOT7_CMD_USOCO                           "AT+USOCO"
#define LTEIOT7_CMD_USOWR                           "AT+USOWR"
#define LTEIOT7_CMD_USORD                           "AT+USORD"
#define LTEIOT7_CMD_USORF                           "AT+USORF"
#define LTEIOT7_CMD_USOCL                           "AT+USOCL"
#define LTEIOT7_CMD_UGPS                            "AT+UGPS"
#define LTEIOT7_CMD_UGGGA                           "AT+UGGGA"

/**
 * @brief LTE IoT 7 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT7_RSP_OK                              "OK"
#define LTEIOT7_RSP_ERROR                           "ERROR"

/**
 * @brief LTE IoT 7 power state settings.
 * @details Specified power state settings of LTE IoT 7 Click driver.
 */
#define LTEIOT7_POWER_STATE_SWITCH                  0
#define LTEIOT7_POWER_STATE_ON                      1
#define LTEIOT7_POWER_STATE_REBOOT                  2

/**
 * @brief LTE IoT 7 response buffer commands.
 * @details Specified response buffer commands of LTE IoT 7 Click driver.
 */
#define LTEIOT7_RSP_START                           "$"
#define LTEIOT7_RSP_DELIMITER                       ","
#define LTEIOT7_RSP_GPGGA                           "$GPGGA"

/**
 * @brief LTE IoT 7 GPGGA command elements.
 * @details Specified GPGGA command elements of LTE IoT 7 Click driver.
 */
#define LTEIOT7_GPGGA_ELEMENT_SIZE                  15
#define LTEIOT7_GPGGA_TIME                          1
#define LTEIOT7_GPGGA_LATITUDE                      2
#define LTEIOT7_GPGGA_LATITUDE_SIDE                 3
#define LTEIOT7_GPGGA_LONGITUDE                     4
#define LTEIOT7_GPGGA_LONGITUDE_SIDE                5
#define LTEIOT7_GPGGA_QUALITY_INDICATOR             6
#define LTEIOT7_GPGGA_NUMBER_OF_SATELLITES          7
#define LTEIOT7_GPGGA_H_DILUTION_OF_POS             8
#define LTEIOT7_GPGGA_ALTITUDE                      9
#define LTEIOT7_GPGGA_ALTITUDE_UNIT                 10
#define LTEIOT7_GPGGA_GEOIDAL_SEPARATION            11
#define LTEIOT7_GPGGA_GEOIDAL_SEPARATION_UNIT       12
#define LTEIOT7_GPGGA_TIME_SINCE_LAST_DGPS          13
#define LTEIOT7_GPGGA_DGPS_REFERENCE_STATION_ID     14

/**
 * @brief LTE IoT 7 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                             256

/*! @} */ // lteiot7_cmd

/**
 * @defgroup lteiot7_map LTE IoT 7 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 7 Click driver.
 */

/**
 * @addtogroup lteiot7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 7 Click to the selected MikroBUS.
 */
#define LTEIOT7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ein = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ri = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot7_map
/*! @} */ // lteiot7

/**
 * @brief LTE IoT 7 Click context object.
 * @details Context object definition of LTE IoT 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;          /**< PWR control pin. */
    digital_out_t ein;          /**< EXTINT (GNSS external interrupt connected to u-blox GNSS chip) pin. */
    digital_out_t rts;          /**< UART ready to send pin. */

    // Input pins
    digital_in_t ri;            /**< UART ring indicator pin. */
    digital_in_t cts;           /**< UART clear to send pin. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */

} lteiot7_t;

/**
 * @brief LTE IoT 7 Click configuration object.
 * @details Configuration object definition of LTE IoT 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t pwr;             /**< PWR control pin. */
    pin_name_t ein;             /**< EXTINT (GNSS external interrupt connected to u-blox GNSS chip) pin. */
    pin_name_t rts;             /**< UART ready to send pin. */
    pin_name_t ri;              /**< UART ring indicator pin. */
    pin_name_t cts;             /**< UART clear to send pin. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} lteiot7_cfg_t;

/**
 * @brief LTE IoT 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTEIOT7_OK = 0,
    LTEIOT7_ERROR = -1,
    LTEIOT7_ERROR_TIMEOUT = -2,
    LTEIOT7_ERROR_CMD = -3,
    LTEIOT7_ERROR_UNKNOWN = -4

} lteiot7_return_value_t;

/*!
 * @addtogroup lteiot7 LTE IoT 7 Click Driver
 * @brief API for configuring and manipulating LTE IoT 7 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot7_cfg_setup ( lteiot7_cfg_t *cfg );

/**
 * @brief LTE IoT 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot7_init ( lteiot7_t *ctx, lteiot7_cfg_t *cfg );

/**
 * @brief LTE IoT 7 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot7_generic_write ( lteiot7_t *ctx, char *data_in, uint16_t len );

/**
 * @brief LTE IoT 7 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot7_generic_read ( lteiot7_t *ctx, char *data_out, uint16_t len );

/**
 * @brief LTE IoT 7 set PWR pin function.
 * @details This function sets the PWR pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot7_set_pwr_pin ( lteiot7_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 7 set EIN pin function.
 * @details This function sets the EXTINT pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot7_set_ein_pin ( lteiot7_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 7 set RTS pin function.
 * @details This function sets the ready to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot7_set_rts_pin ( lteiot7_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 7 get RI pin function.
 * @details This function returns the ring indication (RI) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot7_get_ri_pin ( lteiot7_t *ctx );

/**
 * @brief LTE IoT 7 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot7_get_cts_pin ( lteiot7_t *ctx );

/**
 * @brief LTE IoT 7 set power state function.
 * @details This function sets a desired power state by toggling PWR pin with a specific time for high state.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Switch power state,
 *                    @li @c 1 - Power ON.
 *                    @li @c 2 - Reboot.
 * @return None.
 * @note None.
 */
void lteiot7_set_power_state ( lteiot7_t *ctx, uint8_t state );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void lteiot7_send_cmd ( lteiot7_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void lteiot7_send_cmd_with_parameter ( lteiot7_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void lteiot7_send_cmd_check ( lteiot7_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void lteiot7_send_cmd_parameter_check ( lteiot7_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void lteiot7_set_sim_apn ( lteiot7_t *ctx, char *sim_apn );

/**
 * @brief LTE IoT 7 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void lteiot7_send_sms_text ( lteiot7_t *ctx, char *phone_number, char *sms_text );

/**
 * @brief LTE IoT 7 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #lteiot7_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot7_send_sms_pdu ( lteiot7_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

/**
 * @brief LTE IoT 7 parse GPGGA function.
 * @details This function parses the GPGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gpgga_element : GPGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot7_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT7_H

/*! @} */ // lteiot7

// ------------------------------------------------------------------------ END
