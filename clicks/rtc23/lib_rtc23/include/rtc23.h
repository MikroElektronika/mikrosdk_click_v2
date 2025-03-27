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
 * @file rtc23.h
 * @brief This file contains API for RTC 23 Click Driver.
 */

#ifndef RTC23_H
#define RTC23_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup rtc23 RTC 23 Click Driver
 * @brief API for configuring and manipulating RTC 23 Click driver.
 * @{
 */

/**
 * @defgroup rtc23_reg RTC 23 Registers List
 * @brief List of registers of RTC 23 Click driver.
 */

/**
 * @addtogroup rtc23_reg
 * @{
 */

/**
 * @brief RTC 23 register list.
 * @details Specified register list of RTC 23 Click driver.
 */
#define RTC23_REG_HUNDREDTHS                        0x00
#define RTC23_REG_SECONDS                           0x01
#define RTC23_REG_MINUTES                           0x02
#define RTC23_REG_HOURS                             0x03
#define RTC23_REG_DATE                              0x04
#define RTC23_REG_MONTHS                            0x05
#define RTC23_REG_YEARS                             0x06
#define RTC23_REG_WEEKDAYS                          0x07
#define RTC23_REG_HUNDREDTHS_ALARM                  0x08
#define RTC23_REG_SECONDS_ALARM                     0x09
#define RTC23_REG_MINUTES_ALARM                     0x0A
#define RTC23_REG_HOURS_ALARM                       0x0B
#define RTC23_REG_DATE_ALARM                        0x0C
#define RTC23_REG_MONTHS_ALARM                      0x0D
#define RTC23_REG_WEEKDAYS_ALARM                    0x0E
#define RTC23_REG_STATUS                            0x0F
#define RTC23_REG_CONTROL1                          0x10
#define RTC23_REG_CONTROL2                          0x11
#define RTC23_REG_INT_MASK                          0x12
#define RTC23_REG_SQW                               0x13
#define RTC23_REG_CAL_XT                            0x14
#define RTC23_REG_CAL_RC_HI                         0x15
#define RTC23_REG_CAL_RC_LOW                        0x16
#define RTC23_REG_SLEEP_CONTROL                     0x17
#define RTC23_REG_TIMER_CONTROL                     0x18
#define RTC23_REG_TIMER                             0x19
#define RTC23_REG_TIMER_INITIAL                     0x1A
#define RTC23_REG_WDT                               0x1B
#define RTC23_REG_OSC_CONTROL                       0x1C
#define RTC23_REG_OSC_STATUS                        0x1D
#define RTC23_REG_CONFIGURATION_KEY                 0x1F
#define RTC23_REG_TRICKLE                           0x20
#define RTC23_REG_BREF_CONTROL                      0x21
#define RTC23_REG_AFCTRL                            0x26
#define RTC23_REG_BATMODE_IO                        0x27
#define RTC23_REG_ID0                               0x28
#define RTC23_REG_ID1                               0x29
#define RTC23_REG_ID2                               0x2A
#define RTC23_REG_ID3                               0x2B
#define RTC23_REG_ID4                               0x2C
#define RTC23_REG_ID5                               0x2D
#define RTC23_REG_ID6                               0x2E
#define RTC23_REG_ASTAT                             0x2F
#define RTC23_REG_OCTRL                             0x30
#define RTC23_REG_EXTENSION_ADDRESS                 0x3F
#define RTC23_REG_RAM                               0x40

/*! @} */ // rtc23_reg

/**
 * @defgroup rtc23_set RTC 23 Registers Settings
 * @brief Settings for registers of RTC 23 Click driver.
 */

/**
 * @addtogroup rtc23_set
 * @{
 */

/**
 * @brief RTC 23 day of week values.
 * @details Specified day of week values of RTC 23 Click driver.
 */
#define RTC23_MONDAY                                0x00
#define RTC23_TUESDAY                               0x01
#define RTC23_WEDNESDAY                             0x02
#define RTC23_THURSDAY                              0x03
#define RTC23_FRIDAY                                0x04
#define RTC23_SATURDAY                              0x05
#define RTC23_SUNDAY                                0x06

/**
 * @brief RTC 23 device ID value.
 * @details Specified device ID value of RTC 23 Click driver.
 */
#define RTC23_DEVICE_ID                             0x18

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b rtc23_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define RTC23_SET_DATA_SAMPLE_EDGE                  SET_SPI_DATA_SAMPLE_EDGE
#define RTC23_SET_DATA_SAMPLE_MIDDLE                SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // rtc23_set

/**
 * @defgroup rtc23_map RTC 23 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 23 Click driver.
 */

/**
 * @addtogroup rtc23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 23 Click to the selected MikroBUS.
 */
#define RTC23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.psw = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.wdi = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc23_map
/*! @} */ // rtc23

/**
 * @brief RTC 23 Click context object.
 * @details Context object definition of RTC 23 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wdi;          /**< Watchdog reset pin. */

    // Input pins
    digital_in_t psw;           /**< INT 2 or power switch pin. */
    digital_in_t int_pin;       /**< INT 1 or function pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} rtc23_t;

/**
 * @brief RTC 23 Click configuration object.
 * @details Configuration object definition of RTC 23 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wdi;             /**< Watchdog reset pin. */
    pin_name_t psw;             /**< INT 2 or power switch pin. */
    pin_name_t int_pin;         /**< INT 1 or function pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} rtc23_cfg_t;

/**
 * @brief RTC 23 Click time object.
 * @details Time object definition of RTC 23 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second_100th;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc23_time_t;

/**
 * @brief RTC 23 Click date object.
 * @details Date object definition of RTC 23 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc23_date_t;

/**
 * @brief RTC 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC23_OK = 0,
    RTC23_ERROR = -1

} rtc23_return_value_t;

/*!
 * @addtogroup rtc23 RTC 23 Click Driver
 * @brief API for configuring and manipulating RTC 23 Click driver.
 * @{
 */

/**
 * @brief RTC 23 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc23_cfg_setup ( rtc23_cfg_t *cfg );

/**
 * @brief RTC 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_init ( rtc23_t *ctx, rtc23_cfg_t *cfg );

/**
 * @brief RTC 23 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_write_regs ( rtc23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 23 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_read_regs ( rtc23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 23 write reg function.
 * @details This function writes a data byte to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_write_reg ( rtc23_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 23 read reg function.
 * @details This function reads a data byte from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_read_reg ( rtc23_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 23 set WDI pin function.
 * @details This function sets the watchdog reset (WDI) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtc23_set_wdi_pin ( rtc23_t *ctx, uint8_t state );

/**
 * @brief RTC 23 get PSW pin function.
 * @details This function returns the power switch (PSW) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc23_get_psw_pin ( rtc23_t *ctx );

/**
 * @brief RTC 23 get INT pin function.
 * @details This function returns the interrupt (INT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc23_get_int_pin ( rtc23_t *ctx );

/**
 * @brief RTC 23 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_check_communication ( rtc23_t *ctx );

/**
 * @brief RTC 23 set time function.
 * @details This function sets the starting time values - second 100th, second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[in] time : Time object structure that carries second 100th, second, minute and hour values in Decimal format.
 * See #rtc23_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_set_time ( rtc23_t *ctx, rtc23_time_t *time );

/**
 * @brief RTC 23 read time function.
 * @details This function reads the current time values - second 100th, second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[out] time : Time object structure.
 * See #rtc23_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_read_time ( rtc23_t *ctx, rtc23_time_t *time );

/**
 * @brief RTC 23 set date function.
 * @details This function sets the starting date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[in] date : Date object structure that carries day of week, day, month and year values in Decimal format.
 * See #rtc23_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_set_date ( rtc23_t *ctx, rtc23_date_t *date );

/**
 * @brief RTC 23 read date function.
 * @details This function reads the current date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[out] date : Date object structure.
 * See #rtc23_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc23_read_date ( rtc23_t *ctx, rtc23_date_t *date );

#ifdef __cplusplus
}
#endif
#endif // RTC23_H

/*! @} */ // rtc23

// ------------------------------------------------------------------------ END
