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
 * @file nanopower3.c
 * @brief Nano Power 3 Click Driver.
 */

#include "nanopower3.h"

void nanopower3_cfg_setup ( nanopower3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an  = HAL_PIN_NC;
    cfg->ctr = HAL_PIN_NC;
    cfg->pg  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NANOPOWER3_DEVICE_ADDRESS_GND;
}

err_t nanopower3_init ( nanopower3_t *ctx, nanopower3_cfg_t *cfg ) 
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

    digital_out_init( &ctx->ctr, cfg->ctr );

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t nanopower3_default_cfg ( nanopower3_t *ctx ) 
{
    err_t error_flag = NANOPOWER3_OK;
    
    nanopower3_set_ctr_pin( ctx, NANOPOWER3_PIN_STATE_HIGH );
    
    error_flag = nanopower3_set_voltage( ctx, NANOPOWER3_1V_OUT_VOLTAGE );
    
    return error_flag;
}

err_t nanopower3_generic_write ( nanopower3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t nanopower3_generic_read ( nanopower3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t nanopower3_get_pg_pin_state ( nanopower3_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

uint8_t nanopower3_get_an_pin_state ( nanopower3_t *ctx )
{
    return digital_in_read( &ctx->an );
}

void nanopower3_set_ctr_pin ( nanopower3_t *ctx, uint8_t pin_state )
{
    if( NANOPOWER3_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->ctr );
    }
    else
    {
        digital_out_low( &ctx->ctr );
    }
}

err_t nanopower3_write_data ( nanopower3_t *ctx, uint8_t cmd, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = data_in;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t nanopower3_set_wiper_pos ( nanopower3_t *ctx, uint8_t wiper_pos )
{
    return nanopower3_write_data( ctx, NANOPOWER3_CMD_VREG, wiper_pos );
}

err_t nanopower3_set_resistance ( nanopower3_t *ctx, uint32_t resistance )
{
    uint8_t wiper_pos = 0;
    if ( ( NANOPOWER3_MAX_RESISTANCE < resistance ) || ( resistance < NANOPOWER3_R11_RESISTANCE ) )
    {
        return NANOPOWER3_ERROR;
    }
    
    wiper_pos = ( uint8_t ) NANOPOWER3_DIGIPOT_MAX_VAL - ( ( 
                ( float ) ( resistance - NANOPOWER3_R11_RESISTANCE ) / NANOPOWER3_DIGIPOT_MAX_RESISTANCE ) * 
                NANOPOWER3_DIGIPOT_MAX_VAL + NANOPOWER3_ROUND_TO_NEAREST_INT );
    
    return nanopower3_set_wiper_pos( ctx, wiper_pos );
}

err_t nanopower3_set_voltage ( nanopower3_t *ctx, uint8_t out_vol )
{
    err_t error_flag = NANOPOWER3_OK;
    
    switch ( out_vol )
    {
        case NANOPOWER3_1V_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_1V_RESISTANCE );
            break;
        }
        case NANOPOWER3_1V2_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_1V2_RESISTANCE );
            break;
        }
        case NANOPOWER3_1V5_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_1V5_RESISTANCE );
            break;
        }
        case NANOPOWER3_1V8_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_1V8_RESISTANCE );
            break;
        }
        case NANOPOWER3_2V_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_2V_RESISTANCE );
            break;
        }
        case NANOPOWER3_2V5_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_2V5_RESISTANCE );
            break;
        }
        case NANOPOWER3_3V_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_3V_RESISTANCE );
            break;
        }
        case NANOPOWER3_3V3_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_3V3_RESISTANCE );
            break;
        }
        case NANOPOWER3_3V5_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_3V5_RESISTANCE );
            break;
        }
        case NANOPOWER3_4V_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_4V_RESISTANCE );
            break;
        }
        case NANOPOWER3_4V5_OUT_VOLTAGE:
        {
            error_flag |= nanopower3_set_resistance( ctx, NANOPOWER3_4V5_RESISTANCE );
            break;
        }
        default:
        {
            error_flag = NANOPOWER3_ERROR;
        }
    }
    
    return error_flag;
}


// ------------------------------------------------------------------------- END
