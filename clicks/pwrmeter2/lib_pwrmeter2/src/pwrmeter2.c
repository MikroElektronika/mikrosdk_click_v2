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

#include "pwrmeter2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWRMETER2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pwrmeter2_cfg_setup ( pwrmeter2_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->md1 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->md0 = HAL_PIN_NC;
    cfg->dr = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t pwrmeter2_init ( pwrmeter2_t *ctx, pwrmeter2_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, PWRMETER2_DUMMY ) ) 
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

    // Output pins 
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins
    digital_in_init( &ctx->md1, cfg->md1 );
    digital_in_init( &ctx->md0, cfg->md0 );
    digital_in_init( &ctx->dr, cfg->dr );
    
    return PWRMETER2_OK;
}

err_t pwrmeter2_default_cfg ( pwrmeter2_t *ctx )
{
    err_t error_flag = PWRMETER2_OK;
    pwrmeter2_reset( ctx );
    error_flag |= pwrmeter2_write_reg( ctx, PWRMETER2_REG_CONFIG1, PWRMETER2_CH0_NORMAL_MODE | 
                                                                   PWRMETER2_CH1_NORMAL_MODE | 
                                                                   PWRMETER2_INTERNAL_VOL_REF_EN | 
                                                                   PWRMETER2_INTERNAL_CLOCK_EN );
    error_flag |= pwrmeter2_write_reg( ctx, PWRMETER2_REG_STATUS_COMM, PWRMETER2_READ_REG_TYPES | 
                                                                       PWRMETER2_ADDR_COUNT_INCR_WRITE |
                                                                       PWRMETER2_DATA_WIDTH_24_BIT | 
                                                                       0x000003ul );
    error_flag |= pwrmeter2_write_reg( ctx, PWRMETER2_REG_CONFIG0, PWRMETER2_OFFCAL_EN | 
                                                                   PWRMETER2_GAINCAL_EN | 
                                                                   PWRMETER2_DITHERING_STRENGTH_MAX | 
                                                                   PWRMETER2_CURRENT_X_2 | 
                                                                   PWRMETER2_AMCLK_MCLK_PER_8 | 
                                                                   PWRMETER2_OSR_256 );
    error_flag |= pwrmeter2_write_reg( ctx, PWRMETER2_REG_GAIN_CONFIG, PWRMETER2_CH0_GAIN1 | 
                                                                       PWRMETER2_CH1_GAIN1 );
    error_flag |= pwrmeter2_write_reg( ctx, PWRMETER2_REG_GAINCAL_CH0, 0xD30000ul );
    error_flag |= pwrmeter2_write_reg( ctx, PWRMETER2_REG_GAINCAL_CH1, 0xD30000ul );
    error_flag |= pwrmeter2_write_reg( ctx, PWRMETER2_REG_OFFCAL_CH1, 0xFFE800ul );
    Delay_100ms ( );
    return error_flag;
}

err_t pwrmeter2_write_reg ( pwrmeter2_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t reg_addr = 0;
    uint8_t data_buf[ 3 ] = { 0 };
    if ( reg > 0x1F )
    {
        return PWRMETER2_ERROR;
    }
    reg_addr = ( reg << 1 ) | 0x40;
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_addr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );  
    return error_flag;
}

err_t pwrmeter2_read_reg ( pwrmeter2_t *ctx, uint8_t reg, uint32_t *data_out, uint8_t len )
{
    uint8_t reg_addr = 0;
    uint8_t data_buf[ 39 ] = { 0 };
    if ( ( reg > 0x1F ) || ( len > 13 ) )
    {
        return PWRMETER2_ERROR;
    }
    reg_addr = ( reg << 1 ) | 0x41;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_addr, 1 );
    error_flag |= spi_master_read( &ctx->spi, data_buf, len * 3 );
    spi_master_deselect_device( ctx->chip_select );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_out[ cnt ] = ( ( uint32_t ) data_buf[ cnt * 3 ] << 16 ) | 
                          ( ( uint16_t ) data_buf[ cnt * 3 + 1 ] << 8 ) | 
                          data_buf[ cnt * 3 + 2 ];
    }
    return error_flag;
}

err_t pwrmeter2_read_conv_data ( pwrmeter2_t *ctx, uint32_t *data_ch_0, uint32_t *data_ch_1 )
{
    uint32_t data_buf[ 2 ] = { 0 };
    while ( pwrmeter2_check_ready_pin ( ctx ) );
    err_t error_flag = pwrmeter2_read_reg ( ctx, PWRMETER2_REG_CH0_ADC_DATA, data_buf, 2 );
    *data_ch_0 = data_buf[ 0 ];
    *data_ch_1 = data_buf[ 1 ];
    return error_flag;
}

err_t pwrmeter2_get_data ( pwrmeter2_t *ctx, float *voltage, float *current, float *power )
{
    int32_t volt_val = 0;
    int32_t curr_val = 0;
    uint32_t ch_0_data = 0;
    uint32_t ch_1_data = 0;
    err_t error_flag = pwrmeter2_read_conv_data( ctx, &ch_0_data, &ch_1_data );
    volt_val = ch_0_data;
    volt_val <<= 8;
    volt_val >>= 8;
    curr_val = ch_1_data;
    curr_val <<= 8;
    curr_val >>= 8;
    *voltage = ( float ) volt_val / 0x800000ul * 48.0f ;
    *current = ( float ) curr_val / 0x800000ul * -40.0f;
    *power = fabs( *voltage ) * fabs( *current );
    return error_flag;
}

void pwrmeter2_reset( pwrmeter2_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_1sec( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
}

uint8_t pwrmeter2_get_modulator_1 ( pwrmeter2_t *ctx )
{
    return digital_in_read( &ctx->md1 );
}

uint8_t pwrmeter2_get_modulator_0 ( pwrmeter2_t *ctx )
{   
    return digital_in_read( &ctx->md0 );
}

uint8_t pwrmeter2_check_ready_pin ( pwrmeter2_t *ctx )
{
    return digital_in_read( &ctx->dr );
}

// ------------------------------------------------------------------------- END

