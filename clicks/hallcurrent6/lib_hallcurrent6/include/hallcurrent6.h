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
 * \brief This file contains API for Hall Current 6 Click driver.
 *
 * \addtogroup hallcurrent6 Hall Current 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HALLCURRENT6_H
#define HALLCURRENT6_H

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
#define HALLCURRENT6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HALLCURRENT6_RETVAL  uint8_t

#define HALLCURRENT6_OK           0x00
#define HALLCURRENT6_INIT_ERROR   0xFF
/** \} */


/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} hallcurrent6_t;

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

} hallcurrent6_cfg_t;

/** \} */ // End types group

 
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
void hallcurrent6_cfg_setup ( hallcurrent6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx              Click object.
 * @param cfg              Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HALLCURRENT6_RETVAL hallcurrent6_init ( hallcurrent6_t *ctx, hallcurrent6_cfg_t *cfg );

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
void hallcurrent6_generic_write ( hallcurrent6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void hallcurrent6_generic_read ( hallcurrent6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read 
 *
 * @description This function writes data from the desired register.
 */             
void hallcurrent6_generic_write ( hallcurrent6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Reads ADC current data
 *
 * @param       (12 bits) adc value
 * @param ctx   Click object.
 *
 * @description The value of 2065 is 0A
 */             
uint16_t hallcurrent6_read_data ( hallcurrent6_t *ctx );

/**
 * @brief Reads current data
 *
 * @param Current      data in [mA]
 * @param ctx          Click object.
 * 
 * @description Bipolar current sensor -- nominal 400mV/A or 5A full scale
 */             
float hallcurrent6_get_current ( hallcurrent6_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _HALLCURRENT6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
