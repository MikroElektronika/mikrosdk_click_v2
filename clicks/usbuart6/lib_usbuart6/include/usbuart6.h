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
 * @file usbuart6.h
 * @brief This file contains API for USB UART 6 Click Driver.
 */

#ifndef USBUART6_H
#define USBUART6_H

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
 * @addtogroup usbuart6 USB UART 6 Click Driver
 * @brief API for configuring and manipulating USB UART 6 Click driver.
 * @{
 */

/**
 * @defgroup usbuart6_cmd USB UART 6 Device Settings
 * @brief Settings for registers of USB UART 6 Click driver.
 */

/**
 * @addtogroup usbuart6_cmd
 * @{
 */

/**
 * @brief USB UART 6 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define USBUART6_TX_DRV_BUFFER_SIZE    200
#define USBUART6_RX_DRV_BUFFER_SIZE    200

/*! @} */ // usbuart6_cmd

/**
 * @defgroup usbuart6_map USB UART 6 MikroBUS Map
 * @brief MikroBUS pin mapping of USB UART 6 Click driver.
 */

/**
 * @addtogroup usbuart6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB UART 6 Click to the selected MikroBUS.
 */
#define USBUART6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // usbuart6_map
/*! @} */ // usbuart6

/**
 * @brief USB UART 6 Click context object.
 * @details Context object definition of USB UART 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;               /**< Enable pin (active high). */
    digital_out_t cts;              /**< UART CTS pin. */

    // Input pins
    digital_in_t rts;               /**< UART RTS pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ USBUART6_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ USBUART6_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} usbuart6_t;

/**
 * @brief USB UART 6 Click configuration object.
 * @details Configuration object definition of USB UART 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t en;                  /**< Enable pin (active high). */
    pin_name_t cts;                 /**< UART CTS pin. */
    pin_name_t rts;                 /**< UART RTS pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} usbuart6_cfg_t;

/**
 * @brief USB UART 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBUART6_OK = 0,
    USBUART6_ERROR = -1

} usbuart6_return_value_t;

/*!
 * @addtogroup usbuart6 USB UART 6 Click Driver
 * @brief API for configuring and manipulating USB UART 6 Click driver.
 * @{
 */

/**
 * @brief USB UART 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbuart6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbuart6_cfg_setup ( usbuart6_cfg_t *cfg );

/**
 * @brief USB UART 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #usbuart6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbuart6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuart6_init ( usbuart6_t *ctx, usbuart6_cfg_t *cfg );

/**
 * @brief USB UART 6 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #usbuart6_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuart6_generic_write ( usbuart6_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief USB UART 6 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #usbuart6_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuart6_generic_read ( usbuart6_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief USB UART 6 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #usbuart6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void usbuart6_enable_device ( usbuart6_t *ctx );

/**
 * @brief USB UART 6 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #usbuart6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void usbuart6_disable_device ( usbuart6_t *ctx );

/**
 * @brief USB UART 6 set CTS pin function.
 * @details This function sets the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #usbuart6_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void usbuart6_set_cts_pin ( usbuart6_t *ctx, uint8_t state );

/**
 * @brief USB UART 6 get RTS pin function.
 * @details This function returns the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #usbuart6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t usbuart6_get_rts_pin ( usbuart6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBUART6_H

/*! @} */ // usbuart6

// ------------------------------------------------------------------------ END
