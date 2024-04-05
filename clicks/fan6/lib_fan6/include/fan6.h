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
 * \brief This file contains API for Fan 6  Click driver.
 *
 * \addtogroup fan6 Fan 6  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FAN6_H
#define FAN6_H

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
#define FAN6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.io1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.sdn = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.io2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FAN6_RETVAL  uint8_t

#define FAN6_OK           0x00
#define FAN6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define FAN6_INTERNAL_TEMP_READ_REG               0x00
#define FAN6_EXTDIODE1_TEMP_READ_REG              0x02
#define FAN6_EXTDIODE2_TEMP_READ_REG              0x04
#define FAN6_EXTDIODE3_TEMP_READ_REG              0x06
#define FAN6_CRITICAL_TEMP_REG                    0x0A
#define FAN6_PUSHED_TEMP1_REG                     0x0C
#define FAN6_PUSHED_TEMP2_REG                     0x0D
#define FAN6_TRIP_SET_VOLTAGE_REG                 0x10
#define FAN6_EXTDIODE1_IDEALITY_REG               0x11
#define FAN6_EXTDIODE2_IDEALITY_REG               0x12
#define FAN6_EXTDIODE1_BETA_CONFIG_REG            0x14
#define FAN6_EXTDIODE2_BETA_CONFIG_REG            0x15
#define FAN6_EXTDIODE_REC_CONFIG_REG              0x17
#define FAN6_EXTDIODE1_TCRIT_LIMIT_REG            0x19
#define FAN6_EXTDIODE2_TCRIT_LIMIT_REG            0x1A
#define FAN6_EXTDIODE3_TCRIT_LIMIT_REG            0x1B
#define FAN6_INTDIODE_TCRIT_LIMIT_REG             0x1D
#define FAN6_TCRIT_STATUS_REG                     0x1F
#define FAN6_CONFIGURATION_REG                    0x20
#define FAN6_CONFIGURATION2_REG                   0x21
#define FAN6_INTERRUPT_STATUS_REG                 0x23
#define FAN6_HIGH_LIMIT_STATUS_REG                0x24
#define FAN6_LOW_LIMIT_STATUS_REG                 0x25
#define FAN6_DIODE_FAULT_REG                      0x26
#define FAN6_FAN_STATUS_REG                       0x27
#define FAN6_INTERRUPT_EN_REG                     0x28
#define FAN6_FAN_INTERRUPT_EN_REG                 0x29
#define FAN6_PWM_CONFIG_REG                       0x2A
#define FAN6_PWM_BASE_FREQ_REG                    0x2B
#define FAN6_EXTDIODE1_HIGHTEMP_LIMIT_REG         0x30
#define FAN6_EXTDIODE2_HIGHTEMP_LIMIT_REG         0x31
#define FAN6_EXTDIODE3_HIGHTEMP_LIMIT_REG         0x32
#define FAN6_INTDIODE_HIGHTEMP_LIMIT_REG          0x34
#define FAN6_EXTDIODE1_LOWTEMP_LIMIT_REG          0x38
#define FAN6_EXTDIODE2_LOWTEMP_LIMIT_REG          0x39
#define FAN6_EXTDIODE3_LOWTEMP_LIMIT_REG          0x3A
#define FAN6_INTDIODE_LOWTEMP_LIMIT_REG           0x3C
#define FAN6_FAN_SETTING_REG                      0x40
#define FAN6_PWM_DIVIDE_REG                       0x41
#define FAN6_FAN_CONFIG1_REG                      0x42
#define FAN6_FAN_CONFIG2_REG                      0x43
#define FAN6_GAIN_REG                             0x45
#define FAN6_FAN_SPINUP_CONFIG_REG                0x46
#define FAN6_FAN_STEP_REG                         0x47
#define FAN6_FAN_MIN_DRIVE_REG                    0x48
#define FAN6_FAN_VALID_TACH_COUNT_REG             0x49
#define FAN6_FAN_DRIVE_FAIL_BAND_REG              0x4A
#define FAN6_TACH_TARGET_REG                      0x4C
#define FAN6_TACH_READING_REG                     0x4E
#define FAN6_LUT_CONFIG_REG                       0x50
#define FAN6_LUT_DRIVE1_REG                       0x51
#define FAN6_LUT_TEMP1_SETTING1_REG               0x52
#define FAN6_LUT_TEMP2_SETTING1_REG               0x53
#define FAN6_LUT_TEMP3_SETTING1_REG               0x54
#define FAN6_LUT_INTTEMP_SETTING1_REG             0x55
#define FAN6_LUT_DRIVE2_REG                       0x56
#define FAN6_LUT_TEMP1_SETTING2_REG               0x57
#define FAN6_LUT_TEMP2_SETTING2_REG               0x58
#define FAN6_LUT_TEMP3_SETTING2_REG               0x59
#define FAN6_LUT_INTTEMP_SETTING2_REG             0x5A
#define FAN6_LUT_DRIVE3_REG                       0x5B
#define FAN6_LUT_TEMP1_SETTING3_REG               0x5C
#define FAN6_LUT_TEMP2_SETTING3_REG               0x5D
#define FAN6_LUT_TEMP3_SETTING3_REG               0x5E
#define FAN6_LUT_INTTEMP_SETTING3_REG             0x5F
#define FAN6_LUT_DRIVE4_REG                       0x60
#define FAN6_LUT_TEMP1_SETTING4_REG               0x61
#define FAN6_LUT_TEMP2_SETTING4_REG               0x62
#define FAN6_LUT_TEMP3_SETTING4_REG               0x63
#define FAN6_LUT_INTTEMP_SETTING4_REG             0x64
#define FAN6_LUT_DRIVE5_REG                       0x65
#define FAN6_LUT_TEMP1_SETTING5_REG               0x66
#define FAN6_LUT_TEMP2_SETTING5_REG               0x67
#define FAN6_LUT_TEMP3_SETTING5_REG               0x68
#define FAN6_LUT_INTTEMP_SETTING5_REG             0x69
#define FAN6_LUT_DRIVE6_REG                       0x6A
#define FAN6_LUT_TEMP1_SETTING6_REG               0x6B
#define FAN6_LUT_TEMP2_SETTING6_REG               0x6C
#define FAN6_LUT_TEMP3_SETTING6_REG               0x6D
#define FAN6_LUT_INTTEMP_SETTING6_REG             0x6E
#define FAN6_LUT_DRIVE7_REG                       0x6F
#define FAN6_LUT_TEMP1_SETTING7_REG               0x70
#define FAN6_LUT_TEMP2_SETTING7_REG               0x71
#define FAN6_LUT_TEMP3_SETTING7_REG               0x72
#define FAN6_LUT_INTTEMP_SETTING7_REG             0x73
#define FAN6_LUT_DRIVE8_REG                       0x74
#define FAN6_LUT_TEMP1_SETTING8_REG               0x75
#define FAN6_LUT_TEMP2_SETTING8_REG               0x76
#define FAN6_LUT_TEMP3_SETTING8_REG               0x77
#define FAN6_LUT_INTTEMP_SETTING8_REG             0x78
#define FAN6_GPIO_DIR_REG                         0xE1
#define FAN6_GPIO_OUTPUT_CONFIG_REG               0xE2
#define FAN6_GPIO_INPUT_REG                       0xE3
#define FAN6_GPIO_OUTPUT_REG                      0xE4
#define FAN6_GPIO_INTERR_EN_REG                   0xE5
#define FAN6_GPIO_STATUS_REG                      0xE6
#define FAN6_SW_LOCK_REG                          0xEF
#define FAN6_PRODUCT_FEATURES_REG                 0xFC
#define FAN6_PRODUCT_ID_REG                       0xFD
#define FAN6_MANUFACTURER_ID_REG                  0xFE
#define FAN6_REVISION_REG                         0xFF
/** \} */

