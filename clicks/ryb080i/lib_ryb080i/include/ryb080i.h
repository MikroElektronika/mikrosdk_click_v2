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
 * @file ryb080i.h
 * @brief This file contains API for RYB080I Click Driver.
 */

#ifndef RYB080I_H
#define RYB080I_H

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
 * @addtogroup ryb080i RYB080I Click Driver
 * @brief API for configuring and manipulating RYB080I Click driver.
 * @{
 */

/**
 * @defgroup ryb080i_cmd RYB080I Device Settings
 * @brief Settings for registers of RYB080I Click driver.
 */

/**
 * @addtogroup ryb080i_cmd
 * @{
 */

/**
 * @brief RYB080I control commands.
 * @details Specified setting for control commands of RYB080I Click driver.
 */
#define RYB080I_CMD_AT                          "AT"
#define RYB080I_CMD_SW_RESET                    "AT+RESET"
#define RYB080I_CMD_BROADCAST_NAME              "AT+NAME"
#define RYB080I_CMD_DEVICE_NAME                 "AT+ATTR"
#define RYB080I_CMD_OUTPUT_POWER                "AT+CPFOP"
#define RYB080I_CMD_CONNECTION_ENABLE           "AT+CNE"
#define RYB080I_CMD_BROADCAST_PERIOD            "AT+PERIOD"
#define RYB080I_CMD_POWER_MODE                  "AT+PWMODE"
#define RYB080I_CMD_ADVERTISING_ENABLE          "AT+CFUN"
#define RYB080I_CMD_BAUD_RATE                   "AT+IPR"
#define RYB080I_CMD_INQUIRE_MAC_ADDRESS         "AT+ADDR"
#define RYB080I_CMD_END_KEY_ENABLE              "AT+ENTER"
#define RYB080I_CMD_CONNECTION_STATUS           "AT+CONNECT"
#define RYB080I_CMD_CONNECT_MAC                 "AT+CON"
#define RYB080I_CMD_CONNECT_NUM                 "AT+CONT"
#define RYB080I_CMD_DISCONNECT                  "AT+DCON"
#define RYB080I_CMD_GPIO_OUT                    "AT+GPIO"
#define RYB080I_CMD_SW_VERSION                  "AT+CGMS"

/**
 * @brief RYB080I device response to AT commands.
 * @details Device response to commands.
 */
#define RYB080I_RSP_OK                          "OK"
#define RYB080I_RSP_FOUND                       "Found"
#define RYB080I_RSP_READY                       "READY"
#define RYB080I_RSP_GENERIC                     "+"
#define RYB080I_RSP_CONNECTED                   "+++++"
#define RYB080I_RSP_DISCONNECTED                "-----"
#define RYB080I_RSP_NO_CONNECTIONS              "CONNECT=0,0"

/**
 * @brief RYB080I driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RYB080I_TX_DRV_BUFFER_SIZE              200
#define RYB080I_RX_DRV_BUFFER_SIZE              600

/*! @} */ // ryb080i_cmd

/**
 * @defgroup ryb080i_map RYB080I MikroBUS Map
 * @brief MikroBUS pin mapping of RYB080I Click driver.
 */

/**
 * @addtogroup ryb080i_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RYB080I Click to the selected MikroBUS.
 */
#define RYB080I_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // ryb080i_map
/*! @} */ // ryb080i

/**
 * @brief RYB080I Click context object.
 * @details Context object definition of RYB080I Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ RYB080I_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ RYB080I_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ RYB080I_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} ryb080i_t;

/**
 * @brief RYB080I Click configuration object.
 * @details Configuration object definition of RYB080I Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} ryb080i_cfg_t;

/**
 * @brief RYB080I Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RYB080I_OK = 0,
    RYB080I_ERROR = -1,
    RYB080I_ERROR_TIMEOUT = -2,
    RYB080I_ERROR_CMD = -3

} ryb080i_return_value_t;

/*!
 * @addtogroup ryb080i RYB080I Click Driver
 * @brief API for configuring and manipulating RYB080I Click driver.
 * @{
 */

/**
 * @brief RYB080I configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ryb080i_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ryb080i_cfg_setup ( ryb080i_cfg_t *cfg );

/**
 * @brief RYB080I initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ryb080i_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ryb080i_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ryb080i_init ( ryb080i_t *ctx, ryb080i_cfg_t *cfg );

/**
 * @brief RYB080I data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ryb080i_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ryb080i_generic_write ( ryb080i_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief RYB080I data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ryb080i_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ryb080i_generic_read ( ryb080i_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief RYB080I set rst pin function.
 * @details This function sets the reset (RST) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ryb080i_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ryb080i_set_rst_pin ( ryb080i_t *ctx, uint8_t state );

/**
 * @brief RYB080I reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #ryb080i_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ryb080i_reset_device ( ryb080i_t *ctx );

/**
 * @brief RYB080I cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ryb080i_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ryb080i_cmd_run ( ryb080i_t *ctx, uint8_t *cmd );

/**
 * @brief RYB080I cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #ryb080i_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param : Parameters string.
 * @return None.
 * @note None.
 */
void ryb080i_cmd_set ( ryb080i_t *ctx, uint8_t *cmd, uint8_t *param );

/**
 * @brief RYB080I cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #ryb080i_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void ryb080i_cmd_get ( ryb080i_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // RYB080I_H

/*! @} */ // ryb080i

// ------------------------------------------------------------------------ END
