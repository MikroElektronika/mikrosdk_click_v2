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
 * @file solidswitch3.c
 * @brief SolidSwitch 3 Click Driver.
 */

#include "solidswitch3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void solidswitch3_cfg_setup ( solidswitch3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->in1  = HAL_PIN_NC;
    cfg->in2  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t solidswitch3_init ( solidswitch3_t *ctx, solidswitch3_cfg_t *cfg ) 
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

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );

    return SPI_MASTER_SUCCESS;
}

err_t solidswitch3_default_cfg ( solidswitch3_t *ctx ) 
{
    err_t error_flag = SOLIDSWITCH3_OK;
    
    solidswitch3_set_dir_mode ( ctx, SOLIDSWITCH3_DIR_MODE_SPI );
    solidswitch3_set_in1_pin ( ctx, 0 );
    solidswitch3_set_in2_pin ( ctx, 0 );
    solidswitch3_reset ( ctx );
    
    // disable all outputs
    error_flag |= solidswitch3_write_data ( ctx, 0 );

    return error_flag;
}

err_t solidswitch3_write_data ( solidswitch3_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &data_buf[ 0 ], 2 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, data_buf[ 0 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, data_buf[ 1 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->output_state = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return error_flag;
}

err_t solidswitch3_enable_output ( solidswitch3_t *ctx, uint8_t channel )
{
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        if ( channel & ( SOLIDSWITCH3_CH_OUT1 << cnt ) )
        {
            ctx->output_state &= ~( SOLIDSWITCH3_OUT_BITS_MASK << ( cnt * 2 ) );
            ctx->output_state |= ( SOLIDSWITCH3_OUT_ENABLE << ( cnt * 2 ) );
        }
    }
    return solidswitch3_write_data ( ctx, ctx->output_state );
}

err_t solidswitch3_disable_output ( solidswitch3_t *ctx, uint8_t channel )
{
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        if ( channel & ( SOLIDSWITCH3_CH_OUT1 << cnt ) )
        {
            ctx->output_state &= ~( SOLIDSWITCH3_OUT_BITS_MASK << ( cnt * 2 ) );
        }
    }
    return solidswitch3_write_data ( ctx, ctx->output_state );
}

void solidswitch3_reset ( solidswitch3_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void solidswitch3_set_dir_mode ( solidswitch3_t *ctx, uint8_t dir_mode )
{
    digital_out_write ( &ctx->dir, dir_mode );
}

void solidswitch3_set_rst_pin ( solidswitch3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void solidswitch3_set_in1_pin ( solidswitch3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in1, state );
}

void solidswitch3_set_in2_pin ( solidswitch3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in2, state );
}

// ------------------------------------------------------------------------- END
