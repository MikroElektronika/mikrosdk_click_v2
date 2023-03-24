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
 * @file ccrf3.c
 * @brief ccRF 3 Click Driver.
 */

#include "ccrf3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define CCRF3_DUMMY  0x00

void ccrf3_cfg_setup ( ccrf3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->gp0  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->gp2  = HAL_PIN_NC;
    cfg->gp3  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t ccrf3_init ( ccrf3_t *ctx, ccrf3_cfg_t *cfg ) 
{
    digital_in_init( &ctx->miso, cfg->miso );
    
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, CCRF3_DUMMY ) ) 
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

    digital_in_init( &ctx->gp0, cfg->gp0 );
    digital_in_init( &ctx->gp2, cfg->gp2 );
    digital_in_init( &ctx->gp3, cfg->gp3 );

    digital_out_high( &ctx->rst );

    return SPI_MASTER_SUCCESS;
}

err_t ccrf3_default_cfg ( ccrf3_t *ctx ) 
{
    err_t error_flag = CCRF3_OK;
    
    ccrf3_cmd_strobe( ctx, CCRF3_SRES );
    
    ccrf3_write_reg_single( ctx, CCRF3_IOCFG3, 0xB0 );
    ccrf3_write_reg_single( ctx, CCRF3_IOCFG2, 0x06 );
    ccrf3_write_reg_single( ctx, CCRF3_IOCFG1, 0xB0 );
    ccrf3_write_reg_single( ctx, CCRF3_IOCFG0, 0xB0 );
    ccrf3_write_reg_single( ctx, CCRF3_SYNC_CFG1, 0x0B );
    ccrf3_write_reg_single( ctx, CCRF3_DCFILT_CFG, 0x1C );
    ccrf3_write_reg_single( ctx, CCRF3_IQIC, 0xC6 );
    ccrf3_write_reg_single( ctx, CCRF3_CHAN_BW, 0x08 );
    ccrf3_write_reg_single( ctx, CCRF3_MDMCFG0, 0x05 );
    ccrf3_write_reg_single( ctx, CCRF3_AGC_REF, 0x20 );
    ccrf3_write_reg_single( ctx, CCRF3_AGC_CS_THR, 0x19 );
    ccrf3_write_reg_single( ctx, CCRF3_AGC_CFG1, 0xA9 );
    ccrf3_write_reg_single( ctx, CCRF3_AGC_CFG0, 0xCF );
    ccrf3_write_reg_single( ctx, CCRF3_FIFO_CFG, 0x00 );
    ccrf3_write_reg_single( ctx, CCRF3_SETTLING_CFG, 0x03 );
    ccrf3_write_reg_single( ctx, CCRF3_FS_CFG, 0x14 );
    ccrf3_write_reg_single( ctx, CCRF3_PKT_CFG1, 0x05 );
    ccrf3_write_reg_single( ctx, CCRF3_PKT_CFG0, 0x20 );
    ccrf3_write_reg_single( ctx, CCRF3_PA_CFG2, 0x4F );
    ccrf3_write_reg_single( ctx, CCRF3_PA_CFG1, 0x56 );
    ccrf3_write_reg_single( ctx, CCRF3_PA_CFG0, 0x1C );
    ccrf3_write_reg_single( ctx, CCRF3_PKT_LEN, 0xFF );
    ccrf3_write_reg_single( ctx, CCRF3_IF_MIX_CFG, 0x00 );
    ccrf3_write_reg_single( ctx, CCRF3_FREQOFF_CFG, 0x22 );
    ccrf3_write_reg_single( ctx, CCRF3_FREQ2, 0x6C );
    ccrf3_write_reg_single( ctx, CCRF3_FREQ1, 0x80 );
    ccrf3_write_reg_single( ctx, CCRF3_FREQ0, 0x00 );
    ccrf3_write_reg_single( ctx, CCRF3_FS_DIG1, 0x00 );
    ccrf3_write_reg_single( ctx, CCRF3_FS_DIG0, 0x5F );
    ccrf3_write_reg_single( ctx, CCRF3_FS_CAL0, 0x0E );
    ccrf3_write_reg_single( ctx, CCRF3_FS_DIVTWO, 0x03 );
    ccrf3_write_reg_single( ctx, CCRF3_FS_DSM0, 0x33 );
    ccrf3_write_reg_single( ctx, CCRF3_FS_DVC0, 0x17 );
    ccrf3_write_reg_single( ctx, CCRF3_FS_PFD, 0x50 );
    ccrf3_write_reg_single( ctx, CCRF3_FS_PRE, 0x6E );
    ccrf3_write_reg_single( ctx, CCRF3_FS_REG_DIV_CML, 0x14 );
    ccrf3_write_reg_single( ctx, CCRF3_FS_SPARE, 0xAC );
    ccrf3_write_reg_single( ctx, CCRF3_XOSC5, 0x0E );
    ccrf3_write_reg_single( ctx, CCRF3_XOSC3, 0xC7 );
    ccrf3_write_reg_single( ctx, CCRF3_XOSC1, 0x07 );  
    
    ccrf3_manual_calibration( ctx );

    return error_flag;
}

