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

#include "flash4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define FLASH4_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_memcpy ( char * d1, char * s1, uint8_t n );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void flash4_cfg_setup ( flash4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->io3 = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 40000; 
}

FLASH4_RETVAL flash4_init ( flash4_t *ctx, flash4_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = FLASH4_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return FLASH4_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, FLASH4_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_high( &ctx->rst );
    digital_in_init( &ctx->io3, cfg->io3 );

    return FLASH4_OK;
}

void flash4_generic_transfer ( flash4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

void flash4_read_manufacturer_id ( flash4_t *ctx, uint8_t *device_id )
{
    uint8_t write_reg[ 6 ];

    write_reg[ 0 ] = FLASH4_CMD_READ_ID;
    write_reg[ 1 ] = 0x00;
    write_reg[ 2 ] = 0x00;
    write_reg[ 3 ] = 0x00;

    flash4_generic_transfer( ctx, write_reg, 4, device_id, 2 );
}

void flash4_read_identification ( flash4_t *ctx, uint8_t *out_data, uint8_t n_data ) 
{
    uint8_t write_reg[ 1 ];
    
    write_reg[ 0 ] = FLASH4_CMD_READ_IDENTIFICATION;

    flash4_generic_transfer( ctx, write_reg, 1, out_data, n_data );
}

uint8_t flash4_read_electronic_id ( flash4_t *ctx )
{
    uint8_t write_reg[ 4 ];
    uint8_t read_reg[ 1 ];
    
    write_reg[ 0 ] = FLASH4_CMD_READ_ELECTRONIC_SIGNATURE;
    write_reg[ 1 ] = 0x00;
    write_reg[ 2 ] = 0x00;
    write_reg[ 3 ] = 0x00;

    flash4_generic_transfer( ctx, write_reg, 4, read_reg, 1 );

    return read_reg[ 0 ];
}

void flash4_read_serial_flash_parameters ( flash4_t *ctx, uint8_t *out_params, uint8_t n_data )
{
    uint8_t write_reg[ 5 ];
    
    write_reg[ 0 ] = FLASH4_CMD_READ_SERIAL_FLASH_PARAMETERS;
    write_reg[ 1 ] = 0x00;
    write_reg[ 2 ] = 0x00;
    write_reg[ 3 ] = 0x00;
    write_reg[ 4 ] = 0x00;

    flash4_generic_transfer( ctx, write_reg, 5, out_params, n_data );
}

uint8_t flash4_read_byte ( flash4_t *ctx, uint8_t reg )
{
    uint8_t write_reg[ 2 ];
    uint8_t read_reg[ 1 ];
    
    write_reg[ 0 ] = reg;

    flash4_generic_transfer( ctx, write_reg, 1, read_reg, 1 );
    
    return read_reg[ 0 ];
}

void flash4_write_byte ( flash4_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t data_buf[ 2 ];
    
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data;
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void flash4_write_command ( flash4_t *ctx, uint8_t cmd )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void flash4_write_reg ( flash4_t *ctx, uint8_t status, uint8_t config )
{
    uint8_t write_reg[ 3 ];
    
    write_reg[ 0 ] = FLASH4_CMD_WRITE_REGISTER_WRR;
    write_reg[ 1 ] = status;
    write_reg[ 2 ] = config;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_reg, 3 );
    spi_master_deselect_device( ctx->chip_select );    
}

void flash4_read_ecc ( flash4_t *ctx, uint8_t *out_ecc, uint8_t n_dummy )
{
    uint8_t write_reg[ 5 ];
    
    write_reg[ 0 ] = FLASH4_CMD_READ_ECC_STATUS_REG;
    write_reg[ 1 ] = 0x00;
    write_reg[ 2 ] = 0x00;
    write_reg[ 3 ] = 0x00;
    write_reg[ 4 ] = 0x00;

    flash4_generic_transfer( ctx, write_reg, 5, out_ecc, 16 );
}

void flash4_read_auto_boot ( flash4_t *ctx, uint8_t *out_ab )
{
    uint8_t write_reg[ 1 ];
    
    write_reg[ 0 ] = FLASH4_CMD_READ_AUTO_BOOT_REG;

    flash4_generic_transfer( ctx, write_reg, 1, out_ab, 4 );
}

void flash4_read_flash( flash4_t *ctx, uint8_t *out_data, uint32_t addr, uint8_t n_data)
{
    uint8_t write_reg[ 5 ];
    
    write_reg[ 0 ] = FLASH4_CMD_READ_FLASH;
    write_reg[ 1 ] = ( uint8_t )( addr>>24 & 0xFF );
    write_reg[ 2 ] = ( uint8_t )( addr>>16 & 0xFF );
    write_reg[ 3 ] = ( uint8_t )( addr>>8 & 0xFF );
    write_reg[ 4 ] = ( uint8_t )( addr & 0xFF );

    flash4_generic_transfer( ctx, write_reg, 5, out_data, n_data );
}

void flash4_4_read_flash ( flash4_t *ctx, uint8_t *out_data, uint32_t addr, uint8_t n_data )
{
    uint8_t write_reg[ 5 ];

    write_reg[ 0 ] = FLASH4_CMD_4READ_FLASH;
    write_reg[ 1 ] = ( uint8_t )( addr >> 24 );
    write_reg[ 2 ] = ( uint8_t )( addr >> 16 );
    write_reg[ 3 ] = ( uint8_t )( addr >> 8 );
    write_reg[ 4 ] = ( uint8_t )( addr );

    flash4_generic_transfer( ctx, write_reg, 5, out_data, n_data );
}

void flash4_fast_read_flash ( flash4_t *ctx, uint8_t *out_data, uint32_t addr, uint8_t n_data_dummy)
{
    uint8_t write_reg[ 5 ];

    write_reg[ 1 ] = ( uint8_t )( ( addr >> 24 ) & 0xFF );
    write_reg[ 2 ] = ( uint8_t )( ( addr >> 16 ) & 0xFF );
    write_reg[ 3 ] = ( uint8_t )( ( addr >> 8 ) & 0xFF );
    write_reg[ 4 ] = ( uint8_t )( addr & 0xFF );

    write_reg[ 0 ] = FLASH4_CMD_FAST_READ_FLASH;

    flash4_generic_transfer( ctx, write_reg, 5, out_data, n_data_dummy );
}

void flash4_4_fast_read_flash ( flash4_t *ctx, uint8_t *out_data, uint8_t addr, uint8_t n_data ) 
{
    uint8_t write_reg[ 5 ];

    write_reg[ 1 ] = ( uint8_t )( ( addr >> 24 ) & 0xFF );
    write_reg[ 2 ] = ( uint8_t )( ( addr >> 16 ) & 0xFF );
    write_reg[ 3 ] = ( uint8_t )( ( addr >> 8 ) & 0xFF );
    write_reg[ 4 ] = ( uint8_t )( addr & 0xFF );

    write_reg[ 0 ] = FLASH4_CMD_FAST_4READ_FLASH;

    flash4_generic_transfer( ctx, write_reg, 5, out_data, n_data );
}

void flash4_4_page_program ( flash4_t *ctx, uint8_t *in_data, uint32_t addr, uint8_t n_data )
{  
    uint8_t write_reg[ 256 ];
    uint8_t cnt;
    
    write_reg[ 1 ] = ( uint8_t )( ( addr >> 24 ));
    write_reg[ 2 ] = ( uint8_t )( ( addr >> 16 ));
    write_reg[ 3 ] = ( uint8_t )( ( addr >> 8 ));
    write_reg[ 4 ] = ( uint8_t )( addr );

    write_reg[ 0 ] = FLASH4_CMD_PAGE_4PROGRAM;
    
    for ( cnt = 5; cnt < n_data + 5 ; cnt++ )
    {
         write_reg[ cnt ] = in_data[ cnt - 5 ];
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_reg, n_data + 5 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void flash4_sector_erase ( flash4_t *ctx, uint32_t addr )
{
    uint8_t write_reg[ 5 ];

    write_reg[ 1 ] = ( uint8_t )( ( addr >> 24 ) );
    write_reg[ 2 ] = ( uint8_t )( ( addr >> 16 ) );
    write_reg[ 3 ] = ( uint8_t )( ( addr >> 8 ));
    write_reg[ 4 ] = ( uint8_t )( addr );

    write_reg[ 0 ] = FLASH4_CMD_SECTOR_ERASE;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_reg, 5 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void flash4_4sector_erase( flash4_t *ctx, uint32_t addr )
{
    uint8_t write_reg[ 5 ];

    write_reg[ 1 ] = ( uint8_t )( ( addr >> 24 ) );
    write_reg[ 2 ] = ( uint8_t )( ( addr >> 16 ));
    write_reg[ 3 ] = ( uint8_t )( ( addr >> 8 ) );
    write_reg[ 4 ] = ( uint8_t )( addr );

    write_reg[ 0 ] = FLASH4_CMD_SECTOR_4ERASE;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_reg, 5 );
    spi_master_deselect_device( ctx->chip_select ); 
}

uint8_t flash4_check_wip ( flash4_t *ctx )
{
    uint8_t read_data;
    
    read_data = flash4_read_byte( ctx, FLASH4_CMD_READ_STATUS_REG_1 );
    
    if ( read_data & 0x01 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

uint8_t flash4_check_wel ( flash4_t *ctx )
{
    uint8_t read_data;

    read_data = flash4_read_byte( ctx, FLASH4_CMD_READ_STATUS_REG_1 );
    
    if ( read_data & 0x02 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

uint8_t flash4_check_ps ( flash4_t *ctx )
{
    uint8_t read_data;

    read_data = flash4_read_byte( ctx, FLASH4_CMD_READ_STATUS_REG_2 );

    if ( read_data & 0x01 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t flash4_check_es ( flash4_t *ctx )
{
    uint8_t read_data;

    read_data = flash4_read_byte( ctx, FLASH4_CMD_READ_STATUS_REG_2 );
    
    if ( read_data & 0x02 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void flash4_reset ( flash4_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_memcpy ( char * d1, char * s1, uint8_t n )
{
    char *dd;
    char *ss;

    ss = s1;
    dd = d1;
    while ( n-- )
    {
        *dd++ = *ss++;
    }
}

// ------------------------------------------------------------------------- END

