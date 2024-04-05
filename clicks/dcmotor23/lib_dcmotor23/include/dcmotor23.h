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
 * @file dcmotor23.h
 * @brief This file contains API for DC Motor 23 Click Driver.
 */

#ifndef DCMOTOR23_H
#define DCMOTOR23_H

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
 * @addtogroup dcmotor23 DC Motor 23 Click Driver
 * @brief API for configuring and manipulating DC Motor 23 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor23_reg DC Motor 23 Registers List
 * @brief List of registers of DC Motor 23 Click driver.
 */

/**
 * @addtogroup dcmotor23_reg
 * @{
 */

/**
 * @brief DC Motor 23 description register.
 * @details Specified register for description of DC Motor 23 Click driver.
 */
#define DCMOTOR23_REG_INPUT                 0x00
#define DCMOTOR23_REG_OUTPUT                0x01
#define DCMOTOR23_REG_POLARITY              0x02
#define DCMOTOR23_REG_CONFIG                0x03

/*! @} */ // dcmotor23_reg

/**
 * @defgroup dcmotor23_set DC Motor 23 Registers Settings
 * @brief Settings for registers of DC Motor 23 Click driver.
 */

/**
 * @addtogroup dcmotor23_set
 * @{
 */

/**
 * @brief DC Motor 23 description setting.
 * @details Specified setting for description of DC Motor 23 Click driver.
 */
/**
 * @brief DC Motor 23 pin mask.
 * @details Specified PCA9538 pin mask of DC Motor 23 Click driver.
 */
#define DCMOTOR23_LO_PIN                    0x01
#define DCMOTOR23_PHASE_A_PIN               0x02
#define DCMOTOR23_PHASE_B_PIN               0x04
#define DCMOTOR23_TRQ_A1_PIN                0x08
#define DCMOTOR23_TRQ_A2_PIN                0x10
#define DCMOTOR23_TRQ_B1_PIN                0x20
#define DCMOTOR23_TRQ_B2_PIN                0x40

/**
 * @brief DC Motor 23 pin direction config.
 * @details Specified pin direction config of DC Motor 23 Click driver.
 */
#define DCMOTOR23_DEFAULT_CONFIG            0x01

/**
 * @brief DC Motor 23 pin logic level setting.
 * @details Specified setting for pin logic level of DC Motor 23 Click driver.
 */
#define DCMOTOR23_PIN_LOW_LEVEL             0
#define DCMOTOR23_PIN_HIGH_LEVEL            1

/**
 * @brief DC Motor 23 output mode setting.
 * @details Specified setting for output mode of DC Motor 23 Click driver.
 */
#define DCMOTOR23_MODE_DECAY                0x00
#define DCMOTOR23_MODE_CCW                  0x01
#define DCMOTOR23_MODE_CW                   0x02

/**
 * @brief DC Motor 23 output torque setting.
 * @details Specified setting for output torque of DC Motor 23 Click driver.
 */
#define DCMOTOR23_TORQUE_0                  0x00
#define DCMOTOR23_TORQUE_38                 0x01
#define DCMOTOR23_TORQUE_71                 0x02
#define DCMOTOR23_TORQUE_100                0x03

/**
 * @brief DC Motor 23 output setting.
 * @details Specified setting for output selection of DC Motor 23 Click driver.
 */
#define DCMOTOR23_SEL_OUT_A                 0x00
#define DCMOTOR23_SEL_OUT_B                 0x01

/**
 * @brief DC Motor 23 device address setting.
 * @details Specified setting for device slave address selection of
 * DC Motor 23 Click driver.
 */
#define DCMOTOR23_DEVICE_ADDRESS_0          0x70
#define DCMOTOR23_DEVICE_ADDRESS_1          0x71
#define DCMOTOR23_DEVICE_ADDRESS_2          0x72
#define DCMOTOR23_DEVICE_ADDRESS_3          0x73

/*! @} */ // dcmotor23_set

/**
 * @defgroup dcmotor23_map DC Motor 23 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 23 Click driver.
 */

/**
 * @addtogroup dcmotor23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 23 Click to the selected MikroBUS.
 */
#define DCMOTOR23_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.en_a = MIKROBUS( mikrobus, MIKROBUS_CS );  \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.en_b = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor23_map
/*! @} */ // dcmotor23

/**
 * @brief DC Motor 23 Click context object.
 * @details Context object definition of DC Motor 23 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en_a;      /**< Enable A input pin for motor Ach. */
    digital_out_t slp;       /**< Sleep mode pin. */
    digital_out_t rst;       /**< Reset pin. */
    digital_out_t en_b;      /**< Enable B input pin for motor Ach. */

    // Input pins

    digital_in_t int_pin;    /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} dcmotor23_t;

/**
 * @brief DC Motor 23 Click configuration object.
 * @details Configuration object definition of DC Motor 23 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en_a;           /**< Enable A input pin for motor Ach. */
    pin_name_t slp;            /**< Sleep mode pin. */
    pin_name_t rst;            /**< Reset pin. */
    pin_name_t en_b;           /**< Enable B input pin for motor Ach. */
    pin_name_t int_pin;        /**< Description. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} dcmotor23_cfg_t;

/**
 * @brief DC Motor 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR23_OK = 0,
    DCMOTOR23_ERROR = -1

} dcmotor23_return_value_t;

/*!
 * @addtogroup dcmotor23 DC Motor 23 Click Driver
 * @brief API for configuring and manipulating DC Motor 23 Click driver.
 * @{
 */

