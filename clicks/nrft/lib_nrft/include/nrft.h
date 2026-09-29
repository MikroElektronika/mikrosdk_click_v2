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
 * @file nrft.h
 * @brief This file contains API for nRF T Click Driver.
 */

#ifndef NRFT_H
#define NRFT_H

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
 * @addtogroup nrft nRF T Click Driver
 * @brief API for configuring and manipulating nRF T Click driver.
 * @{
 */

/**
 * @defgroup nrft_reg nRF T Registers List
 * @brief List of registers of nRF T Click driver.
 */

/**
 * @addtogroup nrft_reg
 * @{
 */

/**
 * @brief nRF T register addresses.
 * @details Register addresses used to configure and monitor nRF T Click.
 */
#define NRFT_REG_CONFIG                             0x00
#define NRFT_REG_EN_AA                              0x01
#define NRFT_REG_EN_RXADDR                          0x02
#define NRFT_REG_SETUP_AW                           0x03
#define NRFT_REG_SETUP_RETR                         0x04
#define NRFT_REG_RF_CH                              0x05
#define NRFT_REG_RF_SETUP                           0x06
#define NRFT_REG_STATUS                             0x07
#define NRFT_REG_OBSERVE_TX                         0x08
#define NRFT_REG_RPD                                0x09
#define NRFT_REG_RX_ADDR_P0                         0x0A
#define NRFT_REG_RX_ADDR_P1                         0x0B
#define NRFT_REG_RX_ADDR_P2                         0x0C
#define NRFT_REG_RX_ADDR_P3                         0x0D
#define NRFT_REG_RX_ADDR_P4                         0x0E
#define NRFT_REG_RX_ADDR_P5                         0x0F
#define NRFT_REG_TX_ADDR                            0x10
#define NRFT_REG_RX_PW_P0                           0x11
#define NRFT_REG_RX_PW_P1                           0x12
#define NRFT_REG_RX_PW_P2                           0x13
#define NRFT_REG_RX_PW_P3                           0x14
#define NRFT_REG_RX_PW_P4                           0x15
#define NRFT_REG_RX_PW_P5                           0x16
#define NRFT_REG_FIFO_STATUS                        0x17
#define NRFT_REG_DYNPD                              0x1C
#define NRFT_REG_FEATURE                            0x1D

/*! @} */ // nrft_reg

/**
 * @defgroup nrft_set nRF T Registers Settings
 * @brief Settings for registers of nRF T Click driver.
 */

/**
 * @addtogroup nrft_set
 * @{
 */

/**
 * @brief nRF T SPI commands.
 * @details SPI command bytes used for register and packet access on nRF T Click.
 */
#define NRFT_CMD_R_REGISTER                         0x00
#define NRFT_CMD_W_REGISTER                         0x20
#define NRFT_CMD_R_RX_PL_WID                        0x60
#define NRFT_CMD_R_RX_PAYLOAD                       0x61
#define NRFT_CMD_W_TX_PAYLOAD                       0xA0
#define NRFT_CMD_W_ACK_PAYLOAD                      0xA8
#define NRFT_CMD_W_TX_PAYLOAD_NO_ACK                0xB0
#define NRFT_CMD_FLUSH_TX                           0xE1
#define NRFT_CMD_FLUSH_RX                           0xE2
#define NRFT_CMD_REUSE_TX_PL                        0xE3
#define NRFT_CMD_NOP                                0xFF

/**
 * @brief nRF T configuration settings.
 * @details CRC, power, receiver, and interrupt mask bits for nRF T Click.
 */
#define NRFT_CONFIG_MASK_RX_DR                      0x40
#define NRFT_CONFIG_MASK_TX_DS                      0x20
#define NRFT_CONFIG_MASK_MAX_RT                     0x10
#define NRFT_CONFIG_EN_CRC                          0x08
#define NRFT_CONFIG_CRC_2_BYTES                     0x04
#define NRFT_CONFIG_PWR_UP                          0x02
#define NRFT_CONFIG_PRIM_RX                         0x01

/**
 * @brief nRF T data pipe settings.
 * @details Pipe masks and address widths used by nRF T Click.
 */
#define NRFT_PIPE_0                                 0x01
#define NRFT_PIPE_1                                 0x02
#define NRFT_PIPE_2                                 0x04
#define NRFT_PIPE_3                                 0x08
#define NRFT_PIPE_4                                 0x10
#define NRFT_PIPE_5                                 0x20
#define NRFT_PIPE_ALL                               0x3F
#define NRFT_ADDRESS_WIDTH_3_BYTES                  0x01
#define NRFT_ADDRESS_WIDTH_4_BYTES                  0x02
#define NRFT_ADDRESS_WIDTH_5_BYTES                  0x03

/**
 * @brief nRF T automatic retry settings.
 * @details Retry delay fields are combined with a retry count from 0 to 15 on nRF T Click.
 */
#define NRFT_RETRY_DELAY_250_US                     0x00
#define NRFT_RETRY_DELAY_500_US                     0x10
#define NRFT_RETRY_DELAY_750_US                     0x20
#define NRFT_RETRY_DELAY_1000_US                    0x30
#define NRFT_RETRY_DELAY_1500_US                    0x50
#define NRFT_RETRY_DELAY_2000_US                    0x70
#define NRFT_RETRY_DELAY_4000_US                    0xF0
#define NRFT_RETRY_COUNT_MASK                       0x0F

/**
 * @brief nRF T radio settings.
 * @details Air data rate and transmit power fields for the nRF T Click RF_SETUP register.
 */
#define NRFT_DATA_RATE_250_KBPS                     0x20
#define NRFT_DATA_RATE_1_MBPS                       0x00
#define NRFT_DATA_RATE_2_MBPS                       0x08
#define NRFT_TX_POWER_MINUS_18_DBM                  0x00
#define NRFT_TX_POWER_MINUS_12_DBM                  0x02
#define NRFT_TX_POWER_MINUS_6_DBM                   0x04
#define NRFT_TX_POWER_0_DBM                         0x06

/**
 * @brief nRF T status settings.
 * @details Interrupt flags, receive pipe field, and FIFO masks reported by nRF T Click.
 */
#define NRFT_STATUS_RX_DR                           0x40
#define NRFT_STATUS_TX_DS                           0x20
#define NRFT_STATUS_MAX_RT                          0x10
#define NRFT_STATUS_RX_PIPE_MASK                    0x0E
#define NRFT_STATUS_TX_FULL                         0x01
#define NRFT_STATUS_IRQ_MASK                        0x70
#define NRFT_STATUS_TX_IRQ_MASK                     0x30
#define NRFT_FIFO_TX_REUSE                          0x40
#define NRFT_FIFO_TX_FULL                           0x20
#define NRFT_FIFO_TX_EMPTY                          0x10
#define NRFT_FIFO_RX_FULL                           0x02
#define NRFT_FIFO_RX_EMPTY                          0x01
#define NRFT_OBSERVE_TX_LOST_MASK                   0xF0
#define NRFT_OBSERVE_TX_RETRY_MASK                  0x0F
#define NRFT_RPD_DETECTED                           0x01

/**
 * @brief nRF T feature settings.
 * @details Optional dynamic payload and acknowledgment payload bits for nRF T Click.
 */
#define NRFT_FEATURE_EN_DPL                         0x04
#define NRFT_FEATURE_EN_ACK_PAY                     0x02
#define NRFT_FEATURE_EN_DYN_ACK                     0x01

/**
 * @brief nRF T operating modes.
 * @details Power-down, transmit standby, and continuous receive modes of nRF T Click.
 */
#define NRFT_MODE_POWER_DOWN                        0
#define NRFT_MODE_TX                                1
#define NRFT_MODE_RX                                2

/**
 * @brief nRF T packet limits.
 * @details Maximum payload, address length, and hardware channel index supported by nRF T Click.
 */
#define NRFT_MAX_PAYLOAD_SIZE                       32
#define NRFT_MAX_ADDRESS_SIZE                       5
#define NRFT_MAX_CHANNEL                            125

/**
 * @brief nRF T default radio configuration.
 * @details Matching settings for two nRF T Click boards using fixed-length packets on pipe 0.
 */
#define NRFT_DEFAULT_CHANNEL                        40
#define NRFT_DEFAULT_PAYLOAD_SIZE                   32
#define NRFT_DEFAULT_ADDRESS                        { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 }
#define NRFT_DEFAULT_CONFIG                         ( NRFT_CONFIG_EN_CRC | NRFT_CONFIG_CRC_2_BYTES )
#define NRFT_DEFAULT_RF_SETUP                       ( NRFT_DATA_RATE_1_MBPS | NRFT_TX_POWER_0_DBM )
#define NRFT_DEFAULT_RETRIES                        ( NRFT_RETRY_DELAY_500_US | 15 )

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b nrft_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define NRFT_SET_DATA_SAMPLE_EDGE                   SET_SPI_DATA_SAMPLE_EDGE
#define NRFT_SET_DATA_SAMPLE_MIDDLE                 SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // nrft_set

/**
 * @defgroup nrft_map nRF T MikroBUS Map
 * @brief MikroBUS pin mapping of nRF T Click driver.
 */

/**
 * @addtogroup nrft_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of nRF T Click to the selected MikroBUS.
 */
#define NRFT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ce   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nrft_map
/*! @} */ // nrft

/**
 * @brief nRF T Click context object.
 * @details Context object definition of nRF T Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ce;           /**< Chip Enable Activates RX or TX mode. */

    // Input pins
    digital_in_t int_pin;       /**< Maskable interrupt pin. Active low. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

} nrft_t;

/**
 * @brief nRF T Click configuration object.
 * @details Configuration object definition of nRF T Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t ce;              /**< Chip Enable Activates RX or TX mode. */
    pin_name_t int_pin;         /**< Maskable interrupt pin. Active low. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} nrft_cfg_t;

/**
 * @brief nRF T Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NRFT_OK = 0,
    NRFT_ERROR = -1,
    NRFT_NO_DATA = -2,
    NRFT_MAX_RETRIES = -3,
    NRFT_TIMEOUT = -4

} nrft_return_value_t;

/*!
 * @addtogroup nrft nRF T Click Driver
 * @brief API for configuring and manipulating nRF T Click driver.
 * @{
 */

/**
 * @brief nRF T configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nrft_cfg_t object definition for detailed explanation.
 * @return None.
 * @note All used pins will be set to unconnected state.
 */
void nrft_cfg_setup ( nrft_cfg_t *cfg );

/**
 * @brief nRF T initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nrft_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nrft_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nrft_init ( nrft_t *ctx, nrft_cfg_t *cfg );

/**
 * @brief nRF T default configuration function.
 * @details This function configures nRF T Click for 1 Mbps, 0 dBm, 16-bit CRC, and fixed 32-byte packets on pipe 0.
 * @param[in] ctx : Click context object.
 * See #nrft_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Selects channel 40 (2440 MHz), a five-byte address, and automatic acknowledgment with up to 15 retries.
 * Clears both FIFOs, verifies configuration by readback, and leaves the radio in powered TX standby.
 * Both peers must use matching settings. Dynamic payloads and acknowledgment payloads are disabled.
 */
err_t nrft_default_cfg ( nrft_t *ctx );

/**
 * @brief nRF T write register function.
 * @details This function writes one byte to a selected nRF T Click register.
 * @param[in] ctx : Click context object.
 * See #nrft_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Configure the radio in power-down or transmit standby mode. STATUS flags may be cleared while receiving.
 */
err_t nrft_write_reg ( nrft_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief nRF T write registers function.
 * @details This function writes one nRF T Click register, including a multi-byte address register.
 * @param[in] ctx : Click context object.
 * See #nrft_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Input bytes, least significant byte first for an address register.
 * @param[in] len : One byte, or up to five bytes for RX_ADDR_P0, RX_ADDR_P1, and TX_ADDR.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Register addresses do not auto-increment. Configure in power-down or transmit standby mode.
 * STATUS flags may be cleared while receiving. Reserved register addresses are rejected.
 */
err_t nrft_write_regs ( nrft_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief nRF T read register function.
 * @details This function reads one byte from a selected nRF T Click register.
 * @param[in] ctx : Click context object.
 * See #nrft_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nrft_read_reg ( nrft_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief nRF T read registers function.
 * @details This function reads one nRF T Click register, including a multi-byte address register.
 * @param[in] ctx : Click context object.
 * See #nrft_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output bytes, least significant byte first for an address register.
 * @param[in] len : One byte, or up to five bytes for RX_ADDR_P0, RX_ADDR_P1, and TX_ADDR.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Register addresses do not auto-increment. Reserved register addresses are rejected.
 */
err_t nrft_read_regs ( nrft_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief nRF T send command function.
 * @details This function sends one command without payload data to nRF T Click.
 * @param[in] ctx : Click context object.
 * @param[in] command : FLUSH_TX, FLUSH_RX, REUSE_TX_PL, or NOP command.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note Flush commands discard all queued packets in the selected FIFO.
 * Do not flush RX during acknowledgment transmission or reuse a payload during transmission.
 */
err_t nrft_send_command ( nrft_t *ctx, uint8_t command );

/**
 * @brief nRF T set operating mode function.
 * @details This function selects the nRF T Click power-down, transmit standby, or receive mode.
 * @param[in] ctx : Click context object.
 * @param[in] mode : NRFT_MODE_POWER_DOWN, NRFT_MODE_TX, or NRFT_MODE_RX.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note TX mode keeps CE low until nrft_send_packet starts a transfer. RX mode keeps CE high.
 * Call after the current transmission has finished. Queued packets are preserved.
 */
err_t nrft_set_mode ( nrft_t *ctx, uint8_t mode );

/**
 * @brief nRF T set channel function.
 * @details This function selects the nRF T Click radio frequency channel.
 * @param[in] ctx : Click context object.
 * @param[in] channel : Channel index from 0 to NRFT_MAX_CHANNEL.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note The center frequency is 2400 MHz plus the channel index. Both peers must use the same channel.
 * Configure in power-down or transmit standby mode. Writing RF_CH resets the lost-packet counter.
 */
err_t nrft_set_channel ( nrft_t *ctx, uint8_t channel );

/**
 * @brief nRF T set transmit address function.
 * @details This function configures the nRF T Click transmit address and pipe 0 acknowledgment address.
 * @param[in] ctx : Click context object.
 * @param[in] address : Address bytes, least significant byte first.
 * @param[in] len : Address length from 3 to NRFT_MAX_ADDRESS_SIZE bytes.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note Sets the common address width and verifies both addresses by readback.
 * Configure in power-down or transmit standby mode. Both peers must use the same address and width.
 */
err_t nrft_set_tx_address ( nrft_t *ctx, uint8_t *address, uint8_t len );

/**
 * @brief nRF T send packet function.
 * @details This function transmits one nRF T Click packet and waits for completion or retry exhaustion.
 * @param[in] ctx : Click context object.
 * @param[in] data_in : Pointer to the payload bytes.
 * @param[in] len : Payload length from 1 to NRFT_MAX_PAYLOAD_SIZE bytes.
 * @return @li @c 0 - Packet sent (acknowledged when auto acknowledgment is enabled),
 *         @li @c -1 - Invalid arguments or communication error,
 *         @li @c -3 - Automatic retries exhausted without acknowledgment,
 *         @li @c -4 - Transmit completion timeout.
 * @note Enters TX mode and discards pending TX payloads before sending. The wait is bounded to 100 one-ms polls.
 * With fixed payloads, len must match the receiver RX_PW register (32 bytes with the default configuration).
 * Success or retry exhaustion leaves TX standby; a timeout or communication error attempts power-down.
 * Call nrft_set_mode to resume reception. Invalid arguments leave the radio unchanged.
 */
err_t nrft_send_packet ( nrft_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief nRF T receive packet function.
 * @details This function reads one fixed-length packet from the nRF T Click receive FIFO.
 * @param[in] ctx : Click context object.
 * @param[out] data_out : Output buffer of at least NRFT_MAX_PAYLOAD_SIZE bytes.
 * @param[out] len : Received payload length, or zero when no packet is returned.
 * @return @li @c 0 - Packet received,
 *         @li @c -1 - Invalid arguments, payload configuration, or communication error,
 *         @li @c -2 - Receive FIFO empty.
 * @note Supports fixed payload lengths only; dynamic payloads must remain disabled.
 * Poll this function until NRFT_NO_DATA to drain queued packets, independently of the interrupt pin.
 * The received data is binary and is not automatically null-terminated.
 */
err_t nrft_receive_packet ( nrft_t *ctx, uint8_t *data_out, uint8_t *len );

/**
 * @brief nRF T get interrupt function.
 * @details This function reads the nRF T Click active-low interrupt pin.
 * @param[in] ctx : Click context object.
 * @return @li @c 0 - Interrupt pin is active low,
 *         @li @c 1 - Interrupt pin is inactive high.
 * @note Read STATUS to identify the source and write one to its interrupt bit to clear it.
 * Use the receive FIFO status to check for queued packets after an interrupt has been cleared.
 */
uint8_t nrft_get_interrupt ( nrft_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NRFT_H

/*! @} */ // nrft

// ------------------------------------------------------------------------ END
