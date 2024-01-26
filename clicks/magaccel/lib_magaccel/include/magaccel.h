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
 * @file magaccel.h
 * @brief This file contains API for MagAccel Click Driver.
 */

#ifndef MAGACCEL_H
#define MAGACCEL_H

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
 * @addtogroup magaccel MagAccel Click Driver
 * @brief API for configuring and manipulating MagAccel Click driver.
 * @{
 */

/**
 * @defgroup magaccel_reg MagAccel Registers List
 * @brief List of registers of MagAccel Click driver.
 */

/**
 * @addtogroup magaccel_reg
 * @{
 */

/**
 * @brief MagAccel description register.
 * @details Specified register for description of MagAccel Click driver.
 */
#define MAGACCEL_REG_INT_STATUS           0x00
#define MAGACCEL_REG_TEMP_OUT             0x01
#define MAGACCEL_REG_VECM_LSB             0x02
#define MAGACCEL_REG_VECM_MSB             0x03
#define MAGACCEL_REG_OUT_X_LSB            0x04
#define MAGACCEL_REG_OUT_X_MSB            0x05
#define MAGACCEL_REG_OUT_Y_LSB            0x06
#define MAGACCEL_REG_OUT_Y_MSB            0x07
#define MAGACCEL_REG_OUT_Z_LSB            0x08
#define MAGACCEL_REG_OUT_Z_MSB            0x09
#define MAGACCEL_REG_BUF_STATUS           0x0B
#define MAGACCEL_REG_BUF_X_LSB            0x0C
#define MAGACCEL_REG_BUF_X_MSB            0x0D
#define MAGACCEL_REG_BUF_Y_LSB            0x0E
#define MAGACCEL_REG_BUF_Y_MSB            0x0F
#define MAGACCEL_REG_BUF_Z_LSB            0x10
#define MAGACCEL_REG_BUF_Z_MSB            0x11
#define MAGACCEL_REG_PROD_REV             0x12
#define MAGACCEL_REG_WHO_AM_I             0x13
#define MAGACCEL_REG_SYS_MODE             0x14
#define MAGACCEL_REG_SENS_CONFIG1         0x15
#define MAGACCEL_REG_SENS_CONFIG2         0x16
#define MAGACCEL_REG_SENS_CONFIG3         0x17
#define MAGACCEL_REG_SENS_CONFIG4         0x18
#define MAGACCEL_REG_SENS_CONFIG5         0x19
#define MAGACCEL_REG_WAKE_IDLE_LSB        0x1A
#define MAGACCEL_REG_WAKE_IDLE_MSB        0x1B
#define MAGACCEL_REG_SLEEP_IDLE_LSB       0x1C
#define MAGACCEL_REG_SLEEP_IDLE_MSB       0x1D
#define MAGACCEL_REG_ASLP_COUNT_LSB       0x1E
#define MAGACCEL_REG_ASLP_COUNT_MSB       0x1F
#define MAGACCEL_REG_INT_EN               0x20
#define MAGACCEL_REG_INT_PIN_SEL          0x21
#define MAGACCEL_REG_OFF_X                0x22
#define MAGACCEL_REG_OFF_Y                0x23
#define MAGACCEL_REG_OFF_Z                0x24
#define MAGACCEL_REG_BUF_CONFIG1          0x26
#define MAGACCEL_REG_BUF_CONFIG2          0x27
#define MAGACCEL_REG_ORIENT_STATUS        0x28
#define MAGACCEL_REG_ORIENT_CONFIG        0x29
#define MAGACCEL_REG_ORIENT_DBCOUNT       0x2A
#define MAGACCEL_REG_ORIENT_BF_ZCOMP      0x2B
#define MAGACCEL_REG_ORIENT_THS_REG       0x2C
#define MAGACCEL_REG_SDCD_INT_SRC1        0x2D
#define MAGACCEL_REG_SDCD_INT_SRC2        0x2E
#define MAGACCEL_REG_SDCD_CONFIG1         0x2F
#define MAGACCEL_REG_SDCD_CONFIG2         0x30
#define MAGACCEL_REG_SDCD_OT_DBCNT        0x31
#define MAGACCEL_REG_SDCD_WT_DBCNT        0x32
#define MAGACCEL_REG_SDCD_LTHS_LSB        0x33
#define MAGACCEL_REG_SDCD_LTHS_MSB        0x34
#define MAGACCEL_REG_SDCD_UTHS_LSB        0x35
#define MAGACCEL_REG_SDCD_UTHS_MSB        0x36
#define MAGACCEL_REG_SELF_TEST_CONFIG1    0x37
#define MAGACCEL_REG_SELF_TEST_CONFIG2    0x38

/*! @} */ // magaccel_reg

/**
 * @defgroup magaccel_set MagAccel Registers Settings
 * @brief Settings for registers of MagAccel Click driver.
 */

/**
 * @addtogroup magaccel_set
 * @{
 */

/**
 * @brief MagAccel nominal sensitivity data values.
 * @details Nominal sensitivity data values of MagAccel Click driver.
 */
#define MAGACCEL_SRC_BOOT_COMPLETED       0x01

/**
 * @brief MagAccel device ID data values.
 * @details Device ID data values of MagAccel Click driver.
 */
#define MAGACCEL_DEVICE_ID_VAL            0x86

/**
 * @brief MagAccel SW reset bit mask data values.
 * @details SW reset bit mask data values of MagAccel Click driver.
 */
#define MAGACCEL_SW_RESET_BIT_MASK        0x80

/**
 * @brief MagAccel operating mode data values.
 * @details Operating mode data values of MagAccel Click driver.
 */
#define MAGACCEL_OP_MODE_STANDBY          0x00
#define MAGACCEL_OP_MODE_ACTIVE           0x01
#define MAGACCEL_OP_MODE_BIT_MASK         0xFE

/**
 * @brief MagAccel full-scale measurement range (FSR) selection.
 * @details Full-scale measurement range (FSR) selection of MagAccel Click driver.
 */
#define MAGACCEL_FSR_SEL_2G               0x00
#define MAGACCEL_FSR_SEL_4G               0x01
#define MAGACCEL_FSR_SEL_8G               0x02
#define MAGACCEL_FSR_SEL_16G              0x03
#define MAGACCEL_FSR_SEL_BIT_MASK         0xF9

/**
 * @brief MagAccel data-ready interrupt output enable data values.
 * @details Data-ready interrupt output enable data values of MagAccel Click driver.
 */
#define MAGACCEL_INT_EN_DRDY_DIS          0x00
#define MAGACCEL_INT_EN_DRDY_EN           0x80

/**
 * @brief MagAccel data-ready and magnetic field detection data values.
 * @details Data-ready and magnetic field detection data values of MagAccel Click driver.
 */
#define MAGACCEL_DATA_READY               0
#define MAGACCEL_DET_MAG_FIELD            0

/**
 * @brief MagAccel nominal sensitivity data values.
 * @details Nominal sensitivity data values of MagAccel Click driver.
 */
#define MAGACCEL_FSR_SENS_VAL_2G          0.98f
#define MAGACCEL_FSR_SENS_VAL_4G          1.95f
#define MAGACCEL_FSR_SENS_VAL_8G          3.91f
#define MAGACCEL_FSR_SENS_VAL_16G         7.81f


/**
 * @brief MagAccel device address setting.
 * @details Specified setting for device slave address selection of
 * MagAccel Click driver.
 */
#define MAGACCEL_DEVICE_ADDRESS           0x18

/*! @} */ // magaccel_set

/**
 * @defgroup magaccel_map MagAccel MikroBUS Map
 * @brief MikroBUS pin mapping of MagAccel Click driver.
 */

/**
 * @addtogroup magaccel_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MagAccel Click to the selected MikroBUS.
 */
#define MAGACCEL_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.fld = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.mot = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // magaccel_map
/*! @} */ // magaccel

/**
 * @brief MagAccel Click context object.
 * @details Context object definition of MagAccel Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t fld;    /**< Magnetic field detection pin. */
    digital_in_t mot;    /**< Mode-dependent multifunction pin. */

    // Modules
    i2c_master_t i2c;    /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

    // Sensitivity
    float sensitivity;       /**< Nominal sensitivity resolution. */

} magaccel_t;

