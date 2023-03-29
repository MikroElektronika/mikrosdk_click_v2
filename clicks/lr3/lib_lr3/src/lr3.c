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

#include "lr3.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void send_message ( lr3_t *ctx, lr3_message_t *msg );

static uint8_t read_message ( lr3_t *ctx, lr3_message_t *msg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lr3_cfg_setup ( lr3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->wk  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

LR3_RETVAL lr3_init ( lr3_t *ctx, lr3_cfg_t *cfg )
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

    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->wk );
    Delay_1sec( );

    return LR3_OK;
}

int32_t lr3_generic_read ( lr3_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void lr3_generic_write ( lr3_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

void lr3_hard_reset ( lr3_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( ); 
    Delay_100ms( ); 
    Delay_100ms( ); 
    Delay_100ms( ); 
    Delay_100ms( ); 
    digital_out_high( &ctx->rst );
    Delay_1sec();
}

void lr3_wake_up ( lr3_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wk, state );
    Delay_100ms( );
}

void lr3_set_ind_handler ( lr3_t *ctx, lr3_ind_hdl_t hdl )
{
    ctx->ind_handler = hdl;
}

uint8_t lr3_command ( lr3_t *ctx, lr3_message_t *msg, lr3_message_t *rsp )
{
    lr3_message_t *tmp_msg = msg;
    lr3_message_t *tmp_rsp = rsp;
    uint8_t result;
    uint8_t tmp_buf[ 50 ];
    
    // Clear RX buffer
    lr3_generic_read( ctx, tmp_buf, 50 );
    
    send_message( ctx, tmp_msg );
    result = read_message( ctx, tmp_rsp );
    return result;
}

uint8_t lr3_read_message_process ( lr3_t *ctx )
{
    while ( 0 != digital_in_read( &ctx->int_pin ) )
    {
        uint8_t res;
        lr3_message_t tmp;

        if ( 0 == ( res = read_message( ctx, &tmp ) ) )
        {
            ctx->ind_handler( &tmp.command, &tmp.payload_size, &tmp.payload[ 0 ] );
            return res;
        }
    }
    return LR3_ERR_RESPONSE;
}

/* --------------------------------------------------------------- API CALLS */

LR3_RETVAL lr3_soft_reset ( lr3_t *ctx )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    cmd_msg.command = LR3_CMD_RESET;
    cmd_msg.payload_size = 0x00;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT ) == rsp_msg.command )
    {
        return LR3_OK;
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_factory_reset ( lr3_t *ctx )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    cmd_msg.command = LR3_CMD_FACTORY_RESET;
    cmd_msg.payload_size = 0x00;   

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }
    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_write_eeprom ( lr3_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    if ( n_bytes > 254 )
    {
        return LR3_ERR_PL_LEN;
    }
    cmd_msg.command = LR3_CMD_EEPROM_WRITE;
    cmd_msg.payload_size = n_bytes + 1;
    cmd_msg.payload[ 0 ] = address;
    memcpy( &cmd_msg.payload[ 1 ], data_in, n_bytes );

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }
    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }
    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_read_eeprom ( lr3_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_out )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    if ( n_bytes > 254 )
    {
        return LR3_ERR_PL_LEN;   
    }

    cmd_msg.command = LR3_CMD_EEPROM_READ;
    cmd_msg.payload_size = 2;
    cmd_msg.payload[ 0 ] = address;
    cmd_msg.payload[ 1 ] = n_bytes;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }
    memcpy( data_out, &rsp_msg.payload[ 1 ], n_bytes );
    
    return rsp_msg.payload[ 0 ];
}

LR3_RETVAL lr3_get_fw_version ( lr3_t *ctx, uint32_t *fw_version )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;
    uint32_t temp = 0;

    cmd_msg.command = LR3_CMD_GET_FW_VERSION;
    cmd_msg.payload_size = 0;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }
    if ( rsp_msg.payload_size == 4 )
    {
        temp = rsp_msg.payload[ 3 ];
        temp <<= 8;
        temp |= rsp_msg.payload[ 2 ];
        temp <<= 8;
        temp |= rsp_msg.payload[ 1 ];
        temp <<= 8;
        temp |= rsp_msg.payload[ 0 ];
        *fw_version = temp;
        return LR3_OK;
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_get_serial_no ( lr3_t *ctx, uint32_t *serial_no )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;
    uint32_t temp = 0;

    cmd_msg.command = LR3_CMD_GET_SERIAL_NO;
    cmd_msg.payload_size = 0;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 4 )
    {
        temp = rsp_msg.payload[ 3 ];
        temp <<= 8;
        temp |= rsp_msg.payload[ 2 ];
        temp <<= 8;
        temp |= rsp_msg.payload[ 1 ];
        temp <<= 8;
        temp |= rsp_msg.payload[ 0 ];
        *serial_no = temp;
        return LR3_OK;
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_enable_pairing ( lr3_t *ctx, uint8_t state )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    cmd_msg.command = LR3_ENABLE_PAIRING;
    cmd_msg.payload_size = 1;
    cmd_msg.payload[ 0 ] = state;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    
    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }
    
    return LR3_OK;
}

