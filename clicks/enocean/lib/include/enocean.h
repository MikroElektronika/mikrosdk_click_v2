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
 * \brief This file contains API for EnOcean Click driver.
 *
 * \addtogroup enocean EnOcean Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ENOCEAN_H
#define ENOCEAN_H

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
#define ENOCEAN_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ENOCEAN_RETVAL  uint8_t

#define ENOCEAN_OK           0x00
#define ENOCEAN_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define ENOCEAN_NEMA_GPGGA 1
#define ENOCEAN_NEMA_GPGLL 3
#define ENOCEAN_NEMA_GPGGA_NUM_ELEMENT 15
#define ENOCEAN_NEMA_GPGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define ENOCEAN_GPGGA_TIME                      1 
#define ENOCEAN_GPGGA_LATITUDE                  2
#define ENOCEAN_GPGGA_LATITUDE_SIDE             3
#define ENOCEAN_GPGGA_LONGITUDE                 4
#define ENOCEAN_GPGGA_LONGITUDE_SIDE            5
#define ENOCEAN_GPGGA_QUALITY_INDICATOR         6
#define ENOCEAN_GPGGA_NUMBER_OF_SATELLITES      7
#define ENOCEAN_GPGGA_H_DILUTION_OF_POS         8
#define ENOCEAN_GPGGA_ALTITUDE                  9
#define ENOCEAN_GPGGA_ALTITUDE_UNIT             10
#define ENOCEAN_GPGGA_GEOIDAL_SEPARATION        11
#define ENOCEAN_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define ENOCEAN_GPGGA_TIME_SINCE_LAST_DGPS      13
#define ENOCEAN_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define ENOCEAN_GPGLL_LATITUDE                  1
#define ENOCEAN_GPGLL_LATITUDE_SIDE             2
#define ENOCEAN_GPGLL_LONGITUDE                 3
#define ENOCEAN_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define ENOCEAN_ERROR_COMMAND_OR_ELEMENT   0xFF
#define ENOCEAN_ERROR_START_OR_END_COMMAND 0x8F
#define ENOCEAN_ERROR_NEXT_ELEMENT         0x4F
#define ENOCEAN_ERROR_CURRENT_ELEMENT      0x2F
#define ENOCEAN_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */


/**
 * \defgroup offset      Offset
 * \{
 */
#define ENOCEAN2_RX_BUFFER_SIZE          512
#define ENOCEAN2_SEQUENCE_NUMBER_OFFSET  2
#define ENOCEAN2_COMMAND_OFFSET          17
/** \} */

/**
 * \defgroup Return Values
 * \{
 */
#define ENOCEAN2_ERR_OK                  0xE0
#define ENOCEAN2_ERR_BUFFER_FULL         0xE1
#define ENOCEAN2_ERR_CHAR_TIMEOUT        0xE2
#define ENOCEAN2_ERR_INVALID_SIZE        0xE3
#define ENOCEAN2_ERR_NO_MEMORY           0xE4
/** \} */

/**
 * \defgroup Packet Types
 * \{
 */
#define ENOCEAN2_TYPE_RADIO_ERP1                 0x01
#define ENOCEAN2_TYPE_RESPONSE                   0x02
#define ENOCEAN2_TYPE_RADIO_SUB_TEL              0x03
#define ENOCEAN2_TYPE_EVENT                      0x04
#define ENOCEAN2_TYPE_COMMON                     0x05
#define ENOCEAN2_TYPE_SMART_ACK                  0x06
#define ENOCEAN2_TYPE_REMOTE_MAN                 0x07
#define ENOCEAN2_TYPE_RADIO_MESSAGE              0x09
#define ENOCEAN2_TYPE_RADIO_ERP2                 0x0A
#define ENOCEAN2_TYPE_RADIO_802_15_4             0x10
#define ENOCEAN2_TYPE_COMMAND_2_4                0x11
/** \} */

/**
 * \defgroup Event Codes
 * \{
 */
#define ENOCEAN2_EV_SA_RECLAIM_NOT_SUCCESSFUL    0x01
#define ENOCEAN2_EV_SA_CONFIRM_LEARN             0x02
#define ENOCEAN2_EV_SA_LEARN_ACK                 0x03
#define ENOCEAN2_EV_CO_READY                     0x04
#define ENOCEAN2_EV_CO_EVENT_SECUREDEVICES       0x05
#define ENOCEAN2_EV_CO_DUTYCYCLE_LIMIT           0x06
#define ENOCEAN2_EV_CO_TRANSMIT_FAILED           0x07
/** \} */

