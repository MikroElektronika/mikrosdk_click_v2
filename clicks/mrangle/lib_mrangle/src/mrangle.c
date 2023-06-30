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
 * @file mrangle.c
 * @brief MR Angle Click Driver.
 */

#include "mrangle.h"

// ------------------------------------------------------------- PRIVATE MACROS

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                               0x00

/**
 * @brief SPI start bit.
 * @details Definition of SPI start bit.
 */
#define START_BIT                           0x06

/**
 * @brief ADC resolution.
 * @details Resolution of adc.
 */
#define ADC_RESOLUTION                      4095

/**
 * @brief ADC power supply value.
 * @details Power supply voltage value of adc.
 */
#define ADC_VREF_3300_mV                    3.3
#define ADC_VREF_5000_mV                    5.0

/**
 * @brief Degrees range constant.
 * @details Conversion constant from radian to degrees.
 */
#define ADC_CONV_DEG                        180

/**
 * @brief Degrees range constant.
 * @details Conversion constant from radian to degrees.
 */
#define LIN_FUN_COEFF_GRADIENT              0.00325
#define LIN_FUN_COEFF_VERTICAL_INTERCEPT    0.22

/**
 * @brief ADC channel constant.
 * @details ADC channel constant reads a desired ADC channel function.
 */
#define MRANGLE_ADC_CH0                     0x00
#define MRANGLE_ADC_CH1                     0x40
#define MRANGLE_ADC_CH2                     0x80

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Conversion delay.
 * @details Conversion delay for 1 millisecond.
 */
static void dev_conv_delay ( void );

/**
 * @brief Reset delay.
 * @details Reset delay for 100 millisecond.
 */
static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mrangle_cfg_setup ( mrangle_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->tce = HAL_PIN_NC;
    cfg->pdn = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->vref = ADC_VREF_3300_mV;
}

err_t mrangle_init ( mrangle_t *ctx, mrangle_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->tce, cfg->tce );
    digital_out_init( &ctx->pdn, cfg->pdn );
    
    ctx->vref = cfg->vref;

    return SPI_MASTER_SUCCESS;
}

void mrangle_default_cfg ( mrangle_t *ctx ) 
{
    mrangle_powerdown_mode( ctx, POWERDOWN_MODE_DISABLE );
    dev_reset_delay( );
    
    mrangle_output_mode( ctx, OUTPUT_MODE_VOUT_SIN_COS );
    dev_reset_delay( );
}

void mrangle_powerdown_mode ( mrangle_t *ctx, mrangle_powerdown_mode_value_t pd_mode ) 
{
    digital_out_write( &ctx->pdn, pd_mode );
}

void mrangle_output_mode ( mrangle_t *ctx, mrangle_output_mode_value_t output_mode ) 
{
    digital_out_write( &ctx->tce, output_mode );
}

