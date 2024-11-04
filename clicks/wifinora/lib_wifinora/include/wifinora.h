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
 * @file wifinora.h
 * @brief This file contains API for WiFi NORA Click Driver.
 */

#ifndef WIFINORA_H
#define WIFINORA_H

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
 * @addtogroup wifinora WiFi NORA Click Driver
 * @brief API for configuring and manipulating WiFi NORA Click driver.
 * @{
 */

/**
 * @defgroup wifinora_cmd WiFi NORA Device Settings
 * @brief Settings for registers of WiFi NORA Click driver.
 */

/**
 * @addtogroup wifinora_cmd
 * @{
 */

/**
 * @brief WiFi NORA control commands.
 * @details Specified setting for control commands of WiFi NORA Click driver.
 */
#define WIFINORA_CMD_AT                             "AT"
#define WIFINORA_CMD_AT_USYFR                       "AT+USYFR"
#define WIFINORA_CMD_AT_GMM                         "AT+GMM"
#define WIFINORA_CMD_AT_SW_RESET                    "AT+CPWROFF"
#define WIFINORA_CMD_AT_UWAPC                       "AT+UWAPC"
#define WIFINORA_CMD_AT_UWSCP                       "AT+UWSCP"
#define WIFINORA_CMD_AT_UWSIPD                      "AT+UWSIPD"
#define WIFINORA_CMD_AT_UWSSW                       "AT+UWSSW"
#define WIFINORA_CMD_AT_UWSC                        "AT+UWSC"
#define WIFINORA_CMD_AT_USOCR                       "AT+USOCR"
#define WIFINORA_CMD_AT_USOC                        "AT+USOC"
#define WIFINORA_CMD_AT_USOWS                       "AT+USOWS"
#define WIFINORA_CMD_AT_USORS                       "AT+USORS"
#define WIFINORA_CMD_AT_USOCL                       "AT+USOCL"

/**
 * @brief WiFi NORA response codes.
 * @details Specified response codes of WiFi NORA Click driver.
 */
#define WIFINORA_RSP_OK                             "OK"
#define WIFINORA_RSP_ERROR                          "ERROR"
#define WIFINORA_RSP_READY                          "+STARTUP"

/**
 * @brief WiFi NORA pin states.
 * @details Specified pin states of WiFi NORA Click driver.
 */
#define WIFINORA_PIN_STATE_HIGH                     0x01
#define WIFINORA_PIN_STATE_LOW                      0x00

/**
 * @brief WiFi NORA driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define WIFINORA_TX_DRV_BUFFER_SIZE    100
#define WIFINORA_RX_DRV_BUFFER_SIZE    300

/*! @} */ // wifinora_cmd

/**
 * @defgroup wifinora_map WiFi NORA MikroBUS Map
 * @brief MikroBUS pin mapping of WiFi NORA Click driver.
 */

/**
 * @addtogroup wifinora_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of WiFi NORA Click to the selected MikroBUS.
 */
#define WIFINORA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.whs = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wkp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // wifinora_map
/*! @} */ // wifinora

/**
 * @brief WiFi NORA Click context object.
 * @details Context object definition of WiFi NORA Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wkp;              /**< Wake up pin. */
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t cts;              /**< Clear to send pin. */

    // Input pins
    digital_in_t whs;               /**< Wake host pin. */
    digital_in_t rts;               /**< Ready to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ WIFINORA_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ WIFINORA_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} wifinora_t;

/**
 * @brief WiFi NORA Click configuration object.
 * @details Configuration object definition of WiFi NORA Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t wkp;                 /**< Wake up pin. */
    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t cts;                 /**< Clear to send pin. */
    pin_name_t whs;                 /**< Wake host pin. */
    pin_name_t rts;                 /**< Ready to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} wifinora_cfg_t;

/**
 * @brief WiFi NORA Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WIFINORA_OK = 0,
    WIFINORA_ERROR = -1,
    WIFINORA_ERROR_TIMEOUT = -2,
    WIFINORA_ERROR_CMD = -3,
    WIFINORA_ERROR_UNKNOWN = -4

} wifinora_return_value_t;

/*!
 * @addtogroup wifinora WiFi NORA Click Driver
 * @brief API for configuring and manipulating WiFi NORA Click driver.
 * @{
 */

/**
 * @brief WiFi NORA configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #wifinora_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void wifinora_cfg_setup ( wifinora_cfg_t *cfg );

/**
 * @brief WiFi NORA initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wifinora_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifinora_init ( wifinora_t *ctx, wifinora_cfg_t *cfg );

/**
 * @brief WiFi NORA data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifinora_generic_write ( wifinora_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WiFi NORA data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifinora_generic_read ( wifinora_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief WiFi NORA set RST pin function.
 * @details This function is used to set RST pin state.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @param[in] pin_state : State of the RST pin.
 * @return Nothing.
 * @note None.
 */
void wifinora_set_rst_pin ( wifinora_t *ctx, uint8_t pin_state );

/**
 * @brief WiFi NORA set WKP pin function.
 * @details This function is used to set WKP pin state.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @param[in] pin_state : State of the WKP pin.
 * @return Nothing.
 * @note None.
 */
void wifinora_set_wkp_pin ( wifinora_t *ctx, uint8_t pin_state );

/**
 * @brief WiFi NORA set CTS pin function.
 * @details This function is used to set CTS pin state.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @param[in] pin_state : State of the CTS pin.
 * @return Nothing.
 * @note None.
 */
void wifinora_set_cts_pin ( wifinora_t *ctx, uint8_t pin_state );

/**
 * @brief WiFi NORA get WHS pin state function.
 * @details This function is used to get WHS pin state.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @return State of the WHS pin.
 * @note None.
 */
uint8_t wifinora_get_whs_pin ( wifinora_t *ctx );

/**
 * @brief WiFi NORA get RTS pin state function.
 * @details This function is used to get RTS pin state.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @return State of the RTS pin.
 * @note None.
 */
uint8_t wifinora_get_rts_pin ( wifinora_t *ctx );

/**
 * @brief WiFi NORA HW reset function.
 * @details This function is used to perform HW reset.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void wifinora_hw_reset ( wifinora_t *ctx );

/**
 * @brief WiFi NORA send command function.
 * @details This function is used to send a desired command.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @return Nothing.
 * @note None.
 */
void wifinora_send_cmd ( wifinora_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief WiFi NORA send command with parameter function.
 * @details This function sends a desired command with the parameter.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @param[in] param_buf : Parameters string.
 * @return Nothing.
 * @note None.
 */
void wifinora_send_cmd_with_par ( wifinora_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief WiFi NORA send command check function.
 * @details This function sends a desired command with the question mark for checking parameters.
 * @param[in] ctx : Click context object.
 * See #wifinora_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @return Nothing.
 * @note None.
 */
void wifinora_send_cmd_check ( wifinora_t *ctx, uint8_t *at_cmd_buf );

#ifdef __cplusplus
}
#endif
#endif // WIFINORA_H

/*! @} */ // wifinora

// ------------------------------------------------------------------------ END
