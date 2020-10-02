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
    cfg->packet_counter_cfg = 0;
}

CCRF2_RETVAL ccrf2_init ( ccrf2_t *ctx, ccrf2_cfg_t *cfg )
{
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

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG3, 0xB0 );
    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG2, 0x00 );
    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG1, 0xB0 );
    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG0, 0xB0 );
    ccrf2_write_byte_reg( ctx, CCRF2_SYNC_CFG1, 0x0B );
    ccrf2_write_byte_reg( ctx, CCRF2_DCFILT_CFG, 0x1C );
    ccrf2_write_byte_reg( ctx, CCRF2_IQIC, 0xC6 );
    ccrf2_write_byte_reg( ctx, CCRF2_CHAN_BW, 0x08 );
    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG0, 0x05 );
    ccrf2_write_byte_reg( ctx, CCRF2_AGC_REF, 0x20 );
    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CS_THR, 0x19 );
    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG1, 0xA9 );
    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG0, 0xCF );
    ccrf2_write_byte_reg( ctx, CCRF2_FIFO_CFG, 0x00 );
    ccrf2_write_byte_reg( ctx, CCRF2_SETTLING_CFG, 0x03 );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_CFG, 0x12 );
    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG1, 0x05 );
    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG0, 0x20 );
    ccrf2_write_byte_reg( ctx, CCRF2_PA_CFG2, 0x4F );
    ccrf2_write_byte_reg( ctx, CCRF2_PA_CFG1, 0x56 );
    ccrf2_write_byte_reg( ctx, CCRF2_PA_CFG0, 0x1C );
    ccrf2_write_byte_reg( ctx, CCRF2_PKT_LEN, 0xFF );
    ccrf2_write_byte_reg( ctx, CCRF2_IF_MIX_CFG, 0x00 );
    ccrf2_write_byte_reg( ctx, CCRF2_FREQOFF_CFG, 0x22 );
    ccrf2_write_byte_reg( ctx, CCRF2_FREQ2, 0x6C );
    ccrf2_write_byte_reg( ctx, CCRF2_FREQ1, 0x80 );
    ccrf2_write_byte_reg( ctx, CCRF2_FREQ0, 0x00 );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_DIG1, 0x00 );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_DIG0, 0x5F );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_CAL0, 0x0E );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_DIVTWO, 0x03 );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_DSM0, 0x33 );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_DVC0, 0x17 );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_PFD, 0x50 );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_PRE, 0x6E );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_REG_DIV_CML, 0x14 );
    ccrf2_write_byte_reg( ctx, CCRF2_FS_SPARE, 0xAC );
    ccrf2_write_byte_reg( ctx, CCRF2_XOSC5, 0x0E );
    ccrf2_write_byte_reg( ctx, CCRF2_XOSC3, 0xC7 );
    ccrf2_write_byte_reg( ctx, CCRF2_XOSC1, 0x07 );  
}

void ccrf2_generic_transfer ( ccrf2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_1ms( );
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
    uint8_t w_wuffer[ 1 ];
    uint8_t r_buffer[ 2 ];

    w_wuffer[ 0 ] = cmd;

    ccrf2_generic_transfer( ctx, w_wuffer, 1, r_buffer, 1 );

    return r_buffer[ 0 ];
}

uint8_t ccrf2_get_tx_status ( ccrf2_t *ctx )
{
    return ccrf2_cmd_strobe( ctx, CCRF2_SNOP );
}

uint8_t ccrf2_get_rx_status ( ccrf2_t *ctx )
{
    return ccrf2_cmd_strobe ( ctx, CCRF2_SNOP | CCRF2_RADIO_READ_ACCESS );
}

void ccrf2_read_write_burst_single ( ccrf2_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes )
{
    uint16_t cnt;
    uint8_t w_buffer[ 100 ];

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        w_buffer[ cnt ] = rw_data[ cnt ];
    }

    if ( reg_address & CCRF2_RADIO_READ_ACCESS )
    {
        if ( reg_address & CCRF2_RADIO_BURST_ACCESS )
        {
            rw_data[ cnt ] = spi_master_read( &ctx->spi, rw_data, n_bytes );
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
            spi_master_write( &ctx->spi, w_buffer, n_bytes );
        }
        else
        {
            spi_master_write( &ctx->spi, w_buffer, 1 );
        }
    }
}

CCRF2_STATUS_T ccrf2_byte_reg_access ( ccrf2_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes )
{
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = ctx->access_type | reg_address;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_write( &ctx->spi, w_buffer, 1 );
    ccrf2_read_write_burst_single( ctx, ctx->access_type | reg_address, rw_data, n_bytes );

    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1ms( );

    return CCRF2_STATUS_OK;
}

CCRF2_STATUS_T ccrf2_bytes_reg_access ( ccrf2_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint8_t n_bytes )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = ctx->access_type | ctx->ext_addr;
    w_buffer[ 1 ] = reg_address;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_write( &ctx->spi, w_buffer, 2 );
    ccrf2_read_write_burst_single( ctx, ctx->access_type | ctx->ext_addr, rw_data, n_bytes );

    spi_master_deselect_device( ctx->chip_select ); 
    Delay_1ms( );

    return CCRF2_STATUS_OK;
}

