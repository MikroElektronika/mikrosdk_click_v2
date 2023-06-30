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
 * @file temphum21.c
 * @brief TempHum 21 Click Driver.
 */

#include "temphum21.h"

void temphum21_cfg_setup ( temphum21_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->all = HAL_PIN_NC;
    cfg->alh = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM21_SET_DEV_ADDR;
}

err_t temphum21_init ( temphum21_t *ctx, temphum21_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );
    
    digital_in_init( &ctx->all, cfg->all );
    digital_in_init( &ctx->alh, cfg->alh );
    
    temphum21_enable_device ( ctx );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t temphum21_default_cfg ( temphum21_t *ctx ) 
{
    err_t error_flag = TEMPHUM21_OK;
    
    error_flag |= temphum21_enter_command_mode ( ctx );
    uint8_t status = 0;
    uint16_t eeprom_write = 0;
    uint16_t eeprom_read = 0;
    
    eeprom_write = TEMPHUM21_ALARM_HIGH_ON_80PCT;
    error_flag |= temphum21_eeprom_write ( ctx, TEMPHUM21_REG_ALARM_HIGH_ON, eeprom_write );
    error_flag |= temphum21_eeprom_read ( ctx, TEMPHUM21_REG_ALARM_HIGH_ON, &status, &eeprom_read );
    if ( ( eeprom_read != eeprom_write ) || 
         ( status != ( TEMPHUM21_STATUS_COMMAND_MODE | TEMPHUM21_RESPONSE_ACK ) ) )
    {
        error_flag |= TEMPHUM21_ERROR;
    }
    
    eeprom_write = TEMPHUM21_ALARM_HIGH_OFF_75PCT;
    error_flag |= temphum21_eeprom_write ( ctx, TEMPHUM21_REG_ALARM_HIGH_OFF, eeprom_write );
    error_flag |= temphum21_eeprom_read ( ctx, TEMPHUM21_REG_ALARM_HIGH_OFF, &status, &eeprom_read );
    if ( ( eeprom_read != eeprom_write ) || 
         ( status != ( TEMPHUM21_STATUS_COMMAND_MODE | TEMPHUM21_RESPONSE_ACK ) ) )
    {
        error_flag |= TEMPHUM21_ERROR;
    }
    
    eeprom_write = TEMPHUM21_ALARM_LOW_ON_20PCT;
    error_flag |= temphum21_eeprom_write ( ctx, TEMPHUM21_REG_ALARM_LOW_ON, eeprom_write );
    error_flag |= temphum21_eeprom_read ( ctx, TEMPHUM21_REG_ALARM_LOW_ON, &status, &eeprom_read );
    if ( ( eeprom_read != eeprom_write ) || 
         ( status != ( TEMPHUM21_STATUS_COMMAND_MODE | TEMPHUM21_RESPONSE_ACK ) ) )
    {
        error_flag |= TEMPHUM21_ERROR;
    }
    
    eeprom_write = TEMPHUM21_ALARM_LOW_OFF_25PCT;
    error_flag |= temphum21_eeprom_write ( ctx, TEMPHUM21_REG_ALARM_LOW_OFF, eeprom_write );
    error_flag |= temphum21_eeprom_read ( ctx, TEMPHUM21_REG_ALARM_LOW_OFF, &status, &eeprom_read );
    if ( ( eeprom_read != eeprom_write ) || 
         ( status != ( TEMPHUM21_STATUS_COMMAND_MODE | TEMPHUM21_RESPONSE_ACK ) ) )
    {
        error_flag |= TEMPHUM21_ERROR;
    }
    
    error_flag |= temphum21_exit_command_mode ( ctx );
    Delay_100ms ( );

    return error_flag;
}

err_t temphum21_request_measurement ( temphum21_t *ctx ) 
{
    uint8_t dummy = 0;
    return i2c_master_write( &ctx->i2c, &dummy, 1 );
}

err_t temphum21_read_measurement ( temphum21_t *ctx, float *temperature, float *humidity )
{
    uint8_t data_buf[ 4 ] = { 0 };
    uint16_t raw_data = 0;
    err_t error_flag = temphum21_request_measurement ( ctx );
    // The measurement cycle duration is typically 36.65ms for temperature and humidity readings.
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    error_flag |= i2c_master_read ( &ctx->i2c, data_buf, 4 );
    raw_data = ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) & TEMPHUM21_DATA_RES;
    *humidity = ( float ) raw_data / TEMPHUM21_DATA_RES * TEMPHUM21_HUM_RES;
    raw_data = ( ( ( uint16_t ) data_buf[ 2 ] << 6 ) | ( data_buf[ 3 ] >> 2 ) ) & TEMPHUM21_DATA_RES;
    *temperature = ( float ) raw_data / TEMPHUM21_DATA_RES * TEMPHUM21_TEMP_RES - TEMPHUM21_TEMP_OFFSET;
    if ( TEMPHUM21_OK == error_flag )
    {
        error_flag = data_buf[ 0 ] & TEMPHUM21_STATUS_BIT_MASK; // status bits
    }
    return error_flag; 
}

uint8_t temphum21_get_all_pin ( temphum21_t *ctx )
{
    return digital_in_read ( &ctx->all );
}

uint8_t temphum21_get_alh_pin ( temphum21_t *ctx )
{
    return digital_in_read ( &ctx->alh );
}

void temphum21_enable_device ( temphum21_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void temphum21_disable_device ( temphum21_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t temphum21_eeprom_read ( temphum21_t *ctx, uint8_t address, uint8_t *status, uint16_t *data_out )
{
    if ( address > 0x1F )
    {
        return TEMPHUM21_ERROR;
    }
    err_t error_flag = TEMPHUM21_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = address;
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, 3 );
    Delay_1ms ( );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 3 );
    *status = data_buf[ 0 ];
    *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    return error_flag;
}

err_t temphum21_eeprom_write ( temphum21_t *ctx, uint8_t address, uint16_t data_in )
{
    if ( address > 0x1F )
    {
        return TEMPHUM21_ERROR;
    }
    err_t error_flag = TEMPHUM21_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = address | TEMPHUM21_CMD_WRITE_EEPROM;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, 3 );
    Delay_10ms ( );
    Delay_10ms ( );
    return error_flag;
}

err_t temphum21_enter_command_mode ( temphum21_t *ctx )
{
    err_t error_flag = TEMPHUM21_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = TEMPHUM21_CMD_START_CM;
    temphum21_disable_device ( ctx );
    Delay_1sec ( );
    temphum21_enable_device ( ctx );
    Delay_1ms ( );
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, 3 );
    Delay_1ms ( );
    return error_flag;
}

err_t temphum21_exit_command_mode ( temphum21_t *ctx )
{
    err_t error_flag = TEMPHUM21_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = TEMPHUM21_CMD_START_NOM;
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, 3 );
    Delay_100ms ( );
    return error_flag;
}

// ------------------------------------------------------------------------- END
