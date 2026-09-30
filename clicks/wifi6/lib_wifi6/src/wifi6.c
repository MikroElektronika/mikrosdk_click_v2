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
 * @file wifi6.c
 * @brief WiFi 6 Click Driver.
 */

#include "wifi6.h"

/**
 * @brief WiFi 6 BGAPI frame settings.
 * @details These macros define the WF121 frame header fields, command-route value, and bounded drain buffer.
 */
#define WIFI6_HEADER_SIZE              4
#define WIFI6_HEADER_WIFI              0x08
#define WIFI6_HEADER_TECH_MASK         0x78
#define WIFI6_HEADER_EVENT             0x80
#define WIFI6_HEADER_LENGTH_MASK       0x07
#define WIFI6_ROUTE_BGAPI              0xFF
#define WIFI6_FRAME_DRAIN_BUFFER_SIZE  16

/**
 * @brief WiFi 6 Click IP configuration payload size.
 * @details The WF121 payload contains IPv4 address, netmask, gateway, and DHCP enable fields.
 */
#define WIFI6_IP_CONFIG_SIZE           13

/**
 * @brief WiFi 6 operating settings.
 * @details These macros select normal firmware boot, station operation, DHCP, and radio power management.
 */
#define WIFI6_BOOT_NORMAL              0
#define WIFI6_MODE_STATION             1
#define WIFI6_POWER_ALWAYS_ON          0
#define WIFI6_DHCP_ENABLED             1
#define WIFI6_INTERFACE_WLAN           0

/**
 * @brief WiFi 6 asynchronous event identifiers.
 * @details These macros identify boot, WLAN, network, and endpoint notifications within their BGAPI classes.
 */
#define WIFI6_EVT_BOOT                 0x00
#define WIFI6_EVT_EXCEPTION            0x02
#define WIFI6_EVT_MAC                  0x00
#define WIFI6_EVT_WIFI_ON              0x00
#define WIFI6_EVT_WIFI_OFF             0x01
#define WIFI6_EVT_CONNECTED            0x05
#define WIFI6_EVT_DISCONNECTED         0x06
#define WIFI6_EVT_INTERFACE            0x07
#define WIFI6_EVT_CONNECT_FAILED       0x08
#define WIFI6_EVT_IP_CONFIG            0x00
#define WIFI6_EVT_UDP_DATA             0x04
#define WIFI6_EVT_SYNTAX_ERROR         0x00
#define WIFI6_EVT_DATA                 0x01
#define WIFI6_EVT_STATUS               0x02
#define WIFI6_EVT_CLOSING              0x03
#define WIFI6_EVT_ENDPOINT_ERROR       0x04

/**
 * @brief WiFi 6 context clearing function.
 * @details This function clears cached protocol state without changing the UART or GPIO objects.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return Nothing.
 * @note Used during initialization and software reset.
 */
static void wifi6_clear_state ( wifi6_t *ctx );

/**
 * @brief WiFi 6 little-endian value reading function.
 * @details This function decodes a two-byte BGAPI integer.
 * @param[in] buffer : Pointer to two input bytes.
 * @return Decoded unsigned 16-bit value.
 * @note IPv4 and MAC addresses are byte arrays and do not use this conversion.
 */
static uint16_t wifi6_read_u16 ( uint8_t *buffer );

/**
 * @brief WiFi 6 exact UART reading function.
 * @details This function reads a requested byte count using a shared one-millisecond polling budget.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[out] buffer : Output buffer.
 * @param[in] len : Number of bytes to read.
 * @param[in,out] timeout : Remaining polling budget.
 * @return @li @c 0 - Success,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note The caller keeps module CTS low throughout the frame.
 */
static err_t wifi6_read_bytes ( wifi6_t *ctx, uint8_t *buffer, uint16_t len, uint16_t *timeout );

/**
 * @brief WiFi 6 BGAPI frame reading function.
 * @details This function reads and validates one complete BGAPI header and payload.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in,out] timeout : Remaining polling budget for an incomplete frame.
 * @return @li @c 0 - Frame received,
 *         @li @c 1 - No frame available,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Oversized payloads are drained before reporting an error. CTS is high when this function returns.
 */
static err_t wifi6_read_frame ( wifi6_t *ctx, uint16_t *timeout );

/**
 * @brief WiFi 6 BGAPI frame writing function.
 * @details This function writes a command header followed by its binary arguments.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] command_class : BGAPI command class.
 * @param[in] command_id : BGAPI command identifier.
 * @param[in] buffer : Command arguments, or NULL for an empty command.
 * @param[in] len : Argument length.
 * @return @li @c 0 - Success,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note The Wi-Fi technology bits are present in both commands and events.
 */
static err_t wifi6_write_frame ( wifi6_t *ctx, uint8_t command_class, uint8_t command_id,
                                 uint8_t *buffer, uint16_t len );

/**
 * @brief WiFi 6 event handling function.
 * @details This function decodes the current frame into network, endpoint, and receive-buffer state.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Event handled or ignored,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Network data is queued even when it arrives before a command response.
 */
static err_t wifi6_update_event ( wifi6_t *ctx );

