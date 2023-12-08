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
 * \brief This file contains API for iqRF Click driver.
 *
 * \addtogroup iqrf iqRF Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IQRF_H
#define IQRF_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define IQRF_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX );  \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );  \
  cfg.adc     = MIKROBUS( mikrobus, MIKROBUS_AN );  \
  cfg.io      = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS );  \
  cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IQRF_RETVAL  uint8_t

#define IQRF_OK           0x00
#define IQRF_INIT_ERROR   0xFF
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

    digital_out_t io;
    digital_out_t cs;
    digital_out_t pwm;

    // Input pins 

    digital_in_t adc;
    digital_in_t int_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} iqrf_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t adc;
    pin_name_t io;
    pin_name_t cs;
    pin_name_t pwm;
    pin_name_t int_pin;

    // Static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.  

} iqrf_cfg_t;

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
void iqrf_cfg_setup ( iqrf_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param iqrf Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IQRF_RETVAL iqrf_init ( iqrf_t *ctx, iqrf_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for iqRF click.
 * @note
 *    Click default configuration:
 * -------------------------------
 * <pre>
 *    Hardware reset.
 * </pre>
 */
void iqrf_default_cfg ( iqrf_t *ctx );

/**
 * @brief Generic multi write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Input data buffer
 * @param len          Number of the bytes in the data buffer
 *
 * @description This function writes data.
 */
void iqrf_generic_multi_write ( iqrf_t *ctx, char *data_buf,  uint8_t len );

/**
 * @brief Generic multi read function.
 *
 * @param ctx        Click object.
 * @param data_buf   Output data buffer.
 * @param len        Number of the bytes in data buffer.
 *
 * @description This function reads data.
 */
void iqrf_generic_multi_read ( iqrf_t *ctx, char *data_buf,  uint8_t len );

/**
 * @brief Generic single read function.
 *
 * @param ctx          Click object.
 * @return one byte data
 *
 * @description This function read one byte data.
 */
char iqrf_generic_single_read ( iqrf_t *ctx );

/**
 * @brief Generic single write function.
 *
 * @param ctx          Click object.
 * @param tx_data      Input data 
 *
 * @description This function write one byte data.
 */
void iqrf_generic_single_write ( iqrf_t *ctx, char tx_data );

/**
 * @brief Interrupt function.
 *
 * @param ctx          Click object.
 * @return  INT pin state
 * ---------------------------------
 * <pre>
 *    0 - No active interrupt.
 * </pre>
 * 
 * <pre>
 *    1 - Active interrupt.
 * </pre>
 *
 * @description This function checks if interrupt is active.
 */
uint8_t iqrf_get_interrupt ( iqrf_t *ctx );

/**
 * @brief Hardware reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function performs hardware reset.
 */
void iqrf_hw_reset ( iqrf_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _IQRF_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