CCRF2_STATUS_T ccrf2_read_bytes_reg ( ccrf2_t *ctx, uint16_t reg_address, uint8_t *read_data, uint8_t n_bytes )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;

    rc = CCRF2_STATUS_ERROR;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( CCRF2_SINGLE_TXFIFO <= reg_address && !temp_ext )
    {
        rc = CCRF2_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        ctx->access_type = CCRF2_RADIO_BURST_ACCESS | CCRF2_RADIO_READ_ACCESS;
        if ( !temp_ext )
        {
            rc = ccrf2_byte_reg_access( ctx, temp_addr, read_data, n_bytes );
        }
        else if ( temp_ext == 0x2F )
        {
            ctx->ext_addr = temp_ext;
            rc = ccrf2_bytes_reg_access( ctx, reg_address, read_data, n_bytes );
        }
    }

    return rc;
}

uint8_t ccrf2_read_byte_reg ( ccrf2_t *ctx, uint16_t reg_address )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;
    uint8_t r_buffer[ 1 ];

    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( CCRF2_SINGLE_TXFIFO <= reg_address && !temp_ext )
    {
        rc = CCRF2_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        ctx->access_type = CCRF2_RADIO_BURST_ACCESS | CCRF2_RADIO_READ_ACCESS;
        if ( !temp_ext )
        {
            ccrf2_byte_reg_access(  ctx, temp_addr, r_buffer, 1 );
        }
        else if ( temp_ext == 0x2F )
        {
            ctx->ext_addr = temp_ext;
            ccrf2_bytes_reg_access( ctx, reg_address, r_buffer, 1 );
        }
    }

    return r_buffer[ 0 ];
}

void ccrf2_write_bytes_reg ( ccrf2_t *ctx, uint16_t reg_address, uint8_t *write_data, uint8_t n_bytes )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;

    rc = 0;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( CCRF2_SINGLE_TXFIFO <= temp_addr && !temp_ext )
    {
        rc = CCRF2_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        ctx->access_type = CCRF2_RADIO_BURST_ACCESS | CCRF2_RADIO_WRITE_ACCESS;
        if ( !temp_ext)
        {
            ccrf2_byte_reg_access( ctx, temp_addr, write_data, n_bytes );
        }
        else if ( temp_ext == 0x2F )
        {
            ctx->ext_addr = temp_ext;
            ccrf2_bytes_reg_access( ctx, temp_addr, write_data, n_bytes );
        }
    }
}

uint8_t ccrf2_write_byte_reg ( ccrf2_t *ctx, uint16_t reg_address, uint8_t write_data )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;
    uint8_t w_buffer[ 1 ];

    rc = 0;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    w_buffer[ 0 ] = write_data;

    if ( CCRF2_SINGLE_TXFIFO <= temp_addr && !temp_ext )
    {
        rc = CCRF2_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        ctx->access_type = CCRF2_RADIO_BURST_ACCESS | CCRF2_RADIO_WRITE_ACCESS;
        if ( !temp_ext )
        {
            rc = ccrf2_byte_reg_access( ctx, temp_addr, w_buffer, 1 );
        }
        else if ( temp_ext == 0x2F )
        {
            ctx->ext_addr = temp_ext;
            rc = ccrf2_bytes_reg_access( ctx, temp_addr, w_buffer, 1 );
        }
    }

    return rc;
}

void ccrf2_read_write_burst_single1 ( ccrf2_t *ctx, uint8_t reg_address, uint8_t *read_data, uint8_t n_bytes )
{
    uint16_t cnt;

    if ( reg_address & CCRF2_RADIO_READ_ACCESS )
    {
        if ( reg_address & CCRF2_RADIO_BURST_ACCESS )
        {
           spi_master_read( &ctx->spi, read_data, n_bytes );
        }
        else
        {
            spi_master_read( &ctx->spi, read_data, 1 );
        }
    }
    else
    {

        if ( reg_address & CCRF2_RADIO_BURST_ACCESS )
        {

            spi_master_write( &ctx->spi, read_data, n_bytes );
        }
        else
        {
            spi_master_write( &ctx->spi, read_data, 1 );
        }
    }
}

uint8_t ccrf2_access_byte_register ( ccrf2_t *ctx, uint8_t reg_address, uint8_t *read_data, uint8_t n_bytes )
{
    uint8_t r_buffer[ 1 ];
    uint8_t w_buffer[ 255 ];
    uint8_t cnt;

    w_buffer[ 0 ] = ctx->access_type | reg_address;

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        w_buffer[ cnt + 1 ] = read_data[ cnt ];
    }

    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );

    spi_master_write_then_read( &ctx->spi, w_buffer, n_bytes, r_buffer, 1 );

    ccrf2_read_write_burst_single( ctx, w_buffer[ 0 ], w_buffer, n_bytes );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select ); 

    return r_buffer[ 0 ];
}

uint8_t ccrf2_write_tx_fifo ( ccrf2_t *ctx, uint8_t *write_data, uint8_t n_bytes )
{
    ctx->access_type = 0;
    return ccrf2_byte_reg_access( ctx, CCRF2_BURST_TXFIFO, write_data, n_bytes );
}

