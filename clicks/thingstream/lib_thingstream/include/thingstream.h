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
 * \brief This file contains API for Thingstream Click driver.
 *
 * \addtogroup thingstream Thingstream Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THINGSTREAM_H
#define THINGSTREAM_H

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
#define THINGSTREAM_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THINGSTREAM_OK                              0
#define THINGSTREAM_ERROR                          -1
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define THINGSTREAM_DRV_RX_BUFFER_SIZE              600
#define THINGSTREAM_DRV_TX_BUFFER_SIZE              100
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define THINGSTREAM_NEMA_CGNSINF                    1
#define THINGSTREAM_NEMA_GPGLL                      3
#define THINGSTREAM_NEMA_CGNSINF_NUM_ELEMENT        20
#define THINGSTREAM_NEMA_GPGLL_NUM_ELEMENT          5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define THINGSTREAM_GPGGA_TIME                      1 
#define THINGSTREAM_GPGGA_LATITUDE                  2
#define THINGSTREAM_GPGGA_LATITUDE_SIDE             3
#define THINGSTREAM_GPGGA_LONGITUDE                 4
#define THINGSTREAM_GPGGA_LONGITUDE_SIDE            5
#define THINGSTREAM_GPGGA_QUALITY_INDICATOR         6
#define THINGSTREAM_GPGGA_NUMBER_OF_SATELLITES      7
#define THINGSTREAM_GPGGA_H_DILUTION_OF_POS         8
#define THINGSTREAM_GPGGA_ALTITUDE                  9
#define THINGSTREAM_GPGGA_ALTITUDE_UNIT             10
#define THINGSTREAM_GPGGA_GEOIDAL_SEPARATION        11
#define THINGSTREAM_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define THINGSTREAM_GPGGA_TIME_SINCE_LAST_DGPS      13
#define THINGSTREAM_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define THINGSTREAM_GPGLL_LATITUDE                  1
#define THINGSTREAM_GPGLL_LATITUDE_SIDE             2
#define THINGSTREAM_GPGLL_LONGITUDE                 3
#define THINGSTREAM_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define THINGSTREAM_ERROR_COMMAND_OR_ELEMENT        0xFF
#define THINGSTREAM_ERROR_START_OR_END_COMMAND      0x8F
#define THINGSTREAM_ERROR_NEXT_ELEMENT              0x4F
#define THINGSTREAM_ERROR_CURRENT_ELEMENT           0x2F
#define THINGSTREAM_NO_ERROR                        0x00
/** \} */

/**
 * \defgroup rmc_element CGNSINF command elements 
 * \{
 */
#define THINGSTREAM_CGNSINF_RUN_STAT                1
#define THINGSTREAM_CGNSINF_FIX_STAT                2
#define THINGSTREAM_CGNSINF_DATE_TIME               3
#define THINGSTREAM_CGNSINF_LATITUDE                4
#define THINGSTREAM_CGNSINF_LONGITUDE               5
#define THINGSTREAM_CGNSINF_ALTITUDE                6
#define THINGSTREAM_CGNSINF_SPEED                   7
#define THINGSTREAM_CGNSINF_COURSE                  8
#define THINGSTREAM_CGNSINF_FIX_MODE                9 
#define THINGSTREAM_CGNSINF_RESERVED1               10
#define THINGSTREAM_CGNSINF_HDOP                    11
#define THINGSTREAM_CGNSINF_PDOP                    12
#define THINGSTREAM_CGNSINF_VDOP                    13
#define THINGSTREAM_CGNSINF_RESERVED2               14
#define THINGSTREAM_CGNSINF_SAT_VIEW                15
#define THINGSTREAM_CGNSINF_SAT_USED                16
#define THINGSTREAM_CGNSINF_GLONASS_VIEW            17           
#define THINGSTREAM_CGNSINF_RESERVED3               18
#define THINGSTREAM_CGNSINF_C_N0                    19
#define THINGSTREAM_CGNSINF_HPA                     20
#define THINGSTREAM_CGNSINF_VPA                     21
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
    
    // Modules 
    uart_t uart;

    char uart_rx_buffer[ THINGSTREAM_DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ THINGSTREAM_DRV_TX_BUFFER_SIZE ];

} thingstream_t;

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

    // static variable 
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} thingstream_cfg_t;

/**
 * @brief Error type 
 */
// Actuator switch type
typedef uint8_t thingstream_actuator_sw_t;

// Actuator counter type
typedef int16_t thingstream_actuator_cnt_t;

// Actuator string type
typedef char thingstream_actuator_str_t;

// Parser error type
typedef uint8_t thingstream_error_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void thingstream_cfg_setup ( thingstream_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param thingstream Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t thingstream_init ( thingstream_t *ctx, thingstream_cfg_t *cfg );

/**
 * @brief Power module.
 * 
 * @param ctx         Click object.
 * @param power_state State of pin.
 */
void thingstream_module_power ( thingstream_t *ctx, uint8_t power_state );

/**
 * @brief Set RST pin state.
 * 
 * @param ctx    Click object.
 * @param state Pin state ( 1 or 0 ).
 */
void thingstream_reset_pin_state ( thingstream_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 * 
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void thingstream_generic_write ( thingstream_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
int32_t thingstream_generic_read ( thingstream_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command.
 * 
 * @param ctx Click object.
 * @param command Command to send.
 */
void thingstream_send_command ( thingstream_t *ctx, char *command );

/**
 * @brief Generic parser function.
 * 
 * @param ctx            Click object.
 * @param command        NEMA ( GPS/GNSS ) command.
 * @param element        Element position in command.
 * @param parser_buf     Parser buffer for data storage.
 * 
 * @return error data
 */
thingstream_error_t thingstream_generic_parser ( char *rsp,  uint8_t command, 
                                                 uint8_t element, char *parser_buf );

#ifdef __cplusplus
}
#endif
#endif  // _THINGSTREAM_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
