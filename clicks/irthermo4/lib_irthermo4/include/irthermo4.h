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
 * @file irthermo4.h
 * @brief This file contains API for IR Thermo 4 Click Driver.
 */

#ifndef IRTHERMO4_H
#define IRTHERMO4_H

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
 * @addtogroup irthermo4 IR Thermo 4 Click Driver
 * @brief API for configuring and manipulating IR Thermo 4 Click driver.
 * @{
 */

/**
 * @defgroup irthermo4_reg IR Thermo 4 Registers List
 * @brief List of registers of IR Thermo 4 Click driver.
 */

/**
 * @addtogroup irthermo4_reg
 * @{
 */

/**
 * @brief IR Thermo 4 registers list.
 * @details Specified registers list of IR Thermo 4 Click driver.
 */
#define IRTHERMO4_REG_TP_OBJECT             0x01
#define IRTHERMO4_REG_TP_AMBIENT            0x03
#define IRTHERMO4_REG_TP_OBJ_LP1            0x05
#define IRTHERMO4_REG_TP_OBJ_LP2            0x07
#define IRTHERMO4_REG_TP_AMB_LP3            0x0A
#define IRTHERMO4_REG_TP_OBJ_LP2_FROZEN     0x0C
#define IRTHERMO4_REG_TP_PRESENCE           0x0F
#define IRTHERMO4_REG_TP_MOTION             0x10
#define IRTHERMO4_REG_TP_AMB_SHOCK          0x11
#define IRTHERMO4_REG_INTERRUPT_STATUS      0x12
#define IRTHERMO4_REG_CHIP_STATUS           0x13
#define IRTHERMO4_REG_S_LP1_LP2             0x14
#define IRTHERMO4_REG_S_LP3                 0x15
#define IRTHERMO4_REG_TP_PRESENCE_THOLD     0x16
#define IRTHERMO4_REG_TP_MOTION_THOLD       0x17
#define IRTHERMO4_REG_TP_AMB_SHOCK_THOLD    0x18
#define IRTHERMO4_REG_INTERRUPT_MASK        0x19
#define IRTHERMO4_REG_MULTIPLE              0x1A
#define IRTHERMO4_REG_TIMER_INTERRUPT       0x1B
#define IRTHERMO4_REG_TP_OT_THOLD           0x1C
#define IRTHERMO4_REG_EEPROM_CONTROL        0x1F
#define IRTHERMO4_REG_EEPROM_CONTENT        0x20
#define IRTHERMO4_REG_SLAVE_ADDRESS         0x3F

/*! @} */ // irthermo4_reg

/**
 * @defgroup irthermo4_set IR Thermo 4 Registers Settings
 * @brief Settings for registers of IR Thermo 4 Click driver.
 */

/**
 * @addtogroup irthermo4_set
 * @{
 */

/**
 * @brief IR Thermo 4 temperature calculation values.
 * @details Specified temperature calculation values of IR Thermo 4 Click driver.
 */
#define IRTHERMO4_ROOM_TEMPERATURE          25.0f
#define IRTHERMO4_FUNCTION_EXPONENT         4.2f
#define IRTHERMO4_DIGITS_K_TO_M             100.0f
#define IRTHERMO4_TP_OFFSET_TO_U0           32768
#define IRTHERMO4_TP_OUT_TO_UOUT            2

/**
 * @brief IR Thermo 4 EEPROM control command.
 * @details Specified EEPROM control command of IR Thermo 4 Click driver.
 */
#define IRTHERMO4_EEPROM_READ_ENABLE        0x80
#define IRTHERMO4_EEPROM_READ_DISABLE       0x00

/**
 * @brief IR Thermo 4 refresh slave address command.
 * @details Specified refresh slave address command of IR Thermo 4 Click driver.
 */
#define IRTHERMO4_CMD_RELOAD                0x04

/**
 * @brief IR Thermo 4 device address setting.
 * @details Specified setting for device slave address selection of
 * IR Thermo 4 Click driver.
 */
#define IRTHERMO4_DEVICE_ADDRESS_GEN_CALL   0x00
#define IRTHERMO4_DEVICE_ADDRESS_GND        0x0C
#define IRTHERMO4_DEVICE_ADDRESS_VCC        0x0E

/*! @} */ // irthermo4_set

/**
 * @defgroup irthermo4_map IR Thermo 4 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Thermo 4 Click driver.
 */

/**
 * @addtogroup irthermo4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Thermo 4 Click to the selected MikroBUS.
 */
#define IRTHERMO4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // irthermo4_map
/*! @} */ // irthermo4

/**
 * @brief IR Thermo 4 Click EEPROM content object.
 * @details EEPROM content object definition of IR Thermo 4 Click driver.
 */
typedef struct
{
    uint8_t protocol;           /**< EEPROM Protocol number. */
    uint8_t lookup;             /**< Identifier for look-up-table. */
    uint16_t ptat25;            /**< Tamb output in digits at 25deg Celsius. */
    float m_val;                /**< PTAT slope [digits/K]. */
    uint32_t u0_val;            /**< TP offset. */
    uint32_t uout1;             /**< TP output for Tobj1 at 25deg Celsius. */
    uint8_t tobj1;              /**< Tobj value in deg Celsius for Uout1. */
    uint8_t slave_add;          /**< I2C slave address with external addressing bit. */
    float k_val;                /**< Scaling/calibration factor calculated using EEPROM values. */

} irthermo4_eeprom_t;

/**
 * @brief IR Thermo 4 Click context object.
 * @details Context object definition of IR Thermo 4 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (Active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    irthermo4_eeprom_t eeprom;  /**< EEPROM content. */

} irthermo4_t;

