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
 * @file adac2.c
 * @brief ADAC 2 Click Driver.
 */

#include "adac2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief SPI Read bit.
 * @details Definition of SPI Read bit.
 */
#define ADAC2_SPI_READ_BIT  0x01

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
static uint8_t adac2_calculate_crc8_maxim ( uint8_t *data_buf, uint8_t len );

void adac2_cfg_setup ( adac2_cfg_t *cfg ) 
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

err_t adac2_init ( adac2_t *ctx, adac2_cfg_t *cfg ) 
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

err_t adac2_default_cfg ( adac2_t *ctx ) 
{
    err_t error_flag = ADAC2_OK;
    
    ctx->spi_crc_enable = false;
    
    adac2_reset_device ( ctx );
    
    error_flag |= adac2_enable_spi_crc ( ctx );
    
    if ( ADAC2_ERROR == adac2_check_communication ( ctx ) )
    {
        return ADAC2_ERROR;
    }
    
    error_flag |= adac2_set_conversion_mode ( ctx, ADAC2_CONV_MODE_CONTINUOUS );
    
    uint32_t rx_data;
    error_flag |= adac2_read_register ( ctx, ADAC2_REG_GEN_CNFG, &rx_data );
    rx_data = ( rx_data & ( ~ADAC2_GEN_CNFG_AO_CNFG_MASK ) ) | ADAC2_GEN_CNFG_AO_CNFG_12p5V;
    rx_data = ( rx_data & ( ~ADAC2_GEN_CNFG_AI3_CNFG_MASK ) ) | ADAC2_GEN_CNFG_AI3_CNFG_SE;
    rx_data = ( rx_data & ( ~ADAC2_GEN_CNFG_AI4_CNFG_MASK ) ) | ADAC2_GEN_CNFG_AI4_CNFG_SE;
    rx_data = ( rx_data & ( ~ADAC2_GEN_CNFG_AI5_6_CNFG_MASK ) ) | ADAC2_GEN_CNFG_AI5_6_CNFG_DIFF;
    error_flag |= adac2_write_register ( ctx, ADAC2_REG_GEN_CNFG, rx_data );
    
    // Enable all GPIOs set as OUTPUT
    error_flag |= adac2_write_register ( ctx, ADAC2_REG_GEN_GPIO_CTRL, ( ( uint32_t ) ADAC2_GPIO_ALL_MASK << 16 ) | 
                                                                       ( ( uint16_t ) ADAC2_GPIO_ALL_MASK << 8 ) );
    
    return error_flag;
}

err_t adac2_write_register ( adac2_t *ctx, uint8_t reg, uint32_t data_in )
{
    err_t error_flag = ADAC2_OK;
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = ( reg << 1 ) & ( ~ADAC2_SPI_READ_BIT );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    if ( ctx->spi_crc_enable )
    {
        data_buf[ 4 ] = adac2_calculate_crc8_maxim ( data_buf, 4 );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 5 );
    }
    else
    {
        error_flag |= spi_master_write( &ctx->spi, data_buf, 4 );
    }
    spi_master_deselect_device( ctx->chip_select ); 
    return error_flag;
}

