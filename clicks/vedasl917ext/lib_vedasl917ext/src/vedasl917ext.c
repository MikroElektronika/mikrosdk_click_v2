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
 * @file vedasl917ext.c
 * @brief Veda SL917 EXT Click Driver.
 * @details SiWN917 SPI framing follows Silicon Labs AN1432 and the WiSeConnect NCP interface.
 */

#include "vedasl917ext.h"

/**
 * @brief SPI default transmit byte.
 * @details Zero byte clocked on MOSI during SPI reads.
 */
#define VEDASL917EXT_DUMMY                  0x00

/**
 * @brief SiWN917 SPI control bytes and response tokens.
 * @details Specified codes for register, memory, and frame transfers, with their framing masks and sizes.
 */
#define VEDASL917EXT_SPI_REG_READ           0x41
#define VEDASL917EXT_SPI_REG_WRITE          0x62
#define VEDASL917EXT_SPI_MEM_READ           0x54
#define VEDASL917EXT_SPI_MEM_WRITE          0x74
#define VEDASL917EXT_SPI_FRAME_WRITE        0x7C
#define VEDASL917EXT_SPI_FRAME_LENGTH       0x5C
#define VEDASL917EXT_SPI_FRAME_READ         0x5D
#define VEDASL917EXT_SPI_SUCCESS            0x58
#define VEDASL917EXT_SPI_BUSY               0x54
#define VEDASL917EXT_SPI_FAIL               0x52
#define VEDASL917EXT_SPI_START              0x55
#define VEDASL917EXT_SPI_REG_MAX            0x3F
#define VEDASL917EXT_SPI_PREFIX_SIZE        4
#define VEDASL917EXT_LENGTH_MASK            0x0FFF
#define VEDASL917EXT_ALIGNMENT_MASK         0xFFFCu
#define VEDASL917EXT_QUEUE_SHIFT            4
#define VEDASL917EXT_STATUS_OFFSET          12
#define VEDASL917EXT_DISCARD_SIZE           16

/**
 * @brief Veda SL917 EXT bootloader settings.
 * @details Specified boot options, bootloader status values, and interrupt polarity mask.
 */
#define VEDASL917EXT_BOOT_VALID             0xAB
#define VEDASL917EXT_BOOT_STATUS_MASK       0xF000u
#define VEDASL917EXT_BOOT_STATUS_VALID      0xA000u
#define VEDASL917EXT_BOOT_LOAD              0x31
#define VEDASL917EXT_BOOT_CHECKSUM_OK       0xAA
#define VEDASL917EXT_BOOT_CHECKSUM_FAIL     0xCC
#define VEDASL917EXT_BOOT_NO_FIRMWARE       0x23
#define VEDASL917EXT_BOOT_NOT_SAVED         0xF1
#define VEDASL917EXT_BOOT_OPTIONS_FAIL      0xF2
#define VEDASL917EXT_BOOT_INVALID_OPTION    0xF3
#define VEDASL917EXT_INT_POLARITY_MASK      0xFC

/**
 * @brief Veda SL917 EXT command payload settings.
 * @details Specified payload sizes, radio settings, and offsets for decoding scan records.
 */
#define VEDASL917EXT_OPERMODE_SIZE          40
#define VEDASL917EXT_FEATURE_SIZE           12
#define VEDASL917EXT_FEATURE_RF_INTERNAL    1
#define VEDASL917EXT_FEATURE_AFE            1
#define VEDASL917EXT_FEATURE_ENABLES        0x31ul
#define VEDASL917EXT_BAND_2_4_GHZ           0
#define VEDASL917EXT_VERSION_SIZE           9
#define VEDASL917EXT_SCAN_REQUEST_SIZE      50
#define VEDASL917EXT_SCAN_SSID_OFFSET       4
#define VEDASL917EXT_SCAN_BSSID_OFFSET      38

/**
 * @brief Veda SL917 EXT station payload settings.
 * @details Specified request sizes and field offsets for association and IPv4 configuration.
 */
#define VEDASL917EXT_PSK_REQUEST_SIZE       99
#define VEDASL917EXT_PSK_PASSPHRASE         1
#define VEDASL917EXT_PSK_MIN_LEN            8
#define VEDASL917EXT_PSK_MAX_LEN            63
#define VEDASL917EXT_JOIN_REQUEST_SIZE      117
#define VEDASL917EXT_JOIN_SSID_OFFSET       68
#define VEDASL917EXT_JOIN_FLAGS_OFFSET      102
#define VEDASL917EXT_JOIN_SSID_LEN_OFFSET   105
#define VEDASL917EXT_JOIN_CCMP              0x80
#define VEDASL917EXT_JOIN_MFP_CAPABLE       0x20
#define VEDASL917EXT_DHCP_REQUEST_SIZE      59
#define VEDASL917EXT_DHCP_REPLY_SIZE        18
#define VEDASL917EXT_DHCP_UNICAST           0x09

/**
 * @brief Veda SL917 EXT socket payload settings.
 * @details Specified WiSeConnect 3.4.0 socket record sizes and offsets for SiWN917.
 * Port fields use little-endian byte order. IPv4 address bytes follow network order.
 */
#define VEDASL917EXT_QUEUE_SOCKET_DATA      5
#define VEDASL917EXT_SOCKET_DATA_FRAME      0
#define VEDASL917EXT_SOCKET_OPEN_SIZE       415
#define VEDASL917EXT_SOCKET_ID_OFFSET       4
#define VEDASL917EXT_SOCKET_OPEN_REPLY_MIN  6
#define VEDASL917EXT_SOCKET_RETRIES_OFFSET  134
#define VEDASL917EXT_SOCKET_FLAGS_OFFSET    135
#define VEDASL917EXT_SOCKET_WINDOW_OFFSET   136
#define VEDASL917EXT_SOCKET_KEEP_OFFSET     137
#define VEDASL917EXT_SOCKET_TCP_RETRIES     10
#define VEDASL917EXT_SOCKET_TCP_WINDOW      10
#define VEDASL917EXT_SOCKET_TCP_KEEP        1200u
#define VEDASL917EXT_SOCKET_RX_WINDOW_FLAG  0x10
#define VEDASL917EXT_SOCKET_TCP_TX_OFFSET   56
#define VEDASL917EXT_SOCKET_UDP_TX_OFFSET   44
#define VEDASL917EXT_SOCKET_RX_HDR_SIZE     28
#define VEDASL917EXT_DATA_ID_OFFSET         2
#define VEDASL917EXT_DATA_LENGTH_OFFSET     4
#define VEDASL917EXT_DATA_START_OFFSET      8
#define VEDASL917EXT_DATA_PORT_OFFSET       10
#define VEDASL917EXT_DATA_ADDRESS_OFFSET    12
#define VEDASL917EXT_SOCKET_CLOSE_SIZE      4
#define VEDASL917EXT_STATUS_NO_TCP_SERVER   0xBB38u
#define VEDASL917EXT_STATUS_NO_TCP_LEGACY   0xFF87u

/**
 * @brief Veda SL917 EXT 16-bit field decoding function.
 * @details This function decodes a little-endian field without requiring an aligned buffer.
 * @param[in] buffer : Pointer to the first of two bytes.
 * @return Decoded 16-bit value.
 */
static uint16_t vedasl917ext_get_u16 ( uint8_t *buffer );

/**
 * @brief Veda SL917 EXT 32-bit field decoding function.
 * @details This function decodes a little-endian field without requiring an aligned buffer.
 * @param[in] buffer : Pointer to the first of four bytes.
 * @return Decoded 32-bit value.
 */
static uint32_t vedasl917ext_get_u32 ( uint8_t *buffer );

