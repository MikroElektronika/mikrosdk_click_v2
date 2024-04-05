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
 * \brief This file contains API for Servo Click driver.
 *
 * \addtogroup servo Servo Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SERVO_H
#define SERVO_H

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
#define SERVO_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.oe   = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SERVO_RETVAL  uint8_t

#define SERVO_OK           0x00
#define SERVO_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup servo_registers Servo Registers
 * \{
 */
#define SERVO_REG_MODE_1                  0x00
#define SERVO_REG_MODE_2                  0x01
#define SERVO_REG_SUB_ADDRESS_1           0x02
#define SERVO_REG_SUB_ADDRESS_2           0x03
#define SERVO_REG_SUB_ADDRESS_3           0x04
#define SERVO_REG_ALL_CALL_ADR            0x05

#define SERVO_REG_MOTOR_1_ON_L            0x06
#define SERVO_REG_MOTOR_1_ON_H            0x07
#define SERVO_REG_MOTOR_1_OFF_L           0x08
#define SERVO_REG_MOTOR_1_OFF_H           0x09
#define SERVO_REG_MOTOR_2_ON_L            0x0A
#define SERVO_REG_MOTOR_2_ON_H            0x0B
#define SERVO_REG_MOTOR_2_OFF_L           0x0C
#define SERVO_REG_MOTOR_2_OFF_H           0x0D
#define SERVO_REG_MOTOR_3_ON_L            0x0E
#define SERVO_REG_MOTOR_3_ON_H            0x0F
#define SERVO_REG_MOTOR_3_OFF_L           0x10
#define SERVO_REG_MOTOR_3_OFF_H           0x11
#define SERVO_REG_MOTOR_4_ON_L            0x12
#define SERVO_REG_MOTOR_4_ON_H            0x13
#define SERVO_REG_MOTOR_4_OFF_L           0x14
#define SERVO_REG_MOTOR_4_OFF_H           0x15
#define SERVO_REG_MOTOR_5_ON_L            0x16
#define SERVO_REG_MOTOR_5_ON_H            0x17
#define SERVO_REG_MOTOR_5_OFF_L           0x18
#define SERVO_REG_MOTOR_5_OFF_H           0x19
#define SERVO_REG_MOTOR_6_ON_L            0x1A
#define SERVO_REG_MOTOR_6_ON_H            0x1B
#define SERVO_REG_MOTOR_6_OFF_L           0x1C
#define SERVO_REG_MOTOR_6_OFF_H           0x1D
#define SERVO_REG_MOTOR_7_ON_L            0x1E
#define SERVO_REG_MOTOR_7_ON_H            0x1F
#define SERVO_REG_MOTOR_7_OFF_L           0x20
#define SERVO_REG_MOTOR_7_OFF_H           0x21
#define SERVO_REG_MOTOR_8_ON_L            0x22
#define SERVO_REG_MOTOR_8_ON_H            0x23
#define SERVO_REG_MOTOR_8_OFF_L           0x24
#define SERVO_REG_MOTOR_8_OFF_H           0x25
#define SERVO_REG_MOTOR_9_ON_L            0x26
#define SERVO_REG_MOTOR_9_ON_H            0x27
#define SERVO_REG_MOTOR_9_OFF_L           0x28
#define SERVO_REG_MOTOR_9_OFF_H           0x29
#define SERVO_REG_MOTOR_10_ON_L           0x2A
#define SERVO_REG_MOTOR_10_ON_H           0x2B
#define SERVO_REG_MOTOR_10_OFF_L          0x2C
#define SERVO_REG_MOTOR_10_OFF_H          0x2D
#define SERVO_REG_MOTOR_11_ON_L           0x2E
#define SERVO_REG_MOTOR_11_ON_H           0x2F
#define SERVO_REG_MOTOR_11_OFF_L          0x30
#define SERVO_REG_MOTOR_11_OFF_H          0x31
#define SERVO_REG_MOTOR_12_ON_L           0x32
#define SERVO_REG_MOTOR_12_ON_H           0x33
#define SERVO_REG_MOTOR_12_OFF_L          0x34
#define SERVO_REG_MOTOR_12_OFF_H          0x35
#define SERVO_REG_MOTOR_13_ON_L           0x36
#define SERVO_REG_MOTOR_13_ON_H           0x37
#define SERVO_REG_MOTOR_13_OFF_L          0x38
#define SERVO_REG_MOTOR_13_OFF_H          0x39
#define SERVO_REG_MOTOR_14_ON_L           0x3A
#define SERVO_REG_MOTOR_14_ON_H           0x3B
#define SERVO_REG_MOTOR_14_OFF_L          0x3C
#define SERVO_REG_MOTOR_14_OFF_H          0x3D
#define SERVO_REG_MOTOR_15_ON_L           0x3E
#define SERVO_REG_MOTOR_15_ON_H           0x3F
#define SERVO_REG_MOTOR_15_OFF_L          0x40
#define SERVO_REG_MOTOR_15_OFF_H          0x41
#define SERVO_REG_MOTOR_16_ON_L           0x42
#define SERVO_REG_MOTOR_16_ON_H           0x43
#define SERVO_REG_MOTOR_16_OFF_L          0x44
#define SERVO_REG_MOTOR_16_OFF_H          0x45

#define SERVO_REG_ALL_MOTOR_ON_L          0xFA
#define SERVO_REG_ALL_MOTOR_ON_H          0xFB
#define SERVO_REG_ALL_MOTOR_OFF_L         0xFC
#define SERVO_REG_ALL_MOTOR_OFF_H         0xFD
#define SERVO_REG_PRE_SCALE               0xFE
#define SERVO_REG_TEST_MODE               0xFF
/** \} */

/**
 * \defgroup mode_1_register Mode 1 Register
 * \{
 */
#define SERVO_MODE1_RESTART_ENABLE            0x01 << 7
#define SERVO_MODE1_RESTART_DISABLE           0x00 << 7
#define SERVO_MODE1_INTERNAL_CLOCK            0x00 << 6
#define SERVO_MODE1_EXTCLK_PIN_CLOCK          0x01 << 6
#define SERVO_MODE1_AUTO_INCREMENT_ENABLE     0x01 << 5
#define SERVO_MODE1_AUTO_INCREMENT_DISABLE    0x00 << 5
#define SERVO_MODE1_NORMAL_MODE               0x00 << 4
#define SERVO_MODE1_LOW_POWER_MODE            0x01 << 4
#define SERVO_MODE1_USE_SUBADR_1              0x01 << 3
#define SERVO_MODE1_NO_USE_SUBADR_1           0x00 << 3
#define SERVO_MODE1_USE_SUBADR_2              0x01 << 2
#define SERVO_MODE1_NO_USE_SUBADR_2           0x00 << 2
#define SERVO_MODE1_USE_SUBADR_3              0x01 << 1
#define SERVO_MODE1_NO_USE_SUBADR_3           0x00 << 1
#define SERVO_MODE1_USE_ALL_CALL_ADR          0x01
#define SERVO_MODE1_NO_USE_ALL_CALL_ADR       0x00
/** \} */

/**
 * \defgroup mode_2_register Mode 2 Register
 * \{
 */
#define SERVO_MODE2_OUT_LOGIC_NOT_INVERTED    0x00 << 4
#define SERVO_MODE2_OUT_LOGIC_INVERTED        0x01 << 4
#define SERVO_MODE2_OUT_CHANGE_ON_STOP_CMD    0x00 << 3
#define SERVO_MODE2_OUT_CHANGE_ON_ACK_CMD     0x01 << 3
#define SERVO_MODE2_OPEN_DRAIN_STRUCTURE      0x00 << 2
#define SERVO_MODE2_TOTEM_POLE_STRUCTURE      0x01 << 2
/** \} */

/**
 * \defgroup servo_min_max Servo Min Max
 * \{
 */
#define SERVO_DEFAULT_LOW_RESOLUTION          0  
#define SERVO_DEFAULT_HIGH_RESOLUTION         330

#define SERVO_GENERAL_CALL_ADR                0x00
#define SERVO_SOFT_RESET                      0x06

#define SERVO_VREF_3300                       3300
#define SERVO_VREF_5000                       5000
/** \} */

/**
 * \defgroup servo_motor Servo Motor
 * \{
 */
#define SERVO_MOTOR_1                         0x06
#define SERVO_MOTOR_2                         0x0A
#define SERVO_MOTOR_3                         0x0E
#define SERVO_MOTOR_4                         0x12
#define SERVO_MOTOR_5                         0x16
#define SERVO_MOTOR_6                         0x1A
#define SERVO_MOTOR_7                         0x1E
#define SERVO_MOTOR_8                         0x22
#define SERVO_MOTOR_9                         0x26
#define SERVO_MOTOR_10                        0x2A
#define SERVO_MOTOR_11                        0x2E
#define SERVO_MOTOR_12                        0x32
#define SERVO_MOTOR_13                        0x36
#define SERVO_MOTOR_14                        0x3A
#define SERVO_MOTOR_15                        0x3E
#define SERVO_MOTOR_16                        0x42

#define SERVO_POSITIVE_CH0_NEGATIVE_CH1       0xA0
#define SERVO_POSITIVE_CH2_NEGATIVE_CH3       0xA1
#define SERVO_POSITIVE_CH4_NEGATIVE_CH5       0xA2
#define SERVO_POSITIVE_CH6_NEGATIVE_CH7       0xA3
#define SERVO_POSITIVE_CH8_NEGATIVE_CH9       0xA4
#define SERVO_POSITIVE_CH10_NEGATIVE_CH11     0xA5
#define SERVO_POSITIVE_CH12_NEGATIVE_CH13     0xA6
#define SERVO_POSITIVE_CH14_NEGATIVE_CH15     0xA7
#define SERVO_POSITIVE_CH1_NEGATIVE_CH0       0xA8
#define SERVO_POSITIVE_CH3_NEGATIVE_CH2       0xA9
#define SERVO_POSITIVE_CH5_NEGATIVE_CH4       0xAA
#define SERVO_POSITIVE_CH7_NEGATIVE_CH6       0xAB
#define SERVO_POSITIVE_CH9_NEGATIVE_CH8       0xAC
#define SERVO_POSITIVE_CH11_NEGATIVE_CH10     0xAD
#define SERVO_POSITIVE_CH13_NEGATIVE_CH12     0xAE
#define SERVO_POSITIVE_CH15_NEGATIVE_CH14     0xAF

#define SERVO_POSITIVE_CH0                    0xB0
#define SERVO_POSITIVE_CH2                    0xB1
#define SERVO_POSITIVE_CH4                    0xB2
#define SERVO_POSITIVE_CH6                    0xB3
#define SERVO_POSITIVE_CH8                    0xB4
#define SERVO_POSITIVE_CH10                   0xB5
#define SERVO_POSITIVE_CH12                   0xB6
#define SERVO_POSITIVE_CH14                   0xB7
#define SERVO_POSITIVE_CH1                    0xB8
#define SERVO_POSITIVE_CH3                    0xB9
#define SERVO_POSITIVE_CH5                    0xBA
#define SERVO_POSITIVE_CH7                    0xBB
#define SERVO_POSITIVE_CH9                    0xBC
#define SERVO_POSITIVE_CH11                   0xBD
#define SERVO_POSITIVE_CH13                   0xBE
#define SERVO_POSITIVE_CH15                   0xBF
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
  uint8_t min_position;
  uint8_t max_position;
  uint16_t low_resolution;
  uint16_t high_resolution;

} servo_pos_and_res_t;

