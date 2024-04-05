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
 * @file buck22.h
 * @brief This file contains API for Buck 22 Click Driver.
 */

#ifndef BUCK22_H
#define BUCK22_H

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
 * @addtogroup buck22 Buck 22 Click Driver
 * @brief API for configuring and manipulating Buck 22 Click driver.
 * @{
 */

/**
 * @defgroup buck22_reg Buck 22 Registers List
 * @brief List of registers of Buck 22 Click driver.
 */

/**
 * @addtogroup buck22_reg
 * @{
 */

/**
 * @brief Buck 22 register list.
 * @details Specified register list of Buck 22 Click driver.
 */
#define BUCK22_REG_VOUT                     0x01
#define BUCK22_REG_CONTROL                  0x03
#define BUCK22_REG_STATUS                   0x05

/*! @} */ // buck22_reg

/**
 * @defgroup buck22_set Buck 22 Registers Settings
 * @brief Settings for registers of Buck 22 Click driver.
 */

/**
 * @addtogroup buck22_set
 * @{
 */

/**
 * @brief Buck 22 VOUT setting.
 * @details Specified setting for VOUT of Buck 22 Click driver.
 */
#define BUCK22_VOUT_MIN                     800
#define BUCK22_VOUT_MAX                     3350
#define BUCK22_VOLTAGE_FACTOR               2
#define BUCK22_VOUT_RESOLUTION              ( 5 * BUCK22_VOLTAGE_FACTOR )

/**
 * @brief Buck 22 CONTROL setting.
 * @details Specified setting for CONTROL of Buck 22 Click driver.
 */
#define BUCK22_CONTROL_RESET                0x80
#define BUCK22_CONTROL_FPWM_VOUT_CHANGE     0x40
#define BUCK22_CONTROL_SOFT_EN              0x20
#define BUCK22_CONTROL_FPWM_EN              0x10
#define BUCK22_CONTROL_DISCHARGE_EN         0x08
#define BUCK22_CONTROL_HICCUP_EN            0x04
#define BUCK22_CONTROL_VRAMP_SPEED_20       0x00
#define BUCK22_CONTROL_VRAMP_SPEED_10       0x01
#define BUCK22_CONTROL_VRAMP_SPEED_5        0x02
#define BUCK22_CONTROL_VRAMP_SPEED_1        0x03
#define BUCK22_CONTROL_VRAMP_SPEED_MASK     0x03
#define BUCK22_CONTROL_DEFAULT_SETTING      ( BUCK22_CONTROL_FPWM_VOUT_CHANGE | \
                                              BUCK22_CONTROL_SOFT_EN | \
                                              BUCK22_CONTROL_DISCHARGE_EN | \
                                              BUCK22_CONTROL_HICCUP_EN | \
                                              BUCK22_CONTROL_VRAMP_SPEED_1 )

/**
 * @brief Buck 22 STATUS setting.
 * @details Specified setting for STATUS of Buck 22 Click driver.
 */
#define BUCK22_STATUS_THERMAL_WARNING       0x10
#define BUCK22_STATUS_HICCUP                0x08
#define BUCK22_STATUS_UVLO                  0x01

/**
 * @brief Buck 22 device address setting.
 * @details Specified setting for device slave address selection of
 * Buck 22 Click driver.
 */
#define BUCK22_DEVICE_ADDRESS               0x42

/*! @} */ // buck22_set

/**
 * @defgroup buck22_map Buck 22 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck 22 Click driver.
 */

/**
 * @addtogroup buck22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck 22 Click to the selected MikroBUS.
 */
#define BUCK22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buck22_map
/*! @} */ // buck22

/**
 * @brief Buck 22 Click context object.
 * @details Context object definition of Buck 22 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t pg;                /**< Power-good pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} buck22_t;

/**
 * @brief Buck 22 Click configuration object.
 * @details Configuration object definition of Buck 22 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t pg;                  /**< Power-good pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} buck22_cfg_t;

/**
 * @brief Buck 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCK22_OK = 0,
    BUCK22_ERROR = -1

} buck22_return_value_t;

/*!
 * @addtogroup buck22 Buck 22 Click Driver
 * @brief API for configuring and manipulating Buck 22 Click driver.
 * @{
 */

/**
 * @brief Buck 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buck22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buck22_cfg_setup ( buck22_cfg_t *cfg );

/**
 * @brief Buck 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buck22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buck22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck22_init ( buck22_t *ctx, buck22_cfg_t *cfg );

/**
 * @brief Buck 22 set vout function.
 * @details This function sets the output voltage by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck22_t object definition for detailed explanation.
 * @param[in] vout_mv : Voltage output in millivolts (800-3350mV).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck22_set_vout ( buck22_t *ctx, uint16_t vout_mv );

/**
 * @brief Buck 22 read vout function.
 * @details This function reads the output voltage by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck22_t object definition for detailed explanation.
 * @param[out] vout_mv : Voltage output in millivolts (800-3350mV).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck22_read_vout ( buck22_t *ctx, uint16_t *vout_mv );

/**
 * @brief Buck 22 set control function.
 * @details This function sets the control register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck22_t object definition for detailed explanation.
 * @param[in] control : Control register setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck22_set_control ( buck22_t *ctx, uint8_t control );

/**
 * @brief Buck 22 read status function.
 * @details This function reads the status register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck22_t object definition for detailed explanation.
 * @param[out] status : Status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck22_read_status ( buck22_t *ctx, uint8_t *status );

/**
 * @brief Buck 22 get pg pin function.
 * @details This function returns the power good (PG) pin logic state.
 * @param[in] ctx : Click context object.
 * See #buck22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t buck22_get_pg_pin ( buck22_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUCK22_H

/*! @} */ // buck22

// ------------------------------------------------------------------------ END
