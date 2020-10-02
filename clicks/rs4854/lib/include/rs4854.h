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
 * \brief This file contains API for RS485 4 Click driver.
 *
 * \addtogroup rs4854 RS485 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RS4854_H
#define RS4854_H

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
#define RS4854_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.re = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.de = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RS4854_RETVAL  uint8_t

#define RS4854_OK           0x00
#define RS4854_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/**
 * \defgroup pin_state  Pin state
 * \{
 */
#define RS4854_PIN_STATE_LOW    0
#define RS4854_PIN_STATE_HIGH   1
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

    digital_out_t re;
    digital_out_t de;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} rs4854_t;

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

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} rs4854_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t rs4854_error_t;

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
void rs4854_cfg_setup ( rs4854_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param rs4854 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RS4854_RETVAL rs4854_init ( rs4854_t *ctx, rs4854_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param rs4854 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void rs4854_generic_write ( rs4854_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param rs4854 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int16_t rs4854_generic_read ( rs4854_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Rx disable function.
 *
 * @param ctx          Click object.
 *
 * @description This function disable rx.
 */
void rs4854_rx_disable ( rs4854_t *ctx );

/**
 * @brief Rx enable function.
 *
 * @param ctx          Click object.
 *
 * @description This function enable rx.
 */
void rs4854_rx_enable ( rs4854_t *ctx );

/**
 * @brief Tx disable function.
 *
 * @param ctx          Click object.
 *
 * @description This function disable tx.
 */
void rs4854_tx_disable ( rs4854_t *ctx );

/**
 * @brief Tx enable function.
 *
 * @param ctx          Click object.
 *
 * @description This function enable tx.
 */
void rs4854_tx_enable ( rs4854_t *ctx );

/**
 * @brief Sets RE pin to high or low state
 *
 * @param pin_state  pin state
 * 
 * @description This function sets state of the re pin.
 */
void rs4854_re_pin_set (rs4854_t *ctx,  uint8_t pin_state );

/**
 * @brief Sets DE pin to high or low state
 *
 * @param pin_state  pin state
 * 
 * @description This function sets state of the de pin.
 */
void rs4854_de_pin_set ( rs4854_t *ctx,  uint8_t pin_state );

/**
 * @brief Function for send command
 *
 * @param ctx          Click object.
 * @param command      Data to  be send.
 */
void rs4854_send_command ( rs4854_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _RS4854_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
