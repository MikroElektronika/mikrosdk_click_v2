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

#include "c6dofimu11.h"


void c6dofimu11_cfg_setup ( c6dofimu11_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->gp1 = HAL_PIN_NC;
    cfg->gp2 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C6DOFIMU11_I2C_SLAVE_ADDRESS_GND;
}

C6DOFIMU11_RETVAL c6dofimu11_init ( c6dofimu11_t *ctx, c6dofimu11_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return C6DOFIMU11_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->gp1, cfg->gp1 );

    // Input pins

    digital_in_init( &ctx->gp2, cfg->gp2 );
  

    return C6DOFIMU11_OK;
}

void c6dofimu11_default_cfg ( c6dofimu11_t *ctx )
{
    // Click default configuration 
    
    c6dofimu11_write_byte( ctx, C6DOFIMU11_CNTL2, 
                                C6DOFIMU11_CNTL2_TEMP_EN_STANDBY_MODE | 
                                C6DOFIMU11_CNTL2_MAG_EN_STANDBY_MODE | 
                                C6DOFIMU11_CNTL2_ACCEL_EN_STANDBY_MODE );

    c6dofimu11_write_byte ( ctx, C6DOFIMU11_INC3, 
                                 C6DOFIMU11_INC3_IEL2_FIFO_TRIG | 
                                 C6DOFIMU11_INC3_IEL1_FIFO_TRIG );

    c6dofimu11_write_byte ( ctx, C6DOFIMU11_CNTL2, 
                                 C6DOFIMU11_CNTL2_GSEL_8G | 
                                 C6DOFIMU11_CNTL2_RES_MAX2 | 
                                 C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE | 
                                 C6DOFIMU11_CNTL2_ACCEL_EN_OPERATING_MODE );
    
}

void c6dofimu11_generic_write ( c6dofimu11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );  
}

