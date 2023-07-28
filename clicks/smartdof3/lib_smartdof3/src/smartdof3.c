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
 * @file smartdof3.c
 * @brief Smart DOF 3 Click Driver.
 */

#include "smartdof3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                       0x00
#define SPI_READ_MASK               0x80

/**
 * @brief Temperature sensor characteristics values.
 * @details Definition of temperature sensor characteristics values.
 */
#define SMARTDOF3_TEMP_SEN_LSB_C    256
#define SMARTDOF3_TEMP_LSB_0         25

/**
 * @brief Smart DOF 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof3_i2c_write ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart DOF 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof3_i2c_read ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart DOF 3 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof3_spi_write ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart DOF 3 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof3_spi_read ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void smartdof3_cfg_setup ( smartdof3_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->it2  = HAL_PIN_NC;
    cfg->it1  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTDOF3_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = SMARTDOF3_DRV_SEL_I2C;
}

void smartdof3_drv_interface_selection ( smartdof3_cfg_t *cfg, smartdof3_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t smartdof3_init ( smartdof3_t *ctx, smartdof3_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( SMARTDOF3_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = smartdof3_i2c_read;
        ctx->write_f = smartdof3_i2c_write;
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

        ctx->read_f  = smartdof3_spi_read;
        ctx->write_f = smartdof3_spi_write;
    }

    digital_in_init( &ctx->it2, cfg->it2 );
    digital_in_init( &ctx->it1, cfg->it1 );

    return SMARTDOF3_OK;
}

err_t smartdof3_default_cfg ( smartdof3_t *ctx ) 
{
    uint8_t device_id;
    err_t err_flag = smartdof3_get_device_id( ctx, &device_id );
    if ( SMARTDOF3_DEVICE_ID == device_id )
    {
        err_flag |= smartdof3_soft_reset( ctx );
        Delay_10ms( );
        
        // Enable register address automatically incremented during a 
        // multiple byte access with a serial interface.
        err_flag |= smartdof3_en_auto_incr( ctx );
        Delay_1ms( );
        
        // Output registers are not updated until MSB and LSB have been read
        err_flag |= smartdof3_en_block_data_upd( ctx );
        Delay_1ms( );
        
        // Accelerometer ODR: 12.5 Hz (high performance)
        err_flag |= smartdof3_set_acc_data_rate( ctx, SMARTDOF3_ODR_XL_G_12_5_HZ );
        Delay_1ms( );
        
        // Accelerometer full-scale: ±2 g
        err_flag |= smartdof3_set_acc_full_scale( ctx, SMARTDOF3_XL_FULL_SCALE_2G );
        Delay_1ms( );
        
        // Gyroscope ODR: 12.5 Hz (high performance)
        err_flag |= smartdof3_set_gyro_data_rate( ctx, SMARTDOF3_ODR_XL_G_12_5_HZ );
        Delay_1ms( );
        
        // Gyroscope chain full-scale: ±500 dps
        err_flag |= smartdof3_set_gyro_full_scale( ctx, SMARTDOF3_GY_FULL_SCALE_500DPS );
        Delay_1ms( );
    }
    else
    {
        err_flag = SMARTDOF3_ERROR;
    }
    return err_flag;
}

err_t smartdof3_generic_write ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t smartdof3_generic_read ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t smartdof3_get_device_id ( smartdof3_t *ctx, uint8_t *device_id )
{
    return smartdof3_generic_read( ctx, SMARTDOF3_REG_WHO_AM_I, device_id, 1 );
}

err_t smartdof3_soft_reset ( smartdof3_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL3_C, &data_buf, 1 );
    data_buf |= SMARTDOF3_CTRL3_SOFT_RESET;
    err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL3_C, &data_buf, 1 );
    return err_flag;
}

err_t smartdof3_en_auto_incr ( smartdof3_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL3_C, &data_buf, 1 );
    data_buf &= SMARTDOF3_CTRL3_IF_INC_BIT_MASK;
    data_buf |= SMARTDOF3_CTRL3_IF_INC_ENABLE;
    err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL3_C, &data_buf, 1 );
    return err_flag;
}

err_t smartdof3_en_block_data_upd ( smartdof3_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL3_C, &data_buf, 1 );
    data_buf &= SMARTDOF3_CTRL3_BDU_BIT_MASK;
    data_buf |= SMARTDOF3_CTRL3_BDU_ENABLE;
    err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL3_C, &data_buf, 1 );
    return err_flag;
}

err_t smartdof3_set_op_mode ( smartdof3_t *ctx, uint8_t acc_op_mode, uint8_t gyro_op_mode )
{
    err_t err_flag = SMARTDOF3_OK;
    if ( SMARTDOF3_OP_MODE_PERFORMANCE_HIGH < ( acc_op_mode | gyro_op_mode ) )
    {
        err_flag = SMARTDOF3_ERROR;
    }
    else
    {
        acc_op_mode <<= 4;
        err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL6_C, &acc_op_mode, 1 );
        gyro_op_mode <<= 7;
        err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL7_G, &gyro_op_mode, 1 );
    }
    return err_flag;
}

err_t smartdof3_set_acc_data_rate ( smartdof3_t *ctx, uint8_t data_rate )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = SMARTDOF3_OK;
    if ( SMARTDOF3_ODR_XL_G_6667_HZ < data_rate )
    {
        err_flag = SMARTDOF3_ERROR;
    }
    else
    {
        data_rate &= SMARTDOF3_ODR_XL_G_BIT_MASK;
        data_rate <<= 4;
        err_flag |= smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL1_XL, &data_buf, 1 );
        data_buf &= SMARTDOF3_ODR_XL_G_BIT_MASK;
        data_buf |= data_rate;
        err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL1_XL, &data_buf, 1 );
    }
    return err_flag;
}

err_t smartdof3_set_acc_full_scale ( smartdof3_t *ctx, uint8_t data_scale )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = SMARTDOF3_OK;
    if ( SMARTDOF3_XL_FULL_SCALE_BIT_MASK < data_scale )
    {
        err_flag = SMARTDOF3_ERROR;
    }
    else
    {
        data_scale &= SMARTDOF3_XL_FULL_SCALE_BIT_MASK;
        data_scale <<= 2;
        err_flag |= smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL1_XL, &data_buf, 1 );
        data_buf &= ~SMARTDOF3_ODR_XL_G_BIT_MASK;
        data_buf |= data_scale;
        err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL1_XL, &data_buf, 1 );
    }
    return err_flag;
}

err_t smartdof3_get_acc_full_scale ( smartdof3_t *ctx, uint8_t *data_scale )
{
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL1_XL, data_scale, 1 );
    *data_scale >>= 2;
    *data_scale &= SMARTDOF3_XL_FULL_SCALE_BIT_MASK;
    return err_flag;
}

err_t smartdof3_get_acc_sensitivity ( smartdof3_t *ctx, float *sensitivity )
{
    uint8_t full_scale;
    err_t err_flag = smartdof3_get_acc_full_scale ( ctx, &full_scale );
    switch ( full_scale )
    {
        case SMARTDOF3_XL_FULL_SCALE_2G:
        {
            *sensitivity = SMARTDOF3_ACC_SENSITIVITY_FS_2G;
            break;
        }
        case SMARTDOF3_XL_FULL_SCALE_4G:
        {
            *sensitivity = SMARTDOF3_ACC_SENSITIVITY_FS_4G;
            break;
        }
        case SMARTDOF3_XL_FULL_SCALE_8G:
        {
            *sensitivity = SMARTDOF3_ACC_SENSITIVITY_FS_8G;
            break;
        }
        case SMARTDOF3_XL_FULL_SCALE_16G:
        {
            *sensitivity = SMARTDOF3_ACC_SENSITIVITY_FS_16G;
            break;
        }
        default: 
        {
            *sensitivity = SMARTDOF3_ACC_SENSITIVITY_FS_2G;
            err_flag = SMARTDOF3_ERROR;
            break;
        } 
    }
  return err_flag;
}

err_t smartdof3_set_gyro_data_rate ( smartdof3_t *ctx, uint8_t data_rate )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = SMARTDOF3_OK;
    if ( SMARTDOF3_ODR_XL_G_6667_HZ < data_rate )
    {
        err_flag = SMARTDOF3_ERROR;
    }
    else
    {
        data_rate &= SMARTDOF3_ODR_XL_G_BIT_MASK;
        data_rate <<= 4;
        err_flag |= smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL2_G, &data_buf, 1 );
        data_buf &= SMARTDOF3_ODR_XL_G_BIT_MASK;
        data_buf |= data_rate;
        err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL2_G, &data_buf, 1 );
    }
    return err_flag;
}

err_t smartdof3_set_gyro_full_scale ( smartdof3_t *ctx, uint8_t data_scale )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = SMARTDOF3_OK;
    if ( SMARTDOF3_GY_FULL_SCALE_BIT_MASK < data_scale )
    {
        err_flag = SMARTDOF3_ERROR;
    }
    else
    {
        data_scale &= SMARTDOF3_GY_FULL_SCALE_BIT_MASK;
        data_scale <<= 1;
        err_flag |= smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL2_G, &data_buf, 1 );
        data_buf &= ~SMARTDOF3_ODR_XL_G_BIT_MASK;
        data_buf |= data_scale;
        err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL2_G, &data_buf, 1 );
    }
    return err_flag;
}

err_t smartdof3_get_gyro_full_scale ( smartdof3_t *ctx, uint8_t *data_scale )
{
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL2_G, data_scale, 1 );
    *data_scale >>= 1;
    *data_scale &= SMARTDOF3_GY_FULL_SCALE_BIT_MASK;
    return err_flag;
}

err_t smartdof3_get_status ( smartdof3_t *ctx, smartdof3_status_t *status )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_STATUS, &data_buf, 1 );
    status->tda  = ( data_buf >> 2 ) & 0x01;
    status->gda  = ( data_buf >> 1 ) & 0x01;
    status->xlda =   data_buf        & 0x01;
    return err_flag;
}

err_t smartdof3_get_gyro_sensitivity ( smartdof3_t *ctx, float *sensitivity )
{
    uint8_t full_scale;
    err_t err_flag = smartdof3_get_gyro_full_scale ( ctx, &full_scale );
    switch ( full_scale )
    {
        case SMARTDOF3_GY_FULL_SCALE_125DPS:
        {
            *sensitivity = SMARTDOF3_GYRO_SENSITIVITY_FS_125DPS;
            break;
        }
        case SMARTDOF3_GY_FULL_SCALE_250DPS:
        {
            *sensitivity = SMARTDOF3_GYRO_SENSITIVITY_FS_250DPS;
            break;
        }
        case SMARTDOF3_GY_FULL_SCALE_500DPS:
        {
            *sensitivity = SMARTDOF3_GYRO_SENSITIVITY_FS_500DPS;
            break;
        }
        case SMARTDOF3_GY_FULL_SCALE_1000DPS:
        {
            *sensitivity = SMARTDOF3_GYRO_SENSITIVITY_FS_1000DPS;
            break;
        }
        case SMARTDOF3_GY_FULL_SCALE_2000DPS:
        {
            *sensitivity = SMARTDOF3_GYRO_SENSITIVITY_FS_2000DPS;
            break;
        }
        default: 
        {
            *sensitivity = SMARTDOF3_GYRO_SENSITIVITY_FS_125DPS;
            break;
        } 
    }
  return err_flag;
}

err_t smartdof3_get_acc_axis_data ( smartdof3_t *ctx, smartdof3_axis_data_t *acc_axis )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_OUTX_L_A, data_buf, 6 );
    acc_axis->x = data_buf[ 1 ];
    acc_axis->x <<= 8;
    acc_axis->x |= data_buf[ 0 ];
    acc_axis->y = data_buf[ 3 ];
    acc_axis->y <<= 8;
    acc_axis->y |= data_buf[ 2 ];
    acc_axis->z = data_buf[ 5 ];
    acc_axis->z <<= 8;
    acc_axis->z |= data_buf[ 4 ];
    return err_flag;
}

err_t smartdof3_get_gyro_axis_data ( smartdof3_t *ctx, smartdof3_axis_data_t *gyro_axis )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_OUTX_L_G, data_buf, 6 );
    gyro_axis->x = data_buf[ 1 ];
    gyro_axis->x <<= 8;
    gyro_axis->x |= data_buf[ 0 ];
    gyro_axis->y = data_buf[ 3 ];
    gyro_axis->y <<= 8;
    gyro_axis->y |= data_buf[ 2 ];
    gyro_axis->z = data_buf[ 5 ];
    gyro_axis->z <<= 8;
    gyro_axis->z |= data_buf[ 4 ];
    return err_flag;
}

err_t smartdof3_get_acc_axis ( smartdof3_t *ctx, smartdof3_axis_t *acc_axis )
{
    smartdof3_axis_data_t acc_axis_raw;
    float acc_sensitivity;
    err_t err_flag = smartdof3_get_acc_axis_data ( ctx, &acc_axis_raw );
    err_flag |= smartdof3_get_acc_sensitivity ( ctx, &acc_sensitivity );
    acc_axis->x = ( ( float ) acc_axis_raw.x ) * acc_sensitivity;
    acc_axis->y = ( ( float ) acc_axis_raw.y ) * acc_sensitivity;
    acc_axis->z = ( ( float ) acc_axis_raw.z ) * acc_sensitivity;
    return err_flag;
}

err_t smartdof3_get_gyro_axis ( smartdof3_t *ctx, smartdof3_axis_t *gyro_axis )
{
    smartdof3_axis_data_t gyro_axis_raw;
    float gyro_sensitivity;
    err_t err_flag = smartdof3_get_gyro_axis_data ( ctx, &gyro_axis_raw );
    err_flag |= smartdof3_get_gyro_sensitivity ( ctx, &gyro_sensitivity );
    gyro_axis->x = ( ( float ) gyro_axis_raw.x ) * gyro_sensitivity;
    gyro_axis->y = ( ( float ) gyro_axis_raw.y ) * gyro_sensitivity;
    gyro_axis->z = ( ( float ) gyro_axis_raw.z ) * gyro_sensitivity;
    return err_flag;
}

err_t smartdof3_enable_temperature ( smartdof3_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_CTRL10_C, &data_buf, 1 );
    data_buf |= SMARTDOF3_TIMESTAMP_ENABLE;
    err_flag |= smartdof3_generic_write( ctx, SMARTDOF3_REG_CTRL10_C, &data_buf, 1 );
    return err_flag;
}

err_t smartdof3_get_temperature_raw ( smartdof3_t *ctx, int16_t *temp_raw )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = smartdof3_generic_read( ctx, SMARTDOF3_REG_OUT_TEMP_L, data_buf, 2 );
    *temp_raw = data_buf[ 1 ];
    *temp_raw <<= 8;
    *temp_raw |= data_buf[ 0 ];
    return err_flag;
}

err_t smartdof3_get_temperature ( smartdof3_t *ctx, float *temperature )
{
    int16_t temp_raw;
    err_t err_flag = smartdof3_get_temperature_raw( ctx, &temp_raw );
    *temperature = ( float ) temp_raw;
    *temperature /= SMARTDOF3_TEMP_SEN_LSB_C;
    *temperature += SMARTDOF3_TEMP_LSB_0;
    return err_flag;
}

uint8_t smartdof3_get_in1_pin ( smartdof3_t *ctx )
{
    return digital_in_read ( &ctx->it1 );
}

uint8_t smartdof3_get_in2_pin ( smartdof3_t *ctx )
{
    return digital_in_read ( &ctx->it2 );
}

static err_t smartdof3_i2c_write ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t smartdof3_i2c_read ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t smartdof3_spi_write ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t smartdof3_spi_read ( smartdof3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
