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

static void clear_buffer( bluetooth_t *ctx );

void delay500ms( );

void delay5sec( );

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
    cfg->uart_blocking  = true;
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
    
    ctx->response_finished = 0;
    ctx->bt_state          = 0;
    ctx->response_id       = 0;
    ctx->response          = 0;
    ctx->buffer_cnt        = 0;
    ctx->getting_settings  = 0;

    return BLUETOOTH_OK;

}

void bluetooth_generic_write ( bluetooth_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int16_t bluetooth_generic_read ( bluetooth_t *ctx, char *data_buf, uint16_t max_len )
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

uint8_t bluetooth_get_response ( bluetooth_t *ctx )
{
    if ( ctx->response_finished )
    {
        ctx->response_finished = 0;
        return ctx->response_id;
    }
    else
    {
        return 0;
    }
}

void bluetooth_rx_isr ( bluetooth_t *ctx, char character )
{
    ctx->driver_buffer[ ctx->buffer_cnt++ ] = character;

    if( character == 13 )
    {
        ctx->response_finished = 1;

        if( !ctx->getting_settings )
        {
            ctx->driver_buffer[ --ctx->buffer_cnt ] = 0;
        }
    }
}

BLUETOOTH_RETVAL bluetooth_enter_command_mode ( bluetooth_t *ctx )
{
    uint8_t input = 36;

    bluetooth_generic_write( ctx, &input, 1 );
    bluetooth_generic_write( ctx, &input, 1 );
    bluetooth_generic_write( ctx, &input, 1 );
    
    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_exit_command_mode ( bluetooth_t *ctx )
{
    uint8_t input = 45;

    bluetooth_generic_write( ctx, &input, 1 );
    bluetooth_generic_write( ctx, &input, 1 );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_toggles_echo ( bluetooth_t *ctx, uint8_t t_echo )
{
    uint8_t input;

    if ( t_echo == 0 )
    {
        input = 45;
        bluetooth_generic_write( ctx, &input, 1 );
    }
    else if ( t_echo == 1 )
    {
        input = 43;
        bluetooth_generic_write( ctx, &input, 1 );
    }
    else
    {
        return BLUETOOTH_ERR;
    }

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_device_name ( bluetooth_t *ctx, uint8_t *name )
{
    uint8_t input = 13;
    uint8_t *name_ptr = name;
    uint8_t tx_buffer[ 20 ] = { "SN," };
    
    if( strlen( name ) > 20 )
    {
        return BLUETOOTH_ERR;
    }
    
    clear_buffer( ctx );
    strcat( tx_buffer, name_ptr );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_operating_mode ( bluetooth_t *ctx, uint8_t op_mode )
{
    uint8_t input = 13;
    uint8_t tx_buffer[ 20 ] = { "SM," };
    uint8_t buff[ 5 ];
    
    if ( op_mode > 6 )
    {
        return BLUETOOTH_ERR;
    }
    
    buff[ 0 ] = op_mode + 48;

    clear_buffer( ctx );
    strcat( tx_buffer, buff );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_enable_7_bit_data_mode ( bluetooth_t *ctx )
{
    uint8_t input = 13;
    uint8_t tx_buffer[ 20 ] = { "S7,1" };

    clear_buffer( ctx );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_disable_7_bit_data_mode ( bluetooth_t *ctx )
{
    uint8_t input = 13;
    uint8_t tx_buffer[ 20 ] = { "S7,0" };

    clear_buffer( ctx );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_set_authentication ( bluetooth_t *ctx, uint8_t auth_value )
{
    uint8_t input = 13;
    uint8_t tx_buffer[ 20 ] = { "SA," };
    uint8_t buff[ 5 ];

    if ( auth_value > 4 || auth_value == 3 )
    {
        return BLUETOOTH_ERR;
    }

    buff[ 0 ] = auth_value + 48;

    strcat( tx_buffer, buff );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_break ( bluetooth_t *ctx, uint8_t break_signal )
{
    uint8_t input = 13;
    uint8_t tx_buffer[ 20 ] = { "SB," };
    uint8_t buff[ 5 ];

    if ( break_signal < 1 || break_signal > 6 )
    {
        return BLUETOOTH_ERR;
    }

    buff[ 0 ] = break_signal + 48;

    clear_buffer( ctx );
    strcat( tx_buffer, buff );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_cod ( bluetooth_t *ctx, uint8_t *msw, uint8_t *lsw )
{
    uint8_t input = 13;
    uint8_t *msw_ptr = msw;
    uint8_t *lsw_ptr = lsw;
    uint8_t tx_buffer_c[ 20 ] = { "SC," };
    uint8_t tx_buffer_d[ 20 ] = { "SD," };

    if( strlen( msw ) > 4 || strlen( lsw ) > 4 )
    {
        return BLUETOOTH_ERR;
    }

    clear_buffer( ctx );
    strcat( tx_buffer_c, msw );
    bluetooth_generic_write( ctx, tx_buffer_c, strlen( tx_buffer_c ) );
    bluetooth_generic_write( ctx, &input, 1 );
    delay500ms( );

    while( !ctx->response_finished );
    
    strcat( tx_buffer_d, lsw );
    bluetooth_generic_write( ctx, tx_buffer_d, strlen( tx_buffer_d ) );
    bluetooth_generic_write( ctx, &input, 1 );
    delay500ms( );

    while( !ctx->response_finished );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_factory_defaults ( bluetooth_t *ctx )
{
    uint8_t input = 13;
    uint8_t tmp_buffer[ 20 ] = { "SF,1" };

    clear_buffer( ctx );
    bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_discoverability ( bluetooth_t *ctx, uint8_t *d_hex_value )
{
    uint8_t input = 13;
    uint8_t *d_hex_value_ptr = d_hex_value;
    uint8_t tmp_buffer[ 20 ] = { "SI," };

    clear_buffer( ctx );
    strcat( tmp_buffer, d_hex_value_ptr );
    bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL  bluetooth_setConnectability ( bluetooth_t *ctx, uint8_t *c_hex_value )
{
    uint8_t input = 13;
    uint8_t *c_hex_value_ptr = c_hex_value;
    uint8_t tmp_buffer[ 20 ] = { "SJ," };

    clear_buffer( ctx );
    strcat( tmp_buffer, c_hex_value_ptr );
    bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    while( !ctx->response_finished );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_uart_parity ( bluetooth_t *ctx, uint8_t character )
{
    uint8_t input;
    uint8_t tmp_buffer[ 20 ] = { "SL," };
    
    clear_buffer( ctx );
    
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
            break;
        }
        case  'O':
        {
            bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
            input = 79;
            bluetooth_generic_write( ctx, &input, 1 );
            input = 13;
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  'N':
        {
            bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
            input = 78;
            bluetooth_generic_write( ctx, &input, 1 );
            input = 13;
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
    }

    return BLUETOOTH_ERR;
}

BLUETOOTH_RETVAL bluetooth_set_extended_status_string ( bluetooth_t *ctx, uint8_t *es_string )
{
    uint8_t input = 13;
    uint8_t *es_string_ptr = es_string;
    uint8_t tmp_buffer[ 20 ] = { "SO," };
    
    if ( strlen( es_string ) > 8 )
    {
        return BLUETOOTH_ERR;
    }

    clear_buffer( ctx );
    strcat( tmp_buffer, es_string_ptr );
    bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_set_security_pin_code ( bluetooth_t *ctx, uint8_t *sp_code )
{
    uint8_t input = 13;
    uint8_t *sp_code_ptr = sp_code;
    uint8_t tmp_buffer[ 20 ] = { "SP," };
    
    if ( strlen( sp_code ) > 20 )
    {
        return BLUETOOTH_ERR;
    }

    clear_buffer( ctx );
    strcat( tmp_buffer, sp_code_ptr );
    bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_special_config ( bluetooth_t *ctx, uint16_t special_config )
{
    uint8_t input = 13;

    switch ( special_config )
    {
        case  0:
        {
            bluetooth_generic_write( ctx, "SQ,0", 4 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  4:
        {
            bluetooth_generic_write( ctx, "SQ,4", 4 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  8:
        {
            bluetooth_generic_write( ctx, "SQ,8", 4 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  16:
        {
            bluetooth_generic_write( ctx, "SQ,16", 5 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  128:
        {
            bluetooth_generic_write( ctx, "SQ,128", 6 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  256:
        {
            bluetooth_generic_write( ctx, "SQ,256", 6 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
    }

    return BLUETOOTH_ERR;
}

BLUETOOTH_RETVAL bluetooth_set_remote_address ( bluetooth_t *ctx, uint8_t *r_addr )
{
    uint8_t input = 13;
    uint8_t *r_addr_ptr = r_addr;
    uint8_t tmp_buffer[ 20 ] = { "SR," };

    clear_buffer( ctx );
    strcat( tmp_buffer, r_addr_ptr );
    bluetooth_generic_write( ctx, tmp_buffer, strlen( tmp_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_baud_rate ( bluetooth_t *ctx, uint32_t baud_rate )
{
    uint8_t input = 13;

    switch ( baud_rate )
    {
        case  1200:
        {
            bluetooth_generic_write( ctx, "SU,12", 5 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  2400:
        {
            bluetooth_generic_write( ctx, "SU,24", 5 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  9600:
        {
            bluetooth_generic_write( ctx, "SU,96", 5 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  19200:
        {
            bluetooth_generic_write( ctx, "SU,19", 5 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  38400:
        {
            bluetooth_generic_write( ctx, "SU,38", 5 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  57600:
        {
            bluetooth_generic_write( ctx, "SU,57", 5 );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
        case  115200:
        {
            bluetooth_generic_write( ctx, "SU,11", 5  );
            bluetooth_generic_write( ctx, &input, 1 );

            return BLUETOOTH_OK;
            break;
        }
    }

    return BLUETOOTH_ERR;
}

BLUETOOTH_RETVAL bluetooth_enable_bonding ( bluetooth_t *ctx )
{
    uint8_t input = 13;

    clear_buffer( ctx );
    bluetooth_generic_write( ctx, "SX,1", 4 );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_disable_bonding ( bluetooth_t *ctx )
{
    uint8_t input = 13;

    clear_buffer( ctx );
    bluetooth_generic_write( ctx, "SX,0", 4 );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_reboot ( bluetooth_t *ctx )
{ 
    uint8_t input = 13;
    
    clear_buffer( ctx );
    bluetooth_generic_write( ctx, "R,1", 3 );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_set_profile ( bluetooth_t *ctx, uint8_t profile )
{
    uint8_t input = 13;
    uint8_t tx_buffer[ 20 ] = { "S~," };
    uint8_t buff[ 5 ];

    if ( profile > 6 )
    {
        return BLUETOOTH_ERR;
    }

    buff[ 0 ] = profile + 48;

    clear_buffer( ctx );
    strcat( tx_buffer, buff );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_enable_role_switch ( bluetooth_t *ctx )
{
    uint8_t input = 13;
    clear_buffer( ctx );
    bluetooth_generic_write( ctx, "S?,1", 4 );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_disable_role_switch ( bluetooth_t *ctx )
{
    uint8_t input = 13;
    clear_buffer( ctx );
    bluetooth_generic_write( ctx, "S?,0", 4 );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_connect_to_remote_address ( bluetooth_t *ctx, uint8_t *r_addr )
{
    uint8_t input = 13;
    uint8_t *r_addr_ptr = r_addr;
    uint8_t tx_buffer[ 20 ] = { "C," };

    clear_buffer( ctx );
    strcat( tx_buffer, r_addr_ptr );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_connect_to_remote_address_fast_mode ( bluetooth_t *ctx, uint8_t *r_addr )
{
    uint8_t input = 13;
    uint8_t *r_addr_ptr = r_addr;
    uint8_t tx_buffer[ 20 ] = { "CF," };

    clear_buffer( ctx );
    strcat( tx_buffer, r_addr_ptr );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_endspecial_config ( bluetooth_t *ctx )
{
    uint8_t input = 13;
    clear_buffer( ctx );
    bluetooth_generic_write( ctx, "F,1", 3 );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_get_help ( bluetooth_t *ctx, uint8_t *response )
{
    uint8_t input = 13;
    uint8_t *tmp_ptr = response;
    uint8_t tmp[ 15 ] = { 0 };
    uint8_t cnt;

    ctx->getting_settings = 1;

    clear_buffer( ctx );

    bluetooth_generic_write( ctx, "H", 1 );
    bluetooth_generic_write( ctx, &input, 1 );

    for( cnt = 0; cnt < 30; cnt++ )
    {
        while( !ctx->response_finished );

        ctx->response_finished = 0;
    }

    strcpy( tmp_ptr, ctx->driver_buffer );
    ctx->getting_settings = 0;
    
    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_get_basic_settings ( bluetooth_t *ctx, uint8_t *response )
{
    uint8_t input = 13;
    uint8_t *tmp_ptr = response;
    uint8_t tmp[ 15 ] = { 0 };
    uint8_t cnt;

    ctx->getting_settings = 1;

    clear_buffer( ctx );

    bluetooth_generic_write( ctx, "D", 1 );
    bluetooth_generic_write( ctx, &input, 1 );

    for( cnt = 0; cnt < 30; cnt++ )
    {
        while( !ctx->response_finished );

        ctx->response_finished = 0;
    }

    strcpy( tmp_ptr, ctx->driver_buffer );
    ctx->getting_settings = 0;
    
    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_get_extended_settings ( bluetooth_t *ctx, uint8_t *response )
{
    uint8_t input = 13;
    uint8_t *tmp_ptr = response;
    uint8_t tmp[ 15 ] = { 0 };
    uint8_t cnt;

    ctx->getting_settings = 1;

    clear_buffer( ctx );

    bluetooth_generic_write( ctx, "E", 1 );
    bluetooth_generic_write( ctx, &input, 1 );

    for( cnt = 0; cnt < 30; cnt++ )
    {
        while( !ctx->response_finished );

        ctx->response_finished = 0;
    }

    strcpy( tmp_ptr, ctx->driver_buffer );
    ctx->getting_settings = 0;
    
    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_get_device_address ( bluetooth_t *ctx, uint8_t *response )
{
    uint8_t input = 13;
    uint8_t *tmp_ptr = response;
    uint8_t tmp[ 15 ] = { 0 };
    uint8_t cnt;

    ctx->getting_settings = 1;

    clear_buffer( ctx );

    bluetooth_generic_write( ctx, "GB", 2 );
    bluetooth_generic_write( ctx, &input, 1 );

    for( cnt = 0; cnt < 30; cnt++ )
    {
        while( !ctx->response_finished );

        ctx->response_finished = 0;
    }

    strcpy( tmp_ptr, ctx->driver_buffer );
    ctx->getting_settings = 0;
    
    return BLUETOOTH_OK;
}


void bluetooth_scans_device ( bluetooth_t *ctx, uint8_t *response )
{
    uint8_t input = 13;
    uint8_t *tmp_ptr = response;
    uint8_t tmp[ 15 ] = { 0 };
    uint8_t cnt;

    ctx->getting_settings = 1;

    clear_buffer( ctx );

    bluetooth_generic_write( ctx, "IQ", 2 );
    bluetooth_generic_write( ctx, &input, 1 );

    for( cnt = 0; cnt < 30; cnt++ )
    {
        while( !ctx->response_finished );

        ctx->response_finished = 0;
    }

    strcpy( tmp_ptr, ctx->driver_buffer );
    ctx->getting_settings = 0;
}


void bluetooth_get_signal_status ( bluetooth_t *ctx, uint8_t *response )
{
    uint8_t input = 13;
    uint8_t *tmp_ptr = response;
    uint8_t tmp[ 15 ] = { 0 };
    uint8_t cnt;

    ctx->getting_settings = 1;

    clear_buffer( ctx );

    bluetooth_generic_write( ctx, "M", 1 );
    bluetooth_generic_write( ctx, &input, 1 );

    for( cnt = 0; cnt < 30; cnt++ )
    {
        while( !ctx->response_finished );

        ctx->response_finished = 0;
    }

    strcpy( tmp_ptr, ctx->driver_buffer );
    ctx->getting_settings = 0;
}


BLUETOOTH_RETVAL bluetooth_set_undiscoverable (  bluetooth_t *ctx )
{
    uint8_t input = 13;
    clear_buffer( ctx );
    bluetooth_generic_write( ctx, "Q,", 2 );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}

BLUETOOTH_RETVAL bluetooth_set_quiet_mode ( bluetooth_t *ctx, uint8_t q_mode )
{
    uint8_t input = 13;
    uint8_t tx_buffer[ 20 ] = { "Q," };
    uint8_t buff[ 5 ];

    if ( q_mode == 0 || q_mode == 1 || q_mode == 2 )
    {
        buff[ 0 ] = q_mode + 48;
    }
    else if ( q_mode == 3 )
    {
        buff[ 0 ] = 63;
    }
    else
    {
        return BLUETOOTH_ERR;
    }

    clear_buffer( ctx );
    strcat( tx_buffer, buff );
    bluetooth_generic_write( ctx, tx_buffer, strlen( tx_buffer ) );
    bluetooth_generic_write( ctx, &input, 1 );

    return BLUETOOTH_OK;
}


BLUETOOTH_RETVAL bluetooth_get_firmware_version ( bluetooth_t *ctx, uint8_t *firmware_version )
{
    uint8_t input = 13;
    uint8_t *tmp_ptr = firmware_version;
    uint8_t tmp[ 15 ] = { 0 };
    uint8_t cnt;

    ctx->getting_settings = 1;

    clear_buffer( ctx );

    bluetooth_generic_write( ctx, "V", 1 );
    bluetooth_generic_write( ctx, &input, 1 );

    for( cnt = 0; cnt < 30; cnt++ )
    {
        while( !ctx->response_finished );

        ctx->response_finished = 0;
    }

    strcpy( tmp_ptr, ctx->driver_buffer );
    ctx->getting_settings = 0;

    return BLUETOOTH_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void clear_buffer( bluetooth_t *ctx )
{
    memset( ctx->driver_buffer, 0, 255 );
    ctx->response_finished = 0;
}

void delay500ms()
{
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
}

void delay5sec()
{
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

// ------------------------------------------------------------------------- END

