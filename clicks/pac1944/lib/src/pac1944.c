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
 * @file pac1944.c
 * @brief PAC1944 Click Driver.
 */

#include "pac1944.h"

// ------------------------------------------------------------- PRIVATE MACROS
    
#define DUMMY                                         0

#define PAC1944_NULL                                  0

#define PAC1944_FSR_VSOURCE_V                         9
#define PAC1944_FSR_ISENSE_A                          25
#define PAC1944_FSR_PSENSE_W                          225

#define PAC1944_NEG_PWR_FSR_CH1_OFFSET                6
#define PAC1944_NEG_PWR_FSR_CH2_OFFSET                4
#define PAC1944_NEG_PWR_FSR_CH3_OFFSET                2
#define PAC1944_NEG_PWR_FSR_CH4_OFFSET                0

#define PAC1944_CALC_DENOMINATOR_UNIPOLAR             65536
#define PAC1944_CALC_DENOMINATOR_BIPOLAR              32768

#define PAC1944_CALC_PWR_DENOMINATOR_UNIPOLAR         1073741824
#define PAC1944_CALC_PWR_DENOMINATOR_BIPOLAR          536870912

#define PAC1944_TWOS_COMP_PWR_SIGN_NEGATIVE           0x20000000
#define PAC1944_TWOS_COMP_PWR_SIGN_CONV               0xC0000000

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pac1944_cfg_setup ( pac1944_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->slw = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PAC1944_DEVICE_ADDR_GND;
}

err_t pac1944_init ( pac1944_t *ctx, pac1944_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->slw, cfg->slw );
    digital_out_init( &ctx->en, cfg->en );
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

void pac1944_default_cfg ( pac1944_t *ctx ) {
    pac1944_setup_t setup_cfg_data;
    
    setup_cfg_data.sample_mode = PAC1944_CTRLH_SPS_1024_ADAPT_ACC;
    setup_cfg_data.gpio_alert2 = PAC1944_CTRLH_INT_PIN_ALERT;
    setup_cfg_data.slow_alert1 = PAC1944_CTRLH_SLW_PIN_SLOW;
    setup_cfg_data.channels_state = PAC1944_CTRLL_ALL_CH_ON;

    setup_cfg_data.cfg_vsense1 = PAC1944_MEAS_MODE_BIPOLAR_FSR;
    setup_cfg_data.cfg_vsense2 = PAC1944_MEAS_MODE_BIPOLAR_HALF_FSR;
    setup_cfg_data.cfg_vsense3 = PAC1944_MEAS_MODE_UNIPOLAR_FSR;
    setup_cfg_data.cfg_vsense4 = PAC1944_MEAS_MODE_UNIPOLAR_FSR;
    
    setup_cfg_data.cfg_vbus1 = PAC1944_MEAS_MODE_BIPOLAR_FSR;
    setup_cfg_data.cfg_vbus2 = PAC1944_MEAS_MODE_BIPOLAR_HALF_FSR;
    setup_cfg_data.cfg_vbus3 = PAC1944_MEAS_MODE_UNIPOLAR_FSR;
    setup_cfg_data.cfg_vbus4 = PAC1944_MEAS_MODE_UNIPOLAR_FSR;
    
    pac1944_setup_config( ctx, setup_cfg_data );
    
    pac1944_set_slow_state( ctx, PAC1944_SLOW_STATE_OFF );
}

void pac1944_set_slow_state ( pac1944_t *ctx, uint8_t state ) {
    digital_out_write( &ctx->slw, state );
}

void pac1944_device_state ( pac1944_t *ctx, uint8_t state ) {
    digital_out_write( &ctx->en, state );
}

