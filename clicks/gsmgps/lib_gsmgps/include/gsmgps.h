/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 * \brief This file contains API for GSMGPS Click driver.
 *
 * \addtogroup gsmgps GSMGPS Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GSMGPS_H
#define GSMGPS_H

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
#define GSMGPS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.sta = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.pwk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.ri = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GSMGPS_RETVAL  uint8_t
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define GSMGPS_NEMA_GPGGA 1
#define GSMGPS_NEMA_GPGLL 3
#define GSMGPS_NEMA_GPGGA_NUM_ELEMENT 15
#define GSMGPS_NEMA_GPGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define GSMGPS_GPGGA_TIME                      1 
#define GSMGPS_GPGGA_LATITUDE                  2
#define GSMGPS_GPGGA_LATITUDE_SIDE             3
#define GSMGPS_GPGGA_LONGITUDE                 4
#define GSMGPS_GPGGA_LONGITUDE_SIDE            5
#define GSMGPS_GPGGA_QUALITY_INDICATOR         6
#define GSMGPS_GPGGA_NUMBER_OF_SATELLITES      7
#define GSMGPS_GPGGA_H_DILUTION_OF_POS         8
#define GSMGPS_GPGGA_ALTITUDE                  9
#define GSMGPS_GPGGA_ALTITUDE_UNIT             10
#define GSMGPS_GPGGA_GEOIDAL_SEPARATION        11
#define GSMGPS_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define GSMGPS_GPGGA_TIME_SINCE_LAST_DGPS      13
#define GSMGPS_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define GSMGPS_GPGLL_LATITUDE                  1
#define GSMGPS_GPGLL_LATITUDE_SIDE             2
#define GSMGPS_GPGLL_LONGITUDE                 3
#define GSMGPS_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define GSMGPS_ERROR_COMMAND_OR_ELEMENT   0xFF
#define GSMGPS_ERROR_START_OR_END_COMMAND 0x8F
#define GSMGPS_ERROR_NEXT_ELEMENT         0x4F
#define GSMGPS_ERROR_CURRENT_ELEMENT      0x2F
#define GSMGPS_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define GSMGPS_MODULE_POWER_ON   1
#define GSMGPS_MODULE_POWER_OFF  0
/** \} */

/**
 * \defgroup at_command AT command 
 * \{
 */
#define GSMGPS_CMD_AT          "AT"
#define GSMGPS_CMD_ATI         "ATI"
#define GSMGPS_CMD_CGMR        "AT+CGMR"

#define GSMGPS_CMD_CFUN        "AT+CFUN"
#define GSMGPS_CMD_CREG        "AT+CREG"
#define GSMGPS_CMD_CGDCONT     "AT+CGDCONT"
#define GSMGPS_CMD_CIMI        "AT+CIMI"
#define GSMGPS_CMD_CGATT       "AT+CGATT"
#define GSMGPS_CMD_CSQ         "AT+CSQ"
#define GSMGPS_CMD_COPS        "AT+COPS"
#define GSMGPS_CMD_CMGS        "AT+CMGS"
#define GSMGPS_CMD_CMGF        "AT+CMGF"
#define GSMGPS_CMD_CGNSPWR     "AT+CGNSPWR"
#define GSMGPS_CMD_CGPSINF     "AT+CGPSINF"
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

    digital_out_t pwk;
    digital_out_t rts;

    // Input pins 

    digital_in_t sta;
    digital_in_t ri;
    digital_in_t cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} gsmgps_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t sta;
    pin_name_t pwk;
    pin_name_t rts;
    pin_name_t ri;
    pin_name_t cts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} gsmgps_cfg_t;

/**
 * @brief GSM-GPS Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GSMGPS_OK = 0,
    GSMGPS_ERROR = -1

} gsmgps_return_value_t;

/**
 * @brief Error type 
 */
typedef uint8_t gsmgps_error_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void gsmgps_cfg_setup ( gsmgps_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
GSMGPS_RETVAL gsmgps_init ( gsmgps_t *ctx, gsmgps_cfg_t *cfg );

/**
 * @brief Power ON/OFF the module.
 * @param ctx Click object.
 * @param state 0 - power OFF, 1 - power ON.
 */
void gsmgps_module_power ( gsmgps_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void gsmgps_generic_write ( gsmgps_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t gsmgps_generic_read ( gsmgps_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Sets state of the RTS pin.
 * @details This function sets RTS pin state.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void gsmgps_set_rts ( gsmgps_t *ctx, uint8_t state );

/**
 * @brief CTS Pin Get function
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t gsmgps_get_cts ( gsmgps_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void gsmgps_send_cmd ( gsmgps_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the Click module.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 */
void gsmgps_send_cmd_with_parameter ( gsmgps_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void gsmgps_send_cmd_check ( gsmgps_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void gsmgps_send_cmd_parameter_check ( gsmgps_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 */
void gsmgps_set_sim_apn ( gsmgps_t *ctx, char *sim_apn );

/**
 * @brief GSM-GPS send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] message_context  Message to be sent.
 *
 * @return Nothing.
 */
void gsmgps_send_sms_text ( gsmgps_t *ctx, char *phone_number, char *sms_text );

/**
 * @brief GSM-GPS send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #gsmgps_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t gsmgps_send_sms_pdu ( gsmgps_t *ctx, char *service_center_number, 
                                           char *phone_number, char *sms_text );

/**
 * @brief Generic parser function.
 * @param gsmgps Click object.
 * @param command NEMA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * @return error data
 */
gsmgps_error_t gsmgps_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

#ifdef __cplusplus
}
#endif
#endif  // _GSMGPS_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
