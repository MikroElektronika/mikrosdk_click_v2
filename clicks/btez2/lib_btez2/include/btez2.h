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
 * @file btez2.h
 * @brief This file contains API for BT-EZ 2 Click Driver.
 */

#ifndef BTEZ2_H
#define BTEZ2_H

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
 * @addtogroup btez2 BT-EZ 2 Click Driver
 * @brief API for configuring and manipulating BT-EZ 2 Click driver.
 * @{
 */

/**
 * @defgroup btez2_cmd BT-EZ 2 Device Settings
 * @brief Settings for registers of BT-EZ 2 Click driver.
 */

/**
 * @addtogroup btez2_cmd
 * @{
 */

/**
 * @brief BT-EZ 2 commands begin.
 * @details Specified setting for commands begin of BT-EZ 2 Click driver.
 */
#define BTEZ2_PACKET_CMD_ACTION                     "/"
#define BTEZ2_PACKET_CMD_SET                        "S"
#define BTEZ2_PACKET_CMD_GET                        "G"
#define BTEZ2_PACKET_CMD_PROFILE                    "."
#define BTEZ2_PACKET_RESPONSE                       "@R"
#define BTEZ2_PACKET_EVENT                          "@E"
#define BTEZ2_PACKET_PARAM_DELIMITER                ","
#define BTEZ2_PACKET_END                            "\r\n"

/**
 * @brief BT-EZ 2 action commands.
 * @details Specified setting for action commands of BT-EZ 2 Click driver.
 */
#define BTEZ2_CMD_SYS_PING                          "PING"
#define BTEZ2_CMD_SYS_REBOOT                        "RBT"
#define BTEZ2_CMD_SYS_DUMP                          "DUMP"
#define BTEZ2_CMD_SYS_STORE_CONFIG                  "SCFG"
#define BTEZ2_CMD_SYS_FACTORY_RESET                 "RFAC"
#define BTEZ2_CMD_SYS_QUERY_FW_VERSION              "QFV"
#define BTEZ2_CMD_SYS_QUERY_UNIQUE_ID               "QUID"
#define BTEZ2_CMD_SYS_QUERY_RANDOM_NUM              "QRND"
#define BTEZ2_CMD_SYS_AES_ENCRYPT                   "AESE"
#define BTEZ2_CMD_SYS_AES_DECRYPT                   "AESD"
#define BTEZ2_CMD_SYS_WRITE_USER_DATA               "WUD"
#define BTEZ2_CMD_SYS_READ_USER_DATA                "RUD"
#define BTEZ2_CMD_SYS_FORCE_HIBERNATION             "SLEEP"
#define BTEZ2_CMD_GAP_CONNECT                       "C"
#define BTEZ2_CMD_GAP_CANCEL_CONNECTION             "CX"
#define BTEZ2_CMD_GAP_UPDATE_CONN_PARAMS            "UCP"
#define BTEZ2_CMD_GAP_SEND_CONNUPDATE_RESP          "CUR"
#define BTEZ2_CMD_GAP_DISCONNECT                    "DIS"
#define BTEZ2_CMD_GAP_ADD_WHITELIST_ENTRY           "WLA"
#define BTEZ2_CMD_GAP_DELETE_WHITELIST_ENTRY        "WLD"
#define BTEZ2_CMD_GAP_START_ADV                     "A"
#define BTEZ2_CMD_GAP_STOP_ADV                      "AX"
#define BTEZ2_CMD_GAP_START_SCAN                    "S"
#define BTEZ2_CMD_GAP_STOP_SCAN                     "SX"
#define BTEZ2_CMD_GAP_QUERY_PEER_ADDRESS            "QPA"
#define BTEZ2_CMD_GAP_QUERY_RSSI                    "QSS"
#define BTEZ2_CMD_GAP_QUERY_WHITELIST               "QWL"
#define BTEZ2_CMD_GAP_PHY_UPDATE                    "UP"
#define BTEZ2_CMD_SMP_QUERY_BONDS                   "QB"
#define BTEZ2_CMD_SMP_DELETE_BOND                   "BD"
#define BTEZ2_CMD_SMP_PAIR                          "P"
#define BTEZ2_CMD_SMP_QUERY_RANDOM_ADDRESS          "QRA"
#define BTEZ2_CMD_SMP_SEND_PAIRREQ_RESP             "PR"
#define BTEZ2_CMD_SMP_SEND_PASSKEYREQ_RESP          "PE"

/**
 * @brief BT-EZ 2 set/get commands.
 * @details Specified setting for set/get commands of BT-EZ 2 Click driver.
 */
#define BTEZ2_CMD_PROTOCOL_PARSE_MODE               "PPM"
#define BTEZ2_CMD_PROTOCOL_ECHO_MODE                "PEM"
#define BTEZ2_CMD_SYS_BT_ADDRESS                    "BA"
#define BTEZ2_CMD_SYS_SLEEP_PARAMS                  "SLP"
#define BTEZ2_CMD_SYS_TX_POWER                      "TXP"
#define BTEZ2_CMD_SYS_UART_PARAMS                   "TU"
#define BTEZ2_CMD_SYS_TRANSPORT                     "T"
#define BTEZ2_CMD_GAP_DEVICE_NAME                   "DN"
#define BTEZ2_CMD_GAP_DEVICE_APPEARANCE             "DA"
#define BTEZ2_CMD_GAP_ADV_DATA                      "AD"
#define BTEZ2_CMD_GAP_SR_DATA                       "SRD"
#define BTEZ2_CMD_GAP_ADV_PARAMS                    "AP"
#define BTEZ2_CMD_GAP_SCAN_PARAMS                   "SP"
#define BTEZ2_CMD_GAP_CONN_PARAMS                   "CP"
#define BTEZ2_CMD_GAP_EXTENDED_ADV_DATA             "EAD"
#define BTEZ2_CMD_GAP_EXTENDED_SR_DATA              "ERD"
#define BTEZ2_CMD_SMP_PRIVACY_MODE                  "PRV"
#define BTEZ2_CMD_SMP_SECURITY_PARAMS               "SBP"
#define BTEZ2_CMD_SMP_FIXED_PASSKEY                 "FPK"

/**
 * @brief BT-EZ 2 profile commands.
 * @details Specified setting for profile commands of BT-EZ 2 Click driver.
 */
#define BTEZ2_CMD_CYSPP_CHECK                       "CYSPPCHECK"
#define BTEZ2_CMD_CYSPP_START                       "CYSPPSTART"
#define BTEZ2_CMD_CYSPP_SET_PARAMS                  "CYSPPSP"
#define BTEZ2_CMD_CYSPP_GET_PARAMS                  "CYSPPGP"
#define BTEZ2_CMD_CYSPP_SET_CLIENT_HANDLES          "CYSPPSH"
#define BTEZ2_CMD_CYSPP_GET_CLIENT_HANDLES          "CYSPPGH"
#define BTEZ2_CMD_CYSPP_SET_PACKETIZATION           "CYSPPSK"
#define BTEZ2_CMD_CYSPP_GET_PACKETIZATION           "CYSPPGK"

/**
 * @brief BT-EZ 2 event commands.
 * @details Specified setting for event commands of BT-EZ 2 Click driver.
 */
#define BTEZ2_EVT_SYS_BOOT                          "BOOT"
#define BTEZ2_EVT_SYS_ERROR                         "ERR"
#define BTEZ2_EVT_SYS_FACTORY_RESET_COMPLETE        "RFAC"
#define BTEZ2_EVT_SYS_FACTORY_TEST_ENTERED          "TFAC"
#define BTEZ2_EVT_SYS_DUMP_BLOB                     "DBLOB"
#define BTEZ2_EVT_GAP_WHITELIST_ENTRY               "WL"
#define BTEZ2_EVT_GAP_ADV_STATE_CHANGED             "ASC"
#define BTEZ2_EVT_GAP_SCAN_STATE_CHANGED            "SSC"
#define BTEZ2_EVT_GAP_SCAN_RESULT                   "S"
#define BTEZ2_EVT_GAP_CONNECTED                     "C"
#define BTEZ2_EVT_GAP_DISCONNECTED                  "DIS"
#define BTEZ2_EVT_GAP_CONNECTION_UPDATE_REQUESTED   "UCR"
#define BTEZ2_EVT_GAP_CONNECTION_UPDATED            "CU"
#define BTEZ2_EVT_GAP_PHY_UPDATED                   "PU"
#define BTEZ2_EVT_SMP_BOND_ENTRY                    "B"
#define BTEZ2_EVT_SMP_PAIRING_REQUESTED             "P"
#define BTEZ2_EVT_SMP_PAIRING_RESULT                "PR"
#define BTEZ2_EVT_SMP_ENCRYPTION_STATUS             "ENC"
#define BTEZ2_EVT_SMP_PASSKEY_DISPLAY_REQUESTED     "PKD"
#define BTEZ2_EVT_SMP_PASSKEY_ENTRY_REQUESTED       "PKE"
#define BTEZ2_EVT_CYSPP_STATUS                      ".CYSPP"

/**
 * @brief BT-EZ 2 response and event flag settings.
 * @details Specified response and event flag settings of BT-EZ 2 Click driver.
 */
#define BTEZ2_PACKET_TYPE_EVENT                     0
#define BTEZ2_PACKET_TYPE_RESPONSE                  1

/**
 * @brief BT-EZ 2 timeout settings.
 * @details Specified timeout settings of BT-EZ 2 Click driver.
 */
#define BTEZ2_RSP_TIMEOUT_1000MS                    1000
#define BTEZ2_CMD_TIMEOUT_5000MS                    5000
#define BTEZ2_WAIT_TIMEOUT_5S                       5
#define BTEZ2_WAIT_TIMEOUT_INFINITE                 0

/**
 * @brief BT-EZ 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BTEZ2_CMD_CODE_BUFFER_SIZE                  20
#define BTEZ2_PAYLOAD_BUFFER_SIZE                   200
#define BTEZ2_TX_DRV_BUFFER_SIZE                    200
#define BTEZ2_RX_DRV_BUFFER_SIZE                    500

/*! @} */ // btez2_cmd

/**
 * @defgroup btez2_map BT-EZ 2 MikroBUS Map
 * @brief MikroBUS pin mapping of BT-EZ 2 Click driver.
 */

/**
 * @addtogroup btez2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BT-EZ 2 Click to the selected MikroBUS.
 */
#define BTEZ2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.cyspp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // btez2_map
/*! @} */ // btez2

/**
 * @brief BT-EZ 2 Click response/event packet object.
 * @details Response/event packet object definition of BT-EZ 2 Click driver.
 */
typedef struct
{
    uint8_t rsp_flag;               /**< Response/Event flag (1-response, 0-event). */
    uint8_t command_type;           /**< Command response type (BTEZ2_PACKET_CMD_x). */
    uint8_t command[ BTEZ2_CMD_CODE_BUFFER_SIZE ];  /**< Command code string. */
    uint16_t rsp_result;            /**< Response result word (0-OK). */
    uint8_t payload[ BTEZ2_PAYLOAD_BUFFER_SIZE ];   /**< Packet payload string (optional). */

} btez2_rsp_evt_packet_t;

/**
 * @brief BT-EZ 2 Click context object.
 * @details Context object definition of BT-EZ 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cyspp;            /**< Command/Data pin (high:command, low:data). */
    digital_out_t rst;              /**< Reset device pin (active low). */
    digital_out_t cts;              /**< UART CTS pin. */

    // Input pins
    digital_in_t rts;               /**< UART RTS pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BTEZ2_RX_DRV_BUFFER_SIZE ]; /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ BTEZ2_TX_DRV_BUFFER_SIZE ]; /**< TX Buffer size. */
    uint8_t cmd_buffer[ BTEZ2_PAYLOAD_BUFFER_SIZE ];    /**< Command buffer. */
    btez2_rsp_evt_packet_t evt_pkt; /**< Event packet object. */

} btez2_t;

