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
 * @file lr14.h
 * @brief This file contains API for LR 14 Click Driver.
 */

#ifndef LR14_H
#define LR14_H

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
 * @addtogroup lr14 LR 14 Click Driver
 * @brief API for configuring and manipulating LR 14 Click driver.
 * @{
 */

/**
 * @defgroup lr14_cmd LR 14 Device Settings
 * @brief Settings for registers of LR 14 Click driver.
 */

/**
 * @addtogroup lr14_cmd
 * @{
 */

/**
 * @brief LR 14 control commands.
 * @details Specified setting for control commands of LR 14 Click driver.
 */
#define LR14_CMD_AT                                 "AT"
#define LR14_CMD_TOGGLE_ECHO                        "ATE"
#define LR14_CMD_FACTORY_RESET                      "ATR"
#define LR14_CMD_GET_MODEL_ID                       "AT+HWMODEL"
#define LR14_CMD_GET_FW_VERSION                     "AT+VER"
#define LR14_CMD_GET_SERIAL_NUMBER                  "AT+SN"
#define LR14_CMD_NETWORK_WORK_MODE                  "AT+NWM"
#define LR14_CMD_P2P_MODE_FREQUENCY                 "AT+PFREQ"
#define LR14_CMD_P2P_MODE_SPREADING_FACTOR          "AT+PSF"
#define LR14_CMD_P2P_MODE_BANDWIDTH                 "AT+PBW"
#define LR14_CMD_P2P_MODE_CODE_RATE                 "AT+PCR"
#define LR14_CMD_P2P_MODE_PREAMBLE_LENGTH           "AT+PPL"
#define LR14_CMD_P2P_MODE_TX_POWER                  "AT+PTP"
#define LR14_CMD_P2P_RX_MODE                        "AT+PRECV"
#define LR14_CMD_P2P_TX_MODE                        "AT+PSEND"

/**
 * @brief LR 14 device response for AT commands.
 * @details Device response after commands.
 */
#define LR14_RSP_OK                                 "OK"
#define LR14_RSP_ERROR                              "AT_ERROR"
#define LR14_RSP_PARAM_ERROR                        "AT_PARAM_ERROR"
#define LR14_RSP_BUSY_ERROR                         "AT_BUSY_ERROR"
#define LR14_RSP_TEST_PARAM_OVERFLOW                "AT_TEST_PARAM_OVERFLOW"
#define LR14_RSP_NO_CLASSB_ENABLE                   "AT_NO_CLASSB_ENABLE"
#define LR14_RSP_NO_NETWORK_JOINED                  "AT_NO_NETWORK_JOINED"
#define LR14_RSP_RX_ERROR                           "AT_RX_ERROR"
#define LR14_RSP_INITIAL                            "----------------------"

/**
 * @brief LR 14 device events settings.
 * @details Device events settings.
 */
#define LR14_EVT_RX_P2P                             "+EVT:RXP2P"
#define LR14_EVT_RX_P2P_ERROR                       "+EVT:RXP2P RECEIVE ERROR"
#define LR14_EVT_RX_P2P_TIMEOUT                     "+EVT:RXP2P RECEIVE TIMEOUT"
#define LR14_EVT_TX_P2P                             "+EVT:TXP2P"

/**
 * @brief LR 14 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LR14_TX_DRV_BUFFER_SIZE                     200
#define LR14_RX_DRV_BUFFER_SIZE                     600

/*! @} */ // lr14_cmd

/**
 * @defgroup lr14_map LR 14 MikroBUS Map
 * @brief MikroBUS pin mapping of LR 14 Click driver.
 */

/**
 * @addtogroup lr14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR 14 Click to the selected MikroBUS.
 */
#define LR14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // lr14_map
/*! @} */ // lr14

/**
 * @brief LR 14 Click context object.
 * @details Context object definition of LR 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LR14_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LR14_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LR14_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} lr14_t;

/**
 * @brief LR 14 Click configuration object.
 * @details Configuration object definition of LR 14 Click driver.
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

} lr14_cfg_t;

/**
 * @brief LR 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LR14_OK = 0,
    LR14_ERROR = -1,
    LR14_ERROR_TIMEOUT = -2,
    LR14_ERROR_CMD = -3

} lr14_return_value_t;

/*!
 * @addtogroup lr14 LR 14 Click Driver
 * @brief API for configuring and manipulating LR 14 Click driver.
 * @{
 */

/**
 * @brief LR 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lr14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lr14_cfg_setup ( lr14_cfg_t *cfg );

/**
 * @brief LR 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lr14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lr14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr14_init ( lr14_t *ctx, lr14_cfg_t *cfg );

/**
 * @brief LR 14 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr14_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr14_generic_write ( lr14_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LR 14 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr14_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr14_generic_read ( lr14_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LR 14 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr14_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lr14_set_rst_pin ( lr14_t *ctx, uint8_t state );

/**
 * @brief LR 14 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lr14_reset_device ( lr14_t *ctx );

/**
 * @brief LR 14 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #lr14_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lr14_cmd_run ( lr14_t *ctx, uint8_t *cmd );

/**
 * @brief LR 14 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lr14_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void lr14_cmd_set ( lr14_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LR 14 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #lr14_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lr14_cmd_get ( lr14_t *ctx, uint8_t *cmd );

/**
 * @brief LR 14 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lr14_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lr14_cmd_help ( lr14_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // LR14_H

/*! @} */ // lr14

// ------------------------------------------------------------------------ END
