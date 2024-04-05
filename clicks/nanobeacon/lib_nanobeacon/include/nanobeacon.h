/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file nanobeacon.h
 * @brief This file contains API for NanoBeacon Click Driver.
 */

#ifndef NANOBEACON_H
#define NANOBEACON_H

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
#include "drv_uart.h"

/*!
 * @addtogroup nanobeacon NanoBeacon Click Driver
 * @brief API for configuring and manipulating NanoBeacon Click driver.
 * @{
 */

/**
 * @defgroup nanobeacon_cmd NanoBeacon Device Settings
 * @brief Settings for registers of NanoBeacon Click driver.
 */

/**
 * @addtogroup nanobeacon_cmd
 * @{
 */

/**
 * @brief NanoBeacon opcode commands.
 * @details Specified setting for opcode commands of NanoBeacon Click driver.
 */
#define NANOBEACON_OPCODE_READY             0x01
#define NANOBEACON_OPCODE_READY_ACK         0x80
#define NANOBEACON_OPCODE_READY_NACK        0x81
#define NANOBEACON_OPCODE_RATE              0x02
#define NANOBEACON_OPCODE_READ_REG          0x03
#define NANOBEACON_OPCODE_READ_REG_RESP     0x83
#define NANOBEACON_OPCODE_WRITE_REG         0x04
#define NANOBEACON_OPCODE_WRITE_REG_RESP    0x84
#define NANOBEACON_OPCODE_READ_MEM          0x05
#define NANOBEACON_OPCODE_READ_MEM_RESP     0x85
#define NANOBEACON_OPCODE_WRITE_MEM         0x06
#define NANOBEACON_OPCODE_WRITE_MEM_RESP    0x86
#define NANOBEACON_OPCODE_READ_EFUSE        0x07
#define NANOBEACON_OPCODE_READ_EFUSE_RESP   0x87
#define NANOBEACON_OPCODE_WRITE_EFUSE       0x08
#define NANOBEACON_OPCODE_WRITE_EFUSE_RESP  0x88

/**
 * @brief NanoBeacon command and data packet format.
 * @details Specified setting for command and data packet format of NanoBeacon Click driver.
 */
#define NANOBEACON_PACKET_HEADER            0xAE
#define NANOBEACON_PACKET_TAIL              0xEA
#define NANOBEACON_PAYLOAD_READY            0xAA
#define NANOBEACON_PACKET_PAYLOAD_SIZE      128
#define NANOBEACON_TIMEOUT_MS               3000
#define NANOBEACON_CHECK_COMM_NUM_TRIES     5

/**
 * @brief NanoBeacon driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NANOBEACON_TX_DRV_BUFFER_SIZE       ( NANOBEACON_PACKET_PAYLOAD_SIZE + 4 )
#define NANOBEACON_RX_DRV_BUFFER_SIZE       ( NANOBEACON_PACKET_PAYLOAD_SIZE + 4 )

/*! @} */ // nanobeacon_cmd

/**
 * @defgroup nanobeacon_map NanoBeacon MikroBUS Map
 * @brief MikroBUS pin mapping of NanoBeacon Click driver.
 */

/**
 * @addtogroup nanobeacon_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NanoBeacon Click to the selected MikroBUS.
 */
#define NANOBEACON_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dq = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // nanobeacon_map
/*! @} */ // nanobeacon

/**
 * @brief NanoBeacon Click packet object.
 * @details Packet object definition of NanoBeacon Click driver.
 */
typedef struct
{
    uint8_t opcode;         /**< Opcode byte. */
    uint8_t payload_len;    /**< Payload length. */
    uint8_t payload[ NANOBEACON_PACKET_PAYLOAD_SIZE ];  /**< Payload data. */

} nanobeacon_packet_t;

/**
 * @brief NanoBeacon Click context object.
 * @details Context object definition of NanoBeacon Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;       /**< Chip enable pin (Active low). */
    digital_out_t dq;       /**< MGPIO5 pin. */

    // Input pins
    digital_in_t an;        /**< MGPIO4 pin. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ NANOBEACON_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    uint8_t uart_tx_buffer[ NANOBEACON_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    
} nanobeacon_t;

/**
 * @brief NanoBeacon Click configuration object.
 * @details Configuration object definition of NanoBeacon Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t an;          /**< MGPIO4 pin. */
    pin_name_t en;          /**< Chip enable pin (Active low). */
    pin_name_t dq;          /**< MGPIO5 pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} nanobeacon_cfg_t;

/**
 * @brief NanoBeacon Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NANOBEACON_OK = 0,
    NANOBEACON_ERROR = -1

} nanobeacon_return_value_t;

/*!
 * @addtogroup nanobeacon NanoBeacon Click Driver
 * @brief API for configuring and manipulating NanoBeacon Click driver.
 * @{
 */

