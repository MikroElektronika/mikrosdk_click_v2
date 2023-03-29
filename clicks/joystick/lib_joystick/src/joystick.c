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

#include "joystick.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void com_delay( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void joystick_cfg_setup ( joystick_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->tst   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = JOYSTICK_I2C_ADDRESS_0;
}

JOYSTCIK_RETVAL joystick_init ( joystick_t *ctx, joystick_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return JOYSTCIK_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_write( &ctx->rst, 1 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    digital_in_init( &ctx->tst, cfg->tst );

    return JOYSTCIK_OK;

}

void joystick_default_cfg ( joystick_t *ctx )
{
    // Click default configuration 
    uint8_t temp_data;
    uint8_t temp_buffer[ 1 ];
    uint8_t write_temp_buff[ 1 ];

    write_temp_buff[ 0 ] = JOYSTICK_CONTROL2_TEST_CMD;
    joystick_generic_write( ctx, JOYSTICK_CONTROL2, write_temp_buff, 1 );
  
    write_temp_buff[ 0 ] = JOYSTICK_AGC_MAX_SENSITIVITY_CMD;
    joystick_generic_write( ctx, JOYSTICK_AGC, write_temp_buff, 1 );
  
    write_temp_buff[ 0 ] = JOYSTICK_T_CTRL_SCALING_90_8_CMD;
    joystick_generic_write( ctx, JOYSTICK_T_CTRL, write_temp_buff, 1 );

    joystick_generic_read( ctx, JOYSTICK_CONTROL1, temp_buffer, 1 );

    temp_data = temp_buffer[ 0 ];
    temp_data &= 0x01;

    write_temp_buff[ 0 ] = JOYSTICK_CONTROL1_RESET_CMD | temp_data;
    
    joystick_generic_write( ctx, JOYSTICK_CONTROL1, write_temp_buff, 1 );
}

void joystick_generic_write ( joystick_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void joystick_generic_read ( joystick_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}


uint8_t joystick_check_id_code ( joystick_t *ctx )
{
    uint8_t temp_buffer[ 1 ];

    joystick_generic_read( ctx, JOYSTICK_ID_CODE, temp_buffer, 1 );

    return ( ( temp_buffer[ 0 ] == JOYSTICK_ID_CODE ) ? 1 : 0 );
}


uint8_t joystick_check_id_version ( joystick_t *ctx )
{
    uint8_t temp_buffer[ 1 ];

    joystick_generic_read( ctx, JOYSTICK_ID_CODE, temp_buffer, 1 );

    return ( ( temp_buffer[ 0 ] == JOYSTICK_ID_VERSION ) ? 1 : 0 );
}

void joystick_set_low_power_mode ( joystick_t *ctx, uint8_t timings )
{
    uint8_t temp_data;
    uint8_t temp_buffer[ 1 ];
    
    timings %= 8;

    joystick_generic_read( ctx, JOYSTICK_CONTROL1, temp_buffer, 1 );

    temp_data = *temp_buffer;
    temp_data &= 0x7F;
    temp_data |= timings << 4;
    
    joystick_generic_write( ctx, JOYSTICK_CONTROL1, &temp_data, 1 );
}

void joystick_set_scaling_factor ( joystick_t *ctx, uint8_t scaling_factor )
{
    if ( scaling_factor < 32 )
    {
        joystick_generic_write( ctx, JOYSTICK_T_CTRL, &scaling_factor, 1 );
    }
    else
    {
        uint8_t write_temp_buff;

        write_temp_buff = JOYSTICK_T_CTRL_SCALING_100_CMD;

        joystick_generic_write( ctx, JOYSTICK_T_CTRL, &write_temp_buff, 1 );
    }
}

void joystick_disabled_interrupt( joystick_t *ctx )
{
    uint8_t temp_data;
    uint8_t temp_buffer [ 1 ];
    uint8_t write_temp_buff[ 1 ];

    joystick_generic_read( ctx, JOYSTICK_CONTROL1, temp_buffer, 1 );
    temp_data = *temp_buffer;
    temp_data &= 0x04;

    write_temp_buff[ 0 ] = JOYSTICK_CONTROL1_RESET_CMD | temp_data;

    joystick_generic_write( ctx, JOYSTICK_CONTROL1, &write_temp_buff, 1 );
}

void joystick_enabled_interrupt( joystick_t *ctx )
{
    uint8_t temp_data;

    joystick_generic_read( ctx, JOYSTICK_CONTROL1, &temp_data, 1 );

    temp_data |= 0x04;
    temp_data = JOYSTICK_CONTROL1_RESET_CMD | temp_data;

    
    joystick_generic_write( ctx, JOYSTICK_CONTROL1, &temp_data, 1 );
}

void joystick_invert_spinning( joystick_t *ctx )
{
    uint8_t temp_data [ 1 ];
    temp_data[ 0 ] = JOYSTICK_INVERT_SPINING_CMD;

    joystick_generic_write( ctx, JOYSTICK_CONTROL2, &temp_data, 1 );  //proveri
}

uint8_t joystick_get_position( joystick_t *ctx )
{
    int8_t ox;
    int8_t oy;
    uint8_t position;
    uint8_t temp_buffer_1[ 1 ];
    uint8_t temp_buffer_2[ 1 ];


    position = 0;

    joystick_generic_read( ctx, JOYSTICK_X, &temp_buffer_1, 1 );
    ox = *temp_buffer_1;
    com_delay( );

    joystick_generic_read( ctx, JOYSTICK_Y_RES_INT, &temp_buffer_2, 1 );
    oy = *temp_buffer_2;
    com_delay( );
    
    if ( ox <= -60 )
    {
        // right
        position = 3;
    }
    
    if ( ox >= 60 )
    {
        // left
        position = 7;
    }
    
    if ( oy >= 60 )
    {
        if ( ( ox < 20 ) && ( ox >= -20 ) )
        {
            // top
            position = 1;
        }
    }
    
    if ( oy <= -60 )
    {
        if ( ( ox <= 20 ) && ( ox >= -20 ) )
        {
            // bottom
            position = 5;
        }
    }
    
    if ( ( ox < -20 ) && ( ox > -60 ) )
    {
        if ( oy > 20 )
        {
            // top-right
            position = 2;
        }
        else
        {
            // bottom-right
            position = 4;
        }
    }
    
    if ( ( ox < 60 ) && ( ox > 20 ) )
    {
        if ( oy < -20 )
        {
            // top-left
            position = 6;
        }
        else
        {
            // bottom-left
            position = 8;
        }
    }

    return position;
}

uint8_t joystick_get_interrupt ( joystick_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t joystick_press_button ( joystick_t *ctx )
{
    return digital_in_read( &ctx->tst );
}

void joystick_soft_reset ( joystick_t *ctx )
{
    uint8_t buffer;
    uint8_t temp_buffer[ 1 ];

    joystick_generic_read( ctx, JOYSTICK_CONTROL1, &temp_buffer, 1 );
    buffer = temp_buffer[ 0 ];
    buffer &= 0x01;
    buffer = JOYSTICK_CONTROL1_RESET_CMD | buffer;

    joystick_generic_write( ctx, JOYSTICK_CONTROL1, &buffer, 1 );
}

void joystick_hardware_reset( joystick_t *ctx )
{
    digital_out_write( &ctx->rst, 0 );
    com_delay( );
    digital_out_write( &ctx->rst, 1 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void com_delay ( void )
{
    Delay_10us();
}

// ------------------------------------------------------------------------- END