/**
 * \defgroup Common Commands Codes
 * \{
 */
#define ENOCEAN2_CO_WR_SLEEP                     0x01
#define ENOCEAN2_CO_WR_RESET                     0x02
#define ENOCEAN2_CO_RD_VERSION                   0x03
#define ENOCEAN2_CO_RD_SYS_LOG                   0x04
#define ENOCEAN2_CO_WR_SYS_LOG                   0x05
#define ENOCEAN2_CO_WR_BIST                      0x06
#define ENOCEAN2_CO_WR_IDBASE                    0x07
#define ENOCEAN2_CO_RD_IDBASE                    0x08
#define ENOCEAN2_CO_WR_REPEATER                  0x09
#define ENOCEAN2_CO_RD_REPEATER                  0x0A
#define ENOCEAN2_CO_WR_FILTER_ADD                0x0B
#define ENOCEAN2_CO_WR_FILTER_DEL                0x0C
#define ENOCEAN2_CO_WR_FILTER_DEL_ALL            0x0D
#define ENOCEAN2_CO_WR_FILTER_ENABLE             0x0E
#define ENOCEAN2_CO_RD_FILTER                    0x0F
#define ENOCEAN2_CO_WR_WAIT_MATURITY             0x10
#define ENOCEAN2_CO_WR_SUBTEL                    0x11
#define ENOCEAN2_CO_WR_MEM                       0x12
#define ENOCEAN2_CO_RD_MEM                       0x13
#define ENOCEAN2_CO_RD_MEM_ADDRESS               0x14
#define ENOCEAN2_CO_RD_SECURITY                  0x15
#define ENOCEAN2_CO_WR_SECURITY                  0x16
#define ENOCEAN2_CO_WR_LEARNMODE                 0x17
#define ENOCEAN2_CO_RD_LEARNMODE                 0x18
#define ENOCEAN2_CO_WR_SECUREDEVICE_ADD          0x19
#define ENOCEAN2_CO_WR_SECUREDEVICE_DEL          0x20
#define ENOCEAN2_CO_RD_SECUREDEVICE_BY_INDEX     0x21
#define ENOCEAN2_CO_WR_MODE                      0x22
#define ENOCEAN2_CO_RD_NUMSECUREDEVICES          0x23
#define ENOCEAN2_CO_RD_SECUREDEVICE_BY_ID        0x24
#define ENOCEAN2_CO_WR_SECUREDEVICE_ADD_PSK      0x25
#define ENOCEAN2_CO_WR_SECUREDEVICE_SENDTEACHIN  0x26
#define ENOCEAN2_CO_WR_TEMPORARY_RLC_WINDOW      0x27
#define ENOCEAN2_CO_RD_SECUREDEVICE_PSK          0x28
#define ENOCEAN2_CO_RD_DUTYCYCLE_LIMIT           0x29
#define ENOCEAN2_CO_SET_BAUDRATE                 0x30
#define ENOCEAN2_CO_GET_FREQUENCY_INFO           0x31
#define ENOCEAN2_CO_GET_STEPCODE                 0x32
/** \} */

/**
 * \defgroup Smart Ack. Commands codes
 * \{
 */
#define ENOCEAN2_SA_WR_LEARNMODE                 0x01
#define ENOCEAN2_SA_RD_LEARNMODE                 0x02
#define ENOCEAN2_SA_WR_LEARNCONFIRM              0x03
#define ENOCEAN2_SA_WR_CLIENTLEARNRQ             0x04
#define ENOCEAN2_SA_WR_RESET                     0x05
#define ENOCEAN2_SA_RD_LEARNEDCLIENTS            0x06
#define ENOCEAN2_SA_WR_RECLAIMS                  0x07
#define ENOCEAN2_SA_WR_POSTMASTER                0x08
/** \} */

/**
 * \defgroup Return codes
 * \{
 */
