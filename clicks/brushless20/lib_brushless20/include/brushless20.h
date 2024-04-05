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
 * @file brushless20.h
 * @brief This file contains API for Brushless 20 Click Driver.
 */

#ifndef BRUSHLESS20_H
#define BRUSHLESS20_H

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
 * @addtogroup brushless20 Brushless 20 Click Driver
 * @brief API for configuring and manipulating Brushless 20 Click driver.
 * @{
 */

/**
 * @defgroup brushless20_reg Brushless 20 Registers List
 * @brief List of registers of Brushless 20 Click driver.
 */

/**
 * @addtogroup brushless20_reg
 * @{
 */

/**
 * @brief Brushless 20 PCA9538A registers.
 * @details Specified PCA9538A registers of Brushless 20 Click driver.
 */
#define BRUSHLESS20_REG_INPUT                       0x00
#define BRUSHLESS20_REG_OUTPUT                      0x01
#define BRUSHLESS20_REG_POLARITY                    0x02
#define BRUSHLESS20_REG_CONFIG                      0x03

/*! @} */ // brushless20_reg

/**
 * @defgroup brushless20_set Brushless 20 Registers Settings
 * @brief Settings for registers of Brushless 20 Click driver.
 */

/**
 * @addtogroup brushless20_set
 * @{
 */

/**
 * @brief Brushless 20 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Brushless 20 Click driver.
 */
#define BRUSHLESS20_NONE_PIN                        0x00
#define BRUSHLESS20_IN1_PIN                         0x01
#define BRUSHLESS20_EN1_PIN                         0x02
#define BRUSHLESS20_IN2_PIN                         0x04
#define BRUSHLESS20_EN2_PIN                         0x08
#define BRUSHLESS20_IN3_PIN                         0x10
#define BRUSHLESS20_EN3_PIN                         0x20
#define BRUSHLESS20_NRST_PIN                        0x40
#define BRUSHLESS20_FLT_PIN                         0x80
#define BRUSHLESS20_ALL_PINS                        0xFF

/**
 * @brief Brushless 20 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Brushless 20 Click driver.
 */
#define BRUSHLESS20_DEFAULT_CONFIG                  0x80

/**
 * @brief Brushless 20 direction setting.
 * @details Specified setting for direction of Brushless 20 Click driver.
 */
#define BRUSHLESS20_DIR_CW                          0
#define BRUSHLESS20_DIR_CCW                         1

/**
 * @brief Brushless 20 pin logic level setting.
 * @details Specified setting for pin logic level of Brushless 20 Click driver.
 */
#define BRUSHLESS20_PIN_LOW_LEVEL                   0
#define BRUSHLESS20_PIN_HIGH_LEVEL                  1

/**
 * @brief Brushless 20 trapezoidal (120 percents) commutation state settings.
 * @details Specified trapezoidal (120 percents) commutation state settings of Brushless 20 Click driver.
 */
#define BRUSHLESS20_TR_COM_STATE_COAST              0
#define BRUSHLESS20_TR_COM_STATE_1                  1
#define BRUSHLESS20_TR_COM_STATE_2                  2
#define BRUSHLESS20_TR_COM_STATE_3                  3
#define BRUSHLESS20_TR_COM_STATE_4                  4
#define BRUSHLESS20_TR_COM_STATE_5                  5
#define BRUSHLESS20_TR_COM_STATE_6                  6
#define BRUSHLESS20_TR_COM_STATE_BRAKE              7

/**
 * @brief Brushless 20 driving speed and time settings.
 * @details Specified driving speed and time settings of Brushless 20 Click driver.
 */
#define BRUSHLESS20_SPEED_MIN                       0
#define BRUSHLESS20_SPEED_MAX                       100
#define BRUSHLESS20_NUM_PIN_TOGGLE                  8
#define BRUSHLESS20_ROUND_TO_NEAREAST_INT           0.5

/**
 * @brief Brushless 20 commutation sequance duration settings.
 * @details Specified commutation sequance duration settings of Brushless 20 Click driver.
 * @note In order to improve driving time accuracy, measure and adjust the following macros for your setup.
 * Call brushless20_perform_com_sequence for MAX and MAX-1 speed and measure the duration of each execution.
 * @b BRUSHLESS20_COM_SEQ_DURATION_FOR_SPEED_MAX = duration for a single commutation sequance in milliseconds for MAX speed.
 * @b BRUSHLESS20_COM_SEQ_DURATION_SPEED_STEP = duration for a single commutation sequance in milliseconds for MAX-1 speed - 
 *                                              @b BRUSHLESS20_COM_SEQ_DURATION_FOR_SPEED_MAX.
 */
#define BRUSHLESS20_COM_SEQ_DURATION_FOR_SPEED_MAX  24.729
#define BRUSHLESS20_COM_SEQ_DURATION_SPEED_STEP     ( 29.4361 - BRUSHLESS20_COM_SEQ_DURATION_FOR_SPEED_MAX )

/**
 * @brief Brushless 20 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 20 Click driver.
 */
#define BRUSHLESS20_DEVICE_ADDRESS_A1A0_00          0x70
#define BRUSHLESS20_DEVICE_ADDRESS_A1A0_01          0x71
#define BRUSHLESS20_DEVICE_ADDRESS_A1A0_10          0x72
#define BRUSHLESS20_DEVICE_ADDRESS_A1A0_11          0x73

/*! @} */ // brushless20_set

/**
 * @defgroup brushless20_map Brushless 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 20 Click driver.
 */

/**
 * @addtogroup brushless20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 20 Click to the selected MikroBUS.
 */
#define BRUSHLESS20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless20_map
/*! @} */ // brushless20

/**
 * @brief Brushless 20 Click context object.
 * @details Context object definition of Brushless 20 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t slp;          /**< Sleep mode pin. */
    digital_out_t rst;          /**< PCA9538A reset pin. */

    // Input pins
    digital_in_t  int_pin;      /**< PCA9538A interrupt pin. */

    // Modules
    i2c_master_t  i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} brushless20_t;

