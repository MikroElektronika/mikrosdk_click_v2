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
 * \brief This file contains API for BT Audio Click driver.
 *
 * \addtogroup btaudio BT Audio Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BTAUDIO_H
#define BTAUDIO_H

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
#define BTAUDIO_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.pwr    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.cmd    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.frs    = MIKROBUS( mikrobus, MIKROBUS_INT ); \
  cfg.baud   = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BTAUDIO_RETVAL  uint8_t

#define BTAUDIO_OK           0x00
#define BTAUDIO_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 600
#define DRV_TX_BUFFER_SIZE 100
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define BTAUDIO_ERR                    0x00
#define BTAUDIO_STATUS_FALSE           0x00
#define BTAUDIO_STATUS_TRUE            0x01
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t pwr;
    digital_out_t cmd;
    digital_out_t baud;
    digital_out_t frs;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];
} btaudio_t;

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
    pin_name_t pwr;
    pin_name_t cmd;
    pin_name_t frs;
    pin_name_t baud;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} btaudio_cfg_t;

typedef enum
{
    ANALOG_OUTPUT   = 0,
    I2S_OUPUT       = 1,
    S_PDIF_OUPUT    = 2,
    INTERCOM_DAC    = 3
    
} a2dp_routing_values_t;

typedef enum
{
    RES_24 = 0,
    RES_32 = 1

} bit_res_t;

typedef enum
{
    RATE_8K   = 0,
    RATE_32K  = 1,
    RATE_44K1 = 2,
    RATE_48K  = 3

} sample_rate_t;

typedef enum
{
    IAP_MODE    = 0,
    SPP_MODE    = 1,
    A2DP_MODE   = 2,
    HFP_MODE    = 3

} profile_bitmask_values;

typedef enum
{
    AVRCP_EK             = 0,
    RECONNECT_PWR_ON     = 1,
    DISCOVERABLE         = 2,
    AAC_APTX             = 3,
    REBOOT_DIS           = 4,
    MUTE_VOLUME          = 5,
    ENABLE_PIO4          = 6,
    DISABLE_SYS_TONES    = 7,
    PWR_OFF_P_TIMEOUT    = 8,
    RESET_PWR_OFF        = 9,
    RECONNECT_PANIC      = 10,
    ENABLE_INDICATOR     = 11,
    ENABLE_TRACK_CHANGE  = 12,
    ENABLE_PLAYBACK_TONE = 13,
    AUTO_ACCEPT          = 14
    
} extended_features_bitmask_values;

/**
 * @brief Error type 
 */
