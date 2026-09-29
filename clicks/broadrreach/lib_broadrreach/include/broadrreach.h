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
 * @file broadrreach.h
 * @brief This file contains API for BroadR-Reach Click Driver.
 */

#ifndef BROADRREACH_H
#define BROADRREACH_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup broadrreach BroadR-Reach Click Driver
 * @brief API for configuring and manipulating BroadR-Reach Click driver.
 * @{
 */

/**
 * @defgroup broadrreach_reg BroadR-Reach Registers List
 * @brief List of registers of BroadR-Reach Click driver.
 */

/**
 * @addtogroup broadrreach_reg
 * @{
 */

/**
 * @brief BroadR-Reach Click common register addresses.
 * @details These macros contain absolute byte addresses. Multi-byte values use the most significant byte first.
 */
#define BROADRREACH_REG_MR                      0x0000
#define BROADRREACH_REG_GAR                     0x0001
#define BROADRREACH_REG_SUBR                    0x0005
#define BROADRREACH_REG_SHAR                    0x0009
#define BROADRREACH_REG_SIPR                    0x000F
#define BROADRREACH_REG_IR                      0x0015
#define BROADRREACH_REG_IMR                     0x0016
#define BROADRREACH_REG_RTR                     0x0017
#define BROADRREACH_REG_RCR                     0x0019
#define BROADRREACH_REG_RMSR                    0x001A
#define BROADRREACH_REG_TMSR                    0x001B
#define BROADRREACH_REG_PATR                    0x001C
#define BROADRREACH_REG_PTIMER                  0x0028
#define BROADRREACH_REG_PMAGIC                  0x0029
#define BROADRREACH_REG_UIPR                    0x002A
#define BROADRREACH_REG_UPORT                   0x002E

/**
 * @brief BroadR-Reach Click socket register offsets.
 * @details Add these offsets to BROADRREACH_SOCKET_BASE( socket ) for sockets 0 to 3.
 */
#define BROADRREACH_SOCKET_BASE( n )            ( 0x0400 + ( ( uint16_t ) ( n ) * 0x0100 ) )
#define BROADRREACH_SN_MR                       0x0000
#define BROADRREACH_SN_CR                       0x0001
#define BROADRREACH_SN_IR                       0x0002
#define BROADRREACH_SN_SR                       0x0003
#define BROADRREACH_SN_PORT                     0x0004
#define BROADRREACH_SN_DHAR                     0x0006
#define BROADRREACH_SN_DIPR                     0x000C
#define BROADRREACH_SN_DPORT                    0x0010
#define BROADRREACH_SN_MSSR                     0x0012
#define BROADRREACH_SN_PROTO                    0x0014
#define BROADRREACH_SN_TOS                      0x0015
#define BROADRREACH_SN_TTL                      0x0016
#define BROADRREACH_SN_TX_FSR                   0x0020
#define BROADRREACH_SN_TX_RD                    0x0022
#define BROADRREACH_SN_TX_WR                    0x0024
#define BROADRREACH_SN_RX_RSR                   0x0026
#define BROADRREACH_SN_RX_RD                    0x0028

/*! @} */ // broadrreach_reg

/**
 * @defgroup broadrreach_set BroadR-Reach Registers Settings
 * @brief Settings for registers of BroadR-Reach Click driver.
 */

/**
 * @addtogroup broadrreach_set
 * @{
 */

/**
 * @brief BroadR-Reach Click SPI operation codes and mode register settings.
 * @details Each SPI transaction transfers one opcode, a 16-bit address, and one data byte in mode 0.
 */
#define BROADRREACH_SPI_READ                    0x0F
#define BROADRREACH_SPI_WRITE                   0xF0
#define BROADRREACH_MR_RESET                    0x80

/**
 * @brief BroadR-Reach Click socket command codes.
 * @details Write these values to Sn_CR to open, close, transmit, or release received data.
 */
#define BROADRREACH_CMD_OPEN                    0x01
#define BROADRREACH_CMD_LISTEN                  0x02
#define BROADRREACH_CMD_CONNECT                 0x04
#define BROADRREACH_CMD_DISCON                  0x08
#define BROADRREACH_CMD_CLOSE                   0x10
#define BROADRREACH_CMD_SEND                    0x20
#define BROADRREACH_CMD_SEND_MAC                0x21
#define BROADRREACH_CMD_SEND_KEEP               0x22
#define BROADRREACH_CMD_RECV                    0x40

/**
 * @brief BroadR-Reach Click socket protocol modes.
 * @details Write one protocol value to Sn_MR before issuing BROADRREACH_CMD_OPEN.
 */
#define BROADRREACH_MODE_TCP                    0x01
#define BROADRREACH_MODE_UDP                    0x02
#define BROADRREACH_MODE_IPRAW                  0x03
#define BROADRREACH_MODE_MACRAW                 0x04
#define BROADRREACH_MODE_PPPOE                  0x05

/**
 * @brief BroadR-Reach Click socket status values.
 * @details Read these values from Sn_SR to determine the current socket protocol state.
 */
#define BROADRREACH_STATUS_CLOSED               0x00
#define BROADRREACH_STATUS_INIT                 0x13
#define BROADRREACH_STATUS_LISTEN               0x14
#define BROADRREACH_STATUS_ESTAB                0x17
#define BROADRREACH_STATUS_CLOSE_WAIT           0x1C
#define BROADRREACH_STATUS_UDP                  0x22
#define BROADRREACH_STATUS_IPRAW                0x32
#define BROADRREACH_STATUS_MACRAW               0x42
#define BROADRREACH_STATUS_PPPOE                0x5F

/**
 * @brief BroadR-Reach Click socket interrupt flags.
 * @details Sn_IR flags are cleared by writing one to the corresponding bit, not by writing zero.
 */
#define BROADRREACH_IR_CON                      0x01
#define BROADRREACH_IR_DISCON                   0x02
#define BROADRREACH_IR_RECV                     0x04
#define BROADRREACH_IR_TIMEOUT                  0x08
#define BROADRREACH_IR_SEND_OK                  0x10
#define BROADRREACH_IR_ALL                      0x1F

/**
 * @brief BroadR-Reach Click socket memory layout and UDP limits.
 * @details The default configuration assigns 2 KB of TX and RX memory to each of four sockets.
 * The 1472-byte payload limit fits a 1500-byte Ethernet MTU without IP fragmentation.
 */
#define BROADRREACH_SOCKET_COUNT                4
#define BROADRREACH_MEM_2KB                     0x55
#define BROADRREACH_BUFFER_SIZE                 2048
#define BROADRREACH_BUFFER_MASK                 0x07FF
#define BROADRREACH_TX_BASE                     0x4000
#define BROADRREACH_RX_BASE                     0x6000
#define BROADRREACH_UDP_HEADER_SIZE             8
#define BROADRREACH_UDP_MAX_SIZE                1472

/**
 * @brief BroadR-Reach Click data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 * Can be overwritten with @b broadrreach_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BROADRREACH_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define BROADRREACH_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // broadrreach_set

/**
 * @defgroup broadrreach_map BroadR-Reach MikroBUS Map
 * @brief MikroBUS pin mapping of BroadR-Reach Click driver.
 */

/**
 * @addtogroup broadrreach_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BroadR-Reach Click to the selected MikroBUS.
 */
#define BROADRREACH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso     = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi     = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck      = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs       = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst      = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // broadrreach_map
/*! @} */ // broadrreach

/**
 * @brief BroadR-Reach Click context object.
 * @details Context object definition of BroadR-Reach Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;           /**< Active-low reset shared by the Ethernet controller and PHY. */

    // Input pins
    digital_in_t int_pin;        /**< Active-low W3150A+ interrupt input. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t chip_select;      /**< Chip select pin descriptor (used for SPI driver). */

} broadrreach_t;

