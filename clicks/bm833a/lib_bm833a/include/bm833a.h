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
 * @file bm833a.h
 * @brief This file contains API for BM833A Click Driver.
 */

#ifndef BM833A_H
#define BM833A_H

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
 * @addtogroup bm833a BM833A Click Driver
 * @brief API for configuring and manipulating BM833A Click driver.
 * @{
 */

/**
 * @defgroup bm833a_cmd BM833A Device Settings
 * @brief Settings for registers of BM833A Click driver.
 */

/**
 * @addtogroup bm833a_cmd
 * @{
 */

/**
 * @brief BM833A control commands.
 * @details Specified setting for control commands of BM833A Click driver.
 */
#define BM833A_CMD_AT                               "AT"
#define BM833A_CMD_RESET                            "AT+RESET"
#define BM833A_CMD_DEFAULT_RESET                    "AT+DEFAULT"
#define BM833A_CMD_SAVE_SETTINGS                    "AT+SAVE"
#define BM833A_CMD_DEVICE_NAME                      "AT+NAME"
#define BM833A_CMD_GET_SW_VERSION                   "AT+VERSION"
#define BM833A_CMD_GET_CONNECTED_RSSI               "AT+RSSI"
#define BM833A_CMD_GET_MAC                          "AT+ADDR"
#define BM833A_CMD_DISCONNECT                       "AT+DISCON"

/**
 * @brief BM833A device response for AT commands.
 * @details Device response after commands.
 */
#define BM833A_RSP_OK                               "OK"
#define BM833A_RSP_FAIL                             "FAIL"
#define BM833A_RSP_SEND                             "SEND"

/**
 * @brief BM833A device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define BM833A_URC_CONNECTED                        "+CONNECTED"
#define BM833A_URC_DISCONNECTED                     "+DISCONNECTED"
#define BM833A_URC_RECEIVE                          "+B"

/**
 * @brief BM833A device response time for AT commands.
 * @details Device response time after commands.
 */
#define BM833A_MAX_RSP_TIME_DEFAULT                 5000ul
#define BM833A_MAX_RSP_TIME_RESET                   30000ul
#define BM833A_MAX_RSP_TIME_BLE_CONNECT             180000ul

/**
 * @brief BM833A driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BM833A_TX_DRV_BUFFER_SIZE                   200
#define BM833A_RX_DRV_BUFFER_SIZE                   600

/*! @} */ // bm833a_cmd

/**
 * @defgroup bm833a_map BM833A MikroBUS Map
 * @brief MikroBUS pin mapping of BM833A Click driver.
 */

/**
 * @addtogroup bm833a_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BM833A Click to the selected MikroBUS.
 */
#define BM833A_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cmd = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // bm833a_map
/*! @} */ // bm833a

/**
 * @brief BM833A Click context object.
 * @details Context object definition of BM833A Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wup;              /**< UART wake-up pin (active low). */
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cmd;              /**< Command/Data pin (high:command, low:data). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BM833A_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ BM833A_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ BM833A_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} bm833a_t;

/**
 * @brief BM833A Click configuration object.
 * @details Configuration object definition of BM833A Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t wup;                 /**< UART wake-up pin (active low). */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cmd;                 /**< Command/Data pin (high:command, low:data). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} bm833a_cfg_t;

/**
 * @brief BM833A Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BM833A_OK = 0,
    BM833A_ERROR = -1,
    BM833A_ERROR_TIMEOUT = -2,
    BM833A_ERROR_CMD = -3

} bm833a_return_value_t;

/*!
 * @addtogroup bm833a BM833A Click Driver
 * @brief API for configuring and manipulating BM833A Click driver.
 * @{
 */

/**
 * @brief BM833A configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bm833a_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bm833a_cfg_setup ( bm833a_cfg_t *cfg );

/**
 * @brief BM833A initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bm833a_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm833a_init ( bm833a_t *ctx, bm833a_cfg_t *cfg );

/**
 * @brief BM833A data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm833a_generic_write ( bm833a_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BM833A data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm833a_generic_read ( bm833a_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BM833A set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bm833a_set_rst_pin ( bm833a_t *ctx, uint8_t state );

/**
 * @brief BM833A reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bm833a_reset_device ( bm833a_t *ctx );

/**
 * @brief BM833A set WUP pin function.
 * @details This function sets the wake-up pin logic state.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bm833a_set_wup_pin ( bm833a_t *ctx, uint8_t state );

/**
 * @brief BM833A wakeup device function.
 * @details This function wakes UP the device by toggling the wake-up pin logic state.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bm833a_wakeup_device ( bm833a_t *ctx );

/**
 * @brief BM833A set cmd mode function.
 * @details This function sets the command mode by setting the CMD pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bm833a_set_cmd_mode ( bm833a_t *ctx );

/**
 * @brief BM833A set data mode function.
 * @details This function sets the data mode by setting the CMD pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bm833a_set_data_mode ( bm833a_t *ctx );

/**
 * @brief BM833A cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BM833A_CMD_x definitions.
 * @return None.
 * @note None.
 */
void bm833a_cmd_run ( bm833a_t *ctx, uint8_t *cmd );

/**
 * @brief BM833A cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BM833A_CMD_x definitions.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void bm833a_cmd_set ( bm833a_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief BM833A cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BM833A_CMD_x definitions.
 * @return None.
 * @note None.
 */
void bm833a_cmd_get ( bm833a_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // BM833A_H

/*! @} */ // bm833a

// ------------------------------------------------------------------------ END
