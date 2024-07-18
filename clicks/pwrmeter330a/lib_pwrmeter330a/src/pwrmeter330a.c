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
 * @file pwrmeter330a.c
 * @brief PWR Meter 3 30A Click Driver.
 */

#include "pwrmeter330a.h"

void pwrmeter330a_cfg_setup ( pwrmeter330a_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dio1 = HAL_PIN_NC;
    cfg->dio0 = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PWRMETER330A_DEVICE_ADDRESS_0;
}

err_t pwrmeter330a_init ( pwrmeter330a_t *ctx, pwrmeter330a_cfg_t *cfg ) 
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
    
    digital_out_t dio0, dio1;
    digital_out_init( &dio0, cfg->dio0 );
    digital_out_init( &dio1, cfg->dio1 );
    
    switch ( ctx->slave_address )
    {
        case PWRMETER330A_DEVICE_ADDRESS_0:
        {
            digital_out_low ( &dio0 );
            digital_out_low ( &dio1 );
            break;
        }
        case PWRMETER330A_DEVICE_ADDRESS_1:
        {
            digital_out_high ( &dio0 );
            digital_out_low ( &dio1 );
            break;
        }
        case PWRMETER330A_DEVICE_ADDRESS_2:
        {
            digital_out_low ( &dio0 );
            digital_out_high ( &dio1 );
            break;
        }
        case PWRMETER330A_DEVICE_ADDRESS_3:
        {
            digital_out_high ( &dio0 );
            digital_out_high ( &dio1 );
            break;
        }
        default:
        {
            return I2C_MASTER_ERROR;
        }
    }
    
    pwrmeter330a_disable_device ( ctx );
    Delay_100ms ( );
    pwrmeter330a_enable_device ( ctx );
    Delay_100ms ( );
    
    digital_in_init( &ctx->dio1, cfg->dio1 );
    digital_in_init( &ctx->dio0, cfg->dio0 );

    return I2C_MASTER_SUCCESS;
}

err_t pwrmeter330a_default_cfg ( pwrmeter330a_t *ctx ) 
{
    err_t error_flag = PWRMETER330A_OK;
    error_flag |= pwrmeter330a_allow_write_access ( ctx );
    error_flag |= pwrmeter330a_set_dio0_sel ( ctx, PWRMETER330A_DIO_0_SEL_OV );
    error_flag |= pwrmeter330a_set_dio1_sel ( ctx, PWRMETER330A_DIO_1_SEL_UV );
    error_flag |= pwrmeter330a_set_ovrms_thold ( ctx, PWRMETER330A_OVERVREG_3 ); // set overvoltage threshold to ~28V
    error_flag |= pwrmeter330a_set_uvrms_thold ( ctx, PWRMETER330A_UNDERVREG_1 ); // set undervoltage threshold to ~9.3V
    error_flag |= pwrmeter330a_set_bypass_n_state ( ctx, PWRMETER330A_BYPASS_N_ENABLE );
    error_flag |= pwrmeter330a_set_num_samples ( ctx, PWRMETER330A_MAX_NUM_SAMPLES );
    error_flag |= pwrmeter330a_deny_write_access ( ctx );
    return error_flag;
}

err_t pwrmeter330a_write_register ( pwrmeter330a_t *ctx, uint8_t reg, uint32_t data_in )
{
    if ( ( ( reg < PWRMETER330A_REG_EEPROM_0B ) || ( reg > PWRMETER330A_REG_EEPROM_0F ) ) && 
         ( ( reg < PWRMETER330A_REG_SHADOW_1B ) || ( reg > PWRMETER330A_REG_SHADOW_1F ) ) && 
         ( ( reg < PWRMETER330A_REG_VOLATILE_20 ) || ( reg > PWRMETER330A_REG_VOLATILE_30 ) ) )
    {
        return PWRMETER330A_ERROR;
    }
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 5 );
}

err_t pwrmeter330a_read_register ( pwrmeter330a_t *ctx, uint8_t reg, uint32_t *data_out )
{
    if ( ( ( reg < PWRMETER330A_REG_EEPROM_0B ) || ( reg > PWRMETER330A_REG_EEPROM_0F ) ) && 
         ( ( reg < PWRMETER330A_REG_SHADOW_1B ) || ( reg > PWRMETER330A_REG_SHADOW_1F ) ) && 
         ( ( reg < PWRMETER330A_REG_VOLATILE_20 ) || ( reg > PWRMETER330A_REG_VOLATILE_30 ) ) )
    {
        return PWRMETER330A_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    if ( I2C_MASTER_ERROR == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 4 ) )
    {
        return PWRMETER330A_ERROR;
    }
    *data_out = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
                ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    return PWRMETER330A_OK;
}

