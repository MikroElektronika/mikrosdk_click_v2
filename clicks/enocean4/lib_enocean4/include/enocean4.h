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
 * \brief This file contains API for EnOcean 4 Click driver.
 *
 * \addtogroup enocean4 EnOcean 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ENOCEAN4_H
#define ENOCEAN4_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define ENOCEAN4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ENOCEAN4_RETVAL  uint8_t

#define ENOCEAN4_OK           0x00
#define ENOCEAN4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
#define DRV_TX_BUFFER_SIZE 100
/** \} */


#define ENOCEAN4_SYNC_BYTE             0x55
#define ENOCEAN4_MAX_BUFF_SIZE         256
#define ENOCEAN4_HEADER_SIZE           0x04
#define ENOCEAN4_BUFF_EMPTY            0x00

#define ENOCEAN4_RESPONSE_READY                0x01
#define ENOCEAN4_RESPONSE_NOT_READY            0x00
#define ENOCEAN4_UART_RX_NOT_READY             0x00
#define ENOCEAN4_OK                            0x00
#define ENOCEAN4_INVALID_PACKET_SIZE           0xFC
#define ENOCEAN4_CRC8D_ERROR                   0xFD
#define ENOCEAN4_CRC8H_ERROR                   0xFE
#define ENOCEAN4_SYNC_BYTE_ERROR               0xFF

#define ENOCEAN4_PACK_TYPE_RADIO_ERP1          0x01
#define ENOCEAN4_PACK_TYPE_RESPONSE            0x02
#define ENOCEAN4_PACK_TYPE_RADIO_SUB_TEL       0x03
#define ENOCEAN4_PACK_TYPE_EVENT               0x04
#define ENOCEAN4_PACK_TYPE_COMMON_CMD          0x05
#define ENOCEAN4_PACK_TYPE_SMART_ACK_CMD       0x06
#define ENOCEAN4_PACK_TYPE_REMOTE_MAN_CMD      0x07
#define ENOCEAN4_PACK_TYPE_RADIO_MSG           0x09
#define ENOCEAN4_PACK_TYPE_RADIO_ERP2          0x0A
#define ENOCEAN4_PACK_TYPE_RADIO_802_15_4      0x10
#define ENOCEAN4_PACK_TYPE_CMD_2_4             0x11
#define ENOCEAN4_RORG_VLD                      0xD2
#define ENOCEAN4_RORG_ADT                      0xA6
#define ENOCEAN4_RORG_4BS                      0xA5
#define ENOCEAN4_RET_OK                        0x00
#define ENOCEAN4_RET_ERROR                     0x01
#define ENOCEAN4_RET_NOT_SUPPORTED             0x02
#define ENOCEAN4_RET_WRONG_PARAM               0x03
#define ENOCEAN4_RET_OP_DENIED                 0x04
#define ENOCEAN4_RET_LOCK_SET                  0x05
#define ENOCEAN4_RET_BUFF_TO_SMALL             0x06
#define ENOCEAN4_RET_NO_FREE_BUFF              0x07

