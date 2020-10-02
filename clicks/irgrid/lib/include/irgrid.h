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
 * \brief This file contains API for IR Grid Click driver.
 *
 * \addtogroup irgrid IR Grid Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRGRID_H
#define IRGRID_H

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
#define IRGRID_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRGRID_RETVAL  uint8_t

#define IRGRID_OK           0x00
#define IRGRID_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define IRGRID_CAL_ACOMMON_L        0xD0
#define IRGRID_CAL_ACOMMON_H        0xD1
#define IRGRID_CAL_ACP_L            0xD3
#define IRGRID_CAL_ACP_H            0xD4
#define IRGRID_CAL_BCP              0xD5
#define IRGRID_CAL_ALPHA_CP_L       0xD6
#define IRGRID_CAL_ALPHA_CP_H       0xD7
#define IRGRID_CAL_TGC              0xD8
#define IRGRID_CAL_AI_SCALE         0xD9
#define IRGRID_CAL_BI_SCALE         0xD9
#define IRGRID_VTH_L                0xDA
#define IRGRID_VTH_H                0xDB
#define IRGRID_KT1_L                0xDC
#define IRGRID_KT1_H                0xDD
#define IRGRID_KT2_L                0xDE
#define IRGRID_KT2_H                0xDF
#define IRGRID_KT_SCALE             0xD2
#define IRGRID_CAL_A0_L             0xE0
#define IRGRID_CAL_A0_H             0xE1
#define IRGRID_CAL_A0_SCALE         0xE2
#define IRGRID_CAL_DELTA_A_SCALE    0xE3
#define IRGRID_CAL_EMIS_L           0xE4
#define IRGRID_CAL_EMIS_H           0xE5
#define IRGRID_OSC_TRIM_VALUE       0xF7
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

    uint8_t slave_ram_address;
    uint8_t slave_eeprom_address;

    // static variable 
    uint8_t refresh_rate;
    float   temperature_amb;
    int16_t resolution;
    int16_t cpix;
    int16_t ptat;

} irgrid_t;

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
    uint8_t i2c_ram_address;
    uint8_t i2c_eeprom_address;

} irgrid_cfg_t;

/**
 * @brief Click data object definition.
 */
typedef struct
{
    // Static variable 

    uint8_t  eeprom_data[ 256 ];
    int16_t  ir_data[ 64 ];
    float    temperature_data[ 64 ];
    float    a_data[ 64 ];
    float    b_data[ 64 ];
    float    alpha_a_data[ 64 ];

} irgrid_data_t;

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
void irgrid_cfg_setup ( irgrid_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRGRID_RETVAL irgrid_init ( irgrid_t *ctx, irgrid_cfg_t *cfg );

/**
 * @brief Device Initialization
 *
 * @param ctx          Click object.
 * @param data_str     Data click object.
 * @param refrate      Refresh Rate
 *
 * @returns 0 - OK
 *
 *  @description Initializes device, reads eeprom memory and places it inside internal buffers.
 */
uint8_t irgrid_device_init ( irgrid_t *ctx, irgrid_data_t *data_str, uint8_t refrate );

/**
 * @brief Write function using RAM slave adress.
 *
 * @param ctx          Data click object.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void irgrid_write_ram( irgrid_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read function using RAM slave adress.
 *
 * @param ctx          Click object.
 * @param reg          Register address pointer.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void irgrid_read_ram ( irgrid_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write function using EEPROM slave adress.
 *
 * @param ctx          Data click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void irgrid_write_eeprom ( irgrid_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read function using EEPROM slave adress.
 *
 * @param ctx          Click object.
 * @param reg          Register address pointer.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void irgrid_read_eeprom ( irgrid_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Measurement
 *
 * @param ctx          Click object.
 * @param data_str     Data click object.
 * @returns 0 - OK
 *
 * @description Measures temperature and places it inside internal buffers. This function is 
 * needed to be called prior to `irgrid_get_ir_raw` or `irgrid_get_temperature`.
 */
uint8_t irgrid_measure ( irgrid_t *ctx, irgrid_data_t *data_str );

/**
 * @brief Read Raw Temperature buffer
 *
 * @param data_str     Data click object.
 * @param buffer       Output data buf.
 *
 * @description Populates provided buffer with raw measurements. Buffer must have at least 64 members.
 */
void irgrid_get_ir_raw ( irgrid_data_t *data_str, int16_t *buffer );

/**
 * @brief Read Calculated Temperature buffer
 *
 * @param data_str     Data click object.
 * @param buffer       Output data buf.
 *
 * @description Populates provided buffer with calculated temperatures. Buffer must have at least 64 members.
 */
void irgrid_get_temperature ( irgrid_data_t *data_str, float *buffer );

/**
 * @brief Read Ambient Temperature
 *
 * @param ctx          Click object.
 *
 * @returns            Ambient temperature.
 *
 * @description Read Ambient temperautre.
 */
float irgrid_get_amb_temperature ( irgrid_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _IRGRID_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
