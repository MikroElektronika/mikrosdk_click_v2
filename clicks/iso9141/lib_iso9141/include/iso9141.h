/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file iso9141.h
 * @brief This file contains API for ISO 9141 Click Driver.
 */

#ifndef ISO9141_H
#define ISO9141_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup iso9141 ISO 9141 Click Driver
 * @brief API for configuring and manipulating ISO 9141 Click driver.
 * @{
 */

/**
 * @defgroup iso9141_set ISO 9141 Device Settings
 * @brief Settings for registers of ISO 9141 Click driver.
 */

/**
 * @addtogroup iso9141_set
 * @{
 */

/**
 * @brief ISO 9141 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ISO9141_TX_DRV_BUFFER_SIZE      100
#define ISO9141_RX_DRV_BUFFER_SIZE      300

/*! @} */ // iso9141_set

/**
 * @defgroup iso9141_map ISO 9141 MikroBUS Map
 * @brief MikroBUS pin mapping of ISO 9141 Click driver.
 */

/**
 * @addtogroup iso9141_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISO 9141 Click to the selected MikroBUS.
 */
#define ISO9141_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \

/*! @} */ // iso9141_map
/*! @} */ // iso9141

/**
 * @brief ISO 9141 Click context object.
 * @details Context object definition of ISO 9141 Click driver.
 */
typedef struct
{
    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ ISO9141_RX_DRV_BUFFER_SIZE ];   /**< Buffer size. */
    uint8_t uart_tx_buffer[ ISO9141_TX_DRV_BUFFER_SIZE ];   /**< Buffer size. */

} iso9141_t;

/**
 * @brief ISO 9141 Click configuration object.
 * @details Configuration object definition of ISO 9141 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} iso9141_cfg_t;

/**
 * @brief ISO 9141 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISO9141_OK = 0,
    ISO9141_ERROR = -1

} iso9141_return_value_t;

/*!
 * @addtogroup iso9141 ISO 9141 Click Driver
 * @brief API for configuring and manipulating ISO 9141 Click driver.
 * @{
 */

/**
 * @brief ISO 9141 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #iso9141_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void iso9141_cfg_setup ( iso9141_cfg_t *cfg );

/**
 * @brief ISO 9141 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #iso9141_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #iso9141_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iso9141_init ( iso9141_t *ctx, iso9141_cfg_t *cfg );

/**
 * @brief ISO 9141 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iso9141_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iso9141_generic_write ( iso9141_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief ISO 9141 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #iso9141_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t iso9141_generic_read ( iso9141_t *ctx, uint8_t *data_buf, uint16_t max_len );

#ifdef __cplusplus
}
#endif
#endif // ISO9141_H

/*! @} */ // iso9141

// ------------------------------------------------------------------------ END
