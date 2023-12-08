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
 * @file angle7.h
 * @brief This file contains API for Angle 7 Click Driver.
 */

#ifndef ANGLE7_H
#define ANGLE7_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup angle7 Angle 7 Click Driver
 * @brief API for configuring and manipulating Angle 7 Click driver.
 * @{
 */

/**
 * @defgroup angle7_reg Angle 7 Registers List
 * @brief List of registers of Angle 7 Click driver.
 */

/**
 * @addtogroup angle7_reg
 * @{
 */

/**
 * @brief Angle 7 register list.
 * @details Specified register list for description of Angle 7 Click driver.
 */
#define ANGLE7_REG_ZMCO                     0x00
#define ANGLE7_REG_ZPOS_MSB                 0x01
#define ANGLE7_REG_ZPOS_LSB                 0x02
#define ANGLE7_REG_MPOS_MSB                 0x03
#define ANGLE7_REG_MPOS_LSB                 0x04
#define ANGLE7_REG_MANG_MSB                 0x05
#define ANGLE7_REG_MANG_LSB                 0x06
#define ANGLE7_REG_CONF_MSB                 0x07
#define ANGLE7_REG_CONF_LSB                 0x08
#define ANGLE7_REG_STATUS                   0x0B
#define ANGLE7_REG_RAW_ANGLE_MSB            0x0C
#define ANGLE7_REG_RAW_ANGLE_LSB            0x0D
#define ANGLE7_REG_ANGLE_MSB                0x0E
#define ANGLE7_REG_ANGLE_LSB                0x0F
#define ANGLE7_REG_AGC                      0x1A
#define ANGLE7_REG_MAGNITUDE_MSB            0x1B
#define ANGLE7_REG_MAGNITUDE_LSB            0x1C
#define ANGLE7_REG_BURN                     0xFF

/*! @} */ // angle7_reg

/**
 * @defgroup angle7_set Angle 7 Registers Settings
 * @brief Settings for registers of Angle 7 Click driver.
 */

/**
 * @addtogroup angle7_set
 * @{
 */

/**
 * @brief Angle 7 CONF register settings.
 * @details Specified CONF register settings of Angle 7 Click driver.
 */
#define ANGLE7_CONF_WATCHDOG_OFF            0x0000
#define ANGLE7_CONF_WATCHDOG_ON             0x2000
#define ANGLE7_CONF_WATCHDOG_BIT_MASK       0x2000
#define ANGLE7_CONF_FTH_SLOW                0x0000
#define ANGLE7_CONF_FTH_6LSB                0x0400
#define ANGLE7_CONF_FTH_7LSB                0x0800
#define ANGLE7_CONF_FTH_9LSB                0x0C00
#define ANGLE7_CONF_FTH_18LSB               0x1000
#define ANGLE7_CONF_FTH_21LSB               0x1400
#define ANGLE7_CONF_FTH_24LSB               0x1800
#define ANGLE7_CONF_FTH_10LSB               0x1C00
#define ANGLE7_CONF_FTH_BIT_MASK            0x1C00
#define ANGLE7_CONF_SF_16X                  0x0000
#define ANGLE7_CONF_SF_8X                   0x0100
#define ANGLE7_CONF_SF_4X                   0x0200
#define ANGLE7_CONF_SF_2X                   0x0300
#define ANGLE7_CONF_SF_BIT_MASK             0x0300
#define ANGLE7_CONF_PWMF_115HZ              0x0000
#define ANGLE7_CONF_PWMF_230HZ              0x0040
#define ANGLE7_CONF_PWMF_460HZ              0x0080
#define ANGLE7_CONF_PWMF_920HZ              0x00C0
#define ANGLE7_CONF_PWMF_BIT_MASK           0x00C0
#define ANGLE7_CONF_OUTS_ANALOG_FULL        0x0000
#define ANGLE7_CONF_OUTS_ANALOG_REDUCED     0x0010
#define ANGLE7_CONF_OUTS_PWM                0x0020
#define ANGLE7_CONF_OUTS_BIT_MASK           0x0030
#define ANGLE7_CONF_HYST_OFF                0x0000
#define ANGLE7_CONF_HYST_1LSB               0x0004
#define ANGLE7_CONF_HYST_2LSB               0x0008
#define ANGLE7_CONF_HYST_3LSB               0x000C
#define ANGLE7_CONF_HYST_BIT_MASK           0x000C
#define ANGLE7_CONF_PM_NOM                  0x0000
#define ANGLE7_CONF_PM_LPM1                 0x0001
#define ANGLE7_CONF_PM_LPM2                 0x0002
#define ANGLE7_CONF_PM_LPM3                 0x0003
#define ANGLE7_CONF_PM_BIT_MASK             0x0003

/**
 * @brief Angle 7 STATUS register settings.
 * @details Specified STATUS register settings of Angle 7 Click driver.
 */
#define ANGLE7_STATUS_MAGNET_DETECTED       0x20
#define ANGLE7_STATUS_MAGNET_TOO_WEAK       0x10
#define ANGLE7_STATUS_MAGNET_TOO_STRONG     0x08

/**
 * @brief Angle 7 BURN register settings.
 * @details Specified BURN register settings of Angle 7 Click driver.
 */
#define ANGLE7_BURN_ANGLE                   0x80
#define ANGLE7_BURN_SETTING                 0x40

/**
 * @brief Angle 7 Angle calculation values.
 * @details Specified Angle calculation values of Angle 7 Click driver.
 */
#define ANGLE7_RESOLUTION                   0x0FFF
#define ANGLE7_FULL_CIRCLE                  360.0
#define ANGLE7_ZERO_POSITION                0.0

/**
 * @brief Angle 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Angle 7 Click driver.
 */
#define ANGLE7_DEVICE_ADDRESS               0x36

/*! @} */ // angle7_set

/**
 * @defgroup angle7_map Angle 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Angle 7 Click driver.
 */

/**
 * @addtogroup angle7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Angle 7 Click to the selected MikroBUS.
 */
#define ANGLE7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // angle7_map
/*! @} */ // angle7

/**
 * @brief Angle 7 Click context object.
 * @details Context object definition of Angle 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */

    // Input pins
    digital_in_t  int_pin;      /**< Analog or PWM input pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */
    analog_in_t  adc;           /**< ADC module object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    float start_position;
    float stop_position;

} angle7_t;

/**
 * @brief Angle 7 Click configuration object.
 * @details Configuration object definition of Angle 7 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;             /**< Enable pin. */
    pin_name_t  an;             /**< Analog pin descriptor. */
    pin_name_t  int_pin;        /**< Analog or PWM input pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */
    
    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} angle7_cfg_t;

