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
 * @file barcode3.h
 * @brief This file contains API for Barcode 3 Click Driver.
 */

#ifndef BARCODE3_H
#define BARCODE3_H

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
 * @addtogroup barcode3 Barcode 3 Click Driver
 * @brief API for configuring and manipulating Barcode 3 Click driver.
 * @{
 */

/**
 * @defgroup barcode3_cmd Barcode 3 Device Settings
 * @brief Settings for registers of Barcode 3 Click driver.
 */

/**
 * @addtogroup barcode3_cmd
 * @{
 */

/**
 * @brief Barcode 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BARCODE3_TX_DRV_BUFFER_SIZE     50
#define BARCODE3_RX_DRV_BUFFER_SIZE     1000

/*! @} */ // barcode3_cmd

/**
 * @defgroup barcode3_map Barcode 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Barcode 3 Click driver.
 */

/**
 * @addtogroup barcode3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barcode 3 Click to the selected MikroBUS.
 */
#define BARCODE3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.trg = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // barcode3_map
/*! @} */ // barcode3

/**
 * @brief Barcode 3 Click context object.
 * @details Context object definition of Barcode 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Device reset pin (active low). */
    digital_out_t trg;                  /**< Trigger scanning pin (active low). */

    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BARCODE3_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ BARCODE3_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} barcode3_t;

/**
 * @brief Barcode 3 Click configuration object.
 * @details Configuration object definition of Barcode 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Device reset pin (active low). */
    pin_name_t trg;                     /**< Trigger scanning pin (active low). */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} barcode3_cfg_t;

/**
 * @brief Barcode 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BARCODE3_OK = 0,
    BARCODE3_ERROR = -1

} barcode3_return_value_t;

/*!
 * @addtogroup barcode3 Barcode 3 Click Driver
 * @brief API for configuring and manipulating Barcode 3 Click driver.
 * @{
 */

/**
 * @brief Barcode 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barcode3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barcode3_cfg_setup ( barcode3_cfg_t *cfg );

/**
 * @brief Barcode 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #barcode3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barcode3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barcode3_init ( barcode3_t *ctx, barcode3_cfg_t *cfg );

/**
 * @brief Barcode 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #barcode3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barcode3_generic_write ( barcode3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Barcode 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #barcode3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barcode3_generic_read ( barcode3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Barcode 3 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #barcode3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void barcode3_set_rst_pin ( barcode3_t *ctx, uint8_t state );

/**
 * @brief Barcode 3 set trg pin function.
 * @details This function sets the TRG pin logic state.
 * @param[in] ctx : Click context object.
 * See #barcode3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void barcode3_set_trg_pin ( barcode3_t *ctx, uint8_t state );

/**
 * @brief Barcode 3 reset device function.
 * @details This function resets the device by toggling the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #barcode3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void barcode3_reset_device ( barcode3_t *ctx );

/**
 * @brief Barcode 3 start scanning function.
 * @details This function starts the barcode scanning by setting the TRG pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #barcode3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void barcode3_start_scanning ( barcode3_t *ctx );

/**
 * @brief Barcode 3 stop scanning function.
 * @details This function stops the barcode scanning by setting the TRG pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #barcode3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void barcode3_stop_scanning ( barcode3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BARCODE3_H

/*! @} */ // barcode3

// ------------------------------------------------------------------------ END