uint8_t ccrf2_read_rx_fifo ( ccrf2_t *ctx, uint8_t *read_data, uint8_t n_bytes )
{
    ctx->access_type = 0;
    return ccrf2_byte_reg_access( ctx, CCRF2_BURST_RXFIFO, read_data, n_bytes );
}

void ccrf2_manual_calibration ( ccrf2_t *ctx )
{
    uint8_t original_fs_cal2;
    uint8_t cal_results_vcdac_start_high[ 3 ];
    uint8_t cal_results_vcdac_start_mid[ 3 ];
    uint8_t marc_state;
    uint8_t write_byte;

    // 1) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    write_byte = 0x00;
    ccrf2_write_bytes_reg( ctx, CCRF2_FS_VCO2, &write_byte, 1 );

    // 2) Start with high VCDAC (original VCDAC_START + 2):
    ccrf2_read_bytes_reg( ctx, CCRF2_FS_CAL2, &original_fs_cal2, 1 );
    write_byte = original_fs_cal2 + 2;
    ccrf2_write_bytes_reg( ctx, CCRF2_FS_CAL2, &write_byte, 1 );

    // 3) Calibrate and wait for calibration to be done (radio back in IDLE state)
    ccrf2_cmd_strobe( ctx, CCRF2_SCAL );

    do
    {
        ccrf2_read_bytes_reg( ctx, CCRF2_MARCSTATE, &marc_state, 1 );
    }
    while ( marc_state != 0x41 );

    // 4) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with high VCDAC_START value
    ccrf2_read_bytes_reg( ctx, CCRF2_FS_VCO2, &cal_results_vcdac_start_high[ 0 ], 1 );
    ccrf2_read_bytes_reg( ctx, CCRF2_FS_VCO4, &cal_results_vcdac_start_high[ 1 ], 1 );
    ccrf2_read_bytes_reg( ctx, CCRF2_FS_CHP, &cal_results_vcdac_start_high[ 2 ], 1 );

    // 5) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    write_byte = 0x00;
    ccrf2_write_bytes_reg( ctx, CCRF2_FS_VCO2, &write_byte, 1 );

    // 6) Continue with mid VCDAC (original VCDAC_START):
    write_byte = original_fs_cal2;
    ccrf2_write_bytes_reg( ctx, CCRF2_FS_CAL2, &write_byte, 1 );

    // 7) Calibrate and wait for calibration to be done (radio back in IDLE state)
    ccrf2_cmd_strobe( ctx, CCRF2_SCAL );

    do
    {
        ccrf2_read_bytes_reg( ctx, CCRF2_MARCSTATE, &marc_state, 1 );
    }
    while ( marc_state != 0x41 );

    // 8) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with mid VCDAC_START value
    ccrf2_read_bytes_reg( ctx, CCRF2_FS_VCO2, &cal_results_vcdac_start_mid[ 0 ], 1 );
    ccrf2_read_bytes_reg( ctx, CCRF2_FS_VCO4, &cal_results_vcdac_start_mid[ 1 ], 1 );
    ccrf2_read_bytes_reg( ctx, CCRF2_FS_CHP, &cal_results_vcdac_start_mid[ 2 ], 1 );

    // 9) Write back highest FS_VCO2 and corresponding FS_VCO and FS_CHP result
    if ( cal_results_vcdac_start_high[ 0 ] > cal_results_vcdac_start_mid[ 0 ] )
    {
        write_byte = cal_results_vcdac_start_high[ 0 ];
        ccrf2_write_bytes_reg( ctx, CCRF2_FS_VCO2, &write_byte, 1 );
        write_byte = cal_results_vcdac_start_high[ 1 ];
        ccrf2_write_bytes_reg( ctx, CCRF2_FS_VCO4, &write_byte, 1 );
        write_byte = cal_results_vcdac_start_high[ 2 ];
        ccrf2_write_bytes_reg( ctx, CCRF2_FS_CHP, &write_byte, 1 );
    }
    else
    {
        write_byte = cal_results_vcdac_start_mid[ 0 ];
        ccrf2_write_bytes_reg( ctx, CCRF2_FS_VCO2, &write_byte, 1 );
        write_byte = cal_results_vcdac_start_mid[ 1 ];
        ccrf2_write_bytes_reg( ctx, CCRF2_FS_VCO4, &write_byte, 1 );
        write_byte = cal_results_vcdac_start_mid[ 2 ];
        ccrf2_write_bytes_reg( ctx, CCRF2_FS_CHP, &write_byte, 1 );
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

uint8_t ccrf2_get_interrupt ( ccrf2_t *ctx )
{
    return !digital_in_read( &ctx->gp3 );
}

void ccrf2_send_tx_data ( ccrf2_t *ctx, uint8_t *tx_data, uint8_t n_bytes )
{
    uint8_t cnt;
    uint8_t tx_buffer[ 255 ];

    ctx->packet_counter++;

    tx_buffer[ 0 ] = n_bytes;
    tx_buffer[ 1 ] = ( uint8_t ) ( ctx->packet_counter >> 8 );
    tx_buffer[ 2 ] = ( uint8_t )  ctx->packet_counter;

    for ( cnt = 0; cnt < n_bytes + 3; cnt++ )
    {
        tx_buffer[ cnt + 3 ] = tx_data[ cnt ];
    }

    ccrf2_write_tx_fifo( ctx, tx_buffer, n_bytes + 3 );

    ccrf2_cmd_strobe( ctx, CCRF2_STX );

    while ( ccrf2_get_interrupt( ctx ) );
}

void ccrf2_receive_rx_data ( ccrf2_t *ctx, uint8_t *rx_data )
{
    uint8_t n_bytes;
    uint8_t marc_state;

    n_bytes = 0;

    if ( ccrf2_get_interrupt( ctx ) )
    {
        while ( ccrf2_get_interrupt( ctx ) );

        n_bytes = ccrf2_read_byte_reg( ctx, CCRF2_NUM_RXBYTES );

        if ( n_bytes != 0 )
        {
            marc_state = ccrf2_read_byte_reg( ctx, CCRF2_MARCSTATE );

            if ( ( marc_state & 0x1F ) == 0x11 )
            {
                ccrf2_cmd_strobe( ctx, CCRF2_SFRX );
            }
            else
            {
                ccrf2_read_rx_fifo ( ctx, &rx_data[ 0 ], n_bytes );

                if ( rx_data[ n_bytes - 1 ] & 0x80 )
                {
                    ccrf2_set_rx_mode( ctx );
                }
            }
        }
    }
}

void ccrf2_enable_analog_transfer_gpio3 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG3 );

    tmp |= 0x80;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG3, tmp );
}

