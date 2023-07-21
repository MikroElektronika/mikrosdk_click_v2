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
 * \brief This file contains API for Fiber Opt Click driver.
 *
 * \addtogroup fiberopt Fiber Opt Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FIBEROPT_H
#define FIBEROPT_H

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
#define FIBEROPT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FIBEROPT_OK                     0
#define FIBEROPT_ERROR                 -1
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define FIBEROPT_DRV_TX_BUFFER_SIZE     100
#define FIBEROPT_DRV_RX_BUFFER_SIZE     300
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
    // Modules 
    uart_t uart;
    
    uint8_t uart_rx_buffer[ FIBEROPT_DRV_RX_BUFFER_SIZE ];
    uint8_t uart_tx_buffer[ FIBEROPT_DRV_TX_BUFFER_SIZE ];
    
} fiberopt_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // static variable 
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.   

} fiberopt_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void fiberopt_cfg_setup ( fiberopt_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t fiberopt_init ( fiberopt_t *ctx, fiberopt_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Input data buffer
 * @param len          Number of the bytes in the data buffer
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function writes data.
 */
err_t fiberopt_generic_write ( fiberopt_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @param data_buf   Output data buffer.
 * @param len        Number of the bytes in data buffer.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @details This function reads data.
 */
err_t fiberopt_generic_read ( fiberopt_t *ctx, uint8_t *data_buf, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif  // _FIBEROPT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
