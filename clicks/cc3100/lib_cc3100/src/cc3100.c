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
 * @file cc3100.c
 * @brief CC3100 Click Driver.
 */

#include "cc3100.h"

/**
 * @brief CC3100 Click SimpleLink frame format constants.
 * @details These constants define synchronization words, response headers, and frame alignment
 * for the binary host interface. Protocol fields use little-endian byte order.
 * @note CC3100_SYNC_SCAN_SIZE bounds synchronization recovery; payload capacity is set separately.
 */
#define CC3100_SPI_DUMMY             0xFF
#define CC3100_SYNC_WORD             0xABCDDCBAul
#define CC3100_SYNC_BUG_MASK         0x7FFF7F7Ful
#define CC3100_SYNC_SEQ_FLAG         0x04
#define CC3100_SYNC_SCAN_SIZE        1024
#define CC3100_RESPONSE_HEADER       8
#define CC3100_RESPONSE_EXTRA        4
#define CC3100_RESPONSE_MASK         0x7FFF
#define CC3100_OPCODE_SYNC           0x0400

/**
 * @brief CC3100 Click socket flow-control settings.
 * @details These constants define valid socket descriptors, reserved transmit credits, and connect wait time.
 * @note Reserved credits leave NWP buffers available for commands and flow-control traffic.
 */
#define CC3100_SOCKET_ID_MASK        0x0F
#define CC3100_SOCKET_COUNT          8
#define CC3100_TX_RESERVED           2
#define CC3100_CONNECT_TIMEOUT_MS    30000

/**
 * @brief CC3100 Click network and socket configuration constants.
 * @details These constants identify SimpleLink settings, roles, address family, socket types, and options.
 * @note Values are part of the NWP protocol and must match the SimpleLink definitions.
 */
#define CC3100_CFG_MAC               2
#define CC3100_CFG_IPV4              3
#define CC3100_CFG_DHCP              4
#define CC3100_CFG_GENERAL           1
#define CC3100_CFG_VERSION           12
#define CC3100_POLICY_CONNECTION     0x10
#define CC3100_ROLE_STATION          0
#define CC3100_ROLE_P2P              1
#define CC3100_ROLE_AP               2
#define CC3100_INIT_STATION          1
#define CC3100_INIT_AP               3
#define CC3100_INIT_P2P              5
#define CC3100_AF_INET               2
#define CC3100_SOCK_STREAM           1
#define CC3100_SOCK_DGRAM            2
#define CC3100_SOL_SOCKET            1
#define CC3100_SO_NONBLOCKING        24

/**
 * @brief CC3100 Click nonblocking receive idle status.
 * @details This status is returned when the socket receive request has no data available.
 * @note cc3100_receive maps this module status to CC3100_NO_DATA.
 */
#define CC3100_MODULE_AGAIN          -11

/**
 * @brief CC3100 Click two-byte field read function.
 * @details This function decodes a little-endian field without relying on compiler structure packing.
 * @param[in] buffer : Pointer to a two-byte little-endian field.
 * @return Decoded unsigned 16-bit value.
 * @note The input pointer may refer to an unaligned byte address.
 */
static uint16_t cc3100_get_u16 ( uint8_t *buffer );

/**
 * @brief CC3100 Click four-byte field read function.
 * @details This function decodes a little-endian field without relying on compiler structure packing.
 * @param[in] buffer : Pointer to a four-byte little-endian field.
 * @return Decoded unsigned 32-bit value.
 * @note The input pointer may refer to an unaligned byte address.
 */
static uint32_t cc3100_get_u32 ( uint8_t *buffer );

/**
 * @brief CC3100 Click little-endian field write function.
 * @details This function encodes a two-byte value in the SimpleLink wire format.
 * @param[out] buffer : Pointer to a two-byte output field.
 * @param[in] value : Field value.
 * @return Nothing.
 * @note The output pointer may refer to an unaligned byte address.
 */
static void cc3100_put_u16 ( uint8_t *buffer, uint16_t value );

/**
 * @brief CC3100 Click transport write function.
 * @details This function writes bytes to the selected interface. The caller controls SPI chip select.
 * UART sends one byte per millisecond so queued data cannot bypass a change of the module nRTS signal.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] buffer : Pointer to the input bytes.
 * @param[in] len : Number of bytes to write.
 * @return CC3100_OK, CC3100_TIMEOUT, or CC3100_ERROR.
 * @note In SPI mode, the caller keeps chip select asserted across a complete transaction.
 */
static err_t cc3100_write_bytes ( cc3100_t *ctx, uint8_t *buffer, uint16_t len );

/**
 * @brief CC3100 Click transport read function.
 * @details This function reads exactly len bytes while sharing one polling budget across a response.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[out] buffer : Pointer to the output buffer.
 * @param[in] len : Number of bytes to read.
 * @param[in,out] timeout : Remaining one-millisecond polling intervals.
 * @return CC3100_OK, CC3100_TIMEOUT, or CC3100_ERROR.
 * @note The timeout value is reduced as polling intervals are consumed.
 */
static err_t cc3100_read_bytes ( cc3100_t *ctx, uint8_t *buffer, uint16_t len, uint16_t *timeout );

/**
 * @brief CC3100 Click response synchronization check function.
 * @details This function validates legacy or sequence-numbered sync words using the NWP-defined sync mask.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] word : Received synchronization candidate.
 * @return 1 for a valid synchronization word, otherwise 0.
 * @note Sequence-numbered words are checked against ctx->rx_sequence.
 */
static uint8_t cc3100_sync_matches ( cc3100_t *ctx, uint32_t word );

/**
 * @brief CC3100 Click event update function.
 * @details This function updates cached network, role, and socket status from a validated response.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return CC3100_OK, CC3100_MODULE_ERROR, or CC3100_PROTOCOL_ERROR.
 * @note Unrecognized response and event opcodes leave the cached state unchanged.
 */
static err_t cc3100_update_event ( cc3100_t *ctx );

/**
 * @brief CC3100 Click response read function.
 * @details This function receives one complete frame, including alignment bytes, into the context buffer.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in,out] timeout : Remaining one-millisecond polling intervals.
 * @return CC3100_OK or a negative error code. See #cc3100_return_value_t.
 * @note SPI waits one millisecond after the host read-sync request before clocking the response.
 */
static err_t cc3100_read_frame ( cc3100_t *ctx, uint16_t *timeout );

