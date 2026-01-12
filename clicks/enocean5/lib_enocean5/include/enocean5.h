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
 * @file enocean5.h
 * @brief This file contains API for EnOcean 5 Click Driver.
 */

#ifndef ENOCEAN5_H
#define ENOCEAN5_H

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
 * @addtogroup enocean5 EnOcean 5 Click Driver
 * @brief API for configuring and manipulating EnOcean 5 Click driver.
 * @{
 */

/**
 * @defgroup enocean5_cmd EnOcean 5 Device Settings
 * @brief Settings of EnOcean 5 Click driver.
 */

/**
 * @addtogroup enocean5_cmd
 * @{
 */

/**
 * @brief EnOcean 5 packet sync byte.
 * @details Specified packet sync byte of EnOcean 5 Click driver.
 */
#define ENOCEAN5_PKT_SYNC_BYTE              0x55

/**
 * @brief EnOcean 5 packet type bytes.
 * @details Specified packet type bytes of EnOcean 5 Click driver.
 */
#define ENOCEAN5_PKT_TYPE_RADIO_ERP1        0x01
#define ENOCEAN5_PKT_TYPE_RESPONSE          0x02
#define ENOCEAN5_PKT_TYPE_EVENT             0x04
#define ENOCEAN5_PKT_TYPE_COMMON_CMD        0x05
#define ENOCEAN5_PKT_TYPE_REMOTE_MAN_CMD    0x07
#define ENOCEAN5_PKT_TYPE_RADIO_MESSAGE     0x09
#define ENOCEAN5_PKT_TYPE_RADIO_ERP2        0x0A

/**
 * @brief EnOcean 5 command code bytes.
 * @details Specified command code bytes of EnOcean 5 Click driver.
 */
#define ENOCEAN5_CMD_WR_SLEEP               0x01
#define ENOCEAN5_CMD_WR_RESET               0x02
#define ENOCEAN5_CMD_RD_VERSION             0x03
#define ENOCEAN5_CMD_WR_IDBASE              0x07
#define ENOCEAN5_CMD_RD_IDBASE              0x08
#define ENOCEAN5_CMD_WR_REPEATER            0x09
#define ENOCEAN5_CMD_RD_REPEATER            0x0A
#define ENOCEAN5_CMD_WR_FILTER_ADD          0x0B
#define ENOCEAN5_CMD_WR_FILTER_DEL          0x0C
#define ENOCEAN5_CMD_WR_FILTER_DEL_ALL      0x0D
#define ENOCEAN5_CMD_WR_FILTER_ENABLE       0x0E
#define ENOCEAN5_CMD_RD_FILTER              0x0F
#define ENOCEAN5_CMD_WR_WAIT_MATURITY       0x10
#define ENOCEAN5_CMD_WR_LEARNMODE           0x17
#define ENOCEAN5_CMD_RD_LEARNMODE           0x18
#define ENOCEAN5_CMD_WR_SECDEV_DEL          0x1A
#define ENOCEAN5_CMD_WR_MODE                0x1C
#define ENOCEAN5_CMD_RD_SECDEV_COUNT        0x1D
#define ENOCEAN5_CMD_RD_SECDEV_BY_ID        0x1E
#define ENOCEAN5_CMD_WR_SECDEV_SENDTECHIN   0x20
#define ENOCEAN5_CMD_RD_DUTYCYCLE_LIMIT     0x23
#define ENOCEAN5_CMD_SET_BAUDRATE           0x24
#define ENOCEAN5_CMD_GET_FREQUENCY_INFO     0x25
#define ENOCEAN5_CMD_WR_STARTUP_DELAY       0x2F
#define ENOCEAN5_CMD_SET_CRC_SIZE           0x34
#define ENOCEAN5_CMD_GET_CRC_SIZE           0x35
#define ENOCEAN5_CMD_WR_RLC_SAVE_PERIOD     0x36
#define ENOCEAN5_CMD_WR_RLC_LEGACY_MODE     0x37
#define ENOCEAN5_CMD_WR_SECDEV2_ADD         0x38
#define ENOCEAN5_CMD_WR_RSSITESTMODE        0x3A
#define ENOCEAN5_CMD_RD_RSSITESTMODE        0x3B
#define ENOCEAN5_CMD_WR_SECDEV_MAINKEY      0x3C
#define ENOCEAN5_CMD_RD_SECDEV_MAINKEY      0x3D
#define ENOCEAN5_CMD_WR_TRANSPARENT_MODE    0x3E
#define ENOCEAN5_CMD_RD_TRANSPARENT_MODE    0x3F
#define ENOCEAN5_CMD_WR_TX_ONLY_MODE        0x40
#define ENOCEAN5_CMD_RD_TX_ONLY_MODE        0x41

/**
 * @brief EnOcean 5 return code bytes.
 * @details Specified return code bytes of EnOcean 5 Click driver.
 */
#define ENOCEAN5_RET_OK                     0x00
#define ENOCEAN5_RET_ERROR                  0x01
#define ENOCEAN5_RET_NOT_SUPPORTED          0x02
#define ENOCEAN5_RET_WRONG_PARAM            0x03
#define ENOCEAN5_RET_OPERATION_DENIED       0x04
#define ENOCEAN5_RET_LOCK_SET               0x05
#define ENOCEAN5_RET_BUFFER_TOO_SMALL       0x06
#define ENOCEAN5_RET_NO_FREE_BUFFER         0x07

/**
 * @brief EnOcean 5 event code bytes.
 * @details Specified event code bytes of EnOcean 5 Click driver.
 */
#define ENOCEAN5_EVT_READY                  0x04
#define ENOCEAN5_EVT_SECUREDEVICES          0x05
#define ENOCEAN5_EVT_DUTYCYCLE_LIMIT        0x06
#define ENOCEAN5_EVT_TX_DONE                0x08
#define ENOCEAN5_EVT_LRN_MODE_DISABLED      0x09

/**
 * @brief EnOcean 5 filter setting bytes.
 * @details Specified filter setting bytes of EnOcean 5 Click driver.
 */
#define ENOCEAN5_FILTER_TYPE_SOURCE_ID      0x00
#define ENOCEAN5_FILTER_TYPE_RORG           0x01
#define ENOCEAN5_FILTER_TYPE_RSSI           0x02
#define ENOCEAN5_FILTER_TYPE_DESTINATION_ID 0x03
#define ENOCEAN5_FILTER_ACTION_FW_FALSE     0x00
#define ENOCEAN5_FILTER_ACTION_FW_TRUE      0x80
#define ENOCEAN5_FILTER_ACTION_REP_FALSE    0x40
#define ENOCEAN5_FILTER_ACTION_REP_TRUE     0xC0

/**
 * @brief EnOcean 5 wake-up cause bytes.
 * @details Specified wake-up cause bytes of EnOcean 5 Click driver.
 */
#define ENOCEAN5_WAKEUP_VOLTAGE_DROP        0x00
#define ENOCEAN5_WAKEUP_HW_RESET            0x01
#define ENOCEAN5_WAKEUP_WATCHDOG            0x02
#define ENOCEAN5_WAKEUP_FLYWHEEL            0x03
#define ENOCEAN5_WAKEUP_PARITY_ERROR        0x04
#define ENOCEAN5_WAKEUP_MEMORY_ERROR        0x05
#define ENOCEAN5_WAKEUP_INVALID_MEM_ADDR    0x06
#define ENOCEAN5_WAKEUP_HW_WAKEUP_PIN0      0x07
#define ENOCEAN5_WAKEUP_HW_WAKEUP_PIN1      0x08
#define ENOCEAN5_WAKEUP_UNKNOWN_RESET       0x09
#define ENOCEAN5_WAKEUP_UART                0x0A
#define ENOCEAN5_WAKEUP_SW_RESET            0x0B

/**
 * @brief EnOcean 5 ERP1 security level bytes.
 * @details Specified ERP1 security level bytes of EnOcean 5 Click driver.
 */
#define ENOCEAN5_ERP1_SEC_LVL_NOT_PROC      0x00
#define ENOCEAN5_ERP1_SEC_LVL_OBSOLETE      0x01
#define ENOCEAN5_ERP1_SEC_LVL_DECR          0x02
#define ENOCEAN5_ERP1_SEC_LVL_AUTH          0x03
#define ENOCEAN5_ERP1_SEC_LVL_DECR_AUTH     0x04

/**
 * @brief EnOcean 5 telegram types.
 * @details Specified telegram types of EnOcean 5 Click driver.
 */
#define ENOCEAN5_RORG_RPS                   0xF6
#define ENOCEAN5_RORG_1BS                   0xD5
#define ENOCEAN5_RORG_4BS                   0xA5
#define ENOCEAN5_RORG_VLD                   0xD2
#define ENOCEAN5_RORG_MSC                   0xD1
#define ENOCEAN5_RORG_ADT                   0xA6
#define ENOCEAN5_RORG_SM_LRN_REQ            0xC6
#define ENOCEAN5_RORG_SM_LRN_ANS            0xC7
#define ENOCEAN5_RORG_SM_REC                0xA7
#define ENOCEAN5_RORG_SYS_EX                0xC5
#define ENOCEAN5_RORG_SEC                   0x30
#define ENOCEAN5_RORG_SEC_ENCAPS            0x31
#define ENOCEAN5_RORG_SEC_MAN               0x34
#define ENOCEAN5_RORG_SIGNAL                0xD0
#define ENOCEAN5_RORG_UTE                   0xD4

/**
 * @brief EnOcean 5 device ID bytes.
 * @details Specified device ID bytes of EnOcean 5 Click driver.
 */
#define ENOCEAN5_BROADCAST_ID               ( 0xFFFFFFFFul )
#define ENOCEAN5_TX_ID                      ( 0x00000000ul )

/**
 * @brief EnOcean 5 response timeout settings.
 * @details Specified response timeout settings of EnOcean 5 Click driver.
 */
#define ENOCEAN5_RSP_TIMEOUT_1000MS         1000
#define ENOCEAN5_WAIT_TIME_1S               1
#define ENOCEAN5_WAIT_TIME_5S               5
#define ENOCEAN5_WAIT_TIME_60S              60

/**
 * @brief EnOcean 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ENOCEAN5_TX_DRV_BUFFER_SIZE         300
#define ENOCEAN5_RX_DRV_BUFFER_SIZE         300
#define ENOCEAN5_PAYLOAD_BUFFER_SIZE        256
#define ENOCEAN5_PAYLOAD_OPT_BUFFER_SIZE    10

/*! @} */ // enocean5_cmd

/**
 * @defgroup enocean5_map EnOcean 5 MikroBUS Map
 * @brief MikroBUS pin mapping of EnOcean 5 Click driver.
 */

/**
 * @addtogroup enocean5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EnOcean 5 Click to the selected MikroBUS.
 */
#define ENOCEAN5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // enocean5_map
/*! @} */ // enocean5

/**
 * @brief EnOcean 5 Click ESP3 packet structure object.
 * @details ESP3 packet structure object definition of EnOcean 5 Click driver.
 */
typedef struct
{
    uint16_t pl_len;                                            /**< Payload length. */
    uint8_t pl_opt_len;                                         /**< Payload optional length. */
    uint8_t type;                                               /**< Packet type. */
    uint8_t payload[ ENOCEAN5_PAYLOAD_BUFFER_SIZE ];            /**< Payload buffer. */
    uint8_t payload_opt[ ENOCEAN5_PAYLOAD_OPT_BUFFER_SIZE ];    /**< Payload optional buffer. */
    
} enocean5_packet_t;

/**
 * @brief EnOcean 5 Click device version object.
 * @details Device version object definition of EnOcean 5 Click driver.
 */
typedef struct
{
	uint8_t app_ver[ 4 ];           /**< Application version. */
	uint8_t app_desc[ 16 ];         /**< Application description. */
	uint8_t api_ver[ 4 ];           /**< API version. */
	uint32_t device_id;             /**< Device unique ID. */
	uint32_t device_ver;            /**< Device version (reserved for internal use). */

} enocean5_info_t;

/**
 * @brief EnOcean 5 Click context object.
 * @details Context object definition of EnOcean 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ ENOCEAN5_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ ENOCEAN5_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    enocean5_packet_t tx_pkt;       /**< TX packet structure. */
    enocean5_packet_t rx_pkt;       /**< RX packet structure. */
    enocean5_info_t info;           /**< Device information structure. */

} enocean5_t;

