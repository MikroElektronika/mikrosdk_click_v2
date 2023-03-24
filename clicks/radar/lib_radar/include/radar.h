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
 * @file radar.h
 * @brief This file contains API for Radar Click Driver.
 */

#ifndef RADAR_H
#define RADAR_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup radar Radar Click Driver
 * @brief API for configuring and manipulating Radar Click driver.
 * @{
 */

/**
 * @defgroup radar_cmd Radar Device Settings
 * @brief Settings for registers of Radar Click driver.
 */

/**
 * @addtogroup radar_cmd
 * @{
 */

/**
 * @brief Radar control commands.
 * @details Specified setting for control commands of Radar Click driver.
 */
#define RADAR_CMD_HEADER                0xD9
#define RADAR_CMD_ID_VERSION            0x00
#define RADAR_CMD_ID_ACK                0x02
#define RADAR_CMD_ID_MAX_DETECT_RANGE   0x03
#define RADAR_CMD_ID_SENSITIVITY        0x04
#define RADAR_CMD_ID_DETECT_OUT         0x05
#define RADAR_CMD_ID_DETECT_IN_EVT      0x06
#define RADAR_CMD_ID_DETECT_OUT_EVT     0x07
#define RADAR_CMD_ID_RESET_CONFIG       0x08
#define RADAR_CMD_ID_GET_DETECT_STATUS  0x09
#define RADAR_CMD_ID_DETECT_ENABLE      0x0A
#define RADAR_CMD_ID_RFCW_MODE          0x0B
#define RADAR_CMD_ID_CHIP_TEMPERATURE   0x0D
#define RADAR_CMD_ID_SLEEP_MODE         0x0E
#define RADAR_CMD_ID_CALIB_MODE         0x0F
#define RADAR_CMD_ID_CALIB_MSG          0x10
#define RADAR_CMD_ID_CALIB_MSG_RATE     0x11
#define RADAR_CMD_ID_MIN_DETECT_RANGE   0x30
#define RADAR_CMD_ID_MACRO_THRESHOLD    0x31
#define RADAR_CMD_ID_MICRO_THRESHOLD    0x32
#define RADAR_CMD_ID_MACRO_VALID        0x33
#define RADAR_CMD_ID_MICRO_VALID        0x34
#define RADAR_CMD_ID_DETECT_MODE        0x35
#define RADAR_CMD_ID_MACRO_DETECT_RANGE 0x36
#define RADAR_CMD_ID_MACRO_DETECT_DELAY 0x37
#define RADAR_CMD_ID_CHIRP_PER_FRAME    0x38
#define RADAR_CMD_ID_UNIQUE_ID          0xF7

/**
 * @brief Radar set command results.
 * @details Specified set command results of Radar Click driver.
 */
#define RADAR_SET_CMD_FAIL              0x00
#define RADAR_SET_CMD_SUCCESS           0x01

/**
 * @brief Radar response timeout value.
 * @details Specified response timeout value in milliseconds of Radar Click driver.
 */
#define RADAR_TIMEOUT                   1000

/**
 * @brief Radar detection range values.
 * @details Specified detection range values of Radar Click driver.
 */
#define RADAR_DEFAULT_MIN_RANGE         0.0
#define RADAR_DEFAULT_MAX_RANGE         3.0

/**
 * @brief Radar driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                 256

/*! @} */ // radar_cmd

/**
 * @defgroup radar_map Radar MikroBUS Map
 * @brief MikroBUS pin mapping of Radar Click driver.
 */

/**
 * @addtogroup radar_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Radar Click to the selected MikroBUS.
 */
#define RADAR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // radar_map
/*! @} */ // radar

/**
 * @brief Radar Click float bytes type object.
 * @details Float bytes type object definition of Radar Click driver.
 */
typedef union
{
    uint8_t b_data[ 4 ];
    float f_data;
    
} radar_float_bytes_t;

/**
 * @brief Radar Click context object.
 * @details Context object definition of Radar Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset pin. */

    // Input pins
    digital_in_t gp2;                           /**< GPIO2 pin - bootloader mode indication. */
    digital_in_t gp1;                           /**< GPIO1 pin - presence detected indication. */
    digital_in_t gp0;                           /**< GPIO0 pin - no presence indication. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */

} radar_t;

