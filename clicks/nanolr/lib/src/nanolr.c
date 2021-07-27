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

#include "nanolr.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t nanolr_checksum_calc ( uint16_t pckg_len, uint8_t *pckg_payload );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void nanolr_cfg_setup ( nanolr_cfg_t *cfg )
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
}

NANOLR_RETVAL nanolr_init ( nanolr_t *ctx, nanolr_cfg_t *cfg )
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

    ctx->rsp_len = 0;
    ctx->rsp_rdy = 0;
    
    return NANOLR_OK;
}

void nanolr_default_cfg ( nanolr_t *ctx )
{
    nanolr_set_st_pin( ctx, 0 );
    nanolr_reset( ctx );

    nanolr_network_stop( ctx );
    Delay_100ms( );

    nanolr_save_energy_always_on( ctx );
    Delay_100ms( );

    nanolr_network_start( ctx );
    Delay_100ms( );
}

void nanolr_reset ( nanolr_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

void nanolr_generic_write ( nanolr_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t nanolr_generic_read ( nanolr_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t nanolr_request_2_send ( nanolr_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->rts );

    return state;
}

void nanolr_clear_2_send ( nanolr_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->cts, state );
}

uint8_t nanolr_get_gp1_pin ( nanolr_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->gp1 );

    return state;
}

void nanolr_set_st_pin ( nanolr_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->st, state );
}

void nanolr_get_device_info ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x01, 0x05 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_get_device_state ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x04, 0x08 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_sw_reset ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x05, 0x09 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_get_fw_ver ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x06, 0x0A };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_restore_2_factory ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x07, 0x0B };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_save_settings ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x08, 0x0C };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_get_output_power ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x10, 0x14 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_get_operating_channel ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x11, 0x15 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_set_output_power ( nanolr_t *ctx, uint8_t out_pwr )
{
    if ( ( out_pwr > 1 ) && ( out_pwr < 20 ) )
    {
        uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x10, out_pwr, 0x15 + out_pwr };
        
        nanolr_generic_write( ctx, data_buff, 5 );
    }
}

void nanolr_set_operating_channel ( nanolr_t *ctx, nanolr_network_t *net )
{
    uint8_t data_buff[ 8 ] = { 0x00, 0x08, 0x11, net->channel, net->spreading_factor, net->bandwidth, net->coding_rate, 
                               0x19 + net->channel + net->spreading_factor + net->bandwidth + net->coding_rate };

    
    nanolr_generic_write( ctx, data_buff, 8 );
}

void nanolr_save_energy_always_on ( nanolr_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x13, 0x00, 0x18 };

    nanolr_generic_write( ctx, data_buff, 5 );
}

void nanolr_save_energy_rx_window ( nanolr_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x13, 0x01, 0x19 };

    nanolr_generic_write( ctx, data_buff, 5 );
}

void nanolr_save_energy_tx_only ( nanolr_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x13, 0x02, 0x1A };

    nanolr_generic_write( ctx, data_buff, 5 );
}

void nanolr_get_physical_address ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x20, 0x24 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_set_physical_address ( nanolr_t *ctx, uint8_t *app_eui, uint8_t *dev_eui )
{
    uint8_t data_buff[ 3 ] = { 0x00, 0x14, 0x20 };
    uint16_t check_sum_tmp = 0x24;
    uint8_t check_sum;

    nanolr_generic_write( ctx, data_buff, 3 );

    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        nanolr_generic_write( ctx, &app_eui[ cnt ], 1 );
        nanolr_generic_write( ctx, &dev_eui[ cnt ], 1 );
        check_sum_tmp += app_eui[ cnt ];
        check_sum_tmp += dev_eui[ cnt ];
    }

    check_sum = ( uint8_t ) ( check_sum_tmp & 0xFF );

    nanolr_generic_write( ctx, &check_sum, 1 );
}

void nanolr_get_network_address ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x21, 0x25 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_set_network_address ( nanolr_t *ctx, uint16_t ntw_addr )
{
    uint8_t data_buff[ 3 ] = { 0x00, 0x06, 0x21 };
    uint8_t addr_buf[ 2 ];
    uint8_t combine;

    addr_buf[ 0 ] = ( uint8_t ) ( ntw_addr >> 8 );
    addr_buf[ 1 ] = ( uint8_t ) ntw_addr;
    combine = 0x27 + addr_buf[ 0 ] + addr_buf[ 1 ];

    nanolr_generic_write( ctx, data_buff, 3 );
    nanolr_generic_write( ctx, addr_buf, 2 );
    nanolr_generic_write( ctx, &combine, 1 );
}

void nanolr_get_network_id ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x22, 0x26 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_set_network_id ( nanolr_t *ctx, uint16_t ntw_id )
{
    uint8_t data_buff[ 3 ] = { 0x00, 0x06, 0x22 };
    uint8_t id_buf[ 2 ];
    uint8_t combine;

    id_buf[ 0 ] = ( uint8_t ) ( ntw_id >> 8 );
    id_buf[ 1 ] = ( uint8_t ) ntw_id;
    combine = 0x28 + id_buf[ 0 ] + id_buf[ 1 ];

    nanolr_generic_write( ctx, data_buff, 3 );
    nanolr_generic_write( ctx, id_buf, 2 );
    nanolr_generic_write( ctx, &combine, 1 );
}

void nanolr_get_network_role ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x23, 0x27 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_set_network_role ( nanolr_t *ctx, uint8_t ntw_role )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x23, 0x28, 0x2A };
    uint8_t temp;

    nanolr_generic_write( ctx, data_buff, 3 );

    if ( ntw_role == NANOLR_NTW_ROLE_COORDINATOR )
    {
        temp = NANOLR_NTW_ROLE_COORDINATOR;
        
        nanolr_generic_write( ctx, &temp, 1 );
        nanolr_generic_write( ctx, &data_buff[ 3 ], 1 );
    }
    else
    {
        temp = NANOLR_NTW_ROLE_END_DEVICE;

        nanolr_generic_write( ctx, &temp, 1 );
        nanolr_generic_write( ctx, &data_buff[ 4 ], 1 );
    }
}

