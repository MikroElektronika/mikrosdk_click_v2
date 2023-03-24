/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "ccrf2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define CCRF2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ccrf2_cfg_setup ( ccrf2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->gp0 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->gp2 = HAL_PIN_NC;
    cfg->gp3 = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

CCRF2_RETVAL ccrf2_init ( ccrf2_t *ctx, ccrf2_cfg_t *cfg )
{
    digital_in_init( &ctx->miso, cfg->miso );
    
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = CCRF2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return CCRF2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, CCRF2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->gp0, cfg->gp0 );
    digital_in_init( &ctx->gp2, cfg->gp2 );
    digital_in_init( &ctx->gp3, cfg->gp3 );
    
    digital_out_high( &ctx->rst );

    return CCRF2_OK;
}

void ccrf2_default_cfg ( ccrf2_t *ctx )
{
    ccrf2_cmd_strobe( ctx, CCRF2_SRES );
    
    ccrf2_write_reg_single( ctx, CCRF2_IOCFG3, 0xB0 );
    ccrf2_write_reg_single( ctx, CCRF2_IOCFG2, 0x06 );
    ccrf2_write_reg_single( ctx, CCRF2_IOCFG1, 0xB0 );
    ccrf2_write_reg_single( ctx, CCRF2_IOCFG0, 0xB0 );
    ccrf2_write_reg_single( ctx, CCRF2_SYNC_CFG1, 0x0B );
    ccrf2_write_reg_single( ctx, CCRF2_DCFILT_CFG, 0x1C );
    ccrf2_write_reg_single( ctx, CCRF2_IQIC, 0xC6 );
    ccrf2_write_reg_single( ctx, CCRF2_CHAN_BW, 0x08 );
    ccrf2_write_reg_single( ctx, CCRF2_MDMCFG0, 0x05 );
    ccrf2_write_reg_single( ctx, CCRF2_AGC_REF, 0x20 );
    ccrf2_write_reg_single( ctx, CCRF2_AGC_CS_THR, 0x19 );
    ccrf2_write_reg_single( ctx, CCRF2_AGC_CFG1, 0xA9 );
    ccrf2_write_reg_single( ctx, CCRF2_AGC_CFG0, 0xCF );
    ccrf2_write_reg_single( ctx, CCRF2_FIFO_CFG, 0x00 );
    ccrf2_write_reg_single( ctx, CCRF2_SETTLING_CFG, 0x03 );
    ccrf2_write_reg_single( ctx, CCRF2_FS_CFG, 0x12 );
    ccrf2_write_reg_single( ctx, CCRF2_PKT_CFG1, 0x05 );
    ccrf2_write_reg_single( ctx, CCRF2_PKT_CFG0, 0x20 );
    ccrf2_write_reg_single( ctx, CCRF2_PA_CFG2, 0x4F );
    ccrf2_write_reg_single( ctx, CCRF2_PA_CFG1, 0x56 );
    ccrf2_write_reg_single( ctx, CCRF2_PA_CFG0, 0x1C );
    ccrf2_write_reg_single( ctx, CCRF2_PKT_LEN, 0xFF );
    ccrf2_write_reg_single( ctx, CCRF2_IF_MIX_CFG, 0x00 );
    ccrf2_write_reg_single( ctx, CCRF2_FREQOFF_CFG, 0x22 );
    ccrf2_write_reg_single( ctx, CCRF2_FREQ2, 0x6C );
    ccrf2_write_reg_single( ctx, CCRF2_FREQ1, 0x80 );
    ccrf2_write_reg_single( ctx, CCRF2_FREQ0, 0x00 );
    ccrf2_write_reg_single( ctx, CCRF2_FS_DIG1, 0x00 );
    ccrf2_write_reg_single( ctx, CCRF2_FS_DIG0, 0x5F );
    ccrf2_write_reg_single( ctx, CCRF2_FS_CAL0, 0x0E );
    ccrf2_write_reg_single( ctx, CCRF2_FS_DIVTWO, 0x03 );
    ccrf2_write_reg_single( ctx, CCRF2_FS_DSM0, 0x33 );
    ccrf2_write_reg_single( ctx, CCRF2_FS_DVC0, 0x17 );
    ccrf2_write_reg_single( ctx, CCRF2_FS_PFD, 0x50 );
    ccrf2_write_reg_single( ctx, CCRF2_FS_PRE, 0x6E );
    ccrf2_write_reg_single( ctx, CCRF2_FS_REG_DIV_CML, 0x14 );
    ccrf2_write_reg_single( ctx, CCRF2_FS_SPARE, 0xAC );
    ccrf2_write_reg_single( ctx, CCRF2_XOSC5, 0x0E );
    ccrf2_write_reg_single( ctx, CCRF2_XOSC3, 0xC7 );
    ccrf2_write_reg_single( ctx, CCRF2_XOSC1, 0x07 );  
    
    ccrf2_manual_calibration( ctx );
}

