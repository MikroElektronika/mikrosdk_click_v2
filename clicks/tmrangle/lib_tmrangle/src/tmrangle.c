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

#include "tmrangle.h"
#include <math.h>
#include <stdlib.h>

// ------------------------------------------------------------- PRIVATE MACROS 

#define TMRANGLE_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void tmrangle_cfg_setup ( tmrangle_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

}

TMRANGLE_RETVAL tmrangle_init ( tmrangle_t *ctx, tmrangle_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = TMRANGLE_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return TMRANGLE_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, TMRANGLE_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
   
    return TMRANGLE_OK;
}



uint16_t tmrangle_read_channel_adc ( tmrangle_t* ctx, uint8_t channel )
{
    uint8_t r_buffer[ 2 ];
    uint8_t w_buffer[ 2 ];
    int16_t result;

    w_buffer[ 0 ] = 0x06;
    w_buffer[ 1 ] = 0x00;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, w_buffer, 1 );

    w_buffer[ 0 ] = channel;
    w_buffer[ 0 ] &= 0x03;
    w_buffer[ 0 ] <<= 6;
    w_buffer[ 1 ] = TMRANGLE_DUMMY;
    
    spi_master_set_default_write_data( &ctx->spi, w_buffer[ 0 ] );
    spi_master_read( &ctx->spi, &r_buffer[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, w_buffer[ 1 ] );
    spi_master_read( &ctx->spi, &r_buffer[ 1 ], 1 );

//     spi_master_write_then_read( &ctx->spi, w_buffer, 2, r_buffer, 2 );

    spi_master_deselect_device( ctx->chip_select ); 

    result = r_buffer[ 0 ];
    result &= 0x0F;
    result <<= 8;
    result |= r_buffer[ 1 ];

    return result;
}

void tmrangle_calculate_diff ( tmrangle_t* ctx )
{
    ctx->sensor_data.diff_y = ( int16_t )ctx->sensor_data.sin_p - ( int16_t )ctx->sensor_data.sin_n;
    ctx->sensor_data.diff_x = ( int16_t )ctx->sensor_data.cos_p - ( int16_t )ctx->sensor_data.cos_n;
    ctx->sensor_data.uncalibrated_angle = atan2( ( float )ctx->sensor_data.diff_y, ( float )ctx->sensor_data.diff_x );
}

void tmrangle_init_sensor_data ( tmrangle_t* ctx )
{
    ctx->sensor_data.cos_p = tmrangle_read_channel_adc( ctx, TMRANGLE_COS_P );
    ctx->sensor_data.cos_n = tmrangle_read_channel_adc( ctx, TMRANGLE_COS_N );
    ctx->sensor_data.sin_p = tmrangle_read_channel_adc( ctx, TMRANGLE_SIN_P );
    ctx->sensor_data.sin_n = tmrangle_read_channel_adc( ctx, TMRANGLE_SIN_N );
    tmrangle_calculate_diff( ctx );
}

void tmrangle_calib_calculate_one_direction ( tmrangle_t* ctx, 
                                              tmrangle_rotation_data_store_t* rotation_data_store )
{
    rotation_data_store->amplitude_x = ( ( float )rotation_data_store->max_cos -
                                         ( float )rotation_data_store->min_cos ) / 2.00;
    rotation_data_store->amplitude_y = ( ( float )rotation_data_store->max_sin -
                                         ( float )rotation_data_store->min_sin ) / 2.00;

    rotation_data_store->offset_x = ( ( float )rotation_data_store->max_cos +
                                      ( float )rotation_data_store->min_cos ) / 2.00;
    rotation_data_store->offset_y = ( ( float )rotation_data_store->max_sin + 
                                      ( float )rotation_data_store->min_sin ) / 2.00;

    rotation_data_store->max_cos = -0x07FF;
    rotation_data_store->min_cos = 0x07FF;
    rotation_data_store->max_sin = -0x07FF;
    rotation_data_store->min_sin = 0x07FF;

    rotation_data_store->x_45_corr = ( rotation_data_store->x_45 - rotation_data_store->offset_x )
                                     / rotation_data_store->amplitude_x;
    rotation_data_store->x_135_corr = ( rotation_data_store->x_135 - rotation_data_store->offset_x ) 
                                      / rotation_data_store->amplitude_x;

    rotation_data_store->y_45_corr = ( rotation_data_store->y_45 - rotation_data_store->offset_y ) 
                                     / rotation_data_store->amplitude_y;
    rotation_data_store->y_135_corr = ( rotation_data_store->y_135 - rotation_data_store->offset_y )
                                      / rotation_data_store->amplitude_y;

    rotation_data_store->magnitude_45 = sqrt( ( rotation_data_store->x_45_corr 
                                              * rotation_data_store->x_45_corr )
                                            + ( rotation_data_store->y_45_corr 
                                              * rotation_data_store->y_45_corr ) );
    rotation_data_store->magnitude_135 = sqrt( ( rotation_data_store->x_135_corr
                                               * rotation_data_store->x_135_corr ) 
                                             + ( rotation_data_store->y_135_corr 
                                               * rotation_data_store->y_135_corr ) );

    rotation_data_store->ortho_one_dir = 2.00 * atan2( ( rotation_data_store->magnitude_135 
                                                       - rotation_data_store->magnitude_45 ) 
                                                     , ( rotation_data_store->magnitude_135 
                                                       + rotation_data_store->magnitude_45 ) );

}

