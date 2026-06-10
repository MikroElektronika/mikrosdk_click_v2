/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file rtc26.h
 * @brief This file contains API for RTC 26 Click Driver.
 */

#ifndef RTC26_H
#define RTC26_H

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
 * @addtogroup rtc26 RTC 26 Click Driver
 * @brief API for configuring and manipulating RTC 26 Click driver.
 * @{
 */

/**
 * @defgroup rtc26_reg RTC 26 Registers List
 * @brief List of registers of RTC 26 Click driver.
 */

/**
 * @addtogroup rtc26_reg
 * @{
 */

/**
 * @brief RTC 26 Register Map.
 * @details Specified Register Map of RTC 26 Click driver.
 */
#define RTC26_REG_SEC                   0x00
#define RTC26_REG_MIN                   0x01
#define RTC26_REG_HOUR                  0x02
#define RTC26_REG_WEEK                  0x03
#define RTC26_REG_DAY                   0x04
#define RTC26_REG_MONTH                 0x05
#define RTC26_REG_YEAR                  0x06
#define RTC26_REG_RAM                   0x07
#define RTC26_REG_MIN_ALARM             0x08
#define RTC26_REG_HOUR_ALARM            0x09
#define RTC26_REG_WEEK_DAY_ALARM        0x0A
#define RTC26_REG_TIMER_CNT0            0x0B
#define RTC26_REG_TIMER_CNT1            0x0C
#define RTC26_REG_EXTENSION             0x0D
#define RTC26_REG_FLAG                  0x0E
#define RTC26_REG_CONTROL               0x0F
#define RTC26_REG_TEMP                  0x17
#define RTC26_REG_DEVICE_ID             0x20
#define RTC26_REG_RSV                   0x21
#define RTC26_REG_OFFSET0               0x25
#define RTC26_REG_OFFSET1               0x26
#define RTC26_REG_SUBSEC                0x27

/*! @} */ // rtc26_reg

/**
 * @defgroup rtc26_set RTC 26 Registers Settings
 * @brief Settings for registers of RTC 26 Click driver.
 */

/**
 * @addtogroup rtc26_set
 * @{
 */

/**
 * @brief RTC 26 day of week values setting.
 * @details Specified setting for day of week values of RTC 26 Click driver.
 */
#define RTC26_WEEK_SUNDAY               0x01
#define RTC26_WEEK_MONDAY               0x02
#define RTC26_WEEK_TUESDAY              0x04
#define RTC26_WEEK_WEDNESDAY            0x08
#define RTC26_WEEK_THURSDAY             0x10
#define RTC26_WEEK_FRIDAY               0x20
#define RTC26_WEEK_SATURDAY             0x40

/**
 * @brief RTC 26 extension register setting.
 * @details Specified setting for extension register of RTC 26 Click driver.
 */
#define RTC26_EXT_TEST                  0x80   
#define RTC26_EXT_WADA_WEEK             0x00   
#define RTC26_EXT_WADA_DAY              0x40    
#define RTC26_EXT_USEL_1S               0x00    
#define RTC26_EXT_USEL_1MIN             0x20   
#define RTC26_EXT_TE_DISABLE            0x00    
#define RTC26_EXT_TE_ENABLE             0x10   
#define RTC26_EXT_FSEL_32768HZ          0x00   
#define RTC26_EXT_FSEL_1024HZ           0x04    
#define RTC26_EXT_FSEL_1HZ              0x08   
#define RTC26_EXT_TSEL_4096HZ           0x00    
#define RTC26_EXT_TSEL_64HZ             0x01    
#define RTC26_EXT_TSEL_1HZ              0x02    
#define RTC26_EXT_TSEL_1_60HZ           0x03   

/**
 * @brief RTC 26 flag register bit masks setting.
 * @details Specified setting for flag register bit masks of RTC 26 Click driver.
 */
#define RTC26_FLAG_UF                   0x20    
#define RTC26_FLAG_TF                   0x10   
#define RTC26_FLAG_AF                   0x08    
#define RTC26_FLAG_VLF                  0x02
#define RTC26_FLAG_VDET                 0x01

/**
 * @brief RTC 26 control register setting.
 * @details Specified setting for control register of RTC 26 Click driver.
 */
#define RTC26_CTRL_CSEL_0_5S            0x00
#define RTC26_CTRL_CSEL_2S              0x40
#define RTC26_CTRL_CSEL_10S             0x80
#define RTC26_CTRL_CSEL_30S             0xC0
#define RTC26_CTRL_UIE                  0x20
#define RTC26_CTRL_TIE                  0x10
#define RTC26_CTRL_AIE                  0x08
#define RTC26_CTRL_RESET                0x01

/**
 * @brief RTC 26 alarm enable bit setting.
 * @details Specified setting for alarm enable bit of RTC 26 Click driver.
 */
#define RTC26_ALARM_ENABLE              0x00
#define RTC26_ALARM_DISABLE             0x80

/**
 * @brief RTC 26 device ID value setting.
 * @details Specified setting for device ID value of RTC 26 Click driver.
 */
#define RTC26_DEVICE_ID                 0xD2

/**
 * @brief RTC 26 RSV register required value setting.
 * @details Specified setting for RSV register required value of RTC 26 Click driver.
 */
#define RTC26_RSV_REQUIRED_VAL          0x80

/**
 * @brief RTC 26 register bit mask setting.
 * @details Specified setting for register bit masks of RTC 26 Click driver.
 */
#define RTC26_SEC_BIT_MASK              0x7F
#define RTC26_MIN_BIT_MASK              0x7F
#define RTC26_HOUR_BIT_MASK             0x3F
#define RTC26_WEEK_BIT_MASK             0x7F
#define RTC26_DAY_BIT_MASK              0x3F
#define RTC26_MONTH_BIT_MASK            0x1F

/**
 * @brief RTC 26 limit values setting.
 * @details Specified setting for limit values of RTC 26 Click driver.
 */
#define RTC26_MAX_SEC                   59
#define RTC26_MAX_MIN                   59
#define RTC26_MAX_HOUR                  23
#define RTC26_MAX_DAY                   31
#define RTC26_MIN_DAY                   1
#define RTC26_MAX_MONTH                 12
#define RTC26_MIN_MONTH                 1

/**
 * @brief RTC 26 alarm register bit mask setting.
 * @details Specified setting for alarm register bit masks of RTC 26 Click driver.
 */
#define RTC26_ALARM_AE_BIT_MASK         0x80
#define RTC26_ALARM_MIN_BIT_MASK        0x7F
#define RTC26_ALARM_HOUR_BIT_MASK       0x3F
#define RTC26_ALARM_DAY_WEEK_BIT_MASK   0x7F

/**
 * @brief RTC 26 week days number setting.
 * @details Specified setting for week days number of RTC 26 Click driver.
 */
#define RTC26_WEEK_DAYS_NUM             7

/**
 * @brief RTC 26 temperature calculation setting.
 * @details Specified setting for temperature calculation of RTC 26 Click driver.
 */
#define RTC26_TEMP_MULTIPLIER           2.0f
#define RTC26_TEMP_OFFSET               147.5f
#define RTC26_TEMP_DIVISOR              3.0448f

/**
 * @brief RTC 26 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 26 Click driver.
 */
#define RTC26_DEVICE_ADDRESS            0x32

/*! @} */ // rtc26_set

/**
 * @defgroup rtc26_map RTC 26 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 26 Click driver.
 */

/**
 * @addtogroup rtc26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 26 Click to the selected MikroBUS.
 */
#define RTC26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.foe = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc26_map
/*! @} */ // rtc26

/**
 * @brief RTC 26 Click context object.
 * @details Context object definition of RTC 26 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t foe;                          /**< Frequency output enable pin (FOE). */

    // Input pins
    digital_in_t out;                           /**< Frequency output state pin (FOUT). */
    digital_in_t int_pin;                       /**< Interrupt output pin (active low, open-drain). */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} rtc26_t;

