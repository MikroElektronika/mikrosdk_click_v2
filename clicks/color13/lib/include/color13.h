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
 * @file color13.h
 * @brief This file contains API for Color 13 Click Driver.
 */

#ifndef COLOR13_H
#define COLOR13_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup color13 Color 13 Click Driver
 * @brief API for configuring and manipulating Color 13 Click driver.
 * @{
 */

/**
 * @defgroup color13_reg Color 13 Registers List
 * @brief List of registers of Color 13 Click driver.
 */

/**
 * @addtogroup color13_reg
 * @{
 */

/**
 * @brief Color 13 description register.
 * @details Specified register for description of Color 13 Click driver.
 */
#define COLOR13_REG_MAIN_CTRL       0x00
#define COLOR13_REG_PS_VCSEL        0x01
#define COLOR13_REG_PS_PULSES       0x02
#define COLOR13_REG_PS_MEASRATE     0x03
#define COLOR13_REG_LS_MEAS_RATE    0x04
#define COLOR13_REG_LS_GAIN         0x05
#define COLOR13_REG_PART_ID         0x06
#define COLOR13_REG_MAIN_STATUS     0x07
#define COLOR13_REG_PS_DATA_0       0x08
#define COLOR13_REG_PS_DATA_1       0x09
#define COLOR13_REG_LS_DATA_IR_0    0x0A
#define COLOR13_REG_LS_DATA_IR_1    0x0B
#define COLOR13_REG_LS_DATA_IR_2    0x0C
#define COLOR13_REG_LS_DATA_GREEN_0 0x0D
#define COLOR13_REG_LS_DATA_GREEN_1 0x0E
#define COLOR13_REG_LS_DATA_GREEN_2 0x0F
#define COLOR13_REG_LS_DATA_BLUE_0  0x10
#define COLOR13_REG_LS_DATA_BLUE_1  0x11
#define COLOR13_REG_LS_DATA_BLUE_2  0x12
#define COLOR13_REG_LS_DATA_RED_0   0x13
#define COLOR13_REG_LS_DATA_RED_1   0x14
#define COLOR13_REG_LS_DATA_RED_2   0x15
#define COLOR13_REG_INT_CFG         0x19        
#define COLOR13_REG_INT_PST         0x1A
#define COLOR13_REG_PS_THRES_UP_0   0x1B
#define COLOR13_REG_PS_THRES_UP_1   0x1C
#define COLOR13_REG_PS_THRES_LOW_0  0x1D
#define COLOR13_REG_PS_THRES_LOW_1  0x1E
#define COLOR13_REG_PS_CAN_0        0x1F
#define COLOR13_REG_PS_CAN_1_ANA    0x20
#define COLOR13_REG_LS_THRES_UP_0   0x21
#define COLOR13_REG_LS_THRES_UP_1   0x22
#define COLOR13_REG_LS_THRES_UP_2   0x23
#define COLOR13_REG_LS_THRES_LOW_0  0x24
#define COLOR13_REG_LS_THRES_LOW_1  0x25
#define COLOR13_REG_LS_THRES_LOW_2  0x26
#define COLOR13_REG_LS_THRES_VAR    0x27

/*! @} */ // color13_reg

/**
 * @defgroup color13_set Color 13 Registers Settings
 * @brief Settings for registers of Color 13 Click driver.
 */

/**
 * @addtogroup color13_set
 * @{
 */

/**
 * @brief Color 13 device ID data.
 * @details Specified data for device ID of Color 13 Click.
 */
#define COLOR13_ID 0xC2


/**
 * @brief Color 13 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 13 Click driver.
 */
#define COLOR13_SET_DEV_ADDR  0x52

/*! @} */ // color13_set

/**
 * @defgroup color13_map Color 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 13 Click driver.
 */

/**
 * @addtogroup color13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 13 Click to the selected MikroBUS.
 */
#define COLOR13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color13_map
/*! @} */ // color13

/**
 * @brief Color 13 Click context object.
 * @details Context object definition of Color 13 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;  /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    
    // ALS resolution
    float lux_resolution;

} color13_t;

/**
 * @brief Color 13 Click configuration object.
 * @details Configuration object definition of Color 13 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} color13_cfg_t;

/**
 * @brief Color 13 color data object.
 * @details Color data object of Color 13 Click driver.
 */
typedef struct
{
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    uint32_t ir;

} color13_color_t;

/**
 * @brief Color 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   COLOR13_OK = 0,
   COLOR13_ERROR = -1,
   COLOR13_ERROR_OVF = -2,
   COLOR13_ERROR_PARAM = -3,
   COLOR13_ERROR_CFG = -4

} color13_return_value_t;

/*!
 * @addtogroup color13 Color 13 Click Driver
 * @brief API for configuring and manipulating Color 13 Click driver.
 * @{
 */

/**
 * @brief Color 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color13_cfg_setup ( color13_cfg_t *cfg );

/**
 * @brief Color 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #color13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t color13_init ( color13_t *ctx, color13_cfg_t *cfg );

/**
 * @brief Color 13 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t color13_generic_write ( color13_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Color 13 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t color13_generic_read ( color13_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Get interrupt pin state.
 * @details Read @b int_pin state.
 * @param[in] ctx : Click context object.
 * See #color13_t object definition for detailed explanation.
 * @return Interrupt state.
 */
uint8_t color13_get_int ( color13_t *ctx );

/**
 * @brief Read proximity data from device.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color13_t object definition for detailed explanation.
 * @param[out] ps_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Overflow,
 *         @li @c -4 - Error configuration.
 *
 * See #err_t definition for detailed explanation.
 * @note Device should be configured for proximity reading before calling 
 * this function. Bit @b PS_EN should be 1, of the @b MAIN_CTRL register.
 */
err_t color13_get_proximity ( color13_t *ctx, uint16_t *ps_data );

/**
 * @brief Read lux data from device.
 * @details This function reads adc data and calculates lux data from device.
 * @param[in] ctx : Click context object.
 * See #color13_t object definition for detailed explanation.
 * @param[out] als_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The device should be configured for ALS reading before calling 
 * this function. Bit @b RGB_MODE should be 0 and @b LS_EN should be
 * 1, of the @b MAIN_CTRL register. The function will call function 
 * @b color13_get_als_resolution on it's first iteration for calculating
 * lux data for its configuration. If you change the configuration of the device
 * After calling this function once you need to call @b color13_get_als_resolution 
 * separately to set @b lux_resolution in the context object for getting current 
 * calculation of lux data.
 */
err_t color13_get_als ( color13_t *ctx, float *als_data );

/**
 * @brief Read ls data from color registers.
 * @details This function reads data from reg, green, 
 * blue or ir registers and returns data to @b ls_data.
 * @param[in] ctx : Click context object.
 * See #color13_t object definition for detailed explanation.
 * @param[in] ls_reg : LSB register address of data.
 * @param[out] ls_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -3 - Error Parameter.
 *
 * See #err_t definition for detailed explanation.
 * @note The device should be configured to enable LS reading before calling 
 * this function. You can configure it by setting @b LS_EN bit of the @b MAIN_CTRL 
 * register. Depending of the reading you want to use you can configure @b RGB_MODE 
 * bit to 0 if you want ALS data from @b COLOR13_REG_LS_DATA_GREEN_0 register or 
 * to 1 if you want RGB data from LS registers.
 */
err_t color13_ls_color ( color13_t *ctx, uint8_t ls_reg, uint32_t *ls_data );

/**
 * @brief Read color data from device.
 * @details This function reads red, green, blue, and ir registers 
 * data and sets data in @b color_data object.
 * @param[in] ctx : Click context object.
 * See #color13_t object definition for detailed explanation.
 * @param[out] color_data : Color data object.
 * See #color13_color_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The device should be configured for RGB reading before calling 
 * this function. Bits @b RGB_MODE and @b LS_EN, of the @b MAIN_CTRL 
 * register, should be set to 1.
 */
err_t color13_get_rgb_ir ( color13_t *ctx, color13_color_t *color_data );

/**
 * @brief Get resolution for the lux calculation.
 * @details Function reads configuration from device and returns corresponding 
 * lux resolution, and sets member @b lux_resolution of context object.
 * @param[in,out] ctx : Click context object.
 * See #color13_t object definition for detailed explanation.
 * @param[out] ps_data : Output read data.
 * @return Resolution for the current configuration of als data.
 */
float color13_get_als_resolution ( color13_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // COLOR13_H

/*! @} */ // color13

// ------------------------------------------------------------------------ END
