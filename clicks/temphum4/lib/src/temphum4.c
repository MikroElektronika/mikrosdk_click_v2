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

#include "temphum4.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void communication_delay( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum4_cfg_setup ( temphum4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ad0 = HAL_PIN_NC;
    cfg->ad1   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x42;
}

TEMPHUM4_RETVAL temphum4_init ( temphum4_t *ctx, temphum4_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->ad0, cfg->ad0 );
    digital_out_init( &ctx->ad1, cfg->ad1 );
    
    digital_out_write( &ctx->ad0, 0 );
    digital_out_write( &ctx->ad1, 1 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TEMPHUM4_OK;
}

void temphum4_default_cfg ( temphum4_t *ctx )
{
    temphum4_set_mode( ctx, TEMPHUM4_MODE_ACTIVE );
    temphum4_configuration ( ctx, 
                            TEMPHUM4_CONF_NORMAL_OPERATION |
                            TEMPHUM4_CONF_HEATER_DISABLED |
                            TEMPHUM4_CONF_MODE_TEMP_AND_HUM |
                            TEMPHUM4_CONF_BATTERY_VOLTAGE_2_8_V |
                            TEMPHUM4_CONF_TEMPERATURE_14bit |
                            TEMPHUM4_CONF_HUMINIDY_14bit );
}

void temphum4_generic_write ( temphum4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 ); 
}

void temphum4_generic_read ( temphum4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, &reg, 1 ); 
    communication_delay();
    i2c_master_read( &ctx->i2c, data_buf, len ); 
}

void temphum4_set_mode ( temphum4_t *ctx, uint8_t value )
{
    digital_out_write( &ctx->ad1, value );   
}

uint16_t temphum4_get_manifacturer_id ( temphum4_t *ctx )
{
    uint8_t read_reg[ 2 ];
    uint16_t main_id;
    uint8_t int_pin_state;
    
    int_pin_state = digital_in_read( &ctx->int_pin );
    
    if ( int_pin_state == 1 )
    {
       temphum4_generic_read( ctx, 0xFE, read_reg, 2 ); 
    
       main_id = read_reg[ 0 ];
       main_id <<= 8;
       main_id = main_id | read_reg[ 1 ];
    
      communication_delay();
    }
    return main_id;
}
uint16_t temphum4_get_device_id ( temphum4_t *ctx )
{
    uint8_t read_reg[ 2 ];
    uint16_t main_id;
    uint8_t int_pin_state;
    
    int_pin_state = digital_in_read( &ctx->int_pin );
    if ( int_pin_state == 1 )
    {
       temphum4_generic_read( ctx, 0xFF, read_reg, 2); 
    
       main_id = read_reg[ 0 ];
       main_id <<= 8;
       main_id = main_id | read_reg[ 1 ];
    
      communication_delay();
    }
    return main_id;
}
void temphum4_configuration ( temphum4_t *ctx, uint16_t conf_data )
{
    uint8_t data_buff[ 2 ];
    
    data_buff[ 0 ] = conf_data >> 8;
    data_buff[ 1 ] = conf_data;
    
    temphum4_generic_write( ctx, 0x02, data_buff, 2 );
    communication_delay( );
}

float temphum4_get_temperature ( temphum4_t *ctx )
{
    uint8_t data_buff[ 2 ];
    int16_t temp_data;
    float temperature;
    uint8_t int_pin_state;
    
    int_pin_state = digital_in_read( &ctx->int_pin );
    if ( int_pin_state == 1 )
    {
        temphum4_generic_read( ctx, 0x00, data_buff, 2 );
        temp_data = data_buff[ 0 ]; 
        temp_data <<= 8;
        temp_data = temp_data | data_buff[ 1 ];
        temperature = temp_data / 65536.00;
        temperature = temperature * 165;
        temperature = temperature - 40.00;

        communication_delay( );
    }
    return temperature;
}

float temphum4_get_humidity ( temphum4_t *ctx )
{
    uint8_t data_buff[ 2 ];
    uint16_t hum_data;
    float humidity;
    uint8_t int_pin_state; 

    int_pin_state = digital_in_read( &ctx->int_pin ); 
    if (  int_pin_state == 1 )
    {
        temphum4_generic_read( ctx, 0x01, data_buff, 2);
        hum_data = data_buff[ 0 ];
        hum_data <<= 8;
        hum_data = hum_data | data_buff[ 1 ];
        humidity = hum_data / 65536.00;
        humidity = humidity * 100;

        communication_delay( );
    }
    return humidity;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void communication_delay ( void ) 
{
    Delay_100ms();
}

// ------------------------------------------------------------------------- END