#define ENOCEAN4_EVENT_SA_RECLAIM_NOT_SUCCESSFUL       0x01
#define ENOCEAN4_EVENT_SA_CONFIRM_LEARN                0x02
#define ENOCEAN4_EVENT_SA_LEARN_ACK                    0x03
#define ENOCEAN4_EVENT_CO_READY                        0x04
#define ENOCEAN4_EVENT_CO_EVENT_SECUREDEVICES          0x05
#define ENOCEAN4_EVENT_CO_DUTYCYCLE_LIMIT              0x06
#define ENOCEAN4_EVENT_CO_TRANSMIT_FAILED              0x07
#define ENOCEAN4_CMD_CO_WR_SLEEP                       0x01
#define ENOCEAN4_CMD_CO_WR_RESET                       0x02
#define ENOCEAN4_CMD_CO_RD_VERSION                     0x03
#define ENOCEAN4_CMD_CO_RD_SYS_LOG                     0x04
#define ENOCEAN4_CMD_CO_WR_SYS_LOG                     0x05
#define ENOCEAN4_CMD_CO_WR_BIST                        0x06
#define ENOCEAN4_CMD_CO_WR_IDBASE                      0x07
#define ENOCEAN4_CMD_CO_RD_IDBASE                      0x08
#define ENOCEAN4_CMD_CO_WR_REPEATER                    0x09
#define ENOCEAN4_CMD_CO_RD_REPEATER                    0x0A
#define ENOCEAN4_CMD_CO_WR_FILTER_ADD                  0x0B
#define ENOCEAN4_CMD_CO_WR_FILTER_DEL                  0x0C
#define ENOCEAN4_CMD_CO_WR_FILTER_DEL_ALL              0x0D
#define ENOCEAN4_CMD_CO_WR_FILTER_ENABLE               0x0E
#define ENOCEAN4_CMD_CO_RD_FILTER                      0x0F
#define ENOCEAN4_CMD_CO_WR_WAIT_MATURITY               0x10
#define ENOCEAN4_CMD_CO_WR_SUBTEL                      0x11
#define ENOCEAN4_CMD_CO_WR_MEM                         0x12
#define ENOCEAN4_CMD_CO_RD_MEM                         0x13
#define ENOCEAN4_CMD_CO_RD_MEM_ADDRESS                 0x14
#define ENOCEAN4_CMD_CO_RD_SECURITY                    0x15
#define ENOCEAN4_CMD_CO_WR_SECURITY                    0x16
#define ENOCEAN4_CMD_CO_WR_LEARNMODE                   0x17
#define ENOCEAN4_CMD_CO_RD_LEARNMODE                   0x18
#define ENOCEAN4_CMD_CO_WR_SECUREDEVICE_ADD            0x19
#define ENOCEAN4_CMD_CO_WR_SECUREDEVICE_DEL            0x1A
#define ENOCEAN4_CMD_CO_RD_SECUREDEVICE_BY_INDEX       0x1B
#define ENOCEAN4_CMD_CO_WR_MODE                        0x1C
#define ENOCEAN4_CMD_CO_RD_NUMSECUREDEVICES            0x1D
#define ENOCEAN4_CMD_CO_RD_SECUREDEVICE_BY_ID          0x1E
#define ENOCEAN4_CMD_CO_WR_SECUREDEVICE_ADD_PSK        0x1F
#define ENOCEAN4_CMD_CO_WR_SECUREDEVICE_SENDTEACHIN    0x20
#define ENOCEAN4_CMD_CO_WR_TEMPORARY_RLC_WINDOW        0x21
#define ENOCEAN4_CMD_CO_RD_SECUREDEVICE_PSK            0x22
#define ENOCEAN4_CMD_CO_RD_DUTYCYCLE_LIMIT             0x23
#define ENOCEAN4_CMD_CO_SET_BAUDRATE                   0x24
#define ENOCEAN4_CMD_CO_GET_FREQUENCY_INFO             0x25
#define ENOCEAN4_CMD_CO_GET_STEPCODE                   0x27
#define ENOCEAN4_CMD_CO_WR_REMAN_CODE                  0x2E
#define ENOCEAN4_CMD_CO_WR_STARTUP_DELAY               0x2F
#define ENOCEAN4_CMD_CO_WR_REMAN_REPEATING             0x30
#define ENOCEAN4_CMD_CO_RD_REMAN_REPEATING             0x31
#define ENOCEAN4_CMD_CO_SET_NOISETHRESHOLD             0x32
#define ENOCEAN4_CMD_CO_GET_NOISETHRESHOLD             0x33
#define ENOCEAN4_SA_WR_LEARNMODE                       0x01
#define ENOCEAN4_SA_RD_LEARNMODE                       0x02
#define ENOCEAN4_SA_WR_LEARNCONFIRM                    0x03
#define ENOCEAN4_SA_WR_CLIENTLEARNRQ                   0x04
#define ENOCEAN4_SA_WR_RESET                           0x05
#define ENOCEAN4_SA_RD_LEARNEDCLIENTS                  0x06
#define ENOCEAN4_SA_WR_RECLAIMS                        0x07
#define ENOCEAN4_SA_WR_POSTMASTER                      0x08
#define ENOCEAN4_SA_RD_MAILBOX_STATUS                  0x09
#define ENOCEAN4_SA_DEL_MAILBOX                        0x0A
#define ENOCEAN4_R820_RD_CHANNEL                       0x02
#define ENOCEAN4_R802_WR_CHANNEL                       0x01

