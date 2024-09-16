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
 * @file b102c.h
 * @brief This file contains API for B102C Click Driver.
 */

#ifndef B102C_H
#define B102C_H

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
 * @addtogroup b102c B102C Click Driver
 * @brief API for configuring and manipulating B102C Click driver.
 * @{
 */

/**
 * @defgroup b102c_cmd B102C Device Settings
 * @brief Settings for registers of B102C Click driver.
 */

/**
 * @addtogroup b102c_cmd
 * @{
 */

/**
 * @brief B102C control commands.
 * @details Specified setting for control commands of B102C Click driver.
 */
#define B102C_CMD_AT                "AT"
#define B102C_CMD_RESET             "AT+RESET"
#define B102C_CMD_LADDR             "AT+LADDR"
#define B102C_CMD_NAME              "AT+NAME"
#define B102C_CMD_PIN               "AT+PIN"
#define B102C_CMD_BAUD              "AT+BAUD"
#define B102C_CMD_ADVMOD            "AT+ADVMOD"
#define B102C_CMD_ADVEN             "AT+ADVEN"
#define B102C_CMD_ADVINT            "AT+ADVINT"
#define B102C_CMD_POWER             "AT+POWER"
#define B102C_CMD_ROLE              "AT+ROLE"
#define B102C_CMD_INQ               "AT+INQ"
#define B102C_CMD_SINQ              "AT+SINQ"
#define B102C_CMD_SCANRLT           "AT+SCANRLT"
#define B102C_CMD_CONN              "AT+CONN"
#define B102C_CMD_SLEEP             "AT+SLEEP"
#define B102C_CMD_PAIR              "AT+PAIR"
#define B102C_CMD_DEFAULT           "AT+DEFAULT"
#define B102C_CMD_XXX               "AT+XXX"
#define B102C_CMD_ENTERDTS          "AT+ENTERDTS"
#define B102C_CMD_GPIOCFG           "AT+GPIOCFG"
#define B102C_CMD_RSSI              "AT+RSSI"
#define B102C_CMD_MUUID             "AT+MUUID"

/**
 * @brief B102C response.
 * @details Specified response settings of B102C Click driver.
 */
#define B102C_RSP_OK                "OK"
#define B102C_RSP_ERROR             "ERR"
#define B102C_RSP_READY             "Ready"

/**
 * @brief B102C pin state settings.
 * @details Specified pin states of B102C Click driver.
 */
#define B102C_PIN_STATE_HIGH        0x01
#define B102C_PIN_STATE_LOW         0x00

/**
 * @brief B102C driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define B102C_TX_DRV_BUFFER_SIZE    100
#define B102C_RX_DRV_BUFFER_SIZE    300

/*! @} */ // b102c_cmd

/**
 * @defgroup b102c_map B102C MikroBUS Map
 * @brief MikroBUS pin mapping of B102C Click driver.
 */

/**
 * @addtogroup b102c_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of B102C Click to the selected MikroBUS.
 */
#define B102C_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // b102c_map
/*! @} */ // b102c

/**
 * @brief B102C Click context object.
 * @details Context object definition of B102C Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset pin. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ B102C_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ B102C_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} b102c_t;

/**
 * @brief B102C Click configuration object.
 * @details Configuration object definition of B102C Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} b102c_cfg_t;

/**
 * @brief B102C Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    B102C_OK = 0,
    B102C_ERROR = -1,
    B102C_OVERFLOW = -2,
    B102C_TIMEOUT = -3

} b102c_return_value_t;

/*!
 * @addtogroup b102c B102C Click Driver
 * @brief API for configuring and manipulating B102C Click driver.
 * @{
 */

/**
 * @brief B102C configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #b102c_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void b102c_cfg_setup ( b102c_cfg_t *cfg );

/**
 * @brief B102C initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #b102c_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t b102c_init ( b102c_t *ctx, b102c_cfg_t *cfg );

/**
 * @brief B102C default configuration function.
 * @details This function executes a default configuration of B102C
 * click board.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t b102c_default_cfg ( b102c_t *ctx );

/**
 * @brief B102C data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t b102c_generic_write ( b102c_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief B102C data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t b102c_generic_read ( b102c_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief B102C set RST pin state function.
 * @details This function is used to set state of the RST pin of the B102C Click module.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @param[in] pin_state : State of the RST pin.
 * @return Nothing.
 * @note None.
 */
void b102c_set_rst_pin ( b102c_t *ctx, uint8_t pin_state );

/**
 * @brief B102C hardware reset function.
 * @details This function is used to perform a hardware reset of the B102C Click module.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void b102c_hw_reset ( b102c_t *ctx );

/**
 * @brief B102C send command function.
 * @details This function sends a specified command to the B102C Click module.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 * @return Nothing.
 * @note None.
 */
void b102c_send_cmd ( b102c_t *ctx, uint8_t *cmd );

/**
 * @brief B102C send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void b102c_send_cmd_with_params ( b102c_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief B102C check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void b102c_send_cmd_check ( b102c_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief B102C check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void b102c_send_cmd_params_check ( b102c_t *ctx, uint8_t *at_cmd_buf );

#ifdef __cplusplus
}
#endif
#endif // B102C_H

/*! @} */ // b102c

// ------------------------------------------------------------------------ END
