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
 * \brief This file contains API for Temp Log 6 Click driver.
 *
 * \addtogroup templog6 Temp Log 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPLOG6_H
#define TEMPLOG6_H

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
#define TEMPLOG6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPLOG6_RETVAL  uint8_t

#define TEMPLOG6_OK           0x00
#define TEMPLOG6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define TEMPLOG6_REG_LOCAL_TEMPERATURE              0x00
#define TEMPLOG6_REG_REMOTE_TEMPERATURE             0x01
#define TEMPLOG6_REG_STATUS                         0x02
#define TEMPLOG6_REG_RD_CONFIGURATION               0x03
#define TEMPLOG6_REG_RD_LOCAL_HIGH_LIMIT            0x05
#define TEMPLOG6_REG_RD_REMOTE_HIGH_LIMIT           0x07
#define TEMPLOG6_REG_WR_CONFIGURATION               0x09
#define TEMPLOG6_REG_WR_LOCAL_HIGH_LIMIT            0x0B
#define TEMPLOG6_REG_WR_REMOTE_HIGH_LIMIT           0x0D
#define TEMPLOG6_REG_SINGLE_SHOT                    0x0F
#define TEMPLOG6_REG_REMOTE_EXTENDED_TEMP           0x10
#define TEMPLOG6_REG_INTERNAL_EXTENDED_TEMP         0x11
#define TEMPLOG6_REG_MANUFACTURER_ID                0xFE
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define TEMPLOG6_CFG_ALERT_OFF                      0x80
#define TEMPLOG6_CFG_ALERT_ON                       0x00
#define TEMPLOG6_CFG_STANDBY_MODE                   0x40
#define TEMPLOG6_CFG_NORMAL_MODE                    0x00
#define TEMPLOG6_CFG_LOCAL_MEASUREMENT_OFF          0x20
#define TEMPLOG6_CFG_LOCAL_MEASUREMENT_ON           0x00
#define TEMPLOG6_CFG_ALERT_1_FAULT                  0x00
#define TEMPLOG6_CFG_ALERT_2_FAULT                  0x10
 
#define TEMPLOG6_DEVICE_SLAVE_ADDRESS               0x4A
#define TEMPLOG6_MANUFACTURER_ID                    0x4D
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} templog6_t;

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

} templog6_cfg_t;

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
void templog6_cfg_setup ( templog6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPLOG6_RETVAL templog6_init ( templog6_t *ctx, templog6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Temp Log 6 click.
 */
void templog6_default_cfg ( templog6_t *ctx );

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
void templog6_generic_write ( templog6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void templog6_generic_read ( templog6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write one byte function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf         Data to be written.
 *
 * @description This function reads one byte of data from the desired register.
 */
void templog6_write_byte ( templog6_t *ctx, uint8_t reg, uint8_t data_buf );

/**
 * @brief Read one byte function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads one byte of data from the desired register.
 */
uint8_t templog6_read_byte ( templog6_t *ctx, uint8_t reg );

/**
 * @brief Gets interrupt.
 *
 * @param ctx          Click object.
 *
 * @description This function gets the interrupt.
 */
uint8_t templog6_get_interrupt ( templog6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPLOG6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
