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

#include "ccrf.h"
#include "string.h" 

// ------------------------------------------------------------- PRIVATE MACROS 

#define CCRF_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ccrf_cfg_setup ( ccrf_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->gd0 = HAL_PIN_NC;
    cfg->gd2 = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

err_t ccrf_init ( ccrf_t *ctx, ccrf_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, CCRF_DUMMY ) ) 
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

    // Output pins 
    digital_out_init( &ctx->gd2, cfg->gd2 );

    // Input pins
    digital_in_init( &ctx->gd0, cfg->gd0 );

    return CCRF_OK;
}

void ccrf_default_cfg ( ccrf_t *ctx )
{
    ccrf_hw_reset( ctx );
    Delay_100ms ( );
    
    ccrf_sw_reset( ctx );
    Delay_100ms ( );
    
    ccrf_write_byte( ctx, CCRF_FSCTRL1, 0x0A );
    ccrf_write_byte( ctx, CCRF_FSCTRL0, 0x00 );
    ccrf_write_byte( ctx, CCRF_FREQ2, 0x5D );
    ccrf_write_byte( ctx, CCRF_FREQ1, 0x93 );
    ccrf_write_byte( ctx, CCRF_FREQ0, 0xB1 );
    ccrf_write_byte( ctx, CCRF_MDMCFG4, 0x2D );
    ccrf_write_byte( ctx, CCRF_MDMCFG3, 0x3B );
    ccrf_write_byte( ctx, CCRF_MDMCFG2, 0x73 );
    ccrf_write_byte( ctx, CCRF_MDMCFG1, 0x22 );
    ccrf_write_byte( ctx, CCRF_MDMCFG0, 0xF8 );
    ccrf_write_byte( ctx, CCRF_CHANNR, 0x00 );
    ccrf_write_byte( ctx, CCRF_DEVIATN, 0x01 );
    ccrf_write_byte( ctx, CCRF_FREND1, 0xB6 );
    ccrf_write_byte( ctx, CCRF_FREND0, 0x10 );
    ccrf_write_byte( ctx, CCRF_MCSM0, 0x18 );
    ccrf_write_byte( ctx, CCRF_FOCCFG, 0x1D );
    ccrf_write_byte( ctx, CCRF_BSCFG, 0x1C );
    ccrf_write_byte( ctx, CCRF_AGCCTRL2, 0xC7 );
    ccrf_write_byte( ctx, CCRF_AGCCTRL1, 0x00 );
    ccrf_write_byte( ctx, CCRF_AGCCTRL0, 0xB0 );
    ccrf_write_byte( ctx, CCRF_FSCAL3, 0xEA );
    ccrf_write_byte( ctx, CCRF_FSCAL2, 0x0A );
    ccrf_write_byte( ctx, CCRF_FSCAL1, 0x00 );
    ccrf_write_byte( ctx, CCRF_FSCAL0, 0x11 );
    ccrf_write_byte( ctx, CCRF_FSTEST, 0x59 );
    ccrf_write_byte( ctx, CCRF_TEST2, 0x88 );
    ccrf_write_byte( ctx, CCRF_TEST1, 0x31 );
    ccrf_write_byte( ctx, CCRF_TEST0, 0x0B );
    ccrf_write_byte( ctx, CCRF_FIFOTHR, 0x07 );
    ccrf_write_byte( ctx, CCRF_IOCFG2, 0x29 );
    ccrf_write_byte( ctx, CCRF_IOCFG0, 0x06 );
    ccrf_write_byte( ctx, CCRF_PKTCTRL1, 0x04 );
    ccrf_write_byte( ctx, CCRF_PKTCTRL0, 0x05 );
    ccrf_write_byte( ctx, CCRF_ADDR, 0x30 );
    ccrf_write_byte( ctx, CCRF_PKTLEN, 0xFF );
    Delay_100ms ( );
    
    ccrf_write_byte( ctx, CCRF_PATABLE, 0xFE );;
    Delay_100ms ( );
}

