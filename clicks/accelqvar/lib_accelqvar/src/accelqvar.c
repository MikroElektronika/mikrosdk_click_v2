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
** EXaccelqvar OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file accelqvar.c
 * @brief AccelQvar Click Driver.
 */

#include "accelqvar.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief AccelQvar I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accelqvar_i2c_write ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief AccelQvar I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accelqvar_i2c_read ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief AccelQvar SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accelqvar_spi_write ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief AccelQvar SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accelqvar_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accelqvar_spi_read ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accelqvar_cfg_setup ( accelqvar_cfg_t *cfg ) 
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
    cfg->i2c_address = ACCELQVAR_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCELQVAR_DRV_SEL_I2C;
}

void accelqvar_drv_interface_sel ( accelqvar_cfg_t *cfg, accelqvar_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accelqvar_init ( accelqvar_t *ctx, accelqvar_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCELQVAR_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accelqvar_i2c_read;
        ctx->write_f = accelqvar_i2c_write;
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

        ctx->read_f  = accelqvar_spi_read;
        ctx->write_f = accelqvar_spi_write;
    }

    digital_in_init( &ctx->it1, cfg->it1 );
    digital_in_init( &ctx->it2, cfg->it2 );
    ctx->sensitivity = ACCELQVAR_SENSITIVITY_FS_2G;

    return ACCELQVAR_OK;
}

err_t accelqvar_default_cfg ( accelqvar_t *ctx ) 
{
     err_t err_flag = ACCELQVAR_OK;
    uint8_t device_who_am_i = DUMMY;

    if ( ACCELQVAR_DRV_SEL_SPI == ctx->drv_sel ) 
    {
        err_flag = accelqvar_spi_wake_up( ctx );
        Delay_100ms( );
    }

    err_flag |= accelqvar_sw_reset( ctx );
    Delay_100ms( );

    err_flag |= accelqvar_get_device_id( ctx, &device_who_am_i );
    if ( ACCELQVAR_WHO_AM_I == device_who_am_i )
    {
        err_flag |= accelqvar_set_odr( ctx, ACCELQVAR_CTRL5_ODR_800_HZ );
        Delay_10ms( );

        err_flag |= accelqvar_set_fsr( ctx, ACCELQVAR_CTRL5_FS_2_G );
        Delay_10ms( );

        err_flag |= accelqvar_en_qvar( ctx );
        Delay_10ms( );
    }
    else
    {
        err_flag = ACCELQVAR_ERROR;
    }
    return err_flag;
}

err_t accelqvar_generic_write ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accelqvar_generic_read ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accelqvar_get_device_id ( accelqvar_t *ctx, uint8_t *device_id ) 
{
    return accelqvar_generic_read( ctx, ACCELQVAR_REG_WHO_AM_I, device_id, 1 );
}

err_t accelqvar_sw_reset ( accelqvar_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = accelqvar_generic_read( ctx, ACCELQVAR_REG_CTRL1, &data_buf, 1 );
    data_buf |= ACCELQVAR_CTRL1_SW_RESET;
    err_flag |= accelqvar_generic_write( ctx, ACCELQVAR_REG_CTRL1, &data_buf, 1 );
    return err_flag;
}

err_t accelqvar_set_odr ( accelqvar_t *ctx, uint8_t odr ) 
{
    err_t err_flag = ACCELQVAR_ERROR;
    if ( ( odr & ACCELQVAR_CTRL5_ODR_ONE_SHOT_IFACE ) || 
         ( odr == ACCELQVAR_CTRL5_ODR_PWR_DOWN ) )
    {
        uint8_t data_buf = DUMMY;
        err_flag = accelqvar_generic_read( ctx, ACCELQVAR_REG_CTRL5, &data_buf, 1 );
        data_buf &= ~ACCELQVAR_CTRL5_ODR_ONE_SHOT_IFACE;
        data_buf |= odr;
        err_flag |= accelqvar_generic_write( ctx, ACCELQVAR_REG_CTRL5, &data_buf, 1 );
    }
    return err_flag;
}

