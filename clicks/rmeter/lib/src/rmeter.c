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

#include "rmeter.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define RMETER_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void rmeter_generic_transfer 
( 
    rmeter_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rmeter_cfg_setup ( rmeter_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->an = HAL_PIN_NC;
    cfg->s3 = HAL_PIN_NC;
    cfg->s1 = HAL_PIN_NC;
    cfg->s2 = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

RMETER_RETVAL rmeter_init ( rmeter_t *ctx, rmeter_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = RMETER_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return RMETER_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, RMETER_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->s3, cfg->s3 );
    digital_out_init( &ctx->s1, cfg-> s1 );
    digital_out_init( &ctx->s2, cfg->s2 );

    // Input pins

    digital_in_init( &ctx->an,  cfg->an  );

    return RMETER_OK;
}

void rmeter_range_s1 ( rmeter_t *ctx, uint8_t state )
{
    if ( state == RMETER_SELECT )
	{
        digital_out_high( &ctx->s1 );
	}
	else if ( state == RMETER_DESELECT )
	{
        digital_out_low( &ctx->s1 );
	}
}

void rmeter_range_s2 ( rmeter_t *ctx, uint8_t state )
{
    if ( state == RMETER_SELECT )
	{
        digital_out_high( &ctx->s2 );
    }
	else if ( state == RMETER_DESELECT )
	{
        digital_out_low( &ctx->s2 );
    }
}

void rmeter_range_s3 ( rmeter_t *ctx, uint8_t state )
{
    if ( state == RMETER_SELECT )
	{
        digital_out_high( &ctx->s3 );
    }
	else if ( state == RMETER_DESELECT )
	{
        digital_out_low( &ctx->s3 );
    }
}

uint16_t rmeter_read_data ( rmeter_t *ctx )
{
    uint8_t rx_buf[ 2 ];
	uint16_t result;

    rmeter_generic_transfer( ctx, 0, 0, rx_buf, 2 );
    
	result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
	
    return result;
}

uint16_t rmeter_get_volage ( rmeter_t *ctx )
{
    uint16_t result = 0;

    result = rmeter_read_data( ctx );
    result &= RMETER_FILTER_USEFULL_DATA;
    result >>= 1;

    return result;
}

float rmeter_avg_volt ( rmeter_t *ctx )
{
    uint16_t temp;
    uint16_t sum = 0;
    float average;
    float result;
    uint8_t n_cnt;
    
    for ( n_cnt = 0; n_cnt < RMETER_DATA_SAMPLE_NUM; n_cnt++ )
    {
        temp = rmeter_get_volage( ctx );
        Delay_10ms();
        sum = sum + temp;
    }

    average = sum / RMETER_DATA_SAMPLE_NUM;
    result = average / 2;

    return result;
}

float rmeter_calc ( rmeter_t *ctx, uint32_t res_filt )
{
    float gain;
    float voltage;
    float rsem;
    uint32_t resx;

    resx = res_filt;

    voltage = rmeter_avg_volt( ctx );
    gain = ( voltage / RMETER_GAIN_CALC_CONST );
    gain = gain - 1;

    rsem = resx * gain;
    rsem = rsem - RMETER_RANGE_VALUE;

    return rsem;
}

float rmeter_get_ohms ( rmeter_t *ctx )
{
    float voltage;
    uint32_t resx;
    float result;

    resx = RMETER_RANGE_BASE_VALUE_1;
    rmeter_range_s1 ( ctx, RMETER_SELECT );
    rmeter_range_s2 ( ctx, RMETER_DESELECT );
    rmeter_range_s3 ( ctx, RMETER_DESELECT );

    voltage = voltage = rmeter_avg_volt( ctx );

    if ( voltage < RMETER_RANGE_VALUE )
    {
        result = rmeter_calc( ctx, resx );
        return result;
    }
    else if ( voltage > RMETER_RANGE_VALUE )
    {
        resx = RMETER_RANGE_BASE_VALUE_2;
        rmeter_range_s1 ( ctx, RMETER_DESELECT );
        rmeter_range_s2 ( ctx, RMETER_SELECT );
        rmeter_range_s3 ( ctx, RMETER_DESELECT );

        voltage = rmeter_avg_volt( ctx );

        if ( voltage < RMETER_RANGE_VALUE )
        {
            result = rmeter_calc( ctx, resx );
            return result;
        }
    }
    if ( voltage > RMETER_RANGE_VALUE )
    {
        resx = RMETER_RANGE_BASE_VALUE_3;
        rmeter_range_s1 ( ctx, RMETER_DESELECT );
        rmeter_range_s2 ( ctx, RMETER_DESELECT );
        rmeter_range_s3 ( ctx, RMETER_SELECT );

        voltage = rmeter_avg_volt( ctx );

        if ( voltage < RMETER_RANGE_VALUE )
        {
            result =  rmeter_calc( ctx, resx );
            if( result > RMETER_RANGE_VALUE_MAX )
            {
                resx = RMETER_RANGE_BASE_VALUE_0;
                result =  rmeter_calc( ctx, resx );
                return result;
            }
            return result;
        }
    }
    if ( voltage > RMETER_RANGE_VALUE )
    return RMETER_OVER_RANGE;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void rmeter_generic_transfer 
( 
    rmeter_t *ctx, 
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

// ------------------------------------------------------------------------- END