/**
 * @brief Veda SL917 EXT 32-bit field encoding function.
 * @details This function stores a 32-bit value in little-endian byte order.
 * @param[out] buffer : Destination with room for four bytes.
 * @param[in] value : Value to encode.
 * @return Nothing.
 */
static void vedasl917ext_put_u32 ( uint8_t *buffer, uint32_t value );

/**
 * @brief Veda SL917 EXT SPI control function.
 * @details This function sends control bytes C1 and C2 and retries while the module returns a busy token.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] command : C1 SPI operation code.
 * @param[in] argument : C2 register address or transfer mode.
 * @return @li @c  0 - Control bytes accepted,
 *         @li @c -1 - SPI transfer error,
 *         @li @c -2 - Busy timeout,
 *         @li @c -3 - Unexpected response token.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Chip select must already be asserted.
 */
static err_t vedasl917ext_control ( vedasl917ext_t *ctx, uint8_t command, uint8_t argument );

/**
 * @brief Veda SL917 EXT SPI start token function.
 * @details This function clocks SPI reads until the module sends the start token, reports a failure, or times out.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @return @li @c  0 - Start token received,
 *         @li @c -1 - SPI transfer error,
 *         @li @c -2 - Start token timeout,
 *         @li @c -3 - Failure token received.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Chip select must already be asserted.
 */
static err_t vedasl917ext_wait_token ( vedasl917ext_t *ctx );

/**
 * @brief Veda SL917 EXT SPI frame start function.
 * @details This function sends an SPI frame operation and its little-endian transfer length, and waits for the
 * start token on reads.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] command : SPI frame read or write operation code.
 * @param[in] len : Transfer size in bytes.
 * @return @li @c  0 - Ready to transfer the frame,
 *         @li @c <0 - SPI transfer, timeout, or protocol error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Chip select must already be asserted.
 */
static err_t vedasl917ext_frame_start ( vedasl917ext_t *ctx, uint8_t command, uint16_t len );

/**
 * @brief Veda SL917 EXT SPI discard function.
 * @details This function clocks out unread response bytes in chunks without storing them in the receive buffer.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] len : Number of bytes to discard.
 * @return @li @c  0 - Success,
 *         @li @c -1 - SPI transfer error.
 * See #err_t definition for detailed explanation.
 * @note Chip select must already be asserted.
 */
static err_t vedasl917ext_discard ( vedasl917ext_t *ctx, uint16_t len );

/**
 * @brief Veda SL917 EXT WLAN frame write function.
 * @details This function waits for transmit buffer space and writes a WLAN frame descriptor followed by a separate
 * payload transfer padded to a multiple of four bytes.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] queue : WLAN management or socket payload queue.
 * @param[in] command : WLAN command identifier, or zero for a socket payload.
 * @param[in] buffer : Payload buffer, or NULL for a zero-length payload.
 * @param[in] len : Number of payload bytes before padding.
 * @return @li @c  0 - Frame written,
 *         @li @c <0 - Argument, SPI transfer, timeout, or protocol error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 */
static err_t vedasl917ext_write_frame ( vedasl917ext_t *ctx, uint8_t queue, uint16_t command,
                                        uint8_t *buffer, uint16_t len );

/**
 * @brief Veda SL917 EXT response frame read function.
 * @details This function checks for a pending frame, validates its length and descriptor offset, and stores the
 * response in the context after consuming any padding.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @return @li @c  0 - Frame read,
 *         @li @c  1 - No pending frame,
 *         @li @c <0 - SPI transfer, timeout, protocol, or receive buffer error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Reading a pending frame invalidates cached scan results.
 */
static err_t vedasl917ext_read_frame ( vedasl917ext_t *ctx );

/**
 * @brief Veda SL917 EXT WLAN response wait function.
 * @details This function polls for the specified WLAN response and consumes unrelated notifications.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] command : Expected WLAN response identifier.
 * @param[in] polls : Maximum number of response polls.
 * @return @li @c  0 - Expected response received,
 *         @li @c <0 - SPI transfer, timeout, protocol, receive buffer, or firmware error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note A card ready indication during a command wait is a protocol error.
 */
static err_t vedasl917ext_wait_response ( vedasl917ext_t *ctx, uint16_t command, uint16_t polls );

/**
 * @brief Veda SL917 EXT WLAN command function.
 * @details This function sends a WLAN command and waits for its response.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] command : WLAN command identifier.
 * @param[in] buffer : Payload buffer, or NULL for a zero-length payload.
 * @param[in] len : Number of payload bytes before padding.
 * @param[in] polls : Maximum number of response polls.
 * @return @li @c  0 - Command completed,
 *         @li @c <0 - Command or response error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note A failed command clears driver readiness except when the firmware reports no TCP listener.
 */
static err_t vedasl917ext_command ( vedasl917ext_t *ctx, uint16_t command, uint8_t *buffer,
                                    uint16_t len, uint16_t polls );

/**
 * @brief Veda SL917 EXT NCP boot function.
 * @details This function initializes SPI framing, selects active-high interrupts, loads the installed NCP image,
 * and waits for CARD READY.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @return @li @c  0 - Firmware ready,
 *         @li @c <0 - SPI transfer, timeout, protocol, receive buffer, or bootloader error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Call after releasing hardware reset with WAKE low.
 */
static err_t vedasl917ext_boot ( vedasl917ext_t *ctx );

void vedasl917ext_cfg_setup ( vedasl917ext_cfg_t *cfg )
{
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->slp     = HAL_PIN_NC;
    cfg->rst     = HAL_PIN_NC;
    cfg->wake    = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = VEDASL917EXT_SPI_DEFAULT_SPEED;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t vedasl917ext_init ( vedasl917ext_t *ctx, vedasl917ext_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;
    err_t error_flag = VEDASL917EXT_OK;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;
    ctx->ready = 0;
    ctx->boot_version = 0;
    ctx->last_status = 0;
    ctx->rx_command = 0;
    ctx->rx_status = 0;
    ctx->rx_length = 0;
    ctx->rx_queue = 0;
    ctx->scan_count = 0;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, VEDASL917EXT_DUMMY ) )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else
    {
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );

        if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->rst, cfg->rst ) )
        {
            error_flag = VEDASL917EXT_ERROR;
        }
        else if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_low( &ctx->rst ) )
        {
            error_flag = VEDASL917EXT_ERROR;
        }
        else if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->wake, cfg->wake ) )
        {
            error_flag = VEDASL917EXT_ERROR;
        }
        else if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_low( &ctx->wake ) )
        {
            error_flag = VEDASL917EXT_ERROR;
        }
        else if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->slp, cfg->slp ) )
        {
            error_flag = VEDASL917EXT_ERROR;
        }
        else if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->int_pin, cfg->int_pin ) )
        {
            error_flag = VEDASL917EXT_ERROR;
        }
    }

    return error_flag;
}

