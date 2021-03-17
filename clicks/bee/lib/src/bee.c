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

#include "bee.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BEE_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static uint8_t data_rx_fifo[1 + BEE_HEADER_LENGHT + BEE_DATA_LENGHT + 2 + 1 + 1];
static uint8_t lost_data;
static uint8_t DATA_RX[ BEE_DATA_LENGHT ];
static uint8_t lqi[ 1 ];
static uint8_t rssi2[ 1 ];
static uint8_t data_tx_normal_fifo[ BEE_DATA_LENGHT + BEE_HEADER_LENGHT + 2 ];
static uint8_t seq_number;
static uint8_t pan_id_1[ 2 ];
static uint8_t pan_id_2[ 2 ];
static uint8_t address_short_1[ 2 ];
static uint8_t address_long_1[ 8 ];
static uint8_t address_short_2[ 2 ];
static uint8_t address_long_2[ 8 ];

static uint8_t data_tx[ BEE_DATA_LENGHT ];

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void bee_cfg_setup ( bee_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->wa = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 1000000; 
}

BEE_RETVAL bee_init ( bee_t *ctx, bee_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = BEE_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return BEE_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BEE_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->wa, cfg->wa );
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return BEE_OK;
}

void bee_generic_transfer ( bee_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );      
}

void bee_write_byte_short ( bee_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = reg_address << 1;
    w_buffer[ 0 ] &= 0x7F;
    w_buffer[ 0 ] |= 0x01;
    w_buffer[ 1 ] = write_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, w_buffer, 2 );
    spi_master_deselect_device( ctx->chip_select );    
}

uint8_t bee_read_byte_short ( bee_t *ctx, uint8_t reg_address )
{
    uint8_t w_buffer[ 1 ];
    uint8_t r_buffer[ 1 ];

    w_buffer[ 0 ] = reg_address << 1;
    w_buffer[ 0 ] &= 0x7E;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, w_buffer, 1 );
    spi_master_read( &ctx->spi, r_buffer, 1 );
    spi_master_deselect_device( ctx->chip_select );    

    return r_buffer[ 0 ];
}

void bee_write_byte_long ( bee_t *ctx, uint16_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 3 ];

    w_buffer[ 0 ] = reg_address >> 3;
    w_buffer[ 0 ] &= 0x7F;
    w_buffer[ 0 ] |= 0x80;
    w_buffer[ 1 ] = reg_address << 5;
    w_buffer[ 1 ] &= 0xE0;
    w_buffer[ 1 ] |= 0x10;
    w_buffer[ 2 ] = write_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, w_buffer, 3 );
    spi_master_deselect_device( ctx->chip_select );    
}

uint8_t bee_read_byte_long ( bee_t *ctx, uint16_t reg_address )
{
    uint8_t w_buffer[ 2 ];
    uint8_t r_buffer[ 1 ];

    w_buffer[ 0 ] = reg_address >> 3;
    w_buffer[ 0 ] &= 0x7F;
    w_buffer[ 0 ] |= 0x80;
    w_buffer[ 1 ] = reg_address << 5;
    w_buffer[ 1 ] &= 0xE0;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, w_buffer, 2 );
    spi_master_read( &ctx->spi, r_buffer, 1 );
    spi_master_deselect_device( ctx->chip_select );  

    return r_buffer[ 0 ];
}

void bee_hw_reset ( bee_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_5ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
}

void bee_power_reset ( bee_t *ctx )
{
    bee_write_byte_short( ctx, BEE_SOFTRST, 0x04 );
}

void bee_bb_reset ( bee_t *ctx )
{
    bee_write_byte_short( ctx, BEE_SOFTRST, 0x02 );
}

void bee_mac_reset ( bee_t *ctx )
{
    bee_write_byte_short( ctx, BEE_SOFTRST, 0x01 );
}

void bee_soft_reset ( bee_t *ctx )
{
    bee_write_byte_short( ctx, BEE_SOFTRST, 0x07 );
}