void ccrf3_hw_reset ( ccrf3_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

uint8_t ccrf3_cmd_strobe ( ccrf3_t *ctx, uint8_t cmd )
{
    uint8_t r_buffer;

    spi_master_set_default_write_data( &ctx->spi, cmd );
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    while ( digital_in_read( &ctx->miso ) );
    spi_master_read( &ctx->spi, &r_buffer, 1 );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_10us( );
    spi_master_set_default_write_data( &ctx->spi, CCRF3_DUMMY );

    return r_buffer;
}

void ccrf3_read_write_burst_single ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes )
{
    if ( reg_address & CCRF3_RADIO_READ_ACCESS )
    {
        spi_master_set_default_write_data( &ctx->spi, CCRF3_DUMMY );
        if ( reg_address & CCRF3_RADIO_BURST_ACCESS )
        {
            spi_master_read( &ctx->spi, rw_data, n_bytes );
        }
        else
        {
            spi_master_read( &ctx->spi, rw_data, 1 );
        }
    }
    else
    {
        if ( reg_address & CCRF3_RADIO_BURST_ACCESS )
        {
            spi_master_write( &ctx->spi, rw_data, n_bytes );
        }
        else
        {
            spi_master_write( &ctx->spi, rw_data, 1 );
        }
    }
}

uint8_t ccrf3_8bit_reg_access ( ccrf3_t *ctx, char access_type, uint8_t reg_address, uint8_t *rw_data, 
                                              uint16_t n_bytes )
{
    uint8_t w_buffer;
    uint8_t r_buffer;

    w_buffer = access_type | reg_address;

    spi_master_set_default_write_data( &ctx->spi, w_buffer );
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    while ( digital_in_read( &ctx->miso ) );
    spi_master_read( &ctx->spi, &r_buffer, 1 );
    ccrf3_read_write_burst_single( ctx, w_buffer, rw_data, n_bytes );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select ); 
    spi_master_set_default_write_data( &ctx->spi, CCRF3_DUMMY );

    return r_buffer;
}

uint8_t ccrf3_16bit_reg_access ( ccrf3_t *ctx, uint8_t access_type, uint8_t ext_address, 
                                               uint8_t reg_address, uint8_t *rw_data, uint8_t n_bytes )
{
    uint8_t w_buffer;
    uint8_t r_buffer;

    w_buffer = access_type | ext_address;

    spi_master_set_default_write_data( &ctx->spi, w_buffer );
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    while ( digital_in_read( &ctx->miso ) );
    spi_master_read( &ctx->spi, &r_buffer, 1 );
    spi_master_write( &ctx->spi, &reg_address, 1 );

    ccrf3_read_write_burst_single( ctx, w_buffer, rw_data, n_bytes );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select ); 
    spi_master_set_default_write_data( &ctx->spi, CCRF3_DUMMY );
    Delay_10us( );

    return r_buffer;
}