uint8_t ccrf_get_start( ccrf_t *ctx )
{
    return digital_in_read( &ctx->gd0 );
}

void ccrf_write_byte ( ccrf_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ] = { 0 };

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 1 ] = write_data;

    spi_master_select_device( ctx->chip_select );
    
    while ( ccrf_get_start( ctx ) );
    
    spi_master_write( &ctx->spi, w_buffer, 2 );
    
    spi_master_deselect_device( ctx->chip_select );  
}

void ccrf_write_bytes ( ccrf_t *ctx, uint8_t reg_address, uint8_t *write_data, uint8_t n_bytes )
{
    uint8_t w_buffer[ 2 ] = { 0 };

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 0 ] |= CCRF_WRITE_BURST;
    w_buffer[ 1 ] = n_bytes;

    spi_master_select_device( ctx->chip_select );
    
    while ( ccrf_get_start( ctx ) );

    spi_master_write( &ctx->spi, w_buffer, 2 );

    spi_master_write( &ctx->spi, write_data, n_bytes );

    spi_master_deselect_device( ctx->chip_select );  
}

void ccrf_write_strobe ( ccrf_t *ctx, uint8_t strobe ) 
{
    uint8_t w_buffer[ 1 ] = { 0 };
    
    w_buffer[ 0 ] = strobe;
    
    spi_master_select_device( ctx->chip_select );

    while ( ccrf_get_start( ctx ) );
    
    spi_master_write( &ctx->spi, w_buffer, 1 );

    spi_master_deselect_device( ctx->chip_select );  
}

uint8_t ccrf_read_byte ( ccrf_t *ctx, uint8_t reg_address )
{
    uint8_t w_buffer[ 1 ] = { 0 };
    uint8_t r_buffer[ 1 ] = { 0 };

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 0 ] |= CCRF_READ_SINGLE;

    spi_master_select_device( ctx->chip_select );

    while ( ccrf_get_start( ctx ) );

    spi_master_write( &ctx->spi, w_buffer, 1 );
    spi_master_read( &ctx->spi, r_buffer, 1 );

    spi_master_deselect_device( ctx->chip_select );  

    return r_buffer[ 0 ];
}

uint8_t ccrf_read_byte_status ( ccrf_t *ctx, uint8_t reg_address )
{
    uint8_t w_buffer[ 1 ] = { 0 };
    uint8_t r_buffer[ 1 ] = { 0 };

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 0 ] |= CCRF_READ_BURST;

    spi_master_select_device( ctx->chip_select );

    while ( ccrf_get_start( ctx ) );

    spi_master_write( &ctx->spi, w_buffer, 1 );
    spi_master_read( &ctx->spi, r_buffer, 1 );

    spi_master_deselect_device( ctx->chip_select );  

    return r_buffer[ 0 ];
}

void ccrf_read_bytes( ccrf_t *ctx, uint8_t reg_address, uint8_t *read_data, uint8_t n_bytes )
{
    uint8_t w_buffer[ 1 ] = { 0 };

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 0 ] |= CCRF_READ_BURST;

    spi_master_select_device( ctx->chip_select );
    
    while ( ccrf_get_start( ctx ) );

    spi_master_write( &ctx->spi, w_buffer, 1 );
    spi_master_read( &ctx->spi, read_data, n_bytes );
    
    spi_master_deselect_device( ctx->chip_select );  
}

void ccrf_sw_reset ( ccrf_t *ctx )
{
    uint8_t w_buffer[ 1 ] = { 0 };

    w_buffer[ 0 ] = CCRF_SRES;
    
    spi_master_select_device( ctx->chip_select );

    while ( ccrf_get_start( ctx ) );
    
    spi_master_write( &ctx->spi, w_buffer, 1 );
    
    spi_master_deselect_device( ctx->chip_select );  
}

