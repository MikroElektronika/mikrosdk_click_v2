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
 * @file accel19.c
 * @brief Accel 19 Click Driver.
 */

#include "accel19.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Temperature calcutation data.
 * @details Definition of temperature calcutation data.
 */
#define ACCEL19_TEMPERATURE_LSB_PER_C                16
#define ACCEL19_TEMPERATURE_LSB_ZERO                 25

/**
 * @brief Accel 19 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel19_i2c_write ( accel19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 19 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel19_i2c_read ( accel19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 19 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel19_spi_write ( accel19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 19 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel19_spi_read ( accel19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 19 configuration delay function.
 * @details This function executes a configuration delay of the 10 milliseconds.
 * @return Nothing.
 * @note None.
 */
static void dev_cfg_delay ( void );

void accel19_cfg_setup ( accel19_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL19_SET_DEV_ADDR_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL19_DRV_SEL_I2C;
}

void accel19_drv_interface_selection ( accel19_cfg_t *cfg, accel19_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel19_init ( accel19_t *ctx, accel19_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL19_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel19_i2c_read;
        ctx->write_f = accel19_i2c_write;
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

        ctx->read_f  = accel19_spi_read;
        ctx->write_f = accel19_spi_write;
    }
    
    ctx->chip_select = cfg->cs;
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_in_init( &ctx->in2, cfg->in2 );
    digital_in_init( &ctx->in1, cfg->in1 );

    return 0;
}

err_t accel19_default_cfg ( accel19_t *ctx ) 
{
    err_t error_flag = accel19_set_control( ctx, ACCEL19_CNTL1_ODR_HP_LP_200_Hz, 
                                                 ACCEL19_CNTL1_OP_MODE_HIGH_POWER_MODE, 
                                                 ACCEL19_CNTL1_LP_MODE4_RES_14_bit );
    dev_cfg_delay( );
    
    accel19_set_full_scale( ctx, ACCEL19_CTRL6_FS_2g );
    dev_cfg_delay( );
    
    error_flag |= accel19_set_bw_filt_odr( ctx, ACCEL19_CTRL6_BW_FILT_ODR_2 );
    dev_cfg_delay( );
    
    return error_flag;
}

err_t accel19_generic_write ( accel19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel19_generic_read ( accel19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel19_get_temperature ( accel19_t *ctx, float *temperature )
{
    uint8_t rx_buf[ 2 ];
    int16_t tmp;
    
    err_t error_flag = accel19_generic_read( ctx, ACCEL19_REG_OUT_T_L, rx_buf, 2 );
    
    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ]; 
    tmp >>= 4;
    
    *temperature = ( float ) tmp;
    *temperature /= ACCEL19_TEMPERATURE_LSB_PER_C;
    *temperature += ACCEL19_TEMPERATURE_LSB_ZERO;
    
    return error_flag;
}

err_t accel19_check_device_id ( accel19_t *ctx ) 
{
    uint8_t id_val;
    
    accel19_generic_read( ctx, ACCEL19_REG_WHO_AM_I, &id_val, 1 );
    
    if ( id_val == ACCEL19_DEVICE_ID ) 
    {
        return ACCEL19_OK;
    }
    else
    {
        return ACCEL19_ERROR;    
    }
}

err_t accel19_set_control ( accel19_t *ctx, uint8_t odr, uint8_t op_mode, uint8_t lp_mode )
{
    uint8_t tx_buf;
    
    odr     &= ACCEL19_CNTL1_ODR_BIT_MASK;
    op_mode &= ACCEL19_CNTL1_OP_MODE_BIT_MASK;
    lp_mode &= ACCEL19_CNTL1_LP_MODE_BIT_MASK;
    
    return accel19_generic_write( ctx, ACCEL19_REG_CTRL1, &tx_buf, 1 );
}

err_t accel19_soft_reset ( accel19_t *ctx )
{
    uint8_t data_buf;
    
    err_t error_flag = accel19_generic_read( ctx, ACCEL19_REG_CTRL2, &data_buf, 1 );
    
    data_buf |= ACCEL19_CNTL2_SOFT_RESET;
    error_flag |= accel19_generic_write( ctx, ACCEL19_REG_CTRL2, &data_buf, 1 );
    
    return error_flag;
}

err_t accel19_get_status ( accel19_t *ctx, uint8_t *status )
{    
    return accel19_generic_read( ctx, ACCEL19_REG_STATUS, status, 1 );
}

uint8_t accel19_data_ready (accel19_t *ctx ) 
{
    uint8_t rx_buf;
    
    accel19_generic_read( ctx, ACCEL19_REG_STATUS, &rx_buf, 1 );
    
    rx_buf &= ACCEL19_STATUS_DRDY;

    return rx_buf;
}

err_t accel19_set_full_scale ( accel19_t *ctx, uint8_t full_scale )
{
    uint8_t data_buf;
    
    full_scale &= ACCEL19_CTRL6_FS_BIT_MASK;
    
    err_t error_flag = accel19_generic_read( ctx, ACCEL19_REG_CTRL6, &data_buf, 1 );
    
    data_buf &= ~ACCEL19_CTRL6_FS_16g;
    data_buf |= full_scale;
    
    error_flag |= accel19_generic_write( ctx, ACCEL19_REG_CTRL6, &data_buf, 1 );
    
    return error_flag;
}

err_t accel19_set_bw_filt_odr ( accel19_t *ctx, uint8_t bw_filt_odr )
{
    uint8_t data_buf;
    
    bw_filt_odr &= ACCEL19_CTRL6_BW_FILT_BIT_MASK;
    
    err_t error_flag = accel19_generic_read( ctx, ACCEL19_REG_CTRL6, &data_buf, 1 );
    
    data_buf &= ~ACCEL19_CTRL6_BW_FILT_BIT_MASK;
    data_buf |= bw_filt_odr;
    
    error_flag |= accel19_generic_write( ctx, ACCEL19_REG_CTRL6, &data_buf, 1 );
    
    return error_flag;
}

err_t accel19_get_axis_data ( accel19_t *ctx, accel19_axis_t *axis )
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    
    err_t err_flag = accel19_generic_read( ctx, ACCEL19_REG_OUT_X_L, rx_buf, 6 );
    
    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ];
    
    axis->x = ( int16_t ) tmp;
    
    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    
    axis->y = ( int16_t ) tmp;
    
    tmp = rx_buf[ 5 ];
    tmp <<= 8;
    tmp |= rx_buf[ 4 ];
    
    axis->z = ( int16_t ) tmp;
    
    return err_flag;
}

uint8_t accel19_get_int_1 ( accel19_t *ctx ) 
{
     return digital_in_read( &ctx->in1 );
}

uint8_t accel19_get_int_2 ( accel19_t *ctx ) 
{
     return digital_in_read( &ctx->in2 );
}

static err_t accel19_i2c_write ( accel19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t accel19_i2c_read ( accel19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel19_spi_write ( accel19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
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

static err_t accel19_spi_read ( accel19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static void dev_cfg_delay ( void ) 
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------ END