err_t ccrf3_read_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t *read_data, uint8_t n_bytes )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    err_t error_flag;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( ( CCRF3_SINGLE_TXFIFO <= temp_addr ) && ( temp_ext == 0 ) )
    {
        error_flag = CCRF3_STATUS_CHIP_RDYN_BM;
    }
    else
    {
        if ( !temp_ext )
        {
            error_flag = ccrf3_8bit_reg_access( ctx, CCRF3_RADIO_BURST_ACCESS | CCRF3_RADIO_READ_ACCESS, 
                                             temp_addr, read_data, n_bytes );
        }
        else if ( temp_ext == 0x2F )
        {
            error_flag = ccrf3_16bit_reg_access( ctx, CCRF3_RADIO_BURST_ACCESS | CCRF3_RADIO_READ_ACCESS, 
                                             temp_ext, temp_addr, read_data, n_bytes );
        }
    }

    return error_flag;
}


err_t ccrf3_write_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t *write_data, uint8_t n_bytes )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    err_t error_flag;

    error_flag = CCRF3_STATUS_ERROR;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( ( CCRF3_SINGLE_TXFIFO <= temp_addr ) && ( temp_ext == 0 ) )
    {
        error_flag = CCRF3_STATUS_CHIP_RDYN_BM;
    }
    else
    {
        if ( !temp_ext )
        {
            error_flag = ccrf3_8bit_reg_access( ctx, CCRF3_RADIO_BURST_ACCESS | CCRF3_RADIO_WRITE_ACCESS, 
                                             temp_addr, write_data, n_bytes );
        }
        else if ( temp_ext == 0x2F )
        {
            error_flag = ccrf3_16bit_reg_access( ctx, CCRF3_RADIO_BURST_ACCESS | CCRF3_RADIO_WRITE_ACCESS, 
                                             temp_ext, temp_addr, write_data, n_bytes );
        }
    }

    return error_flag;
}

uint8_t ccrf3_write_reg_single( ccrf3_t *ctx, uint16_t reg_address, uint8_t write_data )
{
    return ccrf3_write_reg( ctx, reg_address, &write_data, 1 );
}

uint8_t ccrf3_write_tx_fifo ( ccrf3_t *ctx, uint8_t *write_data, uint8_t n_bytes )
{
    return ccrf3_8bit_reg_access( ctx, 0x00, CCRF3_BURST_TXFIFO, write_data, n_bytes );
}

uint8_t ccrf3_read_rx_fifo ( ccrf3_t *ctx, uint8_t *read_data, uint8_t n_bytes )
{
    return ccrf3_8bit_reg_access( ctx, 0x00, CCRF3_BURST_RXFIFO, read_data, n_bytes );
}

void ccrf3_manual_calibration ( ccrf3_t *ctx )
{
    uint8_t original_fs_cal2;
    uint8_t cal_results_vcdac_start_high[ 3 ];
    uint8_t cal_results_vcdac_start_mid[ 3 ];
    uint8_t marc_state;
    uint8_t write_byte;

    ccrf3_write_reg_single( ctx, CCRF3_FS_VCO2, 0x00 );

    ccrf3_read_reg( ctx, CCRF3_FS_CAL2, &original_fs_cal2, 1 );
    ccrf3_write_reg_single( ctx, CCRF3_FS_CAL2, original_fs_cal2 + 2 );

    ccrf3_cmd_strobe( ctx, CCRF3_SCAL );

    do
    {
        ccrf3_read_reg( ctx, CCRF3_MARCSTATE, &marc_state, 1 );
    }
    while ( marc_state != 0x41 );

    ccrf3_read_reg( ctx, CCRF3_FS_VCO2, &cal_results_vcdac_start_high[ 0 ], 1 );
    ccrf3_read_reg( ctx, CCRF3_FS_VCO4, &cal_results_vcdac_start_high[ 1 ], 1 );
    ccrf3_read_reg( ctx, CCRF3_FS_CHP, &cal_results_vcdac_start_high[ 2 ], 1 );

    ccrf3_write_reg_single( ctx, CCRF3_FS_VCO2, 0x00 );

    ccrf3_write_reg_single( ctx, CCRF3_FS_CAL2, original_fs_cal2 );

    ccrf3_cmd_strobe( ctx, CCRF3_SCAL );

    do
    {
        ccrf3_read_reg( ctx, CCRF3_MARCSTATE, &marc_state, 1 );
    }
    while ( marc_state != 0x41 );

    ccrf3_read_reg( ctx, CCRF3_FS_VCO2, &cal_results_vcdac_start_mid[ 0 ], 1 );
    ccrf3_read_reg( ctx, CCRF3_FS_VCO4, &cal_results_vcdac_start_mid[ 1 ], 1 );
    ccrf3_read_reg( ctx, CCRF3_FS_CHP, &cal_results_vcdac_start_mid[ 2 ], 1 );

    if ( cal_results_vcdac_start_high[ 0 ] > cal_results_vcdac_start_mid[ 0 ] )
    {
        ccrf3_write_reg_single( ctx, CCRF3_FS_VCO2, cal_results_vcdac_start_high[ 0 ] );
        ccrf3_write_reg_single( ctx, CCRF3_FS_VCO4, cal_results_vcdac_start_high[ 1 ] );
        ccrf3_write_reg_single( ctx, CCRF3_FS_CHP, cal_results_vcdac_start_high[ 2 ] );
    }
    else
    {
        ccrf3_write_reg_single( ctx, CCRF3_FS_VCO2, cal_results_vcdac_start_mid[ 0 ] );
        ccrf3_write_reg_single( ctx, CCRF3_FS_VCO4, cal_results_vcdac_start_mid[ 1 ] );
        ccrf3_write_reg_single( ctx, CCRF3_FS_CHP, cal_results_vcdac_start_mid[ 2 ] );
    }
}

