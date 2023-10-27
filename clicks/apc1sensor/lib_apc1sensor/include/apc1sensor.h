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
 * @file apc1sensor.h
 * @brief This file contains API for APC1 Sensor Demo Driver.
 */

#ifndef APC1SENSOR_H
#define APC1SENSOR_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_uart.h"

/*!
 * @addtogroup apc1sensor APC1 Sensor Demo Driver
 * @brief API for configuring and manipulating APC1 Sensor Demo driver.
 * @{
 */

/**
 * @defgroup apc1sensor_cmd APC1 Sensor Commands List
 * @brief List of commands of APC1 Sensor Demo driver.
 */

/**
 * @addtogroup apc1sensor_cmd
 * @{
 */

/**
 * @brief APC1 Sensor commands definition.
 * @details Specified commands definition of APC1 Sensor Demo driver.
 */
#define APC1SENSOR_ADDRESS_CMD              0x40
#define APC1SENSOR_ADDRESS_RESPONSE         0x47
#define APC1SENSOR_CMD_SET_MEAS_MODE        0xE1
#define APC1SENSOR_CMD_REQ_MEASUREMENT      0xE2
#define APC1SENSOR_CMD_SET_MODE             0xE4
#define APC1SENSOR_CMD_GET_INFO             0xE9

/*! @} */ // apc1sensor_cmd

/**
 * @defgroup apc1sensor_set APC1 Sensor Registers Settings
 * @brief Settings for registers of APC1 Sensor Demo driver.
 */

/**
 * @addtogroup apc1sensor_set
 * @{
 */

/**
 * @brief APC1 Sensor header bytes definition.
 * @details Specified header bytes definition of APC1 Sensor Demo driver.
 */
#define APC1SENSOR_HEADER_0                 0x42
#define APC1SENSOR_HEADER_1                 0x4D

/**
 * @brief APC1 Sensor measurement mode definition.
 * @details Specified measurement mode definition of APC1 Sensor Demo driver.
 */
#define APC1SENSOR_MEASUREMENT_PASSIVE      0x00
#define APC1SENSOR_MEASUREMENT_ACTIVE       0x01

/**
 * @brief APC1 Sensor commands mode definition.
 * @details Specified commands mode definition of APC1 Sensor Demo driver.
 */
#define APC1SENSOR_MODE_IDLE                0x00
#define APC1SENSOR_MODE_MEASUREMENT         0x01
#define APC1SENSOR_MODE_RESET               0x0F

/**
 * @brief APC1 Sensor operating mode setting.
 * @details Specified setting for operating mode of APC1 Sensor Demo driver.
 */
#define APC1SENSOR_OPMODE_NORMAL            0
#define APC1SENSOR_OPMODE_DEEP_SLEEP        1
#define APC1SENSOR_OPMODE_RESET             2

/**
 * @brief APC1 Sensor driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define APC1SENSOR_TX_DRV_BUFFER_SIZE       100
#define APC1SENSOR_RX_DRV_BUFFER_SIZE       300

/**
 * @brief APC1 Sensor device address setting.
 * @details Specified setting for device slave address selection of
 * APC1 Sensor Demo driver.
 */
#define APC1SENSOR_DEVICE_ADDRESS           0x12

/*! @} */ // apc1sensor_set

/**
 * @defgroup apc1sensor_map APC1 Sensor MikroBUS Map
 * @brief MikroBUS pin mapping of APC1 Sensor Demo driver.
 */

/**
 * @addtogroup apc1sensor_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of APC1 Sensor Demo to the selected MikroBUS.
 */
#define APC1SENSOR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.set = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // apc1sensor_map
/*! @} */ // apc1sensor

/**
 * @brief APC1 Sensor Click driver selector.
 * @details Selects target driver interface of APC1 Sensor Click driver.
 */
typedef enum
{
    APC1SENSOR_DRV_SEL_I2C,     /**< UART driver descriptor. */
    APC1SENSOR_DRV_SEL_UART     /**< I2C driver descriptor. */

} apc1sensor_drv_t;

/**
 * @brief APC1 Sensor Demo context object.
 * @details Context object definition of APC1 Sensor Demo driver.
 */
typedef struct
{
    digital_out_t set;          /**< Operating mode set pin. */
    digital_out_t rst;          /**< Reset pin. */

    i2c_master_t i2c;           /**< I2C driver object. */
    uart_t uart;                /**< UART driver object. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint8_t uart_rx_buffer[ APC1SENSOR_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ APC1SENSOR_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    apc1sensor_drv_t drv_sel;   /**< Master driver interface selector. */

    uint8_t meas_mode;          /**< Measurement mode selection (UART only). */

} apc1sensor_t;

/**
 * @brief APC1 Sensor Demo configuration object.
 * @details Configuration object definition of APC1 Sensor Demo driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    pin_name_t set;             /**< Operating mode set pin. */
    pin_name_t rst;             /**< Reset pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

    apc1sensor_drv_t drv_sel;   /**< Master driver interface selector. */

} apc1sensor_cfg_t;

/**
 * @brief APC1 Sensor Demo measurement data object.
 * @details Measurement object definition of APC1 Sensor Demo driver.
 */
