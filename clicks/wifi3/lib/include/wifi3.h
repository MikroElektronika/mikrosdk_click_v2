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
 * \brief This file contains API for wifi3 Click driver.
 *
 * \addtogroup wifi3 wifi3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef WIFI3_H
#define WIFI3_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"
#include "log.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

#define CR           0x0D
#define LF           0x0A

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define WIFI3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define WIFI3_RETVAL  uint8_t

#define WIFI3_OK           0x00
#define WIFI3_INIT_ERROR   0xFF
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

typedef struct
{
    uint8_t cmd[ 100 ];
    uint8_t str_len;
} wifi3_atcmd_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

   digital_out_t an;
   digital_out_t rst;
   digital_out_t cs;

   // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} wifi3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

   pin_name_t an;
   pin_name_t rst;
   pin_name_t cs;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} wifi3_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t wifi3_error_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 // AT COMMANDS - STRING DECLARATIONS
 // More related commands and their argumets format could be found on the following link:
 // https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
extern const wifi3_atcmd_t WIFI3_CHECK;
extern const wifi3_atcmd_t WIFI3_RST;
extern const wifi3_atcmd_t WIFI3_CHECK_FIRMWARE;
extern const wifi3_atcmd_t WIFI3_SET_MODE;
extern const wifi3_atcmd_t WIFI3_CONNECT;
extern const wifi3_atcmd_t WIFI3_LIST_AP;
extern const wifi3_atcmd_t WIFI3_QUIT_AP;
extern const wifi3_atcmd_t WIFI3_SET_AP_PARAMETERS;
extern const wifi3_atcmd_t WIFI3_JOIN_DEV_IP;
extern const wifi3_atcmd_t WIFI3_CONNECTION_STATUS;
extern const wifi3_atcmd_t WIFI3_START;
extern const wifi3_atcmd_t WIFI3_MODE;
extern const wifi3_atcmd_t WIFI3_SEND;
extern const wifi3_atcmd_t WIFI3_CLOSE;
extern const wifi3_atcmd_t WIFI3_GET_IP;
extern const wifi3_atcmd_t WIFI3_SET_MULTIPLE_CONNECTION;
extern const wifi3_atcmd_t WIFI3_SET_AS_SERVER;
extern const wifi3_atcmd_t WIFI3_SET_SERVER_TIMEOUT;
extern const wifi3_atcmd_t WIFI3_RECEIVE;

/** \} */ // End constants group
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
void wifi3_cfg_setup ( wifi3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param wifi3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
WIFI3_RETVAL wifi3_init ( wifi3_t *ctx, wifi3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for wifi3 click.
 */
void wifi3_default_cfg ( wifi3_t *ctx );

/**
 * @brief Wake-up module.
 * @param wifi3 Click object.
 */
void wifi3_module_wakeup ( wifi3_t *ctx );

/**
 * @brief Reset module.
 * @param wifi3 Click object.
 */
void wifi3_module_reset ( wifi3_t *ctx );

/**
 * @brief Set WKP ( wake-up ) pin state.
 * @param wifi3 Click object.
 * @param statte Pin state ( 1 or 0 ).
 */
void wifi3_set_wkp_pin ( wifi3_t *ctx, uint8_t state );

/**
 * @brief Set RST ( reset ) pin state.
 * @param wifi3 Click object.
 * @param statte Pin state ( 1 or 0 ).
 */
void wifi3_set_rst_pin ( wifi3_t *ctx, uint8_t state );

/**
 * @brief Get PPS pin state.
 * @param wifi3 Click object.
 * @return current pin state.
 */
uint8_t wifi3_get_pps_pin ( wifi3_t *ctx );

/**
 * @brief Generic write function.
 * @param wifi3 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void wifi3_generic_write ( wifi3_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param wifi3 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
uint16_t wifi3_generic_read ( wifi3_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic parser function.
 * @param wifi3 Click object.
 * @param command NEMA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * @return error data
 */
wifi3_error_t wifi3_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
);

/**
 * @brief Sends at command and logs the communication.
 * @param wifi3 Click object.
 * @param log Logging object
 * @param cmd At command structure
 * @param args At command arguments string pointer (NULL if no arguments).
 * @return error data
 * 
 * @description This function sends AT commant to wifi3 click, logs sent and received data. 
 */
uint8_t wifi3_send_cmd( wifi3_t* ctx , log_t* logger , const wifi3_atcmd_t* cmd , uint8_t* args );

/**
 * @brief Read received data.
 * @param wifi3 Click object.
 * @param r_buf Read buffer pointer.
 * @return error data
 * 
 * @description This function reads data received from Wifi3 click.
 */
uint8_t wifi3_read( wifi3_t* ctx , uint8_t* r_buf );

#ifdef __cplusplus
}
#endif
#endif  // _WIFI3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
