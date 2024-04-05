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
 * \brief This file contains API for Nano LR Click driver.
 *
 * \addtogroup nanolr Nano LR Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NANOLR_H
#define NANOLR_H

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
#define NANOLR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.st  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NANOLR_RETVAL       uint8_t

#define NANOLR_OK           0x00
#define NANOLR_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup list_of_commands List of commands
 * \{
 */
#define NANOLR_CMD_DEV_INFO                                   0x01
#define NANOLR_CMD_DEV_STATE                                  0x04
#define NANOLR_CMD_RESET                                      0x05
#define NANOLR_CMD_FW_VER                                     0x06
#define NANOLR_CMD_RESTORE_DEF_SETTINGS                       0x07
#define NANOLR_CMD_SAVE_SETTINGS                              0x08
#define NANOLR_CMD_SERIAL_PORT_CFG                            0x09
#define NANOLR_CMD_OUTPUT_POWER                               0x10
#define NANOLR_CMD_OP_CHAN                                    0x11
#define NANOLR_CMD_ENERGY_SAVE                                0x13
#define NANOLR_CMD_PHYSICAL_ADR                               0x20
#define NANOLR_CMD_NETWORK_ADR                                0x21
#define NANOLR_CMD_NETWORK_ID                                 0x22
#define NANOLR_CMD_NETWORK_ROLE                               0x23
#define NANOLR_CMD_NETWORK_AUTO_SETTINGS                      0x24
#define NANOLR_CMD_NETWORK_PREF                               0x25
#define NANOLR_CMD_NETWORK_SECURITY                           0x26
#define NANOLR_CMD_NETWORK_JOIN_MODE                          0x27
#define NANOLR_CMD_NETWORK_STOP                               0x30
#define NANOLR_CMD_NETWORK_START                              0x31
#define NANOLR_CMD_SEND_DATA                                  0x50
#define NANOLR_CMD_RECEIVED_DATA                              0x60
#define NANOLR_CMD_ENTER_BOOTLOADER                           0x70
/** \} */

/**
 * \defgroup bootloading_phase Available only during bootloading phase!
 * \{
 */
#define NANOLR_SET_BOOTLOADER_OPTIONS                         0x71
#define NANOLR_ERASE_MEM                                      0x78
#define NANOLR_WRITE_MEM_CHUNK                                0x7A
#define NANOLR_READ_MEM_CHUNK                                 0x7B
#define NANOLR_COMMIT_FW                                      0x7F
/** \} */

/**
 * \defgroup execution_status_byte Execution status byte
 * \{
 */
#define NANOLR_SUCCESS                                        0x00
#define NANOLR_GENERIC_ERROR                                  0x01
#define NANOLR_PARAM_NOT_ACCEPTED                             0x02
#define NANOLR_OPERATION_TIMEOUT                              0x03
#define NANOLR_NO_MEMORY                                      0x04
#define NANOLR_UNSUPPORTED                                    0x05
#define NANOLR_BUSY                                           0x06
/** \} */

/**
 * \defgroup list_of_responses List of responses
 * \{
 */
#define NANOLR_DEV_INFO_RESP                                  0x81
#define NANOLR_DEV_STATE_RESP                                 0x84
#define NANOLR_RESET_RESP                                     0x85
#define NANOLR_FW_VER_RESP                                    0x86
#define NANOLR_RESTORE_DEF_SETTINGS_RESP                      0x87
#define NANOLR_SAVE_SETTINGS_RESP                             0x88
#define NANOLR_SERIAL_PORT_CFG_RESP                           0x89
#define NANOLR_OUTPUT_POWER_RESP                              0x90
#define NANOLR_OP_CHAN_RESP                                   0x91
#define NANOLR_ENERGY_SAVE_RESP                               0x93
#define NANOLR_PHYSICAL_ADR_RESP                              0xA0
#define NANOLR_NETWORK_ADR_RESP                               0xA1
#define NANOLR_NETWORK_ID_RESP                                0xA2
#define NANOLR_NETWORK_ROLE_RESP                              0xA3
#define NANOLR_NETWORK_AUTO_SETTINGS_RESP                     0xA4
#define NANOLR_NETWORK_PREF_RESP                              0xA5
#define NANOLR_NETWORK_SECURITY_RESP                          0xA6
/** \} */

/**
 * \defgroup baud_rate Baud rate
 * \{
 */
#define NANOLR_BAUD_RATE_MAINTAIN_SPEED                       0x00
#define NANOLR_BAUD_RATE_1200                                 0x01
#define NANOLR_BAUD_RATE_2400                                 0x02
#define NANOLR_BAUD_RATE_4800                                 0x03
#define NANOLR_BAUD_RATE_9600                                 0x04
#define NANOLR_BAUD_RATE_19200                                0x05
#define NANOLR_BAUD_RATE_38400                                0x06
#define NANOLR_BAUD_RATE_57600                                0x07
#define NANOLR_BAUD_RATE_115200                               0x08
/** \} */

/**
 * \defgroup model_id Model ID
 * \{
 */
#define NANOLR_DEVICE_ID_UNKNOWN                              0x00
#define NANOLR_DEVICE_ID_EMB_ZRF2XX                           0x20
#define NANOLR_DEVICE_ID_EMB_ZRF231XX                         0x24
#define NANOLR_DEVICE_ID_EMB_ZRF231PA                         0x26
#define NANOLR_DEVICE_ID_EMB_ZRF212XX                         0x28
#define NANOLR_DEVICE_ID_EMB_ZRF212B                          0x29
#define NANOLR_DEVICE_ID_EMB_Z253X                            0x30
#define NANOLR_DEVICE_ID_EMB_Z2530X                           0x34
#define NANOLR_DEVICE_ID_EMB_Z2530PA                          0x36
#define NANOLR_DEVICE_ID_EMB_Z2531X                           0x38
#define NANOLR_DEVICE_ID_EMB_Z2531PA_USB                      0x3A
#define NANOLR_DEVICE_ID_EMB_Z2538X                           0x3C
#define NANOLR_DEVICE_ID_EMB_Z2538PA                          0x3D
#define NANOLR_DEVICE_ID_EMB_WMBX                             0x40
#define NANOLR_DEVICE_ID_EMB_WMB169X                          0x44
#define NANOLR_DEVICE_ID_EMB_WMB169T                          0x45
#define NANOLR_DEVICE_ID_EMB_WMB169PA                         0x46
#define NANOLR_DEVICE_ID_EMB_WMB868X                          0x48
#define NANOLR_DEVICE_ID_EMB_WMB868                           0x49
#define NANOLR_DEVICE_ID_EMB_LRX                              0x50
#define NANOLR_DEVICE_ID_EMB_LR1272                           0x54
/** \} */

/**
 * \defgroup network_role Network role
 * \{
 */
#define NANOLR_NETWORK_ROLE_COORDINATOR                       0x00
#define NANOLR_NETWORK_ROLE_RESERVED                          0x01
#define NANOLR_NETWORK_ROLE_END_DEV                           0x02
/** \} */

/**
 * \defgroup single_byte_ind_device_state   Single byte indicating the device's state
 * \{
 */
#define NANOLR_DEV_STATE_BOOTING                              0x00
#define NANOLR_DEV_STATE_INSIDE_BOOTLOADER                    0x01
#define NANOLR_DEV_STATE_RDY_STARTUP_OP_SUCC                  0x10
#define NANOLR_DEV_STATE_RDY_STARTUP_OP_FAILED                0x11
#define NANOLR_DEV_STATE_OFFLINE                              0x20
#define NANOLR_DEV_STATE_CONNECTING                           0x21
#define NANOLR_DEV_STATE_TRANSPARENT_MODE_STARTUP             0x22
#define NANOLR_DEV_STATE_ONLINE                               0x30
#define NANOLR_DEV_STATE_DISCONNECTING                        0x40
#define NANOLR_DEV_STATE_RESERVED                             0x50
#define NANOLR_DEV_STATE_END_RECEIVING_WINDOW                 0x51
/** \} */

/**
 * \defgroup energy_save_mode Energy save mode
 * \{
 */
#define NANOLR_ENERGY_SAVE_MODE_ALWAYS_ON                     0x00
#define NANOLR_ENERGY_SAVE_MODE_RX_WINDOW                     0x01
#define NANOLR_ENERGY_SAVE_MODE_TX_ONLY                       0x02
/** \} */

/**
 * \defgroup operating_channel Operating channel
 * \{
 */
#define NANOLR_OP_CHANNEL_CH_1_868_1MHz                       0x01
#define NANOLR_OP_CHANNEL_CH_2_868_3MHz                       0x02
#define NANOLR_OP_CHANNEL_CH_3_868_5MHz                       0x03
#define NANOLR_OP_CHANNEL_CH_4_869_525MHz                     0x04
#define NANOLR_OP_CHANNEL_SPR_FCT_128                         0x07
#define NANOLR_OP_CHANNEL_SPR_FCT_256                         0x08
#define NANOLR_OP_CHANNEL_SPR_FCT_512                         0x09
#define NANOLR_OP_CHANNEL_SPR_FCT_1024                        0x0A
#define NANOLR_OP_CHANNEL_SPR_FCT_2048                        0x0B
#define NANOLR_OP_CHANNEL_SPR_FCT_4096                        0x0C
#define NANOLR_OP_CHANNEL_BANDWIDTH_125KHz                    0x00
#define NANOLR_OP_CHANNEL_BANDWIDTH_250KHz                    0x01
#define NANOLR_OP_CHANNEL_CODING_RATE_4_5                     0x01
#define NANOLR_OP_CHANNEL_CODING_RATE_4_6                     0x02
#define NANOLR_OP_CHANNEL_CODING_RATE_4_7                     0x03
#define NANOLR_OP_CHANNEL_CODING_RATE_4_8                     0x04
/** \} */

/**
 * \defgroup Network role Network role
 * \{
 */
#define NANOLR_NTW_ROLE_COORDINATOR                           0x00
#define NANOLR_NTW_ROLE_END_DEVICE                            0x02
/** \} */

/**
 * \defgroup network_preference Network preference
 * \{
 */
#define NANOLR_NTW_PREFERENCE_PROTOCOL_LR_EMB                 0x00
#define NANOLR_NTW_PREFERENCE_PROTOCOL_LR_WAN                 0x80
#define NANOLR_NTW_PREFERENCE_AUTO_JOIN_DISABLE               0x00
#define NANOLR_NTW_PREFERENCE_AUTO_JOIN_ENABLE                0x40
#define NANOLR_NTW_PREFERENCE_ADAPTIVE_DATA_RATE_DISABLE      0x00
#define NANOLR_NTW_PREFERENCE_ADAPTIVE_DATA_RATE_ENABLE       0x20
/** \} */

/**
 * \defgroup network_join_mode Network join mode
 * \{
 */
#define NANOLR_NTW_JOIN_MODE_ABP                              0x00
#define NANOLR_NTW_JOIN_MODE_OTAA                             0x01

#define NANOLR_RSP_READY                                      0x01
#define NANOLR_RSP_NOT_READY                                  0x00

#define NANOLR_ERR_CRC                                        0x01
#define NANOLR_ERR_STATUS_OK                                  0x00
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
 * @macro nanolr_err_t
 * @brief Driver Error type
 */
#define nanolr_err_t  uint8_t

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t st;
    digital_out_t rst;
    digital_out_t cts;

    // Input pins 

    digital_in_t gp1;
    digital_in_t rts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    char rx_data[ 256 ];
    uint16_t rsp_len;
    uint8_t rsp_rdy;

} nanolr_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t st;
    pin_name_t rst;
    pin_name_t cts;
    pin_name_t gp1;
    pin_name_t rts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} nanolr_cfg_t;

