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

#include "rn4678.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void delay500ms( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rn4678_cfg_setup ( rn4678_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->wkup = HAL_PIN_NC;
    cfg->sw_btn = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

RN4678_RETVAL rn4678_init ( rn4678_t *ctx, rn4678_cfg_t *cfg )
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
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->wkup, cfg->wkup );
    digital_out_init( &ctx->sw_btn, cfg->sw_btn );
    
    // Input pins

    digital_in_init( &ctx->rts, cfg->rts );

    return RN4678_OK;
}

void rn4678_generic_write ( rn4678_t *ctx, char *data_buf, uint16_t len )
{
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        uart_write( &ctx->uart, data_buf++, 1 );
        Delay_1ms();
    }
}

void rn4678_write_command ( rn4678_t *ctx, char *data_buf, uint16_t len )
{
    uint8_t tmp_buf[ 30 ] = { 0 };
    uint8_t carriage_return[ ] = "\r";
    memcpy( tmp_buf, data_buf, len );
    strcat( tmp_buf, carriage_return );
    
    digital_out_high( &ctx->cts );
    Delay_1ms( );
    rn4678_generic_write( ctx, tmp_buf, len + 1 );
    digital_out_low( &ctx->cts );
}

int32_t rn4678_generic_read ( rn4678_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void rn4678_set_cts_pin ( rn4678_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->cts );
    }
    else
    {
        digital_out_low( &ctx->cts );
    }
}

void rn4678_enable ( rn4678_t *ctx )
{ 
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->sw_btn );
    digital_out_low( &ctx->wkup );
}

