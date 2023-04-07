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
 * @file accel29.c
 * @brief Accel 29 Click Driver.
 */

#include "accel29.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY               0x00

/**
 * @brief Accel 29 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel29_i2c_write ( accel29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 29 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel29_i2c_read ( accel29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 29 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel29_spi_write ( accel29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 29 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel29_spi_read ( accel29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel29_cfg_setup ( accel29_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;
    cfg->int2 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL29_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL29_DRV_SEL_I2C;
}

void accel29_drv_interface_selection ( accel29_cfg_t *cfg, accel29_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel29_init ( accel29_t *ctx, accel29_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL29_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel29_i2c_read;
        ctx->write_f = accel29_i2c_write;
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

        ctx->read_f  = accel29_spi_read;
        ctx->write_f = accel29_spi_write;
    }

    digital_in_init( &ctx->int1, cfg->int1 );
    digital_in_init( &ctx->int2, cfg->int2 );

    return ACCEL29_OK;
}

err_t accel29_default_cfg ( accel29_t *ctx ) 
{
    err_t error_flag = ACCEL29_OK;
    if ( ACCEL29_ERROR == accel29_check_communication ( ctx ) )
    {
        return ACCEL29_ERROR;
    }
    error_flag |= accel29_write_register ( ctx, ACCEL29_REG_INT_ENABLE, ACCEL29_INT_ENABLE_DATA_READY );
    error_flag |= accel29_write_register ( ctx, ACCEL29_REG_INT_MAP, ACCEL29_INT_MAP_DATA_READY_INT2 );
    error_flag |= accel29_write_register ( ctx, ACCEL29_REG_BW_RATE, ACCEL29_BW_RATE_100_HZ );
    error_flag |= accel29_write_register ( ctx, ACCEL29_REG_POWER_CTL, ACCEL29_POWER_CTL_MEASURE );
    Delay_100ms ( );
    return error_flag;
}

err_t accel29_generic_write ( accel29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel29_generic_read ( accel29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel29_write_register ( accel29_t *ctx, uint8_t reg, uint8_t data_in )
{
    return accel29_generic_write ( ctx, reg, &data_in, 1 );
}

err_t accel29_read_register ( accel29_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return accel29_generic_read ( ctx, reg, data_out, 1 );
}

err_t accel29_check_communication ( accel29_t *ctx )
{
    uint8_t devid;
    if ( ACCEL29_OK == accel29_read_register ( ctx, ACCEL29_REG_DEVID, &devid ) )
    {
        if ( ACCEL29_DEVID == devid )
        {
            return ACCEL29_OK;
        }
    }
    return ACCEL29_ERROR;
}

uint8_t accel29_get_int1_pin ( accel29_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

uint8_t accel29_get_int2_pin ( accel29_t *ctx )
{
    return digital_in_read ( &ctx->int2 );
}

err_t accel29_get_axes ( accel29_t *ctx, accel29_axes_t *axes )
{
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    err_t error_flag = accel29_generic_read ( ctx, ACCEL29_REG_DATA_X0, data_buf, 6 );
    if ( ( NULL != axes ) && ( ACCEL29_OK == error_flag ) )
    {
        raw_data = ( ( int16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        axes->x = raw_data / ACCEL29_SCALE_FACTOR_LSB_PER_G;
        raw_data = ( ( int16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        axes->y = raw_data / ACCEL29_SCALE_FACTOR_LSB_PER_G;
        raw_data = ( ( int16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ];
        axes->z = raw_data / ACCEL29_SCALE_FACTOR_LSB_PER_G;
    }
    return error_flag;
}

err_t accel29_get_avg_axes ( accel29_t *ctx, uint16_t num_samples, accel29_axes_t *avg_axes )
{
    err_t error_flag = ACCEL29_OK;
    accel29_axes_t axes = { 0 };
    uint16_t data_cnt = 0;
    while ( data_cnt < num_samples )
    {
        // Wait for data ready indication
        while ( !accel29_get_int2_pin ( ctx ) );
        
        accel29_axes_t tmp_axes;
        error_flag |= accel29_get_axes ( ctx, &tmp_axes );
        axes.x += tmp_axes.x;
        axes.y += tmp_axes.y;
        axes.z += tmp_axes.z;
        data_cnt++;
    }
    avg_axes->x = axes.x / num_samples;
    avg_axes->y = axes.y / num_samples;
    avg_axes->z = axes.z / num_samples;
    return error_flag;
}

err_t accel29_calibrate_offset ( accel29_t *ctx, accel29_axes_t calib_axes )
{
    accel29_axes_t axes;
    err_t error_flag = accel29_write_register ( ctx, ACCEL29_REG_OFSX, ACCEL29_OFS_RESET );
    error_flag |= accel29_write_register ( ctx, ACCEL29_REG_OFSY, ACCEL29_OFS_RESET );
    error_flag |= accel29_write_register ( ctx, ACCEL29_REG_OFSZ, ACCEL29_OFS_RESET );
    Delay_100ms ( );
    error_flag |= accel29_get_avg_axes ( ctx, ACCEL29_NUM_OF_SAMPLES, &axes );
    
    int8_t offset = ( int8_t ) ( ( calib_axes.x - axes.x ) / ACCEL29_OFS_SCALE_FACTOR_G_PER_LSB );
    error_flag |= accel29_write_register ( ctx, ACCEL29_REG_OFSX, ( uint8_t ) offset );
    offset = ( int8_t ) ( ( calib_axes.y - axes.y ) / ACCEL29_OFS_SCALE_FACTOR_G_PER_LSB );
    error_flag |= accel29_write_register ( ctx, ACCEL29_REG_OFSY, ( uint8_t ) offset );
    offset = ( int8_t ) ( ( calib_axes.z - axes.z ) / ACCEL29_OFS_SCALE_FACTOR_G_PER_LSB );
    error_flag |= accel29_write_register ( ctx, ACCEL29_REG_OFSZ, ( uint8_t ) offset );
    return error_flag;
}

static err_t accel29_i2c_write ( accel29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel29_i2c_read ( accel29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel29_spi_write ( accel29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t reg_adr = ( reg & ACCEL29_ADDRESS_MASK );
    if ( len > 1 )
    {
        reg_adr |= ACCEL29_SPI_MB_BIT;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_adr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel29_spi_read ( accel29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = ( reg & ACCEL29_ADDRESS_MASK ) | ACCEL29_SPI_RW_BIT;
    if ( len > 1 )
    {
        reg_adr |= ACCEL29_SPI_MB_BIT;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
