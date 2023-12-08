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
 * @file stepper16.h
 * @brief This file contains API for Stepper16 Click Driver.
 */

#ifndef STEPPER16_H
#define STEPPER16_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

/*!
 * @addtogroup stepper16 Stepper16 Click Driver
 * @brief API for configuring and manipulating Stepper16 Click driver.
 * @{
 */

/**
 * @defgroup stepper16_reg Stepper16 Registers List
 * @brief List of registers of Stepper16 Click driver.
 */

/**
 * @addtogroup stepper16_reg
 * @{
 */

/**
 * @brief Stepper16 control and status register.
 * @details Specified register for control and status of Stepper16 Click driver.
 */
#define STEPPER16_REG_CR1           0x01
#define STEPPER16_REG_CR2           0x02
#define STEPPER16_REG_CR3           0x03
#define STEPPER16_REG_CR4           0x04
#define STEPPER16_REG_CR5           0x0B
#define STEPPER16_REG_CR6           0x0C
#define STEPPER16_REG_SR1           0x05
#define STEPPER16_REG_SR2           0x06
#define STEPPER16_REG_SR3           0x07
#define STEPPER16_REG_SR4           0x08
#define STEPPER16_REG_SR5           0x09
#define STEPPER16_REG_SR6           0x0A

/*! @} */ // stepper16_reg

/**
 * @defgroup stepper16_set Stepper16 Registers Settings
 * @brief Settings for registers of Stepper16 Click driver.
 */

/**
 * @addtogroup stepper16_set
 * @{
 */

/**
 * @brief Stepper16 step resolution.
 * @details Specified setting for step resolution of Stepper16 Click driver.
 */
#define STEPPER16_STEP_RES_FULL     0x7
#define STEPPER16_STEP_RES_HALF     0x3
#define STEPPER16_STEP_RES_QUARTER  0x2
#define STEPPER16_STEP_RES_1div8    0x1
#define STEPPER16_STEP_RES_1div16   0x0

/**
 * @brief Stepper 18 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER16_SPEED_VERY_SLOW   1
#define STEPPER16_SPEED_SLOW        2
#define STEPPER16_SPEED_MEDIUM      3
#define STEPPER16_SPEED_FAST        4 
#define STEPPER16_SPEED_VERY_FAST   5

/*! @} */ // stepper16_set

/**
 * @defgroup stepper16_map Stepper16 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper16 Click driver.
 */

/**
 * @addtogroup stepper16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper16 Click to the selected MikroBUS.
 */
#define STEPPER16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.nxt = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.err = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper16_map
/*! @} */ // stepper16

/**
 * @brief Stepper16 Click context object.
 * @details Context object definition of Stepper16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  dir;         /**< Direction. */
    digital_out_t  nxt;         /**< Next step control. */
    digital_out_t  cs;         /**< Next step control. */

    // Input pins
    digital_in_t  err;          /**< Error interrupt. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    //status bits
    uint8_t spierr;             /**< SPI ERROR. */
    uint8_t uv;                 /**< Under voltage detection. */
    uint8_t eldef;              /**< Eletrical defect. */
    uint8_t tsd;                /**< Thermal shutdown. */
    uint8_t tw;                 /**< Thermal warning. */
    
    uint16_t steps;             /**< Motor steps. */
    float resolution;           /**< Description. */
    uint8_t step_resolution;    /**< Description. */

} stepper16_t;

/**
 * @brief Stepper16 Click configuration object.
 * @details Configuration object definition of Stepper16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                 /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  dir;                                /**< Direction. */
    pin_name_t  nxt;                                /**< Next step control. */
    pin_name_t  err;                                /**< Error interrupt. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} stepper16_cfg_t;

/**
 * @brief Stepper16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   STEPPER16_OK = 0,
   STEPPER16_ERROR = -1

} stepper16_return_value_t;

/*!
 * @addtogroup stepper16 Stepper16 Click Driver
 * @brief API for configuring and manipulating Stepper16 Click driver.
 * @{
 */

