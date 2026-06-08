/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file thermostat7.c
 * @brief Thermostat 7 Click Driver.
 */

#include "thermostat7.h"

/**
 * @brief Thermostat 7 temperature to limit register function.
 * @details This function converts a floating-point temperature in degrees Celsius
 * to the 16-bit two's complement format.
 * @param[in] temperature_limit : Temperature limit.
 * @return Temperature in 16-bit two's complement.
 * @note None.
 */
static uint16_t thermostat7_temp_to_limit_reg ( float temperature_limit );

void thermostat7_cfg_setup ( thermostat7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMOSTAT7_DEVICE_ADDRESS;
}

err_t thermostat7_init ( thermostat7_t *ctx, thermostat7_cfg_t *cfg ) 
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

err_t thermostat7_default_cfg ( thermostat7_t *ctx ) 
{   
    err_t error_flag = THERMOSTAT7_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    
    error_flag |= thermostat7_check_communication( ctx );
    if ( THERMOSTAT7_OK != error_flag )
    {
        return THERMOSTAT7_ERROR;
    }

    /* CONFIGURATION REGISTER(0x01):
     *    bit[10:9] = 0 -> no hysteresis
     *    bit[8]    = 0 -> thermal sensor enabled
     *    bit[7]    = 0 -> critical trip can be updated
     *    bit[6]    = 0 -> alarm trip can be updated
     *    bit[4]    = 0 -> EVENT is not being asserted
     *    bit[3]    = 1 -> EVENT enabled
     *    bit[2]    = 0 -> alarm and critical trip mapped to EVENT condition
     *    bit[1]    = 0 -> EVENT active low
     *    bit[0]    = 0 -> Comparator mode */
    data_buf[ 0 ] = ( uint8_t ) ( THERMOSTAT7_CFG_EVENT_CTRL_EN >> 8 );
    data_buf[ 1 ] = ( uint8_t ) ( THERMOSTAT7_CFG_EVENT_CTRL_EN & 0xFF );
    error_flag |= thermostat7_write_regs( ctx, THERMOSTAT7_REG_CONFIGURATION, data_buf, 2 );

    /* set alarm temperature limits for EVENT condition */
    error_flag |= thermostat7_set_high_limit( ctx, THERMOSTAT7_DEFAULT_TEMP_HIGH );
    error_flag |= thermostat7_set_low_limit( ctx, THERMOSTAT7_DEFAULT_TEMP_LOW );
    error_flag |= thermostat7_set_critical_limit( ctx, THERMOSTAT7_DEFAULT_TEMP_CRITICAL );

    /* "Power-Up Delay to Valid Temperature Recording is 100ms" */
    Delay_100ms( );
    Delay_10ms( );

    return error_flag;
}

err_t thermostat7_write_reg ( thermostat7_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return thermostat7_write_regs( ctx, reg, &data_in, 1 );
}

err_t thermostat7_write_regs ( thermostat7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t thermostat7_read_reg ( thermostat7_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return thermostat7_read_regs( ctx, reg, data_out, 1 );
}

err_t thermostat7_read_regs ( thermostat7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t thermostat7_check_communication ( thermostat7_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };

    /* read manufacturer ID from Manufacturer ID Register(0x06) -> expected value 0x1B09 */
    if ( THERMOSTAT7_OK == thermostat7_read_regs( ctx, THERMOSTAT7_REG_MANUFACTURER_ID, data_buf, 2 ) )
    {   
        /* assemble 16-bit read data -> MSB is read first */
        uint16_t manufacturer_id = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];

        if ( THERMOSTAT7_MANUFACTURER_ID == manufacturer_id )
        {
            return THERMOSTAT7_OK;
        }
    }
    return THERMOSTAT7_ERROR;
}

err_t thermostat7_set_high_limit ( thermostat7_t *ctx, float temperature_limit )
{
    /* convert temperature limit to 16-bit two's complement format and write it to High Limit Register(0x02) */
    uint16_t reg_val = thermostat7_temp_to_limit_reg( temperature_limit );
    uint8_t data_buf[ 2 ] = { 0 };
    
    /* send MSB first */
    data_buf[ 0 ] = ( uint8_t ) ( reg_val >> 8 );
    data_buf[ 1 ] = ( uint8_t ) ( reg_val & 0xFF );

    return thermostat7_write_regs( ctx, THERMOSTAT7_REG_HIGH_LIMIT, data_buf, 2 );
}

