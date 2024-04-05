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
 * \brief This file contains API for BIG 7-SEG Click driver.
 *
 * \addtogroup big7seg BIG 7-SEG Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BIG7SEG_H
#define BIG7SEG_H

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
#define BIG7SEG_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.mr    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.pwm   = MIKROBUS( mikrobus, MIKROBUS_PWM ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BIG7SEG_RETVAL  uint8_t

#define BIG7SEG_OK           0x00
#define BIG7SEG_INIT_ERROR   0xFF
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
    digital_out_t pwm;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} big7seg_t;

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
    pin_name_t pwm;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} big7seg_cfg_t;

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
void big7seg_cfg_setup ( big7seg_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param big7seg Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BIG7SEG_RETVAL big7seg_init ( big7seg_t *ctx, big7seg_cfg_t *cfg );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void big7seg_generic_transfer 
( 
    big7seg_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @breif Generic write data function
 *
 * @param ctx             Click object.
 * @param write_data      Data to write
 *
 * @description Function will write number on BIG 7-SEG display
 */
void big7seg_write_data ( big7seg_t *ctx, uint8_t write_data );

/**
 * @breif Function set BIG 7-SEG
 *
 * @param ctx          Click object.
 * 
 * @description Function set BIG 7-SEG display
 */
void big7seg_set7seg ( big7seg_t *ctx );

/**
 * @breif Function reset BIG 7-SEG
 *
 * @param ctx          Click object.
 * 
 * @description Function reset BIG 7-SEG display
 */
void big7seg_reset7seg ( big7seg_t *ctx );

/**
 * @breif Turn ON BIG 7-SEG display
 *
 * @param ctx          Click object.
 * 
 * @description Function enable BIG 7-SEG display
 */
void big7seg_display_on ( big7seg_t *ctx );

/**
 * @breif Turn OFF BIG 7-SEG display
 *
 * @param ctx          Click object.
 * 
 * @description Function disable BIG 7-SEG display
 */
void big7seg_display_off ( big7seg_t *ctx );

/**
 * @breif Function write number
 *
 * @param ctx             Click object.
 * @param display_number
 * 
 * @description Function write number on BIG 7-SEG display
 */
void big7seg_write_data_number ( big7seg_t *ctx, uint8_t display_number );

/**
 * @breif Function write character
 *
 * @param ctx            Click object.
 * @param display_char
 * 
 * @description Function write character on BIG 7-SEG display
 */
void big7seg_write_data_character ( big7seg_t *ctx, char display_char );

#ifdef __cplusplus
}
#endif
#endif  // _BIG7SEG_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
