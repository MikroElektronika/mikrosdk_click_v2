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
 * @file bt122a.c
 * @brief BT122-A Click Driver.
 */

#include "bt122a.h"

void bt122a_cfg_setup ( bt122a_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t bt122a_init ( bt122a_t *ctx, bt122a_cfg_t *cfg ) 
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
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->cts );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );

    bt122a_reset_device ( ctx );

    return UART_SUCCESS;
}

err_t bt122a_generic_write ( bt122a_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t bt122a_generic_read ( bt122a_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void bt122a_set_rst_pin ( bt122a_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void bt122a_reset_device ( bt122a_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
}

void bt122a_set_cts_pin ( bt122a_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

uint8_t bt122a_get_rts_pin ( bt122a_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

void bt122a_send_package ( bt122a_t *ctx, bt122a_package_t pkg ) 
{
    uint8_t tx_buf[ BT122A_MAX_PAYLOAD_LEN + 4 ] = { 0 };

    if ( pkg.payload_len > BT122A_MAX_PAYLOAD_LEN )
    {
        pkg.payload_len = BT122A_MAX_PAYLOAD_LEN;
    }
    
    tx_buf[ 0 ] = pkg.msg_type;
    tx_buf[ 1 ] = pkg.payload_len;
    tx_buf[ 2 ] = pkg.msg_class;
    tx_buf[ 3 ] = pkg.msg_id;
    memcpy ( &tx_buf[ 4 ], pkg.payload, pkg.payload_len );
    
    uart_clear ( &ctx->uart );
    uart_write( &ctx->uart, tx_buf, pkg.payload_len + 4 );
    Delay_10ms( );
}

err_t bt122a_read_package ( bt122a_t *ctx, bt122a_package_t *pkg )
{
    uint32_t timeout_cnt = 0;
    pkg->msg_type = 0;
    
    while ( ( pkg->msg_type != BT122A_MSG_TYPE_COMMAND ) && 
            ( pkg->msg_type != BT122A_MSG_TYPE_EVENT ) )
    {
        if ( 1 == uart_read( &ctx->uart, &pkg->msg_type, 1 ) )
        {
            timeout_cnt = 0;
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= BT122A_RSP_TIMEOUT_1000MS )
        {
            return BT122A_ERROR;
        }
    }
    Delay_10ms( );
    
    if ( 1 != uart_read( &ctx->uart, &pkg->payload_len, 1 ) )
    {
        return BT122A_ERROR;
    }
    
    if ( 1 != uart_read( &ctx->uart, &pkg->msg_class, 1 ) )
    {
        return BT122A_ERROR;
    }
    
    if ( 1 != uart_read( &ctx->uart, &pkg->msg_id, 1 ) )
    {
        return BT122A_ERROR;
    }
    
    if ( pkg->payload_len != uart_read( &ctx->uart, pkg->payload, pkg->payload_len ) )
    {
        return BT122A_ERROR;
    }
    
    return BT122A_OK;
}

err_t bt122a_set_local_name ( bt122a_t *ctx, uint8_t *name )
{
    bt122a_package_t pkg;

    if ( strlen( name ) > 30 || strlen( name ) < 1 )
    {
        return BT122A_ERROR;
    }
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = strlen( name ) + 1;
    pkg.msg_class = BT122A_MSG_CLASS_SYSTEM;
    pkg.msg_id = BT122A_MSG_ID_SYSTEM_SET_LOCAL_NAME;
    pkg.payload[ 0 ] = strlen( name );
    strcpy( &pkg.payload[ 1 ], name );
    
    bt122a_send_package ( ctx, pkg );
    
    if ( BT122A_ERROR == bt122a_read_package ( ctx, &pkg ) )
    {
        return BT122A_ERROR;
    }
    
    if ( ( 0 == pkg.payload[ 0 ] ) && ( 0 == pkg.payload[ 1 ] ) )
    {
        return BT122A_OK;
    }
    
    return BT122A_ERROR;
}

err_t bt122a_set_bondable_mode ( bt122a_t *ctx, uint8_t mode )
{
    bt122a_package_t pkg;

    if ( mode > BT122A_SM_SET_BONDABLE_ALLOWED )
    {
        return BT122A_ERROR;
    }
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = 1;
    pkg.msg_class = BT122A_MSG_CLASS_SM;
    pkg.msg_id = BT122A_MSG_ID_SM_SET_BONDABLE_MODE;
    pkg.payload[ 0 ] = mode;
    
    bt122a_send_package ( ctx, pkg );
    
    if ( BT122A_ERROR == bt122a_read_package ( ctx, &pkg ) )
    {
        return BT122A_ERROR;
    }
    
    if ( ( 0 == pkg.payload[ 0 ] ) && ( 0 == pkg.payload[ 1 ] ) )
    {
        return BT122A_OK;
    }
    
    return BT122A_ERROR;
}

err_t bt122a_delete_bondings ( bt122a_t *ctx )
{    
    bt122a_package_t pkg;
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = 0;
    pkg.msg_class = BT122A_MSG_CLASS_SM;
    pkg.msg_id = BT122A_MSG_ID_SM_DELETE_BONDINGS;
    
    bt122a_send_package ( ctx, pkg );
    
    if ( BT122A_ERROR == bt122a_read_package ( ctx, &pkg ) )
    {
        return BT122A_ERROR;
    }
    
    if ( ( 0 == pkg.payload[ 0 ] ) && ( 0 == pkg.payload[ 1 ] ) )
    {
        return BT122A_OK;
    }
    
    return BT122A_ERROR;
}

err_t bt122a_set_class_of_device ( bt122a_t *ctx, uint32_t cod )
{    
    bt122a_package_t pkg;
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = 4;
    pkg.msg_class = BT122A_MSG_CLASS_SYSTEM;
    pkg.msg_id = BT122A_MSG_ID_SYSTEM_SET_CLASS_OF_DEV;
    pkg.payload[ 3 ] = ( uint8_t ) ( ( cod >> 24 ) & 0xFF );
    pkg.payload[ 2 ] = ( uint8_t ) ( ( cod >> 16 ) & 0xFF );
    pkg.payload[ 1 ] = ( uint8_t ) ( ( cod >> 8 ) & 0xFF );
    pkg.payload[ 0 ] = ( uint8_t ) ( cod & 0xFF );
    
    bt122a_send_package ( ctx, pkg );
    
    if ( BT122A_ERROR == bt122a_read_package ( ctx, &pkg ) )
    {
        return BT122A_ERROR;
    }
    
    if ( ( 0 == pkg.payload[ 0 ] ) && ( 0 == pkg.payload[ 1 ] ) )
    {
        return BT122A_OK;
    }
    
    return BT122A_ERROR;
}

err_t bt122a_set_gap_mode ( bt122a_t *ctx, uint8_t connectable, uint8_t discoverable, uint8_t limited )
{    
    bt122a_package_t pkg;
    
    if ( ( connectable > BT122A_GAP_MODE_CONNECTABLE ) || 
         ( discoverable > BT122A_GAP_MODE_DISCOVERABLE ) || 
         ( limited > BT122A_GAP_MODE_NOT_LIMITED ) )
    {
        return BT122A_ERROR;
    }
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = 3;
    pkg.msg_class = BT122A_MSG_CLASS_GAP;
    pkg.msg_id = BT122A_MSG_ID_GAP_SET_MODE;
    pkg.payload[ 0 ] = connectable;
    pkg.payload[ 1 ] = discoverable;
    pkg.payload[ 2 ] = limited;
    
    bt122a_send_package ( ctx, pkg );
    
    if ( BT122A_ERROR == bt122a_read_package ( ctx, &pkg ) )
    {
        return BT122A_ERROR;
    }
    
    if ( ( 0 == pkg.payload[ 0 ] ) && ( 0 == pkg.payload[ 1 ] ) )
    {
        return BT122A_OK;
    }
    
    return BT122A_ERROR;
}

err_t bt122a_rfcomm_start_server ( bt122a_t *ctx, uint8_t sdp_id, uint8_t stream_dest )
{    
    bt122a_package_t pkg;
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = 2;
    pkg.msg_class = BT122A_MSG_CLASS_RFCOMM;
    pkg.msg_id = BT122A_MSG_ID_RFCOMM_START_SERVER;
    pkg.payload[ 0 ] = sdp_id;
    pkg.payload[ 1 ] = stream_dest;
    
    bt122a_send_package ( ctx, pkg );
    
    if ( BT122A_ERROR == bt122a_read_package ( ctx, &pkg ) )
    {
        return BT122A_ERROR;
    }
    
    if ( ( 0 == pkg.payload[ 0 ] ) && ( 0 == pkg.payload[ 1 ] ) )
    {
        return BT122A_OK;
    }
    
    return BT122A_ERROR;
}

err_t bt122a_rfcomm_stop_server ( bt122a_t *ctx, uint8_t sdp_id )
{    
    bt122a_package_t pkg;
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = 1;
    pkg.msg_class = BT122A_MSG_CLASS_RFCOMM;
    pkg.msg_id = BT122A_MSG_ID_RFCOMM_STOP_SERVER;
    pkg.payload[ 0 ] = sdp_id;
    
    bt122a_send_package ( ctx, pkg );
    
    if ( BT122A_ERROR == bt122a_read_package ( ctx, &pkg ) )
    {
        return BT122A_ERROR;
    }
    
    if ( ( 0 == pkg.payload[ 0 ] ) && ( 0 == pkg.payload[ 1 ] ) )
    {
        return BT122A_OK;
    }
    
    return BT122A_ERROR;
}

err_t bt122a_factory_reset ( bt122a_t *ctx )
{    
    bt122a_package_t pkg;
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = 0;
    pkg.msg_class = BT122A_MSG_CLASS_SYSTEM;
    pkg.msg_id = BT122A_MSG_ID_SYSTEM_FACTORY_RESET;
    
    bt122a_send_package ( ctx, pkg );
    
    if ( BT122A_ERROR == bt122a_read_package ( ctx, &pkg ) )
    {
        return BT122A_ERROR;
    }
    
    if ( ( 0 == pkg.payload[ 0 ] ) && ( 0 == pkg.payload[ 1 ] ) )
    {
        return BT122A_OK;
    }
    
    return BT122A_ERROR;
}

err_t bt122a_system_reset ( bt122a_t *ctx, uint8_t mode )
{    
    if ( mode > BT122A_SYSTEM_RESET_BOOT_TO_DFU )
    {
        return BT122A_ERROR;
    }
    
    bt122a_package_t pkg;
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = 1;
    pkg.msg_class = BT122A_MSG_CLASS_SYSTEM;
    pkg.msg_id = BT122A_MSG_ID_SYSTEM_RESET;
    pkg.payload[ 0 ] = mode;
    
    bt122a_send_package ( ctx, pkg );
    
    return BT122A_OK;
}

err_t bt122a_endpoint_send_data ( bt122a_t *ctx, uint8_t *endpoint, uint8_t *msg )
{    
    bt122a_package_t pkg;
    
    pkg.msg_type = BT122A_MSG_TYPE_COMMAND;
    pkg.payload_len = strlen( msg ) + 2;
    pkg.msg_class = BT122A_MSG_CLASS_ENDPOINT;
    pkg.msg_id = BT122A_MSG_ID_ENDPOINT_SEND_DATA;
    pkg.payload[ 0 ] = *endpoint;
    pkg.payload[ 1 ] = strlen( msg );
    strcpy( &pkg.payload[ 2 ], msg );
    
    bt122a_send_package ( ctx, pkg );
    
    if ( BT122A_ERROR == bt122a_read_package ( ctx, &pkg ) )
    {
        return BT122A_ERROR;
    }
    
    if ( ( 0 == pkg.payload[ 0 ] ) && ( 0 == pkg.payload[ 1 ] ) )
    {
        *endpoint = pkg.payload[ 2 ];
        return BT122A_OK;
    }
    
    return BT122A_ERROR;
}

// ------------------------------------------------------------------------- END
