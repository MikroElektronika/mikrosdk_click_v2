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
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void gmrangle_generic_transfer ( gmrangle_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

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
 * TLE5012 GMR-Based Angular Sensor on the GMR Angle click board.
*/
float dev_calculate_angle_speed ( float ang_range, int16_t angle_speed_val, uint16_t fir_md, uint16_t prediction_val );

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

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

GMRANGLE_RETVAL gmrangle_init ( gmrangle_t *ctx, gmrangle_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = GMRANGLE_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return GMRANGLE_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, GMRANGLE_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->css, cfg->css );
    digital_out_init( &ctx->ifc, cfg->ifc );

    // Input pins

    digital_in_init( &ctx->ifa, cfg->ifa );
    digital_in_init( &ctx->ifb, cfg->ifb );

    return GMRANGLE_OK;
}

uint16_t gmrangle_read_data ( gmrangle_t *ctx, uint8_t reg )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    uint16_t result;

    tx_buf[ 0 ] = reg & GMRANGLE_GET_BIT_5_4;
    tx_buf[ 0 ] >>= 4;
    tx_buf[ 0 ] |= GMRANGLE_READ_SENSOR;
    tx_buf[ 1 ] = reg & GMRANGLE_GET_BIT_3_0;
    tx_buf[ 1 ] <<= 4;
    tx_buf[ 1 ] |= 0x02;

    digital_out_high( &ctx->css );
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    digital_out_low( &ctx->css );
    
    spi_master_read(&ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );      

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

void gmrangle_write_data ( gmrangle_t *ctx, uint8_t reg, uint16_t tx_data )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = reg & GMRANGLE_GET_BIT_5_4;
    tx_buf[ 0 ] >>= 4;
    tx_buf[ 0 ] |= GMRANGLE_WRITE_SENSOR;
    tx_buf[ 1 ] = reg & GMRANGLE_GET_BIT_3_0;
    tx_buf[ 1 ] <<= 4;
    tx_buf[ 1 ] |= 0x02;

    digital_out_high( &ctx->css );
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    digital_out_low( &ctx->css );
    
    tx_buf[ 0 ] = ( uint8_t ) ( tx_data >> 8 );
    tx_buf[ 0 ] <<= 8;
    tx_buf[ 1 ] = ( uint8_t ) ( tx_data & 0x00FF );
    
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );    
}

uint16_t gmrangle_get_status ( gmrangle_t *ctx )
{
    uint16_t result;

    result = gmrangle_read_data( ctx, GMRANGLE_REG_STAT );

    return result;
}

void gmrangle_set_activation_status ( gmrangle_t *ctx, uint16_t a_data )
{
    a_data &= 0x02FF;

    gmrangle_write_data( ctx, GMRANGLE_REG_ACSTAT, a_data );
}

int16_t gmrangle_get_angle_speed_value ( gmrangle_t *ctx )
{
    uint16_t result;

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
    uint16_t fir_md_val;
    uint16_t int_mode_2_prediction;
    uint16_t raw_angle_range;
    int16_t angle_speed_data;
    float angle_range;
    uint16_t tmp;

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

    *final_angle_speed = dev_calculate_angle_speed( angle_range, angle_speed_data, fir_md_val, int_mode_2_prediction );
}

float gmrangle_get_angle_range ( gmrangle_t *ctx )
{
    uint16_t read_data;
    float angle_range;
    read_data = 0;

    read_data = gmrangle_read_data( ctx, GMRANGLE_REG_MOD_2 );

    read_data &= GMRANGLE_GET_BIT_14_4;
    read_data >>= 4;
    angle_range = GMRANGLE_ANGLE_360_VAL * ( GMRANGLE_POW_2_7 / ( float ) ( read_data ) );

    return angle_range;
}

int16_t gmrangle_get_num_revolutions ( gmrangle_t *ctx )
{
    int16_t read_data;
    read_data = 0;

    read_data = ( int16_t ) gmrangle_read_data( ctx, GMRANGLE_REG_AREV );
    read_data &= GMRANGLE_DELETE_7BITS;

    if ( read_data & GMRANGLE_CHECK_BIT_9 )
    {
        read_data -= GMRANGLE_CHANGE_UNIT_TO_INT_9;
    }

    return read_data;
}

int16_t gmrangle_get_angle_value ( gmrangle_t *ctx )
{
    int16_t read_data;

    read_data = gmrangle_read_data( ctx, GMRANGLE_REG_AVAL );
    
    if ( read_data > 0x8000 )
    {
        read_data &= GMRANGLE_DELETE_BIT_15;

        if ( read_data > GMRANGLE_MAX_BIT_14 )
        {
            read_data &= GMRANGLE_MAX_BIT_14;
            read_data <<= 2;
            read_data /= 4;
        }
    }

    return read_data;
}

float gmrangle_calculate_angle ( gmrangle_t *ctx )
{
    float c_angle;
    int16_t read_data;

    read_data = gmrangle_get_angle_value( ctx );

    c_angle = ( float ) read_data;
    c_angle *= GMRANGLE_ANGLE_COEFF_CALC;

    return c_angle;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void gmrangle_generic_transfer ( gmrangle_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

float dev_calculate_angle_speed ( float ang_range, int16_t angle_speed_val, uint16_t fir_md, uint16_t prediction_val )
{
    float final_angle_speed;
    float microsec_to_sec;
    float fir_md_val;

    microsec_to_sec = 0.000001;

    if ( fir_md == 1 )
    {
        fir_md_val = 42.7;
    }
    else if ( fir_md == 0 )
    {
        fir_md_val = 21.3;
    }
    else if ( fir_md == 2 )
    {
        fir_md_val = 85.3;
    }
    else if ( fir_md == 3 )
    {
        fir_md_val = 170.6;
    }
    else
    {
        fir_md_val = 0;
    }

    final_angle_speed = ( ( ang_range / GMRANGLE_POW_2_15 ) * ( ( float ) angle_speed_val ) ) / ( ( ( float ) prediction_val ) * fir_md_val * microsec_to_sec );

    return final_angle_speed;
}

// ------------------------------------------------------------------------- END

