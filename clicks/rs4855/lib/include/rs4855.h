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
 * \brief This file contains API for RS485 5 Click driver.
 *
 * \addtogroup rs4855 RS485 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RS4855_H
#define RS4855_H

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
#define RS4855_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.de = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.re = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RS4855_RETVAL  uint8_t

#define RS4855_OK           0x00
#define RS4855_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define RS4855_NEMA_GPGGA 1
#define RS4855_NEMA_GPGLL 3
#define RS4855_NEMA_GPGGA_NUM_ELEMENT 15
#define RS4855_NEMA_GPGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define RS4855_GPGGA_TIME                      1 
#define RS4855_GPGGA_LATITUDE                  2
#define RS4855_GPGGA_LATITUDE_SIDE             3
#define RS4855_GPGGA_LONGITUDE                 4
#define RS4855_GPGGA_LONGITUDE_SIDE            5
#define RS4855_GPGGA_QUALITY_INDICATOR         6
#define RS4855_GPGGA_NUMBER_OF_SATELLITES      7
#define RS4855_GPGGA_H_DILUTION_OF_POS         8
#define RS4855_GPGGA_ALTITUDE                  9
#define RS4855_GPGGA_ALTITUDE_UNIT             10
#define RS4855_GPGGA_GEOIDAL_SEPARATION        11
#define RS4855_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define RS4855_GPGGA_TIME_SINCE_LAST_DGPS      13
#define RS4855_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define RS4855_GPGLL_LATITUDE                  1
#define RS4855_GPGLL_LATITUDE_SIDE             2
#define RS4855_GPGLL_LONGITUDE                 3
#define RS4855_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define RS4855_ERROR_COMMAND_OR_ELEMENT   0xFF
#define RS4855_ERROR_START_OR_END_COMMAND 0x8F
#define RS4855_ERROR_NEXT_ELEMENT         0x4F
#define RS4855_ERROR_CURRENT_ELEMENT      0x2F
#define RS4855_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

#define RS4855_PIN_STATE_HIGH              1
#define RS4855_PIN_STATE_LOW               0

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

    digital_out_t de;
    digital_out_t re;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} rs4855_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t de;
    pin_name_t re;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} rs4855_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t rs4855_error_t;

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
void rs4855_cfg_setup ( rs4855_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RS4855_RETVAL rs4855_init ( rs4855_t *ctx, rs4855_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void rs4855_generic_write ( rs4855_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t rs4855_generic_read ( rs4855_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Sets DE pin to high or low state
 * @param ctx Click object.
 * @param state  pin state
 */
void rs4855_set_de_state( rs4855_t *ctx, uint8_t state );

/**
 * @brief Sets RE pin to high or low state
 * @param ctx Click object.
 * @param state  pin state
 */
void rs4855_set_re_state( rs4855_t *ctx, uint8_t state );

/**
 * @brief Function for sending byte by byte
 * @param ctx Click object.
 * @param command command/data to be sent
 */
void rs4855_send_byte_by_byte ( rs4855_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _RS4855_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
