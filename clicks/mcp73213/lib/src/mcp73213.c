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

#include "mcp73213.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MCP73213_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mcp73213_cfg_setup ( mcp73213_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

MCP73213_RETVAL mcp73213_init ( mcp73213_t *ctx, mcp73213_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MCP73213_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_MASTER_SUCCESS )
    {
        return MCP73213_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MCP73213_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    spi_master_deselect_device( ctx->chip_select );

    return MCP73213_OK;
}

void mcp73213_generic_transfer 
( 
    mcp73213_t *ctx, 
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

void mcp73213_write_data ( mcp73213_t *ctx, uint8_t command, uint8_t write_data )
{
    uint8_t tmp;

    tmp = command;
    tmp |= MCP73213_SPI_CMD_WRITE;

    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    spi_master_write( &ctx->spi, &tmp, 1 );
    spi_master_write( &ctx->spi, &write_data, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t mcp73213_read_data ( mcp73213_t *ctx, uint8_t command )
{
    uint8_t w_temp;
    uint8_t r_temp;

    w_temp = command;
    w_temp |= MCP73213_SPI_CMD_READ;

    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    spi_master_write_then_read( &ctx->spi, &w_temp, 1, &r_temp, 1 );
    spi_master_deselect_device( ctx->chip_select );  

    return r_temp;
}

void mcp73213_set_current_output ( mcp73213_t *ctx, uint8_t out_data )
{
    uint8_t w_tmp;

    w_tmp = MCP73213_VOLATILE_WIPER_0;
    w_tmp |= MCP73213_SPI_CMD_WRITE;

    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    spi_master_write( &ctx->spi, &w_tmp, 1 );
    spi_master_write( &ctx->spi, &out_data, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t mcp73213_get_status ( mcp73213_t *ctx )
{
    uint8_t status_data;

    status_data = mcp73213_read_data( ctx, MCP73213_STATUS_REGISTER );

    return status_data;
}

float mcp73213_convert_output ( uint8_t value_adc, float v_ref )
{
    float result;

    result = ( ( float ) value_adc * v_ref ) / 255.00; 

    return result;
}

// ------------------------------------------------------------------------- END

