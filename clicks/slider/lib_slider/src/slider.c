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

#include "slider.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define SLIDER_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void slider_cfg_setup ( slider_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->oe = HAL_PIN_NC;
    cfg->csl = HAL_PIN_NC;

    cfg->spi_speed = 400000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

SLIDER_RETVAL slider_init ( slider_t *ctx, slider_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = SLIDER_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return SLIDER_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, SLIDER_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->oe, cfg->oe );
    digital_out_init( &ctx->csl, cfg->csl );
    //digital_in_init( &ctx->miso, cfg->miso );
    
    slider_enable_led_output( ctx, 0 );

    return SLIDER_OK;

}

void slider_default_cfg ( slider_t *ctx )
{
    slider_enable_led_output( ctx, 0 );
}


uint32_t slider_read_adc ( slider_t *ctx )
{
    uint8_t buff_out[ 4 ];
    uint32_t ret_val;
    uint8_t i;

    spi_master_select_device( ctx->chip_select );
    Delay_22us( );
    spi_master_read( &ctx->spi, buff_out, 4 );
    spi_master_deselect_device( ctx->chip_select );   
    Delay_22us( );

    ret_val = buff_out[ 0 ];
    ret_val <<= 8;
    ret_val |= buff_out[ 1 ];
    ret_val <<= 8;
    ret_val |= buff_out[ 2 ];
    ret_val <<= 1;
    buff_out[ 3 ] >>= 7;
    ret_val |= buff_out[ 3 ];
    ret_val &= 0x003FFFFF;
    
    return ret_val;
}

uint32_t slider_read_adc_and_ready ( slider_t *ctx )
{
    uint32_t ret_val = 0;
    uint8_t check_flag = 1;
    
    //while( check_flag )
    //{
    //    spi_master_select_device( ctx->chip_select );
    //    check_flag = digital_in_read( &ctx->miso );
    //    spi_master_deselect_device( ctx->chip_select );  
    //}
    
    ret_val = slider_read_adc( ctx );
    
    return ret_val;
}

void slider_enable_led_output ( slider_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->oe, state );
}

void slider_enable_output_laches ( slider_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->csl, state );
}

uint32_t slider_write_output ( slider_t *ctx )
{
    uint32_t adc_value = 0;
    uint8_t res = 0;
    uint16_t temp = 0;
    uint8_t cnt = 0;
    uint8_t output_buffer[ 2 ];
    uint8_t i;
    
    adc_value = slider_read_adc( ctx );

    res = adc_value / 65457;
    
    for( cnt = 0; cnt < res; cnt++ )
    {
        if(cnt == 0)
        {
            temp |= 1;
        }else
        {
            temp = ( temp << 1 ) | 1;
        }
    }
    
    output_buffer[ 0 ] = temp >> 8;
    output_buffer[ 1 ] = temp;
    
    Delay_10ms();
    spi_master_select_device( ctx->chip_select );
    slider_enable_output_laches( ctx, 1 );
    Delay_22us();
    spi_master_write( &ctx->spi, output_buffer, 2 );
    spi_master_deselect_device( ctx->chip_select );   
    slider_enable_output_laches( ctx, 0 );
    Delay_22us();
    
    
    return adc_value;
}

// ------------------------------------------------------------------------- END

