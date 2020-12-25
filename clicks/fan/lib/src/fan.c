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
 * \file fan.c
 *
 */

#include "fan.h"


#define FAN_MAX_TX_BUF_SIZE  256
#define DUMMY                0
#define FAN_DEF_CFG          0x80

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void
fan_cfg_setup ( fan_cfg_t *cfg )
{
    cfg->scl     = HAL_PIN_NC;
    cfg->sda     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = FAN_DEV_ADDR;

    cfg->fan_setup_cfg.poles_cfg     = FAN_EDGE_2_POLE;
    cfg->fan_setup_cfg.edges_cfg     = 2;
    cfg->fan_setup_cfg.range_cfg     = FAN_RPM_MIN_1000;
    cfg->fan_setup_cfg.mul_cfg       = 0;
    cfg->fan_setup_cfg.frequency_cfg = 32768;
    cfg->fan_setup_cfg.mode_cfg      = 0;
    cfg->fan_setup_cfg.lock_cfg      = 0;
}

err_t
fan_default_cfg ( fan_t *ctx )
{
    return fan_write_byte( ctx, FAN_SETTING, FAN_DEF_CFG );
}

err_t
fan_init ( fan_t *ctx, fan_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    ctx->fan_setup.number_of_poles = cfg->fan_setup_cfg.poles_cfg;
    ctx->fan_setup.number_of_edges = cfg->fan_setup_cfg.edges_cfg;
    ctx->fan_setup.range           = cfg->fan_setup_cfg.range_cfg;
    ctx->fan_setup.mul             = cfg->fan_setup_cfg.mul_cfg;
    ctx->fan_setup.frequency       = cfg->fan_setup_cfg.frequency_cfg;
    ctx->fan_setup.fsc_mode        = cfg->fan_setup_cfg.mode_cfg;
    ctx->fan_setup.software_lock   = cfg->fan_setup_cfg.lock_cfg;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    if ( digital_in_init( &ctx->int_pin, cfg->int_pin ) == DIGITAL_IN_UNSUPPORTED_PIN )
    {
        return DIGITAL_IN_UNSUPPORTED_PIN;
    }

    return I2C_MASTER_SUCCESS;
}

err_t
fan_generic_write ( fan_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ FAN_MAX_TX_BUF_SIZE ] = { DUMMY };
    uint8_t cnt;

    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = *data_in;
        data_in++;
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

