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
 * \brief This file contains API for LLC SPI Click driver.
 *
 * \addtogroup llcspi LLC SPI Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LLCSPI_H
#define LLCSPI_H

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

#define LLCSPI_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LLCSPI_RETVAL  uint8_t

#define LLCSPI_OK           0x00
#define LLCSPI_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup null_value  NULL value
 * \{
 */
#define NULL     0
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
    // Modules 

    spi_master_t spi;

} llcspi_t;

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

    hal_spi_speed_t spi_speed;
    hal_spi_mode_t spi_mode;

} llcspi_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void llcspi_cfg_setup ( llcspi_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param llcspi Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
LLCSPI_RETVAL llcspi_init ( llcspi_t *ctx, llcspi_cfg_t *cfg );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param block        Transfer block structure.
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void llcspi_generic_transfer ( llcspi_t *ctx, spi_master_transfer_data_t *block );

/**
 * @brief Function for set CS pin state
 *
 * @param ctx              Click object.
 * @param state            CS pin state
 */
void spillc_set_cs_pin ( llcspi_t *ctx, uint8_t state);

/**
 * @brief LLC SPI write
 *
 * @param ctx               Click object.
 * @param p_buf             pointer to data buffer
 * @param n_bytes           number of bytes for writing
 *
 * @description Function executes write sequence of n bytes.
 *
 * @note
 * This function have not using CS pin.
 */
void spillc_generic_write ( llcspi_t *ctx, uint8_t *p_buf, uint16_t n_bytes );

/**
 * @brief LLC SPI read
 *
 * @param ctx              Click object.
 * @param p_buf            pointer to data buffer
 * @param n_bytes          number of bytes for writing
 *
 * @description Function executes read sequence of n bytes.
 *
 * @note
 * This function should not use CS pin.
 */
void spillc_generic_read ( llcspi_t *ctx, uint8_t *p_buf, uint16_t n_bytes );

#ifdef __cplusplus
}
#endif
#endif  // _LLCSPI_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