err_t thermostat7_set_low_limit ( thermostat7_t *ctx, float temperature_limit )
{
    /* convert temperature limit to 16-bit two's complement format and write it to Low Limit Register(0x03) */
    uint16_t reg_val = thermostat7_temp_to_limit_reg( temperature_limit );
    uint8_t data_buf[ 2 ] = { 0 };
    
    /* send MSB first */
    data_buf[ 0 ] = ( uint8_t ) ( reg_val >> 8 );
    data_buf[ 1 ] = ( uint8_t ) ( reg_val & 0xFF );

    return thermostat7_write_regs( ctx, THERMOSTAT7_REG_LOW_LIMIT, data_buf, 2 );
}

err_t thermostat7_set_critical_limit ( thermostat7_t *ctx, float temperature_limit )
{
    /* convert temperature limit to 16-bit two's complement format and write it to Critical Limit Register(0x04) */
    uint16_t reg_val = thermostat7_temp_to_limit_reg( temperature_limit );
    uint8_t data_buf[ 2 ] = { 0 };
    
    /* send MSB first */
    data_buf[ 0 ] = ( uint8_t ) ( reg_val >> 8 );
    data_buf[ 1 ] = ( uint8_t ) ( reg_val & 0xFF );

    return thermostat7_write_regs( ctx, THERMOSTAT7_REG_CRITICAL_LIMIT, data_buf, 2 );
}

err_t thermostat7_read_temperature ( thermostat7_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    
    /* read temperature data register(0x05) */
    err_t error_flag = thermostat7_read_regs( ctx, THERMOSTAT7_REG_TEMPERATURE, data_buf, 2 );
    if ( THERMOSTAT7_OK == error_flag )
    {   
        /* assemble 16-bit read data -> MSB is read first */
        uint16_t raw_u = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];

        /* Isolate the 13-bit temperature data [12:0], stripping alarm status bits [15:13]. */
        raw_u &= THERMOSTAT7_TDR_DATA_MASK;

        /* read the sign flag from TDR register and perform sign extension if temperature is negative */
        int16_t raw_s;
        if ( raw_u & THERMOSTAT7_TDR_SIGN_BIT )
        {
            raw_s = ( int16_t ) ( raw_u | THERMOSTAT7_TEMP_SIGN_EXTEND );
        }
        else
        {
            raw_s = ( int16_t ) raw_u;
        }
        
        /* Capability Register power-on value is 0x007F => LSB = 0.0625 degrees Celsius */
        *temperature = ( float ) raw_s * THERMOSTAT7_TEMP_RESOLUTION;
    }

    return error_flag;
}

err_t thermostat7_read_alarm_status ( thermostat7_t *ctx, uint8_t *status )
{
    uint8_t data_buf[ 2 ] = { 0 };

    /* Read temperature data register(0x05) */
    err_t error_flag = thermostat7_read_regs( ctx, THERMOSTAT7_REG_TEMPERATURE, data_buf, 2 );
    if ( THERMOSTAT7_OK == error_flag )
    {
        /* assemble 16-bit read data -> MSB is read first */
        uint16_t raw_u = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];

        *status = THERMOSTAT7_ALARM_NONE;
        
        /* check if any temperature alarm has been set, */
        if ( raw_u & THERMOSTAT7_TDR_TCRIT_FLAG )
        {
            *status |= THERMOSTAT7_ALARM_TCRIT;
        }
        if ( raw_u & THERMOSTAT7_TDR_HIGH_FLAG )
        {
            *status |= THERMOSTAT7_ALARM_HIGH;
        }
        if ( raw_u & THERMOSTAT7_TDR_LOW_FLAG )
        {
            *status |= THERMOSTAT7_ALARM_LOW;
        }
    }

    return error_flag;
}

static uint16_t thermostat7_temp_to_limit_reg ( float temperature_limit )
{
    /* For the 3 temperature limit registers LSB = 0.25 degrees Celsius */
    int16_t raw = ( int16_t ) ( temperature_limit / THERMOSTAT7_LIMIT_RESOLUTION );

    /* bits[1:0] and bits[15:13] in limit registers are always 0 */
    return ( uint16_t ) ( raw << THERMOSTAT7_LIMIT_REG_SHIFT ) & THERMOSTAT7_LIMIT_REG_MASK;
}

// ------------------------------------------------------------------------- END