/**
 * \defgroup beta Beta
 * \{
 */
#define FAN6_AUTOBETA_DETECTION_DISABLED          0x00
#define FAN6_AUTOBETA_DETECTION_ENABLED           0x10
#define FAN6_MIN_BETA_80MILI                      0x00
#define FAN6_MIN_BETA_111MILI                     0x01
#define FAN6_MIN_BETA_176MILI                     0x02
#define FAN6_MIN_BETA_290MILI                     0x03
#define FAN6_MIN_BETA_480MILI                     0x04
#define FAN6_MIN_BETA_900MILI                     0x05
#define FAN6_MIN_BETA_2330MILI                    0x06
#define FAN6_MIN_BETA_DISABLED                    0x07
/** \} */

/**
 * \defgroup extdiode_rec Extdiode Rec
 * \{
 */
#define FAN6_EXTDIODE_REC_DISABLED                0x00
#define FAN6_EXTDIODE3_REC_ENABLED                0x04
#define FAN6_EXTDIODE2_REC_ENABLED                0x02
#define FAN6_EXTDIODE1_REC_ENABLED                0x01
/** \} */

/**
 * \defgroup extdiode_sys Extdiode Sys
 * \{
 */
#define FAN6_ALERT_PIN_UNMASKED                   0x00
#define FAN6_ALERT_PIN_MASKED                     0x80
#define FAN6_EXTDIODE_SYS_SHDN_PIN_NOT_LINKED     0x00
#define FAN6_EXTDIODE3_SYS_SHDN_PIN_LINKED        0x08
#define FAN6_EXTDIODE2_SYS_SHDN_PIN_LINKED        0x04
#define FAN6_EXTDIODE1_SYS_SHDN_PIN_LINKED        0x02
#define FAN6_ANTIPARALLEL_DIODE_FUNCT_DISABLED    0x00
#define FAN6_ANTIPARALLEL_DIODE_FUNCT_ENABLED     0x01
/** \} */

