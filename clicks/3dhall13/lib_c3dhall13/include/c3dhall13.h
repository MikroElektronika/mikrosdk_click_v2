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
 * @file c3dhall13.h
 * @brief This file contains API for 3D Hall 13 Click Driver.
 */

#ifndef C3DHALL13_H
#define C3DHALL13_H

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
 * @addtogroup c3dhall13 3D Hall 13 Click Driver
 * @brief API for configuring and manipulating 3D Hall 13 Click driver.
 * @{
 */

/**
 * @defgroup c3dhall13_reg 3D Hall 13 Registers List
 * @brief List of registers of 3D Hall 13 Click driver.
 */

/**
 * @addtogroup c3dhall13_reg
 * @{
 */

/**
 * @brief 3D Hall 13 register list.
 * @details Specified register list of 3D Hall 13 Click driver.
 */
#define C3DHALL13_REG_DEVICE_CONFIG_1                       0x00
#define C3DHALL13_REG_DEVICE_CONFIG_2                       0x01
#define C3DHALL13_REG_SENSOR_CONFIG_1                       0x02
#define C3DHALL13_REG_SENSOR_CONFIG_2                       0x03
#define C3DHALL13_REG_THR_CONFIG_1                          0x04
#define C3DHALL13_REG_THR_CONFIG_2                          0x05
#define C3DHALL13_REG_THR_CONFIG_3                          0x06
#define C3DHALL13_REG_SENSOR_CONFIG_3                       0x07
#define C3DHALL13_REG_INT_CONFIG_1                          0x08
#define C3DHALL13_REG_SENSOR_CONFIG_4                       0x09
#define C3DHALL13_REG_SENSOR_CONFIG_5                       0x0A
#define C3DHALL13_REG_SENSOR_CONFIG_6                       0x0B
#define C3DHALL13_REG_I2C_ADDRESS                           0x0C
#define C3DHALL13_REG_DEVICE_ID                             0x0D
#define C3DHALL13_REG_MANUFACTURER_ID_LSB                   0x0E
#define C3DHALL13_REG_MANUFACTURER_ID_MSB                   0x0F
#define C3DHALL13_REG_T_RESULT_MSB                          0x10
#define C3DHALL13_REG_T_RESULT_LSB                          0x11
#define C3DHALL13_REG_X_RESULT_MSB                          0x12
#define C3DHALL13_REG_X_RESULT_LSB                          0x13
#define C3DHALL13_REG_Y_RESULT_MSB                          0x14
#define C3DHALL13_REG_Y_RESULT_LSB                          0x15
#define C3DHALL13_REG_Z_RESULT_MSB                          0x16
#define C3DHALL13_REG_Z_RESULT_LSB                          0x17
#define C3DHALL13_REG_CONV_STATUS                           0x18
#define C3DHALL13_REG_ANGLE_RESULT_MSB                      0x19
#define C3DHALL13_REG_ANGLE_RESULT_LSB                      0x1A
#define C3DHALL13_REG_MAGNITUDE_RESULT                      0x1B
#define C3DHALL13_REG_DEVICE_STATUS                         0x1C

/*! @} */ // c3dhall13_reg

/**
 * @defgroup c3dhall13_set 3D Hall 13 Registers Settings
 * @brief Settings for registers of 3D Hall 13 Click driver.
 */

/**
 * @addtogroup c3dhall13_set
 * @{
 */

/**
 * @brief 3D Hall 13 DEVICE_CONFIG_1 register settings.
 * @details Specified settings for DEVICE_CONFIG_1 register of 3D Hall 13 Click driver.
 */
#define C3DHALL13_DEVICE_CONFIG_1_CRC_DISABLE               0x00
#define C3DHALL13_DEVICE_CONFIG_1_CRC_ENABLE                0x80
#define C3DHALL13_DEVICE_CONFIG_1_CRC_EN_MASK               0x80
#define C3DHALL13_DEVICE_CONFIG_1_MAG_TEMPCO_0              0x00
#define C3DHALL13_DEVICE_CONFIG_1_MAG_TEMPCO_0_12           0x20
#define C3DHALL13_DEVICE_CONFIG_1_MAG_TEMPCO_0_3            0x40
#define C3DHALL13_DEVICE_CONFIG_1_MAG_TEMPCO_0_2            0x60
#define C3DHALL13_DEVICE_CONFIG_1_MAG_TEMPCO_MASK           0x60
#define C3DHALL13_DEVICE_CONFIG_1_CONV_AVG_1X               0x00
#define C3DHALL13_DEVICE_CONFIG_1_CONV_AVG_2X               0x04
#define C3DHALL13_DEVICE_CONFIG_1_CONV_AVG_4X               0x08
#define C3DHALL13_DEVICE_CONFIG_1_CONV_AVG_8X               0x0C
#define C3DHALL13_DEVICE_CONFIG_1_CONV_AVG_16X              0x10
#define C3DHALL13_DEVICE_CONFIG_1_CONV_AVG_32X              0x14
#define C3DHALL13_DEVICE_CONFIG_1_CONV_AVG_MASK             0x1C
#define C3DHALL13_DEVICE_CONFIG_1_I2C_RD_STANDARD           0x00
#define C3DHALL13_DEVICE_CONFIG_1_I2C_RD_1_BYTE_16BIT       0x01
#define C3DHALL13_DEVICE_CONFIG_1_I2C_RD_1_BYTE_8BIT        0x02
#define C3DHALL13_DEVICE_CONFIG_1_I2C_RD_MASK               0x03

/**
 * @brief 3D Hall 13 DEVICE_CONFIG_2 register settings.
 * @details Specified settings for DEVICE_CONFIG_2 register of 3D Hall 13 Click driver.
 */
#define C3DHALL13_DEVICE_CONFIG_2_THR_HYST_2_LSB            0x00
#define C3DHALL13_DEVICE_CONFIG_2_THR_HYST_4_LSB            0x20
#define C3DHALL13_DEVICE_CONFIG_2_THR_HYST_8_LSB            0x40
#define C3DHALL13_DEVICE_CONFIG_2_THR_HYST_16_LSB           0x60
#define C3DHALL13_DEVICE_CONFIG_2_THR_HYST_32_LSB           0x80
#define C3DHALL13_DEVICE_CONFIG_2_THR_HYST_64_LSB           0xA0
#define C3DHALL13_DEVICE_CONFIG_2_THR_HYST_128_LSB          0xC0
#define C3DHALL13_DEVICE_CONFIG_2_THR_HYST_256_LSB          0xE0
#define C3DHALL13_DEVICE_CONFIG_2_THR_HYST_MASK             0xE0
#define C3DHALL13_DEVICE_CONFIG_2_LP_LN_ACTIVE_CURRENT_MODE 0x00
#define C3DHALL13_DEVICE_CONFIG_2_LP_LN_NOISE_MODE          0x10
#define C3DHALL13_DEVICE_CONFIG_2_LP_LN_MASK                0x10
#define C3DHALL13_DEVICE_CONFIG_2_I2C_GLITCH_FILTER_ON      0x00
#define C3DHALL13_DEVICE_CONFIG_2_I2C_GLITCH_FILTER_OFF     0x08
#define C3DHALL13_DEVICE_CONFIG_2_I2C_GLITCH_FILTER_MASK    0x08
#define C3DHALL13_DEVICE_CONFIG_2_TRIGGER_MODE_CMD          0x00
#define C3DHALL13_DEVICE_CONFIG_2_TRIGGER_MODE_INT          0x04
#define C3DHALL13_DEVICE_CONFIG_2_TRIGGER_MODE_MASK         0x04
#define C3DHALL13_DEVICE_CONFIG_2_OPERATING_MODE_STANDBY    0x00
#define C3DHALL13_DEVICE_CONFIG_2_OPERATING_MODE_SLEEP      0x01
#define C3DHALL13_DEVICE_CONFIG_2_OPERATING_MODE_CONTINUOUS 0x02
#define C3DHALL13_DEVICE_CONFIG_2_OPERATING_MODE_WS         0x03
#define C3DHALL13_DEVICE_CONFIG_2_OPERATING_MODE_MASK       0x03

/**
 * @brief 3D Hall 13 SENSOR_CONFIG_1 register settings.
 * @details Specified settings for SENSOR_CONFIG_1 register of 3D Hall 13 Click driver.
 */
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_DISABLE         0x00
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_X        0x10
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_Y        0x20
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_XY       0x30
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_Z        0x40
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_ZX       0x50
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_YZ       0x60
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_XYZ      0x70
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_XYX      0x80
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_YXY      0x90
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_YZY      0xA0
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_ENABLE_XZX      0xB0
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_XYZ_POS_OFFSET  0xC0
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_XYZ_NEG_OFFSET  0xD0
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_HALL_RES_ADC    0xE0
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_HALL_OFFSET_AFE 0xF0
#define C3DHALL13_SENSOR_CONFIG_1_MAG_CH_EN_MASK            0xF0
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_1MS             0x00
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_5MS             0x01
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_10MS            0x02
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_15MS            0x03
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_20MS            0x04
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_30MS            0x05
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_50MS            0x06
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_100MS           0x07
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_500MS           0x08
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_1000MS          0x09
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_2000MS          0x0A
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_5000MS          0x0B
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_20000MS         0x0C
#define C3DHALL13_SENSOR_CONFIG_1_SLEEPTIME_MASK            0x0F

/**
 * @brief 3D Hall 13 SENSOR_CONFIG_2 register settings.
 * @details Specified settings for SENSOR_CONFIG_2 register of 3D Hall 13 Click driver.
 */
#define C3DHALL13_SENSOR_CONFIG_2_T_RATE_SINGLE             0x00
#define C3DHALL13_SENSOR_CONFIG_2_T_RATE_AVG                0x80
#define C3DHALL13_SENSOR_CONFIG_2_T_RATE_MASK               0x80
#define C3DHALL13_SENSOR_CONFIG_2_INTB_POL_LOW              0x00
#define C3DHALL13_SENSOR_CONFIG_2_INTB_POL_HIGH             0x40
#define C3DHALL13_SENSOR_CONFIG_2_INTB_POL_MASK             0x40
#define C3DHALL13_SENSOR_CONFIG_2_MAG_THR_DIR_ABOVE         0x00
#define C3DHALL13_SENSOR_CONFIG_2_MAG_THR_DIR_BELOW         0x20
#define C3DHALL13_SENSOR_CONFIG_2_MAG_THR_DIR_MASK          0x20
#define C3DHALL13_SENSOR_CONFIG_2_MAG_GAIN_CH_1             0x00
#define C3DHALL13_SENSOR_CONFIG_2_MAG_GAIN_CH_2             0x10
#define C3DHALL13_SENSOR_CONFIG_2_MAG_GAIN_CH_MASK          0x10
#define C3DHALL13_SENSOR_CONFIG_2_ANGLE_EN_NO_ANGLE         0x00
#define C3DHALL13_SENSOR_CONFIG_2_ANGLE_EN_XY_ANGLE         0x04
#define C3DHALL13_SENSOR_CONFIG_2_ANGLE_EN_YZ_ANGLE         0x08
#define C3DHALL13_SENSOR_CONFIG_2_ANGLE_EN_XZ_ANGLE         0x0C
#define C3DHALL13_SENSOR_CONFIG_2_ANGLE_EN_MASK             0x0C
#define C3DHALL13_SENSOR_CONFIG_2_X_Y_RANGE_40MT            0x00
#define C3DHALL13_SENSOR_CONFIG_2_X_Y_RANGE_80MT            0x02
#define C3DHALL13_SENSOR_CONFIG_2_X_Y_RANGE_MASK            0x02
#define C3DHALL13_SENSOR_CONFIG_2_Z_RANGE_40MT              0x00
#define C3DHALL13_SENSOR_CONFIG_2_Z_RANGE_80MT              0x01
#define C3DHALL13_SENSOR_CONFIG_2_Z_RANGE_MASK              0x01

/**
 * @brief 3D Hall 13 SENSOR_CONFIG_3 register settings.
 * @details Specified settings for SENSOR_CONFIG_3 register of 3D Hall 13 Click driver.
 */
#define C3DHALL13_SENSOR_CONFIG_3_WOC_SEL_DISABLE           0x00
#define C3DHALL13_SENSOR_CONFIG_3_WOC_SEL_ANGLE             0x40
#define C3DHALL13_SENSOR_CONFIG_3_WOC_SEL_MAG_FIELD         0x80
#define C3DHALL13_SENSOR_CONFIG_3_WOC_SEL_MASK              0xC0
#define C3DHALL13_SENSOR_CONFIG_3_THR_SEL_DISABLE           0x00
#define C3DHALL13_SENSOR_CONFIG_3_THR_SEL_ANGLE             0x10
#define C3DHALL13_SENSOR_CONFIG_3_THR_SEL_B_FIELD           0x20
#define C3DHALL13_SENSOR_CONFIG_3_THR_SEL_BUTTON            0x30
#define C3DHALL13_SENSOR_CONFIG_3_THR_SEL_MASK              0x30
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_HYS_1_DEG           0x00
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_HYS_2_DEGS          0x04
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_HYS_4_DEGS          0x08
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_HYS_8_DEGS          0x08
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_HYS_MASK            0x0C
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_OFFSET_EN_DISABLE   0x00
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_OFFSET_EN_ENABLE    0x02
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_OFFSET_EN_MASK      0x02
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_OFFSET_DIR_ADDED    0x00
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_OFFSET_DIR_SUBSTR   0x01
#define C3DHALL13_SENSOR_CONFIG_3_ANGLE_OFFSET_DIR_MASK     0x01

/**
 * @brief 3D Hall 13 INT_CONFIG_1 register settings.
 * @details Specified settings for INT_CONFIG_1 register of 3D Hall 13 Click driver.
 */
#define C3DHALL13_INT_CONFIG_1_RESULT_INT_NO_ASSERT         0x00
#define C3DHALL13_INT_CONFIG_1_RESULT_INT_ASSERT            0x80
#define C3DHALL13_INT_CONFIG_1_RESULT_INT_MASK              0x80
#define C3DHALL13_INT_CONFIG_1_THRESHOLD_INT_NO_ASSERT      0x00
#define C3DHALL13_INT_CONFIG_1_THRESHOLD_INT_ASSERT         0x40
#define C3DHALL13_INT_CONFIG_1_THRESHOLD_INT_MASK           0x40
#define C3DHALL13_INT_CONFIG_1_INT_STATE_LATCHED            0x00
#define C3DHALL13_INT_CONFIG_1_INT_STATE_PULSE_5US          0x20
#define C3DHALL13_INT_CONFIG_1_INT_STATE_MASK               0x20
#define C3DHALL13_INT_CONFIG_1_INT_MODE_NO_INT              0x00
#define C3DHALL13_INT_CONFIG_1_INT_MODE_INT                 0x04
#define C3DHALL13_INT_CONFIG_1_INT_MODE_INT_WO_I2C_BUSY     0x08
#define C3DHALL13_INT_CONFIG_1_INT_MODE_SCL                 0x0C
#define C3DHALL13_INT_CONFIG_1_INT_MODE_SCL_WO_I2C_BUSY     0x10
#define C3DHALL13_INT_CONFIG_1_INT_MODE_UNIPOLAR_SWITCH     0x14
#define C3DHALL13_INT_CONFIG_1_INT_MODE_OMNIPOLAR_SWITCH    0x18
#define C3DHALL13_INT_CONFIG_1_INT_MODE_MASK                0x1C
#define C3DHALL13_INT_CONFIG_1_INT_POL_EN_DISABLE           0x00
#define C3DHALL13_INT_CONFIG_1_INT_POL_EN_ENABLE            0x02
#define C3DHALL13_INT_CONFIG_1_INT_POL_EN_MASK              0x02
#define C3DHALL13_INT_CONFIG_1_MASK_INT_ENABLE              0x00
#define C3DHALL13_INT_CONFIG_1_MASK_INT_DISABLE             0x01
#define C3DHALL13_INT_CONFIG_1_MASK_INT_MASK                0x01

/**
 * @brief 3D Hall 13 DEVICE_ID and MANUFACTURER_ID values.
 * @details Specified DEVICE_ID and MANUFACTURER_ID values of 3D Hall 13 Click driver.
 */
#define C3DHALL13_DEVICE_ID                                 0x00
#define C3DHALL13_DEVICE_ID_MASK                            0x0C
#define C3DHALL13_MANUFACTURER_ID_LSB                       0x49
#define C3DHALL13_MANUFACTURER_ID_MSB                       0x54

/**
 * @brief 3D Hall 13 CONV_STATUS register settings.
 * @details Specified settings for CONV_STATUS register of 3D Hall 13 Click driver.
 */
#define C3DHALL13_CONV_STATUS_SET_COUNT_MASK                0xE0
#define C3DHALL13_CONV_STATUS_POR                           0x10
#define C3DHALL13_CONV_STATUS_DIAG_STATUS                   0x02
#define C3DHALL13_CONV_STATUS_DATA_READY                    0x01

/**
 * @brief 3D Hall 13 DEVICE_STATUS register settings.
 * @details Specified settings for DEVICE_STATUS register of 3D Hall 13 Click driver.
 */
#define C3DHALL13_DEVICE_STATUS_INTB_RB                     0x10
#define C3DHALL13_DEVICE_STATUS_INT_ER                      0x04
#define C3DHALL13_DEVICE_STATUS_OTP_CRC_ER                  0x02
#define C3DHALL13_DEVICE_STATUS_THR_CROSS                   0x01

/**
 * @brief 3D Hall 13 calculation values.
 * @details Specified calculation values of 3D Hall 13 Click driver.
 */
#define C3DHALL13_TEMP_SENS_T0                              25.0
#define C3DHALL13_TEMP_ADC_T0                               17512
#define C3DHALL13_TEMP_ADC_RESOLUTION                       58.2
#define C3DHALL13_ANGLE_RESOLUTION                          16.0
#define C3DHALL13_XYZ_SENSITIVITY_40MT                      885.0
#define C3DHALL13_XYZ_SENSITIVITY_80MT                      446.0

/**
 * @brief 3D Hall 13 device address setting.
 * @details Specified setting for device slave address selection of
 * 3D Hall 13 Click driver.
 */
#define C3DHALL13_DEVICE_ADDRESS_0                          0x34
#define C3DHALL13_DEVICE_ADDRESS_1                          0x35

/*! @} */ // c3dhall13_set

/**
 * @defgroup c3dhall13_map 3D Hall 13 MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 13 Click driver.
 */

/**
 * @addtogroup c3dhall13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 13 Click to the selected MikroBUS.
 */
#define C3DHALL13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3dhall13_map
/*! @} */ // c3dhall13

/**
 * @brief 3D Hall 13 Click data object.
 * @details Data object definition of 3D Hall 13 Click driver.
 */
typedef struct
{
    float x_axis;
    float y_axis;
    float z_axis;
    float angle;
    float temperature;
    uint8_t magnitude;
    
} c3dhall13_data_t;

/**
 * @brief 3D Hall 13 Click context object.
 * @details Context object definition of 3D Hall 13 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} c3dhall13_t;

/**
 * @brief 3D Hall 13 Click configuration object.
 * @details Configuration object definition of 3D Hall 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} c3dhall13_cfg_t;

/**
 * @brief 3D Hall 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL13_OK = 0,
    C3DHALL13_ERROR = -1

} c3dhall13_return_value_t;

/*!
 * @addtogroup c3dhall13 3D Hall 13 Click Driver
 * @brief API for configuring and manipulating 3D Hall 13 Click driver.
 * @{
 */

/**
 * @brief 3D Hall 13 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3dhall13_cfg_setup ( c3dhall13_cfg_t *cfg );

/**
 * @brief 3D Hall 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall13_init ( c3dhall13_t *ctx, c3dhall13_cfg_t *cfg );

/**
 * @brief 3D Hall 13 default configuration function.
 * @details This function executes a default configuration of 3D Hall 13
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c3dhall13_default_cfg ( c3dhall13_t *ctx );

/**
 * @brief 3D Hall 13 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall13_generic_write ( c3dhall13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 3D Hall 13 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall13_generic_read ( c3dhall13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 3D Hall 13 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall13_write_register ( c3dhall13_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 3D Hall 13 read register function.
 * @details This function reads data from the selected register.
 * @param[in] ctx : Click context object.
 * See #c3dhall13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall13_read_register ( c3dhall13_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 3D Hall 13 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3dhall13_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3dhall13_get_int_pin ( c3dhall13_t *ctx );

/**
 * @brief 3D Hall 13 check communication function.
 * @details This function checks the communication by reading and verifying the device and manufacturer IDs.
 * @param[in] ctx : Click context object.
 * See #c3dhall13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall13_check_communication ( c3dhall13_t *ctx );

/**
 * @brief 3D Hall 13 read data function.
 * @details This function reads new data which consists of X, Y, and Z axis values in mT, 
 * and temperature in Celsius. It also reads the angle in Degrees between X and Y by default, 
 * and magnitude data as well.
 * @param[in] ctx : Click context object.
 * See #c3dhall13_t object definition for detailed explanation.
 * @param[out] data_out : A structure object that contains the output read data.
 * See #c3dhall13_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall13_read_data ( c3dhall13_t *ctx, c3dhall13_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // C3DHALL13_H

/*! @} */ // c3dhall13

// ------------------------------------------------------------------------ END