/**
 * @brief Click response structure definition.
 */
typedef struct
{
    uint16_t length;
    uint8_t message_id;
    uint8_t payload[ 256 ];
    uint8_t crc;

} nanolr_rsp_t;

/**
 * @brief Click network structure definition.
 */
typedef struct
{
    uint8_t channel;
    uint8_t spreading_factor;
    uint8_t bandwidth;
    uint8_t coding_rate;

} nanolr_network_t;

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
void nanolr_cfg_setup ( nanolr_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NANOLR_RETVAL nanolr_init ( nanolr_t *ctx, nanolr_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for NanoLR click.
 */
void nanolr_default_cfg ( nanolr_t *ctx );

/**
 * @brief Reset module.
 *
 * @param ctx Click object.
 *
 * @description The function resets the module.
 */
void nanolr_reset ( nanolr_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx       Click object.
 * @param data_buf  Data buffer for sends.
 * @param len       Number of bytes for sends.
 *
 * @description The function write specific number of data.
 */
void nanolr_generic_write ( nanolr_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx       Click object.
 * @param data_buf  Data buffer for read data.
 * @param max_len   The maximum length of data that can be read.
 *
 * @returns Number of reads data.
 *
 * @description The function read maximum length of data that is specified
 */
int32_t nanolr_generic_read ( nanolr_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Request to Send function
 *
 * @param ctx       Click object. 
 *
 * @returns 0 : inactive,  1 : active
 *
 * @description The function Request to Send indicate a desire to transmit.
 */
uint8_t nanolr_request_2_send ( nanolr_t *ctx );

/**
 * @brief Clear to Send function
 *
 * @param ctx       Click object.  
 * @param state     0 : inactive, 1 : active
 *
 * @description The function in response the DCE asserts CTS to grant permission.
 */
void nanolr_clear_2_send ( nanolr_t *ctx, uint8_t state );

/**
 * @brief Get GP1 pin state function
 *
 * @param ctx       Click object.   
 *
 * @returns 0 : inactive,  1 : active
 *
 * @description The function get states of the GP1 ( PWM ) pin that can handle interrupts.
 */
uint8_t nanolr_get_gp1_pin ( nanolr_t *ctx );

/**
 * @brief Set ST pin state function
 *
 * @param ctx       Click object.   
 * @param state     0 : inactive, 1 : active
 *
 * @description The function set states of the ST ( AN ) pin.
 */
void nanolr_set_st_pin ( nanolr_t *ctx, uint8_t state );

/**
 * @brief Get device information function
 *
 * @param ctx       Click object.
 * 
 * @description The function requires device information.
 */
void nanolr_get_device_info ( nanolr_t *ctx );

/**
 * @brief Get device state function
 *
 * @param ctx       Click object.
 * 
 * @description The function requires state information.
 */
void nanolr_get_device_state ( nanolr_t *ctx );

/**
 * @brief Software reset function
 *
 * @param ctx       Click object.
 * 
 * @description The function sends a command for the software reset on the device.
 */
void nanolr_sw_reset ( nanolr_t *ctx );

/**
 * @brief Get firmware version function
 *
 * @param ctx       Click object.
 * 
 * @description The function requires device firmware version.
 */
void nanolr_get_fw_ver ( nanolr_t *ctx );

/**
 * @brief Restore to factory function
 *
 * @param ctx       Click object.
 * 
 * @description The function sends a command to reset the device to factory settings.
 */
void nanolr_restore_2_factory ( nanolr_t *ctx );

/**
 * @brief Restore to factory function
 *
 * @param ctx       Click object.
 * 
 * @description The function sends a command to save the current settings.
 */
void nanolr_save_settings ( nanolr_t *ctx );

/**
 * @brief Get output power function
 *
 * @param ctx       Click object.
 * 
 * @description The function retrieve the current output power.
 */
void nanolr_get_output_power ( nanolr_t *ctx );

/**
 * @brief Get operating channel function
 *
 * @param ctx       Click object.
 * 
 * @description The function retrieve the current channel.
 */
void nanolr_get_operating_channel ( nanolr_t *ctx );

/**
 * @brief Set output power function
 *
 * @param ctx       Click object. 
 * @param out_pwr   Output power [+2, +19] dBm
 *
 * @description The function retrieve the current output power.
 */
void nanolr_set_output_power ( nanolr_t *ctx, uint8_t out_pwr );

/**
 * @brief Set operating channel function
 *
 * @param ctx       Click object. 
 * @param channel
 * <pre>
 * - 0x01 ( NANOLR_OP_CHANNEL_CH_1_868_1MHz )    : 868.100 MHz;
 * - 0x02 ( NANOLR_OP_CHANNEL_CH_2_868_3MHz )    : 868.300 MHz;
 * - 0x03 ( NANOLR_OP_CHANNEL_CH_3_868_5MHz )    : 868.500 MHz;
 * - 0x04 ( NANOLR_OP_CHANNEL_CH_4_869_525MHz )  : 869.525 MHz;
 * </pre> 
 *
 * @param spreading_factor
 * <pre> 
 * - 0x07 ( NANOLR_OP_CHANNEL_SPR_FCT_128 )      : Chips/symbol 128;
 * - 0x08 ( NANOLR_OP_CHANNEL_SPR_FCT_256 )      : Chips/symbol 256;
 * - 0x09 ( NANOLR_OP_CHANNEL_SPR_FCT_512 )      : Chips/symbol 512;
 * - 0x0A ( NANOLR_OP_CHANNEL_SPR_FCT_1024 )     : Chips/symbol 1024;
 * - 0x0B ( NANOLR_OP_CHANNEL_SPR_FCT_2048 )     : Chips/symbol 2048;
 * - 0x0C ( NANOLR_OP_CHANNEL_SPR_FCT_4096 )     : Chips/symbol 4096;
  * <pre>
 *
 * @param bandwidth
 * <pre>
 * - 0x00 ( NANOLR_OP_CHANNEL_BANDWIDTH_125KHZ ) : 125 kHz;
 * - 0x01 ( NANOLR_OP_CHANNEL_BANDWIDTH_250KHZ ) : 250 kHz;
 * </pre>
 *
 * @param coding_rate
 * <pre> 
 * - 0x00 ( NANOLR_OP_CHANNEL_CODING_RATE_4_5 )  : Coding Rate 4/5;
 * - 0x01 ( NANOLR_OP_CHANNEL_CODING_RATE_4_6 )  : Coding Rate 4/6;
 * - 0x02 ( NANOLR_OP_CHANNEL_CODING_RATE_4_7 )  : Coding Rate 4/7;
 * - 0x03 ( NANOLR_OP_CHANNEL_CODING_RATE_4_8 )  : Coding Rate 4/8;
 * </pre> 
 *
 * @description The function set the current channel.
 *
 * @note The operating channel can only be changed when network is down. When using the LRWAN 
 * network, the channel is automatically assigned by the concentrator.
 */
void nanolr_set_operating_channel ( nanolr_t *ctx, nanolr_network_t *net );

/**
 * @brief Save energy on function
 *
 * @param ctx       Click object.
 * 
 * @description The function sends a command
 * to set save energy mode: LRWANTM Class C / LREMB reception anytime
 * of the device.
 */
void nanolr_save_energy_always_on ( nanolr_t *ctx );

/**
 * @brief Save energy rx window function
 *
 * @param ctx       Click object.
 *  
 * @description The function sends a command to set save energy mode: LRWANTM Class A / 
 * LREMB receive after transmit of the device.
 */
void nanolr_save_energy_rx_window ( nanolr_t *ctx );

/**
 * @brief Save energy tx only function
 *
 * @param ctx       Click object.
 *  
 * @description The function sends a command to set save energy mode: LREMB transmit only
 * of the device.
 */
void nanolr_save_energy_tx_only ( nanolr_t *ctx );

/**
 * @brief Get physical address function
 *
 * @param ctx       Click object.
 *  
 * @description The function retrieve the physical address of a module.
 */
void nanolr_get_physical_address ( nanolr_t *ctx );

/**
 * @brief Set physical address function
 *
 * @param ctx       Click object.
 * @param app_eui   Pointer to the memory location where app_eui data ( 8 bytes ) be stored
 * @param dev_eui   Pointer to the memory location where dev_eui data ( 8 bytes ) be stored
 *
 * @description The function set the physical address of a module.
 *
 * @note The physical address is used only when joining to a LRWAN network.
 */
void nanolr_set_physical_address ( nanolr_t *ctx, uint8_t *app_eui, uint8_t *dev_eui );

/**
 * @brief Get network address function
 *
 * @param ctx       Click object.
 *  
 * @description The function retrieve the addresses in use on the module.
 *
 * @note
 * <pre>
 * - LRWAN Network: To set the network addresses, the payload is a 4
 * bytes field (sent most significant byte first)
 * indicating the network identifier to be used.
 * When using Over-the-air activation, this param is set during network start.
 * - LREMB Network: When using the LREMB protocol,
 * the network address is 2 Byte long.
 * </pre>
 */
void nanolr_get_network_address ( nanolr_t *ctx );

/**
 * @brief Set network address function
 *
 * @param ctx       Click object. 
 * @param ntw_addr  16-bit network address
 *
 * @description The function set the network addresses.
 *
 * @note 
 * The address 0xFFFF indicates the broadcast address.
 * Addresses form 0xFFF0 to 0xFFFE are reserved.
 */
void nanolr_set_network_address ( nanolr_t *ctx, uint16_t ntw_addr );

/**
 * @brief Get network identifiers function
 *
 * @param ctx       Click object.
 * 
 * @description The function retrieve the network ID in use on the module.
 *
 * @note
 * <pre> 
 * - LRWAN Network: the EBI �network identifier� is 4 bytes long
 * and corresponds to the �Network ID� identifier.
 * - LREMB Network: In Embit custom radio networks,
 * the Network ID correspond to the �PAN ID� and
 * identifies the specific network in use.
 * </pre> 
 */
void nanolr_get_network_id ( nanolr_t *ctx );

/**
 * @brief Set network identifiers function
 *
 * @param ctx       Click object. 
 * @param ntw_id    16-bit network ID
 *
 * @description The function set the network ID in use on the module.
 */
void nanolr_set_network_id ( nanolr_t *ctx, uint16_t ntw_id );

/**
 * @brief Get network role function
 *
 * @param ctx       Click object.
 * 
 * @description The function retrieve the selected network role of the module.
 */
void nanolr_get_network_role ( nanolr_t *ctx );

/**
 * @brief Set network role function
 *
 * @param ctx       Click object. 
 * @param ntw_role
 * <pre>
 * - 0x00 ( NANOLR_NTW_ROLE_COORDINATOR ) : Coordinator.
 * - 0x02 ( NANOLR_NTW_ROLE_END_DEVICE )  : End Device.
 * </pre> 
 *
 * @description The function set the selected network role of the module.
 *
 * @note
 * Only the End Device role is supported on LRWAN networks.
 */
void nanolr_set_network_role ( nanolr_t *ctx, uint8_t ntw_role );

/**
 * @brief Get network automated settings function
 *
 * @param ctx       Click object. 
 * 
 * @description The function retrieve the automated settings of the module.
 */
void nanolr_get_network_auto_settings ( nanolr_t *ctx );

/**
 * @brief Get network preference function
 *
 * @param ctx       Click object. 
 * 
 * @description The function retrieve the active network preferences.
 */
void nanolr_get_network_preference ( nanolr_t *ctx );

/**
 * @brief Set network preference function
 *
 * @param ctx       Click object.  
 * @param prot
 * <pre>
 * - 0x00 ( NANOLR_NTW_PREFERENCE_PROTOCOL_LR_EMB ) :
 * LREMB network protocol.
 * - 0x80 ( NANOLR_NTW_PREFERENCE_PROTOCOL_LR_WAN ) :
 * LRWAN network protocol.
 * </pre>
 *
 * @param auto_join
 * <pre>
 * - 0x00 ( NANOLR_NTW_PREFERENCE_AUTO_JOIN_DISABLE ) :
 * Auto Joining Disabled (Activation By Personalization - ABP).
 * - 0x40 ( NANOLR_NTW_PREFERENCE_AUTO_JOIN_ENABLE )  :
 * Auto Joining Enabled (Over-The-Air Activation - OTAA).
 * </pre> 
 *
 * @param adr
 * <pre> 
 * - 0x00 ( NANOLR_NTW_PREFERENCE_ADAPTIVE_DATA_RATE_DISABLE ) :
 * disable ADR (Adaptive Data Rate)
 * - 0x20 ( NANOLR_NTW_PREFERENCE_ADAPTIVE_DATA_RATE_ENABLE )  :
 * enable ADR (Adaptive Data Rate).
 * </pre>
 *
 * @description The function set network preferences of the module.
 */
void nanolr_set_network_preference ( nanolr_t *ctx, uint8_t prot, uint8_t auto_join, uint8_t adr );

/**
 * @brief Get network join mode function
 *
 * @param ctx       Click object.  
 *
 * @description The function retrieve the network join mode of the module.
 */
void nanolr_get_network_join_mode ( nanolr_t *ctx );

/**
 * @brief Set network join mode function
 *
 * @param ctx               Click object.   
 * @param ntw_join_mode
 * <pre> 
 * - 0x00 ( NANOLR_NTW_JOIN_MODE_ABP )  : ABP (activation by personalisation).
 * - 0x01 ( NANOLR_NTW_JOIN_MODE_OTAA ) : OTAA (over-the-air-activation).
 * </pre>
 *
 * @description The function set network join mode of the module.
 */
void nanolr_set_network_join_mode ( nanolr_t *ctx, uint8_t ntw_join_mode );

/**
 * @brief Get battery level function
 *
 * @param ctx       Click object.  
 *
 * @description The function  the battery level of the module.
 */
void nanolr_get_battery_level  ( nanolr_t *ctx );

/**
 * @brief Get LRWAN network type function
 *
 * @param ctx       Click object.   
 *
 * @description The function retrieve the LRWAN network type of the module: public or private.
 */
void nanolr_get_wan_network_type ( nanolr_t *ctx );

/**
 * @brief Set LRWAN network type public function
 *
 * @param ctx       Click object.  
 * 
 * @description The function set the LRWAN network type of the module: public.
 */
void nanolr_wan_network_public ( nanolr_t *ctx );

/**
 * @brief Set LRWAN network type private function
 *
 * @param ctx       Click object.  
 * 
 * @description The function set the LRWAN network type of the module:
 * private.
 */
void nanolr_wan_network_private ( nanolr_t *ctx );

/**
 * @brief Network stop function
 *
 * @param ctx       Click object.  
 * 
 * @description The function send the commands to stops the network.
 */
void nanolr_network_stop ( nanolr_t *ctx );

/**
 * @brief Network start function
 *
 * @param ctx       Click object.  
 * 
 * @description The function send the commands to start the network.
 */
void nanolr_network_start ( nanolr_t *ctx );

/**
 * @brief Send data function
 *
 * @param ctx       Click object.   
 * @param tx_data    pointer to the memory location where tx_data be stored
 * @param length     number of bytes to send
 *
 * @description The function the send data command depends on the network protocol chosen.
 *
 * @note 
 * <pre> 
 * Send data LREMB broadcast:
 * send options: 0x0000;
 * destination address (broadcast): 0xFFFF;
 * any EMB-EVB boards is configured with reception always enabled,
 * so it is able to receive both direct messages and broadcast messages.
 * The end device usually employs
 * energy save mode (will be implemented in the future).
 * </pre>
 */
void nanolr_send_data ( nanolr_t *ctx, uint8_t *tx_data, uint8_t length );

/**
 * @brief Check response ready function
 *
 * @param ctx       Click object.  
 * 
 * @returns 0 : the response is not ready,  1 : the response is ready
 *
 * @description The function check if the response is ready.
 */
uint8_t nanolr_rsp_rdy ( nanolr_t *ctx );

/**
 * @brief UART ISR function
 *
 * @param ctx       Click object.  
 * 
 * @description The function read response bytes from the device 
 *              and sets flag after each received byte.
 */
void nanolr_uart_isr ( nanolr_t *ctx );

/**
 * @brief Response parser function
 *
 * @param ctx       Click object.  
 * 
 * @returns 0 : error status ok,  1 : error crc
 *
 * @description The function parser device response.
 */
nanolr_err_t nanolr_parser_rsp ( nanolr_t *ctx, nanolr_rsp_t *response );

#ifdef __cplusplus
}
#endif
#endif  // _NANOLR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
