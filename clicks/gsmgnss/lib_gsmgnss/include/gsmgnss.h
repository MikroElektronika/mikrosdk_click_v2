/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for GSM GNSS Click driver.
 *
 * \addtogroup gsmgnss GSM GNSS Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GSMGNSS_H
#define GSMGNSS_H

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


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define GSMGNSS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.det = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GSMGNSS_RETVAL  uint8_t
/** \} */

/**
 * \defgroup support_cmd Current support NMEA command 
 * \{
 */
#define GSMGNSS_NMEA_GNGGA 1
#define GSMGNSS_NMEA_GNGLL 3
#define GSMGNSS_NMEA_GNGGA_NUM_ELEMENT 15
#define GSMGNSS_NMEA_GNGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup GNGGA_element GNGGA command elements 
 * \{
 */
#define GSMGNSS_GNGGA_TIME                      1 
#define GSMGNSS_GNGGA_LATITUDE                  2
#define GSMGNSS_GNGGA_LATITUDE_SIDE             3
#define GSMGNSS_GNGGA_LONGITUDE                 4
#define GSMGNSS_GNGGA_LONGITUDE_SIDE            5
#define GSMGNSS_GNGGA_QUALITY_INDICATOR         6
#define GSMGNSS_GNGGA_NUMBER_OF_SATELLITES      7
#define GSMGNSS_GNGGA_H_DILUTION_OF_POS         8
#define GSMGNSS_GNGGA_ALTITUDE                  9
#define GSMGNSS_GNGGA_ALTITUDE_UNIT             10
#define GSMGNSS_GNGGA_GEOIDAL_SEPARATION        11
#define GSMGNSS_GNGGA_GEOIDAL_SEPARATION_UNIT   12
#define GSMGNSS_GNGGA_TIME_SINCE_LAST_DGPS      13
#define GSMGNSS_GNGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup GNGLL_element GNGLL command elements 
 * \{
 */
#define GSMGNSS_GNGLL_LATITUDE                  1
#define GSMGNSS_GNGLL_LATITUDE_SIDE             2
#define GSMGNSS_GNGLL_LONGITUDE                 3
#define GSMGNSS_GNGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define GSMGNSS_ERROR_COMMAND_OR_ELEMENT   0xFF
#define GSMGNSS_ERROR_START_OR_END_COMMAND 0x8F
#define GSMGNSS_ERROR_NEXT_ELEMENT         0x4F
#define GSMGNSS_ERROR_CURRENT_ELEMENT      0x2F
#define GSMGNSS_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define GSMGNSS_MODULE_POWER_ON   1
#define GSMGNSS_MODULE_POWER_OFF  0
/** \} */

/**
 * \defgroup at_command AT command 
 * \{
 */
#define GSMGNSS_CMD_AT          "AT"
#define GSMGNSS_CMD_ATI         "ATI"
#define GSMGNSS_CMD_CGMR        "AT+CGMR"

#define GSMGNSS_CMD_CFUN        "AT+CFUN"
#define GSMGNSS_CMD_CREG        "AT+CREG"
#define GSMGNSS_CMD_CGREG       "AT+CGREG"
#define GSMGNSS_CMD_CGDCONT     "AT+CGDCONT"
#define GSMGNSS_CMD_CIMI        "AT+CIMI"
#define GSMGNSS_CMD_CMEE        "AT+CMEE"
#define GSMGNSS_CMD_CGATT       "AT+CGATT"
#define GSMGNSS_CMD_CSQ         "AT+CSQ"
#define GSMGNSS_CMD_COPS        "AT+COPS"
#define GSMGNSS_CMD_CMGS        "AT+CMGS"
#define GSMGNSS_CMD_CMGF        "AT+CMGF"
#define GSMGNSS_CMD_QGNSSC      "AT+QGNSSC"
#define GSMGNSS_CMD_QGNSSRD     "AT+QGNSSRD"
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 256
#define DRV_TX_BUFFER_SIZE 256
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
/**
 * @brief Click ctx object definition.
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

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} gsmgnss_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t det;
    pin_name_t rst;
    pin_name_t rts;
    pin_name_t ring;
    pin_name_t cts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} gsmgnss_cfg_t;

/**
 * @brief GSM GNSS Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GSMGNSS_OK = 0,
    GSMGNSS_ERROR = -1

} GSMGNSS_return_value_t;

/**
 * @brief Error type 
 */
typedef uint8_t gsmgnss_error_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void gsmgnss_cfg_setup ( gsmgnss_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GSMGNSS_RETVAL gsmgnss_init ( gsmgnss_t *ctx, gsmgnss_cfg_t *cfg );

/**
 * @brief Power ON/OFF the module.
 * @param ctx Click object.
 * @param state 0 - power OFF, 1 - power ON.
 */
void gsmgnss_module_power ( gsmgnss_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void gsmgnss_generic_write ( gsmgnss_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t gsmgnss_generic_read ( gsmgnss_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Sets state of the RTS pin.
 * @details This function sets RTS pin state.
 * @param[in] ctx : Click context object.
 * See #gsmgnss_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void gsmgnss_set_rts ( gsmgnss_t *ctx, uint8_t state );

/**
 * @brief CTS Pin Get function
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #gsmgnss_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t gsmgnss_get_cts ( gsmgnss_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #gsmgnss_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void gsmgnss_send_cmd ( gsmgnss_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #gsmgnss_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 */
void gsmgnss_send_cmd_with_parameter ( gsmgnss_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsmgnss_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void gsmgnss_send_cmd_check ( gsmgnss_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsmgnss_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void gsmgnss_send_cmd_parameter_check ( gsmgnss_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #gsmgnss_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 */
void gsmgnss_set_sim_apn ( gsmgnss_t *ctx, char *sim_apn );

/**
 * @brief GSM GNSS send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #gsmgnss_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] message_context  Message to be sent.
 *
 * @return Nothing.
 */
void gsmgnss_send_sms_text ( gsmgnss_t *ctx, char *phone_number, char *sms_text );

/**
 * @brief GSM GNSS send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #gsmgnss_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t gsmgnss_send_sms_pdu ( gsmgnss_t *ctx, char *service_center_number, 
                                           char *phone_number, char *sms_text );

/**
 * @brief Generic parser function.
 * @param gsmgnss Click object.
 * @param command NMEA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * @return error data
 */
gsmgnss_error_t gsmgnss_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

#ifdef __cplusplus
}
#endif
#endif  // _GSMGNSS_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
