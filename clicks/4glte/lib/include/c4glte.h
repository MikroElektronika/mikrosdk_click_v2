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
 * \brief This file contains API for 4G LTE Click driver.
 *
 * \addtogroup c4glte 4G LTE Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C4GLTE_H
#define C4GLTE_H

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
#define C4GLTE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.sta    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.pwk    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.ri     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts    = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C4GLTE_RETVAL  uint8_t

#define C4GLTE_OK           0x00
#define C4GLTE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup state_of_power  State of power
 * \{
 */
#define C4GLTE_MODULE_POWER_ON  1
#define C4GLTE_MODULE_POWER_OFF  0
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

    digital_out_t pwk;
    digital_out_t rts;

    // Input pins 

    digital_in_t sta;
    digital_in_t ri;
    digital_in_t cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} c4glte_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t sta;
    pin_name_t pwk;
    pin_name_t rts;
    pin_name_t ri;
    pin_name_t cts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} c4glte_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t c4glte_error_t;

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
void c4glte_cfg_setup ( c4glte_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param c4glte Click object.
 * @param cfg    Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C4GLTE_RETVAL c4glte_init ( c4glte_t *ctx, c4glte_cfg_t *cfg );

/**
 * @brief Power module.
 * 
 * @param c4glte      Click object.
 * @param power_state State of pin.
 */
void c4glte_module_power ( c4glte_t *ctx, uint8_t power_state );

/**
 * @brief Generic write function.
 * 
 * @param c4glte    Click object.
 * @param data_buf  Data buffer for sends.
 * @param len       Number of bytes for sends.
 */
void c4glte_generic_write ( c4glte_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param c4glte    Click object.
 * @param data_buf  Data buffer for read data.
 * @param max_len   The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
uint16_t c4glte_generic_read ( c4glte_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command.
 * 
 * @param c4glte  Click object.
 * @param command Command to be send.
 */
void c4glte_send_command ( c4glte_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _C4GLTE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
