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
 * @file proteuse.h
 * @brief This file contains API for Proteus-e Click Driver.
 */

#ifndef PROTEUSE_H
#define PROTEUSE_H

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
 * @addtogroup proteuse Proteus-e Click Driver
 * @brief API for configuring and manipulating Proteus-e Click driver.
 * @{
 */

/**
 * @defgroup proteuse_cmd Proteus-e Device Settings
 * @brief Settings for registers of Proteus-e Click driver.
 */

/**
 * @addtogroup proteuse_cmd
 * @{
 */

/**
 * @brief Proteus-e start byte.
 * @details Specified start byte of Proteus-e Click driver.
 */
#define PROTEUSE_START_BYTE                     0x02

/**
 * @brief Proteus-e commands type settings.
 * @details Specified commands type settings of Proteus-e Click driver.
 */
#define PROTEUSE_CMD_TYPE_REQ                   0x00
#define PROTEUSE_CMD_TYPE_CNF                   0x40
#define PROTEUSE_CMD_TYPE_IND                   0x80
#define PROTEUSE_CMD_TYPE_RSP                   0xC0
#define PROTEUSE_CMD_TYPE_MASK                  0xC0

/**
 * @brief Proteus-e commands request settings.
 * @details Specified commands request settings of Proteus-e Click driver.
 */
#define PROTEUSE_CMD_REQ_RESET                  0x00
#define PROTEUSE_CMD_REQ_GET_STATE              0x01
#define PROTEUSE_CMD_REQ_SLEEP                  0x02
#define PROTEUSE_CMD_REQ_DATA                   0x04
#define PROTEUSE_CMD_REQ_DISCONNECT             0x07
#define PROTEUSE_CMD_REQ_DELETE_BONDS           0x0E
#define PROTEUSE_CMD_REQ_GET_BONDS              0x0F
#define PROTEUSE_CMD_REQ_GET                    0x10
#define PROTEUSE_CMD_REQ_SET                    0x11
#define PROTEUSE_CMD_REQ_PHY_UPDATE             0x1A
#define PROTEUSE_CMD_REQ_UART_DISABLE           0x1B
#define PROTEUSE_CMD_REQ_FACTORY_RESET          0x1C
#define PROTEUSE_CMD_REQ_DTM_START              0x1D
#define PROTEUSE_CMD_REQ_DTM                    0x1E
#define PROTEUSE_CMD_REQ_GET_RAM                0x20
#define PROTEUSE_CMD_REQ_SET_RAM                0x21
#define PROTEUSE_CMD_REQ_GPIO_LOCAL_WRITE_CFG   0x25
#define PROTEUSE_CMD_REQ_GPIO_LOCAL_WRITE       0x26
#define PROTEUSE_CMD_REQ_GPIO_LOCAL_READ        0x27
#define PROTEUSE_CMD_REQ_GPIO_REMOTE_WRITE_CFG  0x28
#define PROTEUSE_CMD_REQ_GPIO_REMOTE_WRITE      0x29
#define PROTEUSE_CMD_REQ_GPIO_REMOTE_READ       0x2A
#define PROTEUSE_CMD_REQ_GPIO_LOCAL_READ_CFG    0x2B
#define PROTEUSE_CMD_REQ_GPIO_REMOTE_READ_CFG   0x2C
#define PROTEUSE_CMD_REQ_ALLOW_UNBONDED_CONN    0x2D

/**
 * @brief Proteus-e commands confirmation settings.
 * @details Specified commands confirmation settings of Proteus-e Click driver.
 */
#define PROTEUSE_CMD_CNF_RESET                  0x40
#define PROTEUSE_CMD_CNF_GET_STATE              0x41
#define PROTEUSE_CMD_CNF_SLEEP                  0x42
#define PROTEUSE_CMD_CNF_DATA                   0x44
#define PROTEUSE_CMD_CNF_DISCONNECT             0x47
#define PROTEUSE_CMD_CNF_DELETE_BONDS           0x4E
#define PROTEUSE_CMD_CNF_GET_BONDS              0x4F
#define PROTEUSE_CMD_CNF_GET                    0x50
#define PROTEUSE_CMD_CNF_SET                    0x51
#define PROTEUSE_CMD_CNF_PHY_UPDATE             0x5A
#define PROTEUSE_CMD_CNF_UART_DISABLE           0x5B
#define PROTEUSE_CMD_CNF_FACTORY_RESET          0x5C
#define PROTEUSE_CMD_CNF_DTM_START              0x5D
#define PROTEUSE_CMD_CNF_DTM                    0x5E
#define PROTEUSE_CMD_CNF_GET_RAM                0x60
#define PROTEUSE_CMD_CNF_SET_RAM                0x61
#define PROTEUSE_CMD_CNF_GPIO_LOCAL_WRITE_CFG   0x65
#define PROTEUSE_CMD_CNF_GPIO_LOCAL_WRITE       0x66
#define PROTEUSE_CMD_CNF_GPIO_LOCAL_READ        0x67
#define PROTEUSE_CMD_CNF_GPIO_REMOTE_WRITE_CFG  0x68
#define PROTEUSE_CMD_CNF_GPIO_REMOTE_WRITE      0x69
#define PROTEUSE_CMD_CNF_GPIO_REMOTE_READ       0x6A
#define PROTEUSE_CMD_CNF_GPIO_LOCAL_READ_CFG    0x6B
#define PROTEUSE_CMD_CNF_GPIO_REMOTE_READ_CFG   0x6C
#define PROTEUSE_CMD_CNF_ALLOW_UNBONDED_CONN    0x6D

/**
 * @brief Proteus-e commands indication settings.
 * @details Specified commands indication settings of Proteus-e Click driver.
 */
#define PROTEUSE_CMD_IND_SLEEP                  0x82
#define PROTEUSE_CMD_IND_DATA                   0x84
#define PROTEUSE_CMD_IND_CONNECT                0x86
#define PROTEUSE_CMD_IND_DISCONNECT             0x87
#define PROTEUSE_CMD_IND_SECURITY               0x88
#define PROTEUSE_CMD_IND_PHY_UPDATE             0x9A
#define PROTEUSE_CMD_IND_UART_ENABLE            0x9B
#define PROTEUSE_CMD_IND_ERROR                  0xA2
#define PROTEUSE_CMD_IND_GPIO_LOCAL_WRITE       0xA6
#define PROTEUSE_CMD_IND_GPIO_REMOTE_WRITE_CFG  0xA8
#define PROTEUSE_CMD_IND_GPIO_REMOTE_WRITE      0xA9

/**
 * @brief Proteus-e commands response settings.
 * @details Specified commands response settings of Proteus-e Click driver.
 */
#define PROTEUSE_CMD_RSP_TX_COMPLETE            0xC4
#define PROTEUSE_CMD_RSP_CHANNEL_OPEN           0xC6

/**
 * @brief Proteus-e user settings index list.
 * @details Specified user settings index list of Proteus-e Click driver.
 */
#define PROTEUSE_SET_IDX_FS_FW_VERSION          0x01
#define PROTEUSE_SET_IDX_RF_DEVICE_NAME         0x02
#define PROTEUSE_SET_IDX_FS_MAC                 0x03
#define PROTEUSE_SET_IDX_FS_BTMAC               0x04
#define PROTEUSE_SET_IDX_UART_TRANSP_ETX        0x05
#define PROTEUSE_SET_IDX_UART_TRANSP_ETX_CFG    0x06
#define PROTEUSE_SET_IDX_RF_ADV_TIMEOUT         0x07
#define PROTEUSE_SET_IDX_RF_CONN_INTERVAL       0x08
#define PROTEUSE_SET_IDX_RF_ADV_INTERVAL        0x09
#define PROTEUSE_SET_IDX_UART_CFG_INDEX         0x0B
#define PROTEUSE_SET_IDX_RF_SEC_FLAGS           0x0C
#define PROTEUSE_SET_IDX_RF_ADV_DATA            0x0D
#define PROTEUSE_SET_IDX_RF_SCAN_RSP_DATA       0x0E
#define PROTEUSE_SET_IDX_FS_DEVICE_INFO         0x0F
#define PROTEUSE_SET_IDX_FS_SERIAL_NUMBER       0x10
#define PROTEUSE_SET_IDX_RF_TX_POWER            0x11
#define PROTEUSE_SET_IDX_RF_STATIC_PASSKEY      0x12
#define PROTEUSE_SET_IDX_RF_APPEARANCE          0x19
#define PROTEUSE_SET_IDX_RF_SPP_BASE_UUID       0x1A
#define PROTEUSE_SET_IDX_RF_CFG_FLAGS           0x1C
#define PROTEUSE_SET_IDX_RF_SPP_SERVICE_UUID    0x20
#define PROTEUSE_SET_IDX_RF_SPP_RX_UUID         0x21
#define PROTEUSE_SET_IDX_RF_SPP_TX_UUID         0x22
#define PROTEUSE_SET_IDX_UART_TRANSP_TIMEOUT    0x24
#define PROTEUSE_SET_IDX_UART_TRANSP_MAX_PL     0x25

/**
 * @brief Proteus-e CNF_GET status settings.
 * @details Specified CNF_GET status settings of Proteus-e Click driver.
 */
#define PROTEUSE_CNF_GET_STATUS_OK              0x00
#define PROTEUSE_CNF_GET_STATUS_FAILED          0x01
#define PROTEUSE_CNF_GET_STATUS_NOT_PERMITTED   0xFF

/**
 * @brief Proteus-e CNF_DATA status settings.
 * @details Specified CNF_DATA status settings of Proteus-e Click driver.
 */
#define PROTEUSE_CNF_DATA_STATUS_OK             0x00
#define PROTEUSE_CNF_DATA_STATUS_FAILED         0x01
#define PROTEUSE_CNF_DATA_STATUS_NOT_PERMITTED  0xFF

/**
 * @brief Proteus-e IND_DISCONNECT reason settings.
 * @details Specified IND_DISCONNECT reason settings of Proteus-e Click driver.
 */
#define PROTEUSE_IND_DISC_REASON_TIMEOUT        0x08
#define PROTEUSE_IND_DISC_REASON_USER_TERM      0x13
#define PROTEUSE_IND_DISC_REASON_HOST_TERM      0x16
#define PROTEUSE_IND_DISC_REASON_CONN_INTERVAL  0x3B
#define PROTEUSE_IND_DISC_REASON_MIC_FAILURE    0x3D
#define PROTEUSE_IND_DISC_REASON_SETUP_FAILED   0x3E

/**
 * @brief Proteus-e IND_SECURITY status settings.
 * @details Specified IND_SECURITY status settings of Proteus-e Click driver.
 */
#define PROTEUSE_IND_SEC_STATUS_RE_BONDED       0x00
#define PROTEUSE_IND_SEC_STATUS_BONDED          0x01
#define PROTEUSE_IND_SEC_STATUS_PAIRED          0x02

/**
 * @brief Proteus-e response timeout settings.
 * @details Specified response timeout settings of Proteus-e Click driver.
 */
#define PROTEUSE_RSP_TIMEOUT_1000MS             1000
#define PROTEUSE_WAIT_TIME_1S                   1

/**
 * @brief Proteus-e driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define PROTEUSE_TX_DRV_BUFFER_SIZE             300
#define PROTEUSE_RX_DRV_BUFFER_SIZE             300
#define PROTEUSE_PAYLOAD_BUFFER_SIZE            256

/*! @} */ // proteuse_cmd

/**
 * @defgroup proteuse_map Proteus-e MikroBUS Map
 * @brief MikroBUS pin mapping of Proteus-e Click driver.
 */

/**
 * @addtogroup proteuse_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proteus-e Click to the selected MikroBUS.
 */
#define PROTEUSE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // proteuse_map
/*! @} */ // proteuse

/**
 * @brief Proteus-e Click command packet structure object.
 * @details Command packet structure object definition of Proteus-e Click driver.
 */
typedef struct
{
    uint8_t cmd;                                        // Command code
    uint8_t payload[ PROTEUSE_PAYLOAD_BUFFER_SIZE ];    // Payload buffer
    uint8_t payload_len;                                // Payload length
    
} proteuse_packet_t;

/**
 * @brief Proteus-e Click context object.
 * @details Context object definition of Proteus-e Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;               /**< UART enable pin (active high). */
    digital_out_t rst;              /**< Reset pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ PROTEUSE_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ PROTEUSE_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    proteuse_packet_t cmd_pkt;      // Command packet structure
    proteuse_packet_t evt_pkt;      // Confirmation/Indication/Response event packet structure

} proteuse_t;

/**
 * @brief Proteus-e Click configuration object.
 * @details Configuration object definition of Proteus-e Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t en;                  /**< UART enable pin (active high). */
    pin_name_t rst;                 /**< Reset pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} proteuse_cfg_t;

/**
 * @brief Proteus-e Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PROTEUSE_OK = 0,
    PROTEUSE_ERROR = -1

} proteuse_return_value_t;

/*!
 * @addtogroup proteuse Proteus-e Click Driver
 * @brief API for configuring and manipulating Proteus-e Click driver.
 * @{
 */

/**
 * @brief Proteus-e configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proteuse_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proteuse_cfg_setup ( proteuse_cfg_t *cfg );

/**
 * @brief Proteus-e initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proteuse_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proteuse_init ( proteuse_t *ctx, proteuse_cfg_t *cfg );

/**
 * @brief Proteus-e default configuration function.
 * @details This function executes a default configuration of Proteus-e
 * Click board.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proteuse_default_cfg ( proteuse_t *ctx );

/**
 * @brief Proteus-e data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proteuse_generic_write ( proteuse_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Proteus-e data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proteuse_generic_read ( proteuse_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Proteus-e set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void proteuse_set_rst_pin ( proteuse_t *ctx, uint8_t state );

/**
 * @brief Proteus-e reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proteuse_reset_device ( proteuse_t *ctx );

/**
 * @brief Proteus-e set EN pin function.
 * @details This function sets the uart enable pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void proteuse_set_en_pin ( proteuse_t *ctx, uint8_t state );

/**
 * @brief Proteus-e enable uart function.
 * @details This function enables uart by toggling the uart enable pin logic state.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proteuse_enable_uart ( proteuse_t *ctx );

/**
 * @brief Proteus-e send command function.
 * @details This function sends a desired command packet from the Click context object.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proteuse_send_cmd ( proteuse_t *ctx );

/**
 * @brief Proteus-e read event function.
 * @details This function reads an event packet from the ring buffer and stores it in
 * the Click context object. It waits up to 1 second for a packet, and if there's no packet
 * received it returns an error.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t proteuse_read_event ( proteuse_t *ctx );

/**
 * @brief Proteus-e wait for event function.
 * @details This function waits for the desired event packet to arrive and stores it
 * in the Click context object.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @param[in] cmd : Expected packet command byte.
 * @param[in] max_time_s : Maximum wait time in seconds.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proteuse_wait_for_event ( proteuse_t *ctx, uint8_t cmd, uint8_t max_time_s );

/**
 * @brief Proteus-e clear buffers function.
 * @details This function clears the ring buffers and the event packet object.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void proteuse_clear_buffers ( proteuse_t *ctx );

/**
 * @brief Proteus-e set user settings function.
 * @details This function writes data to a desired user settings index.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @param[in] set_idx : User settings index.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proteuse_set_user_setting ( proteuse_t *ctx, uint8_t set_idx, uint8_t *data_in, uint8_t len );

/**
 * @brief Proteus-e get user settings function.
 * @details This function reads data from the desired user settings index and stores it
 * in the Click context event packet object.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @param[in] set_idx : User settings index.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t proteuse_get_user_setting ( proteuse_t *ctx, uint8_t set_idx );

#ifdef __cplusplus
}
#endif
#endif // PROTEUSE_H

/*! @} */ // proteuse

// ------------------------------------------------------------------------ END
