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
 * \brief This file contains API for LR 3 Click driver.
 *
 * \addtogroup lr3 LR 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LR3_H
#define LR3_H

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
#define LR3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.wk = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LR3_RETVAL  uint8_t

#define LR3_OK           0x00
#define LR3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup response Response
 * \{
 */
#define FRAME_HEADER        0xAA
#define RESPONSE_BIT        0x80
/** \} */

/**
 * \defgroup lr_commands LR Commands
 * \{
 */
#define LR3_CMD_RESET                       0x30
#define LR3_CMD_FACTORY_RESET               0x31
#define LR3_CMD_EEPROM_WRITE                0x32
#define LR3_CMD_EEPROM_READ                 0x33
#define LR3_CMD_GET_FW_VERSION              0x34
#define LR3_CMD_GET_SERIAL_NO               0x35
#define LR3_ENABLE_PAIRING                  0x40
#define LR3_GET_NETWORK_TABLE_SIZE          0x42
#define LR3_GET_NETWORK_TABLE_ROW           0x43
#define LR3_DEL_NET_TABLE_ROW               0x44
#define LR3_DEL_ALL_NETWORK_TABLE           0x45
#define LR3_GET_PAIRING_REQUEST             0x48
#define LR3_GET_ACTIVATION_STATUS           0x4A
#define LR3_TX_MESSAGE                      0x50
#define LR3_CHECK_LINK_REQUEST              0x56
#define LR3_SET_APP_KEY                     0x58

#define LR3_INDICATES_DEVICE_PAIRING        0x41
#define LR3_INDICATES_PAIRING_CONFIRM       0x49
#define LR3_INDICATES_TX_MSG_CONFIRMED      0x51
#define LR3_INDICATES_TX_MSG_UNCONFIRMED    0x52
#define LR3_INDICATES_RX_MSG                0x53
#define LR3_INDICATES_LINK_CHECK            0x57
#define LR3_INDICATES_TX_SESSION_ABORT      0x59

#define LR3_OK                              0x00
#define LR3_ERR_ADDR_RANGE                  0x01
#define LR3_ERR_NOT_IDLE                    0x02

#define LR3_ERR_PL_LEN                      0xFC
#define LR3_ERR_CHKSUM                      0xFD
#define LR3_ERR_RESPONSE                    0xFE
#define LR3_ERR_HEADER                      0xFF

#define LR3_UNCONFIRMED_DATA_TX             0x00
#define LR3_CONFIRMED_DATA_TX               0x01

#define LR3_BROADCAST_MESSAGE               0xFFFFFFFF
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define LR3_MODULE_POWER_ON   1
#define LR3_MODULE_POWER_OFF  0
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
 * @brief LR3_TYPES Types.
 */
typedef void ( *lr3_ind_hdl_t )( uint8_t *cmd, uint8_t* p_load_size, uint8_t *p_load );

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t wk;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    lr3_ind_hdl_t ind_handler;
} lr3_t;

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
    pin_name_t wk;
    pin_name_t int_pin;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} lr3_cfg_t;

typedef struct {

    uint8_t command;
    uint8_t payload_size;
    uint8_t payload[ 255 ];
    
} lr3_message_t;

