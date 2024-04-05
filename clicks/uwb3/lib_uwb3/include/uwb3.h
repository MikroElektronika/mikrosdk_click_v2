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
 * @file uwb3.h
 * @brief This file contains API for UWB 3 Click Driver.
 */

#ifndef UWB3_H
#define UWB3_H

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
 * @addtogroup uwb3 UWB 3 Click Driver
 * @brief API for configuring and manipulating UWB 3 Click driver.
 * @{
 */

/**
 * @defgroup uwb3_cmd UWB 3 Device Settings
 * @brief Settings for registers of UWB 3 Click driver.
 */

/**
 * @addtogroup uwb3_cmd
 * @{
 */

/**
 * @brief UWB 3 anytime commands.
 * @details Specified setting for anytime commands of UWB 3 Click driver.
 */
#define UWB3_CMD_HELP               "help"
#define UWB3_CMD_STAT               "stat"
#define UWB3_CMD_DECA               "deca$"
#define UWB3_CMD_STOP               "stop"
#define UWB3_CMD_SAVE               "save"
#define UWB3_CMD_THREAD             "thread"

/**
 * @brief UWB 3 application selection commands.
 * @details Specified setting for application selection commands of UWB 3 Click driver.
 */
#define UWB3_CMD_LISTENER2          "listener2"
#define UWB3_CMD_TCFM               "tcfm"
#define UWB3_CMD_TCWM               "tcwm"
#define UWB3_CMD_RESPF              "respf"
#define UWB3_CMD_INITF              "initf"

/**
 * @brief UWB 3 listener options commands.
 * @details Specified setting for listener options commands of UWB 3 Click driver.
 */
#define UWB3_CMD_LSTAT              "lstat"

/**
 * @brief UWB 3 FiRa options commands.
 * @details Specified setting for FiRa options commands of UWB 3 Click driver.
 */
#define UWB3_CMD_PAVRG              "pavrg"

/**
 * @brief UWB 3 IDLE time commands.
 * @details Specified setting for IDLE time commands of UWB 3 Click driver.
 */
#define UWB3_CMD_ANTTXA             "anttxa"
#define UWB3_CMD_ANTRXA             "antrxa"
#define UWB3_CMD_XTALTRIM           "xtaltrim"
#define UWB3_CMD_PDOAOFF            "pdoaoff"
#define UWB3_CMD_UART               "uart"

/**
 * @brief UWB 3 service commands.
 * @details Specified setting for service commands of UWB 3 Click driver.
 */
#define UWB3_CMD_RESTORE            "restore"
#define UWB3_CMD_DIAG               "diag"
#define UWB3_CMD_UWBCFG             "uwbcfg"
#define UWB3_CMD_STSKEYIV           "stskeyiv"
#define UWB3_CMD_TXPOWER            "txpower"
#define UWB3_CMD_ANTENNA            "antenna"
#define UWB3_CMD_DECAID             "decaid"
#define UWB3_CMD_VERSION            "version"

/**
 * @brief UWB 3 device response to commands.
 * @details Device response to commands.
 */
#define UWB3_RSP_OK                 "ok"
#define UWB3_RSP_ERROR              "error"

/**
 * @brief UWB 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define UWB3_TX_DRV_BUFFER_SIZE     100
#define UWB3_RX_DRV_BUFFER_SIZE     1000

/*! @} */ // uwb3_cmd

/**
 * @defgroup uwb3_map UWB 3 MikroBUS Map
 * @brief MikroBUS pin mapping of UWB 3 Click driver.
 */

/**
 * @addtogroup uwb3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UWB 3 Click to the selected MikroBUS.
 */
#define UWB3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // uwb3_map
/*! @} */ // uwb3

/**
 * @brief UWB 3 Click context object.
 * @details Context object definition of UWB 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset device pin. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ UWB3_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ UWB3_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} uwb3_t;

/**
 * @brief UWB 3 Click configuration object.
 * @details Configuration object definition of UWB 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset device pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} uwb3_cfg_t;

/**
 * @brief UWB 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UWB3_OK = 0,
    UWB3_ERROR = -1,
    UWB3_ERROR_TIMEOUT = -2

} uwb3_return_value_t;

/*!
 * @addtogroup uwb3 UWB 3 Click Driver
 * @brief API for configuring and manipulating UWB 3 Click driver.
 * @{
 */

/**
 * @brief UWB 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uwb3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uwb3_cfg_setup ( uwb3_cfg_t *cfg );

/**
 * @brief UWB 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #uwb3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uwb3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb3_init ( uwb3_t *ctx, uwb3_cfg_t *cfg );

/**
 * @brief UWB 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb3_generic_write ( uwb3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief UWB 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb3_generic_read ( uwb3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief UWB 3 send cmd function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #uwb3_t object definition for detailed explanation.
 * @param[in] cmd  Command buffer.
 * @return None.
 * @note None.
 */
void uwb3_send_cmd ( uwb3_t *ctx, uint8_t *cmd );

/**
 * @brief UWB 3 send cmd with parameter function.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #uwb3_t object definition for detailed explanation.
 * @param[in] cmd  Command buffer.
 * @param[in] param  Parameter buffer.
 * @return None.
 * @note None.
 */
void uwb3_send_cmd_with_parameter ( uwb3_t *ctx, uint8_t *cmd, uint8_t *param );

/**
 * @brief UWB 3 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #uwb3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void uwb3_set_rst_pin ( uwb3_t *ctx, uint8_t state );

/**
 * @brief UWB 3 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #uwb3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void uwb3_reset_device ( uwb3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // UWB3_H

/*! @} */ // uwb3

// ------------------------------------------------------------------------ END