/**
 * @brief EnOcean 5 Click configuration object.
 * @details Configuration object definition of EnOcean 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} enocean5_cfg_t;

/**
 * @brief EnOcean 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ENOCEAN5_OK = 0,
    ENOCEAN5_ERROR = -1

} enocean5_return_value_t;

/*!
 * @addtogroup enocean5 EnOcean 5 Click Driver
 * @brief API for configuring and manipulating EnOcean 5 Click driver.
 * @{
 */

/**
 * @brief EnOcean 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #enocean5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void enocean5_cfg_setup ( enocean5_cfg_t *cfg );

/**
 * @brief EnOcean 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #enocean5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t enocean5_init ( enocean5_t *ctx, enocean5_cfg_t *cfg );

/**
 * @brief EnOcean 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t enocean5_generic_write ( enocean5_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief EnOcean 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t enocean5_generic_read ( enocean5_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief EnOcean 5 set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void enocean5_set_rst_pin ( enocean5_t *ctx, uint8_t state );

/**
 * @brief EnOcean 5 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t enocean5_reset_device ( enocean5_t *ctx );

/**
 * @brief EnOcean 5 send packet function.
 * @details This function sends TX packet from the Click context object.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @return @li @c  0 - Packet is sent,
 *         @li @c -1 - Packet error.
 * @note None.
 */
