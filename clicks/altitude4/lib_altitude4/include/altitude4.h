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
 * \brief This file contains API for Altitude 4 Click driver.
 *
 * \addtogroup altitude4 Altitude 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ALTITUDE4_H
#define ALTITUDE4_H

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
#define ALTITUDE4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ALTITUDE4_RETVAL  uint8_t

#define ALTITUDE4_OK           0x00
#define ALTITUDE4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup cfg_reg Configuration & Registers
 * \{
 */
#define ALTITUDE4_SLAVE_ADDRESS                    0x27

#define ALTITUDE4_START_CMD_MODE                   0xA9
#define ALTITUDE4_EXIT_CMD_MODE                    0xA8
#define ALTITUDE4_INC_MEM_PAGE_CNT                 0x5E
#define ALTITUDE4_CREATE_MEM_PAGE_CHECKSUM         0xAA
#define ALTITUDE4_SENS_DATA                        0xAC
/** \} */


#define FRNDINT( x )   ( ( double ) ( long ) ( x ) )

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Sensor object definition.
 */
 typedef struct
 {
    float pressure;
    float temperature;
    float altitude;

 } altitude4_sensor_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{   
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} altitude4_t;

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

} altitude4_cfg_t;

/**
 * @brief Floating point union definition.
 */
union both
{
    struct flt
    {
        unsigned char   mant[ 2 ];
        unsigned        hmant : 7;
        unsigned        exp : 8;
        unsigned        sign : 1;

    } flt;

    double fl;
};

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
void altitude4_cfg_setup ( altitude4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param altitude4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ALTITUDE4_RETVAL altitude4_init ( altitude4_t *ctx, altitude4_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg      Register address.
 * @param r_buf    Read buffer.
 * @param len      Read data size.
 *
 * @description This function stores the len amount of data into the r_buf. The data is read from
 *              the address reg. 
 */
void altitude4_generic_read ( altitude4_t *ctx, uint8_t reg, uint8_t *r_buf, uint8_t len );

/**
 * @brief Generic write function.
 *
 * @param ctx      Click object.
 * @param reg      Register address.
 * @param w_buf    Write buffer.
 * @param len      Read data size.
 *
 * @description This function writes the len amount of data from the w_buf to the address reg. 
 */
void altitude4_generic_write ( altitude4_t *ctx, uint8_t reg, uint8_t *w_buf, uint8_t len );

/**
 * @brief Read sensor function.
 *
 * @param ctx          Click object.
 * @param sens_data    Sensor data object.
 *
 * @description This function acquires sensor data from the click module and stores it in the
 *              sensor data object. 
 */
uint8_t altitude4_read_sensor ( altitude4_t *ctx, altitude4_sensor_t *sens_data );

#ifdef __cplusplus
}
#endif
#endif  // _ALTITUDE4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
