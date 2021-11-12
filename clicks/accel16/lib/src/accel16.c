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
 * @file accel16.c
 * @brief Accel 16 Click Driver.
 */

#include "accel16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY               0x00
#define DEFAULT_RES         1000.0
#define TEMPERATURE_RES     0.065
#define ADC_10PCT           0.33
#define ADC_VREF            2.64
#define ADC_RESOLUTION      4095.0
#define ADC_OFFSET          2048

void accel16_cfg_setup ( accel16_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int2 = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t accel16_init ( accel16_t *ctx, accel16_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return SPI_MASTER_SUCCESS;
}

err_t accel16_default_cfg ( accel16_t *ctx ) 
{
    err_t error_flag = ACCEL16_OK;
    
    error_flag |= accel16_single_reg_write( ctx, ACCEL16_REG_SOFT_RESET, 0x52 );
    Delay_10ms( );  
    
    if ( ACCEL16_APPLICATION_FIFO == ctx->application_type )
    {
        error_flag |= accel16_single_reg_write( ctx, ACCEL16_REG_ACT_INACT_CTL, 0x35 );
        error_flag |= accel16_single_reg_write( ctx, ACCEL16_REG_FIFO_CONTROL, 0x00 );
        error_flag |= accel16_single_reg_write( ctx, ACCEL16_REG_FIFO_CONTROL, 0xFF );
        error_flag |= accel16_single_reg_write( ctx, ACCEL16_REG_FIFO_SAMPLES, 0xDF );
        error_flag |= accel16_single_reg_write( ctx, ACCEL16_REG_INTMAP1, 0x82 );
    }
    else if ( ACCEL16_APPLICATION_REG == ctx->application_type )
    {
        error_flag |= accel16_single_reg_write( ctx, ACCEL16_REG_INTMAP1, 0x81 );
    }

    error_flag |= accel16_filter_configuration( ctx, ACCEL16_2G, ACCEL16_100HZ );
    error_flag |= accel16_single_reg_write( ctx, ACCEL16_REG_POWER_CTL, 0x8A );
    
    return error_flag;
}

err_t accel16_multiple_reg_write ( accel16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 0x30 ] = { 0 };

    tx_buf[ 0 ] = ACCEL16_CMD_WRITE_REG;
    tx_buf[ 1 ] = reg;
    for ( uint8_t cnt = 2; cnt < len + 2; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 2 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t accel16_single_reg_write ( accel16_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_buf[ 3 ] = { 0 };

    tx_buf[ 0 ] = ACCEL16_CMD_WRITE_REG;
    tx_buf[ 1 ] = reg;
    tx_buf[ 2 ] = data_in;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t accel16_multiple_reg_read ( accel16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t tx_data[ 2 ] = { ACCEL16_CMD_READ_REG, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_data, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t accel16_single_reg_read ( accel16_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t tx_data[ 2 ] = { ACCEL16_CMD_READ_REG, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_data, 2, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t accel16_fifo_read ( accel16_t *ctx, uint8_t *data_out, uint16_t len )
{
    uint8_t tx_data = ACCEL16_CMD_READ_FIFO;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &tx_data, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

uint8_t accel16_get_interrupt_1 ( accel16_t *ctx )
{
    return digital_in_read( &ctx->int1 );
}

uint8_t accel16_get_interrupt_2 ( accel16_t *ctx )
{
    return digital_in_read( &ctx->int2 );
}

err_t accel16_filter_configuration ( accel16_t *ctx, accel16_gain_t gain, accel16_output_rate_t odr )
{
    uint8_t default_setting = 0x10;
    default_setting |= ( gain - 1 ) << 6;
    default_setting |= odr;
    
    ctx->resolution = DEFAULT_RES / ( float )gain;
    
    return accel16_single_reg_write( ctx, ACCEL16_REG_FILTER_CTL, default_setting );
}

err_t accel16_get_axes ( accel16_t *ctx, accel16_axes_t *axes )
{
    uint8_t temp_buf[ 6 ] = { 0 };
    int16_t temp_data = 0;
    err_t ret_val = accel16_multiple_reg_read( ctx, ACCEL16_REG_XDATA_L, &temp_buf[ 0 ], 6 );
    
    temp_data = ( ( int16_t )temp_buf[ 1 ] << 8 ) | temp_buf[ 0 ];
    axes->x = temp_data / ctx->resolution;
    
    temp_data = ( ( int16_t )temp_buf[ 3 ] << 8 ) | temp_buf[ 2 ];
    axes->y = temp_data / ctx->resolution;
    
    temp_data = ( ( int16_t )temp_buf[ 5 ] << 8 ) | temp_buf[ 4 ];
    axes->z = temp_data / ctx->resolution;
    
    return ret_val;
}

err_t accel16_get_temperature ( accel16_t *ctx, float *temperature )
{
    uint8_t temp_buf[ 2 ] = { 0 };
    int16_t temp_data = 0;
    err_t ret_val = accel16_multiple_reg_read( ctx, ACCEL16_REG_TEMP_L, &temp_buf[ 0 ], 2 );

    temp_data = ( ( int16_t )temp_buf[ 1 ] << 8 ) | temp_buf[ 0 ];
    *temperature = ( float )temp_data * TEMPERATURE_RES;
    
    return ret_val;
}

err_t accel16_get_adc ( accel16_t *ctx, float *v_adc )
{
    uint8_t temp_buf[ 2 ] = { 0 };
    int16_t temp_data = 0;
    err_t ret_val = accel16_multiple_reg_read( ctx, ACCEL16_REG_ADC_DATA_L, &temp_buf[ 0 ], 2 );

    temp_data = ( ( int16_t )temp_buf[ 1 ] << 8 ) | temp_buf[ 0 ];
    temp_data += ADC_OFFSET;
    *v_adc = ADC_10PCT + ( float )temp_data / ADC_RESOLUTION * ADC_VREF;
    
    return ret_val;
}

// ------------------------------------------------------------------------- END
