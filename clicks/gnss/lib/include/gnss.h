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
 * \brief This file contains API for GNSS Click driver.
 *
 * \addtogroup gnss GNSS Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GNSS_H
#define GNSS_H

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
#define GNSS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.fon = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GNSS_RETVAL  uint8_t

#define GNSS_OK           0x00
#define GNSS_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define GNSS_NEMA_GPGGA 1
#define GNSS_NEMA_GPGLL 3
#define GNSS_NEMA_GPGGA_NUM_ELEMENT 15
#define GNSS_NEMA_GPGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define GNSS_GPGGA_TIME                      1 
#define GNSS_GPGGA_LATITUDE                  2
#define GNSS_GPGGA_LATITUDE_SIDE             3
#define GNSS_GPGGA_LONGITUDE                 4
#define GNSS_GPGGA_LONGITUDE_SIDE            5
#define GNSS_GPGGA_QUALITY_INDICATOR         6
#define GNSS_GPGGA_NUMBER_OF_SATELLITES      7
#define GNSS_GPGGA_H_DILUTION_OF_POS         8
#define GNSS_GPGGA_ALTITUDE                  9
#define GNSS_GPGGA_ALTITUDE_UNIT             10
#define GNSS_GPGGA_GEOIDAL_SEPARATION        11
#define GNSS_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define GNSS_GPGGA_TIME_SINCE_LAST_DGPS      13
#define GNSS_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define GNSS_GPGLL_LATITUDE                  1
#define GNSS_GPGLL_LATITUDE_SIDE             2
#define GNSS_GPGLL_LONGITUDE                 3
#define GNSS_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define GNSS_ERROR_COMMAND_OR_ELEMENT   0xFF
#define GNSS_ERROR_START_OR_END_COMMAND 0x8F
#define GNSS_ERROR_NEXT_ELEMENT         0x4F
#define GNSS_ERROR_CURRENT_ELEMENT      0x2F
#define GNSS_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 1000
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
    digital_out_t fon;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} gnss_t;

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
    pin_name_t fon;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} gnss_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t gnss_error_t;

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
void gnss_cfg_setup ( gnss_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gnss Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GNSS_RETVAL gnss_init ( gnss_t *ctx, gnss_cfg_t *cfg );

/**
 * @brief Wake-up or reset module.
 * @param gnss Click object.
 */
void gnss_module_wakeup ( gnss_t *ctx );

/**
 * @brief Set RST ( reset ) pin state.
 * @param gnss Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void gnss_set_rst_pin ( gnss_t *ctx, uint8_t state );

/**
 * @brief Set FON ( Force ON ) pin state.
 * @param gnss Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void gnss_set_fon_pin ( gnss_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 * @param gnss Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void gnss_generic_write ( gnss_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param gnss Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t gnss_generic_read ( gnss_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic parser function.
 * @param gnss Click object.
 * @param command NEMA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * @return error data
 */
gnss_error_t gnss_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

#ifdef __cplusplus
}
#endif
#endif  // _GNSS_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
