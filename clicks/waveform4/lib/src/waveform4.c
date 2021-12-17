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
 * @file waveform4.c
 * @brief Waveform 4 Click Driver.
 */

#include "waveform4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void waveform4_cfg_setup ( waveform4_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->trg  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t waveform4_init ( waveform4_t *ctx, waveform4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->trg, cfg->trg );

    return SPI_MASTER_SUCCESS;
}

err_t waveform4_default_cfg ( waveform4_t *ctx ) 
{
    err_t error_flag = WAVEFORM4_OK;
    
    waveform4_reset_registers ( ctx );
    Delay_100ms ( );
    
    error_flag |= waveform4_set_wave_output ( ctx, WAVEFORM4_CHANNEL_1, WAVEFORM4_WAVE_SINE );
    error_flag |= waveform4_set_wave_output ( ctx, WAVEFORM4_CHANNEL_2, WAVEFORM4_WAVE_SINE );
    error_flag |= waveform4_set_wave_output ( ctx, WAVEFORM4_CHANNEL_3, WAVEFORM4_WAVE_SINE );
    error_flag |= waveform4_set_wave_output ( ctx, WAVEFORM4_CHANNEL_4, WAVEFORM4_WAVE_SINE );
    error_flag |= waveform4_set_gain ( ctx, WAVEFORM4_CHANNEL_1, WAVEFORM4_DEFAULT_GAIN );
    error_flag |= waveform4_set_gain ( ctx, WAVEFORM4_CHANNEL_2, WAVEFORM4_DEFAULT_GAIN );
    error_flag |= waveform4_set_gain ( ctx, WAVEFORM4_CHANNEL_3, WAVEFORM4_DEFAULT_GAIN );
    error_flag |= waveform4_set_gain ( ctx, WAVEFORM4_CHANNEL_4, WAVEFORM4_DEFAULT_GAIN );
    error_flag |= waveform4_set_frequency ( ctx, WAVEFORM4_DEFAULT_FREQUENCY );

    return error_flag;
}

err_t waveform4_write_registers ( waveform4_t *ctx, uint16_t reg, uint16_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 259 ] = { 0 };
    
    if ( len > ( WAVEFORM4_REG_CFG_ERROR + 1 ) )
    {
        return WAVEFORM4_ERROR;
    }

    tx_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF ) & WAVEFORM4_SPI_WRITE_MASK;
    tx_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ ( cnt * 2 ) + 2 ] = ( uint8_t ) ( data_in[ cnt ] >> 8 );
        tx_buf[ ( cnt * 2 ) + 3 ] = ( uint8_t ) ( data_in[ cnt ] & 0xFF );
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, ( ( uint16_t ) len * 2 ) + 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t waveform4_read_registers ( waveform4_t *ctx, uint16_t reg, uint16_t *data_out, uint8_t len ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };
    uint8_t rx_buf[ 256 ] = { 0 };
    
    if ( len > ( WAVEFORM4_REG_CFG_ERROR + 1 ) )
    {
        return WAVEFORM4_ERROR;
    }

    tx_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF ) | WAVEFORM4_SPI_READ_MASK;
    tx_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, rx_buf, len * 2 );
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        data_out[ cnt ] = rx_buf[ cnt * 2 ];
        data_out[ cnt ] <<= 8;
        data_out[ cnt ] |= rx_buf[ ( cnt * 2 ) + 1 ];
    }
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t waveform4_write_register ( waveform4_t *ctx, uint16_t reg, uint16_t data_in ) 
{
    return waveform4_write_registers ( ctx, reg, &data_in, 1 );
}

err_t waveform4_read_register ( waveform4_t *ctx, uint16_t reg, uint16_t *data_out ) 
{
    return waveform4_read_registers ( ctx, reg, data_out, 1 );
}

void waveform4_set_rst_pin ( waveform4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void waveform4_set_trg_pin ( waveform4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->trg, state );
}

void waveform4_reset_registers ( waveform4_t *ctx )
{
    waveform4_set_rst_pin ( ctx, 0 );
    Delay_10us ( );
    waveform4_set_rst_pin ( ctx, 1 );
}

