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
 * @file rtkbase.h
 * @brief This file contains API for RTK Base Click Driver.
 */

#ifndef RTKBASE_H
#define RTKBASE_H

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
 * @addtogroup rtkbase RTK Base Click Driver
 * @brief API for configuring and manipulating RTK Base Click driver.
 * @{
 */

/**
 * @defgroup rtkbase_cmd RTK Base Device Settings
 * @brief Settings for registers of RTK Base Click driver.
 */

/**
 * @addtogroup rtkbase_cmd
 * @{
 */

/**
 * @brief RTK Base driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define TX_DRV_BUFFER_SIZE                  100
#define RX_DRV_BUFFER_SIZE                  1000

/*! @} */ // rtkbase_cmd

/**
 * @defgroup rtkbase_map RTK Base MikroBUS Map
 * @brief MikroBUS pin mapping of RTK Base Click driver.
 */

/**
 * @addtogroup rtkbase_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTK Base Click to the selected MikroBUS.
 */
#define RTKBASE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.bt = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // rtkbase_map
/*! @} */ // rtkbase

/**
 * @brief RTK Base Click context object.
 * @details Context object definition of RTK Base Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t shd;          /**< Shutdown pin (Active low). */
    digital_out_t rst;          /**< Reset pin (Active low). */
    digital_out_t wup;          /**< Wake up pin (Active high). */
    digital_out_t bt;           /**< Boot pin (Active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (TX1 ready) informs when transmission buffer is full. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} rtkbase_t;

/**
 * @brief RTK Base Click configuration object.
 * @details Configuration object definition of RTK Base Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t shd;             /**< Shutdown pin (Active low). */
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t wup;             /**< Wake up pin (Active high). */
    pin_name_t bt;              /**< Boot pin (Active high). */
    pin_name_t int_pin;         /**< Interrupt pin (TX1 ready) informs when transmission buffer is full. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} rtkbase_cfg_t;

/**
 * @brief RTK Base Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTKBASE_OK = 0,
    RTKBASE_ERROR = -1

} rtkbase_return_value_t;

/*!
 * @addtogroup rtkbase RTK Base Click Driver
 * @brief API for configuring and manipulating RTK Base Click driver.
 * @{
 */

/**
 * @brief RTK Base configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtkbase_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtkbase_cfg_setup ( rtkbase_cfg_t *cfg );

/**
 * @brief RTK Base initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtkbase_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtkbase_init ( rtkbase_t *ctx, rtkbase_cfg_t *cfg );

/**
 * @brief RTK Base data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtkbase_generic_write ( rtkbase_t *ctx, char *data_in, uint16_t len );

/**
 * @brief RTK Base data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtkbase_generic_read ( rtkbase_t *ctx, char *data_out, uint16_t len );

/**
 * @brief RTK Base clear ring buffers function.
 * @details This function clears UART tx and rx ring buffers.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rtkbase_clear_ring_buffers ( rtkbase_t *ctx );

/**
 * @brief RTK Base rx bytes available function.
 * @details This function returns the number of bytes available in the RX ring buffer.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @return Number of bytes available in the RX ring buffer.
 * @note None.
 */
err_t rtkbase_rx_bytes_available ( rtkbase_t *ctx );

/**
 * @brief RTK Base enable rx interrupt function.
 * @details This function enables the RX interrupt by performing a dummy uart read.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rtkbase_enable_rx_interrupt ( rtkbase_t *ctx );

/**
 * @brief RTK Base set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtkbase_set_rst_pin ( rtkbase_t *ctx, uint8_t state );

/**
 * @brief RTK Base set WUP pin function.
 * @details This function sets the WUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtkbase_set_wup_pin ( rtkbase_t *ctx, uint8_t state );

/**
 * @brief RTK Base set BOOT pin function.
 * @details This function sets the BOOT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtkbase_set_boot_pin ( rtkbase_t *ctx, uint8_t state );

/**
 * @brief RTK Base set SHD pin function.
 * @details This function sets the SHD pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtkbase_set_shd_pin ( rtkbase_t *ctx, uint8_t state );

/**
 * @brief RTK Base get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtkbase_get_int_pin ( rtkbase_t *ctx );

/**
 * @brief RTK Base calculate crc24 function.
 * @details This function calculates and returns the CRC 24-bit of RTCM3 packet input.
 * The CRC across the whole packet should sum to zero (remainder).
 * @param[in] data_buf : RTCM3 packet data buffer.
 * @param[in] data_len : RTCM3 packet data length.
 * @return Calculated CRC 24-bit.
 * @note None.
 */
uint32_t rtkbase_calculate_crc24( uint8_t *data_buf, uint16_t data_len );

#ifdef __cplusplus
}
#endif
#endif // RTKBASE_H

/*! @} */ // rtkbase

// ------------------------------------------------------------------------ END
