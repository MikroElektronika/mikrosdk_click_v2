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
 * \brief This file contains API for RS232 Isolator Click driver.
 *
 * \addtogroup rs232isolator RS232 Isolator Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RS232ISOLATOR_H
#define RS232ISOLATOR_H

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
#define RS232ISOLATOR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RS232ISOLATOR_RETVAL  uint8_t

#define RS232ISOLATOR_OK           0x00
#define RS232ISOLATOR_INIT_ERROR   0xFF
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

    digital_out_t cts;

    // Input pins 

    digital_in_t rts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} rs232isolator_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t cts;
    pin_name_t rts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} rs232isolator_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t rs232isolator_error_t;

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
void rs232isolator_cfg_setup ( rs232isolator_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param rs232isolator Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RS232ISOLATOR_RETVAL rs232isolator_init ( rs232isolator_t *ctx, rs232isolator_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param rs232isolator Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void rs232isolator_generic_write ( rs232isolator_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param rs232isolator Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int16_t rs232isolator_generic_read ( rs232isolator_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Function settings RTS state.
 *
 * @param ctx          Click object.
 * @param state        RTS state 
 *
 * @description This function sets rts.
 */
void rs232_2_set_rts ( rs232isolator_t *ctx, uint8_t state );

/**
 * @brief Read CTS state.
 *
 * @param ctx          Click object.
 *
 * @description This function gets cts.
 */
uint8_t rs232_2_get_cts ( rs232isolator_t *ctx );

/**
 * @brief Function for send command.
 *
 * @param ctx          Click object.
 * @param command      Data to be send
 */
void rs232isolator_send_command ( rs232isolator_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _RS232ISOLATOR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