void ccrf2_hw_reset ( ccrf2_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

uint8_t ccrf2_cmd_strobe ( ccrf2_t *ctx, uint8_t cmd )
{
    uint8_t r_buffer;

    spi_master_set_default_write_data( &ctx->spi, cmd );
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    while ( digital_in_read( &ctx->miso ) );
    spi_master_read( &ctx->spi, &r_buffer, 1 );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_10us( );
    spi_master_set_default_write_data( &ctx->spi, CCRF2_DUMMY );

    return r_buffer;
}

void ccrf2_read_write_burst_single ( ccrf2_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes )
{
    if ( reg_address & CCRF2_RADIO_READ_ACCESS )
    {
        spi_master_set_default_write_data( &ctx->spi, CCRF2_DUMMY );
        if ( reg_address & CCRF2_RADIO_BURST_ACCESS )
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
        if ( reg_address & CCRF2_RADIO_BURST_ACCESS )
        {
            spi_master_write( &ctx->spi, rw_data, n_bytes );
        }
        else
        {
            spi_master_write( &ctx->spi, rw_data, 1 );
        }
    }
}

uint8_t ccrf2_8bit_reg_access ( ccrf2_t *ctx, char access_type, uint8_t reg_address, uint8_t *rw_data, 
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
    ccrf2_read_write_burst_single( ctx, w_buffer, rw_data, n_bytes );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select ); 
    spi_master_set_default_write_data( &ctx->spi, CCRF2_DUMMY );

    return r_buffer;
}

uint8_t ccrf2_16bit_reg_access ( ccrf2_t *ctx, uint8_t access_type, uint8_t ext_address, 
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

    ccrf2_read_write_burst_single( ctx, w_buffer, rw_data, n_bytes );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select ); 
    spi_master_set_default_write_data( &ctx->spi, CCRF2_DUMMY );
    Delay_10us( );

    return r_buffer;
}

uint8_t ccrf2_read_reg ( ccrf2_t *ctx, uint16_t reg_address, uint8_t *read_data, uint8_t n_bytes )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;

    rc = CCRF2_STATUS_ERROR;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( ( CCRF2_SINGLE_TXFIFO <= temp_addr ) && ( temp_ext == 0 ) )
    {
        rc = CCRF2_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        if ( !temp_ext )
        {
            rc = ccrf2_8bit_reg_access( ctx, CCRF2_RADIO_BURST_ACCESS | CCRF2_RADIO_READ_ACCESS, 
                                             temp_addr, read_data, n_bytes );
        }
        else if ( temp_ext == 0x2F )
        {
            rc = ccrf2_16bit_reg_access( ctx, CCRF2_RADIO_BURST_ACCESS | CCRF2_RADIO_READ_ACCESS, 
                                             temp_ext, temp_addr, read_data, n_bytes );
        }
    }

    return rc;
}


