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
 * @file i2c1wire2.c
 * @brief I2C 1-Wire 2 Click Driver.
 */

#include "i2c1wire2.h"

void i2c1wire2_cfg_setup ( i2c1wire2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = I2C1WIRE2_DEVICE_ADDRESS;
}

err_t i2c1wire2_init ( i2c1wire2_t *ctx, i2c1wire2_cfg_t *cfg ) 
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

err_t i2c1wire2_default_cfg ( i2c1wire2_t *ctx ) 
{
    err_t error_flag = I2C1WIRE2_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= i2c1wire2_master_reset( ctx );
    Delay_10ms( );
    tmp_data[ 0 ] = I2C1WIRE2_CUSTOM_VAL;
    tmp_data[ 1 ] = I2C1WIRE2_VTH_OFF | I2C1WIRE2_VIAPO_OFF | I2C1WIRE2_RWPU_EXT;
    i2c1wire2_write_port_cfg ( ctx, I2C1WIRE2_REG_PRUP_BUFF, tmp_data );

    return error_flag;
}

err_t i2c1wire2_generic_write ( i2c1wire2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t i2c1wire2_generic_read ( i2c1wire2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t i2c1wire2_master_reset ( i2c1wire2_t *ctx )
{
    err_t error_flag = I2C1WIRE2_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    uint8_t cmd_data = I2C1WIRE2_CMD_MASTER_RESET;

    error_flag |= i2c_master_write( &ctx->i2c, &cmd_data, 1 );
    Delay_10ms();
    error_flag |= i2c_master_read( &ctx->i2c, tmp_data, 2 );

    if ( I2C1WIRE2_RESULT_BYTE_OK != tmp_data[ 1 ] )
    {
        error_flag |= I2C1WIRE2_ERROR;
    }

    return error_flag;
}

err_t i2c1wire2_read_port_cfg ( i2c1wire2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = I2C1WIRE2_OK;
    uint8_t data_buf[ 42 ] = { 0 };
    uint8_t tmp_data[ 3 ] = { 0 };
    uint8_t rx_len;

    if ( reg > I2C1WIRE2_REG_PDSLEW )
    {
        rx_len = 42;
    }
    else
    {
        rx_len = 4;
    }

    tmp_data[ 0 ] = I2C1WIRE2_CMD_READ_1WIRE_PORT_CFG;
    tmp_data[ 1 ] = 1;
    tmp_data[ 2 ] = reg;

    error_flag |= i2c_master_write( &ctx->i2c, tmp_data, 3 );
    Delay_10ms();
    i2c_master_read( &ctx->i2c, data_buf, rx_len );

    if ( I2C1WIRE2_RESULT_BYTE_OK != tmp_data[ 1 ] )
    {
        error_flag |= I2C1WIRE2_ERROR;
    }

    return error_flag;
}

err_t i2c1wire2_write_port_cfg ( i2c1wire2_t *ctx, uint8_t reg, uint8_t *data_in )
{
    err_t error_flag = I2C1WIRE2_OK;
    uint8_t tmp_data[ 5 ] = { 0 };
    tmp_data[ 0 ] = I2C1WIRE2_CMD_WRITE_1WIRE_PORT_CFG;
    tmp_data[ 1 ] = 3;
    tmp_data[ 2 ] = reg;
    tmp_data[ 3 ] = data_in[ 0 ];
    tmp_data[ 4 ] = data_in[ 1 ];

    error_flag |= i2c_master_write( &ctx->i2c, tmp_data, 5 );
    Delay_10ms();
    error_flag |= i2c_master_read( &ctx->i2c, tmp_data, 2 );

    if ( I2C1WIRE2_RESULT_BYTE_OK != tmp_data[ 1 ] )
    {
        error_flag |= I2C1WIRE2_ERROR;
    }

    return error_flag;
}

err_t i2c1wire2_write_script_cmd ( i2c1wire2_t *ctx, uint8_t *param_data, uint8_t param_len, uint8_t *response, uint8_t response_len )
{
    err_t error_flag = I2C1WIRE2_OK;
    uint8_t tx_data_buf[ 256 ] = { 0 };
    uint8_t rx_data_buf[ 256 ] = { 0 };

    tx_data_buf[ 0 ] = I2C1WIRE2_CMD_1WIRE_SCRIPT;
    tx_data_buf[ 1 ] = param_len;
    for ( uint8_t n_cnt = 0; n_cnt < param_len; n_cnt++ )
    {
        tx_data_buf[ n_cnt + 2 ] = param_data[ n_cnt ];
    }

    error_flag |= i2c_master_write( &ctx->i2c, tx_data_buf, param_len + 2 );
    Delay_10ms();
    error_flag |= i2c_master_read( &ctx->i2c, rx_data_buf, response_len + 2 );

    if ( I2C1WIRE2_RESULT_BYTE_OK != rx_data_buf[ 1 ] )
    {
        error_flag |= I2C1WIRE2_ERROR;
    }

    for ( uint8_t n_cnt = 0; n_cnt < param_len; n_cnt++ )
    {
        response[ n_cnt ] = rx_data_buf[ n_cnt + 2 ];
    }

    return error_flag;
}

err_t i2c1wire2_search ( i2c1wire2_t *ctx, uint8_t *flag, uint8_t *rom_id, uint8_t *last_flag, uint8_t param_data, uint8_t command_code )
{
    err_t error_flag = I2C1WIRE2_OK;
    uint8_t tx_data_buf[ 4 ] = { 0 };
    uint8_t rx_data_buf[ 11 ] = { 0 };

    tx_data_buf[ 0 ] = I2C1WIRE2_CMD_1WIRE_SEARCH;
    tx_data_buf[ 1 ] = 2;
    tx_data_buf[ 2 ] = param_data;
    tx_data_buf[ 3 ] = command_code;

    error_flag |= i2c_master_write( &ctx->i2c, tx_data_buf, 4 );
    Delay_100ms();
    error_flag |= i2c_master_read( &ctx->i2c, rx_data_buf, 11 );

    switch ( rx_data_buf [ 1 ] )
    {
        case I2C1WIRE2_RESULT_BYTE_OK:
        {
            for ( uint8_t n_cnt = 0; n_cnt < 8; n_cnt++ )
            {
                rom_id[ n_cnt ] = rx_data_buf [ 2 + n_cnt ];
            }
            *last_flag = rx_data_buf[ 10 ];
            *flag = I2C1WIRE2_RESULT_BYTE_OK;
            break;
        }
        case I2C1WIRE2_NO_PRESENCE_PULS:
        {
            error_flag = I2C1WIRE2_OK;
            *flag = I2C1WIRE2_NO_PRESENCE_PULS;
            break;
        }
        case I2C1WIRE2_NO_DEVICE_DETECTED:
        {
            error_flag = I2C1WIRE2_OK;
            *flag = I2C1WIRE2_NO_DEVICE_DETECTED;
            break;
        }
        case I2C1WIRE2_RESULT_BYTE_ERROR_INVALID_PARAMS:
        {
            error_flag = I2C1WIRE2_ERROR;
            *flag = I2C1WIRE2_RESULT_BYTE_ERROR_INVALID_PARAMS;
            break;
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
