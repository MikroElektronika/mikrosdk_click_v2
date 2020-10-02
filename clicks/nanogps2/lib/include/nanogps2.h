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
 * \brief This file contains API for Nano GPS 2 Click driver.
 *
 * \addtogroup nanogps2 Nano GPS 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NANOGPS2_H
#define NANOGPS2_H

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
#define NANOGPS2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.wkp    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.fon    = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NANOGPS2_RETVAL  uint8_t

#define NANOGPS2_OK           0x00
#define NANOGPS2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define NANOGPS2_NEMA_GNGGA 1
#define NANOGPS2_NEMA_GPGLL 3
#define NANOGPS2_NEMA_GNGGA_NUM_ELEMENT 15
#define NANOGPS2_NEMA_GPGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define NANOGPS2_GNGGA_TIME                      1 
#define NANOGPS2_GNGGA_LATITUDE                  2
#define NANOGPS2_GNGGA_LATITUDE_SIDE             3
#define NANOGPS2_GNGGA_LONGITUDE                 4
#define NANOGPS2_GNGGA_LONGITUDE_SIDE            5
#define NANOGPS2_GNGGA_QUALITY_INDICATOR         6
#define NANOGPS2_GNGGA_NUMBER_OF_SATELLITES      7
#define NANOGPS2_GNGGA_H_DILUTION_OF_POS         8
#define NANOGPS2_GNGGA_ALTITUDE                  9
#define NANOGPS2_GNGGA_ALTITUDE_UNIT             10
#define NANOGPS2_GNGGA_GEOIDAL_SEPARATION        11
#define NANOGPS2_GNGGA_GEOIDAL_SEPARATION_UNIT   12
#define NANOGPS2_GNGGA_TIME_SINCE_LAST_DGPS      13
#define NANOGPS2_GNGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define NANOGPS2_GPGLL_LATITUDE                  1
#define NANOGPS2_GPGLL_LATITUDE_SIDE             2
#define NANOGPS2_GPGLL_LONGITUDE                 3
#define NANOGPS2_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define NANOGPS2_ERROR_COMMAND_OR_ELEMENT   0xFF
#define NANOGPS2_ERROR_START_OR_END_COMMAND 0x8F
#define NANOGPS2_ERROR_NEXT_ELEMENT         0x4F
#define NANOGPS2_ERROR_CURRENT_ELEMENT      0x2F
#define NANOGPS2_NO_ERROR                   0x00
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

    digital_out_t wkp;
    digital_out_t en;
    digital_out_t fon;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} nanogps2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t wkp;
    pin_name_t en;
    pin_name_t fon;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} nanogps2_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t nanogps2_error_t;

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
void nanogps2_cfg_setup ( nanogps2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx  Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NANOGPS2_RETVAL nanogps2_init ( nanogps2_t *ctx, nanogps2_cfg_t *cfg );

/**
 * @brief Generic function for setting fon pin status
 *
 * @param ctx             Click object.
 * @param state           state of the pin
 */
void nanogps2_set_fon_pin_state ( nanogps2_t *ctx, uint8_t state );

/**
 * @brief Generic function for setting wkp pin status
 *
 * @param ctx             Click object.
 * @param state           state of the pin
 */
void nanogps2_set_wkp_pin_state ( nanogps2_t *ctx, uint8_t state );

/**
 * @brief Generic function for setting en pin status
 *
 * @param ctx             Click object.
 * @param state           state of the pin
 */
void nanogps2_set_en_pin_state ( nanogps2_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 * 
 * @param nanogps2 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void nanogps2_generic_write ( nanogps2_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param nanogps2 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
uint16_t nanogps2_generic_read ( nanogps2_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Function for send command.
 *
 * @param ctx             Click object.
 * @param cmd             Command to be send.
 */
void nanogps2_send_cmd ( nanogps2_t *ctx, uint8_t *cmd );

/**
 * @brief Generic parser function.
 * 
 * @param rsp Response buffer.
 * @param command NEMA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * 
 * @return error data
 */
nanogps2_error_t nanogps2_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

#ifdef __cplusplus
}
#endif
#endif  // _NANOGPS2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
