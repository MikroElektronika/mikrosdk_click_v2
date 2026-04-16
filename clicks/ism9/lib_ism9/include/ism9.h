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
 * @file ism9.h
 * @brief This file contains API for ISM 9 Click Driver.
 */

#ifndef ISM9_H
#define ISM9_H

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
 * @addtogroup ism9 ISM 9 Click Driver
 * @brief API for configuring and manipulating ISM 9 Click driver.
 * @{
 */

/**
 * @defgroup ism9_cmd ISM 9 Device Settings
 * @brief Settings of ISM 9 Click driver.
 */

/**
 * @addtogroup ism9_cmd
 * @{
 */

/**
 * @brief ISM 9 start byte.
 * @details Specified start byte of ISM 9 Click driver.
 */
#define ISM9_START_BYTE                             0x02

/**
 * @brief ISM 9 commands type settings.
 * @details Specified commands type settings of ISM 9 Click driver.
 */
#define ISM9_CMD_TYPE_REQ                           0x00
#define ISM9_CMD_TYPE_CNF                           0x40
#define ISM9_CMD_TYPE_IND                           0x80
#define ISM9_CMD_TYPE_MASK                          0xC0

/**
 * @brief ISM 9 commands request settings.
 * @details Specified commands request settings of ISM 9 Click driver.
 */
#define ISM9_CMD_REQ_DATA                           0x00
#define ISM9_CMD_REQ_DATAEX                         0x01
#define ISM9_CMD_REQ_SET_MODE                       0x04
#define ISM9_CMD_REQ_RESET                          0x05
#define ISM9_CMD_REQ_SET_CHANNEL                    0x06
#define ISM9_CMD_REQ_SET_DESTNETID                  0x07
#define ISM9_CMD_REQ_SET_DESTADDR                   0x08
#define ISM9_CMD_REQ_SET                            0x09
#define ISM9_CMD_REQ_GET                            0x0A
#define ISM9_CMD_REQ_RSSI                           0x0D
#define ISM9_CMD_REQ_SHUTDOWN                       0x0E
#define ISM9_CMD_REQ_STANDBY                        0x0F
#define ISM9_CMD_REQ_SET_PAPOWER                    0x11
#define ISM9_CMD_REQ_FACTORY_RESET                  0x12

/**
 * @brief ISM 9 commands confirmation settings.
 * @details Specified commands confirmation settings of ISM 9 Click driver.
 */
#define ISM9_CMD_CNF_DATA                           0x40
#define ISM9_CMD_CNF_RESET                          0x45
#define ISM9_CMD_CNF_SET_CHANNEL                    0x46
#define ISM9_CMD_CNF_SET_DESTNETID                  0x47
#define ISM9_CMD_CNF_SET_DESTADDR                   0x48
#define ISM9_CMD_CNF_SET                            0x49
#define ISM9_CMD_CNF_GET                            0x4A
#define ISM9_CMD_CNF_RSSI                           0x4D
#define ISM9_CMD_CNF_SHUTDOWN                       0x4E
#define ISM9_CMD_CNF_STANDBY                        0x4F
#define ISM9_CMD_CNF_SET_PAPOWER                    0x51
#define ISM9_CMD_CNF_FACTORY_RESET                  0x52

/**
 * @brief ISM 9 commands indication settings.
 * @details Specified commands indication settings of ISM 9 Click driver.
 */
#define ISM9_CMD_IND_REPEAT                         0x80
#define ISM9_CMD_IND_DATAEX                         0x81
#define ISM9_CMD_IND_RESET                          0x85
#define ISM9_CMD_IND_STANDBY                        0x8F
#define ISM9_CMD_IND_DUTYCYCLE                      0x90

/**
 * @brief ISM 9 user settings index list.
 * @details Specified user settings index list of ISM 9 Click driver.
 */
#define ISM9_SET_IDX_UART_BAUDRATE                  0x00
#define ISM9_SET_IDX_RADIO_DEFAULT_RF_PROFILE       0x01
#define ISM9_SET_IDX_RADIO_DEFAULT_RF_TX_POWER      0x02
#define ISM9_SET_IDX_RADIO_DEFAULT_RF_CHANNEL       0x03
#define ISM9_SET_IDX_MAC_DEFAULT_ADDRESS_MODE       0x04
#define ISM9_SET_IDX_MAC_NUM_RETRYS                 0x06
#define ISM9_SET_IDX_MAC_DEFAULT_DEST_NET_ID        0x07
#define ISM9_SET_IDX_MAC_DEFAULT_DEST_ADDR          0x08
#define ISM9_SET_IDX_MAC_SOURCE_NET_ID              0x0A
#define ISM9_SET_IDX_MAC_SOURCE_ADDR                0x0B
#define ISM9_SET_IDX_OP_MODE                        0x0E
#define ISM9_SET_IDX_CFG_FLAGS                      0x0F
#define ISM9_SET_IDX_RP_FLAGS                       0x10
#define ISM9_SET_IDX_RP_NUM_SLOTS                   0x11
#define ISM9_SET_IDX_OP_MODE_FLAGS                  0x12
#define ISM9_SET_IDX_UART_ETX_CHARACTER_0           0x13
#define ISM9_SET_IDX_UART_ETX_CHARACTER_1           0x14
#define ISM9_SET_IDX_UART_TIMEOUT                   0x15
#define ISM9_SET_IDX_LBT_OBSERVATION_PERIOD         0x1A
#define ISM9_SET_IDX_LBT_THRESHOLD                  0x1B
#define ISM9_SET_IDX_FACTORY_SETTINGS               0x20
#define ISM9_SET_IDX_FIRMWARE_VERSION               0x21

/**
 * @brief ISM 9 CNF_GET status settings.
 * @details Specified CNF_GET status settings of ISM 9 Click driver.
 */
#define ISM9_CNF_GET_STATUS_OK                      0x00
#define ISM9_CNF_GET_STATUS_FAILED                  0x01

/**
 * @brief ISM 9 CNF_DATA status settings.
 * @details Specified CNF_DATA status settings of ISM 9 Click driver.
 */
#define ISM9_CNF_DATA_STATUS_ACK                    0x00
#define ISM9_CNF_DATA_STATUS_NACK                   0x01
#define ISM9_CNF_DATA_STATUS_INVALID_CH             0x02
#define ISM9_CNF_DATA_STATUS_RADIO_CH_BUSY          0x03
#define ISM9_CNF_DATA_STATUS_MODULE_BUSY            0x04
#define ISM9_CNF_DATA_STATUS_INVALID                0xFF

/**
 * @brief ISM 9 response timeout settings.
 * @details Specified response timeout settings of ISM 9 Click driver.
 */
#define ISM9_RSP_TIMEOUT_1000MS                     1000
#define ISM9_WAIT_TIME_1S                           1
#define ISM9_WAIT_TIME_3S                           3

/**
 * @brief ISM 9 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ISM9_TX_DRV_BUFFER_SIZE                     300
#define ISM9_RX_DRV_BUFFER_SIZE                     300
#define ISM9_PAYLOAD_BUFFER_SIZE                    256

/*! @} */ // ism9_cmd

/**
 * @defgroup ism9_map ISM 9 MikroBUS Map
 * @brief MikroBUS pin mapping of ISM 9 Click driver.
 */

/**
 * @addtogroup ism9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISM 9 Click to the selected MikroBUS.
 */
#define ISM9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.mode_1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.busy = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ism9_map
/*! @} */ // ism9

/**
 * @brief ISM 9 Click command packet structure object.
 * @details Command packet structure object definition of ISM 9 Click driver.
 */
typedef struct
{
    uint8_t cmd;                                    /**< Command code. */
    uint8_t payload[ ISM9_PAYLOAD_BUFFER_SIZE ];    /**< Payload buffer. */
    uint8_t payload_len;                            /**< Payload length. */
    
} ism9_packet_t;

/**
 * @brief ISM 9 Click context object.
 * @details Context object definition of ISM 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mode_1;           /**< Mode pin, LOW -> command, HIGH -> transparent. */
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t wup;              /**< Wake-up pin (falling-edge). */

    // Input pins
    digital_in_t busy;              /**< Busy module pin (active high). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ ISM9_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ ISM9_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    ism9_packet_t cmd_pkt;          /**< Command packet structure. */
    ism9_packet_t evt_pkt;          /**< Confirmation/Indication event packet structure. */

} ism9_t;

