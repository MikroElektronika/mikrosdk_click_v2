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
 * @file digiin2.c
 * @brief DIGI IN 2 Click Driver.
 */

#include "digiin2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/** 
 * @brief Calculation for CRC 5 function.
 * @details This function calculates CRC 5 with parameteres: 
 * @li @c  Width 5 bit
 * @li @c  Polynomial 0x15 ( x5 + x4 + x2 + 1 )
 * @li @c  Initialization 0x1F
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] byte1 : Byte 1 for CRC calculation.
 * @param[in] byte2 : Byte 2 for CRC calculation.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t digiin2_crc5_encode_2byte( uint8_t byte1, uint8_t byte2 );

void digiin2_cfg_setup ( digiin2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;
    cfg->ltc  = HAL_PIN_NC;
    cfg->flt  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t digiin2_init ( digiin2_t *ctx, digiin2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->ltc, cfg->ltc );

    digital_in_init( &ctx->rdy , cfg->rdy );
    digital_in_init( &ctx->flt, cfg->flt );

    digiin2_set_ltc_pin( ctx, DIGIIN2_PIN_STATE_HIGH );

    ctx->device_address = DIGIIN2_CHIP_ADDRESS_00;
    ctx->crc_en = DIGIIN2_CRC_ENABLED;

    return SPI_MASTER_SUCCESS;
}

err_t digiin2_default_cfg ( digiin2_t *ctx ) 
{
    err_t error_flag = DIGIIN2_OK;
    
    error_flag |= digiin2_write_reg( ctx, DIGIIN2_REG_CNFG1, DIGIIN2_HITHR_HIGH | DIGIIN2_CURR_X1 |
                                                             DIGIIN2_GLITCH_FIL_EN | DIGIIN2_GLITCH_FIL_DELAY_50_US );
    error_flag |= digiin2_write_reg( ctx, DIGIIN2_REG_CNFG2, DIGIIN2_HITHR_HIGH | DIGIIN2_CURR_X1 | 
                                                             DIGIIN2_GLITCH_FIL_EN | DIGIIN2_GLITCH_FIL_DELAY_50_US );
    error_flag |= digiin2_write_reg( ctx, DIGIIN2_REG_CNFG3, DIGIIN2_HITHR_HIGH | DIGIIN2_CURR_X1 |
                                                             DIGIIN2_GLITCH_FIL_EN | DIGIIN2_GLITCH_FIL_DELAY_50_US );
    error_flag |= digiin2_write_reg( ctx, DIGIIN2_REG_CNFG4, DIGIIN2_HITHR_HIGH | DIGIIN2_CURR_X1 | 
                                                             DIGIIN2_GLITCH_FIL_EN | DIGIIN2_GLITCH_FIL_DELAY_50_US );
    error_flag |= digiin2_write_reg( ctx, DIGIIN2_REG_CNFG5, DIGIIN2_HITHR_HIGH | DIGIIN2_CURR_X1 | 
                                                             DIGIIN2_GLITCH_FIL_EN | DIGIIN2_GLITCH_FIL_DELAY_50_US );
    error_flag |= digiin2_write_reg( ctx, DIGIIN2_REG_CNFG6, DIGIIN2_HITHR_HIGH | DIGIIN2_CURR_X1 | 
                                                             DIGIIN2_GLITCH_FIL_EN | DIGIIN2_GLITCH_FIL_DELAY_50_US );
    error_flag |= digiin2_write_reg( ctx, DIGIIN2_REG_CNFG7, DIGIIN2_HITHR_HIGH | DIGIIN2_CURR_X1 | 
                                                             DIGIIN2_GLITCH_FIL_EN | DIGIIN2_GLITCH_FIL_DELAY_50_US );
    error_flag |= digiin2_write_reg( ctx, DIGIIN2_REG_GLOBLCFG, DIGIIN2_FSPICLEAR_READ | DIGIIN2_LEDINT_CFG_VMLOW );

    return error_flag;
}

void digiin2_set_dev_address ( digiin2_t *ctx, uint8_t device_address )
{
    ctx->device_address = device_address;
}

