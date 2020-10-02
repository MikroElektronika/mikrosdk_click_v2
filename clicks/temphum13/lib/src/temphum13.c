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

#include "temphum13.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Calculate crc8 for input value
 *
 * @param uint16_t value for crc8 calculation
 *
 * @returns crc8 calculation result
 *
 * @description This function calculates crc8 for input value.
 */
static uint8_t temphum13_crc( uint16_t input_value );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum13_cfg_setup ( temphum13_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPHUM13_DEVICE_ADDRESS;
}

TEMPHUM13_RETVAL temphum13_init ( temphum13_t *ctx, temphum13_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM13_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return TEMPHUM13_OK;
}

void temphum13_default_cfg ( temphum13_t *ctx )
{
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    temphum13_soft_reset( ctx );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
}

void temphum13_generic_write ( temphum13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void temphum13_generic_read ( temphum13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, &reg, 1 );
    Delay_100ms( );
    i2c_master_read( &ctx->i2c,data_buf, len );
    Delay_100ms();
}

float temphum13_get_temperature ( temphum13_t *ctx )
{
    float retval_temperature;
    uint16_t aux_temperature;
    uint8_t aux_buffer[3];
    uint8_t aux_command;
    uint8_t aux_crc;
    
    aux_command = TEMPHUM13_CMD_TRIG_TEMP_MEAS_HOLD;
    
    temphum13_generic_read( ctx, aux_command, aux_buffer, 3 );
    
    aux_temperature = aux_buffer[ 0 ];
    aux_temperature <<= 8;
    aux_temperature |= aux_buffer[ 1 ];
    
    if ( aux_buffer[ 2 ] == temphum13_crc( aux_temperature ) )
    {
        aux_temperature &= 0xFFFC;

        retval_temperature = (float)( aux_temperature );
        retval_temperature /= 65536;
        retval_temperature *= 175.72;
        retval_temperature -= 46.85;

        return retval_temperature;
    }
    
    return 65536.00;
}

float temphum13_get_humidity ( temphum13_t *ctx )
{
    float retval_humidity;
    uint16_t aux_humidity;
    uint8_t aux_buffer[ 3 ];
    uint8_t aux_command;
    uint8_t aux_crc;

    aux_command = TEMPHUM13_CMD_TRIG_HUMI_MEAS_HOLD;

    temphum13_generic_read( ctx, aux_command, aux_buffer, 3 );

    aux_humidity = aux_buffer[ 0 ];
    aux_humidity <<= 8;
    aux_humidity |= aux_buffer[ 1 ];
    
    if ( aux_buffer[ 2 ] == temphum13_crc( aux_humidity ) )
    {
        aux_humidity &= 0xFFFC;

        retval_humidity = ( float )( aux_humidity );
        retval_humidity /= 65536;
        retval_humidity *= 125.0;
        retval_humidity -= 6.0;

        return retval_humidity;
    }

    return 65536.00;
}

uint8_t temphum13_get_user_register ( temphum13_t *ctx )
{
    uint8_t aux_command;
    uint8_t aux_content;
    
    aux_command = TEMPHUM13_CMD_READ_USER_REG;
    aux_content = 0;
    
    temphum13_generic_read( ctx, aux_command, &aux_content, 1 );

    return aux_content;
}

void temphum13_set_user_register ( temphum13_t *ctx, uint8_t register_content )
{
    uint8_t reg_address;
    uint8_t data_to_write;

    reg_address = TEMPHUM13_CMD_WRITE_USER_REG;
    data_to_write = register_content;

    temphum13_generic_write( ctx, reg_address, &data_to_write, 1 );
}

void temphum13_soft_reset ( temphum13_t *ctx )
{
    uint8_t aux_reg_address;

    aux_reg_address = TEMPHUM13_CMD_SOFT_RESET;

    i2c_master_write( &ctx->i2c, &aux_reg_address, 1 );   
}

