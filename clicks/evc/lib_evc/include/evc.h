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
 * \brief This file contains API for EVC Click driver.
 *
 * \addtogroup evc EVC Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EVC_H
#define EVC_H

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
#define EVC_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EVC_RETVAL  uint8_t

#define EVC_OK           0x00
#define EVC_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup volume Volume
 * \{
 */
#define EVC_SET_VOLUME_1dB     0x11
#define EVC_SET_VOLUME_10dB    0x01
#define EVC_SET_VOLUME_20dB    0x02
#define EVC_SET_VOLUME_2dB     0x12
#define EVC_SET_VOLUME_30dB    0x03
#define EVC_SET_VOLUME_3dB     0x13
#define EVC_SET_VOLUME_40dB    0x04
#define EVC_SET_VOLUME_4dB     0x14
#define EVC_SET_VOLUME_50dB    0x05
#define EVC_SET_VOLUME_5dB     0x15
#define EVC_SET_VOLUME_60dB    0x06
#define EVC_SET_VOLUME_6dB     0x16
#define EVC_SET_VOLUME_70dB    0x07
#define EVC_SET_VOLUME_7dB     0x17
#define EVC_SET_VOLUME_0dB     0x00
#define EVC_SET_VOLUME_8dB     0x18
#define EVC_SET_VOLUME_9dB     0x19
/** \} */

/**
 * \defgroup channel Channel
 * \{
 */
#define EVC_CHANNEL_1      0x80
#define EVC_CHANNEL_2      0x40
#define EVC_CHANNEL_3      0x00
#define EVC_CHANNEL_4      0x20
#define EVC_CHANNEL_5      0x60
#define EVC_CHANNEL_6      0xA0
#define EVC_ALL_CHANNEL    0xC0
/** \} */

/**
 * \defgroup mute_unmute Mute/Unmute
 * \{
 */
#define EVC_ALL_CHANNEL_MUTE      0xF9
#define EVC_ALL_CHANNEL_UNMUTE    0xF8
/** \} */

/**
 * \defgroup clear Clear
 * \{
 */
#define EVC_CLEAR_ALL    0xC0
/** \} */

/**
 * \defgroup dev_sl_addr Device Slave Address 
 * \{
 */
#define EVC_DEVICE_SLAVE_ADDRESS_01    0x42
#define EVC_DEVICE_SLAVE_ADDRESS_00    0x40
#define EVC_DEVICE_SLAVE_ADDRESS_10    0x44
#define EVC_DEVICE_SLAVE_ADDRESS_11    0x46
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
    uint8_t mute_flag;
    uint8_t play_flag;
    int8_t volume;
    uint8_t channel;
    uint8_t test_flag;

} evc_t;

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
    uint8_t mute_cfg_flag;
    uint8_t play_cfg_flag;
    int8_t cfg_volume;
    uint8_t cfg_channel;
    uint8_t test_cfg_flag;

} evc_cfg_t;

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
void evc_cfg_setup ( evc_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EVC_RETVAL evc_init ( evc_t *ctx, evc_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for EVC click.
 * @note Calling this function clears all registers, sets each channel to 0dB and unmutes the sound.
 * Contains additional initialization settings.
 */
void evc_default_cfg ( evc_t *ctx );

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
void evc_generic_write ( evc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void evc_generic_read ( evc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set volume for the channel
 *
 * @param ctx          Click object.
 * @param channel      Chunnel register (from _EQUALIZER_CHANNEL_1 to _EQUALIZER_CHANNEL_6)
 * @param volume1      Volume (from _EQUALIZER_SET_VOLUME_1dB to _EQUALIZER_SET_VOLUME_9dB)
 * @param volume2      Volume (from _EQUALIZER_SET_VOLUME_10dB to _EQUALIZER_SET_VOLUME_70dB)
 *
 * @description This function sets the volume for the selected channel, uses two variables.
 */
void evc_set_volume_part ( evc_t *ctx, uint8_t channel, uint8_t volume1, uint8_t volume2 );

/**
 * @brief Set volume for the channel
 * 
 * @param ctx          Click object.
 * @param channel      Chunnel register (from _EQUALIZER_CHANNEL_1 to _EQUALIZER_CHANNEL_6)
 * @param volume       Volume (from 0 to -79) (int8_t value)
 *
 * @description This function sets the volume for the selected channel, uses one volume variables.
 */
void evc_set_volume_full ( evc_t *ctx, uint8_t channel, int8_t volume );

/**
 * @brief Clear register
 * 
 * @param ctx          Click object.
 * 
 * @description This function clears the registers.
 * @note The PT2258 function register does not have any default settings.
 * After clearing the register, an initial value must send in order to each register.
 * If a register does has not been set, it is possible that no sound will be output.
 * The cleaning and settings for each registers are included in the function "defaultConfiguration()".
 */
void evc_clear ( evc_t *ctx );

/**
 * @brief Mute and Unmute
 * 
 * @param ctx          Click object.
 * @param Mute         Mute register
 *
 * @description This function mute and unmute the sound
 */
void evc_mute ( evc_t *ctx, uint8_t mute );

#ifdef __cplusplus
}
#endif
#endif  // _EVC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
