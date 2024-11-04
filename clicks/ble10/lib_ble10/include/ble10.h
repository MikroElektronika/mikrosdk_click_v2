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
 * @file ble10.h
 * @brief This file contains API for BLE 10 Click Driver.
 */

#ifndef BLE10_H
#define BLE10_H

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
 * @addtogroup ble10 BLE 10 Click Driver
 * @brief API for configuring and manipulating BLE 10 Click driver.
 * @{
 */

/**
 * @defgroup ble10_cmd BLE 10 Device Settings
 * @brief Settings for registers of BLE 10 Click driver.
 */

/**
 * @addtogroup ble10_cmd
 * @{
 */

/**
 * @brief BLE 10 AT commands list.
 * @details Specified list of AT commands of BLE 10 Click driver.
 */
#define BLE10_CMD_AT            "AT"        // Attention
#define BLE10_CMD_ATRST         "ATRST"     // Software Reset
#define BLE10_CMD_ATFRST        "ATFRST"    // Factory Reset
#define BLE10_CMD_ATSN          "ATSN"      // Set Device Name
#define BLE10_CMD_ATP           "ATP"       // List Pairings
#define BLE10_CMD_ATCP          "ATCP"      // Clear Pairings
#define BLE10_CMD_ATDI          "ATDI"      // Discover Nearby Devices
#define BLE10_CMD_ATT           "ATT"       // Get temperature

/**
 * @brief BLE 10 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE         500

/*! @} */ // ble10_cmd

/**
 * @defgroup ble10_map BLE 10 MikroBUS Map
 * @brief MikroBUS pin mapping of BLE 10 Click driver.
 */

/**
 * @addtogroup ble10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLE 10 Click to the selected MikroBUS.
 */
#define BLE10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.ain  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pio3 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts  = MIKROBUS( mikrobus, MIKROBUS_INT ); \
    cfg.cts  = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // ble10_map
/*! @} */ // ble10

/**
 * @brief BLE 10 Click context object.
 * @details Context object definition of BLE 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                      /**< Reset pin. */
    digital_out_t cts;                      /**< Clear To Send pin. */

    // Input pins
    digital_in_t  rts;                      /**< Ready To Send pin. */
    digital_in_t  pio3;                     /**< PIO3 pin. */

    // Modules
    uart_t        uart;                     /**< UART driver object. */
    analog_in_t   adc;                      /**< ADC module object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */

} ble10_t;

/**
 * @brief BLE 10 Click configuration object.
 * @details Configuration object definition of BLE 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */
    pin_name_t ain;                     /**< Analog input pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin. */
    pin_name_t cts;                     /**< Clear To Send pin. */
    pin_name_t rts;                     /**< Ready To Send pin. */
    pin_name_t pio3;                    /**< PIO3 pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */
    
    analog_in_resolution_t  resolution; /**< ADC resolution. */
    float                   vref;       /**< ADC reference voltage. */

} ble10_cfg_t;

/**
 * @brief BLE 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BLE10_OK = 0,
    BLE10_ERROR = -1

} ble10_return_value_t;

/*!
 * @addtogroup ble10 BLE 10 Click Driver
 * @brief API for configuring and manipulating BLE 10 Click driver.
 * @{
 */

/**
 * @brief BLE 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ble10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ble10_cfg_setup ( ble10_cfg_t *cfg );

/**
 * @brief BLE 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ble10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_init ( ble10_t *ctx, ble10_cfg_t *cfg );

/**
 * @brief BLE 10 default configuration function.
 * @details This function executes a default configuration of BLE 10
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void ble10_default_cfg ( ble10_t *ctx );

/**
 * @brief BLE 10 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_generic_write ( ble10_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief BLE 10 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_generic_read ( ble10_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief BLE 10 get ready to send pin function.
 * @details This function returns the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ble10_get_rts_pin ( ble10_t *ctx );

/**
 * @brief BLE 10 get PIO3 pin function.
 * @details This function returns the PIO3 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ble10_get_pio3_pin ( ble10_t *ctx );

/**
 * @brief BLE 10 set clear to send pin function.
 * @details This function sets the CTS pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ble10_set_cts_pin ( ble10_t *ctx, uint8_t state ); 

/**
 * @brief BLE 10 set reset pin function.
 * @details This function sets the RST pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ble10_set_rst_pin ( ble10_t *ctx, uint8_t state );

/**
 * @brief BLE 10 hw reset function.
 * @details This function resets the module by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ble10_hw_reset ( ble10_t *ctx );

/**
 * @brief BLE 10 software reset function.
 * @details This function software resets the device.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_sw_reset ( ble10_t *ctx );

/**
 * @brief BLE 10 factory reset function.
 * @details This function factory resets the device.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Factory reset clears the pairings.
 */
err_t ble10_factory_reset ( ble10_t *ctx );

/**
 * @brief BLE 10 send command function.
 * @details This function sends a desired command with the CR byte appended to.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_send_cmd ( ble10_t *ctx, char *at_cmd_buf );

/**
 * @brief BLE 10 send command with parameter function.
 * @details This function sends a desired command with the parameter buffer and CR byte appended to.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @param[in] param_buf : Parameters string.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_send_cmd_with_parameter ( ble10_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief BLE 10 send command check function.
 * @details This function sends a desired command with the question mark and CR byte appended to.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command string.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_send_cmd_check ( ble10_t *ctx, char *at_cmd_buf );

/**
 * @brief BLE 10 remove pairings function.
 * @details This function removes all the device pairings.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_remove_pairings ( ble10_t *ctx );

/**
 * @brief BLE 10 list current pairings function.
 * @details This function lists all current pairings.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_list_pairings ( ble10_t *ctx );

/**
 * @brief BLE 10 set local device name function.
 * @details This function sets the local device name.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[in] dev_name : Device name ( up to 20 characters ).
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_set_device_name ( ble10_t *ctx, char *dev_name );

/**
 * @brief BLE 10 discover nearby devices function.
 * @details This function discovers nearby advertising LE devices.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_discover_nearby_devices ( ble10_t *ctx );

/**
 * @brief BLE 10 get temperature function.
 * @details This function executes get temperature command which returns the current temperature
 * of the module's internal temperature sensor.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_get_temperature ( ble10_t *ctx );

/**
 * @brief BLE 10 read AIN pin value function.
 * @details This function reads results of AD conversion of the AIN pin.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble10_read_an_pin_value ( ble10_t *ctx, uint16_t *data_out );

/**
 * @brief BLE 10 read AIN pin voltage level function.
 * @details This function reads results of AD conversion of the AIN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ble10_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t ble10_read_an_pin_voltage ( ble10_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // BLE10_H

/*! @} */ // ble10

// ------------------------------------------------------------------------ END