/**
 * @brief Stepper16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper16_cfg_setup ( stepper16_cfg_t *cfg );

/**
 * @brief Stepper16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper16_init ( stepper16_t *ctx, stepper16_cfg_t *cfg );

/**
 * @brief Stepper16 default configuration function.
 * @details This function executes a default configuration of Stepper16
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper16_default_cfg ( stepper16_t *ctx );

/**
 * @brief Stepper16 data writing function.
 * @details This function writes a data to
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper16_generic_write ( stepper16_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Stepper16 data reading function.
 * @details This function reads a data from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper16_generic_read ( stepper16_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Set next step state.
 * @details This function sets a @b nxt pin to high/low state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] value : Logic state to set.
 * @return Nothing.
 */
void stepper16_set_next ( stepper16_t *ctx, uint8_t value );

/**
 * @brief Set direction.
 * @details This function sets a @b dir pin to high/low state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] value : Logic state to set.
 * @return Nothing.
 */
void stepper16_set_dir ( stepper16_t *ctx, uint8_t value );

/**
 * @brief Get error.
 * @details This function gets a @b err pin.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Logic state of pin.
 */
uint8_t stepper16_get_error_flag ( stepper16_t *ctx );

/**
 * @brief Resets device.
 * @details This function resets device.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Nothing.
 * @note Uppon powerup device user need to call this function and 
 * to read @b STEPPER16_REG_SR1 to clear under voltage error.
 */
void stepper16_hard_reset ( stepper16_t *ctx );

/**
 * @brief Transimt wake up signal.
 * @details This function toggles cs pin to signal wake up.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Nothing.
 */
void stepper16_wake_up ( stepper16_t *ctx );

/**
 * @brief Set step resolution.
 * @details This function set step resolution fo motor control.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] step_res : Step resolution:
 *                      @li @c  7 - Full step,
 *                      @li @c  3 - Half step,
 *                      @li @c  2 - Quarter step,
 *                      @li @c  1 - 1/8 step,
 *                      @li @c  0 - 1/16 step.
 * @return Nothing.
 */
void stepper16_set_step_resolution ( stepper16_t *ctx, uint8_t step_res );

/**
 * @brief Move motor in angle value.
 * @details This function moves motor for desired angle value.
 * @param[in] ctx : Click context object.
 * See #stepper16_t object definition for detailed explanation.
 * @param[in] degree : Degrees to move.
 * @param[in] speed : Predefined speed macros:
 *                  @li @c  1 - Very Slow,
 *                  @li @c  2 - Slow,
 *                  @li @c  3 - Normal,
 *                  @li @c  4 - Fast,
 *                  @li @c  5 - Very Fast.
 * @return Nothing
 */
void stepper16_move_motor_angle ( stepper16_t *ctx, float degree, uint8_t speed );

/**
 * @brief Move motor in step value.
 * @details This function moves motor for desired step value.
 * @param[in] ctx : Click context object.
 * See #stepper16_t object definition for detailed explanation.
 * @param[in] steps : Steps to move.
 * @param[in] speed : Predefined speed macros:
 *                  @li @c  1 - Very Slow,
 *                  @li @c  2 - Slow,
 *                  @li @c  3 - Normal,
 *                  @li @c  4 - Fast,
 *                  @li @c  5 - Very Fast.
 * @return Nothing
 */
void stepper16_move_motor_step ( stepper16_t *ctx, uint16_t steps, uint8_t speed );

/**
 * @brief Calculate step-degree resolution.
 * @details This function calculates resolution of selected motor steps.
 * @param[in] ctx : Click context object.
 * See #stepper16_t object definition for detailed explanation.
 * @return Nothing.
 * @note It calculates steps set from context object and sets resolution of it's member.
 */
void stepper16_calculate_resolution ( stepper16_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // STEPPER16_H

/*! @} */ // stepper16

// ------------------------------------------------------------------------ END
