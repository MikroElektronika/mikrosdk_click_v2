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
 * @file canfd7.h
 * @brief This file contains API for CAN FD 7 Click Driver.
 */

#ifndef CANFD7_H
#define CANFD7_H

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
 * @addtogroup canfd7 CAN FD 7 Click Driver
 * @brief API for configuring and manipulating CAN FD 7 Click driver.
 * @{
 */

/**
 * @defgroup canfd7_cmd CAN FD 7 Device Settings
 * @brief Settings for registers of CAN FD 7 Click driver.
 */

/**
 * @addtogroup canfd7_cmd
 * @{
 */

/**
 * @brief CAN FD 7 control commands.
 * @details Specified setting for control commands of CAN FD 7 Click driver.
 */
#define CANFD7_STANDBY_ON            0x01
#define CANFD7_STANDBY_OFF           0x00

/**
 * @brief CAN FD 7 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define CANFD7_TX_DRV_BUFFER_SIZE    100
#define CANFD7_RX_DRV_BUFFER_SIZE    300

/*! @} */ // canfd7_cmd

/**
 * @defgroup canfd7_map CAN FD 7 MikroBUS Map
 * @brief MikroBUS pin mapping of CAN FD 7 Click driver.
 */

/**
 * @addtogroup canfd7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CAN FD 7 Click to the selected MikroBUS.
 */
#define CANFD7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // canfd7_map
/*! @} */ // canfd7

/**
 * @brief CAN FD 7 Click context object.
 * @details Context object definition of CAN FD 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t stb;                      /**< Standby mode pin. */

    // Modules
    uart_t uart;                            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ CANFD7_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ CANFD7_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} canfd7_t;

/**
 * @brief CAN FD 7 Click configuration object.
 * @details Configuration object definition of CAN FD 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                      /**< RX pin. */
    pin_name_t tx_pin;                      /**< TX pin. */

    // Additional gpio pins
    pin_name_t stb;                         /**< Standby mode pin. */

    // Static variable
    uint32_t         baud_rate;             /**< Clock speed. */
    bool             uart_blocking;         /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;              /**< Data bits. */
    uart_parity_t    parity_bit;            /**< Parity bit. */
    uart_stop_bits_t stop_bit;              /**< Stop bits. */

} canfd7_cfg_t;

/**
 * @brief CAN FD 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CANFD7_OK = 0,
    CANFD7_ERROR = -1

} canfd7_return_value_t;

/*!
 * @addtogroup canfd7 CAN FD 7 Click Driver
 * @brief API for configuring and manipulating CAN FD 7 Click driver.
 * @{
 */

/**
 * @brief CAN FD 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #canfd7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void canfd7_cfg_setup ( canfd7_cfg_t *cfg );

/**
 * @brief CAN FD 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #canfd7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #canfd7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd7_init ( canfd7_t *ctx, canfd7_cfg_t *cfg );

/**
 * @brief CAN FD 7 default configuration function.
 * @details This function executes a default configuration of CAN FD 7
 * click board.
 * @param[in] ctx : Click context object.
 * See #canfd7_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void canfd7_default_cfg ( canfd7_t *ctx );

/**
 * @brief CAN FD 7 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #canfd7_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd7_generic_write ( canfd7_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief CAN FD 7 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #canfd7_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t canfd7_generic_read ( canfd7_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief CAN FD 7 set STB pin function.
 * @details This function is used to set Standby mode.
 * @param[in] ctx : Click context object.
 * See #canfd7_t object definition for detailed explanation.
 * @param[in] pin_state : Standby state.
 * @return Nothing.
 * @note None.
 */
void canfd7_set_stb_pin ( canfd7_t *ctx, uint8_t pin_state );

#ifdef __cplusplus
}
#endif
#endif // CANFD7_H

/*! @} */ // canfd7

// ------------------------------------------------------------------------ END
