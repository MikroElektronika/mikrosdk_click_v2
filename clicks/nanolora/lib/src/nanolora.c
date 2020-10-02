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

#include "nanolora.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t nanolora_checksum_calc ( uint16_t pckg_len, uint8_t *pckg_payload );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void nanolora_cfg_setup ( nanolora_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->st  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;

    cfg->rsp_len_cfg = 0;
}

NANOLORA_RETVAL nanolora_init ( nanolora_t *ctx, nanolora_cfg_t *cfg )
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

     digital_out_init( &ctx->st, cfg->st );
     digital_out_init( &ctx->rst, cfg->rst );
     digital_out_init( &ctx->cts, cfg->cts );

    // Input pins

     digital_in_init( &ctx->gp1, cfg->gp1 );
     digital_in_init( &ctx->rts, cfg->rts );

     ctx->rsp_len = cfg->rsp_len_cfg;
    

    return NANOLORA_OK;
}

void nanolora_default_cfg ( nanolora_t *ctx )
{
    nanolora_set_st_pin( ctx, 0 );
    nanolora_reset( ctx );

    nanolora_network_stop( ctx );
    Delay_100ms( );

    nanolora_save_energy_always_on( ctx );
    Delay_100ms( );

    nanolora_network_start( ctx );
    Delay_100ms( );
}

void nanolora_reset ( nanolora_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

void nanolora_generic_write ( nanolora_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

uint16_t nanolora_generic_read ( nanolora_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t nanolora_request_2_send ( nanolora_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->rts );

    return state;
}

void nanolora_clear_2_send ( nanolora_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->cts, state );
}

uint8_t nanolora_get_gp1_pin ( nanolora_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->gp1 );

    return state;
}

void nanolora_set_st_pin ( nanolora_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->st, state );
}

void nanolora_send_command ( nanolora_t *ctx, char *command )
{
    char tmp_buf[ 100 ];
    uint8_t len;
    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );
    strcat( tmp_buf, "\r" );

    nanolora_generic_write( ctx, tmp_buf, strlen( tmp_buf ) );
}

void nanolora_get_device_info ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x01, 0x05 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_get_device_state ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x04, 0x08 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_sw_reset ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x05, 0x09 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_get_fw_ver ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x06, 0x0A };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_restore_2_factory ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x07, 0x0B };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_save_settings ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x08, 0x0C };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_get_output_power ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x10, 0x14 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_get_operating_channel ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x11, 0x15 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_set_output_power ( nanolora_t *ctx, uint8_t out_pwr )
{
    uint8_t data_buff[ 3 ] = { 0x00, 0x05, 0x10 };

    if ( ( out_pwr > 1 ) && ( out_pwr < 20 ) )
    {
        nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );   
        nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );   
        nanolora_generic_write( ctx, &data_buff[ 2 ], 1 ); 
        nanolora_generic_write( ctx, &out_pwr, 1 );

        out_pwr += 0x15;

        nanolora_generic_write( ctx, &out_pwr, 1 );
    }
}

void nanolora_set_operating_channel ( nanolora_t *ctx, nanolora_network_t *net )
{
    uint8_t data_buff[ 3 ] = { 0x00, 0x08, 0x11 };
    uint8_t combine = 0x19 + net->channel + net->spreading_factor +
                      net->bandwidth + net->coding_rate;

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );

    nanolora_generic_write( ctx, &net->channel, 1 );
    nanolora_generic_write( ctx, &net->spreading_factor, 1 );
    nanolora_generic_write( ctx, &net->bandwidth, 1 );
    nanolora_generic_write( ctx, &net->coding_rate, 1 );

    nanolora_generic_write( ctx, &combine, 1 );
}

void nanolora_save_energy_always_on ( nanolora_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x13, 0x00, 0x18 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 4 ], 1 );
}

void nanolora_save_energy_rx_window ( nanolora_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x13, 0x01, 0x19 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 4 ], 1 );
}

