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

#include "ccrf3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define CCRF3_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ccrf3_cfg_setup ( ccrf3_cfg_t *cfg )
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

CCRF3_RETVAL ccrf3_init ( ccrf3_t *ctx, ccrf3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = CCRF3_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return CCRF3_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, CCRF3_DUMMY );
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

    return CCRF3_OK;
}

void ccrf3_default_cfg ( ccrf3_t *ctx )
{
    ccrf3_cmd_strobe( ctx, CCRF3_SRES );

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG3, 0xB0 );
    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG2, 0x00 );
    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG1, 0xB0 );
    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG0, 0xB0 );
    ccrf3_write_byte_reg( ctx, CCRF3_SYNC_CFG1, 0x0B );
    ccrf3_write_byte_reg( ctx, CCRF3_DCFILT_CFG, 0x1C );
    ccrf3_write_byte_reg( ctx, CCRF3_IQIC, 0xC6 );
    ccrf3_write_byte_reg( ctx, CCRF3_CHAN_BW, 0x08 );
    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG0, 0x05 );
    ccrf3_write_byte_reg( ctx, CCRF3_AGC_REF, 0x20 );
    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CS_THR, 0x19 );
    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG1, 0xA9 );
    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG0, 0xCF );
    ccrf3_write_byte_reg( ctx, CCRF3_FIFO_CFG, 0x00 );
    ccrf3_write_byte_reg( ctx, CCRF3_SETTLING_CFG, 0x03 );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_CFG, 0x12 );
    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG1, 0x05 );
    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG0, 0x20 );
    ccrf3_write_byte_reg( ctx, CCRF3_PA_CFG2, 0x4F );
    ccrf3_write_byte_reg( ctx, CCRF3_PA_CFG1, 0x56 );
    ccrf3_write_byte_reg( ctx, CCRF3_PA_CFG0, 0x1C );
    ccrf3_write_byte_reg( ctx, CCRF3_PKT_LEN, 0xFF );
    ccrf3_write_byte_reg( ctx, CCRF3_IF_MIX_CFG, 0x00 );
    ccrf3_write_byte_reg( ctx, CCRF3_FREQOFF_CFG, 0x22 );
    ccrf3_write_byte_reg( ctx, CCRF3_FREQ2, 0x6C );
    ccrf3_write_byte_reg( ctx, CCRF3_FREQ1, 0x80 );
    ccrf3_write_byte_reg( ctx, CCRF3_FREQ0, 0x00 );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_DIG1, 0x00 );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_DIG0, 0x5F );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_CAL0, 0x0E );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_DIVTWO, 0x03 );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_DSM0, 0x33 );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_DVC0, 0x17 );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_PFD, 0x50 );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_PRE, 0x6E );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_REG_DIV_CML, 0x14 );
    ccrf3_write_byte_reg( ctx, CCRF3_FS_SPARE, 0xAC );
    ccrf3_write_byte_reg( ctx, CCRF3_XOSC5, 0x0E );
    ccrf3_write_byte_reg( ctx, CCRF3_XOSC3, 0xC7 );
    ccrf3_write_byte_reg( ctx, CCRF3_XOSC1, 0x07 ); 
}

void ccrf3_generic_transfer ( ccrf3_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
    Delay_1ms( );  
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
    uint8_t w_buffer[ 1 ];
    uint8_t r_buffer[ 1 ];

    w_buffer[ 0 ] = cmd;

    ccrf3_generic_transfer( ctx, w_buffer, 1, r_buffer, 1 );

    return r_buffer[ 0 ];
}

uint8_t ccrf3_get_tx_status ( ccrf3_t *ctx )
{
    return ccrf3_cmd_strobe( ctx, CCRF3_SNOP );
}

uint8_t ccrf3_get_rx_status ( ccrf3_t *ctx )
{
    return ccrf3_cmd_strobe ( ctx, CCRF3_SNOP | CCRF3_RADIO_READ_ACCESS );
}

void ccrf3_read_write_burst_single ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes )
{
    uint16_t cnt;
    uint8_t w_buffer[ 100 ];

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        w_buffer[ cnt ] = rw_data[ cnt ];
    }

    if ( reg_address & CCRF3_RADIO_READ_ACCESS )
    {
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
            spi_master_write( &ctx->spi, w_buffer, n_bytes );
        }
        else
        {
            spi_master_write( &ctx->spi, w_buffer, 1 );
        }
    }
}

CCRF3_STATUS_T ccrf3_byte_reg_access ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint16_t n_bytes )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = ctx->access_type | reg_address;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_write( &ctx->spi, w_buffer, 1 );
    ccrf3_read_write_burst_single( ctx, ctx->access_type | reg_address, rw_data, n_bytes );

    spi_master_deselect_device( ctx->chip_select );  
    Delay_1ms( );

    return CCRF3_STATUS_OK;
}

CCRF3_STATUS_T ccrf3_bytes_reg_access ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *rw_data, uint8_t n_bytes )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = ctx->access_type | ctx->ext_addr;
    w_buffer[ 1 ] = reg_address;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_write( &ctx->spi, w_buffer, 2 );
    ccrf3_read_write_burst_single( ctx, ctx->access_type | ctx->ext_addr, rw_data, n_bytes );

    spi_master_deselect_device( ctx->chip_select );  
    Delay_1ms( );

    return CCRF3_STATUS_OK;
}

