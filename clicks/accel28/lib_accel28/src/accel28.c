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
 * @file accel28.c
 * @brief Accel 28 Click Driver.
 */

#include "accel28.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Accel 28 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel28_i2c_write ( accel28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 28 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel28_i2c_read ( accel28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 28 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel28_spi_write ( accel28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 28 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel28_spi_read ( accel28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel28_cfg_setup ( accel28_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL28_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL28_DRV_SEL_I2C;
}

void accel28_drv_interface_selection ( accel28_cfg_t *cfg, accel28_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel28_init ( accel28_t *ctx, accel28_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL28_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel28_i2c_read;
        ctx->write_f = accel28_i2c_write;
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

        ctx->read_f  = accel28_spi_read;
        ctx->write_f = accel28_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ACCEL28_OK;
}

err_t accel28_default_cfg ( accel28_t *ctx ) 
{
    err_t error_flag = ACCEL28_OK;
    
    error_flag |= accel28_sw_reset( ctx );
    
    error_flag |= accel28_write_reg ( ctx, ACCEL28_REG_CTRL1, ACCEL28_CTRL1_HR_MODE
                                                            | ACCEL28_CTRL1_ODR_100HZ 
                                                            | ACCEL28_CTRL1_BLOCK_DATA_UPATE_EN 
                                                            | ACCEL28_CTRL1_X_AXIS_ENABLE 
                                                            | ACCEL28_CTRL1_Y_AXIS_ENABLE 
                                                            | ACCEL28_CTRL1_Z_AXIS_ENABLE );
    error_flag |= accel28_write_reg ( ctx, ACCEL28_REG_CTRL2, ACCEL28_CTRL2_HPM_FREQ_DEV_100 );
    error_flag |= accel28_write_reg ( ctx, ACCEL28_REG_CTRL3, ACCEL28_CTRL3_INT1_DRDY_EN );
    error_flag |= accel28_write_reg ( ctx, ACCEL28_REG_CTRL4, ACCEL28_CTRL4_FS_2G 
                                                            | ACCEL28_CTRL4_ADD_INC_ENABLED );
    error_flag |= accel28_write_reg ( ctx, ACCEL28_REG_CTRL5, ACCEL28_CTRL5_DEC_UDATE_8_SAMPLES 
                                                            | ACCEL28_CTRL5_INT_ACTIVE_HIGH );

    return error_flag;
}

err_t accel28_generic_write ( accel28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel28_generic_read ( accel28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t accel28_get_int_state ( accel28_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t accel28_get_raw_data ( accel28_t *ctx, accel28_data_t *data_out )
{
    err_t error_flag = ACCEL28_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= accel28_generic_read( ctx, ACCEL28_REG_OUT_X_L, tmp_data, 2 );
    data_out->x_data = ( float ) ( ( ( int16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ] );
    
    error_flag |= accel28_generic_read( ctx, ACCEL28_REG_OUT_Y_L, tmp_data, 2 );
    data_out->y_data = ( float ) ( ( ( int16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ] );
    
    error_flag |= accel28_generic_read( ctx, ACCEL28_REG_OUT_Z_L, tmp_data, 2 );
    data_out->z_data = ( float ) ( ( ( int16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ] );
    
    return error_flag;
}

err_t accel28_get_data ( accel28_t *ctx, accel28_data_t *data_out )
{
    err_t error_flag = ACCEL28_OK;
    accel28_data_t tmp_data;
    uint8_t reg_data;
    
    error_flag |= accel28_get_raw_data( ctx, &tmp_data );
    
    error_flag |= accel28_read_reg( ctx, ACCEL28_REG_CTRL4, &reg_data );
    switch ( reg_data & ACCEL28_CTRL4_FS_MASK )
    {
        case ( ACCEL28_CTRL4_FS_2G ):
        {
            data_out->x_data = tmp_data.x_data * ACCEL28_2G_DATA_CONV;
            data_out->y_data = tmp_data.y_data * ACCEL28_2G_DATA_CONV;
            data_out->z_data = tmp_data.z_data * ACCEL28_2G_DATA_CONV;
            break;
        }
        
        case ( ACCEL28_CTRL4_FS_4G ):
        {
            data_out->x_data = tmp_data.x_data * ACCEL28_4G_DATA_CONV;
            data_out->y_data = tmp_data.y_data * ACCEL28_4G_DATA_CONV;
            data_out->z_data = tmp_data.z_data * ACCEL28_4G_DATA_CONV;
            break;
        }
        
        case ( ACCEL28_CTRL4_FS_8G ):
        {
            data_out->x_data = tmp_data.x_data * ACCEL28_8G_DATA_CONV;
            data_out->y_data = tmp_data.y_data * ACCEL28_8G_DATA_CONV;
            data_out->z_data = tmp_data.z_data * ACCEL28_8G_DATA_CONV;
            break;
        }
        
        default:
        {
            error_flag = ACCEL28_ERROR;
        }
    }
    
    return error_flag;
}

err_t accel28_write_reg ( accel28_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = ACCEL28_OK;
    
    error_flag |= accel28_generic_write( ctx, reg, &data_in, 1 );
    
    return error_flag;
}

err_t accel28_read_reg ( accel28_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = ACCEL28_OK;
    
    error_flag |= accel28_generic_read( ctx, reg, data_out, 1 );
    
    return error_flag;
}

err_t accel28_sw_reset ( accel28_t *ctx )
{
    err_t error_flag = ACCEL28_OK;
    uint8_t tmp_data = 0;
    
    error_flag |= accel28_read_reg( ctx, ACCEL28_REG_CTRL5, &tmp_data );
    tmp_data |= ACCEL28_CTRL5_SW_RESET;
    error_flag |= accel28_write_reg( ctx, ACCEL28_REG_CTRL5, tmp_data );
    
    return error_flag;
}

static err_t accel28_i2c_write ( accel28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel28_i2c_read ( accel28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel28_spi_write ( accel28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel28_spi_read ( accel28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
