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

#include "c3dhall6.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C3DHALL6_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static const float coeff_a[] = {
    33.058618473989548,
    58.655751569001961,
    32.390974856200445,
    5.8531952112628600,
    0.19523741936234277,
    -0.0024346033004411264
};
static const float coeff_b[] = {
    33.058618473992416,
    69.675291059524653,
    49.004348218216250,
    12.975578862709239,
    1.0
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static float c3dhall6_eval_poly ( float x, float code *d, int n );
static float c3dhall6_fabs ( float d );
static float c3dhall6_atan ( float f );
static float c3dhall6_atan2 ( float y, float  x );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c3dhall6_cfg_setup ( c3dhall6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 

    cfg->dev_aux_ref.aux_ref_adc_ch0 = 2048.0;
    cfg->dev_aux_ref.aux_ref_adc_ch1 = 2048.0;
    cfg->dev_aux_ref.aux_ref_adc_ch2 = 2048.0;
    cfg->dev_aux_ref.aux_ref_adc_ch3 = 2048.0;
    cfg->dev_aux_ref.aux_ref_volt = 3.3;
}

C3DHALL6_RETVAL c3dhall6_init ( c3dhall6_t *ctx, c3dhall6_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;
    
    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = C3DHALL6_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return C3DHALL6_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, C3DHALL6_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return C3DHALL6_OK;
}

void c3dhall6_generic_transfer ( c3dhall6_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void c3dhall6_spi_get ( c3dhall6_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t n_bytes )
{
    c3dhall6_generic_transfer( ctx, data_in, 1, data_out, n_bytes );
}

void c3dhall6_set_reference_values ( c3dhall6_t *ctx, float reference_voltage, float ref_adc_ch0, float ref_adc_ch1, float ref_adc_ch2, float ref_adc_ch3 )
{
    ctx->device_aux_ref.aux_ref_adc_ch0 = ref_adc_ch0;
    ctx->device_aux_ref.aux_ref_adc_ch0 = ref_adc_ch1;
    ctx->device_aux_ref.aux_ref_adc_ch2 = ref_adc_ch2;
    ctx->device_aux_ref.aux_ref_adc_ch3 = ref_adc_ch3;
    ctx->device_aux_ref.aux_ref_volt = reference_voltage;
}

void c3dhall6_get_adc_value ( c3dhall6_t *ctx, uint8_t channel_no, uint16_t *adc_value )
{
    ctx->in_buf[ 0 ] = 0x06;
    ctx->in_buf[ 1 ] = channel_no;
    c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );
    *adc_value = ( uint16_t )( ctx->out_buf[ 1 ] );
    *adc_value <<= 8;
    *adc_value |= ( uint16_t )( ctx->out_buf[ 2 ] );
}

void c3dhall6_get_volt( c3dhall6_t *ctx, uint8_t channel_no, float *channel_voltage )
{
    ctx->in_buf[ 0 ] = 0x06;
    ctx->in_buf[ 1 ] = channel_no;
    c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );
    ctx->aux_var = ( uint16_t )( ctx->out_buf[ 1 ] );
    ctx->aux_var <<= 8;
    ctx->aux_var |= ( uint16_t )( ctx->out_buf[ 2 ] );
    *channel_voltage = ( float )( ctx->aux_var );
    *channel_voltage *= ctx->device_aux_ref.aux_ref_volt;
    *channel_voltage /= 4096.0;
}