/**
 * \defgroup dynamic_averaging Dynamic Averaging
 * \{
 */
#define FAN6_DYNAMIC_AVERAGING_ENABLED            0x00
#define FAN6_DYNAMIC_AVERAGING_DISABLED           0x40
#define FAN6_SMBUS_ENABLED                        0x00
#define FAN6_SMBUS_DISABLED                       0x20
#define FAN6_DIGITAL_AVERAGING_ENABLED            0x00
#define FAN6_DIGITAL_AVERAGING_DISABLED           0x10
#define FAN6_CONSECUTIVE_OUTOFLIMIT_NUMBER_1      0x00
#define FAN6_CONSECUTIVE_OUTOFLIMIT_NUMBER_2      0x04
#define FAN6_CONSECUTIVE_OUTOFLIMIT_NUMBER_3      0x08
#define FAN6_CONSECUTIVE_OUTOFLIMIT_NUMBER_4      0x0C
#define FAN6_CONVERSION_RATE_1_PERSEC             0x00
#define FAN6_CONVERSION_RATE_2_PERSEC             0x01
#define FAN6_CONVERSION_RATE_4_PERSEC             0x02
#define FAN6_CONVERSION_RATE_CONTINUOUS           0x03
/** \} */

/**
 * \defgroup extdiode_interrupt Extdiode Interrupt
 * \{
 */
#define FAN6_ALL_INTERRUPTS_DISABLED              0x00
#define FAN6_EXTDIODE3_INTERRUPT_ENABLED          0x08
#define FAN6_EXTDIODE2_INTERRUPT_ENABLED          0x04
#define FAN6_EXTDIODE1_INTERRUPT_ENABLED          0x02
#define FAN6_INTDIODE_INTERRUPT_ENABLED           0x01
/** \} */

/**
 * \defgroup fan_reg Fan Reg
 * \{
 */
#define FAN6_ALL_FAN_INTERRUPTS_DISABLED          0x00
#define FAN6_FAN_SPIN_BIT_ENABLED                 0x02
#define FAN6_FAN_STALL_BIT_ENABLED                0x01
/** \} */

/**
 * \defgroup pwm_pin Pwm Pin
 * \{
 */
#define FAN6_PWM_PIN_OPEN_DRAIN                   0x00
#define FAN6_PWM_PIN_PUSH_PULL                    0x10
#define FAN6_NORMAL_POLARITY                      0x00
#define FAN6_INVERTED_POLARITY                    0x01
/** \} */

