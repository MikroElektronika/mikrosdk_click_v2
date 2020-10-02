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

#include "lora3.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void send_message ( lora3_t *ctx, lora3_message_t *msg );

uint8_t read_message ( lora3_t *ctx, lora3_message_t *msg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lora3_cfg_setup ( lora3_cfg_t *cfg )
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

LORA3_RETVAL lora3_init ( lora3_t *ctx, lora3_cfg_t *cfg )
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
    

    return LORA3_OK;
}

uint16_t lora3_generic_read ( lora3_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void lora3_hard_reset ( lora3_t *ctx )
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

void lora3_wake_up ( lora3_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wk, state );
    Delay_100ms( );
}

void lora3_set_ind_handler ( lora3_t *ctx, lora3_ind_hdl_t hdl )
{
    ctx->ind_hanlder = hdl;
}

uint8_t lora3_command ( lora3_t *ctx, lora3_message_t *msg, lora3_message_t *rsp )
{
    lora3_message_t *tmp_msg = msg;
    lora3_message_t *tmp_rsp = rsp;

    send_message( ctx, tmp_msg );
    return read_message( ctx, tmp_rsp );
}

void lora3_read_message_process ( lora3_t *ctx )
{
    if ( 0 == digital_in_read( &ctx->int_pin ) )
    {
        uint8_t res;
        lora3_message_t tmp;

        if ( 0 == ( res = read_message( ctx, &tmp ) ) )
        {
            ctx->ind_hanlder( &tmp.command, &tmp.pay_load_size, &tmp.pay_load[ 0 ] );
        }
    }
}

/* --------------------------------------------------------------- API CALLS */

LORA3_RETVAL lora3_soft_reset ( lora3_t *ctx )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    cmd_msg.command = LORA3_CMD_RESET;
    cmd_msg.pay_load_size = 0x00;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT ) == rsp_msg.command )
    {
        return LORA3_OK;
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_factory_reset ( lora3_t *ctx )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    cmd_msg.command = LORA3_CMD_FACTORY_RESET;
    cmd_msg.pay_load_size = 0x00;   

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | RESPONSE_BIT ) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }
    if ( rsp_msg.pay_load_size == 1 )
    {
        return rsp_msg.pay_load[ 0 ];
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_write_eeprom ( lora3_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    if ( n_bytes > 254 )
    {
        ctx->result = LORA3_ERR_PL_LEN;
        return 0;
    }
    cmd_msg.command = LORA3_CMD_EEPROM_WRITE;
    cmd_msg.pay_load_size = n_bytes + 1;
    cmd_msg.pay_load[ 0 ] = address;
    memcpy( &cmd_msg.pay_load[ 1 ], data_in, n_bytes );

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        ctx->result = result;
        return 0;
    }
    if ( ( cmd_msg.command | RESPONSE_BIT ) != rsp_msg.command )
    {
        ctx->result = LORA3_ERR_RESPONSE;
        return 0;
    }
    if ( rsp_msg.pay_load_size == 1 )
    {
        ctx->result = rsp_msg.pay_load[ 0 ];
    }
    ctx->result = LORA3_ERR_RESPONSE;
    return 0;
}

LORA3_RETVAL lora3_read_eeprom ( lora3_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_out )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    if ( n_bytes > 254 )
    {
        return LORA3_ERR_PL_LEN;   
    }

    cmd_msg.command = LORA3_CMD_EEPROM_READ;
    cmd_msg.pay_load_size = 2;
    cmd_msg.pay_load[ 0 ] = address;
    cmd_msg.pay_load[ 1 ] = n_bytes;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }
    memcpy( data_out, &rsp_msg.pay_load[ 1 ], n_bytes );
    
    return rsp_msg.pay_load[ 0 ];
}

