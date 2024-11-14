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
 * @file isoadc7.c
 * @brief ISO ADC 7 Click Driver.
 */

#include "isoadc7.h"

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
 * @li @c  Example { D9, 0D, 00, 00 }- 0x9DE5
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t isoadc7_crc16_ccitt ( uint8_t *data_buf, uint16_t len );

/**
 * @brief Word input data to buffer.
 * @details This function separates word input data in to buffer.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] data_word : Word data.
 * @param[out] data_buf : Buffer address to get data in.
 * @return None.
 * @note None.
 */
static void isoadc7_word_to_buf ( isoadc7_t *ctx, uint32_t data_word, uint8_t *data_buf );

/**
 * @brief Buffer to word output data value.
 * @details This function gets word data from buffer.
 * @param[in] ctx : Click context object.
 * See #adc15_t object definition for detailed explanation.
 * @param[in] data_buf : Buffer address to get data from.
 * @param[out] data_word : Word data.
 * @return None.
 * @note None.
 */
static void isoadc7_buf_to_word ( isoadc7_t *ctx, uint8_t *data_buf, uint32_t *data_word );

void isoadc7_cfg_setup ( isoadc7_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->xen  = HAL_PIN_NC;
    cfg->drdy = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t isoadc7_init ( isoadc7_t *ctx, isoadc7_cfg_t *cfg ) 
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
    digital_out_init( &ctx->xen, cfg->xen );

    digital_in_init( &ctx->drdy, cfg->drdy );

    return SPI_MASTER_SUCCESS;
}

err_t isoadc7_default_cfg ( isoadc7_t *ctx ) 
{
    err_t error_flag = ISOADC7_OK;
    ISOADC7_SET_DATA_SAMPLE_EDGE;
    ctx->word_size = 3;
    isoadc7_enable_osc ( ctx );
    isoadc7_reset_device ( ctx );
    if ( ISOADC7_ERROR == isoadc7_check_id ( ctx ) )
    {
        return ISOADC7_ERROR;
    }
    error_flag |= isoadc7_sw_reset ( ctx );
    error_flag |= isoadc7_set_gain ( ctx, ISOADC7_GAIN_1, ISOADC7_GAIN_1, ISOADC7_GAIN_1 );
    error_flag |= isoadc7_write_reg ( ctx, ISOADC7_REG_MODE, ISOADC7_MODE_WLENGTH_24BIT | 
                                                             ISOADC7_MODE_TIMEOUT_ENABLE | 
                                                             ISOADC7_MODE_DRDY_HIZ | 
                                                             ISOADC7_MODE_DRDY_FMT );
    error_flag |= isoadc7_write_reg ( ctx, ISOADC7_REG_CLOCK, ISOADC7_CLOCK_CH2_EN | 
                                                              ISOADC7_CLOCK_CH1_EN | 
                                                              ISOADC7_CLOCK_CH0_EN | 
                                                              ISOADC7_CLOCK_CLK_DIV_2 | 
                                                              ISOADC7_CLOCK_OSR_1024 | 
                                                              ISOADC7_CLOCK_PWR_HIGH );
    error_flag |= isoadc7_write_reg ( ctx, ISOADC7_REG_CH0_CFG, ISOADC7_CH0_CFG_MUX_AIN0P_AIN0N );
    error_flag |= isoadc7_write_reg ( ctx, ISOADC7_REG_CH1_CFG, ISOADC7_CH1_CFG_MUX_AIN1P_AIN12N );
    error_flag |= isoadc7_write_reg ( ctx, ISOADC7_REG_CH2_CFG, ISOADC7_CH2_CFG_MUX_AIN2P_AIN12N );
    error_flag |= isoadc7_write_reg ( ctx, ISOADC7_REG_DCDC_CTRL, ISOADC7_DCDC_CTRL_DCDC_EN );
    Delay_100ms ( );
    return error_flag;
}

err_t isoadc7_write_reg ( isoadc7_t *ctx, uint8_t reg, uint16_t data_in )
{
    return isoadc7_write_regs ( ctx, reg, &data_in, 1 );
}

