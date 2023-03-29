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
 * \brief This file contains API for 5G NB IoT Click driver.
 *
 * \addtogroup c5gnbiot 5G NB IoT Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C5GNBIOT_H
#define C5GNBIOT_H

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
#define C5GNBIOT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.on = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define C5GNBIOT_MODULE_POWER_ON   1
#define C5GNBIOT_MODULE_POWER_OFF  0
/** \} */

/**
 * \defgroup commands AT Commands define
 * \{
 */
#define C5GNBIOT_CMD_AT          "AT"
#define C5GNBIOT_CMD_ATI         "ATI"
#define C5GNBIOT_CMD_CGMR        "AT+CGMR"

#define C5GNBIOT_CMD_CFUN        "AT+CFUN"
#define C5GNBIOT_CMD_CREG        "AT+CREG"
#define C5GNBIOT_CMD_CEREG       "AT+CEREG"
#define C5GNBIOT_CMD_CGDCONT     "AT+CGDCONT"
#define C5GNBIOT_CMD_CIMI        "AT+CIMI"
#define C5GNBIOT_CMD_CGATT       "AT+CGATT"
#define C5GNBIOT_CMD_CESQ        "AT+CESQ"
#define C5GNBIOT_CMD_COPS        "AT+COPS"
#define C5GNBIOT_CMD_CMGS        "AT+CMGS"
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 300
#define DRV_TX_BUFFER_SIZE 300
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

    digital_out_t on;
    digital_out_t rts;
    
    // Input pins 
    
    digital_in_t cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} c5gnbiot_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t on;
    pin_name_t cts;
    pin_name_t rts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} c5gnbiot_cfg_t;

/**
 * @brief 5G NB IoT Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C5GNBIOT_OK = 0,
    C5GNBIOT_ERROR = -1

} c5gnbiot_return_value_t;

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
 * @brief 5G NB IoT configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c5gnbiot_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c5gnbiot_cfg_setup ( c5gnbiot_cfg_t *cfg );

/**
 * @brief 5G NB IoT initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c5gnbiot_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gnbiot_init ( c5gnbiot_t *ctx, c5gnbiot_cfg_t *cfg );

/**
 * @brief 5G NB IoT data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gnbiot_generic_write ( c5gnbiot_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief 5G NB IoT data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c5gnbiot_generic_read ( c5gnbiot_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief 5G NB IoT module power on.
 * @details This function resets the chip on 5G NB IoT click.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @return Nothing.
 */
void c5gnbiot_power_on ( c5gnbiot_t *ctx );

/**
 * @brief Sets state of the ON pin.
 * @details This function sets ON pin state.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void c5gnbiot_set_on ( c5gnbiot_t *ctx, uint8_t state );

/**
 * @brief Sets state of the RTS pin.
 * @details This function sets RTS pin state.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void c5gnbiot_set_rts ( c5gnbiot_t *ctx, uint8_t state );

/**
 * @brief CTS Pin Get function
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t c5gnbiot_get_cts ( c5gnbiot_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void c5gnbiot_send_cmd ( c5gnbiot_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 */
void c5gnbiot_send_cmd_with_parameter ( c5gnbiot_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void c5gnbiot_send_cmd_check ( c5gnbiot_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void c5gnbiot_send_cmd_parameter_check ( c5gnbiot_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 */
void c5gnbiot_set_sim_apn ( c5gnbiot_t *ctx, char *sim_apn );

/**
 * @brief 5G NB IoT send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #c5gnbiot_t object definition for detailed explanation.
 * @param[in] service_center_number  SMSC of the SIM card.
 * @param[in] phone_number  Phone number to message.
 * @param[in] sms_text  Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t c5gnbiot_send_text_message ( c5gnbiot_t *ctx, char *service_center_number, 
                                                   char *phone_number, char *sms_text );

#ifdef __cplusplus
}
#endif
#endif  // _C5GNBIOT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
