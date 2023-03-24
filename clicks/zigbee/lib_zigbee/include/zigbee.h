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
 * @file zigbee.h
 * @brief This file contains API for ZigBee Click Driver.
 */

#ifndef ZIGBEE_H
#define ZIGBEE_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup zigbee ZigBee Click Driver
 * @brief API for configuring and manipulating ZigBee Click driver.
 * @{
 */

/**
 * @defgroup zigbee_cmd ZigBee Device Settings
 * @brief Settings for registers of ZigBee Click driver.
 */

/**
 * @addtogroup zigbee_cmd
 * @{
 */

/**
 * @brief ZigBee control commands.
 * @details Specified setting for control commands of ZigBee Click driver.
 */
#define ZIGBEE_CMD_AT                           "AT"
#define ZIGBEE_CMD_ATI                          "ATI"
#define ZIGBEE_CMD_ATZ                          "ATZ"
#define ZIGBEE_CMD_AT_REMZ                      "AT+REMZ"
#define ZIGBEE_CMD_AT_F                         "AT&F"
#define ZIGBEE_CMD_AT_BLOAD                     "AT+BLOAD"
#define ZIGBEE_CMD_AT_PASSTHROUGH               "AT+PASSTHROUGH"
#define ZIGBEE_CMD_AT_RECOVER                   "AT+RECOVER"
#define ZIGBEE_CMD_ATS                          "ATS"
#define ZIGBEE_CMD_ATREMS                       "ATREMS"
#define ZIGBEE_CMD_ATSALL                       "ATSALL"
#define ZIGBEE_CMD_AT_TOKDUMP                   "AT+TOKDUMP"

/**
 * @brief ZigBee network control commands.
 * @details Specified setting for network control commands of ZigBee Click driver.
 */
#define ZIGBEE_CMD_AT_ESCAN                     "AT+ESCAN"
#define ZIGBEE_CMD_AT_EN                        "AT+EN"
#define ZIGBEE_CMD_AT_PANSCAN                   "AT+PANSCAN"
#define ZIGBEE_CMD_AT_JN                        "AT+JN"
#define ZIGBEE_CMD_AT_JPAN                      "AT+JPAN"
#define ZIGBEE_CMD_AT_SJN                       "AT+SJN"
#define ZIGBEE_CMD_AT_DASSL                     "AT+DASSL"
#define ZIGBEE_CMD_AT_DASSR                     "AT+DASSR"
#define ZIGBEE_CMD_AT_N                         "AT+N"
#define ZIGBEE_CMD_AT_NTABLE                    "AT+NTABLE"
#define ZIGBEE_CMD_AT_RTABLE                    "AT+RTABLE"
#define ZIGBEE_CMD_AT_IDREQ                     "AT+IDREQ"
#define ZIGBEE_CMD_AT_EUIREQ                    "AT+EUIREQ"
#define ZIGBEE_CMD_AT_NODEDESC                  "AT+NODEDESC"
#define ZIGBEE_CMD_AT_POWERDESC                 "AT+POWERDESC"
#define ZIGBEE_CMD_AT_ACTEPDESC                 "AT+ACTEPDESC"
#define ZIGBEE_CMD_AT_SIMPLEDESC                "AT+SIMPLEDESC"
#define ZIGBEE_CMD_AT_MATCHREQ                  "AT+MATCHREQ"
#define ZIGBEE_CMD_AT_ANNCE                     "AT+ANNCE"
#define ZIGBEE_CMD_AT_SR                        "AT+SR"
#define ZIGBEE_CMD_AT_FNDSR                     "AT+FNDSR"
#define ZIGBEE_CMD_AT_POLL                      "AT+POLL"
#define ZIGBEE_CMD_AT_REJOIN                    "AT+REJOIN"
#define ZIGBEE_CMD_AT_SN                        "AT+SN"
#define ZIGBEE_CMD_AT_KEYUPD                    "AT+KEYUPD"
#define ZIGBEE_CMD_AT_BECOMENTC                 "AT+BECOMENTC"
#define ZIGBEE_CMD_AT_BECOMENM                  "AT+BECOMENM"
#define ZIGBEE_CMD_AT_CCHANGE                   "AT+CCHANGE"

/**
 * @brief ZigBee messageing commands.
 * @details Specified setting for messageing commands of ZigBee Click driver.
 */
#define ZIGBEE_CMD_AT_ATABLE                    "AT+ATABLE"
#define ZIGBEE_CMD_AT_ASET                      "AT+ASET"
#define ZIGBEE_CMD_AT_MTABLE                    "AT+MTABLE"
#define ZIGBEE_CMD_AT_MSET                      "AT+MSET"
#define ZIGBEE_CMD_AT_BCAST                     "AT+BCAST"
#define ZIGBEE_CMD_AT_BCASTB                    "AT+BCASTB"
#define ZIGBEE_CMD_AT_UCAST                     "AT+UCAST"
#define ZIGBEE_CMD_AT_UCASTB                    "AT+UCASTB"
#define ZIGBEE_CMD_AT_SCAST                     "AT+SCAST"
#define ZIGBEE_CMD_AT_SCASTB                    "AT+SCASTB"
#define ZIGBEE_CMD_AT_SSINK                     "AT+SSINK"
#define ZIGBEE_CMD_AT_MCAST                     "AT+MCAST"
#define ZIGBEE_CMD_AT_MCASTB                    "AT+MCASTB"
#define ZIGBEE_CMD_AT_DMODE                     "AT+DMODE"
#define ZIGBEE_CMD_AT_PPP                       "+++"
#define ZIGBEE_CMD_AT_IDENT                     "AT+IDENT"
#define ZIGBEE_CMD_AT_SENDUCAST                 "AT+SENDUCAST"
#define ZIGBEE_CMD_AT_SENDUCASTB                "AT+SENDUCASTB"
#define ZIGBEE_CMD_AT_SNEDMCAST                 "AT+SNEDMCAST"
#define ZIGBEE_CMD_AT_SENDMCASTB                "AT+SENDMCASTB"
#define ZIGBEE_CMD_AT_INTERPAN                  "AT+INTERPAN"
#define ZIGBEE_CMD_AT_RDATAB                    "AT+RDATAB"

/**
 * @brief ZigBee binding management commands.
 * @details Specified setting for binding management commands of ZigBee Click driver.
 */
#define ZIGBEE_CMD_AT_LBTABLE                   "AT+LBTABLE"
#define ZIGBEE_CMD_AT_BSET                      "AT+BSET"
#define ZIGBEE_CMD_AT_BCLR                      "AT+BCLR"
#define ZIGBEE_CMD_AT_BTABLE                    "AT+BTABLE"
#define ZIGBEE_CMD_AT_BIND                      "AT+BIND"
#define ZIGBEE_CMD_AT_UNBIND                    "AT+UNBIND"
#define ZIGBEE_CMD_AT_EDBIND                    "AT+EDBIND"

/**
 * @brief ZigBee time-related commands.
 * @details Specified setting for time-related commands of ZigBee Click driver.
 */
#define ZIGBEE_CMD_AT_SETTIME                   "AT+SETTIME"
#define ZIGBEE_CMD_AT_GETTIME                   "AT+GETTIME"
#define ZIGBEE_CMD_AT_SYNCTIME                  "AT+SYNCTIME"

/**
 * @brief ZigBee suffix buffer.
 * @details Specified setting for suffix buffer of ZigBee Click driver.
 */
#define ZIGBEE_SUFFIX_NULL                      ""

/**
 * @brief ZigBee driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ZIGBEE_DEV_BUFFER_MAX                   80

/*! @} */ // zigbee_cmd

/**
 * @defgroup zigbee_map ZigBee MikroBUS Map
 * @brief MikroBUS pin mapping of ZigBee Click driver.
 */

/**
 * @addtogroup zigbee_map
 * @{
 */

/**
 * @brief ZigBee error codes.
 * @details Specified setting for error codes of ZigBee Click driver.
 */
#define ZIGBEE_ERROR_OK                         0X00
#define ZIGBEE_ERROR_CANT_POLL_TIMEOUT          0X01
#define ZIGBEE_ERROR_UNKNOWN_CMD                0X02
#define ZIGBEE_ERROR_INVALID_SREG               0X04
#define ZIGBEE_ERROR_INVALID_PARAM              0X05
#define ZIGBEE_ERROR_RECIPIENT                  0X06
#define ZIGBEE_ERROR_MSG_NACK                   0X07
#define ZIGBEE_ERROR_NSINK                      0X08
#define ZIGBEE_ERROR_ADR_TABLE_IN_USE           0X09
#define ZIGBEE_ERROR_MSG_NOT_SENT               0X0A
#define ZIGBEE_ERROR_LOCAL_NODE_NSINK           0X0B
#define ZIGBEE_ERROR_TOO_MANY_CHAR              0X0C
#define ZIGBEE_ERROR_BG_SCAN_IN_PROGRESS        0X0E
#define ZIGBEE_ERROR_FATAL_INIT_NET             0X0F
#define ZIGBEE_ERROR_BOOTLOADING                0X10
#define ZIGBEE_ERROR_FATAL_INIT_STACK           0X12
#define ZIGBEE_ERROR_NODE_OUT_OF_BUFFER         0X18
#define ZIGBEE_ERROR_READ_ONLY_REG              0X19
#define ZIGBEE_ERROR_DATA_MODE_REFUSED_RN       0X1A
#define ZIGBEE_ERROR_CONN_LOST_DATA_MODE        0X1B
#define ZIGBEE_ERROR_RN_IN_DATA_MODE            0X1C
#define ZIGBEE_ERROR_INVALID_PASWD              0X20
#define ZIGBEE_ERROR_CANT_FORM_NET              0X25
#define ZIGBEE_ERROR_NO_NET_FOUND               0X27
#define ZIGBEE_ERROR_NOD_PART_OF_PAN            0X28
#define ZIGBEE_ERROR_LEAVING_PAN                0X2C
#define ZIGBEE_ERROR_SCANNING_PAN               0X2D
#define ZIGBEE_ERROR_NO_RESP_BOOTLOADER         0X33
#define ZIGBEE_ERROR_TARGET_NO_RESP             0X34
#define ZIGBEE_ERROR_TIMEOUT_XCASTB             0X35
#define ZIGBEE_ERROR_MAC_TX_QUEUE_FULL          0X39
#define ZIGBEE_ERROR_INVALID_BIND_INDEX         0X6C
#define ZIGBEE_ERROR_INVALID_OP                 0X70
#define ZIGBEE_ERROR_MORE_THAN_10_UNI_MSG       0X72
#define ZIGBEE_ERROR_MSG_TOO_LONG               0X74
#define ZIGBEE_ERROR_ZDP_INVALID_REQ_TYPE       0X80
#define ZIGBEE_ERROR_ZDP_DEV_NOT_FOUND          0X81
#define ZIGBEE_ERROR_ZDP_INVALID_ENDPONT        0X82
#define ZIGBEE_ERROR_ZDP_NOT_ACTIVE             0X83
#define ZIGBEE_ERROR_ZDP_NOT_SUPPORTED          0X84
#define ZIGBEE_ERROR_ZDP_TIMEOUT                0X85
#define ZIGBEE_ERROR_ZDP_NO_MATCH               0X86
#define ZIGBEE_ERROR_ZDP_TABLE_FULL             0X87
#define ZIGBEE_ERROR_ZDP_NO_ENTRY               0X88
#define ZIGBEE_ERROR_ZDP_NO_DESC                0X89
#define ZIGBEE_ERROR_OP_IF_CONN_TO_PAN          0X91
#define ZIGBEE_ERROR_NODE_NOT_IN_NET            0X93
#define ZIGBEE_ERROR_CANNT_JOIN_NET             0X94
#define ZIGBEE_ERROR_MOBILE_END_DEV_MOVE        0X96
#define ZIGBEE_ERROR_CANT_JOIN_2006_NET         0X98
#define ZIGBEE_ERROR_8_MSG_IN_8_SEC_MAX         0XA1
#define ZIGBEE_ERROR_NO_BEACON                  0XAB
#define ZIGBEE_ERROR_NET_KEY_SENT               0XAC
#define ZIGBEE_ERROR_NO_RECEIVE_NET_KEY         0XAD
#define ZIGBEE_ERROR_NO_LINK_KEY_REQ            0XAE
#define ZIGBEE_ERROR_PRECONFIG_KEY_REQ          0XAF
#define ZIGBEE_ERROR_NWK_ALREADY_PRESENT        0XC5
#define ZIGBEE_ERROR_NWK_TABLE_FULL             0XC7
#define ZIGBEE_ERROR_NWK_UNKNOWN_DEV            0XC8

#define ZIGBEE_RESP_ERROR                       "ERROR"
#define ZIGBEE_RESP_OK                          "OK"
#define ZIGBEE_ERROR_INC                        6

#define ZIGBEE_ERROR_CODE_MAX                   59
#define ZIGBEE_ERROR_CODE                       0
#define ZIGBEE_ERROR_DESC                       1

/**
 * @brief ZigBee device host mode.
 * @details Setting ZigBee Click into a host operation mode.
 */
#define ZIGBEE_DEV_HOST                         1

/**
 * @brief ZigBee device user mode.
 * @details Setting ZigBee Click into a user operation mode.
 */
#define ZIGBEE_DEV_USER                         2

#define ZIGBEE_APP_TASK                         11
#define ZIGBEE_APP_INIT                         12

/**
 * @brief ZigBee operation codes.
 * @details Specified operation codes of ZigBee Click driver.
 */
#define ZIGBEE_OP_WAIT                          0x00
#define ZIGBEE_OP_OK                            0xAA
#define ZIGBEE_OP_ERROR                         0xBB
#define ZIGBEE_OP_NL                            0xCC

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ZigBee Click to the selected MikroBUS.
 */
#define ZIGBEE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.fw      = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // zigbee_map
/*! @} */ // zigbee

/**
 * @brief ZigBee Click context object.
 * @details Context object definition of ZigBee Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t fw;               /**< FW Update. */
    digital_out_t rst;              /**< Reset. */

    // Input pins
    digital_in_t int_pin;           /**< Interrupt. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ ZIGBEE_DEV_BUFFER_MAX ];         /**< Buffer size. */
    char uart_tx_buffer[ ZIGBEE_DEV_BUFFER_MAX ];         /**< Buffer size. */

} zigbee_t;