/**
 * @brief NanoBeacon configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nanobeacon_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nanobeacon_cfg_setup ( nanobeacon_cfg_t *cfg );

/**
 * @brief NanoBeacon initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nanobeacon_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_init ( nanobeacon_t *ctx, nanobeacon_cfg_t *cfg );

/**
 * @brief NanoBeacon data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_generic_write ( nanobeacon_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NanoBeacon data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_generic_read ( nanobeacon_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NanoBeacon get an pin function.
 * @details This function returns the AN pin logic state.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nanobeacon_get_an_pin ( nanobeacon_t *ctx );

/**
 * @brief NanoBeacon set EN pin function.
 * @details This function sets the EN pin logic state.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nanobeacon_set_en_pin ( nanobeacon_t *ctx, uint8_t state );

/**
 * @brief NanoBeacon set DQ pin function.
 * @details This function sets the DQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nanobeacon_set_dq_pin ( nanobeacon_t *ctx, uint8_t state );

/**
 * @brief NanoBeacon restart device function.
 * @details This function restarts the device by toggling the EN pin.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nanobeacon_restart_device ( nanobeacon_t *ctx );

/**
 * @brief NanoBeacon send packet function.
 * @details This function sends a command data packet by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] pkt_in : Command data packet.
 * See #nanobeacon_packet_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_send_packet ( nanobeacon_t *ctx, nanobeacon_packet_t pkt_in );

/**
 * @brief NanoBeacon read packet function.
 * @details This function reads a response data packet by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[out] pkt_out : Response data packet.
 * See #nanobeacon_packet_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_read_packet ( nanobeacon_t *ctx, nanobeacon_packet_t *pkt_out );

/**
 * @brief NanoBeacon check communication function.
 * @details This function checks the communication by sending the ready request command.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_check_communication ( nanobeacon_t *ctx );

/**
 * @brief NanoBeacon write reg function.
 * @details This function writes a desired data to the selected register address.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] address : 2-byte register address.
 * @param[in] data_in : 4-byte data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_write_reg ( nanobeacon_t *ctx, uint16_t address, uint32_t data_in );

/**
 * @brief NanoBeacon read reg function.
 * @details This function reads data from the selected register address.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] address : 2-byte register address.
 * @param[out] data_out : 4-byte data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_read_reg ( nanobeacon_t *ctx, uint16_t address, uint32_t *data_out );

/**
 * @brief NanoBeacon write mem function.
 * @details This function writes a desired data to the selected memory address.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] address : 2-byte memory address.
 * @param[in] data_in : 4-byte data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_write_mem ( nanobeacon_t *ctx, uint16_t address, uint32_t data_in );

/**
 * @brief NanoBeacon read mem function.
 * @details This function reads data from the selected memory address.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] address : 2-byte memory address.
 * @param[out] data_out : 4-byte data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_read_mem ( nanobeacon_t *ctx, uint16_t address, uint32_t *data_out );

/**
 * @brief NanoBeacon write efuse function.
 * @details This function writes a desired data to the selected efuse aid.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] aid : 1-byte efuse aid.
 * @param[in] data_in : 2-byte data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_write_efuse ( nanobeacon_t *ctx, uint8_t aid, uint16_t data_in );

/**
 * @brief NanoBeacon read efuse function.
 * @details This function reads data from the selected efuse aid.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @param[in] aid : 1-byte efuse aid.
 * @param[out] data_out : 2-byte data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_read_efuse ( nanobeacon_t *ctx, uint8_t aid, uint16_t *data_out );

/**
 * @brief NanoBeacon set advertising function.
 * @details This function sets the device MAC address, interval and advertising raw data.
 * @param[in] mac_address : 6-byte device MAC address (should not be set to all zeros or ones).
 * @param[in] interval : Broadcast interval in milliseconds.
 * @param[in] adv_raw_data : Advertising raw data buffer (up to 31 bytes).
 * @param[in] len : Lenght of advertising raw data buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_set_advertising ( uint8_t *mac_address, uint16_t interval, uint8_t *adv_raw_data, uint8_t len );

/**
 * @brief NanoBeacon load adv to ram function.
 * @details This function loads advertising data to RAM.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_load_adv_to_ram ( nanobeacon_t *ctx );

/**
 * @brief NanoBeacon start advertising function.
 * @details This function starts the advertising.
 * @param[in] ctx : Click context object.
 * See #nanobeacon_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanobeacon_start_advertising ( nanobeacon_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NANOBEACON_H

/*! @} */ // nanobeacon

// ------------------------------------------------------------------------ END
