/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file geomagnetic2.h
 * @brief This file contains API for GeoMagnetic 2 Click Driver.
 */

#ifndef GEOMAGNETIC2_H
#define GEOMAGNETIC2_H

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
 * @addtogroup geomagnetic2 GeoMagnetic 2 Click Driver
 * @brief API for configuring and manipulating GeoMagnetic 2 Click driver.
 * @{
 */

/**
 * @defgroup geomagnetic2_reg GeoMagnetic 2 Registers List
 * @brief List of registers of GeoMagnetic 2 Click driver.
 */

/**
 * @addtogroup geomagnetic2_reg
 * @{
 */

/**
 * @brief GeoMagnetic 2 register map.
 * @details Specified register map of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_REG_CHIP_ID                0x00
#define GEOMAGNETIC2_REG_ERR_REG                0x02
#define GEOMAGNETIC2_REG_PAD_CTRL               0x03
#define GEOMAGNETIC2_REG_PMU_CMD_AGGR_SET       0x04
#define GEOMAGNETIC2_REG_PMU_CMD_AXIS_EN        0x05
#define GEOMAGNETIC2_REG_PMU_CMD                0x06
#define GEOMAGNETIC2_REG_PMU_CMD_STATUS_0       0x07
#define GEOMAGNETIC2_REG_PMU_CMD_STATUS_1       0x08
#define GEOMAGNETIC2_REG_I3C_ERR                0x09
#define GEOMAGNETIC2_REG_I2C_WDT_SET            0x0A
#define GEOMAGNETIC2_REG_INT_CTRL               0x2E
#define GEOMAGNETIC2_REG_INT_CTRL_IBI           0x2F
#define GEOMAGNETIC2_REG_INT_STATUS             0x30
#define GEOMAGNETIC2_REG_MAG_X_XLSB             0x31
#define GEOMAGNETIC2_REG_MAG_X_LSB              0x32
#define GEOMAGNETIC2_REG_MAG_X_MSB              0x33
#define GEOMAGNETIC2_REG_MAG_Y_XLSB             0x34
#define GEOMAGNETIC2_REG_MAG_Y_LSB              0x35
#define GEOMAGNETIC2_REG_MAG_Y_MSB              0x36
#define GEOMAGNETIC2_REG_MAG_Z_XLSB             0x37
#define GEOMAGNETIC2_REG_MAG_Z_LSB              0x38
#define GEOMAGNETIC2_REG_MAG_Z_MSB              0x39
#define GEOMAGNETIC2_REG_TEMP_XLSB              0x3A
#define GEOMAGNETIC2_REG_TEMP_LSB               0x3B
#define GEOMAGNETIC2_REG_TEMP_MSB               0x3C
#define GEOMAGNETIC2_REG_SENSORTIME_XLSB        0x3D
#define GEOMAGNETIC2_REG_SENSORTIME_LSB         0x3E
#define GEOMAGNETIC2_REG_SENSORTIME_MSB         0x3F
#define GEOMAGNETIC2_REG_OTP_CMD_REG            0x50
#define GEOMAGNETIC2_REG_OTP_DATA_MSB_REG       0x52
#define GEOMAGNETIC2_REG_OTP_DATA_LSB_REG       0x53
#define GEOMAGNETIC2_REG_OTP_STATUS_REG         0x55
#define GEOMAGNETIC2_REG_TMR_SELFTEST_USER      0x60
#define GEOMAGNETIC2_REG_CTRL_USER              0x61
#define GEOMAGNETIC2_REG_CMD                    0x7E

/*! @} */ // geomagnetic2_reg

/**
 * @defgroup geomagnetic2_set GeoMagnetic 2 Registers Settings
 * @brief Settings for registers of GeoMagnetic 2 Click driver.
 */

/**
 * @addtogroup geomagnetic2_set
 * @{
 */

/**
 * @brief GeoMagnetic 2 chip ID setting.
 * @details Specified setting for chip ID of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_CHIP_ID                    0x33

/**
 * @brief GeoMagnetic 2 PMU command values setting.
 * @details Specified setting for PMU command values of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_PMU_CMD_SUS                0x00
#define GEOMAGNETIC2_PMU_CMD_NM                 0x01
#define GEOMAGNETIC2_PMU_CMD_UPD_OAE            0x02
#define GEOMAGNETIC2_PMU_CMD_FM                 0x03
#define GEOMAGNETIC2_PMU_CMD_FM_FAST            0x04
#define GEOMAGNETIC2_PMU_CMD_FGR                0x05
#define GEOMAGNETIC2_PMU_CMD_FGR_FAST           0x06
#define GEOMAGNETIC2_PMU_CMD_BR                 0x07
#define GEOMAGNETIC2_PMU_CMD_BR_FAST            0x08

/**
 * @brief GeoMagnetic 2 output data rate and mask setting.
 * @details Specified setting for output data rate and mask of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_ODR_400HZ                  0x02
#define GEOMAGNETIC2_ODR_200HZ                  0x03
#define GEOMAGNETIC2_ODR_100HZ                  0x04
#define GEOMAGNETIC2_ODR_50HZ                   0x05
#define GEOMAGNETIC2_ODR_25HZ                   0x06
#define GEOMAGNETIC2_ODR_12_5HZ                 0x07
#define GEOMAGNETIC2_ODR_6_25HZ                 0x08
#define GEOMAGNETIC2_ODR_3_125HZ                0x09
#define GEOMAGNETIC2_ODR_1_5625HZ               0x0A
#define GEOMAGNETIC2_ODR_MASK                   0x0F

/**
 * @brief GeoMagnetic 2 averaging and bit shift setting.
 * @details Specified setting for averaging and bit shift of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_AVG_1                      0x00
#define GEOMAGNETIC2_AVG_2                      0x01
#define GEOMAGNETIC2_AVG_4                      0x02
#define GEOMAGNETIC2_AVG_8                      0x03
#define GEOMAGNETIC2_AVG_SHIFT                  4

/**
 * @brief GeoMagnetic 2 axis enable and mask setting.
 * @details Specified setting for axis enable and mask of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_AXIS_EN_X                  0x01
#define GEOMAGNETIC2_AXIS_EN_Y                  0x02
#define GEOMAGNETIC2_AXIS_EN_Z                  0x04
#define GEOMAGNETIC2_AXIS_EN_ALL                0x07
#define GEOMAGNETIC2_AXIS_EN_MASK               0x07

/**
 * @brief GeoMagnetic 2 PMU status flags setting.
 * @details Specified setting for PMU status flags of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_PMU_CMD_BUSY_MASK          0x01
#define GEOMAGNETIC2_PMU_ODR_OVWR_MASK          0x02
#define GEOMAGNETIC2_PMU_AVR_OVWR_MASK          0x04
#define GEOMAGNETIC2_PMU_IS_NORMAL_MASK         0x08
#define GEOMAGNETIC2_PMU_CMD_ILLEGAL_MASK       0x10

/**
 * @brief GeoMagnetic 2 interrupt status setting.
 * @details Specified setting for interrupt status of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_INT_DRDY_MASK              0x04

/**
 * @brief GeoMagnetic 2 interrupt configuration setting.
 * @details Specified setting for interrupt configuration of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_INT_DRDY_EN                0x80
#define GEOMAGNETIC2_INT_OUTPUT_EN              0x08
#define GEOMAGNETIC2_INT_OD_PUSH_PULL           0x04
#define GEOMAGNETIC2_INT_POL_HIGH               0x02
#define GEOMAGNETIC2_INT_MODE_LATCHED           0x01

/**
 * @brief GeoMagnetic 2 OTP command values and masks setting.
 * @details Specified setting for OTP command values and masks of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_OTP_CMD_LOCK               0x80
#define GEOMAGNETIC2_OTP_CMD_DIR_READ           0x20
#define GEOMAGNETIC2_OTP_ADDR_MASK              0x1F

/**
 * @brief GeoMagnetic 2 soft reset command setting.
 * @details Specified setting for soft reset command of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_CMD_SOFT_RESET             0xB6

/**
 * @brief GeoMagnetic 2 burst read data length setting.
 * @details Specified setting for burst read data length of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_DATA_LEN                   15

/**
 * @brief GeoMagnetic 2 I2C dummy bytes count setting.
 * @details Specified setting for I2C dummy bytes count of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_DUMMY_BYTES                2

/**
 * @brief GeoMagnetic 2 max number of data setting.
 * @details Specified setting for max number of data of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_BMM350_MAX_LEN             127

/**
 * @brief GeoMagnetic 2 OTP compensation sign-extension threshold setting.
 * @details Specified setting for OTP compensation sign-extension threshold of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_OTP_12BIT_SIGN_THRESH      2048

/**
 * @brief GeoMagnetic 2 OTP status command done flag setting.
 * @details Specified setting for OTP status command done flag of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_OTP_STATUS_CMD_DONE        0x01

/**
 * @brief GeoMagnetic 2 raw data 24-bit sign extension setting.
 * @details Specified settings for raw data 24-bit sign extension of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_RAW_SIGN_BIT               0x800000
#define GEOMAGNETIC2_RAW_SIGN_EXT_MASK          0xFF000000

/**
 * @brief GeoMagnetic 2 OTP compensation scale factors setting.
 * @details Specified settings for OTP compensation scale factors of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_OTP_SENS_SCALE             256.0f
#define GEOMAGNETIC2_OTP_T_SENS_SCALE           512.0f
#define GEOMAGNETIC2_OTP_T_OFFS_SCALE           5.0f
#define GEOMAGNETIC2_OTP_TCO_SCALE              32.0f
#define GEOMAGNETIC2_OTP_TCS_SCALE              16384.0f
#define GEOMAGNETIC2_OTP_CROSS_SCALE            800.0f
#define GEOMAGNETIC2_OTP_T0_BASE                23.0f

/**
 * @brief GeoMagnetic 2 raw-to-uT and raw-to-degC conversion factor setting.
 * @details Specified setting for raw-to-uT and raw-to-degC conversion factor of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_TEMP_SENS                  0.00204f
#define GEOMAGNETIC2_ADC_GAIN                 ( 1.0f / 1.5f )
#define GEOMAGNETIC2_LUT_GAIN                   0.714607238769531f
#define GEOMAGNETIC2_RAW_SCALING                1048576.0f
#define GEOMAGNETIC2_TEMP_OFFSET_BASE           25.49f

#define GEOMAGNETIC2_TEMP_LSB_TO_DEGC           \
    ( 1.0f / ( GEOMAGNETIC2_TEMP_SENS *         \
               GEOMAGNETIC2_ADC_GAIN *          \
               GEOMAGNETIC2_LUT_GAIN *          \
               GEOMAGNETIC2_RAW_SCALING ) )


#define GEOMAGNETIC2_BXY_SENS                   14.55f
#define GEOMAGNETIC2_BZ_SENS                    9.0f
#define GEOMAGNETIC2_INA_XY_GAIN_TRGT           19.46f
#define GEOMAGNETIC2_INA_Z_GAIN_TRGT            31.0f
#define GEOMAGNETIC2_POWER                    ( 1000000.0f / 1048576.0f )

#define GEOMAGNETIC2_MAG_XY_LSB_TO_UT           \
    ( GEOMAGNETIC2_POWER /                      \
    ( GEOMAGNETIC2_BXY_SENS *                   \
      GEOMAGNETIC2_INA_XY_GAIN_TRGT *           \
      GEOMAGNETIC2_ADC_GAIN *                   \
      GEOMAGNETIC2_LUT_GAIN ) )

#define GEOMAGNETIC2_MAG_Z_LSB_TO_UT            \
    ( GEOMAGNETIC2_POWER /                      \
    ( GEOMAGNETIC2_BZ_SENS *                    \
      GEOMAGNETIC2_INA_Z_GAIN_TRGT *            \
      GEOMAGNETIC2_ADC_GAIN *                   \
      GEOMAGNETIC2_LUT_GAIN ) )

/**
 * @brief GeoMagnetic 2 timing delays setting.
 * @details Specified setting for timing delays of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_DELAY_SOFT_RESET_MS        2
#define GEOMAGNETIC2_DELAY_STARTUP_MS           2
#define GEOMAGNETIC2_DELAY_SUS_TO_NM_MS         38
#define GEOMAGNETIC2_DELAY_NM_TO_SUS_MS         6
#define GEOMAGNETIC2_DELAY_FM_MS                15
#define GEOMAGNETIC2_DELAY_BR_MS                14
#define GEOMAGNETIC2_DELAY_FGR_MS               18
#define GEOMAGNETIC2_DELAY_OTP_RDY_MS           5

/**
 * @brief GeoMagnetic 2 timeout setting.
 * @details Specified setting for timeout of GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_OTP_TIMEOUT_MS             50
#define GEOMAGNETIC2_PMU_TIMEOUT_MS             100

/**
 * @brief GeoMagnetic 2 device address setting.
 * @details Specified setting for device slave address selection of
 * GeoMagnetic 2 Click driver.
 */
#define GEOMAGNETIC2_DEVICE_ADDRESS             0x14

/*! @} */ // geomagnetic2_set

/**
 * @defgroup geomagnetic2_map GeoMagnetic 2 MikroBUS Map
 * @brief MikroBUS pin mapping of GeoMagnetic 2 Click driver.
 */

/**
 * @addtogroup geomagnetic2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GeoMagnetic 2 Click to the selected MikroBUS.
 */
#define GEOMAGNETIC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // geomagnetic2_map
/*! @} */ // geomagnetic2

/**
 * @brief GeoMagnetic 2 Click OTP compensation coefficients data structure.
 * @details OTP compensation coefficients data structure definition of GeoMagnetic 2 Click driver.
 */
typedef struct
{
    float dut_offx;     /**< Offset correction X-axis (raw counts). */
    float dut_offy;     /**< Offset correction Y-axis (raw counts). */
    float dut_offz;     /**< Offset correction Z-axis (raw counts). */
    float dut_sensx;    /**< Sensitivity correction X-axis. */
    float dut_sensy;    /**< Sensitivity correction Y-axis. */
    float dut_sensz;    /**< Sensitivity correction Z-axis. */
    float dut_tcox;     /**< Temperature coefficient of offset X. */
    float dut_tcoy;     /**< Temperature coefficient of offset Y. */
    float dut_tcoz;     /**< Temperature coefficient of offset Z. */
    float dut_tcsx;     /**< Temperature coefficient of sensitivity X. */
    float dut_tcsy;     /**< Temperature coefficient of sensitivity Y. */
    float dut_tcsz;     /**< Temperature coefficient of sensitivity Z. */
    float cross_x_y;    /**< Cross-axis correction XY. */
    float cross_y_x;    /**< Cross-axis correction YX. */
    float cross_z_x;    /**< Cross-axis correction ZX. */
    float cross_z_y;    /**< Cross-axis correction ZY. */
    float dut_t0;       /**< Reference temperature (degrees C). */
    float dut_t_sens;   /**< Temperature sensor sensitivity correction. */
    float dut_t_offs;   /**< Temperature sensor offset correction. */

} geomagnetic2_comp_t;

/**
 * @brief GeoMagnetic 2 Click context object.
 * @details Context object definition of GeoMagnetic 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;                       /**< Interrupt pin (active when data ready). */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */
    
    // cache variables
    geomagnetic2_comp_t comp;                   /**< OTP compensation coefficients. */
    uint8_t powermode;                          /**< Current power mode. */

} geomagnetic2_t;