err_t mrangle_generic_write ( mrangle_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = MRANGLE_OK;
    spi_master_select_device( ctx->chip_select );
    dev_conv_delay( );
    error_flag |= spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mrangle_generic_read ( mrangle_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = MRANGLE_OK;
    spi_master_select_device( ctx->chip_select );
    dev_conv_delay( );
    error_flag |= spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mrangle_get_adc_sin ( mrangle_t *ctx, uint16_t *sin_adc ) 
{
    err_t error_flag = MRANGLE_OK;
    uint8_t tx_data = 0;
    uint8_t rx_data[ 2 ] = { 0 };

    tx_data = START_BIT;
    
    spi_master_select_device( ctx->chip_select ); 
    dev_conv_delay( );
    error_flag |= spi_master_write( &ctx->spi, &tx_data, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, MRANGLE_ADC_CH0 );
    error_flag |= spi_master_read( &ctx->spi, rx_data, 2 );
    spi_master_deselect_device( ctx->chip_select );
    dev_conv_delay( );
    
    *sin_adc = ( ( uint16_t ) rx_data[ 0 ] << 8 ) | rx_data[ 1 ];

    return error_flag;
}

err_t mrangle_get_sin ( mrangle_t *ctx, float *sin ) 
{
    uint16_t sin_adc = 0;
    
    err_t error_flag = mrangle_get_adc_sin( ctx, &sin_adc );

    *sin = ( ( float ) sin_adc / ADC_RESOLUTION ) * ctx->vref - ctx->vref / 2;

    return error_flag;
}

err_t mrangle_get_adc_cos ( mrangle_t *ctx, uint16_t *cos_adc ) 
{
    err_t error_flag = MRANGLE_OK;
    uint8_t tx_data = 0;
    uint8_t rx_data[ 2 ] = { 0 };

    tx_data = START_BIT;
    
    spi_master_select_device( ctx->chip_select ); 
    dev_conv_delay( );
    error_flag |= spi_master_write( &ctx->spi, &tx_data, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, MRANGLE_ADC_CH1 );
    error_flag |= spi_master_read( &ctx->spi, rx_data, 2 );
    spi_master_deselect_device( ctx->chip_select );
    dev_conv_delay( );
    
    *cos_adc = ( ( uint16_t ) rx_data[ 0 ] << 8 ) | rx_data[ 1 ];

    return error_flag;
}

err_t mrangle_get_cos ( mrangle_t *ctx, float *cos ) 
{
    uint16_t cos_adc = 0;
    
    err_t error_flag = mrangle_get_adc_cos( ctx, &cos_adc );

    *cos = ( ( float ) cos_adc / ADC_RESOLUTION ) * ctx->vref - ctx->vref / 2;

    return error_flag;
}

err_t mrangle_get_adc_temp ( mrangle_t *ctx, uint16_t *temp_adc ) 
{
    err_t error_flag = MRANGLE_OK;
    uint8_t tx_data = 0;
    uint8_t rx_data[ 2 ] = { 0 };
    
    tx_data = START_BIT;
    
    spi_master_select_device( ctx->chip_select ); 
    dev_conv_delay( );
    error_flag |= spi_master_write( &ctx->spi, &tx_data, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, MRANGLE_ADC_CH2 );
    error_flag |= spi_master_read( &ctx->spi, rx_data, 2 );
    spi_master_deselect_device( ctx->chip_select );
    dev_conv_delay( );
    
    *temp_adc = ( ( uint16_t ) rx_data[ 0 ] << 8 ) | rx_data[ 1 ];

    return error_flag;
}

err_t mrangle_get_temperature ( mrangle_t *ctx, float *temperature ) 
{
    uint16_t temp_adc = 0;
    float tmp = 0;
    float v_temp = 0;
    
    mrangle_output_mode( ctx, OUTPUT_MODE_VOUT_TEMP );
    dev_conv_delay( );

    err_t error_flag = mrangle_get_adc_temp( ctx, &temp_adc );
    
    mrangle_output_mode( ctx, OUTPUT_MODE_VOUT_TEMP );
    dev_conv_delay( );
    
    v_temp = ( float ) temp_adc;
    v_temp /= ADC_RESOLUTION;
    v_temp *= ctx->vref;
    
    tmp = ( float ) v_temp;
    tmp /= ctx->vref;
    
    tmp -= LIN_FUN_COEFF_VERTICAL_INTERCEPT;
    tmp /= LIN_FUN_COEFF_GRADIENT;
    
    *temperature = tmp;

    return error_flag;
}

err_t mrangle_get_angle ( mrangle_t *ctx, float *angle ) 
{
    err_t error_flag = MRANGLE_OK;
    float v_sin = 0;
    float v_cos = 0;
    float tmp = 0;
    
    error_flag |= mrangle_get_sin( ctx, &v_sin );
    
    error_flag |= mrangle_get_cos( ctx, &v_cos );
    
    tmp = atan2( v_cos, v_sin );
    tmp *= ADC_CONV_DEG;
    tmp /= TWO_PI;
    
    if ( tmp < 0 ) 
    {
        tmp += ADC_CONV_DEG;    
    }
    
    *angle = tmp;
    
    return error_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_conv_delay ( void ) 
{
    Delay_1ms( );
}

static void dev_reset_delay ( void ) 
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
