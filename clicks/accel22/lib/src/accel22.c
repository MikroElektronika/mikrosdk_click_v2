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
 * @file accel22.c
 * @brief Accel 22 Click Driver.
 */

#include "accel22.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Accel 22 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel22_i2c_write ( accel22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 22 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel22_i2c_read ( accel22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 22 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel22_spi_write ( accel22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 22 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel22_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel22_spi_read ( accel22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel22_cfg_setup ( accel22_cfg_t *cfg ) 
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
    cfg->i2c_address = ACCEL22_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL22_DRV_SEL_SPI;
}

void accel22_drv_interface_selection ( accel22_cfg_t *cfg, accel22_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel22_init ( accel22_t *ctx, accel22_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL22_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel22_i2c_read;
        ctx->write_f = accel22_i2c_write;
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

        ctx->read_f  = accel22_spi_read;
        ctx->write_f = accel22_spi_write;
    }

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return ACCEL22_OK;
}

err_t accel22_default_cfg ( accel22_t *ctx ) 
{
    err_t error_flag = ACCEL22_OK;
    
    error_flag |= accel22_write_register ( ctx, ACCEL22_REG_SOFT_RESET, ACCEL22_SOFT_RESET );
    Delay_100ms ( );
    
    if ( ACCEL22_ERROR == accel22_check_communication ( ctx ) )
    {
        return ACCEL22_ERROR;
    }
    error_flag |= accel22_write_register ( ctx, ACCEL22_REG_INTMAP1_LOWER, ACCEL22_INTMAP1_LOWER_DATA_RDY );
    error_flag |= accel22_set_filter_config ( ctx, ACCEL22_2G, ACCEL22_400HZ );
    error_flag |= accel22_write_register ( ctx, ACCEL22_REG_POWER_CTL, ACCEL22_POWER_CTL_MEASUREMENT_MODE );
    Delay_100ms ( );
    
    ctx->room_temp_offset = 0;
    error_flag |= accel22_calibrate_temperature ( ctx, ACCEL22_ROOM_TEMPERATURE );
    Delay_100ms ( );
    
    return error_flag;
}