/**
 * @brief ISM 9 Click configuration object.
 * @details Configuration object definition of ISM 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t mode_1;              /**< Mode pin, LOW -> command, HIGH -> transparent. */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t wup;                 /**< Wake-up pin (falling-edge). */
    pin_name_t busy;                /**< Busy module pin (active high). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} ism9_cfg_t;

/**
 * @brief ISM 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISM9_OK = 0,
    ISM9_ERROR = -1

} ism9_return_value_t;

/*!
 * @addtogroup ism9 ISM 9 Click Driver
 * @brief API for configuring and manipulating ISM 9 Click driver.
 * @{
 */

/**
 * @brief ISM 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ism9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ism9_cfg_setup ( ism9_cfg_t *cfg );

/**
 * @brief ISM 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ism9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism9_init ( ism9_t *ctx, ism9_cfg_t *cfg );

/**
 * @brief ISM 9 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism9_generic_write ( ism9_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ISM 9 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism9_generic_read ( ism9_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief ISM 9 set MODE_1 pin function.
 * @details This function sets the command mode (MODE_1) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ism9_set_mode_1_pin ( ism9_t *ctx, uint8_t state );

/**
 * @brief ISM 9 set WUP pin function.
 * @details This function sets the wake-up (WUP) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ism9_set_wup_pin ( ism9_t *ctx, uint8_t state );

/**
 * @brief ISM 9 set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ism9_set_rst_pin ( ism9_t *ctx, uint8_t state );

/**
 * @brief ISM 9 get BUSY pin function.
 * @details This function returns the module busy pin logic state.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ism9_get_busy_pin ( ism9_t *ctx );

/**
 * @brief ISM 9 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ism9_reset_device ( ism9_t *ctx );

/**
 * @brief ISM 9 send command function.
 * @details This function sends a desired command packet from the Click context object.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @return @li @c  0 - Packet is sent,
 *         @li @c -1 - Timeout error.
 * @note None.
 */
