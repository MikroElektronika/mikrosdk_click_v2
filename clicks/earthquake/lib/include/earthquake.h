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
 * \brief This file contains API for Earthquake Click driver.
 *
 * \addtogroup earthquake Earthquake Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EARTHQUAKE_H
#define EARTHQUAKE_H

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
#define EARTHQUAKE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.st = MIKROBUS( mikrobus, MIKROBUS_CS );    \
  cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup    Earthquake Sensor Mode
 * \{
 */
#define EARTHQUAKE_STANDBY_MODE                                         0
#define EARTHQUAKE_NORMAL_MODE                                          1
#define EARTHQUAKE_INIT_INST                                            2
#define EARTHQUAKE_OFFSET_ACQ                                           3
#define EARTHQUAKE_SELF_DIAGNOSTIC                                      4
 /** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EARTHQUAKE_RETVAL  uint8_t

#define EARTHQUAKE_OK           0x00
#define EARTHQUAKE_INIT_ERROR   0xFF
/** \} */

/** \} */ // End group macro 

// -------------------------------------------------------------- PRIVATE MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup I2C address
 * \{
 */
#define EARTHQUAKE_I2C_ADDRESS                                           0x55
/** \} */

/**
 * \defgroup    Return Values
 * \{
 */
#define EARTHQUAKE_CLICK_ERR                                             0xFF
#define EARTHQUAKE_CLICK_OK                                              0x00
 /** \} */

/**
 * \defgroup Earthquake Registers Status
 * \{
 */
#define EARTHQUAKE_STATE                                                0x1000
#define EARTHQUAKE_AXIS_STATE                                           0x1001
#define EARTHQUAKE_EVENT                                                0x1002
/** \} */

/**
 * \defgroup Change Status
 * \{
 */
#define EARTHQUAKE_MODE                                                 0x1003
#define EARTHQUAKE_CTRL                                                 0x1004
#define EARTHQUAKE_CLEAR_COMMAND                                        0x1005
/** \} */

/**
 * \defgroup Earthquake-Related Data (During an Earthquake)
 * \{
 */
#define EARTHQUAKE_MAIN_SI_H                                            0x2000
#define EARTHQUAKE_MAIN_SI_L                                            0x2001
#define EARTHQUAKE_MAIN_PGA_H                                           0x2002
#define EARTHQUAKE_MAIN_PGA_L                                           0x2003
/** \} */

/**
 * \defgroup Latest Data 1
 * \{
 */
#define EARTHQUAKE_N1_MAIN_OFFSET_X_H                                   0x3000
#define EARTHQUAKE_N1_MAIN_OFFSET_X_L                                   0x3001
#define EARTHQUAKE_N1_MAIN_OFFSET_Y_H                                   0x3002
#define EARTHQUAKE_N1_MAIN_OFFSET_Y_L                                   0x3003
#define EARTHQUAKE_N1_MAIN_OFFSET_Z_H                                   0x3004
#define EARTHQUAKE_N1_MAIN_OFFSET_Z_L                                   0x3005

#define EARTHQUAKE_N1_MAIN_T_AVE_H                                      0x3006
#define EARTHQUAKE_N1_MAIN_T_AVE_L                                      0x3007
#define EARTHQUAKE_N1_MAIN_SI_H                                         0x3008
#define EARTHQUAKE_N1_MAIN_SI_L                                         0x3009
#define EARTHQUAKE_N1_MAIN_PGA_H                                        0x300A
#define EARTHQUAKE_N1_MAIN_PGA_L                                        0x300B
/** \} */

/**
 * \defgroup Latest Data 2
 * \{
 */
#define EARTHQUAKE_N2_MAIN_OFFSET_X_H                                   0x3100
#define EARTHQUAKE_N2_MAIN_OFFSET_X_L                                   0x3101
#define EARTHQUAKE_N2_MAIN_OFFSET_Y_H                                   0x3102
#define EARTHQUAKE_N2_MAIN_OFFSET_Y_L                                   0x3103
#define EARTHQUAKE_N2_MAIN_OFFSET_Z_H                                   0x3104
#define EARTHQUAKE_N2_MAIN_OFFSET_Z_L                                   0x3105

#define EARTHQUAKE_N2_MAIN_T_AVE_H                                      0x3106
#define EARTHQUAKE_N2_MAIN_T_AVE_L                                      0x3107
#define EARTHQUAKE_N2_MAIN_SI_H                                         0x3108
#define EARTHQUAKE_N2_MAIN_SI_L                                         0x3109
#define EARTHQUAKE_N2_MAIN_PGA_H                                        0x310A
#define EARTHQUAKE_N2_MAIN_PGA_L                                        0x310B
/** \} */

/**
 * \defgroup Latest Data 3
 * \{
 */
#define EARTHQUAKE_N3_MAIN_OFFSET_X_H                                   0x3200
#define EARTHQUAKE_N3_MAIN_OFFSET_X_L                                   0x3201
#define EARTHQUAKE_N3_MAIN_OFFSET_Y_H                                   0x3202
#define EARTHQUAKE_N3_MAIN_OFFSET_Y_L                                   0x3203
#define EARTHQUAKE_N3_MAIN_OFFSET_Z_H                                   0x3204
#define EARTHQUAKE_N3_MAIN_OFFSET_Z_L                                   0x3205

#define EARTHQUAKE_N3_MAIN_T_AVE_H                                      0x3206
#define EARTHQUAKE_N3_MAIN_T_AVE_L                                      0x3207
#define EARTHQUAKE_N3_MAIN_SI_H                                         0x3208
#define EARTHQUAKE_N3_MAIN_SI_L                                         0x3209
#define EARTHQUAKE_N3_MAIN_PGA_H                                        0x320A
#define EARTHQUAKE_N3_MAIN_PGA_L                                        0x320B
/** \} */

/**
 * \defgroup Latest Data 4
 * \{
 */
#define EARTHQUAKE_N4_MAIN_OFFSET_X_H                                   0x3300
#define EARTHQUAKE_N4_MAIN_OFFSET_X_L                                   0x3301
#define EARTHQUAKE_N4_MAIN_OFFSET_Y_H                                   0x3302
#define EARTHQUAKE_N4_MAIN_OFFSET_Y_L                                   0x3303
#define EARTHQUAKE_N4_MAIN_OFFSET_Z_H                                   0x3304
#define EARTHQUAKE_N4_MAIN_OFFSET_Z_L                                   0x3305

#define EARTHQUAKE_N4_MAIN_T_AVE_H                                      0x3306
#define EARTHQUAKE_N4_MAIN_T_AVE_L                                      0x3307
#define EARTHQUAKE_N4_MAIN_SI_H                                         0x3308
#define EARTHQUAKE_N4_MAIN_SI_L                                         0x3309
#define EARTHQUAKE_N4_MAIN_PGA_H                                        0x330A
#define EARTHQUAKE_N4_MAIN_PGA_L                                        0x330B
/** \} */

/**
 * \defgroup Latest Data 5
 * \{
 */
#define EARTHQUAKE_N5_MAIN_OFFSET_X_H                                   0x3400
#define EARTHQUAKE_N5_MAIN_OFFSET_X_L                                   0x3401
#define EARTHQUAKE_N5_MAIN_OFFSET_Y_H                                   0x3402
#define EARTHQUAKE_N5_MAIN_OFFSET_Y_L                                   0x3403
#define EARTHQUAKE_N5_MAIN_OFFSET_Z_H                                   0x3404
#define EARTHQUAKE_N5_MAIN_OFFSET_Z_L                                   0x3405

#define EARTHQUAKE_N5_MAIN_T_AVE_H                                      0x3406
#define EARTHQUAKE_N5_MAIN_T_AVE_L                                      0x3407
#define EARTHQUAKE_N5_MAIN_SI_H                                         0x3408
#define EARTHQUAKE_N5_MAIN_SI_L                                         0x3409
#define EARTHQUAKE_N5_MAIN_PGA_H                                        0x340A
#define EARTHQUAKE_N5_MAIN_PGA_L                                        0x340B
/** \} */

/**
 * \defgroup SI Ranked Data 1
 * \{
 */
#define EARTHQUAKE_M1_MAIN_OFFSET_X_H                                   0x3500
#define EARTHQUAKE_M1_MAIN_OFFSET_X_L                                   0x3501
#define EARTHQUAKE_M1_MAIN_OFFSET_Y_H                                   0x3502
#define EARTHQUAKE_M1_MAIN_OFFSET_Y_L                                   0x3503
#define EARTHQUAKE_M1_MAIN_OFFSET_Z_H                                   0x3504
#define EARTHQUAKE_M1_MAIN_OFFSET_Z_L                                   0x3505

#define EARTHQUAKE_M1_MAIN_T_AVE_H                                      0x3506
#define EARTHQUAKE_M1_MAIN_T_AVE_L                                      0x3507
#define EARTHQUAKE_M1_MAIN_SI_H                                         0x3508
#define EARTHQUAKE_M1_MAIN_SI_L                                         0x3509
#define EARTHQUAKE_M1_MAIN_PGA_H                                        0x350A
#define EARTHQUAKE_M1_MAIN_PGA_L                                        0x350B
/** \} */

/**
 * \defgroup SI Ranked Data 2
 * \{
 */
#define EARTHQUAKE_M2_MAIN_OFFSET_X_H                                   0x3600
#define EARTHQUAKE_M2_MAIN_OFFSET_X_L                                   0x3601
#define EARTHQUAKE_M2_MAIN_OFFSET_Y_H                                   0x3602
#define EARTHQUAKE_M2_MAIN_OFFSET_Y_L                                   0x3603
#define EARTHQUAKE_M2_MAIN_OFFSET_Z_H                                   0x3604
#define EARTHQUAKE_M2_MAIN_OFFSET_Z_L                                   0x3605

#define EARTHQUAKE_M2_MAIN_T_AVE_H                                      0x3606
#define EARTHQUAKE_M2_MAIN_T_AVE_L                                      0x3607
#define EARTHQUAKE_M2_MAIN_SI_H                                         0x3608
#define EARTHQUAKE_M2_MAIN_SI_L                                         0x3609
#define EARTHQUAKE_M2_MAIN_PGA_H                                        0x360A
#define EARTHQUAKE_M2_MAIN_PGA_L                                        0x360B
/** \} */

/**
 * \defgroup SI Ranked Data 3
 * \{
 */
#define EARTHQUAKE_M3_MAIN_OFFSET_X_H                                   0x3700
#define EARTHQUAKE_M3_MAIN_OFFSET_X_L                                   0x3701
#define EARTHQUAKE_M3_MAIN_OFFSET_Y_H                                   0x3702
#define EARTHQUAKE_M3_MAIN_OFFSET_Y_L                                   0x3703
#define EARTHQUAKE_M3_MAIN_OFFSET_Z_H                                   0x3704
#define EARTHQUAKE_M3_MAIN_OFFSET_Z_L                                   0x3705

#define EARTHQUAKE_M3_MAIN_T_AVE_H                                      0x3706
#define EARTHQUAKE_M3_MAIN_T_AVE_L                                      0x3707
#define EARTHQUAKE_M3_MAIN_SI_H                                         0x3708
#define EARTHQUAKE_M3_MAIN_SI_L                                         0x3709
#define EARTHQUAKE_M3_MAIN_PGA_H                                        0x370A
#define EARTHQUAKE_M3_MAIN_PGA_L                                        0x370B
/** \} */

/**
 * \defgroup SI Ranked Data 4
 * \{
 */
#define EARTHQUAKE_M4_MAIN_OFFSET_X_H                                   0x3800
#define EARTHQUAKE_M4_MAIN_OFFSET_X_L                                   0x3801
#define EARTHQUAKE_M4_MAIN_OFFSET_Y_H                                   0x3802
#define EARTHQUAKE_M4_MAIN_OFFSET_Y_L                                   0x3803
#define EARTHQUAKE_M4_MAIN_OFFSET_Z_H                                   0x3804
#define EARTHQUAKE_M4_MAIN_OFFSET_Z_L                                   0x3805

#define EARTHQUAKE_M4_MAIN_T_AVE_H                                      0x3806
#define EARTHQUAKE_M4_MAIN_T_AVE_L                                      0x3807
#define EARTHQUAKE_M4_MAIN_SI_H                                         0x3808
#define EARTHQUAKE_M4_MAIN_SI_L                                         0x3809
#define EARTHQUAKE_M4_MAIN_PGA_H                                        0x380A
#define EARTHQUAKE_M4_MAIN_PGA_L                                        0x380B
/** \} */

/**
 * \defgroup SI Ranked Data 5
 * \{
 */
#define EARTHQUAKE_M5_MAIN_OFFSET_X_H                                   0x3900
#define EARTHQUAKE_M5_MAIN_OFFSET_X_L                                   0x3901
#define EARTHQUAKE_M5_MAIN_OFFSET_Y_H                                   0x3902
#define EARTHQUAKE_M5_MAIN_OFFSET_Y_L                                   0x3903
#define EARTHQUAKE_M5_MAIN_OFFSET_Z_H                                   0x3904
#define EARTHQUAKE_M5_MAIN_OFFSET_Z_L                                   0x3905

#define EARTHQUAKE_M5_MAIN_T_AVE_H                                      0x3906
#define EARTHQUAKE_M5_MAIN_T_AVE_L                                      0x3907
#define EARTHQUAKE_M5_MAIN_SI_H                                         0x3908
#define EARTHQUAKE_M5_MAIN_SI_L                                         0x3909
#define EARTHQUAKE_M5_MAIN_PGA_H                                        0x390A
#define EARTHQUAKE_M5_MAIN_PGA_L                                        0x390B
/** \} */

/**
 * \defgroup Initial Installation Data
 * \{
 */
#define EARTHQUAKE_OFFSET_SET_X_H                                       0x4000
#define EARTHQUAKE_OFFSET_SET_X_L                                       0x4001
#define EARTHQUAKE_OFFSET_SET_Y_H                                       0x4002
#define EARTHQUAKE_OFFSET_SET_Y_L                                       0x4003
#define EARTHQUAKE_OFFSET_SET_Z_H                                       0x4004
#define EARTHQUAKE_OFFSET_SET_Z_L                                       0x4005

#define EARTHQUAKE_OFFSET_SET_T_AVE_H                                   0x4006
#define EARTHQUAKE_OFFSET_SET_T_AVE_L                                   0x4007
#define EARTHQUAKE_OFFSET_SET_MAX_X_H                                   0x4008
#define EARTHQUAKE_OFFSET_SET_MAX_X_L                                   0x4009
#define EARTHQUAKE_OFFSET_SET_MAX_Y_H                                   0x400A
#define EARTHQUAKE_OFFSET_SET_MAX_Y_L                                   0x400B
#define EARTHQUAKE_OFFSET_SET_MAX_Z_H                                   0x400C
#define EARTHQUAKE_OFFSET_SET_MAX_Z_L                                   0x400D

#define EARTHQUAKE_OFFSET_SET_MIN_X_H                                   0x400E
#define EARTHQUAKE_OFFSET_SET_MIN_X_L                                   0x400F
#define EARTHQUAKE_OFFSET_SET_MIN_Y_H                                   0x4010
#define EARTHQUAKE_OFFSET_SET_MIN_Y_L                                   0x4011
#define EARTHQUAKE_OFFSET_SET_MIN_Z_H                                   0x4012
#define EARTHQUAKE_OFFSET_SET_MIN_Z_L                                   0x4013

#define EARTHQUAKE_OFFSET_SET_AXIS                                      0x4014
/** \} */

/**
 * \defgroup Latest Offset Data
 * \{
 */
#define EARTHQUAKE_OFFSET_RECENT_X_H                                    0x4100
#define EARTHQUAKE_OFFSET_RECENT_X_L                                    0x4101
#define EARTHQUAKE_OFFSET_RECENT_Y_H                                    0x4102
#define EARTHQUAKE_OFFSET_RECENT_Y_L                                    0x4103
#define EARTHQUAKE_OFFSET_RECENT_Z_H                                    0x4104
#define EARTHQUAKE_OFFSET_RECENT_Z_L                                    0x4105

#define EARTHQUAKE_OFFSET_RECENT_T_AVE_H                                0x4106
#define EARTHQUAKE_OFFSET_RECENT_T_AVE_L                                0x4107

#define EARTHQUAKE_OFFSET_RECENT_MAX_X_H                                0x4108
#define EARTHQUAKE_OFFSET_RECENT_MAX_X_L                                0x4109
#define EARTHQUAKE_OFFSET_RECENT_MAX_Y_H                                0x410A
#define EARTHQUAKE_OFFSET_RECENT_MAX_Y_L                                0x410B
#define EARTHQUAKE_OFFSET_RECENT_MAX_Z_H                                0x410C
#define EARTHQUAKE_OFFSET_RECENT_MAX_Z_L                                0x410D

#define EARTHQUAKE_OFFSET_RECENT_MIN_X_H                                0x410E
#define EARTHQUAKE_OFFSET_RECENT_MIN_X_L                                0x410F
#define EARTHQUAKE_OFFSET_RECENT_MIN_Y_H                                0x4110
#define EARTHQUAKE_OFFSET_RECENT_MIN_Y_L                                0x4111
#define EARTHQUAKE_OFFSET_RECENT_MIN_Z_H                                0x4112
#define EARTHQUAKE_OFFSET_RECENT_MIN_Z_L                                0x4113

#define EARTHQUAKE_OFFSET_RECENT_STATE                                  0x4114
/** \} */

/**
 * \defgroup Self-Diagnostic Data
 * \{
 */
#define EARTHQUAKE_SELFTEST_BEFORE_X_H                                  0x4200
#define EARTHQUAKE_SELFTEST_BEFORE_X_L                                  0x4201
#define EARTHQUAKE_SELFTEST_AFTER_X_H                                   0x4202
#define EARTHQUAKE_SELFTEST_AFTER_X_L                                   0x4203
#define EARTHQUAKE_SELFTEST_BEFORE_Y_H                                  0x4204
#define EARTHQUAKE_SELFTEST_BEFORE_Y_L                                  0x4205
#define EARTHQUAKE_SELFTEST_AFTER_Y_H                                   0x4206
#define EARTHQUAKE_SELFTEST_AFTER_Y_L                                   0x4207
#define EARTHQUAKE_SELFTEST_BEFORE_Z_H                                  0x4208
#define EARTHQUAKE_SELFTEST_BEFORE_Z_L                                  0x4209
#define EARTHQUAKE_SELFTEST_AFTER_Z_H                                   0x420A
#define EARTHQUAKE_SELFTEST_AFTER_Z_L                                   0x420B

#define EARTHQUAKE_SELFTEST_T_AVE_H                                     0x420C
#define EARTHQUAKE_SELFTEST_T_AVE_L                                     0x420D

#define EARTHQUAKE_SELFTEST_ERROR                                       0x420E
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

    digital_in_t int2;
    digital_in_t int1;

    // Output pins 

    digital_out_t st;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} earthquake_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t st;
    pin_name_t int2;
    pin_name_t int1;

    // static variable 

    uint8_t i2c_speed;
    uint8_t i2c_address;

} earthquake_cfg_t;

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
void earthquake_cfg_setup ( earthquake_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param earthquake Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EARTHQUAKE_RETVAL earthquake_init ( earthquake_t *ctx, earthquake_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Earthquake click.
 */
void earthquake_default_cfg ( earthquake_t *ctx );

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
void earthquake_generic_write ( earthquake_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void earthquake_generic_read ( earthquake_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Shutoff output function.
 *
 * 
 * @param ctx          Click object.
 * @returns 
 * - 0 :  when idle;
 * - 1 :  when working;
 *
 * @description This function reads state od INT2 pin.
 * An open-drain output, goes active during earthquake calculations, 
 * offset acquisition, and self-diagnostic processing.
 */
uint8_t earthquake_proc_notify ( earthquake_t *ctx );

/**
 * @brief Shutoff output function.
 * 
 * @param ctx          Click object.
 * @returns
 * - 0 :  when idle;
 * - 1 :  when working;
 *
 * @description This function reads state od INT1 pin.
 * An open-drain output, goes active (ON) when the shutoff judgment condition
 * and collapse detection condition are met.
 */
uint8_t earthquake_shutoff_output ( earthquake_t *ctx );

/**
 * @brief Read status function.
 * 
 * @param ctx          Click object.
 * @returns value that represents status
 * - 0 : Normal Mode standby
 * - 1 : Normal Mode not in standby
 * - 2 : Initial Installation Mode
 * - 3 : Offset Acquisition Mode
 * - 4 : Self-Diagnostic Mode
 *
 * @description This function reads data from a STATE register.
 */
uint8_t earthquake_read_status ( earthquake_t *ctx );

/**
 * @brief Read SI function.
 * 
 * @param ctx          Click object.
 * @returns combined values of SI_H and SI_L registers
 *
 * @description This function reads and combines data 
 * from SI_H and SI_L registers.
 */
uint16_t earthquake_read_si ( earthquake_t *ctx );

/**
 * @brief Clear Memory function
 * 
 * @param ctx          Click object.
 * @returns combined values of SI_H and SI_L registers
 *
 * @description This function clears earthquake data, 
 * self-diagnostic data, latest offset data and initial installation data.
 */
void earthquake_clear_mememory ( earthquake_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _EARTHQUAKE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