/**
 * @brief WiFi 6 command transaction function.
 * @details This function sends one command and processes interleaved events until its matching response arrives.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] command_class : Expected command and response class.
 * @param[in] command_id : Expected command and response identifier.
 * @param[in] buffer : Command arguments, or NULL.
 * @param[in] len : Argument length.
 * @return @li @c 0 - Matching response received,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Commands are serialized; reset the module after a response timeout before issuing another command.
 */
static err_t wifi6_command ( wifi6_t *ctx, uint8_t command_class, uint8_t command_id,
                             uint8_t *buffer, uint16_t len );

/**
 * @brief WiFi 6 command result checking function.
 * @details This function validates response length and decodes its leading 16-bit module result.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] min_len : Minimum response payload size.
 * @return @li @c 0 - Module accepted the command,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note The password command uses a one-byte result and is checked separately.
 */
static err_t wifi6_check_result ( wifi6_t *ctx, uint16_t min_len );

/**
 * @brief WiFi 6 event flag waiting function.
 * @details This function processes events until the selected context flag is set or its polling budget expires.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in,out] flag : Pointer to the boot, radio-ready, or MAC-valid context flag.
 * @return @li @c 0 - Flag set,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Malformed and non-event frames are discarded while searching for the requested flag.
 * Module-reported errors are returned immediately.
 */
static err_t wifi6_wait_flag ( wifi6_t *ctx, uint8_t *flag );

/**
 * @brief WiFi 6 endpoint activation waiting function.
 * @details This function waits until the selected endpoint permits sending and receiving.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] endpoint : Endpoint identifier returned by the module.
 * @return @li @c 0 - Endpoint active,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Activation and closing events can arrive before the command response assigns the endpoint.
 */
static err_t wifi6_wait_endpoint ( wifi6_t *ctx, uint8_t endpoint );

/**
 * @brief WiFi 6 endpoint closing function.
 * @details This function closes one endpoint and checks the response identifier.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] endpoint : Endpoint identifier.
 * @return @li @c 0 - Endpoint closed,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note WIFI6_ENDPOINT_INVALID requires no command.
 */
static err_t wifi6_close_endpoint ( wifi6_t *ctx, uint8_t endpoint );

/**
 * @brief WiFi 6 endpoint closing acknowledgment function.
 * @details This function acknowledges an endpoint-closing event so the module can reuse its endpoint index.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Event acknowledged or not applicable,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Call only after the command transaction that read the event has completed.
 */
static err_t wifi6_ack_closing_event ( wifi6_t *ctx );

void wifi6_cfg_setup ( wifi6_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Module RTS is a host input; module CTS is a host output.
    cfg->rts = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate  = 115200;
    cfg->data_bit   = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit = UART_PARITY_DEFAULT;
    cfg->stop_bit   = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t wifi6_init ( wifi6_t *ctx, wifi6_cfg_t *cfg )
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

    // Pause module output until the UART reader has enabled reception.
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_high( &ctx->cts );
    digital_in_init( &ctx->rts, cfg->rts );

    wifi6_clear_state( ctx );

    return WIFI6_OK;
}

err_t wifi6_default_cfg ( wifi6_t *ctx )
{
    uint8_t setting;
    err_t error_flag = wifi6_reset( ctx );
    if ( WIFI6_OK == error_flag )
    {
        setting = WIFI6_POWER_ALWAYS_ON;
        error_flag = wifi6_command( ctx, WIFI6_CLASS_SYSTEM, WIFI6_CMD_POWER_SAVE, &setting, 1 );
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_check_result( ctx, 2 );
        }
    }

    if ( WIFI6_OK == error_flag )
    {
        setting = WIFI6_MODE_STATION;
        error_flag = wifi6_command( ctx, WIFI6_CLASS_SME, WIFI6_CMD_SET_MODE, &setting, 1 );
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_check_result( ctx, 2 );
        }
    }

    if ( WIFI6_OK == error_flag )
    {
        // Keep address, netmask, and gateway unset; DHCP occupies the final payload byte.
        memset( ctx->frame, 0, WIFI6_IP_CONFIG_SIZE );
        ctx->frame[ WIFI6_IP_CONFIG_SIZE - 1 ] = WIFI6_DHCP_ENABLED;
        error_flag = wifi6_command( ctx, WIFI6_CLASS_TCPIP, WIFI6_CMD_IP_CONFIG,
                                    ctx->frame, WIFI6_IP_CONFIG_SIZE );
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_check_result( ctx, 2 );
        }
    }

    if ( WIFI6_OK == error_flag )
    {
        error_flag = wifi6_command( ctx, WIFI6_CLASS_SME, WIFI6_CMD_WIFI_ON, NULL, 0 );
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_check_result( ctx, 2 );
        }
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_wait_flag( ctx, &ctx->radio_on );
        }
    }

    if ( WIFI6_OK == error_flag )
    {
        setting = WIFI6_INTERFACE_WLAN;
        ctx->mac_valid = 0;
        error_flag = wifi6_command( ctx, WIFI6_CLASS_CONFIG, WIFI6_CMD_GET_MAC, &setting, 1 );
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_check_result( ctx, 3 );
        }
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_wait_flag( ctx, &ctx->mac_valid );
        }
    }
    return error_flag;
}

