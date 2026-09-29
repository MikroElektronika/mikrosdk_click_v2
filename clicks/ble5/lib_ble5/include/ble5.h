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
 * @file ble5.h
 * @brief This file contains API for BLE 5 Click Driver.
 */

#ifndef BLE5_H
#define BLE5_H

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
 * @addtogroup ble5 BLE 5 Click Driver
 * @brief API for configuring and manipulating BLE 5 Click driver.
 * @{
 */

/**
 * @defgroup ble5_cmd BLE 5 Device Settings
 * @brief Settings of BLE 5 Click driver.
 */

/**
 * @addtogroup ble5_cmd
 * @{
 */

/**
 * @brief BLE 5 control commands.
 * @details Command identifiers for the BLE 5 Click AT firmware. Parameters are
 * binary bytes separated by commas, as specified by the command protocol.
 * @note Based on Toshiba Bluetooth SDK 3.4, section 9.6. Command availability
 * depends on the installed firmware.
 */
#define BLE5_CMD_SYSSBAUD                           "AT+SYSSBAUD"
#define BLE5_CMD_SYSSBDADDR                         "AT+SYSSBDADDR"
#define BLE5_CMD_SYSSBDADDRNVM                      "AT+SYSSBDADDRNVM"
#define BLE5_CMD_SYSGBDADDR                         "AT+SYSGBDADDR"
#define BLE5_CMD_SYSSTXPOW                          "AT+SYSSTXPOW"
#define BLE5_CMD_SYSGENVRSSI                        "AT+SYSGENVRSSI"
#define BLE5_CMD_SYSREADRSSI                        "AT+SYSREADRSSI"
#define BLE5_CMD_SYSGETNVMINFO                      "AT+SYSGETNVMINFO"
#define BLE5_CMD_SYSWRNVM                           "AT+SYSWRNVM"
#define BLE5_CMD_SYSRDNVM                           "AT+SYSRDNVM"
#define BLE5_CMD_SYSERSNVM                          "AT+SYSERSNVM"
#define BLE5_CMD_SYSRDSWVERSION                     "AT+SYSRDSWVERSION"
#define BLE5_CMD_LESCAN                             "AT+LESCAN"
#define BLE5_CMD_LEGDEVS                            "AT+LEGDEVS"
#define BLE5_CMD_LECON                              "AT+LECON"
#define BLE5_CMD_LEDISCON                           "AT+LEDISCON"
#define BLE5_CMD_LECONINFO                          "AT+LECONINFO"
#define BLE5_CMD_LECONUPD                           "AT+LECONUPD"
#define BLE5_CMD_LEGRSSI                            "AT+LEGRSSI"
#define BLE5_CMD_LEADV                              "AT+LEADV"
#define BLE5_CMD_LESRANDOM                          "AT+LESRANDOM"
#define BLE5_CMD_LECONDEVS                          "AT+LECONDEVS"
#define BLE5_CMD_LERESOLVADDR                       "AT+LERESOLVADDR"
#define BLE5_CMD_LEGENOOBDATA                       "AT+LEGENOOBDATA"
#define BLE5_CMD_GSADDPROF                          "AT+GSADDPROF"
#define BLE5_CMD_GSREGPROF                          "AT+GSREGPROF"
#define BLE5_CMD_GSADDSVC                           "AT+GSADDSVC"
#define BLE5_CMD_GSADDCHAR                          "AT+GSADDCHAR"
#define BLE5_CMD_GSADDDESC                          "AT+GSADDDESC"
#define BLE5_CMD_GSUPDVAL                           "AT+GSUPDVAL"
#define BLE5_CMD_GSRDUPD                            "AT+GSRDUPD"
#define BLE5_CMD_GSWRUPD                            "AT+GSWRUPD"
#define BLE5_CMD_GSSRVMTU                           "AT+GSSRVMTU"
#define BLE5_CMD_GSSRVNOT                           "AT+GSSRVNOT"
#define BLE5_CMD_GSSRVIND                           "AT+GSSRVIND"
#define BLE5_CMD_SECSETPARAM                        "AT+SECSETPARAM"
#define BLE5_CMD_SECBOND                            "AT+SECBOND"
#define BLE5_CMD_SECBONDACCEPT                      "AT+SECBONDACCEPT"
#define BLE5_CMD_SECUNBOND                          "AT+SECUNBOND"
#define BLE5_CMD_SECBONDDEVS                        "AT+SECBONDDEVS"
#define BLE5_CMD_SECDISPKEYEV                       "AT+SECDISPKEYEV"
#define BLE5_CMD_SECENTKEYEV                        "AT+SECENTKEYEV"
#define BLE5_CMD_SECLEGACYOOBDATAREQEV              "AT+SECLEGACYOOBDATAREQEV"
#define BLE5_CMD_SECOOBDATAREQEV                    "AT+SECOOBDATAREQEV"
#define BLE5_CMD_SECNUMCOMPVEREV                    "AT+SECNUMCOMPVEREV"
#define BLE5_CMD_SECCFMPKEY                         "AT+SECCFMPKEY"
#define BLE5_CMD_SECLEGACYOOBDATA                   "AT+SECLEGACYOOBDATA"
#define BLE5_CMD_SECOOBDATA                         "AT+SECOOBDATA"
#define BLE5_CMD_SECREJPAIR                         "AT+SECREJPAIR"
#define BLE5_CMD_LESPPINIT                          "AT+LESPPINIT"
#define BLE5_CMD_LESPPSCAN                          "AT+LESPPSCAN"
#define BLE5_CMD_LESPPADV                           "AT+LESPPADV"
#define BLE5_CMD_LESPPCONN                          "AT+LESPPCONN"
#define BLE5_CMD_GSSRVSPPTXDATA                     "AT+GSSRVSPPTXDATA"

/**
 * @brief BLE 5 responses and events.
 * @details Identifiers used to recognize BLE 5 Click command replies and
 * asynchronous events. Binary parameters follow the identifier and separator.
 */
#define BLE5_RSP_OK                                 "+OK"
#define BLE5_RSP_ERROR                              "+ERR"
#define BLE5_RSP_READY                              "+SYSRDY="
#define BLE5_RSP_VERSION                            "+SWVERSION="
#define BLE5_RSP_ADDRESS                            "+BDADDR="
#define BLE5_EVT_PREFIX                             "+EV "
#define BLE5_EVT_CONNECTED                          "+EV LE_CONN_COMPLETED_EVENT "
#define BLE5_EVT_DISCONNECTED                       "+EV LE_DISCONN_EVENT "
#define BLE5_EVT_MTU_REQUEST                        "+EV SERVER_MTU_REQUEST_EVENT "
#define BLE5_EVT_READ                               "+EV SERVER_READ_EVENT "
#define BLE5_EVT_WRITE                              "+EV SERVER_WRITE_EVENT "
#define BLE5_EVT_WRITE_COMMAND                      "+EV SERVER_WRITE_COMMAND_EVENT "

/**
 * @brief BLE 5 packet settings.
 * @details BLE 5 Click packets contain a three-byte little-endian total length
 * and a CR/LF terminator. Command parameters use big-endian byte order, except
 * characteristic and descriptor values, which retain their GATT byte order.
 */
#define BLE5_PACKET_HEADER_SIZE                     3
#define BLE5_PACKET_END_SIZE                        2
#define BLE5_CMD_BUFFER_SIZE                        256
#define BLE5_STATUS_SUCCESS                         0x00
#define BLE5_ATT_MTU_DEFAULT                        23
#define BLE5_ATT_VALUE_SIZE                         20
#define BLE5_UUID_16_BIT                            0x00
#define BLE5_UUID_128_BIT                           0x01
#define BLE5_CHAR_READ                              0x02
#define BLE5_CHAR_WRITE_COMMAND                     0x04
#define BLE5_CHAR_WRITE                             0x08
#define BLE5_CHAR_NOTIFY                            0x10

/**
 * @brief BLE 5 GATT profile and packet settings.
 * @details IDs and offsets used by the Nordic UART service protocol.
 */
#define BLE5_GAP_PROFILE_ID                         1
#define BLE5_UART_PROFILE_ID                        2
#define BLE5_DEVICE_NAME_CHARACTERISTIC_ID          1
#define BLE5_APPEARANCE_CHARACTERISTIC_ID           2
#define BLE5_UART_RX_CHARACTERISTIC_ID              1
#define BLE5_UART_TX_CHARACTERISTIC_ID              2
#define BLE5_VALUE_ELEMENT_ID                       1
#define BLE5_CCCD_ELEMENT_ID                        2
#define BLE5_CCCD_VALUE_SIZE                        2
#define BLE5_ATTRIBUTE_HEADER_SIZE                  11
#define BLE5_ATTRIBUTE_VALUE_OFFSET                 12
#define BLE5_NOTIFICATION_PREFIX_SIZE               9
#define BLE5_NOTIFICATION_CONNECTION_HIGH_OFFSET    6
#define BLE5_NOTIFICATION_CONNECTION_LOW_OFFSET     7
#define BLE5_NOTIFICATION_SEPARATOR_OFFSET          8
#define BLE5_NOTIFICATION_VALUE_OFFSET              9

/**
 * @brief BLE 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BLE5_TX_DRV_BUFFER_SIZE                     300
#define BLE5_RX_DRV_BUFFER_SIZE                     600

/*! @} */ // ble5_cmd

/**
 * @defgroup ble5_map BLE 5 MikroBUS Map
 * @brief MikroBUS pin mapping of BLE 5 Click driver.
 */

/**
 * @addtogroup ble5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLE 5 Click to the selected MikroBUS.
 */
#define BLE5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.wp0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ble5_map
/*! @} */ // ble5

/**
 * @brief BLE 5 Click context object.
 * @details Context object definition of BLE 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp0;                          /**< Wake-up 0 output. */
    digital_out_t rst;                          /**< Active-low reset output. */
    digital_out_t rts;                          /**< UART request-to-send output. */
    digital_out_t wp1;                          /**< Wake-up 1 output. */

    // Input pins
    digital_in_t cts;                           /**< UART clear-to-send input. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BLE5_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ BLE5_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} ble5_t;

/**
 * @brief BLE 5 Click configuration object.
 * @details Configuration object definition of BLE 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t wp0;                             /**< Wake-up 0 pin. */
    pin_name_t rst;                             /**< Reset pin. */
    pin_name_t rts;                             /**< UART request-to-send pin. */
    pin_name_t wp1;                             /**< Wake-up 1 pin. */
    pin_name_t cts;                             /**< UART clear-to-send pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} ble5_cfg_t;

/**
 * @brief BLE 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BLE5_OK = 0,
    BLE5_ERROR = -1,
    BLE5_ERROR_TIMEOUT = -2,
    BLE5_ERROR_CMD = -3,
    BLE5_ERROR_OVERFLOW = -4

} ble5_return_value_t;

/*!
 * @addtogroup ble5 BLE 5 Click Driver
 * @brief API for configuring and manipulating BLE 5 Click driver.
 * @{
 */

/**
 * @brief BLE 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ble5_cfg_t object definition for detailed explanation.
 * @return None.
 * @note The all used pins will be set to unconnected state.
 */
void ble5_cfg_setup ( ble5_cfg_t *cfg );

/**
 * @brief BLE 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ble5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ble5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble5_init ( ble5_t *ctx, ble5_cfg_t *cfg );

/**
 * @brief BLE 5 default configuration function.
 * @details This function sets the BLE 5 Click wake-up and RTS outputs high,
 * then resets the module to start its preprogrammed AT firmware.
 * @param[in] ctx : Click context object.
 * See #ble5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Set MODE to Standalone. Wait for BLE5_RSP_READY before sending commands.
 */
err_t ble5_default_cfg ( ble5_t *ctx );

/**
 * @brief BLE 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ble5_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble5_generic_write ( ble5_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BLE 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ble5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble5_generic_read ( ble5_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BLE 5 command running function.
 * @details This function sends a BLE 5 Click command without parameters,
 * including the packet length and CR/LF terminator.
 * @param[in] ctx : Click context object.
 * @param[in] cmd : Null-terminated command identifier, including AT+.
 * @return @li @c 0 - Packet sent,
 *         @li @c -1 - Invalid argument or UART error,
 *         @li @c -2 - UART transmit timeout.
 * @note Read the command reply separately. Getter commands use this function.
 */
err_t ble5_cmd_run ( ble5_t *ctx, uint8_t *cmd );

/**
 * @brief BLE 5 command setting function.
 * @details This function sends a BLE 5 Click command with binary parameters,
 * including the packet length, parameter separator, and CR/LF terminator.
 * @param[in] ctx : Click context object.
 * @param[in] cmd : Null-terminated command identifier, including AT+.
 * @param[in] params : Binary parameters with comma separators, or NULL if empty.
 * @param[in] len : Parameter length in bytes, including any zero bytes.
 * @return @li @c 0 - Packet sent,
 *         @li @c -1 - Invalid argument or UART error,
 *         @li @c -2 - UART transmit timeout.
 * @note Read the command reply separately. The complete packet must fit
 * BLE5_CMD_BUFFER_SIZE. Do not use strlen to size binary parameters.
 */
err_t ble5_cmd_set ( ble5_t *ctx, uint8_t *cmd, uint8_t *params, uint16_t len );

/**
 * @brief BLE 5 hardware reset function.
 * @details This function pulses the BLE 5 Click reset pin low for 100 ms and
 * clears the UART buffers before releasing reset.
 * @param[in] ctx : Click context object.
 * @return None.
 * @note Reset clears the runtime GATT configuration. Wait for BLE5_RSP_READY.
 */
void ble5_device_reset ( ble5_t *ctx );

/**
 * @brief BLE 5 wake-up 0 setting function.
 * @details This function sets the BLE 5 Click WP0 output level.
 * @param[in] ctx : Click context object.
 * @param[in] state : Output level, 0 or 1.
 * @return None.
 * @note None.
 */
void ble5_set_wp0_pin ( ble5_t *ctx, uint8_t state );

/**
 * @brief BLE 5 wake-up 1 setting function.
 * @details This function sets the BLE 5 Click WP1 output level.
 * @param[in] ctx : Click context object.
 * @param[in] state : Output level, 0 or 1.
 * @return None.
 * @note None.
 */
void ble5_set_wp1_pin ( ble5_t *ctx, uint8_t state );

/**
 * @brief BLE 5 RTS setting function.
 * @details This function sets the BLE 5 Click RTS output level.
 * @param[in] ctx : Click context object.
 * @param[in] state : Output level, 0 or 1.
 * @return None.
 * @note None.
 */
void ble5_set_rts_pin ( ble5_t *ctx, uint8_t state );

/**
 * @brief BLE 5 CTS reading function.
 * @details This function reads the BLE 5 Click CTS input level.
 * @param[in] ctx : Click context object.
 * @return Pin level, 0 or 1.
 * @note None.
 */
uint8_t ble5_get_cts_pin ( ble5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BLE5_H

/*! @} */ // ble5

// ------------------------------------------------------------------------ END
