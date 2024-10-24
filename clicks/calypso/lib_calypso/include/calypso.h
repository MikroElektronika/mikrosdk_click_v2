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
 * @file calypso.h
 * @brief This file contains API for Calypso Click Driver.
 */

#ifndef CALYPSO_H
#define CALYPSO_H

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
#include "drv_i2c_master.h"
#include "drv_uart.h"

/*!
 * @addtogroup calypso Calypso Click Driver
 * @brief API for configuring and manipulating Calypso Click driver.
 * @{
 */

/**
 * @defgroup calypso_cmd Calypso Device Settings
 * @brief Settings for registers of Calypso Click driver.
 */

/**
 * @addtogroup calypso_cmd
 * @{
 */

/**
 * @brief Calypso control commands.
 * @details Specified setting for control commands of Calypso Click driver.
 */
#define CALYPSO_CMD_AT                  "AT"
#define CALYPSO_CMD_AT_START            "AT+start"
#define CALYPSO_CMD_AT_TEST             "AT+test"
#define CALYPSO_CMD_AT_REBOOT           "AT+reboot"
#define CALYPSO_CMD_AT_GET              "AT+get"
#define CALYPSO_CMD_AT_SET              "AT+set"
#define CALYPSO_CMD_AT_WLAN_SET_MODE    "AT+wlanSetMode"
#define CALYPSO_CMD_AT_WLAN_SCAN        "AT+wlanScan"
#define CALYPSO_CMD_AT_WLAN_CONNECT     "AT+wlanConnect"
#define CALYPSO_CMD_AT_WLAN_DISCONNECT  "AT+wlanDisconnect"
#define CALYPSO_CMD_AT_WLAN_PROFILE_ADD "AT+wlanProfileAdd"
#define CALYPSO_CMD_AT_WLAN_PROFILE_GET "AT+wlanProfileGet"
#define CALYPSO_CMD_AT_WLAN_PROFILE_DEL "AT+wlanProfileDel"
#define CALYPSO_CMD_AT_WLAN_SET         "AT+wlanSet"
#define CALYPSO_CMD_AT_WLAN_GET         "AT+wlanGet"
#define CALYPSO_CMD_AT_WLAN_POLICY_SET  "AT+wlanPolicySet"
#define CALYPSO_CMD_AT_WLAN_POLICY_GET  "AT+wlanPolicyGet"
#define CALYPSO_CMD_AT_NET_CFG_SET      "AT+netCfgSet"
#define CALYPSO_CMD_AT_NET_CFG_GET      "AT+netCfgGet"
#define CALYPSO_CMD_AT_SOCKET           "AT+socket"
#define CALYPSO_CMD_AT_CLOSE            "AT+close"
#define CALYPSO_CMD_AT_BIND             "AT+bind"
#define CALYPSO_CMD_AT_LISTEN           "AT+listen"
#define CALYPSO_CMD_AT_CONNECT          "AT+connect"
#define CALYPSO_CMD_AT_ACCEPT           "AT+accept"
#define CALYPSO_CMD_AT_SELECT           "AT+select"
#define CALYPSO_CMD_AT_SET_SOCK_OPT     "AT+setSockOpt"
#define CALYPSO_CMD_AT_GET_SOCK_OPT     "AT+getSockOpt"
#define CALYPSO_CMD_AT_RECV             "AT+recv"
#define CALYPSO_CMD_AT_RECV_FROM        "AT+recvFrom"
#define CALYPSO_CMD_AT_SEND             "AT+send"
#define CALYPSO_CMD_AT_SEND_TO          "AT+sendTo"
#define CALYPSO_CMD_AT_GPIO_GET         "AT+gpioGet"
#define CALYPSO_CMD_AT_GPIO_SET         "AT+gpioSet"

/**
 * @brief Calypso response codes.
 * @details Specified response codes of Calypso Click driver.
 */
#define CALYPSO_RSP_OK                  "OK"
#define CALYPSO_RSP_ERROR               "ERROR"
#define CALYPSO_RSP_READY               "+eventstartup"
#define CALYPSO_RSP_CONNECTED           "+eventwlan:connect"

/**
 * @brief Calypso APP mode settings.
 * @details Specified APP mode settings of Calypso Click driver.
 */
#define CALYPSO_APP_MODE_AT_COMMAND     0x00
#define CALYPSO_APP_MODE_OTA            0x01
#define CALYPSO_APP_MODE_PROVISIONIG    0x02
#define CALYPSO_APP_MODE_TRANSPARENT    0x03

/**
 * @brief Calypso Port expander register address settings.
 * @details Specified Port expander register address settings of Calypso Click driver.
 */
#define CALYPSO_REG_INPUT_PORT          0x00
#define CALYPSO_REG_OUTPUT_PORT         0x01
#define CALYPSO_REG_POLARITY_INVERSION  0x02
#define CALYPSO_REG_CONFIGURATION       0x03

/**
 * @brief Calypso driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define CALYPSO_TX_DRV_BUFFER_SIZE      256
#define CALYPSO_RX_DRV_BUFFER_SIZE      256

/**
 * @brief Calypso driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define CALYPSO_PIN_NONE_MASK           0x00
#define CALYPSO_PIN_ALL_MASK            0x0F
#define CALYPSO_PIN_AP0_MASK            0x01
#define CALYPSO_PIN_AP1_MASK            0x02
#define CALYPSO_PIN_BOOT_MASK           0x04
#define CALYPSO_PIN_RM2_MASK            0x08

/**
 * @brief Calypso pin states.
 * @details Specified pin states of Calypso Click driver.
 */
