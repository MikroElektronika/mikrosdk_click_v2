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
 * @file gsmgnss2.h
 * @brief This file contains API for GSM/GNSS 2 Click Driver.
 */

#ifndef GSMGNSS2_H
#define GSMGNSS2_H

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
 * @addtogroup gsmgnss2 GSM/GNSS 2 Click Driver
 * @brief API for configuring and manipulating GSM/GNSS 2 Click driver.
 * @{
 */

/**
 * @defgroup gsmgnss2_cmd GSM/GNSS 2 Device Settings
 * @brief Settings for registers of GSM/GNSS 2 Click driver.
 */

/**
 * @addtogroup gsmgnss2_cmd
 * @{
 */

/**
 * @brief GSM/GNSS 2 control commands.
 * @details Specified setting for control commands of GSM/GNSS 2 Click driver.
 */
#define GSMGNSS2_CMD_AT                             "AT"
#define GSMGNSS2_CMD_ATI                            "ATI"
#define GSMGNSS2_CMD_CGMR                           "AT+CGMR"
#define GSMGNSS2_CMD_CFUN                           "AT+CFUN"
#define GSMGNSS2_CMD_CREG                           "AT+CREG"
#define GSMGNSS2_CMD_CGREG                          "AT+CGREG"
#define GSMGNSS2_CMD_CGDCONT                        "AT+CGDCONT"
#define GSMGNSS2_CMD_CIMI                           "AT+CIMI"
#define GSMGNSS2_CMD_CMEE                           "AT+CMEE"
#define GSMGNSS2_CMD_CGATT                          "AT+CGATT"
#define GSMGNSS2_CMD_CSQ                            "AT+CSQ"
#define GSMGNSS2_CMD_COPS                           "AT+COPS"
#define GSMGNSS2_CMD_CMGS                           "AT+CMGS"
#define GSMGNSS2_CMD_CMGF                           "AT+CMGF"
#define GSMGNSS2_CMD_CGNSPWR                        "AT+CGNSPWR"
#define GSMGNSS2_CMD_CGNSTST                        "AT+CGNSTST"

/**
 * @brief GSMGNSS 2 response buffer commands.
 * @details Specified response buffer commands of GSMGNSS 2 Click driver.
 */
#define GSMGNSS2_RSP_START                          "$"
#define GSMGNSS2_RSP_DELIMITER                      ","
#define GSMGNSS2_RSP_GNGGA                          "$GNGGA"

/**
 * @brief GSMGNSS 2 GNGGA command elements.
 * @details Specified GNGGA command elements of GSMGNSS 2 Click driver.
 */
#define GSMGNSS2_GNGGA_ELEMENT_SIZE                 15
#define GSMGNSS2_GNGGA_TIME                         1 
#define GSMGNSS2_GNGGA_LATITUDE                     2
#define GSMGNSS2_GNGGA_LATITUDE_SIDE                3
#define GSMGNSS2_GNGGA_LONGITUDE                    4
#define GSMGNSS2_GNGGA_LONGITUDE_SIDE               5
#define GSMGNSS2_GNGGA_QUALITY_INDICATOR            6
#define GSMGNSS2_GNGGA_NUMBER_OF_SATELLITES         7
#define GSMGNSS2_GNGGA_H_DILUTION_OF_POS            8
#define GSMGNSS2_GNGGA_ALTITUDE                     9
#define GSMGNSS2_GNGGA_ALTITUDE_UNIT                10
#define GSMGNSS2_GNGGA_GEOIDAL_SEPARATION           11
#define GSMGNSS2_GNGGA_GEOIDAL_SEPARATION_UNIT      12
#define GSMGNSS2_GNGGA_TIME_SINCE_LAST_DGPS         13
#define GSMGNSS2_GNGGA_DGPS_REFERENCE_STATION_ID    14

/**
 * @brief GSMGNSS 2 module power state.
 * @details Specified module power state of GSMGNSS 2 Click driver.
 */
#define GSMGNSS2_MODULE_POWER_ON                    1
#define GSMGNSS2_MODULE_POWER_OFF                   0

/**
 * @brief GSM/GNSS 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE_RX                          256
#define DRV_BUFFER_SIZE_TX                          256 

/*! @} */ // gsmgnss2_cmd

/**
 * @defgroup gsmgnss2_map GSM/GNSS 2 MikroBUS Map
 * @brief MikroBUS pin mapping of GSM/GNSS 2 Click driver.
 */

/**
 * @addtogroup gsmgnss2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GSM/GNSS 2 Click to the selected MikroBUS.
 */
#define GSMGNSS2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.det = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gsmgnss2_map
/*! @} */ // gsmgnss2

/**
 * @brief GSM/GNSS 2 Click context object.
 * @details Context object definition of GSM/GNSS 2 Click driver.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t rts;

    // Input pins 

    digital_in_t det;
    digital_in_t ring;
    digital_in_t cts;
    
    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE_RX ];      /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE_TX ];      /**< Buffer size. */

} gsmgnss2_t;