CCRF3_STATUS_T ccrf3_read_bytes_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t *read_data, uint8_t n_bytes )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;

    rc = CCRF3_STATUS_ERROR;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( CCRF3_SINGLE_TXFIFO <= reg_address && !temp_ext )
    {
        rc = CCRF3_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        ctx->access_type = CCRF3_RADIO_BURST_ACCESS | CCRF3_RADIO_READ_ACCESS;
        if ( !temp_ext )
        {
            rc = ccrf3_byte_reg_access( ctx, temp_addr, read_data, n_bytes );
        }
        else if ( temp_ext == 0x2F )
        {
            ctx->ext_addr = temp_ext;
            rc = ccrf3_bytes_reg_access( ctx, reg_address, read_data, n_bytes );
        }
    }

    return rc;
}

uint8_t ccrf3_read_byte_reg ( ccrf3_t *ctx, uint16_t reg_address )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;
    uint8_t r_buffer[ 1 ];

    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( CCRF3_SINGLE_TXFIFO <= reg_address && !temp_ext )
    {
        rc = CCRF3_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        ctx->access_type = CCRF3_RADIO_BURST_ACCESS | CCRF3_RADIO_READ_ACCESS;
        if ( !temp_ext )
        {
            ccrf3_byte_reg_access(  ctx, temp_addr, r_buffer, 1 );
        }
        else if ( temp_ext == 0x2F )
        {
            ctx->ext_addr = temp_ext;
            ccrf3_bytes_reg_access( ctx, reg_address, r_buffer, 1 );
        }
    }

    return r_buffer[ 0 ];
}

void ccrf3_write_bytes_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t *write_data, uint8_t n_bytes )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;

    rc = 0;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    if ( CCRF3_SINGLE_TXFIFO <= temp_addr && !temp_ext )
    {
        rc = CCRF3_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        ctx->access_type = CCRF3_RADIO_BURST_ACCESS | CCRF3_RADIO_WRITE_ACCESS;
        if ( !temp_ext)
        {
            ccrf3_byte_reg_access( ctx, temp_addr, write_data, n_bytes );
        }
        else if ( temp_ext == 0x2F )
        {
            ctx->ext_addr = temp_ext;
            ccrf3_bytes_reg_access( ctx, temp_addr, write_data, n_bytes );
        }
    }
}

uint8_t ccrf3_write_byte_reg ( ccrf3_t *ctx, uint16_t reg_address, uint8_t write_data )
{
    uint8_t temp_ext;
    uint8_t temp_addr;
    uint8_t rc;
    uint8_t w_buffer[ 1 ];

    rc = 0;
    temp_ext  = ( uint8_t )( reg_address >> 8 );
    temp_addr = ( uint8_t )( reg_address & 0x00FF );

    w_buffer[ 0 ] = write_data;

    if ( CCRF3_SINGLE_TXFIFO <= temp_addr && !temp_ext )
    {
        rc = CCRF3_STATUS_CHIP_RDYn_BM;
    }
    else
    {
        ctx->access_type = CCRF3_RADIO_BURST_ACCESS | CCRF3_RADIO_WRITE_ACCESS;
        if ( !temp_ext )
        {
            rc = ccrf3_byte_reg_access( ctx, temp_addr, w_buffer, 1 );
        }
        else if ( temp_ext == 0x2F )
        {
            ctx->ext_addr = temp_ext;
            rc = ccrf3_bytes_reg_access( ctx, temp_addr, w_buffer, 1 );
        }
    }

    return rc;
}

void ccrf3_read_write_burst_single1 ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *read_data, uint8_t n_bytes )
{
    uint16_t cnt;

    if ( reg_address & CCRF3_RADIO_READ_ACCESS )
    {
        if ( reg_address & CCRF3_RADIO_BURST_ACCESS )
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
        if ( reg_address & CCRF3_RADIO_BURST_ACCESS )
        {
            spi_master_write( &ctx->spi, read_data, n_bytes );
        }
        else
        {
            spi_master_write( &ctx->spi, read_data, 1 );
        }
    }
}

uint8_t ccrf3_access_byte_register ( ccrf3_t *ctx, uint8_t reg_address, uint8_t *read_data, uint8_t n_bytes )
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

    spi_master_write_then_read( &ctx->spi, w_buffer, 1, r_buffer, 1 );

    ccrf3_read_write_burst_single( ctx, w_buffer[ 0 ], w_buffer, n_bytes );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select );  

    return r_buffer[ 0 ];
}

uint8_t ccrf3_write_tx_fifo ( ccrf3_t *ctx, uint8_t *write_data, uint8_t n_bytes )
{
    ctx->access_type = 0;
    return ccrf3_byte_reg_access( ctx, CCRF3_BURST_TXFIFO, write_data, n_bytes );
}

