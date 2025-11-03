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
 * @file bldcfoc2.h
 * @brief This file contains API for BLDC FOC 2 Click Driver.
 */

#ifndef BLDCFOC2_H
#define BLDCFOC2_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup bldcfoc2 BLDC FOC 2 Click Driver
 * @brief API for configuring and manipulating BLDC FOC 2 Click driver.
 * @{
 */

/**
 * @defgroup bldcfoc2_reg BLDC FOC 2 Registers List
 * @brief List of registers of BLDC FOC 2 Click driver.
 */

/**
 * @addtogroup bldcfoc2_reg
 * @{
 */

/**
 * @brief BLDC FOC 2 register list .
 * @details Specified register list of BLDC FOC 2 Click driver.
 */
#define BLDCFOC2_REG_EEPROM_8          0x08
#define BLDCFOC2_REG_EEPROM_9          0x09
#define BLDCFOC2_REG_EEPROM_10         0x0A
#define BLDCFOC2_REG_EEPROM_11         0x0B
#define BLDCFOC2_REG_EEPROM_12         0x0C
#define BLDCFOC2_REG_EEPROM_13         0x0D
#define BLDCFOC2_REG_EEPROM_14         0x0E
#define BLDCFOC2_REG_EEPROM_15         0x0F
#define BLDCFOC2_REG_EEPROM_16         0x10
#define BLDCFOC2_REG_EEPROM_17         0x11
#define BLDCFOC2_REG_EEPROM_18         0x12
#define BLDCFOC2_REG_EEPROM_19         0x13
#define BLDCFOC2_REG_EEPROM_20         0x14
#define BLDCFOC2_REG_EEPROM_21         0x15
#define BLDCFOC2_REG_EEPROM_22         0x16
#define BLDCFOC2_REG_EEPROM_23         0x17
#define BLDCFOC2_REG_EEPROM_24         0x18
#define BLDCFOC2_REG_EEPROM_25         0x19
#define BLDCFOC2_REG_EEPROM_26         0x1A
#define BLDCFOC2_REG_EEPROM_27         0x1B
#define BLDCFOC2_REG_EEPROM_28         0x1C
#define BLDCFOC2_REG_EEPROM_29         0x1D
#define BLDCFOC2_REG_EEPROM_30         0x1E
#define BLDCFOC2_REG_EEPROM_31         0x1F
#define BLDCFOC2_REG_EEPROM_32         0x20
#define BLDCFOC2_REG_EEPROM_33         0x21
#define BLDCFOC2_REG_EEPROM_34         0x22
#define BLDCFOC2_REG_EEPROM_35         0x23
#define BLDCFOC2_REG_EEPROM_36         0x24
#define BLDCFOC2_REG_EEPROM_37         0x25
#define BLDCFOC2_REG_EEPROM_38         0x26
#define BLDCFOC2_REG_EEPROM_39         0x27
#define BLDCFOC2_REG_EEPROM_40         0x28
#define BLDCFOC2_REG_EEPROM_41         0x29
#define BLDCFOC2_REG_EEPROM_42         0x2A
#define BLDCFOC2_REG_EEPROM_43         0x2B
#define BLDCFOC2_REG_EEPROM_44         0x2C
#define BLDCFOC2_REG_EEPROM_45         0x2D
#define BLDCFOC2_REG_EEPROM_46         0x2E
#define BLDCFOC2_REG_EEPROM_47         0x2F
#define BLDCFOC2_REG_EEPROM_48         0x30
#define BLDCFOC2_REG_EEPROM_49         0x31
#define BLDCFOC2_REG_EEPROM_50         0x32
#define BLDCFOC2_REG_EEPROM_51         0x33
#define BLDCFOC2_REG_EEPROM_52         0x34
#define BLDCFOC2_REG_EEPROM_53         0x35
#define BLDCFOC2_REG_EEPROM_54         0x36
#define BLDCFOC2_REG_EEPROM_55         0x37
#define BLDCFOC2_REG_EEPROM_56         0x38
#define BLDCFOC2_REG_EEPROM_57         0x39
#define BLDCFOC2_REG_EEPROM_58         0x3A
#define BLDCFOC2_REG_EEPROM_59         0x3B
#define BLDCFOC2_REG_EEPROM_60         0x3C
#define BLDCFOC2_REG_EEPROM_61         0x3D
#define BLDCFOC2_REG_EEPROM_62         0x3E
#define BLDCFOC2_REG_EEPROM_63         0x3F
#define BLDCFOC2_REG_EEPROM_CTRL       0xBF
#define BLDCFOC2_REG_EEPROM_ADDR       0xC0
#define BLDCFOC2_REG_EEPROM_DATA       0xC1
#define BLDCFOC2_REG_EEPROM_ACCESS     0xC4

/*! @} */ // bldcfoc2_reg

/**
 * @defgroup bldcfoc2_set BLDC FOC 2 Registers Settings
 * @brief Settings for registers of BLDC FOC 2 Click driver.
 */

/**
 * @addtogroup bldcfoc2_set
 * @{
 */

/**
 * @brief BLDC FOC 2 EEPROM default setting.
 * @details Specified default setting for EEPROM for F80 PRO KV1900 motor of BLDC FOC 2 Click driver.
 * Configured for 11.2V 10A power supply and PWM input frequency 20KHz with duty cycle range 10 to 50%.
 */
#define BLDCFOC2_EEPROM_8              0x0047FF
#define BLDCFOC2_EEPROM_9              0x0000FA
#define BLDCFOC2_EEPROM_10             0x0067FF
#define BLDCFOC2_EEPROM_11             0x000000
#define BLDCFOC2_EEPROM_12             0x007FF3
#define BLDCFOC2_EEPROM_13             0x000109
#define BLDCFOC2_EEPROM_14             0x000E2A
#define BLDCFOC2_EEPROM_15             0x006270
#define BLDCFOC2_EEPROM_16             0x00006C
#define BLDCFOC2_EEPROM_17             0x002457
#define BLDCFOC2_EEPROM_18             0x00DA0D
#define BLDCFOC2_EEPROM_19             0x007701
#define BLDCFOC2_EEPROM_20             0x003238
#define BLDCFOC2_EEPROM_21             0x000060
#define BLDCFOC2_EEPROM_22             0x006007
#define BLDCFOC2_EEPROM_23             0x00041E
#define BLDCFOC2_EEPROM_24             0x000006
#define BLDCFOC2_EEPROM_25             0x000014
#define BLDCFOC2_EEPROM_26             0x000012
#define BLDCFOC2_EEPROM_27             0x000000
#define BLDCFOC2_EEPROM_28             0x000DA1
#define BLDCFOC2_EEPROM_29             0x000011
#define BLDCFOC2_EEPROM_30             0x000000
#define BLDCFOC2_EEPROM_31             0x00007E
#define BLDCFOC2_EEPROM_32             0x000000
#define BLDCFOC2_EEPROM_33             0x000000
#define BLDCFOC2_EEPROM_34             0x000000
#define BLDCFOC2_EEPROM_35             0x000000
#define BLDCFOC2_EEPROM_36             0x000000
#define BLDCFOC2_EEPROM_37             0x000000
#define BLDCFOC2_EEPROM_38             0x000000
#define BLDCFOC2_EEPROM_39             0x000000
#define BLDCFOC2_EEPROM_40             0x000000
#define BLDCFOC2_EEPROM_41             0x000000
#define BLDCFOC2_EEPROM_42             0x000000
#define BLDCFOC2_EEPROM_43             0x000000
#define BLDCFOC2_EEPROM_44             0x000000
#define BLDCFOC2_EEPROM_45             0x000000
#define BLDCFOC2_EEPROM_46             0x000000
#define BLDCFOC2_EEPROM_47             0x000000
#define BLDCFOC2_EEPROM_48             0x000000
#define BLDCFOC2_EEPROM_49             0x000000
#define BLDCFOC2_EEPROM_50             0x000000
#define BLDCFOC2_EEPROM_51             0x000000
#define BLDCFOC2_EEPROM_52             0x000000
#define BLDCFOC2_EEPROM_53             0x000000
#define BLDCFOC2_EEPROM_54             0x000000
#define BLDCFOC2_EEPROM_55             0x000000
#define BLDCFOC2_EEPROM_56             0x000000
#define BLDCFOC2_EEPROM_57             0x000000
#define BLDCFOC2_EEPROM_58             0x000000
#define BLDCFOC2_EEPROM_59             0x000000
#define BLDCFOC2_EEPROM_60             0x000000
#define BLDCFOC2_EEPROM_61             0x000000
#define BLDCFOC2_EEPROM_62             0x000000
#define BLDCFOC2_EEPROM_63             0x000000

/**
 * @brief BLDC FOC 2 EEPROM setting.
 * @details Specified setting for EEPROM of BLDC FOC 2 Click driver.
 */
#define BLDCFOC2_EEPROM_CTRL_RD        0x000008
#define BLDCFOC2_EEPROM_CTRL_WR        0x000004
#define BLDCFOC2_EEPROM_CTRL_ER        0x000002
#define BLDCFOC2_EEPROM_CTRL_EN        0x000001
#define BLDCFOC2_EEPROM_ACCESS_LOCK    0x000000
#define BLDCFOC2_EEPROM_ACCESS_UNLOCK  0x000001
#define BLDCFOC2_EEPROM_DATA_CLEAR     0x000000
#define BLDCFOC2_EEPROM_SHADOW_OFFSET  64

/**
 * @brief BLDC FOC 2 direction setting.
 * @details Specified setting for direction of BLDC FOC 2 Click driver.
 */
#define BLDCFOC2_DIR_CCW               0
#define BLDCFOC2_DIR_CW                1

/**
 * @brief BLDC FOC 2 speed settings.
 * @details Specified setting for speed settings as percentage of duty cycle of BLDC FOC 2 Click driver.
 */
#define BLDCFOC2_SPEED_MIN             10
#define BLDCFOC2_SPEED_START           15
#define BLDCFOC2_SPEED_MAX             50
#define BLDCFOC2_SPEED_TO_DUTY         100

/**
 * @brief BLDC FOC 2 default PWM settings.
 * @details Specified setting for default PWM settings of BLDC FOC 2 Click driver.
 */
#define BLDCFOC2_PWM_FREQ              20000
#define BLDCFOC2_PWM_ZERO_DUTY         0.0

/**
 * @brief BLDC FOC 2 device address setting.
 * @details Specified setting for device slave address selection of
 * BLDC FOC 2 Click driver.
 */
#define BLDCFOC2_DEVICE_ADDRESS        0x55 

/*! @} */ // bldcfoc2_set

/**
 * @defgroup bldcfoc2_map BLDC FOC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of BLDC FOC 2 Click driver.
 */

/**
 * @addtogroup bldcfoc2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLDC FOC 2 Click to the selected MikroBUS.
 */
#define BLDCFOC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fgo = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // bldcfoc2_map
/*! @} */ // bldcfoc2

/**
 * @brief BLDC FOC 2 Click context object.
 * @details Context object definition of BLDC FOC 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< RST/Brake control pin (active low). */
    digital_out_t dir;          /**< Direction control pin. */

    // Input pins
    digital_in_t fgo;           /**< Motor speed indication pin. */
    digital_in_t fault;         /**< Fault indicator pin. */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

} bldcfoc2_t;

