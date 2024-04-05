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
 * @file rtc12.h
 * @brief This file contains API for RTC 12 Click Driver.
 */

#ifndef RTC12_H
#define RTC12_H

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
 * @addtogroup rtc12 RTC 12 Click Driver
 * @brief API for configuring and manipulating RTC 12 Click driver.
 * @{
 */

/**
 * @defgroup rtc12_reg RTC 12 Registers List
 * @brief List of registers of RTC 12 Click driver.
 */

/**
 * @addtogroup rtc12_reg
 * @{
 */

/**
 * @brief RTC 12 description register.
 * @details Specified register for description of RTC 12 Click driver.
 */
#define RTC12_REG_SECONDS                     0x00
#define RTC12_REG_MINUTES                     0x01
#define RTC12_REG_HOUR                        0x02
#define RTC12_REG_DAY                         0x03
#define RTC12_REG_DATE                        0x04
#define RTC12_REG_MONTH                       0x05
#define RTC12_REG_YEAR                        0x06
#define RTC12_REG_ALARM_0_SECONDS             0x07
#define RTC12_REG_ALARM_0_MINUTES             0x08
#define RTC12_REG_ALARM_0_HOUR                0x09
#define RTC12_REG_ALARM_0_DAY                 0x0A
#define RTC12_REG_ALARM_1_SECONDS             0x0B
#define RTC12_REG_ALARM_1_MINUTES             0x0C
#define RTC12_REG_ALARM_1_HOUR                0x0D
#define RTC12_REG_ALARM_1_DAY                 0x0E
#define RTC12_REG_CONTROL                     0x0F
#define RTC12_REG_STATUS                      0x10
#define RTC12_REG_TRICKLE_CHARGER             0x11

/*! @} */ // rtc12_reg

/**
 * @defgroup rtc12_set RTC 12 Registers Settings
 * @brief Settings for registers of RTC 12 Click driver.
 */

/**
 * @addtogroup rtc12_set
 * @{
 */

/**
 * @brief RTC 12 description setting.
 * @details Specified setting for description of RTC 12 Click driver.
 */
#define RTC12_SET_EOSC_ENABLE                 0x00
#define RTC12_SET_EOSC_DISABLE                0x01
#define RTC12_SET_DOSF_ENABLE                 0x00
#define RTC12_SET_DOSF_DISABL                 0x01
#define RTC12_SET_EGFIL_DISABLE               0x00
#define RTC12_SET_EGFIL_ENABLE                0x01
#define RTC12_SET_SQW_DISABLE                 0x00
#define RTC12_SET_SQW_ENABLE                  0x01
#define RTC12_SET_INTCN_A0IE                  0x00
#define RTC12_SET_INTCN_A0IE_A1IE             0x01
#define RTC12_SET_ALARM_1_DISABLE             0x00
#define RTC12_SET_ALARM_1_ENABLE              0x01
#define RTC12_SET_ALARM_0_DISABLE             0x00
#define RTC12_SET_ALARM_0_ENABLE              0x01


/*! @} */ // rtc12_set

/**
 * @defgroup rtc12_map RTC 12 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 12 Click driver.
 */

/**
 * @addtogroup rtc12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 12 Click to the selected MikroBUS.
 */
#define RTC12_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.pf = MIKROBUS( mikrobus, MIKROBUS_AN );     \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc12_map
/*! @} */ // rtc12

/**
 * @brief RTC 12 Click context object.
 * @details Context object definition of RTC 12 Click driver.
 */
typedef struct
{
    // Input pins

    digital_in_t  pf;         /**< Power-Fail pin. */
    digital_in_t  int_pin;    /**< Interrupt pin.  */

    // Modules

    spi_master_t  spi;        /**< SPI driver object. */

    pin_name_t  chip_select;  /**< Chip select pin descriptor (used for SPI driver). */

} rtc12_t;

/**
 * @brief RTC 12 Click configuration object.
 * @details Configuration object definition of RTC 12 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;        /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;        /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;         /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;          /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t  pf;          /**< Power-Fail pin. */
    pin_name_t  int_pin;     /**< Interrupt pin.  */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} rtc12_cfg_t;

/**
 * @brief RTC 12 Click time object.
 * @details Time object definition of RTC 12 Click driver.
 */
typedef struct 
{
    uint8_t hours; 
    uint8_t min;
    uint8_t sec; 
    
} rtc12_time_t;

/**
 * @brief RTC 12 Click date object.
 * @details Date object definition of RTC 12 Click driver.
 */
typedef struct 
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t day_of_week;
    

} rtc12_date_t;

