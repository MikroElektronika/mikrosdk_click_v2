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

#include "flash3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define FLASH3_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void drv_command ( flash3_t *ctx, uint8_t command );


static void drv_write_data ( flash3_t *ctx, uint8_t *buffer, uint16_t count );


static uint8_t drv_read_byte ( flash3_t *ctx );


static void drv_read_data ( flash3_t *ctx, uint8_t *buffer,uint16_t count );


static void drv_write_address ( flash3_t *ctx, uint32_t address );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void flash3_cfg_setup ( flash3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->hlo = HAL_PIN_NC;
    cfg->wp = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

FLASH3_RETVAL flash3_init ( flash3_t *ctx, flash3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = FLASH3_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return FLASH3_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, FLASH3_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->hlo, cfg->hlo );
    digital_out_init( &ctx->wp, cfg->wp );
    digital_in_init( &ctx->cs, cfg->cs);

    return FLASH3_OK;
}

void flash3_generic_transfer ( flash3_t *ctx, uint8_t *wr_buf, 
                            uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

void flash3_pause ( flash3_t *ctx )
{
    digital_out_low( &ctx->hlo );
    spi_master_select_device( ctx->chip_select );
}

void flash3_unpause ( flash3_t *ctx )
{
    digital_out_high( &ctx->hlo );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_wr_prot_enable ( flash3_t *ctx )
{
    digital_out_low( &ctx->wp );
}

void flash3_wr_prot_disable ( flash3_t *ctx )
{
    digital_out_high( &ctx->wp );
}

void flash3_setting ( flash3_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    digital_out_high( &ctx->wp );
    digital_out_high( &ctx->hlo );
}

void flash3_write_enable ( flash3_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_WREN );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_write_disable ( flash3_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_WRDI );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_write_cmd ( flash3_t *ctx, uint8_t cmd )
{
    flash3_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, cmd );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_write_adv_cmd ( flash3_t *ctx, uint8_t cmd, uint8_t *arg, uint32_t cnt )
{
    flash3_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, cmd );
    drv_write_data( ctx, arg, cnt );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t flash3_rd_stat_reg ( flash3_t *ctx )
{
    uint8_t result;

    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_RDSR );
    result = drv_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  

    return result;
}

void flash3_wr_stat_reg ( flash3_t *ctx, uint8_t status )
{
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_WRSR );
    drv_command( ctx, status );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t flash3_rd_func_reg ( flash3_t *ctx )
{
    uint8_t result;

    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_RDFR );
    result = drv_read_byte( ctx );
    spi_master_deselect_device( ctx->chip_select );  

    return result;
}

void flash3_wr_func_reg ( flash3_t *ctx, uint8_t function )
{
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_WRFR );
    drv_command( ctx, function );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_normal_read( flash3_t *ctx, uint32_t addr, uint8_t *buff, uint32_t cnt )
{
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_NORMAL_RD );
    drv_write_address( ctx, addr );
    drv_read_data( ctx, &buff[ 0 ], cnt );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_fast_read ( flash3_t *ctx, uint32_t addr, uint8_t *buff, uint32_t cnt )
{
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_FAST_RD );
    drv_write_address( ctx, addr );
    drv_command( ctx, 0xFF );
    drv_read_data( ctx, &buff[ 0 ], cnt );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_write ( flash3_t *ctx, uint32_t addr, uint8_t *buff, uint32_t cnt )
{
    flash3_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    drv_command( ctx, FLASH3_PP );
    drv_write_address( ctx, addr );
    drv_write_data( ctx, &buff[ 0 ], cnt );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_chip_erase ( flash3_t *ctx )
{
    flash3_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_CHIP_ER );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_sector_erase ( flash3_t *ctx, uint32_t address )
{
    flash3_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_SECTOR_ER );
    drv_write_address( ctx, address );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_block32_erase( flash3_t *ctx, uint32_t address )
{
    flash3_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_BLOCK_ER32 );
    drv_write_address( ctx, address );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash3_block64_erase( flash3_t *ctx, uint32_t address )
{
    flash3_write_enable( ctx );
    spi_master_select_device( ctx->chip_select );
    drv_command( ctx, FLASH3_BLOCK_ER64 );
    drv_write_address( ctx, address );
    spi_master_deselect_device( ctx->chip_select );  
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void drv_command ( flash3_t *ctx, uint8_t command )
{
    uint8_t temp[ 1 ];

    temp[ 0 ] = command;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &temp, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

static void drv_write_data ( flash3_t *ctx, uint8_t *buffer, uint16_t count )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, buffer, count );
    spi_master_deselect_device( ctx->chip_select );
}

static uint8_t drv_read_byte ( flash3_t *ctx )
{
    uint8_t ret_val[ 1 ];

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, ret_val, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return ret_val[ 0 ];
}

static void drv_read_data ( flash3_t *ctx, uint8_t *buffer, uint16_t count )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, buffer, count );
    spi_master_deselect_device( ctx->chip_select );
}

static void drv_write_address ( flash3_t *ctx, uint32_t address )
{
    uint8_t temp[ 3 ];
    temp[ 0 ] = ( uint8_t )  ( address >> 16 );
    temp[ 1 ] = ( uint8_t )  ( ( address & 0x00FF00 ) >> 8 );
    temp[ 2 ] = ( uint8_t )  ( address & 0x0000FF );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, temp, 3 );
    spi_master_deselect_device( ctx->chip_select );

    return;
}

// ------------------------------------------------------------------------- END

