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
 * @file magneticrotary5.c
 * @brief Magnetic Rotary 5 Click Driver.
 */

#include "magneticrotary5.h"

void magneticrotary5_cfg_setup ( magneticrotary5_cfg_t *cfg ) 
{
    cfg->ddclk = HAL_PIN_NC;
    cfg->cs    = HAL_PIN_NC;
    cfg->dio   = HAL_PIN_NC;
    cfg->an    = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = MAGNETICROTARY5_VREF_3V3;
}

err_t magneticrotary5_init ( magneticrotary5_t *ctx, magneticrotary5_cfg_t *cfg ) 
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->ddclk, cfg->ddclk );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_low ( &ctx->ddclk );
    digital_out_low ( &ctx->cs );
    ctx->dio = cfg->dio;

    return MAGNETICROTARY5_OK;
}

err_t magneticrotary5_default_cfg ( magneticrotary5_t *ctx ) 
{
    err_t error_flag = MAGNETICROTARY5_OK;
    error_flag |= magneticrotary5_set_mt_cnt ( ctx, MAGNETICROTARY5_DEFAULT_MT_CNT );
    return error_flag;
}

err_t magneticrotary5_write_cmd ( magneticrotary5_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    if ( ( NULL == data_in ) || ( cmd > MAGNETICROTARY5_CMD_WRITE_OTP ) ||
         ( len < MAGNETICROTARY5_MIN_DATA_LEN ) || ( len > MAGNETICROTARY5_MAX_DATA_LEN ) )
    {
        return MAGNETICROTARY5_ERROR;
    }
    digital_out_t dio_out;
    digital_out_init( &dio_out, ctx->dio );
    digital_out_low ( &dio_out );
    digital_out_high ( &ctx->cs );
    Delay_10us ( );
    // write command
    for ( uint8_t bit_cnt = 5; bit_cnt > 0; bit_cnt-- )
    {
        digital_out_low ( &ctx->ddclk );
        Delay_10us ( );
        
        digital_out_write ( &dio_out, ( ( cmd >> ( bit_cnt - 1 ) ) & 1 ) );

        digital_out_high ( &ctx->ddclk );
        Delay_10us ( );
    }
    // write data
    for ( uint8_t byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        for ( uint8_t bit_cnt = 8; bit_cnt > 0; bit_cnt-- )
        {
            digital_out_low ( &ctx->ddclk );
            Delay_10us ( );
            
            digital_out_write ( &dio_out, ( ( data_in[ byte_cnt ] >> ( bit_cnt - 1 ) ) & 1 ) );
            
            digital_out_high ( &ctx->ddclk );
            Delay_10us ( );
        }
    }
    
    digital_out_low ( &dio_out );
    digital_out_low ( &ctx->ddclk );
    digital_out_low ( &ctx->cs );
    return MAGNETICROTARY5_OK;
}

err_t magneticrotary5_read_cmd ( magneticrotary5_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    if ( ( NULL == data_out ) || ( cmd > MAGNETICROTARY5_CMD_WRITE_OTP ) ||
         ( len < MAGNETICROTARY5_MIN_DATA_LEN ) || ( len > MAGNETICROTARY5_MAX_DATA_LEN ) )
    {
        return MAGNETICROTARY5_ERROR;
    }
    digital_in_t dio_in;
    digital_out_t dio_out;
    digital_out_init( &dio_out, ctx->dio );
    digital_out_low ( &dio_out );
    digital_out_high ( &ctx->cs );
    Delay_10us ( );
    // write command
    for ( uint8_t bit_cnt = 5; bit_cnt > 0; bit_cnt-- )
    {
        digital_out_low ( &ctx->ddclk );
        Delay_10us ( );
        
        digital_out_write ( &dio_out, ( ( cmd >> ( bit_cnt - 1 ) ) & 1 ) );

        digital_out_high ( &ctx->ddclk );
        Delay_10us ( );
    }
    digital_in_init( &dio_in, ctx->dio );
    // read data
    for ( uint8_t byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        data_out[ byte_cnt ] = 0;
        for ( uint8_t bit_cnt = 8; bit_cnt > 0; bit_cnt-- )
        {
            digital_out_low ( &ctx->ddclk );
            Delay_10us ( );
            
            data_out[ byte_cnt ] |= ( digital_in_read ( &dio_in ) << ( bit_cnt - 1 ) );
            
            digital_out_high ( &ctx->ddclk );
            Delay_10us ( );
        }
    }
    
    digital_out_init( &dio_out, ctx->dio );
    digital_out_low ( &dio_out );
    digital_out_low ( &ctx->ddclk );
    digital_out_low ( &ctx->cs );
    return MAGNETICROTARY5_OK;
}

err_t magneticrotary5_read_angle ( magneticrotary5_t *ctx, uint8_t *agc, uint16_t *angle )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = magneticrotary5_read_cmd ( ctx, MAGNETICROTARY5_CMD_RD_ANGLE, data_buf, 2 );
    *agc = ( ( data_buf[ 0 ] >> 1 ) & MAGNETICROTARY5_MASK_AGC_BITS );
    *angle = ( ( uint16_t ) ( data_buf[ 0 ] & MAGNETICROTARY5_MASK_ANGLE_MSB ) << 8 ) | data_buf[ 1 ];
    return error_flag;
}

err_t magneticrotary5_read_mt_cnt ( magneticrotary5_t *ctx, int16_t *mt_cnt )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = magneticrotary5_read_cmd ( ctx, MAGNETICROTARY5_CMD_RD_MT_COUNTER, data_buf, 2 );
    *mt_cnt = ( ( int16_t ) ( ( ( int16_t ) data_buf[ 0 ] << 8 ) | 
                              ( data_buf[ 1 ] & ( MAGNETICROTARY5_MASK_MT_CNT_LSB << 7 ) ) ) >> 7 );
    return error_flag;
}

err_t magneticrotary5_set_mt_cnt ( magneticrotary5_t *ctx, int16_t mt_cnt )
{
    if ( ( mt_cnt < MAGNETICROTARY5_MIN_MT_CNT ) || ( mt_cnt > MAGNETICROTARY5_MAX_MT_CNT ) )
    {
        return MAGNETICROTARY5_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( mt_cnt & MAGNETICROTARY5_MASK_MT_CNT_MSB ) >> 1 );
    data_buf[ 1 ] = ( uint8_t ) ( ( mt_cnt & MAGNETICROTARY5_MASK_MT_CNT_LSB ) << 7 );
    return magneticrotary5_write_cmd ( ctx, MAGNETICROTARY5_CMD_SET_MT_COUNTER, data_buf, 2 );
}

err_t magneticrotary5_read_raw_adc ( magneticrotary5_t *ctx, uint16_t *raw_adc )
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t magneticrotary5_read_voltage ( magneticrotary5_t *ctx, float *voltage )
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t magneticrotary5_set_vref ( magneticrotary5_t *ctx, float vref )
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

// ------------------------------------------------------------------------- END
