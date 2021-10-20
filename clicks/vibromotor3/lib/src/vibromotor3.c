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
 * @file vibromotor3.c
 * @brief Vibro Motor 3 Click Driver.
 */

#include "vibromotor3.h"

void vibromotor3_cfg_setup ( vibromotor3_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = VIBROMOTOR3_SET_DEV_ADDR;
    
    cfg->dev_pwm_freq = VIBROMOTOR3_DEF_FREQ;
}

err_t vibromotor3_init ( vibromotor3_t *ctx, vibromotor3_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;
    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->en, cfg->en );
    
    pwm_config_t pwm_cfg;
    pwm_configure_default( &pwm_cfg );
    
	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR ) {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );
    
    return I2C_MASTER_SUCCESS;
}

err_t vibromotor3_default_cfg ( vibromotor3_t *ctx )  {
    vibromotor3_set_lra_mode( ctx, VIBROMOTOR3_PROPERTY_ENABLE );
    vibromotor3_write_byte( ctx, VIBROMOTOR3_CTRL3, VIBROMOTOR3_LRA_OPEN_LOOP );
    vibromotor3_set_mode( ctx, VIBROMOTOR3_PWM_ANALOG );
    vibromotor3_set_library( ctx, VIBROMOTOR3_ROM_LRA );
    vibromotor3_start_motor( ctx, VIBROMOTOR3_GO );
    return VIBROMOTOR3_OK;
}

err_t vibromotor3_generic_write ( vibromotor3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t vibromotor3_generic_read ( vibromotor3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t vibromotor3_set_duty_cycle ( vibromotor3_t *ctx, float duty_cycle ) {
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t vibromotor3_pwm_stop ( vibromotor3_t *ctx ) {
    return pwm_stop( &ctx->pwm );
}

err_t vibromotor3_pwm_start ( vibromotor3_t *ctx ) {
    return pwm_start( &ctx->pwm );
}

void vibromotor3_enable ( vibromotor3_t *ctx, uint8_t state ) { 
    if ( state == VIBROMOTOR3_PROPERTY_ENABLE ) {
        digital_out_high( &ctx->en );
    } else {
        digital_out_low( &ctx->en );
    }
}

void vibromotor3_write_byte ( vibromotor3_t *ctx, uint8_t reg, uint8_t wr_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = wr_data;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t vibromotor3_read_byte ( vibromotor3_t *ctx, uint8_t reg ) {
    uint8_t res = 0;

    i2c_master_write( &ctx->i2c, &reg, 1 );
    i2c_master_read( &ctx->i2c, &res, 1 );
    
    return res;
}

void vibromotor3_set_mode ( vibromotor3_t *ctx, uint8_t mode_sel ) {
    switch( mode_sel ) {
        case 0: {
            vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_INT_TRIG );
            break;
        }
        case 1: {
            vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_EXT_TRIG_EDGE );
            break;
        }
        case 2: {
            vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_EXT_TRIG_LEVEL );
            break;
        }
        case 3: {
            vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_PWM_ANALOG );
            break;
        }
        case 4: {
            vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_AUDIO2HAPTIC );
            break;
        }
        case 5: {
            vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_RTP );
            break;
        }
        case 6: {
            vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_DIAGNOSTICS );
            break;
        }
        case 7: {
            vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_AUTO_CALIBRATION );
            break;
        }
        default: {
            vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_STANDBY );
            break;
        }
    }
}

void vibromotor3_soft_rst ( vibromotor3_t *ctx ) {
    vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, VIBROMOTOR3_DEV_RESRT );
}

void vibromotor3_stb_mode ( vibromotor3_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val;

    aux_reg_val = vibromotor3_read_byte( ctx, VIBROMOTOR3_MODE );

    if ( state == 0 ) {
        aux_reg_val &= ~VIBROMOTOR3_STANDBY;
    } else if ( state == 1 ) {
        aux_reg_val |= VIBROMOTOR3_STANDBY;
    }

    vibromotor3_write_byte( ctx, VIBROMOTOR3_MODE, aux_reg_val );
}

uint8_t vibromotor3_get_stat ( vibromotor3_t *ctx ) {
    uint8_t res;

    res = vibromotor3_read_byte( ctx, VIBROMOTOR3_STATUS );

    return res;
}