void ccrf2_disable_analog_transfer_gpio3 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG3 );

    tmp &= 0x7F;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG3, tmp );
}

void ccrf2_enable_invert_output_gpio3 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG3 );

    tmp |= 0x40;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG3, tmp );
}

void ccrf2_disable_invert_output_gpio3 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG3 );

    tmp &= 0x3F;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG3, tmp );
}

void ccrf2_enable_analog_transfer_gpio2 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG2 );

    tmp |= 0x80;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG2, tmp );
}

void ccrf2_disable_analog_transfer_gpio2 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG2 );

    tmp &= 0x7F;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG2, tmp );
}

void ccrf2_enable_invert_output_gpio2 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG2 );

    tmp |= 0x40;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG2, tmp );
}

void ccrf2_disable_invert_output_gpio2 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG2 );

    tmp &= 0x3F;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG2, tmp );
}

void ccrf2_enable_analog_transfer_gpio0 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG0 );

    tmp |= 0x80;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG0, tmp );
}

void ccrf2_disable_analog_transfer_gpio0 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG0 );

    tmp &= 0x7F;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG0, tmp );
}

void ccrf2_enable_invert_output_gpio0 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG0 );

    tmp |= 0x40;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG0, tmp );
}

void ccrf2_disable_invert_output_gpio0 ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IOCFG0 );

    tmp &= 0x3F;

    ccrf2_write_byte_reg( ctx, CCRF2_IOCFG0, tmp );
}

void ccrf2_set_sync_mode ( ccrf2_t *ctx, uint8_t s_mode )
{
    uint8_t tmp;

    s_mode &= 0x07;
    s_mode <<= 2;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_SYNC_CFG0 );
    tmp &= 0xE3;
    tmp |= s_mode;

    ccrf2_write_byte_reg( ctx, CCRF2_SYNC_CFG0, tmp );
}

void ccrf2_set_sync_num_error ( ccrf2_t *ctx, uint8_t num_err )
{
    uint8_t tmp;

    num_err &= 0x03;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_SYNC_CFG0 );
    tmp &= 0xFC;
    tmp |= num_err;

    ccrf2_write_byte_reg( ctx, CCRF2_SYNC_CFG0, tmp );
}

void ccrf2_config_modem_mode ( ccrf2_t *ctx, uint8_t m_mode )
{
    uint8_t tmp;

    m_mode &= 0x03;
    m_mode <<= 6;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MODCFG_DEV_E );
    tmp &= 0x3F;
    tmp |= m_mode;

    ccrf2_write_byte_reg( ctx, CCRF2_MODCFG_DEV_E, tmp );
}

void ccrf2_set_modulation_format ( ccrf2_t *ctx, uint8_t m_format )
{
    uint8_t tmp;

    m_format &= 0x07;
    m_format <<= 3;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MODCFG_DEV_E );
    tmp &= 0xC7;
    tmp |= m_format;

    ccrf2_write_byte_reg( ctx, CCRF2_MODCFG_DEV_E, tmp );
}

void ccrf2_set_dc_period_filter ( ccrf2_t *ctx, uint16_t n_samples )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_DCFILT_CFG );
    tmp &= 0xC7;

    switch ( n_samples )
    {
        case 32:
        {
            tmp |= 0x00;
        }
        case 64:
        {
            tmp |= 0x08;
        }
        case 128:
        {
            tmp |= 0x10;
        }
        case 256:
        {
            tmp |= 0x18;
        }
        case 512:
        {
            tmp |= 0x38;
        }
        default :
        {
            tmp |= 0x08;
        }
    }

    ccrf2_write_byte_reg( ctx, CCRF2_DCFILT_CFG, tmp );
}

void ccrf2_set_min_num_transmitted ( ccrf2_t *ctx, uint8_t mNumber )
{
    uint8_t tmp;

    mNumber &= 0x0F;
    mNumber <<= 2;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PREAMBLE_CFG1 );
    tmp &= 0x87;
    tmp |= mNumber;

    ccrf2_write_byte_reg( ctx, CCRF2_PREAMBLE_CFG1, tmp );
}

