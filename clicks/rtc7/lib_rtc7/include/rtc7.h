/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */
/*!
 * \file
 *
 * \brief This file contains API for RTC 7 Click driver.
 *
 * \addtogroup rtc7 RTC 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTC7_H
#define RTC7_H

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


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define RTC7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.itb = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.ita = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTC7_OK                                 0
#define RTC7_ERROR                             -1
/** \} */

/**
 * \defgroup addr Addr
 * \{
 */
#define RTC7_SECONDS_ADDR                       0x06
#define RTC7_MINUTES_ADDR                       0x07
#define RTC7_HOURS_ADDR                         0x08
#define RTC7_DAY_ADDR                           0x09
#define RTC7_DATE_ADDR                          0x0A
#define RTC7_MONTH_ADDR                         0x0B
#define RTC7_YEAR_ADDR                          0x0C
/** \} */

/**
 * \defgroup byte Byte
 * \{
 */
#define RTC7_TIMEDATE_BYTES                     7
#define RTC7_SECONDS_BYTE                       0
#define RTC7_MINUTES_BYTE                       1
#define RTC7_HOURS_BYTE                         2
#define RTC7_DAY_BYTE                           3
#define RTC7_DATE_BYTE                          4
#define RTC7_MONTH_BYTE                         5
#define RTC7_YEAR_BYTE                          6
/** \} */

/**
 * \defgroup mask Mask
 * \{
 */
#define RTC7_SECONDS_MASK                       0x7F
#define RTC7_MINUTES_MASK                       0x7F
#define RTC7_HOURS_MASK                         0x1F
#define RTC7_DAY_MASK                           0x07
#define RTC7_DATE_MASK                          0x3F
#define RTC7_MONTH_MASK                         0x1F
#define RTC7_YEAR_MASK                          0xFF
/** \} */

/**
 * \defgroup time Time
 * \{
 */
#define RTC7_JULIAN_DAY_1970                    2440588
#define RTC7_TIME_SEC_IN_MIN                    60
#define RTC7_TIME_SEC_IN_HOUR                   3600
#define RTC7_TIME_SEC_IN_24_HOURS               86400
/** \} */

/**
 * \defgroup reg Reg
 * \{
 */
#define RTC7_CONFIG1_REG                        0x00
#define RTC7_CONFIG2_REG                        0x01
#define RTC7_SLEEP_CONFIG_REG                   0x02
#define RTC7_TIMER_CONFIG_REG                   0x03
#define RTC7_INT_EN_REG                         0x04
#define RTC7_INT_STATUS_REG                     0x05
#define RTC7_ALM1_SEC_REG                       0x0D
#define RTC7_ALM1_MIN_REG                       0x0E
#define RTC7_ALM1_HRS_REG                       0x0F
#define RTC7_ALM1_DAY_DATE_REG                  0x10
#define RTC7_ALM2_MIN_REG                       0x11
#define RTC7_ALM2_HRS_REG                       0x12
#define RTC7_ALM2_DAY_DATE_REG                  0x13
#define RTC7_TIMER_COUNT_REG                    0x14
#define RTC7_TIMER_INIT_REG                     0x15
#define RTC7_RAM0_REG_ADDR16H                   0x16
#define RTC7_RAM63_REG_ADDR55H                  0x55
#define RTC7_PWR_MGMT_REG                       0x56
#define RTC7_TRICKLE_REG                        0x57
#define RTC7_SPARE_REG                          0x58
#define RTC7_SPARE_ST_REG                       0x59
#define RTC7_TEST1_REG                          0x64
#define RTC7_TEST2_REG                          0x65
#define RTC7_TEST3_REG                          0x66
#define RTC7_TCFG1_REG                          0x67
#define RTC7_TCFG2_REG                          0x68
#define RTC7_TCFG3_REG                          0x69
#define RTC7_OTP1_B1_REG                        0x6A
#define RTC7_OTP1_B2_REG                        0x6B
#define RTC7_OTP1_B3_REG                        0x6C
#define RTC7_OTP1_B4_REG                        0x6D
#define RTC7_OTP2_B1_REG                        0x6E
#define RTC7_OTP2_B2_REG                        0x6F
#define RTC7_OTP2_B3_REG                        0x70
#define RTC7_OTP2_B4_REG                        0x71
#define RTC7_TCFG4_REG                          0x72
#define RTC7_TCFG5_REG                          0x73
#define RTC7_TEST_DIG_REG                       0x74
/** \} */

