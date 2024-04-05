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
 * @file spectrometer2.h
 * @brief This file contains API for Spectrometer 2 Click Driver.
 */

#ifndef SPECTROMETER2_H
#define SPECTROMETER2_H

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
 * @addtogroup spectrometer2 Spectrometer 2 Click Driver
 * @brief API for configuring and manipulating Spectrometer 2 Click driver.
 * @{
 */

/**
 * @defgroup spectrometer2_reg Spectrometer 2 Registers List
 * @brief List of registers of Spectrometer 2 Click driver.
 */

/**
 * @addtogroup spectrometer2_reg
 * @{
 */

/**
 * @brief Spectrometer 2 register map.
 * @details Specified register map of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_REG_DEVICE_ID             0x00
#define SPECTROMETER2_REG_REVISION_ID           0x01
#define SPECTROMETER2_REG_INTERRUPT_CTRL        0x02
#define SPECTROMETER2_REG_ALS_CTRL              0x03
#define SPECTROMETER2_REG_ALS_PERIOD            0x04
#define SPECTROMETER2_REG_ALS_CH1_DATA_H        0x06
#define SPECTROMETER2_REG_ALS_CH1_DATA_M        0x07
#define SPECTROMETER2_REG_ALS_CH1_DATA_L        0x08
#define SPECTROMETER2_REG_ALS_CH2_DATA_H        0x0A
#define SPECTROMETER2_REG_ALS_CH2_DATA_M        0x0B
#define SPECTROMETER2_REG_ALS_CH2_DATA_L        0x0C
#define SPECTROMETER2_REG_ALS_CH3_DATA_H        0x0E
#define SPECTROMETER2_REG_ALS_CH3_DATA_M        0x0F
#define SPECTROMETER2_REG_ALS_CH3_DATA_L        0x10
#define SPECTROMETER2_REG_ALS_CH4_DATA_H        0x12
#define SPECTROMETER2_REG_ALS_CH4_DATA_M        0x13
#define SPECTROMETER2_REG_ALS_CH4_DATA_L        0x14
#define SPECTROMETER2_REG_ALS_CH5_DATA_H        0x16
#define SPECTROMETER2_REG_ALS_CH5_DATA_M        0x17
#define SPECTROMETER2_REG_ALS_CH5_DATA_L        0x18
#define SPECTROMETER2_REG_ALS_CH6_DATA_H        0x1A
#define SPECTROMETER2_REG_ALS_CH6_DATA_M        0x1B
#define SPECTROMETER2_REG_ALS_CH6_DATA_L        0x1C
#define SPECTROMETER2_REG_ALS_EXPOSURE_M        0x1D
#define SPECTROMETER2_REG_ALS_EXPOSURE_L        0x1E
#define SPECTROMETER2_REG_ALS_GAIN_CH1          0x25
#define SPECTROMETER2_REG_ALS_GAIN_CH2          0x26
#define SPECTROMETER2_REG_ALS_GAIN_CH3          0x27
#define SPECTROMETER2_REG_ALS_GAIN_CH4          0x28
#define SPECTROMETER2_REG_ALS_GAIN_CH5          0x29
#define SPECTROMETER2_REG_ALS_GAIN_CH6          0x2A
#define SPECTROMETER2_REG_CHANNEL6_ENABLE       0x2D
#define SPECTROMETER2_REG_ALS_CHANNEL_ENABLE    0x2E
#define SPECTROMETER2_REG_AC_MODE_CTRL          0x31
#define SPECTROMETER2_REG_PEDESTAL_VALUE        0x32
#define SPECTROMETER2_REG_SDA_DRV_CFG           0x3C
#define SPECTROMETER2_REG_GPIO1_DRV_CFG         0x41

/*! @} */ // spectrometer2_reg

/**
 * @defgroup spectrometer2_set Spectrometer 2 Registers Settings
 * @brief Settings for registers of Spectrometer 2 Click driver.
 */

/**
 * @addtogroup spectrometer2_set
 * @{
 */

/**
 * @brief Spectrometer 2 INTERRUPT_CTRL register settings.
 * @details Specified INTERRUPT_CTRL register settings of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_INTR_STATUS               0x02
#define SPECTROMETER2_CLR_INTR_SET              0x01
#define SPECTROMETER2_CLR_INTR_CLEAR            0x00

/**
 * @brief Spectrometer 2 ALS_EXPOSURE register settings.
 * @details Specified ALS_EXPOSURE register settings of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_EXPOSURE_TIME_MS_MAX      1638.4
#define SPECTROMETER2_EXPOSURE_TIME_MS_DEFAULT  160.0
#define SPECTROMETER2_EXPOSURE_TIME_MS_MIN      1.6
#define SPECTROMETER2_EXPOSURE_TIME_MS_LSB      1.6
#define SPECTROMETER2_EXPOSURE_TIME_RES         0x03FF

/**
 * @brief Spectrometer 2 ALS_PERIOD register settings.
 * @details Specified ALS_PERIOD register settings of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_IM_PERIOD_MS_MAX          5227.5
#define SPECTROMETER2_IM_PERIOD_MS_DEFAULT      200.0
#define SPECTROMETER2_IM_PERIOD_MS_MIN          0.0
#define SPECTROMETER2_IM_PERIOD_MS_LSB          20.5
#define SPECTROMETER2_IM_PERIOD_RES             0xFF

/**
 * @brief Spectrometer 2 ALS_GAIN_CHx register settings.
 * @details Specified ALS_GAIN_CHx register settings of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_AGAIN_66p6X               0x01
#define SPECTROMETER2_AGAIN_50X                 0x02
#define SPECTROMETER2_AGAIN_33X                 0x03
#define SPECTROMETER2_AGAIN_25X                 0x04
#define SPECTROMETER2_AGAIN_16X                 0x05
#define SPECTROMETER2_AGAIN_10X                 0x06
#define SPECTROMETER2_AGAIN_7p1X                0x07
#define SPECTROMETER2_AGAIN_5X                  0x08
#define SPECTROMETER2_AGAIN_3p33X               0x09
#define SPECTROMETER2_AGAIN_2p5X                0x0A
#define SPECTROMETER2_AGAIN_1p67X               0x0B
#define SPECTROMETER2_AGAIN_1p25X               0x0C
#define SPECTROMETER2_AGAIN_1X                  0x0D
#define SPECTROMETER2_AGAIN_0p83X               0x0E
#define SPECTROMETER2_AGAIN_0p71X               0x0F
#define SPECTROMETER2_AGAIN_BIT_MASK            0x0F

/**
 * @brief Spectrometer 2 CHANNEL6_ENABLE register settings.
 * @details Specified CHANNEL6_ENABLE register settings of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_CHANNEL6_DISABLE          0x00
#define SPECTROMETER2_CHANNEL6_ENABLE           0x01

/**
 * @brief Spectrometer 2 ALS_CHANNEL_ENABLE register settings.
 * @details Specified ALS_CHANNEL_ENABLE register settings of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_NO_CHANNEL_ENABLED        0x00
#define SPECTROMETER2_CHANNEL1_ENABLE           0x01
#define SPECTROMETER2_CHANNEL2_ENABLE           0x02
#define SPECTROMETER2_CHANNEL3_ENABLE           0x04
#define SPECTROMETER2_CHANNEL4_ENABLE           0x08
#define SPECTROMETER2_CHANNEL5_ENABLE           0x10
#define SPECTROMETER2_ALL_CHANNELS_ENABLE       0x1F

/**
 * @brief Spectrometer 2 ALS_CTRL register settings.
 * @details Specified ALS_CTRL register settings of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_ALS_MODE_SINGLE           0x00
#define SPECTROMETER2_ALS_MODE_CONTINUOUS       0x06
#define SPECTROMETER2_ALS_STOP                  0x00
#define SPECTROMETER2_ALS_START                 0x01

/**
 * @brief Spectrometer 2 color flags.
 * @details Specified color flags of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_UNKNOWN_COLOR             0
#define SPECTROMETER2_RED_COLOR                 1
#define SPECTROMETER2_YELLOW_COLOR              2
#define SPECTROMETER2_GREEN_COLOR               3
#define SPECTROMETER2_CYAN_COLOR                4
#define SPECTROMETER2_BLUE_COLOR                5
#define SPECTROMETER2_MAGENTA_COLOR             6
#define SPECTROMETER2_WHITE_COLOR               7
#define SPECTROMETER2_BLACK_COLOR               8

/**
 * @brief Spectrometer 2 color from HSL thresholds.
 * @details Specified color from HSL thresholds of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_WHITE_COLOR_LIGHTNESS     95
#define SPECTROMETER2_BLACK_COLOR_LIGHTNESS     5
#define SPECTROMETER2_YELLOW_COLOR_HUE_ANGLE    30
#define SPECTROMETER2_GREEN_COLOR_HUE_ANGLE     90
#define SPECTROMETER2_CYAN_COLOR_HUE_ANGLE      150
#define SPECTROMETER2_BLUE_COLOR_HUE_ANGLE      210
#define SPECTROMETER2_MAGENTA_COLOR_HUE_ANGLE   270
#define SPECTROMETER2_RED_COLOR_HUE_ANGLE       330

/**
 * @brief Spectrometer 2 RGB to HSL calculation values.
 * @details Specified RGB to HSL calculation values of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_HSL_HUE_RESOLUTION        360
#define SPECTROMETER2_HSL_SATURATION_RESOLUTION 100
#define SPECTROMETER2_HSL_LIGHTNESS_RESOLUTION  100

/**
 * @brief Spectrometer 2 device ID value.
 * @details Specified device ID value of Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_DEVICE_ID                 0x70

/**
 * @brief Spectrometer 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Spectrometer 2 Click driver.
 */
#define SPECTROMETER2_DEVICE_ADDRESS            0x20

/*! @} */ // spectrometer2_set

/**
 * @defgroup spectrometer2_map Spectrometer 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Spectrometer 2 Click driver.
 */

/**
 * @addtogroup spectrometer2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Spectrometer 2 Click to the selected MikroBUS.
 */
#define SPECTROMETER2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // spectrometer2_map
/*! @} */ // spectrometer2

/**
 * @brief Spectrometer 2 Click context object.
 * @details Context object definition of Spectrometer 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  an;           /**< AC flicker signal (PDM data) pin. */
    digital_in_t  int_pin;      /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} spectrometer2_t;

