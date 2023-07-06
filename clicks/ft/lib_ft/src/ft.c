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

// ------------------------------------------------------------------ CONSTS
static const uint16_t ft_crc_table[ 256 ] =
{
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t ft_crc16_calculate ( uint8_t *buf_data, uint16_t len );

static void ft_reset_data_flags ( ft_t *ctx );

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

err_t ft_init ( ft_t *ctx, ft_cfg_t *cfg )
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

void ft_generic_write ( ft_t *ctx, uint8_t *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t ft_generic_read ( ft_t *ctx, uint8_t *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void ft_set_rst_pin ( ft_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void ft_send_package ( ft_t *ctx, uint8_t *data_buf, uint16_t len, uint8_t queue )
{
    uint8_t tx_buf[ FT_MAX_DATA_BUFFER ] = { 0 };
    uint16_t cnt = 0;
    uint16_t crc_value = 0;
    uint16_t package_len = 0;
    
    package_len = FT_DRV_HEADER_LEN + FT_DRV_DATA_CRC_LEN + len;
    
    tx_buf[ 0 ] = FT_DRV_HEADER_DATA;
    tx_buf[ 1 ] = FT_DRV_HEADER_DATA;
    
    tx_buf[ 2 ] = ( uint8_t )( package_len & 0x00FF );
    tx_buf[ 3 ] = ( uint8_t )( ( package_len & 0xFF00 ) >> 8 );
    tx_buf[ 4 ] = queue;
    
    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + FT_DRV_HEADER_LEN ] = data_buf[ cnt ];
    }

    crc_value = ft_crc16_calculate( tx_buf, FT_DRV_HEADER_LEN + len );
    tx_buf[ FT_DRV_HEADER_LEN + len ] = ( uint8_t )( crc_value & 0x00FF );
    tx_buf[ FT_DRV_HEADER_LEN + len + 1 ] = ( uint8_t )( ( crc_value & 0xFF00 ) >> 8 );

    for ( cnt = 0; cnt < package_len; cnt++ )
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
    uint8_t cnt = 0;
    uint16_t data_len = 0;
    
    data_len = ctx->drv_rsp_lenght - FT_DRV_DATA_CRC_LEN - FT_DRV_HEADER_LEN;
    
    for ( cnt = 0; cnt < data_len; cnt++ )
    {
        data_buf[ cnt ] = ctx->drv_rsp_buff[ cnt + FT_DRV_HEADER_LEN ];
    }
    
    ft_reset_data_flags( ctx );
    return data_len;
}

void ft_isr_parser ( ft_t *ctx, uint8_t rsp_data )
{
    if ( FT_DRV_NEW_DATA_AVAILABLE != ctx->drv_new_data )
    {
        if ( FT_DRV_CONFIRMED_PACKAGE == ctx->drv_start_package )
        {
            ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
            if ( ctx->drv_buff_cnt == ctx->drv_rsp_lenght )
            {
                ctx->drv_new_data = FT_DRV_NEW_DATA_AVAILABLE;
            }
        }
        else
        {
            if ( ( FT_DRV_CHECK_HEADER_DATA_1 == ctx->drv_rsp_flag ) && ( FT_DRV_HEADER_DATA == rsp_data ) )
            {
                ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
                ctx->drv_rsp_flag = FT_DRV_CHECK_HEADER_DATA_2;
            }
            else if ( ( FT_DRV_CHECK_HEADER_DATA_2 == ctx->drv_rsp_flag ) && ( FT_DRV_HEADER_DATA == rsp_data ) )
            {
                ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
                ctx->drv_rsp_flag = FT_DRV_CHECK_LEN_DATA_LSB;
            }
            else if ( FT_DRV_CHECK_LEN_DATA_LSB == ctx->drv_rsp_flag )
            {
                ctx->drv_rsp_lenght = rsp_data;
                ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
                ctx->drv_rsp_flag = FT_DRV_CHECK_LEN_DATA_MSB;
            }
            else if ( FT_DRV_CHECK_LEN_DATA_MSB == ctx->drv_rsp_flag )
            {
                ctx->drv_rsp_lenght |= rsp_data << 8;
                ctx->drv_rsp_buff[ ctx->drv_buff_cnt++ ] = rsp_data;
                ctx->drv_start_package = FT_DRV_CONFIRMED_PACKAGE;
            }
        }
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t ft_crc16_calculate ( uint8_t *buf_data, uint16_t len )
{
    uint8_t temp = 0;
    uint16_t crc = 0xFFFF;

    while ( len-- )
    {
        temp = *buf_data++ ^ crc;
        crc >>= 8;
        crc ^= ft_crc_table[ temp ];
    }
    return crc;
}

static void ft_reset_data_flags ( ft_t *ctx )
{
    ctx->drv_new_data      = 0;
    ctx->drv_start_package = 0;
    ctx->drv_rsp_flag      = 0;
    ctx->drv_buff_cnt      = 0;
    ctx->drv_rsp_lenght    = 0;
}

// ------------------------------------------------------------------------- END
