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

#include "ft.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t crc16_calculate ( uint8_t *buf_data, uint16_t len );

static void reset_data_flags ( ft_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ft_cfg_setup ( ft_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

     cfg->rst = HAL_PIN_NC;
     cfg->cs   = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

FT_RETVAL ft_init ( ft_t *ctx, ft_cfg_t *cfg )
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
    digital_out_init( &ctx->cs, cfg->cs );

    digital_out_high( &ctx->rst );

    ctx->drv_new_data       = 0;
    ctx->drv_start_package  = 0;
    ctx->drv_rsp_flag       = 0;
    ctx->drv_buff_cnt       = 0;
    ctx->drv_rsp_lenght     = 0;

    return FT_OK;
}

void ft_generic_write ( ft_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t ft_generic_read ( ft_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void ft_set_rst_pin ( ft_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void ft_send_package ( ft_t *ctx, uint8_t *data_buf, uint16_t len, uint8_t queue )
{
    uint8_t tx_buf[ MAX_DATA_BUFFER ];
    uint16_t cnt;
    uint16_t crc_value;
    uint16_t global_len = 0;
    
    global_len = DRV_HEADER_LEN + DRV_DATA_CRC_LEN + len;
    
    tx_buf[ 0 ] = DRV_HEADER_DATA;
    tx_buf[ 1 ] = DRV_HEADER_DATA;
    
    tx_buf[ 2 ] = ( uint8_t )( global_len & 0x00ff );
    tx_buf[ 3 ] = ( uint8_t )( ( global_len & 0xff00 ) >> 8 );
    tx_buf[ 4 ] = queue;
    
    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + DRV_HEADER_LEN ] = data_buf[ cnt ];
    }

    crc_value = crc16_calculate( tx_buf,  DRV_HEADER_LEN + len );
    tx_buf[ DRV_HEADER_LEN + len ] = ( uint8_t )( crc_value & 0x00ff );
    tx_buf[ DRV_HEADER_LEN + len + 1 ] = ( uint8_t )( ( crc_value & 0xff00 ) >> 8 );

    for ( cnt = 0; cnt < global_len; cnt++ )
    {
       ft_generic_write( ctx, &tx_buf[ cnt ], 1 );
    }
}


uint8_t ft_get_data_status ( ft_t *ctx )
{
    return ctx->drv_new_data;
}

uint16_t ft_get_data ( ft_t *ctx, uint8_t *data_buf )
{
    uint8_t cnt;
    uint16_t data_len;
    
    data_len = ctx->drv_rsp_lenght - DRV_DATA_CRC_LEN;
    
    for ( cnt = DRV_HEADER_LEN; cnt < data_len; cnt++ )
    {
       data_buf[ cnt - DRV_HEADER_LEN ] =  ctx->drv_rsp_buff[ cnt ];
    }
    
    reset_data_flags( ctx );
    return data_len;
}

void ft_isr_parser ( ft_t *ctx, uint8_t rsp_data )
{
    if ( ctx->drv_new_data != DRV_NEW_DATA_AVAILABLE )
    {
        if ( ctx->drv_start_package == DRV_CONFIRMED_PACKAGE )
        {
            ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
        }
        else
        {
            if ( ( ctx->drv_rsp_flag == DRV_CHACK_HEDER_DATA_1 ) && ( rsp_data == DRV_HEADER_DATA ) )
            {
                ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
                ctx->drv_rsp_flag = DRV_CHACK_HEDER_DATA_2;
            }
            else if ( ( ctx->drv_rsp_flag == DRV_CHACK_HEDER_DATA_2 ) && ( rsp_data == DRV_HEADER_DATA ) )
            {
                ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
                ctx->drv_rsp_flag = DRV_CHACK_LEN_DATA_LSB;
            }
            else if ( ctx->drv_rsp_flag == DRV_CHACK_LEN_DATA_LSB )
            {
                ctx->drv_rsp_lenght = rsp_data;
                ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
                ctx->drv_rsp_flag = DRV_CHACK_LEN_DATA_MSB;
            }
            else if ( ctx->drv_rsp_flag == DRV_CHACK_LEN_DATA_MSB )
            {
                ctx->drv_rsp_lenght |= rsp_data << 8;
                ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
                ctx->drv_start_package = DRV_CONFIRMED_PACKAGE;
            }
        }

        if ( ctx->drv_buff_cnt == ctx->drv_rsp_lenght )
        {
            ctx->drv_new_data = DRV_NEW_DATA_AVAILABLE;
        }
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


static uint16_t crc16_calculate ( uint8_t *buf_data, uint16_t len )
{
    uint8_t temp;
    uint16_t crc = 0xFFFF;

    while ( len-- )
    {
      temp = *buf_data++ ^ crc;
      crc >>= 8;
      crc ^= CRC_TABLE[ temp ];
    }
    return crc;
}

static void reset_data_flags ( ft_t *ctx )
{
    ctx->drv_new_data      = 0;
    ctx->drv_start_package = 0;
    ctx->drv_rsp_flag      = 0;
    ctx->drv_buff_cnt      = 0;
    ctx->drv_rsp_lenght    = 0;
}


// ------------------------------------------------------------------------- END