/**
 * @brief DC Motor 23 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor23_cfg_setup ( dcmotor23_cfg_t *cfg );

/**
 * @brief DC Motor 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor23_init ( dcmotor23_t *ctx, dcmotor23_cfg_t *cfg );

/**
 * @brief DC Motor 23 default configuration function.
 * @details This function executes a default configuration of DC Motor 23
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor23_default_cfg ( dcmotor23_t *ctx );

/**
 * @brief DC Motor 23 I2C writing function.
 * @details This function writes a desired data byte to the selected PCA9538A register
 * the selected register by using I2C serial interface
 * of the PCA9538 8-bit I2C-bus and SMBus low power I/O port with interrupt and reset
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor23_write_register ( dcmotor23_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DC Motor 23 I2C reading function.
 * @details This function reads data from 
 * the selected PCA9538A register by using I2C serial interface
 * of the PCA9538 8-bit I2C-bus and SMBus low power I/O port with interrupt and reset
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor23_read_register ( dcmotor23_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DC Motor 23 get LO pin function.
 * @details This function reads the LO pin logic state
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[out] pin_state : LO pin logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor23_get_lo_pin ( dcmotor23_t *ctx, uint8_t *pin_state );

/**
 * @brief DC Motor 23 set output mode function.
 * @details This function set desired mode for the selected output
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] mode :
 *         @li @c DCMOTOR23_MODE_DECAY - Decay,
 *         @li @c DCMOTOR23_MODE_CCW   - Counter-Clockwise,
 *         @li @c DCMOTOR23_MODE_CW    - Clockwise.
 * @param[in] sel_motor : 
 *         @li @c DCMOTOR23_SEL_OUT_A - select A output OUTA,
 *         @li @c DCMOTOR23_SEL_OUT_A - select B output OUTB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor23_set_output_mode ( dcmotor23_t *ctx, uint8_t mode, uint8_t sel_motor );

/**
 * @brief DC Motor 23 set clockwise function.
 * @details This function set clockwise for the selected output
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] sel_motor : 
 *         @li @c DCMOTOR23_SEL_OUT_A - select A output OUTA,
 *         @li @c DCMOTOR23_SEL_OUT_A - select B output OUTB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor23_set_clockwise ( dcmotor23_t *ctx, uint8_t sel_motor );

/**
 * @brief DC Motor 23 set counter clockwise function.
 * @details This function set counter clockwise for the selected output
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] sel_motor : 
 *         @li @c DCMOTOR23_SEL_OUT_A - select A output OUTA,
 *         @li @c DCMOTOR23_SEL_OUT_A - select B output OUTB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor23_set_counter_clockwise ( dcmotor23_t *ctx, uint8_t sel_motor );

/**
 * @brief DC Motor 23 set decay function.
 * @details This function set decay for the selected output
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] sel_motor : 
 *         @li @c DCMOTOR23_SEL_OUT_A - select A output OUTA,
 *         @li @c DCMOTOR23_SEL_OUT_A - select B output OUTB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note @li @c Slow Decay - State of the DECAY set to Low level,
 *       @li @c Fast Decay - State of the DECAY set to High level.
 */
err_t dcmotor23_set_decay ( dcmotor23_t *ctx, uint8_t sel_motor );

/**
 * @brief DC Motor 23 set OUTA torque function.
 * @details This function set sets the OUTA torque
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] torque : 
 *         @li @c DCMOTOR23_TORQUE_0 - 0% (Output OFF),
 *         @li @c DCMOTOR23_TORQUE_38 -38%,
 *         @li @c DCMOTOR23_TORQUE_71 -71%,
 *         @li @c DCMOTOR23_TORQUE_100 -100%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor23_set_outa_torque ( dcmotor23_t *ctx, uint8_t torque );

/**
 * @brief DC Motor 23 set OUTB torque function.
 * @details This function sets the OUTB torque
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] torque : 
 *         @li @c DCMOTOR23_TORQUE_0   - 0% (Output OFF),
 *         @li @c DCMOTOR23_TORQUE_38  - 38%,
 *         @li @c DCMOTOR23_TORQUE_71  - 71%,
 *         @li @c DCMOTOR23_TORQUE_100 - 100%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor23_set_outb_torque ( dcmotor23_t *ctx, uint8_t torque );

/**
 * @brief DC Motor 23 set normal operation mode function.
 * @details This function set normal operation mode and enable
 * the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void dcmotor23_normal_operation_mode ( dcmotor23_t *ctx );

/**
 * @brief DC Motor 23 set sleep operation mode function.
 * @details This function set sleep operation mode and disable
 * the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void dcmotor23_sleep_mode ( dcmotor23_t *ctx );

/**
 * @brief DC Motor 23 reset device function.
 * @details This function perform reset
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void dcmotor23_reset_device ( dcmotor23_t *ctx );

/**
 * @brief DC Motor 23 get INT pin function.
 * @details This function get interrupt pin stste
 * of the PCA9538 8-bit I2C-bus and SMBus low power I/O port with interrupt and reset
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @return INT pin logic state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t dcmotor23_get_int_pin ( dcmotor23_t *ctx );

/**
 * @brief DC Motor 23 set EN_A pin function.
 * @details This function sets the ENABLE_A pin logic state
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] state : ENABLE_A pin logic state.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void dcmotor23_set_en_a_pin ( dcmotor23_t *ctx, uint8_t state );

/**
 * @brief DC Motor 23 set EN_B pin function.
 * @details This function sets the ENABLE_B pin logic state
 * of the TB67H480 BiCD Constant Current Dual H-bridge Driver IC
 * on the DC Motor 23 Click board™.
 * @param[in] ctx : Click context object.
 * See #dcmotor23_t object definition for detailed explanation.
 * @param[in] state : ENABLE_B pin logic state.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void dcmotor23_set_en_b_pin ( dcmotor23_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR23_H

/*! @} */ // dcmotor23

// ------------------------------------------------------------------------ END