err_t wifi6_reset ( wifi6_t *ctx )
{
    uint8_t boot_mode = WIFI6_BOOT_NORMAL;
    err_t error_flag;

    // Prefer the module's cold-start boot event; reset only if it was missed or invalid.
    if ( !ctx->ready )
    {
        error_flag = wifi6_wait_flag( ctx, &ctx->ready );
        if ( WIFI6_OK == error_flag )
        {
            return WIFI6_OK;
        }
    }

    digital_out_high( &ctx->cts );
    Delay_1ms( );
    uart_clear( &ctx->uart );
    wifi6_clear_state( ctx );

    // Software reset has no response. Readiness is established by the boot event.
    error_flag = wifi6_write_frame( ctx, WIFI6_CLASS_SYSTEM, WIFI6_CMD_RESET, &boot_mode, 1 );
    if ( WIFI6_OK == error_flag )
    {
        // The reset frame has no response; give the module time to start emitting system_boot.
        Delay_1ms( );
        error_flag = wifi6_wait_flag( ctx, &ctx->ready );
    }
    return error_flag;
}

err_t wifi6_connect ( wifi6_t *ctx, char *ssid, char *password )
{
    uint16_t length;
    err_t error_flag = WIFI6_ARGUMENT_ERROR;

    if ( ssid && password && ctx->radio_on &&
         ( WIFI6_ENDPOINT_INVALID == ctx->tx_endpoint ) &&
         ( WIFI6_ENDPOINT_INVALID == ctx->rx_endpoint ) )
    {
        length = strlen( ssid );
        if ( length && ( length <= WIFI6_SSID_SIZE ) &&
             ( strlen( password ) <= WIFI6_PASSWORD_SIZE ) )
        {
            error_flag = WIFI6_OK;

            // Empty passwords are not sent: an open access point does not authenticate with a PSK.
            length = strlen( password );
            if ( length )
            {
                memmove( &ctx->frame[ 1 ], password, length );
                ctx->frame[ 0 ] = ( uint8_t ) length;
                error_flag = wifi6_command( ctx, WIFI6_CLASS_SME, WIFI6_CMD_SET_PASSWORD,
                                            ctx->frame, length + 1 );
                if ( WIFI6_OK == error_flag )
                {
                    if ( ctx->frame_len != 1 )
                    {
                        error_flag = WIFI6_PROTOCOL_ERROR;
                    }
                    else
                    {
                        ctx->module_error = ctx->frame[ 0 ];
                        if ( ctx->module_error )
                        {
                            error_flag = WIFI6_MODULE_ERROR;
                        }
                    }
                }
            }

            if ( WIFI6_OK == error_flag )
            {
                memset( &ctx->network, 0, sizeof( ctx->network ) );
                length = strlen( ssid );
                memmove( &ctx->frame[ 1 ], ssid, length );
                ctx->frame[ 0 ] = ( uint8_t ) length;
                error_flag = wifi6_command( ctx, WIFI6_CLASS_SME, WIFI6_CMD_CONNECT_SSID,
                                            ctx->frame, length + 1 );
                if ( WIFI6_OK == error_flag )
                {
                    error_flag = wifi6_check_result( ctx, 9 );
                }
            }
        }
    }
    return error_flag;
}

err_t wifi6_process ( wifi6_t *ctx )
{
    uint16_t timeout = WIFI6_FRAME_TIMEOUT_MS;
    err_t error_flag = wifi6_read_frame( ctx, &timeout );

    if ( WIFI6_OK == error_flag )
    {
        if ( !ctx->frame_event )
        {
            return WIFI6_PROTOCOL_ERROR;
        }
        error_flag = wifi6_update_event( ctx );
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_ack_closing_event( ctx );
        }
    }
    return error_flag;
}