/**
 * @brief CC3100 Click expected response wait function.
 * @details This function waits for the requested response and, when specified, its completion event.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] opcode : Expected response opcode.
 * @param[in] event : Required completion event, or zero when no second response is expected.
 * @return CC3100_OK or a negative error code. See #cc3100_return_value_t.
 * @note The TCP connect completion event may arrive before its command acknowledgement.
 */
static err_t cc3100_wait_response ( cc3100_t *ctx, uint16_t opcode, uint16_t event );

/**
 * @brief CC3100 Click command write function.
 * @details This function sends a padded SimpleLink command using the selected SPI or UART frame format.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] opcode : Command opcode.
 * @param[in] buffer : Command arguments and payload, or NULL for an empty command.
 * @param[in] len : Number of unpadded command bytes.
 * @return CC3100_OK or a negative error code. See #cc3100_return_value_t.
 * @note Payload padding is transmitted only to align the next frame field.
 */
static err_t cc3100_write_command ( cc3100_t *ctx, uint16_t opcode, uint8_t *buffer, uint16_t len );

/**
 * @brief CC3100 Click command transaction function.
 * @details This function writes a command and waits for its response. TCP connect also waits for its completion
 * event, which may arrive before the command acknowledgement.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] opcode : Command opcode.
 * @param[in] buffer : Command arguments and payload, or NULL for an empty command.
 * @param[in] len : Number of command bytes.
 * @param[in] response : Expected response opcode.
 * @return CC3100_OK or a negative error code. See #cc3100_return_value_t.
 * @note TCP socket connection completion uses CC3100_CONNECT_TIMEOUT_MS.
 */
static err_t cc3100_command ( cc3100_t *ctx, uint16_t opcode, uint8_t *buffer,
                              uint16_t len, uint16_t response );

/**
 * @brief CC3100 Click module status check function.
 * @details This function checks the signed status field of the most recent command response.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return CC3100_OK, CC3100_MODULE_ERROR, or CC3100_PROTOCOL_ERROR.
 * @note The decoded status is saved in ctx->module_error.
 */
static err_t cc3100_check_status ( cc3100_t *ctx );

/**
 * @brief CC3100 Click configuration query function.
 * @details This function reads a device or network configuration item from the NWP.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] opcode : Configuration query command.
 * @param[in] id : Configuration identifier.
 * @param[in] option : Configuration option.
 * @param[in] length : Requested configuration payload length.
 * @return CC3100_OK or a negative error code. See #cc3100_return_value_t.
 * @note The response payload and its actual length remain in the context object.
 */
static err_t cc3100_get_config ( cc3100_t *ctx, uint16_t opcode, uint16_t id,
                                 uint16_t option, uint16_t length );

void cc3100_cfg_setup ( cc3100_cfg_t *cfg ) 
{
    cfg->sck      = HAL_PIN_NC;
    cfg->miso     = HAL_PIN_NC;
    cfg->mosi     = HAL_PIN_NC;
    cfg->cs       = HAL_PIN_NC;
    cfg->tx_pin   = HAL_PIN_NC;
    cfg->rx_pin   = HAL_PIN_NC;
    cfg->ncts     = HAL_PIN_NC;
    cfg->nrts     = HAL_PIN_NC;
    cfg->rst      = HAL_PIN_NC;
    cfg->hib      = HAL_PIN_NC;
    cfg->int_pin  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->baud_rate   = 115200;
    cfg->data_bit    = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit  = UART_PARITY_DEFAULT;
    cfg->stop_bit    = UART_STOP_BITS_DEFAULT;

    cfg->drv_sel = CC3100_DRV_SEL_SPI;
}

void cc3100_drv_interface_sel ( cc3100_cfg_t *cfg, cc3100_drv_t drv_sel )
{
    cfg->drv_sel = drv_sel;
}

err_t cc3100_init ( cc3100_t *ctx, cc3100_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;
    uart_config_t uart_cfg;
    err_t error_flag = CC3100_ERROR;

    ctx->drv_sel = cfg->drv_sel;
    ctx->ready = 0;
    ctx->socket_id = -1;
    ctx->module_error = 0;
    memset( &ctx->network, 0, sizeof( ctx->network ) );
    if ( CC3100_DRV_SEL_SPI == ctx->drv_sel )
    {
        spi_master_configure_default( &spi_cfg );
        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;
        ctx->chip_select = cfg->cs;

        error_flag = spi_master_open( &ctx->spi, &spi_cfg );
        if ( SPI_MASTER_ERROR != error_flag )
        {
            error_flag = spi_master_set_default_write_data( &ctx->spi, CC3100_SPI_DUMMY );
        }
        if ( SPI_MASTER_ERROR != error_flag )
        {
            error_flag = spi_master_set_mode( &ctx->spi, cfg->spi_mode );
        }
        if ( SPI_MASTER_ERROR != error_flag )
        {
            error_flag = spi_master_set_speed( &ctx->spi, cfg->spi_speed );
        }
        if ( SPI_MASTER_ERROR != error_flag )
        {
            spi_master_set_chip_select_polarity( cfg->cs_polarity );
            spi_master_deselect_device( ctx->chip_select );
            digital_in_init( &ctx->int_pin, cfg->int_pin );
        }
    }
    else if ( CC3100_DRV_SEL_UART == ctx->drv_sel )
    {
        // J1A/J2A route CS/INT to UART handshake pins instead of SPI signals.
        digital_out_init( &ctx->ncts, cfg->ncts );
        digital_out_high( &ctx->ncts );
        digital_in_init( &ctx->nrts, cfg->nrts );

        uart_configure_default( &uart_cfg );
        uart_cfg.tx_pin = cfg->tx_pin;
        uart_cfg.rx_pin = cfg->rx_pin;
        uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
        uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );
        ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
        ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

        error_flag = uart_open( &ctx->uart, &uart_cfg );
        if ( UART_ERROR != error_flag )
        {
            error_flag = uart_set_baud( &ctx->uart, cfg->baud_rate );
        }
        if ( UART_ERROR != error_flag )
        {
            error_flag = uart_set_data_bits( &ctx->uart, cfg->data_bit );
        }
        if ( UART_ERROR != error_flag )
        {
            error_flag = uart_set_parity( &ctx->uart, cfg->parity_bit );
        }
        if ( UART_ERROR != error_flag )
        {
            error_flag = uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
        }
        if ( UART_ERROR != error_flag )
        {
            uart_set_blocking( &ctx->uart, false );
        }
    }

    if ( CC3100_OK == error_flag )
    {
        digital_out_init( &ctx->rst, cfg->rst );
        digital_out_init( &ctx->hib, cfg->hib );
        digital_out_low( &ctx->hib );
        digital_out_high( &ctx->rst );
    }

    return error_flag;
}


