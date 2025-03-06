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
 * @file velaif820.h
 * @brief This file contains API for Vela IF820 Click Driver.
 */

#ifndef VELAIF820_H
#define VELAIF820_H

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
 * @addtogroup velaif820 Vela IF820 Click Driver
 * @brief API for configuring and manipulating Vela IF820 Click driver.
 * @{
 */

/**
 * @defgroup velaif820_cmd Vela IF820 Device Settings
 * @brief Settings for registers of Vela IF820 Click driver.
 */

/**
 * @addtogroup velaif820_cmd
 * @{
 */

/**
 * @brief Vela IF820 commands begin.
 * @details Specified setting for commands begin of Vela IF820 Click driver.
 */
#define VELAIF820_PACKET_CMD_ACTION                     "/"
#define VELAIF820_PACKET_CMD_SET                        "S"
#define VELAIF820_PACKET_CMD_GET                        "G"
#define VELAIF820_PACKET_CMD_PROFILE                    "."
#define VELAIF820_PACKET_RESPONSE                       "@R"
#define VELAIF820_PACKET_EVENT                          "@E"
#define VELAIF820_PACKET_PARAM_DELIMITER                ","
#define VELAIF820_PACKET_END                            "\r\n"

/**
 * @brief Vela IF820 action commands.
 * @details Specified setting for action commands of Vela IF820 Click driver.
 */
#define VELAIF820_CMD_SYS_PING                          "PING"
#define VELAIF820_CMD_SYS_REBOOT                        "RBT"
#define VELAIF820_CMD_SYS_DUMP                          "DUMP"
#define VELAIF820_CMD_SYS_STORE_CONFIG                  "SCFG"
#define VELAIF820_CMD_SYS_FACTORY_RESET                 "RFAC"
#define VELAIF820_CMD_SYS_QUERY_FW_VERSION              "QFV"
#define VELAIF820_CMD_SYS_QUERY_RANDOM_NUM              "QRND"
#define VELAIF820_CMD_SYS_WRITE_USER_DATA               "WUD"
#define VELAIF820_CMD_SYS_READ_USER_DATA                "RUD"
#define VELAIF820_CMD_GAP_CONNECT                       "C"
#define VELAIF820_CMD_GAP_CANCEL_CONNECTION             "CX"
#define VELAIF820_CMD_GAP_DISCONNECT                    "DIS"
#define VELAIF820_CMD_GAP_START_ADV                     "A"
#define VELAIF820_CMD_GAP_STOP_ADV                      "AX"
#define VELAIF820_CMD_GAP_START_SCAN                    "S"
#define VELAIF820_CMD_GAP_STOP_SCAN                     "SX"
#define VELAIF820_CMD_GAP_QUERY_PEER_ADDRESS            "QPA"
#define VELAIF820_CMD_GAP_QUERY_RSSI                    "QSS"
#define VELAIF820_CMD_SMP_QUERY_BONDS                   "QB"
#define VELAIF820_CMD_SMP_DELETE_BOND                   "BD"
#define VELAIF820_CMD_SMP_PAIR                          "P"
#define VELAIF820_CMD_BT_QUERY_NAME                     "BTQN"
#define VELAIF820_CMD_BT_CONNECT                        "BTC"
#define VELAIF820_CMD_BT_CANCEL_CONNECTION              "BTCX"
#define VELAIF820_CMD_BT_DISCONNECT                     "BTDIS"
#define VELAIF820_CMD_BT_QUERY_PEER_ADDRESS             "BTQPA"
#define VELAIF820_CMD_BT_QUERY_RSSI                     "BTQSS"

/**
 * @brief Vela IF820 set/get commands.
 * @details Specified setting for set/get commands of Vela IF820 Click driver.
 */
#define VELAIF820_CMD_PROTOCOL_PARSE_MODE               "PPM"
#define VELAIF820_CMD_PROTOCOL_ECHO_MODE                "PEM"
#define VELAIF820_CMD_SYS_BT_ADDRESS                    "BA"
#define VELAIF820_CMD_SYS_TX_POWER                      "TXP"
#define VELAIF820_CMD_SYS_TRANSPORT                     "T"
#define VELAIF820_CMD_GAP_DEVICE_NAME                   "DN"
#define VELAIF820_CMD_GAP_DEVICE_APPEARANCE             "DA"
#define VELAIF820_CMD_GAP_ADV_DATA                      "AD"
#define VELAIF820_CMD_GAP_SR_DATA                       "SRD"
#define VELAIF820_CMD_GAP_ADV_PARAMS                    "AP"
#define VELAIF820_CMD_GAP_SCAN_PARAMS                   "SP"
#define VELAIF820_CMD_GAP_CONNECTION_PARAMS             "CP"
#define VELAIF820_CMD_SMP_PIN_CODE                      "BTPIN"

/**
 * @brief Vela IF820 profile commands.
 * @details Specified setting for profile commands of Vela IF820 Click driver.
 */
#define VELAIF820_CMD_CYSPP_START                       "CYSPPSTART"
#define VELAIF820_CMD_CYSPP_SET_PARAMS                  "CYSPPSP"
#define VELAIF820_CMD_CYSPP_GET_PARAMS                  "CYSPPGP"
#define VELAIF820_CMD_CYSPP_SET_PACKETIZATION           "CYSPPSK"
#define VELAIF820_CMD_CYSPP_GET_PACKETIZATION           "CYSPPGK"
#define VELAIF820_CMD_SPP_SEND_CMD                      "SPPS"
#define VELAIF820_CMD_SPP_SET_CFG                       "SPPSC"
#define VELAIF820_CMD_SPP_GET_CFG                       "SPPGC"

/**
 * @brief Vela IF820 event commands.
 * @details Specified setting for event commands of Vela IF820 Click driver.
 */
#define VELAIF820_EVT_SYS_BOOT                          "BOOT"
#define VELAIF820_EVT_SYS_ERROR                         "ERR"
#define VELAIF820_EVT_SYS_FACTORY_RESET_COMPLETE        "RFAC"
#define VELAIF820_EVT_SYS_DUMP_BLOB                     "DBLOB"
#define VELAIF820_EVT_GAP_ADV_STATE_CHANGED             "ASC"
#define VELAIF820_EVT_GAP_SCAN_STATE_CHANGED            "SSC"
#define VELAIF820_EVT_GAP_SCAN_RESULT                   "S"
#define VELAIF820_EVT_GAP_CONNECTED                     "C"
#define VELAIF820_EVT_GAP_DISCONNECTED                  "DIS"
#define VELAIF820_EVT_GAP_CONNECTION_UPDATED            "CU"
#define VELAIF820_EVT_SMP_BOND_ENTRY                    "B"
#define VELAIF820_EVT_SMP_PAIRING_REQUESTED             "P"
#define VELAIF820_EVT_SMP_PAIRING_RESULT                "PR"
#define VELAIF820_EVT_SMP_ENCRYPTION_STATUS             "ENC"
#define VELAIF820_EVT_SMP_PIN_ENTRY_REQUESTED           "BTPIN"
#define VELAIF820_EVT_BT_INQUIRY_RESULT                 "BTIR"
#define VELAIF820_EVT_BT_NAME_RESULT                    "BTINR"
#define VELAIF820_EVT_BT_INQUIRY_COMPLETED              "BTIC"
#define VELAIF820_EVT_BT_CONNECTED                      "BTCON"
#define VELAIF820_EVT_BT_CONNECTION_STATUS              "BTCS"
#define VELAIF820_EVT_BT_CONNECTION_FAILED              "BTCF"
#define VELAIF820_EVT_BT_DISCONNECTED                   "BTDIS"
#define VELAIF820_EVT_SPP_DATA_RECEIVED                 "SPPD"

/**
 * @brief Vela IF820 response and event flag settings.
 * @details Specified response and event flag settings of Vela IF820 Click driver.
 */
#define VELAIF820_PACKET_TYPE_EVENT                     0
#define VELAIF820_PACKET_TYPE_RESPONSE                  1

/**
 * @brief Vela IF820 timeout settings.
 * @details Specified timeout settings of Vela IF820 Click driver.
 */
#define VELAIF820_RSP_TIMEOUT_1000MS                    1000
#define VELAIF820_CMD_TIMEOUT_5000MS                    5000
#define VELAIF820_WAIT_TIMEOUT_5S                       5
#define VELAIF820_WAIT_TIMEOUT_INFINITE                 0

/**
 * @brief Vela IF820 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define VELAIF820_CMD_CODE_BUFFER_SIZE                  20
#define VELAIF820_PAYLOAD_BUFFER_SIZE                   200
#define VELAIF820_TX_DRV_BUFFER_SIZE                    200
#define VELAIF820_RX_DRV_BUFFER_SIZE                    500

/*! @} */ // velaif820_cmd

/**
 * @defgroup velaif820_map Vela IF820 MikroBUS Map
 * @brief MikroBUS pin mapping of Vela IF820 Click driver.
 */

/**
 * @addtogroup velaif820_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Vela IF820 Click to the selected MikroBUS.
 */
#define VELAIF820_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.hwe = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.spp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // velaif820_map
/*! @} */ // velaif820

/**
 * @brief Vela IF820 Click response/event packet object.
 * @details Response/event packet object definition of Vela IF820 Click driver.
 */
typedef struct
{
    uint8_t rsp_flag;               /**< Response/Event flag (1-response, 0-event). */
    uint8_t command[ VELAIF820_CMD_CODE_BUFFER_SIZE ];  /**< Command code string. */
    uint16_t rsp_result;            /**< Response result word (0-OK). */
    uint8_t payload[ VELAIF820_PAYLOAD_BUFFER_SIZE ];   /**< Packet payload string (optional). */

} velaif820_rsp_evt_packet_t;

/**
 * @brief Vela IF820 Click context object.
 * @details Context object definition of Vela IF820 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rts;              /**< UART RTS pin. */
    digital_out_t rst;              /**< Reset device pin (active low). */
    digital_out_t spp;              /**< Command/Data pin (high:command, low:data). */

    // Input pins
    digital_in_t hwe;               /**< IF820 awake and ready pin (active high). */
    digital_in_t cts;               /**< UART CTS pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ VELAIF820_RX_DRV_BUFFER_SIZE ]; /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ VELAIF820_TX_DRV_BUFFER_SIZE ]; /**< TX Buffer size. */
    uint8_t cmd_buffer[ VELAIF820_PAYLOAD_BUFFER_SIZE ];    /**< Command buffer. */
    velaif820_rsp_evt_packet_t evt_pkt; /**< Event packet object. */

} velaif820_t;

