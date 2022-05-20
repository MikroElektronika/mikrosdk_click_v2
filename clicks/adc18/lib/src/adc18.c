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
 * @file adc18.c
 * @brief ADC 18 Click Driver.
 */

#include "adc18.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY               0x00

/**
 * @brief SPI Read bit.
 * @details Definition of SPI Read bit.
 */
#define ADC18_SPI_READ_BIT  0x01

/** 
 * @brief Calculation for Maxim CRC 8 function.
 * @details This function calculates Maxim CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 + 1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated Maxim CRC.
 * @note None.
 */
static uint8_t adc18_calculate_crc8_maxim ( uint8_t *data_buf, uint8_t len );

void adc18_cfg_setup ( adc18_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc18_init ( adc18_t *ctx, adc18_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t adc18_default_cfg ( adc18_t *ctx ) 
{
    err_t error_flag = ADC18_OK;
    
    ctx->spi_crc_enable = false;
    
    adc18_reset_device ( ctx );
    
    error_flag |= adc18_enable_spi_crc ( ctx );
    
    if ( ADC18_ERROR == adc18_check_communication ( ctx ) )
    {
        return ADC18_ERROR;
    }
    
    error_flag |= adc18_set_conversion_mode ( ctx, ADC18_CONV_MODE_CONTINUOUS );

    return error_flag;
}

err_t adc18_write_register ( adc18_t *ctx, uint8_t reg, uint32_t data_in )
{
    err_t error_flag = ADC18_OK;
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = ( reg << 1 ) & ( ~ADC18_SPI_READ_BIT );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    if ( ctx->spi_crc_enable )
    {
        data_buf[ 4 ] = adc18_calculate_crc8_maxim ( data_buf, 4 );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 5 );
    }
    else
    {
        error_flag |= spi_master_write( &ctx->spi, data_buf, 4 );
    }
    spi_master_deselect_device( ctx->chip_select ); 
    return error_flag;
}

err_t adc18_read_register ( adc18_t *ctx, uint8_t reg, uint32_t *data_out )
{
    err_t error_flag = ADC18_OK;
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = ( reg << 1 ) | ADC18_SPI_READ_BIT;
    spi_master_select_device( ctx->chip_select );
    if ( ctx->spi_crc_enable )
    {
        error_flag |= spi_master_write_then_read( &ctx->spi, &data_buf[ 0 ], 1, &data_buf[ 1 ], 4 );
        if ( data_buf[ 4 ] != adc18_calculate_crc8_maxim ( data_buf, 4 ) )
        {
            spi_master_deselect_device( ctx->chip_select ); 
            return ADC18_ERROR;
        }
    }
    else
    {
        error_flag |= spi_master_write_then_read( &ctx->spi, &data_buf[ 0 ], 1, &data_buf[ 1 ], 3 );
    }
    spi_master_deselect_device( ctx->chip_select ); 
    *data_out = ( ( uint32_t ) data_buf[ 1 ] << 16 ) | ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
    return error_flag;
}

err_t adc18_enable_spi_crc ( adc18_t *ctx )
{
    uint32_t rx_data;
    err_t error_flag = adc18_read_register ( ctx, ADC18_REG_GEN_CNFG, &rx_data );
    rx_data |= ADC18_GEN_CNFG_CRC_EN;
    error_flag |= adc18_write_register ( ctx, ADC18_REG_GEN_CNFG, rx_data );
    if ( ADC18_OK == error_flag )
    {
        ctx->spi_crc_enable = true;
    }
    return error_flag;
}

err_t adc18_disable_spi_crc ( adc18_t *ctx )
{
    uint32_t rx_data;
    err_t error_flag = adc18_read_register ( ctx, ADC18_REG_GEN_CNFG, &rx_data );
    rx_data &= ~ADC18_GEN_CNFG_CRC_EN;
    error_flag |= adc18_write_register ( ctx, ADC18_REG_GEN_CNFG, rx_data );
    if ( ADC18_OK == error_flag )
    {
        ctx->spi_crc_enable = false;
    }
    return error_flag;
}

err_t adc18_check_communication ( adc18_t *ctx )
{
    uint32_t prod_id;
    if ( ADC18_OK == adc18_read_register ( ctx, ADC18_REG_GEN_PROD, &prod_id ) )
    {
        prod_id = ( prod_id >> 16 ) & 0xFF;
        if ( ADC18_PRODUCT_ID == prod_id )
        {
            return ADC18_OK;
        }
    }
    return ADC18_ERROR;
}

void adc18_reset_device ( adc18_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

uint8_t adc18_get_rdy_pin ( adc18_t *ctx )
{
    return digital_in_read ( &ctx->rdy );
}

uint8_t adc18_get_int_pin ( adc18_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t adc18_start_conversion ( adc18_t *ctx, uint8_t data_rate )
{
    if ( data_rate > ADC18_DATA_RATE_115200_SPS )
    {
        return ADC18_ERROR;
    }
    return adc18_write_register ( ctx, ADC18_REG_DCHNL_CMD, 
                                  ( uint32_t ) ( ADC18_START_CONVERSION | data_rate ) << 16 );
}

err_t adc18_stop_conversion ( adc18_t *ctx )
{
    return adc18_write_register ( ctx, ADC18_REG_DCHNL_CMD, ( uint32_t ) ADC18_STOP_CONVERSION << 16 );
}

err_t adc18_set_conversion_mode ( adc18_t *ctx, uint8_t mode )
{
    return adc18_write_register ( ctx, ADC18_REG_DCHNL_CTRL1, ( uint32_t ) mode << 16 );
}

err_t adc18_set_active_channel ( adc18_t *ctx, uint8_t channel )
{
    if ( channel > ADC18_CH_AI10_COM_AI12_MULTI_DIFF )
    {
        return ADC18_ERROR;
    }
    return adc18_write_register ( ctx, ADC18_REG_GEN_CHNL_CTRL, ( ( uint32_t ) channel << 8 ) | 
                                  ( ( uint32_t ) ( ADC18_AIP_TEST_2MOHM_TO_AGND | ADC18_AIN_TEST_2MOHM_TO_AGND ) << 16 ) );
}

err_t adc18_read_raw_adc ( adc18_t *ctx, int32_t *raw_adc )
{
    uint32_t reg_data;
    if ( ADC18_OK == adc18_read_register ( ctx, ADC18_REG_DCHNL_DATA, &reg_data ) )
    {
        *raw_adc = ( ( int32_t ) ( reg_data << 8 ) ) >> 8;
        return ADC18_OK;
    }
    return ADC18_ERROR;
}

err_t adc18_read_voltage ( adc18_t *ctx, float *voltage )
{
    int32_t raw_adc;
    if ( ADC18_OK == adc18_read_raw_adc ( ctx, &raw_adc ) )
    {
        *voltage = ( float ) raw_adc / ADC18_DATA_RESOLUTION * ADC18_FULL_SCALE_VOLTAGE;
        return ADC18_OK;
    }
    return ADC18_ERROR;
}

static uint8_t adc18_calculate_crc8_maxim ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    for ( uint8_t cnt_0 = 0; cnt_0 < len; cnt_0++ ) 
    {
        uint8_t in_byte = data_buf[ cnt_0 ];
        for ( uint8_t cnt_1 = 0; cnt_1 < 8; cnt_1++ ) 
        {
            uint8_t mix = ( crc ^ in_byte ) & 0x01;
            crc >>= 1;
            if ( 0 != mix ) 
            {
                crc ^= 0x8C;
            }
            in_byte >>= 1;
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
