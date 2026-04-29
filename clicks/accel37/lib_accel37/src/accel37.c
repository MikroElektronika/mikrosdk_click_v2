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
 * @file accel37.c
 * @brief Accel 37 Click Driver.
 */

#include "accel37.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                       0x00

/**
 * @brief SPI subcommand setting data.
 * @details Definition of SPI subcommand setting data.
 */
#define ACCEL37_SPI_CMD_WRITE       0x0A
#define ACCEL37_SPI_CMD_READ        0x0B

/**
 * @brief Accel 37 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel37_i2c_write ( accel37_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 37 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel37_i2c_read ( accel37_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 37 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel37_spi_write ( accel37_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 37 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel37_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel37_spi_read ( accel37_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel37_cfg_setup ( accel37_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL37_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL37_DRV_SEL_I2C;
}

void accel37_drv_interface_sel ( accel37_cfg_t *cfg, accel37_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel37_init ( accel37_t *ctx, accel37_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL37_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel37_i2c_read;
        ctx->write_f = accel37_i2c_write;
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

        ctx->read_f  = accel37_spi_read;
        ctx->write_f = accel37_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ACCEL37_OK;
}

err_t accel37_default_cfg ( accel37_t *ctx ) 
{
    err_t error_flag = ACCEL37_OK;
    
    /* check device id */
    if ( ACCEL37_ERROR == accel37_check_communication( ctx ) )
    {
        return ACCEL37_ERROR;
    }

    /* soft reset */
    if ( ACCEL37_ERROR == accel37_reset_device( ctx ) )
    {
        return ACCEL37_ERROR;
    }

    /* A latency of 20ms is required after a software reset */
    Delay_10ms( );
    Delay_10ms( );
    
    /* FILTER_CTL :
     *   bit[7:6] = 00  -> range +/-2g
     *   bit[5]   = 1   -> I2C HS ON
     *   bit[2:0] = 011 -> 100Hz */
    error_flag |= accel37_write_reg( ctx, ACCEL37_REG_FILTER_CTL,
                                     ACCEL37_FILTER_CTL_I2C_HS    |
                                     ACCEL37_FILTER_CTL_RANGE_2G  |
                                     ACCEL37_FILTER_CTL_ODR_100HZ );
    
    /* cache current sensitivity(+/-2g => 4000LSB/g ) */
    ctx->accel_sens = ACCEL37_ACCEL_SENS_2G; 
    
    /* TEMP_CTL :
     *   bit[7] = 1 -> Z axis non linear compensation ON
     *   bit[0] = 1 -> temp sensor on */                                 
    error_flag |= accel37_write_reg( ctx, ACCEL37_REG_TEMP_CTL,
                                     ACCEL37_TEMP_CTL_NL_COMP_EN | 
                                     ACCEL37_TEMP_CTL_TEMP_EN );

    /* enter measurement mode */
    error_flag |= accel37_write_reg( ctx, ACCEL37_REG_POWER_CTL, ACCEL37_POWER_CTL_MEASURE );

    Delay_100ms( );
                                     
    return error_flag;
}

