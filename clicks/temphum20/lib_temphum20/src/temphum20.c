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
 * @file temphum20.c
 * @brief TempHum 20 Click Driver.
 */

#include "temphum20.h"

void temphum20_cfg_setup ( temphum20_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->alh  = HAL_PIN_NC;
    cfg->all  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM20_SET_DEV_ADDR;
}

err_t temphum20_init ( temphum20_t *ctx, temphum20_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alh, cfg->alh );
    digital_in_init( &ctx->all, cfg->all );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    digital_out_init( &ctx->en, cfg->en );

    return I2C_MASTER_SUCCESS;
}

err_t temphum20_default_cfg ( temphum20_t *ctx ) 
{
    temphum20_reset_device ( ctx );
    return temphum20_set_operating_mode ( ctx, TEMPHUM20_OPMODE_NORMAL );
}

err_t temphum20_write_data ( temphum20_t *ctx, uint8_t *tx_buf, uint8_t tx_len ) 
{
    return i2c_master_write( &ctx->i2c, tx_buf, tx_len );
}

err_t temphum20_read_data ( temphum20_t *ctx, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_read( &ctx->i2c, rx_buf, rx_len );
}

void temphum20_set_en_pin ( temphum20_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en, state );
}

uint8_t temphum20_get_int_pin ( temphum20_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

uint8_t temphum20_get_alarm_high_pin ( temphum20_t *ctx )
{
    return digital_in_read ( &ctx->alh );
}

uint8_t temphum20_get_alarm_low_pin ( temphum20_t *ctx )
{
    return digital_in_read ( &ctx->all );
}

void temphum20_reset_device ( temphum20_t *ctx )
{
    temphum20_set_en_pin ( ctx, 0 );
    Delay_100ms ( );
    temphum20_set_en_pin ( ctx, 1 );
    Delay_1ms ( );
}

err_t temphum20_write_command ( temphum20_t *ctx, uint8_t cmd_byte, uint16_t cmd_data ) 
{
    uint8_t data_buf[ 3 ] = { 0 };

    data_buf[ 0 ] = cmd_byte;
    data_buf[ 1 ] = ( uint8_t ) ( ( cmd_data >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( cmd_data & 0xFF );

    return temphum20_write_data( ctx, data_buf, 3 );
}

err_t temphum20_get_measurement ( temphum20_t *ctx, float *temp, float *hum ) 
{
    uint8_t rx_buf[ 4 ] = { 0 };
    
    while ( !temphum20_get_int_pin ( ctx ) );
    
    err_t error_flag = temphum20_read_data( ctx, rx_buf, 4 );
        
    if ( ( TEMPHUM20_OK == error_flag ) && 
         ( TEMPHUM20_STATUS_VALID_DATA == ( rx_buf[ 0 ] & TEMPHUM20_STATUS_BITS_MASK ) ) )
    {
        *hum = ( ( float ) ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] ) / 
                             TEMPHUM20_DATA_RESOLUTION ) * TEMPHUM20_HUM_MULTIPLIER;
        *temp = ( ( float ) ( ( ( uint16_t ) rx_buf[ 2 ] << 6 ) | ( ( rx_buf[ 3 ] >> 2 ) & 0x3F ) ) / 
                             TEMPHUM20_DATA_RESOLUTION ) * TEMPHUM20_TEMP_MULTIPLIER - TEMPHUM20_TEMP_OFFSET;
        return TEMPHUM20_OK;
    }
    return TEMPHUM20_ERROR;
}

err_t temphum20_set_operating_mode ( temphum20_t *ctx, uint8_t op_mode ) 
{
    if ( TEMPHUM20_OPMODE_NORMAL == op_mode )
    {
        return temphum20_write_command ( ctx, TEMPHUM20_CMD_START_NOM, TEMPHUM20_DUMMY );
    }
    else if ( TEMPHUM20_OPMODE_COMMAND == op_mode )
    {
        temphum20_reset_device ( ctx );
        return temphum20_write_command ( ctx, TEMPHUM20_CMD_START_CM, TEMPHUM20_DUMMY );
    }
    return TEMPHUM20_ERROR;
}

// ------------------------------------------------------------------------- END
