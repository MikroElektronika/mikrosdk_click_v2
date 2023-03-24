/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish,distribute, sublicense, and/or sell
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
 * @file tdc2.c
 * @brief TDC 2 Click Driver.
 */

#include "tdc2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void tdc2_cfg_setup ( tdc2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rir  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->dis  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_2;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t tdc2_init ( tdc2_t *ctx, tdc2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rir, cfg->rir );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dis, cfg->dis );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );
    digital_out_low( &ctx->rir );
    digital_out_low( &ctx->dis );

    return SPI_MASTER_SUCCESS;
}

err_t tdc2_default_cfg ( tdc2_t *ctx ) 
{
    err_t error_flag = TDC2_OK;
    
    uint8_t config[ 17 ] = { TDC2_ENABLE_RSTINDX_PIN | TDC2_ENABLE_STOP1_PIN, TDC2_HIT_ENABLE_STOP1, 
                             TDC2_FIFO_COMMON_READ_ON | TDC2_FIFO_BLOCKWISE_READ_ON,
                             DUMMY, DUMMY, DUMMY, TDC2_CFG6_FIXED_VALUE, 
                             TDC2_CFG7_FIXED_VALUE | TDC2_REFERENCE_CLOCK_INTERNAL, 
                             TDC2_CFG8_FIXED_VALUE, TDC2_CFG9_FIXED_VALUE,
                             TDC2_CFG10_FIXED_VALUE, TDC2_CFG11_FIXED_VALUE, TDC2_CFG12_FIXED_VALUE, 
                             TDC2_CFG13_FIXED_VALUE, TDC2_CFG14_FIXED_VALUE, TDC2_CFG15_FIXED_VALUE,
                             TDC2_CFG16_FIXED_VALUE };
    
    error_flag = tdc2_sw_reset( ctx );
    error_flag = tdc2_write_config( ctx, TDC2_REG_CFG0, config, 17 );
    error_flag = tdc2_set_resolution( ctx, TDC2_1pS_RESOLUTION );

    return error_flag;
}

err_t tdc2_generic_write ( tdc2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t tdc2_generic_read ( tdc2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t tdc2_write_config ( tdc2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = TDC2_OK;
    uint8_t reg_addres;
    reg_addres = TDC2_SPIOPC_WRITE_CONFIG + reg;
    
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write( &ctx->spi, &reg_addres, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t tdc2_read_config ( tdc2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = TDC2_OK;
    uint8_t reg_addres;
    reg_addres = TDC2_SPIOPC_READ_CONFIG + reg;
    
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, &reg_addres, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t tdc2_read_results ( tdc2_t *ctx, uint8_t reg, uint32_t *reference_index, uint32_t *stop_result )
{
    err_t error_flag = TDC2_OK;
    uint8_t rx_data[ 6 ];
    uint8_t reg_addres;
    uint32_t tmp_data;
    
    reg_addres = TDC2_SPIOPC_READ_RESULTS + reg;
    
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, &reg_addres, 1, rx_data, 6 );
    spi_master_deselect_device( ctx->chip_select );
    
    tmp_data = rx_data[ 0 ];
    tmp_data <<= 8;
    tmp_data |= rx_data[ 1 ];
    tmp_data <<= 8;
    tmp_data |= rx_data[ 2 ];
    *reference_index = tmp_data;
    
    tmp_data = rx_data[ 3 ];
    tmp_data <<= 8;
    tmp_data |= rx_data[ 4 ];
    tmp_data <<= 8;
    tmp_data |= rx_data[ 5 ];
    *stop_result = tmp_data;
    
    return error_flag;
}

err_t tdc2_send_command ( tdc2_t *ctx, uint8_t command )
{
    err_t error_flag = TDC2_OK;
    
    error_flag = tdc2_generic_write( ctx, command, 0, 0 );
    
    return error_flag;
}

err_t tdc2_sw_reset ( tdc2_t *ctx )
{
    err_t error_flag = TDC2_OK;
    
    error_flag = tdc2_send_command( ctx, TDC2_SPIOPC_POWER );
    Delay_10ms( );
    
    return error_flag;
}

err_t tdc2_start_measuring ( tdc2_t *ctx )
{
    err_t error_flag = TDC2_OK;
    
    error_flag = tdc2_send_command( ctx, TDC2_SPIOPC_INIT );
    
    return error_flag;
}

err_t tdc2_set_resolution ( tdc2_t *ctx, uint32_t resolution )
{
    err_t error_flag = TDC2_OK;
    uint8_t tx_buf[ 3 ];
    tx_buf[ 0 ] = ( uint8_t ) ( resolution & 0xFF );
    tx_buf[ 1 ] = ( uint8_t ) ( ( resolution >> 8 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( ( resolution >> 16 ) & 0xFF );
    
    error_flag = tdc2_write_config( ctx, TDC2_REG_CFG3, tx_buf, 3 );
    
    return error_flag;
}

err_t tdc2_get_resolution ( tdc2_t *ctx, uint32_t *resolution )
{
    err_t error_flag = TDC2_OK;
    uint32_t temp_data;
    uint8_t rx_buf[ 3 ];
    
    error_flag = tdc2_read_config( ctx, TDC2_REG_CFG3, rx_buf, 3 );

    temp_data = rx_buf[ 2 ];
    temp_data <<= 8;
    temp_data |= rx_buf[ 1 ];
    temp_data <<= 8;
    temp_data |= rx_buf[ 0 ];
    
    *resolution = temp_data;
    
    return error_flag;
}

void tdc2_reset_index ( tdc2_t *ctx )
{
    digital_out_high( &ctx->rir );
    Delay_1ms( );
    digital_out_low( &ctx->rir );
}

void tdc2_disable_stop_channels ( tdc2_t *ctx )
{
    digital_out_high( &ctx->rir );
}

void tdc2_enable_stop_channels ( tdc2_t *ctx )
{
    digital_out_low( &ctx->rir );
}

uint8_t tdc2_get_int_state ( tdc2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t tdc2_get_time_between_stops ( tdc2_t *ctx, uint32_t stop_result1, uint32_t reference_index1, 
                                    uint32_t stop_result2, uint32_t reference_index2, 
                                    uint32_t *time_in_us )
{
    err_t error_flag = TDC2_OK;
    uint32_t resolution = 0;
    uint32_t resolution_10us;
    error_flag = tdc2_get_resolution( ctx, &resolution );
    // Dividing the resolution to convert it to 10 uS resolution to avoid data overflow.
    resolution_10us = resolution / 100;
    
    *time_in_us = ( ( stop_result2 - stop_result1 ) + 
                  ( reference_index2 - reference_index1 ) * resolution_10us ) / 10;
    
    return error_flag;
}


// ------------------------------------------------------------------------- END
