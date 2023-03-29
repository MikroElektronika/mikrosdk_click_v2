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
 * @file accel30.c
 * @brief Accel 30 Click Driver.
 */

#include "accel30.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY              0x00

/**
 * @brief SPI write/read bit mask.
 * @details Definition of SPI write/read bit mask data.
 */
#define SPI_WRITE_MASK     0x40
#define SPI_READ_MASK      0xC0

/**
 * @brief Accel 30 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel30_i2c_write ( accel30_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 30 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel30_i2c_read ( accel30_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 30 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel30_spi_write ( accel30_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 30 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel30_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel30_spi_read ( accel30_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel30_cfg_setup ( accel30_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL30_DEVICE_ADDRESS_VCC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL30_DRV_SEL_I2C;
}

void accel30_drv_interface_selection ( accel30_cfg_t *cfg, accel30_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel30_init ( accel30_t *ctx, accel30_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL30_DRV_SEL_I2C == ctx->drv_sel ) 
    {       
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;
        ctx->chip_select = cfg->cs;
        
        spi_master_deselect_device( ctx->chip_select );

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

        ctx->read_f  = accel30_i2c_read;
        ctx->write_f = accel30_i2c_write;
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

        ctx->read_f  = accel30_spi_read;
        ctx->write_f = accel30_spi_write;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );

    return ACCEL30_OK;
}

err_t accel30_default_cfg ( accel30_t *ctx ) 
{
    uint8_t data_buf[ 1 ] = { 0 };
    data_buf[ 0 ] = DUMMY;
    err_t err_flag = accel30_generic_write( ctx, ACCEL30_REG_SCRATCH, data_buf, 1 );
    err_flag |= accel30_soft_reset( ctx );
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_SCRATCH, data_buf, 1 );
    err_flag |= accel30_set_mode( ctx, ACCEL30_MODE_STANDBY );
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_SCRATCH, data_buf, 1 );
    err_flag |= accel30_set_wake_gain( ctx, ACCEL30_GAIN_1X );
    err_flag |= accel30_set_sniff_gain( ctx, ACCEL30_GAIN_1X );
    err_flag |= accel30_set_pwr_mode( ctx, ACCEL30_PRE_POWER );
    err_flag |= accel30_set_range_ctrl( ctx, ACCEL30_RANGE_2G );
    err_flag |= accel30_set_resolution_ctrl( ctx, ACCEL30_RESOLUTION_12BIT );
    err_flag |= accel30_set_mode( ctx, ACCEL30_MODE_CWAKE );
    return err_flag;
}

err_t accel30_generic_write ( accel30_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel30_generic_read ( accel30_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel30_set_mode ( accel30_t *ctx, accel30_op_mode_t mode )
{
    uint8_t data_buf[ 1 ] = { 0 };
    err_t err_flag = accel30_generic_read( ctx, ACCEL30_REG_MODE_C, data_buf, 1 );
    data_buf[ 0 ] &= ACCEL30_MODE_BIT_MASK;
    data_buf[ 0 ] |= mode;
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_MODE_C, data_buf, 1 );
    return err_flag;
}

err_t accel30_set_range_ctrl ( accel30_t *ctx, accel30_range_t range )
{
    uint8_t data_buf[ 1 ] = { 0 };  
    ctx->range_cfg = range;
    err_t err_flag = accel30_set_mode( ctx, ACCEL30_MODE_STANDBY );
    err_flag |= accel30_generic_read( ctx, ACCEL30_REG_RANGE_C, data_buf, 1 );
    data_buf[ 0 ] &= ACCEL30_RANGE_BIT_MASK;
    data_buf[ 0 ] |= ( range & ACCEL30_RANGE_BIT_MASK ) << 4; 
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_RANGE_C, data_buf, 1 );
    return err_flag;
}

err_t accel30_soft_reset ( accel30_t *ctx )
{
    uint8_t data_buf[ 1 ] = { 0 };
    data_buf[ 0 ]  = ACCEL30_MODE_STANDBY | ACCEL30_ENABLE_XYZ_AXIS_PD | ACCEL30_TRIG_CMD_CONTINUOUS;
    err_t err_flag = accel30_generic_write( ctx, ACCEL30_REG_MODE_C, data_buf, 1 );
    data_buf[ 0 ] = ACCEL30_FORCE_RESET;
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_RESET, data_buf, 1 );
    Delay_100ms( );
    data_buf[ 0 ] = DUMMY;
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_SCRATCH, data_buf, 1 );
    if ( ctx->drv_sel == ACCEL30_DRV_SEL_I2C )
    {
        data_buf[ 0 ] = ACCEL30_I2C_ENABLE;
    }
    else
    {
        data_buf[ 0 ] = ACCEL30_SPI_ENABLE;
    }
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_FREG_1, data_buf, 1 );
    
    return err_flag;
}

err_t accel30_set_sniff_gain ( accel30_t *ctx, accel30_gain_t gain )
{
    uint8_t data_buf[ 1 ] = { 0 };
    data_buf[ 0 ] = ACCEL30_DMX_PN_DISABLE;
    err_t err_flag = accel30_generic_write( ctx, ACCEL30_REG_DMX, data_buf, 1 );
    err_flag |= accel30_generic_read( ctx, ACCEL30_REG_GAIN, data_buf, 1 );
    data_buf[ 0 ] &= ACCEL30_GAIN_BIT_MASK;
    data_buf[ 0 ] |= ( gain << 6 );
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_GAIN, data_buf, 1 );
    return err_flag;
}

err_t accel30_set_wake_gain ( accel30_t *ctx, accel30_gain_t gain )
{
    uint8_t data_buf[ 1 ] = { 0 };
    data_buf[ 0 ] = ACCEL30_DMX_RES_BIT_MASK;
    err_t err_flag = accel30_generic_write( ctx, ACCEL30_REG_DMX, data_buf, 1 );
    err_flag |= accel30_generic_read( ctx, ACCEL30_REG_GAIN, data_buf, 1 );
    data_buf[ 0 ] &= ACCEL30_GAIN_BIT_MASK;
    data_buf[ 0 ] |= ( gain << 6 );
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_GAIN, data_buf, 1 );
    return err_flag;
}

err_t accel30_set_resolution_ctrl ( accel30_t *ctx, accel30_resolution_t resolution )
{
    uint8_t data_buf[ 1 ] = { 0 };
    ctx->resolution_cfg = resolution;
    err_t err_flag = accel30_set_mode( ctx, ACCEL30_MODE_STANDBY );
    err_flag |= accel30_generic_read( ctx, ACCEL30_REG_RANGE_C, data_buf, 1 );
    data_buf[ 0 ] &= ACCEL30_RESOLUTION_BIT_MASK;
    data_buf[ 0 ] |= resolution;
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_RANGE_C, data_buf, 1 );
    return err_flag;
}

err_t accel30_set_sample_rate ( accel30_t *ctx, accel30_cwake_t sample_rate )
{
    uint8_t data_buf[ 1 ] = { 0 };  
    err_t err_flag = accel30_set_mode( ctx, ACCEL30_MODE_STANDBY );
    err_flag |= accel30_generic_read( ctx, ACCEL30_REG_WAKE_C, data_buf, 1 );
    data_buf[ 0 ] = sample_rate;
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_WAKE_C, data_buf, 1 );
    return err_flag;
}

err_t accel30_set_sniff_sample_rate ( accel30_t *ctx, accel30_sniff_sr_t sample_rate )
{
    uint8_t data_buf[ 1 ] = { 0 };  
    err_t err_flag = accel30_set_mode( ctx, ACCEL30_MODE_STANDBY );
    err_flag |= accel30_generic_read( ctx, ACCEL30_REG_SNIFF_C, data_buf, 1 );
    data_buf[ 0 ] = sample_rate;
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_SNIFF_C, data_buf, 1 );
    return err_flag;
}

err_t accel30_set_pwr_mode ( accel30_t *ctx, accel30_power_mode_t pwr_mode )
{
    uint8_t data_buf[ 1 ] = { 0 };  
    err_t err_flag = accel30_set_mode( ctx, ACCEL30_MODE_STANDBY );
    err_flag |= accel30_generic_read( ctx, ACCEL30_REG_POWER_MODE, data_buf, 1 );
    data_buf[ 0 ] = pwr_mode;
    err_flag |= accel30_generic_write( ctx, ACCEL30_REG_WAKE_C, data_buf, 1 );
    return err_flag;
}

err_t accel30_get_axis ( accel30_t *ctx, accel30_axis_t *acc_axis )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t err_flag = accel30_generic_read ( ctx, ACCEL30_REG_XOUT_LSB, data_buf, 6 );
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

err_t accel30_get_avg_axes ( accel30_t *ctx, accel30_avg_axis_t *acc_avg_axis )
{
    float range_sel[ 5 ] = { 19.614, 39.228, 78.456, 156.912, 117.684 }; 
    float resolution_sel[ 6 ] = { 32.0, 64.0, 128.0, 512.0, 2048.0, 8192.0 };
    accel30_axis_t acc_axis;
    err_t err_flag = accel30_get_axis( ctx, &acc_axis );
    acc_avg_axis->x = ( float ) acc_axis.x / resolution_sel[ ctx->resolution_cfg ] * range_sel[ ctx->range_cfg ];
    acc_avg_axis->y = ( float ) acc_axis.y / resolution_sel[ ctx->resolution_cfg ] * range_sel[ ctx->range_cfg ];
    acc_avg_axis->z = ( float ) acc_axis.z / resolution_sel[ ctx->resolution_cfg ] * range_sel[ ctx->range_cfg ];
    return err_flag;
}

uint8_t accel30_get_int_pin ( accel30_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

static err_t accel30_i2c_write ( accel30_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel30_i2c_read ( accel30_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel30_spi_write ( accel30_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_WRITE_MASK;
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_adr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel30_spi_read ( accel30_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
