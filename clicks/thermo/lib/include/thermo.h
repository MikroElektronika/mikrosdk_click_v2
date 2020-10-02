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
 * \brief This file contains API for THERMO Click driver.
 *
 * \addtogroup thermo THERMO Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO_H
#define THERMO_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define THERMO_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO_RETVAL  uint8_t

#define THERMO_OK           0x00
#define THERMO_INIT_ERROR   0xFF
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
    digital_out_t cs;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} thermo_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} thermo_cfg_t;

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
void thermo_cfg_setup ( thermo_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param thermo Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMO_RETVAL thermo_init ( thermo_t *ctx, thermo_cfg_t *cfg );

/**
 * @brief Read data from sensor function
 *
 * @param thermo Click object.
 *
 * @returns      32-bit read sensor data
 *
 * @description Function reads the 32-bit of data from the
 * MAX31855 sensor on Thermo click board.
 */
uint32_t thermo_read_data ( thermo_t* ctx );

/**
 * @brief Get thermocouple temperature function
 *
 * @param thermo Click object.
 *
 * @returns float thermocouple temperature in degree Celsius [ �C ]
 *
 * @description Function gets thermocouple temperature data from MAX31855 sensor on Thermo click board
 * and convert to float value of thermocouple temperature in degree Celsius [ �C ].
 */
float thermo_get_temperature ( thermo_t* ctx );

/**
 * @brief Get reference junction temperature function
 *
 * @param thermo Click object.
 *
 * @returns float reference junction temperature in degree Celsius [ �C ]
 *
 * @description Function get reference junction temperature data from MAX31855 sensor on Thermo click board
 * and convert to float value of reference junction temperature in degree Celsius [ �C ].
 */
float thermo_get_junction_temperature ( thermo_t* ctx );

/**
 * @brief Check fault states function
 *
 * @param thermo Click object.
 *
 * @returns
 * - 0 : OK
 * - 1 : ERROR ( when any of the SCV, SCG, or OC faults are active );
 *
 * @description Function checks fault states of MAX31855 sensor on Thermo click board.
 */
uint8_t thermo_check_fault ( thermo_t* ctx );

/**
 * @brief Check short-circuited to Vcc function
 *
 * @param thermo Click object.
 *
 * @returns
 * - 0 : OK
 * - 1 : ERROR ( when the thermocouple is short-circuited to VCC );
 *
 * @description Function check fault states of short-circuited to Vcc
 * of MAX31855 sensor on Thermo click board.
 */
uint8_t thermo_short_circuited_vcc ( thermo_t* ctx );

/**
 * @brief Check short-circuited to GND function
 *
 * @param thermo Click object.
 *
 * @returns
 * - 0 : OK
 * - 1 : ERROR ( when the thermocouple is short-circuited to GND );
 *
 * @description Function check fault states of short-circuited to GND
 * of MAX31855 sensor on Thermo click board.
 */
uint8_t thermo_short_circuited_gnd ( thermo_t* ctx );

/**
 * @brief Check connections fault function
 *
 * @param thermo Click object.
 *
 * @returns
 * - 0 : OK
 * - 1 : ERROR (  when the thermocouple is open (no connections) );
 *
 * @description Function check connections fault
 * of MAX31855 sensor on Thermo click board.
 */
uint8_t thermo_check_connections ( thermo_t* ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
