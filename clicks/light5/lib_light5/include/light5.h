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
 * @file light5.h
 * @brief This file contains API for Light 5 Click Driver.
 */

#ifndef LIGHT5_H
#define LIGHT5_H

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
 * @addtogroup light5 Light 5 Click Driver
 * @brief API for configuring and manipulating Light 5 Click driver.
 * @{
 */

/**
 * @defgroup light5_reg Light 5 Registers List
 * @brief List of registers of Light 5 Click driver.
 */

/**
 * @addtogroup light5_reg
 * @{
 */

/**
 * @brief Light 5 register map.
 * @details Specified register map of Light 5 Click driver.
 */
#define LIGHT5_REG_CH0_EXP_RESMSB               0x00
#define LIGHT5_REG_CH0_RESLSB_CNT_CRC           0x01
#define LIGHT5_REG_CH1_EXP_RES_MSB              0x02
#define LIGHT5_REG_CH1_RESLSB_CNT_CRC           0x03
#define LIGHT5_REG_FIFO_CH0_EXP_RES_MSB         0x04
#define LIGHT5_REG_FIFO_CH0_RESLSB_CNT_CRC      0x05
#define LIGHT5_REG_FIFO_CH1_EXP_RES_MSB         0x06
#define LIGHT5_REG_FIFO_CH1_RESLSB_CNT_CRC      0x07
#define LIGHT5_REG_THLD_EXP_RES_L               0x08
#define LIGHT5_REG_THLD_EXP_RES_H               0x09
#define LIGHT5_REG_CONFIG_0                     0x0A
#define LIGHT5_REG_CONFIG_1                     0x0B
#define LIGHT5_REG_STATUS                       0x0C
#define LIGHT5_REG_DEVICE_ID                    0x11

/*! @} */ // light5_reg

/**
 * @defgroup light5_set Light 5 Registers Settings
 * @brief Settings for registers of Light 5 Click driver.
 */

/**
 * @addtogroup light5_set
 * @{
 */

/**
 * @brief Light 5 CONFIG_0 register setting.
 * @details Specified setting for CONFIG_0 register of Light 5 Click driver.
 */
#define LIGHT5_CONFIG_0_QWAKE_DIS               0x0000
#define LIGHT5_CONFIG_0_QWAKE_EN                0x8000
#define LIGHT5_CONFIG_0_QWAKE_MASK              0x8000
#define LIGHT5_CONFIG_0_RANGE_0_613KLUX         0x0000
#define LIGHT5_CONFIG_0_RANGE_1_2KLUX           0x0400
#define LIGHT5_CONFIG_0_RANGE_2_5KLUX           0x0800
#define LIGHT5_CONFIG_0_RANGE_4_9KLUX           0x0C00
#define LIGHT5_CONFIG_0_RANGE_9_8KLUX           0x1000
#define LIGHT5_CONFIG_0_RANGE_19_6KLUX          0x1400
#define LIGHT5_CONFIG_0_RANGE_39_3KLUX          0x1800
#define LIGHT5_CONFIG_0_RANGE_78_5KLUX          0x1C00
#define LIGHT5_CONFIG_0_RANGE_157KLUX           0x2000
#define LIGHT5_CONFIG_0_RANGE_AUTO              0x3000
#define LIGHT5_CONFIG_0_RANGE_MASK              0x3C00
#define LIGHT5_CONFIG_0_CONV_600US              0x0000
#define LIGHT5_CONFIG_0_CONV_1MS                0x0040
#define LIGHT5_CONFIG_0_CONV_1_8MS              0x0080
#define LIGHT5_CONFIG_0_CONV_3_4MS              0x00C0
#define LIGHT5_CONFIG_0_CONV_6_5MS              0x0100
#define LIGHT5_CONFIG_0_CONV_12_7MS             0x0140
#define LIGHT5_CONFIG_0_CONV_25MS               0x0180
#define LIGHT5_CONFIG_0_CONV_50MS               0x01C0
#define LIGHT5_CONFIG_0_CONV_100MS              0x0200
#define LIGHT5_CONFIG_0_CONV_200MS              0x0240
#define LIGHT5_CONFIG_0_CONV_400MS              0x0280
#define LIGHT5_CONFIG_0_CONV_800MS              0x02C0
#define LIGHT5_CONFIG_0_CONV_MASK               0x03C0
#define LIGHT5_CONFIG_0_OP_MODE_PD              0x0000
#define LIGHT5_CONFIG_0_OP_MODE_F_ONESHOT       0x0010
#define LIGHT5_CONFIG_0_OP_MODE_ONESHOT         0x0020
#define LIGHT5_CONFIG_0_OP_MODE_CONTINUOUS      0x0030
#define LIGHT5_CONFIG_0_OP_MODE_MASK            0x0030
#define LIGHT5_CONFIG_0_LATCH_DIS               0x0000
#define LIGHT5_CONFIG_0_LATCH_EN                0x0008
#define LIGHT5_CONFIG_0_LATCH_MASK              0x0008
#define LIGHT5_CONFIG_0_INT_POL_LOW             0x0000
#define LIGHT5_CONFIG_0_INT_POL_HIGH            0x0004
#define LIGHT5_CONFIG_0_INT_POL_MASK            0x0004
#define LIGHT5_CONFIG_0_FAULT_COUNT_1           0x0000
#define LIGHT5_CONFIG_0_FAULT_COUNT_2           0x0001
#define LIGHT5_CONFIG_0_FAULT_COUNT_4           0x0002
#define LIGHT5_CONFIG_0_FAULT_COUNT_8           0x0003
#define LIGHT5_CONFIG_0_FAULT_COUNT_MASK        0x0003

/**
 * @brief Light 5 CONFIG_1 register setting.
 * @details Specified setting for CONFIG_1 register of Light 5 Click driver.
 */
#define LIGHT5_CONFIG_1_RESERVED                0x8000
#define LIGHT5_CONFIG_1_THRESHOLD_CH0           0x0000
#define LIGHT5_CONFIG_1_THRESHOLD_CH1           0x0020
#define LIGHT5_CONFIG_1_THRESHOLD_MASK          0x0020
#define LIGHT5_CONFIG_1_INT_DIR_INPUT           0x0000
#define LIGHT5_CONFIG_1_INT_DIR_OUTPUT          0x0010
#define LIGHT5_CONFIG_1_INT_DIR_MASK            0x0010
#define LIGHT5_CONFIG_1_INT_CFG_SMBUS_ALR       0x0000
#define LIGHT5_CONFIG_1_INT_CFG_EVERY_CONV      0x0004
#define LIGHT5_CONFIG_1_INT_CFG_EVERY_2_CONV    0x0008
#define LIGHT5_CONFIG_1_INT_CFG_EVERY_4_CONV    0x000C
#define LIGHT5_CONFIG_1_INT_CFG_MASK            0x000C
#define LIGHT5_CONFIG_1_I2C_BURST_DISABLE       0x0000
#define LIGHT5_CONFIG_1_I2C_BURST_ENABLE        0x0001
#define LIGHT5_CONFIG_1_I2C_BURST_MASK          0x0001

/**
 * @brief Light 5 STATUS register setting.
 * @details Specified setting for STATUS register of Light 5 Click driver.
 */
#define LIGHT5_STATUS_OVERLOAD_FLAG             0x0008
#define LIGHT5_STATUS_CONVERSION_READY_FLAG     0x0004
#define LIGHT5_STATUS_FLAG_H                    0x0002
#define LIGHT5_STATUS_FLAG_L                    0x0001

/**
 * @brief Light 5 device ID value.
 * @details Specified device ID value of Light 5 Click driver.
 */
#define LIGHT5_DEVICE_ID                        0x0221

/**
 * @brief Light 5 channel number selection values.
 * @details Specified channel number selection values of Light 5 Click driver.
 */
#define LIGHT5_CHANNEL_0                        0x00
#define LIGHT5_CHANNEL_1                        0x01

/**
 * @brief Light 5 lux and color calculations.
 * @details Specified lux and color calculations of Light 5 Click driver.
 */
#define LIGHT5_COEF_LUX                         0.000585
#define LIGHT5_COEF_UW_CM2                      0.0001923

/**
 * @brief Light 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Light 5 Click driver.
 */
#define LIGHT5_DEVICE_ADDRESS_0                 0x44
#define LIGHT5_DEVICE_ADDRESS_1                 0x45

/*! @} */ // light5_set

/**
 * @defgroup light5_map Light 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Light 5 Click driver.
 */

/**
 * @addtogroup light5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Light 5 Click to the selected MikroBUS.
 */
#define LIGHT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // light5_map
/*! @} */ // light5

/**
 * @brief Light 5 Click channel data object.
 * @details Channel data object definition of Light 5 Click driver.
 */
typedef struct
{
    uint8_t exponent;           /**< 4-bit exponent data which determines the full-scale range. */
    uint32_t mantissa;          /**< 20-bit mantissa data. */
    uint8_t counter;            /**< 4-bit sample counter. */
    uint8_t crc;                /**< 4-bit CRC. */
    
} light5_raw_data_t;

/**
 * @brief Light 5 Click data object.
 * @details Data object definition of Light 5 Click driver.
 */
typedef struct
{
    uint32_t ch0;               /**< CH0 (Lux) ADC data counts. */
    uint32_t ch1;               /**< CH1 (Wide Band) ADC data counts. */
    
} light5_adc_data_t;

/**
 * @brief Light 5 Click data object.
 * @details Data object definition of Light 5 Click driver.
 */
typedef struct
{
    float lux;                  /**< Lux data counts. */
    float wide_band;            /**< Wide Band data counts. */
    
} light5_data_t;

/**
 * @brief Light 5 Click context object.
 * @details Context object definition of Light 5 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} light5_t;

/**
 * @brief Light 5 Click configuration object.
 * @details Configuration object definition of Light 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} light5_cfg_t;

/**
 * @brief Light 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHT5_OK = 0,
    LIGHT5_ERROR = -1

} light5_return_value_t;

/*!
 * @addtogroup light5 Light 5 Click Driver
 * @brief API for configuring and manipulating Light 5 Click driver.
 * @{
 */

/**
 * @brief Light 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #light5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void light5_cfg_setup ( light5_cfg_t *cfg );

/**
 * @brief Light 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #light5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light5_init ( light5_t *ctx, light5_cfg_t *cfg );

/**
 * @brief Light 5 default configuration function.
 * @details This function executes a default configuration of Light 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t light5_default_cfg ( light5_t *ctx );

/**
 * @brief Light 5 write reg function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light5_write_reg ( light5_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Light 5 read reg function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light5_read_reg ( light5_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Light 5 read regs function.
 * @details This function reads a desired number of data words starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of data words to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light5_read_regs ( light5_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len );

/**
 * @brief Light 5 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t light5_get_int_pin ( light5_t *ctx );

/**
 * @brief Light 5 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light5_check_communication ( light5_t *ctx );

/**
 * @brief Light 5 read raw data function.
 * @details This function reads the selected channel raw data.
 * @param[in] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @param[in] ch_sel : Channel selection number.
 * @param[out] data_out : RAW channel data read.
 * See #light5_raw_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light5_read_raw_data ( light5_t *ctx, uint8_t ch_sel, light5_raw_data_t *data_out );

/**
 * @brief Light 5 read adc data function.
 * @details This function reads the ADC counts measurement of all channels.
 * @param[in] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @param[out] data_out : ADC counts measurement of all channels.
 * See #light5_adc_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light5_read_adc_data ( light5_t *ctx, light5_adc_data_t *data_out );

/**
 * @brief Light 5 read data function.
 * @details This function reads the light intensity in lux and wide band measurement in uW/cm2.
 * @param[in] ctx : Click context object.
 * See #light5_t object definition for detailed explanation.
 * @param[out] data_out : Data measurement of all channels.
 * See #light5_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t light5_read_data ( light5_t *ctx, light5_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // LIGHT5_H

/*! @} */ // light5

// ------------------------------------------------------------------------ END
