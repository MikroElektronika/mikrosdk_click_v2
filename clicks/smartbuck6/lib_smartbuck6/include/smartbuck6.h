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
 * @file smartbuck6.h
 * @brief This file contains API for Smart Buck 6 Click Driver.
 */

#ifndef SMARTBUCK6_H
#define SMARTBUCK6_H

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
 * @addtogroup smartbuck6 Smart Buck 6 Click Driver
 * @brief API for configuring and manipulating Smart Buck 6 Click driver.
 * @{
 */

/**
 * @defgroup smartbuck6_reg Smart Buck 6 Registers List
 * @brief List of registers of Smart Buck 6 Click driver.
 */

/**
 * @addtogroup smartbuck6_reg
 * @{
 */

/**
 * @brief Smart Buck 6 register list.
 * @details Specified register list of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_REG_STATUS_0                 0x00
#define SMARTBUCK6_REG_STATUS_1                 0x01
#define SMARTBUCK6_REG_BUCK_A_CURR_PWR_METER    0x02
#define SMARTBUCK6_REG_BUCK_B_CURR_PWR_METER    0x03
#define SMARTBUCK6_REG_BUCK_C_CURR_PWR_METER    0x04
#define SMARTBUCK6_REG_BUCKX_VOLTAGE            0x06
#define SMARTBUCK6_REG_CLEAR_0                  0x07
#define SMARTBUCK6_REG_CLEAR_1                  0x08
#define SMARTBUCK6_REG_MASK_0                   0x09
#define SMARTBUCK6_REG_MASK_1                   0x0A
#define SMARTBUCK6_REG_REMOTE                   0x0B
#define SMARTBUCK6_REG_BUCKX_CTRL               0x0C
#define SMARTBUCK6_REG_PG                       0x0D
#define SMARTBUCK6_REG_DISCHARGE_R              0x0E
#define SMARTBUCK6_REG_SW_FREQ                  0x0F
#define SMARTBUCK6_REG_MONITOR_EN               0x10
#define SMARTBUCK6_REG_SOFT_STOP_EN             0x11
#define SMARTBUCK6_REG_SOFT_STOP                0x12
#define SMARTBUCK6_REG_SOFT_START               0x13
#define SMARTBUCK6_REG_PROTECT                  0x14
#define SMARTBUCK6_REG_BUCK_A_VOUT              0x15
#define SMARTBUCK6_REG_BUCK_B_VOUT              0x16
#define SMARTBUCK6_REG_BUCK_C_VOUT              0x17
#define SMARTBUCK6_REG_PON_CONFIG_0             0x19
#define SMARTBUCK6_REG_PON_CONFIG_1             0x1A
#define SMARTBUCK6_REG_PON_CONFIG_2             0x1B
#define SMARTBUCK6_REG_PON_CONFIG_3             0x1C
#define SMARTBUCK6_REG_PON_OFF_DELAY0           0x1D
#define SMARTBUCK6_REG_PON_SEQ_DELAY_1_2        0x1E
#define SMARTBUCK6_REG_PON_SEQ_DELAY_3_PG       0x1F
#define SMARTBUCK6_REG_POFF_SEQ_CONFIG_0        0x20
#define SMARTBUCK6_REG_POFF_SEQ_CONFIG_1        0x21
#define SMARTBUCK6_REG_POFF_SEQ_CONFIG_2        0x22
#define SMARTBUCK6_REG_POFF_SEQ_CONFIG_3        0x23
#define SMARTBUCK6_REG_ADC_TEMP                 0x24
#define SMARTBUCK6_REG_VOUT_RANGE_SEL           0x25
#define SMARTBUCK6_REG_OC_STATUS_CLEAR          0x2A
#define SMARTBUCK6_REG_MTP_AUTO                 0x30
#define SMARTBUCK6_REG_PART_ID                  0x31
#define SMARTBUCK6_REG_CODE_ID                  0x35
#define SMARTBUCK6_REG_CODE_VERSION             0x36
#define SMARTBUCK6_REG_ACTIVE_POS_EN_A_B        0x71
#define SMARTBUCK6_REG_I2C_ADDRESS              0x73
#define SMARTBUCK6_REG_ACTIVE_POS_EN_C          0x79
#define SMARTBUCK6_REG_VIN_OV                   0x90
#define SMARTBUCK6_REG_VIN_UVLO                 0xAF

/*! @} */ // smartbuck6_reg

/**
 * @defgroup smartbuck6_set Smart Buck 6 Registers Settings
 * @brief Settings for registers of Smart Buck 6 Click driver.
 */

/**
 * @addtogroup smartbuck6_set
 * @{
 */

/**
 * @brief Smart Buck 6 STATUS_0 register setting.
 * @details Specified setting for STATUS_0 register of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_STATUS_0_OVER_TEMP_STATUS    0x40
#define SMARTBUCK6_STATUS_0_BUCK_A_PWR_NOT_GOOD 0x20
#define SMARTBUCK6_STATUS_0_BUCK_B_PWR_NOT_GOOD 0x10
#define SMARTBUCK6_STATUS_0_BUCK_C_PWR_NOT_GOOD 0x08
#define SMARTBUCK6_STATUS_0_VIN_OV              0x02

/**
 * @brief Smart Buck 6 STATUS_1 register setting.
 * @details Specified setting for STATUS_1 register of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_STATUS_1_BUCK_A_OV           0x80
#define SMARTBUCK6_STATUS_1_BUCK_B_OV           0x40
#define SMARTBUCK6_STATUS_1_BUCK_C_OV           0x20
#define SMARTBUCK6_STATUS_1_BUCK_A_UV           0x08
#define SMARTBUCK6_STATUS_1_BUCK_B_UV           0x04
#define SMARTBUCK6_STATUS_1_BUCK_C_UV           0x02

/**
 * @brief Smart Buck 6 CLEAR_0 register setting.
 * @details Specified setting for CLEAR_0 register of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_CLEAR_0_BUCK_A_PWR_NOT_GOOD  0x20
#define SMARTBUCK6_CLEAR_0_BUCK_B_PWR_NOT_GOOD  0x10
#define SMARTBUCK6_CLEAR_0_BUCK_C_PWR_NOT_GOOD  0x08
#define SMARTBUCK6_CLEAR_0_VIN_OVP              0x02
#define SMARTBUCK6_CLEAR_0_GLOBAL               0x01

/**
 * @brief Smart Buck 6 CLEAR_1 register setting.
 * @details Specified setting for CLEAR_1 register of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_CLEAR_1_BUCK_A_OV            0x80
#define SMARTBUCK6_CLEAR_1_BUCK_B_OV            0x40
#define SMARTBUCK6_CLEAR_1_BUCK_C_OV            0x20
#define SMARTBUCK6_CLEAR_1_BUCK_A_UV            0x08
#define SMARTBUCK6_CLEAR_1_BUCK_B_UV            0x04
#define SMARTBUCK6_CLEAR_1_BUCK_C_UV            0x02

/**
 * @brief Smart Buck 6 OC_STATUS_CLEAR register setting.
 * @details Specified setting for OC_STATUS_CLEAR register of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_OC_STATUS_CLEAR_BUCK_A_OC    0x80
#define SMARTBUCK6_OC_STATUS_CLEAR_BUCK_B_OC    0x40
#define SMARTBUCK6_OC_STATUS_CLEAR_BUCK_C_OC    0x20
#define SMARTBUCK6_OC_STATUS_BUCK_A_OC          0x08
#define SMARTBUCK6_OC_STATUS_BUCK_B_OC          0x04
#define SMARTBUCK6_OC_STATUS_BUCK_C_OC          0x02

/**
 * @brief Smart Buck 6 BUCKX_CTRL register setting.
 * @details Specified setting for BUCKX_CTRL register of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_BUCKX_CTRL_BUCK_C_EN         0x20
#define SMARTBUCK6_BUCKX_CTRL_BUCK_B_EN         0x40
#define SMARTBUCK6_BUCKX_CTRL_BUCK_A_EN         0x80
#define SMARTBUCK6_BUCKX_CTRL_BUCK_X_EN_MASK    0xE0
#define SMARTBUCK6_BUCKX_CTRL_PWM_BUCK_C_AUTO   0x02
#define SMARTBUCK6_BUCKX_CTRL_PWM_BUCK_B_AUTO   0x04
#define SMARTBUCK6_BUCKX_CTRL_PWM_BUCK_A_AUTO   0x08

/**
 * @brief Smart Buck 6 VOUT_RANGE_SEL register setting.
 * @details Specified setting for VOUT_RANGE_SEL register of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_VOUT_RANGE_SEL_BUCK_C_15MV   0x02
#define SMARTBUCK6_VOUT_RANGE_SEL_BUCK_B_15MV   0x04
#define SMARTBUCK6_VOUT_RANGE_SEL_BUCK_A_15MV   0x08
#define SMARTBUCK6_VOUT_RANGE_SEL_BUCK_X_MASK   0x0E

/**
 * @brief Smart Buck 6 PART_ID register setting.
 * @details Specified setting for PART_ID register of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_PART_ID                      0x13

/**
 * @brief Smart Buck 6 buck selection setting.
 * @details Specified setting for buck selection of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_BUCK_C                       0x01
#define SMARTBUCK6_BUCK_B                       0x02
#define SMARTBUCK6_BUCK_A                       0x04
#define SMARTBUCK6_BUCK_ALL                     0x07

/**
 * @brief Smart Buck 6 vout setting.
 * @details Specified setting for vout of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_VOUT_MV_MIN                  400
#define SMARTBUCK6_VOUT_MV_MAX                  3600
#define SMARTBUCK6_VOUT_MV_STEP_THRESHOLD       1200
#define SMARTBUCK6_VOUT_MV_STEP_10MV            10
#define SMARTBUCK6_VOUT_MV_STEP_15MV            15

/**
 * @brief Smart Buck 6 current resolution setting.
 * @details Specified setting for current resolution of Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_IOUT_RES_MV                  125

/**
 * @brief Smart Buck 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart Buck 6 Click driver.
 */
#define SMARTBUCK6_DEVICE_ADDRESS_A2A1_11       0x07
#define SMARTBUCK6_DEVICE_ADDRESS_A2A1_ZZ       0x08
#define SMARTBUCK6_DEVICE_ADDRESS_A2A1_00       0x09
#define SMARTBUCK6_DEVICE_ADDRESS_A2A1_0Z       0x0A
#define SMARTBUCK6_DEVICE_ADDRESS_A2A1_01       0x0B
#define SMARTBUCK6_DEVICE_ADDRESS_A2A1_Z0       0x0C
#define SMARTBUCK6_DEVICE_ADDRESS_A2A1_Z1       0x0D
#define SMARTBUCK6_DEVICE_ADDRESS_A2A1_10       0x0E
#define SMARTBUCK6_DEVICE_ADDRESS_A2A1_1Z       0x0F

/*! @} */ // smartbuck6_set

/**
 * @defgroup smartbuck6_map Smart Buck 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Buck 6 Click driver.
 */

/**
 * @addtogroup smartbuck6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Buck 6 Click to the selected MikroBUS.
 */
#define SMARTBUCK6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartbuck6_map
/*! @} */ // smartbuck6

/**
 * @brief Smart Buck 6 Click status object.
 * @details Status object definition of Smart Buck 6 Click driver.
 */
typedef struct
{
    uint8_t status_0;           /**< Status 0 register. */
    uint8_t status_1;           /**< Status 1 register. */
    uint8_t oc_status;          /**< OC status register. */

} smartbuck6_status_t;

/**
 * @brief Smart Buck 6 Click context object.
 * @details Context object definition of Smart Buck 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;           /**< Enable pin (active low). */

    // Input pins
    digital_in_t pg;            /**< Power good indication pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} smartbuck6_t;

/**
 * @brief Smart Buck 6 Click configuration object.
 * @details Configuration object definition of Smart Buck 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t on;              /**< Enable pin (active low). */
    pin_name_t pg;              /**< Power good indication pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} smartbuck6_cfg_t;

/**
 * @brief Smart Buck 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTBUCK6_OK = 0,
    SMARTBUCK6_ERROR = -1

} smartbuck6_return_value_t;

/*!
 * @addtogroup smartbuck6 Smart Buck 6 Click Driver
 * @brief API for configuring and manipulating Smart Buck 6 Click driver.
 * @{
 */

/**
 * @brief Smart Buck 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartbuck6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartbuck6_cfg_setup ( smartbuck6_cfg_t *cfg );

/**
 * @brief Smart Buck 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartbuck6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck6_init ( smartbuck6_t *ctx, smartbuck6_cfg_t *cfg );

/**
 * @brief Smart Buck 6 default configuration function.
 * @details This function executes a default configuration of Smart Buck 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartbuck6_default_cfg ( smartbuck6_t *ctx );

/**
 * @brief Smart Buck 6 write register function.
 * @details This function writes a single byte of data to the specified register address.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck6_write_reg ( smartbuck6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Smart Buck 6 read register function.
 * @details This function reads a single byte of data from the specified register address.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck6_read_reg ( smartbuck6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Smart Buck 6 enable device function.
 * @details This function sets the ON pin to logic low state to enable the device.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck6_enable_device ( smartbuck6_t *ctx );

/**
 * @brief Smart Buck 6 disable device function.
 * @details This function sets the ON pin to logic high state to disable the device.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck6_disable_device ( smartbuck6_t *ctx );

/**
 * @brief Smart Buck 6 get power-good pin function.
 * @details This function reads the logic level of the PG pin.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t smartbuck6_get_pg_pin ( smartbuck6_t *ctx );

/**
 * @brief Smart Buck 6 check communication function.
 * @details This function checks communication by reading and verifying the PART ID register.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck6_check_com ( smartbuck6_t *ctx );

/**
 * @brief Smart Buck 6 read status registers function.
 * @details This function reads the STATUS_0, STATUS_1, and OC_STATUS registers and stores them in the status structure.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @param[out] status : Pointer to status structure.
 * See #smartbuck6_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck6_read_status ( smartbuck6_t *ctx, smartbuck6_status_t *status );

/**
 * @brief Smart Buck 6 clear status flags function.
 * @details This function clears global and buck-specific overcurrent status flags.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck6_clear_status ( smartbuck6_t *ctx );

/**
 * @brief Smart Buck 6 enable selected buck function.
 * @details This function enables one or more buck regulators by setting their control bits.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @param[in] buck_sel : Buck regulator selection mask (e.g. SMARTBUCK6_BUCK_A, BUCK_B, BUCK_C, BUCK_ALL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck6_enable_buck ( smartbuck6_t *ctx, uint8_t buck_sel );

/**
 * @brief Smart Buck 6 disable selected buck function.
 * @details This function disables one or more buck regulators by clearing their control bits.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @param[in] buck_sel : Buck regulator selection mask (e.g. SMARTBUCK6_BUCK_A, BUCK_B, BUCK_C, BUCK_ALL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck6_disable_buck ( smartbuck6_t *ctx, uint8_t buck_sel );

/**
 * @brief Smart Buck 6 set output voltage function.
 * @details This function sets the output voltage for one or more buck regulators.
 * It automatically adjusts the voltage range selection and applies reconfiguration if needed.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @param[in] buck_sel : Buck regulator selection mask.
 * @param[in] vout_mv : Output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Reconfiguration includes disabling and re-enabling the regulator.
 */
err_t smartbuck6_set_buck_vout ( smartbuck6_t *ctx, uint8_t buck_sel, uint16_t vout_mv );

/**
 * @brief Smart Buck 6 read buck output current function.
 * @details This function reads and returns the output current of the selected buck regulator.
 * @param[in] ctx : Click context object.
 * See #smartbuck6_t object definition for detailed explanation.
 * @param[in] buck_sel : Buck regulator selection (only one buck should be selected).
 * @param[out] current_ma : Pointer to store output current in milliamps.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck6_read_buck_current ( smartbuck6_t *ctx, uint8_t buck_sel, uint16_t *current_ma );

#ifdef __cplusplus
}
#endif
#endif // SMARTBUCK6_H

/*! @} */ // smartbuck6

// ------------------------------------------------------------------------ END