/**
 * @brief GeoMagnetic 2 Click configuration object.
 * @details Configuration object definition of GeoMagnetic 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin descriptor. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} geomagnetic2_cfg_t;

/**
 * @brief GeoMagnetic 2 Click output data structure.
 * @details Compensated magnetic and temperature data of GeoMagnetic 2 Click driver.
 */
typedef struct
{
    float mag_x;            /**< Magnetic field X-axis (uT). */
    float mag_y;            /**< Magnetic field Y-axis (uT). */
    float mag_z;            /**< Magnetic field Z-axis (uT). */
    float temperature;      /**< Die temperature (degrees C). */

} geomagnetic2_data_t;

/**
 * @brief GeoMagnetic 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GEOMAGNETIC2_OK = 0,
    GEOMAGNETIC2_ERROR = -1

} geomagnetic2_return_value_t;

/*!
 * @addtogroup geomagnetic2 GeoMagnetic 2 Click Driver
 * @brief API for configuring and manipulating GeoMagnetic 2 Click driver.
 * @{
 */

/**
 * @brief GeoMagnetic 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #geomagnetic2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void geomagnetic2_cfg_setup ( geomagnetic2_cfg_t *cfg );

/**
 * @brief GeoMagnetic 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #geomagnetic2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_init ( geomagnetic2_t *ctx, geomagnetic2_cfg_t *cfg );

/**
 * @brief GeoMagnetic 2 default configuration function.
 * @details This function executes a default configuration of GeoMagnetic 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t geomagnetic2_default_cfg ( geomagnetic2_t *ctx );

/**
 * @brief GeoMagnetic 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_generic_write ( geomagnetic2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief GeoMagnetic 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_generic_read ( geomagnetic2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief GeoMagnetic 2 chip ID verification function.
 * @details This function reads and verifies the chip ID register.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @return @li @c  0 - Chip ID matches,
 *         @li @c -1 - Chip ID mismatch or communication error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_check_chip_id ( geomagnetic2_t *ctx );

/**
 * @brief GeoMagnetic 2 soft reset function.
 * @details This function performs a software reset and waits for the device to become ready.
 * After reset, OTP is accessible and device is in suspend mode.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_soft_reset ( geomagnetic2_t *ctx );

/**
 * @brief GeoMagnetic 2 power mode set function.
 * @details This function transitions the device to the requested power mode with proper
 * delays and state checks.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[in] powermode : Target power mode command value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Normal mode cannot transition directly to forced mode.
 * This function handles the intermediate suspend step automatically.
 */
