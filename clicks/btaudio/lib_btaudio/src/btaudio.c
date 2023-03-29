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
 */

#include "btaudio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"
#include "conversions.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void btaudio_cfg_setup ( btaudio_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->pwr = HAL_PIN_NC;
    cfg->cmd = HAL_PIN_NC;
    cfg->frs = HAL_PIN_NC;
    cfg->baud = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

BTAUDIO_RETVAL btaudio_init ( btaudio_t *ctx, btaudio_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->pwr, cfg->pwr );
    digital_out_init( &ctx->cmd, cfg->cmd );
    digital_out_init( &ctx->baud, cfg->baud );
    digital_out_init( &ctx->frs, cfg->frs );
    
    digital_out_low( &ctx->rst );
    digital_out_high( &ctx->baud );
    digital_out_low( &ctx->cmd );
    digital_out_low( &ctx->pwr );
    digital_out_high( &ctx->frs );

    return BTAUDIO_OK;
}

void btaudio_generic_write ( btaudio_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t btaudio_generic_read ( btaudio_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void btaudio_write_command ( btaudio_t *ctx, char *data_buf )
{
    uint8_t carriage_return = 13;
    uart_write( &ctx->uart, data_buf, strlen( data_buf ) );
    uart_write( &ctx->uart, &carriage_return, 1 );
}

void btaudio_set_power_on ( btaudio_t *ctx )
{
    digital_out_high( &ctx->pwr );
}

void btaudio_set_power_off ( btaudio_t *ctx )
{
    digital_out_low( &ctx->pwr );
}

void btaudio_reset ( btaudio_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

void btaudio_write_byte ( btaudio_t *ctx, uint8_t input )
{
    uart_write( &ctx->uart, &input, 1 );
}

// Set mode function 
void btaudio_set_mode ( btaudio_t *ctx, uint8_t mode )
{
    if ( mode == 1 )
    {
        digital_out_high( &ctx->cmd );
    }
    else
    {
        digital_out_low( &ctx->cmd );
    }
}

// Set command mode function 
void btaudio_set_cmd_mode ( btaudio_t *ctx, uint8_t mode )
{
    btaudio_set_mode( ctx, mode );
}

// Set factory defaults settings function 
void btaudio_set_factory_defaults ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 5 ] = "SF,1";
    uint8_t tmp[ 4 ] = "R,1";

    btaudio_write_command( ctx, tmp_buffer );
    Delay_10ms( );
    Delay_10ms( );
    btaudio_write_command( ctx, tmp );
}

// Get all settings function 
void btaudio_get_all_settings ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "D";

    btaudio_write_command( ctx, tmp_buffer );
}

// Set audio output function 
void btaudio_set_audio_output( btaudio_t *ctx, a2dp_routing_values_t setting, 
                                               bit_res_t bit_res, 
                                               sample_rate_t sample_rate )
{
    uint8_t tmp_buffer[ 8 ] =  "S|,";
    
    tmp_buffer[ 3 ] = 48;
    tmp_buffer[ 4 ] = setting + 48;
    tmp_buffer[ 5 ] = bit_res + 48;
    tmp_buffer[ 6 ] = sample_rate + 48;
    tmp_buffer[ 7 ] = 13;

    btaudio_generic_write( ctx, tmp_buffer, 8 );
}

// Set device name function 
uint8_t btaudio_set_device_name ( btaudio_t *ctx, uint8_t *name )
{
    uint8_t tmp_buffer[ 25 ] = "SN,";

    if ( strlen( name ) > 20 )
    {
        return BTAUDIO_ERR;
    }

    strcat( tmp_buffer, name );
    btaudio_write_command( ctx, tmp_buffer );

    return BTAUDIO_OK;
}

// Set automatic shutdown function 
uint8_t btaudio_set_automatic_shutdown ( btaudio_t *ctx, uint16_t seconds )
{
    uint8_t tmp_buffer[ 10 ] = "S^,";
    uint8_t tmp[ 6 ] = { 0 };
    
    if ( seconds > 600 )
    {
        return BTAUDIO_ERR;
    }
    
    uint16_to_str ( seconds, tmp );
    str_cut_chr ( tmp, ' ' );
    
    strcat( tmp_buffer, tmp );
    
    btaudio_write_command( ctx, tmp_buffer );

    return BTAUDIO_OK;
}

// Set extended features function 
void btaudio_set_extended_features ( btaudio_t *ctx, extended_features_bitmask_values ext_features )
{
    uint8_t tmp_buffer[ 20 ] = "S%,";
    uint8_t tmp[ 6 ] = { 0 };
    
    uint16_t tmp_ext = 1 << ext_features;

    uint16_to_hex ( tmp_ext, tmp );
    str_cut_chr ( tmp, ' ' );
    
    strcat( tmp_buffer, tmp );
    
    btaudio_write_command( ctx, tmp_buffer );
}

