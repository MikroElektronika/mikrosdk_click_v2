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
 * \brief This file contains API for RS485 Isolator Click driver.
 *
 * \addtogroup rs485isolator RS485 Isolator Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RS485ISOLATOR_H
#define RS485ISOLATOR_H

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
#define RS485ISOLATOR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.re = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.de = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RS485ISOLATOR_OK                    0
#define RS485ISOLATOR_ERROR                -1
/** \} */

/**
 * \defgroup receiver_mode Receiver Enable/Disable
 * \{
 */
#define RS485ISOLATOR_RECEIVER_ENABLE       0
#define RS485ISOLATOR_RECEIVER_DISABLE      1
/** \} */

/**
 * \defgroup driver_mode Driver Enable/Disable
 * \{
 */
#define RS485ISOLATOR_DRIVER_ENABLE         1
#define RS485ISOLATOR_DRIVER_DISABLE        0
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define RS485ISOLATOR_DRV_RX_BUFFER_SIZE    200
#define RS485ISOLATOR_DRV_TX_BUFFER_SIZE    200
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
    digital_out_t re;
    digital_out_t de;

    // Modules 
    uart_t uart;

    uint8_t uart_rx_buffer[ RS485ISOLATOR_DRV_RX_BUFFER_SIZE ];
    uint8_t uart_tx_buffer[ RS485ISOLATOR_DRV_TX_BUFFER_SIZE ];

} rs485isolator_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 
    pin_name_t re;
    pin_name_t de;

    // static variable 
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} rs485isolator_cfg_t;

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
void rs485isolator_cfg_setup ( rs485isolator_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t rs485isolator_init ( rs485isolator_t *ctx, rs485isolator_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void rs485isolator_generic_write ( rs485isolator_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
err_t rs485isolator_generic_read ( rs485isolator_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief Set receiver state
 *
 * @param ctx          Click object.
 * @param state        Select state (Enable / Disable)
 */
void rs485isolator_set_receiver_mode ( rs485isolator_t *ctx, uint8_t state );

/**
 * @brief Set driver state
 *
 * @param ctx          Click object.
 * @param state        Select state (Enable / Disable)
 */
void rs485isolator_set_driver_mode ( rs485isolator_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _RS485ISOLATOR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