void ccrf2_config_preamble ( ccrf2_t *ctx, uint8_t p_value )
{
    uint8_t tmp;

    p_value &= 0x03;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PREAMBLE_CFG1 );
    tmp &= 0xFC;
    tmp |= p_value;

    ccrf2_write_byte_reg( ctx, CCRF2_PREAMBLE_CFG1, tmp );
}

void ccrf2_disable_preamble_detection ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PREAMBLE_CFG0 );
    tmp &= 0xDF;

    ccrf2_write_byte_reg( ctx, CCRF2_PREAMBLE_CFG0, tmp );
}

void ccrf2_enable_preamble_detection ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PREAMBLE_CFG0 );
    tmp |= 0x20;

    ccrf2_write_byte_reg( ctx, CCRF2_PREAMBLE_CFG0, tmp );
}

void ccrf2_start_up_timer_pqt ( ccrf2_t *ctx, uint8_t v_timer )
{
    uint8_t tmp;

    v_timer &= 0x01;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PREAMBLE_CFG0 );

    if ( v_timer )
    {
        tmp |= 0x10;
    }
    else
    {
        tmp &= 0xEF;
    }

    ccrf2_write_byte_reg( ctx, CCRF2_PREAMBLE_CFG0, tmp );
}

void ccrf2_disable_iq_comp ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IQIC );
    tmp &= 0x7F;

    ccrf2_write_byte_reg( ctx, CCRF2_IQIC, tmp );
}

void ccrf2_enable_iq_comp ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IQIC );
    tmp |= 0x80;

    ccrf2_write_byte_reg( ctx, CCRF2_IQIC, tmp );
}

void ccrf2_disable_iqic_coef ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IQIC );
    tmp &= 0xBF;

    ccrf2_write_byte_reg( ctx, CCRF2_IQIC, tmp );
}

void ccrf2_enable_iqic_coef ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IQIC );
    tmp |= 0x40;

    ccrf2_write_byte_reg( ctx, CCRF2_IQIC, tmp );
}

void ccrf2_set_iqic_block_length_settling ( ccrf2_t *ctx, uint8_t iqicLen )
{
    uint8_t tmp;

    iqicLen &= 0x03;
    iqicLen <<= 4;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IQIC );
    tmp &= 0xCF;
    tmp |= iqicLen;

    ccrf2_write_byte_reg( ctx, CCRF2_IQIC, tmp );
}

void ccrf2_set_iqic_block_length( ccrf2_t *ctx, uint8_t iqicLen )
{
    uint8_t tmp;

    iqicLen &= 0x03;
    iqicLen <<= 2;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IQIC );
    tmp &= 0x3F;
    tmp |= iqicLen;

    ccrf2_write_byte_reg( ctx, CCRF2_IQIC, tmp );
}

void ccrf2_set_iqic_ch_lvl_threshold ( ccrf2_t *ctx, uint8_t iqic_thr )
{
    uint8_t tmp;

    iqic_thr &= 0x03;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_IQIC );
    tmp &= 0xFC;
    tmp |= iqic_thr;

    ccrf2_write_byte_reg( ctx, CCRF2_IQIC, tmp );
}

void ccrf2_disable_ch_filter ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_CHAN_BW  );
    tmp &= 0x7F;

    ccrf2_write_byte_reg( ctx, CCRF2_CHAN_BW, tmp );
}

void ccrf2_enable_ch_filter ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_CHAN_BW );
    tmp |= 0x80;

    ccrf2_write_byte_reg( ctx, CCRF2_CHAN_BW, tmp );
}

void ccrf2_disable_fifo ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG1 );
    tmp &= 0xBF;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_enable_fifo ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG1 );
    tmp |= 0x40;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_disable_manchester_mode ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG1 );
    tmp &= 0xDF;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_enable_manchester_mode ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG1 );
    tmp |= 0x20;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_disable_invert_data ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG1 );
    tmp &= 0xEF;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_enable_invert_data ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG1 );
    tmp |= 0x10;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_disable_collision_detect ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG1 );
    tmp &= 0xF7;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_enable_collision_detect ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG1 );
    tmp |= 0x08;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_set_dvga_gain( ccrf2_t *ctx, uint8_t dvga_gain )
{
    uint8_t tmp;

    dvga_gain &= 0x03;
    dvga_gain <<= 1;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG1 );
    tmp &= 0xF9;
    tmp |= dvga_gain;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_disable_transparent_mode ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG0 );
    tmp &= 0xBF;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG1, tmp );
}

void ccrf2_enable_transparent_mode ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG0 );
    tmp |= 0x40;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG0, tmp );
}

void ccrf2_set_transparent_data_filter ( ccrf2_t *ctx, uint8_t t_data )
{
    uint8_t tmp;

    t_data &= 0x01;
    t_data <<= 3;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG0 );
    tmp &= 0xF7;
    tmp |= t_data;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG0, tmp );
}

void ccrf2_disable_viterbi_detection ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG0 );
    tmp &= 0xFB;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG0, tmp );
}

void ccrf2_enable_viterbi_detection ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_MDMCFG0 );
    tmp |= 0x04;

    ccrf2_write_byte_reg( ctx, CCRF2_MDMCFG0, tmp );
}

