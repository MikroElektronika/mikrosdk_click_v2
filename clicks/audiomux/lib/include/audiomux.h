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
 * \brief This file contains API for AudioMUX Click driver.
 *
 * \addtogroup audiomux AudioMUX Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AUDIOMUX_H
#define AUDIOMUX_H

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
#define AUDIOMUX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */



/**
 * \defgroup error_code Error Code
 * \{
 */
#define  AUDIOMUX_RETVAL  uint8_t

#define  AUDIOMUX_OK                                             0x00
#define  AUDIOMUX_INIT_ERROR                                     0xFF
/** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define  AUDIOMUX_DEVICE_ADDR                                    0x44
/** \} */

/**
 * \defgroup address_auto_inc Address Auto Increment
 * \{
 */
#define  AUDIOMUX_AUTO_INCR                                      0x10
/** \} */

/**
 * \defgroup memory_addr Memory Addresses
 * \{
 */
#define  AUDIOMUX_INPUT_SEL_ADDR                                 0x00
#define  AUDIOMUX_INPUT_GAIN_ADDR                                0x01
#define  AUDIOMUX_SURROUND_ADDR                                  0x02
#define  AUDIOMUX_VOLUME_LEFT_ADDR                               0x03
#define  AUDIOMUX_VOLUME_RIGHT_ADDR                              0x04
#define  AUDIOMUX_TREBLE_BASS_ADDR                               0x05
#define  AUDIOMUX_OUTPUT_ADDR                                    0x06
#define  AUDIOMUX_BASS_ALC_ADDR                                  0x07
/** \} */

/**
 * \defgroup in_and_mic_sel Settings for Input Selection and MIC
 * \{
 */
#define  AUDIOMUX_IN1_EN                                         0x00
#define  AUDIOMUX_IN2_EN                                         0x01
#define  AUDIOMUX_IN3_EN                                         0x02
#define  AUDIOMUX_IN4_EN                                         0x03
#define  AUDIOMUX_MIC_GAIN_14DB                                  0x00
#define  AUDIOMUX_MIC_GAIN_10DB                                  0x01
#define  AUDIOMUX_MIC_GAIN_6DB                                   0x02
#define  AUDIOMUX_MIC_GAIN_0DB                                   0x03
#define  AUDIOMUX_MIC_OFF                                        0x01
#define  AUDIOMUX_MIC_ON                                         0x00
/** \} */

/**
 * \defgroup mute_input Settings for Mute Input
 * \{
 */
#define  AUDIOMUX_MUTE_INPUT_ON                                  0x01
#define  AUDIOMUX_MUTE_INPUT_OFF                                 0x00
/** \} */

/**
 * \defgroup input_gain_sel Settings for Input Gain Selection
 * \{
 */
#define  AUDIOMUX_IN_GAIN_0DB                                    0x00
#define  AUDIOMUX_IN_GAIN_2DB                                    0x01
#define  AUDIOMUX_IN_GAIN_4DB                                    0x02
#define  AUDIOMUX_IN_GAIN_6DB                                    0x03
#define  AUDIOMUX_IN_GAIN_8DB                                    0x04
#define  AUDIOMUX_IN_GAIN_10DB                                   0x05
#define  AUDIOMUX_IN_GAIN_12DB                                   0x06
#define  AUDIOMUX_IN_GAIN_14DB                                   0x07
/** \} */

/**
 * \defgroup surr_and_mix Surrounding and Mixing Settings
 * \{
 */
#define  AUDIOMUX_SURROUND_MODE_ON                               0x01
#define  AUDIOMUX_SURROUND_MODE_OFF                              0x00
#define  AUDIOMUX_SURROUND_GAIN_0DB                              0x00
#define  AUDIOMUX_SURROUND_GAIN_6DB                              0x02
#define  AUDIOMUX_SURROUND_GAIN_9DB                              0x04
#define  AUDIOMUX_SURROUND_GAIN_12DB                             0x06
#define  AUDIOMUX_MIX_INV_100                                    0x00
#define  AUDIOMUX_MIX_INV_50                                     0x08
#define  AUDIOMUX_MIX_INV_25                                     0x10
#define  AUDIOMUX_MIX_0                                          0x18
#define  AUDIOMUX_MIX_NONINV_100                                 0x20
#define  AUDIOMUX_MIX_NONINV_75                                  0x28
#define  AUDIOMUX_MIX_NONINV_50                                  0x30
#define  AUDIOMUX_MIX_MUTE                                       0x38
#define  AUDIOMUX_BUFF_GAIN_0                                    0x40
#define  AUDIOMUX_BUFF_GAIN_6DB                                  0x00
/** \} */

/**
 * \defgroup volume_config Settings for Volume
 * \{
 */