/**
 * @brief ZigBee Click configuration object.
 * @details Configuration object definition of ZigBee Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t fw;                      /**< FW Update. */
    pin_name_t rst;                     /**< Reset. */
    pin_name_t int_pin;                 /**< Interrupt. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} zigbee_cfg_t;

typedef struct
{
    uint8_t error_code;
    uint8_t *error_desc;
} zigbee_error_type;

/**
 * @brief ZigBee Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ZIGBEE_OK = 0,
    ZIGBEE_ERROR = -1

} zigbee_return_value_t;

/*!
 * @addtogroup zigbee ZigBee Click Driver
 * @brief API for configuring and manipulating ZigBee Click driver.
 * @{
 */

/**
 * @brief ZigBee configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #zigbee_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void zigbee_cfg_setup ( zigbee_cfg_t *cfg );

/**
 * @brief ZigBee initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #zigbee_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t zigbee_init ( zigbee_t *ctx, zigbee_cfg_t *cfg );

/**
 * @brief ZigBee data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t zigbee_generic_write ( zigbee_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief ZigBee data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 */
err_t zigbee_generic_read ( zigbee_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Function merges two string and sends it to device.
 * @details This function is used to send AT command plus parameter that it needs.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @param[in] at_buf : Pointer to at macro defined in driver.
 * @param[in] suffix_buf : Pointer to string that concats to at_buf.
 * @return Nothing.
**/
void zigbee_send_at ( zigbee_t *ctx, uint8_t *at_buf, uint8_t *suffix_buf );

/**
 * @brief Function sends string to device.
 * @details This function is used to send commands via UART.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @param[in] cmd_buf : String that will be sent to device.
 * @return Nothing.
**/
void zigbee_send_cmd ( zigbee_t *ctx, uint8_t *cmd_buf );

/**
 * @brief Function checking driver buffer string.
 * @details This function is checking driver buffer for the codes.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to data.
 * @return @li @c 0x00 - ZIGBEE_OP_WAIT,
 *         @li @c 0xAA - ZIGBEE_OP_OK,
 *         @li @c 0xBB - ZIGBEE_OP_ERROR,
 *         @li @c 0xCC - ZIGBEE_OP_NL.
**/
uint8_t zigbee_resp ( zigbee_t *ctx, char *data_in );

/**
 * @brief Function for converting error code to error message.
 * @details This function is used for converting error code to error message.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @param[in] error_code : Error hex code.
 * @return Returns string for certain error_code
**/
char *zigbee_error_handler ( zigbee_t *ctx, uint8_t error_code );

/**
 * @brief Function setting RST pin status.
 * @details This function is used for setting state of the RST pin.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @param[in] status : Pin status.
 * @return Nothing.
**/
void zigbee_set_pin_rst ( zigbee_t *ctx, uint8_t status );

/**
 * @brief Function setting FW pin status.
 * @details This function is used for setting state of the FW pin.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @param[in] status : Pin status.
 * @return Nothing.
**/
void zigbee_set_pin_fw ( zigbee_t *ctx, uint8_t status );

/**
 * @brief Function getting INT pin status.
 * @details This function is used for getting the state of INT pin.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @return Returns pin status.
**/
uint8_t zigbee_get_pin_int ( zigbee_t *ctx );

/**
 * @brief Function for reseting device.
 * @details This function is used for restarting device.
 * @param[in] ctx : Click context object.
 * See #zigbee_t object definition for detailed explanation.
 * @return Nothing.
**/
void zigbee_restart ( zigbee_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ZIGBEE_H

/*! @} */ // zigbee

// ------------------------------------------------------------------------ END
