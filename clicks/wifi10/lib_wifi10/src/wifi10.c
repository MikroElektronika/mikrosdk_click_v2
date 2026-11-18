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
 * @file wifi10.c
 * @brief WiFi 10 Click Driver.
 * @details QCA4004 hosted SPI transport, firmware startup, station control, and IPv4 socket offload.
 * @note See wifi10_protocol.h for the notices applicable to the QCA4004 hosted protocol adaptation.
 */

#include "wifi10.h"
#include "wifi10_protocol.h"
#include "wifi10_wpa.h"

/**
 * @brief WiFi 10 SPI startup function.
 * @details Releases reset with the hosted SPI straps set and then opens and configures the SPI master.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in,out] spi_cfg : SPI master configuration with the selected clock, MISO, and MOSI pins.
 * @return @li @c 0 - SPI master ready,
 *         @li @c -1 - Bootstrap pin or SPI setup error.
 * See #err_t definition for detailed explanation.
 * @note The SPI master must be closed and CHIP_PWD_L must be low on entry.
 */
static err_t wifi10_start_spi ( wifi10_t *ctx, spi_master_config_t *spi_cfg );

/**
 * @brief Little-endian 16-bit field decoding function.
 * @details Decodes two bytes without requiring an aligned firmware record.
 * @param[in] buffer : First byte of the field.
 * @return Decoded 16-bit value.
 */
static uint16_t wifi10_get_le16 ( uint8_t *buffer );

/**
 * @brief Little-endian 32-bit field decoding function.
 * @details Decodes four bytes without requiring an aligned firmware record.
 * @param[in] buffer : First byte of the field.
 * @return Decoded 32-bit value.
 */
static uint32_t wifi10_get_le32 ( uint8_t *buffer );

/**
 * @brief Little-endian 16-bit field encoding function.
 * @details Stores the low byte first in a firmware record.
 * @param[out] buffer : Destination with room for two bytes.
 * @param[in] value : Value to encode.
 * @return Nothing.
 */
static void wifi10_put_le16 ( uint8_t *buffer, uint16_t value );

/**
 * @brief Little-endian 32-bit field encoding function.
 * @details Stores the low byte first in a firmware record.
 * @param[out] buffer : Destination with room for four bytes.
 * @param[in] value : Value to encode.
 * @return Nothing.
 */
static void wifi10_put_le32 ( uint8_t *buffer, uint32_t value );

/**
 * @brief QCA4004 SPI transfer function.
 * @details Sends an address token followed by a transfer through an internal port or the mailbox.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] address : SPI address with the internal access bit set for register ports.
 * @param[in,out] buffer : Source bytes for writes or destination for reads.
 * @param[in] length : Number of bytes to transfer.
 * @param[in] read : Set to 1 to read or 0 to write.
 * @return @li @c 0 - Transfer complete,
 *         @li @c -1 - SPI transfer error.
 * See #err_t definition for detailed explanation.
 * @note Mailbox writes use separate chip-select pulses for the address token and payload.
 */
static err_t wifi10_transfer ( wifi10_t *ctx, uint16_t address, uint8_t *buffer, uint16_t length, uint8_t read );

/**
 * @brief QCA4004 host register access function.
 * @details Transfers bytes at consecutive host addresses and polls for completion.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] address : First host register address.
 * @param[in,out] buffer : Source bytes for writes or destination for reads.
 * @param[in] length : Number of bytes to transfer, from 1 to WIFI10_HOST_MAX_LENGTH.
 * @param[in] read : Set to 1 to read or 0 to write.
 * @return @li @c 0 - Access complete,
 *         @li @c -1 - Invalid transfer length or SPI error,
 *         @li @c -2 - Host access timed out.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_host_access ( wifi10_t *ctx, uint16_t address, uint8_t *buffer, uint8_t length, uint8_t read );

/**
 * @brief QCA4004 diagnostic window address function.
 * @details Writes the high bytes of the target address first. Writing the low byte triggers the access.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] reg : Diagnostic read or write address register.
 * @param[in] address : Target memory address.
 * @return @li @c 0 - Diagnostic window address set,
 *         @li @c -1 - SPI access error,
 *         @li @c -2 - Host access timed out.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_diag_address ( wifi10_t *ctx, uint16_t reg, uint32_t address );

/**
 * @brief QCA4004 diagnostic read function.
 * @details Selects the target address and reads one 32-bit word through the diagnostic window.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] address : Target memory address.
 * @param[out] value : Decoded word, updated on success.
 * @return @li @c 0 - Word read,
 *         @li @c -1 - SPI access error,
 *         @li @c -2 - Host access timed out.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_diag_read ( wifi10_t *ctx, uint32_t address, uint32_t *value );

/**
 * @brief QCA4004 diagnostic write function.
 * @details Loads the value register before writing the target address to trigger the write.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] address : Target memory address.
 * @param[in] value : Word in host numeric order.
 * @return @li @c 0 - Word written,
 *         @li @c -1 - SPI access error,
 *         @li @c -2 - Host access timed out.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_diag_write ( wifi10_t *ctx, uint32_t address, uint32_t value );

/**
 * @brief HTC credit initialization function.
 * @details Resets credit counters and allocates credits to the fixed hosted endpoints.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] count : Total transmit credit budget.
 * @return @li @c 0 - Credits allocated,
 *         @li @c -3 - Fewer than three credits available.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_credit_init ( wifi10_t *ctx, uint8_t count );

/**
 * @brief HTC credit counter function.
 * @details Recovers credits from the firmware counter and reconciles credits already reported in trailers.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] endpoint : HTC endpoint whose credits are being recovered.
 * @return @li @c 0 - Credit check complete,
 *         @li @c -3 - Credit count overflow,
 *         @li @c <0 - Host access error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Counter recovery is available after the firmware publishes its credit counters.
 */
static err_t wifi10_credit_update ( wifi10_t *ctx, uint8_t endpoint );

/**
 * @brief HTC trailer processing function.
 * @details Checks trailer record lengths and accounts for credits already recovered from firmware counters.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] buffer : First byte of the trailer.
 * @param[in] length : Trailer length in bytes.
 * @return @li @c 0 - Trailer processed,
 *         @li @c -3 - Invalid trailer record, endpoint, or credit count.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_read_trailer ( wifi10_t *ctx, uint8_t *buffer, uint16_t length );

/**
 * @brief QCA4004 CPU interrupt handling function.
 * @details Reads the CPU interrupt cause, initializes published transmit credits, and acknowledges the interrupt.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @return @li @c 0 - Interrupt acknowledged,
 *         @li @c -3 - Invalid initial credit count,
 *         @li @c <0 - Host access error.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_handle_cpu_irq ( wifi10_t *ctx );

/**
 * @brief HTC mailbox receive function.
 * @details Reads one complete frame when enough bytes are available and checks its header and trailer before dispatch.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @return @li @c 0 - Poll complete, including when no frame was available,
 *         @li @c <0 - Transport, frame validation, or event processing error.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_read_frame ( wifi10_t *ctx );

/**
 * @brief HTC mailbox transmit function.
 * @details Waits for credits and FIFO space, adds the HTC header, and sends the padded frame.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] endpoint : HTC endpoint for the frame.
 * @param[in] length : Frame length with the HTC header and without padding.
 * @return @li @c 0 - Frame transferred,
 *         @li @c -2 - Transmit wait or transport timed out,
 *         @li @c <0 - Transport, protocol, or socket error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Prepare the WMI bytes in ctx->tx_buf before calling this function.
 */
static err_t wifi10_send_frame ( wifi10_t *ctx, uint8_t endpoint, uint16_t length );

/**
 * @brief Firmware response wait function.
 * @details Services incoming frames until a state byte reaches the requested value.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] flag : State byte inspected after event processing.
 * @param[in] expected : Required value of the state byte.
 * @param[in] timeout : Polling delay budget in milliseconds.
 * @return @li @c 0 - Requested state reached,
 *         @li @c -2 - Wait or transport timed out,
 *         @li @c <0 - Transport, disconnect, or event processing error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note A timeout leaves a driver fault that requires a hardware reset.
 */
static err_t wifi10_wait_flag ( wifi10_t *ctx, uint8_t *flag, uint8_t expected, uint32_t timeout );

/**
 * @brief WMI control command function.
 * @details Writes the WMI command header and sends the payload on the control endpoint.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] command : WMI command identifier.
 * @param[in] payload : Command payload, or NULL if length is zero.
 * @param[in] length : Payload length in bytes.
 * @return @li @c 0 - Command frame transferred,
 *         @li @c -1 - Frame too large or SPI transfer error,
 *         @li @c <0 - Transport or event processing error.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_command ( wifi10_t *ctx, uint16_t command, uint8_t *payload, uint16_t length );

/**
 * @brief WPA2 key digit decoding function.
 * @details Decodes an ASCII hexadecimal digit and accepts uppercase and lowercase letters.
 * @param[in] digit : ASCII character to decode.
 * @return Value from 0 to 15, or WIFI10_HEX_INVALID.
 */
static uint8_t wifi10_hex_value ( uint8_t digit );

