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
 * @file aiwb212f.h
 * @brief This file contains API for Ai-WB2-12F Click Driver.
 */

#ifndef AIWB212F_H
#define AIWB212F_H

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
 * @addtogroup aiwb212f Ai-WB2-12F Click Driver
 * @brief API for configuring and manipulating Ai-WB2-12F Click driver.
 * @{
 */

/**
 * @defgroup aiwb212f_cmd Ai-WB2-12F Device Settings
 * @brief Settings for registers of Ai-WB2-12F Click driver.
 */

/**
 * @addtogroup aiwb212f_cmd
 * @{
 */

/**
 * @brief Ai-WB2-12F control commands.
 * @details Specified setting for control commands of Ai-WB2-12F Click driver.
 */
#define AIWB212F_CMD_AT                             "AT"
#define AIWB212F_CMD_AT_HELP                        "AT+HELP"
#define AIWB212F_CMD_AT_SW_RESET                    "AT+RST"
#define AIWB212F_CMD_AT_GMR                         "AT+GMR"
#define AIWB212F_CMD_AT_SLEEP                       "AT+SLEEP"
#define AIWB212F_CMD_AT_SYSIOMAP                    "AT+SYSIOMAP"
#define AIWB212F_CMD_AT_SYSGPIOWRITE                "AT+SYSGPIOWRITE"
#define AIWB212F_CMD_AT_SYSGPIOREAD                 "AT+SYSGPIOREAD"
#define AIWB212F_CMD_AT_PWMCFG                      "AT+PWMCFG"
#define AIWB212F_CMD_AT_PWMCFGS                     "AT+PWMCFGS"
#define AIWB212F_CMD_AT_PWMSTOP                     "AT+PWMSTOP"
#define AIWB212F_CMD_AT_PWMDUTYSET                  "AT+PWMDUTYSET"
#define AIWB212F_CMD_AT_PWMDUTYSETS                 "AT+PWMDUTYSETS"
#define AIWB212F_CMD_AT_WMODE                       "AT+WMODE"
#define AIWB212F_CMD_AT_WSCAN                       "AT+WSCAN"
#define AIWB212F_CMD_AT_WSDHCP                      "AT+WSDHCP"
#define AIWB212F_CMD_AT_WJAP                        "AT+WJAP"
#define AIWB212F_CMD_AT_WAUTOCONN                   "AT+WAUTOCONN"
#define AIWB212F_CMD_AT_WAPDHCP                     "AT+WAPDHCP"
#define AIWB212F_CMD_AT_WAP                         "AT+WAP"
#define AIWB212F_CMD_AT_PING                        "AT+PING"
#define AIWB212F_CMD_AT_CIPSTAMAC_DEF               "AT+CIPSTAMAC_DEF"
#define AIWB212F_CMD_AT_WCOUNTRY                    "AT+WCOUNTRY"
#define AIWB212F_CMD_AT_WCONFIG                     "AT+WCONFIG"
#define AIWB212F_CMD_AT_SOCKET                      "AT+SOCKET"
#define AIWB212F_CMD_AT_SOCKETSEND                  "AT+SOCKETSEND"
#define AIWB212F_CMD_AT_SOCKETSENDLINE              "AT+SOCKETSENDLINE"
#define AIWB212F_CMD_AT_SOCKETREAD                  "AT+SOCKETREAD"
#define AIWB212F_CMD_AT_SOCKETDEL                   "AT+SOCKETDEL"
#define AIWB212F_CMD_AT_SOCKETRECVCFG               "AT+SOCKETRECVCFG"
#define AIWB212F_CMD_AT_SOCKETTT                    "AT+SOCKETTT"
#define AIWB212F_CMD_AT_MQTT                        "AT+MQTT"
#define AIWB212F_CMD_AT_MQTTPUB                     "AT+MQTTPUB"
#define AIWB212F_CMD_AT_MQTTPUBRAW                  "AT+MQTTPUBRAW"
#define AIWB212F_CMD_AT_MQTTSUB                     "AT+MQTTSUB"
#define AIWB212F_CMD_AT_BLEMAC                      "AT+BLEMAC"
#define AIWB212F_CMD_AT_BLEMODE                     "AT+BLEMODE"
#define AIWB212F_CMD_AT_BLERFPWR                    "AT+BLERFPWR"
#define AIWB212F_CMD_AT_BLENAME                     "AT+BLENAME"

/**
 * @brief Ai-WB2-12F response codes.
 * @details Specified response codes of Ai-WB2-12F Click driver.
 */
#define AIWB212F_RSP_OK                             "OK"
#define AIWB212F_RSP_ERROR                          "ERROR"
#define AIWB212F_RSP_READY                          "ready"

/**
 * @brief Ai-WB2-12F driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define AIWB212F_TX_DRV_BUFFER_SIZE                 100
#define AIWB212F_RX_DRV_BUFFER_SIZE                 300

/*! @} */ // aiwb212f_cmd

/**
 * @defgroup aiwb212f_map Ai-WB2-12F MikroBUS Map
 * @brief MikroBUS pin mapping of Ai-WB2-12F Click driver.
 */

/**
 * @addtogroup aiwb212f_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ai-WB2-12F Click to the selected MikroBUS.
 */
#define AIWB212F_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // aiwb212f_map
/*! @} */ // aiwb212f

/**
 * @brief Ai-WB2-12F Click context object.
 * @details Context object definition of Ai-WB2-12F Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;                                       /**< Enable pin. */

    // Modules
    uart_t uart;                                            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ AIWB212F_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ AIWB212F_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} aiwb212f_t;