/**
 * @brief BroadR-Reach Click configuration object.
 * @details Configuration object definition of BroadR-Reach Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Active-low reset pin descriptor. */
    pin_name_t int_pin;         /**< Active-low interrupt pin descriptor. */

    // SPI settings
    uint32_t                            spi_speed;   /**< SPI serial speed in Hz; default is 1 MHz. */
    spi_master_mode_t                   spi_mode;    /**< SPI master mode; W3150A+ requires mode 0. */
    spi_master_chip_select_polarity_t   cs_polarity; /**< Chip select pin polarity. */

} broadrreach_cfg_t;

/**
 * @brief BroadR-Reach network parameters.
 * @details Static IPv4 configuration. Use a unique unicast MAC address and IP address for each board.
 */
typedef struct
{
    uint8_t mac[ 6 ];           /**< Local MAC address, most significant byte first. */
    uint8_t ip[ 4 ];            /**< Local IPv4 address in dotted-decimal byte order. */
    uint8_t subnet[ 4 ];        /**< IPv4 subnet mask. */
    uint8_t gateway[ 4 ];       /**< Gateway address; use zero for an isolated same-subnet link. */

} broadrreach_network_t;

/**
 * @brief BroadR-Reach received UDP packet information.
 * @details Sender address and original payload length, excluding the eight-byte hardware header.
 */