void vibromotor3_set_rtp_input ( vibromotor3_t *ctx, uint8_t data_in ) {
    vibromotor3_write_byte( ctx, VIBROMOTOR3_RT_PB_IN, data_in );
}

void vibromotor3_set_state_hi_z ( vibromotor3_t *ctx, uint8_t state ) {
    uint8_t tmp_val;

    tmp_val = vibromotor3_read_byte( ctx, VIBROMOTOR3_LIB_SEL );

    if ( state == 0 ) {
        tmp_val &= ~VIBROMOTOR3_HIZ;
    } else if ( state == 1 ) {
        tmp_val |= VIBROMOTOR3_HIZ;
    }

    vibromotor3_write_byte( ctx, VIBROMOTOR3_LIB_SEL, tmp_val );
}

void vibromotor3_set_library ( vibromotor3_t *ctx, uint8_t lib_sel ) {
    uint8_t tmp_val;

    tmp_val = vibromotor3_read_byte( ctx, VIBROMOTOR3_LIB_SEL );

    tmp_val &= 0xF8;

    switch ( lib_sel ) {
        case 0: {
            tmp_val |= VIBROMOTOR3_RAM;
            break;
        }
        case 1: {
            tmp_val |= VIBROMOTOR3_ROM_A;
            break;
        }
        case 2: {
            tmp_val |= VIBROMOTOR3_ROM_B;
            break;
        }
        case 3: {
            tmp_val |= VIBROMOTOR3_ROM_C;
            break;
        }
        case 4: {
            tmp_val |= VIBROMOTOR3_ROM_D;
            break;
        }
        case 5: {
            tmp_val |= VIBROMOTOR3_ROM_E;
            break;
        }
        case 6: {
            tmp_val |= VIBROMOTOR3_ROM_LRA;
            break;
        }
        default: {
            tmp_val |= VIBROMOTOR3_RAM;
            break;
        }
    }

    vibromotor3_write_byte( ctx, VIBROMOTOR3_LIB_SEL, tmp_val );
}

void vibromotor3_start_motor ( vibromotor3_t *ctx, uint8_t state ) {
    if ( state == VIBROMOTOR3_STOP ) {
        vibromotor3_write_byte( ctx, VIBROMOTOR3_REG_GO, VIBROMOTOR3_STOP );
    } else if ( state == VIBROMOTOR3_GO ) {
        vibromotor3_write_byte( ctx, VIBROMOTOR3_REG_GO, VIBROMOTOR3_GO );
    }
}

void vibromotor3_set_ovdr_offset ( vibromotor3_t *ctx, uint8_t data_in ) {
    vibromotor3_write_byte( ctx, VIBROMOTOR3_OVERDRIVE_OFFS, data_in );
}

void vibromotor3_set_sustain_offset_pos ( vibromotor3_t *ctx, uint8_t data_in ) {
    vibromotor3_write_byte( ctx, VIBROMOTOR3_SUSTAIN_P_OFFS, data_in );
}

void vibromotor3_set_sustain_offset_neg ( vibromotor3_t *ctx, uint8_t data_in ) {
    vibromotor3_write_byte( ctx, VIBROMOTOR3_SUSTAIN_N_OFFS, data_in );
}

void vibromotor3_set_brake_time_offset ( vibromotor3_t *ctx, uint8_t data_in ) {
    vibromotor3_write_byte( ctx, VIBROMOTOR3_BRAKE_OFF, data_in );
}

void vibromotor3_set_rated_volt ( vibromotor3_t *ctx, uint8_t data_in ) {
    vibromotor3_write_byte( ctx, VIBROMOTOR3_RATED_VOLT, data_in );
}

void vibromotor3_set_ovdrv_clamp_volt ( vibromotor3_t *ctx, uint8_t data_in ) {
    vibromotor3_write_byte( ctx, VIBROMOTOR3_OD_CLAMP_VOLT, data_in );
}

uint8_t vibromotor3_get_calib_res_comp ( vibromotor3_t *ctx ) {
    uint8_t tmp;
    uint8_t res;

    tmp = vibromotor3_read_byte( ctx, VIBROMOTOR3_CAL_COMP );
    
    res = ( 1 + tmp ) / 255;

    return res;
}

