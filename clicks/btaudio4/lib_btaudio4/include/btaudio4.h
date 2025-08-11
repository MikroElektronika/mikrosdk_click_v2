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
 * @file btaudio4.h
 * @brief This file contains API for BT Audio 4 Click Driver.
 */

#ifndef BTAUDIO4_H
#define BTAUDIO4_H

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
 * @addtogroup btaudio4 BT Audio 4 Click Driver
 * @brief API for configuring and manipulating BT Audio 4 Click driver.
 * @{
 */

/**
 * @defgroup btaudio4_cmd BT Audio 4 Device Settings
 * @brief Settings for registers of BT Audio 4 Click driver.
 */

/**
 * @addtogroup btaudio4_cmd
 * @{
 */

/**
 * @brief BT Audio 4 control commands.
 * @details Specified setting for control commands of BT Audio 4 Click driver.
 */
#define BTAUDIO4_CMD_ADVERTISING           "ADVERTISING"
#define BTAUDIO4_CMD_AVRCP_META_DATA       "AVRCP_META_DATA"
#define BTAUDIO4_CMD_AT                    "AT"
#define BTAUDIO4_CMD_BATTERY_STATUS        "BATTERY_STATUS"
#define BTAUDIO4_CMD_BLE_GET_CHAR          "BLE_GET_CHAR"
#define BTAUDIO4_CMD_BCAST_REPORT          "BCAST_REPORT"
#define BTAUDIO4_CMD_BLE_GET_DES           "BLE_GET_DES"
#define BTAUDIO4_CMD_BLE_GET_SERV          "BLE_GET_SERV"
#define BTAUDIO4_CMD_BLE_INDICATION        "BLE_INDICATION"
#define BTAUDIO4_CMD_BLE_NOTIF             "BLE_NOTIF"
#define BTAUDIO4_CMD_BLE_NOTIFICATION      "BLE_NOTIFICATION"
#define BTAUDIO4_CMD_BLE_READ              "BLE_READ"
#define BTAUDIO4_CMD_BLE_READ_RES          "BLE_READ_RES"
#define BTAUDIO4_CMD_BLE_SET_DB            "BLE_SET_DB"
#define BTAUDIO4_CMD_BLE_WRITE             "BLE_WRITE"
#define BTAUDIO4_CMD_BROADCAST             "BROADCAST"
#define BTAUDIO4_CMD_BROADCODE             "BROADCODE"
#define BTAUDIO4_CMD_CALL                  "CALL"
#define BTAUDIO4_CMD_CLOSE                 "CLOSE"
#define BTAUDIO4_CMD_CONFIG                "CONFIG"
#define BTAUDIO4_CMD_CONNECTABLE           "CONNECTABLE"
#define BTAUDIO4_CMD_DISCOVERABLE          "DISCOVERABLE"
#define BTAUDIO4_CMD_ENTER_DATA_MODE       "ENTER_DATA_MODE"
#define BTAUDIO4_CMD_HELP                  "HELP"
#define BTAUDIO4_CMD_GET                   "GET"
#define BTAUDIO4_CMD_INQUIRY               "INQUIRY"
#define BTAUDIO4_CMD_LIST                  "LIST"
#define BTAUDIO4_CMD_MICBIAS               "MICBIAS"
#define BTAUDIO4_CMD_MUSIC                 "MUSIC"
#define BTAUDIO4_CMD_NAME                  "NAME"
#define BTAUDIO4_CMD_OPEN                  "OPEN"
#define BTAUDIO4_CMD_PAIR                  "PAIR"
#define BTAUDIO4_CMD_PASSKEY               "PASSKEY"
#define BTAUDIO4_CMD_PIO                   "PIO"
#define BTAUDIO4_CMD_POWER                 "POWER"
#define BTAUDIO4_CMD_RESET                 "RESET"
#define BTAUDIO4_CMD_RESTORE               "RESTORE"
#define BTAUDIO4_CMD_ROUTE                 "ROUTE"
#define BTAUDIO4_CMD_RSSI                  "RSSI"
#define BTAUDIO4_CMD_QUALITY               "QUALITY"
#define BTAUDIO4_CMD_SCAN                  "SCAN"
#define BTAUDIO4_CMD_SCAN_UNI              "SCAN_UNI"
#define BTAUDIO4_CMD_SEND                  "SEND"
#define BTAUDIO4_CMD_SEND_RAW              "SEND_RAW"
#define BTAUDIO4_CMD_SET                   "SET"
#define BTAUDIO4_CMD_SRRD                  "SRRD"
#define BTAUDIO4_CMD_STATUS                "STATUS"
#define BTAUDIO4_CMD_UNPAIR                "UNPAIR"
#define BTAUDIO4_CMD_TONES                 "TONES"
#define BTAUDIO4_CMD_VOLUME                "VOLUME"
#define BTAUDIO4_CMD_VERSION               "VERSION"
#define BTAUDIO4_CMD_WRITE                 "WRITE"

/**
 * @brief BT Audio 4 control commands parameters.
 * @details Specified setting for control commands parameters of BT Audio 4 Click driver.
 */
#define BTAUDIO4_PARAM_AUDIO                "AUDIO"
#define BTAUDIO4_PARAM_AUDIO_DIGITAL        "AUDIO_DIGITAL"
#define BTAUDIO4_PARAM_AUDIO_ANALOG         "AUDIO_ANALOG"
#define BTAUDIO4_PARAM_AUTOCONN             "AUTOCONN"
#define BTAUDIO4_PARAM_AUTO_DATA            "AUTO_DATA"
#define BTAUDIO4_PARAM_BATT_CONFIG          "BATT_CONFIG"
#define BTAUDIO4_PARAM_BCAST_CONFIG         "BCAST_CONFIG"
#define BTAUDIO4_PARAM_BLE_CONFIG           "BLE_CONFIG"
#define BTAUDIO4_PARAM_BT_CONFIG            "BT_CONFIG"
#define BTAUDIO4_PARAM_CMD_TO               "CMD_TO"
#define BTAUDIO4_PARAM_COD                  "COD"
#define BTAUDIO4_PARAM_CODEC                "CODEC"
#define BTAUDIO4_PARAM_DEEP_SLEEP           "DEEP_SLEEP"
#define BTAUDIO4_PARAM_GPIO_CONFIG          "GPIO_CONFIG"
#define BTAUDIO4_PARAM_HFP_CONFIG           "HFP_CONFIG"
#define BTAUDIO4_PARAM_LOCAL_ADDR           "LOCAL_ADDR"
#define BTAUDIO4_PARAM_NAME                 "NAME"
#define BTAUDIO4_PARAM_NAME_BCAST           "NAME_BCAST"
#define BTAUDIO4_PARAM_NAME_SHORT           "NAME_SHORT"
#define BTAUDIO4_PARAM_MUSIC_META_DATA      "MUSIC_META_DATA"
#define BTAUDIO4_PARAM_POWERMAX             "POWERMAX"
#define BTAUDIO4_PARAM_PROFILES             "PROFILES"
#define BTAUDIO4_PARAM_SSP_CAPS             "SSP_CAPS"
#define BTAUDIO4_PARAM_SPP_UUID             "SPP_UUID"
#define BTAUDIO4_PARAM_UART_CONFIG          "UART_CONFIG"
#define BTAUDIO4_PARAM_UCAST_CONFIG         "UCAST_CONFIG"
#define BTAUDIO4_PARAM_UI_CONFIG            "UI_CONFIG"
#define BTAUDIO4_PARAM_VOLUME_CONTROL       "VOLUME_CONTROL"

/**
 * @brief BT Audio 4 command notifications.
 * @details Specified setting for command notifications of BT Audio 4 Click driver.
 */
#define BTAUDIO4_NOTIF_A2DP_STREAM_START    "A2DP_STREAM_START"
#define BTAUDIO4_NOTIF_A2DP_STREAM_SUSPEND  "A2DP_STREAM_SUSPEND"
#define BTAUDIO4_NOTIF_ABS_VOL              "ABS_VOL"
#define BTAUDIO4_NOTIF_AT                   "AT"
#define BTAUDIO4_NOTIF_AVRCP_BACKWARD       "AVRCP_BACKWARD"
#define BTAUDIO4_NOTIF_AVRCP_FORWARD        "AVRCP_FORWARD"
#define BTAUDIO4_NOTIF_AVRCP_MEDIA          "AVRCP_MEDIA"
#define BTAUDIO4_NOTIF_AVRCP_PAUSE          "AVRCP_PAUSE"
#define BTAUDIO4_NOTIF_AVRCP_PLAY           "AVRCP_PLAY"
#define BTAUDIO4_NOTIF_AVRCP_STOP           "AVRCP_STOP"
#define BTAUDIO4_NOTIF_BLE_INDICATION       "BLE_INDICATION"
#define BTAUDIO4_NOTIF_BLE_NOTIFICATION     "BLE_NOTIFICATION"
#define BTAUDIO4_NOTIF_BLE_READ             "BLE_READ"
#define BTAUDIO4_NOTIF_BLE_WRITE            "BLE_WRITE"
#define BTAUDIO4_NOTIF_CALL_ACTIVE          "CALL_ACTIVE"
#define BTAUDIO4_NOTIF_CALL_DIAL            "CALL_DIAL"
#define BTAUDIO4_NOTIF_CALL_END             "CALL_END"
#define BTAUDIO4_NOTIF_CALL_INCOMING        "CALL_INCOMING"
#define BTAUDIO4_NOTIF_CALL_OUTGOING        "CALL_OUTGOING"
#define BTAUDIO4_NOTIF_CLOSE_OK             "CLOSE_OK"
#define BTAUDIO4_NOTIF_ERROR                "ERROR"
#define BTAUDIO4_NOTIF_LINK_LOSS            "LINK_LOSS"
#define BTAUDIO4_NOTIF_OPEN_OK              "OPEN_OK"
#define BTAUDIO4_NOTIF_OPEN_ERROR           "OPEN_ERROR"
#define BTAUDIO4_NOTIF_PAIR_ERROR           "PAIR_ERROR"
#define BTAUDIO4_NOTIF_PAIR_OK              "PAIR_OK"
#define BTAUDIO4_NOTIF_PAIR_PASSKEY         "PAIR_PASSKEY"
#define BTAUDIO4_NOTIF_PAIR_PENDING         "PAIR_PENDING"
#define BTAUDIO4_NOTIF_RECV                 "RECV"
#define BTAUDIO4_NOTIF_SCO_OPEN             "SCO_OPEN"
#define BTAUDIO4_NOTIF_SCO_CLOSE            "SCO_CLOSE"

/**
 * @brief BT Audio 4 device response to commands.
 * @details Device response to commands.
 */
#define BTAUDIO4_RSP_OK                     "OK"
#define BTAUDIO4_RSP_ERROR                  "ERROR"
#define BTAUDIO4_RSP_READY                  "Ready"

/**
 * @brief BT Audio 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BTAUDIO4_TX_DRV_BUFFER_SIZE         150
#define BTAUDIO4_RX_DRV_BUFFER_SIZE         1000

/*! @} */ // btaudio4_cmd

/**
 * @defgroup btaudio4_map BT Audio 4 MikroBUS Map
 * @brief MikroBUS pin mapping of BT Audio 4 Click driver.
 */

/**
 * @addtogroup btaudio4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BT Audio 4 Click to the selected MikroBUS.
 */
#define BTAUDIO4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // btaudio4_map
/*! @} */ // btaudio4

/**
 * @brief BT Audio 4 Click context object.
 * @details Context object definition of BT Audio 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< Clear to send pin (active low). */

    // Input pins
    digital_in_t rts;               /**< Request to send pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BTAUDIO4_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ BTAUDIO4_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ BTAUDIO4_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} btaudio4_t;

/**
 * @brief BT Audio 4 Click configuration object.
 * @details Configuration object definition of BT Audio 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< Clear to send pin (active low). */
    pin_name_t rts;                 /**< Request to send pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} btaudio4_cfg_t;

/**
 * @brief BT Audio 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BTAUDIO4_OK = 0,
    BTAUDIO4_ERROR = -1,
    BTAUDIO4_ERROR_TIMEOUT = -2,
    BTAUDIO4_ERROR_CMD = -3

} btaudio4_return_value_t;

/*!
 * @addtogroup btaudio4 BT Audio 4 Click Driver
 * @brief API for configuring and manipulating BT Audio 4 Click driver.
 * @{
 */

/**
 * @brief BT Audio 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #btaudio4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void btaudio4_cfg_setup ( btaudio4_cfg_t *cfg );

/**
 * @brief BT Audio 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #btaudio4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio4_init ( btaudio4_t *ctx, btaudio4_cfg_t *cfg );

/**
 * @brief BT Audio 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio4_generic_write ( btaudio4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BT Audio 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio4_generic_read ( btaudio4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BT Audio 4 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void btaudio4_set_rst_pin ( btaudio4_t *ctx, uint8_t state );

/**
 * @brief BT Audio 4 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btaudio4_reset_device ( btaudio4_t *ctx );

/**
 * @brief BT Audio 4 set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void btaudio4_set_cts_pin ( btaudio4_t *ctx, uint8_t state );

/**
 * @brief BT Audio 4 get RTS pin function.
 * @details This function returns the ready to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t btaudio4_get_rts_pin ( btaudio4_t *ctx );

/**
 * @brief BT Audio 4 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BTAUDIO4_CMD_x definitions.
 * @return None.
 * @note None.
 */
void btaudio4_cmd_run ( btaudio4_t *ctx, uint8_t *cmd );

/**
 * @brief BT Audio 4 cmd set function.
 * @details This function sets a value to a specified command parameter of the Click module.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @param[in] param : Command parameter string, see BTAUDIO4_PARAM_x definitions.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void btaudio4_cmd_set ( btaudio4_t *ctx, uint8_t *param, uint8_t *value );

/**
 * @brief BT Audio 4 cmd get function.
 * @details This function is used to get the value of a given command parameter from the Click module.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @param[in] param : Command parameter string, see BTAUDIO4_PARAM_x definitions.
 * @return None.
 * @note None.
 */
void btaudio4_cmd_get ( btaudio4_t *ctx, uint8_t *param );

#ifdef __cplusplus
}
#endif
#endif // BTAUDIO4_H

/*! @} */ // btaudio4

// ------------------------------------------------------------------------ END
