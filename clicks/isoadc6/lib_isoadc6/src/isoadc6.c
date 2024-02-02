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
 * @file isoadc6.c
 * @brief ISO ADC 6 Click Driver.
 */

#include "isoadc6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief ISO ADC 6 check data ready function.
 * @details This function checks if data results are ready.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @return @li @c 0 - The data is ready,
 *         @li @c 1 - The data is not read.
 * @note None.
 */
static uint8_t isoadc6_check_data_ready ( isoadc6_t* ctx );

/**
 * @brief ISO ADC 6 get reg len function.
 * @details This function return register length data.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @return @li @c 0 - Error,
 *         @li @c 1 - Register length.
 * @note None.
 */
static uint8_t isoadc6_get_reg_len ( isoadc6_t* ctx, uint8_t reg );

void isoadc6_cfg_setup ( isoadc6_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->vref = ISOADC6_VTG_REF_2_65_V;
    cfg->calib = ISOADC6_CALIB_DEFAULT;
    cfg->ch_sel = ISOADC6_SEL_CH_0;
}

err_t isoadc6_init ( isoadc6_t *ctx, isoadc6_cfg_t *cfg ) 
{
    ctx->vref = cfg->vref;
    ctx->calib = cfg->calib;
    ctx->ch_sel = cfg->ch_sel;
    
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

    return SPI_MASTER_SUCCESS;
}

err_t isoadc6_default_cfg ( isoadc6_t *ctx ) 
{
    uint8_t device_id = DUMMY, sil_rev = DUMMY;
    err_t err_flag = isoadc6_get_device_id( ctx, &device_id, &sil_rev );
    if ( ISOADC6_DEVICE_ID == device_id )
    {
        err_flag |= isoadc6_set_ch_config( ctx, ISOADC6_CFG_BIP_OP_EN |  
                                                ISOADC6_CFG_BUFF_ON_AINP_EN | 
                                                ISOADC6_CFG_BUFF_ON_AINM_EN );
        err_flag |= isoadc6_set_channel( ctx, ISOADC6_SEL_CH_0, 
                                              ISOADC6_CHANNEL_ENABLE | 
                                              ISOADC6_CHANNEL_NEG_AN_IN_AIN1 );
        err_flag |= isoadc6_set_adc_control( ctx, ISOADC6_CTRL_DATA_STATUS_EN | 
                                                  ISOADC6_CTRL_DOUT_PIN_EN |
                                                  ISOADC6_CTRL_INT_REF_VVTG_EN |
                                                  ISOADC6_CTRL_FULL_POWER_MODE | 
                                                  ISOADC6_CTRL_SINGLE_CONV_MODE );
    }
    else
    {
        err_flag = ISOADC6_ERROR;
    }
    return err_flag;
}

err_t isoadc6_generic_write ( isoadc6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    err_t err_flag = spi_master_write( &ctx->spi, &reg, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t isoadc6_generic_read ( isoadc6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10us( );
    return err_flag;
}

err_t isoadc6_write_byte ( isoadc6_t* ctx, uint8_t reg, uint8_t data_in )
{
    err_t err_flag = ISOADC6_ERROR;
    if ( ISOADC6_LEN_REG_BYTE == isoadc6_get_reg_len( ctx, reg ) )
    {
        err_flag = isoadc6_generic_write( ctx, reg, &data_in, 1 );
    }
    return err_flag;
}

err_t isoadc6_read_byte ( isoadc6_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t err_flag = ISOADC6_ERROR;
    if ( ISOADC6_LEN_REG_BYTE == isoadc6_get_reg_len( ctx, reg ) )
    {
        err_flag = isoadc6_generic_read( ctx, reg | ISOADC6_CMD_SPI_READ, data_out, 1 );
    }
    return err_flag;
}

err_t isoadc6_write_word ( isoadc6_t* ctx, uint8_t reg, uint16_t data_in )
{
    err_t err_flag = ISOADC6_ERROR;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 1 ] = ( uint8_t ) data_in;
    if ( ISOADC6_LEN_REG_WORD == isoadc6_get_reg_len( ctx, reg ) )
    {
        err_flag = isoadc6_generic_write( ctx, reg, data_buf, 2 );
    }
    return err_flag;
}

err_t isoadc6_read_word ( isoadc6_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t err_flag = ISOADC6_ERROR;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ISOADC6_LEN_REG_WORD == isoadc6_get_reg_len( ctx, reg ) )
    {
        err_flag = isoadc6_generic_read( ctx, reg | ISOADC6_CMD_SPI_READ, data_buf, 2 );
        *data_out = data_buf[ 0 ];
        *data_out <<= 8;
        *data_out |= data_buf[ 1 ];
    }
    return err_flag;
}

err_t isoadc6_write_dword ( isoadc6_t* ctx, uint8_t reg, uint32_t data_in )
{
    err_t err_flag = ISOADC6_ERROR;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 16 );
    data_buf[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 2 ] = ( uint8_t ) data_in;
    if ( ISOADC6_LEN_REG_DWORD == isoadc6_get_reg_len( ctx, reg ) )
    {
        err_flag = isoadc6_generic_write( ctx, reg, data_buf, 3 );
    }
   
    return err_flag;
}

err_t isoadc6_read_dword ( isoadc6_t *ctx, uint8_t reg, uint32_t *data_out )
{
    err_t err_flag = ISOADC6_ERROR;
    uint8_t data_buf[ 3 ] = { 0 };
    if ( ISOADC6_LEN_REG_DWORD == isoadc6_get_reg_len( ctx, reg ) )
    {
        err_flag = isoadc6_generic_read( ctx, reg | ISOADC6_CMD_SPI_READ, data_buf, 3 );
        *data_out = data_buf[ 0 ];
        *data_out <<= 8;
        *data_out |= data_buf[ 1 ];
        *data_out <<= 8;
        *data_out |= data_buf[ 2 ];
    }
    return err_flag;
}