err_t adac2_read_register ( adac2_t *ctx, uint8_t reg, uint32_t *data_out )
{
    err_t error_flag = ADAC2_OK;
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = ( reg << 1 ) | ADAC2_SPI_READ_BIT;
    spi_master_select_device( ctx->chip_select );
    if ( ctx->spi_crc_enable )
    {
        error_flag |= spi_master_write_then_read( &ctx->spi, &data_buf[ 0 ], 1, &data_buf[ 1 ], 4 );
        if ( data_buf[ 4 ] != adac2_calculate_crc8_maxim ( data_buf, 4 ) )
        {
            spi_master_deselect_device( ctx->chip_select ); 
            return ADAC2_ERROR;
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

err_t adac2_enable_spi_crc ( adac2_t *ctx )
{
    uint32_t rx_data;
    err_t error_flag = adac2_read_register ( ctx, ADAC2_REG_GEN_CNFG, &rx_data );
    rx_data |= ADAC2_GEN_CNFG_CRC_EN_ENABLE;
    error_flag |= adac2_write_register ( ctx, ADAC2_REG_GEN_CNFG, rx_data );
    if ( ADAC2_OK == error_flag )
    {
        ctx->spi_crc_enable = true;
    }
    return error_flag;
}

err_t adac2_disable_spi_crc ( adac2_t *ctx )
{
    uint32_t rx_data;
    err_t error_flag = adac2_read_register ( ctx, ADAC2_REG_GEN_CNFG, &rx_data );
    rx_data &= ~ADAC2_GEN_CNFG_CRC_EN_ENABLE;
    error_flag |= adac2_write_register ( ctx, ADAC2_REG_GEN_CNFG, rx_data );
    if ( ADAC2_OK == error_flag )
    {
        ctx->spi_crc_enable = false;
    }
    return error_flag;
}

err_t adac2_check_communication ( adac2_t *ctx )
{
    uint32_t prod_id;
    if ( ADAC2_OK == adac2_read_register ( ctx, ADAC2_REG_GEN_PROD, &prod_id ) )
    {
        prod_id = ( prod_id >> 16 ) & 0xFF;
        if ( ADAC2_PRODUCT_ID == prod_id )
        {
            return ADAC2_OK;
        }
    }
    return ADAC2_ERROR;
}

void adac2_reset_device ( adac2_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

uint8_t adac2_get_rdy_pin ( adac2_t *ctx )
{
    return digital_in_read ( &ctx->rdy );
}

uint8_t adac2_get_int_pin ( adac2_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t adac2_start_conversion ( adac2_t *ctx, uint8_t data_rate )
{
    if ( data_rate > ADAC2_DATA_RATE_115200_SPS )
    {
        return ADAC2_ERROR;
    }
    return adac2_write_register ( ctx, ADAC2_REG_DCHNL_CMD, 
                                  ( uint32_t ) ( ADAC2_START_CONVERSION | data_rate ) << 16 );
}

err_t adac2_stop_conversion ( adac2_t *ctx )
{
    return adac2_write_register ( ctx, ADAC2_REG_DCHNL_CMD, ( uint32_t ) ADAC2_STOP_CONVERSION << 16 );
}

err_t adac2_set_conversion_mode ( adac2_t *ctx, uint8_t mode )
{
    return adac2_write_register ( ctx, ADAC2_REG_DCHNL_CTRL1, ( uint32_t ) mode << 16 );
}

err_t adac2_set_active_ain_channel ( adac2_t *ctx, uint8_t channel )
{
    if ( channel > ADAC2_CH_AUX1_AUX2_DIFFERENTIAL )
    {
        return ADAC2_ERROR;
    }
    uint32_t rx_data;
    err_t error_flag = adac2_read_register ( ctx, ADAC2_REG_GEN_CHNL_CTRL, &rx_data );
    rx_data &= ~ADAC2_CH_MASK;
    rx_data |= ( ( uint32_t ) channel << 8 );
    error_flag |= adac2_write_register ( ctx, ADAC2_REG_GEN_CHNL_CTRL, rx_data );
    return error_flag;
}

err_t adac2_read_raw_adc ( adac2_t *ctx, int32_t *raw_adc )
{
    uint32_t reg_data;
    if ( ADAC2_OK == adac2_read_register ( ctx, ADAC2_REG_DCHNL_DATA, &reg_data ) )
    {
        *raw_adc = ( ( int32_t ) ( reg_data << 8 ) ) >> 8;
        return ADAC2_OK;
    }
    return ADAC2_ERROR;
}

err_t adac2_read_voltage ( adac2_t *ctx, float fsr, float *voltage )
{
    int32_t raw_adc;
    if ( ADAC2_OK == adac2_read_raw_adc ( ctx, &raw_adc ) )
    {
        *voltage = ( float ) raw_adc / ADAC2_ADC_DATA_RESOLUTION * fsr;
        return ADAC2_OK;
    }
    return ADAC2_ERROR;
}

err_t adac2_write_dac ( adac2_t *ctx, int32_t dac )
{
    if ( ( dac < ADAC2_DAC_MIN_VALUE ) || ( dac > ADAC2_DAC_MAX_VALUE ) )
    {
        return ADAC2_ERROR;
    }
    return adac2_write_register ( ctx, ADAC2_REG_AO_DATA_WR, 
                                  ( uint32_t ) ( ( dac & ADAC2_DAC_DATA_RESOLUTION ) << 6 ) );
}

static uint8_t adac2_calculate_crc8_maxim ( uint8_t *data_buf, uint8_t len )
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