void ccrf2_set_rssi_threshold ( ccrf2_t *ctx, uint8_t rssi_thr )
{
    uint8_t tmp;

    rssi_thr &= 0x01;
    rssi_thr <<= 7;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG3 );
    tmp &= 0x7F;
    tmp |= rssi_thr;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG3, tmp );
}

void ccrf2_set_receiver_max_gain ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG2 );
    tmp &= 0x7F;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG2, tmp );
}

void ccrf2_set_receiver_previous_gain ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG2 );
    tmp |= 0x80;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG2, tmp );
}

void ccrf2_set_performance_mode ( ccrf2_t *ctx, uint8_t p_mode )
{
    uint8_t tmp;

    p_mode &= 0x03;
    p_mode <<= 5;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG2 );
    tmp &= 0x9F;
    tmp |= p_mode;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG2, tmp );
}

void ccrf2_set_agc_behavior ( ccrf2_t *ctx, uint8_t agc_value )
{
    uint8_t tmp;

    agc_value &= 0x07;
    agc_value <<= 5;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG1 );
    tmp &= 0x1F;
    tmp |= agc_value;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG1, tmp );
}

void ccrf2_set_agc_integration ( ccrf2_t *ctx, uint8_t agc_value )
{
    uint8_t tmp;

    agc_value &= 0x07;
    agc_value <<= 2;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG1 );
    tmp &= 0xE3;
    tmp |= agc_value;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG1, tmp );
}

void ccrf2_set_wait_time_agc_gain ( ccrf2_t *ctx, uint8_t w_time )
{
    uint8_t tmp;

    w_time &= 0x03;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG1 );
    tmp &= 0xFC;
    tmp |= w_time;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG1, tmp );
}

void ccrf2_set_agc_hysteresis_lvl ( ccrf2_t *ctx, uint8_t agc_value )
{
    uint8_t tmp;

    agc_value &= 0x03;
    agc_value <<= 6;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG0 );
    tmp &= 0x3F;
    tmp |= agc_value;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG0, tmp );
}

void ccrf2_set_agc_slew_rate_limit ( ccrf2_t *ctx, uint8_t agc_value )
{
    uint8_t tmp;

    agc_value &= 0x03;
    agc_value <<= 4;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG0 );
    tmp &= 0xCF;
    tmp |= agc_value;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG0, tmp );
}

void ccrf2_set_rssi_valid_cnt ( ccrf2_t *ctx, uint8_t rssi_cnt )
{
    uint8_t tmp;

    rssi_cnt &= 0x03;
    rssi_cnt <<= 2;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG0 );
    tmp &= 0xF3;
    tmp |= rssi_cnt;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG0, tmp );
}

void ccrf2_set_decimation_factor ( ccrf2_t *ctx, uint8_t dec_factor )
{
    uint8_t tmp;

    dec_factor &= 0x03;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_AGC_CFG0 );
    tmp &= 0xFC;
    tmp |= dec_factor;

    ccrf2_write_byte_reg( ctx, CCRF2_AGC_CFG0, tmp );
}

void ccrf2_set_address_packet_rx ( ccrf2_t *ctx, uint8_t dev_addr )
{
    ccrf2_write_byte_reg( ctx, CCRF2_DEV_ADDR, dev_addr );
}

void ccrf2_disable_out_of_lock_detector ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_FS_CFG );
    tmp &= 0xF0;

    ccrf2_write_byte_reg( ctx, CCRF2_FS_CFG, tmp );
}

void ccrf2_enable_out_of_lock_detector ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_FS_CFG );
    tmp |= 0x10;

    ccrf2_write_byte_reg( ctx, CCRF2_FS_CFG, tmp );
}

void ccrf2_select_band_settings ( ccrf2_t *ctx, uint8_t band_settings )
{
    uint8_t tmp;

    band_settings &= 0x0F;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_FS_CFG );
    tmp &= 0xF0;
    tmp |= band_settings;

    ccrf2_write_byte_reg( ctx, CCRF2_FS_CFG, tmp );
}

void ccrf2_set_wor_resolution ( ccrf2_t *ctx, uint8_t wor_res )
{
    uint8_t tmp;

    wor_res &= 0x03;
    wor_res <<= 6;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_WOR_CFG1 );
    tmp &= 0x3F;
    tmp |= wor_res;

    ccrf2_write_byte_reg( ctx, CCRF2_WOR_CFG1, tmp );
}

void ccrf2_set_wor_mode ( ccrf2_t *ctx, uint8_t w_mode )
{
    uint8_t tmp;

    w_mode &= 0x07;

    if ( w_mode > 4 )
    {
        w_mode = 0x01;
    }

    w_mode <<= 3;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_WOR_CFG1 );
    tmp &= 0xC7;
    tmp |= w_mode;

    ccrf2_write_byte_reg( ctx, CCRF2_WOR_CFG1, tmp );
}

void ccrf2_set_event_timeout ( ccrf2_t *ctx, uint8_t e_timeout )
{
    uint8_t tmp;

    e_timeout &= 0x07;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_WOR_CFG1 );
    tmp &= 0xF8;
    tmp |= e_timeout;

    ccrf2_write_byte_reg( ctx, CCRF2_WOR_CFG1, tmp );
}

