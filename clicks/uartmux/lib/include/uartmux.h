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
 * \brief This file contains API for UART Mux Click driver.
 *
 * \addtogroup uartmux UART Mux Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UARTMUX_H
#define UARTMUX_H

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
#define UARTMUX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.inh = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.a = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.b = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UARTMUX_RETVAL  uint8_t

#define UARTMUX_OK           0x00
#define UARTMUX_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UARTMUX_PIN_STATE_HIGH    1
#define UARTMUX_PIN_STATE_LOW     0
/** \} */

/**
 * \defgroup choose_channel_1  Choose channel 1
 * \{
 */
#define UARTMUX_STATE_A_CHANNEL_1   0
#define UARTMUX_STATE_B_CHANNEL_1   0
/** \} */

/**
 * \defgroup choose_channel_2  Choose channel 2
 * \{
 */
#define UARTMUX_STATE_A_CHANNEL_2   1
#define UARTMUX_STATE_B_CHANNEL_2   0
/** \} */

/**
 * \defgroup choose_channel_3  Choose channel 3
 * \{
 */
#define UARTMUX_STATE_A_CHANNEL_3   0
#define UARTMUX_STATE_B_CHANNEL_3   1
/** \} */

/**
 * \defgroup choose_channel_4  Choose channel 4
 * \{
 */
#define UARTMUX_STATE_A_CHANNEL_4   1
#define UARTMUX_STATE_B_CHANNEL_4   1
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct 
{
    uint8_t state_a;
    uint8_t state_b;

}uartmux_channel_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t inh;
    digital_out_t a;
    digital_out_t b;

    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    //uartmux_channel_t channel;

} uartmux_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t inh;
    pin_name_t a;
    pin_name_t b;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} uartmux_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t uartmux_error_t;

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
void uartmux_cfg_setup ( uartmux_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param uartmux Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UARTMUX_RETVAL uartmux_init ( uartmux_t *ctx, uartmux_cfg_t *cfg );

/**
 * @brief Generic write function.
 * 
 * @param uartmux  Click object.
 * @param data_buf Data buffer for sends.
 * @param channel  Struct of channel ( 1, 2, 3, 4 )
 */
void uartmux_generic_write ( uartmux_t *ctx, char *data_buf, uartmux_channel_t *channel );
/**
 * @brief Generic read function.
 * 
 * @param uartmux Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @param channel Struct of channel ( 1, 2, 3, 4 )
 * 
 * @return Number of reads data.
 */
int32_t uartmux_generic_read ( uartmux_t *ctx, char *data_buf, uint16_t max_len, uartmux_channel_t *channel );

/**
 * @brief Send command.
 * 
 * @param uartmux Click object.
 * @param command Data to be send.
 * @param channel Struct of channel ( 1, 2, 3, 4 )
 */
void uartmux_send_command ( uartmux_t *ctx, char *command, uartmux_channel_t *channel );

/**
 * @brief Set INT pin
 * 
 * @param uartmux Click object.
 * @param state   State of INT pin.
 */
void uartmux_set_inhibit_communication ( uartmux_t *ctx, uint8_t state );

/**
 * @brief Choose channel
 * 
 * @param uartmux  Click object.
 * @param channel  Struct of channel ( 1, 2, 3, 4 )
 */
void uartmux_choose_channel ( uartmux_t *ctx, uartmux_channel_t *channel );

#ifdef __cplusplus
}
#endif
#endif  // _UARTMUX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
