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
 * \brief This file contains API for FM Click driver.
 *
 * \addtogroup fm FM Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FM_H
#define FM_H

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
#define FM_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.gp2  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.sen  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.gp1  = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FM_RETVAL  uint8_t

#define FM_OK                                     0x00
#define FM_INIT_ERROR                             0xFF
/** \} */

/**
 * \defgroup slave_addr Slave addres
 * \{
 */
#define DEFAULT_SLAVE_ADDRESS                     0x10
/** \} */

/**
 * \defgroup reg_addr Register addresses 
 * \{
 */
#define FM_DEVICE_ID                              0x000E
#define FM_CHIP_ID                                0x000F
#define FM_POWER_CONFIGURATION                    0x0000
#define FM_CHANNEL                                0x0001
#define FM_SYSTEM_CONFIGURATION_1                 0x0002
#define FM_SYSTEM_CONFIGURATION_2                 0x0003
#define FM_SYSTEM_CONFIGURATION_3                 0x0004
#define FM_TEST_1                                 0x0005
#define FM_TEST_2                                 0x0006
#define FM_BOOT_CONFIGURATION                     0x0007
#define FM_STATUS_RSSI                            0x0008
#define FM_READ_CHANNEL                           0x0009
#define FM_RDS_A                                  0x000A
#define FM_RDS_B                                  0x000B
#define FM_RDS_C                                  0x000C
#define FM_RDS_D                                  0x000D
/** \} */

/**
 * \defgroup power_cfg_reg Power configuration register 
 * \{
 */
#define FM_SOFTMUTE_MASK                          0x7FFF
#define FM_SOFTMUTE_ENABLE                        0x0000
#define FM_SOFTMUTE_DISABLE                       0x8000

#define FM_MUTE_MASK                              0xBFFF
#define FM_MUTE_ENABLE                            0x0000
#define FM_MUTE_DISABLE                           0x4000

#define FM_STEREO_MASK                            0xDFFF
#define FM_STEREO                                 0x0000
#define FM_FORCE_MONO                             0x2000

#define FM_RDS_MODE_MASK                          0xF7FF
#define FM_RDS_MODE_STANDARD                      0x0000
#define FM_RDS_MODE_VERBOSE                       0x0800

#define FM_SEEK_MODE_MASK                         0xFBFF
#define FM_SEEK_MODE_WRAP                         0x0000
#define FM_SEEK_MODE_STOP                         0x0400

#define FM_SEEK_DIRECTION_MASK                    0xFDFF
#define FM_SEEK_DIRECTION_DOWN                    0x0000
#define FM_SEEK_DIRECTION_UP                      0x0200

#define FM_SEEK_MASK                              0xFEFF
#define FM_SEEK_DISABLE                           0x0000
#define FM_SEEK_ENABLE                            0x0100

#define FM_POWERUP_DISABLE_MASK                   0xFFBF
#define FM_POWERUP_DISABLE_LOW                    0x0000
#define FM_POWERUP_DISABLE_HIGH                   0x0040

#define FM_POWERUP_ENABLE_MASK                    0xFFFE
#define FM_POWERUP_ENABLE_LOW                     0x0000
#define FM_POWERUP_ENABLE_HIGH                    0x0001
/** \} */ 

/**
 * \defgroup channel Channel 
 * \{
 */
#define FM_TUNE_MASK                              0x7FFF
#define FM_TUNE_DISABLE                           0x0000
#define FM_TUNE_ENABLE                            0x8000
/** \} */

/**
 * \defgroup sys_cfg System configuration
 * \{
 */
#define FM_RDS_INTERRUPT_MASK                     0x7FFF
#define FM_RDS_INTERRUPT_DISABLE                  0x0000
#define FM_RDS_INTERRUPT_ENABLE                   0x8000

#define FM_SEEK_TUNE_COMPLETE_INTERRUPT_MASK      0xBFFF
#define FM_SEEK_TUNE_COMPLETE_INTERRUPT_DISABLE   0x0000
#define FM_SEEK_TUNE_COMPLETE_INTERRUPT_ENABLE    0x4000