// Set authentication function 
void btaudio_set_authentication ( btaudio_t *ctx, uint8_t authentication )
{
    uint8_t tmp_buffer[ 5 ] = "SA,";
    uint8_t tmp_auth = authentication % 5;
    
    if ( tmp_auth == 3 )
    {
        tmp_auth = 4;
    }
    
    tmp_buffer[ 3 ] = tmp_auth + 48;
    btaudio_write_command( ctx, tmp_buffer );
}

// Set service class of device function 
uint8_t btaudio_set_service_class_device( btaudio_t *ctx, uint8_t *sc_device )
{
    uint8_t tmp_buffer[ 10 ] = "SC,";

    if ( strlen( sc_device ) > 6 )
    {
        return BTAUDIO_ERR;
    }
    
    strcat( tmp_buffer, sc_device );
    btaudio_write_command( ctx, tmp_buffer );

    return BTAUDIO_OK;
}

// Set service class of device function 
void btaudio_set_discovery_mask ( btaudio_t *ctx, uint8_t discovery_mask )
{
    uint8_t tmp_buffer[ 6 ] = "SD,";
    uint8_t tmp[ 4 ] = { 0 };
    uint8_t tmp_disc = discovery_mask % 16;
    
    uint8_to_hex ( tmp_disc, tmp );
    str_cut_chr ( tmp, ' ' );
    
    strcat( tmp_buffer, tmp );
    btaudio_write_command( ctx, tmp_buffer );
}

// Set the security pin code function 
uint8_t btaudio_set_security_pin ( btaudio_t *ctx, uint8_t *security_pin )
{
    uint8_t tmp_buffer[ 26 ] = "SP,";

    if ( strlen( security_pin ) > 20 )
    {
        return BTAUDIO_ERR;
    }

    strcat( tmp_buffer, security_pin );
    btaudio_write_command( ctx, tmp_buffer );

    return BTAUDIO_OK;
}

/* Set speaker gain levels function */
void btaudio_set_speaker_gain_lvl ( btaudio_t *ctx, uint8_t speaker_gain_lvl )
{
    uint8_t tmp_buffer[ 6 ] = "SS,";
    uint8_t tmp[ 4 ] = { 0 };
    uint8_t tmp_gain = speaker_gain_lvl % 16;

    uint8_to_hex ( tmp_gain, tmp );
    str_cut_chr ( tmp, ' ' );
    
    strcat( tmp_buffer, tmp );
    btaudio_write_command( ctx, tmp_buffer );
}

// Set tone gain levels function 
void btaudio_set_toneain_lvl ( btaudio_t *ctx, uint8_t tone_gain_lvl )
{
    uint8_t tmp_buffer[ 6 ] = "ST,";
    uint8_t tmp[ 4 ] = { 0 };
    uint8_t tmp_gain = tone_gain_lvl % 32;
    
    uint8_to_hex ( tmp_gain, tmp );
    str_cut_chr ( tmp, ' ' );

    strcat( tmp_buffer, tmp );
    btaudio_write_command( ctx, tmp_buffer );
}

// Get basic settings function 
void btaudio_get_basic_settings ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "D";

    btaudio_write_command( ctx, tmp_buffer );
}

// Get register settings function 
void btaudio_get_reg_settings ( btaudio_t *ctx, char cmd )
{
    uint8_t tmp_buffer[ 2 ];
    
    tmp_buffer[ 0 ] = 'G';
    tmp_buffer[ 1 ] = cmd;

    btaudio_write_command( ctx, tmp_buffer );
}

// Get battery status function 
void btaudio_get_battery_status ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 3 ] = "GB";
    
    btaudio_write_command( ctx, tmp_buffer );
}

// Get help status function 
void btaudio_get_help( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "H";
   
    btaudio_write_command( ctx, tmp_buffer );
}

// Get firmware version function 
void btaudio_get_firmware_version ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "V";
   
    btaudio_write_command( ctx, tmp_buffer );
}

// Toggle local echo function 
void btaudio_toggle_local_echo ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "+";

    btaudio_write_command( ctx, tmp_buffer );
}

// Toggle discoverable function 
uint8_t btaudio_toggle_discoverable ( btaudio_t *ctx, uint8_t discoverable )
{
    uint8_t tmp_buffer[ 4 ] = "@,";
    
    if ( discoverable > 1 )
    {
        return BTAUDIO_ERR;
    }
    
    tmp_buffer[ 2 ] = discoverable + 48;
    
    btaudio_write_command( ctx, tmp_buffer );

    return BTAUDIO_OK;
}

// Answer the keyboard function 
uint8_t btaudio_answer_keyboard ( btaudio_t *ctx, uint8_t answer )
{
    uint8_t tmp_buffer[ 4 ] = "#,";

    switch ( answer )
    {
        case 0: case '0': case 'n': case 'N':
        {
            if ( answer == 0 )
                tmp_buffer[ 2 ] = answer + 48;
            else
                tmp_buffer[ 2 ] = answer;
            break;
        }
        case 1: case '1': case 'y': case 'Y':
        {
            if ( answer == 1 )
                tmp_buffer[ 2 ] = answer + 48;
            else
                tmp_buffer[ 2 ] = answer;
            break;
        }
        default:
            return BTAUDIO_ERR;
    }
    
    btaudio_write_command( ctx, tmp_buffer );

    return BTAUDIO_OK;
}