void c3dhall6_get_angle_deg ( c3dhall6_t *ctx, uint8_t die, float *angle_value )
{
    if ( die == C3DHALL6_DIE_A )
    {
        ctx->in_buf[ 0 ] = 0x06;
        ctx->in_buf[ 1 ] = C3DHALL6_CHANNEL_0;

        c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );
        
        ctx->device_aux_ch.aux_ch0 = ( uint16_t )( ctx->out_buf[ 1 ] );
        ctx->device_aux_ch.aux_ch0 <<= 8;
        ctx->device_aux_ch.aux_ch0 |= ( uint16_t )( ctx->out_buf[ 2 ] );
        
        ctx->in_buf[ 0 ] = 0x06;
        ctx->in_buf[ 1 ] = C3DHALL6_CHANNEL_1;

        c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );

        ctx->device_aux_ch.aux_ch1 = ( uint16_t )( ctx->out_buf[ 1 ] );
        ctx->device_aux_ch.aux_ch1 <<= 8;
        ctx->device_aux_ch.aux_ch1 |= ( uint16_t )( ctx->out_buf[ 2 ] );
        
        ctx->device_float_ch.aux_float_ch0 = ( float )( ctx->device_aux_ch.aux_ch0 ) - ctx->device_aux_ref.aux_ref_adc_ch0;
        ctx->device_float_ch.aux_float_ch1 = ( float )( ctx->device_aux_ch.aux_ch1 ) - ctx->device_aux_ref.aux_ref_adc_ch1;

        *angle_value = c3dhall6_atan2( ( float )( ctx->device_float_ch.aux_float_ch1 ), ( float )( ctx->device_float_ch.aux_float_ch0 ) );
        *angle_value *= 180.0;
        *angle_value /= SINGLE_PI_CONST;
    }
    else if ( die == C3DHALL6_DIE_B )
    {
        ctx->in_buf[ 0 ] = 0x06;
        ctx->in_buf[ 1 ] = C3DHALL6_CHANNEL_2;
        c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );
        ctx->device_aux_ch.aux_ch2 = ( uint16_t )( ctx->out_buf[ 1 ] );
        ctx->device_aux_ch.aux_ch2 <<= 8;
        ctx->device_aux_ch.aux_ch2 |= ( uint16_t )( ctx->out_buf[ 2 ] );
        
        ctx->in_buf[ 0 ] = 0x06;
        ctx->in_buf[ 1 ] = C3DHALL6_CHANNEL_3;
        c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );
        
        ctx->device_aux_ch.aux_ch3 = ( uint16_t )( ctx->out_buf[ 1 ] );
        ctx->device_aux_ch.aux_ch3 <<= 8;
        ctx->device_aux_ch.aux_ch3 |= ( uint16_t )( ctx->out_buf[ 2 ] );

        ctx->device_float_ch.aux_float_ch2 = ( float )( ctx->device_aux_ch.aux_ch2 ) - ctx->device_aux_ref.aux_ref_adc_ch2;
        ctx->device_float_ch.aux_float_ch3 = ( float )( ctx->device_aux_ch.aux_ch3 ) - ctx->device_aux_ref.aux_ref_adc_ch3;
        
        *angle_value = c3dhall6_atan2( ( float )( ctx->device_float_ch.aux_float_ch3 ), ( float )( ctx->device_float_ch.aux_float_ch2 ) );
        *angle_value *= 180.0;
        *angle_value /= SINGLE_PI_CONST;
    }
}

