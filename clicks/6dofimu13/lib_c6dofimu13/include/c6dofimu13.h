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
 * @file c6dofimu13.h
 * @brief This file contains API for 6DOF IMU 13 Click Driver.
 */

#ifndef C6DOFIMU13_H
#define C6DOFIMU13_H

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
 * @addtogroup c6dofimu13 6DOF IMU 13 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 13 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu13_reg 6DOF IMU 13 Registers List
 * @brief List of registers of 6DOF IMU 13 Click driver.
 */

/**
 * @addtogroup c6dofimu13_reg
 * @{
 */

/**
 * @brief 6DOF IMU 13 Magnetometer register summary.
 * @details The list of Magnetometer registers.
 */
#define C6DOFIMU13_MAG_SELFTEST_RESP     0x0C
#define C6DOFIMU13_MAG_MORE_INFO_VER     0x0D
#define C6DOFIMU13_MAG_MORE_INFO         0x0E
#define C6DOFIMU13_MAG_WHO_I_AM          0x0F
#define C6DOFIMU13_MAG_OUT_X_LSB         0x10
#define C6DOFIMU13_MAG_OUT_X_MSB         0x11
#define C6DOFIMU13_MAG_OUT_Y_LSB         0x12
#define C6DOFIMU13_MAG_OUT_Y_MSB         0x13
#define C6DOFIMU13_MAG_OUT_Z_LSB         0x14
#define C6DOFIMU13_MAG_OUT_Z_MSB         0x15
#define C6DOFIMU13_MAG_STAT              0x18
#define C6DOFIMU13_MAG_CTL_1             0x1B
#define C6DOFIMU13_MAG_CTL_2             0x1C
#define C6DOFIMU13_MAG_CTL_3             0x1D
#define C6DOFIMU13_MAG_CTL_4             0x1E
#define C6DOFIMU13_MAG_OFFS_X_LSB        0x20
#define C6DOFIMU13_MAG_OFFS_X_MSB        0x21
#define C6DOFIMU13_MAG_OFFS_Y_LSB        0x22
#define C6DOFIMU13_MAG_OFFS_Y_MSB        0x23
#define C6DOFIMU13_MAG_OFFS_Z_LSB        0x24
#define C6DOFIMU13_MAG_OFFS_Z_MSB        0x25
#define C6DOFIMU13_MAG_ITHR_L            0x26
#define C6DOFIMU13_MAG_ITHR_H            0x27
#define C6DOFIMU13_MAG_TEMP_VAL          0x31

/**
 * @brief 6DOF IMU 13 Accelerometer register summary.
 * @details The list of Accelerometer registers.
 */
#define C6DOFIMU13_ACCEL_SR              0x03
#define C6DOFIMU13_ACCEL_OPSTAT          0x04
#define C6DOFIMU13_ACCEL_INTEN           0x06
#define C6DOFIMU13_ACCEL_MODE            0x07
#define C6DOFIMU13_ACCEL_SRTFR           0x08
#define C6DOFIMU13_ACCEL_TAPEN           0x09
#define C6DOFIMU13_ACCEL_TTTRX           0x0A
#define C6DOFIMU13_ACCEL_TTTRY           0x0B
#define C6DOFIMU13_ACCEL_TTTRZ           0x0C
#define C6DOFIMU13_ACCEL_XOUT_EX_L       0x0D
#define C6DOFIMU13_ACCEL_XOUT_EX_H       0x0E
#define C6DOFIMU13_ACCEL_YOUT_EX_L       0x0F
#define C6DOFIMU13_ACCEL_YOUT_EX_H       0x10
#define C6DOFIMU13_ACCEL_ZOUT_EX_L       0x11
#define C6DOFIMU13_ACCEL_ZOUT_EX_H       0x12
#define C6DOFIMU13_ACCEL_OUTCFG          0x20
#define C6DOFIMU13_ACCEL_XOFFL           0x21
#define C6DOFIMU13_ACCEL_XOFFH           0x22
#define C6DOFIMU13_ACCEL_YOFFL           0x23
#define C6DOFIMU13_ACCEL_YOFFH           0x24
#define C6DOFIMU13_ACCEL_ZOFFL           0x25
#define C6DOFIMU13_ACCEL_ZOFFH           0x26
#define C6DOFIMU13_ACCEL_XGAIN           0x27
#define C6DOFIMU13_ACCEL_YGAIN           0x28
#define C6DOFIMU13_ACCEL_ZGAIN           0x29
#define C6DOFIMU13_ACCEL_PCODE           0x3B

