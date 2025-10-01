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
 * @file bgm113.c
 * @brief BGM113 Click Driver.
 */

#include "bgm113.h"

void bgm113_cfg_setup ( bgm113_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t bgm113_init ( bgm113_t *ctx, bgm113_cfg_t *cfg ) 
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

    return UART_SUCCESS;
}

err_t bgm113_generic_write ( bgm113_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t bgm113_generic_read ( bgm113_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void bgm113_set_rst_pin ( bgm113_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void bgm113_set_cts_pin ( bgm113_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

uint8_t bgm113_get_rts_pin ( bgm113_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

void bgm113_send_packet ( bgm113_t *ctx ) 
{
    uint8_t cmd_buf[ 4 ] = { 0 };

    if ( ctx->cmd_pkt.payload_len > BGM113_MAX_PAYLOAD_LEN )
    {
        ctx->cmd_pkt.payload_len = BGM113_MAX_PAYLOAD_LEN;
    }
    
    cmd_buf[ 0 ] = ctx->cmd_pkt.msg_type;
    cmd_buf[ 1 ] = ctx->cmd_pkt.payload_len;
    cmd_buf[ 2 ] = ctx->cmd_pkt.msg_class;
    cmd_buf[ 3 ] = ctx->cmd_pkt.msg_id;
    
    bgm113_clear_buffers ( ctx );
    bgm113_generic_write( ctx, cmd_buf, 4 );
    if ( ctx->cmd_pkt.payload_len ) 
    {
        bgm113_generic_write ( ctx, ctx->cmd_pkt.payload, ctx->cmd_pkt.payload_len );
    }  
    Delay_10ms( );
}

err_t bgm113_read_packet ( bgm113_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t rsp_buf[ 4 ] = { 0 };
    
    while ( ( BGM113_MSG_TYPE_RESPONSE != rsp_buf[ 0 ] ) && 
            ( BGM113_MSG_TYPE_EVENT != rsp_buf[ 0 ] ) )
    {
        if ( 1 == bgm113_generic_read( ctx, rsp_buf, 1 ) )
        {
            timeout_cnt = 0;
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= BGM113_RSP_TIMEOUT_1000MS )
        {
            return BGM113_ERROR;
        }
    }
    Delay_10ms( );
    
    if ( 3 != bgm113_generic_read( ctx, &rsp_buf[ 1 ], 3 ) )
    {
        return BGM113_ERROR;
    }

    ctx->rsp_pkt.msg_type = rsp_buf[ 0 ];
    ctx->rsp_pkt.payload_len = rsp_buf[ 1 ];
    ctx->rsp_pkt.msg_class = rsp_buf[ 2 ];
    ctx->rsp_pkt.msg_id = rsp_buf[ 3 ];

    if ( ctx->rsp_pkt.payload_len > BGM113_MAX_PAYLOAD_LEN )
    {
        return BGM113_ERROR;
    }

    if ( ctx->rsp_pkt.payload_len )
    {
        if ( ctx->rsp_pkt.payload_len != bgm113_generic_read( ctx, ctx->rsp_pkt.payload, ctx->rsp_pkt.payload_len ) )
        {
            return BGM113_ERROR;
        }
    }

    return BGM113_OK;
}

err_t bgm113_wait_packet ( bgm113_t *ctx, uint8_t msg_type, uint8_t msg_class, uint8_t msg_id, uint8_t max_time_s )
{
    uint8_t cnt = 0;
    while ( cnt < max_time_s )
    {
        if ( BGM113_ERROR == bgm113_read_packet ( ctx ) )
        {
            cnt++;
        }
        if ( ( ctx->rsp_pkt.msg_type == msg_type ) &&
             ( ctx->rsp_pkt.msg_class == msg_class ) &&
             ( ctx->rsp_pkt.msg_id == msg_id ) )
        {
            return BGM113_OK;
        }
    } 
    return BGM113_ERROR;
}

void bgm113_clear_buffers ( bgm113_t *ctx )
{
    uart_clear ( &ctx->uart );
    ctx->rsp_pkt.msg_type = 0;
    ctx->rsp_pkt.payload_len = 0;
    ctx->rsp_pkt.msg_class = 0;
    ctx->rsp_pkt.msg_id = 0;
    memset ( ctx->rsp_pkt.payload, 0, BGM113_MAX_PAYLOAD_LEN );
}

err_t bgm113_reset_device ( bgm113_t *ctx )
{
    bgm113_clear_buffers ( ctx );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    if ( BGM113_OK == bgm113_wait_packet ( ctx, BGM113_MSG_TYPE_EVENT, BGM113_MSG_CLASS_SYSTEM, 
                                                BGM113_MSG_ID_EVT_SYSTEM_BOOT, BGM113_WAIT_TIME_5S ) )
    {
        return BGM113_OK;
    }
    return BGM113_ERROR;
}

err_t bgm113_check_communication ( bgm113_t *ctx )
{    
    ctx->cmd_pkt.msg_type = BGM113_MSG_TYPE_COMMAND;
    ctx->cmd_pkt.payload_len = 0;
    ctx->cmd_pkt.msg_class = BGM113_MSG_CLASS_SYSTEM;
    ctx->cmd_pkt.msg_id = BGM113_MSG_ID_SYSTEM_HELLO;
    
    bgm113_send_packet ( ctx );

    if ( BGM113_OK == bgm113_wait_packet ( ctx, BGM113_MSG_TYPE_RESPONSE, BGM113_MSG_CLASS_SYSTEM, 
                                                BGM113_MSG_ID_SYSTEM_HELLO, BGM113_WAIT_TIME_1S ) )
    {
        if ( ( 0 == ctx->rsp_pkt.payload[ 0 ] ) && ( 0 == ctx->rsp_pkt.payload[ 1 ] ) )
        {
            return BGM113_OK;
        }
    }
    
    return BGM113_ERROR;
}

err_t bgm113_get_bt_address ( bgm113_t *ctx )
{
    ctx->cmd_pkt.msg_type = BGM113_MSG_TYPE_COMMAND;
    ctx->cmd_pkt.payload_len = 0;
    ctx->cmd_pkt.msg_class = BGM113_MSG_CLASS_SYSTEM;
    ctx->cmd_pkt.msg_id = BGM113_MSG_ID_SYSTEM_GET_BT_ADDRESS;
    
    bgm113_send_packet ( ctx );
    
    if ( BGM113_OK == bgm113_wait_packet ( ctx, BGM113_MSG_TYPE_RESPONSE, BGM113_MSG_CLASS_SYSTEM, 
                                                BGM113_MSG_ID_SYSTEM_GET_BT_ADDRESS, BGM113_WAIT_TIME_1S ) )
    {
        if ( 6 == ctx->rsp_pkt.payload_len )
        {
            return BGM113_OK;
        }
    }
    
    return BGM113_ERROR;
}

err_t bgm113_set_bondable_mode ( bgm113_t *ctx, uint8_t mode )
{
    if ( mode > BGM113_SM_SET_BONDABLE_ALLOWED )
    {
        return BGM113_ERROR;
    }
    
    ctx->cmd_pkt.msg_type = BGM113_MSG_TYPE_COMMAND;
    ctx->cmd_pkt.payload_len = 1;
    ctx->cmd_pkt.msg_class = BGM113_MSG_CLASS_SM;
    ctx->cmd_pkt.msg_id = BGM113_MSG_ID_SM_SET_BONDABLE_MODE;
    ctx->cmd_pkt.payload[ 0 ] = mode;
    
    bgm113_send_packet ( ctx );

    if ( BGM113_OK == bgm113_wait_packet ( ctx, BGM113_MSG_TYPE_RESPONSE, BGM113_MSG_CLASS_SM, 
                                                BGM113_MSG_ID_SM_SET_BONDABLE_MODE, BGM113_WAIT_TIME_1S ) )
    {
        if ( ( 0 == ctx->rsp_pkt.payload[ 0 ] ) && ( 0 == ctx->rsp_pkt.payload[ 1 ] ) )
        {
            return BGM113_OK;
        }
    }
    
    return BGM113_ERROR;
}

err_t bgm113_delete_bondings ( bgm113_t *ctx )
{    
    ctx->cmd_pkt.msg_type = BGM113_MSG_TYPE_COMMAND;
    ctx->cmd_pkt.payload_len = 0;
    ctx->cmd_pkt.msg_class = BGM113_MSG_CLASS_SM;
    ctx->cmd_pkt.msg_id = BGM113_MSG_ID_SM_DELETE_BONDINGS;
    
    bgm113_send_packet ( ctx );

    if ( BGM113_OK == bgm113_wait_packet ( ctx, BGM113_MSG_TYPE_RESPONSE, BGM113_MSG_CLASS_SM, 
                                                BGM113_MSG_ID_SM_DELETE_BONDINGS, BGM113_WAIT_TIME_1S ) )
    {
        if ( ( 0 == ctx->rsp_pkt.payload[ 0 ] ) && ( 0 == ctx->rsp_pkt.payload[ 1 ] ) )
        {
            return BGM113_OK;
        }
    }
    
    return BGM113_ERROR;
}

err_t bgm113_set_gap_mode ( bgm113_t *ctx, uint8_t connectable, uint8_t discoverable )
{    
    if ( ( connectable > BGM113_LE_GAP_SCANNABLE_NON_CONNECTABLE ) || 
         ( discoverable > BGM113_LE_GAP_USER_DATA ) )
    {
        return BGM113_ERROR;
    }
    
    ctx->cmd_pkt.msg_type = BGM113_MSG_TYPE_COMMAND;
    ctx->cmd_pkt.payload_len = 2;
    ctx->cmd_pkt.msg_class = BGM113_MSG_CLASS_LE_GAP;
    ctx->cmd_pkt.msg_id = BGM113_MSG_ID_LE_GAP_SET_MODE;
    ctx->cmd_pkt.payload[ 0 ] = discoverable;
    ctx->cmd_pkt.payload[ 1 ] = connectable;
    
    bgm113_send_packet ( ctx );

    if ( BGM113_OK == bgm113_wait_packet ( ctx, BGM113_MSG_TYPE_RESPONSE, BGM113_MSG_CLASS_LE_GAP, 
                                                BGM113_MSG_ID_LE_GAP_SET_MODE, BGM113_WAIT_TIME_1S ) )
    {
        if ( ( 0 == ctx->rsp_pkt.payload[ 0 ] ) && ( 0 == ctx->rsp_pkt.payload[ 1 ] ) )
        {
            return BGM113_OK;
        }
    }
    
    return BGM113_ERROR;
}

err_t bgm113_system_reset ( bgm113_t *ctx, uint8_t mode )
{
    if ( mode > BGM113_SYSTEM_RESET_BOOT_TO_DFU )
    {
        return BGM113_ERROR;
    }
    
    ctx->cmd_pkt.msg_type = BGM113_MSG_TYPE_COMMAND;
    ctx->cmd_pkt.payload_len = 1;
    ctx->cmd_pkt.msg_class = BGM113_MSG_CLASS_SYSTEM;
    ctx->cmd_pkt.msg_id = BGM113_MSG_ID_SYSTEM_RESET;
    ctx->cmd_pkt.payload[ 0 ] = mode;
    
    if ( BGM113_SYSTEM_RESET_NORMAL == mode )
    {
        if ( BGM113_OK == bgm113_wait_packet ( ctx, BGM113_MSG_TYPE_EVENT, BGM113_MSG_CLASS_SYSTEM, 
                                                    BGM113_MSG_ID_EVT_SYSTEM_BOOT, BGM113_WAIT_TIME_5S ) )
        {
            return BGM113_OK;
        }
    }
    else
    {
        if ( BGM113_OK == bgm113_wait_packet ( ctx, BGM113_MSG_TYPE_EVENT, BGM113_MSG_CLASS_DFU, 
                                                    BGM113_MSG_ID_EVT_DFU_BOOT, BGM113_WAIT_TIME_5S ) )
        {
            return BGM113_OK;
        }
    }
    
    return BGM113_ERROR;
}

// ------------------------------------------------------------------------- END
