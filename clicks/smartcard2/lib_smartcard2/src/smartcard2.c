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
 * @file smartcard2.c
 * @brief Smart Card 2 Click Driver.
 */

#include "smartcard2.h"

/**
 * @brief Smart Card 2 calculate checksum function.
 * @details This function calculates checksum of the data input buffer.
 * @param[in] data_in : Data buffer to calculate checksum from.
 * @param[in] data_len : Number of data bytes for checksum calculation.
 * @return Calculated checksum.
 * @note None.
 */
static uint8_t smartcard2_calculate_checksum ( uint8_t *data_in, uint16_t data_len );

void smartcard2_cfg_setup ( smartcard2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t smartcard2_init ( smartcard2_t *ctx, smartcard2_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rst, cfg->rst );
    smartcard2_disable_device ( ctx );
    Delay_100ms ( );
    smartcard2_enable_device ( ctx );
    Delay_100ms ( );

    // perform dummy read in order to enable uart RX interrupt
    uint8_t dummy;
    smartcard2_generic_read( ctx, &dummy, 1 );
    
    ctx->seq_num = 0;
    return UART_SUCCESS;
}

err_t smartcard2_generic_write ( smartcard2_t *ctx, char *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t smartcard2_generic_read ( smartcard2_t *ctx, char *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void smartcard2_enable_device ( smartcard2_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void smartcard2_disable_device ( smartcard2_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

err_t smartcard2_send_ccid ( smartcard2_t *ctx, smartcard2_ccid_t *ccid )
{
    if ( NULL == ccid )
    {
        return SMARTCARD2_ERROR;
    }
    uint8_t data_buf[ SMARTCARD2_MAX_BUF_SIZE ] = { 0 };
    data_buf[ 0 ] = SMARTCARD2_SYNC;
    data_buf[ 1 ] = SMARTCARD2_CTRL_ACK;
    data_buf[ 2 ] = ccid->type;
    data_buf[ 3 ] = ( uint8_t ) ( ccid->payload_size & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( ccid->payload_size >> 8 ) & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( ccid->payload_size >> 16 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( ( ccid->payload_size >> 24 ) & 0xFF );
    data_buf[ 7 ] = ccid->slot_num;
    data_buf[ 8 ] = ccid->seq_num;
    ctx->seq_num = ccid->seq_num;
    memcpy( &data_buf[ 9 ], ccid->spec_bytes, 3 );
    if ( ccid->payload_size )
    {
        memcpy( &data_buf[ 12 ], ccid->payload, ccid->payload_size );
    }
    data_buf[ ccid->payload_size + 12 ] = smartcard2_calculate_checksum ( data_buf, ccid->payload_size + 12 );
    smartcard2_generic_write( ctx, data_buf, ccid->payload_size + 13 );
    Delay_10ms ( );
    return SMARTCARD2_OK;
}

err_t smartcard2_read_ccid ( smartcard2_t *ctx, smartcard2_ccid_t *ccid )
{
    if ( NULL == ccid )
    {
        return SMARTCARD2_ERROR;
    }
    err_t error_flag = SMARTCARD2_OK;
    uint8_t data_buf[ SMARTCARD2_MAX_BUF_SIZE ] = { 0 };
    uint16_t data_buf_len = 0;
    uint16_t timeout_cnt = 0;
    uint32_t payload_size = 0;
    
    // Read the first byte of message (event or sync byte)
    while ( SMARTCARD2_OK == error_flag )
    {
        if ( ( 1 == smartcard2_generic_read( ctx, data_buf, 1 ) ) && 
             ( ( SMARTCARD2_EVT_NOTIFY_SLOT_CHANGE == data_buf[ data_buf_len ] ) || 
               ( SMARTCARD2_EVT_HARDWARE_ERROR == data_buf[ data_buf_len ] ) || 
               ( SMARTCARD2_SYNC == data_buf[ data_buf_len ] ) ))
        {
            data_buf_len++;
            break;
        }
        if ( ++timeout_cnt > SMARTCARD2_TIMEOUT_MS )
        {
            error_flag = SMARTCARD2_TIMEOUT_ERROR;
        }
        Delay_1ms( );
    }
    Delay_10ms( );
    timeout_cnt = 0;
    
    if ( SMARTCARD2_OK == error_flag )
    {
        if ( SMARTCARD2_EVT_HARDWARE_ERROR == data_buf[ 0 ] )
        {
            // Read 3 bytes of hw error event message
            if ( 3 == smartcard2_generic_read( ctx, &data_buf[ data_buf_len ], 3 ) )
            {
                data_buf_len += 3;
            }
            else
            {
                error_flag = SMARTCARD2_READ_ERROR;
            }
        }
        else
        {
            // Read the second byte of message (event or ack/nack byte)
            if ( 1 == smartcard2_generic_read( ctx, &data_buf[ data_buf_len ], 1 ) )
            {
                data_buf_len++;
            }
            else
            {
                error_flag = SMARTCARD2_READ_ERROR;
            }
        }
    }
         
    // Check if it's a response message
    if ( ( SMARTCARD2_OK == error_flag ) && ( SMARTCARD2_SYNC == data_buf[ 0 ] ) )
    {
        // Check the response acknowledge
        if ( SMARTCARD2_CTRL_ACK == data_buf[ 1 ] )
        {
            // Read 10-bytes header
            // a message type (1 byte), a length field (four bytes), the slot number (1 byte), 
            // a sequence number field (1 byte), and either three message specific bytes, or
            // a status field (1 byte), an error field and one message specific byte.
            if ( 10 == smartcard2_generic_read( ctx, &data_buf[ data_buf_len ], 10 ) )
            {
                data_buf_len += 10;
                payload_size = ( ( uint32_t ) data_buf[ 6 ] << 24 ) | ( ( uint32_t ) data_buf[ 5 ] << 16 ) |
                               ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ];
                if ( payload_size > SMARTCARD2_SHORT_APDU_MAX_SIZE )
                {
                    payload_size = SMARTCARD2_SHORT_APDU_MAX_SIZE;
                }
                if ( payload_size == smartcard2_generic_read( ctx, &data_buf[ data_buf_len ], payload_size ) )
                {
                    data_buf_len += payload_size;
                }
                else
                {
                    error_flag = SMARTCARD2_READ_ERROR;
                }
            }
            else
            {
                error_flag = SMARTCARD2_READ_ERROR;
            }
        }
        
        // Read and check the checksum byte
        if ( SMARTCARD2_OK == error_flag )
        {
            if ( 1 == smartcard2_generic_read( ctx, &data_buf[ data_buf_len ], 1 ) )
            {
                data_buf_len++;
                if ( data_buf[ data_buf_len - 1 ] != smartcard2_calculate_checksum ( data_buf, data_buf_len - 1 ) )
                {
                    error_flag = SMARTCARD2_CHECKSUM_ERROR;
                }
            }
            else
            {
                error_flag = SMARTCARD2_READ_ERROR;
            }
        }
    }
    
    // If no error occured copy the message to output arguments
    if ( SMARTCARD2_OK == error_flag )
    {
        if ( SMARTCARD2_EVT_HARDWARE_ERROR == data_buf[ 0 ] )
        {
            ccid->type = data_buf[ 0 ];
            ccid->payload_size = 1;
            ccid->slot_num = data_buf[ 1 ];
            ccid->seq_num = data_buf[ 2 ];
            ccid->payload[ 0 ] = data_buf[ 3 ];
        }
        else if ( SMARTCARD2_EVT_NOTIFY_SLOT_CHANGE == data_buf[ 0 ] )
        {
            ccid->type = data_buf[ 0 ];
            ccid->payload_size = 1;
            ccid->payload[ 0 ] = data_buf[ 1 ];
        }
        else if ( ( SMARTCARD2_SYNC == data_buf[ 0 ] ) && ( SMARTCARD2_CTRL_NACK == data_buf[ 1 ] ) )
        {
            ccid->type = data_buf[ 1 ];
            ccid->payload_size = 0;
        }
        else
        {
            ccid->type = data_buf[ 2 ];
            ccid->payload_size = payload_size;
            ccid->slot_num = data_buf[ 7 ];
            ccid->seq_num = data_buf[ 8 ];
            memcpy( ccid->spec_bytes, &data_buf[ 9 ], 3 );
            if ( ccid->payload_size )
            {
                memcpy( ccid->payload, &data_buf[ 12 ], ccid->payload_size );
            }
        }
    }
    return error_flag;
}

err_t smartcard2_icc_power_on ( smartcard2_t *ctx, uint8_t power_sel )
{
    if ( power_sel > SMARTCARD2_POWER_SEL_1_8V )
    {
        return SMARTCARD2_ERROR;
    }
    smartcard2_ccid_t ccid = { 0 };
    ccid.type = SMARTCARD2_CMD_ICC_POWER_ON;
    ccid.payload_size = 0;
    ccid.slot_num = 0;
    ccid.seq_num = ++ctx->seq_num;
    ccid.spec_bytes[ 0 ] = power_sel;
    ccid.spec_bytes[ 1 ] = 0;
    ccid.spec_bytes[ 2 ] = 0;
    return smartcard2_send_ccid ( ctx, &ccid );
}

err_t smartcard2_icc_power_off ( smartcard2_t *ctx )
{
    smartcard2_ccid_t ccid = { 0 };
    ccid.type = SMARTCARD2_CMD_ICC_POWER_OFF;
    ccid.payload_size = 0;
    ccid.slot_num = 0;
    ccid.seq_num = ++ctx->seq_num;
    ccid.spec_bytes[ 0 ] = 0;
    ccid.spec_bytes[ 1 ] = 0;
    ccid.spec_bytes[ 2 ] = 0;
    return smartcard2_send_ccid ( ctx, &ccid );
}

err_t smartcard2_get_slot_status ( smartcard2_t *ctx )
{
    smartcard2_ccid_t ccid = { 0 };
    ccid.type = SMARTCARD2_CMD_GET_SLOT_STATUS;
    ccid.payload_size = 0;
    ccid.slot_num = 0;
    ccid.seq_num = ++ctx->seq_num;
    ccid.spec_bytes[ 0 ] = 0;
    ccid.spec_bytes[ 1 ] = 0;
    ccid.spec_bytes[ 2 ] = 0;
    return smartcard2_send_ccid ( ctx, &ccid );
}

static uint8_t smartcard2_calculate_checksum ( uint8_t *data_in, uint16_t data_len )
{
    uint8_t checksum = 0;
    for ( uint16_t cnt = 0; cnt < data_len; cnt++ )
    {
        checksum ^= data_in[ cnt ];
    }
    return checksum;
}

// ------------------------------------------------------------------------- END
