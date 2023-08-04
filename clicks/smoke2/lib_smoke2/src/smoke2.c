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
 * @file smoke2.c
 * @brief Smoke 2 Click Driver.
 */

#include "smoke2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Smoke 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smoke2_i2c_write ( smoke2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smoke 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smoke2_i2c_read ( smoke2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smoke 2 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smoke2_spi_write ( smoke2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smoke 2 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smoke2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smoke2_spi_read ( smoke2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void read_data_for_calibration ( smoke2_t *ctx );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void smoke2_cfg_setup ( smoke2_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMOKE2_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = SMOKE2_DRV_SEL_I2C;
}

void smoke2_drv_interface_selection ( smoke2_cfg_t *cfg, smoke2_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t smoke2_init ( smoke2_t *ctx, smoke2_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    
    if ( SMOKE2_DRV_SEL_I2C == ctx->drv_sel ) 
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
        ctx->read_f  = smoke2_i2c_read;
        ctx->write_f = smoke2_i2c_write;
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

        ctx->read_f  = smoke2_spi_read;
        ctx->write_f = smoke2_spi_write;
    }
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    return SMOKE2_OK;
}

void smoke2_default_cfg ( smoke2_t *ctx ) 
{
    smoke2_write_data( ctx, 0x11, 0x30A9 );
    smoke2_write_data( ctx, 0x12, 0x0200 );
    smoke2_write_data( ctx, 0x14, 0x011D );
    smoke2_write_data( ctx, 0x15, 0x0000 );
    smoke2_write_data( ctx, 0x17, 0x0009 );
    
    smoke2_write_data( ctx, 0x18, 0x0000 );
    smoke2_write_data( ctx, 0x19, 0x3FFF );
    smoke2_write_data( ctx, 0x1A, 0x3FFF );
    smoke2_write_data( ctx, 0x1B, 0x3FFF );
    smoke2_write_data( ctx, 0x1D, 0x0009 );
    
    smoke2_write_data( ctx, 0x1E, 0x0000 );
    smoke2_write_data( ctx, 0x1F, 0x3FFF );
    smoke2_write_data( ctx, 0x20, 0x3FFF );
    smoke2_write_data( ctx, 0x21, 0x3FFF );
    smoke2_write_data( ctx, 0x22, 0x3539 );
    smoke2_write_data( ctx, 0x23, 0x3536 );
    smoke2_write_data( ctx, 0x24, 0x1530 );
    smoke2_write_data( ctx, 0x25, 0x630C );
    smoke2_write_data( ctx, 0x30, 0x0320 );
    smoke2_write_data( ctx, 0x31, 0x040E );
    smoke2_write_data( ctx, 0x35, 0x0320 );
    smoke2_write_data( ctx, 0x36, 0x040E );
    smoke2_write_data( ctx, 0x39, 0x22F0 );
    smoke2_write_data( ctx, 0x3B, 0x22F0 );
    smoke2_write_data( ctx, 0x3C, 0x31C6 );
    
    smoke2_write_data( ctx, 0x42, 0x1C34 );
    smoke2_write_data( ctx, 0x43, 0xADA5 );
    smoke2_write_data( ctx, 0x44, 0x1C34 );
    smoke2_write_data( ctx, 0x45, 0xADA5 );
    smoke2_write_data( ctx, 0x58, 0x0544 );
    smoke2_write_data( ctx, 0x54, 0x0AA0 );
    
    smoke2_write_data( ctx, 0x5F, 0x0007 );
    
    smoke2_set_mode( ctx, SMOKE2_MODE_PROGRAM );
    smoke2_set_bit( ctx, SMOKE2_REG_SAMPLE_CLK, 7, 1 );
    smoke2_set_bit( ctx, SMOKE2_REG_DATA_ACCESS_CTL, 0, 1 );
    smoke2_set_bit( ctx, SMOKE2_REG_INT_MASK, 5, 0 );
    smoke2_set_bit( ctx, SMOKE2_REG_INT_MASK, 6, 1 );
    smoke2_set_bit( ctx, SMOKE2_REG_INT_MASK, 8, 1 );
    
    smoke2_set_bit( ctx, SMOKE2_REG_GPIO_DRV, 0, 1 );
    smoke2_set_bit( ctx, SMOKE2_REG_GPIO_DRV, 1, 1 );
    smoke2_set_bit( ctx, SMOKE2_REG_GPIO_DRV, 2, 1 );

    smoke2_write_data( ctx, SMOKE2_REG_SLOT_EN, 0x3001 );
    
    smoke2_set_mode( ctx, SMOKE2_MODE_NORMAL );
}