void bee_rf_reset ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    tmp = bee_read_byte_short( ctx, BEE_RFCTL );
    tmp = tmp | 0x04;
    bee_write_byte_short( ctx, BEE_RFCTL, tmp );
    tmp = tmp & ( ~0x04 );
    bee_write_byte_short( ctx, BEE_RFCTL, tmp );
    Delay_1ms( );
}

void bee_enable_interrupt ( bee_t *ctx )
{
    bee_write_byte_long( ctx, BEE_SLPCON0, 0x02 );
    bee_write_byte_short( ctx, BEE_INTCON_M, 0xF7 );
}

void bee_set_channel ( bee_t *ctx, uint8_t n_channel )
{
    if ( ( n_channel > 26 ) || ( n_channel < 11 ) )
    {
        n_channel = 11;
    }
  
    switch ( n_channel ) 
    {
        case 11:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x02 );
            break;
        }
        case 12:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x12 );
            break;
        }
        case 13:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x22 );
            break;
        }
        case 14:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x32 );
            break;
        }
        case 15:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x42 );
            break;
        }
        case 16:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x52 );
            break;
        }
        case 17:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x62 );
            break;
        }
        case 18:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x72 );
            break;
        }
        case 19:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x82 );
            break;
        }
        case 20:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0x92 );
            break;
        }
        case 21:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0xA2 );
            break;
        }
        case 22:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0xB2 );
            break;
        }
        case 23:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0xC2 );
            break;
        }
        case 24:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0xD2 );
            break;
        }
        case 25:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0xE2 );
            break;
        }
        case 26:
        {
            bee_write_byte_long( ctx, BEE_RFCON0, 0xF2 );
            break;
        }
    }
    
    bee_rf_reset( ctx );
}

void bee_set_cca_mode ( bee_t *ctx, uint8_t cca_mode )
{
    uint8_t tmp;
    tmp = 0;
    
    switch ( cca_mode )
    {
        case 1: 
        {
            tmp = bee_read_byte_short( ctx, BEE_BBREG2 );
            tmp = tmp | 0x80;
            tmp = tmp & 0xDF;
            bee_write_byte_short( ctx, BEE_BBREG2, tmp );
            bee_write_byte_short( ctx, BEE_CCAEDTH, 0x60 );
            break;
        }

        case 2: 
        {
          tmp = bee_read_byte_short( ctx, BEE_BBREG2 );
          tmp = tmp | 0x40;
          tmp = tmp & 0x7F;
          bee_write_byte_short( ctx, BEE_BBREG2, tmp );

          tmp = bee_read_byte_short( ctx, BEE_BBREG2 );
          tmp = tmp | 0x38;
          tmp = tmp & 0xFB;
          bee_write_byte_short( ctx, BEE_BBREG2, tmp );
          break;
        }

        case 3: 
        {
          tmp = bee_read_byte_short( ctx, BEE_BBREG2);
          tmp = tmp | 0xC0;
          bee_write_byte_short( ctx, BEE_BBREG2, tmp );

          tmp = bee_read_byte_short( ctx, BEE_BBREG2 );
          tmp = tmp | 0x38;
          tmp = tmp & 0xFB;
          bee_write_byte_short( ctx, BEE_BBREG2, tmp );
          bee_write_byte_short( ctx, BEE_CCAEDTH, 0x60 );
          break;
        }
    }
}

void bee_set_rssi_mode ( bee_t *ctx, uint8_t rssi_mode )
{
    uint8_t tmp;
    tmp = 0;

    switch ( rssi_mode )
    {
        case 1: 
        {
            tmp = bee_read_byte_short( ctx, BEE_BBREG6 );
            tmp = tmp | 0x80;
            bee_write_byte_short( ctx, BEE_BBREG6, tmp );
            break;
        }
        case 2:
        {
            bee_write_byte_short( ctx, BEE_BBREG6, 0x40 );
            break;
        }
    }
}

void bee_nonbeacon_pan_coordinator_device ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    tmp = bee_read_byte_short( ctx, BEE_RXMCR );
    tmp = tmp | 0x08;
    bee_write_byte_short( ctx, BEE_RXMCR, tmp );

    tmp = bee_read_byte_short( ctx, BEE_TXMCR );
    tmp = tmp & 0xDF;
    bee_write_byte_short( ctx, BEE_TXMCR, tmp );

    bee_write_byte_short( ctx, BEE_ORDER, 0xFF );
}