err_t cc3100_reset ( cc3100_t *ctx )
{
    uint8_t dummy;
    uint16_t timeout = CC3100_TIMEOUT_MS;
    err_t error_flag;

    ctx->ready = 0;
    ctx->socket_id = -1;
    ctx->rx_sequence = 0;
    ctx->tx_credits = 0;
    ctx->tx_failure = 0;
    ctx->module_error = 0;
    ctx->first_command = 1;
    memset( &ctx->network, 0, sizeof( ctx->network ) );

    // Hold the network processor disabled before changing reset or clearing queued UART bytes.
    digital_out_low( &ctx->hib );
    digital_out_low( &ctx->rst );
    cc3100_set_ncts( ctx, 1 );
    Delay_100ms( );
    if ( CC3100_DRV_SEL_UART == ctx->drv_sel )
    {
        uart_clear( &ctx->uart );
        uart_read( &ctx->uart, &dummy, 1 );
    }
    digital_out_high( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->hib );

    // IRQ signals a pending SPI message, not successful startup. Validate INIT_COMPLETE before sending commands.
    error_flag = cc3100_read_frame( ctx, &timeout );
    if ( ( CC3100_OK == error_flag ) && ( CC3100_EVT_INIT != ctx->response_opcode ) )
    {
        error_flag = CC3100_PROTOCOL_ERROR;
    }
    if ( CC3100_OK == error_flag )
    {
        ctx->ready = 1;
    }
    return error_flag;
}

err_t cc3100_default_cfg ( cc3100_t *ctx )
{
    uint8_t buffer[ 12 ] = { 0 };
    err_t error_flag;

    error_flag = cc3100_reset( ctx );
    if ( ( CC3100_OK == error_flag ) && ( CC3100_ROLE_STATION != ctx->role ) )
    {
        buffer[ 0 ] = CC3100_ROLE_STATION;
        error_flag = cc3100_command( ctx, CC3100_CMD_WLAN_MODE, buffer, 4,
                                     CC3100_CMD_WLAN_MODE & CC3100_RESPONSE_MASK );
        if ( CC3100_OK == error_flag )
        {
            error_flag = cc3100_check_status( ctx );
        }
    }
    if ( CC3100_OK == error_flag )
    {
        // Disable automatic profile selection so the example uses only the supplied SSID.
        buffer[ 0 ] = CC3100_POLICY_CONNECTION;
        error_flag = cc3100_command( ctx, CC3100_CMD_WLAN_POLICY, buffer, 4,
                                     CC3100_CMD_WLAN_POLICY & CC3100_RESPONSE_MASK );
        if ( CC3100_OK == error_flag )
        {
            error_flag = cc3100_check_status( ctx );
        }
    }
    if ( CC3100_OK == error_flag )
    {
        error_flag = cc3100_get_config( ctx, CC3100_CMD_NETCFG_GET, CC3100_CFG_IPV4, 0, 16 );
    }
    if ( ( CC3100_OK == error_flag ) && ( 0 == cc3100_get_u16( &ctx->response[ 4 ] ) ) )
    {
        // Change persistent addressing only when DHCP is currently disabled.
        memset( buffer, 0, sizeof( buffer ) );
        cc3100_put_u16( &buffer[ 2 ], CC3100_CFG_DHCP );
        cc3100_put_u16( &buffer[ 4 ], 1 );
        cc3100_put_u16( &buffer[ 6 ], 1 );
        buffer[ 8 ] = 1;
        error_flag = cc3100_command( ctx, CC3100_CMD_NETCFG_SET, buffer, sizeof( buffer ),
                                     CC3100_CMD_NETCFG_SET & CC3100_RESPONSE_MASK );
        if ( CC3100_OK == error_flag )
        {
            error_flag = cc3100_check_status( ctx );
        }
    }
    if ( CC3100_OK == error_flag )
    {
        // Apply role and addressing changes, and drop any connection restored during the first startup.
        error_flag = cc3100_reset( ctx );
        if ( ( CC3100_OK == error_flag ) && ( CC3100_ROLE_STATION != ctx->role ) )
        {
            ctx->ready = 0;
            error_flag = CC3100_MODULE_ERROR;
        }
    }
    return error_flag;
}

err_t cc3100_get_version ( cc3100_t *ctx, cc3100_version_t *version )
{
    err_t error_flag = CC3100_ARGUMENT_ERROR;
    uint8_t index;

    if ( version )
    {
        error_flag = cc3100_get_config( ctx, CC3100_CMD_DEVICE_GET,
                                        CC3100_CFG_GENERAL, CC3100_CFG_VERSION, 44 );
        if ( CC3100_OK == error_flag )
        {
            // The version payload has an 8-byte prefix before chip, firmware, PHY, NWP, and ROM fields.
            version->chip_id = cc3100_get_u32( &ctx->response[ 8 ] );
            for ( index = 0; index < 4; index++ )
            {
                version->firmware[ index ] = cc3100_get_u32( &ctx->response[ 12 + index * 4 ] );
                version->phy[ index ] = ctx->response[ 28 + index ];
                version->nwp[ index ] = cc3100_get_u32( &ctx->response[ 32 + index * 4 ] );
            }
            version->rom = cc3100_get_u16( &ctx->response[ 48 ] );
        }
    }
    return error_flag;
}

err_t cc3100_get_mac ( cc3100_t *ctx, uint8_t *mac )
{
    err_t error_flag = CC3100_ARGUMENT_ERROR;

    if ( mac )
    {
        error_flag = cc3100_get_config( ctx, CC3100_CMD_NETCFG_GET, CC3100_CFG_MAC, 0, 6 );
        if ( CC3100_OK == error_flag )
        {
            memcpy( mac, &ctx->response[ 8 ], 6 );
        }
    }
    return error_flag;
}

