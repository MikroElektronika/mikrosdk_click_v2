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
 * @file haptic4.c
 * @brief Haptic 4 Click Driver.
 */

#include "haptic4.h"

void haptic4_cfg_setup ( haptic4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->gp1   = HAL_PIN_NC;
    cfg->gp2 = HAL_PIN_NC;
    cfg->gp0 = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HAPTIC4_DEVICE_ADDRESS;
}

err_t haptic4_init ( haptic4_t *ctx, haptic4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->gp1, cfg->gp1 );
    digital_out_init( &ctx->gp2, cfg->gp2 );
    digital_out_init( &ctx->gp0, cfg->gp0 );

    digital_in_init( &ctx->irq, cfg->irq );

    return I2C_MASTER_SUCCESS;
}

err_t haptic4_default_cfg ( haptic4_t *ctx ) 
{
    err_t error_flag = HAPTIC4_OK;
    
    if ( HAPTIC4_ERROR == haptic4_check_communication ( ctx ) )
    {
        return HAPTIC4_ERROR;
    }
    
    error_flag |= haptic4_set_acceleration_mode ( ctx, HAPTIC4_TOP_CFG1_ACCEL_ENABLE );
    
    error_flag |= haptic4_set_actuator_type ( ctx, HAPTIC4_TOP_CFG1_ACT_TYPE_LRA );
    error_flag |= haptic4_set_actuator_abs_volt ( ctx, HAPTIC4_DEFAULT_ACTUATOR_ABS_VOLT );
    error_flag |= haptic4_set_actuator_nom_volt ( ctx, HAPTIC4_DEFAULT_ACTUATOR_NOM_VOLT );
    error_flag |= haptic4_set_actuator_imax ( ctx, HAPTIC4_DEFAULT_ACTUATOR_IMAX );
    error_flag |= haptic4_set_actuator_impedance ( ctx, HAPTIC4_DEFAULT_ACTUATOR_IMPEDANCE );
    error_flag |= haptic4_set_actuator_lra_freq ( ctx, HAPTIC4_DEFAULT_ACTUATOR_LRA_FREQ );
    
    error_flag |= haptic4_set_freq_track ( ctx, HAPTIC4_TOP_CFG1_FREQ_TRACK_DISABLE );
    error_flag |= haptic4_set_operation_mode ( ctx, HAPTIC4_TOP_CTL1_OP_MODE_DRO );
    Delay_1sec ( );

    return error_flag;
}

