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
 * @file stepper11.c
 * @brief Stepper 11 Click Driver.
 */

#include "stepper11.h"

/**
 * @brief Driver macros for calculation.
 */
#define STEPPER11_FULL_CIRCLE               360.0
#define STEPPER11_DUMMY                     0

/**
 * @brief Stepper 11 device resolution value.
 * @details Specified setting for step value.
 */
#define STEPPER11_RESOLUTION_VALUE_FULL     1
#define STEPPER11_RESOLUTION_VALUE_HALF     2
#define STEPPER11_RESOLUTION_VALUE_QUARTER  4
#define STEPPER11_RESOLUTION_VALUE_1div8    8
#define STEPPER11_RESOLUTION_VALUE_1div16   16
#define STEPPER11_RESOLUTION_VALUE_1div32   32

/**
 * @brief Set delay for controling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper11_speed_delay( uint8_t speed_macro );

void stepper11_cfg_setup ( stepper11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->dir   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->clk = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER11_SET_DEV_ADDR;
}

err_t stepper11_init ( stepper11_t *ctx, stepper11_cfg_t *cfg ) 
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

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->clk, cfg->clk );
    digital_out_init( &ctx->en, cfg->en );
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    ctx->steps = 0;
    ctx->resolution = 0.0;
    ctx->step_resolution = 0;

    return I2C_MASTER_SUCCESS;
}

err_t stepper11_default_cfg ( stepper11_t *ctx ) 
{
    //Set P7, P6, P5 to input rest to output
    err_t ret_val = stepper11_generic_write( ctx,  STEPPER11_REG_CONFIGURATION, 0xE0 );
    
    stepper11_set_reset( ctx, 0 );
    stepper11_set_enable( ctx, 1 );

    ctx->steps = 200;
    stepper11_set_step_resolution( ctx, STEPPER11_RESOLUTION_FULL );
    
    return ret_val;
}

err_t stepper11_generic_write ( stepper11_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepper11_generic_read ( stepper11_t *ctx, uint8_t reg, uint8_t *rx_data )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_data, 1 );
}

void stepper11_set_direction ( stepper11_t *ctx, uint8_t state )
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

void stepper11_set_enable ( stepper11_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

void stepper11_set_reset ( stepper11_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void stepper11_set_clock ( stepper11_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->clk );
    }
    else
    {
        digital_out_low( &ctx->clk );
    }
}

uint8_t stepper11_get_interrupt ( stepper11_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t stepper11_get_diag ( stepper11_t *ctx )
{
    uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = stepper11_generic_read( ctx, STEPPER11_REG_INPUT_PORT, &current_state );
    
    current_state >>= 5;
    return current_state & 1;
}

uint8_t stepper11_get_mo ( stepper11_t *ctx )
{
    uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = stepper11_generic_read( ctx, STEPPER11_REG_INPUT_PORT, &current_state );
    
    current_state >>= 6;
    return current_state & 1;
}

uint8_t stepper11_get_sd ( stepper11_t *ctx )
{
    uint8_t current_state = 0;
    err_t ret_val;
    
    ret_val = stepper11_generic_read( ctx, STEPPER11_REG_INPUT_PORT, &current_state );
    
    current_state >>= 7;
    return current_state & 1;
}

err_t stepper11_set_step_resolution ( stepper11_t *ctx, uint8_t step_res )
{
    err_t ret_val = STEPPER11_ERROR;
    if ( step_res <= STEPPER11_RESOLUTION_1div32 )
    {
        uint8_t temp_data = 0;
        stepper11_generic_read( ctx, STEPPER11_REG_OUTPUT_PORT, &temp_data );
        temp_data &= 0xF8;
        temp_data |= step_res;
        stepper11_generic_write( ctx, STEPPER11_REG_OUTPUT_PORT, temp_data );
        ret_val = STEPPER11_OK;

        switch ( step_res )
        {
            case STEPPER11_RESOLUTION_FULL:
            {
                ctx->step_resolution = STEPPER11_RESOLUTION_VALUE_FULL;
                break;
            }
            case STEPPER11_RESOLUTION_HALF_A:
            case STEPPER11_RESOLUTION_HALF_B:
            {
                ctx->step_resolution = STEPPER11_RESOLUTION_VALUE_HALF;
                break;
            }
            case STEPPER11_RESOLUTION_QUARTER:
            {
                ctx->step_resolution = STEPPER11_RESOLUTION_VALUE_QUARTER;
                break;
            }
            case STEPPER11_RESOLUTION_1div8:
            {
                ctx->step_resolution = STEPPER11_RESOLUTION_VALUE_1div8;
                break;
            }
            case STEPPER11_RESOLUTION_1div16:
            {
                ctx->step_resolution = STEPPER11_RESOLUTION_VALUE_1div16;
                break;
            }
            case STEPPER11_RESOLUTION_1div32:
            {
                ctx->step_resolution = STEPPER11_RESOLUTION_VALUE_1div32;
                break;
            }
            default:
            {
                ctx->step_resolution = STEPPER11_DUMMY;
                break;
            }
        }
    }

    return ret_val;
}

err_t stepper11_set_torque ( stepper11_t *ctx, uint8_t torque )
{
    err_t ret_val = STEPPER11_ERROR;
    if ( torque <= STEPPER11_TORQUE_30 )
    {
        uint8_t temp_data = 0;
        stepper11_generic_read( ctx, STEPPER11_REG_OUTPUT_PORT, &temp_data );
        temp_data &= 0xE7;
        temp_data |= torque << 3;
        stepper11_generic_write( ctx, STEPPER11_REG_OUTPUT_PORT, temp_data );
        ret_val = STEPPER11_OK;
    }

    return ret_val;
}

void stepper11_move_motor_angle ( stepper11_t *ctx, float degree, uint8_t speed )
{    
    ctx->resolution = STEPPER11_FULL_CIRCLE / ctx->steps;
    uint16_t steps_to_move = ( uint16_t )( degree / ctx->resolution );
    
    steps_to_move *= ctx->step_resolution;
    
    for ( uint16_t step_cnt = 0; step_cnt < steps_to_move; step_cnt++ )
    {
        digital_out_low( &ctx->clk );
        stepper11_speed_delay( speed );
        digital_out_high( &ctx->clk );
        stepper11_speed_delay( speed );
    }
}

void stepper11_move_motor_step ( stepper11_t *ctx, uint16_t steps, uint8_t speed )
{
    uint16_t steps_to_move = ctx->step_resolution * steps;
    
    for ( uint16_t step_cnt = 0; step_cnt < steps_to_move; step_cnt++ )
    {
        digital_out_low( &ctx->clk );
        stepper11_speed_delay( speed );
        digital_out_high( &ctx->clk );
        stepper11_speed_delay( speed );
    }
}

static void stepper11_speed_delay( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER11_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER11_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER11_SPEED_FAST:
        {
            Delay_1ms( );
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
