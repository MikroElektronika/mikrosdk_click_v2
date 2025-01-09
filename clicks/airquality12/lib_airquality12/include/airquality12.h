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
 * @file airquality12.h
 * @brief This file contains API for Air Quality 12 Click Driver.
 */

#ifndef AIRQUALITY12_H
#define AIRQUALITY12_H

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
 * @addtogroup airquality12 Air Quality 12 Click Driver
 * @brief API for configuring and manipulating Air Quality 12 Click driver.
 * @{
 */

/**
 * @defgroup airquality12_reg Air Quality 12 Registers List
 * @brief List of registers of Air Quality 12 Click driver.
 */

/**
 * @addtogroup airquality12_reg
 * @{
 */

/**
 * @brief Air Quality 12 commands list.
 * @details Specified commands list of Air Quality 12 Click driver.
 */
#define AIRQUALITY12_CMD_GET_PRODUCT_ID         0x00
#define AIRQUALITY12_CMD_GET_TRACKING_NUMBER    0x01
#define AIRQUALITY12_CMD_GET_OPERATION_MODE     0x10
#define AIRQUALITY12_CMD_SET_OPERATION_MODE     0x11
#define AIRQUALITY12_CMD_SET_HUMIDITY           0x12
#define AIRQUALITY12_CMD_GET_MEASUREMENT        0x18
#define AIRQUALITY12_CMD_CONFIG_GPIO            0x20
#define AIRQUALITY12_CMD_GET_GPIO               0x21
#define AIRQUALITY12_CMD_SET_GPIO               0x22
#define AIRQUALITY12_CMD_CLEAR_GPIO             0x23
#define AIRQUALITY12_CMD_READ_FLASH_SHADOW      0x40
#define AIRQUALITY12_CMD_WRITE_FLASH_SHADOW     0x41
#define AIRQUALITY12_CMD_WRITE_FLASH            0x42
#define AIRQUALITY12_CMD_RESET                  0x8F

/*! @} */ // airquality12_reg

/**
 * @defgroup airquality12_set Air Quality 12 Registers Settings
 * @brief Settings for registers of Air Quality 12 Click driver.
 */

/**
 * @addtogroup airquality12_set
 * @{
 */

/**
 * @brief Air Quality 12 operating mode setting.
 * @details Specified setting for operating mode of Air Quality 12 Click driver.
 */
#define AIRQUALITY12_OP_MODE_SUSPEND            0x00
#define AIRQUALITY12_OP_MODE_IAQ_2ND_GEN        0x01
#define AIRQUALITY12_OP_MODE_IAQ_2ND_GEN_ULP    0x02
#define AIRQUALITY12_OP_MODE_PBAQ               0x05
#define AIRQUALITY12_OP_MODE_SENSOR_CLEANING    0x80

/**
 * @brief Air Quality 12 humidity setting.
 * @details Specified setting for humidity of Air Quality 12 Click driver.
 */
#define AIRQUALITY12_HUMIDITY_MIN               0
#define AIRQUALITY12_HUMIDITY_DEFAULT           50
#define AIRQUALITY12_HUMIDITY_MAX               100

/**
 * @brief Air Quality 12 product ID setting.
 * @details Specified setting for product ID of Air Quality 12 Click driver.
 */
#define AIRQUALITY12_PRODUCT_ID                 0x2310

/**
 * @brief Air Quality 12 status setting.
 * @details Specified setting for status of Air Quality 12 Click driver.
 */
#define AIRQUALITY12_STATUS_INVALID_CMD         0x80
#define AIRQUALITY12_STATUS_WRONG_CHECKSUM      0x40
#define AIRQUALITY12_STATUS_I2C_NACK            0x20
#define AIRQUALITY12_STATUS_DATA_NOT_READY      0x10
#define AIRQUALITY12_STATUS_NO_MORE_CLEANING    0x08
#define AIRQUALITY12_STATUS_OK                  0x00

/**
 * @brief Air Quality 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Air Quality 12 Click driver.
 */
#define AIRQUALITY12_DEVICE_ADDRESS             0x38

/**
 * @brief Air Quality 12 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define AIRQUALITY12_TX_DRV_BUFFER_SIZE         100
#define AIRQUALITY12_RX_DRV_BUFFER_SIZE         300

/*! @} */ // airquality12_set

/**
 * @defgroup airquality12_map Air Quality 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Air Quality 12 Click driver.
 */

/**
 * @addtogroup airquality12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Air Quality 12 Click to the selected MikroBUS.
 */
#define AIRQUALITY12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // airquality12_map
/*! @} */ // airquality12

/**
 * @brief Air Quality 12 Click driver selector.
 * @details Selects target driver interface of Air Quality 12 Click driver.
 */
typedef enum
{
    AIRQUALITY12_DRV_SEL_UART,          /**< UART driver descriptor. */
    AIRQUALITY12_DRV_SEL_I2C            /**< I2C driver descriptor. */

} airquality12_drv_t;

/**
 * @brief Air Quality 12 Click context object.
 * @details Context object definition of Air Quality 12 Click driver.
 */
typedef struct airquality12_s
{
    digital_out_t rst;                  /**< Reset pin (active low). */
    digital_out_t gp1;                  /**< GPIO 1 pin. */

    digital_in_t int_pin;               /**< Interrupt pin (active high). */

    i2c_master_t i2c;                   /**< I2C driver object. */
    uart_t uart;                        /**< UART driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    airquality12_drv_t drv_sel;         /**< Master driver interface selector. */

    uint8_t uart_rx_buffer[ AIRQUALITY12_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ AIRQUALITY12_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} airquality12_t;

/**
 * @brief Air Quality 12 Click configuration object.
 * @details Configuration object definition of Air Quality 12 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */
    pin_name_t rst;                     /**< Reset pin (active low). */
    pin_name_t gp1;                     /**< GPIO 1 pin. */
    pin_name_t int_pin;                 /**< Interrupt pin (active high). */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

    airquality12_drv_t drv_sel;         /**< Master driver interface selector. */

} airquality12_cfg_t;

/**
 * @brief Air Quality 12 Click request and response parameters object.
 * @details Request and response parameters object definition of Air Quality 12 Click driver.
 */
typedef struct
{
    uint8_t req_buf[ 2 ];               /**< Request parameters buffer. */
    uint8_t req_len;                    /**< Number of request parameters bytes. */
    uint8_t resp_buf[ 9 ];              /**< Response parameters buffer. */
    uint8_t resp_len;                   /**< Number of response parameters bytes. */
    uint8_t status;                     /**< Command status byte code. */

} airquality12_param_t;

/**
 * @brief Air Quality 12 Click device info object.
 * @details Device info object definition of Air Quality 12 Click driver.
 */
typedef struct
{
    uint16_t product_id;                /**< Product ID word. */
    uint8_t fw_ver_major;               /**< Firmware version major byte. */
    uint8_t fw_ver_minor;               /**< Firmware version minor byte. */
    uint8_t fw_ver_patch;               /**< Firmware version patch byte. */
    uint8_t tracking_num[ 6 ];          /**< ASIC tracking number bytes. */

} airquality12_info_t;

/**
 * @brief Air Quality 12 Click measurement results object.
 * @details Measurement results object definition of Air Quality 12 Click driver.
 */
typedef struct
{
    uint8_t sample_num;                 /**< Sample counter byte, incremented with each sample. */
    float iaq;                          /**< Indoor Air Quality index in UBA levels. */
    float tvoc;                         /**< Total Volatile Organic Compounds in mg/m^3. */
    float etoh;                         /**< Ethanol Equivalent in ppm. */
    uint16_t eco2;                      /**< Estimated CO2 in ppm. */
    uint16_t rel_iaq;                   /**< Relative IAQ index. */

} airquality12_results_t;

/**
 * @brief Air Quality 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AIRQUALITY12_OK = 0,
    AIRQUALITY12_ERROR = -1

} airquality12_return_value_t;

/*!
 * @addtogroup airquality12 Air Quality 12 Click Driver
 * @brief API for configuring and manipulating Air Quality 12 Click driver.
 * @{
 */

/**
 * @brief Air Quality 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #airquality12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void airquality12_cfg_setup ( airquality12_cfg_t *cfg );

/**
 * @brief Air Quality 12 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #airquality12_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #airquality12_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void airquality12_drv_interface_sel ( airquality12_cfg_t *cfg, airquality12_drv_t drv_sel );

/**
 * @brief Air Quality 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #airquality12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_init ( airquality12_t *ctx, airquality12_cfg_t *cfg );

/**
 * @brief Air Quality 12 default configuration function.
 * @details This function executes a default configuration of Air Quality 12
 * Click board.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t airquality12_default_cfg ( airquality12_t *ctx );

/**
 * @brief Air Quality 12 send cmd function.
 * @details This function sends the selected command with parameters and reads response.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in,out] params : Parameters structure with request and response buffers.
 * See #airquality12_param_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_send_cmd ( airquality12_t *ctx, uint8_t cmd, airquality12_param_t *params );

/**
 * @brief Air Quality 12 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void airquality12_set_rst_pin ( airquality12_t *ctx, uint8_t state );

/**
 * @brief Air Quality 12 set gp1 pin function.
 * @details This function sets the GP1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void airquality12_set_gp1_pin ( airquality12_t *ctx, uint8_t state );

/**
 * @brief Air Quality 12 reset device function.
 * @details This function resets device by toggling the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void airquality12_reset_device ( airquality12_t *ctx );

/**
 * @brief Air Quality 12 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t airquality12_get_int_pin ( airquality12_t *ctx );

/**
 * @brief Air Quality 12 check comm function.
 * @details This function checks the communication by reading and verifying the product ID.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_check_comm ( airquality12_t *ctx );

/**
 * @brief Air Quality 12 get sensor info function.
 * @details This function reads the device product ID, firmware version, and tracking number.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[out] info : Sensor information structure.
 * See #airquality12_info_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_get_sensor_info ( airquality12_t *ctx, airquality12_info_t *info );

/**
 * @brief Air Quality 12 get op mode function.
 * @details This function reads the sensor operating mode.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[out] op_mode : Sensor operating mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_get_op_mode ( airquality12_t *ctx, uint8_t *op_mode );

/**
 * @brief Air Quality 12 set op mode function.
 * @details This function sets the sensor operating mode.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] op_mode : Sensor operating mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_set_op_mode ( airquality12_t *ctx, uint8_t op_mode );

/**
 * @brief Air Quality 12 set humidity function.
 * @details This function sets the relative humidity level in percents.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] humidity : Relative humidity level in percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default humidity level is set to 50%. Measure the humidity level externally and adjust
 * this setting in a loop before reading measurements.
 */
err_t airquality12_set_humidity ( airquality12_t *ctx, float humidity );

/**
 * @brief Air Quality 12 get measurement function.
 * @details This function reads the sensor measurement results.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[out] results : Sensor measurement results.
 * See #airquality12_results_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_get_measurement ( airquality12_t *ctx, airquality12_results_t *results );

/**
 * @brief Air Quality 12 config gpio function.
 * @details This function sets the GPIO1 and GPIO2 pins direction.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] gpio_mask : GPIO mask (bit0 - GPIO1, bit1 - GPIO2).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_config_gpio ( airquality12_t *ctx, uint8_t gpio_mask );

/**
 * @brief Air Quality 12 get gpio function.
 * @details This function reads the GPIO1-4 pins value.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] gpio_mask : GPIO mask (bit0 - GPIO1, bit1 - GPIO2, bit2 - GPIO3, bit3 - GPIO4).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_get_gpio ( airquality12_t *ctx, uint8_t *gpio_mask );

/**
 * @brief Air Quality 12 set gpio function.
 * @details This function sets the GPIO1 and GPIO2 pins to high logic state.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] gpio_mask : GPIO mask (bit0 - GPIO1, bit1 - GPIO2).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_set_gpio ( airquality12_t *ctx, uint8_t gpio_mask );

/**
 * @brief Air Quality 12 clear gpio function.
 * @details This function clears the GPIO1 and GPIO2 pins to low logic state.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @param[in] gpio_mask : GPIO mask (bit0 - GPIO1, bit1 - GPIO2).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality12_clear_gpio ( airquality12_t *ctx, uint8_t gpio_mask );

/**
 * @brief Air Quality 12 perform cleaning function.
 * @details This function performs the sensor cleaning procedure.
 * @param[in] ctx : Click context object.
 * See #airquality12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The sensor must run a cleaning procedure once in its lifetime.
 * The cleaning process takes up to 1 minute.
 */
err_t airquality12_perform_cleaning ( airquality12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // AIRQUALITY12_H

/*! @} */ // airquality12

// ------------------------------------------------------------------------ END
