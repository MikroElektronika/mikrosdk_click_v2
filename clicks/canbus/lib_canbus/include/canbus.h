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
 * @file canbus.h
 * @brief This file contains API for CAN Bus Click Driver.
 */

#ifndef CANBUS_H
#define CANBUS_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup canbus CAN Bus Click Driver
 * @brief API for configuring and manipulating CAN Bus Click driver.
 * @{
 */

/**
 * @defgroup canbus_set CAN Bus Device Settings
 * @brief Settings for registers of CAN Bus Click driver.
 */

/**
 * @addtogroup canbus_set
 * @{
 */

/**
 * @brief CAN Bus driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // canbus_set

/**
 * @defgroup canbus_map CAN Bus MikroBUS Map
 * @brief MikroBUS pin mapping of CAN Bus Click driver.
 */

/**
 * @addtogroup canbus_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CAN Bus Click to the selected MikroBUS.
 */
#define CANBUS_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // canbus_map
/*! @} */ // canbus

/**
 * @brief CAN Bus Click context object.
 * @details Context object definition of CAN Bus Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t stb;                       /**< Standby pin. */

    // Modules

    uart_t uart;                             /**< UART driver object. */

    // Buffers

    char uart_rx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */

} canbus_t;

/**
 * @brief CAN Bus Click configuration object.
 * @details Configuration object definition of CAN Bus Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t rx_pin;                       /**< RX pin. */
    pin_name_t tx_pin;                       /**< TX pin. */

    // Additional gpio pins

    pin_name_t stb;                          /**< Standby pin: 
                                                  low for high-speed operation, 
                                                  high to place the device in low-current standby mode. */

    // Static variable

    uint32_t          baud_rate;             /**< Clock speed. */
    bool              uart_blocking;         /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;              /**< Data bits. */
    uart_parity_t     parity_bit;            /**< Parity bit. */
    uart_stop_bits_t  stop_bit;              /**< Stop bits. */

} canbus_cfg_t;

/**
 * @brief CAN Bus Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CANBUS_OK = 0,
   CANBUS_ERROR = -1

} canbus_return_value_t;

/*!
 * @addtogroup canbus CAN Bus Click Driver
 * @brief API for configuring and manipulating CAN Bus Click driver.
 * @{
 */

/**
 * @brief CAN Bus configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #canbus_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void canbus_cfg_setup ( canbus_cfg_t *cfg );

/**
 * @brief CAN Bus initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #canbus_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #canbus_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canbus_init ( canbus_t *ctx, canbus_cfg_t *cfg );

/**
 * @brief CAN Bus default configuration function.
 * @details This function executes a default configuration of CAN Bus
 * click board.
 * @param[in] ctx : Click context object.
 * See #canbus_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t canbus_default_cfg ( canbus_t *ctx );

/**
 * @brief CAN Bus data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #canbus_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canbus_generic_write ( canbus_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief CAN Bus data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #canbus_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canbus_generic_read ( canbus_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief CAN Bus low current standby mode function.
 * @details This function enables the low current standby mode by 
 * sets the STB ( AN ) pin on the high level
 * of the CAN Bus click board™.
 * @param[in] ctx : Click context object.
 * See #canbus_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canbus_set_low_current_standby_mode ( canbus_t *ctx );

/**
 * @brief CAN Bus high speed mode function.
 * @details This function enables the high speed operation mode by 
 * clears the STB ( AN ) pin on the low level 
 * of the CAN Bus click board™.
 * @param[in] ctx : Click context object.
 * See #canbus_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canbus_set_high_speed_mode ( canbus_t *ctx );

/**
 * @brief CAN Bus send data function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #canbus_t object definition for detailed explanation.
 * @param[out] tx_data : Output read data.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canbus_send_data ( canbus_t *ctx, char *tx_data );

#ifdef __cplusplus
}
#endif
#endif // CANBUS_H

/*! @} */ // canbus

// ------------------------------------------------------------------------ END