void ccrf3_set_rx_mode ( ccrf3_t *ctx )
{
    ccrf3_cmd_strobe( ctx, CCRF3_SRX );
}

void ccrf3_set_tx_mode ( ccrf3_t *ctx )
{
    ccrf3_cmd_strobe( ctx, CCRF3_STX );
}

uint8_t ccrf3_read_gp0 ( ccrf3_t *ctx )
{
    return digital_in_read( &ctx->gp0 );
}

uint8_t ccrf3_read_gp2 ( ccrf3_t *ctx )
{
    return digital_in_read( &ctx->gp2 );
}

uint8_t ccrf3_read_gp3 ( ccrf3_t *ctx )
{
    return digital_in_read( &ctx->gp3 );
}

void ccrf3_send_tx_data ( ccrf3_t *ctx, uint8_t *tx_data, uint8_t n_bytes )
{
    uint8_t tx_buffer[ 255 ];

    ctx->packet_counter++;

    tx_buffer[ 0 ] = n_bytes + 3;
    tx_buffer[ 1 ] = ( uint8_t ) ( ctx->packet_counter >> 8 );
    tx_buffer[ 2 ] = ( uint8_t )  ctx->packet_counter;

    for ( uint8_t cnt = 0; cnt < n_bytes; cnt++ )
    {
        tx_buffer[ cnt + 3 ] = tx_data[ cnt ];
    }

    ccrf3_write_tx_fifo( ctx, tx_buffer, n_bytes + 4 );

    ccrf3_set_tx_mode( ctx );

    while ( !ccrf3_read_gp2( ctx ) );
    
    while ( ccrf3_read_gp2( ctx ) );
}

uint8_t ccrf3_receive_rx_data ( ccrf3_t *ctx, uint8_t *rx_data )
{
    uint8_t n_bytes;
    uint8_t marc_state;

    n_bytes = 0;

    if ( ccrf3_read_gp2( ctx ) )
    {
        while ( ccrf3_read_gp2( ctx ) );

        ccrf3_read_reg( ctx, CCRF3_NUM_RXBYTES, &n_bytes, 1 );

        if ( n_bytes != 0 )
        {
            ccrf3_read_reg( ctx, CCRF3_MARCSTATE, &marc_state, 1 );

            if ( ( marc_state & 0x1F ) == 0x11 )
            {
                ccrf3_cmd_strobe( ctx, CCRF3_SFRX );
            }
            else
            {
                ccrf3_read_rx_fifo ( ctx, rx_data, n_bytes );

                if ( rx_data[ n_bytes - 1 ] & 0x80 )
                {
                    ccrf3_set_rx_mode( ctx );
                    
                    ctx->packet_counter = rx_data[ 1 ] << 8;
                    ctx->packet_counter |= rx_data[ 2 ];
                }
            }
        }
    }
    
    return n_bytes;
}

// ------------------------------------------------------------------------- END
