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
 * @file light6.h
 * @brief This file contains API for Light 6 Click Driver.
 */

#ifndef LIGHT6_H
#define LIGHT6_H

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
 * @addtogroup light6 Light 6 Click Driver
 * @brief API for configuring and manipulating Light 6 Click driver.
 * @{
 */

/**
 * @defgroup light6_reg Light 6 Registers List
 * @brief List of registers of Light 6 Click driver.
 */

/**
 * @addtogroup light6_reg
 * @{
 */

/**
 * @brief Light 6 register list.
 * @details Specified register list of Light 6 Click driver.
 */
#define LIGHT6_REG_ALS_CONF                     0x00
#define LIGHT6_REG_ALS_THDH_L                   0x04
#define LIGHT6_REG_ALS_THDH_H                   0x05
#define LIGHT6_REG_ALS_THDL_L                   0x06
#define LIGHT6_REG_ALS_THDL_H                   0x07
#define LIGHT6_REG_ALS_DATA_L                   0x10
#define LIGHT6_REG_ALS_DATA_H                   0x11
#define LIGHT6_REG_IR_DATA_L                    0x12
#define LIGHT6_REG_IR_DATA_H                    0x13
#define LIGHT6_REG_VEML6031X01_ID_L             0x14
#define LIGHT6_REG_VEML6031X01_ID_H             0x15
#define LIGHT6_REG_INT_FLAG                     0x17

/*! @} */ // light6_reg

/**
 * @defgroup light6_set Light 6 Registers Settings
 * @brief Settings for registers of Light 6 Click driver.
 */

/**
 * @addtogroup light6_set
 * @{
 */

/**
 * @brief Light 6 als config setting.
 * @details Specified setting for als config of Light 6 Click driver.
 */
#define LIGHT6_ALS_CONFIG_ALS_IT_3_125_MS       0x0000
#define LIGHT6_ALS_CONFIG_ALS_IT_6_25_MS        0x1000
#define LIGHT6_ALS_CONFIG_ALS_IT_12_5_MS        0x2000
#define LIGHT6_ALS_CONFIG_ALS_IT_25_MS          0x3000
#define LIGHT6_ALS_CONFIG_ALS_IT_50_MS          0x4000
#define LIGHT6_ALS_CONFIG_ALS_IT_100_MS         0x5000
#define LIGHT6_ALS_CONFIG_ALS_IT_200_MS         0x6000
#define LIGHT6_ALS_CONFIG_ALS_IT_400_MS         0x7000
#define LIGHT6_ALS_CONFIG_ALS_IT_MASK           0x7000
#define LIGHT6_ALS_CONFIG_ALS_MODE_AUTO         0x0000
#define LIGHT6_ALS_CONFIG_ALS_MODE_ACTIVE_FORCE 0x0800
#define LIGHT6_ALS_CONFIG_ALS_MODE_MASK         0x0800
#define LIGHT6_ALS_CONFIG_ALS_TRIGGER_OFF       0x0000
#define LIGHT6_ALS_CONFIG_ALS_TRIGGER_ON        0x0400
#define LIGHT6_ALS_CONFIG_ALS_TRIGGER_MASK      0x0400
#define LIGHT6_ALS_CONFIG_ALS_INT_OFF           0x0000
#define LIGHT6_ALS_CONFIG_ALS_INT_ON            0x0200
#define LIGHT6_ALS_CONFIG_ALS_INT_MASK          0x0200
#define LIGHT6_ALS_CONFIG_ALS_ON_TURN_ON        0x0000
#define LIGHT6_ALS_CONFIG_ALS_ON_TURN_OFF       0x0180
#define LIGHT6_ALS_CONFIG_ALS_ON_MASK           0x0180
#define LIGHT6_ALS_CONFIG_ALS_PDDIV_4_4_PD      0x0000
#define LIGHT6_ALS_CONFIG_ALS_PDDIV_1_4_PD      0x0040
#define LIGHT6_ALS_CONFIG_ALS_PDDIV_MASK        0x0040
#define LIGHT6_ALS_CONFIG_ALS_GAIN_X1           0x0000
#define LIGHT6_ALS_CONFIG_ALS_GAIN_X2           0x0008
#define LIGHT6_ALS_CONFIG_ALS_GAIN_X0_66        0x0010
#define LIGHT6_ALS_CONFIG_ALS_GAIN_X0_5         0x0018
#define LIGHT6_ALS_CONFIG_ALS_GAIN_MASK         0x0018
#define LIGHT6_ALS_CONFIG_ALS_PERS_1            0x0000
#define LIGHT6_ALS_CONFIG_ALS_PERS_2            0x0002
#define LIGHT6_ALS_CONFIG_ALS_PERS_4            0x0004
#define LIGHT6_ALS_CONFIG_ALS_PERS_8            0x0006
#define LIGHT6_ALS_CONFIG_ALS_PERS_MASK         0x0006
#define LIGHT6_ALS_CONFIG_ALS_CAL_OFF           0x0000
#define LIGHT6_ALS_CONFIG_ALS_CAL_ON            0x0001
#define LIGHT6_ALS_CONFIG_ALS_CAL_MASK          0x0001

/**
 * @brief Light 6 INT flag register setting.
 * @details Specified setting for INT flag register of Light 6 Click driver.
 */
#define LIGHT6_INT_FLAG_AF_DATA_READY           0x08
#define LIGHT6_INT_FLAG_ALS_IF_L                0x04
#define LIGHT6_INT_FLAG_ALS_IF_H                0x02

/**
 * @brief Light 6 device ID setting.
 * @details Specified setting for device ID of Light 6 Click driver.
 */
#define LIGHT6_DEVICE_ID                        0x0001

/**
 * @brief Light 6 ALS minimal resolution setting.
 * @details Specified setting for ALS minimal resolution of Light 6 Click driver.
 */
#define LIGHT6_ALS_MIN_RES                      0.002568f

/**
 * @brief Light 6 default setting.
 * @details Specified default setting of Light 6 Click driver.
 */
#define LIGHT6_ALS_CONFIG_DEFAULT               ( LIGHT6_ALS_CONFIG_ALS_IT_25_MS | \
                                                  LIGHT6_ALS_CONFIG_ALS_MODE_AUTO | \
                                                  LIGHT6_ALS_CONFIG_ALS_TRIGGER_OFF | \
                                                  LIGHT6_ALS_CONFIG_ALS_INT_OFF | \
                                                  LIGHT6_ALS_CONFIG_ALS_ON_TURN_ON | \
                                                  LIGHT6_ALS_CONFIG_ALS_PDDIV_4_4_PD | \
                                                  LIGHT6_ALS_CONFIG_ALS_GAIN_X1 | \
                                                  LIGHT6_ALS_CONFIG_ALS_PERS_8 | \
                                                  LIGHT6_ALS_CONFIG_ALS_CAL_ON )