/*! @} */ // c6dofimu13_reg

/**
 * @defgroup c6dofimu13_set 6DOF IMU 13 Registers Settings
 * @brief Settings for registers of 6DOF IMU 13 Click driver.
 */

/**
 * @addtogroup c6dofimu13_set
 * @{
 */

/**
 * @brief 6DOF IMU 13 Status register settings.
 * @details Status register setting flags.
 */
#define C6DOFIMU13_MAG_STAT_DRDY         0x40
#define C6DOFIMU13_MAG_STAT_DOR          0x20

/**
 * @brief 6DOF IMU 13 Control 1 register settings.
 * @details Control 1 register setting flags.
 */
#define C6DOFIMU13_MAG_CTL_1_PC_NORM     0x80
#define C6DOFIMU13_MAG_CTL_1_PC_STBY     0x00
#define C6DOFIMU13_MAG_CTL_1_ODR_05      0x00
#define C6DOFIMU13_MAG_CTL_1_ODR_10      0x08
#define C6DOFIMU13_MAG_CTL_1_ODR_20      0x10
#define C6DOFIMU13_MAG_CTL_1_ODR_100     0x18
#define C6DOFIMU13_MAG_CTL_1_FS_DEF      0x02
#define C6DOFIMU13_MAG_CTL_1_FS_NORM     0x00

/**
 * @brief 6DOF IMU 13 Control 3 register settings.
 * @details Control 3 register setting flags.
 */
#define C6DOFIMU13_MAG_CTL_3_SRST_SR     0x80
#define C6DOFIMU13_MAG_CTL_3_SRST_NOP    0x00
#define C6DOFIMU13_MAG_CTL_3_FRC_SM      0x40
#define C6DOFIMU13_MAG_CTL_3_FRC_NOP     0x00
#define C6DOFIMU13_MAG_CTL_3_STC_EN      0x10
#define C6DOFIMU13_MAG_CTL_3_STC_NOP     0x00
#define C6DOFIMU13_MAG_CTL_3_TCS_EN      0x02
#define C6DOFIMU13_MAG_CTL_3_TCS_NOP     0x00
#define C6DOFIMU13_MAG_CTL_3_OCL_EN      0x01
#define C6DOFIMU13_MAG_CTL_3_OCL_NOP     0x00

/**
 * @brief 6DOF IMU 13 Control 4 register settings.
 * @details Control 4 register setting flags.
 */
#define C6DOFIMU13_MAG_CTL_4_RS_S_14     0x00
#define C6DOFIMU13_MAG_CTL_4_RS_S_15     0x10

/**
 * @brief 6DOF IMU 13 Magnetometer Sensitivity settings.
 * @details Magnetometer Sensitivity setting.
 */
#define C6DOFIMU13_MAG_SENS              0.15
#define C6DOFIMU13_MAG_ORIENTATION_COEF  -1.0

/**
 * @brief 6DOF IMU 13 Magnetometer Range and operation mode settings.
 * @details Magnetometer Range and operation mode setting.
 */
#define C6DOFIMU13_MAG_RES_14_BIT        0x00
#define C6DOFIMU13_MAG_RES_15_BIT        0x01
#define C6DOFIMU13_MAG_OP_MODE_S_SHOT    0x00
#define C6DOFIMU13_MAG_OP_MODE_CONT      0x01
#define C6DOFIMU13_MAG_TEMP_MEAS_OFF     0x00
#define C6DOFIMU13_MAG_TEMP_MEAS_ON      0x01

/**
 * @brief 6DOF IMU 13 Magnetometer axis settings.
 * @details Magnetometer axis setting.
 */
#define C6DOFIMU13_MAG_AXIS_X            0x00
#define C6DOFIMU13_MAG_AXIS_Y            0x01
#define C6DOFIMU13_MAG_AXIS_Z            0x02

/**
 * @brief 6DOF IMU 13 Accelerometer SR: Status Register Flags settings.
 * @details Accelerometer SR: Status Register Flags setting.
 */
#define C6DOFIMU13_ACCEL_SR_TAP_XP       0x01
#define C6DOFIMU13_ACCEL_SR_TAP_XN       0x02
#define C6DOFIMU13_ACCEL_SR_TAP_YP       0x04
#define C6DOFIMU13_ACCEL_SR_TAP_YN       0x08
#define C6DOFIMU13_ACCEL_SR_TAP_ZP       0x10
#define C6DOFIMU13_ACCEL_SR_TAP_ZN       0x20
#define C6DOFIMU13_ACCEL_SR_AC_INT       0x80