uint8_t pwrmeter330a_get_dio0_pin ( pwrmeter330a_t *ctx )
{
    return digital_in_read ( &ctx->dio0 );
}

uint8_t pwrmeter330a_get_dio1_pin ( pwrmeter330a_t *ctx )
{
    return digital_in_read ( &ctx->dio1 );
}

void pwrmeter330a_enable_device ( pwrmeter330a_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void pwrmeter330a_disable_device ( pwrmeter330a_t *ctx )
{
    digital_out_high ( &ctx->en );
}

err_t pwrmeter330a_allow_write_access ( pwrmeter330a_t *ctx )
{
    return pwrmeter330a_write_register ( ctx, PWRMETER330A_REG_VOLATILE_2F, PWRMETER330A_CUST_ACCESS_CODE );
}

err_t pwrmeter330a_deny_write_access ( pwrmeter330a_t *ctx )
{
    return pwrmeter330a_write_register ( ctx, PWRMETER330A_REG_VOLATILE_2F, PWRMETER330A_CUST_ACCESS_CODE_CLEAR );
}

err_t pwrmeter330a_set_bypass_n_state ( pwrmeter330a_t *ctx, uint8_t state )
{
    if ( state > PWRMETER330A_BYPASS_N_ENABLE )
    {
        return PWRMETER330A_ERROR;
    }
    uint32_t reg_data;
    err_t error_flag = pwrmeter330a_read_register ( ctx, PWRMETER330A_REG_SHADOW_1F, &reg_data );
    if ( ( PWRMETER330A_OK == error_flag ) &&
         ( ( ( reg_data & PWRMETER330A_BYPASS_N_EN_MASK ) >> 24 ) != state ) )
    {
        reg_data &= ~PWRMETER330A_BYPASS_N_EN_MASK;
        reg_data |= ( ( uint32_t ) state << 24 ) & PWRMETER330A_BYPASS_N_EN_MASK;
        error_flag = pwrmeter330a_write_register ( ctx, PWRMETER330A_REG_SHADOW_1F, reg_data );
    }
    ctx->bypass_n_en = state;
    return error_flag;
}

err_t pwrmeter330a_set_num_samples ( pwrmeter330a_t *ctx, uint16_t num_samples )
{
    if ( num_samples > PWRMETER330A_MAX_NUM_SAMPLES )
    {
        return PWRMETER330A_ERROR;
    }
    uint32_t reg_data;
    err_t error_flag = pwrmeter330a_read_register ( ctx, PWRMETER330A_REG_SHADOW_1F, &reg_data );
    if ( ( PWRMETER330A_OK == error_flag ) &&
         ( ( ( reg_data & PWRMETER330A_N_MASK ) >> 14 ) != num_samples ) )
    {
        reg_data &= ~PWRMETER330A_N_MASK;
        reg_data |= ( ( uint32_t ) num_samples << 14 ) & PWRMETER330A_N_MASK;
        error_flag = pwrmeter330a_write_register ( ctx, PWRMETER330A_REG_SHADOW_1F, reg_data );
    }
    return error_flag;
}

err_t pwrmeter330a_set_dio0_sel ( pwrmeter330a_t *ctx, uint8_t dio_sel )
{
    if ( dio_sel > PWRMETER330A_DIO_0_SEL_OV_UV )
    {
        return PWRMETER330A_ERROR;
    }
    uint32_t reg_data;
    err_t error_flag = pwrmeter330a_read_register ( ctx, PWRMETER330A_REG_SHADOW_1F, &reg_data );
    if ( ( PWRMETER330A_OK == error_flag ) &&
         ( ( ( reg_data & PWRMETER330A_DIO_0_SEL_MASK ) >> 10 ) != dio_sel ) )
    {
        reg_data &= ~PWRMETER330A_DIO_0_SEL_MASK;
        reg_data |= ( ( uint32_t ) dio_sel << 10 ) & PWRMETER330A_DIO_0_SEL_MASK;
        error_flag = pwrmeter330a_write_register ( ctx, PWRMETER330A_REG_SHADOW_1F, reg_data );
    }
    return error_flag;
}

err_t pwrmeter330a_set_dio1_sel ( pwrmeter330a_t *ctx, uint8_t dio_sel )
{
    if ( dio_sel > PWRMETER330A_DIO_1_SEL_OV_UV_OCF )
    {
        return PWRMETER330A_ERROR;
    }
    uint32_t reg_data;
    err_t error_flag = pwrmeter330a_read_register ( ctx, PWRMETER330A_REG_SHADOW_1F, &reg_data );
    if ( ( PWRMETER330A_OK == error_flag ) &&
         ( ( ( reg_data & PWRMETER330A_DIO_1_SEL_MASK ) >> 12 ) != dio_sel ) )
    {
        reg_data &= ~PWRMETER330A_DIO_1_SEL_MASK;
        reg_data |= ( ( uint32_t ) dio_sel << 12 ) & PWRMETER330A_DIO_1_SEL_MASK;
        error_flag = pwrmeter330a_write_register ( ctx, PWRMETER330A_REG_SHADOW_1F, reg_data );
    }
    return error_flag;
}

err_t pwrmeter330a_set_ovrms_thold ( pwrmeter330a_t *ctx, uint8_t ovrms )
{
    if ( ovrms > PWRMETER330A_OVERVREG_MAX )
    {
        return PWRMETER330A_ERROR;
    }
    uint32_t reg_data;
    err_t error_flag = pwrmeter330a_read_register ( ctx, PWRMETER330A_REG_SHADOW_1E, &reg_data );
    if ( ( PWRMETER330A_OK == error_flag ) &&
         ( ( ( reg_data & PWRMETER330A_OVERVREG_MASK ) >> 8 ) != ovrms ) )
    {
        reg_data &= ~PWRMETER330A_OVERVREG_MASK;
        reg_data |= ( ( uint32_t ) ovrms << 8 ) & PWRMETER330A_OVERVREG_MASK;
        error_flag = pwrmeter330a_write_register ( ctx, PWRMETER330A_REG_SHADOW_1E, reg_data );
    }
    return error_flag;
}

err_t pwrmeter330a_set_uvrms_thold ( pwrmeter330a_t *ctx, uint8_t uvrms )
{
    if ( uvrms > PWRMETER330A_UNDERVREG_MAX )
    {
        return PWRMETER330A_ERROR;
    }
    uint32_t reg_data;
    err_t error_flag = pwrmeter330a_read_register ( ctx, PWRMETER330A_REG_SHADOW_1E, &reg_data );
    if ( ( PWRMETER330A_OK == error_flag ) &&
         ( ( ( reg_data & PWRMETER330A_UNDERVREG_MASK ) >> 14 ) != uvrms ) )
    {
        reg_data &= ~PWRMETER330A_UNDERVREG_MASK;
        reg_data |= ( ( uint32_t ) uvrms << 14 ) & PWRMETER330A_UNDERVREG_MASK;
        error_flag = pwrmeter330a_write_register ( ctx, PWRMETER330A_REG_SHADOW_1E, reg_data );
    }
    return error_flag;
}

err_t pwrmeter330a_read_rms ( pwrmeter330a_t *ctx, float *v_rms, float *i_rms )
{
    uint32_t reg_data;
    if ( PWRMETER330A_ERROR == pwrmeter330a_read_register ( ctx, PWRMETER330A_REG_VOLATILE_20, &reg_data ) )
    {
        return PWRMETER330A_ERROR;
    }
    float volts = ( float ) ( reg_data & 0xFFFF );
    volts /= PWRMETER330A_ADC_FSCALE;
    volts *= PWRMETER330A_DELTA_VIN_MAX_mV;
    volts /= PWRMETER330A_mV_TO_V;
    if ( ctx->bypass_n_en )
    {
        volts *= ( ( PWRMETER330A_DC_RDIV_OHM + PWRMETER330A_RSENSE_OHM ) / PWRMETER330A_RSENSE_OHM );
    }
    else
    {
        volts *= ( ( PWRMETER330A_AC_RDIV_OHM + PWRMETER330A_RSENSE_OHM ) / PWRMETER330A_RSENSE_OHM );
    }
    *v_rms = volts;
    
    float amps = ( float ) ( ( int16_t ) ( ( reg_data >> 16 ) & 0xFFFF ) );
    amps /= PWRMETER330A_ADC_FSCALE;
    amps *= PWRMETER330A_MAX_CURRENT;
    *i_rms = amps;
    return PWRMETER330A_OK;
}

err_t pwrmeter330a_read_average_rms ( pwrmeter330a_t *ctx, float *v_rms, float *i_rms, uint16_t num_avg )
{
    float v_rms_tmp, v_rms_avg = 0, i_rms_tmp, i_rms_avg = 0;
    uint16_t cnt = 0;
    uint16_t bad_read_cnt = 0;
    while ( cnt < num_avg )
    {
        if ( PWRMETER330A_OK == pwrmeter330a_read_rms ( ctx, &v_rms_tmp, &i_rms_tmp ) )
        {
            v_rms_avg += v_rms_tmp;
            i_rms_avg += i_rms_tmp;
            cnt++;
        }
        else
        {
            bad_read_cnt++;
        }
        if ( bad_read_cnt > num_avg )
        {
            return PWRMETER330A_ERROR;
        }
    }
    *v_rms = v_rms_avg / num_avg;
    *i_rms = i_rms_avg / num_avg;
    return PWRMETER330A_OK;
}

// ------------------------------------------------------------------------- END
