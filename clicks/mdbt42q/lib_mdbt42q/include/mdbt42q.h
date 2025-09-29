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
 * @file mdbt42q.h
 * @brief This file contains API for MDBT42Q Click Driver.
 */

#ifndef MDBT42Q_H
#define MDBT42Q_H

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
 * @addtogroup mdbt42q MDBT42Q Click Driver
 * @brief API for configuring and manipulating MDBT42Q Click driver.
 * @{
 */

/**
 * @defgroup mdbt42q_cmd MDBT42Q Device Settings
 * @brief Settings for registers of MDBT42Q Click driver.
 */

/**
 * @addtogroup mdbt42q_cmd
 * @{
 */

/**
 * @brief MDBT42Q control commands.
 * @details Specified setting for control commands of MDBT42Q Click driver.
 */
#define MDBT42Q_CMD_SET_PARAM_DEVICE_NAME       "AT+NAME"
#define MDBT42Q_CMD_SET_BAUDRATE_9600           "AT+BAUDRATE9600"
#define MDBT42Q_CMD_SET_BAUDRATE_19200          "AT+BAUDRATE19200"
#define MDBT42Q_CMD_SET_BAUDRATE_38400          "AT+BAUDRATE38400"
#define MDBT42Q_CMD_SET_BAUDRATE_57600          "AT+BAUDRATE57600"
#define MDBT42Q_CMD_SET_BAUDRATE_115200         "AT+BAUDRATE115200"
#define MDBT42Q_CMD_SET_BAUDRATE_230400         "AT+BAUDRATE230400"
#define MDBT42Q_CMD_SET_BAUDRATE_460800         "AT+BAUDRATE460800"
#define MDBT42Q_CMD_ENABLE_FLOW_CONTROL         "AT+FLOWCONTROLEN"
#define MDBT42Q_CMD_DISABLE_FLOW_CONTROL        "AT+FLOWCONTROLDIS"
#define MDBT42Q_CMD_SET_TX_POWER_4DBM           "AT+TXPOWER4DBM"
#define MDBT42Q_CMD_SET_TX_POWER_0DBM           "AT+TXPOWER0DBM"
#define MDBT42Q_CMD_SET_TX_POWER_MINUS_4DBM     "AT+TXPOWER-4DBM"
#define MDBT42Q_CMD_SET_TX_POWER_MINUS_8DBM     "AT+TXPOWER-8DBM"
#define MDBT42Q_CMD_SET_TX_POWER_MINUS_20DBM    "AT+TXPOWER-20DBM"
#define MDBT42Q_CMD_USE_INTERNAL_XTAL           "AT+XTALINTERNAL"
#define MDBT42Q_CMD_USE_EXTERNAL_XTAL           "AT+XTALEXTERNAL"
#define MDBT42Q_CMD_SET_CONNECT_IND_LOW         "AT+CONNECTINDICATORLOW"
#define MDBT42Q_CMD_SET_CONNECT_IND_HIGH        "AT+CONNECTINDICATORHIGH"
#define MDBT42Q_CMD_SET_PHYMODE_1MBPS           "AT+PHYMODE1MBPS"
#define MDBT42Q_CMD_SET_PHYMODE_2MBPS           "AT+PHYMODE2MBPS"
#define MDBT42Q_CMD_SET_WAKEUP_LOW              "AT+WAKEUPLOW"
#define MDBT42Q_CMD_SET_WAKEUP_HIGH             "AT+WAKEUPHIGH"
#define MDBT42Q_CMD_SET_PARAM_ADV_TIME          "AT+ADVTIME"
#define MDBT42Q_CMD_DISABLE_DCDC                "AT+DCDCDIS"
#define MDBT42Q_CMD_ENABLE_DCDC                 "AT+DCDCEN"
#define MDBT42Q_CMD_SET_CONN_INTERVAL_MODE_0    "AT+CONNECTINTERVALMODE0"
#define MDBT42Q_CMD_SET_CONN_INTERVAL_MODE_1    "AT+CONNECTINTERVALMODE1"
#define MDBT42Q_CMD_SET_CONN_INTERVAL_MODE_2    "AT+CONNECTINTERVALMODE2"
#define MDBT42Q_CMD_SET_PARAM_CONN_INTERVAL_T   "AT+CONNECTINTERVALTIME"
#define MDBT42Q_CMD_SET_PARAM_ADV_LED_PATTERN   "AT+ADVPATTERN"
#define MDBT42Q_CMD_SET_PARAM_CONN_LED_PATTERN  "AT+CONNECTPATTERN"
#define MDBT42Q_CMD_SET_PARAM_SERIAL_NUMBER     "AT+SERIALNO"
#define MDBT42Q_CMD_DISABLE_RESPONSE            "AT+RESPONSEDIS"
#define MDBT42Q_CMD_ENABLE_RESPONSE             "AT+RESPONSEEN"
#define MDBT42Q_CMD_SET_PARAM_MAC_ADDRESS       "AT+MACADDR"
#define MDBT42Q_CMD_RESET                       "AT+RESET"
#define MDBT42Q_CMD_ADV_START                   "AT+ADVSTART"
#define MDBT42Q_CMD_ADV_STOP                    "AT+ADVSTOP"
#define MDBT42Q_CMD_ENTER_SLEEP                 "AT+SLEEP"
#define MDBT42Q_CMD_DISCONNECT                  "AT+DISCONNECT"
#define MDBT42Q_CMD_RESTORE_DEFAULT             "AT+DEFAULT"
#define MDBT42Q_CMD_SET_GPIO_12_HIGH            "AT+SETGPIO12HIGH"
#define MDBT42Q_CMD_SET_GPIO_13_HIGH            "AT+SETGPIO13HIGH"
#define MDBT42Q_CMD_SET_GPIO_14_HIGH            "AT+SETGPIO14HIGH"
#define MDBT42Q_CMD_SET_GPIO_15_HIGH            "AT+SETGPIO15HIGH"
#define MDBT42Q_CMD_SET_GPIO_16_HIGH            "AT+SETGPIO16HIGH"
#define MDBT42Q_CMD_SET_GPIO_17_HIGH            "AT+SETGPIO17HIGH"
#define MDBT42Q_CMD_SET_GPIO_18_HIGH            "AT+SETGPIO18HIGH"
#define MDBT42Q_CMD_SET_GPIO_19_HIGH            "AT+SETGPIO19HIGH"
#define MDBT42Q_CMD_SET_GPIO_12_LOW             "AT+SETGPIO12LOW"
#define MDBT42Q_CMD_SET_GPIO_13_LOW             "AT+SETGPIO13LOW"
#define MDBT42Q_CMD_SET_GPIO_14_LOW             "AT+SETGPIO14LOW"
#define MDBT42Q_CMD_SET_GPIO_15_LOW             "AT+SETGPIO15LOW"
#define MDBT42Q_CMD_SET_GPIO_16_LOW             "AT+SETGPIO16LOW"
#define MDBT42Q_CMD_SET_GPIO_17_LOW             "AT+SETGPIO17LOW"
#define MDBT42Q_CMD_SET_GPIO_18_LOW             "AT+SETGPIO18LOW"
#define MDBT42Q_CMD_SET_GPIO_19_LOW             "AT+SETGPIO19LOW"
#define MDBT42Q_CMD_SET_GPIO_12_OFF             "AT+SETGPIO12OFF"
#define MDBT42Q_CMD_SET_GPIO_13_OFF             "AT+SETGPIO13OFF"
#define MDBT42Q_CMD_SET_GPIO_14_OFF             "AT+SETGPIO14OFF"
#define MDBT42Q_CMD_SET_GPIO_15_OFF             "AT+SETGPIO15OFF"
#define MDBT42Q_CMD_SET_GPIO_16_OFF             "AT+SETGPIO16OFF"
#define MDBT42Q_CMD_SET_GPIO_17_OFF             "AT+SETGPIO17OFF"
#define MDBT42Q_CMD_SET_GPIO_18_OFF             "AT+SETGPIO18OFF"
#define MDBT42Q_CMD_SET_GPIO_19_OFF             "AT+SETGPIO19OFF"
#define MDBT42Q_CMD_GET_DEVICE_NAME             "AT?NAME"
#define MDBT42Q_CMD_GET_VERSION                 "AT?VERSION"
#define MDBT42Q_CMD_GET_MAC_ADDRESS             "AT?MACADDR"
#define MDBT42Q_CMD_GET_BAUD_RATE               "AT?BAUDRATE"
#define MDBT42Q_CMD_GET_FLOW_CONTROL            "AT?FLOWCONTROL"
#define MDBT42Q_CMD_GET_TX_POWER                "AT?TXPOWER"
#define MDBT42Q_CMD_GET_OSCILLATOR              "AT?XTAL"
#define MDBT42Q_CMD_GET_CONNECT_INDICATOR       "AT?CONNECTINDICATOR"
#define MDBT42Q_CMD_GET_PHY_MODE                "AT?PHYMODE"
#define MDBT42Q_CMD_GET_WAKEUP_MODE             "AT?WAKEUP"
#define MDBT42Q_CMD_GET_ADV_TIME                "AT?ADVTIME"
#define MDBT42Q_CMD_GET_DCDC_STATUS             "AT?DCDC"
#define MDBT42Q_CMD_GET_CONN_INTERVAL_MODE      "AT?CONNECTINTERVALMODE"
#define MDBT42Q_CMD_GET_ADV_LED_PATTERN         "AT?ADVPATTERN"
#define MDBT42Q_CMD_GET_CONN_LED_PATTERN        "AT?CONNECTPATTERN"
#define MDBT42Q_CMD_GET_SERIAL_NUMBER           "AT?SERIALNO"
#define MDBT42Q_CMD_GET_ADC_VALUE               "AT?ADCVALUE"
#define MDBT42Q_CMD_GET_RESPONSE_MODE           "AT?RESPONSE"
#define MDBT42Q_CMD_GET_ALL_PARAMETERS          "AT?ALLPARAMETERS"
#define MDBT42Q_CMD_GET_CONN_INTERVAL_TIME      "AT?CONNECTINTERVALTIME"

/**
 * @brief MDBT42Q driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define MDBT42Q_TX_DRV_BUFFER_SIZE              200
#define MDBT42Q_RX_DRV_BUFFER_SIZE              600

/*! @} */ // mdbt42q_cmd

/**
 * @defgroup mdbt42q_map MDBT42Q MikroBUS Map
 * @brief MikroBUS pin mapping of MDBT42Q Click driver.
 */

/**
 * @addtogroup mdbt42q_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MDBT42Q Click to the selected MikroBUS.
 */
#define MDBT42Q_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.ind = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pd = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // mdbt42q_map
/*! @} */ // mdbt42q

/**
 * @brief MDBT42Q Click context object.
 * @details Context object definition of MDBT42Q Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< HW reset pin (active low). */
    digital_out_t cts;              /**< UART clear to send pin (active low). */
    digital_out_t pd;               /**< UART disable pin (active high). */

    // Input pins
    digital_in_t ind;               /**< BT connection active indicator pin (active low). */
    digital_in_t rts;               /**< UART request to send pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ MDBT42Q_RX_DRV_BUFFER_SIZE ];   /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ MDBT42Q_TX_DRV_BUFFER_SIZE ];   /**< TX Buffer size. */
    uint8_t cmd_buffer[ MDBT42Q_TX_DRV_BUFFER_SIZE ];       /**< Command buffer. */

} mdbt42q_t;

