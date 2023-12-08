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
 * @file color15.h
 * @brief This file contains API for Color 15 Click Driver.
 */

#ifndef COLOR15_H
#define COLOR15_H

#ifdef __cplusplus
extern "C"{
#endif

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

/*!
 * @addtogroup color15 Color 15 Click Driver
 * @brief API for configuring and manipulating Color 15 Click driver.
 * @{
 */

/**
 * @defgroup color15_reg Color 15 Registers List
 * @brief List of registers of Color 15 Click driver.
 */

/**
 * @addtogroup color15_reg
 * @{
 */

/**
 * @brief Color 15 register map.
 * @details Specified register map of Color 15 Click driver.
 */
#define COLOR15_REG_SYSM_CTRL               0x00
#define COLOR15_REG_INT_CTRL                0x01
#define COLOR15_REG_INT_FLAG                0x02
#define COLOR15_REG_WAIT_TIME               0x03
#define COLOR15_REG_CLS_GAIN                0x04
#define COLOR15_REG_CLS_TIME                0x05
#define COLOR15_REG_PERSISTENCE             0x0B
#define COLOR15_REG_CLS_THRES_LL            0x0C
#define COLOR15_REG_CLS_THRES_LH            0x0D
#define COLOR15_REG_CLS_THRES_HL            0x0E
#define COLOR15_REG_CLS_THRES_HH            0x0F
#define COLOR15_REG_INT_SOURCE              0x16
#define COLOR15_REG_ERROR_FLAG              0x17
#define COLOR15_REG_RCH_DATA_L              0x1C
#define COLOR15_REG_RCH_DATA_H              0x1D
#define COLOR15_REG_GCH_DATA_L              0x1E
#define COLOR15_REG_GCH_DATA_H              0x1F
#define COLOR15_REG_BCH_DATA_L              0x20
#define COLOR15_REG_BCH_DATA_H              0x21
#define COLOR15_REG_WCH_DATA_L              0x22
#define COLOR15_REG_WCH_DATA_H              0x23
#define COLOR15_REG_IRCH_DATA_L             0x24
#define COLOR15_REG_IRCH_DATA_H             0x25
#define COLOR15_REG_PROD_ID_L               0xBC
#define COLOR15_REG_PROD_ID_H               0xBD

/*! @} */ // color15_reg

/**
 * @defgroup color15_set Color 15 Registers Settings
 * @brief Settings for registers of Color 15 Click driver.
 */

/**
 * @addtogroup color15_set
 * @{
 */

/**
 * @brief Color 15 SYSM_CTRL register settings.
 * @details Specified SYSM_CTRL register settings of Color 15 Click driver.
 */
#define COLOR15_SYSM_CTRL_SWRST             0x80
#define COLOR15_SYSM_CTRL_EN_WAIT           0x40
#define COLOR15_SYSM_CTRL_EN_IR             0x02
#define COLOR15_SYSM_CTRL_EN_CLS            0x01

/**
 * @brief Color 15 INT_CTRL register settings.
 * @details Specified INT_CTRL register settings of Color 15 Click driver.
 */
#define COLOR15_INT_CTRL_CLS_SYNC           0x10
#define COLOR15_INT_CTRL_EN_CINT            0x01

/**
 * @brief Color 15 INT_FLAG register settings.
 * @details Specified INT_FLAG register settings of Color 15 Click driver.
 */
#define COLOR15_INT_FLAG_POR                0x80
#define COLOR15_INT_FLAG_DATA_FLAG          0x40
#define COLOR15_INT_FLAG_CLS                0x01
#define COLOR15_INT_FLAG_CLEAR_ALL          0x00

/**
 * @brief Color 15 WAIT_TIME register settings.
 * @details Specified WAIT_TIME register settings of Color 15 Click driver.
 */
#define COLOR15_WAIT_TIME_MS_MAX            2560
#define COLOR15_WAIT_TIME_MS_DEFAULT        100
#define COLOR15_WAIT_TIME_MS_MIN            10
#define COLOR15_WAIT_TIME_MS_LSB            10
#define COLOR15_WAIT_TIME_RES               0xFF

/**
 * @brief Color 15 CLS_TIME register settings.
 * @details Specified CLS_TIME register settings of Color 15 Click driver.
 */
#define COLOR15_CLSCONV_1                   0x00
#define COLOR15_CLSCONV_2                   0x01
#define COLOR15_CLSCONV_3                   0x02
#define COLOR15_CLSCONV_4                   0x03
#define COLOR15_CLSCONV_5                   0x04
#define COLOR15_CLSCONV_6                   0x05
#define COLOR15_CLSCONV_7                   0x06
#define COLOR15_CLSCONV_8                   0x07
#define COLOR15_CLSCONV_9                   0x08
#define COLOR15_CLSCONV_10                  0x09
#define COLOR15_CLSCONV_11                  0x0A
#define COLOR15_CLSCONV_12                  0x0B
#define COLOR15_CLSCONV_13                  0x0C
#define COLOR15_CLSCONV_14                  0x0D
#define COLOR15_CLSCONV_15                  0x0E
#define COLOR15_INT_TIME_1                  0x00
#define COLOR15_INT_TIME_4                  0x01
#define COLOR15_INT_TIME_16                 0x02
#define COLOR15_INT_TIME_64                 0x03
#define COLOR15_MAX_COUNT_LSB               1024
#define COLOR15_MAX_COUNT_RES               0xFFFF

/**
 * @brief Color 15 CLS_GAIN register settings.
 * @details Specified CLS_GAIN register settings of Color 15 Click driver.
 */
#define COLOR15_CLS_GAIN_DIOD_SELT_X1       0x00
#define COLOR15_CLS_GAIN_DIOD_SELT_X2       0x80
#define COLOR15_CLS_GAIN_PGA_CLS_X1         0x01
#define COLOR15_CLS_GAIN_PGA_CLS_X4         0x02
#define COLOR15_CLS_GAIN_PGA_CLS_X8         0x04
#define COLOR15_CLS_GAIN_PGA_CLS_X32        0x08
#define COLOR15_CLS_GAIN_PGA_CLS_X96        0x10

/**
 * @brief Color 15 PERSISTANCE register settings.
 * @details Specified PERSISTANCE register settings of Color 15 Click driver.
 */
#define COLOR15_PRS_CLS_INDEPENDENT         0x00
#define COLOR15_PRS_CLS_1_CLS               0x01
#define COLOR15_PRS_CLS_2_CLS               0x02
#define COLOR15_PRS_CLS_3_CLS               0x03
#define COLOR15_PRS_CLS_4_CLS               0x04
#define COLOR15_PRS_CLS_5_CLS               0x05
#define COLOR15_PRS_CLS_6_CLS               0x06
#define COLOR15_PRS_CLS_7_CLS               0x07
#define COLOR15_PRS_CLS_8_CLS               0x08
#define COLOR15_PRS_CLS_9_CLS               0x09
#define COLOR15_PRS_CLS_10_CLS              0x0A
#define COLOR15_PRS_CLS_11_CLS              0x0B
#define COLOR15_PRS_CLS_12_CLS              0x0C
#define COLOR15_PRS_CLS_13_CLS              0x0D
#define COLOR15_PRS_CLS_14_CLS              0x0E
#define COLOR15_PRS_CLS_15_CLS              0x0F

/**
 * @brief Color 15 INT_SOURCE register settings.
 * @details Specified INT_SOURCE register settings of Color 15 Click driver.
 */
#define COLOR15_INT_SRC_RCH_DATA            0x01
#define COLOR15_INT_SRC_GCH_DATA            0x02
#define COLOR15_INT_SRC_BCH_DATA            0x04
#define COLOR15_INT_SRC_WCH_DATA            0x08
#define COLOR15_INT_SRC_IRCH_DATA           0x10

/**
 * @brief Color 15 color flags.
 * @details Specified color flags of Color 15 Click driver.
 */
#define COLOR15_UNKNOWN_COLOR               0
#define COLOR15_RED_COLOR                   1
#define COLOR15_YELLOW_COLOR                2
#define COLOR15_GREEN_COLOR                 3
#define COLOR15_CYAN_COLOR                  4
#define COLOR15_BLUE_COLOR                  5
#define COLOR15_MAGENTA_COLOR               6
#define COLOR15_WHITE_COLOR                 7
#define COLOR15_BLACK_COLOR                 8

/**
 * @brief Color 15 color from HSL thresholds.
 * @details Specified color from HSL thresholds of Color 15 Click driver.
 */
#define COLOR15_WHITE_COLOR_LIGHTNESS       97
#define COLOR15_BLACK_COLOR_LIGHTNESS       3
#define COLOR15_YELLOW_COLOR_HUE_ANGLE      30
#define COLOR15_GREEN_COLOR_HUE_ANGLE       90
#define COLOR15_CYAN_COLOR_HUE_ANGLE        150
#define COLOR15_BLUE_COLOR_HUE_ANGLE        210
#define COLOR15_MAGENTA_COLOR_HUE_ANGLE     270
#define COLOR15_RED_COLOR_HUE_ANGLE         330

/**
 * @brief Color 15 RGB to HSL calculation values.
 * @details Specified RGB to HSL calculation values of Color 15 Click driver.
 */
#define COLOR15_HSL_HUE_RESOLUTION          360
#define COLOR15_HSL_SATURATION_RESOLUTION   100
#define COLOR15_HSL_LIGHTNESS_RESOLUTION    100

/**
 * @brief Color 15 product ID values.
 * @details Specified product ID values of Color 15 Click driver.
 */
#define COLOR15_PRODUCT_ID_LSB              0x12
#define COLOR15_PRODUCT_ID_MSB              0x07

/**
 * @brief Color 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 15 Click driver.
 */
#define COLOR15_DEVICE_ADDRESS              0x38

/*! @} */ // color15_set

/**
 * @defgroup color15_map Color 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 15 Click driver.
 */

/**
 * @addtogroup color15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 15 Click to the selected MikroBUS.
 */
#define COLOR15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color15_map
/*! @} */ // color15

/**
 * @brief Color 15 Click context object.
 * @details Context object definition of Color 15 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    
    uint16_t resolution;            /**< Output data resolution. */

} color15_t;

