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
 * @file usbuart5.h
 * @brief This file contains API for USB UART 5 Click Driver.
 */

#ifndef USBUART5_H
#define USBUART5_H

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
 * @addtogroup usbuart5 USB UART 5 Click Driver
 * @brief API for configuring and manipulating USB UART 5 Click driver.
 * @{
 */

/**
 * @defgroup usbuart5_cmd USB UART 5 Device Settings
 * @brief Settings for registers of USB UART 5 Click driver.
 */

/**
 * @addtogroup usbuart5_cmd
 * @{
 */

/**
 * @brief USB UART 5 config suspend mode values.
 * @details The specified setting for suspend mode values
 * of the USB UART 5 Click driver.
 */
#define USBUART5_SUSPEND_MODE_DISABLE    0
#define USBUART5_SUSPEND_MODE_ENABLE     1

/**
 * @brief USB UART 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define USBUART5_TX_DRV_BUFFER_SIZE    100
#define USBUART5_RX_DRV_BUFFER_SIZE    300

/*! @} */ // usbuart5_cmd

/**
 * @defgroup usbuart5_map USB UART 5 MikroBUS Map
 * @brief MikroBUS pin mapping of USB UART 5 Click driver.
 */

/**
 * @addtogroup usbuart5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB UART 5 Click to the selected MikroBUS.
 */
#define USBUART5_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.spd = MIKROBUS( mikrobus, MIKROBUS_AN );      \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS );     \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // usbuart5_map
/*! @} */ // usbuart5

/**
 * @brief USB UART 5 Click context object.
 * @details Context object definition of USB UART 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;    /**< Device reset. */
    digital_out_t cts;    /**< Clear To Send. */

    // Input pins
    digital_in_t spd;     /**< USB Suspend state. */
    digital_in_t rts;     /**< Ready To Send. */

    // Modules
    uart_t uart;          /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ USBUART5_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ USBUART5_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} usbuart5_t;

/**
 * @brief USB UART 5 Click configuration object.
 * @details Configuration object definition of USB UART 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t spd;                             /**< USB Suspend state. */
    pin_name_t rst;                             /**< Device reset. */
    pin_name_t cts;                             /**< Clear To Send. */
    pin_name_t rts;                             /**< Ready To Send. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} usbuart5_cfg_t;

/**
 * @brief USB UART 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBUART5_OK = 0,
    USBUART5_ERROR = -1

} usbuart5_return_value_t;

/**
 * @brief USB UART 5 Click pin state.
 * @details Predefined enum values for pin stat.
 */
typedef enum
{
    USBUART5_PIN_STATE_LOW = 0,
    USBUART5_PIN_STATE_HIGH = 1

} usbuart5_pin_state_t;

/*!
 * @addtogroup usbuart5 USB UART 5 Click Driver
 * @brief API for configuring and manipulating USB UART 5 Click driver.
 * @{
 */

/**
 * @brief USB UART 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbuart5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbuart5_cfg_setup ( usbuart5_cfg_t *cfg );

/**
 * @brief USB UART 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbuart5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbuart5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuart5_init ( usbuart5_t *ctx, usbuart5_cfg_t *cfg );

/**
 * @brief USB UART 5 default configuration function.
 * @details This function executes a default configuration of USB UART 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbuart5_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void usbuart5_default_cfg ( usbuart5_t *ctx );

/**
 * @brief USB UART 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #usbuart5_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuart5_generic_write ( usbuart5_t *ctx, char *data_in, uint16_t len );

/**
 * @brief USB UART 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #usbuart5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuart5_generic_read ( usbuart5_t *ctx, char *data_out, uint16_t len );

/**
 * @brief USB UART 5 enable the device function.
 * @details This function enable 
 * the CP2110 Single-Chip HID USB to UART Bridge
 * on the USB UART 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbuart5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void usbuart5_enable_device ( usbuart5_t *ctx );

/**
 * @brief USB UART 5 reset the device function.
 * @details This function performs resets 
 * the CP2110 Single-Chip HID USB to UART Bridge
 * on the USB UART 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbuart5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void usbuart5_reset_device ( usbuart5_t *ctx );

/**
 * @brief USB UART 5 set cts pin state function.
 * @details This function sets the CTS (Clear To Send) pin logic state.
 * @param[in] ctx : Click context object.
 * See #usbuart5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void usbuart5_set_cts_pin ( usbuart5_t *ctx, usbuart5_pin_state_t state );

/**
 * @brief USB UART 5 get USB Suspend state function.
 * @details This function get USB Suspend state
 * of the CP2110 Single-Chip HID USB to UART Bridge
 * on the USB UART 5 Click board™.
 * @param[in] ctx : Click context object.
 * See #usbuart5_t object definition for detailed explanation.
 * @return @li @c 0 - Connected,
 *         @li @c 1 - USB Suspend state.
 * @note None.
 */
uint8_t usbuart5_get_suspend_state ( usbuart5_t *ctx );

/**
 * @brief USB UART 5 get rts pin state function.
 * @details This function returns the RTS (Ready To Send) pin logic state.
 * @param[in] ctx : Click context object.
 * See #usbuart5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t usbuart5_get_rts_pin ( usbuart5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBUART5_H

/*! @} */ // usbuart5

// ------------------------------------------------------------------------ END