/**
 * @brief Spectrometer 2 Click configuration object.
 * @details Configuration object definition of Spectrometer 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  an;             /**< AC flicker signal (PDM data) pin. */
    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} spectrometer2_cfg_t;

/**
 * @brief Spectrometer 2 ALS channels data object.
 * @details ALS channels data object of Spectrometer 2 Click driver.
 */
typedef struct
{
    uint32_t red;
    uint32_t visible;
    uint32_t blue;
    uint32_t green;
    uint32_t ir;
    uint32_t clear;

} spectrometer2_als_channels_t;

/**
 * @brief Spectrometer 2 HSL color data object.
 * @details HSL color data object of Spectrometer 2 Click driver.
 */
typedef struct
{
    float hue;
    float saturation;
    float lightness;

} spectrometer2_hsl_t;

/**
 * @brief Spectrometer 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SPECTROMETER2_OK = 0,
    SPECTROMETER2_ERROR = -1

} spectrometer2_return_value_t;

/*!
 * @addtogroup spectrometer2 Spectrometer 2 Click Driver
 * @brief API for configuring and manipulating Spectrometer 2 Click driver.
 * @{
 */

/**
 * @brief Spectrometer 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spectrometer2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spectrometer2_cfg_setup ( spectrometer2_cfg_t *cfg );

/**
 * @brief Spectrometer 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spectrometer2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_init ( spectrometer2_t *ctx, spectrometer2_cfg_t *cfg );

/**
 * @brief Spectrometer 2 default configuration function.
 * @details This function executes a default configuration of Spectrometer 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t spectrometer2_default_cfg ( spectrometer2_t *ctx );

/**
 * @brief Spectrometer 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_generic_write ( spectrometer2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Spectrometer 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_generic_read ( spectrometer2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Spectrometer 2 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_write_register ( spectrometer2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Spectrometer 2 read register function.
 * @details This function reads a desired data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_read_register ( spectrometer2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Spectrometer 2 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_check_communication ( spectrometer2_t *ctx );

/**
 * @brief Spectrometer 2 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t spectrometer2_get_int_pin ( spectrometer2_t *ctx );

/**
 * @brief Spectrometer 2 get an pin function.
 * @details This function returns the AN pin logic state.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t spectrometer2_get_an_pin ( spectrometer2_t *ctx );

/**
 * @brief Spectrometer 2 get data function.
 * @details This function reads data from 6 ALS channels (Red, Visible, Blue, Green, IR, Clear).
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @param[out] als_channels : ALS channels (Red, Visible, Blue, Green, IR, Clear).
 * See #spectrometer2_als_channels_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_get_data ( spectrometer2_t *ctx, spectrometer2_als_channels_t *als_channels );

/**
 * @brief Spectrometer 2 clear interrupt function.
 * @details This function clears the interrupts by writing to the INTERRUPT_CTRL register.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_clear_interrupt ( spectrometer2_t *ctx );

/**
 * @brief Spectrometer 2 set exposure time function.
 * @details This function sets the exposure time.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @param[in] exp_time : Exposure time in milliseconds [1.6-1638.4].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_set_exposure_time ( spectrometer2_t *ctx, float exp_time );

/**
 * @brief Spectrometer 2 set inter measurement period function.
 * @details This function sets the inter measurement period.
 * @param[in] ctx : Click context object.
 * See #spectrometer2_t object definition for detailed explanation.
 * @param[in] im_period : Inter measurement period in milliseconds [0.0-5227.5].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spectrometer2_set_inter_measurement_period ( spectrometer2_t *ctx, float im_period );

/**
 * @brief Spectrometer 2 get color function.
 * @details This function returns the color name flag from the input HSL color.
 * @param[out] hsl : HSL (hue, saturation, lightness) input value.
 * See #spectrometer2_hsl_t object definition for detailed explanation.
 * @return Color name flag.
 * See color flags macro definition for detailed explanation.
 * @note None.
 */
uint8_t spectrometer2_get_color ( spectrometer2_hsl_t *hsl );

/**
 * @brief Spectrometer 2 rgbc to hsl function.
 * @details This function converts RGBC (red, green, blue, clear) to HSL (hue, saturation, lightness) color value.
 * @param[out] rgbc : RGBC (red, green, blue, clear) input value.
 * See #spectrometer2_als_channels_t object definition for detailed explanation.
 * @param[out] hsl : HSL (hue, saturation, lightness) input value.
 * See #spectrometer2_hsl_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void spectrometer2_rgbc_to_hsl ( spectrometer2_als_channels_t *rgbc, spectrometer2_hsl_t *hsl );

#ifdef __cplusplus
}
#endif
#endif // SPECTROMETER2_H

/*! @} */ // spectrometer2

// ------------------------------------------------------------------------ END
