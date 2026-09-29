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
 * @file devicedrive.c
 * @brief DeviceDrive Click Driver.
 */

#include "devicedrive.h"

/**
 * @brief DeviceDrive command formatting settings.
 * @details JSON envelope and scratch buffer sizes used to format commands. The
 * command-name limit bounds envelope construction; parameter buffers allow quotes
 * and backslashes to be escaped without truncation.
 */
#define DEVICEDRIVE_COMMAND_PREFIX              "{\"devicedrive\":{\"command\":\""
#define DEVICEDRIVE_COMMAND_NAME_SIZE_MAX       32
#define DEVICEDRIVE_NETWORK_PARAMS_SIZE         256
#define DEVICEDRIVE_SERVER_PARAMS_SIZE          544

/**
 * @brief DeviceDrive complete data writing function.
 * @details This function queues data in chunks of up to 64 bytes, retrying partial
 * UART writes until all bytes are queued or the two-second timeout expires.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  0 - Success,
 *         @li @c -2 - UART write timeout.
 * See #err_t definition for detailed explanation.
 * @note Reset the module after a write timeout to discard a partial serial frame.
 */
static err_t devicedrive_write_all ( devicedrive_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief DeviceDrive JSON string quoting function.
 * @details This function quotes a string and escapes embedded quotes and backslashes.
 * @param[in] text : Null-terminated input string.
 * @param[out] quoted : Output buffer for the quoted string.
 * @param[in] size : Output buffer size, including the terminating null byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Control character or insufficient buffer space.
 * See #err_t definition for detailed explanation.
 * @note The output must not be used if an error is returned.
 */
static err_t devicedrive_quote_string ( char *text, char *quoted, uint16_t size );

void devicedrive_cfg_setup ( devicedrive_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t devicedrive_init ( devicedrive_t *ctx, devicedrive_cfg_t *cfg )
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
    digital_out_low( &ctx->rst );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_high( &ctx->en );

    return UART_SUCCESS;
}

err_t devicedrive_generic_write ( devicedrive_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t devicedrive_generic_read ( devicedrive_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

void devicedrive_hw_reset ( devicedrive_t *ctx )
{
    digital_out_low( &ctx->rst );
    digital_out_high( &ctx->en );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    uart_clear( &ctx->uart );
    digital_out_high( &ctx->rst );
}

err_t devicedrive_cmd_run ( devicedrive_t *ctx, char *command )
{
    return devicedrive_cmd_set( ctx, command, "" );
}

err_t devicedrive_cmd_set ( devicedrive_t *ctx, char *command, char *params )
{
    char command_buf[ DEVICEDRIVE_MESSAGE_SIZE_MAX + 1 ];
    size_t command_len;
    size_t params_len;
    size_t command_size;
    size_t index;
    err_t error_flag = DEVICEDRIVE_ERROR;

    if ( command && params )
    {
        command_len = strlen( command );
        params_len = strlen( params );
        command_size = strlen( DEVICEDRIVE_COMMAND_PREFIX ) + command_len + params_len + 3;
        if ( params_len )
        {
            command_size++;
        }
        if ( command_len && ( command_len <= DEVICEDRIVE_COMMAND_NAME_SIZE_MAX ) &&
             ( params_len <= DEVICEDRIVE_MESSAGE_SIZE_MAX ) &&
             ( command_size <= DEVICEDRIVE_MESSAGE_SIZE_MAX ) )
        {
            error_flag = DEVICEDRIVE_OK;
            for ( index = 0; index < command_len; index++ )
            {
                if ( ( ( command[ index ] < 'a' ) || ( command[ index ] > 'z' ) ) && ( command[ index ] != '_' ) )
                {
                    error_flag = DEVICEDRIVE_ERROR;
                }
            }
            if ( DEVICEDRIVE_OK == error_flag )
            {
                // Keep command first: the firmware processes subsequent members as parameters.
                strcpy( command_buf, DEVICEDRIVE_COMMAND_PREFIX );
                strcat( command_buf, command );
                strcat( command_buf, "\"" );
                if ( params_len )
                {
                    strcat( command_buf, "," );
                }
                strcat( command_buf, params );
                strcat( command_buf, "}}" );
                error_flag = devicedrive_send_message( ctx, command_buf, DEVICEDRIVE_SEND_RECEIVE );
            }
        }
    }
    return error_flag;
}

err_t devicedrive_set_network ( devicedrive_t *ctx, char *ssid, char *password )
{
    char quoted_ssid[ 2 * DEVICEDRIVE_SSID_SIZE_MAX + 3 ];
    char quoted_password[ 2 * DEVICEDRIVE_PASSWORD_SIZE_MAX + 3 ];
    char params[ DEVICEDRIVE_NETWORK_PARAMS_SIZE ];
    err_t error_flag = DEVICEDRIVE_ERROR;

    if ( ssid && password )
    {
        if ( strlen( ssid ) && ( strlen( ssid ) <= DEVICEDRIVE_SSID_SIZE_MAX ) &&
             ( strlen( password ) <= DEVICEDRIVE_PASSWORD_SIZE_MAX ) )
        {
            error_flag = devicedrive_quote_string( ssid, quoted_ssid, sizeof( quoted_ssid ) );
            if ( DEVICEDRIVE_OK == error_flag )
            {
                error_flag = devicedrive_quote_string( password, quoted_password, sizeof( quoted_password ) );
            }
            if ( DEVICEDRIVE_OK == error_flag )
            {
                strcpy( params, "\"" DEVICEDRIVE_PARAM_NETWORK_SSID "\":" );
                strcat( params, quoted_ssid );
                strcat( params, ",\"" DEVICEDRIVE_PARAM_NETWORK_PWD "\":" );
                strcat( params, quoted_password );
                error_flag = devicedrive_cmd_set( ctx, DEVICEDRIVE_CMD_SETUP, params );
            }
        }
    }
    return error_flag;
}

err_t devicedrive_set_server ( devicedrive_t *ctx, char *url )
{
    char quoted_url[ 2 * DEVICEDRIVE_URL_SIZE_MAX + 3 ];
    char params[ DEVICEDRIVE_SERVER_PARAMS_SIZE ];
    err_t error_flag = DEVICEDRIVE_ERROR;

    if ( url )
    {
        if ( ( 0 == strncmp( url, "https://", 8 ) ) && ( strlen( url ) > 8 ) &&
             ( strlen( url ) <= DEVICEDRIVE_URL_SIZE_MAX ) )
        {
            error_flag = devicedrive_quote_string( url, quoted_url, sizeof( quoted_url ) );
            if ( DEVICEDRIVE_OK == error_flag )
            {
                strcpy( params, "\"" DEVICEDRIVE_PARAM_MASTER_URL "\":" );
                strcat( params, quoted_url );
                error_flag = devicedrive_cmd_set( ctx, DEVICEDRIVE_CMD_SETUP, params );
            }
        }
    }
    return error_flag;
}

err_t devicedrive_send_message ( devicedrive_t *ctx, char *message, uint8_t mode )
{
    uint8_t ending[ 2 ] = { DEVICEDRIVE_ETX, DEVICEDRIVE_EOT };
    size_t len;
    size_t index;
    err_t error_flag = DEVICEDRIVE_ERROR;

    if ( message && ( mode <= DEVICEDRIVE_SEND_ONLY ) )
    {
        len = strlen( message );
        if ( len && ( len <= DEVICEDRIVE_MESSAGE_SIZE_MAX ) )
        {
            error_flag = DEVICEDRIVE_OK;
            for ( index = 0; index < len; index++ )
            {
                // Reject control bytes that could terminate or corrupt the serial frame.
                if ( ( uint8_t ) message[ index ] < ' ' )
                {
                    error_flag = DEVICEDRIVE_ERROR;
                }
            }
            if ( DEVICEDRIVE_OK == error_flag )
            {
                error_flag = devicedrive_write_all( ctx, ( uint8_t * ) message, ( uint16_t ) len );
            }
            if ( DEVICEDRIVE_OK == error_flag )
            {
                if ( DEVICEDRIVE_SEND_ONLY == mode )
                {
                    error_flag = devicedrive_write_all( ctx, ending, sizeof( ending ) );
                }
                else
                {
                    error_flag = devicedrive_write_all( ctx, &ending[ 1 ], 1 );
                }
            }
        }
    }
    return error_flag;
}

static err_t devicedrive_write_all ( devicedrive_t *ctx, uint8_t *data_in, uint16_t len )
{
    #define WRITE_TIMEOUT_MS        2000
    #define WRITE_CHUNK_SIZE        64

    uint16_t offset = 0;
    uint16_t chunk_size;
    uint16_t elapsed;
    err_t written;
    err_t error_flag = DEVICEDRIVE_ERROR_TIMEOUT;

    for ( elapsed = 0; ( elapsed < WRITE_TIMEOUT_MS ) && ( offset < len ); elapsed++ )
    {
        chunk_size = len - offset;
        if ( chunk_size > WRITE_CHUNK_SIZE )
        {
            chunk_size = WRITE_CHUNK_SIZE;
        }
        written = devicedrive_generic_write( ctx, &data_in[ offset ], chunk_size );
        if ( ( written > 0 ) && ( written <= chunk_size ) )
        {
            offset += written;
        }
        Delay_1ms( );
    }
    if ( offset == len )
    {
        error_flag = DEVICEDRIVE_OK;
    }
    return error_flag;
}

static err_t devicedrive_quote_string ( char *text, char *quoted, uint16_t size )
{
    uint16_t index = 0;
    uint16_t offset = 0;
    err_t error_flag = DEVICEDRIVE_ERROR;

    if ( size >= 3 )
    {
        error_flag = DEVICEDRIVE_OK;
        quoted[ offset++ ] = '"';
        while ( text[ index ] && ( DEVICEDRIVE_OK == error_flag ) )
        {
            if ( ( ( uint8_t ) text[ index ] < ' ' ) || ( offset + 3 >= size ) )
            {
                error_flag = DEVICEDRIVE_ERROR;
            }
            else
            {
                if ( ( '"' == text[ index ] ) || ( '\\' == text[ index ] ) )
                {
                    quoted[ offset++ ] = '\\';
                }
                quoted[ offset++ ] = text[ index++ ];
            }
        }
        quoted[ offset++ ] = '"';
        quoted[ offset ] = 0;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
