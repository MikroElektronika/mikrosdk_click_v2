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
 * @file dac13.c
 * @brief DAC 13 Click Driver.
 */

#include "dac13.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dac13_cfg_setup ( dac13_cfg_t *cfg )
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->ldc  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->alt  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t dac13_init ( dac13_t *ctx, dac13_cfg_t *cfg )
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

    digital_out_init( &ctx->ldc, cfg->ldc );
    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->alt, cfg->alt );

    return SPI_MASTER_SUCCESS;
}

err_t dac13_default_cfg ( dac13_t *ctx )
{
    err_t error_flag = DAC13_OK;
    dac13_set_ldc_pin ( ctx, 0 );
    dac13_reset_device ( ctx );
    if ( DAC13_ERROR == dac13_check_communication ( ctx ) )
    {
        return DAC13_ERROR;
    }
    error_flag |= dac13_write_register ( ctx, DAC13_REG_REFERENCE_CONFIG, DAC13_REFERENCE_VOLTAGE_SEL_INT_OUT );
    error_flag |= dac13_set_output_range ( ctx, DAC13_OUT_RANGE_0_TO_5V );
    return error_flag;
}

err_t dac13_generic_write ( dac13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t reg_addr = reg & ( ~DAC13_SPI_READ_BIT );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_addr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dac13_generic_read ( dac13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t reg_addr = reg | DAC13_SPI_READ_BIT;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_addr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dac13_write_register ( dac13_t *ctx, uint8_t reg, uint8_t data_in )
{
    return dac13_generic_write ( ctx, reg, &data_in, 1 );
}

err_t dac13_read_register ( dac13_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return dac13_generic_read ( ctx, reg, data_out, 1 );
}

err_t dac13_write_register_16b ( dac13_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    return dac13_generic_write ( ctx, reg, data_buf, 2 );
}

err_t dac13_read_register_16b ( dac13_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( DAC13_OK == dac13_generic_read ( ctx, reg, data_buf, 2 ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        return DAC13_OK;
    }
    return DAC13_ERROR;
}

void dac13_set_ldc_pin ( dac13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ldc, state );
}

void dac13_set_rst_pin ( dac13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t dac13_get_alert_pin ( dac13_t *ctx )
{
    return digital_in_read ( &ctx->alt );
}

void dac13_reset_device ( dac13_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

err_t dac13_check_communication ( dac13_t *ctx )
{
    uint16_t product_id, vendor_id;
    if ( DAC13_ERROR == dac13_read_register_16b ( ctx, DAC13_REG_PRODUCT_ID_H, &product_id ) )
    {
        return DAC13_ERROR;
    }
    if ( DAC13_ERROR == dac13_read_register_16b ( ctx, DAC13_REG_VENDOR_H, &vendor_id ) )
    {
        return DAC13_ERROR;
    }
    if ( ( DAC13_PRODUCT_ID != product_id ) || ( DAC13_VENDOR_ID != vendor_id ) )
    {
        return DAC13_ERROR;
    }
    return DAC13_OK;
}

err_t dac13_set_output_range ( dac13_t *ctx, uint8_t out_range )
{
    switch ( out_range )
    {
        case DAC13_OUT_RANGE_0_TO_2p5V:
        {
            ctx->v_zero_scale = DAC13_VZS_OUT_RANGE_0_TO_2p5V;
            ctx->v_full_scale = DAC13_VFS_OUT_RANGE_0_TO_2p5V;
            break;
        }
        case DAC13_OUT_RANGE_0_TO_5V:
        {
            ctx->v_zero_scale = DAC13_VZS_OUT_RANGE_0_TO_5V;
            ctx->v_full_scale = DAC13_VFS_OUT_RANGE_0_TO_5V;
            break;
        }
        case DAC13_OUT_RANGE_0_TO_10V:
        {
            ctx->v_zero_scale = DAC13_VZS_OUT_RANGE_0_TO_10V;
            ctx->v_full_scale = DAC13_VFS_OUT_RANGE_0_TO_10V;
            break;
        }
        case DAC13_OUT_RANGE_NEG_5_TO_5V:
        {
            ctx->v_zero_scale = DAC13_VZS_OUT_RANGE_NEG_5_TO_5V;
            ctx->v_full_scale = DAC13_VFS_OUT_RANGE_NEG_5_TO_5V;
            break;
        }
        case DAC13_OUT_RANGE_NEG_2p5_TO_7p5V:
        {
            ctx->v_zero_scale = DAC13_VZS_OUT_RANGE_NEG_2p5_TO_7p5V;
            ctx->v_full_scale = DAC13_VFS_OUT_RANGE_NEG_2p5_TO_7p5V;
            break;
        }
        default:
        {
            return DAC13_ERROR;
        }
    }
    return dac13_write_register ( ctx, DAC13_REG_CH0_OUTPUT_RANGE, out_range );
}

err_t dac13_set_dac_value ( dac13_t *ctx, uint16_t dac_value )
{
    uint16_t reg_data;
    err_t error_flag = dac13_write_register_16b ( ctx, DAC13_REG_CH0_DAC_16B, dac_value );
    error_flag |= dac13_read_register_16b ( ctx, DAC13_REG_CH0_DAC_16B, &reg_data );
    if ( reg_data != dac_value )
    {
        return DAC13_ERROR;
    }
    return error_flag;
}

err_t dac13_set_output_voltage ( dac13_t *ctx, float voltage )
{
    uint16_t dac_value;
    if ( ( voltage < ctx->v_zero_scale ) || ( voltage > ctx->v_full_scale ) )
    {
        return DAC13_ERROR;
    }
    dac_value = ( uint16_t ) ( ( ( voltage - ctx->v_zero_scale ) / 
                                 ( ctx->v_full_scale - ctx->v_zero_scale ) ) * DAC13_DAC_RES_16BIT );
    return dac13_set_dac_value ( ctx, dac_value );
}

// ------------------------------------------------------------------------- END