#define  AUDIOMUX_VOL1_0DB                                       0x00
#define  AUDIOMUX_VOL1_1DB_NEG                                   0x01
#define  AUDIOMUX_VOL1_2DB_NEG                                   0x02
#define  AUDIOMUX_VOL1_3DB_NEG                                   0x03
#define  AUDIOMUX_VOL1_4DB_NEG                                   0x04
#define  AUDIOMUX_VOL1_5DB_NEG                                   0x05
#define  AUDIOMUX_VOL1_6DB_NEG                                   0x06
#define  AUDIOMUX_VOL1_7DB_NEG                                   0x07
#define  AUDIOMUX_VOL1_8DB_NEG                                   0x08
#define  AUDIOMUX_VOL1_16DB_NEG                                  0x10
#define  AUDIOMUX_VOL1_24DB_NEG                                  0x18
#define  AUDIOMUX_VOL1_32DB_NEG                                  0x20
#define  AUDIOMUX_VOL1_40DB_NEG                                  0x28
#define  AUDIOMUX_VOL1_48DB_NEG                                  0x30
#define  AUDIOMUX_VOL1_56DB_NEG                                  0x38
#define  AUDIOMUX_VOL2_0DB                                       0x00
#define  AUDIOMUX_VOL2_8DB_NEG                                   0x01
#define  AUDIOMUX_VOL2_16DB_NEG                                  0x02
#define  AUDIOMUX_VOL2_24DB_NEG                                  0x03
/** \} */

/**
 * \defgroup treble_and_bass Settings for Treble and Bass
 * \{
 */
#define  AUDIOMUX_TRE_BASS_14DB_NEG                              0x00
#define  AUDIOMUX_TRE_BASS_12DB_NEG                              0x01
#define  AUDIOMUX_TRE_BASS_10DB_NEG                              0x02
#define  AUDIOMUX_TRE_BASS_8DB_NEG                               0x03
#define  AUDIOMUX_TRE_BASS_6DB_NEG                               0x04
#define  AUDIOMUX_TRE_BASS_4DB_NEG                               0x05
#define  AUDIOMUX_TRE_BASS_2DB_NEG                               0x06
#define  AUDIOMUX_TRE_BASS_0DB                                   0x07
#define  AUDIOMUX_TRE_BASS_14DB                                  0x08
#define  AUDIOMUX_TRE_BASS_12DB                                  0x09
#define  AUDIOMUX_TRE_BASS_10DB                                  0x0A
#define  AUDIOMUX_TRE_BASS_8DB                                   0x0B
#define  AUDIOMUX_TRE_BASS_6DB                                   0x0C
#define  AUDIOMUX_TRE_BASS_4DB                                   0x0D
#define  AUDIOMUX_TRE_BASS_2DB                                   0x0E
/** \} */

/**
 * \defgroup mute_output Settings for Mute Output
 * \{
 */
#define  AUDIOMUX_MUTE_OUTPUT_ON                                 0x00
#define  AUDIOMUX_MUTE_OUTPUT_OFF                                0x01
/** \} */

/**
 * \defgroup bass_alc_mode Settings for Bass ALC Mode
 * \{
 */
#define  AUDIOMUX_ALC_MODE_ON                                    0x01
#define  AUDIOMUX_DETECTOR_ON                                    0x02
#define  AUDIOMUX_RELEASE_CURR                                   0x04
#define  AUDIOMUX_TIME_RES_12K5                                  0x00
#define  AUDIOMUX_TIME_RES_25K                                   0x08
#define  AUDIOMUX_TIME_RES_50K                                   0x10
#define  AUDIOMUX_TIME_RES_100K                                  0x18
#define  AUDIOMUX_THRSH_700MVRMS                                 0x00
#define  AUDIOMUX_THRSH_485MVRMS                                 0x20
#define  AUDIOMUX_THRSH_320MVRMS                                 0x40
#define  AUDIOMUX_THRSH_170MVRMS                                 0x60
#define  AUDIOMUX_MODE1_FIXED_RES                                0x00
#define  AUDIOMUX_MODE2_ADAPTIVE                                 0x80
/** \} */

/**
 * \defgroup audiomux_ret_val Returned values for AudioMUX
 * \{
 */
#define  AUDIOMUX_OK                                             0x00
#define  AUDIOMUX_ADDR_ERR                                       0x01
#define  AUDIOMUX_NBYTES_ERR                                     0x02
#define  AUDIOMUX_IN_SEL_ERR                                     0x03
#define  AUDIOMUX_GAIN_ERR                                       0x04
#define  AUDIOMUX_STATE_ERR                                      0x05
#define  AUDIOMUX_VOL_ERR                                        0x06
#define  AUDIOMUX_TRE_BASS_ERR                                   0x07
/** \} */

/**
 * \defgroup other_macros Other Macros
 * \{
 */