void bee_nonbeacon_coordinator_device ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    tmp = bee_read_byte_short( ctx, BEE_RXMCR );
    tmp = tmp | 0x04;
    bee_write_byte_short( ctx, BEE_RXMCR, tmp );

    tmp = bee_read_byte_short( ctx, BEE_TXMCR );
    tmp = tmp & 0xDF;
    bee_write_byte_short( ctx, BEE_TXMCR, tmp );

    bee_write_byte_short( ctx, BEE_ORDER, 0xFF );
}

void bee_nonbeacon_device ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    tmp = bee_read_byte_short( ctx, BEE_RXMCR );
    tmp = tmp & 0xF3;
    bee_write_byte_short( ctx, BEE_RXMCR, tmp);

    tmp = bee_read_byte_short( ctx, BEE_TXMCR );
    tmp = tmp & 0xDF;
    bee_write_byte_short( ctx, BEE_TXMCR, tmp );
}

void bee_set_ack ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    tmp = bee_read_byte_short( ctx, BEE_TXNCON );
    tmp = tmp | 0x04;
    bee_write_byte_short( ctx, BEE_TXNCON, tmp );
}

void bee_set_not_ack ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    tmp = bee_read_byte_short( ctx, BEE_TXNCON );
    tmp = tmp | (~0x04);
    bee_write_byte_short( ctx, BEE_TXNCON, tmp );
}
 
void bee_enable_encrypt ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    tmp = bee_read_byte_short( ctx, BEE_TXNCON );
    tmp = tmp | 0x02;
    bee_write_byte_short( ctx, BEE_TXNCON, tmp );
}

void bee_disabl_encrypt ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    tmp = bee_read_byte_short( ctx, BEE_TXNCON );
    tmp = tmp | (~0x02);
    bee_write_byte_short( ctx, BEE_TXNCON, tmp );
}

void bee_set_ifs_recomended ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    bee_write_byte_short( ctx, BEE_RXMCR, 0x93 );

    tmp = bee_read_byte_short( ctx, BEE_TXPEND );
    tmp = tmp | 0x7C;
    bee_write_byte_short( ctx, BEE_TXPEND, tmp );

    tmp = bee_read_byte_short( ctx, BEE_TXSTBL );
    tmp = tmp | 0x90;
    bee_write_byte_short( ctx, BEE_TXSTBL, tmp );

    tmp = bee_read_byte_short( ctx, BEE_TXTIME );
    tmp = tmp | 0x31;
    bee_write_byte_short( ctx, BEE_TXTIME, tmp );
}

void bee_set_ifs_default ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    bee_write_byte_short( ctx, BEE_RXMCR, 0x75 );

    tmp = bee_read_byte_short( ctx, BEE_TXPEND );
    tmp = tmp | 0x84;
    bee_write_byte_short( ctx, BEE_TXPEND, tmp );

    tmp = bee_read_byte_short( ctx, BEE_TXSTBL );
    tmp = tmp | 0x50;
    bee_write_byte_short( ctx, BEE_TXSTBL, tmp );

    tmp = bee_read_byte_short( ctx, BEE_TXTIME );
    tmp = tmp | 0x41;
    bee_write_byte_short( ctx, BEE_TXTIME, tmp );
}

void bee_set_reception_mode ( bee_t *ctx, uint8_t r_mode )
{
    uint8_t tmp;
    tmp = 0;

    switch ( r_mode )
    {
        case 1:
        {
            tmp = bee_read_byte_short( ctx, BEE_RXMCR );
            tmp = tmp & ( ~0x03 );
            bee_write_byte_short( ctx, BEE_RXMCR, tmp );
            break;
        }

        case 2: 
        {
            tmp = bee_read_byte_short( ctx, BEE_RXMCR );
            tmp = tmp & ( ~0x01 );
            tmp = tmp | 0x02;
            bee_write_byte_short( ctx, BEE_RXMCR, tmp );
            break;
        }

        case 3: 
        {
            tmp = bee_read_byte_short( ctx, BEE_RXMCR );
            tmp = tmp & ( ~0x02 );
            tmp = tmp | 0x01;
            bee_write_byte_short( ctx, BEE_RXMCR, tmp );
            break;
        }
    }
}

