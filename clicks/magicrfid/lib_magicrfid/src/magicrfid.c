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
 * @file magicrfid.c
 * @brief Magic RFID Click Driver.
 */

#include "magicrfid.h"

/**
 * @brief Magic RFID Click CRC-CCITT table.
 * @details CRC-CCITT 16-bit table for calculating CRC of Magic RFID Click driver.
 */
static uint16_t magicrfid_crc_table[ ] =
{
    0x0000,
    0x1021,
    0x2042,
    0x3063,
    0x4084,
    0x50A5,
    0x60C6,
    0x70E7,
    0x8108,
    0x9129,
    0xA14A,
    0xB16B,
    0xC18C,
    0xD1AD,
    0xE1CE,
    0xF1EF,
};

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Magic RFID calculate CRC function.
 * @details This function calculates CRC of the selected input data.
 * @param[in] data_buf : Data to be calculated.
 * @param[in] len : Number of bytes to be calculated.
 * @return CRC value.
 */
static uint16_t magicrfid_calculate_crc ( uint8_t *data_buf, uint8_t len );

/**
 * @brief Magic RFID device delay function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[in] time_ms : Duration of the delay.
 */
static void magicrfid_delay_com ( uint16_t time_ms );

/**
 * @brief Magic RFID device reset delay function.
 * @details Reset delay of  300 milliseconds.
 */
static void magicrfid_reset_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void magicrfid_cfg_setup ( magicrfid_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t magicrfid_init ( magicrfid_t *ctx, magicrfid_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->en, cfg->en );
    
    return UART_SUCCESS;
}

void magicrfid_default_cfg ( magicrfid_t *ctx ) 
{
    magicrfid_device_reset( ctx );
    magicrfid_delay_com( MAGICRFID_LONG_DELAY_TIME );
    
    magicrfid_set_baud_rate( ctx, 115200 );
    magicrfid_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    
    magicrfid_set_region( ctx, MAGICRFID_REGION_OPEN );
    magicrfid_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    
    magicrfid_set_read_power( ctx, 500 );
    magicrfid_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    
    magicrfid_set_write_power( ctx, 500 );
    magicrfid_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    
    magicrfid_set_antenna_port( ctx );
    magicrfid_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    
    magicrfid_set_tag_protocol( ctx, MAGICRFID_TAG_PROTOCOL_GEN2 );
    magicrfid_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    
    magicrfid_set_reader_config ( ctx, 0x0C, 0x00 );
    magicrfid_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
    
    magicrfid_start_reading( ctx );
    magicrfid_delay_com( MAGICRFID_NORMAL_DELAY_TIME );
}

