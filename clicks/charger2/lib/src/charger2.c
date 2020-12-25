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

#include "charger2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void charger2_cfg_setup ( charger2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x70;
}

CHARGER2_RETVAL charger2_init ( charger2_t *ctx, charger2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CHARGER2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    return CHARGER2_OK;
}

void charger2_generic_write ( charger2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void charger2_generic_read ( charger2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t charger2_write_reg ( charger2_t *ctx, uint8_t register_address, uint8_t transfer_data )
{
    uint8_t buffData[ 2 ];
    
    if ( ( ( register_address > 0x01 ) && ( register_address < 0x20 ) ) || ( register_address > 0x3F ) )
    {
        return 1;
    }
    
    charger2_generic_write( ctx, register_address, &transfer_data, 1 );

    return 0;
}

uint8_t charger2_read_reg ( charger2_t *ctx, uint8_t register_address, uint8_t *value_out, uint8_t n_bytes )
{
    uint8_t regAddr;
    
    if ( register_address > 0x3F )
    {
        return 1;
    }
        
    if ( n_bytes > 64 )
    {
        return 2;
    }

    regAddr = register_address;
    
    charger2_generic_read( ctx, register_address, value_out, n_bytes );

    return 0;
}

uint8_t charger2_read_data ( charger2_t *ctx, uint8_t data_mode, uint32_t *data_out )
{
    uint16_t temp;
    float lsb_data;
    uint8_t buff_data[ 2 ];
    
    switch ( data_mode )
    {
        case CHARGER2_GAS_GAUGE_CHARGE_DATA :
        {
            buff_data[ 0 ] = CHARGER2_REG_CHARGE_LOW;
            lsb_data = 6.70;
        break;
        }
        case CHARGER2_CONV_NUMBER :
        {
            buff_data[ 0 ] = CHARGER2_REG_COUNTER_LOW;
            lsb_data = 1.00;
        break;
        }
        case CHARGER2_SHUNT_VOLTAGE :
        {
            buff_data[ 0 ] = CHARGER2_REG_CURRENT_LOW;
            lsb_data = 11.77;
            charger2_check_conv_cycle( ctx, CHARGER2_CURRENT_CYCLE_CHECK );
        break;
        }
        case CHARGER2_BATTERY_VOLTAGE :
        {
            buff_data[ 0 ] = CHARGER2_REG_VOLTAGE_LOW;
            lsb_data = 2.44;
            charger2_check_conv_cycle( ctx, CHARGER2_VOLTAGE_TEMP_CYCLE_CHECK );
        break;
        }
        case CHARGER2_TEMPERATURE :
        {
            buff_data[ 0 ] = CHARGER2_REG_TEMPERATURE_LOW;
            lsb_data = 0.125;
            charger2_check_conv_cycle( ctx, CHARGER2_VOLTAGE_TEMP_CYCLE_CHECK );
        break;
        }
        case CHARGER2_BATTERY_CURRENT :
        {
            buff_data[ 0 ] = CHARGER2_REG_CURRENT_LOW;
            lsb_data = 11.77 / R_SHUNT;
            charger2_check_conv_cycle( ctx, CHARGER2_CURRENT_CYCLE_CHECK );
         break;
        }
        default :
        {
            return 1;
        }
    }
    ctx->unit_mode = data_mode;
    
    charger2_read_reg( ctx,  buff_data[ 0 ], buff_data, 2 );
    temp = buff_data[ 1 ];
    temp <<= 8;
    temp |= buff_data[ 0 ];
        
    *data_out = temp * lsb_data;
        
    return 0;
}

uint8_t charger2_reset ( charger2_t *ctx, uint8_t reset_mode )
{
    uint8_t tmp;

    if ( reset_mode == CHARGER2_RESET_COUNTER_MODE )
    {
        charger2_write_reg( ctx, CHARGER2_REG_CONTROL, CHARGER2_RESET_CHARGE_ACCUM_AND_COUNTER | CHARGER2_IO0_OUTPUT_OPEN );
        Delay_1sec( );
        
        return 0;
    }
    else if ( reset_mode == CHARGER2_SOFT_RESET_MODE )
    {
        charger2_write_reg( ctx, CHARGER2_REG_CONTROL, CHARGER2_ASSERT_SOFT_RESET | CHARGER2_IO0_OUTPUT_OPEN );
        Delay_1sec( );
        charger2_write_reg( ctx, CHARGER2_REG_CONTROL, CHARGER2_RELEASE_SOFT_RESET | CHARGER2_IO0_OUTPUT_OPEN );
        charger2_read_reg( ctx, CHARGER2_REG_CONTROL, &tmp, 1 );
        while ( ( tmp & 0x10 ) >> 4 )
        {
            charger2_read_reg( ctx, CHARGER2_REG_CONTROL, &tmp, 1 );    
        }
            
        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t charger2_check_conv_cycle( charger2_t *ctx, uint8_t conv_mode )
{
    uint8_t tmp;
    
    charger2_read_reg( ctx, CHARGER2_REG_CONTROL, &tmp, 1 );
    
    if ( conv_mode == CHARGER2_CURRENT_CYCLE_CHECK )
    {
        while ( !( (tmp & 0x04 ) >> 2 ) )
            charger2_read_reg( ctx, CHARGER2_REG_CONTROL, &tmp, 1 );
            
        return 0;
    }
    else if ( conv_mode == CHARGER2_VOLTAGE_TEMP_CYCLE_CHECK )
    {
        while ( !( ( tmp & 0x08 ) >> 3 ) )
        {
            charger2_read_reg( ctx, CHARGER2_REG_CONTROL, &tmp, 1 );
        }
            
        return 0;
    }
    else
    {
        return 1;
    }
}

// ------------------------------------------------------------------------- END

