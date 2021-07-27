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

#include "lr5.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t calc_checksum ( uint8_t op_code, uint8_t payload_length, uint8_t *payload );
static void send_command ( lr5_t *ctx, lr5_cmd_t *cmd_send );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lr5_cfg_setup ( lr5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

     cfg->rst = HAL_PIN_NC;
     cfg->wk  = HAL_PIN_NC;
     cfg->int_pin  = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

LR5_RETVAL lr5_init ( lr5_t *ctx, lr5_cfg_t *cfg )
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
     digital_out_init( &ctx->wk, cfg->wk );

    // Input pins

     digital_in_init( &ctx->int_pin, cfg->int_pin );

    ctx->command_code  = 0x00;
    ctx->received_flag = LR5_RESPONSE_NOT_RECEIVED;
    ctx->rx_cnt = 0;
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->wk );

    return LR5_OK;
}

int32_t lr5_generic_read ( lr5_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}


void lr5_response_handler_set ( lr5_t *ctx, void ( *handler )( uint8_t*, uint8_t*, uint8_t* ) )
{
    ctx->driver_hdl = handler;
}

void lr5_uart_isr ( lr5_t *ctx )
{
    if ( ( ctx->rx_cnt ) > 1 )
    {
        if ( ( ctx->rx_cnt  ) == ( ctx->rx_dat[ 2 ] + 3 ) )
        {
            ctx->received_flag = LR5_RESPONSE_RECEIVED;
            ctx->rx_cnt = 0;
            
            return;
        }
    }
    
    ctx->rx_cnt++;
}

LR5_RETVAL lr5_response_ready ( lr5_t *ctx )
{
    if ( ctx->received_flag )
    {
        ctx->received_flag = LR5_RESPONSE_NOT_RECEIVED;
        
        return LR5_RESPONSE_RECEIVED;
    }
    
    return LR5_RESPONSE_NOT_RECEIVED;
}

LR5_RETVAL lr5_task ( lr5_t *ctx )
{
    uint8_t rx_buff[ 256 ];
    uint8_t rx_idx;
    uint8_t rx_code;
    uint8_t rx_length;
    uint8_t response_code;
    uint8_t chksum;
    
    if ( ctx->rx_dat[ 0 ] != FRAME_HEADER )
    {
        return LR5_FRAME_HEADER_ERR;
    }

    rx_code = ctx->rx_dat[ 1 ];
    rx_length = ctx->rx_dat[ 2 ];
    response_code = LR5_CMD_RESPONSE_READY;
    
    if ( rx_code != ( ctx->command_code | RESPONSE_BIT ) )
    {
        if ( ( rx_code == JOIN_IND ) || ( rx_code == TX_MSG_CONFIRMED_IND ) || ( rx_code == TX_MSG_UNCONFIRMED_IND ) || ( rx_code == RX_MSG_IND ) )
        {
            response_code = LR5_IND_RESPONSE_READY;
        }
        else
        {
            return LR5_CMD_RESPONSE_ERR;
        }
    }

    for ( rx_idx = 0; rx_idx < rx_length; rx_idx++ )
    {
        rx_buff[ rx_idx ] = ctx->rx_dat[ rx_idx + 3 ];
    }

    chksum = calc_checksum( rx_code, rx_length, &rx_buff[ 0 ] );
    
    if ( chksum != ctx->rx_dat[ rx_length + 3 ] )
    {
        return LR5_CHKSUM_ERR;
    }
    
    ctx->driver_hdl( &rx_code, &rx_length, &rx_buff[ 0 ] );
    digital_out_high( &ctx->wk );
    Delay_1ms( );
    
    return response_code;
}

void lr5_hw_reset ( lr5_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms();
    Delay_100ms();
    digital_out_high( &ctx->rst );
    Delay_1sec();
    Delay_1sec();
}

LR5_RETVAL lr5_data_indication ( lr5_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
    {
        return LR5_DATA_NOT_READY;
    }
    else
    {
        return LR5_DATA_READY;
    }
}

void lr5_reset_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = RESET_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

void lr5_factory_reset_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = FACTORY_RESET_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