/**
 * @brief BT-EZ 2 Click configuration object.
 * @details Configuration object definition of BT-EZ 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t cyspp;               /**< Command/Data pin (high:command, low:data). */
    pin_name_t rst;                 /**< Reset device pin (active low). */
    pin_name_t cts;                 /**< UART CTS pin. */
    pin_name_t rts;                 /**< UART RTS pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} btez2_cfg_t;

/**
 * @brief BT-EZ 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BTEZ2_OK = 0,
    BTEZ2_ERROR = -1,
    BTEZ2_ERROR_TIMEOUT = -2,
    BTEZ2_ERROR_CMD = -3

} btez2_return_value_t;

/*!
 * @addtogroup btez2 BT-EZ 2 Click Driver
 * @brief API for configuring and manipulating BT-EZ 2 Click driver.
 * @{
 */

/**
 * @brief BT-EZ 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #btez2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void btez2_cfg_setup ( btez2_cfg_t *cfg );

/**
 * @brief BT-EZ 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #btez2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btez2_init ( btez2_t *ctx, btez2_cfg_t *cfg );

/**
 * @brief BT-EZ 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btez2_generic_write ( btez2_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BT-EZ 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btez2_generic_read ( btez2_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BT-EZ 2 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void btez2_set_rst_pin ( btez2_t *ctx, uint8_t state );

/**
 * @brief BT-EZ 2 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btez2_reset_device ( btez2_t *ctx );

/**
 * @brief BT-EZ 2 set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void btez2_set_cts_pin ( btez2_t *ctx, uint8_t state );

/**
 * @brief BT-EZ 2 get RTS pin function.
 * @details This function returns the request to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t btez2_get_rts_pin ( btez2_t *ctx );

/**
 * @brief BT-EZ 2 set cmd mode function.
 * @details This function sets the command mode by setting the CYSPP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btez2_set_cmd_mode ( btez2_t *ctx );

/**
 * @brief BT-EZ 2 set data mode function.
 * @details This function sets the data mode by setting the CYSPP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btez2_set_data_mode ( btez2_t *ctx );

/**
 * @brief BT-EZ 2 cmd action function.
 * @details This function sends a specified action command to the Click module.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BTEZ2_CMD_x action definitions.
 * @param[in] params : Command arguments string (optional).
 * @return None.
 * @note None.
 */
void btez2_cmd_action ( btez2_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief BT-EZ 2 cmd set function.
 * @details This function sends a specified set command to the Click module.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BTEZ2_CMD_x set/get definitions.
 * @param[in] params : Command arguments string.
 * @return None.
 * @note None.
 */
void btez2_cmd_set ( btez2_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief BT-EZ 2 cmd get function.
 * @details This function sends a specified get command to the Click module.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BTEZ2_CMD_x set/get definitions.
 * @param[in] params : Command arguments string (optional).
 * @return None.
 * @note None.
 */
void btez2_cmd_get ( btez2_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief BT-EZ 2 cmd profile function.
 * @details This function sends a specified profile command to the Click module.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BTEZ2_CMD_x profile definitions.
 * @param[in] params : Command arguments string (optional).
 * @return None.
 * @note None.
 */
void btez2_cmd_profile ( btez2_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief BT-EZ 2 read packet function.
 * @details This function reads a response or event packet from the Click module and stores
 * it in ctx->evt_pkt structure.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btez2_read_packet ( btez2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BTEZ2_H

/*! @} */ // btez2

// ------------------------------------------------------------------------ END
