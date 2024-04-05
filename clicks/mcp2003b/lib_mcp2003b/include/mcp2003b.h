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
 * @file mcp2003b.h
 * @brief This file contains API for MCP2003B Click Driver.
 */

#ifndef MCP2003B_H
#define MCP2003B_H

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
 * @addtogroup mcp2003b MCP2003B Click Driver
 * @brief API for configuring and manipulating MCP2003B Click driver.
 * @{
 */

/**
 * @defgroup mcp2003b_cmd MCP2003B Device Settings
 * @brief Settings for registers of MCP2003B Click driver.
 */

/**
 * @addtogroup mcp2003b_cmd
 * @{
 */

/**
 * @brief MCP2003B driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define MCP2003B_TX_DRV_BUFFER_SIZE    100
#define MCP2003B_RX_DRV_BUFFER_SIZE    300

/*! @} */ // mcp2003b_cmd

/**
 * @defgroup mcp2003b_map MCP2003B MikroBUS Map
 * @brief MikroBUS pin mapping of MCP2003B Click driver.
 */

/**
 * @addtogroup mcp2003b_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MCP2003B Click to the selected MikroBUS.
 */
#define MCP2003B_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // mcp2003b_map
/*! @} */ // mcp2003b

/**
 * @brief MCP2003B Click context object.
 * @details Context object definition of MCP2003B Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cs;               /**< Chip select pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ MCP2003B_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ MCP2003B_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} mcp2003b_t;

/**
 * @brief MCP2003B Click configuration object.
 * @details Configuration object definition of MCP2003B Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t cs;                  /**< Chip select pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} mcp2003b_cfg_t;

/**
 * @brief MCP2003B Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MCP2003B_OK = 0,
    MCP2003B_ERROR = -1

} mcp2003b_return_value_t;

/*!
 * @addtogroup mcp2003b MCP2003B Click Driver
 * @brief API for configuring and manipulating MCP2003B Click driver.
 * @{
 */

/**
 * @brief MCP2003B configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mcp2003b_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mcp2003b_cfg_setup ( mcp2003b_cfg_t *cfg );

/**
 * @brief MCP2003B initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #mcp2003b_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mcp2003b_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mcp2003b_init ( mcp2003b_t *ctx, mcp2003b_cfg_t *cfg );

/**
 * @brief MCP2003B data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mcp2003b_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mcp2003b_generic_write ( mcp2003b_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief MCP2003B data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mcp2003b_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mcp2003b_generic_read ( mcp2003b_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief MCP2003B set cs pin function.
 * @details This function sets the chip select (CS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #mcp2003b_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mcp2003b_set_cs_pin ( mcp2003b_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // MCP2003B_H

/*! @} */ // mcp2003b

// ------------------------------------------------------------------------ END