err_t ism9_send_cmd ( ism9_t *ctx );

/**
 * @brief ISM 9 read event function.
 * @details This function reads an event packet from the ring buffer and stores it in
 * the Click context object. It waits up to 1 second for a packet, and if there's no packet
 * received it returns an error.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism9_read_event ( ism9_t *ctx );

/**
 * @brief ISM 9 wait for event function.
 * @details This function waits for the desired event packet to arrive and stores it
 * in the Click context object.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @param[in] cmd : Expected packet command byte.
 * @param[in] max_time_s : Maximum wait time in seconds.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ism9_wait_for_event ( ism9_t *ctx, uint8_t cmd, uint8_t max_time_s );

/**
 * @brief ISM 9 clear buffers function.
 * @details This function clears the ring buffers and the event packet object.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ism9_clear_buffers ( ism9_t *ctx );

/**
 * @brief ISM 9 set user settings function.
 * @details This function writes data to a desired user settings index.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @param[in] set_idx : User settings index.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ism9_set_user_setting ( ism9_t *ctx, uint8_t set_idx, uint8_t *data_in, uint8_t len );

/**
 * @brief ISM 9 get user settings function.
 * @details This function reads data from the desired user settings index and stores it
 * in the Click context event packet object.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @param[in] set_idx : User settings index.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ism9_get_user_setting ( ism9_t *ctx, uint8_t set_idx );

#ifdef __cplusplus
}
#endif
#endif // ISM9_H

/*! @} */ // ism9

// ------------------------------------------------------------------------ END
