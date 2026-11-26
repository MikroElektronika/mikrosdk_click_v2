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
 * @file proteusii.h
 * @brief This file contains API for Proteus-II Click Driver.
 */

#ifndef PROTEUSII_H
#define PROTEUSII_H

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
 * @addtogroup proteusii Proteus-II Click Driver
 * @brief API for configuring and manipulating Proteus-II Click driver.
 * @{
 */

/**
 * @defgroup proteusii_cmd Proteus-II Device Settings
 * @brief Settings for registers of Proteus-II Click driver.
 */

/**
 * @addtogroup proteusii_cmd
 * @{
 */

/**
 * @brief Proteus-II start byte.
 * @details Specified start byte of Proteus-II Click driver.
 */
#define PROTEUSII_START_BYTE                     0x02

/**
 * @brief Proteus-II commands type settings.
 * @details Specified commands type settings of Proteus-II Click driver.
 */
#define PROTEUSII_CMD_TYPE_REQ                   0x00
#define PROTEUSII_CMD_TYPE_CNF                   0x40
#define PROTEUSII_CMD_TYPE_IND                   0x80
#define PROTEUSII_CMD_TYPE_RSP                   0xC0
#define PROTEUSII_CMD_TYPE_MASK                  0xC0

/**
 * @brief Proteus-II commands request settings.
 * @details Specified commands request settings of Proteus-II Click driver.
 */
#define PROTEUSII_CMD_REQ_RESET                  0x00
#define PROTEUSII_CMD_REQ_GET_STATE              0x01
#define PROTEUSII_CMD_REQ_SLEEP                  0x02
#define PROTEUSII_CMD_REQ_DATA                   0x04
#define PROTEUSII_CMD_REQ_CONNECT                0x06
#define PROTEUSII_CMD_REQ_DISCONNECT             0x07
#define PROTEUSII_CMD_REQ_SCAN_START             0x09
#define PROTEUSII_CMD_REQ_SCAN_STOP              0x0A
#define PROTEUSII_CMD_REQ_GET_DEVICES            0x0B
#define PROTEUSII_CMD_REQ_SET_BEACON             0x0C
#define PROTEUSII_CMD_REQ_PASSKEY                0x0D
#define PROTEUSII_CMD_REQ_DELETE_BONDS           0x0E
#define PROTEUSII_CMD_REQ_GET_BONDS              0x0F
#define PROTEUSII_CMD_REQ_GET                    0x10
#define PROTEUSII_CMD_REQ_SET                    0x11
#define PROTEUSII_CMD_REQ_PHY_UPDATE             0x1A
#define PROTEUSII_CMD_REQ_UART_DISABLE           0x1B
#define PROTEUSII_CMD_REQ_FACTORY_RESET          0x1C
#define PROTEUSII_CMD_REQ_DTM_START              0x1D
#define PROTEUSII_CMD_REQ_DTM                    0x1E
#define PROTEUSII_CMD_REQ_BOOTLOADER             0x1F

/**
 * @brief Proteus-II commands confirmation settings.
 * @details Specified commands confirmation settings of Proteus-II Click driver.
 */
#define PROTEUSII_CMD_CNF_RESET                  0x40
#define PROTEUSII_CMD_CNF_GET_STATE              0x41
#define PROTEUSII_CMD_CNF_SLEEP                  0x42
#define PROTEUSII_CMD_CNF_DATA                   0x44
#define PROTEUSII_CMD_CNF_CONNECT                0x46
#define PROTEUSII_CMD_CNF_DISCONNECT             0x47
#define PROTEUSII_CMD_CNF_SCAN_START             0x49
#define PROTEUSII_CMD_CNF_SCAN_STOP              0x4A
#define PROTEUSII_CMD_CNF_GET_DEVICES            0x4B
#define PROTEUSII_CMD_CNF_SET_BEACON             0x4C
#define PROTEUSII_CMD_CNF_PASSKEY                0x4D
#define PROTEUSII_CMD_CNF_DELETE_BONDS           0x4E
#define PROTEUSII_CMD_CNF_GET_BONDS              0x4F
#define PROTEUSII_CMD_CNF_GET                    0x50
#define PROTEUSII_CMD_CNF_SET                    0x51
#define PROTEUSII_CMD_CNF_PHY_UPDATE             0x5A
#define PROTEUSII_CMD_CNF_UART_DISABLE           0x5B
#define PROTEUSII_CMD_CNF_FACTORY_RESET          0x5C
#define PROTEUSII_CMD_CNF_DTM_START              0x5D
#define PROTEUSII_CMD_CNF_DTM                    0x5E
#define PROTEUSII_CMD_CNF_BOOTLOADER             0x5F

/**
 * @brief Proteus-II commands indication settings.
 * @details Specified commands indication settings of Proteus-II Click driver.
 */
#define PROTEUSII_CMD_IND_SLEEP                  0x82
#define PROTEUSII_CMD_IND_DATA                   0x84
#define PROTEUSII_CMD_IND_CONNECT                0x86
#define PROTEUSII_CMD_IND_DISCONNECT             0x87
#define PROTEUSII_CMD_IND_SECURITY               0x88
#define PROTEUSII_CMD_IND_RSSI                   0x8B
#define PROTEUSII_CMD_IND_BEACON                 0x8C
#define PROTEUSII_CMD_IND_PASSKEY                0x8D
#define PROTEUSII_CMD_IND_PHY_UPDATE             0x9A
#define PROTEUSII_CMD_IND_UART_ENABLE            0x9B
#define PROTEUSII_CMD_IND_ERROR                  0xA2

/**
 * @brief Proteus-II commands response settings.
 * @details Specified commands response settings of Proteus-II Click driver.
 */
#define PROTEUSII_CMD_RSP_TX_COMPLETE            0xC4
#define PROTEUSII_CMD_RSP_CHANNEL_OPEN           0xC6

/**
 * @brief Proteus-II user settings index list.
 * @details Specified user settings index list of Proteus-II Click driver.
 */
#define PROTEUSII_SET_IDX_FS_FW_VERSION          0x01
#define PROTEUSII_SET_IDX_RF_DEVICE_NAME         0x02
#define PROTEUSII_SET_IDX_FS_MAC                 0x03
#define PROTEUSII_SET_IDX_FS_BTMAC               0x04
#define PROTEUSII_SET_IDX_RF_ADV_TIMEOUT         0x07
#define PROTEUSII_SET_IDX_RF_CONN_TIMING         0x08
#define PROTEUSII_SET_IDX_RF_SCAN_TIMING         0x09
#define PROTEUSII_SET_IDX_RF_SCAN_FACTOR         0x0A
#define PROTEUSII_SET_IDX_UART_BAUD_INDEX        0x0B
#define PROTEUSII_SET_IDX_RF_SEC_FLAGS           0x0C
#define PROTEUSII_SET_IDX_RF_SCAN_FLAGS          0x0D
#define PROTEUSII_SET_IDX_RF_BEACON_FLAGS        0x0E
#define PROTEUSII_SET_IDX_FS_DEVICE_INFO         0x0F
#define PROTEUSII_SET_IDX_FS_SERIAL_NUMBER       0x10
#define PROTEUSII_SET_IDX_RF_TX_POWER            0x11
#define PROTEUSII_SET_IDX_RF_STATIC_PASSKEY      0x12
#define PROTEUSII_SET_IDX_DIS_FLAGS              0x13
#define PROTEUSII_SET_IDX_DIS_MANUF_NAME         0x14
#define PROTEUSII_SET_IDX_DIS_MODEL_NUMBER       0x15
#define PROTEUSII_SET_IDX_DIS_SERIAL_NUMBER      0x16
#define PROTEUSII_SET_IDX_DIS_HW_VERSION         0x17
#define PROTEUSII_SET_IDX_DIS_SW_VERSION         0x18
#define PROTEUSII_SET_IDX_RF_APPEARANCE          0x19
#define PROTEUSII_SET_IDX_RF_SPP_BASE_UUID       0x1A
#define PROTEUSII_SET_IDX_UART_FLAGS             0x1B
#define PROTEUSII_SET_IDX_CFG_FLAGS              0x1C
#define PROTEUSII_SET_IDX_RF_ADV_FLAGS           0x1D
#define PROTEUSII_SET_IDX_RF_SEC_PER_ONLY        0x2C

/**
 * @brief Proteus-II CNF_GET status settings.
 * @details Specified CNF_GET status settings of Proteus-II Click driver.
 */
#define PROTEUSII_CNF_GET_STATUS_OK              0x00
#define PROTEUSII_CNF_GET_STATUS_FAILED          0x01
#define PROTEUSII_CNF_GET_STATUS_NOT_PERMITTED   0xFF

/**
 * @brief Proteus-II CNF_DATA status settings.
 * @details Specified CNF_DATA status settings of Proteus-II Click driver.
 */
#define PROTEUSII_CNF_DATA_STATUS_OK             0x00
#define PROTEUSII_CNF_DATA_STATUS_FAILED         0x01
#define PROTEUSII_CNF_DATA_STATUS_NOT_PERMITTED  0xFF

/**
 * @brief Proteus-II IND_DISCONNECT reason settings.
 * @details Specified IND_DISCONNECT reason settings of Proteus-II Click driver.
 */
#define PROTEUSII_IND_DISC_REASON_TIMEOUT        0x08
#define PROTEUSII_IND_DISC_REASON_USER_TERM      0x13
#define PROTEUSII_IND_DISC_REASON_HOST_TERM      0x16
#define PROTEUSII_IND_DISC_REASON_CONN_INTERVAL  0x3B
#define PROTEUSII_IND_DISC_REASON_MIC_FAILURE    0x3D
#define PROTEUSII_IND_DISC_REASON_SETUP_FAILED   0x3E

/**
 * @brief Proteus-II IND_SECURITY status settings.
 * @details Specified IND_SECURITY status settings of Proteus-II Click driver.
 */
#define PROTEUSII_IND_SEC_STATUS_RE_BONDED       0x00
#define PROTEUSII_IND_SEC_STATUS_BONDED          0x01
#define PROTEUSII_IND_SEC_STATUS_PAIRED          0x02

/**
 * @brief Proteus-II response timeout settings.
 * @details Specified response timeout settings of Proteus-II Click driver.
 */
#define PROTEUSII_RSP_TIMEOUT_1000MS             1000
#define PROTEUSII_WAIT_TIME_1S                   1

/**
 * @brief Proteus-II driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Normal command mode only; high throughput mode is not supported.
 */
#define PROTEUSII_TX_DRV_BUFFER_SIZE             300
#define PROTEUSII_RX_DRV_BUFFER_SIZE             300
#define PROTEUSII_PAYLOAD_BUFFER_SIZE            256

/*! @} */ // proteusii_cmd

/**
 * @defgroup proteusii_map Proteus-II MikroBUS Map
 * @brief MikroBUS pin mapping of Proteus-II Click driver.
 */

/**
 * @addtogroup proteusii_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proteus-II Click to the selected MikroBUS.
 */
#define PROTEUSII_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.busy = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // proteusii_map
/*! @} */ // proteusii

/**
 * @brief Proteus-II Click command packet structure object.
 * @details Command packet structure object definition of Proteus-II Click driver.
 */
typedef struct
{
    uint8_t cmd;                                        // Command code
    uint8_t payload[ PROTEUSII_PAYLOAD_BUFFER_SIZE ];   // Payload buffer
    uint8_t payload_len;                                // Payload length

} proteusii_packet_t;

/**
 * @brief Proteus-II Click context object.
 * @details Context object definition of Proteus-II Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< Module CTS pin (active low). */
    digital_out_t wup;              /**< Wake-up pin (active low). */

    // Input pins
    digital_in_t busy;              /**< Module BUSY pin. */
    digital_in_t rts;               /**< Module RTS pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ PROTEUSII_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ PROTEUSII_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    proteusii_packet_t cmd_pkt;     /**< Command packet structure. */
    proteusii_packet_t evt_pkt;     /**< Confirmation/Indication/Response event packet structure. */

} proteusii_t;