/**
 * \defgroup freq Freq
 * \{
 */
#define RTC7_RESET_DIGITAL_BLOCK                0x00
#define RTC7_NOT_RESET_DIGITAL_BLOCK            0x01
#define RTC7_OUTPUT_FREQ_1HZ                    0x00
#define RTC7_OUTPUT_FREQ_4098HZ                 0x02
#define RTC7_OUTPUT_FREQ_8192HZ                 0x04
#define RTC7_OUTPUT_FREQ_32768HZ                0x06
#define RTC7_ENABLE_OSC                         0x00
#define RTC7_DISABLE_OSC                        0x08
#define RTC7_INPUT_FREQ_1HZ                     0x00
#define RTC7_INPUT_FREQ_50HZ                    0x10
#define RTC7_INPUT_FREQ_60HZ                    0x20
#define RTC7_INPUT_FREQ_32768HZ                 0x30
#define RTC7_OUTPUT_SQUARE_WAVE                 0x00
#define RTC7_OUTPUT_INTERRUPT                   0x40
#define RTC7_DISABLE_EXT_CLOCK                  0x00
#define RTC7_ENABLE_EXT_CLOCK                   0x80
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define RTC7_SOLAR_MODE                         0x00
#define RTC7_LUNAR_MODE                         0x01
#define RTC7_WRITE_NOT_ALLOW                    0x00
#define RTC7_WRITE_ALLOW                        0x02
#define RTC7_READ_NOT_ALLOW                     0x00
#define RTC7_READ_ALLOW                         0x04
#define RTC7_I2C_TIMEOUT_DIS                    0x00
#define RTC7_I2C_TIMEOUT_EN                     0x08
#define RTC7_VOLTAGE_THRESH_1400MV              0x00
#define RTC7_VOLTAGE_THRESH_1800MV              0x10
#define RTC7_VOLTAGE_THRESH_2100MV              0x20
#define RTC7_VOLTAGE_THRESH_2500MV              0x30
#define RTC7_NORMAL_OP_MODE                     0x00
#define RTC7_DATA_RETENTION_MODE                0x40
/** \} */

/**
 * \defgroup sleep Sleep
 * \{
 */
#define RTC7_SLEEP_PERIOD_NO_DELAY              0x00
#define RTC7_SLEEP_PERIOD_8_TO_16MS             0x01
#define RTC7_SLEEP_PERIOD_16_TO_24MS            0x02
#define RTC7_SLEEP_PERIOD_24_TO_32MS            0x03
#define RTC7_SLEEP_PERIOD_32_TO_40MS            0x04
#define RTC7_SLEEP_PERIOD_40_TO_48MS            0x05
#define RTC7_SLEEP_PERIOD_48_TO_56MS            0x06
#define RTC7_SLEEP_PERIOD_56_TO_64MS            0x07
#define RTC7_SLEEP_MANAGER_DIS                  0x00
#define RTC7_SLEEP_MANAGER_EN                   0x08
#define RTC7_DIN0_INTERR_FALL_EDGE              0x00
#define RTC7_DIN0_INTERR_RISE_EDGE              0x10
#define RTC7_DIN1_INTERR_FALL_EDGE              0x00
#define RTC7_DIN1_INTERR_RISE_EDGE              0x20
#define RTC7_AN_INTERR_FALL_EDGE                0x00
#define RTC7_AN_INTERR_RISE_EDGE                0x40
#define RTC7_SLEEP_MODE_DIS                     0x00
#define RTC7_SLEEP_MODE_EN                      0x80
/** \} */

/**
 * \defgroup timer Timer
 * \{
 */
#define RTC7_TIMER_FREQ_1024HZ                  0x00
#define RTC7_TIMER_FREQ_256HZ                   0x01
#define RTC7_TIMER_FREQ_64HZ                    0x02
#define RTC7_TIMER_FREQ_16HZ                    0x03
#define RTC7_TIMER_WILL_HALT                    0x00
#define RTC7_TIMER_RELOADS_VALUE                0x04
#define RTC7_PULSE_INTERR_TM_IS_0               0x00
#define RTC7_PULSE_INTERR_TM_IS_1               0x08
#define RTC7_TIMER_DIS                          0x00
#define RTC7_TIMER_EN                           0x10
/** \} */

/**
 * \defgroup interr Interr
 * \{
 */