void ccrf_hw_reset ( ccrf_t *ctx )
{
    uint8_t w_buffer[ 1 ] = { 0 };

    w_buffer[ 0 ] = CCRF_SRES;
    
    spi_master_deselect_device( ctx->chip_select );  
    Delay_10us( );
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_10us( );
    Delay_10us( );
    Delay_10us( );
    Delay_10us( );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, w_buffer, 1 );
    spi_master_deselect_device( ctx->chip_select );  
    Delay_1ms( );
    Delay_1ms( );
}

void ccrf_transmit_packet ( ccrf_t *ctx, uint8_t *tx_buffer, uint8_t n_bytes )
{
    ccrf_write_bytes( ctx, CCRF_TXFIFO, tx_buffer, n_bytes );

    ccrf_write_strobe( ctx, CCRF_STX );

    while ( !ccrf_get_start( ctx ) );

    while ( ccrf_get_start( ctx ) );
}

uint8_t ccrf_receive_packet ( ccrf_t *ctx, uint8_t *rx_buffer, uint8_t *length_buff )
{
    uint8_t status[ 2 ] = { 0 };
    uint8_t packet_length = 0;

    ccrf_write_strobe( ctx, CCRF_SRX );

    Delay_10us ( );
    
    while ( ccrf_get_start( ctx ) );

    if ( ( ccrf_read_byte_status( ctx, CCRF_RXBYTES ) & CCRF_BURST_IN_RXFIFO ) )
    {
        packet_length = ccrf_read_byte( ctx, CCRF_RXFIFO );

        if ( packet_length <= *length_buff )
        {
            ccrf_read_bytes( ctx, CCRF_RXFIFO, rx_buffer, packet_length );
            *length_buff = packet_length;

            ccrf_read_bytes( ctx, CCRF_RXFIFO, status, 2 );

            return ( status[ CCRF_LQI_RX ] & CCRF_CRC_OK );
        } 
        else 
        {
            *length_buff = ccrf_read_byte( ctx, CCRF_RXFIFO );

            ccrf_write_strobe( ctx, CCRF_SIDLE );

            ccrf_write_strobe( ctx, CCRF_SFRX );
            
            return 0;
        }
    } 
    else
    {
        return 0;
    }
}

uint8_t ccrf_transmit_packet_with_address ( ccrf_t *ctx, uint8_t *tx_buffer, uint8_t n_bytes, uint8_t *attempts )
{
    uint8_t rx_buffer[ 61 ] = { 0 };;
    uint8_t length = 0;

    ccrf_transmit_packet( ctx, tx_buffer, n_bytes );

    length = strlen( rx_buffer );

    switch ( ccrf_receive_packet( ctx, rx_buffer, &length ) )
    {
        case CCRF_RECEIVE_CRC_ERROR:
        {
            *attempts++;
            ccrf_transmit_packet_with_address( ctx, tx_buffer, n_bytes, attempts );
            break;
        }

        case CCRF_RECEIVE_CRC_OK:
        {
            return *attempts;
        }
    }
}

void ccrf_set_gd2_active_low ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_IOCFG2 );

    tmp |= 0x40;

    ccrf_write_byte( ctx, CCRF_IOCFG2, tmp );
}

void ccrf_set_gd2_active_high ( ccrf_t *ctx )
{
    uint8_t tmp = 0;
    
    tmp = ccrf_read_byte( ctx, CCRF_IOCFG2 );
    
    tmp &= 0xBF;
    
    ccrf_write_byte( ctx, CCRF_IOCFG2, tmp );
}

void ccrf_set_gd0_active_low ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_IOCFG0 );

    tmp |= 0x40;

    ccrf_write_byte( ctx, CCRF_IOCFG0, tmp );
}

void ccrf_set_gd0_active_high ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_IOCFG0 );

    tmp &= 0xBF;

    ccrf_write_byte( ctx, CCRF_IOCFG0, tmp );
}


void ccrf_enable_temperature_sensor ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_IOCFG0 );

    tmp &= 0x7F;

    ccrf_write_byte( ctx, CCRF_IOCFG0, tmp );
}

