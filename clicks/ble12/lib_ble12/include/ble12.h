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
 * @file ble12.h
 * @brief This file contains API for BLE 12 Click Driver.
 */

#ifndef BLE12_H
#define BLE12_H

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
 * @addtogroup ble12 BLE 12 Click Driver
 * @brief API for configuring and manipulating BLE 12 Click driver.
 * @{
 */

/**
 * @defgroup ble12_cmd BLE 12 Device Settings
 * @brief Settings for registers of BLE 12 Click driver.
 */

/**
 * @addtogroup ble12_cmd
 * @{
 */

/**
 * @brief BLE 12 control commands.
 * @details Specified setting for control commands of BLE 12 Click driver.
 */
#define BLE12_CMD_AT                     "AT" 
#define BLE12_CMD_SW_RESET               "AT+RESET"
#define BLE12_CMD_GET_VERSION            "AT+VERSION?"
#define BLE12_CMD_GET_RSSI               "AT+RSSI?"
#define BLE12_CMD_SET_ADINTERVAL         "AT+ADINTERVAL="
#define BLE12_CMD_GET_ADINTERVAL         "AT+ADINTERVAL=?"
#define BLE12_CMD_SET_ADSTART            "AT+ADSTART="
#define BLE12_CMD_GET_ADSTART            "AT+ADSTART?"
#define BLE12_CMD_SET_ADVMANU            "AT+ADVMANU="
#define BLE12_CMD_GET_ADVMANU            "AT+ADVMANU?"
#define BLE12_CMD_SET_ADVRESP            "AT+ADVRESP="
#define BLE12_CMD_GET_ADVRESP            "AT+ADVRESP?"
#define BLE12_CMD_SET_SCANNER            "AT+SCANNER="
#define BLE12_CMD_GET_SCANNER            "AT+SCANNER?"
#define BLE12_CMD_SET_AUTOCON            "AT+AUTOCON="
#define BLE12_CMD_GET_AUTOCON            "AT+AUTOCON?"
#define BLE12_CMD_SET_DISCON             "AT+DISCON=1"
#define BLE12_CMD_SET_FILTERA            "AT+FILTERA="
#define BLE12_CMD_GET_FILTERA            "AT+FILTERA?"
#define BLE12_CMD_SET_FILTERR            "AT+FILTERR="
#define BLE12_CMD_GET_FILTERR            "AT+FILTERR?"
#define BLE12_CMD_SET_MANUAID            "AT+MANUAID=" 
#define BLE12_CMD_GET_MANUAID            "AT+MANUAID?"
#define BLE12_CMD_SET_MANURID            "AT+MANURID=" 
#define BLE12_CMD_GET_MANURID            "AT+MANURID?" 
#define BLE12_CMD_SET_DCDC               "AT+DCDC=" 
#define BLE12_CMD_GET_DCDC               "AT+DCDC?" 
#define BLE12_CMD_SET_SAVE               "AT+SAVE=1" 
#define BLE12_CMD_SET_STOP               "AT+STOP="
#define BLE12_CMD_SET_NAME               "AT+NAME="
#define BLE12_CMD_GET_UART               "AT+UART?" 
#define BLE12_CMD_SET_UART               "AT+UART=" 
#define BLE12_CMD_GET_ADDR               "AT+ADDR?" 
#define BLE12_CMD_GET_RX                 "AT+RX?" 
#define BLE12_CMD_SET_DEFAULT            "AT+DEFAULT" 
#define BLE12_CMD_GET_RFPW               "AT+RFPW?"
#define BLE12_CMD_SET_RFPW               "AT+RFPW=" 
#define BLE12_CMD_SET_GPIO               "AT+PIO="
#define BLE12_CMD_GET_GPIO               "AT+PIO?"
#define BLE12_CMD_SET_GPIO_IO            "AT+PIS="
#define BLE12_CMD_INIT_LED1              "AT+PIS=017,1"
#define BLE12_CMD_INIT_LED2              "AT+PIS=019,1"

/**
 * @brief BLE 12 respond event.
 * @details Specified setting for respond event of BLE 12 Click driver.
 */
#define BLE12_EVT_CONNECTED              "CONNECTED"
#define BLE12_EVT_DISCONNECTED           "DISCONNECTED"
#define BLE12_EVT_SCAN_TIMEOUT           "SCAN TIMEOUT"

/**
 * @brief BLE 12 control led.
 * @details Specified setting for control led of BLE 12 Click driver.
 */
#define BLE12_LED_YELLOW                 0x00
#define BLE12_LED_RED                    0x01
#define BLE12_LED_ON                     0x00
#define BLE12_LED_OFF                    0x01
#define BLE12_OP_MODE_CMD                0x00
#define BLE12_OP_MODE_DATA               0x01
#define BLE12_SELECT_LED_YELLOW          "017,"
#define BLE12_SELECT_LED_RED             "019,"
#define BLE12_SET_LED_STATE_ON           "0"
#define BLE12_SET_LED_STATE_OFF          "1"

/**
 * @brief BLE 12 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // ble12_cmd

/**
 * @defgroup ble12_map BLE 12 MikroBUS Map
 * @brief MikroBUS pin mapping of BLE 12 Click driver.
 */

/**
 * @addtogroup ble12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLE 12 Click to the selected MikroBUS.
 */
#define BLE12_MAP_MIKROBUS( cfg, mikrobus )          \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.wkp = MIKROBUS( mikrobus, MIKROBUS_CS );     \
    cfg.cmd = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.req = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ble12_map
/*! @} */ // ble12

/**
 * @brief BLE 12 Click context object.
 * @details Context object definition of BLE 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;     /**< Reset pin. */
    digital_out_t wkp;     /**< Wake up pin. */
    digital_out_t cmd;     /**< Mode selection pin. */

    // Input pins
    digital_in_t req;      /**< Request pin. */

    // Modules
    uart_t uart;           /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} ble12_t;

