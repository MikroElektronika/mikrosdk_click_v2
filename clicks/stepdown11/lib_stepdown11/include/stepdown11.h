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
 * @file stepdown11.h
 * @brief This file contains API for Step Down 11 Click Driver.
 */

#ifndef STEPDOWN11_H
#define STEPDOWN11_H

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
 * @addtogroup stepdown11 Step Down 11 Click Driver
 * @brief API for configuring and manipulating Step Down 11 Click driver.
 * @{
 */

/**
 * @defgroup stepdown11_reg Step Down 11 Registers List
 * @brief List of registers of Step Down 11 Click driver.
 */

/**
 * @addtogroup stepdown11_reg
 * @{
 */

/**
 * @brief Step Down 11 description register.
 * @details Specified register for description of Step Down 11 Click driver.
 */
#define STEPDOWN11_ADDR_BIT_READ_INPUT_REG              0x00
#define STEPDOWN11_ADDR_BIT_READ_EEPROM                 0x01
#define STEPDOWN11_ADDR_BIT_READ_CTRL_REG               0x02
#define STEPDOWN11_ADDR_BIT_READ_RDAC                   0x03
#define STEPDOWN11_ADDR_BIT_RDAC_DECR                   0x00
#define STEPDOWN11_ADDR_BIT_RDAC_INCR                   0x01
#define STEPDOWN11_ADDR_BIT_COPY_TO_RDAC                0x00
#define STEPDOWN11_ADDR_BIT_COPY_TO_EEPROM              0x01
#define STEPDOWN11_ADDR_BIT_SCALE_MODE_NORMAL           0x80
#define STEPDOWN11_ADDR_BIT_SCALE_MODE_SHDN             0x81
#define STEPDOWN11_ADDR_BIT_SCALE_EXIT                  0x00
#define STEPDOWN11_ADDR_BIT_SCALE_ENTER                 0x01
#define STEPDOWN11_ADDR_BIT_SW_SHDN_MODE_NORMAL         0x00
#define STEPDOWN11_ADDR_BIT_SW_SHDN_MODE_SHDN           0x01

/*! @} */ // stepdown11_reg

/**
 * @defgroup stepdown11_set Step Down 11 Registers Settings
 * @brief Settings for registers of Step Down 11 Click driver.
 */

/**
 * @addtogroup stepdown11_set
 * @{
 */

/**
 * @brief Step Down 11 description setting.
 * @details Specified setting for description of Step Down 11 Click driver.
 */
#define STEPDOWN11_CTRL_BIT_NOP                         0x00
#define STEPDOWN11_CTRL_BIT_WRITE_RDAC                  0x10
#define STEPDOWN11_CTRL_BIT_WRITE_SHIFT_REG             0x20
#define STEPDOWN11_CTRL_BIT_READ                        0x30
#define STEPDOWN11_CTRL_BIT_LIN_RDAC                    0x40
#define STEPDOWN11_CTRL_BIT_6_DB_RDAC                   0x50
#define STEPDOWN11_CTRL_BIT_COPY_LRDAC                  0x60
#define STEPDOWN11_CTRL_BIT_COPY_RDAC_EEPROM            0x70
#define STEPDOWN11_CTRL_BIT_WRITE_EEPROM                0x80
#define STEPDOWN11_CTRL_BIT_SCALE                       0x90
#define STEPDOWN11_CTRL_BIT_SW_RST                      0xB0
#define STEPDOWN11_CTRL_BIT_SW_SHDN                     0xC0
#define STEPDOWN11_CTRL_BIT_REG_CTRL                    0xD0
#define STEPDOWN11_CTRL_BIT_MASK                        0xF0

/**
 * @brief Step Down 11 description of the wiper selection.
 * @details Specified setting for wiper selection of Step Down 11 Click driver.
 */
#define STEPDOWN11_WIPER_SEL_1                          0x00
#define STEPDOWN11_WIPER_SEL_2                          0x01
#define STEPDOWN11_WIPER_SEL_BOTH                       0x08

/**
 * @brief Step Down 11 S-CONF Device Configuration Modes.
 * @details Specified setting for S-CONF Device Configuration Modes of Step Down 11 Click driver.
 */
#define STEPDOWN11_S_CONF_1MHZ_SPREAD_OFF               0
#define STEPDOWN11_S_CONF_2_2MHZ_SPREAD_OFF             4870
#define STEPDOWN11_S_CONF_2_2MHZ_SPREAD_TRIANGLE        6040
#define STEPDOWN11_S_CONF_2_2MHZ_SPREAD_RANDOM          7500

/**
 * @brief Step Down 11 wiper and resistance data values.
 * @details Specified wiper and resistance data values of Step Down 11 Click driver.
 */
#define STEPDOWN11_WIPER_POS_MAX                        255
#define STEPDOWN11_WIPER_POS_MIN                        0
#define STEPDOWN11_WIPER_POS_MIDDLE                     127
#define STEPDOWN11_RES_10_KOHM                          10000
#define STEPDOWN11_RES_0_KOHM                           0
#define STEPDOWN11_R_5_RESISTANCE                       2700
#define STEPDOWN11_R_9_RESISTANCE                       10
#define STEPDOWN11_VFB_VALUE                            0.8f

/**
 * @brief Step Down 11 pin states setting.
 * @details Specified setting for pin states of Step Down 11 Click driver.
 */
#define STEPDOWN11_ENABLE_OUTPUT                        0x01
#define STEPDOWN11_DISABLE_OUTPUT                       0x00

/**
 * @brief Step Down 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Step Down 11 Click driver.
 */
#define STEPDOWN11_DEVICE_ADDRESS_0                     0x2F
#define STEPDOWN11_DEVICE_ADDRESS_1                     0x2C
#define STEPDOWN11_DEVICE_ADDRESS_2                     0x23
#define STEPDOWN11_DEVICE_ADDRESS_3                     0x20

/*! @} */ // stepdown11_set

/**
 * @defgroup stepdown11_map Step Down 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 11 Click driver.
 */

/**
 * @addtogroup stepdown11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 11 Click to the selected MikroBUS.
 */
#define STEPDOWN11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepdown11_map
/*! @} */ // stepdown11

/**
 * @brief Step Down 11 Click context object.
 * @details Context object definition of Step Down 11 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */
    digital_out_t en;           /**< Enable output pin. */

    // Input pins
    digital_in_t pg;            /**< Power-good pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepdown11_t;

/**
 * @brief Step Down 11 Click configuration object.
 * @details Configuration object definition of Step Down 11 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t en;              /**< Enable output pin. */
    pin_name_t pg;              /**< Power-good pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepdown11_cfg_t;

/**
 * @brief Step Down 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN11_OK = 0,
    STEPDOWN11_ERROR = -1

} stepdown11_return_value_t;

/*!
 * @addtogroup stepdown11 Step Down 11 Click Driver
 * @brief API for configuring and manipulating Step Down 11 Click driver.
 * @{
 */

/**
 * @brief Step Down 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown11_cfg_setup ( stepdown11_cfg_t *cfg );

/**
 * @brief Step Down 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_init ( stepdown11_t *ctx, stepdown11_cfg_t *cfg );

/**
 * @brief Step Down 11 default configuration function.
 * @details This function executes a default configuration of Step Down 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepdown11_default_cfg ( stepdown11_t *ctx );

/**
 * @brief Step Down 11 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_generic_write ( stepdown11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Step Down 11 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_generic_read ( stepdown11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Step Down 11 set EN pin state function.
 * @details This function is used to set EN pin state.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] pin_state : EN pin state.
 * @return Nothing.
 * @note None.
 */
void stepdown11_set_en_pin ( stepdown11_t *ctx, uint8_t pin_state );

/**
 * @brief Step Down 11 get PG pin state function.
 * @details This function is used to reset digi pot.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @return PG pin state.
 * @note None.
 */
uint8_t stepdown11_get_pg_pin ( stepdown11_t *ctx );

/**
 * @brief Step Down 11 reset digi pot function.
 * @details This function is used to reset digi pot.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void stepdown11_reset_digi_pot ( stepdown11_t *ctx );

/**
 * @brief Step Down 11 I2C writing function.
 * @details This function writes a byte of data for 
 * the selected command and address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] ctrl : Control bits - commands operation.
 * @param[in] addr : Address bits - wiper selection.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_write_data ( stepdown11_t *ctx, uint8_t ctrl, uint8_t addr, uint8_t data_in );

/**
 * @brief Step Down 11 I2C reading function.
 * @details This function reads a byte of data from
 * the selected address and data bits mask by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] addr : Address bits - wiper selection.
 * @param[in] mask : Data bits mask.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_read_data ( stepdown11_t *ctx, uint8_t addr, uint8_t mask, uint8_t *data_out );

/**
 * @brief Step Down 11 write the RDAC function.
 * @details This function writes RDAC data value
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the Step Down 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] addr : Address bits - wiper selection.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_write_rdac ( stepdown11_t *ctx, uint8_t addr, uint8_t data_in );

/**
 * @brief Step Down 11 read the RDAC function.
 * @details This function reads the RDAC data value
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the Step Down 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] addr : Address bits - wiper selection.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_read_rdac ( stepdown11_t *ctx, uint8_t addr, uint8_t *data_out );

/**
 * @brief Step Down 11 set the resistance function.
 * @details This function sets the resistance of the selected wiper 
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the Step Down 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] wiper_sel : Wiper selection.
 * @param[in] res_kohm : Rwb1/2 (wiper-to-B) resistance from 0.0 to 10.0 [kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_set_resistance ( stepdown11_t *ctx, uint8_t wiper_sel, float res_kohm );

/**
 * @brief Step Down 11 get the resistance function.
 * @details This function gets the resistance of the selected wiper 
 * of the AD5142A, Dual Channel, 256-Position, I2C, 
 * Nonvolatile Digital Potentiometer on the Step Down 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] wiper_sel : Wiper selection.
 * @param[out] res_kohm : Rwb1/2 (wiper-to-B) resistance from 0.0 to 10.0 [kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_get_resistance ( stepdown11_t *ctx, uint8_t wiper_sel, float *res_kohm );

/**
 * @brief Step Down 11 set voltage output function.
 * @details This function is used to set voltage output.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] v_out : Output voltage in volts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_set_voltage ( stepdown11_t *ctx, float v_out );

/**
 * @brief Step Down 11 set S-CONF device configuration mode function.
 * @details This function is used to set S-CONF device configuration mode.
 * @param[in] ctx : Click context object.
 * See #stepdown11_t object definition for detailed explanation.
 * @param[in] v_out : Output voltage in volts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown11_set_mode ( stepdown11_t *ctx, float sconf_mode );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN11_H

/*! @} */ // stepdown11

// ------------------------------------------------------------------------ END