/**
 * @brief MDBT42Q Click configuration object.
 * @details Configuration object definition of MDBT42Q Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t ind;                 /**< BT connection active indicator pin (active low). */
    pin_name_t rst;                 /**< HW reset pin (active low). */
    pin_name_t cts;                 /**< UART clear to send pin (active low). */
    pin_name_t pd;                  /**< UART disable pin (active high). */
    pin_name_t rts;                 /**< UART request to send pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} mdbt42q_cfg_t;

/**
 * @brief MDBT42Q Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MDBT42Q_OK = 0,
    MDBT42Q_ERROR = -1,
    MDBT42Q_ERROR_TIMEOUT = -2

} mdbt42q_return_value_t;

/*!
 * @addtogroup mdbt42q MDBT42Q Click Driver
 * @brief API for configuring and manipulating MDBT42Q Click driver.
 * @{
 */

/**
 * @brief MDBT42Q configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mdbt42q_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mdbt42q_cfg_setup ( mdbt42q_cfg_t *cfg );

/**
 * @brief MDBT42Q initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mdbt42q_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mdbt42q_init ( mdbt42q_t *ctx, mdbt42q_cfg_t *cfg );

/**
 * @brief MDBT42Q data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mdbt42q_generic_write ( mdbt42q_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief MDBT42Q data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mdbt42q_generic_read ( mdbt42q_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief MDBT42Q set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mdbt42q_set_rst_pin ( mdbt42q_t *ctx, uint8_t state );

/**
 * @brief MDBT42Q set PD pin function.
 * @details This function sets the UART Power down pin logic state.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mdbt42q_set_pd_pin ( mdbt42q_t *ctx, uint8_t state );

/**
 * @brief MDBT42Q set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mdbt42q_set_cts_pin ( mdbt42q_t *ctx, uint8_t state );

/**
 * @brief MDBT42Q get RTS pin function.
 * @details This function returns the ready to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mdbt42q_get_rts_pin ( mdbt42q_t *ctx );

/**
 * @brief MDBT42Q get IND pin function.
 * @details This function returns the BT connection active indicator (IND) pin logic state.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mdbt42q_get_ind_pin ( mdbt42q_t *ctx );

/**
 * @brief MDBT42Q reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void mdbt42q_reset_device ( mdbt42q_t *ctx );

/**
 * @brief MDBT42Q cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see MDBT42Q_CMD_x definitions.
 * @return None.
 * @note None.
 */
void mdbt42q_cmd_run ( mdbt42q_t *ctx, uint8_t *cmd );

/**
 * @brief MDBT42Q cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see MDBT42Q_CMD_SET_PARAM_x definitions.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void mdbt42q_cmd_set ( mdbt42q_t *ctx, uint8_t *cmd, uint8_t *value );

#ifdef __cplusplus
}
#endif
#endif // MDBT42Q_H

/*! @} */ // mdbt42q

// ------------------------------------------------------------------------ END