void nanolora_save_energy_tx_only ( nanolora_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x13, 0x02, 0x1A };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 4 ], 1 );
}

void nanolora_get_physical_address ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x20, 0x24 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_set_physical_address ( nanolora_t *ctx, uint8_t *app_eui, uint8_t *dev_eui )
{
    uint8_t data_buff[ 3 ] = { 0x00, 0x14, 0x20 };
    uint16_t check_sum_tmp;
    uint8_t check_sum;
    uint8_t cnt;

    check_sum_tmp = 0x24;

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );

    for ( cnt = 0; cnt < 8; cnt++ )
    {
        nanolora_generic_write( ctx, &app_eui[ cnt ], 1 );
        nanolora_generic_write( ctx, &dev_eui[ cnt ], 1 );
        check_sum_tmp += app_eui[ cnt ];
        check_sum_tmp += dev_eui[ cnt ];
    }

    check_sum = ( uint8_t ) check_sum_tmp;

    nanolora_generic_write( ctx, &check_sum, 1 );
}

void nanolora_get_network_address ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x21, 0x25 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_set_network_address ( nanolora_t *ctx, uint16_t ntw_addr )
{
    uint8_t data_buff[ 3 ] = { 0x00, 0x06, 0x21 };
    uint8_t buf[ 2 ];
    uint8_t combine;

    buf[ 0 ] = ( uint8_t ) ( ntw_addr >> 8 );
    buf[ 1 ] = ( uint8_t ) ntw_addr;
    combine = 0x27 + buf[ 0 ] + buf[ 1 ];

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &buf[ 0 ], 1 );
    nanolora_generic_write( ctx, &buf[ 1 ], 1 );
    nanolora_generic_write( ctx, &combine, 1 );
}

void nanolora_get_network_id ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x22, 0x26 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_set_network_id ( nanolora_t *ctx, uint16_t ntw_id )
{
    uint8_t data_buff[ 3 ] = { 0x00, 0x06, 0x22 };
    uint8_t buf[ 2 ];
    uint8_t combine;

    buf[ 0 ] = ( uint8_t ) ( ntw_id >> 8 );
    buf[ 1 ] = ( uint8_t ) ntw_id;
    combine = 0x28 + buf[ 0 ] + buf[ 1 ];

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &buf[ 0 ], 1 );
    nanolora_generic_write( ctx, &buf[ 1 ], 1 );
    nanolora_generic_write( ctx, &combine, 1 );
}

void nanolora_get_network_role ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x23, 0x27 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_set_network_role ( nanolora_t *ctx, uint8_t ntw_role )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x23, 0x28, 0x2A };
    uint8_t temp;

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );

    if ( ntw_role == NANOLORA_NTW_ROLE_COORDINATOR )
    {
        temp = NANOLORA_NTW_ROLE_COORDINATOR;
        
        nanolora_generic_write( ctx, &temp, 1 );
        nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
    }
    else
    {
        temp = NANOLORA_NTW_ROLE_END_DEVICE;

        nanolora_generic_write( ctx, &temp, 1 );
        nanolora_generic_write( ctx, &data_buff[ 4 ], 1 );
    }
}

void nanolora_get_network_auto_settings ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x24, 0x28 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_get_network_preference ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x25, 0x29 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_set_network_preference ( nanolora_t *ctx, uint8_t prot, uint8_t auto_join, uint8_t adr )
{
    uint8_t tmp;
    uint8_t check_sum;
    uint8_t data_buff[ 3 ] = { 0x00, 0x05, 0x25 };

    tmp |= prot;
    tmp |= auto_join;
    tmp |= adr;

    check_sum = 0x2A + tmp;

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &tmp, 1 );
    nanolora_generic_write( ctx, &check_sum, 1 );
}

