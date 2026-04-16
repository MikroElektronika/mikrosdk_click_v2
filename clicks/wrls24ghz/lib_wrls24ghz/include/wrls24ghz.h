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
 * @file wrls24ghz.h
 * @brief This file contains API for WRLS 2.4GHz Click Driver.
 */

#ifndef WRLS24GHZ_H
#define WRLS24GHZ_H

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
 * @addtogroup wrls24ghz WRLS 2.4GHz Click Driver
 * @brief API for configuring and manipulating WRLS 2.4GHz Click driver.
 * @{
 */

/**
 * @defgroup wrls24ghz_cmd WRLS 2.4GHz Device Settings
 * @brief Settings of WRLS 2.4GHz Click driver.
 */

/**
 * @addtogroup wrls24ghz_cmd
 * @{
 */

/**
 * @brief WRLS 2.4GHz control commands.
 * @details Specified setting for control commands of WRLS 2.4GHz Click driver.
 */
#define WRLS24GHZ_CMD_BEGIN                     "<"
#define WRLS24GHZ_CMD_END                       ">"
#define WRLS24GHZ_CMD_SET_NAME(NAME)            "<ST_NAME="NAME">"
#define WRLS24GHZ_CMD_READ_NAME                 "<RD_NAME>"
#define WRLS24GHZ_CMD_SET_ADVERTISING(X)        "<ST_ADV_ONOFF="X">"
#define WRLS24GHZ_CMD_READ_ADVERTISING          "<RD_ADV_ONOFF>"
#define WRLS24GHZ_CMD_SET_ADVERTISING_DATA(X)   "<ST_ADV_DATA="X">"
#define WRLS24GHZ_CMD_READ_ADVERTISING_DATA     "<RD_ADV_DATA>"
#define WRLS24GHZ_CMD_SET_ADVERTISING_GAP(X)    "<ST_ADV_GAP="X">"
#define WRLS24GHZ_CMD_READ_ADVERTISING_GAP      "<RD_ADV_GAP>"
#define WRLS24GHZ_CMD_DISCONNECT_LINK           "<ST_DISCONNECT_LINK>"
#define WRLS24GHZ_CMD_READ_CONNECTION_STATUS    "<RD_LINK>"
#define WRLS24GHZ_CMD_SET_TX_POWER(X)           "<ST_TX_POWER="X">"
#define WRLS24GHZ_CMD_READ_TX_POWER             "<RD_TX_POWER>"
#define WRLS24GHZ_CMD_BLE_RESET                 "<ST_RESET_BLE>"
#define WRLS24GHZ_CMD_SET_BAUD(X)               "<ST_BAUD="X">"
#define WRLS24GHZ_CMD_READ_BAUD                 "<RD_BAUD>"
#define WRLS24GHZ_CMD_SET_CON_MIN_GAP(X)        "<ST_CON_MIN_GAP="X">"
#define WRLS24GHZ_CMD_READ_CON_MIN_GAP          "<RD_CON_MIN_GAP>"
#define WRLS24GHZ_CMD_SET_CON_MAX_GAP(X)        "<ST_CON_MAX_GAP="X">"
#define WRLS24GHZ_CMD_READ_CON_MAX_GAP          "<RD_CON_MAX_GAP>"
#define WRLS24GHZ_CMD_SET_CON_TIMEOUT(X)        "<ST_CON_TIMEOUT="X">"
#define WRLS24GHZ_CMD_READ_CON_TIMEOUT          "<RD_CON_TIMEOUT>"
#define WRLS24GHZ_CMD_SET_MAC(X)                "<ST_OWN_MAC="X">"
#define WRLS24GHZ_CMD_READ_MAC                  "<RD_BLE_MAC>"
#define WRLS24GHZ_CMD_CANCEL_SET_MAC            WRLS24GHZ_CMD_SET_MAC(0)
#define WRLS24GHZ_CMD_SET_UART_PARITY(X)        "<ST_UART_PARITY="X">"
#define WRLS24GHZ_CMD_READ_UART_PARITY          "<RD_UART_PARITY>"
#define WRLS24GHZ_CMD_SET_SLEEP_DELAY(X)        "<ST_SLEEP_DELAY="X">"
#define WRLS24GHZ_CMD_READ_SLEEP_DELAY          "<RD_SLEEP_DELAY>"
#define WRLS24GHZ_CMD_FACTORY_RESET             "<ST_FACTORY>"
#define WRLS24GHZ_CMD_SET_CH_NAME(X)            "<ST_CH_NAME="X">"
#define WRLS24GHZ_CMD_READ_CH_NAME              "<RD_CH_NAME>"
#define WRLS24GHZ_CMD_SET_SECRET(X)             "<ST_SECRET="X">"
#define WRLS24GHZ_CMD_CLEAR_SECRET              "<ST_CLEAR_SECRET>"
#define WRLS24GHZ_CMD_READ_SECRET               "<RD_SECRET>"
#define WRLS24GHZ_CMD_ENABLE_APP_CONFIG         "<ST_APP_CONFIG>"
#define WRLS24GHZ_CMD_SET_WAKE_ONCE             "<ST_WAKE=ONCE>"
#define WRLS24GHZ_CMD_SET_WAKE_FOREVER          "<ST_WAKE=FOREVER>"
#define WRLS24GHZ_CMD_SET_WAKE_NORMAL           "<ST_WAKE=NORMAL>"
#define WRLS24GHZ_CMD_READ_WAKE                 "<RD_WAKE>"
#define WRLS24GHZ_CMD_SET_RX_LOW_WAKEUP(X)      "<ST_RX_LOW_WAKEUP="X">"
#define WRLS24GHZ_CMD_READ_RX_LOW_WAKEUP        "<RD_RX_LOW_WAKEUP>"
#define WRLS24GHZ_CMD_READ_SOFT_VERSION         "<RD_SOFT_VERSION>"

/**
 * @brief WRLS 2.4GHz timeout settings.
 * @details Specified timeout settings of WRLS 2.4GHz Click driver.
 */
#define WRLS24GHZ_WAIT_TIMEOUT_5000MS           5000
#define WRLS24GHZ_WAIT_TIMEOUT_10000MS          10000
#define WRLS24GHZ_WAIT_TIMEOUT_INFINITE         0

/**
 * @brief WRLS 2.4GHz driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define WRLS24GHZ_TX_DRV_BUFFER_SIZE            256
#define WRLS24GHZ_RX_DRV_BUFFER_SIZE            256

/*! @} */ // wrls24ghz_cmd

/**
 * @defgroup wrls24ghz_map WRLS 2.4GHz MikroBUS Map
 * @brief MikroBUS pin mapping of WRLS 2.4GHz Click driver.
 */

/**
 * @addtogroup wrls24ghz_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of WRLS 2.4GHz Click to the selected MikroBUS.
 */
#define WRLS24GHZ_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.status = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // wrls24ghz_map
/*! @} */ // wrls24ghz

/**
 * @brief WRLS 2.4GHz Click context object.
 * @details Context object definition of WRLS 2.4GHz Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active high). */

    // Input pins
    digital_in_t status;            /**< Connection active status pin (active high). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ WRLS24GHZ_RX_DRV_BUFFER_SIZE ]; /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ WRLS24GHZ_TX_DRV_BUFFER_SIZE ]; /**< TX Buffer size. */

} wrls24ghz_t;

