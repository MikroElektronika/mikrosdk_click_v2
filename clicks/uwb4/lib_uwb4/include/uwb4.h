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
 * @file uwb4.h
 * @brief This file contains API for UWB 4 Click Driver.
 */

#ifndef UWB4_H
#define UWB4_H

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
 * @addtogroup uwb4 UWB 4 Click Driver
 * @brief API for configuring and manipulating UWB 4 Click driver.
 * @{
 */

/**
 * @defgroup uwb4_cmd UWB 4 Device Settings
 * @brief Settings for registers of UWB 4 Click driver.
 */

/**
 * @addtogroup uwb4_cmd
 * @{
 */

/**
 * @brief UWB 4 control commands.
 * @details Specified setting for control commands of UWB 4 Click driver.
 */
#define UWB4_CMD_AT                     "AT"
#define UWB4_CMD_DISABLE_ECHO           "ATE0"
#define UWB4_CMD_ENABLE_ECHO            "ATE1"
#define UWB4_CMD_GET_MODULE_NAME        "ATI0"
#define UWB4_CMD_GET_FIRMWARE_VERSION   "ATI3"
#define UWB4_CMD_GET_BLE_ADDRESS        "ATI4"
#define UWB4_CMD_GET_UNIQUE_ID          "ATI5"
#define UWB4_CMD_GET_LAST_RESET_REASON  "ATI2001"
#define UWB4_CMD_GET_FREE_MEMORY        "ATI2002"
#define UWB4_CMD_GET_ALLOCATED_MEMORY   "ATI2003"
#define UWB4_CMD_RESET_MODULE           "ATZ"
#define UWB4_CMD_CREATE_SESSION         "AT+UWBS"
#define UWB4_CMD_DELETE_SESSION         "AT+UWBSD"
#define UWB4_CMD_SET_ADDRESS            "AT+UWBSA"
#define UWB4_CMD_ADD_PEER               "AT+UWBSAM"
#define UWB4_CMD_REMOVE_PEER            "AT+UWBSAMX"
#define UWB4_CMD_SET_RANGING_INTERVAL   "AT+UWBSI"
#define UWB4_CMD_SET_SESSION_CONFIG     "AT+UWBSC"
#define UWB4_CMD_START_SESSION          "AT+UWBSS"

/**
 * @brief UWB 4 device response for AT commands.
 * @details Device response after commands.
 */
#define UWB4_RSP_OK                     "OK"
#define UWB4_RSP_ERROR                  "ERROR"
#define UWB4_RSP_RANGE                  "RANGE:"

/**
 * @brief UWB 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define UWB4_TX_DRV_BUFFER_SIZE         256
#define UWB4_RX_DRV_BUFFER_SIZE         256

/*! @} */ // uwb4_cmd

/**
 * @defgroup uwb4_map UWB 4 MikroBUS Map
 * @brief MikroBUS pin mapping of UWB 4 Click driver.
 */

/**
 * @addtogroup uwb4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UWB 4 Click to the selected MikroBUS.
 */
#define UWB4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.btn = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // uwb4_map
/*! @} */ // uwb4

/**
 * @brief UWB 4 Click context object.
 * @details Context object definition of UWB 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset device (active low). */

    // Input pins
    digital_in_t btn;               /**< Button pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ UWB4_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ UWB4_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ UWB4_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} uwb4_t;

/**
 * @brief UWB 4 Click configuration object.
 * @details Configuration object definition of UWB 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset device (active low). */
    pin_name_t btn;                 /**< Button pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} uwb4_cfg_t;

/**
 * @brief UWB 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UWB4_OK = 0,
    UWB4_ERROR = -1,
    UWB4_ERROR_TIMEOUT = -2,
    UWB4_ERROR_CMD = -3

} uwb4_return_value_t;

/*!
 * @addtogroup uwb4 UWB 4 Click Driver
 * @brief API for configuring and manipulating UWB 4 Click driver.
 * @{
 */

/**
 * @brief UWB 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uwb4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uwb4_cfg_setup ( uwb4_cfg_t *cfg );

/**
 * @brief UWB 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #uwb4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uwb4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb4_init ( uwb4_t *ctx, uwb4_cfg_t *cfg );

/**
 * @brief UWB 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb4_generic_write ( uwb4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief UWB 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #uwb4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uwb4_generic_read ( uwb4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief UWB 4 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #uwb4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void uwb4_set_rst_pin ( uwb4_t *ctx, uint8_t state );

/**
 * @brief UWB 4 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #uwb4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void uwb4_reset_device ( uwb4_t *ctx );

/**
 * @brief UWB 4 get BTN pin function.
 * @details This function returns the button pin logic state.
 * @param[in] ctx : Click context object.
 * See #uwb4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t uwb4_get_btn_pin ( uwb4_t *ctx );

/**
 * @brief UWB 4 cmd run function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #uwb4_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void uwb4_cmd_run ( uwb4_t *ctx, uint8_t *cmd );

/**
 * @brief UWB 4 cmd set function.
 * @details This function sets a value to a specified command of the click module.
 * @param[in] ctx : Click context object.
 * See #uwb4_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void uwb4_cmd_set ( uwb4_t *ctx, uint8_t *cmd, uint8_t *value );

#ifdef __cplusplus
}
#endif
#endif // UWB4_H

/*! @} */ // uwb4

// ------------------------------------------------------------------------ END