/**
 * @brief RTC 12 Click alarm object.
 * @details Alarm object definition of RTC 12 Click driver.
 */
typedef struct 
{
    uint8_t day;
    uint8_t hours; 
    uint8_t min;
    uint8_t sec;
    uint8_t alarm_rate;
    
} rtc12_alarm_t;

/**
 * @brief RTC 12 Click control object.
 * @details Control object definition of RTC 12 Click driver.
 */
typedef struct 
{
    uint8_t eosc;
    uint8_t dosf; 
    uint8_t egfil;
    uint8_t sqw;
    uint8_t intcn;
    uint8_t a1ie;
    uint8_t a0ie;
    
} rtc12_control_t;


/**
 * @brief RTC 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   RTC12_OK = 0,
   RTC12_ERROR = -1

} rtc12_return_value_t;

/*!
 * @addtogroup rtc12 RTC 12 Click Driver
 * @brief API for configuring and manipulating RTC 12 Click driver.
 * @{
 */

/**
 * @brief RTC 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc12_cfg_setup ( rtc12_cfg_t *cfg );

/**
 * @brief RTC 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_init ( rtc12_t *ctx, rtc12_cfg_t *cfg );

/**
 * @brief RTC 12 default configuration function.
 * @details This function executes a default configuration of RTC 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtc12_default_cfg ( rtc12_t *ctx );

/**
 * @brief RTC 12 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_generic_write ( rtc12_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 12 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_generic_read ( rtc12_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 12 set control register function.
 * @details This function sets a control register 
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[in] rtc_ctrl : RTC control structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_set_ctrl_reg ( rtc12_t *ctx, rtc12_control_t rtc_ctrl );

/**
 * @brief RTC 12 get control register function.
 * @details This function get a control register data 
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[out] rtc_ctrl : RTC control structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_get_ctrl_reg ( rtc12_t *ctx, rtc12_control_t *rtc_ctrl );

/**
 * @brief RTC 12 get time function.
 * @details This function get RTC time data structure
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[out] rtc_time : Pointer of the RTC time structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_get_time ( rtc12_t *ctx, rtc12_time_t *rtc_time );

/**
 * @brief RTC 12 set time function.
 * @details This function set RTC time data structure
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[in] rtc_time : RTC time structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_set_time ( rtc12_t *ctx, rtc12_time_t rtc_time );

/**
 * @brief RTC 12 get date function.
 * @details This function get RTC data structure
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[out] rtc_date : Pointer of the RTC date structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_get_date ( rtc12_t *ctx, rtc12_date_t *rtc_date );

/**
 * @brief RTC 12 get time function.
 * @details This function get RTC time data structure
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[in] rtc_date : RTC date structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_set_date ( rtc12_t *ctx, rtc12_date_t rtc_date );

/**
 * @brief RTC 12 get alarm 0 function.
 * @details This function get RTC alarm 0 structure
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[out] rtc_alarm : Pointer of the RTC alarm 0 structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_get_alarm_0 ( rtc12_t *ctx, rtc12_alarm_t *rtc_alarm );

/**
 * @brief RTC 12 get alarm 0 function.
 * @details This function get RTC alarm 0 data structure
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[in] rtc_alarm : RTC alarm 0 structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_set_alarm_0 ( rtc12_t *ctx, rtc12_alarm_t rtc_alarm );

/**
 * @brief RTC 12 get alarm 1 function.
 * @details This function get RTC alarm 1 structure
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[out] rtc_alarm : Pointer of the RTC alarm 1 structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_get_alarm_1 ( rtc12_t *ctx, rtc12_alarm_t *rtc_alarm );

/**
 * @brief RTC 12 get alarm 1 function.
 * @details This function get RTC alarm 1 data structure
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @param[in] rtc_alarm : RTC alarm 1 structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc12_set_alarm_1 ( rtc12_t *ctx, rtc12_alarm_t rtc_alarm );

/**
 * @brief RTC 12 check interrupt state function.
 * @details This function check the interrupt state
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @return @li @c 0 - INT pin state low,
 *         @li @c 1 - INT pin state high.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t rtc12_check_int ( rtc12_t *ctx );

/**
 * @brief RTC 12 check power fail state function.
 * @details This function check the power fail state
 * of the DS1343 Low-Current SPI/3-Wire RTCs 
 * on the RTC 12 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc12_t object definition for detailed explanation.
 * @return @li @c 0 - PF pin state low,
 *         @li @c 1 - PF pin state high.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t rtc12_check_power_fail ( rtc12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RTC12_H

/*! @} */ // rtc12

// ------------------------------------------------------------------------ END