err_t haptic4_generic_write ( haptic4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t haptic4_generic_read ( haptic4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t haptic4_write_register ( haptic4_t *ctx, uint8_t reg, uint8_t data_in )
{
    return haptic4_generic_write( ctx, reg, &data_in, 1 );
}

err_t haptic4_read_register ( haptic4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return haptic4_generic_read( ctx, reg, data_out, 1 );
}

err_t haptic4_write_register_bits ( haptic4_t *ctx, uint8_t reg, uint8_t mask, uint8_t data_in )
{
    err_t error_flag = HAPTIC4_OK;
    uint8_t reg_data = 0;
    error_flag |= haptic4_read_register ( ctx, reg, &reg_data );
    reg_data = ( reg_data & ~mask ) | data_in;
    error_flag |= haptic4_write_register( ctx, reg, reg_data );
    return error_flag;
}

err_t haptic4_check_communication ( haptic4_t *ctx )
{
    uint8_t chip_rev = 0;
    if ( HAPTIC4_OK == haptic4_read_register ( ctx, HAPTIC4_REG_CHIP_REV, &chip_rev ) )
    {
        if ( HAPTIC4_CHIP_REV == chip_rev )
        {
            return HAPTIC4_OK;
        }
    }
    return HAPTIC4_ERROR;
}

void haptic4_set_gp0 ( haptic4_t *ctx, uint8_t pin_state )
{
    if ( HAPTIC4_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high ( &ctx->gp0 );
    }
    else
    {
        digital_out_low ( &ctx->gp0 );
    }
}

void haptic4_set_gp1 ( haptic4_t *ctx, uint8_t pin_state )
{
    if ( HAPTIC4_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high ( &ctx->gp1 );
    }
    else
    {
        digital_out_low ( &ctx->gp1 );
    }
}

void haptic4_set_gp2 ( haptic4_t *ctx, uint8_t pin_state )
{
    if ( HAPTIC4_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high ( &ctx->gp2 );
    }
    else
    {
        digital_out_low ( &ctx->gp2 );
    }
}

uint8_t haptic4_get_int_pin ( haptic4_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

err_t haptic4_set_actuator_type ( haptic4_t *ctx, uint8_t type )
{
    if ( ( HAPTIC4_TOP_CFG1_ACT_TYPE_LRA != type ) && ( HAPTIC4_TOP_CFG1_ACT_TYPE_ERM != type ) )
    {
        return HAPTIC4_ERROR;
    }
    return haptic4_write_register_bits ( ctx, HAPTIC4_REG_TOP_CFG1, HAPTIC4_TOP_CFG1_ACT_TYPE_MASK, type );
}

err_t haptic4_set_actuator_abs_volt ( haptic4_t *ctx, float abs_volt )
{
    if ( ( abs_volt < HAPTIC4_ACTUATOR_VOLTAGE_MIN ) || ( abs_volt > HAPTIC4_ACTUATOR_VOLTAGE_MAX ) )
    {
        return HAPTIC4_ERROR;
    }
    return haptic4_write_register ( ctx, HAPTIC4_REG_ACTUATOR2, 
                                    ( uint8_t ) ( abs_volt / HAPTIC4_ACTUATOR_VOLTAGE_RESOLUTION ) );
}

err_t haptic4_set_actuator_nom_volt ( haptic4_t *ctx, float nom_volt )
{
    if ( ( nom_volt < HAPTIC4_ACTUATOR_VOLTAGE_MIN ) || ( nom_volt > HAPTIC4_ACTUATOR_VOLTAGE_MAX ) )
    {
        return HAPTIC4_ERROR;
    }
    return haptic4_write_register ( ctx, HAPTIC4_REG_ACTUATOR1, 
                                    ( uint8_t ) ( nom_volt / HAPTIC4_ACTUATOR_VOLTAGE_RESOLUTION ) );
}

err_t haptic4_set_actuator_imax ( haptic4_t *ctx, float max_curr )
{
    if ( ( max_curr < HAPTIC4_ACTUATOR_IMAX_MIN ) || ( max_curr > HAPTIC4_ACTUATOR_IMAX_MAX ) )
    {
        return HAPTIC4_ERROR;
    }
    return haptic4_write_register ( ctx, HAPTIC4_REG_ACTUATOR3, 
                                    ( uint8_t ) ( ( max_curr - HAPTIC4_ACTUATOR_IMAX_MIN ) / 
                                                    HAPTIC4_ACTUATOR_IMAX_DIVIDER ) & HAPTIC4_ACTUATOR_IMAX_RESOLUTION );
}

err_t haptic4_set_actuator_impedance ( haptic4_t *ctx, float impedance )
{
    if ( ( impedance < HAPTIC4_ACTUATOR_IMPEDANCE_MIN ) || ( impedance > HAPTIC4_ACTUATOR_IMPEDANCE_MAX ) )
    {
        return HAPTIC4_ERROR;
    }
    err_t error_flag = HAPTIC4_OK;
    uint8_t impedance_msb = 0;
    uint8_t impedance_lsb = 0;
    uint8_t max_curr = 0; 
    uint16_t v2i_factor;
    error_flag |= haptic4_read_register ( ctx, HAPTIC4_REG_ACTUATOR3, &max_curr );
    v2i_factor = ( uint16_t ) ( ( impedance * ( ( max_curr & HAPTIC4_ACTUATOR_IMAX_RESOLUTION ) + 
                                                  HAPTIC4_ACTUATOR_IMPEDANCE_MIN ) ) / HAPTIC4_ACTUATOR_V2I_FACTOR_DIVIDER );
    impedance_msb = ( uint8_t ) ( ( v2i_factor >> 8 ) & 0xFF );
    impedance_lsb = ( uint8_t ) ( v2i_factor & 0xFF );
    error_flag |= haptic4_write_register ( ctx, HAPTIC4_REG_CALIB_V2I_H, impedance_msb );
    error_flag |= haptic4_write_register ( ctx, HAPTIC4_REG_CALIB_V2I_L, impedance_lsb );
    return error_flag;
}

err_t haptic4_set_actuator_lra_freq ( haptic4_t *ctx, float frequency )
{
    if ( ( frequency < HAPTIC4_ACTUATOR_LRA_FREQ_MIN ) || ( frequency > HAPTIC4_ACTUATOR_LRA_FREQ_MAX ) )
    {
        return HAPTIC4_ERROR;
    }
    err_t error_flag = HAPTIC4_OK;
    uint8_t frequency_msb, frequency_lsb; 
    uint16_t lra_period;
    lra_period = ( uint16_t ) ( 1.0 / ( frequency * HAPTIC4_ACTUATOR_LRA_FREQ_RESOLUTION ) );
    frequency_msb = ( uint8_t ) ( ( lra_period >> 7 ) & 0xFF );
    frequency_lsb = ( uint8_t ) ( lra_period & 0x7F );
    error_flag |= haptic4_write_register ( ctx, HAPTIC4_REG_FRQ_LRA_PER_H, frequency_msb );
    error_flag |= haptic4_write_register ( ctx, HAPTIC4_REG_FRQ_LRA_PER_L, frequency_lsb );
    return error_flag;
}

err_t haptic4_set_operation_mode ( haptic4_t *ctx, uint8_t op_mode )
{
    if ( op_mode > HAPTIC4_TOP_CTL1_OP_MODE_ETWM )
    {
        return HAPTIC4_ERROR;
    }
    return haptic4_write_register_bits ( ctx, HAPTIC4_REG_TOP_CTL1, HAPTIC4_TOP_CTL1_OP_MODE_MASK, op_mode );
}

err_t haptic4_set_freq_track ( haptic4_t *ctx, uint8_t freq_track_en )
{
    if ( ( HAPTIC4_TOP_CFG1_FREQ_TRACK_DISABLE != freq_track_en ) && ( HAPTIC4_TOP_CFG1_FREQ_TRACK_ENABLE != freq_track_en ) )
    {
        return HAPTIC4_ERROR;
    }
    return haptic4_write_register_bits ( ctx, HAPTIC4_REG_TOP_CFG1, HAPTIC4_TOP_CFG1_FREQ_TRACK_MASK, freq_track_en );
}

err_t haptic4_set_acceleration_mode ( haptic4_t *ctx, uint8_t accel_en )
{
    if ( ( HAPTIC4_TOP_CFG1_ACCEL_DISABLE != accel_en ) && ( HAPTIC4_TOP_CFG1_ACCEL_ENABLE != accel_en ) )
    {
        return HAPTIC4_ERROR;
    }
    return haptic4_write_register_bits ( ctx, HAPTIC4_REG_TOP_CFG1, HAPTIC4_TOP_CFG1_ACCEL_MASK, accel_en );
}

err_t haptic4_set_vibration_level ( haptic4_t *ctx, float level )
{
    if ( ( level < HAPTIC4_VIBRATION_LEVEL_MIN ) || ( level > HAPTIC4_VIBRATION_LEVEL_MAX ) )
    {
        return HAPTIC4_ERROR;
    }
    err_t error_flag = HAPTIC4_OK;
    uint8_t accel_state = 0;
    error_flag |= haptic4_read_register ( ctx, HAPTIC4_REG_TOP_CFG1, &accel_state );
    if ( HAPTIC4_TOP_CFG1_ACCEL_ENABLE == ( accel_state & HAPTIC4_TOP_CFG1_ACCEL_MASK ) )
    {
        if ( level < HAPTIC4_VIBRATION_LEVEL_MIN_ACC_EN )
        {
            level = HAPTIC4_VIBRATION_LEVEL_MIN_ACC_EN;
        }
    }
    float override_val = level / HAPTIC4_VIBRATION_LEVEL_RESOLUTION;
    if ( level > 0.0 )
    {
        override_val += HAPTIC4_ROUND_TO_NEAREST_INT;
    }
    else
    {
        override_val -= HAPTIC4_ROUND_TO_NEAREST_INT;
    }
    return haptic4_write_register ( ctx, HAPTIC4_REG_TOP_CTL2, ( int8_t ) override_val );
}

err_t haptic4_get_vibration_level ( haptic4_t *ctx, float *level )
{
    uint8_t override_val = 0;
    if ( HAPTIC4_OK == haptic4_read_register ( ctx, HAPTIC4_REG_TOP_CTL2, &override_val ) )
    {
        *level = ( int8_t ) override_val * HAPTIC4_VIBRATION_LEVEL_RESOLUTION;
        return HAPTIC4_OK;
    }
    return HAPTIC4_ERROR;
}

// ------------------------------------------------------------------------- END
