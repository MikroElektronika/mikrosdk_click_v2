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
 * @file wifinina.h
 * @brief This file contains API for WiFi NINA Click Driver.
 */

#ifndef WIFININA_H
#define WIFININA_H

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
 * @addtogroup wifinina WiFi NINA Click Driver
 * @brief API for configuring and manipulating WiFi NINA Click driver.
 * @{
 */

/**
 * @defgroup wifinina_cmd WiFi NINA Device Settings
 * @brief Settings of WiFi NINA Click driver.
 */

/**
 * @addtogroup wifinina_cmd
 * @{
 */

/**
 * @brief WiFi NINA control commands.
 * @details Specified setting for control commands of WiFi NINA Click driver.
 */
#define WIFININA_CMD_AT                         "AT"
#define WIFININA_CMD_GET_MODEL_ID               "AT+GMM"
#define WIFININA_CMD_GET_SW_VERSION             "AT+GMR"
#define WIFININA_CMD_GET_SERIAL_NUM             "AT+GSN"
#define WIFININA_CMD_FACTORY_RESET              "AT+UFACTORY"
#define WIFININA_CMD_REBOOT_DEVICE              "AT+CPWROFF"
#define WIFININA_CMD_NETWORK_HOST_NAME          "AT+UNHN"
#define WIFININA_CMD_WIFI_STATION_CONFIG        "AT+UWSC"
#define WIFININA_CMD_WIFI_STATION_CONFIG_ACTION "AT+UWSCA"
#define WIFININA_CMD_WIFI_STATION_STATUS        "AT+UWSSTAT"
#define WIFININA_CMD_CONNECT_PEER               "AT+UDCP"
#define WIFININA_CMD_WRITE_DATA                 "AT+UDATW"
#define WIFININA_CMD_READ_DATA                  "AT+UDATR"
#define WIFININA_CMD_CLOSE_PEER                 "AT+UDCPC"
#define WIFININA_CMD_ENTER_DATA_MODE            "ATO1"
#define WIFININA_CMD_ENTER_CMD_MODE             "+++"

/**
 * @brief WiFi NINA device response to AT commands.
 * @details Device response to commands.
 */
#define WIFININA_RSP_OK                         "OK"
#define WIFININA_RSP_ERROR                      "ERROR"

/**
 * @brief WiFi NINA device response time for AT commands.
 * @details Device response time after commands.
 */
#define WIFININA_MAX_AT_DEFAULT                5000ul
#define WIFININA_MAX_BOOT_GREETING             10000ul
#define WIFININA_MAX_FACTORY_RESET             60000ul
#define WIFININA_MAX_REBOOT                    20000ul
#define WIFININA_MAX_WIFI_CONNECT              30000ul
#define WIFININA_MAX_PEER_CONNECT              10000ul
#define WIFININA_MAX_DATA_TXRX                 10000ul
#define WIFININA_MAX_PEER_CLOSE                5000ul
/**
 * @brief WiFi NINA device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define WIFININA_URC_GREETING                   "+STARTUP"
#define WIFININA_URC_WIFI_LINK_CONNECTED        "+UUWLE:"
#define WIFININA_URC_NETWORK_UP                 "+UUNU:"
#define WIFININA_URC_PEER_CONNECTED             "+UUDPC:"
#define WIFININA_URC_PEER_DISCONNECTED          "+UUDPD:"
#define WIFININA_URC_READ_SOCKET_DATA           "+UUDATA:"

/**
 * @brief WiFi NINA driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define WIFININA_TX_DRV_BUFFER_SIZE             200
#define WIFININA_RX_DRV_BUFFER_SIZE             600

/**
 * @brief WiFi NINA pin states.
 * @details Specified pin states of WiFi NINA Click driver.
 */
#define WIFININA_PIN_STATE_HIGH                 0x01
#define WIFININA_PIN_STATE_LOW                  0x00

/*! @} */ // wifinina_cmd

/**
 * @defgroup wifinina_map WiFi NINA MikroBUS Map
 * @brief MikroBUS pin mapping of WiFi NINA Click driver.
 */

/**
 * @addtogroup wifinina_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of WiFi NINA Click to the selected MikroBUS.
 */
#define WIFININA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // wifinina_map
/*! @} */ // wifinina

/**
 * @brief WiFi NINA Click context object.
 * @details Context object definition of WiFi NINA Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset pin (active low). */
    digital_out_t cts;      /**< UART clear to send pin (active low). */

    // Input pins
    digital_in_t rts;       /**< UART request to send pin (active low). */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ WIFININA_RX_DRV_BUFFER_SIZE ];   /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ WIFININA_TX_DRV_BUFFER_SIZE ];   /**< TX Buffer size. */
    uint8_t cmd_buffer[ WIFININA_TX_DRV_BUFFER_SIZE ];       /**< Command buffer. */

} wifinina_t;

/**
 * @brief WiFi NINA Click configuration object.
 * @details Configuration object definition of WiFi NINA Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset pin (active low). */
    pin_name_t cts;                             /**< UART clear to send pin (active low). */
    pin_name_t rts;                             /**< UART request to send pin (active low). */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} wifinina_cfg_t;

/**
 * @brief WiFi NINA Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WIFININA_OK = 0,
    WIFININA_ERROR = -1,
    WIFININA_ERROR_TIMEOUT = -2,
    WIFININA_ERROR_CMD = -3,
    WIFININA_ERROR_UNKNOWN = -4

} wifinina_return_value_t;

/*!
 * @addtogroup wifinina WiFi NINA Click Driver
 * @brief API for configuring and manipulating WiFi NINA Click driver.
 * @{
 */

/**
 * @brief WiFi NINA configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #wifinina_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void wifinina_cfg_setup ( wifinina_cfg_t *cfg );

/**
 * @brief WiFi NINA initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wifinina_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifinina_init ( wifinina_t *ctx, wifinina_cfg_t *cfg );

/**
 * @brief WiFi NINA data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifinina_generic_write ( wifinina_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WiFi NINA data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifinina_generic_read ( wifinina_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief WiFi NINA set rst pin function.
 * @details This function sets the reset (RST) pin logic state.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void wifinina_set_rst_pin ( wifinina_t *ctx, uint8_t pin_state );

/**
 * @brief WiFi NINA set cts pin function.
 * @details This function sets the UART clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void wifinina_set_cts_pin ( wifinina_t *ctx, uint8_t pin_state );

/**
 * @brief WiFi NINA get rts pin function.
 * @details This function returns the UART request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t wifinina_get_rts_pin ( wifinina_t *ctx );

/**
 * @brief WiFi NINA hardware reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void wifinina_hw_reset ( wifinina_t *ctx );

/**
 * @brief WiFi NINA cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #wifinina object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void wifinina_cmd_run ( wifinina_t *ctx, uint8_t *cmd );

/**
 * @brief WiFi NINA cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #wifinina object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void wifinina_cmd_set ( wifinina_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief WiFi NINA cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #wifinina object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void wifinina_cmd_get ( wifinina_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // WIFININA_H

/*! @} */ // wifinina

// ------------------------------------------------------------------------ END
