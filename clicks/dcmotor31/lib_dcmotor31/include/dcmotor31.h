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
 * @file dcmotor31.h
 * @brief This file contains API for DC Motor 31 Click Driver.
 */

#ifndef DCMOTOR31_H
#define DCMOTOR31_H

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
 * @addtogroup dcmotor31 DC Motor 31 Click Driver
 * @brief API for configuring and manipulating DC Motor 31 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor31_reg DC Motor 31 Registers List
 * @brief List of registers of DC Motor 31 Click driver.
 */

/**
 * @addtogroup dcmotor31_reg
 * @{
 */

/**
 * @brief DC Motor 31 PCA9538A registers.
 * @details Specified PCA9538A registers of DC Motor 31 Click driver.
 */
#define DCMOTOR31_REG_INPUT                     0x00
#define DCMOTOR31_REG_OUTPUT                    0x01
#define DCMOTOR31_REG_POLARITY                  0x02
#define DCMOTOR31_REG_CONFIG                    0x03

/*! @} */ // dcmotor31_reg

/**
 * @defgroup dcmotor31_set DC Motor 31 Registers Settings
 * @brief Settings for registers of DC Motor 31 Click driver.
 */

/**
 * @addtogroup dcmotor31_set
 * @{
 */

/**
 * @brief DC Motor 31 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of DC Motor 31 Click driver.
 */
#define DCMOTOR31_PIN_LO                        0x01
#define DCMOTOR31_PIN_TRQ_0                     0x02
#define DCMOTOR31_PIN_TRQ_1                     0x04
#define DCMOTOR31_PIN_TRQ_2                     0x08
#define DCMOTOR31_PIN_TRQ_3                     0x10
#define DCMOTOR31_PIN_TRQ_4                     0x20
#define DCMOTOR31_PINS_TRQ                      0x3E

/**
 * @brief DC Motor 31 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of DC Motor 31 Click driver.
 */
#define DCMOTOR31_DEFAULT_CONFIG                0xC1

/**
 * @brief DC Motor 31 torque setting.
 * @details Specified setting for torque of DC Motor 31 Click driver.
 */
#define DCMOTOR31_TORQUE_0                      0x00
#define DCMOTOR31_TORQUE_5                      0x01
#define DCMOTOR31_TORQUE_10                     0x02
#define DCMOTOR31_TORQUE_15                     0x03
#define DCMOTOR31_TORQUE_20                     0x04
#define DCMOTOR31_TORQUE_24                     0x05
#define DCMOTOR31_TORQUE_29                     0x06
#define DCMOTOR31_TORQUE_34                     0x07
#define DCMOTOR31_TORQUE_38                     0x08
#define DCMOTOR31_TORQUE_43                     0x09
#define DCMOTOR31_TORQUE_47                     0x0A
#define DCMOTOR31_TORQUE_51                     0x0B
#define DCMOTOR31_TORQUE_56                     0x0C
#define DCMOTOR31_TORQUE_60                     0x0D
#define DCMOTOR31_TORQUE_63                     0x0E
#define DCMOTOR31_TORQUE_67                     0x0F
#define DCMOTOR31_TORQUE_71                     0x10
#define DCMOTOR31_TORQUE_74                     0x11
#define DCMOTOR31_TORQUE_77                     0x12
#define DCMOTOR31_TORQUE_80                     0x13
#define DCMOTOR31_TORQUE_83                     0x14
#define DCMOTOR31_TORQUE_86                     0x15
#define DCMOTOR31_TORQUE_88                     0x16
#define DCMOTOR31_TORQUE_90                     0x17
#define DCMOTOR31_TORQUE_92                     0x18
#define DCMOTOR31_TORQUE_94                     0x19
#define DCMOTOR31_TORQUE_96                     0x1A
#define DCMOTOR31_TORQUE_97                     0x1B
#define DCMOTOR31_TORQUE_98                     0x1C
#define DCMOTOR31_TORQUE_99                     0x1D
#define DCMOTOR31_TORQUE_100                    0x1E

/**
 * @brief DC Motor 31 operating mode setting.
 * @details Specified setting for operating mode of DC Motor 31 Click driver.
 */
#define DCMOTOR31_MODE_BRAKE                    0
#define DCMOTOR31_MODE_FORWARD                  1
#define DCMOTOR31_MODE_REVERSE                  2

/**
 * @brief DC Motor 31 device address setting.
 * @details Specified setting for device slave address selection of
 * DC Motor 31 Click driver.
 */
