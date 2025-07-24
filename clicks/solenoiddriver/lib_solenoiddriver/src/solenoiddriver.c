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
 * @file solenoiddriver.c
 * @brief Solenoid Driver Click Driver.
 */

#include "solenoiddriver.h"

/**
 * @brief Dummy and SPI Read/Write data.
 * @details Definition of dummy and SPI Read/Write data.
 */
#define SOLENOIDDRIVER_SPI_DUMMY            0x00
#define SOLENOIDDRIVER_SPI_READ_MASK        0x40
#define SOLENOIDDRIVER_SPI_WRITE_MASK       0x80
#define SOLENOIDDRIVER_SPI_READ_DIAG_MASK   0x01
#define SOLENOIDDRIVER_SPI_READ_REG_MASK    0x02

void solenoiddriver_cfg_setup ( solenoiddriver_cfg_t *cfg ) 
{
    cfg->sck   = HAL_PIN_NC;
    cfg->miso  = HAL_PIN_NC;
    cfg->mosi  = HAL_PIN_NC;
    cfg->cs    = HAL_PIN_NC;
    cfg->in1   = HAL_PIN_NC;
    cfg->sleep = HAL_PIN_NC;
    cfg->in0   = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t solenoiddriver_init ( solenoiddriver_t *ctx, solenoiddriver_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, SOLENOIDDRIVER_SPI_DUMMY ) ) 
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

    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->sleep, cfg->sleep );
    digital_out_init( &ctx->in0, cfg->in0 );

    return SPI_MASTER_SUCCESS;
}

err_t solenoiddriver_default_cfg ( solenoiddriver_t *ctx ) 
{
    err_t error_flag = SOLENOIDDRIVER_OK;
    SOLENOIDDRIVER_SET_DATA_SAMPLE_EDGE;
    solenoiddriver_exit_sleep ( ctx );
    Delay_100ms ( );
    error_flag |= solenoiddriver_unlock_settings ( ctx );
    error_flag |= solenoiddriver_reset_device ( ctx );
    Delay_100ms ( );
    error_flag |= solenoiddriver_clear_latch ( ctx );
    error_flag |= solenoiddriver_write_reg ( ctx, SOLENOIDDRIVER_REG_CONFIG, SOLENOIDDRIVER_CONFIG_ACT | 
                                                                             SOLENOIDDRIVER_CONFIG_OCP );
    error_flag |= solenoiddriver_write_reg ( ctx, SOLENOIDDRIVER_REG_CONFIG2, SOLENOIDDRIVER_CONFIG2_SR_3V );
    Delay_100ms ( );
    return error_flag;
}

err_t solenoiddriver_write_reg ( solenoiddriver_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = SOLENOIDDRIVER_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( reg & ( ~SOLENOIDDRIVER_SPI_READ_MASK ) ) | SOLENOIDDRIVER_SPI_WRITE_MASK;
    data_buf[ 1 ] = data_in;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->diagnosis = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return error_flag;
}

err_t solenoiddriver_read_reg ( solenoiddriver_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = SOLENOIDDRIVER_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( reg & ( ~SOLENOIDDRIVER_SPI_WRITE_MASK ) ) | SOLENOIDDRIVER_SPI_READ_MASK;
    if ( SOLENOIDDRIVER_REG_STANDARD_DIAGNOSIS == reg )
    {
        data_buf[ 1 ] = SOLENOIDDRIVER_SPI_READ_DIAG_MASK;
    }
    else
    {
        data_buf[ 1 ] = SOLENOIDDRIVER_SPI_READ_REG_MASK;
    }
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( SOLENOIDDRIVER_REG_STANDARD_DIAGNOSIS == reg )
    {
        ctx->diagnosis = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    else if ( NULL != data_out )
    {
        if ( ( SOLENOIDDRIVER_SPI_WRITE_MASK == ( data_buf[ 0 ] & SOLENOIDDRIVER_SPI_WRITE_MASK ) ) && 
             ( SOLENOIDDRIVER_SPI_READ_MASK != ( data_buf[ 0 ] & SOLENOIDDRIVER_SPI_READ_MASK ) ) )
        {
            *data_out = data_buf[ 1 ];
        }
        else
        {
            error_flag |= SOLENOIDDRIVER_ERROR;
        }
    }
    else
    {
        error_flag |= SOLENOIDDRIVER_ERROR;
    }
    return error_flag;
}

void solenoiddriver_set_in0_pin ( solenoiddriver_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in0, state );
}

