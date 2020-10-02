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

#include "temphum3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void communication_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum3_cfg_setup ( temphum3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x41;
}

TEMPHUM3_RETVAL temphum3_init ( temphum3_t *ctx, temphum3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->cs, cfg->cs );
   
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TEMPHUM3_OK;

}

void temphum3_default_cfg ( temphum3_t *ctx )
{
    temphum3_set_mode( ctx, TEMPHUM3_MODE_ACTIVE );

    temphum3_set_measurement( ctx, 
                              TEMPHUM3_MCONF_TEMP_RES_14BIT |
                              TEMPHUM3_MCONF_HUM_RES_14BIT | 
                              TEMPHUM3_MCONF_HUM_TEMP | 
                              TEMPHUM3_MCONF_MEAS_START );
    
    temphum3_set_configuration( ctx, 
                              TEMPHUM3_CONF_NORMAL_MODE  |
                              TEMPHUM3_CONF_ODR_REPEATED_1SEC |
                              TEMPHUM3_CONF_HEATER_OFF |
                              TEMPHUM3_CONF_INT_DRDY_HIGH_Z |
                              TEMPHUM3_CONF_INT_POL_LOW |
                              TEMPHUM3_CONF_INT_MODE_SENSITIVE ); 
                             
    temphum3_set_high_temp( ctx, 45 );
    temphum3_set_low_temp ( ctx, 10 );
    temphum3_set_high_hum ( ctx, 30 );
    temphum3_set_low_hum  ( ctx, 70 );
}

void temphum3_generic_write ( temphum3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void temphum3_generic_read ( temphum3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void temphum3_set_measurement ( temphum3_t *ctx, uint8_t value )
{
    temphum3_generic_write( ctx, 0x0F, &value, 1 );
}

void temphum3_set_configuration ( temphum3_t *ctx, uint8_t value )
{
    temphum3_generic_write ( ctx, 0x0E, &value, 1 );
}

void temphum3_set_mode ( temphum3_t *ctx, uint8_t value )
{
    digital_out_write( &ctx->cs, value );
}

float temphum3_get_temperature ( temphum3_t *ctx )
{
    uint8_t msb[ 1 ];
    uint8_t lsb[ 1 ];
    
    volatile int16_t temp_data;
    volatile float temp;
    
    temphum3_generic_read( ctx, 0x01, &msb, 1 );

    temp_data = msb[ 0 ];       
    temp_data <<= 8;
    
    communication_delay();
    temphum3_generic_read( ctx, 0x00, &lsb, 1 );
    
    temp_data = temp_data | lsb[ 0 ];
    temp = temp_data / 65536.00;
    temp = temp * 165;
    temp = temp - 40.00;
    
    return temp; 
}

float temphum3_get_humidity ( temphum3_t *ctx )
{
    uint8_t msb[ 1 ];
    uint8_t lsb[ 1 ];
    uint8_t buff[ 1 ];
    volatile int16_t hum_data;
    volatile float hum;

    temphum3_generic_read( ctx, 0x03, &msb, 1 );

    hum_data = msb[ 0 ];  
    hum_data <<= 8;
    
    communication_delay();
    
    temphum3_generic_read( ctx, 0x02, &lsb, 1 );
    
    hum_data = hum_data | lsb[ 0 ];
    hum = hum_data / 65536.00;
    hum = hum * 100;
    
    return hum;
}

uint16_t temphum3_get_id ( temphum3_t *ctx )
{
    uint16_t value = 0;
    
    while ( value != 0x07D0 )
    {
        uint8_t r_reg[ 2 ];

        temphum3_generic_read( ctx, 0xFE, &r_reg, 2 );
        value = r_reg[ 1 ];
        value <<= 8;
        value |= r_reg[0];
    }

    return value;
}

uint16_t temphum3_get_manufacturer_id ( temphum3_t *ctx )
{
    uint16_t value = 0;
    uint8_t r_reg[ 2 ];
        
    while ( value != 0x5449 )
    {
        temphum3_generic_read( ctx, 0xFC, &r_reg, 2 );
        value = r_reg[ 1 ];
        value <<= 8;
        value = value | r_reg[ 0 ];
    }
    return value;
}

uint8_t temphum3_get_status_interrupt ( temphum3_t *ctx, uint8_t mask )
{
    uint8_t w_reg = TEMPHUM3_REG_INTERRUPT_DRDY;
    uint8_t r_reg[ 1 ];
    
    temphum3_generic_read( ctx, w_reg, r_reg, 1 );
    
    if ( r_reg[ 0 ] & mask )
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

uint8_t temphum3_get_interrupt_mask ( temphum3_t *ctx, uint8_t mask )
{
    uint8_t w_reg = TEMPHUM3_REG_INTERRUPT_MASK;
    uint8_t r_reg[ 1 ];
    
    temphum3_generic_read( ctx, w_reg, r_reg, 1 );
    
    if ( r_reg[ 0 ] & mask )
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

void temphum3_set_offset ( temphum3_t *ctx, uint8_t reg, uint8_t value )
{
    temphum3_generic_write( ctx, reg, &value, 2);
}

void temphum3_set_high_temp ( temphum3_t *ctx, uint8_t temp_data )
{
    uint8_t w_reg;
    w_reg = ( uint8_t )( ( temp_data + 40 ) / 165 * 0xFF );

    temphum3_generic_write( ctx, 0x0B, &w_reg, 1 );
}

void temphum3_set_low_temp ( temphum3_t *ctx, uint8_t temp_data)
{
    uint8_t w_reg;
    w_reg = ( uint8_t )( ( temp_data + 40 ) / 165 * 0xFF );

    temphum3_generic_write( ctx, 0x0A, &w_reg, 1 );
}

void temphum3_set_high_hum( temphum3_t *ctx, uint8_t hum_data)
{
    uint8_t w_reg;
    w_reg = ( uint8_t )( ( hum_data / 100 ) * 0xFF );

    temphum3_generic_write( ctx, 0x0C, &w_reg, 1 );
}

void temphum3_set_low_hum( temphum3_t *ctx, uint8_t hum_data)
{
    uint8_t w_reg;
    w_reg = ( uint8_t )( ( hum_data / 100 ) * 0xFF );

    temphum3_generic_write( ctx, 0x0D, &w_reg, 1 );
}

float temphum3_get_max_hum ( temphum3_t *ctx )
{
    uint8_t r_reg[ 1 ];
    float hum_data;

    temphum3_generic_read( ctx, TEMPHUM3_REG_HUMIDITY_MAX, r_reg, 1 );
    
    hum_data = ( r_reg[ 0 ] / 256.00 ) * 100;
    return hum_data;
}

float temphum3_get_max_temp ( temphum3_t *ctx )
{
    uint8_t r_reg[ 1 ];
    float temp_data;

    temphum3_generic_read( ctx, TEMPHUM3_REG_TEMPERATURE_MAX, r_reg, 1 );
    
    temp_data = ( r_reg[ 0 ] / 256.00 ) * 100;  
    temp_data = temp_data - 40;

    return temp_data;
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void communication_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