/**
 * @brief Proteus-II Click configuration object.
 * @details Configuration object definition of Proteus-II Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t busy;                /**< Module BUSY pin. */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< Module CTS pin (active low). */
    pin_name_t wup;                 /**< Wake-up pin (active low). */
    pin_name_t rts;                 /**< Module RTS pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} proteusii_cfg_t;

/**
 * @brief Proteus-II Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROTEUSII_OK = 0,
    PROTEUSII_ERROR = -1

} proteusii_return_value_t;

/*!
 * @addtogroup proteusii Proteus-II Click Driver
 * @brief API for configuring and manipulating Proteus-II Click driver.
 * @{
 */

/**
 * @brief Proteus-II configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proteusii_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proteusii_cfg_setup ( proteusii_cfg_t *cfg );

/**
 * @brief Proteus-II initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proteusii_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proteusii_init ( proteusii_t *ctx, proteusii_cfg_t *cfg );

/**
 * @brief Proteus-II data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proteusii_generic_write ( proteusii_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Proteus-II data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proteusii_generic_read ( proteusii_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Proteus-II set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void proteusii_set_rst_pin ( proteusii_t *ctx, uint8_t state );

/**
 * @brief Proteus-II set CTS pin function.
 * @details This function sets the module CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note CTS is active low. The CS pin is connected to CTS when RST is high.
 */
