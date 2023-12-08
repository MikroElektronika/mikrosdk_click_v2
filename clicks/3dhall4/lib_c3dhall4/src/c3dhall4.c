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
 * @file c3dhall4.c
 * @brief 3D Hall 4 Click Driver.
 */

#include "c3dhall4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void c3dhall4_cfg_setup ( c3dhall4_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->tan  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = C3DHALL4_ADC_VREF_3V3;
}

err_t c3dhall4_init ( c3dhall4_t *ctx, c3dhall4_cfg_t *cfg ) 
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

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->tan;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    return C3DHALL4_OK;
}

err_t c3dhall4_default_cfg ( c3dhall4_t *ctx ) 
{
    err_t error_flag = C3DHALL4_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    
    C3DHALL4_SET_DATA_SAMPLE_EDGE;
    
    error_flag = c3dhall4_reg_read ( ctx, C3DHALL4_REG_G_CTRL_X, data_buf, 3 );
    data_buf[ 0 ] &= C3DHALL4_RANGE_MASK;
    data_buf[ 1 ] &= C3DHALL4_RANGE_MASK;
    data_buf[ 2 ] &= C3DHALL4_RANGE_MASK;
    if ( C3DHALL4_RANGE_20 == data_buf[ 0 ] )
    {
        ctx->x_sens = C3DHALL4_SENS_RANGE_20;
    }
    else if ( C3DHALL4_RANGE_40 == data_buf[ 0 ] )
    {
        ctx->x_sens = C3DHALL4_SENS_RANGE_40;
    }
    else if ( C3DHALL4_RANGE_350 == data_buf[ 0 ] )
    {
        ctx->x_sens = C3DHALL4_SENS_RANGE_350;
    }
    else
    {
        ctx->x_sens = C3DHALL4_SENS_RANGE_3000;
    }
    
    if ( C3DHALL4_RANGE_20 == data_buf[ 1 ] )
    {
        ctx->z_sens = C3DHALL4_SENS_RANGE_20;
    }
    else if ( C3DHALL4_RANGE_40 == data_buf[ 1 ] )
    {
        ctx->z_sens = C3DHALL4_SENS_RANGE_40;
    }
    else if ( C3DHALL4_RANGE_350 == data_buf[ 1 ] )
    {
        ctx->z_sens = C3DHALL4_SENS_RANGE_350;
    }
    else
    {
        ctx->z_sens = C3DHALL4_SENS_RANGE_3000;
    }
    
    if ( C3DHALL4_RANGE_20 == data_buf[ 2 ] )
    {
        ctx->y_sens = C3DHALL4_SENS_RANGE_20;
    }
    else if ( C3DHALL4_RANGE_40 == data_buf[ 2 ] )
    {
        ctx->y_sens = C3DHALL4_SENS_RANGE_40;
    }
    else if ( C3DHALL4_RANGE_350 == data_buf[ 2 ] )
    {
        ctx->y_sens = C3DHALL4_SENS_RANGE_350;
    }
    else
    {
        ctx->y_sens = C3DHALL4_SENS_RANGE_3000;
    }
    
    return error_flag;
}

err_t c3dhall4_reg_write ( c3dhall4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 2 ] = { C3DHALL4_CMD_REG_WRITE, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t c3dhall4_reg_read ( c3dhall4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 3 ] = { C3DHALL4_CMD_REG_READ, reg, DUMMY };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    error_flag |= spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t c3dhall4_eeprom_write ( c3dhall4_t *ctx, uint8_t address, uint8_t data_in )
{
    uint8_t data_buf[ 3 ] = { C3DHALL4_CMD_EREG_WRITE, address, data_in };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    Delay_10ms ( );
    Delay_10ms ( );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( C3DHALL4_CMD_SPECIAL_KEY != data_buf[ 0 ] )
    {
        error_flag = C3DHALL4_ERROR;
    }
    return error_flag;
}

err_t c3dhall4_eeprom_read ( c3dhall4_t *ctx, uint8_t address, uint8_t *data_out )
{
    uint8_t data_buf[ 3 ] = { C3DHALL4_CMD_EREG_READ, address, DUMMY };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( C3DHALL4_CMD_SPECIAL_KEY != data_buf[ 0 ] )
    {
        error_flag = C3DHALL4_ERROR;
    }
    else
    {
        *data_out = data_buf[ 1 ];
    }
    return error_flag;
}

err_t c3dhall4_eeprom_update_cksum ( c3dhall4_t *ctx )
{
    err_t error_flag = C3DHALL4_OK;
    uint8_t checksum = 0;
    uint8_t ereg = C3DHALL4_EREG_0;
    uint8_t ereg_data = 0;
    while ( ereg < C3DHALL4_EREG_CHECKSUM )
    {
        if ( C3DHALL4_ERROR == c3dhall4_eeprom_read ( ctx, ereg, &ereg_data ) )
        {
            return C3DHALL4_ERROR;
        }
        checksum += ereg_data;
        ereg++;
    }
    checksum = 256 - checksum;
    return c3dhall4_eeprom_write ( ctx, C3DHALL4_EREG_CHECKSUM, checksum );
}

err_t c3dhall4_read_an_pin_value ( c3dhall4_t *ctx, uint16_t *data_out )
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t c3dhall4_read_an_pin_voltage ( c3dhall4_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t c3dhall4_read_data ( c3dhall4_t *ctx, c3dhall4_data_t *data_out )
{
    uint8_t data_buf[ 9 ] = { 0 };
    float raw_data = 0;
    err_t error_flag = c3dhall4_reg_read ( ctx, C3DHALL4_REG_STATUS, data_buf, 9 );
    if ( data_out && ( C3DHALL4_OK == error_flag ) )
    {
        data_out->status = data_buf[ 0 ];
        raw_data = ( ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 1 ] );
        raw_data -= C3DHALL4_OFFSET_XYZ;
        data_out->x_data = raw_data / ctx->x_sens;
        raw_data = ( ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ] );
        raw_data -= C3DHALL4_OFFSET_XYZ;
        data_out->z_data = raw_data / ctx->z_sens;
        raw_data = ( ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 5 ] );
        raw_data -= C3DHALL4_OFFSET_XYZ;
        data_out->y_data = raw_data / ctx->y_sens;
        raw_data = ( ( ( uint16_t ) data_buf[ 8 ] << 8 ) | data_buf[ 7 ] );
        raw_data -= C3DHALL4_OFFSET_TEMPERATURE;
        data_out->chip_temp = raw_data / C3DHALL4_SENS_TEMPERATURE;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
