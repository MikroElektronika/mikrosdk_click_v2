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
 * @file irthermo2.c
 * @brief IrThermo 2 Click Driver.
 */

#include "irthermo2.h"


void irthermo2_cfg_setup ( irthermo2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->al = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = IRTHERMO2_I2C_ADDRESS_0;
}

err_t irthermo2_init ( irthermo2_t *ctx, irthermo2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return IRTHERMO2_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->al, cfg->al );

    return IRTHERMO2_OK;
}

void irthermo2_default_cfg ( irthermo2_t *ctx )
{
    irthermo2_write_data( ctx, IRTHERMO2_CONFIGURATION, IRTHERMO2_CFG_MODEON
                                                      | IRTHERMO2_CFG_ALERTEN
                                                      | IRTHERMO2_CFG_TRANSC
                                                      | IRTHERMO2_CFG_1SAMPLE );

    irthermo2_write_data( ctx, IRTHERMO2_STATUS_MASK_AND_ENABLE, IRTHERMO2_STAT_ALERTEN
                                                               | IRTHERMO2_STAT_CRTEN );

    irthermo2_check_id( ctx );
}

void irthermo2_generic_write ( irthermo2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );      
}

void irthermo2_generic_read ( irthermo2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void irthermo2_write_data ( irthermo2_t *ctx, uint8_t address, uint16_t write_data )
{
    uint8_t buffer_write[ 2 ];

    buffer_write[ 0 ] = ( uint8_t ) ( ( write_data & 0xFF00 ) >> 8 );
    buffer_write[ 1 ] = ( uint8_t ) ( write_data & 0x00FF );

    irthermo2_generic_write( ctx, address, buffer_write, 2 );
}

uint16_t irthermo2_read_data ( irthermo2_t *ctx, uint8_t address )
{
    uint8_t buffer_read[ 2 ];
    uint16_t result;

    irthermo2_generic_read ( ctx, address, buffer_read, 2 );

    result = buffer_read[ 0 ];
    result <<= 8;
    result |= buffer_read[ 1 ];

    return result;
}

err_t irthermo2_check_id ( irthermo2_t *ctx )
{
    uint16_t device_id;

    device_id = irthermo2_read_data( ctx, IRTHERMO2_DEVICE_ID );

    if ( device_id != IRTHERMO2_DEVICE_ID_VALUE )
        return IRTHERMO2_RESULT_ERROR;
    else
        return IRTHERMO2_RESULT_OK;
}

float irthermo2_get_object_temperature_c ( irthermo2_t *ctx )
{
    uint8_t buffer_read[ 2 ];

    uint16_t temperature_obj;
    float result;

    irthermo2_generic_read ( ctx, IRTHERMO2_OBJECT_TEMPERATURE, buffer_read, 2 );

    temperature_obj = buffer_read[ 0 ];
    temperature_obj <<= 8;
    temperature_obj |= buffer_read[ 1 ];
    temperature_obj >>= 2;

    if ( temperature_obj & ( 1 << 13 ) )
        temperature_obj |= 0xE000;

    result = ( float ) temperature_obj;
    result *= 0.03125;

    return result;
}

float irthermo2_get_object_temperature_f ( irthermo2_t *ctx )
{
    uint8_t buffer_read[ 2 ];

    uint16_t temperature_obj;
    float result;

    irthermo2_generic_read ( ctx, IRTHERMO2_OBJECT_TEMPERATURE, buffer_read, 2 );

    temperature_obj = buffer_read[ 0 ];
    temperature_obj <<= 8;
    temperature_obj |= buffer_read[ 1 ];
    temperature_obj >>= 2;

    if ( temperature_obj & ( 1 << 13 ) )
        temperature_obj |= 0xE000;

    result = ( float ) temperature_obj;
    result *= 0.05625;
    result += 32;

    return result;
}

float irthermo2_get_raw_temperature ( irthermo2_t *ctx )
{
    uint16_t temperature_raw;
    float result;

    temperature_raw = irthermo2_read_data( ctx, IRTHERMO2_LOCAL_TEMPERATURE );

    temperature_raw <<= 2;

    result = ( float ) temperature_raw;
    result *= 0.03125;

    return result;
}

uint8_t irhhermo2_get_alert ( irthermo2_t *ctx )
{
    return  digital_in_read( &ctx->al );
}

// ------------------------------------------------------------------------- END