/**
 * @brief WRLS 2.4GHz Click configuration object.
 * @details Configuration object definition of WRLS 2.4GHz Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active high). */
    pin_name_t status;              /**< Connection active status pin (active high). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} wrls24ghz_cfg_t;

/**
 * @brief WRLS 2.4GHz Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WRLS24GHZ_OK = 0,
    WRLS24GHZ_ERROR = -1

} wrls24ghz_return_value_t;

/*!
 * @addtogroup wrls24ghz WRLS 2.4GHz Click Driver
 * @brief API for configuring and manipulating WRLS 2.4GHz Click driver.
 * @{
 */

/**
 * @brief WRLS 2.4GHz configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #wrls24ghz_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void wrls24ghz_cfg_setup ( wrls24ghz_cfg_t *cfg );

/**
 * @brief WRLS 2.4GHz initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wrls24ghz_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wrls24ghz_init ( wrls24ghz_t *ctx, wrls24ghz_cfg_t *cfg );

/**
 * @brief WRLS 2.4GHz data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wrls24ghz_generic_write ( wrls24ghz_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WRLS 2.4GHz data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wrls24ghz_generic_read ( wrls24ghz_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief WRLS 2.4GHz set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void wrls24ghz_set_rst_pin ( wrls24ghz_t *ctx, uint8_t state );

/**
 * @brief WRLS 2.4GHz get STATUS pin function.
 * @details This function returns the connection active status (STATUS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t wrls24ghz_get_status_pin ( wrls24ghz_t *ctx );

/**
 * @brief WRLS 2.4GHz reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void wrls24ghz_reset_device ( wrls24ghz_t *ctx );

/**
 * @brief WRLS 2.4GHz send cmd function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void wrls24ghz_send_cmd ( wrls24ghz_t *ctx, uint8_t *cmd );

/**
 * @brief WRLS 2.4GHz wake UART function.
 * @details This function wakes the module up by sending a dummy byte by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void wrls24ghz_wake_uart ( wrls24ghz_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // WRLS24GHZ_H

/*! @} */ // wrls24ghz

// ------------------------------------------------------------------------ END
