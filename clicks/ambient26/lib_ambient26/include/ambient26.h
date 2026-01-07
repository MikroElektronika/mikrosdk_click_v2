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
 * @file ambient26.h
 * @brief This file contains API for Ambient 26 Click Driver.
 */

#ifndef AMBIENT26_H
#define AMBIENT26_H

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
 * @addtogroup ambient26 Ambient 26 Click Driver
 * @brief API for configuring and manipulating Ambient 26 Click driver.
 * @{
 */

/**
 * @defgroup ambient26_reg Ambient 26 Registers List
 * @brief List of registers of Ambient 26 Click driver.
 */

/**
 * @addtogroup ambient26_reg
 * @{
 */

/**
 * @brief Ambient 26 register list.
 * @details Specified register list of Ambient 26 Click driver.
 */
#define AMBIENT26_REG_MAIN_CTRL             0x00
#define AMBIENT26_REG_ALS_UVS_MEAS_RATE     0x04
#define AMBIENT26_REG_ALS_UVS_GAIN          0x05
#define AMBIENT26_REG_PART_ID               0x06
#define AMBIENT26_REG_MAIN_STATUS           0x07
#define AMBIENT26_REG_ALS_DATA_0            0x0D
#define AMBIENT26_REG_ALS_DATA_1            0x0E
#define AMBIENT26_REG_ALS_DATA_2            0x0F
#define AMBIENT26_REG_UVS_DATA_0            0x10
#define AMBIENT26_REG_UVS_DATA_1            0x11
#define AMBIENT26_REG_UVS_DATA_2            0x12
#define AMBIENT26_REG_INT_CFG               0x19
#define AMBIENT26_REG_INT_PST               0x1A
#define AMBIENT26_REG_ALS_UVS_THRES_UP_0    0x21
#define AMBIENT26_REG_ALS_UVS_THRES_UP_1    0x22
#define AMBIENT26_REG_ALS_UVS_THRES_UP_2    0x23
#define AMBIENT26_REG_ALS_UVS_THRES_LOW_0   0x24
#define AMBIENT26_REG_ALS_UVS_THRES_LOW_1   0x25
#define AMBIENT26_REG_ALS_UVS_THRES_LOW_2   0x26

/*! @} */ // ambient26_reg

/**
 * @defgroup ambient26_set Ambient 26 Registers Settings
 * @brief Settings for registers of Ambient 26 Click driver.
 */

/**
 * @addtogroup ambient26_set
 * @{
 */

/**
 * @brief Ambient 26 MAIN_CTRL register setting.
 * @details Specified setting for MAIN_CTRL register of Ambient 26 Click driver.
 */
#define AMBIENT26_MAIN_CTRL_SW_RESET        0x10
#define AMBIENT26_MAIN_CTRL_UVS_MODE_ALS    0x00
#define AMBIENT26_MAIN_CTRL_UVS_MODE_UVS    0x08
#define AMBIENT26_MAIN_CTRL_UVS_MODE_MASK   0x08
#define AMBIENT26_MAIN_CTRL_SENSOR_STANDBY  0x00
#define AMBIENT26_MAIN_CTRL_SENSOR_ACTIVE   0x02
#define AMBIENT26_MAIN_CTRL_SENSOR_MASK     0x02

/**
 * @brief Ambient 26 ALS_UVS_MEAS_RATE register setting.
 * @details Specified setting for ALS_UVS_MEAS_RATE register of Ambient 26 Click driver.
 */
#define AMBIENT26_ALS_UVS_RES_20_BIT        0x00
#define AMBIENT26_ALS_UVS_RES_19_BIT        0x10
#define AMBIENT26_ALS_UVS_RES_18_BIT        0x20
#define AMBIENT26_ALS_UVS_RES_17_BIT        0x30
#define AMBIENT26_ALS_UVS_RES_16_BIT        0x40
#define AMBIENT26_ALS_UVS_RES_13_BIT        0x50
#define AMBIENT26_ALS_UVS_RES_MASK          0x70
#define AMBIENT26_ALS_UVS_RATE_25_MS        0x00
#define AMBIENT26_ALS_UVS_RATE_50_MS        0x01
#define AMBIENT26_ALS_UVS_RATE_100_MS       0x02
#define AMBIENT26_ALS_UVS_RATE_200_MS       0x03
#define AMBIENT26_ALS_UVS_RATE_500_MS       0x04
#define AMBIENT26_ALS_UVS_RATE_1000_MS      0x05
#define AMBIENT26_ALS_UVS_RATE_2000_MS      0x06
#define AMBIENT26_ALS_UVS_RATE_MASK         0x07

/**
 * @brief Ambient 26 ALS_UVS_GAIN register setting.
 * @details Specified setting for ALS_UVS_GAIN register of Ambient 26 Click driver.
 */
#define AMBIENT26_ALS_UVS_GAIN_1            0x00
#define AMBIENT26_ALS_UVS_GAIN_3            0x01
#define AMBIENT26_ALS_UVS_GAIN_6            0x02
#define AMBIENT26_ALS_UVS_GAIN_9            0x03
#define AMBIENT26_ALS_UVS_GAIN_18           0x04
#define AMBIENT26_ALS_UVS_GAIN_MASK         0x07

/**
 * @brief Ambient 26 PART_ID register setting.
 * @details Specified setting for PART_ID register of Ambient 26 Click driver.
 */
#define AMBIENT26_PART_ID                   0xB0
#define AMBIENT26_PART_ID_MASK              0xF0
#define AMBIENT26_REVISION_ID               0x02
#define AMBIENT26_REVISION_ID_MASK          0x0F

/**
 * @brief Ambient 26 MAIN_STATUS register setting.
 * @details Specified setting for MAIN_STATUS register of Ambient 26 Click driver.
 */
#define AMBIENT26_MAIN_STATUS_POWER_ON      0x20
#define AMBIENT26_MAIN_STATUS_INTERRUPT     0x10
#define AMBIENT26_MAIN_STATUS_DATA          0x08

/**
 * @brief Ambient 26 INT_CFG register setting.
 * @details Specified setting for INT_CFG register of Ambient 26 Click driver.
 */
#define AMBIENT26_INT_CFG_LS_INT_SEL_ALS    0x10
#define AMBIENT26_INT_CFG_LS_INT_SEL_UVS    0x30
#define AMBIENT26_INT_CFG_LS_INT_SEL_MASK   0x30
#define AMBIENT26_INT_CFG_LS_INT_EN_DISABLE 0x00
#define AMBIENT26_INT_CFG_LS_INT_EN_ENABLE  0x04
#define AMBIENT26_INT_CFG_LS_INT_EN_MASK    0x04

/**
 * @brief Ambient 26 INT_PST register setting.
 * @details Specified setting for INT_PST register of Ambient 26 Click driver.
 */
#define AMBIENT26_INT_PST_1                 0x00
#define AMBIENT26_INT_PST_2                 0x10
#define AMBIENT26_INT_PST_3                 0x20
#define AMBIENT26_INT_PST_4                 0x30
#define AMBIENT26_INT_PST_5                 0x40
#define AMBIENT26_INT_PST_6                 0x50
#define AMBIENT26_INT_PST_7                 0x60
#define AMBIENT26_INT_PST_8                 0x70
#define AMBIENT26_INT_PST_9                 0x80
#define AMBIENT26_INT_PST_10                0x90
#define AMBIENT26_INT_PST_11                0xA0
#define AMBIENT26_INT_PST_12                0xB0
#define AMBIENT26_INT_PST_13                0xC0
#define AMBIENT26_INT_PST_14                0xD0
#define AMBIENT26_INT_PST_15                0xE0
#define AMBIENT26_INT_PST_16                0xF0
#define AMBIENT26_INT_PST_MASK              0xF0

/**
 * @brief Ambient 26 mode setting.
 * @details Specified setting for mode of Ambient 26 Click driver.
 */
#define AMBIENT26_MODE_ALS                  0
#define AMBIENT26_MODE_UVS                  1

/**
 * @brief Ambient 26 resolution setting.
 * @details Specified setting for resolution of Ambient 26 Click driver.
 */
#define AMBIENT26_RESOLUTION_13_BIT         0
#define AMBIENT26_RESOLUTION_16_BIT         1
#define AMBIENT26_RESOLUTION_17_BIT         2
#define AMBIENT26_RESOLUTION_18_BIT         3
#define AMBIENT26_RESOLUTION_19_BIT         4
#define AMBIENT26_RESOLUTION_20_BIT         5

/**
 * @brief Ambient 26 data rate setting.
 * @details Specified setting for data rate of Ambient 26 Click driver.
 */
#define AMBIENT26_DATA_RATE_25_MS           0
#define AMBIENT26_DATA_RATE_50_MS           1
#define AMBIENT26_DATA_RATE_100_MS          2
#define AMBIENT26_DATA_RATE_200_MS          3
#define AMBIENT26_DATA_RATE_500_MS          4
#define AMBIENT26_DATA_RATE_1000_MS         5
#define AMBIENT26_DATA_RATE_2000_MS         6

/**
 * @brief Ambient 26 gain range setting.
 * @details Specified setting for gain range of Ambient 26 Click driver.
 */
#define AMBIENT26_GAIN_1                    0
#define AMBIENT26_GAIN_3                    1
#define AMBIENT26_GAIN_6                    2
#define AMBIENT26_GAIN_9                    3
#define AMBIENT26_GAIN_18                   4

/**
 * @brief Ambient 26 interrupt setting.
 * @details Specified setting for interrupt of Ambient 26 Click driver.
 */
#define AMBIENT26_INT_MODE_ALS              0
#define AMBIENT26_INT_MODE_UVS              1
#define AMBIENT26_INT_PERSISTANCE_1         0
#define AMBIENT26_INT_PERSISTANCE_2         1
#define AMBIENT26_INT_PERSISTANCE_3         2
#define AMBIENT26_INT_PERSISTANCE_4         3
#define AMBIENT26_INT_PERSISTANCE_5         4
#define AMBIENT26_INT_PERSISTANCE_6         5
#define AMBIENT26_INT_PERSISTANCE_7         6
#define AMBIENT26_INT_PERSISTANCE_8         7
#define AMBIENT26_INT_PERSISTANCE_9         8
#define AMBIENT26_INT_PERSISTANCE_10        9
#define AMBIENT26_INT_PERSISTANCE_11        10
#define AMBIENT26_INT_PERSISTANCE_12        11
#define AMBIENT26_INT_PERSISTANCE_13        12
#define AMBIENT26_INT_PERSISTANCE_14        13
#define AMBIENT26_INT_PERSISTANCE_15        14
#define AMBIENT26_INT_PERSISTANCE_16        15

/**
 * @brief Ambient 26 threshold setting.
 * @details Specified setting for threshold of Ambient 26 Click driver.
 */
#define AMBIENT26_THRESHOLD_UPPER           0x000000ul
#define AMBIENT26_THRESHOLD_LOWER           0x0FFFFFul

/**
 * @brief Ambient 26 measurement setting.
 * @details Specified setting for measurement of Ambient 26 Click driver.
 */
#define AMBIENT26_MAX_GAIN                  18
#define AMBIENT26_MAX_RES                   20
#define AMBIENT26_UVI_SENS                  2300.0
#define AMBIENT26_ALS_SENS                  0.6

/**
 * @brief Ambient 26 timeout setting.
 * @details Specified setting for timeout of Ambient 26 Click driver.
 */
#define AMBIENT26_TIMEOUT_MS                3000

/**
 * @brief Ambient 26 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 26 Click driver.
 */
#define AMBIENT26_DEVICE_ADDRESS            0x53

/*! @} */ // ambient26_set

/**
 * @defgroup ambient26_map Ambient 26 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 26 Click driver.
 */

/**
 * @addtogroup ambient26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 26 Click to the selected MikroBUS.
 */
#define AMBIENT26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ambient26_map
/*! @} */ // ambient26

/**
 * @brief Ambient 26 Click context object.
 * @details Context object definition of Ambient 26 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint8_t main_status;        /**< Main status setting. */
    uint8_t mode;               /**< ALS or UVS mode setting. */
    uint8_t data_rate;          /**< Data rate setting. */
    uint8_t gain;               /**< Gain range setting. */
    uint8_t data_res;           /**< Data resolution setting. */
    float integration_time;     /**< Data integration time setting. */

} ambient26_t;

