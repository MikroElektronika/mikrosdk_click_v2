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
 * @file dac9.c
 * @brief DAC 9 Click Driver.
 */

#include "dac9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

static uint8_t gain_chk;

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief DAC 9 dev writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dev_write ( dac9_t *ctx, uint8_t reg, uint16_t data_in );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

/**
 * @brief DAC 9 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t dac9_i2c_write ( dac9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 9 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t dac9_i2c_read ( dac9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DAC 9 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t dac9_spi_write ( dac9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 9 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t dac9_spi_read ( dac9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void dac9_cfg_setup ( dac9_cfg_t *cfg ) {
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DAC9_I2C_ADR_AGND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = DAC9_DRV_SEL_SPI;
}

void dac9_drv_interface_selection ( dac9_cfg_t *cfg, dac9_drv_t drv_sel ) {
    cfg->drv_sel = drv_sel;
}

err_t dac9_init ( dac9_t *ctx, dac9_cfg_t *cfg ) {
    ctx->drv_sel = cfg->drv_sel;

    if ( DAC9_DRV_SEL_I2C == ctx->drv_sel ) {
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

        ctx->read_f  = dac9_i2c_read;
        ctx->write_f = dac9_i2c_write;
        digital_out_t cs;
        digital_out_init( &cs, cfg->cs);
        digital_out_low( &cs );
    } else {
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

        ctx->read_f  = dac9_spi_read;
        ctx->write_f = dac9_spi_write;
    }

    return 0;
}

err_t dac9_generic_write ( dac9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t dac9_generic_read ( dac9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    return ctx->read_f( ctx, reg, data_out, len );
}

static err_t dac9_i2c_write ( dac9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

static err_t dac9_i2c_read ( dac9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t dac9_spi_write ( dac9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t dac9_spi_read ( dac9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t dac9_enable_sync ( dac9_t *ctx, uint8_t en_sync ) {
    err_t error_flag;

    if ( en_sync == DAC9_SYNC_ENABLE ) {
        error_flag = dev_write( ctx, DAC9_REG_SYNC, DAC9_SYNC_ENABLE );
    } else if ( en_sync == DAC9_SYNC_DISABLE ) {
        error_flag =  dev_write( ctx, DAC9_REG_SYNC, DAC9_SYNC_DISABLE );
    }

    return error_flag;
}

err_t dac9_set_config ( dac9_t *ctx, uint16_t en_ref_pwdwn, uint16_t en_dac_pwdwn ) {
    err_t error_flag;
    uint8_t rx_buf[ 2 ];
    uint16_t tmp;

    en_ref_pwdwn &= DAC9_CONFIG_REF_PWDWN_BIT_MASK;
    en_dac_pwdwn &= DAC9_CONFIG_DAC_PWDWN_BIT_MASK;

    if ( ctx->drv_sel == DAC9_DRV_SEL_I2C) { 
        dac9_i2c_read( ctx, DAC9_REG_CONFIG, rx_buf, 2 );
        tmp = ( uint16_t ) ( rx_buf[ 0 ] << 8 );
        tmp |= ( uint16_t ) rx_buf[ 1 ];
    }

    if ( ( en_ref_pwdwn & en_dac_pwdwn ) >
         ( DAC9_CONFIG_REF_PWDWN_BIT_MASK | DAC9_CONFIG_DAC_PWDWN_BIT_MASK )
       ) {
        error_flag = DAC9_ERROR;
    } else {
        tmp |= ( uint16_t ) en_ref_pwdwn;
        tmp |= ( uint16_t ) en_dac_pwdwn;
        error_flag = dev_write( ctx, DAC9_REG_CONFIG, tmp );
    }

    return error_flag;
}

err_t dac9_set_gain ( dac9_t *ctx, uint16_t en_ref_div, uint16_t en_buf_gain ) {
    err_t error_flag;
    uint8_t rx_buf[ 2 ];
    uint16_t tmp;

    gain_chk = en_buf_gain;

    if ( ctx->drv_sel == DAC9_DRV_SEL_I2C) { 
        dac9_i2c_read( ctx, DAC9_REG_GAIN, rx_buf, 2 );
        tmp = ( uint16_t ) ( rx_buf[ 0 ] << 8 );
        tmp |= ( uint16_t ) rx_buf[ 1 ];
    }

    if ( ( en_ref_div & en_buf_gain ) >
         ( DAC9_GAIN_REF_DIV_BIT_MASK | DAC9_GAIN_BUFF_GAIN_BIT_MASK )
       ) {
        error_flag = DAC9_ERROR;
    } else {
        tmp |= ( uint16_t ) en_ref_div;
        tmp |= ( uint16_t ) en_buf_gain;
        error_flag = dev_write( ctx, DAC9_REG_GAIN, tmp );
    }

    return error_flag;
}

void dac9_set_synchronously_load ( dac9_t *ctx ) {
    dev_write( ctx, DAC9_REG_TRIGGER, DAC9_TRIGGER_LDAC );
}

void dac9_soft_reset ( dac9_t *ctx ) {
    dev_write( ctx, DAC9_REG_TRIGGER, DAC9_TRIGGER_SOFT_RESET );
}

uint8_t dac9_get_ref_alarm ( dac9_t *ctx ) {
    uint8_t ref_alarm;
    uint8_t rx_buf[ 2 ];
    uint16_t status_val;

    if ( ctx->drv_sel == DAC9_DRV_SEL_I2C) { 
        dac9_i2c_read( ctx, DAC9_REG_STATUS, rx_buf, 2 );
        status_val = ( uint16_t ) ( rx_buf[ 0 ] << 8 );
        status_val |= ( uint16_t ) rx_buf[ 1 ];
     }
    status_val &= DAC9_STATUS_REF_ALARM_BIT_MASK;

    ref_alarm = ( uint8_t ) status_val;

    return ref_alarm;
}

err_t dac9_set_vout ( dac9_t *ctx, uint16_t vout_mv ) {
    err_t error_flag;
    float v_data;
    uint16_t vout_data;

    if ( ( gain_chk == DAC9_GAIN_BUFF_GAIN_2 ) && ( vout_mv > 2500 ) 
       || ( gain_chk == DAC9_GAIN_BUFF_GAIN_1 ) && ( vout_mv > 1250 ) ) {
        error_flag = DAC9_ERROR;
    } else {
        v_data = ( float ) vout_mv;
        
        if ( gain_chk == DAC9_GAIN_BUFF_GAIN_2 ) {
            v_data *= 26.2144;
        } else {
            v_data *= 52.4288;
        }
        vout_data = ( uint16_t ) v_data;

        error_flag = dev_write( ctx, DAC9_REG_DAC, vout_data );
    }

    return error_flag;
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

err_t dev_write ( dac9_t *ctx, uint8_t reg, uint16_t data_in ) {
    uint8_t tx_buf[ 2 ];
    tx_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) data_in;
    err_t error_flag = dac9_generic_write( ctx, reg, tx_buf, 2 );
    return error_flag;
}

// ------------------------------------------------------------------------ END
