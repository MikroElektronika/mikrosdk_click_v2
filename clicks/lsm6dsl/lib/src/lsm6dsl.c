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

#include "lsm6dsl.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define LSM6DSL_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lsm6dsl_cfg_setup ( lsm6dsl_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

LSM6DSL_RETVAL lsm6dsl_init ( lsm6dsl_t *ctx, lsm6dsl_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = LSM6DSL_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return LSM6DSL_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, LSM6DSL_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( cfg->cs );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LSM6DSL_OK;
}

void lsm6dsl_default_cfg ( lsm6dsl_t *ctx )
{
    lsm6dsl_write_byte( ctx, LSM6DSL_CTRL1_XL, LSM6DSL_ODR_104_HZ | LSM6DSL_FULLSCALE_XL_2 );
    lsm6dsl_write_byte( ctx, LSM6DSL_CTRL2_G, LSM6DSL_ODR_104_HZ | LSM6DSL_FULLSCALE_G_245 );
}

void lsm6dsl_generic_transfer 
( 
    lsm6dsl_t *ctx, 
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

uint8_t lsm6dsl_read_byte ( lsm6dsl_t *ctx, uint8_t reg_address )
{
    uint8_t rx_data;
    uint8_t w_data;

    w_data = reg_address | 0x80;

    lsm6dsl_generic_transfer( ctx, &w_data, 1, &rx_data, 1 );
    
    return  rx_data;
}

void lsm6dsl_write_byte ( lsm6dsl_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 1 ] = write_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, w_buffer, 2 );
    spi_master_deselect_device( ctx->chip_select );

}

uint8_t lsm6dsl_check_id ( lsm6dsl_t *ctx )
{
    uint8_t check_id;
    
    check_id = 0x00;
    
    check_id = lsm6dsl_read_byte( ctx, LSM6DSL_WHO_AM_I_REG );

    if ( check_id != LSM6DSL_CHECK_ID )
    {
        return 0x01;
    }
    else
    {
        return 0x00;
    }
}

void lsm6dsl_set_accel_config ( lsm6dsl_t *ctx, uint8_t odr_sel, uint8_t full_scale )
{
    lsm6dsl_write_byte( ctx, LSM6DSL_CTRL1_XL, odr_sel | full_scale );
}

void lsm6dsl_set_gyro_config ( lsm6dsl_t *ctx, uint8_t odr_sel, uint8_t full_scale )
{
    lsm6dsl_write_byte( ctx, LSM6DSL_CTRL2_G, odr_sel | full_scale );
}

void lsm6dsl_soft_reset ( lsm6dsl_t *ctx )
{
    uint8_t temp_data;
    
    temp_data = lsm6dsl_read_byte( ctx, LSM6DSL_CTRL3_C );
    
    temp_data |= 0x01;

    lsm6dsl_write_byte( ctx, LSM6DSL_CTRL3_C, temp_data );
}

void lsm6dsl_sleep_gyro ( lsm6dsl_t *ctx )
{
    uint8_t temp_data;

    temp_data = lsm6dsl_read_byte( ctx, LSM6DSL_CTRL4_C );

    temp_data |= 0x40;

    lsm6dsl_write_byte( ctx, LSM6DSL_CTRL4_C, temp_data );
}

void lsm6dsl_wake_up_gyro ( lsm6dsl_t *ctx )
{
    uint8_t temp_data;

    temp_data = lsm6dsl_read_byte( ctx, LSM6DSL_CTRL4_C );

    temp_data &= 0xBF;

    lsm6dsl_write_byte( ctx, LSM6DSL_CTRL4_C, temp_data );
}

void lsm6dsl_circular_burst_mode ( lsm6dsl_t *ctx, uint8_t burst_mode )
{
    uint8_t temp_data;

    temp_data = lsm6dsl_read_byte( ctx, LSM6DSL_CTRL5_C );
    
    if ( burst_mode < 4 )
    {
        temp_data |= burst_mode << 5;
    }

    lsm6dsl_write_byte( ctx, LSM6DSL_CTRL5_C, temp_data );
}

void lsm6dsl_set_self_test_mode ( lsm6dsl_t *ctx, uint8_t gyro_self_test, uint8_t accel_self_test )
{
    uint8_t temp_data;

    temp_data = lsm6dsl_read_byte( ctx, LSM6DSL_CTRL5_C );

    temp_data |= gyro_self_test;
    temp_data |= accel_self_test;

    lsm6dsl_write_byte( ctx, LSM6DSL_CTRL5_C, temp_data );
}

uint8_t lsm6dsl_get_status_reg ( lsm6dsl_t *ctx ) 
{
    uint8_t status_data;

    status_data = lsm6dsl_read_byte( ctx, LSM6DSL_STATUS_REG );

    return status_data;
}

