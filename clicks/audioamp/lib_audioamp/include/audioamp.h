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
 * \{
 */

#ifndef AUDIOAMP_H
#define AUDIOAMP_H

#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus  MikroBUS
 * \{
 */
#define AUDIOAMP_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code  Error Code
 * \{
 */
#define AUDIOAMP_OK            0
#define AUDIOAMP_INIT_ERROR  (-1)
/** \} */

/**
 * \defgroup dev_addr  Device Address
 * \{
 */
#define AUDIOAMP_I2C_ADDRESS_0  0x7C
#define AUDIOAMP_I2C_ADDRESS_1  0x7D
/** \} */

/**
 * \defgroup ch_sel  Channel Selectors
 * \{
 */
#define AUDIOAMP_IN_1  0x04
#define AUDIOAMP_IN_2  0x08
/** \} */

/**
 * \defgroup diag_set  Diagnostic Settings
 * \{
 */
#define AUDIOAMP_DG_EN      0x10
#define AUDIOAMP_DG_CONT    0x08
#define AUDIOAMP_DG_RESET   0x06
#define AUDIOAMP_DG_ILIMIT  0x04
/** \} */

/** \} */ // End group macro

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

    // Static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} audioamp_cfg_t;

/** \} */ // End types group

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
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t audioamp_init ( audioamp_t *ctx, audioamp_cfg_t *cfg );

/**
 * @brief Turn on the Audio Amp click function.
 *
 * @param ctx  Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description Function turns on the Audio Amp click
 * by setting POWER_ON and set INPUT_2 and INPUT_1 bits
 * to MODE CONTROL register of LM48100Q-Q1 chip.
 */
err_t audioamp_power_on ( audioamp_t *ctx );

/**
 * @brief Turn off the Audio Amp click function.
 *
 * @param ctx  Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description Function turns off the Audio Amp click
 * by setting POWER_OFF bit to MODE CONTROL register of LM48100Q-Q1 chip.
 */
err_t audioamp_power_off ( audioamp_t *ctx );

/**
 * @brief Set volume function.
 *
 * @param ctx  Click object.
 * @param in_sel  Enter AUDIOAMP_IN_1 to select input 1 and/or
 *                enter AUDIOAMP_IN_2 to select input 2.
 * @param volume_level  Enter volume level from 1 to 32.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description Function sets the volume of the selected input
 * of LM48100Q-Q1 chip on AudioAmp Click board.
 */
err_t audioamp_set_volume ( audioamp_t *ctx, uint8_t in_sel, uint8_t volume_level );

/**
 * @brief Mute input function.
 *
 * @param ctx  Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description Function allows the user to mute the input
 * by clearing INPUT_2 and INPUT_1 bits
 * to MODE CONTROL register of LM48100Q-Q1 chip.
 */
err_t audioamp_mute ( audioamp_t *ctx );

/**
 * @brief Unmute input function.
 *
 * @param ctx  Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description Function allows the user to unmute the input
 * by setting INPUT_2 and INPUT_1 bits
 * to MODE CONTROL register of LM48100Q-Q1 chip.
 */
err_t audioamp_unmute ( audioamp_t *ctx );

/**
 * @brief Set normal opeation of Fault function.
 *
 * @param ctx  Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description Function sets the normal opration mode
 * by clearing all bits
 * to FAULT DETECTION CONTROL register of LM48100Q-Q1 chip.
 */
err_t audioamp_set_fault_normal_operation ( audioamp_t *ctx );

/**
 * @brief Set fault detection control function.
 *
 * @param ctx  Click object.
 * @param input_command  Fault settings :
 *  0 : Ignore output short circuit fault (outputs shorted together);
 *  1 : Ignore output short circuit fault;
 *  2 : Ignore output short to VDD or GND fault;
 *  3 : Ignore output over-current fault;
 *  4 : Ignore thermal overload fault;
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description Function sets a fault detection control
 * by setting the entered command to FAULT DETECTION CONTROL register of LM48100Q-Q1 chip.
 */
err_t audioamp_set_fault_detecton_control ( audioamp_t *ctx, uint8_t input_command );

/**
 * @brief Set diagnostic control function.
 *
 * @param ctx  Click object.
 * @param input_command  Diagnostic settings - to see the diagnostic settings
 * refer to the Diagnostic Settings option.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description Function sets a diagnostic control
 * by setting the entered command to DIAGNOSTIC CONTROL register of LM48100Q-Q1 chip.
 */
err_t audioamp_set_diagnostic_control ( audioamp_t *ctx, uint8_t input_command );

/**
 * @brief Check Fault status function.
 *
 * @param ctx  Click object.
 * @return 0 - detected,
 *         1 - not detected.
 *
 * @description Function checks the status of fault pin
 * of LM48100Q-Q1 chip on AudioAmp Click board.
 */
uint8_t audioamp_check_fault ( audioamp_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // AUDIOAMP_H

/** \} */ // End public_function group
/** \} */ // End click Driver group

// ------------------------------------------------------------------------ END