err_t cc3100_connect ( cc3100_t *ctx, char *ssid, char *password, uint8_t security )
{
    uint8_t buffer[ 9 + CC3100_SSID_SIZE + CC3100_KEY_SIZE ] = { 0 };
    uint16_t ssid_length = 0;
    uint16_t key_length = 0;
    err_t error_flag = CC3100_ARGUMENT_ERROR;

    if ( ssid )
    {
        ssid_length = strlen( ssid );
    }
    if ( password )
    {
        key_length = strlen( password );
    }
    if ( ( ssid_length > 0 ) && ( ssid_length <= CC3100_SSID_SIZE ) &&
         ( ( ( CC3100_SECURITY_OPEN == security ) && !key_length ) ||
           ( ( CC3100_SECURITY_WPA_WPA2 == security ) && ( key_length >= 8 ) &&
             ( key_length <= CC3100_KEY_SIZE ) ) ) )
    {
        // The fixed descriptor is nine bytes; SSID and key follow without null terminators.
        buffer[ 0 ] = security;
        buffer[ 1 ] = ( uint8_t ) ssid_length;
        buffer[ 8 ] = ( uint8_t ) key_length;
        memcpy( &buffer[ 9 ], ssid, ssid_length );
        if ( key_length )
        {
            memcpy( &buffer[ 9 + ssid_length ], password, key_length );
        }
        memset( &ctx->network, 0, sizeof( ctx->network ) );
        error_flag = cc3100_command( ctx, CC3100_CMD_WLAN_CONNECT, buffer, 9 + ssid_length + key_length,
                                     CC3100_CMD_WLAN_CONNECT & CC3100_RESPONSE_MASK );
        if ( CC3100_OK == error_flag )
        {
            error_flag = cc3100_check_status( ctx );
        }
    }
    return error_flag;
}

err_t cc3100_disconnect ( cc3100_t *ctx )
{
    err_t error_flag;

    error_flag = cc3100_command( ctx, CC3100_CMD_WLAN_DISCONNECT, NULL, 0,
                                 CC3100_CMD_WLAN_DISCONNECT & CC3100_RESPONSE_MASK );
    if ( CC3100_OK == error_flag )
    {
        error_flag = cc3100_check_status( ctx );
    }
    return error_flag;
}

err_t cc3100_process ( cc3100_t *ctx )
{
    uint16_t timeout = CC3100_TIMEOUT_MS;
    uint8_t available;
    err_t error_flag = CC3100_ERROR;

    if ( ctx->ready )
    {
        if ( CC3100_DRV_SEL_SPI == ctx->drv_sel )
        {
            available = digital_in_read( &ctx->int_pin );
        }
        else
        {
            // Give the module time to start an event before deciding that the UART is idle.
            cc3100_set_ncts( ctx, 0 );
            Delay_1ms( );
            available = uart_bytes_available( &ctx->uart ) != 0;
            cc3100_set_ncts( ctx, 1 );
        }
        error_flag = CC3100_NO_DATA;
        if ( available )
        {
            error_flag = cc3100_read_frame( ctx, &timeout );
            if ( ( CC3100_OK == error_flag ) && ( ctx->response_opcode & CC3100_OPCODE_SYNC ) )
            {
                // A synchronous reply with no active command indicates that framing has been lost.
                ctx->ready = 0;
                error_flag = CC3100_PROTOCOL_ERROR;
            }
        }
    }
    return error_flag;
}

err_t cc3100_open_socket ( cc3100_t *ctx, uint8_t protocol, uint16_t local_port,
                           uint8_t *peer_ip, uint16_t peer_port )
{
    uint8_t buffer[ 12 ] = { 0 };
    err_t error_flag = CC3100_ARGUMENT_ERROR;
    err_t close_error;
    int16_t module_error;

    if ( peer_ip && peer_port && ctx->network.ip_acquired && ( ctx->socket_id < 0 ) &&
         ( ( CC3100_PROTOCOL_TCP == protocol ) || ( CC3100_PROTOCOL_UDP == protocol ) ) )
    {
        buffer[ 0 ] = CC3100_AF_INET;
        buffer[ 1 ] = CC3100_SOCK_DGRAM;
        if ( CC3100_PROTOCOL_TCP == protocol )
        {
            buffer[ 1 ] = CC3100_SOCK_STREAM;
        }
        buffer[ 2 ] = protocol;
        error_flag = cc3100_command( ctx, CC3100_CMD_SOCKET, buffer, 4,
                                     CC3100_CMD_SOCKET & CC3100_RESPONSE_MASK );
        if ( CC3100_OK == error_flag )
        {
            error_flag = cc3100_check_status( ctx );
        }
        if ( CC3100_OK == error_flag )
        {
            if ( ( ctx->response[ 2 ] & CC3100_SOCKET_ID_MASK ) >= CC3100_SOCKET_COUNT )
            {
                ctx->ready = 0;
                error_flag = CC3100_PROTOCOL_ERROR;
            }
        }
        if ( CC3100_OK == error_flag )
        {
            ctx->socket_id = ctx->response[ 2 ];
            ctx->protocol = protocol;
            memcpy( ctx->peer_ip, peer_ip, 4 );
            ctx->peer_port = peer_port;

            memset( buffer, 0, sizeof( buffer ) );
            buffer[ 2 ] = ( uint8_t ) ctx->socket_id;
            buffer[ 3 ] = CC3100_AF_INET << 4;
            if ( CC3100_PROTOCOL_TCP == protocol )
            {
                // Socket addresses use network byte order for both IP address and port.
                buffer[ 4 ] = ( uint8_t ) ( peer_port >> 8 );
                buffer[ 5 ] = ( uint8_t ) peer_port;
                memcpy( &buffer[ 8 ], peer_ip, 4 );
                error_flag = cc3100_command( ctx, CC3100_CMD_CONNECT, buffer, sizeof( buffer ),
                                             CC3100_CMD_CONNECT & CC3100_RESPONSE_MASK );
            }
            else
            {
                buffer[ 4 ] = ( uint8_t ) ( local_port >> 8 );
                buffer[ 5 ] = ( uint8_t ) local_port;
                error_flag = cc3100_command( ctx, CC3100_CMD_BIND, buffer, sizeof( buffer ),
                                             CC3100_CMD_BIND & CC3100_RESPONSE_MASK );
                if ( CC3100_OK == error_flag )
                {
                    error_flag = cc3100_check_status( ctx );
                }
            }
        }
        if ( CC3100_OK == error_flag )
        {
            // A socket-level nonblocking option makes an empty receive return -11 instead of waiting forever.
            memset( buffer, 0, sizeof( buffer ) );
            buffer[ 0 ] = ( uint8_t ) ctx->socket_id;
            buffer[ 1 ] = CC3100_SOL_SOCKET;
            buffer[ 2 ] = CC3100_SO_NONBLOCKING;
            buffer[ 3 ] = 4;
            buffer[ 4 ] = 1;
            error_flag = cc3100_command( ctx, CC3100_CMD_SOCKET_OPTION, buffer, 8,
                                         CC3100_CMD_SOCKET_OPTION & CC3100_RESPONSE_MASK );
            if ( CC3100_OK == error_flag )
            {
                error_flag = cc3100_check_status( ctx );
            }
        }
        if ( ( CC3100_OK != error_flag ) && ( ctx->socket_id >= 0 ) )
        {
            // Preserve the original module status if socket cleanup also reports an error.
            module_error = ctx->module_error;
            close_error = cc3100_close_socket( ctx );
            ctx->module_error = module_error;
            if ( CC3100_OK != close_error )
            {
                ctx->ready = 0;
            }
        }
    }
    return error_flag;
}

