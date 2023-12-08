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
 * \brief This file contains API for LR 5 Click driver.
 *
 * \addtogroup lr5 LR 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LR5_H
#define LR5_H

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
#define LR5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.wk  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LR5_RETVAL  uint8_t

#define LR5_OK           0x00
#define LR5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup response Response Macros
 * \{
 */
#define RESPONSE_BIT                  0x80
#define FRAME_HEADER                  0xAA
/** \} */

/**
 * \defgroup cmd_macros Command macros
 * \{
 */
#define RESET_CMD                     0x30
#define FACTORY_RESET_CMD             0x31
#define EEPROM_WRITE_CMD              0x32
#define EEPROM_READ_CMD               0x33
#define GET_FW_VERSION_CMD            0x34
#define GET_SERIALNO_CMD              0x35
#define GET_DEV_EUI_CMD               0x36
#define JOIN_CMD                      0x40
#define JOIN_IND                      0x41
#define GET_ACT_STATUS_CMD            0x42
#define SET_APP_KEY_CMD               0x43
#define SET_APP_SESSION_KEY_CMD       0x44
#define SET_NWK_SESSION_KEY_CMD       0x45
#define TX_MSG_CMD                    0x46
#define TX_MSG_CONFIRMED_IND          0x47
#define TX_MSG_UNCONFIRMED_IND        0x48
#define RX_MSG_IND                    0x49
#define GET_SESSION_STATUS_CMD        0x4A
#define SET_NEXT_DR_CMD               0x4B
#define SET_BATTERY_LVL_CMD           0x50
#define GET_BATTERY_LVL_CMD           0x51
#define SET_UPLINK_CNT_CMD            0x52
#define GET_UPLINK_CNT_CMD            0x53
#define SET_DOWNLINK_CNT_CMD          0x54
#define GET_DOWNLINK_CNT_CMD          0x55
#define SET_CH_MASK_CMD               0x57
#define GET_CH_PARAM_CMD              0x58
/** \} */

/**
 * \defgroup commands_parameters Settings for commands parameters
 * \{
 */
#define LR5_ABP                     0x00
#define LR5_OTAA                    0x01
#define LR5_UNRELIABLE_DATA_TX      0x00
#define LR5_RELIABLE_DATA_TX        0x01
#define LR5_SF10_125KHZ             0x00
#define LR5_SF9_125KHZ              0x01
#define LR5_SF8_125KHZ              0x02
#define LR5_SF7_125KHZ              0x03
#define LR5_SF8_500KHZ              0x04
#define LR5_CH_IDX_0                0x00
#define LR5_CH_IDX_1                0x01
#define LR5_CH_IDX_2                0x02
#define LR5_CH_IDX_3                0x03
#define LR5_CH_IDX_4                0x04
#define LR5_CH_IDX_5                0x05
#define LR5_CH_IDX_6                0x06
#define LR5_CH_IDX_7                0x07
#define LR5_CH_IDX_8                0x08
#define LR5_CH_IDX_9                0x09
#define LR5_CH_IDX_10               0x0A
#define LR5_CH_IDX_11               0x0B
#define LR5_CH_IDX_12               0x0C
#define LR5_CH_IDX_13               0x0D
#define LR5_CH_IDX_14               0x0E
#define LR5_CH_IDX_15               0x0F
/** \} */

/**
 * \defgroup ret_values_of_func Returned values of functions
 * \{
 */
#define LR5_FRAME_HEADER_ERR        0xFF
#define LR5_CMD_RESPONSE_ERR        0xFE
#define LR5_CHKSUM_ERR              0xFD
#define LR5_NBYTES_INVALID          0xFC
#define LR5_CH_IDX_INVALID          0xFB
#define LR5_OK                      0x00
#define LR5_RESPONSE_NOT_RECEIVED   0x00
#define LR5_RESPONSE_RECEIVED       0x01
#define LR5_CMD_RESPONSE_READY      0x01
#define LR5_IND_RESPONSE_READY      0x02
#define LR5_DATA_READY              0x00
#define LR5_DATA_NOT_READY          0x01
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
 * @brief Handler definition for data logging.
 */
typedef void ( *lr5_hdl_t )( uint8_t*, uint8_t*, uint8_t* );

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

    uint8_t command_code;
    uint8_t received_flag;
    uint8_t rx_dat[ 260 ];
    uint16_t rx_cnt;
    lr5_hdl_t driver_hdl;

} lr5_t;

/**
 * @brief Command structure definition.
 */
typedef struct 
{
    uint8_t   cmd_code;
    uint8_t   cmd_length;
    uint8_t   cmd_data[ 256 ];

} lr5_cmd_t;

/**
 * @brief Message command definition.
 */
