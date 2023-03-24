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
 * @file c6dofimu14.c
 * @brief 6DOF IMU 14 Click Driver.
 */

#include "c6dofimu14.h"

/**
 * @brief Timeout value.
 * @details Definition of timeout value for jumping out of infinite loops.
 */
#define TIMEOUT     10000

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY       0x00

/**
 * @brief 6DOF IMU 14 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu14_i2c_write ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 14 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu14_i2c_read ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 14 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu14_spi_write ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 14 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu14_spi_read ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 14 check data ready function.
 * @details This function checks if the desired flag is set in the status register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @param[in] flag : Bit flag from the status register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu14_check_data_ready ( c6dofimu14_t *ctx, uint8_t flag );

void c6dofimu14_cfg_setup ( c6dofimu14_cfg_t *cfg ) 
{
    cfg->scl         = HAL_PIN_NC;
    cfg->sda         = HAL_PIN_NC;
    cfg->sck         = HAL_PIN_NC;
    cfg->miso        = HAL_PIN_NC;
    cfg->mosi        = HAL_PIN_NC;
    cfg->cs          = HAL_PIN_NC;
    cfg->snc         = HAL_PIN_NC;
    cfg->int_pin     = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C6DOFIMU14_SET_DEV_ADDR_GND;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel     = C6DOFIMU14_DRV_SEL_SPI;
}

void c6dofimu14_drv_interface_selection ( c6dofimu14_cfg_t *cfg, c6dofimu14_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t c6dofimu14_init ( c6dofimu14_t *ctx, c6dofimu14_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ctx->drv_sel == C6DOFIMU14_DRV_SEL_I2C ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;
        
        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );
        
        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
        {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = c6dofimu14_i2c_read;
        ctx->write_f = c6dofimu14_i2c_write;
    } 
    else 
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
        {
            return SPI_MASTER_ERROR;
        }

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );

        ctx->read_f  = c6dofimu14_spi_read;
        ctx->write_f = c6dofimu14_spi_write;
    }
    
    digital_in_init( &ctx->snc, cfg->snc );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return C6DOFIMU14_OK;
}

err_t c6dofimu14_default_cfg ( c6dofimu14_t *ctx ) 
{
    uint8_t tmp_data;
    
    err_t error_check = c6dofimu14_software_reset ( ctx );
    Delay_100ms( );
    
    tmp_data = C6DOFIMU14_DRIVECONFIG_MIN_SLEW_RATE;
    error_check |= c6dofimu14_generic_write ( ctx, C6DOFIMU14_REG0_DRIVE_CONFIG, &tmp_data, 1 );
    
    error_check |= c6dofimu14_generic_read ( ctx, C6DOFIMU14_REG0_WHO_AM_I, &tmp_data, 1 );
    if ( tmp_data != C6DOFIMU14_DEF_WHO_AM_I )
    {
        return C6DOFIMU14_ERROR;
    }
    
    tmp_data = C6DOFIMU14_PWR_TEMP_ENABLE | 
               C6DOFIMU14_PWR_IDLE_0 |
               C6DOFIMU14_PWR_GYRO_MODE_LOW_NOISE |
               C6DOFIMU14_PWR_ACCEL_MODE_LOW_NOISE;
    error_check |= c6dofimu14_generic_write ( ctx, C6DOFIMU14_REG0_PWR_MGMT_0, &tmp_data, 1 );
    
    tmp_data = C6DOFIMU14_ACFG0_FS_SEL_16G |
               C6DOFIMU14_ACFG0_ODR_1KHZ;
    error_check |= c6dofimu14_generic_write ( ctx, C6DOFIMU14_REG0_ACCEL_CONFIG_0, &tmp_data, 1 );
    
    tmp_data = C6DOFIMU14_GCFG0_FS_SEL_2000DPS |
               C6DOFIMU14_GCFG0_ODR_1KHZ;
    error_check |= c6dofimu14_generic_write ( ctx, C6DOFIMU14_REG0_GYRO_CONFIG_0, &tmp_data, 1 );
    
    tmp_data = C6DOFIMU14_FIFOCONFIG_STREAM_TO_FIFO_MODE;
    error_check |= c6dofimu14_generic_write ( ctx, C6DOFIMU14_REG0_FIFO_CONFIG, &tmp_data, 1 );
    
    tmp_data = C6DOFIMU14_FIFOCONFIG1_TEMP_EN |
               C6DOFIMU14_FIFOCONFIG1_GYRO_EN |
               C6DOFIMU14_FIFOCONFIG1_ACCEL_EN;
    error_check |= c6dofimu14_generic_write ( ctx, C6DOFIMU14_REG0_FIFO_CONFIG_1, &tmp_data, 1 );

    Delay_100ms( );
    return error_check;
}

err_t c6dofimu14_generic_write ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t c6dofimu14_generic_read ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t c6dofimu14_get_int_pin ( c6dofimu14_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

uint8_t c6dofimu14_get_snc_pin ( c6dofimu14_t *ctx )
{
    return digital_in_read ( &ctx->snc );
}

err_t c6dofimu14_software_reset ( c6dofimu14_t *ctx )
{
    uint8_t tmp_data = C6DOFIMU14_DEVCONFIG_SOFT_RESET_ENABLE;
    return c6dofimu14_generic_write( ctx, C6DOFIMU14_REG0_DEVICE_CONFIG, &tmp_data, 1 );
}

err_t c6dofimu14_get_data ( c6dofimu14_t *ctx, c6dofimu14_axis_t *acc_axis, c6dofimu14_axis_t *gyro_axis )
{
    uint8_t tmp_data[ 16 ];
    
    err_t error_check = c6dofimu14_check_data_ready ( ctx, C6DOFIMU14_INTSTATUS_FIFO_FULL );
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_FIFO_DATA, tmp_data, 16 );
    
    if ( ( tmp_data[ 0 ] & 0xFC ) == ( C6DOFIMU14_FIFOHEADER_ACCEL | 
                                       C6DOFIMU14_FIFOHEADER_GYRO | 
                                       C6DOFIMU14_FIFOHEADER_TIMESTAMP_ODR ) )
    {
        acc_axis->x = tmp_data[ 1 ];
        acc_axis->x <<= 8;
        acc_axis->x |= tmp_data[ 2 ];

        acc_axis->y = tmp_data[ 3 ];
        acc_axis->y <<= 8;
        acc_axis->y |= tmp_data[ 4 ];
        
        acc_axis->z = tmp_data[ 5 ];
        acc_axis->z <<= 8;
        acc_axis->z |= tmp_data[ 6 ];
        
        gyro_axis->x = tmp_data[ 7 ];
        gyro_axis->x <<= 8;
        gyro_axis->x |= tmp_data[ 8 ];
        
        gyro_axis->y = tmp_data[ 9 ];
        gyro_axis->y <<= 8;
        gyro_axis->y |= tmp_data[ 10 ];
        
        gyro_axis->z = tmp_data[ 11 ];
        gyro_axis->z <<= 8;
        gyro_axis->z |= tmp_data[ 12 ];
    }
    
    return error_check;
}

err_t c6dofimu14_get_temperature ( c6dofimu14_t *ctx, float *temp )
{
    int16_t raw_data;
    uint8_t tmp_data;
    
    err_t error_check = c6dofimu14_check_data_ready ( ctx, C6DOFIMU14_INTSTATUS_DATA_RDY );
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_TEMP_DATA_MSB, &tmp_data, 1 );
    raw_data = tmp_data;
    raw_data <<= 8;
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_TEMP_DATA_LSB, &tmp_data, 1 );
    raw_data |= tmp_data;
    *temp = ( ( float ) raw_data / 132.48 ) + 25.00;
    return error_check;
}

err_t c6dofimu14_get_accel_axis ( c6dofimu14_t *ctx, c6dofimu14_axis_t *axis )
{
    uint8_t tmp_data;
    err_t error_check = c6dofimu14_check_data_ready ( ctx, C6DOFIMU14_INTSTATUS_DATA_RDY );
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_ACCEL_X_MSB, &tmp_data, 1 );
    axis->x = tmp_data;
    axis->x <<= 8;
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_ACCEL_X_LSB, &tmp_data, 1 );
    axis->x |= tmp_data;

    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_ACCEL_Y_MSB, &tmp_data, 1 );
    axis->y = tmp_data;
    axis->y <<= 8;
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_ACCEL_Y_LSB, &tmp_data, 1 );
    axis->y |= tmp_data;
    
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_ACCEL_Z_MSB, &tmp_data, 1 );
    axis->z = tmp_data;
    axis->z <<= 8;
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_ACCEL_Z_LSB, &tmp_data, 1 );
    axis->z |= tmp_data;
    
    return error_check;
}

err_t c6dofimu14_get_gyro_axis ( c6dofimu14_t *ctx, c6dofimu14_axis_t *axis )
{
    uint8_t tmp_data;
    
    err_t error_check = c6dofimu14_check_data_ready ( ctx, C6DOFIMU14_INTSTATUS_DATA_RDY );
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_GYRO_X_MSB, &tmp_data, 1 );
    axis->x = tmp_data;
    axis->x <<= 8;
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_GYRO_X_LSB, &tmp_data, 1 );
    axis->x |= tmp_data;

    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_GYRO_Y_MSB, &tmp_data, 1 );
    axis->y = tmp_data;
    axis->y <<= 8;
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_GYRO_Y_LSB, &tmp_data, 1 );
    axis->y |= tmp_data;
    
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_GYRO_Z_MSB, &tmp_data, 1 );
    axis->z = tmp_data;
    axis->z <<= 8;
    error_check |= c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_GYRO_Z_LSB, &tmp_data, 1 );
    axis->z |= tmp_data;
    
    return error_check;
}

static err_t c6dofimu14_i2c_write ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t c6dofimu14_i2c_read ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t c6dofimu14_spi_write ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg & C6DOFIMU14_SPI_WRITE_MASK;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t c6dofimu14_spi_read ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t tmp_reg = reg | C6DOFIMU14_SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &tmp_reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t c6dofimu14_check_data_ready ( c6dofimu14_t *ctx, uint8_t flag ) 
{
    uint8_t tmp_data;
    uint16_t timeout_cnt = 0;
    for ( ; ; )
    {
        c6dofimu14_generic_read( ctx, C6DOFIMU14_REG0_INT_STATUS_1, &tmp_data, 1 );
        Delay_1ms( );
        if ( tmp_data & 0x08 )
        {
            return C6DOFIMU14_OK;
        }
        if ( timeout_cnt++ > TIMEOUT )
        {
            return C6DOFIMU14_ERROR;
        }
    }
}

// ------------------------------------------------------------------------ END
