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
 * @file buck15.h
 * @brief This file contains API for Buck 15 Click Driver.
 */

#ifndef BUCK15_H
#define BUCK15_H

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
 * @addtogroup buck15 Buck 15 Click Driver
 * @brief API for configuring and manipulating Buck 15 Click driver.
 * @{
 */

/**
 * @defgroup buck15_set Buck 15 Registers Settings
 * @brief Settings for registers of Buck 15 Click driver.
 */

/**
 * @addtogroup buck15_set
 * @{
 */

/**
 * @brief Buck 15 RDAC selection bitmasks.
 * @details Specified setting for RDAC selection of Buck 15 Click driver.
 */
#define BUCK15_INSTR_RDAC_SEL_1           0x00
#define BUCK15_INSTR_RDAC_SEL_2           0x80

/**
 * @brief Buck 15 midscale reset bitmasks.
 * @details Specified setting for midscale reset bitmasks of Buck 15 Click driver.
 */
#define BUCK15_INSTR_RDAC_MIDSCALE_DIS    0x00
#define BUCK15_INSTR_RDAC_MIDSCALE_EN     0x40

/**
 * @brief Buck 15 shutdown bitmasks.
 * @details Specified setting for shutdown bitmasks of Buck 15 Click driver.
 */
#define BUCK15_INSTR_RDAC_SHUTDOWN_DIS    0x00
#define BUCK15_INSTR_RDAC_SHUTDOWN_EN     0x20

/**
 * @brief Buck 15 output logic pin latched bitmasks.
 * @details Specified setting for output logic pin latched bitmasks of Buck 15 Click driver.
 */
#define BUCK15_INSTR_RDAC_OTUPUT_0        0x00
#define BUCK15_INSTR_RDAC_OTUPUT_1        0x08
#define BUCK15_INSTR_RDAC_OTUPUT_2        0x10
#define BUCK15_INSTR_RDAC_OTUPUT_3        0x18

/**
 * @brief Buck 15 output voltage sense wiper position data values.
 * @details Output voltage sense wiper position data values of Buck 15 Click driver.
 */
#define BUCK15_VOS_WIPER_POS              255, 175, 128, 128, 128, 199, 105,  \
                                          81, 91, 80, 79, 70, 69, 132, 130,   \
                                          130, 38, 102, 71, 8, 5, 1

/**
 * @brief Buck 15 output voltage setting wiper position data values.
 * @details Output voltage setting wiper position data values of Buck 15 Click driver.
 */
#define BUCK15_VSET_WIPER_POS             1, 10, 63, 101, 146, 218, 180, 175, \
                                          185, 190, 200, 200, 205, 225, 227,  \
                                          228, 211, 235, 252, 254, 254, 255

/**
 * @brief Buck 15 output voltage data table.
 * @details Output voltage data table of Buck 15 Click driver.
 */
#define BUCK15_VOUT_TABLE                 0.6f, 0.8f, 1.0f, 1.1f, 1.3f, 1.5f, \
                                          1.8f, 1.9f, 2.0f, 2.2f, 2.5f, 2.6f, \
                                          2.8f, 3.0f, 3.2f, 3.3f, 3.5f, 3.8f, \
                                          4.0f, 4.3f, 4.6f, 5.0f


/**
 * @brief Buck 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Buck 15 Click driver.
 */
#define BUCK15_DEVICE_ADDRESS_GND         0x2C
#define BUCK15_DEVICE_ADDRESS_VCC         0x2D

/*! @} */ // buck15_set

/**
 * @defgroup buck15_map Buck 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck 15 Click driver.
 */

/**
 * @addtogroup buck15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck 15 Click to the selected MikroBUS.
 */
#define BUCK15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buck15_map
/*! @} */ // buck15

/**
 * @brief Buck 15 Click context object.
 * @details Context object definition of Buck 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;    /**< Enable pin. */

    // Input pins
    digital_in_t pg;     /**< Power good pin. */

    // Modules
    i2c_master_t i2c;    /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} buck15_t;