uint8_t ccrf3_read_rx_fifo ( ccrf3_t *ctx, uint8_t *read_data, uint8_t n_bytes )
{
    ctx->access_type = 0;
    return ccrf3_byte_reg_access( ctx, CCRF3_BURST_RXFIFO, read_data, n_bytes );
}

void ccrf3_manual_calibration ( ccrf3_t *ctx )
{
    uint8_t original_fs_cal2;
    uint8_t cal_results_vcdac_start_high[ 3 ];
    uint8_t cal_results_vcdac_start_mid[ 3 ];
    uint8_t marc_state;
    uint8_t write_byte;

    // 1) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    write_byte = 0x00;
    ccrf3_write_bytes_reg( ctx, CCRF3_FS_VCO2, &write_byte, 1 );

    // 2) Start with high VCDAC (original VCDAC_START + 2):
    ccrf3_read_bytes_reg( ctx, CCRF3_FS_CAL2, &original_fs_cal2, 1 );
    write_byte = original_fs_cal2 + 2;
    ccrf3_write_bytes_reg( ctx, CCRF3_FS_CAL2, &write_byte, 1 );

    // 3) Calibrate and wait for calibration to be done
    //   (radio back in IDLE state)
    ccrf3_cmd_strobe( ctx, CCRF3_SCAL );

    do
    {
        ccrf3_read_bytes_reg( ctx, CCRF3_MARCSTATE, &marc_state, 1 );
    }
    while ( marc_state != 0x41 );

    // 4) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with
    //    high VCDAC_START value
    ccrf3_read_bytes_reg( ctx, CCRF3_FS_VCO2, &cal_results_vcdac_start_high[ 0 ], 1 );
    ccrf3_read_bytes_reg( ctx, CCRF3_FS_VCO4, &cal_results_vcdac_start_high[ 1 ], 1 );
    ccrf3_read_bytes_reg( ctx, CCRF3_FS_CHP, &cal_results_vcdac_start_high[ 2 ], 1 );

    // 5) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    write_byte = 0x00;
    ccrf3_write_bytes_reg( ctx, CCRF3_FS_VCO2, &write_byte, 1 );

    // 6) Continue with mid VCDAC (original VCDAC_START):
    write_byte = original_fs_cal2;
    ccrf3_write_bytes_reg( ctx, CCRF3_FS_CAL2, &write_byte, 1 );

    // 7) Calibrate and wait for calibration to be done
    //   (radio back in IDLE state)
    ccrf3_cmd_strobe( ctx, CCRF3_SCAL );

    do
    {
        ccrf3_read_bytes_reg( ctx, CCRF3_MARCSTATE, &marc_state, 1 );
    }
    while ( marc_state != 0x41 );

    // 8) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained
    //    with mid VCDAC_START value
    ccrf3_read_bytes_reg( ctx, CCRF3_FS_VCO2, &cal_results_vcdac_start_mid[ 0 ], 1 );
    ccrf3_read_bytes_reg( ctx, CCRF3_FS_VCO4, &cal_results_vcdac_start_mid[ 1 ], 1 );
    ccrf3_read_bytes_reg( ctx, CCRF3_FS_CHP, &cal_results_vcdac_start_mid[ 2 ], 1 );

    // 9) Write back highest FS_VCO2 and corresponding FS_VCO
    //    and FS_CHP result
    if ( cal_results_vcdac_start_high[ 0 ] > cal_results_vcdac_start_mid[ 0 ] )
    {
        write_byte = cal_results_vcdac_start_high[ 0 ];
        ccrf3_write_bytes_reg( ctx, CCRF3_FS_VCO2, &write_byte, 1 );
        write_byte = cal_results_vcdac_start_high[ 1 ];
        ccrf3_write_bytes_reg( ctx, CCRF3_FS_VCO4, &write_byte, 1 );
        write_byte = cal_results_vcdac_start_high[ 2 ];
        ccrf3_write_bytes_reg( ctx, CCRF3_FS_CHP, &write_byte, 1 );
    }
    else
    {
        write_byte = cal_results_vcdac_start_mid[ 0 ];
        ccrf3_write_bytes_reg( ctx, CCRF3_FS_VCO2, &write_byte, 1 );
        write_byte = cal_results_vcdac_start_mid[ 1 ];
        ccrf3_write_bytes_reg( ctx, CCRF3_FS_VCO4, &write_byte, 1 );
        write_byte = cal_results_vcdac_start_mid[ 2 ];
        ccrf3_write_bytes_reg( ctx, CCRF3_FS_CHP, &write_byte, 1 );
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

uint8_t ccrf3_get_interrupt ( ccrf3_t *ctx )
{
    return !digital_in_read( &ctx->gp3 );
}

void ccrf3_send_tx_data ( ccrf3_t *ctx, uint8_t *tx_data, uint8_t n_bytes )
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

    ccrf3_write_tx_fifo( ctx, tx_buffer, n_bytes + 3 );

    ccrf3_cmd_strobe( ctx, CCRF3_STX );

    while ( ccrf3_get_interrupt( ctx ) );
}

void ccrf3_receive_rx_data ( ccrf3_t *ctx, uint8_t *rx_data )
{
    uint8_t n_bytes;
    uint8_t marc_state;

    n_bytes = 0;

    if ( ccrf3_get_interrupt( ctx ) )
    {
        while ( ccrf3_get_interrupt( ctx ) );

        n_bytes = ccrf3_read_byte_reg( ctx, CCRF3_NUM_RXBYTES );

        if ( n_bytes != 0 )
        {
            marc_state = ccrf3_read_byte_reg( ctx, CCRF3_MARCSTATE );

            if ( ( marc_state & 0x1F ) == 0x11 )
            {
                ccrf3_cmd_strobe( ctx, CCRF3_SFRX );
            }
            else
            {
                ccrf3_read_rx_fifo ( ctx, &rx_data[ 0 ], n_bytes );

                if ( rx_data[ n_bytes - 1 ] & 0x80 )
                {
                    ccrf3_set_rx_mode( ctx );
                }
            }
        }
    }
}

void ccrf3_enable_analog_transfer_gpio3 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG3 );

    tmp |= 0x80;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG3, tmp );
}

