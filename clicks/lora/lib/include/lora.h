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
 * \brief This file contains API for LoRa Click driver.
 *
 * \addtogroup lora LoRa Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LORA_H
#define LORA_H

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
#define LORA_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LORA_RETVAL  uint8_t

#define LORA_OK           0x00
#define LORA_INIT_ERROR   0xFF
/** \} */
                      
/**
 * \defgroup var Variables
 * \{
 */
#define LORA_MAC_TX                   "mac tx "
#define LORA_JOIN                     "mac join "
#define LORA_RADIO_TX                 "radio tx "
#define LORA_RADIO_RX                 "radio rx "
/** \} */

/**
 * \defgroup timer_limit Timer Limit ( ms )
 * \{
 */
#define LORA_TIMER_EXPIRED            50000
/** \} */

/**
 * \defgroup number_of_response_indexes Number of Response Indexes
 * \{
 */
#define LORA_RESP_COUNT               100
/** \} */

/**
 * \defgroup response_string_max_size Response String Max Size
 * \{
 */
#define LORA_MAX_RSP_SIZE             20
/** \} */

/**
 * \defgroup command_string_max_size Command String Max Size
 * \{
 */
#define LORA_MAX_CMD_SIZE             64
/** \} */

/**
 * \defgroup command_string_max_size Command String Max Size
 * \{
 */ 
#define LORA_MAX_DATA_SIZE            256
#define LORA_MAX_TRANSFER_SIZE        384
/** \} */

/**
 * \defgroup payload Payload
 * \{
 */ 
#define LORA_PL_CNF                   "cnf "
#define LORA_PL_UNCNF                 "uncnf "
/** \} */

/**
 * \defgroup join_mode Join mode
 * \{
 */
#define LORA_JM_OTAA                  "otaa"
#define LORA_JM_ABP                   "abp"
/** \} */

/**
 * \defgroup cmd Command
 * \{
 */
#define LORA_CMD_SYS_GET_VER          "sys get ver"
#define LORA_CMD_MAC_PAUSE            "mac pause"
#define LORA_CMD_RADIO_SET_WDT        "radio set wdt 0"
#define LORA_ARG_0                    "0"
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
 * @brief Click buffers object definition.
 */
typedef struct
{
    char     tx_buffer[ LORA_MAX_TRANSFER_SIZE ];
    char     rx_buffer[ LORA_MAX_TRANSFER_SIZE ];
    uint16_t rx_buffer_len;

} lora_buffers_t;

/**
 * @brief Timer Flags and Counter object definition.
 */
typedef struct
{
    bool     timer_f;
    bool     timeout_f;
    bool     timer_use_f;
    uint32_t ticker;
    uint32_t timer_max;
    
} lora_timer_t;

/**
 * @brief  Process Flags object definition.
 */
typedef struct
{
    bool rsp_rdy_f;
    bool lora_rdy_f;
    
} lora_procces_flags_t;

/**
 * @brief Response object definition.
 */
typedef struct
{
    bool  rsp_f;
    char  *rsp_buffer;
    bool  callback_default;
    void ( *callback_resp )( char *response );
    
} lora_response_t;

/**
 * @brief Mac object definition.
 */
