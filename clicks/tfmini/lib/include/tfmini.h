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
 * @file tfmini.h
 * @brief This file contains API for TFmini Click Driver.
 */

#ifndef TFMINI_H
#define TFMINI_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_uart.h"

/*!
 * @addtogroup tfmini TFmini Click Driver
 * @brief API for configuring and manipulating TFmini Click driver.
 * @{
 */

/**
 * @defgroup tfmini_cmd TFmini Device Settings
 * @brief Settings for registers of TFmini Click driver.
 */

/**
 * @addtogroup tfmini_cmd
 * @{
 */

/**
 * @brief TFmini command frame macros.
 * @details Specified macros for command frame of TFmini Click driver.
 */
#define TFMINI_CMD_HEADER                   0x5A
#define TFMINI_CMD_ID_FW_VERSION            0x01
#define TFMINI_CMD_ID_SYSTEM_RESET          0x02
#define TFMINI_CMD_ID_FRAME_RATE            0x03
#define TFMINI_CMD_ID_TRIGGER_DETECTION     0x04
#define TFMINI_CMD_ID_OUTPUT_FORMAT         0x05
#define TFMINI_CMD_ID_BAUD_RATE             0x06
#define TFMINI_CMD_ID_ENABLE_OUTPUT         0x07
#define TFMINI_CMD_ID_COM_SELECTION         0x0A
#define TFMINI_CMD_ID_SLAVE_ADDRESS         0x0B
#define TFMINI_CMD_ID_DATA_FRAME            0x00
#define TFMINI_CMD_ID_IO_MODE_ENABLE        0x3B
#define TFMINI_CMD_ID_RESTORE_FACTORY       0x10
#define TFMINI_CMD_ID_SAVE_SETTINGS         0x11

/**
 * @brief TFmini output data frame macros.
 * @details Specified macros for output data frame of TFmini Click driver.
 */
#define TFMINI_HEADER                       0x59
#define TFMINI_FRAME_SIZE                   0x07
#define TFMINI_MAX_BYTES_BEFORE_HEADER      100
#define TFMINI_LOW_SIGNAL_STRENGTH          -1
#define TFMINI_SIGNAL_STRENGTH_SATURATION   -2
#define TFMINI_AMBIENT_LIGHT_SATURATION     -4
#define TFMINI_NO_HEADER_FOUND              -5
#define TFMINI_WRONG_CHECKSUM               -6

/**
 * @brief TFmini driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                     500

/**
 * @brief TFmini device address setting.
 * @details Specified setting for device slave address selection of
 * TFmini Click driver.
 */
#define TFMINI_SET_DEV_ADDR                 0x10

/*! @} */ // tfmini_cmd

/**
 * @defgroup tfmini_map TFmini MikroBUS Map
 * @brief MikroBUS pin mapping of TFmini Click driver.
 */

/**
 * @addtogroup tfmini_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TFmini Click to the selected MikroBUS.
 */
#define TFMINI_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );

/*! @} */ // tfmini_map
/*! @} */ // tfmini

/**
 * @brief TFmini Click driver selector.
 * @details Selects target driver interface of TFmini Click driver.
 */
typedef enum
{
    TFMINI_DRV_SEL_UART,     /**< UART driver descriptor. */
    TFMINI_DRV_SEL_I2C       /**< I2C driver descriptor. */

} tfmini_drv_t;

/**
 * @brief TFmini Click command frame definition structure.
 * @details Command frame definition object of TFmini Click driver.
 */
typedef struct
{
    uint8_t cmd_id;                         /**< Command ID. */
    uint8_t payload[ TFMINI_FRAME_SIZE ];   /**< Payload buffer. */
    uint8_t payload_len;                    /**< Payload length. */

} tfmini_frame_t;

/**
 * @brief TFmini Click context object.
 * @details Context object definition of TFmini Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                               /**< I2C driver object. */
    uart_t       uart;                              /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    
    uint8_t      slave_address;                     /**< Device slave address (used for I2C driver). */
    tfmini_drv_t drv_sel;                           /**< Master driver interface selector. */

} tfmini_t;

