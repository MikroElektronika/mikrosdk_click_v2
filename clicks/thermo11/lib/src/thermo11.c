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

#include "thermo11.h"

// ------------------------------------------------------------------ VARIABLES

#define TEMP_LSB  0.0078125

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo11_cfg_setup ( thermo11_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO11_DEV_ADDR ;
}

THERMO11_RETVAL thermo11_init ( thermo11_t *ctx, thermo11_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;


    if (  i2c_master_open( &ctx->i2c, &i2c_cfg )== I2C_MASTER_ERROR )
    {
        return THERMO11_INIT_ERROR;
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return THERMO11_OK;

}

void thermo11_default_cfg ( thermo11_t *ctx )
{
    thermo11_write_reg( ctx, THERMO11_CONFIG_REG, THERMO11_CONTINUOUS_CONV_MODE | 
                                                  THERMO11_CONV_TIME_4 |  
                                                  THERMO11_8_AVRG_CONV | 
                                                  THERMO11_ALERT_MODE |   
                                                  THERMO11_INT_PIN_ACT_HIGH |  
                                                  THERMO11_INT_PIN_DRDY_FLAG );
    thermo11_set_temp( ctx, THERMO11_HIGH_LIMIT_REG, 30.5 );
    thermo11_set_temp( ctx, THERMO11_LOW_LIMIT_REG, -5 );
}

void thermo11_generic_write ( thermo11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermo11_generic_read ( thermo11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );

}

THERMO11_RETVAL thermo11_write_reg ( thermo11_t *ctx, uint8_t  reg_addr, uint16_t  data_in )
{
    uint8_t temp_data[ 2 ];
    
    if ( (reg_addr < THERMO11_CONFIG_REG ) || (reg_addr > THERMO11_EEPROM3_REG ) )
    {
        return THERMO11_INVALID_ADDR;
    }
    
    temp_data[ 0 ] = data_in >> 8;
    temp_data[ 1 ] = data_in;
    
    thermo11_generic_write( ctx, reg_addr, temp_data, 2 );
    
    return THERMO11_OK;
}

THERMO11_RETVAL thermo11_read_reg ( thermo11_t *ctx, uint8_t reg_addr, uint16_t *data_out )
{
    uint8_t temp_data[ 2 ];
    
    if ( ( reg_addr > THERMO11_EEPROM3_REG ) && ( reg_addr != THERMO11_DEV_ID_REG ) )
    {
        return THERMO11_INVALID_ADDR;
    }
    
    thermo11_generic_read( ctx, reg_addr, &temp_data, 1 );

    *data_out = temp_data[ 0 ];
    *data_out <<= 8;
    *data_out |= temp_data[ 1 ];
    

    return THERMO11_OK;
}

void thermo11_repeat_read_reg ( thermo11_t *ctx, uint16_t *data_out )
{
    uint8_t temp_data[ 2 ];

    thermo11_generic_read( ctx, temp_data[ 0 ], &temp_data[ 1 ], 1 );

    *data_out = temp_data[ 0 ];
    *data_out <<= 8;
    *data_out |= temp_data[ 1 ];
}

float thermo11_get_temp ( thermo11_t *ctx, uint8_t temp_addr )
{
    uint16_t temp_val;
    float ret_val;
    
    if ( ( temp_addr != THERMO11_TEMPERATURE_REG ) && ( temp_addr != THERMO11_HIGH_LIMIT_REG ) && ( temp_addr !=  THERMO11_LOW_LIMIT_REG ) && ( temp_addr !=  THERMO11_TEMP_OFFSET_REG ) )
    {
        return  THERMO11_INVALID_ADDR;
    }

    thermo11_read_reg ( ctx, temp_addr, &temp_val );
    
    ret_val = temp_val;
    ret_val *=  TEMP_LSB;
    
    return ret_val;
}

THERMO11_RETVAL thermo11_get_int ( thermo11_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t thermo11_sm_bus_alert_cmd ( thermo11_t *ctx )
{
    uint8_t alert_cmd = 0x0C;
    uint8_t alert_response;
    
    thermo11_generic_read ( ctx, alert_cmd, &alert_response, 1 );

    return alert_response;
}

void thermo11_general_call_reset_cmd ( thermo11_t *ctx )
{
    uint8_t reset_cmd = 0x00;
    uint8_t followed_byte = 0x06;
    
    thermo11_generic_write ( ctx, reset_cmd, &followed_byte, 1 );

    Delay_100ms( );
}

void thermo11_sw_reset( thermo11_t *ctx )
{
    uint16_t tmp;
    
    thermo11_read_reg( ctx, THERMO11_CONFIG_REG, &tmp );
    tmp |= THERMO11_SW_RESET_CMD;
    thermo11_write_reg( ctx, THERMO11_CONFIG_REG, tmp );

    Delay_100ms( );
}

THERMO11_RETVAL thermo11_check_status( thermo11_t *ctx )
{
    uint16_t temp;
    uint8_t ret_val;
    
    thermo11_read_reg( ctx, THERMO11_CONFIG_REG, &temp );
    ret_val = temp >> 13; 
    
    return ret_val;
}

THERMO11_RETVAL thermo11_program_eeprom ( thermo11_t *ctx, uint8_t eeprom_addr, uint16_t eeprom_data )
{
    uint16_t eeprom_busy;

    if ((eeprom_addr != THERMO11_EEPROM1_REG) && (eeprom_addr != THERMO11_EEPROM2_REG) && (eeprom_addr != THERMO11_EEPROM3_REG))
    {
        return THERMO11_INVALID_ADDR;
    }

     thermo11_write_reg( ctx, THERMO11_EEPROM_UNLOCK_REG, THERMO11_EEPROM_UNLOCK );
     thermo11_write_reg( ctx, eeprom_addr, eeprom_data );
    
    Delay_10ms();
    thermo11_read_reg( ctx, THERMO11_EEPROM_UNLOCK_REG, &eeprom_busy );
    
    while (eeprom_busy &  THERMO11_EEPROM_BUSY_FLAG)
    {
        Delay_10ms();
        thermo11_read_reg( ctx, THERMO11_EEPROM_UNLOCK_REG, &eeprom_busy );
    }
    
    thermo11_general_call_reset_cmd( ctx );
    
    return  THERMO11_OK;
}

THERMO11_RETVAL thermo11_set_temp ( thermo11_t *ctx, uint8_t temp_addr, float temp_value )
{
    int16_t write_data;
    
    if ( ( temp_addr != THERMO11_HIGH_LIMIT_REG ) && ( temp_addr != THERMO11_LOW_LIMIT_REG ) && ( temp_addr != THERMO11_TEMP_OFFSET_REG ) )
    {
        return THERMO11_INVALID_ADDR;
    }
    if ( ( temp_value > 255.9921875 ) || ( temp_value < -256 ) )
    {
        return THERMO11_INVALID_TEMP_RANGE;
    }
    
    temp_value /= TEMP_LSB;
    write_data = temp_value;
    
     thermo11_write_reg( ctx, temp_addr, write_data );
    
    return THERMO11_OK;
}

// ------------------------------------------------------------------------- END



