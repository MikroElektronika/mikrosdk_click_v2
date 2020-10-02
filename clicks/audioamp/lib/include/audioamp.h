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
 * \brief This file contains API for AudioAMP Click driver.
 *
 * \addtogroup audioamp AudioAMP Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AUDIOAMP_H
#define AUDIOAMP_H

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
#define AUDIOAMP_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AUDIOAMP_RETVAL  uint8_t

#define AUDIOAMP_OK           0x00
#define AUDIOAMP_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup address  Address
 * \{
 */
#define AUDIOAMP_I2C_ADDRESS_0                                      0x7C 
#define AUDIOAMP_I2C_ADDRESS_1                                      0x7D 
/** \} */ 

/**
 * \defgroup data_reg  Data Reg
 * \{
 */
#define AUDIOAMP_REG_MODE                                           0x00 
#define AUDIOAMP_REG_DIAG                                           0x20 
#define AUDIOAMP_REG_FAULT                                          0x40 
#define AUDIOAMP_REG_VOL_1                                          0x60 
#define AUDIOAMP_REG_VOL_2                                          0x80 
/** \} */

/**
 * \defgroup mode  Mode
 * \{
 */
#define AUDIOAMP_MODE_CH_1                                          0x00 
#define AUDIOAMP_MODE_CH_2                                          0x01 
#define AUDIOAMP_MODE_MUX                                           0x02 
#define AUDIOAMP_MODE_MUTE                                          0x03 
/** \} */

/**
 * \defgroup volume  Volume
 * \{
 */
#define AUDIOAMP_CMD_POWER_ON                                       0x1C 
#define AUDIOAMP_CMD_POWER_OFF                                      0x00 
#define AUDIOAMP_CMD_VOLUME_1                                       0x06 
#define AUDIOAMP_CMD_VOLUME_2                                       0x08 
#define AUDIOAMP_CMD_ENABLE                                         0x10 
#define AUDIOAMP_CMD_DISABLE                                        0x00 
/** \} */

/**
 * \defgroup data_cdm  Data Cdm
 * \{
 */
#define AUDIOAMP_CMD_DG_EN                                          0x10 
#define AUDIOAMP_CMD_DG_CONT                                        0x08 
#define AUDIOAMP_CMD_DG_RESET                                       0x06 
#define AUDIOAMP_CMD_DG_ILIMIT                                      0x04 
/** \} */

/**
 * \defgroup data_ch  Data Ch
 * \{
 */
#define AUDIOAMP_CH_1_BIT                                           0x04 
#define AUDIOAMP_CH_2_BIT                                           0x08 
#define AUDIOAMP_MUX_BIT                                            0x0C 
#define AUDIOAMP_MUTE_BIT                                           0x00 
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
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} audioamp_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} audioamp_cfg_t;

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
void audioamp_cfg_setup ( audioamp_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param audioamp Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AUDIOAMP_RETVAL audioamp_init ( audioamp_t *ctx, audioamp_cfg_t *cfg );

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
void audioamp_generic_write ( audioamp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void audioamp_generic_read ( audioamp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Turn on the Audio Amp click function
 *
 * @param ctx          Click object.
 * 
 * @description Function turn on the Audio Amp click
 * by set POEWR_ON and set INPUT_2 and INPUT_1 bits
 * to MODE CONTROL register of LM48100Q-Q1 chip.
 */
void audioamp_power_on ( audioamp_t *ctx );

/**
 * @brief Turn off the Audio Amp click function
 *
 * @param ctx          Click object.
 * 
 * @description Function turn off the Audio Amp click
 * by set POEWR_OFF bits
 * to MODE CONTROL register of LM48100Q-Q1 chip.
 */
void audioamp_power_off ( audioamp_t *ctx );

/**
 * @brief Set mux volume function
 *
 * @param ctx          Click object.
 * 
 * @param volume_value                    
 * 8-bit value from 0 to 31
 *
 * @description Function sets mux volume
 * to LM48100Q-Q1 chip on AudioAmp Click board.
 */
void audioamp_set_volume ( audioamp_t *ctx, uint8_t volume_value );

/**
 * @brief Set channel volume function
 *
 * @param ctx          Click object.
 * 
 * @param channel                        
 * - 0 : CHANNEL 1;
 * - 1 : CHANNEL 2;
 *
 * @param volume_value                    
 * 8-bit value from 0 to 31
 *
 * @description Function sets volume of selected channel
 * of LM48100Q-Q1 chip on AudioAmp Click board.
 */
void audioamp_set_volume_channel ( audioamp_t *ctx, uint8_t channel, uint8_t volume_value );

/**
 * @brief Enable amplifier function
 *
 * @param ctx          Click object.
 * 
 * @description Function enable the Audio Amp click
 * by set POEWR_ON bits
 * to MODE CONTROL register of LM48100Q-Q1 chip.
 */
void audioamp_enable ( audioamp_t *ctx );

/**
 * @brief Disable amplifier function
 *
 * @param ctx          Click object.
 * 
 * @description Function disable the Audio Amp click
 * by set POEWR_OFF bits
 * to MODE CONTROL register of LM48100Q-Q1 chip.
 */
void audioamp_disable ( audioamp_t *ctx );

/**
 * @brief Set mute mode function
 *
 * @param ctx          Click object.
 * 
 * @description Function set mute mode
 * by claer INPUT_2 and INPUT_1 bits
 * to MODE CONTROL register of LM48100Q-Q1 chip.
 */
void audioamp_mute_mode ( audioamp_t *ctx );

/**
 * @brief Set unmute mode function
 *
 * @param ctx          Click object.
 * 
 * @description Function set unmute mode
 * by sets INPUT_2 and INPUT_1 bits
 * to MODE CONTROL register of LM48100Q-Q1 chip.
 */
void audioamp_unmute_mode ( audioamp_t *ctx );

/**
 * @brief Set normal opeation function
 *
 * @param ctx          Click object.
 * 
 * @description Function set mute mode
 * by claer all bits
 * to FAULT DETECTION CONTROL register of LM48100Q-Q1 chip.
 */
void audioamp_set_normal_operation ( audioamp_t *ctx );

/**
 * @brief Set fault detection control function
 *
 * @param ctx          Click object.
 * 
 * @param input_command
 * - 0 : Ignore output short circuit fault (outputs shorted together);
 * - 1 : Ignore output short circuit fault;
 * - 2 : Ignore output short to VDD or GND fault;
 * - 3 : Ignore output over-current fault;
 * - 4 : Ignore thermal overload fault;
 *
 * @description Function set fault detection control
 * by set command to FAULT DETECTION CONTROL register of LM48100Q-Q1 chip.
 */
void audioamp_set_fault_detecton_control( audioamp_t *ctx, uint8_t input_command );

/**
 * @brief Set input mixer mode function
 *
 * @param ctx          Click object.
 * 
 * @param input_mode
 * - 0 : INPUT 1 only;
 * - 1 : INPUT 2 only;
 * - 2 : INPUT 1 & INPUT 2;
 * - 3 : MUTE;
 *
 * @description Function set input mixer mode
 * by sets command to MODE CONTROL register of LM48100Q-Q1 chip.
 */
void audioamp_set_input( audioamp_t *ctx, uint8_t input_mode );

/**
 * @brief Check interrupt status function
 *
 * @param ctx          Click object.
 * 
 * @param result
 * - 0 : detected;
 * - 1 : not detected;
 *
 * @description Function check interrupt status
 * by return value of INT pin
 * of LM48100Q-Q1 chip on AudioAmp Click board.
 */
uint8_t audioamp_check_status ( audioamp_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AUDIOAMP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
