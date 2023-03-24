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
 * @file pressure18.c
 * @brief Pressure 18 Click Driver.
 */

#include "pressure18.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Pressure 18 concat bytes macro.
 * @details Specified macro to combine two 8 bit data's to form a 16 bit data.
 */
#define PRESSURE18_CONCAT_BYTES( msb, lsb )     ( ( ( uint16_t ) msb << 8 ) | lsb )

/**
 * @brief Pressure 18 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure18_i2c_write ( pressure18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 18 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure18_i2c_read ( pressure18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 18 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure18_spi_write ( pressure18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 18 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure18_spi_read ( pressure18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 18 get calib coefficients function.
 * @details This function reads the calibration data from the sensor, parse it then compensates it 
 * and store in the device structure.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure18_get_calib_coefficients ( pressure18_t *ctx );

/**
 * @brief Pressure 18 compensate temperature function.
 * @details This function is used to compensate the raw temperature data and return the compensated
 * temperature data in Celsius.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] raw_temp : 24-bit raw temperature data.
 * @return Compensated temperature in Celsius.
 * @note None.
 */
static float pressure18_compensate_temperature ( pressure18_t *ctx, uint32_t raw_temp );

/**
 * @brief Pressure 18 compensate pressure function.
 * @details This function is used to compensate the raw pressure data and return the compensated
 * pressure data in Pascals.
 * @param[in] ctx : Click context object.
 * See #pressure18_t object definition for detailed explanation.
 * @param[in] raw_temp : 24-bit raw pressure data.
 * @return Compensated pressure in Pascals.
 * @note This function relies on the @b pressure18_compensate_temperature funtion.
 */
static float pressure18_compensate_pressure ( pressure18_t *ctx, uint32_t raw_press );

void pressure18_cfg_setup ( pressure18_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE18_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = PRESSURE18_DRV_SEL_I2C;
}

