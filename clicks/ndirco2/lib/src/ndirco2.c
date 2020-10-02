/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "ndirco2.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t ndirco2_get_bytes_num ( uint8_t reg_address );
static void ndirco2_only_read ( ndirco2_t *ctx, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ndirco2_cfg_setup ( ndirco2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->bsy = HAL_PIN_NC;
    cfg->cal   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x68;
}

NDIRCO2_RETVAL ndirco2_init ( ndirco2_t *ctx, ndirco2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return NDIRCO2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->bsy, cfg->bsy );
    digital_in_init( &ctx->cal, cfg->cal );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return NDIRCO2_OK;
}

void ndirco2_generic_write ( ndirco2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void ndirco2_generic_read ( ndirco2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t ndirco2_read_register ( ndirco2_t *ctx, uint8_t register_address, uint16_t *data_out )
{
    uint8_t buff_data [ 2 ] = { 0 };
    uint8_t n_bytes;
    uint16_t ret_val = 0;
    
    if ( register_address > 0x10 )
    {    
        return 1;
    }

    n_bytes = ndirco2_get_bytes_num( register_address );
    ndirco2_generic_read( ctx, register_address, buff_data, n_bytes );
    ret_val = buff_data[ 1 ];
    ret_val <<= 8;
    ret_val |= buff_data[ 0 ];
    *data_out = ret_val;
    return 0;
}

uint8_t ndirco2_write_register ( ndirco2_t *ctx, uint8_t register_address, uint8_t transfer_data )
{
    if ( register_address > 0x10 )
    {
        return 1;
    }
    ndirco2_generic_write( ctx, register_address, &transfer_data, 1 );
    Delay_10ms( );
    return 0;
}

void ndirco2_read_current_address ( ndirco2_t *ctx, uint8_t *data_out, uint8_t n_bytes )
{
    ndirco2_only_read( ctx, data_out, n_bytes );
}

void ndirco2_read_co2 ( ndirco2_t *ctx, uint8_t set_check_mode, uint16_t *output_data )
{
    if ( !set_check_mode )
    {
        while ( ndirco2_check_busy( ctx ) );
        ndirco2_read_register( ctx, NDIRCO2_DATA_LOW_REG, output_data );
    }
    else
    {
        while ( !ndirco2_check_average_complete( ctx ) );
        ndirco2_read_register ( ctx, NDIRCO2_DATA_LOW_REG, output_data );
        ndirco2_set_mode( ctx, 0 );
        ndirco2_set_mode( ctx, 1 );
    }
}

uint8_t ndirco2_check_busy ( ndirco2_t *ctx )
{
    if ( digital_in_read( &ctx->bsy ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }  
}

uint8_t ndirco2_check_average_complete ( ndirco2_t *ctx )
{
    uint16_t avr_cnt;
    
    ndirco2_read_register( ctx, NDIRCO2_STATUS_REG, &avr_cnt );
    if ( avr_cnt & 0x10 )
    {
        return 1;
    }
    else
    {
        return 0;
    }        
}

void ndirco2_set_mode ( ndirco2_t *ctx, uint8_t select_mode )
{
    uint16_t temp;
    
    ndirco2_read_register( ctx, NDIRCO2_CONTROL_REG, &temp );
    if ( !select_mode )
    {
        temp &= 0x04;
    }
    else
    {
        temp &= 0x04;
        temp |= 0x02;
    }
    ndirco2_write_register( ctx, NDIRCO2_CONTROL_REG, temp );
}

void ndirco2_reset ( ndirco2_t *ctx )
{
    uint16_t temp = 1;

    ndirco2_write_register( ctx, NDIRCO2_SOFTWARE_RESET_REG, temp );
    Delay_100ms( );
    ndirco2_read_register( ctx, 0x00, &temp );
    while ( temp )
    {
        ndirco2_read_register( ctx, NDIRCO2_SOFTWARE_RESET_REG, &temp );
    }
}

uint8_t ndirco2_check_alarm( ndirco2_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }   
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t ndirco2_get_bytes_num ( uint8_t reg_address )
{
    uint8_t num_bytes;

    if ( reg_address == NDIRCO2_DATA_LOW_REG )
    {
        num_bytes = 2;
    }
    else
    {
        num_bytes = 1;
    }
    return num_bytes;
}

static void ndirco2_only_read ( ndirco2_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_read( &ctx->i2c, data_buf, len );
}
// ------------------------------------------------------------------------- END

