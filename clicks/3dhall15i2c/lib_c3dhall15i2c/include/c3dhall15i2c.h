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
 * @file c3dhall15i2c.h
 * @brief This file contains API for 3D Hall 15 I2C Click Driver.
 */

#ifndef C3DHALL15I2C_H
#define C3DHALL15I2C_H

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
 * @addtogroup c3dhall15i2c 3D Hall 15 I2C Click Driver
 * @brief API for configuring and manipulating 3D Hall 15 I2C Click driver.
 * @{
 */

/**
 * @defgroup c3dhall15i2c_reg 3D Hall 15 I2C Registers List
 * @brief List of registers of 3D Hall 15 I2C Click driver.
 */

/**
 * @addtogroup c3dhall15i2c_reg
 * @{
 */

/**
 * @brief 3D Hall 15 I2C register list.
 * @details Specified register list of 3D Hall 15 I2C Click driver.
 */
#define C3DHALL15I2C_REG_NOP                            0x00
#define C3DHALL15I2C_REG_INDIRECT_WR_ADDRESS            0x02
#define C3DHALL15I2C_REG_INDIRECT_WR_DATA_MSB           0x04
#define C3DHALL15I2C_REG_INDIRECT_WR_DATA_LSB           0x06
#define C3DHALL15I2C_REG_INDIRECT_WR_STATUS             0x08
#define C3DHALL15I2C_REG_INDIRECT_RD_ADDRESS            0x0A
#define C3DHALL15I2C_REG_INDIRECT_RD_STATUS             0x0C
#define C3DHALL15I2C_REG_INDIRECT_RD_DATA_MSB           0x0E
#define C3DHALL15I2C_REG_INDIRECT_RD_DATA_LSB           0x10
#define C3DHALL15I2C_REG_I2C_LOOP_BACK                  0x12
#define C3DHALL15I2C_REG_I2C_X_Y_8B                     0x14
#define C3DHALL15I2C_REG_I2C_T_Z_8B                     0x16
#define C3DHALL15I2C_REG_I2C_ANGLE_RADIUSSQ_8B          0x18
#define C3DHALL15I2C_REG_I2C_SIN_COS_8B                 0x1A
#define C3DHALL15I2C_REG_TEMPERATURE                    0x1C
#define C3DHALL15I2C_REG_X_CHANNEL                      0x1E
#define C3DHALL15I2C_REG_Y_CHANNEL                      0x20
#define C3DHALL15I2C_REG_Z_CHANNEL                      0x22
#define C3DHALL15I2C_REG_ANGLE                          0x24
#define C3DHALL15I2C_REG_RADIUS                         0x26
#define C3DHALL15I2C_REG_SINE                           0x28
#define C3DHALL15I2C_REG_COSINE                         0x2A
#define C3DHALL15I2C_REG_X_RAW_FILT_OUT                 0x2C
#define C3DHALL15I2C_REG_Y_RAW_FILT_OUT                 0x2E
#define C3DHALL15I2C_REG_Z_RAW_FILT_OUT                 0x30
#define C3DHALL15I2C_REG_CTRL1                          0x32
#define C3DHALL15I2C_REG_I2C_LOOPB_CONF                 0x34
#define C3DHALL15I2C_REG_CTRL2                          0x36
#define C3DHALL15I2C_REG_CTRL3                          0x38
#define C3DHALL15I2C_REG_CTRL4                          0x3A
#define C3DHALL15I2C_REG_RESERVED                       0x3C
#define C3DHALL15I2C_REG_ACCESS_KEY                     0x3E

/*! @} */ // c3dhall15i2c_reg

/**
 * @defgroup c3dhall15i2c_set 3D Hall 15 I2C Registers Settings
 * @brief Settings for registers of 3D Hall 15 I2C Click driver.
 */

/**
 * @addtogroup c3dhall15i2c_set
 * @{
 */

/**
 * @brief 3D Hall 15 I2C CTRL1 register setting.
 * @details Specified setting for CTRL1 register of 3D Hall 15 I2C Click driver.
 */
#define C3DHALL15I2C_CTRL1_START_SAMPLE_CLEAR           0x0000
#define C3DHALL15I2C_CTRL1_START_SAMPLE_SET             0x1000
#define C3DHALL15I2C_CTRL1_START_SAMPLE_MASK            0x1000
#define C3DHALL15I2C_CTRL1_INTERRUPT_FLAG_CLEAR         0x0000
#define C3DHALL15I2C_CTRL1_INTERRUPT_FLAG_SET           0x0800
#define C3DHALL15I2C_CTRL1_INTERRUPT_FLAG_MASK          0x0800
#define C3DHALL15I2C_CTRL1_STATUS_READY_CLEAR           0x0000
#define C3DHALL15I2C_CTRL1_STATUS_READY_SET             0x0400
#define C3DHALL15I2C_CTRL1_STATUS_READY_MASK            0x0400
#define C3DHALL15I2C_CTRL1_SLEEP_CNT_0_68_MS            0x0000
#define C3DHALL15I2C_CTRL1_SLEEP_CNT_1_36_MS            0x0010
#define C3DHALL15I2C_CTRL1_SLEEP_CNT_6_82_MS            0x0020
#define C3DHALL15I2C_CTRL1_SLEEP_CNT_13_64_MS           0x0030
#define C3DHALL15I2C_CTRL1_SLEEP_CNT_68_18_MS           0x0040
#define C3DHALL15I2C_CTRL1_SLEEP_CNT_136_36_MS          0x0050
#define C3DHALL15I2C_CTRL1_SLEEP_CNT_681_82_MS          0x0060
#define C3DHALL15I2C_CTRL1_SLEEP_CNT_1363_64_MS         0x0070
#define C3DHALL15I2C_CTRL1_SLEEP_CNT_MASK               0x0070
#define C3DHALL15I2C_CTRL1_OP_MODE_ACTIVE               0x0000
#define C3DHALL15I2C_CTRL1_OP_MODE_ACTIVE_INT           0x0002
#define C3DHALL15I2C_CTRL1_OP_MODE_ACTIVE_SAM           0x0004
#define C3DHALL15I2C_CTRL1_OP_MODE_SLEEP                0x0006
#define C3DHALL15I2C_CTRL1_OP_MODE_SLEEP_SAM            0x0008
#define C3DHALL15I2C_CTRL1_OP_MODE_LPDCM_INT            0x000A
#define C3DHALL15I2C_CTRL1_OP_MODE_LPDCM                0x000C
#define C3DHALL15I2C_CTRL1_OP_MODE_MASK                 0x000E

/**
 * @brief 3D Hall 15 I2C CTRL2 register setting.
 * @details Specified setting for CTRL2 register of 3D Hall 15 I2C Click driver.
 */
#define C3DHALL15I2C_CTRL2_INT_THR_MSB_DIR_MASK         0x0F00
#define C3DHALL15I2C_CTRL2_INT_THR_LSB_DIR_MASK         0x00FF

/**
 * @brief 3D Hall 15 I2C CTRL3 register setting.
 * @details Specified setting for CTRL3 register of 3D Hall 15 I2C Click driver.
 */
#define C3DHALL15I2C_CTRL3_AFE_CHAN_DIS_Z_DIR_EN        0x0000
#define C3DHALL15I2C_CTRL3_AFE_CHAN_DIS_Z_DIR_DIS       0x2000
#define C3DHALL15I2C_CTRL3_AFE_CHAN_DIS_Z_DIR_MASK      0x2000
#define C3DHALL15I2C_CTRL3_AFE_CHAN_DIS_Y_DIR_EN        0x0000
#define C3DHALL15I2C_CTRL3_AFE_CHAN_DIS_Y_DIR_DIS       0x1000
#define C3DHALL15I2C_CTRL3_AFE_CHAN_DIS_Y_DIR_MASK      0x1000
#define C3DHALL15I2C_CTRL3_AFE_CHAN_DIS_X_DIR_EN        0x0000
#define C3DHALL15I2C_CTRL3_AFE_CHAN_DIS_X_DIR_DIS       0x0800
#define C3DHALL15I2C_CTRL3_AFE_CHAN_DIS_X_DIR_MASK      0x0800
#define C3DHALL15I2C_CTRL3_POL_F_Z_DIR_NORMAL           0x0000
#define C3DHALL15I2C_CTRL3_POL_F_Z_DIR_INVERTED         0x0400
#define C3DHALL15I2C_CTRL3_POL_F_Z_DIR_MASK             0x0400
#define C3DHALL15I2C_CTRL3_POL_F_Y_DIR_NORMAL           0x0000
#define C3DHALL15I2C_CTRL3_POL_F_Y_DIR_INVERTED         0x0200
#define C3DHALL15I2C_CTRL3_POL_F_Y_DIR_MASK             0x0200
#define C3DHALL15I2C_CTRL3_POL_F_X_DIR_NORMAL           0x0000
#define C3DHALL15I2C_CTRL3_POL_F_X_DIR_INVERTED         0x0100
#define C3DHALL15I2C_CTRL3_POL_F_X_DIR_MASK             0x0100
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_X                0x0000
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_Y                0x0008
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_Z                0x0010
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_ABS_X            0x0018
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_ABS_Y            0x0020
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_ABS_Z            0x0028
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_TEMP             0x0030
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_ANGLE            0x0038
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_RADIUS           0x0040
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_NEW_SAMPLE       0x0048
#define C3DHALL15I2C_CTRL3_INT_SEL_DIR_MASK             0x0078
#define C3DHALL15I2C_CTRL3_INT_SIGN_DIR_LESS            0x0000
#define C3DHALL15I2C_CTRL3_INT_SIGN_DIR_GREATER         0x0004
#define C3DHALL15I2C_CTRL3_INT_SIGN_DIR_MASK            0x0004
#define C3DHALL15I2C_CTRL3_INT_FLAG_LATCH_DIR_DIS       0x0000
#define C3DHALL15I2C_CTRL3_INT_FLAG_LATCH_DIR_EN        0x0002
#define C3DHALL15I2C_CTRL3_INT_FLAG_LATCH_DIR_MASK      0x0002
#define C3DHALL15I2C_CTRL3_SAMPLE_INT_POL_DIR_LOW       0x0001
#define C3DHALL15I2C_CTRL3_SAMPLE_INT_POL_DIR_HIGH      0x0001
#define C3DHALL15I2C_CTRL3_SAMPLE_INT_POL_DIR_MASK      0x0001

/**
 * @brief 3D Hall 15 I2C CTRL4 register setting.
 * @details Specified setting for CTRL4 register of 3D Hall 15 I2C Click driver.
 */
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_LPM_DIR_195_5_HZ  0x0000
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_LPM_DIR_391_HZ    0x0100
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_LPM_DIR_782_HZ    0x0200
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_LPM_DIR_1564_HZ   0x0300
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_LPM_DIR_3128_HZ   0x0400
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_LPM_DIR_6256_HZ   0x0500
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_LPM_DIR_12512_HZ  0x0600
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_LPM_DIR_MASK      0x0700
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_DIR_195_5_HZ      0x0000
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_DIR_391_HZ        0x0010
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_DIR_782_HZ        0x0020
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_DIR_1564_HZ       0x0030
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_DIR_3128_HZ       0x0040
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_DIR_6256_HZ       0x0050
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_DIR_12512_HZ      0x0060
#define C3DHALL15I2C_CTRL4_CIC_BW_SEL_DIR_MASK          0x0070
#define C3DHALL15I2C_CTRL4_CORDIC_POL_DIR_NORMAL        0x0000
#define C3DHALL15I2C_CTRL4_CORDIC_POL_DIR_INVERTED      0x0008
#define C3DHALL15I2C_CTRL4_CORDIC_POL_DIR_MASK          0x0008
#define C3DHALL15I2C_CTRL4_CORDIC_SEL_DIR_COS_X_SINE_Y  0x0000
#define C3DHALL15I2C_CTRL4_CORDIC_SEL_DIR_COS_X_SINE_Z  0x0001
#define C3DHALL15I2C_CTRL4_CORDIC_SEL_DIR_COS_Y_SINE_Z  0x0002
#define C3DHALL15I2C_CTRL4_CORDIC_SEL_DIR_COS_Y_SINE_X  0x0003
#define C3DHALL15I2C_CTRL4_CORDIC_SEL_DIR_COS_Z_SINE_X  0x0004
#define C3DHALL15I2C_CTRL4_CORDIC_SEL_DIR_COS_Z_SINE_Y  0x0005
#define C3DHALL15I2C_CTRL4_CORDIC_SEL_DIR_MASK          0x0007

/**
 * @brief 3D Hall 15 I2C data calculation setting.
 * @details Specified setting for data calculation of 3D Hall 15 I2C Click driver.
 */
#define C3DHALL15I2C_TEMP_SIGN_BIT                      0x0800
#define C3DHALL15I2C_TEMP_SIGN_MASK                     0xF000
#define C3DHALL15I2C_TEMP_RES                           8.052
#define C3DHALL15I2C_TEMP_OFFSET                        25.0
#define C3DHALL15I2C_XYZ_SIGN_BIT                       0x4000
#define C3DHALL15I2C_XYZ_SIGN_MASK                      0x8000
#define C3DHALL15I2C_XYZ_RES_MT                         268.0
#define C3DHALL15I2C_ANGLE_RES_DEG                      0.0109863

/**
 * @brief 3D Hall 15 I2C device address setting.
 * @details Specified setting for device slave address selection of
 * 3D Hall 15 I2C Click driver.
 */
#define C3DHALL15I2C_DEVICE_ADDRESS                     0x65

/*! @} */ // c3dhall15i2c_set

/**
 * @defgroup c3dhall15i2c_map 3D Hall 15 I2C MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 15 I2C Click driver.
 */

/**
 * @addtogroup c3dhall15i2c_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 15 I2C Click to the selected MikroBUS.
 */
#define C3DHALL15I2C_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sample = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3dhall15i2c_map
/*! @} */ // c3dhall15i2c

/**
 * @brief 3D Hall 15 I2C Click context object.
 * @details Context object definition of 3D Hall 15 I2C Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sample;           /**< Start sample pin (active low). */

    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} c3dhall15i2c_t;

