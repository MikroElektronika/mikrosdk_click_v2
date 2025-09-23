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
 * @file accel23.c
 * @brief Accel 23 Click Driver.
 */

#include "accel23.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Accel 23 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel23_i2c_write ( accel23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 23 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel23_i2c_read ( accel23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 23 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel23_spi_write ( accel23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 23 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel23_spi_read ( accel23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel23_cfg_setup ( accel23_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->eck  = HAL_PIN_NC;
    cfg->it2  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL23_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL23_DRV_SEL_I2C;
}

void accel23_drv_interface_sel ( accel23_cfg_t *cfg, accel23_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel23_init ( accel23_t *ctx, accel23_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL23_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel23_i2c_read;
        ctx->write_f = accel23_i2c_write;
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

        ctx->read_f  = accel23_spi_read;
        ctx->write_f = accel23_spi_write;
    }

    digital_out_init( &ctx->eck, cfg->eck );

    digital_in_init( &ctx->it2, cfg->it2 );

    return ACCEL23_OK;
}

err_t accel23_default_cfg ( accel23_t *ctx ) 
{
    err_t error_flag = ACCEL23_OK;
    Delay_100ms ( );
    if ( ACCEL23_DRV_SEL_SPI == ctx->drv_sel )
    {
        error_flag |= accel23_spi_wake_up ( ctx );
        Delay_100ms ( );
    }

    if ( ACCEL23_ERROR == accel23_check_communication ( ctx ) )
    {
        Delay_100ms ( );
        if ( ACCEL23_ERROR == accel23_check_communication ( ctx ) )
        {
            return ACCEL23_ERROR;
        }
    }

    error_flag |= accel23_sw_reset ( ctx );
    Delay_100ms ( );

    if ( ACCEL23_ERROR == accel23_check_communication ( ctx ) )
    {
        Delay_100ms ( );
        if ( ACCEL23_ERROR == accel23_check_communication ( ctx ) )
        {
            return ACCEL23_ERROR;
        }
    }

    error_flag |= accel23_set_odr( ctx, ACCEL23_ODR_12_5_HZ );

    error_flag |= accel23_set_fsr( ctx, ACCEL23_FS_2G );

    return error_flag;
}

