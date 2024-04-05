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
 * @file brushless13.h
 * @brief This file contains API for Brushless 13 Click Driver.
 */

#ifndef BRUSHLESS13_H
#define BRUSHLESS13_H

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
 * @addtogroup brushless13 Brushless 13 Click Driver
 * @brief API for configuring and manipulating Brushless 13 Click driver.
 * @{
 */

/**
 * @defgroup brushless13_reg Brushless 13 Registers List
 * @brief List of registers of Brushless 13 Click driver.
 */

/**
 * @addtogroup brushless13_reg
 * @{
 */

/**
 * @brief Brushless 13 description register.
 * @details Specified register for description of Brushless 13 Click driver.
 */
#define BRUSHLESS13_REG_INPUT_PORT                  0x00
#define BRUSHLESS13_REG_OUTPUT_PORT                 0x01
#define BRUSHLESS13_REG_POLARITY_INV                0x02
#define BRUSHLESS13_REG_CONFIG                      0x03

/*! @} */ // brushless13_reg

/**
 * @defgroup brushless13_set Brushless 13 Registers Settings
 * @brief Settings for registers of Brushless 13 Click driver.
 */

/**
 * @addtogroup brushless13_set
 * @{
 */

/**
 * @brief Brushless 13 description setting.
 * @details Specified setting for description of Brushless 13 Click driver.
 */
#define BRUSHLESS13_TR_COM_STATE_COAST              0x00
#define BRUSHLESS13_TR_COM_STATE_1                  0x01
#define BRUSHLESS13_TR_COM_STATE_2                  0x02
#define BRUSHLESS13_TR_COM_STATE_3                  0x03
#define BRUSHLESS13_TR_COM_STATE_4                  0x04
#define BRUSHLESS13_TR_COM_STATE_5                  0x05
#define BRUSHLESS13_TR_COM_STATE_6                  0x06
#define BRUSHLESS13_TR_COM_STATE_BRAKE              0x07

/**
 * @brief Brushless 13 pin mask.
 * @details Specified pin mask of Brushless 13 Click driver.
 */
#define BRUSHLESS13_NONE_PIN                        0x00
#define BRUSHLESS13_ENW_PIN                         0x01
#define BRUSHLESS13_INW_PIN                         0x02
#define BRUSHLESS13_ENV_PIN                         0x04
#define BRUSHLESS13_INV_PIN                         0x08
#define BRUSHLESS13_ENU_PIN                         0x10
#define BRUSHLESS13_INU_PIN                         0x20
#define BRUSHLESS13_FLT_PIN                         0x40
#define BRUSHLESS13_ALL_OUTPUT_PIN                  0x3F
#define BRUSHLESS13_ALL_PIN                         0x7F

/**
 * @brief Brushless 13 mode setting.
 * @details Specified setting for mode of Brushless 13 Click driver.
 */
#define BRUSHLESS13_MODE_ENX_INX                    0x01
#define BRUSHLESS13_MODE_INXL_INXH                  0x00

/**
 * @brief Brushless 13 direction setting.
 * @details Specified setting for direction of Brushless 13 Click driver.
 */
#define BRUSHLESS13_DIR_CW                          0x01
#define BRUSHLESS13_DIR_CCW                         0x00

/**
 * @brief Brushless 13 pin logic level setting.
 * @details Specified setting for pin logic level of Brushless 13 Click driver.
 */
#define BRUSHLESS13_PIN_STATE_LOW                   0x00
#define BRUSHLESS13_PIN_STATE_HIGH                  0x01

/**
 * @brief Brushless 13 FLT pin state setting.
 * @details Specified setting for FLT pin state of Brushless 13 Click driver.
 */
#define BRUSHLESS13_FLT_PIN_INACTIVE                0x01
#define BRUSHLESS13_FLT_PIN_ACTIVE                  0x00

/**
 * @brief Brushless 13 driving speed and time settings.
 * @details Specified driving speed and time settings of Brushless 13 Click driver.
 */
#define BRUSHLESS13_SPEED_MIN                       0
#define BRUSHLESS13_SPEED_MAX                       100
#define BRUSHLESS13_NUM_PIN_TOGGLE                  8
#define BRUSHLESS13_ROUND_TO_NEAREAST_INT           0.5

/**
 * @brief Brushless 13 commutation sequance duration settings.
 * @details Specified commutation sequance duration settings of Brushless 13 Click driver.
 * @note In order to improve driving time accuracy, measure and adjust the following macros for your setup.
 * Call brushless13_perform_com_seq for MAX and MAX-1 speed and measure the duration of each execution.
 * @b BRUSHLESS13_COM_SEQ_DURATION_FOR_SPEED_MAX = duration for a single commutation sequance in milliseconds for MAX speed.
 * @b BRUSHLESS13_COM_SEQ_DURATION_SPEED_STEP = duration for a single commutation sequance in milliseconds for MAX-1 speed - 
 *                                              @b BRUSHLESS13_COM_SEQ_DURATION_FOR_SPEED_MAX.
 */
#define BRUSHLESS13_COM_SEQ_DURATION_FOR_SPEED_MAX  20.293
#define BRUSHLESS13_COM_SEQ_DURATION_SPEED_STEP     ( 20.351 - BRUSHLESS13_COM_SEQ_DURATION_FOR_SPEED_MAX )

/**
 * @brief Brushless 13 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 13 Click driver.
 */
#define BRUSHLESS13_DEVICE_ADDRESS_A1A0_00          0x70
#define BRUSHLESS13_DEVICE_ADDRESS_A1A0_01          0x71
#define BRUSHLESS13_DEVICE_ADDRESS_A1A0_10          0x72
#define BRUSHLESS13_DEVICE_ADDRESS_A1A0_11          0x73

/*! @} */ // brushless13_set

/**
 * @defgroup brushless13_map Brushless 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 13 Click driver.
 */

/**
 * @addtogroup brushless13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 13 Click to the selected MikroBUS.
 */
#define BRUSHLESS13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.mod = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless13_map
/*! @} */ // brushless13

/**
 * @brief Brushless 13 Click context object.
 * @details Context object definition of Brushless 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */
    digital_out_t mod;          /**< Mode selection pin. */

    // Input pins
    digital_in_t flt;           /**< Fault pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint8_t mode;               /**< PWM mode. */
    
} brushless13_t;

