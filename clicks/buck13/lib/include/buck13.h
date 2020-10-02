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
 * \brief This file contains API for Buck 13 Click driver.
 *
 * \addtogroup buck13 Buck 13 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK13_H
#define BUCK13_H

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

#define BUCK13_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.en    = MIKROBUS( mikrobus, MIKROBUS_AN );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK13_RETVAL  uint8_t

#define BUCK13_OK           0x00
#define BUCK13_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup buck_enable Buck enable
 * \{
 */
#define BUCK13_ENABLE         1
#define BUCK13_DISABLE        0
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

    digital_out_t en;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} buck13_t;

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

    pin_name_t en;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} buck13_cfg_t;

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
void buck13_cfg_setup ( buck13_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx    Click object.
 * @param cfg    Click configuration structure.
 * 
 * @returns      Initialization response.  
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK13_RETVAL buck13_init ( buck13_t *ctx, buck13_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Buck 13 click.
 * 
 * @note Default Configuration
 * <pre>
 * Buck mode : Disabled - BUCK13_DISABLE.
 * </pre>
 */
void buck13_default_cfg ( buck13_t *ctx );

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
void buck13_generic_transfer 
( 
    buck13_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Enable Buck13 function.
 *
 * @param ctx          Click object.
 * @param pwr_state    Enable/disable state.
 *
 * @description Enables/disables Buck13 module.
 */
void buck13_enable ( buck13_t *ctx, uint8_t pwr_state );

/**
 * @brief Get ADC function.
 *
 * @param ctx          Click object.
 *
 * @returns            Returns ADC value.         
 * @description Get adc values from the module.
 */
uint16_t buck13_get_adc( buck13_t *ctx );

/**
 * @brief Get voltage function.
 *
 * @param ctx          Click object.
 * 
 * @returns            Returns voltage value.
 * @description Get voltage value from the module.
 */
uint16_t buck13_get_voltage( buck13_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BUCK13_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
