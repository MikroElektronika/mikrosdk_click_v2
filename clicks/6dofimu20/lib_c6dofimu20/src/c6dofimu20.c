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
 * @file c6dofimu20.c
 * @brief 6DOF IMU 20 Click Driver.
 */

#include "c6dofimu20.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief 6DOF IMU 20 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu20_i2c_write ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 20 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu20_i2c_read ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 20 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu20_spi_write ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 20 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu20_spi_read ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void c6dofimu20_cfg_setup ( c6dofimu20_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->it1  = HAL_PIN_NC;
    cfg->it2  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C6DOFIMU20_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = C6DOFIMU20_DRV_SEL_I2C;
}

void c6dofimu20_drv_interface_selection ( c6dofimu20_cfg_t *cfg, c6dofimu20_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t c6dofimu20_init ( c6dofimu20_t *ctx, c6dofimu20_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    


    if ( C6DOFIMU20_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );
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

        ctx->read_f  = c6dofimu20_i2c_read;
        ctx->write_f = c6dofimu20_i2c_write;
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

        ctx->read_f  = c6dofimu20_spi_read;
        ctx->write_f = c6dofimu20_spi_write;
    }

    digital_in_init( &ctx->it1, cfg->it1 );
    digital_in_init( &ctx->it2, cfg->it2 );

    
    return C6DOFIMU20_OK;
}

err_t c6dofimu20_default_cfg ( c6dofimu20_t *ctx ) 
{
    err_t error_flag = C6DOFIMU20_OK;
    
    c6dofimu20_sw_reset( ctx );
       
    c6dofimu20_set_reg( ctx, C6DOFIMU20_REG_ACC_CONF, C6DOFIMU20_ACC_CONF_ODR_100_Hz | 
                                                      C6DOFIMU20_ACC_CONF_ACC_RANGE_16G |
                                                      C6DOFIMU20_ACC_CONF_ACC_BW_DIV_4 | 
                                                      C6DOFIMU20_ACC_CONF_ACC_AVG_NUM_64 | 
                                                      C6DOFIMU20_ACC_CONF_ACC_MODE_CONSTANT_OPERATION);

    c6dofimu20_set_reg( ctx, C6DOFIMU20_REG_GYR_CONF, C6DOFIMU20_GYR_CONF_ODR_100_Hz | 
                                                      C6DOFIMU20_GYR_CONF_GYR_RANGE_8G |
                                                      C6DOFIMU20_GYR_CONF_GYR_BW_DIV_2 | 
                                                      C6DOFIMU20_GYR_CONF_GYR_AVG_NUM_64 | 
                                                      C6DOFIMU20_GYR_CONF_GYR_MODE_CONSTANT_OPERATION);
    
    return error_flag;
}

err_t c6dofimu20_generic_write ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t c6dofimu20_generic_read ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t c6dofimu20_set_reg ( c6dofimu20_t *ctx, uint8_t reg, uint16_t data_in )
{
    err_t error_flag = C6DOFIMU20_OK;
    uint8_t tx_data[ 2 ] = { 0 };
    
    tx_data[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    tx_data[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    
    error_flag |= c6dofimu20_generic_write( ctx, reg, tx_data, 2 );
    
    return error_flag;
}

err_t c6dofimu20_get_reg ( c6dofimu20_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = C6DOFIMU20_OK;
    uint16_t tmp_data = 0;
    uint8_t rx_data[ 3 ] = { 0 };
    
    error_flag |= c6dofimu20_generic_read( ctx, reg, rx_data, 3 );
    
    tmp_data = rx_data[ 2 ];
    tmp_data <<= 8;
    tmp_data |= rx_data[ 1 ];
    
    *data_out = tmp_data;
    
    return error_flag;
}

err_t c6dofimu20_get_id ( c6dofimu20_t *ctx, uint8_t *chip_id )
{
    err_t error_flag = C6DOFIMU20_OK;
    uint16_t tmp_data = 0;
    
    error_flag = c6dofimu20_get_reg( ctx, C6DOFIMU20_REG_CHIP_ID, &tmp_data );
    
    *chip_id = ( ( uint8_t ) tmp_data & 0xFF );
    
    return error_flag;
}

uint8_t c6dofimu20_get_int1_state ( c6dofimu20_t *ctx )
{
    return digital_in_read( &ctx->it1 );
}

uint8_t c6dofimu20_get_int2_state ( c6dofimu20_t *ctx )
{
    return digital_in_read( &ctx->it2 );
}

err_t c6dofimu20_get_acc_data ( c6dofimu20_t *ctx, c6dofimu20_data_t *acc_data )
{
    err_t error_flag = C6DOFIMU20_OK;
    uint16_t tmp_data;
    
    error_flag |= c6dofimu20_get_reg( ctx, C6DOFIMU20_REG_ACC_DATA_X, &tmp_data );
    acc_data->data_x = ( int16_t ) tmp_data;
    error_flag |= c6dofimu20_get_reg( ctx, C6DOFIMU20_REG_ACC_DATA_Y, &tmp_data );
    acc_data->data_y = ( int16_t ) tmp_data;
    error_flag |= c6dofimu20_get_reg( ctx, C6DOFIMU20_REG_ACC_DATA_Z, &tmp_data );
    acc_data->data_z = ( int16_t ) tmp_data;
    
    return error_flag;
}

err_t c6dofimu20_get_gyr_data ( c6dofimu20_t *ctx, c6dofimu20_data_t *gyr_data )
{
    err_t error_flag = C6DOFIMU20_OK;
    uint16_t tmp_data;
    
    error_flag |= c6dofimu20_get_reg( ctx, C6DOFIMU20_REG_GYR_DATA_X, &tmp_data );
    gyr_data->data_x = ( int16_t ) tmp_data;
    error_flag |= c6dofimu20_get_reg( ctx, C6DOFIMU20_REG_GYR_DATA_Y, &tmp_data );
    gyr_data->data_y = ( int16_t ) tmp_data;
    error_flag |= c6dofimu20_get_reg( ctx, C6DOFIMU20_REG_GYR_DATA_Z, &tmp_data );
    gyr_data->data_z = ( int16_t ) tmp_data;
    
    return error_flag;
}

err_t c6dofimu20_get_temperature ( c6dofimu20_t *ctx, float *temp_data )
{
    err_t error_flag = C6DOFIMU20_OK;
    uint16_t tmp_data = 0;
    
    error_flag |= c6dofimu20_get_reg( ctx, C6DOFIMU20_REG_TEMP_DATA, &tmp_data );
    
    *temp_data = ( ( float ) tmp_data / C6DOFIMU20_TEMP_CALC_DIVIDER ) + C6DOFIMU20_TEMP_CALC_VALUE;
    
    return error_flag;
}

err_t c6dofimu20_sw_reset ( c6dofimu20_t *ctx )
{
    err_t error_flag = C6DOFIMU20_OK;
    
    error_flag |= c6dofimu20_set_reg( ctx, C6DOFIMU20_REG_CMD, C6DOFIMU20_SW_RESET_CMD );
    Delay_100ms( );
    
    return error_flag;  
}

static err_t c6dofimu20_i2c_write ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t c6dofimu20_i2c_read ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t rx_buf[ 256 ] = { 0 };
    i2c_master_write( &ctx->i2c, &reg, 1 );
    i2c_master_read( &ctx->i2c, rx_buf, len + 1 );
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_out[ cnt ] = rx_buf[ cnt + 1 ];
    }
    return 0;
}

static err_t c6dofimu20_spi_write ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t c6dofimu20_spi_read ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t tx_data;
    tx_data = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &tx_data, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
