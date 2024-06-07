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
 * @file light2.h
 * @brief This file contains API for Light 2 Click Driver.
 */

#ifndef LIGHT2_H
#define LIGHT2_H

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
 * @addtogroup light2 Light 2 Click Driver
 * @brief API for configuring and manipulating Light 2 Click driver.
 * @{
 */

/**
 * @defgroup light2_reg Light 2 Registers List
 * @brief List of registers of Light 2 Click driver.
 */

/**
 * @addtogroup light2_reg
 * @{
 */

/**
 * @brief Light 2 description register.
 * @details Specified register for description of Light 2 Click driver.
 */
#define LIGHT2_REG_COMMAND              0x00
#define LIGHT2_REG_DATA_LSB             0x01
#define LIGHT2_REG_DATA_MSB             0x02

/*! @} */ // light2_reg

/**
 * @defgroup light2_set Light 2 Registers Settings
 * @brief Settings for registers of Light 2 Click driver.
 */

/**
 * @addtogroup light2_set
 * @{
 */

/**
 * @brief Light 2 description setting.
 * @details Specified setting for description of Light 2 Click driver.
 */
#define LIGHT2_EN_DEVICE                0x80
#define LIGHT2_ONE_TIME_MEASURE         0x00
#define LIGHT2_EN_CONT_MEASURE          0x40
#define LIGHT2_AMBIENT_LIGHT_SENS       0x00
#define LIGHT2_IR_LIGHT_SENS            0x20
#define LIGHT2_16_BIT_ADC               0x00
#define LIGHT2_12_BIT_ADC               0x04
#define LIGHT2_8_BIT_ADC                0x08
#define LIGHT2_4_BIT_ADC                0x0C
#define LIGHT2_ADC_RESOLUTION_MASK      0x0C
#define LIGHT2_ADC_DATA_OUT             0x10
#define LIGHT2_TIMER_DATA_OUT           0x14
#define LIGHT2_RANGE_1                  0x00
#define LIGHT2_RANGE_2                  0x01
#define LIGHT2_RANGE_3                  0x02
#define LIGHT2_RANGE_4                  0x03
#define LIGHT2_RANGE_MASK               0x03

/**
 * @brief Light 2 maximum range reading value.
 * @details Specified values for maximum range reading of Light 2 Click driver.
 */
#define LIGHT2_RANGE_1_MAX              1000
#define LIGHT2_RANGE_2_MAX              4000
#define LIGHT2_RANGE_3_MAX              16000
#define LIGHT2_RANGE_4_MAX              64000

/**
 * @brief Light 2 maximum ADC value.
 * @details Specified ADC values of Light 2 Click driver.
 */
#define LIGHT2_16_BIT_MAX               0xFFFFu
#define LIGHT2_12_BIT_MAX               0x0FFFu
#define LIGHT2_8_BIT_MAX                0x00FFu
#define LIGHT2_4_BIT_MAX                0x000Fu

/**
 * @brief Light 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Light 2 Click driver.
 */
#define LIGHT2_DEVICE_ADDRESS_0        0x44
#define LIGHT2_DEVICE_ADDRESS_1        0x45

/*! @} */ // light2_set

/**
 * @defgroup light2_map Light 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Light 2 Click driver.
 */

/**
 * @addtogroup light2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Light 2 Click to the selected MikroBUS.
 */
#define LIGHT2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // light2_map
/*! @} */ // light2

/**
 * @brief Light 2 Click context object.
 * @details Context object definition of Light 2 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float a_const;              /**< LUX calculation constant. */

} light2_t;

/**
 * @brief Light 2 Click configuration object.
 * @details Configuration object definition of Light 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} light2_cfg_t;

/**
 * @brief Light 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHT2_OK = 0,
    LIGHT2_ERROR = -1

} light2_return_value_t;

/*!
 * @addtogroup light2 Light 2 Click Driver
 * @brief API for configuring and manipulating Light 2 Click driver.
 * @{
 */

/**
 * @brief Light 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #light2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void light2_cfg_setup ( light2_cfg_t *cfg );

/**
 * @brief Light 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #light2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #light2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light2_init ( light2_t *ctx, light2_cfg_t *cfg );

/**
 * @brief Light 2 default configuration function.
 * @details This function executes a default configuration of Light 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #light2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t light2_default_cfg ( light2_t *ctx );

/**
 * @brief Light 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light2_generic_write ( light2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Light 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light2_generic_read ( light2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Light 2 write config function.
 * @details This function is used to set configuration for Light 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #light2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light2_write_config ( light2_t *ctx, uint8_t data_in );

/**
 * @brief Light 2 raw data reading function.
 * @details This function reads raw data from the ADC of Light 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #light2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light2_read_raw_data ( light2_t *ctx, uint16_t *data_out );

/**
 * @brief Light 2 get calculation constant function.
 * @details This function is used to get a calculation constant depending on Light 2
 * click board configuration.
 * @param[in] ctx : Click context object.
 * See #light2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use this function after any changes to the configuration to get calculation factor.
 */
err_t light2_get_cal_const ( light2_t *ctx );

/**
 * @brief Light 2 get light data function.
 * @details This function is used to read light data of Light 2
 * click board configuration.
 * @param[in] ctx : Click context object.
 * See #light2_t object definition for detailed explanation.
 * @param[out] light_data : Read data in LUX.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light2_get_light_data ( light2_t *ctx, float *light_data );

#ifdef __cplusplus
}
#endif
#endif // LIGHT2_H

/*! @} */ // light2

// ------------------------------------------------------------------------ END
