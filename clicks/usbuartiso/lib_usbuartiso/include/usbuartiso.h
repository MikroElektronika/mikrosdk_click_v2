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
 * @file usbuartiso.h
 * @brief This file contains API for USB UART ISO Click Driver.
 */

#ifndef USBUARTISO_H
#define USBUARTISO_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup usbuartiso USB UART ISO Click Driver
 * @brief API for configuring and manipulating USB UART ISO Click driver.
 * @{
 */

/**
 * @defgroup usbuartiso_cmd USB UART ISO Device Settings
 * @brief Settings for registers of USB UART ISO Click driver.
 */

/**
 * @addtogroup usbuartiso_cmd
 * @{
 */

/**
 * @brief USB UART ISO driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define USBUARTISO_TX_DRV_BUFFER_SIZE    100
#define USBUARTISO_RX_DRV_BUFFER_SIZE    300

/*! @} */ // usbuartiso_cmd

/**
 * @defgroup usbuartiso_map USB UART ISO MikroBUS Map
 * @brief MikroBUS pin mapping of USB UART ISO Click driver.
 */

/**
 * @addtogroup usbuartiso_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB UART ISO Click to the selected MikroBUS.
 */
#define USBUARTISO_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_AN );     \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS );     \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // usbuartiso_map
/*! @} */ // usbuartiso

/**
 * @brief USB UART ISO Click context object.
 * @details Context object definition of USB UART ISO Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cts;    /**< Clear to send pin. */
    digital_out_t pwr;    /**< Power control pin. */

    // Input pins
    digital_in_t slp;     /**< Sleep indicator pin. */
    digital_in_t rts;     /**< Request to send pin. */

    // Modules
    uart_t uart;          /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ USBUARTISO_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ USBUARTISO_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} usbuartiso_t;

/**
 * @brief USB UART ISO Click configuration object.
 * @details Configuration object definition of USB UART ISO Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */

    // Additional gpio pins
    pin_name_t slp;    /**< Sleep indicator pin. */
    pin_name_t cts;    /**< Clear to send pin. */
    pin_name_t pwr;    /**< Power control pin. */
    pin_name_t rts;    /**< Request to send pin. */

    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */

} usbuartiso_cfg_t;

/**
 * @brief USB UART ISO Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBUARTISO_OK = 0,
    USBUARTISO_ERROR = -1

} usbuartiso_return_value_t;

/*!
 * @addtogroup usbuartiso USB UART ISO Click Driver
 * @brief API for configuring and manipulating USB UART ISO Click driver.
 * @{
 */

/**
 * @brief USB UART ISO configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbuartiso_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbuartiso_cfg_setup ( usbuartiso_cfg_t *cfg );

/**
 * @brief USB UART ISO initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbuartiso_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbuartiso_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuartiso_init ( usbuartiso_t *ctx, usbuartiso_cfg_t *cfg );

/**
 * @brief USB UART ISO default configuration function.
 * @details This function executes a default configuration of USB UART ISO
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbuartiso_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void usbuartiso_default_cfg ( usbuartiso_t *ctx );

/**
 * @brief USB UART ISO data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #usbuartiso_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuartiso_generic_write ( usbuartiso_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief USB UART ISO data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #usbuartiso_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuartiso_generic_read ( usbuartiso_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief USB UART ISO power on function.
 * @details This function performs a power on 
 * of the FT232RL, USB Full Speed to Serial UART IC
 * on the USB UART ISO click board™.  
 * @param[in] ctx : Click context object.
 * See #usbuartiso_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void usbuartiso_power_on ( usbuartiso_t *ctx );

/**
 * @brief USB UART ISO power off function.
 * @details This function performs a power off 
 * of the FT232RL, USB Full Speed to Serial UART IC
 * on the USB UART ISO click board™.  
 * @param[in] ctx : Click context object.
 * See #usbuartiso_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void usbuartiso_power_off ( usbuartiso_t *ctx );

/**
 * @brief USB UART ISO sleep indicator function.
 * @details This function indicates that the device going into USB suspend mode
 * of the FT232RL, USB Full Speed to Serial UART IC
 * on the USB UART ISO click board™.  
 * @param[in] ctx : Click context object.
 * See #usbuartiso_t object definition for detailed explanation.
 * @return @li @c 0 - USB suspend mode,
 *         @li @c 1 - USB operating mode.
 * @note None.
 */
uint8_t usbuartiso_get_slp_ind ( usbuartiso_t *ctx );

/**
 * @brief USB UART ISO request to send function.
 * @details This function is flow control and uses to get requests to send status
 * of the USB UART ISO click board™.  
 * @param[in] ctx : Click context object.
 * See #usbuartiso_t object definition for detailed explanation.
 * @return Status of the request to send.
 * @note None.
 */
uint8_t usbuartiso_request_to_send ( usbuartiso_t *ctx );

/**
 * @brief USB UART ISO clear to send function.
 * @details This function is flow control and uses to sets the clear to send state
 * of the USB UART ISO click board™.  
 * @param[in] ctx : Click context object.
 * See #usbuartiso_t object definition for detailed explanation.
 * @param[in] cts : Clear to send state.
 * @return Nothing.
 * @note None.
 */
void usbuartiso_clear_to_send ( usbuartiso_t *ctx, uint8_t cts );

#ifdef __cplusplus
}
#endif
#endif // USBUARTISO_H

/*! @} */ // usbuartiso

// ------------------------------------------------------------------------ END
