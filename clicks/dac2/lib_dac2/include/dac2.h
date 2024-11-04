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
 * \brief This file contains API for DAC 2 Click driver.
 *
 * \addtogroup dac2 DAC 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DAC2_H
#define DAC2_H

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

#define DAC2_MAP_MIKROBUS( cfg, mikrobus )          \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );   \
   cfg.clr   = MIKROBUS( mikrobus, MIKROBUS_RST );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DAC2_RETVAL  uint8_t

#define DAC2_OK                          0x00
#define DAC2_INIT_ERROR                  0xFF
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

    digital_out_t clr;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} dac2_t;

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

    pin_name_t clr;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} dac2_cfg_t;

/** \} */ // End types group

// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 
/** \} */ // End constants group

// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


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
 * @param cfg           Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void dac2_cfg_setup ( dac2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param dac2          Click object.
 * @param cfg           Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
DAC2_RETVAL dac2_init ( dac2_t *ctx, dac2_cfg_t *cfg );

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
void dac2_generic_transfer 
( 
    dac2_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 *
 * @description This function executes default configuration for LTC2601 Click.
 */
void dac2_default_cfg ( dac2_t *ctx );

/**
 * @brief Asynchronous Clear Input function.
 *
 * @param ctx           Click object.
 *
 * @description This function clears all registers and causes the DAC voltage 
 * outputs to drop to 0V for LTC2601.
 */
void dac2_clr_dac_2_reg ( dac2_t *ctx );

/**
 * @brief Procentage generic write function.
 *
 * @param ctx           Click object.
 * @param value_pct     Required percentage of output voltage ( from 0% to 100%).
 *
 * @description This function required percentage value ( from 0% to 100% ) 
 * convert to digital input and transforms it to the output voltage 
 * from 0 to Vref [mV].
 */
void dac2_write_output_voltage_procentage ( dac2_t *ctx, uint8_t value_pct );

/**
 * @brief Data generic write function.
 *
 * @param ctx           Click object.
 * @param value_pct     Required 16-bit data of output voltage.
 *
 * @description This function required 16-bit data value ( from 0 to 65535 ) 
 * convert to digital input and transforms it to the output voltage 
 * from 0 to Vref [mV].
 */
void dac2_write_output_voltage_data ( dac2_t *ctx, uint16_t value_data );

#ifdef __cplusplus
}
#endif
#endif  // _DAC2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
