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
 * \brief This file contains API for Remote Temp Click driver.
 *
 * \addtogroup remotetemp Remote Temp Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef REMOTETEMP_H
#define REMOTETEMP_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define REMOTETEMP_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.thm = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define REMOTETEMP_RETVAL  uint8_t

#define REMOTETEMP_OK                  0x00
#define REMOTETEMP_INIT_ERROR          0xFF
/** \} */

/**
 * \defgroup device_addresses Device Addresses
 * \{
 */
#define REMOTETEMP_DEVICE_ADDRESS_4p7  0x7C
#define REMOTETEMP_DEVICE_ADDRESS_6p8  0x5C
#define REMOTETEMP_DEVICE_ADDRESS_10   0x4C
#define REMOTETEMP_DEVICE_ADDRESS_15   0x6C
#define REMOTETEMP_DEVICE_ADDRESS_22   0x1C
#define REMOTETEMP_DEVICE_ADDRESS_33   0x3C
/** \} */

/**
 * \defgroup ranges Ranges
 * \{
 */
#define REMOTETEMP_RANGE_0_127         0x00
#define REMOTETEMP_RANGE_m64_191       0x01
/** \} */

/**
 * \defgroup external_diodes External Diodes
 * \{
 */
#define REMOTETEMP_EXT_DIODE_1         0x01
#define REMOTETEMP_EXT_DIODE_2         0x02
#define REMOTETEMP_EXT_DIODE_3         0x03
#define REMOTETEMP_EXT_DIODE_4         0x04
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define REMOTETEMP_STATUS                                   0x02
#define REMOTETEMP_CONFIG                                   0x09
#define REMOTETEMP_CONVERT                                  0x0A
#define REMOTETEMP_INT_DIODE_HIGH_LIMIT                     0x0B
#define REMOTETEMP_INT_DIODE_LOW_LIMIT                      0x0C
#define REMOTETEMP_EXT1_HIGH_LIMIT_HIGH_BYTE                0x0D
#define REMOTETEMP_EXT1_LOW_LIMIT_HIGH_BYTE                 0x0E
#define REMOTETEMP_ONE_SHOT                                 0x0F
#define REMOTETEMP_SCRTCHPD1                                0x11
#define REMOTETEMP_SCRTCHPD2                                0x12
#define REMOTETEMP_EXT1_HIGH_LIMIT_LOW_BYTE                 0x13
#define REMOTETEMP_EXT1_LOW_LIMIT_LOW_BYTE                  0x14
#define REMOTETEMP_EXT2_HIGH_LIMIT_HIGH_BYTE                0x15
#define REMOTETEMP_EXT2_LOW_LIMIT_HIGH_BYTE                 0x16
#define REMOTETEMP_EXT2_HIGH_LIMIT_LOW_BYTE                 0x17
#define REMOTETEMP_EXT2_LOW_LIMIT_LOW_BYTE                  0x18
#define REMOTETEMP_EXT1_THERM_LIMIT                         0x19
#define REMOTETEMP_EXT2_THERM_LIMIT                         0x1A
#define REMOTETEMP_EXTERNAL_DIODE_FAULT_STATUS              0x1B
#define REMOTETEMP_DIODE_FAULT_MASK                         0x1F
#define REMOTETEMP_INT_DIODE_THERM_LIMIT                    0x20
#define REMOTETEMP_THRM_HYS                                 0x21
#define REMOTETEMP_CONSEC_ALERT                             0x22
#define REMOTETEMP_EXT1_BETA_CONFIG                         0x25
#define REMOTETEMP_EXT2_BETA_CONFIG                         0x26
#define REMOTETEMP_EXT1_IDEALITY_FACTOR                     0x27
#define REMOTETEMP_EXT2_IDEALITY_FACTOR                     0x28
#define REMOTETEMP_EXT3_HIGH_LIMIT_HIGH_BYTE                0x2C
#define REMOTETEMP_EXT3_LOW_LIMIT_HIGH_BYTE                 0x2D
#define REMOTETEMP_EXT3_HIGH_LIMIT_LOW_BYTE                 0x2E
#define REMOTETEMP_EXT3_LOW_LIMIT_LOW_BYTE                  0x2F
#define REMOTETEMP_EXT3_THERM_LIMIT                         0x30
#define REMOTETEMP_EXT3_IDEALITY_FACTOR                     0x31
#define REMOTETEMP_EXT4_HIGH_LIMIT_HIGH_BYTE                0x34
#define REMOTETEMP_EXT4_LOW_LIMIT_HIGH_BYTE                 0x35
#define REMOTETEMP_EXT4_HIGH_LIMIT_LOW_BYTE                 0x36
#define REMOTETEMP_EXT4_LOW_LIMIT_LOW_BYTE                  0x37
#define REMOTETEMP_EXT4_THERM_LIMIT                         0x38
#define REMOTETEMP_EXT4_IDEALITY_FACTOR                     0x39
#define REMOTETEMP_HIGH_LIMIT_STATUS                        0x3A
#define REMOTETEMP_LOW_LIMIT_STATUS                         0x3B
#define REMOTETEMP_THERM_LIMIT_STATUS                       0x3C
#define REMOTETEMP_ROC_GAIN                                 0x3D
#define REMOTETEMP_ROC_CONFIG                               0x3E
#define REMOTETEMP_ROC_STATUS                               0x3F
#define REMOTETEMP_R1_RESH                                  0x40
#define REMOTETEMP_R1_LIMH                                  0x41
#define REMOTETEMP_R1_LIML                                  0x42
#define REMOTETEMP_R1_SMPL                                  0x43
#define REMOTETEMP_R2_RESH                                  0x44
#define REMOTETEMP_R23_RESL                                 0x45
#define REMOTETEMP_R2_LIMH                                  0x46
#define REMOTETEMP_R2_LIML                                  0x47
#define REMOTETEMP_R2_SMPL                                  0x48
#define REMOTETEMP_PER_MAXT1L                               0x4A
#define REMOTETEMP_PER_MAXTH                                0x4B
#define REMOTETEMP_PER_MAXT23L                              0x4C
#define REMOTETEMP_GBL_MAXT1H                               0x4D
#define REMOTETEMP_GBL_MAXT1L                               0x4E
#define REMOTETEMP_GBL_MAXT2H                               0x4F
#define REMOTETEMP_GBL_MAXT2L                               0x50
#define REMOTETEMP_FILTER_SEL                               0x51
#define REMOTETEMP_INT_HIGH_BYTE                            0x60
#define REMOTETEMP_INT_LOW_BYTE                             0x61
#define REMOTETEMP_EXT1_HIGH_BYTE                           0x62
#define REMOTETEMP_EXT1_LOW_BYTE                            0x63
#define REMOTETEMP_EXT2_HIGH_BYTE                           0x64
#define REMOTETEMP_EXT2_LOW_BYTE                            0x65
#define REMOTETEMP_EXT3_HIGH_BYTE                           0x66
#define REMOTETEMP_EXT3_LOW_BYTE                            0x67
#define REMOTETEMP_EXT4_HIGH_BYTE                           0x68
#define REMOTETEMP_EXT4_LOW_BYTE                            0x69
#define REMOTETEMP_HOTTEST_DIODE_HIGH_BYTE                  0x6A
#define REMOTETEMP_HOTTEST_DIODE_LOW_BYTE                   0x6B
#define REMOTETEMP_HOTTEST_STATUS                           0x6C
#define REMOTETEMP_HOTTEST_CONFIG                           0x6D
#define REMOTETEMP_PRODUCT_ID                               0xFD
#define REMOTETEMP_MANUFACTURER_ID                          0xFE
#define REMOTETEMP_REVISION                                 0xFF
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

    digital_in_t thm;
    digital_in_t alr;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint8_t range_set;

} remotetemp_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t thm;
    pin_name_t alr;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} remotetemp_cfg_t;

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
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void remotetemp_cfg_setup ( remotetemp_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
REMOTETEMP_RETVAL remotetemp_init ( remotetemp_t *ctx, remotetemp_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for RemoteTemp click.
 */
void remotetemp_default_cfg ( remotetemp_t *ctx );

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
void remotetemp_generic_write ( remotetemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void remotetemp_generic_read ( remotetemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );


/**
 * @brief Getting state of INT pin.
 *
 * @param ctx  Click object.
 * 
 * @returns 0 if INT pin is in LOW state.
 * @returns 1 if INT pin is in HIGH state.
 *
 * @description This function gets state of INT pin.
 */
uint8_t remotetemp_int_get ( remotetemp_t *ctx );

/**
 * @brief Getting state of AN pin.
 *
 * @param ctx  Click object.
 *
 * @returns 0 if AN pin is in LOW state.
 * @returns 1 if AN pin is in HIGH state.
 * 
 * @description This function gets state of AN pin.
 */
uint8_t remotetemp_an_get ( remotetemp_t *ctx );

/**
 * @brief Setting temperature range.
 *
 * @param ctx             Click object.
 * @param range_setting   Sets temperature range.
 * 
 * @returns 0 for successful range parameter.
 * @returns 1 for invalid range parameter.
 * 
 * @description This function sets temperature range (( from 0 to 127 ) or ( from (-64) to 191 )).
 */
uint8_t remotetemp_set_range( remotetemp_t *ctx, uint8_t range_setting );

/**
 * @brief Reads register content.
 *
 * @param ctx                Click object.
 * @param register_address   Sets temperature range.
 * @param read_buffer        Buffer for storing register content.
 * @param n_bytes            Number of registers(bytes) to read.
 * 
 * @returns none
 * 
 * @description This function reads content from register(s).
 */
void remotetemp_read ( remotetemp_t *ctx, uint8_t register_address, uint8_t * read_buffer, uint8_t n_bytes );

/**
 * @brief Setting register content.
 *
 * @param ctx                  Click object.
 * @param register_address     Address of the (first) register to write to.
 * @param register_values      Buffer for storing register content.
 * @param n_bytes              Number of registers(bytes) to read.
 * 
 * @returns none
 * 
 * @description This function writes content to register(s).
 */
void remotetemp_write ( remotetemp_t *ctx, uint8_t register_address, uint8_t * register_values, uint8_t n_bytes );

/**
 * @brief Setting Internal diode high limit.
 *
 * @param ctx           Click object.
 * @param limit_value   Threshold value.
 * 
 * @returns none
 * 
 * @description This function sets high threshold value for internal diode.
 */
void remotetemp_set_int_diode_high_limit ( remotetemp_t *ctx, int16_t limit_value );

/**
 * @brief Setting Internal diode low limit.
 *
 * @param ctx           Click object.
 * @param limit_value   Threshold value.
 * 
 * @returns none
 * 
 * @description This function sets low threshold value for internal diode.
 */
void remotetemp_set_int_diode_low_limit ( remotetemp_t *ctx, int16_t limit_value );

/**
 * @brief Setting external diodes high limit.
 *
 * @param ctx           Click object.
 * @param limit_value   Threshold value.
 * @param diode         Diode number.
 * 
 * @returns none
 * 
 * @description This function sets high threshold value for external diodes.
 */
void remotetemp_set_ext_diode_high_limit ( remotetemp_t *ctx, int16_t limit_value, uint8_t diode );

/**
 * @brief Setting external diodes low limit.
 *
 * @param ctx           Click object.
 * @param limit_value   Threshold value.
 * @param diode         Diode number.
 * 
 * @returns none
 * 
 * @description This function sets low threshold values for external diodes.
 */
void remotetemp_set_ext_diode_low_limit ( remotetemp_t *ctx, int16_t limit_value, uint8_t diode );

/**
 * @brief Setting external diodes thermal limits.
 *
 * @param ctx           Click object.
 * @param limit_value   Threshold value.
 * @param diode         Diode number.
 * 
 * @returns none
 * 
 * @description This function sets thermal threshold values for external diodes.
 */
void remotetemp_set_ext_diode_therm_limit ( remotetemp_t *ctx, int16_t limit_value, uint8_t diode );

/**
 * @brief Setting internal diodes thermal limits.
 *
 * @param ctx           Click object.
 * @param limit_value   Threshold value.
 * 
 * @returns none
 * 
 * @description This function sets thermal threshold value for internal diode.
 */
void remotetemp_set_int_diode_therm_limit ( remotetemp_t *ctx, int16_t limit_value );

/**
 * @brief Getting internal diode temperature value.
 *
 * @param ctx  Click object.
 * 
 * @returns float - internal diode temperature value
 * 
 * @description This function reads internal diode registers and calculates temperature value.
 */
float remotetemp_get_internal_diode ( remotetemp_t *ctx );

/**
 * @brief Getting external diode temperature value.
 *
 * @param ctx  Click object.
 * @param diode     Diode number.
 *
 * @returns float - external diode temperature value
 * 
 * @description This function reads external diode registers and calculates temperature value.
 */
float remotetemp_get_external_diode ( remotetemp_t *ctx, uint8_t diode );

/**
 * @brief Getting hottest diode temperature value.
 *
 * @param ctx  Click object.
 *
 * @returns float - hottest diode temperature value
 * 
 * @description This function reads hottest diode registers and calculates temperature value.
 */
float remotetemp_get_hottest_diode ( remotetemp_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _REMOTETEMP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