err_t vedasl917ext_default_cfg ( vedasl917ext_t *ctx )
{
    uint8_t buffer[ VEDASL917EXT_OPERMODE_SIZE ] = { 0 };
    err_t error_flag;

    vedasl917ext_reset( ctx );
    error_flag = vedasl917ext_boot( ctx );
    if ( VEDASL917EXT_OK == error_flag )
    {
        // Zero operation/coexistence fields select a WLAN-only station.
        vedasl917ext_put_u32( &buffer[ 4 ], VEDASL917EXT_FEATURE_OPEN | VEDASL917EXT_FEATURE_PSK |
                                            VEDASL917EXT_FEATURE_AGGREGATION | VEDASL917EXT_FEATURE_NEW_STATUS );
        vedasl917ext_put_u32( &buffer[ 8 ], VEDASL917EXT_TCPIP_DHCP | VEDASL917EXT_TCPIP_DNS |
                                            VEDASL917EXT_TCPIP_EXT_VALID );
        vedasl917ext_put_u32( &buffer[ 12 ], VEDASL917EXT_CUSTOM_EXT_VALID );
        vedasl917ext_put_u32( &buffer[ 16 ], VEDASL917EXT_EXT_NCP_MEMORY | VEDASL917EXT_EXT_XTAL |
                                             VEDASL917EXT_EXT_RF_SWITCH );
        vedasl917ext_put_u32( &buffer[ 24 ], VEDASL917EXT_TCPIP_HOST_CLOSE );
        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_OPERMODE, buffer,
                                           VEDASL917EXT_OPERMODE_SIZE, VEDASL917EXT_COMMAND_POLLS );
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        memset( buffer, 0, sizeof( buffer ) );
        buffer[ 1 ] = VEDASL917EXT_FEATURE_RF_INTERNAL;
        buffer[ 4 ] = VEDASL917EXT_FEATURE_AFE;
        // The NCP feature bitmap starts at byte 8, after three reserved bytes.
        vedasl917ext_put_u32( &buffer[ 8 ], VEDASL917EXT_FEATURE_ENABLES );
        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_FEATURE, buffer,
                                           VEDASL917EXT_FEATURE_SIZE, VEDASL917EXT_COMMAND_POLLS );
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        buffer[ 0 ] = VEDASL917EXT_BAND_2_4_GHZ;
        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_BAND, buffer, 1, VEDASL917EXT_COMMAND_POLLS );
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_INIT, NULL, 0, VEDASL917EXT_COMMAND_POLLS );
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        ctx->ready = 1;
    }

    return error_flag;
}