/**
 * @brief 6DOF IMU 13 Accelerometer OPSTAT: Device Status Register Flags settings.
 * @details Accelerometer OPSTAT: Device Status Register Flags setting.
 */
#define C6DOFIMU13_ACCEL_OPSTAT_WAKE     0x01
#define C6DOFIMU13_ACCEL_OPSTAT_WDT      0x10
#define C6DOFIMU13_ACCEL_OPSTAT_OTPA     0x80

/**
 * @brief 6DOF IMU 13 Accelerometer INTEN: Interrupt Enable Register settings.
 * @details Accelerometer INTEN: Interrupt Enable Register setting.
 */
#define C6DOFIMU13_ACCEL_INTEN_TIXPEN    0x01
#define C6DOFIMU13_ACCEL_INTEN_TIXNEN    0x02
#define C6DOFIMU13_ACCEL_INTEN_TIYPEN    0x04
#define C6DOFIMU13_ACCEL_INTEN_TIYNEN    0x08
#define C6DOFIMU13_ACCEL_INTEN_TIZPEN    0x10
#define C6DOFIMU13_ACCEL_INTEN_TIZNEN    0x20
#define C6DOFIMU13_ACCEL_INTEN_AC_INT_EN 0x80

/**
 * @brief 6DOF IMU 13 Accelerometer MODE: Mode Register settings.
 * @details Accelerometer MODE: Mode Register setting.
 */
#define C6DOFIMU13_ACCEL_MODE_STDBY      0x00
#define C6DOFIMU13_ACCEL_MODE_WAKE       0x01
#define C6DOFIMU13_ACCEL_MODE_WDT_NEG    0x10
#define C6DOFIMU13_ACCEL_MODE_WDT_POS    0x20
#define C6DOFIMU13_ACCEL_MODE_IPP        0x40
#define C6DOFIMU13_ACCEL_MODE_IAH        0x80

/**
 * @brief 6DOF IMU 13 Accelerometer SRTFR: Sample Rate and Tap Feature Register settings.
 * @details Accelerometer SRTFR: Sample Rate and Tap Feature Register setting.
 */
#define C6DOFIMU13_ACCEL_SRTFR_RATE_32   0x00
#define C6DOFIMU13_ACCEL_SRTFR_RATE_16   0x01
#define C6DOFIMU13_ACCEL_SRTFR_RATE_8    0x02
#define C6DOFIMU13_ACCEL_SRTFR_RATE_4    0x03
#define C6DOFIMU13_ACCEL_SRTFR_RATE_2    0x04
#define C6DOFIMU13_ACCEL_SRTFR_RATE_1    0x05
#define C6DOFIMU13_ACCEL_SRTFR_RATE_0_5  0x06
#define C6DOFIMU13_ACCEL_SRTFR_RATE_0_25 0x07
#define C6DOFIMU13_ACCEL_SRTFR_RATE_64   0x08
#define C6DOFIMU13_ACCEL_SRTFR_RATE_128  0x09
#define C6DOFIMU13_ACCEL_SRTFR_RATE_256  0x0A
#define C6DOFIMU13_ACCEL_SRTFR_FLIP_TAPX 0x10
#define C6DOFIMU13_ACCEL_SRTFR_FLIP_TAPY 0x20
#define C6DOFIMU13_ACCEL_SRTFR_FLIP_TAPZ 0x40
#define C6DOFIMU13_ACCEL_SRTFR_TAP_LATCH 0x80

/**
 * @brief 6DOF IMU 13 Accelerometer TAPEN: Tap Control Register settings.
 * @details Accelerometer TAPEN: Tap Control Register setting.
 */
#define C6DOFIMU13_ACCEL_TAPEN_TAPXPEN   0x01
#define C6DOFIMU13_ACCEL_TAPEN_TAPXNEN   0x02
#define C6DOFIMU13_ACCEL_TAPEN_TAPYPEN   0x04
#define C6DOFIMU13_ACCEL_TAPEN_TAPYNEN   0x08
#define C6DOFIMU13_ACCEL_TAPEN_TAPZPEN   0x10
#define C6DOFIMU13_ACCEL_TAPEN_TAPZNEN   0x20
#define C6DOFIMU13_ACCEL_TAPEN_THRDUR    0x40
#define C6DOFIMU13_ACCEL_TAPEN_TAP_EN    0x80

