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
 * @file rtc25.c
 * @brief RTC 25 Click Driver.
 */

#include "rtc25.h"
#include "conversions.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief RTC 25 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtc25_i2c_write ( rtc25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 25 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtc25_i2c_read ( rtc25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 25 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtc25_spi_write ( rtc25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 25 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtc25_spi_read ( rtc25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void rtc25_cfg_setup ( rtc25_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->ts3  = HAL_PIN_NC;
    cfg->ts4  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC25_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = RTC25_DRV_SEL_I2C;
}

void rtc25_drv_interface_sel ( rtc25_cfg_t *cfg, rtc25_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t rtc25_init ( rtc25_t *ctx, rtc25_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( RTC25_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = rtc25_i2c_read;
        ctx->write_f = rtc25_i2c_write;
    } 
    else 
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

        ctx->read_f  = rtc25_spi_read;
        ctx->write_f = rtc25_spi_write;
    }

    digital_out_init( &ctx->ts3, cfg->ts3 );
    digital_out_init( &ctx->ts4, cfg->ts4 );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    Delay_10ms ( );
    digital_out_high ( &ctx->ts3 );
    digital_out_high ( &ctx->ts4 );

    return RTC25_OK;
}

err_t rtc25_default_cfg ( rtc25_t *ctx ) 
{
    err_t error_flag = RTC25_OK;

    if ( RTC25_ERROR == rtc25_check_communication ( ctx ) )
    {
        return RTC25_ERROR;
    }
    
    error_flag |= rtc25_write_reg ( ctx, RTC25_REG_SR_RESET, RTC25_SR_RESET_SOFT_RESET );
    Delay_100ms ( );
    
    error_flag |= rtc25_write_reg ( ctx, RTC25_REG_CONTROL_1, RTC25_CONTROL_1_FIXED_BITS | 
                                                              RTC25_CONTROL_1_SECOND_INT_EN );
    
    error_flag |= rtc25_write_reg ( ctx, RTC25_REG_INT_A_MASK1, RTC25_INT_MASK1_MI | 
                                                                RTC25_INT_MASK1_WD_CD | 
                                                                RTC25_INT_MASK1_AIE | 
                                                                RTC25_INT_MASK1_BIE | 
                                                                RTC25_INT_MASK1_BLIE );
    Delay_100ms ( );

    return error_flag;
}

err_t rtc25_write_regs ( rtc25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t rtc25_read_regs ( rtc25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t rtc25_write_reg ( rtc25_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t rtc25_read_reg ( rtc25_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

void rtc25_set_ts3_pin ( rtc25_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ts3, state );
}

void rtc25_set_ts4_pin ( rtc25_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ts4, state );
}

uint8_t rtc25_get_int_pin ( rtc25_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtc25_check_communication ( rtc25_t *ctx )
{
    uint8_t sr_reset = 0;
    if ( RTC25_OK == rtc25_read_reg ( ctx, RTC25_REG_SR_RESET, &sr_reset ) )
    {
        if ( RTC25_SR_RESET_READ == sr_reset )
        {
            return RTC25_OK;
        }
    }
    return RTC25_ERROR;
}

err_t rtc25_stop_clock ( rtc25_t *ctx )
{
    uint8_t control_1 = 0;
    if ( RTC25_OK == rtc25_read_reg ( ctx, RTC25_REG_CONTROL_1, &control_1 ) )
    {
        control_1 |= RTC25_CONTROL_1_STOP_CLOCK;
        if ( RTC25_OK == rtc25_write_reg ( ctx, RTC25_REG_CONTROL_1, control_1 ) )
        {
            return RTC25_OK;
        }
    }
    return RTC25_ERROR;
}

err_t rtc25_start_clock ( rtc25_t *ctx )
{
    uint8_t control_1 = 0;
    if ( RTC25_OK == rtc25_read_reg ( ctx, RTC25_REG_CONTROL_1, &control_1 ) )
    {
        control_1 &= ( ~RTC25_CONTROL_1_STOP_CLOCK );
        if ( RTC25_OK == rtc25_write_reg ( ctx, RTC25_REG_CONTROL_1, control_1 ) )
        {
            return RTC25_OK;
        }
    }
    return RTC25_ERROR;
}

err_t rtc25_clear_prescaler ( rtc25_t *ctx )
{
    return rtc25_write_reg ( ctx, RTC25_REG_SR_RESET, RTC25_SR_RESET_CLEAR_PRESCALER );
}

err_t rtc25_clear_msf ( rtc25_t *ctx )
{
    uint8_t control_2 = 0;
    if ( RTC25_OK == rtc25_read_reg ( ctx, RTC25_REG_CONTROL_2, &control_2 ) )
    {
        control_2 &= ( ~RTC25_CONTROL_2_MSF );
        if ( RTC25_OK == rtc25_write_reg ( ctx, RTC25_REG_CONTROL_2, control_2 ) )
        {
            return RTC25_OK;
        }
    }
    return RTC25_ERROR;
}

err_t rtc25_set_time ( rtc25_t *ctx, rtc25_time_t *time )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( time->second_100th );
    data_buf[ 1 ] = dec_to_bcd ( time->second );
    data_buf[ 2 ] = dec_to_bcd ( time->minute );
    data_buf[ 3 ] = dec_to_bcd ( time->hour );
    if ( RTC25_ERROR == rtc25_write_regs ( ctx, RTC25_REG_100TH_SECONDS, data_buf, 4 ) )
    {
        return RTC25_ERROR;
    }
    return RTC25_OK;
}

err_t rtc25_read_time ( rtc25_t *ctx, rtc25_time_t *time )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC25_ERROR == rtc25_read_regs ( ctx, RTC25_REG_100TH_SECONDS, data_buf, 4 ) )
    {
        return RTC25_ERROR;
    }
    if ( data_buf[ 1 ] & RTC25_SECONDS_OSF )
    {
        return RTC25_ERROR;
    }
    time->second_100th = bcd_to_dec ( data_buf[ 0 ] );
    time->second = bcd_to_dec ( data_buf[ 1 ] & RTC25_SECONDS_SEC_MASK );
    time->minute = bcd_to_dec ( data_buf[ 2 ] );
    time->hour = bcd_to_dec ( data_buf[ 3 ] );
    return RTC25_OK;
}