/**
 * @brief MagAccel Click configuration object.
 * @details Configuration object definition of MagAccel Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t fld;    /**< Magnetic field detection pin. */
    pin_name_t mot;    /**< Mode-dependent multifunction pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} magaccel_cfg_t;

/**
 * @brief MagAccel Click axes data.
 * @details Axes data object definition of MagAccel Click driver.
 */
typedef struct
{
    float x;    /**< X-axis: convert raw-data into engineering units. */
    float y;    /**< Y-axis: convert raw-data into engineering units. */
    float z;    /**< Z-axis: convert raw-data into engineering units. */

} magaccel_axes_t;

/**
 * @brief MagAccel Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGACCEL_OK = 0,
    MAGACCEL_ERROR = -1

} magaccel_return_value_t;

/*!
 * @addtogroup magaccel MagAccel Click Driver
 * @brief API for configuring and manipulating MagAccel Click driver.
 * @{
 */

/**
 * @brief MagAccel configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magaccel_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magaccel_cfg_setup ( magaccel_cfg_t *cfg );

/**
 * @brief MagAccel initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magaccel_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_init ( magaccel_t *ctx, magaccel_cfg_t *cfg );

/**
 * @brief MagAccel default configuration function.
 * @details This function executes a default configuration of MagAccel
 * click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t magaccel_default_cfg ( magaccel_t *ctx );

/**
 * @brief MagAccel I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_generic_write ( magaccel_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief MagAccel I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_generic_read ( magaccel_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief MagAccel get device ID function.
 * @details This function reads the device identification data
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the MagAccel Click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @param[out] device_id : Device identification.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_get_device_id ( magaccel_t *ctx, uint8_t *device_id );

/**
 * @brief MagAccel get status function.
 * @details This function reads the status data
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the MagAccel Click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_get_status ( magaccel_t *ctx, uint8_t *status );

/**
 * @brief MagAccel soft reset function.
 * @details This function trigger the soft reset sequence
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the MagAccel Click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_sw_reset ( magaccel_t *ctx );

/**
 * @brief MagAccel set operating mode function.
 * @details This function sets the desired operating mode
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the MagAccel Click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @param[in] op_mode : Standby/Active mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_set_op_mode ( magaccel_t *ctx, uint8_t op_mode );

/**
 * @brief MagAccel set FSR function.
 * @details This function sets the desired full-scale measurement range
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the MagAccel Click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @param[in] op_mode : Standby/Active mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_set_fsr ( magaccel_t *ctx, uint8_t fsr );

/**
 * @brief MagAccel enable data ready function.
 * @details This function is used to enable data-ready interrupt output
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the MagAccel Click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_en_data_ready ( magaccel_t *ctx );

/**
 * @brief MagAccel get the accel sensor axes function.
 * @details This function reads the accelerometer sensor axes data 
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the MagAccel Click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @param[out] axes : Linear acceleration output data object (mg).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magaccel_get_axes_data ( magaccel_t *ctx, magaccel_axes_t *axes );

/**
 * @brief MagAccel get data ready function.
 * @details This function checks if data is ready by reading the states of the MOT (INT) pin
 * of the FXLS8974, 3-Axis Low-g Accelerometer on the MagAccel Click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @return @li @c 0 - The data is ready,
 *         @li @c 1 - Data not ready.
 * @note None.
 */
uint8_t magaccel_check_data_ready ( magaccel_t *ctx );

/**
 * @brief MagAccel checks the magnetic field function.
 * @details This function checks the magnetic field y by reading the states of the FLD (AN) pin
 * of the NMH1000, Magnetic switch on the MagAccel Click board.
 * @param[in] ctx : Click context object.
 * See #magaccel_t object definition for detailed explanation.
 * @return @li @c 0 - Presence of a magnetic field,
 *         @li @c 1 - Absence of a magnetic field.
 * @note None.
 */
uint8_t magaccel_check_mag_field ( magaccel_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MAGACCEL_H

/*! @} */ // magaccel

// ------------------------------------------------------------------------ END
