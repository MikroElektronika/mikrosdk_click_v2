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
 * @file haptic5.h
 * @brief This file contains API for Haptic 5 Click Driver.
 */

#ifndef HAPTIC5_H
#define HAPTIC5_H

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
 * @addtogroup haptic5 Haptic 5 Click Driver
 * @brief API for configuring and manipulating Haptic 5 Click driver.
 * @{
 */

/**
 * @defgroup haptic5_reg Haptic 5 Registers List
 * @brief List of registers of Haptic 5 Click driver.
 */

/**
 * @addtogroup haptic5_reg
 * @{
 */

/**
 * @brief Haptic 5 register map.
 * @details Specified register map of Haptic 5 Click driver.
 */
#define HAPTIC5_REG_PRODUCT_NUM                 0x0000
#define HAPTIC5_REG_MAJOR_VER                   0x0002
#define HAPTIC5_REG_MINOR_VER                   0x0004
#define HAPTIC5_REG_SYSTEM_STATUS               0x1000
#define HAPTIC5_REG_SYSTEM_SETTINGS             0x1002
#define HAPTIC5_REG_OVER_TEMP_SETTINGS          0x1003
#define HAPTIC5_REG_CONT_MODE_REP_TIME          0x1004
#define HAPTIC5_REG_SYSTEM_CONTROL              0x1006
#define HAPTIC5_REG_HAPTIC_CONTROL              0x1007
#define HAPTIC5_REG_HBRIDGE_SETUP               0x2000
#define HAPTIC5_REG_PWM_FREQUENCY               0x20A0
#define HAPTIC5_REG_LRA_FREQUENCY               0x20A2
#define HAPTIC5_REG_AUTORESONANCE_BOFF          0x20A4

/*! @} */ // haptic5_reg

/**
 * @defgroup haptic5_set Haptic 5 Settings
 * @brief Settings for configuration of Haptic 5 Click driver.
 */

/**
 * @addtogroup haptic5_set
 * @{
 */

/**
 * @brief Haptic 5 communication select setting.
 * @details Specified setting for communication select of Haptic 5 Click driver.
 */
#define HAPTIC5_COM_PWM                         0
#define HAPTIC5_COM_I2C                         1
#define HAPTIC5_DEFAULT_COM                     HAPTIC5_COM_PWM

/**
 * @brief Haptic 5 PRODUCT_NUM register setting.
 * @details Specified setting for PRODUCT_NUM register of Haptic 5 Click driver.
 */
#define HAPTIC5_PRODUCT_NUM                     0x09B9

/**
 * @brief Haptic 5 SYSTEM_SETTINGS register setting.
 * @details Specified setting for SYSTEM_SETTINGS register of Haptic 5 Click driver.
 */
#define HAPTIC5_SYSTEM_SETTINGS_MODE_NORMAL     0x00
#define HAPTIC5_SYSTEM_SETTINGS_MODE_CONTINUOUS 0x80
#define HAPTIC5_SYSTEM_SETTINGS_MODE_MASK       0x80
#define HAPTIC5_SYSTEM_SETTINGS_TRIGGER_EDGE    0x00
#define HAPTIC5_SYSTEM_SETTINGS_TRIGGER_LEVEL   0x40
#define HAPTIC5_SYSTEM_SETTINGS_TRIGGER_MASK    0x40
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_0MS     0x00
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_512MS   0x04
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_1024MS  0x08
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_1536MS  0x0C
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_2048MS  0x10
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_2560MS  0x14
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_3072MS  0x18
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_3584MS  0x1C
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_4096MS  0x20
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_4608MS  0x24
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_5120MS  0x28
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_5632MS  0x2C
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_6144MS  0x30
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_6656MS  0x34
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_7168MS  0x38
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_7680MS  0x3C
#define HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_MASK    0x3C
#define HAPTIC5_SYSTEM_SETTINGS_PWR_MODE_FAST   0x00
#define HAPTIC5_SYSTEM_SETTINGS_PWR_MODE_ULP    0x01
#define HAPTIC5_SYSTEM_SETTINGS_PWR_MODE_AUTO   0x02
#define HAPTIC5_SYSTEM_SETTINGS_PWR_MODE_MASK   0x03

/**
 * @brief Haptic 5 SYSTEM_CONTROL register setting.
 * @details Specified setting for SYSTEM_CONTROL register of Haptic 5 Click driver.
 */
#define HAPTIC5_SYSTEM_CONTROL_SOFT_RESET       0x02
#define HAPTIC5_SYSTEM_CONTROL_ACK_RESET        0x01

/**
 * @brief Haptic 5 default PWM frequency.
 * @details Specified setting for default PWM frequency of Haptic 5 Click driver.
 */
#define HAPTIC5_PWM_DEF_FREQ                    20000
#define HAPTIC5_PWM_DEF_DUTY                    0.0

/**
 * @brief Haptic 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Haptic 5 Click driver.
 */
#define HAPTIC5_DEVICE_ADDRESS_0                0x54
#define HAPTIC5_DEVICE_ADDRESS_1                0x40
#define HAPTIC5_DEVICE_ADDRESS_0_DEBUG          0x55
#define HAPTIC5_DEVICE_ADDRESS_1_DEBUG          0x41

/*! @} */ // haptic5_set

/**
 * @defgroup haptic5_map Haptic 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Haptic 5 Click driver.
 */

/**
 * @addtogroup haptic5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Haptic 5 Click to the selected MikroBUS.
 */
#define HAPTIC5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.trg = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // haptic5_map
/*! @} */ // haptic5

/**
 * @brief Haptic 5 Click context object.
 * @details Context object definition of Haptic 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t trg;          /**< Trigger haptics pin (I2C mode only). */
    digital_out_t rst;          /**< Reset pin (active low). */
    digital_out_t dir;          /**< Motor drive direction pin (PWM mode only - low:forward, high:reverse). */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    // PWM frequency
    uint32_t pwm_freq;          /**< PWM frequency value. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} haptic5_t;

/**
 * @brief Haptic 5 Click configuration object.
 * @details Configuration object definition of Haptic 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t pwm;             /**< PWM pin. */

    // Additional gpio pins
    pin_name_t trg;             /**< Trigger haptics pin (I2C mode only). */
    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t dir;             /**< Motor drive direction pin (PWM mode only - low:forward, high:reverse). */

    // Static variable
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */
    uint32_t i2c_speed;         /**< I2C serial speed. */
    uint8_t i2c_address;        /**< I2C slave address. */

} haptic5_cfg_t;