void ccrf_disable_temperature_sensor ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_IOCFG0 );

    tmp |= 0x80;

    ccrf_write_byte( ctx, CCRF_IOCFG0, tmp );
}

void ccrf_set_fifo_threshold ( ccrf_t *ctx, uint8_t threshold_rx_tx )
{
    ccrf_write_byte( ctx, CCRF_FIFOTHR, threshold_rx_tx & 0x0F );
}

void ccrf_set_max_length_packets ( ccrf_t *ctx, uint8_t max_length )
{
    ccrf_write_byte( ctx, CCRF_PKTLEN, max_length );
}

void ccrf_turn_data_whitening_on ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_PKTCTRL0 );

    tmp |= 0x40;

    ccrf_write_byte( ctx, CCRF_PKTCTRL0, tmp );
}

void ccrf_turn_data_whitening_off ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_PKTCTRL0 );

    tmp &= 0xBF;

    ccrf_write_byte( ctx, CCRF_PKTCTRL0, tmp );
}

void ccrf_format_rx_tx_data ( ccrf_t *ctx, uint8_t rx_tx_data_format )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_PKTCTRL0 );

    tmp &= 0xCF;
    tmp |= ( ( rx_tx_data_format & 0x03 ) << 4 );

    ccrf_write_byte( ctx, CCRF_PKTCTRL0, tmp );
}

void ccrf_set_device_address ( ccrf_t *ctx, uint8_t dev_addr )
{
    ccrf_write_byte( ctx, CCRF_ADDR, dev_addr );
}

void ccrf_set_channel_number ( ccrf_t *ctx, uint8_t ch_num )
{
    ccrf_write_byte( ctx, CCRF_CHANNR, ch_num );
}

void ccrf_set_if_frequency ( ccrf_t *ctx, uint8_t if_freq )
{
    ccrf_write_byte( ctx, CCRF_FSCTRL1, if_freq & 0x1F );
}

void ccrf_set_frequency_offset ( ccrf_t *ctx, uint8_t freq_offset )
{
    ccrf_write_byte( ctx, CCRF_FSCTRL0, freq_offset );
}

void ccrf_disable_dc_blocking_filter ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MDMCFG2 );

    tmp |= 0x80;

    ccrf_write_byte( ctx, CCRF_MDMCFG2, tmp );
}

void ccrf_enable_dc_blocking_filter ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MDMCFG2 );

    tmp &= 0x7F;

    ccrf_write_byte( ctx, CCRF_MDMCFG2, tmp );
}

void ccrf_set_modulation ( ccrf_t *ctx, uint8_t rf_modulation )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MDMCFG2 );

    tmp &= 0x8F;
    
    switch ( rf_modulation )
    {
        case 0: 
        {
            tmp |= 0x00;
            break;
        }
        case 1:
        {
            tmp |= 0x10;
            break;
        }
        case 2:
        {
            tmp |= 0x30;
            break;
        }
        case 3:
        {
            tmp |= 0x70;
            break;
        }
    }

    ccrf_write_byte( ctx, CCRF_MDMCFG2, tmp );
}

void ccrf_enable_manchester_encoding ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MDMCFG2 );

    tmp |= 0x08;

    ccrf_write_byte( ctx, CCRF_MDMCFG2, tmp );
}

void ccrf_disable_manchester_encoding ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MDMCFG2 );

    tmp &= 0xF7;

    ccrf_write_byte( ctx, CCRF_MDMCFG2, tmp );
}

void ccrf_set_sync_word_qualifier_mode ( ccrf_t *ctx, uint8_t q_mode )
{
    uint8_t tmp = 0;
    
    tmp = ccrf_read_byte( ctx, CCRF_MDMCFG2 );

    tmp &= 0xF8;
    tmp |= ( q_mode & 0x07 );

    ccrf_write_byte( ctx, CCRF_MDMCFG2, tmp );
}

