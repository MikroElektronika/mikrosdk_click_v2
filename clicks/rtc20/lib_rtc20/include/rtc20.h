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
 * @file rtc20.h
 * @brief This file contains API for RTC 20 Click Driver.
 */

#ifndef RTC20_H
#define RTC20_H

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
 * @addtogroup rtc20 RTC 20 Click Driver
 * @brief API for configuring and manipulating RTC 20 Click driver.
 * @{
 */

/**
 * @defgroup rtc20_reg RTC 20 Registers List
 * @brief List of registers of RTC 20 Click driver.
 */

/**
 * @addtogroup rtc20_reg
 * @{
 */

/**
 * @brief RTC 20 description register.
 * @details Specified register for description of RTC 20 Click driver.
 */
#define RTC20_REG_HUNDREDTHS                    0x00
#define RTC20_REG_SECONDS                       0x01
#define RTC20_REG_MINUTES                       0x02
#define RTC20_REG_HOURS                         0x03
#define RTC20_REG_DATE                          0x04
#define RTC20_REG_MONTH                         0x05
#define RTC20_REG_YEAR                          0x06
#define RTC20_REG_DAY                           0x07
#define RTC20_REG_HUNDREDTHS_ALARM              0x08
#define RTC20_REG_SECONDS_ALARM                 0x09
#define RTC20_REG_MINUTES_ALARM                 0x0A
#define RTC20_REG_HOURS_ALARM                   0x0B
#define RTC20_REG_DATE_ALARM                    0x0C
#define RTC20_REG_MONTH_ALARM                   0x0D
#define RTC20_REG_WEEKDAYS_ALARM                0x0E
#define RTC20_REG_STATUS                        0x0F
#define RTC20_REG_CONTROL1                      0x10
#define RTC20_REG_CONTROL2                      0x11
#define RTC20_REG_OSC_CONTROL                   0x1C
#define RTC20_REG_OSC_STATUS                    0x1D

/*! @} */ // rtc20_reg

/**
 * @defgroup rtc20_set RTC 20 Registers Settings
 * @brief Settings for registers of RTC 20 Click driver.
 */

/**
 * @addtogroup rtc20_set
 * @{
 */

/**
 * @brief RTC 20 description setting.
 * @details Specified setting for description of RTC 20 Click driver.
 */
#define RTC20_SET_CTRL_STOP_DISABLE             0x00
#define RTC20_SET_CTRL_STOP_ENABLE              0x01
#define RTC20_SET_CTRL_HOURS_OP_MODE_24h        0x00
#define RTC20_SET_CTRL_HOURS_OP_MODE_12h        0x01
#define RTC20_SET_CTRL_OUTB_nIRQ2               0x00
#define RTC20_SET_CTRL_OUTB_LKO2                0x01
#define RTC20_SET_CTRL_OUT_nIRQ                 0x00
#define RTC20_SET_CTRL_OUT_SQWE                 0x01
#define RTC20_SET_CTRL_ARST_NO_CLR              0x00
#define RTC20_SET_CTRL_ARST_CLR                 0x01
#define RTC20_SET_CTRL_WRTC_DISABLE             0x00
#define RTC20_SET_CTRL_WRTC_ENABLE              0x01
#define RTC20_SET_CTRL_OUT2S_nIRQ_ENABLE        0x00
#define RTC20_SET_CTRL_OUT2S_SQW_ENABLE         0x01
#define RTC20_SET_CTRL_OUT2S_nAIRQ_ENABLE       0x03
#define RTC20_SET_CTRL_OUT2S_TIRQ_ENABLE        0x04
#define RTC20_SET_CTRL_OUT2S_nTIRQ_ENABLE       0x05
#define RTC20_SET_CTRL_OUT2S_OUTB_ENABLE        0x07
#define RTC20_SET_CTRL_OUT1S_nIRQ_ENABLE        0x00
#define RTC20_SET_CTRL_OUT1S_SQW_ENABLE         0x01
#define RTC20_SET_CTRL_OUT1S_SQW_nIRQ_ENABLE    0x02
#define RTC20_SET_CTRL_OUT1S_nAIRQ_ENABLE       0x03

/**
 * @brief RTC 20 Days of the Week.
 * @details Specified description of Days of the Week of RTC 20 Click driver.
 */
#define RTC20_DW_SUNDAY                            0
#define RTC20_DW_MONDAY                            1
#define RTC20_DW_TUESDAY                           2
#define RTC20_DW_WEDNESDAY                         3
#define RTC20_DW_THURSDAY                          4
#define RTC20_DW_FRIDAY                            5
#define RTC20_DW_SATURDAY                          6



/**
 * @brief RTC 20 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 20 Click driver.
 */
#define RTC20_DEVICE_ADDRESS                    0x69

/*! @} */ // rtc20_set

/**
 * @defgroup rtc20_map RTC 20 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 20 Click driver.
 */

/**
 * @addtogroup rtc20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 20 Click to the selected MikroBUS.
 */
#define RTC20_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ir2 = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.wdi = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ext = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ir1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc20_map
/*! @} */ // rtc20

/**
 * @brief RTC 20 Click context object.
 * @details Context object definition of RTC 20 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wdi;        /**< Watchdog Timer reset pin. */
    digital_out_t ext;        /**< External interrupt pin. */

    // Input pins
    digital_in_t ir2;         /**< Secondary interrupt pin. */
    digital_in_t ir1;         /**< Primary interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} rtc20_t;

/**
 * @brief RTC 20 Click configuration object.
 * @details Configuration object definition of RTC 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t ir2;            /**< Secondary interrupt pin. */
    pin_name_t wdi;            /**< Watchdog Timer reset pin. */
    pin_name_t ext;            /**< External interrupt pin. */
    pin_name_t ir1;            /**< Primary interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} rtc20_cfg_t;

/**
 * @brief RTC 20 Click time object.
 * @details Time object definition of RTC 20 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t hundredths;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc20_time_t;

/**
 * @brief RTC 20 Click date object.
 * @details Date object definition of RTC 20 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc20_date_t;

/**
 * @brief RTC 20 Click control signals object.
 * @details Cntrol signals object definition of RTC 20 Click driver.
 */
typedef struct
{
    uint8_t stop;
    uint8_t hours_op_mode;
    uint8_t outb;
    uint8_t out;
    uint8_t arst;
    uint8_t wrtc;
    uint8_t out2s;
    uint8_t out1s;

} rtc20_ctrl_signals_t;

/**
 * @brief RTC 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC20_OK = 0,
    RTC20_ERROR = -1

} rtc20_return_value_t;

/*!
 * @addtogroup rtc20 RTC 20 Click Driver
 * @brief API for configuring and manipulating RTC 20 Click driver.
 * @{
 */

/**
 * @brief RTC 20 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc20_cfg_setup ( rtc20_cfg_t *cfg );

/**
 * @brief RTC 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_init ( rtc20_t *ctx, rtc20_cfg_t *cfg );

/**
 * @brief RTC 20 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_generic_write ( rtc20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 20 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_generic_read ( rtc20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 20 I2C reading function.
 * @details This function sets the WDI pin logic state
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] pin_state : WDI pin logic state.
 * @return Nothing.
 * @note Watchdog Timer reset input connection. 
 * It may also be used to generate an External 2 interrupt with 
 * polarity selected by the EX2P bit if enabled by the EX2E bit. 
 * The value of the WDI pin may be read in the WDI register bit. 
 * This pin does not have an internal pull-up 
 * or pull-down resistor and so one must be added externally. 
 * It must not be left floating or the RTC may consume higher current.
 */
void rtc20_wdi_pin_state ( rtc20_t *ctx, uint8_t pin_state );

/**
 * @brief RTC 20 I2C reading function.
 * @details This function sets the EXT pin logic state
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] pin_state : EXT pin logic state.
 * @return Nothing.
 * @note External interrupt input connection. 
 * It may be used to generate an External 1 interrupt with polarity
 * selected by the EX1P bit if enabled by the EX1E bit. 
 * The value of the EXTI pin may be read in the EXIN register bit. 
 * This pin does not have an internal pull-up or pull-down resistor 
 * and so one must be added externally. 
 * It must not be left floating or the RTC may consume higher current.
 */
void rtc20_ext_pin_state ( rtc20_t *ctx, uint8_t pin_state );

/**
 * @brief RTC 20 set time function.
 * @details This function sets the desired RTC time data  
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] rtc_time : RTC time object structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_set_time ( rtc20_t *ctx, rtc20_time_t rtc_time );

/**
 * @brief RTC 20 get time function.
 * @details This function reads the current RTC time data 
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[out] rtc_time : RTC time object structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_get_time ( rtc20_t *ctx, rtc20_time_t *rtc_time );

/**
 * @brief RTC 20 set date function.
 * @details This function sets the desired RTC date data  
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] rtc_date : RTC date object structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_set_date ( rtc20_t *ctx, rtc20_date_t rtc_date );

/**
 * @brief RTC 20 get date function.
 * @details This function reads the current RTC date data  
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] rtc_date : RTC date object structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_get_date ( rtc20_t *ctx, rtc20_date_t *rtc_date );

/**
 * @brief RTC 20 set alarm function.
 * @details This function sets the desired RTC alarm time and date data  
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] rtc_alarm_time : RTC time object structure.
 * @param[in] rtc_alarm_date : RTC date object structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_set_alarm ( rtc20_t *ctx, rtc20_time_t rtc_alarm_time, rtc20_date_t rtc_alarm_date );

/**
 * @brief RTC 20 get alarm function.
 * @details This function reads the current RTC alarm time and date data  
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[out] rtc_alarm_time : RTC time object structure.
 * @param[out] rtc_alarm_date : RTC date object structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_get_alarm ( rtc20_t *ctx, rtc20_time_t *rtc_alarm_time, rtc20_date_t *rtc_alarm_date );

/**
 * @brief RTC 20 get status function.
 * @details This function reads the status data  
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_get_status ( rtc20_t *ctx, uint8_t *status );

/**
 * @brief RTC 20 set ctrl signals function.
 * @details This function set the control signals data
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] ctrl_signals : Cntrol signals object structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_set_ctrl_signals ( rtc20_t *ctx, rtc20_ctrl_signals_t ctrl_signals );

/**
 * @brief RTC 20 get ctrl signals function.
 * @details This function reads the control signals data  
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @param[in] ctrl_signals : Cntrol signals object structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc20_get_ctrl_signals ( rtc20_t *ctx, rtc20_ctrl_signals_t *ctrl_signals );

/**
 * @brief RTC 20 get IR1 pin function.
 * @details This function get primary interrupt pin stste
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @return IR1 pin logic state.
 * @note Primary interrupt output connection. 
 * @li @c  1. FOUT/nIRQ can drive the value of the OUT bit.
 * @li @c  2. FOUT/nIRQ can drive the inverse of the combined interrupt signal IRQ (see Interrupts).
 * @li @c  3. FOUT/nIRQ can drive the square wave output (see 0x13 - SQW) if enabled by SQWE.
 * @li @c  4. FOUT/nIRQ can drive the inverse of the alarm interrupt signal AIRQ (see Interrupts).
 */
uint8_t rtc20_get_ir1_pin ( rtc20_t *ctx );

/**
 * @brief RTC 20 get IR2 pin function.
 * @details This function get secondary interrupt pin stste
 * of the AB08X5 Real-Time Clock on the RTC 20 Click board™.
 * @param[in] ctx : Click context object.
 * See #rtc20_t object definition for detailed explanation.
 * @return IR2 pin logic state.
 * @note Secondary interrupt output connection. It is an open drain output.
 *    @li @c  1. nIRQ2 may be configured to generate several signals 
 * as a function of the OUT2S field (see 0x11 - Control2). nIRQ2 can drive the value of the OUTB bit.
 *    @li @c  2. nIRQ2 can drive the square wave output (see 0x13 - SQW) if enabled by SQWE.
 *    @li @c  3. nIRQ2 can drive the inverse of the combined interrupt signal IRQ(see Interrupts).
 *    @li @c  4. nIRQ2 can drive the inverse of the alarm interrupt signal AIRQ(see Interrupts).
 *    @li @c  5. nIRQ2 can drive either sense of the timer interrupt signal TIRQ.
 */
uint8_t rtc20_get_ir2_pin ( rtc20_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RTC20_H

/*! @} */ // rtc20

// ------------------------------------------------------------------------ END
