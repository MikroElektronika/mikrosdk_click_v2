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
 * \brief This file contains API for LDC 1000 Click driver.
 *
 * \addtogroup ldc1000 LDC 1000 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LDC1000_H
#define LDC1000_H

#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "math.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define LDC1000_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LDC1000_RETVAL  uint8_t

#define LDC1000_OK           0x00
#define LDC1000_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_map Register Map
 * \{
 */
#define LDC1000_CMD_ID            0x00
#define LDC1000_CMD_RPMAX         0x01
#define LDC1000_CMD_RPMIN         0x02
#define LDC1000_CMD_SENSORFREQ    0x03
#define LDC1000_CMD_LDCCONFIG     0x04
#define LDC1000_CMD_CLKCONFIG     0x05
#define LDC1000_CMD_THRESHILSB    0x06
#define LDC1000_CMD_THRESHIMSB    0x07
#define LDC1000_CMD_THRESLOLSB    0x08
#define LDC1000_CMD_THRESLOMSB    0x09
#define LDC1000_CMD_INTCONFIG     0x0A
#define LDC1000_CMD_PWRCONFIG     0x0B
#define LDC1000_CMD_STATUS        0x20
#define LDC1000_CMD_PROXLSB       0x21
#define LDC1000_CMD_PROXMSB       0x22
#define LDC1000_CMD_FREQCTRLSB    0x23
#define LDC1000_CMD_FREQCTRMID    0x24
#define LDC1000_CMD_FREQCTRMSB    0x25
/** \} */

/**
 * \defgroup constants Constants
 * \{
 */
#define LDC1000_RPMAX_38_785K             0x11
#define LDC1000_RPMIN_2_39K               0x3B
#define LDC1000_SENSORFREQ_N217_F20       0xD9
#define LDC1000_LDCCONFIG_A2V_T6144       0x0F
#define LDC1000_CLKCONFIG_EC_ET_ENABLE    0x02
#define LDC1000_PWRCONFIG_ACTIVE_MODE     0x01
#define LDC1000_CMD_SPI_READ              0x80
#define LDC1000_SENSITIVITY               100
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

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} ldc1000_t;

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

    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} ldc1000_cfg_t;

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
void ldc1000_cfg_setup ( ldc1000_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ldc1000 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LDC1000_RETVAL ldc1000_init ( ldc1000_t *ctx, ldc1000_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for LDC 1000 click.
 */
void ldc1000_default_cfg ( ldc1000_t *ctx );

/**
 * @brief Byte write function.
 *
 * @param ctx       Click object.
 * @param address   Register address.
 * @param input_data      Data byte.
 *
 * @description This function writes 1 byte of data to the specified register address.
 */
void ldc1000_write_byte ( ldc1000_t *ctx, uint8_t address, uint8_t input_data );

/**
 * @brief Byte read function.
 *
 * @param ctx       Click object.
 * @param address   Register address.
 *
 * @description This function reads 1 byte of data from the specified register address.
 */
uint8_t ldc1000_read_byte ( ldc1000_t *ctx, uint8_t address );

/**
 * @brief Get proximity data function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads the proximity data.
 */
uint16_t ldc1000_get_proximity_data ( ldc1000_t *ctx );

/**
 * @brief Get inductance data function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads the inductance data.
 */
float ldc1000_get_inductance_data ( ldc1000_t *ctx );

/**
 * @brief Get interrupt pin input function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads the input voltage from the INT pin.
 */
uint8_t ldc1000_get_int_input ( ldc1000_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LDC1000_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