// DFU mode function 
void btaudio_dfu_mode ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "$";

    btaudio_write_command( ctx, tmp_buffer );
}

// Call phone number function 
uint8_t btaudio_call_phone_number ( btaudio_t *ctx, char *p_number )
{
    uint8_t tmp_buffer[ 30 ] = "A,";

    if ( strlen( p_number ) > 25 )
    {
        return BTAUDIO_ERR;
    }
    
    strcat( tmp_buffer, p_number );

    btaudio_write_command( ctx, tmp_buffer );

    return BTAUDIO_OK;
}

// Show track metadata function 
void btaudio_show_track_metadata ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 3 ] = "AD";

    btaudio_write_command( ctx, tmp_buffer );
}

// Dial last phone number function 
void btaudio_dial_last_phone_number ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 3 ] = "AR";

    btaudio_write_command( ctx, tmp_buffer );
}

// Increase volume function 
void btaudio_increase_volume ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 4 ] = "AV+";

    btaudio_write_command( ctx, tmp_buffer );
}

// Decrease volume function 
void btaudio_decrease_volume ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 4 ] = "AV-";

    btaudio_write_command( ctx, tmp_buffer );
}

// Play next track function 
void btaudio_next_track ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 4 ] = "AT+";

    btaudio_write_command( ctx, tmp_buffer );
}

// Play previous track function 
void btaudio_previous_track ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 4 ] = "AT-";

    btaudio_write_command( ctx, tmp_buffer );
}

/* Pause track function */
void btaudio_pause_play_track ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 3 ] = "AP";

    btaudio_write_command( ctx, tmp_buffer );
}

// Enable voice commands function 
void btaudio_enable_voice_commands ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "P";

    btaudio_write_command( ctx, tmp_buffer );
}

// Get GPIO DIRR function 
void btaudio_get_gpio_dirr ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 3 ] = "I@";

    btaudio_write_command( ctx, tmp_buffer );
}

// Get GPIO level function 
void btaudio_get_gpio_level ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 3 ] = { "I&" };

    btaudio_write_command( ctx, tmp_buffer );
}

// Disconnect current connection function 
void btaudio_disconnect_current_connection ( btaudio_t *ctx, profile_bitmask_values profile )
{
    uint8_t tmp_buffer[ 5 ] = "K,0";
    
    tmp_buffer[ 3 ] = ( 1 << profile ) + 48;
    btaudio_write_command( ctx, tmp_buffer );
}

// Mute hold call function 
uint8_t btaudio_mute_hold_call ( btaudio_t *ctx, uint8_t mute )
{
    uint8_t tmp_buffer[ 4 ] = "M,";
    
    if ( mute > 1 )
    {
        return BTAUDIO_ERR;
    }

    tmp_buffer[ 2 ] = mute + 48;

    btaudio_write_command( ctx, tmp_buffer );

    return BTAUDIO_OK;
}

// Reboot function 
void btaudio_reboot ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 4 ] = "R,1";

    btaudio_write_command( ctx, tmp_buffer );
}

// Display caller Id function 
void btaudio_display_caller_id ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "T";
    
    btaudio_write_command( ctx, tmp_buffer );
}

// Reset prev paired devices function 
void btaudio_reset_prev_paired_devices ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "U";

    btaudio_write_command( ctx, tmp_buffer );
}

// Query connection status function 
void btaudio_query_connection_status ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "Q";
    
    btaudio_write_command( ctx, tmp_buffer );
}

// Reconnect most recent function 
void btaudio_reconnect_most_recent ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "B";

    btaudio_write_command( ctx, tmp_buffer );
}

// Accept call function 
void btaudio_accept_call ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "C";

    btaudio_write_command( ctx, tmp_buffer );
}

// Reject call function 
void btaudio_reject_call ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "E";

    btaudio_write_command( ctx, tmp_buffer );
}

// User busy function 
void btaudio_userBusy( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "F";

    btaudio_write_command( ctx, tmp_buffer );
}

// Accept held call function 
void btaudio_accept_held_call ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "J";

    btaudio_write_command( ctx, tmp_buffer );
}

// Set hold accept incoming function 
void btaudio_set_hold_accept_incoming ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "L";

    btaudio_write_command( ctx, tmp_buffer );
}

// Add held call function 
void btaudio_add_held_call ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "N";

    btaudio_write_command( ctx, tmp_buffer );
}

// Connect two calls function 
void btaudio_cnnct_two_calls ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 2 ] = "O";

    btaudio_write_command( ctx, tmp_buffer );
}

// Transfer active calls function 
void btaudio_transfer_active_calls ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 4 ] = "X,1";

    btaudio_write_command( ctx, tmp_buffer );
}

uint8_t btaudio_interrupt ( btaudio_t *ctx )
{
   return digital_in_read( &ctx->frs );
}

// ------------------------------------------------------------------------- END

