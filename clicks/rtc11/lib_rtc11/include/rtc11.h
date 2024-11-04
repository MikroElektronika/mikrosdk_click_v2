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
 * @file rtc11.h
 * @brief This file contains API for RTC 11 Click Driver.
 */

#ifndef RTC11_H
#define RTC11_H

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

/*!
 * @addtogroup rtc11 RTC 11 Click Driver
 * @brief API for configuring and manipulating RTC 11 Click driver.
 * @{
 */

/**
 * @defgroup rtc11_reg RTC 11 Registers List
 * @brief List of registers of RTC 11 Click driver.
 */

/**
 * @addtogroup rtc11_reg
 * @{
 */

/**
 * @brief RTC 11 description register.
 * @details Specified register for description of RTC 11 Click driver.
 */
#define RTC11_RD_BIT_MASK     0x7F
#define RTC11_WR_BIT_MASK     0x80

#define RTC11_REG_HDT         0x00
#define RTC11_REG_SEC         0x01
#define RTC11_REG_MIN         0x02
#define RTC11_REG_HRS         0x03
#define RTC11_REG_DAT         0x04
#define RTC11_REG_MON         0x05
#define RTC11_REG_YRS         0x06
#define RTC11_REG_WKD         0x07
#define RTC11_REG_ALA_HDT     0x08
#define RTC11_REG_ALA_SEC     0x09
#define RTC11_REG_ALA_MIN     0x0A
#define RTC11_REG_ALA_HRS     0x0B
#define RTC11_REG_ALA_DAT     0x0C
#define RTC11_REG_ALA_MON     0x0D
#define RTC11_REG_ALA_WKD     0x0E
#define RTC11_REG_STAT        0x0F
#define RTC11_REG_CTL1        0x10
#define RTC11_REG_CTL2        0x11
#define RTC11_REG_INT_MSK     0x12
#define RTC11_REG_SQW         0x13
#define RTC11_REG_CAL_XT      0x14
#define RTC11_REG_CAL_RC_HI   0x15
#define RTC11_REG_CAL_RC_LOW  0x16
#define RTC11_REG_INT_POL     0x17
#define RTC11_REG_TMR_CTL     0x18
#define RTC11_REG_TMR         0x19
#define RTC11_REG_TMR_INIT    0x1A
#define RTC11_REG_WDT         0x1B
#define RTC11_REG_OSC_CTL     0x1C
#define RTC11_REG_OSC_STAT    0x1D
#define RTC11_REG_CFG_KEY     0x1F
#define RTC11_REG_TRCK        0x20
#define RTC11_REG_BREF_CTL    0x21
#define RTC11_REG_BAT_MODE    0x27
#define RTC11_REG_ID_0        0x28
#define RTC11_REG_ID_1        0x29
#define RTC11_REG_ID_2        0x2A
#define RTC11_REG_ID_3        0x2B
#define RTC11_REG_ID_4        0x2C
#define RTC11_REG_ID_5        0x2D
#define RTC11_REG_ID_6        0x2E
#define RTC11_REG_ASTAT       0x2F
#define RTC11_REG_OCTRL       0x30
#define RTC11_REG_EXT_ADR     0x3F
#define RTC11_REG_RAM         0x40

/*! @} */ // rtc11_reg

/**
 * @defgroup rtc11_set RTC 11 Registers Settings
 * @brief Settings for registers of RTC 11 Click driver.
 */

/**
 * @addtogroup rtc11_set
 * @{
 */

/**
 * @brief RTC 11 description setting.
 * @details Specified setting for description of RTC 11 Click driver.
 */
#define RTC11_CTL1_STOP       0x80
#define RTC11_CTL1_12_HRS     0x40
#define RTC11_CTL1_OUTB       0x20
#define RTC11_CTL1_OUT        0x10
#define RTC11_CTL1_ARST       0x04
#define RTC11_CTL1_WRTC       0x01

#define RTC11_ACS_OSC_CTL     0xA1
#define RTC11_SW_RST          0x3C
#define RTC11_ACS_AN_CTL_REG  0x9D

#define RTC11_CEB             0x80
#define RTC11_BLIE            0x10
#define RTC11_TIE             0x08
#define RTC11_AIE             0x04
#define RTC11_EX2E            0x02
#define RTC11_EX1E            0x01

#define RTC11_PROP_DIS        0x00
#define RTC11_PROP_EN         0x01

/*! @} */ // rtc11_set

/**
 * @defgroup rtc11_map RTC 11 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 11 Click driver.
 */

/**
 * @addtogroup rtc11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 11 Click to the selected MikroBUS.
 */
