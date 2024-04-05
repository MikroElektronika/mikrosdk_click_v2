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
 * \brief This file contains API for Led ring R  Click driver.
 *
 * \addtogroup ledringr Led ring R  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LEDRINGR_H
#define LEDRINGR_H

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

#define LEDRINGR_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.mr = MIKROBUS( mikrobus, MIKROBUS_RST ); 
   
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LEDRINGR_RETVAL  uint8_t

#define LEDRINGR_OK           0x00
#define LEDRINGR_INIT_ERROR   0xFF
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

    digital_out_t mr;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} ledringr_t;

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

    // Additional gpio pins 

    pin_name_t mr;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} ledringr_cfg_t;

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
void ledringr_cfg_setup ( ledringr_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ledringr Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LEDRINGR_RETVAL ledringr_init ( ledringr_t *ctx, ledringr_cfg_t *cfg );

/**
 * @brief Transfer data function.
 *
 * @param ctx        Click object.
 * @param write_buf  Write data.
 * @param wbuf_size   Buffer size.
 * @param read_buf   Read buffer.  
 * @param rbuf_size   Buffer size.
 * 
 * @description This function transfers data to/from the click module.
 */
void ledringr_transfer_data 
(   
    ledringr_t *ctx, 
    uint8_t *write_buf,
    uint16_t wbuf_size,
    uint8_t *read_buf,
    uint16_t rbuf_size
);

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_to_write        Data to write.
 *
 * @description This function turn On led by data.
 */
void ledringr_write_data ( ledringr_t *ctx, uint32_t data_to_write );

/**
 * @brief Turn On LED by position.
 *
 * @param ctx          Click object.
 * @param led_position        Led position.
 *
 * @description Function turn On LED by position.
 */
void ledringr_turn_on_led ( ledringr_t *ctx, uint8_t led_position );

/**
 * @brief Set led.
 *
 * @param ctx          Click object.
 *
 * @description Function sets led's to standby
 */
void ledringr_led_ring_set ( ledringr_t *ctx );

/**
 * @brief Set led.
 *
 * @param ctx          Click object.
 *
 * @description Function sets led's to standby
 */
void ledringr_led_ring_reset ( ledringr_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LEDRINGR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
