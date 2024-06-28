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
 * @file inclinometer4.c
 * @brief Inclinometer 4 Click Driver.
 */

#include "inclinometer4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Inclinometer 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t inclinometer4_i2c_write ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Inclinometer 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t inclinometer4_i2c_read ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Inclinometer 4 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t inclinometer4_spi_write ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Inclinometer 4 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #inclinometer4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t inclinometer4_spi_read ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void inclinometer4_cfg_setup ( inclinometer4_cfg_t *cfg ) 
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
    cfg->i2c_address = INCLINOMETER4_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = INCLINOMETER4_DRV_SEL_I2C;
}

void inclinometer4_drv_interface_sel ( inclinometer4_cfg_t *cfg, inclinometer4_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t inclinometer4_init ( inclinometer4_t *ctx, inclinometer4_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( INCLINOMETER4_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = inclinometer4_i2c_read;
        ctx->write_f = inclinometer4_i2c_write;
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

        ctx->read_f  = inclinometer4_spi_read;
        ctx->write_f = inclinometer4_spi_write;
    }

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return INCLINOMETER4_OK;
}

err_t inclinometer4_default_cfg ( inclinometer4_t *ctx ) 
{
    err_t error_flag = INCLINOMETER4_OK;
    uint8_t reg_data = DUMMY;
    uint8_t num_tries = 0;
    for ( ; ; )
    {
        Delay_100ms ( );
        // Wait for a boot sequence completed flag
        if ( ( INCLINOMETER4_OK == inclinometer4_get_status( ctx, &reg_data ) ) &&
             ( reg_data & INCLINOMETER4_INT_STATUS_SRC_BOOT ) )
        {
            break;
        }
        if ( ++num_tries > 10 )
        {
            return INCLINOMETER4_ERROR;
        }
    }
    error_flag |= inclinometer4_sw_reset ( ctx );
    Delay_100ms ( );
    if ( INCLINOMETER4_ERROR == inclinometer4_check_comm ( ctx ) )
    {
        return INCLINOMETER4_ERROR;
    }
    error_flag |= inclinometer4_set_mode ( ctx, INCLINOMETER4_MODE_STANDBY );
    Delay_100ms ( );
    error_flag |= inclinometer4_set_fsr ( ctx, INCLINOMETER4_FSR_2G );
    error_flag |= inclinometer4_set_odr ( ctx, INCLINOMETER4_ODR_6_25_HZ );
    // Enable data ready interrupt on INT2 pin open-drain active low
    error_flag |= inclinometer4_write_reg ( ctx, INCLINOMETER4_REG_INT_EN, INCLINOMETER4_INT_EN_DRDY );
    error_flag |= inclinometer4_write_reg ( ctx, INCLINOMETER4_REG_INT_PIN_SEL, INCLINOMETER4_INT_PIN_SEL_DRDY_INT2 );
    error_flag |= inclinometer4_write_reg ( ctx, INCLINOMETER4_REG_SENS_CONFIG4, INCLINOMETER4_SENS_CONFIG4_INT_PP_OD );
    Delay_10ms ( );
    error_flag |= inclinometer4_set_mode ( ctx, INCLINOMETER4_MODE_ACTIVE );
    Delay_100ms ( );
    return error_flag;
}

err_t inclinometer4_write_regs ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t inclinometer4_read_regs ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t inclinometer4_write_reg ( inclinometer4_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t inclinometer4_read_reg ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

uint8_t inclinometer4_get_int1_pin ( inclinometer4_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

uint8_t inclinometer4_get_int2_pin ( inclinometer4_t *ctx )
{
    return digital_in_read ( &ctx->int2 );
}

err_t inclinometer4_check_comm ( inclinometer4_t *ctx )
{
    uint8_t device_id = DUMMY;
    if ( INCLINOMETER4_OK == inclinometer4_read_reg ( ctx, INCLINOMETER4_REG_WHO_AM_I, &device_id ) )
    {
        if ( INCLINOMETER4_WHO_AM_I == device_id )
        {
            return INCLINOMETER4_OK;
        }
    }
    return INCLINOMETER4_ERROR;
}

err_t inclinometer4_get_status ( inclinometer4_t *ctx, uint8_t *status ) 
{
    return inclinometer4_read_reg ( ctx, INCLINOMETER4_REG_INT_STATUS, status );
}

err_t inclinometer4_sw_reset ( inclinometer4_t *ctx ) 
{
    return inclinometer4_write_reg ( ctx, INCLINOMETER4_REG_SENS_CONFIG1, INCLINOMETER4_SENS_CONFIG1_RST );
}

err_t inclinometer4_set_mode ( inclinometer4_t *ctx, uint8_t mode ) 
{
    if ( mode > INCLINOMETER4_MODE_ACTIVE )
    {
        return INCLINOMETER4_ERROR;
    }
    uint8_t reg_data = DUMMY;
    err_t error_flag = inclinometer4_read_reg ( ctx, INCLINOMETER4_REG_SENS_CONFIG1, &reg_data );
    reg_data &= ( ~INCLINOMETER4_SENS_CONFIG1_MODE_MASK );
    reg_data |= mode;
    error_flag |= inclinometer4_write_reg ( ctx, INCLINOMETER4_REG_SENS_CONFIG1, reg_data );
    return error_flag;
}

err_t inclinometer4_set_fsr ( inclinometer4_t *ctx, uint8_t fsr ) 
{
    if ( fsr > INCLINOMETER4_FSR_16G )
    {
        return INCLINOMETER4_ERROR;
    }
    uint8_t reg_data = DUMMY;
    err_t error_flag = inclinometer4_read_reg ( ctx, INCLINOMETER4_REG_SENS_CONFIG1, &reg_data );
    reg_data &= ( ~INCLINOMETER4_SENS_CONFIG1_FSR_MASK );
    reg_data |= ( fsr << 1 );
    error_flag |= inclinometer4_write_reg ( ctx, INCLINOMETER4_REG_SENS_CONFIG1, reg_data );
    if ( INCLINOMETER4_OK == error_flag )
    {
        ctx->lsb_per_g = INCLINOMETER4_LSB_PER_G_FSR_2G >> fsr;
    }
    return error_flag;
}

err_t inclinometer4_set_odr ( inclinometer4_t *ctx, uint8_t odr ) 
{
    if ( odr > INCLINOMETER4_ODR_0_781_HZ )
    {
        return INCLINOMETER4_ERROR;
    }
    uint8_t reg_data = DUMMY;
    err_t error_flag = inclinometer4_read_reg ( ctx, INCLINOMETER4_REG_SENS_CONFIG3, &reg_data );
    reg_data &= ( ~INCLINOMETER4_SENS_CONFIG3_WAKE_ODR_MASK );
    reg_data |= ( odr << 4 );
    error_flag |= inclinometer4_write_reg ( ctx, INCLINOMETER4_REG_SENS_CONFIG3, reg_data );
    return error_flag;
}

err_t inclinometer4_get_data ( inclinometer4_t *ctx, inclinometer4_data_t *data_out )
{
    uint8_t data_buf[ 7 ] = { DUMMY };
    int16_t raw_data = DUMMY;
    uint8_t status = DUMMY;
    err_t error_flag = inclinometer4_get_status ( ctx, &status );
    if ( ( INCLINOMETER4_OK == error_flag ) && ( status & INCLINOMETER4_INT_STATUS_SRC_DRDY ) )
    {
        error_flag |= inclinometer4_read_regs ( ctx, INCLINOMETER4_REG_OUT_X_LSB, data_buf, 6 );
        error_flag |= inclinometer4_read_reg ( ctx, INCLINOMETER4_REG_TEMP_OUT, &data_buf[ 6 ] );
        if ( ( INCLINOMETER4_OK == error_flag ) && ( NULL != data_out ) )
        {
            raw_data = data_buf[ 1 ];
            raw_data <<= 8;
            raw_data |= data_buf[ 0 ];
            data_out->x = ( float ) raw_data / ctx->lsb_per_g;
            raw_data = data_buf[ 3 ];
            raw_data <<= 8;
            raw_data |= data_buf[ 2 ];
            data_out->y = ( float ) raw_data / ctx->lsb_per_g;
            raw_data = data_buf[ 5 ];
            raw_data <<= 8;
            raw_data |= data_buf[ 4 ];
            data_out->z = ( float ) raw_data / ctx->lsb_per_g;
            data_out->temperature = ( int8_t ) data_buf[ 6 ] + INCLINOMETER4_TEMP_OFFSET;
            return INCLINOMETER4_OK;
        }
    }
    return INCLINOMETER4_ERROR;
}

static err_t inclinometer4_i2c_write ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t inclinometer4_i2c_read ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t inclinometer4_spi_write ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 2 ] = { reg, DUMMY };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t inclinometer4_spi_read ( inclinometer4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t data_buf[ 2 ] = { reg | SPI_READ_MASK, DUMMY };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_buf, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
