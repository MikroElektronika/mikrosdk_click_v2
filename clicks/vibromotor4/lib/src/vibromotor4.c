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
 * @file vibromotor4.c
 * @brief Vibro Motor 4 Click Driver.
 */

#include "vibromotor4.h"

/**
 * @brief Vibro Motor 4 configuration delay function.
 * @details This function performs a delay of 10 millisecond.
 * @return Nothing.
 * @note None.
 */
static void dev_cfg_delay ( void );

void vibromotor4_cfg_setup ( vibromotor4_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = VIBROMOTOR4_SET_DEV_ADDR;

    cfg->dev_pwm_freq = VIBROMOTOR4_DEFAULT_FREQUENCY;
}

err_t vibromotor4_init ( vibromotor4_t *ctx, vibromotor4_cfg_t *cfg )
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

    digital_out_init( &ctx->en, cfg->en );

    pwm_config_t pwm_cfg;
    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR )
    {
        return PWM_ERROR;
    }

    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    return I2C_MASTER_SUCCESS;
}

err_t vibromotor4_default_cfg ( vibromotor4_t *ctx )
{
    vibromotor4_set_lra_mode( ctx, VIBROMOTOR4_PROPERTY_ENABLE );
    dev_cfg_delay( );

    vibromotor4_write_byte( ctx, VIBROMOTOR4_CTRL3, VIBROMOTOR4_LRA_OPEN_LOOP );
    dev_cfg_delay( );

    vibromotor4_set_mode( ctx, VIBROMOTOR4_PWM_ANALOG );
    dev_cfg_delay( );

    vibromotor4_set_library( ctx, VIBROMOTOR4_ROM_LRA );
    dev_cfg_delay( );

    vibromotor4_start_motor( ctx, VIBROMOTOR4_GO );
    dev_cfg_delay( );

    return VIBROMOTOR4_OK;
}

err_t vibromotor4_generic_write ( vibromotor4_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len )
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t vibromotor4_generic_read ( vibromotor4_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t vibromotor4_enable ( vibromotor4_t *ctx, vibromotor4_property_mode_t pr_mode )
{
    if ( pr_mode == VIBROMOTOR4_PROPERTY_ENABLE )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }

    return VIBROMOTOR4_OK;
}

err_t vibromotor4_write_byte ( vibromotor4_t *ctx, uint8_t reg, uint8_t wr_data )
{
    return vibromotor4_generic_write( ctx, reg, &wr_data, 1 );
}

err_t vibromotor4_read_byte ( vibromotor4_t *ctx, uint8_t reg, uint8_t *rx_buf )
{
    return vibromotor4_generic_read( ctx, reg, rx_buf, 1 );
}

err_t vibromotor4_set_mode ( vibromotor4_t *ctx, uint8_t mode_sel )
{
    err_t err_flag;

    switch ( mode_sel )
    {
        case 0:
        {
            err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_INT_TRIG );
            break;
        }
        case 1:
        {
            err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_EXT_TRIG_EDGE );
            break;
        }
        case 2:
        {
            err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_EXT_TRIG_LEVEL );
            break;
        }
        case 3:
        {
            err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_PWM_ANALOG );
            break;
        }
        case 4:
        {
            err_flag =  vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_AUDIO2HAPTIC );
            break;
        }
        case 5:
        {
            err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_RTP );
            break;
        }
        case 6:
        {
            err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_DIAGNOSTICS );
            break;
        }
        case 7:
        {
            err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_AUTO_CALIBRATION );
            break;
        }
        default:
        {
            err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_STANDBY );
            break;
        }
    }

    return err_flag;
}

err_t vibromotor4_soft_rst ( vibromotor4_t *ctx )
{
    return vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, VIBROMOTOR4_DEV_RESRT );
}

err_t vibromotor4_stb_mode ( vibromotor4_t *ctx, uint8_t state )
{
    uint8_t aux_reg_val;

    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_MODE, &aux_reg_val );

    if ( state == 0 )
    {
        aux_reg_val &= ~VIBROMOTOR4_STANDBY;
    }
    else if ( state == 1 )
    {
        aux_reg_val |= VIBROMOTOR4_STANDBY;
    }

    err_flag |= vibromotor4_write_byte( ctx, VIBROMOTOR4_MODE, aux_reg_val );

    return err_flag;
}

err_t vibromotor4_get_stat ( vibromotor4_t *ctx, uint8_t *stat )
{
    return vibromotor4_read_byte( ctx, VIBROMOTOR4_STATUS, stat );
}

