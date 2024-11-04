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
 * \brief This file contains API for LTE IoT Click driver.
 *
 * \addtogroup lteiot LTE IoT Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LTEIOT_H
#define LTEIOT_H

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
#define LTEIOT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.pwr    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cts     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.ri     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.rts    = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LTEIOT_RETVAL  uint8_t

#define LTEIOT_OK           0x00
#define LTEIOT_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define LTEIOT_MODULE_POWER_ON   1
#define LTEIOT_MODULE_POWER_OFF  0
/** \} */

/**
 * \defgroup commands AT Commands define
 * \{
 */
#define LTEIOT_CMD_AT          "AT"
#define LTEIOT_CMD_ATI         "ATI"
#define LTEIOT_CMD_CGMR        "AT+CGMR"

#define LTEIOT_CMD_CFUN        "AT+CFUN"
#define LTEIOT_CMD_CREG        "AT+CREG"
#define LTEIOT_CMD_CEREG       "AT+CEREG"
#define LTEIOT_CMD_CGDCONT     "AT+CGDCONT"
#define LTEIOT_CMD_CIMI        "AT+CIMI"
#define LTEIOT_CMD_CGATT       "AT+CGATT"
#define LTEIOT_CMD_CSQ         "AT+CSQ"
#define LTEIOT_CMD_CESQ        "AT+CESQ"
#define LTEIOT_CMD_COPS        "AT+COPS"
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
#define DRV_TX_BUFFER_SIZE 100
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

    digital_out_t pwr;
    digital_out_t rst;
    digital_out_t rts;

    // Input pins 

    digital_in_t ri;
    digital_in_t cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} lteiot_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t pwr;
    pin_name_t rst;
    pin_name_t cts;
    pin_name_t ri;
    pin_name_t rts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} lteiot_cfg_t;

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
 * @brief LTE IoT configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot_cfg_setup ( lteiot_cfg_t *cfg );

/**
 * @brief LTE IoT initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot_init ( lteiot_t *ctx, lteiot_cfg_t *cfg );

/**
 * @brief LTE IoT data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot_generic_write ( lteiot_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LTE IoT data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot_generic_read ( lteiot_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief LTE IoT module power on.
 * @details This function resets the chip on LTE IoT Click.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @return Nothing.
 */
void lteiot_power_on ( lteiot_t *ctx );

/**
 * @brief Sets state of the RST pin.
 * @details This function sets RST pin state.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void lteiot_set_rst ( lteiot_t *ctx, uint8_t state );

/**
 * @brief Sets state of the RTS pin.
 * @details This function sets RTS pin state.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void lteiot_set_rts ( lteiot_t *ctx, uint8_t state );

/**
 * @brief CTS Pin Get function
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t lteiot_get_cts ( lteiot_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void lteiot_send_cmd ( lteiot_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the Click module.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 */
void lteiot_send_cmd_with_parameter ( lteiot_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void lteiot_send_cmd_check ( lteiot_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void lteiot_send_cmd_parameter_check ( lteiot_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 */
void lteiot_set_sim_apn ( lteiot_t *ctx, char *sim_apn );

/**
 * @brief LTE IoT send text message.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #lteiot_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] message_context  Message to be sent.
 *
 * @return Nothing.
 */
void lteiot_send_text_message ( lteiot_t *ctx, char *phone_number, char *message_context );

#ifdef __cplusplus
}
#endif
#endif  // _LTEIOT_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