err_t wifi6_open_socket ( wifi6_t *ctx, uint8_t protocol, uint16_t local_port,
                          uint8_t *peer_ip, uint16_t peer_port )
{
    uint8_t args[ 7 ];
    uint8_t command_id;
    err_t error_flag;

    if ( !peer_ip || !peer_port || !ctx->network.up || !ctx->network.ip_acquired ||
         ( ( protocol != WIFI6_PROTOCOL_TCP ) && ( protocol != WIFI6_PROTOCOL_UDP ) ) ||
         ( ( protocol == WIFI6_PROTOCOL_UDP ) && !local_port ) ||
         ( WIFI6_ENDPOINT_INVALID != ctx->tx_endpoint ) ||
         ( WIFI6_ENDPOINT_INVALID != ctx->rx_endpoint ) )
    {
        return WIFI6_ARGUMENT_ERROR;
    }

    ctx->protocol = protocol;
    memcpy( ctx->peer_ip, peer_ip, 4 );
    ctx->peer_port = peer_port;
    ctx->rx_length = 0;
    ctx->rx_pending = 0;
    memset( ctx->ep_active, 0, sizeof( ctx->ep_active ) );
    memset( ctx->ep_closed, 0, sizeof( ctx->ep_closed ) );

    if ( WIFI6_PROTOCOL_UDP == protocol )
    {
        // WF121 UDP clients only transmit. A listener receives replies on the chosen source port.
        args[ 0 ] = ( uint8_t ) local_port;
        args[ 1 ] = ( uint8_t ) ( local_port >> 8 );
        args[ 2 ] = WIFI6_ROUTE_BGAPI;
        error_flag = wifi6_command( ctx, WIFI6_CLASS_TCPIP, WIFI6_CMD_UDP_SERVER, args, 3 );
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_check_result( ctx, 3 );
        }
        if ( WIFI6_OK != error_flag )
        {
            return error_flag;
        }
        ctx->rx_endpoint = ctx->frame[ 2 ];
        error_flag = wifi6_wait_endpoint( ctx, ctx->rx_endpoint );
        if ( WIFI6_OK != error_flag )
        {
            return error_flag;
        }
    }

    // IPv4 bytes stay in network order; the port is a little-endian BGAPI integer.
    memcpy( args, peer_ip, 4 );
    args[ 4 ] = ( uint8_t ) peer_port;
    args[ 5 ] = ( uint8_t ) ( peer_port >> 8 );
    args[ 6 ] = WIFI6_ROUTE_BGAPI;
    command_id = WIFI6_CMD_TCP_CONNECT;
    if ( WIFI6_PROTOCOL_UDP == protocol )
    {
        command_id = WIFI6_CMD_UDP_CONNECT;
    }
    error_flag = wifi6_command( ctx, WIFI6_CLASS_TCPIP, command_id, args, sizeof( args ) );
    if ( WIFI6_OK == error_flag )
    {
        error_flag = wifi6_check_result( ctx, 3 );
    }
    if ( WIFI6_OK != error_flag )
    {
        return error_flag;
    }
    ctx->tx_endpoint = ctx->frame[ 2 ];
    if ( WIFI6_PROTOCOL_TCP == protocol )
    {
        ctx->rx_endpoint = ctx->tx_endpoint;
    }
    error_flag = wifi6_wait_endpoint( ctx, ctx->tx_endpoint );
    if ( ( WIFI6_OK == error_flag ) && ( WIFI6_PROTOCOL_UDP == protocol ) )
    {
        args[ 0 ] = ctx->tx_endpoint;
        args[ 1 ] = ( uint8_t ) local_port;
        args[ 2 ] = ( uint8_t ) ( local_port >> 8 );
        error_flag = wifi6_command( ctx, WIFI6_CLASS_TCPIP, WIFI6_CMD_UDP_BIND, args, 3 );
        if ( WIFI6_OK == error_flag )
        {
            error_flag = wifi6_check_result( ctx, 2 );
        }
    }
    return error_flag;
}

err_t wifi6_send ( wifi6_t *ctx, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = WIFI6_ARGUMENT_ERROR;
    uint8_t mask;

    if ( data_in && len && ( len <= WIFI6_DATA_SIZE ) &&
         ( WIFI6_ENDPOINT_INVALID != ctx->tx_endpoint ) )
    {
        error_flag = wifi6_process( ctx );
        if ( error_flag >= 0 )
        {
            mask = ( uint8_t ) ( 1u << ( ctx->tx_endpoint & 7 ) );
            if ( ctx->ep_closed[ ctx->tx_endpoint >> 3 ] & mask )
            {
                error_flag = WIFI6_CLOSED;
            }
            else if ( !( ctx->ep_active[ ctx->tx_endpoint >> 3 ] & mask ) )
            {
                error_flag = WIFI6_NO_DATA;
            }
            else
            {
                memmove( &ctx->frame[ 2 ], data_in, len );
                ctx->frame[ 0 ] = ctx->tx_endpoint;
                ctx->frame[ 1 ] = ( uint8_t ) len;
                error_flag = wifi6_command( ctx, WIFI6_CLASS_ENDPOINT, WIFI6_CMD_SEND,
                                            ctx->frame, len + 2 );
                if ( WIFI6_OK == error_flag )
                {
                    error_flag = wifi6_check_result( ctx, 3 );
                    if ( ( WIFI6_OK == error_flag ) && ( ctx->frame[ 2 ] != ctx->tx_endpoint ) )
                    {
                        error_flag = WIFI6_PROTOCOL_ERROR;
                    }
                }
            }
        }
    }
    return error_flag;
}

err_t wifi6_receive ( wifi6_t *ctx, uint8_t *data_out, uint16_t capacity, wifi6_packet_t *packet )
{
    err_t error_flag;
    uint16_t length;

    if ( !data_out || !capacity || !packet || ( WIFI6_ENDPOINT_INVALID == ctx->rx_endpoint ) )
    {
        return WIFI6_ARGUMENT_ERROR;
    }
    packet->length = 0;
    if ( !ctx->rx_pending )
    {
        error_flag = wifi6_process( ctx );
        if ( error_flag < 0 )
        {
            return error_flag;
        }
    }
    if ( ctx->rx_pending )
    {
        length = ctx->rx_length;
        if ( length > capacity )
        {
            if ( WIFI6_PROTOCOL_UDP == ctx->protocol )
            {
                return WIFI6_BUFFER_ERROR;
            }
            length = capacity;
        }
        memcpy( data_out, ctx->rx_data, length );
        packet->length = length;
        memcpy( packet->ip, ctx->peer_ip, 4 );
        packet->port = ctx->peer_port;
        ctx->rx_length -= length;
        memmove( ctx->rx_data, &ctx->rx_data[ length ], ctx->rx_length );
        ctx->rx_pending = ( ctx->rx_length != 0 );
        return WIFI6_OK;
    }
    if ( ctx->ep_closed[ ctx->rx_endpoint >> 3 ] & ( 1u << ( ctx->rx_endpoint & 7 ) ) )
    {
        return WIFI6_CLOSED;
    }
    return WIFI6_NO_DATA;
}

