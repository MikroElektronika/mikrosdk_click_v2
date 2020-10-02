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

#include "dht22.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dht22_cfg_setup ( dht22_cfg_t *cfg )
{
    // Additional gpio pins

    cfg-> sd11   = HAL_PIN_NC;
    cfg-> sd12   = HAL_PIN_NC;
    cfg->sd2 = HAL_PIN_NC;
}

DHT22_RETVAL dht22_init ( dht22_t *ctx, dht22_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->sd12, cfg->sd12 );

    // Input pins

    digital_in_init( &ctx->sd11, cfg->sd11 );
    digital_in_init( &ctx->sd2, cfg->sd2 );

    return DHT22_OK;
}

void dht22_start_signal ( dht22_t *ctx )
{
    uint8_t timeout;

    digital_out_high( &ctx->sd12 );

    Delay_100ms( );

    digital_out_low( &ctx->sd12 );

    Delay_1ms( );
    Delay_1ms( );

    digital_out_high( &ctx->sd12 );
}

uint8_t dht22_check_sensor_response ( dht22_t *ctx )
{
    uint8_t timeout;

    timeout = 200;

    while ( digital_in_read( &ctx->sd11 ) )
    {
        Delay_1us( );

        if ( !timeout-- )
            return 0;
    }
    
    while ( !digital_in_read( &ctx->sd11 ) )
        Delay_1us( );

    while ( digital_in_read( &ctx->sd11 ) )
        Delay_1us( );
    
    return 1;
}

uint32_t dht22_get_sensor_data ( dht22_t *ctx )
{
    uint8_t cnt_i ;
    uint8_t cnt_j ;
    uint8_t sensor_byte_buffer;
    uint32_t result;
    uint8_t read_buffer[ 5 ];
    
    result = 0x00000000;
    
    for ( cnt_i = 0; cnt_i < 5; cnt_i++ )
    {
        for ( cnt_j = 1; cnt_j <= 8; cnt_j++ )
                {
            while ( !digital_in_read( &ctx->sd11 ) )
                Delay_1us( );

            Delay_10us( );
            Delay_10us( );
            Delay_10us( );

            sensor_byte_buffer <<= 1;

            if ( digital_in_read( &ctx->sd11 ) )
            {
                sensor_byte_buffer |= 1;

                Delay_22us( );
                Delay_22us( );
                Delay_1us( );

                while ( digital_in_read( &ctx->sd11 ) )
                    Delay_1us( );

            }
        }

    read_buffer[ cnt_i ] = sensor_byte_buffer;
    
    }

    result = read_buffer[ 0 ];
    result <<= 8;
    result |= read_buffer[ 1 ];
    result <<= 8;
    result |= read_buffer[ 2 ];
    result <<= 8;
    result |= read_buffer[ 3 ];

    return result;
}

uint16_t dht22_calculate_temperature ( dht22_t *ctx, uint32_t sensor_data )
{
    uint16_t temperature;

    temperature = ( uint16_t ) sensor_data ;
    
    return temperature;
}

float dht22_calc_temp_c ( dht22_t *ctx, uint32_t sensor_data )
{
    uint16_t temp_data;
    float result;
    
    result = 0.0;

    temp_data = ( uint16_t ) sensor_data ;
    
    result = temp_data / 10.0;

    return result;
}

uint16_t dht22_calculate_humidity ( dht22_t *ctx, uint32_t sensor_data )
{
    uint16_t humidity;

    humidity = ( uint16_t ) ( sensor_data >> 16 );

    return humidity;
}

float dht22_calc_humidity ( dht22_t *ctx, uint32_t sensor_data )
{
    uint16_t hum_data;
    float result;

    result = 0.0;

    hum_data = ( uint16_t ) sensor_data ;

    result = hum_data / 10.0;

    return result;
}

void cs_input ( dht22_t *ctx, dht22_cfg_t *cfg )
{
    digital_in_init( &ctx->sd11, cfg->sd11 );
}

void cs_output ( dht22_t *ctx, dht22_cfg_t *cfg )
{
    digital_out_init( &ctx->sd12, cfg->sd12 );
}

// ------------------------------------------------------------------------- END

