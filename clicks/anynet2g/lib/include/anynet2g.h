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
 * \brief This file contains API for AnyNet 2G Click driver.
 *
 * \addtogroup anynet2g AnyNet 2G Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ANYNET2G_H
#define ANYNET2G_H

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
#define ANYNET2G_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.an     = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.slp    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.dsr    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.dtr    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.iot    = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ANYNET2G_RETVAL  uint8_t

#define ANYNET2G_OK           0x00
#define ANYNET2G_INIT_ERROR   0xFF
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

    digital_out_t an;
    digital_out_t slp;
    digital_out_t dtr;
    digital_out_t iot;

    // Input pins 

    digital_in_t dsr;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} anynet2g_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t slp;
    pin_name_t dsr;
    pin_name_t dtr;
    pin_name_t iot;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} anynet2g_cfg_t;

/**
 * @brief Error type 
 */
// Actuator switch type
typedef uint8_t anynet2g_actuator_sw_t;

// Actuator counter type
typedef int16_t anynet2g_actuator_cnt_t;

// Actuator string type
typedef char anynet2g_actuator_str_t;

// Parser error type
typedef uint8_t anynet2g_error_t;

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
void anynet2g_cfg_setup ( anynet2g_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param anynet2g Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ANYNET2G_RETVAL anynet2g_init ( anynet2g_t *ctx, anynet2g_cfg_t *cfg );

/**
 * @brief Generic write function.
 * 
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void anynet2g_generic_write ( anynet2g_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
int32_t anynet2g_generic_read ( anynet2g_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command.
 * 
 * @param ctx Click object.
 * @param command Data to be sent.
 */
void anynet2g_send_command ( anynet2g_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _ANYNET2G_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
