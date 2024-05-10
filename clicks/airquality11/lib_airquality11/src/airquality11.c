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
 * @file airquality11.c
 * @brief Air Quality 11 Click Driver.
 */

#include "airquality11.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x01

/**
 * @brief Air Quality 11 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airquality11_i2c_write ( airquality11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Quality 11 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airquality11_i2c_read ( airquality11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Air Quality 11 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airquality11_spi_write ( airquality11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Air Quality 11 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t airquality11_spi_read ( airquality11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void airquality11_cfg_setup ( airquality11_cfg_t *cfg ) 
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
    cfg->i2c_address = AIRQUALITY11_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = AIRQUALITY11_DRV_SEL_I2C;
}

void airquality11_drv_interface_sel ( airquality11_cfg_t *cfg, airquality11_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t airquality11_init ( airquality11_t *ctx, airquality11_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    digital_out_init( &ctx->en, cfg->en );
    digital_out_high( &ctx->en );
    Delay_100ms( );

    if ( AIRQUALITY11_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = airquality11_i2c_read;
        ctx->write_f = airquality11_i2c_write;
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

        ctx->read_f  = airquality11_spi_read;
        ctx->write_f = airquality11_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    ctx->temperature = 25.0;
    ctx->humidity = 50.0;

    return AIRQUALITY11_OK;
}

err_t airquality11_default_cfg ( airquality11_t *ctx ) 
{
    uint16_t device_id = DUMMY;
    err_t err_flag = airquality11_get_device_id( ctx, &device_id );
    if ( AIRQUALITY11_PART_ID == device_id )
    {
        err_flag |= airquality11_set_op_mode( ctx, AIRQUALITY11_RESET );
        Delay_100ms( );

        err_flag |= airquality11_set_op_mode( ctx, AIRQUALITY11_IDLE );
        Delay_10ms( );

        err_flag |= airquality11_set_measure_c( ctx, ctx->temperature, ctx->humidity );
        Delay_10ms( );

        err_flag |= airquality11_set_op_mode( ctx, AIRQUALITY11_STANDARD );
        Delay_10ms( );
    }
    else
    {
        err_flag = AIRQUALITY11_ERROR;
    }
    return err_flag;
}

err_t airquality11_generic_write ( airquality11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t airquality11_generic_read ( airquality11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t airquality11_write_word ( airquality11_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf = DUMMY;
    data_buf = ( uint8_t ) data_in;
    err_t err_flag = airquality11_generic_write( ctx, reg, &data_buf, 1 );
    data_buf = ( uint8_t ) ( data_in >> 8 );
    err_flag |= airquality11_generic_write( ctx, ++reg, &data_buf, 1 );
    return err_flag;
}

err_t airquality11_read_word ( airquality11_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = airquality11_generic_read( ctx, reg, data_buf, 2 );
    *data_out = data_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 0 ];
    return err_flag;
}

err_t airquality11_get_device_id ( airquality11_t *ctx, uint16_t *device_id ) 
{
    return airquality11_read_word( ctx, AIRQUALITY11_REG_PART_ID, device_id );
}

err_t airquality11_set_op_mode ( airquality11_t *ctx, airquality11_op_mode_t op_mode ) 
{
    uint8_t data_buf = op_mode;
    return airquality11_generic_write( ctx, AIRQUALITY11_REG_OPMODE, &data_buf, 1 );
}

err_t airquality11_set_int_config ( airquality11_t *ctx, uint8_t int_cfg ) 
{
    return airquality11_generic_write( ctx, AIRQUALITY11_REG_CONFIG, &int_cfg, 1 );
}

err_t airquality11_set_cmd ( airquality11_t *ctx, airquality11_cmd_t cmd ) 
{
    uint8_t data_buf = cmd;
    return airquality11_generic_write( ctx, AIRQUALITY11_REG_COMMAND, &data_buf, 1 );
}

err_t airquality11_set_measure_c ( airquality11_t *ctx, float temperature, float humidity ) 
{
    err_t err_flag = AIRQUALITY11_OK;
    if ( ( AIRQUALITY11_TEMP_MAX < temperature ) || ( AIRQUALITY11_TEMP_MIN > temperature ) ||
         ( AIRQUALITY11_HUM_MAX < humidity ) || ( AIRQUALITY11_HUM_MIN > humidity ) )
    {
        err_flag = AIRQUALITY11_ERROR;
    }
    else
    {
        temperature += AIRQUALITY11_TEMP_CALC_KC;
        temperature *= AIRQUALITY11_TEMP_CALC_MLT;
        err_flag |= airquality11_write_word( ctx, AIRQUALITY11_REG_TEMP_IN, ( uint16_t ) temperature );

        humidity *= AIRQUALITY11_HUM_CALC_MLT;
        err_flag |= airquality11_write_word( ctx, AIRQUALITY11_REG_RH_IN, ( uint16_t ) humidity );
    }
    return err_flag;
}

err_t airquality11_get_status ( airquality11_t *ctx, uint8_t *status ) 
{
    return airquality11_generic_read( ctx, AIRQUALITY11_REG_DEVICE_STATUS, status, 1 );
}

err_t airquality11_get_aqi_uba ( airquality11_t *ctx, uint8_t *aqi_uba ) 
{
    err_t err_flag = airquality11_generic_read( ctx, AIRQUALITY11_REG_DATA_AQI_UBA, aqi_uba, 1 );
    *aqi_uba &= AIRQUALITY11_AQI_UBA_BITMASK;
    return err_flag;
}

err_t airquality11_get_tvoc ( airquality11_t *ctx, uint16_t *tvoc_ppb ) 
{
    return airquality11_read_word( ctx, AIRQUALITY11_REG_DATA_ETVOC, tvoc_ppb );
}

err_t airquality11_get_co2 ( airquality11_t *ctx, uint16_t *co2_ppm ) 
{
    return airquality11_read_word( ctx, AIRQUALITY11_REG_DATA_ECO2, co2_ppm );
}

err_t airquality11_get_aqi_s ( airquality11_t *ctx, uint16_t *aqi_s ) 
{
    return airquality11_read_word( ctx, AIRQUALITY11_REG_DATA_AQI_S, aqi_s );
}

err_t airquality11_get_measure_c ( airquality11_t *ctx, float *temperature, float *humidity ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = airquality11_read_word( ctx, AIRQUALITY11_REG_DATA_T, &data_buf );
    *temperature = ( float ) data_buf;
    *temperature /= AIRQUALITY11_TEMP_CALC_MLT;
    *temperature -= AIRQUALITY11_TEMP_CALC_KC;

    err_flag |= airquality11_read_word( ctx, AIRQUALITY11_REG_DATA_RH, &data_buf );
    *humidity = ( float ) data_buf;
    *humidity /= AIRQUALITY11_HUM_CALC_MLT;
    return err_flag;
}

err_t airquality11_write_gpr_reg ( airquality11_t *ctx, uint8_t *data_in ) 
{
    err_t err_flag = AIRQUALITY11_OK;
    for ( uint8_t n_cnt = 0; n_cnt < 8; n_cnt++ )
    {
        err_flag |= airquality11_generic_write( ctx, AIRQUALITY11_REG_GPR_WRITE + n_cnt, &( data_in[ 0 ] ), 1 );
    }
    return err_flag;
}

err_t airquality11_read_gpr_reg ( airquality11_t *ctx, uint8_t *data_out ) 
{
    return airquality11_generic_read( ctx, AIRQUALITY11_REG_GPR_READ, data_out, 8 );
}

uint8_t airquality11_get_interrupt ( airquality11_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

static err_t airquality11_i2c_write ( airquality11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t airquality11_i2c_read ( airquality11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t airquality11_spi_write ( airquality11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    reg <<= 1;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t airquality11_spi_read ( airquality11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = ( reg << 1 ) | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
