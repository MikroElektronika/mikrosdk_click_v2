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
 * @file ethwiz.c
 * @brief ETH WIZ Click Driver.
 */

#include "ethwiz.h"

/**
 * @brief ETH WIZ transport settings.
 * @details Defines the minimum MACRAW frame length and the dummy byte clocked out during SPI reads.
 */
#define ETHWIZ_ETH_HEADER_SIZE         14u
#define ETHWIZ_SPI_DUMMY               0x00u

/**
 * @brief ETH WIZ hardware socket settings.
 * @details Defines the W5500 socket 0 register block, commands, states and interrupt bits.
 */
#define ETHWIZ_SOCK_REG                W5500_BSB_SOCKET0_REG( 0 )
#define ETHWIZ_SOCK_CONNECT            0x04u
#define ETHWIZ_SOCK_DISCONNECT         0x08u
#define ETHWIZ_SOCK_INIT               0x13u
#define ETHWIZ_SOCK_ESTABLISHED        0x17u
#define ETHWIZ_SOCK_CLOSE_WAIT         0x1Cu
#define ETHWIZ_SOCK_UDP                0x22u
#define ETHWIZ_SOCK_IR_CONNECTED       0x01u
#define ETHWIZ_SOCK_IR_TIMEOUT         0x08u
#define ETHWIZ_SOCK_IR_SEND_OK         0x10u
#define ETHWIZ_SOCK_IR_ALL             0x1Fu

/**
 * @brief ETH WIZ hardware socket limits.
 * @details Defines the socket poll budgets, stable size read retries and maximum payload size.
 * @note Each wait includes the time spent on SPI transactions in addition to the 1 ms polling delays.
 */
#define ETHWIZ_SOCK_CMD_MS             50u
#define ETHWIZ_SOCK_CONNECT_MS         5000u
#define ETHWIZ_SOCK_SEND_MS            3000u
#define ETHWIZ_SOCK_DISCONNECT_MS      500u
#define ETHWIZ_SOCK_SIZE_RETRIES       8u
#define ETHWIZ_SOCK_TX_MAX             1460u

/**
 * @brief ETH WIZ UDP packet information.
 * @details Size of the W5500 UDP header containing the sender IPv4 address, port and payload length.
 */
#define ETHWIZ_UDP_INFO_SIZE           8u

/**
 * @brief ETH WIZ SDK initialization callback.
 * @details Uses SDK initialization and clears the transmit fault only on success.
 * @param[in] eth : First member of the Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Existing sessions are lost.
 */
static err_t ethwiz_transport_init ( eth_transport_t *eth );

/**
 * @brief ETH WIZ SDK transmit callback.
 * @details Sends through the SDK and prevents further transfers after a failed send.
 * @param[in] eth : First member of the Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] buffer : Ethernet frame without FCS.
 * @param[in] len : Frame length in bytes.
 * @return Number of bytes sent, or zero on error.
 * @note A failed valid-frame transfer latches the context tx_fault flag.
 */
static uint16_t ethwiz_transport_send ( eth_transport_t *eth, uint8_t *buffer, uint16_t len );

/**
 * @brief ETH WIZ word read function.
 * @details Reads a big-endian 16-bit register without changing the output on error.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] reg : Register offset.
 * @param[in] block : Shifted W5500_BSB_* block selector.
 * @param[out] value : Register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ethwiz_read_word ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint16_t *value );

/**
 * @brief ETH WIZ socket register wait function.
 * @details This function polls a socket 0 register until the masked value matches or the poll budget expires.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] reg : Socket register offset.
 * @param[in] mask : Register bits to check.
 * @param[in] expected : Expected value after masking.
 * @param[in] polls : Maximum number of reads separated by 1 ms delays.
 * @return @li @c  0 - Expected value read,
 *         @li @c -1 - SPI error, socket timeout interrupt or poll budget exhausted.
 * See #err_t definition for detailed explanation.
 * @note A socket timeout interrupt aborts the wait when polling Sn_IR.
 */
static err_t ethwiz_sock_wait ( ethwiz_t *ctx, uint16_t reg, uint8_t mask, uint8_t expected, uint16_t polls );

