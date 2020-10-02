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
 * \brief This file contains API for HAPTIC Click driver.
 *
 * \addtogroup haptic HAPTIC Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HAPTIC_H
#define HAPTIC_H

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
#define HAPTIC_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HAPTIC_RETVAL  uint8_t

#define HAPTIC_OK           0x00
#define HAPTIC_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address I2C address
 * \{
 */
#define HAPTIC_I2C_ADDRESS                                          0x5A
/** \} */

/**
 * \defgroup register_address Register address
 * \{
 */
#define HAPTIC_REG_STATUS                                           0x00
#define HAPTIC_REG_MODE                                             0x01
#define HAPTIC_REG_RTPIN                                            0x02
#define HAPTIC_REG_LIBRARY                                          0x03
#define HAPTIC_REG_WAVESEQ1                                         0x04
#define HAPTIC_REG_WAVESEQ2                                         0x05
#define HAPTIC_REG_WAVESEQ3                                         0x06
#define HAPTIC_REG_WAVESEQ4                                         0x07
#define HAPTIC_REG_WAVESEQ5                                         0x08
#define HAPTIC_REG_WAVESEQ6                                         0x09
#define HAPTIC_REG_WAVESEQ7                                         0x0A
#define HAPTIC_REG_WAVESEQ8                                         0x0B

#define HAPTIC_REG_GO                                               0x0C
#define HAPTIC_REG_OVERDRIVE                                        0x0D
#define HAPTIC_REG_SUSTAINPOS                                       0x0E
#define HAPTIC_REG_SUSTAINNEG                                       0x0F
#define HAPTIC_REG_BREAK                                            0x10
#define HAPTIC_REG_AUDIOCTRL                                        0x11
#define HAPTIC_REG_AUDIOMININ                                       0x12
#define HAPTIC_REG_AUDIOMAXIN                                       0x13
#define HAPTIC_REG_AUDIOMINOUT                                      0x14
#define HAPTIC_REG_AUDIOMAXOUT                                      0x15
#define HAPTIC_REG_RATEDV                                           0x16
#define HAPTIC_REG_CLAMPV                                           0x17
#define HAPTIC_REG_AUTOCALCOMP                                      0x18
#define HAPTIC_REG_AUTOCALEMF                                       0x19
#define HAPTIC_REG_FEEDBACK                                         0x1A
#define HAPTIC_REG_CONTROL1                                         0x1B
#define HAPTIC_REG_CONTROL2                                         0x1C
#define HAPTIC_REG_CONTROL3                                         0x1D
#define HAPTIC_REG_CONTROL4                                         0x1E
#define HAPTIC_REG_VBAT                                             0x21
#define HAPTIC_REG_LRARESON                                         0x22
/** \} */

/**
 * \defgroup mode_select Mode select
 * \{
 */
#define HAPTIC_MODE_INTTRIG                                         0x00
#define HAPTIC_MODE_EXTTRIGEDGE                                     0x01
#define HAPTIC_MODE_EXTTRIGLVL                                      0x02
#define HAPTIC_MODE_PWMANALOG                                       0x03
#define HAPTIC_MODE_AUDIOVIBE                                       0x04
#define HAPTIC_MODE_REALTIME                                        0x05
#define HAPTIC_MODE_DIAGNOS                                         0x06
#define HAPTIC_MODE_AUTOCAL                                         0x07
/** \} */

/**
 * \defgroup default_min_input Deafult min input
 * \{
 */
#define HAPTIC_DEFAULT_MIN_INPUT                                    0xC0
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

    digital_out_t cs;
    digital_out_t pwm;

    // Input pins 
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} haptic_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t cs;
    pin_name_t pwm;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} haptic_cfg_t;

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
void haptic_cfg_setup ( haptic_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HAPTIC_RETVAL haptic_init ( haptic_t *ctx, haptic_cfg_t *cfg );

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
void haptic_generic_write ( haptic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void haptic_generic_read ( haptic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Enable the device function.
 *
 * @param ctx          Click object.
 *
 * @description Function enable the device
 * on the DRV2605 chip by set RST pin ( high ) on Haptic Click board.
 *
 * @note
 * After calling this function, you must call delay for approximately 200 ms.
 */
void haptic_enable (  haptic_t *ctx );

 /**
 * @brief Disable the device function.
 *
 * @param ctx          Click object.
 *
 * @description Function disable the device function
 * on the DRV2605 chip by clear RST pin ( low ) on Haptic Click board.
 */
void haptic_disable ( haptic_t *ctx );

 /**
 * @brief Generic write the byte of data function.
 * 
 * @param ctx           Click object.
 * @param reg_address   8-bit register address.
 * @param write_data    8-bit data to write to given address.
 *
 * @description Function write the byte of data to given 8-bit register address
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_write_byte (  haptic_t *ctx, uint8_t reg_address, uint8_t write_data );

 /**
 * @brief Generic read the byte of data function.
 *
 * @param ctx          Click object.
 * @param reg_address  8-bit register address.
 *
 * @return result
 * 8-bit read data from given address
 *
 *
 * @description Function read the byte of data from given 8-bit register address
 * of DRV2605 chip on Haptic Click board.
 */
uint8_t haptic_read_byte ( haptic_t *ctx, uint8_t reg_address );

 /**
 * @brief Sets the Haptic click to desired mode function.
 *
 * @param ctx          Click object.
 * @param sel_mode     Select mode.
 *
 * @description Function sets the desired mode by write mode register
 * of the DRV2605 chip on Haptic Click board.
 */
void haptic_set_mode ( haptic_t *ctx, uint8_t sel_mode );

 /**
 * @brief Resets all the registers function.
 *
 * @param ctx          Click object.
 *
 * @description Function resets all the registers by set highest bit of mode registe
 * of the DRV2605 chip on Haptic Click board.
 */
void haptic_soft_reset ( haptic_t *ctx );

 /**
 * @brief Get status register value function.
 *
 * @param ctx          Click object.
 *
 * @return result
 * 8-bit read status data.
 *
 * @description Function reads the value from the status register
 * of DRV2605 chip on Haptic Click board.
 */
uint8_t haptic_get_status ( haptic_t *ctx );

 /**
 * @brief Sets the desired input for RTP mode function.
 *
 * @param ctx          Click object.
 * @param input        8-bit desired input for RTP mode.
 *
 * @description Function sets the desired input for RTP mode
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_rtp_input ( haptic_t *ctx, uint8_t input );

 /**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 *
 * @description Function sets the device in HI state
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_state_hi ( haptic_t *ctx );

 /**
 * @brief Sets the desired library of vibrating patterns to read function.
 *
 * @param ctx          Click object.
 * @param library      8-bit desired pattern library for reading.
 *
 * @description Function sets the desired library of vibrating patterns to read register
 * of DRV2605 chip on Haptic Click board.
 */
uint8_t haptic_set_library ( haptic_t *ctx, uint8_t library );

 /**
 * @brief Starts moving the motor function.
 *
 * @param ctx          Click object.
 *
 * @description Function starts reading the desired pattern 
 * and moving the motor by set lowest bit of go register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_start_motor ( haptic_t *ctx );

 /**
 * @brief Sets overdrive offset function.
 *
 * @param ctx          Click object.
 * @param temp_data     8-bit desired overdrive offset.
 *
 * @description Function sets overdrive offset by write 
 * desired overdrive value to address of the target register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_overdrive_offset ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets desired sustain offset - positive function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired positive sustain offset.
 *
 * @description Function sets desired sustain offset - positive by write
 * desired positive sustain value to address of the target register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_sustain_offset_positive ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets desired sustain offset - negative function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired negative sustain offset.
 *
 * @description Function sets desired sustain offset - negative by write
 * desired negative sustain value to address of the target register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_sustain_offset_negative ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets desired brake time offset function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired brake time offset.
 *
 * @description Function sets desired brake time offset by write
 * desired brake time value to address of the target register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_brake_time_offset ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets minimum input for audio to vibe mode function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired minimum input
 *
 * @description Function sets minimum input for audio to vibe mode by write
 * desired minimum input value to address of the target register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_audio_minimum_input ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets maximum input for audio to vibe mode function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired maximum input.
 *
 * @description Function sets maximum input for audio to vibe mode by write
 * desired maximum input value to address of the target register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_audio_maximum_input ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets minimum output for audio to vibe mode function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired minimum output.
 *
 * @description Function sets minimum output for audio to vibe mode by write
 * desired minimum output value to address of the target register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_audio_minimum_output ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets maximum output for audio to vibe mode function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired maximum output
 *
 * @description Function sets maximum output for audio to vibe mode by write
 * desired maximum output value to address of the target register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_audio_maximum_output ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets the reference voltage function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired value.
 *
 * @description Function sets the reference voltage for full-scale output during closed-loop 
 * by write desired value to address of the target register 
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_rated_voltage ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets a clamp function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired value.
 *
 * @description Function sets a clamp so that the automatic overdrive is bounded
 * by write desired value to address of the target register 
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_overdrive_clamp_voltage ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets the peak detection time function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired value.
 *
 * @return result
 * - 0 : if successful.
 *
 * @description Function sets the peak detection time for the audio-to-vibe signal path
 * by write desired value to address of the target register 
 * of DRV2605 chip on Haptic Click board.
 */
uint8_t haptic_set_audio_peak_time ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Sets the low-pass filter frequency function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired value.
 *
 * @description Function sets the low-pass filter frequency for the audio-to-vibe signal path
 * by write desired value to address of the target register
 * of DRV2605 chip on Haptic Click board.
 */
uint8_t haptic_set_audio_low_pass_filter ( haptic_t *ctx, uint8_t temp_data );

 /**
 * @brief Reads the voltage-compensation function.
 *
 * @param ctx          Click object.
 *
 * @return result                      
 * 8-bit value contained in the register
 *
 * @description Function get the voltage-compensation result after execution of auto calibration
 * by read value from the target register address
 * of DRV2605 chip on Haptic Click board.
 */
uint8_t haptic_get_calibration_result_comp ( haptic_t *ctx );

 /**
 * @brief Reads the rated back - EMF function.
 *
 * @param ctx          Click object.
 *
 * @return result
 * 8-bit value contained in the register
 *
 * @description Function get the rated back - EMF result after execution of auto calibration
 * by read value from the target register address
 * of DRV2605 chip on Haptic Click board.
 */
uint8_t haptic_get_calibration_result_emf ( haptic_t *ctx );
 
 /**
 * @brief Reading of the supply voltage function.
 *
 * @param ctx          Click object.
 *
 * @return result
 * 8-bit voltage on VDD pin
 *
 * @description Function does a real-time reading of the supply voltage at the VDD pin
 * of DRV2605 chip on Haptic Click board.
 */
uint8_t haptic_get_supply_voltage_value ( haptic_t *ctx );

 /**
 * @brief Reads the measurement of the LRA resonance period function.
 *
 * @param ctx          Click object.
 *
 * @return result
 * 8-bit voltage on VDD pin
 *
 * @description Function gets the measurement of the LRA resonance period
 * by read value from the LRA resonance register of DRV2605 chip on Haptic Click board.
 *
 * @note
 * The device must be actively sending a waveform to take a reading.
 */
uint8_t haptic_get_lra_resonance_period ( haptic_t *ctx );

 /**
 * @brief Sets the Haptic click in ERM mode function.
 *
 * @param ctx          Click object.
 *
 * @description Function sets the Haptic click in ERM mode
 * by write clear highest bit of feedback register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_to_erm_mode ( haptic_t *ctx );

 /**
 * @brief Sets the Haptic click in LRA mode function.
 *
 * @param ctx          Click object.
 *
 * @description Function sets the Haptic click in LRA mode
 * by write set highest bit of feedback register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_to_lra_mode ( haptic_t *ctx );

 /**
 * @brief Sets the feedback gain ratio function.
 *
 * @param ctx            Click object.
 * @param brake_factor   8-bit desired brake factor
 *
 * @return
 * - 0 if failed.
 * - 1 if successful.
 *
 * @description Function sets the feedback gain ratio between braking gain and driving gain.
 * In general, adding additional feedback gain while braking is desirable
 * so that the actuator brakes as quickly as possible.
 * Large ratios provide less-stable operation than lower ones.
 */
uint8_t haptic_setBrakeFactor( haptic_t *ctx, uint8_t brake_factor );

 /**
 * @brief Selects a loop gain function.
 *
 * @param ctx          Click object.
 * @param gain         8-bit desired gain
 *
 * @return
 * - 0 if failed.
 * - 1 if successful.
 *
 * @description Function selects a loop gain for the feedback control
 * of DRV2605 chip on Haptic Click board.
 */
uint8_t haptic_set_loop_gain ( haptic_t *ctx, uint8_t gain );

 /**
 * @brief Sets the input to analog function.
 *
 * @param ctx          Click object.
 *
 * @description Function sets the input of the Haptic click to analog
 * by set second lowest bit of control 3 register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_input_to_analog ( haptic_t *ctx );

 /**
 * @brief Sets the input for PWM control function.
 *
 * @param ctx          Click object.
 *
 * @description Function sets the input for PWM control of the motor
 * by clear second lowest bit of control 3 register
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_set_input_to_pwm ( haptic_t *ctx );

  /**
 * @brief Sets the waveform identifier function.
 *
 * @param ctx          Click object.
 * @param temp_data    8-bit desired waveform.
 *
 * @description Function sets the waveform identifier of the waveform to be played
 * of DRV2605 chip on Haptic Click board.
 * A waveform identifier is an integer value referring
 * to the index position of a waveform in a ROM library. Playback begins at
 * register address 0x04 when the user asserts the GO bit ( register 0x0C ).
 * When playback of that waveform ends, the waveform sequencer plays the
 * next waveform identifier held in register 0x05
 */
void haptic_set_sequence ( haptic_t *ctx, uint8_t temp_data );

  /**
 * @brief Applies a 0.9-V common mode voltage function.
 *
 * @param ctx          Click object.
 *
 * @description Function applies a 0.9-V common mode voltage to the IN/TRIG pin
 * by write value of 0xB3 to control 1 register address
 * of DRV2605 chip on Haptic Click board.
 */
void haptic_enable_ac_coulping ( haptic_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _HAPTIC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
