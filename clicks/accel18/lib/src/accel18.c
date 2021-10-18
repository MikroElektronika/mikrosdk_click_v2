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
 * @file accel18.c
 * @brief Accel 18 Click Driver.
 */

#include "accel18.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                       0x00
#define SPI_READ_MASK               0x80

/**
 * @brief Data resolution.
 * @details Definition of data resolution macros for calculating axis value.
 */
#define ACCEL18_RESOLUTION_2G       16384.0
#define ACCEL18_RESOLUTION_4G       8192.0
#define ACCEL18_RESOLUTION_8G       4096.0
#define ACCEL18_RESOLUTION_16G      2048.0
#define ACCEL18_RESOLUTION_12G      2730.0

/**
 * @brief Accel 18 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel18_i2c_write ( accel18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 18 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel18_i2c_read ( accel18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 18 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel18_spi_write ( accel18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 18 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel18_spi_read ( accel18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel18_cfg_setup ( accel18_cfg_t *cfg )
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->i1   = HAL_PIN_NC;
    cfg->i2   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL18_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL18_DRV_SEL_I2C;
}

void accel18_drv_interface_selection ( accel18_cfg_t *cfg, accel18_drv_t drv_sel )
{
    cfg->drv_sel = drv_sel;
}

err_t accel18_init ( accel18_t *ctx, accel18_cfg_t *cfg )
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL18_DRV_SEL_I2C == ctx->drv_sel )
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

        if ( I2C_MASTER_ERROR == i2c_master_set_timeout( &ctx->i2c, 0 ) )
        {
            return I2C_MASTER_ERROR;
        }

        digital_out_t cs;
        digital_out_init( &cs, cfg->cs );
        digital_out_high( &cs );

        ctx->read_f  = accel18_i2c_read;
        ctx->write_f = accel18_i2c_write;
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

        ctx->read_f  = accel18_spi_read;
        ctx->write_f = accel18_spi_write;
    }

    digital_in_init( &ctx->i1, cfg->i1 );
    digital_in_init( &ctx->i2, cfg->i2 );

    return 0;
}

err_t accel18_default_cfg ( accel18_t *ctx )
{
    uint8_t temp_data;
    err_t ret_val = ACCEL18_OK;

    //Standby
    ret_val |= accel18_byte_write( ctx, ACCEL18_REG_MODE, ACCEL18_STATE_STANDBY );
    //Reset
    ret_val |= accel18_byte_read( ctx, ACCEL18_REG_MOTION_CONTROL, &temp_data );
    temp_data |= ACCEL18_MOTION_RESET;
    ret_val |= accel18_byte_write( ctx, ACCEL18_REG_MOTION_CONTROL, temp_data );
    Delay_100ms( );
    temp_data &= ~ACCEL18_MOTION_RESET;
    ret_val |= accel18_byte_write( ctx, ACCEL18_REG_MOTION_CONTROL, temp_data );
    Delay_100ms( );
    //Configuration
    ret_val |= accel18_byte_write( ctx, ACCEL18_REG_INTERRUPT_ENABLE, ACCEL18_INT_FLIP_EN |
                                        ACCEL18_INT_SHAKE_EN | ACCEL18_INT_TILT_EN |
                                        ACCEL18_INT_AUTO_CLR_EN | ACCEL18_INT_ACQ_EN );
    ret_val |= accel18_byte_write( ctx, ACCEL18_REG_RANGE_SELECTION, ACCEL18_RATE_25 );
    ret_val |= accel18_byte_write( ctx, ACCEL18_REG_MOTION_CONTROL, ACCEL18_MOTION_SHAKE_EN |
                                        ACCEL18_MOTION_TF_EN );
    ret_val |= accel18_set_range( ctx, ACCEL18_RANGE_8G );
    ret_val |= accel18_byte_write(ctx, ACCEL18_REG_GPIO_CONTROL, 0 );
    //Wakeup
    ret_val |= accel18_byte_write( ctx, ACCEL18_REG_MODE, ACCEL18_STATE_WAKE );

    return ret_val;
}

err_t accel18_generic_write ( accel18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel18_byte_write ( accel18_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t accel18_generic_read ( accel18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel18_byte_read ( accel18_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t accel18_read_axes ( accel18_t *ctx, accel18_axes_t *axes_data )
{
    int16_t axis_data;
    uint8_t temp_data[ 6 ] = { 0 };

    err_t ret_val = accel18_generic_read( ctx, ACCEL18_REG_XOUT_ACCEL_DATA_LSB, temp_data, 6 );
    axis_data = temp_data[ 0 ] | ( ( int16_t )temp_data[ 1 ] << 8 );
    axes_data->x = axis_data / ctx->range_resolution;
    axis_data = temp_data[ 2 ] | ( ( int16_t )temp_data[ 3 ] << 8 );
    axes_data->y = axis_data / ctx->range_resolution;
    axis_data = temp_data[ 4 ] | ( ( int16_t )temp_data[ 5 ] << 8 );
    axes_data->z = axis_data / ctx->range_resolution;
    return ret_val;
}

err_t accel18_set_range ( accel18_t *ctx, uint8_t range_macro )
{
    uint8_t reg_val = 0;
    err_t ret_val = accel18_byte_read( ctx, ACCEL18_REG_RANGE_SELECTION, &reg_val );
    if ( ( !ret_val ) && ( ( range_macro != ACCEL18_RANGE_2G ) &&
        ( range_macro != ACCEL18_RANGE_4G ) && ( range_macro != ACCEL18_RANGE_8G ) &&
        ( range_macro != ACCEL18_RANGE_16G ) && ( range_macro != ACCEL18_RANGE_12G ) ) )
    {
        ret_val = ACCEL18_ERROR;
    }
    else
    {
        reg_val &= 0x0F;
        reg_val |= range_macro;
        ret_val |= accel18_byte_write( ctx, ACCEL18_REG_RANGE_SELECTION, reg_val );
        switch ( range_macro )
        {
            case ACCEL18_RANGE_2G:
            {
                ctx->range_resolution = ACCEL18_RESOLUTION_2G;
                break;
            }
            case ACCEL18_RANGE_4G:
            {
                ctx->range_resolution = ACCEL18_RESOLUTION_4G;
                break;
            }
            case ACCEL18_RANGE_8G:
            {
                ctx->range_resolution = ACCEL18_RESOLUTION_8G;
                break;
            }
            case ACCEL18_RANGE_16G:
            {
                ctx->range_resolution = ACCEL18_RESOLUTION_16G;
                break;
            }
            case ACCEL18_RANGE_12G:
            {
                ctx->range_resolution = ACCEL18_RESOLUTION_12G;
                break;
            }
            default:
            {
                ret_val = ACCEL18_ERROR;
                break;
            }
        }
    }

    return ret_val;
}

uint8_t accel18_get_interrupt_1 ( accel18_t *ctx )
{
    return digital_in_read( &ctx->i1 );
}

uint8_t accel18_get_interrupt_2 ( accel18_t *ctx )
{
    return digital_in_read( &ctx->i2 );
}



static err_t accel18_i2c_write ( accel18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t accel18_i2c_read ( accel18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel18_spi_write ( accel18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t accel18_spi_read ( accel18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t reg_adr[ 2 ] = { reg | SPI_READ_MASK, 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, reg_adr, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

// ------------------------------------------------------------------------ END
