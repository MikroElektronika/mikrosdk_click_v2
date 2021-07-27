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

#include "lr4.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void send_message ( lr4_t *ctx, lr4_message_t *msg );

static uint8_t read_message ( lr4_t *ctx, lr4_message_t *msg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lr4_cfg_setup ( lr4_cfg_t *cfg )
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

LR4_RETVAL lr4_init ( lr4_t *ctx, lr4_cfg_t *cfg )
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

    return LR4_OK;
}

int32_t lr4_generic_read ( lr4_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void lr4_generic_write ( lr4_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

void lr4_hard_reset ( lr4_t *ctx )
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

void lr4_wake_up ( lr4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wk, state );
    Delay_100ms( );
}

void lr4_set_ind_handler ( lr4_t *ctx, lr4_ind_hdl_t hdl )
{
    ctx->ind_handler = hdl;
}

uint8_t lr4_command ( lr4_t *ctx, lr4_message_t *msg, lr4_message_t *rsp )
{
    lr4_message_t *tmp_msg = msg;
    lr4_message_t *tmp_rsp = rsp;
    uint8_t tmp_buf[ 50 ];
    uint8_t result = 0;
    
    // Clear RX buffer
    lr4_generic_read( ctx, tmp_buf, 50 );
    
    send_message( ctx, tmp_msg );
    result = read_message( ctx, tmp_rsp );
    if ( result == 0 )
    {
        ctx->ind_handler( &tmp_rsp->command, &tmp_rsp->payload_size, &tmp_rsp->payload[ 0 ] );
    }
    return result;
}

uint8_t lr4_read_message_process ( lr4_t *ctx )
{
    while ( 0 != digital_in_read( &ctx->int_pin ) )
    {
        uint8_t res;
        lr4_message_t tmp;

        if ( 0 == ( res = read_message( ctx, &tmp ) ) )
        {
            ctx->ind_handler( &tmp.command, &tmp.payload_size, &tmp.payload[ 0 ] );
            return res;
        }
    }
    return LR4_ERR_RESPONSE;
}

/* --------------------------------------------------------------- API CALLS */

LR4_RETVAL lr4_soft_reset ( lr4_t *ctx )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    cmd_msg.command = LR4_CMD_RESET;
    cmd_msg.payload_size = 0x00;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) == rsp_msg.command )
    {
        return LR4_OK;
    }

    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_factory_reset ( lr4_t *ctx )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    cmd_msg.command = LR4_CMD_FACTORY_RESET;
    cmd_msg.payload_size = 0x00;   

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }
    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_write_eeprom ( lr4_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    if ( n_bytes > 254 )
    {
        return LR4_ERR_PL_LEN;
    }
    cmd_msg.command = LR4_CMD_EEPROM_WRITE;
    cmd_msg.payload_size = n_bytes + 1;
    cmd_msg.payload[ 0 ] = address;
    memcpy( &cmd_msg.payload[ 1 ], data_in, n_bytes );

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }
    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }
    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_read_eeprom ( lr4_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_out )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    if ( n_bytes > 254 )
    {
        return LR4_ERR_PL_LEN;   
    }

    cmd_msg.command = LR4_CMD_EEPROM_READ;
    cmd_msg.payload_size = 2;
    cmd_msg.payload[ 0 ] = address;
    cmd_msg.payload[ 1 ] = n_bytes;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }
    memcpy( data_out, &rsp_msg.payload[ 1 ], n_bytes );
    
    return rsp_msg.payload[ 0 ];
}