err_t isoadc7_write_regs ( isoadc7_t *ctx, uint8_t reg, uint16_t *data_in, uint8_t len )
{
    if ( ( reg > ISOADC7_REG_REGMAP_CRC ) || ( NULL == data_in ) || ( len < 1 ) || ( len > 23 ) )
    {
        return ISOADC7_ERROR;
    }
    err_t error_flag = ISOADC7_OK;
    uint8_t data_buf[ 100 ] = { 0 };
    uint32_t data_word = ISOADC7_CMD_WREG | ( ( uint16_t ) ( reg & 0x3F ) << 7 ) | ( ( len - 1 ) & 0x7F );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, data_buf );

    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_word = ( uint32_t ) data_in[ cnt ] << ( 8 * ( ctx->word_size - 2 ) );
        isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size * ( cnt + 1 ) ] );
    }

    data_word = isoadc7_crc16_ccitt ( data_buf, ctx->word_size * ( len + 1 ) );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );

    if ( len < 3 )
    {
        isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size * 4 ] );
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, data_buf, ctx->word_size * 5 );
        spi_master_deselect_device( ctx->chip_select );
    }
    else
    {
        isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size * ( len + 1 ) ] );
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, data_buf, ctx->word_size * ( len + 2 ) );
        spi_master_deselect_device( ctx->chip_select );
    }

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    if ( ISOADC7_OK == error_flag )
    {
        // check acknowledge
        isoadc7_buf_to_word ( ctx, data_buf, &data_word );
        if ( ISOADC7_RSP_WREG != ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xE000 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        // check crc
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 4 ], &data_word );
        if ( ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) != 
             isoadc7_crc16_ccitt ( data_buf, ctx->word_size * 4 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    return error_flag;
}

err_t isoadc7_read_reg ( isoadc7_t *ctx, uint8_t reg, uint16_t *data_out )
{
    if ( ( reg > ISOADC7_REG_REGMAP_CRC ) || ( NULL == data_out ) )
    {
        return ISOADC7_ERROR;
    }
    err_t error_flag = ISOADC7_OK;
    uint8_t data_buf[ 20 ] = { 0 };
    uint32_t data_word = ISOADC7_CMD_RREG | ( ( uint16_t ) ( reg & 0x3F ) << 7 );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, data_buf );

    data_word = isoadc7_crc16_ccitt ( data_buf, ctx->word_size );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size ] );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    if ( ISOADC7_OK == error_flag )
    {
        // check crc
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 4 ], &data_word );
        if ( ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) != 
             isoadc7_crc16_ccitt ( data_buf, ctx->word_size * 4 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        isoadc7_buf_to_word ( ctx, data_buf, &data_word );
        *data_out = ( uint16_t ) ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) );
    }
    return error_flag;
}

err_t isoadc7_read_regs ( isoadc7_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len )
{
    if ( ( reg > ISOADC7_REG_REGMAP_CRC ) || ( NULL == data_out ) || ( len < 2 ) || ( len > 23 ) )
    {
        return ISOADC7_ERROR;
    }
    err_t error_flag = ISOADC7_OK;
    uint8_t data_buf[ 100 ] = { 0 };
    uint32_t data_word = ISOADC7_CMD_RREG | ( ( uint16_t ) ( reg & 0x3F ) << 7 ) | ( ( len - 1 ) & 0x7F );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, data_buf );

    data_word = isoadc7_crc16_ccitt ( data_buf, ctx->word_size );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size ] );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, ctx->word_size * ( len + 2 ) );
    spi_master_deselect_device( ctx->chip_select );

    if ( ISOADC7_OK == error_flag )
    {
        // check acknowledge
        isoadc7_buf_to_word ( ctx, data_buf, &data_word );
        if ( ISOADC7_RSP_RREG != ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xE000 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        // check crc
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * ( len + 1 ) ], &data_word );
        if ( ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) != 
             isoadc7_crc16_ccitt ( data_buf, ctx->word_size * ( len + 1 ) ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        for ( uint8_t cnt = 0; cnt < len; cnt++ )
        {
            isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * ( cnt + 1 ) ], &data_word );
            data_out[ cnt ] = ( uint16_t ) ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) );
        }
    }
    return error_flag;
}

