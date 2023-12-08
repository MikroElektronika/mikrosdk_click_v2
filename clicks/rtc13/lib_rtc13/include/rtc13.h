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
 * @file rtc13.h
 * @brief This file contains API for RTC 13 Click Driver.
 */

#ifndef RTC13_H
#define RTC13_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup rtc13 RTC 13 Click Driver
 * @brief API for configuring and manipulating RTC 13 Click driver.
 * @{
 */

/**
 * @defgroup rtc13_reg RTC 13 Registers List
 * @brief List of registers of RTC 13 Click driver.
 */

/**
 * @addtogroup rtc13_reg
 * @{
 */

/**
 * @brief RTC 13 description register.
 * @details Specified register for description of RTC 13 Click driver.
 */
#define RTC13_REG_CTRL1_ADDR                           0x00
#define RTC13_REG_CTRL2_ADDR                           0x01
#define RTC13_REG_TIME_SECONDS                         0x02
#define RTC13_REG_TIME_MINUTES                         0x03
#define RTC13_REG_TIME_HOUR                            0x04
#define RTC13_REG_DATE_DAY                             0x05
#define RTC13_REG_DATE_WEEKDAYS                        0x06
#define RTC13_REG_DATE_MONTHS                          0x07
#define RTC13_REG_DATE_YEARS                           0x08
#define RTC13_REG_ALARM_MINUTE                         0x09
#define RTC13_REG_ALARM_HOUR                           0x0A
#define RTC13_REG_ALARM_DAY                            0x0B
#define RTC13_REG_ALARM_WEEKDAY                        0x0C
#define RTC13_REG_OFFSET_ADDR                          0x0D
#define RTC13_REG_TIMER_CLKOUT_ADDR                    0x0E
#define RTC13_REG_COUNTDOWN_TIMER_ADDR                 0x0F

/*! @} */ // rtc13_reg

/**
 * @defgroup rtc13_set RTC 13 Registers Settings
 * @brief Settings for registers of RTC 13 Click driver.
 */

/**
 * @addtogroup rtc13_set
 * @{
 */

/**
 * @brief RTC 13 description setting.
 * @details Specified setting for description of RTC 13 Click driver.
 */
#define RTC13_SOFT_RESET                               0x58
#define RTC13_BLOCK_CLKOUT_DISABLE                     0x00
#define RTC13_BLOCK_CLKOUT_ENABLE                      0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b rtc13_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define RTC13_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define RTC13_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // rtc13_set

/**
 * @defgroup rtc13_map RTC 13 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 13 Click driver.
 */

/**
 * @addtogroup rtc13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 13 Click to the selected MikroBUS.
 */
#define RTC13_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.cle = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc13_map
/*! @} */ // rtc13

/**
 * @brief RTC 13 Click time object.
 * @details Time object definition of RTC 13 Click driver.
 */
typedef struct 
{
    uint8_t hours; 
    uint8_t min;
    uint8_t sec; 
    
} rtc13_time_t;

/**
 * @brief RTC 13 Click date object.
 * @details Date object definition of RTC 13 Click driver.
 */
typedef struct 
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t weekday;

} rtc13_date_t;

/**
 * @brief RTC 13 Click alarm object.
 * @details Alarm object definition of RTC 13 Click driver.
 */
typedef struct 
{
    uint8_t min;
    uint8_t hours;
    uint8_t day;
    uint8_t weekday;
    
} rtc13_alarm_t;

/**
 * @brief RTC 13 Click context object.
 * @details Context object definition of RTC 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  cle;         /**< CLKOUT enable or disable pin. */

    // Input pins
    digital_in_t  int_pin;      /**< Interrupt pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} rtc13_t;

/**
 * @brief RTC 13 Click configuration object.
 * @details Configuration object definition of RTC 13 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;          /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;          /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;           /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;            /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  cle;           /**< CLKOUT enable or disable pin. */
    pin_name_t  int_pin;       /**< Interrupt pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} rtc13_cfg_t;

/**
 * @brief RTC 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   RTC13_OK = 0,
   RTC13_ERROR = -1

} rtc13_return_value_t;

/*!
 * @addtogroup rtc13 RTC 13 Click Driver
 * @brief API for configuring and manipulating RTC 13 Click driver.
 * @{
 */