/**
 * @brief Vela IF820 Click configuration object.
 * @details Configuration object definition of Vela IF820 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t hwe;                 /**< IF820 awake and ready pin (active high). */
    pin_name_t rts;                 /**< UART RTS pin. */
    pin_name_t rst;                 /**< Reset device pin (active low). */
    pin_name_t spp;                 /**< Command/Data pin (high:command, low:data). */
    pin_name_t cts;                 /**< UART CTS pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} velaif820_cfg_t;

/**
 * @brief Vela IF820 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VELAIF820_OK = 0,
    VELAIF820_ERROR = -1,
    VELAIF820_ERROR_TIMEOUT = -2,
    VELAIF820_ERROR_CMD = -3

} velaif820_return_value_t;

/*!
 * @addtogroup velaif820 Vela IF820 Click Driver
 * @brief API for configuring and manipulating Vela IF820 Click driver.
 * @{
 */

/**
 * @brief Vela IF820 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #velaif820_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void velaif820_cfg_setup ( velaif820_cfg_t *cfg );

/**
 * @brief Vela IF820 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #velaif820_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t velaif820_init ( velaif820_t *ctx, velaif820_cfg_t *cfg );

/**
 * @brief Vela IF820 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t velaif820_generic_write ( velaif820_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Vela IF820 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t velaif820_generic_read ( velaif820_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Vela IF820 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void velaif820_set_rst_pin ( velaif820_t *ctx, uint8_t state );

/**
 * @brief Vela IF820 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void velaif820_reset_device ( velaif820_t *ctx );

/**
 * @brief Vela IF820 set RTS pin function.
 * @details This function sets the request to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void velaif820_set_rts_pin ( velaif820_t *ctx, uint8_t state );

/**
 * @brief Vela IF820 get CTS pin function.
 * @details This function returns the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t velaif820_get_cts_pin ( velaif820_t *ctx );

/**
 * @brief Vela IF820 get HWE pin function.
 * @details This function returns the IF820 ready pin logic state.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t velaif820_get_hwe_pin ( velaif820_t *ctx );

/**
 * @brief Vela IF820 set cmd mode function.
 * @details This function sets the command mode by setting the SPP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void velaif820_set_cmd_mode ( velaif820_t *ctx );

/**
 * @brief Vela IF820 set data mode function.
 * @details This function sets the data mode by setting the SPP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void velaif820_set_data_mode ( velaif820_t *ctx );

/**
 * @brief Vela IF820 cmd action function.
 * @details This function sends a specified action command to the Click module.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see VELAIF820_CMD_x action definitions.
 * @param[in] params : Command arguments string (optional).
 * @return None.
 * @note None.
 */
void velaif820_cmd_action ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief Vela IF820 cmd set function.
 * @details This function sends a specified set command to the Click module.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see VELAIF820_CMD_x set/get definitions.
 * @param[in] params : Command arguments string.
 * @return None.
 * @note None.
 */
void velaif820_cmd_set ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief Vela IF820 cmd get function.
 * @details This function sends a specified get command to the Click module.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see VELAIF820_CMD_x set/get definitions.
 * @param[in] params : Command arguments string (optional).
 * @return None.
 * @note None.
 */
void velaif820_cmd_get ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief Vela IF820 cmd profile function.
 * @details This function sends a specified profile command to the Click module.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see VELAIF820_CMD_x profile definitions.
 * @param[in] params : Command arguments string (optional).
 * @return None.
 * @note None.
 */
void velaif820_cmd_profile ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params );

/**
 * @brief Vela IF820 read packet function.
 * @details This function reads a response or event packet from the Click module and stores
 * it in ctx->evt_pkt structure.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t velaif820_read_packet ( velaif820_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VELAIF820_H

/*! @} */ // velaif820

// ------------------------------------------------------------------------ END
