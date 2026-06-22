/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file rtlsuwb.h
 * @brief This file contains API for RTLS UWB Click Driver.
 */

#ifndef RTLSUWB_H
#define RTLSUWB_H

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
 * @addtogroup rtlsuwb RTLS UWB Click Driver
 * @brief API for configuring and manipulating RTLS UWB Click driver.
 * @{
 */

/**
 * @defgroup rtlsuwb_cmd RTLS UWB Device Settings
 * @brief Settings of RTLS UWB Click driver.
 */

/**
 * @addtogroup rtlsuwb_cmd
 * @{
 */

/**
 * @brief RTLS UWB anytime commands.
 * @details Specified setting for anytime commands of RTLS UWB Click driver.
 */
#define RTLSUWB_CMD_HELP                    "help"
#define RTLSUWB_CMD_STAT                    "stat"
#define RTLSUWB_CMD_STOP                    "stop"
#define RTLSUWB_CMD_THREAD                  "thread"

/**
 * @brief RTLS UWB application selection commands.
 * @details Specified setting for application selection commands of RTLS UWB Click driver.
 */
#define RTLSUWB_CMD_LISTENER2               "listener"
#define RTLSUWB_CMD_RESPF                   "respf"
#define RTLSUWB_CMD_INITF                   "initf"

/**
 * @brief RTLS UWB listener options commands.
 * @details Specified setting for listener options commands of RTLS UWB Click driver.
 */
#define RTLSUWB_CMD_LSTAT                   "lstat"

/**
 * @brief RTLS UWB IDLE time commands.
 * @details Specified setting for IDLE time commands of RTLS UWB Click driver.
 */
#define RTLSUWB_CMD_UART                    "uart"
#define RTLSUWB_CMD_CALKEY                  "calkey"
#define RTLSUWB_CMD_LISTCAL                 "listcal"

/**
 * @brief RTLS UWB service commands.
 * @details Specified setting for service commands of RTLS UWB Click driver.
 */
#define RTLSUWB_CMD_RESTORE                 "restore"
#define RTLSUWB_CMD_DIAG                    "diag"
#define RTLSUWB_CMD_LCFG                    "lcfg"
#define RTLSUWB_CMD_DECAID                  "decaid"
#define RTLSUWB_CMD_SAVE                    "save"
#define RTLSUWB_CMD_SETAPP                  "setapp"
#define RTLSUWB_CMD_GETOTP                  "getotp"

/**
 * @brief RTLS UWB device response to commands.
 * @details Device response to commands.
 */
#define RTLSUWB_RSP_OK                      "ok"
#define RTLSUWB_RSP_ERROR                   "error"
#define RTLSUWB_RSP_BLOCK_END               "}\r\n"

/**
 * @brief RTLS UWB device response time for commands.
 * @details Device response time after commands.
 */
#define RTLSUWB_MAX_RSP_TIME_DEFAULT        5000ul

/**
 * @brief RTLS UWB driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RTLSUWB_TX_DRV_BUFFER_SIZE          128
#define RTLSUWB_RX_DRV_BUFFER_SIZE          1024

/*! @} */ // rtlsuwb_cmd

/**
 * @defgroup rtlsuwb_map RTLS UWB MikroBUS Map
 * @brief MikroBUS pin mapping of RTLS UWB Click driver.
 */

/**
 * @addtogroup rtlsuwb_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTLS UWB Click to the selected MikroBUS.
 */
#define RTLSUWB_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // rtlsuwb_map
/*! @} */ // rtlsuwb

/**
 * @brief RTLS UWB Click context object.
 * @details Context object definition of RTLS UWB Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */

    // Input pins
    digital_in_t irq;               /**< IRQ pin (P0.28). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ RTLSUWB_RX_DRV_BUFFER_SIZE ];   /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ RTLSUWB_TX_DRV_BUFFER_SIZE ];   /**< TX Buffer size. */
    uint8_t cmd_buffer[ RTLSUWB_TX_DRV_BUFFER_SIZE ];       /**< Command buffer. */

} rtlsuwb_t;

/**
 * @brief RTLS UWB Click configuration object.
 * @details Configuration object definition of RTLS UWB Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t irq;                 /**< IRQ pin (P0.28). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} rtlsuwb_cfg_t;

/**
 * @brief RTLS UWB Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTLSUWB_OK = 0,
    RTLSUWB_ERROR = -1,
    RTLSUWB_ERROR_TIMEOUT = -2,
    RTLSUWB_ERROR_CMD = -3

} rtlsuwb_return_value_t;

/*!
 * @addtogroup rtlsuwb RTLS UWB Click Driver
 * @brief API for configuring and manipulating RTLS UWB Click driver.
 * @{
 */

/**
 * @brief RTLS UWB configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtlsuwb_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtlsuwb_cfg_setup ( rtlsuwb_cfg_t *cfg );

/**
 * @brief RTLS UWB initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtlsuwb_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtlsuwb_init ( rtlsuwb_t *ctx, rtlsuwb_cfg_t *cfg );

/**
 * @brief RTLS UWB data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtlsuwb_generic_write ( rtlsuwb_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief RTLS UWB data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtlsuwb_generic_read ( rtlsuwb_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief RTLS UWB set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtlsuwb_set_rst_pin ( rtlsuwb_t *ctx, uint8_t state );

/**
 * @brief RTLS UWB get IRQ pin function.
 * @details This function returns the IRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtlsuwb_get_irq_pin ( rtlsuwb_t *ctx );

/**
 * @brief RTLS UWB reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rtlsuwb_reset_device ( rtlsuwb_t *ctx );

/**
 * @brief RTLS UWB cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void rtlsuwb_cmd_run ( rtlsuwb_t *ctx, uint8_t *cmd );

/**
 * @brief RTLS UWB cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #rtlsuwb_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void rtlsuwb_cmd_set ( rtlsuwb_t *ctx, uint8_t *cmd, uint8_t *value );

#ifdef __cplusplus
}
#endif
#endif // RTLSUWB_H

/*! @} */ // rtlsuwb

// ------------------------------------------------------------------------ END
