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
 * @file isoadc5.c
 * @brief ISO ADC 5 Click Driver.
 */

#include "isoadc5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/** 
 * @brief Check CRC Enable function.
 * @details This function checks if the CRC is enabled. 
 * @param[in] ctx : Click context object.
 * See #isoadc5_t object definition for detailed explanation.
 * @return @li @c  0x8000 - CRC enabled,
 *         @li @c  0 - CRC disabled,
 *         @li @c -1 - Error.
 * @note None.
 */
static err_t isoadc5_check_crc_enable ( isoadc5_t *ctx );

/** 
 * @brief SMBus calculation for CRC8 function.
 * @details This function calculates CRC8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x07 (x8 + x2 + x +1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t isoadc5_calculate_crc( uint8_t *data_buf, uint8_t len );

void isoadc5_cfg_setup ( isoadc5_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t isoadc5_init ( isoadc5_t *ctx, isoadc5_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t isoadc5_write_register ( isoadc5_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    if ( reg > ISOADC5_REG_CONTROL )
    {
        return ISOADC5_ERROR;
    }
    uint8_t tx_buf[ 4 ] = { 0 };
    err_t error_flag = ISOADC5_ERROR;
    
    tx_buf[ 0 ] = ( reg << 2 ) | ISOADC5_SPI_WRITE;
    tx_buf[ 1 ] = ( uint8_t )( data_in >> 8 );
    tx_buf[ 2 ] = ( uint8_t )( data_in & 0xFF );
    
    spi_master_select_device( ctx->chip_select );
    if ( ISOADC5_EN_CRC == isoadc5_check_crc_enable( ctx ) )
    {
        tx_buf[ 3 ] = isoadc5_calculate_crc( tx_buf, 3 );
        error_flag = spi_master_write( &ctx->spi, tx_buf, 4 );
    }
    else if ( ISOADC5_OK == error_flag )
    {
        error_flag = spi_master_write( &ctx->spi, tx_buf, 3 );
    }
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t isoadc5_read_register ( isoadc5_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    if ( reg > ISOADC5_REG_CONTROL )
    {
        return ISOADC5_ERROR;
    }
    uint8_t data_len = 2;
    uint8_t tmp_buf[ 4 ] = { 0 };
    
    if ( ISOADC5_EN_CRC == isoadc5_check_crc_enable( ctx ) )
    {
        data_len = 3;
    }
    tmp_buf[ 0 ] = reg << 2;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &tmp_buf[ 0 ], 1, &tmp_buf[ 1 ], data_len );
    spi_master_deselect_device( ctx->chip_select );
    
    if ( data_len == 3 )
    {
        if ( tmp_buf[ data_len ] != isoadc5_calculate_crc ( tmp_buf, data_len ) )
        {
            return ISOADC5_ERROR;
        }
    }
    
    *data_out = tmp_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= tmp_buf[ 2 ];

    return error_flag;
}

err_t isoadc5_read_register_burst ( isoadc5_t *ctx, uint8_t filt, isoadc5_burst_payload_t *payload ) 
{
    if ( filt > ISOADC5_ADC_FILTERED )
    {
        return ISOADC5_ERROR;
    }
    uint8_t data_len = 10;
    uint8_t tmp_buf[ 12 ] = { 0 };
    
    if ( ISOADC5_EN_CRC == isoadc5_check_crc_enable( ctx ) )
    {
        data_len = 11;
    }
    if ( ISOADC5_ADC_UNFILTERED == filt )
    {
        tmp_buf[ 0 ] = ( ISOADC5_REG_ADC_1 << 2 ) | ISOADC5_SPI_BURST;
    }
    else
    {
        tmp_buf[ 0 ] = ( ISOADC5_REG_FADC_1 << 2 ) | ISOADC5_SPI_BURST;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &tmp_buf[ 0 ], 1, &tmp_buf[ 1 ], data_len );
    spi_master_deselect_device( ctx->chip_select );
    
    if ( data_len == 11 )
    {
        if ( tmp_buf[ data_len ] != isoadc5_calculate_crc ( tmp_buf, data_len ) )
        {
            return ISOADC5_ERROR;
        }
    }
    
    if ( ISOADC5_ADC_UNFILTERED == filt )
    {
        if ( ( tmp_buf[ 1 ] | tmp_buf[ 3 ] | tmp_buf[ 5 ] | tmp_buf[ 7 ] ) & ( ISOADC5_ADC_NOT_UPDATED >> 8 ) )
        {
            return ISOADC5_ERROR;
        }
    }
    
    payload->adc_1 = tmp_buf[ 1 ];
    payload->adc_1 <<= 8;
    payload->adc_1 |= tmp_buf[ 2 ];
    payload->adc_1 &= ISOADC5_ADC_12BIT_MASK;
    
    payload->adc_2 = tmp_buf[ 3 ];
    payload->adc_2 <<= 8;
    payload->adc_2 |= tmp_buf[ 4 ];
    payload->adc_2 &= ISOADC5_ADC_12BIT_MASK;
    
    payload->adc_3 = tmp_buf[ 5 ];
    payload->adc_3 <<= 8;
    payload->adc_3 |= tmp_buf[ 6 ];
    payload->adc_3 &= ISOADC5_ADC_12BIT_MASK;
    
    payload->adc_4 = tmp_buf[ 7 ];
    payload->adc_4 <<= 8;
    payload->adc_4 |= tmp_buf[ 8 ];
    payload->adc_4 &= ISOADC5_ADC_12BIT_MASK;
    
    payload->int_status = tmp_buf[ 9 ];
    payload->int_status <<= 8;
    payload->int_status |= tmp_buf[ 10 ];

    return error_flag;
}

err_t isoadc5_read_voltage( isoadc5_t *ctx, uint8_t filt, uint8_t ch, float *volt )
{
    if ( ( filt > ISOADC5_ADC_FILTERED ) || 
         ( ch > ISOADC5_ADC_CHANNEL_4 ) || 
         ( ch < ISOADC5_ADC_CHANNEL_1 ) )
    {
        return ISOADC5_ERROR;
    }
    uint16_t raw_adc = 0;
    
    err_t error_flag = isoadc5_read_register ( ctx, ch + filt * ISOADC5_ADC_CHANNEL_4, &raw_adc );
    
    if ( ISOADC5_ADC_UNFILTERED == filt )
    {
        if ( raw_adc & ISOADC5_ADC_NOT_UPDATED )
        {
            return error_flag;
        }
    }
    
    *volt = ( float ) ( raw_adc * ISOADC5_MAX_VOLTAGE ) / ISOADC5_ADC_12BIT_MASK;
    
    return error_flag;
}

uint8_t isoadc5_get_int_pin ( isoadc5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t isoadc5_check_crc_enable ( isoadc5_t *ctx )
{
    uint8_t reg = ISOADC5_REG_CONTROL << 2;
    uint8_t rx_buf[ 3 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    if ( ( ISOADC5_EN_CRC >> 8 ) == rx_buf[ 0 ] )
    {
        return ISOADC5_EN_CRC;
    }

    return error_flag;
}

static uint8_t isoadc5_calculate_crc( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    
    for ( uint8_t i = 0; i < len; i++ ) 
    {
        crc ^= data_buf[ i ];
        for ( uint8_t j = 0; j < 8; j++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {    
                crc = ( uint8_t )( ( crc << 1 ) ^ 0x07 );
            }
            else
            {
                 crc <<= 1;
            }    
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
