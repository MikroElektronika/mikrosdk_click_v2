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
 * \brief This file contains API for Ambient 11 Click driver.
 *
 * \addtogroup ambient11 Ambient 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMBIENT11_H
#define AMBIENT11_H

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
#define AMBIENT11_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMBIENT11_RETVAL  uint8_t

#define AMBIENT11_OK                                        0x00
#define AMBIENT11_INIT_ERROR                                0xFF
/** \} */

/**
 * \defgroup ambient11_I2C slave address
 * \{
 */
#define AMBIENT11_SLAVE_ADDRESS                             0x29
/** \} */

/**
 * \defgroup ambient11_commands
 * \{
 */
#define AMBIENT11_ALS_CONF_WR                               0x00
#define AMBIENT11_TRSHLD_WINDOW_SET_HIGH                    0x01
#define AMBIENT11_TRSHLD_WINDOW_SET_LOW                     0x02
#define AMBIENT11_ALS_CONF_RD                               0x04
#define AMBIENT11_WHITE_VAL                                 0x05
#define AMBIENT11_TRSHLD_TRIG_INT                           0x06
/** \} */

/**
 * \defgroup ambient11_configuration register settings
 * \{
 */
#define AMBIENT11_ALS_CONF_SENS_LOW                         0x1000
#define AMBIENT11_ALS_CONF_DG_DOUBLE                        0x0800
#define AMBIENT11_ALS_CONF_GAIN_DOUBLE_SENS                 0x0400
#define AMBIENT11_ALS_CONF_IT_25                            0x0300
#define AMBIENT11_ALS_CONF_IT_50                            0x0200
#define AMBIENT11_ALS_CONF_IT_100                           0x0000
#define AMBIENT11_ALS_CONF_IT_200                           0x0040
#define AMBIENT11_ALS_CONF_IT_400                           0x0080
#define AMBIENT11_ALS_CONF_IT_800                           0x00C0
#define AMBIENT11_ALS_CONF_PERS_1                           0x0000
#define AMBIENT11_ALS_CONF_PERS_2                           0x0010
#define AMBIENT11_ALS_CONF_PERS_4                           0x0020
#define AMBIENT11_ALS_CONF_PERS_8                           0x0030
#define AMBIENT11_ALS_CONF_INT_CHAN                         0x0008
#define AMBIENT11_ALS_CONF_CHAN_EN                          0x0004
#define AMBIENT11_ALS_CONF_INT_EN                           0x0002
#define AMBIENT11_ALS_CONF_SHUT_DOWN                        0x0001
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

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} ambient11_t;

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

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} ambient11_cfg_t;

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
void ambient11_cfg_setup ( ambient11_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AMBIENT11_RETVAL ambient11_init ( ambient11_t *ctx, ambient11_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Ambient11 click.
 */
void ambient11_default_cfg ( ambient11_t *ctx );

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
void ambient11_generic_write ( ambient11_t *ctx, uint8_t wr_cmd, uint16_t wr_data );

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
uint16_t ambient11_generic_read ( ambient11_t *ctx, uint8_t reg_addr );

/**
 * @brief Calculate Illumination function
 *
 * @param[in] typical_res  float value that defines resolution
 *
 * @returns lx_val float value that shows illumination in lux
 *
 * @description Function is used to calculate ambiental illumination.
 * @note The devices resolution depends on settings applied.
 * User should consult the datasheet and choose resolution value 
 * that corresponds to the settings applied.
**/
float ambient11_calc_illumination ( ambient11_t *ctx, float typical_res );

/**
 * @brief Check interrupt function
 *
 * @returns 0 - Interrupt has occured / 1 - Interrupt has not occured
 *
 * @description Function checks interrupt occurence.
**/
uint8_t ambient11_check_int ( ambient11_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AMBIENT11_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
