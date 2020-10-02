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
static void int_to_hex_str ( uint16_t decimal, char *hexadecimal );

void delay_500_ms ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rn4678_cfg_setup ( rn4678_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

     cfg->sw_btn = HAL_PIN_NC;
     cfg->rst_n  = HAL_PIN_NC;
     cfg->rts    = HAL_PIN_NC;
     cfg->wkup   = HAL_PIN_NC;
     cfg->cts    = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
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

     digital_out_init( &ctx->sw_btn, cfg->sw_btn );
     digital_out_init( &ctx->rst_n, cfg->rst_n );
     digital_out_init( &ctx->rts, cfg->rts );
     digital_out_init( &ctx->wkup, cfg->wkup );

    // Input pins

     digital_in_init( &ctx->cts, cfg->cts );


    return RN4678_OK;
}


void rn4678_hw_reset ( rn4678_t *ctx )
{
    digital_out_low( &ctx->rst_n );
    Delay_100ms( );
    digital_out_high( &ctx->rst_n );
    Delay_100ms( );    
    Delay_100ms( );
}

void rn4678_uart_write ( rn4678_t *ctx, uint8_t *tx_data )
{
    uint16_t cnt;

    cnt = 0;

    while ( tx_data[ cnt ] != 0x00 )
    {
        uart_write( &ctx->uart, &tx_data[ cnt ], 1 );
        cnt++;
    }
}

void rn4678_initialize ( rn4678_t *ctx, char *dev_addr )
{
    rn4678_hw_reset( ctx );

    rn4678_uart_write( ctx, "$$$" );
    Delay_100ms();

    rn4678_uart_write( ctx, "$$$\r" );
    Delay_1sec();

    rn4678_uart_write( ctx, "SF,1\r" );
    Delay_1sec();
    Delay_1sec();

    rn4678_uart_write( ctx, "$$$" );
    Delay_100ms();

    rn4678_uart_write( ctx, "$$$\r" );
    Delay_1sec();

    rn4678_uart_write( ctx, "SW,0A,0A\r" );
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();

    rn4678_uart_write( ctx, "SW,0B,0B\r" );
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();

    rn4678_uart_write( ctx, "R,1\r" );
    Delay_1sec();
    Delay_1sec();

    rn4678_uart_write( ctx, "$$$" );
    Delay_100ms();

    rn4678_uart_write( ctx, "$$$\r" );
    Delay_1sec();

    rn4678_uart_write( ctx, "&," );
    rn4678_uart_write( ctx, dev_addr );

    rn4678_uart_write( ctx, "\r" );
    Delay_100ms();

    ctx->end_flag = 0;
    ctx->sen_flag = 0;
    ctx->tmp_pos = 0;
    memset( ctx->device_buffer, 0, 255 );
}

