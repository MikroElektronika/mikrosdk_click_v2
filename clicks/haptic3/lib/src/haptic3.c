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
 * @file haptic3.c
 * @brief HAPTIC 3 Click Driver.
 */

#include "haptic3.h"

void haptic3_cfg_setup ( haptic3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HAPTIC3_DEVICE_ADDRESS;
}

err_t haptic3_init ( haptic3_t *ctx, haptic3_cfg_t *cfg ) 
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

    digital_in_init( &ctx->irq, cfg->irq );

    return I2C_MASTER_SUCCESS;
}

err_t haptic3_default_cfg ( haptic3_t *ctx ) 
{
    err_t error_flag = HAPTIC3_OK;
    haptic3_disable_device ( ctx );
    Delay_100ms ( );
    haptic3_enable_device ( ctx );
    Delay_100ms ( );
    
    if ( HAPTIC3_ERROR == haptic3_check_communication ( ctx ) )
    {
        return HAPTIC3_ERROR;
    }
    
    error_flag |= haptic3_set_acceleration_mode ( ctx, HAPTIC3_TOP_CFG1_ACCEL_ENABLE );
    
    error_flag |= haptic3_set_actuator_type ( ctx, HAPTIC3_TOP_CFG1_ACT_TYPE_LRA );
    error_flag |= haptic3_set_actuator_abs_volt ( ctx, HAPTIC3_DEFAULT_ACTUATOR_ABS_VOLT );
    error_flag |= haptic3_set_actuator_nom_volt ( ctx, HAPTIC3_DEFAULT_ACTUATOR_NOM_VOLT );
    error_flag |= haptic3_set_actuator_imax ( ctx, HAPTIC3_DEFAULT_ACTUATOR_IMAX );
    error_flag |= haptic3_set_actuator_impedance ( ctx, HAPTIC3_DEFAULT_ACTUATOR_IMPEDANCE );
    error_flag |= haptic3_set_actuator_lra_freq ( ctx, HAPTIC3_DEFAULT_ACTUATOR_LRA_FREQ );
    
    error_flag |= haptic3_set_freq_track ( ctx, HAPTIC3_TOP_CFG1_FREQ_TRACK_DISABLE );
    error_flag |= haptic3_set_operation_mode ( ctx, HAPTIC3_TOP_CTL1_OP_MODE_DRO );
    Delay_1sec ( );
    
    return error_flag;
}

