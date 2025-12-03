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
 * @file rak4630.h
 * @brief This file contains API for RAK4630 Click Driver.
 */

#ifndef RAK4630_H
#define RAK4630_H

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
 * @addtogroup rak4630 RAK4630 Click Driver
 * @brief API for configuring and manipulating RAK4630 Click driver.
 * @{
 */

/**
 * @defgroup rak4630_cmd RAK4630 Device Settings
 * @brief Settings for registers of RAK4630 Click driver.
 */

/**
 * @addtogroup rak4630_cmd
 * @{
 */

/**
 * @brief RAK4630 control commands.
 * @details Specified setting for control commands of RAK4630 Click driver.
 */
#define RAK4630_CMD_AT                                  "AT"
#define RAK4630_CMD_TOGGLE_ECHO                         "ATE"
#define RAK4630_CMD_FACTORY_RESET                       "ATR"
#define RAK4630_CMD_GET_MODEL_ID                        "AT+HWMODEL"
#define RAK4630_CMD_GET_FW_VERSION                      "AT+VER"
#define RAK4630_CMD_GET_SERIAL_NUMBER                   "AT+SN"
#define RAK4630_CMD_GET_BLE_MAC_ADDRESS                 "AT+BLEMAC"
#define RAK4630_CMD_NETWORK_WORK_MODE                   "AT+NWM"
#define RAK4630_CMD_P2P_MODE_FREQUENCY                  "AT+PFREQ"
#define RAK4630_CMD_P2P_MODE_SPREADING_FACTOR           "AT+PSF"
#define RAK4630_CMD_P2P_MODE_BANDWIDTH                  "AT+PBW"
#define RAK4630_CMD_P2P_MODE_CODE_RATE                  "AT+PCR"
#define RAK4630_CMD_P2P_MODE_PREAMBLE_LENGTH            "AT+PPL"
#define RAK4630_CMD_P2P_MODE_TX_POWER                   "AT+PTP"
#define RAK4630_CMD_P2P_RX_MODE                         "AT+PRECV"
#define RAK4630_CMD_P2P_TX_MODE                         "AT+PSEND"

/**
 * @brief RAK4630 device response for AT commands.
 * @details Device response after commands.
 */
#define RAK4630_RSP_OK                                  "OK"
#define RAK4630_RSP_ERROR                               "AT_ERROR"
#define RAK4630_RSP_PARAM_ERROR                         "AT_PARAM_ERROR"
#define RAK4630_RSP_BUSY_ERROR                          "AT_BUSY_ERROR"
#define RAK4630_RSP_TEST_PARAM_OVERFLOW                 "AT_TEST_PARAM_OVERFLOW"
#define RAK4630_RSP_NO_CLASSB_ENABLE                    "AT_NO_CLASSB_ENABLE"
#define RAK4630_RSP_NO_NETWORK_JOINED                   "AT_NO_NETWORK_JOINED"
#define RAK4630_RSP_RX_ERROR                            "AT_RX_ERROR"
#define RAK4630_RSP_INITIAL                             "Current Work Mode"

/**
 * @brief RAK4630 device events settings.
 * @details Device events settings.
 */
#define RAK4630_EVT_RX_P2P                              "+EVT:RXP2P"
#define RAK4630_EVT_RX_P2P_ERROR                        "+EVT:RXP2P RECEIVE ERROR"
#define RAK4630_EVT_RX_P2P_TIMEOUT                      "+EVT:RXP2P RECEIVE TIMEOUT"
#define RAK4630_EVT_TX_P2P                              "+EVT:TXP2P"

/**
 * @brief RAK4630 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RAK4630_TX_DRV_BUFFER_SIZE                      200
#define RAK4630_RX_DRV_BUFFER_SIZE                      600

/*! @} */ // rak4630_cmd

/**
 * @defgroup rak4630_map RAK4630 MikroBUS Map
 * @brief MikroBUS pin mapping of RAK4630 Click driver.
 */

/**
 * @addtogroup rak4630_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RAK4630 Click to the selected MikroBUS.
 */
#define RAK4630_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // rak4630_map
/*! @} */ // rak4630

/**
 * @brief RAK4630 Click context object.
 * @details Context object definition of RAK4630 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    
    // Input pins
    digital_in_t an;                /**< AN pin input. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ RAK4630_RX_DRV_BUFFER_SIZE ];   /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ RAK4630_TX_DRV_BUFFER_SIZE ];   /**< TX Buffer size. */
    uint8_t cmd_buffer[ RAK4630_TX_DRV_BUFFER_SIZE ];       /**< Command buffer. */

} rak4630_t;

/**
 * @brief RAK4630 Click configuration object.
 * @details Configuration object definition of RAK4630 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t an;                  /**< AN pin input. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} rak4630_cfg_t;

/**
 * @brief RAK4630 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RAK4630_OK = 0,
    RAK4630_ERROR = -1,
    RAK4630_ERROR_TIMEOUT = -2,
    RAK4630_ERROR_CMD = -3

} rak4630_return_value_t;

/*!
 * @addtogroup rak4630 RAK4630 Click Driver
 * @brief API for configuring and manipulating RAK4630 Click driver.
 * @{
 */

/**
 * @brief RAK4630 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rak4630_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rak4630_cfg_setup ( rak4630_cfg_t *cfg );

/**
 * @brief RAK4630 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rak4630_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rak4630_init ( rak4630_t *ctx, rak4630_cfg_t *cfg );

/**
 * @brief RAK4630 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rak4630_generic_write ( rak4630_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief RAK4630 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rak4630_generic_read ( rak4630_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief RAK4630 get AN pin function.
 * @details This function returns the AN pin logic state.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rak4630_get_an_pin ( rak4630_t *ctx );

/**
 * @brief RAK4630 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rak4630_set_rst_pin ( rak4630_t *ctx, uint8_t state );

/**
 * @brief RAK4630 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rak4630_reset_device ( rak4630_t *ctx );

/**
 * @brief RAK4630 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void rak4630_cmd_run ( rak4630_t *ctx, uint8_t *cmd );

/**
 * @brief RAK4630 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void rak4630_cmd_set ( rak4630_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief RAK4630 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void rak4630_cmd_get ( rak4630_t *ctx, uint8_t *cmd );

/**
 * @brief RAK4630 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void rak4630_cmd_help ( rak4630_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // RAK4630_H

/*! @} */ // rak4630

// ------------------------------------------------------------------------ END
