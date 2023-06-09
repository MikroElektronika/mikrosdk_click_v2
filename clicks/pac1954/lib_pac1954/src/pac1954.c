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
 * @file pac1954.c
 * @brief PAC1954 Click Driver.
 */

#include "pac1954.h"

/**
 * @brief PAC1954 Measurement Full Scale Range Definition.
 * @details Specified full scale range for all measurements.
 */
#define PAC1954_FSR_VSOURCE_V  32
#define PAC1954_FSR_ISENSE_A   25
#define PAC1954_FSR_PSENSE_W   800

void pac1954_cfg_setup ( pac1954_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en      = HAL_PIN_NC;
    cfg->slw     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PAC1954_DEV_ADDR_0;
}

err_t pac1954_init ( pac1954_t *ctx, pac1954_cfg_t *cfg ) 
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

    digital_out_init( &ctx->slw, cfg->slw );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t pac1954_default_cfg ( pac1954_t *ctx ) 
{
    uint8_t dflt_cfg[ 2 ];
    
    pac1954_enable ( ctx, PAC1954_DEV_ENABLE );
    Delay_100ms( );

    dflt_cfg[ 0 ] = PAC1954_CTRLH_SPS_1024_ADAPT_ACC | 
                    PAC1954_CTRLH_INT_PIN_ALERT | 
                    PAC1954_CTRLH_SLW_PIN_SLOW;
    dflt_cfg[ 1 ] = PAC1954_CTRLL_ALL_CH_ON;

    err_t error_flag = pac1954_generic_write ( ctx, PAC1954_REG_CTRL, dflt_cfg, 2 );
    
    dflt_cfg[ 0 ] = ( PAC1954_MEAS_MODE_BIPOLAR_FSR << PAC1954_NEG_PWR_FSR_CH1_OFFSET ) |
                    ( PAC1954_MEAS_MODE_BIPOLAR_HALF_FSR << PAC1954_NEG_PWR_FSR_CH2_OFFSET ) |
                    ( PAC1954_MEAS_MODE_UNIPOLAR_FSR << PAC1954_NEG_PWR_FSR_CH3_OFFSET ) |
                    ( PAC1954_MEAS_MODE_UNIPOLAR_FSR << PAC1954_NEG_PWR_FSR_CH4_OFFSET );
    dflt_cfg[ 1 ] = ( PAC1954_MEAS_MODE_BIPOLAR_FSR << PAC1954_NEG_PWR_FSR_CH1_OFFSET ) |
                    ( PAC1954_MEAS_MODE_BIPOLAR_HALF_FSR << PAC1954_NEG_PWR_FSR_CH2_OFFSET ) |
                    ( PAC1954_MEAS_MODE_UNIPOLAR_FSR << PAC1954_NEG_PWR_FSR_CH3_OFFSET ) |
                    ( PAC1954_MEAS_MODE_UNIPOLAR_FSR << PAC1954_NEG_PWR_FSR_CH4_OFFSET );

    error_flag |= pac1954_generic_write ( ctx, PAC1954_REG_NEG_PWR_FSR, dflt_cfg, 2 );
    
    pac1954_set_ch_8_sps ( ctx, PAC1954_ALL_CH_SAMPLE_8SPS_OFF );
    Delay_100ms( );
    
    return error_flag;
}