void bee_set_frame_format_filter ( bee_t *ctx, uint8_t fff_mode )
{
    uint8_t tmp;
    tmp = 0;
    
    switch ( fff_mode )
    {
        case 1:
        {
            tmp = bee_read_byte_short( ctx, BEE_RXFLUSH );
            tmp = tmp & ( ~0x0E );
            bee_write_byte_short( ctx, BEE_RXFLUSH, tmp );
            break;
        }

        case 2:
        {
            tmp = bee_read_byte_short( ctx, BEE_RXFLUSH );
            tmp = tmp & ( ~0x06 );
            tmp = tmp | 0x08;
            bee_write_byte_short( ctx, BEE_RXFLUSH, tmp );
            break;
        }

        case 3:
        {
            tmp = bee_read_byte_short( ctx, BEE_RXFLUSH );
            tmp = tmp & ( ~0x0A );
            tmp = tmp | 0x04;
            bee_write_byte_short( ctx, BEE_RXFLUSH, tmp );
            break;
        }
        
        case 4:
        {
            tmp = bee_read_byte_short( ctx, BEE_RXFLUSH );
            tmp = tmp & (~0x0C);
            tmp = tmp | 0x02;
            bee_write_byte_short( ctx, BEE_RXFLUSH, tmp );
            break;
        }
    }
}

void bee_flush_rx_fifo_pointer ( bee_t *ctx ) 
{
    uint8_t tmp;
    tmp = 0;

    tmp = bee_read_byte_short( ctx, BEE_RXFLUSH );
    tmp = tmp | 0x01;
    bee_write_byte_short( ctx, BEE_RXFLUSH, tmp );
}

void bee_set_short_address (  bee_t *ctx, uint8_t *short_address )
{
    bee_write_byte_short( ctx, BEE_SADRL, short_address[ 0 ] );
    bee_write_byte_short( ctx, BEE_SADRH, short_address[ 1 ] );
}

void bee_set_long_address ( bee_t *ctx, uint8_t *long_address )
{
    uint8_t cnt;

    for ( cnt = 0; cnt < 8; cnt++ )
    {
        bee_write_byte_short( ctx, BEE_EADR0 + cnt, long_address[ cnt ] );
    }
}

void bee_set_pan_id ( bee_t *ctx, uint8_t *pan_id )
{
    bee_write_byte_short( ctx, BEE_PANIDL, pan_id[ 0 ] );
    bee_write_byte_short( ctx, BEE_PANIDH, pan_id[ 1 ] );
}

void bee_enable_immediate_wake_up ( bee_t *ctx )
{
    uint8_t tmp;
    tmp = 0;

    digital_out_low( &ctx->wa );
    Delay_10ms( );
    tmp = bee_read_byte_short( ctx, BEE_RXFLUSH );
    tmp = tmp | 0x60;
    bee_write_byte_short( ctx, BEE_RXFLUSH, tmp );

    tmp = bee_read_byte_short( ctx, BEE_WAKECON );
    tmp = tmp | 0x80;
    bee_write_byte_short( ctx, BEE_WAKECON, tmp );
}

void bee_hw_wake_up ( bee_t *ctx )
{
    digital_out_high( &ctx->wa );
    Delay_5ms( );
}

void bee_enable_pll ( bee_t *ctx )
{
    bee_write_byte_long( ctx, BEE_RFCON2, 0x80 );
}

void bee_disable_pll ( bee_t *ctx )
{
    bee_write_byte_long( ctx, BEE_RFCON2, 0x00 );
}

void bee_set_tx_power ( bee_t *ctx, uint8_t tx_power )
{
    if ( ( tx_power < 0 ) || ( tx_power > 31 ) )
    {
        tx_power = 31;
    }

    tx_power = 31 - tx_power;
    tx_power &= 0x1F;
    tx_power <<= 3;
    tx_power &= 0xF8;
    bee_write_byte_long( ctx, BEE_RFCON3, tx_power );
}

