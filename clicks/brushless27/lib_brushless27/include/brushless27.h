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
 * @file brushless27.h
 * @brief This file contains API for Brushless 27 Click Driver.
 */

#ifndef BRUSHLESS27_H
#define BRUSHLESS27_H

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
 * @addtogroup brushless27 Brushless 27 Click Driver
 * @brief API for configuring and manipulating Brushless 27 Click driver.
 * @{
 */

/**
 * @defgroup brushless27_reg Brushless 27 Registers List
 * @brief List of registers of Brushless 27 Click driver.
 */

/**
 * @addtogroup brushless27_reg
 * @{
 */

/**
 * @brief Brushless 27 description register.
 * @details Specified register for description of Brushless 27 Click driver.
 */
#define BRUSHLESS27_REG_INPUT_PORT                  0x00
#define BRUSHLESS27_REG_OUTPUT_PORT                 0x01
#define BRUSHLESS27_REG_POLARITY_INV                0x02
#define BRUSHLESS27_REG_CONFIG                      0x03

/*! @} */ // brushless27_reg

/**
 * @defgroup brushless27_set Brushless 27 Registers Settings
 * @brief Settings for registers of Brushless 27 Click driver.
 */

/**
 * @addtogroup brushless27_set
 * @{
 */

/**
 * @brief Brushless 27 description setting.
 * @details Specified setting for description of Brushless 27 Click driver.
 */
#define BRUSHLESS27_TR_COM_STATE_COAST              0x00
#define BRUSHLESS27_TR_COM_STATE_1                  0x01
#define BRUSHLESS27_TR_COM_STATE_2                  0x02
#define BRUSHLESS27_TR_COM_STATE_3                  0x03
#define BRUSHLESS27_TR_COM_STATE_4                  0x04
#define BRUSHLESS27_TR_COM_STATE_5                  0x05
#define BRUSHLESS27_TR_COM_STATE_6                  0x06
#define BRUSHLESS27_TR_COM_STATE_BRAKE              0x07

/**
 * @brief Brushless 27 pin mask.
 * @details Specified pin mask of Brushless 27 Click driver.
 */
#define BRUSHLESS27_NONE_PIN                        0x00
#define BRUSHLESS27_UH_PIN                          0x01
#define BRUSHLESS27_VH_PIN                          0x02
#define BRUSHLESS27_WH_PIN                          0x04
#define BRUSHLESS27_VL_PIN                          0x10
#define BRUSHLESS27_WL_PIN                          0x20
#define BRUSHLESS27_UL_PIN                          0x40
#define BRUSHLESS27_FLT_PIN                         0x80
#define BRUSHLESS27_ALL_OUTPUT_PIN                  0x77
#define BRUSHLESS27_ALL_PIN                         0xF7

/**
 * @brief Brushless 27 mode setting.
 * @details Specified setting for mode of Brushless 27 Click driver.
 */
#define BRUSHLESS27_MODE_ENX_INX                    0x01
#define BRUSHLESS27_MODE_INXL_INXH                  0x00

/**
 * @brief Brushless 27 direction setting.
 * @details Specified setting for direction of Brushless 27 Click driver.
 */
#define BRUSHLESS27_DIR_CW                          0x01
#define BRUSHLESS27_DIR_CCW                         0x00

/**
 * @brief Brushless 27 pin logic level setting.
 * @details Specified setting for pin logic level of Brushless 27 Click driver.
 */
#define BRUSHLESS27_PIN_STATE_LOW                   0x00
#define BRUSHLESS27_PIN_STATE_HIGH                  0x01

/**
 * @brief Brushless 27 FLT pin state setting.
 * @details Specified setting for FLT pin state of Brushless 27 Click driver.
 */
#define BRUSHLESS27_FLT_PIN_INACTIVE                0x01
#define BRUSHLESS27_FLT_PIN_ACTIVE                  0x00

/**
 * @brief Brushless 27 driving speed and time settings.
 * @details Specified driving speed and time settings of Brushless 27 Click driver.
 */
#define BRUSHLESS27_SPEED_MIN                       0
#define BRUSHLESS27_SPEED_MAX                       100
#define BRUSHLESS27_NUM_PIN_TOGGLE                  8
#define BRUSHLESS27_ROUND_TO_NEAREAST_INT           0.5

/**
 * @brief Brushless 27 commutation sequance duration settings.
 * @details Specified commutation sequance duration settings of Brushless 27 Click driver.
 * @note In order to improve driving time accuracy, measure and adjust the following macros for your setup.
 * Call brushless27_perform_com_seq for MAX and MAX-1 speed and measure the duration of each execution.
 * @b BRUSHLESS27_COM_SEQ_DURATION_FOR_SPEED_MAX = duration for a single commutation sequance in milliseconds for MAX speed.
 * @b BRUSHLESS27_COM_SEQ_DURATION_SPEED_STEP = duration for a single commutation sequance in milliseconds for MAX-1 speed - 
 *                                              @b BRUSHLESS27_COM_SEQ_DURATION_FOR_SPEED_MAX.
 */
#define BRUSHLESS27_COM_SEQ_DURATION_FOR_SPEED_MAX  21.611
#define BRUSHLESS27_COM_SEQ_DURATION_SPEED_STEP     ( 22.044 - BRUSHLESS27_COM_SEQ_DURATION_FOR_SPEED_MAX )

/**
 * @brief Brushless 27 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 27 Click driver.
 */
#define BRUSHLESS27_DEVICE_ADDRESS_A1A0_00          0x70
#define BRUSHLESS27_DEVICE_ADDRESS_A1A0_01          0x71
#define BRUSHLESS27_DEVICE_ADDRESS_A1A0_10          0x72
#define BRUSHLESS27_DEVICE_ADDRESS_A1A0_11          0x73

/*! @} */ // brushless27_set

/**
 * @defgroup brushless27_map Brushless 27 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 27 Click driver.
 */

/**
 * @addtogroup brushless27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 27 Click to the selected MikroBUS.
 */
#define BRUSHLESS27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sen = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless27_map
/*! @} */ // brushless27

/**
 * @brief Brushless 27 Click context object.
 * @details Context object definition of Brushless 27 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */

    // Input pins
    digital_in_t sen;           /**< Sense pin. */
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} brushless27_t;

