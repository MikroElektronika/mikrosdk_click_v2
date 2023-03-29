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
 * \brief This file contains API for GPS Click driver.
 *
 * \addtogroup gps GPS Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GPS_H
#define GPS_H

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
#define GPS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.reset = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.tmpls = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GPS_RETVAL  uint8_t

#define GPS_OK           0x00
#define GPS_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define GPS_NEMA_GPGGA 1
#define GPS_NEMA_GPGLL 3
#define GPS_NEMA_GPGGA_NUM_ELEMENT 15
#define GPS_NEMA_GPGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define GPS_GPGGA_TIME                      1 
#define GPS_GPGGA_LATITUDE                  2
#define GPS_GPGGA_LATITUDE_SIDE             3
#define GPS_GPGGA_LONGITUDE                 4
#define GPS_GPGGA_LONGITUDE_SIDE            5
#define GPS_GPGGA_QUALITY_INDICATOR         6
#define GPS_GPGGA_NUMBER_OF_SATELLITES      7
#define GPS_GPGGA_H_DILUTION_OF_POS         8
#define GPS_GPGGA_ALTITUDE                  9
#define GPS_GPGGA_ALTITUDE_UNIT             10
#define GPS_GPGGA_GEOIDAL_SEPARATION        11
#define GPS_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define GPS_GPGGA_TIME_SINCE_LAST_DGPS      13
#define GPS_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define GPS_GPGLL_LATITUDE                  1
#define GPS_GPGLL_LATITUDE_SIDE             2
#define GPS_GPGLL_LONGITUDE                 3
#define GPS_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define GPS_ERROR_COMMAND_OR_ELEMENT   0xFF
#define GPS_ERROR_START_OR_END_COMMAND 0x8F
#define GPS_ERROR_NEXT_ELEMENT         0x4F
#define GPS_ERROR_CURRENT_ELEMENT      0x2F
#define GPS_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 600
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
    // Output pins 

    digital_out_t reset;

    // Input pins 

    digital_in_t tmpls;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} gps_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t reset;
    pin_name_t tmpls;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} gps_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t gps_error_t;

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
void gps_cfg_setup ( gps_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gps Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GPS_RETVAL gps_init ( gps_t *ctx, gps_cfg_t *cfg );

/**
 * @brief Wake-up module.
 * @param gps Click object.
 */
void gps_module_wakeup ( gps_t *ctx );

/**
 * @brief Set RST ( reset ) pin state.
 * @param gps Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void gps_set_rst_pin ( gps_t *ctx, uint8_t state );

/**
 * @brief uint8_t gps_get_tmpls_pin ( gps_t *ctx );
 * @param gps Click object.
 * @return current pin state.
 */
uint8_t gps_get_tmpls_pin ( gps_t *ctx );

/**
 * @brief Generic write function.
 * @param gps Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void gps_generic_write ( gps_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param gps Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t gps_generic_read ( gps_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic parser function.
 * @param gps Click object.
 * @param command NEMA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * @return error data
 */
gps_error_t gps_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

#ifdef __cplusplus
}
#endif
#endif  // _GPS_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
