/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file wifly.c
 * @brief WiFly Click Driver.
 */

#include "wifly.h"
#include "conversions.h"

/**
 * @brief WiFly Click reply and association limits.
 * @details These macros bound reply settling, network status polling, and numeric conversion storage.
 */
#define WIFLY_REPLY_IDLE_MS             20
#define WIFLY_JOIN_ATTEMPTS             30
#define WIFLY_NUMBER_SIZE               8
#define WIFLY_ASCII_LAST                126

/**
 * @brief WiFly Click volatile default settings.
 * @details These commands configure manual association and small transparent UART transfers.
 * @note No settings are saved to the module Flash.
 */
static char *wifly_default_commands[] =
{
    WIFLY_CMD_SET_UART_MODE,
    WIFLY_CMD_SET_UART_FLOW,
    WIFLY_CMD_SET_WLAN_JOIN,
    WIFLY_CMD_SET_WLAN_CHANNEL,
    WIFLY_CMD_SET_IP_DHCP,
    WIFLY_CMD_SET_IP_FLAGS,
    WIFLY_CMD_SET_SYS_AUTOCONN,
    WIFLY_CMD_SET_SYS_AUTOSLEEP,
    WIFLY_CMD_SET_SYS_SLEEP,
    WIFLY_CMD_SET_COMM_IDLE,
    WIFLY_CMD_SET_COMM_REMOTE,
    WIFLY_CMD_SET_COMM_OPEN,
    WIFLY_CMD_SET_COMM_CLOSE,
    WIFLY_CMD_SET_COMM_TIME,
    WIFLY_CMD_SET_COMM_MATCH,
    WIFLY_CMD_SET_BCAST_INTERVAL,
    WIFLY_CMD_SET_SYS_PRINTLVL
};

/**
 * @brief WiFly Click complete UART writing function.
 * @details This function retries partial UART writes until every byte is queued or the wait expires.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[in] data_in : Input byte buffer.
 * @param[in] len : Number of bytes to queue.
 * @return Success or a negative #wifly_return_value_t error.
 * @note The caller must validate the buffer and length.
 */
