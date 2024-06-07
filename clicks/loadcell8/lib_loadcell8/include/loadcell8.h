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
 * @file loadcell8.h
 * @brief This file contains API for Load Cell 8 Click Driver.
 */

#ifndef LOADCELL8_H
#define LOADCELL8_H

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
 * @addtogroup loadcell8 Load Cell 8 Click Driver
 * @brief API for configuring and manipulating Load Cell 8 Click driver.
 * @{
 */

/**
 * @defgroup loadcell8_reg Load Cell 8 Registers List
 * @brief List of registers of Load Cell 8 Click driver.
 */

/**
 * @defgroup loadcell8_set Load Cell 8 Registers Settings
 * @brief Settings for registers of Load Cell 8 Click driver.
 */

/**
 * @addtogroup loadcell8_set
 * @{
 */

/**
 * @brief Load Cell 8 description setting.
 * @details Specified setting for description of Load Cell 8 Click driver.
 */
#define LOADCELL8_DATA_NO_DATA        0
#define LOADCELL8_DATA_OK             1
#define LOADCELL8_WEIGHT_100G         100u
#define LOADCELL8_WEIGHT_500G         500u
#define LOADCELL8_WEIGHT_1000G        1000u
#define LOADCELL8_WEIGHT_5000G        5000u
#define LOADCELL8_WEIGHT_10000G       10000u
#define LOADCELL8_WEIGHT_ZERO         0.0f
#define LOADCELL8_AVG_MEASURE_100     100.0
#define LOADCELL8_MEASURE_DATA_RES    0x3FFF

/**
 * @brief Load Cell 8 device address setting.
 * @details Specified setting for device slave address selection of
 * Load Cell 8 Click driver.
 */
#define LOADCELL8_DEVICE_ADDRESS      0x78

/*! @} */ // loadcell8_set

/**
 * @defgroup loadcell8_map Load Cell 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Load Cell 8 Click driver.
 */

/**
 * @addtogroup loadcell8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Load Cell 8 Click to the selected MikroBUS.
 */
#define LOADCELL8_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // loadcell8_map
/*! @} */ // loadcell8

/**
 * @brief Load Cell 8 Click context object.
 * @details Context object definition of Load Cell 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;    /**< Enable pin. */

    // Input pins
    digital_in_t an;      /**< Analog pin descriptor. */

    // Modules
    i2c_master_t i2c;     /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} loadcell8_t;

/**
 * @brief Load Cell 8 Click configuration object.
 * @details Configuration object definition of Load Cell 8 Click driver.
 */
typedef struct
{
    pin_name_t scl;     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;     /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t an;    /**< Analog pin descriptor. */
    pin_name_t en;    /**< Enable pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} loadcell8_cfg_t;

/**
 * @brief Load Cell 8 Click data object.
 * @details Data object definition of Load Cell 8 Click driver.
 */
typedef struct
{
    float tare;
    uint8_t tare_ok;
    float weight_coeff_100g;
    uint8_t weight_data_100g_ok;
    float weight_coeff_500g;
    uint8_t weight_data_500g_ok;
    float weight_coeff_1000g;
    uint8_t weight_data_1000g_ok;
    float weight_coeff_5000g;
    uint8_t weight_data_5000g_ok;
    float weight_coeff_10000g;
    uint8_t weight_data_10000g_ok;
    
} loadcell8_data_t;

/**
 * @brief Load Cell 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LOADCELL8_OK = 0,
    LOADCELL8_ERROR = -1

} loadcell8_return_value_t;

/*!
 * @addtogroup loadcell8 Load Cell 8 Click Driver
 * @brief API for configuring and manipulating Load Cell 8 Click driver.
 * @{
 */

/**
 * @brief Load Cell 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #loadcell8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void loadcell8_cfg_setup ( loadcell8_cfg_t *cfg );

/**
 * @brief Load Cell 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #loadcell8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell8_init ( loadcell8_t *ctx, loadcell8_cfg_t *cfg );

/**
 * @brief Load Cell 8 default configuration function.
 * @details This function executes a default configuration of Load Cell 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t loadcell8_default_cfg ( loadcell8_t *ctx );

/**
 * @brief Load Cell 8 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell8_generic_write ( loadcell8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Load Cell 8 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell8_generic_read ( loadcell8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Load Cell 8 HW reset function.
 * @details This function performs hardware reset with delay of 20 ms.
 * @param[in] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void loadcell8_hw_reset ( loadcell8_t *ctx );

/**
 * @brief Load Cell 8 read raw ADC value function.
 * @details This function reads raw ADC value by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell8_read_raw_adc ( loadcell8_t *ctx, uint32_t *raw_adc );

/**
 * @brief Load Cell 8 read raw ADC value function.
 * @details This function calculates the cell_data which is the raw ADC readings of 
 * the empty container by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @param[out] cell_data : Cell data object.
 * See #loadcell8_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell8_tare_scale ( loadcell8_t *ctx, loadcell8_data_t *cell_data );

/**
 * @brief Load Cell 8 calibrate weight function.
 * @details This function calibrates the weight by calculating the cell_data 
 * for the input calibration weight by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @param[in] cal_val : Etalon weight value.
 * @param[out] cell_data : Cell data object.
 * See #loadcell8_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell8_calibration_weight ( loadcell8_t *ctx, uint16_t cal_val, loadcell8_data_t *cell_data );

/**
 * @brief Load Cell 8 get weight function.
 * @details This function calculates the weight of the goods in grams.
 * @param[in] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @param[out] cell_data : Cell data object.
 * See #loadcell8_data_t object definition for detailed explanation.
 * @param[out] weight : The weight of the goods in grams.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell8_get_weight ( loadcell8_t *ctx, loadcell8_data_t *cell_data, float *weight_g );

#ifdef __cplusplus
}
#endif
#endif // LOADCELL8_H

/*! @} */ // loadcell8

// ------------------------------------------------------------------------ END
