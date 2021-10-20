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
 * @file c6dofimu13.c
 * @brief 6DOF IMU 13 Click Driver.
 */

#include "c6dofimu13.h"

/**
 * @brief 6DOF IMU 13 calculate twos complement.
 * @details This function calculates twos complement.
 * @param[in] raw : Raw data.
 * @param[in] length : Data length in bits.
 * @note None.
 *
 * @endcode
 */
static void dev_get_twos_comp ( int16_t *raw, uint8_t length );

void c6dofimu13_cfg_setup ( c6dofimu13_cfg_t *cfg ) 
{
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins

    cfg->in2  = HAL_PIN_NC;
    cfg->in1  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C6DOFIMU13_DEV_ADDRESS_ACCEL_GND;
}

err_t c6dofimu13_init ( c6dofimu13_t *ctx, c6dofimu13_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_in_init( &ctx->in2, cfg->in2 );
    digital_in_init( &ctx->in1, cfg->in1 );

    return I2C_MASTER_SUCCESS;
}

err_t c6dofimu13_default_cfg ( c6dofimu13_t *ctx ) 
{
    err_t error_check;
    
    error_check = c6dofimu13_mag_init ( ctx, C6DOFIMU13_MAG_RES_15_BIT, 
                                             C6DOFIMU13_MAG_OP_MODE_CONT, 
                                             C6DOFIMU13_MAG_TEMP_MEAS_ON );
    Delay_100ms( );
    
    error_check = c6dofimu13_accel_init ( ctx, C6DOFIMU13_ACCEL_SRTFR_RATE_32, 
                                               C6DOFIMU13_ACCEL_OUTCFG_RANGE_16, 
                                               C6DOFIMU13_ACCEL_OUTCFG_RES_14 );
    Delay_100ms( );
    
    return error_check;
}

err_t c6dofimu13_set_slave_address ( c6dofimu13_t *ctx, uint8_t slave_address ) 
{
    if ( slave_address == C6DOFIMU13_DEV_ADDRESS_MAG )
    {
        if ( i2c_master_set_slave_address( &ctx->i2c, slave_address ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }
    }
    else
    {
        ctx->slave_address = slave_address;
        if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }
    }

    return C6DOFIMU13_OK;
}

err_t c6dofimu13_generic_write ( c6dofimu13_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) 
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t c6dofimu13_generic_read ( c6dofimu13_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t c6dofimu13_mag_init ( c6dofimu13_t *ctx, uint8_t res, uint8_t op_mode, uint8_t temp_meas )
{
    uint8_t cmd_byte;
    uint8_t range_byte;
    uint8_t force_state;
    err_t error_check;

    error_check = c6dofimu13_set_slave_address ( ctx, C6DOFIMU13_DEV_ADDRESS_MAG );
    
    cmd_byte = C6DOFIMU13_MAG_CTL_3_SRST_SR;
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_3, &cmd_byte, 1 );
    
    if ( temp_meas == 1 )
    {
        force_state = C6DOFIMU13_MAG_CTL_3_TCS_EN;
    }
    else
    {
        force_state = C6DOFIMU13_MAG_CTL_3_TCS_NOP;
    }

    if ( res == 1 )
    {
        range_byte = 0x80 | C6DOFIMU13_MAG_CTL_4_RS_S_15;
    }
    else
    {
        range_byte = 0x80 | C6DOFIMU13_MAG_CTL_4_RS_S_14;
    }
    
    switch( op_mode )
    {
        case C6DOFIMU13_MAG_OP_MODE_S_SHOT:
        {
            cmd_byte = C6DOFIMU13_MAG_CTL_1_PC_NORM | 
                       C6DOFIMU13_MAG_CTL_1_ODR_100 | 
                       C6DOFIMU13_MAG_CTL_1_FS_DEF;
                       
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_3, &force_state, 1 );
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_4, &range_byte, 1 );
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_1, &cmd_byte, 1 );
            break;
        }
        case C6DOFIMU13_MAG_OP_MODE_CONT:
        {
            force_state |= C6DOFIMU13_MAG_CTL_3_FRC_SM;
            cmd_byte = C6DOFIMU13_MAG_CTL_1_PC_NORM | C6DOFIMU13_MAG_CTL_1_ODR_100;
            
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_4, &range_byte, 1 );
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_1, &cmd_byte, 1 );
            break;
        }
        default:
        {
            cmd_byte = C6DOFIMU13_MAG_CTL_1_PC_NORM | 
                       C6DOFIMU13_MAG_CTL_1_ODR_100 | 
                       C6DOFIMU13_MAG_CTL_1_FS_DEF;
                       
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_3, &force_state, 1 );
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_4, &range_byte, 1 );
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_1, &cmd_byte, 1 );
            break;
        }
    }
    
    return error_check;
}

