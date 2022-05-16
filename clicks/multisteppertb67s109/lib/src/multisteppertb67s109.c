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
 * @file multisteppertb67s109.c
 * @brief Multi Stepper TB67S109 Click Driver.
 */

#include "multisteppertb67s109.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void multisteppertb67s109_speed_delay ( uint8_t speed_macro );

void multisteppertb67s109_cfg_setup ( multisteppertb67s109_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->clk  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = MULTISTEPPERTB67S109_DEVICE_ADDRESS_A1A0_00;
}

err_t multisteppertb67s109_init ( multisteppertb67s109_t *ctx, multisteppertb67s109_cfg_t *cfg ) 
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

    digital_out_init( &ctx->an, cfg->an );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->clk, cfg->clk );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t multisteppertb67s109_default_cfg ( multisteppertb67s109_t *ctx ) 
{
    err_t error_flag = MULTISTEPPERTB67S109_OK;
    
    multisteppertb67s109_enable_device ( ctx );
    
    multisteppertb67s109_set_direction ( ctx, MULTISTEPPERTB67S109_DIR_CW );
    
    multisteppertb67s109_reset_device ( ctx );
    
    // Configure DMODE0, DMODE1, and DMODE2 as OUTPUT, others as INPUT
    error_flag |= multisteppertb67s109_write_register ( ctx, MULTISTEPPERTB67S109_REG_CONFIG, MULTISTEPPERTB67S109_DEFAULT_CONFIG );
    
    error_flag |= multisteppertb67s109_set_step_mode ( ctx, MULTISTEPPERTB67S109_MODE_FULL_STEP );

    return error_flag;
}

err_t multisteppertb67s109_write_register ( multisteppertb67s109_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t multisteppertb67s109_read_register ( multisteppertb67s109_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t multisteppertb67s109_get_step_mode ( multisteppertb67s109_t *ctx, uint8_t *mode )
{
    uint8_t reg_data;
    if ( MULTISTEPPERTB67S109_ERROR == multisteppertb67s109_read_register ( ctx, MULTISTEPPERTB67S109_REG_OUTPUT, &reg_data ) )
    {
        return MULTISTEPPERTB67S109_ERROR;
    }
    *mode = reg_data & MULTISTEPPERTB67S109_MODE_BITS_MASK;
    return MULTISTEPPERTB67S109_OK;
}

err_t multisteppertb67s109_set_step_mode ( multisteppertb67s109_t *ctx, uint8_t mode )
{
    if ( mode > MULTISTEPPERTB67S109_MODE_1_OVER_32 )
    {
        return MULTISTEPPERTB67S109_ERROR;
    }
    uint8_t reg_data;
    if ( MULTISTEPPERTB67S109_ERROR == multisteppertb67s109_read_register ( ctx, MULTISTEPPERTB67S109_REG_OUTPUT, &reg_data ) )
    {
        return MULTISTEPPERTB67S109_ERROR;
    }
    if ( mode == ( reg_data & MULTISTEPPERTB67S109_MODE_BITS_MASK ) )
    {
        return MULTISTEPPERTB67S109_OK;
    }
    reg_data &= ~MULTISTEPPERTB67S109_MODE_BITS_MASK;
    reg_data |= mode;
    return multisteppertb67s109_write_register ( ctx, MULTISTEPPERTB67S109_REG_OUTPUT, reg_data );
}

void multisteppertb67s109_drive_motor ( multisteppertb67s109_t *ctx, uint32_t steps, uint8_t speed )
{
    multisteppertb67s109_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        multisteppertb67s109_set_clk_pin ( ctx, MULTISTEPPERTB67S109_PIN_HIGH_LEVEL );
        multisteppertb67s109_speed_delay ( speed );
        multisteppertb67s109_set_clk_pin ( ctx, MULTISTEPPERTB67S109_PIN_LOW_LEVEL );
        multisteppertb67s109_speed_delay ( speed );
    }
    multisteppertb67s109_disable_device ( ctx );
}

void multisteppertb67s109_enable_device ( multisteppertb67s109_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void multisteppertb67s109_disable_device ( multisteppertb67s109_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void multisteppertb67s109_set_direction ( multisteppertb67s109_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->an, dir );
}

void multisteppertb67s109_switch_direction ( multisteppertb67s109_t *ctx )
{
    digital_out_toggle ( &ctx->an );
}

void multisteppertb67s109_reset_device ( multisteppertb67s109_t *ctx )
{
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t multisteppertb67s109_get_int_pin ( multisteppertb67s109_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void multisteppertb67s109_set_clk_pin ( multisteppertb67s109_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->clk, state );
}

static void multisteppertb67s109_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case MULTISTEPPERTB67S109_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case MULTISTEPPERTB67S109_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case MULTISTEPPERTB67S109_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case MULTISTEPPERTB67S109_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case MULTISTEPPERTB67S109_SPEED_VERY_FAST:
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
