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
 * @file accelpressure.h
 * @brief This file contains API for AccelPressure Click Driver.
 */

#ifndef ACCELPRESSURE_H
#define ACCELPRESSURE_H

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
 * @addtogroup accelpressure AccelPressure Click Driver
 * @brief API for configuring and manipulating AccelPressure Click driver.
 * @{
 */

/**
 * @defgroup accelpressure_reg AccelPressure Registers List
 * @brief List of registers of AccelPressure Click driver.
 */

/**
 * @addtogroup accelpressure_reg
 * @{
 */

/**
 * @brief AccelPressure accel - FXLS8974CF description register.
 * @details Specified accel - FXLS8974CF register for description 
 * of AccelPressure Click driver.
 */
#define ACCELPRESSURE_ACC_REG_INT_STATUS               0x00
#define ACCELPRESSURE_ACC_REG_TEMP_OUT                 0x01
#define ACCELPRESSURE_ACC_REG_VECM_LSB                 0x02
#define ACCELPRESSURE_ACC_REG_VECM_MSB                 0x03
#define ACCELPRESSURE_ACC_REG_OUT_X_LSB                0x04
#define ACCELPRESSURE_ACC_REG_OUT_X_MSB                0x05
#define ACCELPRESSURE_ACC_REG_OUT_Y_LSB                0x06
#define ACCELPRESSURE_ACC_REG_OUT_Y_MSB                0x07
#define ACCELPRESSURE_ACC_REG_OUT_Z_LSB                0x08
#define ACCELPRESSURE_ACC_REG_OUT_Z_MSB                0x09
#define ACCELPRESSURE_ACC_REG_BUF_STATUS               0x0B
#define ACCELPRESSURE_ACC_REG_BUF_X_LSB                0x0C
#define ACCELPRESSURE_ACC_REG_BUF_X_MSB                0x0D
#define ACCELPRESSURE_ACC_REG_BUF_Y_LSB                0x0E
#define ACCELPRESSURE_ACC_REG_BUF_Y_MSB                0x0F
#define ACCELPRESSURE_ACC_REG_BUF_Z_LSB                0x10
#define ACCELPRESSURE_ACC_REG_BUF_Z_MSB                0x11
#define ACCELPRESSURE_ACC_REG_PROD_REV                 0x12
#define ACCELPRESSURE_ACC_REG_WHO_AM_I                 0x13
#define ACCELPRESSURE_ACC_REG_SYS_MODE                 0x14
#define ACCELPRESSURE_ACC_REG_SENS_CONFIG1             0x15
#define ACCELPRESSURE_ACC_REG_SENS_CONFIG2             0x16
#define ACCELPRESSURE_ACC_REG_SENS_CONFIG3             0x17
#define ACCELPRESSURE_ACC_REG_SENS_CONFIG4             0x18
#define ACCELPRESSURE_ACC_REG_SENS_CONFIG5             0x19
#define ACCELPRESSURE_ACC_REG_WAKE_IDLE_LSB            0x1A
#define ACCELPRESSURE_ACC_REG_WAKE_IDLE_MSB            0x1B
#define ACCELPRESSURE_ACC_REG_SLEEP_IDLE_LSB           0x1C
#define ACCELPRESSURE_ACC_REG_SLEEP_IDLE_MSB           0x1D
#define ACCELPRESSURE_ACC_REG_ASLP_COUNT_LSB           0x1E
#define ACCELPRESSURE_ACC_REG_ASLP_COUNT_MSB           0x1F
#define ACCELPRESSURE_ACC_REG_INT_EN                   0x20
#define ACCELPRESSURE_ACC_REG_INT_PIN_SEL              0x21
#define ACCELPRESSURE_ACC_REG_OFF_X                    0x22
#define ACCELPRESSURE_ACC_REG_OFF_Y                    0x23
#define ACCELPRESSURE_ACC_REG_OFF_Z                    0x24
#define ACCELPRESSURE_ACC_REG_BUF_CONFIG1              0x26
#define ACCELPRESSURE_ACC_REG_BUF_CONFIG2              0x27
#define ACCELPRESSURE_ACC_REG_ORIENT_STATUS            0x28
#define ACCELPRESSURE_ACC_REG_ORIENT_CONFIG            0x29
#define ACCELPRESSURE_ACC_REG_ORIENT_DBCOUNT           0x2A
#define ACCELPRESSURE_ACC_REG_ORIENT_BF_ZCOMP          0x2B
#define ACCELPRESSURE_ACC_REG_ORIENT_THS_REG           0x2C
#define ACCELPRESSURE_ACC_REG_SDCD_INT_SRC1            0x2D
#define ACCELPRESSURE_ACC_REG_SDCD_INT_SRC2            0x2E
#define ACCELPRESSURE_ACC_REG_SDCD_CONFIG1             0x2F
#define ACCELPRESSURE_ACC_REG_SDCD_CONFIG2             0x30
#define ACCELPRESSURE_ACC_REG_SDCD_OT_DBCNT            0x31
#define ACCELPRESSURE_ACC_REG_SDCD_WT_DBCNT            0x32
#define ACCELPRESSURE_ACC_REG_SDCD_LTHS_LSB            0x33
#define ACCELPRESSURE_ACC_REG_SDCD_LTHS_MSB            0x34
#define ACCELPRESSURE_ACC_REG_SDCD_UTHS_LSB            0x35
#define ACCELPRESSURE_ACC_REG_SDCD_UTHS_MSB            0x36
#define ACCELPRESSURE_ACC_REG_SELF_TEST_CONFIG1        0x37
#define ACCELPRESSURE_ACC_REG_SELF_TEST_CONFIG2        0x38

/**
 * @brief AccelPressure pressure - MPL3115A2 description register.
 * @details Specified pressure - MPL3115A2 register for description 
 * of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_REG_STATUS                 0x00
#define ACCELPRESSURE_PRESS_REG_OUT_P_MSB              0x01
#define ACCELPRESSURE_PRESS_REG_OUT_P_CSB              0x02
#define ACCELPRESSURE_PRESS_REG_OUT_P_LSB              0x03
#define ACCELPRESSURE_PRESS_REG_OUT_T_MSB              0x04
#define ACCELPRESSURE_PRESS_REG_OUT_T_LSB              0x05
#define ACCELPRESSURE_PRESS_REG_DR_STATUS              0x06
#define ACCELPRESSURE_PRESS_REG_OUT_P_DELTA_MSB        0x07
#define ACCELPRESSURE_PRESS_REG_OUT_P_DELTA_CSB        0x08
#define ACCELPRESSURE_PRESS_REG_OUT_P_DELTA_LSB        0x09
#define ACCELPRESSURE_PRESS_REG_OUT_T_DELTA_MSB        0x0A
#define ACCELPRESSURE_PRESS_REG_OUT_T_DELTA_LSB        0x0B
#define ACCELPRESSURE_PRESS_REG_WHO_AM_I               0x0C
#define ACCELPRESSURE_PRESS_REG_FIFO_STATUS            0x0D
#define ACCELPRESSURE_PRESS_REG_FIFO_DATA              0x0E
#define ACCELPRESSURE_PRESS_REG_FIFO_SETUP             0x0F
#define ACCELPRESSURE_PRESS_REG_TIME_DLY               0x10
#define ACCELPRESSURE_PRESS_REG_SYSMOD                 0x11
#define ACCELPRESSURE_PRESS_REG_INT_SOURCE             0x12
#define ACCELPRESSURE_PRESS_REG_PT_DATA_CFG            0x13
#define ACCELPRESSURE_PRESS_REG_BAR_IN_MSB             0x14
#define ACCELPRESSURE_PRESS_REG_BAR_IN_LSB             0x15
#define ACCELPRESSURE_PRESS_REG_P_TGT_MSB              0x16
#define ACCELPRESSURE_PRESS_REG_P_TGT_LSB              0x17
#define ACCELPRESSURE_PRESS_REG_T_TGT                  0x18
#define ACCELPRESSURE_PRESS_REG_P_WND_MSB              0x19
#define ACCELPRESSURE_PRESS_REG_P_WND_LSB              0x1A
#define ACCELPRESSURE_PRESS_REG_T_WND                  0x1B
#define ACCELPRESSURE_PRESS_REG_P_MIN_MSB              0x1C
#define ACCELPRESSURE_PRESS_REG_P_MIN_CSB              0x1D
#define ACCELPRESSURE_PRESS_REG_P_MIN_LSB              0x1E
#define ACCELPRESSURE_PRESS_REG_T_MIN_MSB              0x1F
#define ACCELPRESSURE_PRESS_REG_T_MIN_LSB              0x20
#define ACCELPRESSURE_PRESS_REG_P_MAX_MSB              0x21
#define ACCELPRESSURE_PRESS_REG_P_MAX_CSB              0x22
#define ACCELPRESSURE_PRESS_REG_P_MAX_LSB              0x23
#define ACCELPRESSURE_PRESS_REG_T_MAX_MSB              0x24
#define ACCELPRESSURE_PRESS_REG_T_MAX_LSB              0x25
#define ACCELPRESSURE_PRESS_REG_CTRL1                  0x26
#define ACCELPRESSURE_PRESS_REG_CTRL2                  0x27
#define ACCELPRESSURE_PRESS_REG_CTRL3                  0x28
#define ACCELPRESSURE_PRESS_REG_CTRL4                  0x29
#define ACCELPRESSURE_PRESS_REG_CTRL5                  0x2A
#define ACCELPRESSURE_PRESS_REG_OFF_P                  0x2B
#define ACCELPRESSURE_PRESS_REG_OFF_T                  0x2C
#define ACCELPRESSURE_PRESS_REG_OFF_H                  0x2D

/*! @} */ // accelpressure_reg

/**
 * @defgroup accelpressure_set AccelPressure Registers Settings
 * @brief Settings for registers of AccelPressure Click driver.
 */

/**
 * @addtogroup accelpressure_set
 * @{
 */

/**
 * @brief AccelPressure accelerometer nominal sensitivity data values.
 * @details Nominal sensitivity data values of AccelPressure Click driver.
 */
#define ACCELPRESSURE_ACC_SRC_BOOT_COMPLETED           0x01

/**
 * @brief AccelPressure accelerometer device ID data values.
 * @details Device ID data values of AccelPressure Click driver.
 */
#define ACCELPRESSURE_ACC_DEVICE_ID_VAL                0x86

/**
 * @brief AccelPressure accelerometer SW reset bit mask data values.
 * @details SW reset bit mask data values of AccelPressure Click driver.
 */
#define ACCELPRESSURE_ACC_SW_RESET_BIT_MASK            0x80

/**
 * @brief AccelPressure accelerometer operating mode data values.
 * @details Operating mode data values of AccelPressure Click driver.
 */
#define ACCELPRESSURE_ACC_OP_MODE_STANDBY              0x00
#define ACCELPRESSURE_ACC_OP_MODE_ACTIVE               0x01
#define ACCELPRESSURE_ACC_OP_MODE_BIT_MASK             0xFE

/**
 * @brief AccelPressure accelerometer full-scale measurement range (FSR) selection.
 * @details Full-scale measurement range (FSR) selection of AccelPressure Click driver.
 */
#define ACCELPRESSURE_ACC_FSR_SEL_2G                   0x00
#define ACCELPRESSURE_ACC_FSR_SEL_4G                   0x01
#define ACCELPRESSURE_ACC_FSR_SEL_8G                   0x02
#define ACCELPRESSURE_ACC_FSR_SEL_16G                  0x03
#define ACCELPRESSURE_ACC_FSR_SEL_BIT_MASK             0xF9

/**
 * @brief AccelPressure accelerometer data-ready interrupt output enable data values.
 * @details Data-ready interrupt output enable data values of AccelPressure Click driver.
 */
#define ACCELPRESSURE_ACC_INT_EN_DRDY_DIS              0x00
#define ACCELPRESSURE_ACC_INT_EN_DRDY_EN               0x80

/**
 * @brief AccelPressure accelerometer nominal sensitivity data values.
 * @details Nominal sensitivity data values of AccelPressure Click driver.
 */
#define ACCELPRESSURE_ACC_FSR_SENS_VAL_2G              0.98f
#define ACCELPRESSURE_ACC_FSR_SENS_VAL_4G              1.95f
#define ACCELPRESSURE_ACC_FSR_SENS_VAL_8G              3.91f
#define ACCELPRESSURE_ACC_FSR_SENS_VAL_16G             7.81f

/**
 * @brief AccelPressure pressure status data values.
 * @details Status data values of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_STATUS_FLAG_TDR            0x02
#define ACCELPRESSURE_PRESS_STATUS_FLAG_PDR            0x04
#define ACCELPRESSURE_PRESS_STATUS_FLAG_PTDR           0x08
#define ACCELPRESSURE_PRESS_STATUS_FLAG_TOW            0x20
#define ACCELPRESSURE_PRESS_STATUS_FLAG_POW            0x40
#define ACCELPRESSURE_PRESS_STATUS_FLAG_PTOW           0x80

/**
 * @brief AccelPressure pressure interrupt source flag data values.
 * @details Interrupt source flag data values of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_INT_SOURCE_FLAG_DRDY       0x80
#define ACCELPRESSURE_PRESS_INT_SOURCE_FLAG_FIFO       0x40
#define ACCELPRESSURE_PRESS_INT_SOURCE_FLAG_PW         0x20
#define ACCELPRESSURE_PRESS_INT_SOURCE_FLAG_TW         0x10
#define ACCELPRESSURE_PRESS_INT_SOURCE_FLAG_PTH        0x08
#define ACCELPRESSURE_PRESS_INT_SOURCE_FLAG_TTH        0x04
#define ACCELPRESSURE_PRESS_INT_SOURCE_FLAG_PCHG       0x02
#define ACCELPRESSURE_PRESS_INT_SOURCE_FLAG_TCHG       0x01

/**
 * @brief AccelPressure pressure control register 1 bit mask.
 * @details Control register 1 bit mask of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_CTRL1_ALT_BARO             0x00
#define ACCELPRESSURE_PRESS_CTRL1_ALT_ALTI             0x80
#define ACCELPRESSURE_PRESS_CTRL1_ALT_BITMASK          0x7F
#define ACCELPRESSURE_PRESS_CTRL1_SBYB                 0x01
#define ACCELPRESSURE_PRESS_CTRL1_OST                  0x02
#define ACCELPRESSURE_PRESS_CTRL1_CLR                  0x03
#define ACCELPRESSURE_PRESS_CTRL1_RST                  0x04
#define ACCELPRESSURE_PRESS_CTRL1_RAW                  0x40
#define ACCELPRESSURE_PRESS_CTRL1_ALT                  0x80
#define ACCELPRESSURE_PRESS_CTRL1_BAR                  0x00
#define ACCELPRESSURE_PRESS_CTRL1_OS1_6MS              0x00
#define ACCELPRESSURE_PRESS_CTRL1_OS2_10MS             0x08
#define ACCELPRESSURE_PRESS_CTRL1_OS4_18MS             0x10
#define ACCELPRESSURE_PRESS_CTRL1_OS8_34MS             0x18
#define ACCELPRESSURE_PRESS_CTRL1_OS16_66MS            0x20
#define ACCELPRESSURE_PRESS_CTRL1_OS32_130MS           0x28
#define ACCELPRESSURE_PRESS_CTRL1_OS64_258MS           0x30
#define ACCELPRESSURE_PRESS_CTRL1_OS128_512MS          0x38

/**
 * @brief AccelPressure pressure operating mode data values.
 * @details Operating mode data values of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_MODE_BAROMETER             0x00
#define ACCELPRESSURE_PRESS_MODE_ALTIMETER             0x01

/**
 * @brief AccelPressure pressure control register 3 bit mask.
 * @details Control register 3 bit mask of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_CTRL3_INT1_POL_HIGH        0x20
#define ACCELPRESSURE_PRESS_CTRL3_INT1_POL_LOW         0x00
#define ACCELPRESSURE_PRESS_CTRL3_INT1_OD              0x10
#define ACCELPRESSURE_PRESS_CTRL3_INT2_POL_HIGH        0x02
#define ACCELPRESSURE_PRESS_CTRL3_INT2_POL_LOW         0x00
#define ACCELPRESSURE_PRESS_CTRL3_INT2_OD              0x01

/**
 * @brief AccelPressure pressure control register 4 bit mask.
 * @details Control register 4 bit mask of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_CTRL4_INT_EN_DRDY          0x80
#define ACCELPRESSURE_PRESS_CTRL4_INT_EN_FIFO          0x40
#define ACCELPRESSURE_PRESS_CTRL4_INT_EN_PW            0x20
#define ACCELPRESSURE_PRESS_CTRL4_INT_EN_TW            0x10
#define ACCELPRESSURE_PRESS_CTRL4_INT_EN_PTH           0x08
#define ACCELPRESSURE_PRESS_CTRL4_INT_EN_TTH           0x04
#define ACCELPRESSURE_PRESS_CTRL4_INT_EN_PCHG          0x02
#define ACCELPRESSURE_PRESS_CTRL4_INT_EN_TCHG          0x01
#define ACCELPRESSURE_PRESS_CTRL4_INT_DIS_ALL          0x00

/**
 * @brief AccelPressure pressure control register 5 bit mask.
 * @details Control register 5 bit mask of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_CTRL5_INT1_DRDY            0x80
#define ACCELPRESSURE_PRESS_CTRL5_INT2_DRDY            0x00
#define ACCELPRESSURE_PRESS_CTRL5_INT1_FIFO            0x40
#define ACCELPRESSURE_PRESS_CTRL5_INT2_FIFO            0x00
#define ACCELPRESSURE_PRESS_CTRL5_INT1_PW              0x20
#define ACCELPRESSURE_PRESS_CTRL5_INT2_PW              0x00
#define ACCELPRESSURE_PRESS_CTRL5_INT1_TW              0x10
#define ACCELPRESSURE_PRESS_CTRL5_INT2_TW              0x00
#define ACCELPRESSURE_PRESS_CTRL5_INT1_PTH             0x08
#define ACCELPRESSURE_PRESS_CTRL5_INT2_PTH             0x00
#define ACCELPRESSURE_PRESS_CTRL5_INT1_TTH             0x04
#define ACCELPRESSURE_PRESS_CTRL5_INT2_TTH             0x00
#define ACCELPRESSURE_PRESS_CTRL5_INT1_PCHG            0x02
#define ACCELPRESSURE_PRESS_CTRL5_INT2_PCHG            0x00
#define ACCELPRESSURE_PRESS_CTRL5_INT1_TCHG            0x01
#define ACCELPRESSURE_PRESS_CTRL5_INT2_TCHG            0x00

/**
 * @brief AccelPressure pressure FIFO setup register bit mask.
 * @details FIFO setup register bit mask of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_F_SETUP_FIFO_DISABLE       0x00
#define ACCELPRESSURE_PRESS_F_SETUP_FIFO_CIR_BUFF      0x40
#define ACCELPRESSURE_PRESS_F_SETUP_FIFO_STOP_MODE     0x80

/**
 * @brief AccelPressure pressure sensor data register bit mask.
 * @details Sensor data register bit mask of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_PT_DATA_DR_EVENT_EN        0x04
#define ACCELPRESSURE_PRESS_PT_DATA_PD_EVENT_EN        0x02
#define ACCELPRESSURE_PRESS_PT_DATA_TD_EVENT_EN        0x01
#define ACCELPRESSURE_PRESS_PT_DATA_ALL_EVENTS_DIS     0x00

/**
 * @brief AccelPressure pressure and temperature calculation data values.
 * @details Sensor data register bit mask of AccelPressure Click driver.
 */
#define ACCELPRESSURE_PRESS_PRESSURE_SENS              0.25f
#define ACCELPRESSURE_PRESS_CONVERT_PA_TO_MBAR         100.0f
#define ACCELPRESSURE_PRESS_TEMP_SENS                  0.0625f

/**
 * @brief AccelPressure device address setting.
 * @details Specified setting for device slave address selection of
 * AccelPressure Click driver.
 */
#define ACCELPRESSURE_DEVICE_ADDRESS_ACCEL             0x18
#define ACCELPRESSURE_DEVICE_ADDRESS_PRESS             0x60

/*! @} */ // accelpressure_set

/**
 * @defgroup accelpressure_map AccelPressure MikroBUS Map
 * @brief MikroBUS pin mapping of AccelPressure Click driver.
 */

/**
 * @addtogroup accelpressure_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AccelPressure Click to the selected MikroBUS.
 */
#define ACCELPRESSURE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );   \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS );    \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.mot = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // accelpressure_map
/*! @} */ // accelpressure

/**
 * @brief AccelPressure Click context object.
 * @details Context object definition of AccelPressure Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cs;     /**< SPI chip select pin. */
    digital_out_t pwm;    /**< Wakeup pin. */

    // Input pins
    digital_in_t an;      /**< Hibernate mode pin. */
    digital_in_t mot;     /**< Motion detect pin. */

    // Modules
    i2c_master_t i2c;     /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

    // Sensitivity
    float sensitivity;        /**< Nominal sensitivity resolution. */

} accelpressure_t;