#define CALYPSO_PIN_STATE_HIGH          0x01
#define CALYPSO_PIN_STATE_LOW           0x00

/**
 * @brief Calypso device address setting.
 * @details Specified setting for device slave address selection of
 * Calypso Click driver.
 */
#define CALYPSO_DEVICE_ADDRESS          0x41

/*! @} */ // calypso_cmd

/**
 * @defgroup calypso_map Calypso MikroBUS Map
 * @brief MikroBUS pin mapping of Calypso Click driver.
 */

/**
 * @addtogroup calypso_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Calypso Click to the selected MikroBUS.
 */
#define CALYPSO_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rm0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // calypso_map
/*! @} */ // calypso

/**
 * @brief Calypso Click context object.
 * @details Context object definition of Calypso Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */
    digital_out_t cts;          /**< Clear to send. */
    digital_out_t wup;          /**< Wake-up pin. */

    // Input pins
    digital_in_t rm0;           /**< Remote GPIO pin. */
    digital_in_t rts;           /**< Ready to send pin. */

    // Modules
    uart_t uart;                /**< UART driver object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ CALYPSO_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ CALYPSO_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} calypso_t;

/**
 * @brief Calypso Click configuration object.
 * @details Configuration object definition of Calypso Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t rm0;                     /**< Remote GPIO pin. */
    pin_name_t rst;                     /**< Reset pin. */
    pin_name_t cts;                     /**< Clear to send. */
    pin_name_t wup;                     /**< Wake-up pin. */
    pin_name_t rts;                     /**< Ready to send pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */
    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

} calypso_cfg_t;

/**
 * @brief Calypso Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CALYPSO_OK = 0,
    CALYPSO_ERROR = -1,
    CALYPSO_ERROR_TIMEOUT = -2,
    CALYPSO_ERROR_CMD = -3,
    CALYPSO_ERROR_UNKNOWN = -4

} calypso_return_value_t;

/*!
 * @addtogroup calypso Calypso Click Driver
 * @brief API for configuring and manipulating Calypso Click driver.
 * @{
 */

/**
 * @brief Calypso configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #calypso_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void calypso_cfg_setup ( calypso_cfg_t *cfg );

/**
 * @brief Calypso initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #calypso_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t calypso_init ( calypso_t *ctx, calypso_cfg_t *cfg );

/**
 * @brief Calypso default configuration function.
 * @details This function executes a default configuration of CALYPSO
 * click board.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t calypso_default_cfg ( calypso_t *ctx );

/**
 * @brief Calypso data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t calypso_generic_write ( calypso_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Calypso data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t calypso_generic_read ( calypso_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Calypso port expander data writing function.
 * @details This function writes a data byte into the selected register.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] reg : Register to be written.
 * @param[in] data_in : Data for sending.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t calypso_port_expander_write ( calypso_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Calypso port expander data reading function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] reg : Register to be read.
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t calypso_port_expander_read ( calypso_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Calypso set port expander pin function.
 * @details This function is used to set port expander pin state.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] set_mask : Pin set HIGH.
 * @param[in] clr_mask : Pin set LOW.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t calypso_set_pins ( calypso_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief Calypso set app mode function.
 * @details This function is used to set selected APP mode of CALYPSO
 * click board.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] mode_sel : Selected APP mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t calypso_set_app_mode ( calypso_t *ctx, uint8_t mode_sel );

/**
 * @brief Calypso set RST pin function.
 * @details This function is used to set RST pin state.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] pin_state : State of the RST pin.
 * @return Nothing.
 * @note None.
 */
void calypso_set_rst_pin ( calypso_t *ctx, uint8_t pin_state );

/**
 * @brief Calypso set CTS pin function.
 * @details This function is used to set CTS pin state.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] pin_state : State of the CTS pin.
 * @return Nothing.
 * @note None.
 */
void calypso_set_cts_pin ( calypso_t *ctx, uint8_t pin_state );

/**
 * @brief Calypso set WUP pin function.
 * @details This function is used to set WUP pin state.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] pin_state : State of the WUP pin.
 * @return Nothing.
 * @note None.
 */
void calypso_set_wup_pin ( calypso_t *ctx, uint8_t pin_state );

/**
 * @brief Calypso get RTS pin state function.
 * @details This function is used to get RTS pin state.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @return State of the RTS pin.
 * @note None.
 */
uint8_t calypso_get_rts_pin ( calypso_t *ctx );

/**
 * @brief Calypso get RM0 pin state function.
 * @details This function is used to get RM0 pin state.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @return State of the RM0 pin.
 * @note None.
 */
uint8_t calypso_get_rm0_pin ( calypso_t *ctx );

/**
 * @brief Calypso HW reset function.
 * @details This function is used to perform HW reset.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void calypso_hw_reset ( calypso_t *ctx );

/**
 * @brief Calypso send command function.
 * @details This function is used to send a desired command.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @return Nothing.
 * @note None.
 */
void calypso_send_cmd ( calypso_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Calypso send command with parameter function.
 * @details This function sends a desired command with the parameter.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @param[in] param_buf : Parameters string.
 * @return Nothing.
 * @note None.
 */
void calypso_send_cmd_with_par ( calypso_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Calypso send command check function.
 * @details This function sends a desired command with the question mark for checking parameters.
 * @param[in] ctx : Click context object.
 * See #calypso_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @return Nothing.
 * @note None.
 */
void calypso_send_cmd_check ( calypso_t *ctx, uint8_t *at_cmd_buf );

#ifdef __cplusplus
}
#endif
#endif // CALYPSO_H

/*! @} */ // calypso

// ------------------------------------------------------------------------ END
