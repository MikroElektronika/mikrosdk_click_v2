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
 * \brief This file contains API for CAN FD 5 Click driver.
 *
 * \addtogroup canfd5 CAN FD 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CANFD5_H
#define CANFD5_H

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
#define CANFD5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CANFD5_RETVAL  uint8_t

#define CANFD5_OK           0x00
#define CANFD5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/**
 * \defgroup pin_state  Pin state
 * \{
 */
#define CANFD5_PIN_STATE_DISABLE             0x00
#define CANFD5_PIN_STATE_ENABLE              0x01
/** \} */
 
/**
 * \defgroup operating_mode  Operating mode
 * \{
 */
#define CANFD5_OPERATING_MODE_NORMAL         0x00
#define CANFD5_OPERATING_MODE_STAND_BY       0x01
#define CANFD5_OPERATING_MODE_SLEEP          0x02
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

    digital_out_t cs;
    digital_out_t pwm;


    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} canfd5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t cs;
    pin_name_t pwm;
    pin_name_t int_pin;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} canfd5_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t canfd5_error_t;

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
void canfd5_cfg_setup ( canfd5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param canfd5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CANFD5_RETVAL canfd5_init ( canfd5_t *ctx, canfd5_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param canfd5 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void canfd5_generic_write ( canfd5_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t canfd5_generic_read ( canfd5_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Set SLP pin state function
 *
 * @param ctx Click object.
 * @param stb_state
 * - 0 ( CANFD5_PIN_STATE_DISABLE ) : Disable.
 * - 1 ( CANFD5_PIN_STATE_ENABLE )  : Enable.
 *
 * @description This function set state of the SLP ( CS ) pin
 * of UJA1162A Self-supplied high-speed CAN transceiver on CAN FD 5 click board.
 */
void canfd5_set_slp_pin_state ( canfd5_t *ctx, uint8_t slp_state );

/**
 * @brief Set WAK pin state function
 *
 * @param ctx Click object.
 * @param stb_state
 * - 0 ( CANFD5_PIN_STATE_DISABLE ) : Disable.
 * - 1 ( CANFD5_PIN_STATE_ENABLE )  : Enable.
 *
 * @description This function set state of the WAK ( PWM ) pin
 * of UJA1162A Self-supplied high-speed CAN transceiver on CAN FD 5 click board.
 */
void canfd5_set_wak_pin_state ( canfd5_t *ctx, uint8_t wak_state );

/**
 * @brief Set WAK pin state function
 *
 * @param ctx Click object.
 * 
 * @return
 * state of the CTS ( INT ) pin.
 *
 * @description This function get state of the CTS ( INT ) pin
 * of UJA1162A Self-supplied high-speed CAN transceiver on CAN FD 5 click board.
 */
uint8_t canfd5_get_cts_pin_state ( canfd5_t *ctx );

/**
 * @brief Set normal operating mode function
 *
 * @param ctx Click object.
 * 
 * @description This function set normal operating mode
 * of UJA1162A Self-supplied high-speed CAN transceiver on CAN FD 5 click board.
 */
void canfd5_set_normal_operating_mode ( canfd5_t *ctx );

/**
 * @brief Set stand-by operating mode function
 *
 * @param ctx Click object.
 * 
 * @description This function set stand-by operating mode
 * of UJA1162A Self-supplied high-speed CAN transceiver on CAN FD 5 click board.
 */
void canfd5_set_standby_operating_mode ( canfd5_t *ctx );

/**
 * @brief Set sleep operating mode function
 *
 * @param ctx Click object.
 * 
 * @description This function set sleep operating mode
 * of UJA1162A Self-supplied high-speed CAN transceiver on CAN FD 5 click board.
 */
void canfd5_set_sleep_operating_mode ( canfd5_t *ctx );

/**
 * @brief Set operating mode function
 *
 * @param ctx Click object.
 * @param op_mode
 * - 0 ( CANFD5_OPERATING_MODE_NORMAL )   : Normal mode;
 * - 1 ( CANFD5_OPERATING_MODE_STAND_BY ) : Stand-by mode;
 * - 2 ( CANFD5_OPERATING_MODE_SLEEP )    : Sleep mode;
 *
 * @description This function set desired operating mode
 * of UJA1162A Self-supplied high-speed CAN transceiver on CAN FD 5 click board.
 */
void canfd5_set_operating_mode ( canfd5_t *ctx, uint8_t op_mode );

#ifdef __cplusplus
}
#endif
#endif  // _CANFD5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
