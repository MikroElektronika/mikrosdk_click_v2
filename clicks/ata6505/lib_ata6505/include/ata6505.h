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
 * @file ata6505.h
 * @brief This file contains API for ATA6505 Click Driver.
 */

#ifndef ATA6505_H
#define ATA6505_H

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
 * @addtogroup ata6505 ATA6505 Click Driver
 * @brief API for configuring and manipulating ATA6505 Click driver.
 * @{
 */

/**
 * @defgroup ata6505_cmd ATA6505 Device Settings
 * @brief Settings for registers of ATA6505 Click driver.
 */

/**
 * @addtogroup ata6505_cmd
 * @{
 */

/**
 * @brief ATA6505 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ATA6505_TX_DRV_BUFFER_SIZE      100
#define ATA6505_RX_DRV_BUFFER_SIZE      300

/*! @} */ // ata6505_cmd

/**
 * @defgroup ata6505_map ATA6505 MikroBUS Map
 * @brief MikroBUS pin mapping of ATA6505 Click driver.
 */

/**
 * @addtogroup ata6505_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ATA6505 Click to the selected MikroBUS.
 */
#define ATA6505_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.nres = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ata6505_map
/*! @} */ // ata6505

/**
 * @brief ATA6505 Click context object.
 * @details Context object definition of ATA6505 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;               /**< Enable control pin. */

    // Input pins
    digital_in_t nres;              /**< Reset pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ ATA6505_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ ATA6505_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} ata6505_t;

/**
 * @brief ATA6505 Click configuration object.
 * @details Configuration object definition of ATA6505 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t en;                  /**< Enable control pin. */
    pin_name_t nres;                /**< Reset pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} ata6505_cfg_t;

/**
 * @brief ATA6505 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ATA6505_OK = 0,
    ATA6505_ERROR = -1

} ata6505_return_value_t;

/*!
 * @addtogroup ata6505 ATA6505 Click Driver
 * @brief API for configuring and manipulating ATA6505 Click driver.
 * @{
 */

/**
 * @brief ATA6505 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ata6505_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ata6505_cfg_setup ( ata6505_cfg_t *cfg );

/**
 * @brief ATA6505 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ata6505_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ata6505_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ata6505_init ( ata6505_t *ctx, ata6505_cfg_t *cfg );

/**
 * @brief ATA6505 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ata6505_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ata6505_generic_write ( ata6505_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ATA6505 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ata6505_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ata6505_generic_read ( ata6505_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief ATA6505 set EN pin function.
 * @details This function sets the EN pin logic state.
 * @param[in] ctx : Click context object.
 * See #ata6505_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ata6505_set_en_pin ( ata6505_t *ctx, uint8_t state );

/**
 * @brief ATA6505 get NRES pin function.
 * @details This function returns the NRES pin logic state.
 * @param[in] ctx : Click context object.
 * See #ata6505_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ata6505_get_nres_pin ( ata6505_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ATA6505_H

/*! @} */ // ata6505

// ------------------------------------------------------------------------ END