err_t isoadc6_get_device_id ( isoadc6_t* ctx, uint8_t *device_id, uint8_t *sil_rev )
{
    err_t err_flag = isoadc6_read_byte( ctx, ISOADC6_REG_ID, device_id );
    *sil_rev = *device_id;
    *sil_rev &= ISOADC6_SIL_REV_BIT_MASK;
    *device_id &= ISOADC6_DEV_ID_REV_BIT_MASK;
    *device_id >>= 4;
    return err_flag;
}

err_t isoadc6_set_channel ( isoadc6_t* ctx, uint8_t sel_ch, uint16_t ch_data )
{
    err_t err_flag = ISOADC6_ERROR;
    if ( ISOADC6_SEL_CH_15 >= sel_ch )
    {
        err_flag = isoadc6_write_word( ctx, ISOADC6_REG_CHANNEL_0 + sel_ch, ch_data );
        ctx->ch_sel = sel_ch;
    }
    return err_flag;
}

err_t isoadc6_set_ch_config ( isoadc6_t* ctx, uint16_t cfg_data )
{
    return isoadc6_write_word( ctx, ISOADC6_REG_CONFIG_0 + ctx->ch_sel, cfg_data );
}

err_t isoadc6_set_adc_control ( isoadc6_t* ctx, uint16_t adc_ctrl )
{
    return isoadc6_write_word( ctx, ISOADC6_REG_CONTROL, adc_ctrl );
}

err_t isoadc6_set_ch_offset ( isoadc6_t* ctx, uint32_t offset )
{
    return isoadc6_write_word( ctx, ISOADC6_REG_OFFSET_0 + ctx->ch_sel, offset );
}

err_t isoadc6_get_ch_offset ( isoadc6_t* ctx,  uint32_t *offset )
{
    return isoadc6_read_dword( ctx, ISOADC6_REG_OFFSET_0 + ctx->ch_sel, offset );
}

err_t isoadc6_set_ch_gain ( isoadc6_t* ctx, uint32_t gain )
{
    return isoadc6_write_word( ctx, ISOADC6_REG_GAIN_0 + ctx->ch_sel, gain );
}

err_t isoadc6_get_ch_gain ( isoadc6_t* ctx, uint32_t *gain )
{
    return isoadc6_read_dword( ctx, ISOADC6_REG_GAIN_0 + ctx->ch_sel, gain );
}

err_t isoadc6_get_adc_data ( isoadc6_t* ctx, uint32_t *adc_data )
{
    uint16_t control = DUMMY;
    err_t err_flag = isoadc6_read_word( ctx, ISOADC6_REG_CONTROL, &control );
    control &= ( ~ISOADC6_CTRL_MODE_MASK );
    control |= ISOADC6_CTRL_SINGLE_CONV_MODE;
    err_flag |= isoadc6_write_word( ctx, ISOADC6_REG_CONTROL, control );
    
    while( isoadc6_check_data_ready( ctx ) );
    
    err_flag |= isoadc6_read_dword( ctx, ISOADC6_REG_DATA, adc_data );
    return err_flag;
}

err_t isoadc6_get_voltage ( isoadc6_t* ctx, float *voltage )
{
    uint32_t adc_data = DUMMY, offset = DUMMY, gain = DUMMY;
    err_t err_flag = isoadc6_get_ch_offset( ctx, &offset );
    err_flag |= isoadc6_get_ch_gain( ctx, &gain );
    gain /= ISOADC6_GAIN_COEFF;
    err_flag |= isoadc6_get_adc_data( ctx, &adc_data );
    *voltage = ( float ) adc_data;
    *voltage -=  ( float ) offset;
    *voltage *=  ctx->calib;
    *voltage *=  ctx->vref;
    *voltage /=  gain;
    *voltage /= ( float ) offset;
    return err_flag;
}

static uint8_t isoadc6_check_data_ready ( isoadc6_t* ctx )
{
    uint8_t ready_check = DUMMY;
    err_t err_flag = isoadc6_read_byte( ctx, ISOADC6_REG_COMM_STATUS, &ready_check );
    if ( ISOADC6_NEW_DATA_BIT_MASK & ready_check )
    {
        err_flag |= ISOADC6_NEW_DATA_NOT_READY;
    }
    return err_flag;
}

static uint8_t isoadc6_get_reg_len ( isoadc6_t* ctx, uint8_t reg )
{
    if ( ISOADC6_REG_GAIN_7 < reg )
    { 
        return ISOADC6_LEN_REG_ERROR;
    }
    else if ( ( ISOADC6_REG_COMM_STATUS == reg ) || 
              ( ISOADC6_REG_ID == reg ) || 
              ( ISOADC6_REG_MCLK_CNT == reg ) )
    {
        return ISOADC6_LEN_REG_BYTE;
    }
    else if ( ( ISOADC6_REG_CONTROL == reg ) || 
              ( ISOADC6_REG_IO_CONTROL_2 == reg ) || 
              ( ( ISOADC6_REG_CHANNEL_0 <= reg ) && 
                ( ISOADC6_REG_CONFIG_7 >= reg ) ) )
    {
        return ISOADC6_LEN_REG_WORD;
    }
    else
    {
        return ISOADC6_LEN_REG_DWORD;
    }
}

// ------------------------------------------------------------------------- END
