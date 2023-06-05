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
 * @file gyro6.c
 * @brief Gyro 6 Click Driver.
 */

#include "gyro6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Gyro 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gyro6_i2c_write ( gyro6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Gyro 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gyro6_i2c_read ( gyro6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Gyro 6 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gyro6_spi_write ( gyro6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Gyro 6 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gyro6_spi_read ( gyro6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void gyro6_cfg_setup ( gyro6_cfg_t *cfg )
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GYRO6_SET_DEV_ADDR_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = GYRO6_DRV_SEL_I2C;
}

void gyro6_drv_interface_selection ( gyro6_cfg_t *cfg, gyro6_drv_t drv_sel )
{
    cfg->drv_sel = drv_sel;
}

err_t gyro6_init ( gyro6_t *ctx, gyro6_cfg_t *cfg )
{
    ctx->drv_sel = cfg->drv_sel;

    if ( GYRO6_DRV_SEL_I2C == ctx->drv_sel )
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

        ctx->read_f  = gyro6_i2c_read;
        ctx->write_f = gyro6_i2c_write;
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

        ctx->read_f  = gyro6_spi_read;
        ctx->write_f = gyro6_spi_write;
    }

    digital_out_init( &ctx->pwm, cfg->pwm );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return GYRO6_OK;
}

err_t gyro6_default_cfg ( gyro6_t *ctx )
{
    gyro6_set_pwm_pin ( ctx, 0 );

    if ( GYRO6_ERROR == gyro6_check_communication ( ctx ) )
    {
        return GYRO6_ERROR;
    }

    err_t error_flag = gyro6_write_register ( ctx, GYRO6_REG_PWR_MGMT_1, GYRO6_PWR_MGMT_1_DEVICE_RESET );
    Delay_1sec( );

    error_flag |= gyro6_write_register ( ctx, GYRO6_REG_PWR_MGMT_1, GYRO6_PWR_MGMT_1_AUTO_SEL_CLOCK );

    error_flag |= gyro6_write_register ( ctx, GYRO6_REG_GYRO_CONFIG, GYRO6_GYRO_CONFIG_FS_SEL_1000DPS );

    error_flag |= gyro6_write_register ( ctx, GYRO6_REG_INT_PIN_CFG, GYRO6_INT_PIN_CFG_LATCH_INT_EN |
                                                                     GYRO6_INT_PIN_CFG_INT_RD_CLEAR );

    error_flag |= gyro6_write_register ( ctx, GYRO6_REG_INT_ENABLE, GYRO6_INT_ENABLE_DATA_RDY_INT_EN );

    error_flag |= gyro6_set_low_power_mode ( ctx, GYRO6_SAMPLE_RATE_10HZ, GYRO6_LP_MODE_CFG_G_AVGCFG_128X );

    return error_flag;
}

err_t gyro6_generic_write ( gyro6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t gyro6_generic_read ( gyro6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t gyro6_write_register ( gyro6_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t gyro6_read_register ( gyro6_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

uint8_t gyro6_get_int_pin ( gyro6_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void gyro6_set_pwm_pin ( gyro6_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->pwm, state );
}

err_t gyro6_check_communication ( gyro6_t *ctx )
{
    uint8_t devid = 0;
    if ( GYRO6_OK == gyro6_read_register ( ctx, GYRO6_REG_WHO_AM_I, &devid ) )
    {
        if ( GYRO6_DEVICE_ID == devid )
        {
            return GYRO6_OK;
        }
    }
    return GYRO6_ERROR;
}

err_t gyro6_read_die_temperature ( gyro6_t *ctx, float *temperature )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    int16_t raw_temp = 0;

    if ( GYRO6_ERROR == gyro6_generic_read ( ctx, GYRO6_REG_TEMP_OUT_H, rx_buf, 2 ) )
    {
        return GYRO6_ERROR;
    }

    raw_temp = rx_buf[ 0 ];
    raw_temp <<= 8;
    raw_temp |= rx_buf[ 1 ];

    *temperature = ( float ) raw_temp - GYRO6_ROOM_TEMP_OFFSET;
    *temperature /= GYRO6_TEMP_SENSITIVITY;
    *temperature += GYRO6_TEMP_NOMINAL;

    return GYRO6_OK;
}

err_t gyro6_get_axis ( gyro6_t *ctx, float *x_axis, float *y_axis, float *z_axis )
{
    uint8_t rx_buf[ 6 ];
    int16_t aux_x_axis = 0;
    int16_t aux_y_axis = 0;
    int16_t aux_z_axis = 0;
    float gyro_sens = 0;

    if ( GYRO6_ERROR == gyro6_read_register ( ctx, GYRO6_REG_GYRO_CONFIG, rx_buf ) )
    {
        return GYRO6_ERROR;
    }

    rx_buf[ 0 ] &= GYRO6_GYRO_CONFIG_FS_SEL_BITS_MASK;

    switch ( rx_buf[ 0 ] )
    {
        case GYRO6_GYRO_CONFIG_FS_SEL_250DPS :
        {
            gyro_sens = GYRO6_GYRO_SENSITIVITY_FS_SEL_0;
            break;
        }
        case GYRO6_GYRO_CONFIG_FS_SEL_500DPS :
        {
            gyro_sens = GYRO6_GYRO_SENSITIVITY_FS_SEL_1;
            break;
        }
        case GYRO6_GYRO_CONFIG_FS_SEL_1000DPS :
        {
            gyro_sens = GYRO6_GYRO_SENSITIVITY_FS_SEL_2;
            break;
        }
        case GYRO6_GYRO_CONFIG_FS_SEL_2000DPS :
        {
            gyro_sens = GYRO6_GYRO_SENSITIVITY_FS_SEL_3;
            break;
        }
        default :
        {
            return GYRO6_ERROR;
        }
    }

    if ( GYRO6_ERROR == gyro6_generic_read ( ctx, GYRO6_REG_GYRO_XOUT_H, rx_buf, 6 ) )
    {
        return GYRO6_ERROR;
    }

    aux_x_axis = rx_buf[ 0 ];
    aux_x_axis <<= 8;
    aux_x_axis |= rx_buf[ 1 ];

    aux_y_axis = rx_buf[ 2 ];
    aux_y_axis <<= 8;
    aux_y_axis |= rx_buf[ 3 ];

    aux_z_axis = rx_buf[ 4 ];
    aux_z_axis <<= 8;
    aux_z_axis |= rx_buf[ 5 ];

    *x_axis = ( float ) aux_x_axis / gyro_sens;
    *y_axis = ( float ) aux_y_axis / gyro_sens;
    *z_axis = ( float ) aux_z_axis / gyro_sens;

    return GYRO6_OK;
}

err_t gyro6_set_low_power_mode ( gyro6_t *ctx, uint8_t sample_rate, uint8_t average )
{
    if ( GYRO6_ERROR == gyro6_write_register ( ctx, GYRO6_REG_SMPLRT_DIV, sample_rate ) )
    {
        return GYRO6_ERROR;
    }

    average &= GYRO6_LP_MODE_CFG_G_AVGCFG_128X;
    if ( GYRO6_ERROR == gyro6_write_register ( ctx, GYRO6_REG_LP_MODE_CFG,
                                                    GYRO6_LP_MODE_CFG_GYRO_CYCLE |
                                                    average ) )
    {
        return GYRO6_ERROR;
    }
    return GYRO6_OK;
}

static err_t gyro6_i2c_write ( gyro6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t gyro6_i2c_read ( gyro6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t gyro6_spi_write ( gyro6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
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

static err_t gyro6_spi_read ( gyro6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

// ------------------------------------------------------------------------ END