err_t accel37_generic_write ( accel37_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel37_generic_read ( accel37_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel37_write_reg ( accel37_t *ctx, uint8_t reg, uint8_t data_in )
{
    return accel37_generic_write( ctx, reg, &data_in, 1 );
}

err_t accel37_read_reg ( accel37_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return accel37_generic_read( ctx, reg, data_out, 1 );
}

err_t accel37_check_communication ( accel37_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };

    /* Burst read 2 bytes from address 0x00:
     *    data_buf[0] <- DEVID_AD  (0xAD)
     *    data_buf[1] <- DEVID_MST (0x1D) */
    if ( ACCEL37_OK == accel37_generic_read( ctx, ACCEL37_REG_DEVID_AD, data_buf, 2 ) )
    {
        if ( ( ACCEL37_DEVID_AD  == data_buf[ 0 ] ) &&
             ( ACCEL37_DEVID_MST == data_buf[ 1 ] ) )
        {
            return ACCEL37_OK;
        }
    }
    return ACCEL37_ERROR;
}

err_t accel37_reset_device ( accel37_t *ctx )
{
    return accel37_write_reg( ctx, ACCEL37_REG_SOFT_RESET, ACCEL37_SOFT_RESET_KEY );
}

err_t accel37_set_fsr ( accel37_t *ctx, uint8_t fsr )
{
    err_t error_flag = ACCEL37_OK;
    uint8_t reg_data = 0;

    if ( fsr > ACCEL37_FS_8G )
    {
        return ACCEL37_ERROR;
    }

    /* Perform a read-modify-write on FILTER_CTL */
    error_flag = accel37_read_reg( ctx, ACCEL37_REG_FILTER_CTL, &reg_data );

    if ( ACCEL37_OK == error_flag )
    {
        /* modify bits[7:6] */
        reg_data &= ~ACCEL37_FILTER_CTL_RANGE_MASK;
        reg_data |= ( ( fsr << 6 ) & ACCEL37_FILTER_CTL_RANGE_MASK );

        /* sensitivity scales down by factor of 2 with each FSR step */
        ctx->accel_sens = ACCEL37_ACCEL_SENS_2G / ( 1 << fsr );

        /* write back modified FILTER_CTL */
        error_flag = accel37_write_reg( ctx, ACCEL37_REG_FILTER_CTL, reg_data );
    }

    return error_flag;
}

err_t accel37_set_odr ( accel37_t *ctx, uint8_t odr )
{
    err_t error_flag = ACCEL37_OK;
    uint8_t reg_data = 0;

    if ( odr > ACCEL37_ODR_400HZ )
    {
        return ACCEL37_ERROR;
    }

    /* Read-modify-write on FILTER_CTL */
    error_flag = accel37_read_reg( ctx, ACCEL37_REG_FILTER_CTL, &reg_data );

    if ( ACCEL37_OK == error_flag )
    {
        reg_data &= ~ACCEL37_FILTER_CTL_ODR_MASK;
        reg_data |= ( odr & ACCEL37_FILTER_CTL_ODR_MASK );
        error_flag = accel37_write_reg( ctx, ACCEL37_REG_FILTER_CTL, reg_data );
    }

    return error_flag;
}

err_t accel37_data_ready ( accel37_t *ctx )
{   
    uint8_t reg_data = 0;

    /* read status register */
    if ( ACCEL37_OK != accel37_read_reg( ctx, ACCEL37_REG_STATUS, &reg_data ) )
    {
        return ACCEL37_ERROR;
    }
    
    /* check DATA_READY bit */
    if ( reg_data & ACCEL37_STATUS_DATA_READY )
    {
        return ACCEL37_OK;
    }
    
    return ACCEL37_DATA_NOT_READY;
}

err_t accel37_get_accel ( accel37_t *ctx, accel37_axes_t *accel )
{
    err_t error_flag = ACCEL37_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;

    if ( NULL == accel )
    {
        return ACCEL37_ERROR;
    }

    /* check if there is a new sample ready to be read */
    error_flag = accel37_data_ready( ctx );
    
    if ( ACCEL37_OK == error_flag )
    {
        /* Burst read data(6 bytes) :
        *   data_buf[0] = XDATA_H (0x0E)
        *   data_buf[1] = XDATA_L (0x0F)
        *   data_buf[2] = YDATA_H (0x10)
        *   data_buf[3] = YDATA_L (0x11)
        *   data_buf[4] = ZDATA_H (0x12)
        *   data_buf[5] = ZDATA_L (0x13) */
        error_flag = accel37_generic_read( ctx, ACCEL37_REG_XDATA_H, data_buf, 6 );
    }

    if ( ACCEL37_OK == error_flag )
    {
        /* X-axis */
        raw_data = ( int16_t ) ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] );
        raw_data >>= 2;
        accel->x = ( float ) raw_data / ctx->accel_sens;

        /* Y-axis */
        raw_data = ( int16_t ) ( ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ] );
        raw_data >>= 2;
        accel->y = ( float ) raw_data / ctx->accel_sens;

        /* Z-axis */
        raw_data = ( int16_t ) ( ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ] );
        raw_data >>= 2;
        accel->z = ( float ) raw_data / ctx->accel_sens;
    }

    return error_flag;
}