uint8_t ccrf2_write_reg ( ccrf2_t *ctx, uint16_t reg_address, uint8_t *write_data, uint8_t n_bytes )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;

    rc = CCRF2_STATUS_ERROR;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( ( CCRF2_SINGLE_TXFIFO <= temp_addr ) && ( temp_ext == 0 ) )
    {
        rc = CCRF2_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        if ( !temp_ext )
        {
            rc = ccrf2_8bit_reg_access( ctx, CCRF2_RADIO_BURST_ACCESS | CCRF2_RADIO_WRITE_ACCESS, 
                                             temp_addr, write_data, n_bytes );
        }
        else if ( temp_ext == 0x2F )
        {
            rc = ccrf2_16bit_reg_access( ctx, CCRF2_RADIO_BURST_ACCESS | CCRF2_RADIO_WRITE_ACCESS, 
                                             temp_ext, temp_addr, write_data, n_bytes );
        }
    }

    return rc;
}

uint8_t ccrf2_write_reg_single( ccrf2_t *ctx, uint16_t reg_address, uint8_t write_data )
{
    return ccrf2_write_reg( ctx, reg_address, &write_data, 1 );
}

uint8_t ccrf2_write_tx_fifo ( ccrf2_t *ctx, uint8_t *write_data, uint8_t n_bytes )
{
    return ccrf2_8bit_reg_access( ctx, 0x00, CCRF2_BURST_TXFIFO, write_data, n_bytes );
}

uint8_t ccrf2_read_rx_fifo ( ccrf2_t *ctx, uint8_t *read_data, uint8_t n_bytes )
{
    return ccrf2_8bit_reg_access( ctx, 0x00, CCRF2_BURST_RXFIFO, read_data, n_bytes );
}

void ccrf2_manual_calibration ( ccrf2_t *ctx )
{
    uint8_t original_fs_cal2;
    uint8_t cal_results_vcdac_start_high[ 3 ];
    uint8_t cal_results_vcdac_start_mid[ 3 ];
    uint8_t marc_state;
    uint8_t write_byte;

    // 1) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    ccrf2_write_reg_single( ctx, CCRF2_FS_VCO2, 0x00 );

    // 2) Start with high VCDAC (original VCDAC_START + 2):
    ccrf2_read_reg( ctx, CCRF2_FS_CAL2, &original_fs_cal2, 1 );
    ccrf2_write_reg_single( ctx, CCRF2_FS_CAL2, original_fs_cal2 + 2 );

    // 3) Calibrate and wait for calibration to be done (radio back in IDLE state)
    ccrf2_cmd_strobe( ctx, CCRF2_SCAL );

    do
    {
        ccrf2_read_reg( ctx, CCRF2_MARCSTATE, &marc_state, 1 );
    }
    while ( marc_state != 0x41 );

    // 4) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with high VCDAC_START value
    ccrf2_read_reg( ctx, CCRF2_FS_VCO2, &cal_results_vcdac_start_high[ 0 ], 1 );
    ccrf2_read_reg( ctx, CCRF2_FS_VCO4, &cal_results_vcdac_start_high[ 1 ], 1 );
    ccrf2_read_reg( ctx, CCRF2_FS_CHP, &cal_results_vcdac_start_high[ 2 ], 1 );

    // 5) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    ccrf2_write_reg_single( ctx, CCRF2_FS_VCO2, 0x00 );

    // 6) Continue with mid VCDAC (original VCDAC_START):
    ccrf2_write_reg_single( ctx, CCRF2_FS_CAL2, original_fs_cal2 );

    // 7) Calibrate and wait for calibration to be done (radio back in IDLE state)
    ccrf2_cmd_strobe( ctx, CCRF2_SCAL );

    do
    {
        ccrf2_read_reg( ctx, CCRF2_MARCSTATE, &marc_state, 1 );
    }
    while ( marc_state != 0x41 );

    // 8) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with mid VCDAC_START value
    ccrf2_read_reg( ctx, CCRF2_FS_VCO2, &cal_results_vcdac_start_mid[ 0 ], 1 );
    ccrf2_read_reg( ctx, CCRF2_FS_VCO4, &cal_results_vcdac_start_mid[ 1 ], 1 );
    ccrf2_read_reg( ctx, CCRF2_FS_CHP, &cal_results_vcdac_start_mid[ 2 ], 1 );

    // 9) Write back highest FS_VCO2 and corresponding FS_VCO and FS_CHP result
    if ( cal_results_vcdac_start_high[ 0 ] > cal_results_vcdac_start_mid[ 0 ] )
    {
        ccrf2_write_reg_single( ctx, CCRF2_FS_VCO2, cal_results_vcdac_start_high[ 0 ] );
        ccrf2_write_reg_single( ctx, CCRF2_FS_VCO4, cal_results_vcdac_start_high[ 1 ] );
        ccrf2_write_reg_single( ctx, CCRF2_FS_CHP, cal_results_vcdac_start_high[ 2 ] );
    }
    else
    {
        ccrf2_write_reg_single( ctx, CCRF2_FS_VCO2, cal_results_vcdac_start_mid[ 0 ] );
        ccrf2_write_reg_single( ctx, CCRF2_FS_VCO4, cal_results_vcdac_start_mid[ 1 ] );
        ccrf2_write_reg_single( ctx, CCRF2_FS_CHP, cal_results_vcdac_start_mid[ 2 ] );
    }
}

