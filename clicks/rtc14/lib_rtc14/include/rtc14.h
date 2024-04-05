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
 * @file rtc14.h
 * @brief This file contains API for RTC 14 Click Driver.
 */

#ifndef RTC14_H
#define RTC14_H

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
 * @addtogroup rtc14 RTC 14 Click Driver
 * @brief API for configuring and manipulating RTC 14 Click driver.
 * @{
 */

/**
 * @defgroup rtc14_reg RTC 14 Registers List
 * @brief List of registers of RTC 14 Click driver.
 */

/**
 * @addtogroup rtc14_reg
 * @{
 */

/**
 * @brief RTC 14 description register.
 * @details Specified register for description of RTC 14 Click driver.
 */
#define RTC14_REG_SC                                         0x00
#define RTC14_REG_MN                                         0x01
#define RTC14_REG_HR                                         0x02
#define RTC14_REG_DT                                         0x03
#define RTC14_REG_MO                                         0x04
#define RTC14_REG_YR                                         0x05
#define RTC14_REG_DW                                         0x06
#define RTC14_REG_SR                                         0x07
#define RTC14_REG_INT                                        0x08
#define RTC14_REG_ATR                                        0x0A
#define RTC14_REG_DTR                                        0x0B
#define RTC14_REG_SCA                                        0x0C
#define RTC14_REG_MNA                                        0x0D
#define RTC14_REG_HRA                                        0x0E
#define RTC14_REG_DTA                                        0x0F
#define RTC14_REG_MOA                                        0x10
#define RTC14_REG_DWA                                        0x11
#define RTC14_REG_USR1                                       0x12
#define RTC14_REG_USR2                                       0x13
#define RTC14_REG_SCT                                        0x14
#define RTC14_REG_MNT                                        0x15
#define RTC14_REG_HRT                                        0x16
#define RTC14_REG_DTT                                        0x17
#define RTC14_REG_MOT                                        0x18
#define RTC14_REG_YRT                                        0x19

/*! @} */ // rtc14_reg

/**
 * @defgroup rtc14_set RTC 14 Registers Settings
 * @brief Settings for registers of RTC 14 Click driver.
 */

/**
 * @addtogroup rtc14_set
 * @{
 */

/**
 * @brief RTC 14 description setting.
 * @details Specified setting for description of RTC 14 Click driver.
 */
#define RTC14_SET_HOURS_FORMAT_12                            0x00
#define RTC14_SET_HOURS_FORMAT_24                            0x80
#define RTC14_SET_HOURS_FORMAT_12_AM                         0x00
#define RTC14_SET_HOURS_FORMAT_12_PM                         0x20
#define RTC14_SET_ALARM_ENABLE                               0x80
#define RTC14_SET_INT_ENABLE                                 0x40
#define RTC14_SET_SOFT_RESET                                 0x80
#define RTC14_SET_ENABLE_WRTC                                0x10

/**
 * @brief RTC 14 Days of the Week.
 * @details Specified description of Days of the Week of RTC 14 Click driver.
 */
#define RTC14_DW_SUNDAY                                      0x00
#define RTC14_DW_MONDAY                                      0x01
#define RTC14_DW_TUESDAY                                     0x02
#define RTC14_DW_WEDNESDAY                                   0x03
#define RTC14_DW_THURSDAY                                    0x04
#define RTC14_DW_FRIDAY                                      0x05
#define RTC14_DW_SATURDAY                                    0x06

/**
 * @brief RTC 14 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 14 Click driver.
 */
#define RTC14_SET_DEV_ADDR                                   0x6F

/*! @} */ // rtc14_set

/**
 * @defgroup rtc14_map RTC 14 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 14 Click driver.
 */

/**
 * @addtogroup rtc14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 14 Click to the selected MikroBUS.
 */
#define RTC14_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.fo = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.ein = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc14_map
/*! @} */ // rtc14

/**
 * @brief RTC 14 Click context object.
 * @details Context object definition of RTC 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  ein;      /**< Event pin. */

    // Input pins
    digital_in_t  fo;        /**< Frequency pin. */
    digital_in_t  int_pin;   /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} rtc14_t;

/**
 * @brief RTC 14 Click configuration object.
 * @details Configuration object definition of RTC 14 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  fo;         /**< Frequency pin. */
    pin_name_t  ein;        /**< Event pin. */
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} rtc14_cfg_t;

/**
 * @brief RTC 14 Click time object.
 * @details Time object definition of RTC 14 Click driver.
 */
typedef struct 
{
    uint8_t hours_format;
    uint8_t am_pm;
    uint8_t hours; 
    uint8_t min;
    uint8_t sec; 
    
} rtc14_time_t;

/**
 * @brief RTC 14 Click date object.
 * @details Date object definition of RTC 14 Click driver.
 */
typedef struct 
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t day_of_week;
    

} rtc14_date_t;