err_t magicrfid_generic_write ( magicrfid_t *ctx, uint8_t *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t magicrfid_generic_read ( magicrfid_t *ctx, uint8_t *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void magicrfid_device_reset ( magicrfid_t *ctx ) 
{
    digital_out_low( &ctx->en );
    magicrfid_reset_delay( );
    digital_out_high( &ctx->en );
}

void magicrfid_send_command ( magicrfid_t *ctx, magicrfid_command_t cmd )
{
    uint8_t tx_data[ MAGICRFID_TX_DRV_BUFFER_SIZE ] = { 0 };
    uint16_t crc = 0;
    
    uart_clear ( &ctx->uart );
    
    tx_data[ 0 ] = MAGICRFID_HEADER; 
    tx_data[ 1 ] = cmd.data_len;
    tx_data[ 2 ] = cmd.opcode;
    
    for ( uint8_t cnt = 0; cnt < cmd.data_len; cnt++ )
    {
        tx_data[ cnt + 3 ] = cmd.data_buf[ cnt ];
    }
    
    crc = magicrfid_calculate_crc( &tx_data[ 1 ], cmd.data_len + 2 );
    
    tx_data[ cmd.data_len + 3 ] = ( uint8_t ) ( ( crc >> 8 ) & 0xFF );
    tx_data[ cmd.data_len + 4 ] = ( uint8_t ) ( crc & 0xFF );
    
    uart_write( &ctx->uart, tx_data, cmd.data_len + 5 );
    Delay_10ms ( );
}

err_t magicrfid_get_response ( magicrfid_t *ctx, magicrfid_response_t *rsp )
{
    uint8_t rx_data[ MAGICRFID_RX_DRV_BUFFER_SIZE ] = { 0 };
    uint16_t crc = 0;
    uint16_t timeout_cnt = 0;
    if ( NULL == rsp )
    {
        return MAGICRFID_ERROR;
    }
    memset ( rsp->data_buf, 0, MAGICRFID_RESPONSE_MAX_DATA_LEN );
    
    while ( ( 1 != magicrfid_generic_read( ctx, rx_data, 1 ) ) && 
            ( MAGICRFID_HEADER != rx_data[ 0 ] ) )
    {
        if ( ++timeout_cnt > MAGICRFID_TIMEOUT_MS )
        {
            return MAGICRFID_ERROR;
        }
        Delay_1ms ( );
    }
    Delay_1ms ( );
    if ( 4 != magicrfid_generic_read( ctx, &rx_data[ 1 ], 4 ) )
    {
        return MAGICRFID_ERROR;
    }
    Delay_10ms ( );
    if ( ( rx_data[ 1 ] + 2 ) != magicrfid_generic_read( ctx, &rx_data[ 5 ], rx_data[ 1 ] + 2 ) )
    {
        return MAGICRFID_ERROR;
    }

    crc = ( ( uint16_t ) rx_data[ rx_data[ 1 ] + 5 ] << 8 ) | rx_data[ rx_data[ 1 ] + 6 ];
    
    if ( crc != magicrfid_calculate_crc( &rx_data[ 1 ], rx_data[ 1 ] + 4 ) )
    {
        return MAGICRFID_ERROR;
    }
    rsp->data_len = rx_data[ 1 ];
    rsp->opcode = rx_data[ 2 ];
    rsp->status = ( ( uint16_t ) rx_data[ 3 ] << 8 ) | rx_data[ 4 ];
    memcpy ( rsp->data_buf, &rx_data[ 5 ], rsp->data_len );
    return MAGICRFID_OK;
}

int8_t magicrfid_parse_tag_rssi ( magicrfid_response_t rsp )
{
    return ( rsp.data_buf[ 7 ] - 256 );
}

uint32_t magicrfid_parse_tag_freq ( magicrfid_response_t rsp )
{
    uint32_t tag_freq = ( ( uint32_t ) rsp.data_buf[ 9 ] << 16 ) | 
                        ( ( uint16_t ) rsp.data_buf[ 10 ] << 8 ) | 
                        rsp.data_buf[ 11 ];
    return tag_freq;
}

void magicrfid_parse_tag_epc ( magicrfid_response_t rsp, magicrfid_epc_t *epc )
{
    uint16_t emb_data_num_bits = ( ( uint16_t ) rsp.data_buf[ 19 ] << 8 ) | rsp.data_buf[ 20 ];
    uint8_t emb_data_num_bytes = ( emb_data_num_bits / 8 );
    if ( emb_data_num_bits % 8 )
    {
        emb_data_num_bytes++;
    }
    uint16_t epc_data_num_bits = ( ( uint16_t ) rsp.data_buf[ 22 + emb_data_num_bytes ] << 8 ) | 
                                 rsp.data_buf[ 23 + emb_data_num_bytes ];
    uint8_t epc_data_num_bytes = epc_data_num_bits / 8;
    if ( epc_data_num_bits % 8 )
    {
        epc_data_num_bytes++;
    }
    if ( epc && ( epc_data_num_bytes <= MAGICRFID_EPC_MAX_DATA_LEN ) )
    {
        epc->data_len = epc_data_num_bytes - 4;
        epc->epc_pc = ( ( uint16_t ) rsp.data_buf[ 24 + emb_data_num_bytes ] << 8 ) | 
                      rsp.data_buf[ 25 + emb_data_num_bytes ];
        memcpy ( epc->data_buf, &rsp.data_buf[ 26 + emb_data_num_bytes ], epc->data_len );
        epc->epc_crc = ( ( uint16_t ) rsp.data_buf[ 22 + emb_data_num_bytes + epc_data_num_bytes ] << 8 ) | 
                      rsp.data_buf[ 23 + emb_data_num_bytes + epc_data_num_bytes ];
    }
}

void magicrfid_set_tag_protocol ( magicrfid_t *ctx, uint8_t protocol )
{
    magicrfid_command_t cmd;
    cmd.opcode = MAGICRFID_OPCODE_SET_TAG_PROTOCOL;
    cmd.data_len = 2;
    cmd.data_buf[ 0 ] = 0;
    cmd.data_buf[ 1 ] = protocol;
    magicrfid_send_command( ctx, cmd );
}

void magicrfid_set_region ( magicrfid_t *ctx, uint8_t region )
{
    magicrfid_command_t cmd;
    cmd.opcode = MAGICRFID_OPCODE_SET_REGION;
    cmd.data_len = 1;
    cmd.data_buf[ 0 ] = region;
    magicrfid_send_command( ctx, cmd );
}

void magicrfid_set_antenna_port ( magicrfid_t *ctx )
{
    magicrfid_command_t cmd;
    cmd.opcode = MAGICRFID_OPCODE_SET_ANTENNA_PORT;
    cmd.data_len = 2;
    cmd.data_buf[ 0 ] = 0x01;
    cmd.data_buf[ 1 ] = 0x01;
    magicrfid_send_command( ctx, cmd );
}

void magicrfid_set_baud_rate ( magicrfid_t *ctx, uint32_t baud_rate )
{
    magicrfid_command_t cmd;
    cmd.opcode = MAGICRFID_OPCODE_SET_BAUD_RATE;
    cmd.data_len = 4;
    cmd.data_buf[ 0 ] = ( uint8_t ) ( ( baud_rate >> 24 ) & 0xFF );
    cmd.data_buf[ 1 ] = ( uint8_t ) ( ( baud_rate >> 16 ) & 0xFF );
    cmd.data_buf[ 2 ] = ( uint8_t ) ( ( baud_rate >> 8 ) & 0xFF );
    cmd.data_buf[ 3 ] = ( uint8_t ) ( baud_rate & 0xFF );
    magicrfid_send_command( ctx, cmd );
}

void magicrfid_set_read_power ( magicrfid_t *ctx, uint16_t power_setting )
{
    if ( power_setting > 2700 )
    {
        power_setting = 2700;
    }
    magicrfid_command_t cmd;
    cmd.opcode = MAGICRFID_OPCODE_SET_READ_TX_POWER;
    cmd.data_len = 2;
    cmd.data_buf[ 0 ] = ( uint8_t ) ( ( power_setting >> 8 ) & 0xFF );
    cmd.data_buf[ 1 ] = ( uint8_t ) ( power_setting & 0xFF );
    magicrfid_send_command( ctx, cmd );
}

void magicrfid_set_write_power ( magicrfid_t *ctx, uint16_t power_setting )
{
    if ( power_setting > 2700 )
    {
        power_setting = 2700;
    }
    magicrfid_command_t cmd;
    cmd.opcode = MAGICRFID_OPCODE_SET_WRITE_TX_POWER;
    cmd.data_len = 2;
    cmd.data_buf[ 0 ] = ( uint8_t ) ( ( power_setting >> 8 ) & 0xFF );
    cmd.data_buf[ 1 ] = ( uint8_t ) ( power_setting & 0xFF );
    magicrfid_send_command( ctx, cmd );
}

void magicrfid_set_reader_config ( magicrfid_t *ctx, uint8_t option1, uint8_t option2 )
{
    magicrfid_command_t cmd;
    cmd.opcode = MAGICRFID_OPCODE_SET_READER_OPTIONAL_PARAMS;
    cmd.data_len = 3;
    cmd.data_buf[ 0 ] = 1;
    cmd.data_buf[ 1 ] = option1;
    cmd.data_buf[ 2 ] = option2;
    magicrfid_send_command( ctx, cmd );
}

void magicrfid_start_reading ( magicrfid_t *ctx )
{
    magicrfid_command_t cmd;
    cmd.opcode = MAGICRFID_OPCODE_MULTI_PROTOCOL_TAG_OP;
    cmd.data_len = 16;
    cmd.data_buf[ 0 ] = 0x00;
    cmd.data_buf[ 1 ] = 0x00;
    cmd.data_buf[ 2 ] = 0x01;
    cmd.data_buf[ 3 ] = 0x22;
    cmd.data_buf[ 4 ] = 0x00;
    cmd.data_buf[ 5 ] = 0x00;
    cmd.data_buf[ 6 ] = 0x05;
    cmd.data_buf[ 7 ] = 0x07;
    cmd.data_buf[ 8 ] = 0x22;
    cmd.data_buf[ 9 ] = 0x10;
    cmd.data_buf[ 10 ] = 0x00;
    cmd.data_buf[ 11 ] = 0x1B;
    cmd.data_buf[ 12 ] = 0x03;
    cmd.data_buf[ 13 ] = 0xE8;
    cmd.data_buf[ 14 ] = 0x01;
    cmd.data_buf[ 15 ] = 0xFF;
    magicrfid_send_command( ctx, cmd );
}

void magicrfid_clear_buffers ( magicrfid_t *ctx )
{
    uart_clear ( &ctx->uart );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static uint16_t magicrfid_calculate_crc ( uint8_t *data_buf, uint8_t len )
{
    uint16_t crc = 0xFFFF;
    
    for ( uint8_t n_cnt = 0; n_cnt < len; n_cnt++ )
    {
        crc = ( ( crc << 4 ) | ( data_buf[ n_cnt ] >> 4 ) ) ^ magicrfid_crc_table[ crc >> 12 ];
        crc = ( ( crc << 4 ) | ( data_buf[ n_cnt ] & 0x0F ) ) ^ magicrfid_crc_table[ crc >> 12 ];
    }
    
    return crc;
}

static void magicrfid_delay_com ( uint16_t time_ms ) 
{
    for ( uint16_t cnt = 0; cnt < time_ms; cnt++ ) 
    {
        Delay_1ms( );
    }
}

static void magicrfid_reset_delay( void ) 
{
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
