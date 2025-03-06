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
 * @file accel32.c
 * @brief Accel 32 Click Driver.
 */

#include "accel32.h"

/**
 * @brief SPI Dummy data and RW bit.
 * @details Definition of SPI Dummy data and RW bit.
 */
#define DUMMY                   0x00
#define ACCEL32_SPI_READ_BIT    0x01

void accel32_cfg_setup ( accel32_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int0 = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t accel32_init ( accel32_t *ctx, accel32_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int0, cfg->int0 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return SPI_MASTER_SUCCESS;
}

err_t accel32_default_cfg ( accel32_t *ctx ) 
{
    err_t error_flag = ACCEL32_OK;
    if ( ACCEL32_ERROR == accel32_check_communication ( ctx ) )
    {
        return ACCEL32_ERROR;
    }
    error_flag |= accel32_reset_device ( ctx );
    Delay_100ms ( );
    error_flag |= accel32_write_reg ( ctx, ACCEL32_REG_DIG_EN, ACCEL32_DIG_EN_MODE_CHANNEL_EN_ALL );
    error_flag |= accel32_set_op_mode ( ctx, ACCEL32_OP_MODE_HP );
    error_flag |= accel32_set_accel_fsr ( ctx, ACCEL32_ACCEL_FSR_15G );
    Delay_100ms ( );
    return error_flag;
}

err_t accel32_write_regs ( accel32_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = ACCEL32_OK;
    uint8_t reg_adr = ( reg << 1 );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &reg_adr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t accel32_read_regs ( accel32_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = ACCEL32_OK;
    uint8_t reg_adr = ( reg << 1 ) | ACCEL32_SPI_READ_BIT;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t accel32_write_reg ( accel32_t *ctx, uint8_t reg, uint8_t data_in )
{
    return accel32_write_regs ( ctx, reg, &data_in, 1 );
}

err_t accel32_read_reg ( accel32_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return accel32_read_regs ( ctx, reg, data_out, 1 );
}

uint8_t accel32_get_int0_pin ( accel32_t *ctx )
{
    return digital_in_read ( &ctx->int0 );
}

uint8_t accel32_get_int1_pin ( accel32_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

err_t accel32_check_communication ( accel32_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ACCEL32_OK == accel32_read_regs ( ctx, ACCEL32_REG_DEVID_AD, data_buf, 2 ) )
    {
        if ( ( ACCEL32_DEVID_AD == data_buf[ 0 ] ) && 
             ( ACCEL32_DEVID_MST == data_buf[ 1 ] ) )
        {
            return ACCEL32_OK;
        }
    }
    return ACCEL32_ERROR;
}

err_t accel32_reset_device ( accel32_t *ctx )
{
    return accel32_write_reg ( ctx, ACCEL32_REG_RESET, ACCEL32_RESET );
}

err_t accel32_set_op_mode ( accel32_t *ctx, uint8_t op_mode )
{
    err_t error_flag = ACCEL32_OK;
    uint8_t reg_data = 0;
    if ( op_mode > ACCEL32_OP_MODE_HP_VLP )
    {
        error_flag = ACCEL32_ERROR;
    }
    if ( ACCEL32_OK == error_flag )
    {
        error_flag = accel32_read_reg ( ctx, ACCEL32_REG_OP_MODE, &reg_data );
    }
    if ( ACCEL32_OK == error_flag )
    {
        reg_data &= ( ~ACCEL32_OP_MODE_MASK );
        reg_data |= ( op_mode & ACCEL32_OP_MODE_MASK );
        error_flag = accel32_write_reg ( ctx, ACCEL32_REG_OP_MODE, reg_data );
    }
    return error_flag;
}

err_t accel32_set_accel_fsr ( accel32_t *ctx, uint8_t fsr )
{
    err_t error_flag = ACCEL32_OK;
    uint8_t reg_data = 0;
    if ( fsr > ACCEL32_ACCEL_FSR_60G )
    {
        error_flag = ACCEL32_ERROR;
    }
    if ( ACCEL32_OK == error_flag )
    {
        error_flag = accel32_read_reg ( ctx, ACCEL32_REG_OP_MODE, &reg_data );
    }
    if ( ACCEL32_OK == error_flag )
    {
        reg_data &= ( ~ACCEL32_OP_MODE_RANGE_MASK );
        reg_data |= ( ( fsr << 6 ) & ACCEL32_OP_MODE_RANGE_MASK );
        ctx->accel_sens = ACCEL32_SCALE_FACTOR_LSB_PER_G / ( 1 << fsr );
        error_flag = accel32_write_reg ( ctx, ACCEL32_REG_OP_MODE, reg_data );
    }
    return error_flag;
}

err_t accel32_get_drdy ( accel32_t *ctx, uint8_t *drdy )
{
    err_t error_flag = ACCEL32_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = ACCEL32_ERROR;
    }
    if ( ACCEL32_OK == error_flag )
    {
        error_flag = accel32_read_reg ( ctx, ACCEL32_REG_STATUS3, &reg_data );
    }
    if ( ACCEL32_OK == error_flag )
    {
        *drdy = ( ACCEL32_STATUS3_DATA_READY & reg_data );
    }
    return error_flag;
}

err_t accel32_get_accel ( accel32_t *ctx, accel32_axes_t *accel )
{
    err_t error_flag = ACCEL32_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == accel )
    {
        error_flag = ACCEL32_ERROR;
    }
    if ( ACCEL32_OK == error_flag )
    {
        error_flag = accel32_get_drdy ( ctx, &drdy );
    }
    if ( ACCEL32_OK == error_flag )
    {
        if ( ACCEL32_STATUS3_DATA_READY != ( ACCEL32_STATUS3_DATA_READY & drdy ) )
        {
            error_flag = ACCEL32_DATA_NOT_READY;
        }
    }
    if ( ACCEL32_OK == error_flag )
    {
        error_flag = accel32_read_regs ( ctx, ACCEL32_REG_XDATA_H, data_buf, 6 );
    }
    if ( ACCEL32_OK == error_flag )
    {
        raw_data = data_buf[ 0 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 1 ];
        accel->x = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 2 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 3 ];
        accel->y = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 4 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 5 ];
        accel->z = ( float ) raw_data / ctx->accel_sens;
    }
    return error_flag;
}

