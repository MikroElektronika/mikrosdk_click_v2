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
 * @file ambient24.h
 * @brief This file contains API for Ambient 24 Click Driver.
 */

#ifndef AMBIENT24_H
#define AMBIENT24_H

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
 * @addtogroup ambient24 Ambient 24 Click Driver
 * @brief API for configuring and manipulating Ambient 24 Click driver.
 * @{
 */

/**
 * @defgroup ambient24_reg Ambient 24 Registers List
 * @brief List of registers of Ambient 24 Click driver.
 */

/**
 * @addtogroup ambient24_reg
 * @{
 */

/**
 * @brief Ambient 24 register list.
 * @details Specified register list of Ambient 24 Click driver.
 */
#define AMBIENT24_REG_ALS_CONF                      0x00
#define AMBIENT24_REG_ALS_THDH_L                    0x04
#define AMBIENT24_REG_ALS_THDH_H                    0x05
#define AMBIENT24_REG_ALS_THDL_L                    0x06
#define AMBIENT24_REG_ALS_THDL_H                    0x07
#define AMBIENT24_REG_ALS_DATA_L                    0x10
#define AMBIENT24_REG_ALS_DATA_H                    0x11
#define AMBIENT24_REG_IR_DATA_L                     0x12
#define AMBIENT24_REG_IR_DATA_H                     0x13
#define AMBIENT24_REG_VEML4031X00_ID_L              0x14
#define AMBIENT24_REG_VEML4031X00_ID_H              0x15
#define AMBIENT24_REG_INT_FLAG                      0x17

/*! @} */ // ambient24_reg

/**
 * @defgroup ambient24_set Ambient 24 Registers Settings
 * @brief Settings for registers of Ambient 24 Click driver.
 */

/**
 * @addtogroup ambient24_set
 * @{
 */

/**
 * @brief Ambient 24 als config setting.
 * @details Specified setting for als config of Ambient 24 Click driver.
 */
#define AMBIENT24_ALS_CONFIG_ALS_IT_3_125_MS        0x0000
#define AMBIENT24_ALS_CONFIG_ALS_IT_6_25_MS         0x1000
#define AMBIENT24_ALS_CONFIG_ALS_IT_12_5_MS         0x2000
#define AMBIENT24_ALS_CONFIG_ALS_IT_25_MS           0x3000
#define AMBIENT24_ALS_CONFIG_ALS_IT_50_MS           0x4000
#define AMBIENT24_ALS_CONFIG_ALS_IT_100_MS          0x5000
#define AMBIENT24_ALS_CONFIG_ALS_IT_200_MS          0x6000
#define AMBIENT24_ALS_CONFIG_ALS_IT_400_MS          0x7000
#define AMBIENT24_ALS_CONFIG_ALS_IT_MASK            0x7000
#define AMBIENT24_ALS_CONFIG_ALS_MODE_AUTO          0x0000
#define AMBIENT24_ALS_CONFIG_ALS_MODE_ACTIVE_FORCE  0x0800
#define AMBIENT24_ALS_CONFIG_ALS_MODE_MASK          0x0800
#define AMBIENT24_ALS_CONFIG_ALS_TRIGGER_OFF        0x0000
#define AMBIENT24_ALS_CONFIG_ALS_TRIGGER_ON         0x0400
#define AMBIENT24_ALS_CONFIG_ALS_TRIGGER_MASK       0x0400
#define AMBIENT24_ALS_CONFIG_ALS_INT_OFF            0x0000
#define AMBIENT24_ALS_CONFIG_ALS_INT_ON             0x0200
#define AMBIENT24_ALS_CONFIG_ALS_INT_MASK           0x0200
#define AMBIENT24_ALS_CONFIG_ALS_ON_TURN_ON         0x0000
#define AMBIENT24_ALS_CONFIG_ALS_ON_TURN_OFF        0x0180
#define AMBIENT24_ALS_CONFIG_ALS_ON_MASK            0x0180
#define AMBIENT24_ALS_CONFIG_ALS_PDDIV_4_4_PD       0x0000
#define AMBIENT24_ALS_CONFIG_ALS_PDDIV_1_4_PD       0x0040
#define AMBIENT24_ALS_CONFIG_ALS_PDDIV_MASK         0x0040
#define AMBIENT24_ALS_CONFIG_ALS_GAIN_X1            0x0000
#define AMBIENT24_ALS_CONFIG_ALS_GAIN_X2            0x0008
#define AMBIENT24_ALS_CONFIG_ALS_GAIN_X0_66         0x0010
#define AMBIENT24_ALS_CONFIG_ALS_GAIN_X0_5          0x0018
#define AMBIENT24_ALS_CONFIG_ALS_GAIN_MASK          0x0018
#define AMBIENT24_ALS_CONFIG_ALS_PERS_1             0x0000
#define AMBIENT24_ALS_CONFIG_ALS_PERS_2             0x0002
#define AMBIENT24_ALS_CONFIG_ALS_PERS_4             0x0004
#define AMBIENT24_ALS_CONFIG_ALS_PERS_8             0x0006
#define AMBIENT24_ALS_CONFIG_ALS_PERS_MASK          0x0006
#define AMBIENT24_ALS_CONFIG_ALS_CAL_OFF            0x0000
#define AMBIENT24_ALS_CONFIG_ALS_CAL_ON             0x0001
#define AMBIENT24_ALS_CONFIG_ALS_CAL_MASK           0x0001

/**
 * @brief Ambient 24 INT flag register setting.
 * @details Specified setting for INT flag register of Ambient 24 Click driver.
 */
#define AMBIENT24_INT_FLAG_AF_DATA_READY            0x08
#define AMBIENT24_INT_FLAG_ALS_IF_L                 0x04
#define AMBIENT24_INT_FLAG_ALS_IF_H                 0x02

/**
 * @brief Ambient 24 device ID setting.
 * @details Specified setting for device ID of Ambient 24 Click driver.
 */
#define AMBIENT24_DEVICE_ID                         0x0001

/**
 * @brief Ambient 24 ALS minimal resolution setting.
 * @details Specified setting for ALS minimal resolution of Ambient 24 Click driver.
 */
#define AMBIENT24_ALS_MIN_RES                       0.002568f

/**
 * @brief Ambient 24 default setting.
 * @details Specified default setting of Ambient 24 Click driver.
 */
#define AMBIENT24_ALS_CONFIG_DEFAULT                ( AMBIENT24_ALS_CONFIG_ALS_IT_25_MS | \
                                                      AMBIENT24_ALS_CONFIG_ALS_MODE_AUTO | \
                                                      AMBIENT24_ALS_CONFIG_ALS_TRIGGER_OFF | \
                                                      AMBIENT24_ALS_CONFIG_ALS_INT_OFF | \
                                                      AMBIENT24_ALS_CONFIG_ALS_ON_TURN_ON | \
                                                      AMBIENT24_ALS_CONFIG_ALS_PDDIV_4_4_PD | \
                                                      AMBIENT24_ALS_CONFIG_ALS_GAIN_X1 | \
                                                      AMBIENT24_ALS_CONFIG_ALS_PERS_8 | \
                                                      AMBIENT24_ALS_CONFIG_ALS_CAL_OFF )
