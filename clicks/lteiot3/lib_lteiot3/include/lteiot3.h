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
 * @file lteiot3.h
 * @brief This file contains API for LTE IoT 3 Click Driver.
 */

#ifndef LTEIOT3_H
#define LTEIOT3_H

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
 * @addtogroup lteiot3 LTE IoT 3 Click Driver
 * @brief API for configuring and manipulating LTE IoT 3 Click driver.
 * @{
 */

/**
 * @defgroup lteiot3_cmd LTE IoT 3 Device Settings
 * @brief Settings for registers of LTE IoT 3 Click driver.
 */

/**
 * @addtogroup lteiot3_cmd
 * @{
 */

/**
 * @brief LTE IoT 3 control commands.
 * @details Specified setting for control commands of LTE IoT 3 Click driver.
 */
#define LTEIOT3_CMD_AT                              "AT"
#define LTEIOT3_CMD_ATI                             "ATI"
#define LTEIOT3_CMD_CFUN                            "AT+CFUN"
#define LTEIOT3_CMD_CREG                            "AT+CREG"
#define LTEIOT3_CMD_CGDCONT                         "AT+CGDCONT"
#define LTEIOT3_CMD_CESQ                            "AT+CESQ"
#define LTEIOT3_CMD_COPS                            "AT+COPS"
#define LTEIOT3_CMD_CMGS                            "AT+CMGS"
#define LTEIOT3_CMD_CMGF                            "AT+CMGF"
#define LTEIOT3_CMD_CGPADDR                         "AT+CGPADDR"
#define LTEIOT3_CMD_SICA                            "AT^SICA"
#define LTEIOT3_CMD_SISS                            "AT^SISS"
#define LTEIOT3_CMD_SISO                            "AT^SISO"
#define LTEIOT3_CMD_SISW                            "AT^SISW"
#define LTEIOT3_CMD_SISR                            "AT^SISR"
#define LTEIOT3_CMD_SISC                            "AT^SISC"
#define LTEIOT3_CMD_SGPSC                           "AT^SGPSC"

/**
 * @brief LTE IoT 3 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT3_RSP_OK                              "OK"
#define LTEIOT3_RSP_ERROR                           "ERROR"
#define LTEIOT3_RSP_SYSSTART                        "^SYSSTART"

/**
 * @brief LTE IoT 3 power state settings.
 * @details Specified power state settings of LTE IoT 3 Click driver.
 */
#define LTEIOT3_POWER_STATE_SWITCH                  0
#define LTEIOT3_POWER_STATE_ON                      1
#define LTEIOT3_POWER_STATE_REBOOT                  2

/**
 * @brief LTE IoT 3 response buffer commands.
 * @details Specified response buffer commands of LTE IoT 3 Click driver.
 */
#define LTEIOT3_RSP_START                           "$"
#define LTEIOT3_RSP_DELIMITER                       ","
#define LTEIOT3_RSP_END                             "\r\n"
#define LTEIOT3_RSP_GGA                             "GGA"

/**
 * @brief LTE IoT 3 GGA command elements.
 * @details Specified GGA command elements of LTE IoT 3 Click driver.
 */
#define LTEIOT3_GGA_ELEMENT_SIZE                    15
#define LTEIOT3_GGA_TIME                            1
#define LTEIOT3_GGA_LATITUDE                        2
#define LTEIOT3_GGA_LATITUDE_SIDE                   3
#define LTEIOT3_GGA_LONGITUDE                       4
#define LTEIOT3_GGA_LONGITUDE_SIDE                  5
#define LTEIOT3_GGA_QUALITY_INDICATOR               6
#define LTEIOT3_GGA_NUMBER_OF_SATELLITES            7
#define LTEIOT3_GGA_H_DILUTION_OF_POS               8
#define LTEIOT3_GGA_ALTITUDE                        9
#define LTEIOT3_GGA_ALTITUDE_UNIT                   10
#define LTEIOT3_GGA_GEOIDAL_SEPARATION              11
#define LTEIOT3_GGA_GEOIDAL_SEPARATION_UNIT         12
#define LTEIOT3_GGA_TIME_SINCE_LAST_DGPS            13
#define LTEIOT3_GGA_DGPS_REFERENCE_STATION_ID       14

/**
 * @brief LTE IoT 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTEIOT3_RX_DRV_BUFFER_SIZE                  256
#define LTEIOT3_TX_DRV_BUFFER_SIZE                  256

/*! @} */ // lteiot3_cmd

/**
 * @defgroup lteiot3_map LTE IoT 3 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 3 Click driver.
 */

/**
 * @addtogroup lteiot3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 3 Click to the selected MikroBUS.
 */
#define LTEIOT3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.smi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot3_map
/*! @} */ // lteiot3

/**
 * @brief LTE IoT 3 Click context object.
 * @details Context object definition of LTE IoT 3 Click driver.
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
    uint8_t uart_rx_buffer[ LTEIOT3_RX_DRV_BUFFER_SIZE ];      /**< Buffer size. */
    uint8_t uart_tx_buffer[ LTEIOT3_TX_DRV_BUFFER_SIZE ];      /**< Buffer size. */

} lteiot3_t;

/**
 * @brief LTE IoT 3 Click configuration object.
 * @details Configuration object definition of LTE IoT 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t on;             /**< Ignition pin. */
    pin_name_t cs;             /**< SPI Chip select. */
    pin_name_t cts;            /**< UART clear to send pin. */
    pin_name_t smi;            /**< Suspend mode indicator pin. */
    pin_name_t rts;            /**< UART ready to send pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} lteiot3_cfg_t;

/**
 * @brief LTE IoT 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTEIOT3_OK = 0,
    LTEIOT3_ERROR = -1,
    LTEIOT3_ERROR_TIMEOUT = -2,
    LTEIOT3_ERROR_CMD = -3,
    LTEIOT3_ERROR_UNKNOWN = -4

} lteiot3_return_value_t;

/*!
 * @addtogroup lteiot3 LTE IoT 3 Click Driver
 * @brief API for configuring and manipulating LTE IoT 3 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot3_cfg_setup ( lteiot3_cfg_t *cfg );

/**
 * @brief LTE IoT 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot3_init ( lteiot3_t *ctx, lteiot3_cfg_t *cfg );

/**
 * @brief LTE IoT 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot3_generic_write ( lteiot3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE IoT 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot3_generic_read ( lteiot3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE IoT 3 set on pin function.
 * @details This function sets the ON pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot3_set_on_pin ( lteiot3_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 3 set rts pin function.
 * @details This function sets the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot3_set_rts_pin ( lteiot3_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 3 set cs pin function.
 * @details This function sets the CS pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot3_set_cs_pin ( lteiot3_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 3 get smi pin function.
 * @details This function returns the suspend mode indication (SMI) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot3_get_smi_pin ( lteiot3_t *ctx );

/**
 * @brief LTE IoT 3 get cts pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot3_get_cts_pin ( lteiot3_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void lteiot3_send_cmd ( lteiot3_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void lteiot3_send_cmd_with_parameter ( lteiot3_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void lteiot3_send_cmd_check ( lteiot3_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void lteiot3_send_cmd_parameter_check ( lteiot3_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 * @note None.
 */
void lteiot3_set_sim_apn ( lteiot3_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE IoT 3 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return Nothing.
 * @note None.
 */
void lteiot3_send_sms_text ( lteiot3_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 3 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #lteiot3_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot3_send_sms_pdu ( lteiot3_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 3 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot3_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT3_H

/*! @} */ // lteiot3

// ------------------------------------------------------------------------ END
