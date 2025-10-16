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
 * @file smartbuck8.h
 * @brief This file contains API for Smart Buck 8 Click Driver.
 */

#ifndef SMARTBUCK8_H
#define SMARTBUCK8_H

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
 * @addtogroup smartbuck8 Smart Buck 8 Click Driver
 * @brief API for configuring and manipulating Smart Buck 8 Click driver.
 * @{
 */

/**
 * @defgroup smartbuck8_reg Smart Buck 8 Registers List
 * @brief List of registers of Smart Buck 8 Click driver.
 */

/**
 * @addtogroup smartbuck8_reg
 * @{
 */

/**
 * @brief Smart Buck 8 register map.
 * @details Specified register map of Smart Buck 8 Click driver.
 */
#define SMARTBUCK8_REG_VOUT                     0x01
#define SMARTBUCK8_REG_CONTROL                  0x03
#define SMARTBUCK8_REG_STATUS                   0x05

/*! @} */ // smartbuck8_reg

/**
 * @defgroup smartbuck8_set Smart Buck 8 Registers Settings
 * @brief Settings for registers of Smart Buck 8 Click driver.
 */

/**
 * @addtogroup smartbuck8_set
 * @{
 */

/**
 * @brief Smart Buck 8 CONTROL register setting.
 * @details Specified setting for CONTROL register of Smart Buck 8 Click driver.
 */
#define SMARTBUCK8_CONTROL_RESET                0x80
#define SMARTBUCK8_CONTROL_EN_FPWM_ON_CHANGE    0x40
#define SMARTBUCK8_CONTROL_SOFT_EN              0x20
#define SMARTBUCK8_CONTROL_EN_FPWM              0x10
#define SMARTBUCK8_CONTROL_EN_OUT_DISCHARGE     0x08
#define SMARTBUCK8_CONTROL_EN_HICCUP            0x04
#define SMARTBUCK8_CONTROL_V_RAMP_SPEED_0_25US  0x00
#define SMARTBUCK8_CONTROL_V_RAMP_SPEED_0_5US   0x01
#define SMARTBUCK8_CONTROL_V_RAMP_SPEED_1US     0x02
#define SMARTBUCK8_CONTROL_V_RAMP_SPEED_5US     0x03
#define SMARTBUCK8_CONTROL_V_RAMP_SPEED_MASK    0x03

/**
 * @brief Smart Buck 8 STATUS register setting.
 * @details Specified setting for STATUS register of Smart Buck 8 Click driver.
 */
#define SMARTBUCK8_STATUS_THERMAL_WARNING       0x10
#define SMARTBUCK8_STATUS_HICCUP                0x08
#define SMARTBUCK8_STATUS_UVLO                  0x01

/**
 * @brief Smart Buck 8 vout setting.
 * @details Specified setting for vout of Smart Buck 8 Click driver.
 */
#define SMARTBUCK8_VOUT_MV_MIN                  400
#define SMARTBUCK8_VOUT_MV_MAX                  1675
#define SMARTBUCK8_VOUT_MV_STEP_5MV             5

/**
 * @brief Smart Buck 8 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart Buck 8 Click driver.
 */
#define SMARTBUCK8_DEVICE_ADDRESS               0x42

/*! @} */ // smartbuck8_set

/**
 * @defgroup smartbuck8_map Smart Buck 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Buck 8 Click driver.
 */

/**
 * @addtogroup smartbuck8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Buck 8 Click to the selected MikroBUS.
 */
#define SMARTBUCK8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pon = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartbuck8_map
/*! @} */ // smartbuck8

/**
 * @brief Smart Buck 8 Click context object.
 * @details Context object definition of Smart Buck 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pon;          /**< Internal power enable pin (active high). */
    digital_out_t en;           /**< Enable pin (active high). */

    // Input pins
    digital_in_t pg;            /**< Power-good signal pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} smartbuck8_t;

/**
 * @brief Smart Buck 8 Click configuration object.
 * @details Configuration object definition of Smart Buck 8 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t pon;             /**< Internal power enable pin (active high). */
    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t pg;              /**< Power-good signal pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} smartbuck8_cfg_t;

/**
 * @brief Smart Buck 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTBUCK8_OK = 0,
    SMARTBUCK8_ERROR = -1

} smartbuck8_return_value_t;

/*!
 * @addtogroup smartbuck8 Smart Buck 8 Click Driver
 * @brief API for configuring and manipulating Smart Buck 8 Click driver.
 * @{
 */

/**
 * @brief Smart Buck 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartbuck8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartbuck8_cfg_setup ( smartbuck8_cfg_t *cfg );

/**
 * @brief Smart Buck 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartbuck8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck8_init ( smartbuck8_t *ctx, smartbuck8_cfg_t *cfg );

/**
 * @brief Smart Buck 8 default configuration function.
 * @details This function executes a default configuration of Smart Buck 8
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartbuck8_default_cfg ( smartbuck8_t *ctx );

/**
 * @brief Smart Buck 8 write register function.
 * @details This function writes a single byte to one of the writable Smart Buck 8 registers.
 * Allowed registers are VOUT and CONTROL.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck8_write_reg ( smartbuck8_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Smart Buck 8 read register function.
 * @details This function reads a single byte from one of the readable Smart Buck 8 registers.
 * Allowed registers are VOUT, CONTROL, and STATUS.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck8_read_reg ( smartbuck8_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Smart Buck 8 enable power function.
 * @details This function sets the PON pin to high logic level to enable the internal power supply.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck8_enable_power ( smartbuck8_t *ctx );

/**
 * @brief Smart Buck 8 disable power function.
 * @details This function sets the PON pin to low logic level to disable the internal power supply.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck8_disable_power ( smartbuck8_t *ctx );

/**
 * @brief Smart Buck 8 enable device function.
 * @details This function sets the EN pin to high logic level to enable the device.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck8_enable_device ( smartbuck8_t *ctx );

/**
 * @brief Smart Buck 8 disable device function.
 * @details This function sets the EN pin to low logic level to disable the device.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck8_disable_device ( smartbuck8_t *ctx );

/**
 * @brief Smart Buck 8 get power-good pin function.
 * @details This function reads the logic level of the PG (power-good) pin.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @return PG pin logic state.
 * @note None.
 */
uint8_t smartbuck8_get_pg_pin ( smartbuck8_t *ctx );

/**
 * @brief Smart Buck 8 read status register function.
 * @details This function reads the value of the STATUS register and returns it via output pointer.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @param[out] status : Pointer to memory where status register value will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck8_read_status ( smartbuck8_t *ctx, uint8_t *status );

/**
 * @brief Smart Buck 8 set control register function.
 * @details This function writes a control byte to the CONTROL register.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @param[in] control : Control register byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck8_set_control ( smartbuck8_t *ctx, uint8_t control );

/**
 * @brief Smart Buck 8 set output voltage function.
 * @details This function sets the output voltage by writing a scaled value to the VOUT register.
 * Voltage range is [SMARTBUCK8_VOUT_MV_MIN, SMARTBUCK8_VOUT_MV_MAX] in steps of 5 mV.
 * @param[in] ctx : Click context object.
 * See #smartbuck8_t object definition for detailed explanation.
 * @param[in] vout_mv : Desired output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck8_set_vout ( smartbuck8_t *ctx, uint16_t vout_mv );

#ifdef __cplusplus
}
#endif
#endif // SMARTBUCK8_H

/*! @} */ // smartbuck8

// ------------------------------------------------------------------------ END
