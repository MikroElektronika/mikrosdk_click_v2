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
 * @file environment5.h
 * @brief This file contains API for Environment 5 Click Driver.
 */

#ifndef ENVIRONMENT5_H
#define ENVIRONMENT5_H

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
 * @addtogroup environment5 Environment 5 Click Driver
 * @brief API for configuring and manipulating Environment 5 Click driver.
 * @{
 */

/**
 * @defgroup environment5_reg Environment 5 Registers List
 * @brief List of registers of Environment 5 Click driver.
 */

/**
 * @addtogroup environment5_reg
 * @{
 */

/**
 * @brief Environment 5 STC31-C commands list.
 * @details Specified STC31-C commands list of Environment 5 Click driver.
 */
#define ENVIRONMENT5_STC_CMD_DISABLE_CRC                0x3768
#define ENVIRONMENT5_STC_CMD_SET_MEAS_MODE_AND_BIN_GAS  0x3615
#define ENVIRONMENT5_STC_CMD_SET_REL_HUMIDITY           0x3624
#define ENVIRONMENT5_STC_CMD_SET_TEMPERATURE            0x361E
#define ENVIRONMENT5_STC_CMD_SET_PRESSURE               0x362F
#define ENVIRONMENT5_STC_CMD_MEAS_GAS_CONCENTRATION     0x3639
#define ENVIRONMENT5_STC_CMD_FORCED_RECALIB             0x3661
#define ENVIRONMENT5_STC_CMD_ENABLE_AUTO_SELF_CALIB     0x3FEF
#define ENVIRONMENT5_STC_CMD_DISABLE_AUTO_SELF_CALIB    0x3F6E
#define ENVIRONMENT5_STC_CMD_ENABLE_WEAK_FILTER         0x3FC8
#define ENVIRONMENT5_STC_CMD_DISABLE_WEAK_FILTER        0x3F49
#define ENVIRONMENT5_STC_CMD_ENABLE_STRONG_FILTER       0x3FD5
#define ENVIRONMENT5_STC_CMD_DISABLE_STRONG_FILTER      0x3F54
#define ENVIRONMENT5_STC_CMD_SELF_TEST                  0x365B
#define ENVIRONMENT5_STC_CMD_PREPARE_READ_STATE         0x3752
#define ENVIRONMENT5_STC_CMD_READ_STATE                 0xE133
#define ENVIRONMENT5_STC_CMD_WRITE_STATE                0xE133
#define ENVIRONMENT5_STC_CMD_APPLY_STATE                0x3650
#define ENVIRONMENT5_STC_CMD_READ_OFFSET_VALUE          0x370A
#define ENVIRONMENT5_STC_CMD_WRITE_OFFSET_VALUE         0x3608
#define ENVIRONMENT5_STC_CMD_ENTER_SLEEP_MODE           0x3677
#define ENVIRONMENT5_STC_CMD_READ_PRODUCT_ID_0          0x367C
#define ENVIRONMENT5_STC_CMD_READ_PRODUCT_ID_1          0xE102

/**
 * @brief Environment 5 SHT40 commands list.
 * @details Specified SHT40 commands list of Environment 5 Click driver.
 */
#define ENVIRONMENT5_SHT_CMD_MEAS_TH_HIGH_PREC          0xFD
#define ENVIRONMENT5_SHT_CMD_MEAS_TH_MED_PREC           0xF6
#define ENVIRONMENT5_SHT_CMD_MEAS_TH_LOW_PREC           0xE0
#define ENVIRONMENT5_SHT_CMD_READ_SERIAL_NUM            0x89
#define ENVIRONMENT5_SHT_CMD_SOFT_RESET                 0x94
#define ENVIRONMENT5_SHT_CMD_ACT_HEATER_200MW_1S        0x39
#define ENVIRONMENT5_SHT_CMD_ACT_HEATER_200MW_0_1S      0x32
#define ENVIRONMENT5_SHT_CMD_ACT_HEATER_110MW_1S        0x2F
#define ENVIRONMENT5_SHT_CMD_ACT_HEATER_110MW_0_1S      0x24
#define ENVIRONMENT5_SHT_CMD_ACT_HEATER_20MW_1S         0x1E
#define ENVIRONMENT5_SHT_CMD_ACT_HEATER_20MW_0_1S       0x15

/*! @} */ // environment5_reg

/**
 * @defgroup environment5_set Environment 5 Registers Settings
 * @brief Settings for registers of Environment 5 Click driver.
 */

/**
 * @addtogroup environment5_set
 * @{
 */

/**
 * @brief Environment 5 STC31-C measurement mode values.
 * @details Specified STC31-C measurement mode values of Environment 5 Click driver.
 */
#define ENVIRONMENT5_STC_MODE_LN_CO2_IN_N2_0_TO_100     0x0000
#define ENVIRONMENT5_STC_MODE_LN_CO2_IN_AIR_0_TO_100    0x0001
#define ENVIRONMENT5_STC_MODE_LN_CO2_IN_N2_0_TO_25      0x0002
#define ENVIRONMENT5_STC_MODE_LN_CO2_IN_AIR_0_TO_25     0x0003
#define ENVIRONMENT5_STC_MODE_LC_CO2_IN_N2_0_TO_100     0x0010
#define ENVIRONMENT5_STC_MODE_LC_CO2_IN_AIR_0_TO_100    0x0011
#define ENVIRONMENT5_STC_MODE_LC_CO2_IN_N2_0_TO_40      0x0012
#define ENVIRONMENT5_STC_MODE_LC_CO2_IN_AIR_0_TO_40     0x0013

/**
 * @brief Environment 5 STC31-C measurement calculation values.
 * @details Specified STC31-C measurement calculation values of Environment 5 Click driver.
 */
#define ENVIRONMENT5_STC_MAX_RH                         100.0
#define ENVIRONMENT5_STC_RH_DATA_RESOLUTION             65535.0
#define ENVIRONMENT5_STC_TEMP_DATA_RESOLUTION           200.0
#define ENVIRONMENT5_STC_MAX_CO2                        100.0
#define ENVIRONMENT5_STC_MIN_CO2                        0.0
#define ENVIRONMENT5_STC_CO2_DATA_RESOLUTION            32768.0
#define ENVIRONMENT5_STC_CO2_OFFSET                     16384.0

/**
 * @brief Environment 5 SHT40 temperature and humidity calculation values.
 * @details Specified SHT40 temperature and humidity calculation values of Environment 5 Click driver.
 */
#define ENVIRONMENT5_SHT_MAX_RH                         100.0
#define ENVIRONMENT5_SHT_MIN_RH                         0.0
#define ENVIRONMENT5_SHT_DATA_RESOLUTION                65535.0
#define ENVIRONMENT5_SHT_ABS_MIN_TEMP                   ( -45.0 )
#define ENVIRONMENT5_SHT_ABS_MAX_TEMP                   ( 130.0 )
#define ENVIRONMENT5_SHT_ABS_MIN_HUM                    ( -6.0 )
#define ENVIRONMENT5_SHT_ABS_MAX_HUM                    ( 119.0 )

/**
 * @brief Environment 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Environment 5 Click driver.
 */
#define ENVIRONMENT5_SHT_DEVICE_ADDRESS                 0x45
#define ENVIRONMENT5_STC_DEVICE_ADDRESS_0               0x29
#define ENVIRONMENT5_STC_DEVICE_ADDRESS_1               0x2A
#define ENVIRONMENT5_STC_DEVICE_ADDRESS                 ENVIRONMENT5_STC_DEVICE_ADDRESS_0

/*! @} */ // environment5_set

/**
 * @defgroup environment5_map Environment 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Environment 5 Click driver.
 */

/**
 * @addtogroup environment5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Environment 5 Click to the selected MikroBUS.
 */
#define ENVIRONMENT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // environment5_map
/*! @} */ // environment5

/**
 * @brief Environment 5 Click context object.
 * @details Context object definition of Environment 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    bool stc_crc_enabled;       /**< CRC enabled flag for STC31-C sensor. */

} environment5_t;

