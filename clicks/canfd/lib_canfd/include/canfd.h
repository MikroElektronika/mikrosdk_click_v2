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
 * \brief This file contains API for CAN FD Click driver.
 *
 * \addtogroup canfd CAN FD Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CANFD_H
#define CANFD_H

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
#define CANFD_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.stb = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.wke = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.err = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CANFD_RETVAL  uint8_t

#define CANFD_OK           0x00
#define CANFD_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup pin_state   Pin State
 * \{
 */
#define CANFD_PIN_STATE_ENABLE                                      0x01
#define CANFD_PIN_STATE_DISABLE                                     0x00
#define CANFD_NULL                                                  0x00
/** \} */

/**
 * \defgroup operation_mode   Operation Mode
 * \{
 */
#define CANFD_OPERATING_MODE_NORMAL                                 0
#define CANFD_OPERATING_MODE_RECEIVE                                1
#define CANFD_OPERATING_MODE_STAND_BY                               2
#define CANFD_OPERATING_MODE_SLEEP                                  3
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

    digital_out_t stb;
    digital_out_t en;

    // Input pins 

    digital_in_t wke;
    digital_in_t err;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} canfd_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t stb;
    pin_name_t en;
    pin_name_t wke;
    pin_name_t err;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} canfd_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t canfd_error_t;

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
void canfd_cfg_setup ( canfd_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
CANFD_RETVAL canfd_init ( canfd_t *ctx, canfd_cfg_t *cfg );

/**
 * @brief Set WKE ( wake-up ) pin state.
 * 
 * @param ctx Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void canfd_set_wke_pin ( canfd_t *ctx, uint8_t state );

/**
 * @brief Set RST ( reset ) pin state.
 * @param ctx Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void canfd_set_stb_pin ( canfd_t *ctx, uint8_t state );

/**
 * @brief Set ERR ( INT ) pin state.
 * 
 * @param ctx Click object.
 * @param state Pin state ( 1 or 0 ).
 */
uint8_t canfd_get_err_pin ( canfd_t *ctx );

/**
 * @brief Set STB ( RST ) pin state.
 * 
 * @param ctx Click object.
 * @param stb_state Pin state ( 1 or 0 ).
 */
void canfd_set_stand_by_stb_pin ( canfd_t *ctx, uint8_t stb_state );

/**
 * @brief Set EN ( CS ) pin state.
 * 
 * @param ctx Click object.
 * @param stb_state Pin state ( 1 or 0 ).
 */
void canfd_set_mode_en_pin ( canfd_t *ctx, uint8_t en_state );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void canfd_generic_write ( canfd_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t canfd_generic_read ( canfd_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Operation mode.
 * 
 * @param ctx      Click object.
 * @param op_mode  Mode.
 */
void canfd_set_operating_mode ( canfd_t *ctx, uint8_t op_mode );

#ifdef __cplusplus
}
#endif
#endif  // _CANFD_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