/**
 * @brief WMI control event function.
 * @details Checks the WMI header and dispatches station events and socket replies for device zero.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] buffer : Event bytes including the WMI header.
 * @param[in] length : Event length in bytes.
 * @return @li @c 0 - Event handled or ignored,
 *         @li @c -3 - Invalid control event length,
 *         @li @c -4 - Firmware rejected a command,
 *         @li @c -7 - Firmware error or incompatible ABI.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_control_event ( wifi10_t *ctx, uint8_t *buffer, uint16_t length );

/**
 * @brief Socket offload command function.
 * @details Sends a socket command and waits for a reply matching the command and expected handle.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] command : Socket command identifier.
 * @param[in] handle : Expected socket handle, or zero for open and global commands.
 * @param[in] payload : Payload following the socket command header.
 * @param[in] length : Payload length in bytes.
 * @param[in] timeout : Response polling delay budget in milliseconds.
 * @return @li @c 0 - Command completed successfully,
 *         @li @c -4 - Firmware rejected the socket command,
 *         @li @c <0 - Transport, timeout, or connection error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note A timed-out command may still be pending in firmware. Reset the module before retrying.
 */
static err_t wifi10_socket_command ( wifi10_t *ctx, uint32_t command, int32_t handle,
                                     uint8_t *payload, uint16_t length, uint32_t timeout );

/**
 * @brief Socket offload response function.
 * @details Updates sockets on close indications and stores replies that match an outstanding command.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] buffer : Socket response following the WMI header.
 * @param[in] length : Socket response length in bytes.
 * @return @li @c 0 - Response handled or ignored,
 *         @li @c -3 - Incomplete socket header or IPv4 configuration.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_socket_response ( wifi10_t *ctx, uint8_t *buffer, uint16_t length );

/**
 * @brief Socket payload event function.
 * @details Buffers the payload for its owning socket and preserves TCP byte order and UDP datagram boundaries.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] buffer : Received bytes including the WMI data header.
 * @param[in] length : Frame length in bytes.
 * @return @li @c 0 - Frame buffered or no local socket owns the frame,
 *         @li @c -3 - Invalid frame for a local socket,
 *         @li @c -6 - Receive buffer full or datagram too large.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_socket_event ( wifi10_t *ctx, uint8_t *buffer, uint16_t length );

/**
 * @brief Socket handle lookup function.
 * @details Searches the allocated socket slots for a positive firmware handle.
 * @param[in] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] handle : Firmware socket handle.
 * @return Matching socket or NULL.
 */
static wifi10_socket_t *wifi10_find_socket ( wifi10_t *ctx, int32_t handle );

/**
 * @brief Socket payload transmit function.
 * @details Builds the offload header and reserves the firmware's TCP or UDP headroom before sending.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] socket : Allocated socket for the transmission.
 * @param[in] payload : Payload bytes.
 * @param[in] length : Payload length in bytes.
 * @param[in] address : UDP destination in host numeric order. Unused for TCP.
 * @param[in] port : UDP destination port. Unused for TCP.
 * @return @li @c 0 - Payload frame transferred to the module,
 *         @li @c -1 - Invalid payload or SPI transfer error,
 *         @li @c <0 - Transport, timeout, or socket error.
 * See #wifi10_return_value_t definition for detailed explanation.
 */
static err_t wifi10_send_payload ( wifi10_t *ctx, wifi10_socket_t *socket, uint8_t *payload, uint16_t length,
                                   uint32_t address, uint16_t port );

void wifi10_cfg_setup ( wifi10_cfg_t *cfg )
{
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->fet     = HAL_PIN_NC;
    cfg->iot     = HAL_PIN_NC;
    cfg->pwd     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = WIFI10_SPI_DEFAULT_SPEED;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t wifi10_init ( wifi10_t *ctx, wifi10_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;
    err_t error_flag = SPI_MASTER_SUCCESS;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;
    ctx->cfg = *cfg;
    ctx->spi_open = 0;
    memset( &ctx->state, 0, sizeof( ctx->state ) );

    // Assert reset before driving the power and mode pins.
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->pwd, cfg->pwd ) )
    {
        error_flag = WIFI10_ERROR;
    }
    if ( WIFI10_ERROR != error_flag )
    {
        digital_out_low( &ctx->pwd );
        if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->fet, cfg->fet ) )
        {
            error_flag = WIFI10_ERROR;
        }
    }
    if ( WIFI10_ERROR != error_flag )
    {
        digital_out_low( &ctx->fet );
        if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->iot, cfg->iot ) )
        {
            error_flag = WIFI10_ERROR;
        }
    }
    if ( WIFI10_ERROR != error_flag )
    {
        digital_out_high( &ctx->iot );

        // Input pin.
        if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->int_pin, cfg->int_pin ) )
        {
            error_flag = WIFI10_ERROR;
        }
    }
    if ( WIFI10_ERROR != error_flag )
    {
        error_flag = wifi10_start_spi( ctx, &spi_cfg );
    }
    ctx->state.fault = error_flag;

    return error_flag;
}

err_t wifi10_hw_reset ( wifi10_t *ctx )
{
    spi_master_config_t spi_cfg;
    err_t error_flag = SPI_MASTER_SUCCESS;

    digital_out_low( &ctx->pwd );
    if ( ctx->spi_open )
    {
        error_flag = spi_master_close( &ctx->spi );
        if ( SPI_MASTER_ERROR != error_flag )
        {
            ctx->spi_open = 0;
        }
    }
    if ( SPI_MASTER_ERROR != error_flag )
    {
        spi_master_configure_default( &spi_cfg );
        spi_cfg.sck  = ctx->cfg.sck;
        spi_cfg.miso = ctx->cfg.miso;
        spi_cfg.mosi = ctx->cfg.mosi;
        error_flag = wifi10_start_spi( ctx, &spi_cfg );
    }
    memset( &ctx->state, 0, sizeof( ctx->state ) );
    ctx->state.fault = error_flag;

    return error_flag;
}

err_t wifi10_default_cfg ( wifi10_t *ctx )
{
    uint16_t space = 0;
    uint32_t refclk = 0;
    uint32_t attempt;
    uint8_t stack_cfg[ WIFI10_SOCKET_HEADER + 4u ] = { 0 };
    uint8_t power = WIFI10_WMI_MAX_PERFORMANCE;
    uint8_t bss_filter[ WIFI10_BSS_FILTER_SIZE ] = { WIFI10_BSS_FILTER_NONE };
    uint8_t channel_cfg[ WIFI10_CHANNEL_PARAMS_SIZE ] = { 0, 0, WIFI10_WMI_PHY_11G };
    uint8_t ht_cfg[ WIFI10_HT_CAP_SIZE ] = { WIFI10_WMI_HT_BAND_24, 1, 0, 1, 0, 0, WIFI10_WMI_HT_AMPDU_EXP };
    err_t error_flag = ctx->state.fault;

    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_write_reg( ctx, WIFI10_REG_CONFIG, WIFI10_CONFIG_IO_ENABLE | WIFI10_CONFIG_KEEP_AWAKE );
        // The SDK postpones external accesses for 100 ms after starting the target CPU.
        Delay_100ms( );
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_read_reg( ctx, WIFI10_REG_WRITE_SPACE, &space );
        if ( ( WIFI10_OK == error_flag ) && ( WIFI10_WRITE_SPACE_INITIAL != space ) )
        {
            error_flag = WIFI10_ERROR_PROTOCOL;
        }
    }
    if ( WIFI10_OK == error_flag )
    {
        // Polling keeps device IRQ outputs masked, including throughout mailbox transfers.
        error_flag = wifi10_write_reg( ctx, WIFI10_REG_INT_ENABLE, 0 );
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_write_reg( ctx, WIFI10_REG_WRITE_WATERMARK, 0 );
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_write_reg( ctx, WIFI10_REG_INT_CAUSE, WIFI10_SPI_IRQ_WATERMARK );
    }
    for ( attempt = 0; ( WIFI10_OK == error_flag ) && ( attempt < WIFI10_BOOT_TIMEOUT ); attempt++ )
    {
        error_flag = wifi10_diag_read( ctx, WIFI10_HI_REFCLK, &refclk );
        if ( ( WIFI10_OK != error_flag ) || ( WIFI10_REFCLK == refclk ) )
        {
            break;
        }
        Delay_1ms( );
    }
    if ( ( WIFI10_OK == error_flag ) && ( WIFI10_REFCLK != refclk ) )
    {
        error_flag = WIFI10_ERROR_TIMEOUT;
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_credit_init( ctx, WIFI10_DEFAULT_CREDITS );
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_diag_write( ctx, WIFI10_HI_POWER, WIFI10_BOOT_POWER );
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_diag_write( ctx, WIFI10_HI_BOOT, WIFI10_BOOT_NORMAL );
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_diag_write( ctx, WIFI10_HI_OPTIONS, WIFI10_BOOT_OPTIONS );
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_wait_flag( ctx, &ctx->state.ready, 1, WIFI10_BOOT_TIMEOUT );
    }
    if ( WIFI10_OK == error_flag )
    {
        // Set the 2.4 GHz PHY without launching an automatic scan. CONNECT performs discovery.
        error_flag = wifi10_command( ctx, WIFI10_CMD_CHANNEL_PARAMS, channel_cfg, sizeof( channel_cfg ) );
    }
    if ( WIFI10_OK == error_flag )
    {
        // Match the SDK's 802.11n settings for 20 MHz channels in the 2.4 GHz band.
        error_flag = wifi10_command( ctx, WIFI10_CMD_HT_CAP, ht_cfg, sizeof( ht_cfg ) );
    }
    if ( WIFI10_OK == error_flag )
    {
        // SDK stack-init layout: enable, receive buffers, maximum sockets, reserved.
        wifi10_put_le32( stack_cfg, WIFI10_SOCK_STACK_INIT );
        wifi10_put_le32( stack_cfg + 4, 4 );
        stack_cfg[ 8 ] = 1;
        stack_cfg[ 9 ] = 2;
        stack_cfg[ 10 ] = WIFI10_MAX_SOCKETS;
        error_flag = wifi10_command( ctx, WIFI10_CMD_SOCKET, stack_cfg, sizeof( stack_cfg ) );
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_command( ctx, WIFI10_CMD_POWER, &power, sizeof( power ) );
    }
    if ( WIFI10_OK == error_flag )
    {
        // Keep beacon reports out of the host mailbox while the firmware searches for the AP.
        error_flag = wifi10_command( ctx, WIFI10_CMD_BSS_FILTER, bss_filter, sizeof( bss_filter ) );
    }
    if ( WIFI10_OK == error_flag )
    {
        // Require a WMI reply after all radio and socket setup commands have been sent.
        ctx->state.channel_list_ready = 0;
        error_flag = wifi10_command( ctx, WIFI10_CMD_CHANNEL_LIST, NULL, 0 );
        if ( WIFI10_OK == error_flag )
        {
            error_flag = wifi10_wait_flag( ctx, &ctx->state.channel_list_ready, 1, WIFI10_COMMAND_TIMEOUT );
        }
    }
    if ( WIFI10_OK != error_flag )
    {
        ctx->state.fault = error_flag;
    }

    return error_flag;
}

