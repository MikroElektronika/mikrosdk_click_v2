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
 * @file accel35.c
 * @brief Accel 35 Click Driver.
 */

#include "accel35.h"

/**
 * @brief Dummy and SPI/I2C subcommand setting data.
 * @details Definition of dummy and SPI/I2C subcommand setting data.
 */
#define DUMMY                       0x00
#define SPI_RW_BIT                  0x80
#define SPI_AUTO_INCREMENT_REG_BIT  0x40
#define I2C_AUTO_INCREMENT_REG_BIT  0x80

/**
 * @brief Accel 35 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel35_i2c_write ( accel35_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 35 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel35_i2c_read ( accel35_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 35 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel35_spi_write ( accel35_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 35 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel35_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel35_spi_read ( accel35_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel35_cfg_setup ( accel35_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->it2  = HAL_PIN_NC;
    cfg->it1  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL35_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL35_DRV_SEL_I2C;
}

void accel35_drv_interface_sel ( accel35_cfg_t *cfg, accel35_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel35_init ( accel35_t *ctx, accel35_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL35_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel35_i2c_read;
        ctx->write_f = accel35_i2c_write;
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

        ctx->read_f  = accel35_spi_read;
        ctx->write_f = accel35_spi_write;
    }

    digital_in_init( &ctx->it2, cfg->it2 );
    digital_in_init( &ctx->it1, cfg->it1 );

    return ACCEL35_OK;
}

err_t accel35_default_cfg ( accel35_t *ctx ) 
{
    err_t error_flag = ACCEL35_OK;
    Delay_100ms ( );
    if ( ACCEL35_ERROR == accel35_check_communication ( ctx ) )
    {
        return ACCEL35_ERROR;
    }

    error_flag |= accel35_write_reg ( ctx, ACCEL35_REG_CTRL1, ACCEL35_CTRL1_ODR_POWER_DOWN | 
                                                              ACCEL35_CTRL1_LPEN | 
                                                              ACCEL35_CTRL1_ZEN | 
                                                              ACCEL35_CTRL1_YEN | 
                                                              ACCEL35_CTRL1_XEN );

    error_flag |= accel35_write_reg ( ctx, ACCEL35_REG_CTRL4, ACCEL35_CTRL4_BDU | 
                                                              ACCEL35_CTRL4_FS_2G | 
                                                              ACCEL35_CTRL4_ST_NORMAL | 
                                                              ACCEL35_CTRL4_SIM_4_WIRE );
    error_flag |= accel35_enable_temp_sensor ( ctx );

    error_flag |= accel35_set_odr( ctx, ACCEL35_ODR_10_HZ );

    error_flag |= accel35_set_fsr( ctx, ACCEL35_FS_2G );

    return error_flag;
}

err_t accel35_write_reg ( accel35_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t accel35_write_regs ( accel35_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel35_read_reg ( accel35_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t accel35_read_regs ( accel35_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t accel35_get_it1_pin ( accel35_t *ctx )
{
    return digital_in_read ( &ctx->it1 );
}

uint8_t accel35_get_it2_pin ( accel35_t *ctx )
{
    return digital_in_read ( &ctx->it2 );
}

err_t accel35_check_communication ( accel35_t *ctx )
{
    uint8_t num_tries = 10;
    uint8_t who_am_i = 0;
    while ( num_tries-- )
    {
        if ( ACCEL35_OK == accel35_read_reg ( ctx, ACCEL35_REG_WHO_AM_I, &who_am_i ) )
        {
            if ( ACCEL35_WHO_AM_I == who_am_i )
            {
                return ACCEL35_OK;
            }
        }
        Delay_10ms ( );
    }
    return ACCEL35_ERROR;
}

err_t accel35_set_odr ( accel35_t *ctx, uint8_t odr ) 
{
    err_t error_flag = ACCEL35_OK;
    uint8_t ctrl1 = DUMMY;
    if ( odr > ACCEL35_ODR_5376_HZ )
    {
        error_flag = ACCEL35_ERROR;
    }

    if ( ACCEL35_OK == error_flag )
    {
        error_flag = accel35_read_reg ( ctx, ACCEL35_REG_CTRL1, &ctrl1 );
        ctrl1 &= ~ACCEL35_CTRL1_ODR_MASK;
        ctrl1 |= ( ( odr << 4 ) & ACCEL35_CTRL1_ODR_MASK );
        error_flag |= accel35_write_reg ( ctx, ACCEL35_REG_CTRL1, ctrl1 );
    }
    return error_flag;
}

err_t accel35_set_fsr ( accel35_t *ctx, uint8_t fsr ) 
{
    err_t error_flag = ACCEL35_OK;
    uint8_t ctrl4 = DUMMY;
    if ( fsr > ACCEL35_FS_16G )
    {
        error_flag = ACCEL35_ERROR;
    }
    
    if ( ACCEL35_OK == error_flag )
    {
        error_flag = accel35_read_reg ( ctx, ACCEL35_REG_CTRL4, &ctrl4 );
        ctrl4 &= ~ACCEL35_CTRL4_FS_MASK;
        ctrl4 |= ( fsr & ACCEL35_CTRL4_FS_MASK );
        error_flag |= accel35_write_reg ( ctx, ACCEL35_REG_CTRL4, ctrl4 );
    }

    if ( ACCEL35_OK == error_flag )
    {
        ctx->accel_sens = ACCEL35_ACCEL_SENS_G_PER_LSB * ( 1 << fsr );
    }
    return error_flag;
}

err_t accel35_enable_temp_sensor ( accel35_t *ctx ) 
{
    return accel35_write_reg ( ctx, ACCEL35_REG_TEMP_CFG, ACCEL35_TEMP_CFG_TEMP_ENABLE );
}

err_t accel35_disable_temp_sensor ( accel35_t *ctx ) 
{
    return accel35_write_reg ( ctx, ACCEL35_REG_TEMP_CFG, ACCEL35_TEMP_CFG_TEMP_DISABLE );
}

err_t accel35_check_accel_drdy ( accel35_t *ctx )
{
    err_t error_flag = ACCEL35_OK;
    uint8_t status = 0;
    error_flag = accel35_read_reg ( ctx, ACCEL35_REG_STATUS, &status );
    if ( ACCEL35_OK == error_flag )
    {
        if ( ACCEL35_STATUS_ZYXDA != ( status & ACCEL35_STATUS_ZYXDA ) )
        {
            error_flag = ACCEL35_NO_DRDY;
        }
    }
    return error_flag;
}

err_t accel35_get_accel ( accel35_t *ctx, accel35_axes_t *accel )
{
    err_t error_flag = ACCEL35_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = DUMMY;
    
    if ( NULL == accel )
    {
        error_flag = ACCEL35_ERROR;
    }

    if ( ACCEL35_OK == error_flag )
    {
        error_flag = accel35_check_accel_drdy ( ctx );
    }

    if ( ACCEL35_OK == error_flag )
    {
        error_flag = accel35_read_regs ( ctx, ACCEL35_REG_OUT_X_L, data_buf, 6 );
    }

    if ( ACCEL35_OK == error_flag )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        raw_data >>= 8;
        accel->x = ( float ) raw_data * ctx->accel_sens;
        raw_data = data_buf[ 3 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 2 ];
        raw_data >>= 8;
        accel->y = ( float ) raw_data * ctx->accel_sens;
        raw_data = data_buf[ 5 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 4 ];
        raw_data >>= 8;
        accel->z = ( float ) raw_data * ctx->accel_sens;
    }
    return error_flag;
}

err_t accel35_check_temp_drdy ( accel35_t *ctx )
{
    err_t error_flag = ACCEL35_OK;
    uint8_t status = 0;
    error_flag = accel35_read_reg ( ctx, ACCEL35_REG_STATUS_AUX, &status );
    if ( ACCEL35_OK == error_flag )
    {
        if ( ACCEL35_STATUS_AUX_TDA != ( status & ACCEL35_STATUS_AUX_TDA ) )
        {
            error_flag = ACCEL35_NO_DRDY;
        }
    }
    return error_flag;
}

err_t accel35_get_temp ( accel35_t *ctx, float *temp )
{
    err_t error_flag = ACCEL35_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = ACCEL35_ERROR;
    }

    if ( ACCEL35_OK == error_flag )
    {
        error_flag = accel35_check_temp_drdy ( ctx );
    }

    if ( ACCEL35_OK == error_flag )
    {
        error_flag = accel35_read_regs ( ctx, ACCEL35_REG_OUT_TEMP_L, data_buf, 2 );
    }

    if ( ACCEL35_OK == error_flag )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        raw_data >>= 8;
        *temp = ( float ) raw_data * ACCEL35_TEMP_SENS_C_PER_LSB + ACCEL35_TEMP_OFFSET;
    }
    return error_flag;
}

err_t accel35_get_data ( accel35_t *ctx, accel35_data_t *data_out )
{
    err_t error_flag = ACCEL35_OK;
    if ( NULL == data_out )
    {
        error_flag = ACCEL35_ERROR;
    }
    if ( ACCEL35_OK == error_flag )
    {
        error_flag = accel35_get_accel ( ctx, &data_out->accel );
    }
    if ( ACCEL35_OK == error_flag )
    {
        error_flag = accel35_get_temp ( ctx, &data_out->temperature );
    }
    return error_flag;
}

static err_t accel35_i2c_write ( accel35_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    if ( len > 1 )
    {
        data_buf[ 0 ] = reg | I2C_AUTO_INCREMENT_REG_BIT;
    }
    else
    {
        data_buf[ 0 ] = reg;
    }
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel35_i2c_read ( accel35_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t subcmd = 0;
    if ( len > 1 )
    {
        subcmd = reg | I2C_AUTO_INCREMENT_REG_BIT;
    }
    else
    {
        subcmd = reg;
    }
    return i2c_master_write_then_read( &ctx->i2c, &subcmd, 1, data_out, len );
}

static err_t accel35_spi_write ( accel35_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t subcmd = 0;
    if ( len > 1 )
    {
        subcmd = reg | SPI_AUTO_INCREMENT_REG_BIT;
    }
    else
    {
        subcmd = reg;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &subcmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel35_spi_read ( accel35_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t subcmd = 0;
    if ( len > 1 )
    {
        subcmd = reg | SPI_RW_BIT | SPI_AUTO_INCREMENT_REG_BIT;
    }
    else
    {
        subcmd = reg | SPI_RW_BIT;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &subcmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
