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
 * @file multisteppertb67s101.c
 * @brief Multi Stepper TB67S101 Click Driver.
 */

#include "multisteppertb67s101.h"

/**
 * @brief Multi Stepper TB67S101 I/O signal table for full step resolution.
 * @details Specified I/O signal table for full step resolution, set in the following order:
 * PHASEA, INA1, INA2, PHASEB, INB1, and INB2.
 */
static uint8_t multisteppertb67s101_full_step[ 4 ][ 6 ] = 
{
    { 1, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 0, 1, 1 },
    { 1, 1, 1, 0, 1, 1 },
};

/**
 * @brief Multi Stepper TB67S101 I/O signal table for half step resolution.
 * @details Specified I/O signal table for half step resolution, set in the following order:
 * PHASEA, INA1, INA2, PHASEB, INB1, and INB2.
 */
static uint8_t multisteppertb67s101_half_step[ 8 ][ 6 ] = 
{
    { 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 1, 1, 1 },
    { 0, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 0, 0, 0 },
    { 0, 1, 1, 0, 1, 1 },
    { 0, 0, 0, 0, 1, 1 },
    { 1, 1, 1, 0, 1, 1 },
    { 1, 1, 1, 0, 0, 0 }
};

/**
 * @brief Multi Stepper TB67S101 I/O signal table for quarter step resolution.
 * @details Specified I/O signal table for quarter step resolution, set in the following order:
 * PHASEA, INA1, INA2, PHASEB, INB1, and INB2.
 */
static uint8_t multisteppertb67s101_quarter_step[ 16 ][ 6 ] = 
{
    { 1, 1, 0, 1, 1, 0 },
    { 1, 0, 1, 1, 1, 1 },
    { 0, 0, 0, 1, 1, 1 },
    { 0, 0, 1, 1, 1, 1 },
    { 0, 1, 0, 1, 1, 0 },
    { 0, 1, 1, 1, 0, 1 },
    { 0, 1, 1, 0, 0, 0 },
    { 0, 1, 1, 0, 0, 1 },
    { 0, 1, 0, 0, 1, 0 },
    { 0, 0, 1, 0, 1, 1 },
    { 0, 0, 0, 0, 1, 1 },
    { 1, 0, 1, 0, 1, 1 },
    { 1, 1, 0, 0, 1, 0 },
    { 1, 1, 1, 0, 0, 1 },
    { 1, 1, 1, 0, 0, 0 },
    { 1, 1, 1, 1, 0, 1 } 
};

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void multisteppertb67s101_speed_delay ( uint8_t speed_macro );

/**
 * @brief Set pins for one micro step.
 * @details This function sets PHASEA, INA1, INA2, PHASEB, INB1, and INB2 pins for a desired step.
 * @param[in] ctx : Click context object.
 * See #multisteppertb67s101_t object definition for detailed explanation.
 * @param[in] pins_array : Array of six bytes that contains PHASEA, INA1, INA2, PHASEB, INB1, and INB2 pins
 * logic state value.
 * @return Nothing.
 */
static err_t multisteppertb67s101_set_pins ( multisteppertb67s101_t *ctx, uint8_t pins_array[ 6 ] );

void multisteppertb67s101_cfg_setup ( multisteppertb67s101_cfg_t *cfg ) 
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
    cfg->i2c_address = MULTISTEPPERTB67S101_DEVICE_ADDRESS_A1A0_00;
}

err_t multisteppertb67s101_init ( multisteppertb67s101_t *ctx, multisteppertb67s101_cfg_t *cfg ) 
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
    digital_out_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t multisteppertb67s101_default_cfg ( multisteppertb67s101_t *ctx ) 
{
    multisteppertb67s101_set_direction ( ctx, MULTISTEPPERTB67S101_DIR_CW );
    
    multisteppertb67s101_set_step_mode ( ctx, MULTISTEPPERTB67S101_MODE_FULL_STEP );
    
    // Configure PHASEA and PHASEB as OUTPUT, others as INPUT
    return multisteppertb67s101_write_register ( ctx, MULTISTEPPERTB67S101_REG_CONFIG, MULTISTEPPERTB67S101_DEFAULT_CONFIG );
}

