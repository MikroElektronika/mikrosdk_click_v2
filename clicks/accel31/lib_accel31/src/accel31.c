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
 * @file accel31.c
 * @brief Accel 31 Click Driver.
 */

#include "accel31.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief ACCEL 31 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel31_i2c_write ( accel31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ACCEL 31 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel31_i2c_read ( accel31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ACCEL 31 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel31_spi_write ( accel31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ACCEL 31 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel31_spi_read ( accel31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel31_cfg_setup ( accel31_cfg_t *cfg ) 
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
    cfg->i2c_address = ACCEL31_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL31_DRV_SEL_SPI;
}

void accel31_drv_interface_sel ( accel31_cfg_t *cfg, accel31_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel31_init ( accel31_t *ctx, accel31_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL31_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel31_i2c_read;
        ctx->write_f = accel31_i2c_write;
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

        ctx->read_f  = accel31_spi_read;
        ctx->write_f = accel31_spi_write;
    }

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return ACCEL31_OK;
}

err_t accel31_default_cfg ( accel31_t *ctx ) 
{
    err_t error_flag = ACCEL31_OK;
    uint8_t reg_data = 0;
    // Dummy check to determine the serial interface
    accel31_check_communication ( ctx );
    Delay_10ms ( );

    if ( ACCEL31_ERROR == accel31_check_communication ( ctx ) )
    {
        return ACCEL31_ERROR;
    }
    // Switch to normal operating mode
    error_flag |= accel31_write_reg ( ctx, ACCEL31_REG_CMD_SUSPEND, ACCEL31_CMD_SUSPEND_MODE_NORMAL );
    Delay_1sec ( );

    // Set INT2 as output in I2C mode to prevent an unexpected detection of SPI
    if ( ( ACCEL31_DRV_SEL_I2C == ctx->drv_sel ) && ( ACCEL31_OK == error_flag ) )
    {
        error_flag |= accel31_write_reg ( ctx, ACCEL31_REG_INT2_CONF, ACCEL31_INT2_CONF_MODE_LATCH );
    }

    // Disable accelerometer and temperature sensors
    error_flag |= accel31_write_reg ( ctx, ACCEL31_REG_ACC_CONF_0, ACCEL31_ACC_CONF_0_SENSOR_DISABLE );
    Delay_100ms ( );

    // Set output data rate
    error_flag |= accel31_set_accel_odr ( ctx, ACCEL31_ACCEL_ODR_12_5_HZ );
    error_flag |= accel31_set_temp_odr ( ctx, ACCEL31_TEMP_ODR_12_5_HZ );

    // Set full scale range
    error_flag |= accel31_set_accel_fsr ( ctx, ACCEL31_ACCEL_FS_2G );

    // Enable accelerometer and temperature sensors
    error_flag |= accel31_write_reg ( ctx, ACCEL31_REG_ACC_CONF_0, ACCEL31_ACC_CONF_0_SENSOR_ENABLE );
    Delay_100ms ( );

    return error_flag;
}

