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
 * \brief This file contains API for Microwave 2 Click driver.
 *
 * \addtogroup microwave2 Microwave 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MICROWAVE2_H
#define MICROWAVE2_H

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
#define MICROWAVE2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.da = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.dl = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MICROWAVE2_RETVAL  uint8_t

#define MICROWAVE2_OK           0x00
#define MICROWAVE2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */  

/**
 * \defgroup status  Status
 * \{
 */
#define MICROWAVE2_MOVING_AWAY       1
#define MICROWAVE2_MOVING_CLOSER     2
#define MICROWAVE2_STOPPED_MOVING    4
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
    // Input pins 

    digital_in_t da;
    digital_in_t dl;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    uint8_t internal_sync; //for syncronizing the parser with the incoming data
    uint8_t array_counter; //for setting of the position in the buffer
    uint8_t *address_holder; 

} microwave2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t da;
    pin_name_t dl;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.   

} microwave2_cfg_t;

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
void microwave2_cfg_setup ( microwave2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param microwave2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MICROWAVE2_RETVAL microwave2_init ( microwave2_t *ctx, microwave2_cfg_t *cfg );

/**
 * @brief Generic multi write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Input data buffer
 * @param len          Number of the bytes in the data buffer
 *
 * @description This function writes data.
 */
void microwave2_generic_multi_write ( microwave2_t *ctx, char *data_buf,  uint8_t len );

/**
 * @brief Generic multi read function.
 *
 * @param ctx        Click object.
 * @param data_buf   Output data buffer.
 * @param len        Number of the bytes in data buffer.
 *
 * @description This function reads data.
 */
void microwave2_generic_multi_read ( microwave2_t *ctx, char *data_buf,  uint8_t len );


/**
 * @brief Generic single read function.
 *
 * @param ctx        Click object.
 * @return one byte data
 *
 * @description This function read one byte data.
 */
char microwave2_generic_single_read ( microwave2_t *ctx );

/**
 * @brief Generic single write function.
 *
 * @param ctx          Click object.
 * @param tx_data      Input data 
 *
 * @description This function write one byte data.
 */
void microwave2_generic_single_write ( microwave2_t *ctx, char tx_data );

/** 
 * @brief Set pin DA 
 * 
 * @param ctx          Click object.
 * 
 * @description This pin will be set to 1 if the object is aproaching.
 */
uint8_t microwave2_da_state ( microwave2_t *ctx );

/** 
 * @brief Set pin DL 
 * 
 * @param ctx          Click object.
 * 
 * @description This pin will be set to 1 if the object is moving away.
 */
uint8_t microwave2_dl_state ( microwave2_t *ctx );

/** 
 * @brief Uart hendler
 * 
 * @param ctx          Click object.
 * @param packeg_buffer
 * @param r_data
 * 
 * @description This function will handle packet's that the click board is sending when
 * movement is detected.
 */
void microwave2_uart_handler ( microwave2_t *ctx, uint8_t *packeg_buffer, uint8_t r_data );

/** 
 * @brief Check trafic
 * 
 * @param ctx          Click object.
 * 
 * @descriptionFunction compares received packets and return's the value that 
 * can be compared to the predefined one to test if the object is 
 * aproaching, has stopped aproaching or moving away from the click board.
 */
uint8_t microwave2_check_trafic ( microwave2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MICROWAVE2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