/**
 * @brief GSM/GNSS 2 Click configuration object.
 * @details Configuration object definition of GSM/GNSS 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                              /**< RX pin. */
    pin_name_t tx_pin;                              /**< TX pin. */

    // Additional gpio pins 

    pin_name_t det;
    pin_name_t rst;
    pin_name_t rts;
    pin_name_t ring;
    pin_name_t cts;

    // Static variable
    uint32_t          baud_rate;                    /**< Clock speed. */
    bool              uart_blocking;                /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                     /**< Data bits. */
    uart_parity_t     parity_bit;                   /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                     /**< Stop bits. */

} gsmgnss2_cfg_t;

/**
 * @brief GSM/GNSS 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GSMGNSS2_OK = 0,
    GSMGNSS2_ERROR = -1

} gsmgnss2_return_value_t;

/*!
 * @addtogroup gsmgnss2 GSM/GNSS 2 Click Driver
 * @brief API for configuring and manipulating GSM/GNSS 2 Click driver.
 * @{
 */

/**
 * @brief GSM/GNSS 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gsmgnss2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gsmgnss2_cfg_setup ( gsmgnss2_cfg_t *cfg );

/**
 * @brief GSM/GNSS 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gsmgnss2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsmgnss2_init ( gsmgnss2_t *ctx, gsmgnss2_cfg_t *cfg );

/**
 * @brief Power ON/OFF the module.
 * @param ctx Click object.
 * @param state 0 - power OFF, 1 - power ON.
 */
void gsmgnss2_module_power ( gsmgnss2_t *ctx, uint8_t state );

/**
 * @brief GSM/GNSS 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsmgnss2_generic_write ( gsmgnss2_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief GSM/GNSS 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsmgnss2_generic_read ( gsmgnss2_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 */
void gsmgnss2_send_cmd ( gsmgnss2_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 */
void gsmgnss2_send_cmd_with_parameter ( gsmgnss2_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 */
void gsmgnss2_send_cmd_check ( gsmgnss2_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 */
void gsmgnss2_send_cmd_parameter_check ( gsmgnss2_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 * @return Nothing.
 */
void gsmgnss2_set_sim_apn ( gsmgnss2_t *ctx, char *sim_apn );

/**
 * @brief GSM GNSS 2 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] message_context  Message to be sent.
 * @return Nothing.
 */
void gsmgnss2_send_sms_text ( gsmgnss2_t *ctx, char *phone_number, char *sms_text );

/**
 * @brief GSM GNSS 2 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #gsmgnss2_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t gsmgnss2_send_sms_pdu ( gsmgnss2_t *ctx, char *service_center_number, 
                              char *phone_number, char *sms_text );

/**
 * @brief GSM GNSS 2 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gsmgnss2_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GSMGNSS2_H

/*! @} */ // gsmgnss2

// ------------------------------------------------------------------------ END
