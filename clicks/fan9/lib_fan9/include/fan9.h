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
 * @file fan9.h
 * @brief This file contains API for Fan 9 Click Driver.
 */

#ifndef FAN9_H
#define FAN9_H

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
 * @addtogroup fan9 Fan 9 Click Driver
 * @brief API for configuring and manipulating Fan 9 Click driver.
 * @{
 */

/**
 * @defgroup fan9_reg Fan 9 Registers List
 * @brief List of registers of Fan 9 Click driver.
 */

/**
 * @addtogroup fan9_reg
 * @{
 */

/**
 * @brief Fan 9 description register.
 * @details Specified register for description of Fan 9 Click driver.
 */
#define FAN9_REG_EEPROM_ADDR_8          0x08
#define FAN9_REG_EEPROM_ADDR_9          0x09
#define FAN9_REG_EEPROM_ADDR_10         0x0A
#define FAN9_REG_EEPROM_ADDR_11         0x0B
#define FAN9_REG_EEPROM_ADDR_12         0x0C
#define FAN9_REG_EEPROM_ADDR_13         0x0D
#define FAN9_REG_EEPROM_ADDR_14         0x0E
#define FAN9_REG_EEPROM_ADDR_15         0x0F
#define FAN9_REG_EEPROM_ADDR_16         0x10
#define FAN9_REG_EEPROM_ADDR_17         0x11
#define FAN9_REG_EEPROM_ADDR_18         0x12
#define FAN9_REG_EEPROM_ADDR_19         0x13
#define FAN9_REG_EEPROM_ADDR_20         0x14
#define FAN9_REG_EEPROM_ADDR_21         0x15
#define FAN9_REG_EEPROM_ADDR_22         0x16
#define FAN9_REG_EEPROM_ADDR_23         0x17
#define FAN9_REG_EEPROM_ADDR_24         0x18
#define FAN9_REG_EEPROM_ADDR_25         0x19
#define FAN9_REG_EEPROM_ADDR_26         0x1A
#define FAN9_REG_EEPROM_ADDR_27         0x1B
#define FAN9_REG_EEPROM_ADDR_28         0x1C
#define FAN9_REG_EEPROM_ADDR_29         0x1D
#define FAN9_REG_EEPROM_ADDR_30         0x1E
#define FAN9_REG_PWM_VAL                0x65

/*! @} */ // fan9_reg

/**
 * @defgroup fan9_set Fan 9 Registers Settings
 * @brief Settings for registers of Fan 9 Click driver.
 */

/**
 * @addtogroup fan9_set
 * @{
 */

/**
 * @brief Fan 9 description setting.
 * @details Specified setting for description of Fan 9 Click driver.
 */
#define FAN9_SPEED_CTRL_OPEN_LOOP       0x0000
#define FAN9_SPEED_CTRL_CLOASED         0x0001
#define FAN9_PHA_MODE_AUTO              0x0000
#define FAN9_PHA_MODE_LINEAR_PHASE      0x0002
#define FAN9_RD_ENABLED                 0x0000
#define FAN9_RD_DISABLED                0x0004
#define FAN9_SPEED_CONTROL_PWM          0x0000
#define FAN9_SPEED_CONTROL_ANALOG       0x0008
#define FAN9_POLE_PAIR_1                0x0000
#define FAN9_POLE_PAIR_2                0x0010
#define FAN9_POLE_PAIR_3                0x0020
#define FAN9_POLE_PAIR_4                0x0030
#define FAN9_POLE_PAIR_5                0x0040
#define FAN9_POLE_PAIR_6                0x0050
#define FAN9_POLE_PAIR_7                0x0060
#define FAN9_NOCOAST                    0x0080
#define FAN9_COAST                      0x0000
#define FAN9_ALIGNMODE_ALIGN            0x0000
#define FAN9_ALIGNMODE_ONE_CYCLE        0x0100
#define FAN9_QCKSTART_DISABLED          0x0000
#define FAN9_QCKSTART_ENABLED           0x0200
#define FAN9_OVPOPT_DISABLED            0x0000
#define FAN9_OVPOPT_LOCK_DETECT         0x0400
#define FAN9_FGSTRT_FG_DISABLED         0x0000
#define FAN9_FGSTRT_FG_ENABLED          0x0800
#define FAN9_BEMFHYS_LEVEL_0            0x0000
#define FAN9_BEMFHYS_LEVEL_1            0x1000
#define FAN9_BEMFHYS_LEVEL_2            0x2000
#define FAN9_BEMFHYS_LEVEL_3            0x3000
#define FAN9_SOWAUTO_VALUE_0            0x0000
#define FAN9_SOWAUTO_VALUE_1            0x4000
#define FAN9_OCPOPT_RST_AFTER_TLOCK     0x0000
#define FAN9_OCPOPT_RST_AFTER_PWM_ONOFF 0x8000

/**
 * @brief Fan 9 Start DMD values setting.
 * @details Specified setting for Start DMD description of Fan 9 Click driver.
 */
#define FAN9_STRTDMD_VALUE              0x0033
#define FAN9_DMDPOST_VALUE              0xCA00

/**
 * @brief Fan 9 pin state setting.
 * @details Specified setting for pin state of Fan 9 Click driver.
 */
#define FAN9_PIN_STATE_LOW              0x00
#define FAN9_PIN_STATE_HIGH             0x01

/**
 * @brief Fan 9 direction setting.
 * @details Specified setting for direction of Fan 9 Click driver.
 */
#define FAN9_DIRECTION_CW               0x00
#define FAN9_DIRECTION_CCW              0x01

/**
 * @brief Fan 9 brake states setting.
 * @details Specified setting for brake states of Fan 9 Click driver.
 */
#define FAN9_BRAKE_OFF                  0x00
#define FAN9_BRAKE_ON                   0x01

/**
 * @brief Fan 9 pwm calculation setting.
 * @details Specified setting for pwm calculation of Fan 9 Click driver.
 */
#define FAN9_PWM_CALCULATION_CONS       511.0f
#define FAN9_PWM_CALCULATION_MUL        100


/**
 * @brief Fan 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Fan 9 Click driver.
 */
#define FAN9_DEVICE_ADDRESS             0x55

/*! @} */ // fan9_set

/**
 * @defgroup fan9_map Fan 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Fan 9 Click driver.
 */

/**
 * @addtogroup fan9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Fan 9 Click to the selected MikroBUS.
 */
#define FAN9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rd  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.brk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // fan9_map
/*! @} */ // fan9

/**
 * @brief Fan 9 Click context object.
 * @details Context object definition of Fan 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t brk;      /**< Brake pin. */
    digital_out_t dir;      /**< Direction pin. */

    // Input pins
    digital_in_t rd;        /**< Speed output pin. */
    
    digital_in_t flt;       /**< Fault pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} fan9_t;

/**
 * @brief Fan 9 Click configuration object.
 * @details Configuration object definition of Fan 9 Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rd;          /**< Speed output pin. */
    pin_name_t brk;         /**< Brake pin. */
    pin_name_t dir;         /**< Direction pin. */
    pin_name_t flt;         /**< Fault pin. */

    uint32_t   i2c_speed;   /**< I2C serial speed. */
    uint8_t    i2c_address; /**< I2C slave address. */

} fan9_cfg_t;

