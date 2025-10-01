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
 * @file bgm113.h
 * @brief This file contains API for BGM113 Click Driver.
 */

#ifndef BGM113_H
#define BGM113_H

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
 * @addtogroup bgm113 BGM113 Click Driver
 * @brief API for configuring and manipulating BGM113 Click driver.
 * @{
 */

/**
 * @defgroup bgm113_cmd BGM113 Device Settings
 * @brief Settings for registers of BGM113 Click driver.
 */

/**
 * @addtogroup bgm113_cmd
 * @{
 */

/**
 * @brief BGM113 message type setting.
 * @details Specified settings for message type of BGM113 Click driver.
 */
#define BGM113_MSG_TYPE_COMMAND                 0x20
#define BGM113_MSG_TYPE_RESPONSE                0x20
#define BGM113_MSG_TYPE_EVENT                   0xA0

/**
 * @brief BGM113 message class setting.
 * @details Specified settings for message class of BGM113 Click driver.
 */
#define BGM113_MSG_CLASS_DFU                    0x00
#define BGM113_MSG_CLASS_SYSTEM                 0x01
#define BGM113_MSG_CLASS_LE_GAP                 0x03
#define BGM113_MSG_CLASS_LE_CONNECTION          0x08
#define BGM113_MSG_CLASS_GATT                   0x09
#define BGM113_MSG_CLASS_GATT_SERVER            0x0A
#define BGM113_MSG_CLASS_ENDPOINT               0x0B
#define BGM113_MSG_CLASS_HARDWARE               0x0C
#define BGM113_MSG_CLASS_FLASH_PS               0x0D
#define BGM113_MSG_CLASS_TEST                   0x0E
#define BGM113_MSG_CLASS_SM                     0x0F
#define BGM113_MSG_CLASS_UTIL                   0x11

/**
 * @brief BGM113 message ID setting.
 * @details Specified settings for message ID of BGM113 Click driver.
 * @note Refer to the Bluetooth Smart Software API Reference Manual Rev. 1.3 for more message IDs.
 */
#define BGM113_MSG_ID_SYSTEM_HELLO              0x00
#define BGM113_MSG_ID_SYSTEM_RESET              0x01
#define BGM113_MSG_ID_SYSTEM_GET_BT_ADDRESS     0x03
#define BGM113_MSG_ID_SYSTEM_SET_TX_POWER       0x0A
#define BGM113_MSG_ID_SYSTEM_GET_RANDOM_DATA    0x0B
#define BGM113_MSG_ID_SM_SET_BONDABLE_MODE      0x00
#define BGM113_MSG_ID_SM_DELETE_BONDINGS        0x07
#define BGM113_MSG_ID_LE_GAP_SET_MODE           0x01
#define BGM113_MSG_ID_ENDPOINT_SEND             0x00
#define BGM113_MSG_ID_EVT_DFU_BOOT              0x00
#define BGM113_MSG_ID_EVT_SYSTEM_BOOT           0x00
#define BGM113_MSG_ID_EVT_SYSTEM_EXT_SIGNAL     0x03
#define BGM113_MSG_ID_EVT_SYSTEM_AWAKE          0x04
#define BGM113_MSG_ID_EVT_SYSTEM_HW_ERROR       0x05
#define BGM113_MSG_ID_EVT_GATT_MTU_EXCHANGED    0x00
#define BGM113_MSG_ID_EVT_SM_BONDED             0x03
#define BGM113_MSG_ID_EVT_SM_BONDING_FAILED     0x04
#define BGM113_MSG_ID_EVT_ENDPOINT_DATA         0x01
#define BGM113_MSG_ID_EVT_LE_CONNECTION_OPENED  0x00
#define BGM113_MSG_ID_EVT_LE_CONNECTION_CLOSED  0x01
#define BGM113_MSG_ID_EVT_LE_CONNECTION_PARAMS  0x02

/**
 * @brief BGM113 reset mode setting.
 * @details Specified settings for reset mode of BGM113 Click driver.
 */
#define BGM113_SYSTEM_RESET_NORMAL              0x00
#define BGM113_SYSTEM_RESET_BOOT_TO_DFU         0x01

/**
 * @brief BGM113 bondable mode setting.
 * @details Specified settings for bondable mode of BGM113 Click driver.
 */
#define BGM113_SM_SET_BONDABLE_NOT_ACCEPTED     0x00
#define BGM113_SM_SET_BONDABLE_ALLOWED          0x01

/**
 * @brief BGM113 LE gap mode setting.
 * @details Specified settings for LE gap mode of BGM113 Click driver.
 */
#define BGM113_LE_GAP_NON_CONNECTABLE           0x00
#define BGM113_LE_GAP_DIRECTED_CONNECTABLE      0x01
#define BGM113_LE_GAP_UNDIRECTED_CONNECTABLE    0x02
#define BGM113_LE_GAP_SCANNABLE_NON_CONNECTABLE 0x03
#define BGM113_LE_GAP_NON_DISCOVERABLE          0x00
#define BGM113_LE_GAP_LIMITED_DISCOVERABLE      0x01
#define BGM113_LE_GAP_GENERAL_DISCOVERABLE      0x02
#define BGM113_LE_GAP_BROADCAST                 0x03
#define BGM113_LE_GAP_USER_DATA                 0x04

/**
 * @brief BGM113 response timeout settings.
 * @details Specified response timeout settings of BGM113 Click driver.
 */
#define BGM113_RSP_TIMEOUT_1000MS               1000
#define BGM113_WAIT_TIME_1S                     1
#define BGM113_WAIT_TIME_5S                     5

/**
 * @brief BGM113 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BGM113_TX_DRV_BUFFER_SIZE               256
#define BGM113_RX_DRV_BUFFER_SIZE               256
#define BGM113_MAX_PAYLOAD_LEN                  64

/*! @} */ // bgm113_cmd

/**
 * @defgroup bgm113_map BGM113 MikroBUS Map
 * @brief MikroBUS pin mapping of BGM113 Click driver.
 */

/**
 * @addtogroup bgm113_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BGM113 Click to the selected MikroBUS.
 */
#define BGM113_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // bgm113_map
/*! @} */ // bgm113

/**
 * @brief BGM113 Click packet structure object.
 * @details Packet structure object definition of BGM113 Click driver.
 */
typedef struct
{
    uint8_t msg_type;               /**< Message type (Command/Response/Event). */
    uint8_t payload_len;            /**< Payload length (up to BGM113_MAX_PAYLOAD_LEN). */
    uint8_t msg_class;              /**< Message class. */
    uint8_t msg_id;                 /**< Message ID. */
    uint8_t payload[ BGM113_MAX_PAYLOAD_LEN ];  /**< Payload buffer. */

} bgm113_packet_t;

/**
 * @brief BGM113 Click context object.
 * @details Context object definition of BGM113 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< Clear to send pin. */

    // Input pins
    digital_in_t rts;               /**< Request to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BGM113_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ BGM113_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    bgm113_packet_t cmd_pkt;        // Command packet structure
    bgm113_packet_t rsp_pkt;        // Response/Event packet structure

} bgm113_t;

/**
 * @brief BGM113 Click configuration object.
 * @details Configuration object definition of BGM113 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< Clear to send pin. */
    pin_name_t rts;                 /**< Request to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} bgm113_cfg_t;

/**
 * @brief BGM113 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BGM113_OK = 0,
    BGM113_ERROR = -1

} bgm113_return_value_t;

/*!
 * @addtogroup bgm113 BGM113 Click Driver
 * @brief API for configuring and manipulating BGM113 Click driver.
 * @{
 */

/**
 * @brief BGM113 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bgm113_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bgm113_cfg_setup ( bgm113_cfg_t *cfg );

/**
 * @brief BGM113 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bgm113_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_init ( bgm113_t *ctx, bgm113_cfg_t *cfg );

/**
 * @brief BGM113 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_generic_write ( bgm113_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BGM113 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_generic_read ( bgm113_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BGM113 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bgm113_set_rst_pin ( bgm113_t *ctx, uint8_t state );

/**
 * @brief BGM113 set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bgm113_set_cts_pin ( bgm113_t *ctx, uint8_t state );

/**
 * @brief BGM113 get RTS pin function.
 * @details This function returns the request to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t bgm113_get_rts_pin ( bgm113_t *ctx );

/**
 * @brief BGM113 send packet function.
 * @details This function sends a desired command packet from the Click context object.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bgm113_send_packet ( bgm113_t *ctx );

/**
 * @brief BGM113 read packet function.
 * @details This function reads an event or response packet from the ring buffer and stores it in
 * the Click context object. It waits up to 1 second for a packet, and if there's no packet
 * received it returns an error.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_read_packet ( bgm113_t *ctx );

/**
 * @brief BGM113 wait packet function.
 * @details This function waits for the desired event or response packet to arrive and stores it
 * in the Click context object.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @param[in] msg_type : Message type (Event/Response).
 * @param[in] msg_class : Message class.
 * @param[in] msg_id : Message ID.
 * @param[in] max_time_s : Maximum wait time in seconds.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bgm113_wait_packet ( bgm113_t *ctx, uint8_t msg_type, uint8_t msg_class, uint8_t msg_id, uint8_t max_time_s );

/**
 * @brief BGM113 clear buffers function.
 * @details This function clears the ring buffers and the response packet object.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bgm113_clear_buffers ( bgm113_t *ctx );

/**
 * @brief BGM113 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bgm113_reset_device ( bgm113_t *ctx );

/**
 * @brief BGM113 check communication function.
 * @details This function verify whether the communication between the host and the device is functional.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_check_communication ( bgm113_t *ctx );

/**
 * @brief BGM113 get BT address function.
 * @details This function reads the BT public address used by the device.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_get_bt_address ( bgm113_t *ctx );

/**
 * @brief BGM113 set bondable mode function.
 * @details This function sets the bondable mode of the device.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @param[in] mode : @li @c  0 - Not accepted,
 *                   @li @c  1 - Allowed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_set_bondable_mode ( bgm113_t *ctx, uint8_t mode );

/**
 * @brief BGM113 delete bondings function.
 * @details This function deletes all bondings.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_delete_bondings ( bgm113_t *ctx );

/**
 * @brief BGM113 set gap mode function.
 * @details This function configures the current BT LE GAP Connectable and Discoverable modes.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @param[in] connectable : @li @c  0 - Non-connectable,
 *                          @li @c  1 - Directed connectable (RESERVED),
 *                          @li @c  2 - Undirected connectable,
 *                          @li @c  3 - Scannable non-connectable.
 * @param[in] discoverable : @li @c  0 - Non-discoverable,
 *                           @li @c  1 - Limited discoverable,
 *                           @li @c  2 - General discoverable,
 *                           @li @c  3 - Broadcast,
 *                           @li @c  4 - User data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_set_gap_mode ( bgm113_t *ctx, uint8_t connectable, uint8_t discoverable );

/**
 * @brief BGM113 system reset function.
 * @details This function resets the device.
 * @param[in] ctx : Click context object.
 * See #bgm113_t object definition for detailed explanation.
 * @param[in] mode : @li @c  0 - Normal reset,
 *                   @li @c  1 - Boot to DFU.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bgm113_system_reset ( bgm113_t *ctx, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // BGM113_H

/*! @} */ // bgm113

// ------------------------------------------------------------------------ END
