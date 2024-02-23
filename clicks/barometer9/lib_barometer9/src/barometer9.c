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
 * @file barometer9.c
 * @brief Barometer 9 Click Driver.
 */

#include "barometer9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x01

/**
 * @brief Barometer 9 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer9_i2c_write ( barometer9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 9 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer9_i2c_read ( barometer9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 9 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer9_spi_write ( barometer9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 9 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer9_spi_read ( barometer9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void barometer9_cfg_setup ( barometer9_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BAROMETER9_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = BAROMETER9_DRV_SEL_SPI;
    
}

void barometer9_drv_interface_sel ( barometer9_cfg_t *cfg, barometer9_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t barometer9_init ( barometer9_t *ctx, barometer9_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( BAROMETER9_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = barometer9_i2c_read;
        ctx->write_f = barometer9_i2c_write;
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

        ctx->read_f  = barometer9_spi_read;
        ctx->write_f = barometer9_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return BAROMETER9_OK;
}

err_t barometer9_default_cfg ( barometer9_t *ctx ) 
{
    err_t error_flag = BAROMETER9_OK;
    uint8_t cfg_data = 0;
    
    error_flag |= barometer9_sw_reset( ctx ); 

    error_flag |= barometer9_generic_read( ctx, BAROMETER9_MODE_CFG, &cfg_data, 1 );
    cfg_data |= BAROMETER9_AVERAGE_MODE | BAROMETER9_MEASURMENT_MODE | BAROMETER9_READ_PRES_AND_TEMP;
    error_flag |= barometer9_generic_write( ctx, BAROMETER9_MODE_CFG, &cfg_data, 1 );

    return error_flag;
}

err_t barometer9_generic_write ( barometer9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t barometer9_generic_read ( barometer9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}


err_t barometer9_read_part_id ( barometer9_t *ctx, uint16_t *part_id )
{
    err_t error_flag = BAROMETER9_OK;
    uint8_t tmp_data[ 2 ] = { 0 };

    error_flag |= barometer9_generic_read( ctx, BAROMETER9_REG_PART_ID0, tmp_data, 2 );

    *part_id = ( ( uint16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ];

    return error_flag;
}

err_t barometer9_get_temperature ( barometer9_t *ctx, float *temperature )
{
    err_t error_flag = BAROMETER9_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    uint16_t raw_temp = 0;

    error_flag |= barometer9_generic_read( ctx, BAROMETER9_TEMP_OUT_L, tmp_data, 2 );
    raw_temp = ( ( uint16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ];

    *temperature = ( ( float ) raw_temp / BAROMETER9_TEMPERATURE_CON_CONST ) - BAROMETER9_K_TO_C_CON_CONST;

    return error_flag;
}

err_t barometer9_get_pressure ( barometer9_t *ctx, float *pressure )
{
    err_t error_flag = BAROMETER9_OK;
    uint8_t tmp_data[ 3 ] = { 0 };
    uint32_t raw_press = 0;

    error_flag |= barometer9_generic_read( ctx, BAROMETER9_PRESS_OUT_XL, tmp_data, 3 );
    raw_press =  ( ( uint32_t ) tmp_data[ 2 ] << 16 ) | ( ( uint32_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ];

    *pressure = ( ( float ) raw_press / BAROMETER9_PRESSURE_CON_CONST );

    return error_flag;
}

err_t barometer9_sw_reset ( barometer9_t *ctx )
{
    err_t error_flag = BAROMETER9_OK;
    uint8_t tmp_data = 0;

    tmp_data = BAROMETER9_SW_RESET;
    error_flag |= barometer9_generic_write( ctx, BAROMETER9_MODE_CFG, &tmp_data, 1 );
    Delay_10ms( );

    tmp_data = BAROMETER9_HIGH_POWER_MODE;
    error_flag |= barometer9_generic_write( ctx, BAROMETER9_MODE_CFG, &tmp_data, 1 );
    Delay_10ms( );

    return error_flag;
}

static err_t barometer9_i2c_write ( barometer9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t barometer9_i2c_read ( barometer9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t barometer9_spi_write ( barometer9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t reg_adr = reg << 2;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_adr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t barometer9_spi_read ( barometer9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg << 2 | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