err_t cc3100_close_socket ( cc3100_t *ctx )
{
    uint8_t buffer[ 4 ] = { 0 };
    err_t error_flag = CC3100_OK;

    if ( ctx->socket_id >= 0 )
    {
        buffer[ 0 ] = ( uint8_t ) ctx->socket_id;
        error_flag = cc3100_command( ctx, CC3100_CMD_CLOSE, buffer, sizeof( buffer ),
                                     CC3100_CMD_CLOSE & CC3100_RESPONSE_MASK );
        if ( CC3100_OK == error_flag )
        {
            error_flag = cc3100_check_status( ctx );
        }
        ctx->socket_id = -1;
    }
    return error_flag;
}

err_t cc3100_send ( cc3100_t *ctx, uint8_t *data_in, uint16_t len )
{
    uint8_t buffer[ 12 + CC3100_DATA_SIZE ] = { 0 };
    uint16_t descriptor = 4;
    uint16_t opcode = CC3100_CMD_SEND;
    err_t error_flag = CC3100_ARGUMENT_ERROR;

    if ( data_in && len && ( len <= CC3100_DATA_SIZE ) && ( ctx->socket_id >= 0 ) &&
         ctx->ready && ctx->network.ip_acquired )
    {
        // Refresh asynchronous credits and socket errors before preparing the next payload.
        error_flag = cc3100_process( ctx );
        if ( ( CC3100_OK == error_flag ) || ( CC3100_NO_DATA == error_flag ) )
        {
            error_flag = CC3100_OK;
            if ( !ctx->network.ip_acquired )
            {
                error_flag = CC3100_ERROR;
            }
            else if ( ctx->tx_failure & ( 1 << ( ctx->socket_id & CC3100_SOCKET_ID_MASK ) ) )
            {
                error_flag = CC3100_MODULE_ERROR;
            }
            else if ( ctx->tx_credits <= CC3100_TX_RESERVED )
            {
                error_flag = CC3100_NO_DATA;
            }
            if ( CC3100_OK == error_flag )
            {
                cc3100_put_u16( buffer, len );
                buffer[ 2 ] = ( uint8_t ) ctx->socket_id;
                if ( CC3100_PROTOCOL_UDP == ctx->protocol )
                {
                    descriptor = 12;
                    opcode = CC3100_CMD_SENDTO;
                    buffer[ 3 ] = CC3100_AF_INET << 4;
                    buffer[ 4 ] = ( uint8_t ) ( ctx->peer_port >> 8 );
                    buffer[ 5 ] = ( uint8_t ) ctx->peer_port;
                    memcpy( &buffer[ 8 ], ctx->peer_ip, 4 );
                }
                memcpy( &buffer[ descriptor ], data_in, len );
                ctx->tx_credits--;
                error_flag = cc3100_write_command( ctx, opcode, buffer, descriptor + len );
            }
        }
    }
    return error_flag;
}

err_t cc3100_receive ( cc3100_t *ctx, uint8_t *data_out, uint16_t len, cc3100_packet_t *packet )
{
    uint8_t buffer[ 4 ] = { 0 };
    uint16_t opcode = CC3100_CMD_RECV;
    uint16_t response = CC3100_EVT_SOCKET_RECV;
    uint16_t descriptor = 4;
    int16_t received;
    err_t error_flag = CC3100_ARGUMENT_ERROR;

    if ( packet )
    {
        // A failed or empty read must not leave a stale length from the caller's previous packet.
        packet->length = 0;
    }
    if ( data_out && packet && len && ( len <= CC3100_DATA_SIZE ) &&
         ( ctx->socket_id >= 0 ) && ctx->ready && ctx->network.ip_acquired )
    {
        error_flag = cc3100_process( ctx );
        if ( ( CC3100_OK == error_flag ) || ( CC3100_NO_DATA == error_flag ) )
        {
            error_flag = CC3100_NO_DATA;
            // Keep one NWP buffer in reserve for command and flow-control traffic.
            if ( !ctx->network.ip_acquired )
            {
                error_flag = CC3100_ERROR;
            }
            else if ( ctx->tx_credits > CC3100_TX_RESERVED - 1 )
            {
                cc3100_put_u16( buffer, len );
                buffer[ 2 ] = ( uint8_t ) ctx->socket_id;
                if ( CC3100_PROTOCOL_UDP == ctx->protocol )
                {
                    opcode = CC3100_CMD_RECVFROM;
                    response = CC3100_EVT_SOCKET_RECVFROM;
                    // UDP responses include the source port and address after the common 4-byte descriptor.
                    descriptor = 12;
                    buffer[ 3 ] = CC3100_AF_INET << 4;
                }
                ctx->tx_credits--;
                error_flag = cc3100_command( ctx, opcode, buffer, sizeof( buffer ), response );
                if ( CC3100_OK == error_flag )
                {
                    error_flag = cc3100_check_status( ctx );
                    if ( ( CC3100_MODULE_ERROR == error_flag ) && ( CC3100_MODULE_AGAIN == ctx->module_error ) )
                    {
                        ctx->module_error = 0;
                        error_flag = CC3100_NO_DATA;
                    }
                }
                if ( CC3100_OK == error_flag )
                {
                    received = ( int16_t ) cc3100_get_u16( ctx->response );
                    if ( ( ctx->response[ 2 ] != ( uint8_t ) ctx->socket_id ) ||
                         ( ctx->response_length < descriptor ) ||
                         ( ( uint16_t ) received > ctx->response_length - descriptor ) )
                    {
                        ctx->ready = 0;
                        error_flag = CC3100_PROTOCOL_ERROR;
                    }
                    else if ( ( uint16_t ) received > len )
                    {
                        // Reject an undersized application buffer instead of returning a truncated datagram.
                        error_flag = CC3100_BUFFER_ERROR;
                    }
                    else if ( ( 0 == received ) && ( CC3100_PROTOCOL_TCP == ctx->protocol ) )
                    {
                        error_flag = CC3100_CLOSED;
                    }
                    else
                    {
                        packet->length = ( uint16_t ) received;
                        memcpy( data_out, &ctx->response[ descriptor ], packet->length );
                        if ( CC3100_PROTOCOL_UDP == ctx->protocol )
                        {
                            memcpy( packet->ip, &ctx->response[ 8 ], 4 );
                            packet->port = ( ( uint16_t ) ctx->response[ 4 ] << 8 ) | ctx->response[ 5 ];
                        }
                        else
                        {
                            memcpy( packet->ip, ctx->peer_ip, 4 );
                            packet->port = ctx->peer_port;
                        }
                    }
                }
            }
        }
    }
    return error_flag;
}

