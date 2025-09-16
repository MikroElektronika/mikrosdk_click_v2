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
 * @file temphum26.h
 * @brief This file contains API for TempHum 26 Click Driver.
 */

#ifndef TEMPHUM26_H
#define TEMPHUM26_H

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
 * @addtogroup temphum26 TempHum 26 Click Driver
 * @brief API for configuring and manipulating TempHum 26 Click driver.
 * @{
 */

/**
 * @defgroup temphum26_reg TempHum 26 Registers List
 * @brief List of registers of TempHum 26 Click driver.
 */

/**
 * @addtogroup temphum26_reg
 * @{
 */

/**
 * @brief TempHum 26 register map.
 * @details Specified register map of TempHum 26 Click driver.
 */
#define TEMPHUM26_REG_PART_ID                   0x00
#define TEMPHUM26_REG_DIE_REV                   0x02
#define TEMPHUM26_REG_UID                       0x04
#define TEMPHUM26_REG_SYS_CTRL                  0x10
#define TEMPHUM26_REG_SYS_STAT                  0x11
#define TEMPHUM26_REG_SENS_RUN                  0x21
#define TEMPHUM26_REG_SENS_START                0x22
#define TEMPHUM26_REG_SENS_STOP                 0x23
#define TEMPHUM26_REG_SENS_STAT                 0x24
#define TEMPHUM26_REG_T_VAL                     0x30
#define TEMPHUM26_REG_H_VAL                     0x33

/*! @} */ // temphum26_reg

/**
 * @defgroup temphum26_set TempHum 26 Registers Settings
 * @brief Settings for registers of TempHum 26 Click driver.
 */

/**
 * @addtogroup temphum26_set
 * @{
 */

/**
 * @brief TempHum 26 PART_ID register setting.
 * @details Specified setting for PART_ID register of TempHum 26 Click driver.
 */
#define TEMPHUM26_PART_ID                       0x0211

/**
 * @brief TempHum 26 SYS_CTRL register setting.
 * @details Specified setting for SYS_CTRL register of TempHum 26 Click driver.
 */
#define TEMPHUM26_SYS_CTRL_RESET                0x80
#define TEMPHUM26_SYS_CTRL_LOW_POWER_DISABLE    0x00
#define TEMPHUM26_SYS_CTRL_LOW_POWER_ENABLE     0x01

/**
 * @brief TempHum 26 SYS_STAT register setting.
 * @details Specified setting for SYS_STAT register of TempHum 26 Click driver.
 */
#define TEMPHUM26_SYS_STAT_STANDBY              0x00
#define TEMPHUM26_SYS_STAT_ACTIVE               0x01

/**
 * @brief TempHum 26 measurement mode setting.
 * @details Specified setting for measurement mode of TempHum 26 Click driver.
 */
#define TEMPHUM26_MODE_SINGLE_SHOT              0
#define TEMPHUM26_MODE_CONTINUOUS               1

/**
 * @brief TempHum 26 START/STOP measurement flag setting.
 * @details Specified setting for START/STOP measurement flag of TempHum 26 Click driver.
 */
#define TEMPHUM26_FLAG_TEMP_ONLY                0
#define TEMPHUM26_FLAG_HUM_ONLY                 1
#define TEMPHUM26_FLAG_TEMP_HUM                 2

/**
 * @brief TempHum 26 data measurement setting.
 * @details Specified setting for data measurement of TempHum 26 Click driver.
 */
#define TEMPHUM26_DATA_VALID_BIT                0x01
#define TEMPHUM26_NUM_MEASUREMENT_TRIES         10
#define TEMPHUM26_TEMPERATURE_RES               64
#define TEMPHUM26_TEMPERATURE_K_TO_C            273.15
#define TEMPHUM26_HUMIDITY_RES                  512

/**
 * @brief TempHum 26 device address setting.
 * @details Specified setting for device slave address selection of
 * TempHum 26 Click driver.
 */
#define TEMPHUM26_DEVICE_ADDRESS                0x44

/*! @} */ // temphum26_set

/**
 * @defgroup temphum26_map TempHum 26 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 26 Click driver.
 */

/**
 * @addtogroup temphum26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 26 Click to the selected MikroBUS.
 */
#define TEMPHUM26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // temphum26_map
/*! @} */ // temphum26

/**
 * @brief TempHum 26 Click info object.
 * @details Info object definition of TempHum 26 Click driver.
 */
typedef struct
{
    uint16_t part_id;           /**< Device part ID word. */
    uint16_t die_rev;           /**< Device DIE revision number word. */
    uint8_t uid[ 8 ];           /**< Device 8-bytes unique ID. */

} temphum26_info_t;

/**
 * @brief TempHum 26 Click context object.
 * @details Context object definition of TempHum 26 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    temphum26_info_t info;      /**< Device information. */

} temphum26_t;

