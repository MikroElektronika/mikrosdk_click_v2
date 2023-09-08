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
 * @file lightranger7.h
 * @brief This file contains API for LightRanger 7 Click Driver.
 */

#ifndef LIGHTRANGER7_H
#define LIGHTRANGER7_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup lightranger7 LightRanger 7 Click Driver
 * @brief API for configuring and manipulating LightRanger 7 Click driver.
 * @{
 */

/**
 * @defgroup lightranger7_cmd LightRanger 7 Device Settings
 * @brief Settings for registers of LightRanger 7 Click driver.
 */

/**
 * @addtogroup lightranger7_cmd
 * @{
 */

/**
 * @brief LightRanger 7 control commands.
 * @details Specified setting for control commands of LightRanger 7 Click driver.
 */
#define LIGHTRANGER7_CMD_START              's'
#define LIGHTRANGER7_CMD_STOP               'p'

/**
 * @brief LightRanger 7 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LIGHTRANGER7_TX_DRV_BUFFER_SIZE     100
#define LIGHTRANGER7_RX_DRV_BUFFER_SIZE     1000

/*! @} */ // lightranger7_cmd

/**
 * @defgroup lightranger7_map LightRanger 7 MikroBUS Map
 * @brief MikroBUS pin mapping of LightRanger 7 Click driver.
 */

/**
 * @addtogroup lightranger7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightRanger 7 Click to the selected MikroBUS.
 */
#define LIGHTRANGER7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX );

/*! @} */ // lightranger7_map
/*! @} */ // lightranger7

/**
 * @brief LightRanger 7 Click context object.
 * @details Context object definition of LightRanger 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Reset pin (Active low). */
    
    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LIGHTRANGER7_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ LIGHTRANGER7_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} lightranger7_t;

/**
 * @brief LightRanger 7 Click configuration object.
 * @details Configuration object definition of LightRanger 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */
    pin_name_t rst;                     /**< Reset pin (Active low). */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} lightranger7_cfg_t;

/**
 * @brief LightRanger 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHTRANGER7_OK = 0,
    LIGHTRANGER7_ERROR = -1

} lightranger7_return_value_t;

/*!
 * @addtogroup lightranger7 LightRanger 7 Click Driver
 * @brief API for configuring and manipulating LightRanger 7 Click driver.
 * @{
 */

/**
 * @brief LightRanger 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lightranger7_cfg_setup ( lightranger7_cfg_t *cfg );

/**
 * @brief LightRanger 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lightranger7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightranger7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger7_init ( lightranger7_t *ctx, lightranger7_cfg_t *cfg );

/**
 * @brief LightRanger 7 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger7_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger7_generic_write ( lightranger7_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LightRanger 7 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger7_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger7_generic_read ( lightranger7_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LightRanger 7 start measurement function.
 * @details This function starts the measurement by sending the 's' command over UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger7_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note The click board must be programmed with a AFBR_S50_CANApp_RA4M2 firmware which
 * support this command.
 */
err_t lightranger7_start_measurement ( lightranger7_t *ctx );

/**
 * @brief LightRanger 7 stop measurement function.
 * @details This function stops the measurement by sending the 'p' command over UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger7_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note The click board must be programmed with a AFBR_S50_CANApp_RA4M2 firmware which
 * support this command.
 */
err_t lightranger7_stop_measurement ( lightranger7_t *ctx );

/**
 * @brief LightRanger 7 enable device function.
 * @details This function enables the device by setting the rst pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger7_enable_device ( lightranger7_t *ctx );

/**
 * @brief LightRanger 7 disable device function.
 * @details This function disables the device by setting the rst pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger7_disable_device ( lightranger7_t *ctx );

/**
 * @brief LightRanger 7 reset device function.
 * @details This function resets the device by toggling the rst pin state.
 * @param[in] ctx : Click context object.
 * See #lightranger7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger7_reset_device ( lightranger7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LIGHTRANGER7_H

/*! @} */ // lightranger7

// ------------------------------------------------------------------------ END
