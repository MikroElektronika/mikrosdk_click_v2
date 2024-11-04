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
 * \brief This file contains API for Touchkey 2 Click driver.
 *
 * \addtogroup touchkey2 Touchkey 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TOUCHKEY2_H
#define TOUCHKEY2_H

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
#define TOUCHKEY2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.pc5_target_reset = MIKROBUS( mikrobus, MIKROBUS_RST ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TOUCHKEY2_RETVAL  uint8_t

#define TOUCHKEY2_OK           0x00
#define TOUCHKEY2_INIT_ERROR   0xFF
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

    digital_out_t pc5_target_reset;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];    

} touchkey2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    pin_name_t pc5_target_reset;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.  

} touchkey2_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void touchkey2_cfg_setup ( touchkey2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param touchkey2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
TOUCHKEY2_RETVAL touchkey2_init ( touchkey2_t *ctx, touchkey2_cfg_t *cfg );

/**
 * @brief Generic multi write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Input data buffer
 * @param len          Number of the bytes in the data buffer
 *
 * @description This function writes data.
 */
void touchkey2_generic_multi_write ( touchkey2_t *ctx, char *data_buf,  uint8_t len );

/**
 * @brief Generic multi read function.
 *
 * @param ctx        Click object.
 * @param data_buf   Output data buffer.
 * @param len        Number of the bytes in data buffer.
 *
 * @description This function reads data.
 */
void touchkey2_generic_multi_read ( touchkey2_t *ctx, char *data_buf,  uint8_t len );

/**
 * @brief Generic single read function.
 *
 * @param ctx        Click object.
 * @return one byte data
 *
 * @description This function read one byte data.
 */
char touchkey2_generic_single_read ( touchkey2_t *ctx );

/**
 * @brief Generic single write function.
 *
 * @param ctx          Click object.
 * @param tx_data      Input data 
 *
 * @description This function write one byte data.
 */
void touchkey2_generic_single_write ( touchkey2_t *ctx, char tx_data );

/**
 * @brief Set reset pin function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to set the reset pin.
 */
void touchkey2_set_reset_pin ( touchkey2_t *ctx );

/**
 * @brief Clear reset pin function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to clear the reset pin.
 */
void touchkey2_clear_reset_pin ( touchkey2_t *ctx );

/**
 * @brief Reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to reset the device.
 */
void touchkey2_target_reset ( touchkey2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TOUCHKEY2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
