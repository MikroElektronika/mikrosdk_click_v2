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
 * \brief This file contains API for Vacuum Click driver.
 *
 * \addtogroup vacuum Vacuum Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef VACCUM_H
#define VACCUM_H

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
#define VACCUM_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VACCUM_RETVAL  uint8_t

#define VACCUM_OK           0x00
#define VACCUM_INIT_ERROR   0xFF
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

    digital_out_t an;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    uint16_t pressure;

} vacuum_t;

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
  
    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} vacuum_cfg_t;

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
void vacuum_cfg_setup ( vacuum_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
VACCUM_RETVAL vacuum_init ( vacuum_t *ctx, vacuum_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Vacuum click.
 */
void vacuum_default_cfg ( vacuum_t *ctx );

/**
 * @brief Function for reads 12 bit ADC data.
 * 
 * @param ctx          Click object.
 *
 * @description This function reads data.
 */
uint16_t vacuum_read_data ( vacuum_t *ctx );

/**
 * @brief Voltage reading function.
 * 
 * @param ctx          Click object.
 *
 * @description This function gets voltage.
 */
float vacuum_get_voltage ( vacuum_t *ctx );

/**
 * @brief Function for converting ADC value to pressure data.
 * 
 * @param ctx          Click object.
 *
 * @description This function gets pressure.
 */
float vacuum_get_pressure ( vacuum_t *ctx );

/**
 * @brief Function for converting ADC value to percentage of Vacuum.
 * 
 * @param ctx          Click object.
 *
 * @description This function gets percentage of vacuum.
 */
float vacuum_get_percentage_of_vacuum ( vacuum_t *ctx );

/**
 * @brief Sensor calibration.
 * 
 * @param ctx          Click object.
 *
 * @description This function sensor calibration.
 */
void vacuum_calibration ( vacuum_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _VACCUM_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
