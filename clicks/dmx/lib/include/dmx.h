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
 * \brief This file contains API for DMX Click driver.
 *
 * \addtogroup dmx DMX Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DMX_H
#define DMX_H

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
#define DMX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.abr = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.run = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DMX_RETVAL  uint8_t

#define DMX_OK           0x00
#define DMX_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup dmx_cmd DMX Commands
 * \{
 */
#define DMX_SLAVE               0
#define DMX_MASTER              1

#define DMX_CONFIG_MODE         0
#define DMX_RUN_MODE            1

#define DMX_INT_INACTIVE        0
#define DMX_INT_ACTIVE          1

#define DMX_RSP_NOT_READY       0
#define DMX_RSP_READY           1

#define DMX_CMD_RSP             1
#define DMX_DATA_RSP            2
/** \} */

#define END_BUFF               0
#define DMX_MASTER_USER_CTRL   0
#define DMX_MASTER_DEMO_CTRL   1

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

    digital_out_t rst;
    digital_out_t abr;
    digital_out_t run;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} dmx_t;

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
    pin_name_t abr;
    pin_name_t run;
    pin_name_t int_pin;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} dmx_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t dmx_error_t;

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
void dmx_cfg_setup ( dmx_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DMX_RETVAL dmx_init ( dmx_t *ctx, dmx_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Dmx click.
 */
void dmx_default_cfg ( dmx_t *ctx );

/**
 * @brief Reset function.
 * @param ctx Click object.
 */
void dmx_reset ( dmx_t *ctx, uint8_t dev_mode );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void dmx_generic_write ( dmx_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
uint16_t dmx_generic_read ( dmx_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Mode Setting function
 * @param ctx Click object.
 * @param run_mode <pre>
 *                    0 - config mode
 *                    1 - run mode
 *                 </pre>
 * 
 * @description This function allows user to put device in config or run mode.
 * @note Config mode must be set when user wants to execute device configuration.
 *       When run mode is set, the data transfer is started.
 */
void dmx_run ( dmx_t *ctx, uint8_t run_mode );

/**
 * @brief Interrupt Check function
 * @param ctx Click object.
 * @returns <pre>
 *            0 - inactive state
 *            1 - active state
 *          </pre>
 *
 * @description This function checks the interrupt state.
 */
uint8_t dmx_check_int ( dmx_t *ctx );

/**
 * @brief Auto Baud Rate Setting function
 * @param ctx Click object.
 * 
 * @description This function sets auto (default) baud rate.
 * @note The default baud rate is 115200 bps.
 */
void dmx_auto_baud_rate ( dmx_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DMX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
