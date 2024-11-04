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

#include "gmrangle.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define GMRANGLE_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Calculate the angle speed function
 *
 * @param ang_range                  float value of the angular range
 * @param angle_speed_val            16-bit signed angle speed value
 * @param fir_md                     firMD
 * @param prediction_val             16-bit prediction value
 *
 * @return
 * float value of the angle speed
 *
 * @description Function calculate the angle speed of the
 * TLE5012 GMR-Based Angular Sensor on the GMR Angle Click board.
*/
static float gmrangle_calc_angle_speed ( float ang_range, int16_t angle_speed_val, 
                                         uint16_t fir_md, uint16_t prediction_val );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gmrangle_cfg_setup ( gmrangle_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ifa = HAL_PIN_NC;
    cfg->css = HAL_PIN_NC;
    cfg->ifc = HAL_PIN_NC;
    cfg->ifb = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

err_t gmrangle_init ( gmrangle_t *ctx, gmrangle_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, GMRANGLE_DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    // Output pins 
    digital_out_init( &ctx->css, cfg->css );

    // Input pins
    digital_in_init( &ctx->ifa, cfg->ifa );
    digital_in_init( &ctx->ifb, cfg->ifb );
    digital_in_init( &ctx->ifc, cfg->ifc );

    return GMRANGLE_OK;
}

uint16_t gmrangle_read_data ( gmrangle_t *ctx, uint8_t reg )
{
    uint8_t tx_buf[ 2 ] = { 0 };
    uint8_t rx_buf[ 2 ] = { 0 };

    tx_buf[ 0 ] = GMRANGLE_READ_SENSOR | ( ( reg & GMRANGLE_GET_BIT_5_4 ) >> 4 );
    tx_buf[ 1 ] = ( ( reg & GMRANGLE_GET_BIT_3_0 ) << 4 ) | 0x02;

    digital_out_high( &ctx->css );
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    digital_out_low( &ctx->css );
    
    spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );      

    return ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
}

void gmrangle_write_data ( gmrangle_t *ctx, uint8_t reg, uint16_t tx_data )
{
    uint8_t tx_buf[ 4 ] = { 0 };

    tx_buf[ 0 ] = ( ( reg & GMRANGLE_GET_BIT_5_4 ) >> 4 );
    tx_buf[ 1 ] = ( ( reg & GMRANGLE_GET_BIT_3_0 ) << 4 ) | 0x02;
    tx_buf[ 2 ] = ( uint8_t ) ( tx_data >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) ( tx_data & 0xFF );

    digital_out_high( &ctx->css );
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 4 );
    digital_out_low( &ctx->css );
    spi_master_deselect_device( ctx->chip_select );    
}

uint16_t gmrangle_get_status ( gmrangle_t *ctx )
{
    return gmrangle_read_data( ctx, GMRANGLE_REG_STAT );
}

void gmrangle_set_act_status ( gmrangle_t *ctx, uint16_t a_data )
{
    gmrangle_write_data( ctx, GMRANGLE_REG_ACSTAT, a_data & 0x02FF );
}

int16_t gmrangle_get_angle_speed_value ( gmrangle_t *ctx )
{
    uint16_t result = 0;

    result = gmrangle_read_data( ctx, GMRANGLE_REG_ASPD );

    result &= 0x7FFF;

    if ( result & GMRANGLE_CHECK_BIT_14 )
    {
        result -= GMRANGLE_CHANGE_UINT_TO_INT_15;
    }

    return result;
}