void bee_basic_init ( bee_t *ctx ) 
{
    bee_write_byte_short( ctx, BEE_PACON2, 0x98 );
    bee_write_byte_short( ctx, BEE_TXSTBL, 0x95 );
    bee_write_byte_long( ctx, BEE_RFCON1, 0x01 );
    bee_enable_pll( ctx );
    bee_write_byte_long( ctx, BEE_RFCON6, 0x90 );
    bee_write_byte_long( ctx, BEE_RFCON7, 0x80 );
    bee_write_byte_long( ctx, BEE_RFCON8, 0x10 );
    bee_write_byte_long( ctx, BEE_SLPCON1, 0x21 );
}

void bee_nonbeacon_init ( bee_t *ctx ) 
{
    bee_basic_init( ctx );
    bee_set_cca_mode( ctx, 1 );
    bee_set_rssi_mode( ctx, 2 );
    bee_enable_interrupt( ctx );
    bee_set_channel( ctx, 11 );
    bee_rf_reset( ctx );
}

uint8_t bee_interrupt_activity ( bee_t *ctx )
{
    uint8_t cnt_i;
    uint8_t cnt_j;
    uint8_t intn_d;

    intn_d = 0;
    cnt_j = 0;
  
    for ( cnt_i = 0; cnt_i < 5; cnt_i++ )
    {
        if ( digital_in_read( &ctx->int_pin ) )
        {
            cnt_j++;
        }
    }
  
    if ( cnt_j > 2 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void bee_start_transmit ( bee_t *ctx )
{
    uint8_t tmp;

    tmp = bee_read_byte_short( ctx, BEE_TXNCON );
    tmp = tmp | 0x01;
    bee_write_byte_short( ctx, BEE_TXNCON, tmp );
}

void bee_read_rx_fifo ( bee_t *ctx, uint8_t *rx_data )
{
    uint8_t tmp;
    uint8_t cnt;

    tmp = bee_read_byte_short( ctx, BEE_BBREG1 );
    tmp = tmp | 0x04;
    bee_write_byte_short( ctx, BEE_BBREG1, tmp );

    for ( cnt = 0; cnt < 128; cnt++ )
    {
        if ( cnt <  ( 1 + BEE_DATA_LENGHT + BEE_HEADER_LENGHT + 2 + 1 + 1 ) )
        {
            data_rx_fifo[ cnt ] = bee_read_byte_long( ctx, BEE_RX_FIFO + cnt );
        }
        
        if ( cnt >= ( 1 + BEE_DATA_LENGHT + BEE_HEADER_LENGHT + 2 + 1 + 1 ) )
        {
            lost_data = bee_read_byte_long( ctx, BEE_RX_FIFO + cnt );
        }
    }
    
    for ( cnt = 0; cnt < BEE_DATA_LENGHT; cnt++) {
        *rx_data++ = data_rx_fifo[ BEE_HEADER_LENGHT + cnt + 1];
    }
    
    *lqi   = data_rx_fifo[ 1 + BEE_HEADER_LENGHT + BEE_DATA_LENGHT + 2 ];
    *rssi2 = data_rx_fifo[ 1 + BEE_HEADER_LENGHT + BEE_DATA_LENGHT + 3 ];

    tmp = bee_read_byte_short( ctx, BEE_BBREG1 );
    tmp = tmp & ( ~0x04 );
    bee_write_byte_short( ctx, BEE_BBREG1, tmp );
}

void bee_write_tx_normal_fifo ( bee_t *ctx, uint16_t address_tx_normal_fifo, uint8_t *tx_data )
{
    uint16_t cnt;

    for ( cnt = 0; cnt < (BEE_HEADER_LENGHT + BEE_DATA_LENGHT + 2); cnt++ )
    {
        bee_write_byte_long( ctx, address_tx_normal_fifo + cnt, tx_data[ cnt ] );
    }

    bee_set_not_ack( ctx );
    bee_disabl_encrypt( ctx );
    bee_start_transmit( ctx );
}

uint8_t bee_interrupt ( bee_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