/**
 * @brief IR Thermo 4 Click configuration object.
 * @details Configuration object definition of IR Thermo 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin (Active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} irthermo4_cfg_t;

/**
 * @brief IR Thermo 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRTHERMO4_OK = 0,
    IRTHERMO4_ERROR = -1

} irthermo4_return_value_t;

/*!
 * @addtogroup irthermo4 IR Thermo 4 Click Driver
 * @brief API for configuring and manipulating IR Thermo 4 Click driver.
 * @{
 */

/**
 * @brief IR Thermo 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irthermo4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void irthermo4_cfg_setup ( irthermo4_cfg_t *cfg );

/**
 * @brief IR Thermo 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irthermo4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irthermo4_init ( irthermo4_t *ctx, irthermo4_cfg_t *cfg );

/**
 * @brief IR Thermo 4 default configuration function.
 * @details This function executes a default configuration of IR Thermo 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t irthermo4_default_cfg ( irthermo4_t *ctx );

/**
 * @brief IR Thermo 4 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irthermo4_write_regs ( irthermo4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief IR Thermo 4 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irthermo4_read_regs ( irthermo4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief IR Thermo 4 write reg function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irthermo4_write_reg ( irthermo4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief IR Thermo 4 read reg function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irthermo4_read_reg ( irthermo4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief IR Thermo 4 refresh address function.
 * @details This function reloads the slave address from the EEPROM by issuing the general call command.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irthermo4_refresh_address ( irthermo4_t *ctx );

/**
 * @brief IR Thermo 4 read EEPROM function.
 * @details This function reads the content of EEPROM and stores it in a Click context object.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irthermo4_read_eeprom ( irthermo4_t *ctx );

/**
 * @brief IR Thermo 4 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t irthermo4_get_int_pin ( irthermo4_t *ctx );

/**
 * @brief IR Thermo 4 read ambient temp function.
 * @details This function reads and calculates the ambient temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @param[out] t_amb : Calculated ambient temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irthermo4_read_ambient_temp ( irthermo4_t *ctx, float *t_amb );

/**
 * @brief IR Thermo 4 read object temp function.
 * @details This function reads and calculates the object temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #irthermo4_t object definition for detailed explanation.
 * @param[out] t_obj : Calculated object temperature in degrees Celsius.
 * @param[in] t_amb : Ambient temperature in degrees Celsius (required for the object temperature calculation).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t irthermo4_read_object_temp ( irthermo4_t *ctx, float *t_obj, float t_amb );

#ifdef __cplusplus
}
#endif
#endif // IRTHERMO4_H

/*! @} */ // irthermo4

// ------------------------------------------------------------------------ END
