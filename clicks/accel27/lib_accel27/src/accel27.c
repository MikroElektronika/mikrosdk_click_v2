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
 * @file accel27.c
 * @brief Accel 27 Click Driver.
 */

#include "accel27.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x01

/**
 * @brief Accel 27 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel27_i2c_write ( accel27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 27 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel27_i2c_read ( accel27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 27 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel27_spi_write ( accel27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 27 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel27_spi_read ( accel27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel27_cfg_setup ( accel27_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int2 = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL27_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL27_DRV_SEL_I2C;
}

void accel27_drv_interface_selection ( accel27_cfg_t *cfg, accel27_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel27_init ( accel27_t *ctx, accel27_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL27_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = accel27_i2c_read;
        ctx->write_f = accel27_i2c_write;
    } 
    else 
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

        ctx->read_f  = accel27_spi_read;
        ctx->write_f = accel27_spi_write;
    }

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return ACCEL27_OK;
}

err_t accel27_default_cfg ( accel27_t *ctx ) 
{
    err_t error_flag = ACCEL27_OK;
    if ( ACCEL27_ERROR == accel27_check_communication ( ctx ) )
    {
        return ACCEL27_ERROR;
    }
    error_flag |= accel27_reset_device ( ctx );
    Delay_100ms ( );
    error_flag |= accel27_write_register ( ctx, ACCEL27_REG_INT1_MAP, ACCEL27_INT_MAP_DATA_RDY );
    error_flag |= accel27_write_register ( ctx, ACCEL27_REG_TIMING, ACCEL27_TIMING_ODR_320HZ );
    error_flag |= accel27_write_register ( ctx, ACCEL27_REG_POWER_CTL, ACCEL27_POWER_CTL_FLT_SETL_4_OF_ODR | 
                                                                       ACCEL27_POWER_CTL_LPF_DISABLE | 
                                                                       ACCEL27_POWER_CTL_HPF_DISABLE | 
                                                                       ACCEL27_POWER_CTL_MODE_MEASUREMENT );
    Delay_100ms ( );
    return error_flag;
}

err_t accel27_generic_write ( accel27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel27_generic_read ( accel27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel27_write_register ( accel27_t *ctx, uint8_t reg, uint8_t data_in )
{
    return accel27_generic_write ( ctx, reg, &data_in, 1 );
}

err_t accel27_read_register ( accel27_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return accel27_generic_read ( ctx, reg, data_out, 1 );
}

err_t accel27_check_communication ( accel27_t *ctx )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( ACCEL27_OK == accel27_generic_read ( ctx, ACCEL27_REG_DEVID_AD, data_buf, 3 ) )
    {
        if ( ( ACCEL27_DEVID_AD == data_buf[ 0 ] ) && 
             ( ACCEL27_DEVID_MST == data_buf[ 1 ] ) && 
             ( ACCEL27_DEVID_PRODUCT == data_buf[ 2 ] ) )
        {
            return ACCEL27_OK;
        }
    }
    return ACCEL27_ERROR;
}

uint8_t accel27_get_int1_pin ( accel27_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

uint8_t accel27_get_int2_pin ( accel27_t *ctx )
{
    return digital_in_read ( &ctx->int2 );
}

err_t accel27_get_axes ( accel27_t *ctx, accel27_axes_t *axes )
{
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    err_t error_flag = accel27_generic_read ( ctx, ACCEL27_REG_XDATA_H, data_buf, 6 );
    if ( ( NULL != axes ) && ( ACCEL27_OK == error_flag ) )
    {
        raw_data = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        axes->x = ( raw_data >> 4 ) / ACCEL27_SCALE_FACTOR_LSB_PER_G;
        raw_data = ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
        axes->y = ( raw_data >> 4 ) / ACCEL27_SCALE_FACTOR_LSB_PER_G;
        raw_data = ( ( int16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
        axes->z = ( raw_data >> 4 ) / ACCEL27_SCALE_FACTOR_LSB_PER_G;
    }
    return error_flag;
}

err_t accel27_reset_device ( accel27_t *ctx )
{
    return accel27_write_register ( ctx, ACCEL27_REG_RESET, ACCEL27_RESET );
}

static err_t accel27_i2c_write ( accel27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel27_i2c_read ( accel27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel27_spi_write ( accel27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t reg_adr = ( reg << 1 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_adr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel27_spi_read ( accel27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = ( reg << 1 ) | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