typedef struct
{
    uint8_t ip[ 4 ];            /**< Sender IPv4 address. */
    uint16_t port;              /**< Sender UDP port in host byte order. */
    uint16_t length;            /**< Original datagram payload length in bytes. */

} broadrreach_packet_t;

/**
 * @brief BroadR-Reach Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BROADRREACH_OK = 0,         /**< Operation completed successfully. */
    BROADRREACH_ERROR = -1,     /**< Invalid parameter, SPI error, or unexpected controller state. */
    BROADRREACH_TIMEOUT = -2,   /**< Hardware command or transmission did not complete in time. */
    BROADRREACH_NO_DATA = -3,   /**< No complete UDP datagram is available. */
    BROADRREACH_BUFFER_ERROR = -4,  /**< Datagram exceeds the caller's buffer and has been discarded. */

} broadrreach_return_value_t;

/*!
 * @addtogroup broadrreach BroadR-Reach Click Driver
 * @brief API for configuring and manipulating BroadR-Reach Click driver.
 * @{
 */

/**
 * @brief BroadR-Reach configuration object setup function.
 * @details This function initializes Click configuration structure to initial values.
 * @param[out] cfg : Click configuration structure.
 * See #broadrreach_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All used pins are set to the unconnected state. SPI defaults to mode 0 at 1 MHz.
 */
void broadrreach_cfg_setup ( broadrreach_cfg_t *cfg );

/**
 * @brief BroadR-Reach initialization function.
 * @details This function initializes all necessary pins and peripherals used for this Click board.
 * @param[out] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #broadrreach_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - SPI initialization error.
 * See #err_t definition for detailed explanation.
 * @note SPI mode 0 and active-low CS are required by the W3150A+.
 */
err_t broadrreach_init ( broadrreach_t *ctx, broadrreach_cfg_t *cfg );

/**
 * @brief BroadR-Reach default configuration function.
 * @details This function resets the controller, allocates 2 KB per socket in each direction,
 * and selects a 200 ms retry period with three retries.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @return @li @c BROADRREACH_OK - Default configuration applied,
 *         @li @c BROADRREACH_ERROR - Communication or verification error.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note Network addresses are not changed. The onboard PIC configures the PHY from the hardware mode selectors.
 */
err_t broadrreach_default_cfg ( broadrreach_t *ctx );