LR4_RETVAL lr4_get_fw_version ( lr4_t *ctx, uint32_t *fw_version )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;
    uint32_t temp = 0;

    cmd_msg.command = LR4_CMD_GET_FW_VERSION;
    cmd_msg.payload_size = 0;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
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
        return LR4_OK;
    }

    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_get_serial_no ( lr4_t *ctx, uint32_t *serial_no )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;
    uint32_t temp = 0;

    cmd_msg.command = LR4_CMD_GET_SERIAL_NO;
    cmd_msg.payload_size = 0;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
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
        return LR4_OK;
    }

    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_get_dev_eui ( lr4_t *ctx, uint8_t *dev_eui )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    cmd_msg.command = LR4_CMD_GET_DEV_EUI;
    cmd_msg.payload_size = 0;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    
    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }
    
    if ( rsp_msg.payload_size == 8 )
    {
        memcpy( dev_eui, &rsp_msg.payload[ 0 ], 8 );
        return LR4_OK;
    }
    
    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_join_network ( lr4_t *ctx, uint8_t mode )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    cmd_msg.command = LR4_CMD_JOIN;
    cmd_msg.payload_size = 1;
    cmd_msg.payload[ 0 ] = mode;


    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_get_status ( lr4_t *ctx, uint8_t status_mode )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;
    
    if ( status_mode == 0 )
    {
        cmd_msg.command = LR4_CMD_GET_ACTIVATION_STATUS;
    }
    else
    {
        cmd_msg.command = LR4_CMD_GET_SESSION_STATUS;
    }

    cmd_msg.payload_size = 0;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_set_key ( lr4_t *ctx, uint8_t *key_data, uint8_t key_mode )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    if ( key_mode == 0 )
    {
        cmd_msg.command = LR4_CMD_SET_APP_KEY;
    }
    else if ( key_mode == 1 )
    {
        cmd_msg.command = LR4_CMD_SET_APP_SESSION_KEY;
    }
    else
    {
        cmd_msg.command = LR4_CMD_SET_NWK_SESSION_KEY;
    }
    
    cmd_msg.payload_size = 0x10;
    memcpy( &cmd_msg.payload[ 0 ], key_data, cmd_msg.payload_size );

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }

    return LR4_OK;
}

LR4_RETVAL lr4_tx_message ( lr4_t *ctx, lr4_tx_msg_t *tx_msg )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    if ( tx_msg->n_bytes > 253 )
    {
        return LR4_ERR_PL_LEN;
    }
    if ( tx_msg->port == 0 )
    {
        tx_msg->port = 1;
    }
    else if ( tx_msg->port > 223 )
    {
        tx_msg->port = 223;
    }

    cmd_msg.command = LR4_CMD_TX_MSG;
    cmd_msg.payload_size = tx_msg->n_bytes + 2;
    cmd_msg.payload[ 0 ] = tx_msg->option;
    cmd_msg.payload[ 1 ] = tx_msg->port;
    memcpy( &cmd_msg.payload[ 2 ], tx_msg->data_in, tx_msg->n_bytes );

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }
    
    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_set_next_tx_data_rate ( lr4_t *ctx, uint8_t data_rate )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    if ( data_rate > 7 )
    {
        data_rate = 7;
    }

    cmd_msg.command = LR4_CMD_SET_NEXT_DR;
    cmd_msg.payload_size = 1;
    cmd_msg.payload[ 0 ] = data_rate;


    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_set_battery_level ( lr4_t *ctx, uint8_t battery_level )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    cmd_msg.command = LR4_CMD_SET_BATTERY_LVL;
    cmd_msg.payload_size = 1;
    cmd_msg.payload[ 0 ] = battery_level;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }

    return LR4_OK;
}

LR4_RETVAL lr4_get_battery_level ( lr4_t *ctx )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;

    cmd_msg.command = LR4_CMD_GET_BATTERY_LVL;
    cmd_msg.payload_size = 0;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }

    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }
    
    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_set_counter ( lr4_t *ctx, uint32_t cnt, uint8_t cnt_mode )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;
    
    if ( cnt_mode == 0 )
    {
        cmd_msg.command = LR4_CMD_SET_UPLINK_CNT;
    }
    else
    {
        cmd_msg.command = LR4_CMD_SET_DOWNLINK_CNT;
    }
    cmd_msg.payload_size = 4;
    cmd_msg.payload[ 0 ] = ( uint8_t )( cnt & 0xFF );
    cmd_msg.payload[ 1 ] = ( uint8_t )( ( cnt >> 8 ) & 0xFF );
    cmd_msg.payload[ 2 ] = ( uint8_t )( ( cnt >> 16 ) & 0xFF );
    cmd_msg.payload[ 3 ] = ( uint8_t )( ( cnt >> 24 ) & 0xFF );


    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }

    return LR4_OK;
}

