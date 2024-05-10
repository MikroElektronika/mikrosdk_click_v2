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
 * @file stepup2.h
 * @brief This file contains API for Step Up 2 Click Driver.
 */

#ifndef STEPUP2_H
#define STEPUP2_H

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
 * @addtogroup stepup2 Step Up 2 Click Driver
 * @brief API for configuring and manipulating Step Up 2 Click driver.
 * @{
 */

/**
 * @defgroup stepup2_ctrl_byte Step Up 2 Registers List
 * @brief List of registers of Step Up 2 Click driver.
 */

/**
 * @addtogroup stepup2_ctrl_byte
 * @{
 */

/**
 * @brief Step Up 2 description control byte.
 * @details Specified control byte for description of Step Up 2 Click driver.
 */
#define STEPUP2_CTRL_BYTE_VREG          0x11
#define STEPUP2_CTRL_BYTE_NVREG         0x21
#define STEPUP2_CTRL_BYTE_VREG_NVREG    0x51
#define STEPUP2_CTRL_BYTE_NVREG_VREG    0x61

/*! @} */ // stepup2_ctrl_byte

/**
 * @defgroup stepup2_set Step Up 2 Registers Settings
 * @brief Settings for registers of Step Up 2 Click driver.
 */

/**
 * @addtogroup stepup2_set
 * @{
 */

/**
 * @brief Step Up 2 wiper and resistance data values.
 * @details Specified wiper and resistance data values of Step Up 2 Click driver.
 */
#define STEPUP2_WIPER_POS_MIN           0
#define STEPUP2_WIPER_POS_MIDDLE        127
#define STEPUP2_WIPER_POS_MAX           255
#define STEPUP2_RES_0_KOHM              0.0f
#define STEPUP2_RES_3_01_KOHM           3.01f
#define STEPUP2_RES_50_KOHM             50.0f
#define STEPUP2_RES_200_KOHM            200.0f

/**
 * @brief Step Up 2 resistance and output voltage lists.
 * @details Resistance and output voltage lists of Step Up 2 Click driver.
 */
#define STEPUP2_RESISTANCE_LIST         3.01f, 6.19f, 7.87f, 9.76f, \
                                        12.1f, 18.2f, 22.6f, 28.7f, \
                                        49.9f, 75.0f, 0.0f, 100.0f, \
                                        124.0f, 154.0f, 191.0f
#define STEPUP2_VOUT_LIST               5.5f, 5.2f, 5.0f, 4.8f, 4.5f, \
                                        4.3f, 4.0f, 3.8f, 3.6f, 3.5f, \
                                        3.3f, 3.2f, 3.0f, 2.8f, 2.5f


/**
 * @brief Step Up 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Step Up 2 Click driver.
 */
#define STEPUP2_DEVICE_ADDRESS_0        0x28
#define STEPUP2_DEVICE_ADDRESS_1        0x29

/*! @} */ // stepup2_set

/**
 * @defgroup stepup2_map Step Up 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Up 2 Click driver.
 */

/**
 * @addtogroup stepup2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Up 2 Click to the selected MikroBUS.
 */
#define STEPUP2_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // stepup2_map
/*! @} */ // stepup2

/**
 * @brief Step Up 2 Click context object.
 * @details Context object definition of Step Up 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;         /**< Enable pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} stepup2_t;

/**
 * @brief Step Up 2 Click configuration object.
 * @details Configuration object definition of Step Up 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;             /**< Enable pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} stepup2_cfg_t;

/**
 * @brief Step Up 2 Click output voltage selection.
 * @details Output voltage selection of Step Up 2 Click driver.
 */
typedef enum
{
    STEPUP2_VOUT_5V5 = 0,
    STEPUP2_VOUT_5V2,
    STEPUP2_VOUT_5V,
    STEPUP2_VOUT_4V8,
    STEPUP2_VOUT_4V5,
    STEPUP2_VOUT_4V3,
    STEPUP2_VOUT_4V,
    STEPUP2_VOUT_3V8,
    STEPUP2_VOUT_3V6,
    STEPUP2_VOUT_3V5,
    STEPUP2_VOUT_3V3,
    STEPUP2_VOUT_3V2,
    STEPUP2_VOUT_3V,
    STEPUP2_VOUT_2V8,
    STEPUP2_VOUT_2V5
    
} stepup2_vout_t;

/**
 * @brief Step Up 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPUP2_OK = 0,
    STEPUP2_ERROR = -1

} stepup2_return_value_t;

/*!
 * @addtogroup stepup2 Step Up 2 Click Driver
 * @brief API for configuring and manipulating Step Up 2 Click driver.
 * @{
 */

/**
 * @brief Step Up 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepup2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepup2_cfg_setup ( stepup2_cfg_t *cfg );

/**
 * @brief Step Up 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepup2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepup2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepup2_init ( stepup2_t *ctx, stepup2_cfg_t *cfg );

/**
 * @brief Step Up 2 default configuration function.
 * @details This function executes a default configuration of Step Up 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepup2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepup2_default_cfg ( stepup2_t *ctx );

/**
 * @brief Step Up 2 enable the device function.
 * @details This function turns on the power switch and enables the boost mode
 * of the TPS61299, 95-nA Quiescent Current, 5.5-V Boost Converter
 * with Input Current Limit and Fast Transient Performance
 * on the Step Up 2 Click board.
 * @param[in] ctx : Click context object.
 * See #stepup2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void stepup2_enable ( stepup2_t *ctx );

/**
 * @brief Step Up 2 disable the device function.
 * @details This function turns off power switch and disable the boost mode
 * of the TPS61299, 95-nA Quiescent Current, 5.5-V Boost Converter
 * with Input Current Limit and Fast Transient Performance
 * on the Step Up 2 Click board.
 * @param[in] ctx : Click context object.
 * See #stepup2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void stepup2_disable ( stepup2_t *ctx );

/**
 * @brief Step Up 2 data writing function.
 * @details This function writes a desired data byte using the selected command
 * of the MAX5419, 256-Tap, Nonvolatile, I2C-Interface, Digital Potentiometers
 * on the Step Up 2 Click board.
 * @param[in] ctx : Click context object.
 * See #stepup2_t object definition for detailed explanation.
 * @param[in] ctrl_byte : Control byte.
 * See #stepup2_ctrl_byte object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepup2_write_data ( stepup2_t *ctx, uint8_t ctrl_byte, uint8_t data_in );

/**
 * @brief Step Up 2 data reading function.
 * @details This function reads the volatile memory register and the wiper position
 * of the MAX5419, 256-Tap, Nonvolatile, I2C-Interface, Digital Potentiometers
 * on the Step Up 2 Click board.
 * @param[in] ctx : Click context object.
 * See #stepup2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepup2_read_data ( stepup2_t *ctx, uint8_t *data_out );

/**
 * @brief Step Up 2 sets the wiper position function.
 * @details This function writes to the volatile memory register 
 * and the wiper position updates with the data in the volatile memory register
 * of the MAX5419, 256-Tap, Nonvolatile, I2C-Interface, Digital Potentiometers
 * on the Step Up 2 Click board.
 * @param[in] ctx : Click context object.
 * See #stepup2_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position [0-63].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepup2_set_wiper_pos ( stepup2_t *ctx, uint8_t wiper_pos );

/**
 * @brief Step Up 2 sets the resistance function.
 * @details This function sets a desired resistance 
 * by writing  to the volatile memory register and the wiper position
 * of the MAX5419, 256-Tap, Nonvolatile, I2C-Interface, Digital Potentiometers
 * on the Step Up 2 Click board.
 * @param[in] ctx : Click context object.
 * See #stepup2_t object definition for detailed explanation.
 * @param[in] res_kohm : Resistance [0-200kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepup2_set_resistance ( stepup2_t *ctx, float res_kohm );

/**
 * @brief Step Up 2 sets the VOUT function.
 * @details This function sets the voltage output level 
 * by writes to the volatile memory register and the wiper position
 * of the TPS61299, 95-nA Quiescent Current, 5.5-V Boost Converter
 * with Input Current Limit and Fast Transient Performance
 * on the Step Up 2 Click board.
 * @param[in] ctx : Click context object.
 * See #stepup2_t object definition for detailed explanation.
 * @param[in] vout : Voltage output [2.5-5.5V].
 * See #stepup2_vout_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepup2_set_vout ( stepup2_t *ctx, stepup2_vout_t vout );

#ifdef __cplusplus
}
#endif
#endif // STEPUP2_H

/*! @} */ // stepup2

// ------------------------------------------------------------------------ END