LR5_RETVAL lr5_eeprom_write_cmd ( lr5_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes )
{
    lr5_cmd_t command;
    uint8_t cnt;
    
    if ( n_bytes > 254 )
    {
        return LR5_NBYTES_INVALID;
    }
    
    command.cmd_code      = EEPROM_WRITE_CMD;
    command.cmd_length    = n_bytes + 1;
    command.cmd_data[ 0 ] = start_addr;
    
    for ( cnt = 1; cnt <= n_bytes; cnt++ )
    {
        command.cmd_data[ cnt ] = *data_in;
        data_in++;
    }
    
    send_command( ctx, &command );
    
    return LR5_OK;
}

LR5_RETVAL lr5_eeprom_read_cmd ( lr5_t *ctx, uint8_t start_addr, uint8_t n_bytes )
{
    lr5_cmd_t command;
    
    if ( n_bytes > 254 ) 
    {
        return LR5_NBYTES_INVALID;
    }
    
    command.cmd_code      = EEPROM_READ_CMD;
    command.cmd_length    = 0x02;
    command.cmd_data[ 0 ] = start_addr;
    command.cmd_data[ 1 ] = n_bytes;
    
    send_command( ctx, &command );
    
    return LR5_OK;
}

void lr5_get_fw_version_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = GET_FW_VERSION_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

void lr5_get_serial_no_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = GET_SERIALNO_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

void lr5_get_dev_eui_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = GET_DEV_EUI_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

void lr5_join_cmd ( lr5_t *ctx, uint8_t mode )
{
    lr5_cmd_t command;
    
    command.cmd_code      = JOIN_CMD;
    command.cmd_length    = 0x01;
    command.cmd_data[ 0 ] = mode;
    
    send_command( ctx, &command );
}

void lr5_get_activation_status_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = GET_ACT_STATUS_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

void lr5_set_app_key_cmd ( lr5_t *ctx, uint8_t *app_key )
{
    lr5_cmd_t command;
    uint8_t cnt;
    
    command.cmd_code   = SET_APP_KEY_CMD;
    command.cmd_length = 0x10;
    
    for ( cnt = 0; cnt < command.cmd_length; cnt++ )
    {
        command.cmd_data[ cnt ] = *app_key;
        app_key++;
    }
    
    send_command( ctx, &command );
}

void lr5_set_app_session_key_cmd ( lr5_t *ctx, uint8_t *app_s_key )
{
    lr5_cmd_t command;
    uint8_t cnt;
    
    command.cmd_code   = SET_APP_SESSION_KEY_CMD;
    command.cmd_length = 0x10;
    
    for ( cnt = 0; cnt < command.cmd_length; cnt++ )
    {
        command.cmd_data[ cnt ] = *app_s_key;
        app_s_key++;
    }
    
    send_command( ctx, &command );
}

void lr5_set_nwk_session_key_cmd ( lr5_t *ctx, uint8_t *nwk_s_key )
{
    lr5_cmd_t command;
    uint8_t cnt;
    
    command.cmd_code   = SET_NWK_SESSION_KEY_CMD;
    command.cmd_length = 0x10;
    
    for ( cnt = 0; cnt < command.cmd_length; cnt++ )
    {
        command.cmd_data[ cnt ] = *nwk_s_key;
        nwk_s_key++;
    }
    
    send_command( ctx, &command );
}

LR5_RETVAL lr5_tx_msg_cmd ( lr5_t *ctx, lr5_msg_t *msg )
{
    lr5_cmd_t command;
    uint8_t cnt;
    
    if ( msg->msg_length > 253 )
    {
        return LR5_NBYTES_INVALID;
    }
    
    command.cmd_code      = TX_MSG_CMD;
    command.cmd_length    = msg->msg_length + 2;
    command.cmd_data[ 0 ] = msg->options;
    command.cmd_data[ 1 ] = msg->port;
    
    for ( cnt = 0; cnt < msg->msg_length; cnt++ )
    {
        command.cmd_data[ cnt + 2 ] = *msg->msg_data;
        msg->msg_data++;
    }
    
    send_command( ctx, &command );
    
    return LR5_OK;
}

void lr5_get_session_status_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = GET_SESSION_STATUS_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

void lr5_set_next_dr_cmd ( lr5_t *ctx, uint8_t data_rate )
{
    lr5_cmd_t command;
    
    command.cmd_code      = SET_NEXT_DR_CMD;
    command.cmd_length    = 0x01;
    command.cmd_data[ 0 ] = data_rate;
    
    send_command( ctx, &command );
}