err_t accel23_write_reg ( accel23_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t accel23_write_regs ( accel23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel23_read_reg ( accel23_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t accel23_read_regs ( accel23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

void accel23_set_eck_pin ( accel23_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->eck, state );
}

uint8_t accel23_get_it2_pin ( accel23_t *ctx )
{
    return digital_in_read ( &ctx->it2 );
}

err_t accel23_check_communication ( accel23_t *ctx )
{
    uint8_t who_am_i = 0;
    err_t error_flag = accel23_read_reg ( ctx, ACCEL23_REG_WHO_AM_I, &who_am_i );
    if ( ( ACCEL23_OK == error_flag ) && ( ACCEL23_WHO_AM_I != who_am_i ) )
    {
        error_flag = ACCEL23_ERROR;
    }
    return error_flag;
}

err_t accel23_spi_wake_up ( accel23_t *ctx )
{
    return accel23_write_reg ( ctx, ACCEL23_REG_EN_DEVICE_CONFIG, ACCEL23_EN_DEVICE_CONFIG_SOFT_PD );
}

err_t accel23_sw_reset ( accel23_t *ctx )
{
    uint8_t ctrl1 = DUMMY;
    err_t error_flag = accel23_read_reg ( ctx, ACCEL23_REG_CTRL1, &ctrl1 );
    ctrl1 |= ACCEL23_CTRL1_SW_RESET;
    error_flag |= accel23_write_reg ( ctx, ACCEL23_REG_CTRL1, ctrl1 );
    return error_flag;
}

err_t accel23_set_odr ( accel23_t *ctx, uint8_t odr ) 
{
    err_t error_flag = ACCEL23_OK;
    uint8_t ctrl5 = DUMMY;
    if ( ( ( odr > ACCEL23_ODR_800_HZ ) && ( odr < ACCEL23_ODR_ONE_SHOT_INT2 ) ) || 
         ( odr > ACCEL23_ODR_ONE_SHOT_INT2 ) )
    {
        error_flag = ACCEL23_ERROR;
    }

    if ( ACCEL23_OK == error_flag )
    {
        error_flag = accel23_read_reg ( ctx, ACCEL23_REG_CTRL5, &ctrl5 );
        ctrl5 &= ~ACCEL23_CTRL5_ODR_MASK;
        ctrl5 |= ( ( odr << 4 ) & ACCEL23_CTRL5_ODR_MASK );
        error_flag |= accel23_write_reg ( ctx, ACCEL23_REG_CTRL5, ctrl5 );
    }
    return error_flag;
}

err_t accel23_set_fsr ( accel23_t *ctx, uint8_t fsr ) 
{
    err_t error_flag = ACCEL23_OK;
    uint8_t ctrl5 = DUMMY;
    if ( fsr > ACCEL23_FS_16G )
    {
        error_flag = ACCEL23_ERROR;
    }
    
    if ( ACCEL23_OK == error_flag )
    {
        error_flag = accel23_read_reg ( ctx, ACCEL23_REG_CTRL5, &ctrl5 );
        ctrl5 &= ~ACCEL23_CTRL5_FS_MASK;
        ctrl5 |= ( fsr & ACCEL23_CTRL5_FS_MASK );
        error_flag |= accel23_write_reg ( ctx, ACCEL23_REG_CTRL5, ctrl5 );
    }

    if ( ACCEL23_OK == error_flag )
    {
        ctx->accel_sens = ACCEL23_ACCEL_SENS_G_PER_LSB * ( 1 << fsr );
    }
    return error_flag;
}

err_t accel23_check_accel_drdy ( accel23_t *ctx )
{
    err_t error_flag = ACCEL23_OK;
    uint8_t status = 0;
    error_flag = accel23_read_reg ( ctx, ACCEL23_REG_STATUS, &status );
    if ( ACCEL23_OK == error_flag )
    {
        if ( ACCEL23_STATUS_DRDY != ( status & ACCEL23_STATUS_DRDY ) )
        {
            error_flag = ACCEL23_NO_DRDY;
        }
    }
    return error_flag;
}

err_t accel23_get_accel ( accel23_t *ctx, accel23_axes_t *accel )
{
    err_t error_flag = ACCEL23_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = DUMMY;
    
    if ( NULL == accel )
    {
        error_flag = ACCEL23_ERROR;
    }

    if ( ACCEL23_OK == error_flag )
    {
        error_flag = accel23_check_accel_drdy ( ctx );
    }

    if ( ACCEL23_OK == error_flag )
    {
        error_flag = accel23_read_regs ( ctx, ACCEL23_REG_OUT_X_L, data_buf, 6 );
    }

    if ( ACCEL23_OK == error_flag )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        accel->x = ( float ) raw_data * ctx->accel_sens;
        raw_data = data_buf[ 3 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 2 ];
        accel->y = ( float ) raw_data * ctx->accel_sens;
        raw_data = data_buf[ 5 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 4 ];
        accel->z = ( float ) raw_data * ctx->accel_sens;
    }
    return error_flag;
}

err_t accel23_get_temp ( accel23_t *ctx, float *temp )
{
    err_t error_flag = ACCEL23_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = ACCEL23_ERROR;
    }
    if ( ACCEL23_OK == error_flag )
    {
        error_flag = accel23_read_regs ( ctx, ACCEL23_REG_OUT_T_AH_QVAR_L, data_buf, 2 );
    }
    if ( ACCEL23_OK == error_flag )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        raw_data >>= 4;
        *temp = ( float ) raw_data * ACCEL23_TEMP_SENS_C_PER_LSB + ACCEL23_TEMP_OFFSET;
    }
    return error_flag;
}

err_t accel23_get_data ( accel23_t *ctx, accel23_data_t *data_out )
{
    err_t error_flag = ACCEL23_OK;
    if ( NULL == data_out )
    {
        error_flag = ACCEL23_ERROR;
    }
    if ( ACCEL23_OK == error_flag )
    {
        error_flag = accel23_get_accel ( ctx, &data_out->accel );
    }
    if ( ACCEL23_OK == error_flag )
    {
        error_flag = accel23_get_temp ( ctx, &data_out->temperature );
    }
    return error_flag;
}

static err_t accel23_i2c_write ( accel23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel23_i2c_read ( accel23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel23_spi_write ( accel23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel23_spi_read ( accel23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