void ccrf_disable_fec ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MDMCFG1 );

    tmp &= 0x7F;

    ccrf_write_byte( ctx, CCRF_MDMCFG1, tmp );
}

void ccrf_enable_fec ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MDMCFG1 );

    tmp |= 0x80;

    ccrf_write_byte( ctx, CCRF_MDMCFG1, tmp );
}

void ccrf_set_min_num_preamble ( ccrf_t *ctx, uint8_t p_num )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MDMCFG1 );

    tmp &= 0x8F;
    tmp |= ( ( p_num & 0x07 ) << 4 );

    ccrf_write_byte( ctx, CCRF_MDMCFG1, tmp );
}

void ccrf_set_cca_mode ( ccrf_t *ctx, uint8_t cca_mode )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MCSM1 );

    tmp &= 0xCF;
    tmp |= ( ( cca_mode & 0x03 ) << 4 );

    ccrf_write_byte( ctx, CCRF_MCSM1, tmp );
}

void ccrf_set_state_packet_recived ( ccrf_t *ctx, uint8_t pr_state )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MCSM1 );

    tmp &= 0xF3;
    tmp |= ( ( pr_state & 0x03 ) << 2 );

    ccrf_write_byte( ctx, CCRF_MCSM1, tmp );
}

void ccrf_set_state_packet_sent ( ccrf_t *ctx, uint8_t ps_state )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MCSM1 );

    tmp &= 0xFC;
    tmp |= ( ps_state & 0x03 );

    ccrf_write_byte( ctx, CCRF_MCSM1, tmp );
}

void ccrf_set_auto_calibrate_mode ( ccrf_t *ctx, uint8_t ac_mode )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_MCSM0 );

    tmp &= 0xCF;
    tmp |= ( ( ac_mode & 0x03 ) << 4 );

    ccrf_write_byte( ctx, CCRF_MCSM0, tmp );
}

void ccrf_set_freq_loop_gain_bs ( ccrf_t *ctx, uint8_t fcl_gain )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_FOCCFG );

    tmp &= 0xE7;
    tmp |= ( ( fcl_gain & 0x03 ) << 3 );

    ccrf_write_byte( ctx, CCRF_FOCCFG, tmp );
}

void ccrf_set_freq_loop_gain_as ( ccrf_t *ctx, uint8_t fcl_gain )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_FOCCFG );

    tmp &= 0xFB;
    tmp |= ( ( fcl_gain & 0x01 ) << 2 );

    ccrf_write_byte( ctx, CCRF_FOCCFG, tmp );
}

void ccrf_set_bit_sync_config ( ccrf_t *ctx, uint8_t bs_config )
{
    ccrf_write_byte( ctx, CCRF_BSCFG, bs_config );
}

void ccrf_set_dvga_gain ( ccrf_t *ctx, uint8_t dvga_gain )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL2 );

    tmp &= 0x3F;
    tmp |= ( ( dvga_gain & 0x03 ) << 6 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL2, tmp );
}

void ccrf_set_lna_gain ( ccrf_t *ctx, uint8_t lna_gain )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL2 );

    tmp &= 0xC7;
    tmp |= ( ( lna_gain & 0x07 ) << 3 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL2, tmp );
}

void ccrf_set_amplitude_ch_filter ( ccrf_t *ctx, uint8_t ach_filter )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL2 );

    tmp &= 0xF8;
    tmp |= ( ach_filter & 0x07 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL2, tmp );
}

void ccrf_set_lna_strategies ( ccrf_t *ctx, uint8_t lna_strat )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL1 );

    tmp &= 0xBF;
    tmp |= ( ( lna_strat & 0x01 ) << 6 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL1, tmp );
}

void ccrf_set_relative_rssi_threshold ( ccrf_t *ctx, uint8_t rssi_threshold )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL1 );

    tmp &= 0xCF;
    tmp |= ( ( rssi_threshold & 0x03 ) << 4 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL1, tmp );
}