err_t isoadc7_standby ( isoadc7_t *ctx )
{
    err_t error_flag = ISOADC7_OK;
    uint8_t data_buf[ 20 ] = { 0 };
    uint32_t data_word = ISOADC7_CMD_STANDBY;
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, data_buf );

    data_word = isoadc7_crc16_ccitt ( data_buf, ctx->word_size );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size ] );
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    Delay_100ms ( );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    if ( ISOADC7_OK == error_flag )
    {
        // check acknowledge
        isoadc7_buf_to_word ( ctx, data_buf, &data_word );
        if ( ISOADC7_RSP_STANDBY != ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        // check crc
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 4 ], &data_word );
        if ( ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) != 
             isoadc7_crc16_ccitt ( data_buf, ctx->word_size * 4 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }
    return error_flag;
}

err_t isoadc7_wakeup ( isoadc7_t *ctx )
{
    err_t error_flag = ISOADC7_OK;
    uint8_t data_buf[ 20 ] = { 0 };
    uint32_t data_word = ISOADC7_CMD_WAKEUP;
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, data_buf );

    data_word = isoadc7_crc16_ccitt ( data_buf, ctx->word_size );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size ] );
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    Delay_100ms ( );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    if ( ISOADC7_OK == error_flag )
    {
        // check acknowledge
        isoadc7_buf_to_word ( ctx, data_buf, &data_word );
        if ( ISOADC7_RSP_WAKEUP != ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        // check crc
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 4 ], &data_word );
        if ( ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) != 
             isoadc7_crc16_ccitt ( data_buf, ctx->word_size * 4 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }
    return error_flag;
}

err_t isoadc7_lock ( isoadc7_t *ctx )
{
    err_t error_flag = ISOADC7_OK;
    uint8_t data_buf[ 20 ] = { 0 };
    uint32_t data_word = ISOADC7_CMD_LOCK;
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, data_buf );

    data_word = isoadc7_crc16_ccitt ( data_buf, ctx->word_size );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size ] );
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    Delay_100ms ( );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    if ( ISOADC7_OK == error_flag )
    {
        // check acknowledge
        isoadc7_buf_to_word ( ctx, data_buf, &data_word );
        if ( ISOADC7_RSP_LOCK != ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        // check crc
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 4 ], &data_word );
        if ( ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) != 
             isoadc7_crc16_ccitt ( data_buf, ctx->word_size * 4 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }
    return error_flag;
}

err_t isoadc7_unlock ( isoadc7_t *ctx )
{
    err_t error_flag = ISOADC7_OK;
    uint8_t data_buf[ 20 ] = { 0 };
    uint32_t data_word = ISOADC7_CMD_UNLOCK;
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, data_buf );

    data_word = isoadc7_crc16_ccitt ( data_buf, ctx->word_size );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size ] );
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    Delay_100ms ( );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    if ( ISOADC7_OK == error_flag )
    {
        // check acknowledge
        isoadc7_buf_to_word ( ctx, data_buf, &data_word );
        if ( ISOADC7_RSP_UNLOCK != ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        // check crc
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 4 ], &data_word );
        if ( ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) != 
             isoadc7_crc16_ccitt ( data_buf, ctx->word_size * 4 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }
    return error_flag;
}

