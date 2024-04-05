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
 * @file environment4.h
 * @brief This file contains API for Environment 4 Click Driver.
 */

#ifndef ENVIRONMENT4_H
#define ENVIRONMENT4_H

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
 * @addtogroup environment4 Environment 4 Click Driver
 * @brief API for configuring and manipulating Environment 4 Click driver.
 * @{
 */

/**
 * @defgroup environment4_reg Environment 4 Registers List
 * @brief List of registers of Environment 4 Click driver.
 */

/**
 * @addtogroup environment4_reg
 * @{
 */

/**
 * @brief Environment 4 SGP41 commands list.
 * @details Specified SGP41 commands list of Environment 4 Click driver.
 */
#define ENVIRONMENT4_SGP_CMD_EXE_CONDITIONING       0x2612u
#define ENVIRONMENT4_SGP_CMD_MEAS_RAW_SIGNALS       0x2619u
#define ENVIRONMENT4_SGP_CMD_EXE_SELF_TEST          0x280Eu
#define ENVIRONMENT4_SGP_TURN_HEATER_OFF            0x3615u
#define ENVIRONMENT4_SGP_GET_SERIAL_NUMBER          0x3682u

/**
 * @brief Environment 4 SHT41A commands list.
 * @details Specified SHT41A commands list of Environment 4 Click driver.
 */
#define ENVIRONMENT4_SHT_CMD_MEAS_TH_HIGH_PREC      0xFD
#define ENVIRONMENT4_SHT_CMD_MEAS_TH_MED_PREC       0xF6
#define ENVIRONMENT4_SHT_CMD_MEAS_TH_LOW_PREC       0xE0
#define ENVIRONMENT4_SHT_CMD_READ_SERIAL_NUM        0x89
#define ENVIRONMENT4_SHT_CMD_SOFT_RESET             0x94
#define ENVIRONMENT4_SHT_CMD_ACT_HEATER_200mW_1S    0x39
#define ENVIRONMENT4_SHT_CMD_ACT_HEATER_200mW_0p1S  0x32
#define ENVIRONMENT4_SHT_CMD_ACT_HEATER_110mW_1S    0x2F
#define ENVIRONMENT4_SHT_CMD_ACT_HEATER_110mW_0p1S  0x24
#define ENVIRONMENT4_SHT_CMD_ACT_HEATER_20mW_1S     0x1E
#define ENVIRONMENT4_SHT_CMD_ACT_HEATER_20mW_0p1S   0x15

/*! @} */ // environment4_reg

/**
 * @defgroup environment4_set Environment 4 Registers Settings
 * @brief Settings for registers of Environment 4 Click driver.
 */

/**
 * @addtogroup environment4_set
 * @{
 */

/**
 * @brief Environment 4 SGP41 self test bit values.
 * @details Specified SGP41 self test bit values of Environment 4 Click driver.
 */
#define ENVIRONMENT4_SGP_SELF_TEST_OK               0x00
#define ENVIRONMENT4_SGP_SELF_TEST_VOC_PIXEL        0x01
#define ENVIRONMENT4_SGP_SELF_TEST_NOX_PIXEL        0x02
#define ENVIRONMENT4_SGP_SELF_TEST_MASK             0x03

/**
 * @brief Environment 4 SHT41A temperature and humidity calculation values.
 * @details Specified SHT41A temperature and humidity calculation values of Environment 4 Click driver.
 */
#define ENVIRONMENT4_SHT_MAX_RH                     100.0
#define ENVIRONMENT4_SHT_MIN_RH                     0.0
#define ENVIRONMENT4_SHT_DATA_RESOLUTION            65535.0
#define ENVIRONMENT4_SHT_ABS_MIN_TEMP               ( -45.0 )
#define ENVIRONMENT4_SHT_ABS_MAX_TEMP               ( 130.0 )
#define ENVIRONMENT4_SHT_ABS_MIN_HUM                ( -6.0 )
#define ENVIRONMENT4_SHT_ABS_MAX_HUM                ( 119.0 )

/**
 * @brief Environment 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Environment 4 Click driver.
 */
#define ENVIRONMENT4_SHT_DEVICE_ADDRESS             0x44
#define ENVIRONMENT4_SGP_DEVICE_ADDRESS             0x59

/*! @} */ // environment4_set

/**
 * @defgroup environment4_map Environment 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Environment 4 Click driver.
 */

/**
 * @addtogroup environment4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Environment 4 Click to the selected MikroBUS.
 */
#define ENVIRONMENT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // environment4_map
/*! @} */ // environment4

/**
 * @brief Environment 4 Click context object.
 * @details Context object definition of Environment 4 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} environment4_t;

/**
 * @brief Environment 4 Click configuration object.
 * @details Configuration object definition of Environment 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} environment4_cfg_t;

/**
 * @brief Environment 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ENVIRONMENT4_OK = 0,
    ENVIRONMENT4_ERROR = -1

} environment4_return_value_t;

/*!
 * @addtogroup environment4 Environment 4 Click Driver
 * @brief API for configuring and manipulating Environment 4 Click driver.
 * @{
 */

/**
 * @brief Environment 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #environment4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void environment4_cfg_setup ( environment4_cfg_t *cfg );

/**
 * @brief Environment 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #environment4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_init ( environment4_t *ctx, environment4_cfg_t *cfg );

/**
 * @brief Environment 4 sgp exe conditioning function.
 * @details This function executes conditioning command for SGP41 device by using I2C serial interface.
 * It starts the conditioning, i.e., the VOC pixel will be operated at the same temperature as it is by calling
 * the environment4_sgp_meas_raw_signals function while the NOx pixel will be operated at
 * a different temperature for conditioning. This command returns only the measured raw signal of the VOC pixel
 * SRAW_VOC as 2 bytes.
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @param[in] comp_rh : Leaves humidity compensation disabled by sending the default value 0x8000 (50%RH) or
 * enabled humidity compensation when sending the relative humidity in ticks (ticks = %RH * 65535 / 100)
 * @param[in] comp_t : Leaves humidity compensation disabled by sending the default value 0x6666 (25 degC) or
 * enabled humidity compensation when sending the temperature in ticks (ticks = (degC + 45) * 65535 / 175)
 * @param[out] sraw_voc : u16 unsigned integer directly provides the raw signal SRAW_VOC in ticks which is proportional
 * to the logarithm of the resistance of the sensing element.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sgp_exe_conditioning ( environment4_t *ctx, uint16_t comp_rh, uint16_t comp_t, 
                                          uint16_t *sraw_voc );

/**
 * @brief Environment 4 sgp meas raw signals function.
 * @details This function measures raw signals for SGP41 device by using I2C serial interface.
 * It starts/continues the VOC + NOx measurement mode.
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @param[in] comp_rh : Leaves humidity compensation disabled by sending the default value 0x8000 (50%RH) or
 * enabled humidity compensation when sending the relative humidity in ticks (ticks = %RH * 65535 / 100)
 * @param[in] comp_t : Leaves humidity compensation disabled by sending the default value 0x6666 (25 degC) or
 * enabled humidity compensation when sending the temperature in ticks (ticks = (degC + 45) * 65535 / 175)
 * @param[out] sraw_voc : u16 unsigned integer directly provides the raw signal SRAW_VOC in ticks which is proportional
 * to the logarithm of the resistance of the sensing element.
 * @param[out] sraw_nox : u16 unsigned integer directly provides the raw signal SRAW_NOX in ticks which is proportional
 * to the logarithm of the resistance of the sensing element.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sgp_meas_raw_signals ( environment4_t *ctx, uint16_t comp_rh, uint16_t comp_t, 
                                          uint16_t *sraw_voc, uint16_t *sraw_nox );

/**
 * @brief Environment 4 sgp exe self test function.
 * @details This function triggers the SGP41 device built-in self-test checking for integrity of both hotplate and MOX material
 * and returns the result of this test as 1 byte (only 2 least significant bits are valid).
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @param[out] test_result : @li @c 0 - OK,
 *                           @li @c 1 - VOC pixel fail,
 *                           @li @c 2 - NOx pixel fail,
 *                           @li @c 3 - Both VOC and NOx pixels fail.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sgp_exe_self_test ( environment4_t *ctx, uint8_t *test_result );

/**
 * @brief Environment 4 sgp turn heater off function.
 * @details This function turns the hotplate off and stops the measurement for the SGP41 device.
 * Subsequently, the sensor enters the idle mode.
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sgp_turn_heater_off ( environment4_t *ctx );

/**
 * @brief Environment 4 sgp get serial num function.
 * @details This function provides the decimal serial number of the SGP41 chip by returning 3x2 bytes.
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @param[out] serial_num : 48-bit unique serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sgp_get_serial_num ( environment4_t *ctx, uint16_t *serial_num );

/**
 * @brief Environment 4 sht send cmd function.
 * @details This function sends the selected command byte to SHT41A device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sht_send_cmd ( environment4_t *ctx, uint8_t cmd );

/**
 * @brief Environment 4 sht read response function.
 * @details This function reads 6 response bytes from SHT41A device to the previously sent command
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @param[out] data_out : 6 response bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sht_read_response ( environment4_t *ctx, uint8_t *data_out );

/**
 * @brief Environment 4 sht soft reset function.
 * @details This function performs the software reset by sending the soft reset command to SHT41A device.
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sht_soft_reset ( environment4_t *ctx );

/**
 * @brief Environment 4 sht read serial num function.
 * @details This function reads the 4-bytes unique serial number from SHT41A device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @param[out] serial_num : 4-bytes unique serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sht_read_serial_num ( environment4_t *ctx, uint32_t *serial_num );

/**
 * @brief Environment 4 sht read meas hp function.
 * @details This function reads the temperature and humidity measurements with high precision from SHT41A device.
 * @param[in] ctx : Click context object.
 * See #environment4_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @param[out] hum : Relative humidity in percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment4_sht_read_meas_hp ( environment4_t *ctx, float *temp, float *hum );

#ifdef __cplusplus
}
#endif
#endif // ENVIRONMENT4_H

/*! @} */ // environment4

// ------------------------------------------------------------------------ END
