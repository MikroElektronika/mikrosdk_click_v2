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

#include "bluetooth.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void delay500ms( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void bluetooth_cfg_setup ( bluetooth_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

BLUETOOTH_RETVAL bluetooth_init ( bluetooth_t *ctx, bluetooth_cfg_t *cfg )
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

    digital_out_high( &ctx->rst );

    return BLUETOOTH_OK;
}

void bluetooth_generic_write ( bluetooth_t *ctx, char *data_buf, uint16_t len )
{
    while(*data_buf) {
        uart_write( &ctx->uart, data_buf++, 1);
        Delay_10us();
    }
}

void bluetooth_write_command ( bluetooth_t *ctx, char *data_buf, uint16_t len )
{
    uint8_t tmp_buf[ 30 ];
    uint8_t carriage_return = '\r';
    memcpy( tmp_buf, data_buf, len );
    strcat( tmp_buf, &carriage_return );
    
    bluetooth_generic_write( ctx, tmp_buf, len+1 );
}

int32_t bluetooth_generic_read ( bluetooth_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void bluetooth_enable ( bluetooth_t *ctx )
{ 
    digital_out_high( &ctx->rst );
}

void bluetooth_hw_reset ( bluetooth_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

void bluetooth_enter_command_mode ( bluetooth_t *ctx )
{
    uint8_t cmd_mode[ ] = "$$$";

    bluetooth_generic_write( ctx, cmd_mode, 3 );
}

void bluetooth_exit_command_mode ( bluetooth_t *ctx )
{
    uint8_t exit_cmd_mode[ ] = "---";

    bluetooth_write_command( ctx, exit_cmd_mode, 3 );
}

void bluetooth_toggle_echo ( bluetooth_t *ctx )
{
    uint8_t cmd_toggle = '+';

    bluetooth_write_command( ctx, &cmd_toggle, 1 );
}

void bluetooth_set_device_name ( bluetooth_t *ctx, uint8_t *name )
{
    uint8_t tx_buffer[ 23 ] = { "SN," };
    
    if( strlen( name ) > 20 )
    {
        name[ 20 ] = 0;
    }
    
    strcat( tx_buffer, name );
    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void bluetooth_set_operating_mode ( bluetooth_t *ctx, uint8_t op_mode )
{
    uint8_t tx_buffer[ 5 ] = { "SM," };
    
    tx_buffer[ 3 ] = op_mode + 48;
    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void bluetooth_enable_7_bit_data_mode ( bluetooth_t *ctx )
{
    uint8_t tx_buffer[ 5 ] = { "S7,1" };

    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void bluetooth_disable_7_bit_data_mode ( bluetooth_t *ctx )
{
    uint8_t tx_buffer[ 5 ] = { "S7,0" };

    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void bluetooth_set_authentication ( bluetooth_t *ctx, uint8_t auth_value )
{
    uint8_t tx_buffer[ 5 ] = { "SA," };

    tx_buffer[ 3 ] = auth_value + 48;

    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void bluetooth_set_break ( bluetooth_t *ctx, uint8_t break_signal )
{
    uint8_t tx_buffer[ 5 ] = { "SB," };

    tx_buffer[ 3 ] = break_signal + 48;

    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

BLUETOOTH_RETVAL bluetooth_set_cod ( bluetooth_t *ctx, uint8_t *msw, uint8_t *lsw )
{
    uint8_t *msw_ptr = msw;
    uint8_t *lsw_ptr = lsw;
    uint8_t tx_buffer_c[ 20 ] = { "SC," };
    uint8_t tx_buffer_d[ 20 ] = { "SD," };

    if( strlen( msw ) > 4 || strlen( lsw ) > 4 )
    {
        return BLUETOOTH_ERR;
    }

    strcat( tx_buffer_c, msw );
    bluetooth_write_command( ctx, tx_buffer_c, strlen( tx_buffer_c ) );
    delay500ms( );
    
    strcat( tx_buffer_d, lsw );
    bluetooth_write_command( ctx, tx_buffer_d, strlen( tx_buffer_d ) );
    delay500ms( );

    return BLUETOOTH_OK;
}

void bluetooth_set_factory_defaults ( bluetooth_t *ctx )
{
    uint8_t tmp_buffer[ 5 ] = { "SF,1" };

    bluetooth_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );
}

void bluetooth_set_discoverability ( bluetooth_t *ctx, uint8_t *d_hex_value )
{
    uint8_t tmp_buffer[ 20 ] = { "SI," };

    strcat( tmp_buffer, d_hex_value );
    bluetooth_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );
}

void bluetooth_setConnectability ( bluetooth_t *ctx, uint8_t *c_hex_value )
{
    uint8_t tmp_buffer[ 20 ] = { "SJ," };

    strcat( tmp_buffer, c_hex_value );
    bluetooth_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );
}

BLUETOOTH_RETVAL bluetooth_set_uart_parity ( bluetooth_t *ctx, uint8_t character )
{
    uint8_t input;
    uint8_t tmp_buffer[ 20 ] = { "SL," };
    
    switch ( character )
    {
        case  'E':
        {
            bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
            input = 69;
            bluetooth_generic_write( ctx, &input, 1 );
            input = 13;
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
        }
        case  'O':
        {
            bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
            input = 79;
            bluetooth_generic_write( ctx, &input, 1 );
            input = 13;
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
        }
        case  'N':
        {
            bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
            input = 78;
            bluetooth_generic_write( ctx, &input, 1 );
            input = 13;
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
        }
    }

    return BLUETOOTH_ERR;
}

void bluetooth_set_extended_status_string ( bluetooth_t *ctx, uint8_t *es_string )
{
    uint8_t tx_buffer[ 23 ] = { "SO," };
    
    if( strlen( es_string ) > 8 )
    {
        es_string[ 8 ] = 0;
    }
    
    strcat( tx_buffer, es_string );
    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

BLUETOOTH_RETVAL bluetooth_set_security_pin_code ( bluetooth_t *ctx, uint8_t *sp_code )
{
    uint8_t tmp_buffer[ 23 ] = { "SP," };
    
    if ( strlen( sp_code ) > 20 )
    {
        return BLUETOOTH_ERR;
    }

    strcat( tmp_buffer, sp_code );
    bluetooth_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_special_config ( bluetooth_t *ctx, uint16_t special_config )
{
    switch ( special_config )
    {
        case  0:
        {
            bluetooth_write_command( ctx, "SQ,0", 4 );

            return BLUETOOTH_OK;
        }
        case  4:
        {
            bluetooth_write_command( ctx, "SQ,4", 4 );
            
            return BLUETOOTH_OK;
        }
        case  8:
        {
            bluetooth_write_command( ctx, "SQ,8", 4 );

            return BLUETOOTH_OK;
        }
        case  16:
        {
            bluetooth_write_command( ctx, "SQ,16", 5 );

            return BLUETOOTH_OK;
        }
        case  128:
        {
            bluetooth_write_command( ctx, "SQ,128", 6 );

            return BLUETOOTH_OK;
        }
        case  256:
        {
            bluetooth_write_command( ctx, "SQ,256", 6 );

            return BLUETOOTH_OK;
        }
    }

    return BLUETOOTH_ERR;
}

void bluetooth_set_remote_address ( bluetooth_t *ctx, uint8_t *r_addr )
{
    uint8_t tmp_buffer[ 20 ] = { "SR," };

    strcat( tmp_buffer, r_addr );
    bluetooth_write_command( ctx, tmp_buffer, strlen( tmp_buffer ) );
}

BLUETOOTH_RETVAL bluetooth_set_baud_rate ( bluetooth_t *ctx, uint32_t baud_rate )
{
    switch ( baud_rate )
    {
        case  1200:
        {
            bluetooth_write_command( ctx, "SU,12", 5 );

            return BLUETOOTH_OK;
        }
        case  2400:
        {
            bluetooth_write_command( ctx, "SU,24", 5 );

            return BLUETOOTH_OK;
        }
        case  9600:
        {
            bluetooth_write_command( ctx, "SU,96", 5 );

            return BLUETOOTH_OK;
        }
        case  19200:
        {
            bluetooth_write_command( ctx, "SU,19", 5 );

            return BLUETOOTH_OK;
        }
        case  38400:
        {
            bluetooth_write_command( ctx, "SU,38", 5 );

            return BLUETOOTH_OK;
        }
        case  57600:
        {
            bluetooth_write_command( ctx, "SU,57", 5 );

            return BLUETOOTH_OK;
        }
        case  115200:
        {
            bluetooth_write_command( ctx, "SU,11", 5  );

            return BLUETOOTH_OK;
        }
    }

    return BLUETOOTH_ERR;
}

void bluetooth_enable_bonding ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "SX,1", 4 );
}

void bluetooth_disable_bonding ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "SX,0", 4 );
}

void bluetooth_reboot ( bluetooth_t *ctx )
{ 
    bluetooth_write_command( ctx, "R,1", 3 );
}

BLUETOOTH_RETVAL bluetooth_set_profile ( bluetooth_t *ctx, uint8_t profile )
{
    uint8_t tx_buffer[ 20 ] = { "S~," };

    if ( profile > 6 )
    {
        return BLUETOOTH_ERR;
    }

    tx_buffer[ 3 ] = profile + 48;

    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );

    return BLUETOOTH_OK;
}

void bluetooth_enable_role_switch ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "S?,1", 4 );
}

