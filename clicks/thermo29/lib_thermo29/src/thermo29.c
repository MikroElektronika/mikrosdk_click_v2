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
 * @file thermo29.c
 * @brief Thermo 29 Click Driver.
 */

#include "thermo29.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/** 
 * @brief CCITT-FALSE calculation for CRC16 function.
 * @details This function calculates CRC16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Polynomial 0x1021 ( x16 + x12 + x5 + x0 )
 * @li @c  Initialization 0xFFFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final result
 * @li @c  Example { AB, CD } - 0xD46A
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t thermo29_calculate_crc16_ccitt ( uint8_t *data_buf, uint16_t len );

void thermo29_cfg_setup ( thermo29_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->alert = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t thermo29_init ( thermo29_t *ctx, thermo29_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alert, cfg->alert );

    return SPI_MASTER_SUCCESS;
}

err_t thermo29_default_cfg ( thermo29_t *ctx ) 
{
    err_t error_flag = THERMO29_OK;
    thermo29_enable_crc ( ctx );
    if ( THERMO29_ERROR == thermo29_check_communication ( ctx ) )
    {
        return THERMO29_ERROR;
    }
    // Writing to the configuration register with a CRC enabled transaction is not supported
    thermo29_disable_crc ( ctx );
    error_flag |= thermo29_write_register ( ctx, THERMO29_REG_CONFIGURATION, THERMO29_CONFIGURATION_MODE_CONT | 
                                                                             THERMO29_CONFIGURATION_CONV_PER_1S );
    thermo29_enable_crc ( ctx );
    error_flag |= thermo29_write_register ( ctx, THERMO29_REG_ALERT_ENABLE, THERMO29_ALERT_ENABLE_DATA_READY );
    error_flag |= thermo29_clear_alert_status ( ctx );
    return error_flag;
}