/**
 * @brief Ai-WB2-12F Click configuration object.
 * @details Configuration object definition of Ai-WB2-12F Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t en;                              /**< Enable pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} aiwb212f_cfg_t;

/**
 * @brief Ai-WB2-12F Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AIWB212F_OK = 0,
    AIWB212F_ERROR = -1,
    AIWB212F_ERROR_TIMEOUT = -2,
    AIWB212F_ERROR_CMD = -3,
    AIWB212F_ERROR_UNKNOWN = -4

} aiwb212f_return_value_t;

/*!
 * @addtogroup aiwb212f Ai-WB2-12F Click Driver
 * @brief API for configuring and manipulating Ai-WB2-12F Click driver.
 * @{
 */

/**
 * @brief Ai-WB2-12F configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #aiwb212f_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void aiwb212f_cfg_setup ( aiwb212f_cfg_t *cfg );

/**
 * @brief Ai-WB2-12F initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #aiwb212f_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #aiwb212f_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t aiwb212f_init ( aiwb212f_t *ctx, aiwb212f_cfg_t *cfg );

/**
 * @brief Ai-WB2-12F default configuration function.
 * @details This function executes a default configuration of Ai-WB2-12F
 * Click board.
 * @param[in] ctx : Click context object.
 * See #aiwb212f_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t aiwb212f_default_cfg ( aiwb212f_t *ctx );

/**
 * @brief Ai-WB2-12F data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #aiwb212f_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t aiwb212f_generic_write ( aiwb212f_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Ai-WB2-12F data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #aiwb212f_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t aiwb212f_generic_read ( aiwb212f_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Ai-WB2-12F hardware reset function.
 * @details This function is used to perform a hardware reset of the device.
 * @param[in] ctx : Click context object.
 * See #aiwb212f_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void aiwb212f_hw_reset ( aiwb212f_t *ctx );

/**
 * @brief Ai-WB2-12F send command function.
 * @details This function is used to send a desired command.
 * @param[in] ctx : Click context object.
 * See #aiwb212f_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @return Nothing.
 * @note None.
 */
void aiwb212f_send_cmd ( aiwb212f_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Ai-WB2-12F send command with parameter function.
 * @details This function sends a desired command with the parameter.
 * @param[in] ctx : Click context object.
 * See #aiwb212f_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @param[in] param_buf : Parameters string.
 * @return Nothing.
 * @note None.
 */
void aiwb212f_send_cmd_with_par ( aiwb212f_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Ai-WB2-12F send command check function.
 * @details This function sends a desired command with the question mark for checking parameters.
 * @param[in] ctx : Click context object.
 * See #aiwb212f_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @return Nothing.
 * @note None.
 */
void aiwb212f_send_cmd_check ( aiwb212f_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Ai-WB2-12F set gpio pin state function.
 * @details This function sends a command to change state of the selected GPIO pin.
 * @param[in] ctx : Click context object.
 * See #aiwb212f_t object definition for detailed explanation.
 * @param[in] pin : Selected pin.
 * @param[in] pin : Pin state.
 * @return Nothing.
 * @note None.
 */
void aiwb212f_set_gpio ( aiwb212f_t *ctx, uint8_t *pin, uint8_t *state );

#ifdef __cplusplus
}
#endif
#endif // AIWB212F_H

/*! @} */ // aiwb212f

// ------------------------------------------------------------------------ END
