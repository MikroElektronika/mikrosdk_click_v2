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
 * @file leddriver16.c
 * @brief LED Driver 16 Click Driver.
 */

#include "leddriver16.h"

/**
 * @brief Dummy data and read bit.
 * @details Definition of dummy data and read bit.
 */
#define DUMMY                       0x00
#define LEDDRIVER16_SPI_READ_BIT    0x01

void leddriver16_cfg_setup ( leddriver16_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->oe   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t leddriver16_init ( leddriver16_t *ctx, leddriver16_cfg_t *cfg ) 
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
    digital_out_init( &ctx->oe, cfg->oe );

    return SPI_MASTER_SUCCESS;
}

err_t leddriver16_default_cfg ( leddriver16_t *ctx ) 
{
    err_t error_flag = LEDDRIVER16_OK;
    leddriver16_enable_device ( ctx );
    leddriver16_enable_output ( ctx );
    error_flag |= leddriver16_write_register ( ctx, LEDDRIVER16_REG_MODE1, LEDDRIVER16_MODE1_NORMAL_MODE );
    error_flag |= leddriver16_clear_errors ( ctx );
    error_flag |= leddriver16_set_led_state ( ctx, LEDDRIVER16_LED_CHANNEL_ALL, LEDDRIVER16_LEDOUT_PWM_ALL );
    error_flag |= leddriver16_set_led_iref ( ctx, LEDDRIVER16_LED_CHANNEL_ALL, LEDDRIVER16_IREF_MAX );
    error_flag |= leddriver16_set_led_pwm ( ctx, LEDDRIVER16_LED_CHANNEL_ALL, LEDDRIVER16_PWM_DUTY_MIN );
    return error_flag;
}

err_t leddriver16_write_register ( leddriver16_t *ctx, uint8_t reg, uint8_t data_in )
{
    if ( reg > LEDDRIVER16_REG_EFLAG3 )
    {
        return LEDDRIVER16_ERROR;
    }
    uint8_t reg_addr = reg << 1;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_addr, 1 );
    error_flag |= spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t leddriver16_read_register ( leddriver16_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( reg > LEDDRIVER16_REG_EFLAG3 )
    {
        return LEDDRIVER16_ERROR;
    }
    uint8_t reg_addr = ( reg << 1 ) | LEDDRIVER16_SPI_READ_BIT;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_addr, 1, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void leddriver16_disable_device ( leddriver16_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void leddriver16_enable_device ( leddriver16_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void leddriver16_disable_output ( leddriver16_t *ctx )
{
    digital_out_high ( &ctx->oe );
}

void leddriver16_enable_output ( leddriver16_t *ctx )
{
    digital_out_low ( &ctx->oe );
}

err_t leddriver16_clear_errors ( leddriver16_t *ctx )
{
    uint8_t mode2 = 0;
    if ( LEDDRIVER16_OK == leddriver16_read_register ( ctx, LEDDRIVER16_REG_MODE2, &mode2 ) )
    {
        mode2 |= LEDDRIVER16_MODE2_CLRERR;
        return leddriver16_write_register ( ctx, LEDDRIVER16_REG_MODE2, mode2 );
    }
    return LEDDRIVER16_ERROR;
}

err_t leddriver16_set_led_state ( leddriver16_t *ctx, uint16_t led_ch_mask, uint8_t state )
{
    if ( state > LEDDRIVER16_LEDOUT_PWM_GRPPWM )
    {
        return LEDDRIVER16_ERROR;
    }
    uint8_t ledout = 0;
    uint8_t grp_mask = 0;
    err_t error_flag = LEDDRIVER16_OK;
    for ( uint8_t grp_cnt = 0; grp_cnt < 4; grp_cnt++ )
    {
        if ( led_ch_mask & ( LEDDRIVER16_LED_CHANNEL_GRP0 << ( grp_cnt * 4 ) ) )
        {
            grp_mask = ( led_ch_mask >> ( grp_cnt * 4 ) ) & LEDDRIVER16_LED_CHANNEL_GRP0;
            error_flag |= leddriver16_read_register ( ctx, LEDDRIVER16_REG_LEDOUT0 + grp_cnt, &ledout );
            for ( uint8_t led_cnt = 0; led_cnt < 4; led_cnt++ )
            {
                if ( ( grp_mask >> led_cnt ) & LEDDRIVER16_LED_CHANNEL_0 )
                {
                    ledout &= ~( LEDDRIVER16_LEDOUT_MASK << ( led_cnt * 2 ) );
                    ledout |= ( state << ( led_cnt * 2 ) );
                }
            }
            error_flag |= leddriver16_write_register ( ctx, LEDDRIVER16_REG_LEDOUT0 + grp_cnt, ledout );
        }
    }
    return error_flag;
}

err_t leddriver16_set_led_pwm ( leddriver16_t *ctx, uint16_t led_ch_mask, uint8_t duty_cycle )
{
    err_t error_flag = LEDDRIVER16_OK;
    if ( LEDDRIVER16_LED_CHANNEL_ALL == led_ch_mask )
    {
        return leddriver16_write_register ( ctx, LEDDRIVER16_REG_PWMALL, duty_cycle );
    }
    for ( uint8_t led_cnt = 0; led_cnt < 16; led_cnt++ )
    {
        if ( ( led_ch_mask >> led_cnt ) & LEDDRIVER16_LED_CHANNEL_0 )
        {
            error_flag |= leddriver16_write_register ( ctx, LEDDRIVER16_REG_PWM0 + led_cnt, duty_cycle );
        }
    }
    return error_flag;
}

err_t leddriver16_set_led_iref ( leddriver16_t *ctx, uint16_t led_ch_mask, uint8_t iref )
{
    err_t error_flag = LEDDRIVER16_OK;
    if ( LEDDRIVER16_LED_CHANNEL_ALL == led_ch_mask )
    {
        return leddriver16_write_register ( ctx, LEDDRIVER16_REG_IREFALL, iref );
    }
    for ( uint8_t led_cnt = 0; led_cnt < 16; led_cnt++ )
    {
        if ( ( led_ch_mask >> led_cnt ) & LEDDRIVER16_LED_CHANNEL_0 )
        {
            error_flag |= leddriver16_write_register ( ctx, LEDDRIVER16_REG_IREF0 + led_cnt, iref );
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
