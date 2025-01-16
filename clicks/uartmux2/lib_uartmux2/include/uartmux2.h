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
 * @file uartmux2.h
 * @brief This file contains API for UART MUX 2 Click Driver.
 */

#ifndef UARTMUX2_H
#define UARTMUX2_H

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
 * @addtogroup uartmux2 UART MUX 2 Click Driver
 * @brief API for configuring and manipulating UART MUX 2 Click driver.
 * @{
 */

/**
 * @defgroup uartmux2_set UART MUX 2 Device Settings
 * @brief Settings for registers of UART MUX 2 Click driver.
 */

/**
 * @addtogroup uartmux2_set
 * @{
 */

/**
 * @brief UART MUX 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE              200

/*! @} */ // uartmux2_set

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief UART MUX 2 error status.
 * @details Specified error status 
 * for description of UART MUX 2 Click driver.
 */
#define UARTMUX2_SUCCESS               0
#define UARTMUX2_ERROR                -1


/*! @} */ // status

/**
 * @addtogroup op_mode
 * @{
 */

/**
 * @brief UART MUX 2 operation mode.
 * @details Specified operation mode selection 
 * for description of UART MUX 2 Click driver.
 */
#define UARTMUX2_OP_MODE_NORMAL        0x00
#define UARTMUX2_OP_MODE_POWER_DOWN    0x01


/*! @} */ // op_mode

/**
 * @addtogroup mux_ch
 * @{
 */

/**
 * @brief UART MUX 2 select channel.
 * @details Specified select uart mux channel 
 * of UART MUX 2 Click driver.
 */
#define UARTMUX2_CHANNEL_0            0
#define UARTMUX2_CHANNEL_1            1
#define UARTMUX2_CHANNEL_2            2
#define UARTMUX2_CHANNEL_3            3


/*! @} */ // mux_ch

/**
 * @defgroup uartmux2_map UART MUX 2 MikroBUS Map
 * @brief MikroBUS pin mapping of UART MUX 2 Click driver.
 */

/**
 * @addtogroup uartmux2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UART MUX 2 Click to the selected MikroBUS.
 */
#define UARTMUX2_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.off = MIKROBUS( mikrobus, MIKROBUS_AN );     \
    cfg.a1 = MIKROBUS( mikrobus, MIKROBUS_RST );     \
    cfg.a0 = MIKROBUS( mikrobus, MIKROBUS_CS );      \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_PWM );     \
    cfg.inv = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // uartmux2_map
/*! @} */ // uartmux2

/**
 * @brief UART MUX 2 Click context object.
 * @details Context object definition of UART MUX 2 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t off;    /**< Automatic OFF power-down control. */
    digital_out_t a1;     /**< Address channel selection. */
    digital_out_t a0;     /**< Address channel selection. */
    digital_out_t on;     /**< Automatic ON power-down control. */

    // Input pins

    digital_in_t inv;       /**< Invalid status pin. */

    // Modules

    uart_t uart;                                    /**< UART driver object. */

    // Buffers

    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} uartmux2_t;

/**
 * @brief UART MUX 2 Click configuration object.
 * @details Configuration object definition of UART MUX 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins

    pin_name_t off;       /**< Automatic OFF power-down control. */
    pin_name_t a1;        /**< Address channel selection. */
    pin_name_t a0;        /**< Address channel selection. */
    pin_name_t on;        /**< Automatic ON power-down control. */
    pin_name_t inv;       /**< Invalid status pin. */

    // Static variable

    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} uartmux2_cfg_t;

/*!
 * @addtogroup uartmux2 UART MUX 2 Click Driver
 * @brief API for configuring and manipulating UART MUX 2 Click driver.
 * @{
 */

/**
 * @brief UART MUX 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uartmux2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uartmux2_cfg_setup ( uartmux2_cfg_t *cfg );

/**
 * @brief UART MUX 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #uartmux2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uartmux2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uartmux2_init ( uartmux2_t *ctx, uartmux2_cfg_t *cfg );

/**
 * @brief UART MUX 2 default configuration function.
 * @details This function executes a default configuration of UART MUX 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #uartmux2_t object definition for detailed explanation.

 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void uartmux2_default_cfg ( uartmux2_t *ctx );

/**
 * @brief UART MUX 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #uartmux2_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uartmux2_generic_write ( uartmux2_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief UART MUX 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #uartmux2_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uartmux2_generic_read ( uartmux2_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief UART MUX 2 set operation mode function.
 * @details This function set a desired operation mode of the 
 * UART MUX 2 Click board. 
 * @param[in] ctx : Click context object.
 * See #uartmux2_t object definition for detailed explanation.
 * @param[in] op_mode : Operation mode
 *         @li @c 0x00 ( UARTMUX2_OP_MODE_NORMAL )     - Normal operation with automatic power down disabled,
 *         @li @c 0x01 ( UARTMUX2_OP_MODE_POWER_DOWN ) - Normal operation with automatic power down enabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uartmux2_set_operation_mode ( uartmux2_t *ctx, uint8_t op_mode );

/**
 * @brief UART MUX 2 set channel function.
 * @details This function set a desired channel f the 
 * UART MUX 2 Click board. 
 * @param[in] ctx : Click context object.
 * See #uartmux2_t object definition for detailed explanation.
 * @param[in] mux_ch : Selected channel
 *         @li @c 0 ( UARTMUX2_CHANNEL_0 ) - UART0, Channel 0,
 *         @li @c 1 ( UARTMUX2_CHANNEL_1 ) - UART1, Channel 1,
 *         @li @c 2 ( UARTMUX2_CHANNEL_2 ) - UART2, Channel 2,
 *         @li @c 3 ( UARTMUX2_CHANNEL_3 ) - UART3, Channel 3.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uartmux2_set_channel ( uartmux2_t *ctx, uint8_t mux_ch );

/**
 * @brief UART MUX 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #uartmux2_t object definition for detailed explanation.
 * @param[in] tx_data : Data buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uartmux2_send_data ( uartmux2_t *ctx, char *tx_data );

/**
 * @brief UART MUX 2 get INV pin status function.
 * @details This function get INV pin status ( RS232 status ) of the 
 * UART MUX 2 Click board.  
 * @param[in] ctx : Click context object.
 * See #uartmux2_t object definition for detailed explanation.
 * @return @li @c 0 - RS232 receiver input are unpowered,
 *         @li @c 1 - RS232 receiver input are powered.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t uartmux2_get_inv_status ( uartmux2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // UARTMUX2_H

/*! @} */ // uartmux2

// ------------------------------------------------------------------------ END
