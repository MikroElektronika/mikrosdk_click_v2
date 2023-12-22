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
 * @file opto7.h
 * @brief This file contains API for Opto 7 Click Driver.
 */

#ifndef OPTO7_H
#define OPTO7_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup opto7 Opto 7 Click Driver
 * @brief API for configuring and manipulating Opto 7 Click driver.
 * @{
 */

/**
 * @defgroup opto7_cmd Opto 7 Device Settings
 * @brief Settings for registers of Opto 7 Click driver.
 */

/**
 * @addtogroup opto7_cmd
 * @{
 */

/**
 * @brief Opto 7 control commands.
 * @details Specified setting for control commands of Opto 7 Click driver.
 */
#define OPTO7_PIN_STATE_HIGH        0x01
#define OPTO7_PIN_STATE_LOW         0x00

/**
 * @brief Opto 7 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define OPTO7_TX_DRV_BUFFER_SIZE    100
#define OPTO7_RX_DRV_BUFFER_SIZE    300

/*! @} */ // opto7_cmd

/**
 * @defgroup opto7_map Opto 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Opto 7 Click driver.
 */

/**
 * @addtogroup opto7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Opto 7 Click to the selected MikroBUS.
 */
#define OPTO7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // opto7_map
/*! @} */ // opto7

/**
 * @brief Opto 7 Click driver selector.
 * @details Selects target driver interface of Opto 7 Click driver.
 */
typedef enum
{
    OPTO7_DRV_SEL_GPIO,      /**< GPIO driver descriptor. */
    OPTO7_DRV_SEL_UART       /**< UART driver descriptor. */

} opto7_drv_t;

/**
 * @brief Opto 7 Click context object.
 * @details Context object definition of Opto 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t gp1;                          /**< Output pin. */

    // Input pins
    digital_in_t gp2;                           /**< Input pin. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ OPTO7_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ OPTO7_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    
    opto7_drv_t drv_sel;                /**< Master driver interface selector. */

} opto7_t;

/**
 * @brief Opto 7 Click configuration object.
 * @details Configuration object definition of Opto 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t gp1;                             /**< Output pin. */
    pin_name_t gp2;                             /**< Input pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */
    opto7_drv_t drv_sel;               /**< Master driver interface selector. */

} opto7_cfg_t;

/**
 * @brief Opto 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    OPTO7_OK = 0,
    OPTO7_ERROR = -1

} opto7_return_value_t;

/*!
 * @addtogroup opto7 Opto 7 Click Driver
 * @brief API for configuring and manipulating Opto 7 Click driver.
 * @{
 */

/**
 * @brief Opto 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #opto7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void opto7_cfg_setup ( opto7_cfg_t *cfg );

/**
 * @brief Opto 7 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #opto7_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #opto7_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void opto7_drv_interface_selection ( opto7_cfg_t *cfg, opto7_drv_t drv_sel );

/**
 * @brief Opto 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #opto7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #opto7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t opto7_init ( opto7_t *ctx, opto7_cfg_t *cfg );

/**
 * @brief Opto 7 default configuration function.
 * @details This function executes a default configuration of Opto 7
 * click board.
 * @param[in] ctx : Click context object.
 * See #opto7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t opto7_default_cfg ( opto7_t *ctx );

/**
 * @brief Opto 7 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #opto7_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t opto7_generic_write ( opto7_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Opto 7 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #opto7_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t opto7_generic_read ( opto7_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Opto 7 set GP1 pin function.
 * @details This function is used to set GP1 pin state.
 * @param[in] ctx : Click context object.
 * See #opto7_t object definition for detailed explanation.
 * @param[in] pin_state : GP1 Pin state.
 * @return Nothing.
 * @note None.
 */
void opto7_set_gp1_pin( opto7_t *ctx, uint8_t pin_state );

/**
 * @brief Opto 7 get GP2 pin function.
 * @details This function is used to get GP2 pin state.
 * @param[in] ctx : Click context object.
 * See #opto7_t object definition for detailed explanation.
 * @return @li @c 1 - Pin state high,
 *         @li @c 0 - Pin state low.
 * @note None.
 */
uint8_t opto7_get_gp2_pin( opto7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OPTO7_H

/*! @} */ // opto7

// ------------------------------------------------------------------------ END