void pressure18_drv_interface_selection ( pressure18_cfg_t *cfg, pressure18_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t pressure18_init ( pressure18_t *ctx, pressure18_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( PRESSURE18_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = pressure18_i2c_read;
        ctx->write_f = pressure18_i2c_write;
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

        ctx->read_f  = pressure18_spi_read;
        ctx->write_f = pressure18_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PRESSURE18_OK;
}

err_t pressure18_default_cfg ( pressure18_t *ctx ) 
{
    err_t error_flag = PRESSURE18_OK;
    if ( PRESSURE18_ERROR == pressure18_check_communication ( ctx ) )
    {
        return PRESSURE18_ERROR;
    }
    error_flag |= pressure18_soft_reset ( ctx );
    error_flag |= pressure18_get_calib_coefficients ( ctx );
    error_flag |= pressure18_write_register ( ctx, PRESSURE18_REG_OSR, PRESSURE18_OSR_T_X1 | PRESSURE18_OSR_P_X4 );
    error_flag |= pressure18_write_register ( ctx, PRESSURE18_REG_ODR, PRESSURE18_ODR_320_MS );
    error_flag |= pressure18_write_register ( ctx, PRESSURE18_REG_INT_CTRL, PRESSURE18_INT_CTRL_DRDY_ENABLED | 
                                                                            PRESSURE18_INT_CTRL_LEVEL_ACTIVE_HIGH | 
                                                                            PRESSURE18_INT_CTRL_OD_PUSH_PULL );
    error_flag |= pressure18_write_register ( ctx, PRESSURE18_REG_PWR_CTRL, PRESSURE18_PWR_CTRL_MODE_NORMAL | 
                                                                            PRESSURE18_PWR_CTRL_PRESS_EN | 
                                                                            PRESSURE18_PWR_CTRL_TEMP_EN );
    return error_flag;
}

err_t pressure18_generic_write ( pressure18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t pressure18_generic_read ( pressure18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t pressure18_write_register ( pressure18_t *ctx, uint8_t reg, uint8_t data_in )
{
    return pressure18_generic_write ( ctx, reg, &data_in, 1 );
}

err_t pressure18_read_register ( pressure18_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return pressure18_generic_read ( ctx, reg, data_out, 1 );
}

err_t pressure18_check_communication ( pressure18_t *ctx )
{
    uint8_t chip_id;
    if ( PRESSURE18_OK == pressure18_read_register ( ctx, PRESSURE18_REG_CHIP_ID, &chip_id ) )
    {
        if ( PRESSURE18_CHIP_ID == chip_id )
        {
            return PRESSURE18_OK;
        }
    }
    return PRESSURE18_ERROR;
}

uint8_t pressure18_get_int_pin ( pressure18_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t pressure18_soft_reset ( pressure18_t *ctx )
{
    uint8_t status;
    if ( ( PRESSURE18_OK == pressure18_read_register ( ctx, PRESSURE18_REG_STATUS, &status ) ) &&
         ( status & PRESSURE18_STATUS_CMD_RDY ) )
    {
        if ( PRESSURE18_OK == pressure18_write_register ( ctx, PRESSURE18_REG_CMD, PRESSURE18_CMD_SOFT_RESET ) )
        {
            Delay_5ms ( );
            if ( ( PRESSURE18_OK == pressure18_read_register ( ctx, PRESSURE18_REG_ERR, &status ) ) &&
                 ( PRESSURE18_ERR_CMD != ( status & PRESSURE18_ERR_CMD ) ) )
            {
                return PRESSURE18_OK;
            }
        }
    }
    return PRESSURE18_ERROR;
}

err_t pressure18_read_data ( pressure18_t *ctx, float *pressure, float *temperature )
{
    uint8_t data_buf[ 7 ] = { 0 };
    if ( ( PRESSURE18_OK == pressure18_generic_read ( ctx, PRESSURE18_REG_STATUS, data_buf, 7 ) ) && 
         ( ( data_buf[ 0 ] & PRESSURE18_STATUS_DRDY_PRESS ) && ( data_buf[ 0 ] & PRESSURE18_STATUS_DRDY_TEMP ) ) )
    {
        uint32_t raw_pressure = ( ( uint32_t ) data_buf[ 3 ] << 16 ) | ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 1 ];
        uint32_t raw_temperature = ( ( uint32_t ) data_buf[ 6 ] << 16 ) | ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ];
        *temperature = pressure18_compensate_temperature ( ctx, raw_temperature );
        *pressure = pressure18_compensate_pressure ( ctx, raw_pressure );
        return PRESSURE18_OK;
    }
    return PRESSURE18_ERROR;
}

static err_t pressure18_i2c_write ( pressure18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 64 ] = { 0 };
    if ( len > 32 )
    {
        return PRESSURE18_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt * 2 ] = reg + cnt;
        data_buf[ cnt * 2 + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t pressure18_i2c_read ( pressure18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t pressure18_spi_write ( pressure18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 64 ] = { 0 };
    if ( len > 32 )
    {
        return PRESSURE18_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt * 2 ] = reg + cnt;
        data_buf[ cnt * 2 + 1 ] = data_in[ cnt ];
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t pressure18_spi_read ( pressure18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg | SPI_READ_MASK;
    data_buf[ 1 ] = DUMMY;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_buf, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t pressure18_get_calib_coefficients ( pressure18_t *ctx )
{
    uint8_t data_buf[ 21 ] = { 0 };
    if ( PRESSURE18_OK == pressure18_generic_read ( ctx, PRESSURE18_REG_CALIB_DATA, data_buf, 21 ) )
    {
        ctx->calib_coef.par_t1 = PRESSURE18_CONCAT_BYTES ( data_buf[ 1 ], data_buf[ 0 ] ) / pow ( 2.0, -8.0 );
        ctx->calib_coef.par_t2 = PRESSURE18_CONCAT_BYTES ( data_buf[ 3 ], data_buf[ 2 ] ) / pow ( 2.0, 30.0 );
        ctx->calib_coef.par_t3 = ( ( int8_t ) data_buf[ 4 ] ) / pow ( 2.0, 48.0 );
        ctx->calib_coef.par_p1 = ( ( ( int16_t ) PRESSURE18_CONCAT_BYTES ( data_buf[ 6 ], data_buf[ 5 ] ) ) - pow ( 2.0, 14.0 ) ) / 
                                  pow ( 2.0, 20.0 );
        ctx->calib_coef.par_p2 = ( ( ( int16_t ) PRESSURE18_CONCAT_BYTES ( data_buf[ 8 ], data_buf[ 7 ] ) ) - pow ( 2.0, 14.0 ) ) / 
                                  pow ( 2.0, 29.0 );
        ctx->calib_coef.par_p3 = ( ( int8_t ) data_buf[ 9 ] ) / pow ( 2.0, 32.0 );
        ctx->calib_coef.par_p4 = ( ( int8_t ) data_buf[ 10 ] ) / pow ( 2.0, 37.0 );
        ctx->calib_coef.par_p5 = PRESSURE18_CONCAT_BYTES ( data_buf[ 12 ], data_buf[ 11 ] ) / pow ( 2.0, -3.0 );
        ctx->calib_coef.par_p6 = PRESSURE18_CONCAT_BYTES ( data_buf[ 14 ], data_buf[ 13 ] ) / pow ( 2.0, 6.0 );
        ctx->calib_coef.par_p7 = ( ( int8_t ) data_buf[ 15 ] ) / pow ( 2.0, 8.0 );
        ctx->calib_coef.par_p8 = ( ( int8_t ) data_buf[ 16 ] ) / pow ( 2.0, 15.0 );
        ctx->calib_coef.par_p9 = ( ( int16_t ) PRESSURE18_CONCAT_BYTES ( data_buf[ 18 ], data_buf[ 17 ] ) ) / pow ( 2.0, 48.0 );
        ctx->calib_coef.par_p10 = ( ( int8_t ) data_buf[ 19 ] ) / pow ( 2.0, 48.0 );
        ctx->calib_coef.par_p11 = ( ( int8_t ) data_buf[ 20 ] ) / pow ( 2.0, 65.0 );
        return PRESSURE18_OK;
    }
    return PRESSURE18_ERROR;
}

static float pressure18_compensate_temperature ( pressure18_t *ctx, uint32_t raw_temp )
{
    float partial_data1;
    float partial_data2;
    partial_data1 = ( float ) raw_temp - ctx->calib_coef.par_t1;
    partial_data2 = partial_data1 * ctx->calib_coef.par_t2;
    /* Update the compensated temperature in calib structure since this is
     * needed for pressure calculation */
    ctx->calib_coef.t_lin = partial_data2 + pow ( partial_data1, 2.0 ) * ctx->calib_coef.par_t3;
    return ctx->calib_coef.t_lin;
}

static float pressure18_compensate_pressure ( pressure18_t *ctx, uint32_t raw_press )
{
    float partial_data1;
    float partial_data2;
    float partial_data3;
    float partial_out1;
    float partial_out2;
    partial_data1 = ctx->calib_coef.par_p6 * ctx->calib_coef.t_lin;
    partial_data2 = ctx->calib_coef.par_p7 * pow ( ctx->calib_coef.t_lin, 2.0 );
    partial_data3 = ctx->calib_coef.par_p8 * pow ( ctx->calib_coef.t_lin, 3.0 );
    partial_out1 = ctx->calib_coef.par_p5 + partial_data1 + partial_data2 + partial_data3;

    partial_data1 = ctx->calib_coef.par_p2 * ctx->calib_coef.t_lin;
    partial_data2 = ctx->calib_coef.par_p3 * pow ( ctx->calib_coef.t_lin, 2.0 );
    partial_data3 = ctx->calib_coef.par_p4 * pow ( ctx->calib_coef.t_lin, 3.0 );
    partial_out2 = ( float ) raw_press * ( ctx->calib_coef.par_p1 + partial_data1 + partial_data2 + partial_data3 );

    partial_data1 = pow ( ( float ) raw_press, 2.0 );
    partial_data2 = ctx->calib_coef.par_p9 + ctx->calib_coef.par_p10 * ctx->calib_coef.t_lin;
    partial_data3 = partial_data1 * partial_data2 + pow ( ( float ) raw_press, 3.0 ) * ctx->calib_coef.par_p11;
    return ( partial_out1 + partial_out2 + partial_data3 );
}

// ------------------------------------------------------------------------ END