/**
 * @brief TempHum 26 Click configuration object.
 * @details Configuration object definition of TempHum 26 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} temphum26_cfg_t;

/**
 * @brief TempHum 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM26_OK = 0,
    TEMPHUM26_ERROR = -1

} temphum26_return_value_t;

/*!
 * @addtogroup temphum26 TempHum 26 Click Driver
 * @brief API for configuring and manipulating TempHum 26 Click driver.
 * @{
 */

/**
 * @brief TempHum 26 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum26_cfg_setup ( temphum26_cfg_t *cfg );

/**
 * @brief TempHum 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum26_init ( temphum26_t *ctx, temphum26_cfg_t *cfg );

/**
 * @brief TempHum 26 default configuration function.
 * @details This function executes a default configuration of the TempHum 26 Click board.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function enables the device and sets measurement mode to single shot.
 */
err_t temphum26_default_cfg ( temphum26_t *ctx );

/**
 * @brief TempHum 26 write multiple registers function.
 * @details This function writes a sequence of bytes to consecutive registers starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to data to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_write_regs ( temphum26_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief TempHum 26 read multiple registers function.
 * @details This function reads a sequence of bytes from consecutive registers starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the memory where read data will be stored.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_read_regs ( temphum26_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief TempHum 26 write single register function.
 * @details This function writes a single byte to the specified register.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_write_reg ( temphum26_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief TempHum 26 read single register function.
 * @details This function reads one byte from the specified register.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory where read byte will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_read_reg ( temphum26_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief TempHum 26 enable device function.
 * @details This function sets the EN pin to high logic level to enable the device.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum26_enable_device ( temphum26_t *ctx );

/**
 * @brief TempHum 26 disable device function.
 * @details This function sets the EN pin to low logic level to disable the device.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum26_disable_device ( temphum26_t *ctx );

/**
 * @brief TempHum 26 check communication function.
 * @details This function verifies device identity and UID by reading the part ID and die revision
 * and checks whether they match expected values.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_check_communication ( temphum26_t *ctx );

/**
 * @brief TempHum 26 set active power mode function.
 * @details This function sets the device to active mode by clearing the low power enable bit and
 * verifying the system status register.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_power_mode_active ( temphum26_t *ctx );

/**
 * @brief TempHum 26 set standby power mode function.
 * @details This function sets the device to standby mode by enabling the low power mode and
 * verifying the system status register.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_power_mode_standby ( temphum26_t *ctx );

/**
 * @brief TempHum 26 set measurement mode function.
 * @details This function sets the measurement mode to either single shot or continuous based on the input argument.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @param[in] mode : Measurement mode.
 *                   @li @c 0 - Single shot
 *                   @li @c 1 - Continuous
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_set_measurement_mode ( temphum26_t *ctx, uint8_t mode );

/**
 * @brief TempHum 26 start measurement function.
 * @details This function starts the measurement for temperature, humidity, or both depending on the selected flag.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @param[in] flag : Measurement type flag.
 *                   @li @c 0 - Temperature
 *                   @li @c 1 - Humidity
 *                   @li @c 2 - Both
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_start_measurement ( temphum26_t *ctx, uint8_t flag );

/**
 * @brief TempHum 26 stop measurement function.
 * @details This function stops the measurement process based on the selected flag for temperature, humidity, or both.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @param[in] flag : Measurement type flag.
 *                   @li @c 0 - Temperature
 *                   @li @c 1 - Humidity
 *                   @li @c 2 - Both
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t temphum26_stop_measurement ( temphum26_t *ctx, uint8_t flag );

/**
 * @brief TempHum 26 read temperature and humidity function.
 * @details This function reads temperature and humidity data from the device with CRC check and data validity,
 * and converts the raw values to physical values in degrees Celsius and %RH.
 * @param[in] ctx : Click context object.
 * See #temphum26_t object definition for detailed explanation.
 * @param[out] temp : Pointer to memory where temperature in Celsius will be stored.
 * @param[out] hum : Pointer to memory where humidity in percentage will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Both pointers can be NULL if specific measurement is not needed.
 */
err_t temphum26_read_data ( temphum26_t *ctx, float *temp, float *hum );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM26_H

/*! @} */ // temphum26

// ------------------------------------------------------------------------ END