void ccrf3_disable_analog_transfer_gpio3 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG3 );

    tmp &= 0x7F;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG3, tmp );
}

void ccrf3_enable_invert_output_gpio3 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG3 );

    tmp |= 0x40;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG3, tmp );
}

void ccrf3_disable_invert_output_gpio3 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG3 );

    tmp &= 0x3F;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG3, tmp );
}

void ccrf3_enable_analog_transfer_gpio2 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG2 );

    tmp |= 0x80;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG2, tmp );
}

void ccrf3_disable_analog_transfer_gpio2 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG2 );

    tmp &= 0x7F;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG2, tmp );
}

void ccrf3_enable_invert_output_gpio2 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG2 );

    tmp |= 0x40;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG2, tmp );
}

void ccrf3_disable_invert_output_gpio2( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG2 );

    tmp &= 0x3F;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG2, tmp );
}

void ccrf3_enable_analog_transfer_gpio0 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG0 );

    tmp |= 0x80;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG0, tmp );
}

void ccrf3_disable_analog_transfer_gpio0 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG0 );

    tmp &= 0x7F;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG0, tmp );
}

void ccrf3_enable_invert_output_gpio0 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG0 );

    tmp |= 0x40;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG0, tmp );
}

void ccrf3_disable_invert_output_gpio0 ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IOCFG0 );

    tmp &= 0x3F;

    ccrf3_write_byte_reg( ctx, CCRF3_IOCFG0, tmp );
}

void ccrf3_set_sync_mode( ccrf3_t *ctx, uint8_t s_mode )
{
    uint8_t tmp;

    s_mode &= 0x07;
    s_mode <<= 2;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_SYNC_CFG0 );
    tmp &= 0xE3;
    tmp |= s_mode;

    ccrf3_write_byte_reg( ctx, CCRF3_SYNC_CFG0, tmp );
}

void ccrf3_set_sync_num_error ( ccrf3_t *ctx, uint8_t num_err )
{
    uint8_t tmp;

    num_err &= 0x03;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_SYNC_CFG0 );
    tmp &= 0xFC;
    tmp |= num_err;

    ccrf3_write_byte_reg( ctx, CCRF3_SYNC_CFG0, tmp );
}

void ccrf3_config_modem_mode ( ccrf3_t *ctx, uint8_t m_mode )
{
    uint8_t tmp;

    m_mode &= 0x03;
    m_mode <<= 6;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MODCFG_DEV_E );
    tmp &= 0x3F;
    tmp |= m_mode;

    ccrf3_write_byte_reg( ctx, CCRF3_MODCFG_DEV_E, tmp );
}

void ccrf3_set_modulation_format ( ccrf3_t *ctx, uint8_t m_format )
{
    uint8_t tmp;

    m_format &= 0x07;
    m_format <<= 3;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MODCFG_DEV_E );
    tmp &= 0xC7;
    tmp |= m_format;

    ccrf3_write_byte_reg( ctx, CCRF3_MODCFG_DEV_E, tmp );
}

void ccrf3_set_dc_period_filter ( ccrf3_t *ctx, uint16_t n_samples )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_DCFILT_CFG );
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

    ccrf3_write_byte_reg( ctx, CCRF3_DCFILT_CFG, tmp );
}

void ccrf3_set_min_num_transmitted ( ccrf3_t *ctx, uint8_t mNumber )
{
    uint8_t tmp;

    mNumber &= 0x0F;
    mNumber <<= 2;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PREAMBLE_CFG1 );
    tmp &= 0x87;
    tmp |= mNumber;

    ccrf3_write_byte_reg( ctx, CCRF3_PREAMBLE_CFG1, tmp );
}

void ccrf3_config_preamble ( ccrf3_t *ctx, uint8_t p_value )
{
    uint8_t tmp;

    p_value &= 0x03;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PREAMBLE_CFG1 );
    tmp &= 0xFC;
    tmp |= p_value;

    ccrf3_write_byte_reg( ctx, CCRF3_PREAMBLE_CFG1, tmp );
}

void ccrf3_disable_preamble_detection ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PREAMBLE_CFG0 );
    tmp &= 0xDF;

    ccrf3_write_byte_reg( ctx, CCRF3_PREAMBLE_CFG0, tmp );
}