err_t multisteppertb67s101_write_register ( multisteppertb67s101_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t multisteppertb67s101_read_register ( multisteppertb67s101_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t multisteppertb67s101_drive_motor ( multisteppertb67s101_t *ctx, uint32_t steps, uint8_t speed )
{
    err_t error_flag = MULTISTEPPERTB67S101_OK;
    multisteppertb67s101_enable_device ( ctx );
    for ( uint32_t num_steps = 0; num_steps < steps; num_steps++ )
    {
        if ( MULTISTEPPERTB67S101_MODE_QUARTER_STEP == ctx->step_mode )
        {
            if ( MULTISTEPPERTB67S101_DIR_CW == ctx->direction )
            {
                error_flag |= multisteppertb67s101_set_pins ( ctx, multisteppertb67s101_quarter_step[ num_steps % 16 ] );
            }
            else
            {
                error_flag |= multisteppertb67s101_set_pins ( ctx, multisteppertb67s101_quarter_step[ 15 - ( num_steps % 16 ) ] );
            }
        }
        else if ( MULTISTEPPERTB67S101_MODE_HALF_STEP == ctx->step_mode )
        {
            if ( MULTISTEPPERTB67S101_DIR_CW == ctx->direction )
            {
                error_flag |= multisteppertb67s101_set_pins ( ctx, multisteppertb67s101_half_step[ num_steps % 8 ] );
            }
            else
            {
                error_flag |= multisteppertb67s101_set_pins ( ctx, multisteppertb67s101_half_step[ 7 - ( num_steps % 8 ) ] );
            }
        }
        else
        {
            if ( MULTISTEPPERTB67S101_DIR_CW == ctx->direction )
            {
                error_flag |= multisteppertb67s101_set_pins ( ctx, multisteppertb67s101_full_step[ num_steps % 4 ] );
            }
            else
            {
                error_flag |= multisteppertb67s101_set_pins ( ctx, multisteppertb67s101_full_step[ 3 - ( num_steps % 4 ) ] );
            }
        }
        multisteppertb67s101_speed_delay ( speed );
    }
    multisteppertb67s101_disable_device ( ctx );
    return error_flag;
}

void multisteppertb67s101_enable_device ( multisteppertb67s101_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void multisteppertb67s101_disable_device ( multisteppertb67s101_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void multisteppertb67s101_set_ina1_pin ( multisteppertb67s101_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->an, state );
}

void multisteppertb67s101_set_ina2_pin ( multisteppertb67s101_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->int_pin, state );
}

void multisteppertb67s101_set_inb1_pin ( multisteppertb67s101_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->clk, state );
}

void multisteppertb67s101_set_inb2_pin ( multisteppertb67s101_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en, state );
}

void multisteppertb67s101_set_step_mode ( multisteppertb67s101_t *ctx, uint8_t mode )
{
    if ( MULTISTEPPERTB67S101_MODE_QUARTER_STEP == mode )
    {
        ctx->step_mode = MULTISTEPPERTB67S101_MODE_QUARTER_STEP;
    }
    else if ( MULTISTEPPERTB67S101_MODE_HALF_STEP == mode )
    {
        ctx->step_mode = MULTISTEPPERTB67S101_MODE_HALF_STEP;
    }
    else
    {
        ctx->step_mode = MULTISTEPPERTB67S101_MODE_FULL_STEP;
    }
}

void multisteppertb67s101_set_direction ( multisteppertb67s101_t *ctx, uint8_t dir )
{
    if ( MULTISTEPPERTB67S101_DIR_CCW == dir )
    {
        ctx->direction = MULTISTEPPERTB67S101_DIR_CCW;
    }
    else
    {
        ctx->direction = MULTISTEPPERTB67S101_DIR_CW;
    }
}

void multisteppertb67s101_switch_direction ( multisteppertb67s101_t *ctx )
{
    if ( MULTISTEPPERTB67S101_DIR_CCW == ctx->direction )
    {
        ctx->direction = MULTISTEPPERTB67S101_DIR_CW;
    }
    else
    {
        ctx->direction = MULTISTEPPERTB67S101_DIR_CCW;
    }
}

static void multisteppertb67s101_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case MULTISTEPPERTB67S101_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case MULTISTEPPERTB67S101_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case MULTISTEPPERTB67S101_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case MULTISTEPPERTB67S101_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case MULTISTEPPERTB67S101_SPEED_VERY_FAST:
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

static err_t multisteppertb67s101_set_pins ( multisteppertb67s101_t *ctx, uint8_t pins_array[ 6 ] )
{
    uint8_t reg_data = ( pins_array[ 0 ] << 1 ) | ( pins_array[ 3 ] << 2 ); // PHASEA and PHASEB
    multisteppertb67s101_set_ina1_pin ( ctx, pins_array[ 1 ] );
    multisteppertb67s101_set_ina2_pin ( ctx, pins_array[ 2 ] );
    multisteppertb67s101_set_inb1_pin ( ctx, pins_array[ 4 ] );
    multisteppertb67s101_set_inb2_pin ( ctx, pins_array[ 5 ] );
    return multisteppertb67s101_write_register ( ctx, MULTISTEPPERTB67S101_REG_OUTPUT, reg_data );
}

// ------------------------------------------------------------------------- END
