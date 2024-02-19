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
 * @file battboost.h
 * @brief This file contains API for BATT Boost Click Driver.
 */

#ifndef BATTBOOST_H
#define BATTBOOST_H

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
 * @addtogroup battboost BATT Boost Click Driver
 * @brief API for configuring and manipulating BATT Boost Click driver.
 * @{
 */

/**
 * @defgroup battboost_reg BATT Boost Registers List
 * @brief List of registers of BATT Boost Click driver.
 */

/**
 * @addtogroup battboost_reg
 * @{
 */

/**
 * @brief BATT Boost description register.
 * @details Specified register for description of BATT Boost Click driver.
 */
#define BATTBOOST_REG_STATUS                    0x00
#define BATTBOOST_REG_CHENERGY_3                0x01
#define BATTBOOST_REG_CHENERGY_2                0x02
#define BATTBOOST_REG_CHENERGY_1                0x03
#define BATTBOOST_REG_CHENERGY_0                0x04
#define BATTBOOST_REG_VCAP                      0x05
#define BATTBOOST_REG_VCHEND                    0x06
#define BATTBOOST_REG_PROFILE_MSB               0x07
#define BATTBOOST_REG_COMMAND                   0x08
#define BATTBOOST_REG_SET1                      0x09
#define BATTBOOST_REG_SET2                      0x0A
#define BATTBOOST_REG_SET3                      0x0B
#define BATTBOOST_REG_SET4                      0x0C
#define BATTBOOST_REG_SET5                      0x0D

/*! @} */ // battboost_reg

/**
 * @defgroup battboost_set BATT Boost Registers Settings
 * @brief Settings for registers of BATT Boost Click driver.
 */

/**
 * @addtogroup battboost_set
 * @{
 */

 /**
 * @brief BATT Boost status conditions.
 * @details Status conditions of BATT Boost Click driver.
 */
#define BATTBOOST_STATUS_LOWBAT                 0x80
#define BATTBOOST_STATUS_EW                     0x40
#define BATTBOOST_STATUS_ALRM                   0x20
#define BATTBOOST_STATUS_RDY                    0x01

 /**
 * @brief BATT Boost storage capacitor voltage status bit mask.
 * @details Storage capacitor voltage status of BATT Boost Click driver.
 */
#define BATTBOOST_VCAP_BIT_MASK                 0x1F

 /**
 * @brief BATT Boost target charge voltage bit mask.
 * @details Target charge voltage of BATT Boost Click driver.
 */
#define BATTBOOST_VCHEND_BIT_MASK               0x1F

 /**
 * @brief BATT Boost minimum input voltage comparator threshold values.
 * @details Minimum input voltage comparator threshold values of BATT Boost Click driver.
 */
#define BATTBOOST_SET2_VMIN_2_4V                2.4f
#define BATTBOOST_SET2_VMIN_2_6V                2.6f
#define BATTBOOST_SET2_VMIN_2_8V                2.8f
#define BATTBOOST_SET2_VMIN_3_0V                3.0f
#define BATTBOOST_SET2_VMIN_3_2V                3.2f
#define BATTBOOST_SET2_VMIN_BIT_MASK            0xF8
#define BATTBOOST_SET2_ICH_BIT_MASK             0x1F
#define BATTBOOST_SET2_SET_VDH_VBT              0x10

 /**
 * @brief BATT Boost input voltage comparator Early Warning voltage values.
 * @details Input voltage comparator Early Warning voltage values of BATT Boost Click driver.
 */
#define BATTBOOST_SET3_VEW_2_4V                 0
#define BATTBOOST_SET3_VEW_2_6V                 1
#define BATTBOOST_SET3_VEW_2_8V                 2
#define BATTBOOST_SET3_VEW_3_0V                 3
#define BATTBOOST_SET3_VEW_3_2V                 4
#define BATTBOOST_SET3_VEW_3_4V                 5
#define BATTBOOST_SET3_VEW_3_6V                 6
#define BATTBOOST_SET3_VEW_3_84V                7
#define BATTBOOST_SET3_VEW_4_1V                 8
#define BATTBOOST_SET3_VEW_4_3V                 9
#define BATTBOOST_SET3_VEW_BIT_MASK             0x0F
#define BATTBOOST_SET3_EEW_DISABLE              0
#define BATTBOOST_SET3_EEW_ENABLE               1

 /**
 * @brief BATT Boost optimization margin values.
 * @details Optimization margin values of BATT Boost Click driver.
 */
#define BATTBOOST_SET5_OPT_MARG_MIN             0
#define BATTBOOST_SET5_OPT_MARG_NORMAL          1
#define BATTBOOST_SET5_OPT_MARG_SAFE            2
#define BATTBOOST_SET5_OPT_MARG_EXTRA_SAFE      3

 /**
 * @brief BATT Boost maximum storage voltage.
 * @details Maximum storage voltage of BATT Boost Click driver.
 */
#define BATTBOOST_SET4_VCAPMAX_4_95V            0
#define BATTBOOST_SET4_VCAPMAX_5_54V            1
#define BATTBOOST_SET4_VCAPMAX_BIT_MASK         0xEF


 /**
 * @brief BATT Boost optimizer profiles values.
 * @details Optimizer profiles values of BATT Boost Click driver.
 */
#define BATTBOOST_CMD_PROF_0_FIXED_MODE         0
#define BATTBOOST_CMD_PROF_BIT_MASK             0xFC
#define BATTBOOST_CMD_BIT_MASK                  0x0F
#define BATTBOOST_PROF_MSB_BIT_MASK             0x03
#define BATTBOOST_PROF_BIT_MASK                 0xF0

/**
 * @brief BATT Boost operation mode data values.
 * @details Operation mode data values of BATT Boost Click driver.
 */
#define BATTBOOST_OP_MODE_STANDBY               0
#define BATTBOOST_OP_MODE_STBY_BIT_MASK         0x06
#define BATTBOOST_OP_MODE_CHARGE                1
#define BATTBOOST_OP_MODE_CHG_BIT_MASK          0xF0
#define BATTBOOST_OP_MODE_SET_CHARGE            0x02
#define BATTBOOST_OP_MODE_ACTIVE                2
#define BATTBOOST_OP_MODE_SET_ACT_ACTIVE        0x04

/**
 * @brief BATT Boost reset optimizer data values.
 * @details Reset optimizer data values of BATT Boost Click driver.
 */
#define BATTBOOST_CMD_RESET_BIT_MASK            0x08

/**
 * @brief BATT Boost auto mode data values.
 * @details Auto mode data values of BATT Boost Click driver.
 */
#define BATTBOOST_CMD_AUTOMODE_ENABLE           0x80

/**
 * @brief BATT Boost output voltage control values.
 * @details Output voltage control of BATT Boost Click driver.
 */
#define BATTBOOST_SET1_VSET_1_8V                1.8f
#define BATTBOOST_SET1_VSET_2_0V                2.0f
#define BATTBOOST_SET1_VSET_2_2V                2.2f
#define BATTBOOST_SET1_VSET_2_4V                2.4f
#define BATTBOOST_SET1_VSET_2_5V                2.5f
#define BATTBOOST_SET1_VSET_2_6V                2.6f
#define BATTBOOST_SET1_VSET_2_7V                2.7f
#define BATTBOOST_SET1_VSET_2_8V                2.8f
#define BATTBOOST_SET1_VSET_2_9V                2.9f
#define BATTBOOST_SET1_VSET_3_0V                3.0f
#define BATTBOOST_SET1_VSET_3_1V                3.1f
#define BATTBOOST_SET1_VSET_3_2V                3.2f
#define BATTBOOST_SET1_VSET_3_3V                3.3f
#define BATTBOOST_SET1_VSET_3_4V                3.4f
#define BATTBOOST_SET1_VSET_3_5V                3.5f
#define BATTBOOST_SET1_VSET_3_6V                3.6f
#define BATTBOOST_SET1_VSET_BIT_MASK            0xF0
#define BATTBOOST_SET1_VFIX_BIT_MASK            0x0F

/**
 * @brief BATT Boost start ON pin conditions.
 * @details Start ON pin conditions of BATT Boost Click driver.
 */
#define BATTBOOST_CONDITION_STOP                0
#define BATTBOOST_CONDITION_START               1

/**
 * @brief BATT Boost ready pin states.
 * @details Ready pin states of BATT Boost Click driver.
 */
#define BATTBOOST_STATUS_NOT_READY              0
#define BATTBOOST_STATUS_READY                  1

/**
 * @brief BATT Boost device address setting.
 * @details Specified setting for device slave address selection of
 * BATT Boost Click driver.
 */
#define BATTBOOST_DEVICE_ADDRESS_0              0x2E
#define BATTBOOST_DEVICE_ADDRESS_1              0x2F

/*! @} */ // battboost_set

/**
 * @defgroup battboost_map BATT Boost MikroBUS Map
 * @brief MikroBUS pin mapping of BATT Boost Click driver.
 */

/**
 * @addtogroup battboost_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BATT Boost Click to the selected MikroBUS.
 */
#define BATTBOOST_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.on  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // battboost_map
/*! @} */ // battboost

/**
 * @brief BATT Boost Click context object.
 * @details Context object definition of BATT Boost Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;       /**< Start pin. */

    // Input pins
    digital_in_t rdy;       /**< Ready pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} battboost_t;

/**
 * @brief BATT Boost Click configuration object.
 * @details Configuration object definition of BATT Boost Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t on;              /**< Start pin. */
    pin_name_t rdy;             /**< Ready pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} battboost_cfg_t;

/**
 * @brief BATT Boost Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BATTBOOST_OK = 0,
    BATTBOOST_ERROR = -1

} battboost_return_value_t;

/**
 * @brief BATT Boost Click capacitor end-of-charge voltage.
 * @details Predefined enum values for capacitor end-of-charge voltage.
 */
typedef enum
{
    BATTBOOST_VFIX_2_60V = 3,
    BATTBOOST_VFIX_2_95V,
    BATTBOOST_VFIX_3_27V,
    BATTBOOST_VFIX_3_57V,
    BATTBOOST_VFIX_3_84V,
    BATTBOOST_VFIX_4_10V,
    BATTBOOST_VFIX_4_33V,
    BATTBOOST_VFIX_4_55V,
    BATTBOOST_VFIX_4_76V,
    BATTBOOST_VFIX_4_95V,
    BATTBOOST_VFIX_5_16V,
    BATTBOOST_VFIX_5_34V,
    BATTBOOST_VFIX_5_54V

} battboost_vfix_t;

/**
 * @brief BATT Boost Click capacitor charge current.
 * @details Predefined enum values for capacitor charge current.
 */
typedef enum
{
    BATTBOOST_ICH_2_MA = 0,
    BATTBOOST_ICH_4_MA,
    BATTBOOST_ICH_8_MA,
    BATTBOOST_ICH_16_MA,
    BATTBOOST_ICH_50_MA

} battboost_ich_t;

/*!
 * @addtogroup battboost BATT Boost Click Driver
 * @brief API for configuring and manipulating BATT Boost Click driver.
 * @{
 */

/**
 * @brief BATT Boost configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #battboost_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void battboost_cfg_setup ( battboost_cfg_t *cfg );

/**
 * @brief BATT Boost initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #battboost_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost_init ( battboost_t *ctx, battboost_cfg_t *cfg );

/**
 * @brief BATT Boost default configuration function.
 * @details This function executes a default configuration of BATT Boost
 * click board.
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t battboost_default_cfg ( battboost_t *ctx );

/**
 * @brief BATT Boost I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost_generic_write ( battboost_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief BATT Boost I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost_generic_read ( battboost_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief BATT Boost gets the status function.
 * @details This function reads the the status information 
 * of low battery input, capacitor input voltage early warning,
 * VDH output alarm and ready state
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost_get_status ( battboost_t *ctx, uint8_t *status );

/**
 * @brief BATT Boost gets the charge cycle count function.
 * @details This function reads the fuel gauge charge cycle count 
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[out] chenergy : Charge cycle count data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost_get_chenergy ( battboost_t *ctx, uint32_t *chenergy );

/**
 * @brief BATT Boost gets the storage capacitor voltage status function.
 * @details This function is used to read the storage capacitor voltage status
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[out] vcap : Storage capacitor voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost_get_vcap ( battboost_t *ctx, float *vcap );

/**
 * @brief BATT Boost gets the target charge voltage function.
 * @details This function reads the target charge voltage
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[out] vchend : Target charge voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battboost_get_vchend ( battboost_t *ctx, uint8_t *vchend );

/**
 * @brief BATT Boost sets optimizer profile number function.
 * @details This function sets desired optimizer profile number 
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] prof : Optimizer profile selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If profile 0 is selected, no optimization occurs, VFIX is applied.
*/
err_t battboost_set_prof ( battboost_t *ctx, uint8_t prof );

/**
 * @brief BATT Boost gets optimizer profile number function.
 * @details This function reads the actual optimizer profile number 
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] prof : Optimizer profile selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
*/
err_t battboost_get_prof ( battboost_t *ctx, uint8_t *prof );

/**
 * @brief BATT Boost sets the operating mode function.
 * @details This function is used to select the desired operating mode
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] op_mode : Operating state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
*/
err_t battboost_set_op_mode ( battboost_t *ctx, uint8_t op_mode );

/**
 * @brief BATT Boost reset optimizer result function.
 * @details This function is used to reset optimizer result of active profile
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
*/
err_t battboost_reset_optimizer ( battboost_t *ctx );

/**
 * @brief BATT Boost sets the auto mode function.
 * @details This function is used to set the auto mode 
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
*/
err_t battboost_set_automode ( battboost_t *ctx );

/**
 * @brief BATT Boost sets the output voltage function.
 * @details This function is used to control the output voltage levels
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] vset : Output voltage [1.8V-3.6V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
*/
err_t battboost_set_vset ( battboost_t *ctx, float vset );

/**
 * @brief BATT Boost sets the end-of-charge voltage function.
 * @details This function is used to control the end-of-charge voltage levels
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] vfix : Capacitor end-of-charge voltage [2.6V-5.54V].
 * See #battboost_vfix_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
*/
err_t battboost_set_vfix ( battboost_t *ctx, battboost_vfix_t vfix );

/**
 * @brief BATT Boost sets the input threshold voltage function.
 * @details This function control the input threshold voltage levels
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] vmin : - Input threshold voltage [2.4V-3.2V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
*/
err_t battboost_set_vmin ( battboost_t *ctx, float vmin );

/**
 * @brief BATT Boost sets the charge current function.
 * @details This function is used to sets the charge current levels
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] ich : Charge current [2mA-50mAV].
 * See #battboost_ich_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For the emergency charge charge current is set to 50mA.
*/
err_t battboost_set_ich ( battboost_t *ctx, battboost_ich_t ich );

/**
 * @brief BATT Boost sets the high-impedance mode function.
 * @details This function is used to configures the VDH high-impedance mode 
 * in Standby and Active states
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
*/
err_t battboost_high_impedance_mode ( battboost_t *ctx );

/**
 * @brief BATT Boost sets the Vvdh Vvbt mode function.
 * @details This function is used to configures the VDH Vvdh=Vvbt mode
 * in Standby and Active states
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *  @note None.
*/
err_t battboost_vdh_vbt_mode ( battboost_t *ctx );

/**
 * @brief BATT Boost sets the early warning voltage function.
 * @details This function sets and enables the early warning voltage level
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] vew : Early warning voltage [2.4V-4.3V].
 * @param[in] eew : Enable early warning.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *  @note None.
*/
err_t battboost_set_vew ( battboost_t *ctx, uint8_t vew, uint8_t eew );

/**
 * @brief BATT Boost sets the capacitor maximum storage voltage function.
 * @details This function sets the capacitor maximum storage voltage level
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] vcapmax : Capacitor maximum storage voltage, 4.95V or 5.54V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *  @note None.
*/
err_t battboost_set_vcapmax ( battboost_t *ctx, uint8_t vcapmax );

/**
 * @brief BATT Boost sets the optimization margin voltage function.
 * @details This function sets the optimization margin voltage level
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] opt_marg :  Optimization margin voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *  @note None.
*/
err_t battboost_set_opt_marg ( battboost_t *ctx, uint8_t opt_marg );

/**
 * @brief BATT Boost sets the ON pin state function.
 * @details This function sets the desired states of the ON (RST) pin
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @param[in] start :  ON pin state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 *  @note None.
*/
void battboost_set_on_pin_state ( battboost_t *ctx, uint8_t start );

/**
 * @brief BATT Boost gets ready state function.
 * @details This function is used to check if device is ready to deliver full power
 * of the NBM5100ABQX, Coin cell battery life booster 
 * with adaptive power optimization on the BATT Boost Click board. 
 * @param[in] ctx : Click context object.
 * See #battboost_t object definition for detailed explanation.
 * @return @li @c 0 - Device is not ready,
 *         @li @c 1 - Device is ready to deliver full power.
 *  @note None.
*/
uint8_t battboost_get_ready ( battboost_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BATTBOOST_H

/*! @} */ // battboost

// ------------------------------------------------------------------------ END