err_t accelqvar_set_fsr ( accelqvar_t *ctx, uint8_t fsr ) 
{
    err_t err_flag = ACCELQVAR_ERROR;
    if ( fsr <= ACCELQVAR_CTRL5_FS_16_G )
    {
        uint8_t data_buf = DUMMY;
        ctx->sensitivity = ACCELQVAR_SENSITIVITY_FS_2G;
        if ( fsr == ACCELQVAR_CTRL5_FS_4_G )
        {
            ctx->sensitivity = ACCELQVAR_SENSITIVITY_FS_4G;
        }
        else if ( fsr == ACCELQVAR_CTRL5_FS_8_G )
        {
            ctx->sensitivity = ACCELQVAR_SENSITIVITY_FS_8G;
        }
        else if ( fsr == ACCELQVAR_CTRL5_FS_16_G )
        {
            ctx->sensitivity = ACCELQVAR_SENSITIVITY_FS_16G;
        }
        err_flag = accelqvar_generic_read( ctx, ACCELQVAR_REG_CTRL5, &data_buf, 1 );
        data_buf &= ~ACCELQVAR_CTRL5_FS_16_G;
        data_buf |= fsr;
        err_flag |= accelqvar_generic_write( ctx, ACCELQVAR_REG_CTRL5, &data_buf, 1 );
    }
    return err_flag;
}

err_t accelqvar_get_axes_data ( accelqvar_t *ctx, accelqvar_axes_t *axes )
{
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t axis_data = DUMMY;
    
    err_t err_flag = accelqvar_generic_read( ctx, ACCELQVAR_REG_OUT_X_L, data_buf, 6 );
    axis_data = data_buf[ 1 ];
    axis_data <<= 8;
    axis_data |= data_buf[ 0 ];
    axes->x = ( float ) axis_data * ctx->sensitivity;
    axis_data = data_buf[ 3 ];
    axis_data <<= 8;
    axis_data |= data_buf[ 2 ];
    axes->y = ( float ) axis_data * ctx->sensitivity;
    axis_data = data_buf[ 5 ];
    axis_data <<= 8;
    axis_data |= data_buf[ 4 ];
    axes->z = ( float ) axis_data * ctx->sensitivity;
    
    return err_flag;
}

err_t accelqvar_spi_wake_up ( accelqvar_t *ctx )
{
    uint8_t data_buf = ACCELQVAR_IF_WAKE_UP_SOFT_PD;
    return accelqvar_generic_write( ctx, ACCELQVAR_REG_IF_WAKE_UP, &data_buf, 1 );
}

err_t accelqvar_en_qvar ( accelqvar_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = accelqvar_generic_read( ctx, ACCELQVAR_REG_AH_QVAR_CFG, &data_buf, 1 );
    data_buf |= ACCELQVAR_AH_QVAR_CFG_AH_QVAR_EN;
    err_flag |= accelqvar_generic_write( ctx, ACCELQVAR_REG_AH_QVAR_CFG, &data_buf, 1 );
    return err_flag;
}

err_t accelqvar_get_qvar_data ( accelqvar_t *ctx, float *qvar )
{
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t qvar_data = DUMMY;
    
    err_t err_flag = accelqvar_generic_read( ctx, ACCELQVAR_REG_OUT_T_AH_QVAR_L, data_buf, 2 );
    qvar_data = data_buf[ 1 ];
    qvar_data <<= 8;
    qvar_data |= data_buf[ 0 ];
    qvar_data >>= 4;
    *qvar = ( float ) qvar_data;
    *qvar /= ACCELQVAR_QVAR_DIVIDER;

    return err_flag;
}

uint8_t accelqvar_get_int1 ( accelqvar_t *ctx )
{
    return digital_in_read( &ctx->it1 );
}

uint8_t accelqvar_get_int2 ( accelqvar_t *ctx )
{
    return digital_in_read( &ctx->it2 );
}

static err_t accelqvar_i2c_write ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accelqvar_i2c_read ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accelqvar_spi_write ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accelqvar_spi_read ( accelqvar_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