uint8_t temphum13_enable_heater ( temphum13_t *ctx, uint8_t enable_heater )
{
    uint8_t aux_stat_reg;
    
    aux_stat_reg = temphum13_get_user_register( ctx );
    
    if ( enable_heater == 1 )
    {
        aux_stat_reg |= 0x04;
        
        temphum13_set_user_register( ctx, aux_stat_reg );
        
        return 0;
    }
    else if ( enable_heater == 0 )
    {
        aux_stat_reg &= 0xFB;

        temphum13_set_user_register( ctx, aux_stat_reg );
        
        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t temphum13_change_resolution ( temphum13_t *ctx, uint8_t measurement_resolution )
{
    uint8_t aux_stat_reg;

    aux_stat_reg = temphum13_get_user_register( ctx );

    if ( measurement_resolution == 0x00 )
    {
        aux_stat_reg &= 0x7E;
        aux_stat_reg |= measurement_resolution;

        temphum13_set_user_register( ctx, aux_stat_reg );

        return 0;
    }
    else if ( measurement_resolution == 0x01 )
    {
        aux_stat_reg &= 0x7E;
        aux_stat_reg |= measurement_resolution;

        temphum13_set_user_register( ctx, aux_stat_reg );

        return 0;
    }
    else if ( measurement_resolution == 0x80 )
    {
        aux_stat_reg &= 0x7E;
        aux_stat_reg |= measurement_resolution;

        temphum13_set_user_register( ctx, aux_stat_reg );

        return 0;
    }
    else if ( measurement_resolution == 0x81 )
    {
        aux_stat_reg &= 0x7E;
        aux_stat_reg |= measurement_resolution;

        temphum13_set_user_register( ctx, aux_stat_reg );

        return 0;
    }
    else
    {
        return 1;
    }
}

uint8_t temphum13_disable_otp_reload ( temphum13_t *ctx, uint8_t disable_otp_reload )
{
    uint8_t aux_stat_reg;

    aux_stat_reg = temphum13_get_user_register( ctx );

    if ( disable_otp_reload == 1 )
    {
        aux_stat_reg |= 0x02;

        temphum13_set_user_register( ctx, aux_stat_reg );

        return 0;
    }
    else if ( disable_otp_reload == 0 )
    {
        aux_stat_reg &= 0xFD;

        temphum13_set_user_register( ctx, aux_stat_reg );

        return 0;
    }
    else
    {
        return 1;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t temphum13_crc ( uint16_t input_value )
{
    char crc[ 8 ];
    uint8_t i;
    char do_invert;
    uint8_t ret_val;
    uint16_t aux_mask;
    char bit_string[ 16 ];
    
    aux_mask = 0x8000;
    
    for ( i = 0; i < 16; i ++ )
    {
        if ( ( ( input_value & aux_mask ) != 0x0000 ) )
        {
            bit_string[ i ] = '1';
        }
        else
        {
            bit_string[ i ] = '0';
        }
        
        aux_mask >>= 1;
    }

    for ( i = 0; i < 8; ++ i )
    {
        crc[ i ] = 0;
    }

    for ( i = 0; i < 16; ++ i )
    {
        do_invert = ( '1' == bit_string[ i ] ) ^ crc[ 7 ];

        crc[ 7 ] = crc[ 6 ];
        crc[ 6 ] = crc[ 5 ];
        crc[ 5 ] = crc[ 4 ] ^ do_invert;
        crc[ 4 ] = crc[ 3 ] ^ do_invert;
        crc[ 3 ] = crc[ 2 ];
        crc[ 2 ] = crc[ 1 ];
        crc[ 1 ] = crc[ 0 ];
        crc[ 0 ] = do_invert;
    }

    ret_val = 0x00;
    aux_mask = 0x0001;
    
    for ( i = 0; i < 8; i ++ )
    {
        if ( ( ( crc[ i ] & 0x01 ) == 0x01 ) )
        {
            ret_val |= aux_mask;
        }
        aux_mask <<= 1;
    }
    
    return ret_val;
}

// ------------------------------------------------------------------------- END

