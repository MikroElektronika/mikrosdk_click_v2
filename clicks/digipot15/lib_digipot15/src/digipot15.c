/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file digipot15.c
 * @brief DIGI POT 15 Click Driver.
 */

#include "digipot15.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief DIGI POT 15 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t digipot15_i2c_write ( digipot15_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief DIGI POT 15 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t digipot15_i2c_read ( digipot15_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief DIGI POT 15 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t digipot15_spi_write ( digipot15_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief DIGI POT 15 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot15_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t digipot15_spi_read ( digipot15_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

void digipot15_cfg_setup ( digipot15_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->com  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DIGIPOT15_DEVICE_ADDRESS_A1A0_00;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = DIGIPOT15_DRV_SEL_I2C;
}

void digipot15_drv_interface_sel ( digipot15_cfg_t *cfg, digipot15_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t digipot15_init ( digipot15_t *ctx, digipot15_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    digital_out_init( &ctx->com, cfg->com );
    Delay_1ms ( );

    if ( DIGIPOT15_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        digital_out_high ( &ctx->com );
        Delay_1ms ( );

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

        ctx->read_f  = digipot15_i2c_read;
        ctx->write_f = digipot15_i2c_write;
    } 
    else 
    {
        digital_out_low ( &ctx->com );
        Delay_1ms ( );

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

        ctx->read_f  = digipot15_spi_read;
        ctx->write_f = digipot15_spi_write;
    }

    return DIGIPOT15_OK;
}

err_t digipot15_default_cfg ( digipot15_t *ctx ) 
{
    err_t error_flag = DIGIPOT15_OK;
    error_flag |= digipot15_soft_reset ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t digipot15_write_reg ( digipot15_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t cmd = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    cmd = ( ( reg << 3 ) & DIGIPOT15_CMD_REG_MASK ) | DIGIPOT15_CMD_OP_WRITE_DATA;
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    return ctx->write_f( ctx, cmd, data_buf, 2 );
}

err_t digipot15_read_reg ( digipot15_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t cmd = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = DIGIPOT15_OK;
    if ( NULL == data_out )
    {
        return DIGIPOT15_ERROR;
    }
    cmd = ( ( reg << 3 ) & DIGIPOT15_CMD_REG_MASK ) | DIGIPOT15_CMD_OP_READ_DATA;
    error_flag = ctx->write_f( ctx, cmd, data_buf, 2 );
    if ( DIGIPOT15_OK == error_flag )
    {
        *data_out = ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) & DIGIPOT15_DATA_MASK;
    }
    return error_flag;
}

err_t digipot15_increment_wiper ( digipot15_t *ctx, uint8_t reg )
{
    uint8_t cmd = 0;
    cmd = ( ( reg << 3 ) & DIGIPOT15_CMD_REG_MASK ) | DIGIPOT15_CMD_OP_INCREMENT_WIPER;
    return ctx->write_f( ctx, cmd, NULL, 0 );
}

err_t digipot15_decrement_wiper ( digipot15_t *ctx, uint8_t reg )
{
    uint8_t cmd = 0;
    cmd = ( ( reg << 3 ) & DIGIPOT15_CMD_REG_MASK ) | DIGIPOT15_CMD_OP_DECREMENT_WIPER;
    return ctx->write_f( ctx, cmd, NULL, 0 );
}

err_t digipot15_soft_reset ( digipot15_t *ctx )
{
    return digipot15_write_reg ( ctx, DIGIPOT15_REG_RESET, DIGIPOT15_RESET_SWRSTVAL );
}

err_t digipot15_set_wiper ( digipot15_t *ctx, uint16_t wiper )
{
    return digipot15_write_reg ( ctx, DIGIPOT15_REG_VOLATILE_WIPER_0, wiper );
}

void digipot15_set_com_pin ( digipot15_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->com, state );
}

static err_t digipot15_i2c_write ( digipot15_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t cnt = 0;
    if ( len > 2 )
    {
        return DIGIPOT15_ERROR;
    }
    data_buf[ 0 ] = cmd;
    for ( cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t digipot15_i2c_read ( digipot15_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_out, len );
}

static err_t digipot15_spi_write ( digipot15_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    if ( len )
    {
        error_flag |= spi_master_write( &ctx->spi, data_in, len );
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t digipot15_spi_read ( digipot15_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
