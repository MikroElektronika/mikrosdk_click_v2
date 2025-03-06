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
 * @file c6dofimu24.c
 * @brief 6DOF IMU 24 Click Driver.
 */

#include "c6dofimu24.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief 6DOF IMU 24 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu24_i2c_write ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 24 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu24_i2c_read ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 24 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu24_spi_write ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 24 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu24_spi_read ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void c6dofimu24_cfg_setup ( c6dofimu24_cfg_t *cfg ) 
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
    cfg->i2c_address = C6DOFIMU24_DEVICE_ADDRESS_1;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = C6DOFIMU24_DRV_SEL_I2C;
}

void c6dofimu24_drv_interface_sel ( c6dofimu24_cfg_t *cfg, c6dofimu24_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t c6dofimu24_init ( c6dofimu24_t *ctx, c6dofimu24_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( C6DOFIMU24_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = c6dofimu24_i2c_read;
        ctx->write_f = c6dofimu24_i2c_write;
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

        ctx->read_f  = c6dofimu24_spi_read;
        ctx->write_f = c6dofimu24_spi_write;
    }

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return C6DOFIMU24_OK;
}

err_t c6dofimu24_default_cfg ( c6dofimu24_t *ctx ) 
{
    err_t error_flag = C6DOFIMU24_OK;
    uint8_t reg_data = 0;
    
    // Reset device and checks communication
    error_flag |= c6dofimu24_reset_device ( ctx );
    Delay_100ms ( );
    error_flag |= c6dofimu24_check_communication ( ctx );
    if ( C6DOFIMU24_OK != error_flag )
    {
        return C6DOFIMU24_ERROR;
    };

    // Set active low - data ready interrupt routed to INT1 pin
    error_flag |= c6dofimu24_read_reg ( ctx, C6DOFIMU24_REG0_INT_CONFIG, &reg_data );
    reg_data &= ~( C6DOFIMU24_INT_CONFIG_INT1_MODE_MASK | C6DOFIMU24_INT_CONFIG_INT1_DRV_MASK | 
                   C6DOFIMU24_INT_CONFIG_INT1_POL_MASK );
    reg_data |= ( C6DOFIMU24_INT_CONFIG_INT1_MODE_LATCH | C6DOFIMU24_INT_CONFIG_INT1_DRV_OD | 
                  C6DOFIMU24_INT_CONFIG_INT1_POL_LOW );
    error_flag |= c6dofimu24_write_reg ( ctx, C6DOFIMU24_REG0_INT_CONFIG, reg_data );
    error_flag |= c6dofimu24_read_reg ( ctx, C6DOFIMU24_REG0_INT_CONFIG1, &reg_data );
    reg_data &= ~C6DOFIMU24_INT_CONFIG1_ASYNC_RESET_MASK;
    reg_data |= C6DOFIMU24_INT_CONFIG1_ASYNC_RESET_DIS;
    error_flag |= c6dofimu24_write_reg ( ctx, C6DOFIMU24_REG0_INT_CONFIG1, reg_data );
    error_flag |= c6dofimu24_write_reg ( ctx, C6DOFIMU24_REG0_INT_SOURCE0, C6DOFIMU24_INT_SOURCE0_UI_DRDY_INT1_EN );

    // Set full scale range and output data rate for gyro and accel
    error_flag |= c6dofimu24_set_gyro_fs_odr ( ctx, C6DOFIMU24_GYRO_FS_SEL_2000DPS, C6DOFIMU24_GYRO_ODR_12_5HZ );
    error_flag |= c6dofimu24_set_accel_fs_odr ( ctx, C6DOFIMU24_ACCEL_FS_SEL_4G, C6DOFIMU24_ACCEL_ODR_12_5HZ );

    // Enable both gyro and accel in low noise mode
    error_flag |= c6dofimu24_read_reg ( ctx, C6DOFIMU24_REG0_PWR_MGMT0, &reg_data );
    reg_data &= ~( C6DOFIMU24_PWR_MGMT0_GYRO_MODE_MASK | C6DOFIMU24_PWR_MGMT0_ACCEL_MODE_MASK );
    reg_data |= ( C6DOFIMU24_PWR_MGMT0_GYRO_MODE_LN | C6DOFIMU24_PWR_MGMT0_ACCEL_MODE_LN );
    error_flag |= c6dofimu24_write_reg ( ctx, C6DOFIMU24_REG0_PWR_MGMT0, reg_data );
    Delay_100ms ( );

    return error_flag;
}

err_t c6dofimu24_write_regs ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t c6dofimu24_read_regs ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t c6dofimu24_write_reg ( c6dofimu24_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t c6dofimu24_read_reg ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t c6dofimu24_select_reg_bank ( c6dofimu24_t *ctx, uint8_t bank_num )
{
    if ( ( bank_num > C6DOFIMU24_USER_BANK_2 ) && ( C6DOFIMU24_USER_BANK_4 != bank_num ) )
    {
        return C6DOFIMU24_ERROR;
    }
    return c6dofimu24_write_reg ( ctx, C6DOFIMU24_REG0_REG_BANK_SEL, bank_num );
}

uint8_t c6dofimu24_get_int1_pin ( c6dofimu24_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

uint8_t c6dofimu24_get_int2_pin ( c6dofimu24_t *ctx )
{
    return digital_in_read ( &ctx->int2 );
}

err_t c6dofimu24_reset_device ( c6dofimu24_t *ctx )
{
    uint8_t int_status = 0;
    if ( C6DOFIMU24_OK == c6dofimu24_write_reg ( ctx, C6DOFIMU24_REG0_DEVICE_CONFIG, C6DOFIMU24_DEVICE_CONFIG_SOFT_RESET ) )
    {
        Delay_10ms ( );
        if ( C6DOFIMU24_OK == c6dofimu24_read_reg ( ctx, C6DOFIMU24_REG0_INT_STATUS, &int_status ) )
        {
            if ( int_status & C6DOFIMU24_INT_STATUS_RESET_DONE )
            {
                return C6DOFIMU24_OK;
            }
        }
    }
    return C6DOFIMU24_ERROR;
}

err_t c6dofimu24_check_communication ( c6dofimu24_t *ctx )
{
    uint8_t who_am_i = 0;
    if ( C6DOFIMU24_OK == c6dofimu24_read_reg ( ctx, C6DOFIMU24_REG0_WHO_AM_I, &who_am_i ) )
    {
        if ( C6DOFIMU24_WHO_AM_I == who_am_i )
        {
            return C6DOFIMU24_OK;
        }
    }
    return C6DOFIMU24_ERROR;
}

err_t c6dofimu24_clear_data_ready ( c6dofimu24_t *ctx )
{
    uint8_t status = 0;
    return c6dofimu24_read_reg ( ctx, C6DOFIMU24_REG0_INT_STATUS, &status );
}

err_t c6dofimu24_set_gyro_fs_odr ( c6dofimu24_t *ctx, uint8_t fs_sel, uint8_t odr )
{
    uint8_t reg_data = 0;
    if ( ( fs_sel > C6DOFIMU24_GYRO_FS_SEL_2000DPS ) || ( odr > C6DOFIMU24_GYRO_ODR_32000HZ ) )
    {
        return C6DOFIMU24_ERROR;
    }
    err_t error_flag = c6dofimu24_read_reg ( ctx, C6DOFIMU24_REG0_GYRO_CONFIG0, &reg_data );
    reg_data &= ~( C6DOFIMU24_GYRO_CONFIG0_FS_SEL_MASK | C6DOFIMU24_GYRO_CONFIG0_ODR_MASK );
    reg_data |= ( ( ( C6DOFIMU24_GYRO_FS_SEL_2000DPS - fs_sel ) << 5 ) & C6DOFIMU24_GYRO_CONFIG0_FS_SEL_MASK );
    if ( odr < C6DOFIMU24_GYRO_ODR_500HZ )
    {
        reg_data |= ( ( C6DOFIMU24_GYRO_CONFIG0_ODR_12_5HZ - odr ) & C6DOFIMU24_GYRO_CONFIG0_ODR_MASK );
    }
    else if ( odr > C6DOFIMU24_GYRO_ODR_500HZ )
    {
        reg_data |= ( ( C6DOFIMU24_GYRO_CONFIG0_ODR_12_5HZ - odr + 1 ) & C6DOFIMU24_GYRO_CONFIG0_ODR_MASK );
    }
    else if ( C6DOFIMU24_GYRO_ODR_500HZ == odr )
    {
        reg_data |= C6DOFIMU24_GYRO_CONFIG0_ODR_500HZ;
    }
    error_flag |= c6dofimu24_write_reg ( ctx, C6DOFIMU24_REG0_GYRO_CONFIG0, reg_data );
    ctx->gyro_sens = ( float ) C6DOFIMU24_GYRO_DATA_RES / ( C6DOFIMU24_GYRO_MIN_DPS * ( 1 << fs_sel ) );
    return error_flag;
}

err_t c6dofimu24_set_accel_fs_odr ( c6dofimu24_t *ctx, uint8_t fs_sel, uint8_t odr )
{
    uint8_t reg_data = 0;
    if ( ( fs_sel > C6DOFIMU24_ACCEL_FS_SEL_32G ) || ( odr > C6DOFIMU24_ACCEL_ODR_32000HZ ) )
    {
        return C6DOFIMU24_ERROR;
    }
    err_t error_flag = c6dofimu24_read_reg ( ctx, C6DOFIMU24_REG0_ACCEL_CONFIG0, &reg_data );
    reg_data &= ~( C6DOFIMU24_ACCEL_CONFIG0_FS_SEL_MASK | C6DOFIMU24_ACCEL_CONFIG0_ODR_MASK );
    reg_data |= ( ( ( C6DOFIMU24_ACCEL_FS_SEL_32G - fs_sel ) << 5 ) & C6DOFIMU24_ACCEL_CONFIG0_FS_SEL_MASK );
    if ( odr < C6DOFIMU24_ACCEL_ODR_500HZ )
    {
        reg_data |= ( ( C6DOFIMU24_ACCEL_CONFIG0_ODR_1_5625HZ - odr ) & C6DOFIMU24_GYRO_CONFIG0_ODR_MASK );
    }
    else if ( odr > C6DOFIMU24_ACCEL_ODR_500HZ )
    {
        reg_data |= ( ( C6DOFIMU24_ACCEL_CONFIG0_ODR_1_5625HZ - odr + 1 ) & C6DOFIMU24_GYRO_CONFIG0_ODR_MASK );
    }
    else if ( C6DOFIMU24_ACCEL_ODR_500HZ == odr )
    {
        reg_data |= C6DOFIMU24_ACCEL_CONFIG0_ODR_500HZ;
    }
    error_flag |= c6dofimu24_write_reg ( ctx, C6DOFIMU24_REG0_ACCEL_CONFIG0, reg_data );
    ctx->accel_sens = ( float ) C6DOFIMU24_ACCEL_DATA_RES / ( C6DOFIMU24_ACCEL_MIN_G << fs_sel );
    return error_flag;
}

err_t c6dofimu24_read_gyro ( c6dofimu24_t *ctx, c6dofimu24_axes_t *gyro )
{
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( C6DOFIMU24_OK == c6dofimu24_read_regs ( ctx, C6DOFIMU24_REG0_GYRO_DATA_X1, data_buf, 6 ) )
    {
        raw_data = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        gyro->x = ( float ) raw_data / ctx->gyro_sens;
        raw_data = ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
        gyro->y = ( float ) raw_data / ctx->gyro_sens;
        raw_data = ( ( int16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
        gyro->z = ( float ) raw_data / ctx->gyro_sens;
        return C6DOFIMU24_OK;
    }
    return C6DOFIMU24_ERROR;
}

err_t c6dofimu24_read_accel ( c6dofimu24_t *ctx, c6dofimu24_axes_t *accel )
{
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( C6DOFIMU24_OK == c6dofimu24_read_regs ( ctx, C6DOFIMU24_REG0_ACCEL_DATA_X1, data_buf, 6 ) )
    {
        raw_data = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        accel->x = ( float ) raw_data / ctx->accel_sens;
        raw_data = ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
        accel->y = ( float ) raw_data / ctx->accel_sens;
        raw_data = ( ( int16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
        accel->z = ( float ) raw_data / ctx->accel_sens;
        return C6DOFIMU24_OK;
    }
    return C6DOFIMU24_ERROR;
}

err_t c6dofimu24_read_temperature ( c6dofimu24_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( C6DOFIMU24_OK == c6dofimu24_read_regs ( ctx, C6DOFIMU24_REG0_TEMP_DATA1, data_buf, 2 ) )
    {
        raw_data = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        *temperature = ( ( float ) raw_data / C6DOFIMU24_TEMP_RES ) + C6DOFIMU24_TEMP_OFFSET;
        return C6DOFIMU24_OK;
    }
    return C6DOFIMU24_ERROR;
}

err_t c6dofimu24_read_data ( c6dofimu24_t *ctx, c6dofimu24_data_t *data_out )
{
    uint8_t data_buf[ 14 ] = { 0 };
    int16_t raw_data = 0;
    if ( C6DOFIMU24_OK == c6dofimu24_read_regs ( ctx, C6DOFIMU24_REG0_TEMP_DATA1, data_buf, 14 ) )
    {
        raw_data = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        data_out->temperature = ( ( float ) raw_data / C6DOFIMU24_TEMP_RES ) + C6DOFIMU24_TEMP_OFFSET;
        raw_data = ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
        data_out->accel.x = ( float ) raw_data / ctx->accel_sens;
        raw_data = ( ( int16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
        data_out->accel.y = ( float ) raw_data / ctx->accel_sens;
        raw_data = ( ( int16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 7 ];
        data_out->accel.z = ( float ) raw_data / ctx->accel_sens;
        raw_data = ( ( int16_t ) data_buf[ 8 ] << 8 ) | data_buf[ 9 ];
        data_out->gyro.x = ( float ) raw_data / ctx->gyro_sens;
        raw_data = ( ( int16_t ) data_buf[ 10 ] << 8 ) | data_buf[ 11 ];
        data_out->gyro.y = ( float ) raw_data / ctx->gyro_sens;
        raw_data = ( ( int16_t ) data_buf[ 12 ] << 8 ) | data_buf[ 13 ];
        data_out->gyro.z = ( float ) raw_data / ctx->gyro_sens;
        return C6DOFIMU24_OK;
    }
    return C6DOFIMU24_ERROR;
}

static err_t c6dofimu24_i2c_write ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t c6dofimu24_i2c_read ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t c6dofimu24_spi_write ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t c6dofimu24_spi_read ( c6dofimu24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