err_t wifi10_write_reg ( wifi10_t *ctx, uint16_t reg, uint16_t value )
{
    uint8_t buffer[ 4 ];
    err_t error_flag;

    reg |= WIFI10_SPI_INTERNAL;
    buffer[ 0 ] = ( uint8_t ) ( reg >> 8 );
    buffer[ 1 ] = ( uint8_t ) reg;
    buffer[ 2 ] = ( uint8_t ) ( value >> 8 );
    buffer[ 3 ] = ( uint8_t ) value;
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    error_flag = spi_master_write( &ctx->spi, buffer, sizeof( buffer ) );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t wifi10_read_reg ( wifi10_t *ctx, uint16_t reg, uint16_t *value )
{
    uint8_t command[ 2 ];
    uint8_t buffer[ 2 ];
    err_t error_flag;

    reg |= WIFI10_SPI_INTERNAL | WIFI10_SPI_READ;
    command[ 0 ] = ( uint8_t ) ( reg >> 8 );
    command[ 1 ] = ( uint8_t ) reg;
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    error_flag = spi_master_write_then_read( &ctx->spi, command, sizeof( command ), buffer, sizeof( buffer ) );
    spi_master_deselect_device( ctx->chip_select );
    if ( SPI_MASTER_SUCCESS == error_flag )
    {
        *value = ( ( uint16_t ) buffer[ 0 ] << 8 ) | buffer[ 1 ];
    }

    return error_flag;
}

err_t wifi10_process ( wifi10_t *ctx )
{
    uint16_t interrupts = 0;
    err_t error_flag = ctx->state.fault;

    if ( ( WIFI10_OK == error_flag ) && ( 0u == ctx->spi_open ) )
    {
        error_flag = WIFI10_ERROR;
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_read_reg( ctx, WIFI10_REG_INT_CAUSE, &interrupts );
    }
    if ( ( WIFI10_OK == error_flag ) && ( interrupts & WIFI10_SPI_IRQ_ERRORS ) )
    {
        ctx->state.protocol_fault = "SPI interrupt";
        ctx->state.protocol_detail = interrupts;
        error_flag = WIFI10_ERROR_PROTOCOL;
    }
    if ( ( WIFI10_OK == error_flag ) && ( interrupts & WIFI10_SPI_IRQ_CPU ) )
    {
        error_flag = wifi10_handle_cpu_irq( ctx );
    }
    if ( ( WIFI10_OK == error_flag ) && ( interrupts & WIFI10_SPI_IRQ_PACKET ) )
    {
        error_flag = wifi10_write_reg( ctx, WIFI10_REG_INT_CAUSE, WIFI10_SPI_IRQ_PACKET );
    }
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_read_frame( ctx );
    }
    if ( WIFI10_OK != error_flag )
    {
        ctx->state.fault = error_flag;
    }

    return error_flag;
}

err_t wifi10_connect ( wifi10_t *ctx, char *ssid, char *password, uint8_t auth )
{
    uint8_t buffer[ WIFI10_STATION_CMD_SIZE ];
    uint16_t ssid_length = 0;
    uint16_t password_length = 0;
    uint32_t connect_flags = WIFI10_WMI_FOLLOW_CHANNEL;
    uint32_t elapsed = 0;
    err_t error_flag = WIFI10_ERROR;

    // Clear the buffer separately so mikroC AI does not copy flash padding into ssid_length.
    memset( buffer, 0, sizeof( buffer ) );

    if ( ( NULL != ssid ) && ( NULL != password ) )
    {
        while ( ( ssid_length <= WIFI10_SSID_MAX_LENGTH ) && ssid[ ssid_length ] )
        {
            ssid_length++;
        }
        while ( ( password_length <= WIFI10_PMK_HEX_LENGTH ) && password[ password_length ] )
        {
            password_length++;
        }
        if ( ( ssid_length > 0u ) && ( ssid_length <= WIFI10_SSID_MAX_LENGTH ) &&
             ( ( ( WIFI10_AUTH_OPEN == auth ) && ( 0u == password_length ) ) ||
               ( ( WIFI10_AUTH_WPA2_PSK == auth ) && ( password_length >= 8u ) &&
                 ( ( password_length <= WIFI10_PASSWORD_MAX_LENGTH ) || ( WIFI10_PMK_HEX_LENGTH == password_length ) ) ) ) )
        {
            error_flag = ctx->state.fault;
            if ( ( WIFI10_OK == error_flag ) && ( ( 0u == ctx->state.ready ) || ctx->state.associated ) )
            {
                error_flag = WIFI10_ERROR;
            }
            for ( uint16_t index = 0; ( WIFI10_OK == error_flag ) && ( index < password_length ); index++ )
            {
                if ( ( ( uint8_t ) password[ index ] < 0x20u ) || ( ( uint8_t ) password[ index ] > 0x7Eu ) )
                {
                    error_flag = WIFI10_ERROR;
                }
            }
        }
    }
    if ( ( WIFI10_OK == error_flag ) && ( WIFI10_AUTH_WPA2_PSK == auth ) )
    {
        if ( WIFI10_PMK_HEX_LENGTH == password_length )
        {
            for ( uint8_t index = 0; index < WIFI10_PMK_LENGTH; index++ )
            {
                uint8_t high = wifi10_hex_value( ( uint8_t ) password[ 2u * index ] );
                uint8_t low = wifi10_hex_value( ( uint8_t ) password[ 2u * index + 1u ] );
                if ( ( WIFI10_HEX_INVALID == high ) || ( WIFI10_HEX_INVALID == low ) )
                {
                    error_flag = WIFI10_ERROR;
                    break;
                }
                buffer[ index ] = ( uint8_t ) ( ( high << 4 ) | low );
            }
        }
        else
        {
            wifi10_derive_pmk( ssid, ( uint8_t ) ssid_length, password, ( uint8_t ) password_length, buffer );
        }
        if ( WIFI10_OK == error_flag )
        {
            buffer[ WIFI10_PMK_LENGTH ] = WIFI10_PMK_LENGTH;
            error_flag = wifi10_command( ctx, WIFI10_CMD_SET_PMK, buffer, WIFI10_PMK_CMD_SIZE );
        }
        memset( buffer, 0, sizeof( buffer ) );
        memset( ctx->tx_buf, 0, sizeof( ctx->tx_buf ) );
    }
    if ( WIFI10_OK == error_flag )
    {
        // Apply the SDK's connect scan policy. Zero fields retain firmware defaults.
        wifi10_put_le16( buffer + 4, WIFI10_WMI_BG_SCAN_DISABLED );
        buffer[ 10 ] = WIFI10_WMI_SHORT_SCAN_RATIO;
        buffer[ 11 ] = WIFI10_WMI_DEFAULT_SCAN_FLAGS;
        error_flag = wifi10_command( ctx, WIFI10_CMD_SCAN_PARAMS, buffer, WIFI10_SCAN_PARAMS_SIZE );
    }
    if ( WIFI10_OK == error_flag )
    {
        memset( buffer, 0, sizeof( buffer ) );
        buffer[ 0 ] = WIFI10_WMI_NETWORK_STATION;
        buffer[ 1 ] = WIFI10_WMI_AUTH_OPEN;
        buffer[ 2 ] = WIFI10_WMI_AUTH_NONE;
        buffer[ 3 ] = WIFI10_WMI_CRYPT_NONE;
        buffer[ 5 ] = WIFI10_WMI_CRYPT_NONE;
        if ( WIFI10_AUTH_WPA2_PSK == auth )
        {
            buffer[ 2 ] = WIFI10_WMI_AUTH_WPA2;
            buffer[ 3 ] = WIFI10_WMI_CRYPT_AES;
            buffer[ 5 ] = WIFI10_WMI_CRYPT_AES;
            connect_flags |= WIFI10_WMI_WPA_OFFLOAD | WIFI10_WMI_IGNORE_GROUP_CIPHER;
        }
        buffer[ 7 ] = ( uint8_t ) ssid_length;
        memcpy( buffer + 8, ssid, ssid_length );
        // Leave the channel hint and BSSID at zero so firmware selects the AP.
        wifi10_put_le32( buffer + 48, connect_flags );
        ctx->state.station_auth = auth;
        ctx->state.disconnect_reason = 0;
        error_flag = wifi10_command( ctx, WIFI10_CMD_CONNECT, buffer, WIFI10_STATION_CMD_SIZE );
    }
    while ( ( WIFI10_OK == error_flag ) && ( 0u == ctx->state.connected ) && ( elapsed < WIFI10_CONNECT_TIMEOUT ) )
    {
        error_flag = wifi10_process( ctx );
        // The firmware keeps scanning after NO_NETWORK_AVAIL.
        if ( ( WIFI10_OK == error_flag ) && ctx->state.disconnect_reason &&
             ( WIFI10_DISCONNECT_NO_NETWORK != ctx->state.disconnect_reason ) )
        {
            error_flag = WIFI10_ERROR_DISCONNECTED;
        }
        if ( ( WIFI10_OK == error_flag ) && ( 0u == ctx->state.connected ) )
        {
            Delay_1ms( );
            elapsed++;
        }
    }
    if ( ( WIFI10_OK == error_flag ) && ( 0u == ctx->state.connected ) )
    {
        error_flag = WIFI10_ERROR_TIMEOUT;
        ctx->state.fault = error_flag;
    }

    return error_flag;
}

