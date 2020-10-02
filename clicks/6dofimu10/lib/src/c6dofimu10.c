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

#include "c6dofimu10.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void drv_set_register ( c6dofimu10_t *ctx,  uint8_t reg, uint8_t set_data );

static int16_t drv_read_data_u16 ( c6dofimu10_t *ctx,  uint8_t reg );

static uint8_t drv_get_register ( c6dofimu10_t *ctx,  uint8_t reg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu10_cfg_setup ( c6dofimu10_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->gp2 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C6DOFIMU10_SLAVE_ADDRESS_GND;
}

c6DOFIMU10_RETVAL c6dofimu10_init ( c6dofimu10_t *ctx, c6dofimu10_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return c6DOFIMU10_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->gp2, cfg->gp2 );

    // Input pins

    digital_in_init( &ctx->gp1, cfg->gp1 );

    return c6DOFIMU10_OK;

}

void c6dofimu10_default_cfg ( c6dofimu10_t *ctx )
{
    drv_set_register ( ctx, C6DOFIMU10_REG_INC_1, 
                       C6DOFIMU10_INC1_GP1_BUFF_FULL_INT_DISABLE |
                       C6DOFIMU10_INC1_GP1_WM_INT_DISABLE | 
                       C6DOFIMU10_INC1_GP1_ACCEL_DRDY_ENABLE | 
                       C6DOFIMU10_INC1_GP1_MAG_DRDY_DISABLE |
                       C6DOFIMU10_INC1_GP1_FREE_FALL_INT_DISABLE |
                       C6DOFIMU10_INC1_GP1_ACCEL_MOTION_DISABLE |
                       C6DOFIMU10_INC1_GP1_MAG_MOTION_DISABLE  );

    drv_set_register ( ctx, C6DOFIMU10_REG_INC_2, 
                       C6DOFIMU10_INC2_GP2_BUFF_FULL_INT_DISABLE |
                       C6DOFIMU10_INC2_GP2_WM_INT_DISABLE | 
                       C6DOFIMU10_INC2_GP2_ACCEL_DRDY_ENABLE | 
                       C6DOFIMU10_INC2_GP2_MAG_DRDY_DISABLE |
                       C6DOFIMU10_INC2_GP2_FREE_FALL_INT_DISABLE |
                       C6DOFIMU10_INC2_GP2_ACCEL_MOTION_DISABLE |
                       C6DOFIMU10_INC2_GP2_MAG_MOTION_DISABLE );

    drv_set_register ( ctx, C6DOFIMU10_REG_INC_3, 
                       C6DOFIMU10_INC3_IED2_OPEN_DRAIN |
                       C6DOFIMU10_INC3_IEA2_ACTIVE_HIGH |
                       C6DOFIMU10_INC3_IEL2_LATCHED |
                       C6DOFIMU10_INC3_IED1_OPEN_DRAIN |
                       C6DOFIMU10_INC3_IEA1_ACTIVE_HIGH |
                       C6DOFIMU10_INC3_IEL1_LATCHED );

    drv_set_register ( ctx, C6DOFIMU10_REG_INC_4, 
                       C6DOFIMU10_INC4_ACCEL_NEGATIVE_X_ENABLE |
                       C6DOFIMU10_INC4_ACCEL_POSITIVE_X_ENABLE |
                       C6DOFIMU10_INC4_ACCEL_NEGATIVE_Y_ENABLE |
                       C6DOFIMU10_INC4_ACCEL_POSITIVE_Y_ENABLE |
                       C6DOFIMU10_INC4_ACCEL_NEGATIVE_Z_ENABLE |
                       C6DOFIMU10_INC4_ACCEL_POSITIVE_Z_ENABLE );

    drv_set_register ( ctx, C6DOFIMU10_REG_INC_5, 
                       C6DOFIMU10_INC4_MAG_NEGATIVE_X_ENABLE |
                       C6DOFIMU10_INC4_MAG_POSITIVE_X_ENABLE |
                       C6DOFIMU10_INC4_MAG_NEGATIVE_Y_ENABLE |
                       C6DOFIMU10_INC4_MAG_POSITIVE_Y_ENABLE |
                       C6DOFIMU10_INC4_MAG_NEGATIVE_Z_ENABLE |
                       C6DOFIMU10_INC4_MAG_POSITIVE_Z_ENABLE );

    drv_set_register ( ctx, C6DOFIMU10_REG_AMI_CNTL_3, 
                       C6DOFIMU10_AMICNTL3_ACCEL_MOTION_ENABLE |
                       C6DOFIMU10_AMICNTL3_ACCEL_MOTION_LATCHED |
                       C6DOFIMU10_AMICNTL3_ACCEL_ODR_100 );

    drv_set_register ( ctx, C6DOFIMU10_REG_MMI_CNTL_3, 
                       C6DOFIMU10_MMICNTL3_MAG_MOTION_ENABLE |
                       C6DOFIMU10_MMICNTL3_MAG_MOTION_LATCHED |
                       C6DOFIMU10_MMICNTL3_MAG_ODR_100 );  

    drv_set_register ( ctx, C6DOFIMU10_REG_CNTL_1,                                 
                       C6DOFIMU10_CNTL1_SW_RESET_NO_ACTION |
                       C6DOFIMU10_CNTL1_ST_MODE_DISABLE |
                       C6DOFIMU10_CNTL1_ST_POLARITY_POSITIVE |
                       C6DOFIMU10_CNTL1_COTC_NO_ACTION );

    drv_set_register ( ctx, C6DOFIMU10_REG_CNTL_2,
                       C6DOFIMU10_CNTL2_TEMP_OPERATING_MODE |                               
                       C6DOFIMU10_CNTL2_ACCEL_RANGE_2g |
                       C6DOFIMU10_CNTL2_RES_SAMBLE_A4_M2 |
                       C6DOFIMU10_CNTL2_MAG_OPERATING_MODE |
                       C6DOFIMU10_CNTL2_ACCEL_OPERATING_MODE );
}