void lr5_set_battery_level_cmd ( lr5_t *ctx, uint8_t battery_level )
{
    lr5_cmd_t command;
    
    command.cmd_code      = SET_BATTERY_LVL_CMD;
    command.cmd_length    = 0x01;
    command.cmd_data[ 0 ] = battery_level;
    
    send_command( ctx, &command );
}

void lr5_get_battery_level_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = GET_BATTERY_LVL_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

void lr5_set_uplink_cnt_cmd ( lr5_t *ctx, uint32_t uplink_cnt )
{
    lr5_cmd_t command;
    
    command.cmd_code      = SET_UPLINK_CNT_CMD;
    command.cmd_length    = 0x04;
    command.cmd_data[ 0 ] = uplink_cnt;
    command.cmd_data[ 1 ] = uplink_cnt >> 8;
    command.cmd_data[ 2 ] = uplink_cnt >> 16;
    command.cmd_data[ 3 ] = uplink_cnt >> 24;
    
    send_command( ctx, &command );
}

void lr5_get_uplink_cnt_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = GET_UPLINK_CNT_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

void lr5_set_downlink_cnt_cmd ( lr5_t *ctx, uint32_t downlink_cnt )
{
    lr5_cmd_t command;
    
    command.cmd_code      = SET_DOWNLINK_CNT_CMD;
    command.cmd_length    = 0x04;
    command.cmd_data[ 0 ] = downlink_cnt;
    command.cmd_data[ 1 ] = downlink_cnt >> 8;
    command.cmd_data[ 2 ] = downlink_cnt >> 16;
    command.cmd_data[ 3 ] = downlink_cnt >> 24;
    
    send_command( ctx, &command );
}

void lr5_get_downlink_cnt_cmd ( lr5_t *ctx )
{
    lr5_cmd_t command;
    
    command.cmd_code   = GET_DOWNLINK_CNT_CMD;
    command.cmd_length = 0x00;
    
    send_command( ctx, &command );
}

void lr5_set_ch_mask_cmd ( lr5_t *ctx, uint8_t *ch_mask )
{
    lr5_cmd_t command;
    uint8_t cnt;
    
    command.cmd_code   = SET_CH_MASK_CMD;
    command.cmd_length = 0x09;
    
    for ( cnt = 0; cnt < command.cmd_length; cnt++ )
    {
        command.cmd_data[ cnt ] = *ch_mask;
        ch_mask++;
    }
    
    send_command( ctx, &command );
}

LR5_RETVAL lr5_get_ch_param_cmd ( lr5_t *ctx, uint8_t ch_idx )
{
    lr5_cmd_t command;
    
    if ( ch_idx > LR5_CH_IDX_15 )
    {
        return LR5_CH_IDX_INVALID;
    }
    
    command.cmd_code      = GET_CH_PARAM_CMD;
    command.cmd_length    = 0x01;
    command.cmd_data[ 0 ] = ch_idx;
    
    send_command( ctx, &command );
    
    return LR5_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


static uint8_t calc_checksum ( uint8_t op_code, uint8_t payload_length, uint8_t *payload )
{
    uint8_t checksum = FRAME_HEADER;
    uint8_t cnt;
    
    checksum += op_code;
    checksum += payload_length;
    
    for ( cnt = 0; cnt < payload_length; cnt++ )
    {
        checksum += *payload;
        payload++;
    }
    
    checksum = ~checksum;
    checksum += 1;
    
    return checksum;
}

static void send_command ( lr5_t *ctx, lr5_cmd_t *cmd_send )
{
    uint8_t chksum;
    uint8_t cnt;
    uint8_t tmp;
    
    chksum = calc_checksum( cmd_send->cmd_code, cmd_send->cmd_length, &cmd_send->cmd_data[ 0 ] );
    
    digital_out_low( &ctx->wk );
    Delay_1ms();
    
    tmp = FRAME_HEADER;
    uart_write( &ctx->uart, &tmp, 1 );
    uart_write( &ctx->uart, &cmd_send->cmd_code, 1 );
    uart_write( &ctx->uart, &cmd_send->cmd_length, 1 );
    
    for ( cnt = 0; cnt < cmd_send->cmd_length; cnt++ )
    {
        uart_write( &ctx->uart, &cmd_send->cmd_data[ cnt ], 1 );
    }
    
    uart_write( &ctx->uart, &chksum, 1 );
    
    ctx->command_code = cmd_send->cmd_code;
}

// ------------------------------------------------------------------------- END