/**
 * @brief 6DOF IMU 13 Accelerometer OUTCFG: Output Configuration Register settings.
 * @details Accelerometer OUTCFG: Output Configuration Register setting.
 */
#define C6DOFIMU13_ACCEL_OUTCFG_RANGE_2  0x00
#define C6DOFIMU13_ACCEL_OUTCFG_RANGE_4  0x10
#define C6DOFIMU13_ACCEL_OUTCFG_RANGE_8  0x20
#define C6DOFIMU13_ACCEL_OUTCFG_RANGE_16 0x30
#define C6DOFIMU13_ACCEL_OUTCFG_RES_6    0x00
#define C6DOFIMU13_ACCEL_OUTCFG_RES_7    0x01
#define C6DOFIMU13_ACCEL_OUTCFG_RES_8    0x02
#define C6DOFIMU13_ACCEL_OUTCFG_RES_10   0x03
#define C6DOFIMU13_ACCEL_OUTCFG_RES_12   0x04
#define C6DOFIMU13_ACCEL_OUTCFG_RES_14   0x05

/**
 * @brief 6DOF IMU 13 Accelerometer axis.
 * @details Accelerometer axis value.
 */
#define C6DOFIMU13_ACCEL_AXIS_X          0x00
#define C6DOFIMU13_ACCEL_AXIS_Y          0x01
#define C6DOFIMU13_ACCEL_AXIS_Z          0x02


/**
 * @brief 6DOF IMU 13 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 13 Click driver.
 */
#define C6DOFIMU13_DEV_ADDRESS_ACCEL_GND 0x4C
#define C6DOFIMU13_DEV_ADDRESS_ACCEL_VCC 0x6C
#define C6DOFIMU13_DEV_ADDRESS_MAG       0x0C

/*! @} */ // c6dofimu13_set

/**
 * @defgroup c6dofimu13_map 6DOF IMU 13 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 13 Click driver.
 */

/**
 * @addtogroup c6dofimu13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 13 Click to the selected MikroBUS.
 */
#define C6DOFIMU13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu13_map
/*! @} */ // c6dofimu13

/**
 * @brief 6DOF IMU 13 Click context object.
 * @details Context object definition of 6DOF IMU 13 Click driver.
 */
typedef struct
{
    // Input pins

    digital_in_t  in2;      /**< Magnetometer interrupt pin. */
    digital_in_t  in1;      /**< Accelerometer interrupt pin. */

    // Modules

    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    

    float calc_coef;        /**< Accel coeficient */

} c6dofimu13_t;