err_t geomagnetic2_set_powermode ( geomagnetic2_t *ctx, uint8_t powermode );

/**
 * @brief GeoMagnetic 2 ODR and averaging set function.
 * @details This function configures the output data rate and noise averaging setting.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[in] odr : ODR setting.
 * @param[in] avg : Averaging setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_set_odr_avg ( geomagnetic2_t *ctx, uint8_t odr, uint8_t avg );

/**
 * @brief GeoMagnetic 2 axis enable function.
 * @details This function enables individual measurement axes.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[in] axes : Bitmask of axes to enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_enable_axes ( geomagnetic2_t *ctx, uint8_t axes );

/**
 * @brief GeoMagnetic 2 interrupt default configuration function.
 * @details This function configures the INT pin to default operation:
 * push-pull, active-high, latched mode, and output enabled.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_config_interrupt ( geomagnetic2_t *ctx );

/**
 * @brief GeoMagnetic 2 interrupt enable function.
 * @details This function enables or disables the data-ready interrupt on the INT pin.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[in] enable : 1 to enable, 0 to disable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_enable_interrupt ( geomagnetic2_t *ctx, uint8_t enable );

/**
 * @brief GeoMagnetic 2 interrupt status read function.
 * @details This function reads the INT_STATUS register.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[out] int_status : Interrupt status byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_get_int_status ( geomagnetic2_t *ctx, uint8_t *int_status );

/**
 * @brief GeoMagnetic 2 INT pin state read function.
 * @details This function reads the logical level of the hardware INT pin.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @return @li @c 1 - Pin is high,
 *         @li @c 0 - Pin is low.
 * @note None.
 */