void tmrangle_calib_calculate_ortho ( tmrangle_calib_data_t* calib_param )
{
    calib_param->sin_ortho = sin( -( calib_param->rotation_data.ortho_one_dir ) );
    calib_param->cos_ortho = cos( -( calib_param->rotation_data.ortho_one_dir ) );
}

void tmrangle_init_calib_data ( tmrangle_t* ctx, tmrangle_calib_data_t* calib_param,
                                trigonometry_t *dev )
{
    calib_param->rotation_data.angle_135_found = 0;
    calib_param->rotation_data.angle_45_found = 0;
    calib_param->rotation_data.nr_valid_rotations = 0;

    calib_param->rotation_data.max_cos = dev->max_diff_cos;
    calib_param->rotation_data.min_cos = dev->min_diff_cos;
    calib_param->rotation_data.max_sin = dev->max_diff_sin;
    calib_param->rotation_data.min_sin = dev->min_diff_sin;

    calib_param->rotation_data.x_45 = dev->cos_45;
    calib_param->rotation_data.x_135 = dev->cos_135;

    calib_param->rotation_data.y_45 = dev->sin_45;
    calib_param->rotation_data.y_135 = dev->sin_135;

    tmrangle_calib_calculate_one_direction( ctx, &(calib_param->rotation_data) );
    tmrangle_calib_calculate_ortho( calib_param );
}

float tmrangle_get_calib_deff_angle (  tmrangle_t* ctx, tmrangle_calib_data_t* calib_param )
{
    float corr_x;
    float corr_y;
    float ortho_y;
    float diff_result;

    corr_x = ( ( float )ctx->sensor_data.diff_x - calib_param->rotation_data.offset_x )
                      / calib_param->rotation_data.amplitude_x;
    corr_y = ( ( float )ctx->sensor_data.diff_y - calib_param->rotation_data.offset_y )
                      / calib_param->rotation_data.amplitude_y;

    ortho_y = ( corr_y - ( corr_x * calib_param->sin_ortho ) ) / calib_param->cos_ortho;

    diff_result = atan2( ortho_y, corr_x );

    return diff_result;
}

float tmrangle_get_calib_angle ( tmrangle_t* ctx, tmrangle_calib_data_t* calib_param )
{
    float calib_angle;

    calib_angle = ( tmrangle_get_calib_deff_angle( ctx, calib_param ) ) * TMRANGLE_RAD2DEGFACTOR;

    return calib_angle;
}

void tmrangle_calib_find_min_max ( tmrangle_t* ctx, tmrangle_rotation_data_store_t* rotation_data_store )
{
    if ( ctx->sensor_data.diff_x < rotation_data_store->min_cos )
    {
        rotation_data_store->min_cos = ctx->sensor_data.diff_x;
    }

    if ( ctx->sensor_data.diff_x > rotation_data_store->max_cos )
    {
        rotation_data_store->max_cos = ctx->sensor_data.diff_x;
    }

    if ( ctx->sensor_data.diff_y < rotation_data_store->min_sin )
    {
        rotation_data_store->min_sin = ctx->sensor_data.diff_y;
    }

    if ( ctx->sensor_data.diff_y > rotation_data_store->max_sin )
    {
        rotation_data_store->max_sin = ctx->sensor_data.diff_y;
    }
}

void tmrangle_calib_one_direction_min_max ( tmrangle_t* ctx, tmrangle_rotation_data_store_t* rotation_data_store )
{
    tmrangle_calib_find_min_max( ctx, rotation_data_store );

    if ( ( ctx->sensor_data.uncalibrated_angle <= TMRANGLE_ANGLE45_H ) 
      && ( ctx->sensor_data.uncalibrated_angle >= TMRANGLE_ANGLE45_L ) )
    {
        rotation_data_store->x_45 = ( float )ctx->sensor_data.diff_x;
        rotation_data_store->y_45 = ( float )ctx->sensor_data.diff_y;
        rotation_data_store->angle_45_found = 1;
    }
    else if ( ( ctx->sensor_data.uncalibrated_angle <= TMRANGLE_ANGLE135_H ) 
           && ( ctx->sensor_data.uncalibrated_angle >= TMRANGLE_ANGLE135_L ) )
    {
        rotation_data_store->x_135 = ( float )ctx->sensor_data.diff_x;
        rotation_data_store->y_135 = ( float )ctx->sensor_data.diff_y;
        rotation_data_store->angle_135_found = 1;
    }
}

void tmrangle_calibration_find_param ( tmrangle_t* ctx, tmrangle_calib_data_t* calib_param )
{
    tmrangle_calib_one_direction_min_max( ctx, &calib_param->rotation_data );

    if ( calib_param->rotation_data.angle_135_found &&
         calib_param->rotation_data.angle_45_found )
    {
        calib_param->rotation_data.nr_valid_rotations++;
        calib_param->rotation_data.angle_45_found = 0;
        calib_param->rotation_data.angle_135_found = 0;
    }

    if ( calib_param->rotation_data.nr_valid_rotations > TMRANGLE_ROTATION_VALID )
    {
        calib_param->rotation_data.nr_valid_rotations ^= calib_param->rotation_data.nr_valid_rotations;
        tmrangle_calib_calculate_one_direction( ctx, &calib_param->rotation_data );
        tmrangle_calib_calculate_ortho( calib_param );
    }
}

// ------------------------------------------------------------------------- END

