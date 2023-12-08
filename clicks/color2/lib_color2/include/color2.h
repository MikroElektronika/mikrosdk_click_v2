/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Color 2 Click driver.
 *
 * \addtogroup color2 Color 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COLOR2_H
#define COLOR2_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define COLOR2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COLOR2_OK                               0
#define COLOR2_ERROR                           -1
/** \} */

/**
 * \defgroup config_register Config Registers
 * \{
 */ 
#define COLOR2_I2C_ADDR                         0x44
#define COLOR2_DEVICE_ID                        0x00
#define COLOR2_CONFIG_1                         0x01
#define COLOR2_CONFIG_2                         0x02
#define COLOR2_CONFIG_3                         0x03
#define COLOR2_THRESHOLD_LL                     0x04
#define COLOR2_THRESHOLD_LH                     0x05
#define COLOR2_THRESHOLD_HL                     0x06
#define COLOR2_THRESHOLD_HH                     0x07
#define COLOR2_STATUS                           0x08
#define COLOR2_GREEN_L                          0x09
#define COLOR2_GREEN_H                          0x0A
#define COLOR2_RED_L                            0x0B
#define COLOR2_RED_H                            0x0C
#define COLOR2_BLUE_L                           0x0D
#define COLOR2_BLUE_H                           0x0E
#define COLOR2_CFG_DEFAULT                      0x00
#define COLOR2_CFG1_MODE_POWERDOWN              0x00
#define COLOR2_CFG1_MODE_G                      0x01
#define COLOR2_CFG1_MODE_R                      0x02
#define COLOR2_CFG1_MODE_B                      0x03
#define COLOR2_CFG1_MODE_STANDBY                0x04
#define COLOR2_CFG1_MODE_RGB                    0x05
#define COLOR2_CFG1_MODE_RG                     0x06
#define COLOR2_CFG1_MODE_GB                     0x07
#define COLOR2_CFG1_375LUX                      0x00
#define COLOR2_CFG1_10KLUX                      0x08
#define COLOR2_CFG1_16BIT                       0x00
#define COLOR2_CFG1_12BIT                       0x10
#define COLOR2_CFG1_ADC_SYNC_NORMAL             0x00
#define COLOR2_CFG1_ADC_SYNC_TO_INT             0x20
#define COLOR2_CFG2_IR_OFFSET_OFF               0x00
#define COLOR2_CFG2_IR_OFFSET_ON                0x80
#define COLOR2_CFG2_IR_ADJUST_LOW               0x00
#define COLOR2_CFG2_IR_ADJUST_MID               0x20
#define COLOR2_CFG2_IR_ADJUST_HIGH              0x3F
/** \} */

/**
 * \defgroup interrupt_register Interrupt Registers
 * \{
 */ 
#define COLOR2_CFG3_NO_INT                      0x00
#define COLOR2_CFG3_G_INT                       0x01
#define COLOR2_CFG3_R_INT                       0x02
#define COLOR2_CFG3_B_INT                       0x03
#define COLOR2_CFG3_INT_PRST1                   0x00
#define COLOR2_CFG3_INT_PRST2                   0x04
#define COLOR2_CFG3_INT_PRST4                   0x08
#define COLOR2_CFG3_INT_PRST8                   0x0C
#define COLOR2_CFG3_RGB_CONV_TO_INT_DISABLE     0x00
#define COLOR2_CFG3_RGB_CONV_TO_INT_ENABLE      0x10
/** \} */

/**
 * \defgroup status_flag_masks STATUS FLAG MASKS
 * \{
 */
#define COLOR2_FLAG_INT                         0x01
#define COLOR2_FLAG_CONV_DONE                   0x02
#define COLOR2_FLAG_BROWNOUT                    0x04
#define COLOR2_FLAG_CONV_G                      0x10
#define COLOR2_FLAG_CONV_R                      0x20
#define COLOR2_FLAG_CONV_B                      0x30
/** \} */

/**
 * @brief Color 2 color flags.
 * @details Specified color flags of Color 2 Click driver.
 */
#define COLOR2_UNKNOWN_COLOR                    0
#define COLOR2_RED_COLOR                        1
#define COLOR2_YELLOW_COLOR                     2
#define COLOR2_GREEN_COLOR                      3
#define COLOR2_CYAN_COLOR                       4
#define COLOR2_BLUE_COLOR                       5
#define COLOR2_MAGENTA_COLOR                    6
#define COLOR2_WHITE_COLOR                      7
#define COLOR2_BLACK_COLOR                      8

/**
 * @brief Color 2 color from HSL thresholds.
 * @details Specified color from HSL thresholds of Color 2 Click driver.
 */
#define COLOR2_WHITE_COLOR_LIGHTNESS            97
#define COLOR2_BLACK_COLOR_LIGHTNESS            3
#define COLOR2_YELLOW_COLOR_HUE_ANGLE           30
#define COLOR2_GREEN_COLOR_HUE_ANGLE            90
#define COLOR2_CYAN_COLOR_HUE_ANGLE             150
#define COLOR2_BLUE_COLOR_HUE_ANGLE             210
#define COLOR2_MAGENTA_COLOR_HUE_ANGLE          270
#define COLOR2_RED_COLOR_HUE_ANGLE              330

