/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file dht22.c
 * @brief DHT22 Click Driver.
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

    Delay_1ms( );
    Delay_1ms( );

    digital_out_high( &ctx->sda_out );

    return DHT22_OK;
}

err_t dht22_check_sensor_response ( dht22_t *ctx )
{
    if ( ctx->sda_in_stat == DIGITAL_IN_UNSUPPORTED_PIN )
    {
        return DHT22_ERROR;
    }

    while ( digital_in_read( &ctx->sda_in ) );
    
    while ( !digital_in_read( &ctx->sda_in ) );

    while ( digital_in_read( &ctx->sda_in ) );

    return DHT22_OK;
}

err_t dht22_get_sensor_data ( dht22_t *ctx, uint16_t *hum_data, uint16_t *temp_data )
{
    uint8_t read_buffer[ 5 ] = { 0 };
    uint8_t tim_cnt = 0;
    uint8_t sensor_byte_buffer = 0;

    for ( uint8_t cnt_i = 0; cnt_i < 5; cnt_i++ )
    {
        sensor_byte_buffer = 0;
        for ( uint8_t cnt_j = 0; cnt_j < 8; cnt_j++ )
        {
            tim_cnt = 0;
            while ( !digital_in_read( &ctx->sda_in ) );
            
            while ( digital_in_read( &ctx->sda_in ) )
            {
                Delay_10us( );
                tim_cnt++;
            }
            
            sensor_byte_buffer <<= 1;
            if( tim_cnt > 3 )
            {
                sensor_byte_buffer |= 1;
            }
        }
        read_buffer[ cnt_i ] = sensor_byte_buffer;
    }
    
    *hum_data = read_buffer[ 0 ];
    *hum_data <<= 8;
    *hum_data |= read_buffer[ 1 ];
    
    *temp_data = read_buffer[ 2 ];
    *temp_data <<= 8;
    *temp_data |= read_buffer[ 3 ];

    return DHT22_OK;
}

err_t dht22_get_measurement_data ( dht22_t *ctx, float *humidity, float *temperature ) 
{
    uint16_t hum_data = 0, temp_data = 0;
    err_t err_flag = dht22_get_sensor_data( ctx, &hum_data, &temp_data );
    *humidity = ( float ) hum_data;
    *humidity /= 10.0;
    *temperature = ( float ) temp_data;
    *temperature /= 10.0;
    
    return err_flag;
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