void bluetooth_disable_role_switch ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "S?,0", 4 );
}

void bluetooth_connect_to_remote_address ( bluetooth_t *ctx, uint8_t *r_addr )
{
    uint8_t tx_buffer[ 20 ] = { "C," };

    strcat( tx_buffer, r_addr );
    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void bluetooth_connect_to_remote_address_fast_mode ( bluetooth_t *ctx, uint8_t *r_addr )
{
    uint8_t tx_buffer[ 20 ] = { "CF," };
    
    strcat( tx_buffer, r_addr );
    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );
}

void bluetooth_endspecial_config ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "F,1", 3 );
}


void bluetooth_get_help ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "H", 1 );
}

void bluetooth_get_basic_settings ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "D", 1 );
}

void bluetooth_get_extended_settings ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "E", 1 );
}

void bluetooth_get_device_address ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "GB", 2 );
}

void bluetooth_scans_device ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "IQ", 2 );
}

void bluetooth_get_signal_status ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "M", 1 );
}

void bluetooth_set_undiscoverable (  bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "Q,", 2 );
}

BLUETOOTH_RETVAL bluetooth_set_quiet_mode ( bluetooth_t *ctx, uint8_t q_mode )
{
    uint8_t tx_buffer[ 20 ] = { "Q," };

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
        return BLUETOOTH_ERR;
    }

    bluetooth_write_command( ctx, tx_buffer, strlen( tx_buffer ) );

    return BLUETOOTH_OK;
}


void bluetooth_get_firmware_version ( bluetooth_t *ctx )
{
    bluetooth_write_command( ctx, "V", 1 );
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