err_t c6dofimu13_mag_get_x ( c6dofimu13_t *ctx, float *result )
{
    int16_t adc_val;
    uint8_t range;
    uint8_t rx_buf[ 2 ];
    err_t error_check;
    
    error_check = c6dofimu13_set_slave_address ( ctx, C6DOFIMU13_DEV_ADDRESS_MAG );

    error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_MAG_CTL_4, &range, 1 );

    error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_MAG_OUT_X_LSB, rx_buf, 2 );

    adc_val = rx_buf[ 1 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 0 ];

    if ( range & C6DOFIMU13_MAG_CTL_4_RS_S_15 )
    {
        adc_val &= 0x7FFF;
        if ( adc_val & 0x4000 )
        {
            dev_get_twos_comp( &adc_val, 15 );
        }
    }
    else
    {
        adc_val &= 0x3FFF;
        if ( adc_val & 0x2000 )
        {
            dev_get_twos_comp( &adc_val, 14 );
        }
    }

    *result = ( float ) adc_val * C6DOFIMU13_MAG_SENS;

    return error_check;
}

err_t c6dofimu13_mag_get_y ( c6dofimu13_t *ctx, float *result )
{
    int16_t adc_val;
    uint8_t range;
    uint8_t rx_buf[ 2 ];
    err_t error_check;
    
    error_check = c6dofimu13_set_slave_address ( ctx, C6DOFIMU13_DEV_ADDRESS_MAG );
    
    error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_MAG_CTL_4, &range, 1 );

    error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_MAG_OUT_Y_LSB, rx_buf, 2 );

    adc_val = rx_buf[ 1 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 0 ];

    if ( range & C6DOFIMU13_MAG_CTL_4_RS_S_15 )
    {
        adc_val &= 0x7FFF;
        if ( adc_val & 0x4000 )
        {
            dev_get_twos_comp( &adc_val, 15 );
        }
    }
    else
    {
        adc_val &= 0x3FFF;
        if ( adc_val & 0x2000 )
        {
            dev_get_twos_comp( &adc_val, 14 );
        }
    }

    *result = ( float ) adc_val * C6DOFIMU13_MAG_SENS;

    return error_check;
}

err_t c6dofimu13_mag_get_z ( c6dofimu13_t *ctx, float *result )
{
    int16_t adc_val;
    uint8_t range;
    uint8_t rx_buf[ 2 ];
    err_t error_check;
    
    error_check = c6dofimu13_set_slave_address ( ctx, C6DOFIMU13_DEV_ADDRESS_MAG );
    
    error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_MAG_CTL_4, &range, 1 );

    error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_MAG_OUT_Z_LSB, rx_buf, 2 );

    adc_val = rx_buf[ 1 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 0 ];

    if ( range & C6DOFIMU13_MAG_CTL_4_RS_S_15 )
    {
        adc_val &= 0x7FFF;
        if ( adc_val & 0x4000 )
        {
            dev_get_twos_comp( &adc_val, 15 );
        }
    }
    else
    {
        adc_val &= 0x3FFF;
        if ( adc_val & 0x2000 )
        {
            dev_get_twos_comp( &adc_val, 14 );
        }
    }

    *result = ( float ) adc_val * C6DOFIMU13_MAG_SENS;

    return error_check;
}

err_t c6dofimu13_mag_get_data ( c6dofimu13_t *ctx, float *mag_x, float *mag_y, float *mag_z )
{
    err_t error_check;
    
    error_check = c6dofimu13_mag_get_x( ctx, mag_x );
    error_check |= c6dofimu13_mag_get_y( ctx, mag_y );
    error_check |= c6dofimu13_mag_get_z( ctx, mag_z );
    
    return error_check;
}