void ccrf3_enable_preamble_detection ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PREAMBLE_CFG0 );
    tmp |= 0x20;

    ccrf3_write_byte_reg( ctx, CCRF3_PREAMBLE_CFG0, tmp );
}

void ccrf3_start_up_timer_pqt ( ccrf3_t *ctx, uint8_t v_timer )
{
    uint8_t tmp;

    v_timer &= 0x01;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PREAMBLE_CFG0 );

    if ( v_timer )
    {
        tmp |= 0x10;
    }
    else
    {
        tmp &= 0xEF;
    }

    ccrf3_write_byte_reg( ctx, CCRF3_PREAMBLE_CFG0, tmp );
}

void ccrf3_disable_iq_comp ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IQIC );
    tmp &= 0x7F;

    ccrf3_write_byte_reg( ctx, CCRF3_IQIC, tmp );
}

void ccrf3_enable_iq_comp ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IQIC );
    tmp |= 0x80;

    ccrf3_write_byte_reg( ctx, CCRF3_IQIC, tmp );
}

void ccrf3_disable_iqic_coef ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IQIC );
    tmp &= 0xBF;

    ccrf3_write_byte_reg( ctx, CCRF3_IQIC, tmp );
}

void ccrf3_enable_iqic_coef ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IQIC );
    tmp |= 0x40;

    ccrf3_write_byte_reg( ctx, CCRF3_IQIC, tmp );
}

void ccrf3_set_iqic_block_length_settling ( ccrf3_t *ctx, uint8_t iqicLen )
{
    uint8_t tmp;

    iqicLen &= 0x03;
    iqicLen <<= 4;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IQIC );
    tmp &= 0xCF;
    tmp |= iqicLen;

    ccrf3_write_byte_reg( ctx, CCRF3_IQIC, tmp );
}

void ccrf3_set_iqic_block_length( ccrf3_t *ctx, uint8_t iqicLen )
{
    uint8_t tmp;

    iqicLen &= 0x03;
    iqicLen <<= 2;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IQIC );
    tmp &= 0x3F;
    tmp |= iqicLen;

    ccrf3_write_byte_reg( ctx, CCRF3_IQIC, tmp );
}

void ccrf3_set_iqic_ch_lvl_threshold ( ccrf3_t *ctx, uint8_t iqic_thr )
{
    uint8_t tmp;

    iqic_thr &= 0x03;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_IQIC );
    tmp &= 0xFC;
    tmp |= iqic_thr;

    ccrf3_write_byte_reg( ctx, CCRF3_IQIC, tmp );
}

void ccrf3_disable_ch_filter ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_CHAN_BW  );
    tmp &= 0x7F;

    ccrf3_write_byte_reg( ctx, CCRF3_CHAN_BW, tmp );
}

void ccrf3_enable_ch_filter ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_CHAN_BW );
    tmp |= 0x80;

    ccrf3_write_byte_reg( ctx, CCRF3_CHAN_BW, tmp );
}

void ccrf3_disable_fifo ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG1 );
    tmp &= 0xBF;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_enable_fifo ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG1 );
    tmp |= 0x40;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_disable_manchester_mode ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG1 );
    tmp &= 0xDF;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_enable_manchester_mode ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG1 );
    tmp |= 0x20;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_disable_invert_data ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG1 );
    tmp &= 0xEF;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_enable_invert_data ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG1 );
    tmp |= 0x10;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_disable_collision_detect ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG1 );
    tmp &= 0xF7;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_enable_collision_detect ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG1 );
    tmp |= 0x08;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_set_dvga_gain( ccrf3_t *ctx, uint8_t dvga_gain )
{
    uint8_t tmp;

    dvga_gain &= 0x03;
    dvga_gain <<= 1;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG1 );
    tmp &= 0xF9;
    tmp |= dvga_gain;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_disable_transparent_mode ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG0 );
    tmp &= 0xBF;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG1, tmp );
}

void ccrf3_enable_transparent_mode ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG0 );
    tmp |= 0x40;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG0, tmp );
}

void ccrf3_set_transparent_data_filter ( ccrf3_t *ctx, uint8_t t_data )
{
    uint8_t tmp;

    t_data &= 0x01;
    t_data <<= 3;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG0 );
    tmp &= 0xF7;
    tmp |= t_data;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG0, tmp );
}

void ccrf3_disable_viterbi_detection ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG0 );
    tmp &= 0xFB;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG0, tmp );
}

void ccrf3_enable_viterbi_detection ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_MDMCFG0 );
    tmp |= 0x04;

    ccrf3_write_byte_reg( ctx, CCRF3_MDMCFG0, tmp );
}

void ccrf3_set_rssi_threshold ( ccrf3_t *ctx, uint8_t rssi_thr )
{
    uint8_t tmp;

    rssi_thr &= 0x01;
    rssi_thr <<= 7;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG3 );
    tmp &= 0x7F;
    tmp |= rssi_thr;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG3, tmp );
}

void ccrf3_set_receiver_max_gain ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG2 );
    tmp &= 0x7F;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG2, tmp );
}

