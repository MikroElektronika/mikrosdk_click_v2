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

#include "flash5.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define FLASH5_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static const uint8_t device_id[ 3 ] = { 0xEF, 0xAA, 0x21 };

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void communication_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void flash5_cfg_setup ( flash5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->wp = HAL_PIN_NC;
    cfg->hld = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

FLASH5_RETVAL flash5_init ( flash5_t *ctx, flash5_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = FLASH5_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return FLASH5_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, FLASH5_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_init( &ctx->hld, cfg->hld );
    
    digital_out_high( &ctx->wp );
    digital_out_high( &ctx->hld );
    
    return FLASH5_OK;
}

void flash5_generic_transfer ( flash5_t *ctx, uint8_t *wr_buf, 
                             uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    communication_delay( );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len  );
    communication_delay( );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash5_read_data ( flash5_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint16_t n_buf_size )
{
    flash5_generic_transfer( ctx,  &reg_addr, 1, data_buf, n_buf_size );
}

void flash5_write_data ( flash5_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint16_t n_buf_size )
{
    uint8_t write_buf[ 100 ];
    uint16_t n_cnt;

    write_buf[ 0 ] = reg_addr;

    for ( n_cnt = 1; n_cnt < ( n_buf_size + 1 ); n_cnt++ )
    {
        write_buf[ n_cnt ] = *data_buf;
        data_buf++;
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_buf, n_buf_size + 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash5_send_cmd ( flash5_t *ctx, uint8_t cmd_data )
{
    spi_master_select_device( ctx->chip_select );
    communication_delay( );
    spi_master_write( &ctx->spi, &cmd_data, 1 );
    communication_delay( );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t flash5_set_wp_pin ( flash5_t *ctx, uint8_t status )
{
    if ( ( status == FLASH5_PIN_STATUS_HIGH ) || ( status == FLASH5_PIN_STATUS_LOW ) )
    {
        digital_out_write( &ctx->wp, status );
    }
    
    return FLASH5_DEVICE_ERROR;
}

uint8_t flash5_set_hold_pin ( flash5_t *ctx, uint8_t status )
{
    if ( ( status == FLASH5_PIN_STATUS_HIGH ) || ( status == FLASH5_PIN_STATUS_LOW ) )
    {
        digital_out_write( &ctx->hld, status );
    }
    
    return FLASH5_DEVICE_ERROR;
}

uint8_t flash5_device_id_check ( flash5_t *ctx )
{
    uint8_t buf_id[ 4 ];
    uint8_t n_cnt;
    uint8_t err_cnt = 0;

    flash5_read_data( ctx, FLASH5_CMD_DEVICE_ID, buf_id, 4 );

    for ( n_cnt = 0; n_cnt < 3; n_cnt++ )
    {
        if ( buf_id[ n_cnt + 1 ] != device_id[ n_cnt ] )
        {
            err_cnt++;
        }
    }

    if ( err_cnt == 0 )
    {
        return FLASH5_DEVICE_OK;
    }

    return FLASH5_DEVICE_ERROR;
}

void flash5_page_read ( flash5_t *ctx, uint16_t page_num )
{
    uint8_t data_buf[ 4 ];

    data_buf[ 0 ] = FLASH5_CMD_PAGE_READ_DATA;
    data_buf[ 1 ] = 0x00;
    data_buf[ 2 ] = ( uint8_t ) ( ( page_num >> 8 ) & 0x00FF );
    data_buf[ 3 ] = ( uint8_t ) ( page_num & 0x00FF );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );  
}

void flash5_execute_load ( flash5_t *ctx, uint16_t page_num )
{
    uint8_t execute_buf[ 4 ];

    execute_buf[ 0 ] = FLASH5_CMD_EXECUTE;
    execute_buf[ 1 ] = 0x00;
    execute_buf[ 2 ] = ( uint8_t ) ( ( page_num >> 8 ) & 0x00FF );
    execute_buf[ 3 ] = ( uint8_t ) ( page_num & 0x00FF );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, execute_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
}

void flash5_page_read_memory ( flash5_t *ctx, uint16_t column_addr, uint8_t *data_buf, uint16_t buf_size )
{
    uint8_t write_buf[ 4 ];

    write_buf[ 0 ] = FLASH5_CMD_READ_DATA;
    write_buf[ 1 ] = ( uint8_t ) ( ( column_addr >> 8 ) & 0x00FF );
    write_buf[ 2 ] = ( uint8_t ) ( column_addr & 0x00FF );
    write_buf[ 3 ] = 0x00;

    flash5_generic_transfer( ctx, write_buf, 4, data_buf, buf_size );
}

void flash5_continous_read_memory ( flash5_t *ctx, uint8_t *data_buf, uint16_t buf_size )
{
    uint8_t write_buf[ 4 ];

    write_buf[ 0 ] = FLASH5_CMD_READ_DATA;
    write_buf[ 1 ] = 0x00;
    write_buf[ 2 ] = 0x00;
    write_buf[ 3 ] = 0x00;

    flash5_generic_transfer( ctx, write_buf, 4, data_buf, buf_size );
}

void flash5_page_load_memory ( flash5_t *ctx, uint16_t column_addr, uint8_t *data_buf, uint16_t buf_size )
{
    uint8_t write_buf[ 2048 ];
    uint16_t n_cnt;

    write_buf[ 0 ] = 0x02;
    write_buf[ 1 ] = ( uint8_t ) ( ( column_addr >> 8 ) & 0x00FF );
    write_buf[ 2 ] = ( uint8_t ) ( column_addr & 0x00FF );

    for ( n_cnt = 3; n_cnt < ( buf_size + 3 ); n_cnt++ )
    {
        write_buf[n_cnt] = data_buf[ n_cnt - 3 ];
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_buf, buf_size + 3 );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t flash5_read_status_data ( flash5_t *ctx, uint8_t status_cmd, uint8_t status_addr )
{
    uint8_t write_buf[ 2 ];
    uint8_t read_buf[ 1 ];

    write_buf[ 0 ] = status_cmd;
    write_buf[ 1 ] = status_addr;

    flash5_generic_transfer( ctx, write_buf, 2, read_buf, 1 );

    return read_buf[ 0 ];
}

void flash5_write_status_data ( flash5_t *ctx, uint8_t status_cmd, uint8_t status_addr, uint8_t status_data )
{
    uint8_t write_buf[ 3 ];
    
    write_buf[ 0 ] = status_cmd;
    write_buf[ 1 ] = status_addr;
    write_buf[ 2 ] = status_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
}

void flash5_software_reset ( flash5_t *ctx )
{
    flash5_send_cmd( ctx, FLASH5_CMD_RESET );
}

void flash5_erase_page_data ( flash5_t *ctx, uint16_t page_addr )
{
    uint8_t write_buf[ 4 ];
    
    write_buf[ 0 ] = FLASH5_CMD_BLOCK_ERASE;
    write_buf[ 1 ] = 0x00;
    write_buf[ 2 ] = ( uint8_t ) ( ( page_addr >> 8 ) & 0x00FF );
    write_buf[ 3 ] = ( uint8_t ) ( page_addr & 0x00FF );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void communication_delay ( void )
{
    Delay_10ms(  );
}

// ------------------------------------------------------------------------- END

