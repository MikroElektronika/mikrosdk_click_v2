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

#include "boost.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BOOST_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void boost_cfg_setup ( boost_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->cs2 = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

BOOST_RETVAL boost_init ( boost_t *ctx, boost_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = BOOST_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->cs2, cfg->cs2 );

    ctx->chip_select = cfg->cs;
    ctx->an_chip_select = cfg->cs2;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return BOOST_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BOOST_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_deselect_device( ctx->an_chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->en, cfg->en );

    return BOOST_OK;
}

void boost_default_cfg ( boost_t *ctx )
{
    boost_set_configuration( ctx, BOOST_EXT_POWER );
}

void boost_generic_transfer ( boost_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );    
}

void boost_write_byte ( boost_t *ctx, uint16_t write_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = ( uint8_t ) ( ( write_data >> 8 ) & 0x0F );
    w_buffer[ 0 ] |= BOOST_START_COMMAND;
    w_buffer[ 1 ] = ( uint8_t ) write_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, w_buffer, 2 );
    spi_master_deselect_device( ctx->chip_select );    
}

uint32_t boost_read_byte ( boost_t *ctx )
{
    uint8_t  r_buffer[ 3 ];
    uint32_t result;
    
    result = 0;

    digital_out_low( &ctx->cs2 );
    Delay_10us();
    digital_out_high( &ctx->cs2 );
    Delay_10us();

    spi_master_select_device( ctx->an_chip_select );
    spi_master_read( &ctx->spi, r_buffer, 3 );
    spi_master_deselect_device( ctx->an_chip_select );  

    result = r_buffer[ 0 ];
    result <<= 8;
    result |= r_buffer[ 1 ];
    result <<= 8;
    result |= r_buffer[ 2 ];

    return result;
}

void boost_set_configuration ( boost_t *ctx, uint8_t pwr_src )
{
    uint8_t power_source;

    if ( pwr_src == BOOST_INT_POWER || pwr_src == BOOST_EXT_POWER )
        power_source = pwr_src;
    else
        power_source = BOOST_INT_POWER;
    
    boost_write_byte( ctx, 0x0FFF );
}

float boost_get_voltage ( boost_t *ctx )
{
    uint16_t tmp_val;
    uint32_t read_val;
    float result;

    read_val = boost_read_byte( ctx );
    
    tmp_val = ( ( read_val * 4096 ) / 4194304 );
    
    result = ( ( float ) tmp_val ) * ( ( BOOST_ADC_R8 + BOOST_ADC_R7 ) / BOOST_ADC_R8 );
    
    return result;
}

void boost_set_voltage ( boost_t *ctx, uint16_t value )
{
    uint16_t read_val;
    uint16_t current_dac;

    current_dac = 0x0FFF;

    read_val = boost_get_voltage( ctx );

    if ( read_val != value && value < BOOST_HI_LIMIT)
    {
        if ( read_val > value )
        {
            while ( read_val <= value )
            {
                current_dac += 10;
                boost_write_byte( ctx, current_dac );

                read_val = boost_get_voltage( ctx );

                Delay_10us( );
            }
        }
        else
   
        {
            while ( read_val >= value )
            {
                current_dac -= 10;

                boost_write_byte( ctx, --current_dac );

                read_val = boost_get_voltage( ctx );

                Delay_10us( );
            }
        }
    }
}

void boost_enable ( boost_t *ctx )
{
    digital_out_high( &ctx->en );
}

void boost_disable ( boost_t *ctx )
{
    digital_out_low( &ctx->en );
}

// ------------------------------------------------------------------------- END

