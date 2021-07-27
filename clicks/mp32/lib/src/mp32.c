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

#include "mp32.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_delay_cmd_set ( void );

static void dev_delay_reset ( void );

static void dev_delay_write ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mp32_cfg_setup ( mp32_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

MP32_RETVAL mp32_init ( mp32_t *ctx, mp32_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    return MP32_OK;
}

void mp32_generic_write ( mp32_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t mp32_generic_read ( mp32_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void mp32_hw_reset ( mp32_t *ctx )
{
    digital_out_high( &ctx->rst );
}

void mp32_rx_cmd ( mp32_t *ctx, uint8_t *rd_data, uint8_t len )
{
    uint8_t cnt;
    
    for ( cnt = 0; cnt < len; cnt++ )
    {
        mp32_generic_read( ctx, rd_data, 1  );
    }
}

void mp32_tx_cmd ( mp32_t *ctx, uint8_t cmd, uint16_t spec_data )
{
    uint8_t tmp;
    uint8_t temp;
    
    temp = MP32_CMD_START_CODE;
    mp32_generic_write( ctx, &temp, 1 );  // Start
    
    temp = MP32_VERSION_CODE;
    mp32_generic_write( ctx, &temp, 1 );  // Firmware version
    
    temp = 0x06;
    mp32_generic_write( ctx, &temp, 1 );  // Command length
    
    mp32_generic_write( ctx, &cmd, 1 );  
    
    temp = MP32_FDBK_CODE_OFF;              
    mp32_generic_write( ctx, &temp, 1 );  // Feedback flag
    
    
    tmp = ( uint8_t ) ( spec_data >> 8 );
    mp32_generic_write( ctx, &tmp, 1 );   // DataH
    
    tmp = ( uint8_t ) spec_data;
    mp32_generic_write( ctx, &tmp, 1 );   // DataL
    
    temp = MP32_CMD_END_CODE;
    mp32_generic_write( ctx, &temp, 1 );  // Stop
    
    if ( cmd == MP32_SET_DEV )
    {
        dev_delay_cmd_set( );
    }
    else if ( cmd == MP32_RESET )
    {
        dev_delay_reset( );
    }
    else
    {
        dev_delay_write( );
    }
}

void mp32_sw_reset ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_RESET, 0x0000 );
}

void mp32_play_specific ( mp32_t *ctx, uint16_t track_index )
{
    mp32_tx_cmd( ctx, MP32_PLAY_SPEC_TRACK, track_index );
}

void mp32_play_mode ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_PLAY, 0x0000 );
}

void mp32_pause_mode ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_PAUSE, 0x0000 );
}

void mp32_stop_mode ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_STOP, 0x0000 );
}

void mp32_set_volume ( mp32_t *ctx, uint8_t perc )
{
    uint16_t volume;

    if ( perc < 0 )
    {
        perc = 0;
    }
    if ( perc > 100 )
    {
        perc = 100;
    }

    volume = ( perc * 0x1E ) / 100;

    mp32_tx_cmd( ctx, MP32_SET_VOL_VALUE, volume );
}

void mp32_volume_up ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_SET_VOL_UP, 0x0000 );
}

void mp32_volume_down ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_SET_VOL_DOWN, 0x0000 );
}

void mp32_play_next ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_PLAY_NEXT_SONG, 0x0000 );
}

void mp32_play_previous ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_PLAY_PREV_SONG, 0x0000 );
}

void mp32_set_eq ( mp32_t *ctx, uint8_t eq )
{
    uint16_t tmp;
    
    if ( ( eq < 0 ) || ( eq > 5 ) )
    {
        eq = 0;
    }
    
    tmp = eq;
    
    mp32_tx_cmd( ctx, MP32_SET_EQUALIZER, tmp );
}

void mp32_repeat_current ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_REP_CURR_TRACK, 0x0000 );
}

void mp32_set_device ( mp32_t *ctx, uint8_t device )
{
    uint16_t tmp;

    tmp = 0x0000;

    tmp |= device;
    
    mp32_tx_cmd( ctx, MP32_SET_DEV, tmp );
}

void mp32_set_low_power_mode ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_ENTER_STDBY_MODE, 0x0000 );
}

void mp32_play_spec_in_fol ( mp32_t *ctx, uint8_t fol_inx, uint8_t track_inx )
{
    uint16_t tmp;

    tmp = 0x0000;
    
    tmp = track_inx;
    tmp <<= 8;
    tmp |= fol_inx;
    
    mp32_tx_cmd( ctx, MP32_PLAY_SONG_SPEC, tmp );
}

void mp32_loop_all ( mp32_t *ctx, uint8_t loop_mode )
{
    uint16_t tmp;

    tmp = 0x0000;

    tmp |= loop_mode;
    
    mp32_tx_cmd( ctx, MP32_SET_ALL_LOOP, tmp );
}

void mp32_play_fol ( mp32_t *ctx, uint8_t fol_inx )
{
    uint16_t tmp;
    
    tmp = 0x0000;

    tmp |= fol_inx;
    
    mp32_tx_cmd( ctx, MP32_PLAY_SONG_MP3, tmp );
}

void mp32_loop_fol ( mp32_t *ctx, uint8_t fol_inx )
{
    uint16_t tmp;

    tmp = 0x0000;

    tmp |= fol_inx;
    
    mp32_tx_cmd( ctx, MP32_SET_LOOP_FOL, tmp );
}

void mp32_random_all ( mp32_t *ctx )
{
    mp32_tx_cmd( ctx, MP32_SET_SHUF_ALL, 0x0000 );
}

void mp32_loop ( mp32_t *ctx, uint8_t state )
{
    uint16_t tmp;

    tmp = 0x0000;

    tmp |= state;
    
    mp32_tx_cmd( ctx, MP32_REP_SINGLE, tmp );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_delay_cmd_set ( void )
{
    Delay_100ms( );
    Delay_100ms( );
}

static void dev_delay_reset ( void )
{
    Delay_1sec( );
}

static void dev_delay_write ( void )
{
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

