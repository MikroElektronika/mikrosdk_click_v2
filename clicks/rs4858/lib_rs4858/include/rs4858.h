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
 * @file rs4858.h
 * @brief This file contains API for RS485 8 Click Driver.
 */

#ifndef RS4858_H
#define RS4858_H

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
 * @addtogroup rs4858 RS485 8 Click Driver
 * @brief API for configuring and manipulating RS485 8 Click driver.
 * @{
 */

/**
 * @defgroup rs4858_cmd RS485 8 Device Settings
 * @brief Settings for registers of RS485 8 Click driver.
 */

/**
 * @addtogroup rs4858_cmd
 * @{
 */

/**
 * @brief RS485 8 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RS4858_TX_DRV_BUFFER_SIZE    100
#define RS4858_RX_DRV_BUFFER_SIZE    300

/*! @} */ // rs4858_cmd

/**
 * @defgroup rs4858_map RS485 8 MikroBUS Map
 * @brief MikroBUS pin mapping of RS485 8 Click driver.
 */

/**
 * @addtogroup rs4858_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RS485 8 Click to the selected MikroBUS.
 */
#define RS4858_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // rs4858_map
/*! @} */ // rs4858

/**
 * @brief RS485 8 Click context object.
 * @details Context object definition of RS485 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;  /**< Enable device pin. */

    // Modules
    uart_t uart;       /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ RS4858_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ RS4858_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} rs4858_t;

/**
 * @brief RS485 8 Click configuration object.
 * @details Configuration object definition of RS485 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t en;                      /**< Enable device pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} rs4858_cfg_t;

/**
 * @brief RS485 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RS4858_OK = 0,
    RS4858_ERROR = -1

} rs4858_return_value_t;

/*!
 * @addtogroup rs4858 RS485 8 Click Driver
 * @brief API for configuring and manipulating RS485 8 Click driver.
 * @{
 */

/**
 * @brief RS485 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rs4858_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rs4858_cfg_setup ( rs4858_cfg_t *cfg );

/**
 * @brief RS485 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rs4858_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rs4858_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4858_init ( rs4858_t *ctx, rs4858_cfg_t *cfg );

/**
 * @brief RS485 8 default configuration function.
 * @details This function executes a default configuration of RS485 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #rs4858_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void rs4858_default_cfg ( rs4858_t *ctx );

/**
 * @brief RS485 8 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs4858_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4858_generic_write ( rs4858_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief RS485 8 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs4858_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4858_generic_read ( rs4858_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief RS485 8 enable the device function.
 * @details This function is used to enable the RS485 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4858_enable_device ( rs4858_t *ctx );

/**
 * @brief RS485 8 disable the device function.
 * @details This function is used to disable the RS485 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4858_disable_device ( rs4858_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RS4858_H

/*! @} */ // rs4858

// ------------------------------------------------------------------------ END
