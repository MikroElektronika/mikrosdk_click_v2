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
 * @file temphum27.h
 * @brief This file contains API for TempHum 27 Click Driver.
 */

#ifndef TEMPHUM27_H
#define TEMPHUM27_H

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

/*!
 * @addtogroup temphum27 TempHum 27 Click Driver
 * @brief API for configuring and manipulating TempHum 27 Click driver.
 * @{
 */

/**
 * @defgroup temphum27_reg TempHum 27 Registers List
 * @brief List of registers of TempHum 27 Click driver.
 */

/**
 * @addtogroup temphum27_reg
 * @{
 */

/**
 * @brief TempHum 27 commands list.
 * @details Specified commands list of TempHum 27 Click driver.
 */
#define TEMPHUM27_CMD_HOLD_TEMP_MEAS            0xE3
#define TEMPHUM27_CMD_NO_HOLD_TEMP_MEAS         0xF3
#define TEMPHUM27_CMD_HOLD_TEMP_HUM_MEAS        0xE5
#define TEMPHUM27_CMD_NO_HOLD_TEMP_HUM_MEAS     0xF5
#define TEMPHUM27_CMD_READ_REG                  0xA7
#define TEMPHUM27_CMD_WRITE_REG                 0xA6
#define TEMPHUM27_CMD_STOP_PERIODIC_MEAS        0x30
#define TEMPHUM27_CMD_READ_SENSOR_ID            0xD7

/**
 * @brief TempHum 27 registers list.
 * @details Specified registers list of TempHum 27 Click driver.
 */
#define TEMPHUM27_REG_MEAS_RESOLUTION           0x00
#define TEMPHUM27_REG_PERIODIC_CONFIG           0x02
#define TEMPHUM27_REG_ALERT_ENABLE              0x03
#define TEMPHUM27_REG_RST_THOLD_TEMP_H_LSB      0x05
#define TEMPHUM27_REG_RST_THOLD_TEMP_H_MSB      0x06
#define TEMPHUM27_REG_TRG_THOLD_TEMP_H_LSB      0x07
#define TEMPHUM27_REG_TRG_THOLD_TEMP_H_MSB      0x08
#define TEMPHUM27_REG_TRG_THOLD_TEMP_L_LSB      0x09
#define TEMPHUM27_REG_TRG_THOLD_TEMP_L_MSB      0x0A
#define TEMPHUM27_REG_RST_THOLD_TEMP_L_LSB      0x0B
#define TEMPHUM27_REG_RST_THOLD_TEMP_L_MSB      0x0C
#define TEMPHUM27_REG_RST_THOLD_HUM_H_LSB       0x0D
#define TEMPHUM27_REG_RST_THOLD_HUM_H_MSB       0x0E
#define TEMPHUM27_REG_TRG_THOLD_HUM_H_LSB       0x0F
#define TEMPHUM27_REG_TRG_THOLD_HUM_H_MSB       0x10
#define TEMPHUM27_REG_TRG_THOLD_HUM_L_LSB       0x11
#define TEMPHUM27_REG_TRG_THOLD_HUM_L_MSB       0x12
#define TEMPHUM27_REG_RST_THOLD_HUM_L_LSB       0x13
#define TEMPHUM27_REG_RST_THOLD_HUM_L_MSB       0x14

/*! @} */ // temphum27_reg

/**
 * @defgroup temphum27_set TempHum 27 Registers Settings
 * @brief Settings for registers of TempHum 27 Click driver.
 */

/**
 * @addtogroup temphum27_set
 * @{
 */

/**
 * @brief TempHum 27 periodic config register setting.
 * @details Specified periodic config register setting of TempHum 27 Click driver.
 */
#define TEMPHUM27_PERIODIC_CONFIG_ACTIVATE      0x80
#define TEMPHUM27_PERIODIC_CONFIG_FREQ_0_5S     0x00
#define TEMPHUM27_PERIODIC_CONFIG_FREQ_1S       0x10
#define TEMPHUM27_PERIODIC_CONFIG_FREQ_2_5S     0x20
#define TEMPHUM27_PERIODIC_CONFIG_FREQ_MASK     0x30
#define TEMPHUM27_PERIODIC_CONFIG_ALR_POL_LOW   0x00
#define TEMPHUM27_PERIODIC_CONFIG_ALR_POL_HIGH  0x01
#define TEMPHUM27_PERIODIC_CONFIG_ALR_POL_MASK  0x01

/**
 * @brief TempHum 27 periodic measurement frequency setting.
 * @details Specified periodic measurement frequency of TempHum 27 Click driver.
 */
#define TEMPHUM27_PERIODIC_FREQ_0_5S            0
#define TEMPHUM27_PERIODIC_FREQ_1S              1
#define TEMPHUM27_PERIODIC_FREQ_2_5S            2

/**
 * @brief TempHum 27 measurements conversion setting.
 * @details Specified measurements conversion of TempHum 27 Click driver.
 */
#define TEMPHUM27_DATA_RESOLUTION               0x3FFF
#define TEMPHUM27_TEMP_DATA_RES                 165
#define TEMPHUM27_TEMP_DATA_OFFSET              40
#define TEMPHUM27_HUM_DATA_RES                  100

/**
 * @brief TempHum 27 device address setting.
 * @details Specified setting for device slave address selection of
 * TempHum 27 Click driver.
 */
