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

void dht22_cfg_setup ( dht22_cfg_t *cfg )
{
    cfg->sd1 = HAL_PIN_NC;
    cfg->sd2 = HAL_PIN_NC;

    cfg->sda_sel = DHT22_SDA_SEL_SDA1;
}

err_t dht22_init ( dht22_t *ctx, dht22_cfg_t *cfg )
{
    ctx->sd1 = cfg->sd1;
    ctx->sd2 = cfg->sd2;

    ctx->sda_sel = cfg->sda_sel;

    ctx->sda_out_stat = DIGITAL_OUT_UNSUPPORTED_PIN;
    ctx->sda_in_stat = DIGITAL_IN_UNSUPPORTED_PIN;

    if ( ( cfg->sd1 == HAL_PIN_NC ) && ( cfg->sd2 == HAL_PIN_NC ) )
    {
        return DHT22_ERROR;
    }

    return DHT22_OK;
}

err_t dht22_start_signal ( dht22_t *ctx )
{
    if ( ctx->sda_out_stat == DIGITAL_OUT_UNSUPPORTED_PIN )
    {
        return DHT22_ERROR;
    }

    digital_out_low( &ctx->sda_out );

    Delay_500us( );
    Delay_50us( );

    digital_out_high( &ctx->sda_out );

    return DHT22_OK;
}

err_t dht22_check_sensor_response ( dht22_t *ctx, uint8_t *check_out )
{
    if ( ctx->sda_in_stat == DIGITAL_IN_UNSUPPORTED_PIN )
    {
        return DHT22_ERROR;
    }

    Delay_10us( );
    Delay_10us( );
    Delay_10us( );

    uint8_t timeout = 100;

    while ( !digital_in_read( &ctx->sda_in ) )
    {
        Delay_1us( );

        if ( !timeout-- )
        {
            *check_out = DHT22_RESP_NOT_READY;

            return DHT22_OK;
        }
    }

    timeout = 100;

    while ( digital_in_read( &ctx->sda_in ) )
    {
        Delay_1us( );

        if ( !timeout-- )
        {
            *check_out = DHT22_RESP_NOT_READY;

            return DHT22_OK;
        }
    }

    *check_out = DHT22_RESP_READY;

    return DHT22_OK;
}

err_t dht22_get_sensor_data ( dht22_t *ctx, uint32_t *data_out )
{
    if ( ctx->sda_in_stat == DIGITAL_IN_UNSUPPORTED_PIN )
    {
        return DHT22_ERROR;
    }

    uint8_t sensor_byte_buffer = 0;
    uint8_t read_buffer[ 5 ];

    for ( uint8_t cnt_i = 0; cnt_i < 5; cnt_i++ )
    {
        for ( uint8_t cnt_j = 1; cnt_j <= 8; cnt_j++ )
        {
            while ( !digital_in_read( &ctx->sda_in ) );

            uint8_t tim_cnt = 0;

            while ( digital_in_read( &ctx->sda_in ) )
            {
                Delay_1us( );
                tim_cnt++;
            }

            sensor_byte_buffer <<= 1;

            if ( tim_cnt > 30 )
            {
                sensor_byte_buffer |= 1;
            }
        }

        read_buffer[ cnt_i ] = sensor_byte_buffer;
    }

    uint32_t results = read_buffer[ 0 ];
    results <<= 8;
    results |= read_buffer[ 1 ];
    results <<= 8;
    results |= read_buffer[ 2 ];
    results <<= 8;
    results |= read_buffer[ 3 ];

    *data_out = results;

    return DHT22_OK;
}

uint16_t dht22_get_temperature ( dht22_t *ctx, uint32_t sensor_data )
{
    return (uint16_t)sensor_data;
}

float dht22_calculate_temperature ( dht22_t *ctx, uint32_t sensor_data )
{
    uint16_t temp_data = dht22_get_temperature( ctx, sensor_data );

    return (float)temp_data / 10;
}

uint16_t dht22_get_humidity ( dht22_t *ctx, uint32_t sensor_data )
{
    return (uint16_t)( sensor_data >> 16 );
}

float dht22_calculate_humidity ( dht22_t *ctx, uint32_t sensor_data )
{
    uint16_t hum_data = dht22_get_humidity( ctx, sensor_data );

    return (float)hum_data / 10;
}

err_t dht22_init_sda_input ( dht22_t *ctx )
{
    if ( ctx->sda_sel == DHT22_SDA_SEL_SDA1 )
    {
        ctx->sda_in_stat = digital_in_init( &ctx->sda_in, ctx->sd1 );
    }
    else
    {
        ctx->sda_in_stat = digital_in_init( &ctx->sda_in, ctx->sd2 );
    }

    ctx->sda_out_stat = DIGITAL_OUT_UNSUPPORTED_PIN;

    return ctx->sda_in_stat;
}

err_t dht22_init_sda_output ( dht22_t *ctx )
{
    if ( ctx->sda_sel == DHT22_SDA_SEL_SDA1 )
    {
        ctx->sda_out_stat = digital_out_init( &ctx->sda_out, ctx->sd1 );
    }
    else
    {
        ctx->sda_out_stat = digital_out_init( &ctx->sda_out, ctx->sd2 );
    }

    ctx->sda_in_stat = DIGITAL_IN_UNSUPPORTED_PIN;

    return ctx->sda_out_stat;
}

// ------------------------------------------------------------------------ END