err_t pac1954_generic_write ( pac1954_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = tx_buf[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t pac1954_generic_read ( pac1954_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t pac1954_single_write ( pac1954_t *ctx, uint8_t reg, uint8_t data_in )
{
    return pac1954_generic_write( ctx, reg, &data_in, 1 );
}

err_t pac1954_single_read ( pac1954_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return pac1954_generic_read ( ctx, reg, data_out, 1 );
}

err_t pac1954_set_address_pointer ( pac1954_t *ctx, uint8_t reg )
{
    return i2c_master_write( &ctx->i2c, &reg, 1 );
}

err_t pac1954_read_last_access_reg ( pac1954_t *ctx, uint8_t *data_out )
{
    return i2c_master_read( &ctx->i2c, data_out, 1 );
}

err_t pac1954_refresh_cmd ( pac1954_t *ctx )
{
    err_t error_flag = pac1954_set_address_pointer( ctx, PAC1954_REG_REFRESH );
    Delay_1ms( );
    return error_flag;
}

err_t pac1954_vol_refresh_cmd ( pac1954_t *ctx )
{
    err_t error_flag = pac1954_set_address_pointer( ctx, PAC1954_REG_REFRESH_V );
    Delay_1ms( );
    return error_flag;
}

err_t pac1954_get_measurement ( pac1954_t *ctx, uint8_t meas_sel, uint8_t ch_sel, 
                                uint8_t avg_sel, uint32_t *data_out )
{
    uint8_t tmp_data[ 4 ] = { 0 };
    uint8_t n_bytes;
    
    switch ( meas_sel )
    {
        case PAC1954_MEAS_SEL_V_SOURCE :
        {
            if ( avg_sel == PAC1954_AVG_SEL_DISABLE )
            {
                tmp_data[ 0 ] = 0x06;
            }
            else
            {
                tmp_data[ 0 ] = 0x0E;
            }
            
            n_bytes = 2;
            break;
        }
        case PAC1954_MEAS_SEL_I_SENSE :
        {
            if ( avg_sel == PAC1954_AVG_SEL_DISABLE )
            {
                tmp_data[ 0 ] = 0x0A;
            }
            else
            {
                tmp_data[ 0 ] = 0x12;
            }
            
            n_bytes = 2;
            break;
        }
        case PAC1954_MEAS_SEL_P_SENSE :
        {
            tmp_data[ 0 ] = 0x16;
            n_bytes = 4;
            break;
        }
        default :
        {
            return PAC1954_ERROR;
        }
    }
    
    if ( ( ch_sel < PAC1954_CH_SEL_CH_1 ) || ( ch_sel > PAC1954_CH_SEL_CH_4 ) )
    {
        return PAC1954_ERROR;
    }
    
    tmp_data[ 0 ] += ch_sel;
    
    err_t error_flag = pac1954_generic_read( ctx, tmp_data[ 0 ], tmp_data, n_bytes );
    
    for ( uint8_t cnt = 0; cnt < n_bytes; cnt++ )
    {
        if ( cnt == 3 )
        {
            *data_out <<= 6;
            *data_out |= tmp_data[ cnt ] >> 2;
        }
        else
        {
            *data_out <<= 8;
            *data_out |= tmp_data[ cnt ];
        }
    }
    
    return error_flag;
}

err_t pac1954_get_acc_count ( pac1954_t *ctx, uint32_t *data_out )
{
    uint8_t tmp_data[ 4 ] = { 0 };
    
    tmp_data[ 0 ] = PAC1954_REG_ACC_COUNT;
    
    err_t error_flag = pac1954_generic_read( ctx, tmp_data[ 0 ], tmp_data, 4 );
    
    *data_out = tmp_data[ 0 ];
    *data_out <<= 8;
    *data_out |= tmp_data[ 1 ];
    *data_out <<= 8;
    *data_out |= tmp_data[ 2 ];
    *data_out <<= 8;
    *data_out |= tmp_data[ 3 ];

    return error_flag;
}

err_t pac1954_get_acc_output ( pac1954_t *ctx, uint8_t ch_sel, uint8_t *data_out )
{
    if ( ( ch_sel < PAC1954_CH_SEL_CH_1 ) || ( ch_sel > PAC1954_CH_SEL_CH_4 ) )
    {
        return PAC1954_ERROR;
    }
    
    return pac1954_generic_read( ctx, ch_sel + 0x02, data_out, 7 );
}

err_t pac1954_get_calc_measurement ( pac1954_t *ctx, uint8_t meas_sel, uint8_t ch_sel, 
                                     uint8_t avg_sel, uint8_t meas_mode, float *data_out )
{
    uint32_t ret_val = 0;
    volatile int16_t ret_val_16_sign;
    volatile int32_t ret_val_32_sign;
    
    if ( ( ch_sel < PAC1954_CH_SEL_CH_1 ) || ( ch_sel > PAC1954_CH_SEL_CH_4 ) )
    {
        return PAC1954_ERROR;
    }

    err_t error_flag = pac1954_get_measurement( ctx, meas_sel, ch_sel, avg_sel, &ret_val );
    
    switch ( meas_sel )
    {
        case PAC1954_MEAS_SEL_V_SOURCE :
        {
            if ( meas_mode == PAC1954_MEAS_MODE_UNIPOLAR_FSR )
            {
                *data_out = ret_val;
                *data_out /= 0x10000;
                *data_out *= PAC1954_FSR_VSOURCE_V;
            }
            else
            {
                ret_val_16_sign = ( int16_t ) ret_val;
                *data_out = ret_val_16_sign;
                *data_out /= 0x8000;
                *data_out *= PAC1954_FSR_VSOURCE_V;
                
                if ( meas_mode != PAC1954_MEAS_MODE_BIPOLAR_FSR )
                {
                    *data_out /= 0x02;
                }
            }
            break;
        }
        case PAC1954_MEAS_SEL_I_SENSE :
        {
            if ( meas_mode == PAC1954_MEAS_MODE_UNIPOLAR_FSR )
            {
                *data_out = ret_val;
                *data_out /= 0x10000;
                *data_out *= PAC1954_FSR_ISENSE_A;
            }
            else
            {
                ret_val_16_sign = ( int16_t ) ret_val;
                *data_out = ret_val_16_sign;
                *data_out /= 0x8000;
                *data_out *= PAC1954_FSR_ISENSE_A;
                
                if ( meas_mode != PAC1954_MEAS_MODE_BIPOLAR_FSR )
                {
                    *data_out /= 0x02;
                }
            }
            break;
        }
        case PAC1954_MEAS_SEL_P_SENSE :
        {
            if ( meas_mode == PAC1954_MEAS_MODE_UNIPOLAR_FSR )
            {
                *data_out = ret_val;
                *data_out /= 0x40000000;
                *data_out *= PAC1954_FSR_PSENSE_W;
            }
            else
            {
                ret_val_32_sign = ( int32_t ) ret_val;
                
                if ( ret_val & 0x20000000 )
                {
                    ret_val_32_sign |= 0xC0000000;
                }
                
                *data_out = ret_val_32_sign;
                *data_out /= 0x20000000;
                *data_out *= PAC1954_FSR_PSENSE_W;
                
                if ( meas_mode != PAC1954_MEAS_MODE_BIPOLAR_FSR )
                {
                    *data_out /= 0x02;
                }
            }
            break;
        }
        default :
        {
            return PAC1954_ERROR;
        }
    }

    return error_flag;
}

void pac1954_set_ch_8_sps ( pac1954_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->slw, state );
}

void pac1954_enable ( pac1954_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en, state );
}

uint8_t pac1954_get_alert2_status ( pac1954_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