void nanolora_get_network_join_mode ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x27, 0x28 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_set_network_join_mode ( nanolora_t *ctx, uint8_t ntw_join_mode )
{

    uint8_t data_buff[ 6 ] = { 0x00, 0x05, 0x27, 0x2C, 0x01, 0x2D };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );

    if ( ntw_join_mode == NANOLORA_NTW_JOIN_MODE_ABP )
    {
        nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
        nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
    }
    else
    {
        nanolora_generic_write( ctx, &data_buff[ 4 ], 1 );
        nanolora_generic_write( ctx, &data_buff[ 5 ], 1 );
    }
}

void nanolora_get_battery_level  ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x2B, 0x30 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_get_wan_network_type ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x2D, 0x31 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_wan_network_public ( nanolora_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x2D, 0x34, 0x66 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 4 ], 1 );
}

void nanolora_wan_network_private ( nanolora_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x2D, 0x12, 0x44 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 4 ], 1 );
}

void nanolora_network_stop ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x30, 0x34 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_network_start ( nanolora_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x31, 0x35 };

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 3 ], 1 );
}

void nanolora_send_data ( nanolora_t *ctx, uint8_t *tx_data, uint8_t length )
{
    uint8_t data_buff[ 3 ] = { 0x00, 0x50, 0xFF };
    
    uint8_t packet_len;
    uint8_t cnt;
    uint16_t check_sum_tmp;
    uint8_t check_sum;

    packet_len = 7 + length + 1;
    check_sum_tmp = 0x024E + packet_len;

    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &packet_len, 1 );
    nanolora_generic_write( ctx, &data_buff[ 1 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 0 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );
    nanolora_generic_write( ctx, &data_buff[ 2 ], 1 );

    for ( cnt = 0; cnt < length; cnt++ )
    {
        nanolora_generic_write( ctx, &tx_data[ cnt ], 1 );
        check_sum_tmp += tx_data[ cnt ];
    }

    check_sum = ( uint8_t )check_sum_tmp;

    nanolora_generic_write( ctx, &check_sum, 1 );
}

uint8_t nanolora_rsp_rdy ( nanolora_t *ctx )
{
    if ( ctx->rsp_rdy )
    {
        ctx->rsp_rdy = NANOLORA_RSP_NOT_READY;

        return NANOLORA_RSP_READY;
    }

    return NANOLORA_RSP_NOT_READY;
}

void nanolora_uart_isr ( nanolora_t *ctx, uint8_t reader_hdlr )
{
    static uint16_t rx_idx = 0;

    ctx->rx_data[ rx_idx++ ] = reader_hdlr;

    if ( rx_idx == 1 )
    {
        ctx->rsp_len = ( uint16_t )ctx->rx_data[ 0 ] << 8;
    }
    else if ( rx_idx == 2 )
    {
        ctx->rsp_len |= ctx->rx_data[ 1 ];
    }
    else if ( rx_idx == ctx->rsp_len )
    {
        rx_idx  = 0;
        ctx->rsp_rdy = NANOLORA_RSP_READY;
    }
}

nanolora_err_t nanolora_parser_rsp ( nanolora_t *ctx, nanolora_rsp_t *response )
{
    uint16_t cnt;
    uint8_t crc_byte;

    response->length     = ctx->rsp_len;
    response->message_id = ctx->rx_data[ 2 ];

    for ( cnt = 3; cnt < ctx->rsp_len - 1; cnt++ )
    {
        response->payload[ cnt - 3 ] = ctx->rx_data[ cnt ];
    }

    response->crc = ctx->rx_data[ ctx->rsp_len - 1 ];

    crc_byte = nanolora_checksum_calc( ctx->rsp_len, ctx->rx_data );

    if ( crc_byte == response->crc )
    {
        return NANOLORA_ERR_STATUS_OK;
    }

    return NANOLORA_ERR_CRC;
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t nanolora_checksum_calc ( uint16_t pckg_len, uint8_t *pckg_payload )
{
    uint16_t cnt;
    uint8_t checksum = 0;

    for ( cnt = 0; cnt < pckg_len - 1; cnt++ )
    {
        checksum += *pckg_payload;
        pckg_payload++;
    }

    return checksum;
}

// ------------------------------------------------------------------------- END