#define RTC11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wdi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.exi = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.it2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.it1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc11_map
/*! @} */ // rtc11

/**
 * @brief RTC 11 Click context object.
 * @details Context object definition of RTC 11 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  wdi;       /**< Watchdog Timer Reset. */
    digital_out_t  exi;     /**< External Interrupt. */

    // Input pins
    digital_in_t  it2;       /**< Secondary Interrupt. */
    digital_in_t  it1;       /**< Primary Interrupt. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} rtc11_t;

/**
 * @brief RTC 11 Click configuration object.
 * @details Configuration object definition of RTC 11 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t   wdi;         /**< Watchdog Timer Reset. */
    pin_name_t  exi;        /**< External Interrupt. */
    pin_name_t  it2;        /**< Secondary Interrupt. */
    pin_name_t  it1;        /**< Primary Interrupt. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} rtc11_cfg_t;

/**
 * @brief RTC 11 Click time object.
 * @details Time object definition of RTC 12 Click driver.
 */
typedef struct 
{
    uint8_t hours; 
    uint8_t min;
    uint8_t sec; 
} rtc11_time_t;

/**
 * @brief RTC 11 Click date object.
 * @details Date object definition of RTC 12 Click driver.
 */
typedef struct 
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t day_of_week;
} rtc11_date_t;

/**
 * @brief RTC 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   RTC11_OK = 0,
   RTC11_ERROR = -1

} rtc11_return_value_t;

/*!
 * @addtogroup rtc11 RTC 11 Click Driver
 * @brief API for configuring and manipulating RTC 11 Click driver.
 * @{
 */

/**
 * @brief RTC 11 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc11_cfg_setup ( rtc11_cfg_t *cfg );

/**
 * @brief RTC 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc11_init ( rtc11_t *ctx, rtc11_cfg_t *cfg );

/**
 * @brief RTC 11 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] wr_data : Data to be written.
 * @param[in] n_len : Number of bytes to be written.
 * @return Nothing.
 */
void rtc11_generic_write ( rtc11_t *ctx, uint8_t reg, uint8_t *wr_data, uint16_t n_len );

/**
 * @brief RTC 11 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rd_data : Output read data.
 * @param[in] n_len : Number of bytes to be read.
 * @return Nothing.
 */
void rtc11_generic_read ( rtc11_t *ctx, uint8_t reg, uint8_t *rd_data, uint16_t n_len );

/**
 * @brief Check Interrupt 1 pin function
 * @details Function is used to check if an interrupt has occured.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Interrupt 1 pin state
 * @note Pin state depends on applied settings.
**/
uint8_t rtc11_check_irq_1 ( rtc11_t *ctx );

/**
 * @brief Check Interrupt 2 pin function
 * @details Function is used to check if an interrupt has occured.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Interrupt 2 pin state
 * @note Pin state depends on applied settings.
**/
uint8_t rtc11_check_irq_2 ( rtc11_t *ctx );

/**
 * @brief Watchdog reset function
 * @details Function is used to set the state of the 
 * Watchdog reset input pin.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value defines the state of the pin.
 * @return Nothing.
**/
void rtc11_wdi ( rtc11_t *ctx, uint8_t state );

/**
 * @brief External interrupt function
 * @details Function is used to set the state of the
 * External interrupt input pin.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value defines the state of the pin.
 * @return Nothing.
**/
void rtc11_ext_int ( rtc11_t *ctx, uint8_t state );

/**
 * @brief Set hundredths function
 * @details Function is used to set the hundredths of a second.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] hundredths : Value defines the hundredths of a second.
 * @return Nothing.
**/
void rtc11_set_time_hundredths ( rtc11_t *ctx, uint8_t hundredths );

/**
 * @brief Set seconds function
 * @details Function is used to set the seconds.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] seconds : Value defines seconds.
 * @return Nothing.
**/
void rtc11_set_time_seconds ( rtc11_t *ctx, uint8_t seconds );

/**
 * @brief Set minutes function
 * @details Function is used to set the minutes.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] minutes : Value defines minutes.
 * @return Nothing.
**/
void rtc11_set_time_minutes ( rtc11_t *ctx, uint8_t minutes );

/**
 * @brief Set hours function
 * @details Function is used to set the hours.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] hours : Value defines hours.
 * @return Nothing.
**/
void rtc11_set_time_hours ( rtc11_t *ctx, uint8_t hours );

/**
 * @brief Get hundredths function
 * @details Function is used to get the hundredths of a second.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value defines hundredths of a second.
**/
uint8_t rtc11_get_time_hundredths ( rtc11_t *ctx );