/**
 * @brief BroadR-Reach write register function.
 * @details This function writes a single byte of data to the selected W3150A+ address.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] reg : Absolute 16-bit register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c BROADRREACH_OK - Register written,
 *         @li @c BROADRREACH_ERROR - SPI communication error.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t broadrreach_write_reg ( broadrreach_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief BroadR-Reach write registers function.
 * @details This function writes a sequential block of data using one SPI transaction per byte.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] reg : Absolute 16-bit start address in register or packet memory.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c BROADRREACH_OK - Registers written,
 *         @li @c BROADRREACH_ERROR - Invalid range or SPI communication error.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t broadrreach_write_regs ( broadrreach_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief BroadR-Reach read register function.
 * @details This function reads a single byte of data from the selected W3150A+ address.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] reg : Absolute 16-bit register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c BROADRREACH_OK - Register read,
 *         @li @c BROADRREACH_ERROR - Invalid argument or SPI communication error.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t broadrreach_read_reg ( broadrreach_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief BroadR-Reach read registers function.
 * @details This function reads a sequential block of data using one SPI transaction per byte.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] reg : Absolute 16-bit start address in register or packet memory.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c BROADRREACH_OK - Registers read,
 *         @li @c BROADRREACH_ERROR - Invalid range or SPI communication error.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note None.
 */