void proteusii_set_cts_pin ( proteusii_t *ctx, uint8_t state );

/**
 * @brief Proteus-II get BUSY pin function.
 * @details This function reads the module BUSY pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return @li @c 0 - Pin low,
 *         @li @c 1 - Pin high.
 * @note BUSY is only relevant in transparent mode; ignore it in command mode.
 */
uint8_t proteusii_get_busy_pin ( proteusii_t *ctx );

/**
 * @brief Proteus-II get RTS pin function.
 * @details This function reads the module RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return @li @c 0 - Pin low,
 *         @li @c 1 - Pin high.
 * @note RTS is active low and is meaningful only when UART flow control is enabled.
 */
uint8_t proteusii_get_rts_pin ( proteusii_t *ctx );

/**
 * @brief Proteus-II reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note RST also controls the ClickID mux. Readiness is confirmed by GET_STATE_CNF.
 */
err_t proteusii_reset_device ( proteusii_t *ctx );

/**
 * @brief Proteus-II set WUP pin function.
 * @details This function sets the wake-up pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void proteusii_set_wup_pin ( proteusii_t *ctx, uint8_t state );

/**
 * @brief Proteus-II wake-up function.
 * @details This function leaves sleep or re-enables UART by toggling the wake-up pin.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return None.
 * @note Read GET_STATE_CNF after sleep or UART_ENABLE_IND after UART disable.
 */
