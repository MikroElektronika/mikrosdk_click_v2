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
 * \brief This file contains API for IrThermo  Click driver.
 *
 * \addtogroup irthermo IrThermo  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRTHERMO_H
#define IRTHERMO_H

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
#define IRTHERMO_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRTHERMO_RETVAL  uint8_t

#define IRTHERMO_OK           0x00
#define IRTHERMO_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup various_macros Various Macros
 * \{
 */
#define IRTHRM3V3_RAW_DATA_CH1   0x04
#define IRTHRM3V3_RAW_DATA_CH2   0x05
#define IRTHRM3V3_TA             0x06
#define IRTHRM3V3_TOBJ1          0x07
#define IRTHRM3V3_TOBJ2          0x08
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
    digital_in_t pwm;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} irthermo_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t pwm;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} irthermo_cfg_t;

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
void irthermo_cfg_setup ( irthermo_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRTHERMO_RETVAL irthermo_init ( irthermo_t *ctx, irthermo_cfg_t *cfg );

/**
 * @brief Reads Temperature ambient from sensor
 *
 * @param ctx Click object.
 *
 * @description Returns ambient temperature value in Celsius
 */
float irthrm3v3_get_t_ambient ( irthermo_t* ctx );

/**
 * @brief Reads Temperature object1 from sensor
 *
 * @param ctx Click object.
 *
 * @description Returns object temperature value in Celsius
 */
float irthrm3v3_get_t_object ( irthermo_t* ctx );

/**
 * @brief Generic function for reading values from RAM
 *
 * @param ctx       Click object.
 * @param address   address of register
 *
 * @description Returns 16bit value of register
 */
uint16_t irthrm3v3_read_reg ( irthermo_t* ctx, uint8_t address );



#ifdef __cplusplus
}
#endif
#endif  // _IRTHERMO_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
