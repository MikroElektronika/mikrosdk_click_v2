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
 * \brief This file contains API for GNSS7 Click driver.
 *
 * \addtogroup gnss7 GNSS7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GNSS7_H
#define GNSS7_H

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
#define GNSS7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.sel = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.exi = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.pls = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GNSS7_RETVAL  uint8_t

#define GNSS7_OK           0x00
#define GNSS7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define GNSS7_NEMA_GNGGA 1
#define GNSS7_NEMA_GNGLL 3
#define GNSS7_NEMA_GNGGA_NUM_ELEMENT 15
#define GNSS7_NEMA_GNGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define GNSS7_GNGGA_TIME                      1 
#define GNSS7_GNGGA_LATITUDE                  2
#define GNSS7_GNGGA_LATITUDE_SIDE             3
#define GNSS7_GNGGA_LONGITUDE                 4
#define GNSS7_GNGGA_LONGITUDE_SIDE            5
#define GNSS7_GNGGA_QUALITY_INDICATOR         6
#define GNSS7_GNGGA_NUMBER_OF_SATELLITES      7
#define GNSS7_GNGGA_H_DILUTION_OF_POS         8
#define GNSS7_GNGGA_ALTITUDE                  9
#define GNSS7_GNGGA_ALTITUDE_UNIT             10
#define GNSS7_GNGGA_GEOIDAL_SEPARATION        11
#define GNSS7_GNGGA_GEOIDAL_SEPARATION_UNIT   12
#define GNSS7_GNGGA_TIME_SINCE_LAST_DGPS      13
#define GNSS7_GNGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define GNSS7_GNGLL_LATITUDE                  1
#define GNSS7_GNGLL_LATITUDE_SIDE             2
#define GNSS7_GNGLL_LONGITUDE                 3
#define GNSS7_GNGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define GNSS7_ERROR_COMMAND_OR_ELEMENT   0xFF
#define GNSS7_ERROR_START_OR_END_COMMAND 0x8F
#define GNSS7_ERROR_NEXT_ELEMENT         0x4F
#define GNSS7_ERROR_CURRENT_ELEMENT      0x2F
#define GNSS7_NO_ERROR                   0x00
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

    digital_out_t sel;
    digital_out_t rst;

    // Input pins 

    digital_in_t exi;
    digital_in_t pls;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} gnss7_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t sel;
    pin_name_t rst;
    pin_name_t exi;
    pin_name_t pls;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} gnss7_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t gnss7_error_t;

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
void gnss7_cfg_setup ( gnss7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gnss7 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GNSS7_RETVAL gnss7_init ( gnss7_t *ctx, gnss7_cfg_t *cfg );

/**
 * @brief Wake-up module.
 * @param gnss7 Click object.
 */
void gnss7_module_wakeup ( gnss7_t *ctx );

/**
 * @brief Get EXI ( external interrupt ) pin state.
 * @param gnss7 Click object.
 * @return current pin state.
 */
uint8_t gnss7_get_exi_pin ( gnss7_t *ctx );

/**
 * @brief Set RST ( reset ) pin state.
 * @param gnss7 Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void gnss7_set_rst_pin ( gnss7_t *ctx, uint8_t state );

/**
 * @brief Set SEL ( mode select ) pin state.
 * @param gnss7 Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void gnss7_set_sel_pin ( gnss7_t *ctx, uint8_t state );

/**
 * @brief Get PLS pin state.
 * @param gnss7 Click object.
 * @return current pin state.
 */
uint8_t gnss7_get_pls_pin ( gnss7_t *ctx );

/**
 * @brief Generic write function.
 * @param gnss7 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void gnss7_generic_write ( gnss7_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param gnss7 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
uint16_t gnss7_generic_read ( gnss7_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic parser function.
 * @param gnss7 Click object.
 * @param command NEMA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * @return error data
 */
gnss7_error_t gnss7_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

#ifdef __cplusplus
}
#endif
#endif  // _GNSS7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
