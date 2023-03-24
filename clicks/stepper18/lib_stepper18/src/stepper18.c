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
 * @file stepper18.c
 * @brief Stepper 18 Click Driver.
 */

#include "stepper18.h"

/**
 * @brief Driver macros for calculation.
 */
#define FULL_CIRCLE     360.0
#define RESOLUTION      4096.0
#define VREF            3330.0

/**
 * @brief Set delay for controling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper18_speed_delay( uint8_t speed_macro );

void stepper18_cfg_setup ( stepper18_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->dir   = HAL_PIN_NC;
    cfg->slp = HAL_PIN_NC;
    cfg->stp = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPPER18_SET_DEV_ADDR;
}

err_t stepper18_init ( stepper18_t *ctx, stepper18_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->slp, cfg->slp );
    digital_out_init( &ctx->stp, cfg->stp );
    
    digital_in_init( &ctx->flt, cfg->flt );

    ctx->steps = 0;
    ctx->resolution = 0.0;

    return I2C_MASTER_SUCCESS;
}

err_t stepper18_default_cfg ( stepper18_t *ctx ) 
{
    ctx->steps = 200;
    stepper18_calculate_resolution( ctx );
    stepper18_set_out_voltage( ctx, 1590 );
    stepper18_set_en( ctx, 1 );
    stepper18_set_slp( ctx, 1 );
    return STEPPER18_OK;
}

err_t stepper18_generic_write ( stepper18_t *ctx, uint8_t *tx_buf, uint8_t tx_len ) 
{
    return i2c_master_write( &ctx->i2c, tx_buf, tx_len );
}

err_t stepper18_set_out_voltage ( stepper18_t *ctx, uint16_t voltage )
{
    if ( voltage > VREF )
        return STEPPER18_ERROR;
    
    uint8_t write_buf[ 2 ] = { 0 };
    uint16_t output = voltage * RESOLUTION / VREF;

    write_buf[ 0 ] = ( uint8_t )( output >> 8 );
    write_buf[ 1 ] = ( uint8_t )( output );
    
    return stepper18_generic_write( ctx, write_buf, 2 );
}

void stepper18_set_dir ( stepper18_t *ctx, uint8_t value )
{
    if ( value )
    {
        digital_out_high( &ctx->dir );
    }
    else
    {
        digital_out_low( &ctx->dir );
    }
}

void stepper18_set_slp ( stepper18_t *ctx, uint8_t value )
{
    if ( value )
    {
        digital_out_high( &ctx->slp );
    }
    else
    {
        digital_out_low( &ctx->slp );
    }
}

void stepper18_set_en ( stepper18_t *ctx, uint8_t value )
{
    if ( value )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

void stepper18_set_stp ( stepper18_t *ctx, uint8_t value )
{
    if ( value )
    {
        digital_out_high( &ctx->stp );
    }
    else
    {
        digital_out_low( &ctx->stp );
    }
}

uint8_t stepper18_get_flt ( stepper18_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

void stepper18_move_motor_angle ( stepper18_t *ctx, float degree, uint8_t step_res, uint8_t speed )
{
    if ( 0 == ctx->resolution )
    {
        stepper18_calculate_resolution( ctx );
    }
    
    uint16_t steps_to_move = ( uint16_t )( degree / ctx->resolution );
    
    steps_to_move *= step_res;
    
    stepper18_set_en( ctx, 1 );
    for ( uint16_t step_cnt = 0; step_cnt < steps_to_move; step_cnt++ )
    {
        stepper18_set_stp( ctx, 1 );
        stepper18_speed_delay( speed );
        stepper18_set_stp( ctx, 0 );
        stepper18_speed_delay( speed );
    }
    stepper18_set_en( ctx, 0 );
}

void stepper18_move_motor_step ( stepper18_t *ctx, uint16_t steps, uint8_t step_res, uint8_t speed )
{
    if ( 0 == ctx->resolution )
    {
        stepper18_calculate_resolution( ctx );
    }
    
    uint16_t steps_to_move = step_res * steps;
    
    stepper18_set_en( ctx, 1 );
    for ( uint16_t step_cnt = 0; step_cnt < steps_to_move; step_cnt++ )
    {
        stepper18_set_stp( ctx, 1 );
        stepper18_speed_delay( speed );
        stepper18_set_stp( ctx, 0 );
        stepper18_speed_delay( speed );
    }
    stepper18_set_en( ctx, 0 );
}

void stepper18_calculate_resolution ( stepper18_t *ctx )
{
    ctx->resolution = FULL_CIRCLE / ctx->steps;
}

static void stepper18_speed_delay( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER18_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER18_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER18_SPEED_MEDIUM:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER18_SPEED_FAST:
        {
            Delay_500us();
            Delay_80us();
            Delay_80us();
            Delay_50us();
            break;
        }
        case STEPPER18_SPEED_VERY_FAST:
        {
            Delay_500us();
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
