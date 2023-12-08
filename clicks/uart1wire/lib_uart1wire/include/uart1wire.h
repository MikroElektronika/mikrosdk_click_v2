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
 * \brief This file contains API for UART 1-Wire Click driver.
 *
 * \addtogroup uart1wire UART 1-Wire Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UART1WIRE_H
#define UART1WIRE_H

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
#define UART1WIRE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UART1WIRE_RETVAL  uint8_t

#define UART1WIRE_OK      0
#define UART1WIRE_ERROR   -1
/** \} */

/**
 * \defgroup init_cfg Initialization & Configuration
 * \{
 */
#define UART1WIRE_COMMAND_MODE                  0xE3
#define UART1WIRE_DATA_MODE                     0xE1
#define UART1WIRE_RESET                         0xC1
#define UART1WIRE_SKIP_ROM                      0xCC
#define UART1WIRE_CONVERT_TEMPERATURE           0x44
#define UART1WIRE_READ_SCRATCHPAD               0xBE
#define UART1WIRE_READ_SEQ                      0xFF
#define UART1WIRE_TEMP_SENSOR_RESOLUTION_12BIT  12
#define UART1WIRE_TEMP_SENSOR_RESOLUTION_11BIT  11
#define UART1WIRE_TEMP_SENSOR_RESOLUTION_10BIT  10
#define UART1WIRE_TEMP_SENSOR_RESOLUTION_9BIT   9
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 300
#define DRV_TX_BUFFER_SIZE 100
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

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} uart1wire_t;

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

} uart1wire_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t uart1wire_error_t;

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
void uart1wire_cfg_setup ( uart1wire_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param uart1wire Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UART1WIRE_RETVAL uart1wire_init ( uart1wire_t *ctx, uart1wire_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param uart1wire Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void uart1wire_generic_write ( uart1wire_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param uart1wire Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t uart1wire_generic_read ( uart1wire_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Write command function.
 *
 * @param ctx   Click object.
 * @param cmd   Command value.
 *
 * @description This function sends an 8-bit command to the click module.
 */
void uart1wire_write_command ( uart1wire_t *ctx, uint8_t cmd );

/**
 * @brief Read byte function.
 *
 * @param ctx   Click object.
 *
 * @return    Read data byte.
 * 
 * @description This function reads one byte of data from the click module.
 */
uint8_t uart1wire_read_byte ( uart1wire_t *ctx );

/**
 * @brief Reset function.
 *
 * @param ctx   Click object.
 *
 * @description This function sends a reset pulse signal.
 */
void uart1wire_reset ( uart1wire_t *ctx );

/**
 * @brief Read data function.
 *
 * @param ctx   Click object.
 * @param data_out Data buffer for read data.
 * @param num_bytes The maximum length of data that can be read.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @description This function reads a desired number of data bytes from the click module.
 */
int8_t uart1wire_read_data ( uart1wire_t *ctx, uint8_t *data_out, uint8_t num_bytes );

/**
 * @brief Read temperature function.
 *
 * @param ctx   Click object.
 * @param temperature Temperature data.
 * @param resolution Temperature sensor resolution.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * @description This function reads the temperature from DALLAS one wire temperature sensors.
 */
int8_t uart1wire_read_temperature ( uart1wire_t *ctx, float *temperature, uint8_t resolution );

#ifdef __cplusplus
}
#endif
#endif  // _UART1WIRE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
