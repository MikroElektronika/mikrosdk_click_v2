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
 * @file zigbee.c
 * @brief ZigBee Click Driver.
 */

#include "zigbee.h"


// ---------------------------------------------------------------- VARIABLES

zigbee_error_type ZIGBEE_ERROR_MATRIX[ 60 ] =
{
    { ZIGBEE_ERROR_OK,
     "Everything OK - Success" },

    { ZIGBEE_ERROR_CANT_POLL_TIMEOUT,
     "Couldn’t poll Parent because of Timeout" },

    { ZIGBEE_ERROR_UNKNOWN_CMD,
     "Unknown command" },

    { ZIGBEE_ERROR_INVALID_SREG,
     "Invalid S-Register" },

    { ZIGBEE_ERROR_INVALID_PARAM,
     "Invalid parameter" },

    { ZIGBEE_ERROR_RECIPIENT,
     "Recipient could not be reached" },

    { ZIGBEE_ERROR_MSG_NACK,
     "Message was not acknowledged" },

    { ZIGBEE_ERROR_NSINK,
     "No sink known" },

    { ZIGBEE_ERROR_ADR_TABLE_IN_USE,
     "Address Table entry is in use and cannot be modified" },

    { ZIGBEE_ERROR_MSG_NOT_SENT,
     "Message could not be sent" },

    { ZIGBEE_ERROR_LOCAL_NODE_NSINK,
     "Local node is not sink" },

    { ZIGBEE_ERROR_TOO_MANY_CHAR,
     "Too many characters" },

    { ZIGBEE_ERROR_BG_SCAN_IN_PROGRESS,
     "Background Scan in Progress (Please wait and try again)" },

    { ZIGBEE_ERROR_FATAL_INIT_NET,
     "Fatal error initialising the network" },

    { ZIGBEE_ERROR_BOOTLOADING,
     "Error bootloading" },

    { ZIGBEE_ERROR_FATAL_INIT_STACK,
     "Fatal error initialising the stack" },

    { ZIGBEE_ERROR_NODE_OUT_OF_BUFFER,
     "Node has run out of Buffers" },

    { ZIGBEE_ERROR_READ_ONLY_REG,
     "Trying to write read-only register" },

    { ZIGBEE_ERROR_DATA_MODE_REFUSED_RN,
     "Data Mode Refused by Remote Node" },

    { ZIGBEE_ERROR_CONN_LOST_DATA_MODE,
     "Connection Lost in Data Mode" },

    { ZIGBEE_ERROR_RN_IN_DATA_MODE,
     "Remote node is already in Data Mode" },

    { ZIGBEE_ERROR_INVALID_PASWD,
     "Invalid password" },

    { ZIGBEE_ERROR_CANT_FORM_NET,
     "Cannot form network" },

    { ZIGBEE_ERROR_NO_NET_FOUND,
     "No network found" },

    { ZIGBEE_ERROR_NOD_PART_OF_PAN,
     "Operation cannot be completed if node is part of a PAN" },

    { ZIGBEE_ERROR_LEAVING_PAN,
     "Error leaving the PAN" },

    { ZIGBEE_ERROR_SCANNING_PAN,
     "Error scanning for PANs" },

    { ZIGBEE_ERROR_NO_RESP_BOOTLOADER,
     "No response from the remote bootloader" },

    { ZIGBEE_ERROR_TARGET_NO_RESP,
     "Target did not respond during cloning" },

    { ZIGBEE_ERROR_TIMEOUT_XCASTB,
     "Timeout occurred during xCASTB" },

    { ZIGBEE_ERROR_MAC_TX_QUEUE_FULL,
     "MAC Transmit Queue is Full" },

    { ZIGBEE_ERROR_INVALID_BIND_INDEX,
     "Invalid Binding Index" },

    { ZIGBEE_ERROR_INVALID_OP,
     "Invalid Operation" },

    { ZIGBEE_ERROR_MORE_THAN_10_UNI_MSG,
     "More than 10 unicast messages were in flight at the same time" },

    { ZIGBEE_ERROR_MSG_TOO_LONG,
     "Message too long" },

    { ZIGBEE_ERROR_ZDP_INVALID_REQ_TYPE,
     "ZDP Invalid Request Type" },

    { ZIGBEE_ERROR_ZDP_DEV_NOT_FOUND,
     "ZDP Device not Found" },

    { ZIGBEE_ERROR_ZDP_INVALID_ENDPONT,
     "ZDP Invalid Endpoint" },

    { ZIGBEE_ERROR_ZDP_NOT_ACTIVE,
     "ZDP Not Active" },

    { ZIGBEE_ERROR_ZDP_NOT_SUPPORTED,
     "ZDP Not Supported" },

    { ZIGBEE_ERROR_ZDP_TIMEOUT,
     "ZDP Timeout" },

    { ZIGBEE_ERROR_ZDP_NO_MATCH,
     "ZDP No Match" },

    { ZIGBEE_ERROR_ZDP_TABLE_FULL,
     "ZDP Table Full" },

    { ZIGBEE_ERROR_ZDP_NO_ENTRY,
     "ZDP No Entry" },

    { ZIGBEE_ERROR_ZDP_NO_DESC,
     "ZDP No Descriptor" },

    { ZIGBEE_ERROR_OP_IF_CONN_TO_PAN,
     "Operation only possible if connected to a PAN" },

    { ZIGBEE_ERROR_NODE_NOT_IN_NET,
     "Node is not part of a Network" },

    { ZIGBEE_ERROR_CANNT_JOIN_NET,
     "Cannot join network" },

    { ZIGBEE_ERROR_MOBILE_END_DEV_MOVE,
     "Mobile End Device Move to new Parent Failed" },

    { ZIGBEE_ERROR_CANT_JOIN_2006_NET,
     "Cannot join ZigBee 2006 Network as Router" },

    { ZIGBEE_ERROR_8_MSG_IN_8_SEC_MAX,
     "More than 8 broadcasts were sent within 8 seconds" },

    { ZIGBEE_ERROR_NO_BEACON,
     "Trying to join, but no beacons could be heard" },

    { ZIGBEE_ERROR_NET_KEY_SENT,
     "Network key was sent in the clear when trying to join secured" },

    { ZIGBEE_ERROR_NO_RECEIVE_NET_KEY,
     "Did not receive Network Key" },

    { ZIGBEE_ERROR_NO_LINK_KEY_REQ,
     "No Link Key received" },

    { ZIGBEE_ERROR_PRECONFIG_KEY_REQ,
     "Preconfigured Key Required" },

    { ZIGBEE_ERROR_NWK_ALREADY_PRESENT,
     "NWK Already Present" },

    { ZIGBEE_ERROR_NWK_TABLE_FULL,
     "NWK Table Full" },

    { ZIGBEE_ERROR_NWK_UNKNOWN_DEV,
     "NWK Unknown Device" },

    { 0xFF, "No known error" }
};

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief ZigBee hex to byte function.
 * @details This function is used for converting hex to byte.
 */
