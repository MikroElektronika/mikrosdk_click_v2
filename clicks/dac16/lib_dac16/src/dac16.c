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
 * @file dac16.c
 * @brief DAC 16 Click Driver.
 */

#include "dac16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief DAC 16 I2C writing function.
 * @details This function writes a desired data word to the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac16_i2c_write ( dac16_t *ctx, uint8_t reg, uint16_t *data_in );

/**
 * @brief DAC 16 I2C reading function.
 * @details This function reads data word from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac16_i2c_read ( dac16_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief DAC 16 SPI writing function.
 * @details This function writes a desired data word to the selected register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac16_spi_write ( dac16_t *ctx, uint8_t reg, uint16_t *data_in );

/**
 * @brief DAC 16 SPI reading function.
 * @details This function reads data word from the selected register
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dac16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t dac16_spi_read ( dac16_t *ctx, uint8_t reg, uint16_t *data_out );

void dac16_cfg_setup ( dac16_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->gp   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DAC16_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = DAC16_DRV_SEL_I2C;
}

void dac16_drv_interface_sel ( dac16_cfg_t *cfg, dac16_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t dac16_init ( dac16_t *ctx, dac16_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( DAC16_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = dac16_i2c_read;
        ctx->write_f = dac16_i2c_write;
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

        ctx->read_f  = dac16_spi_read;
        ctx->write_f = dac16_spi_write;
    }

    digital_in_init( &ctx->gp, cfg->gp );

    return DAC16_OK;
}

err_t dac16_default_cfg ( dac16_t *ctx ) 
{
    err_t error_flag = DAC16_OK;
    DAC16_SET_DATA_SAMPLE_EDGE;
    if ( DAC16_ERROR == dac16_check_communication ( ctx ) )
    {
        return DAC16_ERROR;
    }
    // enable VOUT for all channels
    error_flag |= dac16_set_dac_vout_enable ( ctx, DAC16_SEL_DAC_0, DAC16_EN_VOUT_POWER_UP );
    error_flag |= dac16_set_dac_vout_enable ( ctx, DAC16_SEL_DAC_1, DAC16_EN_VOUT_POWER_UP );
    error_flag |= dac16_set_dac_vout_enable ( ctx, DAC16_SEL_DAC_2, DAC16_EN_VOUT_POWER_UP );
    error_flag |= dac16_set_dac_vout_enable ( ctx, DAC16_SEL_DAC_3, DAC16_EN_VOUT_POWER_UP );
    Delay_100ms ( );
    // set DAC vref to VDD
    error_flag |= dac16_set_dac_vref ( ctx, DAC16_SEL_DAC_0, DAC16_VREF_VDD );
    error_flag |= dac16_set_dac_vref ( ctx, DAC16_SEL_DAC_1, DAC16_VREF_VDD );
    error_flag |= dac16_set_dac_vref ( ctx, DAC16_SEL_DAC_2, DAC16_VREF_VDD );
    error_flag |= dac16_set_dac_vref ( ctx, DAC16_SEL_DAC_3, DAC16_VREF_VDD );
    // stop function generator for all channels
    error_flag |= dac16_stop_function_gen ( ctx, DAC16_SEL_DAC_0 );
    error_flag |= dac16_stop_function_gen ( ctx, DAC16_SEL_DAC_1 );
    error_flag |= dac16_stop_function_gen ( ctx, DAC16_SEL_DAC_2 );
    error_flag |= dac16_stop_function_gen ( ctx, DAC16_SEL_DAC_3 );
    // set margin levels and a function generator config to output 
    // triangular wave on OUT1 with a frequency of about 1kHz
    // sine wave on OUT2 with a frequency of about 10.5kHz
    // sawtooth wave on OUT3 with a frequency of about 2kHz
    error_flag |= dac16_set_dac_margins ( ctx, DAC16_SEL_DAC_1, DAC16_DAC_DATA_MIN, DAC16_DAC_DATA_MAX );
    error_flag |= dac16_set_dac_margins ( ctx, DAC16_SEL_DAC_2, DAC16_DAC_DATA_MIN, DAC16_DAC_DATA_MAX );
    error_flag |= dac16_set_dac_margins ( ctx, DAC16_SEL_DAC_3, DAC16_DAC_DATA_MIN, DAC16_DAC_DATA_MAX );
    error_flag |= dac16_config_function_gen ( ctx, DAC16_SEL_DAC_1, DAC16_WAVEFORM_TRIANGULAR,
                                              DAC16_CODE_STEP_32_LSB, DAC16_SLEW_RATE_4_US );
    error_flag |= dac16_config_function_gen ( ctx, DAC16_SEL_DAC_2, DAC16_WAVEFORM_SINE,
                                              DAC16_CODE_STEP_32_LSB, DAC16_SLEW_RATE_4_US );
    error_flag |= dac16_config_function_gen ( ctx, DAC16_SEL_DAC_3, DAC16_WAVEFORM_SAWTOOTH,
                                              DAC16_CODE_STEP_32_LSB, DAC16_SLEW_RATE_4_US );
    // start function generator for OUT1-3
    error_flag |= dac16_start_function_gen ( ctx, DAC16_SEL_DAC_1 );
    error_flag |= dac16_start_function_gen ( ctx, DAC16_SEL_DAC_2 );
    error_flag |= dac16_start_function_gen ( ctx, DAC16_SEL_DAC_3 );
    return error_flag;
}

err_t dac16_write_register ( dac16_t *ctx, uint8_t reg, uint16_t data_in )
{
    return ctx->write_f ( ctx, reg, &data_in );
}

err_t dac16_read_register ( dac16_t *ctx, uint8_t reg, uint16_t *data_out )
{
    return ctx->read_f ( ctx, reg, data_out );
}

uint8_t dac16_get_gp_pin ( dac16_t *ctx )
{
    return digital_in_read ( &ctx->gp );
}

err_t dac16_check_communication ( dac16_t *ctx )
{
    err_t error_flag = DAC16_OK;
    uint16_t reg_data = DAC16_IC_SDO_EN;
    if ( DAC16_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        reg_data = DAC16_IC_SDO_DIS;
    }
    error_flag |= dac16_write_register ( ctx, DAC16_REG_INTERFACE_CONFIG, reg_data );
    if ( DAC16_OK == error_flag )
    {
        Delay_10ms ( );
        error_flag |= dac16_read_register ( ctx, DAC16_REG_GENERAL_STATUS, &reg_data );
        if ( ( DAC16_OK == error_flag ) && ( DAC16_DEVICE_ID != ( reg_data & DAC16_DEVICE_ID_MASK ) ) )
        {
            error_flag = DAC16_ERROR;
        }
    }
    return error_flag;
}

err_t dac16_set_dac_vout_enable ( dac16_t *ctx, uint8_t dac, uint8_t vout_pdn )
{
    if ( ( dac > DAC16_SEL_DAC_3 ) || ( vout_pdn > DAC16_EN_VOUT_POWER_DOWN_HI_Z_AGND ) )
    {
        return DAC16_ERROR;
    }
    err_t error_flag = DAC16_OK;
    uint16_t reg_data = 0;
    error_flag |= dac16_read_register ( ctx, DAC16_REG_COMMON_CONFIG, &reg_data );
    if ( DAC16_OK == error_flag )
    {
        if ( DAC16_SEL_DAC_3 == dac )
        {
            reg_data &= ( ~DAC16_CC_VOUT_PDN_3_MASK );
            reg_data |= ( ( ( uint16_t ) vout_pdn << 10 ) & DAC16_CC_VOUT_PDN_3_MASK );
        }
        else if ( DAC16_SEL_DAC_2 == dac )
        {
            reg_data &= ( ~DAC16_CC_VOUT_PDN_2_MASK );
            reg_data |= ( ( ( uint16_t ) vout_pdn << 7 ) & DAC16_CC_VOUT_PDN_2_MASK );
        }
        else if ( DAC16_SEL_DAC_1 == dac )
        {
            reg_data &= ( ~DAC16_CC_VOUT_PDN_1_MASK );
            reg_data |= ( ( ( uint16_t ) vout_pdn << 4 ) & DAC16_CC_VOUT_PDN_1_MASK );
        }
        else
        {
            reg_data &= ( ~DAC16_CC_VOUT_PDN_0_MASK );
            reg_data |= ( ( ( uint16_t ) vout_pdn << 1 ) & DAC16_CC_VOUT_PDN_0_MASK );
        }
        error_flag |= dac16_write_register ( ctx, DAC16_REG_COMMON_CONFIG, reg_data );
    }
    return error_flag;
}

err_t dac16_set_dac_vref ( dac16_t *ctx, uint8_t dac, uint8_t vref )
{
    if ( ( dac > DAC16_SEL_DAC_3 ) || ( vref > DAC16_VREF_INT_4X ) )
    {
        return DAC16_ERROR;
    }
    err_t error_flag = DAC16_OK;
    uint16_t reg_data = 0;
    uint8_t reg_addr = DAC16_REG_DAC0_VOUT_CMP_CONFIG + dac * ( DAC16_REG_DAC1_VOUT_CMP_CONFIG - 
                                                                DAC16_REG_DAC0_VOUT_CMP_CONFIG );
    error_flag |= dac16_read_register ( ctx, reg_addr, &reg_data );
    if ( DAC16_OK == error_flag )
    {
        reg_data &= ( ~DAC16_VCC_VOUT_GAIN_X_MASK );
        reg_data |= ( ( ( uint16_t ) vref << 10 ) & DAC16_VCC_VOUT_GAIN_X_MASK );
        error_flag |= dac16_write_register ( ctx, reg_addr, reg_data );
    }
    return error_flag;
}

err_t dac16_set_dac_margins ( dac16_t *ctx, uint8_t dac, uint16_t margin_l, uint16_t margin_h )
{
    if ( ( dac > DAC16_SEL_DAC_3 ) || ( margin_l > margin_h ) || 
         ( margin_l > DAC16_DAC_DATA_MAX ) || ( margin_h > DAC16_DAC_DATA_MAX ) )
    {
        return DAC16_ERROR;
    }
    err_t error_flag = DAC16_OK;
    uint8_t reg_addr = DAC16_REG_DAC0_MARGIN_HIGH + dac * ( DAC16_REG_DAC1_MARGIN_HIGH - 
                                                            DAC16_REG_DAC0_MARGIN_HIGH );
    error_flag |= dac16_write_register ( ctx, reg_addr, margin_h << 4 );
    error_flag |= dac16_write_register ( ctx, reg_addr + 1, margin_l << 4 );
    return error_flag;
}

err_t dac16_set_dac_data ( dac16_t *ctx, uint8_t dac, uint16_t dac_data )
{
    if ( ( dac > DAC16_SEL_DAC_3 ) || ( dac_data > DAC16_DAC_DATA_MAX ) )
    {
        return DAC16_ERROR;
    }
    return dac16_write_register ( ctx, DAC16_REG_DAC0_DATA + dac, dac_data << 4 );
}

err_t dac16_start_function_gen ( dac16_t *ctx, uint8_t dac )
{
    if ( dac > DAC16_SEL_DAC_3 )
    {
        return DAC16_ERROR;
    }
    err_t error_flag = DAC16_OK;
    uint16_t reg_data = 0;
    error_flag |= dac16_read_register ( ctx, DAC16_REG_COMMON_DAC_TRIG, &reg_data );
    if ( DAC16_OK == error_flag )
    {
        reg_data |= ( DAC16_CDT_START_FUNC_0 >> ( dac * 4 ) );
        error_flag |= dac16_write_register ( ctx, DAC16_REG_COMMON_DAC_TRIG, reg_data );
    }
    Delay_10ms ( );
    return error_flag;
}

err_t dac16_stop_function_gen ( dac16_t *ctx, uint8_t dac )
{
    if ( dac > DAC16_SEL_DAC_3 )
    {
        return DAC16_ERROR;
    }
    err_t error_flag = DAC16_OK;
    uint16_t reg_data = 0;
    error_flag |= dac16_read_register ( ctx, DAC16_REG_COMMON_DAC_TRIG, &reg_data );
    if ( DAC16_OK == error_flag )
    {
        reg_data &= ( ~( DAC16_CDT_START_FUNC_0 >> ( dac * 4 ) ) );
        error_flag |= dac16_write_register ( ctx, DAC16_REG_COMMON_DAC_TRIG, reg_data );
    }
    Delay_10ms ( );
    return error_flag;
}

err_t dac16_config_function_gen ( dac16_t *ctx, uint8_t dac, uint8_t waveform, 
                                  uint8_t code_step, uint8_t slew_rate )
{
    if ( ( dac > DAC16_SEL_DAC_3 ) || 
         ( ( waveform > DAC16_WAVEFORM_INV_SAWTOOTH ) && 
           ( DAC16_WAVEFORM_SINE != waveform ) && 
           ( DAC16_WAVEFORM_DISABLE != waveform ) ) || 
        ( code_step > DAC16_CODE_STEP_32_LSB ) || 
        ( slew_rate > DAC16_SLEW_RATE_5127_92_US ) )
    {
        return DAC16_ERROR;
    }
    err_t error_flag = DAC16_OK;
    uint16_t reg_data = 0;
    uint8_t reg_addr = DAC16_REG_DAC0_FUNC_CONFIG + dac * ( DAC16_REG_DAC1_FUNC_CONFIG - 
                                                            DAC16_REG_DAC0_FUNC_CONFIG );
    error_flag |= dac16_read_register ( ctx, reg_addr, &reg_data );
    if ( DAC16_OK == error_flag )
    {
        reg_data &= ( ~DAC16_DXFC_FUNC_CONFIG_X_MASK );
        reg_data |= ( ( ( uint16_t ) waveform << 8 ) & DAC16_DXFC_FUNC_CONFIG_X_MASK );
        reg_data &= ( ~DAC16_DXFC_CODE_STEP_X_MASK );
        reg_data |= ( ( ( uint16_t ) code_step << 4 ) & DAC16_DXFC_CODE_STEP_X_MASK );
        reg_data &= ( ~DAC16_DXFC_SLEW_RATE_X_MASK );
        reg_data |= ( ( ( uint16_t ) slew_rate ) & DAC16_DXFC_SLEW_RATE_X_MASK );
        error_flag |= dac16_write_register ( ctx, reg_addr, reg_data );
    }
    Delay_10ms ( );
    return error_flag;
}

static err_t dac16_i2c_write ( dac16_t *ctx, uint8_t reg, uint16_t *data_in ) 
{
    if ( reg > DAC16_REG_BRDCAST_DATA )
    {
        return DAC16_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( *data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( *data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

static err_t dac16_i2c_read ( dac16_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    if ( reg > DAC16_REG_BRDCAST_DATA )
    {
        return DAC16_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( DAC16_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

static err_t dac16_spi_write ( dac16_t *ctx, uint8_t reg, uint16_t *data_in ) 
{
    if ( reg > DAC16_REG_BRDCAST_DATA )
    {
        return DAC16_ERROR;
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

static err_t dac16_spi_read ( dac16_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    if ( reg > DAC16_REG_BRDCAST_DATA )
    {
        return DAC16_ERROR;
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
    if ( DAC16_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