void solenoiddriver_set_in1_pin ( solenoiddriver_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in1, state );
}

void solenoiddriver_set_sleep_pin ( solenoiddriver_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sleep, state );
}

void solenoiddriver_enter_sleep ( solenoiddriver_t *ctx )
{
    digital_out_low ( &ctx->in0 );
    digital_out_low ( &ctx->in1 );
    digital_out_low ( &ctx->sleep );
}

void solenoiddriver_exit_sleep ( solenoiddriver_t *ctx )
{
    digital_out_low ( &ctx->in0 );
    digital_out_low ( &ctx->in1 );
    digital_out_high ( &ctx->sleep );
}

err_t solenoiddriver_reset_device ( solenoiddriver_t *ctx )
{
    err_t error_flag = SOLENOIDDRIVER_OK;
    uint8_t config = 0;
    error_flag |= solenoiddriver_read_reg ( ctx, SOLENOIDDRIVER_REG_CONFIG, &config );
    config |= SOLENOIDDRIVER_CONFIG_RST;
    error_flag |= solenoiddriver_write_reg ( ctx, SOLENOIDDRIVER_REG_CONFIG, config );
    return error_flag;
}

err_t solenoiddriver_lock_settings ( solenoiddriver_t *ctx )
{
    err_t error_flag = SOLENOIDDRIVER_OK;
    uint8_t config = 0;
    error_flag |= solenoiddriver_read_reg ( ctx, SOLENOIDDRIVER_REG_CONFIG2, &config );
    config &= ( ~SOLENOIDDRIVER_CONFIG2_LOCK_MASK );
    config |= SOLENOIDDRIVER_CONFIG2_LOCK_SET_LOCK;
    error_flag |= solenoiddriver_write_reg ( ctx, SOLENOIDDRIVER_REG_CONFIG2, config );
    return error_flag;
}

err_t solenoiddriver_unlock_settings ( solenoiddriver_t *ctx )
{
    err_t error_flag = SOLENOIDDRIVER_OK;
    uint8_t config = 0;
    error_flag |= solenoiddriver_read_reg ( ctx, SOLENOIDDRIVER_REG_CONFIG2, &config );
    config &= ( ~SOLENOIDDRIVER_CONFIG2_LOCK_MASK );
    config |= SOLENOIDDRIVER_CONFIG2_LOCK_SET_UNLOCK;
    error_flag |= solenoiddriver_write_reg ( ctx, SOLENOIDDRIVER_REG_CONFIG2, config );
    return error_flag;
}

err_t solenoiddriver_clear_latch ( solenoiddriver_t *ctx )
{
    return solenoiddriver_write_reg ( ctx, SOLENOIDDRIVER_REG_OUT_CLEAR_LATCH, 
                                      SOLENOIDDRIVER_OUT_CLEAR_LATCH_CLR3 | 
                                      SOLENOIDDRIVER_OUT_CLEAR_LATCH_CLR2 | 
                                      SOLENOIDDRIVER_OUT_CLEAR_LATCH_CLR1 | 
                                      SOLENOIDDRIVER_OUT_CLEAR_LATCH_CLR0 );
}

err_t solenoiddriver_set_output ( solenoiddriver_t *ctx, uint8_t out_ctrl )
{
    return solenoiddriver_write_reg ( ctx, SOLENOIDDRIVER_REG_OUT_CTRL, out_ctrl );
}

// ------------------------------------------------------------------------- END