void nanolr_get_network_auto_settings ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x24, 0x28 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_get_network_preference ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x25, 0x29 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_set_network_preference ( nanolr_t *ctx, uint8_t prot, uint8_t auto_join, uint8_t adr )
{
    uint8_t tmp;
    uint8_t check_sum;
    uint8_t data_buff[ 3 ] = { 0x00, 0x05, 0x25 };

    tmp = prot;
    tmp |= auto_join;
    tmp |= adr;

    check_sum = 0x2A + tmp;

    nanolr_generic_write( ctx, data_buff, 3 );
    nanolr_generic_write( ctx, &tmp, 1 );
    nanolr_generic_write( ctx, &check_sum, 1 );
}

void nanolr_get_network_join_mode ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x27, 0x2B };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_set_network_join_mode ( nanolr_t *ctx, uint8_t ntw_join_mode )
{

    uint8_t data_buff[ 6 ] = { 0x00, 0x05, 0x27, 0x2C, 0x01, 0x2D };

    nanolr_generic_write( ctx, data_buff, 3 );

    if ( ntw_join_mode == NANOLR_NTW_JOIN_MODE_ABP )
    {
        nanolr_generic_write( ctx, &data_buff[ 0 ], 1 );
        nanolr_generic_write( ctx, &data_buff[ 3 ], 1 );
    }
    else
    {
        nanolr_generic_write( ctx, &data_buff[ 4 ], 2 );
    }
}

void nanolr_get_battery_level  ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x2B, 0x30 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_get_wan_network_type ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x2D, 0x31 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_wan_network_public ( nanolr_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x2D, 0x34, 0x66 };

    nanolr_generic_write( ctx, data_buff, 5 );
}

void nanolr_wan_network_private ( nanolr_t *ctx )
{
    uint8_t data_buff[ 5 ] = { 0x00, 0x05, 0x2D, 0x12, 0x44 };

    nanolr_generic_write( ctx, data_buff, 5 );
}

void nanolr_network_stop ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x30, 0x34 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_network_start ( nanolr_t *ctx )
{
    uint8_t data_buff[ 4 ] = { 0x00, 0x04, 0x31, 0x35 };

    nanolr_generic_write( ctx, data_buff, 4 );
}

void nanolr_send_data ( nanolr_t *ctx, uint8_t *tx_data, uint8_t length )
{
    uint8_t data_buff[ 7 ] = { 0x00, 0x00, 0x50, 0x00, 0x00, 0xFF, 0xFF };
    uint8_t packet_len;
    uint16_t check_sum_tmp;
    uint8_t check_sum;

    packet_len = 7 + length + 1;
    check_sum_tmp = 0x024E + packet_len;
    
    data_buff[ 1 ] = packet_len;

    nanolr_generic_write( ctx, data_buff, 7 );

    for ( uint8_t cnt = 0; cnt < length; cnt++ )
    {
        nanolr_generic_write( ctx, &tx_data[ cnt ], 1 );
        check_sum_tmp += tx_data[ cnt ];
    }

    check_sum = ( uint8_t ) ( check_sum_tmp & 0xFF );

    nanolr_generic_write( ctx, &check_sum, 1 );
}

uint8_t nanolr_rsp_rdy ( nanolr_t *ctx )
{
    if ( ctx->rsp_rdy )
    {
        ctx->rsp_rdy = NANOLR_RSP_NOT_READY;

        return NANOLR_RSP_READY;
    }

    return NANOLR_RSP_NOT_READY;
}

void nanolr_uart_isr ( nanolr_t *ctx )
{
    static uint16_t rx_idx = 0;
    uint8_t rx_buf;
    
    if ( nanolr_generic_read( ctx, &rx_buf, 1 ) > 0 ) 
    {
        ctx->rx_data[ rx_idx++ ] = rx_buf;

        if ( rx_idx == 1 )
        {
            ctx->rsp_len = ( uint16_t ) ctx->rx_data[ 0 ] << 8;
        }
        else if ( rx_idx == 2 )
        {
            ctx->rsp_len |= ctx->rx_data[ 1 ];
        }
        else if ( rx_idx == ctx->rsp_len )
        {
            rx_idx = 0;
            ctx->rsp_rdy = NANOLR_RSP_READY;
        }
    }
    
}

nanolr_err_t nanolr_parser_rsp ( nanolr_t *ctx, nanolr_rsp_t *response )
{
    uint8_t crc_byte;

    response->length     = ctx->rsp_len;
    response->message_id = ctx->rx_data[ 2 ];

    for ( uint16_t cnt = 3; cnt < ctx->rsp_len - 1; cnt++ )
    {
        response->payload[ cnt - 3 ] = ctx->rx_data[ cnt ];
    }

    response->crc = ctx->rx_data[ ctx->rsp_len - 1 ];

    crc_byte = nanolr_checksum_calc( ctx->rsp_len, ctx->rx_data );

    if ( crc_byte == response->crc )
    {
        return NANOLR_ERR_STATUS_OK;
    }

    return NANOLR_ERR_CRC;
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t nanolr_checksum_calc ( uint16_t pckg_len, uint8_t *pckg_payload )
{
    uint8_t checksum = 0;

    for ( uint16_t cnt = 0; cnt < pckg_len - 1; cnt++ )
    {
        checksum += *pckg_payload;
        pckg_payload++;
    }

    return checksum;
}

// ------------------------------------------------------------------------- END