err_t enocean5_send_packet ( enocean5_t *ctx );

/**
 * @brief EnOcean 5 read packet function.
 * @details This function reads RX packet from the ring buffer and stores it in
 * the Click context object. It waits up to 1 second for a packet, and if there's no packet
 * received it returns an error.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t enocean5_read_packet ( enocean5_t *ctx );

/**
 * @brief EnOcean 5 wait packet function.
 * @details This function waits for the desired RX packet to arrive and stores it
 * in the Click context object.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @param[in] type : Expected packet type byte.
 * @param[in] cmd : Expected packet code byte.
 * @param[in] max_time_s : Maximum wait time in seconds.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error,
 *         @li @c >0 - Response error, see ENOCEAN5_RET_x macros.
 * @note None.
 */
err_t enocean5_wait_packet ( enocean5_t *ctx, uint8_t type, uint8_t cmd, uint8_t max_time_s );

/**
 * @brief EnOcean 5 clear buffers function.
 * @details This function clears the ring buffers and the RX packet object.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void enocean5_clear_buffers ( enocean5_t *ctx );

/**
 * @brief EnOcean 5 read info function.
 * @details This function reads the device information and stores it
 * in the Click context object.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @return @li @c  0 - Correct packet received,
 *         @li @c -1 - Error,
 *         @li @c >0 - Response error, see ENOCEAN5_RET_x macros.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t enocean5_read_info ( enocean5_t *ctx );

/**
 * @brief EnOcean 5 send radio message function.
 * @details This function forms and sends the radio message telegram.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @param[in] rorg : Telegram type.
 * @param[in] data_in : Data content.
 * @param[in] data_len : Number of data bytes (up to 14).
 * @return @li @c  0 - Packet is sent,
 *         @li @c -1 - Packet error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t enocean5_send_radio_message ( enocean5_t *ctx, uint8_t rorg, uint8_t *data_in, uint8_t data_len );

#ifdef __cplusplus
}
#endif
#endif // ENOCEAN5_H

/*! @} */ // enocean5

// ------------------------------------------------------------------------ END