typedef struct {

    uint8_t *data_in;
    uint8_t n_bytes;
    uint32_t destination_id;
    uint8_t option;
    
} lr3_tx_msg_t;

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
void lr3_cfg_setup ( lr3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LR3_RETVAL lr3_init ( lr3_t *ctx, lr3_cfg_t *cfg );

/**
 * @brief Check sum function.
 *
 * @param ctx Click object.
 * @param cmd Command structure.
 * 
 * @returns Sum
 *
 * @description This function returns sum of all elements in Command structure.
 */
uint8_t lr3_chk_sum ( lr3_message_t *cmd );

/**
 * @brief Generic read function.
 *
 * @param ctx         Click object.
 * @param data_buf    Data buffer for read data.
 * @param max_len     The maximum length of data that can be read.
 *
 * @returns Number of read data.
 *
 * @description This function read maximum length of data.
 */
int32_t lr3_generic_read ( lr3_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic write function.
 * @param lr3 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void lr3_generic_write ( lr3_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Hardware reset function
 *
 * @param ctx  Click object.
 *
 * @description Resets device by setting pin and after that puts device back in normal operation mode.
 */
void lr3_hard_reset ( lr3_t *ctx );

/**
 * @brief Wake Up function
 *
 * @param ctx       Click object. 
 * @param state     0 - wake up, 1 - shutdown
 *
 * @description Puts device in shutdown mode or wake up device depending on state.
 */
void lr3_wake_up ( lr3_t *ctx, uint8_t state );

/**
 * @brief Set indication handler function
 *
 * @param ctx       Click object. 
 * @param hdl       Pointer to void handler function
 *
 * @description Function reads indications (response) to determined command.
 */
void lr3_set_ind_handler ( lr3_t *ctx, lr3_ind_hdl_t hdl );

/**
 * @brief Command function
 *
 * @param ctx        Click object. 
 * @param msg        Pointer to command witch be sent
 * @param rsp        Pointer to output where response be placed
 *
 * @returns 0 - OK, 1 - Check Sum Error
 *
 * @description Function executes commands and reads response on executed commands. 
 *              Also checks CRC error report.
 */
uint8_t lr3_command ( lr3_t *ctx, lr3_message_t *msg, lr3_message_t *rsp );

/**
 * @brief Process function
 *
 * @param ctx  Click object.
 * @returns 0 - OK, other - ERROR
 *
 * @description Function executes reading indications and forwards indications to handler.
 */
uint8_t lr3_read_message_process ( lr3_t *ctx );

/**
 * @brief Software reset function
 *
 * @param ctx  Click object.
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function resets module by sending command.
 */
LR3_RETVAL lr3_soft_reset ( lr3_t *ctx );

/**
 * @brief Factory reset function
 *
 * @param ctx  Click object.
 * 
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *         A value different from 0 is ERROR
 *
 * @description Function performs the recovery of EEPROM default values.
 */
LR3_RETVAL lr3_factory_reset ( lr3_t *ctx );

/**
 * @brief EEPROM write function
 *
 * @param ctx       Click object. 
 * @param address   EEPROM Address where data be written
 * @param n_bytes   Number of bytes witch be written (max 254)
 * @param data_in   Pointer to buffer witch from data be written
 *
 * @returns 0 - OK, 1 - Invalid address, 252 - Payload Length Error, 253 - Check Sum Error, 
 *         254 - Response Error, 255 - Header Error
 *
 * @description Function writes data to EEPROM.
 */
LR3_RETVAL lr3_write_eeprom ( lr3_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in );

/**
 * @brief EEPROM read function
 *
 * @param ctx             Click object.  
 * @param address         EEPROM Address witch from data be read
 * @param n_bytes         Number of bytes witch be read (max 254)
 * @param data_out        Pointer to buffer where data be stored
 *
 * @returns 0 - OK, 252 - Payload Length Error, 253 - Check Sum Error, 254 - Response Error,
 *         255 - Header Error or Data is empty
 *
 * @description Function reads data from EEPROM.
 */
LR3_RETVAL lr3_read_eeprom ( lr3_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_out );

/**
 * @brief Get FW Version function
 *
 * @param ctx                Click object.  
 * @param fw_version         Pointer to buffer where FW Version be stored
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function gets 32-bit FW version.
 */
LR3_RETVAL lr3_get_fw_version ( lr3_t *ctx, uint32_t *fw_version );

/**
 * @brief Get Serial Number function
 *
 * @param ctx           Click object.  
 * @param serial_no     Pointer to buffer where Serial Number be stored
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function gets 32-bit Serial Number.
 */
LR3_RETVAL lr3_get_serial_no ( lr3_t *ctx, uint32_t *serial_no );

/**
 * @brief Enable Pairing function
 *
 * @param ctx        Click object.  
 * @param state      
 * <pre> 
 *      state = 0 - disable pairing procedure
 *      state != 0 - enable pairing procedure
 * </pre>
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function enables or disables network the pairing procedure.
 */
LR3_RETVAL lr3_enable_pairing ( lr3_t *ctx, uint8_t state );

/**
 * @brief Get Network Table Size function
 *
 * @param ctx        Click object.  
 * 
 * @returns 253 - Check Sum Error, 254 - Response Error, 255 - Header Error, 
 *          or return a Network Table size
 *
 * @description Function gets from MASTER module the size of Network Table.
 */
LR3_RETVAL lr3_get_network_table_size ( lr3_t *ctx );

/**
 * @brief Get Network Table Row function
 *
 * @param ctx           Click object.   
 * @param index         index of Network Table row and must be between 0 to Table size - 1
 * @param data_out      Pointer to buffer where Network Table row data be stored
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function gets a Network Table row from index. The first 4 bytes is device ID
 *              and the fifth byte is the byte received at pairing phase.
 */
LR3_RETVAL lr3_get_network_table_row( lr3_t *ctx, uint8_t index, uint8_t *data_out );

/**
 * @brief Delete Network Table Row function
 *
 * @param ctx         Click object.   
 * @param device_id   Pointer to buffer where device ID is placed
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 
 *          255 - Header Error or Device not found
 *
 * @description Function deletes a Network Table row from module Serial Number.
 */
LR3_RETVAL lr3_delete_network_table_row ( lr3_t *ctx, uint8_t *device_id );

/**
 * @brief Delete All Network Table function
 *
 * @param ctx        Click object.  
 * 
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error or Failure
 *
 * @description Function deletes whole Network Table.
 */
LR3_RETVAL lr3_delete_all_network_table ( lr3_t *ctx );

/**
 * @brief Radio frame Transmission function
 *
 * @param ctx        Click object.  
 * @param tx_msg
 * <pre>
 * Structure arguments:
 * - data_in               Pointer to buffer witch from data be sent
 * - n_bytes               Number of bytes witch be sent (max 253)
 * - destination_id        Destination device Serial Number (4 bytes)
 * - option                     0bxxxxxxx0 - Unconfirmed Data Transmission
 *                              0bxxxxxxx1 - Confirmed Data Transmission
 * </pre>
 *
 * @returns 0 - OK, 1 - Device busy, 2 - Device not activated, 252 - Payload Length Error,  
 *         253 - Check Sum Error, 254 - Response Error, 255 - Header Error       
 *
 * @description Function performs the transmission of radio frames.
 */
LR3_RETVAL lr3_tx_message ( lr3_t *ctx, lr3_tx_msg_t *tx_msg );

/**
 * @brief Get Pairing Request function
 *
 * @param ctx        Click object. 
 * 
 * @returns 0 - OK, 1 - Busy, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function requests a pairing to a network.
 */
LR3_RETVAL lr3_get_pairing_request ( lr3_t *ctx );

/**
 * @brief Get Activation Status function
 *
 * @param ctx        Click object.  
 * @param data_out    Pointer to buffer where MASTER Serial Number (4 bytes) be placed
 *
 * @returns 0 - Not activated, 1 - Paired to a network, 253 - Check Sum Error, 
 *          254 - Response Error, 255 - Header Error
 *
 * @description Function gets the module activation status.
 */
LR3_RETVAL lr3_get_activation_status ( lr3_t *ctx, uint8_t *data_out );

/**
 * @brief Radio frame Transmission function
 *
 * @param ctx           Click object.  
 * @param power         Defines the power, from 2 to 14 dBm (suggested value is 11 dBm)
 * @param message_num   Defines the number of messages to be transmitted, from 4 to 20 
 *                      (suggested value is 5)
 * @param message_th    Defines pass/fail criteria treshold as the number of received 
 *                      messages, from 1 to message_num (suggested value is 4)
 *
 * @returns 0 - OK, 1 - Device busy, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function initiates from END NODE a link check procedure between END NODE and MASTER.
 */
LR3_RETVAL lr3_check_link_request ( lr3_t *ctx, uint8_t power, uint8_t message_num, uint8_t message_th );

/**
 * @brief Set App Key function
 *
 * @param ctx        Click object.  
 * @param app_key    Pointer to buffer witch from 16 byte AppKey data be written
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function performs an EEPROM data write 16 byte AppKey data in Little Endian Order,
 *              needed for Application encryption customization.
 */
LR3_RETVAL lr3_set_app_key ( lr3_t *ctx, uint8_t *app_key );

#ifdef __cplusplus
}
#endif
#endif  // _LR3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