err_t digiin2_generic_write ( digiin2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t digiin2_generic_read ( digiin2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void digiin2_set_ltc_pin ( digiin2_t *ctx, uint8_t pin_state )
{
    if ( DIGIIN2_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->ltc );
    }
    else
    {
        digital_out_low( &ctx->ltc );
    }
}

uint8_t digiin2_get_rdy_pin ( digiin2_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

uint8_t digiin2_get_flt_pin ( digiin2_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

err_t digiin2_write_reg ( digiin2_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = DIGIIN2_OK;
    uint8_t reg_data = ctx->device_address | ( reg << 1 ) | 0x01;

    if ( DIGIIN2_CRC_ENABLED == ctx->crc_en )
    {
        uint8_t tmp_data[ 2 ] = { 0 };
        tmp_data[ 0 ] = data_in;
        tmp_data[ 1 ] = digiin2_crc5_encode_2byte( reg_data, data_in );
        error_flag |= digiin2_generic_write( ctx, reg_data, tmp_data, 2 );
    }
    else
    {
        error_flag |= digiin2_generic_write( ctx, reg_data, &data_in, 1 );
    }

    return error_flag;
}

err_t digiin2_read_reg ( digiin2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = DIGIIN2_OK;
    uint8_t reg_data = ctx->device_address | ( reg << 1 );

    error_flag |= digiin2_generic_read( ctx, reg_data, data_out, 1 );

    if ( DIGIIN2_CRC_ENABLED == ctx->crc_en )
    {
        uint8_t tmp_data[ 2 ] = { 0 };
        
        error_flag |= digiin2_generic_read( ctx, reg_data, tmp_data, 2 );
        *data_out = tmp_data[ 0 ];
    }
    else
    {
        error_flag |= digiin2_generic_read( ctx, reg_data, data_out, 1 );
    }

    return error_flag;
}

err_t digiin2_read_ch_counter ( digiin2_t *ctx, uint8_t channel_sel, uint16_t *data_out )
{
    err_t error_flag = DIGIIN2_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= digiin2_read_reg( ctx, DIGIIN2_REG_CNT1_LSB + channel_sel, &tmp_data[ 0 ] );
    error_flag |= digiin2_read_reg( ctx, DIGIIN2_REG_CNT1_MSB + channel_sel, &tmp_data[ 1 ] );
    *data_out = ( ( uint16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ];

    return error_flag;
}

void digiin2_pulse_latch ( digiin2_t *ctx )
{
    digiin2_set_ltc_pin( ctx, DIGIIN2_PIN_STATE_LOW );
    Delay_10ms();
    digiin2_set_ltc_pin( ctx, DIGIIN2_PIN_STATE_HIGH );
}

static uint8_t digiin2_crc5_encode_2byte( uint8_t byte1, uint8_t byte2 )
{
    uint8_t crc5_start = 0x1F;
    uint8_t crc5_poly  = 0x15;
    uint8_t crc_result = crc5_start;

    for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
    {
        if( ( ( ( byte1 >> ( 7 - bit_cnt ) ) & 0x01 ) ^ ( ( crc_result & 0x10 ) >> 4 ) ) > 0 )
        {
            crc_result = ( uint8_t ) ( crc5_poly ^ ( ( crc_result << 1 ) & 0x1F ) );
        }
        else
        {
            crc_result = ( uint8_t ) ( ( crc_result << 1 ) & 0x1F );
        }
    }

    for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
    {
        if( ( ( ( byte2 >> ( 7 - bit_cnt ) ) & 0x01 ) ^ ( ( crc_result & 0x10 ) >> 4 ) ) > 0 )
        {
            crc_result = ( uint8_t ) ( crc5_poly ^ ( ( crc_result << 1 ) & 0x1F ) );
        }
        else
        {
            crc_result = ( uint8_t ) ( ( crc_result << 1 ) & 0x1F );
        }
    }

    uint8_t uint8_t3 = 0x00;
    for ( uint8_t bit_cnt = 0; bit_cnt < 3; bit_cnt++ )
    {
        if( ( ( ( uint8_t3 >> ( 7 - bit_cnt ) ) & 0x01 ) ^ ( ( crc_result & 0x10 ) >> 4 ) ) > 0 )
        {
            crc_result = ( uint8_t ) ( crc5_poly ^ ( ( crc_result << 1 ) & 0x1F ) );
        }
        else
        {
            crc_result = ( uint8_t ) ( ( crc_result << 1 ) & 0x1F );
        }
    }

    return crc_result;
}

// ------------------------------------------------------------------------- END