typedef struct
{
  uint8_t x;
  uint8_t in_min;
  uint8_t in_max;
  uint16_t out_min;
  uint16_t out_max;

} servo_map_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t oe;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address_of_pca9685;
    uint8_t slave_address_of_ltc2497;

    uint8_t min_pos;
    uint8_t max_pos;
    uint16_t vref;
    uint16_t low_res;
    uint16_t high_res;

    servo_pos_and_res_t pos_and_res;

} servo_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t oe;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address_of_pca9685;
    uint8_t i2c_address_of_ltc2497;
} servo_cfg_t;

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
void servo_cfg_setup ( servo_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SERVO_RETVAL servo_init ( servo_t *ctx, servo_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Servo click.
 */
void servo_default_cfg ( servo_t *ctx );

/**
 * @brief Generic write function of pca9685.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register using slave_address of pca9685.
 */
void servo_generic_write_of_pca9685 ( servo_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write function of ltc2497.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register using slave_address of ltc2497.
 */
void servo_generic_write_of_of_ltc2497 ( servo_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function of pca9685.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register using slave_address of pca9685.
 */
void servo_generic_read_of_pca9685 ( servo_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
/**
 * @brief Generic read function of ltc2497.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register using slave_address of ltc2497.
 */
void servo_generic_read_of_ltc2497 ( servo_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Setting function.
 *
 * @param ctx          Click object.
 * @param pos_and_res  Structure with position and resolution.
 *
 * @description This function setting position and resolution.
 */
void servo_setting ( servo_t *ctx, servo_pos_and_res_t pos_and_res );

/**
 * @brief Set Vref function.
 *
 * @param ctx    Click object.
 * @param v_ref  V ref.
 *
 * @description This function settings Vref of Servo Clicks.
 */
void servo_set_vref ( servo_t *ctx, uint16_t v_ref );

/**
 * @brief Stop function.
 *
 * @param ctx    Click object.
 * @param v_ref  V ref.
 *
 * @description When the servo_stop() function is started, all controls and communication with the servo motor are blocked.
 * To restore communication, you need to call the servo_start() function.
 * Use this function when you need to shut down the all motors quickly.
 */
void servo_stop ( servo_t *ctx );

/**
 * @brief Start function.
 *
 * @param ctx    Click object.
 *
 * @description Function for start work servo motor.
 */
void servo_start ( servo_t *ctx );

/**
 * @brief Soft reset function.
 *
 * @param ctx    Click object.
 *
 * @description Functions for soft reset chip.
 */
void servo_soft_reset ( servo_t *ctx );

/**
 * @brief Sleep function.
 *
 * @param ctx    Click object.
 *
 * @description Functions for sleep mode chip.
 */
void servo_sleep ( servo_t *ctx );

/**
 * @brief Set mode function.
 *
 * @param ctx       Click object.
 * @param mode      One of the two modes to be set.
 * @param w_data    Data that will be written in the register.
 *
 * @description This function sets mod.
 * 
 * @note 
 * Options for mode 1 that can be set:
 *      Restart ( enable or disable )
 *      Clock ( internal clock or EXTCLK pin clock )
 *      Auto-Increment ( enable or disable )
 *      Mode ( normal mode or low power mod )
 *      SubAddress 1 ( uses or does not use )
 *      SubAddress 2 ( uses or does not use )
 *      SubAddress 3 ( uses or does not use )
 *      Motor all call address ( uses or does not use )
 *      
 * Options for mode 2 that can be set:
 *      Output logic state ( not inverted or inverted )
 *      Outputs change ( Outputs change on STOP or ACK command )
 *      Outputs configured ( open-drain structure or totem pole structure)
 */
void servo_set_mode ( servo_t *ctx, uint8_t mode, uint8_t w_data );

/**
 * @brief Set position function.
 *
 * @param ctx       Click object.
 * @param motor     Motor to be set.
 * @param position  Position on which the motor will be set.
 *
 * @description This function sets position.
 */
void servo_set_position ( servo_t *ctx, uint8_t motor, uint8_t position );

/**
 * @brief Set frequency function.
 *
 * @param ctx      Click object.
 * @param freq     Motor to be set.
 *
 * @description This function sets frequency.
 */
void servo_set_freq ( servo_t *ctx, uint16_t freq );

/**
 * @brief Functions for reading adc value of current.
 *
 * @param ctx      Click object.
 * @param channel  The channel from which it is read.
 *
 * @description This function reads adc value of current.
 */
uint32_t servo_get_channel ( servo_t *ctx, uint8_t channel );

/**
 * @brief Functions for reading current in mA.
 *
 * @param ctx      Click object.
 * @param channel  The channel from which it is read.
 *
 * @description This function reads the current value of Servo Click witch motor spends.
 */
uint16_t setvo_get_current ( servo_t *ctx, uint8_t channel );

#ifdef __cplusplus
}
#endif
#endif  // _SERVO_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