err_t c6dofimu13_mag_offset ( c6dofimu13_t *ctx, int16_t offset, uint8_t axis )
{
    uint8_t cmd_byte;
    uint8_t force_state;
    uint8_t tx_buf[ 2 ];
    err_t error_check;
    
    error_check = c6dofimu13_set_slave_address ( ctx, C6DOFIMU13_DEV_ADDRESS_MAG );

    force_state = C6DOFIMU13_MAG_CTL_1_FS_DEF;
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_3, &force_state, 1 );

    cmd_byte = C6DOFIMU13_MAG_CTL_3_OCL_EN;
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_3, &cmd_byte, 1 );

    tx_buf[ 0 ] = offset & 0xFF;
    tx_buf[ 1 ] = ( offset >> 8 ) & 0xFF;
    
    switch ( axis )
    {
        case C6DOFIMU13_MAG_AXIS_X :
        {
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_OFFS_X_LSB, tx_buf, 2 );
        }
        case C6DOFIMU13_MAG_AXIS_Y :
        {
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_OFFS_Y_LSB, tx_buf, 2 );
        }
        case C6DOFIMU13_MAG_AXIS_Z :
        {
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_OFFS_Z_LSB, tx_buf, 2 );
        }
    }

    cmd_byte &= ~C6DOFIMU13_MAG_CTL_3_OCL_EN;
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_MAG_CTL_3, &cmd_byte, 1 );
    
    return error_check;
}

err_t c6dofimu13_accel_init ( c6dofimu13_t *ctx, uint8_t samp_rate, uint8_t samp_range, uint8_t samp_res )
{
    uint8_t cmd_byte;
    float res_val;
    float range_val;
    err_t error_check;

    error_check = c6dofimu13_set_slave_address ( ctx, ctx->slave_address );
    
    cmd_byte = C6DOFIMU13_ACCEL_MODE_STDBY;
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_ACCEL_MODE, &cmd_byte, 1 );

    cmd_byte = samp_rate & 0x0F;
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_ACCEL_SRTFR, &cmd_byte, 1 );

    cmd_byte = ( samp_range & 0x70 ) | ( samp_res & 0x07 );
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_ACCEL_OUTCFG, &cmd_byte, 1 );
    
    switch( samp_res )
    {
        case C6DOFIMU13_ACCEL_OUTCFG_RES_6:
        {
            res_val = 32.0;
            break;
        }
        case C6DOFIMU13_ACCEL_OUTCFG_RES_7:
        {
            res_val = 64.0;
            break;
        }
        case C6DOFIMU13_ACCEL_OUTCFG_RES_8:
        {
            res_val = 128.0;
            break;
        }
        case C6DOFIMU13_ACCEL_OUTCFG_RES_10:
        {
            res_val = 512.0;
            break;
        }
        case C6DOFIMU13_ACCEL_OUTCFG_RES_12:
        {
            res_val = 2048.0;
            break;
        }
        case C6DOFIMU13_ACCEL_OUTCFG_RES_14:
        {
            res_val = 8192.0;
            break;
        }
        default:
        {
            res_val = 32.0;
            break;
        }
    }
    
    switch( samp_range )
    {
        case C6DOFIMU13_ACCEL_OUTCFG_RANGE_2:
        {
            range_val = 2.0;
            break;
        }
        case C6DOFIMU13_ACCEL_OUTCFG_RANGE_4:
        {
            range_val = 4.0;
            break;
        }
        case C6DOFIMU13_ACCEL_OUTCFG_RANGE_8:
        {
            range_val = 8.0;
            break;
        }
        case C6DOFIMU13_ACCEL_OUTCFG_RANGE_16:
        {
            range_val = 16.0;
            break;
        }
        default:
        {
            range_val = 2.0;
            break;
        }
    }

    ctx->calc_coef = res_val / range_val;
    
    cmd_byte = C6DOFIMU13_ACCEL_MODE_WAKE;
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_ACCEL_MODE, &cmd_byte, 1 );
    
    return error_check;
}

