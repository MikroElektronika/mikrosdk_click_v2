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

#include "fram.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define FRAM_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void fram_cfg_setup ( fram_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->hld = HAL_PIN_NC;
    cfg->wp = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 1000000; 
}

FRAM_RETVAL fram_init ( fram_t *ctx, fram_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = FRAM_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return FRAM_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, FRAM_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->hld, cfg->hld );
    digital_out_high(&ctx->hld);
    digital_out_init( &ctx->wp, cfg->wp );

    return FRAM_OK;
}

void fram_generic_transfer ( fram_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select ); 
}

void fram_init_f ( fram_t *ctx ) 
{
    spi_master_deselect_device( ctx->chip_select ); 
}

void fram_write_enable ( fram_t *ctx ) 
{
    uint8_t temp;
    temp = FRAM_WREN;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &temp, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void fram_write_disable ( fram_t *ctx ) 
{
    uint8_t temp;
    temp = FRAM_WRDI;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &temp, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    
    return;
}

uint8_t fram_read_status ( fram_t *ctx ) 
{
    uint8_t temp[ 1 ];
    uint8_t reg;

    reg = FRAM_RDSR;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &reg, 1, temp, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
  
    return temp[ 0 ];
}

void fram_write_status ( fram_t *ctx, uint8_t value ) 
{
    uint8_t temp[ 2 ];

    temp[ 0 ] = FRAM_WRSR;
    temp[ 1 ] = value;

    fram_write_enable( ctx );
    Delay_10ms();

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void fram_read ( fram_t *ctx, uint16_t address, uint8_t *buffer, uint16_t count ) 
{   
    uint8_t *data_ptr;
    uint8_t temp[ 3 ];
    uint8_t i;

    data_ptr  = buffer;

    temp[ 0 ]  = FRAM_READ;
    temp[ 1 ] = address >> 8;
    temp[ 2 ] = address & 0xFF;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, temp, 3, buffer, count );
    spi_master_deselect_device( ctx->chip_select );   
}

void fram_write ( fram_t *ctx, uint16_t address, uint8_t *buffer, uint16_t count ) 
{
    uint8_t *data_ptr;
    uint8_t temp[ 3 ];
    uint8_t i;

    data_ptr  = buffer;
    
    temp[ 0 ] = FRAM_WRITE;
    temp[ 1 ] = address >> 8;
    temp[ 2 ] = address & 0xFF;
    
    fram_write_enable( ctx );
    Delay_10ms();

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp, 3 );

    spi_master_write( &ctx->spi, data_ptr, count );

    spi_master_deselect_device( ctx->chip_select );   
    
    fram_write_disable( ctx );  
    Delay_10ms();
}

void fram_erase_all ( fram_t *ctx ) 
{
    uint16_t cntr;
    uint8_t temp[ 3 ];

    temp[ 0 ] = FRAM_WRITE;
    temp[ 1 ] = 0x00;
    temp[ 2 ] = 0x00;

    fram_write_status( ctx, 0x00 );
    Delay_10ms();
    
    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, temp, 3 );    

    temp[ 0 ] = 0x00;

    for ( cntr = 0; cntr < FRAM_MEM_SIZE; cntr++ )
    {
        spi_master_write( &ctx->spi, temp, 1 );
    }
    
    spi_master_deselect_device( ctx->chip_select );  

    fram_write_disable( ctx );  
    Delay_10ms();
}

// ------------------------------------------------------------------------- END