void vedasl917ext_reset ( vedasl917ext_t *ctx )
{
    ctx->ready = 0;
    ctx->boot_version = 0;
    ctx->last_status = 0;
    ctx->rx_command = 0;
    ctx->rx_status = 0;
    ctx->rx_length = 0;
    ctx->rx_queue = 0;
    ctx->scan_count = 0;

    // POC_IN also controls the ClickID CS multiplexer; do not clock SPI while reset is low.
    spi_master_deselect_device( ctx->chip_select );
    digital_out_low( &ctx->wake );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

err_t vedasl917ext_write_reg ( vedasl917ext_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = VEDASL917EXT_ERROR;

    if ( reg <= VEDASL917EXT_SPI_REG_MAX )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = vedasl917ext_control( ctx, VEDASL917EXT_SPI_REG_WRITE, reg );
        if ( VEDASL917EXT_OK == error_flag )
        {
            error_flag = spi_master_write( &ctx->spi, &data_in, 1 );
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t vedasl917ext_read_reg ( vedasl917ext_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = VEDASL917EXT_ERROR;

    if ( ( reg <= VEDASL917EXT_SPI_REG_MAX ) && ( NULL != data_out ) )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag = vedasl917ext_control( ctx, VEDASL917EXT_SPI_REG_READ, reg );
        if ( VEDASL917EXT_OK == error_flag )
        {
            error_flag = vedasl917ext_wait_token( ctx );
        }
        if ( VEDASL917EXT_OK == error_flag )
        {
            error_flag = spi_master_read( &ctx->spi, data_out, 1 );
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t vedasl917ext_write_mem ( vedasl917ext_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len )
{
    uint8_t header[ 6 ];
    err_t error_flag = VEDASL917EXT_ERROR;

    if ( ( NULL != data_in ) && ( 0 != len ) )
    {
        header[ 0 ] = ( uint8_t ) len;
        header[ 1 ] = ( uint8_t ) ( len >> 8 );
        vedasl917ext_put_u32( &header[ 2 ], address );
        spi_master_select_device( ctx->chip_select );
        error_flag = vedasl917ext_control( ctx, VEDASL917EXT_SPI_MEM_WRITE, 0 );
        if ( VEDASL917EXT_OK == error_flag )
        {
            error_flag = spi_master_write( &ctx->spi, header, sizeof( header ) );
        }
        if ( VEDASL917EXT_OK == error_flag )
        {
            error_flag = spi_master_write( &ctx->spi, data_in, len );
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t vedasl917ext_read_mem ( vedasl917ext_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len )
{
    uint8_t header[ 6 ];
    err_t error_flag = VEDASL917EXT_ERROR;

    if ( ( NULL != data_out ) && ( 0 != len ) )
    {
        header[ 0 ] = ( uint8_t ) len;
        header[ 1 ] = ( uint8_t ) ( len >> 8 );
        vedasl917ext_put_u32( &header[ 2 ], address );
        spi_master_select_device( ctx->chip_select );
        error_flag = vedasl917ext_control( ctx, VEDASL917EXT_SPI_MEM_READ, 0 );
        if ( VEDASL917EXT_OK == error_flag )
        {
            error_flag = spi_master_write( &ctx->spi, header, sizeof( header ) );
        }
        if ( VEDASL917EXT_OK == error_flag )
        {
            error_flag = vedasl917ext_wait_token( ctx );
        }
        if ( VEDASL917EXT_OK == error_flag )
        {
            error_flag = spi_master_read( &ctx->spi, data_out, len );
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

err_t vedasl917ext_get_fw_version ( vedasl917ext_t *ctx, vedasl917ext_version_t *version )
{
    err_t error_flag = VEDASL917EXT_NOT_READY;

    if ( NULL == version )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( 0 != ctx->ready )
    {
        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_FW_VERSION, NULL, 0, VEDASL917EXT_COMMAND_POLLS );
        if ( VEDASL917EXT_OK == error_flag )
        {
            if ( ctx->rx_length >= VEDASL917EXT_VERSION_SIZE )
            {
                version->chip_id = ctx->rx_buffer[ 0 ];
                version->rom_id = ctx->rx_buffer[ 1 ];
                version->major = ctx->rx_buffer[ 2 ];
                version->minor = ctx->rx_buffer[ 3 ];
                version->security = ctx->rx_buffer[ 4 ];
                version->patch = ctx->rx_buffer[ 5 ];
                version->customer_id = ctx->rx_buffer[ 6 ];
                version->build = vedasl917ext_get_u16( &ctx->rx_buffer[ 7 ] );
            }
            else
            {
                ctx->ready = 0;
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
        }
    }

    return error_flag;
}

err_t vedasl917ext_get_mac_address ( vedasl917ext_t *ctx, uint8_t *mac )
{
    err_t error_flag = VEDASL917EXT_NOT_READY;

    if ( NULL == mac )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( 0 != ctx->ready )
    {
        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_MAC_ADDRESS, NULL, 0, VEDASL917EXT_COMMAND_POLLS );
        if ( VEDASL917EXT_OK == error_flag )
        {
            if ( ctx->rx_length >= VEDASL917EXT_MAC_SIZE )
            {
                memcpy( mac, ctx->rx_buffer, VEDASL917EXT_MAC_SIZE );
            }
            else
            {
                ctx->ready = 0;
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
        }
    }

    return error_flag;
}

err_t vedasl917ext_scan ( vedasl917ext_t *ctx, uint8_t channel )
{
    uint8_t request[ VEDASL917EXT_SCAN_REQUEST_SIZE ] = { 0 };
    uint32_t count = 0;
    err_t error_flag = VEDASL917EXT_NOT_READY;

    ctx->scan_count = 0;
    if ( channel > VEDASL917EXT_SCAN_LAST_CHANNEL )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( 0 != ctx->ready )
    {
        request[ 0 ] = channel;
        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_SCAN, request,
                                           sizeof( request ), VEDASL917EXT_SCAN_POLLS );
        if ( VEDASL917EXT_OK == error_flag )
        {
            if ( ctx->rx_length < VEDASL917EXT_SCAN_HEADER_SIZE )
            {
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
            else
            {
                count = vedasl917ext_get_u32( ctx->rx_buffer );
                if ( ( count > VEDASL917EXT_SCAN_MAX_AP ) ||
                     ( count * VEDASL917EXT_SCAN_RECORD_SIZE + VEDASL917EXT_SCAN_HEADER_SIZE > ctx->rx_length ) )
                {
                    error_flag = VEDASL917EXT_PROTOCOL_ERROR;
                }
                else
                {
                    ctx->scan_count = ( uint8_t ) count;
                }
            }
            if ( VEDASL917EXT_OK != error_flag )
            {
                ctx->ready = 0;
            }
        }
    }

    return error_flag;
}

err_t vedasl917ext_get_scan_result ( vedasl917ext_t *ctx, uint8_t index, vedasl917ext_ap_t *result )
{
    uint8_t *record;
    err_t error_flag = VEDASL917EXT_ERROR;

    if ( ( NULL != result ) && ( index < ctx->scan_count ) &&
         ( VEDASL917EXT_CMD_SCAN == ctx->rx_command ) && ( 0 != ctx->ready ) )
    {
        record = &ctx->rx_buffer[ VEDASL917EXT_SCAN_HEADER_SIZE + ( uint16_t ) index * VEDASL917EXT_SCAN_RECORD_SIZE ];
        result->channel = record[ 0 ];
        result->security = record[ 1 ];
        result->rssi = -( int16_t ) record[ 2 ];
        result->network_type = record[ 3 ];
        memcpy( result->ssid, &record[ VEDASL917EXT_SCAN_SSID_OFFSET ], VEDASL917EXT_SSID_SIZE );
        result->ssid[ VEDASL917EXT_SSID_SIZE ] = 0;
        memcpy( result->bssid, &record[ VEDASL917EXT_SCAN_BSSID_OFFSET ], VEDASL917EXT_MAC_SIZE );
        error_flag = VEDASL917EXT_OK;
    }

    return error_flag;
}

err_t vedasl917ext_join ( vedasl917ext_t *ctx, char *ssid, uint8_t security, char *passphrase )
{
    uint8_t *request = ctx->rx_buffer;
    size_t ssid_len = 0;
    size_t psk_len = 0;
    err_t error_flag = VEDASL917EXT_NOT_READY;

    if ( ctx->ready )
    {
        if ( NULL != ssid )
        {
            ssid_len = strlen( ssid );
        }
        if ( NULL != passphrase )
        {
            psk_len = strlen( passphrase );
        }
        if ( ( 0 == ssid_len ) || ( ssid_len > VEDASL917EXT_SSID_SIZE ) ||
             ( ( VEDASL917EXT_WIFI_OPEN != security ) && ( VEDASL917EXT_WIFI_WPA2 != security ) ) ||
             ( ( VEDASL917EXT_WIFI_WPA2 == security ) &&
               ( ( psk_len < VEDASL917EXT_PSK_MIN_LEN ) || ( psk_len > VEDASL917EXT_PSK_MAX_LEN ) ) ) )
        {
            error_flag = VEDASL917EXT_ERROR;
        }
        else
        {
            // The firmware uses the targeted scan to select the access point for the join.
            memset( request, 0, VEDASL917EXT_SCAN_REQUEST_SIZE );
            memcpy( &request[ VEDASL917EXT_SCAN_SSID_OFFSET ], ssid, ssid_len );
            error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_SCAN, request,
                                               VEDASL917EXT_SCAN_REQUEST_SIZE, VEDASL917EXT_SCAN_POLLS );
        }

        if ( ( VEDASL917EXT_OK == error_flag ) && ( VEDASL917EXT_WIFI_WPA2 == security ) )
        {
            memset( request, 0, VEDASL917EXT_PSK_REQUEST_SIZE );
            request[ 0 ] = VEDASL917EXT_PSK_PASSPHRASE;
            memcpy( &request[ 1 ], passphrase, psk_len );
            error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_PSK, request,
                                               VEDASL917EXT_PSK_REQUEST_SIZE, VEDASL917EXT_COMMAND_POLLS );
            memset( request, 0, VEDASL917EXT_PSK_REQUEST_SIZE );
        }
        if ( VEDASL917EXT_OK == error_flag )
        {
            memset( request, 0, VEDASL917EXT_JOIN_REQUEST_SIZE );
            request[ 1 ] = security;
            if ( VEDASL917EXT_WIFI_WPA2 == security )
            {
                request[ 1 ] |= VEDASL917EXT_JOIN_CCMP;
                request[ VEDASL917EXT_JOIN_FLAGS_OFFSET ] = VEDASL917EXT_JOIN_MFP_CAPABLE;
            }
            memcpy( &request[ VEDASL917EXT_JOIN_SSID_OFFSET ], ssid, ssid_len );
            request[ VEDASL917EXT_JOIN_SSID_LEN_OFFSET ] = ( uint8_t ) ssid_len;
            error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_JOIN, request,
                                               VEDASL917EXT_JOIN_REQUEST_SIZE, VEDASL917EXT_JOIN_POLLS );
            if ( ( VEDASL917EXT_OK == error_flag ) && ( ( 0 == ctx->rx_length ) || ( 'C' != ctx->rx_buffer[ 0 ] ) ) )
            {
                ctx->ready = 0;
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
        }
    }

    return error_flag;
}

err_t vedasl917ext_dhcp ( vedasl917ext_t *ctx, uint8_t *address )
{
    uint8_t request[ VEDASL917EXT_DHCP_REQUEST_SIZE ] = { VEDASL917EXT_DHCP_UNICAST };
    err_t error_flag = VEDASL917EXT_NOT_READY;

    if ( NULL == address )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( ctx->ready )
    {
        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_IPV4, request, sizeof( request ),
                                           VEDASL917EXT_DHCP_POLLS );
        if ( VEDASL917EXT_OK == error_flag )
        {
            if ( ( ctx->rx_length < VEDASL917EXT_DHCP_REPLY_SIZE ) ||
                 ( 0 == vedasl917ext_get_u32( &ctx->rx_buffer[ VEDASL917EXT_MAC_SIZE ] ) ) )
            {
                ctx->ready = 0;
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
            else
            {
                memcpy( address, &ctx->rx_buffer[ VEDASL917EXT_MAC_SIZE ], VEDASL917EXT_IPV4_SIZE );
            }
        }
    }

    return error_flag;
}

err_t vedasl917ext_socket_open ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket, uint8_t type,
                                 uint8_t *address, uint16_t port, uint16_t local_port )
{
    uint8_t *request = ctx->rx_buffer;
    err_t error_flag = VEDASL917EXT_NOT_READY;

    if ( ( NULL == socket ) || ( NULL == address ) || ( 0 == port ) ||
         ( ( VEDASL917EXT_SOCKET_TCP != type ) && ( VEDASL917EXT_SOCKET_UDP != type ) ) )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( ctx->ready )
    {
        memset( request, 0, VEDASL917EXT_SOCKET_OPEN_SIZE );
        request[ 0 ] = VEDASL917EXT_IPV4_SIZE;
        request[ 2 ] = type;
        request[ 4 ] = ( uint8_t ) local_port;
        request[ 5 ] = ( uint8_t ) ( local_port >> 8 );
        request[ 6 ] = ( uint8_t ) port;
        request[ 7 ] = ( uint8_t ) ( port >> 8 );
        memcpy( &request[ 8 ], address, VEDASL917EXT_IPV4_SIZE );
        request[ VEDASL917EXT_SOCKET_RETRIES_OFFSET ] = VEDASL917EXT_SOCKET_TCP_RETRIES;
        request[ VEDASL917EXT_SOCKET_FLAGS_OFFSET ] = VEDASL917EXT_SOCKET_RX_WINDOW_FLAG;
        request[ VEDASL917EXT_SOCKET_WINDOW_OFFSET ] = VEDASL917EXT_SOCKET_TCP_WINDOW;
        request[ VEDASL917EXT_SOCKET_KEEP_OFFSET ] = ( uint8_t ) VEDASL917EXT_SOCKET_TCP_KEEP;
        request[ VEDASL917EXT_SOCKET_KEEP_OFFSET + 1 ] = ( uint8_t ) ( VEDASL917EXT_SOCKET_TCP_KEEP >> 8 );

        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_SOCKET_OPEN, request,
                                           VEDASL917EXT_SOCKET_OPEN_SIZE, VEDASL917EXT_SOCKET_OPEN_POLLS );
        if ( VEDASL917EXT_OK == error_flag )
        {
            if ( ( ctx->rx_length < VEDASL917EXT_SOCKET_OPEN_REPLY_MIN ) ||
                 ( VEDASL917EXT_IPV4_SIZE != vedasl917ext_get_u16( ctx->rx_buffer ) ) ||
                 ( type != vedasl917ext_get_u16( &ctx->rx_buffer[ 2 ] ) ) )
            {
                ctx->ready = 0;
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
            else
            {
                socket->id = vedasl917ext_get_u16( &ctx->rx_buffer[ VEDASL917EXT_SOCKET_ID_OFFSET ] );
                socket->port = port;
                memcpy( socket->address, address, VEDASL917EXT_IPV4_SIZE );
                socket->type = type;
                socket->open = 1;
            }
        }
    }

    return error_flag;
}

err_t vedasl917ext_socket_send ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket, uint8_t *buffer, uint16_t len )
{
    uint8_t *request = ctx->rx_buffer;
    uint16_t offset = VEDASL917EXT_SOCKET_TCP_TX_OFFSET;
    err_t error_flag = VEDASL917EXT_NOT_READY;

    if ( ( NULL == socket ) || ( NULL == buffer ) || ( 0 == len ) || ( len > VEDASL917EXT_SOCKET_TX_MAX ) )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( ctx->ready && socket->open )
    {
        if ( VEDASL917EXT_SOCKET_UDP == socket->type )
        {
            offset = VEDASL917EXT_SOCKET_UDP_TX_OFFSET;
        }
        ctx->last_status = 0;
        ctx->scan_count = 0;
        memset( request, 0, offset );
        request[ 0 ] = VEDASL917EXT_IPV4_SIZE;
        request[ VEDASL917EXT_DATA_ID_OFFSET ] = ( uint8_t ) socket->id;
        request[ VEDASL917EXT_DATA_ID_OFFSET + 1 ] = ( uint8_t ) ( socket->id >> 8 );
        vedasl917ext_put_u32( &request[ VEDASL917EXT_DATA_LENGTH_OFFSET ], len );
        request[ VEDASL917EXT_DATA_START_OFFSET ] = ( uint8_t ) offset;
        request[ VEDASL917EXT_DATA_PORT_OFFSET ] = ( uint8_t ) socket->port;
        request[ VEDASL917EXT_DATA_PORT_OFFSET + 1 ] = ( uint8_t ) ( socket->port >> 8 );
        memcpy( &request[ VEDASL917EXT_DATA_ADDRESS_OFFSET ], socket->address, VEDASL917EXT_IPV4_SIZE );
        memcpy( &request[ offset ], buffer, len );
        error_flag = vedasl917ext_write_frame( ctx, VEDASL917EXT_QUEUE_SOCKET_DATA, VEDASL917EXT_SOCKET_DATA_FRAME,
                                               request, offset + len );
        if ( VEDASL917EXT_OK != error_flag )
        {
            ctx->ready = 0;
        }
    }

    return error_flag;
}

err_t vedasl917ext_socket_recv ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket, uint8_t *buffer,
                                 uint16_t capacity, uint16_t *received, uint16_t polls )
{
    uint8_t *response = ctx->rx_buffer;
    uint32_t length;
    uint16_t offset;
    uint16_t poll;
    err_t error_flag = VEDASL917EXT_NOT_READY;

    if ( NULL != received )
    {
        *received = 0;
    }
    if ( ( NULL == socket ) || ( NULL == buffer ) || ( NULL == received ) || ( 0 == capacity ) )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( ctx->ready && socket->open )
    {
        ctx->last_status = 0;
        error_flag = VEDASL917EXT_OK;
        for ( poll = 0; ( poll < polls ) && ( VEDASL917EXT_OK == error_flag ) && ( 0 == *received ); poll++ )
        {
            error_flag = vedasl917ext_read_frame( ctx );
            if ( VEDASL917EXT_NO_RESPONSE == error_flag )
            {
                error_flag = VEDASL917EXT_OK;
            }
            else if ( VEDASL917EXT_OK != error_flag )
            {
                ctx->ready = 0;
            }
            else if ( VEDASL917EXT_QUEUE_WLAN == ctx->rx_queue )
            {
                if ( VEDASL917EXT_CMD_DISCONNECT == ctx->rx_command )
                {
                    ctx->last_status = ctx->rx_status;
                    ctx->ready = 0;
                    error_flag = VEDASL917EXT_DISCONNECTED;
                }
                else if ( VEDASL917EXT_CMD_CARD_READY == ctx->rx_command )
                {
                    ctx->ready = 0;
                    error_flag = VEDASL917EXT_PROTOCOL_ERROR;
                }
                else if ( ( VEDASL917EXT_EVT_SOCKET_CLOSED == ctx->rx_command ) && ( ctx->rx_length >= 2 ) &&
                          ( socket->id == vedasl917ext_get_u16( response ) ) )
                {
                    ctx->last_status = ctx->rx_status;
                    error_flag = VEDASL917EXT_SOCKET_CLOSED;
                }
            }
            else if ( ( VEDASL917EXT_QUEUE_SOCKET_DATA == ctx->rx_queue ) &&
                      ( VEDASL917EXT_SOCKET_DATA_FRAME == ctx->rx_command ) )
            {
                if ( ctx->rx_length < VEDASL917EXT_SOCKET_RX_HDR_SIZE )
                {
                    error_flag = VEDASL917EXT_PROTOCOL_ERROR;
                }
                else if ( ( socket->id == vedasl917ext_get_u16( &response[ VEDASL917EXT_DATA_ID_OFFSET ] ) ) &&
                          ( VEDASL917EXT_IPV4_SIZE == vedasl917ext_get_u16( response ) ) &&
                          ( ( VEDASL917EXT_SOCKET_UDP != socket->type ) ||
                            ( ( socket->port == vedasl917ext_get_u16( &response[ VEDASL917EXT_DATA_PORT_OFFSET ] ) ) &&
                              ( 0 == memcmp( &response[ VEDASL917EXT_DATA_ADDRESS_OFFSET ],
                                             socket->address, VEDASL917EXT_IPV4_SIZE ) ) ) ) )
                {
                    length = vedasl917ext_get_u32( &response[ VEDASL917EXT_DATA_LENGTH_OFFSET ] );
                    offset = vedasl917ext_get_u16( &response[ VEDASL917EXT_DATA_START_OFFSET ] );
                    if ( ( offset < VEDASL917EXT_SOCKET_RX_HDR_SIZE ) || ( offset > ctx->rx_length ) ||
                         ( length > ( uint32_t ) ( ctx->rx_length - offset ) ) )
                    {
                        error_flag = VEDASL917EXT_PROTOCOL_ERROR;
                    }
                    else if ( length > capacity )
                    {
                        error_flag = VEDASL917EXT_BUFFER_ERROR;
                    }
                    else if ( 0 != length )
                    {
                        *received = ( uint16_t ) length;
                        memcpy( buffer, &response[ offset ], *received );
                    }
                }
            }
            if ( ( VEDASL917EXT_OK == error_flag ) && ( 0 == *received ) )
            {
                Delay_1ms( );
            }
        }
        if ( ( VEDASL917EXT_OK == error_flag ) && ( 0 == *received ) )
        {
            error_flag = VEDASL917EXT_TIMEOUT;
        }
    }

    return error_flag;
}

err_t vedasl917ext_socket_close ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket )
{
    uint8_t request[ VEDASL917EXT_SOCKET_CLOSE_SIZE ] = { 0 };
    err_t error_flag = VEDASL917EXT_NOT_READY;

    if ( NULL == socket )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    else if ( ctx->ready && socket->open )
    {
        request[ 0 ] = ( uint8_t ) socket->id;
        request[ 1 ] = ( uint8_t ) ( socket->id >> 8 );
        error_flag = vedasl917ext_command( ctx, VEDASL917EXT_CMD_SOCKET_CLOSE, request, sizeof( request ),
                                           VEDASL917EXT_COMMAND_POLLS );
        if ( VEDASL917EXT_OK == error_flag )
        {
            if ( ( ctx->rx_length < 2 ) || ( socket->id != vedasl917ext_get_u16( ctx->rx_buffer ) ) )
            {
                ctx->ready = 0;
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
            else
            {
                socket->open = 0;
            }
        }
    }

    return error_flag;
}

uint8_t vedasl917ext_get_int_pin ( vedasl917ext_t *ctx )
{
    return !!digital_in_read( &ctx->int_pin );
}

uint8_t vedasl917ext_get_slp_pin ( vedasl917ext_t *ctx )
{
    return !!digital_in_read( &ctx->slp );
}

static uint16_t vedasl917ext_get_u16 ( uint8_t *buffer )
{
    return ( uint16_t ) buffer[ 0 ] | ( ( uint16_t ) buffer[ 1 ] << 8 );
}

static uint32_t vedasl917ext_get_u32 ( uint8_t *buffer )
{
    return ( uint32_t ) buffer[ 0 ] | ( ( uint32_t ) buffer[ 1 ] << 8 ) |
           ( ( uint32_t ) buffer[ 2 ] << 16 ) | ( ( uint32_t ) buffer[ 3 ] << 24 );
}

static void vedasl917ext_put_u32 ( uint8_t *buffer, uint32_t value )
{
    buffer[ 0 ] = ( uint8_t ) value;
    buffer[ 1 ] = ( uint8_t ) ( value >> 8 );
    buffer[ 2 ] = ( uint8_t ) ( value >> 16 );
    buffer[ 3 ] = ( uint8_t ) ( value >> 24 );
}

static err_t vedasl917ext_control ( vedasl917ext_t *ctx, uint8_t command, uint8_t argument )
{
    uint8_t tx_buffer[ 2 ];
    uint8_t rx_buffer[ 2 ];
    uint8_t accepted = 0;
    uint16_t poll;
    err_t error_flag = VEDASL917EXT_OK;

    tx_buffer[ 0 ] = command;
    tx_buffer[ 1 ] = argument;
    for ( poll = 0; ( poll < VEDASL917EXT_SPI_BUSY_POLLS ) &&
                    ( VEDASL917EXT_OK == error_flag ) && ( 0 == accepted ); poll++ )
    {
        error_flag = spi_master_transfer( &ctx->spi, tx_buffer, rx_buffer, sizeof( tx_buffer ) );
        if ( VEDASL917EXT_OK == error_flag )
        {
            if ( ( VEDASL917EXT_SPI_SUCCESS == rx_buffer[ 1 ] ) || ( 0 == rx_buffer[ 1 ] ) )
            {
                accepted = 1;
            }
            else if ( VEDASL917EXT_SPI_BUSY == rx_buffer[ 1 ] )
            {
                Delay_1ms( );
            }
            else
            {
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
        }
    }
    if ( ( VEDASL917EXT_OK == error_flag ) && ( 0 == accepted ) )
    {
        error_flag = VEDASL917EXT_TIMEOUT;
    }

    return error_flag;
}

static err_t vedasl917ext_wait_token ( vedasl917ext_t *ctx )
{
    uint8_t token = 0;
    uint16_t poll;
    err_t error_flag = VEDASL917EXT_OK;

    for ( poll = 0; ( poll < VEDASL917EXT_TOKEN_POLLS ) &&
                    ( VEDASL917EXT_OK == error_flag ) && ( VEDASL917EXT_SPI_START != token ); poll++ )
    {
        error_flag = spi_master_read( &ctx->spi, &token, 1 );
        if ( ( VEDASL917EXT_OK == error_flag ) && ( VEDASL917EXT_SPI_START != token ) )
        {
            if ( VEDASL917EXT_SPI_FAIL == token )
            {
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
            else
            {
                Delay_1ms( );
            }
        }
    }
    if ( ( VEDASL917EXT_OK == error_flag ) && ( VEDASL917EXT_SPI_START != token ) )
    {
        error_flag = VEDASL917EXT_TIMEOUT;
    }

    return error_flag;
}

static err_t vedasl917ext_frame_start ( vedasl917ext_t *ctx, uint8_t command, uint16_t len )
{
    uint8_t length_bytes[ 2 ];
    err_t error_flag = vedasl917ext_control( ctx, command, 0 );

    if ( VEDASL917EXT_OK == error_flag )
    {
        length_bytes[ 0 ] = ( uint8_t ) len;
        length_bytes[ 1 ] = ( uint8_t ) ( len >> 8 );
        error_flag = spi_master_write( &ctx->spi, length_bytes, sizeof( length_bytes ) );
    }
    if ( ( VEDASL917EXT_OK == error_flag ) && ( VEDASL917EXT_SPI_FRAME_WRITE != command ) )
    {
        error_flag = vedasl917ext_wait_token( ctx );
    }

    return error_flag;
}

static err_t vedasl917ext_discard ( vedasl917ext_t *ctx, uint16_t len )
{
    uint8_t buffer[ VEDASL917EXT_DISCARD_SIZE ];
    uint16_t chunk;
    err_t error_flag = VEDASL917EXT_OK;

    while ( ( 0 != len ) && ( VEDASL917EXT_OK == error_flag ) )
    {
        chunk = sizeof( buffer );
        if ( len < chunk )
        {
            chunk = len;
        }
        error_flag = spi_master_read( &ctx->spi, buffer, chunk );
        len -= chunk;
    }

    return error_flag;
}

static err_t vedasl917ext_write_frame ( vedasl917ext_t *ctx, uint8_t queue, uint16_t command,
                                        uint8_t *buffer, uint16_t len )
{
    uint8_t descriptor[ VEDASL917EXT_FRAME_DESC_SIZE ] = { 0 };
    uint8_t padding[ 3 ] = { 0 };
    uint8_t status = VEDASL917EXT_INT_BUFFER_FULL;
    uint16_t poll;
    uint16_t aligned_len = ( len + 3u ) & VEDASL917EXT_ALIGNMENT_MASK;
    err_t error_flag = VEDASL917EXT_OK;

    if ( ( len > VEDASL917EXT_FRAME_MAX_PAYLOAD ) || ( ( 0 != len ) && ( NULL == buffer ) ) )
    {
        error_flag = VEDASL917EXT_ERROR;
    }
    for ( poll = 0; ( poll < VEDASL917EXT_COMMAND_POLLS ) &&
                    ( VEDASL917EXT_OK == error_flag ) && ( status & VEDASL917EXT_INT_BUFFER_FULL ); poll++ )
    {
        error_flag = vedasl917ext_read_reg( ctx, VEDASL917EXT_REG_INTERRUPT, &status );
        if ( ( VEDASL917EXT_OK == error_flag ) && ( status & VEDASL917EXT_INT_BUFFER_FULL ) )
        {
            Delay_1ms( );
        }
    }
    if ( ( VEDASL917EXT_OK == error_flag ) && ( status & VEDASL917EXT_INT_BUFFER_FULL ) )
    {
        error_flag = VEDASL917EXT_TIMEOUT;
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        descriptor[ 0 ] = ( uint8_t ) len;
        descriptor[ 1 ] = ( uint8_t ) ( len >> 8 ) | ( uint8_t ) ( queue << VEDASL917EXT_QUEUE_SHIFT );
        descriptor[ 2 ] = ( uint8_t ) command;
        descriptor[ 3 ] = ( uint8_t ) ( command >> 8 );

        spi_master_select_device( ctx->chip_select );
        error_flag = vedasl917ext_frame_start( ctx, VEDASL917EXT_SPI_FRAME_WRITE, sizeof( descriptor ) );
        if ( VEDASL917EXT_OK == error_flag )
        {
            error_flag = spi_master_write( &ctx->spi, descriptor, sizeof( descriptor ) );
        }
        if ( ( VEDASL917EXT_OK == error_flag ) && ( 0 != len ) )
        {
            error_flag = vedasl917ext_frame_start( ctx, VEDASL917EXT_SPI_FRAME_WRITE, aligned_len );
            if ( VEDASL917EXT_OK == error_flag )
            {
                error_flag = spi_master_write( &ctx->spi, buffer, len );
            }
            if ( ( VEDASL917EXT_OK == error_flag ) && ( aligned_len != len ) )
            {
                error_flag = spi_master_write( &ctx->spi, padding, aligned_len - len );
            }
        }
        spi_master_deselect_device( ctx->chip_select );
    }

    return error_flag;
}

static err_t vedasl917ext_read_frame ( vedasl917ext_t *ctx )
{
    uint8_t prefix[ VEDASL917EXT_SPI_PREFIX_SIZE ];
    uint8_t descriptor[ VEDASL917EXT_FRAME_DESC_SIZE ];
    uint8_t status;
    uint16_t total = 0;
    uint16_t offset = 0;
    uint16_t remaining = 0;
    uint16_t payload_len = 0;
    uint16_t copy_len = 0;
    err_t frame_error = VEDASL917EXT_OK;
    err_t error_flag = vedasl917ext_read_reg( ctx, VEDASL917EXT_REG_INTERRUPT, &status );

    if ( VEDASL917EXT_OK == error_flag )
    {
        if ( 0 == ( status & VEDASL917EXT_INT_RX_PENDING ) )
        {
            error_flag = VEDASL917EXT_NO_RESPONSE;
        }
        else
        {
            ctx->rx_length = 0;
            ctx->rx_command = 0;
            ctx->rx_status = 0;
            ctx->rx_queue = 0;
            ctx->scan_count = 0;

            spi_master_select_device( ctx->chip_select );
            error_flag = vedasl917ext_frame_start( ctx, VEDASL917EXT_SPI_FRAME_LENGTH, sizeof( prefix ) );
            if ( VEDASL917EXT_OK == error_flag )
            {
                error_flag = spi_master_read( &ctx->spi, prefix, sizeof( prefix ) );
            }
            if ( VEDASL917EXT_OK == error_flag )
            {
                total = vedasl917ext_get_u16( prefix );
                offset = vedasl917ext_get_u16( &prefix[ 2 ] );
                if ( ( offset < VEDASL917EXT_SPI_PREFIX_SIZE ) || ( total < offset ) ||
                     ( total - offset < VEDASL917EXT_FRAME_DESC_SIZE ) )
                {
                    error_flag = VEDASL917EXT_PROTOCOL_ERROR;
                }
                else
                {
                    remaining = ( total - VEDASL917EXT_SPI_PREFIX_SIZE + 3u ) & VEDASL917EXT_ALIGNMENT_MASK;
                    error_flag = vedasl917ext_frame_start( ctx, VEDASL917EXT_SPI_FRAME_READ, remaining );
                }
            }
            if ( VEDASL917EXT_OK == error_flag )
            {
                error_flag = vedasl917ext_discard( ctx, offset - VEDASL917EXT_SPI_PREFIX_SIZE );
                remaining -= offset - VEDASL917EXT_SPI_PREFIX_SIZE;
            }
            if ( VEDASL917EXT_OK == error_flag )
            {
                error_flag = spi_master_read( &ctx->spi, descriptor, sizeof( descriptor ) );
                remaining -= sizeof( descriptor );
            }
            if ( VEDASL917EXT_OK == error_flag )
            {
                ctx->rx_queue = descriptor[ 1 ] >> VEDASL917EXT_QUEUE_SHIFT;
                ctx->rx_command = vedasl917ext_get_u16( &descriptor[ 2 ] );
                ctx->rx_status = vedasl917ext_get_u16( &descriptor[ VEDASL917EXT_STATUS_OFFSET ] );
                payload_len = vedasl917ext_get_u16( descriptor ) & VEDASL917EXT_LENGTH_MASK;
                if ( payload_len > total - offset - VEDASL917EXT_FRAME_DESC_SIZE )
                {
                    frame_error = VEDASL917EXT_PROTOCOL_ERROR;
                }
                else if ( payload_len > sizeof( ctx->rx_buffer ) )
                {
                    frame_error = VEDASL917EXT_BUFFER_ERROR;
                }
                else
                {
                    copy_len = payload_len;
                }
                if ( 0 != copy_len )
                {
                    error_flag = spi_master_read( &ctx->spi, ctx->rx_buffer, copy_len );
                    remaining -= copy_len;
                }
            }
            if ( VEDASL917EXT_OK == error_flag )
            {
                error_flag = vedasl917ext_discard( ctx, remaining );
            }
            spi_master_deselect_device( ctx->chip_select );
            if ( VEDASL917EXT_OK == error_flag )
            {
                error_flag = frame_error;
                if ( VEDASL917EXT_OK == error_flag )
                {
                    ctx->rx_length = copy_len;
                }
            }
        }
    }

    return error_flag;
}

static err_t vedasl917ext_wait_response ( vedasl917ext_t *ctx, uint16_t command, uint16_t polls )
{
    uint16_t poll;
    uint8_t received = 0;
    err_t error_flag = VEDASL917EXT_OK;

    for ( poll = 0; ( poll < polls ) && ( VEDASL917EXT_OK == error_flag ) && ( 0 == received ); poll++ )
    {
        error_flag = vedasl917ext_read_frame( ctx );
        if ( VEDASL917EXT_NO_RESPONSE == error_flag )
        {
            error_flag = VEDASL917EXT_OK;
        }
        else if ( VEDASL917EXT_OK == error_flag )
        {
            if ( ( VEDASL917EXT_QUEUE_WLAN == ctx->rx_queue ) && ( command == ctx->rx_command ) )
            {
                received = 1;
                ctx->last_status = ctx->rx_status;
                // CARD READY carries boot information, not an ordinary command completion status.
                if ( ( VEDASL917EXT_CMD_CARD_READY != command ) && ( 0 != ctx->rx_status ) )
                {
                    error_flag = VEDASL917EXT_FIRMWARE_ERROR;
                }
            }
            else if ( ( VEDASL917EXT_QUEUE_WLAN == ctx->rx_queue ) &&
                      ( VEDASL917EXT_CMD_DISCONNECT == ctx->rx_command ) )
            {
                ctx->last_status = ctx->rx_status;
                error_flag = VEDASL917EXT_DISCONNECTED;
            }
            else if ( VEDASL917EXT_CMD_CARD_READY == ctx->rx_command )
            {
                error_flag = VEDASL917EXT_PROTOCOL_ERROR;
            }
        }
        if ( ( VEDASL917EXT_OK == error_flag ) && ( 0 == received ) )
        {
            Delay_1ms( );
        }
    }
    if ( ( VEDASL917EXT_OK == error_flag ) && ( 0 == received ) )
    {
        error_flag = VEDASL917EXT_TIMEOUT;
    }

    return error_flag;
}

static err_t vedasl917ext_command ( vedasl917ext_t *ctx, uint16_t command, uint8_t *buffer,
                                    uint16_t len, uint16_t polls )
{
    err_t error_flag;

    ctx->scan_count = 0;
    ctx->last_status = 0;
    error_flag = vedasl917ext_write_frame( ctx, VEDASL917EXT_QUEUE_WLAN, command, buffer, len );
    if ( VEDASL917EXT_OK == error_flag )
    {
        error_flag = vedasl917ext_wait_response( ctx, command, polls );
    }
    if ( ( VEDASL917EXT_FIRMWARE_ERROR == error_flag ) && ( VEDASL917EXT_CMD_SOCKET_OPEN == command ) &&
         ( ( VEDASL917EXT_STATUS_NO_TCP_SERVER == ctx->last_status ) ||
           ( VEDASL917EXT_STATUS_NO_TCP_LEGACY == ctx->last_status ) ) )
    {
        // The firmware completed the open request without allocating a socket.
        error_flag = VEDASL917EXT_NO_TCP_SERVER;
    }
    else if ( VEDASL917EXT_OK != error_flag )
    {
        // A timed-out command may still be running. Require an explicit reset before any later command.
        ctx->ready = 0;
    }

    return error_flag;
}

static err_t vedasl917ext_boot ( vedasl917ext_t *ctx )
{
    uint8_t init_tx[ 4 ] = { 0x12, 0x4A, 0x5C, 0x00 };
    uint8_t init_rx[ 4 ] = { 0 };
    uint8_t buffer[ 2 ] = { 0 };
    uint8_t complete = 0;
    uint16_t poll;
    err_t error_flag = VEDASL917EXT_OK;

    spi_master_select_device( ctx->chip_select );
    for ( poll = 0; ( poll < VEDASL917EXT_SPI_INIT_POLLS ) &&
                    ( VEDASL917EXT_OK == error_flag ) && ( VEDASL917EXT_SPI_SUCCESS != init_rx[ 3 ] ); poll++ )
    {
        error_flag = spi_master_transfer( &ctx->spi, init_tx, init_rx, sizeof( init_tx ) );
        if ( ( VEDASL917EXT_OK == error_flag ) && ( VEDASL917EXT_SPI_SUCCESS != init_rx[ 3 ] ) )
        {
            Delay_1ms( );
        }
    }
    spi_master_deselect_device( ctx->chip_select );
    if ( ( VEDASL917EXT_OK == error_flag ) && ( VEDASL917EXT_SPI_SUCCESS != init_rx[ 3 ] ) )
    {
        error_flag = VEDASL917EXT_TIMEOUT;
    }

    for ( poll = 0; ( poll < VEDASL917EXT_BOOT_POLLS ) &&
                    ( VEDASL917EXT_OK == error_flag ) && ( 0 == complete ); poll++ )
    {
        error_flag = vedasl917ext_read_mem( ctx, VEDASL917EXT_MEM_HOST_OUT, buffer, sizeof( buffer ) );
        if ( VEDASL917EXT_OK == error_flag )
        {
            ctx->last_status = vedasl917ext_get_u16( buffer );
            if ( VEDASL917EXT_BOOT_VALID == buffer[ 1 ] )
            {
                if ( ( VEDASL917EXT_BOOT_NOT_SAVED == buffer[ 0 ] ) ||
                     ( VEDASL917EXT_BOOT_OPTIONS_FAIL == buffer[ 0 ] ) ||
                     ( VEDASL917EXT_BOOT_INVALID_OPTION == buffer[ 0 ] ) )
                {
                    error_flag = VEDASL917EXT_FIRMWARE_ERROR;
                }
                else
                {
                    ctx->boot_version = buffer[ 0 ];
                    complete = 1;
                }
            }
            else
            {
                Delay_1ms( );
            }
        }
    }
    if ( ( VEDASL917EXT_OK == error_flag ) && ( 0 == complete ) )
    {
        error_flag = VEDASL917EXT_TIMEOUT;
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        error_flag = vedasl917ext_read_mem( ctx, VEDASL917EXT_MEM_INT_MASK, buffer, sizeof( buffer ) );
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        buffer[ 1 ] &= VEDASL917EXT_INT_POLARITY_MASK;
        error_flag = vedasl917ext_write_mem( ctx, VEDASL917EXT_MEM_INT_MASK, buffer, sizeof( buffer ) );
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        buffer[ 0 ] = 0;
        buffer[ 1 ] = 0;
        error_flag = vedasl917ext_write_mem( ctx, VEDASL917EXT_MEM_HOST_OUT, buffer, sizeof( buffer ) );
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        buffer[ 0 ] = VEDASL917EXT_BOOT_LOAD;
        buffer[ 1 ] = VEDASL917EXT_BOOT_VALID;
        error_flag = vedasl917ext_write_mem( ctx, VEDASL917EXT_MEM_HOST_IN, buffer, sizeof( buffer ) );
    }

    complete = 0;
    for ( poll = 0; ( poll < VEDASL917EXT_BOOT_POLLS ) &&
                    ( VEDASL917EXT_OK == error_flag ) && ( 0 == complete ); poll++ )
    {
        error_flag = vedasl917ext_read_mem( ctx, VEDASL917EXT_MEM_HOST_OUT, buffer, sizeof( buffer ) );
        if ( VEDASL917EXT_OK == error_flag )
        {
            ctx->last_status = vedasl917ext_get_u16( buffer );
            if ( VEDASL917EXT_BOOT_STATUS_VALID == ( ctx->last_status & VEDASL917EXT_BOOT_STATUS_MASK ) )
            {
                if ( VEDASL917EXT_BOOT_CHECKSUM_OK == buffer[ 0 ] )
                {
                    complete = 1;
                }
                else if ( ( VEDASL917EXT_BOOT_NO_FIRMWARE == buffer[ 0 ] ) ||
                          ( VEDASL917EXT_BOOT_CHECKSUM_FAIL == buffer[ 0 ] ) ||
                          ( VEDASL917EXT_BOOT_INVALID_OPTION == buffer[ 0 ] ) ||
                          ( VEDASL917EXT_BOOT_NOT_SAVED == buffer[ 0 ] ) ||
                          ( VEDASL917EXT_BOOT_OPTIONS_FAIL == buffer[ 0 ] ) )
                {
                    error_flag = VEDASL917EXT_FIRMWARE_ERROR;
                }
            }
            if ( ( VEDASL917EXT_OK == error_flag ) && ( 0 == complete ) )
            {
                Delay_1ms( );
            }
        }
    }
    if ( ( VEDASL917EXT_OK == error_flag ) && ( 0 == complete ) )
    {
        error_flag = VEDASL917EXT_TIMEOUT;
    }
    if ( VEDASL917EXT_OK == error_flag )
    {
        error_flag = vedasl917ext_wait_response( ctx, VEDASL917EXT_CMD_CARD_READY, VEDASL917EXT_COMMAND_POLLS );
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
