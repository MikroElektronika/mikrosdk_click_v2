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
 * \brief This file contains API for AudioAmp 3 Click driver.
 *
 * \addtogroup audioamp3 AudioAmp 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AUDIOAMP3_H
#define AUDIOAMP3_H

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
#define AUDIOAMP3_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AUDIOAMP3_RETVAL       uint8_t
#define AUDIOAMP3_STATUS_T     uint8_t

#define AUDIOAMP3_OK                                        0x00
#define AUDIOAMP3_INIT_ERROR                                0xFF
/** \} */                                                   
                                                            
/**                                                                   
 * \defgroup slave_address Slave Address                              
 * \{                                                                 
 */                                                                   
#define AUDIOAMP3_I2C_SLAVE_ADDRESS                         0x6C
/** \} */                                                   
                                                            
/**                                                         
 * \defgroup diag Diagnostic Register                       
 * \{                                                       
 */                                                         
#define AUDIOAMP3_DIAG_LATCHED_FAULT_REG_1                  0x00
#define AUDIOAMP3_DIAG_LATCHED_FAULT_REG_2                  0x01
#define AUDIOAMP3_DIAG_LATCHED_REG_1                        0x02
#define AUDIOAMP3_DIAG_LATCHED_REG_2                        0x03
/** \} */                                                   
                                                            
/**                                                         
 * \defgroup ext_status External Status Register            
 * \{                                                       
 */                                                         
#define AUDIOAMP3_EXT_STATUS_REG_1                          0x04
#define AUDIOAMP3_EXT_STATUS_REG_2                          0x05
#define AUDIOAMP3_EXT_STATUS_REG_3                          0x06
#define AUDIOAMP3_EXT_STATUS_REG_4                          0x07
#define AUDIOAMP3_EXT_STATUS_REG_5                          0x11
/** \} */                                                   
                                                            
/**                                                         
 * \defgroup ext_ctrl External Control Register             
 * \{                                                       
 */                                                         
#define AUDIOAMP3_EXT_CTRL_REG_1                            0x08
#define AUDIOAMP3_EXT_CTRL_REG_2                            0x09
#define AUDIOAMP3_EXT_CTRL_REG_3                            0x0A
#define AUDIOAMP3_EXT_CTRL_REG_4                            0x0B
#define AUDIOAMP3_EXT_CTRL_REG_5                            0x0C
#define AUDIOAMP3_EXT_CTRL_REG_6                            0x0D
#define AUDIOAMP3_EXT_CTRL_REG_7                            0x10
/** \} */                                                   
                                                            
/**                                                         
 * \defgroup sel Gain Select                                
 * \{                                                       
 */                                                         
#define AUDIOAMP3_SEL_CH_1_GAIN_12dB                        0x00
#define AUDIOAMP3_SEL_CH_1_GAIN_20dB                        0x01
#define AUDIOAMP3_SEL_CH_1_GAIN_32dB                        0x03
#define AUDIOAMP3_SEL_CH_2_GAIN_12dB                        0x00
#define AUDIOAMP3_SEL_CH_2_GAIN_20dB                        0x04
#define AUDIOAMP3_SEL_CH_2_GAIN_32dB                        0x0C
#define AUDIOAMP3_SEL_CH_3_GAIN_12dB                        0x00
#define AUDIOAMP3_SEL_CH_3_GAIN_20dB                        0x10
#define AUDIOAMP3_SEL_CH_3_GAIN_32dB                        0x30
#define AUDIOAMP3_SEL_CH_4_GAIN_12dB                        0x00
#define AUDIOAMP3_SEL_CH_4_GAIN_20dB                        0x40
#define AUDIOAMP3_SEL_CH_4_GAIN_32dB                        0xC0
#define AUDIOAMP3_SEL_ALL_CH_GAIN_26dB                      0xAA
/** \} */

/**
 * \defgroup overcurr Overcurrent Control
 * \{
 */
#define AUDIOAMP3_OVERCURR_CH_1_LIMIT_LVL_1                 0x00
#define AUDIOAMP3_OVERCURR_CH_1_LIMIT_LVL_2                 0x10
#define AUDIOAMP3_OVERCURR_CH_2_LIMIT_LVL_1                 0x00
#define AUDIOAMP3_OVERCURR_CH_2_LIMIT_LVL_2                 0x20
#define AUDIOAMP3_OVERCURR_CH_3_LIMIT_LVL_1                 0x00
#define AUDIOAMP3_OVERCURR_CH_3_LIMIT_LVL_2                 0x40
#define AUDIOAMP3_OVERCURR_CH_4_LIMIT_LVL_1                 0x00
#define AUDIOAMP3_OVERCURR_CH_4_LIMIT_LVL_2                 0x80
#define AUDIOAMP3_CURRENT_LIMIT_LVL_2_ALL_CH                0xF0
#define AUDIOAMP3_DIS_THERMAL_FOLDBACK                      0x01
/** \} */                                              