/**
 * @brief Get seconds function
 * @details Function is used to get the seconds.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value defines seconds.
**/
uint8_t rtc11_get_time_seconds ( rtc11_t *ctx );

/**
 * @brief Get minutes function
 * @details Function is used to get the minutes.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value defines minutes.
**/
uint8_t rtc11_get_time_minutes ( rtc11_t *ctx );

/**
 * @brief Get hours function
 * @details Function is used to get the hours.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value defines hours.
**/
uint8_t rtc11_get_time_hours ( rtc11_t *ctx );

/**
 * @brief Get day function
 * @details Function is used to get the days.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value defines days.
**/
uint8_t rtc11_get_date_day ( rtc11_t *ctx );

/**
 * @brief Set day function
 * @details Function is used to set the days.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] date_day : Value defines days.
 * @return Nothing.
**/
void rtc11_set_date_day ( rtc11_t *ctx, uint8_t date_day );

/**
 * @brief Get month function
 * @details Function is used to get the month
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value defines month.
**/
uint8_t rtc11_get_date_month ( rtc11_t *ctx );

/**
 * @brief Set month function
 * @details Function is used to set the month
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] date_mth : Value defines month.
 * @return Nothing.
**/
void rtc11_set_date_month ( rtc11_t *ctx, uint8_t date_mth );

/**
 * @brief Get year function
 * @details Function is used to get the year.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value defines year.
**/
uint8_t rtc11_get_date_year ( rtc11_t *ctx );

/**
 * @brief Set year function
 * @details Function is used to set the year.
 * @param[in] date_yrs value defines year.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Nothing.
**/
void rtc11_set_date_year ( rtc11_t *ctx, uint16_t date_yrs );

/**
 * @brief Get century flag function
 * @details Function is used to get the century flag.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value defines century flag.
**/
uint8_t rtc11_get_century_flag ( rtc11_t *ctx );

/**
 * @brief Get day of the week function
 * @details Function is used to get the day of the week.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return result value defines day of the week.
**/
uint8_t rtc11_get_day_of_the_week ( rtc11_t *ctx );

/**
 * @brief Set day of the week function
 * @details Function is used to set the day of the week.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] w_day value defines day of the week.
 * @return Nothing.
**/
void rtc11_set_day_of_the_week ( rtc11_t *ctx, uint8_t w_day );

/**
 * @brief Set alarm time hundredths function
 * @details Function is used to set alarm time hundredths of a second.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] hundredths : Value defines alarm time hundredths of a second.
 * @return Nothing.
**/
void rtc11_set_ala_time_hundredths ( rtc11_t *ctx, uint8_t hundredths );

/**
 * @brief Set alarm time seconds function
 * @details Function is used to set alarm time seconds.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] seconds : Value defines alarm time seconds.
 * @return Nothing.
**/
void rtc11_set_ala_time_seconds ( rtc11_t *ctx, uint8_t seconds );

/**
 * @brief Set alarm time minutes function
 * @details Function is used to set alarm time minutes.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] minutes : Value defines alarm time minutes.
 * @return Nothing.
**/
void rtc11_set_ala_time_minutes ( rtc11_t *ctx, uint8_t minutes );

/**
 * @brief Set alarm time hours function
 * @details Function is used to set alarm time hours.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] hours : Value defines alarm time hours.
 * @return Nothing.
**/
void rtc11_set_ala_time_hours ( rtc11_t *ctx, uint8_t hours );

/**
 * @brief Get alarm time hundredths function
 * @details Function is used to get the alarm time hundredths of a second.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value alarm time hundredths of a second.
**/
uint8_t rtc11_get_ala_time_hundredths ( rtc11_t *ctx );

/**
 * @brief Get alarm time seconds function
 * @details Function is used to get the alarm time seconds.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value alarm time seconds.
**/
uint8_t rtc11_get_ala_time_seconds ( rtc11_t *ctx );

/**
 * @brief Get alarm time minutes function
 * @details Function is used to get the alarm time minutes.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value alarm time minutes.
**/
uint8_t rtc11_get_ala_time_minutes ( rtc11_t *ctx );

/**
 * @brief Get alarm time hours function
 * @details Function is used to get the alarm time hours.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value alarm time hours.
**/
uint8_t rtc11_get_ala_time_hours ( rtc11_t *ctx );

/**
 * @brief Get alarm time days function
 * @details Function is used to get the alarm time days.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value alarm time days.
**/
uint8_t rtc11_get_ala_date_day ( rtc11_t *ctx );

