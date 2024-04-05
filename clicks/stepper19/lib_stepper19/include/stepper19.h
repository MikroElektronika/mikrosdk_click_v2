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
 * @file stepper19.h
 * @brief This file contains API for Stepper 19 Click Driver.
 */

#ifndef STEPPER19_H
#define STEPPER19_H

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
 * @addtogroup stepper19 Stepper 19 Click Driver
 * @brief API for configuring and manipulating Stepper 19 Click driver.
 * @{
 */

/**
 * @defgroup stepper19_reg Stepper 19 Registers List
 * @brief List of registers of Stepper 19 Click driver.
 */

/**
 * @addtogroup stepper19_reg
 * @{
 */

/**
 * @brief Stepper 19 description register.
 * @details Specified register for description of Stepper 19 Click driver.
 */
#define STEPPER19_REG_IN_PORT                0x00
#define STEPPER19_REG_OUT_PORT               0x01
#define STEPPER19_REG_POL_INV                0x02
#define STEPPER19_REG_CONFIG                 0x03

/*! @} */ // stepper19_reg

/**
 * @defgroup stepper19_set Stepper 19 Registers Settings
 * @brief Settings for registers of Stepper 19 Click driver.
 */

/**
 * @addtogroup stepper19_set
 * @{
 */

/**
 * @brief Stepper 19 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 19 Click driver.
 */
#define STEPPER19_PIN_STATE_LOW              0
#define STEPPER19_PIN_STATE_HIGH             1

/**
 * @brief Stepper 19 step/direction driver mode.
 * @details Specified step/direction driver mode of Stepper 19 Click driver.
 */
#define STEPPER19_DIR_CLOCKWISE              0
#define STEPPER19_DIR_COUNTERCLOCKWISE       1

/**
 * @brief Stepper 19 GPIO expander pin setting.
 * @details Specified setting for pin bit mask of Stepper 19 Click driver.
 */
#define STEPPER19_PIN_NONE                   0x00
#define STEPPER19_PIN_M0                     0x01
#define STEPPER19_PIN_M1                     0x02
#define STEPPER19_PIN_DEC0                   0x04
#define STEPPER19_PIN_DEC1                   0x08
#define STEPPER19_PIN_TOFF                   0x10
#define STEPPER19_PIN_STP                    0x20
#define STEPPER19_PIN_DIR                    0x40

/**
 * @brief Stepper 19 GPIO expander pin setting.
 * @details Specified setting for pin bit mask of Stepper 19 Click driver.
 */
#define STEPPER19_CTRL_STEP_DIR_GPIO         0
#define STEPPER19_CTRL_STEP_DIR_PORT_EXP     1

/**
 * @brief Stepper 19 port expander pin direction config.
 * @details Specified port expander pin direction config of Stepper 19 Click driver.
 */
#define STEPPER19_PORT_EXP_DEFAULT_CFG       0x03

/**
 * @brief Stepper 19 microstepping indexer settings.
 * @details Microstepping indexer settings of Stepper 19 Click driver.
 */
#define STEPPER19_MSTEP_MODE_FULL            1
#define STEPPER19_MSTEP_MODE_HALF            2
#define STEPPER19_MSTEP_MODE_1_4             4
#define STEPPER19_MSTEP_MODE_1_8             8
#define STEPPER19_MSTEP_MODE_1_16            16
#define STEPPER19_MSTEP_MODE_1_32            32
#define STEPPER19_MSTEP_MODE_1_64            64
#define STEPPER19_MSTEP_MODE_1_128           128
#define STEPPER19_MSTEP_MODE_1_256           256

/**
 * @brief Stepper 19 decay mode settings.
 * @details Decay mode settings of Stepper 19 Click driver.
 */
#define STEPPER19_DECAY_MODE_DYN             0
#define STEPPER19_DECAY_MODE_XRP             1
#define STEPPER19_DECAY_MODE_F_30            2
#define STEPPER19_DECAY_MODE_SLW             3

/**
 * @brief Stepper 19 TOFF settings.
 * @details TOFF settings of Stepper 19 Click driver.
 */
#define STEPPER19_TOFF_7US                   0
#define STEPPER19_TOFF_16US                  1

/**
 * @brief Stepper 19 step delay default value.
 * @details Specified step delay default value of Stepper 19 Click driver.
 */
#define STEPPER19_STEP_DELAY_DEF_100US        2ul

/**
 * @brief Stepper 19 step speed and angle data values.
 * @details Specified step speed and angle data values of Stepper 19 Click driver.
 */
#define STEPPER19_FULL_STEP                  1.0f
#define STEPPER19_STEP_SPEED_MIN             1
#define STEPPER19_STEP_SPEED_MAX             100
#define STEPPER19_ANGLE_360_DEGREES          360.0f

/**
 * @brief Stepper 19 calculation data values.
 * @details Specified calculation data values of Stepper 19 Click driver.
 */
#define STEPPER19_FULL_CIRCLE                360.0
#define STEPPER19_RESOLUTION                 4096.0
#define STEPPER19_VREF                       3330.0

/**
 * @brief Stepper 19 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 19 Click driver.
 */
#define STEPPER19_DEVICE_ADDRESS_0           0x70
#define STEPPER19_DEVICE_ADDRESS_1           0x72
#define STEPPER19_DEVICE_ADDRESS_2           0x74
#define STEPPER19_DEVICE_ADDRESS_3           0x76

/*! @} */ // stepper19_set

/**
 * @defgroup stepper19_map Stepper 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 19 Click driver.
 */

/**
 * @addtogroup stepper19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 19 Click to the selected MikroBUS.
 */
#define STEPPER19_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_CS );  \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.stp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper19_map
/*! @} */ // stepper19

/**
 * @brief Stepper 19 Click context object.
 * @details Context object definition of Stepper 19 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;     /**< Device enable pin. */
    digital_out_t dir;    /**< Direction control pin. */
    digital_out_t stp;    /**< Step signal pin. */

    // Input pins
    digital_in_t flt;     /**< Fault condition pin. */

    // Modules
    i2c_master_t i2c;    /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

    // Motor stepps
    float step_delay;         /**< Step delay. */
    float microstep_mode;     /**< Microstepping mode setting. */
    uint8_t step_dir_mode;    /**< Step and direction control mode. */

} stepper19_t;