/**
 * @brief 3D Hall 15 I2C Click configuration object.
 * @details Configuration object definition of 3D Hall 15 I2C Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t sample;              /**< Start sample pin (active low). */
    pin_name_t int_pin;             /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} c3dhall15i2c_cfg_t;

/**
 * @brief 3D Hall 15 I2C Click data object.
 * @details Data object definition of 3D Hall 15 I2C Click driver.
 */
typedef struct
{
    float temperature;              /**< Temperature in degC. */
    float x;                        /**< X axis (mT). */
    float y;                        /**< Y axis (mT). */
    float z;                        /**< Z axis (mT). */
    float angle;                    /**< Angle in degrees. */
    float magnitude;                /**< Magnitude. */
    
} c3dhall15i2c_data_t;

/**
 * @brief 3D Hall 15 I2C Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL15I2C_OK = 0,
    C3DHALL15I2C_ERROR = -1,
    C3DHALL15I2C_DATA_NOT_READY = -2

} c3dhall15i2c_return_value_t;

/*!
 * @addtogroup c3dhall15i2c 3D Hall 15 I2C Click Driver
 * @brief API for configuring and manipulating 3D Hall 15 I2C Click driver.
 * @{
 */

/**
 * @brief 3D Hall 15 I2C configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall15i2c_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3dhall15i2c_cfg_setup ( c3dhall15i2c_cfg_t *cfg );

/**
 * @brief 3D Hall 15 I2C initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall15i2c_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall15i2c_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall15i2c_init ( c3dhall15i2c_t *ctx, c3dhall15i2c_cfg_t *cfg );

/**
 * @brief 3D Hall 15 I2C default configuration function.
 * @details This function executes a default configuration of 3D Hall 15 I2C
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall15i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c3dhall15i2c_default_cfg ( c3dhall15i2c_t *ctx );

/**
 * @brief 3D Hall 15 I2C write register function.
 * @details This function writes a 16-bit data to the specified register.
 * @param[in] ctx : Click context object.
 * See #c3dhall15i2c_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c3dhall15i2c_write_reg ( c3dhall15i2c_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief 3D Hall 15 I2C read register function.
 * @details This function reads a 16-bit data from the specified register.
 * @param[in] ctx : Click context object.
 * See #c3dhall15i2c_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to a variable where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t c3dhall15i2c_read_reg ( c3dhall15i2c_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief 3D Hall 15 I2C set sample pin function.
 * @details This function sets the state of the SAMPLE pin.
 * @param[in] ctx : Click context object.
 * See #c3dhall15i2c_t object definition for detailed explanation.
 * @param[in] state : Pin logic state (0 - Low, 1 - High).
 * @note None.
 */
