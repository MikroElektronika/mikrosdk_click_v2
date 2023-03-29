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
 * @file barometer8.c
 * @brief Barometer 8 Click Driver.
 */

#include "barometer8.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Barometer 8 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer8_i2c_write ( barometer8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 8 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer8_i2c_read ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Barometer 8 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer8_spi_write ( barometer8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Barometer 8 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barometer8_spi_read ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void barometer8_cfg_setup ( barometer8_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BAROMETER8_SET_DEVICE_ADDRESS;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = BAROMETER8_DRV_SEL_I2C;
}

void barometer8_drv_interface_selection ( barometer8_cfg_t *cfg, barometer8_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t barometer8_init ( barometer8_t *ctx, barometer8_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( BAROMETER8_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = barometer8_i2c_read;
        ctx->write_f = barometer8_i2c_write;
        
        digital_out_t cs_pin;
        digital_out_init ( &cs_pin, cfg->cs );
        digital_out_high ( &cs_pin );
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

        ctx->read_f  = barometer8_spi_read;
        ctx->write_f = barometer8_spi_write;
    }

    return BAROMETER8_OK;
}

err_t barometer8_default_cfg ( barometer8_t *ctx ) 
{
    err_t error_flag = BAROMETER8_OK;
    
    error_flag |= barometer8_software_reset ( ctx );
    Delay_100ms ( );
    
    if ( BAROMETER8_DRV_SEL_SPI == ctx->drv_sel ) 
    {
        error_flag |= barometer8_write_register ( ctx, BAROMETER8_REG_IF_CTRL, BAROMETER8_ENABLE_SPI_READ );
    }
    
    if ( BAROMETER8_ERROR == barometer8_check_communication ( ctx ) )
    {
        return BAROMETER8_ERROR;
    }
    
    error_flag |= barometer8_write_register ( ctx, BAROMETER8_REG_CTRL_REG1, BAROMETER8_ODR_4HZ | 
                                                                             BAROMETER8_AVG_32 );
    
    ctx->ctrl_reg2 = BAROMETER8_BOOT_NORMAL | BAROMETER8_FS_MODE_2;
    error_flag |= barometer8_write_register ( ctx, BAROMETER8_REG_CTRL_REG2, ctx->ctrl_reg2 );
    Delay_1sec ( );
    
    return error_flag;
}

err_t barometer8_generic_write ( barometer8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    if ( ( ( reg < BAROMETER8_REG_INTERRUPT_CFG ) || ( reg > BAROMETER8_REG_CTRL_REG3 ) ) &&
         ( ( reg < BAROMETER8_REG_FIFO_CTRL ) || ( reg > BAROMETER8_REG_REF_P_H ) ) &&
         ( ( reg < BAROMETER8_REG_I3C_IF_CTRL ) || ( reg > BAROMETER8_REG_RPDS_H ) ) &&
         ( ( reg < BAROMETER8_REG_INT_SOURCE ) || ( reg > BAROMETER8_REG_TEMP_OUT_H ) ) &&
         ( ( reg < BAROMETER8_REG_FIFO_DATA_OUT_PRESS_XL ) || ( reg > BAROMETER8_REG_FIFO_DATA_OUT_PRESS_H ) ) )
    {
        return BAROMETER8_ERROR;
    }
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t barometer8_generic_read ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    if ( ( ( reg < BAROMETER8_REG_INTERRUPT_CFG ) || ( reg > BAROMETER8_REG_CTRL_REG3 ) ) &&
         ( ( reg < BAROMETER8_REG_FIFO_CTRL ) || ( reg > BAROMETER8_REG_REF_P_H ) ) &&
         ( ( reg < BAROMETER8_REG_I3C_IF_CTRL ) || ( reg > BAROMETER8_REG_RPDS_H ) ) &&
         ( ( reg < BAROMETER8_REG_INT_SOURCE ) || ( reg > BAROMETER8_REG_TEMP_OUT_H ) ) &&
         ( ( reg < BAROMETER8_REG_FIFO_DATA_OUT_PRESS_XL ) || ( reg > BAROMETER8_REG_FIFO_DATA_OUT_PRESS_H ) ) )
    {
        return BAROMETER8_ERROR;
    }
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t barometer8_write_register ( barometer8_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return barometer8_generic_write( ctx, reg, &data_in, 1 );
}

err_t barometer8_read_register ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return barometer8_generic_read( ctx, reg, data_out, 1 );
}

err_t barometer8_check_communication ( barometer8_t *ctx )
{
    uint8_t who_am_i;
    if ( BAROMETER8_OK == barometer8_read_register ( ctx, BAROMETER8_REG_WHO_AM_I, &who_am_i ) )
    {
        if ( BAROMETER8_WHO_AM_I == who_am_i )
        {
            return BAROMETER8_OK;
        }
    }
    return BAROMETER8_ERROR;
}

err_t barometer8_software_reset ( barometer8_t *ctx )
{
    return barometer8_write_register ( ctx, BAROMETER8_REG_CTRL_REG2, BAROMETER8_SWRESET );
}

err_t barometer8_read_data ( barometer8_t *ctx, float *pressure, float *temperature )
{
    uint8_t status;
    if ( BAROMETER8_ERROR == barometer8_read_register ( ctx, BAROMETER8_REG_STATUS, &status ) )
    {
        return BAROMETER8_ERROR;
    }
    uint8_t data_buf[ 5 ] = { 0 };
    if ( ( status & BAROMETER8_STATUS_T_DA ) && ( status & BAROMETER8_STATUS_P_DA ) )
    {
        if ( BAROMETER8_ERROR == barometer8_generic_read ( ctx, BAROMETER8_REG_PRESSURE_OUT_XL, data_buf, 5 ) )
        {
            return BAROMETER8_ERROR;
        }
        *pressure = ( float ) ( ( ( uint32_t ) data_buf[ 2 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ] );
        if ( ctx->ctrl_reg2 & BAROMETER8_FS_MODE_2 )
        {
            *pressure /= BAROMETER8_PRESSURE_FS_MODE_2_RES;
        }
        else
        {
            *pressure /= BAROMETER8_PRESSURE_FS_MODE_1_RES;
        }
        *temperature = ( ( ( int16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ] ) * 0.01;
        return BAROMETER8_OK;
    }
    return BAROMETER8_ERROR;
}

static err_t barometer8_i2c_write ( barometer8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t barometer8_i2c_read ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t barometer8_spi_write ( barometer8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t barometer8_spi_read ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