void c3dhall6_get_angle_rad ( c3dhall6_t *ctx, uint8_t die, float *angle_value )
{
    if ( die == C3DHALL6_DIE_A )
    {
        ctx->in_buf[0] = 0x06;
        ctx->in_buf[1] = C3DHALL6_CHANNEL_0;
        
        c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );
        
        ctx->device_aux_ch.aux_ch0 = ( uint16_t )( ctx->out_buf[ 1 ] );
        ctx->device_aux_ch.aux_ch0 <<= 8;
        ctx->device_aux_ch.aux_ch0 |= ( uint16_t )( ctx->out_buf[ 2 ] );

        ctx->in_buf[ 0 ] = 0x06;
        ctx->in_buf[ 1 ] = C3DHALL6_CHANNEL_1;
        c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );
        
        ctx->device_aux_ch.aux_ch1 = ( uint16_t )( ctx->out_buf[ 1 ] );
        ctx->device_aux_ch.aux_ch1 <<= 8;
        ctx->device_aux_ch.aux_ch1 |= ( uint16_t )( ctx->out_buf[ 2 ] );

        ctx->device_float_ch.aux_float_ch0 = ( float )( ctx->device_aux_ch.aux_ch0 ) - ctx->device_aux_ref.aux_ref_adc_ch0;
        ctx->device_float_ch.aux_float_ch1 = ( float )( ctx->device_aux_ch.aux_ch1 ) - ctx->device_aux_ref.aux_ref_adc_ch1;

        *angle_value = c3dhall6_atan2( ( float )( ctx->device_float_ch.aux_float_ch1 ), ( float )( ctx->device_float_ch.aux_float_ch0 ) );
    }
    else if ( die == C3DHALL6_DIE_B )
    {
        ctx->in_buf[ 0 ] = 0x06;
        ctx->in_buf[ 1 ] = C3DHALL6_CHANNEL_2;
        c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );
        
        ctx->device_aux_ch.aux_ch2 = ( uint16_t )( ctx->out_buf[ 1 ] );
        ctx->device_aux_ch.aux_ch2 <<= 8;
        ctx->device_aux_ch.aux_ch2 |= ( uint16_t )( ctx->out_buf[ 2 ] );

        ctx->in_buf[ 0 ] = 0x06;
        ctx->in_buf[ 1 ] = C3DHALL6_CHANNEL_3;
        c3dhall6_spi_get( ctx, ctx->in_buf, ctx->out_buf, 5 );
        
        ctx->device_aux_ch.aux_ch3 = ( uint16_t )( ctx->out_buf[ 1 ] );
        ctx->device_aux_ch.aux_ch3 <<= 8;
        ctx->device_aux_ch.aux_ch3 |= ( uint16_t )( ctx->out_buf[ 2 ] );

        ctx->device_float_ch.aux_float_ch2 = ( float )( ctx->device_aux_ch.aux_ch2 ) - ctx->device_aux_ref.aux_ref_adc_ch2;
        ctx->device_float_ch.aux_float_ch3 = ( float )( ctx->device_aux_ch.aux_ch3 ) - ctx->device_aux_ref.aux_ref_adc_ch3;

        *angle_value = c3dhall6_atan2( ( float )( ctx->device_float_ch.aux_float_ch3 ), ( float )( ctx->device_float_ch.aux_float_ch2 ) );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float c3dhall6_eval_poly ( float x, float code *d, int n )
{
    float res;

    res = d[ n ];
    while( n )
    {
        res = x * res + d[ --n ];
    }
    return res;
}

static float c3dhall6_fabs ( float d )
{
    if ( d < 0.0 )
    {
        return -d;
    }
       
    return d;
}

static float c3dhall6_atan ( float f )
{
    unsigned char recip;
    float val, val_squared;

    val = c3dhall6_fabs( f );

    if ( val == 0.0 )
    {
        return 0.0;
    }

    if ( recip = ( val > 1.0 ) )
    {
        val = 1.0 / val;
    }
 
    val_squared = val * val;
    val *= c3dhall6_eval_poly( val_squared, coeff_a, 5 );
    val /= c3dhall6_eval_poly( val_squared, coeff_b, 4 );
    if ( recip )
    {
        val = HALF_PI_CONST - val;
    }    
    val = f < 0.0 ? -val : val;

    return val;
}

static float c3dhall6_atan2 ( float y, float  x )
{
    float v;

    if ( c3dhall6_fabs( y ) >= c3dhall6_fabs( x ) )
    {
        v = c3dhall6_atan( x/y );
        if ( y < 0.0 )
        {
            if ( x >= 0.0 )
            {
                v += SINGLE_PI_CONST;
            }   
            else
            {
                v -= SINGLE_PI_CONST;
            }
            return v;
        }      
    }
    v = -c3dhall6_atan( y/x );
    if ( x < 0. )
    {
        v -= HALF_PI_CONST;
    }
    else
    {
        v += HALF_PI_CONST;
    }
    return v;
}

// ------------------------------------------------------------------------- END

