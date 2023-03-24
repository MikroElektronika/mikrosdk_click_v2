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
 * \brief This file contains API for StereoAmp Click driver.
 *
 * \addtogroup stereoamp StereoAmp Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef STEREOAMP_H
#define STEREOAMP_H

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
#define STEREOAMP_MAP_MIKROBUS( cfg, mikrobus )  \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.fll  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
  cfg.flr  = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define STEREOAMP_RETVAL  uint8_t

#define STEREOAMP_OK                                        0x00
#define STEREOAMP_INIT_ERROR                                0xFF
/** \} */                                                   
                                                            
/**                                                         
 * \defgroup slave_address Slave Address                    
 * \{                                                       
 */                                                         
#define STEREOAMP_I2C_ADDRESS_0                             0x7C
#define STEREOAMP_I2C_ADDRESS_1                             0x7D
/** \} */

/**
 * \defgroup ctrl_reg Control Register
 * \{
 */
#define STEREOAMP_CTRL_REG_MODE_CONTROL                     0x00
#define STEREOAMP_CTRL_REG_DIAGNOSTIC_CONTROL               0x20
#define STEREOAMP_CTRL_REG_FAULT_DETECTION                  0x40
#define STEREOAMP_CTRL_REG_VOLUME_CONTROL1                  0x60
#define STEREOAMP_CTRL_REG_VOLUME_CONTROL2                  0x80
/** \} */

/**
 * \defgroup diag_reg Diagnostic Control Register
 * \{
 */
#define STEREOAMP_DIAG_REG_FIX_ILIMIT                       0x00
#define STEREOAMP_DIAG_REG_ILIMIT                           0x02
#define STEREOAMP_DIAG_REG_DG_RESET                         0x04
#define STEREOAMP_DIAG_REG_DG_ONE_SHOT                      0x00
#define STEREOAMP_DIAG_REG_DG_CONT                          0x08
#define STEREOAMP_DIAG_REG_DG_DISABLE                       0x00
#define STEREOAMP_DIAG_REG_DG_EN                            0x10
/** \} */

/**
 * \defgroup mode Mode Register
 * \{
 */
#define STEREOAMP_MODE_POWER_OFF                            0x00
#define STEREOAMP_MODE_POWER_ON                             0x10
#define STEREOAMP_MODE_INPUT1                               0x04
#define STEREOAMP_MODE_INPUT1_OFF                           0x00
#define STEREOAMP_MODE_INPUT2                               0x08
#define STEREOAMP_MODE_INPUT2_OFF                           0x00
#define STEREOAMP_MODE_BOTH_CHANNELS                        0x0C
/** \} */

/**
 * \defgroup flt_det_reg Fault Detection Control Register
 * \{
 */
#define STEREOAMP_FLT_DET_REG_OUTPUT_SHT                    0x01
#define STEREOAMP_FLT_DET_REG_OUTPUT_OPEN                   0x02
#define STEREOAMP_FLT_DET_REG_RAIL_SHT                      0x04
#define STEREOAMP_FLT_DET_REG_OVF                           0x08
#define STEREOAMP_FLT_DET_REG_TSD                           0x10
/** \} */

/**
 * \defgroup mask Data Mask
 * \{
 */
#define STEREOAMP_MASK_DATA                                 0x1F
#define STEREOAMP_MASK_ADDR                                 0xE0
#define STEREOAMP_MASK_CHANNEL                              0x01
/** \} */

/**
 * \defgroup output Output
 * \{
 */
#define STEREOAMP_OUTPUT_LEFT_SPEAKER                       0x01
#define STEREOAMP_OUTPUT_RIGHT_SPEAKER                      0x00
/** \} */

/**
 * \defgroup gain Volume Control
 * \{
 */
