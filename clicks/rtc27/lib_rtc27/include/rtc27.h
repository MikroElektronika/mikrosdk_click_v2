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
 * @file rtc27.h
 * @brief This file contains API for RTC 27 Click Driver.
 */

#ifndef RTC27_H
#define RTC27_H

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
 * @addtogroup rtc27 RTC 27 Click Driver
 * @brief API for configuring and manipulating RTC 27 Click driver.
 * @{
 */

/**
 * @defgroup rtc27_reg RTC 27 Registers List
 * @brief List of registers of RTC 27 Click driver.
 */

/**
 * @addtogroup rtc27_reg
 * @{
 */

/**
 * @brief RTC 27 register list.
 * @details Specified register list of RTC 27 Click driver.
 */
#define RTC27_REG_CONTROL_1             0x00
#define RTC27_REG_CONTROL_2             0x01
#define RTC27_REG_CONTROL_3             0x02
#define RTC27_REG_CONTROL_4             0x03
#define RTC27_REG_CONTROL_5             0x04
#define RTC27_REG_SR_RESET              0x05
#define RTC27_REG_100TH_SECONDS         0x06
#define RTC27_REG_SECONDS               0x07
#define RTC27_REG_MINUTES               0x08
#define RTC27_REG_HOURS                 0x09
#define RTC27_REG_DAYS                  0x0A
#define RTC27_REG_WEEKDAYS              0x0B
#define RTC27_REG_MONTHS                0x0C
#define RTC27_REG_YEARS                 0x0D
#define RTC27_REG_SECOND_ALARM          0x0E
#define RTC27_REG_MINUTE_ALARM          0x0F
#define RTC27_REG_HOUR_ALARM            0x10
#define RTC27_REG_DAY_ALARM             0x11
#define RTC27_REG_WEEKDAY_ALARM         0x12
#define RTC27_REG_MONTH_ALARM           0x13
#define RTC27_REG_YEAR_ALARM            0x14
#define RTC27_REG_CLKOUT_CTL            0x15
#define RTC27_REG_TIMESTP_CTL1          0x16
#define RTC27_REG_SEC_TIMESTP1          0x17
#define RTC27_REG_MIN_TIMESTP1          0x18
#define RTC27_REG_HOUR_TIMESTP1         0x19
#define RTC27_REG_DAY_TIMESTP1          0x1A
#define RTC27_REG_MON_TIMESTP1          0x1B
#define RTC27_REG_YEAR_TIMESTP1         0x1C
#define RTC27_REG_TIMESTP_CTL2          0x1D
#define RTC27_REG_SEC_TIMESTP2          0x1E
#define RTC27_REG_MIN_TIMESTP2          0x1F
#define RTC27_REG_HOUR_TIMESTP2         0x20
#define RTC27_REG_DAY_TIMESTP2          0x21
#define RTC27_REG_MON_TIMESTP2          0x22
#define RTC27_REG_YEAR_TIMESTP2         0x23
#define RTC27_REG_R_CODE1               0x24
#define RTC27_REG_R_CODE2               0x25
#define RTC27_REG_AGING_OFFSET_HIGH     0x26
#define RTC27_REG_AGING_OFFSET_LOW      0x27
#define RTC27_REG_INTA_MASK1            0x28
#define RTC27_REG_INTA_MASK2            0x29
#define RTC27_REG_INTB_MASK1            0x2A
#define RTC27_REG_INTB_MASK2            0x2B
#define RTC27_REG_WATCHDG_TIM_CTL       0x2C
#define RTC27_REG_WATCHDG_TIM_VAL       0x2D
#define RTC27_REG_TEMPERATURE           0x2E

/*! @} */ // rtc27_reg

/**
 * @defgroup rtc27_set RTC 27 Registers Settings
 * @brief Settings for registers of RTC 27 Click driver.
 */

/**
 * @addtogroup rtc27_set
 * @{
 */

/**
 * @brief RTC 27 CONTROL_1 register setting.
 * @details Specified setting for CONTROL_1 register of RTC 27 Click driver.
 */
#define RTC27_CONTROL_1_TC_DIS          0x40
#define RTC27_CONTROL_1_STOP_CLOCK      0x20
#define RTC27_CONTROL_1_100TH_S_DIS     0x10
#define RTC27_CONTROL_1_12_HOUR_MODE    0x04
#define RTC27_CONTROL_1_MINUTE_INT_EN   0x02
#define RTC27_CONTROL_1_SECOND_INT_EN   0x01
#define RTC27_CONTROL_1_FIXED_BITS      0x08

/**
 * @brief RTC 27 CONTROL_2 register setting.
 * @details Specified setting for CONTROL_2 register of RTC 27 Click driver.
 */
#define RTC27_CONTROL_2_MSF             0x80
#define RTC27_CONTROL_2_TI_TP           0x40
#define RTC27_CONTROL_2_WDTF            0x20
#define RTC27_CONTROL_2_AF              0x10
#define RTC27_CONTROL_2_OSFE_OFF        0x00
#define RTC27_CONTROL_2_OSFE_ON         0x04
#define RTC27_CONTROL_2_OSFE_VLF_ON     0x0C
#define RTC27_CONTROL_2_OSFE_MASK       0x0C
#define RTC27_CONTROL_2_AIE             0x02
#define RTC27_CONTROL_2_SMBUS_TIMEOUT   0x01

/**
 * @brief RTC 27 CONTROL_3 register setting.
 * @details Specified setting for CONTROL_3 register of RTC 27 Click driver.
 */
#define RTC27_CONTROL_3_PWRMNG_EN       0x00
#define RTC27_CONTROL_3_PWRMNG_EN_DIR   0x20
#define RTC27_CONTROL_3_PWRMNG_DIS      0x60
#define RTC27_CONTROL_3_PWRMNG_MASK     0x60
#define RTC27_CONTROL_3_BF              0x08
#define RTC27_CONTROL_3_OSIE            0x04
#define RTC27_CONTROL_3_BIE             0x02

/**
 * @brief RTC 27 SECONDS register setting.
 * @details Specified setting for SECONDS register of RTC 27 Click driver.
 */
#define RTC27_SECONDS_OSF               0x80
#define RTC27_SECONDS_SEC_MASK          0x7F

/**
 * @brief RTC 27 SR_RESET register setting.
 * @details Specified setting for SR_RESET register of RTC 27 Click driver.
 */
#define RTC27_SR_RESET_SOFT_RESET       0x2C
#define RTC27_SR_RESET_CLEAR_PRESCALER  0xA4
#define RTC27_SR_RESET_CLEAR_TIMESTAMP  0x25
#define RTC27_SR_RESET_READ             0x24

/**
 * @brief RTC 27 CLKOUT_CTL register setting.
 * @details Specified setting for CLKOUT_CTL register of RTC 27 Click driver.
 */
#define RTC27_CLKOUT_CTL_TCR_32_MIN     0x00
#define RTC27_CLKOUT_CTL_TCR_16_MIN     0x20
#define RTC27_CLKOUT_CTL_TCR_8_MIN      0x40
#define RTC27_CLKOUT_CTL_TCR_4_MIN      0x60
#define RTC27_CLKOUT_CTL_TCR_2_MIN      0x80
#define RTC27_CLKOUT_CTL_TCR_1_MIN      0xA0
#define RTC27_CLKOUT_CTL_TCR_MASK       0xE0
#define RTC27_CLKOUT_CTL_OTPR           0x10
#define RTC27_CLKOUT_CTL_CLKOE_INTB     0x00
#define RTC27_CLKOUT_CTL_CLKOE_CLKOUT   0x08
#define RTC27_CLKOUT_CTL_CLKOE_MASK     0x08
#define RTC27_CLKOUT_CTL_COF_32768      0x00
#define RTC27_CLKOUT_CTL_COF_16384      0x01
#define RTC27_CLKOUT_CTL_COF_8192       0x02
#define RTC27_CLKOUT_CTL_COF_4096       0x03
#define RTC27_CLKOUT_CTL_COF_2048       0x04
#define RTC27_CLKOUT_CTL_COF_1024       0x05
#define RTC27_CLKOUT_CTL_COF_1          0x06
#define RTC27_CLKOUT_CTL_COF_HIZ        0x07
#define RTC27_CLKOUT_CTL_COF_MASK       0x07

/**
 * @brief RTC 27 INTA_MASK1 and INTB_MASK1 register setting.
 * @details Specified setting for INTA_MASK1 and INTB_MASK1 register of RTC 27 Click driver.
 */
#define RTC27_INT_MASK1_MI              0x20
#define RTC27_INT_MASK1_SI              0x10
#define RTC27_INT_MASK1_OSIE            0x08
#define RTC27_INT_MASK1_AIE             0x04
#define RTC27_INT_MASK1_BIE             0x02
#define RTC27_INT_MASK1_WD_CD           0x01

/**
 * @brief RTC 27 INTA_MASK2 and INTB_MASK2 register setting.
 * @details Specified setting for INTA_MASK2 and INTB_MASK2 register of RTC 27 Click driver.
 */
#define RTC27_INT_MASK2_TSIE            0x08

/**
 * @brief RTC 27 day of week values.
 * @details Specified day of week values of RTC 27 Click driver.
 */
#define RTC27_MONDAY                    0x00
#define RTC27_TUESDAY                   0x01
#define RTC27_WEDNESDAY                 0x02
#define RTC27_THURSDAY                  0x03
#define RTC27_FRIDAY                    0x04
#define RTC27_SATURDAY                  0x05
#define RTC27_SUNDAY                    0x06

/**
 * @brief RTC 27 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 27 Click driver.
 */
#define RTC27_DEVICE_ADDRESS            0x51

/*! @} */ // rtc27_set

/**
 * @defgroup rtc27_map RTC 27 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 27 Click driver.
 */

/**
 * @addtogroup rtc27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 27 Click to the selected MikroBUS.
 */
#define RTC27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc27_map
/*! @} */ // rtc27

/**
 * @brief RTC 27 Click context object.
 * @details Context object definition of RTC 27 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rtc27_t;

/**
 * @brief RTC 27 Click configuration object.
 * @details Configuration object definition of RTC 27 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} rtc27_cfg_t;

/**
 * @brief RTC 27 Click time object.
 * @details Time object definition of RTC 27 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second_100th;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc27_time_t;

/**
 * @brief RTC 27 Click date object.
 * @details Date object definition of RTC 27 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc27_date_t;

/**
 * @brief RTC 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC27_OK = 0,
    RTC27_ERROR = -1

} rtc27_return_value_t;

/*!
 * @addtogroup rtc27 RTC 27 Click Driver
 * @brief API for configuring and manipulating RTC 27 Click driver.
 * @{
 */

/**
 * @brief RTC 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc27_cfg_setup ( rtc27_cfg_t *cfg );

/**
 * @brief RTC 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_init ( rtc27_t *ctx, rtc27_cfg_t *cfg );

/**
 * @brief RTC 27 default configuration function.
 * @details This function executes a default configuration of RTC 27
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtc27_default_cfg ( rtc27_t *ctx );

/**
 * @brief RTC 27 write registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register address of the RTC 27 device.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_write_regs ( rtc27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 27 read registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register address of the RTC 27 device.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_read_regs ( rtc27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 27 write register function.
 * @details This function writes a single data byte to the selected
 * register address of the RTC 27 device.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_write_reg ( rtc27_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 27 read register function.
 * @details This function reads a single data byte from the selected
 * register address of the RTC 27 device.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_read_reg ( rtc27_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 27 get INT pin state function.
 * @details This function returns the logical state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @return INT pin logic state (0 or 1).
 * @note None.
 */
uint8_t rtc27_get_int_pin ( rtc27_t *ctx );

/**
 * @brief RTC 27 communication check function.
 * @details This function checks the communication with the device by reading
 * the reset status register and validating its expected value.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_check_communication ( rtc27_t *ctx );

/**
 * @brief RTC 27 stop clock function.
 * @details This function stops the internal timekeeping clock by setting
 * the STOP bit in the control register.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_stop_clock ( rtc27_t *ctx );

/**
 * @brief RTC 27 start clock function.
 * @details This function starts the internal timekeeping clock by clearing
 * the STOP bit in the control register.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_start_clock ( rtc27_t *ctx );

/**
 * @brief RTC 27 clear prescaler function.
 * @details This function clears the internal prescaler by writing the
 * appropriate command to the status reset register.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_clear_prescaler ( rtc27_t *ctx );

/**
 * @brief RTC 27 clear MSF flag function.
 * @details This function clears the MSF (Minutes/Seconds Flag) bit in the
 * control register 2 to acknowledge and reset the flag state.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_clear_msf ( rtc27_t *ctx );

/**
 * @brief RTC 27 set time function.
 * @details This function sets the time registers with the provided time
 * structure values (hundredths of a second, seconds, minutes, hours).
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[in] time : Time data structure.
 * See #rtc27_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_set_time ( rtc27_t *ctx, rtc27_time_t *time );

/**
 * @brief RTC 27 read time function.
 * @details This function reads the time registers and updates the provided
 * time data structure with the current time values.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[out] time : Time data structure.
 * See #rtc27_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_read_time ( rtc27_t *ctx, rtc27_time_t *time );

/**
 * @brief RTC 27 set date function.
 * @details This function sets the date registers with the provided date
 * structure values (day, day of week, month, year).
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[in] date : Date data structure.
 * See #rtc27_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_set_date ( rtc27_t *ctx, rtc27_date_t *date );

/**
 * @brief RTC 27 read date function.
 * @details This function reads the date registers and updates the provided
 * date data structure with the current calendar values.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[out] date : Date data structure.
 * See #rtc27_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_read_date ( rtc27_t *ctx, rtc27_date_t *date );

/**
 * @brief RTC 27 set time and date function.
 * @details This function sets both time and date registers in a single
 * operation. It stops the clock, clears the prescaler, writes all time and
 * date fields, and then restarts the clock.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[in] time : Time data structure.
 * See #rtc27_time_t object definition for detailed explanation.
 * @param[in] date : Date data structure.
 * See #rtc27_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_set_time_date ( rtc27_t *ctx, rtc27_time_t *time, rtc27_date_t *date );

/**
 * @brief RTC 27 read time and date function.
 * @details This function reads both time and date registers in a single
 * operation and updates the provided time and date structures with the
 * current values.
 * @param[in] ctx : Click context object.
 * See #rtc27_t object definition for detailed explanation.
 * @param[out] time : Time data structure.
 * See #rtc27_time_t object definition for detailed explanation.
 * @param[out] date : Date data structure.
 * See #rtc27_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc27_read_time_date ( rtc27_t *ctx, rtc27_time_t *time, rtc27_date_t *date );

#ifdef __cplusplus
}
#endif
#endif // RTC27_H

/*! @} */ // rtc27

// ------------------------------------------------------------------------ END
