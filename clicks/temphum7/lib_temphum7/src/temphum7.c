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

#include "temphum7.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define TEMPHUM7_MEASURE_RELATIVE_HUMIDITY_HOLD      0xE5
#define TEMPHUM7_MEASURE_RELATIVE_HUMIDITY_NOHOLD    0xF5
#define TEMPHUM7_MEASURE_TEMPERATURE_HOLD            0xE3
#define TEMPHUM7_MEASURE_TEMPERATURE_NOHOLD          0xF3
#define TEMPHUM7_READ_TEMPERATURE_FROM_PREVIOUS_RH   0xE0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void aux_read ( temphum7_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum7_cfg_setup ( temphum7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPHUM7_DEVICE_ADDRESS;
}

TEMPHUM7_RETVAL temphum7_init ( temphum7_t *ctx, temphum7_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default ( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    return TEMPHUM7_OK;
}

void temphum7_default_cfg ( temphum7_t *ctx )
{
    uint8_t temp_buffer[ 1 ];
    
    // Click default configuration 

    temp_buffer[ 0 ] = TEMPHUM7_RESOLUTION_12_BIT;
    temphum7_generic_write( ctx, TEMPHUM7_WRITE_RHT_USER_REGISTER_1, temp_buffer, 1 );
}

void temphum7_generic_write ( temphum7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
    Delay_10ms();
}

void temphum7_generic_read ( temphum7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
    Delay_10ms();
}

float temphum7_get_relative_humidity ( temphum7_t *ctx, uint8_t mode_data )
{
    uint16_t aux;
    float relative_humidity;
    uint8_t data_out[ 2 ];
    
    if ( mode_data == 0 )
    {
        temphum7_generic_read( ctx, TEMPHUM7_MEASURE_RELATIVE_HUMIDITY_HOLD, data_out, 2 );
    }
    else if ( mode_data == 1 )
    {
        temphum7_generic_write( ctx, TEMPHUM7_MEASURE_RELATIVE_HUMIDITY_NOHOLD, data_out, 2 );
    }
    
    aux = data_out[ 0 ];
    aux <<= 8;
    aux |= data_out[ 1 ];
    
    relative_humidity  = ( float )aux * 125;
    relative_humidity /= 65536;
    relative_humidity -= 6;
    
    return relative_humidity;
}

float temphum7_get_temperature ( temphum7_t *ctx, uint8_t mode_data )
{
    uint16_t aux;
    float temperature;
    uint8_t data_out[ 2 ];

    if ( mode_data == 0 )
    {
        temphum7_generic_read( ctx, TEMPHUM7_MEASURE_TEMPERATURE_HOLD, data_out, 2 );
    }
    else if ( mode_data == 1 )
    {
        temphum7_generic_read( ctx, TEMPHUM7_MEASURE_TEMPERATURE_NOHOLD, data_out, 2 );
    }
    else if ( mode_data == 2 )
    {
        temphum7_generic_read( ctx, TEMPHUM7_READ_TEMPERATURE_FROM_PREVIOUS_RH, data_out, 2 );
    }

    aux = data_out[ 0 ];
    aux <<= 8;
    aux |= data_out[ 1 ];

    temperature  = aux * 175.72;
    temperature /= 65536;
    temperature -= 46.85;

    return temperature;
}

void temphum7_get_electronic_serial_number ( temphum7_t *ctx, uint8_t *esn_buffer )
{
    uint8_t aux_buffer[ 2 ];

    aux_buffer[ 0 ] = 0xFA;
    aux_buffer[ 1 ] = 0x0F;

    aux_read( ctx, aux_buffer, esn_buffer, 8 );
    Delay_1ms( );
    
    aux_buffer[ 0 ] = 0xFC;
    aux_buffer[ 1 ] = 0xC9;
    
    aux_read( ctx, aux_buffer, &esn_buffer[8], 6 );
}

uint8_t temphum7_get_firmware_revision ( temphum7_t *ctx )
{
    uint8_t aux_buffer[ 2 ];
    uint8_t fw_revision;

    aux_buffer[ 0 ] = 0x84;
    aux_buffer[ 1 ] = 0xB8;

    aux_read 
    (
        ctx,
        aux_buffer,
        &fw_revision,
        1
    );
    
    return fw_revision;
}

float temphum7_get_heater_current ( temphum7_t *ctx )
{
    uint8_t aux_byte[ 1 ];
    float heater_current;

    temphum7_generic_read
    (
        ctx,
        TEMPHUM7_READ_HEATER_CONTROL_REGISTER,
        aux_byte,
        1
    );
    
    aux_byte[ 0 ] &= 0x0F;
    
    heater_current = aux_byte[ 0 ] * 6.074;
    heater_current += 3.09;

    return heater_current;
}

void temphum7_reset ( temphum7_t *ctx )
{
    uint8_t aux_byte [ 1 ];

    temphum7_generic_write
    (
        ctx,
        TEMPHUM7_RESET,
        aux_byte,
        0
    );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void aux_read ( temphum7_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, reg, 2, data_buf, len );
}

// ------------------------------------------------------------------------- END

