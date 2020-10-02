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

#include "illuminance.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void illuminance_cfg_setup ( illuminance_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ILLUMINANCE_TSL2561_I2C_ADDR_HIGH;
}

ILLUMINANCE_RETVAL illuminance_init ( illuminance_t *ctx, illuminance_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ILLUMINANCE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return ILLUMINANCE_OK;
}

void illuminance_default_cfg ( illuminance_t *ctx )
{
    // Power On
    illuminance_write_data( ctx, ILLUMINANCE_TSL2561_COMMAND_BIT | 
                                 ILLUMINANCE_TSL2561_REGISTER_CONTROL,                               
                                 ILLUMINANCE_TSL2561_CONTROL_POWERON );

    illuminance_write_data( ctx, ILLUMINANCE_TSL2561_COMMAND_BIT |
                                 ILLUMINANCE_TSL2561_REGISTER_TIMING,
                                 ILLUMINANCE_TSL2561_INTEGRATIONTIME_402MS );
}

void illuminance_generic_write ( illuminance_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void illuminance_generic_read ( illuminance_t *ctx, uint8_t reg, uint8_t *data_buf,
                                uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void illuminance_write_data ( illuminance_t *ctx, uint8_t address, uint8_t write_command )
{
    uint8_t write_data;

    write_data = write_command;
    illuminance_generic_write( ctx, address, &write_data, 1 );
}

uint8_t illuminance_read_data ( illuminance_t *ctx, uint8_t address )
{
    uint8_t read_data[ 1 ];

    illuminance_generic_read( ctx, address, read_data, 1 ); 

    return read_data[ 0 ];
}

void illuminance_get_result ( illuminance_t *ctx, uint16_t *value_ch0, uint16_t *value_ch1 )
{
    uint16_t result;
    uint8_t buffer0[ 2 ];
    uint8_t buffer1[ 2 ];

    buffer0[ 0 ] = illuminance_read_data( ctx, ILLUMINANCE_TSL2561_COMMAND_BIT | 
                                               ILLUMINANCE_TSL2561_REGISTER_CHAN0_LOW );
    buffer0[ 1 ] = illuminance_read_data( ctx, ILLUMINANCE_TSL2561_COMMAND_BIT | 
                                             ILLUMINANCE_TSL2561_REGISTER_CHAN0_HIGH );
    
    buffer1[ 0 ] = illuminance_read_data( ctx, ILLUMINANCE_TSL2561_COMMAND_BIT | 
                                               ILLUMINANCE_TSL2561_REGISTER_CHAN1_LOW );
    buffer1[ 1 ] = illuminance_read_data( ctx, ILLUMINANCE_TSL2561_COMMAND_BIT |
                                               ILLUMINANCE_TSL2561_REGISTER_CHAN1_HIGH );

    result = 0x00;
    result = buffer0[ 1 ];
    result <<= 8;
    result |= buffer0[ 0 ];
    
    *value_ch0 = result;

    result = 0x00;
    result = buffer1[ 1 ];
    result <<= 8;
    result |= buffer1[ 0 ];
    
    *value_ch1 = result;
}

uint16_t illuminance_calculate_lux( uint16_t value_gain, uint16_t value_int, uint16_t ch0,
                                    uint16_t ch1 )
{
    uint32_t ch_scale;
    uint32_t channel0;
    uint32_t channel1;
    uint32_t temp;
    uint32_t lux;
    uint32_t ratio;
    uint32_t ratio1;
    uint16_t b;
    uint16_t m;
  
    ratio1 = 0;

    switch ( value_int )
    {
        case 0: 
        {
            ch_scale = ILLUMINANCE_TSL2561_CHSCALE_TINT0;
            break;
        }
        case 1:  
        {
            ch_scale = ILLUMINANCE_TSL2561_CHSCALE_TINT1;
            break;
        }
        default:
        {
            ch_scale = ( 1 << ILLUMINANCE_TSL2561_CH_SCALE );
            break;
        }
    }

    if ( !value_gain )
    {
        ch_scale = ch_scale << 4;
    }
    
    channel0 = ( ch0 * ch_scale ) >> ILLUMINANCE_TSL2561_CH_SCALE;
    channel1 = ( ch1 * ch_scale ) >> ILLUMINANCE_TSL2561_CH_SCALE;

    if ( channel0 != 0 )
    {
        ratio1 = (channel1 << ( ILLUMINANCE_TSL2561_RATIO_SCALE +1 )) / channel0;
    }
    
    ratio = (ratio1 + 1) >> 1;

    if ( ( ratio >= 0 ) && ( ratio <= ILLUMINANCE_TSL2561_K1T ) )
    {
         b = ILLUMINANCE_TSL2561_B1T;
         m = ILLUMINANCE_TSL2561_M1T;
    }
    else if ( ratio <= ILLUMINANCE_TSL2561_K2T )
    {
        b = ILLUMINANCE_TSL2561_B2T;
        m = ILLUMINANCE_TSL2561_M2T;
    }
    else if ( ratio <= ILLUMINANCE_TSL2561_K3T )
    {
        b = ILLUMINANCE_TSL2561_B3T;
        m = ILLUMINANCE_TSL2561_M3T;
    }
    else if ( ratio <= ILLUMINANCE_TSL2561_K4T )
    {
        b = ILLUMINANCE_TSL2561_B4T;
        m = ILLUMINANCE_TSL2561_M4T;
    }
    else if ( ratio <= ILLUMINANCE_TSL2561_K5T )
    {
        b = ILLUMINANCE_TSL2561_B5T;
        m = ILLUMINANCE_TSL2561_M5T;
    }
    else if ( ratio <= ILLUMINANCE_TSL2561_K6T )
    {
        b = ILLUMINANCE_TSL2561_B6T;
        m = ILLUMINANCE_TSL2561_M6T;
    }
    else if ( ratio <= ILLUMINANCE_TSL2561_K7T )
    {
        b = ILLUMINANCE_TSL2561_B7T;
        m = ILLUMINANCE_TSL2561_M7T;
    }
    else if ( ratio > ILLUMINANCE_TSL2561_K8T )
    {
        b = ILLUMINANCE_TSL2561_B8T;
        m = ILLUMINANCE_TSL2561_M8T;
    }

    temp = ( ( channel0 * b ) - ( channel1 * m ) );

    if ( temp < 0 )
    {
        temp = 0;
    }

    temp = temp + ( 1 << ( ILLUMINANCE_TSL2561_LUX_SCALE - 1 ) );
    lux = temp >> ILLUMINANCE_TSL2561_LUX_SCALE;
    
    return lux ;
}

uint8_t illuminance_get_interrupt( illuminance_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