/**
 * @brief RTC 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void rtc13_cfg_setup ( rtc13_cfg_t *cfg );

/**
 * @brief RTC 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_init ( rtc13_t *ctx, rtc13_cfg_t *cfg );

/**
 * @brief RTC 13 default configuration function.
 * @details This function executes a default configuration of RTC 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t rtc13_default_cfg ( rtc13_t *ctx );

/**
 * @brief RTC 13 get interrupt function.
 * @details This function check the interrupt state 
 * of the PCF2123 SPI Real time clock/calendar
 * on the RTC 13 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @return @li @c 0 - INT pin state low,,
 *         @li @c 1 - INT pin state high.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t rtc13_get_interrupt ( rtc13_t *ctx );

/**
 * @brief RTC 13 block CLKOUT function.
 * @details This function enable/disable block CLKOUT 
 * of the PCF2123 SPI Real time clock/calendar
 * on the RTC 13 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[in] en_clkout : 
 *         @li @c  0 - Disable block the CLKOUT.
 *         @li @c  1 - Enable  block the CLKOUT.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @note None.
 *
 * @endcode
 */
err_t rtc13_block_clkout ( rtc13_t *ctx, uint8_t en_clkout );

/**
 * @brief RTC 13 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_generic_write ( rtc13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 13 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_generic_read ( rtc13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 13 soft reset function.
 * @details This function performs a software reset 
 * of the PCF2123 SPI Real time clock/calendar
 * on the RTC 13 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_soft_reset ( rtc13_t *ctx );

/**
 * @brief RTC 13 get time function.
 * @details This function get RTC time data structure
 * of the PCF2123 SPI Real time clock/calendar
 * on the RTC 13 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[out] rtc_time : Pointer of the RTC time structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_get_time ( rtc13_t *ctx, rtc13_time_t *rtc_time );

/**
 * @brief RTC 13 set time function.
 * @details This function set RTC time data structure
 * of the PCF2123 SPI Real time clock/calendar
 * on the RTC 13 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[in] rtc_time : RTC time structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_set_time ( rtc13_t *ctx, rtc13_time_t rtc_time );

/**
 * @brief RTC 13 get date function.
 * @details This function get RTC date data structure
 * of the PCF2123 SPI Real time clock/calendar
 * on the RTC 13 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[out] rtc_date : Pointer of the RTC date data structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_get_date ( rtc13_t *ctx, rtc13_date_t *rtc_date );

/**
 * @brief RTC 13 set date function.
 * @details This function set RTC date data structure
 * of the PCF2123 SPI Real time clock/calendar
 * on the RTC 13 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[in] rtc_date : RTC date structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_set_date ( rtc13_t *ctx, rtc13_date_t rtc_date );

/**
 * @brief RTC 13 get alarm function.
 * @details This function get RTC alarm data structure
 * of the PCF2123 SPI Real time clock/calendar
 * on the RTC 13 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[out] rtc_alarm : Pointer of the RTC alarm data structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_get_alarm ( rtc13_t *ctx, rtc13_alarm_t *rtc_alarm );

/**
 * @brief RTC 13 set alarm function.
 * @details This function set RTC alarm data structure
 * of the PCF2123 SPI Real time clock/calendar
 * on the RTC 13 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc13_t object definition for detailed explanation.
 * @param[in] rtc_alarm : RTC alarm structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc13_set_alarm ( rtc13_t *ctx, rtc13_alarm_t rtc_alarm );

#ifdef __cplusplus
}
#endif
#endif // RTC13_H

/*! @} */ // rtc13

// ------------------------------------------------------------------------ END