/**
 * @brief 6DOF IMU 13 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 13 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  in2;        /**< Magnetometer interrupt pin. */
    pin_name_t  in1;        /**< Accelerometer interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} c6dofimu13_cfg_t;

/**
 * @brief 6DOF IMU 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   C6DOFIMU13_OK = 0,
   C6DOFIMU13_ERROR = -1

} c6dofimu13_return_value_t;

/*!
 * @addtogroup c6dofimu13 6DOF IMU 13 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 13 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 13 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void c6dofimu13_cfg_setup ( c6dofimu13_cfg_t *cfg );

/**
 * @brief 6DOF IMU 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_init ( c6dofimu13_t *ctx, c6dofimu13_cfg_t *cfg );

/**
 * @brief 6DOF IMU 13 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 13
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t c6dofimu13_default_cfg ( c6dofimu13_t *ctx );

/**
 * @brief 6DOF IMU 13 set slave address function.
 * @details This function sets the I2C slave address.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[in] slave_address : Slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_set_slave_address ( c6dofimu13_t *ctx, uint8_t slave_address );

/**
 * @brief 6DOF IMU 13 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_generic_write ( c6dofimu13_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief 6DOF IMU 13 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_generic_read ( c6dofimu13_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief 6DOF IMU 13 Magnetometer initialize function.
 * @details This function initializes magnetometer.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[in] res : Resolution.
 * @param[in] op_mode : Operation mode (single shot or continuous).
 * @param[in] temp_meas : Temperature measurement (enable or disable).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_mag_init ( c6dofimu13_t *ctx, uint8_t res, uint8_t op_mode, uint8_t temp_meas );

/**
 * @brief 6DOF IMU 13 Magnetometer get X-Axis data function.
 * @details This function reads magnetometer X-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] result : Magnetometer X-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_mag_get_x ( c6dofimu13_t *ctx, float *result );

/**
 * @brief 6DOF IMU 13 Magnetometer get Y-Axis data function.
 * @details This function reads magnetometer Y-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] result : Magnetometer Y-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_mag_get_y ( c6dofimu13_t *ctx, float *result );

/**
 * @brief 6DOF IMU 13 Magnetometer get Z-Axis data function.
 * @details This function reads magnetometer Z-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] result : Magnetometer Z-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_mag_get_z ( c6dofimu13_t *ctx, float *result );

/**
 * @brief 6DOF IMU 13 Magnetometer get X, Y, and Z-Axis data function.
 * @details This function reads magnetometer X, Y, and Z-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] mag_x : Magnetometer X-Axis data.
 * @param[out] mag_y : Magnetometer Y-Axis data.
 * @param[out] mag_z : Magnetometer Z-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_mag_get_data ( c6dofimu13_t *ctx, float *mag_x, float *mag_y, float *mag_z );

/**
 * @brief 6DOF IMU 13 set magnetometer offset function.
 * @details This function sets magnetometer offset value for X, Y, or Z-Axis.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[in] offset : Offset value.
 * @param[in] axis : Axis for which it will set the offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_mag_offset ( c6dofimu13_t *ctx, int16_t offset, uint8_t axis );

/**
 * @brief 6DOF IMU 13 Accelerometer initialize function.
 * @details This function initializes accelerometer.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[in] samp_rate : Data sample rate.
 * @param[in] samp_range : Data sample range..
 * @param[in] samp_res : Data sample resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_accel_init ( c6dofimu13_t *ctx, uint8_t samp_rate, uint8_t samp_range, uint8_t samp_res );

/**
 * @brief 6DOF IMU 13 Accelerometer get RAW X-Axis data function.
 * @details This function reads RAW accelerometer X-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] result : RAW Accelerometer X-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_accel_get_raw_x ( c6dofimu13_t *ctx, int16_t *result );

/**
 * @brief 6DOF IMU 13 Accelerometer get RAW Y-Axis data function.
 * @details This function reads RAW accelerometer Y-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] result : RAW Accelerometer Y-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_accel_get_raw_y ( c6dofimu13_t *ctx, int16_t *result );

/**
 * @brief 6DOF IMU 13 Accelerometer get RAW Z-Axis data function.
 * @details This function reads RAW accelerometer Z-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] result : RAW Accelerometer Z-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_accel_get_raw_z ( c6dofimu13_t *ctx, int16_t *result );

/**
 * @brief 6DOF IMU 13 Accelerometer get X-Axis data function.
 * @details This function reads accelerometer X-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] result : Accelerometer X-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_accel_get_x ( c6dofimu13_t *ctx, float *result );

/**
 * @brief 6DOF IMU 13 Accelerometer get Y-Axis data function.
 * @details This function reads accelerometer Y-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] result : Accelerometer Y-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_accel_get_y ( c6dofimu13_t *ctx, float *result );

/**
 * @brief 6DOF IMU 13 Accelerometer get Z-Axis data function.
 * @details This function reads accelerometer Z-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] result : Accelerometer Z-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_accel_get_z ( c6dofimu13_t *ctx, float *result );

/**
 * @brief 6DOF IMU 13 Accelerometer get X, Y, and Z-Axis data function.
 * @details This function reads accelerometer X, Y, and Z-Axis data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[out] accel_x : Accelerometer X-Axis data.
 * @param[out] accel_y : Accelerometer Y-Axis data.
 * @param[out] accel_z : Accelerometer Z-Axis data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_accel_get_data ( c6dofimu13_t *ctx, float *accel_x, float *accel_y, float *accel_z );

/**
 * @brief 6DOF IMU 13 set accelerometer offset function.
 * @details This function sets accelerometer offset value for X, Y, or Z-Axis.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @param[in] offset : Offset value.
 * @param[in] axis : Axis for which it will set the offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c6dofimu13_accel_offset ( c6dofimu13_t *ctx, int16_t offset, uint8_t axis );

/**
 * @brief 6DOF IMU 13 get in1 pin state function.
 * @details This function gets the in1 pin state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t c6dofimu13_get_in1 ( c6dofimu13_t *ctx );

/**
 * @brief 6DOF IMU 13 get in2 pin state function.
 * @details This function gets the in2 pin state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu13_t object definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint8_t c6dofimu13_get_in2 ( c6dofimu13_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU13_H

/*! @} */ // c6dofimu13

// ------------------------------------------------------------------------ END
