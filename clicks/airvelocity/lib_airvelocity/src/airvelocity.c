/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file airvelocity.c
 * @brief Air Velocity Click Driver.
 */

#include "airvelocity.h"

void airvelocity_cfg_setup ( airvelocity_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AIRVELOCITY_DEVICE_ADDRESS;
}

err_t airvelocity_init ( airvelocity_t *ctx, airvelocity_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t airvelocity_read_output ( airvelocity_t *ctx, uint16_t *out_counts )
{
    uint8_t data_buf[ 5 ] = { 0 };
    if ( I2C_MASTER_ERROR == i2c_master_read ( &ctx->i2c, data_buf, 5 ) )
    {
        return AIRVELOCITY_ERROR;
    }
    uint16_t checksum = 0;
    checksum = data_buf[ 1 ] + data_buf[ 2 ] + data_buf[ 3 ] + data_buf[ 4 ];
    if ( ( checksum + data_buf[ 0 ] ) & 0xFF )
    {
        return AIRVELOCITY_ERROR;
    }
    *out_counts = ( ( uint16_t ) ( data_buf[ 1 ] & 0x0F ) << 8 ) | data_buf[ 2 ];
    return AIRVELOCITY_OK;
}

float airvelocity_convert_counts_to_mps ( uint16_t out_counts )
{
    // Output data MPS and counts arrays from the datasheet for FS3000-1005
    static float data_mps[ 9 ]      =  {   0, 1.07, 2.01, 3.00, 3.97, 4.96, 5.98, 6.99, 7.23 };
    static uint16_t data_count[ 9 ] =  { 409,  915, 1522, 2066, 2523, 2908, 3256, 3572, 3686 };
    if ( out_counts <= data_count[ 0 ] ) 
    {
        return data_mps[ 0 ];
    }
    if ( out_counts >= data_count[ 8 ] ) 
    {
        return data_mps[ 8 ];
    }
    
    // find out where our raw data fits in the arrays
    uint8_t data_pos = 0;
    for ( uint8_t cnt = 1; cnt < 8; cnt++ )
    {
        if ( out_counts >= data_count[ cnt ] )
        {
            data_pos = cnt;
        }
    }
    
    // Data MPS from arrays + linear MPS of percentage of window size where our data fits.
    return ( float ) ( data_mps[ data_pos ] + ( ( data_mps[ data_pos + 1 ] - data_mps[ data_pos ] ) * 
                                                ( out_counts - data_count[ data_pos ] ) / 
                                                ( float ) ( data_count[ data_pos + 1 ] - data_count[ data_pos ] ) ) );
}

// ------------------------------------------------------------------------- END
