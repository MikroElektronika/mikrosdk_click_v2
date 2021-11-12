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
 * @file daq.c
 * @brief DAQ Click Driver.
 */

#include "daq.h"

/**
 * @brief Communication macros.
 * @details Definition of communication macros.
 */
#define DUMMY               0x00
#define REG_MASK            0x3F
#define READ_BIT            0x40

/**
 * @brief Gain values.
 * @details Definition of gain values.
 */
#define DAQ_GAIN_RES_12p603 12.603
#define DAQ_GAIN_RES_6p302  6.302
#define DAQ_GAIN_RES_3p151  3.151
#define DAQ_GAIN_RES_1p575  1.575
#define DAQ_GAIN_RES_p788   0.788
#define DAQ_GAIN_RES_p394   0.394
#define DAQ_GAIN_RES_p197   0.197

/**
 * @brief Get gain value from gain resolution.
 * @details This function sets gain value in @b ctx object depending of selected resolution.
 * @param[in] ctx : Click context object.
 * See #daq_t object definition for detailed explanation.
 * @param[in] gain : Gain range.
 * See #daq_gain enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t daq_get_gain_value ( daq_t *ctx, daq_gain gain );

void daq_cfg_setup ( daq_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->io3 = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->io3direction = 0;
}

err_t daq_init ( daq_t *ctx, daq_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
    digital_out_init( &ctx->rst, cfg->rst );
    
    digital_in_init( &ctx->rdy, cfg->rdy );

    if ( cfg->io3direction )
    {
        digital_in_init( &ctx->io3, cfg->io3 );
    }
    else
    {
        digital_out_init( &ctx->io3, cfg->io3 );
    }
    
    ctx->gain = 0;
    
    return SPI_MASTER_SUCCESS;
}

err_t daq_default_cfg ( daq_t *ctx ) 
{
    digital_out_high( &ctx->io3 );
    digital_out_high( &ctx->rst );
    daq_reset( ctx );
    
    //SW Reset
    err_t ret_val = daq_byte_write( ctx, DAQ_REG_SYNC_RESET, 0x3 );
    ret_val |= daq_byte_write( ctx, DAQ_REG_SYNC_RESET, 0x2 );
    Delay_100ms();
    Delay_100ms();
    
    ret_val |= daq_mask_write( ctx, DAQ_REG_POWER_CLOCK,
                        DAQ_POWER_CLK_PWRMODE_MSK,
                        DAQ_POWER_CLK_PWRMODE( DAQ_ECO ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_POWER_CLOCK,
                        DAQ_POWER_CLK_MCLK_DIV_MSK,
                        DAQ_POWER_CLK_MCLK_DIV( DAQ_MCLK_DIV_16 ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_CONVERSION,
                        DAQ_CONVERSION_MODE_MSK,
                        DAQ_CONVERSION_MODE( DAQ_CONV_ONE_SHOT ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_CONVERSION,
                        DAQ_CONVERSION_DIAG_MUX_MSK,
                        DAQ_CONVERSION_DIAG_MUX_SEL( DAQ_AIN_SHORT ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_CONVERSION,
                        DAQ_CONVERSION_DIAG_SEL_MSK,
                        DAQ_CONVERSION_DIAG_SEL( DAQ_CONV_24BIT ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_INTERFACE_FORMAT,
                        DAQ_INTERFACE_CONVLEN_MSK,
                        DAQ_INTERFACE_CONVLEN( DAQ_CONV_24BIT ) );    

    ret_val |= daq_mask_write( ctx, DAQ_REG_ANALOG2,
                        DAQ_ANALOG2_VCM_MSK,
                        DAQ_ANALOG2_VCM( DAQ_VCM_HALF_VCC ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_ANALOG,
                        DAQ_ANALOG_AIN_BUF_NEG_OFF_MSK,
                        DAQ_ANALOG_AIN_BUF_NEG_OFF( DAQ_AIN_ENABLED ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_ANALOG,
                        DAQ_ANALOG_AIN_BUF_POS_OFF_MSK,
                        DAQ_ANALOG_AIN_BUF_POS_OFF( DAQ_AIN_ENABLED ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_ANALOG,
                        DAQ_ANALOG_REF_BUF_NEG_MSK,
                        DAQ_ANALOG_REF_BUF_NEG( DAQ_BUF_ENABLED ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_ANALOG,
                        DAQ_ANALOG_REF_BUF_POS_MSK,
                        DAQ_ANALOG_REF_BUF_POS( DAQ_BUF_ENABLED ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_DIGITAL_FILTER,
                        DAQ_DIGI_FILTER_FILTER_MSK,
                        DAQ_DIGI_FILTER_FILTER( DAQ_SINC5_FIR_DECx32 ) );

    ret_val |= daq_mask_write( ctx, DAQ_REG_SINC3_DEC_RATE_MSB,
                        DAQ_SINC3_DEC_RATE_MSB_MSK,
                        DAQ_SINC3_DEC_RATE_MSB( 0 ) );

    daq_mask_write( ctx, DAQ_REG_SINC3_DEC_RATE_LSB,
                        DAQ_SINC3_DEC_RATE_LSB_MSK,
                        DAQ_SINC3_DEC_RATE_LSB( 0 ) );
    
    ret_val |= daq_byte_write( ctx, DAQ_REG_GPIO_CONTROL, 0x8F );
    ret_val |= daq_set_gain( ctx, DAQ_GAIN_12p603 );

    ret_val |= daq_mask_write( ctx, DAQ_REG_INTERFACE_FORMAT,
                            DAQ_INTERFACE_CRC_EN_MSK,
                            DAQ_INTERFACE_CRC_EN( DAQ_NO_CRC ) );
    
    return DAQ_OK;
}

err_t daq_generic_write ( daq_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };
    uint8_t cnt;

    tx_buf[ 0 ] = reg & REG_MASK;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }
    len++;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t daq_byte_write ( daq_t *ctx, uint8_t reg, uint8_t data_in )
{
    return daq_generic_write( ctx, reg, &data_in, 1 );
}

err_t daq_mask_write ( daq_t *ctx, uint8_t reg, uint8_t mask, uint8_t data_in )
{
    uint8_t reg_data;
	err_t ret;

	ret = daq_byte_read( ctx, reg, &reg_data );
	reg_data &= ~mask;
	reg_data |= data_in;
	ret |= daq_byte_write( ctx, reg, reg_data );

	return ret;
}

err_t daq_generic_read ( daq_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg & REG_MASK;
    reg_adr |= READ_BIT;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t daq_byte_read ( daq_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return daq_generic_read( ctx, reg, data_out, 1 );
}

err_t daq_mask_read ( daq_t *ctx, uint8_t reg, uint8_t mask, uint8_t *data_out )
{
    uint8_t reg_data;
	err_t ret;

	ret = daq_byte_read( ctx, reg, &reg_data );
	*data_out = (reg_data & mask);

	return ret;
}

err_t daq_raw_read ( daq_t *ctx, uint8_t *data_out, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void daq_reset ( daq_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
}

uint8_t daq_data_ready( daq_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

void daq_set_io3 ( daq_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->io3 );
    }
    else
    {
        digital_out_low( &ctx->io3 );
    }
}

uint8_t daq_get_iot3 ( daq_t *ctx )
{
    return digital_in_read( &ctx->io3 );
}

err_t daq_set_gain ( daq_t *ctx, daq_gain gain )
{
    err_t ret_val;
    uint8_t state;
    
    ret_val = daq_get_gain_value( ctx, gain );
    
    if ( gain & DAQ_GPIO_READ_0_MSK )
    {
        state = DAQ_GPIO_HIGH;
    }
    else
    {
        state = DAQ_GPIO_LOW;
    }
    ret_val |= daq_mask_write( ctx, DAQ_REG_GPIO_WRITE,
                                    DAQ_GPIO_WRITE_0_MSK,
                                    DAQ_GPIO_WRITE_0(state));
    
    if ( gain & DAQ_GPIO_READ_1_MSK )
    {
        state = DAQ_GPIO_HIGH;
    }
    else
    {
        state = DAQ_GPIO_LOW;
    }
    ret_val |= daq_mask_write( ctx, DAQ_REG_GPIO_WRITE,
                                    DAQ_GPIO_WRITE_1_MSK,
                                    DAQ_GPIO_WRITE_1(state));
    
    if ( gain & DAQ_GPIO_READ_2_MSK )
    {
        state = DAQ_GPIO_HIGH;
    }
    else
    {
        state = DAQ_GPIO_LOW;
    }
    ret_val |= daq_mask_write( ctx, DAQ_REG_GPIO_WRITE,
                                    DAQ_GPIO_WRITE_2_MSK,
                                    DAQ_GPIO_WRITE_2(state));
    
    return ret_val;
}

err_t daq_read_data ( daq_t *ctx, int32_t *adc_data )
{
    uint8_t adc_buf[ 3 ] = { 0 };

    err_t ret_val = daq_generic_read( ctx, DAQ_REG_ADC_DATA, adc_buf, 3 );
    
    *adc_data =  ( (int32_t)adc_buf[ 0 ] << 24 | 
                  (int32_t)adc_buf[ 1 ] << 16 | 
                  (int32_t)adc_buf[ 2 ] << 8 );
    *adc_data >>= 8;
    return ret_val;
}

void daq_calculate_voltage ( daq_t *ctx, int32_t adc_data, float *voltage )
{
    *voltage = ( ( ( ctx->gain ) / ( DAQ_RESOLUTION ) ) * adc_data );
}

static err_t daq_get_gain_value ( daq_t *ctx, daq_gain gain )
{
    err_t ret_val = DAQ_OK;
    switch ( gain )
    {
        case DAQ_GAIN_12p603:
        {
            ctx->gain = DAQ_GAIN_RES_12p603;
            break;
        }
        case DAQ_GAIN_6p302:
        {
            ctx->gain = DAQ_GAIN_RES_6p302;
            break;
        }
        case DAQ_GAIN_3p151:
        {
            ctx->gain = DAQ_GAIN_RES_3p151;
            break;
        }
        case DAQ_GAIN_1p575:
        {
            ctx->gain = DAQ_GAIN_RES_1p575;
            break;
        }
        case DAQ_GAIN_p788:
        {
            ctx->gain = DAQ_GAIN_RES_p788;
            break;
        }
        case DAQ_GAIN_p394:
        {
            ctx->gain = DAQ_GAIN_RES_p394;
            break;
        }
        case DAQ_GAIN_p197:
        {
            ctx->gain = DAQ_GAIN_RES_p197;
            break;
        }
        default:
        {
            ctx->gain = 0;
            ret_val = DAQ_ERROR;
            break;
        }
    }
    return ret_val;
}

// ------------------------------------------------------------------------- END
