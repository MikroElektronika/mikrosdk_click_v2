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
 * @file stepdown8.c
 * @brief Step Down 8 Click Driver.
 */

#include "stepdown8.h"

void stepdown8_cfg_setup ( stepdown8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->sps = HAL_PIN_NC;
    cfg->pg  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPDOWN8_ADDR_A2A1A0_000;
}

err_t stepdown8_init ( stepdown8_t *ctx, stepdown8_cfg_t *cfg ) 
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
    digital_out_init( &ctx->sps, cfg->sps );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t stepdown8_default_cfg ( stepdown8_t *ctx ) 
{
    err_t error_flag = STEPDOWN8_OK;
    
    stepdown8_set_en_pin( ctx, STEPDOWN8_PIN_STATE_HIGH );
    stepdown8_set_sps_pin( ctx, STEPDOWN8_PIN_STATE_LOW );
    
    error_flag = stepdown8_set_output( ctx, STEPDOWN8_MIN_OUTPUT );

    return error_flag;
}

void stepdown8_set_en_pin ( stepdown8_t *ctx, uint8_t pin_state )
{
    if ( STEPDOWN8_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

void stepdown8_set_sps_pin ( stepdown8_t *ctx, uint8_t pin_state )
{
    if ( STEPDOWN8_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->sps );
    }
    else
    {
        digital_out_low( &ctx->sps );
    }
}

uint8_t stepdown8_get_pg_state ( stepdown8_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

err_t stepdown8_set_wiper_pos ( stepdown8_t *ctx, uint16_t wiper_pos )
{
    uint8_t data_buf[ 2 ] = { ( uint8_t ) ( ( wiper_pos >> 8 ) & 0x01 ), ( uint8_t ) ( wiper_pos & 0xFF ) };
    data_buf[ 0 ] |= STEPDOWN8_R1_RPROG_ADDRESS;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepdown8_set_r2_resistance ( stepdown8_t *ctx, uint32_t resistance )
{
    uint16_t resistance_val;
    
    if ( ( STEPDOWN8_DIGIPOT_MAX_VALUE < resistance ) || ( STEPDOWN8_R10_VALUE > resistance ) )
    {
        return STEPDOWN8_ERROR;
    }
    
    resistance_val = ( uint16_t ) ( ( ( float  ) ( resistance - STEPDOWN8_R10_VALUE ) / STEPDOWN8_DIGIPOT_MAX_VALUE ) * 
    STEPDOWN8_DIGIPOT_RESOLUTION + STEPDOWN8_ROUND_TO_NEAREST_INT );
    
    return stepdown8_set_wiper_pos( ctx, resistance_val );
}

err_t stepdown8_set_output ( stepdown8_t *ctx, float voltage )
{
    err_t error_flag = STEPDOWN8_OK;
    uint32_t res_val = 0;
    
    if ( ( STEPDOWN8_MIN_OUTPUT > voltage ) || ( STEPDOWN8_MAX_OUTPUT < voltage ) )
    {
        return STEPDOWN8_ERROR;
    }
    
    res_val = ( uint32_t ) ( ( float ) STEPDOWN8_R1_VALUE / ( voltage - 1 ) );
    
    return stepdown8_set_r2_resistance( ctx, res_val );
}

// ------------------------------------------------------------------------- END