void ccrf2_set_rx_mode ( ccrf2_t *ctx )
{
    ccrf2_cmd_strobe( ctx, CCRF2_SRX );
}

void ccrf2_set_tx_mode ( ccrf2_t *ctx )
{
    ccrf2_cmd_strobe( ctx, CCRF2_STX );
}

uint8_t ccrf2_read_gp0 ( ccrf2_t *ctx )
{
    return digital_in_read( &ctx->gp0 );
}

uint8_t ccrf2_read_gp2 ( ccrf2_t *ctx )
{
    return digital_in_read( &ctx->gp2 );
}

uint8_t ccrf2_read_gp3 ( ccrf2_t *ctx )
{
    return digital_in_read( &ctx->gp3 );
}

void ccrf2_send_tx_data ( ccrf2_t *ctx, uint8_t *tx_data, uint8_t n_bytes )
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

    ccrf2_write_tx_fifo( ctx, tx_buffer, n_bytes + 4 );

    ccrf2_set_tx_mode( ctx );

    while ( !ccrf2_read_gp2( ctx ) );
    
    while ( ccrf2_read_gp2( ctx ) );
}

uint8_t ccrf2_receive_rx_data ( ccrf2_t *ctx, uint8_t *rx_data )
{
    uint8_t n_bytes;
    uint8_t marc_state;

    n_bytes = 0;

    if ( ccrf2_read_gp2( ctx ) )
    {
        while ( ccrf2_read_gp2( ctx ) );

        ccrf2_read_reg( ctx, CCRF2_NUM_RXBYTES, &n_bytes, 1 );

        if ( n_bytes != 0 )
        {
            ccrf2_read_reg( ctx, CCRF2_MARCSTATE, &marc_state, 1 );

            if ( ( marc_state & 0x1F ) == 0x11 )
            {
                ccrf2_cmd_strobe( ctx, CCRF2_SFRX );
            }
            else
            {
                ccrf2_read_rx_fifo ( ctx, rx_data, n_bytes );

                if ( rx_data[ n_bytes - 1 ] & 0x80 )
                {
                    ccrf2_set_rx_mode( ctx );
                    
                    ctx->packet_counter = rx_data[ 1 ] << 8;
                    ctx->packet_counter |= rx_data[ 2 ];
                }
            }
        }
    }
    
    return n_bytes;
}

// ------------------------------------------------------------------------- END

