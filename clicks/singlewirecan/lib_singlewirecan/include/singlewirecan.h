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
 * \brief This file contains API for Single Wire CAN Click driver.
 *
 * \addtogroup singlewirecan Single Wire CAN Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SINGLEWIRECAN_H
#define SINGLEWIRECAN_H

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
#define SINGLEWIRECAN_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.md0     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.md1     = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SINGLEWIRECAN_RETVAL  uint8_t

#define SINGLEWIRECAN_OK                                              0x00
#define SINGLEWIRECAN_INIT_ERROR                                      0xFF
/** \} */

/**
 * \defgroup operating_mode Operating Mode Settings
 * \{
 */
#define SINGLEWIRECAN_OPERATING_MODE_SLEEP                            0x00
#define SINGLEWIRECAN_OPERATING_MODE_HIGH_SPEED                       0x01
#define SINGLEWIRECAN_OPERATING_MODE_HIGH_VOLTAGE_WAKE_UP             0x02
#define SINGLEWIRECAN_OPERATING_MODE_NORMAL                           0x03
/** \} */

/**
 * \defgroup pin_state_settings Pin State Settings 
 * \{
 */
#define SINGLEWIRECAN_PIN_STATE_LOW                                   0x00
#define SINGLEWIRECAN_PIN_STATE_HIGH                                  0x01
/** \} */

/**
 * \defgroup end_buffer End Buffer
 * \{
 */
#define SINGLEWIRECAN_END_BUFF                                        0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE                                            500
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

    digital_out_t md0;
    digital_out_t md1;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} singlewirecan_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t md0;
    pin_name_t md1;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} singlewirecan_cfg_t;

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
 *
 * @note All used pins will be set to unconnected state.
 */
void singlewirecan_cfg_setup ( singlewirecan_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SINGLEWIRECAN_RETVAL singlewirecan_init ( singlewirecan_t *ctx, singlewirecan_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx         Click object.
 * @param data_buf    Data buffer for send.
 * @param len         Number of bytes for send.
 *
 * @description This function write specified number of bytes
 */
void singlewirecan_generic_write ( singlewirecan_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.

 * @param ctx         Click object.
 * @param data_buf    Data buffer for read data.
 * @param max_len     The maximum length of data that can be read.
 *
 * @returns Number of read data.
 *
 * @description This function reads a desired number of data bytes.
 */
int32_t singlewirecan_generic_read ( singlewirecan_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Sets MD0 pin state
 *
 * @param ctx       Click object. 
 * @param cs_state  Pin state
 *
 * @description The function set MD0 ( RST ) pin to high or low state.
 */
void singlewirecan_set_md_0_pin_state ( singlewirecan_t *ctx, uint8_t rst_state );

/**
 * @brief Sets MD1 pin state
 *
 * @param ctx       Click object. 
 * @param cs_state  Pin state
 *
 * @description The function set MD1 ( CS ) pin to high or low state.
 */
void singlewirecan_set_md_1_pin_state ( singlewirecan_t *ctx, uint8_t cs_state );

/**
 * @brief Set operating mode function
 *
 * @param ctx     Click object. 
 * @param op_mode
 * <pre>
 * - 0x00 ( ONEWIRECAN_OPERATING_MODE_SLEEP )                : Sleep mode;
 * - 0x01 ( ONEWIRECAN_OPERATING_MODE_HIGH_SPEED )           : High-Speed mode;
 * - 0x02 ( ONEWIRECAN_OPERATING_MODE_HIGH_VOLTAGE_WAKE_UP ) : Wake_Up mode;
 * - 0x03 ( ONEWIRECAN_OPERATING_MODE_NORMAL )               : Normal mode;
 * </pre>
 *
 * @description The function set desired operating mode of NCV7356 Single Wire CAN Transceiver
 *              on One-Wire CAN Click board.
 */
void singlewirecan_set_operating_mode ( singlewirecan_t *ctx, uint8_t op_mode );

#ifdef __cplusplus
}
#endif
#endif  // _SINGLEWIRECAN_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
