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
 * @file rtc19.h
 * @brief This file contains API for RTC 19 Click Driver.
 */

#ifndef RTC19_H
#define RTC19_H

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
 * @addtogroup rtc19 RTC 19 Click Driver
 * @brief API for configuring and manipulating RTC 19 Click driver.
 * @{
 */

/**
 * @defgroup rtc19_reg RTC 19 Registers List
 * @brief List of registers of RTC 19 Click driver.
 */

/**
 * @addtogroup rtc19_reg
 * @{
 */

/**
 * @brief RTC 19 RTC register list.
 * @details Specified RTC register list for description of RTC 19 Click driver.
 */
#define RTC19_REG_STATUS                    0x00
#define RTC19_REG_INT_EN                    0x01
#define RTC19_REG_RTC_RESET                 0x02
#define RTC19_REG_RTC_CONFIG1               0x03
#define RTC19_REG_RTC_CONFIG2               0x04
#define RTC19_REG_TIMESTAMP_CONFIG          0x05
#define RTC19_REG_TIMER_CONFIG              0x06
#define RTC19_REG_SLEEP_CONFIG              0x07
#define RTC19_REG_SECONDS_1_128             0x08
#define RTC19_REG_SECONDS                   0x09
#define RTC19_REG_MINUTES                   0x0A
#define RTC19_REG_HOURS                     0x0B
#define RTC19_REG_DAY                       0x0C
#define RTC19_REG_DATE                      0x0D
#define RTC19_REG_MONTH                     0x0E
#define RTC19_REG_YEAR                      0x0F
#define RTC19_REG_ALM1_SEC                  0x10
#define RTC19_REG_ALM1_MIN                  0x11
#define RTC19_REG_ALM1_HRS                  0x12
#define RTC19_REG_ALM1_DAY_DATE             0x13
#define RTC19_REG_ALM1_MON                  0x14
#define RTC19_REG_ALM1_YEAR                 0x15
#define RTC19_REG_ALM2_MIN                  0x16
#define RTC19_REG_ALM2_HRS                  0x17
#define RTC19_REG_ALM2_DAY_DATE             0x18
#define RTC19_REG_TIMER_COUNT2              0x19
#define RTC19_REG_TIMER_COUNT1              0x1A
#define RTC19_REG_TIMER_INIT2               0x1B
#define RTC19_REG_TIMER_INIT1               0x1C
#define RTC19_REG_PWR_MGMT                  0x1D
#define RTC19_REG_TRICKLE_REG               0x1E
#define RTC19_REG_OFFSET_HIGH               0x20
#define RTC19_REG_OFFSET_LOW                0x21

/**
 * @brief RTC 19 TS RAM register list.
 * @details Specified TS RAM register list for description of RTC 19 Click driver.
 */
#define RTC19_REG_TS0_SEC_1_128             0x30
#define RTC19_REG_TS0_SEC                   0x31
#define RTC19_REG_TS0_MIN                   0x32
#define RTC19_REG_TS0_HOUR                  0x33
#define RTC19_REG_TS0_DATE                  0x34
#define RTC19_REG_TS0_MONTH                 0x35
#define RTC19_REG_TS0_YEAR                  0x36
#define RTC19_REG_TS0_FLAGS                 0x37
#define RTC19_REG_TS1_SEC_1_128             0x38
#define RTC19_REG_TS1_SEC                   0x39
#define RTC19_REG_TS1_MIN                   0x3A
#define RTC19_REG_TS1_HOUR                  0x3B
#define RTC19_REG_TS1_DATE                  0x3C
#define RTC19_REG_TS1_MONTH                 0x3D
#define RTC19_REG_TS1_YEAR                  0x3E
#define RTC19_REG_TS1_FLAGS                 0x3F
#define RTC19_REG_TS2_SEC_1_128             0x40
#define RTC19_REG_TS2_SEC                   0x41
#define RTC19_REG_TS2_MIN                   0x42
#define RTC19_REG_TS2_HOUR                  0x43
#define RTC19_REG_TS2_DATE                  0x44
#define RTC19_REG_TS2_MONTH                 0x45
#define RTC19_REG_TS2_YEAR                  0x46
#define RTC19_REG_TS2_FLAGS                 0x47
#define RTC19_REG_TS3_SEC_1_128             0x48
#define RTC19_REG_TS3_SEC                   0x49
#define RTC19_REG_TS3_MIN                   0x4A
#define RTC19_REG_TS3_HOUR                  0x4B
#define RTC19_REG_TS3_DATE                  0x4C
#define RTC19_REG_TS3_MONTH                 0x4D
#define RTC19_REG_TS3_YEAR                  0x4E
#define RTC19_REG_TS3_FLAGS                 0x4F

/*! @} */ // rtc19_reg

/**
 * @defgroup rtc19_set RTC 19 Registers Settings
 * @brief Settings for registers of RTC 19 Click driver.
 */

/**
 * @addtogroup rtc19_set
 * @{
 */

/**
 * @brief RTC 19 RTC_RESET register setting.
 * @details Specified setting for RTC_RESET register of RTC 19 Click driver.
 */
#define RTC19_RTC_RESET_CLEAR               0x00
#define RTC19_RTC_RESET_SET                 0x01

/**
 * @brief RTC 19 INT_EN register setting.
 * @details Specified setting for INT_EN register of RTC 19 Click driver.
 */
#define RTC19_INT_EN_DOSF                   0x40
#define RTC19_INT_EN_PFAILE                 0x20
#define RTC19_INT_EN_VBATLOWIE              0x10
#define RTC19_INT_EN_DIE                    0x08
#define RTC19_INT_EN_TIE                    0x04
#define RTC19_INT_EN_A2IE                   0x02
#define RTC19_INT_EN_A1IE                   0x01

/**
 * @brief RTC 19 TIMER_CONFIG register setting.
 * @details Specified setting for TIMER_CONFIG register of RTC 19 Click driver.
 */
#define RTC19_TIMER_CONFIG_TE               0x10
#define RTC19_TIMER_CONFIG_TPAUSE           0x08
#define RTC19_TIMER_CONFIG_TRPT             0x04
#define RTC19_TIMER_CONFIG_TFS_1024HZ       0x00
#define RTC19_TIMER_CONFIG_TFS_256HZ        0x01
#define RTC19_TIMER_CONFIG_TFS_64HZ         0x02
#define RTC19_TIMER_CONFIG_TFS_16HZ         0x03
#define RTC19_TIMER_CONFIG_TFS_MASK         0x03

/**
 * @brief RTC 19 TIMER_INIT register setting.
 * @details Specified setting for TIMER_INIT register of RTC 19 Click driver.
 */
#define RTC19_TIMER_INIT_16CNT              0x000F

/**
 * @brief RTC 19 day of week values.
 * @details Specified day of week values of RTC 19 Click driver.
 */
#define RTC19_MONDAY                        0x01
#define RTC19_TUESDAY                       0x02
#define RTC19_WEDNESDAY                     0x03
#define RTC19_THURSDAY                      0x04
#define RTC19_FRIDAY                        0x05
#define RTC19_SATURDAY                      0x06
#define RTC19_SUNDAY                        0x07

/**
 * @brief RTC 19 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 19 Click driver.
 */
#define RTC19_DEVICE_ADDRESS                0x68

/*! @} */ // rtc19_set

/**
 * @defgroup rtc19_map RTC 19 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 19 Click driver.
 */

/**
 * @addtogroup rtc19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 19 Click to the selected MikroBUS.
 */
#define RTC19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.psw = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.intb = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.din = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.inta = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc19_map
/*! @} */ // rtc19

/**
 * @brief RTC 19 Click context object.
 * @details Context object definition of RTC 19 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t din;          /**< Digital SCHMITT TRIGGER pin. */

    // Input pins
    digital_in_t psw;           /**< Power switch indication pin. */
    digital_in_t intb;          /**< Active-Low interrupt B pin or Square-Wave clock pin. */
    digital_in_t inta;          /**< Active-Low interrupt A pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rtc19_t;

/**
 * @brief RTC 19 Click configuration object.
 * @details Configuration object definition of RTC 19 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t psw;             /**< Power switch indication pin. */
    pin_name_t intb;            /**< Active-Low interrupt B pin or Square-Wave clock pin. */
    pin_name_t din;             /**< Digital SCHMITT TRIGGER pin. */
    pin_name_t inta;            /**< Active-Low interrupt A pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} rtc19_cfg_t;

/**
 * @brief RTC 19 Click time object.
 * @details Time object definition of RTC 19 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint16_t sub_second;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc19_time_t;

/**
 * @brief RTC 19 Click date object.
 * @details Date object definition of RTC 19 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc19_date_t;

/**
 * @brief RTC 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC19_OK = 0,
    RTC19_ERROR = -1

} rtc19_return_value_t;

/*!
 * @addtogroup rtc19 RTC 19 Click Driver
 * @brief API for configuring and manipulating RTC 19 Click driver.
 * @{
 */

/**
 * @brief RTC 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc19_cfg_setup ( rtc19_cfg_t *cfg );

/**
 * @brief RTC 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_init ( rtc19_t *ctx, rtc19_cfg_t *cfg );

/**
 * @brief RTC 19 default configuration function.
 * @details This function executes a default configuration of RTC 19
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtc19_default_cfg ( rtc19_t *ctx );

/**
 * @brief RTC 19 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_generic_write ( rtc19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 19 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_generic_read ( rtc19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 19 write register function.
 * @details This function writes data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_write_register ( rtc19_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 19 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_read_register ( rtc19_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 19 set din pin function.
 * @details This function sets the DIN pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtc19_set_din_pin ( rtc19_t *ctx, uint8_t state );

/**
 * @brief RTC 19 get psw pin function.
 * @details This function returns the PSW pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc19_get_psw_pin ( rtc19_t *ctx );

/**
 * @brief RTC 19 get inta pin function.
 * @details This function returns the INTA pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc19_get_inta_pin ( rtc19_t *ctx );

/**
 * @brief RTC 19 get intb pin function.
 * @details This function returns the INTB pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc19_get_intb_pin ( rtc19_t *ctx );

/**
 * @brief RTC 19 set time function.
 * @details This function sets the starting time values - second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[in] time : Time object structure that carries second, minute and hour values in Decimal format.
 * See #rtc19_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_set_time ( rtc19_t *ctx, rtc19_time_t *time );

/**
 * @brief RTC 19 read time function.
 * @details This function reads the current time values - second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[out] time : Time object structure.
 * See #rtc19_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_read_time ( rtc19_t *ctx, rtc19_time_t *time );

/**
 * @brief RTC 19 set date function.
 * @details This function sets the starting date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[in] date : Date object structure that carries day of week, day, month and year values in Decimal format.
 * See #rtc19_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_set_date ( rtc19_t *ctx, rtc19_date_t *date );

/**
 * @brief RTC 19 read date function.
 * @details This function reads the current date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[out] date : Date object structure.
 * See #rtc19_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_read_date ( rtc19_t *ctx, rtc19_date_t *date );

/**
 * @brief RTC 19 reset device function.
 * @details This function performs the device reset by writing to the RTC_RESET register.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_reset_device ( rtc19_t *ctx );

/**
 * @brief RTC 19 clear interrupts function.
 * @details This function clears interrupts by reading the STATUS register.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc19_clear_interrupts ( rtc19_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RTC19_H

/*! @} */ // rtc19

// ------------------------------------------------------------------------ END