err_t c6dofimu13_accel_get_raw_x ( c6dofimu13_t *ctx, int16_t *result )
{
    uint8_t rx_buf[ 2 ];
    uint8_t res;
    err_t error_check;
    
    error_check = c6dofimu13_set_slave_address ( ctx, ctx->slave_address );
    
    error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_ACCEL_OUTCFG, &res, 1 );
    res &= 0x07;
    
    if ( res < C6DOFIMU13_ACCEL_OUTCFG_RES_10 )
    {
        error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_ACCEL_XOUT_EX_L, rx_buf, 1 );
        *result = rx_buf[ 0 ];
        switch( res )
        {
            case C6DOFIMU13_ACCEL_OUTCFG_RES_6:
            {
                *result &= 0x003F;
                if ( *result > 0x001F )
                {
                    dev_get_twos_comp( result, 6 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_7:
            {
                *result &= 0x007F;
                if ( *result > 0x003F )
                {
                    dev_get_twos_comp( result, 7 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_8:
            {
                *result &= 0x00FF;
                if ( *result > 0x007F )
                {
                    dev_get_twos_comp( result, 8 );
                }
                break;
            }
            default:
            {
                *result &= 0x003F;
                if ( *result > 0x001F )
                {
                    dev_get_twos_comp( result, 6 );
                }
            }
        }
    }
    else
    {
        error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_ACCEL_XOUT_EX_L, rx_buf, 2 );
        *result = rx_buf[ 1 ];
        *result <<= 8;
        *result |= rx_buf[ 0 ];
        
        switch( res )
        {
            case C6DOFIMU13_ACCEL_OUTCFG_RES_10:
            {
                *result &= 0x03FF;
                if ( *result > 0x01FF )
                {
                    dev_get_twos_comp( result, 10 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_12:
            {
                *result &= 0x0FFF;
                if ( *result > 0x07FF )
                {
                    dev_get_twos_comp( result, 12 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_14:
            {
                *result &= 0x3FFF;
                if ( *result > 0x1FFF )
                {
                    dev_get_twos_comp( result, 14 );
                }
                break;
            }
            default:
            {
                *result &= 0x03FF;
                if ( *result > 0x01FF )
                {
                    dev_get_twos_comp( result, 10 );
                }
                break;
            }
        }
    }

    return error_check;
}

err_t c6dofimu13_accel_get_raw_y ( c6dofimu13_t *ctx, int16_t *result )
{
    uint8_t rx_buf[ 2 ];
    uint8_t res;
    err_t error_check;
    
    error_check = c6dofimu13_set_slave_address ( ctx, ctx->slave_address );
    
    error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_ACCEL_OUTCFG, &res, 1 );
    res &= 0x07;
    
    if ( res < C6DOFIMU13_ACCEL_OUTCFG_RES_10 )
    {
        error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_ACCEL_YOUT_EX_L, rx_buf, 1 );
        *result = rx_buf[ 0 ];
        switch( res )
        {
            case C6DOFIMU13_ACCEL_OUTCFG_RES_6:
            {
                *result &= 0x003F;
                if ( *result > 0x001F )
                {
                    dev_get_twos_comp( result, 6 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_7:
            {
                *result &= 0x007F;
                if ( *result > 0x003F )
                {
                    dev_get_twos_comp( result, 7 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_8:
            {
                *result &= 0x00FF;
                if ( *result > 0x007F )
                {
                    dev_get_twos_comp( result, 8 );
                }
                break;
            }
            default:
            {
                *result &= 0x003F;
                if ( *result > 0x001F )
                {
                    dev_get_twos_comp( result, 6 );
                }
            }
        }
    }
    else
    {
        error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_ACCEL_YOUT_EX_L, rx_buf, 2 );
        *result = rx_buf[ 1 ];
        *result <<= 8;
        *result |= rx_buf[ 0 ];
        
        switch( res )
        {
            case C6DOFIMU13_ACCEL_OUTCFG_RES_10:
            {
                *result &= 0x03FF;
                if ( *result > 0x01FF )
                {
                    dev_get_twos_comp( result, 10 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_12:
            {
                *result &= 0x0FFF;
                if ( *result > 0x07FF )
                {
                    dev_get_twos_comp( result, 12 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_14:
            {
                *result &= 0x3FFF;
                if ( *result > 0x1FFF )
                {
                    dev_get_twos_comp( result, 14 );
                }
                break;
            }
            default:
            {
                *result &= 0x03FF;
                if ( *result > 0x01FF )
                {
                    dev_get_twos_comp( result, 10 );
                }
                break;
            }
        }
    }

    return error_check;
}

err_t c6dofimu13_accel_get_raw_z ( c6dofimu13_t *ctx, int16_t *result )
{
    uint8_t rx_buf[ 2 ];
    uint8_t res;
    err_t error_check;
    
    error_check = c6dofimu13_set_slave_address ( ctx, ctx->slave_address );
    
    error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_ACCEL_OUTCFG, &res, 1 );
    res &= 0x07;
    
    if ( res < C6DOFIMU13_ACCEL_OUTCFG_RES_10 )
    {
        error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_ACCEL_ZOUT_EX_L, rx_buf, 1 );
        *result = rx_buf[ 0 ];
        switch( res )
        {
            case C6DOFIMU13_ACCEL_OUTCFG_RES_6:
            {
                *result &= 0x003F;
                if ( *result > 0x001F )
                {
                    dev_get_twos_comp( result, 6 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_7:
            {
                *result &= 0x007F;
                if ( *result > 0x003F )
                {
                    dev_get_twos_comp( result, 7 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_8:
            {
                *result &= 0x00FF;
                if ( *result > 0x007F )
                {
                    dev_get_twos_comp( result, 8 );
                }
                break;
            }
            default:
            {
                *result &= 0x003F;
                if ( *result > 0x001F )
                {
                    dev_get_twos_comp( result, 6 );
                }
            }
        }
    }
    else
    {
        error_check |= c6dofimu13_generic_read( ctx, C6DOFIMU13_ACCEL_ZOUT_EX_L, rx_buf, 2 );
        *result = rx_buf[ 1 ];
        *result <<= 8;
        *result |= rx_buf[ 0 ];
        
        switch( res )
        {
            case C6DOFIMU13_ACCEL_OUTCFG_RES_10:
            {
                *result &= 0x03FF;
                if ( *result > 0x01FF )
                {
                    dev_get_twos_comp( result, 10 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_12:
            {
                *result &= 0x0FFF;
                if ( *result > 0x07FF )
                {
                    dev_get_twos_comp( result, 12 );
                }
                break;
            }
            case C6DOFIMU13_ACCEL_OUTCFG_RES_14:
            {
                *result &= 0x3FFF;
                if ( *result > 0x1FFF )
                {
                    dev_get_twos_comp( result, 14 );
                }
                break;
            }
            default:
            {
                *result &= 0x03FF;
                if ( *result > 0x01FF )
                {
                    dev_get_twos_comp( result, 10 );
                }
                break;
            }
        }
    }

    return error_check;
}

err_t c6dofimu13_accel_get_x ( c6dofimu13_t *ctx, float *result )
{
    int16_t adc_val;
    err_t error_check;

    error_check = c6dofimu13_accel_get_raw_x( ctx, &adc_val );

    *result = ( float ) adc_val;
    *result /= ctx->calc_coef;

    return error_check;
}

err_t c6dofimu13_accel_get_y ( c6dofimu13_t *ctx, float *result )
{
    int16_t adc_val;
    err_t error_check;

    error_check = c6dofimu13_accel_get_raw_y( ctx, &adc_val );

    *result = ( float ) adc_val;
    *result /= ctx->calc_coef;

    return error_check;
}

err_t c6dofimu13_accel_get_z ( c6dofimu13_t *ctx, float *result )
{
    int16_t adc_val;
    err_t error_check;

    error_check = c6dofimu13_accel_get_raw_z( ctx, &adc_val );

    *result = ( float ) adc_val;
    *result /= ctx->calc_coef;

    return error_check;
}

err_t c6dofimu13_accel_get_data ( c6dofimu13_t *ctx, float *accel_x, float *accel_y, float *accel_z )
{
    err_t error_check;
    
    error_check = c6dofimu13_accel_get_x( ctx, accel_x );
    error_check |= c6dofimu13_accel_get_y( ctx, accel_y );
    error_check |= c6dofimu13_accel_get_z( ctx, accel_z );
    
    return error_check;
}

err_t c6dofimu13_accel_offset ( c6dofimu13_t *ctx, int16_t offset, uint8_t axis )
{
    uint8_t cmd_byte;
    uint8_t tx_buf[ 2 ];
    err_t error_check;
    
    error_check = c6dofimu13_set_slave_address ( ctx, ctx->slave_address );

    cmd_byte = C6DOFIMU13_ACCEL_MODE_STDBY;
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_ACCEL_MODE, &cmd_byte, 1 );

    tx_buf[ 0 ] = offset & 0xFF;
    tx_buf[ 1 ] = ( offset >> 8 ) & 0xFF;
    switch ( axis )
    {
        case C6DOFIMU13_ACCEL_AXIS_X :
        {
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_ACCEL_XOFFL, tx_buf, 2 );
        }
        case C6DOFIMU13_ACCEL_AXIS_Y :
        {
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_ACCEL_YOFFL, tx_buf, 2 );
        }
        case C6DOFIMU13_ACCEL_AXIS_Z :
        {
            error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_ACCEL_ZOFFL, tx_buf, 2 );
        }
    }

    cmd_byte = C6DOFIMU13_ACCEL_MODE_WAKE;
    error_check |= c6dofimu13_generic_write( ctx, C6DOFIMU13_ACCEL_MODE, &cmd_byte, 1 );
    
    return error_check;
}

uint8_t c6dofimu13_get_in1 ( c6dofimu13_t *ctx )
{
    return digital_in_read ( &ctx->in1 );
}

uint8_t c6dofimu13_get_in2 ( c6dofimu13_t *ctx )
{
    return digital_in_read ( &ctx->in2 );
}

static void dev_get_twos_comp ( int16_t *raw, uint8_t length )
{
    if ( *raw & ( ( uint16_t )1 << ( length - 1 ) ) )
    {
        *raw -= ( uint16_t )1 << length;
    }
}

// ------------------------------------------------------------------------- END



