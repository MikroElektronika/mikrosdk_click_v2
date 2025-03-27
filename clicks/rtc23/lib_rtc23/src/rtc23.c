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
 * @file rtc23.c
 * @brief RTC 23 Click Driver.
 */

#include "rtc23.h"
#include "conversions.h"

/**
 * @brief Dummy data and SPI RW bit.
 * @details Definition of dummy data and SPI RW bit.
 */
#define DUMMY               0x00
#define RTC23_SPI_RW_BIT    0x80

void rtc23_cfg_setup ( rtc23_cfg_t *cfg ) 
{
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->wdi = HAL_PIN_NC;
    cfg->psw = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t rtc23_init ( rtc23_t *ctx, rtc23_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wdi, cfg->wdi );

    digital_in_init( &ctx->psw, cfg->psw );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t rtc23_write_regs ( rtc23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t reg_addr = reg | RTC23_SPI_RW_BIT;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_addr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t rtc23_read_regs ( rtc23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t reg_addr = reg & ( ~RTC23_SPI_RW_BIT );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_addr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t rtc23_write_reg ( rtc23_t *ctx, uint8_t reg, uint8_t data_in )
{
    return rtc23_write_regs( ctx, reg, &data_in, 1 );
}

err_t rtc23_read_reg ( rtc23_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return rtc23_read_regs( ctx, reg, data_out, 1 );
}

void rtc23_set_wdi_pin ( rtc23_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wdi, state );
}

uint8_t rtc23_get_psw_pin ( rtc23_t *ctx )
{
    return digital_in_read ( &ctx->psw );
}

uint8_t rtc23_get_int_pin ( rtc23_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtc23_check_communication ( rtc23_t *ctx )
{
    uint8_t device_id = 0;
    if ( RTC23_OK == rtc23_read_reg ( ctx, RTC23_REG_ID0, &device_id ) )
    {
        if ( RTC23_DEVICE_ID == device_id )
        {
            return RTC23_OK;
        }
    }
    return RTC23_ERROR;
}

err_t rtc23_set_time ( rtc23_t *ctx, rtc23_time_t *time )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( time->second_100th );
    data_buf[ 1 ] = dec_to_bcd ( time->second );
    data_buf[ 2 ] = dec_to_bcd ( time->minute );
    data_buf[ 3 ] = dec_to_bcd ( time->hour );
    if ( RTC23_ERROR == rtc23_write_regs ( ctx, RTC23_REG_HUNDREDTHS, data_buf, 4 ) )
    {
        return RTC23_ERROR;
    }
    return RTC23_OK;
}

err_t rtc23_read_time ( rtc23_t *ctx, rtc23_time_t *time )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC23_ERROR == rtc23_read_regs ( ctx, RTC23_REG_HUNDREDTHS, data_buf, 4 ) )
    {
        return RTC23_ERROR;
    }
    time->second_100th = bcd_to_dec ( data_buf[ 0 ] );
    time->second = bcd_to_dec ( data_buf[ 1 ] );
    time->minute = bcd_to_dec ( data_buf[ 2 ] );
    time->hour = bcd_to_dec ( data_buf[ 3 ] );
    return RTC23_OK;
}

err_t rtc23_set_date ( rtc23_t *ctx, rtc23_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( date->day );
    data_buf[ 1 ] = dec_to_bcd ( date->month );
    data_buf[ 2 ] = dec_to_bcd ( date->year );
    data_buf[ 3 ] = dec_to_bcd ( date->day_of_week );
    if ( RTC23_ERROR == rtc23_write_regs ( ctx, RTC23_REG_DATE, data_buf, 4 ) )
    {
        return RTC23_ERROR;
    }
    return RTC23_OK;
}

err_t rtc23_read_date ( rtc23_t *ctx, rtc23_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC23_ERROR == rtc23_read_regs ( ctx, RTC23_REG_DATE, data_buf, 4 ) )
    {
        return RTC23_ERROR;
    }
    date->day = bcd_to_dec ( data_buf[ 0 ] );
    date->month = bcd_to_dec ( data_buf[ 1 ] );
    date->year = bcd_to_dec ( data_buf[ 2 ] );
    date->day_of_week = data_buf[ 3 ];
    return RTC23_OK;
}

// ------------------------------------------------------------------------- END
