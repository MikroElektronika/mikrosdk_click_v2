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
 * \brief This file contains API for Magnetic Rotary Click driver.
 *
 * \addtogroup magneticrotary Magnetic Rotary Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MAGNETICROTARY_H
#define MAGNETICROTARY_H

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

#define T_MAGNROTARY_P    const uint8_t*

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define MAGNETICROTARY_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MAGNETICROTARY_RETVAL  uint8_t

#define MAGNETICROTARY_OK           0x00
#define MAGNETICROTARY_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define MAGNROTARY_CHA_POS_GND_NEG             0x80
#define MAGNROTARY_CHB_POS_GND_NEG             0xC0
#define MAGNROTARY_CHA_POS_CHB_NEG             0x00
#define MAGNROTARY_CHB_POS_CHA_NEG             0x40
/** \} */

/**
 * \defgroup  data_order Data Order
 * \{
 */
#define MAGNROTARY_MSB_LSB_ORDER               0x00
#define MAGNROTARY_MSB_ZEROS_ORDER             0x20
/** \} */

/**
 * \defgroup  vdd_value Vdd Value
 * \{
 */
#define MAGNROTARY_VDD_3V3                     3298
#define MAGNROTARY_VDD_5V                      4960
/** \} */

/**
 * \defgroup  other_macros Other Macros
 * \{
 */
#define  MAGNROTARY_START_BYTE                 0x01
#define  MAGNROTARY_DUMMY_BYTE                 0x00
#define  MAGNROTARY_CMD_MASK                   0xE0
#define  MAGNROTARY_ADC_RESOLUTION             4096
#define  MAGNROTARY_SIGN_BIT                   0x0800
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

} magneticrotary_t;

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

} magneticrotary_cfg_t;

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
void magneticrotary_cfg_setup ( magneticrotary_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param magneticrotary Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MAGNETICROTARY_RETVAL magneticrotary_init ( magneticrotary_t *ctx, magneticrotary_cfg_t *cfg );

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
void magneticrotary_generic_transfer 
( 
    magneticrotary_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief ADC Output Voltage Get function
 *
 * @param ctx          Click object.
 * @param cmd_byte     Settings for AD conversion.
 * @param pwr_volt     Power voltage value selection (millivolts).
 *
 * @returns ADC output voltage value
 *
 * @description This function returns ADC voltage value calculated to millivolts, depending on 
 * the VDD (power) voltage selection.
 */
uint16_t magnrotary_out_volt_adc ( magneticrotary_t *ctx, uint8_t cmd_byte, uint16_t pwr_volt );

 /**
 * @brief ADC Result Read function
 *
 * @param ctx         Click object.
 * @param cmnd_byte   Settings for AD conversion.
 *
 * @returns Result of conversion
 *
 * @description This function returns a 12bit result of AD conversion.
 */
uint16_t magnrotary_read_adc ( magneticrotary_t *ctx, uint8_t cmnd_byte );

/**
 * @brief Magnetic Field Angle Get function
 *
 * @param ctx          Click object.
 * @param cmd_byte     Settings for AD conversion.
 *
 * @returns Magnetic field angle
 *
 * @description This function returns a magnetic field angle calculated to degrees, in the range 
 * from -90 to 90 degrees.
 */
double magnrotary_get_field_angle  ( magneticrotary_t *ctx, uint8_t cmd_byte );


#ifdef __cplusplus
}
#endif
#endif  // _MAGNETICROTARY_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
