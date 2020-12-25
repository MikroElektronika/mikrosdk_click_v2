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

#include "accel5.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel5_cfg_setup ( accel5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins

    cfg->it2 = HAL_PIN_NC;
    cfg->it1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x15;
}

err_t accel5_init ( accel5_t *ctx, accel5_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ACCEL5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Input pins

    digital_in_init( &ctx->it2, cfg->it2 );
    digital_in_init( &ctx->it1, cfg->it1 );

    return ACCEL5_OK;
}

err_t accel5_generic_write ( accel5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint16_t cnt;

    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

err_t accel5_generic_read ( accel5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t reg_tmp = reg;
    
    return i2c_master_write_then_read( &ctx->i2c, &reg_tmp, 1, data_buf, len );
}

void accel5_default_cfg ( accel5_t *ctx, uint8_t mode, uint8_t range )
{
    accel5_write_byte( ctx, ACCEL5_REG_ACC_CONGIG_0, mode );
    accel5_write_byte( ctx, ACCEL5_REG_ACC_CONGIG_1, range );
    accel5_write_byte( ctx, ACCEL5_REG_ACC_CONGIG_2, ACCEL5_CFG_2_DATA_SCR_ACC_FILT_2 );
    
    accel5_write_byte( ctx, ACCEL5_REG_INT_CONFIG_0, ACCEL5_INT_CFG_0_DATA_RDY | 
                                               ACCEL5_INT_CFG_0_GEN1_INT_STATUS |
                                               ACCEL5_INT_CFG_0_GEN1_INT_STATUS |
                                               ACCEL5_INT_CFG_0_ORIENTCH_INT );
                                               
    accel5_write_byte( ctx, ACCEL5_REG_INT_CONFIG_1, ACCEL5_INT_CFG_1_STEP_INT_ENABLE |
                                               ACCEL5_INT_CFG_1_SINGLE_TAP_ENABLE |
                                               ACCEL5_INT_CFG_1_DOUBLE_TAP_ENABLE |
                                               ACCEL5_INT_CFG_1_ACTCH_INT_ENABLE );
    
    accel5_write_byte( ctx, ACCEL5_REG_INT12_MAP, ACCEL5_INT12_MAP_TAP_INT1 );
                                            
    accel5_write_byte( ctx, ACCEL5_REG_ORIENTCH_CONFIG_0, ACCEL5_ORIENT_X_AXIS_ENABLE |
                                                    ACCEL5_ORIENT_Y_AXIS_ENABLE |
                                                    ACCEL5_ORIENT_Z_AXIS_ENABLE |
                                                    ACCEL5_ORIENT_DATA_SRC_ENABLE |
                                                    ACCEL5_ORIENT_STABILITY_ENABLED_1 );

    accel5_write_byte( ctx, ACCEL5_REG_GEN1_INT_CONFIG_0, ACCEL5_GEN1_CFG0_ACT_X_ENABLE |
                                                    ACCEL5_GEN1_CFG0_ACT_Y_ENABLE |
                                                    ACCEL5_GEN1_CFG0_ACT_Z_ENABLE |
                                                    ACCEL5_GEN1_CFG0_DATA_ENABLE |
                                                    ACCEL5_GEN1_CFG0_HYST_24mg |
                                                    ACCEL5_GEN1_CFG0_REFU_EVERYTIME );
                                                   
    accel5_write_byte( ctx, ACCEL5_REG_GEN2_INT_CONFIG_0, ACCEL5_GEN2_CFG0_ACT_X_ENABLE |
                                                    ACCEL5_GEN2_CFG0_ACT_Y_ENABLE |
                                                    ACCEL5_GEN2_CFG0_ACT_Z_ENABLE |
                                                    ACCEL5_GEN2_CFG0_DATA_ENABLE |
                                                    ACCEL5_GEN2_CFG0_HYST_24mg |
                                                    ACCEL5_GEN2_CFG0_REFU_EVERYTIME );

    accel5_write_byte( ctx, ACCEL5_REG_ACTCH_CONFIG_1, ACCEL5_ACTCH_CFG0_X_AXIS_ENABLE |
                                                 ACCEL5_ACTCH_CFG0_Y_AXIS_ENABLE |
                                                 ACCEL5_ACTCH_CFG0_Z_AXIS_ENABLE |
                                                 ACCEL5_ACTCH_CFG0_DATA_ENABLE |
                                                 ACCEL5_ACTCH_CFG0_NPTS_POINT_32 );

    accel5_write_byte( ctx, ACCEL5_REG_TAP_CONFIG_0, ACCEL5_TAP_CFG0_USE_X_AXIS |
                                               ACCEL5_TAP_CFG0_USE_Y_AXIS |
                                               ACCEL5_TAP_CFG0_USE_Z_AXIS );
                                               
    accel5_write_byte( ctx, ACCEL5_REG_TAP_CONFIG_1, ACCEL5_TAP_CFG1_QUIET_DT_SAMPLE_4 |
                                               ACCEL5_TAP_CFG1_QUIET_SAMPLE_60 |
                                               ACCEL5_TAP_CFG1_TICS_TH_SAMPLE_6 );

}

void accel5_write_byte ( accel5_t *ctx, uint8_t reg, uint8_t reg_data )
{
    uint8_t tmp_data = reg_data;

    accel5_generic_write( ctx, reg, &tmp_data, 1 );
}

uint8_t accel5_read_byte ( accel5_t *ctx, uint8_t reg )
{
    uint8_t read_reg;

    accel5_generic_read( ctx, reg, &read_reg, 1 );

    return read_reg;
}

uint16_t accel5_read_data ( accel5_t *ctx, uint8_t reg )
{
    uint8_t read_reg[ 2 ];
    uint16_t read_data;

    accel5_generic_read( ctx, reg, read_reg, 2 );

    read_data = read_reg[ 1 ];
    read_data = read_data << 8;
    read_data = read_data | read_reg[ 0 ];

    return read_data;
}

int16_t accel5_get_axis ( accel5_t *ctx, uint8_t axis )
{
    int16_t axis_data;

    axis_data = accel5_read_data( ctx, axis );
    axis_data = axis_data & 0x0FFF;

    if ( axis_data > 2047 )
    {
        axis_data = (int16_t)( axis_data - 4096 );
    }

    return axis_data;
}

uint32_t accel5_sensor_time ( accel5_t *ctx )
{
    uint32_t s_time;
    uint8_t read_time0;
    uint8_t read_time1;
    uint8_t read_time2;

    read_time0 = accel5_read_byte( ctx, ACCEL5_REG_SENSOR_TIME_0 );
    read_time1 = accel5_read_byte( ctx, ACCEL5_REG_SENSOR_TIME_1 );
    read_time2 = accel5_read_byte( ctx, ACCEL5_REG_SENSOR_TIME_2 );

    s_time = read_time2;
    s_time = s_time << 8;
    s_time = s_time | read_time1;
    s_time = s_time << 8;
    s_time = s_time | read_time0;
    s_time = (uint32_t)s_time * 312.5;

    return s_time;
}

float accel5_get_temperature ( accel5_t *ctx )
{
    int8_t read_data;
    float temp;

    read_data = accel5_read_byte( ctx, ACCEL5_REG_TEMPERATURE );
    if ( read_data > 0x80 )
    {
        read_data = read_data - 256;
    }
    temp = ( read_data * 0.5 ) + 33.0;

    return temp;
}

void accel5_soft_reset ( accel5_t *ctx )
{
    accel5_write_byte( ctx, ACCEL5_REG_CMD, ACCEL5_CMD_SOFTWARE_RESET );
}

// ------------------------------------------------------------------------ END
