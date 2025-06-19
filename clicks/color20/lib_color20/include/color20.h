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
 * @file color20.h
 * @brief This file contains API for Color 20 Click Driver.
 */

#ifndef COLOR20_H
#define COLOR20_H

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
 * @addtogroup color20 Color 20 Click Driver
 * @brief API for configuring and manipulating Color 20 Click driver.
 * @{
 */

/**
 * @defgroup color20_reg Color 20 Registers List
 * @brief List of registers of Color 20 Click driver.
 */

/**
 * @addtogroup color20_reg
 * @{
 */

/**
 * @brief Color 20 register list.
 * @details Specified register list of Color 20 Click driver.
 */
#define COLOR20_REG_RGB_CONF_0                      0x00
#define COLOR20_REG_RGB_CONF_1                      0x01
#define COLOR20_REG_G_THDH_L                        0x04
#define COLOR20_REG_G_THDH_H                        0x05
#define COLOR20_REG_G_THDL_L                        0x06
#define COLOR20_REG_G_THDL_H                        0x07
#define COLOR20_REG_R_DATA_L                        0x10
#define COLOR20_REG_R_DATA_H                        0x11
#define COLOR20_REG_G_DATA_L                        0x12
#define COLOR20_REG_G_DATA_H                        0x13
#define COLOR20_REG_B_DATA_L                        0x14
#define COLOR20_REG_B_DATA_H                        0x15
#define COLOR20_REG_IR_DATA_L                       0x16
#define COLOR20_REG_IR_DATA_H                       0x17
#define COLOR20_REG_VEML6046X00_ID_L                0x18
#define COLOR20_REG_VEML6046X00_ID_H                0x19
#define COLOR20_REG_INT_FLAG                        0x1B

/*! @} */ // color20_reg

/**
 * @defgroup color20_set Color 20 Registers Settings
 * @brief Settings for registers of Color 20 Click driver.
 */

/**
 * @addtogroup color20_set
 * @{
 */

/**
 * @brief Color 20 RGB config register setting.
 * @details Specified setting for RGB config register of Color 20 Click driver.
 */
#define COLOR20_RGB_CONFIG_RGB_IT_3_125_MS          0x0000
#define COLOR20_RGB_CONFIG_RGB_IT_6_25_MS           0x1000
#define COLOR20_RGB_CONFIG_RGB_IT_12_5_MS           0x2000
#define COLOR20_RGB_CONFIG_RGB_IT_25_MS             0x3000
#define COLOR20_RGB_CONFIG_RGB_IT_50_MS             0x4000
#define COLOR20_RGB_CONFIG_RGB_IT_100_MS            0x5000
#define COLOR20_RGB_CONFIG_RGB_IT_200_MS            0x6000
#define COLOR20_RGB_CONFIG_RGB_IT_400_MS            0x7000
#define COLOR20_RGB_CONFIG_RGB_IT_MASK              0x7000
#define COLOR20_RGB_CONFIG_RGB_MODE_AUTO            0x0000
#define COLOR20_RGB_CONFIG_RGB_MODE_ACTIVE_FORCE    0x0800
#define COLOR20_RGB_CONFIG_RGB_MODE_MASK            0x0800
#define COLOR20_RGB_CONFIG_RGB_TRIGGER_OFF          0x0000
#define COLOR20_RGB_CONFIG_RGB_TRIGGER_ON           0x0400
#define COLOR20_RGB_CONFIG_RGB_TRIGGER_MASK         0x0400
#define COLOR20_RGB_CONFIG_G_INT_OFF                0x0000
#define COLOR20_RGB_CONFIG_G_INT_ON                 0x0200
#define COLOR20_RGB_CONFIG_G_INT_MASK               0x0200
#define COLOR20_RGB_CONFIG_RGB_ON_TURN_ON           0x0000
#define COLOR20_RGB_CONFIG_RGB_ON_TURN_OFF          0x0180
#define COLOR20_RGB_CONFIG_RGB_ON_MASK              0x0180
#define COLOR20_RGB_CONFIG_RGB_PDDIV_2_2_PD         0x0000
#define COLOR20_RGB_CONFIG_RGB_PDDIV_1_2_PD         0x0040
#define COLOR20_RGB_CONFIG_RGB_PDDIV_MASK           0x0040
#define COLOR20_RGB_CONFIG_RGB_GAIN_X1              0x0000
#define COLOR20_RGB_CONFIG_RGB_GAIN_X2              0x0008
#define COLOR20_RGB_CONFIG_RGB_GAIN_X0_66           0x0010
#define COLOR20_RGB_CONFIG_RGB_GAIN_X0_5            0x0018
#define COLOR20_RGB_CONFIG_RGB_GAIN_MASK            0x0018
#define COLOR20_RGB_CONFIG_G_PERS_1                 0x0000
#define COLOR20_RGB_CONFIG_G_PERS_2                 0x0002
#define COLOR20_RGB_CONFIG_G_PERS_4                 0x0004
#define COLOR20_RGB_CONFIG_G_PERS_8                 0x0006
#define COLOR20_RGB_CONFIG_G_PERS_MASK              0x0006
#define COLOR20_RGB_CONFIG_RGB_CAL_OFF              0x0000
#define COLOR20_RGB_CONFIG_RGB_CAL_ON               0x0001
#define COLOR20_RGB_CONFIG_RGB_CAL_MASK             0x0001

/**
 * @brief Color 20 device ID setting.
 * @details Specified setting for device ID of Color 20 Click driver.
 */
#define COLOR20_DEVICE_ID                           0x0001

/**
 * @brief Color 20 RGB minimal resolution setting.
 * @details Specified setting for RGB minimal resolution of Color 20 Click driver.
 */
#define COLOR20_RGB_MIN_RES                         0.00525f

/**
 * @brief Color 20 INT flag register setting.
 * @details Specified setting for INT flag register of Color 20 Click driver.
 */
#define COLOR20_INT_FLAG_AF_DATA_READY              0x08
#define COLOR20_INT_FLAG_G_IF_L                     0x04
#define COLOR20_INT_FLAG_G_IF_H                     0x02

/**
 * @brief Color 20 default setting.
 * @details Specified default setting of Color 20 Click driver.
 */
#define COLOR20_RGB_CONFIG_DEFAULT                  ( COLOR20_RGB_CONFIG_RGB_IT_25_MS | \
                                                      COLOR20_RGB_CONFIG_RGB_MODE_AUTO | \
                                                      COLOR20_RGB_CONFIG_RGB_TRIGGER_OFF | \
                                                      COLOR20_RGB_CONFIG_G_INT_OFF | \
                                                      COLOR20_RGB_CONFIG_RGB_ON_TURN_ON | \
                                                      COLOR20_RGB_CONFIG_RGB_PDDIV_2_2_PD | \
                                                      COLOR20_RGB_CONFIG_RGB_GAIN_X1 | \
                                                      COLOR20_RGB_CONFIG_G_PERS_8 | \
                                                      COLOR20_RGB_CONFIG_RGB_CAL_OFF )
