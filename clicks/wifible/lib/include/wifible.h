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
 * \brief This file contains API for WiFi BLE Click driver.
 *
 * \addtogroup wifible WiFi BLE Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef WIFIBLE_H
#define WIFIBLE_H

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
#define WIFIBLE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define WIFIBLE_RETVAL  uint8_t

#define WIFIBLE_OK           0x00
#define WIFIBLE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup evarg  Evarg
 * \{
 */
#define WIFIBLE_EVARG_START_T           0
#define WIFIBLE_EVARG_END_T             1
#define WIFIBLE_EVARG_EVENT_T           2

/**
 * \defgroup event  Event
 * \{
 */
#define WIFIBLE_EVENT_RESPONSE       0x00
#define WIFIBLE_EVENT_TIMEOUT        0x01
#define WIFIBLE_EVENT_BUFFER_OUT     0x02
#define WIFIBLE_EVENT_CALLBACK       0x04
/** \} */

/**
 * \defgroup command Command
 * \{
 */
#define WIFIBLE_START_COMMAND           2
#define WIFIBLE_NEXT_COMMAND            0
#define WIFIBLE_NO_COMMAND              1
/** \} */

/**
 * \defgroup example  Example
 * \{
 */       
#define WIFIBLE_WIFI_EXAMPLE            1
#define WIFIBLE_BLE_EXAMPLE             0
/** \} */

/**
 * \defgroup function_for_wifible  Function for wifible
 * \{
 */       
#define WIFIBLE_UNKNOWN                 0
#define WIFIBLE_TEST                    1
#define WIFIBLE_GET                     2
#define WIFIBLE_SET                     3
#define WIFIBLE_URC                     4
#define WIFIBLE_EXEC                    5
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
    digital_out_t en;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} wifible_t;

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
    pin_name_t en;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} wifible_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t wifible_error_t;

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
void wifible_cfg_setup ( wifible_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param wifible Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
WIFIBLE_RETVAL wifible_init ( wifible_t *ctx, wifible_cfg_t *cfg );

/**
 * @brief Power module.
 * 
 * @param ctx           Click object.
 * @param power_state   State of pin.
 */
void wifible_module_power ( wifible_t *ctx, uint8_t power_state );

/**
 * @brief Generic write function.
 * @param wifible Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void wifible_generic_write ( wifible_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param wifible Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int16_t wifible_generic_read ( wifible_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief GFunction for send command.
 * 
 * @param ctx       Click object.
 * @param command   Data to be send.
*/
void wifible_send_command ( wifible_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _WIFIBLE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
