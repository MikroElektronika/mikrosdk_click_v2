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
 * @file gainamp3.c
 * @brief GainAMP 3 Click Driver.
 */

#include "gainamp3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                       0x00

/**
 * @brief SPI Read bit.
 * @details Definition of SPI Read bit.
 */
#define GAINAMP3_SPI_READ_BIT       0x80

/** 
 * @brief SPI CRC Enable function.
 * @details This function enables SPI CRC. 
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static err_t gainamp3_enable_spi_crc ( gainamp3_t *ctx );

/** 
 * @brief SPI CRC Disable function.
 * @details This function disables SPI CRC. 
 * @param[in] ctx : Click context object.
 * See #gainamp3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
static err_t gainamp3_disable_spi_crc ( gainamp3_t *ctx );

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
static uint8_t gainamp3_calculate_crc( uint8_t *data_buf, uint8_t len );

void gainamp3_cfg_setup ( gainamp3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t gainamp3_init ( gainamp3_t *ctx, gainamp3_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t gainamp3_default_cfg ( gainamp3_t *ctx ) 
{
    ctx->spi_crc_enable = GAINAMP3_SPI_CRC_DISABLE;
    
    err_t error_flag = gainamp3_software_reset ( ctx );
    
    error_flag |= gainamp3_enable_spi_crc ( ctx );
    
    if ( GAINAMP3_ERROR == gainamp3_verify_communication ( ctx ) )
    {
        return GAINAMP3_ERROR;
    }
    
    error_flag |= gainamp3_set_input_channel ( ctx, GAINAMP3_CHANNEL_1 );
    
    return error_flag;
}

err_t gainamp3_continuous_write ( gainamp3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 50 ] = { 0 }; 
    uint8_t crc_buf[ 2 ] = { 0 };
    reg &= ~GAINAMP3_SPI_READ_BIT;
    
    tx_buf[ 0 ] = reg;
    
    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        if ( GAINAMP3_SPI_CRC_ENABLE == ctx->spi_crc_enable )
        {
            tx_buf[ cnt * 2 - 1 ] = data_in[ cnt - 1 ];
            crc_buf[ 0 ] = reg + cnt - 1;
            crc_buf[ 1 ] = data_in[ cnt - 1 ];
            tx_buf[ cnt * 2 ] = gainamp3_calculate_crc ( crc_buf, 2 );
        }
        else
        {
            tx_buf[ cnt ] = data_in[ cnt - 1 ];
        }
    }
    
    if ( GAINAMP3_SPI_CRC_ENABLE == ctx->spi_crc_enable )
    {
        len *= 2;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t gainamp3_continuous_read ( gainamp3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    reg |= GAINAMP3_SPI_READ_BIT;
    
    if ( GAINAMP3_SPI_CRC_ENABLE == ctx->spi_crc_enable )
    {
        uint8_t rx_buf[ 50 ] = { 0 };
        uint8_t crc_buf[ 2 ] = { 0 }; 
        len *= 2;
        
        if ( len > 50 )
        {
            return GAINAMP3_ERROR;
        }
        err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, rx_buf, len );
        spi_master_deselect_device( ctx->chip_select );
        for ( uint8_t cnt = 1; cnt <= len; cnt += 2 )
        {
            crc_buf[ 0 ] = reg + cnt / 2;
            crc_buf[ 1 ] = rx_buf[ cnt - 1 ];
            if ( rx_buf[ cnt ] == gainamp3_calculate_crc ( crc_buf, 2 ) )
            {
                data_out[ cnt / 2 ] = rx_buf[ cnt - 1 ];
            }
            else
            {
                return GAINAMP3_ERROR;
            }
        }
        return error_flag;
    }
    else
    {
        err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
        spi_master_deselect_device( ctx->chip_select );
        
        return error_flag;
    }
}

err_t gainamp3_write_register ( gainamp3_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return gainamp3_continuous_write ( ctx, reg, &data_in, 1 );
}

err_t gainamp3_read_register ( gainamp3_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return gainamp3_continuous_read ( ctx, reg, data_out, 1 );
}

err_t gainamp3_verify_communication ( gainamp3_t *ctx ) 
{
    uint8_t die_rev_id = 0;
    
    if ( GAINAMP3_OK == gainamp3_read_register ( ctx, GAINAMP3_REG_DIE_REV_ID, &die_rev_id ) )
    {
        if ( GAINAMP3_DIE_REV_ID == die_rev_id )
        {
            return GAINAMP3_OK;
        }
    }
    return GAINAMP3_ERROR;
}

err_t gainamp3_set_amplifier_gain ( gainamp3_t *ctx, uint8_t gain ) 
{
    if ( gain > GAINAMP3_GAIN_128 )
    {
        return GAINAMP3_ERROR;
    }
    uint8_t reg_value = 0;
    err_t error_flag = gainamp3_read_register ( ctx, GAINAMP3_REG_GAIN_MUX, &reg_value );
    reg_value &= ~GAINAMP3_GAIN_BITS_MASK;
    reg_value |= ( gain << 3 );
    error_flag |= gainamp3_write_register ( ctx, GAINAMP3_REG_GAIN_MUX, reg_value );
    
    return error_flag;
}

err_t gainamp3_set_input_channel ( gainamp3_t *ctx, uint8_t channel ) 
{
    if ( channel > GAINAMP3_CHANNEL_SHORT_SWITCH )
    {
        return GAINAMP3_ERROR;
    }
    return gainamp3_write_register ( ctx, GAINAMP3_REG_INPUT_MUX, GAINAMP3_CHANNEL_BITS_MASK >> ( channel * 2 ) );
}

err_t gainamp3_software_reset ( gainamp3_t *ctx ) 
{
    return gainamp3_write_register ( ctx, GAINAMP3_REG_RESET, 1 );
}

static err_t gainamp3_enable_spi_crc ( gainamp3_t *ctx )
{
    uint8_t rx_data = 0;
    
    err_t error_flag = gainamp3_read_register ( ctx, GAINAMP3_REG_DIGITAL_ERR_DIS, &rx_data );
    rx_data &= ~GAINAMP3_SPI_CRC_ERR_DISABLE_BIT;
    error_flag |= gainamp3_write_register ( ctx, GAINAMP3_REG_DIGITAL_ERR_DIS, rx_data );
    
    if ( GAINAMP3_OK == error_flag )
    {
        ctx->spi_crc_enable = GAINAMP3_SPI_CRC_ENABLE;
    }
    return error_flag;
}

static err_t gainamp3_disable_spi_crc ( gainamp3_t *ctx )
{
    uint8_t rx_data = 0;
    
    err_t error_flag = gainamp3_read_register ( ctx, GAINAMP3_REG_DIGITAL_ERR_DIS, &rx_data );
    rx_data |= GAINAMP3_SPI_CRC_ERR_DISABLE_BIT;
    error_flag |= gainamp3_write_register ( ctx, GAINAMP3_REG_DIGITAL_ERR_DIS, rx_data );
    
    if ( GAINAMP3_OK == error_flag )
    {
        ctx->spi_crc_enable = GAINAMP3_SPI_CRC_DISABLE;
    }
    return error_flag;
}

static uint8_t gainamp3_calculate_crc ( uint8_t *data_buf, uint8_t len )
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
