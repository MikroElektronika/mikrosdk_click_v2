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
 * \brief This file contains API for LTE Cat.1 Click driver.
 *
 * \addtogroup ltecat1 LTE Cat.1 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LTECAT1_H
#define LTECAT1_H

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
#define LTECAT1_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.an      = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LTECAT1_RETVAL  uint8_t

#define LTECAT1_OK           0x00
#define LTECAT1_INIT_ERROR   0xFF
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

    digital_out_t rst;
    digital_out_t int_pin;

    // Input pins 

    digital_in_t an;
    digital_in_t cs;
    digital_in_t pwm;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} ltecat1_t;

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
    pin_name_t rst;
    pin_name_t cs;
    pin_name_t pwm;
    pin_name_t int_pin;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} ltecat1_cfg_t;

/**
 * @brief Error type 
 */
// Actuator switch type
typedef uint8_t ltecat1_actuator_sw_t;

// Actuator counter type
typedef int16_t ltecat1_actuator_cnt_t;

// Actuator string type
typedef char ltecat1_actuator_str_t;

// Parser error type
typedef uint8_t ltecat1_error_t;

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
void ltecat1_cfg_setup ( ltecat1_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ltecat1 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LTECAT1_RETVAL ltecat1_init ( ltecat1_t *ctx, ltecat1_cfg_t *cfg );

/**
 * @brief Power module.
 * 
 * @param ctx         Click object.
 * @param power_state State of RST pin.
 */
void ltecat1_module_power ( ltecat1_t *ctx, uint8_t power_state );

/**
 * @brief Generic write function.
 * 
 * @param ctx       Click object.
 * @param data_buf  Data buffer for sends.
 * @param len       Number of bytes for sends.
 */
void ltecat1_generic_write ( ltecat1_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx       Click object.
 * @param data_buf  Data buffer for read data.
 * @param max_len   The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
int32_t ltecat1_generic_read ( ltecat1_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Function for send command.
 * 
 * @param ctx       Click object.
 * @param command   Data to be send.
 */
void ltecat1_send_command ( ltecat1_t *ctx, char *command );

/**
 * @brief Generic parser function.
 * 
 * @param data_in            
 * @param cmd      
 * @param data_pos   
 * 
 * @return return data
 */
char *ltecat1_gps_parser ( char *data_in, char *cmd, uint8_t data_pos );

#ifdef __cplusplus
}
#endif
#endif  // _LTECAT1_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
