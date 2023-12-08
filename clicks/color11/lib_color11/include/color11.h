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
 * @file color11.h
 * @brief This file contains API for Color 11 Click Driver.
 */

#ifndef COLOR11_H
#define COLOR11_H

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
 * @addtogroup color11 Color 11 Click Driver
 * @brief API for configuring and manipulating Color 11 Click driver.
 * @{
 */

/**
 * @defgroup color11_reg Color 11 Registers List
 * @brief List of registers of Color 11 Click driver.
 */

/**
 * @addtogroup color11_reg
 * @{
 */

/**
 * @brief Color 11 description register.
 * @details Specified register for description of Color 11 Click driver.
 */
#define COLOR11_REG_RAM_START             0x00
#define COLOR11_REG_ENABLE                0x80
#define COLOR11_REG_ATIME                 0x81
#define COLOR11_REG_PTIME                 0x82
#define COLOR11_REG_WTIME                 0x83
#define COLOR11_REG_AILTL                 0x84
#define COLOR11_REG_AILTH                 0x85
#define COLOR11_REG_AIHTL                 0x86
#define COLOR11_REG_AIHTH                 0x87
#define COLOR11_REG_AUXID                 0x90
#define COLOR11_REG_REVID                 0x91
#define COLOR11_REG_ID                    0x92
#define COLOR11_REG_STATUS                0x93
#define COLOR11_REG_ASTATUS               0x94
#define COLOR11_REG_ADATAL0               0x95
#define COLOR11_REG_ADATAH0               0x96
#define COLOR11_REG_ADATAL1               0x97
#define COLOR11_REG_ADATAH1               0x98
#define COLOR11_REG_ADATAL2               0x99
#define COLOR11_REG_ADATAH2               0x9A
#define COLOR11_REG_ADATAL3               0x9B
#define COLOR11_REG_ADATAH3               0x9C
#define COLOR11_REG_ADATAL4               0x9D
#define COLOR11_REG_ADATAH4               0x9E
#define COLOR11_REG_ADATAL5               0x9F
#define COLOR11_REG_ADATAH5               0xA0
#define COLOR11_REG_STATUS2               0xA3
#define COLOR11_REG_STATUS3               0xA4
#define COLOR11_REG_STATUS5               0xA6
#define COLOR11_REG_STATUS6               0xA7
#define COLOR11_REG_CFG0                  0xA9
#define COLOR11_REG_CFG1                  0xAA
#define COLOR11_REG_CFG3                  0xAC
#define COLOR11_REG_CFG4                  0xAD
#define COLOR11_REG_CFG6                  0xAF
#define COLOR11_REG_CFG8                  0xB1
#define COLOR11_REG_CFG9                  0xB2
#define COLOR11_REG_CFG10                 0xB3
#define COLOR11_REG_CFG11                 0xB4
#define COLOR11_REG_CFG12                 0xB5
#define COLOR11_REG_PERS                  0xBD
#define COLOR11_REG_POFFSETH              0xC8
#define COLOR11_REG_ASTEPL                0xCA
#define COLOR11_REG_ASTEPH                0xCB
#define COLOR11_REG_AGC_GAIN_MAX          0xCF
#define COLOR11_REG_AZCONFIG              0xD6
#define COLOR11_REG_FD_STATUS             0xDB
#define COLOR11_REG_INTENAB               0xF9
#define COLOR11_REG_CONTROL               0xFA

/*! @} */ // color11_reg

/**
 * @defgroup color11_set Color 11 Registers Settings
 * @brief Settings for registers of Color 11 Click driver.
 */

/**
 * @addtogroup color11_set
 * @{
 */

/**
 * @brief Color 11 identification data values.
 * @details Specified identification data values of Color 11 Click driver.
 */
#define COLOR11_ID_AUX                    0x4A
#define COLOR11_ID_REV                    0x53
#define COLOR11_ID_DEV                    0x18

/**
 * @brief Color 11 ALS default configuration values.
 * @details Specified ALS default configuration values of Color 11 Click driver.
 */
#define COLOR11_ALS_INTEG_TIME_DEFAULT    19000
#define COLOR11_ALS_STEP_DEFAULT          2780
#define COLOR11_ALS_THOLD_LOW_DEFAULT     0x0000u
#define COLOR11_ALS_THOLD_HIGH_DEFAULT    0xFFFFu

/**
 * @brief Color 11 interrupt enable bit mask values.
 * @details Specified interrupt enable bit mask values of Color 11 Click driver.
 */
#define COLOR11_SET_INTENAB_ASI_DIS       0x00
#define COLOR11_SET_INTENAB_ASI_EN        0x80
#define COLOR11_SET_INTENAB_AI_DIS        0x00
#define COLOR11_SET_INTENAB_AI_EN         0x08
#define COLOR11_SET_INTENAB_SI_DIS        0x00
#define COLOR11_SET_INTENAB_SI_EN         0x01

/**
 * @brief Color 11 valid status bit mask.
 * @details Specified valid status bit mask of Color 11 Click driver.
 */
#define COLOR11_STATUS2_AVALID             0x40
#define COLOR11_STATUS2_ASAT_DIGITAL       0x10
#define COLOR11_STATUS2_ASAT_ANALOG        0x08
#define COLOR11_STATUS2_FDSAT_ANALOG       0x02
#define COLOR11_STATUS2_FDSAT_DIGITAL      0x01

/**
 * @brief Color 11 step calculation values.
 * @details Specified step calculation values of Color 11 Click driver.
 */
#define COLOR11_ALS_STEP_CONV_TO_US       100
#define COLOR11_ALS_STEP_MIN_ASTEP        278
#define COLOR11_ALS_STEP_COR_FACT         50

/**
 * @brief Color 11 default coefficient values.
 * @details Specified default coefficient values of Color 11 Click driver.
 */
#define COLOR11_COEF_SCALE_DEFAULT        1000.0f
#define COLOR11_COEF_DGF_DEFAULT          898.0f
#define COLOR11_COEF_CLR_DEFAULT          210.0f
#define COLOR11_COEF_RED_DEFAULT         -60.0f
#define COLOR11_COEF_GREEN_DEFAULT        10.0f
#define COLOR11_COEF_BLUE_DEFAULT        -290.0f

/**
 * @brief Color 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 11 Click driver.
 */
#define COLOR11_DEVICE_ADDRESS            0x39

/*! @} */ // color11_set

/**
 * @defgroup color11_map Color 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 11 Click driver.
 */

/**
 * @addtogroup color11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 11 Click to the selected MikroBUS.
 */
#define COLOR11_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color11_map
/*! @} */ // color11

/**
 * @brief Color 11 Click context object.
 * @details Context object definition of Color 11 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} color11_t;

/**
 * @brief Color 11 Click configuration object.
 * @details Configuration object definition of Color 11 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} color11_cfg_t;

/**
 * @brief Color 11 Click ALS data object.
 * @details ALS data object definition of Color 11 Click driver.
 */
typedef struct
{
    uint16_t clear;       
    uint16_t red;       
    uint16_t green;      
    uint16_t blue;       
    uint16_t wideband;       
    uint16_t flicker;     

} color11_als_data_t;

/**
 * @brief Color 11 Click device identification object.
 * @details Device identification object definition of Color 11 Click driver.
 */
typedef struct
{
    uint8_t aux_id;       
    uint8_t rev_id;
    uint8_t dev_id;

} color11_identification_t;

/**
 * @brief Color 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COLOR11_OK = 0,
    COLOR11_ERROR = -1

} color11_return_value_t;

/**
 * @brief Color 11 Click power, enable, and operation value data.
 * @details Predefined enum values for power, enable, and operation values.
 */
typedef enum
{
    COLOR11_DISABLE = 0,
    COLOR11_ENABLE

} color11_pwr_ctrl_t;

/**
 * @brief Color 11 Click ALS Gain value data.
 * @details Predefined enum values for ALS Gain.
 */
typedef enum
{
    COLOR11_AGAIN_X0_5 = 0,
    COLOR11_AGAIN_X1,
    COLOR11_AGAIN_X2,
    COLOR11_AGAIN_X4,
    COLOR11_AGAIN_X8,
    COLOR11_AGAIN_X16,
    COLOR11_AGAIN_X32,
    COLOR11_AGAIN_X64,
    COLOR11_AGAIN_X128,
    COLOR11_AGAIN_X256,
    COLOR11_AGAIN_X512,
    COLOR11_AGAIN_X1024,
    COLOR11_AGAIN_X2048

} color11_again_t;

/*!
 * @addtogroup color11 Color 11 Click Driver
 * @brief API for configuring and manipulating Color 11 Click driver.
 * @{
 */

/**
 * @brief Color 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #color11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void color11_cfg_setup ( color11_cfg_t *cfg );

/**
 * @brief Color 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #color11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_init ( color11_t *ctx, color11_cfg_t *cfg );

/**
 * @brief Color 11 default configuration function.
 * @details This function executes a default configuration of Color 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t color11_default_cfg ( color11_t *ctx );

/**
 * @brief Color 11 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_generic_write ( color11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Color 11 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_generic_read ( color11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Color 11 get identification function.
 * @details This function reads a identification data 
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[out] id : Identification data.
 * See #color11_identification_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_get_identification ( color11_t *ctx, color11_identification_t *id );

/**
 * @brief Color 11 set ALS interrupt threshold function.
 * @details This function sets the ALS interrupt low and high threshold data
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] l_thold : ALS interrupt low threshold data [0-65535].
 * @param[in] h_thold : ALS interrupt high threshold data [0-65535].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_set_als_thold ( color11_t *ctx, uint16_t l_thold, uint16_t h_thold );

/**
 * @brief Color 11 set power control function.
 * @details This function sets the power on the device and enable the functions
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] pwr : Power ON.
 * See #color11_pwr_ctrl_t definition for detailed explanation.
 * @param[in] aen : Enables ALS/Color.
 * See #color11_pwr_ctrl_t definition for detailed explanation.
 * @param[in] wen : Activates the wait time.
 * See #color11_pwr_ctrl_t definition for detailed explanation.
 * @param[in] fden : Activates flicker detection.
 * See #color11_pwr_ctrl_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_set_power_ctrl ( color11_t *ctx, 
                               color11_pwr_ctrl_t pwr, 
                               color11_pwr_ctrl_t aen, 
                               color11_pwr_ctrl_t wen, 
                               color11_pwr_ctrl_t fden );

/**
 * @brief Color 11 set ALS step function.
 * @details This function sets a ALS integration time step size
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[out] als_step : Step size [2780-182000000ns].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_set_als_step ( color11_t *ctx, uint32_t als_step );

/**
 * @brief Color 11 get ALS step function.
 * @details This function reads a ALS integration time step size
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[out] als_step : Step size [2780-182000000ns].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_get_als_step ( color11_t *ctx, uint32_t *als_step );

/**
 * @brief Color 11 set ALS wait time function.
 * @details This function sets a ALS wait time data value
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] wait_time : Wait time [0-255], 2.844ms×(wait+1).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_set_als_wait ( color11_t *ctx, uint8_t wait_time );

/**
 * @brief Color 11 set ALS integration time function.
 * @details This function sets a ALS integration time
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] als_time : ALS time [0-32768000us].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_set_als_time ( color11_t *ctx, uint32_t als_time );

/**
 * @brief Color 11 get ALS integration time function.
 * @details This function reads a ALS integration time
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] als_time : ALS time [0-32768000us].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_get_als_time ( color11_t *ctx, float *als_time );

/**
 * @brief Color 11 set gain function.
 * @details This function sets the ALS sensitivity
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] gain : ALS sensitivity [0-12].
 * See #color11_again_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_set_gain ( color11_t *ctx, color11_again_t gain );

/**
 * @brief Color 11 get gain function.
 * @details This function reads the ALS sensitivity
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[out] gain : ALS sensitivity [0-12].
 * See #color11_again_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_get_gain ( color11_t *ctx, uint8_t *gain );

/**
 * @brief Color 11 set interrupt function.
 * @details This function enable interrupt status 
 * of the ALS, flicker, saturation or system detect
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[in] intenab : Interrupt detect status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_set_interrupt ( color11_t *ctx, uint8_t intenab );

/**
 * @brief Color 11 get data valid status function.
 * @details This function reads the data valid status
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[out] status : Data valid status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_get_data_valid_status ( color11_t *ctx, uint8_t *status );

/**
 * @brief Color 11 get ALS data function.
 * @details This function reads the all ALS channel and get ALS data values
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[out] als_data : ALS data values.
 * See #color11_als_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_get_als_data ( color11_t *ctx, color11_als_data_t *als_data );

/**
 * @brief Color 11 get IR data function.
 * @details This function reads the all ALS channel 
 * and calculate color temperature
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[out] ir : color temperature data values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_get_ir ( color11_t *ctx, float *ir );

/**
 * @brief Color 11 get illuminance function.
 * @details This function reads the all ALS channel 
 * and calculate illuminance data values
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @param[out] lux : Illuminance [lux].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t color11_get_illuminance ( color11_t *ctx, float *lux );

/**
 * @brief Color 11 get interrupt function.
 * @details This function gets states of the Interrupt (INT) pin
 * of the TCS3408, ALS/Color Sensor with Selective Flicker Detection
 * on the Color 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #color11_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t color11_get_interrupt ( color11_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // COLOR11_H

/*! @} */ // color11

// ------------------------------------------------------------------------ END