err_t wifi6_close_socket ( wifi6_t *ctx )
{
    uint8_t tx_endpoint = ctx->tx_endpoint;
    err_t error_flag = wifi6_close_endpoint( ctx, tx_endpoint );

    if ( WIFI6_OK != error_flag )
    {
        return error_flag;
    }
    ctx->tx_endpoint = WIFI6_ENDPOINT_INVALID;
    if ( ctx->rx_endpoint != tx_endpoint )
    {
        error_flag = wifi6_close_endpoint( ctx, ctx->rx_endpoint );
    }
    if ( WIFI6_OK == error_flag )
    {
        ctx->rx_endpoint = WIFI6_ENDPOINT_INVALID;
        ctx->rx_length = 0;
        ctx->rx_pending = 0;
    }
    return error_flag;
}

err_t wifi6_generic_write ( wifi6_t *ctx, uint8_t *data_in, uint16_t len )
{
    uint16_t index;
    uint16_t timeout = WIFI6_TIMEOUT_MS;
    uint16_t pace;
    int32_t written;

    if ( !data_in && len )
    {
        return WIFI6_ARGUMENT_ERROR;
    }
    for ( index = 0; index < len; index++ )
    {
        while ( digital_in_read( &ctx->rts ) )
        {
            if ( !timeout )
            {
                return WIFI6_TIMEOUT;
            }
            Delay_1ms( );
            timeout--;
        }
        written = uart_write( &ctx->uart, &data_in[ index ], 1 );
        if ( written != 1 )
        {
            return WIFI6_ERROR;
        }
        // uart_write queues bytes; pacing prevents a whole frame from bypassing RTS.
        Delay_1ms( );
    }
    return ( err_t ) len;
}

err_t wifi6_generic_read ( wifi6_t *ctx, uint8_t *data_out, uint16_t len )
{
    err_t count;

    if ( !data_out || !len )
    {
        return WIFI6_ARGUMENT_ERROR;
    }
    // Prime UART reception before lowering CTS, including on the first read after initialization.
    count = uart_read( &ctx->uart, data_out, len );
    if ( 0 == count )
    {
        digital_out_low( &ctx->cts );
        Delay_1ms( );
        count = uart_read( &ctx->uart, data_out, len );
        digital_out_high( &ctx->cts );
    }
    return count;
}

static void wifi6_clear_state ( wifi6_t *ctx )
{
    memset( &ctx->network, 0, sizeof( ctx->network ) );
    memset( &ctx->version, 0, sizeof( ctx->version ) );
    memset( ctx->ep_active, 0, sizeof( ctx->ep_active ) );
    memset( ctx->ep_closed, 0, sizeof( ctx->ep_closed ) );
    memset( ctx->mac, 0, sizeof( ctx->mac ) );
    ctx->ready = 0;
    ctx->radio_on = 0;
    ctx->mac_valid = 0;
    ctx->module_error = 0;
    ctx->tx_endpoint = WIFI6_ENDPOINT_INVALID;
    ctx->rx_endpoint = WIFI6_ENDPOINT_INVALID;
    ctx->protocol = WIFI6_PROTOCOL_TCP;
    ctx->rx_length = 0;
    ctx->rx_pending = 0;
    ctx->frame_len = 0;
}

static uint16_t wifi6_read_u16 ( uint8_t *buffer )
{
    return ( uint16_t ) buffer[ 0 ] | ( ( uint16_t ) buffer[ 1 ] << 8 );
}

static err_t wifi6_read_bytes ( wifi6_t *ctx, uint8_t *buffer, uint16_t len, uint16_t *timeout )
{
    uint16_t offset = 0;
    int32_t count;

    while ( offset < len )
    {
        count = uart_read( &ctx->uart, &buffer[ offset ], len - offset );
        if ( count < 0 )
        {
            return WIFI6_ERROR;
        }
        if ( count > 0 )
        {
            offset += ( uint16_t ) count;
        }
        else
        {
            if ( !*timeout )
            {
                return WIFI6_TIMEOUT;
            }
            Delay_1ms( );
            ( *timeout )--;
        }
    }
    return WIFI6_OK;
}