/**
 * @brief Brushless 27 Click configuration object.
 * @details Configuration object definition of Brushless 27 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t sen;             /**< Sense pin. */
    pin_name_t rst;             /**< Reset pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} brushless27_cfg_t;

/**
 * @brief Brushless 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS27_OK = 0,
    BRUSHLESS27_ERROR = -1

} brushless27_return_value_t;

/*!
 * @addtogroup brushless27 Brushless 27 Click Driver
 * @brief API for configuring and manipulating Brushless 27 Click driver.
 * @{
 */

/**
 * @brief Brushless 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless27_cfg_setup ( brushless27_cfg_t *cfg );

/**
 * @brief Brushless 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_init ( brushless27_t *ctx, brushless27_cfg_t *cfg );

/**
 * @brief Brushless 27 default configuration function.
 * @details This function executes a default configuration of Brushless 27
 * Click board.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless27_default_cfg ( brushless27_t *ctx );

/**
 * @brief Brushless 27 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_generic_write ( brushless27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Brushless 27 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_generic_read ( brushless27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Brushless 27 get Sense pin function.
 * @details This function is used to get Sense pin state.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t brushless27_get_sen_pin ( brushless27_t *ctx );

/**
 * @brief Brushless 27 get Interrupt pin function.
 * @details This function is used to get Interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t brushless27_get_int_pin ( brushless27_t *ctx );

/**
 * @brief Brushless 27 reset port expander function.
 * @details This function resets the port expander by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless27_reset_port_exp ( brushless27_t *ctx );

/**
 * @brief Brushless 27 get Fault pin function.
 * @details This function returns the Fault pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error / Fault pin active.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_get_flt_pin ( brushless27_t *ctx );

/**
 * @brief Brushless 27 write register function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_write_reg ( brushless27_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Brushless 27 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_read_reg ( brushless27_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Brushless 27 set pins function.
 * @details This function sets and clears the value of the selected pins of PCA9538A port expander.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_set_pins ( brushless27_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief Brushless 27 set trapezoidal com state function.
 * @details This function sets the pin state for the selected trapezoidal commutation state.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] state : Trapezoidal commutation state (0-7) - BRUSHLESS26_TR_COM_STATE_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_set_trap_com_state ( brushless27_t *ctx, uint8_t state );

/**
 * @brief Brushless 27 toggle pin function.
 * @details This function toggles the selected pin of port expander @b BRUSHLESS26_NUM_PIN_TOGGLE times
 * with a delay of (@b speed + 1) * 100us between each toggle.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] pin_mask : Pin to toggle mask.
 * @param[in] speed : Speed (0-100).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_toggle_pin ( brushless27_t *ctx, uint8_t pin_mask, uint8_t speed );

/**
 * @brief Brushless 27 perform com sequence function.
 * @details This function performs a single commutation sequence for the selected rotation direction at
 * a desired speed.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] dir : Rotation direction.
 * @param[in] speed : Speed (0-100).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_perform_com_seq ( brushless27_t *ctx, uint8_t dir, uint8_t speed );

/**
 * @brief Brushless 27 drive motor function.
 * @details This function drives the motor for a desired time by performing multiple commutation sequences 
 * for the selected rotation direction at a desired speed.
 * @param[in] ctx : Click context object.
 * See #brushless27_t object definition for detailed explanation.
 * @param[in] dir : Rotation direction.
 * @param[in] speed : Speed (0-100).
 * @param[in] time_ms : Driving time in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless27_drive_motor ( brushless27_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS27_H

/*! @} */ // brushless27

// ------------------------------------------------------------------------ END