void ccrf_set_absolute_rssi_threshold ( ccrf_t *ctx, uint8_t rssi_threshold )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL1 );

    tmp &= 0xF0;
    tmp |= ( rssi_threshold & 0x07 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL1, tmp );
}

void ccrf_set_hysteresis_lvl ( ccrf_t *ctx, uint8_t hyst_lvl )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL0 );

    tmp &= 0x3F;
    tmp |= ( ( hyst_lvl & 0x03 ) << 6 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL0, tmp );
}

void ccrf_set_num_ch_filter ( ccrf_t *ctx, uint8_t num_ch_filter )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL0 );

    tmp &= 0xCF;
    tmp |= ( ( num_ch_filter & 0x03 ) << 4 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL0, tmp );
}

void ccrf_set_agc_gain ( ccrf_t *ctx, uint8_t agc_gain )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL0 );

    tmp &= 0xF3;
    tmp |= ( ( agc_gain & 0x03 ) << 2 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL0, tmp );
}

void ccrf_set_avr_len_ampitude ( ccrf_t *ctx, uint8_t al_amp )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_AGCCTRL0 );

    tmp &= 0xFC;
    tmp |= ( al_amp & 0x03 );

    ccrf_write_byte( ctx, CCRF_AGCCTRL0, tmp );
}

void ccrf_set_auto_initial_calibration ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_WORCTRL );

    tmp &= 0x7F;

    ccrf_write_byte( ctx, CCRF_WORCTRL, tmp );
}

void ccrf_set_timeout_reg_block ( ccrf_t *ctx, uint8_t timeout )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_WORCTRL );

    tmp &= 0x8F;
    tmp |= ( ( timeout & 0x07 ) << 4 );

    ccrf_write_byte( ctx, CCRF_WORCTRL, tmp );
}

void ccrf_disable_osc_rc ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_WORCTRL );

    tmp &= 0xF7;

    ccrf_write_byte( ctx, CCRF_WORCTRL, tmp );
}

void ccrf_enable_osc_rc ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_WORCTRL );

    tmp |= 0x08;

    ccrf_write_byte( ctx, CCRF_WORCTRL, tmp );
}

void ccrf_set_timeout_wor ( ccrf_t *ctx, uint8_t timeout )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_WORCTRL );

    tmp &= 0xFC;
    tmp |= ( timeout & 0x03 );

    ccrf_write_byte( ctx, CCRF_WORCTRL, tmp );
}

uint8_t ccrf_get_chip_part_number ( ccrf_t *ctx )
{
    return ccrf_read_byte( ctx, CCRF_PARTNUM );
}

uint8_t ccrf_get_chip_version_number ( ccrf_t *ctx )
{
    return ccrf_read_byte( ctx, CCRF_VERSION );
}

uint8_t ccrf_get_rssi ( ccrf_t *ctx )
{
    return ccrf_read_byte( ctx, CCRF_RSSI );
}

uint8_t ccrf_get_mrc_state ( ccrf_t *ctx )
{
    return ccrf_read_byte( ctx, CCRF_MARCSTATE );
}

uint8_t ccrf_get_gd0_and_packet_state ( ccrf_t *ctx )
{
    return ccrf_read_byte( ctx, CCRF_PKTSTATUS );
}

uint8_t ccrf_get_underflow_rx_fifo ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_RXBYTES );
    
    tmp &= 0x80;
    tmp >>= 7;

    return tmp;
}

uint8_t ccrf_get_rx_fifo_num_bytes ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_RXBYTES );
    
    tmp &= 0x7F;

    return tmp;
}

uint8_t ccrf_get_rc_osc_cal_result ( ccrf_t *ctx )
{
    uint8_t tmp = 0;

    tmp = ccrf_read_byte( ctx, CCRF_RCCTRL1_STATUS );

    tmp &= 0x7F;

    return tmp;
}

// ------------------------------------------------------------------------- END
