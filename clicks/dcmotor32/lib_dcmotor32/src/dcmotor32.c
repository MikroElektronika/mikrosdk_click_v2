/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file dcmotor32.c
 * @brief DC Motor 32 Click Driver.
 */

#include "dcmotor32.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief DC Motor 32 spi select function.
 * @details This function selects the SPI device by clearing the CS pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void dcmotor32_spi_select ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 spi deselect function.
 * @details This function deselects the SPI device by setting the CS pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void dcmotor32_spi_deselect ( dcmotor32_t *ctx );

/**
 * @brief DC Motor 32 spi write function.
 * @details This function writes a desired number of data bytes to SPI interface using bit-banging.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return None.
 * @note None.
 */
static void dcmotor32_spi_write ( dcmotor32_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief DC Motor 32 spi read function.
 * @details This function reads a desired number of data bytes from SPI interface using bit-banging.
 * @param[in] ctx : Click context object.
 * See #dcmotor32_t object definition for detailed explanation.
 * @param[out] data_out : Output data read.
 * @param[in] len : Number of bytes to be read.
 * @return None.
 * @note None.
 */
static void dcmotor32_spi_read ( dcmotor32_t *ctx, uint8_t *data_out, uint8_t len );

void dcmotor32_cfg_setup ( dcmotor32_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->is_pin = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = DCMOTOR32_VREF_DEFAULT;
}

err_t dcmotor32_init ( dcmotor32_t *ctx, dcmotor32_cfg_t *cfg ) 
{
    err_t error_flag = DCMOTOR32_OK;
    
    error_flag |= digital_out_init( &ctx->sck, cfg->sck );
    error_flag |= digital_out_init( &ctx->mosi, cfg->mosi );
    error_flag |= digital_out_init( &ctx->cs, cfg->cs );

    error_flag |= digital_in_init( &ctx->miso, cfg->miso );
    Delay_100ms ( );

    digital_out_low ( &ctx->cs );
    digital_out_low ( &ctx->sck );
    digital_out_low ( &ctx->mosi );
    Delay_100ms ( );

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->is_pin;

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

    return DCMOTOR32_OK;
}

err_t dcmotor32_default_cfg ( dcmotor32_t *ctx ) 
{
    err_t error_flag = DCMOTOR32_OK;
    ctx->control = 0;
    dcmotor32_set_operation_mode ( ctx, DCMOTOR32_CONTROL_MODE_PD_GND_OUT );
    if ( DCMOTOR32_OK != dcmotor32_enable_isense ( ctx ) )
    {
        return DCMOTOR32_ERROR;
    }
    error_flag |= dcmotor32_set_slow_slew_rate ( ctx );
    error_flag |= dcmotor32_enable_device ( ctx );
    error_flag |= dcmotor32_calib_offset ( ctx );

    return error_flag;
}

err_t dcmotor32_set_control ( dcmotor32_t *ctx, uint8_t control )
{
    err_t error_flag = DCMOTOR32_OK;
    uint8_t control_read = 0;
    ctx->control = ( control & ( ~DCMOTOR32_CONTROL_SDO_SEL_MASK ) ) | DCMOTOR32_CONTROL_SDO_SEL_CONTROL;
    dcmotor32_spi_select ( ctx );
    dcmotor32_spi_write ( ctx, &ctx->control, 1 );
    dcmotor32_spi_read ( ctx, &control_read, 1 );
    dcmotor32_spi_deselect ( ctx );
    if ( control_read != ctx->control )
    {
        error_flag |= DCMOTOR32_ERROR;
    }
    Delay_10ms ( );
    return error_flag;
}

err_t dcmotor32_get_status ( dcmotor32_t *ctx )
{
    err_t error_flag = DCMOTOR32_OK;
    ctx->control = ( ctx->control & ( ~DCMOTOR32_CONTROL_SDO_SEL_MASK ) ) | DCMOTOR32_CONTROL_SDO_SEL_STATUS;
    dcmotor32_spi_select ( ctx );
    dcmotor32_spi_write ( ctx, &ctx->control, 1 );
    dcmotor32_spi_read ( ctx, &ctx->status, 1 );
    dcmotor32_spi_deselect ( ctx );
    if ( DCMOTOR32_STATUS_SDO_SEL_STATUS != ( ctx->status & DCMOTOR32_STATUS_SDO_SEL_MASK ) )
    {
        error_flag = DCMOTOR32_ERROR;
    }
    Delay_10ms ( );
    return error_flag;
}

err_t dcmotor32_set_operation_mode ( dcmotor32_t *ctx, uint8_t mode )
{
    ctx->control = ( ctx->control & ( ~DCMOTOR32_CONTROL_MODE_MASK ) ) | ( mode & DCMOTOR32_CONTROL_MODE_MASK );
    return dcmotor32_set_control ( ctx, ctx->control );
}

err_t dcmotor32_enable_isense ( dcmotor32_t *ctx )
{
    ctx->control = ( ctx->control & ( ~DCMOTOR32_CONTROL_CURRENT_SENSE_MASK ) ) | DCMOTOR32_CONTROL_CURRENT_SENSE_ENABLE;
    return dcmotor32_set_control ( ctx, ctx->control );
}

err_t dcmotor32_disable_isense ( dcmotor32_t *ctx )
{
    ctx->control = ( ctx->control & ( ~DCMOTOR32_CONTROL_CURRENT_SENSE_MASK ) ) | DCMOTOR32_CONTROL_CURRENT_SENSE_DISABLE;
    return dcmotor32_set_control ( ctx, ctx->control );
}

err_t dcmotor32_set_fast_slew_rate ( dcmotor32_t *ctx )
{
    ctx->control = ( ctx->control & ( ~DCMOTOR32_CONTROL_SLEW_RATE_MASK ) ) | DCMOTOR32_CONTROL_SLEW_RATE_FAST;
    return dcmotor32_set_control ( ctx, ctx->control );
}

err_t dcmotor32_set_slow_slew_rate ( dcmotor32_t *ctx )
{
    ctx->control = ( ctx->control & ( ~DCMOTOR32_CONTROL_SLEW_RATE_MASK ) ) | DCMOTOR32_CONTROL_SLEW_RATE_SLOW;
    return dcmotor32_set_control ( ctx, ctx->control );
}

err_t dcmotor32_enable_device ( dcmotor32_t *ctx )
{
    ctx->control = ( ctx->control & ( ~DCMOTOR32_CONTROL_EN_MASK ) ) | DCMOTOR32_CONTROL_EN_ENABLE;
    return dcmotor32_set_control ( ctx, ctx->control );
}

err_t dcmotor32_disable_device ( dcmotor32_t *ctx )
{
    ctx->control = ( ctx->control & ( ~DCMOTOR32_CONTROL_EN_MASK ) ) | DCMOTOR32_CONTROL_EN_DISABLE;
    return dcmotor32_set_control ( ctx, ctx->control );
}

err_t dcmotor32_read_adc_raw ( dcmotor32_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t dcmotor32_read_adc_volt ( dcmotor32_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t dcmotor32_read_adc_volt_avg ( dcmotor32_t *ctx, uint16_t num_conv, float *volt_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( DCMOTOR32_OK == dcmotor32_read_adc_volt ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            timeout_cnt = 0;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > DCMOTOR32_TIMEOUT_MS )
        {
            return DCMOTOR32_ERROR;
        }
    }
    *volt_avg = ( voltage_sum / num_conv );
    return DCMOTOR32_OK;
}

err_t dcmotor32_set_adc_vref ( dcmotor32_t *ctx, float vref ) 
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

err_t dcmotor32_calib_offset ( dcmotor32_t *ctx )
{
    float voltage = 0;
    Delay_1sec ( );
    err_t error_flag = dcmotor32_read_adc_volt_avg ( ctx, DCMOTOR32_NUM_CONVERSIONS, &voltage );
    ctx->zero_curr_offset = voltage;
    return error_flag;
}

err_t dcmotor32_get_out_current ( dcmotor32_t *ctx, float *current )
{
    float voltage = 0;
    err_t error_flag = dcmotor32_read_adc_volt_avg ( ctx, DCMOTOR32_NUM_CONVERSIONS, &voltage );
    if ( ( DCMOTOR32_OK == error_flag ) && ( NULL != current ) )
    {
        voltage -= ctx->zero_curr_offset;
        if ( voltage < 0 )
        {
            voltage = 0;
        }
        *current = voltage / ( DCMOTOR32_R9 / ( DCMOTOR32_R8 + DCMOTOR32_R9 ) );
    }
    return error_flag;
}

static void dcmotor32_spi_select ( dcmotor32_t *ctx )
{
    Delay_50us ( );
    digital_out_high ( &ctx->cs );
    Delay_50us ( );
}

static void dcmotor32_spi_deselect ( dcmotor32_t *ctx )
{
    Delay_50us ( );
    digital_out_low ( &ctx->cs );
    Delay_50us ( );
}

static void dcmotor32_spi_write ( dcmotor32_t *ctx, uint8_t *data_in, uint8_t len )
{
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( data_in[ byte_cnt ] & ( 0x80 >> bit_cnt ) )
            {
                digital_out_high ( &ctx->mosi );
            }
            else
            {
                digital_out_low ( &ctx->mosi );
            }
            digital_out_high ( &ctx->sck );
            Delay_50us ( );
            digital_out_low ( &ctx->sck );
            Delay_50us ( );
        }
        digital_out_low ( &ctx->mosi );
        Delay_50us ( );
    }
}

static void dcmotor32_spi_read ( dcmotor32_t *ctx, uint8_t *data_out, uint8_t len )
{
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        data_out[ byte_cnt ] = 0;
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( ctx->control & ( 0x80 >> bit_cnt ) )
            {
                digital_out_high ( &ctx->mosi );
            }
            else
            {
                digital_out_low ( &ctx->mosi );
            }
            digital_out_high ( &ctx->sck );
            Delay_50us ( );

            digital_out_low ( &ctx->sck );
            Delay_50us ( );
            data_out[ byte_cnt ] |= ( ( !!digital_in_read ( &ctx->miso ) ) << ( 7 - bit_cnt ) );
        }
        Delay_50us ( );
    }
}

// ------------------------------------------------------------------------- END
