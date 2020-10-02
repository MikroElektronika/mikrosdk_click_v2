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

#include "adc7.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ADC7_DUMMY 0
#define VREF       4076

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc7_cfg_setup ( adc7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->drl = HAL_PIN_NC;
    cfg->pre = HAL_PIN_NC;
    cfg->mck = HAL_PIN_NC;
    cfg->bsy = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->dev_num_sampl = 4;
    cfg->dev_volt_ref = VREF;
    cfg->dev_value_lsb = 2147483647;
}

ADC7_RETVAL adc7_init ( adc7_t *ctx, adc7_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ADC7_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ADC7_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ADC7_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->pre, cfg->pre );
    digital_out_init( &ctx->mck, cfg->mck );

    // Input pins

    digital_in_init( &ctx->drl, cfg->drl );
    digital_in_init( &ctx->bsy, cfg->bsy );

    digital_out_low( &ctx->pre );

    digital_out_low( &ctx->mck );

    ctx->num_sampl = cfg->dev_num_sampl;
    ctx->volt_ref = cfg->dev_volt_ref;
    ctx->value_lsb = cfg->dev_value_lsb;

    return ADC7_OK;
}

void adc7_default_cfg ( adc7_t *ctx )
{
    adc7_preset_mode( ctx, ADC7_LOW_STATE );
    while( adc7_check_busy( ctx ) == ADC7_DEVICE_IS_BUSY );
    adc7_set_config( ctx, ADC7_GAIN_DISABLE, ADC7_DOWNSAMPL_FACT_64, ADC7_AVERAGING_FILT );  
    while( adc7_check_busy( ctx ) == ADC7_DEVICE_IS_BUSY );
}


uint8_t adc7_set_config ( adc7_t* ctx, uint8_t gain_config, 
                          uint8_t down_samp_factor, uint8_t filter_type )
{
    uint8_t temp_data[ 2 ];
    uint8_t count;

    if ( gain_config > 3 )
    {
        return ADC7_WRONG_GAIN_CONFIG;
    }
    if ( ( down_samp_factor < 2 ) || ( down_samp_factor > 14 ) )
    {
        return ADC7_WRONG_DOWNSAMPL_FACT;
    }
    if ( ( filter_type < 1 ) || ( filter_type > 7 ) )
    {
        return ADC7_WRONG_FILT_TYPE;
    }

    ctx->num_sampl = 1;
    for ( count = 0; count < down_samp_factor; count++ )
    {
        ctx->num_sampl *= 2;
    }

    switch ( gain_config )
    {
        case 0:
        {
            ctx->volt_ref = VREF;
            ctx->value_lsb = 2147483647;
            break;
        }
        case 1:
        {
            ctx->volt_ref = VREF;
            ctx->value_lsb = 1073741823;
            break;
        }
        case 2:
        {
            ctx->volt_ref = ( float )VREF * 0.8;
            ctx->value_lsb = 2147483647;
            break;
        }
        case 3:
        {
            ctx->volt_ref = ( float )VREF * 0.8;
            ctx->value_lsb = 1073741823;
            break;
        }
        default:
        {
            break;
        }
    }

    temp_data[ 0 ] = 0x80;
    temp_data[ 0 ] |= gain_config << 4;
    temp_data[ 0 ] |= down_samp_factor;
    temp_data[ 1 ] = filter_type << 4;

    if ( adc7_check_busy( ctx ) == ADC7_DEVICE_NOT_BUSY )
    { 
        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, temp_data, 2 );
        spi_master_deselect_device( ctx->chip_select ); 

        return ADC7_DEVICE_NOT_BUSY;
    }
    else
    {
        return ADC7_DEVICE_IS_BUSY;
    }
}

uint8_t adc7_check_data_ready ( adc7_t* ctx )
{
    if ( digital_in_read( &ctx->drl ) )
    {
        return ADC7_DATA_NOT_READY;
    }
    else
    {
        return ADC7_DATA_IS_READY;
    }
}

uint8_t adc7_check_busy ( adc7_t* ctx )
{
    if ( digital_in_read( &ctx->bsy ) )
    {
        return ADC7_DEVICE_IS_BUSY;
    }
    else
    {
        return ADC7_DEVICE_NOT_BUSY;
    }
}

void adc7_set_clock ( adc7_t* ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->mck );
    }
    else
    {
        digital_out_low( &ctx->mck );
    }
}

void adc7_preset_mode ( adc7_t* ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->pre );
    }
    else
    {
        digital_out_low( &ctx->pre );
    }
}

uint8_t adc7_read_bytes ( adc7_t* ctx, uint8_t n_bytes, uint8_t* data_out )
{
    if ( adc7_check_data_ready( ctx ) == ADC7_DATA_IS_READY )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_read( &ctx->spi, data_out, n_bytes );
        spi_master_deselect_device( ctx->chip_select ); 

        return ADC7_DATA_IS_READY;
    }
    else
    {
        return ADC7_DATA_NOT_READY;
    }
}

void adc7_start_conv_cycle ( adc7_t* ctx )
{
    uint16_t count;

    for ( count = 0; count < ctx->num_sampl; count++ )
    {
        adc7_set_clock( ctx, 1 );
        Delay_1us( );
        adc7_set_clock( ctx, 0 );
        Delay_1us( );

        while ( adc7_check_busy( ctx ) );
    }
}

uint8_t adc7_read_results ( adc7_t *ctx, int16_t* voltage )
{
    int32_t volt_data;
    double temp;
    uint8_t buff_data[ 4 ];
    uint8_t check_ready;

    check_ready = adc7_read_bytes( ctx, 4, buff_data );

    if ( check_ready )
    {
        return check_ready;
    }

    volt_data = buff_data[ 0 ];
    volt_data <<= 8;
    volt_data |= buff_data[ 1 ];
    volt_data <<= 8;
    volt_data |= buff_data[ 2 ];
    volt_data <<= 8;
    volt_data |= buff_data[ 3 ];

    temp = ( double )volt_data / ctx->value_lsb;
    temp *= ctx->volt_ref;
    *voltage = ( int16_t )temp;

    return check_ready;
}
// ------------------------------------------------------------------------- END