/**
 * @brief RTC 14 Click alarm object.
 * @details Alarm object definition of RTC 14 Click driver.
 */
typedef struct 
{
    uint8_t sec;
    uint8_t min;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t day_of_week;
    
} rtc14_alarm_t;

/**
 * @brief RTC 14 Click time stamp object.
 * @details Time stamp object definition of RTC 14 Click driver.
 */
typedef struct 
{
    uint8_t sec;
    uint8_t min;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
    
} rtc14_time_stamp_t;

/**
 * @brief RTC 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   RTC14_OK = 0,
   RTC14_ERROR = -1

} rtc14_return_value_t;

/*!
 * @addtogroup rtc14 RTC 14 Click Driver
 * @brief API for configuring and manipulating RTC 14 Click driver.
 * @{
 */

/**
 * @brief RTC 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void rtc14_cfg_setup ( rtc14_cfg_t *cfg );

/**
 * @brief RTC 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_init ( rtc14_t *ctx, rtc14_cfg_t *cfg );

/**
 * @brief RTC 14 default configuration function.
 * @details This function executes a default configuration of RTC 14
 * click board.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t rtc14_default_cfg ( rtc14_t *ctx );

/**
 * @brief RTC 14 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_generic_write ( rtc14_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief RTC 14 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_generic_read ( rtc14_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief RTC 14 write SRAM function.
 * @details This function writes a user SRAM memory 
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[in] sram_data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_write_sram ( rtc14_t *ctx, uint16_t sram_data_in );

/**
 * @brief RTC 14 I2C reading SRAM function.
 * @details This function reads a user SRAM memory 
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[out] sram_data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_read_sram ( rtc14_t *ctx, uint16_t *sram_data_out );

/**
 * @brief RTC 14 get interrupt function.
 * @details This function check the interrupt state 
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @return @li @c 0 - INT pin state low,,
 *         @li @c 1 - INT pin state high.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t rtc14_get_interrupt ( rtc14_t *ctx );

/**
 * @brief RTC 14 get fout function.
 * @details This function get frequency output pin state
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @return @li @c 0 - FO pin state low,,
 *         @li @c 1 - FO pin state high.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t rtc14_get_fout ( rtc14_t *ctx );

/**
 * @brief RTC 14 enable RTC function.
 * @details This function enable  the RTC, crystal oscillator
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_enable_rtc ( rtc14_t *ctx );

/**
 * @brief RTC 14 soft reset function.
 * @details This function performs a software reset
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_soft_reset ( rtc14_t *ctx );

/**
 * @brief RTC 14 get time function.
 * @details This function function get RTC time data structure
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[out] rtc_time : Pointer of the RTC time structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_get_time ( rtc14_t *ctx, rtc14_time_t *rtc_time );

/**
 * @brief RTC 14 set time function.
 * @details This function function set RTC time data structure
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[in] rtc_time : Pointer of the RTC time structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_set_time ( rtc14_t *ctx, rtc14_time_t rtc_time );

/**
 * @brief RTC 14 get date function.
 * @details This function function get RTC date data structure
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[out] rtc_date : Pointer of the RTC date structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_get_date ( rtc14_t *ctx, rtc14_date_t *rtc_date );

/**
 * @brief RTC 14 set date function.
 * @details This function function set RTC date data structure
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[in] rtc_date : Pointer of the RTC date structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_set_date ( rtc14_t *ctx, rtc14_date_t rtc_date );

/**
 * @brief RTC 14 get alarm function.
 * @details This function function get RTC alarm data structure
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[out] rtc_alarm : Pointer of the RTC alarm structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_get_alarm ( rtc14_t *ctx, rtc14_alarm_t *rtc_alarm );

/**
 * @brief RTC 14 set alarm function.
 * @details This function function set RTC alarm data structure
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[in] rtc_alarm : Pointer of the RTC alarm structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_set_alarm ( rtc14_t *ctx, rtc14_alarm_t rtc_alarm );

/**
 * @brief RTC 14 trigger time stamp function.
 * @details This function function trigger time stamp ( EIN pin is triggered ) 
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 *
 * @endcode
 */
void rtc14_trigger_time_stamp ( rtc14_t *ctx );

/**
 * @brief RTC 14 get time stamp function.
 * @details This function function get RTC time stamp data structure
 * of the ISL1221 Low Power RTC with Battery Backed SRAM and Event Detection
 * on the RTC 14 click board™.
 * @param[in] ctx : Click context object.
 * See #rtc14_t object definition for detailed explanation.
 * @param[out] rtc_time_stamp : Pointer of the RTC time stamp structure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t rtc14_get_time_stamp ( rtc14_t *ctx, rtc14_time_stamp_t *rtc_time_stamp );

#ifdef __cplusplus
}
#endif
#endif // RTC14_H

/*! @} */ // rtc14

// ------------------------------------------------------------------------ END