err_t wifi10_disconnect ( wifi10_t *ctx )
{
    err_t error_flag = ctx->state.fault;

    if ( ( WIFI10_OK == error_flag ) && ctx->state.associated )
    {
        error_flag = wifi10_command( ctx, WIFI10_CMD_DISCONNECT, NULL, 0 );
        if ( WIFI10_OK == error_flag )
        {
            error_flag = wifi10_wait_flag( ctx, &ctx->state.associated, 0, WIFI10_COMMAND_TIMEOUT );
        }
    }

    return error_flag;
}

err_t wifi10_dhcp ( wifi10_t *ctx, wifi10_ip_cfg_t *ip )
{
    uint8_t buffer[ WIFI10_IPCONFIG_CMD_SIZE ] = { 0 };
    uint32_t poll_delay = 0;
    err_t error_flag = WIFI10_ERROR;

    if ( NULL != ip )
    {
        wifi10_put_le32( buffer, WIFI10_IPCONFIG_DHCP );
        ctx->state.dhcp_start = 1;
        error_flag = wifi10_socket_command( ctx, WIFI10_SOCK_IPCONFIG, 0, buffer, sizeof( buffer ), WIFI10_DHCP_TIMEOUT );
        ctx->state.dhcp_start = 0;

        // The SDK queries the offloaded stack after DHCP start until an address is available.
        wifi10_put_le32( buffer, WIFI10_IPCONFIG_QUERY );
        while ( ( WIFI10_OK == error_flag ) && ( 0ul == ctx->state.ip.address ) && ( poll_delay < WIFI10_DHCP_TIMEOUT ) )
        {
            Delay_100ms( );
            poll_delay += WIFI10_IPCONFIG_POLL_MS;
            error_flag = wifi10_socket_command( ctx, WIFI10_SOCK_IPCONFIG, 0, buffer, sizeof( buffer ),
                                                WIFI10_COMMAND_TIMEOUT );
        }
        if ( WIFI10_OK == error_flag )
        {
            if ( 0ul == ctx->state.ip.address )
            {
                error_flag = WIFI10_ERROR_TIMEOUT;
                ctx->state.fault = error_flag;
            }
            else
            {
                *ip = ctx->state.ip;
            }
        }
    }

    return error_flag;
}

err_t wifi10_socket_open ( wifi10_t *ctx, uint8_t type, int32_t *handle )
{
    uint8_t buffer[ 12 ] = { 0 };
    uint8_t index;
    wifi10_socket_t *socket = NULL;
    err_t error_flag = WIFI10_ERROR;

    if ( ( NULL != handle ) && ( ( WIFI10_SOCKET_TCP == type ) || ( WIFI10_SOCKET_UDP == type ) ) )
    {
        for ( index = 0; index < WIFI10_MAX_SOCKETS; index++ )
        {
            if ( 0 == ctx->state.sockets[ index ].handle )
            {
                socket = &ctx->state.sockets[ index ];
                break;
            }
        }
        if ( NULL != socket )
        {
            wifi10_put_le32( buffer, WIFI10_AF_INET );
            wifi10_put_le32( buffer + 4, type );
            error_flag = wifi10_socket_command( ctx, WIFI10_SOCK_OPEN, 0, buffer, sizeof( buffer ), WIFI10_COMMAND_TIMEOUT );
            if ( WIFI10_OK == error_flag )
            {
                if ( ( ctx->state.response_handle <= 0 ) ||
                     ( NULL != wifi10_find_socket( ctx, ctx->state.response_handle ) ) )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                    ctx->state.fault = error_flag;
                }
                else
                {
                    memset( socket, 0, sizeof( *socket ) );
                    socket->handle = ctx->state.response_handle;
                    socket->type = type;
                    *handle = socket->handle;
                }
            }
        }
    }

    return error_flag;
}

err_t wifi10_socket_connect ( wifi10_t *ctx, int32_t handle, uint32_t address, uint16_t port )
{
    uint8_t buffer[ WIFI10_CONNECT_CMD_SIZE ] = { 0 };
    wifi10_socket_t *socket = wifi10_find_socket( ctx, handle );
    err_t error_flag = WIFI10_ERROR;

    if ( ( NULL != socket ) && ( WIFI10_SOCKET_TCP == socket->type ) &&
         ( 0u == socket->closed ) && ( 0u == socket->connected ) && address && port )
    {
        wifi10_put_le32( buffer, ( uint32_t ) handle );
        wifi10_put_le16( buffer + 4, port );
        wifi10_put_le16( buffer + 6, WIFI10_AF_INET );
        wifi10_put_le32( buffer + 8, address );
        // The address union reserves 28 bytes for the SDK's IPv6 sockaddr.
        wifi10_put_le16( buffer + 32, WIFI10_SOCKADDR_SIZE );
        error_flag = wifi10_socket_command( ctx, WIFI10_SOCK_CONNECT, handle, buffer, sizeof( buffer ),
                                            WIFI10_CONNECT_TIMEOUT );
        if ( WIFI10_OK == error_flag )
        {
            socket->connected = 1;
        }
    }

    return error_flag;
}

err_t wifi10_socket_send ( wifi10_t *ctx, int32_t handle, uint8_t *payload, uint16_t length )
{
    wifi10_socket_t *socket = wifi10_find_socket( ctx, handle );
    err_t error_flag = WIFI10_ERROR;

    if ( ( NULL != socket ) && ( WIFI10_SOCKET_TCP == socket->type ) && socket->connected && ( 0u == socket->closed ) )
    {
        error_flag = wifi10_send_payload( ctx, socket, payload, length, 0, 0 );
    }

    return error_flag;
}

err_t wifi10_socket_sendto ( wifi10_t *ctx, int32_t handle, uint8_t *payload, uint16_t length,
                             uint32_t address, uint16_t port )
{
    wifi10_socket_t *socket = wifi10_find_socket( ctx, handle );
    err_t error_flag = WIFI10_ERROR;

    if ( ( NULL != socket ) && ( WIFI10_SOCKET_UDP == socket->type ) && ( 0u == socket->closed ) && address && port )
    {
        error_flag = wifi10_send_payload( ctx, socket, payload, length, address, port );
    }

    return error_flag;
}

err_t wifi10_socket_recv ( wifi10_t *ctx, int32_t handle, uint8_t *payload, uint16_t capacity,
                           uint16_t *received, uint32_t timeout )
{
    wifi10_socket_t *socket = wifi10_find_socket( ctx, handle );
    uint32_t elapsed = 0;
    uint16_t copy_length;
    err_t error_flag = WIFI10_ERROR;

    if ( NULL != received )
    {
        *received = 0;
        if ( ( NULL != socket ) && ( NULL != payload ) && capacity )
        {
            error_flag = ctx->state.fault;
            while ( ( WIFI10_OK == error_flag ) && ( 0u == socket->rx_pending ) )
            {
                if ( 0u == ctx->state.connected )
                {
                    error_flag = WIFI10_ERROR_DISCONNECTED;
                    break;
                }
                if ( socket->closed )
                {
                    error_flag = WIFI10_ERROR_CLOSED;
                    break;
                }
                error_flag = wifi10_process( ctx );
                if ( ( WIFI10_OK == error_flag ) && ( 0u == socket->rx_pending ) )
                {
                    if ( 0u == ctx->state.connected )
                    {
                        error_flag = WIFI10_ERROR_DISCONNECTED;
                    }
                    else if ( socket->closed )
                    {
                        error_flag = WIFI10_ERROR_CLOSED;
                    }
                }
                if ( ( WIFI10_OK != error_flag ) || socket->rx_pending )
                {
                    break;
                }
                if ( elapsed >= timeout )
                {
                    error_flag = WIFI10_ERROR_TIMEOUT;
                    break;
                }
                Delay_1ms( );
                elapsed++;
            }
            if ( ( WIFI10_OK == error_flag ) && socket->rx_pending )
            {
                copy_length = socket->rx_length - socket->rx_offset;
                if ( ( WIFI10_SOCKET_UDP == socket->type ) && ( copy_length > capacity ) )
                {
                    error_flag = WIFI10_ERROR_BUFFER;
                }
                else
                {
                    if ( copy_length > capacity )
                    {
                        copy_length = capacity;
                    }
                    memcpy( payload, socket->rx_buf + socket->rx_offset, copy_length );
                    socket->rx_offset += copy_length;
                    *received = copy_length;
                    if ( socket->rx_offset == socket->rx_length )
                    {
                        socket->rx_offset = 0;
                        socket->rx_length = 0;
                        socket->rx_pending = 0;
                    }
                }
            }
        }
    }

    return error_flag;
}