void gmrangle_get_angle_speed ( gmrangle_t *ctx, float *final_angle_speed, int16_t *angle_speed_val )
{
    uint16_t fir_md_val = 0;
    uint16_t int_mode_2_prediction = 0;
    uint16_t raw_angle_range = 0;
    int16_t angle_speed_data = 0;
    float angle_range = 0.0f;
    uint16_t tmp = 0;

    *angle_speed_val = gmrangle_get_angle_speed_value( ctx );
    *angle_speed_val &= GMRANGLE_DELETE_BIT_15;

    if ( *angle_speed_val & GMRANGLE_CHECK_BIT_14 )
    {
        *angle_speed_val -= GMRANGLE_CHANGE_UINT_TO_INT_15;
    }
    
    angle_speed_data = *angle_speed_val;

    tmp = gmrangle_read_data( ctx, GMRANGLE_REG_MOD_1 );

    fir_md_val = tmp;
    fir_md_val >>= 14;

    tmp = gmrangle_read_data( ctx, GMRANGLE_REG_MOD_2 );

    int_mode_2_prediction = tmp;

    if ( int_mode_2_prediction & 0x0004 )
    {
        int_mode_2_prediction = 3;
    }
    else
    {
        int_mode_2_prediction = 2;
    }

    raw_angle_range = tmp;
    raw_angle_range &= GMRANGLE_GET_BIT_14_4;
    raw_angle_range >>= 4;
    angle_range = GMRANGLE_ANGLE_360_VAL * ( GMRANGLE_POW_2_7 / ( float ) ( raw_angle_range ) );

    *final_angle_speed = gmrangle_calc_angle_speed( angle_range, angle_speed_data, fir_md_val, int_mode_2_prediction );
}

float gmrangle_get_angle_range ( gmrangle_t *ctx )
{
    uint16_t read_data = 0;
    float angle_range = 0.0f;

    read_data = gmrangle_read_data( ctx, GMRANGLE_REG_MOD_2 );

    read_data &= GMRANGLE_GET_BIT_14_4;
    read_data >>= 4;
    angle_range = GMRANGLE_ANGLE_360_VAL * ( GMRANGLE_POW_2_7 / ( float ) ( read_data ) );

    return angle_range;
}

int16_t gmrangle_get_num_revolutions ( gmrangle_t *ctx )
{
    int16_t read_data = 0;

    read_data = ( int16_t ) gmrangle_read_data( ctx, GMRANGLE_REG_AREV );
    read_data &= GMRANGLE_DELETE_7BITS;

    if ( read_data & GMRANGLE_CHECK_BIT_9 )
    {
        read_data -= GMRANGLE_CHANGE_UNIT_TO_INT_9;
    }

    return read_data;
}

uint16_t gmrangle_get_angle_value ( gmrangle_t *ctx )
{
    uint16_t read_data = 0;

    read_data = gmrangle_read_data( ctx, GMRANGLE_REG_AVAL );
    
    return read_data & GMRANGLE_DATA_RESOLUTION;
}

float gmrangle_calculate_angle ( gmrangle_t *ctx )
{
    uint16_t read_data = 0;
    read_data = gmrangle_get_angle_value( ctx );
    return ( float ) read_data * GMRANGLE_ANGLE_360_VAL / GMRANGLE_DATA_RESOLUTION;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float gmrangle_calc_angle_speed ( float ang_range, int16_t angle_speed_val, 
                                         uint16_t fir_md, uint16_t prediction_val )
{
    float final_angle_speed = 0.0f;
    float microsec_to_sec = 0.0f;
    float fir_md_val = 0.0f;

    microsec_to_sec = 0.000001f;

    if ( 1 == fir_md )
    {
        fir_md_val = 42.7f;
    }
    else if ( 0 == fir_md )
    {
        fir_md_val = 21.3f;
    }
    else if ( 2 == fir_md )
    {
        fir_md_val = 85.3f;
    }
    else if ( 3 == fir_md )
    {
        fir_md_val = 170.6f;
    }
    else
    {
        fir_md_val = 0.0f;
    }

    final_angle_speed = ( ( ang_range / GMRANGLE_POW_2_15 ) * ( ( float ) angle_speed_val ) ) / 
                        ( ( ( float ) prediction_val ) * fir_md_val * microsec_to_sec );

    return final_angle_speed;
}

// ------------------------------------------------------------------------- END