void ccrf3_set_receiver_previous_gain ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG2 );
    tmp |= 0x80;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG2, tmp );
}

void ccrf3_set_performance_mode ( ccrf3_t *ctx, uint8_t p_mode )
{
    uint8_t tmp;

    p_mode &= 0x03;
    p_mode <<= 5;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG2 );
    tmp &= 0x9F;
    tmp |= p_mode;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG2, tmp );
}

void ccrf3_set_agc_behavior ( ccrf3_t *ctx, uint8_t agc_value )
{
    uint8_t tmp;

    agc_value &= 0x07;
    agc_value <<= 5;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG1 );
    tmp &= 0x1F;
    tmp |= agc_value;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG1, tmp );
}

void ccrf3_set_agc_integration ( ccrf3_t *ctx, uint8_t agc_value )
{
    uint8_t tmp;

    agc_value &= 0x07;
    agc_value <<= 2;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG1 );
    tmp &= 0xE3;
    tmp |= agc_value;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG1, tmp );
}

void ccrf3_set_wait_time_agc_gain ( ccrf3_t *ctx, uint8_t w_time )
{
    uint8_t tmp;

    w_time &= 0x03;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG1 );
    tmp &= 0xFC;
    tmp |= w_time;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG1, tmp );
}

void ccrf3_set_agc_hysteresis_lvl ( ccrf3_t *ctx, uint8_t agc_value )
{
    uint8_t tmp;

    agc_value &= 0x03;
    agc_value <<= 6;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG0 );
    tmp &= 0x3F;
    tmp |= agc_value;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG0, tmp );
}

void ccrf3_set_agc_slew_rate_limit ( ccrf3_t *ctx, uint8_t agc_value )
{
    uint8_t tmp;

    agc_value &= 0x03;
    agc_value <<= 4;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG0 );
    tmp &= 0xCF;
    tmp |= agc_value;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG0, tmp );
}

void ccrf3_set_rssi_valid_cnt ( ccrf3_t *ctx, uint8_t rssi_cnt )
{
    uint8_t tmp;

    rssi_cnt &= 0x03;
    rssi_cnt <<= 2;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG0 );
    tmp &= 0xF3;
    tmp |= rssi_cnt;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG0, tmp );
}

void ccrf3_set_decimation_factor ( ccrf3_t *ctx, uint8_t dec_factor )
{
    uint8_t tmp;

    dec_factor &= 0x03;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_AGC_CFG0 );
    tmp &= 0xFC;
    tmp |= dec_factor;

    ccrf3_write_byte_reg( ctx, CCRF3_AGC_CFG0, tmp );
}

void ccrf3_set_address_packet_rx ( ccrf3_t *ctx, uint8_t dev_addr )
{
    ccrf3_write_byte_reg( ctx, CCRF3_DEV_ADDR, dev_addr );
}

void ccrf3_disable_out_of_lock_detector ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_FS_CFG );
    tmp &= 0xF0;

    ccrf3_write_byte_reg( ctx, CCRF3_FS_CFG, tmp );
}

void ccrf3_enable_out_of_lock_detector ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_FS_CFG );
    tmp |= 0x10;

    ccrf3_write_byte_reg( ctx, CCRF3_FS_CFG, tmp );
}

void ccrf3_select_band_settings ( ccrf3_t *ctx, uint8_t band_settings )
{
    uint8_t tmp;

    band_settings &= 0x0F;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_FS_CFG );
    tmp &= 0xF0;
    tmp |= band_settings;

    ccrf3_write_byte_reg( ctx, CCRF3_FS_CFG, tmp );
}

void ccrf3_set_wor_resolution ( ccrf3_t *ctx, uint8_t wor_res )
{
    uint8_t tmp;

    wor_res &= 0x03;
    wor_res <<= 6;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_WOR_CFG1 );
    tmp &= 0x3F;
    tmp |= wor_res;

    ccrf3_write_byte_reg( ctx, CCRF3_WOR_CFG1, tmp );
}

void ccrf3_set_wor_mode ( ccrf3_t *ctx, uint8_t w_mode )
{
    uint8_t tmp;

    w_mode &= 0x07;

    if ( w_mode > 4 )
    {
        w_mode = 0x01;
    }

    w_mode <<= 3;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_WOR_CFG1 );
    tmp &= 0xC7;
    tmp |= w_mode;

    ccrf3_write_byte_reg( ctx, CCRF3_WOR_CFG1, tmp );
}

void ccrf3_set_event_timeout ( ccrf3_t *ctx, uint8_t e_timeout )
{
    uint8_t tmp;

    e_timeout &= 0x07;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_WOR_CFG1 );
    tmp &= 0xF8;
    tmp |= e_timeout;

    ccrf3_write_byte_reg( ctx, CCRF3_WOR_CFG1, tmp );
}

void ccrf3_disable_clock_division ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_WOR_CFG0 );
    tmp &= 0xDF;

    ccrf3_write_byte_reg( ctx, CCRF3_WOR_CFG0, tmp );
}

void ccrf3_enable_clock_division ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_WOR_CFG0 );
    tmp |= 0x20;

    ccrf3_write_byte_reg( ctx, CCRF3_WOR_CFG0, tmp );
}