#define ENOCEAN4_57600_BAUDRATE                        0x00
#define ENOCEAN4_115200_BAUDRATE                       0x01
#define ENOCEAN4_230400_BAUDRATE                       0x02
#define ENOCEAN4_460800_BAUDRATE                       0x03
#define ENOCEAN4_COMPATIBLE_MODE_ERP1                  0x00
#define ENOCEAN4_ADVANCED_MODE_ERP2                    0x01
#define ENOCEAN4_ENABLE                                0x01
#define ENOCEAN4_DISABLE                               0x00
#define ENOCEAN4_FILTER_TYPE_DEV_ID                    0x00
#define ENOCEAN4_FILTER_TYPE_RORG                      0x01
#define ENOCEAN4_FILTER_TYPE_DBM                       0x02
#define ENOCEAN4_FILTER_TYPE_DEST_ID                   0x03
#define ENOCEAN4_BLOCK_RADIO_INTER                     0x00
#define ENOCEAN4_APPLY_RADIO_INTER                     0x80
#define ENOCEAN4_BLOCK_FILTERED_RPT                    0x40
#define ENOCEAN4_APPLY_FILTERED_RPT                    0xC0
#define ENOCEAN4_RPT_OFF                               0x00
#define ENOCEAN4_RPT_ON_ALL                            0x01
#define ENOCEAN4_RPT_ON_FILTERED                       0x02
#define ENOCEAN4_RPT_LEVEL_1                           0x01
#define ENOCEAN4_RPT_LEVEL_2                           0x02

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
typedef struct {

    uint16_t   data_length;
    uint8_t    opt_length;
    uint8_t    packet_type;
    uint8_t    data_buff[ 256 ];

} enocean4_packet_t;

typedef void ( *enocean4_hdl_t )( enocean4_packet_t*, uint8_t* );
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

    enocean4_hdl_t  driver_hdl;
    uint8_t response_ready;
    uint8_t rx_dat[ 270 ];

} enocean4_t;

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

    
} enocean4_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t enocean4_error_t;

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
void enocean4_cfg_setup ( enocean4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param enocean4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ENOCEAN4_RETVAL enocean4_init ( enocean4_t *ctx, enocean4_cfg_t *cfg );

/**
 * @brief Set RST ( reset ) pin state.
 * 
 * @param ctx  Click object.
 * @param enocean4 Click object.
 * @param statte Pin state ( 1 or 0 ).
 */
void enocean4_set_rst_pin ( enocean4_t *ctx, uint8_t state );

/**
 * @brief Generic write function.
 * 
 * @param ctx  Click object.
 * @param enocean4 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void enocean4_generic_write ( enocean4_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx  Click object.
 * @param enocean4 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t enocean4_generic_read ( enocean4_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Handler Set function.
 *
 * @param ctx  Click object.
 * @param handler  Pointer to the function that should be performed
 *
 * @description This function sets handler on the function that should be performed,
 * for example function for the results logging.
 */
void enocean4_response_handler_set( enocean4_t *ctx, void ( *handler )( enocean4_packet_t*, uint8_t* ) );

/**
 * @brief UART Interrupt Routine function
 *
 * @param ctx  Click object.
 *
 * @description This function reads response bytes from the module and sets a flag when response is ready.
 */
void enocean4_uart_isr( enocean4_t *ctx );

/**
 * @brief Response Proccesing function.
 *
 * @param ctx  Click object.
 * @returns 0 - OK, or determined error code
 *
 * @description This function performs a response proccesing and calls handler function if response is valid.
 */
uint8_t enocean4_process ( enocean4_t *ctx );

/**
 * @brief Response Ready Check function.
 *
 * @param ctx  Click object.
 * @returns 0 - Response is not ready, 1 - Response is ready
 *
 * @description This function checks the response ready flag and if flag is set, clears a flag.
 */
uint8_t enocean4_response_ready ( enocean4_t *ctx );

/**
 * @brief Reset function
 *
 * @param ctx  Click object.
 * 
 * @description This function performs a module reset.
 */
void enocean4_reset ( enocean4_t *ctx );

/**
 * @brief Packet Send function
 *
 * @param ctx  Click object.
 * @param packet  Packet data to be sent
 *
 * @returns 0x00 - OK, 0xFC - Invalid packet size
 *
 * @description This function allows user to send a valid packet data to the module by using UART interface.
 * @note Packet data can be desired command, or telegram, sub telegram, message, configurations...
 */
uint8_t enocean4_send_packet ( enocean4_t *ctx, enocean4_packet_t *packet );

#ifdef __cplusplus
}
#endif
#endif  // _ENOCEAN4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
