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

#include "flash6.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define FLASH6_DUMMY    0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void flash6_cfg_setup ( flash6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

FLASH6_RETVAL flash6_init ( flash6_t *ctx, flash6_cfg_t *cfg )
{
   spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = FLASH6_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return FLASH6_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, FLASH6_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return FLASH6_OK;
}

void flash6_generic_transfer 
( 
    flash6_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );     
}

void flash6_send_cmd ( flash6_t *ctx, uint8_t cmd_data )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &cmd_data, 1 );
    spi_master_deselect_device( ctx->chip_select );     
}

void flash6_read_data ( flash6_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint16_t len )
{
    flash6_generic_transfer ( ctx, &reg_addr, 1, data_buf, len);
}

void flash6_write_data ( flash6_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint8_t len )
{
    uint8_t write_buf[ 100 ];
    uint16_t n_cnt;

    write_buf[ 0 ] = reg_addr;

    for ( n_cnt = 1; n_cnt < ( len + 1 ); n_cnt++ )
    {
        write_buf[ n_cnt ] = *data_buf;
        data_buf++;
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );   
}

uint8_t flash6_get_manufacture_device_id ( flash6_t *ctx, uint8_t *manufacture_id, uint8_t *device_id )
{
    uint8_t buf_id[ 6 ];
    uint8_t err_cnt = 0;

    flash6_read_data( ctx, FLASH6_CMD_MANUFACTURER_DEVICE_ID, buf_id, 6 );
    *manufacture_id = buf_id[ 4 ];
    *device_id = buf_id[ 5 ];
    
    if ( *device_id != FLASH6_DEVICE_ID && *manufacture_id != FLASH6_MANIFACTURE_ID )
    {
        err_cnt++;
    }

    if ( err_cnt == 0 )
    {
        return FLASH6_DEVICE_OK;
    }

    return FLASH6_DEVICE_ERROR;
}

void flash6_erase_memory_segment( flash6_t *ctx, uint8_t segment, uint32_t start_addr )
{
    uint8_t buff[ 4 ];
    
    buff[ 0 ] = segment;
    buff[ 1 ] = ( uint8_t )( start_addr >> 16 );
    buff[ 2 ] = ( uint8_t )( start_addr >> 8 );
    buff[ 3 ] = ( uint8_t )( start_addr );

    flash6_send_cmd( ctx, FLASH6_CMD_WRITE_ENABLE );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, buff, 4 );
    spi_master_deselect_device( ctx->chip_select );   
}

uint8_t flash6_read_status_reg ( flash6_t *ctx, uint8_t status_cmd )
{
    uint8_t read_buf[ 1 ];

    flash6_generic_transfer( ctx,  &status_cmd, 1,  read_buf, 1 );

    return read_buf[ 0 ];
}

void flash6_write_status_reg ( flash6_t *ctx, uint8_t status_cmd, uint8_t status_data )
{
    flash6_send_cmd( ctx, FLASH6_CMD_VOL_SR_WRITE_ENABLE );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi,  &status_cmd, 1 );
    spi_master_write( &ctx->spi, &status_data, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void flash6_write_memory_data ( flash6_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size )
{
    uint8_t write_buf[ 256 ];
    uint16_t n_cnt;

    write_buf[ 0 ] = FLASH6_CMD_PAGE_PROGRAM;
    write_buf[ 1 ] = ( uint8_t )( addr >> 16 );
    write_buf[ 2 ] = ( uint8_t )( addr >> 8 );
    write_buf[ 3 ] = ( uint8_t )( addr );

    for ( n_cnt = 4; n_cnt < ( buf_size + 4 ); n_cnt++ )
    {
        write_buf[ n_cnt ] = data_buf[ n_cnt - 4 ];
    }

    flash6_send_cmd( ctx, FLASH6_CMD_WRITE_ENABLE );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi,  write_buf , buf_size + 4 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void flash6_read_memory_data ( flash6_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size )
{
    uint8_t write_buf[ 4 ];

    write_buf[ 0 ] = FLASH6_CMD_READ_DATA;
    write_buf[ 1 ] = ( uint8_t ) ( addr >> 16 );
    write_buf[ 2 ] = ( uint8_t ) ( addr >> 8 );
    write_buf[ 3 ] = ( uint8_t ) ( addr );

    flash6_generic_transfer( ctx, write_buf, 4, data_buf,  buf_size );

}

void flash6_software_reset ( flash6_t *ctx )
{
    flash6_send_cmd( ctx, FLASH6_CMD_ENABLE_RESET );
    flash6_send_cmd( ctx, FLASH6_CMD_RESET_DEVICE );
    Delay_50us( );
}

// ------------------------------------------------------------------------- END