err_t vibromotor4_set_rtp_input ( vibromotor4_t *ctx, uint8_t rtp_input )
{
     return vibromotor4_write_byte( ctx, VIBROMOTOR4_RT_PB_IN, rtp_input );
}

err_t vibromotor4_set_state_hi_z ( vibromotor4_t *ctx, uint8_t state )
{
    uint8_t tmp;

    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_LIB_SEL, &tmp );

    if ( state == 0 )
    {
        tmp &= ~VIBROMOTOR4_HIZ;
    }
    else if ( state == 1 )
    {
        tmp |= VIBROMOTOR4_HIZ;
    }

    err_flag |= vibromotor4_write_byte( ctx, VIBROMOTOR4_LIB_SEL, tmp );

    return err_flag;
}

err_t vibromotor4_set_library ( vibromotor4_t *ctx, uint8_t lib_sel )
{
    uint8_t tmp;

    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_LIB_SEL, &tmp );

    tmp &= 0xF8;

    switch ( lib_sel )
    {
        case 0:
        {
            tmp |= VIBROMOTOR4_RAM;
            break;
        }
        case 1:
        {
            tmp |= VIBROMOTOR4_ROM_A;
            break;
        }
        case 2:
        {
            tmp |= VIBROMOTOR4_ROM_B;
            break;
        }
        case 3:
        {
            tmp |= VIBROMOTOR4_ROM_C;
            break;
        }
        case 4:
        {
            tmp |= VIBROMOTOR4_ROM_D;
            break;
        }
        case 5:
        {
            tmp |= VIBROMOTOR4_ROM_E;
            break;
        }
        case 6:
        {
            tmp |= VIBROMOTOR4_ROM_LRA;
            break;
        }
        default:
        {
            tmp |= VIBROMOTOR4_RAM;
            break;
        }
    }

    err_flag |= vibromotor4_write_byte( ctx, VIBROMOTOR4_LIB_SEL, tmp );

    return err_flag;
}

err_t vibromotor4_start_motor ( vibromotor4_t *ctx, uint8_t state )
{
     err_t err_flag;

    if ( state == VIBROMOTOR4_STOP )
    {
        err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_REG_GO, VIBROMOTOR4_STOP );
    }
    else if ( state == VIBROMOTOR4_GO )
    {
        err_flag = vibromotor4_write_byte( ctx, VIBROMOTOR4_REG_GO, VIBROMOTOR4_GO );
    }

    return err_flag;
}

err_t vibromotor4_set_ovdr_offset ( vibromotor4_t *ctx, uint8_t ovdr_offset )
{
    return vibromotor4_write_byte( ctx, VIBROMOTOR4_OVERDRIVE_OFFS, ovdr_offset );
}

err_t vibromotor4_set_sustain_offset_pos ( vibromotor4_t *ctx, uint8_t sustain_offset_pos )
{
    return vibromotor4_write_byte( ctx, VIBROMOTOR4_SUSTAIN_P_OFFS, sustain_offset_pos );
}

err_t vibromotor4_set_sustain_offset_neg ( vibromotor4_t *ctx, uint8_t sustain_offset_neg )
{
    return vibromotor4_write_byte( ctx, VIBROMOTOR4_SUSTAIN_N_OFFS, sustain_offset_neg );
}

err_t vibromotor4_set_brake_time_offset ( vibromotor4_t *ctx, uint8_t brake_time_offset )
{
    return vibromotor4_write_byte( ctx, VIBROMOTOR4_BRAKE_OFF, brake_time_offset );
}

err_t vibromotor4_set_rated_volt ( vibromotor4_t *ctx, uint8_t rated_volt )
{
    return vibromotor4_write_byte( ctx, VIBROMOTOR4_RATED_VOLT, rated_volt );
}

err_t vibromotor4_set_ovdrv_clamp_volt ( vibromotor4_t *ctx, uint8_t ovdrv_clamp_volt )
{
    return vibromotor4_write_byte( ctx, VIBROMOTOR4_OD_CLAMP_VOLT, ovdrv_clamp_volt );
}

err_t vibromotor4_get_calib_res_comp ( vibromotor4_t *ctx, uint8_t *calib_res_comp )
{
    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_CAL_COMP, calib_res_comp );

    *calib_res_comp += 1;
    *calib_res_comp /= 255;

    return err_flag;
}

