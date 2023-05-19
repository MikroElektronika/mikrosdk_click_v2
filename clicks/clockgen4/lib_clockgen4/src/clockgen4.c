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
 * @file clockgen4.c
 * @brief Clock Gen 4 Click Driver.
 */

#include "clockgen4.h"

/**
 * @brief Write delay of 10 milliseconds.
 */
static void dev_config_delay ( void );

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Clock Gen 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t clockgen4_i2c_write ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Clock Gen 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t clockgen4_i2c_read ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Clock Gen 4 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t clockgen4_spi_write ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Clock Gen 4 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #clockgen4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t clockgen4_spi_read ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void clockgen4_cfg_setup ( clockgen4_cfg_t *cfg ) {
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CLOCKGEN4_I2C_ADR_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = CLOCKGEN4_DRV_SEL_SPI;
}

void clockgen4_drv_interface_selection ( clockgen4_cfg_t *cfg, clockgen4_drv_t drv_sel ) {
    cfg->drv_sel = drv_sel;
}

err_t clockgen4_init ( clockgen4_t *ctx, clockgen4_cfg_t *cfg ) {
    ctx->drv_sel = cfg->drv_sel;

    if ( CLOCKGEN4_DRV_SEL_I2C == ctx->drv_sel ) {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) {
            return I2C_MASTER_ERROR;
        }
        
        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) {
            return I2C_MASTER_ERROR;
        }
        
        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = clockgen4_i2c_read;
        ctx->write_f = clockgen4_i2c_write;
    } 
    else {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cs;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) {
            return SPI_MASTER_ERROR;
        }

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );

        ctx->read_f  = clockgen4_spi_read;
        ctx->write_f = clockgen4_spi_write;
    }
    return 0;
}

err_t clockgen4_default_cfg ( clockgen4_t *ctx ) {
    clockgen4_dev_cfg( ctx, CLOCKGEN4_CLK_OUT | CLOCKGEN4_DEV_CFG_1_EN );
    dev_config_delay( );
    clockgen4_glob_cfg( ctx, CLOCKGEN4_DEV_CFG_2_EN );
    dev_config_delay( );
    clockgen4_fnc_cfg_1( ctx, CLOCKGEN4_AUX_OUT_ACT_H | CLOCKGEN4_REF_CLK_DIV_2 );
    dev_config_delay( );
    clockgen4_fnc_cfg_2( ctx, CLOCKGEN4_CLK_OUT_UNL_U );

    clockgen4_set_ratio ( ctx, 0.005 );
    return CLOCKGEN4_OK;
}

err_t clockgen4_generic_write ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t clockgen4_generic_read ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    return ctx->read_f( ctx, reg, data_out, len );
}

static err_t clockgen4_i2c_write ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t clockgen4_i2c_read ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t clockgen4_spi_write ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = CLOCKGEN4_SPI_CHIP_ADR;
    tx_buf[ 1 ] = reg;
    for ( uint8_t cnt = 0; cnt <= len; cnt++ ) {
        tx_buf[ cnt + 2 ] = data_in[ cnt ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t clockgen4_spi_read ( clockgen4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void clockgen4_dev_ctl ( clockgen4_t *ctx, uint8_t dev_ctl ) {
    dev_ctl &= 0x83;

    clockgen4_generic_write( ctx, CLOCKGEN4_REG_DEV_CTL, &dev_ctl, 1 );
}

void clockgen4_dev_cfg ( clockgen4_t *ctx, uint8_t dev_cfg ) {
    dev_cfg &= 0xE7;

    clockgen4_generic_write( ctx, CLOCKGEN4_REG_DEV_CFG_1, &dev_cfg, 1 );
}

void clockgen4_glob_cfg ( clockgen4_t *ctx, uint8_t glob_cfg ) {
    glob_cfg &= 0x09;

    clockgen4_generic_write ( ctx, CLOCKGEN4_REG_GLOB_CFG, &glob_cfg, 1 );
}

void clockgen4_fnc_cfg_1 ( clockgen4_t *ctx, uint8_t fnc_cfg ) {    
    fnc_cfg &= 0x58;

    clockgen4_generic_write( ctx, CLOCKGEN4_REG_FNC_CFG_1, &fnc_cfg, 1 );
}

void clockgen4_fnc_cfg_2 ( clockgen4_t *ctx, uint8_t fnc_cfg ) {
    fnc_cfg &= 0x10;

    clockgen4_generic_write( ctx, CLOCKGEN4_REG_FNC_CFG_2, &fnc_cfg, 1 );
}

uint32_t clockgen4_set_ratio ( clockgen4_t *ctx, float ratio ) {
    uint32_t sdr;
    uint8_t tx_buf[ 4 ];

    sdr = (uint32_t)( ratio * 1048576.0 );

    tx_buf[ 0 ] = ( uint8_t ) ( sdr >> 24 );
    tx_buf[ 1 ] = ( uint8_t ) ( sdr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( sdr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) sdr;

    clockgen4_generic_write( ctx, CLOCKGEN4_INCR_ENABLE | CLOCKGEN4_REG_M_MSB, tx_buf, 4 );
    return sdr;
}

static void dev_config_delay ( void ) {
    Delay_10ms( );
}

// ------------------------------------------------------------------------ END
