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
 * @file stepdown14.h
 * @brief This file contains API for Step Down 14 Click Driver.
 */

#ifndef STEPDOWN14_H
#define STEPDOWN14_H

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
 * @addtogroup stepdown14 Step Down 14 Click Driver
 * @brief API for configuring and manipulating Step Down 14 Click driver.
 * @{
 */

/**
 * @defgroup stepdown14_reg Step Down 14 Registers List
 * @brief List of registers of Step Down 14 Click driver.
 */

/**
 * @addtogroup stepdown14_reg
 * @{
 */

/**
 * @brief Step Down 14 control registers.
 * @details Specified registers for control of Step Down 14 Click driver.
 */
#define STEPDOWN14_CONTROL_VREG             0x11
#define STEPDOWN14_CONTROL_NVREG            0x21
#define STEPDOWN14_CONTROL_NVREG_X_VREG     0x61
#define STEPDOWN14_CONTROL_VREG_X_NVREG     0x51

/*! @} */ // stepdown14_reg

/**
 * @defgroup stepdown14_set Step Down 14 Registers Settings
 * @brief Settings for registers of Step Down 14 Click driver.
 */

/**
 * @addtogroup stepdown14_set
 * @{
 */

/**
 * @brief Step Down 14 output calculation setting.
 * @details Specified setting for output calculation of Step Down 14 Click driver.
 */
#define STEPDOWN14_R7_OHM                   100000.0
#define STEPDOWN14_R10_OHM                  2400.0
#define STEPDOWN14_WIPER_RES_OHM            325.0
#define STEPDOWN14_FB_VOLTAGE               0.8
#define STEPDOWN14_FULL_SCALE_OHM           200000.0
#define STEPDOWN14_WIPER_POS_MIN            0
#define STEPDOWN14_WIPER_POS_MAX            255
#define STEPDOWN14_FLOAT_COMPARE_OFFSET     0.001
#define STEPDOWN14_VOUT_MIN                 1.2
#define STEPDOWN14_VOUT_MAX                 30.0

/**
 * @brief Step Down 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Step Down 14 Click driver.
 */
#define STEPDOWN14_DEVICE_ADDRESS_0         0x28
#define STEPDOWN14_DEVICE_ADDRESS_1         0x29

/*! @} */ // stepdown14_set

/**
 * @defgroup stepdown14_map Step Down 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 14 Click driver.
 */

/**
 * @addtogroup stepdown14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 14 Click to the selected MikroBUS.
 */
#define STEPDOWN14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepdown14_map
/*! @} */ // stepdown14

/**
 * @brief Step Down 14 Click context object.
 * @details Context object definition of Step Down 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;       /**< Power enable pin (active high). */

    // Input pins
    digital_in_t pg;        /**< Power good pin (active low). */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} stepdown14_t;

/**
 * @brief Step Down 14 Click configuration object.
 * @details Configuration object definition of Step Down 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;          /**< Power enable pin (active high). */
    pin_name_t pg;          /**< Power good pin (active low). */

    uint32_t   i2c_speed;   /**< I2C serial speed. */
    uint8_t    i2c_address; /**< I2C slave address. */

} stepdown14_cfg_t;

/**
 * @brief Step Down 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN14_OK = 0,
    STEPDOWN14_ERROR = -1

} stepdown14_return_value_t;

/*!
 * @addtogroup stepdown14 Step Down 14 Click Driver
 * @brief API for configuring and manipulating Step Down 14 Click driver.
 * @{
 */

/**
 * @brief Step Down 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown14_cfg_setup ( stepdown14_cfg_t *cfg );

/**
 * @brief Step Down 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepdown14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown14_init ( stepdown14_t *ctx, stepdown14_cfg_t *cfg );

/**
 * @brief Step Down 14 set VREG register function.
 * @details This function sets the volatile output voltage control register (VREG)
 * with the provided raw data value.
 * @param[in] ctx : Click context object.
 * See #stepdown14_t object definition for detailed explanation.
 * @param[in] data_in : VREG register raw data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown14_set_vreg ( stepdown14_t *ctx, uint8_t data_in );

/**
 * @brief Step Down 14 set NVREG register function.
 * @details This function sets the non-volatile output voltage control register (NVREG)
 * with the provided raw data value.
 * @param[in] ctx : Click context object.
 * See #stepdown14_t object definition for detailed explanation.
 * @param[in] data_in : NVREG register raw data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown14_set_nvreg ( stepdown14_t *ctx, uint8_t data_in );

/**
 * @brief Step Down 14 move VREG to NVREG function.
 * @details This function copies the current volatile output voltage setting from
 * the VREG register to the non-volatile NVREG register.
 * @param[in] ctx : Click context object.
 * See #stepdown14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown14_move_vreg_to_nvreg ( stepdown14_t *ctx );

/**
 * @brief Step Down 14 move NVREG to VREG function.
 * @details This function copies the stored non-volatile output voltage setting from
 * the NVREG register to the volatile VREG register.
 * @param[in] ctx : Click context object.
 * See #stepdown14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown14_move_nvreg_to_vreg ( stepdown14_t *ctx );

/**
 * @brief Step Down 14 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown14_enable_device ( stepdown14_t *ctx );

/**
 * @brief Step Down 14 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown14_disable_device ( stepdown14_t *ctx );

/**
 * @brief Step Down 14 get PG pin function.
 * @details This function returns the PG pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepdown14_get_pg_pin ( stepdown14_t *ctx );

/**
 * @brief Step Down 14 set output voltage function.
 * @details This function calculates and sets the wiper value for the target output voltage.
 * @param[in] ctx : Click context object.
 * See #stepdown14_t object definition for detailed explanation.
 * @param[in] target_vout : Target output voltage value.
 * @param[out] set_vout : Pointer to the memory location where the set output voltage will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown14_set_vout ( stepdown14_t *ctx, float target_vout, float *set_vout );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN14_H

/*! @} */ // stepdown14

// ------------------------------------------------------------------------ END