err_t broadrreach_read_regs ( broadrreach_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief BroadR-Reach hardware reset function.
 * @details This function resets the W3150A+ and BCM54811, then waits four seconds for PHY configuration.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @return Nothing.
 * @note The onboard PIC reapplies its hardware-selected PHY mode during the wait.
 */
void broadrreach_hw_reset ( broadrreach_t *ctx );

/**
 * @brief BroadR-Reach network configuration function.
 * @details This function writes and verifies the local MAC, IPv4, subnet mask, and gateway addresses.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] network : Network parameters.
 * See #broadrreach_network_t object definition for detailed explanation.
 * @return @li @c BROADRREACH_OK - Network configuration applied,
 *         @li @c BROADRREACH_ERROR - Communication or verification error.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note Call before opening sockets. This function does not perform DHCP or configure the PHY mode.
 */
err_t broadrreach_set_network ( broadrreach_t *ctx, broadrreach_network_t *network );

/**
 * @brief BroadR-Reach UDP socket open function.
 * @details This function closes the selected socket, assigns its local port, and opens it in UDP mode.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] socket : Socket number, from 0 to 3.
 * @param[in] port : Local UDP port, from 1 to 65535.
 * @return @li @c BROADRREACH_OK - UDP socket opened,
 *         @li @c BROADRREACH_ERROR - Invalid argument or communication error,
 *         @li @c BROADRREACH_TIMEOUT - Socket command timed out.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note Requires the default 2 KB per-socket memory allocation. Discards any previously queued data.
 */
err_t broadrreach_open_udp ( broadrreach_t *ctx, uint8_t socket, uint16_t port );

/**
 * @brief BroadR-Reach socket close function.
 * @details This function closes the selected socket and clears its pending interrupt flags.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] socket : Socket number, from 0 to 3.
 * @return @li @c BROADRREACH_OK - Socket closed,
 *         @li @c BROADRREACH_ERROR - Invalid argument or communication error,
 *         @li @c BROADRREACH_TIMEOUT - Socket command timed out.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note Discards queued data. This is not a graceful TCP disconnect.
 */
err_t broadrreach_close_socket ( broadrreach_t *ctx, uint8_t socket );

/**
 * @brief BroadR-Reach socket status function.
 * @details This function reads the selected socket's protocol state from Sn_SR.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] socket : Socket number, from 0 to 3.
 * @param[out] status : Socket status, such as BROADRREACH_STATUS_UDP or BROADRREACH_STATUS_CLOSED.
 * @return @li @c BROADRREACH_OK - Status read,
 *         @li @c BROADRREACH_ERROR - Invalid argument or SPI communication error.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note Socket state is not PHY link status. The PHY management bus is connected to the onboard PIC.
 */
err_t broadrreach_get_status ( broadrreach_t *ctx, uint8_t socket, uint8_t *status );

/**
 * @brief BroadR-Reach destination configuration function.
 * @details This function sets the destination IPv4 address and UDP port for subsequent transmissions.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] socket : Socket number, from 0 to 3.
 * @param[in] ip : Four-byte destination IPv4 address.
 * @param[in] port : Destination UDP port, from 1 to 65535.
 * @return @li @c BROADRREACH_OK - Destination configured,
 *         @li @c BROADRREACH_ERROR - Invalid argument or SPI communication error.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note The controller resolves the destination MAC address through ARP when sending.
 */
err_t broadrreach_set_peer ( broadrreach_t *ctx, uint8_t socket, uint8_t *ip, uint16_t port );

/**
 * @brief BroadR-Reach UDP socket setup function.
 * @details This function opens a local UDP socket and configures its destination IPv4 address and port.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] socket : Socket number, from 0 to 3.
 * @param[in] local_port : Local UDP port, from 1 to 65535.
 * @param[in] peer_ip : Four-byte destination IPv4 address.
 * @param[in] peer_port : Destination UDP port, from 1 to 65535.
 * @return @li @c BROADRREACH_OK - UDP socket opened and destination configured,
 *         @li @c BROADRREACH_ERROR - Invalid argument or communication error,
 *         @li @c BROADRREACH_TIMEOUT - Socket command timed out.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note This function discards any previously queued data on the selected socket.
 */
err_t broadrreach_open_socket ( broadrreach_t *ctx, uint8_t socket, uint16_t local_port,
                                uint8_t *peer_ip, uint16_t peer_port );

/**
 * @brief BroadR-Reach UDP transmission function.
 * @details This function writes one datagram to the socket TX buffer and waits for SEND_OK or a timeout.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] socket : Open UDP socket number, from 0 to 3.
 * @param[in] data_in : Payload bytes to transmit.
 * @param[in] len : Payload length, from 1 to BROADRREACH_UDP_MAX_SIZE bytes.
 * @return @li @c BROADRREACH_OK - Datagram sent,
 *         @li @c BROADRREACH_ERROR - Invalid argument or communication error,
 *         @li @c BROADRREACH_TIMEOUT - Transmission timed out.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note Call broadrreach_set_peer first. Success confirms local transmission, not receipt by the peer.
 * Reopen the socket and set the peer again after a failed send to discard any pending transmission.
 */
err_t broadrreach_send_udp ( broadrreach_t *ctx, uint8_t socket, uint8_t *data_in, uint16_t len );

/**
 * @brief BroadR-Reach UDP reception function.
 * @details This function reads one complete UDP datagram and its sender information, then releases its RX memory.
 * @param[in] ctx : Click context object.
 * See #broadrreach_t object definition for detailed explanation.
 * @param[in] socket : Open UDP socket number, from 0 to 3.
 * @param[out] data_out : Payload buffer; no string terminator is appended.
 * @param[in] size : Capacity of the payload buffer in bytes.
 * @param[out] packet : Sender information and original payload length.
 * See #broadrreach_packet_t object definition for detailed explanation.
 * @return @li @c BROADRREACH_OK - Datagram received,
 *         @li @c BROADRREACH_ERROR - Invalid argument or communication error,
 *         @li @c BROADRREACH_NO_DATA - No complete datagram available,
 *         @li @c BROADRREACH_BUFFER_ERROR - Datagram discarded because the buffer is too small.
 * See #broadrreach_return_value_t definition for detailed explanation.
 * @note Does not wait for incoming packets. An oversized datagram is discarded in full; packet retains its metadata.
 */
err_t broadrreach_receive_udp ( broadrreach_t *ctx, uint8_t socket, uint8_t *data_out, uint16_t size,
                                broadrreach_packet_t *packet );

#ifdef __cplusplus
}
#endif
#endif // BROADRREACH_H

/*! @} */ // broadrreach

// ------------------------------------------------------------------------ END
