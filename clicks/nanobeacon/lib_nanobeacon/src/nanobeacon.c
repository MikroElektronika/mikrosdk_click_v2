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
 * @file nanobeacon.c
 * @brief NanoBeacon Click Driver.
 */

#include "nanobeacon.h"
#include "nanobeacon_adv.h"

void nanobeacon_cfg_setup ( nanobeacon_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->dq = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t nanobeacon_init ( nanobeacon_t *ctx, nanobeacon_cfg_t *cfg ) 
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
    digital_out_init( &ctx->dq, cfg->dq );
    digital_out_low ( &ctx->en );
    digital_out_low ( &ctx->dq );

    // Input pins
    digital_in_init( &ctx->an, cfg->an );

    return UART_SUCCESS;
}

err_t nanobeacon_generic_write ( nanobeacon_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t nanobeacon_generic_read ( nanobeacon_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

uint8_t nanobeacon_get_an_pin ( nanobeacon_t *ctx )
{
    return digital_in_read ( &ctx->an );
}

void nanobeacon_set_en_pin ( nanobeacon_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en, state );
}

void nanobeacon_set_dq_pin ( nanobeacon_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->dq, state );
}

void nanobeacon_restart_device ( nanobeacon_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
    digital_out_high ( &ctx->en );
    Delay_1sec ( );
}

err_t nanobeacon_send_packet ( nanobeacon_t *ctx, nanobeacon_packet_t pkt_in )
{
    uint8_t data_buf[ NANOBEACON_TX_DRV_BUFFER_SIZE ] = { 0 };
    data_buf[ 0 ] = NANOBEACON_PACKET_HEADER;
    data_buf[ 1 ] = pkt_in.opcode;
    data_buf[ 2 ] = pkt_in.payload_len;
    if ( pkt_in.payload_len )
    {
        memcpy ( &data_buf[ 3 ], pkt_in.payload, pkt_in.payload_len );
    }
    data_buf[ pkt_in.payload_len + 3 ] = NANOBEACON_PACKET_TAIL;
    uart_clear ( &ctx->uart );
    return nanobeacon_generic_write ( ctx, data_buf, pkt_in.payload_len + 4 );
}

err_t nanobeacon_read_packet ( nanobeacon_t *ctx, nanobeacon_packet_t *pkt_out )
{
    uint8_t data_buf[ NANOBEACON_RX_DRV_BUFFER_SIZE ] = { 0 };
    uint16_t timeout_cnt = 0;
    if ( NULL == pkt_out )
    {
        return NANOBEACON_ERROR;
    }
    // Read packet header
    while ( ( 1 != nanobeacon_generic_read ( ctx, data_buf, 1 ) ) && 
            ( NANOBEACON_PACKET_HEADER != data_buf[ 0 ] ) )
    {
        if ( ++timeout_cnt > NANOBEACON_TIMEOUT_MS )
        {
            return NANOBEACON_ERROR;
        }
        Delay_1ms ( );
    }
    Delay_10ms ( );
    // Read packet opcode and payload lenght
    if ( 2 != nanobeacon_generic_read ( ctx, &data_buf[ 1 ], 2 ) )
    {
        return NANOBEACON_ERROR;
    }
    // Read packet payload data
    if ( data_buf[ 2 ] )
    {
        if ( data_buf[ 2 ] != nanobeacon_generic_read ( ctx, &data_buf[ 3 ], data_buf[ 2 ] ) )
        {
            return NANOBEACON_ERROR;
        }
    }
    
    // Read and check the packet tail byte
    if ( 1 != nanobeacon_generic_read ( ctx, &data_buf[ data_buf[ 2 ] + 3 ], 1 ) )
    {
        return NANOBEACON_ERROR;
    }
    if ( NANOBEACON_PACKET_TAIL != data_buf[ data_buf[ 2 ] + 3 ] )
    {
        return NANOBEACON_ERROR;
    }
    pkt_out->opcode = data_buf[ 1 ];
    pkt_out->payload_len = data_buf[ 2 ];
    memcpy ( pkt_out->payload, &data_buf[ 3 ], pkt_out->payload_len );
    return NANOBEACON_OK;
}

err_t nanobeacon_check_communication ( nanobeacon_t *ctx )
{
    nanobeacon_packet_t command = { 0 };
    err_t error_flag = NANOBEACON_OK;
    uint8_t num_tries = 0;
    while ( num_tries < NANOBEACON_CHECK_COMM_NUM_TRIES )
    {
        command.opcode = NANOBEACON_OPCODE_READY;
        command.payload_len = 1;
        command.payload[ 0 ] = NANOBEACON_PAYLOAD_READY;
        nanobeacon_send_packet ( ctx, command );
        error_flag = nanobeacon_read_packet ( ctx, &command );
        if ( NANOBEACON_OK == error_flag )
        {
            if ( NANOBEACON_OPCODE_READY_NACK == command.opcode )
            {
                error_flag = command.payload[ 0 ];
            }
            else if ( NANOBEACON_OPCODE_READY_ACK == command.opcode )
            {
                error_flag = NANOBEACON_OK;
                break;
            }
            else
            {
                error_flag = NANOBEACON_ERROR;
            }
        }
        num_tries++;
    }
    return error_flag;
}

