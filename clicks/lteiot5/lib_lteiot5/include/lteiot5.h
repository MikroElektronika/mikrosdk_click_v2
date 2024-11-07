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
 * @file lteiot5.h
 * @brief This file contains API for LTE IoT 5 Click Driver.
 */

#ifndef LTEIOT5_H
#define LTEIOT5_H

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
 * @addtogroup lteiot5 LTE IoT 5 Click Driver
 * @brief API for configuring and manipulating LTE IoT 5 Click driver.
 * @{
 */

/**
 * @defgroup lteiot5_cmd LTE IoT 5 Device Settings
 * @brief Settings for registers of LTE IoT 5 Click driver.
 */

/**
 * @addtogroup lteiot5_cmd
 * @{
 */

/**
 * @brief LTE IoT 5 control commands.
 * @details Specified setting for control commands of LTE IoT 5 Click driver.
 */
#define LTEIOT5_CMD_AT                              "AT"
#define LTEIOT5_CMD_GET_MODEL_ID                    "AT+CGMM"
#define LTEIOT5_CMD_GET_SW_VERSION                  "AT+CGMR"
#define LTEIOT5_CMD_GET_SERIAL_NUM                  "AT+CGSN"
#define LTEIOT5_CMD_FACTORY_RESET                   "AT&F"
#define LTEIOT5_CMD_SET_MODULE_FUNCTIONALITY        "AT+CFUN"
#define LTEIOT5_CMD_EPS_NETWORK_REGISTRATION        "AT+CEREG"
#define LTEIOT5_CMD_SIGNAL_QUALITY_REPORT           "AT+CSQ"
#define LTEIOT5_CMD_OPERATOR_SELECTION              "AT+COPS"
#define LTEIOT5_CMD_SEND_SMS                        "AT+CMGS"
#define LTEIOT5_CMD_SELECT_SMS_FORMAT               "AT+CMGF"
#define LTEIOT5_CMD_DEFINE_PDP_CONTEXT              "AT+CGDCONT"
#define LTEIOT5_CMD_SHOW_PDP_ADDRESS                "AT+CGPADDR"
#define LTEIOT5_CMD_ACTIVATE_PDP_CONTEXT            "AT+CGACT"
#define LTEIOT5_CMD_PSD_CONFIG                      "AT+UPSD"
#define LTEIOT5_CMD_PSD_ACTION                      "AT+UPSDA"
#define LTEIOT5_CMD_CREATE_SOCKET                   "AT+USOCR"
#define LTEIOT5_CMD_CLOSE_SOCKET                    "AT+USOCL"
#define LTEIOT5_CMD_CONNECT_SOCKET                  "AT+USOCO"
#define LTEIOT5_CMD_WRITE_SOCKET_DATA               "AT+USOWR"
#define LTEIOT5_CMD_READ_SOCKET_DATA                "AT+USORD"
#define LTEIOT5_CMD_GNSS_POWER_MANAGEMENT           "AT+UGPS"
#define LTEIOT5_CMD_GET_GNSS_FIX_DATA               "AT+UGGGA"

/**
 * @brief LTE IoT 5 device response for AT commands.
 * @details Device response after commands.
 */
#define LTEIOT5_RSP_OK                              "OK"
#define LTEIOT5_RSP_ERROR                           "ERROR"

/**
 * @brief LTE IoT 5 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define LTEIOT5_URC_CREATE_SOCKET                   "+USOCR: "
#define LTEIOT5_URC_RECEIVED_DATA                   "+UUSORD: "

/**
 * @brief LTE IoT 5 power state settings.
 * @details Specified power state settings of LTE IoT 5 Click driver.
 */
#define LTEIOT5_POWER_STATE_OFF                     0
#define LTEIOT5_POWER_STATE_ON                      1
#define LTEIOT5_POWER_STATE_RESET                   2

/**
 * @brief LTE IoT 5 response buffer commands.
 * @details Specified response buffer commands of LTE IoT 5 Click driver.
 */
#define LTEIOT5_RSP_START                           "$"
#define LTEIOT5_RSP_DELIMITER                       ","
#define LTEIOT5_RSP_END                             "\r\n"
#define LTEIOT5_RSP_GGA                             "GGA"

/**
 * @brief LTE IoT 5 GGA command elements.
 * @details Specified GGA command elements of LTE IoT 5 Click driver.
 */
#define LTEIOT5_GGA_ELEMENT_SIZE                    15
#define LTEIOT5_GGA_TIME                            1
#define LTEIOT5_GGA_LATITUDE                        2
#define LTEIOT5_GGA_LATITUDE_SIDE                   3
#define LTEIOT5_GGA_LONGITUDE                       4
#define LTEIOT5_GGA_LONGITUDE_SIDE                  5
#define LTEIOT5_GGA_QUALITY_INDICATOR               6
#define LTEIOT5_GGA_NUMBER_OF_SATELLITES            7
#define LTEIOT5_GGA_H_DILUTION_OF_POS               8
#define LTEIOT5_GGA_ALTITUDE                        9
#define LTEIOT5_GGA_ALTITUDE_UNIT                   10
#define LTEIOT5_GGA_GEOIDAL_SEPARATION              11
#define LTEIOT5_GGA_GEOIDAL_SEPARATION_UNIT         12
#define LTEIOT5_GGA_TIME_SINCE_LAST_DGPS            13
#define LTEIOT5_GGA_DGPS_REFERENCE_STATION_ID       14

/**
 * @brief LTE IoT 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LTEIOT5_TX_DRV_BUFFER_SIZE                  300
#define LTEIOT5_RX_DRV_BUFFER_SIZE                  300

/*! @} */ // lteiot5_cmd

/**
 * @defgroup lteiot5_map LTE IoT 5 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 5 Click driver.
 */

/**
 * @addtogroup lteiot5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 5 Click to the selected MikroBUS.
 */
#define LTEIOT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lteiot5_map
/*! @} */ // lteiot5

/**
 * @brief LTE IoT 5 Click context object.
 * @details Context object definition of LTE IoT 5 Click driver.
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
    uint8_t uart_rx_buffer[ LTEIOT5_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LTEIOT5_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LTEIOT5_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} lteiot5_t;

/**
 * @brief LTE IoT 5 Click configuration object.
 * @details Configuration object definition of LTE IoT 5 Click driver.
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

} lteiot5_cfg_t;

/**
 * @brief LTE IoT 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LTEIOT5_OK = 0,
    LTEIOT5_ERROR = -1,
    LTEIOT5_ERROR_TIMEOUT = -2,
    LTEIOT5_ERROR_CMD = -3

} lteiot5_return_value_t;

/*!
 * @addtogroup lteiot5 LTE IoT 5 Click Driver
 * @brief API for configuring and manipulating LTE IoT 5 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot5_cfg_setup ( lteiot5_cfg_t *cfg );

/**
 * @brief LTE IoT 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot5_init ( lteiot5_t *ctx, lteiot5_cfg_t *cfg );

/**
 * @brief LTE IoT 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot5_generic_write ( lteiot5_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LTE IoT 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot5_generic_read ( lteiot5_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LTE IoT 5 set PWR pin function.
 * @details This function sets the PWRKEY pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot5_set_pwr_pin ( lteiot5_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 5 set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot5_set_rst_pin ( lteiot5_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 5 set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lteiot5_set_rts_pin ( lteiot5_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 5 get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot5_get_ring_pin ( lteiot5_t *ctx );

/**
 * @brief LTE IoT 5 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lteiot5_get_cts_pin ( lteiot5_t *ctx );

/**
 * @brief LTE IoT 5 set power state function.
 * @details This function sets a desired power state by toggling PWR and RST pins with a specific timing.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Power OFF,
 *                    @li @c 1 - Power ON,
 *                    @li @c 2 - Reset.
 * @return None.
 * @note None.
 */
void lteiot5_set_power_state ( lteiot5_t *ctx, uint8_t state );

/**
 * @brief LTE IoT 5 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot5_cmd_run ( lteiot5_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 5 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void lteiot5_cmd_set ( lteiot5_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LTE IoT 5 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot5_cmd_get ( lteiot5_t *ctx, uint8_t *cmd );

/**
 * @brief LTE IoT 5 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lteiot5_cmd_help ( lteiot5_t *ctx, uint8_t *cmd );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void lteiot5_set_sim_apn ( lteiot5_t *ctx, uint8_t *sim_apn );

/**
 * @brief LTE IoT 5 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void lteiot5_send_sms_text ( lteiot5_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 5 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot5_send_sms_pdu ( lteiot5_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief LTE IoT 5 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot5_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT5_H

/*! @} */ // lteiot5

// ------------------------------------------------------------------------ END