void cc3100_set_ncts ( cc3100_t *ctx, uint8_t state )
{
    if ( CC3100_DRV_SEL_UART == ctx->drv_sel )
    {
        digital_out_write( &ctx->ncts, state );
    }
}

uint8_t cc3100_get_nrts ( cc3100_t *ctx )
{
    uint8_t state = 1;

    if ( CC3100_DRV_SEL_UART == ctx->drv_sel )
    {
        state = digital_in_read( &ctx->nrts );
    }
    return state;
}

static uint16_t cc3100_get_u16 ( uint8_t *buffer )
{
    return ( uint16_t ) buffer[ 0 ] | ( ( uint16_t ) buffer[ 1 ] << 8 );
}

static uint32_t cc3100_get_u32 ( uint8_t *buffer )
{
    return ( uint32_t ) buffer[ 0 ] | ( ( uint32_t ) buffer[ 1 ] << 8 ) |
           ( ( uint32_t ) buffer[ 2 ] << 16 ) | ( ( uint32_t ) buffer[ 3 ] << 24 );
}

static void cc3100_put_u16 ( uint8_t *buffer, uint16_t value )
{
    buffer[ 0 ] = ( uint8_t ) value;
    buffer[ 1 ] = ( uint8_t ) ( value >> 8 );
}

static err_t cc3100_write_bytes ( cc3100_t *ctx, uint8_t *buffer, uint16_t len )
{
    err_t error_flag = CC3100_OK;
    uint16_t index;
    uint16_t timeout = CC3100_TIMEOUT_MS;

    if ( CC3100_DRV_SEL_SPI == ctx->drv_sel )
    {
        error_flag = spi_master_write( &ctx->spi, buffer, len );
    }
    else
    {
        for ( index = 0; ( index < len ) && ( CC3100_OK == error_flag ); index++ )
        {
            while ( cc3100_get_nrts( ctx ) && timeout )
            {
                Delay_1ms( );
                timeout--;
            }
            if ( !timeout )
            {
                error_flag = CC3100_TIMEOUT;
            }
            else if ( 1 != uart_write( &ctx->uart, &buffer[ index ], 1 ) )
            {
                error_flag = CC3100_ERROR;
            }
            else
            {
                // At the default 115200 baud, this allows the byte to leave the UART before rechecking nRTS.
                Delay_1ms( );
            }
        }
    }
    return error_flag;
}

static err_t cc3100_read_bytes ( cc3100_t *ctx, uint8_t *buffer, uint16_t len, uint16_t *timeout )
{
    err_t error_flag = CC3100_OK;
    int32_t count;
    uint16_t offset = 0;

    if ( CC3100_DRV_SEL_SPI == ctx->drv_sel )
    {
        error_flag = spi_master_read( &ctx->spi, buffer, len );
    }
    else
    {
        while ( ( offset < len ) && ( CC3100_OK == error_flag ) )
        {
            count = uart_read( &ctx->uart, &buffer[ offset ], len - offset );
            if ( count > 0 )
            {
                offset += ( uint16_t ) count;
            }
            else if ( count < 0 )
            {
                error_flag = CC3100_ERROR;
            }
            else if ( *timeout )
            {
                Delay_1ms( );
                ( *timeout )--;
            }
            else
            {
                error_flag = CC3100_TIMEOUT;
            }
        }
    }
    return error_flag;
}

static uint8_t cc3100_sync_matches ( cc3100_t *ctx, uint32_t word )
{
    uint32_t expected = CC3100_SYNC_WORD & CC3100_SYNC_BUG_MASK;

    if ( word & CC3100_SYNC_SEQ_FLAG )
    {
        expected = ( expected & 0xFFFFFFF8ul ) | CC3100_SYNC_SEQ_FLAG | ( ctx->rx_sequence & 3 );
    }
    return ( word & CC3100_SYNC_BUG_MASK ) == expected;
}

static err_t cc3100_update_event ( cc3100_t *ctx )
{
    err_t error_flag = CC3100_OK;
    uint8_t index;
    uint8_t role;

    switch ( ctx->response_opcode )
    {
        case CC3100_EVT_INIT:
        {
            if ( ctx->response_length < 4 )
            {
                error_flag = CC3100_PROTOCOL_ERROR;
            }
            else
            {
                role = ctx->response[ 0 ] & 7;
                if ( CC3100_INIT_STATION == role )
                {
                    ctx->role = CC3100_ROLE_STATION;
                }
                else if ( CC3100_INIT_AP == role )
                {
                    ctx->role = CC3100_ROLE_AP;
                }
                else if ( CC3100_INIT_P2P == role )
                {
                    ctx->role = CC3100_ROLE_P2P;
                }
                else
                {
                    ctx->module_error = role;
                    error_flag = CC3100_MODULE_ERROR;
                }
            }
            break;
        }
        case CC3100_EVT_WLAN_CONNECTED:
        {
            ctx->network.connected = 1;
            break;
        }
        case CC3100_EVT_WLAN_DISCONNECTED:
        case CC3100_EVT_IP_LOST:
        case CC3100_EVT_DHCP_TIMEOUT:
        {
            memset( &ctx->network, 0, sizeof( ctx->network ) );
            break;
        }
        case CC3100_EVT_IP_ACQUIRED:
        {
            if ( ctx->response_length < 12 )
            {
                error_flag = CC3100_PROTOCOL_ERROR;
            }
            else
            {
                // The event contains host-order 32-bit IPv4 fields, unlike socket address fields.
                for ( index = 0; index < 4; index++ )
                {
                    ctx->network.ip[ index ] = ctx->response[ 3 - index ];
                    ctx->network.gateway[ index ] = ctx->response[ 7 - index ];
                    ctx->network.dns[ index ] = ctx->response[ 11 - index ];
                }
                ctx->network.connected = 1;
                ctx->network.ip_acquired = 1;
            }
            break;
        }
        case CC3100_EVT_SOCKET_TX_FAILED:
        {
            if ( ctx->response_length >= 4 )
            {
                ctx->module_error = ( int16_t ) cc3100_get_u16( ctx->response );
                ctx->tx_failure |= 1 << ( ctx->response[ 2 ] & CC3100_SOCKET_ID_MASK );
            }
            break;
        }
        case CC3100_EVT_ABORT:
        case CC3100_EVT_FATAL:
        {
            ctx->ready = 0;
            error_flag = CC3100_MODULE_ERROR;
            break;
        }
        default:
        {
            break;
        }
    }
    return error_flag;
}

