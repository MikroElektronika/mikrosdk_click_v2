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
 * @file compass9.c
 * @brief Compass 9 Click Driver.
 */

#include "compass9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Compass 9 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t compass9_i2c_write ( compass9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Compass 9 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t compass9_i2c_read ( compass9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Compass 9 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t compass9_spi_write ( compass9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Compass 9 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #compass9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t compass9_spi_read ( compass9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void compass9_cfg_setup ( compass9_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COMPASS9_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = COMPASS9_DRV_SEL_SPI;
}

void compass9_drv_interface_sel ( compass9_cfg_t *cfg, compass9_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t compass9_init ( compass9_t *ctx, compass9_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( COMPASS9_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = compass9_i2c_read;
        ctx->write_f = compass9_i2c_write;
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

        ctx->read_f  = compass9_spi_read;
        ctx->write_f = compass9_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    Delay_100ms ( );

    return COMPASS9_OK;
}

err_t compass9_default_cfg ( compass9_t *ctx ) 
{
    err_t error_flag = COMPASS9_OK;
    if ( COMPASS9_ERROR == compass9_check_communication ( ctx ) )
    {
        return COMPASS9_ERROR;
    }
    error_flag |= compass9_soft_reset ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t compass9_write_regs ( compass9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t compass9_read_regs ( compass9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t compass9_write_reg ( compass9_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t compass9_read_reg ( compass9_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

uint8_t compass9_get_int_pin ( compass9_t *ctx )
{
    return !!digital_in_read ( &ctx->int_pin );
}

err_t compass9_check_communication ( compass9_t *ctx )
{
    uint8_t num_tries = 10;
    uint8_t product_id = 0;
    while ( num_tries-- )
    {
        if ( COMPASS9_OK == compass9_read_reg ( ctx, COMPASS9_REG_PRODUCT_ID, &product_id ) )
        {
            if ( COMPASS9_PRODUCT_ID == product_id )
            {
                return COMPASS9_OK;
            }
        }
        Delay_10ms ( );
    }
    return COMPASS9_ERROR;
}

err_t compass9_soft_reset ( compass9_t *ctx )
{
    return compass9_write_reg ( ctx, COMPASS9_REG_CTRL1, COMPASS9_CTRL1_SW_RST );
}

err_t compass9_start_measurement ( compass9_t *ctx, uint8_t mode )
{
    err_t error_flag = COMPASS9_OK;
    if ( mode > COMPASS9_MEAS_CONTINUOUS_M_1000HZ )
    {
        return COMPASS9_ERROR;
    }
    if ( ( COMPASS9_MEAS_SINGLE_T == mode ) || ( COMPASS9_MEAS_SINGLE_M == mode ) )
    {
        error_flag |= compass9_write_reg ( ctx, COMPASS9_REG_CTRL2, COMPASS9_CTRL2_EN_PRD_SET | 
                                                                    COMPASS9_CTRL2_PRD_SET_1_SMPL | 
                                                                    COMPASS9_CTRL2_CM_FREQ_OFF );
        if ( COMPASS9_MEAS_SINGLE_T == mode )
        {
            error_flag |= compass9_write_reg ( ctx, COMPASS9_REG_CTRL0, COMPASS9_CTRL0_AUTO_SR_EN | 
                                                                        COMPASS9_CTRL0_INT_MEAS_DONE_EN |
                                                                        COMPASS9_CTRL0_TM_T );
        }
        else
        {
            error_flag |= compass9_write_reg ( ctx, COMPASS9_REG_CTRL0, COMPASS9_CTRL0_AUTO_SR_EN | 
                                                                        COMPASS9_CTRL0_INT_MEAS_DONE_EN |
                                                                        COMPASS9_CTRL0_TM_M );
        }
    }
    else
    {
        error_flag |= compass9_write_reg ( ctx, COMPASS9_REG_CTRL0, COMPASS9_CTRL0_AUTO_SR_EN | 
                                                                    COMPASS9_CTRL0_INT_MEAS_DONE_EN );
        error_flag |= compass9_write_reg ( ctx, COMPASS9_REG_CTRL2, COMPASS9_CTRL2_EN_PRD_SET | 
                                                                    COMPASS9_CTRL2_PRD_SET_1_SMPL | 
                                                                    COMPASS9_CTRL2_CMM_EN |
                                                                    ( mode - COMPASS9_MEAS_CONTINUOUS_M_1HZ + 1 ) );
    }
    return error_flag;
}

err_t compass9_get_magnetic_flux ( compass9_t *ctx, compass9_magnetic_flux_t *flux )
{
    err_t error_flag = COMPASS9_OK;
    uint32_t timeout_cnt = 0;
    int32_t raw_data = 0;
    uint8_t data_buf[ 7 ] = { 0 };
    while ( !compass9_get_int_pin ( ctx ) )
    {
        if ( timeout_cnt++ > COMPASS9_TIMEOUT )
        {
            return COMPASS9_ERROR;
        }
        Delay_1ms ( );
    }
    error_flag = compass9_read_reg ( ctx, COMPASS9_REG_STATUS, data_buf );
    if ( COMPASS9_OK == error_flag )
    {
        if ( COMPASS9_STATUS_MEAS_M_DONE != ( data_buf[ 0 ] & COMPASS9_STATUS_MEAS_M_DONE ) )
        {
            error_flag = COMPASS9_ERROR;
        }
    }
    if ( COMPASS9_OK == error_flag )
    {
        error_flag = compass9_write_reg ( ctx, COMPASS9_REG_STATUS, COMPASS9_STATUS_MEAS_M_DONE );
    }
    if ( COMPASS9_OK == error_flag )
    {
        error_flag = compass9_read_regs ( ctx, COMPASS9_REG_XOUT0, data_buf, 7 );
    }
    if ( COMPASS9_OK == error_flag )
    {
        raw_data = ( ( int32_t ) data_buf[ 0 ] << 10 ) | 
                   ( ( int32_t ) data_buf[ 1 ] << 2 ) | 
                   ( ( ( int32_t ) data_buf[ 6 ] >> 6 ) & 0x03 );
        flux->x_axis = ( raw_data - COMPASS9_MAGNETIC_OFFSET ) / COMPASS9_MAGNETIC_COUNTS_PER_G;
        raw_data = ( ( int32_t ) data_buf[ 2 ] << 10 ) | 
                   ( ( int32_t ) data_buf[ 3 ] << 2 ) | 
                   ( ( ( int32_t ) data_buf[ 6 ] >> 4 ) & 0x03 );
        flux->y_axis = ( raw_data - COMPASS9_MAGNETIC_OFFSET ) / COMPASS9_MAGNETIC_COUNTS_PER_G;
        raw_data = ( ( int32_t ) data_buf[ 4 ] << 10 ) | 
                   ( ( int32_t ) data_buf[ 5 ] << 2 ) | 
                   ( ( ( int32_t ) data_buf[ 6 ] >> 2 ) & 0x03 );
        flux->z_axis = ( raw_data - COMPASS9_MAGNETIC_OFFSET ) / COMPASS9_MAGNETIC_COUNTS_PER_G;
    }
    return error_flag;
}

err_t compass9_get_temperature ( compass9_t *ctx, float *temperature )
{
    err_t error_flag = COMPASS9_OK;
    uint32_t timeout_cnt = 0;
    uint8_t reg_data = 0;
    while ( !compass9_get_int_pin ( ctx ) )
    {
        if ( timeout_cnt++ > COMPASS9_TIMEOUT )
        {
            return COMPASS9_ERROR;
        }
        Delay_1ms ( );
    }
    error_flag = compass9_read_reg ( ctx, COMPASS9_REG_STATUS, &reg_data );
    if ( COMPASS9_OK == error_flag )
    {
        if ( COMPASS9_STATUS_MEAS_T_DONE != ( reg_data & COMPASS9_STATUS_MEAS_T_DONE ) )
        {
            error_flag = COMPASS9_ERROR;
        }
    }
    if ( COMPASS9_OK == error_flag )
    {
        error_flag = compass9_write_reg ( ctx, COMPASS9_REG_STATUS, COMPASS9_STATUS_MEAS_T_DONE );
    }
    if ( COMPASS9_OK == error_flag )
    {
        error_flag = compass9_read_reg ( ctx, COMPASS9_REG_TOUT, &reg_data );
    }
    if ( COMPASS9_OK == error_flag )
    {
        *temperature = reg_data * COMPASS9_TEMPERATURE_RESOLUTION - COMPASS9_TEMPERATURE_OFFSET;
    }
    return error_flag;
}

static err_t compass9_i2c_write ( compass9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t compass9_i2c_read ( compass9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t compass9_spi_write ( compass9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t compass9_spi_read ( compass9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
