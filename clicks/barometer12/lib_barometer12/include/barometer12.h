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
 * @file barometer12.h
 * @brief This file contains API for Barometer 12 Click Driver.
 */

#ifndef BAROMETER12_H
#define BAROMETER12_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup barometer12 Barometer 12 Click Driver
 * @brief API for configuring and manipulating Barometer 12 Click driver.
 * @{
 */

/**
 * @defgroup barometer12_set Barometer 12 Registers Settings
 * @brief Settings for registers of Barometer 12 Click driver.
 */

/**
 * @addtogroup barometer12_set
 * @{
 */

/**
 * @brief Barometer 12 description setting.
 * @details Specified setting for description of Barometer 12 Click driver.
 */

/**
 * @brief Barometer 12 description command.
 * @details Specified command for description of Barometer 12 Click driver.
 */
#define BAROMETER12_CMD_OP_MODE_T_FIRST_LOW_POWER           0x609C
#define BAROMETER12_CMD_OP_MODE_T_FIRST_NORMAL              0x6825
#define BAROMETER12_CMD_OP_MODE_T_FIRST_LOW_NOISE           0x70DF
#define BAROMETER12_CMD_OP_MODE_T_FIRST_ULTRA_LOW_NOISE     0x7866
#define BAROMETER12_CMD_OP_MODE_P_FIRST_LOW_POWER           0x401A
#define BAROMETER12_CMD_OP_MODE_P_FIRST_NORMAL              0x48A3
#define BAROMETER12_CMD_OP_MODE_P_FIRST_LOW_NOISE           0x5059
#define BAROMETER12_CMD_OP_MODE_P_FIRST_ULTRA_LOW_NOISE     0x58E0
#define BAROMETER12_CMD_SOFT_RESET                          0x805D
#define BAROMETER12_CMD_DEVICE_ID                           0xEFC8
#define BAROMETER12_CMD_READ_OTP                            0xC7F7
#define BAROMETER12_CMD_OTP_READ_ADDRESS_REG                0xC595
#define BAROMETER12_CMD_OTP_READ_ADDRESS_PARAM              0x0066

/**
 * @brief Barometer 12 calculation setting.
 * @details Specified calculation for description of Barometer 12 Click driver.
 */
#define BAROMETER12_P_PA_CALIB_0                            45000.0f
#define BAROMETER12_P_PA_CALIB_1                            80000.0f
#define BAROMETER12_P_PA_CALIB_2                            96700.0f
#define BAROMETER12_LUT_LOWER                               3670016.0f
#define BAROMETER12_LUT_UPPER                               12058624.0f
#define BAROMETER12_QUADR_FACTOR                            5.960464477539063e-8f
#define BAROMETER12_OFFSET_FACTOR                           2048.0f
#define BAROMETER12_TEMPERATURE_COEF_1                      45.0f
#define BAROMETER12_TEMPERATURE_COEF_2                      175.0f
#define BAROMETER12_TEMPERATURE_COEF_3                      65536.0f

/**
 * @brief Barometer 12 description setting.
 * @details Specified setting for description of Barometer 12 Click driver.
 */
#define BAROMETER12_OP_MODE_LOW_POWER                       0
#define BAROMETER12_OP_MODE_NORMAL                          1
#define BAROMETER12_OP_MODE_LOW_NOISE                       2
#define BAROMETER12_OP_MODE_ULTRA_LOW_NOISE                 3

/**
 * @brief Barometer 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Barometer 12 Click driver.
 */
#define BAROMETER12_DEVICE_ADDRESS                          0x63

/*! @} */ // barometer12_set

/**
 * @defgroup barometer12_map Barometer 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Barometer 12 Click driver.
 */

/**
 * @addtogroup barometer12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Barometer 12 Click to the selected MikroBUS.
 */
#define BAROMETER12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // barometer12_map
/*! @} */ // barometer12

/**
 * @brief Barometer 12 Click context object.
 * @details Context object definition of Barometer 12 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} barometer12_t;

/**
 * @brief Barometer 12 Click configuration object.
 * @details Configuration object definition of Barometer 12 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} barometer12_cfg_t;

/**
 * @brief Barometer 12 Click structure to hold pressure sensor 
 * related parameters object.
 * @details Structure to hold pressure sensor 
 * related parameters object definition of Barometer 12 Click driver.
 */
typedef struct 
{
    uint16_t op_mode;               /**< Operation mode. */
    float sensor_constants[ 4 ];    /**< Sensor constants. */
    float p_pa_calib[ 3 ];          /**< Pressure calibration coefficient. */
    float lut_lower;                /**< LUT lower data. */
    float lut_upper;                /**< LUT upper data. */
    float quadr_factor;             /**< Quadr factor data. */
    float offst_factor;             /**< Offset factor. */
    
} barometer12_invpres_t;

/**
 * @brief Barometer 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BAROMETER12_OK = 0,
    BAROMETER12_ERROR = -1

} barometer12_return_value_t;

/*!
 * @addtogroup barometer12 Barometer 12 Click Driver
 * @brief API for configuring and manipulating Barometer 12 Click driver.
 * @{
 */

/**
 * @brief Barometer 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #barometer12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void barometer12_cfg_setup ( barometer12_cfg_t *cfg );

/**
 * @brief Barometer 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #barometer12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_init ( barometer12_t *ctx, barometer12_cfg_t *cfg );

/**
 * @brief Barometer 12 default configuration function.
 * @details This function executes a default configuration of Barometer 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t barometer12_default_cfg ( barometer12_t *ctx );

/**
 * @brief Barometer 12 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_generic_write ( barometer12_t *ctx, uint16_t cmd, uint16_t *data_in, uint8_t len );

/**
 * @brief Barometer 12 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_generic_read ( barometer12_t *ctx, uint16_t cmd, uint16_t *data_out, uint8_t len );

/**
 * @brief Barometer 12 set command function.
 * @details This function sets desired command of the Barometer 12 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_set_command ( barometer12_t *ctx, uint16_t cmd ) ;

/**
 * @brief Barometer 12 software reset function.
 * @details This function performs a software reset of the Barometer 12 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_soft_reset ( barometer12_t *ctx );

/**
 * @brief Barometer 12 get device ID function.
 * @details This function read device ID of the Barometer 12 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @param[out] device_id : Device ID value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_get_device_id ( barometer12_t *ctx, uint16_t *device_id );

/**
 * @brief Barometer 12 set up OTP read function.
 * @details This function performs a OTP read mode of the Barometer 12 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_set_up_otp_read ( barometer12_t *ctx );

/**
 * @brief Barometer 12 get OTP function.
 * @details This function read OTP values of the Barometer 12 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @param[out] otp_data : OTP values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_get_otp ( barometer12_t *ctx, uint16_t *otp_data );

/**
 * @brief Barometer 12 inverse process data function.
 * @details This function performs a inverse process data of the Barometer 12 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @param[in] cfg_data : Data structure to hold pressure sensor related parameters.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_inv_invpres_calib ( barometer12_t *ctx, barometer12_invpres_t *cfg_data );

/**
 * @brief Barometer 12 get RAW data function.
 * @details This function read RAW data of the Barometer 12 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @param[in] measurement_comd : Operation mode measurement commands.
 * @param[out] pressure : RAW pressure data.
 * @param[out] temperature : RAW temperature data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_get_raw_data ( barometer12_t *ctx, uint16_t measurement_comd, uint32_t *pressure, uint16_t *temperature );

/**
 * @brief Barometer 12 get pressure and temperature function.
 * @details This function read pressure ( Pa ) and temperature ( degree Celsius ) of 
 * the Barometer 12 click board™. 
 * @param[in] ctx : Click context object.
 * See #barometer12_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data ( Pa ).
 * @param[out] temperature : Temperature data ( degree Celsius ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t barometer12_get_press_and_temp ( barometer12_t *ctx,  float *pressure, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // BAROMETER12_H

/*! @} */ // barometer12

// ------------------------------------------------------------------------ END
