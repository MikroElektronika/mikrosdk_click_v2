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
 * @file stepper21.c
 * @brief Stepper 21 Click Driver.
 */

#include "stepper21.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper21_speed_delay ( uint8_t speed_macro );

void stepper21_cfg_setup ( stepper21_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dir = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER21_DEVICE_ADDRESS_A1A0_00;
}

err_t stepper21_init ( stepper21_t *ctx, stepper21_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->step, cfg->step );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t stepper21_default_cfg ( stepper21_t *ctx ) 
{
    err_t error_flag = STEPPER21_OK;
    stepper21_reset_device ( ctx );
    error_flag |= stepper21_enable_device ( ctx );
    stepper21_set_direction ( ctx, STEPPER21_DIR_CW );
    // Configure FAULT, DECAY, and HOME pins as INPUT, others as OUTPUT
    error_flag |= stepper21_write_register ( ctx, STEPPER21_REG_CONFIG, STEPPER21_DEFAULT_CONFIG );
    error_flag |= stepper21_set_sleep_pin ( ctx, STEPPER21_PIN_STATE_HIGH );
    error_flag |= stepper21_set_decay_pin ( ctx, STEPPER21_PIN_STATE_OPEN );
    error_flag |= stepper21_set_step_mode ( ctx, STEPPER21_MODE_FULL_STEP );
    return error_flag;
}

err_t stepper21_write_register ( stepper21_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper21_read_register ( stepper21_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t stepper21_get_step_mode ( stepper21_t *ctx, uint8_t *mode )
{
    uint8_t reg_data = 0;
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    *mode = ( reg_data >> 5 ) & STEPPER21_MODE_MASK;
    return STEPPER21_OK;
}

err_t stepper21_set_step_mode ( stepper21_t *ctx, uint8_t mode )
{
    uint8_t reg_data = 0;
    if ( mode > STEPPER21_MODE_1_OVER_32 )
    {
        return STEPPER21_ERROR;
    }
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    if ( mode == ( ( reg_data >> 5 ) & STEPPER21_MODE_MASK ) )
    {
        return STEPPER21_OK;
    }
    reg_data &= ~( STEPPER21_MODE_MASK << 5 );
    reg_data |= ( mode << 5 );
    return stepper21_write_register ( ctx, STEPPER21_REG_OUTPUT, reg_data );
}

err_t stepper21_get_sleep_pin ( stepper21_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    *state = ( reg_data & STEPPER21_PIN_SLEEP );
    return STEPPER21_OK;
}

err_t stepper21_set_sleep_pin ( stepper21_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER21_PIN_STATE_HIGH )
    {
        return STEPPER21_ERROR;
    }
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    if ( state == ( reg_data & STEPPER21_PIN_SLEEP ) )
    {
        return STEPPER21_OK;
    }
    reg_data &= ~STEPPER21_PIN_SLEEP;
    reg_data |= state;
    return stepper21_write_register ( ctx, STEPPER21_REG_OUTPUT, reg_data );
}

err_t stepper21_get_fault_pin ( stepper21_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_INPUT, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    *state = ( reg_data & STEPPER21_PIN_FAULT ) >> 1;
    return STEPPER21_OK;
}

err_t stepper21_get_decay_pin ( stepper21_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_CONFIG, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    if ( reg_data & STEPPER21_PIN_DECAY )
    {
        *state = STEPPER21_PIN_STATE_OPEN;
    }
    else
    {
        if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_OUTPUT, &reg_data ) )
        {
            return STEPPER21_ERROR;
        }
        *state = ( reg_data & STEPPER21_PIN_DECAY ) >> 2;
    }
    return STEPPER21_OK;
}

err_t stepper21_set_decay_pin ( stepper21_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER21_PIN_STATE_OPEN )
    {
        return STEPPER21_ERROR;
    }
    
    // Check if decay pin is configured as input (state open) or output (state low/high)
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_CONFIG, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    
    // Check and configure the pin as input for open state
    if ( STEPPER21_PIN_STATE_OPEN == state)
    {
        if ( STEPPER21_PIN_DECAY == ( reg_data & STEPPER21_PIN_DECAY ) )
        {
            return STEPPER21_OK;
        }
        else
        {
            reg_data |= STEPPER21_PIN_DECAY;
            return stepper21_write_register ( ctx, STEPPER21_REG_CONFIG, reg_data );
        }
    }
    
    // Check and configure the pin as output for low or high states
    if ( STEPPER21_PIN_DECAY == ( reg_data & STEPPER21_PIN_DECAY ) )
    {
        reg_data &= ~STEPPER21_PIN_DECAY;
        if ( STEPPER21_ERROR == stepper21_write_register ( ctx, STEPPER21_REG_CONFIG, reg_data ) )
        {
            return STEPPER21_ERROR;
        }
    }
    
    // Check and configure the pin output state
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    if ( state == ( ( reg_data & STEPPER21_PIN_DECAY ) >> 2 ) )
    {
        return STEPPER21_OK;
    }
    reg_data &= ~STEPPER21_PIN_DECAY;
    reg_data |= ( state << 2 );
    return stepper21_write_register ( ctx, STEPPER21_REG_OUTPUT, reg_data );
}

err_t stepper21_get_enable_pin ( stepper21_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    *state = ( reg_data & STEPPER21_PIN_ENABLE ) >> 3;
    return STEPPER21_OK;
}

err_t stepper21_set_enable_pin ( stepper21_t *ctx, uint8_t state )
{
    uint8_t reg_data = 0;
    if ( state > STEPPER21_PIN_STATE_HIGH )
    {
        return STEPPER21_ERROR;
    }
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_OUTPUT, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    if ( state == ( reg_data & STEPPER21_PIN_ENABLE ) )
    {
        return STEPPER21_OK;
    }
    reg_data &= ~STEPPER21_PIN_ENABLE;
    reg_data |= ( state << 3 );
    return stepper21_write_register ( ctx, STEPPER21_REG_OUTPUT, reg_data );
}

err_t stepper21_get_home_pin ( stepper21_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( STEPPER21_ERROR == stepper21_read_register ( ctx, STEPPER21_REG_INPUT, &reg_data ) )
    {
        return STEPPER21_ERROR;
    }
    *state = ( reg_data & STEPPER21_PIN_HOME ) >> 4;
    return STEPPER21_OK;
}

void stepper21_drive_motor ( stepper21_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper21_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper21_set_step_pin ( ctx, STEPPER21_PIN_STATE_HIGH );
        stepper21_speed_delay ( speed );
        stepper21_set_step_pin ( ctx, STEPPER21_PIN_STATE_LOW );
        stepper21_speed_delay ( speed );
    }
    stepper21_disable_device ( ctx );
}

err_t stepper21_enable_device ( stepper21_t *ctx )
{
    return stepper21_set_enable_pin ( ctx, STEPPER21_PIN_STATE_LOW );
}

err_t stepper21_disable_device ( stepper21_t *ctx )
{
    return stepper21_set_enable_pin ( ctx, STEPPER21_PIN_STATE_HIGH );
}

void stepper21_set_direction ( stepper21_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper21_switch_direction ( stepper21_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void stepper21_reset_device ( stepper21_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void stepper21_set_rst_pin ( stepper21_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t stepper21_get_int_pin ( stepper21_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void stepper21_set_step_pin ( stepper21_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

static void stepper21_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER21_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER21_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER21_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER21_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER21_SPEED_VERY_FAST:
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
