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
 * @file accel4.c
 * @brief Accel 4 Click Driver.
 */

#include "accel4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                   0x00
#define SPI_READ_MASK           0x80

/**
 * @brief Resolution.
 * @details Data resolution macros.
 */
#define ACCEL4_2G_RES           0.98
#define ACCEL4_4G_RES           1.95
#define ACCEL4_8G_RES           3.91
#define ACCEL4_16G_RES          7.81
#define ACCEL4_2G_RES_REG_VAL   0
#define ACCEL4_4G_RES_REG_VAL   1
#define ACCEL4_8G_RES_REG_VAL   2
#define ACCEL4_16G_RES_REG_VAL  3

/**
 * @brief Accel 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel4_i2c_write ( accel4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel4_i2c_read ( accel4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 4 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel4_spi_write ( accel4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 4 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel4_spi_read ( accel4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel4_cfg_setup ( accel4_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int2   = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL4_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL4_DRV_SEL_I2C;
}

void accel4_drv_interface_selection ( accel4_cfg_t *cfg, accel4_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel4_init ( accel4_t *ctx, accel4_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL4_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel4_i2c_read;
        ctx->write_f = accel4_i2c_write;
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

        ctx->read_f  = accel4_spi_read;
        ctx->write_f = accel4_spi_write;
    }

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return 0;
}

err_t accel4_default_cfg ( accel4_t *ctx ) 
{
    uint8_t temp_data = 0;
    err_t ret_val = ACCEL4_OK;
    //Enable Interrupt for boot and data ready
    ret_val |= accel4_generic_read( ctx, ACCEL4_REG_INT_EN, &temp_data, 1 );
    temp_data |= 0x80;
    ret_val |= accel4_generic_write( ctx, ACCEL4_REG_INT_EN, &temp_data, 1 );
    //Enable active mode of device
    temp_data = 0x1;
    ret_val |= accel4_generic_write( ctx, ACCEL4_REG_SYS_MODE, &temp_data, 1 );
    ret_val |= accel4_generic_write( ctx, ACCEL4_REG_SENS_CONFIG1, &temp_data, 1 );
    
    ctx->resolution = accel4_axes_get_resolution( ctx );
    
    return ACCEL4_OK;
}

err_t accel4_generic_write ( accel4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel4_generic_read ( accel4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t accel4_get_int1 ( accel4_t *ctx )
{
    return digital_in_read( &ctx->int1 );
}

uint8_t accel4_get_int2 ( accel4_t *ctx )
{
    return digital_in_read( &ctx->int2 );
}

err_t accel4_get_axes_data ( accel4_t *ctx, accel4_axes_t *axes )
{
    uint8_t temp_axis_data[ 2 ] = { 0 };
    int16_t axis_data;
    err_t ret_val = ACCEL4_OK;
    ctx->resolution = 0.98;
    
    ret_val |= accel4_generic_read( ctx, ACCEL4_REG_OUT_X_LSB, &temp_axis_data, 2 );
    axis_data = temp_axis_data[ 0 ] | ( ( int16_t )temp_axis_data[ 1 ] << 8 );
    axes->x = axis_data * ctx->resolution;
    
    ret_val |= accel4_generic_read( ctx, ACCEL4_REG_OUT_Y_LSB, &temp_axis_data, 2 );
    axis_data = temp_axis_data[ 0 ] | ( ( int16_t )temp_axis_data[ 1 ] << 8 );
    axes->y = axis_data * ctx->resolution;
    
    ret_val |= accel4_generic_read( ctx, ACCEL4_REG_OUT_Z_LSB, &temp_axis_data, 2 );
    axis_data = temp_axis_data[ 0 ] | ( ( int16_t )temp_axis_data[ 1 ] << 8 );
    axes->z = axis_data * ctx->resolution;
    
    return ret_val;
}

float accel4_axes_get_resolution ( accel4_t *ctx )
{
    uint8_t res;
    accel4_generic_read( ctx, ACCEL4_REG_SENS_CONFIG1, &res, 1 );
    res >>= 1;
    res &= 3;
    
    switch ( res )
    {
        case ACCEL4_2G_RES_REG_VAL:
        {
            return ACCEL4_2G_RES;
        }
        case ACCEL4_4G_RES_REG_VAL:
        {
            return ACCEL4_4G_RES;
        }
        case ACCEL4_8G_RES_REG_VAL:
        {
            return ACCEL4_8G_RES;
        }
        case ACCEL4_16G_RES_REG_VAL:
        {
            return ACCEL4_16G_RES;
        }
        default:
        {
            return DUMMY;
        }
    }
}

static err_t accel4_i2c_write ( accel4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t accel4_i2c_read ( accel4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel4_spi_write ( accel4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = DUMMY;
    for ( uint8_t cnt = 2; cnt < len + 2; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 2 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t accel4_spi_read ( accel4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr[ 2 ] = { reg | SPI_READ_MASK, DUMMY };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, reg_adr, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

// ------------------------------------------------------------------------ END
