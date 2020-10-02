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
 * \brief This file contains API for MIC24045 Click driver.
 *
 * \addtogroup mic24045 MIC24045 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MIC24045_H
#define MIC24045_H

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
#define MIC24045_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MIC24045_RETVAL  uint8_t

#define MIC24045_OK           0x00
#define MIC24045_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mic24045_addess addess
 * \{
 */
#define MIC24045_I2C_ADDESS_0_0                               0x50
#define MIC24045_I2C_ADDESS_0_1                               0x51
#define MIC24045_I2C_ADDESS_1_0                               0x52
#define MIC24045_I2C_ADDESS_1_1                               0x53
#define MIC24045_I2C_ADDESS_0_HIGH_Z                          0x54
#define MIC24045_I2C_ADDESS_HIGH_Z_0                          0x55
#define MIC24045_I2C_ADDESS_1_HIGH_Z                          0x56
#define MIC24045_I2C_ADDESS_HIGH_Z_1                          0x57
#define MIC24045_I2C_ADDESS_HIGH_Z_HIGH_Z                     0x58
/** \} */

/**
 * \defgroup mic24045_status status
 * \{
 */
#define MIC24045_REG_STATUS                                   0x00
#define MIC24045_REG_SETTINGS1                                0x01
#define MIC24045_REG_SETTINGS2                                0x02
#define MIC24045_REG_VOUT                                     0x03
#define MIC24045_REG_COMMAND                                  0x04
/** \} */

/**
 * \defgroup mic24045_bit bit
 * \{
 */
#define MIC24045_BIT_PGS                                      0x01
#define MIC24045_BIT_ENS                                      0x08
#define MIC24045_BIT_THWRNF                                   0x20
#define MIC24045_BIT_THSDF                                    0x40
#define MIC24045_BIT_OCF                                      0x80
#define MIC24045_BIT_CIFF                                     0x01
/** \} */

/**
 * \defgroup current_limit_bit bit
 * \{
 */
#define MIC24045_SETTING_CURRENT_NORMAL_LOAD_2_A              0x00
#define MIC24045_SETTING_CURRENT_NORMAL_LOAD_3_A              0x40
#define MIC24045_SETTING_CURRENT_NORMAL_LOAD_4_A              0x80
#define MIC24045_SETTING_CURRENT_NORMAL_LOAD_5_A              0xC0
/** \} */

/**
 * \defgroup switching_frequency_bit frequency
 * \{
 */
#define MIC24045_SETTING_FREQUENCY_310_kHz                    0x00
#define MIC24045_SETTING_FREQUENCY_400_kHz                    0x08
#define MIC24045_SETTING_FREQUENCY_500_kHz                    0x10
#define MIC24045_SETTING_FREQUENCY_570_kHz                    0x18
#define MIC24045_SETTING_FREQUENCY_660_kHz                    0x20
#define MIC24045_SETTING_FREQUENCY_780_kHz                    0x28
#define MIC24045_SETTING_FREQUENCY_970_kHz                    0x30
#define MIC24045_SETTING_FREQUENCY_1200_kHz                   0x38
/** \} */

/**
 * \defgroup start_up_delay_bit delay
 * \{
 */
#define MIC24045_SETTING_START_UP_DELAY_0_ms                  0x00
#define MIC24045_SETTING_START_UP_DELAY_0_5_ms                0x10
#define MIC24045_SETTING_START_UP_DELAY_1_ms                  0x20
#define MIC24045_SETTING_START_UP_DELAY_2_ms                  0x30
#define MIC24045_SETTING_START_UP_DELAY_4_ms                  0x40
#define MIC24045_SETTING_START_UP_DELAY_6_ms                  0x50
#define MIC24045_SETTING_START_UP_DELAY_8_ms                  0x60
#define MIC24045_SETTING_START_UP_DELAY_10_ms                 0x70
/** \} */

/**
 * \defgroup voltage_margins_bit margins
 * \{
 */
#define MIC24045_SETTING_CHANGE_NOMINAL_0_PERC                0x00
#define MIC24045_SETTING_CHANGE_NOMINAL_NEG_5_PERC            0x04
#define MIC24045_SETTING_CHANGE_NOMINAL_POS_5_PERC            0x08
#define MIC24045_SETTING_CHANGE_NOMINAL_POS_5_0_PERC          0x0C
/** \} */

/**
 * \defgroup soft_start_ramp_rate_bit rate_bit
 * \{
 */
#define MIC24045_SETTING_SOFT_START_SLOPE_0_16_Vms            0x00
#define MIC24045_SETTING_SOFT_START_SLOPE_0_38_Vms            0x01
#define MIC24045_SETTING_SOFT_START_SLOPE_0_76_Vms            0x02
#define MIC24045_SETTING_SOFT_START_SLOPE_1_50_Vms            0x03
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

    digital_out_t en;

    // Input pins 

    digital_in_t pg;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} mic24045_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t pg;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} mic24045_cfg_t;

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
void mic24045_cfg_setup ( mic24045_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MIC24045_RETVAL mic24045_init ( mic24045_t *ctx, mic24045_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Mic24045 click.
 */
void mic24045_default_cfg ( mic24045_t *ctx );

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
void mic24045_generic_write ( mic24045_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void mic24045_generic_read ( mic24045_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get status function.
 *
 * @param ctx          Click object.
 *
 * @description This function is getting status.
 */
uint8_t mic24045_get_status ( mic24045_t *ctx );

/**
 * @brief Get voltage.
 * 
 * @param ctx          Click object.
 * 
 * @description This function is getting voltage.
 */
float mic24045_get_vout ( mic24045_t *ctx );

/**
 * @brief Set voltage.
 * 
 * @param ctx          Click object.
 * @param v out        float param
 *
 * @description This function is setting v out.
 */
void mic24045_set_vout( mic24045_t *ctx, float v_out );

/**
 * @brief Enable RST.
 * 
 * @param ctx          Click object.
 *
 * @description This function is setting rst on HIGH
 */
void mic24045_enable( mic24045_t *ctx );

/**
 * @brief Disable RST.
 * 
 * @param ctx          Click object.
 *
 * @description This function is setting rst on LOW
 */
void mic24045_disable( mic24045_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MIC24045_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
