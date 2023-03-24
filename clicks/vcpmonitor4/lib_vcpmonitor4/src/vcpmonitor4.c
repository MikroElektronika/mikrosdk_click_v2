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
 * @file vcpmonitor4.c
 * @brief VCP Monitor 4 Click Driver.
 */

#include "vcpmonitor4.h"

/**
 * @brief Spi communication macros.
 * @details Definition of macros for SPI communication.
 */
#define DUMMY       0x00
#define READ_BIT    0x1

/**
 * @brief Resolutions and calculation macros.
 * @details Definition of macros for calculation and resolutions.
 */
#define TEMPERATURE_RESOLUTION 125.0
#define VBUS_RESOLUTION 3.125
#define VSHUNT_RESOLUTION 5.0
#define POWER_RESOLUTION 0.2
#define MILITOBASE 1000.0

void vcpmonitor4_cfg_setup ( vcpmonitor4_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t vcpmonitor4_init ( vcpmonitor4_t *ctx, vcpmonitor4_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
    digital_in_init( &ctx->alr, cfg->alr );

    return SPI_MASTER_SUCCESS;
}

err_t vcpmonitor4_default_cfg ( vcpmonitor4_t *ctx ) 
{
    uint32_t temp_data = 0;
    err_t error_flag = vcpmonitor4_generic_write( ctx, VCPMONITOR4_REG_DIAG_ALERT, 0x4003 );
    error_flag |= vcpmonitor4_generic_read( ctx, VCPMONITOR4_REG_ADC_CONFIG, &temp_data );
    temp_data &= 0x0FFF;
    temp_data |= 0xF000;
    error_flag |= vcpmonitor4_generic_write( ctx, VCPMONITOR4_REG_ADC_CONFIG, temp_data );
    error_flag |= vcpmonitor4_generic_write( ctx, VCPMONITOR4_REG_SHUNT_CAL, 6250 );
    return vcpmonitor4_OK;
}

err_t vcpmonitor4_generic_write ( vcpmonitor4_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t tx_buf[ 3 ] = { 0 };

    tx_buf[ 0 ] = reg << 2;
    tx_buf[ 1 ] = data_in >> 8;
    tx_buf[ 2 ] = data_in;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t vcpmonitor4_generic_read ( vcpmonitor4_t *ctx, uint8_t reg, uint32_t *data_out ) 
{
    uint8_t read_buf[ 3 ] = { 0 };
    uint32_t read_value = 0;
    uint8_t reg_adr = reg << 2;
    reg_adr |= READ_BIT;
    uint8_t read_len = 2;
    
    if ( VCPMONITOR4_REG_POWER == reg )
    {
        read_len++;
    }
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, read_buf, read_len );
    spi_master_deselect_device( ctx->chip_select );
    
    for ( uint8_t cnt = 0; cnt < read_len; cnt++ )
    {
        read_value <<= 8;
        read_value |= read_buf[ cnt ];
    }
    
    *data_out = read_value;

    return error_flag;
}

uint8_t vcpmonitor4_get_alert ( vcpmonitor4_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

err_t vcpmonitor4_get_temperature ( vcpmonitor4_t *ctx, float *temperature )
{
    uint32_t temp_data = 0;
    err_t ret_val = vcpmonitor4_generic_read( ctx, VCPMONITOR4_REG_DIETEMP, &temp_data );
    temp_data >>= 4;
    *temperature = temp_data * TEMPERATURE_RESOLUTION / MILITOBASE;
    return ret_val;
}

err_t vcpmonitor4_get_vbus ( vcpmonitor4_t *ctx, float *vbus )
{
    uint32_t temp_data = 0;
    err_t ret_val = vcpmonitor4_generic_read( ctx, VCPMONITOR4_REG_VBUS, &temp_data );
    *vbus = temp_data *  VBUS_RESOLUTION / MILITOBASE;
    return ret_val;
}

err_t vcpmonitor4_get_vshunt ( vcpmonitor4_t *ctx, float *vshunt )
{
    uint32_t temp_data = 0;
    err_t ret_val = vcpmonitor4_generic_read( ctx, VCPMONITOR4_REG_VSHUNT, &temp_data );
    *vshunt = temp_data * VSHUNT_RESOLUTION / MILITOBASE;
    return ret_val;
}

err_t vcpmonitor4_get_current ( vcpmonitor4_t *ctx, float *current )
{
    uint32_t temp_data = 0;
    err_t ret_val = vcpmonitor4_generic_read( ctx, VCPMONITOR4_REG_CURRENT, &temp_data );
    *current = temp_data * VCPMONITOR4_CURRENT_LSB;
    return ret_val;
}

err_t vcpmonitor4_get_power ( vcpmonitor4_t *ctx, float *power )
{
    uint32_t temp_data = 0;
    err_t ret_val = vcpmonitor4_generic_read( ctx, VCPMONITOR4_REG_POWER, &temp_data );
    *power = POWER_RESOLUTION * temp_data * VCPMONITOR4_CURRENT_LSB;
    return ret_val;
}

// ------------------------------------------------------------------------- END
