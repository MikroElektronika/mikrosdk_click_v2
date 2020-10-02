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
 * \brief This file contains API for Nano LoRa Click driver.
 *
 * \addtogroup nanolora Nano LoRa Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NANOLORA_H
#define NANOLORA_H

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
#define NANOLORA_MAP_MIKROBUS( cfg, mikrobus ) \
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
#define NANOLORA_RETVAL       uint8_t

#define NANOLORA_OK           0x00
#define NANOLORA_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup list_of_commands List of commands
 * \{
 */
#define NANOLORA_CMD_DEV_INFO                                   0x01
#define NANOLORA_CMD_DEV_STATE                                  0x04
#define NANOLORA_CMD_RESET                                      0x05
#define NANOLORA_CMD_FW_VER                                     0x06
#define NANOLORA_CMD_RESTORE_DEF_SETTINGS                       0x07
#define NANOLORA_CMD_SAVE_SETTINGS                              0x08
#define NANOLORA_CMD_SERIAL_PORT_CFG                            0x09
#define NANOLORA_CMD_OUTPUT_POWER                               0x10
#define NANOLORA_CMD_OP_CHAN                                    0x11
#define NANOLORA_CMD_ENERGY_SAVE                                0x13
#define NANOLORA_CMD_PHYSICAL_ADR                               0x20
#define NANOLORA_CMD_NETWORK_ADR                                0x21
#define NANOLORA_CMD_NETWORK_ID                                 0x22
#define NANOLORA_CMD_NETWORK_ROLE                               0x23
#define NANOLORA_CMD_NETWORK_AUTO_SETTINGS                      0x24
#define NANOLORA_CMD_NETWORK_PREF                               0x25
#define NANOLORA_CMD_NETWORK_SECURITY                           0x26
#define NANOLORA_CMD_NETWORK_JOIN_MODE                          0x27
#define NANOLORA_CMD_NETWORK_STOP                               0x30
#define NANOLORA_CMD_NETWORK_START                              0x31
#define NANOLORA_CMD_SEND_DATA                                  0x50
#define NANOLORA_CMD_RECEIVED_DATA                              0x60
#define NANOLORA_CMD_ENTER_BOOTLOADER                           0x70
/** \} */

/**
 * \defgroup bootloading_phase Available only during bootloading phase!
 * \{
 */
#define NANOLORA_SET_BOOTLOADER_OPTIONS                         0x71
#define NANOLORA_ERASE_MEM                                      0x78
#define NANOLORA_WRITE_MEM_CHUNK                                0x7A
#define NANOLORA_READ_MEM_CHUNK                                 0x7B
#define NANOLORA_COMMIT_FW                                      0x7F
/** \} */

/**
 * \defgroup execution_status_byte Execution status byte
 * \{
 */
#define NANOLORA_SUCCESS                                        0x00
#define NANOLORA_GENERIC_ERROR                                  0x01
#define NANOLORA_PARAM_NOT_ACCEPTED                             0x02
#define NANOLORA_OPERATION_TIMEOUT                              0x03
#define NANOLORA_NO_MEMORY                                      0x04
#define NANOLORA_UNSUPPORTED                                    0x05
#define NANOLORA_BUSY                                           0x06
/** \} */

/**
 * \defgroup list_of_responses List of responses
 * \{
 */
#define NANOLORA_DEV_INFO_RESP                                  0x81
#define NANOLORA_DEV_STATE_RESP                                 0x84
#define NANOLORA_RESET_RESP                                     0x85
#define NANOLORA_FW_VER_RESP                                    0x86
#define NANOLORA_RESTORE_DEF_SETTINGS_RESP                      0x87
#define NANOLORA_SAVE_SETTINGS_RESP                             0x88
#define NANOLORA_SERIAL_PORT_CFG_RESP                           0x89
#define NANOLORA_OUTPUT_POWER_RESP                              0x90
#define NANOLORA_OP_CHAN_RESP                                   0x91
#define NANOLORA_ENERGY_SAVE_RESP                               0x93
#define NANOLORA_PHYSICAL_ADR_RESP                              0xA0
#define NANOLORA_NETWORK_ADR_RESP                               0xA1
#define NANOLORA_NETWORK_ID_RESP                                0xA2
#define NANOLORA_NETWORK_ROLE_RESP                              0xA3
#define NANOLORA_NETWORK_AUTO_SETTINGS_RESP                     0xA4
#define NANOLORA_NETWORK_PREF_RESP                              0xA5
#define NANOLORA_NETWORK_SECURITY_RESP                          0xA6
/** \} */

/**
 * \defgroup baud_rate Baud rate
 * \{
 */
#define NANOLORA_BAUD_RATE_MAINTAIN_SPEED                       0x00
#define NANOLORA_BAUD_RATE_1200                                 0x01
#define NANOLORA_BAUD_RATE_2400                                 0x02
#define NANOLORA_BAUD_RATE_4800                                 0x03
#define NANOLORA_BAUD_RATE_9600                                 0x04
#define NANOLORA_BAUD_RATE_19200                                0x05
#define NANOLORA_BAUD_RATE_38400                                0x06
#define NANOLORA_BAUD_RATE_57600                                0x07
#define NANOLORA_BAUD_RATE_115200                               0x08
/** \} */

/**
 * \defgroup model_id Model ID
 * \{
 */
#define NANOLORA_DEVICE_ID_UNKNOWN                              0x00
#define NANOLORA_DEVICE_ID_EMB_ZRF2XX                           0x20
#define NANOLORA_DEVICE_ID_EMB_ZRF231XX                         0x24
#define NANOLORA_DEVICE_ID_EMB_ZRF231PA                         0x26
#define NANOLORA_DEVICE_ID_EMB_ZRF212XX                         0x28
#define NANOLORA_DEVICE_ID_EMB_ZRF212B                          0x29
#define NANOLORA_DEVICE_ID_EMB_Z253X                            0x30
#define NANOLORA_DEVICE_ID_EMB_Z2530X                           0x34
#define NANOLORA_DEVICE_ID_EMB_Z2530PA                          0x36
#define NANOLORA_DEVICE_ID_EMB_Z2531X                           0x38
#define NANOLORA_DEVICE_ID_EMB_Z2531PA_USB                      0x3A
#define NANOLORA_DEVICE_ID_EMB_Z2538X                           0x3C
#define NANOLORA_DEVICE_ID_EMB_Z2538PA                          0x3D
#define NANOLORA_DEVICE_ID_EMB_WMBX                             0x40
#define NANOLORA_DEVICE_ID_EMB_WMB169X                          0x44
#define NANOLORA_DEVICE_ID_EMB_WMB169T                          0x45
#define NANOLORA_DEVICE_ID_EMB_WMB169PA                         0x46
#define NANOLORA_DEVICE_ID_EMB_WMB868X                          0x48
#define NANOLORA_DEVICE_ID_EMB_WMB868                           0x49
#define NANOLORA_DEVICE_ID_EMB_LRX                              0x50
#define NANOLORA_DEVICE_ID_EMB_LR1272                           0x54
/** \} */

/**
 * \defgroup network_role Network role
 * \{
 */
#define NANOLORA_NETWORK_ROLE_COORDINATOR                       0x00
#define NANOLORA_NETWORK_ROLE_RESERVED                          0x01
#define NANOLORA_NETWORK_ROLE_END_DEV                           0x02
/** \} */

/**
 * \defgroup single_byte_ind_device_state   Single byte indicating the device's state
 * \{
 */
#define NANOLORA_DEV_STATE_BOOTING                              0x00
#define NANOLORA_DEV_STATE_INSIDE_BOOTLOADER                    0x01
#define NANOLORA_DEV_STATE_RDY_STARTUP_OP_SUCC                  0x10
#define NANOLORA_DEV_STATE_RDY_STARTUP_OP_FAILED                0x11
#define NANOLORA_DEV_STATE_OFFLINE                              0x20
#define NANOLORA_DEV_STATE_CONNECTING                           0x21
#define NANOLORA_DEV_STATE_TRANSPARENT_MODE_STARTUP             0x22
#define NANOLORA_DEV_STATE_ONLINE                               0x30
#define NANOLORA_DEV_STATE_DISCONNECTING                        0x40
#define NANOLORA_DEV_STATE_RESERVED                             0x50
#define NANOLORA_DEV_STATE_END_RECEIVING_WINDOW                 0x51
/** \} */

/**
 * \defgroup energy_save_mode Energy save mode
 * \{
 */
#define NANOLORA_ENERGY_SAVE_MODE_ALWAYS_ON                     0x00
#define NANOLORA_ENERGY_SAVE_MODE_RX_WINDOW                     0x01
#define NANOLORA_ENERGY_SAVE_MODE_TX_ONLY                       0x02
/** \} */

/**
 * \defgroup operating_channel Operating channel
 * \{
 */
#define NANOLORA_OP_CHANNEL_CH_1_868_1MHz                       0x01
#define NANOLORA_OP_CHANNEL_CH_2_868_3MHz                       0x02
#define NANOLORA_OP_CHANNEL_CH_3_868_5MHz                       0x03
#define NANOLORA_OP_CHANNEL_CH_4_869_525MHz                     0x04
#define NANOLORA_OP_CHANNEL_SPR_FCT_128                         0x07
#define NANOLORA_OP_CHANNEL_SPR_FCT_256                         0x08
#define NANOLORA_OP_CHANNEL_SPR_FCT_512                         0x09
#define NANOLORA_OP_CHANNEL_SPR_FCT_1024                        0x0A
#define NANOLORA_OP_CHANNEL_SPR_FCT_2048                        0x0B
#define NANOLORA_OP_CHANNEL_SPR_FCT_4096                        0x0C
#define NANOLORA_OP_CHANNEL_BANDWIDTH_125KHz                    0x00
#define NANOLORA_OP_CHANNEL_BANDWIDTH_250KHz                    0x01
#define NANOLORA_OP_CHANNEL_CODING_RATE_4_5                     0x01
#define NANOLORA_OP_CHANNEL_CODING_RATE_4_6                     0x02
#define NANOLORA_OP_CHANNEL_CODING_RATE_4_7                     0x03
#define NANOLORA_OP_CHANNEL_CODING_RATE_4_8                     0x04
/** \} */

/**
 * \defgroup Network role Network role
 * \{
 */
#define NANOLORA_NTW_ROLE_COORDINATOR                           0x00
#define NANOLORA_NTW_ROLE_END_DEVICE                            0x02
/** \} */

/**
 * \defgroup network_preference Network preference
 * \{
 */
#define NANOLORA_NTW_PREFERENCE_PROTOCOL_LORA_EMB               0x00
#define NANOLORA_NTW_PREFERENCE_PROTOCOL_LORA_WAN               0x80
#define NANOLORA_NTW_PREFERENCE_AUTO_JOIN_DISABLE               0x00
#define NANOLORA_NTW_PREFERENCE_AUTO_JOIN_ENABLE                0x40
#define NANOLORA_NTW_PREFERENCE_ADAPTIVE_DATA_RATE_DISABLE      0x00
#define NANOLORA_NTW_PREFERENCE_ADAPTIVE_DATA_RATE_ENABLE       0x20
/** \} */

/**
 * \defgroup network_join_mode Network join mode
 * \{
 */
#define NANOLORA_NTW_JOIN_MODE_ABP                              0x00
#define NANOLORA_NTW_JOIN_MODE_OTAA                             0x01

#define NANOLORA_RSP_READY                                      0x01
#define NANOLORA_RSP_NOT_READY                                  0x00

#define NANOLORA_ERR_CRC                                        0x01
#define NANOLORA_ERR_STATUS_OK                                  0x00
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
 * @macro nanolora_err_t
 * @brief Driver Error type
 */
#define nanolora_err_t  uint8_t

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

} nanolora_t;

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

    uint16_t rsp_len_cfg;

} nanolora_cfg_t;