/**
 * @brief Color 15 Click configuration object.
 * @details Configuration object definition of Color 15 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;            /**< Interrupt pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} color15_cfg_t;

/**
 * @brief Color 15 RGBWIR channels data object.
 * @details RGBWIR channels data object of Color 15 Click driver.
 */
typedef struct
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t white;
    uint16_t ir;

} color15_channels_t;

/**
 * @brief Color 15 HSL color data object.
 * @details HSL color data object of Color 15 Click driver.
 */
typedef struct
{
    float hue;
    float saturation;
    float lightness;

} color15_hsl_t;

/**
 * @brief Color 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COLOR15_OK = 0,
    COLOR15_ERROR = -1

} color15_return_value_t;

/*!
 * @addtogroup color15 Color 15 Click Driver
 * @brief API for configuring and manipulating Color 15 Click driver.
 * @{
 */

/**
 * @brief Color 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color15_cfg_setup ( color15_cfg_t *cfg );

/**
 * @brief Color 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color15_init ( color15_t *ctx, color15_cfg_t *cfg );

/**
 * @brief Color 15 default configuration function.
 * @details This function executes a default configuration of Color 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t color15_default_cfg ( color15_t *ctx );

/**
 * @brief Color 15 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color15_generic_write ( color15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Color 15 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color15_generic_read ( color15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Color 15 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color15_write_register ( color15_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Color 15 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color15_read_register ( color15_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Color 15 check communication function.
 * @details This function checks the communication by reading and verifying the product ID.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color15_check_communication ( color15_t *ctx );

/**
 * @brief Color 15 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t color15_get_int_pin ( color15_t *ctx );

/**
 * @brief Color 15 clear interrupt function.
 * @details This function clears all interrupt flags from INT_FLAG register.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color15_clear_interrupt ( color15_t *ctx );

/**
 * @brief Color 15 set wait time function.
 * @details This function sets the wait time.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @param[in] wait_time : Wait time in milliseconds [10-2560].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait time feature needs to be enabled in the SYSM_CTRL register.
 */
