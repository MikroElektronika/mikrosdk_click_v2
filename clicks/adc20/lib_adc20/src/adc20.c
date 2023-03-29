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
 * @file adc20.c
 * @brief ADC 20 Click Driver.
 */

#include "adc20.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void adc20_cfg_setup ( adc20_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc20_init ( adc20_t *ctx, adc20_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t adc20_default_cfg ( adc20_t *ctx ) 
{
    err_t error_flag = ADC20_OK;
    error_flag |= adc20_write_register ( ctx, ADC20_REG_DATA_CFG, ADC20_DATA_CFG_FIX_PAT | 
                                                                  ADC20_DATA_CFG_SPI_MODE_0 );
    if ( ADC20_ERROR == adc20_check_communication ( ctx ) )
    {
        return ADC20_ERROR;
    }
    error_flag |= adc20_write_register ( ctx, ADC20_REG_DATA_CFG, ADC20_DATA_CFG_APPEND_CHANNEL_ID | 
                                                                  ADC20_DATA_CFG_SPI_MODE_0 );
    
    error_flag |= adc20_write_register ( ctx, ADC20_REG_OSR_CFG, ADC20_OSR_NO_AVERAGING );
    
    error_flag |= adc20_set_pin_config ( ctx, ( ADC20_CHANNEL_0 | ADC20_CHANNEL_1 | 
                                                ADC20_CHANNEL_6 | ADC20_CHANNEL_7 ), ADC20_PIN_CFG_GPIO );
    error_flag |= adc20_set_pin_config ( ctx, ( ADC20_CHANNEL_2 | ADC20_CHANNEL_3 | 
                                                ADC20_CHANNEL_4 | ADC20_CHANNEL_5 ), ADC20_PIN_CFG_ANALOG );
    
    error_flag |= adc20_set_gpio_config ( ctx, ( ADC20_CHANNEL_0 | ADC20_CHANNEL_1 ), ADC20_GPIO_CFG_DIG_INPUT );
    error_flag |= adc20_set_gpio_config ( ctx, ( ADC20_CHANNEL_6 | ADC20_CHANNEL_7 ), ADC20_GPIO_CFG_DIG_OUTPUT );
    
    error_flag |= adc20_set_gpo_drive_config ( ctx, ( ADC20_CHANNEL_6 | ADC20_CHANNEL_7 ), ADC20_GPO_DRIVE_CFG_PUSH_PULL );
    
    error_flag |= adc20_set_gpo_value ( ctx, ( ADC20_CHANNEL_6 | ADC20_CHANNEL_7 ), ADC20_GPIO_VALUE_LOW );
    
    error_flag |= adc20_write_register ( ctx, ADC20_REG_AUTO_SEQ_CH_SEL, ( ADC20_CHANNEL_2 | ADC20_CHANNEL_3 | 
                                                                           ADC20_CHANNEL_4 | ADC20_CHANNEL_5 ) );
    return error_flag;
}

err_t adc20_write_register ( adc20_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ADC20_CMD_REG_WRITE;
    data_buf[ 1 ] = reg;
    data_buf[ 2 ] = data_in;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t adc20_read_register ( adc20_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ADC20_CMD_REG_READ;
    data_buf[ 1 ] = reg;
    data_buf[ 2 ] = DUMMY;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 3 );
    *data_out = data_buf[ 0 ];
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t adc20_read_data ( adc20_t *ctx, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_buf, 2 );
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t adc20_check_communication ( adc20_t *ctx )
{
    uint16_t fixed_code;
    if ( ADC20_OK == adc20_read_data ( ctx, &fixed_code ) )
    {
        if ( ADC20_FIXED_CODE == fixed_code )
        {
            return ADC20_OK;
        }
    }
    return ADC20_ERROR;
}

err_t adc20_start_auto_sequence ( adc20_t *ctx )
{
    uint16_t dummy_read;
    err_t error_flag = adc20_write_register ( ctx, ADC20_REG_SEQUENCE_CFG, ADC20_SEQ_START | ADC20_SEQ_MODE_AUTO );
    error_flag |= adc20_read_data ( ctx, &dummy_read );
    return error_flag;
}

err_t adc20_stop_auto_sequence ( adc20_t *ctx )
{
    return adc20_write_register ( ctx, ADC20_REG_SEQUENCE_CFG, ADC20_SEQ_MODE_MANUAL );
}

err_t adc20_set_pin_config ( adc20_t *ctx, uint8_t ch_mask, uint8_t pin_cfg )
{
    uint8_t reg_data;
    if ( ADC20_ERROR == adc20_read_register ( ctx, ADC20_REG_PIN_CFG, &reg_data ) )
    {
        return ADC20_ERROR;
    }
    if ( ADC20_PIN_CFG_GPIO == pin_cfg )
    {
        reg_data |= ch_mask;
    }
    else
    {
        reg_data &= ( ~ch_mask );
    }
    return adc20_write_register ( ctx, ADC20_REG_PIN_CFG, reg_data );
}

err_t adc20_set_gpio_config ( adc20_t *ctx, uint8_t ch_mask, uint8_t gpio_cfg )
{
    uint8_t reg_data;
    if ( ADC20_ERROR == adc20_read_register ( ctx, ADC20_REG_GPIO_CFG, &reg_data ) )
    {
        return ADC20_ERROR;
    }
    if ( ADC20_GPIO_CFG_DIG_OUTPUT == gpio_cfg )
    {
        reg_data |= ch_mask;
    }
    else
    {
        reg_data &= ( ~ch_mask );
    }
    return adc20_write_register ( ctx, ADC20_REG_GPIO_CFG, reg_data );
}

err_t adc20_set_gpo_drive_config ( adc20_t *ctx, uint8_t ch_mask, uint8_t gpo_drive_cfg )
{
    uint8_t reg_data;
    if ( ADC20_ERROR == adc20_read_register ( ctx, ADC20_REG_GPO_DRIVE_CFG, &reg_data ) )
    {
        return ADC20_ERROR;
    }
    if ( ADC20_GPO_DRIVE_CFG_PUSH_PULL == gpo_drive_cfg )
    {
        reg_data |= ch_mask;
    }
    else
    {
        reg_data &= ( ~ch_mask );
    }
    return adc20_write_register ( ctx, ADC20_REG_GPO_DRIVE_CFG, reg_data );
}

err_t adc20_set_gpo_value ( adc20_t *ctx, uint8_t ch_mask, uint8_t value )
{
    uint8_t reg_data;
    if ( ADC20_ERROR == adc20_read_register ( ctx, ADC20_REG_GPO_VALUE, &reg_data ) )
    {
        return ADC20_ERROR;
    }
    if ( ADC20_GPIO_VALUE_HIGH == value )
    {
        reg_data |= ch_mask;
    }
    else
    {
        reg_data &= ( ~ch_mask );
    }
    return adc20_write_register ( ctx, ADC20_REG_GPO_VALUE, reg_data );
}

err_t adc20_read_gpio_value ( adc20_t *ctx, uint8_t *gpio_value )
{
    return adc20_read_register ( ctx, ADC20_REG_GPI_VALUE, gpio_value );
}

// ------------------------------------------------------------------------- END
