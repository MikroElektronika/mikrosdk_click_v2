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

#include "proximity10.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity10_cfg_setup ( proximity10_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXIMITY10_DEFAULT_DEV_ADDR;
}

PROXIMITY10_RETVAL proximity10_init ( proximity10_t *ctx, proximity10_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY10_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY10_OK;
}

void proximity10_default_cfg ( proximity10_t *ctx )
{
    uint8_t w_temp[ 2 ];

    w_temp[ 0 ] = PROXIMITY10_INT_AUTO_CLEAR | PROXIMITY10_INT_PIN_EN;
    proximity10_generic_write( ctx, PROXIMITY10_INT_CFG_REG, w_temp, 1 );

    w_temp[ 0 ] = PROXIMITY10_PS1_INT_EN;
    proximity10_generic_write( ctx, PROXIMITY10_IRQ_EN_REG, w_temp, 1 );

    w_temp[ 0 ] = PROXIMITY10_PS1_INT_MEAS_GREATER_TH | PROXIMITY10_CMD_INT_EN;
    proximity10_generic_write( ctx, PROXIMITY10_IRQ_MODE1_REG, w_temp, 1 );

    w_temp[ 0 ] = PROXIMITY10_CMD_INT_RESP_ERROR;
    proximity10_generic_write( ctx, PROXIMITY10_IRQ_MODE2_REG, w_temp, 1 );

    w_temp[ 0 ] = PROXIMITY10_DEV_WAKEUP_EVERY_10MS;
    proximity10_generic_write( ctx, PROXIMITY10_MEAS_RATE_REG, w_temp, 1 );

    w_temp[ 0 ] = PROXIMITY10_MEAS_AFTER_EVERY_WAKEUP;
    proximity10_generic_write( ctx, PROXIMITY10_ALS_RATE_REG, w_temp, 1 );

    w_temp[ 0 ] = PROXIMITY10_MEAS_AFTER_EVERY_WAKEUP;
    proximity10_generic_write( ctx, PROXIMITY10_PS_RATE_REG, w_temp, 1 );

    w_temp[ 0 ] = PROXIMITY10_LED_MAX_CURRENT;
    proximity10_generic_write( ctx, PROXIMITY10_PS_LED21_REG, w_temp, 1 );
    
    w_temp[ 0 ] = 0xDC;
    w_temp[ 1 ] = 0x05;
    proximity10_generic_write( ctx, PROXIMITY10_PS1_TH_REG, w_temp, 2 );
}

uint8_t proximity10_generic_write ( proximity10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    if ( reg > 0x3E )
    {
        return PROXIMITY10_INVALID_REG_ADDR;
    }

    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    } 

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );     

    return PROXIMITY10_OK;
}

uint8_t proximity10_generic_read ( proximity10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    if ( reg > 0x3E )
    {
        return PROXIMITY10_INVALID_REG_ADDR;
    }

    tx_buf [ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_buf, len );

    return PROXIMITY10_OK;
}

uint8_t proximity10_check_int_status ( proximity10_t *ctx, uint8_t bit_mask, uint8_t clear_en )
{
    uint8_t int_flag;
    uint8_t w_temp;

    w_temp = PROXIMITY10_CLEAR_INT_CMD;
    
    proximity10_generic_read( ctx, PROXIMITY10_IRQ_STATUS_REG, &int_flag, 1 );
    
    if ( clear_en )
    {
        proximity10_generic_write( ctx, PROXIMITY10_IRQ_STATUS_REG, &w_temp, 1 );
    }
    
    int_flag &= bit_mask;
    
    return int_flag;
}

uint8_t proximity10_check_chip_status ( proximity10_t *ctx, uint8_t bit_mask )
{
    uint8_t int_flag;
    
    proximity10_generic_read( ctx, PROXIMITY10_CHIP_STATUS_REG, &int_flag, 1 );
    
    int_flag &= bit_mask;
    
    return int_flag;
}

uint8_t proximity10_check_int_pin ( proximity10_t *ctx )
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