err_t wifi10_socket_close ( wifi10_t *ctx, int32_t handle )
{
    uint8_t buffer[ 4 ];
    wifi10_socket_t *socket = wifi10_find_socket( ctx, handle );
    err_t error_flag = WIFI10_ERROR;

    if ( NULL != socket )
    {
        error_flag = ctx->state.fault;
        if ( ( WIFI10_OK == error_flag ) && ( 0u == socket->closed ) )
        {
            wifi10_put_le32( buffer, ( uint32_t ) handle );
            error_flag = wifi10_socket_command( ctx, WIFI10_SOCK_CLOSE, handle, buffer, sizeof( buffer ),
                                                WIFI10_COMMAND_TIMEOUT );
        }
        if ( WIFI10_OK == error_flag )
        {
            memset( socket, 0, sizeof( *socket ) );
        }
    }

    return error_flag;
}

static err_t wifi10_start_spi ( wifi10_t *ctx, spi_master_config_t *spi_cfg )
{
    digital_in_t clock_pin;
    digital_out_t select_pin;
    err_t error_flag = SPI_MASTER_SUCCESS;

    /* Leave SCK high-impedance and hold CS/HM1 high when CHIP_PWD_L rises. */
    if ( ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &clock_pin, ctx->cfg.sck ) ) ||
         ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &select_pin, ctx->cfg.cs ) ) )
    {
        error_flag = WIFI10_ERROR;
    }
    else
    {
        digital_out_high( &select_pin );
        digital_out_low( &ctx->fet );
        digital_out_high( &ctx->iot );
        Delay_100ms( );
        digital_out_high( &ctx->pwd );
        Delay_100ms( );

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, spi_cfg ) )
        {
            error_flag = SPI_MASTER_ERROR;
        }
        else
        {
            ctx->spi_open = 1;
            if ( ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, WIFI10_DUMMY ) ) ||
                 ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, ctx->cfg.spi_mode ) ) ||
                 ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, ctx->cfg.spi_speed ) ) )
            {
                error_flag = SPI_MASTER_ERROR;
            }
            else
            {
                spi_master_set_chip_select_polarity( ctx->cfg.cs_polarity );
                spi_master_deselect_device( ctx->chip_select );
            }
        }
        if ( SPI_MASTER_ERROR == error_flag )
        {
            digital_out_low( &ctx->pwd );
            if ( ctx->spi_open && ( SPI_MASTER_ERROR != spi_master_close( &ctx->spi ) ) )
            {
                ctx->spi_open = 0;
            }
        }
    }

    return error_flag;
}

static uint16_t wifi10_get_le16 ( uint8_t *buffer )
{
    return ( uint16_t ) buffer[ 0 ] | ( ( uint16_t ) buffer[ 1 ] << 8 );
}

static uint32_t wifi10_get_le32 ( uint8_t *buffer )
{
    return ( uint32_t ) buffer[ 0 ] | ( ( uint32_t ) buffer[ 1 ] << 8 ) |
           ( ( uint32_t ) buffer[ 2 ] << 16 ) | ( ( uint32_t ) buffer[ 3 ] << 24 );
}

static void wifi10_put_le16 ( uint8_t *buffer, uint16_t value )
{
    buffer[ 0 ] = ( uint8_t ) value;
    buffer[ 1 ] = ( uint8_t ) ( value >> 8 );
}

static void wifi10_put_le32 ( uint8_t *buffer, uint32_t value )
{
    buffer[ 0 ] = ( uint8_t ) value;
    buffer[ 1 ] = ( uint8_t ) ( value >> 8 );
    buffer[ 2 ] = ( uint8_t ) ( value >> 16 );
    buffer[ 3 ] = ( uint8_t ) ( value >> 24 );
}

static err_t wifi10_transfer ( wifi10_t *ctx, uint16_t address, uint8_t *buffer, uint16_t length, uint8_t read )
{
    uint8_t command[ 2 ];
    err_t error_flag;

    if ( read )
    {
        address |= WIFI10_SPI_READ;
    }
    command[ 0 ] = ( uint8_t ) ( address >> 8 );
    command[ 1 ] = ( uint8_t ) address;
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    if ( read )
    {
        error_flag = spi_master_write_then_read( &ctx->spi, command, sizeof( command ), buffer, length );
    }
    else
    {
        error_flag = spi_master_write( &ctx->spi, command, sizeof( command ) );
        if ( SPI_MASTER_SUCCESS == error_flag )
        {
            if ( 0u == ( address & WIFI10_SPI_INTERNAL ) )
            {
                // The hosted SDK ends the mailbox address token before starting the DMA byte stream.
                Delay_10us( );
                spi_master_deselect_device( ctx->chip_select );
                Delay_10us( );
                spi_master_select_device( ctx->chip_select );
                Delay_10us( );
            }
            error_flag = spi_master_write( &ctx->spi, buffer, length );
        }
    }
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t wifi10_host_access ( wifi10_t *ctx, uint16_t address, uint8_t *buffer, uint8_t length, uint8_t read )
{
    uint16_t status = 0;
    uint16_t attempt;
    uint16_t control = WIFI10_HOST_ENABLE | address;
    err_t error_flag = WIFI10_ERROR;

    if ( ( length > 0u ) && ( length <= WIFI10_HOST_MAX_LENGTH ) )
    {
        error_flag = wifi10_write_reg( ctx, WIFI10_REG_HOST_SIZE, length );
        if ( ( WIFI10_OK == error_flag ) && ( 0u == read ) )
        {
            control |= WIFI10_HOST_WRITE;
            error_flag = wifi10_transfer( ctx, WIFI10_SPI_INTERNAL | WIFI10_REG_HOST_WRITE, buffer, length, 0 );
        }
        if ( WIFI10_OK == error_flag )
        {
            error_flag = wifi10_write_reg( ctx, WIFI10_REG_HOST_CONFIG, control );
        }
        for ( attempt = 0; ( WIFI10_OK == error_flag ) && ( attempt < WIFI10_HOST_POLL_LIMIT ); attempt++ )
        {
            error_flag = wifi10_read_reg( ctx, WIFI10_REG_STATUS, &status );
            if ( ( WIFI10_OK != error_flag ) || ( status & WIFI10_HOST_DONE ) )
            {
                break;
            }
            Delay_1ms( );
        }
        if ( ( WIFI10_OK == error_flag ) && ( 0u == ( status & WIFI10_HOST_DONE ) ) )
        {
            error_flag = WIFI10_ERROR_TIMEOUT;
        }
        if ( ( WIFI10_OK == error_flag ) && read )
        {
            error_flag = wifi10_transfer( ctx, WIFI10_SPI_INTERNAL | WIFI10_REG_HOST_READ, buffer, length, 1 );
        }
        if ( WIFI10_OK == error_flag )
        {
            error_flag = wifi10_write_reg( ctx, WIFI10_REG_INT_CAUSE, WIFI10_SPI_IRQ_HOST_DONE );
        }
    }

    return error_flag;
}

static err_t wifi10_diag_address ( wifi10_t *ctx, uint16_t reg, uint32_t address )
{
    uint8_t buffer[ 4 ];
    err_t error_flag;

    wifi10_put_le32( buffer, address );
    error_flag = wifi10_host_access( ctx, reg + 1u, &buffer[ 1 ], 3, 0 );
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_host_access( ctx, reg, buffer, 1, 0 );
    }

    return error_flag;
}

static err_t wifi10_diag_read ( wifi10_t *ctx, uint32_t address, uint32_t *value )
{
    uint8_t buffer[ 4 ];
    err_t error_flag = wifi10_diag_address( ctx, WIFI10_WINDOW_READ, address );

    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_host_access( ctx, WIFI10_WINDOW_VALUE, buffer, sizeof( buffer ), 1 );
        if ( WIFI10_OK == error_flag )
        {
            *value = wifi10_get_le32( buffer );
        }
    }

    return error_flag;
}

static err_t wifi10_diag_write ( wifi10_t *ctx, uint32_t address, uint32_t value )
{
    uint8_t buffer[ 4 ];
    err_t error_flag;

    wifi10_put_le32( buffer, value );
    error_flag = wifi10_host_access( ctx, WIFI10_WINDOW_VALUE, buffer, sizeof( buffer ), 0 );
    if ( WIFI10_OK == error_flag )
    {
        error_flag = wifi10_diag_address( ctx, WIFI10_WINDOW_WRITE, address );
    }

    return error_flag;
}

static err_t wifi10_credit_init ( wifi10_t *ctx, uint8_t count )
{
    err_t error_flag = WIFI10_ERROR_PROTOCOL;

    if ( count >= 3u )
    {
        memset( ctx->state.credits, 0, sizeof( ctx->state.credits ) );
        memset( ctx->state.reported, 0, sizeof( ctx->state.reported ) );
        memset( ctx->state.borrowed, 0, sizeof( ctx->state.borrowed ) );
        ctx->state.credits[ 0 ] = 1;
        ctx->state.credits[ WIFI10_EP_CONTROL ] = 1;
        ctx->state.credits[ WIFI10_EP_DATA ] = count - 2u;
        error_flag = WIFI10_OK;
    }

    return error_flag;
}