void ccrf2_disable_clock_division ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_WOR_CFG0 );
    tmp &= 0xDF;

    ccrf2_write_byte_reg( ctx, CCRF2_WOR_CFG0, tmp );
}

void ccrf2_enable_clock_division ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_WOR_CFG0 );
    tmp |= 0x20;

    ccrf2_write_byte_reg( ctx, CCRF2_WOR_CFG0, tmp );
}

void ccrf2_set_cca_mode ( ccrf2_t *ctx, uint8_t cca_mode )
{
    uint8_t tmp;

    cca_mode &= 0x07;
    cca_mode <<= 2;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG2 );
    tmp &= 0xE3;
    tmp |= cca_mode;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG2, tmp );
}

void ccrf2_set_packet_format ( ccrf2_t *ctx, uint8_t p_format )
{
    uint8_t tmp;

    p_format &= 0x03;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG2 );
    tmp &= 0xFC;
    tmp |= p_format;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG2, tmp );
}

void ccrf2_disable_data_whitening ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG1 );
    tmp &= 0xBF;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG1, tmp );
}

void ccrf2_enable_data_whitening ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG1 );
    tmp |= 0x40;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG1, tmp );
}

void ccrf2_set_crc_config ( ccrf2_t *ctx, uint8_t crc_config )
{
    uint8_t tmp;

    crc_config &= 0x03;
    crc_config <<= 2;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG1 );
    tmp &= 0xF3;
    tmp |= crc_config;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG2, tmp );
}

void ccrf2_disable_data_swap ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG1 );
    tmp &= 0xFD;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG1, tmp );
}

void ccrf2_enable_data_swap ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG1 );
    tmp |= 0x02;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG1, tmp );
}

void ccrf2_append_status ( ccrf2_t *ctx, uint8_t app_status )
{
    uint8_t tmp;

    app_status &= 0x01;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG1 );

    if ( app_status )
    {
        tmp |= 0x01;
    }
    else
    {
        tmp &= 0xFE;
    }

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG1, tmp );
}

void ccrf2_disable_uart_mode ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG0 );
    tmp &= 0xFD;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG0, tmp );
}

void ccrf2_enable_uart_mode ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG0 );
    tmp |= 0x02;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG0, tmp );
}

void ccrf2_disable_uart_swap ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG0 );
    tmp &= 0xFE;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG0, tmp );
}

void ccrf2_enable_uart_swap ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PKT_CFG0 );
    tmp |= 0x01;

    ccrf2_write_byte_reg( ctx, CCRF2_PKT_CFG0, tmp );
}

void ccrf2_set_rx_off_mode ( ccrf2_t *ctx, uint8_t rx_off_mode )
{
    uint8_t tmp;

    rx_off_mode &= 0x03;
    rx_off_mode <<= 4;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_RFEND_CFG1 );

    tmp &= 0xCF;
    tmp |= rx_off_mode;

    ccrf2_write_byte_reg( ctx, CCRF2_RFEND_CFG1, tmp );
}

void ccrf2_set_tx_off_mode ( ccrf2_t *ctx, uint8_t tx_off_mode )
{
    uint8_t tmp;

    tx_off_mode &= 0x03;
    tx_off_mode <<= 4;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_RFEND_CFG0 );

    tmp &= 0xCF;
    tmp |= tx_off_mode;

    ccrf2_write_byte_reg( ctx, CCRF2_RFEND_CFG0, tmp );
}

void ccrf2_set_tx_upsampler ( ccrf2_t *ctx, uint8_t tx_upsampler )
{
    uint8_t tmp;

    tx_upsampler &= 0x07;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_PA_CFG0 );

    tmp &= 0xF8;
    tmp |= tx_upsampler;

    ccrf2_write_byte_reg( ctx, CCRF2_PA_CFG0, tmp );
}

void ccrf2_set_packet_length ( ccrf2_t *ctx, uint8_t pack_len )
{
    ccrf2_write_byte_reg( ctx, CCRF2_PKT_LEN, pack_len );
}

void ccrf2_disable_freq_offset_correction ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_FREQOFF_CFG );
    tmp &= 0xDF;

    ccrf2_write_byte_reg( ctx, CCRF2_FREQOFF_CFG, tmp );
}

void ccrf2_enable_freq_offset_correction ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_FREQOFF_CFG );
    tmp |= 0x20;

    ccrf2_write_byte_reg( ctx, CCRF2_FREQOFF_CFG, tmp );
}

void ccrf2_set_ext_clock_freq ( ccrf2_t *ctx, uint8_t ec_freq )
{
    uint8_t tmp;

    ec_freq &= 0x1F;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_ECG_CFG );

    tmp &= 0xE0;
    tmp |= ec_freq;

    ccrf2_write_byte_reg( ctx, CCRF2_ECG_CFG, tmp );
}

void ccrf2_disable_cfm_mode ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_CFM_DATA_CFG );
    tmp &= 0xFE;

    ccrf2_write_byte_reg( ctx, CCRF2_CFM_DATA_CFG, tmp );
}

void ccrf2_enable_cfm_mode ( ccrf2_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_CFM_DATA_CFG );
    tmp |= 0x01;

    ccrf2_write_byte_reg( ctx, CCRF2_CFM_DATA_CFG, tmp );
}

