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
 * @file g2c.h
 * @brief This file contains API for G2C Click Driver.
 */

#ifndef G2C_H
#define G2C_H

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
 * @addtogroup g2c G2C Click Driver
 * @brief API for configuring and manipulating G2C Click driver.
 * @{
 */

/**
 * @defgroup g2c_cmd G2C Device Settings
 * @brief Settings for registers of G2C Click driver.
 */

/**
 * @addtogroup g2c_cmd
 * @{
 */

/**
 * @brief G2C control commands.
 * @details Specified setting for control commands of G2C Click driver.
 */
#define G2C_CMD_AT                  "AT"        // Communication test
#define G2C_CMD_GMR                 "AT+GMR"    // Firmware version
#define G2C_CMD_ATE1                "ATE1"      // Enable echo
#define G2C_CMD_ATE0                "ATE0"      // Disable echo
#define G2C_CMD_RST                 "AT+RST"    // Reset device
#define G2C_CMD_CRST                "AT+CRST"   // Connector module reset
#define G2C_CMD_CEN                 "AT+CEN"    // Enable connector module
#define G2C_CMD_GPEN                "AT+GPEN"   // Enable GPIO outputs
#define G2C_CMD_W                   "AT+W"      // Store configuration
#define G2C_CMD_R                   "AT+R"      // Restore configuration
#define G2C_CMD_NWP                 "AT+NWP"    // Network parameters
#define G2C_CMD_NWCR                "AT+NWCR"   // Network credentials
#define G2C_CMD_NWC                 "AT+NWC"    // Connect to network
#define G2C_CMD_BRCR                "AT+BRCR"   // Broker credentials
#define G2C_CMD_BRC                 "AT+BRC"    // Connect to broker
#define G2C_CMD_ASTA                "AT+ASTA"   // Actuator status
#define G2C_CMD_DSET                "AT+DSET"   // Data set
#define G2C_CMD_PUB                 "AT+PUB"    // Publish data

/**
 * @brief G2C device response for AT commands.
 * @details Device response after commands.
 */
#define G2C_RSP_OK                  "OK"
#define G2C_RSP_ERROR               "ERROR"
#define G2C_RSP_ERR                 "+ERR"
#define G2C_RSP_ACT                 "+ACT"

/**
 * @brief G2C driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define G2C_TX_DRV_BUFFER_SIZE      300
#define G2C_RX_DRV_BUFFER_SIZE      300

/*! @} */ // g2c_cmd

/**
 * @defgroup g2c_map G2C MikroBUS Map
 * @brief MikroBUS pin mapping of G2C Click driver.
 */

/**
 * @addtogroup g2c_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of G2C Click to the selected MikroBUS.
 */
#define G2C_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // g2c_map
/*! @} */ // g2c

/**
 * @brief G2C Click context object.
 * @details Context object definition of G2C Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset pin. */
    digital_out_t cts;      /**< Clear to send pin. */

    // Input pins
    digital_in_t gp0;       /**< General purpose 0 pin. */
    digital_in_t gp1;       /**< General purpose 1 pin. */
    digital_in_t rts;       /**< Request to send pin. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ G2C_RX_DRV_BUFFER_SIZE ]; /**< Buffer size. */
    uint8_t uart_tx_buffer[ G2C_TX_DRV_BUFFER_SIZE ]; /**< Buffer size. */

} g2c_t;

/**
 * @brief G2C Click configuration object.
 * @details Configuration object definition of G2C Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t gp0;         /**< General purpose 0 pin. */
    pin_name_t rst;         /**< Reset pin. */
    pin_name_t cts;         /**< Clear to send pin. */
    pin_name_t gp1;         /**< General purpose 1 pin. */
    pin_name_t rts;         /**< Request to send pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} g2c_cfg_t;

/**
 * @brief G2C Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    G2C_OK = 0,
    G2C_ERROR = -1,
    G2C_ERROR_TIMEOUT = -2,
    G2C_ERROR_CMD = -3,
    G2C_ERROR_UNKNOWN = -4

} g2c_return_value_t;

/*!
 * @addtogroup g2c G2C Click Driver
 * @brief API for configuring and manipulating G2C Click driver.
 * @{
 */

/**
 * @brief G2C configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #g2c_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void g2c_cfg_setup ( g2c_cfg_t *cfg );

/**
 * @brief G2C initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #g2c_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t g2c_init ( g2c_t *ctx, g2c_cfg_t *cfg );

/**
 * @brief G2C data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t g2c_generic_write ( g2c_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief G2C data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t g2c_generic_read ( g2c_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief G2C set cts pin function.
 * @details This function sets the Clear to Send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void g2c_set_cts_pin ( g2c_t *ctx, uint8_t state );

/**
 * @brief G2C set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void g2c_set_rst_pin ( g2c_t *ctx, uint8_t state );

/**
 * @brief G2C get gp0 pin function.
 * @details This function returns the GPIO 0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t g2c_get_gp0_pin ( g2c_t *ctx );

/**
 * @brief G2C get gp1 pin function.
 * @details This function returns the GPIO 1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t g2c_get_gp1_pin ( g2c_t *ctx );

/**
 * @brief G2C get rts pin function.
 * @details This function returns the Request to Send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t g2c_get_rts_pin ( g2c_t *ctx );

/**
 * @brief G2C reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void g2c_reset_device ( g2c_t *ctx );

/**
 * @brief G2C send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void g2c_send_cmd ( g2c_t *ctx, uint8_t *cmd );

/**
 * @brief G2C send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void g2c_send_cmd_with_par ( g2c_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief G2C check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void g2c_send_cmd_check ( g2c_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief G2C check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void g2c_send_cmd_par_check ( g2c_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief G2C set network credentials.
 * @details This function sets the WiFi network credentials.
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] wifi_ssid : WiFi SSID.
 * @param[in] wifi_pass : WiFi Password.
 * @return Nothing.
 * @note None.
 */
void g2c_set_net_creds ( g2c_t *ctx, uint8_t *wifi_ssid, uint8_t *wifi_pass );

/**
 * @brief G2C set broker credentials.
 * @details This function sets the broker credentials (device key and password).
 * @param[in] ctx : Click context object.
 * See #g2c_t object definition for detailed explanation.
 * @param[in] dev_key : Device key.
 * @param[in] password : Device password.
 * @return Nothing.
 * @note None.
 */
void g2c_set_broker_creds ( g2c_t *ctx, uint8_t *dev_key, uint8_t *password );

#ifdef __cplusplus
}
#endif
#endif // G2C_H

/*! @} */ // g2c

// ------------------------------------------------------------------------ END