typedef uint8_t btaudio_error_t;

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
void btaudio_cfg_setup ( btaudio_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param btaudio Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BTAUDIO_RETVAL btaudio_init ( btaudio_t *ctx, btaudio_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param btaudio Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void btaudio_generic_write ( btaudio_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx      Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len  The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
int32_t btaudio_generic_read ( btaudio_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Power On function
 *
 * @param ctx      Click object.
 * 
 * @description The function Power On, enable RN52 Bluetooth audio module 
 * on BT Audio Click board by setting to '1' state of PWR pin.
 */
void btaudio_set_power_on ( btaudio_t *ctx );

/**
 * @brief Power Off function
 *
 * @param ctx      Click object.
 * 
 * @description The function Power Off, disable RN52 Bluetooth audio module
 * on BT Audio Click board by clearing to '0' state of PWR pin .
 */
void btaudio_set_power_off ( btaudio_t *ctx );

/**
 * @brief Reset function
 *
 * @param ctx      Click object.
 * 
 * @description The function resets the device by toggling the reset pin.
 */

void btaudio_reset ( btaudio_t *ctx );

/**
 * @brief Write Single byte function
 *
 * @param ctx      Click object.
 * @param input    Byte to be written.
 * 
 * @description The function writes a single byte via uart.
 */
void btaudio_write_byte ( btaudio_t *ctx, uint8_t input );

/**
 * @brief Write command function
 *
 * @param ctx      Click object.
 * @param data_buf Byte to be written.
 * 
 * @description The function writes command.
 */
void btaudio_write_command ( btaudio_t *ctx, char *data_buf );

/**
 * @brief Set mode function
 *
 * @param ctx      Click object.
 * @param mode          
 * - 0 : Command mode;
 * - 1 : Data mode;
 *
 * @description The function set operating mode
 * of RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_set_mode ( btaudio_t *ctx, uint8_t mode );

/**
 * @brief Set command mode function
 *
 * @param ctx      Click object.
 * @param mode
 * - 0 : Command mode;
 * - 1 : Data mode;
 *
 * @description The function sets operating mode via command.
 */
void btaudio_set_cmd_mode ( btaudio_t *ctx, uint8_t mode );

/**
 * @brief Set factory defaults settings function
 *
 * @param ctx      Click object.
 *
 * @description The function sets factory default settings.
 */
void btaudio_set_factory_defaults ( btaudio_t *ctx );

/**
 * @brief Get all settings function
 *
 * @param ctx      Click object.
 *
 * @description The function gets all settings data of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_get_all_settings ( btaudio_t *ctx );

/**
 * @brief Set audio output function
 *
 * @param ctx      Click object.
 * @param setting
 * - ANALOG_OUTPUT : Analog output ( default );
 * - I2S_OUPUT     : Set the output for I2S;
 * - S_PDIF_OUPUT  : Set the output for S/PDIF;
 * - INTERCOM_DAC  : Intercom DAC mode;
 *
 * @param bit_res
 * - RES_24 : 24 Bits Per Sample;
 * - RES_32 : 32 Bits Per Sample;
 *
 * @param sample_rate
 * - RATE_8K   : 0-8K Samples Per Second;
 * - RATE_32K  : 1-32K Samples Per Second;
 * - RATE_44K1 : 2-44K1 Samples Per Second;
 * - RATE_48K  : 3-48K Samples Per Second;
 *
 * @description The function sets audio output of
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_set_audio_output( btaudio_t *ctx, a2dp_routing_values_t setting, 
                                               bit_res_t bit_res, 
                                               sample_rate_t sample_rate );

/**
 * @brief Set device name function
 *
 * @param ctx      Click object.
 * @param name     pointer to the memory location where the name is stored.
 *
 * @retval status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description The function sets the device name.
 * Is a prefix of up to 20 alphanumeric characters.
 * The device name is set to string-XXXX, where XXXX
 * is the last four digits of the module's MAC address of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
uint8_t btaudio_set_device_name ( btaudio_t *ctx, uint8_t *name );

/**
 * @brief Set automatic shutdown function
 *
 * @param ctx      Click object.
 * @param seconds  time in seconds.
 *
 * @retval status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description The function sets automatic shutdown
 * on idle time in seconds by send command to the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
uint8_t btaudio_set_automatic_shutdown ( btaudio_t *ctx, uint16_t seconds );

/**
 * @brief Set extended features function
 *
 * @param ctx      Click object.
 * @param ext_features
 * - AVRCP_EK             : Enable AVRCP buttons for EK;
 * - RECONNECT_PWR_ON     : Enable reconnect on power-on;
 * - DISCOVERABLE         : Discoverable on start up;
 * - AAC_APTX             : Codec indicators PIO7 (AAC) and PIO6 (aptX);
 * - REBOOT_DIS           : Reboot after disconnect;
 * - MUTE_VOLUME          : Mute volume up/down tones;
 * - ENABLE_PIO4          : Enable voice command button on PIO4;
 * - DISABLE_SYS_TONES    : Disable system tones;
 * - PWR_OFF_P_TIMEOUT    : Power off after pairing timeout;
 * - RESET_PWR_OFF        : Reset after power off;
 * - RECONNECT_PANIC      : Enable list reconnect after panic;
 * - ENABLE_INDICATOR     : Enable latch event indicator PIO2;
 * - ENABLE_TRACK_CHANGE  : Enable track change event;
 * - ENABLE_PLAYBACK_TONE : Enable tones playback at fixed volume;
 * - AUTO_ACCEPT          : Enable auto-accept passkey in Keyboard I/O Authentication mode;
 *
 * @description The function sets the extended features of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_set_extended_features ( btaudio_t *ctx, extended_features_bitmask_values ext_features );

/**
 * @brief Set authentication function
 *
 * @param ctx      Click object.
 * @param ext_features
 * - 0 : Open. Authentication is not required. The device accepts pin code mode;
 * - 1 : SSP Keyboard I/O mode is an association model of Secure Simple Pairing (SSP) (default);
 * - 2 : SSP 'just works' mode is an association model of SSP;
 * - 4 : Pin Code mode is part of legacy pairing;
 *
 * @description The function sets the authentication of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_set_authentication ( btaudio_t *ctx, uint8_t authentication );

/**
 * @brief Set service class of device function
 *
 * @param ctx       Click object.
 * @param sc_device string [ hex ] number, default '240704'.
 *
 * @retval status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description The function sets the service class of device to the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
uint8_t btaudio_set_service_class_device( btaudio_t *ctx, uint8_t *sc_device );

/**
 * @brief Set discovery mask enabled for discovery function
 *
 * @param ctx            Click object.
 * @param discovery_mask number of discovery mask
 *
 * @description The function sets the discovery mask enabled for discovery to the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_set_discovery_mask ( btaudio_t *ctx, uint8_t discovery_mask );

/**
 * @brief Set the security pin code function
 *
 * @param ctx          Click object.
 * @param security_pin pointer to the memory location where security pin be stored.
 *
 * @retval status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description The function sets the security pin code to the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
uint8_t btaudio_set_security_pin ( btaudio_t *ctx, uint8_t *security_pin );

/**
 * @brief Set speaker gain levels function
 *
 * @param ctx              Click object.
 * @param speaker_gain_lvl Speaker Gain Levels value from 0 to 15.
 *
 * @description The function sets the speaker gain levels of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_set_speaker_gain_lvl ( btaudio_t *ctx, uint8_t speaker_gain_lvl );

/**
 * @brief Set tone gain levels function
 *
 * @param ctx              Click object.
 * @param speaker_gain_lvl Speaker Gain Levels value from 0 to 31.
 *
 * @description The function sets the tone gain levels of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_set_toneain_lvl ( btaudio_t *ctx, uint8_t tone_gain_lvl );

/**
 * @brief Get basic settings function
 *
 * @param ctx      Click object.
 * @param response pointer to the memory location where response be stored.
 *
 * @description The function get basic settings data of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_get_basic_settings ( btaudio_t *ctx );

/**
 * @brief Get register settings function
 *
 * @param ctx      Click object.
 * @param cmd      Second character of the command;
 * 
 * @decription The function get register settings
 * on idle time in seconds by send command to the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_get_reg_settings ( btaudio_t *ctx, char cmd );

/**
 * @brief Get battery status function
 *
 * @param ctx      Click object.
 *
 * @description The function get battery status data from the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_get_battery_status ( btaudio_t *ctx );

/**
 * @brief Get help status function
 *
 * @param ctx      Click object.
 *
 * @description The function get help status data from the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_get_help ( btaudio_t *ctx );

/**
 * @brief Get firmware version function
 *
 * @param ctx      Click object.
 *
 * @description The function getfirmware version data of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_get_firmware_version ( btaudio_t *ctx );

/**
 * @brief Toggle local echo function
 *
 * @param ctx      Click object.
 * 
 * @description The function toggles the local echo on and off to the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_toggle_local_echo ( btaudio_t *ctx );

/**
 * @brief Toggle discoverable function
 *
 * @param ctx      Click object.
 * @param discoverable
 * - 0 : not discoverable;
 * - 1 : discoverable;
 *
 * @retval status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description The function toggles whether the RN52 Bluetooth audio module
 * of the BT Audio Click board
 * is discoverable or not.
 */
uint8_t btaudio_toggle_discoverable ( btaudio_t *ctx, uint8_t discoverable );

/**
 * @brief Answer the keyboard function
 *
 * @param ctx      Click object.
 * @param answer
 * - 0, '0', 'N' or 'n' : reject pairing pass key;
 * - 1, '1', 'Y' or 'y' : accept pairing pass key;
 *
 * @retval status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description The function accepts/rejects pairing in keyboard IO authentication mode
 * of the RN52 Bluetooth audio module on BT Audio Click board.
 */
uint8_t btaudio_answer_keyboard ( btaudio_t *ctx, uint8_t answer );

/**
 * @brief DFU mode function
 *
 * @param ctx      Click object.
 * 
 * @description The function will put the RN52 Bluetooth audio module
 * on BT Audio Click board
 * into Device Firmware Upgrade (DFU) mode.
 */
void btaudio_dfu_mode ( btaudio_t *ctx );

/**
 * @brief Call phone number function
 *
 * @param ctx      Click object.
 * @param p_number pointer to the memory location where phone number be stored.
 *
 * @retval status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description The function call phone number from the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
uint8_t btaudio_call_phone_number ( btaudio_t *ctx, char *p_number );

/**
 * @brief Show track metadata function
 *
 * @param ctx      Click object.
 * @param track_data pointer to the memory location where track data be stored.
 *
 * @description The function show track metadata
 * which includes Track Title, Artist,
 * Album, Genre, Number, Total Count, Duration (ms) of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_show_track_metadata ( btaudio_t *ctx );

/**
 * @brief Dial last phone number function
 *
 * @param ctx      Click object.
 *
 * @description The function will redial last dialed number from the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_dial_last_phone_number ( btaudio_t *ctx );

/**
 * @brief Increase volume function
 *
 * @param ctx      Click object.
 * 
 * @description The function increase volume of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_increase_volume ( btaudio_t *ctx );

/**
 * @brief Decrease volume function
 *
 * @param ctx      Click object.
 * 
 * @description The function decrease volume of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_decrease_volume ( btaudio_t *ctx );

/**
 * @brief Play next track function
 *
 * @param ctx      Click object.
 * 
 * @description The function play next track of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_next_track ( btaudio_t *ctx );

/**
 * @brief Play previous track function
 *
 * @param ctx      Click object.
 * 
 * @description The function play previous track of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_previous_track ( btaudio_t *ctx );

/**
 * @brief Pause track function
 *
 * @param ctx      Click object.
 * 
 * @description The function pause track of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_pause_play_track ( btaudio_t *ctx );

/**
 * @brief Enable voice commands function
 *
 * @param ctx      Click object.
 * 
 * @description The function enable voice commands of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_enable_voice_commands ( btaudio_t *ctx );

/**
 * @brief Get GPIO DIRR function
 *
 * @param ctx      Click object.
 *
 * @description The function configures GPIO direction of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_get_gpio_dirr ( btaudio_t *ctx );

/**
 * @brief Get GPIO level function
 *
 * @param ctx      Click object.
 *
 * @description The function get GPIO level and input pull-up configuration of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_get_gpio_level ( btaudio_t *ctx );

/**
 * @brief Disconnect current connection function
 *
 * @param ctx      Click object.
 * @param profile
 * - 0 : iAP;
 * - 1 : SPP;
 * - 2 : A2DP;
 * - 3 : HFP;
 *
 * @description The function disconnect current connection profile of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_disconnect_current_connection ( btaudio_t *ctx, profile_bitmask_values profile );

/**
 * @brief Mute hold call function
 *
 * @param ctx      Click object.
 * @param mute
 * - 0 : mutes the call;
 * - 1 : call is unmuted;
 *
 * @retval status
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description The function mute hold call of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
uint8_t btaudio_mute_hold_call ( btaudio_t *ctx, uint8_t mute );

/**
 * @brief Reboot function
 *
 * @param ctx      Click object.
 *
 * @description The function reboot the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_reboot ( btaudio_t *ctx );

/**
 * @brief Display caller Id function
 *
 * @param ctx      Click object.
 *
 * @description The function display caller Id of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_display_caller_id ( btaudio_t *ctx );

/**
 * @brief Reset prev paired devices function
 *
 * @param ctx      Click object.
 *
 * @description The function reset prev paired devices of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_reset_prev_paired_devices ( btaudio_t *ctx );

/**
 * @brief Query connection status function
 *
 * @param ctx      Click object.
 * 
 * @description The function query connection status of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_query_connection_status ( btaudio_t *ctx );

/**
 * @brief Reconnect most recent function
 *
 * @param ctx      Click object.
 *
 * @description The function reconnect most recent of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_reconnect_most_recent ( btaudio_t *ctx );

/**
 * @brief Accept call function
 *
 * @param ctx      Click object.
 *
 * @description The function accept call of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_accept_call ( btaudio_t *ctx );

/**
 * @brief Reject call function
 *
 * @param ctx      Click object.
 * 
 * @description The function reject call of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_reject_call ( btaudio_t *ctx );

/**
 * @brief User busy function
 *
 * @param ctx      Click object.
 *
 * @description The function user busy of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_userBusy( btaudio_t *ctx );

/**
 * @brief Accept held call function
 *
 * @param ctx      Click object.
 *
 * @description The function accept held call of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_accept_held_call ( btaudio_t *ctx );

/**
 * @brief Set hold accept incoming function
 *
 * @param ctx      Click object.
 *
 * @description The function sets on hold accept incoming calls of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_set_hold_accept_incoming ( btaudio_t *ctx );

/**
 * @brief Add held call function
 *
 * @param ctx      Click object.
 * 
 * @description The function add held call of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_add_held_call ( btaudio_t *ctx );

/**
 * @brief Connect two calls function
 *
 * @param ctx      Click object.
 *
 * @description The function connect two calls of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_cnnct_two_calls ( btaudio_t *ctx );

/**
 * @brief Transfer active calls function
 *
 * @param ctx      Click object.
 *
 * @description The function transfer active calls of the
 * RN52 Bluetooth audio module on BT Audio Click board.
 */
void btaudio_transfer_active_calls ( btaudio_t *ctx );

/**
 * @brief Get interrupt state function
 *
 * @param ctx      Click object.
 * 
 * @return interrupt state
 * - 0 : not active
 * - 1 : active
 *
 * @description The function gets interrupt state
 * by return status of INT pin of BT Audio Click board.
 */
uint8_t btaudio_interrupt ( btaudio_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BTAUDIO_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