#define DCMOTOR31_DEVICE_ADDRESS_A1A0_00        0x70
#define DCMOTOR31_DEVICE_ADDRESS_A1A0_01        0x71
#define DCMOTOR31_DEVICE_ADDRESS_A1A0_10        0x72
#define DCMOTOR31_DEVICE_ADDRESS_A1A0_11        0x73

/*! @} */ // dcmotor31_set

/**
 * @defgroup dcmotor31_map DC Motor 31 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 31 Click driver.
 */

/**
 * @addtogroup dcmotor31_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 31 Click to the selected MikroBUS.
 */
#define DCMOTOR31_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sleep = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pha = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor31_map
/*! @} */ // dcmotor31

/**
 * @brief DC Motor 31 Click context object.
 * @details Context object definition of DC Motor 31 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */
    digital_out_t sleep;        /**< Sleep pin (active low). */
    digital_out_t rst;          /**< Reset pin (active low). */
    digital_out_t pha;          /**< Phase pin (high-forward, low-reverse). */

    // Input pins
    digital_in_t int_pin;       /**< PCA9538A interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} dcmotor31_t;

/**
 * @brief DC Motor 31 Click configuration object.
 * @details Configuration object definition of DC Motor 31 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t sleep;           /**< Sleep pin (active low). */
    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t pha;             /**< Phase pin (high-forward, low-reverse). */
    pin_name_t int_pin;         /**< PCA9538A interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} dcmotor31_cfg_t;

/**
 * @brief DC Motor 31 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR31_OK = 0,
    DCMOTOR31_ERROR = -1

} dcmotor31_return_value_t;

/*!
 * @addtogroup dcmotor31 DC Motor 31 Click Driver
 * @brief API for configuring and manipulating DC Motor 31 Click driver.
 * @{
 */

/**
 * @brief DC Motor 31 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor31_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor31_cfg_setup ( dcmotor31_cfg_t *cfg );

/**
 * @brief DC Motor 31 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor31_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor31_init ( dcmotor31_t *ctx, dcmotor31_cfg_t *cfg );

/**
 * @brief DC Motor 31 default configuration function.
 * @details This function executes a default configuration of DC Motor 31
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor31_default_cfg ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 write reg function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor31_write_reg ( dcmotor31_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DC Motor 31 read reg function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor31_read_reg ( dcmotor31_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DC Motor 31 enter sleep mode function.
 * @details This function sets the SLEEP pin to low logic level, putting the device into sleep mode.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor31_enter_sleep ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 exit sleep mode function.
 * @details This function sets the SLEEP pin to high logic level, bringing the device out of sleep mode.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor31_exit_sleep ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 enable device function.
 * @details This function sets the RST pin to high logic level, enabling the device.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor31_enable_device ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 disable device function.
 * @details This function sets the RST pin to low logic level, disabling the device.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor31_disable_device ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 enable output function.
 * @details This function sets the EN pin to high logic level, enabling the motor output.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor31_enable_output ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 disable output function.
 * @details This function sets the EN pin to low logic level, disabling the motor output.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor31_disable_output ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 set forward direction function.
 * @details This function sets the PHA pin to high logic level, configuring the motor to rotate in forward direction.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor31_set_forward_dir ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 set reverse direction function.
 * @details This function sets the PHA pin to low logic level, configuring the motor to rotate in reverse direction.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor31_set_reverse_dir ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 get INT pin function.
 * @details This function reads the logic level of the INT pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dcmotor31_get_int_pin ( dcmotor31_t *ctx );

/**
 * @brief DC Motor 31 get LO pin state function.
 * @details This function reads the LO pin state from the INPUT register.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @param[out] state : LO pin logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t dcmotor31_get_lo_pin ( dcmotor31_t *ctx, uint8_t *state );

/**
 * @brief DC Motor 31 set torque function.
 * @details This function sets the output torque by writing to the OUTPUT register.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @param[in] torque : Torque level (0-30), see DCMOTOR31_TORQUE_x macros definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error or invalid torque.
 * @note None.
 */
err_t dcmotor31_set_torque ( dcmotor31_t *ctx, uint8_t torque );

/**
 * @brief DC Motor 31 set operation mode function.
 * @details This function sets the motor control mode to forward, reverse, or brake.
 * @param[in] ctx : Click context object.
 * See #dcmotor31_t object definition for detailed explanation.
 * @param[in] mode : Operation mode (forward, reverse, or brake), see DCMOTOR31_MODE_x macros definition.
 * @return None.
 * @note None.
 */
void dcmotor31_set_mode ( dcmotor31_t *ctx, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR31_H

/*! @} */ // dcmotor31

// ------------------------------------------------------------------------ END
