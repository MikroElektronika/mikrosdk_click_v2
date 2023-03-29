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

#include "pot3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define POT3_DUMMY     0
#define ADC_RES        4095
#define VREF_2V        2047
#define VREF_3V3       3305

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pot3_cfg_setup ( pot3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->vo = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

POT3_RETVAL pot3_init ( pot3_t *ctx, pot3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = POT3_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return POT3_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, POT3_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Input pins

    digital_in_init( &ctx->vo, cfg->vo );

    return POT3_OK;

}

uint16_t pot3_read_adc ( pot3_t* ctx )
{
	uint16_t ret_val;

	uint8_t rx_buf[ 2 ];

	spi_master_select_device( ctx->chip_select );
	spi_master_read( &ctx->spi, rx_buf, 2 );
	spi_master_deselect_device( ctx->chip_select );  

	ret_val = rx_buf[ 0 ];
	ret_val <<= 8;
	ret_val |= rx_buf[ 1 ];

	ret_val &= 0x1FFF;
	ret_val >>= 1;
	
	return ret_val;
}

uint16_t pot3_read_avg_adc ( pot3_t* ctx, uint16_t n_samples )
{
	uint32_t res;
	uint16_t cnt;
	uint16_t ret_val;

	res = 0;

	for ( cnt = 0; cnt < n_samples; cnt++ )
	{
		res += pot3_read_adc( ctx );
		Delay_10us( );
	}

	ret_val = res / n_samples;

	return ret_val;
}

uint16_t pot3_get_vout ( pot3_t* ctx, uint8_t vref_sel, uint16_t n_samples )
{
	uint16_t adc_val;
	uint16_t vref_val;
	float res;

	if ( vref_sel == POT3_VREF_2V )
	{
		vref_val = VREF_2V;
	}
	else
	{
		vref_val = VREF_3V3;
	}

	adc_val = pot3_read_avg_adc( ctx, n_samples );

	res = adc_val;
	res /= ADC_RES;
	res *= vref_val;
	adc_val = res;

	return adc_val;
}

// ------------------------------------------------------------------------- END