err_t haptic3_generic_write ( haptic3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len )
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t haptic3_generic_read ( haptic3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t haptic3_write_register ( haptic3_t *ctx, uint8_t reg, uint8_t data_in )
{
    return haptic3_generic_write( ctx, reg, &data_in, 1 );
}

err_t haptic3_read_register ( haptic3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return haptic3_generic_read( ctx, reg, data_out, 1 );
}

err_t haptic3_write_register_bits ( haptic3_t *ctx, uint8_t reg, uint8_t mask, uint8_t data_in )
{
    err_t error_flag = HAPTIC3_OK;
    uint8_t reg_data;
    error_flag |= haptic3_read_register ( ctx, reg, &reg_data );
    reg_data = ( reg_data & ~mask ) | data_in;
    error_flag |= haptic3_write_register( ctx, reg, reg_data );
    return error_flag;
}

err_t haptic3_check_communication ( haptic3_t *ctx )
{
    uint8_t chip_rev;
    if ( HAPTIC3_OK == haptic3_read_register ( ctx, HAPTIC3_REG_CHIP_REV, &chip_rev ) )
    {
        if ( HAPTIC3_CHIP_REV == chip_rev )
        {
            return HAPTIC3_OK;
        }
    }
    return HAPTIC3_ERROR;
}

void haptic3_enable_device ( haptic3_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void haptic3_disable_device ( haptic3_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t haptic3_get_int_pin ( haptic3_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

err_t haptic3_set_actuator_type ( haptic3_t *ctx, uint8_t type )
{
    if ( ( HAPTIC3_TOP_CFG1_ACT_TYPE_LRA != type ) && ( HAPTIC3_TOP_CFG1_ACT_TYPE_ERM != type ) )
    {
        return HAPTIC3_ERROR;
    }
    return haptic3_write_register_bits ( ctx, HAPTIC3_REG_TOP_CFG1, HAPTIC3_TOP_CFG1_ACT_TYPE_MASK, type );
}

err_t haptic3_set_actuator_abs_volt ( haptic3_t *ctx, float abs_volt )
{
    if ( ( abs_volt < HAPTIC3_ACTUATOR_VOLTAGE_MIN ) || ( abs_volt > HAPTIC3_ACTUATOR_VOLTAGE_MAX ) )
    {
        return HAPTIC3_ERROR;
    }
    return haptic3_write_register ( ctx, HAPTIC3_REG_ACTUATOR2, 
                                    ( uint8_t ) ( abs_volt / HAPTIC3_ACTUATOR_VOLTAGE_RESOLUTION ) );
}

err_t haptic3_set_actuator_nom_volt ( haptic3_t *ctx, float nom_volt )
{
    if ( ( nom_volt < HAPTIC3_ACTUATOR_VOLTAGE_MIN ) || ( nom_volt > HAPTIC3_ACTUATOR_VOLTAGE_MAX ) )
    {
        return HAPTIC3_ERROR;
    }
    return haptic3_write_register ( ctx, HAPTIC3_REG_ACTUATOR1, 
                                    ( uint8_t ) ( nom_volt / HAPTIC3_ACTUATOR_VOLTAGE_RESOLUTION ) );
}

err_t haptic3_set_actuator_imax ( haptic3_t *ctx, float max_curr )
{
    if ( ( max_curr < HAPTIC3_ACTUATOR_IMAX_MIN ) || ( max_curr > HAPTIC3_ACTUATOR_IMAX_MAX ) )
    {
        return HAPTIC3_ERROR;
    }
    return haptic3_write_register ( ctx, HAPTIC3_REG_ACTUATOR3, 
                                    ( uint8_t ) ( ( max_curr - HAPTIC3_ACTUATOR_IMAX_MIN ) / 
                                                    HAPTIC3_ACTUATOR_IMAX_DIVIDER ) & HAPTIC3_ACTUATOR_IMAX_RESOLUTION );
}

err_t haptic3_set_actuator_impedance ( haptic3_t *ctx, float impedance )
{
    if ( ( impedance < HAPTIC3_ACTUATOR_IMPEDANCE_MIN ) || ( impedance > HAPTIC3_ACTUATOR_IMPEDANCE_MAX ) )
    {
        return HAPTIC3_ERROR;
    }
    err_t error_flag = HAPTIC3_OK;
    uint8_t impedance_msb, impedance_lsb, max_curr; 
    uint16_t v2i_factor;
    error_flag |= haptic3_read_register ( ctx, HAPTIC3_REG_ACTUATOR3, &max_curr );
    v2i_factor = ( uint16_t ) ( ( impedance * ( ( max_curr & HAPTIC3_ACTUATOR_IMAX_RESOLUTION ) + 
                                                  HAPTIC3_ACTUATOR_IMPEDANCE_MIN ) ) / HAPTIC3_ACTUATOR_V2I_FACTOR_DIVIDER );
    impedance_msb = ( uint8_t ) ( ( v2i_factor >> 8 ) & 0xFF );
    impedance_lsb = ( uint8_t ) ( v2i_factor & 0xFF );
    error_flag |= haptic3_write_register ( ctx, HAPTIC3_REG_CALIB_V2I_H, impedance_msb );
    error_flag |= haptic3_write_register ( ctx, HAPTIC3_REG_CALIB_V2I_L, impedance_lsb );
    return error_flag;
}

err_t haptic3_set_actuator_lra_freq ( haptic3_t *ctx, float frequency )
{
    if ( ( frequency < HAPTIC3_ACTUATOR_LRA_FREQ_MIN ) || ( frequency > HAPTIC3_ACTUATOR_LRA_FREQ_MAX ) )
    {
        return HAPTIC3_ERROR;
    }
    err_t error_flag = HAPTIC3_OK;
    uint8_t frequency_msb, frequency_lsb; 
    uint16_t lra_period;
    lra_period = ( uint16_t ) ( 1.0 / ( frequency * HAPTIC3_ACTUATOR_LRA_FREQ_RESOLUTION ) );
    frequency_msb = ( uint8_t ) ( ( lra_period >> 7 ) & 0xFF );
    frequency_lsb = ( uint8_t ) ( lra_period & 0x7F );
    error_flag |= haptic3_write_register ( ctx, HAPTIC3_REG_FRQ_LRA_PER_H, frequency_msb );
    error_flag |= haptic3_write_register ( ctx, HAPTIC3_REG_FRQ_LRA_PER_L, frequency_lsb );
    return error_flag;
}

err_t haptic3_set_operation_mode ( haptic3_t *ctx, uint8_t op_mode )
{
    if ( op_mode > HAPTIC3_TOP_CTL1_OP_MODE_ETWM )
    {
        return HAPTIC3_ERROR;
    }
    return haptic3_write_register_bits ( ctx, HAPTIC3_REG_TOP_CTL1, HAPTIC3_TOP_CTL1_OP_MODE_MASK, op_mode );
}

err_t haptic3_set_freq_track ( haptic3_t *ctx, uint8_t freq_track_en )
{
    if ( ( HAPTIC3_TOP_CFG1_FREQ_TRACK_DISABLE != freq_track_en ) && ( HAPTIC3_TOP_CFG1_FREQ_TRACK_ENABLE != freq_track_en ) )
    {
        return HAPTIC3_ERROR;
    }
    return haptic3_write_register_bits ( ctx, HAPTIC3_REG_TOP_CFG1, HAPTIC3_TOP_CFG1_FREQ_TRACK_MASK, freq_track_en );
}

err_t haptic3_set_acceleration_mode ( haptic3_t *ctx, uint8_t accel_en )
{
    if ( ( HAPTIC3_TOP_CFG1_ACCEL_DISABLE != accel_en ) && ( HAPTIC3_TOP_CFG1_ACCEL_ENABLE != accel_en ) )
    {
        return HAPTIC3_ERROR;
    }
    return haptic3_write_register_bits ( ctx, HAPTIC3_REG_TOP_CFG1, HAPTIC3_TOP_CFG1_ACCEL_MASK, accel_en );
}

err_t haptic3_set_vibration_level ( haptic3_t *ctx, float level )
{
    if ( ( level < HAPTIC3_VIBRATION_LEVEL_MIN ) || ( level > HAPTIC3_VIBRATION_LEVEL_MAX ) )
    {
        return HAPTIC3_ERROR;
    }
    err_t error_flag = HAPTIC3_OK;
    uint8_t accel_state;
    error_flag |= haptic3_read_register ( ctx, HAPTIC3_REG_TOP_CFG1, &accel_state );
    if ( HAPTIC3_TOP_CFG1_ACCEL_ENABLE == ( accel_state & HAPTIC3_TOP_CFG1_ACCEL_MASK ) )
    {
        if ( level < HAPTIC3_VIBRATION_LEVEL_MIN_ACC_EN )
        {
            level = HAPTIC3_VIBRATION_LEVEL_MIN_ACC_EN;
        }
    }
    float override_val = level / HAPTIC3_VIBRATION_LEVEL_RESOLUTION;
    if ( level > 0.0 )
    {
        override_val += HAPTIC3_ROUND_TO_NEAREST_INT;
    }
    else
    {
        override_val -= HAPTIC3_ROUND_TO_NEAREST_INT;
    }
    return haptic3_write_register ( ctx, HAPTIC3_REG_TOP_CTL2, ( int8_t ) override_val );
}

err_t haptic3_get_vibration_level ( haptic3_t *ctx, float *level )
{
    uint8_t override_val;
    if ( HAPTIC3_OK == haptic3_read_register ( ctx, HAPTIC3_REG_TOP_CTL2, &override_val ) )
    {
        *level = ( int8_t ) override_val * HAPTIC3_VIBRATION_LEVEL_RESOLUTION;
        return HAPTIC3_OK;
    }
    return HAPTIC3_ERROR;
}

// ------------------------------------------------------------------------- END
