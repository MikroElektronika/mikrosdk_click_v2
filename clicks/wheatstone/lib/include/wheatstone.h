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
 * \brief This file contains API for Wheatstone Click driver.
 *
 * \addtogroup wheatstone Wheatstone Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef WHEATSTONE_H
#define WHEATSTONE_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "drv_analog_in.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define WHEATSTONE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an_pin = MIKROBUS( mikrobus, MIKROBUS_AN )
 

/**
 * \defgroup error_code Error Code
 * \{
 */
#define WHEATSTONE_RETVAL  uint8_t

#define WHEATSTONE_OK           0x00
#define WHEATSTONE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup potenciometer  Potenciometer
 * \{
 */
#define WHEATSTONE_DEF_POTENCIOMETER   0xFF
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Analog data type 
 */
typedef  uint16_t wheatstone_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    digital_out_t cs;

    // Modules 

    spi_master_t spi;
    analog_in_t adc;
    pin_name_t chip_select;

} wheatstone_t;

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
    pin_name_t an_pin;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;
    
    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef 

} wheatstone_cfg_t;

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
void wheatstone_cfg_setup ( wheatstone_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param wheatstone Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
WHEATSTONE_RETVAL wheatstone_init ( wheatstone_t *ctx, wheatstone_cfg_t *cfg );

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
void wheatstone_generic_transfer 
( 
    wheatstone_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Set potentiometer ( 0 - 100k )
 *
 * @param ctx          Click object.
 * @param pot_value  Value ( 0x00 - 0xFF )
 *
 * @description This function set 8-bit wiper positions data via SPI
 * on the TPL0501 chip register.
 */
void wheatstone_set_potentiometer ( wheatstone_t *ctx, uint8_t pot_value );

/**
 * @brief Set ADC VREF.
 *
 * @param ctx          Click object.
 * @param vref voltage Reference voltage
 */
void wheatstone_set_adc_vref ( wheatstone_t *ctx, float vref );

/**
 * @brief Set ADC resolution.
 *
 * @param ctx          Click object.
 * @param res ADC resolution
 */
void wheatstone_set_adc_resolution ( wheatstone_t *ctx, float res );

/**
 * @brief Get Voltage
 *
 * @param ctx          Click object.
 * @param adc_value ADC value
 * 
 * @return voltage on the ADC ( AN ) pin
 */
float wheatstone_get_voltage ( wheatstone_t *ctx, uint16_t adc_value );

/**
 * @brief Generic read
 *
 * @param ctx          Click object.
 */
uint16_t wheatstone_generic_read ( wheatstone_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _WHEATSTONE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