err_t vibromotor4_get_supply_volt_val ( vibromotor4_t *ctx, float *supply_volt )
{
    uint8_t tmp;

    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_VBAT_MON, &tmp );

    *supply_volt = ( float ) tmp;
    *supply_volt *= 5.6;
    *supply_volt /= 255;

    return err_flag;
}

err_t vibromotor4_get_lra_resonance_period ( vibromotor4_t *ctx, float *lra_res )
{
    uint8_t tmp;

    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_LRA_RES_PERIOD, &tmp );

    *lra_res = ( float ) tmp;
    *lra_res *= 98.46;

    return err_flag;
}

err_t vibromotor4_set_lra_mode ( vibromotor4_t *ctx, uint8_t state )
{
    uint8_t tmp;

    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, &tmp );

    if ( state == 0 )
    {
        tmp |= VIBROMOTOR4_ERM_MODE;
    }
    else if ( state == 1 )
    {
        tmp |= VIBROMOTOR4_LRA_MODE;
    }

    err_flag |= vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );

    return err_flag;
}

err_t vibromotor4_set_brake_factor ( vibromotor4_t *ctx, uint8_t brk_fac )
{
    uint8_t tmp;

    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, &tmp );
    tmp &= 0x8F;

    switch ( brk_fac )
    {
        case 0:
        {
            tmp |= VIBROMOTOR4_FB_BRAKE_FAC_DIS;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 1:
        {
            tmp |= VIBROMOTOR4_FB_BRAKE_FAC_1X;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 2:
        {
            tmp |= VIBROMOTOR4_FB_BRAKE_FAC_2X;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 3:
        {
            tmp |=  VIBROMOTOR4_FB_BRAKE_FAC_3X;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 4:
        {
            tmp |= VIBROMOTOR4_FB_BRAKE_FAC_4X;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 6:
        {
            tmp |= VIBROMOTOR4_FB_BRAKE_FAC_6X;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 8:
        {
            tmp |= VIBROMOTOR4_FB_BRAKE_FAC_8X;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 16:
        {
            tmp |= VIBROMOTOR4_FB_BRAKE_FAC_16X;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        default:
        {
            tmp |= VIBROMOTOR4_FB_BRAKE_FAC_DIS;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
    }

    return err_flag;
}

err_t vibromotor4_set_loop_gain ( vibromotor4_t *ctx, uint8_t gain )
{
    uint8_t tmp;

    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, &tmp );

    switch ( gain )
    {
        case 0:
        {
            tmp |= VIBROMOTOR4_LOOP_RESP_SLOW;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 1:
        {
            tmp |= VIBROMOTOR4_LOOP_RESP_MEDIUM;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 2:
        {
            tmp |= VIBROMOTOR4_LOOP_RESP_FAST;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        case 3:
        {
            tmp |= VIBROMOTOR4_LOOP_RESP_V_FAST;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
        default:
        {
            tmp |= VIBROMOTOR4_LOOP_RESP_MEDIUM;
            vibromotor4_write_byte( ctx, VIBROMOTOR4_FEEDBACK_CTRL, tmp );
            break;
        }
    }

    return err_flag;
}

err_t vibromotor4_set_input ( vibromotor4_t *ctx, uint8_t state )
{
    uint8_t aux_reg_val;

    err_t err_flag = vibromotor4_read_byte( ctx, VIBROMOTOR4_CTRL3, &aux_reg_val );

    if ( state == 0 )
    {
        aux_reg_val |= VIBROMOTOR4_IN_MODE_ANALOG;
    }
    else if ( state == 1 )
    {
        aux_reg_val &= ~VIBROMOTOR4_IN_MODE_ANALOG;
    }

    err_flag |= vibromotor4_write_byte( ctx, VIBROMOTOR4_CTRL3, aux_reg_val );

    return err_flag;
}

err_t vibromotor4_enable_ac_coulping ( vibromotor4_t *ctx )
{
    return vibromotor4_write_byte( ctx, VIBROMOTOR4_CTRL1, VIBROMOTOR4_DRV_TIME_2P4M |
                                                           VIBROMOTOR4_AC_COUPLE     |
                                                           VIBROMOTOR4_STARTPPBOOST );
}

err_t vibromotor4_set_duty_cycle ( vibromotor4_t *ctx, float duty_cycle )
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t vibromotor4_pwm_stop ( vibromotor4_t *ctx )
{
    return pwm_stop( &ctx->pwm );
}

err_t vibromotor4_pwm_start ( vibromotor4_t *ctx )
{
    return pwm_start( &ctx->pwm );
}

static void dev_cfg_delay ( void )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
