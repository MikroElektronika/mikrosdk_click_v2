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
 * @file expand15.c
 * @brief Expand 15 Click Driver.
 */

#include "expand15.h"

void expand15_cfg_setup ( expand15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND15_DEVICE_ADDRESS_GND;
}

err_t expand15_init ( expand15_t *ctx, expand15_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );

    return I2C_MASTER_SUCCESS;
}

err_t expand15_default_cfg ( expand15_t *ctx ) 
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data;
    
    expand15_hw_reset( ctx );
    
    error_flag |= expand15_set_out_port_config ( ctx, EXPAND15_PORT_PUSH_PULL, EXPAND15_PORT_PUSH_PULL );
    
    tmp_data = EXPAND15_PIN_01_MASK | EXPAND15_PIN_03_MASK | EXPAND15_PIN_05_MASK | EXPAND15_PIN_07_MASK;
    error_flag |= expand15_set_pin_as_in( ctx, EXPAND15_PORT_0, tmp_data );
    
    tmp_data = EXPAND15_PIN_00_MASK | EXPAND15_PIN_02_MASK | EXPAND15_PIN_04_MASK | EXPAND15_PIN_06_MASK;
    error_flag |= expand15_set_pin_as_out( ctx, EXPAND15_PORT_0, tmp_data );
    
    error_flag |= expand15_set_out_pin_state( ctx, EXPAND15_PORT_0 , EXPAND15_ALL_PINS_OFF );
    
    tmp_data = EXPAND15_PIN_10_MASK | EXPAND15_PIN_12_MASK | EXPAND15_PIN_14_MASK | EXPAND15_PIN_16_MASK;
    error_flag |= expand15_set_pin_as_out( ctx, EXPAND15_PORT_1, tmp_data );
    
    tmp_data = EXPAND15_PIN_11_MASK | EXPAND15_PIN_13_MASK | EXPAND15_PIN_15_MASK | EXPAND15_PIN_17_MASK;
    error_flag |= expand15_set_pin_as_in( ctx, EXPAND15_PORT_1, tmp_data );
    
    error_flag |= expand15_set_out_pin_state( ctx, EXPAND15_PORT_1 , EXPAND15_ALL_PINS_OFF );
    
    return error_flag;
}

err_t expand15_generic_write ( expand15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t expand15_generic_read ( expand15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t expand15_get_int_pin_state ( expand15_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void expand15_hw_reset ( expand15_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

err_t expand15_get_in_pin_state ( expand15_t *ctx, uint8_t port, uint8_t *pin_state )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= expand15_generic_read( ctx, EXPAND15_REG_INPUT_PORT_0, tmp_data, 2 );
    
    if ( EXPAND15_PORT_0 == port )
    {
        *pin_state = tmp_data[ 0 ];
    }
    else
    {
        *pin_state = tmp_data[ 1 ];
    }
    
    return error_flag;
}

err_t expand15_get_out_pin_state ( expand15_t *ctx, uint8_t port, uint8_t *pin_state )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= expand15_generic_read( ctx, EXPAND15_REG_OUTPUT_PORT_0, tmp_data, 2 );
    
    if ( EXPAND15_PORT_0 == port )
    {
        *pin_state = tmp_data[ 0 ];
    }
    else
    {
        *pin_state = tmp_data[ 1 ];
    }
    
    return error_flag;
}

err_t expand15_set_out_pin_state ( expand15_t *ctx, uint8_t port, uint8_t pin_state )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    if ( EXPAND15_PORT_0 == port )
    {
        tmp_data[ 0 ] = pin_state;
    }
    else
    {
        tmp_data[ 1 ] = pin_state;
    }
    error_flag |= expand15_generic_write( ctx, EXPAND15_REG_OUTPUT_PORT_0, tmp_data, 2 );
    
    return error_flag;
}

err_t expand15_get_in_pin_polarity ( expand15_t *ctx, uint8_t port, uint8_t *pin_polarity )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= expand15_generic_read( ctx, EXPAND15_REG_POLARITY_INVERSION_0, tmp_data, 2 );
    
    if ( EXPAND15_PORT_0 == port )
    {
        *pin_polarity = tmp_data[ 0 ];
    }
    else
    {
        *pin_polarity = tmp_data[ 1 ];
    }
    
    return error_flag;
}

err_t expand15_set_in_pin_polarity ( expand15_t *ctx, uint8_t port, uint8_t pin_polarity )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= expand15_generic_read( ctx, EXPAND15_REG_POLARITY_INVERSION_0, tmp_data, 2 );
    
    if ( EXPAND15_PORT_0 == port )
    {
        tmp_data[ 0 ] = pin_polarity;
    }
    else
    {
        tmp_data[ 1 ] = pin_polarity;
    }
    
    error_flag |= expand15_generic_write( ctx, EXPAND15_REG_POLARITY_INVERSION_0, tmp_data, 2 );
    
    return error_flag;
}

