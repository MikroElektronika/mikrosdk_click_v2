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

#include "ble4.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ble4_cfg_setup ( ble4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->dtr = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->dsr = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

BLE4_RETVAL ble4_init ( ble4_t *ctx, ble4_cfg_t *cfg )
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
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->dsr, cfg->dsr );

    // Input pins

    digital_in_init( &ctx->dtr, cfg->dtr );
    digital_in_init( &ctx->rts, cfg->rts );

    digital_out_high( &ctx->rst );

    ble4_set_cts_pin ( ctx, 0 );
    ble4_set_dsr_pin ( ctx, 0 );

    ctx->rsp_rdy = BLE4_RSP_NOT_READY;
    ctx->termination_char = '\r';

    return BLE4_OK;
}

void ble4_reset ( ble4_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void ble4_generic_write ( ble4_t *ctx, char *data_buf, uint16_t len )
{
        while(*data_buf) {
            uart_write( &ctx->uart, data_buf++, 1);
            Delay_1ms();
        }
}

int32_t ble4_generic_read ( ble4_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t ble4_response_ready( ble4_t *ctx )
{
    if ( ctx->rsp_rdy )
    {
        ctx->rsp_rdy = BLE4_RSP_NOT_READY;

        return BLE4_RSP_READY;
    }

    return BLE4_RSP_NOT_READY;
}

void ble4_send_command ( ble4_t *ctx, char * command, uint8_t term_char )
{
    char tmp_buf[ 100 ];
    int16_t len;
    
    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );
    tmp_buf[ len ] = term_char;
    tmp_buf[ len + 1 ] = 0;
    
    len = strlen( tmp_buf );

    ble4_set_cts_pin( ctx, 1 );
    ble4_generic_write( ctx, tmp_buf, len );
    ble4_set_cts_pin( ctx, 0 );
    ctx->termination_char = term_char;
}

void ble4_fact_rst_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UFACTORY", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+CPWROFF", ctx->termination_char );
}

void ble4_store_cnfg_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT&W", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+CPWROFF", ctx->termination_char );
}

void ble4_get_local_addr_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UMLA=1", ctx->termination_char );
}

void ble4_set_start_mode_cmd ( ble4_t *ctx, uint8_t start_mode )
{
    uint8_t tx_msg[ 10 ] = "AT+UMSM=";
    
    if ( start_mode < 4)
    {
        tx_msg[ 8 ] = start_mode + 48;
    }
    else
    {
        tx_msg[ 8 ] = '0';
    }
    
    tx_msg[ 9 ] = BLE4_END_BUFF;
    
    ble4_send_command( ctx, tx_msg, ctx->termination_char );
}

void ble4_get_start_mode_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UMSM?", ctx->termination_char );
}

void ble4_enter_mode_cmd ( ble4_t *ctx, uint8_t mode )
{
    uint8_t tx_msg[ 5 ] = "ATO";
    
    if ( mode < 4 )
    {
        tx_msg[ 3 ] = mode + 48;
    }
    else
    {
        tx_msg[ 3 ] = '1';
    }
    
    tx_msg[ 4 ] = BLE4_END_BUFF;

    ble4_send_command( ctx, tx_msg, ctx->termination_char );
}

void ble4_set_echo_cmd ( ble4_t *ctx, uint8_t echo_en )
{
    uint8_t tx_msg[ 5 ] = "ATE";

    if ( echo_en < 2 )
    {
        tx_msg[ 3 ] = echo_en + 48;
    }
    else
    {
        tx_msg[ 3 ] = '1';
    }

    tx_msg[ 4 ] = BLE4_END_BUFF;

    ble4_send_command( ctx, tx_msg, ctx->termination_char );
}

void ble4_get_echo_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "ATE?", ctx->termination_char );
}

void ble4_set_local_name_cmd ( ble4_t *ctx, char *local_name )
{
    uint8_t tx_msg[ 41 ] = "AT+UBTLN=\"";
    uint8_t msg_idx = 10;
    
    while ( *local_name != BLE4_END_BUFF )
    {
        tx_msg[ msg_idx ] = *local_name;
        local_name++;
        msg_idx++;
        
        if ( msg_idx == 39 )
        {
            break;
        }
    }
    
    if ( msg_idx == 10 )
    {
        ble4_send_command( ctx, "AT+UBTLN=\"Bluetooth Device\"", ctx->termination_char );
    }
    else
    {
        tx_msg[ msg_idx ] = '\"';
        tx_msg[ msg_idx + 1 ] = BLE4_END_BUFF;
        
        ble4_send_command( ctx, tx_msg, ctx->termination_char );
    }
}

void ble4_get_local_name_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UBTLN?", ctx->termination_char );
}

void ble4_set_low_energy_role_cmd ( ble4_t *ctx, uint8_t le_role )
{
    uint8_t tx_msg[ 11 ] = "AT+UBTLE=";

    if ( le_role < 4 )
    {
        tx_msg[ 9 ] = le_role + 48;
    }
    else
    {
        tx_msg[ 9 ] = '2';
    }

    tx_msg[ 10 ] = BLE4_END_BUFF;

    ble4_send_command( ctx, tx_msg, ctx->termination_char );
}