/**
 * @brief Brushless 13 Click configuration object.
 * @details Configuration object definition of Brushless 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t mod;             /**< Mode selection pin. */
    pin_name_t flt;             /**< Fault pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} brushless13_cfg_t;

/**
 * @brief Brushless 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS13_OK = 0,
    BRUSHLESS13_ERROR = -1

} brushless13_return_value_t;

/*!
 * @addtogroup brushless13 Brushless 13 Click Driver
 * @brief API for configuring and manipulating Brushless 13 Click driver.
 * @{
 */

/**
 * @brief Brushless 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless13_cfg_setup ( brushless13_cfg_t *cfg );

/**
 * @brief Brushless 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_init ( brushless13_t *ctx, brushless13_cfg_t *cfg );

/**
 * @brief Brushless 13 default configuration function.
 * @details This function executes a default configuration of Brushless 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless13_default_cfg ( brushless13_t *ctx );

/**
 * @brief Brushless 13 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_generic_write ( brushless13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Brushless 13 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_generic_read ( brushless13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Brushless 13 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] state : State of the RST pin.
 * @return None.
 * @note None.
 */
void brushless13_set_rst_pin ( brushless13_t *ctx, uint8_t pin_state );

/**
 * @brief Brushless 13 get flt pin function.
 * @details This function reads FLT pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] state : State of the RST pin.
 * @return @li @c 0 - Fault state,
 *         @li @c 1 - No fault state.
 * @note None.
 */
uint8_t brushless13_get_flt_state ( brushless13_t *ctx );

/**
 * @brief Brushless 13 set mode pin function.
 * @details This function sets the mod pin logic state, regulating operation mode.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] mode_sel : Mode selection.
 * @return None.
 * @note None.
 */
void brushless13_set_mode ( brushless13_t *ctx, uint8_t mode_sel );

/**
 * @brief Brushless 13 reset port expander function.
 * @details This function resets the port expander by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless13_reset_port_exp ( brushless13_t *ctx );

/**
 * @brief Brushless 13 get fault pin function.
 * @details This function returns the fault pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @return State of the FLT pin.
 * @note None.
 */
uint8_t brushless13_get_flt_pin ( brushless13_t *ctx );

/**
 * @brief Brushless 13 write register function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_write_reg ( brushless13_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Brushless 13 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_read_reg ( brushless13_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Brushless 13 set pins function.
 * @details This function sets and clears the value of the selected pins of PCA9538A port expander.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_set_pins ( brushless13_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief Brushless 13 set trapezoidal com state function.
 * @details This function sets the pin state for the selected trapezoidal commutation state.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] state : Trapezoidal commutation state (0-7) - BRUSHLESS26_TR_COM_STATE_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_set_trap_com_state ( brushless13_t *ctx, uint8_t state );

/**
 * @brief Brushless 13 toggle pin function.
 * @details This function toggles the selected pin of port expander @b BRUSHLESS26_NUM_PIN_TOGGLE times
 * with a delay of (@b speed + 1) * 100us between each toggle.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] pin_mask : Pin to toggle mask.
 * @param[in] speed : Speed (0-100).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_toggle_pin ( brushless13_t *ctx, uint8_t pin_mask, uint8_t speed );

/**
 * @brief Brushless 13 perform com sequence function.
 * @details This function performs a single commutation sequence for the selected rotation direction at
 * a desired speed.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] dir : Rotation direction.
 * @param[in] speed : Speed (0-100).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_perform_com_seq ( brushless13_t *ctx, uint8_t dir, uint8_t speed );

/**
 * @brief Brushless 13 drive motor function.
 * @details This function drives the motor for a desired time by performing multiple commutation sequences 
 * for the selected rotation direction at a desired speed.
 * @param[in] ctx : Click context object.
 * See #brushless13_t object definition for detailed explanation.
 * @param[in] dir : Rotation direction.
 * @param[in] speed : Speed (0-100).
 * @param[in] time_ms : Driving time in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless13_drive_motor ( brushless13_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS13_H

/*! @} */ // brushless13

// ------------------------------------------------------------------------ END