typedef struct 
{
    uint8_t options;
    uint8_t port;
    uint8_t *msg_data;
    uint8_t msg_length;

} lr5_msg_t;


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

} lr5_cfg_t;


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
void lr5_cfg_setup ( lr5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LR5_RETVAL lr5_init ( lr5_t *ctx, lr5_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx       Click object.
 * @param data_buf  Buffer to be read.
 * @param max_len   Number of maximum bytes that can be read.
 * 
 * @description This function reads buffer of data using uart_read function.
 */
int32_t lr5_generic_read ( lr5_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Set Handler function
 *
 * @param ctx      Click object.
 * @param handler  Pointer on the function that should be performed
 *
 * @description This function sets handler on the function that should be performed.
 */
void lr5_response_handler_set ( lr5_t *ctx, void ( *handler )( uint8_t*, uint8_t*, uint8_t* ) );

/**
 * @brief UART ISR function
 *
 * @param ctx      Click object.
 * 
 * @description This function sets the flag when entire response packet is received
 * using lr5_process function in main.
 */
void lr5_uart_isr ( lr5_t *ctx );

/**
 * @brief Response Ready function
 *
 * @param ctx      Click object.
 * 
 * @description This function returns 1 if entire response from the module is received, 
 * or returns 0 if is not received. Also clears the response ready flag.
 */
LR5_RETVAL lr5_response_ready ( lr5_t *ctx );

/**
 * @brief Parser Task function
 *
 * @param ctx      Click object. 
 *
 * @returns 1 - Command response ready, 2 - Indication response ready, or determined error code
 *
 * @description This function makes a response from the MIPOT 32001409 module.
 *
 * @note The checksum and frame header checking will be included in this function.
 */
LR5_RETVAL lr5_task ( lr5_t *ctx );

/**
 * @brief HW Reset function
 *
 * @param ctx      Click object.  
 *
 * @description This function performs a HW reset and puts a device back to the normal mode 
 * by using RST pin.
 */
void lr5_hw_reset ( lr5_t *ctx );

/**
 * @brief Data Indication function
 *
 * @param ctx      Click object. 
 *
 * @description This function returns 0 when received radio frame transfer from the module 
 * to the host is started, or returns 1 if is not started.
 */
LR5_RETVAL lr5_data_indication ( lr5_t *ctx );

/**
 * @brief SW Reset Command
 *
 * @param ctx      Click object. 
 * 
 * @description This command performs a SW reset of the module.
 *
 * @note The response on this command will be sent immediately, but the reset will be performed after about 1 second.
 */
void lr5_reset_cmd ( lr5_t *ctx );

/**
 * @brief Factory Reset Command
 *
 * @param ctx      Click object. 
 * 
 * @description This command performs an EEPROM recovery to default values.
 *
 * @note This command is allowed only when the module is in idle state.
 */
void lr5_factory_reset_cmd ( lr5_t *ctx );

/**
 * @brief EEPROM Write Command
 *
 * @param ctx         Click object.  
 * @param start_addr  Address which from a data writing be started
 * @param data_in     Data to be written
 * @param n_bytes     Number of bytes to be written
 *
 * @returns 0x00 - OK, 0xFC - Invalid number of bytes
 *
 * @description This command performs an EEPROM data writing.
 *
 * @note This command is allowed only when the module is in idle state.
 */
LR5_RETVAL lr5_eeprom_write_cmd ( lr5_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief EEPROM Read Command
 *
 * @param ctx         Click object.  
 * @param start_addr  Address which from a data reading be started
 * @param n_bytes     Number of bytes to be read
 *
 * @returns 0x00 - OK, 0xFC - Invalid number of bytes
 *
 * @description This command performs an EEPROM data reading.
 */
LR5_RETVAL lr5_eeprom_read_cmd ( lr5_t *ctx, uint8_t start_addr, uint8_t n_bytes );

/**
 * @brief Get FW Version Command
 *
 * @param ctx         Click object. 
 *
 * @description This command allows user to get the 32bit firmware version.
 */
void lr5_get_fw_version_cmd ( lr5_t *ctx );

/**
 * @brief Get Mipot Serial Number Command
 *
 * @param ctx         Click object. 
 *
 * @description This command allows user to get the 32bit Mipot serial number.
 */
void lr5_get_serial_no_cmd ( lr5_t *ctx );

/**
 * @brief Get DevEUI Command
 *
 * @param ctx         Click object.  
 *
 * @description This command allows user to get DevEUI provided by Mipot.
 */
void lr5_get_dev_eui_cmd ( lr5_t *ctx );

/**
 * @brief Join Network Command
 *
 * @param ctx         Click object. 
 * @param mode        0 - ABP, 1 - OTAA
 *
 * @description This command performs a joining to the network.
 */
void lr5_join_cmd ( lr5_t *ctx, uint8_t mode );

/**
 * @brief Get Activation Status Command
 *
 * @param ctx         Click object. 
 * 
 * @description This command allows user to get the module activation status.
 */
void lr5_get_activation_status_cmd ( lr5_t *ctx );

/**
 * @brief Set App Key Command
 *
 * @param ctx         Click object.  
 * @param app_key     Data to be written
 *
 * @description This command performs the app key data writing to the EEPROM.
 * @note app_key - 16 bytes in Little Endian Order, needed for OTAA procedure.
 */
void lr5_set_app_key_cmd ( lr5_t *ctx, uint8_t *app_key );

/**
 * @brief Set App Session Key Command
 *
 * @param ctx         Click object.  
 * @param app_s_key   Data to be written
 *
 * @description This command performs the app session key data writing to the EEPROM.
 * @note app_s_key - 16 bytes in Little Endian Order, needed for ABP procedure.
 */
void lr5_set_app_session_key_cmd ( lr5_t *ctx, uint8_t *app_s_key );

/**
 * @brief Set Nwk Session Key Command
 *
 * @param ctx         Click object.  
 * @param nwk_s_key   Data to be written
 *
 * @description This command performs the nwk session key data writing to the EEPROM.
 * @note nwk_s_key - 16 bytes in Little Endian Order, needed for ABP procedure.
 */
void lr5_set_nwk_session_key_cmd ( lr5_t *ctx, uint8_t *nwk_s_key );

/**
 * @brief TX Message Command
 *
 * @param ctx         Click object.  
 * @param msg         TX Message object.  
 * <pre>
 * Msg structure arguments:
 *  - options        0 - Unreliable data transmission, 1 - Reliable data transmission
 *  - port           Port number, from 1 to 223
 *  - msg_data       Data to transmit
 *  - msg_length     The maximum allowed data length depends upon set data rate
 * </pre>
 *
 * @returns 0x00 - OK, 0xFC - Invalid number of bytes
 *
 * @description This command performs the transmission of radio frame.
 */
LR5_RETVAL lr5_tx_msg_cmd ( lr5_t *ctx, lr5_msg_t *msg );

/**
 * @brief Get Session Status Command
 *
 * @param ctx         Click object. 
 * 
 * @description This command allows user to get the module current status.
 */
void lr5_get_session_status_cmd ( lr5_t *ctx );

/**
 * @brief Set Next TX Data Rate Command
 *
 * @param ctx         Click object.  
 * @param data_rate   Data Rate selection, from 0 to 4
 *
 * @description This command allows user to set next transmission data rate.
 *
 * @note The value is stored in RAM memory.
 */
void lr5_set_next_dr_cmd ( lr5_t *ctx, uint8_t data_rate );

/**
 * @brief Set Battery Level Command
 *
 * @param ctx             Click object.  
 * @param battery_level   0 - The end-device is connected to an external power source
 *                        1...254 - The battery level
 *                        255 - The end-device was not able to measure battery level
 *
 * @description This command allows user to set the battery level.
 */
void lr5_set_battery_level_cmd ( lr5_t *ctx, uint8_t battery_level );

/**
 * @brief Get Battery Level Command
 *
 * @param ctx         Click object. 
 * 
 * @description This command allows user to get the battery level value.
 */
void lr5_get_battery_level_cmd ( lr5_t *ctx );

/**
 * @brief Set Uplink Counter Command
 *
 * @param ctx         Click object.  
 * @param uplink_cnt  The 32bit uplink counter
 *
 * @description This command allows user to set the uplink counter in RAM memory.
 */
void lr5_set_uplink_cnt_cmd ( lr5_t *ctx, uint32_t uplink_cnt );

/**
 * @brief Get Uplink Counter Command
 *
 * @param ctx         Click object. 
 * 
 * @description This command allows user to get the uplink counter from RAM memory.
 */
void lr5_get_uplink_cnt_cmd ( lr5_t *ctx );

/**
 * @brief Set Downlink Counter Command
 *
 * @param ctx            Click object.  
 * @param downlink_cnt   The 32bit downlink counter
 *
 * @description This command allows user to set the downlink counter in RAM memory.
 */
void lr5_set_downlink_cnt_cmd ( lr5_t *ctx, uint32_t downlink_cnt );

/**
 * @brief Get Downlink Counter Command
 *
 * @param ctx         Click object. 
 * 
 * @description This command allows user to get the downlink counter from RAM memory.
 */
void lr5_get_downlink_cnt_cmd ( lr5_t *ctx );

/**
 * @brief Set Channels Mask Command
 *
 * @param ctx         Click object.  
 * @param ch_mask     The 9 bytes mask for all channels between 0 and 71
 *                    The first byte is mask for channels between 0 and 7
 *                    The MSB of each byte is the lowest channel index
 *
 * @description This command allows user to set the channels mask to enable or disable 
 *              a group of channels.
 *
 * @note These settings will be stored in RAM memory.
 */
void lr5_set_ch_mask_cmd ( lr5_t *ctx, uint8_t *ch_mask );

/**
 * @brief Get Channel Parameters Command
 *
 * @param ctx         Click object.  
 * @param ch_idx      Channel index from 0 to 15
 *
 * @returns 0x00 - OK, 0xFB - Invalid channel index
 *
 * @description This command allows user to get the parameters for desired channel.
 */
LR5_RETVAL lr5_get_ch_param_cmd ( lr5_t *ctx, uint8_t ch_idx );

#ifdef __cplusplus
}
#endif
#endif  // _LR5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