/**
 * @brief Stepper 19 Click configuration object.
 * @details Configuration object definition of Stepper 19 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;     /**< Device enable pin. */
    pin_name_t dir;    /**< Direction control pin. */
    pin_name_t stp;    /**< Step signal pin. */
    pin_name_t flt;    /**< Fault condition pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepper19_cfg_t;

/**
 * @brief Stepper 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER19_OK = 0,
    STEPPER19_ERROR = -1

} stepper19_return_value_t;

/*!
 * @addtogroup stepper19 Stepper 19 Click Driver
 * @brief API for configuring and manipulating Stepper 19 Click driver.
 * @{
 */

/**
 * @brief Stepper 19 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper19_cfg_setup ( stepper19_cfg_t *cfg );

/**
 * @brief Stepper 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_init ( stepper19_t *ctx, stepper19_cfg_t *cfg );

/**
 * @brief Stepper 19 default configuration function.
 * @details This function executes a default configuration of Stepper 19
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper19_default_cfg ( stepper19_t *ctx );

/**
 * @brief Stepper 19 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_generic_write ( stepper19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Stepper 19 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_generic_read ( stepper19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Stepper 19 port expander data writing function.
 * @details This function writes a desired data byte to the selected register
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_port_exp_write ( stepper19_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 19 port expander data reading function.
 * @details This function reads a desired data byte from the selected register
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_port_exp_read ( stepper19_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 19 sets the pin states function.
 * @details This function sets and clears the value of the selected pins
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] set_mask : Pin set mask.
 * @param[in] clr_mask : Pin clear mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_set_pins ( stepper19_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief Stepper 19 sets the microstepping mode function.
 * @details This function sets the microstepping mode settings
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] ms_mode : Microstepping mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_set_microstep_mode ( stepper19_t *ctx, uint8_t ms_mode );

/**
 * @brief Stepper 19 sets the decay mode function.
 * @details This function sets the decay mode settings
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] decay_mode : Decay mode settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_set_decay_mode ( stepper19_t *ctx, uint8_t decay_mode );

/**
 * @brief Stepper 19 set toff function.
 * @details This function sets the desired off time value
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] toff : TOFF settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_set_toff ( stepper19_t *ctx, uint8_t toff );

/**
 * @brief Stepper 19 enable device function.
 * @details This function enables the device outputs
 * of the DRV8424EPWPR, Stepper Drivers With Integrated Current Sense, 1/256 Microstepping,
 * STEP/DIR Interface and smart tune Technology on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void stepper19_enable_device ( stepper19_t *ctx );

/**
 * @brief Stepper 19 disable device function.
 * @details This function disables the device outputs
 * of the DRV8424EPWPR, Stepper Drivers With Integrated Current Sense, 1/256 Microstepping,
 * STEP/DIR Interface and smart tune Technology on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void stepper19_disable_device ( stepper19_t *ctx );

/**
 * @brief Stepper 19 sets the direction function.
 * @details This function sets the desired direction of motor movement: clockwise or counterclockwise
 * of the DRV8424EPWPR, Stepper Drivers With Integrated Current Sense, 1/256 Microstepping,
 * STEP/DIR Interface and smart tune Technology on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] dir : Direction of movement.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_set_direction ( stepper19_t *ctx, uint8_t dir );

/**
 * @brief Stepper 19 sets the step function.
 * @details This function sets the step (STP) pin state
 * of the DRV8424EPWPR, Stepper Drivers With Integrated Current Sense, 1/256 Microstepping,
 * STEP/DIR Interface and smart tune Technology on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] step : Step (STP) pin state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_set_step ( stepper19_t *ctx, uint8_t step );

/**
 * @brief Stepper 19 make the one step function.
 * @details This function is used to make the one step of the desired speed
 * of the DRV8424EPWPR, Stepper Drivers With Integrated Current Sense, 1/256 Microstepping,
 * STEP/DIR Interface and smart tune Technology on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] step_speed : Step speed percent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_make_one_step ( stepper19_t *ctx, uint8_t step_speed );

/**
 * @brief Stepper 19 rotates the shaft through a desired angle function.
 * @details This function rotates the shaft through a desired step speed and angle
 * of the DRV8424EPWPR, Stepper Drivers With Integrated Current Sense, 1/256 Microstepping,
 * STEP/DIR Interface and smart tune Technology on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] step_speed : Step speed percent.
 * @param[in] angle : Angle of rotation.
 * @param[in] res_360 : Resolution of steps per revolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_rotate_by_angle ( stepper19_t *ctx, uint8_t step_speed, float angle, uint16_t res_360 );

/**
 * @brief Stepper 19 rotates the shaft through a desired step function.
 * @details This function rotates the shaft through for the specific number of steps at the selected speed
 * of the DRV8424EPWPR, Stepper Drivers With Integrated Current Sense, 1/256 Microstepping,
 * STEP/DIR Interface and smart tune Technology on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @param[in] step_speed : Step speed percent.
 * @param[in] steps : Number of steps to rotate motor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper19_rotate_by_step ( stepper19_t *ctx, uint8_t step_speed, uint16_t steps );

/**
 * @brief Stepper 19 fault indication function.
 * @details This function reads state of the interrupt (FLT) pin
 * of the DRV8424EPWPR, Stepper Drivers With Integrated Current Sense, 1/256 Microstepping,
 * STEP/DIR Interface and smart tune Technology on the Stepper 19 Click board.
 * @param[in] ctx : Click context object.
 * See #stepper19_t object definition for detailed explanation.
 * @return @li @c 0 - Fault condition,
 *         @li @c 1 - Ok.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t stepper19_fault_indication ( stepper19_t *ctx );



#ifdef __cplusplus
}
#endif
#endif // STEPPER19_H

/*! @} */ // stepper19

// ------------------------------------------------------------------------ END