err_t accel37_get_temp ( accel37_t *ctx, float *temp )
{
    err_t error_flag = ACCEL37_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;

    if ( NULL == temp )
    {
        return ACCEL37_ERROR;
    }

    /* check if there is a new sample ready to be read */
    error_flag = accel37_data_ready( ctx );

    if ( ACCEL37_OK == error_flag )
    {
        /* data_buf[0] = TEMP_H  (0x14)
         * data_buf[1] = TEMP_L  (0x15) */
        error_flag = accel37_generic_read( ctx, ACCEL37_REG_TEMP_H, data_buf, 2 );
    }

    if ( ACCEL37_OK == error_flag )
    {
        raw_data = ( int16_t ) ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] );
        raw_data >>= 2;
        *temp = ( float ) ( raw_data - ACCEL37_TEMP_BIAS ) / ACCEL37_TEMP_SENS + ACCEL37_TEMP_REF_C;
    }
    return error_flag;
}

err_t accel37_get_data ( accel37_t *ctx, accel37_data_t *data_out )
{
    err_t error_flag = ACCEL37_OK;
    uint8_t data_buf[ 8 ] = { 0 };
    int16_t raw_data = 0;

    if ( NULL == data_out )
    {
        return ACCEL37_ERROR;
    }
    
    /* check if there is a new sample ready to be read */
    error_flag = accel37_data_ready( ctx );
    if ( ACCEL37_OK == error_flag )
    {
        /* Burst read all data(8 bytes) :
        *   data_buf[0] = XDATA_H (0x0E)
        *   data_buf[1] = XDATA_L (0x0F)
        *   data_buf[2] = YDATA_H (0x10)
        *   data_buf[3] = YDATA_L (0x11)
        *   data_buf[4] = ZDATA_H (0x12)
        *   data_buf[5] = ZDATA_L (0x13)
        *   data_buf[6] = TEMP_H  (0x14)
        *   data_buf[7] = TEMP_L  (0x15) */
        error_flag = accel37_generic_read( ctx, ACCEL37_REG_XDATA_H, data_buf, 8 );

        if ( ACCEL37_OK == error_flag )
        {
            /* X-axis */
            raw_data = ( int16_t ) ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] );
            raw_data >>= 2;
            data_out->accel.x = ( float ) raw_data / ctx->accel_sens;

            /* Y-axis */
            raw_data = ( int16_t ) ( ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ] );
            raw_data >>= 2;
            data_out->accel.y = ( float ) raw_data / ctx->accel_sens;

            /* Z-axis */
            raw_data = ( int16_t ) ( ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ] );
            raw_data >>= 2;
            data_out->accel.z = ( float ) raw_data / ctx->accel_sens;

            /* Temp */
            raw_data = ( int16_t ) ( ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 7 ] );
            raw_data >>= 2;
            data_out->temperature = ( float ) ( raw_data - ACCEL37_TEMP_BIAS ) /
                                                ACCEL37_TEMP_SENS + ACCEL37_TEMP_REF_C;
        }
    }

    return error_flag;
}

uint8_t accel37_get_int_pin ( accel37_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t accel37_i2c_write ( accel37_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* [START][slave_addr+W][reg_addr][data_0]...[data_n][STOP] */
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel37_i2c_read ( accel37_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* [START][slave_addr+W][reg_addr][REPEATED_START][slave_addr+R][data...][STOP] */
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel37_spi_write ( accel37_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* [CS_low][0x0A][reg_addr][data...][CS_high] */
    uint8_t cmd_buf[ 2 ] = { ACCEL37_SPI_CMD_WRITE, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, cmd_buf, 2 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel37_spi_read ( accel37_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* [CS_low][0x0B][reg_addr][DUMMY...][CS_high] */
    uint8_t cmd_buf[ 2 ] = { ACCEL37_SPI_CMD_READ, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, cmd_buf, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