/**
 * @brief ETH WIZ socket command function.
 * @details This function waits for Sn_CR to become idle, writes the command and waits for Sn_CR to clear.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] command : Sn_CR command value.
 * @return @li @c  0 - Command accepted,
 *         @li @c -1 - SPI error or command register did not clear.
 * See #err_t definition for detailed explanation.
 * @note Command acceptance does not confirm completion of TCP connect or transmission.
 */
static err_t ethwiz_sock_cmd ( ethwiz_t *ctx, uint8_t command );

/**
 * @brief ETH WIZ socket buffer size read function.
 * @details This function reads the size register until two consecutive values agree.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] reg : Offset of Sn_TX_FSR or Sn_RX_RSR.
 * @param[out] size : Stable size in bytes.
 * @return @li @c  0 - Stable value read,
 *         @li @c -1 - SPI error or inconsistent values.
 * See #err_t definition for detailed explanation.
 * @note The output is updated only on success.
 */
static err_t ethwiz_sock_size ( ethwiz_t *ctx, uint16_t reg, uint16_t *size );

/**
 * @brief ETH WIZ socket word write function.
 * @details This function writes a 16-bit value to socket 0 in big-endian byte order.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] reg : Socket register offset.
 * @param[in] value : Register value in host byte order.
 * @return @li @c  0 - Success,
 *         @li @c -1 - SPI error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ethwiz_sock_write_word ( ethwiz_t *ctx, uint16_t reg, uint16_t value );

/* Keep the SDK packet and PHY operations. Wrap MACRAW TX so a failed SEND requires a reset. */
static eth_transport_driver_t ethwiz_driver =
{
    .init            = ethwiz_transport_init,
    .reset           = ethwiz_transport_init,
    .send_packet     = ethwiz_transport_send,
    .read_packet     = w5500_read_packet,
    .available       = w5500_packet_available,
    .get_link_status = w5500_get_link_status,
    .set_mac         = w5500_set_mac,
    .set_ip          = w5500_set_ip
};

void ethwiz_cfg_setup ( ethwiz_cfg_t *cfg )
{
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->rst     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = ETHWIZ_SPI_SPEED;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    memset( cfg->mac, 0, sizeof( cfg->mac ) );
    memset( cfg->ip, 0, sizeof( cfg->ip ) );
}

err_t ethwiz_init ( ethwiz_t *ctx, ethwiz_cfg_t *cfg )
{
    err_t error_flag = ETHWIZ_OK;
    w5500_cfg_t eth_cfg;

    w5500_cfg_setup( &eth_cfg );
    eth_cfg.bus.sck = cfg->sck;
    eth_cfg.bus.miso = cfg->miso;
    eth_cfg.bus.mosi = cfg->mosi;
    eth_cfg.bus.cs = cfg->cs;
    eth_cfg.bus.speed = cfg->spi_speed;
    eth_cfg.bus.mode = cfg->spi_mode;
    eth_cfg.eth.rst = cfg->rst;
    memcpy( eth_cfg.eth.mac, cfg->mac, sizeof( cfg->mac ) );
    memcpy( eth_cfg.eth.ip, cfg->ip, sizeof( cfg->ip ) );

    ctx->eth.driver_ctx = &ctx->controller;
    ctx->eth.drv = NULL;
    ctx->tx_fault = 1;

    /* The SDK deselects the device while configuring the SPI bus. */
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    if ( ETH_TRANSPORT_ERROR == w5500_configure( &ctx->eth, &ctx->bus, &eth_cfg ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->bus.spi, ETHWIZ_SPI_DUMMY ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->bus.spi, cfg->spi_mode ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->bus.spi, cfg->spi_speed ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->int_pin, cfg->int_pin ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else
    {
        /* RST high routes mikroBUS CS to the W5500 through the ClickID switch. */
        ethwiz_set_rst_pin( ctx, 1 );
    }

    return error_flag;
}

err_t ethwiz_default_cfg ( ethwiz_t *ctx )
{
    return eth_transport_init( &ctx->eth, &ethwiz_driver );
}

err_t ethwiz_write_reg ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint8_t data_in )
{
    return ethwiz_write_regs( ctx, reg, block, &data_in, 1 );
}

err_t ethwiz_write_regs ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint8_t *data_in, uint16_t len )
{
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t ) ( reg >> 8 );
    header[ 1 ] = ( uint8_t ) reg;
    header[ 2 ] = block | W5500_RWB_WRITE | W5500_OM_VDM;

    return eth_transport_bus_write( &ctx->eth, header, sizeof( header ), data_in, len );
}