uint8_t geomagnetic2_get_int_pin ( geomagnetic2_t *ctx );

/**
 * @brief GeoMagnetic 2 compensated data read function.
 * @details This function reads raw 24-bit magnetic and temperature data via burst read
 * and applies the full OTP compensation algorithm.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[out] mag_data : Compensated output data in uT and degrees C.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_read_data ( geomagnetic2_t *ctx, geomagnetic2_data_t *mag_data );

/**
 * @brief GeoMagnetic 2 magnetic reset function.
 * @details This function performs a full flux-guide reset (FGR) + bit reset (BR) sequence
 * to recover from magnetic field shock.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should be called if the device experiences a magnetic shock.
 */
err_t geomagnetic2_magnetic_reset ( geomagnetic2_t *ctx );

/**
 * @brief GeoMagnetic 2 OTP word read function.
 * @details This function reads a 16-bit word from the specified OTP address.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[in] addr : OTP address to read from.
 * @param[out] otp_word : Pointer to store the read OTP word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_otp_read_word ( geomagnetic2_t *ctx, uint8_t addr, uint16_t *otp_word );

/**
 * @brief GeoMagnetic 2 OTP read function.
 * @details This function reads the OTP values and updates the compensation parameters.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_update_comp ( geomagnetic2_t *ctx );

/**
 * @brief GeoMagnetic 2 PMU status read function.
 * @details This function reads the PMU status registers and returns the status flags.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @param[out] status0 : PMU status register 0 value.
 * @param[out] status1 : PMU status register 1 value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_get_pmu_status ( geomagnetic2_t *ctx, uint8_t *status0, uint8_t *status1 );

/**
 * @brief GeoMagnetic 2 PMU ready wait function.
 * @details This function waits until the PMU is no longer busy and ready for the next command.
 * @param[in] ctx : Click context object.
 * See #geomagnetic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t geomagnetic2_wait_pmu_ready ( geomagnetic2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // GEOMAGNETIC2_H

/*! @} */ // geomagnetic2

// ------------------------------------------------------------------------ END
