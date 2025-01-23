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
 * @file bt840.h
 * @brief This file contains API for BT840 Click Driver.
 */

#ifndef BT840_H
#define BT840_H

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
 * @addtogroup bt840 BT840 Click Driver
 * @brief API for configuring and manipulating BT840 Click driver.
 * @{
 */

/**
 * @defgroup bt840_cmd BT840 Device Settings
 * @brief Settings for registers of BT840 Click driver.
 */

/**
 * @addtogroup bt840_cmd
 * @{
 */

/**
 * @brief BT840 control commands.
 * @details Specified setting for control commands of BT840 Click driver.
 */
#define BT840_CMD_AT                                "AT"
#define BT840_CMD_RESET                             "AT+RESET"
#define BT840_CMD_DEFAULT_RESET                     "AT+DEFAULT"
#define BT840_CMD_SAVE_SETTINGS                     "AT+SAVE"
#define BT840_CMD_DEVICE_NAME                       "AT+NAME"
#define BT840_CMD_GET_SW_VERSION                    "AT+VERSION"
#define BT840_CMD_GET_CONNECTED_RSSI                "AT+RSSI"
#define BT840_CMD_GET_MAC                           "AT+ADDR"
#define BT840_CMD_DISCONNECT                        "AT+DISCON"

/**
 * @brief BT840 device response for AT commands.
 * @details Device response after commands.
 */
#define BT840_RSP_OK                                "OK"
#define BT840_RSP_FAIL                              "FAIL"
#define BT840_RSP_END_LINE                          "\r\n"
#define BT840_RSP_CONNECTED                         "+CONNECTED"
#define BT840_RSP_DISCONNECTED                      "+DISCONNECTED"
#define BT840_RSP_SEND                              "SEND"
#define BT840_RSP_RECEIVE                           "+B"

/**
 * @brief BT840 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BT840_TX_DRV_BUFFER_SIZE                    200
#define BT840_RX_DRV_BUFFER_SIZE                    600

/*! @} */ // bt840_cmd

/**
 * @defgroup bt840_map BT840 MikroBUS Map
 * @brief MikroBUS pin mapping of BT840 Click driver.
 */

/**
 * @addtogroup bt840_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BT840 Click to the selected MikroBUS.
 */
#define BT840_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cmd = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // bt840_map
/*! @} */ // bt840

/**
 * @brief BT840 Click context object.
 * @details Context object definition of BT840 Click driver.
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
    uint8_t uart_rx_buffer[ BT840_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ BT840_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ BT840_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} bt840_t;

/**
 * @brief BT840 Click configuration object.
 * @details Configuration object definition of BT840 Click driver.
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

} bt840_cfg_t;

/**
 * @brief BT840 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BT840_OK = 0,
    BT840_ERROR = -1,
    BT840_ERROR_TIMEOUT = -2,
    BT840_ERROR_CMD = -3

} bt840_return_value_t;

/*!
 * @addtogroup bt840 BT840 Click Driver
 * @brief API for configuring and manipulating BT840 Click driver.
 * @{
 */

/**
 * @brief BT840 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bt840_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bt840_cfg_setup ( bt840_cfg_t *cfg );

/**
 * @brief BT840 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bt840_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt840_init ( bt840_t *ctx, bt840_cfg_t *cfg );

/**
 * @brief BT840 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt840_generic_write ( bt840_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BT840 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt840_generic_read ( bt840_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BT840 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bt840_set_rst_pin ( bt840_t *ctx, uint8_t state );

/**
 * @brief BT840 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bt840_reset_device ( bt840_t *ctx );

/**
 * @brief BT840 set WUP pin function.
 * @details This function sets the wake-up pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bt840_set_wup_pin ( bt840_t *ctx, uint8_t state );

/**
 * @brief BT840 wakeup device function.
 * @details This function wakes UP the device by toggling the wake-up pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bt840_wakeup_device ( bt840_t *ctx );

/**
 * @brief BT840 set cmd mode function.
 * @details This function sets the command mode by setting the CMD pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bt840_set_cmd_mode ( bt840_t *ctx );

/**
 * @brief BT840 set data mode function.
 * @details This function sets the data mode by setting the CMD pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bt840_set_data_mode ( bt840_t *ctx );

/**
 * @brief BT840 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BT840_CMD_x definitions.
 * @return None.
 * @note None.
 */
void bt840_cmd_run ( bt840_t *ctx, uint8_t *cmd );

/**
 * @brief BT840 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BT840_CMD_x definitions.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void bt840_cmd_set ( bt840_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief BT840 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see BT840_CMD_x definitions.
 * @return None.
 * @note None.
 */
void bt840_cmd_get ( bt840_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // BT840_H

/*! @} */ // bt840

// ------------------------------------------------------------------------ END