/**
 * @brief Color 2 RGB to HSL calculation values.
 * @details Specified RGB to HSL calculation values of Color 2 Click driver.
 */
#define COLOR2_HSL_HUE_RESOLUTION               360
#define COLOR2_HSL_SATURATION_RESOLUTION        100
#define COLOR2_HSL_LIGHTNESS_RESOLUTION         100

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} color2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t int_pin;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} color2_cfg_t;

/**
 * @brief Color 2 RGB channels data object.
 * @details RGB channels data object of Color 2 Click driver.
 */
typedef struct
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;

} color2_rgb_t;

/**
 * @brief Color 2 HSL color data object.
 * @details HSL color data object of Color 2 Click driver.
 */
typedef struct
{
    float hue;
    float saturation;
    float lightness;

} color2_hsl_t;

/** \} */ // End types group

// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void color2_cfg_setup ( color2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param color2 Click object.
 * @param cfg Click configuration structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t color2_init ( color2_t *ctx, color2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function executes default configuration for Color2 click.
 */
err_t color2_default_cfg ( color2_t *ctx );

/**
 * @brief Color 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color2_generic_write ( color2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Color 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color2_generic_read ( color2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Generic write data function
 *
 * @param ctx             Click object.
 * @param reg             Register address
 * @param data_in         Command to write
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function write byte of data to ISL29125
 */
err_t color2_write_reg ( color2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Generic read data function
 *
 * @param ctx             Click object.
 * @param reg             Register address
 * @param data_out        Data from addressed register in ISL29125
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function read byte of data from register address of ISL29125
 */
err_t color2_read_reg ( color2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Get int pin function
 *
 * @param ctx             Click object.
 * @return Pin logic state.
 * @details Function read INT pin logic state
 */
uint8_t color2_get_int_pin ( color2_t *ctx );
 
/**
 * @brief Reset default register value function
 * @param ctx  Click object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Reset default register value function ISL29125
 */
err_t color2_reset ( color2_t *ctx );

/**
 * @brief Init advanced function
 * @param ctx             Click object.
 * @param config1         Register address config1
 * @param config2         Register address config2
 * @param config3         Register address config3
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function read byte of data from register address of ISL29125
 */
err_t color2_init_advanced ( color2_t *ctx, uint8_t config1, uint8_t config2, uint8_t config3 );

/**
 * @brief Function set upper threshold register
 * @param ctx                   Click object.
 * @param upper_threshold       Upper threshold
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function set upper threshold register of ISL29125
 */
err_t color2_set_upper_threshold ( color2_t *ctx, uint16_t upper_threshold );

/**
 * @brief Function set lower threshold register
 * @param ctx                   Click object.
 * @param lower_threshold       Lower threshold
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function set lower threshold register of ISL29125
 */
err_t color2_set_lower_hreshold ( color2_t *ctx, uint16_t lower_threshold );

/**
 * @brief Function read upper threshold register
 * @param ctx               Click object.
 * @param upper_threshold   Upper Threshold 16-bit data
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function read upper threshold register from ISL29125
 */
err_t color2_read_upper_threshold ( color2_t *ctx, uint16_t *upper_threshold );

/**
 * @brief Function read lower threshold register
 * @param ctx               Click object.
 * @param lower_threshold   Lower Threshold 16-bit data
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function read lower threshold register from ISL29125
 */
err_t color2_read_lower_threshold ( color2_t *ctx, uint16_t *lower_threshold );

/**
 * @brief Function read rgb data
 * @param ctx           Click object.
 * @param rgb           RGB data
 * See #color2_rgb_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function read red, green, and blue data from ISL29125
 */
err_t color2_read_rgb ( color2_t *ctx, color2_rgb_t *rgb );

/**
 * @brief Function read status registe value
 * @param ctx       Click object.
 * @param status    16-bit status data
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details Function read status registe value from ISL29125
 */
err_t color2_read_status ( color2_t *ctx, uint8_t *status );

/**
 * @brief Functions for read color value
 * @param ctx       Click object.
 * @param rgb :     RGB (red, green, blue) input value.
 * See #color2_rgb_t object definition for detailed explanation.
 * @param hsl :     HSL (hue, saturation, lightness) input value.
 * See #color2_hsl_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function converts RGB (red, green, blue) to HSL (hue, saturation, lightness) color value.
 */
void color2_rgb_to_hsl ( color2_t *ctx, color2_rgb_t *rgb, color2_hsl_t *hsl );

/**
 * @brief Functions for detect colors
 * @param ctx           Click object.
 * @param hsl :         HSL (hue, saturation, lightness) input value.
 * See #color2_hsl_t object definition for detailed explanation.
 * @return Color name flag.
 * See color flags macro definition for detailed explanation.
 * @details This function returns the color name flag from the input HSL color.
 */
uint8_t color2_get_color ( color2_hsl_t *hsl );

#ifdef __cplusplus
}
#endif
#endif  // _COLOR2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