/**
 * @brief Environment 5 Click configuration object.
 * @details Configuration object definition of Environment 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} environment5_cfg_t;

/**
 * @brief Environment 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ENVIRONMENT5_OK = 0,
    ENVIRONMENT5_ERROR = -1

} environment5_return_value_t;

/*!
 * @addtogroup environment5 Environment 5 Click Driver
 * @brief API for configuring and manipulating Environment 5 Click driver.
 * @{
 */

/**
 * @brief Environment 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #environment5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void environment5_cfg_setup ( environment5_cfg_t *cfg );

/**
 * @brief Environment 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #environment5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment5_init ( environment5_t *ctx, environment5_cfg_t *cfg );

/**
 * @brief Environment 5 default configuration function.
 * @details This function executes a default configuration of Environment 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t environment5_default_cfg ( environment5_t *ctx );

/**
 * @brief Environment 5 enable device function.
 * @details This function enables device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void environment5_enable_device ( environment5_t *ctx );

/**
 * @brief Environment 5 disable device function.
 * @details This function disables device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void environment5_disable_device ( environment5_t *ctx );

/**
 * @brief Environment 5 stc send command function.
 * @details This function sends a command word to the STC31-C device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment5_stc_send_cmd ( environment5_t *ctx, uint16_t cmd );

/**
 * @brief Environment 5 stc send command with data function.
 * @details This function sends a command along with data to the STC31-C device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be sent.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment5_stc_send_cmd_data ( environment5_t *ctx, uint16_t cmd, uint16_t data_in );

/**
 * @brief Environment 5 stc read data function.
 * @details This function reads measurement data from the STC31-C device.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to store the read data.
 * @param[in] len : Number of registers to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment5_stc_read_data ( environment5_t *ctx, uint16_t *data_out, uint8_t len );

/**
 * @brief Environment 5 stc disable crc function.
 * @details This function disables the CRC feature on the STC31-C device.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment5_stc_disable_crc ( environment5_t *ctx );

/**
 * @brief Environment 5 stc read device id function.
 * @details This function reads the product and serial numbers of the STC31-C device.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[out] prod_num : Pointer to store the product number.
 * @param[out] serial_num_msb : Pointer to store the MSB part of the serial number.
 * @param[out] serial_num_lsb : Pointer to store the LSB part of the serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment5_stc_read_id ( environment5_t *ctx, uint32_t *prod_num, uint32_t *serial_num_msb, uint32_t *serial_num_lsb );

/**
 * @brief Environment 5 stc set temperature function.
 * @details This function sets the temperature compensation value on the STC31-C device.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[in] temperature : Temperature value in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment5_stc_set_temp ( environment5_t *ctx, float temperature );

/**
 * @brief Environment 5 stc set humidity function.
 * @details This function sets the relative humidity compensation value on the STC31-C device.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[in] humidity : Humidity value in percentage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment5_stc_set_hum ( environment5_t *ctx, float humidity );

/**
 * @brief Environment 5 stc set measurement mode function.
 * @details This function sets the measurement mode on the STC31-C device.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[in] mode : Measurement mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t environment5_stc_set_meas_mode ( environment5_t *ctx, uint16_t mode );

/**
 * @brief Environment 5 stc read measurement function.
 * @details This function reads gas concentration and temperature data from the STC31-C device.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[out] gas : Pointer to store CO2 gas concentration.
 * @param[out] temp : Pointer to store temperature in degrees Celsius (optional).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note When the environment5_stc_set_temp has not been used, the internal temperature value is read out.
 */
