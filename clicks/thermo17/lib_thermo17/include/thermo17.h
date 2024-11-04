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
 * \brief This file contains API for Thermo 17 Click driver.
 *
 * \addtogroup thermo17 Thermo 17 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO17_H
#define THERMO17_H

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
#define THERMO17_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup slave_address Device slave address
 * \{
 */
#define THERMO17_SLAVE_ADDRESS                         0x4C
/** \} */

/**
 * \defgroup registers Device register addresses
 * \{
 */
#define THERMO17_REG_R_LOCAL_TEMP_HB                   0x00
#define THERMO17_REG_R_REMOTE_TEMP_HB                  0x01
#define THERMO17_REG_R_STATUS                          0x02
#define THERMO17_REG_R_CFG                             0x03
#define THERMO17_REG_R_CONVERSION_RATE                 0x04
#define THERMO17_REG_R_LOCAL_TEMP_LIMIT_H              0x05
#define THERMO17_REG_R_LOCAL_TEMP_LIMIT_L              0x06
#define THERMO17_REG_R_REMOTE_TEMP_LIMIT_H_HB          0x07
#define THERMO17_REG_R_REMOTE_TEMP_LIMIT_L_HB          0x08
#define THERMO17_REG_R_REMOTE_TEMP_LB                  0x10
#define THERMO17_REG_RW_REMOTE_TEMP_OFFSET_HB          0x11
#define THERMO17_REG_RW_REMOTE_TEMP_OFFSET_LB          0x12
#define THERMO17_REG_RW_REMOTE_TEMP_LIMIT_H_LB         0x13
#define THERMO17_REG_RW_REMOTE_TEMP_LIMIT_L_LB         0x14
#define THERMO17_REG_R_LOCAL_TEMP_LB                   0x15
#define THERMO17_REG_RW_REMOTE_TEMP_THERM_LIMIT        0x19
#define THERMO17_REG_RW_LOCAL_TEMP_THERM_LIMIT         0x20
#define THERMO17_REG_RW_THERMO_HYSTERESIS              0x21
#define THERMO17_REG_RW_CONSECUTIVE_ALERT              0x22
#define THERMO17_REG_RW_M_FACTOR_CORRECTION            0x23
#define THERMO17_REG_RW_DIGITAL_FILTER_CTRL            0x24
#define THERMO17_REG_R_ID                              0xFE
#define THERMO17_REG_W_CFG                             0x09
#define THERMO17_REG_W_CONVERSION_RATE                 0x0A
#define THERMO17_REG_W_LOCAL_TEMP_LIMIT_H              0x0B
#define THERMO17_REG_W_LOCAL_TEMP_LIMIT_L              0x0C
#define THERMO17_REG_W_REMOTE_TEMP_LIMIT_H_HB          0x0D
#define THERMO17_REG_W_REMOTE_TEMP_LIMIT_L_HB          0x0E
#define THERMO17_REG_W_ONE_SHOT                        0x0F
/** \} */

/**
 * \defgroup temperature_macro Temperature read macro
 * \{
 */
#define THERMO17_TEMPERATURE_LOCAL                     0xAA
#define THERMO17_TEMPERATURE_REMOTE                    0xBB
#define THERMO17_ERROR                                 0x00
/** \} */

/**
 * \defgroup dev_id Device ID value
 * \{
 */
#define THERMO17_DEV_ID                                0x55
/** \} */

/**
 * \defgroup dev_status Device status register
 * \{
 */
#define THERMO17_STATUS_BUSY                           0x80
#define THERMO17_STATUS_LOCAL_HIGH_TEMP                0x40
#define THERMO17_STATUS_LOCAL_LOW_TEMP                 0x20
#define THERMO17_STATUS_REMOTE_HIGH_TEMP               0x10
#define THERMO17_STATUS_REMOTE_LOW_TEMP                0x08
#define THERMO17_STATUS_REMOTE_SENS_OPEN_CIRCUIT       0x04
#define THERMO17_STATUS_REMOTE_THERM_TIPPED            0x02
#define THERMO17_STATUS_LOCAL_THERM_TIPPED             0x01
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO17_RETVAL  uint8_t

#define THERMO17_OK           0x00
#define THERMO17_INIT_ERROR   0xFF
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

    digital_in_t an;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} thermo17_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermo17_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void thermo17_cfg_setup ( thermo17_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
THERMO17_RETVAL thermo17_init ( thermo17_t *ctx, thermo17_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg_adr      Register address.
 * @param write_data   Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void thermo17_generic_write ( thermo17_t *ctx, uint8_t reg_adr, uint8_t write_data );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg_adr      Register address.
 * 
 * @returns Returns read data
 *
 * @description This function reads data from the desired register.
 */
uint8_t thermo17_generic_read ( thermo17_t *ctx,  uint8_t reg_adr );

/**
 * @brief Function for reading temperature.
 * 
 * @param ctx          Click object.
 * @param temp_macro   Temperature macro ( THERMO17_TEMPERATURE_LOCAL or 
 *                                         THERMO17_TEMPERATURE_REMOTE ).
 * 
 * @returns Returns read data or THERMO17_ERROR if temp_macro is wrong
 *
 * @description This function reads data from the local or remote registers.
 */
float thermo17_read_temp ( thermo17_t *ctx, uint8_t temp_macro );

/**
 * @brief Checks status of int pin.
 *
 * @param ctx  Click object.
 *
 * @returns 0 or 1.
 *
 * @description This function returns the state of the int pin.
 */
uint8_t thermo17_get_int_status ( thermo17_t *ctx );

/**
 * @brief Checks status of an pin.
 *
 * @param ctx  Click object.
 *
 * @returns 0 or 1.
 *
 * @description This function returns the state of the an pin.
 */
uint8_t thermo17_get_an_status ( thermo17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO17_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
