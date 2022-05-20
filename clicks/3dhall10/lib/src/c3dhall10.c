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
 * @file c3dhall10.c
 * @brief 3D Hall 10 Click Driver.
 */

#include "c3dhall10.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief 3D Hall 10 calculate CRC4 function.
 * @details This function calculates CRC4 from 4 input bytes (28-MSBs only) with 
 * polynomial X4 + X + 1 and CRC initialization at 0x0F.
 * @param[in] crc_source : 4 input bytes (28-MSBs only).
 * @return Calculated CRC4 output.
 * @note None.
 */
static uint8_t c3dhall10_calculate_crc ( uint8_t crc_source[ 4 ] );

void c3dhall10_cfg_setup ( c3dhall10_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->alr  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t c3dhall10_init ( c3dhall10_t *ctx, c3dhall10_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alr, cfg->alr );

    return SPI_MASTER_SUCCESS;
}

err_t c3dhall10_default_cfg ( c3dhall10_t *ctx ) 
{
    err_t error_flag = C3DHALL10_OK;
    error_flag |= c3dhall10_write_frame ( ctx, C3DHALL10_REG_DEVICE_CONFIG, C3DHALL10_CONV_AVG_32X | 
                                                                            C3DHALL10_MAG_TEMPCO_0 | 
                                                                            C3DHALL10_OPERATING_MODE_DUTY_CYCLED | 
                                                                            C3DHALL10_T_CH_EN_ENABLE | 
                                                                            C3DHALL10_T_RATE_PER_CONV_AVG | 
                                                                            C3DHALL10_T_HLT_EN_DISABLE );
    error_flag |= c3dhall10_write_frame ( ctx, C3DHALL10_REG_SENSOR_CONFIG, C3DHALL10_ANGLE_EN_XY_ANGLE | 
                                                                            C3DHALL10_SLEEPTIME_100MS | 
                                                                            C3DHALL10_MAG_CH_EN_ENABLE_XYZ | 
                                                                            C3DHALL10_Z_RANGE_25mT | 
                                                                            C3DHALL10_Y_RANGE_25mT | 
                                                                            C3DHALL10_X_RANGE_25mT );
    error_flag |= c3dhall10_write_frame ( ctx, C3DHALL10_REG_SYSTEM_CONFIG, C3DHALL10_DIAG_SEL_ALL_DP_DIAG_ALL | 
                                                                            C3DHALL10_TRIGGER_MODE_SPI_CMD | 
                                                                            C3DHALL10_DATA_TYPE_32BIT_REG | 
                                                                            C3DHALL10_DIAG_EN_DISABLE |
                                                                            C3DHALL10_Z_HLT_EN_DISABLE |
                                                                            C3DHALL10_Y_HLT_EN_DISABLE |
                                                                            C3DHALL10_X_HLT_EN_DISABLE );
    error_flag |= c3dhall10_write_frame ( ctx, C3DHALL10_REG_ALERT_CONFIG, C3DHALL10_ALERT_LATCH_DISABLE | 
                                                                           C3DHALL10_ALERT_MODE_INTERRUPT | 
                                                                           C3DHALL10_STATUS_ALRT_AFE_SYS_NO_ASSERT | 
                                                                           C3DHALL10_RSLT_ALRT_CONV_COMPLETE | 
                                                                           C3DHALL10_THRX_COUNT_1_CONV | 
                                                                           C3DHALL10_T_THRX_ALRT_NO_CROSSED |
                                                                           C3DHALL10_Z_THRX_ALRT_NO_CROSSED |
                                                                           C3DHALL10_Y_THRX_ALRT_NO_CROSSED |
                                                                           C3DHALL10_X_THRX_ALRT_NO_CROSSED );
    error_flag |= c3dhall10_write_frame ( ctx, C3DHALL10_REG_MAG_GAIN_CONFIG, C3DHALL10_GAIN_SELECTION_NO_AXIS );
    
    return error_flag;
}

err_t c3dhall10_write_frame ( c3dhall10_t *ctx, uint8_t reg_addr, uint16_t data_in ) 
{
    if ( reg_addr > C3DHALL10_REG_MAGNITUDE_RESULT )
    {
        return C3DHALL10_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = reg_addr & C3DHALL10_SPI_WRITE_MASK;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 3 ] = c3dhall10_calculate_crc ( data_buf );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t c3dhall10_read_frame ( c3dhall10_t *ctx, uint8_t reg_addr, uint16_t *data_out, uint16_t *status ) 
{
    if ( reg_addr > C3DHALL10_REG_MAGNITUDE_RESULT )
    {
        return C3DHALL10_ERROR;
    }
    err_t error_flag = C3DHALL10_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = reg_addr | C3DHALL10_SPI_READ_MASK;
    data_buf[ 1 ] = DUMMY;
    data_buf[ 2 ] = DUMMY;
    data_buf[ 3 ] = c3dhall10_calculate_crc ( data_buf );
    spi_master_select_device( ctx->chip_select );
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        spi_master_set_default_write_data( &ctx->spi, data_buf[ cnt ] );
        error_flag |= spi_master_read( &ctx->spi, &data_buf[ cnt ], 1 );
    }
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    uint8_t crc = data_buf[ 3 ] & 0x0F;
    if ( ( C3DHALL10_OK == error_flag ) && ( crc == c3dhall10_calculate_crc ( data_buf ) ) )
    {
        *status = ( ( uint16_t ) data_buf[ 0 ] << 4 ) | ( ( data_buf[ 3 ] >> 4 ) & 0x0F );
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
        return C3DHALL10_OK;
    }
    return C3DHALL10_ERROR;
}

