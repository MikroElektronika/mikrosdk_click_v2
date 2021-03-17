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
 * \brief This file contains API for ATA663254 Click driver.
 *
 * \addtogroup ata663254 ATA663254 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ATA663254_H
#define ATA663254_H

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
#define ATA663254_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ATA663254_RETVAL  uint8_t

#define ATA663254_OK           0x00
#define ATA663254_INIT_ERROR   0xFF
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
    digital_out_t en;

    // Input pins 
    digital_in_t rst;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} ata663254_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

   //pin_name_t an;
    pin_name_t rst;
    pin_name_t en;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.  

} ata663254_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group
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
void ata663254_cfg_setup ( ata663254_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ata663254 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ATA663254_RETVAL ata663254_init ( ata663254_t *ctx, ata663254_cfg_t *cfg );

/**
 * @brief Generic multi write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Input data buffer
 * @param len          Number of the bytes in the data buffer
 *
 * @description This function writes data.
 */
void ata663254_generic_write ( ata663254_t *ctx, char *data_buf,  uint16_t len );

/**
 * @brief Generic multi read function.
 *
 * @param ctx        Click object.
 * @param data_buf   Output data buffer.
 * @param len        Number of the bytes in data buffer.
 *
 * @description This function reads data.
 */
int32_t ata663254_generic_read ( ata663254_t *ctx, char *data_buf,  uint16_t len );

/**
 * @brief Chip enable function.
 *
 * @param ctx          Click object.
 * @param state        0 - disable, 1 - enable
 *
 * @description This function enables or disables chip via Chip Select pin.
 */
void ata663254_enable ( ata663254_t *ctx, uint8_t state );

/**
 * @brief Undervoltage detect function.
 *
 * @param ctx          Click object.
 * 
 * @return Rst pin state    0 - undervoltage detected, 1 - undervoltage did not detect.
 *
 * @description This function returns 0 if undervoltage have detected, reset pin switched to 0.
 */
uint8_t ata663254_get_rst_state ( ata663254_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ATA663254_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
