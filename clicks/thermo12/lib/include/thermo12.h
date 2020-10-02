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
 * \brief This file contains API for Thermo 12 Click driver.
 *
 * \addtogroup thermo12 Thermo 12 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO12_H
#define THERMO12_H

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
#define THERMO12_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.ct = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO12_RETVAL  uint8_t

#define THERMO12_OK           0x00
#define THERMO12_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_addr Device Address 
 * \{ 
 */
#define    THERMO12_DEVICE_ADDRESS_1      0x48
#define    THERMO12_DEVICE_ADDRESS_2      0x49
#define    THERMO12_DEVICE_ADDRESS_3      0x4A
#define    THERMO12_DEVICE_ADDRESS_4      0x4B
/** \} */

/**
 * \defgroup registers Registers 
 * \{ 
 */
#define    THERMO12_REG_TEMP_MSB          0x00
#define    THERMO12_REG_TEMP_LSB          0x01
#define    THERMO12_REG_STATUS            0x02
#define    THERMO12_REG_CONFIG            0x03
#define    THERMO12_REG_T_HIGH_SETP_MSB   0x04
#define    THERMO12_REG_T_HIGH_SETP_LSB   0x05
#define    THERMO12_REG_T_LOW_SETP_MSB    0x06
#define    THERMO12_REG_T_LOW_SETP_LSB    0x07
#define    THERMO12_REG_T_CRIT_SETP_MSB   0x08
#define    THERMO12_REG_T_CRIT_SETP_LSB   0x09
#define    THERMO12_REG_T_HYST_SETP       0x0A
#define    THERMO12_REG_ID                0x0B
#define    THERMO12_REG_SOFT_RESET        0x2F
/** \} */

/**
 * \defgroup status_register_masks Status register masks
 * \{ 
 */
#define    THERMO12_T_LOW_MASK           0x10
#define    THERMO12_T_HIGH_MASK          0x20
#define    THERMO12_T_CRIT_MASK          0x40
#define    THERMO12_RDY_MASK             0x80
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

    digital_in_t ct;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} thermo12_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t ct;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermo12_cfg_t;

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
void thermo12_cfg_setup ( thermo12_cfg_t *cfg );

/**
 * @brief           Initialization function.
 * @param thermo12  Click object.
 * @param cfg       Click configuration structure.
 * 
 * @returns         Initialization result.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMO12_RETVAL thermo12_init ( thermo12_t *ctx, thermo12_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx         Click object.
 *
 * @returns           0 - Init success.
 * @returns           1 - Init fail.
 * 
 * @description This function executes default configuration for Thermo12 click.
 */
uint8_t thermo12_default_cfg ( thermo12_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg_address  Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @returns            0 for valid number of bytes (i.e. if number of bytes does not exceed 2)
 * @returns            1 for invalid number of bytes (i.e. if number of bytes exceeds 2) 
 * 
 * @description This function writes data to the desired register.
 */
uint8_t thermo12_set ( thermo12_t *ctx, uint8_t reg_address, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg_address  Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @returns            0 for valid number of bytes (i.e. if number of bytes does not exceed 2)
 * @returns            1 for invalid number of bytes (i.e. if number of bytes exceeds 2)
 * 
 * @description This function reads data from the desired register.
 */
uint8_t thermo12_get ( thermo12_t *ctx, uint8_t reg_address, uint8_t *data_buf, uint8_t len );


/**
 * @brief Getting INT pin state
 *
 * @param ctx        Click object.
 *
 * @returns          0 if INT pin is LOW
 * @returns          1 if INT pin is HIGH
 *
 * @description This function returns INT pin state
 */
uint8_t thermo12_int_get ( thermo12_t *ctx );

/**
 * @brief Getting CS pin state
 *
 * @param ctx        Click object.
 *
 * @returns          0 if INT pin is LOW
 * @returns          1 if INT pin is HIGH
 *
 * @description This function returns CT pin state
 */
uint8_t thermo12_ct_get ( thermo12_t *ctx );


/**
 * @brief Soft reset
 *
 * @param ctx        Click object.
 *
 * @description This function issues soft reset command.
 */
void thermo12_soft_reset ( thermo12_t *ctx );

/**
 * @brief Getting temperature value
 *
 * @param ctx        Click object.
 *
 * @returns          Temperature value.
 * @description This function reads temperature registers and calculates temperature value.
 */
float thermo12_get_temperature ( thermo12_t *ctx );

/**
 * @brief Getting device status
 *
 * @param ctx       Click object.
 *
 * @returns Status register value
 *
 * @description This function returns status register value
 */
uint8_t thermo12_get_status ( thermo12_t *ctx );

/**
 * @brief Setting high threshold limit
 *
 * @param high_threshold      high threshold value
 * @param ctx                 Click object.
 * 
 * @returns                   0 for valid high threshold value (i.e. if threshold value is between -40 and 150)
 * @returns                   1 for invalid high threshold value (i.e. if threshold value is not between -40 and 150)
 *
 * @description             This function sets high threshold value
 */
uint8_t thermo12_set_high_threshold ( thermo12_t *ctx, float high_threshold );

/**
 * @brief Setting low threshold limit
 *
 * @param low_threshold       low threshold value
 * @param ctx                 Click object.
 * 
 * @returns                   0 for valid low threshold value (i.e. if threshold value is between -40 and 150)
 * @returns                   1 for invalid low threshold value (i.e. if threshold value is not between -40 and 150)
 *
 * @description               This function sets low threshold value
 */
uint8_t thermo12_set_low_threshold ( thermo12_t *ctx, float low_threshold );

/**
 * @brief Setting critical threshold limit
 * 
 * @param ctx                 Click object.
 * @param critical_threshold  critical threshold value
 *
 * @returns                   0 for valid critical threshold value (i.e. if threshold value is between -40 and 150)
 * @returns                   1 for invalid critical threshold value (i.e. if threshold value is not between -40 and 150)
 *
 * @description               This function sets critical threshold value
 */
uint8_t thermo12_set_critical_threshold ( thermo12_t *ctx, float critical_threshold );

/**
 * @brief Setting hysteresis value
 * 
 * @param ctx                 Click object.
 * @param hysteresis_value    hysteresis value
 *
 * @returns                   0 for valid hysteresis value (i.e. if hysteresis value is between 0 and 15)
 * @returns                   1 for invalid hysteresis value (i.e. if hysteresis value is not between 0 and 15)
 *
 * @description               This function sets hysteresis value.
 */
uint8_t thermo12_set_hysteresis ( thermo12_t *ctx, uint8_t hysteresis_value );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO12_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