void ccrf3_set_cca_mode ( ccrf3_t *ctx, uint8_t cca_mode )
{
    uint8_t tmp;

    cca_mode &= 0x07;
    cca_mode <<= 2;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG2 );
    tmp &= 0xE3;
    tmp |= cca_mode;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG2, tmp );
}

void ccrf3_set_packet_format ( ccrf3_t *ctx, uint8_t p_format )
{
    uint8_t tmp;

    p_format &= 0x03;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG2 );
    tmp &= 0xFC;
    tmp |= p_format;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG2, tmp );
}

void ccrf3_disable_data_whitening ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG1 );
    tmp &= 0xBF;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG1, tmp );
}

void ccrf3_enable_data_whitening ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG1 );
    tmp |= 0x40;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG1, tmp );
}

void ccrf3_set_crc_config ( ccrf3_t *ctx, uint8_t crc_config )
{
    uint8_t tmp;

    crc_config &= 0x03;
    crc_config <<= 2;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG1 );
    tmp &= 0xF3;
    tmp |= crc_config;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG2, tmp );
}

void ccrf3_disable_data_swap ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG1 );
    tmp &= 0xFD;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG1, tmp );
}

void ccrf3_enable_data_swap ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG1 );
    tmp |= 0x02;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG1, tmp );
}

void ccrf3_append_status ( ccrf3_t *ctx, uint8_t app_status )
{
    uint8_t tmp;

    app_status &= 0x01;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG1 );

    if ( app_status )
    {
        tmp |= 0x01;
    }
    else
    {
        tmp &= 0xFE;
    }

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG1, tmp );
}

void ccrf3_disable_uart_mode ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG0 );
    tmp &= 0xFD;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG0, tmp );
}

void ccrf3_enable_uart_mode ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG0 );
    tmp |= 0x02;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG0, tmp );
}

void ccrf3_disable_uart_swap ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG0 );
    tmp &= 0xFE;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG0, tmp );
}

void ccrf3_enable_uart_swap ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PKT_CFG0 );
    tmp |= 0x01;

    ccrf3_write_byte_reg( ctx, CCRF3_PKT_CFG0, tmp );
}

void ccrf3_set_rx_off_mode ( ccrf3_t *ctx, uint8_t rx_off_mode )
{
    uint8_t tmp;

    rx_off_mode &= 0x03;
    rx_off_mode <<= 4;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_RFEND_CFG1 );

    tmp &= 0xCF;
    tmp |= rx_off_mode;

    ccrf3_write_byte_reg( ctx, CCRF3_RFEND_CFG1, tmp );
}

void ccrf3_set_tx_off_mode ( ccrf3_t *ctx, uint8_t tx_off_mode )
{
    uint8_t tmp;

    tx_off_mode &= 0x03;
    tx_off_mode <<= 4;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_RFEND_CFG0 );

    tmp &= 0xCF;
    tmp |= tx_off_mode;

    ccrf3_write_byte_reg( ctx, CCRF3_RFEND_CFG0, tmp );
}

void ccrf3_set_tx_upsampler ( ccrf3_t *ctx, uint8_t tx_upsampler )
{
    uint8_t tmp;

    tx_upsampler &= 0x07;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_PA_CFG0 );

    tmp &= 0xF8;
    tmp |= tx_upsampler;

    ccrf3_write_byte_reg( ctx, CCRF3_PA_CFG0, tmp );
}

void ccrf3_set_packet_length ( ccrf3_t *ctx, uint8_t pack_len )
{
    ccrf3_write_byte_reg( ctx, CCRF3_PKT_LEN, pack_len );
}

void ccrf3_disable_freq_offset_correction ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_FREQOFF_CFG );
    tmp &= 0xDF;

    ccrf3_write_byte_reg( ctx, CCRF3_FREQOFF_CFG, tmp );
}

void ccrf3_enable_freq_offset_correction ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_FREQOFF_CFG );
    tmp |= 0x20;

    ccrf3_write_byte_reg( ctx, CCRF3_FREQOFF_CFG, tmp );
}

void ccrf3_set_ext_clock_freq ( ccrf3_t *ctx, uint8_t ec_freq )
{
    uint8_t tmp;

    ec_freq &= 0x1F;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_ECG_CFG );

    tmp &= 0xE0;
    tmp |= ec_freq;

    ccrf3_write_byte_reg( ctx, CCRF3_ECG_CFG, tmp );
}

void ccrf3_disable_cfm_mode ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_CFM_DATA_CFG );
    tmp &= 0xFE;

    ccrf3_write_byte_reg( ctx, CCRF3_CFM_DATA_CFG, tmp );
}

void ccrf3_enable_cfm_mode ( ccrf3_t *ctx )
{
    uint8_t tmp;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_CFM_DATA_CFG );
    tmp |= 0x01;

    ccrf3_write_byte_reg( ctx, CCRF3_CFM_DATA_CFG, tmp );
}