uint8_t pac1944_get_alert_state ( pac1944_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

err_t pac1944_generic_write ( pac1944_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;
    
    if ( ( tx_buf != PAC1944_NULL ) && ( tx_len != 0 ) ) {
        data_buf[ 0 ] = reg;

        for ( cnt = 1; cnt <= tx_len; cnt++ ) {
            data_buf[ cnt ] = tx_buf[ cnt - 1 ];
        }

        return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
    }
}

err_t pac1944_generic_read ( pac1944_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    if ( ( rx_buf != PAC1944_NULL ) && ( rx_len != 0 ) ) {
        return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
    }
}

void pac1944_setup_config ( pac1944_t *ctx, pac1944_setup_t cfg_data ) {
    uint8_t temp_cfg[ 2 ];
    
    temp_cfg[ 0 ] = cfg_data.sample_mode | cfg_data.gpio_alert2 | cfg_data.slow_alert1;
    temp_cfg[ 1 ] = cfg_data.channels_state;

    pac1944_generic_write( ctx, PAC1944_REG_CTRL, temp_cfg, 2 );
    
    temp_cfg[ 0 ] = ( cfg_data.cfg_vsense1 << PAC1944_NEG_PWR_FSR_CH1_OFFSET ) |
                    ( cfg_data.cfg_vsense2 << PAC1944_NEG_PWR_FSR_CH2_OFFSET ) |
                    ( cfg_data.cfg_vsense3 << PAC1944_NEG_PWR_FSR_CH3_OFFSET ) |
                    ( cfg_data.cfg_vsense4 << PAC1944_NEG_PWR_FSR_CH4_OFFSET );
    temp_cfg[ 1 ] = ( cfg_data.cfg_vbus1 << PAC1944_NEG_PWR_FSR_CH1_OFFSET ) |
                    ( cfg_data.cfg_vbus2 << PAC1944_NEG_PWR_FSR_CH2_OFFSET ) |
                    ( cfg_data.cfg_vbus3 << PAC1944_NEG_PWR_FSR_CH3_OFFSET ) |
                    ( cfg_data.cfg_vbus4 << PAC1944_NEG_PWR_FSR_CH4_OFFSET );

    pac1944_generic_write( ctx, PAC1944_REG_NEG_PWR_FSR, temp_cfg, 2 );
}

void pac1944_set_address_pointer ( pac1944_t *ctx, uint8_t reg_addr ) {
    uint8_t tmp_data;
    
    tmp_data = reg_addr;
    
    i2c_master_write( &ctx->i2c, &tmp_data, 1 );
}

uint8_t pac1944_read_last_accessed_register ( pac1944_t *ctx ) {
    uint8_t tmp_data = DUMMY;

    i2c_master_read( &ctx->i2c, &tmp_data, 1 );

    return tmp_data;
}

void pac1944_general_refresh_cmd ( pac1944_t *ctx ) {
    uint8_t tmp_data;
    uint8_t indigenous_address;

    tmp_data = PAC1944_REG_REFRESH_G;

    indigenous_address = ctx->slave_address;
    ctx->slave_address = DUMMY;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    Delay_1ms( );
    
    i2c_master_write( &ctx->i2c, &tmp_data, 1 );
    
    ctx->slave_address = indigenous_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    Delay_1ms( );
}


void pac1944_refresh_cmd ( pac1944_t *ctx ) {
    pac1944_set_address_pointer( ctx, PAC1944_REG_REFRESH );
    
    Delay_1ms( );
}

void pac1944_volatile_refresh_cmd ( pac1944_t *ctx ) {
    pac1944_set_address_pointer( ctx, PAC1944_REG_REFRESH_V );
    
    Delay_1ms( );
}

uint32_t pac1944_get_accumulator_count( pac1944_t *ctx ) {
    uint8_t tmp_data[ 4 ] = { DUMMY };
    uint32_t ret_val = DUMMY;
    
    tmp_data[ 0 ] = PAC1944_REG_ACC_COUNT;
    
    pac1944_generic_read( ctx, tmp_data[ 0 ], tmp_data, 4 );
    
    ret_val = tmp_data[ 0 ];
    ret_val <<= 8;
    ret_val |= tmp_data[ 1 ];
    ret_val <<= 8;
    ret_val |= tmp_data[ 2 ];
    ret_val <<= 8;
    ret_val |= tmp_data[ 3 ];

    return ret_val;
}

void pac1944_get_accumulator_output( pac1944_t *ctx, uint8_t ch_sel, uint8_t *acc_out ) {
    uint8_t tmp_data;
    
    if ( ( ch_sel < PAC1944_CH_SEL_CH_1 ) || ( ch_sel > PAC1944_CH_SEL_CH_4 ) )
    {
        return;
    }
    
    tmp_data = PAC1944_REG_VACC_CH1 - 1;
    tmp_data += ch_sel;
    
    pac1944_generic_read( ctx, tmp_data, acc_out, 7 );
}

uint32_t pac1944_get_measurement ( pac1944_t *ctx, uint8_t meas_sel, uint8_t ch_sel, uint8_t avg_sel ) {
    uint8_t tmp_data[ 4 ] = { DUMMY };
    uint8_t n_bytes;
    uint8_t cnt;
    uint32_t ret_val = DUMMY;
    
    switch ( meas_sel )
    {
        case PAC1944_MEAS_SEL_V_SOURCE :
        {
            if ( avg_sel == PAC1944_AVG_SEL_DISABLE )
            {
                tmp_data[ 0 ] = PAC1944_REG_VBUS_CH1 - 1;
            }
            else
            {
                tmp_data[ 0 ] = PAC1944_REG_VBUS_CH1_AVG - 1;
            }
            
            n_bytes = 2;
        break;
        }
        case PAC1944_MEAS_SEL_I_SENSE :
        {
            if ( avg_sel == PAC1944_AVG_SEL_DISABLE )
            {
                tmp_data[ 0 ] = PAC1944_REG_VSENSE_CH1 - 1;
            }
            else
            {
                tmp_data[ 0 ] = PAC1944_REG_VSENSE_CH1_AVG - 1;
            }
            
            n_bytes = 2;
        break;
        }
        case PAC1944_MEAS_SEL_P_SENSE :
        {
            tmp_data[ 0 ] = PAC1944_REG_VPOWER_CH1 - 1;
            
            n_bytes = 4;
        break;
        }
        default :
        {
            return 0;
        }
    }
    
    if ( ( ch_sel < PAC1944_CH_SEL_CH_1 ) || ( ch_sel > PAC1944_CH_SEL_CH_4 ) )
    {
        return 0;
    }
    
    tmp_data[ 0 ] += ch_sel;
    
    pac1944_generic_read( ctx, tmp_data[ 0 ], tmp_data, n_bytes );
    
    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        if ( cnt == 3 )
        {
            ret_val <<= 6;
            ret_val |= tmp_data[ cnt ] >> 2;
        }
        else
        {
            ret_val <<= 8;
            ret_val |= tmp_data[ cnt ];
        }
    }
    
    return ret_val;
}

