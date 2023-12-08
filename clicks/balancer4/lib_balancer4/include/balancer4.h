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
 * @file balancer4.h
 * @brief This file contains API for Balancer 4 Click Driver.
 */

#ifndef BALANCER4_H
#define BALANCER4_H

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
 * @addtogroup balancer4 Balancer 4 Click Driver
 * @brief API for configuring and manipulating Balancer 4 Click driver.
 * @{
 */

/**
 * @defgroup balancer4_reg Balancer 4 Registers List
 * @brief List of registers of Balancer 4 Click driver.
 */

/**
 * @addtogroup balancer4_reg
 * @{
 */

/**
 * @brief Balancer 4 Register Map.
 * @details Specified Register Map of Balancer 4 Click driver.
 */
#define BALANCER4_REG_CONFIG0               0x00
#define BALANCER4_REG_CONFIG1               0x01
#define BALANCER4_REG_TIMER                 0x02
#define BALANCER4_REG_STATUS                0x03
#define BALANCER4_REG_FAULT                 0x04

/*! @} */ // balancer4_reg

/**
 * @defgroup balancer4_set Balancer 4 Registers Settings
 * @brief Settings for registers of Balancer 4 Click driver.
 */

/**
 * @addtogroup balancer4_set
 * @{
 */

/**
 * @brief Balancer 4 config 0 register setting.
 * @details Specified setting for config 0 register of Balancer 4 Click driver.
 */
#define BALANCER4_CONFIG0_VBAT_REG_8p3V     0x00
#define BALANCER4_CONFIG0_VBAT_REG_8p4V     0x20
#define BALANCER4_CONFIG0_VBAT_REG_8p5V     0x40
#define BALANCER4_CONFIG0_VBAT_REG_8p6V     0x60
#define BALANCER4_CONFIG0_VBAT_REG_8p7V     0x80
#define BALANCER4_CONFIG0_VBAT_REG_8p8V     0xA0
#define BALANCER4_CONFIG0_VBAT_REG_8p9V     0xC0
#define BALANCER4_CONFIG0_VBAT_REG_8p2V     0xE0
#define BALANCER4_CONFIG0_CHARGING_DIS      0x00
#define BALANCER4_CONFIG0_CHARGING_EN       0x10
#define BALANCER4_CONFIG0_VBAT_PRE_6V       0x00
#define BALANCER4_CONFIG0_VBAT_PRE_6p1V     0x02
#define BALANCER4_CONFIG0_VBAT_PRE_6p2V     0x04
#define BALANCER4_CONFIG0_VBAT_PRE_6p3V     0x06
#define BALANCER4_CONFIG0_VBAT_PRE_6p4V     0x08
#define BALANCER4_CONFIG0_VBAT_PRE_6p5V     0x0A
#define BALANCER4_CONFIG0_VBAT_PRE_6p6V     0x0C
#define BALANCER4_CONFIG0_VBAT_PRE_6p7V     0x0E
#define BALANCER4_CONFIG0_CELL_OVP_HYS_80mV 0x00
#define BALANCER4_CONFIG0_CELL_OVP_HYS_0mV  0x01

/**
 * @brief Balancer 4 config 1 register setting.
 * @details Specified setting for config 1 register of Balancer 4 Click driver.
 */
#define BALANCER4_CONFIG1_NTC_TYPE_STANDARD 0x00
#define BALANCER4_CONFIG1_NTC_TYPE_JEITA    0x80
#define BALANCER4_CONFIG1_VCELL_BAL_3p5V    0x00
#define BALANCER4_CONFIG1_VCELL_BAL_3p7V    0x40
#define BALANCER4_CONFIG1_BAL_THD_H2L_50mV  0x00
#define BALANCER4_CONFIG1_BAL_THD_H2L_70mV  0x20
#define BALANCER4_CONFIG1_BAL_THD_L2H_50mV  0x00
#define BALANCER4_CONFIG1_BAL_THD_L2H_70mV  0x10
#define BALANCER4_CONFIG1_ICC_250mA         0x00
#define BALANCER4_CONFIG1_ICC_300mA         0x01
#define BALANCER4_CONFIG1_ICC_350mA         0x02
#define BALANCER4_CONFIG1_ICC_400mA         0x03
#define BALANCER4_CONFIG1_ICC_450mA         0x04
#define BALANCER4_CONFIG1_ICC_500mA         0x05
#define BALANCER4_CONFIG1_ICC_550mA         0x06
#define BALANCER4_CONFIG1_ICC_600mA         0x07
#define BALANCER4_CONFIG1_ICC_650mA         0x08
#define BALANCER4_CONFIG1_ICC_700mA         0x09
#define BALANCER4_CONFIG1_ICC_750mA         0x0A
#define BALANCER4_CONFIG1_ICC_800mA         0x0B
#define BALANCER4_CONFIG1_ICC_850mA         0x0C
#define BALANCER4_CONFIG1_ICC_900mA         0x0D
#define BALANCER4_CONFIG1_ICC_950mA         0x0E
#define BALANCER4_CONFIG1_ICC_1000mA        0x0F

/**
 * @brief Balancer 4 timer register setting.
 * @details Specified setting for timer register of Balancer 4 Click driver.
 */
#define BALANCER4_TIMER_FSW_600KHZ          0x00
#define BALANCER4_TIMER_FSW_1200KHZ         0x80
#define BALANCER4_TIMER_I2C_WD_TIMER_NORMAL 0x00
#define BALANCER4_TIMER_I2C_WD_TIMER_RESET  0x40
#define BALANCER4_TIMER_WD_TIMER_DIS        0x00
#define BALANCER4_TIMER_WD_TIMER_40S        0x10
#define BALANCER4_TIMER_WD_TIMER_80S        0x20
#define BALANCER4_TIMER_WD_TIMER_160S       0x30
#define BALANCER4_TIMER_REGISTER_KEEP       0x00
#define BALANCER4_TIMER_REGISTER_RESET      0x08
#define BALANCER4_TIMER_CHG_TIMER_DIS       0x00
#define BALANCER4_TIMER_CHG_TIMER_8H        0x02
#define BALANCER4_TIMER_CHG_TIMER_20H       0x04
#define BALANCER4_TIMER_CHG_TIMER_12H       0x06
#define BALANCER4_TIMER_EN_SUSP_BOOST_DIS   0x00
#define BALANCER4_TIMER_EN_SUSP_BOOST_EN    0x01

/**
 * @brief Balancer 4 status register setting.
 * @details Specified setting for status register of Balancer 4 Click driver.
 */
#define BALANCER4_STATUS_NOT_CHARGING       0x00
#define BALANCER4_STATUS_PRE_CHARGE         0x10
#define BALANCER4_STATUS_CONSTANT_CHARGE    0x20
#define BALANCER4_STATUS_CHARGING_COMPLETE  0x30
#define BALANCER4_STATUS_CHG_STAT_MASK      0x30
#define BALANCER4_STATUS_NOT_IN_PPM         0x00
#define BALANCER4_STATUS_IN_VIN_PPM         0x08
#define BALANCER4_STATUS_PPM_STAT_MASK      0x08
#define BALANCER4_STATUS_BATTERY_PRESENT    0x00
#define BALANCER4_STATUS_BATTERY_MISSING    0x04
#define BALANCER4_STATUS_BATFLOAT_STAT_MASK 0x04
#define BALANCER4_STATUS_THERM_NORMAL       0x00
#define BALANCER4_STATUS_THERM_REGULATION   0x02
#define BALANCER4_STATUS_THERM_STAT_MASK    0x02
#define BALANCER4_STATUS_NOT_IN_VSYS_MIN    0x00
#define BALANCER4_STATUS_IN_VSYS_MIN_REG    0x01
#define BALANCER4_STATUS_VSYS_STAT_MASK     0x01

/**
 * @brief Balancer 4 fault register setting.
 * @details Specified setting for fault register of Balancer 4 Click driver.
 */
#define BALANCER4_FAULT_WD                  0x80
#define BALANCER4_FAULT_INPUT               0x40
#define BALANCER4_FAULT_THERMAL_SD          0x20
#define BALANCER4_FAULT_TIMER               0x10
#define BALANCER4_FAULT_BAT                 0x08
#define BALANCER4_FAULT_NTC_COLD            0x01
#define BALANCER4_FAULT_NTC_COOL            0x02
#define BALANCER4_FAULT_NTC_WARM            0x03
#define BALANCER4_FAULT_NTC_HOT             0x04
#define BALANCER4_FAULT_NTC_MASK            0x07

/**
 * @brief Balancer 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Balancer 4 Click driver.
 */
#define BALANCER4_SET_DEV_ADDR              0x4B

/*! @} */ // balancer4_set

/**
 * @defgroup balancer4_map Balancer 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Balancer 4 Click driver.
 */

/**
 * @addtogroup balancer4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Balancer 4 Click to the selected MikroBUS.
 */
#define BALANCER4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // balancer4_map
/*! @} */ // balancer4

/**
 * @brief Balancer 4 Click context object.
 * @details Context object definition of Balancer 4 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} balancer4_t;

/**
 * @brief Balancer 4 Click configuration object.
 * @details Configuration object definition of Balancer 4 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} balancer4_cfg_t;

/**
 * @brief Balancer 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BALANCER4_OK = 0,
    BALANCER4_ERROR = -1

} balancer4_return_value_t;

/*!
 * @addtogroup balancer4 Balancer 4 Click Driver
 * @brief API for configuring and manipulating Balancer 4 Click driver.
 * @{
 */

/**
 * @brief Balancer 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #balancer4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void balancer4_cfg_setup ( balancer4_cfg_t *cfg );

/**
 * @brief Balancer 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #balancer4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #balancer4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t balancer4_init ( balancer4_t *ctx, balancer4_cfg_t *cfg );

/**
 * @brief Balancer 4 default configuration function.
 * @details This function executes a default configuration of Balancer 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #balancer4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t balancer4_default_cfg ( balancer4_t *ctx );

/**
 * @brief Balancer 4 write register function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #balancer4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t balancer4_write_register ( balancer4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Balancer 4 write and verify register function.
 * @details This function writes a desired data byte to the selected register and verifies if
 * is is written correctly by reading it.
 * @param[in] ctx : Click context object.
 * See #balancer4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t balancer4_write_and_verify_register ( balancer4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Balancer 4 read register function.
 * @details This function reads a data byte from the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #balancer4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t balancer4_read_register ( balancer4_t *ctx, uint8_t reg, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // BALANCER4_H

/*! @} */ // balancer4

// ------------------------------------------------------------------------ END