/**
 * @brief RTC 26 Click configuration object.
 * @details Configuration object definition of RTC 26 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t out;             /**< Frequency output state pin. */
    pin_name_t foe;             /**< Frequency output enable pin. */
    pin_name_t int_pin;         /**< Interrupt output pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} rtc26_cfg_t;

/**
 * @brief RTC 26 Click time object.
 * @details Time object definition of RTC 26 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc26_time_t;

/**
 * @brief RTC 26 Click date object.
 * @details Date object definition of RTC 26 Click driver.
 * @note day_of_week uses bitmask values and only one bit must be set at a time.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc26_date_t;

/**
 * @brief RTC 26 Click alarm object.
 * @details Alarm object definition of RTC 26 Click driver.
 */
typedef struct
{
    uint8_t minute;
    uint8_t hour;
    uint8_t day_week;
    uint8_t minute_en;
    uint8_t hour_en;
    uint8_t day_week_en;

} rtc26_alarm_t;

/**
 * @brief RTC 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC26_OK = 0,
    RTC26_ERROR = -1

} rtc26_return_value_t;

/*!
 * @addtogroup rtc26 RTC 26 Click Driver
 * @brief API for configuring and manipulating RTC 26 Click driver.
 * @{
 */

/**
 * @brief RTC 26 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc26_cfg_setup ( rtc26_cfg_t *cfg );

/**
 * @brief RTC 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_init ( rtc26_t *ctx, rtc26_cfg_t *cfg );

/**
 * @brief RTC 26 default configuration function.
 * @details This function executes a default configuration of RTC 26
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtc26_default_cfg ( rtc26_t *ctx );

/**
 * @brief RTC 26 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_generic_write ( rtc26_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 26 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_generic_read ( rtc26_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 26 set time function.
 * @details This function sets the desired time (hours, minutes, seconds) in the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[in] rtc_time : Pointer to the time structure.
 * See #rtc26_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_set_time ( rtc26_t *ctx, rtc26_time_t rtc_time );

/**
 * @brief RTC 26 get time function.
 * @details This function reads the current time (hours, minutes, seconds) from the RTC
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[out] rtc_time : Pointer to the time structure to store the read values.
 * See #rtc26_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_get_time ( rtc26_t *ctx, rtc26_time_t *rtc_time );

/**
 * @brief RTC 26 set date function.
 * @details This function sets the desired date (day, day of week, month, year) in the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[in] rtc_date : Pointer to the date structure.
 * See #rtc26_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_set_date ( rtc26_t *ctx, rtc26_date_t rtc_date );

/**
 * @brief RTC 26 get date function.
 * @details This function reads the current date (day, day of week, month, year) from the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[out] rtc_date : Pointer to the date structure to store the read values.
 * See #rtc26_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_get_date ( rtc26_t *ctx, rtc26_date_t *rtc_date );

/**
 * @brief RTC 26 set alarm function.
 * @details This function sets the desired alarm time (hours, minutes, day/week) in the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[in] rtc_alarm : Pointer to the alarm structure.
 * See #rtc26_alarm_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Configure WADA bit in extension register before calling this function
 *       to select WEEK or DAY alarm mode for the day_week field.
 */