static err_t wifi6_read_frame ( wifi6_t *ctx, uint16_t *timeout )
{
    uint8_t header[ WIFI6_HEADER_SIZE ];
    uint8_t discard[ WIFI6_FRAME_DRAIN_BUFFER_SIZE ];
    uint16_t remaining;
    uint16_t chunk;
    int32_t count;
    err_t error_flag;

    count = uart_read( &ctx->uart, header, 1 );
    digital_out_low( &ctx->cts );
    if ( 0 == count )
    {
        if ( !*timeout )
        {
            digital_out_high( &ctx->cts );
            return WIFI6_TIMEOUT;
        }
        Delay_1ms( );
        ( *timeout )--;
        count = uart_read( &ctx->uart, header, 1 );
    }
    if ( count <= 0 )
    {
        digital_out_high( &ctx->cts );
        if ( count < 0 )
        {
            return WIFI6_ERROR;
        }
        return WIFI6_NO_DATA;
    }
    if ( ( header[ 0 ] & WIFI6_HEADER_TECH_MASK ) != WIFI6_HEADER_WIFI )
    {
        digital_out_high( &ctx->cts );
        return WIFI6_PROTOCOL_ERROR;
    }

    error_flag = wifi6_read_bytes( ctx, &header[ 1 ], WIFI6_HEADER_SIZE - 1, timeout );
    if ( WIFI6_OK == error_flag )
    {
        ctx->frame_event = header[ 0 ] & WIFI6_HEADER_EVENT;
        ctx->frame_class = header[ 2 ];
        ctx->frame_id = header[ 3 ];
        ctx->frame_len = ( ( uint16_t ) ( header[ 0 ] & WIFI6_HEADER_LENGTH_MASK ) << 8 ) | header[ 1 ];
        if ( ctx->frame_len <= WIFI6_FRAME_SIZE )
        {
            error_flag = wifi6_read_bytes( ctx, ctx->frame, ctx->frame_len, timeout );
        }
        else
        {
            // Finish consuming the frame; never treat discarded payload bytes as a new header.
            remaining = ctx->frame_len;
            while ( remaining && ( WIFI6_OK == error_flag ) )
            {
                chunk = remaining;
                if ( chunk > sizeof( discard ) )
                {
                    chunk = sizeof( discard );
                }
                error_flag = wifi6_read_bytes( ctx, discard, chunk, timeout );
                remaining -= chunk;
            }
            if ( WIFI6_OK == error_flag )
            {
                error_flag = WIFI6_BUFFER_ERROR;
            }
        }
    }
    digital_out_high( &ctx->cts );
    return error_flag;
}

static err_t wifi6_write_frame ( wifi6_t *ctx, uint8_t command_class, uint8_t command_id,
                                 uint8_t *buffer, uint16_t len )
{
    uint8_t header[ WIFI6_HEADER_SIZE ];
    err_t error_flag;

    header[ 0 ] = WIFI6_HEADER_WIFI | ( uint8_t ) ( len >> 8 );
    header[ 1 ] = ( uint8_t ) len;
    header[ 2 ] = command_class;
    header[ 3 ] = command_id;
    error_flag = wifi6_generic_write( ctx, header, sizeof( header ) );
    if ( error_flag < 0 )
    {
        return error_flag;
    }
    if ( len )
    {
        error_flag = wifi6_generic_write( ctx, buffer, len );
    }
    if ( error_flag < 0 )
    {
        return error_flag;
    }
    return WIFI6_OK;
}

