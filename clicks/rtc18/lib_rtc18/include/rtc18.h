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
 * @file rtc18.h
 * @brief This file contains API for RTC 18 Click Driver.
 */

#ifndef RTC18_H
#define RTC18_H

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
 * @addtogroup rtc18 RTC 18 Click Driver
 * @brief API for configuring and manipulating RTC 18 Click driver.
 * @{
 */

/**
 * @defgroup rtc18_reg RTC 18 Registers List
 * @brief List of registers of RTC 18 Click driver.
 */

/**
 * @addtogroup rtc18_reg
 * @{
 */

/**
 * @brief RTC 18 register map.
 * @details Specified register map of RTC 18 Click driver.
 */
#define RTC18_REG_100TH_SECONDS                     0x00
#define RTC18_REG_SECONDS                           0x01
#define RTC18_REG_MINUTES                           0x02
#define RTC18_REG_HOURS                             0x03
#define RTC18_REG_WEEKDAY                           0x04
#define RTC18_REG_DATE                              0x05
#define RTC18_REG_MONTH                             0x06
#define RTC18_REG_YEAR                              0x07
#define RTC18_REG_MINUTES_ALARM                     0x08
#define RTC18_REG_HOURS_ALARM                       0x09
#define RTC18_REG_DATE_ALARM                        0x0A
#define RTC18_REG_TIMER_VALUE_0                     0x0B
#define RTC18_REG_TIMER_VALUE_1                     0x0C
#define RTC18_REG_STATUS                            0x0D
#define RTC18_REG_TEMPERATURE_LSB                   0x0E
#define RTC18_REG_TEMPERATURE_MSB                   0x0F
#define RTC18_REG_CONTROL_1                         0x10
#define RTC18_REG_CONTROL_2                         0x11
#define RTC18_REG_CONTROL_3                         0x12
#define RTC18_REG_TIME_STAMP_CONTROL                0x13
#define RTC18_REG_CLOCK_INT_MASK                    0x14
#define RTC18_REG_EVI_CONTROL                       0x15
#define RTC18_REG_TLOW_THRESHOLD                    0x16
#define RTC18_REG_THIGH_THRESHOLD                   0x17
#define RTC18_REG_TS_TLOW_COUNT                     0x18
#define RTC18_REG_TS_TLOW_SECONDS                   0x19
#define RTC18_REG_TS_TLOW_MINUTES                   0x1A
#define RTC18_REG_TS_TLOW_HOURS                     0x1B
#define RTC18_REG_TS_TLOW_DATE                      0x1C
#define RTC18_REG_TS_TLOW_MONTH                     0x1D
#define RTC18_REG_TS_TLOW_YEAR                      0x1E
#define RTC18_REG_TS_THIGH_COUNT                    0x1F
#define RTC18_REG_TS_THIGH_SECONDS                  0x20
#define RTC18_REG_TS_THIGH_MINUTES                  0x21
#define RTC18_REG_TS_THIGH_HOURS                    0x22
#define RTC18_REG_TS_THIGH_DATE                     0x23
#define RTC18_REG_TS_THIGH_MONTH                    0x24
#define RTC18_REG_TS_THIGH_YEAR                     0x25
#define RTC18_REG_TS_EVI_COUNT                      0x26
#define RTC18_REG_TS_EVI_100TH_SECONDS              0x27
#define RTC18_REG_TS_EVI_SECONDS                    0x28
#define RTC18_REG_TS_EVI_MINUTES                    0x29
#define RTC18_REG_TS_EVI_HOURS                      0x2A
#define RTC18_REG_TS_EVI_DATE                       0x2B
#define RTC18_REG_TS_EVI_MONTH                      0x2C
#define RTC18_REG_TS_EVI_YEAR                       0x2D
#define RTC18_REG_PASSWORD_0                        0x39
#define RTC18_REG_PASSWORD_1                        0x3A
#define RTC18_REG_PASSWORD_2                        0x3B
#define RTC18_REG_PASSWORD_3                        0x3C
#define RTC18_REG_EEPROM_ADDRESS                    0x3D
#define RTC18_REG_EEPROM_DATA                       0x3E
#define RTC18_REG_EEPROM_COMMAND                    0x3F
#define RTC18_REG_USER_RAM_16B                      0x40

/**
 * @brief RTC 18 EEPROM config register map.
 * @details Specified EEPROM config register map of RTC 18 Click driver.
 */
#define RTC18_EEPROM_PMU                            0xC0
#define RTC18_EEPROM_OFFSET                         0xC1
#define RTC18_EEPROM_CLKOUT_1                       0xC2
#define RTC18_EEPROM_CLKOUT_2                       0xC3
#define RTC18_EEPROM_TREF_0                         0xC4
#define RTC18_EEPROM_TREF_1                         0xC5
#define RTC18_EEPROM_PASSWORD_0                     0xC6
#define RTC18_EEPROM_PASSWORD_1                     0xC7
#define RTC18_EEPROM_PASSWORD_2                     0xC8
#define RTC18_EEPROM_PASSWORD_3                     0xC9
#define RTC18_EEPROM_PW_ENABLE                      0xCA
#define RTC18_EEPROM_USER_MEMORY_32B                0xCB

/*! @} */ // rtc18_reg

/**
 * @defgroup rtc18_set RTC 18 Registers Settings
 * @brief Settings for registers of RTC 18 Click driver.
 */

/**
 * @addtogroup rtc18_set
 * @{
 */

/**
 * @brief RTC 18 status register settings.
 * @details Specified status register settings of RTC 18 Click driver.
 */
#define RTC18_STATUS_THF                            0x80
#define RTC18_STATUS_TLF                            0x40
#define RTC18_STATUS_UF                             0x20
#define RTC18_STATUS_TF                             0x10
#define RTC18_STATUS_AF                             0x08
#define RTC18_STATUS_EVF                            0x04
#define RTC18_STATUS_PORF                           0x02
#define RTC18_STATUS_VLF                            0x01

/**
 * @brief RTC 18 control 1 register settings.
 * @details Specified control 1 register settings of RTC 18 Click driver.
 */
#define RTC18_CONTROL1_RESERVED                     0x20
#define RTC18_CONTROL1_USEL                         0x10
#define RTC18_CONTROL1_TE                           0x08
#define RTC18_CONTROL1_EERD                         0x04
#define RTC18_CONTROL1_TD_4096HZ                    0x00
#define RTC18_CONTROL1_TD_64HZ                      0x01
#define RTC18_CONTROL1_TD_1HZ                       0x02
#define RTC18_CONTROL1_TD_1_60HZ                    0x03
#define RTC18_CONTROL1_TD_BIT_MASK                  0x03

/**
 * @brief RTC 18 control 2 register settings.
 * @details Specified control 2 register settings of RTC 18 Click driver.
 */
#define RTC18_CONTROL2_CLKIE                        0x40
#define RTC18_CONTROL2_UIE                          0x20
#define RTC18_CONTROL2_TIE                          0x10
#define RTC18_CONTROL2_AIE                          0x08
#define RTC18_CONTROL2_EIE                          0x04
#define RTC18_CONTROL2_STOP                         0x01

/**
 * @brief RTC 18 control 3 register settings.
 * @details Specified control 3 register settings of RTC 18 Click driver.
 */
#define RTC18_CONTROL3_BSIE                         0x10
#define RTC18_CONTROL3_THE                          0x08
#define RTC18_CONTROL3_TLE                          0x04
#define RTC18_CONTROL3_THIE                         0x02
#define RTC18_CONTROL3_TLIE                         0x01

/**
 * @brief RTC 18 day of week values.
 * @details Specified day of week values of RTC 18 Click driver.
 */
#define RTC18_MONDAY                                0x00
#define RTC18_TUESDAY                               0x01
#define RTC18_WEDNESDAY                             0x02
#define RTC18_THURSDAY                              0x03
#define RTC18_FRIDAY                                0x04
#define RTC18_SATURDAY                              0x05
#define RTC18_SUNDAY                                0x06

/**
 * @brief RTC 18 temperature settings.
 * @details Specified temperature settings of RTC 18 Click driver.
 */
#define RTC18_TEMPERATURE_RESOLUTION                0.0625
#define RTC18_TEMPERATURE_LSB_TEMP_BIT_MASK         0xF0
#define RTC18_TEMPERATURE_LSB_EEF                   0x08 
#define RTC18_TEMPERATURE_LSB_EEBUSY                0x04
#define RTC18_TEMPERATURE_LSB_CLKF                  0x02
#define RTC18_TEMPERATURE_LSB_BSF                   0x01   

/**
 * @brief RTC 18 EEPROM commands list.
 * @details Specified EEPROM commands list of RTC 18 Click driver.
 */
#define RTC18_EECMD_UPDATE                          0x11
#define RTC18_EECMD_REFRESH                         0x12
#define RTC18_EECMD_WRITE_ONE_BYTE                  0x21
#define RTC18_EECMD_READ_ONE_BYTE                   0x22

/**
 * @brief RTC 18 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 18 Click driver.
 */
#define RTC18_DEVICE_ADDRESS                        0x51

/*! @} */ // rtc18_set

/**
 * @defgroup rtc18_map RTC 18 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 18 Click driver.
 */

/**
 * @addtogroup rtc18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 18 Click to the selected MikroBUS.
 */
#define RTC18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.evi = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc18_map
/*! @} */ // rtc18

/**
 * @brief RTC 18 Click context object.
 * @details Context object definition of RTC 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t evi;          /**< Event input pin. */

    // Input pins
    digital_in_t  int_pin;      /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rtc18_t;

/**
 * @brief RTC 18 Click configuration object.
 * @details Configuration object definition of RTC 18 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  evi;            /**< Event input pin. */
    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} rtc18_cfg_t;