#define LIGHT6_THRESHOLD_LOW_DEFAULT            0x0000
#define LIGHT6_THRESHOLD_HIGH_DEFAULT           0x0000

/**
 * @brief Light 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Light 6 Click driver.
 */
#define LIGHT6_DEVICE_ADDRESS                   0x29

/*! @} */ // light6_set

/**
 * @defgroup light6_map Light 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Light 6 Click driver.
 */

/**
 * @addtogroup light6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Light 6 Click to the selected MikroBUS.
 */
#define LIGHT6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // light6_map
/*! @} */ // light6

/**
 * @brief Light 6 Click context object.
 * @details Context object definition of Light 6 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float als_res;              /**< ALS resolution (lux/cnt). */

} light6_t;

/**
 * @brief Light 6 Click configuration object.
 * @details Configuration object definition of Light 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} light6_cfg_t;

/**
 * @brief Light 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHT6_OK = 0,
    LIGHT6_ERROR = -1

} light6_return_value_t;

/*!
 * @addtogroup light6 Light 6 Click Driver
 * @brief API for configuring and manipulating Light 6 Click driver.
 * @{
 */

/**
 * @brief Light 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #light6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void light6_cfg_setup ( light6_cfg_t *cfg );

/**
 * @brief Light 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #light6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light6_init ( light6_t *ctx, light6_cfg_t *cfg );

/**
 * @brief Light 6 default configuration function.
 * @details This function executes a default configuration of Light 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t light6_default_cfg ( light6_t *ctx );

/**
 * @brief Light 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light6_generic_write ( light6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Light 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light6_generic_read ( light6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Light 6 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @return INT pin logic state.
 * @note None.
 */
uint8_t light6_get_int_pin ( light6_t *ctx );

/**
 * @brief Light 6 Check Communication function.
 * @details This function checks the device ID to verify communication with the Light 6 sensor.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t light6_check_communication ( light6_t *ctx );

/**
 * @brief Light 6 Set ALS Configuration function.
 * @details This function sets the ALS (ambient light sensor) configuration register.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[in] config : 16-bit configuration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t light6_set_als_config ( light6_t *ctx, uint16_t config );

/**
 * @brief Light 6 Get ALS Configuration function.
 * @details This function reads the ALS configuration register.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[out] config : Pointer to store the 16-bit configuration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t light6_get_als_config ( light6_t *ctx, uint16_t *config );

/**
 * @brief Light 6 Set ALS Threshold function.
 * @details This function sets the ALS threshold values for interrupt generation.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[in] threshold_low : Lower threshold value.
 * @param[in] threshold_high : Upper threshold value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t light6_set_als_threshold ( light6_t *ctx, uint16_t threshold_low, uint16_t threshold_high );

/**
 * @brief Light 6 Get ALS Threshold function.
 * @details This function reads the ALS threshold values.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[out] threshold_low : Pointer to store the lower threshold value.
 * @param[out] threshold_high : Pointer to store the upper threshold value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t light6_get_als_threshold ( light6_t *ctx, uint16_t *threshold_low, uint16_t *threshold_high );

/**
 * @brief Light 6 Get Interrupt Flag function.
 * @details This function reads the interrupt flag status.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[out] int_flag : Pointer to store the interrupt flag status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t light6_get_int_flag ( light6_t *ctx, uint8_t *int_flag );

/**
 * @brief Light 6 Get Raw Data function.
 * @details This function reads the raw ALS and IR sensor data.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[out] als_data : Pointer to store raw ambient light sensor data.
 * @param[out] ir_data : Pointer to store raw infrared sensor data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t light6_get_raw_data ( light6_t *ctx, uint16_t *als_data, uint16_t *ir_data );

/**
 * @brief Light 6 Get Processed Data function.
 * @details This function reads the raw IR data and ambient light intensity in lux based on raw ALS data.
 * @param[in] ctx : Click context object.
 * See #light6_t object definition for detailed explanation.
 * @param[out] als_data : Pointer to store calculated ambient light intensity (in lux).
 * @param[out] ir_data : Pointer to store raw infrared sensor data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t light6_get_data ( light6_t *ctx, float *als_data, uint16_t *ir_data );

#ifdef __cplusplus
}
#endif
#endif // LIGHT6_H

/*! @} */ // light6

// ------------------------------------------------------------------------ END