#define  T_AUDIOMUX_P                             const uint8_t*
#define  T_AUDIOMUX_RETVAL                        uint8_t
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
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} audiomux_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} audiomux_cfg_t;

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
void audiomux_cfg_setup ( audiomux_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param                 audiomux Click object.
 * @param                 cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AUDIOMUX_RETVAL audiomux_init ( audiomux_t *ctx, audiomux_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx            Click object.
 *
 * @description This function executes default configuration for AudioMUX click.
 * @note
 * <pre>
 * User may change click configuration as he wishes by using provided functions.
 * </pre>
 */
void audiomux_default_cfg ( audiomux_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx             Click object.
 * @param reg             Register address.
 * @param data_buf        Data buf to be written.
 * @param len             Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void audiomux_generic_write ( audiomux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx             Click object.
 * @param reg             Register address.
 * @param data_buf        Output data buf
 * @param len             Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void audiomux_generic_read ( audiomux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Single Write function
 *
 * @param ctx             Click object
 * @param reg_addr        Address where data be written
 * @param data_in         Data to be written
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * @description This function writes one byte data to the register.
 */
T_AUDIOMUX_RETVAL audiomux_write_single_byte ( audiomux_t *ctx, uint8_t reg_addr,
                                               uint8_t data_in );

/**
 * @brief Multiple Write function
 *
 * @param ctx             Click object
 * @param start_addr      Address which from data writing be started
 * @param data_in         Data to be written to register
 * @param n_bytes         Number of bytes to be written
 *
 * @returns 0 - OK, 1 - Wrong address, 2 - Number of bytes is out of range
 *
 * #description This function writes the desired number of bytes to the registers.
 */
T_AUDIOMUX_RETVAL audiomux_write_bytes ( audiomux_t *ctx, uint8_t start_addr,
                                         uint8_t *data_in, uint8_t n_bytes );

/**
 * @brief Single Read function
 *
 * @param ctx             Click object
 * @param reg_addr        Address which from data be read
 * @param data_out        Memory where data be stored
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * @description This function reads one byte data from the register.
 */
T_AUDIOMUX_RETVAL audiomux_read_single_byte ( audiomux_t *ctx, uint8_t reg_addr,
                                              uint8_t *data_out );

/**
 * @brief Multiple Read function
 *
 * @param ctx             Click object
 * @param start_addr      Address which from data read be started
 * @param data_out        Memory where data be stored
 * @param n_bytes         Number of bytes to be read
 *
 * @returns 0 - OK, 1 - Wrong address, 2 - Number of bytes is out of range
 *
 * @description This function reads the desired number of bytes from the registers.
 */
T_AUDIOMUX_RETVAL audiomux_read_bytes ( audiomux_t *ctx, uint8_t start_addr,
                                        uint8_t *data_out, uint8_t n_bytes );

/**
 * @brief Input Selection function
 *
 * @param ctx             Click object
 * @param input_sel       Input channel selection, from 0 (IN1) to 3 (IN4)
 * @param mute_in         1 - Input Mute ON, 0 - Input Mute OFF
 * @param mic_gain        From 0 (14dB) to 3 (0dB)
 * @param mic_state       0 - MIC ON, 1 - MIC OFF
 *
 * @returns 0 - OK, 3 - Input Selection Error, 4 - Gain Error, 5 - State Error
 *
 * @description This function performs a input selection and control.
 */
T_AUDIOMUX_RETVAL audiomux_select_input ( audiomux_t *ctx, uint8_t input_sel, uint8_t mute_in,
                                          uint8_t mic_gain, uint8_t mic_state );

/**
 * @brief Input Gain Control function
 *
 * @param ctx             Click object
 * @param input_gain      From 0 (0dB) to 7 (14dB)
 *
 * @returns 0 - OK, 4 - Gain Error
 *
 * @description This function performs a input gain selection.
 */
T_AUDIOMUX_RETVAL audiomux_set_input_gain ( audiomux_t *ctx, uint8_t input_gain );

/**
 * @brief Volume Control function
 *
 * @param ctx             Click object
 * @param volume1         Pre-EQ section volume, 0x00 is highest volume and 0x3F is lowest volume
 * @param volume2         Post-EQ section volume, 0x00 is highest and 0x03 is lowest volume
 * @param side_sel        0x03 - Left volume control, 0x04 - Right volume control
 *
 * @returns 0 - OK, 1 - Wrong side address, 6 - Wrong volume selection
 *
 * @description This function performs a left or right volume control.
 */
T_AUDIOMUX_RETVAL audiomux_set_volume ( audiomux_t *ctx, uint8_t volume1, uint8_t volume2,
                                        uint8_t side_sel );

/**
 * @brief Treble and Bass Control function
 *
 * @param ctx             Click object
 * @param treble          Treble selection from -14dB to 14dB
 * @param bass            Bass selection from -14dB to 14dB
 *
 * @returns 0 - OK, 7 - Treble or Bass Selection Error
 *
 * @description This function performs a control of the treble and bass for EQ section.
 */
T_AUDIOMUX_RETVAL audiomux_set_treble_bass ( audiomux_t *ctx, uint8_t treble, uint8_t bass );

/**
 * @brief Output Mute function
 *
 * @param ctx             Click object
 * @param state           0 - Output Mute ON, 1 - Output Mute OFF
 *
 * @returns 0 - OK, 5 - Parameter State Error
 *
 * @description This function performs a control of the output to be Mute ON or Mute OFF.
 */
T_AUDIOMUX_RETVAL audiomux_mute_ouput ( audiomux_t *ctx, uint8_t state );


#ifdef __cplusplus
}
#endif
#endif  // _AUDIOMUX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