#define FM_RDS_MASK                               0xEFFF
#define FM_RDS_DISABLE                            0x0000
#define FM_RDS_ENABLE                             0x1000

#define FM_DE_EMPHASIS_MASK                       0xF7FF
#define FM_DE_EMPHASIS_USA                        0x0000
#define FM_DE_EMPHASIS_EUROPE_AUSTRALIA_JAPAN     0x0800

#define FM_AGC_MASK                               0xFBFF
#define FM_AGC_ENABLE                             0x0000
#define FM_AGC_DISABLE                            0x0400

#define FM_STEREO_MONO_BLEND_LEVEL_MASK           0xFF3F
#define FM_STEREO_MONO_BLEND_LEVEL_31_49_RSSI     0x0000
#define FM_STEREO_MONO_BLEND_LEVEL_37_55_RSSI     0x0040
#define FM_STEREO_MONO_BLEND_LEVEL_19_37_RSSI     0x0080
#define FM_STEREO_MONO_BLEND_LEVEL_25_43_RSSI     0x00C0

#define FM_GPIO3_MASK                             0xFFCF
#define FM_GPIO3_HIGH_IMPENDANCE                  0x0000
#define FM_GPIO3_MONO_STEREO_INDICATOR            0x0001
#define FM_GPIO3_LOW                              0x0002
#define FM_GPIO3_HIGH                             0x0003

#define FM_GPIO2_MASK                             0xFFF3
#define FM_GPIO2_HIGH_IMPEDANCE                   0x0000
#define FM_GPIO2_STC_RDS_INTERRUPT                0x0004
#define FM_GPIO2_LOW                              0x0008
#define FM_GPIO2_HIGH                             0x000C

#define FM_GPIO1_MASK                             0xFFFC
#define FM_GPIO1_HIGH_IMPEDANCE                   0x0000
#define FM_GPIO1_RESERVED                         0x0001
#define FM_GPIO1_LOW                              0x0002
#define FM_GPIO1_HIGH                             0x0003
/** \} */

/**
 * \defgroup sys_cfg_2 System configuration 2
 * \{
 */
#define FM_BAND_MASK                              0xFF3F
#define FM_BAND_USA_EUROPE_87P5_108_MHZ           0x0000
#define FM_BAND_JAPAN_WIDE_76_108_MHZ             0x0040
#define FM_BAND_JAPAN_76_90_MHZ                   0x0080
#define FM_BAND_RESERVED                          0x00C0

#define FM_CHANNEL_SPACING_MASK                   0xFFCF
#define FM_CHANNEL_SPACING_USA_AUSTRALIA_200_KHZ  0x0000
#define FM_CHANNEL_SPACING_EUROPE_JAPAN_100_KHZ   0x0010
#define FM_CHANNEL_SPACING_50_KHZ                 0x0020
/** \} */

/**
 * \defgroup sys_cfg_3 System configuration 3
 * \{
 */
#define FM_SOFTMUTE_ATTACK_RECOVER_RATE_MASK      0x3FFF
#define FM_SOFTMUTE_ATTACK_RECOVER_RATE_FASTEST   0x0000
#define FM_SOFTMUTE_ATTACK_RECOVER_RATE_FAST      0x4000
#define FM_SOFTMUTE_ATTACK_RECOVER_RATE_SLOW      0x8000
#define FM_SOFTMUTE_ATTACK_RECOVER_RATE_SLOWEST   0xC000

#define FM_SOFTMUTE_ATTENUATION_MASK              0xCFFF
#define FM_SOFTMUTE_ATTENUATION_16_DB             0x0000
#define FM_SOFTMUTE_ATTENUATION_14_DB             0x1000
#define FM_SOFTMUTE_ATTENUATION_12_DB             0x2000
#define FM_SOFTMUTE_ATTENUATION_10_DB             0x3000

#define FM_EXTENDED_VOLUME_RANGE_MASK             0xFEFF
#define FM_EXTENDED_VOLUME_RANGE_DISABLED         0x0000
#define FM_EXTENDED_VOLUME_RANGE_ENABLED          0x0100
/** \} */

/**
 * \defgroup test_1 Test 1 
 * \{
 */
