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
 * @file temphum24.h
 * @brief This file contains API for TempHum 24 Click Driver.
 */

#ifndef TEMPHUM24_H
#define TEMPHUM24_H

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
 * @addtogroup temphum24 TempHum 24 Click Driver
 * @brief API for configuring and manipulating TempHum 24 Click driver.
 * @{
 */

/**
 * @defgroup temphum24_cmd TempHum 24 Commands List
 * @brief List of commands of TempHum 24 Click driver.
 */

/**
 * @addtogroup temphum24_cmd
 * @{
 */

/**
 * @brief TempHum 24 commands list.
 * @details Specified commands list of TempHum 24 Click driver.
 */
#define TEMPHUM24_CMD_TRG_OD_LP0                    0x2400u
#define TEMPHUM24_CMD_TRG_OD_LP1                    0x240Bu
#define TEMPHUM24_CMD_TRG_OD_LP2                    0x2416u
#define TEMPHUM24_CMD_TRG_OD_LP3                    0x24FFu
#define TEMPHUM24_CMD_AUTO_MEAS_HALF_HZ_LP0         0x2032u
#define TEMPHUM24_CMD_AUTO_MEAS_HALF_HZ_LP1         0x2024u
#define TEMPHUM24_CMD_AUTO_MEAS_HALF_HZ_LP2         0x202Fu
#define TEMPHUM24_CMD_AUTO_MEAS_HALF_HZ_LP3         0x20FFu
#define TEMPHUM24_CMD_AUTO_MEAS_1_HZ_LP0            0x2130u
#define TEMPHUM24_CMD_AUTO_MEAS_1_HZ_LP1            0x2126u
#define TEMPHUM24_CMD_AUTO_MEAS_1_HZ_LP2            0x212Du
#define TEMPHUM24_CMD_AUTO_MEAS_1_HZ_LP3            0x21FFu
#define TEMPHUM24_CMD_AUTO_MEAS_2_HZ_LP0            0x2236u
#define TEMPHUM24_CMD_AUTO_MEAS_2_HZ_LP1            0x2220u
#define TEMPHUM24_CMD_AUTO_MEAS_2_HZ_LP2            0x222Bu
#define TEMPHUM24_CMD_AUTO_MEAS_2_HZ_LP3            0x22FFu
#define TEMPHUM24_CMD_AUTO_MEAS_4_HZ_LP0            0x2334u
#define TEMPHUM24_CMD_AUTO_MEAS_4_HZ_LP1            0x2322u
#define TEMPHUM24_CMD_AUTO_MEAS_4_HZ_LP2            0x2329u
#define TEMPHUM24_CMD_AUTO_MEAS_4_HZ_LP3            0x23FFu
#define TEMPHUM24_CMD_AUTO_MEAS_10_HZ_LP0           0x2737u
#define TEMPHUM24_CMD_AUTO_MEAS_10_HZ_LP1           0x2721u
#define TEMPHUM24_CMD_AUTO_MEAS_10_HZ_LP2           0x272Au
#define TEMPHUM24_CMD_AUTO_MEAS_10_HZ_LP3           0x27FFu
#define TEMPHUM24_CMD_AUTO_MEAS_EXIT                0x3093u
#define TEMPHUM24_CMD_AUTO_MEAS_ROUT_T_RH           0xE000u
#define TEMPHUM24_CMD_AUTO_MEAS_MIN_T               0xE002u
#define TEMPHUM24_CMD_AUTO_MEAS_MAX_T               0xE003u
#define TEMPHUM24_CMD_AUTO_MEAS_MIN_RH              0xE004u
#define TEMPHUM24_CMD_AUTO_MEAS_MAX_RH              0xE005u
#define TEMPHUM24_CMD_PROGRAM_SET_LOW_ALERT         0x6100u
#define TEMPHUM24_CMD_PROGRAM_SET_HIGH_ALERT        0x611Du
#define TEMPHUM24_CMD_PROGRAM_CLEAR_LOW_ALERT       0x610Bu
#define TEMPHUM24_CMD_PROGRAM_CLEAR_HIGH_ALERT      0x6116u
#define TEMPHUM24_CMD_TRANSFER_ALERT_THOLDS_TO_NVM  0x6155u
#define TEMPHUM24_CMD_READ_SET_LOW_ALERT            0xE102u
#define TEMPHUM24_CMD_READ_SET_HIGH_ALERT           0xE11Fu
#define TEMPHUM24_CMD_READ_CLEAR_LOW_ALERT          0xE109u
#define TEMPHUM24_CMD_READ_CLEAR_HIGH_ALERT         0xE114u
#define TEMPHUM24_CMD_INT_HEATER_ENABLE             0x306Du
#define TEMPHUM24_CMD_INT_HEATER_DISABLE            0x3066u
#define TEMPHUM24_CMD_INT_HEATER_CONFIGURE          0x306Eu
#define TEMPHUM24_CMD_STATUS_READ                   0xF32Du
#define TEMPHUM24_CMD_STATUS_CLEAR                  0x3041u
#define TEMPHUM24_CMD_NVM_T_RH_OFFSET               0xA004u
#define TEMPHUM24_CMD_SOFT_RESET                    0x30A2u
#define TEMPHUM24_CMD_READ_NIST_ID_BYTES_5_4        0x3683u
#define TEMPHUM24_CMD_READ_NIST_ID_BYTES_3_2        0x3684u
#define TEMPHUM24_CMD_READ_NIST_ID_BYTES_1_0        0x3685u
#define TEMPHUM24_CMD_READ_MANUFACTURER_ID          0x3781u
#define TEMPHUM24_CMD_OVERRIDE_DEFAULT              0x61BBu

/*! @} */ // temphum24_cmd

/**
 * @defgroup temphum24_set TempHum 24 Registers Settings
 * @brief Settings for registers of TempHum 24 Click driver.
 */

/**
 * @addtogroup temphum24_set
 * @{
 */

/**
 * @brief TempHum 24 manufacturer ID value.
 * @details Specified manufacturer ID value of TempHum 24 Click driver.
 */
#define TEMPHUM24_MANUFACTURER_ID                   0x3000u

/**
 * @brief TempHum 24 temperature and humidity calculation values.
 * @details Specified temperature and humidity calculation values of TempHum 24 Click driver.
 */
#define TEMPHUM24_TEMP_MIN                          ( -45.0f )
#define TEMPHUM24_TEMP_MAX                          ( 130.0f )
#define TEMPHUM24_HUM_MIN                           ( 0.0f )
#define TEMPHUM24_HUM_MAX                           ( 100.0f )
#define TEMPHUM24_DATA_RESOLUTION                   0xFFFFu

/**
 * @brief TempHum 24 device address setting.
 * @details Specified setting for device slave address selection of
 * TempHum 24 Click driver.
 */
#define TEMPHUM24_DEVICE_ADDRESS_A1A0_00            0x44
#define TEMPHUM24_DEVICE_ADDRESS_A1A0_01            0x45
#define TEMPHUM24_DEVICE_ADDRESS_A1A0_10            0x46
#define TEMPHUM24_DEVICE_ADDRESS_A1A0_11            0x47

/*! @} */ // temphum24_set

/**
 * @defgroup temphum24_map TempHum 24 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 24 Click driver.
 */

/**
 * @addtogroup temphum24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 24 Click to the selected MikroBUS.
 */
#define TEMPHUM24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // temphum24_map
/*! @} */ // temphum24

/**
 * @brief TempHum 24 Click context object.
 * @details Context object definition of TempHum 24 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active low). */

    // Input pins
    digital_in_t alert;         /**< Alert pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} temphum24_t;

/**
 * @brief TempHum 24 Click configuration object.
 * @details Configuration object definition of TempHum 24 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t alert;           /**< Alert pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} temphum24_cfg_t;

/**
 * @brief TempHum 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM24_OK = 0,
    TEMPHUM24_ERROR = -1

} temphum24_return_value_t;

/*!
 * @addtogroup temphum24 TempHum 24 Click Driver
 * @brief API for configuring and manipulating TempHum 24 Click driver.
 * @{
 */

/**
 * @brief TempHum 24 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum24_cfg_setup ( temphum24_cfg_t *cfg );

/**
 * @brief TempHum 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum24_init ( temphum24_t *ctx, temphum24_cfg_t *cfg );

/**
 * @brief TempHum 24 default configuration function.
 * @details This function executes a default configuration of TempHum 24
 * click board.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t temphum24_default_cfg ( temphum24_t *ctx );

/**
 * @brief TempHum 24 write cmd function.
 * @details This function writes the selected command word by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum24_write_cmd ( temphum24_t *ctx, uint16_t cmd );

/**
 * @brief TempHum 24 write cmd config function.
 * @details This function writes a desired config to the selected command word by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[in] cmd : Command word to configure.
 * @param[in] config : Command config to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum24_write_cmd_config ( temphum24_t *ctx, uint16_t cmd, uint16_t config );

/**
 * @brief TempHum 24 read single function.
 * @details This function reads a single data word from the device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[out] data_out : Output read word data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function must follow the write command sequence that initiates the data acquisition.
 */
err_t temphum24_read_single ( temphum24_t *ctx, uint16_t *data_out );

/**
 * @brief TempHum 24 read multi function.
 * @details This function reads two data words from the device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[out] data1_out : Output read word data 1.
 * @param[out] data2_out : Output read word data 2.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function must follow the write command sequence that initiates the data acquisition.
 */
err_t temphum24_read_multi ( temphum24_t *ctx, uint16_t *data1_out, uint16_t *data2_out );

/**
 * @brief TempHum 24 write then read single function.
 * @details This function write command word then reads a single data word from the device
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be written.
 * @param[out] data_out : Output read word data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function must follow the write command sequence that initiates the data acquisition.
 */
err_t temphum24_write_then_read_single ( temphum24_t *ctx, uint16_t cmd, uint16_t *data_out );

/**
 * @brief TempHum 24 write then read multi function.
 * @details This function writes command word then reads two data words from the device
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be written.
 * @param[out] data1_out : Output read word data 1.
 * @param[out] data2_out : Output read word data 2.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum24_write_then_read_multi ( temphum24_t *ctx, uint16_t cmd, uint16_t *data1_out, uint16_t *data2_out );

/**
 * @brief TempHum 24 enable device function.
 * @details This function enables device by setting the rst pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum24_enable_device ( temphum24_t *ctx );

/**
 * @brief TempHum 24 disable device function.
 * @details This function disables device by setting the rst pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum24_disable_device ( temphum24_t *ctx );

/**
 * @brief TempHum 24 reset device function.
 * @details This function resets device by toggling the rst pin state.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum24_reset_device ( temphum24_t *ctx );

/**
 * @brief TempHum 24 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t temphum24_get_alert_pin ( temphum24_t *ctx );

/**
 * @brief TempHum 24 check communication function.
 * @details This function checks the communication by reading and verifying the manufacturer ID.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum24_check_communication ( temphum24_t *ctx );

/**
 * @brief TempHum 24 read temp and rh function.
 * @details This function reads the temperature in celsius and the relative humidity
 * level in percents.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[out] temp : Temperature measurements in celsius.
 * @param[out] hum : Humidity measurements in percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The device must be set in auto measurements mode. 
 * For that you can call the temphum24_start_measurement function.
 */
err_t temphum24_read_temp_and_rh ( temphum24_t *ctx, float *temp, float *hum );

/**
 * @brief TempHum 24 read temp history function.
 * @details This function reads the temperature minimum and maximum values since the beginning
 * of measurements.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[out] temp_min : Minimum temperature value in celsius.
 * @param[out] temp_max : Maximum temperature value in celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The device must be set in auto measurements mode. 
 * For that you can call the temphum24_start_measurement function.
 */
err_t temphum24_read_temp_history ( temphum24_t *ctx, float *temp_min, float *temp_max );

/**
 * @brief TempHum 24 read rh history function.
 * @details This function reads the relative humidity minimum and maximum values since the beginning
 * of measurements.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[out] hum_min : Minimum relative humidity level in percents.
 * @param[out] hum_max : Maximum relative humidity level in percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The device must be set in auto measurements mode. 
 * For that you can call the temphum24_start_measurement function.
 */
err_t temphum24_read_rh_history ( temphum24_t *ctx, float *hum_min, float *hum_max );

/**
 * @brief TempHum 24 start measurement function.
 * @details This function starts the auto measurement with 1 Hz rate and default low power mode.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum24_start_measurement ( temphum24_t *ctx );

/**
 * @brief TempHum 24 stop measurement function.
 * @details This function exits the auto measurement mode and returns to sleep mode.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum24_stop_measurement ( temphum24_t *ctx );

/**
 * @brief TempHum 24 read serial number function.
 * @details This function reads the serial number/NIST ID.
 * @param[in] ctx : Click context object.
 * See #temphum24_t object definition for detailed explanation.
 * @param[out] serial_number : Pointer to the memory location where serial number value be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum24_get_serial_number ( temphum24_t *ctx, uint16_t *serial_number );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM24_H

/*! @} */ // temphum24

// ------------------------------------------------------------------------ END