#define STEREOAMP_GAIN_NEG_80dB                             0x00
#define STEREOAMP_GAIN_NEG_54dB                             0x01
#define STEREOAMP_GAIN_NEG_40_5dB                           0x02
#define STEREOAMP_GAIN_NEG_34_5dB                           0x03
#define STEREOAMP_GAIN_NEG_30dB                             0x04
#define STEREOAMP_GAIN_NEG_27dB                             0x05
#define STEREOAMP_GAIN_NEG_24dB                             0x06
#define STEREOAMP_GAIN_NEG_21dB                             0x07
#define STEREOAMP_GAIN_NEG_18dB                             0x08
#define STEREOAMP_GAIN_NEG_15dB                             0x09
#define STEREOAMP_GAIN_NEG_13_5dB                           0x0A
#define STEREOAMP_GAIN_NEG_12dB                             0x0B
#define STEREOAMP_GAIN_NEG_10_5dB                           0x0C
#define STEREOAMP_GAIN_NEG_9dB                              0x0D
#define STEREOAMP_GAIN_NEG_7_5dB                            0x0E
#define STEREOAMP_GAIN_NEG_6dB                              0x0F
#define STEREOAMP_GAIN_NEG_4_5dB                            0x10
#define STEREOAMP_GAIN_NEG_3dB                              0x11
#define STEREOAMP_GAIN_NEG_1_5dB                            0x12
#define STEREOAMP_GAIN_NEG_0dB                              0x13
#define STEREOAMP_GAIN_1_5dB                                0x14
#define STEREOAMP_GAIN_3dB                                  0x15
#define STEREOAMP_GAIN_4_5dB                                0x16
#define STEREOAMP_GAIN_6dB                                  0x17
#define STEREOAMP_GAIN_7_5dB                                0x18
#define STEREOAMP_GAIN_9dB                                  0x19
#define STEREOAMP_GAIN_10_5dB                               0x1A
#define STEREOAMP_GAIN_12dB                                 0x1B
#define STEREOAMP_GAIN_13_5dB                               0x1C
#define STEREOAMP_GAIN_15dB                                 0x1D
#define STEREOAMP_GAIN_16_5dB                               0x1E
#define STEREOAMP_GAIN_18dB                                 0x1F
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

    digital_in_t fll;
    digital_in_t flr;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 
    
    uint8_t slave_address_0;
    uint8_t slave_address_1;

} stereoamp_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t fll;
    pin_name_t flr;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address_0;
    uint8_t i2c_address_1;

} stereoamp_cfg_t;

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
 * @param cfg                       Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void stereoamp_cfg_setup ( stereoamp_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx                       Click object.
 * @param cfg                       Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
STEREOAMP_RETVAL stereoamp_init ( stereoamp_t *ctx, stereoamp_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 *
 * @description This function executes default configuration for LTC2601 click.
 */
void stereoamp_default_cfg ( stereoamp_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx                       Click object.
 * @param ch_address                8-bit channel address.
 * -------------------------------------
 * <pre>
 *     0 = right channel ( speaker )
 *     1 = left channel ( speaker )
 * </pre>
 * -------------------------------------
 * @param reg_addr                  Register address.
 * @param tx_data                   Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void stereoamp_generic_write ( stereoamp_t *ctx, uint8_t ch_addr, uint8_t reg_addr, uint8_t tx_data );

/**
 * @brief Set the volume function.
 *
 * @param ctx                       Click object.
 * @param volume                    5-bit volume value from 0 ( 0x00 ) to 31 ( 0x1F ).
 *
 * @description This function set the volume of both channels to the 
 * Volume Control register address of LM48100Q-Q1 chip on StereoAmp click board.
 */
void stereoamp_set_volume ( stereoamp_t *ctx, uint8_t volume );

/**
 * @brief Set the mute mode function.
 *
 * @param ctx                       Click object.
 *
 * @description This function set the mute mode of both channels to the
 * Volume Control register address of LM48100Q-Q1 chip on StereoAmp click board.
 */
void stereoamp_mute ( stereoamp_t *ctx );

/**
 * @brief Soft reset function.
 *
 * @param ctx                       Click object.
 *
 * @description This function set soft reset by write to the
 * Diagnostic Control register address of LM48100Q-Q1 chip on StereoAmp click board.
 */
void stereoamp_soft_reset ( stereoamp_t *ctx );

/**
 * @brief Enable the diagnostic function.
 *
 * @param ctx                       Click object.
 *
 * @description This function enable the diagnostic by write to the
 * Diagnostic Control register address of LM48100Q-Q1 chip on StereoAmp click board.
 */
void stereoamp_enable_diagnostic ( stereoamp_t *ctx );

/**
 * @brief Set the power On by channel function.
 *
 * @param ctx                       Click object.
 *
 * @description This function set the power On of both channels by write to the
 * Mode Control register address of LM48100Q-Q1 chip on StereoAmp click board.
 */
void stereoamp_set_power_on ( stereoamp_t *ctx );

/**
 * @brief Enable the fault function.
 *
 * @param ctx                       Click object.
 *
 * @description This function enable the fault of both channels by write to the
 * Fault Detection Control register address of LM48100Q-Q1 chip on StereoAmp click board.
 */
void stereoamp_enable_fault ( stereoamp_t *ctx );

/**
 * @brief Check the fault of the left speaker function.
 *
 * @param ctx                       Click object.
 *
 * @description This function check the fault of the left speaker
 * by get states of AN pin of StereoAmp click board.
 */
uint8_t stereoamp_check_fault_left ( stereoamp_t *ctx );

/**
 * @brief Check the fault of the right speaker function.
 *
 * @param ctx                       Click object.
 *
 * @description This function check the fault of the right speaker
 * by get states of INT pin of StereoAmp click board.
 */
uint8_t stereoamp_check_fault_right ( stereoamp_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _STEREOAMP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
