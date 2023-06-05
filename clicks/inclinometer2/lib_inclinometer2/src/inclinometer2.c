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
 * @file inclinometer2.c
 * @brief Inclinometer 2 Click Driver.
 */

#include "inclinometer2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Inclinometer 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t inclinometer2_i2c_write ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Inclinometer 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t inclinometer2_i2c_read ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Inclinometer 2 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t inclinometer2_spi_write ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Inclinometer 2 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t inclinometer2_spi_read ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void inclinometer2_cfg_setup ( inclinometer2_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = INCLINOMETER2_DEVICE_ADDRESS_1;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = INCLINOMETER2_DRV_SEL_I2C;
}

void inclinometer2_drv_interface_selection ( inclinometer2_cfg_t *cfg, inclinometer2_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t inclinometer2_init ( inclinometer2_t *ctx, inclinometer2_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    if ( INCLINOMETER2_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        digital_out_t cs;
        digital_out_init ( &cs, cfg->cs );
        digital_out_high ( &cs );
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
        ctx->read_f  = inclinometer2_i2c_read;
        ctx->write_f = inclinometer2_i2c_write;
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
        ctx->read_f  = inclinometer2_spi_read;
        ctx->write_f = inclinometer2_spi_write;
    }
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    return INCLINOMETER2_OK;
}

err_t inclinometer2_default_cfg ( inclinometer2_t *ctx ) 
{
    err_t error_flag = INCLINOMETER2_OK;
    
    if ( INCLINOMETER2_ERROR == inclinometer2_check_communication ( ctx ) )
    {
        return INCLINOMETER2_ERROR;
    }
    
    error_flag |= inclinometer2_write_register ( ctx, INCLINOMETER2_REG_INT1_CTRL, INCLINOMETER2_INT1_CTRL_DRDY_XL );
    
    error_flag |= inclinometer2_set_fsr_and_odr ( ctx, INCLINOMETER2_FSR_2G, INCLINOMETER2_ODR_12p5HZ );
    
    return error_flag;
}

err_t inclinometer2_generic_write ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t inclinometer2_generic_read ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t inclinometer2_write_register ( inclinometer2_t *ctx, uint8_t reg, uint8_t data_in )
{
    return inclinometer2_generic_write( ctx, reg, &data_in, 1 );
}

err_t inclinometer2_read_register ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return inclinometer2_generic_read( ctx, reg, data_out, 1 );
}

err_t inclinometer2_check_communication ( inclinometer2_t *ctx )
{
    uint8_t who_am_i = 0;
    if ( INCLINOMETER2_OK == inclinometer2_read_register ( ctx, INCLINOMETER2_REG_WHO_AM_I, &who_am_i ) )
    {
        if ( INCLINOMETER2_WHO_AM_I == who_am_i )
        {
            return INCLINOMETER2_OK;
        }
    }
    return INCLINOMETER2_ERROR;
}

uint8_t inclinometer2_get_int_pin ( inclinometer2_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t inclinometer2_set_fsr_and_odr ( inclinometer2_t *ctx, inclinometer2_fsr_t fsr, inclinometer2_odr_t odr )
{
    if ( INCLINOMETER2_FSR_0p5G == fsr )
    {
        ctx->resolution = INCLINOMETER2_ACCEL_FSR_0p5G_RES;
    }
    else if ( INCLINOMETER2_FSR_1G == fsr )
    {
        ctx->resolution = INCLINOMETER2_ACCEL_FSR_1G_RES;
    }
    else if ( INCLINOMETER2_FSR_2G == fsr )
    {
        ctx->resolution = INCLINOMETER2_ACCEL_FSR_2G_RES;
    }
    else
    {
        ctx->resolution = INCLINOMETER2_ACCEL_FSR_3G_RES;
    }
    uint8_t reg_data = 0;
    err_t error_flag = inclinometer2_read_register ( ctx, INCLINOMETER2_REG_CTRL1_XL, &reg_data );
    reg_data &= ~INCLINOMETER2_FSR_BIT_MASK;
    reg_data |= ( fsr << 2 );
    reg_data &= ~INCLINOMETER2_ODR_BIT_MASK;
    reg_data |= ( odr << 4 );
    error_flag |= inclinometer2_write_register ( ctx, INCLINOMETER2_REG_CTRL1_XL, reg_data );
    return error_flag;
}

err_t inclinometer2_get_accel ( inclinometer2_t *ctx, float *x_axis, float *y_axis )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( ( INCLINOMETER2_OK == inclinometer2_read_register ( ctx, INCLINOMETER2_REG_STATUS, data_buf ) ) && 
         ( data_buf[ 0 ] & INCLINOMETER2_STATUS_ACCEL_DRDY ) )
    {
        if ( INCLINOMETER2_OK == inclinometer2_generic_read ( ctx, INCLINOMETER2_REG_OUTX_L_A, data_buf, 4 ) )
        {
            *x_axis = ( ( int16_t ) ( ( ( int16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ] ) ) * ctx->resolution;
            *y_axis = ( ( int16_t ) ( ( ( int16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ] ) ) * ctx->resolution;
            return INCLINOMETER2_OK;
        }
    }
    return INCLINOMETER2_ERROR;
}

err_t inclinometer2_get_temperature ( inclinometer2_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( INCLINOMETER2_OK == inclinometer2_read_register ( ctx, INCLINOMETER2_REG_STATUS, data_buf ) ) && 
         ( data_buf[ 0 ] & INCLINOMETER2_STATUS_TEMP_DRDY ) )
    {
        if ( INCLINOMETER2_OK == inclinometer2_generic_read ( ctx, INCLINOMETER2_REG_OUT_TEMP_L, data_buf, 2 ) )
        {
            *temperature = INCLINOMETER2_ROOM_TEMP + 
                           ( ( int16_t ) ( ( ( int16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ] ) ) / INCLINOMETER2_TEMP_SENS;
            return INCLINOMETER2_OK;
        }
    }
    return INCLINOMETER2_ERROR;
}

static err_t inclinometer2_i2c_write ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        tx_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t inclinometer2_i2c_read ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t inclinometer2_spi_write ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    reg &= ( ~SPI_READ_MASK );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t inclinometer2_spi_read ( inclinometer2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    reg |= SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