err_t isoadc7_sw_reset ( isoadc7_t *ctx )
{
    err_t error_flag = ISOADC7_OK;
    uint8_t data_buf[ 20 ] = { 0 };
    uint32_t data_word = ISOADC7_CMD_RESET;
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, data_buf );

    data_word = isoadc7_crc16_ccitt ( data_buf, ctx->word_size );
    data_word <<= ( 8 * ( ctx->word_size - 2 ) );
    isoadc7_word_to_buf ( ctx, data_word, &data_buf[ ctx->word_size ] );
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    Delay_100ms ( );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    if ( ISOADC7_OK == error_flag )
    {
        // check acknowledge
        isoadc7_buf_to_word ( ctx, data_buf, &data_word );
        if ( ISOADC7_RSP_RESET != ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        // check crc
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 4 ], &data_word );
        if ( ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) != 
             isoadc7_crc16_ccitt ( data_buf, ctx->word_size * 4 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }
    return error_flag;
}

void isoadc7_reset_device ( isoadc7_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void isoadc7_set_rst_pin ( isoadc7_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void isoadc7_enable_osc ( isoadc7_t *ctx )
{
    digital_out_high ( &ctx->xen );
}

void isoadc7_disable_osc ( isoadc7_t *ctx )
{
    digital_out_low ( &ctx->xen );
}

uint8_t isoadc7_get_drdy_pin ( isoadc7_t *ctx )
{
    return digital_in_read ( &ctx->drdy );
}

err_t isoadc7_check_id ( isoadc7_t *ctx )
{
    uint16_t device_id = 0;
    if ( ISOADC7_OK == isoadc7_read_reg ( ctx, ISOADC7_REG_ID, &device_id ) )
    {
        if ( ISOADC7_DEVICE_ID == ( device_id & ISOADC7_DEVICE_ID_MASK ) )
        {
            return ISOADC7_OK;
        }
    }
    return ISOADC7_ERROR;
}

err_t isoadc7_set_word_size ( isoadc7_t *ctx, uint8_t word_size )
{
    if ( ( word_size < 2 ) || ( word_size > 4 ) )
    {
        return ISOADC7_ERROR;
    }
    uint16_t reg_data = 0;
    if ( ISOADC7_OK == isoadc7_read_reg ( ctx, ISOADC7_REG_MODE, &reg_data ) )
    {
        reg_data &= ~ISOADC7_MODE_WLENGTH_MASK;
        reg_data |= ( ( uint16_t ) ( word_size - 2 ) << 8 );
        ctx->word_size = word_size;
        return isoadc7_write_reg ( ctx, ISOADC7_REG_MODE, reg_data );
    }
    return ISOADC7_ERROR;
}

err_t isoadc7_set_gain ( isoadc7_t *ctx, uint8_t gain_ch0, uint8_t gain_ch1, uint8_t gain_ch2 )
{
    if ( ( gain_ch0 > ISOADC7_GAIN_128 ) || ( gain_ch1 > ISOADC7_GAIN_128 ) || ( gain_ch2 > ISOADC7_GAIN_128 ) )
    {
        return ISOADC7_ERROR;
    }
    uint16_t reg_data = ( ( uint16_t ) gain_ch2 << 8 ) | ( gain_ch1 << 4 ) | gain_ch0;
    ctx->fsr_ch0 = ISOADC7_INTERNAL_VREF_MV / ( 1 << gain_ch0 );
    ctx->fsr_ch1 = ISOADC7_INTERNAL_VREF_MV / ( 1 << gain_ch1 );
    ctx->fsr_ch2 = ISOADC7_INTERNAL_VREF_MV / ( 1 << gain_ch2 );
    return isoadc7_write_reg ( ctx, ISOADC7_REG_GAIN, reg_data );
}

err_t isoadc7_read_data ( isoadc7_t *ctx, isoadc7_data_t *data_out )
{
    if ( NULL == data_out )
    {
        return ISOADC7_ERROR;
    }
    err_t error_flag = ISOADC7_OK;
    uint8_t data_buf[ 20 ] = { 0 };
    uint32_t data_word = ISOADC7_CMD_NULL;

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, ctx->word_size * 5 );
    spi_master_deselect_device( ctx->chip_select );

    if ( ISOADC7_OK == error_flag )
    {
        // check crc
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 4 ], &data_word );
        if ( ( ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) ) & 0xFFFF ) != 
             isoadc7_crc16_ccitt ( data_buf, ctx->word_size * 4 ) )
        {
            error_flag |= ISOADC7_ERROR;
        }
    }

    if ( ISOADC7_OK == error_flag )
    {
        isoadc7_buf_to_word ( ctx, data_buf, &data_word );
        data_out->status = ( uint16_t ) ( data_word >> ( 8 * ( ctx->word_size - 2 ) ) & 0xFFFF );
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size ], &data_word );
        data_out->ch0_data = ( int32_t ) data_word;
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 2 ], &data_word );
        data_out->ch1_data = ( int32_t ) data_word;
        isoadc7_buf_to_word ( ctx, &data_buf[ ctx->word_size * 3 ], &data_word );
        data_out->ch2_data = ( int32_t ) data_word;
    }
    return error_flag;
}