/**
 * \defgroup freq_sel Switching Frequency Select and Clip_OTW Configuration
 * \{
 */
#define AUDIOAMP3_FREQ_SEL_417_kHZ_45_PHASE_CLIP_OTWT       0x0D
#define AUDIOAMP3_FREQ_SEL_500_kHZ                          0x00
#define AUDIOAMP3_FREQ_SEL_357_kHZ                          0x02
#define AUDIOAMP3_CONFIG_CLIP_OTW_TWEETER_DETECT            0x00
#define AUDIOAMP3_CONFIG_CLIP_OTW_CLIP_DETECT               0x04
#define AUDIOAMP3_CONFIG_CLIP_OTW_OVERTEMP_WARNING          0x08
#define AUDIOAMP3_ENABLE_HARD_STOP_MODE                     0x10
#define AUDIOAMP3_SET_FS_357_kHZ_180_PHASE_CLIP_OTWT        0x20
#define AUDIOAMP3_SEND_SYNC_PULSE_OSC_SYNC                  0x40
#define AUDIOAMP3_CONFIG_CLIP_OTW_THERMAL_FOLDBACK          0x80
/** \} */

/**
 * \defgroup load_diag Load Diagnostics and Master/Slave Control
 * \{
 */
#define AUDIOAMP3_LOAD_DIAG_RUN_CH_1                        0x01
#define AUDIOAMP3_LOAD_DIAG_RUN_CH_2                        0x02
#define AUDIOAMP3_LOAD_DIAG_RUN_CH_3                        0x04
#define AUDIOAMP3_LOAD_DIAG_RUN_CH_4                        0x08
#define AUDIOAMP3_SET_CLOCK_OUTPUT_DISABLED                 0x50
#define AUDIOAMP3_DIS_DC_DETECTION_ALL_CH                   0x00
#define AUDIOAMP3_EN_TWEETER_DETECT_MODE                    0x20
#define AUDIOAMP3_EN_CLOCK_OUTPUT_OSC_SYNC                  0x80
/** \} */

/**
 * \defgroup out_ctrl Output Control
 * \{
 */
#define AUDIOAMP3_OUT_CTRL_ALL_CH_HI_Z_MUTE_RST_DIS_DC_EN   0x1F
#define AUDIOAMP3_OUT_CTRL_SET_CH_1_2_3_4_MUTE              0x00
#define AUDIOAMP3_OUT_CTRL_SET_PLAY_MODE                    0x20
#define AUDIOAMP3_OUT_CTRL_DC_DET_SHUTDOWN_DIS              0x40
#define AUDIOAMP3_OUT_CTRL_RST_DEVICE                       0x80                
#define AUDIOAMP3_OUT_CTRL_L_LOW_STATE_DIS_ALL_CH           0x00
#define AUDIOAMP3_OUT_CTRL_SET_CH_1_L_LOW_STATE             0xC1
#define AUDIOAMP3_OUT_CTRL_SET_CH_2_L_LOW_STATE             0xC2
#define AUDIOAMP3_OUT_CTRL_SET_CH_3_L_LOW_STATE             0xC4
#define AUDIOAMP3_OUT_CTRL_SET_CH_4_L_LOW_STATE             0xC8
#define AUDIOAMP3_OUT_CTRL_CONN_CH_1_2_BTL_MODE             0xD0
#define AUDIOAMP3_OUT_CTRL_CONN_CH_3_4_BTL_MODE             0xE0
/** \} */

/**
 * \defgroup miscell Miscellaneous Selection
 * \{
 */
#define AUDIOAMP3_MISCELL_NORMAL_SPEED_S2P_S2G_TIMING       0x01
#define AUDIOAMP3_MISCELL_MIN_DC_DET_VAL_0_8_V              0x00
#define AUDIOAMP3_MISCELL_MIN_DC_DET_VAL_2_4_V              0x02
#define AUDIOAMP3_MISCELL_EN_CROSSTALK_ENHANCEMENT          0x04
#define AUDIOAMP3_MISCELL_N_LOAD_DIAG_PHASES                0x08
#define AUDIOAMP3_MISCELL_S2P_S2G_LOAD_DIAG                 0x10
#define AUDIOAMP3_MISCELL_SLOW_COMMON_MODE_RAMP             0x20
#define AUDIOAMP3_MISCELL_SLOWER_CM_RAMP_DOWN_MUTE_MODE     0x80
/** \} */