/**
 * @brief Radar Click configuration object.
 * @details Configuration object definition of Radar Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset pin. */
    pin_name_t gp2;                             /**< GPIO2 pin - bootloader mode indication. */
    pin_name_t gp1;                             /**< GPIO1 pin - presence detected indication. */
    pin_name_t gp0;                             /**< GPIO0 pin - no presence indication. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} radar_cfg_t;

/**
 * @brief Radar Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RADAR_OK = 0,
    RADAR_ERROR = -1

} radar_return_value_t;

/*!
 * @addtogroup radar Radar Click Driver
 * @brief API for configuring and manipulating Radar Click driver.
 * @{
 */

/**
 * @brief Radar configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #radar_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void radar_cfg_setup ( radar_cfg_t *cfg );

/**
 * @brief Radar initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #radar_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radar_init ( radar_t *ctx, radar_cfg_t *cfg );

/**
 * @brief Radar default configuration function.
 * @details This function executes a default configuration of Radar
 * click board.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t radar_default_cfg ( radar_t *ctx );

/**
 * @brief Radar data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radar_generic_write ( radar_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Radar data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radar_generic_read ( radar_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief Radar enable device function.
 * @details This function enables the device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void radar_enable_device ( radar_t *ctx );

/**
 * @brief Radar disable device function.
 * @details This function disables the device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void radar_disable_device ( radar_t *ctx );

/**
 * @brief Radar get gpio 2 pin function.
 * @details This function returns the GPIO 2 (bootloader mode indication) pin logic state.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t radar_get_gpio2_pin ( radar_t *ctx );

/**
 * @brief Radar get gpio 1 pin function.
 * @details This function returns the GPIO 1 (presence detected indication) pin logic state.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t radar_get_gpio1_pin ( radar_t *ctx );

/**
 * @brief Radar get gpio 0 pin function.
 * @details This function returns the GPIO 0 (no presence indication) pin logic state.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t radar_get_gpio0_pin ( radar_t *ctx );

/**
 * @brief Radar set command function.
 * @details This function sends a desired set command with payload to the module and 
 * waits for an ACK response.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @param[in] cmd_id : Set command ID.
 * @param[in] payload : Command payload content.
 * @param[in] payload_size : Command payload size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radar_set_command ( radar_t *ctx, uint8_t cmd_id, uint8_t *payload, uint8_t payload_size );

/**
 * @brief Radar get command function.
 * @details This function sends a desired get command to the module and waits for a response.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @param[in] cmd_id : Get command ID.
 * @param[out] payload : Command payload content.
 * @param[out] payload_size : Command payload size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radar_get_command ( radar_t *ctx, uint8_t cmd_id, uint8_t *payload, uint8_t *payload_size );

/**
 * @brief Radar get event function.
 * @details This function waits for an IN/OUT event or ACK command response.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @param[out] evt_id : Event ID.
 * @param[out] payload : Event payload content.
 * @param[out] payload_size : Event payload size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radar_get_event ( radar_t *ctx, uint8_t *evt_id, uint8_t *payload, uint8_t *payload_size );

/**
 * @brief Radar get temperature function.
 * @details This function reads the chip internal temperature.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @param[out] temperature : Chip internal temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radar_get_temperature ( radar_t *ctx, float *temperature );

/**
 * @brief Radar set detection range function.
 * @details This function sets the min and max presence detection values.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @param[in] min : Minimal detection level in meters [0.0 - 10.0].
 * @param[in] max : Maximal detection level in meters [0.2 - 10.0] (Must be >= min).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radar_set_detection_range ( radar_t *ctx, float min, float max );

/**
 * @brief Radar reset config function.
 * @details This function resets all configuration to default and performs a system reset.
 * @param[in] ctx : Click context object.
 * See #radar_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radar_reset_config ( radar_t *ctx );

/**
 * @brief Radar float ieee to mchip function.
 * @details This function converts the float IEEE-754 to Microchip representation.
 * @return None.
 * @note This is an empty function unless AI for PIC compiler is selected.
 */
void radar_float_ieee_to_mchip ( float *f_data );

/**
 * @brief Radar float ieee to mchip function.
 * @details This function converts the float IEEE-754 to Microchip representation.
 * @return None.
 * @note This is an empty function unless AI for PIC compiler is selected.
 */
void radar_float_mchip_to_ieee ( float *f_data );

#ifdef __cplusplus
}
#endif
#endif // RADAR_H

/*! @} */ // radar

// ------------------------------------------------------------------------ END
