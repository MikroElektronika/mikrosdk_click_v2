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
 * @file obdii.h
 * @brief This file contains API for OBDII Click Driver.
 */

#ifndef OBDII_H
#define OBDII_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup obdii OBDII Click Driver
 * @brief API for configuring and manipulating OBDII Click driver.
 * @{
 */

/**
 * @defgroup obdii_cmd OBDII Device Settings
 * @brief Settings for registers of OBDII Click driver.
 */

/**
 * @addtogroup obdii_cmd
 * @{
 */

/**
 * @brief OBDII control commands.
 * @details Specified setting for control commands of OBDII Click driver.
 */
#define OBDII_CMD_FIRMWARE_VERSION      "ATI"
#define OBDII_CMD_DISABLE_ECHO          "ATE0"
#define OBDII_CMD_ENABLE_ECHO           "ATE1"
#define OBDII_CMD_AUTO_PROTOCOL         "ATSP0"
#define OBDII_CMD_SPACES_OFF            "ATS0"
#define OBDII_CMD_RESET_DEFAULT         "ATD"
#define OBDII_CMD_RESET_DEVICE          "ATZ"
#define OBDII_CMD_GET_CURRENT_RPM       "010C"
#define OBDII_CMD_GET_CURRENT_SPEED     "010D"

/**
 * @brief OBDII device response for AT commands.
 * @details Device response after commands.
 */
#define OBDII_RSP_OK                    "OK"
#define OBDII_RSP_UNKNOWN_CMD           "ERROR"
#define OBDII_RSP_PROMPT                ">"
#define OBDII_RSP_CURRENT_RPM           "410C"
#define OBDII_RSP_CURRENT_SPEED         "410D"

/**
 * @brief OBDII driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define OBDII_TX_DRV_BUFFER_SIZE        100
#define OBDII_RX_DRV_BUFFER_SIZE        300

/*! @} */ // obdii_cmd

/**
 * @defgroup obdii_map OBDII MikroBUS Map
 * @brief MikroBUS pin mapping of OBDII Click driver.
 */

/**
 * @addtogroup obdii_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of OBDII Click to the selected MikroBUS.
 */
#define OBDII_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // obdii_map
/*! @} */ // obdii

/**
 * @brief OBDII Click context object.
 * @details Context object definition of OBDII Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active low). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ OBDII_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ OBDII_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} obdii_t;

/**
 * @brief OBDII Click configuration object.
 * @details Configuration object definition of OBDII Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t int_pin;         /**< Interrupt pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} obdii_cfg_t;

/**
 * @brief OBDII Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    OBDII_OK = 0,
    OBDII_ERROR = -1,
    OBDII_ERROR_TIMEOUT = -2

} obdii_return_value_t;

/*!
 * @addtogroup obdii OBDII Click Driver
 * @brief API for configuring and manipulating OBDII Click driver.
 * @{
 */

/**
 * @brief OBDII configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #obdii_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void obdii_cfg_setup ( obdii_cfg_t *cfg );

/**
 * @brief OBDII initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #obdii_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #obdii_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t obdii_init ( obdii_t *ctx, obdii_cfg_t *cfg );

/**
 * @brief OBDII data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #obdii_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t obdii_generic_write ( obdii_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief OBDII data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #obdii_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t obdii_generic_read ( obdii_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief OBDII send command function.
 * @details This function sends command string by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #obdii_t object definition for detailed explanation.
 * @param[in] cmd : Command string to send.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void obdii_send_command ( obdii_t *ctx, uint8_t *cmd );

/**
 * @brief OBDII reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #obdii_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void obdii_reset_device ( obdii_t *ctx );

/**
 * @brief OBDII set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #obdii_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void obdii_set_rst_pin ( obdii_t *ctx, uint8_t state );

/**
 * @brief OBDII get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #obdii_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t obdii_get_int_pin ( obdii_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OBDII_H

/*! @} */ // obdii

// ------------------------------------------------------------------------ END