/**
 * @brief BLDC FOC 2 Click configuration object.
 * @details Configuration object definition of BLDC FOC 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t pwm;             /**< PWM pin. */

    // Additional gpio pins
    pin_name_t fgo;             /**< Motor speed indication pin. */
    pin_name_t rst;             /**< RST/Brake control pin (active low). */
    pin_name_t dir;             /**< Direction control pin. */
    pin_name_t fault;           /**< Fault indicator pin. */

    // Static variable
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */
    uint32_t i2c_speed;         /**< I2C serial speed. */
    uint8_t i2c_address;        /**< I2C slave address. */

} bldcfoc2_cfg_t;

/**
 * @brief BLDC FOC 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BLDCFOC2_OK = 0,
    BLDCFOC2_ERROR = -1

} bldcfoc2_return_value_t;

/*!
 * @addtogroup bldcfoc2 BLDC FOC 2 Click Driver
 * @brief API for configuring and manipulating BLDC FOC 2 Click driver.
 * @{
 */

/**
 * @brief BLDC FOC 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bldcfoc2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bldcfoc2_cfg_setup ( bldcfoc2_cfg_t *cfg );

/**
 * @brief BLDC FOC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bldcfoc2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc2_init ( bldcfoc2_t *ctx, bldcfoc2_cfg_t *cfg );

/**
 * @brief BLDC FOC 2 default configuration function.
 * @details This function executes a default configuration of BLDC FOC 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t bldcfoc2_default_cfg ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 write register function.
 * @details This function writes a 24-bit data to the selected register.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written (24-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_write_reg ( bldcfoc2_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief BLDC FOC 2 read register function.
 * @details This function reads a 24-bit data from the selected register.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data (24-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_read_reg ( bldcfoc2_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief BLDC FOC 2 read multiple registers function.
 * @details This function reads multiple 24-bit values starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @param[in] reg : Starting register address.
 * @param[out] data_out : Buffer to store read values.
 * @param[in] len : Number of registers to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_read_regs ( bldcfoc2_t *ctx, uint8_t reg, uint32_t *data_out, uint8_t len );

/**
 * @brief BLDC FOC 2 set duty cycle function.
 * @details This function sets the PWM duty cycle used to control the motor speed.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle (0.0 - 1.0).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_set_duty_cycle ( bldcfoc2_t *ctx, float duty_cycle );

/**
 * @brief BLDC FOC 2 stop PWM function.
 * @details This function stops the PWM output.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_pwm_stop ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 start PWM function.
 * @details This function starts the PWM output.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_pwm_start ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 pull brake function.
 * @details This function pulls the brake by setting the RST pin to a low logic state.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bldcfoc2_pull_brake ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 release brake function.
 * @details This function releases the brake by setting the RST pin to a high logic state.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bldcfoc2_release_brake ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 set direction function.
 * @details This function sets the motor rotation direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @param[in] dir : Direction logic level (0 or 1).
 * @return None.
 * @note None.
 */
