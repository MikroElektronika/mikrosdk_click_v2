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
 * @file color19.h
 * @brief This file contains API for Color 19 Click Driver.
 */

#ifndef COLOR19_H
#define COLOR19_H

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
 * @addtogroup color19 Color 19 Click Driver
 * @brief API for configuring and manipulating Color 19 Click driver.
 * @{
 */

/**
 * @defgroup color19_reg Color 19 Registers List
 * @brief List of registers of Color 19 Click driver.
 */

/**
 * @addtogroup color19_reg
 * @{
 */

/**
 * @brief Color 19 register map.
 * @details Specified register map of Color 19 Click driver.
 */
#define COLOR19_REG_CH0_EXP_RESMSB              0x00
#define COLOR19_REG_CH0_RESLSB_CNT_CRC          0x01
#define COLOR19_REG_CH1_EXP_RES_MSB             0x02
#define COLOR19_REG_CH1_RESLSB_CNT_CRC          0x03
#define COLOR19_REG_CH2_EXP_RES_MSB             0x04
#define COLOR19_REG_CH2_RESLSB_CNT_CRC          0x05
#define COLOR19_REG_CH3_EXP_RES_MSB             0x06
#define COLOR19_REG_CH3_RESLSB_CNT_CRC          0x07
#define COLOR19_REG_THLD_EXP_RES_L              0x08
#define COLOR19_REG_THLD_EXP_RES_H              0x09
#define COLOR19_REG_CONFIG_0                    0x0A
#define COLOR19_REG_CONFIG_1                    0x0B
#define COLOR19_REG_STATUS                      0x0C
#define COLOR19_REG_DEVICE_ID                   0x11

/*! @} */ // color19_reg

/**
 * @defgroup color19_set Color 19 Registers Settings
 * @brief Settings for registers of Color 19 Click driver.
 */

/**
 * @addtogroup color19_set
 * @{
 */

/**
 * @brief Color 19 CONFIG_0 register setting.
 * @details Specified setting for CONFIG_0 register of Color 19 Click driver.
 */
#define COLOR19_CONFIG_0_QWAKE_DIS              0x0000
#define COLOR19_CONFIG_0_QWAKE_EN               0x8000
#define COLOR19_CONFIG_0_QWAKE_MASK             0x8000
#define COLOR19_CONFIG_0_RANGE_2_25KLUX         0x0000
#define COLOR19_CONFIG_0_RANGE_4_5KLUX          0x0400
#define COLOR19_CONFIG_0_RANGE_9KLUX            0x0800
#define COLOR19_CONFIG_0_RANGE_18KLUX           0x0C00
#define COLOR19_CONFIG_0_RANGE_36KLUX           0x1000
#define COLOR19_CONFIG_0_RANGE_72KLUX           0x1400
#define COLOR19_CONFIG_0_RANGE_144KLUX          0x1800
#define COLOR19_CONFIG_0_RANGE_AUTO             0x3000
#define COLOR19_CONFIG_0_RANGE_MASK             0x3C00
#define COLOR19_CONFIG_0_CONV_600US             0x0000
#define COLOR19_CONFIG_0_CONV_1_MS              0x0040
#define COLOR19_CONFIG_0_CONV_1_8MS             0x0080
#define COLOR19_CONFIG_0_CONV_3_4MS             0x00C0
#define COLOR19_CONFIG_0_CONV_6_5MS             0x0100
#define COLOR19_CONFIG_0_CONV_12_7MS            0x0140
#define COLOR19_CONFIG_0_CONV_25MS              0x0180
#define COLOR19_CONFIG_0_CONV_50MS              0x01C0
#define COLOR19_CONFIG_0_CONV_100MS             0x0200
#define COLOR19_CONFIG_0_CONV_200MS             0x0240
#define COLOR19_CONFIG_0_CONV_400MS             0x0280
#define COLOR19_CONFIG_0_CONV_800MS             0x02C0
#define COLOR19_CONFIG_0_CONV_MASK              0x03C0
#define COLOR19_CONFIG_0_OP_MODE_PD             0x0000
#define COLOR19_CONFIG_0_OP_MODE_F_ONESHOT      0x0010
#define COLOR19_CONFIG_0_OP_MODE_ONESHOT        0x0020
#define COLOR19_CONFIG_0_OP_MODE_CONTINUOUS     0x0030
#define COLOR19_CONFIG_0_OP_MODE_MASK           0x0030
#define COLOR19_CONFIG_0_LATCH_DIS              0x0000
#define COLOR19_CONFIG_0_LATCH_EN               0x0008
#define COLOR19_CONFIG_0_LATCH_MASK             0x0008
#define COLOR19_CONFIG_0_INT_POL_LOW            0x0000
#define COLOR19_CONFIG_0_INT_POL_HIGH           0x0004
#define COLOR19_CONFIG_0_INT_POL_MASK           0x0004
#define COLOR19_CONFIG_0_FAULT_COUNT_1          0x0000
#define COLOR19_CONFIG_0_FAULT_COUNT_2          0x0001
#define COLOR19_CONFIG_0_FAULT_COUNT_4          0x0002
#define COLOR19_CONFIG_0_FAULT_COUNT_8          0x0003
#define COLOR19_CONFIG_0_FAULT_COUNT_MASK       0x0003

/**
 * @brief Color 19 CONFIG_1 register setting.
 * @details Specified setting for CONFIG_1 register of Color 19 Click driver.
 */
#define COLOR19_CONFIG_1_RESERVED               0x8000
#define COLOR19_CONFIG_1_THRESHOLD_CH0          0x0000
#define COLOR19_CONFIG_1_THRESHOLD_CH1          0x0020
#define COLOR19_CONFIG_1_THRESHOLD_CH2          0x0040
#define COLOR19_CONFIG_1_THRESHOLD_CH3          0x0060
#define COLOR19_CONFIG_1_THRESHOLD_MASK         0x0060
#define COLOR19_CONFIG_1_INT_DIR_INPUT          0x0000
#define COLOR19_CONFIG_1_INT_DIR_OUTPUT         0x0010
#define COLOR19_CONFIG_1_INT_DIR_MASK           0x0010
#define COLOR19_CONFIG_1_INT_CFG_SMBUS_ALR      0x0000
#define COLOR19_CONFIG_1_INT_CFG_NEXT_CH_RDY    0x0004
#define COLOR19_CONFIG_1_INT_CFG_ALL_CH_RDY     0x000C
#define COLOR19_CONFIG_1_INT_CFG_MASK           0x000C
#define COLOR19_CONFIG_1_I2C_BURST_DISABLE      0x0000
#define COLOR19_CONFIG_1_I2C_BURST_ENABLE       0x0001
#define COLOR19_CONFIG_1_I2C_BURST_MASK         0x0001

/**
 * @brief Color 19 STATUS register setting.
 * @details Specified setting for STATUS register of Color 19 Click driver.
 */
#define COLOR19_STATUS_OVERLOAD_FLAG            0x0008
#define COLOR19_STATUS_CONVERSION_READY_FLAG    0x0004
#define COLOR19_STATUS_FLAG_H                   0x0002
#define COLOR19_STATUS_FLAG_L                   0x0001

/**
 * @brief Color 19 device ID value.
 * @details Specified device ID value of Color 19 Click driver.
 */
#define COLOR19_DEVICE_ID                       0x0821

/**
 * @brief Color 19 channel number selection values.
 * @details Specified channel number selection values of Color 19 Click driver.
 */
#define COLOR19_CHANNEL_0                       0x00
#define COLOR19_CHANNEL_1                       0x01
#define COLOR19_CHANNEL_2                       0x02
#define COLOR19_CHANNEL_3                       0x03

/**
 * @brief Color 19 lux and color calculations.
 * @details Specified lux and color calculations of Color 19 Click driver.
 */
#define COLOR19_COEF_RED                        2.4
#define COLOR19_COEF_GREEN                      1.0
#define COLOR19_COEF_BLUE                       1.3
#define COLOR19_COEF_LUX                        0.00215

/**
 * @brief Color 19 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 19 Click driver.
 */
#define COLOR19_DEVICE_ADDRESS_0                0x44
#define COLOR19_DEVICE_ADDRESS_1                0x45

/*! @} */ // color19_set

/**
 * @defgroup color19_map Color 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 19 Click driver.
 */

/**
 * @addtogroup color19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 19 Click to the selected MikroBUS.
 */
#define COLOR19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color19_map
/*! @} */ // color19

/**
 * @brief Color 19 Click channel data object.
 * @details Channel data object definition of Color 19 Click driver.
 */
typedef struct
{
    uint8_t exponent;           /**< 4-bit exponent data which determines the full-scale range. */
    uint32_t mantissa;          /**< 20-bit mantissa data. */
    uint8_t counter;            /**< 4-bit sample counter. */
    uint8_t crc;                /**< 4-bit CRC. */
    
} color19_raw_data_t;

/**
 * @brief Color 19 Click data object.
 * @details Data object definition of Color 19 Click driver.
 */
typedef struct
{
    uint32_t ch0;               /**< CH0 (Red) ADC data counts. */
    uint32_t ch1;               /**< CH1 (Green) ADC data counts. */
    uint32_t ch2;               /**< CH2 (Blue) ADC data counts. */
    uint32_t ch3;               /**< CH3 (White) ADC data counts. */
    
} color19_adc_data_t;

/**
 * @brief Color 19 Click data object.
 * @details Data object definition of Color 19 Click driver.
 */
typedef struct
{
    uint32_t red;               /**< Red color data counts. */
    uint32_t green;             /**< Green color data counts. */
    uint32_t blue;              /**< Blue color data counts. */
    uint32_t white;             /**< White color data counts. */
    uint32_t lux;               /**< Lux data counts. */
    
} color19_data_t;

/**
 * @brief Color 19 Click context object.
 * @details Context object definition of Color 19 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} color19_t;

/**
 * @brief Color 19 Click configuration object.
 * @details Configuration object definition of Color 19 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} color19_cfg_t;

/**
 * @brief Color 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COLOR19_OK = 0,
    COLOR19_ERROR = -1

} color19_return_value_t;

/*!
 * @addtogroup color19 Color 19 Click Driver
 * @brief API for configuring and manipulating Color 19 Click driver.
 * @{
 */

/**
 * @brief Color 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color19_cfg_setup ( color19_cfg_t *cfg );

/**
 * @brief Color 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color19_init ( color19_t *ctx, color19_cfg_t *cfg );

/**
 * @brief Color 19 default configuration function.
 * @details This function executes a default configuration of Color 19
 * Click board.
 * @param[in] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t color19_default_cfg ( color19_t *ctx );

/**
 * @brief Color 19 write reg function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color19_write_reg ( color19_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Color 19 read reg function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color19_read_reg ( color19_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Color 19 read regs function.
 * @details This function reads a desired number of data words starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of data words to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color19_read_regs ( color19_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len );

/**
 * @brief Color 19 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t color19_get_int_pin ( color19_t *ctx );

/**
 * @brief Color 19 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color19_check_communication ( color19_t *ctx );

/**
 * @brief Color 19 read raw data function.
 * @details This function reads the selected channel raw data.
 * @param[in] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @param[in] ch_sel : Channel selection number.
 * @param[out] data_out : RAW channel data read.
 * See #color19_raw_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color19_read_raw_data ( color19_t *ctx, uint8_t ch_sel, color19_raw_data_t *data_out );

/**
 * @brief Color 19 read adc data function.
 * @details This function reads the ADC counts measurement of all channels.
 * @param[in] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @param[out] data_out : ADC counts measurement of all channels.
 * See #color19_adc_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color19_read_adc_data ( color19_t *ctx, color19_adc_data_t *data_out );

/**
 * @brief Color 19 read data function.
 * @details This function reads the color data measurement of all channels and calculates
 * the light intensity in lux.
 * @param[in] ctx : Click context object.
 * See #color19_t object definition for detailed explanation.
 * @param[out] data_out : Color data measurement of all channels.
 * See #color19_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color19_read_data ( color19_t *ctx, color19_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // COLOR19_H

/*! @} */ // color19

// ------------------------------------------------------------------------ END