static err_t cc3100_read_frame ( cc3100_t *ctx, uint16_t *timeout )
{
    uint8_t request[ 4 ] = { 0x65, 0x87, 0x78, 0x56 };
    uint8_t header[ CC3100_RESPONSE_HEADER ];
    uint8_t byte;
    uint8_t available = 0;
    uint32_t scanned = 0;
    uint16_t aligned_length;
    uint16_t tail;
    uint32_t sync = 0;
    err_t error_flag = CC3100_OK;
    
    ctx->response_opcode = 0;
    ctx->response_length = 0;
    cc3100_set_ncts( ctx, 0 );
    while ( !available && ( CC3100_OK == error_flag ) )
    {
        if ( CC3100_DRV_SEL_SPI == ctx->drv_sel )
        {
            available = digital_in_read( &ctx->int_pin );
        }
        else
        {
            available = uart_bytes_available( &ctx->uart ) != 0;
        }
        if ( !available )
        {
            if ( *timeout )
            {
                Delay_1ms( );
                ( *timeout )--;
            }
            else
            {
                error_flag = CC3100_TIMEOUT;
            }
        }
    }

    if ( ( CC3100_OK == error_flag ) && ( CC3100_DRV_SEL_SPI == ctx->drv_sel ) )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = cc3100_write_bytes( ctx, request, sizeof( request ) );
        if ( CC3100_OK == error_flag )
        {
            // Give the NWP time to prepare its response after the host read-sync.
            Delay_1ms( );
        }
    }

    // Keep SPI clocks continuous while scanning; the NWP may need extra clocks to prepare its response.
    while ( ( CC3100_OK == error_flag ) && ( scanned < CC3100_SYNC_SCAN_SIZE ) )
    {
        error_flag = cc3100_read_bytes( ctx, &byte, 1, timeout );
        if ( CC3100_OK == error_flag )
        {
            sync = ( sync >> 8 ) | ( ( uint32_t ) byte << 24 );
            scanned++;
            if ( scanned >= 4 )
            {
                if ( cc3100_sync_matches( ctx, sync ) )
                {
                    break;
                }
            }
        }
    }
    if ( ( CC3100_OK == error_flag ) && !cc3100_sync_matches( ctx, sync ) )
    {
        error_flag = CC3100_PROTOCOL_ERROR;
    }
    // Scanning bytewise can leave the stream unaligned; consume the trailing pad after the response.
    tail = ( 4 - ( scanned & 3 ) ) & 3;

    if ( CC3100_OK == error_flag )
    {
        error_flag = cc3100_read_bytes( ctx, header, 4, timeout );
    }
    // The NWP may send a second sync word before the response header.
    while ( ( CC3100_OK == error_flag ) && cc3100_sync_matches( ctx, cc3100_get_u32( header ) ) )
    {
        scanned += 4;
        if ( scanned >= CC3100_SYNC_SCAN_SIZE )
        {
            error_flag = CC3100_PROTOCOL_ERROR;
        }
        else
        {
            error_flag = cc3100_read_bytes( ctx, header, 4, timeout );
        }
    }
    if ( CC3100_OK == error_flag )
    {
        error_flag = cc3100_read_bytes( ctx, &header[ 4 ], CC3100_RESPONSE_EXTRA, timeout );
    }
    if ( CC3100_OK == error_flag )
    {
        ctx->response_opcode = cc3100_get_u16( header );
        ctx->response_length = cc3100_get_u16( &header[ 2 ] );
        if ( ctx->response_length < CC3100_RESPONSE_EXTRA )
        {
            error_flag = CC3100_PROTOCOL_ERROR;
        }
        else if ( ctx->response_length > CC3100_RESPONSE_SIZE + CC3100_RESPONSE_EXTRA )
        {
            error_flag = CC3100_BUFFER_ERROR;
        }
        else
        {
            // The wire length includes a 4-byte descriptor; response[] stores only the remaining payload.
            ctx->response_length -= CC3100_RESPONSE_EXTRA;
            aligned_length = ( ctx->response_length + 3 ) & 0xFFFC;
            if ( aligned_length )
            {
                error_flag = cc3100_read_bytes( ctx, ctx->response, aligned_length, timeout );
            }
            if ( ( CC3100_OK == error_flag ) && tail )
            {
                error_flag = cc3100_read_bytes( ctx, header, tail, timeout );
            }
            if ( CC3100_OK == error_flag )
            {
                if ( CC3100_EVT_INIT != ctx->response_opcode )
                {
                    ctx->tx_credits = header[ 4 ];
                    ctx->tx_failure = header[ 6 ];
                }
                ctx->rx_sequence++;
            }
        }
    }
    if ( CC3100_DRV_SEL_SPI == ctx->drv_sel )
    {
        spi_master_deselect_device( ctx->chip_select );
    }
    cc3100_set_ncts( ctx, 1 );

    if ( CC3100_OK == error_flag )
    {
        error_flag = cc3100_update_event( ctx );
    }
    if ( CC3100_OK != error_flag )
    {
        // Do not reuse a partially consumed frame for a later command; the caller must restart the NWP.
        ctx->ready = 0;
    }
    return error_flag;
}

