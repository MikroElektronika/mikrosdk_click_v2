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
 * @file dac14.c
 * @brief DAC 14 Click Driver.
 */

#include "dac14.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief DAC 14 I2C writing function.
 * @details This function writes a desired data word to the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac14_i2c_write ( dac14_t *ctx, uint8_t reg, uint16_t *data_in );

/**
 * @brief DAC 14 I2C reading function.
 * @details This function reads data word from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac14_i2c_read ( dac14_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 14 SPI writing function.
 * @details This function writes a desired data word to the selected register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac14_spi_write ( dac14_t *ctx, uint8_t reg, uint16_t *data_in );

/**
 * @brief DAC 14 SPI reading function.
 * @details This function reads data word from the selected register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac14_spi_read ( dac14_t *ctx, uint8_t reg, uint16_t *data_out );

void dac14_cfg_setup ( dac14_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DAC14_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = DAC14_DRV_SEL_I2C;
}

void dac14_drv_interface_selection ( dac14_cfg_t *cfg, dac14_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t dac14_init ( dac14_t *ctx, dac14_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( DAC14_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = dac14_i2c_read;
        ctx->write_f = dac14_i2c_write;
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

        ctx->read_f  = dac14_spi_read;
        ctx->write_f = dac14_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return DAC14_OK;
}

err_t dac14_default_cfg ( dac14_t *ctx ) 
{
    err_t error_flag = DAC14_OK;
    DAC14_SET_DATA_SAMPLE_EDGE;
    if ( DAC14_ERROR == dac14_check_communication ( ctx ) )
    {
        return DAC14_ERROR;
    }
    // enable VOUT for both channels
    error_flag |= dac14_set_dac_vout_enable ( ctx, DAC14_SEL_DAC_0, DAC14_EN_VOUT_POWER_UP );
    error_flag |= dac14_set_dac_vout_enable ( ctx, DAC14_SEL_DAC_1, DAC14_EN_VOUT_POWER_UP );
    Delay_100ms ( );
    // set DAC vref to VDD
    error_flag |= dac14_set_dac_vref ( ctx, DAC14_SEL_DAC_0, DAC14_VREF_VDD );
    error_flag |= dac14_write_register ( ctx, DAC14_SEL_DAC_1, DAC14_VREF_VDD );
    // stop function generator for OUT1
    error_flag |= dac14_stop_function_gen ( ctx, DAC14_SEL_DAC_1 );
    Delay_100ms ( );
    // set margin levels and a function generator config to output 
    // triangular wave on OUT1 with a frequency of about 4kHz
    error_flag |= dac14_set_dac_margins ( ctx, DAC14_SEL_DAC_1, DAC14_DAC_DATA_MIN, DAC14_DAC_DATA_MAX );
    error_flag |= dac14_config_function_gen ( ctx, DAC14_SEL_DAC_1, DAC14_WAVEFORM_TRIANGULAR,
                                              DAC14_CODE_STEP_32_LSB, DAC14_SLEW_RATE_4_US );
    Delay_100ms ( );
    // start function generator for OUT1
    error_flag |= dac14_start_function_gen ( ctx, DAC14_SEL_DAC_1 );
    Delay_100ms ( );
    return error_flag;
}

err_t dac14_write_register ( dac14_t *ctx, uint8_t reg, uint16_t data_in )
{
    return ctx->write_f ( ctx, reg, &data_in );
}

err_t dac14_read_register ( dac14_t *ctx, uint8_t reg, uint16_t *data_out )
{
    return ctx->read_f ( ctx, reg, data_out );
}

uint8_t dac14_get_int_pin ( dac14_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t dac14_check_communication ( dac14_t *ctx )
{
    err_t error_flag = DAC14_OK;
    uint16_t reg_data;
    if ( DAC14_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        reg_data = DAC14_IC_SDO_DIS;
    }
    else
    {
        reg_data = DAC14_IC_SDO_EN;
    }
    error_flag |= dac14_write_register ( ctx, DAC14_REG_INTERFACE_CONFIG, reg_data );
    if ( DAC14_OK == error_flag )
    {
        Delay_10ms ( );
        error_flag |= dac14_read_register ( ctx, DAC14_REG_GENERAL_STATUS, &reg_data );
        if ( ( DAC14_OK == error_flag ) && ( DAC14_DEVICE_ID != ( reg_data & DAC14_DEVICE_ID_MASK ) ) )
        {
            error_flag = DAC14_ERROR;
        }
    }
    return error_flag;
}

err_t dac14_set_dac_vout_enable ( dac14_t *ctx, uint8_t dac, uint8_t vout_pdn )
{
    if ( ( dac > DAC14_SEL_DAC_1 ) || ( vout_pdn > DAC14_EN_VOUT_POWER_DOWN_HI_Z_AGND ) )
    {
        return DAC14_ERROR;
    }
    err_t error_flag = DAC14_OK;
    uint16_t reg_data;
    error_flag |= dac14_read_register ( ctx, DAC14_REG_COMMON_CONFIG, &reg_data );
    if ( DAC14_OK == error_flag )
    {
        if ( DAC14_SEL_DAC_1 == dac )
        {
            reg_data &= ( ~DAC14_CC_VOUT_PDN_1_MASK );
            reg_data |= ( ( ( uint16_t ) vout_pdn << 1 ) & DAC14_CC_VOUT_PDN_1_MASK );
        }
        else
        {
            reg_data &= ( ~DAC14_CC_VOUT_PDN_0_MASK );
            reg_data |= ( ( ( uint16_t ) vout_pdn << 10 ) & DAC14_CC_VOUT_PDN_0_MASK );
        }
        error_flag |= dac14_write_register ( ctx, DAC14_REG_COMMON_CONFIG, reg_data );
    }
    return error_flag;
}

err_t dac14_set_dac_vref ( dac14_t *ctx, uint8_t dac, uint8_t vref )
{
    if ( ( dac > DAC14_SEL_DAC_1 ) || ( vref > DAC14_VREF_INT_4X ) )
    {
        return DAC14_ERROR;
    }
    err_t error_flag = DAC14_OK;
    uint16_t reg_data;
    uint8_t reg_addr = DAC14_REG_DAC0_VOUT_CMP_CONFIG;
    if ( DAC14_SEL_DAC_1 == dac )
    {
        reg_addr = DAC14_REG_DAC1_VOUT_CMP_CONFIG;
    }
    error_flag |= dac14_read_register ( ctx, reg_addr, &reg_data );
    if ( DAC14_OK == error_flag )
    {
        reg_data &= ( ~DAC14_VCC_VOUT_GAIN_X_MASK );
        reg_data |= ( ( ( uint16_t ) vref << 10 ) & DAC14_VCC_VOUT_GAIN_X_MASK );
        error_flag |= dac14_write_register ( ctx, reg_addr, reg_data );
    }
    return error_flag;
}

err_t dac14_set_dac_margins ( dac14_t *ctx, uint8_t dac, uint16_t margin_l, uint16_t margin_h )
{
    if ( ( dac > DAC14_SEL_DAC_1 ) || ( margin_l > margin_h ) || 
         ( margin_l > DAC14_DAC_DATA_MAX ) || ( margin_h > DAC14_DAC_DATA_MAX ) )
    {
        return DAC14_ERROR;
    }
    err_t error_flag = DAC14_OK;
    if ( DAC14_SEL_DAC_1 == dac )
    {
        error_flag |= dac14_write_register ( ctx, DAC14_REG_DAC1_MARGIN_LOW, margin_l << 6 );
        error_flag |= dac14_write_register ( ctx, DAC14_REG_DAC1_MARGIN_HIGH, margin_h << 6 );
    }
    else
    {
        error_flag |= dac14_write_register ( ctx, DAC14_REG_DAC0_MARGIN_LOW, margin_l << 6 );
        error_flag |= dac14_write_register ( ctx, DAC14_REG_DAC0_MARGIN_HIGH, margin_h << 6 );
    }
    return error_flag;
}

err_t dac14_set_dac_data ( dac14_t *ctx, uint8_t dac, uint16_t dac_data )
{
    if ( ( dac > DAC14_SEL_DAC_1 ) || ( dac_data > DAC14_DAC_DATA_MAX ) )
    {
        return DAC14_ERROR;
    }
    err_t error_flag = DAC14_OK;
    if ( DAC14_SEL_DAC_1 == dac )
    {
        error_flag |= dac14_write_register ( ctx, DAC14_REG_DAC1_DATA, dac_data << 6 );
    }
    else
    {
        error_flag |= dac14_write_register ( ctx, DAC14_REG_DAC0_DATA, dac_data << 6 );
    }
    return error_flag;
}

err_t dac14_start_function_gen ( dac14_t *ctx, uint8_t dac )
{
    if ( dac > DAC14_SEL_DAC_1 )
    {
        return DAC14_ERROR;
    }
    err_t error_flag = DAC14_OK;
    uint16_t reg_data;
    error_flag |= dac14_read_register ( ctx, DAC14_REG_COMMON_DAC_TRIG, &reg_data );
    if ( DAC14_OK == error_flag )
    {
        if ( DAC14_SEL_DAC_1 == dac )
        {
            reg_data |= DAC14_CDT_START_FUNC_1;
        }
        else
        {
            reg_data |= DAC14_CDT_START_FUNC_0;
        }
        error_flag |= dac14_write_register ( ctx, DAC14_REG_COMMON_DAC_TRIG, reg_data );
    }
    return error_flag;
}

err_t dac14_stop_function_gen ( dac14_t *ctx, uint8_t dac )
{
    if ( dac > DAC14_SEL_DAC_1 )
    {
        return DAC14_ERROR;
    }
    err_t error_flag = DAC14_OK;
    uint16_t reg_data;
    error_flag |= dac14_read_register ( ctx, DAC14_REG_COMMON_DAC_TRIG, &reg_data );
    if ( DAC14_OK == error_flag )
    {
        if ( DAC14_SEL_DAC_1 == dac )
        {
            reg_data &= ( ~DAC14_CDT_START_FUNC_1 );
        }
        else
        {
            reg_data &= ( ~DAC14_CDT_START_FUNC_0 );
        }
        error_flag |= dac14_write_register ( ctx, DAC14_REG_COMMON_DAC_TRIG, reg_data );
    }
    return error_flag;
}

err_t dac14_config_function_gen ( dac14_t *ctx, uint8_t dac, uint8_t waveform, 
                                  uint8_t code_step, uint8_t slew_rate )
{
    if ( ( dac > DAC14_SEL_DAC_1 ) || 
         ( ( waveform > DAC14_WAVEFORM_INV_SAWTOOTH ) && 
           ( DAC14_WAVEFORM_SINE != waveform ) && 
           ( DAC14_WAVEFORM_DISABLE != waveform ) ) || 
        ( code_step > DAC14_CODE_STEP_32_LSB ) || 
        ( slew_rate > DAC14_SLEW_RATE_5127_92_US ) )
    {
        return DAC14_ERROR;
    }
    err_t error_flag = DAC14_OK;
    uint16_t reg_data;
    uint8_t reg_addr = DAC14_REG_DAC0_FUNC_CONFIG;
    if ( DAC14_SEL_DAC_1 == dac )
    {
        reg_addr = DAC14_REG_DAC1_FUNC_CONFIG;
    }
    error_flag |= dac14_read_register ( ctx, reg_addr, &reg_data );
    if ( DAC14_OK == error_flag )
    {
        reg_data &= ( ~DAC14_DXFC_FUNC_CONFIG_X_MASK );
        reg_data |= ( ( ( uint16_t ) waveform << 8 ) & DAC14_DXFC_FUNC_CONFIG_X_MASK );
        reg_data &= ( ~DAC14_DXFC_CODE_STEP_X_MASK );
        reg_data |= ( ( ( uint16_t ) code_step << 4 ) & DAC14_DXFC_CODE_STEP_X_MASK );
        reg_data &= ( ~DAC14_DXFC_SLEW_RATE_X_MASK );
        reg_data |= ( ( ( uint16_t ) slew_rate ) & DAC14_DXFC_SLEW_RATE_X_MASK );
        error_flag |= dac14_write_register ( ctx, reg_addr, reg_data );
    }
    return error_flag;
}

static err_t dac14_i2c_write ( dac14_t *ctx, uint8_t reg, uint16_t *data_in ) 
{
    if ( reg > DAC14_REG_BRDCAST_DATA )
    {
        return DAC14_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( *data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( *data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

static err_t dac14_i2c_read ( dac14_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    if ( reg > DAC14_REG_BRDCAST_DATA )
    {
        return DAC14_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( DAC14_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

static err_t dac14_spi_write ( dac14_t *ctx, uint8_t reg, uint16_t *data_in ) 
{
    if ( reg > DAC14_REG_BRDCAST_DATA )
    {
        return DAC14_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( *data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( *data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t dac14_spi_read ( dac14_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    if ( reg > DAC14_REG_BRDCAST_DATA )
    {
        return DAC14_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10us ( );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    if ( DAC14_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