uint16_t lsm6dsl_get_axis ( lsm6dsl_t *ctx, uint8_t reg_address_low )
{
    uint16_t result;
    
    result = 0x0000;
    
    result = lsm6dsl_read_byte( ctx, reg_address_low + 1 );
    result <<= 8;
    result |= lsm6dsl_read_byte( ctx, reg_address_low );
    
    return result;
}

float lsm6dsl_get_temperature ( lsm6dsl_t *ctx )
{
    uint16_t temp_data;
    float temperature;

    temp_data = 0x0000;

    temp_data = lsm6dsl_get_axis( ctx, LSM6DSL_OUT_TEMP_L );
    
    temperature = 23.94 + ( ( ( ( float ) temp_data ) - 47.71 ) * 0.0044 ) ;

    return temperature;
}

void lsm6dsl_get_accel ( lsm6dsl_t *ctx, lsm6dsl_accel_t *accel, uint8_t full_scale )
{
    uint16_t temp_data;
    float scaler_const;

    temp_data = 0x0000;
    scaler_const = 0.0;

    if ( full_scale == LSM6DSL_FULLSCALE_XL_2 )
    {
        scaler_const = 0.061;
    }
    
    if ( full_scale == LSM6DSL_FULLSCALE_XL_4 )
    {
        scaler_const = 0.122;
    }
    
    if ( full_scale == LSM6DSL_FULLSCALE_XL_8 )
    {
        scaler_const = 0.244;
    }
    
    if ( full_scale == LSM6DSL_FULLSCALE_XL_16 )
    {
        scaler_const = 0.488;
    }

    temp_data = lsm6dsl_get_axis( ctx, LSM6DSL_OUTX_L_XL );
    
    accel->accel_x = ( float ) temp_data;
    
    if ( accel->accel_x > 32767.0 )
    {
        accel->accel_x -= 65534.0;
    }
    
    accel->accel_x = accel->accel_x * scaler_const;

    temp_data = lsm6dsl_get_axis( ctx, LSM6DSL_OUTY_L_XL );
    
    accel->accel_y = ( float ) temp_data;
    
    if ( accel->accel_y > 32767.0 )
    {
        accel->accel_y -= 65534.0;
    }
    
    accel->accel_y = accel->accel_y * scaler_const;

    temp_data = lsm6dsl_get_axis( ctx, LSM6DSL_OUTZ_L_XL );
    
    accel->accel_z = ( float ) temp_data;
    
    if ( accel->accel_z > 32767.0 )
    {
        accel->accel_z -= 65534.0;
    }
    
    accel->accel_z = accel->accel_z * scaler_const;
}

void lsm6dsl_get_gyro ( lsm6dsl_t *ctx, lsm6dsl_gyro_t *gyro, uint8_t full_scale )
{
    uint16_t temp_data;
    float scaler_const;
    
    temp_data = 0x0000;
    scaler_const = 0.0;

    if ( full_scale == LSM6DSL_FULLSCALE_G_125 )
    {
        scaler_const = 4.375;
    }

    if ( full_scale == LSM6DSL_FULLSCALE_G_245 )
    {
        scaler_const = 8.75;
    }

    if ( full_scale == LSM6DSL_FULLSCALE_G_500 )
    {
        scaler_const = 17.50;
    }
    
    if ( full_scale == LSM6DSL_FULLSCALE_G_1000 )
    {
        scaler_const = 35.00;
    }
        
    if ( full_scale == LSM6DSL_FULLSCALE_G_2000 )
    {
        scaler_const = 70.00;
    }

    temp_data = lsm6dsl_get_axis( ctx, LSM6DSL_OUTX_L_G );

    gyro->gyro_x = ( float ) temp_data;

    if ( gyro->gyro_x > 32767.0 )
    {
        gyro->gyro_x -= 65534.0;
    }

    gyro->gyro_x = gyro->gyro_x * scaler_const;

    temp_data = lsm6dsl_get_axis( ctx, LSM6DSL_OUTY_L_G );

    gyro->gyro_y = ( float ) temp_data;

    if ( gyro->gyro_y > 32767.0 )
    {
        gyro->gyro_y -= 65534.0;
    }

    gyro->gyro_y = gyro->gyro_y * scaler_const;

    temp_data = lsm6dsl_get_axis( ctx, LSM6DSL_OUTZ_L_G );

    gyro->gyro_z = ( float ) temp_data;

    if ( gyro->gyro_z > 32767.0 )
    {
        gyro->gyro_z -= 65534.0;
    }

    gyro->gyro_z = gyro->gyro_z * scaler_const;
}

// ------------------------------------------------------------------------- END