static err_t wifi6_update_event ( wifi6_t *ctx )
{
    uint8_t *payload = ctx->frame;
    uint8_t endpoint;
    uint8_t mask;
    uint16_t length;
    uint8_t was_ready;

    if ( WIFI6_CLASS_SYSTEM == ctx->frame_class )
    {
        if ( WIFI6_EVT_BOOT == ctx->frame_id )
        {
            if ( ctx->frame_len < 14 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            was_ready = ctx->ready;
            wifi6_clear_state( ctx );
            ctx->version.major = wifi6_read_u16( payload );
            ctx->version.minor = wifi6_read_u16( &payload[ 2 ] );
            ctx->version.patch = wifi6_read_u16( &payload[ 4 ] );
            ctx->version.build = wifi6_read_u16( &payload[ 6 ] );
            ctx->ready = 1;
            if ( was_ready )
            {
                return WIFI6_RESTARTED;
            }
        }
        else if ( WIFI6_EVT_EXCEPTION == ctx->frame_id )
        {
            return WIFI6_MODULE_ERROR;
        }
    }
    else if ( WIFI6_CLASS_CONFIG == ctx->frame_class )
    {
        if ( WIFI6_EVT_MAC == ctx->frame_id )
        {
            if ( ctx->frame_len < 7 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            if ( WIFI6_INTERFACE_WLAN == payload[ 0 ] )
            {
                memcpy( ctx->mac, &payload[ 1 ], 6 );
                ctx->mac_valid = 1;
            }
        }
    }
    else if ( WIFI6_CLASS_SME == ctx->frame_class )
    {
        if ( ( WIFI6_EVT_WIFI_ON == ctx->frame_id ) || ( WIFI6_EVT_WIFI_OFF == ctx->frame_id ) )
        {
            if ( ctx->frame_len < 2 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            ctx->module_error = wifi6_read_u16( payload );
            ctx->radio_on = 0;
            if ( ctx->module_error )
            {
                return WIFI6_MODULE_ERROR;
            }
            if ( WIFI6_EVT_WIFI_ON == ctx->frame_id )
            {
                ctx->radio_on = 1;
            }
            else
            {
                memset( &ctx->network, 0, sizeof( ctx->network ) );
            }
        }
        else if ( WIFI6_EVT_CONNECTED == ctx->frame_id )
        {
            if ( ctx->frame_len < 8 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            if ( WIFI6_INTERFACE_WLAN == payload[ 1 ] )
            {
                ctx->network.connected = ( 0 == payload[ 0 ] );
            }
        }
        else if ( WIFI6_EVT_INTERFACE == ctx->frame_id )
        {
            if ( ctx->frame_len < 2 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            if ( WIFI6_INTERFACE_WLAN == payload[ 0 ] )
            {
                ctx->network.up = payload[ 1 ];
                if ( !ctx->network.up )
                {
                    ctx->network.ip_acquired = 0;
                }
            }
        }
        else if ( ( WIFI6_EVT_DISCONNECTED == ctx->frame_id ) ||
                  ( WIFI6_EVT_CONNECT_FAILED == ctx->frame_id ) )
        {
            if ( ctx->frame_len < 3 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            if ( WIFI6_INTERFACE_WLAN == payload[ 2 ] )
            {
                memset( &ctx->network, 0, sizeof( ctx->network ) );
                ctx->module_error = wifi6_read_u16( payload );
                return WIFI6_MODULE_ERROR;
            }
        }
    }
    else if ( WIFI6_CLASS_TCPIP == ctx->frame_class )
    {
        if ( WIFI6_EVT_IP_CONFIG == ctx->frame_id )
        {
            if ( ctx->frame_len < 13 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            memcpy( ctx->network.ip, payload, 4 );
            memcpy( ctx->network.netmask, &payload[ 4 ], 4 );
            memcpy( ctx->network.gateway, &payload[ 8 ], 4 );
            ctx->network.ip_acquired = ( payload[ 0 ] | payload[ 1 ] | payload[ 2 ] | payload[ 3 ] ) != 0;
        }
        else if ( WIFI6_EVT_UDP_DATA == ctx->frame_id )
        {
            if ( ctx->frame_len < 9 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            length = wifi6_read_u16( &payload[ 7 ] );
            if ( length != ctx->frame_len - 9 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            if ( ( WIFI6_PROTOCOL_UDP == ctx->protocol ) && ( payload[ 0 ] == ctx->rx_endpoint ) &&
                 ( 0 == memcmp( &payload[ 1 ], ctx->peer_ip, 4 ) ) &&
                 ( wifi6_read_u16( &payload[ 5 ] ) == ctx->peer_port ) )
            {
                if ( ctx->rx_pending || ( length > WIFI6_DATA_SIZE ) )
                {
                    return WIFI6_BUFFER_ERROR;
                }
                memcpy( ctx->rx_data, &payload[ 9 ], length );
                ctx->rx_length = length;
                ctx->rx_pending = 1;
            }
        }
    }
    else if ( WIFI6_CLASS_ENDPOINT == ctx->frame_class )
    {
        if ( WIFI6_EVT_DATA == ctx->frame_id )
        {
            if ( ( ctx->frame_len < 2 ) || ( payload[ 1 ] != ctx->frame_len - 2 ) )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            if ( ( WIFI6_PROTOCOL_TCP == ctx->protocol ) && ( payload[ 0 ] == ctx->rx_endpoint ) )
            {
                length = payload[ 1 ];
                if ( length > WIFI6_DATA_SIZE - ctx->rx_length )
                {
                    return WIFI6_BUFFER_ERROR;
                }
                memcpy( &ctx->rx_data[ ctx->rx_length ], &payload[ 2 ], length );
                ctx->rx_length += length;
                ctx->rx_pending = ( ctx->rx_length != 0 );
            }
        }
        else if ( WIFI6_EVT_STATUS == ctx->frame_id )
        {
            if ( ctx->frame_len < 8 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            endpoint = payload[ 0 ];
            mask = ( uint8_t ) ( 1u << ( endpoint & 7 ) );
            if ( payload[ 7 ] )
            {
                ctx->ep_active[ endpoint >> 3 ] |= mask;
                ctx->ep_closed[ endpoint >> 3 ] &= ( uint8_t ) ~mask;
            }
            else
            {
                ctx->ep_active[ endpoint >> 3 ] &= ( uint8_t ) ~mask;
            }
        }
        else if ( ( WIFI6_EVT_CLOSING == ctx->frame_id ) || ( WIFI6_EVT_ENDPOINT_ERROR == ctx->frame_id ) )
        {
            if ( ctx->frame_len < 3 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            endpoint = payload[ 2 ];
            mask = ( uint8_t ) ( 1u << ( endpoint & 7 ) );
            ctx->ep_closed[ endpoint >> 3 ] |= mask;
            ctx->ep_active[ endpoint >> 3 ] &= ( uint8_t ) ~mask;
            if ( ( endpoint == ctx->tx_endpoint ) || ( endpoint == ctx->rx_endpoint ) )
            {
                ctx->module_error = wifi6_read_u16( payload );
                if ( WIFI6_EVT_ENDPOINT_ERROR == ctx->frame_id )
                {
                    return WIFI6_MODULE_ERROR;
                }
            }
        }
        else if ( WIFI6_EVT_SYNTAX_ERROR == ctx->frame_id )
        {
            if ( ctx->frame_len < 3 )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            ctx->module_error = wifi6_read_u16( payload );
            return WIFI6_MODULE_ERROR;
        }
    }
    return WIFI6_OK;
}

static err_t wifi6_command ( wifi6_t *ctx, uint8_t command_class, uint8_t command_id,
                             uint8_t *buffer, uint16_t len )
{
    uint16_t timeout = WIFI6_TIMEOUT_MS;
    err_t error_flag = wifi6_write_frame( ctx, command_class, command_id, buffer, len );

    if ( WIFI6_OK != error_flag )
    {
        return error_flag;
    }

    // Give the WF121 one character interval to finish the request before polling its response.
    Delay_1ms( );
    while ( timeout )
    {
        error_flag = wifi6_read_frame( ctx, &timeout );
        if ( error_flag < 0 )
        {
            return error_flag;
        }
        if ( WIFI6_OK == error_flag )
        {
            if ( !ctx->frame_event )
            {
                if ( ( ctx->frame_class == command_class ) && ( ctx->frame_id == command_id ) )
                {
                    return WIFI6_OK;
                }
                return WIFI6_PROTOCOL_ERROR;
            }
            error_flag = wifi6_update_event( ctx );
            if ( WIFI6_OK != error_flag )
            {
                return error_flag;
            }
        }
        if ( timeout )
        {
            Delay_1ms( );
            timeout--;
        }
    }
    return WIFI6_TIMEOUT;
}

static err_t wifi6_check_result ( wifi6_t *ctx, uint16_t min_len )
{
    if ( ctx->frame_len < min_len )
    {
        return WIFI6_PROTOCOL_ERROR;
    }
    ctx->module_error = wifi6_read_u16( ctx->frame );
    if ( ctx->module_error )
    {
        return WIFI6_MODULE_ERROR;
    }
    return WIFI6_OK;
}

static err_t wifi6_wait_flag ( wifi6_t *ctx, uint8_t *flag )
{
    uint16_t timeout = WIFI6_TIMEOUT_MS;
    err_t error_flag;

    while ( !*flag && timeout )
    {
        error_flag = wifi6_read_frame( ctx, &timeout );
        if ( ( error_flag < 0 ) && ( WIFI6_PROTOCOL_ERROR != error_flag ) )
        {
            return error_flag;
        }
        if ( WIFI6_OK == error_flag )
        {
            if ( ctx->frame_event )
            {
                error_flag = wifi6_update_event( ctx );
                if ( ( error_flag < 0 ) && ( WIFI6_PROTOCOL_ERROR != error_flag ) )
                {
                    return error_flag;
                }
            }
        }
        if ( timeout )
        {
            Delay_1ms( );
            timeout--;
        }
    }
    if ( *flag )
    {
        return WIFI6_OK;
    }
    return WIFI6_TIMEOUT;
}

static err_t wifi6_wait_endpoint ( wifi6_t *ctx, uint8_t endpoint )
{
    uint16_t timeout = WIFI6_CONNECT_TIMEOUT_MS;
    uint8_t mask = ( uint8_t ) ( 1u << ( endpoint & 7 ) );
    err_t error_flag;

    if ( WIFI6_ENDPOINT_INVALID == endpoint )
    {
        return WIFI6_PROTOCOL_ERROR;
    }
    while ( timeout )
    {
        if ( ctx->ep_closed[ endpoint >> 3 ] & mask )
        {
            error_flag = wifi6_close_endpoint( ctx, endpoint );
            if ( WIFI6_OK != error_flag )
            {
                return error_flag;
            }
            return WIFI6_CLOSED;
        }
        if ( ctx->ep_active[ endpoint >> 3 ] & mask )
        {
            return WIFI6_OK;
        }
        error_flag = wifi6_read_frame( ctx, &timeout );
        if ( error_flag < 0 )
        {
            return error_flag;
        }
        if ( WIFI6_OK == error_flag )
        {
            if ( !ctx->frame_event )
            {
                return WIFI6_PROTOCOL_ERROR;
            }
            error_flag = wifi6_update_event( ctx );
            if ( WIFI6_OK != error_flag )
            {
                return error_flag;
            }
            if ( ( WIFI6_CLASS_ENDPOINT == ctx->frame_class ) &&
                 ( WIFI6_EVT_CLOSING == ctx->frame_id ) )
            {
                error_flag = wifi6_ack_closing_event( ctx );
                if ( WIFI6_OK != error_flag )
                {
                    return error_flag;
                }
                if ( ctx->ep_closed[ endpoint >> 3 ] & mask )
                {
                    return WIFI6_CLOSED;
                }
            }
        }
        if ( timeout )
        {
            Delay_1ms( );
            timeout--;
        }
    }
    return WIFI6_TIMEOUT;
}

static err_t wifi6_close_endpoint ( wifi6_t *ctx, uint8_t endpoint )
{
    err_t error_flag;

    if ( WIFI6_ENDPOINT_INVALID == endpoint )
    {
        return WIFI6_OK;
    }
    error_flag = wifi6_command( ctx, WIFI6_CLASS_ENDPOINT, WIFI6_CMD_CLOSE, &endpoint, 1 );
    if ( WIFI6_OK == error_flag )
    {
        error_flag = wifi6_check_result( ctx, 3 );
        if ( ( WIFI6_OK == error_flag ) && ( ctx->frame[ 2 ] != endpoint ) )
        {
            error_flag = WIFI6_PROTOCOL_ERROR;
        }
    }
    return error_flag;
}

static err_t wifi6_ack_closing_event ( wifi6_t *ctx )
{
    if ( ctx->frame_event && ( WIFI6_CLASS_ENDPOINT == ctx->frame_class ) &&
         ( WIFI6_EVT_CLOSING == ctx->frame_id ) )
    {
        // The endpoint ID is in the final byte of the closing event payload.
        return wifi6_close_endpoint( ctx, ctx->frame[ 2 ] );
    }
    return WIFI6_OK;
}

// ------------------------------------------------------------------------- END
