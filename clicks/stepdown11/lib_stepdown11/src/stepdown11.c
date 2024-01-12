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
 * @file stepdown11.c
 * @brief Step Down 11 Click Driver.
 */

#include "stepdown11.h"

void stepdown11_cfg_setup ( stepdown11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPDOWN11_DEVICE_ADDRESS_0;
}

err_t stepdown11_init ( stepdown11_t *ctx, stepdown11_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );

    digital_out_high( &ctx->rst );
    
    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t stepdown11_default_cfg ( stepdown11_t *ctx ) 
{
    err_t error_flag = STEPDOWN11_OK;
    
    stepdown11_reset_digi_pot( ctx );
    stepdown11_set_en_pin( ctx, STEPDOWN11_ENABLE_OUTPUT );
    error_flag |= stepdown11_set_mode ( ctx, STEPDOWN11_S_CONF_1MHZ_SPREAD_OFF );
    error_flag |= stepdown11_set_voltage ( ctx, 1 );
    
    return error_flag;
}

err_t stepdown11_generic_write ( stepdown11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t stepdown11_generic_read ( stepdown11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void stepdown11_set_en_pin ( stepdown11_t *ctx, uint8_t pin_state )
{
    if ( STEPDOWN11_ENABLE_OUTPUT == pin_state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

uint8_t stepdown11_get_pg_pin ( stepdown11_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

void stepdown11_reset_digi_pot ( stepdown11_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_10ms( );
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
}

err_t stepdown11_write_data ( stepdown11_t *ctx, uint8_t ctrl, uint8_t addr, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = STEPDOWN11_ERROR;
    data_buf[ 0 ] = ctrl | addr;
    data_buf[ 1 ] = data_in;
    
    err_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    
    return err_flag;
}

err_t stepdown11_read_data ( stepdown11_t *ctx, uint8_t addr, uint8_t mask, uint8_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = STEPDOWN11_ERROR;
    
    data_buf[ 0 ] = STEPDOWN11_CTRL_BIT_READ | addr;
    data_buf[ 1 ] = mask;
    
    err_flag = i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, 1 );
    
    return err_flag;
}

err_t stepdown11_write_rdac ( stepdown11_t *ctx, uint8_t addr, uint8_t data_in ) 
{
    return stepdown11_write_data( ctx, STEPDOWN11_CTRL_BIT_WRITE_RDAC, addr, data_in );
}

err_t stepdown11_read_rdac ( stepdown11_t *ctx, uint8_t addr, uint8_t *data_out ) 
{   
    return stepdown11_read_data( ctx, addr, STEPDOWN11_ADDR_BIT_READ_RDAC, data_out );;
}

err_t stepdown11_set_resistance ( stepdown11_t *ctx, uint8_t wiper_sel, float res_kohm ) 
{
    err_t err_flag = STEPDOWN11_OK;
    if ( res_kohm > STEPDOWN11_RES_10_KOHM )
    {
         err_flag = STEPDOWN11_ERROR;  
    }
    else
    {
        float wiper_pos = ( float ) res_kohm;
        wiper_pos *= ( float ) STEPDOWN11_WIPER_POS_MAX;
        wiper_pos /= ( float ) STEPDOWN11_RES_10_KOHM;
        err_flag |= stepdown11_write_rdac( ctx, wiper_sel, ( uint8_t ) wiper_pos ); 
    }
    return err_flag;
}

err_t stepdown11_get_resistance ( stepdown11_t *ctx, uint8_t wiper_sel, float *res_kohm ) 
{
    err_t err_flag = STEPDOWN11_OK;
    uint8_t data_buf = 0; 
  
    err_flag |= stepdown11_read_rdac( ctx, wiper_sel, &data_buf );
    *res_kohm = ( float ) STEPDOWN11_RES_10_KOHM;
    *res_kohm /= ( float ) STEPDOWN11_WIPER_POS_MAX;
    *res_kohm *= ( float ) data_buf;
    
    return err_flag;
}

err_t stepdown11_set_voltage ( stepdown11_t *ctx, float v_out )
{
    err_t error_flag = STEPDOWN11_OK;
    float resistance = 0;
    
    resistance = ( float ) ( ( STEPDOWN11_R_5_RESISTANCE / ( v_out / STEPDOWN11_VFB_VALUE - 1 ) ) - STEPDOWN11_R_9_RESISTANCE );
    
    if ( resistance > STEPDOWN11_RES_10_KOHM )
    {
        resistance = STEPDOWN11_RES_10_KOHM;
    }
    
    error_flag |= stepdown11_set_resistance( ctx, STEPDOWN11_WIPER_SEL_1, resistance );
    
    return error_flag;
}

err_t stepdown11_set_mode ( stepdown11_t *ctx, float sconf_mode )
{
    if ( STEPDOWN11_S_CONF_2_2MHZ_SPREAD_RANDOM < sconf_mode )
    {
        return STEPDOWN11_ERROR;
    }
    return stepdown11_set_resistance( ctx, STEPDOWN11_WIPER_SEL_2, sconf_mode );
}

// ------------------------------------------------------------------------- END
