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
 * @file brushless14.c
 * @brief Brushless 14 Click Driver.
 */

#include "brushless14.h"

#define BRUSHLESS14_VREF            5000.0
#define BRUSHLESS14_RESOLUTION      4095.0


void brushless14_cfg_setup ( brushless14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
   //cfg->cs   = HAL_PIN_NC;
   //cfg->an   = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
   //cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    
    cfg->i2c_address = BRUSHLESS14_DAC_SLAVE_ADDR;
    
	cfg->dev_pwm_freq = BRUSHLESS14_DEF_FREQ;
}

err_t brushless14_init ( brushless14_t *ctx, brushless14_cfg_t *cfg ) 
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

    if ( I2C_MASTER_ERROR == i2c_master_set_timeout( &ctx->i2c, 0 ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->dir, cfg->dir );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t brushless14_default_cfg ( brushless14_t *ctx ) 
{
    //Default configuration for enabling dac output.
    err_t ret_val = brushless14_dac_write( ctx, BRUSHLESS14_DAC_REG_CONFIG, 0x0000 );
    //Set P7, P6, P5 to input rest to output
    ret_val |= brushless14_port_expander_write( ctx,  BRUSHLESS14_PE_REG_CONFIGURATION, 0xE0 );
    brushless14_set_dir( ctx, 0 );
    ret_val |= brushless14_set_duty_cycle ( ctx, 0 );
    ret_val |= brushless14_pwm_start( ctx );
    
    return ret_val;
}

err_t brushless14_set_duty_cycle ( brushless14_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless14_pwm_stop ( brushless14_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless14_pwm_start ( brushless14_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

err_t brushless14_dac_write ( brushless14_t *ctx, uint8_t reg, uint16_t in_data )
{
    uint8_t write_data[ 3 ] = { 0 };
    err_t ret_val = BRUSHLESS14_OK;
    
    write_data[ 0 ] = reg;
    write_data[ 1 ] = in_data >> 8;
    write_data[ 2 ] = in_data;
    
    ret_val |= i2c_master_set_slave_address( &ctx->i2c, BRUSHLESS14_DAC_SLAVE_ADDR );
    ret_val |= i2c_master_write( &ctx->i2c, write_data, 3 );
    
    return ret_val;
}

err_t brushless14_dac_read ( brushless14_t *ctx, uint8_t reg, uint16_t *out_data )
{
    uint8_t read_data[ 2 ] = { 0 };
    err_t ret_val = BRUSHLESS14_OK;
    
    ret_val |= i2c_master_set_slave_address( &ctx->i2c, BRUSHLESS14_DAC_SLAVE_ADDR );
    ret_val |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, read_data, 2 );
    
    *out_data = ( ( uint16_t )read_data[ 0 ] << 8 ) | read_data[ 1 ];
    
    return ret_val;
}

err_t brushless14_set_adj0 ( brushless14_t *ctx, uint16_t m_voltage )
{
    volatile float temp_data = ( float )m_voltage * BRUSHLESS14_RESOLUTION / BRUSHLESS14_VREF;
    return brushless14_dac_write ( ctx, BRUSHLESS14_DAC_REG_DAC_A_DATA, ( uint16_t )temp_data );
}

err_t brushless14_set_adj1 ( brushless14_t *ctx, uint16_t m_voltage )
{
    float temp_data = ( float )m_voltage * BRUSHLESS14_RESOLUTION / BRUSHLESS14_VREF;
    return brushless14_dac_write ( ctx, BRUSHLESS14_DAC_REG_DAC_B_DATA, ( uint16_t )temp_data );
}

err_t brushless14_set_adj2 ( brushless14_t *ctx, uint16_t m_voltage )
{
    float temp_data = ( float )m_voltage * BRUSHLESS14_RESOLUTION / BRUSHLESS14_VREF;
    return brushless14_dac_write ( ctx, BRUSHLESS14_DAC_REG_DAC_C_DATA, ( uint16_t )temp_data );
}

err_t brushless14_set_adj3 ( brushless14_t *ctx, uint16_t m_voltage )
{
    float temp_data = ( float )m_voltage * BRUSHLESS14_RESOLUTION / BRUSHLESS14_VREF;
    return brushless14_dac_write ( ctx, BRUSHLESS14_DAC_REG_DAC_D_DATA, ( uint16_t )temp_data );
}

err_t brushless14_set_fpwm ( brushless14_t *ctx, uint16_t m_voltage )
{
    float temp_data = ( float )m_voltage * BRUSHLESS14_RESOLUTION / BRUSHLESS14_VREF;
    return brushless14_dac_write ( ctx, BRUSHLESS14_DAC_REG_DAC_E_DATA, ( uint16_t )temp_data );
}

err_t brushless14_set_la ( brushless14_t *ctx, uint16_t m_voltage )
{
    volatile float temp_data = ( float )m_voltage * BRUSHLESS14_RESOLUTION / BRUSHLESS14_VREF;
    return brushless14_dac_write ( ctx, BRUSHLESS14_DAC_REG_DAC_F_DATA, ( uint16_t )temp_data );
}

err_t brushless14_port_expander_write ( brushless14_t *ctx, uint8_t reg, uint8_t in_data )
{
    uint8_t write_data[ 2 ] = { 0 };
    err_t ret_val = BRUSHLESS14_OK;
    
    write_data[ 0 ] = reg;
    write_data[ 1 ] = in_data;
    
    ret_val |= i2c_master_set_slave_address( &ctx->i2c, BRUSHLESS14_EXPANDER_SLAVE_ADDR );
    ret_val |= i2c_master_write( &ctx->i2c, write_data, 2 );
    
    return ret_val;
}

err_t brushless14_port_expander_read ( brushless14_t *ctx, uint8_t reg, uint8_t *out_data )
{
    err_t ret_val = BRUSHLESS14_OK;

    ret_val |= i2c_master_set_slave_address( &ctx->i2c, BRUSHLESS14_EXPANDER_SLAVE_ADDR );
    ret_val |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, out_data, 1 );
    
    return ret_val;
}

err_t brushless14_set_slop ( brushless14_t *ctx, uint8_t state )
{
    volatile uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = brushless14_port_expander_read( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, &current_state );
    current_state &= 0xFE;
    
    if ( state )
    {
        current_state |= 0x01;
    }
    ret_val |= brushless14_port_expander_write( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, current_state );
    
    return ret_val;
}

err_t brushless14_set_rot ( brushless14_t *ctx, uint8_t state )
{
    uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = brushless14_port_expander_read( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, &current_state );
    current_state &= 0xFD;
    
    if ( state )
    {
        current_state |= 0x02;
    }
    ret_val |= brushless14_port_expander_write( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, current_state );
    
    return ret_val;
}

err_t brushless14_set_fst ( brushless14_t *ctx, uint8_t state )
{
    uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = brushless14_port_expander_read( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, &current_state );
    current_state &= 0xFB;
    
    if ( state )
    {
        current_state |= 0x04;
    }
    ret_val |= brushless14_port_expander_write( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, current_state );
    
    return ret_val;
}

err_t brushless14_set_sel_adj ( brushless14_t *ctx, uint8_t state )
{
    uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = brushless14_port_expander_read( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, &current_state );
    current_state &= 0xF7;
    
    if ( state )
    {
        current_state |= 0x08;
    }
    ret_val |= brushless14_port_expander_write( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, current_state );
    
    return ret_val;
}

err_t brushless14_set_lap ( brushless14_t *ctx, uint8_t state )
{
    uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = brushless14_port_expander_read( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, &current_state );
    current_state &= 0xEF;
    
    if ( state )
    {
        current_state |= 0x10;
    }
    ret_val |= brushless14_port_expander_write( ctx, BRUSHLESS14_PE_REG_OUTPUT_PORT, current_state );
    
    return ret_val;
}

err_t brushless14_get_fg_out ( brushless14_t *ctx, uint8_t *state )
{
    uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = brushless14_port_expander_read( ctx, BRUSHLESS14_PE_REG_INPUT_PORT, &current_state );
    current_state >>= 5;
    
    *state = current_state & 1;
    
    return ret_val;
}

err_t brushless14_get_ld_out ( brushless14_t *ctx, uint8_t *state )
{
    uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = brushless14_port_expander_read( ctx, BRUSHLESS14_PE_REG_INPUT_PORT, &current_state );
    
    current_state >>= 6;
    *state = current_state & 1;
    
    return ret_val;
}

uint8_t brushless14_get_int ( brushless14_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void brushless14_set_dir ( brushless14_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->dir );
    }
    else
    {
        digital_out_low( &ctx->dir );
    }
}

// ------------------------------------------------------------------------- END
