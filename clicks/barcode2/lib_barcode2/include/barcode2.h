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
 * \brief This file contains API for Barcode 2 Click driver.
 *
 * \addtogroup barcode2 Barcode 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BARCODE2_H
#define BARCODE2_H

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
#define BARCODE2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.trg = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BARCODE2_RETVAL  uint8_t

#define BARCODE2_OK             0x00
#define BARCODE2_INIT_ERROR     0xFF
/** \} */

/**
 * \defgroup enable_and_disable_state Enable And Disable State
 * \{
 */
#define BARCODE2_DISABLE        0x01
#define BARCODE2_ENABLE         0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE      600
#define DRV_TX_BUFFER_SIZE      50
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
    digital_out_t trg;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} barcode2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t trg;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} barcode2_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t barcode2_error_t;

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
void barcode2_cfg_setup ( barcode2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BARCODE2_RETVAL barcode2_init ( barcode2_t *ctx, barcode2_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx       Click object.
 * @param data_buf  Data buffer for sends.
 * @param len       Number of bytes for sends.
 *
 * @description This function write desired number of bytes.
 */
void barcode2_generic_write ( barcode2_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx       Click object.
 * @param data_buf  Data buffer for read data.
 * @param max_len   The maximum length of data that can be read.
 * @return Number of reads data.
 *
 * @description This function read maximum length of data.
 */
int32_t barcode2_generic_read ( barcode2_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Enable scaning function
 *
 * @param ctx       Click object. 
 * @param en_state 
 * <pre>    
 * - 0x00 ( LOW )  : Enable.
 * - 0x01 ( HIGH ) : Disable.
 * </pre>  
 *
 * @description The function enables or disables barcode scaning
 *              depending on state parametar value.
 */
void barcode2_enable_scaning ( barcode2_t *ctx, uint8_t en_state );

/**
 * @brief Enable reset function
 *
 * @param ctx       Click object.  
 * @param en_state
 * <pre> 
 * - 0x00 ( LOW )  : Enable.
 * - 0x01 ( HIGH ) : Disable. 
 * </pre>  
 *
 * @description The function enables or disables barcode scaner reset 
 *              depending on state parametar value.
 */
void barcode2_enable_reset ( barcode2_t *ctx, uint8_t en_state );


#ifdef __cplusplus
}
#endif
#endif  // _BARCODE2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
