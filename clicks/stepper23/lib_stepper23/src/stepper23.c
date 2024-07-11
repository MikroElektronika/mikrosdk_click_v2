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
 * @file stepper23.c
 * @brief Stepper 23 Click Driver.
 */

#include "stepper23.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper23_speed_delay ( uint8_t speed_macro );

void stepper23_cfg_setup ( stepper23_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dir = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->clk = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER23_DEVICE_ADDRESS_A1A0_00;
}

err_t stepper23_init ( stepper23_t *ctx, stepper23_cfg_t *cfg ) 
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

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->clk, cfg->clk );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t stepper23_default_cfg ( stepper23_t *ctx ) 
{
    err_t error_flag = STEPPER23_OK;
    
    stepper23_enable_device ( ctx );
    
    stepper23_set_direction ( ctx, STEPPER23_DIR_CW );
    
    // Configure DMODE0, DMODE1, DMODE2, DECAY, TRQ0, TRQ1, and SLEEP_X pins as OUTPUT
    error_flag |= stepper23_write_register ( ctx, STEPPER23_REG_CONFIG_0, STEPPER23_P0_DEFAULT_CONFIG );
    // Configure LO and MO pins as INPUT, and RST pin as OUTPUT
    error_flag |= stepper23_write_register ( ctx, STEPPER23_REG_CONFIG_1, STEPPER23_P1_DEFAULT_CONFIG );
    
    error_flag |= stepper23_reset_device ( ctx );
    
    error_flag |= stepper23_set_sleep_x_pin ( ctx, STEPPER23_PIN_HIGH_LEVEL );
    
    error_flag |= stepper23_set_decay ( ctx, STEPPER23_DECAY_MIXED );
    
    error_flag |= stepper23_set_torque ( ctx, STEPPER23_TORQUE_100_PCT );
    
    error_flag |= stepper23_set_step_mode ( ctx, STEPPER23_MODE_FULL_STEP );

    return error_flag;
}

err_t stepper23_write_register ( stepper23_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper23_read_register ( stepper23_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t stepper23_get_step_mode ( stepper23_t *ctx, uint8_t *mode )
{
    uint8_t reg_data = 0;
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    *mode = reg_data & STEPPER23_MODE_MASK;
    return STEPPER23_OK;
}

err_t stepper23_set_step_mode ( stepper23_t *ctx, uint8_t mode )
{
    uint8_t reg_data = 0;
    if ( mode > STEPPER23_MODE_QUARTER_STEP )
    {
        return STEPPER23_ERROR;
    }
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    if ( mode == ( reg_data & STEPPER23_MODE_MASK ) )
    {
        return STEPPER23_OK;
    }
    reg_data &= ~STEPPER23_MODE_MASK;
    reg_data |= mode;
    return stepper23_write_register ( ctx, STEPPER23_REG_OUTPUT_0, reg_data );
}

err_t stepper23_get_torque ( stepper23_t *ctx, uint8_t *torque )
{
    uint8_t reg_data = 0;
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    *torque = ( reg_data >> 5 ) & STEPPER23_TORQUE_MASK;
    return STEPPER23_OK;
}

err_t stepper23_set_torque ( stepper23_t *ctx, uint8_t torque )
{
    uint8_t reg_data = 0;
    if ( torque > STEPPER23_TORQUE_25_PCT )
    {
        return STEPPER23_ERROR;
    }
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    if ( torque == ( ( reg_data >> 5 ) & STEPPER23_TORQUE_MASK ) )
    {
        return STEPPER23_OK;
    }
    reg_data &= ~( STEPPER23_TORQUE_MASK << 5 );
    reg_data |= ( torque << 5 );
    return stepper23_write_register ( ctx, STEPPER23_REG_OUTPUT_0, reg_data );
}

err_t stepper23_get_decay ( stepper23_t *ctx, uint8_t *decay )
{
    uint8_t reg_data = 0;
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    *decay = ( reg_data >> 3 ) & STEPPER23_DECAY_MASK;
    return STEPPER23_OK;
}

err_t stepper23_set_decay ( stepper23_t *ctx, uint8_t decay )
{
    uint8_t reg_data = 0;
    if ( decay > STEPPER23_DECAY_ADMD )
    {
        return STEPPER23_ERROR;
    }
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    if ( decay == ( ( reg_data >> 3 ) & STEPPER23_DECAY_MASK ) )
    {
        return STEPPER23_OK;
    }
    reg_data &= ~( STEPPER23_DECAY_MASK << 3 );
    reg_data |= ( decay << 3 );
    return stepper23_write_register ( ctx, STEPPER23_REG_OUTPUT_0, reg_data );
}

err_t stepper23_get_sleep_x_pin ( stepper23_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    *state = ( reg_data & STEPPER23_P0_SLEEP_X_PIN ) >> 7;
    return STEPPER23_OK;
}

err_t stepper23_set_sleep_x_pin ( stepper23_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER23_PIN_HIGH_LEVEL )
    {
        return STEPPER23_ERROR;
    }
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_0, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER23_P0_SLEEP_X_PIN ) >> 7 ) )
    {
        return STEPPER23_OK;
    }
    reg_data &= ~STEPPER23_P0_SLEEP_X_PIN;
    reg_data |= ( state << 7 );
    return stepper23_write_register ( ctx, STEPPER23_REG_OUTPUT_0, reg_data );
}