err_t
fan_generic_read ( fan_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t
fan_write_byte ( fan_t *ctx, uint8_t reg, uint8_t data_in )
{
    return fan_generic_write( ctx, reg, &data_in, 1 );
}

err_t
fan_read_byte ( fan_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return fan_generic_read( ctx, reg, data_out, 1 );
}

err_t
fan_lock_registers ( fan_t *ctx, uint8_t lock )
{
    uint8_t tmp;

    if ( lock == 1 )
    {
        tmp = 0x01;
    }
    else
    {
        tmp = 0x00;
    }

    ctx->fan_setup.software_lock = lock;

    return fan_write_byte( ctx, FAN_SOFTWARE_LOCK, tmp );
}

err_t
fan_device_info ( fan_t *ctx, uint8_t *info )
{
    if ( fan_read_byte( ctx, FAN_PRODUCT_ID, info ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }
    info++;
    if ( fan_read_byte( ctx, FAN_MANUFACTUERE_ID, info ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }
    info++;
    if ( fan_read_byte( ctx, FAN_REVISION, info ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t
fan_set_valid_tach ( fan_t *ctx, uint16_t tach )
{
    double tmp;
    uint8_t set_tach;

    if ( ctx->fan_setup.software_lock )
    {
        return I2C_MASTER_ERROR;
    }
    if ( tach > 16000 || tach < 480 )
    {
        return I2C_MASTER_ERROR;
    }

    tmp = (float)( 1 / ctx->fan_setup.number_of_poles );
    tmp *= ctx->fan_setup.number_of_edges - 1;
    tmp /= (float)( tach  / ctx->fan_setup.mul );
    tach = tmp * ctx->fan_setup.frequency * SEC_MIN;
    set_tach = tach >> 5;

    return fan_write_byte( ctx, FAN_VALID_TACH, set_tach );
}

err_t
fan_get_valid_tach ( fan_t *ctx, uint16_t *data_out )
{
    uint8_t tach = DUMMY;

    if ( fan_read_byte( ctx, FAN_VALID_TACH, &tach ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    *data_out = tach;
    *data_out <<= 8;

    return I2C_MASTER_SUCCESS;
}

err_t
fan_get_driveband_fail ( fan_t *ctx, uint16_t *data_out )
{
    uint8_t read_data[ 2 ] = { DUMMY };

    if ( fan_read_byte( ctx, FAN_FAIL_LOW, &read_data[ 0 ] ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }
    if ( fan_read_byte( ctx, FAN_FAIL_HIGH, &read_data[ 1 ] ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    *data_out = read_data[ 1 ];
    *data_out <<= 8;
    *data_out |= read_data[ 0 ];
    *data_out >>= 3;

    return I2C_MASTER_SUCCESS;
}

err_t
fan_set_target_tach ( fan_t *ctx, uint16_t tach )
{
    double tmp;
    uint8_t write_data[ 2 ];

    if ( tach > 16000 || tach < 480 )
    {
        return I2C_MASTER_ERROR;
    }

    tmp = (float)( 1 / ctx->fan_setup.number_of_poles );
    tmp *= ctx->fan_setup.number_of_edges - 1;
    tmp /= (float)( tach / ctx->fan_setup.mul );
    tach = tmp * ctx->fan_setup.frequency * SEC_MIN;

    write_data[ 0 ] = (uint8_t)( tach & 0xFF ) << 3;
    write_data[ 1 ] = (uint8_t)( tach >> 5 );

    if ( fan_write_byte( ctx, FAN_TACH_TARGET_LOW, write_data[ 0 ] ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    return fan_write_byte( ctx, FAN_TACH_TARGET_HIGH, write_data[ 1 ] );
}

err_t
fan_get_tach ( fan_t *ctx, uint16_t *data_out )
{
    uint8_t read_data[ 2 ] = { DUMMY };

    if ( fan_read_byte( ctx, FAN_TACH_READING_HIGH, &read_data[ 0 ] ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }
    if ( fan_read_byte( ctx, FAN_TACH_READING_LOW, &read_data[ 1 ] ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    *data_out = read_data[ 0 ];
    *data_out <<= 8;
    *data_out |= read_data[ 1 ];
    *data_out >>= 3;

    if ( *data_out != 0 )
    {
        *data_out = ( 3932160 * 2 ) / *data_out;
    }

    return I2C_MASTER_SUCCESS;
}

err_t
fan_enable_fsc ( fan_t *ctx, uint8_t fsc )
{
    uint8_t tmp_data = DUMMY;

    if ( fan_read_byte( ctx, FAN_CONFIG1, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    if ( fsc == 1 )
    {
        tmp_data |= EN_ALGO;
        ctx->fan_setup.fsc_mode = 1;
    }
    else
    {
        tmp_data &= ~ EN_ALGO;
        ctx->fan_setup.fsc_mode = 0;
    }

    return fan_write_byte( ctx, FAN_CONFIG1, tmp_data );
}

err_t
fan_set_range ( fan_t *ctx, uint8_t range )
{
    uint8_t tmp_data = DUMMY;

    if ( range > FAN_RPM_MIN_4000 )
    {
        return I2C_MASTER_ERROR;
    }

    ctx->fan_setup.range = range;
    fan_update_multiplier( ctx );

    if ( fan_read_byte( ctx, FAN_CONFIG1, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    tmp_data &= ~ RANGE;
    tmp_data |= (uint8_t)range << RANGE_BIT;

    return fan_write_byte( ctx, FAN_CONFIG1, tmp_data );
}

err_t
fan_set_edges ( fan_t *ctx, uint8_t edges )
{
    uint8_t tmp_data = DUMMY;

    if ( edges > FAN_EDGE_4_POLE )
    {
        return I2C_MASTER_ERROR;
    }

    ctx->fan_setup.number_of_edges = 3 + ( edges * 2 );
    ctx->fan_setup.number_of_poles = edges + 1;

    if ( fan_read_byte( ctx, FAN_CONFIG1, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    tmp_data &= ~ EDGES;
    tmp_data |= (uint8_t)edges << EDGES_BIT;

    return fan_write_byte( ctx, FAN_CONFIG1, tmp_data );
}

err_t
fan_set_update ( fan_t *ctx, uint8_t update )
{
    uint8_t tmp_data = DUMMY;

    if ( update > FAN_UPDATE_1600MS )
    {
        return I2C_MASTER_ERROR;
    }

    if ( fan_read_byte( ctx, FAN_CONFIG1, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    tmp_data &= ~ UPDATE;
    tmp_data |= (uint8_t)update << UPDATE_BIT;

    return fan_write_byte( ctx, FAN_CONFIG1, tmp_data );
}

err_t
fan_enable_ramp ( fan_t *ctx, uint8_t ramp_control )
{
    uint8_t tmp_data = DUMMY;

    if ( fan_read_byte( ctx, FAN_CONFIG2, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    if ( ramp_control == 1 )
    {
        tmp_data |= EN_RAMP;
    }
    else
    {
        tmp_data &= ~ EN_RAMP;
    }

    return fan_write_byte( ctx, FAN_CONFIG2, tmp_data );
}

err_t
fan_enable_glitch ( fan_t *ctx, uint8_t glitch )
{
    uint8_t tmp_data = DUMMY;

    if ( fan_read_byte( ctx, FAN_CONFIG2, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    if ( glitch == 1 )
    {
        tmp_data |= GLITCH_EN;
    }
    else
    {
        tmp_data &= ~ GLITCH_EN;
    }

    return fan_write_byte( ctx, FAN_CONFIG2, tmp_data );
}

err_t
fan_set_derivative ( fan_t *ctx, uint8_t derivative )
{
    uint8_t tmp_data = DUMMY;

    if ( derivative > FAN_DERIVATIVE_BOTH )
    {
        return I2C_MASTER_ERROR;
    }

    if ( fan_read_byte( ctx, FAN_CONFIG2, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    tmp_data &= ~ DER_OPT;
    tmp_data |= (uint8_t)( derivative << DER_OPT_BIT );

    return fan_write_byte( ctx, FAN_CONFIG2, tmp_data );
}

err_t
fan_set_error_range ( fan_t *ctx, uint8_t error )
{
    uint8_t tmp_data = DUMMY;

    if ( error > FAN_RPM_200 )
    {
        return I2C_MASTER_ERROR;
    }

    if ( fan_read_byte( ctx, FAN_CONFIG2, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    tmp_data &= ~ ERR_RNG;
    tmp_data |= (uint8_t)( error << ERR_RNG_BIT );

    return fan_write_byte( ctx, FAN_CONFIG2, tmp_data );
}

err_t
fan_set_gaind ( fan_t *ctx, uint8_t gain )
{
    uint8_t tmp_data = DUMMY;

    if ( gain > FAN_GAIN_8X )
    {
        return I2C_MASTER_ERROR;
    }

    if ( fan_read_byte( ctx, FAN_GAIN, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    tmp_data &= ~ GAIND;
    tmp_data |= (uint8_t)( gain << GAIND_BIT );

    return fan_write_byte( ctx, FAN_GAIN, tmp_data );
}

err_t
fan_set_drivefail ( fan_t *ctx, uint8_t count )
{
    uint8_t tmp_data = DUMMY;

    if ( count > FAN_DRIVE_CNT_64 )
    {
        return I2C_MASTER_ERROR;
    }
    if ( ctx->fan_setup.software_lock )
    {
        return I2C_MASTER_ERROR;
    }

    if ( fan_read_byte( ctx, FAN_SPINUP, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    tmp_data &= ~ DRIVE_FAIL_CNT;
    tmp_data |= (uint8_t)( count << DRIVE_FAIL_CNT_BIT );

    return fan_write_byte( ctx, FAN_SPINUP, tmp_data );
}

err_t
fan_enable_no_kick ( fan_t *ctx, uint8_t no_kick )
{
    uint8_t tmp_data = DUMMY;

    if ( ctx->fan_setup.software_lock )
    {
        return I2C_MASTER_ERROR;
    }

    if ( fan_read_byte( ctx, FAN_SPINUP, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    if ( no_kick == 1 )
    {
        tmp_data |= NOKICK;
    }
    else
    {
        tmp_data &= ~ NOKICK;
    }

    return fan_write_byte( ctx, FAN_SPINUP, tmp_data );
}

err_t
fan_set_spin_level ( fan_t *ctx, uint8_t spin )
{
    uint8_t tmp_data = DUMMY;

    if ( spin > FAN_SPINUP_65PERCENT )
    {
        return I2C_MASTER_ERROR;
    }
    if ( ctx->fan_setup.software_lock )
    {
        return I2C_MASTER_ERROR;
    }

    if ( fan_read_byte( ctx, FAN_SPINUP, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    tmp_data &= ~ SPIN_LVL;
    tmp_data |= (uint8_t)( spin << SPIN_LVL_BIT );

    return fan_write_byte( ctx, FAN_SPINUP, tmp_data );
}

err_t
fan_set_spin_time ( fan_t *ctx, uint8_t time )
{
    uint8_t tmp_data = DUMMY;

    if ( time > FAN_SPINUP_2S )
    {
        return I2C_MASTER_ERROR;
    }
    if ( ctx->fan_setup.software_lock )
    {
        return I2C_MASTER_ERROR;
    }

    if ( fan_read_byte( ctx, FAN_SPINUP, &tmp_data ) == I2C_MASTER_ERROR )
    {
        return I2C_MASTER_ERROR;
    }

    tmp_data &= ~ SPINUP_TIME;
    tmp_data |= (uint8_t)( time << SPINUP_TIME_BIT );

    return fan_write_byte( ctx, FAN_SPINUP, tmp_data );
}

err_t
fan_set_max_step ( fan_t *ctx, uint8_t step )
{
    if ( ctx->fan_setup.software_lock )
    {
        return I2C_MASTER_ERROR;
    }
    if ( step > 0x3F )
    {
        return I2C_MASTER_ERROR;
    }

    return fan_write_byte( ctx, FAN_MAX_STEP, step );
}

err_t
fan_set_min_drive ( fan_t *ctx, double min_drive )
{
    uint8_t set_data;

    set_data = min_drive / 100 * 255;

    return fan_write_byte( ctx, FAN_MIN_DRIVE, set_data );
}

void
fan_update_multiplier ( fan_t *ctx )
{
    switch ( ctx->fan_setup.range )
    {
        case FAN_RPM_MIN_500 :
        {
            ctx->fan_setup.mul = 1;
        break;
        }
        case FAN_RPM_MIN_1000 :
        {
            ctx->fan_setup.mul = 2;
        break;
        }
        case FAN_RPM_MIN_2000 :
        {
            ctx->fan_setup.mul = 4;
        break;
        }
        case FAN_RPM_MIN_4000 :
        {
            ctx->fan_setup.mul = 8;
        break;
        }
        default :
        {
        break;
        }
    }
}

void
fan_set_clock ( fan_t *ctx, double freq )
{
    ctx->fan_setup.frequency = freq;
}

err_t
fan_device_cfg ( fan_t *ctx, uint8_t cfg )
{
    return fan_write_byte( ctx, FAN_CONFIGURATION, cfg );
}

err_t
fan_get_status ( fan_t *ctx, uint8_t *data_out )
{
    return fan_read_byte( ctx, FAN_STATUS, data_out );
}

err_t
fan_get_stall_status ( fan_t *ctx, uint8_t *data_out )
{
    return fan_read_byte( ctx, FAN_STALL_STATUS, data_out );
}

err_t
fan_get_spin_status ( fan_t *ctx, uint8_t *data_out )
{
    return fan_read_byte( ctx, FAN_SPIN_STATUS, data_out );
}

err_t
fan_get_drive_fail ( fan_t *ctx, uint8_t *data_out )
{
    return fan_read_byte( ctx, FAN_DRIVE_FAIL_STATUS, data_out );
}

err_t
fan_interrupts ( fan_t *ctx, uint8_t enable )
{
    return fan_write_byte( ctx, FAN_INTERRUPT_ENABLE, enable );
}

err_t
fan_pwm_base ( fan_t *ctx, uint8_t freq )
{
    return fan_write_byte( ctx, FAN_PWM_BASE_FREQ, freq );
}

err_t
fan_setting ( fan_t *ctx, double percentage )
{
    uint8_t tmp;

    if ( percentage > 100 )
    {
        percentage = 100;
    }
    if ( percentage < 0 )
    {
        percentage = 0;
    }

    tmp = percentage / 100 * 255;

    if ( ctx->fan_setup.fsc_mode )
    {
        return I2C_MASTER_ERROR;
    }

    return fan_write_byte( ctx, FAN_SETTING, tmp );
}

uint8_t
fan_read_int_pin ( fan_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