static err_t wifly_write_all ( wifly_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WiFly Click reply collection function.
 * @details This function collects a terminated ASCII reply and checks for a module error.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[in] expected : Required reply token.
 * @param[in] timeout_ms : Maximum UART idle wait time in milliseconds.
 * @return Success or a negative #wifly_return_value_t error.
 * @note A short quiet interval consumes trailing CR/LF and prompt bytes after the token.
 */
static err_t wifly_wait_reply ( wifly_t *ctx, char *expected, uint16_t timeout_ms );

/**
 * @brief WiFly Click Command mode entry function.
 * @details This function sends the escape sequence with guard intervals and verifies the CMD reply.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Success or a negative #wifly_return_value_t error.
 * @note Pending receive bytes are discarded only after the transmit guard interval.
 */
static err_t wifly_enter_command ( wifly_t *ctx );

/**
 * @brief WiFly Click parameter writing function.
 * @details This function appends one value to a command prefix and verifies its AOK reply.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @param[in] prefix : Set-command prefix including the final space.
 * @param[in] value : Null-terminated encoded parameter.
 * @return Success or a negative #wifly_return_value_t error.
 * @note The command is built in the context buffer without formatted printing.
 */
static err_t wifly_set_parameter ( wifly_t *ctx, char *prefix, char *value );

/**
 * @brief WiFly Click network association function.
 * @details This function rejoins the cached SSID and polls association and DHCP status.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Success or a negative #wifly_return_value_t error.
 * @note The module retains the passphrase in RAM; the driver only caches the encoded SSID.
 */
static err_t wifly_join_network ( wifly_t *ctx );

void wifly_cfg_setup ( wifly_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->wake = HAL_PIN_NC;
    cfg->ap_pin = HAL_PIN_NC;

    cfg->baud_rate     = WIFLY_BAUD_RATE;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t wifly_init ( wifly_t *ctx, wifly_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    err_t error_flag = WIFLY_ERROR;
    uint8_t dummy_read = 0;

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

    if ( UART_ERROR != uart_open( &ctx->uart, &uart_cfg ) )
    {
        error_flag = WIFLY_OK;
        uart_set_baud( &ctx->uart, cfg->baud_rate );
        uart_set_parity( &ctx->uart, cfg->parity_bit );
        uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
        uart_set_data_bits( &ctx->uart, cfg->data_bit );

        uart_set_blocking( &ctx->uart, cfg->uart_blocking );

        // GPIO9 must remain low when reset is released to select normal operation.
        digital_out_init( &ctx->ap_pin, cfg->ap_pin );
        digital_out_low( &ctx->ap_pin );
        digital_out_init( &ctx->wake, cfg->wake );
        digital_out_low( &ctx->wake );
        digital_out_init( &ctx->rst, cfg->rst );
        digital_out_high( &ctx->rst );

        ctx->command[ 0 ] = 0;
        ctx->response[ 0 ] = 0;
        ctx->ssid[ 0 ] = 0;
        ctx->response_length = 0;
        ctx->local_port = 0;
        ctx->protocol = 0;
        ctx->command_mode = 0;
        ctx->socket_open = 0;

        // Dummy read to enable RX interrupt.
        uart_read( &ctx->uart, &dummy_read, 1 );
        Delay_100ms();
    }

    return error_flag;
}

err_t wifly_default_cfg ( wifly_t *ctx )
{
    err_t error_flag;
    uint8_t command_index;
    char number[ WIFLY_NUMBER_SIZE ];

    error_flag = wifly_reset( ctx );
    if ( ( WIFLY_OK == error_flag ) || ( WIFLY_TIMEOUT == error_flag ) )
    {
        // Quiet boot profiles omit *READY*. A confirmed CMD reply still proves readiness.
        error_flag = wifly_enter_command( ctx );
    }
    for ( command_index = 0;
          ( command_index < sizeof( wifly_default_commands ) / sizeof( wifly_default_commands[ 0 ] ) ) &&
          ( WIFLY_OK == error_flag ); command_index++ )
    {
        error_flag = wifly_send_command( ctx, wifly_default_commands[ command_index ],
                                         WIFLY_REPLY_AOK, WIFLY_COMMAND_TIMEOUT );
    }
    if ( WIFLY_OK == error_flag )
    {
        uint16_to_str( WIFLY_DATA_SIZE, number );
        error_flag = wifly_set_parameter( ctx, WIFLY_CMD_SET_COMM_SIZE_PFX, l_trim( r_trim( number ) ) );
    }
    return error_flag;
}

err_t wifly_reset ( wifly_t *ctx )
{
    err_t error_flag;

    ctx->command_mode = 0;
    ctx->socket_open = 0;
    ctx->protocol = 0;
    ctx->local_port = 0;
    ctx->ssid[ 0 ] = 0;
    digital_out_low( &ctx->ap_pin );
    digital_out_high( &ctx->wake );
    digital_out_low( &ctx->rst );
    Delay_1ms();
    uart_clear( &ctx->uart );
    digital_out_high( &ctx->rst );

    // The reset pulse exceeds the specified 160 us; boot completion is response-driven.
    error_flag = wifly_wait_reply( ctx, WIFLY_REPLY_READY, WIFLY_BOOT_TIMEOUT );
    digital_out_low( &ctx->wake );
    return error_flag;
}

err_t wifly_send_command ( wifly_t *ctx, char *command, char *expected, uint16_t timeout_ms )
{
    err_t error_flag = WIFLY_ERROR_ARGUMENT;
    char *terminator;
    uint16_t command_length;

    ctx->response_length = 0;
    ctx->response[ 0 ] = 0;
    if ( ctx->command_mode && command && expected && expected[ 0 ] && timeout_ms )
    {
        command_length = strlen( command );
        if ( command_length && ( command_length < WIFLY_COMMAND_SIZE ) &&
             !strchr( command, '\r' ) && !strchr( command, '\n' ) )
        {
            if ( command != ctx->command )
            {
                strcpy( ctx->command, command );
            }
            error_flag = wifly_write_all( ctx, ( uint8_t * ) ctx->command, command_length );
            if ( WIFLY_OK == error_flag )
            {
                error_flag = wifly_write_all( ctx, ( uint8_t * ) "\r\n", 2 );
            }
            if ( WIFLY_OK == error_flag )
            {
                terminator = expected;
                if ( 0 == strcmp( expected, WIFLY_REPLY_AOK ) )
                {
                    // Consume the version prompt as well, so it cannot satisfy the next command.
                    terminator = WIFLY_REPLY_PROMPT;
                }
                error_flag = wifly_wait_reply( ctx, terminator, timeout_ms );
                if ( ( WIFLY_OK == error_flag ) && !strstr( ctx->response, expected ) )
                {
                    error_flag = WIFLY_ERROR_RESPONSE;
                }
            }
        }
    }
    return error_flag;
}

err_t wifly_connect ( wifly_t *ctx, char *ssid, char *password )
{
    err_t error_flag = WIFLY_ERROR_ARGUMENT;
    char parameter[ WIFLY_PASSWORD_SIZE ];
    uint16_t ssid_length;
    uint16_t password_length;
    uint8_t replacement = '$';
    uint8_t index;

    if ( ssid && password && ctx->command_mode && !ctx->socket_open )
    {
        ssid_length = strlen( ssid );
        password_length = strlen( password );
        if ( ssid_length && ( ssid_length < WIFLY_SSID_SIZE ) &&
             ( ( 0 == password_length ) ||
               ( ( password_length >= 8 ) && ( password_length < WIFLY_PASSWORD_SIZE ) ) ) )
        {
            error_flag = WIFLY_OK;
            for ( index = 0; index < ssid_length; index++ )
            {
                if ( ( ssid[ index ] < ' ' ) || ( ( uint8_t ) ssid[ index ] > WIFLY_ASCII_LAST ) )
                {
                    error_flag = WIFLY_ERROR_ARGUMENT;
                }
            }
            for ( index = 0; index < password_length; index++ )
            {
                if ( ( password[ index ] < ' ' ) || ( ( uint8_t ) password[ index ] > WIFLY_ASCII_LAST ) )
                {
                    error_flag = WIFLY_ERROR_ARGUMENT;
                }
            }

            // Choose a replacement absent from both strings, preserving literal '$' characters.
            while ( ( replacement <= WIFLY_ASCII_LAST ) &&
                    ( strchr( ssid, replacement ) || strchr( password, replacement ) ) )
            {
                replacement++;
            }
            if ( replacement > WIFLY_ASCII_LAST )
            {
                error_flag = WIFLY_ERROR_ARGUMENT;
            }
            if ( WIFLY_OK == error_flag )
            {
                uint16_to_str( replacement, parameter );
                error_flag = wifly_set_parameter( ctx, WIFLY_CMD_SET_OPT_REPLACE_PFX, l_trim( r_trim( parameter ) ) );
            }
            if ( WIFLY_OK == error_flag )
            {
                strcpy( ctx->ssid, ssid );
                for ( index = 0; index < ssid_length; index++ )
                {
                    if ( ' ' == ctx->ssid[ index ] )
                    {
                        ctx->ssid[ index ] = replacement;
                    }
                }
                error_flag = wifly_set_parameter( ctx, WIFLY_CMD_SET_WLAN_SSID_PFX, ctx->ssid );
            }
            if ( ( WIFLY_OK == error_flag ) && password_length )
            {
                strcpy( parameter, password );
                for ( index = 0; index < password_length; index++ )
                {
                    if ( ' ' == parameter[ index ] )
                    {
                        parameter[ index ] = replacement;
                    }
                }
                error_flag = wifly_set_parameter( ctx, WIFLY_CMD_SET_WLAN_PHRASE_PFX, parameter );
            }
            // Do not retain a passphrase in the host command or temporary buffers.
            memset( parameter, 0, sizeof( parameter ) );
            memset( ctx->command, 0, sizeof( ctx->command ) );
            if ( WIFLY_OK == error_flag )
            {
                error_flag = wifly_join_network( ctx );
            }
        }
    }
    return error_flag;
}

err_t wifly_open_socket ( wifly_t *ctx, uint8_t protocol, char *peer_ip, uint16_t peer_port, uint16_t local_port )
{
    err_t error_flag = WIFLY_ERROR_ARGUMENT;
    char number[ WIFLY_NUMBER_SIZE ];
    uint8_t index;
    uint16_t octet_value = 0;
    uint8_t octet_digits = 0;
    uint8_t octet_count = 1;

    if ( ctx->command_mode && !ctx->socket_open && ctx->ssid[ 0 ] &&
         peer_ip && peer_ip[ 0 ] && ( strlen( peer_ip ) <= 15 ) && peer_port && local_port &&
         ( ( WIFLY_PROTOCOL_TCP == protocol ) || ( WIFLY_PROTOCOL_UDP == protocol ) ) )
    {
        error_flag = WIFLY_OK;
        // Validate each IPv4 octet; length and character checks alone allow invalid addresses.
        for ( index = 0; peer_ip[ index ]; index++ )
        {
            if ( '.' == peer_ip[ index ] )
            {
                if ( !octet_digits || ( octet_value > 255 ) || ( octet_count >= 4 ) )
                {
                    error_flag = WIFLY_ERROR_ARGUMENT;
                }
                else
                {
                    octet_count++;
                    octet_digits = 0;
                    octet_value = 0;
                }
            }
            else if ( ( peer_ip[ index ] >= '0' ) && ( peer_ip[ index ] <= '9' ) )
            {
                if ( octet_digits >= 3 )
                {
                    error_flag = WIFLY_ERROR_ARGUMENT;
                }
                else
                {
                    octet_value = ( octet_value * 10 ) + ( peer_ip[ index ] - '0' );
                    octet_digits++;
                    if ( octet_value > 255 )
                    {
                        error_flag = WIFLY_ERROR_ARGUMENT;
                    }
                }
            }
            else
            {
                error_flag = WIFLY_ERROR_ARGUMENT;
            }
        }
        if ( ( 4 != octet_count ) || !octet_digits )
        {
            error_flag = WIFLY_ERROR_ARGUMENT;
        }
        if ( WIFLY_OK == error_flag )
        {
            uint16_to_str( protocol, number );
            error_flag = wifly_set_parameter( ctx, WIFLY_CMD_SET_IP_PROTOCOL_PFX, l_trim( r_trim( number ) ) );
        }
        if ( WIFLY_OK == error_flag )
        {
            uint16_to_str( local_port, number );
            error_flag = wifly_set_parameter( ctx, WIFLY_CMD_SET_IP_LOCALPORT_PFX, l_trim( r_trim( number ) ) );
        }
        if ( WIFLY_OK == error_flag )
        {
            error_flag = wifly_set_parameter( ctx, WIFLY_CMD_SET_IP_HOST_PFX, peer_ip );
        }
        if ( WIFLY_OK == error_flag )
        {
            uint16_to_str( peer_port, number );
            error_flag = wifly_set_parameter( ctx, WIFLY_CMD_SET_IP_REMOTE_PFX, l_trim( r_trim( number ) ) );
        }
        if ( ( WIFLY_OK == error_flag ) &&
             ( ( protocol != ctx->protocol ) || ( local_port != ctx->local_port ) ) )
        {
            // Reassociate so the RN-131 binds the new protocol and local listening port.
            error_flag = wifly_join_network( ctx );
            if ( WIFLY_OK == error_flag )
            {
                ctx->protocol = protocol;
                ctx->local_port = local_port;
            }
        }
        if ( WIFLY_OK == error_flag )
        {
            if ( WIFLY_PROTOCOL_TCP == protocol )
            {
                strcpy( ctx->command, WIFLY_CMD_OPEN_PFX );
                strcat( ctx->command, peer_ip );
                strcat( ctx->command, " " );
                strcat( ctx->command, l_trim( r_trim( number ) ) );
                error_flag = wifly_send_command( ctx, ctx->command, WIFLY_REPLY_OPEN, WIFLY_CONNECT_TIMEOUT );
            }
            else
            {
                // UDP has no open handshake; leaving Command mode enables the configured data pipe.
                error_flag = wifly_send_command( ctx, WIFLY_CMD_EXIT, WIFLY_REPLY_EXIT, WIFLY_COMMAND_TIMEOUT );
            }
            if ( WIFLY_OK == error_flag )
            {
                ctx->command_mode = 0;
                ctx->socket_open = 1;
            }
        }
    }
    return error_flag;
}

err_t wifly_close_socket ( wifly_t *ctx )
{
    err_t error_flag;

    error_flag = wifly_enter_command( ctx );
    if ( ( WIFLY_OK == error_flag ) && ctx->socket_open && ( WIFLY_PROTOCOL_TCP == ctx->protocol ) )
    {
        error_flag = wifly_send_command( ctx, WIFLY_CMD_CLOSE, WIFLY_REPLY_PROMPT, WIFLY_COMMAND_TIMEOUT );
    }
    if ( WIFLY_OK == error_flag )
    {
        ctx->socket_open = 0;
    }
    return error_flag;
}

err_t wifly_send ( wifly_t *ctx, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = WIFLY_ERROR_ARGUMENT;

    if ( ctx->socket_open && !ctx->command_mode && data_in && len && ( len <= WIFLY_DATA_SIZE ) )
    {
        error_flag = wifly_write_all( ctx, data_in, len );
    }
    return error_flag;
}

err_t wifly_receive ( wifly_t *ctx, uint8_t *data_out, uint16_t capacity )
{
    err_t read_size = WIFLY_ERROR_ARGUMENT;

    if ( ctx->socket_open && !ctx->command_mode && data_out && capacity )
    {
        read_size = uart_bytes_available( &ctx->uart );
        if ( read_size > 0 )
        {
            if ( read_size > capacity )
            {
                read_size = capacity;
            }
            read_size = wifly_generic_read( ctx, data_out, read_size );
            if ( read_size < 0 )
            {
                read_size = WIFLY_ERROR;
            }
        }
    }
    return read_size;
}

err_t wifly_generic_write ( wifly_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t wifly_generic_read ( wifly_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

static err_t wifly_write_all ( wifly_t *ctx, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = WIFLY_OK;
    err_t write_size;
    uint16_t offset = 0;
    uint16_t wait_ms = 0;

    while ( ( offset < len ) && ( wait_ms < WIFLY_COMMAND_TIMEOUT ) )
    {
        write_size = wifly_generic_write( ctx, &data_in[ offset ], len - offset );
        if ( write_size > 0 )
        {
            offset += write_size;
        }
        else
        {
            // A nonblocking UART can reject a write while its transmit ring is full.
            Delay_1ms();
            wait_ms++;
        }
    }
    if ( offset != len )
    {
        error_flag = WIFLY_TIMEOUT;
    }
    return error_flag;
}

static err_t wifly_wait_reply ( wifly_t *ctx, char *expected, uint16_t timeout_ms )
{
    err_t error_flag = WIFLY_TIMEOUT;
    uint16_t wait_ms = 0;
    uint8_t idle_ms = 0;
    uint8_t rx_byte;
    uint8_t matched = 0;
    uint8_t module_error = 0;

    ctx->response_length = 0;
    ctx->response[ 0 ] = 0;
    while ( ( wait_ms < timeout_ms ) && ( idle_ms < WIFLY_REPLY_IDLE_MS ) )
    {
        if ( uart_bytes_available( &ctx->uart ) )
        {
            if ( 1 != wifly_generic_read( ctx, &rx_byte, 1 ) )
            {
                error_flag = WIFLY_ERROR;
                break;
            }
            idle_ms = 0;
            if ( ctx->response_length >= WIFLY_RESPONSE_SIZE - 1 )
            {
                error_flag = WIFLY_ERROR_OVERFLOW;
                break;
            }
            ctx->response[ ctx->response_length++ ] = rx_byte;
            ctx->response[ ctx->response_length ] = 0;
            if ( strstr( ctx->response, expected ) )
            {
                matched = 1;
            }
            if ( strstr( ctx->response, WIFLY_REPLY_ERROR ) ||
                 strstr( ctx->response, WIFLY_REPLY_ERROR_CR ) )
            {
                module_error = 1;
            }
        }
        else
        {
            Delay_1ms();
            wait_ms++;
            // Count the quiet tail only after a token or module error has appeared.
            if ( matched || module_error )
            {
                idle_ms++;
            }
        }
    }
    if ( WIFLY_REPLY_IDLE_MS == idle_ms )
    {
        error_flag = WIFLY_OK;
        if ( module_error )
        {
            error_flag = WIFLY_ERROR_RESPONSE;
        }
    }
    return error_flag;
}

static err_t wifly_enter_command ( wifly_t *ctx )
{
    err_t error_flag = WIFLY_OK;

    if ( !ctx->command_mode )
    {
        // Allow the 128-byte TX ring to drain even at 2400 baud, then exceed the 250 ms guard.
        Delay_1sec();
        uart_clear( &ctx->uart );
        error_flag = wifly_write_all( ctx, ( uint8_t * ) WIFLY_CMD_ESCAPE, 3 );
        if ( WIFLY_OK == error_flag )
        {
            // Do not append CR/LF. The RN-131 requires silence after the three escape characters.
            Delay_100ms();
            Delay_100ms();
            Delay_100ms();
            error_flag = wifly_wait_reply( ctx, WIFLY_REPLY_CMD, WIFLY_COMMAND_TIMEOUT );
        }
        if ( WIFLY_OK == error_flag )
        {
            ctx->command_mode = 1;
        }
    }
    return error_flag;
}

static err_t wifly_set_parameter ( wifly_t *ctx, char *prefix, char *value )
{
    err_t error_flag = WIFLY_ERROR_OVERFLOW;

    if ( strlen( prefix ) + strlen( value ) < WIFLY_COMMAND_SIZE )
    {
        strcpy( ctx->command, prefix );
        strcat( ctx->command, value );
        error_flag = wifly_send_command( ctx, ctx->command, WIFLY_REPLY_AOK, WIFLY_COMMAND_TIMEOUT );
    }
    return error_flag;
}

static err_t wifly_join_network ( wifly_t *ctx )
{
    err_t error_flag;
    uint8_t attempt;
    uint8_t connected = 0;

    error_flag = wifly_send_command( ctx, WIFLY_CMD_LEAVE, WIFLY_REPLY_PROMPT, WIFLY_COMMAND_TIMEOUT );
    if ( WIFLY_OK == error_flag )
    {
        strcpy( ctx->command, WIFLY_CMD_JOIN_PFX );
        strcat( ctx->command, ctx->ssid );
        error_flag = wifly_send_command( ctx, ctx->command, WIFLY_REPLY_PROMPT, WIFLY_CONNECT_TIMEOUT );
    }
    for ( attempt = 0; ( attempt < WIFLY_JOIN_ATTEMPTS ) &&
          ( WIFLY_OK == error_flag ) && !connected; attempt++ )
    {
        // Association and DHCP finish asynchronously; a command prompt alone is not sufficient.
        Delay_1sec();
        error_flag = wifly_send_command( ctx, WIFLY_CMD_SHOW_NET, WIFLY_REPLY_PROMPT, WIFLY_COMMAND_TIMEOUT );
        if ( ( WIFLY_OK == error_flag ) &&
             strstr( ctx->response, WIFLY_STATUS_ASSOC_OK ) &&
             strstr( ctx->response, WIFLY_STATUS_DHCP_OK ) )
        {
            connected = 1;
        }
    }
    if ( ( WIFLY_OK == error_flag ) && !connected )
    {
        error_flag = WIFLY_TIMEOUT;
    }
    if ( WIFLY_OK == error_flag )
    {
        error_flag = wifly_send_command( ctx, WIFLY_CMD_GET_IP, WIFLY_REPLY_PROMPT, WIFLY_COMMAND_TIMEOUT );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