err_t rtc25_set_date ( rtc25_t *ctx, rtc25_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( date->day );
    data_buf[ 1 ] = dec_to_bcd ( date->day_of_week );
    data_buf[ 2 ] = dec_to_bcd ( date->month );
    data_buf[ 3 ] = dec_to_bcd ( date->year );
    if ( RTC25_ERROR == rtc25_write_regs ( ctx, RTC25_REG_DAYS, data_buf, 4 ) )
    {
        return RTC25_ERROR;
    }
    return RTC25_OK;
}

err_t rtc25_read_date ( rtc25_t *ctx, rtc25_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC25_ERROR == rtc25_read_regs ( ctx, RTC25_REG_DAYS, data_buf, 4 ) )
    {
        return RTC25_ERROR;
    }
    date->day = bcd_to_dec ( data_buf[ 0 ] );
    date->day_of_week = data_buf[ 1 ];
    date->month = bcd_to_dec ( data_buf[ 2 ] );
    date->year = bcd_to_dec ( data_buf[ 3 ] );
    return RTC25_OK;
}

err_t rtc25_set_time_date ( rtc25_t *ctx, rtc25_time_t *time, rtc25_date_t *date )
{
    err_t error_flag = RTC25_OK;
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( time->second_100th );
    data_buf[ 1 ] = dec_to_bcd ( time->second );
    data_buf[ 2 ] = dec_to_bcd ( time->minute );
    data_buf[ 3 ] = dec_to_bcd ( time->hour );
    data_buf[ 4 ] = dec_to_bcd ( date->day );
    data_buf[ 5 ] = dec_to_bcd ( date->day_of_week );
    data_buf[ 6 ] = dec_to_bcd ( date->month );
    data_buf[ 7 ] = dec_to_bcd ( date->year );
    error_flag |= rtc25_stop_clock ( ctx );
    if ( RTC25_OK == error_flag )
    {
        error_flag |= rtc25_clear_prescaler ( ctx );
    }
    if ( RTC25_OK == error_flag )
    {
        error_flag |= rtc25_write_regs ( ctx, RTC25_REG_100TH_SECONDS, data_buf, 8 );
    }
    if ( RTC25_OK == error_flag )
    {
        error_flag |= rtc25_start_clock ( ctx );
    }
    return RTC25_OK;
}

err_t rtc25_read_time_date ( rtc25_t *ctx, rtc25_time_t *time, rtc25_date_t *date )
{
    uint8_t data_buf[ 8 ] = { 0 };
    if ( RTC25_ERROR == rtc25_read_regs ( ctx, RTC25_REG_100TH_SECONDS, data_buf, 8 ) )
    {
        return RTC25_ERROR;
    }
    if ( data_buf[ 1 ] & RTC25_SECONDS_OSF )
    {
        return RTC25_ERROR;
    }
    time->second_100th = bcd_to_dec ( data_buf[ 0 ] );
    time->second = bcd_to_dec ( data_buf[ 1 ] & RTC25_SECONDS_SEC_MASK );
    time->minute = bcd_to_dec ( data_buf[ 2 ] );
    time->hour = bcd_to_dec ( data_buf[ 3 ] );
    date->day = bcd_to_dec ( data_buf[ 4 ] );
    date->day_of_week = data_buf[ 5 ];
    date->month = bcd_to_dec ( data_buf[ 6 ] );
    date->year = bcd_to_dec ( data_buf[ 7 ] );
    return RTC25_OK;
}

static err_t rtc25_i2c_write ( rtc25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t rtc25_i2c_read ( rtc25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t rtc25_spi_write ( rtc25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t rtc25_spi_read ( rtc25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