static err_t wifi10_credit_update ( wifi10_t *ctx, uint8_t endpoint )
{
    uint8_t counters[ 4 ];
    uint8_t credits;
    err_t error_flag = WIFI10_OK;

    if ( ctx->state.credit_init )
    {
        error_flag = wifi10_host_access( ctx, WIFI10_CREDIT_COUNTER + 4u * ( endpoint >> 2 ),
                                         counters, sizeof( counters ), 1 );
        if ( WIFI10_OK == error_flag )
        {
            credits = ( uint8_t ) ( counters[ endpoint & 3u ] - ctx->state.reported[ endpoint ] );
            if ( credits >= ctx->state.borrowed[ endpoint ] )
            {
                credits -= ctx->state.borrowed[ endpoint ];
                if ( ( uint16_t ) ctx->state.credits[ endpoint ] + credits > 255u )
                {
                    ctx->state.protocol_fault = "HTC credit counter";
                    ctx->state.protocol_detail = credits;
                    error_flag = WIFI10_ERROR_PROTOCOL;
                }
                else
                {
                    ctx->state.credits[ endpoint ] += credits;
                    ctx->state.borrowed[ endpoint ] += credits;
                }
            }
        }
    }

    return error_flag;
}

static err_t wifi10_read_trailer ( wifi10_t *ctx, uint8_t *buffer, uint16_t length )
{
    err_t error_flag = WIFI10_OK;
    uint16_t offset = 0;
    uint8_t record_length;
    uint8_t index;
    uint8_t endpoint;
    uint8_t credits;

    while ( ( offset < length ) && ( WIFI10_OK == error_flag ) )
    {
        if ( length - offset < 2u )
        {
            error_flag = WIFI10_ERROR_PROTOCOL;
            break;
        }
        record_length = buffer[ offset + 1u ];
        if ( ( uint16_t ) record_length > length - offset - 2u )
        {
            error_flag = WIFI10_ERROR_PROTOCOL;
            break;
        }
        if ( WIFI10_HTC_CREDIT_RECORD == buffer[ offset ] )
        {
            if ( record_length & 1u )
            {
                error_flag = WIFI10_ERROR_PROTOCOL;
                break;
            }
            for ( index = 0; index < record_length; index += 2u )
            {
                endpoint = buffer[ offset + 2u + index ];
                credits = buffer[ offset + 3u + index ];
                if ( endpoint >= WIFI10_ENDPOINT_COUNT )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                    break;
                }
                ctx->state.reported[ endpoint ] += credits;
                if ( credits >= ctx->state.borrowed[ endpoint ] )
                {
                    credits -= ctx->state.borrowed[ endpoint ];
                    ctx->state.borrowed[ endpoint ] = 0;
                }
                else
                {
                    ctx->state.borrowed[ endpoint ] -= credits;
                    credits = 0;
                }
                if ( ( uint16_t ) ctx->state.credits[ endpoint ] + credits > 255u )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                    break;
                }
                ctx->state.credits[ endpoint ] += credits;
            }
        }
        offset += ( uint16_t ) record_length + 2u;
    }

    return error_flag;
}

static err_t wifi10_handle_cpu_irq ( wifi10_t *ctx )
{
    uint8_t cpu_status;
    uint8_t counters[ 4 ];
    err_t error_flag;

    error_flag = wifi10_host_access( ctx, WIFI10_CPU_INT_STATUS, &cpu_status, 1, 1 );
    if ( ( WIFI10_OK == error_flag ) && ( cpu_status & 1u ) && ( 0u == ctx->state.credit_init ) )
    {
        error_flag = wifi10_host_access( ctx, WIFI10_CREDIT_COUNTER + 4u, counters, sizeof( counters ), 1 );
        if ( WIFI10_OK == error_flag )
        {
            error_flag = wifi10_credit_init( ctx, counters[ 3 ] );
            if ( WIFI10_OK == error_flag )
            {
                ctx->state.credit_init = 1;
            }
            else
            {
                ctx->state.protocol_fault = "HTC credit initialization";
                ctx->state.protocol_detail = counters[ 3 ];
            }
        }
    }
    if ( WIFI10_OK == error_flag )
    {
        cpu_status = 0xFFu;
        error_flag = wifi10_host_access( ctx, WIFI10_CPU_INT_STATUS, &cpu_status, 1, 0 );
    }

    return error_flag;
}

static err_t wifi10_read_frame ( wifi10_t *ctx )
{
    uint16_t available = 0;
    uint16_t lookahead_1 = 0;
    uint16_t lookahead_2 = 0;
    uint16_t payload_length;
    uint16_t frame_length;
    uint16_t transfer_length;
    uint8_t trailer_length;
    uint8_t endpoint;
    err_t error_flag;

    error_flag = wifi10_read_reg( ctx, WIFI10_REG_READ_AVAILABLE, &available );
    if ( ( WIFI10_OK == error_flag ) && ( available >= WIFI10_HTC_HEADER ) )
    {
        error_flag = wifi10_read_reg( ctx, WIFI10_REG_LOOKAHEAD_1, &lookahead_1 );
        if ( WIFI10_OK == error_flag )
        {
            error_flag = wifi10_read_reg( ctx, WIFI10_REG_LOOKAHEAD_2, &lookahead_2 );
        }
        payload_length = ( lookahead_2 >> 8 ) | ( ( uint16_t ) ( lookahead_2 & 0xFFu ) << 8 );
        endpoint = ( uint8_t ) ( lookahead_1 >> 8 );
        if ( ( WIFI10_OK == error_flag ) &&
             ( ( endpoint >= WIFI10_ENDPOINT_COUNT ) || ( payload_length > WIFI10_FRAME_SIZE - WIFI10_HTC_HEADER ) ) )
        {
            ctx->state.protocol_fault = "HTC lookahead";
            ctx->state.protocol_detail = payload_length;
            error_flag = WIFI10_ERROR_PROTOCOL;
        }
        frame_length = payload_length + WIFI10_HTC_HEADER;
        transfer_length = ( frame_length + WIFI10_BLOCK_SIZE - 1u ) & ~( WIFI10_BLOCK_SIZE - 1u );
        // A DMA read larger than the current FIFO byte count is discarded by the module.
        if ( ( WIFI10_OK == error_flag ) && ( available >= transfer_length ) )
        {
            error_flag = wifi10_write_reg( ctx, WIFI10_REG_DMA_SIZE, transfer_length );
            if ( WIFI10_OK == error_flag )
            {
                error_flag = wifi10_transfer( ctx, WIFI10_MAILBOX_END - transfer_length,
                                              ctx->rx_buf, transfer_length, 1 );
            }
            if ( ( WIFI10_OK == error_flag ) &&
                 ( ( ctx->rx_buf[ 0 ] != endpoint ) ||
                   ( ctx->rx_buf[ 1 ] != ( uint8_t ) lookahead_1 ) ||
                   ( wifi10_get_le16( ctx->rx_buf + 2 ) != payload_length ) ) )
            {
                ctx->state.protocol_fault = "HTC header";
                ctx->state.protocol_detail = payload_length;
                error_flag = WIFI10_ERROR_PROTOCOL;
            }
            if ( ( WIFI10_OK == error_flag ) && ( ctx->rx_buf[ 1 ] & WIFI10_HTC_TRAILER ) )
            {
                trailer_length = ctx->rx_buf[ 4 ];
                if ( ( trailer_length < 2u ) || ( trailer_length > payload_length ) )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                }
                else
                {
                    error_flag = wifi10_read_trailer( ctx, ctx->rx_buf + frame_length - trailer_length,
                                                      trailer_length );
                    payload_length -= trailer_length;
                }
                if ( WIFI10_ERROR_PROTOCOL == error_flag )
                {
                    ctx->state.protocol_fault = "HTC trailer";
                    ctx->state.protocol_detail = trailer_length;
                }
            }
            if ( ( WIFI10_OK == error_flag ) && payload_length )
            {
                if ( WIFI10_EP_CONTROL == endpoint )
                {
                    error_flag = wifi10_control_event( ctx, ctx->rx_buf + WIFI10_HTC_HEADER, payload_length );
                    if ( WIFI10_ERROR_PROTOCOL == error_flag )
                    {
                        ctx->state.protocol_fault = "WMI control frame";
                        ctx->state.protocol_detail = payload_length;
                    }
                }
                else if ( endpoint >= WIFI10_EP_DATA )
                {
                    error_flag = wifi10_socket_event( ctx, ctx->rx_buf + WIFI10_HTC_HEADER, payload_length );
                    if ( WIFI10_ERROR_PROTOCOL == error_flag )
                    {
                        ctx->state.protocol_fault = "WMI socket frame";
                        ctx->state.protocol_detail = payload_length;
                    }
                }
            }
        }
    }

    return error_flag;
}