err_t thermo29_write_register ( thermo29_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 6 ] = { 0 };
    uint16_t crc16 = 0;
    if ( reg > THERMO29_REG_DEVICE_ID )
    {
        return THERMO29_ERROR;
    }
    data_buf[ 0 ] = THERMO29_WRITE_BIT;
    if ( ctx->crc_enable )
    {
        data_buf[ 0 ] |= ( THERMO29_CRC_ENABLE | ( ( 1 << 2 ) & THERMO29_CRC_DATA_BLOCK_LEN_MASK ) );
    }
    data_buf[ 1 ] = reg;
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &data_buf[ 0 ], 4 );
    if ( ctx->crc_enable )
    {
        crc16 = thermo29_calculate_crc16_ccitt ( data_buf, 4 );
        data_buf[ 4 ] = ( uint8_t ) ( ( crc16 >> 8 ) & 0xFF );
        data_buf[ 5 ] = ( uint8_t ) ( crc16 & 0xFF );
        error_flag |= spi_master_write( &ctx->spi, &data_buf[ 4 ], 2 );
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t thermo29_read_register ( thermo29_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 6 ] = { 0 };
    uint16_t crc16 = 0;
    if ( reg > THERMO29_REG_DEVICE_ID )
    {
        return THERMO29_ERROR;
    }
    data_buf[ 0 ] = THERMO29_READ_BIT;
    if ( ctx->crc_enable )
    {
        data_buf[ 0 ] |= ( THERMO29_CRC_ENABLE | ( ( 1 << 2 ) & THERMO29_CRC_DATA_BLOCK_LEN_MASK ) );
    }
    data_buf[ 1 ] = reg;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read ( &ctx->spi, &data_buf[ 0 ], 2, &data_buf[ 2 ], 2 );
    if ( ctx->crc_enable )
    {
        error_flag |= spi_master_read ( &ctx->spi, &data_buf[ 4 ], 2 );
        crc16 = ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
        if ( crc16 == thermo29_calculate_crc16_ccitt ( data_buf, 4 ) )
        {
            *data_out = ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
        }
        else
        {
            error_flag = THERMO29_ERROR;
        }
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t thermo29_write_registers ( thermo29_t *ctx, uint8_t reg, uint16_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 4 + THERMO29_DATA_LEN_MAX * 2 ] = { 0 };
    uint16_t crc16 = 0;
    if ( ( ( reg + len ) > THERMO29_REG_DEVICE_ID ) || ( len > THERMO29_DATA_LEN_MAX ) )
    {
        return THERMO29_ERROR;
    }
    data_buf[ 0 ] = THERMO29_AUTO_INCREMENT | THERMO29_WRITE_BIT;
    if ( ctx->crc_enable )
    {
        data_buf[ 0 ] |= ( THERMO29_CRC_ENABLE | ( ( len << 2 ) & THERMO29_CRC_DATA_BLOCK_LEN_MASK ) );
    }
    data_buf[ 1 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ 2 + cnt * 2 ] = ( uint8_t ) ( ( data_in[ cnt ] >> 8 ) & 0xFF );
        data_buf[ 3 + cnt * 2 ] = ( uint8_t ) ( data_in[ cnt ] & 0xFF );
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 + len * 2 );
    if ( ctx->crc_enable )
    {
        crc16 = thermo29_calculate_crc16_ccitt ( data_buf, 2 + len * 2 );
        data_buf[ 2 + len * 2 ] = ( uint8_t ) ( ( crc16 >> 8 ) & 0xFF );
        data_buf[ 3 + len * 2 ] = ( uint8_t ) ( crc16 & 0xFF );
        error_flag |= spi_master_write( &ctx->spi, &data_buf[ 2 + len * 2 ], 2 );
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t thermo29_read_registers ( thermo29_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 4 + THERMO29_DATA_LEN_MAX * 2 ] = { 0 };
    uint16_t crc16 = 0;
    if ( ( ( reg + len ) > THERMO29_REG_DEVICE_ID ) || ( len > THERMO29_DATA_LEN_MAX ) )
    {
        return THERMO29_ERROR;
    }
    data_buf[ 0 ] = THERMO29_AUTO_INCREMENT | THERMO29_READ_BIT;
    if ( ctx->crc_enable )
    {
        data_buf[ 0 ] |= ( THERMO29_CRC_ENABLE | ( ( 1 << 2 ) & THERMO29_CRC_DATA_BLOCK_LEN_MASK ) );
    }
    data_buf[ 1 ] = reg;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read ( &ctx->spi, &data_buf[ 0 ], 2, &data_buf[ 2 ], len * 2 );
    if ( ctx->crc_enable )
    {
        error_flag |= spi_master_read ( &ctx->spi, &data_buf[ 2 + len * 2 ], 2 );
        crc16 = ( ( uint16_t ) data_buf[ 2 + len * 2 ] << 8 ) | data_buf[ 3 + len * 2 ];
        if ( crc16 == thermo29_calculate_crc16_ccitt ( data_buf, 2 + len * 2 ) )
        {
            for ( uint8_t cnt = 0; cnt < len; cnt++ )
            {
                data_out[ cnt ] = ( ( uint16_t ) data_buf[ 2 + cnt * 2 ] << 8 ) | data_buf[ 3 + cnt * 2 ];
            }
        }
        else
        {
            error_flag = THERMO29_ERROR;
        }
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

uint8_t thermo29_get_alert_pin ( thermo29_t *ctx )
{
    return digital_in_read ( &ctx->alert );
}

void thermo29_enable_crc ( thermo29_t *ctx )
{
    ctx->crc_enable = true;
}

void thermo29_disable_crc ( thermo29_t *ctx )
{
    ctx->crc_enable = false;
}

err_t thermo29_check_communication ( thermo29_t *ctx )
{
    uint16_t device_id;
    if ( THERMO29_OK == thermo29_read_register ( ctx, THERMO29_REG_DEVICE_ID, &device_id ) )
    {
        if ( THERMO29_DEVICE_ID == ( device_id & THERMO29_DEVICE_ID_MASK ) )
        {
            return THERMO29_OK;
        }
    }
    return THERMO29_ERROR;
}

err_t thermo29_read_unique_id ( thermo29_t *ctx, uint16_t *unique_id )
{
    return thermo29_read_registers ( ctx, THERMO29_REG_UNIQUE_ID1, unique_id, 3 );
}

err_t thermo29_read_temperature ( thermo29_t *ctx, float *temperature )
{
    uint16_t raw_temp;
    err_t error_flag = thermo29_read_register ( ctx, THERMO29_REG_TEMP_RESULT, &raw_temp );
    if ( THERMO29_OK == error_flag )
    {
        *temperature = ( ( int16_t ) raw_temp >> 2 ) * THERMO29_TEMP_RESOLUTION;
    }
    return error_flag;
}

err_t thermo29_clear_alert_status ( thermo29_t *ctx )
{
    uint16_t alert_status;
    err_t error_flag = thermo29_read_register ( ctx, THERMO29_REG_ALERT_STATUS, &alert_status );
    return thermo29_read_register ( ctx, THERMO29_REG_ALERT_STATUS, &alert_status );
}

static uint16_t thermo29_calculate_crc16_ccitt ( uint8_t *data_buf, uint16_t len )
{
    uint16_t crc16 = 0xFFFF;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        crc16 ^= ( ( data_buf[ cnt ] ) << 8 );
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( crc16 & 0x8000 )
            {
                crc16 = ( crc16 << 1 ) ^ 0x1021;
            }
            else
            {
                crc16 <<= 1;
            }
        }
    }
    return crc16;
}

// ------------------------------------------------------------------------- END
