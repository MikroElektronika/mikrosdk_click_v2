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
 * @file angle8.c
 * @brief Angle 8 Click Driver.
 */

#include "angle8.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void angle8_cfg_setup ( angle8_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->nd   = HAL_PIN_NC;
    cfg->dv   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->mgl  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t angle8_init ( angle8_t *ctx, angle8_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->nd, cfg->nd );
    digital_in_init( &ctx->dv, cfg->dv );
    digital_in_init( &ctx->mgl, cfg->mgl );

    return SPI_MASTER_SUCCESS;
}

err_t angle8_default_cfg ( angle8_t *ctx ) 
{
    err_t error_flag = ANGLE8_OK;
    angle8_enable_device ( ctx );
    Delay_10ms ( );
    
    error_flag |= angle8_write_register ( ctx, ANGLE8_REG_ROTATION_DIRECTION, ANGLE8_ROTATION_DIRECTION_CW );
    error_flag |= angle8_set_cycle_time ( ctx, ANGLE8_CYCLE_TIME_100MS );
    
    error_flag |= angle8_store_all_registers ( ctx );
    error_flag |= angle8_clear_error_flags ( ctx );
    
    return error_flag;
}

err_t angle8_write_register ( angle8_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    if ( ( reg > ANGLE8_REG_ASC_MODE_CONFIG ) && ( ANGLE8_REG_FILTER_WINDOW != reg ) )
    {
        return ANGLE8_ERROR;
    }
    uint8_t tx_buf[ 2 ] = { reg | ANGLE8_CMD_WRITE_REGISTER, data_in };
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( tx_buf[ 1 ] != rx_buf[ 1 ] )
    {
        return ANGLE8_ERROR;
    }
    return error_flag;
}

err_t angle8_read_register ( angle8_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    if ( ( reg > ANGLE8_REG_ASC_MODE_CONFIG ) && ( ANGLE8_REG_FILTER_WINDOW != reg ) && 
         ( ANGLE8_REG_ERROR_FLAGS != reg ) && ( ANGLE8_REG_ALARM_FLAGS != reg ) )
    {
        return ANGLE8_ERROR;
    }
    uint8_t tx_buf[ 2 ] = { reg | ANGLE8_CMD_READ_REGISTER, 0 };
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write ( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = rx_buf[ 1 ];
    return error_flag;
}

err_t angle8_read_angle ( angle8_t *ctx, float *angle ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    uint16_t raw_angle = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
    *angle = ( ( float ) raw_angle / ANGLE8_RESOLUTION ) * ANGLE8_FULL_CIRCLE;
    return error_flag;
}

err_t angle8_clear_error_flags ( angle8_t *ctx ) 
{
    uint8_t tx_buf[ 2 ] = { ANGLE8_CMD_CLEAR_ERROR_FLAGS, 0 };
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t angle8_store_single_register ( angle8_t *ctx, uint8_t reg ) 
{
    if ( ( reg > ANGLE8_REG_ASC_MODE_CONFIG ) && ( ANGLE8_REG_FILTER_WINDOW != reg ) )
    {
        return ANGLE8_ERROR;
    }
    uint8_t tx_buf[ 2 ] = { reg | ANGLE8_CMD_STORE_SINGLE_REGISTER, 0 };
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t angle8_store_all_registers ( angle8_t *ctx ) 
{
    uint8_t tx_buf[ 2 ] = { ANGLE8_CMD_STORE_ALL_REGISTERS, 0 };
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t angle8_restore_all_registers ( angle8_t *ctx ) 
{
    uint8_t tx_buf[ 2 ] = { ANGLE8_CMD_RESTORE_ALL_REGISTERS, 0 };
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void angle8_enable_device ( angle8_t *ctx ) 
{
    digital_out_low ( &ctx->en );
}

void angle8_disable_device ( angle8_t *ctx ) 
{
    digital_out_high ( &ctx->en );
}

uint8_t angle8_get_nd_pin ( angle8_t *ctx ) 
{
    return digital_in_read ( &ctx->nd );
}

uint8_t angle8_get_dv_pin ( angle8_t *ctx ) 
{
    return digital_in_read ( &ctx->dv );
}

uint8_t angle8_get_mgl_pin ( angle8_t *ctx ) 
{
    return digital_in_read ( &ctx->mgl );
}

err_t angle8_set_cycle_time ( angle8_t *ctx, float time_ms )
{
    if ( ( time_ms < ANGLE8_CYCLE_TIME_MIN ) || ( time_ms > ANGLE8_CYCLE_TIME_MAX ) )
    {
        return ANGLE8_ERROR;
    }
    uint16_t raw_time_ms = ( uint16_t ) ( time_ms * 10 );
    err_t error_flag = angle8_write_register ( ctx, ANGLE8_REG_CYCLE_TIME_LSB, ( uint8_t ) ( raw_time_ms & 0xFF ) );
    error_flag |= angle8_write_register ( ctx, ANGLE8_REG_CYCLE_TIME_MSB, ( uint8_t ) ( ( raw_time_ms >> 8 ) & 0xFF ) );
    return error_flag;
}

// ------------------------------------------------------------------------- END
