/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file stepper29.c
 * @brief Stepper 29 Click Driver.
 */

#include "stepper29.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper29_speed_delay ( uint8_t speed_macro );

void stepper29_cfg_setup ( stepper29_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dir = HAL_PIN_NC;
    cfg->agc_out = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->clk = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER29_DEVICE_ADDRESS_A1A0_00;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = STEPPER29_VREF_DEFAULT;
}

err_t stepper29_init ( stepper29_t *ctx, stepper29_cfg_t *cfg ) 
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

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->agc_out;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->clk, cfg->clk );
    digital_out_init( &ctx->mosi, cfg->mosi );
    digital_out_init( &ctx->sck, cfg->sck );
    Delay_1ms ( );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->mosi );
    digital_out_high( &ctx->sck );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t stepper29_default_cfg ( stepper29_t *ctx ) 
{
    err_t error_flag = STEPPER29_OK;
    
    stepper29_enable_device ( ctx );
    
    stepper29_set_direction ( ctx, STEPPER29_DIR_CW );

    // Configure DMODE0, DMODE1, DMODE2, RST pins as OUTPUT, and LO0, LO1 as INPUT
    error_flag |= stepper29_write_exp_reg ( ctx, STEPPER29_EXP_REG_CONFIG_0, STEPPER29_P0_DEFAULT_CONFIG );
    // Configure SLEEP, AWGS, AGC_ON, ADMD, AGC_AUTO pins as OUTPUT, and LO2, MO as INPUT
    error_flag |= stepper29_write_exp_reg ( ctx, STEPPER29_EXP_REG_CONFIG_1, STEPPER29_P1_DEFAULT_CONFIG );
    
    error_flag |= stepper29_reset_device ( ctx );
    
    error_flag |= stepper29_set_sleep_pin ( ctx, STEPPER29_PIN_HIGH_LEVEL );
    
    error_flag |= stepper29_set_step_function ( ctx, STEPPER29_STEP_FUN_NORMAL_USTEP );
    
    error_flag |= stepper29_set_step_mode ( ctx, STEPPER29_MODE_FULL_STEP );

    return error_flag;
}

err_t stepper29_write_reg ( stepper29_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( reg > STEPPER29_REG_ODET_MASK_M_DAC_SEL )
    {
        return STEPPER29_ERROR;
    }
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 7 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in << 1 ) & 0xFE );

    // Start condition
    digital_out_low ( &ctx->mosi );
    Delay_10us ( );
    digital_out_low ( &ctx->sck );
    Delay_10us ( );
    digital_out_write ( &ctx->mosi, 0 );
    digital_out_high ( &ctx->sck );
    Delay_10us ( );

    // Write address byte + 14-bit data + stop condition
    for ( uint8_t byte_cnt = 0; byte_cnt < 3; byte_cnt++ )
    {
        for ( uint8_t bit_cnt = 8; bit_cnt > 0; bit_cnt-- )
        {
            digital_out_low ( &ctx->sck );
            Delay_10us ( );
            
            digital_out_write ( &ctx->mosi, ( ( data_buf[ byte_cnt ] >> ( bit_cnt - 1 ) ) & 1 ) );
            
            digital_out_high ( &ctx->sck );
            Delay_10us ( );
        }
    }
    digital_out_high ( &ctx->mosi );
    return STEPPER29_OK;
}

err_t stepper29_write_exp_reg ( stepper29_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper29_read_exp_reg ( stepper29_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t stepper29_get_step_mode ( stepper29_t *ctx, uint8_t *mode )
{
    uint8_t reg_data = 0;
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    *mode = reg_data & STEPPER29_MODE_MASK;
    return STEPPER29_OK;
}

err_t stepper29_set_step_mode ( stepper29_t *ctx, uint8_t mode )
{
    uint8_t reg_data = 0;
    if ( mode > STEPPER29_MODE_1_OVER_32 )
    {
        return STEPPER29_ERROR;
    }
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    if ( mode == ( reg_data & STEPPER29_MODE_MASK ) )
    {
        return STEPPER29_OK;
    }
    reg_data &= ~STEPPER29_MODE_MASK;
    reg_data |= mode;
    return stepper29_write_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_0, reg_data );
}

err_t stepper29_get_step_function ( stepper29_t *ctx, uint8_t *func )
{
    uint8_t reg_data = 0;
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_1, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    *func = ( reg_data >> 4 ) & STEPPER29_STEP_FUN_MASK;
    return STEPPER29_OK;
}

err_t stepper29_set_step_function ( stepper29_t *ctx, uint8_t func )
{
    uint8_t reg_data = 0;
    if ( func > STEPPER29_STEP_FUN_AGC_AWGS_INT_AUTO )
    {
        return STEPPER29_ERROR;
    }
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_1, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    if ( func == ( ( reg_data >> 4 ) & STEPPER29_STEP_FUN_MASK ) )
    {
        return STEPPER29_OK;
    }
    reg_data &= ~( STEPPER29_STEP_FUN_MASK << 4 );
    reg_data |= ( func << 4 );
    return stepper29_write_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_1, reg_data );
}

