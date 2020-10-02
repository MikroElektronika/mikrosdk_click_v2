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

#include "digipot.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DIGIPOT_DUMMY 0

#define DIGIPOT_VREF_3V3                     3.30
#define DIGIPOT_VREF_5V                      5.00
#define DIGIPOT_CON_CALC_VAL                 255.00

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void digipot_cfg_setup ( digipot_cfg_t *cfg )
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

DIGIPOT_RETVAL digipot_init ( digipot_t *ctx, digipot_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = DIGIPOT_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return DIGIPOT_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, DIGIPOT_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return DIGIPOT_OK;
}

void digipot_generic_transfer ( digipot_t *ctx, uint8_t *wr_buf, 
                                uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

// Set 8-bit wiper positions
void digipot_set_wiper_positions ( digipot_t *ctx, uint8_t wiper_pos )
{
    uint8_t write_buf[ 4 ];

    write_buf[ 0 ] = DIGIPOT_VOLATILE_WIPER_0;
    write_buf[ 1 ] = wiper_pos;
    write_buf[ 2 ] = DIGIPOT_DATA_WRITE_CMD;
    write_buf[ 3 ] = wiper_pos;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );   
}

// Convert ADC value to volatage
float digipot_convert_output ( uint16_t adc_val, float v_ref )
{
    float result;

    result = ( float ) adc_val;
    result *= v_ref;
    result/= DIGIPOT_CON_CALC_VAL;

    return result;
}

// ------------------------------------------------------------------------- END