err_t waveform4_start_pattern ( waveform4_t *ctx )
{
    err_t error_flag = waveform4_write_register ( ctx, WAVEFORM4_REG_PAT_STATUS, WAVEFORM4_START_PATTERN );
    waveform4_set_trg_pin ( ctx, 0 );
    return error_flag;
}

err_t waveform4_stop_pattern ( waveform4_t *ctx )
{
    err_t error_flag = waveform4_write_register ( ctx, WAVEFORM4_REG_PAT_STATUS, WAVEFORM4_STOP_PATTERN );
    waveform4_set_trg_pin ( ctx, 1 );
    return error_flag;
}

err_t waveform4_update_settings ( waveform4_t *ctx )
{
    return waveform4_write_register ( ctx, WAVEFORM4_REG_RAM_UPDATE, WAVEFORM4_UPDATE_SETTINGS );
}

err_t waveform4_write_sram ( waveform4_t *ctx, uint16_t address, uint16_t *data_in, uint16_t len )
{
    if ( ( address < WAVEFORM4_SRAM_ADDRESS_MIN ) || 
         ( address > WAVEFORM4_SRAM_ADDRESS_MAX ) || 
         ( ( address + len ) > ( WAVEFORM4_SRAM_ADDRESS_MAX + 1 ) ) )
    {
        return WAVEFORM4_ERROR;
    }
    err_t error_flag = waveform4_write_register ( ctx, WAVEFORM4_REG_PAT_STATUS, WAVEFORM4_MEM_ACCESS_ENABLE );
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        error_flag |= waveform4_write_register ( ctx, address + cnt, data_in[ cnt ] << 4 );
    }
    error_flag |= waveform4_write_register ( ctx, WAVEFORM4_REG_PAT_STATUS, WAVEFORM4_MEM_ACCESS_DISABLE );
    return error_flag;
}

err_t waveform4_read_sram ( waveform4_t *ctx, uint16_t address, uint16_t *data_out, uint16_t len )
{
    if ( ( address < WAVEFORM4_SRAM_ADDRESS_MIN ) || 
         ( address > WAVEFORM4_SRAM_ADDRESS_MAX ) || 
         ( ( address + len ) > ( WAVEFORM4_SRAM_ADDRESS_MAX + 1 ) ) )
    {
        return WAVEFORM4_ERROR;
    }
    err_t error_flag = waveform4_write_register ( ctx, WAVEFORM4_REG_PAT_STATUS, WAVEFORM4_MEM_ACCESS_ENABLE | 
                                                                                 WAVEFORM4_BUF_READ );
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        error_flag |= waveform4_read_register ( ctx, address + cnt, &data_out[ cnt ] );
        data_out[ cnt ] >>= 4;
    }
    error_flag |= waveform4_write_register ( ctx, WAVEFORM4_REG_PAT_STATUS, WAVEFORM4_MEM_ACCESS_DISABLE );
    return error_flag;
}

err_t waveform4_set_frequency ( waveform4_t *ctx, uint32_t freq ) 
{
    if ( freq > WAVEFORM4_MASTER_CLOCK )
    {
        return WAVEFORM4_ERROR;
    }
    uint32_t freq_tmp = ( uint32_t ) ( ( float ) freq / ( ( float ) WAVEFORM4_MASTER_CLOCK / 
                                                                    WAVEFORM4_FREQ_RESOLUTION ) );
    uint16_t tw_msb = ( uint16_t ) ( ( freq_tmp >> 8 ) & 0xFFFF );
    uint16_t tw_lsb = ( uint16_t ) ( ( freq_tmp << 8 ) & 0xFF00 );
    
    err_t error_flag = waveform4_stop_pattern ( ctx );
    error_flag |= waveform4_write_register ( ctx, WAVEFORM4_REG_DDS_TW32, tw_msb );
    error_flag |= waveform4_write_register ( ctx, WAVEFORM4_REG_DDS_TW1, tw_lsb );
    error_flag |= waveform4_update_settings ( ctx );
    error_flag |= waveform4_start_pattern ( ctx );
    return error_flag;
}

