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
 * @file stepdown7.c
 * @brief Step Down 7 Click Driver.
 */

#include "stepdown7.h"

void stepdown7_cfg_setup ( stepdown7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->md = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPDOWN7_ADDR_A2A1A0_000;
}

err_t stepdown7_init ( stepdown7_t *ctx, stepdown7_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en , cfg->en  );
    digital_out_init( &ctx->md, cfg->md );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t stepdown7_default_cfg ( stepdown7_t *ctx ) 
{
    err_t error_flag = STEPDOWN7_OK;
    
    stepdown7_set_en( ctx, STEPDOWN7_PIN_STATE_HIGH );
    stepdown7_set_mode( ctx, STEPDOWN7_PFM_PWM_MODE );
    error_flag = stepdown7_set_output( ctx, STEPDOWN7_OUTPUT_1V5 );
    
    return error_flag;
}

err_t stepdown7_generic_write ( stepdown7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t stepdown7_generic_read ( stepdown7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void stepdown7_set_mode ( stepdown7_t *ctx, uint8_t mode )
{
    if ( STEPDOWN7_PFM_PWM_MODE == mode)
    {
       digital_out_low( &ctx->md ); 
    }
    else
    {
        digital_out_high( &ctx->md ); 
    }
}

void stepdown7_set_en ( stepdown7_t *ctx, uint8_t en_state )
{
    if ( STEPDOWN7_PIN_STATE_HIGH == en_state )
    {
       digital_out_high( &ctx->en ); 
    }
    else
    {
        digital_out_low( &ctx->en ); 
    }
}

uint8_t stepdown7_get_pg_state ( stepdown7_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

err_t stepdown7_set_wiper_pos ( stepdown7_t *ctx, uint16_t wiper_pos )
{
    uint8_t data_buf[ 2 ] = { ( uint8_t ) ( ( wiper_pos >> 8 ) & 0x01 ), ( uint8_t ) ( wiper_pos & 0xFF ) };
    data_buf[ 0 ] |= STEPDOWN7_R1_RPROG_ADDRESS;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepdown7_set_r1_resistance ( stepdown7_t *ctx, uint32_t resistance )
{
    uint16_t resistance_val;
    
    if ( ( STEPDOWN7_DIGIPOT_MAX_VALUE < resistance ) || ( STEPDOWN7_R8_VALUE > resistance ) )
    {
        return STEPDOWN7_ERROR;
    }
    
    resistance_val = ( uint16_t ) ( ( ( float  ) ( resistance - STEPDOWN7_R8_VALUE ) / STEPDOWN7_DIGIPOT_MAX_VALUE ) * 
    STEPDOWN7_DIGIPOT_RESOLUTION + STEPDOWN7_ROUND_TO_NEAREST_INT );
    
    return stepdown7_set_wiper_pos( ctx, resistance_val );
}

err_t stepdown7_set_output ( stepdown7_t *ctx, uint8_t voltage )
{
    err_t error_flag = STEPDOWN7_OK;
    
    switch ( voltage )
    {
        case ( STEPDOWN7_OUTPUT_1V5 ):
        {
            error_flag |= stepdown7_set_r1_resistance( ctx, STEPDOWN7_1V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN7_OUTPUT_2V5 ):
        {
            error_flag |= stepdown7_set_r1_resistance( ctx, STEPDOWN7_2V5_RESISTANCE );
            break;
        }
        case ( STEPDOWN7_OUTPUT_3V3 ):
        {
            error_flag |= stepdown7_set_r1_resistance( ctx, STEPDOWN7_3V3_RESISTANCE );
            break;
        }
        default:
        {
            error_flag = STEPDOWN7_ERROR;
        }
    }
    
    return error_flag;
}



// ------------------------------------------------------------------------- END