LORA3_RETVAL lora3_get_fw_version ( lora3_t *ctx, uint32_t *fw_version )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;
    uint32_t temp = 0;

    cmd_msg.command = LORA3_CMD_GET_FW_VERSION;
    cmd_msg.pay_load_size = 0;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }
    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }
    if ( rsp_msg.pay_load_size == 4 )
    {
        temp = rsp_msg.pay_load[ 3 ];
        temp <<= 8;
        temp |= rsp_msg.pay_load[ 2 ];
        temp <<= 8;
        temp |= rsp_msg.pay_load[ 1 ];
        temp <<= 8;
        temp |= rsp_msg.pay_load[ 0 ];
        *fw_version = temp;
        return LORA3_OK;
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_get_serial_no ( lora3_t *ctx, uint32_t *serial_no )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;
    uint32_t temp = 0;

    cmd_msg.command = LORA3_CMD_GET_SERIAL_NO;
    cmd_msg.pay_load_size = 0;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }

    if ( rsp_msg.pay_load_size == 4 )
    {
        temp = rsp_msg.pay_load[ 3 ];
        temp <<= 8;
        temp |= rsp_msg.pay_load[ 2 ];
        temp <<= 8;
        temp |= rsp_msg.pay_load[ 1 ];
        temp <<= 8;
        temp |= rsp_msg.pay_load[ 0 ];
        *serial_no = temp;
        return LORA3_OK;
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_enable_pairing ( lora3_t *ctx, uint8_t state )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    cmd_msg.command = LORA3_ENABLE_PAIRING;
    cmd_msg.pay_load_size = 1;
    cmd_msg.pay_load[ 0 ] = state;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        ctx->result = result;
        return 0;
    }
    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        ctx->result = LORA3_ERR_RESPONSE;
        return 0;
    }
    ctx->result = LORA3_OK;
    return 0;
}

LORA3_RETVAL lora3_get_network_table_size ( lora3_t *ctx )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    cmd_msg.command = LORA3_GET_NETWORK_TABLE_SIZE;
    cmd_msg.pay_load_size = 0;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }

    if ( rsp_msg.pay_load_size == 1 )
    {
        return rsp_msg.pay_load[ 0 ];
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_get_network_table_row ( lora3_t *ctx, uint8_t index, uint8_t *data_out )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;
    uint8_t temp;
    
    temp = lora3_get_network_table_size( ctx ) - 1;
    if ( index > temp )
    {
        index = temp;
    }

    cmd_msg.command = LORA3_GET_NETWORK_TABLE_ROW;
    cmd_msg.pay_load_size = 1;
    cmd_msg.pay_load[ 0 ] = index;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }

    if ( rsp_msg.pay_load_size == 5 )
    {
        memcpy( data_out, &rsp_msg.pay_load[ 0 ], 5 );
        return LORA3_OK;
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_delete_network_table_row ( lora3_t *ctx, uint8_t *device_id )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    cmd_msg.command = LORA3_DEL_NET_TABLE_ROW;
    cmd_msg.pay_load_size = 4;
    memcpy( &cmd_msg.pay_load[ 0 ], device_id, 4 );

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }

    if ( rsp_msg.pay_load_size == 1 )
    {
        return rsp_msg.pay_load[ 0 ];
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_delete_all_network_table ( lora3_t *ctx )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;
    
    cmd_msg.command = LORA3_DEL_ALL_NETWORK_TABLE;
    cmd_msg.pay_load_size = 0;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    } 

    if ( rsp_msg.pay_load_size == 1 )
    {
        return rsp_msg.pay_load[ 0 ];
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_tx_message ( lora3_t *ctx, lora3_tx_msg_t *tx_msg )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    if ( tx_msg->n_bytes > 26 )
    {
        return LORA3_ERR_PL_LEN;
    }

    cmd_msg.command = LORA3_TX_MESSAGE;
    cmd_msg.pay_load_size = tx_msg->n_bytes + 5;
    cmd_msg.pay_load[ 0 ] = tx_msg->option;
    cmd_msg.pay_load[ 1 ] = tx_msg->destination_id & 0x000000FF;
    cmd_msg.pay_load[ 2 ] = ( tx_msg->destination_id >> 8 ) & 0x000000FF;
    cmd_msg.pay_load[ 3 ] = ( tx_msg->destination_id >> 16 ) & 0x000000FF;
    cmd_msg.pay_load[ 4 ] = ( tx_msg->destination_id >> 24 ) & 0x000000FF;
    memcpy( &cmd_msg.pay_load[ 5 ], tx_msg->data_in, tx_msg->n_bytes );

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT ) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }

    if ( rsp_msg.pay_load_size == 1 )
    {
        return rsp_msg.pay_load[ 0 ];
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_get_pairing_request ( lora3_t *ctx )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    cmd_msg.command = LORA3_GET_PAIRING_REQUEST;
    cmd_msg.pay_load_size = 0;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }

    if ( rsp_msg.pay_load_size == 1 )
    {
        return rsp_msg.pay_load[ 0 ];
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_get_activation_status ( lora3_t *ctx, uint8_t *data_out )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    cmd_msg.command = LORA3_GET_ACTIVATION_STATUS;
    cmd_msg.pay_load_size = 0;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }

    if ( rsp_msg.pay_load_size == 5 )
    {
        memcpy( data_out, &rsp_msg.pay_load[ 1 ], 4 );
    }

    return rsp_msg.pay_load[ 0 ];
}