err_t smoke2_generic_write ( smoke2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t smoke2_generic_read ( smoke2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t smoke2_get_int_pin ( smoke2_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

void smoke2_write_data( smoke2_t *ctx, uint8_t reg, uint16_t tx_data ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };
    
    tx_buf[ 0 ] = ( uint8_t ) ( ( tx_data >> 8 ) & 0xFF );
    tx_buf[ 1 ] = ( uint8_t ) ( tx_data & 0xFF );
    
    ctx->write_f( ctx, reg, tx_buf, 2 );
}

uint16_t smoke2_read_data( smoke2_t *ctx, uint8_t reg ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    uint16_t out_data = 0;
    ctx->read_f( ctx, reg, rx_buf, 2 );
    out_data = rx_buf[ 0 ];
    out_data <<= 8;
    out_data |= rx_buf[ 1 ];
    return out_data;
}

void smoke2_set_bit ( smoke2_t *ctx, uint8_t reg, uint8_t bit_num , uint8_t val ) 
{
    uint16_t reg_val = smoke2_read_data( ctx, reg );

    if ( val & 1 ) 
    {
        reg_val |= ( 1 << bit_num );
    }
    else 
    {
        reg_val &= ~( 1 << bit_num );
    }
    smoke2_write_data( ctx, reg, reg_val );
}

uint8_t smoke2_get_bit ( smoke2_t *ctx, uint8_t reg, uint8_t bit_num ) 
{
    uint16_t reg_val = smoke2_read_data( ctx, reg );
    return ( reg_val >> bit_num ) & 0x01;
}

void smoke2_set_mode ( smoke2_t *ctx, uint8_t mode ) 
{
    smoke2_write_data( ctx, SMOKE2_REG_MODE, ( mode & 0x03 ) );
}

void smoke2_get_int ( smoke2_t *ctx, uint8_t *fifo, uint8_t *slot_a, uint8_t *slot_b ) 
{
    uint16_t int_val = smoke2_read_data( ctx, SMOKE2_REG_STATUS );

    *fifo = ( int_val >> 8 ) & 0xFF;
    *slot_a = ( int_val >> 5 ) & 0x01;
    *slot_b = ( int_val >> 6 ) & 0x01;

    smoke2_write_data( ctx, SMOKE2_REG_STATUS, 0xFFFF );
    int_val = smoke2_read_data( ctx, SMOKE2_REG_STATUS );
}

uint16_t smoke2_read_sens_data ( smoke2_t *ctx, uint8_t slot, uint8_t chn ) 
{
    uint16_t read_value = 0;
    smoke2_set_bit( ctx, SMOKE2_REG_DATA_ACCESS_CTL, 1 + slot, 1 );
    read_value = smoke2_read_data( ctx, SMOKE2_REG_SLOTA_CH1 + slot + chn );
    smoke2_set_bit( ctx, SMOKE2_REG_DATA_ACCESS_CTL, 1 + slot, 0 );
    return read_value;
}

void smoke2_soft_reset ( smoke2_t *ctx ) 
{
    smoke2_write_data( ctx, SMOKE2_REG_SW_RESET, 0x0001 );
    Delay_100ms( );
}

uint16_t smoke2_smoke_calibration ( smoke2_t *ctx, uint16_t threshold ) 
{
    uint8_t enabled_slot = 0;
    
    ctx->threshold_value = threshold;
    enabled_slot = smoke2_read_data( ctx, SMOKE2_REG_SLOT_EN );
    
    if ( 0x0001 == ( enabled_slot & 0x0001 ) ) 
    {
        ctx->enabled_slot = SMOKE2_SLOT_A;
    }
    else if ( 0x0020 == ( enabled_slot & 0x0020 ) ) 
    { 
        ctx->enabled_slot = SMOKE2_SLOT_B;
    }
    read_data_for_calibration( ctx );    
    return ctx->calibration_value;
}

uint8_t smoke2_check_smoke ( smoke2_t *ctx ) 
{
    uint16_t sens_data;
    if ( 0 == smoke2_get_int_pin( ctx ) ) 
    {
        sens_data = smoke2_read_sens_data( ctx, ctx->enabled_slot, SMOKE2_CHN_1 );
        if ( sens_data > ( ctx->calibration_value + ctx->threshold_value  ) ) 
        {
            return SMOKE2_SMOKE_DETECTED;
        }
        else 
        {
            return SMOKE2_SMOKE_NOT_DETECTED;
        }
    }
    return 0;
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static err_t smoke2_i2c_write ( smoke2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t smoke2_i2c_read ( smoke2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t smoke2_spi_write ( smoke2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t write_cmd = ( reg << 1 ) | SMOKE2_WRITE_CMD;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &write_cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t smoke2_spi_read ( smoke2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t read_cmd = ( reg << 1 ) | SMOKE2_READ_CMD;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &read_cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static void read_data_for_calibration ( smoke2_t *ctx ) 
{    
    uint32_t sum = 0;
    for ( uint8_t cnt = 0; cnt < 100; cnt++ ) 
    {        
        if ( 0 == smoke2_get_int_pin( ctx ) ) 
        {
            sum += smoke2_read_sens_data( ctx, ctx->enabled_slot, SMOKE2_CHN_1 );
        }
    }
    ctx->calibration_value = sum / 100;
}
// ------------------------------------------------------------------------ END