LR4_RETVAL lr4_get_counter ( lr4_t *ctx, uint32_t *cnt, uint8_t cnt_mode )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;
    uint32_t temp = 0;
    
    if ( cnt_mode == 0 )
    {
        cmd_msg.command = LR4_CMD_GET_UPLINK_CNT;
    }
    else
    {
        cmd_msg.command = LR4_CMD_GET_DOWNLINK_CNT;
    }
    cmd_msg.payload_size = 0;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
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
        *cnt = temp;
        return LR4_OK;
    }
    
    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_set_channel ( lr4_t *ctx, uint8_t index, uint32_t freq, uint8_t data_rate_range, uint8_t status )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;
    uint8_t min_drr = data_rate_range & 0x0F;
    uint8_t max_drr = data_rate_range & 0xF0;

    if ( index < 3 )
    {
        index = 3;
    }
    else if ( index > 15 )
    {
        index = 15;
    }
    if ( max_drr > 0x70 )
    {
        max_drr &= 0x00;
        data_rate_range |= 0x70;
    }
    if ( min_drr > 0x07 )
    {
        min_drr &= 0x00;
        data_rate_range |= 0x07;
    }
    if ( min_drr > ( max_drr >> 4 ) )
    {
        min_drr = max_drr >> 4;
    }
    if ( status > 1 )
    {
        status = 1;
    }
    
    cmd_msg.command = LR4_CMD_SET_CH_PARAMETERS;
    cmd_msg.payload_size = 7;
    cmd_msg.payload[ 0 ] = index;
    cmd_msg.payload[ 1 ] = ( uint8_t )( freq & 0xFF );
    cmd_msg.payload[ 2 ] = ( uint8_t )( ( freq >> 8 ) & 0xFF );
    cmd_msg.payload[ 3 ] = ( uint8_t )( ( freq >> 16 ) & 0xFF );
    cmd_msg.payload[ 4 ] = ( uint8_t )( ( freq >> 24 ) & 0xFF );
    cmd_msg.payload[ 5 ] = min_drr | max_drr;
    cmd_msg.payload[ 6 ] = status;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }
    
    if ( rsp_msg.payload_size == 1 )
    {
        return rsp_msg.payload[ 0 ];
    }

    return LR4_ERR_RESPONSE;
}

LR4_RETVAL lr4_get_channel ( lr4_t *ctx, uint8_t index, uint32_t *freq, uint8_t *data_rate_range, uint8_t *status )
{
    uint8_t result;
    lr4_message_t cmd_msg;
    lr4_message_t rsp_msg;
    uint32_t temp = 0;
    
    if ( index > 15 )
    {
        index = 15;
    }
    
    cmd_msg.command = LR4_CMD_GET_CH_PARAMETERS;
    cmd_msg.payload_size = 1;
    cmd_msg.payload[ 0 ] = index;

    if ( result = lr4_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | LR4_RESPONSE_BIT ) != rsp_msg.command )
    {
        return LR4_ERR_RESPONSE;
    }
    
    if ( rsp_msg.payload_size == 6 )
    {
        temp = rsp_msg.payload[ 3 ];
        temp <<= 8;
        temp |= rsp_msg.payload[ 2 ];
        temp <<= 8;
        temp |= rsp_msg.payload[ 1 ];
        temp <<= 8;
        temp |= rsp_msg.payload[ 0 ];
        *freq = temp;
        *data_rate_range = rsp_msg.payload[ 4 ];
        *status = rsp_msg.payload[ 5 ];
        return LR4_OK;
    }
    
    return LR4_ERR_RESPONSE;
}

uint8_t lr4_chk_sum ( lr4_message_t *cmd )
{
    uint8_t res = LR4_FRAME_HEADER;

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

static void send_message ( lr4_t *ctx, lr4_message_t *msg )
{
    uint8_t tmp;
    uint8_t crc = lr4_chk_sum( msg );

    digital_out_low( &ctx->wk );  // NWAKE CTL
    Delay_100ms( );

    tmp = LR4_FRAME_HEADER;
    uart_write( &ctx->uart, &tmp, 1 );
    uart_write( &ctx->uart, &msg->command, 1 );
    uart_write( &ctx->uart, &msg->payload_size, 1 );

    uart_write( &ctx->uart, msg->payload, msg->payload_size );
    
    uart_write( &ctx->uart, &crc, 1 );
}

static uint8_t read_message ( lr4_t *ctx, lr4_message_t *msg )
{
    uint8_t  crc    = 0;
    uint8_t  tmp;
    
    while( uart_read( &ctx->uart, &tmp, 1 ) <= 0 )
    {
        Delay_10ms( );
    }
    
    if ( tmp != LR4_FRAME_HEADER ) 
    {
        return LR4_ERR_HEADER;
    }
        
    uart_read( &ctx->uart, &msg->command, 1 );
    uart_read( &ctx->uart, &msg->payload_size, 1 );

    // Payload 
    uart_read( &ctx->uart, msg->payload, msg->payload_size );
    
    // CRC 
    uart_read( &ctx->uart, &crc, 1 );
    msg->payload[ msg->payload_size ] = crc;
    
    digital_out_high( &ctx->wk );
    Delay_100ms( );

    return ( crc == lr4_chk_sum( msg ) ? LR4_OK : LR4_ERR_CHKSUM );
}


// ------------------------------------------------------------------------- END