err_t accel32_get_temp ( accel32_t *ctx, float *temp )
{
    err_t error_flag = ACCEL32_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = ACCEL32_ERROR;
    }
    if ( ACCEL32_OK == error_flag )
    {
        error_flag = accel32_get_drdy ( ctx, &drdy );
    }
    if ( ACCEL32_OK == error_flag )
    {
        if ( ACCEL32_STATUS3_DATA_READY != ( ACCEL32_STATUS3_DATA_READY & drdy ) )
        {
            error_flag = ACCEL32_DATA_NOT_READY;
        }
    }
    if ( ACCEL32_OK == error_flag )
    {
        error_flag = accel32_read_regs ( ctx, ACCEL32_REG_TDATA_H, data_buf, 2 );
    }
    if ( ACCEL32_OK == error_flag )
    {
        raw_data = data_buf[ 0 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 1 ];
        raw_data >>= 4;
        *temp = ( float ) raw_data / ACCEL32_TEMP_SENS;
    }
    return error_flag;
}

err_t accel32_get_data ( accel32_t *ctx, accel32_data_t *data_out )
{
    err_t error_flag = ACCEL32_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 8 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == data_out )
    {
        error_flag = ACCEL32_ERROR;
    }
    if ( ACCEL32_OK == error_flag )
    {
        error_flag = accel32_get_drdy ( ctx, &drdy );
    }
    if ( ACCEL32_OK == error_flag )
    {
        if ( ACCEL32_STATUS3_DATA_READY != ( ACCEL32_STATUS3_DATA_READY & drdy ) )
        {
            error_flag = ACCEL32_DATA_NOT_READY;
        }
    }
    if ( ACCEL32_OK == error_flag )
    {
        error_flag = accel32_read_regs ( ctx, ACCEL32_REG_XDATA_H, data_buf, 8 );
    }
    if ( ACCEL32_OK == error_flag )
    {
        raw_data = data_buf[ 0 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 1 ];
        data_out->accel.x = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 2 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 3 ];
        data_out->accel.y = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 4 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 5 ];
        data_out->accel.z = ( float ) raw_data / ctx->accel_sens;
        raw_data = data_buf[ 6 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 7 ];
        raw_data >>= 4;
        data_out->temperature = ( float ) ( raw_data - ACCEL32_TEMP_OFFSET_LSB ) / ACCEL32_TEMP_SENS;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
