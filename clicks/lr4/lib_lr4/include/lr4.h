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
 * \brief This file contains API for LR 4 Click driver.
 *
 * \addtogroup lr4 LR 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LR4_H
#define LR4_H

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
#define LR4_MAP_MIKROBUS( cfg, mikrobus ) \
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
#define LR4_RETVAL  uint8_t

#define LR4_OK           0x00
#define LR4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup response Response
 * \{
 */
#define LR4_FRAME_HEADER        0xAA
#define LR4_RESPONSE_BIT        0x80
/** \} */

/**
 * \defgroup lr_commands LR Commands
 * \{
 */
#define LR4_CMD_RESET                       0x30
#define LR4_CMD_FACTORY_RESET               0x31
#define LR4_CMD_EEPROM_WRITE                0x32
#define LR4_CMD_EEPROM_READ                 0x33
#define LR4_CMD_GET_FW_VERSION              0x34
#define LR4_CMD_GET_SERIAL_NO               0x35
#define LR4_CMD_GET_DEV_EUI                 0x36
#define LR4_CMD_JOIN                        0x40
#define LR4_CMD_GET_ACTIVATION_STATUS       0x42
#define LR4_CMD_SET_APP_KEY                 0x43
#define LR4_CMD_SET_APP_SESSION_KEY         0x44
#define LR4_CMD_SET_NWK_SESSION_KEY         0x45
#define LR4_CMD_TX_MSG                      0x46
#define LR4_CMD_GET_SESSION_STATUS          0x4A
#define LR4_CMD_SET_NEXT_DR                 0x4B
#define LR4_CMD_SET_BATTERY_LVL             0x50
#define LR4_CMD_GET_BATTERY_LVL             0x51
#define LR4_CMD_SET_UPLINK_CNT              0x52
#define LR4_CMD_GET_UPLINK_CNT              0x53
#define LR4_CMD_SET_DOWNLINK_CNT            0x54
#define LR4_CMD_GET_DOWNLINK_CNT            0x55
#define LR4_CMD_SET_CH_PARAMETERS           0x57
#define LR4_CMD_GET_CH_PARAMETERS           0x58

#define LR4_INDICATES_JOIN                  0x41
#define LR4_INDICATES_TX_MSG_CONFIRMED      0x47
#define LR4_INDICATES_TX_MSG_UNCONFIRMED    0x48
#define LR4_INDICATES_RX_MSG                0x49

#define LR4_OK                              0x00
#define LR4_ERR_ADDR_RANGE                  0x01
#define LR4_ERR_NOT_IDLE                    0x02

#define LR4_ERR_PL_LEN                      0xFC
#define LR4_ERR_CHKSUM                      0xFD
#define LR4_ERR_RESPONSE                    0xFE
#define LR4_ERR_HEADER                      0xFF


#define LR4_JOIN_ACTIVATION_BY_PERSONALIZATION_MODE   0x00
#define LR4_JOIN_OVER_THE_AIR_ACTIVATION_MODE         0x01
#define LR4_GET_ACTIVATION_MODE                       0x00
#define LR4_GET_SESSION_STATUS_MODE                   0x01
#define LR4_SET_APP_KEY_MODE                          0x00
#define LR4_SET_NWK_SESSION_KEY_MODE                  0x01
#define LR4_UPLINK_CNT                                0x00
#define LR4_DOWNLINK_CNT                              0x01
#define LR4_CHANNEL_DISABLED                          0x00
#define LR4_CHANNEL_ENABLED                           0x01
#define LR4_UNCONFIRMED_TRANSMISSION                  0x00
#define LR4_CONFIRMED_TRANSMISSION                    0x01


#define LR4_STATUS_IDLE                               0x00
#define LR4_STATUS_BUSY                               0x01
#define LR4_STATUS_DEV_NOT_ACTIVATED                  0x02
#define LR4_STATUS_DELAYED                            0x03

#define LR4_STATUS_NOT_ACTIVATED                      0x00
#define LR4_STATUS_JOINING                            0x01
#define LR4_STATUS_JOINED                             0x02
#define LR4_STATUS_MAC_ERROR                          0x03
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define LR4_MODULE_POWER_ON   1
#define LR4_MODULE_POWER_OFF  0
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
 * @brief LR4_TYPES Types.
 */
typedef void ( *lr4_ind_hdl_t )( uint8_t *cmd, uint8_t* p_load_size, uint8_t *p_load );

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

    lr4_ind_hdl_t ind_handler;
} lr4_t;

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

} lr4_cfg_t;

typedef struct {

    uint8_t command;
    uint8_t payload_size;
    uint8_t payload[ 255 ];
    
} lr4_message_t;