err_t rtc26_set_alarm ( rtc26_t *ctx, rtc26_alarm_t rtc_alarm );

/**
 * @brief RTC 26 get alarm function.
 * @details This function reads the current alarm settings (hours, minutes, day/week) from the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[out] rtc_alarm : Pointer to the alarm structure to store the read values.
 * See #rtc26_alarm_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_get_alarm ( rtc26_t *ctx, rtc26_alarm_t *rtc_alarm );

/**
 * @brief RTC 26 get flag register function.
 * @details This function reads the flag register value.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[out] flag : Pointer to variable to store the read flag register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_get_flag_register ( rtc26_t *ctx, uint8_t *flag );

/**
 * @brief RTC 26 clear flag function.
 * @details This function clears selected bits in the flag register.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[in] flag_mask : Bitmask of flags to clear.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Only value 0 can be written to flag bits (UF, TF, AF, VLF, VDET).
 */
err_t rtc26_clear_flag ( rtc26_t *ctx, uint8_t flag_mask );

/**
 * @brief RTC 26 set FOE pin function.
 * @details This function sets the FOE pin state.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - FOUT output disabled (Hi-Z),
 *                    @li @c 1 - FOUT output enabled.
 * @return Nothing.
 * @note None.
 */
void rtc26_set_foe_pin ( rtc26_t *ctx, uint8_t state );

/**
 * @brief RTC 26 get INT pin function.
 * @details This function returns the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc26_get_int_pin ( rtc26_t *ctx );

/**
 * @brief RTC 26 get OUT pin function.
 * @details This function returns the logic state of the OUT pin.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc26_get_out_pin ( rtc26_t *ctx );

/**
 * @brief RTC 26 get temperature function.
 * @details This function reads the temperature sensor data and
 * converts it to degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #rtc26_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to variable to store the read temperature value in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc26_get_temperature ( rtc26_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // RTC26_H

/*! @} */ // rtc26

// ------------------------------------------------------------------------ END