void bldcfoc2_set_direction ( bldcfoc2_t *ctx, uint8_t dir );

/**
 * @brief BLDC FOC 2 switch direction function.
 * @details This function toggles the motor rotation direction by inverting the DIR pin state.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bldcfoc2_switch_direction ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 get FGO pin state function.
 * @details This function returns the logic state of the FGO (FG Out) pin.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t bldcfoc2_get_fgo_pin ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 get FAULT pin state function.
 * @details This function returns the logic state of the FAULT pin.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t bldcfoc2_get_fault_pin ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 EEPROM access lock function.
 * @details This function locks the EEPROM access by writing the appropriate command.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_eeprom_access_lock ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 EEPROM access unlock function.
 * @details This function unlocks the EEPROM access by writing the appropriate command.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_eeprom_access_unlock ( bldcfoc2_t *ctx );

/**
 * @brief BLDC FOC 2 EEPROM erase function.
 * @details This function erases the EEPROM content at the selected address.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM register address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_eeprom_erase ( bldcfoc2_t *ctx, uint8_t addr );

/**
 * @brief BLDC FOC 2 EEPROM write function.
 * @details This function writes a 24-bit value to the selected EEPROM register.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM register address.
 * @param[in] data_in : Data to be written (24-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_eeprom_write ( bldcfoc2_t *ctx, uint8_t addr, uint32_t data_in );

/**
 * @brief BLDC FOC 2 EEPROM read function.
 * @details This function reads a 24-bit value from the selected EEPROM register.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM register address.
 * @param[out] data_out : Pointer to memory where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_eeprom_read ( bldcfoc2_t *ctx, uint8_t addr, uint32_t *data_out );

/**
 * @brief BLDC FOC 2 EEPROM default config function.
 * @details This function sets the default EEPROM configuration for the motor F80 PRO KV1900,
 * optimized for 11.2V 10A power supply and PWM input range 10-50% at 20kHz.
 * @param[in] ctx : Click context object.
 * See #bldcfoc2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t bldcfoc2_eeprom_set_config ( bldcfoc2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BLDCFOC2_H

/*! @} */ // bldcfoc2

// ------------------------------------------------------------------------ END
