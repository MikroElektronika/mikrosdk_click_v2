/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file stepdown13.h
 * @brief This file contains API for Step Down 13 Click Driver.
 */

#ifndef STEPDOWN13_H
#define STEPDOWN13_H

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
 * @addtogroup stepdown13 Step Down 13 Click Driver
 * @brief API for configuring and manipulating Step Down 13 Click driver.
 * @{
 */

/**
 * @defgroup stepdown13_reg Step Down 13 Registers List
 * @brief List of registers of Step Down 13 Click driver.
 */

/**
 * @addtogroup stepdown13_reg
 * @{
 */

/**
 * @brief Step Down 13 control registers.
 * @details Specified registers for control of Step Down 13 Click driver.
 */
#define STEPDOWN13_CONTROL_VREG             0x11
#define STEPDOWN13_CONTROL_NVREG            0x21
#define STEPDOWN13_CONTROL_NVREG_X_VREG     0x61
#define STEPDOWN13_CONTROL_VREG_X_NVREG     0x51

/*! @} */ // stepdown13_reg

/**
 * @defgroup stepdown13_set Step Down 13 Registers Settings
 * @brief Settings for registers of Step Down 13 Click driver.
 */

/**
 * @addtogroup stepdown13_set
 * @{
 */

/**
 * @brief Step Down 13 output calculation setting.
 * @details Specified setting for output calculation of Step Down 13 Click driver.
 */
#define STEPDOWN13_R10_OHM                  100000.0
#define STEPDOWN13_R9_OHM                   10.0
#define STEPDOWN13_WIPER_RES_OHM            325.0
#define STEPDOWN13_FB_VOLTAGE               0.8
#define STEPDOWN13_FULL_SCALE_OHM           200000.0
#define STEPDOWN13_WIPER_POS_MAX            255
#define STEPDOWN13_ACTUAL_FULL_SCALE_PCT    0.95
#define STEPDOWN13_FLOAT_COMPARE_OFFSET     0.001
#define STEPDOWN13_VOUT_MIN                 1.2
#define STEPDOWN13_VOUT_MAX                 5.5

/**
 * @brief Step Down 13 device address setting.
 * @details Specified setting for device slave address selection of
 * Step Down 13 Click driver.
 */
#define STEPDOWN13_DEVICE_ADDRESS_0         0x28
#define STEPDOWN13_DEVICE_ADDRESS_1         0x29

/*! @} */ // stepdown13_set

/**
 * @defgroup stepdown13_map Step Down 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 13 Click driver.
 */

/**
 * @addtogroup stepdown13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 13 Click to the selected MikroBUS.
 */
#define STEPDOWN13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.mode = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // stepdown13_map
/*! @} */ // stepdown13

/**
 * @brief Step Down 13 Click context object.
 * @details Context object definition of Step Down 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mode;         /**< Mode selection pin. */
    digital_out_t en;           /**< Enable output pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepdown13_t;

/**
 * @brief Step Down 13 Click configuration object.
 * @details Configuration object definition of Step Down 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t mode;            /**< Mode selection pin. */
    pin_name_t en;              /**< Enable output pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepdown13_cfg_t;

/**
 * @brief Step Down 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN13_OK = 0,
    STEPDOWN13_ERROR = -1

} stepdown13_return_value_t;

/*!
 * @addtogroup stepdown13 Step Down 13 Click Driver
 * @brief API for configuring and manipulating Step Down 13 Click driver.
 * @{
 */

/**
 * @brief Step Down 13 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown13_cfg_setup ( stepdown13_cfg_t *cfg );

/**
 * @brief Step Down 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown13_init ( stepdown13_t *ctx, stepdown13_cfg_t *cfg );

/**
 * @brief Step Down 13 set VREG register function.
 * @details This function sets the volatile output voltage control register (VREG)
 * with the provided raw data value.
 * @param[in] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @param[in] data_in : VREG register raw data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown13_set_vreg ( stepdown13_t *ctx, uint8_t data_in );

/**
 * @brief Step Down 13 set NVREG register function.
 * @details This function sets the non-volatile output voltage control register (NVREG)
 * with the provided raw data value.
 * @param[in] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @param[in] data_in : NVREG register raw data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown13_set_nvreg ( stepdown13_t *ctx, uint8_t data_in );

/**
 * @brief Step Down 13 move VREG to NVREG function.
 * @details This function copies the current volatile output voltage setting from
 * the VREG register to the non-volatile NVREG register.
 * @param[in] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown13_move_vreg_to_nvreg ( stepdown13_t *ctx );

/**
 * @brief Step Down 13 move NVREG to VREG function.
 * @details This function copies the stored non-volatile output voltage setting from
 * the NVREG register to the volatile VREG register.
 * @param[in] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown13_move_nvreg_to_vreg ( stepdown13_t *ctx );

/**
 * @brief Step Down 13 enable output function.
 * @details This function enables the device output by setting the EN pin to a
 * logic high state and waits for a short stabilization delay.
 * @param[in] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown13_enable_output ( stepdown13_t *ctx );

/**
 * @brief Step Down 13 disable output function.
 * @details This function disables the device output by setting the EN pin to a
 * logic low state and waits for a short stabilization delay.
 * @param[in] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown13_disable_output ( stepdown13_t *ctx );

/**
 * @brief Step Down 13 set COT mode function.
 * @details This function selects the constant on-time (COT) operating mode by
 * setting the MODE pin to a logic high state and waits for a short delay.
 * @param[in] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown13_set_cot_mode ( stepdown13_t *ctx );

/**
 * @brief Step Down 13 set PFM mode function.
 * @details This function selects the pulse-frequency modulation (PFM) operating
 * mode by setting the MODE pin to a logic low state and waits for a short delay.
 * @param[in] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown13_set_pfm_mode ( stepdown13_t *ctx );

/**
 * @brief Step Down 13 set output voltage function.
 * @details This function calculates the required wiper position of the internal
 * digital potentiometer based on the desired output voltage and programs the
 * VREG control register accordingly.
 * @param[in] ctx : Click context object.
 * See #stepdown13_t object definition for detailed explanation.
 * @param[in] vout : Desired output voltage value in volts.
 * See STEPDOWN13_VOUT_MIN and STEPDOWN13_VOUT_MAX for allowed range.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Measure the actual voltage outputs and adjust STEPDOWN13_ACTUAL_FULL_SCALE_PCT
 * accordingly for better accuracy.
 */
err_t stepdown13_set_vout ( stepdown13_t *ctx, float vout );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN13_H

/*! @} */ // stepdown13

// ------------------------------------------------------------------------ END