/**
 * @brief RTC 18 Click time object.
 * @details Time object definition of RTC 18 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second_100th;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc18_time_t;

/**
 * @brief RTC 18 Click date object.
 * @details Date object definition of RTC 18 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc18_date_t;

/**
 * @brief RTC 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC18_OK = 0,
    RTC18_ERROR = -1

} rtc18_return_value_t;

/*!
 * @addtogroup rtc18 RTC 18 Click Driver
 * @brief API for configuring and manipulating RTC 18 Click driver.
 * @{
 */

/**
 * @brief RTC 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc18_cfg_setup ( rtc18_cfg_t *cfg );

/**
 * @brief RTC 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_init ( rtc18_t *ctx, rtc18_cfg_t *cfg );

/**
 * @brief RTC 18 default configuration function.
 * @details This function executes a default configuration of RTC 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtc18_default_cfg ( rtc18_t *ctx );

/**
 * @brief RTC 18 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_generic_write ( rtc18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 18 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_generic_read ( rtc18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 18 write register function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_write_register ( rtc18_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 18 read register function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] reg : register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_read_register ( rtc18_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 18 set EVI pin function.
 * @details This function sets the EVI pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtc18_set_evi_pin ( rtc18_t *ctx, uint8_t state );

/**
 * @brief RTC 18 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc18_get_int_pin ( rtc18_t *ctx );

/**
 * @brief RTC 18 clear periodic interrupt function.
 * @details This function clears the periodic interrupt flag (UF) bit in STATUS register.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_clear_periodic_interrupt ( rtc18_t *ctx );

/**
 * @brief RTC 18 set time function.
 * @details This function sets the starting time values - second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] time : Time object structure that carries second, minute and hour values in Decimal format.
 * See #rtc18_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_set_time ( rtc18_t *ctx, rtc18_time_t *time );

/**
 * @brief RTC 18 read time function.
 * @details This function reads the current time values - second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[out] time : Time object structure.
 * See #rtc18_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_read_time ( rtc18_t *ctx, rtc18_time_t *time );

/**
 * @brief RTC 18 set date function.
 * @details This function sets the starting date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] date : Date object structure that carries day of week, day, month and year values in Decimal format.
 * See #rtc18_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_set_date ( rtc18_t *ctx, rtc18_date_t *date );

/**
 * @brief RTC 18 read date function.
 * @details This function reads the current date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[out] date : Date object structure.
 * See #rtc18_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_read_date ( rtc18_t *ctx, rtc18_date_t *date );

/**
 * @brief RTC 18 read temperature function.
 * @details This function reads temperature measurements in Celsius.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_read_temperature ( rtc18_t *ctx, float *temperature );

/**
 * @brief RTC 18 write eeprom function.
 * @details This function writes a desired data byte to the selected EEPROM address 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] address : EEPROM address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_write_eeprom ( rtc18_t *ctx, uint8_t address, uint8_t data_in );

/**
 * @brief RTC 18 read eeprom function.
 * @details This function reads a data byte from the selected EEPROM address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] address : EEPROM address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc18_read_eeprom ( rtc18_t *ctx, uint8_t address, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // RTC18_H

/*! @} */ // rtc18

// ------------------------------------------------------------------------ END