#define AMBIENT24_THRESHOLD_LOW_DEFAULT             0x0000
#define AMBIENT24_THRESHOLD_HIGH_DEFAULT            0x0000

/**
 * @brief Ambient 24 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 24 Click driver.
 */
#define AMBIENT24_DEVICE_ADDRESS                    0x29

/*! @} */ // ambient24_set

/**
 * @defgroup ambient24_map Ambient 24 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 24 Click driver.
 */

/**
 * @addtogroup ambient24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 24 Click to the selected MikroBUS.
 */
#define AMBIENT24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // ambient24_map
/*! @} */ // ambient24

/**
 * @brief Ambient 24 Click context object.
 * @details Context object definition of Ambient 24 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float als_res;              /**< ALS resolution (lux/cnt). */

} ambient24_t;

/**
 * @brief Ambient 24 Click configuration object.
 * @details Configuration object definition of Ambient 24 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ambient24_cfg_t;

/**
 * @brief Ambient 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT24_OK = 0,
    AMBIENT24_ERROR = -1

} ambient24_return_value_t;

/*!
 * @addtogroup ambient24 Ambient 24 Click Driver
 * @brief API for configuring and manipulating Ambient 24 Click driver.
 * @{
 */

/**
 * @brief Ambient 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient24_cfg_setup ( ambient24_cfg_t *cfg );

/**
 * @brief Ambient 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient24_init ( ambient24_t *ctx, ambient24_cfg_t *cfg );

/**
 * @brief Ambient 24 default configuration function.
 * @details This function executes a default configuration of Ambient 24
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient24_default_cfg ( ambient24_t *ctx );

/**
 * @brief Ambient 24 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient24_generic_write ( ambient24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Ambient 24 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient24_generic_read ( ambient24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Ambient 24 Check Communication function.
 * @details This function checks the device ID to verify communication with the Ambient 24 sensor.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ambient24_check_communication ( ambient24_t *ctx );

/**
 * @brief Ambient 24 Set ALS Configuration function.
 * @details This function sets the ALS (ambient light sensor) configuration register.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[in] config : 16-bit configuration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ambient24_set_als_config ( ambient24_t *ctx, uint16_t config );

/**
 * @brief Ambient 24 Get ALS Configuration function.
 * @details This function reads the ALS configuration register.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[out] config : Pointer to store the 16-bit configuration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ambient24_get_als_config ( ambient24_t *ctx, uint16_t *config );

/**
 * @brief Ambient 24 Set ALS Threshold function.
 * @details This function sets the ALS threshold values for interrupt generation.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[in] threshold_low : Lower threshold value.
 * @param[in] threshold_high : Upper threshold value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ambient24_set_als_threshold ( ambient24_t *ctx, uint16_t threshold_low, uint16_t threshold_high );

/**
 * @brief Ambient 24 Get ALS Threshold function.
 * @details This function reads the ALS threshold values.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[out] threshold_low : Pointer to store the lower threshold value.
 * @param[out] threshold_high : Pointer to store the upper threshold value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ambient24_get_als_threshold ( ambient24_t *ctx, uint16_t *threshold_low, uint16_t *threshold_high );

/**
 * @brief Ambient 24 Get Interrupt Flag function.
 * @details This function reads the interrupt flag status.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[out] int_flag : Pointer to store the interrupt flag status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ambient24_get_int_flag ( ambient24_t *ctx, uint8_t *int_flag );

/**
 * @brief Ambient 24 Get Raw Data function.
 * @details This function reads the raw ALS and IR sensor data.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[out] als_data : Pointer to store raw ambient light sensor data.
 * @param[out] ir_data : Pointer to store raw infrared sensor data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ambient24_get_raw_data ( ambient24_t *ctx, uint16_t *als_data, uint16_t *ir_data );

/**
 * @brief Ambient 24 Get Processed Data function.
 * @details This function reads the raw IR data and ambient light intensity in lux based on raw ALS data.
 * @param[in] ctx : Click context object.
 * See #ambient24_t object definition for detailed explanation.
 * @param[out] als_data : Pointer to store calculated ambient light intensity (in lux).
 * @param[out] ir_data : Pointer to store raw infrared sensor data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t ambient24_get_data ( ambient24_t *ctx, float *als_data, uint16_t *ir_data );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT24_H

/*! @} */ // ambient24

// ------------------------------------------------------------------------ END