uint8_t proximity10_send_command ( proximity10_t *ctx, uint8_t prox_command )
{
    uint8_t resp_data;
    uint8_t w_temp;

    if ( ( prox_command > 0x0F ) || ( prox_command == 0x03 ) || ( prox_command == 0x04 ) || ( prox_command == 0x08 ) || ( prox_command == 0x0C ) )
    {
        return PROXIMITY10_INVALID_CMD;
    }
    
    proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &prox_command, 1 );
    Delay_10ms( );
    
    if ( prox_command == PROXIMITY10_BUSADDR_CMD )
    {
        return PROXIMITY10_OK;
    }
    else
    {
        proximity10_generic_read( ctx, PROXIMITY10_RESPONSE_REG, &resp_data, 1 );
    
        if ( resp_data & 0xF0 )
        {
            w_temp = PROXIMITY10_RESET_CMD;
            proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &w_temp, 1 );
            Delay_10ms( );
        
            return resp_data;
        }
        else
        {
            return PROXIMITY10_OK;
        }
    }
}

uint8_t proximity10_param_query ( proximity10_t *ctx, uint8_t param_addr )
{
    uint8_t resp_data;
    uint8_t w_temp;
    
    if ( param_addr > 0x1F )
    {
        return PROXIMITY10_INVALID_PARAM_ADDR;
    }


    w_temp = param_addr | PROXIMITY10_PARAM_QUERY_CMD;
    proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &w_temp, 1 );
    Delay_10ms( );
    
    proximity10_generic_read( ctx, PROXIMITY10_RESPONSE_REG, &resp_data, 1 );
    
    if ( resp_data & 0xF0 )
    {
        w_temp = PROXIMITY10_RESET_CMD;
        proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &w_temp, 1 );
        Delay_10ms( );
        
        return resp_data;
    }
    else
    {
        return PROXIMITY10_OK;
    }
}

uint8_t proximity10_param_set ( proximity10_t *ctx, uint8_t param_addr, uint8_t param_value )
{
    uint8_t resp_data;
    uint8_t w_temp;

    if ( param_addr > 0x1F )
    {
        return PROXIMITY10_INVALID_PARAM_ADDR;
    }

    proximity10_generic_write( ctx, PROXIMITY10_PARAM_WR_REG, &param_value, 1 );
    
    w_temp = param_addr | PROXIMITY10_PARAM_SET_CMD;
    proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &w_temp, 1 );
    Delay_10ms( );

    proximity10_generic_read( ctx, PROXIMITY10_RESPONSE_REG, &resp_data, 1 );

    if ( resp_data & 0xF0 )
    {
        w_temp = PROXIMITY10_RESET_CMD;
        proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &w_temp, 1 );
        Delay_10ms( );

        return resp_data;
    }
    else
    {
        return PROXIMITY10_OK;
    }
}

uint8_t proximity10_param_and ( proximity10_t *ctx, uint8_t param_addr, uint8_t param_value )
{
    uint8_t resp_data;
    uint8_t w_temp;

    if ( param_addr > 0x1F )
    {
        return PROXIMITY10_INVALID_PARAM_ADDR;
    }

    proximity10_generic_write( ctx, PROXIMITY10_PARAM_WR_REG, &param_value, 1 );
    
    w_temp = param_addr | PROXIMITY10_PARAM_AND_CMD;
    proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &w_temp, 1 );
    Delay_10ms( );

    proximity10_generic_read( ctx, PROXIMITY10_RESPONSE_REG, &resp_data, 1 );

    if ( resp_data & 0xF0 )
    {
        w_temp = PROXIMITY10_RESET_CMD;
        proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &w_temp , 1 );
        Delay_10ms( );

        return resp_data;
    }
    else
    {
        return PROXIMITY10_OK;
    }
}

uint8_t proximity10_param_or ( proximity10_t *ctx, uint8_t param_addr, uint8_t param_value )
{
    uint8_t resp_data;
    uint8_t w_temp;

    if ( param_addr > 0x1F )
    {
        return PROXIMITY10_INVALID_PARAM_ADDR;
    }

    proximity10_generic_write( ctx, PROXIMITY10_PARAM_WR_REG, &param_value, 1 );
    
    w_temp = param_addr | PROXIMITY10_PARAM_OR_CMD;
    proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &w_temp, 1 );
    Delay_10ms( );

    proximity10_generic_read( ctx, PROXIMITY10_RESPONSE_REG, &resp_data, 1 );

    if ( resp_data & 0xF0 )
    {
        w_temp = PROXIMITY10_RESET_CMD;
        proximity10_generic_write( ctx, PROXIMITY10_COMMAND_REG, &w_temp, 1 );
        Delay_10ms( );

        return resp_data;
    }
    else
    {
        return PROXIMITY10_OK;
    }
}

// ------------------------------------------------------------------------- END