void c6dofimu10_generic_write ( c6dofimu10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void c6dofimu10_generic_read ( c6dofimu10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void c6dofimu10_measurement_cfg( c6dofimu10_t *ctx, c6dofimu10_cfg_t *cfg )
{
    drv_set_register ( ctx, C6DOFIMU10_REG_CNTL_2,
                       cfg->op_temp | cfg->op_accel |
                       cfg->op_mag | cfg->accel_range |
                       cfg->res_sample );
}

void c6dofimu10_get_accel_axis ( c6dofimu10_t *ctx, c6dofimu10_axis_t *axis )
{
    axis->x = drv_read_data_u16( ctx, C6DOFIMU10_REG_ACCEL_XOUT );
    axis->y = drv_read_data_u16( ctx, C6DOFIMU10_REG_ACCEL_YOUT );
    axis->z = drv_read_data_u16( ctx, C6DOFIMU10_REG_ACCEL_ZOUT );
}

void c6dofimu10_get_mag_axis ( c6dofimu10_t *ctx, c6dofimu10_axis_t *axis )
{
    axis->x = drv_read_data_u16( ctx, C6DOFIMU10_REG_MAG_XOUT );
    axis->y = drv_read_data_u16( ctx, C6DOFIMU10_REG_MAG_YOUT );
    axis->z = drv_read_data_u16( ctx, C6DOFIMU10_REG_MAG_ZOUT );
}

float c6dofimu10_get_temperature ( c6dofimu10_t *ctx, uint8_t temp_format )
{
    float temperature;
    int8_t temp_data;
     
    temp_data = drv_get_register( ctx, C6DOFIMU10_REG_TEMP_OUT_H );
    temperature = temp_data;
    temperature += drv_get_register( ctx, C6DOFIMU10_REG_TEMP_OUT_L ) * 0.0039;

    if ( temp_format == C6DOFIMU10_TEMP_FORMAT_FARENHAJT )
    {
        return temperature * 9 / 5 + 32;
    }
    else if ( temp_format == C6DOFIMU10_TEMP_FORMAT_KELVIN )
    {
        return temperature + 273.15;
    }

    return temperature;
}

uint8_t c6dofimu10_communication_test ( c6dofimu10_t *ctx )
{
    uint8_t device_id;

    device_id = drv_get_register ( ctx, C6DOFIMU10_REG_WHO_AM_I );

    if ( device_id == C6DOFIMU10_DEF_WHO_AM_I )
    {
       return C6DOFIMU10_DEVICE_OK;
    }
    return C6DOFIMU10_DEVICE_ERROR;
}

void c6dofimu10_get_motion ( c6dofimu10_t *ctx, uint8_t sensor_reg, c6dofimu10_motion_t *motion_obj )
{
    uint8_t raw_data;
    
    raw_data = drv_get_register( ctx, sensor_reg );
    
    motion_obj->neg_x = ( raw_data & 0x20 ) >> 5;
    motion_obj->pos_x = ( raw_data & 0x10 ) >> 4;
    motion_obj->neg_y = ( raw_data & 0x08 ) >> 3;
    motion_obj->pos_y = ( raw_data & 0x04 ) >> 2;
    motion_obj->neg_z = ( raw_data & 0x02 ) >> 1;
    motion_obj->pos_z = ( raw_data & 0x01 );
}

uint8_t c6dofimu10_get_interrupt ( c6dofimu10_t *ctx, uint8_t int_pin )
{
    if ( int_pin == C6DOFIMU10_GP1_INT_PIN )
    {
        return digital_in_read( &ctx->gp1 );
    }
    else
    {
        return digital_in_read( &ctx->gp2 );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void drv_set_register ( c6dofimu10_t *ctx, uint8_t reg, uint8_t set_data )
{
    c6dofimu10_generic_write( ctx, reg, &set_data, 1 );
}

static int16_t drv_read_data_u16 ( c6dofimu10_t *ctx, uint8_t reg )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    int16_t data_out = 0;

    c6dofimu10_generic_read( ctx, reg, rx_buf, 2 );

    data_out = rx_buf[ 1 ];
    data_out <<= 8;
    data_out |= rx_buf[ 0 ];

    return data_out;
}

static uint8_t drv_get_register ( c6dofimu10_t *ctx, uint8_t reg )
{
    uint8_t reg_data;

    c6dofimu10_generic_read( ctx, reg, &reg_data, 1 );

    return reg_data;
}

// ------------------------------------------------------------------------- END