/**
 * @brief Angle 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANGLE7_OK = 0,
    ANGLE7_ERROR = -1

} angle7_return_value_t;

/*!
 * @addtogroup angle7 Angle 7 Click Driver
 * @brief API for configuring and manipulating Angle 7 Click driver.
 * @{
 */

/**
 * @brief Angle 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #angle7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void angle7_cfg_setup ( angle7_cfg_t *cfg );

/**
 * @brief Angle 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #angle7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_init ( angle7_t *ctx, angle7_cfg_t *cfg );

/**
 * @brief Angle 7 default configuration function.
 * @details This function executes a default configuration of Angle 7
 * click board.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t angle7_default_cfg ( angle7_t *ctx );

/**
 * @brief Angle 7 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_generic_write ( angle7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Angle 7 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_generic_read ( angle7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Angle 7 write two bytes function.
 * @details This function writes two bytes of data to two consecutive registers starting from
 * the selected address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_write_two_bytes ( angle7_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Angle 7 read two bytes function.
 * @details This function reads two bytes of data from two consecutive registers starting from
 * the selected address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_read_two_bytes ( angle7_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Angle 7 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_read_an_pin_value ( angle7_t *ctx, uint16_t *data_out );

/**
 * @brief Angle 7 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t angle7_read_an_pin_voltage ( angle7_t *ctx, float *data_out );

/**
 * @brief Angle 7 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t angle7_get_int_pin ( angle7_t *ctx );

/**
 * @brief Angle 7 enable device function.
 * @details This function enables the device by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void angle7_enable_device ( angle7_t *ctx );

/**
 * @brief Angle 7 disable device function.
 * @details This function disables the device by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void angle7_disable_device ( angle7_t *ctx );

/**
 * @brief Angle 7 set start position function.
 * @details This function sets the start position in angle degrees used for angle calculation.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[in] angle : Start angle in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_set_start_position ( angle7_t *ctx, float angle );

/**
 * @brief Angle 7 get start position function.
 * @details This function reads the start position in angle degrees used for angle calculation.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[out] angle : Start angle in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_get_start_position ( angle7_t *ctx, float *angle );

/**
 * @brief Angle 7 set stop position function.
 * @details This function sets the stop position in angle degrees used for angle calculation.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[in] angle : Stop angle in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_set_stop_position ( angle7_t *ctx, float angle );

/**
 * @brief Angle 7 get stop position function.
 * @details This function reads the stop position in angle degrees used for angle calculation.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[out] angle : Stop angle in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_get_stop_position ( angle7_t *ctx, float *angle );

/**
 * @brief Angle 7 get raw angle function.
 * @details This function reads the RAW angle in degrees.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[out] angle : RAW angle in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_get_raw_angle ( angle7_t *ctx, float *angle );

/**
 * @brief Angle 7 get angle function.
 * @details This function reads the calculated angle in degrees.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[out] angle : Calculated angle in degrees.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_get_angle ( angle7_t *ctx, float *angle );

/**
 * @brief Angle 7 get status function.
 * @details This function reads the status data.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[out] status : Status register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_get_status ( angle7_t *ctx, uint8_t *status );

/**
 * @brief Angle 7 get agc function.
 * @details This function reads the AGC (automatic gain control) data.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[out] agc : AGC register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_get_agc ( angle7_t *ctx, uint8_t *agc );

/**
 * @brief Angle 7 get magnitude function.
 * @details This function reads the magnitude data.
 * @param[in] ctx : Click context object.
 * See #angle7_t object definition for detailed explanation.
 * @param[out] magnitude : Magnitude register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle7_get_magnitude ( angle7_t *ctx, uint16_t *magnitude );

#ifdef __cplusplus
}
#endif
#endif // ANGLE7_H

/*! @} */ // angle7

// ------------------------------------------------------------------------ END