/**
 * @brief Ambient 26 Click configuration object.
 * @details Configuration object definition of Ambient 26 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ambient26_cfg_t;

/**
 * @brief Ambient 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT26_OK = 0,
    AMBIENT26_ERROR = -1

} ambient26_return_value_t;

/*!
 * @addtogroup ambient26 Ambient 26 Click Driver
 * @brief API for configuring and manipulating Ambient 26 Click driver.
 * @{
 */

/**
 * @brief Ambient 26 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient26_cfg_setup ( ambient26_cfg_t *cfg );

/**
 * @brief Ambient 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_init ( ambient26_t *ctx, ambient26_cfg_t *cfg );

/**
 * @brief Ambient 26 default configuration function.
 * @details This function executes a default configuration of Ambient 26
 * Click board.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient26_default_cfg ( ambient26_t *ctx );

/**
 * @brief Ambient 26 write register function.
 * @details This function writes a single data byte to the selected register
 * of the Ambient 26 device.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_write_reg ( ambient26_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Ambient 26 read register function.
 * @details This function reads a single data byte from the selected register
 * of the Ambient 26 device.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_read_reg ( ambient26_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Ambient 26 get INT pin function.
 * @details This function returns the logical state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @return INT pin logic state (0 or 1).
 * @note None.
 */
