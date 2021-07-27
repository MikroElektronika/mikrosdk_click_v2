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
 * \brief This file contains API for EnOcean 3 Click driver.
 *
 * \addtogroup enocean3 EnOcean 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ENOCEAN3_H
#define ENOCEAN3_H

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
#define ENOCEAN3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ENOCEAN3_RETVAL  uint8_t

#define ENOCEAN3_OK           0x00
#define ENOCEAN3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
#define DRV_TX_BUFFER_SIZE 100
/** \} */


#define ENOCEAN3_SYNC_BYTE                                  0x55
#define ENOCEAN3_MAX_BUFF_SIZE                              256
#define ENOCEAN3_HEADER_SIZE                                0x04
#define ENOCEAN3_BUFF_EMPTY                                 0x00


#define ENOCEAN3_RESPONSE_READY                             0x01
#define ENOCEAN3_RESPONSE_NOT_READY                         0x00
#define ENOCEAN3_UART_RX_READY                              0x01
#define ENOCEAN3_UART_RX_NOT_READY                          0x00
#define ENOCEAN3_OK                                         0x00
#define ENOCEAN3_INVALID_PACKET_SIZE                        0x01
              
#define ENOCEAN3_PACK_TYPE_EVENT                            0x04
#define ENOCEAN3_PACK_TYPE_COMMON_COMMAND                   0x05
#define ENOCEAN3_CO_EVENT_SECUREDEVICES                     0x05
#define ENOCEAN3_CO_WR_FILTER_ADD                           0x0B
#define ENOCEAN3_CO_WR_FILTER_ENABLE                        0x0E
#define ENOCEAN3_CO_WR_REPEATER                             0x09
#define ENOCEAN3_CO_SET_NOISETHRESHOLD                      0x32

#define ENOCEAN3_FILT_TYPE_SOURCE_ID                        0x00
#define ENOCEAN3_FILT_TYPE_R_ORG                            0x01
#define ENOCEAN3_FILT_TYPE_RSSI                             0x02
#define ENOCEAN3_FILT_TYPE_DEST_ID                          0x03
#define ENOCEAN3_FILT_KIND_NEG_TEL_FWRD                     0x00
#define ENOCEAN3_FILT_KIND_POS_TEL_FWRD                     0x80
#define ENOCEAN3_FILT_KIND_NEG_TEL_RPT                      0x40
#define ENOCEAN3_FILT_KIND_POS_TEL_RPT                      0xC0
#define ENOCEAN3_FILT_FWRD_OFF                              0x00
#define ENOCEAN3_FILT_FWRD_ON                               0x01
#define ENOCEAN3_FILT_OP_OR_ALL_FILT                        0x00
#define ENOCEAN3_FILT_OP_AND_ALL_FILT                       0x01
#define ENOCEAN3_FILT_OP_OR_RADIO_INTER_AND_FILT_RPT        0x08
#define ENOCEAN3_FILT_OP_AND_RADIO_INTER_OR_FILT_RPT        0x09
#define ENOCEAN3_RPT_OFF                                    0x00
#define ENOCEAN3_RPT_ALL_TELEG                              0x01
#define ENOCEAN3_RPT_SELECTIVE                              0x02
#define ENOCEAN3_RPT_LEVEL_OFF                              0x00
#define ENOCEAN3_RPT_LEVEL_ONE                              0x01
#define ENOCEAN3_RPT_LEVEL_TWO                              0x02
#define ENOCEAN3_RSSI_LEVEL_100_DBM_NEG                     0x2E
#define ENOCEAN3_RSSI_LEVEL_99_DBM_NEG                      0x2F
#define ENOCEAN3_RSSI_LEVEL_98_DBM_NEG                      0x30
#define ENOCEAN3_RSSI_LEVEL_97_DBM_NEG                      0x31
#define ENOCEAN3_RSSI_LEVEL_96_DBM_NEG                      0x32
#define ENOCEAN3_RSSI_LEVEL_95_DBM_NEG                      0x33
#define ENOCEAN3_RSSI_LEVEL_94_DBM_NEG                      0x34
#define ENOCEAN3_RSSI_LEVEL_93_DBM_NEG                      0x35
#define ENOCEAN3_RSSI_LEVEL_92_DBM_NEG                      0x36
#define ENOCEAN3_RSSI_LEVEL_91_DBM_NEG                      0x37
#define ENOCEAN3_RSSI_LEVEL_90_DBM_NEG                      0x38

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
/** @defgroup ENOCEAN3_TYPES Types */                             /** @{ */

typedef struct {

    uint16_t   data_length;
    uint8_t    opt_length;
    uint8_t    packet_type;
    uint8_t    data_buff[ 256 ];

} enocean3_packet_t;

typedef void ( *enocean3_hdl_t )( enocean3_packet_t*, uint16_t* );

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

    enocean3_hdl_t driver_hdl;
    uint8_t response_ready;

} enocean3_t;

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

} enocean3_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t enocean3_error_t;

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
void enocean3_cfg_setup ( enocean3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param enocean3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ENOCEAN3_RETVAL enocean3_init ( enocean3_t *ctx, enocean3_cfg_t *cfg );

/**
 * @brief Set RST ( reset ) pin state.
 * @param enocean3 Click object.
 * @param statte Pin state ( 1 or 0 ).
 */
void enocean3_set_rst_pin ( enocean3_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 * @param enocean3 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void enocean3_generic_write ( enocean3_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param enocean3 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t enocean3_generic_read ( enocean3_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Handler Set function.
 *
 * @param ctx Click object.      
 * @param handler  Pointer to the function that should be performed
 *
 * @description This function sets handler on the function that should be performed.
 */
void enocean3_response_handler_set ( enocean3_t *ctx, enocean3_hdl_t handler );

/**
 * @brief Packet Send function.
 *
 * @param ctx Click object.
 * @param packet  Packet data to be sent
 *
 * @returns 0 - OK, 1 - Packet size is invalid
 *
 * @description This function sends a packet data to the device by using UART interface.
 */
uint8_t enocean3_send_packet( enocean3_t *ctx, enocean3_packet_t *packet );

/**
 * @brief Response Ready function
 *
 * @param ctx Click object.
 * 
 * @returns 0 - The response is not ready, 1 - The response is ready
 *
 * @description This function checks does response ready or not.
 */
uint8_t enocean3_response_ready( enocean3_t *ctx );

/**
 * @brief UART Interrupt Routine function
 *
 * @param ctx Click object.
 * 
 * @description This function reads every single byte from the device, performs a crc8 check for header and data packet and makes a
 * received response.
 */
void enocean3_uart_isr( enocean3_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _ENOCEAN3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