LR3_RETVAL lr3_get_network_table_size ( lr3_t *ctx )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    cmd_msg.command = LR3_GET_NETWORK_TABLE_SIZE;
    cmd_msg.payload_size = 0;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_get_network_table_row ( lr3_t *ctx, uint8_t index, uint8_t *data_out )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;
    uint8_t temp;
    
    temp = lr3_get_network_table_size( ctx ) - 1;
    if ( index > temp )
    {
        index = temp;
    }

    cmd_msg.command = LR3_GET_NETWORK_TABLE_ROW;
    cmd_msg.payload_size = 1;
    cmd_msg.payload[ 0 ] = index;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 5 )
    {
        memcpy( data_out, &rsp_msg.payload[ 0 ], 5 );
        return LR3_OK;
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_delete_network_table_row ( lr3_t *ctx, uint8_t *device_id )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    cmd_msg.command = LR3_DEL_NET_TABLE_ROW;
    cmd_msg.payload_size = 4;
    memcpy( &cmd_msg.payload[ 0 ], device_id, 4 );

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_delete_all_network_table ( lr3_t *ctx )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;
    
    cmd_msg.command = LR3_DEL_ALL_NETWORK_TABLE;
    cmd_msg.payload_size = 0;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    } 

    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_tx_message ( lr3_t *ctx, lr3_tx_msg_t *tx_msg )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    if ( tx_msg->n_bytes > 26 )
    {
        return LR3_ERR_PL_LEN;
    }

    cmd_msg.command = LR3_TX_MESSAGE;
    cmd_msg.payload_size = tx_msg->n_bytes + 5;
    cmd_msg.payload[ 0 ] = tx_msg->option;
    cmd_msg.payload[ 1 ] = tx_msg->destination_id & 0x000000FF;
    cmd_msg.payload[ 2 ] = ( tx_msg->destination_id >> 8 ) & 0x000000FF;
    cmd_msg.payload[ 3 ] = ( tx_msg->destination_id >> 16 ) & 0x000000FF;
    cmd_msg.payload[ 4 ] = ( tx_msg->destination_id >> 24 ) & 0x000000FF;
    memcpy( &cmd_msg.payload[ 5 ], tx_msg->data_in, tx_msg->n_bytes );

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }
    
    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_get_pairing_request ( lr3_t *ctx )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    cmd_msg.command = LR3_GET_PAIRING_REQUEST;
    cmd_msg.payload_size = 0;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_get_activation_status ( lr3_t *ctx, uint8_t *data_out )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    cmd_msg.command = LR3_GET_ACTIVATION_STATUS;
    cmd_msg.payload_size = 0;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 5 )
    {
        memcpy( data_out, &rsp_msg.payload[ 1 ], 4 );
    }

    return rsp_msg.payload[ 0 ];
}

LR3_RETVAL lr3_check_link_request ( lr3_t *ctx, uint8_t power, uint8_t message_num, uint8_t message_th )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;
    
    if ( power < 2 )
    {
        power = 2;
    }
    else if ( power > 14 )
    {
        power = 14;
    }
    if ( message_num < 4 )
    {
        message_num = 4;
    }
    else if ( message_num > 20 )
    {
        message_num = 20;
    }
    if ( message_th < 1 )
    {
        message_th = 1;
    }
    else if ( message_th > message_num )
    {
        message_th = message_num;
    }

    cmd_msg.command = LR3_CHECK_LINK_REQUEST;
    cmd_msg.payload_size = 3;
    cmd_msg.payload[ 0 ] = power;
    cmd_msg.payload[ 1 ] = message_num;
    cmd_msg.payload[ 2 ] = message_th;

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR3_ERR_RESPONSE;
}

LR3_RETVAL lr3_set_app_key ( lr3_t *ctx, uint8_t *app_key )
{
    uint8_t result;
    lr3_message_t cmd_msg;
    lr3_message_t rsp_msg;

    cmd_msg.command = LR3_SET_APP_KEY;
    cmd_msg.payload_size = 0x10;
    memcpy( &cmd_msg.payload[ 0 ], app_key, 0x10 );

    if ( result = lr3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LR3_ERR_RESPONSE;
    }

    return LR3_OK;
}

uint8_t lr3_chk_sum ( lr3_message_t *cmd )
{
    uint8_t res = FRAME_HEADER;

    res += cmd->command;
    res += cmd->payload_size;

    for ( uint8_t cnt = 0; cnt < cmd->payload_size; cnt++ )
    {
        res += cmd->payload[ cnt ];
    }

    res = ~res;
    res += 1;

    return res;
}

// ---------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void send_message ( lr3_t *ctx, lr3_message_t *msg )
{
    uint8_t tmp;
    uint8_t crc = lr3_chk_sum( msg );

    digital_out_low( &ctx->wk );  // NWAKE CTL
    Delay_100ms( );

    tmp = FRAME_HEADER;
    uart_write( &ctx->uart, &tmp, 1 );
    uart_write( &ctx->uart, &msg->command, 1 );
    uart_write( &ctx->uart, &msg->payload_size, 1 );

    uart_write( &ctx->uart, msg->payload, msg->payload_size );
    
    uart_write( &ctx->uart, &crc, 1 );
}

static uint8_t read_message ( lr3_t *ctx, lr3_message_t *msg )
{
    uint8_t  crc    = 0;
    uint16_t rx_cnt = 0;
    uint8_t  ftx    = 1;
    uint8_t  pl_cnt = 255;
    uint8_t  tmp;
    
    while( uart_read( &ctx->uart, &tmp, 1 ) <= 0 )
    {
        Delay_10ms( );
    }
    
    if ( tmp != FRAME_HEADER ) 
    {
        return LR3_ERR_HEADER;
    }
        
    uart_read( &ctx->uart, &msg->command, 1 );
    uart_read( &ctx->uart, &msg->payload_size, 1 );
    pl_cnt = msg->payload_size;

    // Payload 
    uart_read( &ctx->uart, msg->payload, pl_cnt );
    
    // CRC 
    uart_read( &ctx->uart, &crc, 1 );

    digital_out_high( &ctx->wk );
    Delay_100ms( );

    return ( crc == lr3_chk_sum( msg ) ? LR3_OK : LR3_ERR_CHKSUM );
}


// ------------------------------------------------------------------------- END

