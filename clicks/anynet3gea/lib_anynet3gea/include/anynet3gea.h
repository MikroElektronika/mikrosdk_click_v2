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
 * @file anynet3gea.h
 * @brief This file contains API for AnyNet 3G-EA Click Driver.
 */

#ifndef ANYNET3GEA_H
#define ANYNET3GEA_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup anynet3gea AnyNet 3G-EA Click Driver
 * @brief API for configuring and manipulating AnyNet 3G-EA Click driver.
 * @{
 */

/**
 * @defgroup anynet3gea_set AnyNet 3G-EA Device Settings
 * @brief Settings for registers of AnyNet 3G-EA Click driver.
 */

/**
 * @addtogroup anynet3gea_set
 * @{
 */

/**
 * @brief AnyNet 3G-EA control commands.
 * @details Specified setting for control commands of AnyNet 3G-EA Click driver.
 */
#define ANYNET3GEA_CMD_AT                           "AT"
#define ANYNET3GEA_CMD_QCCID                        "AT+QCCID"
#define ANYNET3GEA_CMD_GSN                          "AT+GSN"
#define ANYNET3GEA_CMD_AWSVER                       "AT+AWSVER"
#define ANYNET3GEA_CMD_AWSRESET                     "AT+AWSRESET"
#define ANYNET3GEA_CMD_AWSSTATE                     "AT+AWSSTATE"
#define ANYNET3GEA_CMD_AWSBUTTON                    "AT+AWSBUTTON"
#define ANYNET3GEA_CMD_AWSPUBOPEN                   "AT+AWSPUBOPEN"
#define ANYNET3GEA_CMD_AWSPUBLISH                   "AT+AWSPUBLISH"
#define ANYNET3GEA_CMD_AWSSUBOPEN                   "AT+AWSSUBOPEN"
#define ANYNET3GEA_CMD_AWSPUBCLOSE                  "AT+AWSPUBCLOSE"

/**
 * @brief AnyNet 3G-EA device response for AT commands.
 * @details Device response after commands.
 */
#define ANYNET3GEA_RSP_OK                           "OK"
#define ANYNET3GEA_RSP_ERROR                        "ERROR"
#define ANYNET3GEA_RSP_READY_FOR_SEND               ">"
#define ANYNET3GEA_RSP_SEND_OK                      "SEND OK"
#define ANYNET3GEA_RSP_SEND_FAIL                    "SEND FAIL"

/**
 * @brief AnyNet 3G-EA driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ANYNET3GEA_RX_DRV_BUFFER_SIZE               256
#define ANYNET3GEA_TX_DRV_BUFFER_SIZE               256

/*! @} */ // anynet3gea_set

/**
 * @defgroup anynet3gea_map AnyNet 3G-EA MikroBUS Map
 * @brief MikroBUS pin mapping of AnyNet 3G-EA Click driver.
 */

/**
 * @addtogroup anynet3gea_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AnyNet 3G-EA Click to the selected MikroBUS.
 */
#define ANYNET3GEA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dsr = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dtr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.iot = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // anynet3gea_map
/*! @} */ // anynet3gea

/**
 * @brief AnyNet 3G-EA Click context object.
 * @details Context object definition of AnyNet 3G-EA Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t slp;      /**< Sleep mode. */
    digital_out_t dtr;      /**< DTR handshake */
    digital_out_t iot;      /**< IoT button pin. */

    // Input pins
    digital_in_t dsr;       /**< DSR handshake. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ ANYNET3GEA_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    uint8_t uart_tx_buffer[ ANYNET3GEA_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} anynet3gea_t;

/**
 * @brief AnyNet 3G-EA Click configuration object.
 * @details Configuration object definition of AnyNet 3G-EA Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t slp;         /**< Sleep mode. */
    pin_name_t dtr;         /**< DTR handshake */
    pin_name_t iot;         /**< IoT button pin. */
    pin_name_t dsr;         /**< DSR handshake. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} anynet3gea_cfg_t;

/**
 * @brief AnyNet 3G-EA Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANYNET3GEA_OK = 0,
    ANYNET3GEA_ERROR = -1,
    ANYNET3GEA_ERROR_TIMEOUT = -2,
    ANYNET3GEA_ERROR_CMD = -3,
    ANYNET3GEA_ERROR_SEND = -4,
    ANYNET3GEA_ERROR_UNKNOWN = -5

} anynet3gea_return_value_t;

/*!
 * @addtogroup anynet3gea AnyNet 3G-EA Click Driver
 * @brief API for configuring and manipulating AnyNet 3G-EA Click driver.
 * @{
 */

/**
 * @brief AnyNet 3G-EA configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #anynet3gea_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void anynet3gea_cfg_setup ( anynet3gea_cfg_t *cfg );

/**
 * @brief AnyNet 3G-EA initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #anynet3gea_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t anynet3gea_init ( anynet3gea_t *ctx, anynet3gea_cfg_t *cfg );

/**
 * @brief AnyNet 3G-EA data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t anynet3gea_generic_write ( anynet3gea_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief AnyNet 3G-EA data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t anynet3gea_generic_read ( anynet3gea_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief AnyNet 3G-EA set slp pin function.
 * @details This function sets the Sleep mode (SLP) pin logic state.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void anynet3gea_set_slp_pin ( anynet3gea_t *ctx, uint8_t state );

/**
 * @brief AnyNet 3G-EA set dtr pin function.
 * @details This function sets the DTR handshake pin logic state.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void anynet3gea_set_dtr_pin ( anynet3gea_t *ctx, uint8_t state );

/**
 * @brief AnyNet 3G-EA set iot pin function.
 * @details This function sets the IoT button pin logic state.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void anynet3gea_set_iot_pin ( anynet3gea_t *ctx, uint8_t state );

/**
 * @brief AnyNet 3G-EA get dsr pin function.
 * @details This function returns the DSR handshake pin logic state.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t anynet3gea_get_dsr_pin ( anynet3gea_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void anynet3gea_send_cmd ( anynet3gea_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void anynet3gea_send_cmd_with_par ( anynet3gea_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command status.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void anynet3gea_send_cmd_check ( anynet3gea_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command parameters.
 * @param[in] ctx : Click context object.
 * See #anynet3gea_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void anynet3gea_send_cmd_par_check ( anynet3gea_t *ctx, uint8_t *at_cmd_buf );

#ifdef __cplusplus
}
#endif
#endif // ANYNET3GEA_H

/*! @} */ // anynet3gea

// ------------------------------------------------------------------------ END
