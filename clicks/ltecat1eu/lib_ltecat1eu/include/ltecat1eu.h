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
 * @file ltecat1eu.h
 * @brief This file contains API for LTE Cat.1-EU Click Driver.
 */

#ifndef LTECAT1EU_H
#define LTECAT1EU_H

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
 * @addtogroup ltecat1eu LTE Cat.1-EU Click Driver
 * @brief API for configuring and manipulating LTE Cat.1-EU Click driver.
 * @{
 */


/**
 * @defgroup ltecat1eu_set LTE Cat.1-EU Device Settings
 * @brief Settings for registers of LTE Cat.1-EU Click driver.
 */

/**
 * @addtogroup ltecat1eu_set
 * @{
 */

/**
 * @brief LTE Cat.1-EU description setting.
 * @details Specified setting for description of LTE Cat.1-EU Click driver.
 */
#define LTECAT1EU_CMD_AT          "AT"
#define LTECAT1EU_CMD_ATI         "ATI"
#define LTECAT1EU_CMD_CGMR        "AT+CGMR"

#define LTECAT1EU_CMD_CFUN        "AT+CFUN"
#define LTECAT1EU_CMD_CREG        "AT+CREG"
#define LTECAT1EU_CMD_CEREG       "AT+CEREG"
#define LTECAT1EU_CMD_CGDCONT     "AT+CGDCONT"
#define LTECAT1EU_CMD_CIMI        "AT+CIMI"
#define LTECAT1EU_CMD_CGATT       "AT+CGATT"
#define LTECAT1EU_CMD_CSQ         "AT+CSQ"
#define LTECAT1EU_CMD_CESQ        "AT+CESQ"
#define LTECAT1EU_CMD_COPS        "AT+COPS"


/**
 * @brief LTE Cat.1-EU driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_RX_BUFFER_SIZE 500
#define DRV_TX_BUFFER_SIZE 100

/*! @} */ // ltecat1eu_set

/**
 * @defgroup ltecat1eu_map LTE Cat.1-EU MikroBUS Map
 * @brief MikroBUS pin mapping of LTE Cat.1-EU Click driver.
 */

/**
 * @addtogroup ltecat1eu_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE Cat.1-EU Click to the selected MikroBUS.
 */
#define LTECAT1EU_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ltecat1eu_map
/*! @} */ // ltecat1eu

/**
 * @brief LTE Cat.1-EU Click context object.
 * @details Context object definition of LTE Cat.1-EU Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;   
    digital_out_t cs;    
    digital_out_t rts;  

    // Input pins
    digital_in_t cts;      

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];         /**< Buffer size. */

} ltecat1eu_t;

/**
 * @brief LTE Cat.1-EU Click configuration object.
 * @details Configuration object definition of LTE Cat.1-EU Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
   //pin_name_t an;         
    pin_name_t rst;       
    pin_name_t cts;   
    pin_name_t cs;    
    pin_name_t rts;      
    
    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} ltecat1eu_cfg_t;

/**
 * @brief LTE Cat.1-EU Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   LTECAT1EU_OK = 0,
   LTECAT1EU_ERROR = -1

} ltecat1eu_return_value_t;

/*!
 * @addtogroup ltecat1eu LTE Cat.1-EU Click Driver
 * @brief API for configuring and manipulating LTE Cat.1-EU Click driver.
 * @{
 */

/**
 * @brief LTE Cat.1-EU configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ltecat1eu_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ltecat1eu_cfg_setup ( ltecat1eu_cfg_t *cfg );

/**
 * @brief LTE Cat.1-EU initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ltecat1eu_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat1eu_init ( ltecat1eu_t *ctx, ltecat1eu_cfg_t *cfg );

/**
 * @brief LTE Cat.1-EU data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return Nothing.
 * 
 * @note None.
 */
void ltecat1eu_generic_write ( ltecat1eu_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LTE Cat.1-EU data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ltecat1eu_generic_read ( ltecat1eu_t *ctx, char *data_buf, uint16_t max_len );


/**
 * @brief LTE Cat.1-EU module power on.
 * @details This function resets the chip on LTE Cat.1-EU Click.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @return Nothing.
 */
void ltecat1eu_power_on ( ltecat1eu_t *ctx );

/**
 * @brief Sets state of the RST pin.
 * @details This function sets RST pin state.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void ltecat1eu_set_rst ( ltecat1eu_t *ctx, uint8_t state );

/**
 * @brief Sets state of the RTS pin.
 * @details This function sets RTS pin state.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] state Pin state ( 1 or 0 ).
 * @return Nothing.
 */
void ltecat1eu_set_rts ( ltecat1eu_t *ctx, uint8_t state );

/**
 * @brief CTS Pin Get function
 * @details This function allows user to check state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @return @li @c 0 logical low.
 *         @li @c 1 logical high.
 */
uint8_t ltecat1eu_get_cts ( ltecat1eu_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void ltecat1eu_send_cmd ( ltecat1eu_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the Click module.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 */
void ltecat1eu_send_cmd_with_parameter ( ltecat1eu_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void ltecat1eu_send_cmd_check ( ltecat1eu_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 *
 * @return Nothing.
 */
void ltecat1eu_send_cmd_parameter_check ( ltecat1eu_t *ctx, char *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 */
void ltecat1eu_set_sim_apn ( ltecat1eu_t *ctx, char *sim_apn );

/**
 * @brief LTE Cat.1-EU send text message.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #ltecat1eu_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] message_context  Message to be sent.
 *
 * @return Nothing.
 */
void ltecat1eu_send_text_message ( ltecat1eu_t *ctx, char *phone_number, char *message_context );

#ifdef __cplusplus
}
#endif
#endif // LTECAT1EU_H

/*! @} */ // ltecat1eu

// ------------------------------------------------------------------------ END