typedef struct {

    uint8_t *data_in;
    uint8_t n_bytes;
    uint8_t port;
    uint8_t option;
    
} lr4_tx_msg_t;

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
void lr4_cfg_setup ( lr4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LR4_RETVAL lr4_init ( lr4_t *ctx, lr4_cfg_t *cfg );

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
int32_t lr4_generic_read ( lr4_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic write function.
 * @param lr4 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void lr4_generic_write ( lr4_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Hardware reset function
 *
 * @param ctx  Click object.
 *
 * @description Resets device by setting pin and after that puts device back in normal operation mode.
 */
void lr4_hard_reset ( lr4_t *ctx );

/**
 * @brief Wake Up function
 *
 * @param ctx       Click object. 
 * @param state     0 - wake up, 1 - shutdown
 *
 * @description Puts device in shutdown mode or wake up device depending on state.
 */
void lr4_wake_up ( lr4_t *ctx, uint8_t state );

/**
 * @brief Set indication handler function
 *
 * @param ctx       Click object. 
 * @param hdl       Pointer to void handler function
 *
 * @description Function reads indications (response) to determined command.
 */
void lr4_set_ind_handler ( lr4_t *ctx, lr4_ind_hdl_t hdl );

/**
 * @brief Command function
 *
 * @param ctx        Click object. 
 * @param msg        Pointer to command buffer
 * @param rsp        Pointer to output where response will be stored.
 *
 * @returns 0 - OK, 1 - Check Sum Error
 *
 * @description Function executes commands and reads response on executed commands. 
 *              Also checks CRC error report.
 */
uint8_t lr4_command ( lr4_t *ctx, lr4_message_t *msg, lr4_message_t *rsp );

/**
 * @brief Process function
 *
 * @param ctx  Click object.
 * @returns 0 - OK, other - ERROR
 *
 * @description Function executes reading indications and forwards indications to handler.
 */
uint8_t lr4_read_message_process ( lr4_t *ctx );

/**
 * @brief Software reset function
 *
 * @param ctx  Click object.
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function resets module by sending command.
 */
LR4_RETVAL lr4_soft_reset ( lr4_t *ctx );

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
LR4_RETVAL lr4_factory_reset ( lr4_t *ctx );

/**
 * @brief EEPROM write function
 *
 * @param ctx       Click object. 
 * @param address   EEPROM Address where data be written
 * @param n_bytes   Number of bytes which will be written (max 254)
 * @param data_in   Pointer to buffer which will be written.
 *
 * @returns 0 - OK, 1 - Invalid address, 252 - Payload Length Error, 253 - Check Sum Error, 
 *         254 - Response Error, 255 - Header Error
 *
 * @description Function writes data to EEPROM.
 */
LR4_RETVAL lr4_write_eeprom ( lr4_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in );

/**
 * @brief EEPROM read function
 *
 * @param ctx             Click object.  
 * @param address         EEPROM Address from which data will be read
 * @param n_bytes         Number of bytes which will be read (max 254)
 * @param data_out        Pointer to buffer where data be stored
 *
 * @returns 0 - OK, 252 - Payload Length Error, 253 - Check Sum Error, 254 - Response Error,
 *         255 - Header Error or Data is empty
 *
 * @description Function reads data from EEPROM.
 */
LR4_RETVAL lr4_read_eeprom ( lr4_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_out );

/**
 * @brief Get FW Version function
 *
 * @param ctx                Click object.  
 * @param fw_version         Pointer to buffer where FW Version could be stored
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function gets 32-bit FW version.
 */
LR4_RETVAL lr4_get_fw_version ( lr4_t *ctx, uint32_t *fw_version );

/**
 * @brief Get Serial Number function
 *
 * @param ctx           Click object.  
 * @param serial_no     Pointer to buffer where Serial Number could be stored
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function gets 32-bit Serial Number.
 */
LR4_RETVAL lr4_get_serial_no ( lr4_t *ctx, uint32_t *serial_no );

/**
 * @brief Get DevEUI function
 *
 * @param ctx        Click object.  
 * @param dev_eui    Pointer to buffer where devEUI data could be stored  
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function gets DevEUI provided by Mipot.
 */
LR4_RETVAL lr4_get_dev_eui ( lr4_t *ctx, uint8_t *dev_eui );

/**
 * @brief Join Network function
 *
 * @param ctx        Click object.
 * @param mode       0 - Activation by personalization, 1 - Over the air activation
 * 
 * @returns 0 - OK, 2 - Busy, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function performs the join network command.
 */
LR4_RETVAL lr4_join_network ( lr4_t *ctx, uint8_t mode );

/**
 * @brief Get Status function
 *
 * @param ctx           Click object.   
 * @param status_mode   0 - Get Activation Status, 1 - Get Session Status
 *
 * @returns 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *          0 - Not activated, 1 - Joining, 2 - Joined, 3 - MAC ERROR; when statusMode is 0
 *          0 - Idle, 1 - Busy, 2 - Device not activated, 3 - Delayed; when statusMode is 1
 *
 * @description Function gets the module activation and session status.
 */
LR4_RETVAL lr4_get_status ( lr4_t *ctx, uint8_t status_mode );

/**
 * @brief Set Key function
 *
 * @param ctx         Click object.   
 * @param key_data    Pointer to buffer which contains key data
 * @param key_mode    0 - Set App Key, 1 - Set App Session Key, 2 - Set NWK Session Key
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function sets 16 byte key in Little Endian Order. App key is needed for OTAA procedure, 
                and App Session key and NWK Session key is needed for APB procedure.
 */
LR4_RETVAL lr4_set_key ( lr4_t *ctx, uint8_t *key_data, uint8_t key_mode );

/**
 * @brief Radio frame Transmission function
 *
 * @param ctx        Click object.  
 * @param tx_msg
 * <pre>
 * Structure arguments:
 * - data_in               Pointer to buffer that contains data for transmission.
 * - n_bytes               Number of bytes which will be sent (max 253)
 * - port                  From 1 to 223
 * - option                0bxxxxxxx0 - Unreliable Data Transmission, 0bxxxxxxx1 - Reliable Data Transmission
 * </pre>
 *
 * @returns 0 - OK, 252 - Payload Length Error, 253 - Check Sum Error, 254 - Response Error, 
 *          255 - Header Error, 1 - Device busy, 2 - Device not activated, 3 - Channel blocked by duty-cycle, 
 *          5 - Length not supported, 6 - End Node in silent state, 7 - Error
 *
 * @description Function performs the transmission of radio frames.
 */
LR4_RETVAL lr4_tx_message ( lr4_t *ctx, lr4_tx_msg_t *tx_msg );

/**
 * @brief Set Next Data Rate function
 *
 * @param ctx        Click object. 
 * @param data_rate  0 - SF12/125kHz, 1 - SF11/125kHz, 2 - SF10/125kHz, 3 - SF9/125kHz
 *                   4 - SF8/125kHz, 5 - SF7/125kHz, 6 - SF7/250kHz, 7 - FSK
 * 
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *          A value different from zero means that an error has occurred
 *
 * @description Function sets next transmission Data Rate.
 */
LR4_RETVAL lr4_set_next_tx_data_rate ( lr4_t *ctx, uint8_t data_rate );

/**
 * @brief Set Battery Level function
 *
 * @param ctx            Click object.  
 * @param battery_level  0 - The end-device is connected to an external power source
 *                       The battery level - 1 being at minimum and 254 being at maximum
 *                       255 - The end-device was not able to measure battery level

 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function sets Battery Level.
 */
LR4_RETVAL lr4_set_battery_level ( lr4_t *ctx, uint8_t battery_level );

/**
 * @brief Get Battery Level function
 *
 * @param ctx           Click object.  
 *
 * @returns 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *          0 - The end-device is connected to an external power source
 *          The battery level - 1 being at minimum and 254 being at maximum
 *          255 - The end-device was not able to measure battery level
 *
 * @description Function gets Battery Level.
 */
LR4_RETVAL lr4_get_battery_level ( lr4_t *ctx );

/**
 * @brief Set Counter function
 *
 * @param ctx        Click object.  
 * @param cnt        32-bit counter value
 * @param cnt_mode   0 - Set Uplink counter, 1 - Set Downlink counter
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function sets Uplink or Downlink counter.
 */
LR4_RETVAL lr4_set_counter ( lr4_t *ctx, uint32_t cnt, uint8_t cnt_mode );

/**
 * @brief Get Counter function
 *
 * @param ctx        Click object.  
 * @param cnt        Pointer to buffer where counter value could be stored
 * @param cnt_mode   0 - Get Uplink counter, 1 - Get Downlink counter
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *
 * @description Function gets Uplink or Downlink counter.
 */
LR4_RETVAL lr4_get_counter ( lr4_t *ctx, uint32_t *cnt, uint8_t cnt_mode );

/**
 * @brief Set Channel function
 *
 * @param ctx             Click object.  
 * @param index           From 3 to 15
 * @param freq            32-bit frequency value
 * @param data_rate_range Data Rate Max is most significant nibble (from 0 to 7)
 *                        Data Rate Min is less significant nibble (from 0 to 7)
 * @param status          0 - Disabled, 1 - Enabled
 *
 * @returns 0 - OK, 253 - Check Sum Error, 254 - Response Error, 255 - Header Error
 *          242 - Frequency out of range, 244 - MAC busy
 *
 * @description Function sets channel parameters and enable/disable optional channels.
 */
LR4_RETVAL lr4_set_channel ( lr4_t *ctx, uint8_t index, uint32_t freq, uint8_t data_rate_range, uint8_t status );

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
uint8_t lr4_chk_sum ( lr4_message_t *cmd );

#ifdef __cplusplus
}
#endif
#endif  // _LR4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