err_t stepper29_get_sleep_pin ( stepper29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_1, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    *state = ( reg_data & STEPPER29_P1_SLEEP_PIN ) >> 2;
    return STEPPER29_OK;
}

err_t stepper29_set_sleep_pin ( stepper29_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER29_PIN_HIGH_LEVEL )
    {
        return STEPPER29_ERROR;
    }
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_1, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER29_P1_SLEEP_PIN ) >> 2 ) )
    {
        return STEPPER29_OK;
    }
    reg_data &= ~STEPPER29_P1_SLEEP_PIN;
    reg_data |= ( state << 2 );
    return stepper29_write_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_1, reg_data );
}

err_t stepper29_get_lo0_pin ( stepper29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_INPUT_0, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    *state = ( reg_data & STEPPER29_P0_LO0_PIN ) >> 6;
    return STEPPER29_OK;
}

err_t stepper29_get_lo1_pin ( stepper29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_INPUT_0, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    *state = ( reg_data & STEPPER29_P0_LO1_PIN ) >> 7;
    return STEPPER29_OK;
}

err_t stepper29_get_lo2_pin ( stepper29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_INPUT_1, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    *state = ( reg_data & STEPPER29_P1_LO2_PIN );
    return STEPPER29_OK;
}

err_t stepper29_get_mo_pin ( stepper29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_INPUT_1, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    *state = ( reg_data & STEPPER29_P1_MO_PIN ) >> 1;
    return STEPPER29_OK;
}

err_t stepper29_get_rst_pin ( stepper29_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    *state = ( reg_data & STEPPER29_P0_RST_PIN ) >> 3;
    return STEPPER29_OK;
}

err_t stepper29_set_rst_pin ( stepper29_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER29_PIN_HIGH_LEVEL )
    {
        return STEPPER29_ERROR;
    }
    if ( STEPPER29_ERROR == stepper29_read_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER29_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER29_P0_RST_PIN ) >> 3 ) )
    {
        return STEPPER29_OK;
    }
    reg_data &= ~STEPPER29_P0_RST_PIN;
    reg_data |= ( state << 3 );
    return stepper29_write_exp_reg ( ctx, STEPPER29_EXP_REG_OUTPUT_0, reg_data );
}

err_t stepper29_reset_device ( stepper29_t *ctx )
{
    err_t error_flag = STEPPER29_OK;
    error_flag |= stepper29_set_rst_pin ( ctx, STEPPER29_PIN_LOW_LEVEL );
    Delay_100ms ( );
    error_flag |= stepper29_set_rst_pin ( ctx, STEPPER29_PIN_HIGH_LEVEL );
    Delay_100ms ( );
    return error_flag;
}

void stepper29_drive_motor ( stepper29_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper29_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper29_set_clk_pin ( ctx, STEPPER29_PIN_HIGH_LEVEL );
        stepper29_speed_delay ( speed );
        stepper29_set_clk_pin ( ctx, STEPPER29_PIN_LOW_LEVEL );
        stepper29_speed_delay ( speed );
    }
    stepper29_disable_device ( ctx );
}

void stepper29_enable_device ( stepper29_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper29_disable_device ( stepper29_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepper29_set_direction ( stepper29_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper29_switch_direction ( stepper29_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

uint8_t stepper29_get_int_pin ( stepper29_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void stepper29_set_clk_pin ( stepper29_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->clk, state );
}

err_t stepper29_read_adc_raw ( stepper29_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t stepper29_read_adc_volt ( stepper29_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t stepper29_read_adc_volt_avg ( stepper29_t *ctx, uint16_t num_conv, float *volt_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( STEPPER29_OK == stepper29_read_adc_volt ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            timeout_cnt = 0;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > STEPPER29_TIMEOUT_MS )
        {
            return STEPPER29_ERROR;
        }
    }
    *volt_avg = ( voltage_sum / num_conv );
    return STEPPER29_OK;
}

err_t stepper29_set_adc_vref ( stepper29_t *ctx, float vref ) 
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

err_t stepper29_get_out_current ( stepper29_t *ctx, float *position )
{
    float voltage = 0;
    err_t error_flag = stepper29_read_adc_volt_avg ( ctx, STEPPER29_NUM_CONVERSIONS, &voltage );
    if ( ( STEPPER29_OK == error_flag ) && ( NULL != position ) )
    {
        *position = voltage / STEPPER29_VOLTAGE_TO_OUT_CURRENT;
    }
    return error_flag;
}

static void stepper29_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER29_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER29_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER29_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER29_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER29_SPEED_VERY_FAST:
        {
            Delay_500us( );
            break;
        }
        default:
        {
            Delay_1ms( );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