void ccrf3_set_freq_offset ( ccrf3_t *ctx, uint16_t freq_offset )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( freq_offset >> 8 );
    tmp_l = ( uint8_t ) ( freq_offset & 0x00FF );

    ccrf3_cmd_strobe( ctx, CCRF3_AFC );

    ccrf3_write_byte_reg( ctx, CCRF3_FREQOFF1, tmp_m );
    ccrf3_write_byte_reg( ctx, CCRF3_FREQOFF0, tmp_l );
}

void ccrf3_set_fs_loop_bandwidth_rx ( ccrf3_t *ctx, uint8_t fslb_rx )
{
    uint8_t tmp;

    fslb_rx &= 0x03;
    fslb_rx <<= 2;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_FS_DIG0 );

    tmp &= 0xF3;
    tmp |= fslb_rx;

    ccrf3_write_byte_reg( ctx, CCRF3_FS_DIG0, tmp );
}

void ccrf3_set_fs_loop_bandwidth_tx ( ccrf3_t *ctx, uint8_t fslb_tx )
{
    uint8_t tmp;

    fslb_tx &= 0x03;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_FS_DIG0 );

    tmp &= 0xFC;
    tmp |= fslb_tx;

    ccrf3_write_byte_reg( ctx, CCRF3_FS_DIG0, tmp );
}

void ccrf3_set_out_of_lock_avr_time ( ccrf3_t *ctx, uint8_t avr_time )
{
    uint8_t tmp;

    avr_time &= 0x03;
    avr_time <<= 2;

    tmp = ccrf3_read_byte_reg( ctx, CCRF3_FS_CAL0 );

    tmp &= 0xF3;
    tmp |= avr_time;

    ccrf3_write_byte_reg( ctx, CCRF3_FS_CAL0, tmp );
}

void ccrf3_set_dc_comp_real ( ccrf3_t *ctx, uint16_t dc_comp_real )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( dc_comp_real >> 8 );
    tmp_l = ( uint8_t ) ( dc_comp_real & 0x00FF );

    ccrf3_write_byte_reg( ctx, CCRF3_DCFILTOFFSET_I1, tmp_m );
    ccrf3_write_byte_reg( ctx, CCRF3_DCFILTOFFSET_I0, tmp_l );
}

void ccrf3_set_dc_comp_imaginary ( ccrf3_t *ctx, uint16_t dc_comp_im )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( dc_comp_im >> 8 );
    tmp_l = ( uint8_t ) ( dc_comp_im & 0x00FF );

    ccrf3_write_byte_reg( ctx, CCRF3_DCFILTOFFSET_Q1, tmp_m );
    ccrf3_write_byte_reg( ctx, CCRF3_DCFILTOFFSET_Q0, tmp_l );
}

void ccrf3_set_iq_imbalance_real ( ccrf3_t *ctx, uint16_t dc_imb_real )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( dc_imb_real >> 8 );
    tmp_l = ( uint8_t ) ( dc_imb_real & 0x00FF );

    ccrf3_write_byte_reg( ctx, CCRF3_IQIE_I1, tmp_m );
    ccrf3_write_byte_reg( ctx, CCRF3_IQIE_I0, tmp_l );
}

void ccrf3_set_iq_imbalance_imaginary ( ccrf3_t *ctx, uint16_t dc_imb_im )
{
    uint8_t tmp_m;
    uint8_t tmp_l;

    tmp_m = ( uint8_t ) ( dc_imb_im >> 8 );
    tmp_l = ( uint8_t ) ( dc_imb_im & 0x00FF );

    ccrf3_write_byte_reg( ctx, CCRF3_IQIE_Q1, tmp_m );
    ccrf3_write_byte_reg( ctx, CCRF3_IQIE_Q0, tmp_l );
}

uint8_t ccrf3_get_marc_state ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_MARCSTATE );
    result &= 0x1F;

    return result;
}

uint8_t ccrf3_get_chip_id ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_PARTNUMBER );

    return result;
}

uint8_t ccrf3_get_part_vision ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_PARTVERSION );

    return result;
}

uint8_t ccrf3_get_serial_status ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_SERIAL_STATUS );

    return result;
}

uint8_t ccrf3_get_modem_status1 ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_MODEM_STATUS1 );

    return result;
}

uint8_t ccrf3_get_modem_status0 ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_MODEM_STATUS0 );

    return result;
}

uint8_t ccrf3_get_marc_status1 ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_MARC_STATUS1 );

    return result;
}

uint8_t ccrf3_get_marc_status0 ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_MARC_STATUS0 );

    return result;
}

uint8_t ccrf3_get_rx_fifo_pointer_first ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_RXFIRST );

    return result;
}

uint8_t ccrf3_get_tx_fifo_pointer_first ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_TXFIRST );

    return result;
}

uint8_t ccrf3_get_rx_fifo_pointer_last ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_RXLAST );

    return result;
}

uint8_t ccrf3_get_tx__fifo_pointer_last ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_TXLAST );

    return result;
}

uint8_t ccrf3_get_rx_fifo_status ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_NUM_TXBYTES );

    return result;
}

uint8_t ccrf3_get_tx_fifo_status ( ccrf3_t *ctx )
{
    uint8_t result;

    result = ccrf3_read_byte_reg( ctx, CCRF3_NUM_RXBYTES );

    return result;
}

// ------------------------------------------------------------------------- END