float vibromotor3_get_supply_volt_val ( vibromotor3_t *ctx ) {
    uint8_t tmp;
    float res;

    tmp = vibromotor3_read_byte( ctx, VIBROMOTOR3_VBAT_MON );
    
    res = ( (float)tmp * 5.6 ) / 255.0;

    return res;
}

float vibromotor3_get_lra_resonance_period ( vibromotor3_t *ctx ) {
    uint8_t tmp;
    float res;

    tmp = vibromotor3_read_byte( ctx, VIBROMOTOR3_LRA_RES_PERIOD );

    res = (float)res * 98.46;

    return tmp;
}

void vibromotor3_set_lra_mode ( vibromotor3_t *ctx, uint8_t state ) {
    uint8_t tmp_val;

    tmp_val = vibromotor3_read_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL );

    if ( state == 0 ) {
        tmp_val |= VIBROMOTOR3_ERM_MODE;
    } else if ( state == 1 ) {
        tmp_val |= VIBROMOTOR3_LRA_MODE;
    }

    vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
}

void vibromotor3_set_brake_factor ( vibromotor3_t *ctx, uint8_t brk_fac ) {
    uint8_t tmp_val;

    tmp_val = vibromotor3_read_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL );
    tmp_val &= 0x8F;

    switch ( brk_fac ) {
        case 0: {
            tmp_val |= VIBROMOTOR3_FB_BRAKE_FAC_DIS;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 1: {
            tmp_val |= VIBROMOTOR3_FB_BRAKE_FAC_1X;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 2: {
            tmp_val |= VIBROMOTOR3_FB_BRAKE_FAC_2X;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 3: {
            tmp_val |=  VIBROMOTOR3_FB_BRAKE_FAC_3X;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 4: {
            tmp_val |= VIBROMOTOR3_FB_BRAKE_FAC_4X;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 6: {
            tmp_val |= VIBROMOTOR3_FB_BRAKE_FAC_6X;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 8: {
            tmp_val |= VIBROMOTOR3_FB_BRAKE_FAC_8X;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 16: {
            tmp_val |= VIBROMOTOR3_FB_BRAKE_FAC_16X;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        default: {
            tmp_val |= VIBROMOTOR3_FB_BRAKE_FAC_DIS;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
    }
}

void vibromotor3_set_loop_gain ( vibromotor3_t *ctx, uint8_t gain ) {
    uint8_t tmp_val;

    tmp_val = vibromotor3_read_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL );

    switch ( gain ) {
        case 0: {
            tmp_val |= VIBROMOTOR3_LOOP_RESP_SLOW;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 1: {
            tmp_val |= VIBROMOTOR3_LOOP_RESP_MEDIUM;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 2: {
            tmp_val |= VIBROMOTOR3_LOOP_RESP_FAST;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        case 3: {
            tmp_val |= VIBROMOTOR3_LOOP_RESP_V_FAST;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
        default: {
            tmp_val |= VIBROMOTOR3_LOOP_RESP_MEDIUM;
            vibromotor3_write_byte( ctx, VIBROMOTOR3_FEEDBACK_CTRL, tmp_val );
            break;
        }
    }
}

void vibromotor3_set_input ( vibromotor3_t *ctx, uint8_t state ) {
    uint8_t aux_reg_val;

    aux_reg_val = vibromotor3_read_byte( ctx, VIBROMOTOR3_CTRL3 );

    if ( state == 0 ) {
        aux_reg_val |= VIBROMOTOR3_IN_MODE_ANALOG;
    } else if ( state == 1 ) {
        aux_reg_val &= ~VIBROMOTOR3_IN_MODE_ANALOG;
    }

    vibromotor3_write_byte( ctx, VIBROMOTOR3_CTRL3, aux_reg_val );
}

void vibromotor3_enable_ac_coulping ( vibromotor3_t *ctx ) {
    vibromotor3_write_byte( ctx, VIBROMOTOR3_CTRL1, VIBROMOTOR3_DRV_TIME_2P4M | VIBROMOTOR3_AC_COUPLE | VIBROMOTOR3_STARTPPBOOST );
}

// ------------------------------------------------------------------------- END