err_t color15_set_wait_time ( color15_t *ctx, uint16_t wait_time );

/**
 * @brief Color 15 set cls time function.
 * @details This function sets the cls time and output data resolution in @b ctx->resolution.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @param[in] clsconv : CLSCONV bits settings [0x00-0x0F].
 * @param[in] int_time : INT_TIME bits settings [0x00-0x03].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note CLS TIME = CLSCONV * INT_TIME * 2.0667 ms.
 */
err_t color15_set_cls_time ( color15_t *ctx, uint8_t clsconv, uint8_t int_time );

/**
 * @brief Color 15 get data function.
 * @details This function reads data from 5 channels (Red, Green, Blue, White, IR).
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @param[out] channels : Channels output (Red, Green, Blue, White, IR).
 * See #color15_channels_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color15_get_data ( color15_t *ctx, color15_channels_t *channels );

/**
 * @brief Color 15 get color function.
 * @details This function returns the color name flag from the input HSL color.
 * @param[out] hsl : HSL (hue, saturation, lightness) input value.
 * See #color15_hsl_t object definition for detailed explanation.
 * @return Color name flag.
 * See color flags macro definition for detailed explanation.
 * @note None.
 */
uint8_t color15_get_color ( color15_hsl_t *hsl );

/**
 * @brief Color 15 rgbw to hsl function.
 * @details This function converts RGBW (red, green, blue, white) to HSL (hue, saturation, lightness) color value.
 * @param[in] ctx : Click context object.
 * See #color15_t object definition for detailed explanation.
 * @param[out] rgbw : RGBW (red, green, blue, white) input value.
 * See #color15_channels_t object definition for detailed explanation.
 * @param[out] hsl : HSL (hue, saturation, lightness) input value.
 * See #color15_hsl_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void color15_rgbw_to_hsl ( color15_t *ctx, color15_channels_t *rgbw, color15_hsl_t *hsl );

#ifdef __cplusplus
}
#endif
#endif // COLOR15_H

/*! @} */ // color15

// ------------------------------------------------------------------------ END