/**
 * @brief Click response structure definition.
 */
typedef struct
{
    uint16_t length;
    uint8_t message_id;
    uint8_t payload[ 256 ];
    uint8_t crc;

} nanolora_rsp_t;

/**
 * @brief Click network structure definition.
 */
typedef struct
{
    uint8_t channel;
    uint8_t spreading_factor;
    uint8_t bandwidth;
    uint8_t coding_rate;

} nanolora_network_t;

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
void nanolora_cfg_setup ( nanolora_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NANOLORA_RETVAL nanolora_init ( nanolora_t *ctx, nanolora_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for NanoLora click.
 */
void nanolora_default_cfg ( nanolora_t *ctx );

/**
 * @brief Reset module.
 *
 * @param ctx Click object.
 *
 * @description The function resets the module.
 */
void nanolora_reset ( nanolora_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx       Click object.
 * @param data_buf  Data buffer for sends.
 * @param len       Number of bytes for sends.
 *
 * @description The function write specific number of data.
 */
void nanolora_generic_write ( nanolora_t *ctx, char *data_buf, uint16_t len );

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
uint16_t nanolora_generic_read ( nanolora_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Request to Send function
 *
 * @param ctx       Click object. 
 *
 * @returns 0 : inactive,  1 : active
 *
 * @description The function Request to Send indicate a desire to transmit.
 */
uint8_t nanolora_request_2_send ( nanolora_t *ctx );

/**
 * @brief Clear to Send function
 *
 * @param ctx       Click object.  
 * @param state     0 : inactive, 1 : active
 *
 * @description The function in response the DCE asserts CTS to grant permission.
 */
void nanolora_clear_2_send ( nanolora_t *ctx, uint8_t state );

/**
 * @brief Get GP1 pin state function
 *
 * @param ctx       Click object.   
 *
 * @returns 0 : inactive,  1 : active
 *
 * @description The function get states of the GP1 ( PWM ) pin that can handle interrupts.
 */
uint8_t nanolora_get_gp1_pin ( nanolora_t *ctx );

/**
 * @brief Set ST pin state function
 *
 * @param ctx       Click object.   
 * @param state     0 : inactive, 1 : active
 *
 * @description The function set states of the ST ( AN ) pin.
 */
void nanolora_set_st_pin ( nanolora_t *ctx, uint8_t state );

/**
 * @brief Get device information function
 *
 * @param ctx       Click object.
 * 
 * @description The function requires device information.
 */
void nanolora_get_device_info ( nanolora_t *ctx );

/**
 * @brief Get device state function
 *
 * @param ctx       Click object.
 * 
 * @description The function requires state information.
 */
void nanolora_get_device_state ( nanolora_t *ctx );

/**
 * @brief Software reset function
 *
 * @param ctx       Click object.
 * 
 * @description The function sends a command for the software reset on the device.
 */
void nanolora_sw_reset ( nanolora_t *ctx );

/**
 * @brief Get firmware version function
 *
 * @param ctx       Click object.
 * 
 * @description The function requires device firmware version.
 */
void nanolora_get_fw_ver ( nanolora_t *ctx );

/**
 * @brief Restore to factory function
 *
 * @param ctx       Click object.
 * 
 * @description The function sends a command to reset the device to factory settings.
 */
void nanolora_restore_2_factory ( nanolora_t *ctx );

/**
 * @brief Restore to factory function
 *
 * @param ctx       Click object.
 * 
 * @description The function sends a command to save the current settings.
 */
void nanolora_save_settings ( nanolora_t *ctx );

/**
 * @brief Get output power function
 *
 * @param ctx       Click object.
 * 
 * @description The function retrieve the current output power.
 */
void nanolora_get_output_power ( nanolora_t *ctx );

/**
 * @brief Get operating channel function
 *
 * @param ctx       Click object.
 * 
 * @description The function retrieve the current channel.
 */
void nanolora_get_operating_channel ( nanolora_t *ctx );

/**
 * @brief Set output power function
 *
 * @param ctx       Click object. 
 * @param out_pwr   Output power [+2, +19] dBm
 *
 * @description The function retrieve the current output power.
 */
void nanolora_set_output_power ( nanolora_t *ctx, uint8_t out_pwr );

/**
 * @brief Set operating channel function
 *
 * @param ctx       Click object. 
 * @param channel
 * <pre>
 * - 0x01 ( NANOLORA_OP_CHANNEL_CH_1_868_1MHz )    : 868.100 MHz;
 * - 0x02 ( NANOLORA_OP_CHANNEL_CH_2_868_3MHz )    : 868.300 MHz;
 * - 0x03 ( NANOLORA_OP_CHANNEL_CH_3_868_5MHz )    : 868.500 MHz;
 * - 0x04 ( NANOLORA_OP_CHANNEL_CH_4_869_525MHz )  : 869.525 MHz;
 * </pre> 
 *
 * @param spreading_factor
 * <pre> 
 * - 0x07 ( NANOLORA_OP_CHANNEL_SPR_FCT_128 )      : Chips/symbol 128;
 * - 0x08 ( NANOLORA_OP_CHANNEL_SPR_FCT_256 )      : Chips/symbol 256;
 * - 0x09 ( NANOLORA_OP_CHANNEL_SPR_FCT_512 )      : Chips/symbol 512;
 * - 0x0A ( NANOLORA_OP_CHANNEL_SPR_FCT_1024 )     : Chips/symbol 1024;
 * - 0x0B ( NANOLORA_OP_CHANNEL_SPR_FCT_2048 )     : Chips/symbol 2048;
 * - 0x0C ( NANOLORA_OP_CHANNEL_SPR_FCT_4096 )     : Chips/symbol 4096;
  * <pre>
 *
 * @param bandwidth
 * <pre>
 * - 0x00 ( NANOLORA_OP_CHANNEL_BANDWIDTH_125KHZ ) : 125 kHz;
 * - 0x01 ( NANOLORA_OP_CHANNEL_BANDWIDTH_250KHZ ) : 250 kHz;
 * </pre>
 *
 * @param coding_rate
 * <pre> 
 * - 0x00 ( NANOLORA_OP_CHANNEL_CODING_RATE_4_5 )  : Coding Rate 4/5;
 * - 0x01 ( NANOLORA_OP_CHANNEL_CODING_RATE_4_6 )  : Coding Rate 4/6;
 * - 0x02 ( NANOLORA_OP_CHANNEL_CODING_RATE_4_7 )  : Coding Rate 4/7;
 * - 0x03 ( NANOLORA_OP_CHANNEL_CODING_RATE_4_8 )  : Coding Rate 4/8;
 * </pre> 
 *
 * @description The function set the current channel.
 *
 * @note The operating channel can only be changed when network is down. When using the LoRaWAN 
 * network, the channel is automatically assigned by the concentrator.
 */
void nanolora_set_operating_channel ( nanolora_t *ctx, nanolora_network_t *net );

/**
 * @brief Save energy on function
 *
 * @param ctx       Click object.
 * 
 * @description The function sends a command
 * to set save energy mode: LoRaWANTM Class C / LoRaEMB reception anytime
 * of the device.
 */
void nanolora_save_energy_always_on ( nanolora_t *ctx );

/**
 * @brief Save energy rx window function
 *
 * @param ctx       Click object.
 *  
 * @description The function sends a command to set save energy mode: LoRaWANTM Class A / 
 * LoRaEMB receive after transmit of the device.
 */
void nanolora_save_energy_rx_window ( nanolora_t *ctx );

/**
 * @brief Save energy tx only function
 *
 * @param ctx       Click object.
 *  
 * @description The function sends a command to set save energy mode: LoRaEMB transmit only
 * of the device.
 */
void nanolora_save_energy_tx_only ( nanolora_t *ctx );

/**
 * @brief Get physical address function
 *
 * @param ctx       Click object.
 *  
 * @description The function retrieve the physical address of a module.
 */
void nanolora_get_physical_address ( nanolora_t *ctx );

/**
 * @brief Set physical address function
 *
 * @param ctx       Click object.
 * @param app_eui   Pointer to the memory location where app_eui data ( 8 bytes ) be stored
 * @param dev_eui   Pointer to the memory location where dev_eui data ( 8 bytes ) be stored
 *
 * @description The function set the physical address of a module.
 *
 * @note The physical address is used only when joining to a LoRaWAN network.
 */
void nanolora_set_physical_address ( nanolora_t *ctx, uint8_t *app_eui, uint8_t *dev_eui );

/**
 * @brief Get network address function
 *
 * @param ctx       Click object.
 *  
 * @description The function retrieve the addresses in use on the module.
 *
 * @note
 * <pre>
 * - LoRaWAN Network: To set the network addresses, the payload is a 4
 * bytes field (sent most significant byte first)
 * indicating the network identifier to be used.
 * When using Over-the-air activation, this param is set during network start.
 * - LoRaEMB Network: When using the LoRaEMB protocol,
 * the network address is 2 Byte long.
 * </pre>
 */
void nanolora_get_network_address ( nanolora_t *ctx );

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
void nanolora_set_network_address ( nanolora_t *ctx, uint16_t ntw_addr );

/**
 * @brief Get network identifiers function
 *
 * @param ctx       Click object.
 * 
 * @description The function retrieve the network ID in use on the module.
 *
 * @note
 * <pre> 
 * - LoRaWAN Network: the EBI �network identifier� is 4 bytes long
 * and corresponds to the �Network ID� identifier.
 * - LoRaEMB Network: In Embit custom radio networks,
 * the Network ID correspond to the �PAN ID� and
 * identifies the specific network in use.
 * </pre> 
 */
void nanolora_get_network_id ( nanolora_t *ctx );

/**
 * @brief Set network identifiers function
 *
 * @param ctx       Click object. 
 * @param ntw_id    16-bit network ID
 *
 * @description The function set the network ID in use on the module.
 */
void nanolora_set_network_id ( nanolora_t *ctx, uint16_t ntw_id );

/**
 * @brief Get network role function
 *
 * @param ctx       Click object.
 * 
 * @description The function retrieve the selected network role of the module.
 */
void nanolora_get_network_role ( nanolora_t *ctx );

/**
 * @brief Set network role function
 *
 * @param ctx       Click object. 
 * @param ntw_role
 * <pre>
 * - 0x00 ( NANOLORA_NTW_ROLE_COORDINATOR ) : Coordinator.
 * - 0x02 ( NANOLORA_NTW_ROLE_END_DEVICE )  : End Device.
 * </pre> 
 *
 * @description The function set the selected network role of the module.
 *
 * @note
 * Only the End Device role is supported on LoRaWAN networks.
 */
void nanolora_set_network_role ( nanolora_t *ctx, uint8_t ntw_role );

/**
 * @brief Get network automated settings function
 *
 * @param ctx       Click object. 
 * 
 * @description The function retrieve the automated settings of the module.
 */
void nanolora_get_network_auto_settings ( nanolora_t *ctx );

/**
 * @brief Get network preference function
 *
 * @param ctx       Click object. 
 * 
 * @description The function retrieve the active network preferences.
 */
void nanolora_get_network_preference ( nanolora_t *ctx );

/**
 * @brief Set network preference function
 *
 * @param ctx       Click object.  
 * @param prot
 * <pre>
 * - 0x00 ( NANOLORA_NTW_PREFERENCE_PROTOCOL_LORA_EMB ) :
 * LoRaEMB network protocol.
 * - 0x80 ( NANOLORA_NTW_PREFERENCE_PROTOCOL_LORA_WAN ) :
 * LoRaWAN network protocol.
 * </pre>
 *
 * @param auto_join
 * <pre>
 * - 0x00 ( NANOLORA_NTW_PREFERENCE_AUTO_JOIN_DISABLE ) :
 * Auto Joining Disabled (Activation By Personalization - ABP).
 * - 0x40 ( NANOLORA_NTW_PREFERENCE_AUTO_JOIN_ENABLE )  :
 * Auto Joining Enabled (Over-The-Air Activation - OTAA).
 * </pre> 
 *
 * @param adr
 * <pre> 
 * - 0x00 ( NANOLORA_NTW_PREFERENCE_ADAPTIVE_DATA_RATE_DISABLE ) :
 * disable ADR (Adaptive Data Rate)
 * - 0x20 ( NANOLORA_NTW_PREFERENCE_ADAPTIVE_DATA_RATE_ENABLE )  :
 * enable ADR (Adaptive Data Rate).
 * </pre>
 *
 * @description The function set network preferences of the module.
 */
void nanolora_set_network_preference ( nanolora_t *ctx, uint8_t prot, uint8_t auto_join, uint8_t adr );

/**
 * @brief Get network join mode function
 *
 * @param ctx       Click object.  
 *
 * @description The function retrieve the network join mode of the module.
 */
void nanolora_get_network_join_mode ( nanolora_t *ctx );

/**
 * @brief Set network join mode function
 *
 * @param ctx               Click object.   
 * @param ntw_join_mode
 * <pre> 
 * - 0x00 ( NANOLORA_NTW_JOIN_MODE_ABP )  : ABP (activation by personalisation).
 * - 0x01 ( NANOLORA_NTW_JOIN_MODE_OTAA ) : OTAA (over-the-air-activation).
 * </pre>
 *
 * @description The function set network join mode of the module.
 */
void nanolora_set_network_join_mode ( nanolora_t *ctx, uint8_t ntw_join_mode );

/**
 * @brief Get battery level function
 *
 * @param ctx       Click object.  
 *
 * @description The function  the battery level of the module.
 */
void nanolora_get_battery_level  ( nanolora_t *ctx );

/**
 * @brief Get LoRaWAN network type function
 *
 * @param ctx       Click object.   
 *
 * @description The function retrieve the LoRaWAN network type of the module: public or private.
 */
void nanolora_get_wan_network_type ( nanolora_t *ctx );

/**
 * @brief Set LoRaWAN network type public function
 *
 * @param ctx       Click object.  
 * 
 * @description The function set the LoRaWAN network type of the module: public.
 */
void nanolora_wan_network_public ( nanolora_t *ctx );

/**
 * @brief Set LoRaWAN network type private function
 *
 * @param ctx       Click object.  
 * 
 * @description The function set the LoRaWAN network type of the module:
 * private.
 */
void nanolora_wan_network_private ( nanolora_t *ctx );

/**
 * @brief Network stop function
 *
 * @param ctx       Click object.  
 * 
 * @description The function send the commands to stops the network.
 */
void nanolora_network_stop ( nanolora_t *ctx );

/**
 * @brief Network start function
 *
 * @param ctx       Click object.  
 * 
 * @description The function send the commands to start the network.
 */
void nanolora_network_start ( nanolora_t *ctx );

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
 * Send data LoRaEMB broadcast:
 * send options: 0x0000;
 * destination address (broadcast): 0xFFFF;
 * any EMB-EVB boards is configured with reception always enabled,
 * so it is able to receive both direct messages and broadcast messages.
 * The end device usually employs
 * energy save mode (will be implemented in the future).
 * </pre>
 */
void nanolora_send_data ( nanolora_t *ctx, uint8_t *tx_data, uint8_t length );

/**
 * @brief Check response ready function
 *
 * @param ctx       Click object.  
 * 
 * @returns 0 : the response is not ready,  1 : the response is ready
 *
 * @description The function check if the response is ready.
 */
uint8_t nanolora_rsp_rdy ( nanolora_t *ctx );

/**
 * @brief UART ISR function
 *
 * @param ctx       Click object.  
 * 
 * @description The function read response bytes from the device 
 *              and sets flag after each received byte.
 */
void nanolora_uart_isr ( nanolora_t *ctx, uint8_t reader_hdlr );

/**
 * @brief Response parser function
 *
 * @param ctx       Click object.  
 * 
 * @returns 0 : error status ok,  1 : error crc
 *
 * @description The function parser device response.
 */
nanolora_err_t nanolora_parser_rsp ( nanolora_t *ctx, nanolora_rsp_t *response );

#ifdef __cplusplus
}
#endif
#endif  // _NANOLORA_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