err_t accel22_generic_write ( accel22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel22_generic_read ( accel22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel22_write_register ( accel22_t *ctx, uint8_t reg, uint8_t data_in )
{
    return accel22_generic_write( ctx, reg, &data_in, 1 );
}

err_t accel22_read_register ( accel22_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return accel22_generic_read( ctx, reg, data_out, 1 );
}

err_t accel22_check_communication ( accel22_t *ctx )
{
    uint8_t data_buf[ 3 ];
    if ( ACCEL22_OK == accel22_generic_read ( ctx, ACCEL22_REG_DEVID_AD, data_buf, 3 ) )
    {
        if ( ( ACCEL22_ADI_DEVICE_ID == data_buf[ 0 ] ) && 
             ( ACCEL22_MEMS_DEVICE_ID == data_buf[ 1 ] ) && 
             ( ACCEL22_PART_ID == data_buf[ 2 ] ) )
        {
            return ACCEL22_OK;
        }
    }
    return ACCEL22_ERROR;
}

uint8_t accel22_get_int1_pin ( accel22_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

uint8_t accel22_get_int2_pin ( accel22_t *ctx )
{
    return digital_in_read ( &ctx->int2 );
}

err_t accel22_set_filter_config ( accel22_t *ctx, accel22_range_t range, accel22_odr_t odr )
{
    if ( ACCEL22_8G == range )
    {
        ctx->resolution = ACCEL22_ACCEL_8G_RES;
    }
    else if ( ACCEL22_4G == range )
    {
        ctx->resolution = ACCEL22_ACCEL_4G_RES;
    }
    else
    {
        ctx->resolution = ACCEL22_ACCEL_2G_RES;
    }
    uint8_t reg_data;
    err_t error_flag = accel22_read_register ( ctx, ACCEL22_REG_FILTER_CTL, &reg_data );
    reg_data &= ~ACCEL22_RANGE_BIT_MASK;
    reg_data |= ( range << 6 );
    reg_data &= ~ACCEL22_ODR_BIT_MASK;
    reg_data |= odr;
    error_flag |= accel22_write_register ( ctx, ACCEL22_REG_FILTER_CTL, reg_data );
    return error_flag;
}

err_t accel22_get_axes ( accel22_t *ctx, accel22_axes_t *axes )
{
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    err_t error_flag = accel22_generic_read ( ctx, ACCEL22_REG_XDATA_H, data_buf, 6 );
    raw_data = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    axes->x = ( raw_data >> 2 ) * ctx->resolution;
    raw_data = ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
    axes->y = ( raw_data >> 2 ) * ctx->resolution;
    raw_data = ( ( int16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
    axes->z = ( raw_data >> 2 ) * ctx->resolution;
    return error_flag;
}

err_t accel22_enable_temperature_measurement ( accel22_t *ctx )
{
    uint8_t reg_data;
    err_t error_flag = accel22_read_register ( ctx, ACCEL22_REG_ADC_CTL, &reg_data );
    error_flag |= accel22_write_register ( ctx, ACCEL22_REG_ADC_CTL, reg_data & ( ~ACCEL22_ENABLE_ADC ) );
    error_flag |= accel22_read_register ( ctx, ACCEL22_REG_TEMP_CTL, &reg_data );
    error_flag |= accel22_write_register ( ctx, ACCEL22_REG_TEMP_CTL, reg_data | ACCEL22_ENABLE_TEMPERATURE );
    return error_flag;
}

err_t accel22_enable_adc_measurement ( accel22_t *ctx )
{
    uint8_t reg_data;
    err_t error_flag = accel22_read_register ( ctx, ACCEL22_REG_TEMP_CTL, &reg_data );
    error_flag |= accel22_write_register ( ctx, ACCEL22_REG_TEMP_CTL, reg_data & ( ~ACCEL22_ENABLE_TEMPERATURE ) );
    error_flag = accel22_read_register ( ctx, ACCEL22_REG_ADC_CTL, &reg_data );
    error_flag |= accel22_write_register ( ctx, ACCEL22_REG_ADC_CTL, reg_data | ACCEL22_ENABLE_ADC );
    return error_flag;
}

err_t accel22_calibrate_temperature ( accel22_t *ctx, float room_temperature )
{
    err_t error_flag = accel22_enable_temperature_measurement ( ctx );
    float temp_avg = 0;
    for ( uint8_t cnt = 0; cnt < ACCEL22_TEMPERATURE_CAL_SAMPLE_NUM; cnt++ )
    {
        // Wait for data ready indication
        while ( !accel22_get_int1_pin ( ctx ) ); 
        float temp = 0;
        error_flag |= accel22_get_temperature ( ctx, &temp );
        temp_avg += temp;
    }
    ctx->room_temp_offset = ( temp_avg / ACCEL22_TEMPERATURE_CAL_SAMPLE_NUM ) - room_temperature;
    return error_flag;
}

err_t accel22_get_temperature ( accel22_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    err_t error_flag = accel22_generic_read ( ctx, ACCEL22_REG_TEMP_H, data_buf, 2 );
    raw_data = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    *temperature = ACCEL22_ROOM_TEMPERATURE + 
                  ( ( raw_data >> 2 ) - ACCEL22_TEMPERATURE_BIAS ) / ACCEL22_TEMPERATURE_RES - 
                  ctx->room_temp_offset;
    return error_flag;
}

err_t accel22_get_adc ( accel22_t *ctx, float *v_adc )
{
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    err_t error_flag = accel22_generic_read ( ctx, ACCEL22_REG_EX_ADC_H, data_buf, 2 );
    raw_data = ( ( int16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    *v_adc = ( float ) ( ( raw_data >> 2 ) + ACCEL22_ADC_OFFSET ) / ACCEL22_ADC_RES * ACCEL22_ADC_VREG;
    return error_flag;
}

static err_t accel22_i2c_write ( accel22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 257 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t accel22_i2c_read ( accel22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel22_spi_write ( accel22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 258 ] = { 0 };
    tx_buf[ 0 ] = ACCEL22_SPI_WRITE_REG;
    tx_buf[ 1 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        tx_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel22_spi_read ( accel22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t tx_buf[ 2 ] = { 0 };
    tx_buf[ 0 ] = ACCEL22_SPI_READ_REG;
    tx_buf[ 1 ] = reg;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
