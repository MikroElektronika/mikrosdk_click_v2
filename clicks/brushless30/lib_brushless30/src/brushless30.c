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
 * @file brushless30.c
 * @brief Brushless 30 Click Driver.
 */

#include "brushless30.h"

/**
 * @brief Dummy data and SPI read write bit.
 * @details Definition of dummy data and SPI read write bit.
 */
#define BRUSHLESS30_DUMMY                 0x00
#define BRUSHLESS30_SPI_READ_WRITE_BIT    0x80

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x1D (x4 + x3 + x2 + 1)
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final result
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t brushless30_calculate_crc ( uint8_t *data_buf, uint8_t len );

void brushless30_cfg_setup ( brushless30_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->alarm = HAL_PIN_NC;
    cfg->diag = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t brushless30_init ( brushless30_t *ctx, brushless30_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, BRUSHLESS30_DUMMY ) ) 
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

    digital_out_init( &ctx->alarm, cfg->alarm );
    digital_out_low( &ctx->alarm );

    digital_in_init( &ctx->diag, cfg->diag );

    return SPI_MASTER_SUCCESS;
}

err_t brushless30_default_cfg ( brushless30_t *ctx ) 
{
    err_t error_flag = BRUSHLESS30_OK;
    uint16_t reg_data = 0;
    brushless30_disable_driver ( ctx );
    Delay_100ms ( );
    error_flag |= brushless30_write_reg ( ctx, BRUSHLESS30_REG_HS_VDS_SEL, BRUSHLESS30_HS_VDS_SEL );
    error_flag |= brushless30_read_reg ( ctx, BRUSHLESS30_REG_HS_VDS_SEL, &reg_data );
    if ( BRUSHLESS30_HS_VDS_SEL != reg_data )
    {
        error_flag |= BRUSHLESS30_ERROR;
    }
    error_flag |= brushless30_write_reg ( ctx, BRUSHLESS30_REG_LS_VDS_SEL, BRUSHLESS30_LS_VDS_SEL );
    error_flag |= brushless30_read_reg ( ctx, BRUSHLESS30_REG_LS_VDS_SEL, &reg_data );
    if ( BRUSHLESS30_LS_VDS_SEL != reg_data )
    {
        error_flag |= BRUSHLESS30_ERROR;
    }
    error_flag |= brushless30_write_reg ( ctx, BRUSHLESS30_REG_AMP_CTRL, BRUSHLESS30_AMP_CTRL );
    error_flag |= brushless30_read_reg ( ctx, BRUSHLESS30_REG_AMP_CTRL, &reg_data );
    if ( BRUSHLESS30_AMP_CTRL != reg_data )
    {
        error_flag |= BRUSHLESS30_ERROR;
    }
    error_flag |= brushless30_write_reg ( ctx, BRUSHLESS30_REG_CP_RLY_CTRL, BRUSHLESS30_CP_RLY_CTRL );
    error_flag |= brushless30_read_reg ( ctx, BRUSHLESS30_REG_CP_RLY_CTRL, &reg_data );
    if ( BRUSHLESS30_CP_RLY_CTRL != reg_data )
    {
        error_flag |= BRUSHLESS30_ERROR;
    }
    brushless30_enable_driver ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t brushless30_write_reg ( brushless30_t *ctx, uint8_t reg, uint16_t data_in )
{
    err_t error_flag = BRUSHLESS30_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = reg & ( ~BRUSHLESS30_SPI_READ_WRITE_BIT );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 3 ] = brushless30_calculate_crc ( data_buf, 3 );
    spi_master_select_device( ctx->chip_select );
    Delay_10ms ( );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 4 );
    Delay_10ms ( );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t brushless30_read_reg ( brushless30_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = BRUSHLESS30_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t byte_cnt = 0;
    uint8_t crc = 0;
    data_buf[ 0 ] = reg | BRUSHLESS30_SPI_READ_WRITE_BIT;
    data_buf[ 1 ] = BRUSHLESS30_DUMMY;
    data_buf[ 2 ] = brushless30_calculate_crc ( data_buf, 1 );
    data_buf[ 3 ] = BRUSHLESS30_DUMMY;
    spi_master_select_device( ctx->chip_select );
    Delay_10ms ( );
    for ( byte_cnt = 0; byte_cnt < 4; byte_cnt++ )
    {
        error_flag |= spi_master_set_default_write_data( &ctx->spi, data_buf[ byte_cnt ] );
        error_flag |= spi_master_read( &ctx->spi, &data_buf[ byte_cnt ], 1 );
    }
    Delay_10ms ( );
    spi_master_deselect_device( ctx->chip_select );
    crc = brushless30_calculate_crc ( &data_buf[ 1 ], 2 );
    if ( ( BRUSHLESS30_ERROR == error_flag ) ||
         ( BRUSHLESS30_DUMMY != data_buf[ 0 ] ) || 
         ( data_buf[ 3 ] != crc ) )
    {
        return BRUSHLESS30_ERROR;
    }
    *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    return BRUSHLESS30_OK;
}

void brushless30_enable_driver ( brushless30_t *ctx )
{
    digital_out_high ( &ctx->alarm );
}

void brushless30_disable_driver ( brushless30_t *ctx )
{
    digital_out_low ( &ctx->alarm );
}

uint8_t brushless30_get_diag_pin ( brushless30_t *ctx )
{
    return digital_in_read ( &ctx->diag );
}

static uint8_t brushless30_calculate_crc ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0xFF;
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ ) 
    {
        crc ^= data_buf[ byte_cnt ];
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x80 )
            {    
                crc = ( uint8_t ) ( ( crc << 1 ) ^ 0x1D );
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
