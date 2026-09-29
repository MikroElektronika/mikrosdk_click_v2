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
 * @file broadrreach.c
 * @brief BroadR-Reach Click Driver.
 */

#include "broadrreach.h"

/**
 * @brief BroadR-Reach Click driver constants.
 * @details BROADRREACH_DUMMY is sent by the SPI peripheral when reading. BROADRREACH_MR_DEFAULT is the
 * post-reset mode value. BROADRREACH_ADDRESS_SPACE_SIZE is the exclusive end of the W3150A+ register and
 * packet-memory map. The remaining macros define bounded polling, stable-register reads, and retry settings.
 */
#define BROADRREACH_DUMMY                0x00
#define BROADRREACH_MR_DEFAULT           0x00
#define BROADRREACH_ADDRESS_SPACE_SIZE   0x8000UL
#define BROADRREACH_WAIT_MS              3000
#define BROADRREACH_SIZE_READS           8
#define BROADRREACH_RETRY_TIME           2000
#define BROADRREACH_RETRY_COUNT          3

/**
 * @brief BroadR-Reach word read function.
 * @details This function reads a big-endian 16-bit register without assuming the host byte order.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] reg : Address of the most significant byte.
 * @param[out] value : Decoded register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t broadrreach_read_word ( broadrreach_t *ctx, uint16_t reg, uint16_t *value );

/**
 * @brief BroadR-Reach word write function.
 * @details This function writes a 16-bit register with its most significant byte first.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] reg : Address of the most significant byte.
 * @param[in] value : Register value to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t broadrreach_write_word ( broadrreach_t *ctx, uint16_t reg, uint16_t value );

/**
 * @brief BroadR-Reach stable size read function.
 * @details This function requires two matching reads of a hardware-updated TX free or RX received byte count.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] reg : Address of the size register.
 * @param[out] size : Stable byte count, no greater than the configured socket buffer size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t broadrreach_read_size ( broadrreach_t *ctx, uint16_t reg, uint16_t *size );

/**
 * @brief BroadR-Reach socket command function.
 * @details This function issues a socket command and waits until the controller clears Sn_CR.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] socket : Validated socket number, from 0 to 3.
 * @param[in] command : Sn_CR command code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t broadrreach_command ( broadrreach_t *ctx, uint8_t socket, uint8_t command );

/**
 * @brief BroadR-Reach circular buffer read function.
 * @details This function splits a read at the end of the socket's 2 KB buffer and resumes at its base.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] base : Socket RX buffer base address.
 * @param[in] pointer : Unmasked hardware read pointer.
 * @param[out] data_out : Destination buffer.
 * @param[in] len : Number of bytes to read, at most BROADRREACH_BUFFER_SIZE.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t broadrreach_read_buffer ( broadrreach_t *ctx, uint16_t base, uint16_t pointer,
                                       uint8_t *data_out, uint16_t len );

/**
 * @brief BroadR-Reach circular buffer write function.
 * @details This function splits a write at the end of the socket's 2 KB buffer and resumes at its base.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] base : Socket TX buffer base address.
 * @param[in] pointer : Unmasked hardware write pointer.
 * @param[in] data_in : Source buffer.
 * @param[in] len : Number of bytes to write, at most BROADRREACH_BUFFER_SIZE.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t broadrreach_write_buffer ( broadrreach_t *ctx, uint16_t base, uint16_t pointer,
                                        uint8_t *data_in, uint16_t len );

void broadrreach_cfg_setup ( broadrreach_cfg_t *cfg )
{
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->rst     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t broadrreach_init ( broadrreach_t *ctx, broadrreach_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, BROADRREACH_DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_high( &ctx->rst );

    // The driver polls socket registers; initialize INT for applications that use the hardware interrupt.
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t broadrreach_default_cfg ( broadrreach_t *ctx )
{
    uint8_t config[ 5 ];
    uint8_t readback[ 5 ];
    uint8_t mode;
    err_t error_flag;

    broadrreach_hw_reset( ctx );
    error_flag = broadrreach_read_reg( ctx, BROADRREACH_REG_MR, &mode );
    if ( ( BROADRREACH_OK == error_flag ) && ( BROADRREACH_MR_DEFAULT != mode ) )
    {
        error_flag = BROADRREACH_ERROR;
    }

    // RTR/RCR set retries; RMSR/TMSR assign 2 KB to every socket's RX/TX ring.
    config[ 0 ] = ( uint8_t ) ( BROADRREACH_RETRY_TIME >> 8 );
    config[ 1 ] = ( uint8_t ) BROADRREACH_RETRY_TIME;
    config[ 2 ] = BROADRREACH_RETRY_COUNT;
    config[ 3 ] = BROADRREACH_MEM_2KB;
    config[ 4 ] = BROADRREACH_MEM_2KB;
    if ( BROADRREACH_OK == error_flag )
    {
        error_flag = broadrreach_write_regs( ctx, BROADRREACH_REG_RTR, config, sizeof( config ) );
    }
    if ( BROADRREACH_OK == error_flag )
    {
        error_flag = broadrreach_read_regs( ctx, BROADRREACH_REG_RTR, readback, sizeof( readback ) );
    }
    if ( ( BROADRREACH_OK == error_flag ) && ( 0 != memcmp( config, readback, sizeof( config ) ) ) )
    {
        error_flag = BROADRREACH_ERROR;
    }

    return error_flag;
}

err_t broadrreach_write_reg ( broadrreach_t *ctx, uint16_t reg, uint8_t data_in )
{
    return broadrreach_write_regs( ctx, reg, &data_in, 1 );
}

err_t broadrreach_write_regs ( broadrreach_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len )
{
    uint8_t tx_buf[ 4 ];
    uint16_t index;
    err_t error_flag = BROADRREACH_OK;

    if ( ( !data_in ) || ( ( ( uint32_t ) reg + len ) > BROADRREACH_ADDRESS_SPACE_SIZE ) )
    {
        error_flag = BROADRREACH_ERROR;
    }
    // W3150A+ has no SPI burst command: each data byte needs its own complete 32-bit frame.
    for ( index = 0; ( index < len ) && ( BROADRREACH_OK == error_flag ); index++ )
    {
        tx_buf[ 0 ] = BROADRREACH_SPI_WRITE;
        tx_buf[ 1 ] = ( uint8_t ) ( reg >> 8 );
        tx_buf[ 2 ] = ( uint8_t ) reg;
        tx_buf[ 3 ] = data_in[ index ];
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write( &ctx->spi, tx_buf, sizeof( tx_buf ) );
        spi_master_deselect_device( ctx->chip_select );
        reg++;
    }
    return error_flag;
}

err_t broadrreach_read_reg ( broadrreach_t *ctx, uint16_t reg, uint8_t *data_out )
{
    return broadrreach_read_regs( ctx, reg, data_out, 1 );
}

err_t broadrreach_read_regs ( broadrreach_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len )
{
    uint8_t tx_buf[ 3 ];
    uint16_t index;
    err_t error_flag = BROADRREACH_OK;

    if ( ( !data_out ) || ( ( ( uint32_t ) reg + len ) > BROADRREACH_ADDRESS_SPACE_SIZE ) )
    {
        error_flag = BROADRREACH_ERROR;
    }
    // Keep chip select asserted for the three-byte command and one-byte read phase.
    for ( index = 0; ( index < len ) && ( BROADRREACH_OK == error_flag ); index++ )
    {
        tx_buf[ 0 ] = BROADRREACH_SPI_READ;
        tx_buf[ 1 ] = ( uint8_t ) ( reg >> 8 );
        tx_buf[ 2 ] = ( uint8_t ) reg;
        spi_master_select_device( ctx->chip_select );
        error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, sizeof( tx_buf ), &data_out[ index ], 1 );
        spi_master_deselect_device( ctx->chip_select );
        reg++;
    }
    return error_flag;
}

void broadrreach_hw_reset ( broadrreach_t *ctx )
{
    // Reset is active low; the onboard PIC needs the following four seconds to configure the PHY.
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );

    // The PIC detects the PHY reset by polling, then reapplies the hardware-selected mode.
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

err_t broadrreach_set_network ( broadrreach_t *ctx, broadrreach_network_t *network )
{
    uint8_t config[ 18 ];
    uint8_t readback[ 18 ];
    err_t error_flag = BROADRREACH_ERROR;

    if ( network )
    {
        // Pack GAR, SUBR, SHAR, and SIPR explicitly; C structure layout is not the register map.
        memcpy( &config[ 0 ], network->gateway, 4 );
        memcpy( &config[ 4 ], network->subnet, 4 );
        memcpy( &config[ 8 ], network->mac, 6 );
        memcpy( &config[ 14 ], network->ip, 4 );
        error_flag = broadrreach_write_regs( ctx, BROADRREACH_REG_GAR, config, sizeof( config ) );
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_read_regs( ctx, BROADRREACH_REG_GAR, readback, sizeof( readback ) );
        }
        if ( ( BROADRREACH_OK == error_flag ) && ( 0 != memcmp( config, readback, sizeof( config ) ) ) )
        {
            error_flag = BROADRREACH_ERROR;
        }
    }
    return error_flag;
}

err_t broadrreach_open_udp ( broadrreach_t *ctx, uint8_t socket, uint16_t port )
{
    uint16_t base = BROADRREACH_SOCKET_BASE( socket );
    uint8_t status;
    err_t error_flag = BROADRREACH_ERROR;

    if ( ( socket < BROADRREACH_SOCKET_COUNT ) && port )
    {
        // Reopening starts with a clean socket and discards stale TX/RX pointers or flags.
        error_flag = broadrreach_close_socket( ctx, socket );
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_write_reg( ctx, base + BROADRREACH_SN_MR, BROADRREACH_MODE_UDP );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_write_word( ctx, base + BROADRREACH_SN_PORT, port );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_command( ctx, socket, BROADRREACH_CMD_OPEN );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_get_status( ctx, socket, &status );
        }
        if ( ( BROADRREACH_OK == error_flag ) && ( BROADRREACH_STATUS_UDP != status ) )
        {
            error_flag = BROADRREACH_ERROR;
        }
    }
    return error_flag;
}

err_t broadrreach_close_socket ( broadrreach_t *ctx, uint8_t socket )
{
    uint8_t status;
    err_t error_flag = BROADRREACH_ERROR;

    if ( socket < BROADRREACH_SOCKET_COUNT )
    {
        error_flag = broadrreach_command( ctx, socket, BROADRREACH_CMD_CLOSE );
        if ( BROADRREACH_OK == error_flag )
        {
            // Socket interrupt flags use write-one-to-clear semantics.
            error_flag = broadrreach_write_reg( ctx, BROADRREACH_SOCKET_BASE( socket ) + BROADRREACH_SN_IR, 
                                                BROADRREACH_IR_ALL );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_get_status( ctx, socket, &status );
        }
        if ( ( BROADRREACH_OK == error_flag ) && ( BROADRREACH_STATUS_CLOSED != status ) )
        {
            error_flag = BROADRREACH_ERROR;
        }
    }
    return error_flag;
}

err_t broadrreach_get_status ( broadrreach_t *ctx, uint8_t socket, uint8_t *status )
{
    err_t error_flag = BROADRREACH_ERROR;

    if ( ( socket < BROADRREACH_SOCKET_COUNT ) && status )
    {
        error_flag = broadrreach_read_reg( ctx, BROADRREACH_SOCKET_BASE( socket ) + BROADRREACH_SN_SR, status );
    }
    return error_flag;
}

err_t broadrreach_set_peer ( broadrreach_t *ctx, uint8_t socket, uint8_t *ip, uint16_t port )
{
    uint16_t base = BROADRREACH_SOCKET_BASE( socket );
    err_t error_flag = BROADRREACH_ERROR;

    if ( ( socket < BROADRREACH_SOCKET_COUNT ) && ip && port )
    {
        // The controller stores IPv4 octets in network order and the port as a big-endian word.
        error_flag = broadrreach_write_regs( ctx, base + BROADRREACH_SN_DIPR, ip, 4 );
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_write_word( ctx, base + BROADRREACH_SN_DPORT, port );
        }
    }
    return error_flag;
}

err_t broadrreach_open_socket ( broadrreach_t *ctx, uint8_t socket, uint16_t local_port,
                                uint8_t *peer_ip, uint16_t peer_port )
{
    err_t error_flag = BROADRREACH_ERROR;

    // Validate the destination before opening so invalid input cannot leave a socket partially configured.
    if ( peer_ip && peer_port )
    {
        error_flag = broadrreach_open_udp( ctx, socket, local_port );
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_set_peer( ctx, socket, peer_ip, peer_port );
        }
    }
    return error_flag;
}

err_t broadrreach_send_udp ( broadrreach_t *ctx, uint8_t socket, uint8_t *data_in, uint16_t len )
{
    uint16_t base = BROADRREACH_SOCKET_BASE( socket );
    uint16_t free_size;
    uint16_t pointer;
    uint16_t elapsed;
    uint8_t status;
    uint8_t flags = 0;
    err_t error_flag = BROADRREACH_ERROR;

    if ( ( socket < BROADRREACH_SOCKET_COUNT ) && data_in && len && ( len <= BROADRREACH_UDP_MAX_SIZE ) )
    {
        error_flag = broadrreach_get_status( ctx, socket, &status );
        if ( ( BROADRREACH_OK == error_flag ) && ( BROADRREACH_STATUS_UDP != status ) )
        {
            error_flag = BROADRREACH_ERROR;
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_read_size( ctx, base + BROADRREACH_SN_TX_FSR, &free_size );
        }
        if ( ( BROADRREACH_OK == error_flag ) && ( free_size < len ) )
        {
            error_flag = BROADRREACH_TIMEOUT;
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_read_word( ctx, base + BROADRREACH_SN_TX_WR, &pointer );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_write_buffer( ctx, BROADRREACH_TX_BASE + ( uint16_t ) socket * BROADRREACH_BUFFER_SIZE,
                                                   pointer, data_in, len );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            // Clear only TX-related flags so pending receive events are not lost.
            error_flag = broadrreach_write_reg( ctx, base + BROADRREACH_SN_IR,
                                                BROADRREACH_IR_SEND_OK | BROADRREACH_IR_TIMEOUT );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_write_word( ctx, base + BROADRREACH_SN_TX_WR, ( uint16_t ) ( pointer + len ) );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_command( ctx, socket, BROADRREACH_CMD_SEND );
        }

        // Command acceptance alone does not prove transmission; wait for SEND_OK or ARP timeout.
        for ( elapsed = 0; ( elapsed < BROADRREACH_WAIT_MS ) && ( BROADRREACH_OK == error_flag ); elapsed++ )
        {
            error_flag = broadrreach_read_reg( ctx, base + BROADRREACH_SN_IR, &flags );
            if ( ( BROADRREACH_OK != error_flag ) || ( flags & ( BROADRREACH_IR_SEND_OK | BROADRREACH_IR_TIMEOUT ) ) )
            {
                break;
            }
            Delay_1ms( );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_write_reg( ctx, base + BROADRREACH_SN_IR,
                                                flags & ( BROADRREACH_IR_SEND_OK | BROADRREACH_IR_TIMEOUT ) );
            if ( ( BROADRREACH_OK == error_flag ) &&
                 ( ( flags & BROADRREACH_IR_TIMEOUT ) || !( flags & BROADRREACH_IR_SEND_OK ) ) )
            {
                error_flag = BROADRREACH_TIMEOUT;
            }
        }
    }
    return error_flag;
}

err_t broadrreach_receive_udp ( broadrreach_t *ctx, uint8_t socket, uint8_t *data_out, uint16_t size,
                                broadrreach_packet_t *packet )
{
    uint16_t base = BROADRREACH_SOCKET_BASE( socket );
    uint16_t rx_base = BROADRREACH_RX_BASE + ( uint16_t ) socket * BROADRREACH_BUFFER_SIZE;
    uint16_t available;
    uint16_t pointer;
    uint8_t header[ BROADRREACH_UDP_HEADER_SIZE ];
    uint8_t status;
    uint8_t discard = 0;
    err_t error_flag = BROADRREACH_ERROR;

    if ( ( socket < BROADRREACH_SOCKET_COUNT ) && data_out && size && packet )
    {
        memset( packet, 0, sizeof( broadrreach_packet_t ) );
        error_flag = broadrreach_get_status( ctx, socket, &status );
        if ( ( BROADRREACH_OK == error_flag ) && ( BROADRREACH_STATUS_UDP != status ) )
        {
            error_flag = BROADRREACH_ERROR;
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_read_size( ctx, base + BROADRREACH_SN_RX_RSR, &available );
        }
        if ( ( BROADRREACH_OK == error_flag ) && ( available < BROADRREACH_UDP_HEADER_SIZE ) )
        {
            error_flag = BROADRREACH_NO_DATA;
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_read_word( ctx, base + BROADRREACH_SN_RX_RD, &pointer );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            // The first eight bytes are the W3150A+ UDP header: source IP, source port, and payload length.
            error_flag = broadrreach_read_buffer( ctx, rx_base, pointer, header, sizeof( header ) );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            memcpy( packet->ip, header, 4 );
            packet->port = ( ( uint16_t ) header[ 4 ] << 8 ) | header[ 5 ];
            packet->length = ( ( uint16_t ) header[ 6 ] << 8 ) | header[ 7 ];

            // Never advance RX_RD past the complete datagram currently held in the receive buffer.
            if ( packet->length > BROADRREACH_BUFFER_SIZE - BROADRREACH_UDP_HEADER_SIZE )
            {
                error_flag = BROADRREACH_ERROR;
            }
            else if ( packet->length > available - BROADRREACH_UDP_HEADER_SIZE )
            {
                error_flag = BROADRREACH_NO_DATA;
            }
            else if ( packet->length > size )
            {
                discard = 1;
            }
            else
            {
                error_flag = broadrreach_read_buffer( ctx, rx_base,
                                                      ( uint16_t ) ( pointer + BROADRREACH_UDP_HEADER_SIZE ),
                                                      data_out, packet->length );
            }
        }
        if ( BROADRREACH_OK == error_flag )
        {
            // Clear RECV first; the controller reasserts it if another packet remains after the command.
            error_flag = broadrreach_write_reg( ctx, base + BROADRREACH_SN_IR, BROADRREACH_IR_RECV );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            pointer += BROADRREACH_UDP_HEADER_SIZE + packet->length;
            error_flag = broadrreach_write_word( ctx, base + BROADRREACH_SN_RX_RD, pointer );
        }
        if ( BROADRREACH_OK == error_flag )
        {
            error_flag = broadrreach_command( ctx, socket, BROADRREACH_CMD_RECV );
        }
        if ( ( BROADRREACH_OK == error_flag ) && discard )
        {
            error_flag = BROADRREACH_BUFFER_ERROR;
        }
    }
    return error_flag;
}

static err_t broadrreach_read_word ( broadrreach_t *ctx, uint16_t reg, uint16_t *value )
{
    uint8_t data_buf[ 2 ];
    err_t error_flag = broadrreach_read_regs( ctx, reg, data_buf, sizeof( data_buf ) );

    if ( BROADRREACH_OK == error_flag )
    {
        *value = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

static err_t broadrreach_write_word ( broadrreach_t *ctx, uint16_t reg, uint16_t value )
{
    uint8_t data_buf[ 2 ];

    data_buf[ 0 ] = ( uint8_t ) ( value >> 8 );
    data_buf[ 1 ] = ( uint8_t ) value;
    return broadrreach_write_regs( ctx, reg, data_buf, sizeof( data_buf ) );
}

static err_t broadrreach_read_size ( broadrreach_t *ctx, uint16_t reg, uint16_t *size )
{
    uint16_t previous;
    uint16_t current;
    uint8_t attempt;
    err_t error_flag = broadrreach_read_word( ctx, reg, &previous );

    // A packet can arrive between the separate SPI reads of the upper and lower bytes.
    for ( attempt = 0; ( attempt < BROADRREACH_SIZE_READS ) && ( BROADRREACH_OK == error_flag ); attempt++ )
    {
        error_flag = broadrreach_read_word( ctx, reg, &current );
        if ( ( BROADRREACH_OK == error_flag ) && ( current == previous ) )
        {
            if ( current <= BROADRREACH_BUFFER_SIZE )
            {
                *size = current;
            }
            else
            {
                error_flag = BROADRREACH_ERROR;
            }
            break;
        }
        if ( BROADRREACH_OK == error_flag )
        {
            previous = current;
        }
    }
    if ( ( BROADRREACH_OK == error_flag ) && ( BROADRREACH_SIZE_READS == attempt ) )
    {
        error_flag = BROADRREACH_TIMEOUT;
    }
    return error_flag;
}

static err_t broadrreach_command ( broadrreach_t *ctx, uint8_t socket, uint8_t command )
{
    uint16_t reg = BROADRREACH_SOCKET_BASE( socket ) + BROADRREACH_SN_CR;
    uint16_t elapsed;
    uint8_t value = command;
    err_t error_flag = broadrreach_write_reg( ctx, reg, command );

    // Sn_CR remains non-zero while the W3150A+ accepts the command.
    for ( elapsed = 0; ( elapsed < BROADRREACH_WAIT_MS ) && ( BROADRREACH_OK == error_flag ); elapsed++ )
    {
        error_flag = broadrreach_read_reg( ctx, reg, &value );
        if ( ( BROADRREACH_OK != error_flag ) || ( 0 == value ) )
        {
            break;
        }
        Delay_1ms( );
    }
    if ( ( BROADRREACH_OK == error_flag ) && value )
    {
        error_flag = BROADRREACH_TIMEOUT;
    }
    return error_flag;
}

static err_t broadrreach_read_buffer ( broadrreach_t *ctx, uint16_t base, uint16_t pointer,
                                       uint8_t *data_out, uint16_t len )
{
    uint16_t offset = pointer & BROADRREACH_BUFFER_MASK;
    uint16_t first = BROADRREACH_BUFFER_SIZE - offset;
    err_t error_flag;

    // Split a datagram at the ring boundary; the second transfer starts at the buffer base.
    if ( first > len )
    {
        first = len;
    }
    error_flag = broadrreach_read_regs( ctx, base + offset, data_out, first );
    if ( ( BROADRREACH_OK == error_flag ) && ( len > first ) )
    {
        error_flag = broadrreach_read_regs( ctx, base, &data_out[ first ], len - first );
    }
    return error_flag;
}

static err_t broadrreach_write_buffer ( broadrreach_t *ctx, uint16_t base, uint16_t pointer,
                                        uint8_t *data_in, uint16_t len )
{
    uint16_t offset = pointer & BROADRREACH_BUFFER_MASK;
    uint16_t first = BROADRREACH_BUFFER_SIZE - offset;
    err_t error_flag;

    // Split a datagram at the ring boundary; the second transfer starts at the buffer base.
    if ( first > len )
    {
        first = len;
    }
    error_flag = broadrreach_write_regs( ctx, base + offset, data_in, first );
    if ( ( BROADRREACH_OK == error_flag ) && ( len > first ) )
    {
        error_flag = broadrreach_write_regs( ctx, base, &data_in[ first ], len - first );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
