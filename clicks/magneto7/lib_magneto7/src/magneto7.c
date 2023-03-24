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

#include "magneto7.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void magneto7_cfg_setup ( magneto7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = MAGNETO7_DEV_ADDR_L;
}

MAGNETO7_RETVAL magneto7_init ( magneto7_t *ctx, magneto7_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return MAGNETO7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return MAGNETO7_OK;

}

MAGNETO7_RETVAL magneto7_default_cfg ( magneto7_t *ctx )
{
    uint8_t rx_buffer[ 3 ];

    magneto7_get_register( ctx, MAGNETO7_INFO_L, rx_buffer, 3 );
    
    if ( rx_buffer[ 0 ] != 0x01 ) 
    {
        return MAGNETO7_INIT_ERROR;
    }
    if ( rx_buffer[ 1 ] != 0x01 ) 
    {
        return MAGNETO7_INIT_ERROR;
    }
    
    if ( rx_buffer[ 2 ] != 0x41 ) 
    {
        return MAGNETO7_INIT_ERROR;
    }
     
    rx_buffer[ 0 ] = 0xD8;
    magneto7_set_register( ctx, MAGNETO7_CNTL_1, rx_buffer, 1 );
    
    rx_buffer[ 0 ] = 0x00;
    rx_buffer[ 1 ] = 0x00;
    magneto7_set_register( ctx, MAGNETO7_CNTL_4_L, rx_buffer, 2 );

    Delay_10ms( );
    
    rx_buffer[ 0 ] = 0x08;
    magneto7_set_register( ctx, MAGNETO7_CNTL_2, rx_buffer, 1 );

    Delay_10ms( );

    rx_buffer[ 0 ] = 0x40;
    magneto7_set_register( ctx, MAGNETO7_CNTL_3, rx_buffer, 1 );
    
    rx_buffer[ 0 ] = 0x00;
    magneto7_set_register( ctx, MAGNETO7_AVE_A, rx_buffer, 1 );
    
    ctx->sensor_res = 24;
    
    return MAGNETO7_OK;
}

void magneto7_generic_write ( magneto7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void magneto7_generic_read ( magneto7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t magneto7_int_get ( magneto7_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

MAGNETO7_RETVAL magneto7_get_register ( magneto7_t *ctx, uint8_t register_address, uint8_t * data_buffer, uint8_t n_data )
{
    if ( n_data > 6 ) 
    {
        return MAGNETO7_INIT_ERROR;
    }
    magneto7_generic_read( ctx, register_address, data_buffer,  n_data );

    return MAGNETO7_OK;
}

MAGNETO7_RETVAL magneto7_set_register ( magneto7_t *ctx, uint8_t register_address, uint8_t *data_buffer, uint8_t n_data )
{
    
    if ( n_data > 6 )
    {
        return MAGNETO7_INIT_ERROR;
    }
    
    magneto7_generic_write ( ctx, register_address, data_buffer, n_data );

    return MAGNETO7_OK;
}

MAGNETO7_RETVAL magneto7_set_offset ( magneto7_t *ctx, uint8_t offset_axis, uint8_t offset_value )
{
    uint8_t rx_buffer[ 3 ];

    if ( offset_axis > 2 ) 
    {
        return MAGNETO7_INIT_ERROR;
    }
    if ( offset_value < 1 ) 
    {
        return MAGNETO7_INIT_ERROR;
    }
    
    if ( offset_value > 95 )
    {
        return MAGNETO7_INIT_ERROR;
    }
    
    rx_buffer[ 0 ] = offset_value;
    rx_buffer[ 1 ] = 0x00;
    
    switch ( offset_axis )
    {
        case MAGNETO7_X_AXIS :
        {
            magneto7_set_register( ctx, MAGNETO7_OFF_X_L, rx_buffer, 2 );
            break;
        }
        case MAGNETO7_Y_AXIS :
        {
            magneto7_set_register( ctx, MAGNETO7_OFF_Y_L, rx_buffer, 2 );
            break;
        }
        case MAGNETO7_Z_AXIS :
        {
            magneto7_set_register( ctx, MAGNETO7_OFF_Z_L, rx_buffer, 2 );
            break;
        }
        default :
        {
            break;
        }
    }

    return 0;
}

void magneto7_get_temperature ( magneto7_t *ctx, uint16_t *device_temperature )
{
    uint8_t rx_buffer[ 2 ];

    magneto7_get_register( ctx, MAGNETO7_TEMP_L, rx_buffer, 2 );

    *device_temperature = 0;
    *device_temperature |= rx_buffer[ 1 ];     
    *device_temperature <<= 8;
    *device_temperature |= rx_buffer[ 0 ];
}

void magneto7_get_data ( magneto7_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis )
{
    uint8_t rx_buffer[ 6 ];

    magneto7_get_register( ctx, MAGNETO7_DATA_X_L, rx_buffer, 6 );
    
    *x_axis = 0;
    *x_axis |= rx_buffer[ 1 ];
    *x_axis <<= 8;
    *x_axis |= rx_buffer[ 0 ];
    
    *y_axis = 0;
    *y_axis |= rx_buffer[ 3 ];
    *y_axis <<= 8;
    *y_axis |= rx_buffer[ 2 ];
    
    *z_axis = 0;
    *z_axis |= rx_buffer[ 5 ];
    *z_axis <<= 8;
    *z_axis |= rx_buffer[ 4 ];
}

void magneto7_get_fine_data ( magneto7_t *ctx, uint16_t *x_axis, uint16_t *y_axis, uint16_t *z_axis )
{
    uint8_t rx_buffer[ 6 ];

    magneto7_get_register( ctx, MAGNETO7_FINEOUTPUTX_L, rx_buffer, 6 );

    *x_axis = 0;
    *x_axis |= rx_buffer[ 1 ];
    *x_axis <<= 8;
    *x_axis |= rx_buffer[ 0 ];

    *y_axis = 0;
    *y_axis |= rx_buffer[ 3 ];
    *y_axis <<= 8;
    *y_axis |= rx_buffer[ 2 ];

    *z_axis = 0;
    *z_axis |= rx_buffer[ 5 ];
    *z_axis <<= 8;
    *z_axis |= rx_buffer[ 4 ];
}

float magneto7_convert_to_ut ( magneto7_t *ctx, int16_t raw_data, uint8_t sensor_resolution )
{
    float converted_data;

    switch ( sensor_resolution )
    {
        case 0 :
        {
            ctx->sensor_res = 0.168;
            break;
        }
        case 1 :
        {
            ctx->sensor_res = 0.042;
            break;
        }
        default :
        {
            return 0;
            break;
        }
    }
    
    converted_data = (float)( (float)( raw_data ) * (float)( ctx->sensor_res ) );

    return converted_data;
}

void magneto7_get_gain_para ( magneto7_t *ctx, uint16_t *x_axis, uint16_t *y_axis, uint16_t *z_axis )
{
    uint8_t rx_buffer[ 6 ];

    magneto7_get_register( ctx, MAGNETO7_GAIN_PARA_X_L, rx_buffer, 6 );

    *x_axis = 0;
    *x_axis |= rx_buffer[ 1 ];
    *x_axis <<= 8;
    *x_axis |= rx_buffer[ 0 ];

    *y_axis = 0;
    *y_axis |= rx_buffer[ 3 ];
    *y_axis <<= 8;
    *y_axis |= rx_buffer[ 2 ];

    *z_axis = 0;
    *z_axis |= rx_buffer[ 5 ];
    *z_axis <<= 8;
    *z_axis |= rx_buffer[ 4 ];
}

// ------------------------------------------------------------------------- END