void ccrf2_set_freq_offset ( ccrf2_t *ctx, uint16_t freq_offset )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( freq_offset >> 8 );
    tmp_l = ( uint8_t ) ( freq_offset & 0x00FF );

    ccrf2_cmd_strobe( ctx, CCRF2_AFC );

    ccrf2_write_byte_reg( ctx, CCRF2_FREQOFF1, tmp_m );
    ccrf2_write_byte_reg( ctx, CCRF2_FREQOFF0, tmp_l );
}

void ccrf2_set_fs_loop_bandwidth_rx ( ccrf2_t *ctx, uint8_t fslb_rx )
{
    uint8_t tmp;

    fslb_rx &= 0x03;
    fslb_rx <<= 2;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_FS_DIG0 );

    tmp &= 0xF3;
    tmp |= fslb_rx;

    ccrf2_write_byte_reg( ctx, CCRF2_FS_DIG0, tmp );
}

void ccrf2_set_fs_loop_bandwidth_tx ( ccrf2_t *ctx, uint8_t fslb_tx )
{
    uint8_t tmp;

    fslb_tx &= 0x03;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_FS_DIG0 );

    tmp &= 0xFC;
    tmp |= fslb_tx;

    ccrf2_write_byte_reg( ctx, CCRF2_FS_DIG0, tmp );
}

void ccrf2_set_out_of_lock_avr_time ( ccrf2_t *ctx, uint8_t avr_time )
{
    uint8_t tmp;

    avr_time &= 0x03;
    avr_time <<= 2;

    tmp = ccrf2_read_byte_reg( ctx, CCRF2_FS_CAL0 );

    tmp &= 0xF3;
    tmp |= avr_time;

    ccrf2_write_byte_reg( ctx, CCRF2_FS_CAL0, tmp );
}

void ccrf2_set_dc_comp_real ( ccrf2_t *ctx, uint16_t dc_comp_real )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( dc_comp_real >> 8 );
    tmp_l = ( uint8_t ) ( dc_comp_real & 0x00FF );

    ccrf2_write_byte_reg( ctx, CCRF2_DCFILTOFFSET_I1, tmp_m );
    ccrf2_write_byte_reg( ctx, CCRF2_DCFILTOFFSET_I0, tmp_l );
}

void ccrf2_set_dc_comp_imaginary ( ccrf2_t *ctx, uint16_t dc_comp_im )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( dc_comp_im >> 8 );
    tmp_l = ( uint8_t ) ( dc_comp_im & 0x00FF );

    ccrf2_write_byte_reg( ctx, CCRF2_DCFILTOFFSET_Q1, tmp_m );
    ccrf2_write_byte_reg( ctx, CCRF2_DCFILTOFFSET_Q0, tmp_l );
}

void ccrf2_set_iq_imbalance_real ( ccrf2_t *ctx, uint16_t dc_imb_real )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( dc_imb_real >> 8 );
    tmp_l = ( uint8_t ) ( dc_imb_real & 0x00FF );

    ccrf2_write_byte_reg( ctx, CCRF2_IQIE_I1, tmp_m );
    ccrf2_write_byte_reg( ctx, CCRF2_IQIE_I0, tmp_l );
}

void ccrf2_set_iq_imbalance_imaginary ( ccrf2_t *ctx, uint16_t dc_imb_im )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( dc_imb_im >> 8 );
    tmp_l = ( uint8_t ) ( dc_imb_im & 0x00FF );

    ccrf2_write_byte_reg( ctx, CCRF2_IQIE_Q1, tmp_m );
    ccrf2_write_byte_reg( ctx, CCRF2_IQIE_Q0, tmp_l );
}

uint8_t ccrf2_get_marc_state ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_MARCSTATE );
    result &= 0x1F;

    return result;
}

uint8_t ccrf2_get_chip_id ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_PARTNUMBER );

    return result;
}

uint8_t ccrf2_get_part_vision ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_PARTVERSION );

    return result;
}

uint8_t ccrf2_get_serial_status ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_SERIAL_STATUS );

    return result;
}

uint8_t ccrf2_get_modem_status1 ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_MODEM_STATUS1 );

    return result;
}

uint8_t ccrf2_get_modem_status0 ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_MODEM_STATUS0 );

    return result;
}

uint8_t ccrf2_get_marc_status1 ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_MARC_STATUS1 );

    return result;
}

uint8_t ccrf2_get_marc_status0 ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_MARC_STATUS0 );

    return result;
}

uint8_t ccrf2_get_rx_fifo_pointer_first ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_RXFIRST );

    return result;
}

uint8_t ccrf2_get_tx_fifo_pointer_first ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_TXFIRST );

    return result;
}

uint8_t ccrf2_get_rx_fifo_pointer_last ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_RXLAST );

    return result;
}

uint8_t ccrf2_get_tx__fifo_pointer_last ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_TXLAST );

    return result;
}

uint8_t ccrf2_get_rx_fifo_status ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_NUM_TXBYTES );

    return result;
}

uint8_t ccrf2_get_tx_fifo_status ( ccrf2_t *ctx )
{
    uint8_t result;

    result = ccrf2_read_byte_reg( ctx, CCRF2_NUM_RXBYTES );

    return result;
}

// ------------------------------------------------------------------------- END