static err_t wifi10_send_frame ( wifi10_t *ctx, uint8_t endpoint, uint16_t length )
{
    uint16_t transfer_length = ( length + WIFI10_BLOCK_SIZE - 1u ) & ~( WIFI10_BLOCK_SIZE - 1u );
    uint16_t space = 0;
    uint32_t attempt;
    uint8_t can_send = 0;
    uint32_t socket_command = WIFI10_SOCK_STACK_INIT;
    wifi10_socket_t *socket = NULL;
    err_t error_flag = ctx->state.fault;

    if ( WIFI10_EP_DATA == endpoint )
    {
        socket = wifi10_find_socket( ctx, ( int32_t ) wifi10_get_le32(
            ctx->tx_buf + WIFI10_HTC_HEADER + WIFI10_WMI_HEADER + WIFI10_WMI_META_SIZE ) );
    }
    else if ( WIFI10_CMD_SOCKET == wifi10_get_le16( ctx->tx_buf + WIFI10_HTC_HEADER ) )
    {
        socket_command = wifi10_get_le32( ctx->tx_buf + WIFI10_HTC_HEADER + WIFI10_WMI_HEADER );
        if ( ( WIFI10_SOCK_CONNECT == socket_command ) || ( WIFI10_SOCK_CLOSE == socket_command ) )
        {
            socket = wifi10_find_socket( ctx, ( int32_t ) wifi10_get_le32(
                ctx->tx_buf + WIFI10_HTC_HEADER + WIFI10_WMI_HEADER + WIFI10_SOCKET_HEADER ) );
        }
    }
    for ( attempt = 0; ( WIFI10_OK == error_flag ) && ( attempt < WIFI10_COMMAND_TIMEOUT ); attempt++ )
    {
        error_flag = wifi10_process( ctx );
        if ( ( WIFI10_OK == error_flag ) &&
             ( ( WIFI10_EP_DATA == endpoint ) || ( WIFI10_SOCK_STACK_INIT != socket_command ) ) )
        {
            if ( 0u == ctx->state.connected )
            {
                error_flag = WIFI10_ERROR_DISCONNECTED;
            }
            else if ( ( NULL != socket ) && socket->closed )
            {
                error_flag = WIFI10_ERROR_CLOSED;
            }
        }
        if ( ( WIFI10_OK == error_flag ) && ( 0u == ctx->state.credits[ endpoint ] ) )
        {
            error_flag = wifi10_credit_update( ctx, endpoint );
        }
        if ( WIFI10_OK == error_flag )
        {
            error_flag = wifi10_read_reg( ctx, WIFI10_REG_WRITE_SPACE, &space );
        }
        if ( ( WIFI10_OK == error_flag ) && ctx->state.credits[ endpoint ] &&
             ( space >= transfer_length + WIFI10_WRITE_OVERHEAD ) )
        {
            can_send = 1;
            break;
        }
        if ( WIFI10_OK == error_flag )
        {
            Delay_1ms( );
        }
    }
    if ( ( WIFI10_OK == error_flag ) && ( 0u == can_send ) )
    {
        error_flag = WIFI10_ERROR_TIMEOUT;
    }
    if ( WIFI10_OK == error_flag )
    {
        ctx->tx_buf[ 0 ] = endpoint;
        ctx->tx_buf[ 1 ] = WIFI10_HTC_NEED_CREDIT;
        wifi10_put_le16( ctx->tx_buf + 2, length - WIFI10_HTC_HEADER );
        ctx->tx_buf[ 4 ] = 0;
        ctx->tx_buf[ 5 ] = ctx->state.sequence[ endpoint ];
        memset( ctx->tx_buf + length, 0, transfer_length - length );
        error_flag = wifi10_write_reg( ctx, WIFI10_REG_DMA_SIZE, transfer_length );
        if ( WIFI10_OK == error_flag )
        {
            error_flag = wifi10_transfer( ctx, WIFI10_MAILBOX_END - transfer_length,
                                          ctx->tx_buf, transfer_length, 0 );
        }
        if ( WIFI10_OK == error_flag )
        {
            ctx->state.credits[ endpoint ]--;
            ctx->state.sequence[ endpoint ]++;
        }
    }
    if ( ( WIFI10_OK != error_flag ) && ( WIFI10_ERROR_DISCONNECTED != error_flag ) &&
         ( WIFI10_ERROR_CLOSED != error_flag ) )
    {
        ctx->state.fault = error_flag;
    }

    return error_flag;
}

static err_t wifi10_wait_flag ( wifi10_t *ctx, uint8_t *flag, uint8_t expected, uint32_t timeout )
{
    uint32_t elapsed = 0;
    err_t error_flag = ctx->state.fault;

    while ( ( WIFI10_OK == error_flag ) && ( *flag != expected ) && ( elapsed < timeout ) )
    {
        error_flag = wifi10_process( ctx );
        if ( ( WIFI10_OK == error_flag ) && ctx->state.response_pending && ( 0u == ctx->state.connected ) )
        {
            error_flag = WIFI10_ERROR_DISCONNECTED;
            ctx->state.fault = error_flag;
        }
        if ( ( WIFI10_OK == error_flag ) && ( *flag != expected ) )
        {
            Delay_1ms( );
            elapsed++;
        }
    }
    if ( ( WIFI10_OK == error_flag ) && ( *flag != expected ) )
    {
        error_flag = WIFI10_ERROR_TIMEOUT;
        ctx->state.fault = error_flag;
    }

    return error_flag;
}

static err_t wifi10_command ( wifi10_t *ctx, uint16_t command, uint8_t *payload, uint16_t length )
{
    uint16_t frame_length = WIFI10_HTC_HEADER + WIFI10_WMI_HEADER + length;
    err_t error_flag = WIFI10_ERROR;

    if ( frame_length <= WIFI10_FRAME_SIZE )
    {
        memset( ctx->tx_buf, 0, WIFI10_HTC_HEADER + WIFI10_WMI_HEADER );
        wifi10_put_le16( ctx->tx_buf + WIFI10_HTC_HEADER, command );
        if ( length )
        {
            memmove( ctx->tx_buf + WIFI10_HTC_HEADER + WIFI10_WMI_HEADER, payload, length );
        }
        error_flag = wifi10_send_frame( ctx, WIFI10_EP_CONTROL, frame_length );
    }

    return error_flag;
}

static uint8_t wifi10_hex_value ( uint8_t digit )
{
    uint8_t value = WIFI10_HEX_INVALID;

    if ( ( digit >= '0' ) && ( digit <= '9' ) )
    {
        value = digit - '0';
    }
    else if ( ( digit >= 'A' ) && ( digit <= 'F' ) )
    {
        value = digit - 'A' + 10u;
    }
    else if ( ( digit >= 'a' ) && ( digit <= 'f' ) )
    {
        value = digit - 'a' + 10u;
    }

    return value;
}

static err_t wifi10_control_event ( wifi10_t *ctx, uint8_t *buffer, uint16_t length )
{
    uint16_t event;
    err_t error_flag = WIFI10_OK;

    if ( length < WIFI10_WMI_HEADER )
    {
        error_flag = WIFI10_ERROR_PROTOCOL;
    }
    else if ( 0u == ( wifi10_get_le16( buffer + 2 ) & WIFI10_WMI_DEVICE_MASK ) )
    {
        event = wifi10_get_le16( buffer );
        buffer += WIFI10_WMI_HEADER;
        length -= WIFI10_WMI_HEADER;
        switch ( event )
        {
            case WIFI10_CMD_CHANNEL_LIST:
            {
                // This command uses the same identifier for its reply.
                if ( ( length < WIFI10_CHANNEL_LIST_HEADER ) ||
                     ( buffer[ 1 ] > ( length - WIFI10_CHANNEL_LIST_HEADER ) / sizeof( uint16_t ) ) )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                }
                else
                {
                    ctx->state.channel_list_ready = 1;
                }
                break;
            }
            case WIFI10_EVENT_READY:
            {
                if ( length < 15u )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                }
                else
                {
                    ctx->state.firmware_version = wifi10_get_le32( buffer );
                    ctx->state.abi_version = wifi10_get_le32( buffer + 4 );
                    memcpy( ctx->state.mac, buffer + 8, sizeof( ctx->state.mac ) );
                    if ( ( 1ul != ctx->state.abi_version ) &&
                         ( WIFI10_ABI_MAJOR != ( ctx->state.abi_version & WIFI10_ABI_MAJOR_MASK ) ) )
                    {
                        error_flag = WIFI10_ERROR_FIRMWARE;
                    }
                    else
                    {
                        ctx->state.ready = 1;
                    }
                }
                break;
            }
            case WIFI10_EVENT_CONNECT:
            {
                if ( length < 19u )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                }
                else
                {
                    ctx->state.associated = 1;
                    ctx->state.disconnect_reason = 0;
                    if ( WIFI10_AUTH_OPEN == ctx->state.station_auth )
                    {
                        ctx->state.connected = 1;
                    }
                }
                break;
            }
            case WIFI10_EVENT_PEER_NODE:
            {
                if ( length < WIFI10_PEER_EVENT_SIZE )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                }
                else if ( ( WIFI10_PEER_JOIN == buffer[ 0 ] ) && ctx->state.associated &&
                          ( WIFI10_AUTH_WPA2_PSK == ctx->state.station_auth ) )
                {
                    // The firmware reports WPA2 four-way handshake completion as a peer join.
                    ctx->state.connected = 1;
                }
                break;
            }
            case WIFI10_EVENT_DISCONNECT:
            {
                if ( length < 10u )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                }
                else
                {
                    ctx->state.associated = 0;
                    ctx->state.connected = 0;
                    ctx->state.disconnect_reason = buffer[ 8 ];
                    memset( &ctx->state.ip, 0, sizeof( ctx->state.ip ) );
                    for ( uint8_t index = 0; index < WIFI10_MAX_SOCKETS; index++ )
                    {
                        ctx->state.sockets[ index ].closed = 1;
                        ctx->state.sockets[ index ].connected = 0;
                    }
                }
                break;
            }
            case WIFI10_EVENT_CMD_ERROR:
            {
                if ( length < 3u )
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                }
                else
                {
                    ctx->state.command_error = wifi10_get_le16( buffer );
                    ctx->state.command_reason = buffer[ 2 ];
                    error_flag = WIFI10_ERROR_COMMAND;
                }
                break;
            }
            case WIFI10_EVENT_TARGET_ERROR:
            {
                error_flag = WIFI10_ERROR_FIRMWARE;
                break;
            }
            case WIFI10_EVENT_SOCKET:
            {
                error_flag = wifi10_socket_response( ctx, buffer, length );
                break;
            }
            default:
            {
                // Other firmware indications do not complete a pending socket command.
                break;
            }
        }
    }

    return error_flag;
}