/**
 * @brief Set alarm time day function
 * @details Function is used to set alarm time days.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] date_day : Value defines alarm time day.
 * @return Nothing.
**/
void rtc11_set_ala_date_day ( rtc11_t *ctx, uint8_t date_day );

/**
 * @brief Get alarm time month function
 * @details Function is used to get the alarm time month.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value alarm time month.
**/
uint8_t rtc11_get_ala_date_month ( rtc11_t *ctx );

/**
 * @brief Set alarm time month function
 * @details Function is used to set alarm time months.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] date_mth : Value defines alarm time month.
 * @return Nothing.
**/
void rtc11_set_ala_date_month ( rtc11_t *ctx, uint8_t date_mth );

/**
 * @brief Get alarm time day of the week function
 * @details Function is used to get the alarm time day of the week.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Result value alarm time day of the week.
**/
uint8_t rtc11_get_ala_day_of_the_week ( rtc11_t *ctx );

/**
 * @brief Set alarm time day of the week function
 * @details Function is used to set alarm time day of the week.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] w_day : Value defines alarm time day of the week.
 * @return Nothing.
**/
void rtc11_set_ala_day_of_the_week ( rtc11_t *ctx, uint8_t w_day );

/**
 * @brief Software Reset function
 * @details Function is used to perform software reset.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @return Nothing.
**/
void rtc11_soft_rst ( rtc11_t *ctx );

/**
 * @brief Set time hours, minutes and seconds function
 * @details Function is used to set system time.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] rtc_time : Time structure 
 * See #rtc11_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
**/
err_t rtc11_set_time ( rtc11_t *ctx, rtc11_time_t rtc_time );

/**
 * @brief Get time hours, minutes and seconds function
 * @details Function is used to get current system time.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[out] rtc_time : Time structure 
 * See #rtc11_time_t object definition for detailed explanation.
 * @return Nothing.
**/
void rtc11_get_time ( rtc11_t *ctx, rtc11_time_t *rtc_time );

/**
 * @brief Set date day of the week, day, month and year function
 * @details Function is used to set system date.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] rtc_date : Date structure 
 * See #rtc11_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
**/
err_t rtc11_set_date ( rtc11_t *ctx, rtc11_date_t rtc_date );

/**
 * @brief Get date day of the week, day, month and year function
 * @details Function is used to get system date.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[out] rtc_date : Date structure 
 * See #rtc11_date_t object definition for detailed explanation.
 * @return Nothing.
**/
void rtc11_get_date ( rtc11_t *ctx, rtc11_date_t *rtc_date );

/**
 * @brief Stop the clocking system function
 * @details Function is used to start or stop clocking system.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_stp_sys_slk ( rtc11_t *ctx, uint8_t state );

/**
 * @brief Auto reset enable function
 * @details Function is used to enable or disable auto reset interrupt flags.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_auto_rst ( rtc11_t *ctx, uint8_t state );

/**
 * @brief  Write RTC enable function
 * @details Function is used to enable or disable write to RTC.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_write_rtc ( rtc11_t *ctx, uint8_t state );

/**
 * @brief Century Enable function
 * @details Function is used to enable or disable 
 * Century Enable Interrupt.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_cen_en ( rtc11_t *ctx, uint8_t state );

/**
 * @brief Battery Low Interrupt Enable function
 * @details Function is used to enable or disable
 * Battery Low Interrupt.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_bat_low_int_en ( rtc11_t *ctx, uint8_t state );

/**
 * @brief Timer Interrupt Enable function
 * @details Function is used to enable or disable
 * Timer Interrupt.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_timer_int_en ( rtc11_t *ctx, uint8_t state );

/**
 * @brief Alarm Interrupt Enable function
 * @details Function is used to enable or disable
 * Alarm Interrupt.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_alarm_int_en ( rtc11_t *ctx, uint8_t state );

/**
 * @brief XT2 Interrupt Enable function
 * @details Function is used to enable or disable
 * XT2 Interrupt Enable.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_xt2_int_en ( rtc11_t *ctx, uint8_t state );

/**
 * @brief XT1 Interrupt Enable function
 * @details Function is used to enable or disable
 * XT1 Interrupt Enable.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_xt1_int_en ( rtc11_t *ctx, uint8_t state );

/**
 * @brief Batmode enable function
 * @details Function is used to enable or disable
 * the I/O interface when a Brownout Detection occurs.
 * @param[in] ctx : Click context object.
 * See #rtc11_t object definition for detailed explanation.
 * @param[in] state : Value enables or disables the property.
 * @return Nothing.
**/
void rtc11_bat_mode_en ( rtc11_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // RTC11_H

/*! @} */ // rtc11

// ------------------------------------------------------------------------ END
