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
 * @file rak11720.h
 * @brief This file contains API for RAK11720 Click Driver.
 */

#ifndef RAK11720_H
#define RAK11720_H

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
 * @addtogroup rak11720 RAK11720 Click Driver
 * @brief API for configuring and manipulating RAK11720 Click driver.
 * @{
 */

/**
 * @defgroup rak11720_cmd RAK11720 Device Settings
 * @brief Settings for registers of RAK11720 Click driver.
 */

/**
 * @addtogroup rak11720_cmd
 * @{
 */

/**
 * @brief RAK11720 control commands.
 * @details Specified setting for control commands of RAK11720 Click driver.
 */
#define RAK11720_CMD_AT                                 "AT"
#define RAK11720_CMD_TOGGLE_ECHO                        "ATE"
#define RAK11720_CMD_FACTORY_RESET                      "ATR"
#define RAK11720_CMD_GET_MODEL_ID                       "AT+HWMODEL"
#define RAK11720_CMD_GET_FW_VERSION                     "AT+VER"
#define RAK11720_CMD_GET_SERIAL_NUMBER                  "AT+SN"
#define RAK11720_CMD_GET_BLE_MAC_ADDRESS                "AT+BLEMAC"
#define RAK11720_CMD_NETWORK_WORK_MODE                  "AT+NWM"
#define RAK11720_CMD_P2P_MODE_FREQUENCY                 "AT+PFREQ"
#define RAK11720_CMD_P2P_MODE_SPREADING_FACTOR          "AT+PSF"
#define RAK11720_CMD_P2P_MODE_BANDWIDTH                 "AT+PBW"
#define RAK11720_CMD_P2P_MODE_CODE_RATE                 "AT+PCR"
#define RAK11720_CMD_P2P_MODE_PREAMBLE_LENGTH           "AT+PPL"
#define RAK11720_CMD_P2P_MODE_TX_POWER                  "AT+PTP"
#define RAK11720_CMD_P2P_RX_MODE                        "AT+PRECV"
#define RAK11720_CMD_P2P_TX_MODE                        "AT+PSEND"

/**
 * @brief RAK11720 device response for AT commands.
 * @details Device response after commands.
 */
#define RAK11720_RSP_OK                                 "OK"
#define RAK11720_RSP_ERROR                              "AT_ERROR"
#define RAK11720_RSP_PARAM_ERROR                        "AT_PARAM_ERROR"
#define RAK11720_RSP_BUSY_ERROR                         "AT_BUSY_ERROR"
#define RAK11720_RSP_TEST_PARAM_OVERFLOW                "AT_TEST_PARAM_OVERFLOW"
#define RAK11720_RSP_NO_CLASSB_ENABLE                   "AT_NO_CLASSB_ENABLE"
#define RAK11720_RSP_NO_NETWORK_JOINED                  "AT_NO_NETWORK_JOINED"
#define RAK11720_RSP_RX_ERROR                           "AT_RX_ERROR"
#define RAK11720_RSP_INITIAL                            "----------------------"

/**
 * @brief RAK11720 device events settings.
 * @details Device events settings.
 */
#define RAK11720_EVT_RX_P2P                             "+EVT:RXP2P"
#define RAK11720_EVT_RX_P2P_ERROR                       "+EVT:RXP2P RECEIVE ERROR"
#define RAK11720_EVT_RX_P2P_TIMEOUT                     "+EVT:RXP2P RECEIVE TIMEOUT"
#define RAK11720_EVT_TX_P2P                             "+EVT:TXP2P"

/**
 * @brief RAK11720 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RAK11720_TX_DRV_BUFFER_SIZE                     200
#define RAK11720_RX_DRV_BUFFER_SIZE                     600

/*! @} */ // rak11720_cmd

/**
 * @defgroup rak11720_map RAK11720 MikroBUS Map
 * @brief MikroBUS pin mapping of RAK11720 Click driver.
 */

/**
 * @addtogroup rak11720_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RAK11720 Click to the selected MikroBUS.
 */
#define RAK11720_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.boot = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // rak11720_map
/*! @} */ // rak11720

/**
 * @brief RAK11720 Click context object.
 * @details Context object definition of RAK11720 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t boot;             /**< Boot pin (active high). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ RAK11720_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ RAK11720_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ RAK11720_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} rak11720_t;

/**
 * @brief RAK11720 Click configuration object.
 * @details Configuration object definition of RAK11720 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t boot;                /**< Boot pin (active high). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} rak11720_cfg_t;

/**
 * @brief RAK11720 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RAK11720_OK = 0,
    RAK11720_ERROR = -1,
    RAK11720_ERROR_TIMEOUT = -2,
    RAK11720_ERROR_CMD = -3

} rak11720_return_value_t;

/*!
 * @addtogroup rak11720 RAK11720 Click Driver
 * @brief API for configuring and manipulating RAK11720 Click driver.
 * @{
 */

/**
 * @brief RAK11720 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rak11720_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rak11720_cfg_setup ( rak11720_cfg_t *cfg );

/**
 * @brief RAK11720 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rak11720_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rak11720_init ( rak11720_t *ctx, rak11720_cfg_t *cfg );

/**
 * @brief RAK11720 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rak11720_generic_write ( rak11720_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief RAK11720 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rak11720_generic_read ( rak11720_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief RAK11720 set BOOT pin function.
 * @details This function sets the BOOT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rak11720_set_boot_pin ( rak11720_t *ctx, uint8_t state );

/**
 * @brief RAK11720 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rak11720_set_rst_pin ( rak11720_t *ctx, uint8_t state );

/**
 * @brief RAK11720 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rak11720_reset_device ( rak11720_t *ctx );

/**
 * @brief RAK11720 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void rak11720_cmd_run ( rak11720_t *ctx, uint8_t *cmd );

/**
 * @brief RAK11720 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void rak11720_cmd_set ( rak11720_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief RAK11720 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void rak11720_cmd_get ( rak11720_t *ctx, uint8_t *cmd );

/**
 * @brief RAK11720 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void rak11720_cmd_help ( rak11720_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // RAK11720_H

/*! @} */ // rak11720

// ------------------------------------------------------------------------ END
