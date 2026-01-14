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
 * @file rtc25.h
 * @brief This file contains API for RTC 25 Click Driver.
 */

#ifndef RTC25_H
#define RTC25_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup rtc25 RTC 25 Click Driver
 * @brief API for configuring and manipulating RTC 25 Click driver.
 * @{
 */

/**
 * @defgroup rtc25_reg RTC 25 Registers List
 * @brief List of registers of RTC 25 Click driver.
 */

/**
 * @addtogroup rtc25_reg
 * @{
 */

/**
 * @brief RTC 25 register list.
 * @details Specified register list of RTC 25 Click driver.
 */
#define RTC25_REG_CONTROL_1             0x00
#define RTC25_REG_CONTROL_2             0x01
#define RTC25_REG_CONTROL_3             0x02
#define RTC25_REG_CONTROL_4             0x03
#define RTC25_REG_CONTROL_5             0x04
#define RTC25_REG_SR_RESET              0x05
#define RTC25_REG_100TH_SECONDS         0x06
#define RTC25_REG_SECONDS               0x07
#define RTC25_REG_MINUTES               0x08
#define RTC25_REG_HOURS                 0x09
#define RTC25_REG_DAYS                  0x0A
#define RTC25_REG_WEEKDAYS              0x0B
#define RTC25_REG_MONTHS                0x0C
#define RTC25_REG_YEARS                 0x0D
#define RTC25_REG_SECOND_ALARM          0x0E
#define RTC25_REG_MINUTE_ALARM          0x0F
#define RTC25_REG_HOUR_ALARM            0x10
#define RTC25_REG_DAY_ALARM             0x11
#define RTC25_REG_WEEKDAY_ALARM         0x12
#define RTC25_REG_CLKOUT_CTL            0x13
#define RTC25_REG_TIMESTP_CTL1          0x14
#define RTC25_REG_SEC_TIMESTP1          0x15
#define RTC25_REG_MIN_TIMESTP1          0x16
#define RTC25_REG_HOUR_TIMESTP1         0x17
#define RTC25_REG_DAY_TIMESTP1          0x18
#define RTC25_REG_MON_TIMESTP1          0x19
#define RTC25_REG_YEAR_TIMESTP1         0x1A
#define RTC25_REG_TIMESTP_CTL2          0x1B
#define RTC25_REG_SEC_TIMESTP2          0x1C
#define RTC25_REG_MIN_TIMESTP2          0x1D
#define RTC25_REG_HOUR_TIMESTP2         0x1E
#define RTC25_REG_DAY_TIMESTP2          0x1F
#define RTC25_REG_MON_TIMESTP2          0x20
#define RTC25_REG_YEAR_TIMESTP2         0x21
#define RTC25_REG_TIMESTP_CTL3          0x22
#define RTC25_REG_SEC_TIMESTP3          0x23
#define RTC25_REG_MIN_TIMESTP3          0x24
#define RTC25_REG_HOUR_TIMESTP3         0x25
#define RTC25_REG_DAY_TIMESTP3          0x26
#define RTC25_REG_MON_TIMESTP3          0x27
#define RTC25_REG_YEAR_TIMESTP3         0x28
#define RTC25_REG_TIMESTP_CTL4          0x29
#define RTC25_REG_SEC_TIMESTP4          0x2A
#define RTC25_REG_MIN_TIMESTP4          0x2B
#define RTC25_REG_HOUR_TIMESTP4         0x2C
#define RTC25_REG_DAY_TIMESTP4          0x2D
#define RTC25_REG_MON_TIMESTP4          0x2E
#define RTC25_REG_YEAR_TIMESTP4         0x2F
#define RTC25_REG_AGING_OFFSET          0x30
#define RTC25_REG_INT_A_MASK1           0x31
#define RTC25_REG_INT_A_MASK2           0x32
#define RTC25_REG_INT_B_MASK1           0x33
#define RTC25_REG_INT_B_MASK2           0x34
#define RTC25_REG_WATCHDG_TIM_CTL       0x35
#define RTC25_REG_WATCHDG_TIM_VAL       0x36

/*! @} */ // rtc25_reg

/**
 * @defgroup rtc25_set RTC 25 Registers Settings
 * @brief Settings for registers of RTC 25 Click driver.
 */

/**
 * @addtogroup rtc25_set
 * @{
 */

/**
 * @brief RTC 25 CONTROL_1 register setting.
 * @details Specified setting for CONTROL_1 register of RTC 25 Click driver.
 */
#define RTC25_CONTROL_1_TC_DIS          0x40
#define RTC25_CONTROL_1_STOP_CLOCK      0x20
#define RTC25_CONTROL_1_100TH_S_DIS     0x10
#define RTC25_CONTROL_1_12_HOUR_MODE    0x04
#define RTC25_CONTROL_1_MINUTE_INT_EN   0x02
#define RTC25_CONTROL_1_SECOND_INT_EN   0x01
#define RTC25_CONTROL_1_FIXED_BITS      0x08

/**
 * @brief RTC 25 CONTROL_2 register setting.
 * @details Specified setting for CONTROL_2 register of RTC 25 Click driver.
 */
#define RTC25_CONTROL_2_MSF             0x80
#define RTC25_CONTROL_2_WDTF            0x40
#define RTC25_CONTROL_2_AF              0x10
#define RTC25_CONTROL_2_AIE             0x02

/**
 * @brief RTC 25 SECONDS register setting.
 * @details Specified setting for SECONDS register of RTC 25 Click driver.
 */
#define RTC25_SECONDS_OSF               0x80
#define RTC25_SECONDS_SEC_MASK          0x7F

/**
 * @brief RTC 25 SR_RESET register setting.
 * @details Specified setting for SR_RESET register of RTC 25 Click driver.
 */
#define RTC25_SR_RESET_SOFT_RESET       0x2C
#define RTC25_SR_RESET_CLEAR_PRESCALER  0xA4
#define RTC25_SR_RESET_CLEAR_TIMESTAMP  0x25
#define RTC25_SR_RESET_READ             0x24

/**
 * @brief RTC 25 INT_A_MASK1 and INT_B_MASK1 register setting.
 * @details Specified setting for INT_A_MASK1 and INT_B_MASK1 register of RTC 25 Click driver.
 */
#define RTC25_INT_MASK1_MI              0x20
#define RTC25_INT_MASK1_SI              0x10
#define RTC25_INT_MASK1_WD_CD           0x08
#define RTC25_INT_MASK1_AIE             0x04
#define RTC25_INT_MASK1_BIE             0x02
#define RTC25_INT_MASK1_BLIE            0x01

/**
 * @brief RTC 25 INT_A_MASK2 and INT_B_MASK2 register setting.
 * @details Specified setting for INT_A_MASK2 and INT_B_MASK2 register of RTC 25 Click driver.
 */
#define RTC25_INT_MASK2_TSIE1           0x08
#define RTC25_INT_MASK2_TSIE2           0x04
#define RTC25_INT_MASK2_TSIE3           0x02
#define RTC25_INT_MASK2_TSIE4           0x01

/**
 * @brief RTC 25 day of week values.
 * @details Specified day of week values of RTC 25 Click driver.
 */
#define RTC25_MONDAY                    0x00
#define RTC25_TUESDAY                   0x01
#define RTC25_WEDNESDAY                 0x02
#define RTC25_THURSDAY                  0x03
#define RTC25_FRIDAY                    0x04
#define RTC25_SATURDAY                  0x05
#define RTC25_SUNDAY                    0x06

/**
 * @brief RTC 25 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 25 Click driver.
 */
#define RTC25_DEVICE_ADDRESS            0x53

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b rtc25_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define RTC25_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define RTC25_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // rtc25_set

/**
 * @defgroup rtc25_map RTC 25 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 25 Click driver.
 */

/**
 * @addtogroup rtc25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 25 Click to the selected MikroBUS.
 */
#define RTC25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ts3  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ts4  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc25_map
/*! @} */ // rtc25

/**
 * @brief RTC 25 Click driver selector.
 * @details Selects target driver interface of RTC 25 Click driver.
 */
typedef enum
{
    RTC25_DRV_SEL_SPI,                  /**< SPI driver descriptor. */
    RTC25_DRV_SEL_I2C                   /**< I2C driver descriptor. */

} rtc25_drv_t;

/**
 * @brief RTC 25 Click driver interface.
 * @details Definition of driver interface of RTC 25 Click driver.
 */
struct rtc25_s;
typedef err_t ( *rtc25_master_io_t )( struct rtc25_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief RTC 25 Click context object.
 * @details Context object definition of RTC 25 Click driver.
 */
typedef struct rtc25_s
{
    digital_out_t ts3;                  /**< Timestamp 3 pin. */
    digital_out_t ts4;                  /**< Timestamp 4 pin. */

    digital_in_t int_pin;               /**< Interrupt pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    rtc25_drv_t drv_sel;                /**< Master driver interface selector. */

    rtc25_master_io_t write_f;          /**< Master write function. */
    rtc25_master_io_t read_f;           /**< Master read function. */

} rtc25_t;

/**
 * @brief RTC 25 Click configuration object.
 * @details Configuration object definition of RTC 25 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t ts3;                     /**< Timestamp 3 pin. */
    pin_name_t ts4;                     /**< Timestamp 4 pin. */
    pin_name_t int_pin;                 /**< Interrupt pin. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    rtc25_drv_t drv_sel;                /**< Master driver interface selector. */

} rtc25_cfg_t;

/**
 * @brief RTC 25 Click time object.
 * @details Time object definition of RTC 25 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second_100th;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc25_time_t;

/**
 * @brief RTC 25 Click date object.
 * @details Date object definition of RTC 25 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc25_date_t;

/**
 * @brief RTC 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC25_OK = 0,
    RTC25_ERROR = -1

} rtc25_return_value_t;

/*!
 * @addtogroup rtc25 RTC 25 Click Driver
 * @brief API for configuring and manipulating RTC 25 Click driver.
 * @{
 */

/**
 * @brief RTC 25 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc25_cfg_setup ( rtc25_cfg_t *cfg );

/**
 * @brief RTC 25 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #rtc25_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #rtc25_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void rtc25_drv_interface_sel ( rtc25_cfg_t *cfg, rtc25_drv_t drv_sel );

/**
 * @brief RTC 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_init ( rtc25_t *ctx, rtc25_cfg_t *cfg );

/**
 * @brief RTC 25 default configuration function.
 * @details This function executes a default configuration of RTC 25
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtc25_default_cfg ( rtc25_t *ctx );

/**
 * @brief RTC 25 write registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register address of the RTC 25 device.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_write_regs ( rtc25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 25 read registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register address of the RTC 25 device.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_read_regs ( rtc25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 25 write register function.
 * @details This function writes a single data byte to the selected
 * register address of the RTC 25 device.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_write_reg ( rtc25_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 25 read register function.
 * @details This function reads a single data byte from the selected
 * register address of the RTC 25 device.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_read_reg ( rtc25_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 25 set TS3 pin state function.
 * @details This function sets the TS3 pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] state : Logic state of the TS3 pin (0 or 1).
 * @return None.
 * @note None.
 */
void rtc25_set_ts3_pin ( rtc25_t *ctx, uint8_t state );

/**
 * @brief RTC 25 set TS4 pin state function.
 * @details This function sets the TS4 pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] state : Logic state of the TS4 pin (0 or 1).
 * @return None.
 * @note None.
 */
void rtc25_set_ts4_pin ( rtc25_t *ctx, uint8_t state );

/**
 * @brief RTC 25 get INT pin state function.
 * @details This function returns the logical state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @return INT pin logic state (0 or 1).
 * @note None.
 */
uint8_t rtc25_get_int_pin ( rtc25_t *ctx );

/**
 * @brief RTC 25 communication check function.
 * @details This function checks the communication with the device by reading
 * the reset status register and validating its expected value.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_check_communication ( rtc25_t *ctx );

/**
 * @brief RTC 25 stop clock function.
 * @details This function stops the internal timekeeping clock by setting
 * the STOP bit in the control register.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_stop_clock ( rtc25_t *ctx );

/**
 * @brief RTC 25 start clock function.
 * @details This function starts the internal timekeeping clock by clearing
 * the STOP bit in the control register.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_start_clock ( rtc25_t *ctx );

/**
 * @brief RTC 25 clear prescaler function.
 * @details This function clears the internal prescaler by writing the
 * appropriate command to the status reset register.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_clear_prescaler ( rtc25_t *ctx );

/**
 * @brief RTC 25 clear MSF flag function.
 * @details This function clears the MSF (Minutes/Seconds Flag) bit in the
 * control register 2 to acknowledge and reset the flag state.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_clear_msf ( rtc25_t *ctx );

/**
 * @brief RTC 25 set time function.
 * @details This function sets the time registers with the provided time
 * structure values (hundredths of a second, seconds, minutes, hours).
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] time : Time data structure.
 * See #rtc25_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_set_time ( rtc25_t *ctx, rtc25_time_t *time );

/**
 * @brief RTC 25 read time function.
 * @details This function reads the time registers and updates the provided
 * time data structure with the current time values.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[out] time : Time data structure.
 * See #rtc25_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_read_time ( rtc25_t *ctx, rtc25_time_t *time );

/**
 * @brief RTC 25 set date function.
 * @details This function sets the date registers with the provided date
 * structure values (day, day of week, month, year).
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] date : Date data structure.
 * See #rtc25_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_set_date ( rtc25_t *ctx, rtc25_date_t *date );

/**
 * @brief RTC 25 read date function.
 * @details This function reads the date registers and updates the provided
 * date data structure with the current calendar values.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[out] date : Date data structure.
 * See #rtc25_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_read_date ( rtc25_t *ctx, rtc25_date_t *date );

/**
 * @brief RTC 25 set time and date function.
 * @details This function sets both time and date registers in a single
 * operation. It stops the clock, clears the prescaler, writes all time and
 * date fields, and then restarts the clock.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[in] time : Time data structure.
 * See #rtc25_time_t object definition for detailed explanation.
 * @param[in] date : Date data structure.
 * See #rtc25_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_set_time_date ( rtc25_t *ctx, rtc25_time_t *time, rtc25_date_t *date );

/**
 * @brief RTC 25 read time and date function.
 * @details This function reads both time and date registers in a single
 * operation and updates the provided time and date structures with the
 * current values.
 * @param[in] ctx : Click context object.
 * See #rtc25_t object definition for detailed explanation.
 * @param[out] time : Time data structure.
 * See #rtc25_time_t object definition for detailed explanation.
 * @param[out] date : Date data structure.
 * See #rtc25_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc25_read_time_date ( rtc25_t *ctx, rtc25_time_t *time, rtc25_date_t *date );

#ifdef __cplusplus
}
#endif
#endif // RTC25_H

/*! @} */ // rtc25

// ------------------------------------------------------------------------ END
