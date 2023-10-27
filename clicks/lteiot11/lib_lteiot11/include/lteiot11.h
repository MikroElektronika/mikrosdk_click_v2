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
 * @file lteiot11.h
 * @brief This file contains API for LTE IoT 11 Click Driver.
 */

#ifndef LTEIOT11_H
#define LTEIOT11_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup lteiot11 LTE IoT 11 Click Driver
 * @brief API for configuring and manipulating LTE IoT 11 Click driver.
 * @{
 */

/**
 * @defgroup lteiot11_cmd LTE IoT 11 Device Settings
 * @brief Settings for registers of LTE IoT 11 Click driver.
 */

/**
 * @addtogroup lteiot11_cmd
 * @{
 */

/**
 * @brief LTE IoT 11 control commands.
 * @details Specified setting for control commands of LTE IoT 11 Click driver.
 */
#define LTEIOT11_CMD_AT                             "AT"
#define LTEIOT11_CMD_ATI                            "ATI"
#define LTEIOT11_CMD_CFUN                           "AT+CFUN"
#define LTEIOT11_CMD_CREG                           "AT+CREG"
#define LTEIOT11_CMD_CGDCONT                        "AT+CGDCONT"
#define LTEIOT11_CMD_CESQ                           "AT+CESQ"
#define LTEIOT11_CMD_COPS                           "AT+COPS"
#define LTEIOT11_CMD_CMGS                           "AT+CMGS"
#define LTEIOT11_CMD_CMGF                           "AT+CMGF"
#define LTEIOT11_CMD_CGPADDR                        "AT+CGPADDR"
#define LTEIOT11_CMD_SICA                           "AT^SICA"
#define LTEIOT11_CMD_SISS                           "AT^SISS"
#define LTEIOT11_CMD_SISO                           "AT^SISO"
#define LTEIOT11_CMD_SISW                           "AT^SISW"
#define LTEIOT11_CMD_SISR                           "AT^SISR"
#define LTEIOT11_CMD_SISC                           "AT^SISC"
#define LTEIOT11_CMD_SGPSC                          "AT^SGPSC"

/**
 * @brief LTE IoT 11 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT11_RSP_OK                             "OK"
#define LTEIOT11_RSP_ERROR                          "ERROR"
#define LTEIOT11_RSP_SYSSTART                       "^SYSSTART"

/**
 * @brief LTE IoT 11 response buffer commands.
 * @details Specified response buffer commands of LTE IoT 11 Click driver.
 */
#define LTEIOT11_RSP_START                          "$"
#define LTEIOT11_RSP_DELIMITER                      ","
#define LTEIOT11_RSP_END                            "\r\n"
#define LTEIOT11_RSP_GGA                            "GGA"

/**
 * @brief LTE IoT 11 GGA command elements.
 * @details Specified GGA command elements of LTE IoT 11 Click driver.
 */
#define LTEIOT11_GGA_ELEMENT_SIZE                   15
#define LTEIOT11_GGA_TIME                           1
#define LTEIOT11_GGA_LATITUDE                       2
#define LTEIOT11_GGA_LATITUDE_SIDE                  3
#define LTEIOT11_GGA_LONGITUDE                      4
#define LTEIOT11_GGA_LONGITUDE_SIDE                 5
#define LTEIOT11_GGA_QUALITY_INDICATOR              6
#define LTEIOT11_GGA_NUMBER_OF_SATELLITES           7
#define LTEIOT11_GGA_H_DILUTION_OF_POS              8
#define LTEIOT11_GGA_ALTITUDE                       9
#define LTEIOT11_GGA_ALTITUDE_UNIT                  10
#define LTEIOT11_GGA_GEOIDAL_SEPARATION             11
#define LTEIOT11_GGA_GEOIDAL_SEPARATION_UNIT        12
#define LTEIOT11_GGA_TIME_SINCE_LAST_DGPS           13
#define LTEIOT11_GGA_DGPS_REFERENCE_STATION_ID      14

/**
 * @brief LTE IoT 11 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTEIOT11_RX_DRV_BUFFER_SIZE                 256
#define LTEIOT11_TX_DRV_BUFFER_SIZE                 256

/*! @} */ // lteiot11_cmd

/**
 * @defgroup lteiot11_map LTE IoT 11 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 11 Click driver.
 */

/**
 * @addtogroup lteiot11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 11 Click to the selected MikroBUS.
 */
#define LTEIOT11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.smi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot11_map
/*! @} */ // lteiot11

/**
 * @brief LTE IoT 11 Click context object.
 * @details Context object definition of LTE IoT 11 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;           /**< Ignition pin. */
    digital_out_t cs;           /**< SPI Chip select. */
    digital_out_t rts;          /**< UART ready to send pin. */

    // Input pins
    digital_in_t smi;           /**< Suspend mode indicator pin. */
    digital_in_t cts;           /**< UART clear to send pin. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LTEIOT11_RX_DRV_BUFFER_SIZE ];      /**< Buffer size. */
    uint8_t uart_tx_buffer[ LTEIOT11_TX_DRV_BUFFER_SIZE ];      /**< Buffer size. */

} lteiot11_t;

/**
 * @brief LTE IoT 11 Click configuration object.
 * @details Configuration object definition of LTE IoT 11 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t on;              /**< Ignition pin. */
    pin_name_t cs;              /**< SPI Chip select. */
    pin_name_t cts;             /**< UART clear to send pin. */
    pin_name_t smi;             /**< Suspend mode indicator pin. */
    pin_name_t rts;             /**< UART ready to send pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} lteiot11_cfg_t;

/**
 * @brief LTE IoT 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTEIOT11_OK = 0,
    LTEIOT11_ERROR = -1,
    LTEIOT11_ERROR_TIMEOUT = -2,
    LTEIOT11_ERROR_CMD = -3,
    LTEIOT11_ERROR_UNKNOWN = -4

} lteiot11_return_value_t;

/*!
 * @addtogroup lteiot11 LTE IoT 11 Click Driver
 * @brief API for configuring and manipulating LTE IoT 11 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot11_cfg_setup ( lteiot11_cfg_t *cfg );

/**
 * @brief LTE IoT 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot11_init ( lteiot11_t *ctx, lteiot11_cfg_t *cfg );

/**
 * @brief LTE IoT 11 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot11_generic_write ( lteiot11_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE IoT 11 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot11_generic_read ( lteiot11_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE IoT 11 set on pin function.
 * @details This function sets the ON pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot11_set_on_pin ( lteiot11_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 11 set rts pin function.
 * @details This function sets the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot11_set_rts_pin ( lteiot11_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 11 set cs pin function.
 * @details This function sets the CS pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot11_set_cs_pin ( lteiot11_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 11 get smi pin function.
 * @details This function returns the suspend mode indication (SMI) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot11_get_smi_pin ( lteiot11_t *ctx );

/**
 * @brief LTE IoT 11 get cts pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot11_get_cts_pin ( lteiot11_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void lteiot11_send_cmd ( lteiot11_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void lteiot11_send_cmd_with_par ( lteiot11_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void lteiot11_send_cmd_check ( lteiot11_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void lteiot11_send_cmd_par_check ( lteiot11_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void lteiot11_set_sim_apn ( lteiot11_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE IoT 11 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void lteiot11_send_sms_text ( lteiot11_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 11 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #lteiot11_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot11_send_sms_pdu ( lteiot11_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 11 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot11_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT11_H

/*! @} */ // lteiot11

// ------------------------------------------------------------------------ END
