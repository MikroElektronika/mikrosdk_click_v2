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
 * @file bluetooth2.h
 * @brief This file contains API for Bluetooth2 Click Driver.
 */

#ifndef BLUETOOTH2_H
#define BLUETOOTH2_H

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
#include "drv_analog_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup bluetooth2 Bluetooth2 Click Driver
 * @brief API for configuring and manipulating Bluetooth2 Click driver.
 * @{
 */

/**
 * @defgroup bluetooth2_set Bluetooth2 Registers Settings
 * @brief Settings for registers of Bluetooth2 Click driver.
 */

/**
 * @addtogroup bluetooth2_set
 * @{
 */

/**
 * @brief Bluetooth2 list of AT commands.
 * @brief AT commands list of Bluetooth2 Click driver.
 */
#define BLUETOOTH2_ESCAPE_SEQUENCE                  "+++"
#define BLUETOOTH2_FACTORY_RESET                    "SET RESET"
#define BLUETOOTH2_LIST_PAIRINGS                    "SET BT PAIR"
#define BLUETOOTH2_REMOVE_PAIRINGS                  "SET BT PAIR *"
#define BLUETOOTH2_SW_RESET                         "RESET"
#define BLUETOOTH2_SET_DEVICE_NAME                  "SET BT NAME "
#define BLUETOOTH2_FIND_OTHER_DEVICES               "INQUIRY "
#define BLUETOOTH2_PAIR                             "PAIR "
#define BLUETOOTH2_SET_CONTROL_CONFIG               "SET CONTROL CONFIG "
#define BLUETOOTH2_ENABLE_OK_WITH_DEFAULT_VALUES    "0040 1100"
#define BLUETOOTH2_DEV_ADDRESS_FORMAT               "xx:xx:xx:xx:xx:xx"

/**
 * @brief Bluetooth2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                             200

/*! @} */ // bluetooth2_set

/**
 * @defgroup bluetooth2_map Bluetooth2 MikroBUS Map
 * @brief MikroBUS pin mapping of Bluetooth2 Click driver.
 */

/**
 * @addtogroup bluetooth2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Bluetooth2 Click to the selected MikroBUS.
 */
#define BLUETOOTH2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.cts  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.aio  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.io7  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // bluetooth2_map
/*! @} */ // bluetooth2
/**
 * @brief Bluetooth2 Click context object.
 * @details Context object definition of Bluetooth2 Click driver.
 */
typedef struct bluetooth2_s
{
    digital_out_t  rst;                      /**< Reset. */
    digital_out_t  io7;                      /**< Programmable GPIO. */
    digital_out_t  cts;                      /**< Clear to Send. */
    digital_in_t   rts;                      /**< Request to Send. */
    
    uart_t         uart;                     /**< UART driver object. */
    analog_in_t    adc;                      /**< ADC module object. */

    char uart_rx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */

} bluetooth2_t;

/**
 * @brief Bluetooth2 Click configuration object.
 * @details Configuration object definition of Bluetooth2 Click driver.
 */
typedef struct
{
    pin_name_t  rx_pin;                     /**< RX pin. */
    pin_name_t  tx_pin;                     /**< TX pin. */
    pin_name_t  cts;                        /**< Clear to Send. */
    pin_name_t  aio;                        /**< Analog input. */
    pin_name_t  rst;                        /**< Reset. */
    pin_name_t  io7;                        /**< Programmable GPIO. */
    pin_name_t  rts;                        /**< Request to Send. */

    analog_in_resolution_t resolution;      /**< ADC resolution. */
    float                  vref;            /**< ADC reference voltage. */

    uint32_t          baud_rate;            /**< Clock speed. */
    bool              uart_blocking;        /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;             /**< Data bits. */
    uart_parity_t     parity_bit;           /**< Parity bit. */
    uart_stop_bits_t  stop_bit;             /**< Stop bits. */

} bluetooth2_cfg_t;

/**
 * @brief Bluetooth2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BLUETOOTH2_OK = 0,
    BLUETOOTH2_ERROR = -1

} bluetooth2_return_value_t;

/*!
 * @addtogroup bluetooth2 Bluetooth2 Click Driver
 * @brief API for configuring and manipulating Bluetooth2 Click driver.
 * @{
 */

/**
 * @brief Bluetooth2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bluetooth2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bluetooth2_cfg_setup ( bluetooth2_cfg_t *cfg );

/**
 * @brief Bluetooth2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bluetooth2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_init ( bluetooth2_t *ctx, bluetooth2_cfg_t *cfg );

/**
 * @brief Bluetooth2 default configuration function.
 * @details This function executes a default configuration of Bluetooth2
 * click board.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void bluetooth2_default_cfg ( bluetooth2_t *ctx );

/**
 * @brief Bluetooth2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_generic_write ( bluetooth2_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Bluetooth2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_generic_read ( bluetooth2_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Bluetooth2 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_read_an_pin_value ( bluetooth2_t *ctx, uint16_t *data_out );

/**
 * @brief Bluetooth2 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t bluetooth2_read_an_pin_voltage ( bluetooth2_t *ctx, float *data_out );

/**
 * @brief Bluetooth2 set clear to send pin function.
 * @details This function sets the CTS pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bluetooth2_set_cts_pin ( bluetooth2_t *ctx, uint8_t state );

/**
 * @brief Bluetooth2 set reset pin function.
 * @details This function sets the RST pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bluetooth2_set_rst_pin ( bluetooth2_t *ctx, uint8_t state );

/**
 * @brief Bluetooth2 set PIO7 pin function.
 * @details This function sets the PIO7 pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bluetooth2_set_io7_pin ( bluetooth2_t *ctx, uint8_t state );

/**
 * @brief Bluetooth2 get request to send pin function.
 * @details This function returns the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t bluetooth2_get_rts_pin ( bluetooth2_t *ctx );

/**
 * @brief Bluetooth2 write command function.
 * @details This function sends a desired command with the CR byte appended to.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[in] data_buf : Command string.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_write_command ( bluetooth2_t *ctx, char *data_buf );

/**
 * @brief Bluetooth2 hw reset function.
 * @details This function resets the module by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bluetooth2_hw_reset ( bluetooth2_t *ctx );

/**
 * @brief Bluetooth2 toggle mode function.
 * @details This function is used to toggle between command mode and data mode
 * by issuing the escape sequence.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_toggle_mode ( bluetooth2_t *ctx );

/**
 * @brief Bluetooth2 factory reset function.
 * @details This function factory resets the device.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Factory reset does not clear the pairings.
 */
err_t bluetooth2_factory_reset ( bluetooth2_t *ctx );

/**
 * @brief Bluetooth2 sw reset function.
 * @details This function sw resets the device.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_sw_reset ( bluetooth2_t *ctx );

/**
 * @brief Bluetooth2 remove pairings function.
 * @details This function removes all the device pairings.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_remove_pairings ( bluetooth2_t *ctx );

/**
 * @brief Bluetooth2 list current pairings function.
 * @details This function lists all current pairings.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_list_pairings ( bluetooth2_t *ctx );

/**
 * @brief Bluetooth2 set local device name function.
 * @details This function sets the local device name.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[in] dev_name : Device name ( up to 140 characters ).
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_set_device_name ( bluetooth2_t *ctx, char *dev_name );

/**
 * @brief Bluetooth2 find other devices function.
 * @details This function is used to find other Bluetooth devices in the area i.e. 
 * to make a device discovery.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[in] timeout : The maximum amount of time (in units of 1.28 seconds) before the 
 * inquiry process is halted. Range: 1-48.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_find_other_devices ( bluetooth2_t *ctx, uint8_t timeout );

/**
 * @brief Bluetooth2 set local device name function.
 * @details This function sets the local device name.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @param[in] dev_addr : Bluetooth device address of the remote device in format xx:xx:xx:xx:xx:xx 
 * where x is a hexadecimal digit.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bluetooth2_pair ( bluetooth2_t *ctx, uint8_t *dev_addr );

/**
 * @brief Bluetooth2 enable OK response function.
 * @details This function enables OK response. 
 * The module will display "OK." after each successful command.
 * @param[in] ctx : Click context object.
 * See #bluetooth2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This will set optional_block_1 and config_block of CONTROL CONFIG reg to 0040 1100 (default).
 */
err_t bluetooth2_enable_ok_response ( bluetooth2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BLUETOOTH2_H

/*! @} */ // bluetooth2

// ------------------------------------------------------------------------ END