uint8_t ambient26_get_int_pin ( ambient26_t *ctx );

/**
 * @brief Ambient 26 communication check function.
 * @details This function checks the communication by reading the PART ID
 * register and validating its value against the expected device ID mask.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_check_com ( ambient26_t *ctx );

/**
 * @brief Ambient 26 soft reset function.
 * @details This function performs a software reset of the device by writing
 * the reset command to the main control register.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_soft_reset ( ambient26_t *ctx );

/**
 * @brief Ambient 26 set sensor active function.
 * @details This function sets the sensor to active mode by enabling the
 * SENSOR_ACTIVE bit in the main control register.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_set_sensor_active ( ambient26_t *ctx );

/**
 * @brief Ambient 26 set sensor standby function.
 * @details This function sets the sensor to standby mode by clearing the
 * SENSOR_ACTIVE bit in the main control register.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_set_sensor_standby ( ambient26_t *ctx );

/**
 * @brief Ambient 26 set mode function.
 * @details This function sets the ALS/UVS operating mode by updating the
 * UVS mode field in the main control register and stores the selected mode
 * to the driver context.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[in] mode : Operating mode.
 * See AMBIENT26_MODE_* definitions for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_set_mode ( ambient26_t *ctx, uint8_t mode );

/**
 * @brief Ambient 26 set resolution function.
 * @details This function sets the ALS/UVS measurement resolution by updating
 * the resolution bits in the measurement rate register and updates the
 * integration time and data resolution fields in the driver context.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[in] resolution : ALS/UVS resolution setting.
 * See AMBIENT26_RESOLUTION_* definitions for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_set_resolution ( ambient26_t *ctx, uint8_t resolution );

/**
 * @brief Ambient 26 set data rate function.
 * @details This function sets the ALS/UVS measurement data rate by updating
 * the measurement rate bits in the measurement rate register and stores
 * the selected data rate to the driver context.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[in] data_rate : ALS/UVS data rate setting.
 * See AMBIENT26_DATA_RATE_* definitions for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_set_data_rate ( ambient26_t *ctx, uint8_t data_rate );

/**
 * @brief Ambient 26 set gain function.
 * @details This function sets the ALS/UVS gain by updating the gain register
 * and stores the selected gain value to the driver context in linear form.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[in] gain : ALS/UVS gain setting.
 * See AMBIENT26_GAIN_* definitions for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_set_gain ( ambient26_t *ctx, uint8_t gain );

/**
 * @brief Ambient 26 get main status function.
 * @details This function reads the main status register and stores the value
 * to the main_status field of the driver context.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_get_main_status ( ambient26_t *ctx );

/**
 * @brief Ambient 26 enable interrupt function.
 * @details This function configures and enables the ALS/UVS interrupt source
 * and persistence level according to the selected mode and persistence value.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[in] int_mode : Interrupt source selection.
 * See AMBIENT26_INT_MODE_* definitions for detailed explanation.
 * @param[in] persistance : Interrupt persistence setting.
 * See AMBIENT26_INT_PERSISTANCE_* definitions for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_enable_interrupt ( ambient26_t *ctx, uint8_t int_mode, uint8_t persistance );

/**
 * @brief Ambient 26 disable interrupt function.
 * @details This function disables the ALS/UVS interrupt by clearing the
 * interrupt enable bit in the interrupt configuration register.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_disable_interrupt ( ambient26_t *ctx );

/**
 * @brief Ambient 26 set threshold function.
 * @details This function sets the ALS/UVS upper and lower threshold values
 * by writing the threshold registers with the provided 20-bit values.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[in] upper : Upper threshold value (20-bit effective).
 * @param[in] lower : Lower threshold value (20-bit effective).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_set_threshold ( ambient26_t *ctx, uint32_t upper, uint32_t lower );

/**
 * @brief Ambient 26 get ALS raw data function.
 * @details This function reads the raw ALS measurement result from the ALS
 * data registers. If ALS mode is not selected, the function sets ALS mode
 * first and then waits until new data is available or timeout occurs.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[out] als_raw : Pointer to raw ALS data variable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This functions uses interrupt pin as a data ready indication,
 * therefore changing interrupt thresholds should be avoided.
 */
