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
 * @file adc26.h
 * @brief This file contains API for ADC 26 Click Driver.
 */

#ifndef ADC26_H
#define ADC26_H

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
 * @addtogroup adc26 ADC 26 Click Driver
 * @brief API for configuring and manipulating ADC 26 Click driver.
 * @{
 */

/**
 * @defgroup adc26_reg ADC 26 Registers List
 * @brief List of registers of ADC 26 Click driver.
 */

/**
 * @addtogroup adc26_reg
 * @{
 */

/**
 * @brief ADC 26 register map.
 * @details Specified register map of ADC 26 Click driver.
 */
#define ADC26_REG_CONVERSION                0x00
#define ADC26_REG_CONFIG                    0x01
#define ADC26_REG_LO_THRESH                 0x02
#define ADC26_REG_HI_THRESH                 0x03

/*! @} */ // adc26_reg

/**
 * @defgroup adc26_set ADC 26 Registers Settings
 * @brief Settings for registers of ADC 26 Click driver.
 */

/**
 * @addtogroup adc26_set
 * @{
 */

/**
 * @brief ADC 26 CONFIG register setting.
 * @details Specified setting for CONFIG register of ADC 26 Click driver.
 */
#define ADC26_CONFIG_OS_NO_EFFECT           0x0000
#define ADC26_CONFIG_OS_START_CONVERSION    0x8000
#define ADC26_CONFIG_OS_MASK                0x8000
#define ADC26_CONFIG_MUX_P_AIN0_N_AIN1      0x0000
#define ADC26_CONFIG_MUX_P_AIN0_N_AIN3      0x1000
#define ADC26_CONFIG_MUX_P_AIN1_N_AIN3      0x2000
#define ADC26_CONFIG_MUX_P_AIN2_N_AIN3      0x3000
#define ADC26_CONFIG_MUX_P_AIN0_N_GND       0x4000
#define ADC26_CONFIG_MUX_P_AIN1_N_GND       0x5000
#define ADC26_CONFIG_MUX_P_AIN2_N_GND       0x6000
#define ADC26_CONFIG_MUX_P_AIN3_N_GND       0x7000
#define ADC26_CONFIG_MUX_MASK               0x7000
#define ADC26_CONFIG_PGA_6_144V             0x0000
#define ADC26_CONFIG_PGA_4_096V             0x0200
#define ADC26_CONFIG_PGA_2_048V             0x0400
#define ADC26_CONFIG_PGA_1_024V             0x0600
#define ADC26_CONFIG_PGA_0_512V             0x0800
#define ADC26_CONFIG_PGA_0_256V             0x0A00
#define ADC26_CONFIG_PGA_MASK               0x0E00
#define ADC26_CONFIG_MODE_CONTINUOUS        0x0000
#define ADC26_CONFIG_MODE_SINGLE_SHOT       0x0100
#define ADC26_CONFIG_MODE_MASK              0x0100
#define ADC26_CONFIG_DR_128_SPS             0x0000
#define ADC26_CONFIG_DR_250_SPS             0x0020
#define ADC26_CONFIG_DR_490_SPS             0x0040
#define ADC26_CONFIG_DR_920_SPS             0x0060
#define ADC26_CONFIG_DR_1600_SPS            0x0080
#define ADC26_CONFIG_DR_2400_SPS            0x00A0
#define ADC26_CONFIG_DR_3300_SPS            0x00C0
#define ADC26_CONFIG_DR_MASK                0x00E0
#define ADC26_CONFIG_COMP_MODE_TRADITIONAL  0x0000
#define ADC26_CONFIG_COMP_MODE_WINDOW       0x0010
#define ADC26_CONFIG_COMP_MODE_MASK         0x0010
#define ADC26_CONFIG_COMP_POL_ACTIVE_LOW    0x0000
#define ADC26_CONFIG_COMP_POL_ACTIVE_HIGH   0x0008
#define ADC26_CONFIG_COMP_POL_MASK          0x0008
#define ADC26_CONFIG_COMP_LAT_NONLATCHING   0x0000
#define ADC26_CONFIG_COMP_LAT_LATCHING      0x0004
#define ADC26_CONFIG_COMP_LAT_MASK          0x0004
#define ADC26_CONFIG_COMP_QUE_ONE_CONV      0x0000
#define ADC26_CONFIG_COMP_QUE_TWO_CONV      0x0001
#define ADC26_CONFIG_COMP_QUE_FOUR_CONV     0x0002
#define ADC26_CONFIG_COMP_QUE_DISABLE       0x0003
#define ADC26_CONFIG_COMP_QUE_MASK          0x0003

/**
 * @brief ADC 26 MUX setting.
 * @details Specified setting for MUX of ADC 26 Click driver.
 */
#define ADC26_MUX_P_AIN0_N_AIN1             0
#define ADC26_MUX_P_AIN0_N_AIN3             1
#define ADC26_MUX_P_AIN1_N_AIN3             2
#define ADC26_MUX_P_AIN2_N_AIN3             3
#define ADC26_MUX_P_AIN0_N_GND              4
#define ADC26_MUX_P_AIN1_N_GND              5
#define ADC26_MUX_P_AIN2_N_GND              6
#define ADC26_MUX_P_AIN3_N_GND              7

/**
 * @brief ADC 26 PGA setting.
 * @details Specified setting for PGA of ADC 26 Click driver.
 */
#define ADC26_PGA_0_256V                    0
#define ADC26_PGA_0_512V                    1
#define ADC26_PGA_1_024V                    2
#define ADC26_PGA_2_048V                    3
#define ADC26_PGA_4_096V                    4

/**
 * @brief ADC 26 data range setting.
 * @details Specified setting for data range of ADC 26 Click driver.
 */
#define ADC26_ADC_MIN                       ( -2048 )
#define ADC26_ADC_MAX                       ( 2047 )

/**
 * @brief ADC 26 voltage calculation setting.
 * @details Specified setting for voltage calculation of ADC 26 Click driver.
 */
#define ADC26_ADC_RESOLUTION                2048.0f
#define ADC26_ADC_GAIN_MIN                  0.256f

/**
 * @brief ADC 26 device address setting.
 * @details Specified setting for device slave address selection of
 * ADC 26 Click driver.
 */
#define ADC26_DEVICE_ADDRESS_GND            0x48
#define ADC26_DEVICE_ADDRESS_VCC            0x49
#define ADC26_DEVICE_ADDRESS_SDA            0x4A
#define ADC26_DEVICE_ADDRESS_SCL            0x4B

/*! @} */ // adc26_set

/**
 * @defgroup adc26_map ADC 26 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 26 Click driver.
 */

/**
 * @addtogroup adc26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 26 Click to the selected MikroBUS.
 */
#define ADC26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // adc26_map
/*! @} */ // adc26

/**
 * @brief ADC 26 Click context object.
 * @details Context object definition of ADC 26 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alert;         /**< Comparator output or conversion ready pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} adc26_t;

/**
 * @brief ADC 26 Click configuration object.
 * @details Configuration object definition of ADC 26 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alert;           /**< Comparator output or conversion ready pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} adc26_cfg_t;

/**
 * @brief ADC 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC26_OK = 0,
    ADC26_ERROR = -1

} adc26_return_value_t;

/*!
 * @addtogroup adc26 ADC 26 Click Driver
 * @brief API for configuring and manipulating ADC 26 Click driver.
 * @{
 */

/**
 * @brief ADC 26 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc26_cfg_setup ( adc26_cfg_t *cfg );

/**
 * @brief ADC 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adc26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc26_init ( adc26_t *ctx, adc26_cfg_t *cfg );

/**
 * @brief ADC 26 default configuration function.
 * @details This function executes a default configuration of ADC 26
 * Click board.
 * @param[in] ctx : Click context object.
 * See #adc26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t adc26_default_cfg ( adc26_t *ctx );

/**
 * @brief ADC 26 write reg function.
 * @details This function writes a desired data word to the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adc26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc26_write_reg ( adc26_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief ADC 26 read reg function.
 * @details This function reads a desired data word from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #adc26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc26_read_reg ( adc26_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief ADC 26 get alert pin function.
 * @details This function returns the ALERT (data ready) pin logic state.
 * @param[in] ctx : Click context object.
 * See #adc26_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t adc26_get_alert_pin ( adc26_t *ctx );

/**
 * @brief ADC 26 start conversion function.
 * @details This function starts a single-shot conversion for the selected MUX channel
 * and gain level (full-scale range).
 * @param[in] ctx : Click context object.
 * See #adc26_t object definition for detailed explanation.
 * @param[in] mux : MUX channel selection, see ADC26_MUX_x macros definition.
 * @param[in] pga : Gain level or full-scale range selection, see ADC26_PGA_x macros definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc26_start_conversion ( adc26_t *ctx, uint8_t mux, uint8_t pga );

/**
 * @brief ADC 26 write threshold function.
 * @details This function writes the comparator upper and lower threshold ADC values.
 * @param[in] ctx : Click context object.
 * See #adc26_t object definition for detailed explanation.
 * @param[in] lo_thresh : Lower threshold ADC value [-2048,2047].
 * @param[in] hi_thresh : Upper threshold ADC value [-2048,2047].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc26_write_threshold ( adc26_t *ctx, int16_t lo_thresh, int16_t hi_thresh );

/**
 * @brief ADC 26 read ADC function.
 * @details This function reads the RAW ADC measurement.
 * @param[in] ctx : Click context object.
 * See #adc26_t object definition for detailed explanation.
 * @param[out] data_out : RAW ADC data measurement [-2048,2047].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc26_read_adc ( adc26_t *ctx, int16_t *data_out );

/**
 * @brief ADC 26 read voltage function.
 * @details This function reads the RAW ADC measurement and converts it to a voltage level.
 * @param[in] ctx : Click context object.
 * See #adc26_t object definition for detailed explanation.
 * @param[out] voltage : Voltage level output which is dependent on a PGA setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc26_read_voltage ( adc26_t *ctx, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // ADC26_H

/*! @} */ // adc26

// ------------------------------------------------------------------------ END
