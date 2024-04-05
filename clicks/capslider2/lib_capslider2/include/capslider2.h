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
 * \brief This file contains API for CAP SLIDER 2 Click driver.
 *
 * \addtogroup capslider2 CAP SLIDER 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CAPSLIDER2_H
#define CAPSLIDER2_H

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
#define CAPSLIDER2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg. clr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg. rdy = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CAPSLIDER2_RETVAL  uint8_t

#define CAPSLIDER2_OK           0x00
#define CAPSLIDER2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address Device address
 * \{
 */
#define CAPSLDR2_DEVICE_ADDR                            0x64
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define CAPSLDR2_DEVICE_INFO_REG                        0x00
#define CAPSLDR2_SYSTEM_FLAGS_REG                       0x01
#define CAPSLDR2_WHEEL_COORDNT_REG                      0x02
#define CAPSLDR2_TOUCH_BYTES_REG                        0x03
#define CAPSLDR2_COUNTS_REG                             0x04
#define CAPSLDR2_LTA_REG                                0x05
#define CAPSLDR2_MULTIPLIERS_REG                        0x06
#define CAPSLDR2_COMPENS_REG                            0x07
#define CAPSLDR2_PROXSETT_REG                           0x08
#define CAPSLDR2_THRESH_REG                             0x09
#define CAPSLDR2_TIMINGS_REG                            0x0A
#define CAPSLDR2_TARGETS_REG                            0x0B
#define CAPSLDR2_PWM_DUTY_REG                           0x0C
#define CAPSLDR2_PWM_LIM_REG                            0x0D
#define CAPSLDR2_ACTIVE_CHANN_REG                       0x0E
#define CAPSLDR2_BUZZER_REG                             0x0F
/** \} */

/**
 * \defgroup bytes Bytes
 * \{
 */
#define CAPSLDR2_DEV_INFO_NBYTES                        2
#define CAPSLDR2_SYST_FLAGS_NBYTES                      1
#define CAPSLDR2_WHEEL_NBYTES                           4
#define CAPSLDR2_TOUCH_NBYTES                           2
#define CAPSLDR2_COUNTS_NBYTES                          18
#define CAPSLDR2_LTA_NBYTES                             18
#define CAPSLDR2_MULTIPL_NBYTES                         10
#define CAPSLDR2_COMPENS_NBYTES                         10
#define CAPSLDR2_PROXSETT_NBYTES                        6
#define CAPSLDR2_THRESH_NBYTES                          10
#define CAPSLDR2_TIMINGS_NBYTES                         13
#define CAPSLDR2_TARGETS_NBYTES                         10
#define CAPSLDR2_PWM_DUTY_NBYTES                        8
#define CAPSLDR2_PWM_LIM_NBYTES                         2
#define CAPSLDR2_ACT_CHANN_NBYTES                       2
#define CAPSLDR2_BUZZER_NBYTES                          1
/** \} */

/**
 * \defgroup buzzer Buzzer
 * \{
 */
#define CAPSLDR2_BUZZER_EN                              0x80
#define CAPSLDR2_BUZZER_DC_HIGH                         0x04
#define CAPSLDR2_BUZZER_DC_LOW                          0x00
#define CAPSLDR2_BUZZER_PERM_EN                         0x02
#define CAPSLDR2_BUZZER_BURST_EN                        0x01
/** \} */

/**
 * \defgroup chanel Chanel
 * \{
 */
#define CAPSLDR2_CH0_PROX_EN                           0x001
#define CAPSLDR2_CH1_EN                                0x002
#define CAPSLDR2_CH2_EN                                0x004
#define CAPSLDR2_CH3_EN                                0x008
#define CAPSLDR2_CH4_EN                                0x010
#define CAPSLDR2_CH5_EN                                0x020
#define CAPSLDR2_CH6_EN                                0x040
#define CAPSLDR2_CH7_EN                                0x080
#define CAPSLDR2_CH8_EN                                0x100
#define CAPSLDR2_CH9_EN                                0x200
/** \} */

/**
 * \defgroup pwm_constants PWM constants
 * \{
 */
#define CAPSLDR2_PWM_OFF                                0x00
#define CAPSLDR2_PWM_CONST                              0x20
#define CAPSLDR2_PWM_DECR_0_PERCENTS                    0x80
#define CAPSLDR2_PWM_DECR_LIM                           0xA0
#define CAPSLDR2_PWM_INCR_100_PERCENTS                  0xC0
#define CAPSLDR2_PWM_INCR_LIM                           0xE0
#define CAPSLDR2_PWM_DUTY_0_PERCENTS                    0x00
#define CAPSLDR2_PWM_DUTY_25_PERCENTS                   0x10
#define CAPSLDR2_PWM_DUTY_50_PERCENTS                   0x18
#define CAPSLDR2_PWM_DUTY_75_PERCENTS                   0x1C
#define CAPSLDR2_PWM_DUTY_100_PERCENTS                  0x1F
/** \} */

/**
 * \defgroup data Data
 * \{
 */
#define CAPSLDR2_DATA_READY                             0
#define CAPSLDR2_DATA_NOT_READY                         1
#define CAPSLDR2_INVALID_ADDR                           0xFF
#define CAPSLDR2_INVALID_NBYTES                         0xFE
#define CAPSLDR2_INVALID_CHANNEL                        0xFD
#define CAPSLDR2_OK                                     0x00
/** \} */

/**
 * \defgroup led LED
 * \{
 */
#define CAPSLDR2_LED_INTENSITY                          0
#define CAPSLDR2_LED_NUMBER                             1
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

} capslider2_t;

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

} capslider2_cfg_t;

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
void capslider2_cfg_setup ( capslider2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param capslider2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CAPSLIDER2_RETVAL capslider2_init ( capslider2_t *ctx, capslider2_cfg_t *cfg );

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
void capslider2_generic_write ( capslider2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void capslider2_generic_read ( capslider2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );


/**
 * @brief Generic Write function
 *
 * @param ctx                Click object.
 * @param register_address   Address where data be written.
 * @param data_in            Data to be written.
 * @param n_bytes            Number of bytes to be written.
 *
 * @returns 0x00 - OK, 0xFF - Wrong address, 0xFE - Number of bytes is out of range
 *
 * Function writes the determined number of bytes to the register.
 */
uint8_t capsldr2_write_reg ( capslider2_t *ctx, uint8_t register_address, uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief Generic Read function
 *
 * @param ctx                Click object.
 * @param register_address   Address which from data be read
 * @param data_out           Memory where data be stored
 * @param n_bytes            Number of bytes to be read
 *
 * @returns 0x00 - OK, 0xFF - Wrong address, 0xFE - Number of bytes is out of range
 *
 * Function reads the determined number of bytes from the register.
 */
uint8_t capsldr2_read_reg ( capslider2_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Data Ready Check function
 *
 * @param ctx                Click object.
 *
 * @returns 0 - Data is ready, 1 - Data is not ready
 *
 * Function checks is conversion cycle done and is data ready for reading.
 */
uint8_t capsldr2_check_data_ready ( capslider2_t *ctx );

/**
 * @brief Channel Enable function
 *
 * @param ctx                Click object.
 * @param sel_chann          Selects which channel be activated.
 *
 * @returns 0x00 - OK, 0xFD - Wrong channel selection
 *
 * Function puts the desired channel/channels to active state.
 * @note sel_chann parameter has format 0b0000 00c9c8 c7c6c5c4 c3c2c1c0.
 *       1 on the desired bit will put determined channel to active state.
 *       CH1 to CH3 belong to wheel 1, CH4 to CH6 belong to wheel 2, CH7 to CH9 are touch buttons, and CH0 is proximity channel.
 */
uint8_t capsldr2_enable_chann ( capslider2_t *ctx, uint16_t sel_chann );

/**
 * @brief Data Get function
 *
 * @param ctx                Click object.
 * @param wheel_data1        Memory where data from wheel 0 register be stored.
 * @param wheel_data2        Memory where data from wheel 1 register be stored.
 *
 * Function reads data from both wheel registers and stores these values to memory via output parameters.
 */
void capsldr2_get_data( capslider2_t *ctx, uint16_t *wheel_data1, uint16_t *wheel_data2 );

/**
 * @brief Output Set function
 *
 * @param ctx                Click object.
 * @param input_data         Input data which be showed on LEDs.
 * @param output_mode        Determines how input data be showed on LEDs.
 *
 * Function sets output LEDs depending on the input wheel data value on the way which is determined with the ouputMode parameter.
 * @note Input data represents wheel 1 and wheel 2 results in resolution from 0 to 8.
 *       Output Mode parameter determines in which way finger (object) is pulled over the sensor:
 *       0 - will change the LEDs intensity, 1 - will change the number of activated LEDs.
 */
void capsldr2_set_output ( capslider2_t *ctx, uint8_t input_data, uint8_t output_mode );

/**
 * @brief Threshold Set function
 *
 * @param ctx                Click object.
 * @param thresh_value       Determines touch and proximity sensitivity for all channels.
 *
 * Function determines touch and proximity sensitivity (threshold) for all channels.
 * @note Threshold value can be in the range from 0x00 (Most sensitive) to 0xFF (Least sensitive).
 */
void capsldr2_set_threshold ( capslider2_t *ctx, uint8_t thresh_value );

/**
 * @brief Reset function
 *
 * @param ctx                Click object.
 *
 * Function performs the device reset and puts the device back to normal operating mode.
 */
void capsldr2_reset ( capslider2_t *ctx );

/**
 * @brief Config function
 *
 * @param ctx                Click object.
 *
 * Function performs the CAP Slider 2 configuration.
 */
void capsldr2_config ( capslider2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CAPSLIDER2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