#define RTC7_ALARM1_INTERR_DIS                  0x00
#define RTC7_ALARM1_INTERR_EN                   0x01
#define RTC7_ALARM2_INTERR_DIS                  0x00
#define RTC7_ALARM2_INTERR_EN                   0x02
#define RTC7_TIMER_INTERR_DIS                   0x00
#define RTC7_TIMER_INTERR_EN                    0x04
#define RTC7_EXT_INTERR0_DIS                    0x00
#define RTC7_EXT_INTERR0_EN                     0x08
#define RTC7_EXT_INTERR1_DIS                    0x00
#define RTC7_EXT_INTERR1_EN                     0x10
#define RTC7_AN_INTERR_DIS                      0x00
#define RTC7_AN_INTERR_EN                       0x20
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct 
{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t weekdays;
  uint8_t monthday;
  uint8_t month;
  uint8_t year;  
  
}rtc7_time_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 
    digital_in_t itb;
    digital_in_t rst;
    digital_in_t ita;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;
    
    int8_t current_time_zone;
    uint8_t rtc7_century;

} rtc7_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t itb;
    pin_name_t rst;
    pin_name_t ita;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} rtc7_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void rtc7_cfg_setup ( rtc7_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t rtc7_init ( rtc7_t *ctx, rtc7_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @details This function writes data to the desired register.
 */
err_t rtc7_generic_write ( rtc7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @details This function reads data from the desired register.
 */
err_t rtc7_generic_read ( rtc7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write one byte function.
 *
 * @param ctx           Click object.
 * @param reg           Address where data be written.
 * @param data_in       Data to be written.
 *
 * @details This function writes one byte data to the register.
 */
err_t rtc7_write_reg ( rtc7_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Read one byte function.
 *
 * @param ctx           Click object.
 * @param reg           Address which from data be read.
 * @param data_out      Buffer where data be stored.
 * @param len           Number of bytes to be read.
 *
 * @details This function writes one byte data to the register.
 */
err_t rtc7_read_reg ( rtc7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Initialization function.
 *
 * @param ctx             Click object.
 * @param time_zone       Determines the local time zone (from 14 to -12).
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function performs the device initialization.
 */
err_t rtc7_init_time ( rtc7_t *ctx, int8_t time_zone );

/**
 * @brief Oscillator Set function.
 *
 * @param ctx             Click object.
 * @param enable_osc      0x00 - enable osc, 0x08 - disable osc.
 * @param clk_in          Determines the input frequency.
 * @param clk_out         Determines the output frequency.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function performs the oscillator to be configured and enabled.
 */
err_t rtc7_set_osc ( rtc7_t *ctx, uint8_t enable_osc, uint8_t clk_in, uint8_t clk_out );

/**
 * @brief Timer Set function.
 *
 * @param ctx             Click object.
 * @param enable_timer    0x00 - disable timer, 0x10 - enable timer.
 * @param timer_freq      Determines the timer frequency.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function performs the timer to be configured and enabled.
 */
err_t rtc7_set_timer ( rtc7_t *ctx, uint8_t enable_timer, uint8_t timer_freq );

/**
 * @brief Reset function.
 *
 * @param ctx             Click object.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function performs the device reset.
 */
err_t rtc7_reset ( rtc7_t *ctx );

/**
 * @brief Get Gmt Time function.
 *
 * @param ctx           Click object.
 * @param gmt_time      Structure where time data be stored.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function gets the gmt time data.
 */
err_t rtc7_get_gmt_time ( rtc7_t *ctx, rtc7_time_t *gmt_time );

/**
 * @brief Get Local Time function.
 *
 * @param ctx           Click object.
 * @param local_time    Structure where local time data be stored.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function gets the local time data including the determined time zone in calculations.
 */
err_t rtc7_get_local_time ( rtc7_t *ctx, rtc7_time_t *local_time );

/**
 * @brief Set Gmt Time function.
 *
 * @param ctx       Click object.
 * @param time      Structure which from time data be written.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function sets the gmt time to desired value.
 */
err_t rtc7_set_gmt_time( rtc7_t *ctx, rtc7_time_t *time );

/**
 * @brief Interrupt Check function.
 *
 * @param ctx       Click object.
 *
 * @details This function returns the interrupt state, state of INTA pin.
 */
uint8_t rtc7_check_interrupt ( rtc7_t *ctx );

/**
 * @brief Power Switch Control function.
 *
 * @param ctx       Click object.
 *
 * @details This function checks the state of Power Switch Control output pin.
 */
uint8_t rtc7_check_psw ( rtc7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RTC7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
