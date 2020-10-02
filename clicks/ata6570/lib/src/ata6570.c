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

#include "ata6570.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ATA6570_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ata6570_cfg_setup ( ata6570_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins

    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_8;
    cfg->parity_bit     = UART_PARITY_NONE;
    cfg->stop_bit       = UART_STOP_BITS_ONE;
    cfg->uart_blocking  = true;
}

ATA6570_RETVAL ata6570_init ( ata6570_t *ctx, ata6570_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;
    uart_config_t uart_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ATA6570_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ATA6570_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ATA6570_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Default config
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

    return ATA6570_OK;
}

void ata6570_generic_transfer ( ata6570_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );
}

void ata6570_generic_multi_write ( ata6570_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

void ata6570_generic_multi_read ( ata6570_t *ctx, char *data_buf, uint16_t len )
{
    uart_read( &ctx->uart, data_buf, len );
}

char ata6570_generic_single_read ( ata6570_t *ctx )
{
    char rx_data;

    uart_read( &ctx->uart, &rx_data, 1 );
    
    return rx_data;
}

void ata6570_generic_single_write ( ata6570_t *ctx, char tx_data )
{
    uart_write( &ctx->uart, &tx_data, 1 );
}

void ata6570_write_reg ( ata6570_t *ctx, const uint8_t address, uint8_t input )
{
    uint8_t tmp[ 2 ];

    tmp[ 0 ] = ( address << 1 );
    tmp[ 1 ] = input;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 2 );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t ata6570_read_reg ( ata6570_t *ctx, const uint8_t address )
{
    uint8_t tmp;
    uint8_t read_reg;

    tmp = ( address << 1 ) | 0x01;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tmp, 1 );
    Delay_100ms( );
    spi_master_read( &ctx->spi, &read_reg, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    //ata6570_generic_transfer ( ctx, &tmp, 1, &read_reg, 1 );

    return read_reg;
}

// ------------------------------------------------------------------------- END