err_t expand15_get_pin_config ( expand15_t *ctx, uint8_t port, uint8_t *pin_config )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= expand15_generic_read( ctx, EXPAND15_REG_CONFIGURATION_0, tmp_data, 2 );
    
    if ( EXPAND15_PORT_0 == port )
    {
        *pin_config = tmp_data[ 0 ];
    }
    else
    {
        *pin_config = tmp_data[ 1 ];
    }
    
    return error_flag;
}

err_t expand15_set_pin_as_in ( expand15_t *ctx, uint8_t port, uint8_t pin_config )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
     error_flag |= expand15_generic_read( ctx, EXPAND15_REG_CONFIGURATION_0, tmp_data, 2 );
    
    if ( EXPAND15_PORT_0 == port )
    {
        tmp_data[ 0 ] |= pin_config;
    }
    else
    {
        tmp_data[ 1 ] |= pin_config;
    }
    
    error_flag |= expand15_generic_write( ctx, EXPAND15_REG_CONFIGURATION_0, tmp_data, 2 );
    
    return error_flag;
}

err_t expand15_set_pin_as_out ( expand15_t *ctx, uint8_t port, uint8_t pin_config )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= expand15_generic_read( ctx, EXPAND15_REG_CONFIGURATION_0, tmp_data, 2 );
    
    if ( EXPAND15_PORT_0 == port )
    {
        tmp_data[ 0 ] &= ~pin_config;
    }
    else
    {
        tmp_data[ 1 ] &= ~pin_config;
    }
    
    error_flag |= expand15_generic_write( ctx, EXPAND15_REG_CONFIGURATION_0, tmp_data, 2 );
    
    return error_flag;
}

err_t expand15_get_out_level ( expand15_t *ctx, uint8_t port, uint16_t *pin_output_level )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_buf[ 2 ];
    
    if ( EXPAND15_PORT_0 == port )
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_OUTPUT_DRV_STRENGTH_0_0, tmp_buf, 2 );
        *pin_output_level = ( ( ( uint16_t ) tmp_buf[ 0 ] ) << 8 ) | tmp_buf[ 1 ];
    }
    else
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_OUTPUT_DRV_STRENGTH_1_0, tmp_buf, 2 );
        *pin_output_level = ( ( ( uint16_t ) tmp_buf[ 0 ] ) << 8 ) | tmp_buf[ 1 ];
    }
    
    return error_flag;
}

err_t expand15_set_out_level ( expand15_t *ctx, uint8_t port, uint16_t pin_output_level )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_buf[ 2 ];
    
    if ( EXPAND15_PORT_0 == port )
    {
        tmp_buf[ 0 ] = ( uint8_t ) ( pin_output_level >> 8 );
        tmp_buf[ 1 ] = ( uint8_t ) pin_output_level;
        error_flag |= expand15_generic_write( ctx, EXPAND15_REG_OUTPUT_DRV_STRENGTH_0_0, tmp_buf, 2 );
    }
    else
    {
        tmp_buf[ 0 ] = ( uint8_t ) ( pin_output_level >> 8 );
        tmp_buf[ 1 ] = ( uint8_t ) pin_output_level;
        error_flag |= expand15_generic_write( ctx, EXPAND15_REG_OUTPUT_DRV_STRENGTH_1_0, &tmp_buf, 2 );
    }
    
    return error_flag;
}

err_t expand15_set_out_pin_strength( expand15_t *ctx, uint8_t port, uint8_t pin, uint8_t strength )
{
    err_t error_flag = EXPAND15_OK;
    uint16_t tmp_data;
    
    error_flag |= expand15_get_out_level( ctx, port, &tmp_data );
    
    switch ( pin )
    {
        case( EXPAND15_PIN_00_MASK ):
        {
            tmp_data &= ~( ( uint16_t ) EXPAND15_OUTPUT_STRENGTH_FULL );
            tmp_data |= strength;
            break;
        }
        case( EXPAND15_PIN_01_MASK ):
        {
            tmp_data &= ~( ( uint16_t ) EXPAND15_OUTPUT_STRENGTH_FULL ) << 2;
            tmp_data |= strength << 2;
            break;
        }
        case( EXPAND15_PIN_02_MASK ):
        {
            tmp_data &= ~( ( uint16_t ) EXPAND15_OUTPUT_STRENGTH_FULL ) << 4;
            tmp_data |= strength << 4;
            break;
        }
        case( EXPAND15_PIN_03_MASK ):
        {
            tmp_data &= ~( ( uint16_t ) EXPAND15_OUTPUT_STRENGTH_FULL ) << 6;
            tmp_data |= strength << 6;
            break;
        }
        case( EXPAND15_PIN_04_MASK ):
        {
            tmp_data &= ~( ( uint16_t ) EXPAND15_OUTPUT_STRENGTH_FULL ) << 8;
            tmp_data |= strength << 8;
            break;
        }
        case( EXPAND15_PIN_05_MASK ):
        {
            tmp_data &= ~( ( uint16_t ) EXPAND15_OUTPUT_STRENGTH_FULL ) << 10;
            tmp_data |= strength << 10;
            break;
        }
        case( EXPAND15_PIN_06_MASK ):
        {
            tmp_data &= ~( ( uint16_t ) EXPAND15_OUTPUT_STRENGTH_FULL ) << 12;
            tmp_data |= strength << 12;
            break;
        }
        case( EXPAND15_PIN_07_MASK ):
        {
            tmp_data &= ~( ( uint16_t ) EXPAND15_OUTPUT_STRENGTH_FULL ) << 14;
            tmp_data |= strength << 14;
            break;
        }
        default:
        {
            return EXPAND15_ERROR;
        }
    }
    
    error_flag |= expand15_set_out_level( ctx, port, tmp_data );
    
    return error_flag;
}