/**
 * @brief Haptic 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HAPTIC5_OK = 0,
    HAPTIC5_ERROR = -1

} haptic5_return_value_t;

/*!
 * @addtogroup haptic5 Haptic 5 Click Driver
 * @brief API for configuring and manipulating Haptic 5 Click driver.
 * @{
 */

/**
 * @brief Haptic 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #haptic5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void haptic5_cfg_setup ( haptic5_cfg_t *cfg );

/**
 * @brief Haptic 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #haptic5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic5_init ( haptic5_t *ctx, haptic5_cfg_t *cfg );

/**
 * @brief Haptic 5 default configuration function.
 * @details This function executes a default configuration of Haptic 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t haptic5_default_cfg ( haptic5_t *ctx );

#if ( HAPTIC5_DEFAULT_COM == HAPTIC5_COM_I2C )

/**
 * @brief Haptic 5 write registers function.
 * @details This function writes a sequence of bytes to the selected register address.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_write_regs ( haptic5_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Haptic 5 read registers function.
 * @details This function reads a sequence of bytes from the selected register address.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_read_regs ( haptic5_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Haptic 5 write byte to register function.
 * @details This function writes a single byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_write_reg_byte ( haptic5_t *ctx, uint16_t reg, uint8_t data_in );

/**
 * @brief Haptic 5 read byte from register function.
 * @details This function reads a single byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to output variable for read byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_read_reg_byte ( haptic5_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief Haptic 5 write word to register function.
 * @details This function writes a 16-bit word to the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit word to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_write_reg_word ( haptic5_t *ctx, uint16_t reg, uint16_t data_in );

/**
 * @brief Haptic 5 read word from register function.
 * @details This function reads a 16-bit word from the selected register.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to output variable for read word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_read_reg_word ( haptic5_t *ctx, uint16_t reg, uint16_t *data_out );

/**
 * @brief Haptic 5 check communication function.
 * @details This function checks communication by reading the product number register.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_check_communication ( haptic5_t *ctx );

/**
 * @brief Haptic 5 set TRG pin low function.
 * @details This function sets the TRG pin to a low logic state.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void haptic5_set_trg_low ( haptic5_t *ctx );

/**
 * @brief Haptic 5 set TRG pin high function.
 * @details This function sets the TRG pin to a high logic state.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void haptic5_set_trg_high ( haptic5_t *ctx );

#else

/**
 * @brief Haptic 5 set duty cycle function.
 * @details This function sets the PWM duty cycle.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle value (0.0 to 1.0).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_set_duty_cycle ( haptic5_t *ctx, float duty_cycle );

/**
 * @brief Haptic 5 stop PWM function.
 * @details This function stops the PWM output.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_pwm_stop ( haptic5_t *ctx );

/**
 * @brief Haptic 5 start PWM function.
 * @details This function starts the PWM output.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t haptic5_pwm_start ( haptic5_t *ctx );

/**
 * @brief Haptic 5 set direction forward function.
 * @details This function sets the motor direction to forward (DIR pin LOW).
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void haptic5_set_dir_forward ( haptic5_t *ctx );

/**
 * @brief Haptic 5 set direction reverse function.
 * @details This function sets the motor direction to reverse (DIR pin HIGH).
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void haptic5_set_dir_reverse ( haptic5_t *ctx );

/**
 * @brief Haptic 5 toggle direction function.
 * @details This function toggles the state of the DIR pin.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void haptic5_toggle_dir ( haptic5_t *ctx );

#endif

/**
 * @brief Haptic 5 enable device function.
 * @details This function enables the device by setting the RST pin to HIGH.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void haptic5_enable_device ( haptic5_t *ctx );

/**
 * @brief Haptic 5 disable device function.
 * @details This function disables the device by setting the RST pin to LOW.
 * @param[in] ctx : Click context object.
 * See #haptic5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void haptic5_disable_device ( haptic5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HAPTIC5_H

/*! @} */ // haptic5

// ------------------------------------------------------------------------ END