err_t ethwiz_read_reg ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint8_t *data_out )
{
    return ethwiz_read_regs( ctx, reg, block, data_out, 1 );
}

err_t ethwiz_read_regs ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint8_t *data_out, uint16_t len )
{
    uint8_t header[ 3 ];

    header[ 0 ] = ( uint8_t ) ( reg >> 8 );
    header[ 1 ] = ( uint8_t ) reg;
    header[ 2 ] = block | W5500_RWB_READ | W5500_OM_VDM;

    return eth_transport_bus_read( &ctx->eth, header, sizeof( header ), data_out, len );
}

err_t ethwiz_get_version ( ethwiz_t *ctx, uint8_t *version )
{
    return ethwiz_read_reg( ctx, W5500_VERSIONR, W5500_BSB_COMMON_REG, version );
}

err_t ethwiz_set_mac ( ethwiz_t *ctx, uint8_t *mac )
{
    return eth_transport_set_mac( &ctx->eth, mac );
}

err_t ethwiz_set_ip ( ethwiz_t *ctx, uint8_t *ip )
{
    return eth_transport_set_ip( &ctx->eth, ip );
}

err_t ethwiz_set_route ( ethwiz_t *ctx, uint8_t *subnet, uint8_t *gateway )
{
    uint8_t mode;
    err_t error_flag = ethwiz_write_regs( ctx, W5500_GAR, W5500_BSB_COMMON_REG, gateway, 4 );

    if ( ETHWIZ_ERROR != error_flag )
    {
        error_flag = ethwiz_write_regs( ctx, W5500_SUBR, W5500_BSB_COMMON_REG, subnet, 4 );
    }
    if ( ETHWIZ_ERROR != error_flag )
    {
        error_flag = ethwiz_read_reg( ctx, W5500_MR, W5500_BSB_COMMON_REG, &mode );
    }
    if ( ETHWIZ_ERROR != error_flag )
    {
        /* The SDK blocks hardware ping replies for MACRAW. Restore them for the IPv4 demo. */
        mode &= ( uint8_t ) ~W5500_MR_PB;
        error_flag = ethwiz_write_reg( ctx, W5500_MR, W5500_BSB_COMMON_REG, mode );
    }
    return error_flag;
}