err_t environment5_stc_read_meas ( environment5_t *ctx, float *gas, float *temp );

/**
 * @brief Environment 5 sht send cmd function.
 * @details This function sends the selected command byte to SHT40 device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment5_sht_send_cmd ( environment5_t *ctx, uint8_t cmd );

/**
 * @brief Environment 5 sht read response function.
 * @details This function reads 6 response bytes from SHT40 device to the previously sent command
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[out] data_out : 6 response bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment5_sht_read_response ( environment5_t *ctx, uint8_t *data_out );

/**
 * @brief Environment 5 sht soft reset function.
 * @details This function performs the software reset by sending the soft reset command to SHT40 device.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment5_sht_soft_reset ( environment5_t *ctx );

/**
 * @brief Environment 5 sht read serial function.
 * @details This function reads the 4-bytes unique serial number from SHT40 device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[out] serial_num : 4-bytes unique serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment5_sht_read_serial ( environment5_t *ctx, uint32_t *serial_num );

/**
 * @brief Environment 5 sht read meas hp function.
 * @details This function reads the temperature and humidity measurements with high precision from SHT40 device.
 * @param[in] ctx : Click context object.
 * See #environment5_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @param[out] hum : Relative humidity in percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t environment5_sht_read_meas_hp ( environment5_t *ctx, float *temp, float *hum );

#ifdef __cplusplus
}
#endif
#endif // ENVIRONMENT5_H

/*! @} */ // environment5

// ------------------------------------------------------------------------ END
