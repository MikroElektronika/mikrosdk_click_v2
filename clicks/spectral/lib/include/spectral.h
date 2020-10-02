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
 * \brief This file contains API for Spectral Click driver.
 *
 * \addtogroup spectral Spectral Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SPECTRAL_H
#define SPECTRAL_H

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
#define SPECTRAL_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SPECTRAL_RETVAL  uint8_t

#define SPECTRAL_OK           0x00
#define SPECTRAL_INIT_ERROR   0xFF
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

    digital_out_t rst;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} spectral_t;

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
    pin_name_t int_pin;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} spectral_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t spectral_error_t;

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
void spectral_cfg_setup ( spectral_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param spectral Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SPECTRAL_RETVAL spectral_init ( spectral_t *ctx, spectral_cfg_t *cfg );

/**
 * @brief Reset module.
 * 
 * @param spectral Click object.
 */
void spectral_module_reset ( spectral_t *ctx );

/**
 * @brief Generic write function.
 * 
 * @param spectral Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
uint16_t spectral_uart_write ( spectral_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param spectral Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t spectral_uart_read ( spectral_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send Command
 *
 * @param command          pointer to command string
 */
void spectral_send_command ( spectral_t *ctx, char *command );

/**
 * @brief Read calibrated X, Y, and Z color data.
 *
 * @param rsp            pointer to buffer
 * @param xyz_data       pointer to the buffer in which will be written
 *
 */
void spectral_get_color_data ( uint8_t *rsp, uint8_t *xyz_data );

/**
 * @brief Read raw X, Y, and Z data.
 *
 * @param rsp             pointer to buffer
 * @param xyzr_data       pointer to the buffer in which will be written
 */
void spectral_get_xyz_data ( uint8_t *rsp, uint8_t *xyzr_data );

/**
 * @brief Read calibrated x and y for CIE 1931 color gamut.
 *
 * @param rsp           pointer to buffer
 * @param xy_data       pointer to the buffer in which will be written
 */
void spectral_get_xy_small_data ( uint8_t *rsp, uint8_t *xy_data );

/**
 * @brief Read the calibrated LUX value from the sensor.
 *
 * @param rsp             pointer to buffer
 *
 * @return lux value
 */
uint8_t spectral_get_lux_data ( uint8_t *rsp );

/**
 * @brief Read the calibrated CCT value from the sensor.
 *
 * @param rsp             pointer to buffer
 *
 * @return cct value
 */
uint8_t spectral_get_cct_data ( uint8_t *rsp );

/**
 * @brief Read calibrated u�, v� and u, v for CIE 1976 color gamut.
 *
 * @param rsp            pointer to buffer
 * @param uv_data        pointer to the buffer in which will be written
 */
void spectral_get_uv_data ( uint8_t *rsp, uint16_t *uv_data);

/**
 * @brief Read raw X, Y, Z and NIR data as well as two special internal registers D, & C.
 *
 * @param rsp            pointer to buffer
 * @param c_data         pointer to the buffer in which will be written
 */
void spectral_get_data ( char *rsp, uint16_t *c_data );

/**
 * @brief Read calibrated Duv for CIE 1976-color gamut.
 *
 * @param rsp             pointer to buffer
 *
 * @return duv value
 */
uint8_t spectral_get_duv_data ( uint8_t *rsp );

#ifdef __cplusplus
}
#endif
#endif  // _SPECTRAL_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