/**
 * @brief BLE 12 Click configuration object.
 * @details Configuration object definition of BLE 12 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;     /**< RX pin. */
    pin_name_t tx_pin;     /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;        /**< Reset pin. */
    pin_name_t wkp;        /**< Wake up pin. */
    pin_name_t cmd;        /**< Mode selection pin. */
    pin_name_t req;        /**< Request pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} ble12_cfg_t;

/**
 * @brief BLE 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BLE12_OK = 0,
    BLE12_ERROR = -1

} ble12_return_value_t;

/*!
 * @addtogroup ble12 BLE 12 Click Driver
 * @brief API for configuring and manipulating BLE 12 Click driver.
 * @{
 */

/**
 * @brief BLE 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ble12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ble12_cfg_setup ( ble12_cfg_t *cfg );

/**
 * @brief BLE 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ble12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_init ( ble12_t *ctx, ble12_cfg_t *cfg );

/**
 * @brief BLE 12 default configuration function.
 * @details This function executes a default configuration of BLE 12
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ble12_default_cfg ( ble12_t *ctx );

/**
 * @brief BLE 12 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_generic_write ( ble12_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief BLE 12 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_generic_read ( ble12_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief BLE 12 wake up the device function.
 * @details This function performs the wake-up UART interface 
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @return @li @c  0 - Success.
 *
 * @note None.
 */
err_t ble12_wake_up_device ( ble12_t *ctx );

/**
 * @brief BLE 12 sends the command function.
 * @details This function sends the desired command by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_send_cmd ( ble12_t *ctx, char *cmd );

/**
 * @brief BLE 12 send data function.
 * @details This function send the desired data to the paired device
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @param[in] tx_data : Data for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_send_data ( ble12_t *ctx, char *tx_data );

/**
 * @brief BLE 12 LED initialization function.
 * @details This function initialization for LED control
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_init_led ( ble12_t *ctx );

/**
 * @brief BLE 12 set LED state function.
 * @details This function controls the LEDs 
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @param[in] led : select LED
 *         @li @c  0 ( BLE12_LED_YELLOW ) - Yellow led,
 *         @li @c  1 ( BLE12_LED_RED )    - Red led.
 * @param[in] state : LED state
 *         @li @c  0 ( BLE12_LED_ON )  - Turn on the LED,
 *         @li @c  1 ( BLE12_LED_OFF ) - Turn off the LED.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_set_led_state ( ble12_t *ctx, uint8_t led, uint8_t state );

/**
 * @brief BLE 12 reset function.
 * @details This function software reset the device
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_reset ( ble12_t *ctx );

/**
 * @brief BLE 12 get version function.
 * @details This function get module version
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_get_version ( ble12_t *ctx );

/**
 * @brief BLE 12 set device name function.
 * @details This function sets the device name
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @param[in] device_name : Device name.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_set_device_name ( ble12_t *ctx, uint8_t *device_name );

/**
 * @brief BLE 12 save config function.
 * @details This function performs the configuration save procedure
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_save_config ( ble12_t *ctx );

/**
 * @brief BLE 12 set adv interval function.
 * @details This function sets the advertising interval
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @param[in] adv_interval : Advertising interval time ( ms ).
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This command trigger readvertise.
 */
err_t ble12_set_adv_interval ( ble12_t *ctx, uint8_t *adv_interval );

/**
 * @brief BLE 12 disconnect function.
 * @details This function disconnects all paired devices
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_disconnect ( ble12_t *ctx  );

/**
 * @brief BLE 12 set default function.
 * @details This function sets the default module configuration
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_set_default ( ble12_t *ctx );

/**
 * @brief BLE 12 set operating mode function.
 * @details This function sets the operating mode
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @param[in] op_mode : Operating mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_set_op_mode ( ble12_t *ctx, uint8_t op_mode );

/**
 * @brief BLE 12 event start-up function.
 * @details This function event start-up for the control LED
 * by using UART serial interface
 * of the BM832A Bluetooth 5 Module on the BLE 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #ble12_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble12_event_startup ( ble12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BLE12_H

/*! @} */ // ble12

// ------------------------------------------------------------------------ END