err_t c3dhall10_read_data ( c3dhall10_t *ctx, c3dhall10_data_t *data_out )
{
    uint16_t reg_status, reg_data, conv_status, sensor_config;
    err_t error_flag = c3dhall10_read_frame ( ctx, C3DHALL10_REG_CONV_STATUS, &conv_status, &reg_status );
    if ( ( C3DHALL10_OK == error_flag ) && ( conv_status & C3DHALL10_CONV_STATUS_RDY ) )
    {
        error_flag |= c3dhall10_read_frame ( ctx, C3DHALL10_REG_SENSOR_CONFIG, &sensor_config, &reg_status );
        if ( conv_status & C3DHALL10_CONV_STATUS_A )
        {
            error_flag |= c3dhall10_read_frame ( ctx, C3DHALL10_REG_ANGLE_RESULT, &reg_data, &reg_status );
            data_out->angle = reg_data / C3DHALL10_ANGLE_RESOLUTION;
            error_flag |= c3dhall10_read_frame ( ctx, C3DHALL10_REG_MAGNITUDE_RESULT, &reg_data, &reg_status );
            data_out->magnitude = reg_data;
        }
        if ( conv_status & C3DHALL10_CONV_STATUS_T )
        {
            error_flag |= c3dhall10_read_frame ( ctx, C3DHALL10_REG_TEMP_RESULT, &reg_data, &reg_status );
            data_out->temperature = C3DHALL10_TEMP_SENS_T0 + 
                                    ( ( int16_t ) reg_data - C3DHALL10_TEMP_ADC_T0 ) / C3DHALL10_TEMP_ADC_RESOLUTION;
        }
        if ( conv_status & C3DHALL10_CONV_STATUS_Z )
        {
            error_flag |= c3dhall10_read_frame ( ctx, C3DHALL10_REG_Z_CH_RESULT, &reg_data, &reg_status );
            data_out->z_axis = ( ( int16_t ) reg_data ) / C3DHALL10_XYZ_RESOLUTION;
            switch ( sensor_config & C3DHALL10_Z_RANGE_BIT_MASK )
            {
                case C3DHALL10_Z_RANGE_25mT:
                {
                    data_out->z_axis *= 25.0;
                    break;
                }
                case C3DHALL10_Z_RANGE_50mT:
                {
                    data_out->z_axis *= 50.0;
                    break;
                }
                case C3DHALL10_Z_RANGE_100mT:
                {
                    data_out->z_axis *= 100.0;
                    break;
                }
            }
        }
        if ( conv_status & C3DHALL10_CONV_STATUS_Y )
        {
            error_flag |= c3dhall10_read_frame ( ctx, C3DHALL10_REG_Y_CH_RESULT, &reg_data, &reg_status );
            data_out->y_axis = ( ( int16_t ) reg_data ) / C3DHALL10_XYZ_RESOLUTION;
            switch ( sensor_config & C3DHALL10_Y_RANGE_BIT_MASK )
            {
                case C3DHALL10_Y_RANGE_25mT:
                {
                    data_out->y_axis *= 25.0;
                    break;
                }
                case C3DHALL10_Y_RANGE_50mT:
                {
                    data_out->y_axis *= 50.0;
                    break;
                }
                case C3DHALL10_Y_RANGE_100mT:
                {
                    data_out->y_axis *= 100.0;
                    break;
                }
            }
        }
        if ( conv_status & C3DHALL10_CONV_STATUS_X )
        {
            error_flag |= c3dhall10_read_frame ( ctx, C3DHALL10_REG_X_CH_RESULT, &reg_data, &reg_status );
            data_out->x_axis = ( ( int16_t ) reg_data ) / C3DHALL10_XYZ_RESOLUTION;
            switch ( sensor_config & C3DHALL10_X_RANGE_BIT_MASK )
            {
                case C3DHALL10_X_RANGE_25mT:
                {
                    data_out->x_axis *= 25.0;
                    break;
                }
                case C3DHALL10_X_RANGE_50mT:
                {
                    data_out->x_axis *= 50.0;
                    break;
                }
                case C3DHALL10_X_RANGE_100mT:
                {
                    data_out->x_axis *= 100.0;
                    break;
                }
            }
        }
        return error_flag;
    }
    return C3DHALL10_ERROR;
}

uint8_t c3dhall10_get_alert_pin ( c3dhall10_t *ctx )
{
    return digital_in_read ( &ctx->alr );
}

static uint8_t c3dhall10_calculate_crc ( uint8_t crc_source[ 4 ] )
{
    crc_source[ 3 ] &= 0xF0;
    uint8_t crc = 0x0F;
    for ( uint8_t byte_cnt = 0; byte_cnt < 4; byte_cnt++ )
    {
        for ( uint8_t bit_cnt = 8; bit_cnt > 0; bit_cnt-- )
        {
            uint8_t inv = ( ( crc_source[ byte_cnt ] >> ( bit_cnt - 1 ) ) & 1 ) ^ ( ( crc >> 3 ) & 1 );
            crc = ( ( crc ^ inv ) << 1 ) | inv;
        }
    }
    return crc & 0x0F;
}

// ------------------------------------------------------------------------- END
