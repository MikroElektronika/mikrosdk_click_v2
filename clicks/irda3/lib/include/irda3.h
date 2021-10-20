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
 * @file irda3.h
 * @brief This file contains API for IrDA 3 Click Driver.
 */

#ifndef IRDA3_H
#define IRDA3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup irda3 IrDA 3 Click Driver
 * @brief API for configuring and manipulating IrDA 3 Click driver.
 * @{
 */

/**
 * @defgroup irda3_set IrDA 3 Device Settings
 * @brief Settings for registers of IrDA 3 Click driver.
 */

/**
 * @addtogroup irda3_set
 * @{
 */

/**
 * @brief IrDA 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       500

/*! @} */ // irda3_set

/**
 * @defgroup irda3_map IrDA 3 MikroBUS Map
 * @brief MikroBUS pin mapping of IrDA 3 Click driver.
 */

/**
 * @addtogroup irda3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IrDA 3 Click to the selected MikroBUS.
 */
#define IRDA3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.mod = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \

/*! @} */ // irda3_map
/*! @} */ // irda3

/**
 * @brief IrDA 3 Click context object.
 * @details Context object definition of IrDA 3 Click driver.
 */
typedef struct
{
    // Output pins
    
    digital_out_t mod;      /**< Description. */
    digital_out_t rst;      /**< Description. */
    digital_out_t en;       /**< Description. */
   
    // Modules
    
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} irda3_t;

/**
 * @brief IrDA 3 Click configuration object.
 * @details Configuration object definition of IrDA 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    
    pin_name_t mod;          /**< Description. */
    pin_name_t rst;        /**< Description. */
    pin_name_t en;          /**< Description. */

    // Static variable
    
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} irda3_cfg_t;

/**
 * @brief IrDA 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   IRDA3_OK = 0,
   IRDA3_ERROR = -1

} irda3_return_value_t;

/**
 * @brief Click mode settings.
 */
typedef enum
{
    IRDA3_MODE_CMD = 0,
    IRDA3_MODE_DATA

} irda3_mode_t;

/**
 * @brief Click power mode settings.
 */
typedef enum
{
    IRDA3_PWR_OFF = 0,
    IRDA3_PWR_ON

} irda3_pwr_t;

/*!
 * @addtogroup irda3 IrDA 3 Click Driver
 * @brief API for configuring and manipulating IrDA 3 Click driver.
 * @{
 */

/**
 * @brief IrDA 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irda3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irda3_cfg_setup ( irda3_cfg_t *cfg );

/**
 * @brief IrDA 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irda3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irda3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irda3_init ( irda3_t *ctx, irda3_cfg_t *cfg );

/**
 * @brief IrDA 3 default configuration function.
 * @details This function executes a default configuration of IrDA 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #irda3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void irda3_default_cfg ( irda3_t *ctx );

/**
 * @brief Mode Setup function.
 * @details This function allows IrDA 3 click mode to be set.
 * @param ctx  Click object.
 * @param state  0 - Command mode,
 *               1 - Data mode.
 * @return Nothing
 * @note None.
 */
void irda3_mode_setup( irda3_t *ctx, irda3_mode_t state );

/**
 * @brief Power Setup function.
 * @details This function allows IrDA 3 click power mode to be set.
 * @param ctx  Click object.
 * @param state  0 - Power off,
 *               1 - Power on.
 * @return Nothing
 * @note None.
 */
void irda3_pwr_setup( irda3_t *ctx, irda3_pwr_t state );

/**
 * @brief Reset function.
 * @details This function executes a device reset operation.
 * @param ctx  Click object.
 *
 * @return Nothing
 * @note After the reset operation was done, the device will be returned back
 *       to normal mode.
 */
void irda3_reset( irda3_t *ctx );

/**
 * @brief Generic Multiple Send function.
 * @details This function allows data sending operation of multiple data
 *              bytes to be performed.
 * @param ctx  Click object.
 * @param tx_data  Data to be sent.
 * @return Nothing
 * @note None.
 */
void irda3_generic_multiple_send( irda3_t *ctx, char *tx_data );

/**
 * @brief Generic Multiple Receive function.
 * @details This function allows data receiving operation of multiple data
 *              bytes to be performed.
 * @param ctx  Click object.
 * @param rx_data  Memory where read data be stored.
 * @param termination_char  Termination character.
 * @return Nothing
 * @note The function will receive data bytes from the device until termination
 *       character was received. At the end of the received data buffer, this
 *       function will add '\0' character.
 */
void irda3_generic_multiple_receive( irda3_t *ctx, char *rx_data, char termination_char );

/**
 * @brief Generic Single Send function.
 * @details This function allows data sending operation of single data byte
 *              to be performed.
 * @param ctx  Click object.
 * @param tx_data  Data to be sent.
 * @return Nothing
 * @note None.
 */
void irda3_generic_single_send( irda3_t *ctx, char tx_data );

/**
 * @brief Generic Single Receive function.
 * @details This function allows data receiving operation of single data
 *              byte to be performed.
 * @param ctx  Click object.
 *
 * @returns Received data byte.
 * @note None.
 */
char irda3_generic_single_receive( irda3_t *ctx );
#ifdef __cplusplus
}
#endif
#endif // IRDA3_H

/*! @} */ // irda3
