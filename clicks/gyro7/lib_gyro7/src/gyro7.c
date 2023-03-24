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
 * @file gyro7.c
 * @brief Gyro 7 Click Driver.
 */

#include "gyro7.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY   0x00

void gyro7_cfg_setup ( gyro7_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t gyro7_init ( gyro7_t *ctx, gyro7_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t gyro7_default_cfg ( gyro7_t *ctx ) 
{
    err_t error_flag = GYRO7_OK;
    if ( GYRO7_ERROR == gyro7_check_communication ( ctx ) )
    {
        return GYRO7_ERROR;
    }
    error_flag |= gyro7_write_register ( ctx, GYRO7_REG_PWR_MGMT_1, GYRO7_PWR_MGMT_1_DEVICE_RESET );
    Delay_1sec ( );
    error_flag |= gyro7_write_register ( ctx, GYRO7_REG_PWR_MGMT_1, GYRO7_PWR_MGMT_1_INTERNAL_OSC );
    
    error_flag |= gyro7_write_register ( ctx, GYRO7_REG_SMPLRT_DIV, GYRO7_SAMPLE_RATE_40_HZ );
    error_flag |= gyro7_write_register ( ctx, GYRO7_REG_CONFIG, GYRO7_CONFIG_DLPF_CFG_ENABLE_DLPF );
    error_flag |= gyro7_set_dlpf_config ( ctx, GYRO7_DLPF_250_HZ );
    error_flag |= gyro7_write_register ( ctx, GYRO7_REG_GYRO_CONFIG, GYRO7_GYRO_CONFIG_FS_SEL_374_DPS );
    error_flag |= gyro7_write_register ( ctx, GYRO7_REG_INT_PIN_CFG, GYRO7_INT_PIN_CFG_LATCH_INT_EN | 
                                                                     GYRO7_INT_PIN_CFG_INT_RD_CLEAR );
    error_flag |= gyro7_write_register ( ctx, GYRO7_REG_INT_ENABLE, GYRO7_INT_ENABLE_DATA_RDY_EN );
    return error_flag;
}

err_t gyro7_generic_write ( gyro7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    reg &= ( ~GYRO7_SPI_READ_WRITE_BIT );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t gyro7_generic_read ( gyro7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    reg |= GYRO7_SPI_READ_WRITE_BIT;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t gyro7_write_register ( gyro7_t *ctx, uint8_t reg, uint8_t data_in )
{
    return gyro7_generic_write ( ctx, reg, &data_in, 1 );
}

err_t gyro7_read_register ( gyro7_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return gyro7_generic_read ( ctx, reg, data_out, 1 );
}

err_t gyro7_check_communication ( gyro7_t *ctx )
{
    uint8_t who_am_i;
    if ( GYRO7_OK == gyro7_read_register ( ctx, GYRO7_REG_WHO_AM_I, &who_am_i ) )
    {
        if ( GYRO7_WHO_AM_I == who_am_i )
        {
            return GYRO7_OK;
        }
    }
    return GYRO7_ERROR;
}

uint8_t gyro7_get_int_pin ( gyro7_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t gyro7_set_dlpf_config ( gyro7_t *ctx, uint8_t freq )
{
    err_t error_flag = GYRO7_OK;
    switch ( freq )
    {
        case GYRO7_DLPF_40_160_HZ: 
        {
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_40_160_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_40_160_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_40_160_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_40_160_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_40_160_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_40_160_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_40_160_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_40_160_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A1_40_160_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A1_40_160_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A2_40_160_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A2_40_160_HZ & 0xFF ) );
            break;
        }
        case GYRO7_DLPF_80_320_HZ: 
        {
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_80_320_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_80_320_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_80_320_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_80_320_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_80_320_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_80_320_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_80_320_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_80_320_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A1_80_320_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A1_80_320_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A2_80_320_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A2_80_320_HZ & 0xFF ) );
            break;
        }
        case GYRO7_DLPF_160_640_HZ: 
        {
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_160_640_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_160_640_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_160_640_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_160_640_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_160_640_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_160_640_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_160_640_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_160_640_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A1_160_640_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A1_160_640_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A2_160_640_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A2_160_640_HZ & 0xFF ) );
            break;
        }
        case GYRO7_DLPF_250_HZ: 
        {
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_250_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_250_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_250_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_250_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_250_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_250_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_250_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_250_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A1_250_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A1_250_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A2_250_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A2_250_HZ & 0xFF ) );
            break;
        }
        case GYRO7_DLPF_500_HZ: 
        {
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_500_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_500_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_X_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_500_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_X_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_500_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B0B2_500_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B0B2_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B0B2_500_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_H_Y_AXIS, 
                                                 ( uint8_t )( ( GYRO7_DLPF_B1_500_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_B1_L_Y_AXIS, 
                                                 ( uint8_t )( GYRO7_DLPF_B1_500_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A1_500_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A1_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A1_500_HZ & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_H, 
                                                 ( uint8_t )( ( GYRO7_DLPF_A2_500_HZ >> 8 ) & 0xFF ) );
            error_flag |= gyro7_write_register ( ctx, GYRO7_REG_DLPF_A2_L, 
                                                 ( uint8_t )( GYRO7_DLPF_A2_500_HZ & 0xFF ) );
            break;
        }
        default:
        {
            return GYRO7_ERROR;
        }
    }
    return error_flag;
}

err_t gyro7_read_gyroscope ( gyro7_t *ctx, float *x_axis, float *y_axis )
{
    uint8_t data_buf[ 4 ];
    float gyro_sens = 0;
    if ( GYRO7_ERROR == gyro7_read_register ( ctx, GYRO7_REG_GYRO_CONFIG, data_buf ) )
    {
        return GYRO7_ERROR;
    }
    switch ( data_buf[ 0 ] & GYRO7_GYRO_CONFIG_FS_SEL_BITS_MASK )
    { 
        case GYRO7_GYRO_CONFIG_FS_SEL_46p5_DPS :
        {
            gyro_sens = GYRO7_GYRO_SENSITIVITY_FS_SEL_0; 
            break;
        }
        case GYRO7_GYRO_CONFIG_FS_SEL_93_DPS :
        {
            gyro_sens = GYRO7_GYRO_SENSITIVITY_FS_SEL_1; 
            break;
        }
        case GYRO7_GYRO_CONFIG_FS_SEL_187_DPS :
        {
            gyro_sens = GYRO7_GYRO_SENSITIVITY_FS_SEL_2;
            break;
        }
        case GYRO7_GYRO_CONFIG_FS_SEL_374_DPS :
        {
            gyro_sens = GYRO7_GYRO_SENSITIVITY_FS_SEL_3;
            break;
        }
        default :
        {
            return GYRO7_ERROR;
        }
    }
    if ( GYRO7_ERROR == gyro7_generic_read ( ctx, GYRO7_REG_GYRO_XOUT_H, data_buf, 4 ) )
    {
        return GYRO7_ERROR;
    }
    *x_axis = ( float ) ( ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) / gyro_sens;
    *y_axis = ( float ) ( ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ] ) / gyro_sens;
    return GYRO7_OK;
}

err_t gyro7_read_temperature ( gyro7_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( GYRO7_ERROR == gyro7_generic_read ( ctx, GYRO7_REG_TEMP_OUT_H, data_buf, 2 ) )
    {
        return GYRO7_ERROR;
    }
    *temperature = ( float ) ( ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) / GYRO7_TEMP_SENSITIVITY;
    return GYRO7_OK;
}

// ------------------------------------------------------------------------- END