err_t accel31_write_reg ( accel31_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t accel31_write_regs ( accel31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel31_read_reg ( accel31_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t accel31_read_regs ( accel31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t accel31_get_int1_pin ( accel31_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

uint8_t accel31_get_int2_pin ( accel31_t *ctx )
{
    return digital_in_read ( &ctx->int2 );
}

err_t accel31_check_communication ( accel31_t *ctx )
{
    uint8_t chip_id = 0;
    err_t error_flag = accel31_read_reg ( ctx, ACCEL31_REG_CHIP_ID, &chip_id );
    if ( ( ACCEL31_OK == error_flag ) && ( ACCEL31_CHIP_ID != chip_id ) )
    {
        error_flag = ACCEL31_ERROR;
    }
    return error_flag;
}

err_t accel31_sw_reset ( accel31_t *ctx )
{
    err_t error_flag = accel31_write_reg ( ctx, ACCEL31_REG_CMD, ACCEL31_CMD_SOFT_RESET );
    Delay_1sec ( );
    return error_flag;
}

err_t accel31_set_accel_odr ( accel31_t *ctx, uint8_t odr )
{
    err_t error_flag = ACCEL31_OK;
    uint8_t reg_data = 0;
    if ( odr > ACCEL31_ACCEL_ODR_6400_HZ )
    {
        error_flag = ACCEL31_ERROR;
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_read_reg ( ctx, ACCEL31_REG_ACC_CONF_1, &reg_data );
    }
    if ( ACCEL31_OK == error_flag )
    {
        reg_data &= ( ~( ACCEL31_ACC_CONF_1_ACC_ODR_MASK | ACCEL31_ACC_CONF_1_POWER_MODE_MASK ) );
        reg_data |= ( odr & ACCEL31_ACC_CONF_1_ACC_ODR_MASK );
        if ( odr >= ACCEL31_ACCEL_ODR_12_5_HZ )
        {
            reg_data |= ACCEL31_ACC_CONF_1_POWER_MODE_MASK;
        }
        error_flag = accel31_write_reg ( ctx, ACCEL31_REG_ACC_CONF_1, reg_data );
    }
    return error_flag;
}

err_t accel31_set_accel_fsr ( accel31_t *ctx, uint8_t fsr )
{
    err_t error_flag = ACCEL31_OK;
    uint8_t reg_data = 0;
    if ( fsr > ACCEL31_ACCEL_FS_16G )
    {
        error_flag = ACCEL31_ERROR;
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_read_reg ( ctx, ACCEL31_REG_ACC_CONF_2, &reg_data );
    }
    if ( ACCEL31_OK == error_flag )
    {
        reg_data &= ( ~ACCEL31_ACC_CONF_2_ACC_RANGE_MASK );
        reg_data |= ( fsr & ACCEL31_ACC_CONF_2_ACC_RANGE_MASK );
        ctx->accel_sens = ACCEL31_ACCEL_SENS_G_PER_LSB * ( 1 << fsr );
        error_flag = accel31_write_reg ( ctx, ACCEL31_REG_ACC_CONF_2, reg_data );
    }
    return error_flag;
}

err_t accel31_set_temp_odr ( accel31_t *ctx, uint8_t odr )
{
    err_t error_flag = ACCEL31_OK;
    uint8_t reg_data = 0;
    if ( odr > ACCEL31_TEMP_ODR_200_HZ )
    {
        error_flag = ACCEL31_ERROR;
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_read_reg ( ctx, ACCEL31_REG_TEMP_CONF, &reg_data );
    }
    if ( ACCEL31_OK == error_flag )
    {
        reg_data &= ( ~( ACCEL31_TEMP_CONF_RATE_MASK ) );
        reg_data |= ( odr & ACCEL31_TEMP_CONF_RATE_MASK );
        error_flag = accel31_write_reg ( ctx, ACCEL31_REG_TEMP_CONF, reg_data );
    }
    return error_flag;
}

err_t accel31_get_accel_drdy ( accel31_t *ctx, uint8_t *drdy )
{
    err_t error_flag = ACCEL31_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = ACCEL31_ERROR;
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_read_reg ( ctx, ACCEL31_REG_SENSOR_STATUS, &reg_data );
    }
    if ( ACCEL31_OK == error_flag )
    {
        *drdy = ( ACCEL31_SENSOR_STATUS_ACC_RDY & reg_data );
    }
    return error_flag;
}

err_t accel31_get_temp_drdy ( accel31_t *ctx, uint8_t *drdy )
{
    err_t error_flag = ACCEL31_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = ACCEL31_ERROR;
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_read_reg ( ctx, ACCEL31_REG_SENSOR_STATUS, &reg_data );
    }
    if ( ACCEL31_OK == error_flag )
    {
        *drdy = ( ( ACCEL31_SENSOR_STATUS_TEMP_RDY & reg_data ) >> 1 );
    }
    return error_flag;
}

err_t accel31_get_accel ( accel31_t *ctx, accel31_axes_t *accel )
{
    err_t error_flag = ACCEL31_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == accel )
    {
        error_flag = ACCEL31_ERROR;
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_get_accel_drdy ( ctx, &drdy );
    }
    if ( ACCEL31_OK == error_flag )
    {
        if ( drdy )
        {
            error_flag = accel31_write_reg ( ctx, ACCEL31_REG_SENSOR_STATUS, ACCEL31_SENSOR_STATUS_ACC_RDY );
        }
        else
        {
            error_flag = ACCEL31_DATA_NOT_READY;
        }
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_read_regs ( ctx, ACCEL31_REG_ACC_DATA_0, data_buf, 6 );
    }
    if ( ACCEL31_OK == error_flag )
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

err_t accel31_get_temp ( accel31_t *ctx, int8_t *temp )
{
    err_t error_flag = ACCEL31_OK;
    uint8_t drdy = 0;
    uint8_t reg_data = 0;
    int8_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = ACCEL31_ERROR;
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_get_temp_drdy ( ctx, &drdy );
    }
    if ( ACCEL31_OK == error_flag )
    {
        if ( drdy )
        {
            error_flag = accel31_write_reg ( ctx, ACCEL31_REG_SENSOR_STATUS, ACCEL31_SENSOR_STATUS_TEMP_RDY );
        }
        else
        {
            error_flag = ACCEL31_DATA_NOT_READY;
        }
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_read_reg ( ctx, ACCEL31_REG_TEMP_DATA, &reg_data );
    }
    if ( ACCEL31_OK == error_flag )
    {
        raw_data = ( int8_t ) reg_data;
        *temp = raw_data + ACCEL31_TEMP_OFFSET;
    }
    return error_flag;
}

err_t accel31_get_data ( accel31_t *ctx, accel31_data_t *data_out )
{
    err_t error_flag = ACCEL31_OK;
    if ( NULL == data_out )
    {
        error_flag = ACCEL31_ERROR;
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_get_temp ( ctx, &data_out->temperature );
    }
    if ( ACCEL31_OK == error_flag )
    {
        error_flag = accel31_get_accel ( ctx, &data_out->accel );
    }
    return error_flag;
}

static err_t accel31_i2c_write ( accel31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel31_i2c_read ( accel31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel31_spi_write ( accel31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel31_spi_read ( accel31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, 1 );
    error_flag |= spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