err_t ethwiz_socket_open ( ethwiz_t *ctx, ethwiz_socket_t *endpoint )
{
    uint8_t status = ETHWIZ_SOCK_UDP;
    err_t error_flag = ETHWIZ_OK;

    if ( W5500_Sn_MR_TCP == endpoint->protocol )
    {
        status = ETHWIZ_SOCK_INIT;
    }
    if ( ( W5500_Sn_MR_TCP != endpoint->protocol ) && ( W5500_Sn_MR_UDP != endpoint->protocol ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_socket_close( ctx ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_write_reg( ctx, W5500_Sn_IR, ETHWIZ_SOCK_REG, ETHWIZ_SOCK_IR_ALL ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_write_reg( ctx, W5500_Sn_MR, ETHWIZ_SOCK_REG, endpoint->protocol ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_sock_write_word( ctx, W5500_Sn_PORT, endpoint->local_port ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_sock_cmd( ctx, W5500_Sn_CR_OPEN ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_sock_wait( ctx, W5500_Sn_SR, 0xFFu, status, ETHWIZ_SOCK_CMD_MS ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_write_regs( ctx, W5500_Sn_DIPR, ETHWIZ_SOCK_REG, endpoint->peer_ip, 4 ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_sock_write_word( ctx, W5500_Sn_DPORT, endpoint->peer_port ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( W5500_Sn_MR_TCP == endpoint->protocol )
    {
        error_flag = ethwiz_sock_cmd( ctx, ETHWIZ_SOCK_CONNECT );
        if ( ETHWIZ_ERROR != error_flag )
        {
            error_flag = ethwiz_sock_wait( ctx, W5500_Sn_IR, ETHWIZ_SOCK_IR_CONNECTED,
                                           ETHWIZ_SOCK_IR_CONNECTED, ETHWIZ_SOCK_CONNECT_MS );
        }
        if ( ETHWIZ_ERROR != error_flag )
        {
            error_flag = ethwiz_write_reg( ctx, W5500_Sn_IR, ETHWIZ_SOCK_REG, ETHWIZ_SOCK_IR_CONNECTED );
        }
    }
    return error_flag;
}

err_t ethwiz_socket_close ( ethwiz_t *ctx )
{
    uint8_t status;
    err_t error_flag = ethwiz_read_reg( ctx, W5500_Sn_SR, ETHWIZ_SOCK_REG, &status );

    if ( ( ETHWIZ_OK == error_flag ) && ( ( ETHWIZ_SOCK_ESTABLISHED == status ) ||
                                          ( ETHWIZ_SOCK_CLOSE_WAIT == status ) ) )
    {
        error_flag = ethwiz_sock_cmd( ctx, ETHWIZ_SOCK_DISCONNECT );
        if ( ETHWIZ_OK == error_flag )
        {
            error_flag = ethwiz_sock_wait( ctx, W5500_Sn_SR, 0xFFu, W5500_SOCK_CLOSED, ETHWIZ_SOCK_DISCONNECT_MS );
        }
        if ( ETHWIZ_OK == error_flag )
        {
            status = W5500_SOCK_CLOSED;
        }
    }
    if ( ( ETHWIZ_ERROR == error_flag ) || ( W5500_SOCK_CLOSED != status ) )
    {
        error_flag = ethwiz_sock_cmd( ctx, W5500_Sn_CR_CLOSE );
        if ( ETHWIZ_OK == error_flag )
        {
            error_flag = ethwiz_sock_wait( ctx, W5500_Sn_SR, 0xFFu, W5500_SOCK_CLOSED, ETHWIZ_SOCK_CMD_MS );
        }
    }
    return error_flag;
}

err_t ethwiz_socket_send ( ethwiz_t *ctx, uint8_t *buffer, uint16_t len )
{
    uint8_t status;
    uint16_t free_size;
    uint16_t offset;
    err_t error_flag = ETHWIZ_OK;

    if ( !len || ( len > ETHWIZ_SOCK_TX_MAX ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_read_reg( ctx, W5500_Sn_SR, ETHWIZ_SOCK_REG, &status ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ( ETHWIZ_SOCK_ESTABLISHED != status ) && ( ETHWIZ_SOCK_UDP != status ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ( ETHWIZ_ERROR == ethwiz_sock_size( ctx, W5500_Sn_TX_FSR, &free_size ) ) || ( free_size < len ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_read_word( ctx, W5500_Sn_TX_WR, ETHWIZ_SOCK_REG, &offset ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_write_regs( ctx, offset, W5500_BSB_SOCKET0_TX( 0 ), buffer, len ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_sock_write_word( ctx, W5500_Sn_TX_WR, offset + len ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_write_reg( ctx, W5500_Sn_IR, ETHWIZ_SOCK_REG, ETHWIZ_SOCK_IR_SEND_OK ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_sock_cmd( ctx, W5500_Sn_CR_SEND ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else if ( ETHWIZ_ERROR == ethwiz_sock_wait( ctx, W5500_Sn_IR, ETHWIZ_SOCK_IR_SEND_OK,
                                                ETHWIZ_SOCK_IR_SEND_OK, ETHWIZ_SOCK_SEND_MS ) )
    {
        error_flag = ETHWIZ_ERROR;
    }
    else
    {
        error_flag = ethwiz_write_reg( ctx, W5500_Sn_IR, ETHWIZ_SOCK_REG, ETHWIZ_SOCK_IR_SEND_OK );
    }
    return error_flag;
}

err_t ethwiz_socket_receive ( ethwiz_t *ctx, ethwiz_socket_t *endpoint, uint8_t *buffer,
                               uint16_t capacity, uint16_t *received )
{
    uint8_t status;
    uint8_t info[ ETHWIZ_UDP_INFO_SIZE ];
    uint16_t available;
    uint16_t offset;
    uint16_t payload_size;
    uint16_t copy_size = 0;
    uint16_t consume = 0;
    err_t error_flag = ETHWIZ_ERROR;

    *received = 0;
    if ( ( ETHWIZ_OK == ethwiz_read_reg( ctx, W5500_Sn_SR, ETHWIZ_SOCK_REG, &status ) ) &&
         ( ( ( W5500_Sn_MR_UDP == endpoint->protocol ) && ( ETHWIZ_SOCK_UDP == status ) ) ||
           ( ( W5500_Sn_MR_TCP == endpoint->protocol ) &&
             ( ( ETHWIZ_SOCK_ESTABLISHED == status ) || ( ETHWIZ_SOCK_CLOSE_WAIT == status ) ) ) ) &&
         ( ETHWIZ_OK == ethwiz_sock_size( ctx, W5500_Sn_RX_RSR, &available ) ) )
    {
        if ( available || ( ETHWIZ_SOCK_CLOSE_WAIT != status ) )
        {
            error_flag = ETHWIZ_OK;
        }
    }
    if ( ( ETHWIZ_OK == error_flag ) && available )
    {
        error_flag = ethwiz_read_word( ctx, W5500_Sn_RX_RD, ETHWIZ_SOCK_REG, &offset );
        if ( ( ETHWIZ_OK == error_flag ) && ( W5500_Sn_MR_UDP == endpoint->protocol ) )
        {
            error_flag = ETHWIZ_ERROR;
            if ( ( available >= sizeof( info ) ) &&
                 ( ETHWIZ_OK == ethwiz_read_regs( ctx, offset, W5500_BSB_SOCKET0_RX( 0 ), info, sizeof( info ) ) ) )
            {
                /* W5500 UDP header: sender IPv4 address, sender port, then payload length. */
                payload_size = ( ( uint16_t ) info[ 6 ] << 8 ) | info[ 7 ];
                if ( payload_size <= ( available - sizeof( info ) ) )
                {
                    consume = sizeof( info ) + payload_size;
                    if ( ( payload_size <= capacity ) && !memcmp( info, endpoint->peer_ip, 4 ) &&
                         ( endpoint->peer_port == ( ( ( uint16_t ) info[ 4 ] << 8 ) | info[ 5 ] ) ) )
                    {
                        copy_size = payload_size;
                    }
                    error_flag = ETHWIZ_OK;
                }
            }
        }
        else if ( ETHWIZ_OK == error_flag )
        {
            copy_size = available;
            if ( copy_size > capacity )
            {
                copy_size = capacity;
            }
            consume = copy_size;
        }

        if ( ( ETHWIZ_OK == error_flag ) && consume )
        {
            if ( copy_size )
            {
                payload_size = offset;
                if ( W5500_Sn_MR_UDP == endpoint->protocol )
                {
                    payload_size += sizeof( info );
                }
                error_flag = ethwiz_read_regs( ctx, payload_size, W5500_BSB_SOCKET0_RX( 0 ), buffer, copy_size );
            }
            if ( ( ETHWIZ_OK == error_flag ) &&
                 ( ETHWIZ_OK == ethwiz_sock_write_word( ctx, W5500_Sn_RX_RD, offset + consume ) ) )
            {
                error_flag = ethwiz_sock_cmd( ctx, W5500_Sn_CR_RECV );
            }
            else
            {
                error_flag = ETHWIZ_ERROR;
            }
            if ( ETHWIZ_OK == error_flag )
            {
                *received = copy_size;
            }
        }
    }
    return error_flag;
}

uint16_t ethwiz_send_packet ( ethwiz_t *ctx, uint8_t *data_in, uint16_t len )
{
    return eth_transport_send( &ctx->eth, data_in, len );
}

uint16_t ethwiz_read_packet ( ethwiz_t *ctx, uint8_t *data_out, uint16_t len )
{
    uint16_t read_len = 0;

    if ( !ctx->tx_fault )
    {
        read_len = eth_transport_receive( &ctx->eth, data_out, len );
    }
    return read_len;
}

uint8_t ethwiz_packet_available ( ethwiz_t *ctx )
{
    return eth_transport_available( &ctx->eth );
}

uint8_t ethwiz_get_link_status ( ethwiz_t *ctx )
{
    uint8_t link_status;

    ctx->eth.bus_error = 0;
    link_status = eth_transport_get_link_status( &ctx->eth );
    if ( ctx->eth.bus_error )
    {
        link_status = 0;
    }
    return link_status;
}

void ethwiz_set_rst_pin ( ethwiz_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->eth.reset, state );
}

uint8_t ethwiz_get_int_pin ( ethwiz_t *ctx )
{
    return !!digital_in_read( &ctx->int_pin );
}

static err_t ethwiz_transport_init ( eth_transport_t *eth )
{
    /* eth is the first member of the Click context. */
    ethwiz_t *ctx = ( ethwiz_t * ) eth;
    err_t error_flag;

    ctx->tx_fault = 1;
    error_flag = w5500_init( eth );
    if ( ETHWIZ_OK == error_flag )
    {
        ctx->tx_fault = 0;
    }
    return error_flag;
}

static uint16_t ethwiz_transport_send ( eth_transport_t *eth, uint8_t *buffer, uint16_t len )
{
    ethwiz_t *ctx = ( ethwiz_t * ) eth;
    uint16_t sent_len = 0;

    if ( !ctx->tx_fault && ( len >= ETHWIZ_ETH_HEADER_SIZE ) && ( len <= ETHWIZ_FRAME_SIZE ) )
    {
        sent_len = w5500_send_packet( eth, buffer, len );
        if ( sent_len != len )
        {
            /* SDK timeouts can leave a SEND pending; require reset before reusing the socket. */
            ctx->tx_fault = 1;
        }
    }
    return sent_len;
}

static err_t ethwiz_read_word ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint16_t *value )
{
    uint8_t buffer[ 2 ];
    err_t error_flag = ethwiz_read_regs( ctx, reg, block, buffer, sizeof( buffer ) );

    if ( ETHWIZ_OK == error_flag )
    {
        *value = ( ( uint16_t ) buffer[ 0 ] << 8 ) | buffer[ 1 ];
    }
    return error_flag;
}

static err_t ethwiz_sock_wait ( ethwiz_t *ctx, uint16_t reg, uint8_t mask, uint8_t expected, uint16_t polls )
{
    uint8_t value;
    err_t error_flag = ETHWIZ_ERROR;

    while ( polls-- )
    {
        if ( ( ETHWIZ_ERROR == ethwiz_read_reg( ctx, reg, ETHWIZ_SOCK_REG, &value ) ) ||
             ( ( W5500_Sn_IR == reg ) && ( value & ETHWIZ_SOCK_IR_TIMEOUT ) ) )
        {
            break;
        }
        if ( expected == ( value & mask ) )
        {
            error_flag = ETHWIZ_OK;
            break;
        }
        Delay_1ms( );
    }
    return error_flag;
}

static err_t ethwiz_sock_cmd ( ethwiz_t *ctx, uint8_t command )
{
    err_t error_flag = ETHWIZ_ERROR;

    if ( ( ETHWIZ_OK == ethwiz_sock_wait( ctx, W5500_Sn_CR, 0xFFu, 0, ETHWIZ_SOCK_CMD_MS ) ) &&
         ( ETHWIZ_OK == ethwiz_write_reg( ctx, W5500_Sn_CR, ETHWIZ_SOCK_REG, command ) ) )
    {
        error_flag = ethwiz_sock_wait( ctx, W5500_Sn_CR, 0xFFu, 0, ETHWIZ_SOCK_CMD_MS );
    }
    return error_flag;
}

static err_t ethwiz_sock_size ( ethwiz_t *ctx, uint16_t reg, uint16_t *size )
{
    uint8_t retry;
    uint16_t previous;
    uint16_t current;
    err_t error_flag = ETHWIZ_ERROR;

    if ( ETHWIZ_OK == ethwiz_read_word( ctx, reg, ETHWIZ_SOCK_REG, &previous ) )
    {
        for ( retry = 0; retry < ETHWIZ_SOCK_SIZE_RETRIES; retry++ )
        {
            if ( ETHWIZ_ERROR == ethwiz_read_word( ctx, reg, ETHWIZ_SOCK_REG, &current ) )
            {
                break;
            }
            if ( previous == current )
            {
                *size = current;
                error_flag = ETHWIZ_OK;
                break;
            }
            previous = current;
        }
    }
    return error_flag;
}

static err_t ethwiz_sock_write_word ( ethwiz_t *ctx, uint16_t reg, uint16_t value )
{
    uint8_t buffer[ 2 ] = { ( uint8_t ) ( value >> 8 ), ( uint8_t ) value };

    return ethwiz_write_regs( ctx, reg, ETHWIZ_SOCK_REG, buffer, sizeof( buffer ) );
}

// ------------------------------------------------------------------------- END