#define COLOR20_THRESHOLD_LOW_DEFAULT               0x0000
#define COLOR20_THRESHOLD_HIGH_DEFAULT              0x0000

/**
 * @brief Color 20 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 20 Click driver.
 */
#define COLOR20_DEVICE_ADDRESS                      0x29

/*! @} */ // color20_set

/**
 * @defgroup color20_map Color 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 20 Click driver.
 */

/**
 * @addtogroup color20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 20 Click to the selected MikroBUS.
 */
#define COLOR20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color20_map
/*! @} */ // color20

/**
 * @brief Color 20 Click context object.
 * @details Context object definition of Color 20 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    float rgb_res;              /**< RGB resolution (lux/cnt). */

} color20_t;

/**
 * @brief Color 20 Click configuration object.
 * @details Configuration object definition of Color 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} color20_cfg_t;

/**
 * @brief Color 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COLOR20_OK = 0,
    COLOR20_ERROR = -1

} color20_return_value_t;

/*!
 * @addtogroup color20 Color 20 Click Driver
 * @brief API for configuring and manipulating Color 20 Click driver.
 * @{
 */

/**
 * @brief Color 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color20_cfg_setup ( color20_cfg_t *cfg );

/**
 * @brief Color 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color20_init ( color20_t *ctx, color20_cfg_t *cfg );

/**
 * @brief Color 20 default configuration function.
 * @details This function executes a default configuration of Color 20
 * Click board.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t color20_default_cfg ( color20_t *ctx );

/**
 * @brief Color 20 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color20_generic_write ( color20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Color 20 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color20_generic_read ( color20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Color 20 Get INT function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t color20_get_int_pin ( color20_t *ctx );

/**
 * @brief Color 20 check communication function.
 * @details This function checks the device ID to verify communication with the sensor.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @return @li @c  0 - Success (device ID matched),
 *         @li @c -1 - Error.
 * @note None.
 */