static err_t cc3100_wait_response ( cc3100_t *ctx, uint16_t opcode, uint16_t event )
{
    uint16_t timeout = CC3100_TIMEOUT_MS;
    uint8_t response_received = 0;
    uint8_t event_received = ( 0 == event );
    int16_t event_status = 0;
    err_t error_flag = CC3100_OK;

    while ( ( CC3100_OK == error_flag ) && ( !response_received || !event_received ) )
    {
        error_flag = cc3100_read_frame( ctx, &timeout );
        if ( CC3100_OK == error_flag )
        {
            if ( ( opcode == ctx->response_opcode ) && !response_received )
            {
                response_received = 1;
                if ( event )
                {
                    error_flag = cc3100_check_status( ctx );
                    if ( ( CC3100_OK == error_flag ) && ( CC3100_EVT_SOCKET_CONNECT == event ) &&
                         ( ctx->response[ 2 ] != ( uint8_t ) ctx->socket_id ) )
                    {
                        error_flag = CC3100_PROTOCOL_ERROR;
                    }
                    if ( ( CC3100_OK == error_flag ) && ( CC3100_EVT_SOCKET_CONNECT == event ) )
                    {
                        // An Internet TCP handshake may take longer than a local command acknowledgement.
                        timeout = CC3100_CONNECT_TIMEOUT_MS;
                    }
                }
            }
            else if ( event && ( event == ctx->response_opcode ) && !event_received )
            {
                if ( ( ctx->response_length < 4 ) ||
                     ( ( CC3100_EVT_SOCKET_CONNECT == event ) &&
                       ( ctx->response[ 2 ] != ( uint8_t ) ctx->socket_id ) ) )
                {
                    error_flag = CC3100_PROTOCOL_ERROR;
                }
                else
                {
                    // Preserve an early completion while unrelated events or the acknowledgement replace the buffer.
                    event_status = ( int16_t ) cc3100_get_u16( ctx->response );
                    event_received = 1;
                }
            }
            else if ( ctx->response_opcode & CC3100_OPCODE_SYNC )
            {
                error_flag = CC3100_PROTOCOL_ERROR;
            }
        }
        if ( ( CC3100_OK == error_flag ) && ( !response_received || !event_received ) )
        {
            // Event traffic must not extend a missing response wait indefinitely.
            if ( !timeout )
            {
                error_flag = CC3100_TIMEOUT;
            }
            else
            {
                Delay_1ms( );
                timeout--;
            }
        }
    }
    if ( ( CC3100_OK == error_flag ) && event )
    {
        ctx->module_error = event_status;
        if ( event_status < 0 )
        {
            error_flag = CC3100_MODULE_ERROR;
        }
    }
    if ( ( CC3100_PROTOCOL_ERROR == error_flag ) || ( CC3100_TIMEOUT == error_flag ) )
    {
        ctx->ready = 0;
    }

    return error_flag;
}

static err_t cc3100_write_command ( cc3100_t *ctx, uint16_t opcode, uint8_t *buffer, uint16_t len )
{
    uint8_t header[ 12 ] = { 0xFF, 0xEE, 0xDD, 0xBB, 0x21, 0x43, 0x34, 0x12, 0, 0, 0, 0 };
    uint8_t padding[ 3 ] = { 0, 0, 0 };
    uint16_t aligned_length = ( len + 3 ) & 0xFFFC;
    err_t error_flag;

    ctx->response_opcode = 0;
    ctx->response_length = 0;
    cc3100_put_u16( &header[ 8 ], opcode );
    cc3100_put_u16( &header[ 10 ], aligned_length );
    if ( CC3100_DRV_SEL_SPI == ctx->drv_sel )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = cc3100_write_bytes( ctx, &header[ 4 ], 8 );
    }
    else
    {
        error_flag = cc3100_write_bytes( ctx, header, sizeof( header ) );
    }
    if ( ( CC3100_OK == error_flag ) && len )
    {
        error_flag = cc3100_write_bytes( ctx, buffer, len );
    }
    if ( ( CC3100_OK == error_flag ) && ( aligned_length > len ) )
    {
        error_flag = cc3100_write_bytes( ctx, padding, aligned_length - len );
    }
    if ( CC3100_DRV_SEL_SPI == ctx->drv_sel )
    {
        spi_master_deselect_device( ctx->chip_select );
        if ( ctx->first_command )
        {
            Delay_10ms( );
            ctx->first_command = 0;
        }
    }
    if ( CC3100_OK != error_flag )
    {
        ctx->ready = 0;
    }
    return error_flag;
}

static err_t cc3100_command ( cc3100_t *ctx, uint16_t opcode, uint8_t *buffer,
                              uint16_t len, uint16_t response )
{
    err_t error_flag = CC3100_ERROR;
    uint16_t event = 0;

    if ( ctx->ready )
    {
        if ( CC3100_CMD_CONNECT == opcode )
        {
            event = CC3100_EVT_SOCKET_CONNECT;
        }
        error_flag = cc3100_write_command( ctx, opcode, buffer, len );
        if ( CC3100_OK == error_flag )
        {
            error_flag = cc3100_wait_response( ctx, response, event );
        }
    }
    return error_flag;
}

static err_t cc3100_check_status ( cc3100_t *ctx )
{
    err_t error_flag = CC3100_OK;

    if ( ctx->response_length < 4 )
    {
        ctx->ready = 0;
        error_flag = CC3100_PROTOCOL_ERROR;
    }
    else
    {
        ctx->module_error = ( int16_t ) cc3100_get_u16( ctx->response );
        if ( ctx->module_error < 0 )
        {
            error_flag = CC3100_MODULE_ERROR;
        }
    }
    return error_flag;
}

static err_t cc3100_get_config ( cc3100_t *ctx, uint16_t opcode, uint16_t id,
                                 uint16_t option, uint16_t length )
{
    uint8_t buffer[ 8 ] = { 0 };
    err_t error_flag;

    cc3100_put_u16( &buffer[ 2 ], id );
    cc3100_put_u16( &buffer[ 4 ], option );
    cc3100_put_u16( &buffer[ 6 ], length );
    error_flag = cc3100_command( ctx, opcode, buffer, sizeof( buffer ), opcode & CC3100_RESPONSE_MASK );
    if ( CC3100_OK == error_flag )
    {
        error_flag = cc3100_check_status( ctx );
        // Use the received payload length; the echoed configuration length varies between service packs.
        if ( ( CC3100_OK == error_flag ) && ( ctx->response_length < length + 8 ) )
        {
            error_flag = CC3100_PROTOCOL_ERROR;
            ctx->ready = 0;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