typedef struct
{
    char* payload; 
    char* port_no; 
    char *buffer;
    char *response;
    
} lora_mac_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t rts;

    // Input pins 

    digital_in_t cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    lora_buffers_t buff;
    lora_timer_t tm;
    lora_procces_flags_t flags;
    lora_response_t rsp;
    char data_in;

} lora_t;

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
    pin_name_t rts;
    pin_name_t cts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} lora_cfg_t;

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
void lora_cfg_setup ( lora_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LORA_RETVAL lora_init ( lora_t *ctx, lora_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 * @param cb_default    Callback Default
 * @param - pointer to user made callback function that receiving response
 *          as argument and will be executed one every response
 *
 * @description This function executes default configuration for LoRa click.
 *
 * @note 
 * <pre> 
 * Module restart issues the response from the module with current firmware version.
 * Must be called before any other operation. Resets the module and sets 
 * all flags and parameters to default value.
 * </pre>
 */
void lora_default_cfg ( lora_t *ctx, bool cb_default, void ( *response_p )( char *response ) );

/**
 * @brief Generic write function.

 * @param ctx         Click object.
 * @param data_buf    Data buffer for sends.
 * @param len         Number of bytes for sends.
 *
 * @description This function write specific number of bytes
 */
void lora_generic_write ( lora_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.

 * @param ctx         Click object.
 * @param data_buf    Data buffer for read data.
 * @param max_len     The maximum length of data that can be read.
 *
 * @returns Number of reads data.
 *
 * @description This function read maximum length of data.
 */
int16_t lora_generic_read ( lora_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command function.
 *
 * @param ctx       Click object. 
 * @param comd      Well formated command string.
 * @param response  Response data.
 *
 * @description Used by parser to send data inside the software buffer. User can send valid
 *            commands with this function but command string and data should be well formated.
 */
void lora_cmd ( lora_t *ctx, char *cmd,  char *response );

/**
 * @brief Function for writing mac parameters
 *
 * @param ctx       Click object.  
 * @param mac       Mac structure object  
 *
 * @description This function write mac parameters to tx_buffer.
 */
uint8_t lora_mac_tx ( lora_t *ctx, lora_mac_t *mac );

/**
 * @brief Function for setting join mode
 *
 * @param ctx           Click object.  
 * @param join_mode     Join mode.
 * @param response      Response.
 *
 * @description This function sets join mode.
 */
uint8_t lora_join ( lora_t *ctx, char *join_mode, char *response );

/**
 * @brief Main receiver function  
 *
 * @param ctx           Click object.  
 * @param window_size   Window size.
 * @param response      Response.
 *
 * @description This function is used for receive message.
 */
uint8_t lora_rx ( lora_t *ctx, char *window_size, char *response );

/**
 * @brief Main tnanceiver function
 *
 * @param ctx       Click object.  
 * @param buffer    Buffer to be send.
 *
 * @description This function is used for sending message.
 */
uint8_t lora_tx ( lora_t *ctx, char *buffer );

/**
 * @brief Receiver
 *
 * @param ctx       Click object.  
 * @param rx_input  Data from uart receive register
 *
 * @description Must be placed inside the user made uart interrupt routine.
 */
void lora_rx_isr ( lora_t *ctx, char rx_input );

/**
 * @brief Timer
 *
 * @param ctx       Click object.  
 *
 * @description Used for host timing. Should be placed inside the previously made interrupt
 * routine made by user that occurs on every one milisecond.
 */
void lora_tick_isr ( lora_t *ctx );

/**
 * @brief Timer Configuration
 *
 * @param ctx           Click object.
 * @param timer_limit   ( 0 ~ 4294967296 )  
 * 
 * @description Used to configure host watchdog. When timeout occurs response with no data
 *              will be parsed. If user provide 0 as argument timer will be turned off. By
 *              default after the initialization timer limit is turned on and set to
 * @link TIMER_EXPIRED @endlink
 *
 * @note
 * <pre>  
 * RN2483 have it's own watchdog timer, this one should be longer than watchdog and can be 
 * used to restart the module in case of when library does not receiving responses from the 
 * module.
 * </pre> 
 */
void lora_tick_conf ( lora_t *ctx, uint32_t timer_limit );

/**
 * @brief Main Process
 *
 * @param ctx           Click object.
 * 
 * @description Function must be placed inside the infinite while loop.
 */
void lora_isr_process ( lora_t *ctx );

/**
 * @brief Function for write char
 *
 * @param ctx           Click object.
 * @param data_in       Char to be written 
 *
 * @description Function write char into ctx objects.
 */
void lora_put_char ( lora_t *ctx, char data_in );

#ifdef __cplusplus
}
#endif
#endif  // _LORA_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