void rn4678_hw_reset ( rn4678_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

void rn4678_enter_command_mode ( rn4678_t *ctx )
{
    uint8_t cmd_mode[ ] = "$$$";
    
    digital_out_high( &ctx->cts );
    Delay_1ms( );
    rn4678_generic_write( ctx, cmd_mode, 3 );
    digital_out_low( &ctx->cts );
}

void rn4678_exit_command_mode ( rn4678_t *ctx )
{
    uint8_t exit_cmd_mode[ ] = "---";

    rn4678_write_command( ctx, exit_cmd_mode, 3 );
}

void rn4678_toggle_echo ( rn4678_t *ctx )
{
    uint8_t cmd_toggle = '+';

    rn4678_write_command( ctx, &cmd_toggle, 1 );
}

void rn4678_set_device_name ( rn4678_t *ctx, uint8_t *name )
{
    uint8_t tx_buffer[ 23 ] = { "SN," };
    
    if( strlen( name ) > 20 )
    {
        name[ 20 ] = 0;
    }
    
    strcat( tx_buffer, name );
    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void rn4678_set_operating_mode ( rn4678_t *ctx, uint8_t op_mode )
{
    uint8_t tx_buffer[ 5 ] = { "SM, " };
    
    tx_buffer[ 3 ] = op_mode + 48;
    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void rn4678_enable_7_bit_data_mode ( rn4678_t *ctx )
{
    uint8_t tx_buffer[ 5 ] = { "S7,1" };

    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void rn4678_disable_7_bit_data_mode ( rn4678_t *ctx )
{
    uint8_t tx_buffer[ 5 ] = { "S7,0" };

    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void rn4678_set_authentication ( rn4678_t *ctx, uint8_t auth_value )
{
    uint8_t tx_buffer[ 5 ] = { "SA, " };

    tx_buffer[ 3 ] = auth_value + 48;
    
    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void rn4678_set_break ( rn4678_t *ctx, uint8_t break_signal )
{
    uint8_t tx_buffer[ 5 ] = { "SB, " };

    tx_buffer[ 3 ] = break_signal + 48;

    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

RN4678_RETVAL rn4678_set_cod ( rn4678_t *ctx, uint8_t *msw, uint8_t *lsw )
{
    uint8_t *msw_ptr = msw;
    uint8_t *lsw_ptr = lsw;
    uint8_t tx_buffer_c[ 20 ] = { "SC," };
    uint8_t tx_buffer_d[ 20 ] = { "SD," };

    if( strlen( msw ) > 4 || strlen( lsw ) > 4 )
    {
        return RN4678_ERR;
    }

    strcat( tx_buffer_c, msw );
    rn4678_write_command( ctx, tx_buffer_c, strlen( tx_buffer_c ) );
    delay500ms( );
    
    strcat( tx_buffer_d, lsw );
    rn4678_write_command( ctx, tx_buffer_d, strlen( tx_buffer_d ) );
    delay500ms( );

    return RN4678_OK;
}

void rn4678_set_factory_defaults ( rn4678_t *ctx )
{
    uint8_t tmp_buffer[ 5 ] = { "SF,1" };

    rn4678_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );
}

void rn4678_set_discoverability ( rn4678_t *ctx, uint8_t *d_hex_value )
{
    uint8_t tmp_buffer[ 20 ] = { "SI," };

    strcat( tmp_buffer, d_hex_value );
    rn4678_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );
}

void rn4678_setConnectability ( rn4678_t *ctx, uint8_t *c_hex_value )
{
    uint8_t tmp_buffer[ 20 ] = { "SJ," };

    strcat( tmp_buffer, c_hex_value );
    rn4678_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );
}

RN4678_RETVAL rn4678_set_uart_parity ( rn4678_t *ctx, uint8_t character )
{
    uint8_t input;
    uint8_t tmp_buffer[ 20 ] = { "SL," };
    
    digital_out_high( &ctx->cts );
    Delay_1ms( );
    switch ( character )
    {
        case  'E':
        {
            rn4678_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
            input = 69;
            rn4678_generic_write( ctx, &input, 1 );
            input = 13;
            rn4678_generic_write( ctx, &input, 1 );

            return RN4678_OK;
        }
        case  'O':
        {
            rn4678_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
            input = 79;
            rn4678_generic_write( ctx, &input, 1 );
            input = 13;
            rn4678_generic_write( ctx, &input, 1 );

            return RN4678_OK;
        }
        case  'N':
        {
            rn4678_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
            input = 78;
            rn4678_generic_write( ctx, &input, 1 );
            input = 13;
            rn4678_generic_write( ctx, &input, 1 );

            return RN4678_OK;
        }
    }
    digital_out_low( &ctx->cts );

    return RN4678_ERR;
}

void rn4678_set_extended_status_string ( rn4678_t *ctx, uint8_t *es_string )
{
    uint8_t tx_buffer[ 23 ] = { "SO," };
    
    if( strlen( es_string ) > 8 )
    {
        es_string[ 8 ] = 0;
    }
    
    strcat( tx_buffer, es_string );
    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

RN4678_RETVAL rn4678_set_security_pin_code ( rn4678_t *ctx, uint8_t *sp_code )
{
    uint8_t tmp_buffer[ 23 ] = { "SP," };
    
    if ( strlen( sp_code ) > 20 )
    {
        return RN4678_ERR;
    }

    strcat( tmp_buffer, sp_code );
    rn4678_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );

    return RN4678_OK;
}

RN4678_RETVAL rn4678_set_special_config ( rn4678_t *ctx, uint16_t special_config )
{
    switch ( special_config )
    {
        case  0:
        {
            rn4678_write_command( ctx, "SQ,0", 4 );

            return RN4678_OK;
        }
        case  4:
        {
            rn4678_write_command( ctx, "SQ,4", 4 );
            
            return RN4678_OK;
        }
        case  8:
        {
            rn4678_write_command( ctx, "SQ,8", 4 );

            return RN4678_OK;
        }
        case  16:
        {
            rn4678_write_command( ctx, "SQ,16", 5 );

            return RN4678_OK;
        }
        case  128:
        {
            rn4678_write_command( ctx, "SQ,128", 6 );

            return RN4678_OK;
        }
        case  256:
        {
            rn4678_write_command( ctx, "SQ,256", 6 );

            return RN4678_OK;
        }
    }

    return RN4678_ERR;
}

void rn4678_set_remote_address ( rn4678_t *ctx, uint8_t *r_addr )
{
    uint8_t tmp_buffer[ 20 ] = { "SR," };

    strcat( tmp_buffer, r_addr );
    rn4678_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );
}

RN4678_RETVAL rn4678_set_baud_rate ( rn4678_t *ctx, uint32_t baud_rate )
{
    switch ( baud_rate )
    {
        case  1200:
        {
            rn4678_write_command( ctx, "SU,12", 5 );

            return RN4678_OK;
        }
        case  2400:
        {
            rn4678_write_command( ctx, "SU,24", 5 );

            return RN4678_OK;
        }
        case  9600:
        {
            rn4678_write_command( ctx, "SU,96", 5 );

            return RN4678_OK;
        }
        case  19200:
        {
            rn4678_write_command( ctx, "SU,19", 5 );

            return RN4678_OK;
        }
        case  38400:
        {
            rn4678_write_command( ctx, "SU,38", 5 );

            return RN4678_OK;
        }
        case  57600:
        {
            rn4678_write_command( ctx, "SU,57", 5 );

            return RN4678_OK;
        }
        case  115200:
        {
            rn4678_write_command( ctx, "SU,11", 5  );

            return RN4678_OK;
        }
    }

    return RN4678_ERR;
}

void rn4678_enable_bonding ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "SX,1", 4 );
}

void rn4678_disable_bonding ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "SX,0", 4 );
}

