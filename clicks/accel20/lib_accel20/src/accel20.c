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
 * @file accel20.c
 * @brief Accel 20 Click Driver.
 */

#include "accel20.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Accel 20 configuration delay function.
 * @details This function executes a configuration delay of the 10 milliseconds.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_cfg_delay ( void );

/**
 * @brief Accel 20 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel20_i2c_write ( accel20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 20 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel20_i2c_read ( accel20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Accel 20 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel20_spi_write ( accel20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Accel 20 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #accel20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t accel20_spi_read ( accel20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void accel20_cfg_setup ( accel20_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->i2   = HAL_PIN_NC;
    cfg->trg  = HAL_PIN_NC;
    cfg->i1  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCEL20_SET_DEV_ADDR_VCC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = ACCEL20_DRV_SEL_SPI;
}

void accel20_drv_interface_selection ( accel20_cfg_t *cfg, accel20_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t accel20_init ( accel20_t *ctx, accel20_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( ACCEL20_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = accel20_i2c_read;
        ctx->write_f = accel20_i2c_write;
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

        ctx->read_f  = accel20_spi_read;
        ctx->write_f = accel20_spi_write;
    }

    digital_out_init( &ctx->trg, cfg->trg );
    digital_in_init( &ctx->i2, cfg->i2 );
    digital_in_init( &ctx->i1, cfg->i1 );

    return ACCEL20_OK;
}

err_t accel20_default_cfg ( accel20_t *ctx ) 
{ 
    err_t err_flag = accel20_set_operating_mode( ctx, ACCEL20_CNTL1_OP_MODE_STB );
    dev_cfg_delay( );
    
    err_flag |= accel20_enable_int_1_pin( ctx );
    dev_cfg_delay( );
    
    accel20_set_output_data_rate( ctx, ACCEL20_ODCNTL_ODR_50_Hz );
    dev_cfg_delay( );
    
    err_flag |= accel20_set_operating_mode( ctx, ACCEL20_CNTL1_OP_MODE_HP );
    dev_cfg_delay( );
    
    accel20_set_trigger( ctx, ACCEL20_TRIGGER_DISABLE );
    dev_cfg_delay( );
    
    return err_flag;
}

err_t accel20_generic_write ( accel20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t accel20_generic_read ( accel20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t accel20_soft_reset ( accel20_t *ctx )
{
    uint8_t tx_data;
    
    tx_data = ACCEL20_INTERNAL_SOFT_RESET; 
    err_t err_flag = accel20_generic_write( ctx, ACCEL20_REG_INTERNAL, &tx_data, 1 );
    dev_cfg_delay( );
    
    tx_data = ACCEL20_SOFT_RESET_PWR_CYC; 
    err_flag |= accel20_generic_write( ctx, ACCEL20_REG_CNTL2, &tx_data, 1 );
    dev_cfg_delay( );
    
    tx_data = ACCEL20_SOFT_RESET_REBOOT; 
    err_flag |= accel20_generic_write( ctx, ACCEL20_REG_CNTL2, &tx_data, 1 );
    dev_cfg_delay( );

    return err_flag;
}

err_t accel20_check_id ( accel20_t *ctx ) 
{
    uint8_t id_val;
    
    accel20_generic_read( ctx, ACCEL20_REG_WHO_AM_I, &id_val, 1 );
    
    if ( id_val == ACCEL20_CHIP_ID ) 
    {
        return ACCEL20_OK;
    }
    else
    {
        return ACCEL20_ERROR;    
    }
}

uint8_t accel20_data_ready (accel20_t *ctx ) 
{
    uint8_t rx_buf;
    
    accel20_generic_read( ctx, ACCEL20_REG_INS2, &rx_buf, 1 );
    
    rx_buf &= ACCEL20_DATA_READY_BIT_MASK;
    rx_buf >>= 4;

    return rx_buf;
}

err_t accel20_set_operating_mode ( accel20_t *ctx, uint8_t op_mode )
{
    uint8_t data_buf;
    
    op_mode &= ACCEL20_CNTL1_OP_MODE_HP;
    op_mode <<= 6;
    
    err_t err_flag = accel20_generic_read( ctx, ACCEL20_REG_CNTL1, &data_buf, 1 );
    
    data_buf &= ACCEL20_OP_MODE_BIT_MASK;
    data_buf |= op_mode;
    
    err_flag |= accel20_generic_write( ctx, ACCEL20_REG_CNTL1, &data_buf, 1 );
    
    return err_flag;
}

err_t accel20_enable_int_1_pin ( accel20_t *ctx )
{
    uint8_t data_buf;
    
    data_buf = ACCEL20_ENABLE_INT_1; 
    err_t err_flag = accel20_generic_write( ctx, ACCEL20_REG_INC1, &data_buf, 1 );
    
    data_buf = ACCEL20_ENABLE_DATA_READY; 
    err_flag |= accel20_generic_write( ctx, ACCEL20_REG_INC4, &data_buf, 1 );
    
    return err_flag;
}

err_t accel20_enable_int_2_pin ( accel20_t *ctx )
{
    uint8_t data_buf;
    
    data_buf = ACCEL20_ENABLE_INT_1; 
    err_t err_flag = accel20_generic_write( ctx, ACCEL20_REG_INC5, &data_buf, 1 );
    
    data_buf = ACCEL20_ENABLE_DATA_READY; 
    err_flag |= accel20_generic_write( ctx, ACCEL20_REG_INC6, &data_buf, 1 );
    
    return err_flag;
}

err_t accel20_set_accel_range ( accel20_t *ctx, uint8_t range )
{
    uint8_t data_buf;
    
    range &= ACCEL20_CNTL1_RANGE_64g;
    range <<= 3;
    
    err_t err_flag = accel20_generic_read( ctx, ACCEL20_REG_CNTL1, &data_buf, 1 );
    
    data_buf &= ACCEL20_RANGE_BIT_MASK;
    data_buf |= range;
    
    err_flag |= accel20_generic_write( ctx, ACCEL20_REG_CNTL1, &data_buf, 1 );
    
    return err_flag;
}

err_t accel20_set_output_data_rate ( accel20_t *ctx, uint8_t odr )
{
    uint8_t data_buf;
    
    odr &= ACCEL20_ODR_BIT_MASK;
    
    err_t err_flag = accel20_generic_read( ctx, ACCEL20_REG_ODCNTL, &data_buf, 1 );
    
    data_buf &= ACCEL20_ODR_BIT_MASK;
    data_buf |= odr;
    
    err_flag |= accel20_generic_write( ctx, ACCEL20_REG_ODCNTL, &data_buf, 1 );
    
    return err_flag;
}

err_t accel20_get_axis_data ( accel20_t *ctx, accel20_axis_t *axis )
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    
    err_t err_flag = accel20_generic_read( ctx, ACCEL20_REG_XOUT_L, rx_buf, 6 );
    
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

err_t accel20_set_trigger ( accel20_t *ctx, uint8_t en_trg ) 
{
    if ( en_trg > ACCEL20_TRIGGER_ENABLE )
    {
        return ACCEL20_ERROR;   
    }
    
    digital_out_write( &ctx->trg, en_trg ); 
    
    return ACCEL20_OK;
}

uint8_t accel20_get_int_1 ( accel20_t *ctx ) 
{
     return digital_in_read( &ctx->i1 );
}

uint8_t accel20_get_int_2 ( accel20_t *ctx ) 
{
     return digital_in_read( &ctx->i2 );
}

static err_t accel20_i2c_write ( accel20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) 
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t accel20_i2c_read ( accel20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t accel20_spi_write ( accel20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
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

static err_t accel20_spi_read ( accel20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
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