/**
 * \defgroup pwm_base Pwm Base
 * \{
 */
#define FAN6_PWM_BASE_FREQ_26000HZ                0x00
#define FAN6_PWM_BASE_FREQ_19531HZ                0x01
#define FAN6_PWM_BASE_FREQ_4882HZ                 0x02
#define FAN6_PWM_BASE_FREQ_2441HZ                 0x03
/** \} */

/**
 * \defgroup percent_speed Percent Speed
 * \{
 */
#define FAN6_0_PERCENT_SPEED                      0x00
#define FAN6_25_PERCENTS_SPEED                    0x40
#define FAN6_50_PERCENTS_SPEED                    0x80
#define FAN6_75_PERCENTS_SPEED                    0xC0
#define FAN6_100_PERCENTS_SPEED                   0xFF
/** \} */

/**
 * \defgroup update_time Update Time
 * \{
 */
#define FAN6_CONTROL_CIRCUITRY_DISABLED           0x00
#define FAN6_CONTROL_CIRCUITRY_ENABLED            0x80
#define FAN6_RANGE_MIN_500RPM                     0x00
#define FAN6_RANGE_MIN_1000RPM                    0x20
#define FAN6_RANGE_MIN_2000RPM                    0x40
#define FAN6_RANGE_MIN_4000RPM                    0x60
#define FAN6_MIN_3_EDGES                          0x00
#define FAN6_MIN_5_EDGES                          0x08
#define FAN6_MIN_7_EDGES                          0x10
#define FAN6_MIN_9_EDGES                          0x18
#define FAN6_UPDATE_TIME_100_MILISEC              0x00
#define FAN6_UPDATE_TIME_200_MILISEC              0x01
#define FAN6_UPDATE_TIME_300_MILISEC              0x02
#define FAN6_UPDATE_TIME_400_MILISEC              0x03
#define FAN6_UPDATE_TIME_500_MILISEC              0x04
#define FAN6_UPDATE_TIME_800_MILISEC              0x05
#define FAN6_UPDATE_TIME_1200_MILISEC             0x06
#define FAN6_UPDATE_TIME_1600_MILISEC             0x07
/** \} */

/**
 * \defgroup error_range Error Range
 * \{
 */
#define FAN6_RAMP_RATE_CONT_DISABLED              0x00
#define FAN6_RAMP_RATE_CONT_ENABLED               0x40
#define FAN6_GLITCH_FILTER_DISABLED               0x00
#define FAN6_GLITCH_FILTER_ENABLED                0x20
#define FAN6_NO_DERIVATIVE                        0x00
#define FAN6_BASIC_DERIVATIVE                     0x08
#define FAN6_STEP_DERIVATIVE                      0x10
#define FAN6_BOTH_DERIVATIVE                      0x18
#define FAN6_ERROR_RANGE_0RPM                     0x00
#define FAN6_ERROR_RANGE_50RPM                    0x02
#define FAN6_ERROR_RANGE_100RPM                   0x04
#define FAN6_ERROR_RANGE_200RPM                   0x06
/** \} */

/**
 * \defgroup gain Gain
 * \{
 */
#define FAN6_GAIN_1X                              0x00
#define FAN6_GAIN_2X                              0x15
#define FAN6_GAIN_4X                              0x2A
#define FAN6_GAIN_8X                              0x3F
/** \} */

/**
 * \defgroup spinup Spinup
 * \{
 */
#define FAN6_UPDATE_PERIODS_DISABLED              0x00
#define FAN6_16_UPDATE_PERIODS                    0x40
#define FAN6_32_UPDATE_PERIODS                    0x80
#define FAN6_64_UPDATE_PERIODS                    0xC0
#define FAN6_100_PERCENTS_PWM_DRIVE_ENABLED       0x00
#define FAN6_100_PERCENTS_PWM_DRIVE_DISABLED      0x20
#define FAN6_SPINUP_DRIVELEVEL_30_PERCENTS        0x00
#define FAN6_SPINUP_DRIVELEVEL_35_PERCENTS        0x04
#define FAN6_SPINUP_DRIVELEVEL_40_PERCENTS        0x08
#define FAN6_SPINUP_DRIVELEVEL_45_PERCENTS        0x0C
#define FAN6_SPINUP_DRIVELEVEL_50_PERCENTS        0x10
#define FAN6_SPINUP_DRIVELEVEL_55_PERCENTS        0x14
#define FAN6_SPINUP_DRIVELEVEL_60_PERCENTS        0x18
#define FAN6_SPINUP_DRIVELEVEL_65_PERCENTS        0x1C
#define FAN6_SPINUP_TIME_250_MILISEC              0x00
#define FAN6_SPINUP_TIME_500_MILISEC              0x01
#define FAN6_SPINUP_TIME_1_SEC                    0x02
#define FAN6_SPINUP_TIME_2_SEC                    0x03
/** \} */