err_t color20_check_communication ( color20_t *ctx );

/**
 * @brief Color 20 set RGB configuration function.
 * @details This function sets the RGB measurement configuration and calculates the resolution factor.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[in] config : RGB configuration register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Updates the @c ctx->rgb_res field based on config.
 */
err_t color20_set_rgb_config ( color20_t *ctx, uint16_t config );

/**
 * @brief Color 20 get RGB configuration function.
 * @details This function reads the current RGB configuration register value.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[out] config : Pointer to the variable to store RGB configuration value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t color20_get_rgb_config ( color20_t *ctx, uint16_t *config );

/**
 * @brief Color 20 set green channel thresholds function.
 * @details This function sets the high and low threshold values for the green channel interrupt.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[in] threshold_low : Low threshold value.
 * @param[in] threshold_high : High threshold value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t color20_set_g_threshold ( color20_t *ctx, uint16_t threshold_low, uint16_t threshold_high );

/**
 * @brief Color 20 get green channel thresholds function.
 * @details This function reads the high and low threshold values for the green channel interrupt.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[out] threshold_low : Pointer to store the low threshold value.
 * @param[out] threshold_high : Pointer to store the high threshold value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t color20_get_g_threshold ( color20_t *ctx, uint16_t *threshold_low, uint16_t *threshold_high );

/**
 * @brief Color 20 get interrupt flag function.
 * @details This function reads the interrupt flag register.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[out] int_flag : Pointer to store the interrupt flag value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t color20_get_int_flag ( color20_t *ctx, uint8_t *int_flag );

/**
 * @brief Color 20 get raw data function.
 * @details This function reads raw measurement data for red, green, blue, and IR channels.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[out] red : Pointer to store the red channel raw value.
 * @param[out] green : Pointer to store the green channel raw value.
 * @param[out] blue : Pointer to store the blue channel raw value.
 * @param[out] ir_data : Pointer to store the infrared channel raw value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t color20_get_raw_data ( color20_t *ctx, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *ir_data );

/**
 * @brief Color 20 get scaled data function.
 * @details This function the raw IR data and red, green, and blue light intensity in lux based on raw RGB data.
 * @param[in] ctx : Click context object.
 * See #color20_t object definition for detailed explanation.
 * @param[out] red : Pointer to store calculated red light intensity (in lux).
 * @param[out] green : Pointer to store calculated green light intensity (in lux).
 * @param[out] blue : Pointer to store calculated blue light intensity (in lux).
 * @param[out] ir_data : Pointer to store the infrared channel raw value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t color20_get_data ( color20_t *ctx, float *red, float *green, float *blue, uint16_t *ir_data );

#ifdef __cplusplus
}
#endif
#endif // COLOR20_H

/*! @} */ // color20

// ------------------------------------------------------------------------ END