err_t isoadc7_read_voltage ( isoadc7_t *ctx, float *ch0, float *ch1, float *ch2 )
{
    isoadc7_data_t adc_data;

    while ( isoadc7_get_drdy_pin ( ctx ) );

    err_t error_flag = isoadc7_read_data ( ctx, &adc_data );

    if ( ISOADC7_OK == error_flag )
    {
        if ( ( adc_data.status & ISOADC7_STATUS_DRDY0 ) && ( NULL != ch0 ) )
        {
            *ch0 = ( float ) adc_data.ch0_data / 0x800000 * ctx->fsr_ch0;
        }
        if ( ( adc_data.status & ISOADC7_STATUS_DRDY1 ) && ( NULL != ch1 ) )
        {
            *ch1 = ( float ) adc_data.ch1_data / 0x800000 * ctx->fsr_ch1;
        }
        if ( ( adc_data.status & ISOADC7_STATUS_DRDY2 ) && ( NULL != ch2 ) )
        {
            *ch2 = ( float ) adc_data.ch2_data / 0x800000 * ctx->fsr_ch2;
        }
    }
    return error_flag;
}

static uint16_t isoadc7_crc16_ccitt ( uint8_t *data_buf, uint16_t len )
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

static void isoadc7_word_to_buf ( isoadc7_t *ctx, uint32_t data_word, uint8_t *data_buf )
{
    switch ( ctx->word_size )
    {
        case 2:
        {
            data_buf[ 0 ] = ( uint8_t ) ( ( data_word >> 8 ) & 0xFF );
            data_buf[ 1 ] = ( uint8_t ) ( data_word & 0xFF );
            break;
        }
        case 3:
        {
            data_buf[ 0 ] = ( uint8_t ) ( ( data_word >> 16 ) & 0xFF );
            data_buf[ 1 ] = ( uint8_t ) ( ( data_word >> 8 ) & 0xFF );
            data_buf[ 2 ] = ( uint8_t ) ( data_word & 0xFF );
            break;
        }
        case 4:
        {
            data_buf[ 0 ] = ( uint8_t ) ( ( data_word >> 24 ) & 0xFF );
            data_buf[ 1 ] = ( uint8_t ) ( ( data_word >> 16 ) & 0xFF );
            data_buf[ 2 ] = ( uint8_t ) ( ( data_word >> 8 ) & 0xFF );
            data_buf[ 3 ] = ( uint8_t ) ( data_word & 0xFF );
            break;
        }
        default:
        {
            break;
        }
    }
}

static void isoadc7_buf_to_word ( isoadc7_t *ctx, uint8_t *data_buf, uint32_t *data_word )
{
    switch ( ctx->word_size )
    {
        case 2:
        {
            *data_word = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
            if ( data_buf[ 0 ] & 0x80 )
            {
                *data_word |= 0xFFFF0000;
            }
            break;
        }
        case 3:
        {
            *data_word = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | 
                         ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
            if ( data_buf[ 0 ] & 0x80 )
            {
                *data_word |= 0xFF000000;
            }
            break;
        }
        case 4:
        {
            *data_word = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) | 
                         ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
            break;
        }
        default:
        {
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