/**
 * @brief Buck 15 Click configuration object.
 * @details Configuration object definition of Buck 15 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;     /**< Enable pin. */
    pin_name_t pg;     /**< Power good pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} buck15_cfg_t;

/**
 * @brief Buck 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCK15_OK = 0,
    BUCK15_ERROR = -1

} buck15_return_value_t;

/**
 * @brief Buck 15 output voltage values.
 * @details Predefined enum values for output voltage values.
 */
typedef enum
{
    BUCK15_VOUT_0V6 = 0,
    BUCK15_VOUT_0V8,
    BUCK15_VOUT_1V,
    BUCK15_VOUT_1V1,
    BUCK15_VOUT_1V3,
    BUCK15_VOUT_1V5,
    BUCK15_VOUT_1V8,
    BUCK15_VOUT_1V9,
    BUCK15_VOUT_2V,
    BUCK15_VOUT_2V2,
    BUCK15_VOUT_2V5,
    BUCK15_VOUT_2V6,
    BUCK15_VOUT_2V8,
    BUCK15_VOUT_3V,
    BUCK15_VOUT_3V2,
    BUCK15_VOUT_3V3,
    BUCK15_VOUT_3V5,
    BUCK15_VOUT_3V8,
    BUCK15_VOUT_4V,
    BUCK15_VOUT_4V3,
    BUCK15_VOUT_4V6,
    BUCK15_VOUT_5V,

} buck15_vout_t;

/*!
 * @addtogroup buck15 Buck 15 Click Driver
 * @brief API for configuring and manipulating Buck 15 Click driver.
 * @{
 */

/**
 * @brief Buck 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buck15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buck15_cfg_setup ( buck15_cfg_t *cfg );

/**
 * @brief Buck 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buck15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck15_init ( buck15_t *ctx, buck15_cfg_t *cfg );

/**
 * @brief Buck 15 default configuration function.
 * @details This function executes a default configuration of Buck 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t buck15_default_cfg ( buck15_t *ctx );

/**
 * @brief Buck 15 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state
 * of the TPS62903, 3-V to 17-V, High Efficiency and Low IQ Buck Converter
 * on the Buck 15 Click board.
 * @param[in] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void buck15_enable_device ( buck15_t *ctx );

/**
 * @brief Buck 15 disable device function.
 * @details This function disables the device by setting the EN pin to high logic state
 * of the TPS62903, 3-V to 17-V, High Efficiency and Low IQ Buck Converter
 * on the Buck 15 Click board.
 * @param[in] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void buck15_disable_device ( buck15_t *ctx );

/**
 * @brief Buck 15 disable device function.
 * @details This function disables the device
 * of the TPS62903, 3-V to 17-V, High Efficiency and Low IQ Buck Converter
 * on the Buck 15 Click board.
 * @param[in] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
uint8_t buck15_get_power_good ( buck15_t *ctx );

/**
 * @brief Buck 15 I2C writing function.
 * @details This function writes a data byte to 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @param[in] instr : Instruction Byte.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck15_generic_write ( buck15_t *ctx, uint8_t instr, uint8_t data_in );

/**
 * @brief Buck 15 I2C reading function.
 * @details This function reads a desired data bytes from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @param[in] instr : Instruction Byte.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck15_generic_read ( buck15_t *ctx, uint8_t instr, uint8_t *data_out );

/**
 * @brief Buck 15 set VSET function.
 * @details This function sets the wiper position for the output voltage settings 
 * by using an I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @param[in] vos_wp : VSET wiper position.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck15_set_vset ( buck15_t *ctx, uint8_t vset_wp );

/**
 * @brief Buck 15 set VOS function.
 * @details This function sets the wiper position for the output voltage sense 
 * by using an I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @param[in] vos_wp : VOS wiper position.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck15_set_vos ( buck15_t *ctx, uint8_t vos_wp );

/**
 * @brief Buck 15 set VOUT function.
 * @details This function sets the voltage output
 * by using an I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck15_t object definition for detailed explanation.
 * @param[in] vout : Voltage output.
 * See #buck15_vout_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck15_set_vout ( buck15_t *ctx, buck15_vout_t vout );

#ifdef __cplusplus
}
#endif
#endif // BUCK15_H

/*! @} */ // buck15

// ------------------------------------------------------------------------ END