err_t ambient26_get_als_raw ( ambient26_t *ctx, uint32_t *als_raw );

/**
 * @brief Ambient 26 get UVS raw data function.
 * @details This function reads the raw UVS measurement result from the UVS
 * data registers. If UVS mode is not selected, the function sets UVS mode
 * first and then waits until new data is available or timeout occurs.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[out] uvs_raw : Pointer to raw UVS data variable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This functions uses interrupt pin as a data ready indication,
 * therefore changing interrupt thresholds should be avoided.
 */
err_t ambient26_get_uvs_raw ( ambient26_t *ctx, uint32_t *uvs_raw );

/**
 * @brief Ambient 26 get ALS illuminance function.
 * @details This function calculates the ALS illuminance in lux from the
 * raw ALS data using the configured gain and integration time parameters.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[out] als_lux : Pointer to ALS illuminance value in lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_get_als_lux ( ambient26_t *ctx, float *als_lux );

/**
 * @brief Ambient 26 get UV index function.
 * @details This function calculates the UV index value from the raw UVS
 * data using the configured gain, data resolution, and device scaling
 * factors and returns the result as a floating point UV index value.
 * @param[in] ctx : Click context object.
 * See #ambient26_t object definition for detailed explanation.
 * @param[out] uvi : Pointer to UV index value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient26_get_uv_index ( ambient26_t *ctx, float *uvi );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT26_H

/*! @} */ // ambient26

// ------------------------------------------------------------------------ END