err_t nanobeacon_write_reg ( nanobeacon_t *ctx, uint16_t address, uint32_t data_in )
{
    uint32_t data_out = 0;
    nanobeacon_packet_t command = { 0 };
    command.opcode = NANOBEACON_OPCODE_WRITE_REG;
    command.payload_len = 6;
    command.payload[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    command.payload[ 1 ] = ( uint8_t ) ( address & 0xFF );
    command.payload[ 2 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    command.payload[ 3 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    command.payload[ 4 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    command.payload[ 5 ] = ( uint8_t ) ( data_in & 0xFF );
    nanobeacon_send_packet ( ctx, command );
    err_t error_flag = nanobeacon_read_packet ( ctx, &command );
    if ( NANOBEACON_OK == error_flag )
    {
        if ( NANOBEACON_OPCODE_WRITE_REG_RESP == command.opcode )
        {
            data_out = ( ( uint32_t ) command.payload[ 0 ] << 24 ) | 
                       ( ( uint32_t ) command.payload[ 1 ] << 16 ) | 
                       ( ( uint16_t ) command.payload[ 2 ] << 8 ) | 
                       command.payload[ 3 ];
            if ( data_out != data_in )
            {
                error_flag = NANOBEACON_ERROR;
            }
        }
        else
        {
            error_flag = NANOBEACON_ERROR;
        }
    }
    return error_flag;
}

err_t nanobeacon_read_reg ( nanobeacon_t *ctx, uint16_t address, uint32_t *data_out )
{
    nanobeacon_packet_t command = { 0 };
    command.opcode = NANOBEACON_OPCODE_READ_REG;
    command.payload_len = 2;
    command.payload[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    command.payload[ 1 ] = ( uint8_t ) ( address & 0xFF );
    nanobeacon_send_packet ( ctx, command );
    err_t error_flag = nanobeacon_read_packet ( ctx, &command );
    if ( NANOBEACON_OK == error_flag )
    {
        if ( NANOBEACON_OPCODE_READ_REG_RESP == command.opcode )
        {
            *data_out = ( ( uint32_t ) command.payload[ 0 ] << 24 ) | 
                        ( ( uint32_t ) command.payload[ 1 ] << 16 ) | 
                        ( ( uint16_t ) command.payload[ 2 ] << 8 ) | 
                        command.payload[ 3 ];
        }
        else
        {
            error_flag = NANOBEACON_ERROR;
        }
    }
    return error_flag;
}

err_t nanobeacon_write_mem ( nanobeacon_t *ctx, uint16_t address, uint32_t data_in )
{
    uint32_t data_out = 0;
    nanobeacon_packet_t command = { 0 };
    command.opcode = NANOBEACON_OPCODE_WRITE_MEM;
    command.payload_len = 6;
    command.payload[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    command.payload[ 1 ] = ( uint8_t ) ( address & 0xFF );
    command.payload[ 2 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    command.payload[ 3 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    command.payload[ 4 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    command.payload[ 5 ] = ( uint8_t ) ( data_in & 0xFF );
    nanobeacon_send_packet ( ctx, command );
    err_t error_flag = nanobeacon_read_packet ( ctx, &command );
    if ( NANOBEACON_OK == error_flag )
    {
        if ( NANOBEACON_OPCODE_WRITE_MEM_RESP == command.opcode )
        {
            data_out = ( ( uint32_t ) command.payload[ 0 ] << 24 ) | 
                       ( ( uint32_t ) command.payload[ 1 ] << 16 ) | 
                       ( ( uint16_t ) command.payload[ 2 ] << 8 ) | 
                       command.payload[ 3 ];
            if ( data_out != data_in )
            {
                error_flag = NANOBEACON_ERROR;
            }
        }
        else
        {
            error_flag = NANOBEACON_ERROR;
        }
    }
    return error_flag;
}

err_t nanobeacon_read_mem ( nanobeacon_t *ctx, uint16_t address, uint32_t *data_out )
{
    nanobeacon_packet_t command = { 0 };
    command.opcode = NANOBEACON_OPCODE_READ_MEM;
    command.payload_len = 2;
    command.payload[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    command.payload[ 1 ] = ( uint8_t ) ( address & 0xFF );
    nanobeacon_send_packet ( ctx, command );
    err_t error_flag = nanobeacon_read_packet ( ctx, &command );
    if ( NANOBEACON_OK == error_flag )
    {
        if ( NANOBEACON_OPCODE_READ_MEM_RESP == command.opcode )
        {
            *data_out = ( ( uint32_t ) command.payload[ 0 ] << 24 ) | 
                        ( ( uint32_t ) command.payload[ 1 ] << 16 ) | 
                        ( ( uint16_t ) command.payload[ 2 ] << 8 ) | 
                        command.payload[ 3 ];
        }
        else
        {
            error_flag = NANOBEACON_ERROR;
        }
    }
    return error_flag;
}

err_t nanobeacon_write_efuse ( nanobeacon_t *ctx, uint8_t aid, uint16_t data_in )
{
    uint16_t data_out = 0;
    nanobeacon_packet_t command = { 0 };
    command.opcode = NANOBEACON_OPCODE_WRITE_EFUSE;
    command.payload_len = 2;
    
    for ( uint16_t bit_cnt = 0; bit_cnt < 16; bit_cnt++ )
    {
        if ( data_in & ( 1 << bit_cnt ) )
        {
            command.payload[ 0 ] = aid;
            command.payload[ 1 ] = bit_cnt;
            nanobeacon_send_packet ( ctx, command );
        }
    }
    err_t error_flag = nanobeacon_read_efuse ( ctx, aid, &data_out );
    if ( NANOBEACON_OK == error_flag )
    {
        if ( data_out != data_in )
        {
            error_flag = NANOBEACON_ERROR;
        }
    }
    return error_flag;
}

err_t nanobeacon_read_efuse ( nanobeacon_t *ctx, uint8_t aid, uint16_t *data_out )
{
    nanobeacon_packet_t command = { 0 };
    command.opcode = NANOBEACON_OPCODE_READ_EFUSE;
    command.payload_len = 1;
    command.payload[ 0 ] = aid;
    nanobeacon_send_packet ( ctx, command );
    err_t error_flag = nanobeacon_read_packet ( ctx, &command );
    if ( NANOBEACON_OK == error_flag )
    {
        if ( NANOBEACON_OPCODE_READ_EFUSE_RESP == command.opcode )
        {
            *data_out = ( ( uint16_t ) command.payload[ 2 ] << 8 ) | command.payload[ 3 ];
        }
        else
        {
            error_flag = NANOBEACON_ERROR;
        }
    }
    return error_flag;
}

err_t nanobeacon_set_advertising ( uint8_t *mac_address, uint16_t interval, uint8_t *adv_raw_data, uint8_t len )
{
    // Reset advertising data
    nanobeacon_adv_data_reset ( );
    
    // Set advertising on channels 37,38,39, period is 1000ms
    nanobeacon_adv_tx_set ( interval, ADV_CH_37_38_39, ADV_MODE_CONTINUOUS );
    
    // Set advertising MAC address
    nanobeacon_adv_address_set ( ADDR_PUBLIC, mac_address, 60, 0 );

    // Add predefined data to advertising payload
    return nanobeacon_adv_add_data ( adv_raw_data, len, 0 );
}

err_t nanobeacon_load_adv_to_ram ( nanobeacon_t *ctx )
{
    err_t error_flag = NANOBEACON_OK;
    uint16_t mem_address = 0x0100;
    uint8_t buffer[ 96 ] = { 0 };
    uint16_t size = nanobeacon_adv_data_to_raw ( buffer );
    uint32_t value = ( ( uint16_t ) buffer[ 1 ] << 8 ) | buffer[ 0 ];
    error_flag |= nanobeacon_write_mem ( ctx, mem_address++, value );
    for ( uint16_t cnt = 2; cnt < size; cnt += 4 ) 
    {
        value = ( ( uint32_t ) buffer[ cnt + 3 ] << 24 ) | 
                ( ( uint32_t ) buffer[ cnt + 2 ] << 16 ) | 
                ( ( uint16_t ) buffer[ cnt + 1 ] << 8 ) | 
                buffer[ cnt ];
        error_flag |= nanobeacon_write_mem ( ctx, mem_address++, value );
    }
    return error_flag;
}

err_t nanobeacon_start_advertising ( nanobeacon_t *ctx )
{
    err_t error_flag = NANOBEACON_OK;
    uint32_t value = 0;
    error_flag |= nanobeacon_write_reg ( ctx, 0x3394, 0x0100 );
    error_flag |= nanobeacon_write_reg ( ctx, 0x3390, 0x0777 );
    error_flag |= nanobeacon_read_reg ( ctx, 0x10B0, &value );
    if ( NANOBEACON_OK == error_flag )
    {
        value = value | 0x10;
        value = value & 0xFFFFFFFC;
        error_flag |= nanobeacon_write_reg(ctx, 0x10B0, value);
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
