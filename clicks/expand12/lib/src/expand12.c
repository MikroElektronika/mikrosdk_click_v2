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
 * @file expand12.c
 * @brief Expand 12 Click Driver.
 */

#include "expand12.h"

void expand12_cfg_setup ( expand12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND12_SET_DEV_ADDR_A1A0_11;
}

err_t expand12_init ( expand12_t *ctx, expand12_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t expand12_default_cfg ( expand12_t *ctx ) 
{
    err_t error_flag = EXPAND12_OK;
    
    error_flag |= expand12_set_operating_mode ( ctx, EXPAND12_OPMODE_NORMAL );
    
    error_flag |= expand12_set_port_direction( ctx, EXPAND12_PORT_4_7, EXPAND12_DIR_OUTPUT );
    
    error_flag |= expand12_set_port_direction( ctx, EXPAND12_PORT_8_15, EXPAND12_DIR_OUTPUT );
    
    error_flag |= expand12_set_port_direction( ctx, EXPAND12_PORT_16_23, EXPAND12_DIR_OUTPUT );
    
    error_flag |= expand12_set_port_direction( ctx, EXPAND12_PORT_24_31, EXPAND12_DIR_INPUT_WITH_PULLUP );
    
    error_flag |= expand12_set_all_pins_value( ctx, EXPAND12_PIN_LOW_LEVEL );
    
    return error_flag;
}

err_t expand12_generic_write ( expand12_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t expand12_generic_read ( expand12_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t expand12_write_register ( expand12_t *ctx, uint8_t reg, uint8_t data_in )
{
    return expand12_generic_write ( ctx, reg, &data_in, 1 );
}

err_t expand12_read_register ( expand12_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return expand12_generic_read ( ctx, reg, data_out, 1 );
}

err_t expand12_set_operating_mode ( expand12_t *ctx, uint8_t state )
{
    if ( EXPAND12_OPMODE_SHUTDOWN == state )
    {
        return expand12_write_register ( ctx, EXPAND12_REG_CONFIG, EXPAND12_OPMODE_SHUTDOWN );
    }
    else if ( EXPAND12_OPMODE_NORMAL == state )
    {
        return expand12_write_register ( ctx, EXPAND12_REG_CONFIG, EXPAND12_OPMODE_NORMAL );
    }
    return EXPAND12_ERROR;
}

err_t expand12_set_pin_direction ( expand12_t *ctx, uint8_t pin, uint8_t direction )
{
    if ( ( direction > EXPAND12_DIR_INPUT_WITH_PULLUP ) || 
         ( direction < EXPAND12_DIR_OUTPUT ) ||
         ( ( pin > EXPAND12_PIN_31 ) && ( EXPAND12_ALL_PINS != pin ) ) )
    {
        return EXPAND12_ERROR;
    }
    
    if ( EXPAND12_ALL_PINS == pin )
    {
        return expand12_set_all_pins_direction ( ctx, direction );
    }
    uint8_t port_config = 0;
    uint8_t port_reg = EXPAND12_REG_CONFIG_P7_4 + ( pin / 4 );
    
    err_t error_flag = expand12_read_register ( ctx, port_reg, &port_config );
    port_config &= ~( EXPAND12_DIR_INPUT_WITH_PULLUP << ( ( pin % 4 ) * 2 ) );
    port_config |= ( direction << ( ( pin % 4 ) * 2 ) );
    error_flag |= expand12_write_register ( ctx, port_reg, port_config );
    return error_flag;
}

err_t expand12_set_port_direction ( expand12_t *ctx, uint8_t port, uint8_t direction )
{
    if ( ( direction > EXPAND12_DIR_INPUT_WITH_PULLUP ) || 
         ( direction < EXPAND12_DIR_OUTPUT ) ||
         ( port > EXPAND12_PORT_24_31 ) )
    {
        return EXPAND12_ERROR;
    }
    
    uint8_t port_config = direction;
    port_config |= ( direction << 2 );
    port_config |= ( direction << 4 );
    port_config |= ( direction << 6 );
    
    if ( EXPAND12_PORT_4_7 == port )
    {
        return expand12_write_register ( ctx, EXPAND12_REG_CONFIG_P7_4, port_config );
    }
    uint8_t port_reg = EXPAND12_REG_CONFIG_P11_8 + ( ( port - 1 ) * 2 );
    err_t error_flag = expand12_write_register ( ctx, port_reg, port_config );
    error_flag |= expand12_write_register ( ctx, port_reg + 1, port_config );
    return error_flag;
}

err_t expand12_set_all_pins_direction ( expand12_t *ctx, uint8_t direction )
{
    if ( ( direction > EXPAND12_DIR_INPUT_WITH_PULLUP ) || ( direction < EXPAND12_DIR_OUTPUT ) )
    {
        return EXPAND12_ERROR;
    }
    
    err_t error_flag = expand12_set_port_direction ( ctx, EXPAND12_PORT_4_7, direction );
    error_flag |= expand12_set_port_direction ( ctx, EXPAND12_PORT_8_15, direction );
    error_flag |= expand12_set_port_direction ( ctx, EXPAND12_PORT_16_23, direction );
    error_flag |= expand12_set_port_direction ( ctx, EXPAND12_PORT_24_31, direction );
    return error_flag;
}

err_t expand12_set_pin_value ( expand12_t *ctx, uint8_t pin, uint8_t pin_value )
{
    if ( ( pin_value > EXPAND12_PIN_HIGH_LEVEL ) || 
         ( ( pin > EXPAND12_PIN_31 ) && ( EXPAND12_ALL_PINS != pin ) ) )
    {
        return EXPAND12_ERROR;
    }
    
    if ( EXPAND12_ALL_PINS == pin )
    {
        return expand12_set_all_pins_value ( ctx, pin_value );
    }
    return expand12_write_register ( ctx, EXPAND12_REG_P4 + pin, pin_value );
}

err_t expand12_set_port_value ( expand12_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask )
{
    if ( port > EXPAND12_PORT_24_31 )
    {
        return EXPAND12_ERROR;
    }
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    uint8_t port_reg = EXPAND12_REG_P4_7 + ( port * 8 );
    err_t error_flag = expand12_read_register ( ctx, port_reg, &rx_data );
    
    tx_data = ( rx_data & ~clr_mask ) | set_mask;
    
    if ( rx_data != tx_data )
    {
        if ( EXPAND12_REG_P4_7 == port_reg )
        {
            tx_data >>= 4;
        }
        error_flag |= expand12_write_register ( ctx, port_reg, tx_data );
    }
    return error_flag;
}

err_t expand12_set_all_pins_value ( expand12_t *ctx, uint8_t pin_value )
{
    if ( pin_value > EXPAND12_PIN_HIGH_LEVEL ) 
    {
        return EXPAND12_ERROR;
    }
    err_t error_flag = EXPAND12_OK;
    
    if ( EXPAND12_PIN_HIGH_LEVEL == pin_value )
    {
        error_flag |= expand12_write_register ( ctx, EXPAND12_REG_P4_7, EXPAND12_ALL_PINS );
        error_flag |= expand12_write_register ( ctx, EXPAND12_REG_P8_15, EXPAND12_ALL_PINS );
        error_flag |= expand12_write_register ( ctx, EXPAND12_REG_P16_23, EXPAND12_ALL_PINS );
        error_flag |= expand12_write_register ( ctx, EXPAND12_REG_P24_31, EXPAND12_ALL_PINS );
    }
    else
    {
        error_flag |= expand12_write_register ( ctx, EXPAND12_REG_P4_7, EXPAND12_NO_PINS );
        error_flag |= expand12_write_register ( ctx, EXPAND12_REG_P8_15, EXPAND12_NO_PINS );
        error_flag |= expand12_write_register ( ctx, EXPAND12_REG_P16_23, EXPAND12_NO_PINS );
        error_flag |= expand12_write_register ( ctx, EXPAND12_REG_P24_31, EXPAND12_NO_PINS );
    }
    return error_flag;
}

err_t expand12_read_pin_value ( expand12_t *ctx, uint8_t pin, uint8_t *pin_value )
{
    if ( pin > EXPAND12_PIN_31 )
    {
        return EXPAND12_ERROR;
    }
    err_t error_flag = expand12_read_register ( ctx, EXPAND12_REG_P4 + pin, pin_value );
    *pin_value &= EXPAND12_PIN_HIGH_LEVEL;
    return error_flag;
}

err_t expand12_read_port_value ( expand12_t *ctx, uint8_t port, uint8_t *port_value )
{
    if ( port > EXPAND12_PORT_24_31 )
    {
        return EXPAND12_ERROR;
    }
    return expand12_read_register ( ctx, EXPAND12_REG_P4_7 + ( port * 8 ), port_value );
}

err_t expand12_read_all_pins_value ( expand12_t *ctx, uint32_t *pins_value )
{
    uint8_t port_value = 0;
    err_t error_flag = expand12_read_port_value ( ctx, EXPAND12_PORT_24_31, &port_value );
    *pins_value = port_value;
    *pins_value <<= 8;
    error_flag |= expand12_read_port_value ( ctx, EXPAND12_PORT_16_23, &port_value );
    *pins_value |= port_value;
    *pins_value <<= 8;
    error_flag |= expand12_read_port_value ( ctx, EXPAND12_PORT_8_15, &port_value );
    *pins_value |= port_value;
    *pins_value <<= 8;
    error_flag |= expand12_read_port_value ( ctx, EXPAND12_PORT_4_7, &port_value );
    *pins_value |= port_value;
    return error_flag;
}

// ------------------------------------------------------------------------- END
