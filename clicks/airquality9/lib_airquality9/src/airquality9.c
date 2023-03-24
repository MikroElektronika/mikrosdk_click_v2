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
 * @file airquality9.c
 * @brief Air Quality 9 Click Driver.
 */

#include "airquality9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x01

/**
 * @brief Air Quality 9 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airquality9_i2c_write ( airquality9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Quality 9 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airquality9_i2c_read ( airquality9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Air Quality 9 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airquality9_spi_write ( airquality9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Quality 9 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airquality9_spi_read ( airquality9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void airquality9_cfg_setup ( airquality9_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AIRQUALITY9_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = AIRQUALITY9_DRV_SEL_I2C;
}

void airquality9_drv_interface_selection ( airquality9_cfg_t *cfg, airquality9_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t airquality9_init ( airquality9_t *ctx, airquality9_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( AIRQUALITY9_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = airquality9_i2c_read;
        ctx->write_f = airquality9_i2c_write;
        
        digital_out_t cs_pin;
        digital_out_init( &cs_pin, cfg->cs );
        digital_out_high( &cs_pin );
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

        ctx->read_f  = airquality9_spi_read;
        ctx->write_f = airquality9_spi_write;
    }

    digital_out_init( &ctx->en, cfg->en );
    digital_out_low ( &ctx->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return AIRQUALITY9_OK;
}

err_t airquality9_default_cfg ( airquality9_t *ctx )
{
    err_t error_flag = AIRQUALITY9_OK;
    
    airquality9_enable_device ( ctx );
    Delay_1sec ( );
    
    if ( AIRQUALITY9_ERROR == airquality9_check_communication ( ctx ) )
    {
        return AIRQUALITY9_ERROR;
    }
    
    error_flag |= airquality9_set_interrupt_config ( ctx, AIRQUALITY_CONFIG_INTPOL_HIGH | 
                                                          AIRQUALITY_CONFIG_INTCFG_PUSH_PULL | 
                                                          AIRQUALITY_CONFIG_INTDAT_BIT |
                                                          AIRQUALITY_CONFIG_INTEN_BIT );
    
    error_flag |= airquality9_set_operating_mode ( ctx, AIRQUALITY9_OPMODE_STANDARD );
    
    return error_flag;
}

err_t airquality9_generic_write ( airquality9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t airquality9_generic_read ( airquality9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

void airquality9_enable_device ( airquality9_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void airquality9_disable_device ( airquality9_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t airquality9_get_int_pin ( airquality9_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t airquality9_check_communication ( airquality9_t *ctx )
{
    uint8_t part_id[ 2 ];
    if ( AIRQUALITY9_OK == airquality9_generic_read ( ctx, AIRQUALITY9_REG_PART_ID, part_id, 2 ) )
    {
        if ( ( AIRQUALITY9_PART_ID_LSB == part_id[ 0 ] ) && ( AIRQUALITY9_PART_ID_MSB == part_id[ 1 ] ) )
        {
            return AIRQUALITY9_OK;
        }
    }
    return AIRQUALITY9_ERROR;
}

err_t airquality9_set_operating_mode ( airquality9_t *ctx, uint8_t opmode )
{
    if ( ( opmode > AIRQUALITY9_OPMODE_STANDARD ) && ( AIRQUALITY9_OPMODE_RESET != opmode ) )
    {
        return AIRQUALITY9_ERROR;
    }
    return airquality9_generic_write ( ctx, AIRQUALITY9_REG_OPMODE, &opmode, 1 );
}

err_t airquality9_set_interrupt_config ( airquality9_t *ctx, uint8_t int_cfg )
{
    return airquality9_generic_write ( ctx, AIRQUALITY9_REG_CONFIG, &int_cfg, 1 );
}

err_t airquality9_read_status ( airquality9_t *ctx, uint8_t *status )
{
    return airquality9_generic_read ( ctx, AIRQUALITY9_REG_DATA_STATUS, status, 1 );
}

err_t airquality9_read_aqi_uba ( airquality9_t *ctx, uint8_t *aqi_uba )
{
    return airquality9_generic_read ( ctx, AIRQUALITY9_REG_DATA_AQI, aqi_uba, 1 );
}

err_t airquality9_read_tvoc ( airquality9_t *ctx, uint16_t *tvoc )
{
    uint8_t raw_data[ 2 ];
    if ( AIRQUALITY9_OK == airquality9_generic_read ( ctx, AIRQUALITY9_REG_DATA_TVOC, raw_data, 2 ) )
    {
        *tvoc = ( ( uint16_t ) raw_data[ 1 ] << 8 ) | raw_data[ 0 ];
        return AIRQUALITY9_OK;
    }
    return AIRQUALITY9_ERROR;
}

err_t airquality9_read_eco2 ( airquality9_t *ctx, uint16_t *eco2 )
{
    uint8_t raw_data[ 2 ];
    if ( AIRQUALITY9_OK == airquality9_generic_read ( ctx, AIRQUALITY9_REG_DATA_ECO2, raw_data, 2 ) )
    {
        *eco2 = ( ( uint16_t ) raw_data[ 1 ] << 8 ) | raw_data[ 0 ];
        return AIRQUALITY9_OK;
    }
    return AIRQUALITY9_ERROR;
}

static err_t airquality9_i2c_write ( airquality9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        tx_buf[ cnt + 1 ] = data_in[ cnt ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t airquality9_i2c_read ( airquality9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t airquality9_spi_write ( airquality9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = ( reg << 1 ) & ~SPI_READ_MASK;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        tx_buf[ cnt + 1 ] = data_in[ cnt ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t airquality9_spi_read ( airquality9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t reg_adr = ( reg << 1 ) | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

// ------------------------------------------------------------------------ END