float pac1944_get_calc_measurement ( pac1944_t *ctx, uint8_t meas_sel, uint8_t ch_sel, uint8_t avg_sel, uint8_t meas_mode ) {
    uint32_t ret_val = DUMMY;
    int16_t ret_val_16_sign;
    int32_t ret_val_32_sign;
    float res = DUMMY;
    
    if ( ( ch_sel < PAC1944_CH_SEL_CH_1 ) || ( ch_sel > PAC1944_CH_SEL_CH_4 ) )
    {
        return 0;
    }

    ret_val = pac1944_get_measurement( ctx, meas_sel, ch_sel, avg_sel );
    
    switch ( meas_sel )
    {
        case PAC1944_MEAS_SEL_V_SOURCE :
        {
            if ( meas_mode == PAC1944_MEAS_MODE_UNIPOLAR_FSR )
            {
                res = ret_val;
                res /= PAC1944_CALC_DENOMINATOR_UNIPOLAR;
                res *= PAC1944_FSR_VSOURCE_V;
            }
            else
            {
                ret_val_16_sign =  *( uint16_t* )&ret_val;
                res = ret_val_16_sign;
                res /= PAC1944_CALC_DENOMINATOR_BIPOLAR;
                res *= PAC1944_FSR_VSOURCE_V;
                
                if ( meas_mode != PAC1944_MEAS_MODE_BIPOLAR_FSR )
                {
                    res /= 2;
                }
            }
        break;
        }
        case PAC1944_MEAS_SEL_I_SENSE :
        {
            if ( meas_mode == PAC1944_MEAS_MODE_UNIPOLAR_FSR )
            {
                res = ret_val;
                res /= PAC1944_CALC_DENOMINATOR_UNIPOLAR;
                res *= PAC1944_FSR_ISENSE_A;
            }
            else
            {
                ret_val_16_sign =  *( int16_t* )&ret_val;
                res = ret_val_16_sign;
                res /= PAC1944_CALC_DENOMINATOR_BIPOLAR;
                res *= PAC1944_FSR_ISENSE_A;
                
                if ( meas_mode != PAC1944_MEAS_MODE_BIPOLAR_FSR )
                {
                    res /= 2;
                }
            }
        break;
        }
        case PAC1944_MEAS_SEL_P_SENSE :
        {
            if ( meas_mode == PAC1944_MEAS_MODE_UNIPOLAR_FSR )
            {
                res = ret_val;
                res /= PAC1944_CALC_PWR_DENOMINATOR_UNIPOLAR;
                res *= PAC1944_FSR_PSENSE_W;
            }
            else
            {
                ret_val_32_sign = *( int32_t* )&ret_val;
                
                if ( ret_val & PAC1944_TWOS_COMP_PWR_SIGN_NEGATIVE )
                {
                    ret_val_32_sign |= PAC1944_TWOS_COMP_PWR_SIGN_CONV;
                }
                
                res = ret_val_32_sign;
                res /= PAC1944_CALC_PWR_DENOMINATOR_BIPOLAR;
                res *= PAC1944_FSR_PSENSE_W;
                
                if ( meas_mode != PAC1944_MEAS_MODE_BIPOLAR_FSR )
                {
                    res /= 2;
                }
            }
        break;
        }
        default :
        {
            return 0;
        }
    }

    return res;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