err_t waveform4_set_gain ( waveform4_t *ctx, uint8_t channel, float gain ) 
{
    if ( ( channel > WAVEFORM4_CHANNEL_4 ) || 
         ( gain > WAVEFORM4_GAIN_MAX ) || ( gain < WAVEFORM4_GAIN_MIN ) )
    {
        return WAVEFORM4_ERROR;
    }
    uint16_t gain_tmp = ( uint16_t ) ( ( ( int16_t ) ( gain * WAVEFORM4_GAIN_RESOLUTION ) ) << 4 );
    
    err_t error_flag = waveform4_stop_pattern ( ctx );
    error_flag |= waveform4_write_register ( ctx, WAVEFORM4_REG_DAC1_DGAIN - channel, gain_tmp );
    error_flag |= waveform4_update_settings ( ctx );
    error_flag |= waveform4_start_pattern ( ctx );
    return error_flag;
}

err_t waveform4_set_wave_output ( waveform4_t *ctx, uint8_t channel, uint8_t wave ) 
{
    if ( ( channel > WAVEFORM4_CHANNEL_4 ) || 
         ( wave > WAVEFORM4_WAVE_NEGATIVE_SAWTOOTH ) )
    {
        return WAVEFORM4_ERROR;
    }
    err_t error_flag = WAVEFORM4_OK;
    uint16_t reg_address = WAVEFORM4_REG_WAV21_CONFIG - channel / 2;
    uint16_t reg_data = 0;
    error_flag |= waveform4_stop_pattern ( ctx );
    error_flag |= waveform4_read_register ( ctx, reg_address, &reg_data );
    reg_data &= ~( 0x00FF << ( ( channel % 2 ) * 8 ) );
    if ( wave < WAVEFORM4_WAVE_TRIANGLE )
    {
        reg_data |= ( ( WAVEFORM4_WAV_CFG_PRESTORE_DDS | WAVEFORM4_WAV_CFG_WAVE_PRESTORED ) << ( ( channel % 2 ) * 8 ) );
        error_flag |= waveform4_write_register ( ctx, reg_address, reg_data );
        error_flag |= waveform4_read_register ( ctx, WAVEFORM4_REG_DDSX_CONFIG, &reg_data );
        if ( WAVEFORM4_WAVE_COSINE == wave )
        {
            reg_data |= ( ( uint16_t ) WAVEFORM4_DDSX_CFG_ENABLE_COSINE << ( channel * 4 ) );
        }
        else
        {
            reg_data &= ~( ( uint16_t ) WAVEFORM4_DDSX_CFG_ENABLE_COSINE << ( channel * 4 ) );
        }
        error_flag |= waveform4_write_register ( ctx, WAVEFORM4_REG_DDSX_CONFIG, reg_data );
    }
    else
    {
        reg_data |= ( ( WAVEFORM4_WAV_CFG_PRESTORE_SAWTOOTH | WAVEFORM4_WAV_CFG_WAVE_PRESTORED ) << ( ( channel % 2 ) * 8 ) );
        error_flag |= waveform4_write_register ( ctx, reg_address, reg_data );
        reg_address = WAVEFORM4_REG_SAW21_CONFIG - channel / 2;
        error_flag |= waveform4_read_register ( ctx, reg_address, &reg_data );
        reg_data &= ~( 0x00FF << ( ( channel % 2 ) * 8 ) );
        if ( WAVEFORM4_WAVE_TRIANGLE == wave )
        {
            reg_data |= ( ( WAVEFORM4_SAW_CFG_TRIANGLE | WAVEFORM4_SAW_CFG_STEP_1 ) << ( ( channel % 2 ) * 8 ) );
        }
        else if ( WAVEFORM4_WAVE_POSITIVE_SAWTOOTH == wave )
        {
            reg_data |= ( ( WAVEFORM4_SAW_CFG_RAMP_UP | WAVEFORM4_SAW_CFG_STEP_1 ) << ( ( channel % 2 ) * 8 ) );
        }
        else
        {
            reg_data |= ( ( WAVEFORM4_SAW_CFG_RAMP_DOWN | WAVEFORM4_SAW_CFG_STEP_1 ) << ( ( channel % 2 ) * 8 ) );
        }
        error_flag |= waveform4_write_register ( ctx, reg_address, reg_data );
    }
    error_flag |= waveform4_update_settings ( ctx );
    error_flag |= waveform4_start_pattern ( ctx );
    return error_flag;
}

// ------------------------------------------------------------------------- END