void ble4_get_low_energy_role_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UBTLE?", ctx->termination_char );
}

void ble4_get_list_peers_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UDLP?", ctx->termination_char );
}

void ble4_get_server_cnfg_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UDSC", ctx->termination_char );
}

void ble4_set_default_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "ATZ", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+CPWROFF", ctx->termination_char );
}

void ble4_set_sec_mode_cmd ( ble4_t *ctx, uint8_t sec_mode )
{
    uint8_t tx_msg[ 11 ] = "AT+UBTSM=";

    if ( ( sec_mode > 0 ) && ( sec_mode < 7 ) )
    {
        tx_msg[ 9 ] = sec_mode + 48;
    }
    else
    {
        tx_msg[ 9 ] = '1';
    }

    tx_msg[ 10 ] = BLE4_END_BUFF;

    ble4_send_command( ctx, tx_msg, ctx->termination_char );
}

void ble4_get_sec_mode_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UBTSM?", ctx->termination_char );
}

void ble4_pairing_en_cmd ( ble4_t *ctx, uint8_t pairing_mode )
{
    uint8_t tx_msg[ 11 ] = "AT+UBTPM=";

    if ( ( pairing_mode > 0 ) && ( pairing_mode < 3 ) )
    {
        tx_msg[ 9 ] = pairing_mode + 48;
    }
    else
    {
        tx_msg[ 9 ] = '2';
    }

    tx_msg[ 10 ] = BLE4_END_BUFF;

    ble4_send_command( ctx, tx_msg, ctx->termination_char );
}

void ble4_check_pairing_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UBTPM?", ctx->termination_char );
}

void ble4_connectability_en_cmd ( ble4_t *ctx, uint8_t conn_mode )
{
    uint8_t tx_msg[ 11 ] = "AT+UBTCM=";

    if ( ( conn_mode > 0 ) && ( conn_mode < 3 ) )
    {
        tx_msg[ 9 ] = conn_mode + 48;
    }
    else
    {
        tx_msg[ 9 ] = '2';
    }

    tx_msg[ 10 ] = BLE4_END_BUFF;

    ble4_send_command( ctx, tx_msg, ctx->termination_char );
}

void ble4_check_connectability_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UBTCM?", ctx->termination_char );
}

void ble4_discoverability_en_cmd ( ble4_t *ctx, uint8_t discover_mode )
{
    uint8_t tx_msg[ 11 ] = "AT+UBTDM=";

    if ( ( discover_mode > 0 ) && ( discover_mode < 4 ) )
    {
        tx_msg[ 9 ] = discover_mode + 48;
    }
    else
    {
        tx_msg[ 9 ] = '3';
    }

    tx_msg[ 10 ] = BLE4_END_BUFF;

    ble4_send_command( ctx, tx_msg, ctx->termination_char );
}

void ble4_check_discoverability_cmd ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UBTDM?", ctx->termination_char );
}

void ble4_get_info ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+GMI", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+GMM", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+GMR", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+GSN", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+UMRS?", ctx->termination_char );
}

uint8_t ble4_sps_central_pairing ( ble4_t *ctx, uint8_t *local_addr )
{
    uint8_t tx_msg[ 32 ] = "AT+UDDRP=0,sps://";
    uint8_t msg_idx = 17;
    
    while ( *local_addr != BLE4_END_BUFF )
    {
        tx_msg[ msg_idx ] = *local_addr;
        local_addr++;
        msg_idx++;
    }
    
    if ( msg_idx != 29 )
    {
        return BLE4_INIT_ERROR;
    }
    
    tx_msg[ msg_idx ] = ',';
    tx_msg[ msg_idx + 1 ] = '2';
    tx_msg[ msg_idx + 2 ] = BLE4_END_BUFF;

    ble4_send_command( ctx, "AT+UBTLE=1", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, tx_msg, ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+UMSM=1", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT&W", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+CPWROFF", ctx->termination_char );
    
    return BLE4_OK;
}

void ble4_sps_peripheral_pairing ( ble4_t *ctx )
{
    ble4_send_command( ctx, "AT+UBTLE=2", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+UMSM=1", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT&W", ctx->termination_char );
    Delay_10ms( );
    Delay_10ms( );
    ble4_send_command( ctx, "AT+CPWROFF", ctx->termination_char );
}

void ble4_set_cts_pin ( ble4_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->cts );
    }
    else
    {
        digital_out_low( &ctx->cts );
    }
}

void ble4_set_dsr_pin ( ble4_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->dsr );
    }
    else
    {
        digital_out_low( &ctx->dsr );
    }
}

uint8_t ble4_get_dtr_pin ( ble4_t *ctx )
{
    return digital_in_read( &ctx->dtr );
}

uint8_t ble4_get_rts_pin ( ble4_t *ctx )
{
    return digital_in_read( &ctx->rts );
}

// ------------------------------------------------------------------------- END