/**
 * @brief TFmini Click configuration object.
 * @details Configuration object definition of TFmini Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */
    uint32_t          i2c_speed;        /**< I2C serial speed. */
    uint8_t           i2c_address;      /**< I2C slave address. */
    
    tfmini_drv_t      drv_sel;          /**< Master driver interface selector. */

} tfmini_cfg_t;

/**
 * @brief TFmini Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TFMINI_OK = 0,
    TFMINI_ERROR = -1

} tfmini_return_value_t;

/*!
 * @addtogroup tfmini TFmini Click Driver
 * @brief API for configuring and manipulating TFmini Click driver.
 * @{
 */

/**
 * @brief TFmini configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tfmini_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tfmini_cfg_setup ( tfmini_cfg_t *cfg );

/**
 * @brief TFmini driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #tfmini_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #tfmini_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void tfmini_drv_interface_selection ( tfmini_cfg_t *cfg, tfmini_drv_t drv_sel );

/**
 * @brief TFmini initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tfmini_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tfmini_init ( tfmini_t *ctx, tfmini_cfg_t *cfg );

/**
 * @brief TFmini default configuration function.
 * @details This function executes a default configuration of TFmini
 * click board.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t tfmini_default_cfg ( tfmini_t *ctx );

/**
 * @brief TFmini send frame function.
 * @details This function sends a command frame to the sensor.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @param[in] frame : Command frame.
 * See #tfmini_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tfmini_send_frame ( tfmini_t *ctx, tfmini_frame_t frame );

/**
 * @brief TFmini get response function.
 * @details This function reads the command response frame of the sensor.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @param[out] frame : Command response frame.
 * See #tfmini_frame_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -5 - No header found,
 *         @li @c -6 - Wrong checksum.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tfmini_get_response ( tfmini_t *ctx, tfmini_frame_t *frame );

/**
 * @brief TFmini get firmware version function.
 * @details This function reads the sensor firmware version.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @param[out] fw_version : 24bit firmware version value in form V3V2V1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tfmini_get_firmware_version ( tfmini_t *ctx, uint32_t *fw_version );

/**
 * @brief TFmini system reset function.
 * @details This function resets the system by issuing the system reset command.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tfmini_system_reset ( tfmini_t *ctx );

/**
 * @brief TFmini set frame rate function.
 * @details This function sets the output data frame rate.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @param[in] frame_rate : Output data frame rate in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tfmini_set_frame_rate ( tfmini_t *ctx, uint16_t frame_rate );

/**
 * @brief TFmini change interface function.
 * @details This function sets the communication interface bit of the appropriate register.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #tfmini_drv_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note A tfmini_save_settings command must be executed after this function call in order for the changes
 * to take efect. After changing the communication interface reprogram the board with a properly interface
 * selected using tfmini_drv_interface_selection function, and make sure to set the click onboard switch for
 * the proper communication interface.
 */
err_t tfmini_change_interface ( tfmini_t *ctx, tfmini_drv_t drv_sel );

/**
 * @brief TFmini factory default function.
 * @details This function resets the system to factory settings by issuing the factory default command.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tfmini_factory_default ( tfmini_t *ctx );

/**
 * @brief TFmini save settings function.
 * @details This function issues the save settings command.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tfmini_save_settings ( tfmini_t *ctx );

/**
 * @brief TFmini get measurement function.
 * @details This function reads the output data frame and obtains the distance, strength and temperature values from it.
 * @param[in] ctx : Click context object.
 * See #tfmini_t object definition for detailed explanation.
 * @param[out] distance : Target object distance in cm.
 * @param[out] strength : Signal strength [0-65535].
 * @param[out] temperature : Sensor internal temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or low signal strength,
 *         @li @c -2 - Signal strength saturation,
 *         @li @c -4 - Ambient light saturation,
 *         @li @c -5 - No header found,
 *         @li @c -6 - Wrong checksum.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tfmini_get_measurement ( tfmini_t *ctx, int16_t *distance, int16_t *strength, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // TFMINI_H

/*! @} */ // tfmini

// ------------------------------------------------------------------------ END