/**
 * \defgroup mask_bit Bit Mask
 * \{
 */
#define AUDIOAMP3_MASK_BIT_SEL_NO_CH                        0x00
#define AUDIOAMP3_MASK_BIT_SEL_CH_1                         0x01
#define AUDIOAMP3_MASK_BIT_SEL_CH_2                         0x02
#define AUDIOAMP3_MASK_BIT_SEL_ALL_CH                       0x03
#define AUDIOAMP3_MASK_BIT_SEL_GAIN_12dB                    0x0C
#define AUDIOAMP3_MASK_BIT_SEL_GAIN_20dB                    0x14
#define AUDIOAMP3_MASK_BIT_SEL_GAIN_26dB                    0x1A
#define AUDIOAMP3_MASK_BIT_SEL_GAIN_32dB                    0x20
#define AUDIOAMP3_MASK_BIT_CH_1                             0xFC
#define AUDIOAMP3_MASK_BIT_MUTE_NO_CH                       0x10
#define AUDIOAMP3_MASK_BIT_MUTE_CH_1                        0xFE
#define AUDIOAMP3_MASK_BIT_MUTE_CH_2                        0xFD
/** \} */

/**
 * \defgroup gain_val Gain Value
 * \{
 */
#define AUDIOAMP3_GAIN_VAL_MAX                              0x04
#define AUDIOAMP3_GAIN_VAL_MEDIUM                           0x03
#define AUDIOAMP3_GAIN_VAL_MIN                              0x01
#define AUDIOAMP3_GAIN_VAL_0                                0x00
#define AUDIOAMP3_GAIN_VAL_5                                0x05
#define AUDIOAMP3_GAIN_VAL_LVL_1_12dB                       0x01
#define AUDIOAMP3_GAIN_VAL_LVL_2_20dB                       0x02
#define AUDIOAMP3_GAIN_VAL_LVL_3_26dB                       0x03
#define AUDIOAMP3_GAIN_VAL_LVL_4_32dB                       0x04
/** \} */

/**
 * \defgroup status ERROR Status
 * \{
 */
#define AUDIOAMP3_STATUS_ERR                                0x00
#define AUDIOAMP3_STATUS_OK                                 0x01
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

    digital_out_t stb;

    // Input pins 

    digital_in_t clp;
    digital_in_t flt;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} audioamp3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t stb;
    pin_name_t clp;
    pin_name_t flt;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} audioamp3_cfg_t;

/** \} */ // End types group

// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 
/** \} */ // End constants group

// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group

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
 * @param cfg           Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void audioamp3_cfg_setup ( audioamp3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param audioamp3     Click object.
 * @param cfg           Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AUDIOAMP3_RETVAL audioamp3_init ( audioamp3_t *ctx, audioamp3_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx           Click object.
 * @param reg           Register address.
 * @param data_buf      Data buf to be written.
 * @param len           Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void audioamp3_generic_write ( audioamp3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx           Click object.
 * @param reg           Register address.
 * @param data_buf      Output data buf.
 * @param len           Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void audioamp3_generic_read ( audioamp3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Power Up function.
 *
 * @param ctx           Click object.
 *
 * @description This function power up the audio amplifier by sets to '1' state of the STB pin
 * of the AudioAmp 3 click board.
 */
void audioamp3_power_up ( audioamp3_t *ctx );

/**
 * @brief Hardware reset function.
 *
 * @param ctx           Click object.
 *
 * @description This function hardware reset the TAS5414C-Q1 four channel digital audio amplifier
 * on AudioAmp 3 click by cleared to '0' state of the STB pin, wait the 100 ms, sets to '1' state 
 * of the STB pin and wait another the 100 ms.
 * @note Delay is 200 ms.
 */
void audioamp3_hw_reset ( audioamp3_t *ctx );

/**
 * @brief Read all diagnostics function.
 *
 * @param ctx           Click object.
 * @param p_read_data   Pointer to the memory location where the diagnostics data be stored.
 *
 * @description This function read all diagnostics from the targeted registers address starting 
 * from the AUDIOAMP3_DIAG_LATCHED_FAULT_REG_1 registers of TAS5414C-Q1 four channel 
 * digital audio amplifiers on AudioAmp 3 click board.
 */
void audioamp3_read_all_diagnostics ( audioamp3_t *ctx, uint8_t *p_all_diagnostics );

/**
 * @brief Set the channel to low-low state function.
 *
 * @param ctx           Click object.
 * @param s_channel     Channel which is gonna be set to low-low state.
 * ------------------------------------------
 * <pre>
 *     0x01 : Set channel 1 to low-low state;
 *     0x02 : Set channel 2 to low-low state;
 * </pre>
 * ------------------------------------------
 * 
 * @return Status check.
 *         Flag state:
 * ------------------------------------------
 * <pre>
 *     0 : ERROR;
 *     1 : OK;
 * </pre>
 * ------------------------------------------
 *
 * @description This function the channel to low-low state by writing the appropriate value to the
 * target AUDIOAMP3_EXT_CTRL_REG_6 ( 0x0D ) register of TAS5414C-Q1 four channel 
 * digital audio amplifiers on AudioAmp 3 click board.
 */
AUDIOAMP3_STATUS_T audioamp3_set_channel_low_to_low ( audioamp3_t *ctx, uint8_t s_channel );

/**
 * @brief Set the mute mode of channel function.
 *
 * @param ctx           Click object.
 * @param s_channel     Channel which is gonna be set to low-low state.
 * ------------------------------------------
 * <pre>
 *     0x00 : Set non-Hi-Z channels to play mode ( unmute );
 *     0x01 : Set channel 1 to mute mode, non-Hi-Z;
 *     0x02 : Set channel 2 to mute mode, non-Hi-Z;
 *     0x03 : All channels, Hi-Z, mute, reset disabled, dc detect is enabled;
 * </pre>
 * ------------------------------------------
 * 
 * @return Status check.
 *         Flag state:
 * ------------------------------------------
 * <pre>
 *     0 : ERROR;
 *     1 : OK;
 * </pre>
 * ------------------------------------------
 *
 * @description This function set the mute mode of target channel by writing the appropriate value to the
 * target AUDIOAMP3_EXT_CTRL_REG_5 ( 0x0C ) register of TAS5414C-Q1 four channel digital 
 * audio amplifiers on AudioAmp 3 click board.
 */
AUDIOAMP3_STATUS_T audioamp3_set_channel_mute_mode ( audioamp3_t *ctx, uint8_t s_channel );

/**
 * @brief Run channel diagnostics function.
 *
 * @param ctx           Click object.
 * @param rc_channel    Channel on which is gonna be performed diagnostics.
 * 
 * @return Status check.
 *         Flag state:
 * ------------------------------------------
 * <pre>
 *     0 : ERROR;
 *     1 : OK;
 * </pre>
 * ------------------------------------------
 *
 * @description This function run channel diagnostics by writing the appropriate value to the 
 * target AUDIOAMP3_EXT_CTRL_REG_4 ( 0x0B ) register of TAS5414C-Q1 four channel digital 
 * audio amplifiers on AudioAmp 3 click board.
 */
AUDIOAMP3_STATUS_T audioamp3_run_channel_diagnostics ( audioamp3_t *ctx, uint8_t rc_channel );

/**
 * @brief Set the play mode for all channels function.
 *
 * @param ctx           Click object.
 * 
 * @return Status check.
 *         Flag state:
 * ------------------------------------------
 * <pre>
 *     0 : ERROR;
 *     1 : OK;
 * </pre>
 * ------------------------------------------
 *
 * @description This function set the play mode for all channels by writing the appropriate value to the
 * target AUDIOAMP3_EXT_CTRL_REG_5 ( 0x0C ) register of TAS5414C-Q1 four channel digital 
 * audio amplifiers on AudioAmp 3 click board.
 */
AUDIOAMP3_STATUS_T audioamp3_set_play_mode ( audioamp3_t *ctx );

/**
 * @brief Set the gain lvl function.
 *
 * @param ctx           Click object.
 * @param gain_lvl      Choose channel and set channel gain.
 * ------------------------------------------
 * <pre>
 *     0x01 : Set channel 2 gain to 12 dB;
 *     0x02 : Set channel 2 gain to 20 dB;
 *     0x03 : Set all channels gain to 26 dB;
 *     0x04 : Set channel 2 gain to 32 dB;
 * </pre>
 * ------------------------------------------
 * 
 * @return Status check.
 *         Flag state:
 * ------------------------------------------
 * <pre>
 *     0 : ERROR;
 *     1 : OK;
 * </pre>
 * ------------------------------------------
 *
 * @description This function set the gain level for all channels by writing 
 * the appropriate value to the target AUDIOAMP3_EXT_CTRL_REG_1 ( 0x08 ) 
 * register of TAS5414C-Q1 four channel digital audio amplifiers on 
 * AudioAmp 3 click board.
 */
AUDIOAMP3_STATUS_T audioamp3_set_gain_lvl ( audioamp3_t *ctx, uint8_t gain_lvl );

#ifdef __cplusplus
}
#endif
#endif  // _AUDIOAMP3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
