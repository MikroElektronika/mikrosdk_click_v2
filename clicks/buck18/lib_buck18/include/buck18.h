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
 * @file buck18.h
 * @brief This file contains API for Buck 18 Click Driver.
 */

#ifndef BUCK18_H
#define BUCK18_H

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
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup buck18 Buck 18 Click Driver
 * @brief API for configuring and manipulating Buck 18 Click driver.
 * @{
 */

/**
 * @defgroup buck18_reg Buck 18 Registers List
 * @brief List of registers of Buck 18 Click driver.
 */

/**
 * @addtogroup buck18_reg
 * @{
 */

/**
 * @brief Buck 18 description register.
 * @details Specified register for description of Buck 18 Click driver.
 */
#define BUCK18_CMD_RDAC               0x00
#define BUCK18_CMD_RDAC_OTP           0x80

/*! @} */ // buck18_reg

/**
 * @defgroup buck18_set Buck 18 Registers Settings
 * @brief Settings for registers of Buck 18 Click driver.
 */

/**
 * @addtogroup buck18_set
 * @{
 */

/**
 * @brief Buck 18 RDAC wiper position.
 * @details RDAC wiper position of Buck 18 Click driver.
 */
#define BUCK18_OTP_VALID_PRG_RDY      0x00
#define BUCK18_OTP_VALID_TEST         0x40
#define BUCK18_OTP_VALID_ERROR        0x80
#define BUCK18_OTP_VALID_PRG_OK       0xC0

/**
 * @brief Buck 18 wiper and resistance data values.
 * @details Specified wiper and resistance data values of Buck 18 Click driver.
 */
#define BUCK18_WIPER_POS_MAX          0x3F
#define BUCK18_RES_5_KOHM             5.0f
#define BUCK18_RES_50_KOHM            50.0f
#define BUCK18_RES_55_KOHM            55.0f
#define BUCK18_RDAC_WIPER_POSITION    6, 9, 19, 26, 34, 39, 55, 48, 52, 54, 57, 59, 60, 62, 63

/**
 * @brief Buck 18 ADC setting.
 * @details Specified settings for ADC of Buck 18 Click driver.
 */
#define BUCK18_ADC_RESOLUTION         0x0FFF
#define BUCK18_VREF_3V3               3.3
#define BUCK18_VREF_5V                5.0

/**
 * @brief Buck 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Buck 18 Click driver.
 */
#define BUCK18_SET_DEV_ADDR_0         0x2C
#define BUCK18_SET_DEV_ADDR_1         0x2D

/*! @} */ // buck18_set

/**
 * @defgroup buck18_map Buck 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck 18 Click driver.
 */

/**
 * @addtogroup buck18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck 18 Click to the selected MikroBUS.
 */
#define BUCK18_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // buck18_map
/*! @} */ // buck18

/**
 * @brief Buck 18 Click context object.
 * @details Context object definition of Buck 18 Click driver.
 */
typedef struct
{
    digital_out_t rst;    /**< Enable pin. */

    analog_in_t  adc;     /**< ADC module object. */
    i2c_master_t i2c;     /**< I2C driver object. */

    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    float        vref;             /**< ADC reference voltage. */

} buck18_t;

/**
 * @brief Buck 18 Click configuration object.
 * @details Configuration object definition of Buck 18 Click driver.
 */
typedef struct
{
    pin_name_t an;     /**< Analog pin descriptor. */
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rst;    /**< Enable pin. */

    analog_in_resolution_t resolution;     /**< ADC resolution. */
    float                  vref;           /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;      /**< I2C serial speed. */
    uint8_t                i2c_address;    /**< I2C slave address. */

} buck18_cfg_t;

/**
 * @brief Buck 18 Click output voltage selection.
 * @details Cutput voltage selection of Buck 18 Click driver.
 */
typedef enum
{
    BUCK18_VOUT_3V3 = 0,
    BUCK18_VOUT_3V, 
    BUCK18_VOUT_2V8, 
    BUCK18_VOUT_2V75,
    BUCK18_VOUT_2V5, 
    BUCK18_VOUT_2V0, 
    BUCK18_VOUT_1V8,
    BUCK18_VOUT_1V5, 
    BUCK18_VOUT_1V25, 
    BUCK18_VOUT_1V2,
    BUCK18_VOUT_1V15,
    BUCK18_VOUT_1V1,
    BUCK18_VOUT_1V,
    BUCK18_VOUT_0V95,
    BUCK18_VOUT_0V9

} buck18_vout_t;

/**
 * @brief Buck 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCK18_OK = 0,
    BUCK18_ERROR = -1

} buck18_return_value_t;

/*!
 * @addtogroup buck18 Buck 18 Click Driver
 * @brief API for configuring and manipulating Buck 18 Click driver.
 * @{
 */

/**
 * @brief Buck 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buck18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buck18_cfg_setup ( buck18_cfg_t *cfg );

/**
 * @brief Buck 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buck18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck18_init ( buck18_t *ctx, buck18_cfg_t *cfg );

/**
 * @brief Buck 18 default configuration function.
 * @details This function executes a default configuration of Buck 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t buck18_default_cfg ( buck18_t *ctx );

/**
 * @brief Buck 18 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck18_read_raw_adc ( buck18_t *ctx, uint16_t *raw_adc );

/**
 * @brief Buck 18 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t buck18_read_voltage ( buck18_t *ctx, float *voltage );

/**
 * @brief Buck 18 set vref function.
 * @details This function sets the voltage reference for Buck 18 click driver.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b buck18_init is 3.3V.
 */
err_t buck18_set_vref ( buck18_t *ctx, float vref );

/**
 * @brief Buck 18 enable the device function.
 * @details This function turns on the power switch and enables the buck mode
 * of the MAXM38643, Tiny, 1.8V to 5.5V Input, 330nA IQ, 600mA nanoPower Buck Module
 * on the Buck 18 Click board.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void buck18_enable ( buck18_t *ctx );

/**
 * @brief Buck 18 disable the device function.
 * @details This function turns off power switch and disable the buck mode
 * of the MAXM38643, Tiny, 1.8V to 5.5V Input, 330nA IQ, 600mA nanoPower Buck Module
 * on the Buck 18 Click board.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void buck18_disable ( buck18_t *ctx );

/**
 * @brief Buck 18 data writing function.
 * @details This function writes a desired data byte using the selected command
 * of the AD5171, 64-Position OTP Digital Potentiometer
 * on the Buck 18 Click board.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck18_write_data ( buck18_t *ctx, uint8_t cmd, uint8_t data_in );

/**
 * @brief Buck 18 data reading function.
 * @details This function reads a data byte
 * of the AD5171, 64-Position OTP Digital Potentiometer
 * on the Buck 18 Click board.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @param[out] data_out : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck18_read_data ( buck18_t *ctx, uint8_t *data_out );

/**
 * @brief Buck 18 data writing function.
 * @details This function writes a RDAC by sets the position of the wiper position
 * of the AD5171, 64-Position OTP Digital Potentiometer
 * on the Buck 18 Click board.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position [0-63].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck18_write_rdac ( buck18_t *ctx, uint8_t wiper_pos );

/**
 * @brief Buck 18 sets the resistance function.
 * @details This function sets a desired resistance 
 * of the AD5171, 64-Position OTP Digital Potentiometer
 * on the Buck 18 Click board.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @param[in] res_kohm : Resistance [0-50kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck18_set_resistance ( buck18_t *ctx, float res_kohm );

/**
 * @brief Buck 18 sets the VOUT function.
 * @details This function sets the voltage output level 
 * of the MAXM38643, Tiny, 1.8V to 5.5V Input, 330nA IQ, 600mA nanoPower Buck Module
 * on the Buck 18 Click board.
 * @param[in] ctx : Click context object.
 * See #buck18_t object definition for detailed explanation.
 * @param[in] vout : Voltage output [0.9-3.3V].
 * See #buck18_vout_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck18_set_vout ( buck18_t *ctx, buck18_vout_t vout );

#ifdef __cplusplus
}
#endif
#endif // BUCK18_H

/*! @} */ // buck18

// ------------------------------------------------------------------------ END
