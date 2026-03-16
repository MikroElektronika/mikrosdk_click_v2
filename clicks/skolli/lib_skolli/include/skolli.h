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
 * @file skolli.h
 * @brief This file contains API for Skoll-I Click Driver.
 */

#ifndef SKOLLI_H
#define SKOLLI_H

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
 * @addtogroup skolli Skoll-I Click Driver
 * @brief API for configuring and manipulating Skoll-I Click driver.
 * @{
 */

/**
 * @defgroup skolli_cmd Skoll-I Device Settings
 * @brief Settings of Skoll-I Click driver.
 */

/**
 * @addtogroup skolli_cmd
 * @{
 */

/**
 * @brief Skoll-I commands begin.
 * @details Specified setting for commands begin of Skoll-I Click driver.
 */
#define SKOLLI_PACKET_CMD_ACTION                    "/"
#define SKOLLI_PACKET_CMD_SET                       "S"
#define SKOLLI_PACKET_CMD_GET                       "G"
#define SKOLLI_PACKET_CMD_PROFILE                   "."
#define SKOLLI_PACKET_RESPONSE                      "@R"
#define SKOLLI_PACKET_EVENT                         "@E"
#define SKOLLI_PACKET_PARAM_DELIMITER               ","
#define SKOLLI_PACKET_END                           "\r\n"

/**
 * @brief Skoll-I action commands.
 * @details Specified setting for action commands of Skoll-I Click driver.
 */
#define SKOLLI_CMD_SYS_PING                         "PING"
#define SKOLLI_CMD_SYS_REBOOT                       "RBT"
#define SKOLLI_CMD_SYS_DUMP                         "DUMP"
#define SKOLLI_CMD_SYS_STORE_CONFIG                 "SCFG"
#define SKOLLI_CMD_SYS_FACTORY_RESET                "RFAC"
#define SKOLLI_CMD_SYS_QUERY_FW_VERSION             "QFV"
#define SKOLLI_CMD_SYS_QUERY_UNIQUE_ID              "QUID"
#define SKOLLI_CMD_SYS_QUERY_RANDOM_NUM             "QRND"
#define SKOLLI_CMD_SYS_AES_ENCRYPT                  "AESE"
#define SKOLLI_CMD_SYS_AES_DECRYPT                  "AESD"
#define SKOLLI_CMD_SYS_WRITE_USER_DATA              "WUD"
#define SKOLLI_CMD_SYS_READ_USER_DATA               "RUD"
#define SKOLLI_CMD_SYS_FORCE_HIBERNATION            "SLEEP"
#define SKOLLI_CMD_GAP_CONNECT                      "C"
#define SKOLLI_CMD_GAP_CANCEL_CONNECTION            "CX"
#define SKOLLI_CMD_GAP_UPDATE_CONN_PARAMS           "UCP"
#define SKOLLI_CMD_GAP_SEND_CONNUPDATE_RESP         "CUR"
#define SKOLLI_CMD_GAP_DISCONNECT                   "DIS"
#define SKOLLI_CMD_GAP_ADD_WHITELIST_ENTRY          "WLA"
#define SKOLLI_CMD_GAP_DELETE_WHITELIST_ENTRY       "WLD"
#define SKOLLI_CMD_GAP_START_ADV                    "A"
#define SKOLLI_CMD_GAP_STOP_ADV                     "AX"
#define SKOLLI_CMD_GAP_START_SCAN                   "S"
#define SKOLLI_CMD_GAP_STOP_SCAN                    "SX"
#define SKOLLI_CMD_GAP_QUERY_PEER_ADDRESS           "QPA"
#define SKOLLI_CMD_GAP_QUERY_RSSI                   "QSS"
#define SKOLLI_CMD_GAP_QUERY_WHITELIST              "QWL"
#define SKOLLI_CMD_GAP_PHY_UPDATE                   "UP"
#define SKOLLI_CMD_SMP_QUERY_BONDS                  "QB"
#define SKOLLI_CMD_SMP_DELETE_BOND                  "BD"
#define SKOLLI_CMD_SMP_PAIR                         "P"
#define SKOLLI_CMD_SMP_QUERY_RANDOM_ADDRESS         "QRA"
#define SKOLLI_CMD_SMP_SEND_PAIRREQ_RESP            "PR"
#define SKOLLI_CMD_SMP_SEND_PASSKEYREQ_RESP         "PE"

/**
 * @brief Skoll-I set/get commands.
 * @details Specified setting for set/get commands of Skoll-I Click driver.
 */
#define SKOLLI_CMD_PROTOCOL_PARSE_MODE              "PPM"
#define SKOLLI_CMD_PROTOCOL_ECHO_MODE               "PEM"
#define SKOLLI_CMD_SYS_BT_ADDRESS                   "BA"
#define SKOLLI_CMD_SYS_SLEEP_PARAMS                 "SLP"
#define SKOLLI_CMD_SYS_TX_POWER                     "TXP"
#define SKOLLI_CMD_SYS_UART_PARAMS                  "TU"
#define SKOLLI_CMD_SYS_TRANSPORT                    "T"
#define SKOLLI_CMD_GAP_DEVICE_NAME                  "DN"
#define SKOLLI_CMD_GAP_DEVICE_APPEARANCE            "DA"
#define SKOLLI_CMD_GAP_ADV_DATA                     "AD"
#define SKOLLI_CMD_GAP_SR_DATA                      "SRD"
#define SKOLLI_CMD_GAP_ADV_PARAMS                   "AP"
#define SKOLLI_CMD_GAP_SCAN_PARAMS                  "SP"
#define SKOLLI_CMD_GAP_CONN_PARAMS                  "CP"
#define SKOLLI_CMD_GAP_EXTENDED_ADV_DATA            "EAD"
#define SKOLLI_CMD_GAP_EXTENDED_SR_DATA             "ERD"
#define SKOLLI_CMD_SMP_PRIVACY_MODE                 "PRV"
#define SKOLLI_CMD_SMP_SECURITY_PARAMS              "SBP"
#define SKOLLI_CMD_SMP_FIXED_PASSKEY                "FPK"

/**
 * @brief Skoll-I profile commands.
 * @details Specified setting for profile commands of Skoll-I Click driver.
 */
#define SKOLLI_CMD_CYSPP_CHECK                      "CYSPPCHECK"
#define SKOLLI_CMD_CYSPP_START                      "CYSPPSTART"
#define SKOLLI_CMD_CYSPP_SET_PARAMS                 "CYSPPSP"
#define SKOLLI_CMD_CYSPP_GET_PARAMS                 "CYSPPGP"
#define SKOLLI_CMD_CYSPP_SET_CLIENT_HANDLES         "CYSPPSH"
#define SKOLLI_CMD_CYSPP_GET_CLIENT_HANDLES         "CYSPPGH"
#define SKOLLI_CMD_CYSPP_SET_PACKETIZATION          "CYSPPSK"
#define SKOLLI_CMD_CYSPP_GET_PACKETIZATION          "CYSPPGK"

/**
 * @brief Skoll-I event commands.
 * @details Specified setting for event commands of Skoll-I Click driver.
 */
#define SKOLLI_EVT_SYS_BOOT                         "BOOT"
#define SKOLLI_EVT_SYS_ERROR                        "ERR"
#define SKOLLI_EVT_SYS_FACTORY_RESET_COMPLETE       "RFAC"
#define SKOLLI_EVT_SYS_FACTORY_TEST_ENTERED         "TFAC"
#define SKOLLI_EVT_SYS_DUMP_BLOB                    "DBLOB"
#define SKOLLI_EVT_GAP_WHITELIST_ENTRY              "WL"
#define SKOLLI_EVT_GAP_ADV_STATE_CHANGED            "ASC"
#define SKOLLI_EVT_GAP_SCAN_STATE_CHANGED           "SSC"
#define SKOLLI_EVT_GAP_SCAN_RESULT                  "S"
#define SKOLLI_EVT_GAP_CONNECTED                    "C"
#define SKOLLI_EVT_GAP_DISCONNECTED                 "DIS"
#define SKOLLI_EVT_GAP_CONNECTION_UPDATE_REQUESTED  "UCR"
#define SKOLLI_EVT_GAP_CONNECTION_UPDATED           "CU"
#define SKOLLI_EVT_GAP_PHY_UPDATED                  "PU"
#define SKOLLI_EVT_SMP_BOND_ENTRY                   "B"
#define SKOLLI_EVT_SMP_PAIRING_REQUESTED            "P"
#define SKOLLI_EVT_SMP_PAIRING_RESULT               "PR"
#define SKOLLI_EVT_SMP_ENCRYPTION_STATUS            "ENC"
#define SKOLLI_EVT_SMP_PASSKEY_DISPLAY_REQUESTED    "PKD"
#define SKOLLI_EVT_SMP_PASSKEY_ENTRY_REQUESTED      "PKE"
#define SKOLLI_EVT_CYSPP_STATUS                     ".CYSPP"

/**
 * @brief Skoll-I response and event flag settings.
 * @details Specified response and event flag settings of Skoll-I Click driver.
 */
#define SKOLLI_PACKET_TYPE_EVENT                    0
#define SKOLLI_PACKET_TYPE_RESPONSE                 1

/**
 * @brief Skoll-I timeout settings.
 * @details Specified timeout settings of Skoll-I Click driver.
 */
#define SKOLLI_RSP_TIMEOUT_1000MS                   1000
#define SKOLLI_CMD_TIMEOUT_5000MS                   5000
#define SKOLLI_WAIT_TIMEOUT_5S                      5
#define SKOLLI_WAIT_TIMEOUT_INFINITE                0

/**
 * @brief Skoll-I driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define SKOLLI_CMD_CODE_BUFFER_SIZE                 20
#define SKOLLI_PAYLOAD_BUFFER_SIZE                  200
#define SKOLLI_TX_DRV_BUFFER_SIZE                   200
#define SKOLLI_RX_DRV_BUFFER_SIZE                   500

/*! @} */ // skolli_cmd

/**
 * @defgroup skolli_map Skoll-I MikroBUS Map
 * @brief MikroBUS pin mapping of Skoll-I Click driver.
 */

/**
 * @addtogroup skolli_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Skoll-I Click to the selected MikroBUS.
 */
#define SKOLLI_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.con = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.spp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // skolli_map
/*! @} */ // skolli

/**
 * @brief Skoll-I Click response/event packet object.
 * @details Response/event packet object definition of Skoll-I Click driver.
 */
typedef struct
{
    uint8_t rsp_flag;               /**< Response/Event flag (1-response, 0-event). */
    uint8_t command_type;           /**< Command response type (SKOLLI_PACKET_CMD_x). */
    uint8_t command[ SKOLLI_CMD_CODE_BUFFER_SIZE ]; /**< Command code string. */
    uint16_t rsp_result;            /**< Response result word (0-OK). */
    uint8_t payload[ SKOLLI_PAYLOAD_BUFFER_SIZE ];  /**< Packet payload string (optional). */

} skolli_rsp_evt_packet_t;

/**
 * @brief Skoll-I Click context object.
 * @details Context object definition of Skoll-I Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cts;              /**< UART CTS pin. */
    digital_out_t rst;              /**< Reset device pin (active low). */
    digital_out_t spp;              /**< Command/Data pin (high:command, low:data). */

    // Input pins
    digital_in_t con;               /**< Connection status pin (active low). */
    digital_in_t rts;               /**< UART RTS pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ SKOLLI_RX_DRV_BUFFER_SIZE ];    /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ SKOLLI_TX_DRV_BUFFER_SIZE ];    /**< TX Buffer size. */
    uint8_t cmd_buffer[ SKOLLI_PAYLOAD_BUFFER_SIZE ];       /**< Command buffer. */
    skolli_rsp_evt_packet_t evt_pkt;                        /**< Event packet object. */

} skolli_t;