static unsigned char dev_hex_to_byte ( char hex_in[ 2 ] );

/**
 * @brief ZigBee ajust hex function.
 * @details This function is used for converting hex to byte.
 */
static char dev_adjust_hex ( char *byte_in, char *result );

/**
 * @brief ZigBee error process.
 * @details This function is used for processing error flags.
 */
static void dev_error_process ( char *error_hex );

/**
 * @brief ZigBee delay function.
 * @details This function is used for creating delays with the desired length.
 */
static void dev_delay ( uint32_t delay_value );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void zigbee_cfg_setup ( zigbee_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->fw   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 19200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t zigbee_init ( zigbee_t *ctx, zigbee_cfg_t *cfg ) 
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
    digital_out_init( &ctx->fw, cfg->fw );
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->fw );

    return UART_SUCCESS;
}

err_t zigbee_generic_write ( zigbee_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t zigbee_generic_read ( zigbee_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void zigbee_send_at ( zigbee_t *ctx, uint8_t *at_buf, uint8_t *suffix_buf )
{
    uint8_t cmd_buf[ 100 ] = { 0 };
    uint8_t cmd[ 1 ] = { 13 };
    uint8_t *cmd_ptr = &cmd_buf[ 0 ];
    
    strcpy( cmd_buf, at_buf );
    strcat( cmd_buf, suffix_buf );
    while ( ( *cmd_ptr ) != 0 )
    {
        uart_write( &ctx->uart, cmd_ptr, 1 );
        cmd_ptr++;
    }
    uart_write( &ctx->uart, cmd, 1 );
}

void zigbee_send_cmd ( zigbee_t *ctx, uint8_t *cmd_buf )
{
    uint8_t cmd[ 1 ] = { 13 };
    while ( ( *cmd_buf ) != 0 )
    {
        uart_write( &ctx->uart, cmd_buf, 1 );
        cmd_buf++;
    }
    uart_write( &ctx->uart, cmd, 1 );
}


uint8_t zigbee_resp ( zigbee_t *ctx, char *data_in )
{
    char *error_resp;
    
    if ( strrchr( data_in, 10 ) || strrchr( data_in, 13 ) )
    {
        if ( strstr( data_in, ZIGBEE_RESP_OK ) )
        {
            return ZIGBEE_OP_OK;
        }
        else if ( strstr( data_in, ZIGBEE_RESP_ERROR ) )
        {
            strstr( data_in, ZIGBEE_RESP_ERROR );
            dev_error_process( error_resp + ZIGBEE_ERROR_INC );
            return ZIGBEE_OP_ERROR;
        }
        
        return ZIGBEE_OP_NL;
    }
    else
    {
        return ZIGBEE_OP_WAIT;
    }
}

char *zigbee_error_handler ( uint8_t error_code )
{
    uint8_t error_cnt;
    
    for ( error_cnt = 0; error_cnt < ZIGBEE_ERROR_CODE_MAX; error_cnt++ )
    {
        if ( ZIGBEE_ERROR_MATRIX[error_cnt].error_code == error_code )
        {
            return ZIGBEE_ERROR_MATRIX[error_cnt].error_desc;
        }
    }
    return ZIGBEE_ERROR_MATRIX[ ZIGBEE_ERROR_CODE_MAX ].error_desc;
}

void zigbee_set_pin_rst ( zigbee_t *ctx, uint8_t status )
{
    if ( status == 1 ) {
        digital_out_high( &ctx->rst );
    } else {
        digital_out_low( &ctx->rst );
    }
}

void zigbee_set_pin_fw ( zigbee_t *ctx, uint8_t status )
{
    if ( status == 1 ) {
        digital_out_high( &ctx->fw );
    } else {
        digital_out_low( &ctx->fw );
    }
}

uint8_t zigbee_get_pin_int ( zigbee_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void zigbee_restart ( zigbee_t *ctx )
{
    zigbee_set_pin_rst( ctx, 0 );
    dev_delay( 500 );
    zigbee_set_pin_rst( ctx, 1 );
    dev_delay( 500 );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static unsigned char dev_hex_to_byte ( char *hex_in )
{
    char counter1 = 0,
        counter2 = 0,
        result1,
        result2,
        result = 0;
    int i;

    for( i = 0; i < 2; i++ )
    {
        if( !( ( ( hex_in[ i ] >= '0' ) && ( hex_in[ i ] <= '9' ) ) ||
               ( ( hex_in[ i ] >= 'a' ) && ( hex_in[ i ] <= 'f' ) ) ||
               ( ( hex_in[ i ] >= 'A' ) && ( hex_in[ i ] <= 'F' ) ) ) )
            return 0;
    }


    counter1 = dev_adjust_hex( &hex_in[ 0 ], &result1 );
    result1 = result1<<4;

    counter2 = dev_adjust_hex( &hex_in[ 1 ], &result2 );
    result = result1 + result2;

    if ( ( counter1+counter2 )>4 )
        result = 0;

    return result;
}

static char dev_adjust_hex ( char *byte_in, char *result )
{
    char tmp = *byte_in,
         counter = 0;

    if ( ( tmp >= '0' ) && ( tmp <= '9' ) ) *result = ( tmp - 48 );
    else counter++;
    if ( ( tmp >= 'A' ) && ( tmp <= 'F' ) ) *result = ( tmp - 55 );
    else counter++;
    if ( ( tmp >= 'a' ) && ( tmp <= 'f' ) ) *result = ( tmp - 87 );
    else counter++;

    return counter;
}

static void dev_error_process ( char *error_hex )
{
    uint8_t temp_val;
    char *error_hndl;
    temp_val = dev_hex_to_byte( error_hex );
    error_hndl = zigbee_error_handler( temp_val );
}

static void dev_delay ( uint32_t delay_value )
{
    uint32_t delay_cnt;
    for ( delay_cnt = 0; delay_cnt < delay_value; delay_cnt++ )
    {
        Delay_1ms();
    }
}

// ------------------------------------------------------------------------- END