static err_t wifi10_socket_command ( wifi10_t *ctx, uint32_t command, int32_t handle,
                                     uint8_t *payload, uint16_t length, uint32_t timeout )
{
    uint8_t *buffer = ctx->tx_buf + WIFI10_HTC_HEADER + WIFI10_WMI_HEADER;
    err_t error_flag = ctx->state.fault;

    if ( ( WIFI10_OK == error_flag ) && ( ctx->state.response_pending || ( 0u == ctx->state.connected ) ) )
    {
        error_flag = WIFI10_ERROR_DISCONNECTED;
    }
    if ( WIFI10_OK == error_flag )
    {
        wifi10_put_le32( buffer, command );
        wifi10_put_le32( buffer + 4, length );
        memcpy( buffer + WIFI10_SOCKET_HEADER, payload, length );
        ctx->state.response_type = command;
        ctx->state.expected_handle = handle;
        ctx->state.response_pending = 0;
        ctx->state.response_ready = 0;
        error_flag = wifi10_command( ctx, WIFI10_CMD_SOCKET, buffer, length + WIFI10_SOCKET_HEADER );
        if ( WIFI10_OK == error_flag )
        {
            ctx->state.response_pending = 1;
            error_flag = wifi10_wait_flag( ctx, &ctx->state.response_ready, 1, timeout );
        }
        else if ( ( WIFI10_SOCK_CLOSE == command ) && ( WIFI10_ERROR_CLOSED == error_flag ) )
        {
            ctx->state.response_result = 0;
            error_flag = WIFI10_OK;
        }
        if ( ( WIFI10_OK == error_flag ) && ( 0 != ctx->state.response_result ) )
        {
            error_flag = WIFI10_ERROR_COMMAND;
        }
    }

    return error_flag;
}

static err_t wifi10_socket_response ( wifi10_t *ctx, uint8_t *buffer, uint16_t length )
{
    uint32_t response;
    int32_t handle;
    int32_t result;
    wifi10_socket_t *socket;
    err_t error_flag = WIFI10_OK;

    if ( length < WIFI10_SOCKET_RESPONSE )
    {
        error_flag = WIFI10_ERROR_PROTOCOL;
    }
    else
    {
        response = wifi10_get_le32( buffer );
        handle = ( int32_t ) wifi10_get_le32( buffer + 4 );
        result = ( int32_t ) wifi10_get_le32( buffer + 8 );
        if ( ( WIFI10_SOCK_CLOSE == response ) && ( 0 == result ) )
        {
            socket = wifi10_find_socket( ctx, handle );
            if ( NULL != socket )
            {
                socket->closed = 1;
                socket->connected = 0;
            }
        }
        if ( ctx->state.response_pending && ( response == ctx->state.response_type ) &&
             ( ( 0 == ctx->state.expected_handle ) || ( handle == ctx->state.expected_handle ) ) )
        {
            ctx->state.response_handle = handle;
            ctx->state.response_result = result;
            if ( WIFI10_SOCK_OPEN == response )
            {
                // SOCK_OPEN reports success or failure through the socket handle.
                ctx->state.response_result = 0;
                if ( WIFI10_SOCK_OPEN_FAILED == handle )
                {
                    ctx->state.response_result = handle;
                }
            }
            else if ( ( WIFI10_SOCK_IPCONFIG == response ) && ( 0 == result ) )
            {
                if ( length >= WIFI10_SOCKET_RESPONSE + WIFI10_IPCONFIG_IPV4_SIZE )
                {
                    buffer += WIFI10_SOCKET_RESPONSE;
                    ctx->state.ip.address = wifi10_get_le32( buffer + 4u );
                    ctx->state.ip.subnet = wifi10_get_le32( buffer + 8u );
                    ctx->state.ip.gateway = wifi10_get_le32( buffer + 12u );
                }
                else if ( ctx->state.dhcp_start && ( length <= WIFI10_SOCKET_ACK_SIZE ) )
                {
                    // This acknowledgment ends at the socket response header.
                    memset( &ctx->state.ip, 0, sizeof( ctx->state.ip ) );
                }
                else
                {
                    error_flag = WIFI10_ERROR_PROTOCOL;
                }
            }
            if ( WIFI10_OK == error_flag )
            {
                ctx->state.response_pending = 0;
                ctx->state.response_ready = 1;
            }
        }
    }

    return error_flag;
}

static err_t wifi10_socket_event ( wifi10_t *ctx, uint8_t *buffer, uint16_t length )
{
    wifi10_socket_t *socket = NULL;
    uint16_t payload_length;
    err_t error_flag = WIFI10_OK;

    // As in the SDK, discard data without a local socket owner.
    if ( ( length >= WIFI10_WMI_HEADER + sizeof( int32_t ) ) && ( 0u == ( buffer[ 4 ] & WIFI10_WMI_DEVICE_MASK ) ) )
    {
        socket = wifi10_find_socket( ctx, ( int32_t ) wifi10_get_le32( buffer + WIFI10_WMI_HEADER ) );
    }
    if ( NULL != socket )
    {
        if ( ( length < WIFI10_WMI_HEADER + WIFI10_SOCKET_RECV_HEADER ) ||
             ( buffer[ 1 ] & WIFI10_RX_INFO_UNSUPPORTED ) ||
             ( wifi10_get_le16( buffer + 2 ) & WIFI10_RX_INFO2_UNSUPPORTED ) ||
             ( wifi10_get_le16( buffer + 4 ) & WIFI10_RX_INFO3_UNSUPPORTED ) )
        {
            error_flag = WIFI10_ERROR_PROTOCOL;
        }
        else
        {
            buffer += WIFI10_WMI_HEADER;
            payload_length = length - WIFI10_WMI_HEADER - WIFI10_SOCKET_RECV_HEADER;
            if ( WIFI10_SOCKET_UDP == socket->type )
            {
                if ( socket->rx_pending || ( payload_length > WIFI10_RX_CAPACITY ) )
                {
                    error_flag = WIFI10_ERROR_BUFFER;
                }
                else
                {
                    socket->peer_port = wifi10_get_le16( buffer + 4 );
                    socket->peer_address = wifi10_get_le32( buffer + 8 );
                    memcpy( socket->rx_buf, buffer + WIFI10_SOCKET_RECV_HEADER, payload_length );
                    socket->rx_length = payload_length;
                    socket->rx_offset = 0;
                    socket->rx_pending = 1;
                }
            }
            else
            {
                if ( socket->rx_offset )
                {
                    socket->rx_length -= socket->rx_offset;
                    memmove( socket->rx_buf, socket->rx_buf + socket->rx_offset, socket->rx_length );
                    socket->rx_offset = 0;
                }
                if ( payload_length > WIFI10_RX_CAPACITY - socket->rx_length )
                {
                    error_flag = WIFI10_ERROR_BUFFER;
                }
                else if ( payload_length )
                {
                    memcpy( socket->rx_buf + socket->rx_length, buffer + WIFI10_SOCKET_RECV_HEADER, payload_length );
                    socket->rx_length += payload_length;
                    socket->rx_pending = 1;
                }
            }
        }
    }

    return error_flag;
}

static wifi10_socket_t *wifi10_find_socket ( wifi10_t *ctx, int32_t handle )
{
    wifi10_socket_t *socket = NULL;
    uint8_t index;

    if ( handle > 0 )
    {
        for ( index = 0; index < WIFI10_MAX_SOCKETS; index++ )
        {
            if ( ctx->state.sockets[ index ].handle == handle )
            {
                socket = &ctx->state.sockets[ index ];
                break;
            }
        }
    }

    return socket;
}

static err_t wifi10_send_payload ( wifi10_t *ctx, wifi10_socket_t *socket, uint8_t *payload, uint16_t length,
                                   uint32_t address, uint16_t port )
{
    uint16_t headroom = WIFI10_TCP_HEADROOM;
    uint16_t offset = WIFI10_HTC_HEADER + WIFI10_WMI_HEADER + WIFI10_WMI_META_SIZE;
    uint8_t *buffer = ctx->tx_buf + offset;
    err_t error_flag = WIFI10_ERROR;

    if ( ( NULL != payload ) && ( length > 0u ) && ( length <= WIFI10_MAX_PAYLOAD ) && ctx->state.connected )
    {
        if ( WIFI10_SOCKET_UDP == socket->type )
        {
            headroom = WIFI10_UDP_HEADROOM;
        }
        memset( ctx->tx_buf, 0, offset + headroom );
        wifi10_put_le16( ctx->tx_buf + WIFI10_HTC_HEADER + 2u, WIFI10_WMI_META_OFFLOAD );
        wifi10_put_le32( buffer, ( uint32_t ) socket->handle );
        wifi10_put_le16( buffer + 4, length );
        if ( WIFI10_SOCKET_UDP == socket->type )
        {
            wifi10_put_le16( buffer + 12, port );
            wifi10_put_le16( buffer + 14, WIFI10_AF_INET );
            wifi10_put_le32( buffer + 16, address );
            wifi10_put_le16( buffer + 20, WIFI10_SOCKADDR_SIZE );
        }
        memcpy( buffer + headroom, payload, length );
        error_flag = wifi10_send_frame( ctx, WIFI10_EP_DATA, offset + headroom + length );
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
