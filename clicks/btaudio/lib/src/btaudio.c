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

// ------------------------------------------------------------------ VARIABLES

static uint8_t response_finished;

// ----------------------------------------------- PRIVATE FUNCTION DECLARATION

static void clear_buffer ( btaudio_t *ctx );

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

    cfg->baud_rate      = 9600;
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

    // Input pins

    digital_in_init( &ctx->frs, cfg->frs );

    digital_out_low( &ctx->rst );

    return BTAUDIO_OK;
}

void btaudio_set_power_on ( btaudio_t *ctx )
{
    digital_out_high( &ctx->pwr );
}
void btaudio_set_power_off ( btaudio_t *ctx )
{
    digital_out_low( &ctx->pwr );
}

uint16_t btaudio_generic_write ( btaudio_t *ctx, char *data_buf )
{
    uint16_t cnt = 0;
    char *tmp_ptr = data_buf;

    while ( *tmp_ptr != 0 )
    {
        cnt++;
        tmp_ptr++;
    }

    uart_write( &ctx->uart, data_buf, cnt );

    return cnt;
}

void btaudio_write_byte ( btaudio_t *ctx, uint8_t input )
{
    uint8_t len = 1;
    uart_write( &ctx->uart, &input, len );
}

uint16_t btaudio_generic_read ( btaudio_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

// BT Audio RX ISR function 
void btaudio_rx_isr ( btaudio_t *ctx, char ch )
{
    ctx->buffer[ ctx->buffer_cnt++ ] = ch;
    
    if ( ch == 13 )
    {
        response_finished = 1;
        
        if( !ctx->getting_settings )
        {
            ctx->buffer[ --ctx->buffer_cnt ] = 0;
        }
    }
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
void btaudio_set_cmd_mode ( btaudio_t *ctx, uint8_t mode, uint8_t *response )
{
    uint8_t *response_ptr = response;

    clear_buffer( ctx );
    btaudio_set_mode( ctx, mode );

//    while ( !response_finished );

    strcpy( response_ptr,ctx->buffer);
}

// Set factory defaults settings function 
uint8_t btaudio_set_factory_defaults ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 20 ] = "SF,1";
    uint8_t tmp[ 15 ] = "R,1";

    clear_buffer( ctx );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    response_finished = 0;
    btaudio_generic_write( ctx, tmp );
    btaudio_write_byte( ctx, 13 );

    btaudio_process( ctx );

    //while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        clear_buffer( ctx );
        
        while( !response_finished );

        clear_buffer( ctx );
        
        return BTAUDIO_OK;
    }
    else 
    {
        return BTAUDIO_ERR;
    }
}

// Get all settings function 
void btaudio_get_all_settings ( btaudio_t *ctx, uint8_t *response )
{
    uint8_t *response_ptr = response;
    uint8_t i = 0;

    ctx->getting_settings = 1;
    clear_buffer( ctx );
    btaudio_write_byte( ctx, 'D' );
    btaudio_write_byte( ctx, 13 );

    for ( i = 0; i < 14; i++ )
    {
        while ( !response_finished );

        response_finished = 0;
    }
    
    ctx->buffer[ --ctx->buffer_cnt ] = 0;

    strcpy( response_ptr,ctx->buffer);

    ctx->getting_settings = 0;
}

