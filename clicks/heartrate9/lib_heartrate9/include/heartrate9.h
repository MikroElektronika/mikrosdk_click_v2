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
 * @file heartrate9.h
 * @brief This file contains API for Heart Rate 9 Click Driver.
 */

#ifndef HEARTRATE9_H
#define HEARTRATE9_H

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
 * @addtogroup heartrate9 Heart Rate 9 Click Driver
 * @brief API for configuring and manipulating Heart Rate 9 Click driver.
 * @{
 */

/**
 * @defgroup heartrate9_set Heart Rate 9 Device Settings
 * @brief Settings for registers of Heart Rate 9 Click driver.
 */

/**
 * @addtogroup heartrate9_set
 * @{
 */

/**
 * @brief Heart Rate 9 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // heartrate9_set

/**
 * @defgroup heartrate9_map Heart Rate 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Heart Rate 9 Click driver.
 */

/**
 * @addtogroup heartrate9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Heart Rate 9 Click to the selected MikroBUS.
 */
#define HEARTRATE9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \

/*! @} */ // heartrate9_map
/*! @} */ // heartrate9

/**
 * @brief Heart Rate 9 Click context object.
 * @details Context object definition of Heart Rate 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;     /**< Description. */

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} heartrate9_t;

/**
 * @brief Heart Rate 9 Click configuration object.
 * @details Configuration object definition of Heart Rate 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;        /**< Description. */

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} heartrate9_cfg_t;


/*!
 * @addtogroup heartrate9 Heart Rate 9 Click Driver
 * @brief API for configuring and manipulating Heart Rate 9 Click driver.
 * @{
 */

/**
 * @brief Heart Rate 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #heartrate9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void heartrate9_cfg_setup ( heartrate9_cfg_t *cfg );

/**
 * @brief Heart Rate 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #heartrate9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #heartrate9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate9_init ( heartrate9_t *ctx, heartrate9_cfg_t *cfg );

/**
 * @brief Heart Rate 9 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate9_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate9_generic_write ( heartrate9_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Heart Rate 9 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate9_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate9_generic_read ( heartrate9_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Sets state of the @b rst pin setting.
 * @details This function sets @b rst pin output to
 * @b state setting.
 * @param[in] ctx Click context object.
 * See #heartrate9_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 */
void heartrate9_set_rst ( heartrate9_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // HEARTRATE9_H

/*! @} */ // heartrate9

// ------------------------------------------------------------------------ END