err_t stepper23_get_lo1_pin ( stepper23_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_INPUT_1, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    *state = ( reg_data & STEPPER23_P1_LO1_PIN );
    return STEPPER23_OK;
}

err_t stepper23_get_lo2_pin ( stepper23_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_INPUT_1, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    *state = ( reg_data & STEPPER23_P1_LO2_PIN ) >> 1;
    return STEPPER23_OK;
}

err_t stepper23_get_mo_pin ( stepper23_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_INPUT_1, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    *state = ( reg_data & STEPPER23_P1_MO_PIN ) >> 2;
    return STEPPER23_OK;
}

err_t stepper23_get_rst_pin ( stepper23_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_1, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    *state = ( reg_data & STEPPER23_P1_RST_PIN ) >> 3;
    return STEPPER23_OK;
}

err_t stepper23_set_rst_pin ( stepper23_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER23_PIN_HIGH_LEVEL )
    {
        return STEPPER23_ERROR;
    }
    if ( STEPPER23_ERROR == stepper23_read_register ( ctx, STEPPER23_REG_OUTPUT_1, &reg_data ) )
    {
        return STEPPER23_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER23_P1_RST_PIN ) >> 3 ) )
    {
        return STEPPER23_OK;
    }
    reg_data &= ~STEPPER23_P1_RST_PIN;
    reg_data |= ( state << 3 );
    return stepper23_write_register ( ctx, STEPPER23_REG_OUTPUT_1, reg_data );
}

err_t stepper23_reset_device ( stepper23_t *ctx )
{
    err_t error_flag = stepper23_set_rst_pin ( ctx, STEPPER23_PIN_HIGH_LEVEL );
    Delay_100ms ( );
    error_flag |= stepper23_set_rst_pin ( ctx, STEPPER23_PIN_LOW_LEVEL );
    Delay_100ms ( );
    return error_flag;
}

void stepper23_drive_motor ( stepper23_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper23_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper23_set_clk_pin ( ctx, STEPPER23_PIN_HIGH_LEVEL );
        stepper23_speed_delay ( speed );
        stepper23_set_clk_pin ( ctx, STEPPER23_PIN_LOW_LEVEL );
        stepper23_speed_delay ( speed );
    }
    stepper23_disable_device ( ctx );
}

void stepper23_enable_device ( stepper23_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper23_disable_device ( stepper23_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepper23_set_direction ( stepper23_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper23_switch_direction ( stepper23_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

uint8_t stepper23_get_int_pin ( stepper23_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void stepper23_set_clk_pin ( stepper23_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->clk, state );
}

static void stepper23_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER23_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER23_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER23_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER23_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER23_SPEED_VERY_FAST:
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
