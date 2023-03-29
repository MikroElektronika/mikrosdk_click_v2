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
 * \brief This file contains API for Dual LIN Click driver.
 *
 * \addtogroup duallin Dual LIN Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DUALLIN_H
#define DUALLIN_H

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
#define DUALLIN_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.en1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en2 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DUALLIN_RETVAL  uint8_t

#define DUALLIN_OK           0x00
#define DUALLIN_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup state_of_pin  State of pin
 * \{
 */
#define DUALLIN_PIN_STATE_LOW    0
#define DUALLIN_PIN_STATE_HIGH   1
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
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t en1;
    digital_out_t en2;


    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} duallin_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t en1;
    pin_name_t en2;
    pin_name_t int_pin;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} duallin_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t duallin_error_t;

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
void duallin_cfg_setup ( duallin_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DUALLIN_RETVAL duallin_init ( duallin_t *ctx, duallin_cfg_t *cfg );

/**
 * @brief Generic write function.
 * 
 * @param duallin Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void duallin_generic_write ( duallin_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param duallin Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
int16_t duallin_generic_read ( duallin_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Sets state of RST pin
 *
 * @param duallin Click object.
 * @param state   Set pin on low and high ( DUALLIN_PIN_STATE_HIGH or DUALLIN_PIN_STATE_LOW )
 */
void duallin_bus1_status ( duallin_t *ctx, uint8_t state );

/**
 * @brief Sets state of  CS pin
 *
 * @param duallin Click object.
 * @param state   Set pin on low and high ( DUALLIN_PIN_STATE_HIGH or DUALLIN_PIN_STATE_LOW )
 */
void duallin_bus2_status ( duallin_t *ctx, uint8_t state );

/**
 * @brief Send command.
 *
 * @param duallin    Click object.
 * @param command    Data to be send.
 */
void duallin_send_command ( duallin_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _DUALLIN_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