void rn4678_reboot ( rn4678_t *ctx )
{ 
    rn4678_write_command( ctx, "R,1", 3 );
}

RN4678_RETVAL rn4678_set_profile ( rn4678_t *ctx, uint8_t profile )
{
    uint8_t tx_buffer[ 20 ] = { "S~, " };

    if ( profile > 6 )
    {
        return RN4678_ERR;
    }

    tx_buffer[ 3 ] = profile + 48;

    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );

    return RN4678_OK;
}

void rn4678_enable_role_switch ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "S?,1", 4 );
}

void rn4678_disable_role_switch ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "S?,0", 4 );
}

void rn4678_connect_to_remote_address ( rn4678_t *ctx, uint8_t *r_addr )
{
    uint8_t tx_buffer[ 20 ] = { "C," };

    strcat( tx_buffer, r_addr );
    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void rn4678_connect_to_remote_address_fast_mode ( rn4678_t *ctx, uint8_t *r_addr )
{
    uint8_t tx_buffer[ 20 ] = { "CF," };
    
    strcat( tx_buffer, r_addr );
    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void rn4678_endspecial_config ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "F,1", 3 );
}

void rn4678_get_help ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "H", 1 );
}

void rn4678_get_basic_settings ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "D", 1 );
}

void rn4678_get_extended_settings ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "E", 1 );
}

void rn4678_get_device_address ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "GB", 2 );
}

void rn4678_scans_device ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "IQ", 2 );
}

void rn4678_get_signal_status ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "M", 1 );
}

void rn4678_set_undiscoverable (  rn4678_t *ctx )
{
    rn4678_write_command( ctx, "Q,", 2 );
}

RN4678_RETVAL rn4678_set_quiet_mode ( rn4678_t *ctx, uint8_t q_mode )
{
    uint8_t tx_buffer[ 20 ] = { "Q, " };

    if ( q_mode == 0 || q_mode == 1 || q_mode == 2 )
    {
        tx_buffer[ 3 ] = q_mode + 48;
    }
    else if ( q_mode == 3 )
    {
        tx_buffer[ 3 ] = 63;
    }
    else
    {
        return RN4678_ERR;
    }

    rn4678_write_command( ctx, tx_buffer, strlen( tx_buffer ) );

    return RN4678_OK;
}


void rn4678_get_firmware_version ( rn4678_t *ctx )
{
    rn4678_write_command( ctx, "V", 1 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void delay500ms()
{
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
}

// ------------------------------------------------------------------------- END

