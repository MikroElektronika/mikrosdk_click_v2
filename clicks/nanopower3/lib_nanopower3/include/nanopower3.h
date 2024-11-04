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
 * @file nanopower3.h
 * @brief This file contains API for Nano Power 3 Click Driver.
 */

#ifndef NANOPOWER3_H
#define NANOPOWER3_H

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
 * @addtogroup nanopower3 Nano Power 3 Click Driver
 * @brief API for configuring and manipulating Nano Power 3 Click driver.
 * @{
 */

/**
 * @defgroup nanopower3_set Nano Power 3 Registers Settings
 * @brief Settings for registers of Nano Power 3 Click driver.
 */

/**
 * @addtogroup nanopower3_set
 * @{
 */

/**
 * @brief Nano Power 3 description setting.
 * @details Specified setting for description of Nano Power 3 Click driver.
 */
#define NANOPOWER3_CMD_VREG                             0x11
#define NANOPOWER3_CMD_NVREG                            0x21
#define NANOPOWER3_CMD_VREGxNVREG                       0x51
#define NANOPOWER3_CMD_NVREGxVREG                       0x61

/**
 * @brief Nano Power 3 output voltage selection setting.
 * @details Specified setting for output voltage selection of Nano Power 3 Click driver.
 */
#define NANOPOWER3_1V_OUT_VOLTAGE                       0x00
#define NANOPOWER3_1V2_OUT_VOLTAGE                      0x01
#define NANOPOWER3_1V5_OUT_VOLTAGE                      0x02
#define NANOPOWER3_1V8_OUT_VOLTAGE                      0x03
#define NANOPOWER3_2V_OUT_VOLTAGE                       0x04
#define NANOPOWER3_2V5_OUT_VOLTAGE                      0x05
#define NANOPOWER3_3V_OUT_VOLTAGE                       0x06
#define NANOPOWER3_3V3_OUT_VOLTAGE                      0x07
#define NANOPOWER3_3V5_OUT_VOLTAGE                      0x08
#define NANOPOWER3_4V_OUT_VOLTAGE                       0x09
#define NANOPOWER3_4V5_OUT_VOLTAGE                      0x0A

/**
 * @brief Nano Power 3 output voltage resistance setting.
 * @details Specified setting for output voltage resistance of Nano Power 3 Click driver.
 */
#define NANOPOWER3_1V_RESISTANCE                        187000
#define NANOPOWER3_1V2_RESISTANCE                       93100
#define NANOPOWER3_1V5_RESISTANCE                       53600
#define NANOPOWER3_1V8_RESISTANCE                       37400
#define NANOPOWER3_2V_RESISTANCE                        29000
#define NANOPOWER3_2V5_RESISTANCE                       20000
#define NANOPOWER3_3V_RESISTANCE                        15000
#define NANOPOWER3_3V3_RESISTANCE                       13100
#define NANOPOWER3_3V5_RESISTANCE                       12200
#define NANOPOWER3_4V_RESISTANCE                        10000
#define NANOPOWER3_4V5_RESISTANCE                       9000

/**
 * @brief Nano Power 3 calculation setting.
 * @details Specified setting for calculation of Nano Power 3 Click driver.
 */
#define NANOPOWER3_R11_RESISTANCE                       7200
#define NANOPOWER3_DIGIPOT_MAX_RESISTANCE               200000
#define NANOPOWER3_DIGIPOT_MAX_VAL                      255
#define NANOPOWER3_MAX_RESISTANCE                       207200
#define NANOPOWER3_ROUND_TO_NEAREST_INT                 0.5

/**
 * @brief Nano Power 3 pin state setting.
 * @details Specified setting for pin state of Nano Power 3 Click driver.
 */
#define NANOPOWER3_PIN_STATE_HIGH                       0x01
#define NANOPOWER3_PIN_STATE_LOW                        0x00

/**
 * @brief Nano Power 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Nano Power 3 Click driver.
 */
#define NANOPOWER3_DEVICE_ADDRESS_GND                   0x28
#define NANOPOWER3_DEVICE_ADDRESS_VCC                   0x29

/*! @} */ // nanopower3_set

/**
 * @defgroup nanopower3_map Nano Power 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Nano Power 3 Click driver.
 */

/**
 * @addtogroup nanopower3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Nano Power 3 Click to the selected MikroBUS.
 */
#define NANOPOWER3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ctr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nanopower3_map
/*! @} */ // nanopower3

/**
 * @brief Nano Power 3 Click context object.
 * @details Context object definition of Nano Power 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ctr;          /**< CTRL pin. */

    // Input pins
    digital_in_t an;            /**< LDO regulator output. */
    digital_in_t pg;            /**< Power good output. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} nanopower3_t;

/**
 * @brief Nano Power 3 Click configuration object.
 * @details Configuration object definition of Nano Power 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t an;              /**< LDO regulator output. */
    pin_name_t ctr;             /**< CTRL pin. */
    pin_name_t pg;              /**< Power good output. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} nanopower3_cfg_t;

/**
 * @brief Nano Power 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NANOPOWER3_OK = 0,
    NANOPOWER3_ERROR = -1

} nanopower3_return_value_t;

/*!
 * @addtogroup nanopower3 Nano Power 3 Click Driver
 * @brief API for configuring and manipulating Nano Power 3 Click driver.
 * @{
 */

/**
 * @brief Nano Power 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nanopower3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nanopower3_cfg_setup ( nanopower3_cfg_t *cfg );

/**
 * @brief Nano Power 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nanopower3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanopower3_init ( nanopower3_t *ctx, nanopower3_cfg_t *cfg );

/**
 * @brief Nano Power 3 default configuration function.
 * @details This function executes a default configuration of Nano Power 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nanopower3_default_cfg ( nanopower3_t *ctx );

/**
 * @brief Nano Power 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanopower3_generic_write ( nanopower3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Nano Power 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanopower3_generic_read ( nanopower3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Nano Power 3 get PG pin state function.
 * @details This function is used to get state of the PG pin.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t nanopower3_get_pg_pin_state ( nanopower3_t *ctx );

/**
 * @brief Nano Power 3 get AN pin state function.
 * @details This function is used to get state of the AN pin.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t nanopower3_get_an_pin_state ( nanopower3_t *ctx );

/**
 * @brief Nano Power 3 set CTRL pin state function.
 * @details This function is used to set state of the CTRL pin.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @param[in] pin_state : Output pin state.
 * @return Nothing.
 * @note None.
 */
void nanopower3_set_ctr_pin ( nanopower3_t *ctx, uint8_t pin_state );

/**
 * @brief Nano Power 3 command writing function.
 * @details This function writes a command byte and desired data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @param[in] cmd : Command to be sent.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanopower3_write_data ( nanopower3_t *ctx, uint8_t cmd, uint8_t data_in );

/**
 * @brief Nano Power 3 set wiper position function.
 * @details This function is used to set wiper position of the Nano Power 3 Click.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanopower3_set_wiper_pos ( nanopower3_t *ctx, uint8_t wiper_pos );

/**
 * @brief Nano Power 3 set resistance function.
 * @details This function is used to set resistance in Ohms of the Nano Power 3 Click.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @param[in] resistance : Resistance to be set in Ohms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanopower3_set_resistance ( nanopower3_t *ctx, uint32_t resistance );

/**
 * @brief Nano Power 3 set output voltage function.
 * @details This function is used to set output voltage of the Nano Power 3 Click.
 * @param[in] ctx : Click context object.
 * See #nanopower3_t object definition for detailed explanation.
 * @param[in] out_vol : Output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanopower3_set_voltage ( nanopower3_t *ctx, uint8_t out_vol );

#ifdef __cplusplus
}
#endif
#endif // NANOPOWER3_H

/*! @} */ // nanopower3

// ------------------------------------------------------------------------ END