/**
 * @brief AccelPressure Click configuration object.
 * @details Configuration object definition of AccelPressure Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t cs;     /**< SPI chip select pin. */
    pin_name_t an;     /**< Hibernate mode pin. */
    pin_name_t pwm;    /**< Wakeup pin. */
    pin_name_t mot;    /**< Motion detect pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} accelpressure_cfg_t;

/**
 * @brief AccelPressure Click axes data.
 * @details Axes data object definition of AccelPressure Click driver.
 */
typedef struct
{
    float x;    /**< X-axis: convert raw-data into engineering units. */
    float y;    /**< Y-axis: convert raw-data into engineering units. */
    float z;    /**< Z-axis: convert raw-data into engineering units. */

} accelpressure_axes_t;

/**
 * @brief AccelPressure Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ACCELPRESSURE_OK = 0,
    ACCELPRESSURE_ERROR = -1

} accelpressure_return_value_t;

/*!
 * @addtogroup accelpressure AccelPressure Click Driver
 * @brief API for configuring and manipulating AccelPressure Click driver.
 * @{
 */

/**
 * @brief AccelPressure configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accelpressure_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accelpressure_cfg_setup ( accelpressure_cfg_t *cfg );

/**
 * @brief AccelPressure initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accelpressure_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_init ( accelpressure_t *ctx, accelpressure_cfg_t *cfg );

/**
 * @brief AccelPressure default configuration function.
 * @details This function executes a default configuration of AccelPressure
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accelpressure_default_cfg ( accelpressure_t *ctx );

/**
 * @brief AccelPressure accel I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_acc_reg_write ( accelpressure_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief AccelPressure accel I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_acc_reg_read ( accelpressure_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief AccelPressure pressure I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_press_reg_write ( accelpressure_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief AccelPressure pressure I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_press_reg_read ( accelpressure_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief AccelPressure get device ID function.
 * @details This function reads the device identification data
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[out] device_id : Device identification.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_get_device_id ( accelpressure_t *ctx, uint8_t *device_id );

/**
 * @brief AccelPressure get status function.
 * @details This function reads the status data
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_get_status ( accelpressure_t *ctx, uint8_t *status );

/**
 * @brief AccelPressure soft reset function.
 * @details This function trigger the soft reset sequence
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_sw_reset ( accelpressure_t *ctx );

/**
 * @brief AccelPressure set accel operating mode function.
 * @details This function sets the desired accelerometer operating mode
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[in] op_mode : Standby/Active mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_set_acc_mode ( accelpressure_t *ctx, uint8_t op_mode );

/**
 * @brief AccelPressure set FSR function.
 * @details This function sets the desired full-scale measurement range
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[in] fsr : Full-scale measurement range.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_set_fsr ( accelpressure_t *ctx, uint8_t fsr );

/**
 * @brief AccelPressure get the accel sensor axes function.
 * @details This function reads the accelerometer sensor axes data 
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[out] axes : Linear acceleration output data object (mg).
 * See #accelpressure_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_get_axes_data ( accelpressure_t *ctx, accelpressure_axes_t *axes );

/**
 * @brief AccelPressure set pressure operating mode function.
 * @details This function sets the desired pressure operating mode
 * of the MPL3115A2, I2C precision pressure sensor with altimetry 
 * on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[in] op_mode : Standby/Active mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_set_press_mode ( accelpressure_t *ctx, uint8_t op_mode );

/**
 * @brief AccelPressure get data ready status function.
 * @details This function reads the data ready status
 * of the MPL3115A2, I2C precision pressure sensor with altimetry 
 * on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[in] drdy : Data ready status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_get_drdy_status ( accelpressure_t *ctx, uint8_t *drdy );

/**
 * @brief AccelPressure get pressure data function.
 * @details This function reads the pressure data conversion
 * of the MPL3115A2, I2C precision pressure sensor with altimetry 
 * on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data [mbar].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_get_pressure ( accelpressure_t *ctx, float *pressure );

/**
 * @brief AccelPressure get temperature data function.
 * @details This function reads the temperature data conversion
 * of the MPL3115A2, I2C precision pressure sensor with altimetry 
 * on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data [degree Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accelpressure_get_temperature ( accelpressure_t *ctx, float *temperature );

/**
 * @brief AccelPressure get motion detect state function.
 * @details This function checks if motion is detected by reading the states of the MOT (INT) pin
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the AccelPressure Click board.
 * @param[in] ctx : Click context object.
 * See #accelpressure_t object definition for detailed explanation.
 * @return @li @c 0 - Motion is detected,
 *         @li @c 1 - No motion.
 * @note None.
 */
uint8_t accelpressure_get_mot_det ( accelpressure_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ACCELPRESSURE_H

/*! @} */ // accelpressure

// ------------------------------------------------------------------------ END
