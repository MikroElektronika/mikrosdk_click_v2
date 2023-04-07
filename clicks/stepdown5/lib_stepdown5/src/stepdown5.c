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
 * @file stepdown5.c
 * @brief Step Down 5 Click Driver.
 */

#include "stepdown5.h"

void stepdown5_cfg_setup ( stepdown5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->md = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPDOWN5_ADDR_A2A1A0_000;
}

err_t stepdown5_init ( stepdown5_t *ctx, stepdown5_cfg_t *cfg ) 
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

    digital_out_init( &ctx->md, cfg->md );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t stepdown5_default_cfg ( stepdown5_t *ctx ) 
{
    err_t error_flag = STEPDOWN5_OK;

    stepdown5_set_mode( ctx, STEPDOWN5_FORCED_PWM_MODE );
    error_flag |= stepdown5_set_output( ctx, STEPDOWN5_OUTPUT_0V6 );

    return error_flag;
}

err_t stepdown5_generic_write ( stepdown5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t stepdown5_generic_read ( stepdown5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void stepdown5_set_mode ( stepdown5_t *ctx, uint8_t mode )
{
    if ( STEPDOWN5_PFM_PWM_MODE == mode)
    {
       digital_out_low( &ctx->md ); 
    }
    else
    {
        digital_out_high( &ctx->md ); 
    }
}

uint8_t stepdown5_get_pg_state ( stepdown5_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

err_t stepdown5_set_wiper_0_pos ( stepdown5_t *ctx, uint16_t wiper_0_pos )
{
    uint8_t data_buf[ 2 ] = { ( uint8_t ) ( ( wiper_0_pos >> 8 ) & 0x01 ), ( uint8_t ) ( wiper_0_pos & 0xFF ) };
    data_buf[ 0 ] |= STEPDOWN5_R1_RPROG_ADDRESS;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepdown5_set_wiper_1_pos ( stepdown5_t *ctx, uint16_t wiper_1_pos )
{
    uint8_t data_buf[ 2 ] = { ( uint8_t ) ( ( wiper_1_pos >> 8 ) & 0x01 ) , ( uint8_t ) ( wiper_1_pos & 0xFF ) };
    data_buf[ 0 ] |= STEPDOWN5_R2_RPROG_ADDRESS;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepdown5_set_r1_resistance ( stepdown5_t *ctx, uint32_t resistance )
{
    uint16_t resistance_val;
    
    if ( resistance > STEPDOWN5_DIGIPOT_MAX_VALUE )
    {
        return STEPDOWN5_ERROR;
    }
    
    resistance_val = ( uint16_t ) ( ( ( float  ) resistance / STEPDOWN5_DIGIPOT_MAX_VALUE ) * STEPDOWN5_DIGIPOT_RESOLUTION + STEPDOWN5_ROUND_TO_NEAREST_INT );
    
    return stepdown5_set_wiper_0_pos( ctx, resistance_val );
}

err_t stepdown5_set_r2_resistance ( stepdown5_t *ctx, uint32_t resistance )
{
    uint16_t resistance_val;
    
     if ( resistance > STEPDOWN5_DIGIPOT_MAX_VALUE )
    {
        return STEPDOWN5_ERROR;
    }
    
    resistance_val = ( uint16_t ) ( ( ( float  ) resistance / STEPDOWN5_DIGIPOT_MAX_VALUE ) * STEPDOWN5_DIGIPOT_RESOLUTION + STEPDOWN5_ROUND_TO_NEAREST_INT );
    
    return stepdown5_set_wiper_1_pos( ctx, resistance_val );
}

err_t stepdown5_set_output ( stepdown5_t *ctx, uint8_t voltage )
{
    err_t error_flag = STEPDOWN5_OK;
    
    switch ( voltage )
    {
        case ( STEPDOWN5_OUTPUT_0V6 ):
        {
            error_flag |= stepdown5_set_r1_resistance( ctx, 1000 );
            error_flag |= stepdown5_set_r2_resistance( ctx, 100000 );
            break;
        }
        case ( STEPDOWN5_OUTPUT_1V5 ):
        {
            error_flag |= stepdown5_set_r1_resistance( ctx, 100000 );
            error_flag |= stepdown5_set_r2_resistance( ctx, 66667 );
            break;
        }
        case ( STEPDOWN5_OUTPUT_2V5 ):
        {
            error_flag |= stepdown5_set_r1_resistance( ctx, 100000 );
            error_flag |= stepdown5_set_r2_resistance( ctx, 31579 );
            break;
        }
        case ( STEPDOWN5_OUTPUT_3V3 ):
        {
            error_flag |= stepdown5_set_r1_resistance( ctx, 100000 );
            error_flag |= stepdown5_set_r2_resistance( ctx, 22222 );
            break;
        }
        case ( STEPDOWN5_OUTPUT_5V ):
        {
            error_flag |= stepdown5_set_r1_resistance( ctx, 100000 );
            error_flag |= stepdown5_set_r2_resistance( ctx, 13636 );
            break;
        }
        default:
        {
            error_flag = STEPDOWN5_ERROR;
        }
    }
    
    return error_flag;
}


// ------------------------------------------------------------------------- END