#define ENOCEAN2_RET_OK                          0x00
#define ENOCEAN2_RET_ERROR                       0x01
#define ENOCEAN2_RET_NOT_SUPPORTED               0x02
#define ENOCEAN2_RET_WRONG_PARAM                 0x03
#define ENOCEAN2_RET_OPERATION_DENIED            0x04
#define ENOCEAN2_RET_LOCK_SET                    0x05
#define ENOCEAN2_RET_BUFFER_TO_SMALL             0x06
#define ENOCEAN2_RET_NO_FREE_BUFFER              0x07
#define ENOCEAN2_RX_PACKET_MAX_SIZE      256
#define ENOCEAN2_SYNC_BYTE               0x55
#define ENOCEAN2_HEADER_SIZE             0x00000004 
#define ENOCEAN2_SYNC_SIZE               0x06
#define ENOCEAN2_CRC8H_OFFSET            0x05
#define ENOCEAN2_HEADER_OFFSET           0x01
#define STATE_SYNC           1
#define STATE_DATA           2
#define STATE_FINISH         3
/** \} */


/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
typedef struct
{
    uint16_t data_length;
    uint8_t option_length;
    uint8_t type;
    uint8_t *data_buffer;

} enocean_packet_t;

typedef void ( *enocean_callback_t ) ( enocean_packet_t *packet );
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

   //digital_out_t an;
    digital_out_t rst;
   //digital_out_t cs;
   //digital_out_t pwm;
   //digital_out_t int_pin;

    // Input pins 

   //digital_in_t an;
   //digital_in_t rst;
   //digital_in_t cs;
   //digital_in_t pwm;
   //digital_in_t int_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    enocean_packet_t rx_packet;

    uint32_t rx_packet_capacity;
    uint32_t rx_data_cnt;
    uint32_t rx_packet_size;
   
    enocean_callback_t recieve_callback;
    
    uint8_t state;

    uint8_t *rx_buffer_begin;
    uint8_t *rx_buffer_end;
   
    volatile uint8_t *rx_head;
    volatile uint16_t rx_size;
    uint8_t *rx_tail;
    uint16_t rx_capacity;

    char temp;

} enocean_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

   //pin_name_t an;
    pin_name_t rst;
   //pin_name_t cs;
   //pin_name_t pwm;
   //pin_name_t int_pin;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} enocean_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t enocean_error_t;

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
void enocean_cfg_setup ( enocean_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param enocean Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ENOCEAN_RETVAL enocean_init ( enocean_t *ctx, enocean_cfg_t *cfg );

/**
 * @brief Set RST ( reset ) pin state.
 * @param enocean Click object.
 * @param statte Pin state ( 1 or 0 ).
 */
void enocean_set_rst_pin ( enocean_t *ctx, uint8_t state );

/**
 * @brief Get PPS pin state.
 * @param enocean Click object.
 * @return current pin state.
 */
uint8_t enocean_get_pps_pin ( enocean_t *ctx );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void enocean_generic_write ( enocean_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int16_t enocean_generic_read ( enocean_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief <h3> Send ESP3 packet </h3>
 *
 * @param ctx Click object.
 * @param  packet - Sending packet.
 *
 * @retval      ENOCEAN2_ERR_OK
 * @retval      ENOCEAN2_ERR_INVALID_SIZE - Invalid packet size.
 *
 * Sends the ESP3 packet to an EnOcean module.
 *
 *
 */
uint8_t enocean_send ( enocean_t *ctx, enocean_packet_t* packet );

/**
 * @brief <h3> Recieve character </h3>
 *
 * @param ctx Click object.
 * @param rx_data - Recieved byte.
 *
 * @retval      ENOCEAN2_ERR_OK
 * @retval      ENOCEAN2_ERR_BUFFER_FULL - Ring buffer is full.
 *
 * The function push recieved character to ring buffer.
 *
 * @note
 * Call this function inside UART interrupt routine.
 */
uint8_t enocean_rx ( enocean_t *ctx, uint8_t rx_data );

void enocean_aux ( enocean_t *ctx, uint8_t *rx_buffer, uint16_t rx_size, uint8_t *data_buffer, uint16_t data_size );

uint8_t enocean_parser( enocean_t *ctx );

void enocean_set_callback_handler ( enocean_t *ctx, enocean_callback_t recieve );

#ifdef __cplusplus
}
#endif
#endif  // _ENOCEAN_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
