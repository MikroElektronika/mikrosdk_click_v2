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
 * @file lpwifi.h
 * @brief This file contains API for LP WiFi Click Driver.
 */

#ifndef LPWIFI_H
#define LPWIFI_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup lpwifi LP WiFi Click Driver
 * @brief API for configuring and manipulating LP WiFi Click driver.
 * @{
 */

/**
 * @defgroup lpwifi_reg LP WiFi Commands List
 * @brief List of commands of LP WiFi Click driver.
 */

/**
 * @addtogroup lpwifi_reg
 * @{
 */

/**
 * @brief LP WiFi - Basic AT commands.
 * @details Specified basic AT Commands for communication with LP WiFi Click board.
 */
#define LPWIFI_CMD_AT            "AT"
#define LPWIFI_CMD_ATZ           "ATZ"
#define LPWIFI_CMD_ATE           "ATE"
#define LPWIFI_CMD_ATF           "ATF"

/**
 * @brief LP WiFi - WiFi AT commands.
 * @details Specified WiFi AT Commands for communication with LP WiFi Click board.
 */
#define LPWIFI_CMD_WFMODE        "AT+WFMODE"
#define LPWIFI_CMD_WFJAPA        "AT+WFJAPA"

/**
 * @brief LP WiFi - Transfer AT commands.
 * @details Specified Transfer AT Commands for communication with LP WiFi Click board.
 */
#define LPWIFI_CMD_TRTS          "AT+TRTS"
#define LPWIFI_CMD_TRUSE         "AT+TRUSE"

/**
 * @brief LP WiFi - PWM output test commands.
 * @details Specified PWM output test commands for communication with LP WiFi Click board.
 */
#define LPWIFI_CMD_PWMINIT       "AT+PWMINIT"
#define LPWIFI_CMD_PWMSTART      "AT+PWMSTART"
#define LPWIFI_CMD_PWMSTOP       "AT+PWMSTOP"

/**
 * @brief LP WiFi - I2C read/write test commands.
 * @details Specified I2C read/write test commands for communication with LP WiFi Click board.
 */
#define LPWIFI_CMD_I2CINIT       "AT+I2CINIT"
#define LPWIFI_CMD_I2CREAD       "AT+I2CREAD"
#define LPWIFI_CMD_I2CWRITE      "AT+I2CWRITE"

/*! @} */ // lpwifi_reg

/**
 * @defgroup lpwifi_set LP WiFi Device Settings
 * @brief Settings for registers of LP WiFi Click driver.
 */

/**
 * @addtogroup lpwifi_set
 * @{
 */

/**
 * @brief LP WiFi - WiFi mode setting.
 * @details Specified setting for WiFi mode.
 */
#define LPWIFI_MODE_STA          0
#define LPWIFI_MODE_SOFT_AP      1

/**
 * @brief LP WiFi driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE          400

/*! @} */ // lpwifi_set

/**
 * @defgroup lpwifi_map LP WiFi MikroBUS Map
 * @brief MikroBUS pin mapping of LP WiFi Click driver.
 */

/**
 * @addtogroup lpwifi_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LP WiFi Click to the selected MikroBUS.
 */
#define LPWIFI_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.wkp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lpwifi_map
/*! @} */ // lpwifi

/**
 * @brief LP WiFi Click context object.
 * @details Context object definition of LP WiFi Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t wkp;                              /**< Wake up pin. */
    digital_out_t cs;                               /**< SPI chip select programmable pin. */

    // Input pins

    digital_in_t  int_pin;                          /**< Interrupt pin. */

    // Modules

    uart_t uart;                                    /**< UART driver object. */

    // Buffers

    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} lpwifi_t;

/**
 * @brief LP WiFi Click configuration object.
 * @details Configuration object definition of LP WiFi Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t rx_pin;                              /**< RX pin. */
    pin_name_t tx_pin;                              /**< TX pin. */

    // Additional gpio pins

    pin_name_t wkp;                                 /**< Wake up pin. */
    pin_name_t int_pin;                             /**< Interrupt pin. */
    pin_name_t cs;                                  /**< SPI chip select programmable pin. */

    // Static variable

    uint32_t          baud_rate;                    /**< Clock speed. */
    bool              uart_blocking;                /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                     /**< Data bits. */
    uart_parity_t     parity_bit;                   /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                     /**< Stop bits. */

} lpwifi_cfg_t;

/**
 * @brief LP WiFi Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LPWIFI_OK = 0,
    LPWIFI_ERROR = -1

} lpwifi_return_value_t;

/*!
 * @addtogroup lpwifi LP WiFi Click Driver
 * @brief API for configuring and manipulating LP WiFi Click driver.
 * @{
 */

/**
 * @brief LP WiFi configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lpwifi_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lpwifi_cfg_setup ( lpwifi_cfg_t *cfg );

/**
 * @brief LP WiFi initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lpwifi_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lpwifi_init ( lpwifi_t *ctx, lpwifi_cfg_t *cfg );

/**
 * @brief LP WiFi default configuration function.
 * @details This function executes a default configuration of LP WiFi
 * click board.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void lpwifi_default_cfg ( lpwifi_t *ctx );

/**
 * @brief LP WiFi data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lpwifi_generic_write ( lpwifi_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LP WiFi data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lpwifi_generic_read ( lpwifi_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Device factory reset function.
 * @details This function factory resets the device.
 * @param ctx Click object.
 * See #lpwifi_t object definition for detailed explanation.
 * 
 * @return Nothing.
 */
void lpwifi_factory_reset_device ( lpwifi_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void lpwifi_send_cmd ( lpwifi_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 */
void lpwifi_send_cmd_with_parameter ( lpwifi_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Send command to check commands current value.
 * @details Send AT command (@b at_cmd_buf) and appends '?' to check commands value.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : AT command.
 *
 * @return Nothing.
 */
void lpwifi_send_cmd_check ( lpwifi_t *ctx, char *at_cmd_buf );

/**
 * @brief Connect to AP function.
 * @details This function connects to the desired AP.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[in] ssid      SSID of AP.
 * @param[in] password  AP password ( NULL - if the AP is OPEN ).
 *
 * @return Nothing.
 */
void lpwifi_connect_to_ap ( lpwifi_t *ctx, char *ssid, char *password );

/**
 * @brief Set WiFi mode function.
 * @details This function sets WiFi mode to STA or Soft-AP depending on the @b mode value.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[in] mode  0 - STA, 1 - Soft-AP.
 *
 * @return Nothing.
 */
void lpwifi_set_wifi_mode ( lpwifi_t *ctx, uint8_t mode );

/**
 * @brief Create TCP server function.
 * @details This function creates TCP server on the desired port.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[in] port      Local port: 1-65535.
 *
 * @return Nothing.
 */
void lpwifi_create_tcp_server ( lpwifi_t *ctx, uint16_t port );

/**
 * @brief Create UDP socket function.
 * @details This function creates UDP socket on the desired port.
 * @param[in] ctx : Click context object.
 * See #lpwifi_t object definition for detailed explanation.
 * @param[in] port      Local port: 1-65535.
 *
 * @return Nothing.
 */
void lpwifi_create_udp_socket ( lpwifi_t *ctx, uint16_t port );

#ifdef __cplusplus
}
#endif
#endif // LPWIFI_H

/*! @} */ // lpwifi

// ------------------------------------------------------------------------ END
