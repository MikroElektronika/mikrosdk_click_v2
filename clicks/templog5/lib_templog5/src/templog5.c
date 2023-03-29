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

#include "templog5.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void conv_delay( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void templog5_cfg_setup ( templog5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed    = I2C_MASTER_SPEED_STANDARD; 
    cfg->ts_slave     = TEMPLOG5_TS_SLAVE_ADDR_000;
    cfg->eeprom_slave = TEMPLOG5_EEPROM_SLAVE_ADDR_000;

}

TEMPLOG5_RETVAL templog5_init ( templog5_t *ctx, templog5_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->ts_slave     = cfg->ts_slave;
    ctx->eeprom_slave = cfg->eeprom_slave;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPLOG5_INIT_ERROR;
    }

    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TEMPLOG5_OK;
}

void templog5_default_cfg ( templog5_t *ctx )
{
    templog5_write_data( ctx, TEMPLOG5_REG_CONFIGURATION, 
                              TEMPLOG5_CFG_DISABLE_HYSTERESIS |
                              TEMPLOG5_CFG_TEMP_SENSOR_ENABLE |
                              TEMPLOG5_CFG_CRITICAL_TRIP_ENABLE | 
                              TEMPLOG5_CFG_ALARM_TRIP_ENABLE |
                              TEMPLOG5_CFG_EVENT_INT_PIN_ENABLE | 
                              TEMPLOG5_CFG_EVENT_OUT_ENABLE |
                              TEMPLOG5_CFG_EVENT_OUT_ACTIVE_HIGH | 
                              TEMPLOG5_CFG_EVENT_MODE_COMPARATOR );
}

void templog5_write_data ( templog5_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t write_reg[ 3 ];

    write_reg[ 0 ] = reg;
    write_reg[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    write_reg[ 2 ] = ( uint8_t ) ( data_in );

    i2c_master_set_slave_address( &ctx->i2c, ctx->ts_slave );
    i2c_master_write( &ctx->i2c, write_reg, 3 );   
}

void templog5_write_eeprom ( templog5_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_byte )
{
    uint8_t write_reg[ 256 ];
    uint8_t cnt;
    
    write_reg[ 0 ] = start_addr;
    for ( cnt = 0; cnt < n_byte; cnt++ )
    {
        write_reg[ cnt + 1 ] = data_in[ cnt ];
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->eeprom_slave );
    i2c_master_write( &ctx->i2c, write_reg, n_byte + 1 ); 
}

uint16_t templog5_read_data ( templog5_t *ctx, uint8_t reg )
{
    uint8_t write_reg[ 1 ];
    uint8_t read_reg[ 2 ];
    uint16_t read_data;
    
    write_reg[ 0 ] = reg;

    i2c_master_set_slave_address( &ctx->i2c, ctx->ts_slave );
    i2c_master_write_then_read( &ctx->i2c, write_reg, 1, read_reg, 2 );
    
    read_data = read_reg[ 0 ];
    read_data = read_data << 8;
    read_data = read_data | read_reg[ 1 ];
    
    return read_data;
}

void templog5_read_eeprom ( templog5_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_byte )
{
    uint8_t write_reg[ 1 ];

    write_reg[ 0 ] = start_addr;

    i2c_master_set_slave_address( &ctx->i2c, ctx->eeprom_slave );
    i2c_master_write_then_read( &ctx->i2c, write_reg, 1, data_out, n_byte );
}

float templog5_get_temperature ( templog5_t *ctx )
{
    uint16_t temp_out = 0;
    int16_t temp_data;
    uint8_t polarity = 0;
    
    float temperature;
    
    temp_out = templog5_read_data( ctx, TEMPLOG5_REG_TEMPERATURE );
    if ( ( temp_out & 0x1000 ) != 0 )
    {
        polarity = 1;
    }
    ctx->temp_status = ( uint8_t )( ( temp_out & 0xF000 ) >> 12 );
    
    temp_out = ( temp_out & 0x0FFF );
    temp_data = temp_out;
    
    if ( polarity == 1 )
    {
        temp_data = temp_data - 8192;
    }
    temperature = temp_data * 0.0625;
    
    conv_delay();
    
    return temperature;
}

uint8_t templog5_get_temperature_status ( templog5_t *ctx )
{
    return ctx->temp_status;
}

uint8_t templog5_get_interrupt_status ( templog5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void conv_delay()
{
    Delay_100ms();
}

// ------------------------------------------------------------------------- END

