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
 * @file irnss.h
 * @brief This file contains API for IRNSS Click Driver.
 */

#ifndef IRNSS_H
#define IRNSS_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup irnss IRNSS Click Driver
 * @brief API for configuring and manipulating IRNSS Click driver.
 * @{
 */

/**
 * @defgroup irnss_set IRNSS Device Settings
 * @brief Settings for registers of IRNSS Click driver.
 */

/**
 * @addtogroup irnss_set
 * @{
 */

/**
 * @brief IRNSS driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_TX_BUFFER_SIZE                       100
#define DRV_RX_BUFFER_SIZE                       700

/*! @} */ // irnss_set

/**
 * @defgroup irnss_map IRNSS MikroBUS Map
 * @brief MikroBUS pin mapping of IRNSS Click driver.
 */

/**
 * @addtogroup irnss_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IRNSS Click to the selected MikroBUS.
 */
#define IRNSS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wkp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \

/*! @} */ // irnss_map
/*! @} */ // irnss

/**
 * @brief IRNSS Click context object.
 * @details Context object definition of IRNSS Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Description. */
    digital_out_t wkp;                          /**< Description. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

} irnss_t;

/**
 * @brief IRNSS Click configuration object.
 * @details Configuration object definition of IRNSS Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                            /**< Description. */
    pin_name_t wkp;                            /**< Description. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} irnss_cfg_t;

/*!
 * @addtogroup irnss IRNSS Click Driver
 * @brief API for configuring and manipulating IRNSS Click driver.
 * @{
 */

/**
 * @brief IRNSS configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irnss_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irnss_cfg_setup ( irnss_cfg_t *cfg );

/**
 * @brief IRNSS initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irnss_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irnss_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irnss_init ( irnss_t *ctx, irnss_cfg_t *cfg );

/**
 * @brief IRNSS data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #irnss_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irnss_generic_write ( irnss_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief IRNSS data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #irnss_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irnss_generic_read ( irnss_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Sets state of the @b rst pin setting.
 * @details This function sets @b rst pin output to
 * @b state setting.
 * @param[in] ctx Click context object.
 * See irnss_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out low,
 *         @li @c  1 - digital out high.
 */
void irnss_set_rst_pin_state ( irnss_t *ctx, uint8_t state );

/**
 * @brief Sets state of the @b wkp pin setting.
 * @details This function sets @b wkp pin output to
 * @b state setting.
 * @param[in] ctx Click context object.
 * See irnss_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out low,
 *         @li @c  1 - digital out high.
 */
void irnss_set_wkp_pin_state ( irnss_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // IRNSS_H

/*! @} */ // irnss

// ------------------------------------------------------------------------ END
