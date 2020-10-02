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
 * \brief This file contains API for USB UART Click driver.
 *
 * \addtogroup usbuart USB UART Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef USBUART_H
#define USBUART_H

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
#define USBUART_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.slp = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define USBUART_RETVAL  uint8_t

#define USBUART_OK           0x00
#define USBUART_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/**
 * \defgroup power_mode Power Mode
 * \{
 */
#define USBUART_POWER_ON  1
#define USBUART_POWER_OFF 0
/** \} */

/**
 * \defgroup cts_state CTS State
 * \{
 */
#define USBUART_CTS_ACTIVE  1
#define USBUART_CTS_NO_ACTIVE 0
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define USBUART_MODE_SLEEP 1
#define USBUART_MODE_NORMAL 0
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
    digital_out_t slp;
    digital_out_t pwr;

    // Input pins 

    digital_in_t rts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} usbuart_t;

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
    pin_name_t slp;
    pin_name_t pwr;
    pin_name_t rts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} usbuart_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t usbuart_error_t;

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
void usbuart_cfg_setup ( usbuart_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param usbuart Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
USBUART_RETVAL usbuart_init ( usbuart_t *ctx, usbuart_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param usbuart Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void usbuart_generic_write ( usbuart_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param usbuart Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
uint16_t usbuart_generic_read ( usbuart_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Power control.
 *
 * @param ctx        Click object.
 * @param state      PWR pin state
 */
void usbuart_pwr_ctrl ( usbuart_t *ctx, uint8_t state );

/**
 * @brief Set CTS (Clear to send)
 *
 * @param ctx        Click object.
 * @param state      CTS pin state
 */
void usbuart_set_cts ( usbuart_t *ctx, uint8_t state );

/**
 * @brief Set device mode
 *
 * @param ctx        Click object.
 * @param mode       Device mode (Sleep or Normal)
 */
void usbuart_set_mode ( usbuart_t *ctx, uint8_t mode );

/**
 * @brief Set device mode
 *
 * @param ctx        Click object.
 * @return RTS (Request to send) pin state
 */
uint8_t usbuart_get_rts ( usbuart_t *ctx );

/**
 * @brief Function for send command
 *
 * @param ctx        Click object.
 * @param command    Data to be send.
 */
void usbuart_send_command ( usbuart_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _USBUART_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
