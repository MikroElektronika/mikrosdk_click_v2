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
 * \brief This file contains API for c3D Hall Click driver.
 *
 * \addtogroup c3dhall c3D Hall Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C3DHALL_H
#define C3DHALL_H

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

#define C3DHALL_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C3DHALL_RETVAL  uint8_t

#define C3DHALL_OK           0x00
#define C3DHALL_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C3DHALL_NO_ERRORS                                       0x0000
#define C3DHALL_F_ADCMONITOR                                    0x0004
#define C3DHALL_F_ADCSATURA                                     0x0008
#define C3DHALL_F_GAINTOOLOW                                    0x0010
#define C3DHALL_F_GAINTOOHIGH                                   0x0020
#define C3DHALL_F_NORMTOOLOW                                    0x0040
#define C3DHALL_F_FIELDTOOLOW                                   0x0080
#define C3DHALL_F_FIELDTOOHIGH                                  0x0100
#define C3DHALL_F_ROCLAMP                                       0x0200
#define C3DHALL_F_DEADZONEALPHA                                 0x0800
#define C3DHALL_F_DEADZONEBETA                                  0x8000
#define C3DHALL_MULTIPLE_ERRORS                                 0xFFFF
#define C3DHALL_START_COMMUNICATION_BYTE                        0xFF
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

} c3dhall_t;

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

} c3dhall_cfg_t;

/**
 * @brief All data structure definition.
 */
typedef struct
{
    uint16_t data_angle_a;
    uint16_t data_angle_b;
    uint16_t data_error;
    uint8_t data_sum;

} c3dhall_all_data_t;

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
void c3dhall_cfg_setup ( c3dhall_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C3DHALL_RETVAL c3dhall_init ( c3dhall_t *ctx, c3dhall_cfg_t *cfg );

/**
 * @brief Read 8 bytes data from sensor function.
 *
 * @param ctx          Click object.
 * @param block        Structure storage data.
 *
 * @description Function read 8 bytes data from MLX9033 sensor.
 */
void c3dhall_read_all_data ( c3dhall_t *ctx, c3dhall_all_data_t *all_data );

/**
 * @brief Calculate angle function.
 *
 * @param ctx          Click object.
 * @param data_angle   16-bit angle data.
 *
 * @description Function calculate angle from angle data from MLX9033 sensor.
 */
uint8_t c3dhall_calculate_angle ( c3dhall_t *ctx, uint16_t data_angle );

#ifdef __cplusplus
}
#endif
#endif  // _C3DHALL_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