/**
 * \defgroup push_temp Push Temp
 * \{
 */
#define FAN6_PUSH_TEMP_NOT_LOADED                 0x00
#define FAN6_PUSH_TEMP1_LOADED                    0x80
#define FAN6_PUSH_TEMP2_LOADED                    0x40
#define FAN6_LUT_ENABLED                          0x00
#define FAN6_LUT_LOCKED                           0x20
#define FAN6_RPM_TACH_ENABLED                     0x00
#define FAN6_PWM_DUTY_ENABLED                     0x10
/** \} */

/**
 * \defgroup gpio_dir Gpio Dir
 * \{
 */
#define FAN6_GPIO_DIR_INPUT                       0x00
#define FAN6_GPIO2_DIR_OUTPUT                     0x02
#define FAN6_GPIO1_DIR_OUTPUT                     0x01
/** \} */

/**
 * \defgroup gpio_as Gpio As
 * \{
 */
#define FAN6_GPIO_AS_OPEN_DRAIN                   0x00
#define FAN6_GPIO2_AS_PUSH_PULL                   0x02
#define FAN6_GPIO1_AS_PUSH_PULL                   0x01
/** \} */

/**
 * \defgroup gpio_interr Gpio Interr
 * \{
 */
#define FAN6_GPIO_INTERR_DISABLED                 0x00
#define FAN6_GPIO2_INTERR_ENABLED                 0x02
#define FAN6_GPIO1_INTERR_ENABLED                 0x01
/** \} */

/**
 * \defgroup sw_locked Sw Locked
 * \{
 */