/**
 * @brief Skoll-I Click configuration object.
 * @details Configuration object definition of Skoll-I Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t con;                 /**< Connection status pin (active low). */
    pin_name_t rst;                 /**< Reset device pin (active low). */
    pin_name_t cts;                 /**< UART CTS pin. */
    pin_name_t spp;                 /**< Command/Data pin (high:command, low:data). */
    pin_name_t rts;                 /**< UART RTS pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} skolli_cfg_t;

/**
 * @brief Skoll-I Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SKOLLI_OK = 0,
    SKOLLI_ERROR = -1,
    SKOLLI_ERROR_TIMEOUT = -2,
    SKOLLI_ERROR_CMD = -3

} skolli_return_value_t;

/*!
 * @addtogroup skolli Skoll-I Click Driver
 * @brief API for configuring and manipulating Skoll-I Click driver.
 * @{
 */

/**
 * @brief Skoll-I configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #skolli_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void skolli_cfg_setup ( skolli_cfg_t *cfg );

/**
 * @brief Skoll-I initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #skolli_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t skolli_init ( skolli_t *ctx, skolli_cfg_t *cfg );

/**
 * @brief Skoll-I data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t skolli_generic_write ( skolli_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Skoll-I data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t skolli_generic_read ( skolli_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Skoll-I set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void skolli_set_rst_pin ( skolli_t *ctx, uint8_t state );

/**
 * @brief Skoll-I reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void skolli_reset_device ( skolli_t *ctx );

/**
 * @brief Skoll-I set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void skolli_set_cts_pin ( skolli_t *ctx, uint8_t state );

/**
 * @brief Skoll-I get RTS pin function.
 * @details This function returns the request to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t skolli_get_rts_pin ( skolli_t *ctx );

/**
 * @brief Skoll-I get CON pin function.
 * @details This function returns the connection status pin logic state.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t skolli_get_con_pin ( skolli_t *ctx );

/**
 * @brief Skoll-I set cmd mode function.
 * @details This function sets the command mode by setting the SPP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void skolli_set_cmd_mode ( skolli_t *ctx );

/**
 * @brief Skoll-I set data mode function.
 * @details This function sets the data mode by setting the SPP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void skolli_set_data_mode ( skolli_t *ctx );

/**
 * @brief Skoll-I cmd action function.
 * @details This function sends a specified action command to the Click module.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see SKOLLI_CMD_x action definitions.
 * @param[in] params : Command arguments string (optional).
 * @return None.
 * @note None.
 */
void skolli_cmd_action ( skolli_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief Skoll-I cmd set function.
 * @details This function sends a specified set command to the Click module.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see SKOLLI_CMD_x set/get definitions.
 * @param[in] params : Command arguments string.
 * @return None.
 * @note None.
 */
void skolli_cmd_set ( skolli_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief Skoll-I cmd get function.
 * @details This function sends a specified get command to the Click module.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see SKOLLI_CMD_x set/get definitions.
 * @param[in] params : Command arguments string (optional).
 * @return None.
 * @note None.
 */
void skolli_cmd_get ( skolli_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief Skoll-I cmd profile function.
 * @details This function sends a specified profile command to the Click module.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see SKOLLI_CMD_x profile definitions.
 * @param[in] params : Command arguments string (optional).
 * @return None.
 * @note None.
 */
void skolli_cmd_profile ( skolli_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief Skoll-I read packet function.
 * @details This function reads a response or event packet from the Click module and stores
 * it in ctx->evt_pkt structure.
 * @param[in] ctx : Click context object.
 * See #skolli_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t skolli_read_packet ( skolli_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SKOLLI_H

/*! @} */ // skolli

// ------------------------------------------------------------------------ END
