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
 * \brief This file contains API for DAC 6 Click driver.
 *
 * \addtogroup dac6 DAC 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DAC6_H
#define DAC6_H

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

#define DAC6_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DAC6_RETVAL  uint8_t

#define DAC6_OK                             0x00
#define DAC6_INIT_ERROR                     0xFF
/** \} */

/**
 * \defgroup channel_selection Channel selection
 * \{
 */
#define DAC6_CHANNEL_A                      0x00
#define DAC6_CHANNEL_B                      0x01
#define DAC6_CHANNEL_C                      0x02
#define DAC6_CHANNEL_D                      0x03
/** \} */

/**
 * \defgroup operation_mode Operation mode
 * \{
 */
#define DAC6_WRITE_SPEC_UPDATE_NO           0x00
#define DAC6_WRITE_SPEC_UPDATE_OUTPUT       0x01
#define DAC6_WRITE_ALL_AND_UPDATE           0x02
#define DAC6_POWER_DOWN_OUTPUTS             0x03
/** \} */

/**
 * \defgroup reference_voltage_input Reference voltage input
 * \{
 */
#define DAC6_V_REF_2048                     2048
/** \} */

/**
 * \defgroup output_short_circuit_current Output short-circuit current
 * \{
 */
#define DAC6_OUTPUT_SHORT_CIRC_CURR         0x03FF
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

    digital_out_t cs;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    // Variables
    uint8_t chan;
    uint8_t op_mod;
    uint16_t v_ref;
    uint16_t set_out;

} dac6_t;

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
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} dac6_cfg_t;

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
void dac6_cfg_setup ( dac6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DAC6_RETVAL dac6_init ( dac6_t *ctx, dac6_cfg_t *cfg );

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
void dac6_generic_transfer ( dac6_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Generic write function
 *
 * @param ctx          Click object. 
 * @param wr_data      16-bit write data
 *
 * @description Sends 16-bit data to the device's input shift register.
**/
void dac6_write_data ( dac6_t *ctx, uint16_t wr_data );

/**
 * @brief Set DAC output function
 *
 * @param ctx          Click object.
 * <pre>
 * Strucrure arguments:
 * - chan     8-bit data that defines output channel
 * - op_mod   8-bit data that defines mode of operation
 * - set_out  16-bit data that defines output level
 * - v_ref    16-bit reference voltage input [ mv ]
 * </pre> 
 *
 * @description Function is used to set operation mode output channel and level.
 * @note 
 * <pre>
 * - Device's output levels range from 0 to 4095.
 * - Device's ideal output voltage can be calculated by using 
 *       the equation :  Vout = Vrefin � (set_out / 4095).
 * - It is advisable to use predefined values or to consult the datasheet.
 * </pre>
**/
float dac6_set_output ( dac6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DAC6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