// Set audio output function 
uint8_t btaudio_set_audio_output( btaudio_t *ctx, a2dp_routing_values_t setting, bit_res_t bit_res, sample_rate_t sample_rate )
{
    uint8_t tmp_buffer[ 20 ] =  "S|,";
    uint8_t value_buffer[ 20 ] = { 0 };
    
    value_buffer[ 0 ] = 0;
    value_buffer[ 1 ] = setting;
    value_buffer[ 2 ] = bit_res;
    value_buffer[ 3 ] = sample_rate;

    strcat( tmp_buffer, value_buffer );
    clear_buffer( ctx );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Set module name function 
uint8_t btaudio_set_module_name ( btaudio_t *ctx, uint8_t *name )
{
    uint8_t *name_ptr = name;
    uint8_t tmp_buffer[ 26 ] = "S-,";

    if ( strlen( name ) > 15 )
    {
        return BTAUDIO_ERR;
    }

    clear_buffer( ctx );
    strcat( tmp_buffer, name_ptr );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Set automatic shutdown function 
uint8_t btaudio_set_automatic_shutdown ( btaudio_t *ctx, uint16_t seconds )
{
    uint8_t tmp_buffer[ 20 ] = "S^,";
    uint8_t tmp[ 4 ] = { 0 };
    
    if ( seconds > 0 || seconds < 601 )
    {
        tmp[ 0 ] = seconds / 100;
        tmp[ 1 ] = ( seconds % 100 ) / 10;
        tmp[ 2 ] = seconds % 10;
        
        if ( tmp[ 0 ] == 0 )
        {
            if ( tmp[ 1 ] == 0 )
            {
                tmp[ 0 ] = tmp[ 2 ];
            }
            else
            {
                tmp[ 0 ] = tmp[ 1 ];
                tmp[ 1 ] = tmp[ 2 ];
            }
        }
    }

    clear_buffer( ctx );

    strcat( tmp_buffer, tmp );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Set extended features function 
uint8_t btaudio_set_extended_features ( btaudio_t *ctx, extended_features_bitmask_values  ext_features )
{
    uint8_t tmp_buffer[ 20 ] = "S%%,";
    uint8_t tmp[ 10 ] = { 0 };
    
    switch ( ext_features )
    {
        case 0:
        {
            tmp[ 3 ] = 1;
            break;
        }
        case 1:
        {
            tmp[ 3 ] = 2;
            break;
        }
        case 2:
        {
            tmp[ 3 ] = 4;
            break;
        }
        case 3:
        {
            tmp[ 3 ] = 8;
            break;
        }
        case 4:
        {
            tmp[ 2 ] = 1;
            tmp[ 3 ] = 0;
            break;
        }
        case 5:
        {
            tmp[ 2 ] = 2;
            tmp[ 3 ] = 0;
            break;
        }
        case 6:
        {
            tmp[ 2 ] = 4;
            tmp[ 3 ] = 0;
            break;
        }
        case 7:
        {
            tmp[ 2 ] = 8;
            tmp[ 3 ] = 0;
            break;
        }
        case 8:
        {
            tmp[ 1 ] = 1;
            tmp[ 2 ] = 0;
            tmp[ 3 ] = 0;
            break;
        }
        case 9:
        {
            tmp[ 1 ] = 2;
            tmp[ 2 ] = 0;
            tmp[ 3 ] = 0;
            break;
        }
        case 10:
        {
            tmp[ 1 ] = 4;
            tmp[ 2 ] = 0;
            tmp[ 3 ] = 0;
            break;
        }
        case 11:
        {
            tmp[ 1 ] = 8;
            tmp[ 2 ] = 0;
            tmp[ 3 ] = 0;
            break;
        }
        case 12:
        {
            tmp[ 0 ] = 1;
            tmp[ 1 ] = 0;
            tmp[ 2 ] = 0;
            tmp[ 3 ] = 0;
            break;
        }
        case 13:
        {
            tmp[ 0 ] = 2;
            tmp[ 1 ] = 0;
            tmp[ 2 ] = 0;
            tmp[ 3 ] = 0;
            break;
        }
        case 14:
        {
            tmp[ 0 ] = 4;
            tmp[ 1 ] = 0;
            tmp[ 2 ] = 0;
            tmp[ 3 ] = 0;
            break;
        }
    }

    clear_buffer( ctx );

    strcat( tmp_buffer, tmp );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Set authentication function 
uint8_t btaudio_set_authentication ( btaudio_t *ctx, uint8_t authentication )
{
    uint8_t tmp_buffer[ 20 ] = "SA,";
    uint8_t tmp[ 10 ] = { 0 };

    authentication %= 4;
    
    if ( authentication == 3 )
    {
        authentication = 4;
    }
    
    tmp[ 0 ] = authentication;

    clear_buffer( ctx );

    strcat( tmp_buffer, tmp );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Set service class of device function 
uint8_t btaudio_set_service_class_device( btaudio_t *ctx, uint8_t *sc_device )
{
    uint8_t *sc_device_ptr = sc_device;
    uint8_t tmp_buffer[ 26 ] = "SC,";

    if ( strlen( sc_device_ptr ) > 6 )
    {
        return BTAUDIO_ERR;
    }

    clear_buffer( ctx );
    
    strcat( tmp_buffer, sc_device_ptr );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Set service class of device function 
uint8_t btaudio_set_discovery_mask ( btaudio_t *ctx, uint8_t discovery_mask )
{
    uint8_t tmp_buffer[ 26 ] = "SD,";
    uint8_t tmp[ 10 ] = { 0 };
    
    discovery_mask %= 16;
    
    if ( discovery_mask < 10 )
    {
        tmp[ 0 ] = discovery_mask;
    }

    switch( discovery_mask )
    {
        case 10:
        {
            tmp[ 1 ] = 'A';
            break;
        }
        case 11:
        {
            tmp[ 1 ] = 'B';
            break;
        }
        case 12:
        {
            tmp[ 1 ] = 'C';
            break;
        }
        case 13:
        {
            tmp[ 1 ] ='D';
            break;
        }
        case 14:
        {
            tmp[ 1 ] = 'E';
            break;
        }
        case 15:
        {
            tmp[ 1 ] = 'F';
            break;
        }
    }

    clear_buffer( ctx );

    strcat( tmp_buffer, tmp );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Set the security pin code function 
uint8_t btaudio_set_security_pin ( btaudio_t *ctx, uint8_t *security_pin )
{
    uint8_t *security_pin = security_pin;
    uint8_t tmp_buffer[ 26 ] = "SP,";

    if ( strlen( security_pin ) > 20 )
    {
        return BTAUDIO_ERR;
    }

    clear_buffer( ctx );

    strcat( tmp_buffer, security_pin );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

/* Set speaker gain levels function */
uint8_t btaudio_set_speaker_gain_lvl ( btaudio_t *ctx, uint8_t speaker_gain_lvl )
{
    uint8_t tmp_buffer[ 26 ] = "SS,";
    uint8_t tmp[ 10 ] = { 0 };

    speaker_gain_lvl %= 16;

    if ( speaker_gain_lvl < 10 )
    {
        tmp[ 0 ] = speaker_gain_lvl;
    }
    else
    {
        tmp[ 0 ] = 0;
    }

    switch ( speaker_gain_lvl )
    {
        case 10:
        {
            tmp[ 1 ] = 'A';
            break;
        }
        case 11:
        {
            tmp[ 1 ] = 'B';
            break;
        }
        case 12:
        {
            tmp[ 1 ] = 'C';
            break;
        }
        case 13:
        {
            tmp[ 1 ] ='D';
            break;
        }
        case 14:
        {
            tmp[ 1 ] = 'E';
            break;
        }
        case 15:
        {
            tmp[ 1 ] = 'F';
            break;
        }
    }

    clear_buffer( ctx );

    strcat( tmp_buffer, tmp );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Set tone gain levels function 
uint8_t btaudio_set_toneain_lvl ( btaudio_t *ctx, uint8_t tone_gain_lvl )
{
    uint8_t tmp_buffer[ 26 ] = "ST,";
    uint8_t tmp[ 10 ] = { 0 };
    uint8_t ones;
    uint8_t two;

    tone_gain_lvl %= 32;
    
    two = tone_gain_lvl / 16;
    ones = tone_gain_lvl % 16;
    
    if ( two > 0 )
    {
        tmp[ 0 ] = 1;
    }
    else
    {
        tmp[ 0 ] = 0;
    }
    
    if ( ones < 10 )
    {
        tmp[ 1 ] = ones;
    }
        
    switch ( ones )
    {
        case 10:
        {
            tmp[ 1 ] = 'A';
            break;
        }
        case 11:
        {
            tmp[ 1 ] = 'B';
            break;
        }
        case 12:
        {
            tmp[ 1 ] = 'C';
            break;
        }
        case 13:
        {
            tmp[ 1 ] ='D';
            break;
        }
        case 14:
        {
            tmp[ 1 ] = 'E';
            break;
        }
        case 15:
        {
            tmp[ 1 ] = 'F';
            break;
        }
    }

    clear_buffer( ctx );

    strcat( tmp_buffer, tmp );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Get basic settings function 
uint8_t btaudio_get_basic_settings ( btaudio_t *ctx, uint8_t *response )
{
    uint8_t tmp_buffer[ 20 ] = "D";
    uint8_t *tmp_ptr = response;

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    strcpy( tmp_ptr,ctx->buffer);
    
    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Get register settings function 
uint8_t btaudio_get_reg_settings ( btaudio_t *ctx, char *cmd, uint8_t *response )
{
    uint8_t tmp_buffer[ 20 ] = "G";

    clear_buffer( ctx );
    
    strcat( tmp_buffer, cmd );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Get battery status function 
void btaudio_get_battery_status ( btaudio_t *ctx, uint8_t *response )
{
    uint8_t tmp_buffer[ 20 ] = "GB";
    uint8_t *tmp_ptr = response;

    clear_buffer( ctx );
    
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    strcpy( tmp_ptr,ctx->buffer);
}

// Get help status function 
void btaudio_get_help( btaudio_t *ctx, uint8_t *response )
{
    uint8_t tmp_buffer[ 20 ] = "H";
    uint8_t *tmp_ptr = response;
    uint8_t tmp[ 15 ] = { 0 };
    uint8_t i = 0;

    ctx->getting_settings = 1;
    
    clear_buffer( ctx );
    
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    for ( i = 0; i < 30; i++ )
    {
        while ( !response_finished );

        response_finished = 0;
    }

    strcpy( tmp_ptr,ctx->buffer);
    ctx->getting_settings = 0;
}

// Get firmware version function 
void btaudio_get_firmware_version ( btaudio_t *ctx, uint8_t *response )
{
    uint8_t tmp_buffer[ 20 ] = "V";
    uint8_t *tmp_ptr = response;

    clear_buffer( ctx );
    
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    strcpy( tmp_ptr,ctx->buffer);
}

// Toggle local echo function 
void btaudio_toggle_local_echo ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "+";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );
}

// Toggle discoverable function 
uint8_t btaudio_toggle_discoverable ( btaudio_t *ctx, uint8_t discoverable )
{
    uint8_t tmp_buffer[ 10 ] = "@,";
    
    discoverable %= 2;

    if ( discoverable )
    {
        tmp_buffer[ 2 ] = '1';
    }
    else
    {
        tmp_buffer[ 2 ] = '0';
    }
    
    clear_buffer( ctx );
    
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Answer the keyboard function 
uint8_t btaudio_answer_keyboard ( btaudio_t *ctx, uint8_t answer )
{
    uint8_t tmp_buffer[ 10 ] = "#,";
    
    answer %= 2;

    if ( answer )
    {
        tmp_buffer[ 2 ] = '1';
    }
    else
    {
        tmp_buffer[ 2 ] = '0';
    }
    
    clear_buffer( ctx );
    
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// DFU mode function 
void btaudio_dfu_mode ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "$";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while( !response_finished );
}

// Call phone number function 
uint8_t btaudio_call_phone_number ( btaudio_t *ctx, char *p_number )
{
    uint8_t tmp_buffer[ 25 ] = "A,";
    uint8_t *tmp_ptr = p_number;

    strcat( tmp_buffer, tmp_ptr );

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Show track metadata function 
void btaudio_show_track_metadata ( btaudio_t *ctx, uint8_t *track_data )
{
    uint8_t *track_data_ptr = track_data;
    uint8_t tmp_buffer[ 8 ] = "AD";
    uint8_t i = 0;
    uint32_t timeout = 0;

    ctx->getting_settings = 1;

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    clear_buffer( ctx );

    for ( i = 0; i < 14; i++)
    {
        while( !response_finished )
        {
            timeout++;
            
            if( timeout >= 1000000 )
            {
                timeout = 0;
                break;
            }
        }
        
        timeout = 0;

        response_finished = 0;
    }
    
    ctx->getting_settings = 0;
    ctx->buffer[ --ctx->buffer_cnt ] = 0;
    strcpy( track_data_ptr,ctx->buffer);
}

// Dial last phone number function 
uint8_t btaudio_dial_last_phone_number ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "AR";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Increase volume function 
uint8_t btaudio_increase_volume ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "AV+";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    btaudio_process( ctx );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Decrease volume function 
uint8_t btaudio_decrease_volume ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "AV-";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    btaudio_process( ctx );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Play next track function 
uint8_t btaudio_next_track ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "AT+";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    btaudio_process( ctx );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Play previous track function 
uint8_t btaudio_previous_track ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "AT-";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    btaudio_process( ctx );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

/* Pause track function */
uint8_t btaudio_pause_play_track ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "AP";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    btaudio_process( ctx );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Enable voice commands function 
uint8_t btaudio_enable_voice_commands ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "P";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while( !response_finished );

    if ( ctx->buffer[ 0 ] == 'E' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Get GPIO DIRR function 
void btaudio_get_gpio_dirr ( btaudio_t *ctx, uint8_t *response )
{
    uint8_t tmp_buffer[ 10 ] = "I@";
    uint8_t *tmp_ptr = response;

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    strcpy( tmp_ptr,ctx->buffer);
}

// Get GPIO level function 
void btaudio_get_gpio_level ( btaudio_t *ctx, uint8_t *response )
{
    uint8_t tmp_buffer[ 10 ] = { "I&" };

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while( !response_finished );

    strcpy( response,ctx->buffer);
}

// Disconnect current connection function 
uint8_t btaudio_disconnect_current_connection ( btaudio_t *ctx, profile_bitmask_values profile )
{
    uint8_t tmp_buffer[ 20 ] = "K,0";
    uint8_t tmp[ 15 ] = { 0 };

    clear_buffer( ctx );

    strcat( tmp_buffer, tmp );
    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'K' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Mute hold call function 
uint8_t btaudio_mute_hold_call ( btaudio_t *ctx, uint8_t mute )
{
    uint8_t tmp_buffer[ 20 ] = "M,";
    
    mute %= 2;

    if ( mute )
    {
        tmp_buffer[ 2 ] = '1';
    }
    else
    {
        tmp_buffer[ 2 ] = '0';
    }
    
    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Reboot function 
uint8_t btaudio_reboot ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "R,1";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'R' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Display caller Id function 
void btaudio_display_caller_id ( btaudio_t *ctx, uint8_t *response )
{
    uint8_t tmp_buffer[ 10 ] = "T";
    uint8_t *tmp_ptr = response;

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    strcpy( tmp_ptr,ctx->buffer);
}

// Reset prev paired devices function 
uint8_t btaudio_reset_prev_paired_devices ( btaudio_t *ctx )
{
    uint8_t tmp_buffer[ 10 ] = "U";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    if ( ctx->buffer[ 0 ] == 'A' )
    {
        return BTAUDIO_OK;
    }
    else
    {
        return BTAUDIO_ERR;
    }
}

// Query connection status function 
void btaudio_query_connection_status ( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 10 ] = "Q";
    uint16_t tmp = 0;
    uint8_t h_byte;
    uint8_t l_byte;
    uint8_t tmp_h_byte;

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    tmp = xtoi(ctx->buffer);
    h_byte = ( uint8_t ) tmp;
    l_byte = ( uint8_t ) ( tmp >> 8 );

    if ( l_byte & 1 )
    {
        status->iap_connection = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->iap_connection = BTAUDIO_STATUS_FALSE;
    }
    
    if ( l_byte & 2 )
    {
        status->ssp_connection = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->ssp_connection = BTAUDIO_STATUS_FALSE;
    }
    
    if ( l_byte & 4 )
    {
        status->a2dp_connection = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->a2dp_connection = BTAUDIO_STATUS_FALSE;
    }
    
    if ( l_byte & 8 )
    {
        status->hfp_hsp_connection = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->hfp_hsp_connection = BTAUDIO_STATUS_FALSE;
    }
    
    if ( l_byte & 16 )
    {
        status->caller_id_notification = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->caller_id_notification = BTAUDIO_STATUS_FALSE;
    }
    
    if ( l_byte & 32 )
    {
        status->track_change_event = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->track_change_event = BTAUDIO_STATUS_FALSE;
    }

    tmp_h_byte = ( h_byte & 0x0F );
    
    if ( tmp_h_byte == 0 )
    {
        status->limbo = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->limbo = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 1 )
    {
        status->connectable = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->connectable = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 2 )
    {
        status->connectable_discoverable = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->connectable_discoverable = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 3 )
    {
        status->connected = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->connected = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 4 )
    {
        status->outgoing_call = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->outgoing_call = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 5 )
    {
        status->incoming_call = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->incoming_call = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 6 )
    {
        status->active_call_headset = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->active_call_headset = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 7 )
    {
        status->test_mode = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->test_mode = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 8 )
    {
        status->three_way_waiting = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->three_way_waiting = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 9 )
    {
        status->three_way_holding = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->three_way_holding = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 10 )
    {
        status->three_way_multi_call = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->three_way_multi_call = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 11 )
    {
        status->incoming_call_on_hold = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->incoming_call_on_hold = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 12 )
    {
        status->active_call_handset = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->active_call_handset = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 13 )
    {
        status->audio_streaming = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->audio_streaming = BTAUDIO_STATUS_FALSE;
    }
    
    if ( tmp_h_byte == 14 )
    {
        status->low_battery = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->low_battery = BTAUDIO_STATUS_FALSE;
    }
    
    if ( h_byte & 0x08 )
    {
        status->HFP_vol_chnge = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->HFP_vol_chnge = BTAUDIO_STATUS_FALSE;
    }
    
    if ( h_byte & 0x10 )
    {
        status->HFP_mic_lvl_chnge = BTAUDIO_STATUS_TRUE;
    }
    else
    {
        status->HFP_mic_lvl_chnge = BTAUDIO_STATUS_FALSE;
    }
}

// Reconnect most recent function 
void btaudio_reconnect_most_recent ( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 10 ] = "B";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    btaudio_query_connection_status( ctx, status );

}

// Accept call function 
void btaudio_accept_call ( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 10 ] = "C";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    btaudio_query_connection_status( ctx, status );

}

// Reject call function 
void btaudio_reject_call ( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 10 ] = "E";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    btaudio_query_connection_status( ctx, status );
}

// User busy function 
void btaudio_userBusy( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 10 ] = "F";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    btaudio_query_connection_status( ctx, status );
}

// Accept held call function 
void btaudio_accept_held_call ( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 10 ] = "J";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    btaudio_query_connection_status( ctx, status );
}

// Set hold accept incoming function 
void btaudio_set_hold_accept_incoming ( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 10 ] = "L";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    btaudio_query_connection_status( ctx, status );
}

// Add held call function 
void btaudio_add_held_call ( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 10 ] = "N";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    btaudio_query_connection_status( ctx, status );
}

// Connect two calls function 
void btaudio_cnnct_two_calls ( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 10 ] = "O";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while ( !response_finished );

    btaudio_query_connection_status( ctx, status );
}

// Transfer active calls function 
void btaudio_transfer_active_calls ( btaudio_t *ctx, connection_status_t *status )
{
    uint8_t tmp_buffer[ 20 ] = "X,1";

    clear_buffer( ctx );

    btaudio_generic_write( ctx, tmp_buffer );
    btaudio_write_byte( ctx, 13 );

    while( !response_finished );

    btaudio_query_connection_status( ctx, status );
}

uint8_t btaudio_interrupt ( btaudio_t *ctx )
{
   return digital_in_read( &ctx->frs );
}

void btaudio_process ( btaudio_t *ctx )
{
    uint16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    rsp_size = btaudio_generic_read( ctx, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size != 0 )
    {  
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            btaudio_rx_isr ( ctx, uart_rx_buffer[ check_buf_cnt ] ); 
        }
        // Clear RX buffer
        memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
    } 
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void clear_buffer ( btaudio_t *ctx )
{
    memset( ctx->buffer, 0, 0 );
    response_finished = 0;
}

// ------------------------------------------------------------------------- END

