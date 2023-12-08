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
 * \brief This file contains API for Barcode Click driver.
 *
 * \addtogroup barcode Barcode Click Driver
 * \{
 */
// ----------------------------------------------------------------------------

#ifndef BARCODE_H
#define BARCODE_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
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
#define BARCODE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.trg = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BARCODE_RETVAL  int8_t

#define BARCODE_OK            0
#define BARCODE_INIT_ERROR  (-1)
/** \} */

/**
 * \defgroup logic_state  Logic state
 * \{
 */
#define BARCODE_LOGIC_ON       0x00
#define BARCODE_LOGIC_OFF      0x01
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

    char uart_rx_buffer[ 300 ];
    char uart_tx_buffer[ 300 ];

} barcode_t;

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

} barcode_cfg_t;

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
void barcode_cfg_setup ( barcode_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param barcode Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BARCODE_RETVAL barcode_init ( barcode_t *ctx, barcode_cfg_t *cfg );

/**
 * @brief Set WKP ( wake-up ) pin state.
 * @param barcode Click object.
 * @param statte Pin state ( 1 or 0 ).
 */
void barcode_enable_scaning ( barcode_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 * @param barcode Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void barcode_generic_write ( barcode_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param barcode Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
uint16_t barcode_generic_read ( barcode_t *ctx, char *data_buf, uint16_t max_len );

#ifdef __cplusplus
}
#endif
#endif  // BARCODE_H

/** \} */ // End public_function group
/** \} */ // End click Driver group

// ------------------------------------------------------------------------ END