err_t expand15_set_en_pull_up_down ( expand15_t *ctx, uint8_t port, uint8_t port_config )
{
    err_t error_flag = EXPAND15_OK;
    
    if ( EXPAND15_PORT_0 == port )
    {
        error_flag |= expand15_generic_write( ctx, EXPAND15_REG_PULL_UP_DOWN_EN_0, &port_config, 1 );
    }
    else
    {
        error_flag |= expand15_generic_write( ctx, EXPAND15_REG_PULL_UP_DOWN_EN_1, &port_config, 1 );
    }
    
    return error_flag;
}

err_t expand15_get_en_pull_up_down ( expand15_t *ctx, uint8_t port, uint8_t *port_config )
{
    err_t error_flag = EXPAND15_OK;
    
    if ( EXPAND15_PORT_0 == port )
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_PULL_UP_DOWN_EN_0, port_config, 1 );
    }
    else
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_PULL_UP_DOWN_EN_0, port_config, 1 );
    }
    
    return error_flag;
}

err_t expand15_set_pull_up_down ( expand15_t *ctx, uint8_t port, uint8_t pin_config )
{
    err_t error_flag = EXPAND15_OK;
    
    if ( EXPAND15_PORT_0 == port )
    {
        error_flag |= expand15_generic_write( ctx, EXPAND15_REG_PULL_UP_DOWN_SELECT_0, &pin_config, 1 );
    }
    else
    {
        error_flag |= expand15_generic_write( ctx, EXPAND15_REG_PULL_UP_DOWN_SELECT_1, &pin_config, 1 );
    }
    
    return error_flag;
}

err_t expand15_get_pull_up_down ( expand15_t *ctx, uint8_t port, uint8_t *pin_config )
{
    err_t error_flag = EXPAND15_OK;
    
    if ( EXPAND15_PORT_0 == port )
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_PULL_UP_DOWN_SELECT_0, pin_config, 1 );
    }
    else
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_PULL_UP_DOWN_SELECT_0, pin_config, 1 );
    }
    
    return error_flag;
}

err_t expand15_set_int_mask ( expand15_t *ctx, uint8_t port, uint8_t int_config )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t int_cfg_val;
    int_cfg_val = ~int_config; 
    
    if ( EXPAND15_PORT_0 == port )
    {
        error_flag |= expand15_generic_write( ctx, EXPAND15_REG_INTERRUPT_MASK_0, &int_cfg_val, 1 );
    }
    else
    {
        error_flag |= expand15_generic_write( ctx, EXPAND15_REG_INTERRUPT_MASK_1, &int_cfg_val, 1 );
    }
    
    return error_flag;
}

err_t expand15_get_int_mask ( expand15_t *ctx, uint8_t port, uint8_t *int_config )
{
    err_t error_flag = EXPAND15_OK;
    
    if ( EXPAND15_PORT_0 == port )
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_INTERRUPT_MASK_0, int_config, 1 );
    }
    else
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_INTERRUPT_MASK_1, int_config, 1 );
    }
    
    return error_flag;
}

err_t expand15_get_int_status ( expand15_t *ctx, uint8_t port, uint8_t *int_status )
{
    err_t error_flag = EXPAND15_OK;
    
    if ( EXPAND15_PORT_0 == port )
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_INTERRUPT_STATUS_0, int_status, 1 );
    }
    else
    {
        error_flag |= expand15_generic_read( ctx, EXPAND15_REG_INTERRUPT_STATUS_1, int_status, 1 );
    }
    
    return error_flag;
}

err_t expand15_get_out_port_config ( expand15_t *ctx, uint8_t *port0_cfg, uint8_t *port1_cfg )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data = 0;
    
    error_flag |= expand15_generic_read( ctx, EXPAND15_REG_OUTPUT_PORT_CFG, &tmp_data, 1 );
    
    *port0_cfg = tmp_data & EXPAND15_PORT_OPEN_DRAIN;
    *port0_cfg = ( tmp_data >> 1 ) & EXPAND15_PORT_OPEN_DRAIN;
    
    return error_flag;
}

err_t expand15_set_out_port_config ( expand15_t *ctx, uint8_t port0_cfg, uint8_t port1_cfg )
{
    err_t error_flag = EXPAND15_OK;
    uint8_t tmp_data = 0;
    tmp_data = port0_cfg | ( port1_cfg << 1 );
    
    error_flag |= expand15_generic_write( ctx, EXPAND15_REG_OUTPUT_PORT_CFG, &tmp_data, 1 );
    
    return error_flag;
}


// ------------------------------------------------------------------------- END