#define FM_CRYSTAL_OSCYLATOR_MASK                 0x7FFF
#define FM_CRYSTAL_OSCYLATOR_DISABLE              0x0000
#define FM_CRYSTAL_OSCYLATOR_ENABLE               0x8000

#define FM_AUDIO_HIGH_Z_MASK                      0xBFFF
#define FM_AUDIO_HIGH_Z_DISABLE                   0x0000
#define FM_AUDIO_HIGH_Z_ENABLE                    0x4000
/** \} */

/**
 * \defgroup status_rssi Status RSSI
 * \{
 */
#define FM_RDS_READY_MASK                         0x8000
#define FM_SEEK_TUNE_COMPLETE_MASK                0x4000
#define FM_SEEK_FAIL_BAND_LIMIT_MASK              0x2000
#define FM_AFC_RAIL_MASK                          0x1000
#define FM_RDS_SYNCHRONIZED_MASK                  0x0800
#define FM_STEREO_MONO_INDICATOR_MASK             0x0100
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

    digital_out_t rst;
    digital_out_t sen;

    // Input pins 

    digital_in_t gp2;
    digital_in_t gp1;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} fm_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t gp2;
    pin_name_t rst;
    pin_name_t sen;
    pin_name_t gp1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} fm_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void fm_cfg_setup ( fm_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
FM_RETVAL fm_init ( fm_t *ctx, fm_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Fm Click.
 */
void fm_default_cfg ( fm_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx               Click object.
 * @param reg_buf           All registers to be written are stored into reg_buf[ 16 ].
 *
 * @description This function writes all registers from device starting from address 0x02
 * This function should be used after fm_generic_read(); and fm_set_bits(); functions
 */
void fm_generic_write ( fm_t *ctx, uint16_t *reg_buf );

/**
 * @brief Reading all registers
 *
 * @param ctx          Click object.
 * @param reg_buf      All registers to be read are stored into reg_buf[ 16 ].
 *
 * @description This function reads all registers in device starting from address 0x0A
 * This function sorts all device registers in such manner that reg_buf[] 
 * can be used with fm_generic_write(); without change

 */
void fm_generic_read ( fm_t *ctx, uint16_t *reg_buf );

/**
 * @brief Setting bits in specific register on a specific bit location
 *
 * @param ctx                 Click object.
 * @param register_buffer     All device registers are read into register_buffer[ 16 ].
 * @param register_address    Address of the register whose bits are to be set.
 * @param bits_mask           Bits to be set must be masked first.
 * @param bits_value          Value of the bits in selected range.
 *
 * @description This function is used to set bits in specific register on a specific position
 * This function is used after fm_generic_read( uint16_t *register_buffer )
 * This function is used before fm_generic_write( uint16_t *register_buffer )
 */
void fm_set_bits ( uint16_t *register_buffer, uint16_t register_address, uint16_t bits_mask, uint16_t bits_value );

/**
 * @brief Setting seek threshold value
 *
 * @param ctx                 Click object.
 * @param seek_threshold      Value of seek threshold.
 * @returns                   0 or 1
 *
 * @description This function sets seek threshold value
 * This function returns 0 if threshold value is in valid range
 * This function returns 1 if threshold value is not in valid range
 */
uint8_t fm_set_seek_threshold ( fm_t *ctx, uint16_t seek_threshold );

/**
 * @brief Setting volume value
 *
 * @param ctx                 Click object.
 * @param volume_level        Desired volume value
 * @returns                   0 or 1
 *
 * @description This function sets volume value (0-16)
 * This function sets VOLUME bits [3:0] in System configuration 2 register
 * This function returns 0 if volume value is in range
 * This function returns 1 if volume value is not in range
 */
uint8_t fm_set_volume ( fm_t *ctx, uint8_t volume_level );

/**
 * @brief Setting seek SNR threshold value
 *
 * @param ctx                 Click object.
 * @returns                   0 or 1
 *
 * @description This function sets seek SNR threshold value
 * This function sets SKSNR bits in System configuration 3 register
 * This function returns 0 if threshold value is in valid range
 * This function returns 1 if threshold value is not in valid range
 */
uint8_t fm_set_snr_threshold ( fm_t *ctx, uint8_t snr_threshold );

/**
 * @brief Setting seek impulse detection threshold value
 *
 * @param ctx                 Click object.
 * @returns                   0 or 1
 * 
 * @description This function sets impulse detection threshold value
 * This function sets SKCNT bits in System configuration 3 register
 * This function returns 0 if threshold value is in valid range
 * This function returns 1 if threshold value is not in valid range
 */
uint8_t fm_set_seek_impulse_detection_threshold ( fm_t *ctx, uint8_t impulse_detection_threshold );

/**
 * @brief Reading number of errors to be corrected
 *
 * @param ctx                 Click object.
 * @returns n_errors - value that represents number of errors to be corrected
 *
 * @description This function returns BLERA error bits from status RSSI register
 * This function returns 00h if 0 errors occured
 * This function returns 01h if 1–2 errors occured
 * This function returns 10h if 3–5 errors occured
 * This function returns 11h if 6+ errors occured and correction is not possible.
 */
uint8_t fm_get_errors_block_a ( fm_t *ctx );

/**
 * @brief Reading recived strength indicator
 *
 * @param ctx                 Click object.
 * @returns rssi_value - value of recived signal strength in dBuV
 *
 * @description This function reads recived signal strength indicatior
 */
uint8_t fm_get_received_signal_strength_indicator ( fm_t *ctx );

/**
 * @brief Reading number of errors to be corrected
 *
 * @param ctx                 Click object.
 * @returns n_errors - value that represents number of errors to be corrected
 *
 * @description This function returns BLERB error bits from read Channel register
 * This function returns 00h if 0 errors occured
 * This function returns 01h if 1–2 errors occured
 * This function returns 10h if 3–5 errors occured
 * This function returns 11h if 6+ errors occured and correction is not possible.
 */
uint8_t fm_get_errors_block_b (  fm_t *ctx );

/**
 * @brief Reading number of errors to be corrected
 *
 * @param ctx                 Click object.
 * @returns n_errors - value that represents number of errors to be corrected
 *
 * @description This function returns BLERC error bits from read Channel register
 * This function returns 00h if 0 errors occured
 * This function returns 01h if 1–2 errors occured
 * This function returns 10h if 3–5 errors occured
 * This function returns 11h if 6+ errors occured and correction is not possible.
 */
uint8_t fm_get_errors_block_c ( fm_t *ctx );

/**
 * @brief Reading number of errors to be corrected
 *
 * @param ctx                 Click object.
 * @returns n_errors - value that represents number of errors to be corrected
 *
 * @description This function returns BLERD error bits from read Channel register
 * This function returns 00h if 0 errors occured
 * This function returns 01h if 1–2 errors occured
 * This function returns 10h if 3–5 errors occured
 * This function returns 11h if 6+ errors occured and correction is not possible.
 */
uint8_t fm_get_errors_block_d ( fm_t *ctx );

/**
 * @brief Calculating current channel frequency
 *
 * @param ctx                 Click object.
 * @returns channel_frequency - current channel frequency in MHz
 *
 * @description This function calculates current channel frequency based on band and space settings
 */
float fm_get_channel_frequency ( fm_t *ctx );

/**
 * @brief Powering up device
 *
 * @param ctx                 Click object.
 * 
 * @description This function powers up device
 * This function first selects 2 wire mode for I2C
 * This function than enables crystal oscylator and waits for it to settle
 * This function than sets ENABLE bit HIGH and DISABLE bit LOW and waits for device to powerup
 */
void fm_power_up ( fm_t *ctx );

/**
 * @brief Setting basic settings
 *
 * @param ctx                 Click object.
 * 
 * @description This function sets basic settings to device
 * This function sets optimal settings for device operation in Europe
 */
void fm_basic_settings ( fm_t *ctx );

/**
 * @brief Powering down device
 *
 * @param ctx                 Click object.
 * 
 * @description This function powers down device
 */
void fm_power_down ( fm_t *ctx );

/**
 * @brief Reading CHANNEL bits
 *
 * @param ctx                 Click object.
 * @returns channel - value of channel bits - bits [9:0]
 *
 * @description This function reads CHANNEL bits from READCHAN register
 */
uint16_t fm_get_channel ( fm_t *ctx );

/**
 * @brief Setting CHANNEL bits
 *
 * @param ctx                 Click object.
 * @param channel - value stored in channel bits - bits [9:0]
 *
 * @description This function sets CHANNEL bits in CHANNEL register
 */
void fm_tune_channel ( fm_t *ctx, uint16_t channel );

/**
 * @brief Tunning radio station
 *
 * @param ctx                 Click object.
 * @param channel_frequency - frequency of the channel to be tuned
 * @returns 0 or 1
 *
 * @description This function sets channel for desired radio station and sets tune enable bit
 * This function returns 0 if radio station frequency is in valid range
 * This function returns 1 if radio station frequency is not in valid range
 */
uint8_t fm_tune ( fm_t *ctx, float channel_frequency );

/**
 * @brief End tunning
 * 
 * @param ctx                 Click object.
 *
 * @description This function ends tunning radio station by setting TUNE bit LOW
 * This function must be executed after getting tune done interrupt flag
 * This function can be executed before getting tune done interrupt flag
 */
void fm_end_tune ( fm_t *ctx );

/**
 * @brief Start seeking radio station
 *
 * @param ctx                 Click object.
 *
 * @description This function starts seeking radio stations according to basic seek setings
 * This function seeks stations by seeking up and wraps to lower band limit upon reaching upper band limit if basic settings have not been changed
 */
void fm_seek ( fm_t *ctx );

/**
 * @brief End seeking
 *
 * @param ctx                 Click object.
 *
 * @description This function ends seek by setting SEEK bit LOW
 * This function must be called after fm_seek(); function
 * This function must be executed after seek done interrupt flag
 * This function can be executed before seek done interrupt flag
 */
void fm_end_seek ( fm_t *ctx );

/**
 * @brief Increasing volume level
 *
 * @param ctx                 Click object.
 * @returns (o or 1)
 *
 * @description This function increases volume level
 * This function returns 0 if volume level increased
 * This function returns 1 if volume level reached maximum value
 */
uint8_t fm_volume_up ( fm_t *ctx );

/**
 * @brief Decreasing volume level
 *
 * @param ctx                 Click object.
 * @returns (o or 1)
 *
 * @description This function decreases volume level
 * This function returns 0 if volume level decreased
 * This function returns 1 if volume level reached minimum value
 */
uint8_t fm_volume_down ( fm_t *ctx );

/**
 * @brief Enable mute
 *
 * @param ctx                 Click object.
 * 
 * @description This function enables mute
 */
void fm_mute_enable ( fm_t *ctx );

/**
 * @brief Disable mute
 *
 * @param ctx                 Click object.
 * 
 * @description This function disables mute
 */
void fm_mute_disable ( fm_t *ctx );

/**
 * @brief Fine tunning
 *
 * @param ctx                 Click object.
 * @returns 0 if tuned frequency is in valid range; 1 if tuned frequency reached upper band limit
 * 
 * @description This fine tunes frequency in smallest possible increments for spacing setting
 */
uint8_t fm_fine_tune_up ( fm_t *ctx);

/**
 * @brief Fine tunning
 * 
 * @param ctx                 Click object.
 * @returns 0 if tuned frequency is in valid range; 1 if tuned frequency reached lower band limit
 * @description This fine tunes frequency in smallest possible increments for spacing setting
 */
uint8_t fm_fine_tune_down ( fm_t *ctx );

/**
 * @brief Checking INT pin status
 *
 * @param ctx                 Click object.
 * @returns int pin status - (0 or 1)
 *
 * @description This function returns 0 if INT pin is LOW or 1 if INT pin is HIGH
 */
uint8_t fm_get_int_pin ( fm_t *ctx );

/**
 * @brief Checking AN pin status
 *
 * @returns int pin status - (0 or 1)
 *
 * @description This function returns 0 if AN pin is LOW or 1 if AN pin is HIGH
 */
uint8_t fm_get_an_pin ( fm_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _FM_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