LORA3_RETVAL lora3_check_link_request ( lora3_t *ctx, uint8_t power, uint8_t message_num, uint8_t message_th )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;
    
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

    cmd_msg.command = LORA3_CHECK_LINK_REQUEST;
    cmd_msg.pay_load_size = 3;
    cmd_msg.pay_load[ 0 ] = power;
    cmd_msg.pay_load[ 1 ] = message_num;
    cmd_msg.pay_load[ 2 ] = message_th;

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }

    if ( rsp_msg.pay_load_size == 1 )
    {
        return rsp_msg.pay_load[ 0 ];
    }

    return LORA3_ERR_RESPONSE;
}

LORA3_RETVAL lora3_set_app_key ( lora3_t *ctx, uint8_t *app_key )
{
    uint8_t result;
    lora3_message_t cmd_msg;
    lora3_message_t rsp_msg;

    cmd_msg.command = LORA3_SET_APP_KEY;
    cmd_msg.pay_load_size = 0x10;
    memcpy( &cmd_msg.pay_load[ 0 ], app_key, 0x10 );

    if ( result = lora3_command( ctx, &cmd_msg, &rsp_msg ) )
    {
        return result;
    }

    if ( ( cmd_msg.command | RESPONSE_BIT) != rsp_msg.command )
    {
        return LORA3_ERR_RESPONSE;
    }

    return LORA3_OK;
}

uint8_t lora3_chk_sum ( lora3_message_t *cmd )
{
    uint8_t cnt = 0;
    uint8_t res = FRAME_HEADER;

    res += cmd->command;
    res += cmd->pay_load_size;

    for ( cnt = 0; cnt < cmd->pay_load_size; cnt++ )
    {
        res += cmd->pay_load[ cnt ];
    }

    res = ~res;
    res += 1;

    return res;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void send_message ( lora3_t *ctx, lora3_message_t *msg )
{
    uint8_t tmp;
    uint8_t cnt = 0;
    uint8_t crc = lora3_chk_sum( msg );

    digital_out_low( &ctx->wk );  // NWAKE CTL
    Delay_100ms( );

    tmp = FRAME_HEADER;
    uart_write( &ctx->uart, &tmp, 1 );
    uart_write( &ctx->uart, &msg->command, 1 );
    uart_write( &ctx->uart, &msg->pay_load_size, 1 );

    for ( cnt = 0; cnt < msg->pay_load_size; cnt++ )
    {
        uart_write( &ctx->uart, &msg->pay_load[ cnt ], 1 );
    }

    uart_write( &ctx->uart, &crc, 1 );
}

uint8_t read_message ( lora3_t *ctx, lora3_message_t *msg )
{
    uint8_t  crc    = 0;
    uint16_t rx_cnt = 0;
    uint8_t  ftx    = 1;
    uint8_t  pl_cnt = 255;
    uint8_t  tmp;
    
    while ( 1 )
    {
        
        //Blocking calls

        //TODO : Implement watchdog 

        // Head - Response command  - Pay_load size

        uart_read( &ctx->uart, &tmp, 1 );
        if ( tmp != FRAME_HEADER ) 
        {
            return LORA3_ERR_HEADER;
        }
        uart_read( &ctx->uart, &msg->command, 1 );
        uart_read( &ctx->uart, &msg->pay_load_size, 1 );
        pl_cnt = msg->pay_load_size;

        // Pay_load 

        while ( pl_cnt )
        {
            uart_read( &ctx->uart, &msg->pay_load[ rx_cnt++ ], 1 );
            pl_cnt--;
        }
        break;
    }

    // CRC 

    uart_read( &ctx->uart, &crc, 1 );
    digital_out_high( &ctx->wk );
    Delay_100ms( );

    return ( crc == lora3_chk_sum( msg ) ? LORA3_OK : LORA3_ERR_CHKSUM );
}


// ------------------------------------------------------------------------- END

