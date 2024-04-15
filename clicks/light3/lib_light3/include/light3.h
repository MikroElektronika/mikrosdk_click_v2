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
 * @file light3.h
 * @brief This file contains API for Light 3 Click Driver.
 */

#ifndef LIGHT3_H
#define LIGHT3_H

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
 * @addtogroup light3 Light 3 Click Driver
 * @brief API for configuring and manipulating Light 3 Click driver.
 * @{
 */

/**
 * @defgroup light3_reg Light 3 Registers List
 * @brief List of registers of Light 3 Click driver.
 */

/**
 * @addtogroup light3_reg
 * @{
 */

/**
 * @brief Light 3 description register.
 * @details Specified register for description of Light 3 Click driver.
 */
#define LIGHT3_REG_RESULT_MSB_CH0           0x00
#define LIGHT3_REG_RESULT_LSB_CH0           0x01
#define LIGHT3_REG_RESULT_MSB_CH1           0x02
#define LIGHT3_REG_RESULT_LSB_CH1           0x03
#define LIGHT3_REG_RESULT_FIFO_MSB_CH0      0x04
#define LIGHT3_REG_RESULT_FIFO_LSB_CH0      0x05
#define LIGHT3_REG_RESULT_FIFO_MSB_CH1      0x06
#define LIGHT3_REG_RESULT_FIFO_LSB_CH1      0x07
#define LIGHT3_REG_TRESHOLD_LOW             0x08
#define LIGHT3_REG_TRESHOLD_HIGH            0x09
#define LIGHT3_REG_CONFIG                   0x0A
#define LIGHT3_REG_INT_CONFIG               0x0B
#define LIGHT3_REG_ERROR_FLAGS              0x0C
#define LIGHT3_REG_DEVICE_ID                0x11

/*! @} */ // light3_reg

/**
 * @defgroup light3_set Light 3 Registers Settings
 * @brief Settings for registers of Light 3 Click driver.
 */

/**
 * @addtogroup light3_set
 * @{
 */

/**
 * @brief Light 3 description setting.
 * @details Specified setting for description of Light 3 Click driver.
 */
#define LIGHT3_QWAKE_EN                     0x8000u
#define LIGHT3_RANGE_561_LUX                0x0000u
#define LIGHT3_RANGE_1_1_KLUX               0x0400u
#define LIGHT3_RANGE_2_2_KLUX               0x0800u
#define LIGHT3_RANGE_4_4_KLUX               0x0C00u
#define LIGHT3_RANGE_8_9_KLUX               0x1000u
#define LIGHT3_RANGE_17_9_KLUX              0x1400u
#define LIGHT3_RANGE_35_9_KLUX              0x1800u
#define LIGHT3_RANGE_71_8_KLUX              0x1C00u
#define LIGHT3_RANGE_143_KLUX               0x2000u
#define LIGHT3_RANGE_AUTO_RANGE             0x3000u
#define LIGHT3_CONV_TIME_600_US             0x0000u
#define LIGHT3_CONV_TIME_1_MS               0x0040u
#define LIGHT3_CONV_TIME_1_8_MS             0x0080u
#define LIGHT3_CONV_TIME_3_4_MS             0x00C0u
#define LIGHT3_CONV_TIME_6_5_MS             0x0100u
#define LIGHT3_CONV_TIME_12_7_MS            0x0140u
#define LIGHT3_CONV_TIME_25_MS              0x0180u
#define LIGHT3_CONV_TIME_50_MS              0x01C0u
#define LIGHT3_CONV_TIME_100_MS             0x0200u
#define LIGHT3_CONV_TIME_200_MS             0x0240u
#define LIGHT3_CONV_TIME_400_MS             0x0280u
#define LIGHT3_CONV_TIME_800_MS             0x02C0u
#define LIGHT3_MODE_POWER_DOWN              0x0000u
#define LIGHT3_MODE_AUTO_RANGE_ONE_SHOT     0x0010u
#define LIGHT3_MODE_ONE_SHOT                0x0020u
#define LIGHT3_MODE_CONTINUOUS              0x0030u
#define LIGHT3_LATCH                        0x0008u
#define LIGHT3_INT_POL_ACTIVE_LOW           0x0000u
#define LIGHT3_INT_POL_ACTIVE_HIGH          0x0004u
#define LIGHT3_FAULT_COUNT_1                0x0000u
#define LIGHT3_FAULT_COUNT_2                0x0001u
#define LIGHT3_FAULT_COUNT_4                0x0002u
#define LIGHT3_FAULT_COUNT_8                0x0003u

/**
 * @brief Light 3 INT_CONFIG register description setting.
 * @details Specified setting for INT_CONFIG register description of Light 3 Click driver.
 */
#define LIGHT3_INT_CONFIG_REG_DEF_VALUE     0x8000u
#define LIGHT3_TRESHOLD_CH0_SEL             0x0000u
#define LIGHT3_TRESHOLD_CH1_SEL             0x0020u
#define LIGHT3_INT_DIR_INPUT                0x0000u
#define LIGHT3_INT_DIR_OUTPUT               0x0010u
#define LIGHT3_INT_CFG_SMBUS_ALERT          0x0000u
#define LIGHT3_INT_EVERY_CONV               0x0004u
#define LIGHT3_INT_EVERY_2_CONV             0x0008u
#define LIGHT3_INT_EVERY_4_CONV             0x000Cu
#define LIGHT3_I2C_BURST_ENABLED            0x0001u

/**
 * @brief Light 3 conversion factor setting.
 * @details Specified conversion factor used to convert data into LUX of Light 3 Click driver.
 */
#define LIGHT3_LUX_CONV_FACTOR              0.000535f

/**
 * @brief Light 3 pin states setting.
 * @details Specified pin states of Light 3 Click driver.
 */
#define LIGHT3_PIN_STATE_LOW                0x00
#define LIGHT3_PIN_STATE_HIGH               0x01

/**
 * @brief Light 3 software reset setting.
 * @details Specified software reset settings of Light 3 Click driver.
 */
#define LIGHT3_SW_RESET_ADDRESS             0x00
#define LIGHT3_SW_RESET_COMMAND             0x06

/**
 * @brief Light 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Light 3 Click driver.
 */
#define LIGHT3_DEVICE_ADDRESS_0             0x44
#define LIGHT3_DEVICE_ADDRESS_1             0x45

/*! @} */ // light3_set

/**
 * @defgroup light3_map Light 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Light 3 Click driver.
 */

/**
 * @addtogroup light3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Light 3 Click to the selected MikroBUS.
 */
#define LIGHT3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // light3_map
/*! @} */ // light3

/**
 * @brief Light 3 Click context object.
 * @details Context object definition of Light 3 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} light3_t;

/**
 * @brief Light 3 Click configuration object.
 * @details Configuration object definition of Light 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} light3_cfg_t;

/**
 * @brief Light 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHT3_OK = 0,
    LIGHT3_ERROR = -1

} light3_return_value_t;

/*!
 * @addtogroup light3 Light 3 Click Driver
 * @brief API for configuring and manipulating Light 3 Click driver.
 * @{
 */

/**
 * @brief Light 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #light3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void light3_cfg_setup ( light3_cfg_t *cfg );

/**
 * @brief Light 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #light3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_init ( light3_t *ctx, light3_cfg_t *cfg );

/**
 * @brief Light 3 default configuration function.
 * @details This function executes a default configuration of Light 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t light3_default_cfg ( light3_t *ctx );

/**
 * @brief Light 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_generic_write ( light3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Light 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_generic_read ( light3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Light 3 get INT pin state function.
 * @details This function is used to get INT pin state of Light 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @return INT pin state.
 */
uint8_t light3_get_int_pin ( light3_t *ctx );

/**
 * @brief Light 3 software reset function.
 * @details This function is used to perform software reset.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_sw_reset ( light3_t *ctx );

/**
 * @brief Light 3 register writing function.
 * @details This function writes a desired data into
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_write_reg ( light3_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Light 3 register reading function.
 * @details This function reads data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_read_reg ( light3_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Light 3 read CH0 data function.
 * @details This function reads ambient light data from the Channel 0 
 * and performs the calculatios from raw data to Lux.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @param[out] lux : Read ambient light in lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_get_ch0_data ( light3_t *ctx, float *lux );

/**
 * @brief Light 3 read CH1 data function.
 * @details This function reads ambient light data from the Channel 1 
 * and performs the calculatios from raw data to Lux.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @param[out] lux : Read ambient light in lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_get_ch1_data ( light3_t *ctx, float *lux );

/**
 * @brief Light 3 read CH0 FIFO data function.
 * @details This function reads ambient light data from the Channel 0 FIFO 
 * and performs the calculatios from raw data to Lux.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @param[out] lux : Read ambient light in lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_get_ch0_fifo_data ( light3_t *ctx, float *lux );

/**
 * @brief Light 3 read CH1 FIFO data function.
 * @details This function reads ambient light data from the Channel 1 FIFO 
 * and performs the calculatios from raw data to Lux.
 * @param[in] ctx : Click context object.
 * See #light3_t object definition for detailed explanation.
 * @param[out] lux : Read ambient light in lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light3_get_ch1_fifo_data ( light3_t *ctx, float *lux );

#ifdef __cplusplus
}
#endif
#endif // LIGHT3_H

/*! @} */ // light3

// ------------------------------------------------------------------------ END