/**
 * @brief Fan 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FAN9_OK = 0,
    FAN9_ERROR = -1

} fan9_return_value_t;

/*!
 * @addtogroup fan9 Fan 9 Click Driver
 * @brief API for configuring and manipulating Fan 9 Click driver.
 * @{
 */

/**
 * @brief Fan 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #fan9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void fan9_cfg_setup ( fan9_cfg_t *cfg );

/**
 * @brief Fan 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #fan9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan9_init ( fan9_t *ctx, fan9_cfg_t *cfg );

/**
 * @brief Fan 9 default configuration function.
 * @details This function executes a default configuration of Fan 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t fan9_default_cfg ( fan9_t *ctx );

/**
 * @brief Fan 9 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan9_generic_write ( fan9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Fan 9 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan9_generic_read ( fan9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Fan 9 get RD pin state function.
 * @details This function is used to get RD pin state of Fan 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @return RD pin state.
 * @note None.
 */
uint8_t fan9_get_rd_pin ( fan9_t *ctx );

/**
 * @brief Fan 9 get FLT pin state function.
 * @details This function is used to get FLT pin state of Fan 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @return FLT pin state.
 * @note None.
 */
uint8_t fan9_get_flt_pin ( fan9_t *ctx );

/**
 * @brief Fan 9 set direction function.
 * @details This function is used to set direction of Fan 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @param[in] dir : Selected direction.
 * @return Nothing.
 * @note None.
 */
void fan9_set_direction ( fan9_t *ctx, uint8_t dir );

/**
 * @brief Fan 9 set brake state function.
 * @details This function is used to set brake state of Fan 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @param[in] brake_state : Brake state.
 * @return Nothing.
 * @note None.
 */
void fan9_set_brake ( fan9_t *ctx, uint8_t brake_state );

/**
 * @brief Fan 9 register writing function.
 * @details This function writes a desired data bytes into
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan9_write_reg ( fan9_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Fan 9 register reading function.
 * @details This function reads a data bytes from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan9_read_reg ( fan9_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Fan 9 set PWM value function.
 * @details This function is used to set PWM value of Fan 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @param[in] pwm_val : PWM Value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan9_set_pwm ( fan9_t *ctx, uint8_t pwm_val );

/**
 * @brief Fan 9 get PWM value function.
 * @details This function is used to get PWM value of Fan 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #fan9_t object definition for detailed explanation.
 * @param[out] pwm_val : PWM Value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan9_get_pwm ( fan9_t *ctx, uint8_t *pwm_val );

#ifdef __cplusplus
}
#endif
#endif // FAN9_H

/*! @} */ // fan9

// ------------------------------------------------------------------------ END