void rn4678_connect ( rn4678_t *ctx, char *dev_addr )
{
    rn4678_uart_write( ctx, "C,1," );
    rn4678_uart_write( ctx, dev_addr );
    rn4678_uart_write( ctx, "\r" );
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();

    rn4678_uart_write( ctx, "B\r" );
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

void rn4678_disconnect ( rn4678_t *ctx )
{
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();

    rn4678_uart_write( ctx, "$$$" );
    Delay_100ms();

    rn4678_uart_write( ctx, "$$$\r" );
    Delay_1sec();

    rn4678_uart_write( ctx, "K,1\r" );
    Delay_1sec();
}

void rn4678_send ( rn4678_t *ctx, uint8_t msg_type, uint16_t data_type, uint8_t dev_id, uint8_t *tx_data )
{
    char msg_text[ 255 ];
    uint8_t d_buff[ 2 ];

    d_buff[ 0 ] = ( uint8_t ) ( data_type >> 8 );
    d_buff[ 1 ] = ( uint8_t ) data_type;

    msg_text[ 0 ] = '#';
    msg_text[ 1 ] = msg_type;
    msg_text[ 2 ] = ',';
    msg_text[ 3 ] = d_buff[ 0 ];
    msg_text[ 4 ] = d_buff[ 1 ];
    msg_text[ 5 ] = ',';
    msg_text[ 6 ] = dev_id;
    msg_text[ 7 ] = ',';
    msg_text[ 8 ] = '\0';
    strcat( msg_text, tx_data );
    strcat( msg_text, "*\r\n" );

    rn4678_uart_write( ctx, msg_text );
}

void rn4678_receive ( rn4678_t *ctx, char character )
{
    if ( character == '#' )
    {
        ctx->end_flag = 0x01;
        return;
    }

    if ( character == '\r' && ctx->end_flag == 0x01 )
    {
        ctx->end_flag = 0xFF;
        return;
    }

    if ( character == '\n' && ctx->end_flag == 0xFF )
    {
        ctx->device_buffer[ ctx->tmp_pos ] = '\0';
        ctx->tmp_pos = 0;

        ctx->end_flag = 0x00;
        ctx->sen_flag = 1;
        return;
    }

    if ( ctx->end_flag == 0x01 )
    {
        ctx->device_buffer[ ctx->tmp_pos ] = character;
        ctx->tmp_pos++;
        return;
    }
}

uint8_t rn4678_read ( rn4678_t *ctx, uint8_t *rx_data )
{
    uint8_t cnt;

    if ( ctx->sen_flag )
    {
        for ( cnt = 0; cnt <= 255; cnt++ )
        {
            if ( ctx->device_buffer[ cnt ] == '*' )
            {
                ctx->device_buffer[ cnt ] = 0;
                break;
            }
        }

        strcpy( rx_data, ctx->device_buffer );
        ctx->sen_flag = 0;

        return 1;
    }
    else
    {
        return 0;
    }
}

RN4678_STATUS_T rn4678_set_authentication ( rn4678_t *ctx, uint8_t auth_value )
{
    uint8_t tmp;
    uint8_t tx_buffer[ 20 ] = { "SA," };
    uint8_t buff[ 5 ];

    if ( auth_value > 4 || auth_value < 1 )
    {
        return RN4678_ERR;
    }

    buff[ 0 ] = auth_value + 48;

    strcat( tx_buffer, buff );
    rn4678_uart_write( ctx, tx_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_cod ( rn4678_t *ctx, uint8_t *msw, uint8_t *lsw )
{
    uint8_t tmp;
    uint8_t *msw_ptr = msw;
    uint8_t *lsw_ptr = lsw;
    uint8_t tx_buffer_c[ 20 ] = { "SC," };
    uint8_t tx_buffer_d[ 20 ] = { "SD," };

    if( strlen( msw ) > 4 || strlen( lsw ) > 4 )
    {
        return RN4678_ERR;
    }

    memset( ctx->device_buffer, 0, 255 );
    strcat( tx_buffer_c, msw );
    rn4678_uart_write( ctx, tx_buffer_c );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );
    delay_500_ms();

    strcat( tx_buffer_d, lsw );
    rn4678_uart_write( ctx, tx_buffer_d );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );
    delay_500_ms();

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_model_string ( rn4678_t *ctx, uint8_t *model_string )
{
    uint8_t tmp;
    uint8_t tx_buffer[ 22 ] = { "SDM," };
    uint8_t buff[ 5 ];

    if ( strlen( model_string ) > 16 )
    {
        return RN4678_ERR;
    }

    strcat( tx_buffer, model_string );
    rn4678_uart_write( ctx, tx_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_manufacturer_string ( rn4678_t *ctx, uint8_t *manufacturer_string )
{
    uint8_t tmp;
    uint8_t tx_buffer[ 22 ] = { "SDN," };
    uint8_t buff[ 5 ];

    if ( strlen( manufacturer_string ) > 16 )
    {
        return RN4678_ERR;
    }

    strcat( tx_buffer, manufacturer_string );
    rn4678_uart_write( ctx, tx_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_software_revision ( rn4678_t *ctx, uint8_t *software_revision )
{
    uint8_t tmp;
    uint8_t tx_buffer[ 22 ] = { "SDR," };
    uint8_t buff[ 5 ];

    if ( strlen( software_revision ) > 10 )
    {
        return RN4678_ERR;
    }

    strcat( tx_buffer, software_revision );
    rn4678_uart_write( ctx, tx_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_serial_number ( rn4678_t *ctx, uint8_t *serial_number )
{
    uint8_t tmp;
    uint8_t tx_buffer[ 22 ] = { "SDS," };
    uint8_t buff[ 5 ];

    if ( strlen( serial_number ) > 16 )
    {
        return RN4678_ERR;
    }

    strcat( tx_buffer, serial_number );
    rn4678_uart_write( ctx, tx_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_unique_identifier ( rn4678_t *ctx, uint8_t *unique_identifier )
{
    uint8_t tmp;
    uint8_t tx_buffer[ 22 ] = { "SE," };
    uint8_t buff[ 5 ];

    if ( strlen( unique_identifier ) > 16 )
    {
        return RN4678_ERR;
    }

    strcat( tx_buffer, unique_identifier );
    rn4678_uart_write( ctx, tx_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_factory_defaults ( rn4678_t *ctx )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "SF,1" };

    memset( ctx->device_buffer, 0, 255 );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_bluetooth_modes ( rn4678_t *ctx, uint8_t modes )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "SG," };
    uint8_t buff[ 5 ];

    if ( modes > 2 )
    {
        return RN4678_ERR;
    }
    
    buff[ 0 ] = modes + 48;

    memset( ctx->device_buffer, 0, 255 );
    strcat( tmp_buffer, buff );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_enable_low_power_mode ( rn4678_t *ctx, uint8_t clock_idle )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "SH," };
    uint8_t buff[ 5 ];
    
    if ( clock_idle > 1 )
    {
        return RN4678_ERR;
    }

    buff[ 0 ] = clock_idle + 48;

    memset( ctx->device_buffer, 0, 255 );
    strcat( tmp_buffer, buff );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_discoverability ( rn4678_t *ctx, uint16_t time )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "SI," };
    uint8_t buff[ 5 ];

    int_to_hex_str( time, &buff );
    memset( ctx->device_buffer, 0, 255 );
    strcat( tmp_buffer, buff );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_device_name ( rn4678_t *ctx, uint8_t *name )
{
    uint8_t tmp;
    uint8_t *name_ptr = name;
    uint8_t tx_buffer[ 25 ] = { "SN," };

    if( strlen( name ) > 16 )
    {
        return RN4678_ERR;
    }

    memset( ctx->device_buffer, 0, 255 );
    strcat( tx_buffer, name_ptr );
    rn4678_uart_write( ctx, tx_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_security_pin_code ( rn4678_t *ctx, uint8_t *sp_code )
{
    uint8_t tmp;
    uint8_t *sp_code_ptr = sp_code;
    uint8_t tmp_buffer[ 20 ] = { "SP," };

    if ( strlen( sp_code ) != 4 || strlen( sp_code ) != 6 )
    {
        return RN4678_ERR;
    }

    memset( ctx->device_buffer, 0, 255 );
    strcat( tmp_buffer, sp_code_ptr );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_remote_address ( rn4678_t *ctx, uint8_t *r_addr )
{
    uint8_t tmp;
    uint8_t *r_addr_ptr = r_addr;
    uint8_t tmp_buffer[ 20 ] = { "SR," };

    memset( ctx->device_buffer, 0, 255 );
    strcat( tmp_buffer, r_addr_ptr );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_remote_ble_address ( rn4678_t *ctx, uint8_t *r_addr )
{
    uint8_t tmp;
    uint8_t *r_addr_ptr = r_addr;
    uint8_t tmp_buffer[ 20 ] = { "SR,0," };

    memset( ctx->device_buffer, 0, 255 );
    strcat( tmp_buffer, r_addr_ptr );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_clear_stored_address ( rn4678_t *ctx )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "SR,Z" };

    memset( ctx->device_buffer, 0, 255 );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_service_name ( rn4678_t *ctx, uint8_t *service_name )
{
    uint8_t tmp;
    uint8_t *service_name_ptr = service_name;
    uint8_t tmp_buffer[ 20 ] = { "SS," };

    if ( strlen( service_name ) < 1 || strlen( service_name ) > 16 )
    {
        return RN4678_ERR;
    }

    memset( ctx->device_buffer, 0, 255 );
    strcat( tmp_buffer, service_name_ptr );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_baud_rate ( rn4678_t *ctx, uint32_t b_rate )
{
    uint8_t tmp;
    switch ( b_rate )
    {
        case  2400:
        {
            rn4678_uart_write( ctx, "SU,0B" );
            tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

            return RN4678_OK;
            break;
        }
        case  4800:
        {
            rn4678_uart_write( ctx, "SU,0A" );
            tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

            return RN4678_OK;
            break;
        }
        case  9600:
        {
            rn4678_uart_write( ctx, "SU,09" );
            tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

            return RN4678_OK;
            break;
        }
        case  14400:
        {
            rn4678_uart_write( ctx, "SU,08" );
            tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

            return RN4678_OK;
            break;
        }
        case  19200:
        {
            rn4678_uart_write( ctx, "SU,07" );
            tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

            return RN4678_OK;
            break;
        }
        case  38400:
        {
            rn4678_uart_write( ctx, "SU,05" );
            tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

            return RN4678_OK;
            break;
        }
        case  57600:
        {
            rn4678_uart_write( ctx, "SU,04" );
            tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

            return RN4678_OK;
            break;
        }
        case  115200:
        {
            rn4678_uart_write( ctx, "SU,03" );
            tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

            return RN4678_OK;
            break;
        }
    }

    return RN4678_ERR;
}

RN4678_STATUS_T rn4678_enable_beacon ( rn4678_t *ctx )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "SZ,1" };

    memset( ctx->device_buffer, 0, 255 );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_disable_beacon ( rn4678_t *ctx )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "SZ,0" };

    memset( ctx->device_buffer, 0, 255 );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_friendly_device_name ( rn4678_t *ctx, uint8_t *name )
{
    uint8_t tmp;
    uint8_t *name_ptr = name;
    uint8_t tx_buffer[ 20 ] = { "S-," };

    if( strlen( name ) > 11 )
    {
        return RN4678_ERR;
    }

    memset( ctx->device_buffer, 0, 255 );
    strcat( tx_buffer, name_ptr );
    rn4678_uart_write( ctx, tx_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_enable_role_switch ( rn4678_t *ctx )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "S?,1" };

    memset( ctx->device_buffer, 0, 255 );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_disable_role_switch ( rn4678_t *ctx )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "S?,0" };

    memset( ctx->device_buffer, 0, 255 );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_set_configuration ( rn4678_t *ctx, uint8_t *dc_string )
{
    uint8_t tmp;
    uint8_t *dc_string_ptr = dc_string;
    uint8_t tx_buffer[ 20 ] = { "S$," };

    if( strlen( dc_string ) > 10 )
    {
        return RN4678_ERR;
    }

    memset( ctx->device_buffer, 0, 255 );
    strcat( tx_buffer, dc_string_ptr );
    rn4678_uart_write( ctx, tx_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_get_basic_settings ( rn4678_t *ctx, uint8_t *response )
{
    uint8_t data_tmp;
    uint8_t tmp[ 30 ] = { 0 };
    uint8_t cnt;

    memset( ctx->device_buffer, 0, 255 );

    rn4678_uart_write( ctx, "D" );
    data_tmp = 13;
    uart_write( &ctx->uart, &data_tmp, 1 );

    cnt = 0;

    while ( cnt > 30 )
    {
        uart_read( &ctx->uart, &tmp[ cnt ], 1 );
        cnt++;
    }

    strcpy( response, tmp );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_get_device_address ( rn4678_t *ctx, uint8_t *response )
{
    uint8_t tmp_data;
    uint8_t tmp[ 30 ] = { 0 };
    uint8_t cnt;

    memset( ctx->device_buffer, 0, 255 );

    rn4678_uart_write( ctx, "GB" );
    tmp_data = 13;
    uart_write( &ctx->uart, &tmp_data, 1 );

    cnt = 0;

    while ( cnt > 30 )
    {
        uart_read( &ctx->uart, &tmp[ cnt ], 1 );
        cnt++;
    }

    strcpy( response, tmp );

    return RN4678_OK;
}

uint8_t rn4678_get_device_status ( rn4678_t *ctx )
{
    uint8_t tmp;

    memset( ctx->device_buffer, 0, 255 );

    rn4678_uart_write( ctx, "GK" );

    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    uart_read( &ctx->uart, &tmp, 1 );

    return tmp;
}

RN4678_STATUS_T rn4678_enter_commandmode ( rn4678_t *ctx )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "$$$" };

    memset( ctx->device_buffer, 0, 255 );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

RN4678_STATUS_T rn4678_exit_commandmode( rn4678_t *ctx )
{
    uint8_t tmp;
    uint8_t tmp_buffer[ 20 ] = { "---" };

    memset( ctx->device_buffer, 0, 255 );
    rn4678_uart_write( ctx, tmp_buffer );
    tmp = 13;
    uart_write( &ctx->uart, &tmp, 1 );

    return RN4678_OK;
}

uint8_t rn4678_get_interrupt ( rn4678_t *ctx )
{
    return digital_in_read( &ctx->cts );
}

void rn4678_set_rst ( rn4678_t *ctx )
{
    digital_out_high( &ctx->rst_n );
}

void rn4678_clear_rst ( rn4678_t *ctx )
{
    digital_out_low( &ctx->rst_n );
}

void rn4678_set_rts ( rn4678_t *ctx )
{
    digital_out_high( &ctx->rts );
}

void rn4678_clear_rts ( rn4678_t *ctx )
{
    digital_out_low( &ctx->rts );
}

void rn4678_set_pwm ( rn4678_t *ctx )
{
    digital_out_high( &ctx->wkup );
}

void rn4678_clear_pwm ( rn4678_t *ctx )
{
    digital_out_low( &ctx->wkup );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void int_to_hex_str ( uint16_t decimal, char *hexadecimal )
{
    uint16_t remainder;
    uint16_t quotient;
    uint8_t i;
    
    i = 0;

    quotient = decimal;

    while ( quotient != 0 )
    {
        remainder = quotient % 16;
    
        if ( remainder < 10 )
        {
            hexadecimal[ i++ ] = 48 + remainder;
        }
        else
        {
            hexadecimal[ i++ ] = 55 + remainder;
            quotient = quotient / 16;
        }
    }
}

void delay_500_ms ( )
{
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
}

// ------------------------------------------------------------------------- END

