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
 * @file c3dhall11.h
 * @brief This file contains API for 3D Hall 11 Click Driver.
 */

#ifndef C3DHALL11_H
#define C3DHALL11_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup c3dhall11 3D Hall 11 Click Driver
 * @brief API for configuring and manipulating 3D Hall 11 Click driver.
 * @{
 */

/**
 * @defgroup c3dhall11_reg 3D Hall 11 Registers List
 * @brief List of registers of 3D Hall 11 Click driver.
 */

/**
 * @addtogroup c3dhall11_reg
 * @{
 */

/**
 * @brief 3D Hall 11 register list.
 * @details Specified register list of 3D Hall 11 Click driver.
 */
#define C3DHALL11_REG_DEVICE_CONFIG_1               0x00
#define C3DHALL11_REG_DEVICE_CONFIG_2               0x01
#define C3DHALL11_REG_SENSOR_CONFIG_1               0x02
#define C3DHALL11_REG_SENSOR_CONFIG_2               0x03
#define C3DHALL11_REG_X_THR_CONFIG                  0x04
#define C3DHALL11_REG_Y_THR_CONFIG                  0x05
#define C3DHALL11_REG_Z_THR_CONFIG                  0x06
#define C3DHALL11_REG_T_CONFIG                      0x07
#define C3DHALL11_REG_INT_CONFIG_1                  0x08
#define C3DHALL11_REG_MAG_GAIN_CONFIG               0x09
#define C3DHALL11_REG_MAG_OFFSET_CONFIG_1           0x0A
#define C3DHALL11_REG_MAG_OFFSET_CONFIG_2           0x0B
#define C3DHALL11_REG_I2C_ADDRESS                   0x0C
#define C3DHALL11_REG_DEVICE_ID                     0x0D
#define C3DHALL11_REG_MANUFACTURER_ID_LSB           0x0E
#define C3DHALL11_REG_MANUFACTURER_ID_MSB           0x0F
#define C3DHALL11_REG_T_MSB_RESULT                  0x10
#define C3DHALL11_REG_T_LSB_RESULT                  0x11
#define C3DHALL11_REG_X_MSB_RESULT                  0x12
#define C3DHALL11_REG_X_LSB_RESULT                  0x13
#define C3DHALL11_REG_Y_MSB_RESULT                  0x14
#define C3DHALL11_REG_Y_LSB_RESULT                  0x15
#define C3DHALL11_REG_Z_MSB_RESULT                  0x16
#define C3DHALL11_REG_Z_LSB_RESULT                  0x17
#define C3DHALL11_REG_CONV_STATUS                   0x18
#define C3DHALL11_REG_ANGLE_RESULT_MSB              0x19
#define C3DHALL11_REG_ANGLE_RESULT_LSB              0x1A
#define C3DHALL11_REG_MAGNITUDE_RESULT              0x1B
#define C3DHALL11_REG_DEVICE_STATUS                 0x1C

/*! @} */ // c3dhall11_reg

/**
 * @defgroup c3dhall11_set 3D Hall 11 Registers Settings
 * @brief Settings for registers of 3D Hall 11 Click driver.
 */

/**
 * @addtogroup c3dhall11_set
 * @{
 */

/**
 * @brief 3D Hall 11 DEVICE_CONFIG_1 register settings.
 * @details Specified settings for DEVICE_CONFIG_1 register of 3D Hall 11 Click driver.
 */
#define C3DHALL11_CRC_DISABLE                       0x00
#define C3DHALL11_CRC_ENABLE                        0x80
#define C3DHALL11_CRC_EN_BIT_MASK                   0x80
#define C3DHALL11_MAG_TEMPCO_0                      0x00
#define C3DHALL11_MAG_TEMPCO_0p12                   0x20
#define C3DHALL11_MAG_TEMPCO_0p2                    0x60
#define C3DHALL11_MAG_TEMPCO_BIT_MASK               0x60
#define C3DHALL11_CONV_AVG_1X                       0x00
#define C3DHALL11_CONV_AVG_2X                       0x04
#define C3DHALL11_CONV_AVG_4X                       0x08
#define C3DHALL11_CONV_AVG_8X                       0x0C
#define C3DHALL11_CONV_AVG_16X                      0x10
#define C3DHALL11_CONV_AVG_32X                      0x14
#define C3DHALL11_CONV_AVG_BIT_MASK                 0x1C
#define C3DHALL11_I2C_RD_STANDARD                   0x00
#define C3DHALL11_I2C_RD_1_BYTE_16BIT               0x01
#define C3DHALL11_I2C_RD_1_BYTE_8BIT                0x02
#define C3DHALL11_I2C_RD_BIT_MASK                   0x03

/**
 * @brief 3D Hall 11 DEVICE_CONFIG_2 register settings.
 * @details Specified settings for DEVICE_CONFIG_2 register of 3D Hall 11 Click driver.
 */
#define C3DHALL11_THR_HYST_2S_COMPLEMENT            0x00
#define C3DHALL11_THR_HYST_7LSB                     0x20
#define C3DHALL11_THR_HYST_BIT_MASK                 0xE0
#define C3DHALL11_LP_LN_ACTUVE_CURRENT_MODE         0x00
#define C3DHALL11_LP_LN_NOISE_MODE                  0x10
#define C3DHALL11_LP_LN_BIT_MASK                    0x10
#define C3DHALL11_I2C_GLITCH_FILTER_ON              0x00
#define C3DHALL11_I2C_GLITCH_FILTER_OFF             0x08
#define C3DHALL11_I2C_GLITCH_FILTER_BIT_MASK        0x08
#define C3DHALL11_TRIGGER_MODE_CMD                  0x00
#define C3DHALL11_TRIGGER_MODE_INT                  0x04
#define C3DHALL11_TRIGGER_MODE_BIT_MASK             0x04
#define C3DHALL11_OPERATING_MODE_STANDBY            0x00
#define C3DHALL11_OPERATING_MODE_SLEEP              0x01
#define C3DHALL11_OPERATING_MODE_CONTINUOUS         0x02
#define C3DHALL11_OPERATING_MODE_WS                 0x03
#define C3DHALL11_OPERATING_MODE_BIT_MASK           0x03

/**
 * @brief 3D Hall 11 SENSOR_CONFIG_1 register settings.
 * @details Specified settings for SENSOR_CONFIG_1 register of 3D Hall 11 Click driver.
 */
#define C3DHALL11_MAG_CH_EN_DISABLE                 0x00
#define C3DHALL11_MAG_CH_EN_ENABLE_X                0x10
#define C3DHALL11_MAG_CH_EN_ENABLE_Y                0x20
#define C3DHALL11_MAG_CH_EN_ENABLE_XY               0x30
#define C3DHALL11_MAG_CH_EN_ENABLE_Z                0x40
#define C3DHALL11_MAG_CH_EN_ENABLE_ZX               0x50
#define C3DHALL11_MAG_CH_EN_ENABLE_YZ               0x60
#define C3DHALL11_MAG_CH_EN_ENABLE_XYZ              0x70
#define C3DHALL11_MAG_CH_EN_ENABLE_XYX              0x80
#define C3DHALL11_MAG_CH_EN_ENABLE_YXY              0x90
#define C3DHALL11_MAG_CH_EN_ENABLE_YZY              0xA0
#define C3DHALL11_MAG_CH_EN_ENABLE_XZX              0xB0
#define C3DHALL11_MAG_CH_EN_BIT_MASK                0xF0
#define C3DHALL11_SLEEPTIME_1MS                     0x00
#define C3DHALL11_SLEEPTIME_5MS                     0x01
#define C3DHALL11_SLEEPTIME_10MS                    0x02
#define C3DHALL11_SLEEPTIME_15MS                    0x03
#define C3DHALL11_SLEEPTIME_20MS                    0x04
#define C3DHALL11_SLEEPTIME_30MS                    0x05
#define C3DHALL11_SLEEPTIME_50MS                    0x06
#define C3DHALL11_SLEEPTIME_100MS                   0x07
#define C3DHALL11_SLEEPTIME_500MS                   0x08
#define C3DHALL11_SLEEPTIME_1000MS                  0x09
#define C3DHALL11_SLEEPTIME_2000MS                  0x0A
#define C3DHALL11_SLEEPTIME_5000MS                  0x0B
#define C3DHALL11_SLEEPTIME_20000MS                 0x0C
#define C3DHALL11_SLEEPTIME_BIT_MASK                0x0F

/**
 * @brief 3D Hall 11 SENSOR_CONFIG_2 register settings.
 * @details Specified settings for SENSOR_CONFIG_2 register of 3D Hall 11 Click driver.
 */
#define C3DHALL11_THRX_COUNT_1                      0x00
#define C3DHALL11_THRX_COUNT_4                      0x40
#define C3DHALL11_THRX_COUNT_BIT_MASK               0x40
#define C3DHALL11_MAG_THR_DIR_ABOVE                 0x00
#define C3DHALL11_MAG_THR_DIR_BELOW                 0x20
#define C3DHALL11_MAG_THR_DIR_BIT_MASK              0x20
#define C3DHALL11_MAG_GAIN_CH_1                     0x00
#define C3DHALL11_MAG_GAIN_CH_2                     0x10
#define C3DHALL11_MAG_GAIN_CH_BIT_MASK              0x10
#define C3DHALL11_ANGLE_EN_NO_ANGLE                 0x00
#define C3DHALL11_ANGLE_EN_XY_ANGLE                 0x04
#define C3DHALL11_ANGLE_EN_YZ_ANGLE                 0x08
#define C3DHALL11_ANGLE_EN_XZ_ANGLE                 0x0C
#define C3DHALL11_ANGLE_EN_BIT_MASK                 0x0C
#define C3DHALL11_X_Y_RANGE_40mT                    0x00
#define C3DHALL11_X_Y_RANGE_80mT                    0x02
#define C3DHALL11_X_Y_RANGE_BIT_MASK                0x02
#define C3DHALL11_Z_RANGE_40mT                      0x00
#define C3DHALL11_Z_RANGE_80mT                      0x01
#define C3DHALL11_Z_RANGE_BIT_MASK                  0x01

/**
 * @brief 3D Hall 11 T_CONFIG register settings.
 * @details Specified settings for T_CONFIG register of 3D Hall 11 Click driver.
 */
#define C3DHALL11_T_THR_CONFIG_BIT_MASK             0xFE
#define C3DHALL11_T_CH_EN_DISABLE                   0x00
#define C3DHALL11_T_CH_EN_ENABLE                    0x01
#define C3DHALL11_T_CH_EN_BIT_MASK                  0x01

/**
 * @brief 3D Hall 11 INT_CONFIG_1 register settings.
 * @details Specified settings for INT_CONFIG_1 register of 3D Hall 11 Click driver.
 */
#define C3DHALL11_RSLT_INT_NO_ASSERT                0x00
#define C3DHALL11_RSLT_INT_ASSERT                   0x80
#define C3DHALL11_RSLT_INT_BIT_MASK                 0x80
#define C3DHALL11_THRSLD_INT_NO_ASSERT              0x00
#define C3DHALL11_THRSLD_INT_ASSERT                 0x40
#define C3DHALL11_THRSLD_INT_BIT_MASK               0x40
#define C3DHALL11_INT_STATE_LATCHED                 0x00
#define C3DHALL11_INT_STATE_PULSE_10US              0x20
#define C3DHALL11_INT_STATE_BIT_MASK                0x20
#define C3DHALL11_INT_MODE_NO_INT                   0x00
#define C3DHALL11_INT_MODE_INT                      0x04
#define C3DHALL11_INT_MODE_INT_WO_I2C_BUSY          0x08
#define C3DHALL11_INT_MODE_SCL                      0x0C
#define C3DHALL11_INT_MODE_SCL_WO_I2C_BUSY          0x10
#define C3DHALL11_INT_MODE_BIT_MASK                 0x1C
#define C3DHALL11_MASK_INTB_ENABLE                  0x00
#define C3DHALL11_MASK_INTB_DISABLE                 0x01
#define C3DHALL11_MASK_INTB_BIT_MASK                0x01

/**
 * @brief 3D Hall 11 DEVICE_ID and MANUFACTURER_ID values.
 * @details Specified DEVICE_ID and MANUFACTURER_ID values of 3D Hall 11 Click driver.
 */
#define C3DHALL11_DEVICE_ID                         0x01
#define C3DHALL11_MANUFACTURER_ID_LSB               0x49
#define C3DHALL11_MANUFACTURER_ID_MSB               0x54

/**
 * @brief 3D Hall 11 CONV_STATUS register settings.
 * @details Specified settings for CONV_STATUS register of 3D Hall 11 Click driver.
 */
#define C3DHALL11_CONV_STATUS_SET_COUNT             0xE0
#define C3DHALL11_CONV_STATUS_DIAG_STATUS           0x02
#define C3DHALL11_CONV_STATUS_DATA_READY            0x01

/**
 * @brief 3D Hall 11 DEVICE_STATUS register settings.
 * @details Specified settings for DEVICE_STATUS register of 3D Hall 11 Click driver.
 */
#define C3DHALL11_DEVICE_STATUS_INTB_RB             0x10
#define C3DHALL11_DEVICE_STATUS_OSC_ER              0x08
#define C3DHALL11_DEVICE_STATUS_INT_ER              0x04
#define C3DHALL11_DEVICE_STATUS_OTP_CRC_ER          0x02
#define C3DHALL11_DEVICE_STATUS_VCC_UV_ER           0x01

/**
 * @brief 3D Hall 11 calculation values.
 * @details Specified calculation values of 3D Hall 11 Click driver.
 */
#define C3DHALL11_TEMP_SENS_T0                      25.0
#define C3DHALL11_TEMP_ADC_T0                       17508
#define C3DHALL11_TEMP_ADC_RESOLUTION               60.1
#define C3DHALL11_ANGLE_RESOLUTION                  16.0
#define C3DHALL11_XYZ_SENSITIVITY_40mT              820.0
#define C3DHALL11_XYZ_SENSITIVITY_80mT              410.0

/**
 * @brief 3D Hall 11 device address setting.
 * @details Specified setting for device slave address selection of
 * 3D Hall 11 Click driver.
 */
#define C3DHALL11_DEVICE_ADDRESS                    0x35

/*! @} */ // c3dhall11_set

/**
 * @defgroup c3dhall11_map 3D Hall 11 MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 11 Click driver.
 */

/**
 * @addtogroup c3dhall11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 11 Click to the selected MikroBUS.
 */
#define C3DHALL11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3dhall11_map
/*! @} */ // c3dhall11

/**
 * @brief 3D Hall 11 Click data object.
 * @details Data object definition of 3D Hall 11 Click driver.
 */
typedef struct
{
    float x_axis;
    float y_axis;
    float z_axis;
    float angle;
    float temperature;
    uint8_t magnitude;
    
} c3dhall11_data_t;

/**
 * @brief 3D Hall 11 Click context object.
 * @details Context object definition of 3D Hall 11 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;      /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} c3dhall11_t;

/**
 * @brief 3D Hall 11 Click configuration object.
 * @details Configuration object definition of 3D Hall 11 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} c3dhall11_cfg_t;

/**
 * @brief 3D Hall 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL11_OK = 0,
    C3DHALL11_ERROR = -1

} c3dhall11_return_value_t;

/*!
 * @addtogroup c3dhall11 3D Hall 11 Click Driver
 * @brief API for configuring and manipulating 3D Hall 11 Click driver.
 * @{
 */

/**
 * @brief 3D Hall 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3dhall11_cfg_setup ( c3dhall11_cfg_t *cfg );

/**
 * @brief 3D Hall 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall11_init ( c3dhall11_t *ctx, c3dhall11_cfg_t *cfg );

/**
 * @brief 3D Hall 11 default configuration function.
 * @details This function executes a default configuration of 3D Hall 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c3dhall11_default_cfg ( c3dhall11_t *ctx );

/**
 * @brief 3D Hall 11 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall11_generic_write ( c3dhall11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 3D Hall 11 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall11_generic_read ( c3dhall11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 3D Hall 11 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall11_write_register ( c3dhall11_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 3D Hall 11 read register function.
 * @details This function reads data from the selected register.
 * @param[in] ctx : Click context object.
 * See #c3dhall11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall11_read_register ( c3dhall11_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 3D Hall 11 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3dhall11_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3dhall11_get_int_pin ( c3dhall11_t *ctx );

/**
 * @brief 3D Hall 11 check communication function.
 * @details This function checks the communication by reading and verifying the device and manufacturer IDs.
 * @param[in] ctx : Click context object.
 * See #c3dhall11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall11_check_communication ( c3dhall11_t *ctx );

/**
 * @brief 3D Hall 11 read data function.
 * @details This function reads new data which consists of X, Y, and Z axis values in mT, 
 * and temperature in Celsius. It also reads the angle in Degrees between X and Y by default, 
 * and magnitude data as well.
 * @param[in] ctx : Click context object.
 * See #c3dhall11_t object definition for detailed explanation.
 * @param[out] data_out : A structure object that contains the output read data.
 * See #c3dhall11_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall11_read_data ( c3dhall11_t *ctx, c3dhall11_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // C3DHALL11_H

/*! @} */ // c3dhall11

// ------------------------------------------------------------------------ END
