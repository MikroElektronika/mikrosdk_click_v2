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

#include "temphum12.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void conv_time_delay ( );
static void wait_drdy_status ( temphum12_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum12_cfg_setup ( temphum12_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPHUM12_DEVICE_SLAVE_ADDRESS;
}

TEMPHUM12_RETVAL temphum12_init ( temphum12_t *ctx, temphum12_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM12_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TEMPHUM12_OK;
}

void temphum12_default_cfg ( temphum12_t *ctx )
{
    uint8_t temp;

    temp = TEMPHUM12_INTE_DRDY_ENABLE;
    temphum12_generic_write( ctx, TEMPHUM12_REG_INT_ENABLE, &temp , 1 );
    
    temp = TEMPHUM12_ICFG_NORAML_OPERATION |
           TEMPHUM12_ICFG_AMM_5Hz | 
           TEMPHUM12_ICFG_HEATER_DISABLE |
           TEMPHUM12_ICFG_DRDY_ENABLE | 
           TEMPHUM12_ICFG_INT_ACTIVE_HIGH |
           TEMPHUM12_ICFG_COMPARATOR_MODE;
    temphum12_generic_write( ctx, TEMPHUM12_REG_DRDY_INT_CONFIG, &temp, 1 );

    temp = TEMPHUM12_MCFG_TEMP_RES_14bit | 
           TEMPHUM12_MCFG_HUM_RES_14bit | 
           TEMPHUM12_MCFG_TEMP_HUM_READ | 
           TEMPHUM12_MCFG_TRIG_START_MEASUREMENT;
    temphum12_generic_write( ctx, TEMPHUM12_REG_CONFIGURATION, &temp, 1 );
}

void temphum12_generic_write ( temphum12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void temphum12_generic_read ( temphum12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

float temphum12_get_temperature ( temphum12_t *ctx, uint8_t temp_in )
{
    uint16_t temp_out;
    float temperature;
    uint8_t read_reg[ 2 ];

    wait_drdy_status( ctx );

    temphum12_generic_read( ctx, TEMPHUM12_REG_DATA_TEMPERATURE, read_reg, 2 );
    temp_out = read_reg[ 1 ];
    temp_out <<= 8;
    temp_out |= read_reg[ 0 ];

    temperature = ( float )( temp_out / 65536.0 ) * 165.0 - 40;
    
    conv_time_delay( );
    
    if ( temp_in == TEMPHUM12_TEMP_IN_KELVIN )
    {
        temperature = temperature + 273.15;
    }
    else if ( temp_in == TEMPHUM12_TEMP_IN_FAHRENHEIT )
    {
        temperature = ( temperature * 9.0/5.0 ) + 32;
    }
    
    return temperature;
}

float temphum12_get_humidity ( temphum12_t *ctx )
{
    uint16_t hum_out;
    float humidity;
    uint8_t read_reg[ 2 ];

    wait_drdy_status( ctx );
    
    temphum12_generic_read( ctx, TEMPHUM12_REG_DATA_HUMIDITY, read_reg, 2 );
    hum_out = read_reg[ 1 ];
    hum_out <<= 8;
    hum_out |= read_reg[ 0 ];
    
    humidity = ( float ) ( hum_out / 65536.0 ) * 100.0;
    
    conv_time_delay( );
    
    if ( humidity < 1 )
    {
        humidity = 0;
    }
    
    return humidity;
}

uint8_t temphum12_get_intrrupt_state ( temphum12_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void conv_time_delay ( )
{
    Delay_500us( );
    Delay_50us( );
    Delay_50us( );
    Delay_50us( );
    Delay_10us( );
}

static void wait_drdy_status ( temphum12_t *ctx )
{
    uint8_t tmp;
    uint8_t cnt = 0;
    
    do
    {
        if ( cnt > 20 )
        {
            return;
        }
        cnt++;
        Delay_10ms( );
        
        temphum12_generic_read( ctx, TEMPHUM12_REG_DRDY_INTERRUPT, &tmp, 1 );
    
    }
    while ( ( tmp & TEMPHUM12_INT_STATUS_DRDY ) == 0 );
}

// ------------------------------------------------------------------------- END

