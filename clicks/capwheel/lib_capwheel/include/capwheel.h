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
 * \brief This file contains API for CAP WHEEL Click driver.
 *
 * \addtogroup capwheel CAP WHEEL Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CAPWHEEL_H
#define CAPWHEEL_H

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
#define CAPWHEEL_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg. clr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg. rdy = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CAPWHEEL_RETVAL  uint8_t

#define CAPWHEEL_OK           0x00
#define CAPWHEEL_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_addres Device addres
 * \{
 */
#define CAPWHEEL_DEVICE_ADDR                            0x64
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define CAPWHEEL_DEVICE_INFO_REG                        0x00
#define CAPWHEEL_SYSTEM_FLAGS_REG                       0x01
#define CAPWHEEL_WHEEL_COORDNT_REG                      0x02
#define CAPWHEEL_TOUCH_BYTES_REG                        0x03
#define CAPWHEEL_COUNTS_REG                             0x04
#define CAPWHEEL_LTA_REG                                0x05
#define CAPWHEEL_MULTIPLIERS_REG                        0x06
#define CAPWHEEL_COMPENS_REG                            0x07
#define CAPWHEEL_PROXSETT_REG                           0x08
#define CAPWHEEL_THRESH_REG                             0x09
#define CAPWHEEL_TIMINGS_REG                            0x0A
#define CAPWHEEL_TARGETS_REG                            0x0B
#define CAPWHEEL_PWM_DUTY_REG                           0x0C
#define CAPWHEEL_PWM_LIM_REG                            0x0D
#define CAPWHEEL_ACTIVE_CHANN_REG                       0x0E
#define CAPWHEEL_BUZZER_REG                             0x0F
/** \} */

/**
 * \defgroup bytes  Bytes
 * \{
 */
#define CAPWHEEL_DEV_INFO_NBYTES                        2
#define CAPWHEEL_SYST_FLAGS_NBYTES                      1
#define CAPWHEEL_WHEEL_NBYTES                           4
#define CAPWHEEL_TOUCH_NBYTES                           2
#define CAPWHEEL_COUNTS_NBYTES                          18
#define CAPWHEEL_LTA_NBYTES                             18
#define CAPWHEEL_MULTIPL_NBYTES                         9
#define CAPWHEEL_COMPENS_NBYTES                         9
#define CAPWHEEL_PROXSETT_NBYTES                        6
#define CAPWHEEL_THRESH_NBYTES                          10
#define CAPWHEEL_TIMINGS_NBYTES                         13
#define CAPWHEEL_TARGETS_NBYTES                         10
#define CAPWHEEL_PWM_DUTY_NBYTES                        8
#define CAPWHEEL_PWM_LIM_NBYTES                         2
#define CAPWHEEL_ACT_CHANN_NBYTES                       2
#define CAPWHEEL_BUZZER_NBYTES                          1
/** \} */

/**
 * \defgroup buzzer Buzzer
 * \{
 */
#define CAPWHEEL_BUZZER_EN                              0x80
#define CAPWHEEL_BUZZER_DC_HIGH                         0x04
#define CAPWHEEL_BUZZER_DC_LOW                          0x00
#define CAPWHEEL_BUZZER_PERM_EN                         0x02
#define CAPWHEEL_BUZZER_BURST_EN                        0x01
/** \} */

/**
 * \defgroup chanel_select Chanel select
 * \{
 */
#define CAPWHEEL_CH0_PROX_EN                           0x001
#define CAPWHEEL_CH1_EN                                0x002
#define CAPWHEEL_CH2_EN                                0x004
#define CAPWHEEL_CH3_EN                                0x008
#define CAPWHEEL_CH4_EN                                0x010
#define CAPWHEEL_CH5_EN                                0x020
#define CAPWHEEL_CH6_EN                                0x040
#define CAPWHEEL_CH7_EN                                0x080
#define CAPWHEEL_CH8_EN                                0x100
#define CAPWHEEL_CH9_EN                                0x200
/** \} */

/**
 * \defgroup pwm_select PWM select
 * \{
 */
#define CAPWHEEL_PWM_OFF                                0x00
#define CAPWHEEL_PWM_CONST                              0x20
#define CAPWHEEL_PWM_DECR_0_PERCENTS                    0x80
#define CAPWHEEL_PWM_DECR_LIM                           0xA0
#define CAPWHEEL_PWM_INCR_100_PERCENTS                  0xC0
#define CAPWHEEL_PWM_INCR_LIM                           0xE0
#define CAPWHEEL_PWM_DUTY_0_PERCENTS                    0x00
#define CAPWHEEL_PWM_DUTY_25_PERCENTS                   0x10
#define CAPWHEEL_PWM_DUTY_50_PERCENTS                   0x18
#define CAPWHEEL_PWM_DUTY_75_PERCENTS                   0x1C
#define CAPWHEEL_PWM_DUTY_100_PERCENTS                  0x1F
/** \} */

/**
 * \defgroup data Data
 * \{
 */
#define CAPWHEEL_DATA_READY                             0
#define CAPWHEEL_DATA_NOT_READY                         1
#define CAPWHEEL_ADDR_ERROR                             0xFF
#define CAPWHEEL_NBYTES_ERROR                           0xFE
#define CAPWHEEL_CH_SEL_ERROR                           0xFD
#define CAPWHEEL_OK                                     0x00
/** \} */

/**
 * \defgroup led_brightness LED brightness
 * \{
 */
#define CAPWHEEL_LED_BRIGHTNESS_INTENSITY               0
#define CAPWHEEL_LED_BRIGHTNESS_NUMBER                  1
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

    digital_out_t  clr;

    // Input pins 

    digital_in_t  rdy;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} capwheel_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t  clr;
    pin_name_t  rdy;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} capwheel_cfg_t;

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
void capwheel_cfg_setup ( capwheel_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param capwheel Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CAPWHEEL_RETVAL capwheel_init ( capwheel_t *ctx, capwheel_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for CapWheel click.
 */
void capwheel_default_cfg ( capwheel_t *ctx );

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
void capwheel_generic_write ( capwheel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void capwheel_generic_read ( capwheel_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic Write function
 *
 * @param ctx               Click object.
 * @param register_address  Address where data be written.
 * @param data_in           Data to be written.
 * @param n_bytes           Number of bytes to be written.
 *
 * @returns 0x00 - OK, 0xFF - Wrong address, 0xFE - Number of bytes is out of range
 *
 * Function writes the determined number of bytes to the register.
 */
uint8_t capwheel_write_reg ( capwheel_t *ctx, uint8_t register_address, uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief Generic Read function
 *
 * @param ctx               Click object.
 * @param register_address  Address which from data be read.
 * @param data_out          Memory where data be stored.
 * @param n_bytes           Number of bytes to be read.
 *
 * @returns 0x00 - OK, 0xFF - Wrong address, 0xFE - Number of bytes is out of range
 *
 * Function reads the determined number of bytes from the register.
 */
uint8_t capwheel_read_reg ( capwheel_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Data Ready Check function
 *
 * @param ctx               Click object.
 *
 * @returns 0 - Data is ready, 1 - Data is not ready
 *
 * Function checks is conversion cycle done and is data ready for reading.
 */
uint8_t capwheel_check_data_ready ( capwheel_t *ctx );

/**
 * @brief Channel Enable function
 *
 * @param ctx               Click object.
 * @param sel_chann         Selects which channel be activated.
 *
 * @returns 0x00 - OK, 0xFD - Wrong channel selection
 *
 * Function puts the desired channel/channels to active state.
 * @note selChann parameter has format 0b0000 00c9c8 c7c6c5c4 c3c2c1c0.
 *       1 on the desired bit will put determined channel to active state.
 */
uint8_t capwheel_enable_chann ( capwheel_t *ctx, uint16_t sel_chann );

/**
 * @brief Data Get function
 *
 * @param ctx               Click object.
 * @param wheel_data        Memory where data be stored.
 *
 * Function reads data from wheel 1 and stores this value in memory via output parameter.
 */
void capwheel_get_data ( capwheel_t *ctx, uint16_t *wheel_data );

/**
 * @brief Output Set function
 *
 * @param ctx               Click object.
 * @param inputdata         Input data which be showed on output LEDs.
 * @param outputdode        Determines how input data be showed on output LEDs.
 *
 * Function sets output LEDs depending on the input wheel data value in the way which is determined with the ouputMode parameter.
 * @note Input data can be showed on two ways. First way includes brightness intensity changing of all LEDs.
 *       Second way includes number of activated LEDs changing, depending on the wheel input data.
 */
void capwheel_set_output( capwheel_t *ctx, uint16_t input_data, uint8_t output_mode );

/**
 * @brief Threshold Set function
 *
 * @param ctx               Click object.
 * @param thresh_value      Determines touch and proximity sensitivity for all channels.
 *
 * Function determines touch and proximity sensitivity (threshold) for all channels.
 * @note Threshold value can be in range from 0x00 (most sensitive) to 0xFF (least sensitive).
 */
void capwheel_set_threshold ( capwheel_t *ctx, uint8_t thresh_value );

/**
 * @brief Reset function
 *
 * @param ctx               Click object.
 *
 * Function performs the device reset and puts the device back to normal operating mode.
 */
void capwheel_reset ( capwheel_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CAPWHEEL_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
