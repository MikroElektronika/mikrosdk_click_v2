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

#include "lightranger3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lightranger3_cfg_setup ( lightranger3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x4C;

    cfg->dev_confidence_value = 0;
    cfg->dev_distance = 0;
}

LIGHTRANGER3_RETVAL lightranger3_init ( lightranger3_t *ctx, lightranger3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LIGHTRANGER3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LIGHTRANGER3_OK;
}

void lightranger3_generic_write ( lightranger3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void lightranger3_generic_read ( lightranger3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void lightranger3_write_byte ( lightranger3_t *ctx, uint8_t reg, uint8_t w_data )
{
    lightranger3_generic_write( ctx, reg, &w_data, 1 );
}

void lightranger3_write_data ( lightranger3_t *ctx, uint8_t reg, uint16_t w_data )
{
    uint8_t write_reg[ 2 ];

    write_reg[ 0 ] = w_data & 0x00FF; 
    write_reg[ 1 ] = ( w_data & 0xFF00 ) >> 8; 

    lightranger3_generic_write( ctx, reg, write_reg, 2 );
}

uint8_t lightranger3_read_byte ( lightranger3_t *ctx, uint8_t reg )
{
    uint8_t read_data;
    
    lightranger3_generic_read( ctx, reg, &read_data, 1 );
    
    return read_data;
}

uint16_t lightranger3_read_data ( lightranger3_t *ctx, uint8_t reg )
{
    uint8_t read_reg[ 2 ];
    uint16_t value;
    
    lightranger3_generic_read( ctx, reg, read_reg, 2 );

    value = read_reg[ 1 ];
    value = value << 8;
    value = value | read_reg[ 0 ];
    
    return value;
}

uint8_t lightranger3_set_standby_mode ( lightranger3_t *ctx )
{
   uint8_t x;

   lightranger3_write_byte( ctx, LIGHTRANGER3_REG_CMD, LIGHTRANGER3_STANDBY_MODE );

   for ( x = 0; x < 10; x++ )
   {
       if ( ( lightranger3_read_data( ctx, LIGHTRANGER3_REG_DEV_STATUS ) & 0x001F ) == 0x0000 )
       {
           return LIGHTRANGER3_OK;
       }
       Delay_10us( );
   }
   return LIGHTRANGER3_ERROR;
}

uint8_t lightranger3_set_off_mode ( lightranger3_t *ctx )
{
    uint8_t x;

    lightranger3_write_byte( ctx, LIGHTRANGER3_REG_CMD, LIGHTRANGER3_OFF_MODE );
    for ( x = 0 ; x < 10 ; x++)
    {
        if ( ( lightranger3_read_data( ctx, LIGHTRANGER3_REG_DEV_STATUS ) & 0x001F ) == 0x0010 )
        {
            return LIGHTRANGER3_OK;
        }
        Delay_10us( );
    }
    return LIGHTRANGER3_ERROR;
}

uint8_t lightranger3_set_on_mode ( lightranger3_t *ctx )
{
    uint8_t x;

    lightranger3_write_byte( ctx, LIGHTRANGER3_REG_CMD, LIGHTRANGER3_ON_MODE );
    for ( x = 0 ; x < 10 ; x++)
    {
        if ( ( lightranger3_read_data( ctx, LIGHTRANGER3_REG_DEV_STATUS ) & 0x001F ) == 0x0018 )
        {
            return LIGHTRANGER3_OK;
        }
        Delay_10us( );
    }
    return LIGHTRANGER3_ERROR;
}

uint8_t lightranger3_set_measurement_mode ( lightranger3_t *ctx )
{
    uint8_t x;

    lightranger3_write_byte( ctx, LIGHTRANGER3_REG_CMD, LIGHTRANGER3_MEASUREMENT_MODE );
    for ( x = 0 ; x < 10 ; x++)
    {
        if ( ( lightranger3_read_data( ctx, LIGHTRANGER3_REG_ICSR ) & ( 1 << 4 ) ) != 0 )
        {
            return LIGHTRANGER3_OK;
        }
        Delay_10us( );
    }
    return LIGHTRANGER3_ERROR;
}

uint8_t lightranger3_take_single_measurement ( lightranger3_t *ctx )
{
    uint16_t read_value;
    uint8_t error_code;
    uint16_t confidence_register;
    uint8_t measurement_mode;

    measurement_mode = lightranger3_set_measurement_mode( ctx );
    
    if ( measurement_mode == 1)
    {
        return LIGHTRANGER3_ERROR;
    }

    read_value = lightranger3_read_data( ctx, LIGHTRANGER3_REG_RESULT );

    if ( read_value & DISTANCE_IS_GOOD )
    {
        error_code = ( read_value >> 13 ) & 0x03;
        if ( error_code == 0 )
        {
            ctx->distance = ( read_value >> 2 ) & 0x07FF;
            
            confidence_register = lightranger3_read_data( ctx, LIGHTRANGER3_REG_RESULT_CONFIG );
            ctx->confidence_value = ( confidence_register >> 4 ) & 0x07FF;
        }
        return ( error_code );
    }
    else
    {
        return LIGHTRANGER3_ERROR;
    }
}

uint16_t lightranger3_get_distance ( lightranger3_t *ctx )
{
    return ctx->distance;
}

uint16_t lightranger3_get_confidence_value ( lightranger3_t *ctx )
{
  return ctx->confidence_value;
}

uint16_t lightranger3_get_device_id ( lightranger3_t *ctx )
{
    return lightranger3_read_data( ctx, LIGHTRANGER3_REG_DEVICE_ID );
}

void lightranger3_soft_reset ( lightranger3_t *ctx )
{
    lightranger3_write_byte( ctx, LIGHTRANGER3_REG_CMD, 0x40 );
    Delay_100ms( );
}

uint8_t lightranger3_get_interrupt ( lightranger3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t lightranger3_device_init ( lightranger3_t *ctx )
{
    uint8_t settings;
    uint16_t device_id;
    uint8_t stand_mode;
    uint8_t set_off_mode;
    uint8_t set_on_mode;

    device_id = lightranger3_get_device_id( ctx );
    
    if ( device_id != 0xAD02 && device_id != 0xAD01 )
    {
        return LIGHTRANGER3_ERROR;
    }

    stand_mode = lightranger3_set_standby_mode( ctx );

    if ( stand_mode == 1)
    { 
        return LIGHTRANGER3_ERROR;
    }
    
    lightranger3_write_data( ctx, LIGHTRANGER3_REG_ICSR, 0x05 );
    lightranger3_write_data( ctx, LIGHTRANGER3_REG_IER, 0x01 );

    lightranger3_write_data( ctx, LIGHTRANGER3_REG_I2C_INIT_CFG, 0x65 );
    lightranger3_write_data( ctx, LIGHTRANGER3_REG_PMU_CONFIG, 0x0500 );

    set_off_mode = lightranger3_set_off_mode( ctx );

    if ( set_off_mode == 1)
    {
        return LIGHTRANGER3_ERROR;
    }
    
    lightranger3_write_data( ctx, LIGHTRANGER3_REG_PMU_CONFIG, 0x0600) ;

    set_on_mode = lightranger3_set_on_mode( ctx );

    if ( set_on_mode == 1)
    {
        return LIGHTRANGER3_ERROR;
    }

    lightranger3_write_data( ctx, LIGHTRANGER3_REG_CMD_CONFIG_A,   0xE100 );
    lightranger3_write_data( ctx, LIGHTRANGER3_REG_CMD_CONFIG_B,   0x10FF );
    lightranger3_write_data( ctx, LIGHTRANGER3_REG_HW_FW_CONFIG_0, 0x07D0 );
    lightranger3_write_data( ctx, LIGHTRANGER3_REG_HW_FW_CONFIG_1, 0x5008 );
    lightranger3_write_data( ctx, LIGHTRANGER3_REG_HW_FW_CONFIG_2, 0xA041 );
    lightranger3_write_data( ctx, LIGHTRANGER3_REG_HW_FW_CONFIG_3, 0x45D4 );

    return LIGHTRANGER3_OK;
}

// ------------------------------------------------------------------------- END