/**
 * @brief Brushless 20 Click configuration object.
 * @details Configuration object definition of Brushless 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t slp;             /**< Sleep mode pin. */
    pin_name_t rst;             /**< PCA9538A reset pin. */
    pin_name_t int_pin;         /**< PCA9538A interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} brushless20_cfg_t;

/**
 * @brief Brushless 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS20_OK = 0,
    BRUSHLESS20_ERROR = -1

} brushless20_return_value_t;

/*!
 * @addtogroup brushless20 Brushless 20 Click Driver
 * @brief API for configuring and manipulating Brushless 20 Click driver.
 * @{
 */

/**
 * @brief Brushless 20 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless20_cfg_setup ( brushless20_cfg_t *cfg );

/**
 * @brief Brushless 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless20_init ( brushless20_t *ctx, brushless20_cfg_t *cfg );

/**
 * @brief Brushless 20 default configuration function.
 * @details This function executes a default configuration of Brushless 20
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless20_default_cfg ( brushless20_t *ctx );

/**
 * @brief Brushless 20 write register function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless20_write_register ( brushless20_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Brushless 20 read register function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless20_read_register ( brushless20_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Brushless 20 set pins function.
 * @details This function sets and clears the value of the selected pins of PCA9538A port expander.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless20_set_pins ( brushless20_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief Brushless 20 get fault pin function.
 * @details This function returns the fault pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @return @li @c  1 - High logic state,
 *         @li @c  0 - Low logic state,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless20_get_fault_pin ( brushless20_t *ctx );

/**
 * @brief Brushless 20 reset port expander function.
 * @details This function resets the port expander by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless20_reset_port_expander ( brushless20_t *ctx );

/**
 * @brief Brushless 20 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void brushless20_set_rst_pin ( brushless20_t *ctx, uint8_t state );

/**
 * @brief Brushless 20 enter sleep mode function.
 * @details This function enters sleep mode by setting the SLP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless20_enter_sleep_mode ( brushless20_t *ctx );

/**
 * @brief Brushless 20 exit sleep mode function.
 * @details This function exits sleep mode by setting the SLP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless20_exit_sleep_mode ( brushless20_t *ctx );

/**
 * @brief Brushless 20 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless20_get_int_pin ( brushless20_t *ctx );

/**
 * @brief Brushless 20 set trapezoidal com state function.
 * @details This function sets the IN1-3, and EN1-3 pins state for the selected trapezoidal commutation state.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @param[in] state : Trapezoidal commutation state (0-7) - BRUSHLESS20_TR_COM_STATE_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless20_set_trapezoidal_com_state ( brushless20_t *ctx, uint8_t state );

/**
 * @brief Brushless 20 toggle pin function.
 * @details This function toggles the selected pin of PCA9538A port expander @b BRUSHLESS20_NUM_PIN_TOGGLE times
 * with a delay of (@b speed + 1) * 100us between each toggle.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @param[in] pin_mask : Pin to toggle mask.
 * @param[in] speed : Speed (0-100).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless20_toggle_pin ( brushless20_t *ctx, uint8_t pin_mask, uint8_t speed );

/**
 * @brief Brushless 20 perform com sequence function.
 * @details This function performs a single commutation sequence for the selected rotation direction at
 * a desired speed.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @param[in] dir : Rotation direction.
 *                  @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @param[in] speed : Speed (0-100).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless20_perform_com_sequence ( brushless20_t *ctx, uint8_t dir, uint8_t speed );

/**
 * @brief Brushless 20 drive motor function.
 * @details This function drives the motor for a desired time by performing multiple commutation sequences 
 * for the selected rotation direction at a desired speed.
 * @param[in] ctx : Click context object.
 * See #brushless20_t object definition for detailed explanation.
 * @param[in] dir : Rotation direction.
 *                  @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @param[in] speed : Speed (0-100).
 * @param[in] time_ms : Driving time in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note In order to improve driving time accuracy, measure and adjust the following macros for your setup.
 * Call brushless20_perform_com_sequence for MAX and MAX-1 speed and measure the duration of each execution.
 * @b BRUSHLESS20_COM_SEQ_DURATION_FOR_SPEED_MAX = duration for a single commutation sequance in milliseconds for MAX speed.
 * @b BRUSHLESS20_COM_SEQ_DURATION_SPEED_STEP = duration for a single commutation sequance in milliseconds for MAX-1 speed - 
 *                                              @b BRUSHLESS20_COM_SEQ_DURATION_FOR_SPEED_MAX..
 */
err_t brushless20_drive_motor ( brushless20_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS20_H

/*! @} */ // brushless20

// ------------------------------------------------------------------------ END
