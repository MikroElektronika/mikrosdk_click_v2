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
 * \brief This file contains API for RS485 Isolator 2 Click driver.
 *
 * \addtogroup rs485isolator2 RS485 Isolator 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RS485ISOLATOR2_H
#define RS485ISOLATOR2_H

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
#define RS485ISOLATOR2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.re = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.de = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.inr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg. ind = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RS485ISOLATOR2_RETVAL  uint8_t

#define RS485ISOLATOR2_OK           0x00
#define RS485ISOLATOR2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

#define RS485ISOLATOR2_ENABLE_RE      0x00
#define RS485ISOLATOR2_DISABLE_RE     0x01

// Driver Output Enable

#define RS485ISOLATOR2_ENABLE_DE      0x01
#define RS485ISOLATOR2_DISABLE_DE     0x00

// Receiver Inversion Enable

#define RS485ISOLATOR2_ENABLE_INR     0x01
#define RS485ISOLATOR2_DISABLE_INR    0x00

// Driver Inversion Enable

#define RS485ISOLATOR2_ENABLE_IND     0x01
#define RS485ISOLATOR2_DISABLE_IND    0x00

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

    digital_out_t re;
    digital_out_t de;
    digital_out_t inr;
    digital_out_t ind;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} rs485isolator2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t re;
    pin_name_t de;
    pin_name_t inr;
    pin_name_t ind;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} rs485isolator2_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t rs485isolator2_error_t;

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
void rs485isolator2_cfg_setup ( rs485isolator2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RS485ISOLATOR2_RETVAL rs485isolator2_init ( rs485isolator2_t *ctx, rs485isolator2_cfg_t *cfg );

/**
 * @brief Set DE ( cs ) pin state.
 * @param ctx Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void rs485isolator2_set_de_pin ( rs485isolator2_t *ctx, uint8_t state );

/**
 * @brief Set RE ( reset ) pin state.
 * @param ctx Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void rs485isolator2_set_re_pin ( rs485isolator2_t *ctx, uint8_t state );

/**
 * @brief Get IND (int) pin state.
 * @param ctx Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void rs485isolator2_set_ind_pin ( rs485isolator2_t *ctx, uint8_t state );

/**
 * @brief Set INR ( pwm ) pin state.
 * @param ctx Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void rs485isolator2_set_inr_pin ( rs485isolator2_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void rs485isolator2_generic_write ( rs485isolator2_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t rs485isolator2_generic_read ( rs485isolator2_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Bit by bit write function.
 * @param ctx Click object.
 * @param command Data buffer for sends.
 */
void rs485isolator2_send_bit_by_bit( rs485isolator2_t *ctx, char *command );


#ifdef __cplusplus
}
#endif
#endif  // _RS485ISOLATOR2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