void c6dofimu11_generic_read ( c6dofimu11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void c6dofimu11_write_byte ( c6dofimu11_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = write_data;
  
    c6dofimu11_generic_write( ctx, reg_address, tx_buf, 1 ); 
}

uint8_t c6dofimu11_read_byte ( c6dofimu11_t *ctx, uint8_t reg_address )
{
    uint8_t rx_buf[ 1 ];

    rx_buf[ 0 ] = reg_address;

    c6dofimu11_generic_read( ctx, reg_address, rx_buf, 1 );
  
    return rx_buf[ 0 ];
}

void c6dofimu11_write_multiple_bytes ( c6dofimu11_t *ctx, uint8_t reg_address, uint8_t *p_write_data, uint8_t n_bytes )
{
    c6dofimu11_generic_write( ctx, reg_address, p_write_data, n_bytes );
}

void c6dofimu11_read_multiple_bytes ( c6dofimu11_t *ctx, uint8_t reg_address, uint8_t *p_read_data, uint8_t n_bytes )
{
    
    c6dofimu11_generic_read( ctx, reg_address, p_read_data,n_bytes );
}

uint8_t c6dofimu11_check_id ( c6dofimu11_t *ctx )
{
    uint8_t id_val;

    id_val = c6dofimu11_read_byte( ctx, C6DOFIMU11_WHO_AM_I );
    
    if ( id_val == C6DOFIMU11_WHO_AM_I_WIA_ID )
    {
        return C6DOFIMU11_CHECK_ID_SUCCESS;
    }
    else
    {
        return C6DOFIMU11_CHECK_ID_ERROR;
    }
}


void c6dofimu11_disable_sensor ( c6dofimu11_t *ctx )
{
    c6dofimu11_write_byte( ctx, C6DOFIMU11_CNTL2, C6DOFIMU11_CNTL2_TEMP_EN_STANDBY_MODE
                                             | C6DOFIMU11_CNTL2_MAG_EN_STANDBY_MODE
                                             | C6DOFIMU11_CNTL2_ACCEL_EN_STANDBY_MODE );
}

void c6dofimu11_enable_sensor ( c6dofimu11_t *ctx, uint8_t en_accel, uint8_t en_mag, uint8_t en_temp )
{
    uint8_t tmp_val;

    tmp_val = c6dofimu11_read_byte( ctx, C6DOFIMU11_CNTL2 );
    
    if ( en_accel == C6DOFIMU11_CNTL2_ACCEL_ENABLE )
    {
        tmp_val |= C6DOFIMU11_CNTL2_ACCEL_EN_OPERATING_MODE;
    }
    else if ( en_accel == C6DOFIMU11_CNTL2_ACCEL_DISABLE )
    {
        tmp_val &= ~C6DOFIMU11_CNTL2_ACCEL_EN_OPERATING_MODE;
    }
    
    if ( en_mag == C6DOFIMU11_CNTL2_MAG_ENABLE )
    {
        tmp_val |= C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE;
    }
    else if ( en_mag == C6DOFIMU11_CNTL2_MAG_DISABLE )
    {
        tmp_val &= ~C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE;
    }
    
    if ( en_temp == C6DOFIMU11_CNTL2_TEMPERATURE_ENABLE )
    {
        tmp_val |= C6DOFIMU11_CNTL2_TEMP_EN_OPERATING_MODE;
        tmp_val |= C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE;
    }
    else if ( en_temp == C6DOFIMU11_CNTL2_TEMPERATURE_DISABLE )
    {
        tmp_val &= ~C6DOFIMU11_CNTL2_TEMP_EN_OPERATING_MODE;
    }
    
    c6dofimu11_write_byte( ctx, C6DOFIMU11_CNTL2, tmp_val );
}

void c6dofimu11_config_accel ( c6dofimu11_t *ctx, uint8_t data_rate, uint8_t data_range, uint8_t data_resolution )
{
    uint8_t tmp_val;
    
    c6dofimu11_disable_sensor( ctx );

    tmp_val = c6dofimu11_read_byte( ctx, C6DOFIMU11_ODCNTL );
    
    tmp_val &= C6DOFIMU11_ODCNTL_OSM_12800;
    tmp_val |= data_rate;
    
    c6dofimu11_write_byte( ctx, C6DOFIMU11_ODCNTL, tmp_val );
    
    tmp_val = c6dofimu11_read_byte( ctx, C6DOFIMU11_CNTL2 );
    
    tmp_val &= ~C6DOFIMU11_CNTL2_GSEL_MASK;
    tmp_val &= ~C6DOFIMU11_CNTL2_RES_MASK;
    tmp_val |= ( data_range & C6DOFIMU11_CNTL2_GSEL_MASK );
    tmp_val |= ( data_resolution & C6DOFIMU11_CNTL2_RES_MASK );
    tmp_val |= C6DOFIMU11_CNTL2_MAG_EN_MASK;
    tmp_val |= C6DOFIMU11_CNTL2_ACCEL_EN_MASK;
    
    c6dofimu11_write_byte( ctx, C6DOFIMU11_CNTL2, tmp_val );
}

void c6dofimu11_config_mag ( c6dofimu11_t *ctx, uint8_t data_rate, uint8_t data_resolution )
{
    uint8_t tmp_val;

    c6dofimu11_disable_sensor( ctx );

    tmp_val = c6dofimu11_read_byte( ctx, C6DOFIMU11_ODCNTL );

    tmp_val &= C6DOFIMU11_ODCNTL_OSA_25600;
    tmp_val |= data_rate;

    c6dofimu11_write_byte( ctx, C6DOFIMU11_ODCNTL, tmp_val );

    tmp_val = c6dofimu11_read_byte( ctx, C6DOFIMU11_CNTL2 );

    tmp_val &= ~C6DOFIMU11_CNTL2_RES_MASK;
    tmp_val |= ( data_resolution & C6DOFIMU11_CNTL2_RES_MASK );
    tmp_val |= C6DOFIMU11_CNTL2_MAG_EN_MASK;
    tmp_val |= C6DOFIMU11_CNTL2_ACCEL_EN_MASK;

    c6dofimu11_write_byte( ctx, C6DOFIMU11_CNTL2, tmp_val );
}

int16_t c6dofimu11_get_axis ( c6dofimu11_t *ctx, uint8_t reg_add_lsb )
{
    uint16_t axis_val;
    int16_t res_val;
    uint8_t buf[ 2 ];

    buf[ 0 ] = c6dofimu11_read_byte( ctx,reg_add_lsb + 1 );
    buf[ 1 ] = c6dofimu11_read_byte( ctx, reg_add_lsb );

    axis_val = buf[ 0 ];
    axis_val <<= 8;
    axis_val |= buf[ 1 ];

    res_val = ( int16_t ) axis_val;

    return res_val;
}

void c6dofimu11_get_accel_data ( c6dofimu11_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z )
{
    *accel_x = c6dofimu11_get_axis( ctx, C6DOFIMU11_ACCEL_XOUT_L );
    *accel_y = c6dofimu11_get_axis( ctx, C6DOFIMU11_ACCEL_YOUT_L );
    *accel_z = c6dofimu11_get_axis( ctx, C6DOFIMU11_ACCEL_ZOUT_L );
}

void c6dofimu11_get_mag_data ( c6dofimu11_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z )
{
    *mag_x = c6dofimu11_get_axis( ctx, C6DOFIMU11_MAG_XOUT_L );
    *mag_y = c6dofimu11_get_axis( ctx, C6DOFIMU11_MAG_YOUT_L );
    *mag_z = c6dofimu11_get_axis( ctx, C6DOFIMU11_MAG_ZOUT_L );
}

void c6dofimu11_read_accel (  c6dofimu11_t *ctx, c6dofimu11_accel_t *accel_data )
{
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    uint8_t c_tmp;
    
    accel_x = c6dofimu11_get_axis(  ctx, C6DOFIMU11_ACCEL_XOUT_L );
    accel_y = c6dofimu11_get_axis( ctx, C6DOFIMU11_ACCEL_YOUT_L );
    accel_z = c6dofimu11_get_axis( ctx, C6DOFIMU11_ACCEL_ZOUT_L );
    
    c_tmp = c6dofimu11_read_byte( ctx, C6DOFIMU11_CNTL2 );
    c_tmp &= C6DOFIMU11_CNTL2_GSEL_MASK;
    
    switch ( c_tmp )
    {
        case C6DOFIMU11_CNTL2_GSEL_8G:
        {
            accel_data->x = ( float ) accel_x;
            accel_data->x *= C6DOFIMU11_ACCEL_COEF_RES_8G;
            accel_data->y = ( float ) accel_y;
            accel_data->y *= C6DOFIMU11_ACCEL_COEF_RES_8G;
            accel_data->z = ( float ) accel_z;
            accel_data->z *= C6DOFIMU11_ACCEL_COEF_RES_8G;
            break;
        }
        case C6DOFIMU11_CNTL2_GSEL_16G:
        {
            accel_data->x = ( float ) accel_x;
            accel_data->x *= C6DOFIMU11_ACCEL_COEF_RES_16G;
            accel_data->y = ( float ) accel_y;
            accel_data->y *= C6DOFIMU11_ACCEL_COEF_RES_16G;
            accel_data->z = ( float ) accel_z;
            accel_data->z *= C6DOFIMU11_ACCEL_COEF_RES_16G;
            break;
        }
        case C6DOFIMU11_CNTL2_GSEL_32G:
        {
            accel_data->x = ( float ) accel_x;
            accel_data->x *= C6DOFIMU11_ACCEL_COEF_RES_32G;
            accel_data->y = ( float ) accel_y;
            accel_data->y *= C6DOFIMU11_ACCEL_COEF_RES_32G;
            accel_data->z = ( float ) accel_z;
            accel_data->z *= C6DOFIMU11_ACCEL_COEF_RES_32G;
            break;
        }
        case C6DOFIMU11_CNTL2_GSEL_64G:
        {
            accel_data->x = ( float ) accel_x;
            accel_data->x *= C6DOFIMU11_ACCEL_COEF_RES_64G;
            accel_data->y = ( float ) accel_y;
            accel_data->y *= C6DOFIMU11_ACCEL_COEF_RES_64G;
            accel_data->z = ( float ) accel_z;
            accel_data->z *= C6DOFIMU11_ACCEL_COEF_RES_64G;
            break;
        }
    }
}

void c6dofimu11_read_mag ( c6dofimu11_t *ctx, c6dofimu11_mag_t *mag_data )
{
    int16_t mag_x;
    int16_t mag_y;
    int16_t mag_z;
    uint8_t c_tmp;
    
    mag_x = c6dofimu11_get_axis( ctx, C6DOFIMU11_MAG_XOUT_L );
    mag_y = c6dofimu11_get_axis( ctx, C6DOFIMU11_MAG_YOUT_L );
    mag_z = c6dofimu11_get_axis( ctx, C6DOFIMU11_MAG_ZOUT_L );
    
    mag_data->x = ( float ) mag_x;
    mag_data->x *= C6DOFIMU11_MAG_COEF;
    mag_data->y = ( float ) mag_y;
    mag_data->y *= C6DOFIMU11_MAG_COEF;
    mag_data->z = ( float ) mag_z;
    mag_data->z *= C6DOFIMU11_MAG_COEF;
}

void c6dofimu11_enable_temperature_data ( c6dofimu11_t *ctx )
{
    uint8_t tmp_val;

    tmp_val = c6dofimu11_read_byte( ctx, C6DOFIMU11_CNTL2 );
    
    tmp_val |= C6DOFIMU11_CNTL2_TEMP_EN_OPERATING_MODE;
    tmp_val |= C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE;

    c6dofimu11_write_byte ( ctx, C6DOFIMU11_CNTL2, tmp_val );
}

float c6dofimu11_get_temperature ( c6dofimu11_t *ctx )
{
    uint8_t buf[ 2 ];
    int8_t tmp;
    float temperature;

    c6dofimu11_read_multiple_bytes ( ctx, C6DOFIMU11_TEMP_OUT_L, &buf[ 0 ], 2 );

    tmp = ( int8_t ) buf[ 1 ];

    temperature = ( float ) tmp;

    tmp = ( int8_t ) buf[ 0 ];

    temperature += ( ( float ) tmp ) / 256.0;

    return temperature;
}

uint8_t c6dofimu11_get_interrupt ( c6dofimu11_t *ctx )
{
    return digital_in_read( &ctx->gp2 );
  
}

// ------------------------------------------------------------------------- END