typedef struct
{
    uint16_t pm1_0;             /**< PM1.0 mass concentration. */
    uint16_t pm2_5;             /**< PM2.5 mass concentration. */
    uint16_t pm10;              /**< PM10 mass concentration. */
    uint16_t pm1_0_air;         /**< PM1.0 mass concentration in atmospheric environment. */
    uint16_t pm2_5_air;         /**< PM2.5 mass concentration in atmospheric environment. */
    uint16_t pm10_air;          /**< PM10 mass concentration in atmospheric environment. */
    uint16_t part_over_0_3um;   /**< Number of particles with diameter > 0.3µm in 0.1L of air. */
    uint16_t part_over_0_5um;   /**< Number of particles with diameter > 0.5µm in 0.1L of air. */
    uint16_t part_over_1_0um;   /**< Number of particles with diameter > 1.0µm in 0.1L of air. */
    uint16_t part_over_2_5um;   /**< Number of particles with diameter > 2.5µm in 0.1L of air. */
    uint16_t part_over_5_0um;   /**< Number of particles with diameter > 5.0µm in 0.1L of air. */
    uint16_t part_over_10um;    /**< Number of particles with diameter > 10µm in 0.1L of air. */
    uint16_t tvoc;              /**< TVOC output. */
    uint16_t eco2;              /**< Output in ppm CO2 equivalents. */
    float t_comp;               /**< Compensated temperature. */
    float rh_comp;              /**< Compensated humidity. */
    float t_raw;                /**< Uncompensated temperature. */
    float rh_raw;               /**< Uncompensated humidity. */
    uint32_t rs0;               /**< Gas sensor raw resistance value RSi. */
    uint32_t rs1;               /**< Gas sensor raw resistance value RSi. */
    uint32_t rs2;               /**< Gas sensor raw resistance value RSi. */
    uint32_t rs3;               /**< Gas sensor raw resistance value RSi. */
    uint8_t aqi;                /**< Air Quality Index according to UBA Classification of TVOC value. */
    uint8_t version;            /**< Firmware version. */
    uint8_t error_code;         /**< Error code. */

} apc1sensor_measurement_t;

/**
 * @brief APC1 Sensor Demo module type, ID and firmware version object.
 * @details Module type, ID and firmware version object definition of APC1 Sensor Demo driver.
 */
typedef struct
{
    uint8_t module_name[ 7 ];   /**< 6 bytes ASCII name and type + termination character.*/
    uint8_t serial_num[ 8 ];    /**< 8 bytes serial number.*/
    uint8_t fw_version[ 2 ];    /**< 2 bytes firmware version.*/

} apc1sensor_info_t;

/**
 * @brief APC1 Sensor Demo return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    APC1SENSOR_OK = 0,
    APC1SENSOR_ERROR = -1

} apc1sensor_return_value_t;

/*!
 * @addtogroup apc1sensor APC1 Sensor Demo Driver
 * @brief API for configuring and manipulating APC1 Sensor Demo driver.
 * @{
 */

/**
 * @brief APC1 Sensor configuration object setup function.
 * @details This function initializes demo configuration structure to initial
 * values.
 * @param[out] cfg : Demo configuration structure.
 * See #apc1sensor_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void apc1sensor_cfg_setup ( apc1sensor_cfg_t *cfg );

/**
 * @brief APC1 Sensor driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #apc1sensor_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #apc1sensor_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void apc1sensor_drv_interface_sel ( apc1sensor_cfg_t *cfg, apc1sensor_drv_t drv_sel );

/**
 * @brief APC1 Sensor initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this demo board.
 * @param[out] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @param[in] cfg : Demo configuration structure.
 * See #apc1sensor_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t apc1sensor_init ( apc1sensor_t *ctx, apc1sensor_cfg_t *cfg );

/**
 * @brief APC1 Sensor default configuration function.
 * @details This function executes a default configuration of APC1 Sensor
 * demo board.
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t apc1sensor_default_cfg ( apc1sensor_t *ctx );

/**
 * @brief APC1 Sensor set idle mode function.
 * @details This function sets the device to IDLE mode.
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t apc1sensor_set_idle_mode ( apc1sensor_t *ctx );

/**
 * @brief APC1 Sensor start measurement function.
 * @details This function starts measurement by setting the device to measurement mode.
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t apc1sensor_start_measurement ( apc1sensor_t *ctx );

/**
 * @brief APC1 Sensor sw reset function.
 * @details This function performs a device software reset (I2C only).
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t apc1sensor_sw_reset ( apc1sensor_t *ctx );

/**
 * @brief APC1 Sensor set meas mode function.
 * @details This function sets measurement mode to active or passive (UART only).
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Passive,
 *                   @li @c 1 - Active.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t apc1sensor_set_meas_mode ( apc1sensor_t *ctx, uint8_t mode );

/**
 * @brief APC1 Sensor request meas function.
 * @details This function requests measurement in passive measurement mode (UART only).
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t apc1sensor_request_meas ( apc1sensor_t *ctx );

/**
 * @brief APC1 Sensor read info function.
 * @details This function reads the device name, serial number, and firmware version.
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @param[out] info : Device info object.
 * See #apc1sensor_info_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t apc1sensor_read_info ( apc1sensor_t *ctx, apc1sensor_info_t *info );

/**
 * @brief APC1 Sensor read measurement function.
 * @details This function reads the measurement 64-bytes output structure data.
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @param[out] measurement : Measurement output object.
 * See #apc1sensor_measurement_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t apc1sensor_read_measurement ( apc1sensor_t *ctx, apc1sensor_measurement_t *measurement );

/**
 * @brief APC1 Sensor set opmode function.
 * @details This function sets the operation mode by setting the SET and RST pins state.
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @param[in] opmode : @li @c 0 - Normal,
 *                     @li @c 1 - Deep sleep,
 *                     @li @c 2 - Reset.
 * @return None.
 * @note None.
 */
void apc1sensor_set_opmode ( apc1sensor_t *ctx, uint8_t opmode );

/**
 * @brief APC1 Sensor reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void apc1sensor_reset_device ( apc1sensor_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // APC1SENSOR_H

/*! @} */ // apc1sensor

// ------------------------------------------------------------------------ END
