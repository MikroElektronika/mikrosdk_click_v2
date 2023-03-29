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
 * @file accel21.c
 * @brief Accel 21 Click Driver.
 */

#include "accel21.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                       0x00

/**
 * @brief Communication bitmask.
 * @details Definition of communication multiple read bitmask.
 */
#define SPI_READ_MASK               0x80
#define SPI_MULTIPLE_READ_BIT_MASK  0x40
#define I2C_MULTIPLE_READ_BIT_MASK  0x80

/**
 * @brief Accel 21 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel21_i2c_write ( accel21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 21 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel21_i2c_read ( accel21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 21 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel21_spi_write ( accel21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 21 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel21_spi_read ( accel21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel21_cfg_setup ( accel21_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL21_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL21_DRV_SEL_I2C;
}

void accel21_drv_interface_selection ( accel21_cfg_t *cfg, accel21_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel21_init ( accel21_t *ctx, accel21_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL21_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel21_i2c_read;
        ctx->write_f = accel21_i2c_write;
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

        ctx->read_f  = accel21_spi_read;
        ctx->write_f = accel21_spi_write;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->in1, cfg->in1 );
    digital_in_init( &ctx->in2, cfg->in2 );

    digital_out_high( &ctx->rst );

    return ACCEL21_OK;
}

err_t accel21_default_cfg ( accel21_t *ctx ) 
{
    accel21_config_t config;
    config.odr  = ACCEL21_CTRL_REG1_ODR_25_Hz;
    config.lpen = ACCEL21_CTRL_REG1_LPEN_DISABLE;
    config.zen  = ACCEL21_CTRL_REG1_XYZEN_ENABLE;
    config.yen  = ACCEL21_CTRL_REG1_XYZEN_ENABLE;
    config.xen  = ACCEL21_CTRL_REG1_XYZEN_ENABLE;
    config.bdu  = ACCEL21_CTRL_REG4_BDU_NOT_UPDATE;
    config.fs   = ACCEL21_CTRL_REG4_FS_2_g;
    config.hr   = ACCEL21_CTRL_REG4_HR_ENABLE;
    return accel21_set_config ( ctx, config );
}

err_t accel21_generic_write ( accel21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel21_generic_read ( accel21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel21_get_temp_status ( accel21_t *ctx, uint8_t *temp_status ) 
{
    return accel21_generic_read( ctx, ACCEL21_REG_STATUS_AUX, temp_status, 1 );
}

err_t accel21_check_temp_data_ready ( accel21_t *ctx, uint8_t *temp_data_ready ) 
{
    uint8_t temp_status = DUMMY;
    err_t err_flag = accel21_get_temp_status( ctx, &temp_status );
    *temp_data_ready = ( temp_status & ACCEL21_STATUS_AUX_TDA_BIT_MASK ) >> 2;
    return err_flag;
}

err_t accel21_enable_temp_data ( accel21_t *ctx ) 
{
    uint8_t data_buf[ 1 ] = { 0 };
    err_t err_flag = accel21_generic_read( ctx, ACCEL21_REG_TEMP_CFG, data_buf, 1 );
    data_buf[ 0 ] |= ACCEL21_TEMP_CFG_TEMP_EN_BIT_MASK;
    accel21_generic_write( ctx, ACCEL21_REG_TEMP_CFG, data_buf, 1 );
    return err_flag;
}

err_t accel21_get_temp_data_ovr ( accel21_t *ctx, uint8_t *temp_data_ovr ) 
{
    uint8_t temp_status = DUMMY;
    err_t err_flag = accel21_get_temp_status( ctx, &temp_status );
    *temp_data_ovr = ( temp_status & ACCEL21_STATUS_AUX_TOR_BIT_MASK ) >> 6;
    return err_flag;
}

err_t accel21_get_temp_data ( accel21_t *ctx, int16_t *temp_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t tmp = DUMMY;
    err_t err_flag = accel21_generic_read( ctx, ACCEL21_REG_OUT_TEMP_L, data_buf, 2 );
    tmp = data_buf[ 1 ];
    tmp <<= 8;
    tmp |= data_buf[ 0 ];
    *temp_data = ( int16_t ) tmp;
    return err_flag;
}

err_t accel21_get_temperature ( accel21_t *ctx, float *temperature ) 
{
    uint8_t op_mode = DUMMY;
    int16_t temp_data = DUMMY;
    err_t err_flag = accel21_get_temp_data( ctx, &temp_data );
    err_flag |= accel21_get_op_mode( ctx, &op_mode );
    
    if ( op_mode == ACCEL21_OP_MODE_NOT_ALLOWED )
    {
        *temperature = DUMMY; 
        err_flag = ACCEL21_ERROR;
    }
    else if ( op_mode == ACCEL21_OP_MODE_LOW_POWER )
    {
        *temperature = ( ( float ) temp_data / 256.0 ) + 25.0;
    }
    else
    {
        *temperature = ( ( ( float ) temp_data / 256.0 ) / 4.0 ) + 25.0;
    }

    return err_flag;
}

err_t accel21_set_op_mode ( accel21_t *ctx, uint8_t op_mode ) 
{
    uint8_t data_buf[ 1 ] = { 0 };
    err_t err_flag = accel21_generic_read( ctx, ACCEL21_REG_CTRL_REG1, data_buf, 1 );
    data_buf[ 0 ] &= ~ACCEL21_CTRL_OP_MODE_BIT_MASK;
    data_buf[ 0 ] |= ( op_mode << 2 ) & ACCEL21_CTRL_OP_MODE_BIT_MASK;
    err_flag |= accel21_generic_write( ctx, ACCEL21_REG_CTRL_REG1, data_buf, 1 );

    err_flag |= accel21_generic_read( ctx, ACCEL21_REG_CTRL_REG3, data_buf, 1 );
    data_buf[ 0 ] &= ~ACCEL21_CTRL_OP_MODE_BIT_MASK;
    data_buf[ 0 ] |= ( op_mode << 3 ) & ACCEL21_CTRL_OP_MODE_BIT_MASK;
    err_flag |= accel21_generic_write( ctx, ACCEL21_REG_CTRL_REG3, data_buf, 1 );
    return err_flag;
}

err_t accel21_get_op_mode ( accel21_t *ctx, uint8_t *op_mode ) 
{
    uint8_t data_buf[ 1 ] = { 0 };
    err_t err_flag = accel21_generic_read( ctx, ACCEL21_REG_CTRL_REG1, &data_buf, 1 );
    *op_mode = ( data_buf[ 0 ] & ACCEL21_CTRL_OP_MODE_BIT_MASK ) >> 2;
    err_flag |= accel21_generic_read( ctx, ACCEL21_REG_CTRL_REG4, &data_buf, 1 );
    *op_mode |= ( data_buf[ 0 ] & ACCEL21_CTRL_OP_MODE_BIT_MASK ) >> 3;
    return err_flag;
}

err_t accel21_get_device_id ( accel21_t *ctx, uint8_t *device_id ) 
{
    return accel21_generic_read( ctx, ACCEL21_REG_WHO_AM_I, device_id, 1 );
}

err_t accel21_check_id ( accel21_t *ctx ) 
{
    uint8_t device_id = DUMMY;
    err_t err_flag = accel21_get_device_id( ctx, &device_id );
    if ( device_id != ACCEL21_WHO_AM_I )
    {
        err_flag = ACCEL21_ERROR;    
    }
    return err_flag;
}

err_t accel21_get_status ( accel21_t *ctx, uint8_t *status ) 
{    
    return accel21_generic_read( ctx, ACCEL21_REG_STATUS, status, 1 );
}

err_t accel21_check_data_overrun ( accel21_t *ctx, uint8_t *data_overrun ) 
{
    uint8_t tmp_status = DUMMY;
    err_t err_flag = accel21_get_status( ctx, &tmp_status );
    *data_overrun = ( tmp_status & ACCEL21_STATUS_DATA_OVERRUN_BIT_MASK ) >> 3;
    return err_flag;
}

err_t accel21_check_new_data ( accel21_t *ctx, uint8_t *new_data_avl ) 
{
    uint8_t tmp_status;
    err_t err_flag = accel21_get_status( ctx, &tmp_status );
    *new_data_avl = ( tmp_status & ACCEL21_STATUS_NEW_DATA_AVL_BIT_MASK ) >> 7;
    return err_flag;
}

err_t accel21_set_config ( accel21_t *ctx, accel21_config_t config )
{
    uint8_t data_buf[ 1 ] = { 0 };
    data_buf[ 0 ]  = ( config.odr  << 4 ) & ACCEL21_CTRL_REG1_ODR_BIT_MASK;
    data_buf[ 0 ] |= ( config.lpen << 3 ) & ACCEL21_CTRL_REG1_LPEN_BIT_MASK;
    data_buf[ 0 ] |= ( config.zen  << 2 ) & ACCEL21_CTRL_REG1_ZEN_BIT_MASK;
    data_buf[ 0 ] |= ( config.yen  << 1 ) & ACCEL21_CTRL_REG1_YEN_BIT_MASK;
    data_buf[ 0 ] |=   config.xen         & ACCEL21_CTRL_REG1_XEN_BIT_MASK;
    err_t err_flag = accel21_generic_write( ctx, ACCEL21_REG_CTRL_REG1, data_buf, 1 );

    data_buf[ 0 ]  = ( config.bdu << 7 ) & ACCEL21_CTRL_REG4_BDU_BIT_MASK;
    data_buf[ 0 ] |= ( config.fs  << 4 ) & ACCEL21_CTRL_REG4_FS_BIT_MASK;
    data_buf[ 0 ] |= ( config.hr  << 3 ) & ACCEL21_CTRL_REG1_HR_BIT_MASK;
    err_flag |= accel21_generic_write( ctx, ACCEL21_REG_CTRL_REG4, data_buf, 1 );
    return err_flag;
}

err_t accel21_get_axis ( accel21_t *ctx, accel21_axis_t *acc_axis )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t err_flag = accel21_generic_read ( ctx, ACCEL21_REG_OUT_X_L, data_buf, 6 );
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

uint8_t accel21_get_in1_pin ( accel21_t *ctx )
{
    return digital_in_read ( &ctx->in1 );
}

uint8_t accel21_get_in2_pin ( accel21_t *ctx )
{
    return digital_in_read ( &ctx->in2 );
}

static err_t accel21_i2c_write ( accel21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t accel21_i2c_read ( accel21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | I2C_MULTIPLE_READ_BIT_MASK;
    return i2c_master_write_then_read( &ctx->i2c, &reg_adr, 1, data_out, len );
}

static err_t accel21_spi_write ( accel21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t reg_adr = reg;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_adr, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t accel21_spi_read ( accel21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK | SPI_MULTIPLE_READ_BIT_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