#define FAN6_SW_NOT_LOCKED                        0x00
#define FAN6_SW_LOCKED                            0x01
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t io1;
    digital_out_t en;

    // Input pins 

    digital_in_t sdn;
    digital_in_t io2;
    digital_in_t alr;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    
    uint8_t check_ptr;
    uint8_t adc_mode;
    uint8_t config_byte1;
    uint8_t config_byte2;

} fan6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t io1;
    pin_name_t sdn;
    pin_name_t en;
    pin_name_t io2;
    pin_name_t alr;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} fan6_cfg_t;

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
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void fan6_cfg_setup ( fan6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param fan6 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FAN6_RETVAL fan6_init ( fan6_t *ctx, fan6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Fan6 click.
 */
void fan6_default_cfg ( fan6_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void fan6_generic_write ( fan6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void fan6_generic_read ( fan6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write function.
 *
 * @param ctx                 Click object.
 * @param register_address    Register address.
 * @param transfer_data       Data which be written.
 *
 * @description This function writes 16-bit or 8-bit data to register.
 */
void fan6_write_reg ( fan6_t *ctx, const uint8_t register_address, const uint16_t transfer_data );

/**
 * @brief Generic read function.
 *
 * @param ctx                 Click object.
 * @param register_address    Register address.
 *
 * @description This function reads 16-bit or 8-bit data from register.
 */
uint16_t fan6_read_reg ( fan6_t *ctx, const uint8_t register_address );

/**
 * @brief Byte receive function.
 *
 * @param ctx                 Click object.
 * @param register_address    Register address.
 *
 * @description This function sends register address and reads byte from that address, without writting address again,
 * every time when function be called.
 */
uint8_t fan6_receive_byte ( fan6_t *ctx, const uint8_t register_address );

/**
 * @brief EEPROM read function.
 *
 * @param ctx         Click object.
 * @param data_out    Buffer where data be stored.
 *
 * @description This function reads 256 bytes from EEPROM.
 */
void fan6_read_eeprom ( fan6_t *ctx, uint8_t *data_out );

/**
 * @brief PWM mode set function.
 *
 * @param ctx         Click object.
 * @param pwm_duty    Value which determines Fan speed.
 *
 * @description This function sets Fan on PWM mode and determines Fan speed (PWM duty).
 */
void fan6_set_pwm_mode ( fan6_t *ctx, const uint8_t pwm_duty );

/**
 * @brief Fan Speed Control Mode Set function.
 *
 * @param ctx             Click object.
 * @param minimumDrive    Minimum drive setting for the RPM.
 * @param tach_count      Maximum TACH Reading register value.
 * @param tach_target     The target tachometer value that is maintained by the RPM.
 *
 * @description This function sets Fan on Fan Speed Control (FSC) mode and determines minimum drive setting for the RPM,
 * maximum TACH Reading register value and the target tachometer value that is maintained by the RPM.
 */
void fan6_set_fan_speed_con_mode ( fan6_t *ctx, const uint8_t minimum_drive, const uint8_t tach_count, const uint16_t tach_target );

/**
 * @brief Set PWM With LUT Mode function.
 *
 * @param ctx           Click object.
 * @param tach_count    Maximum TACH Reading register value.
 *
 * @description This function sets Fan on PWM with Look Up Table (LUT) mode and determines maximum TACH Reading
 * register value.
 */
void fan6_set_pwm_lut_mode ( fan6_t *ctx, const uint8_t tach_count );

/**
 * @brief Set FSC With LUT Mode function.
 *
 * @param ctx              Click object.
 * @param minimum_drive    Minimum drive setting for the RPM.
 * @param tach_count       Maximum TACH Reading register value.
 *
 * @description This function sets Fan on FSC with LUT mode and determines maximum TACH Reading register value
 * and minimum drive setting for the RPM.
 */
void fan6_set_fsc_lut_mode ( fan6_t *ctx, const uint8_t minimum_drive, const uint8_t tach_count );

/**
 * @brief Tachometer Read function.
 *
 * @param ctx              Click object.
 *
 * @description This function reads current tachometer value and calculates that value in rpm.
 */
uint32_t fan6_read_tachometer ( fan6_t *ctx );

/**
 * @brief Temperature Get function.
 *
 * @param ctx              Click object.
 * @param temp_address     Address where temperature is stored.
 * @param temp_sign        Determines sign of temperature.
 *
 * @description This function can read anyone positive or negative temperature value, from external or internal diode.
 */
float fan6_get_temperature ( fan6_t *ctx, const uint8_t temp_address );

/**
 * @brief Temperature Push function.
 *
 * @param ctx              Click object.
 * @param temp_address     Address where temperature which be pushed is stored.
 * @param temp_selection   Address where tempereture be pushed.
 *
 * @description This function pushes desired temperature value in Temperature 1 or Temperature 2 Pushed register.
 */
void fan6_push_temperature ( fan6_t *ctx, const uint8_t temp_address, const uint8_t temp_selection );

/**
 * @brief Device Enable function.
 *
 * @param ctx       Click object.
 * @param state     State.
 *
 * @description This function can enable or disable device.
 */
void fan6_enable_device ( fan6_t *ctx, const uint8_t state );

/**
 * @brief Interrupt Pin Get function.
 *
 * @param ctx       Click object.
 *
 * @description This function gets interrupt pin.
 */
uint8_t fan6_indicate_critical_thermal_shutdown ( fan6_t *ctx );

/**
 * @brief GPIO 2 Get function.
 *
 * @param ctx       Click object.
 *
 * @description This function gets GPIO 2 state.
 */
uint8_t fan6_get_gpio_2 ( fan6_t *ctx );

/**
 * @brief GPIO 1 Set function.
 *
 * @param ctx       Click object.
 *
 * @description This function sets GPIO 1 on desired state when he is configured as input pin.
 */
void fan6_set_gpio_1 ( fan6_t *ctx, const uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _FAN6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
