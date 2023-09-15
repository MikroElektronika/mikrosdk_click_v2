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
 * @file dac15.c
 * @brief DAC 15 Click Driver.
 */

#include "dac15.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief DAC 15 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac15_i2c_write ( dac15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 15 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac15_i2c_read ( dac15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DAC 15 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac15_spi_write ( dac15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DAC 15 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac15_spi_read ( dac15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void dac15_cfg_setup ( dac15_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DAC15_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = DAC15_DRV_SEL_I2C;
    cfg->vref = DAC15_VREF_3V3;
}

void dac15_drv_interface_selection ( dac15_cfg_t *cfg, dac15_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t dac15_init ( dac15_t *ctx, dac15_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = DAC15_VREF_3V3;
    
    if ( DAC15_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = dac15_i2c_read;
        ctx->write_f = dac15_i2c_write;
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

        ctx->read_f  = dac15_spi_read;
        ctx->write_f = dac15_spi_write;
    }
    
    digital_out_init( &ctx->rst, cfg->rst );
    return DAC15_OK;
}

err_t dac15_default_cfg ( dac15_t *ctx ) 
{
    err_t err_flag = DAC15_OK;
    
    dac15_power_up_to_midscale( ctx );
    Delay_10ms( );
    
    if ( ctx->drv_sel == DAC15_DRV_SEL_I2C )
    {
        uint16_t device_id = DUMMY;
        err_flag |= dac15_get_device_id( ctx, &device_id );
        
        if ( DAC15_DEVICE_ID != device_id )
        {
            return DAC15_ERROR;
        }
    }
    
    err_flag |= dac15_soft_reset( ctx );
    Delay_10ms( );
    
    err_flag |= dac15_set_sync_mode( ctx );
    Delay_10ms( );
    
    err_flag |= dac15_write_reg( ctx, DAC15_REG_CONFIG, DAC15_CONFIG_REF_PWDWN  | 
                                                        DAC15_CONFIG_DAC_B_PWUP |
                                                        DAC15_CONFIG_DAC_A_PWUP );
    Delay_10ms( );
    
    err_flag |= dac15_write_reg( ctx, DAC15_REG_GAIN, DAC15_GAIN_REF_DIV_2     |
                                                      DAC15_GAIN_BUFF_B_GAIN_2 |
                                                      DAC15_GAIN_BUFF_A_GAIN_2 );
    Delay_10ms( );
    return err_flag;
}

err_t dac15_generic_write ( dac15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t dac15_generic_read ( dac15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t dac15_write_reg ( dac15_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    err_t err_flag = DAC15_OK;
    if ( DAC15_REG_DAC_B_DATA < reg )
    {
        err_flag = DAC15_ERROR;
    }
    else
    {
        uint8_t data_buf[ 2 ] = { 0 };
        data_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
        data_buf[ 1 ] = ( uint8_t )   data_in;
        err_flag |= dac15_generic_write( ctx, reg, data_buf, 2 );
    }
    return err_flag;
}

err_t dac15_read_reg ( dac15_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    err_t err_flag = DAC15_OK;
    if ( DAC15_REG_DAC_B_DATA < reg )
    {
        err_flag = DAC15_ERROR;
    }
    else
    {
        uint8_t data_buf[ 2 ] = { 0 };
        err_flag |= dac15_generic_read( ctx, reg, data_buf, 2 );
        *data_out = data_buf[ 0 ];
        *data_out <<= 8;
        *data_out |= data_buf[ 1 ];
    }
    return err_flag;
}

void dac15_power_up_to_zero_scale ( dac15_t *ctx ) 
{
    digital_out_low( &ctx->rst );
}

void dac15_power_up_to_midscale ( dac15_t *ctx ) 
{
    digital_out_high( &ctx->rst );
}

err_t dac15_get_device_id ( dac15_t *ctx, uint16_t *device_id ) 
{
    return dac15_read_reg( ctx, DAC15_REG_DEVID, device_id );
}

err_t dac15_set_sync_mode ( dac15_t *ctx ) 
{
    return dac15_write_reg( ctx, DAC15_REG_TRIGGER, DAC15_TRIGGER_LDA_SYNC_LOAD_DAC );
}

err_t dac15_soft_reset ( dac15_t *ctx ) 
{
    return dac15_write_reg( ctx, DAC15_REG_TRIGGER, DAC15_TRIGGER_SOFT_RESET );
}

err_t dac15_set_dac_data ( dac15_t *ctx, uint8_t dac_sel, uint16_t dac_data ) 
{
    err_t err_flag = DAC15_OK;
    if ( DAC15_SET_DAC_B < dac_sel )
    {
        err_flag = DAC15_ERROR;
    }
    else
    {
        err_flag |= dac15_write_reg( ctx, DAC15_REG_DAC_A_DATA + dac_sel, dac_data );
    }
    return err_flag;
}

err_t dac15_get_dac_data ( dac15_t *ctx, uint8_t dac_sel, uint16_t *dac_data ) 
{
    err_t err_flag = DAC15_OK;
    if ( DAC15_SET_DAC_B < dac_sel )
    {
        err_flag = DAC15_ERROR;
    }
    else
    {
        err_flag |= dac15_read_reg( ctx, DAC15_REG_DAC_A_DATA + dac_sel, dac_data );
    }
    return err_flag;
}

err_t dac15_set_dac_vout ( dac15_t *ctx, uint8_t dac_sel, float vtg ) 
{
    err_t err_flag = DAC15_OK;
    if ( ( DAC15_SET_DAC_B < dac_sel ) || ( ctx->vref < vtg ) )
    {
        err_flag = DAC15_ERROR;
    }
    else
    {
        uint16_t dac_data = DUMMY;
        dac_data = ( uint16_t ) ( ( vtg / ctx->vref ) * DAC15_DAC_RES_16BIT );
        err_flag |= dac15_write_reg( ctx, DAC15_REG_DAC_A_DATA + dac_sel, dac_data );
    }
    return err_flag;
}

err_t dac15_get_dac_vout ( dac15_t *ctx, uint8_t dac_sel, float *vtg ) 
{
    err_t err_flag = DAC15_OK;
    if ( DAC15_SET_DAC_B < dac_sel )
    {
        err_flag = DAC15_ERROR;
    }
    else
    {
        uint16_t dac_data = DUMMY;
        err_flag |= dac15_get_dac_data( ctx, dac_sel, &dac_data );
        *vtg = ( float ) dac_data;
        *vtg /= ( float ) DAC15_DAC_RES_16BIT;
        *vtg *= ctx->vref;
    }
    return err_flag;
}

static err_t dac15_i2c_write ( dac15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t dac15_i2c_read ( dac15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t dac15_spi_write ( dac15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &reg, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

static err_t dac15_spi_read ( dac15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return DAC15_ERROR;
}

// ------------------------------------------------------------------------ END