#define TEMPHUM27_DEVICE_ADDRESS                0x54

/*! @} */ // temphum27_set

/**
 * @defgroup temphum27_map TempHum 27 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 27 Click driver.
 */

/**
 * @addtogroup temphum27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 27 Click to the selected MikroBUS.
 */
#define TEMPHUM27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // temphum27_map
/*! @} */ // temphum27

/**
 * @brief TempHum 27 Click context object.
 * @details Context object definition of TempHum 27 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */

    // Input pins
    digital_in_t alr;           /**< Alert pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} temphum27_t;

/**
 * @brief TempHum 27 Click configuration object.
 * @details Configuration object definition of TempHum 27 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t alr;             /**< Alert pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} temphum27_cfg_t;

/**
 * @brief TempHum 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM27_OK = 0,
    TEMPHUM27_ERROR = -1

} temphum27_return_value_t;

/*!
 * @addtogroup temphum27 TempHum 27 Click Driver
 * @brief API for configuring and manipulating TempHum 27 Click driver.
 * @{
 */

/**
 * @brief TempHum 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum27_cfg_setup ( temphum27_cfg_t *cfg );

/**
 * @brief TempHum 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum27_init ( temphum27_t *ctx, temphum27_cfg_t *cfg );

/**
 * @brief TempHum 27 write register function.
 * @details This function writes a data byte to the selected register using I2C communication.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum27_write_reg ( temphum27_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief TempHum 27 read register function.
 * @details This function reads a byte of data from the selected register using I2C communication.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory where the read byte will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum27_read_reg ( temphum27_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief TempHum 27 read data (hold mode) function.
 * @details This function reads temperature and/or humidity in hold mode and converts to physical values.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @param[out] temp : Pointer to temperature in Celsius.
 * @param[out] hum : Pointer to relative humidity in percentage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note At least one output pointer (temp or hum) must be non-NULL.
 */
err_t temphum27_read_data_hold ( temphum27_t *ctx, float *temp, float *hum );

/**
 * @brief TempHum 27 read data (no hold mode) function.
 * @details This function performs a no-hold measurement and reads temperature and/or humidity.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @param[out] temp : Pointer to temperature in Celsius.
 * @param[out] hum : Pointer to relative humidity in percentage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note At least one output pointer (temp or hum) must be non-NULL.
 */
err_t temphum27_read_data_no_hold ( temphum27_t *ctx, float *temp, float *hum );

/**
 * @brief TempHum 27 start periodic measurement function.
 * @details This function configures and starts periodic measurement mode at the specified frequency.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @param[in] freq : Measurement frequency.
 *                   @li @c 0 - 0.5 seconds,
 *                   @li @c 1 - 1 second.
 *                   @li @c 2 - 2.5 seconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum27_start_periodic_meas ( temphum27_t *ctx, uint8_t freq );

/**
 * @brief TempHum 27 stop periodic measurement function.
 * @details This function stops any ongoing periodic measurement.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum27_stop_periodic_meas ( temphum27_t *ctx );

/**
 * @brief TempHum 27 read data in periodic mode function.
 * @details This function reads temperature and/or humidity data in periodic measurement mode.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @param[out] temp : Pointer to temperature in Celsius.
 * @param[out] hum : Pointer to relative humidity in percentage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note At least one output pointer (temp or hum) must be non-NULL, and alert feature must be disabled (default state).
 */
err_t temphum27_read_data_periodic ( temphum27_t *ctx, float *temp, float *hum );

/**
 * @brief TempHum 27 read data and alert in periodic mode function.
 * @details This function reads temperature, humidity, and alert status during periodic measurements.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @param[out] temp : Pointer to temperature in Celsius.
 * @param[out] hum : Pointer to relative humidity in percentage.
 * @param[out] alert : Pointer to alert flag byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note At least one output pointer (temp, hum, or alert) must be non-NULL, and alert feature must be enabled.
 */
err_t temphum27_read_data_periodic_al ( temphum27_t *ctx, float *temp, float *hum, uint8_t *alert );

/**
 * @brief TempHum 27 read sensor ID function.
 * @details This function reads the unique 32-bit sensor ID.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @param[out] sensor_id : Pointer to memory where sensor ID will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum27_read_sensor_id ( temphum27_t *ctx, uint32_t *sensor_id );

/**
 * @brief TempHum 27 enable device function.
 * @details This function sets the EN pin to high logic level to enable the device.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum27_enable_device ( temphum27_t *ctx );

/**
 * @brief TempHum 27 disable device function.
 * @details This function sets the EN pin to low logic level to disable the device.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum27_disable_device ( temphum27_t *ctx );

/**
 * @brief TempHum 27 reset device function.
 * @details This function performs a hardware reset by toggling the EN pin.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum27_reset_device ( temphum27_t *ctx );

/**
 * @brief TempHum 27 get alert pin function.
 * @details This function reads the logic level of the ALR (alert) pin.
 * @param[in] ctx : Click context object.
 * See #temphum27_t object definition for detailed explanation.
 * @return Pin logic level.
 * @note None.
 */
uint8_t temphum27_get_alert_pin ( temphum27_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM27_H

/*! @} */ // temphum27

// ------------------------------------------------------------------------ END