void c3dhall15i2c_set_sample_pin ( c3dhall15i2c_t *ctx, uint8_t state );

/**
 * @brief 3D Hall 15 I2C get INT pin function.
 * @details This function reads the state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #c3dhall15i2c_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3dhall15i2c_get_int_pin ( c3dhall15i2c_t *ctx );

/**
 * @brief 3D Hall 15 I2C start measurement function.
 * @details This function triggers a measurement by toggling the SAMPLE pin.
 * @param[in] ctx : Click context object.
 * See #c3dhall15i2c_t object definition for detailed explanation.
 * @note The SAMPLE pin is toggled from LOW to HIGH with a 1 ms delay between transitions.
 */
void c3dhall15i2c_start_measurement ( c3dhall15i2c_t *ctx );

/**
 * @brief 3D Hall 15 I2C read data function.
 * @details This function reads the temperature, X, Y, Z magnetic field, angle, and magnitude from the device.
 * @param[in] ctx : Click context object.
 * See #c3dhall15i2c_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the structure where read data will be stored.
 * See #c3dhall15i2c_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note This function performs a measurement trigger before reading the data.
 */
err_t c3dhall15i2c_read_data ( c3dhall15i2c_t *ctx, c3dhall15i2c_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // C3DHALL15I2C_H

/*! @} */ // c3dhall15i2c

// ------------------------------------------------------------------------ END