void proteusii_wake_up ( proteusii_t *ctx );

/**
 * @brief Proteus-II send command function.
 * @details This function sends a desired command packet from the Click context object.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return None.
 * @note Pending receive bytes are preserved. Wait for the command confirmation
 * before sending another request.
 */
void proteusii_send_cmd ( proteusii_t *ctx );

/**
 * @brief Proteus-II read event function.
 * @details This function reads an event packet from the ring buffer and stores it in
 * the Click context object. It waits up to 1 second for a packet, and if there's no packet
 * received it returns an error.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Requires non-blocking UART. Payloads above 255 bytes are not supported.
 */
err_t proteusii_read_event ( proteusii_t *ctx );

/**
 * @brief Proteus-II wait for event function.
 * @details This function waits for the desired event packet to arrive and stores it
 * in the Click context object.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @param[in] cmd : Expected packet command byte.
 * @param[in] max_time_s : Maximum wait time in seconds.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note Reads up to max_time_s event packets; unrelated events are discarded.
 */
err_t proteusii_wait_for_event ( proteusii_t *ctx, uint8_t cmd, uint8_t max_time_s );

/**
 * @brief Proteus-II clear buffers function.
 * @details This function clears the ring buffers and the event packet object.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proteusii_clear_buffers ( proteusii_t *ctx );

/**
 * @brief Proteus-II set user settings function.
 * @details This function writes data to a desired user settings index.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @param[in] set_idx : User settings index.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note Settings are stored in flash and take effect after reset. Compare the
 * current value before writing to avoid unnecessary flash wear. The setting data
 * must fit in 254 bytes, leaving one byte for its index.
 */
err_t proteusii_set_user_setting ( proteusii_t *ctx, uint8_t set_idx, uint8_t *data_in, uint8_t len );

/**
 * @brief Proteus-II get user settings function.
 * @details This function reads data from the desired user settings index and stores it
 * in the Click context event packet object.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @param[in] set_idx : User settings index.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proteusii_get_user_setting ( proteusii_t *ctx, uint8_t set_idx );

#ifdef __cplusplus
}
#endif
#endif // PROTEUSII_H

/*! @} */ // proteusii

// ------------------------------------------------------------------------ END
