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
 * \brief This file contains API for DIGI POT 2 Click driver.
 *
 * \addtogroup digipot2 DIGI POT 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DIGIPOT2_H
#define DIGIPOT2_H

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

#define DIGIPOT2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DIGIPOT2_RETVAL  uint8_t

#define DIGIPOT2_OK           0x00
#define DIGIPOT2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup referent_voltage Referent voltage
 * \{
 */
#define DIGIPOT2_VREF_3V3           3.3
#define DIGIPOT2_VREF_5V            5.0
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

} digipot2_t;

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

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} digipot2_cfg_t;

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
void digipot2_cfg_setup ( digipot2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DIGIPOT2_RETVAL digipot2_init ( digipot2_t *ctx, digipot2_cfg_t *cfg );

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
void digipot2_generic_transfer ( digipot2_t *ctx, uint8_t *wr_buf, 
                                uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic write 8-bit data function.
 *
 * @param ctx          Click object.
 * @param command      8-bit data address command.
 * @param write_data   8-bit data to write.
 *
 * @description Function write 8-bit data via SPI
 * on the TPL0501 chip register.
 */
void digipot2_write_byte ( digipot2_t *ctx, uint8_t command, uint8_t write_data );

 /**
 * @brief Set 8-bit wiper positions.
 *
 * @param ctx                Click object.
 * @param wiper_positions    8-bit wiper positions data.
 *
 * @description Function set 8-bit wiper positions data via SPI
 * on the TPL0501 chip register.
 */
void digipot2_set_wiper_positions ( digipot2_t *ctx, uint8_t wiper_positions );

 /**
 * @brief  Convert ADC value to volatage.
 *
 * @param ctx          Click object.
 * @param value_adc    10-bit ADC value.
 *
 * @param v_ref        Voltage Reference 3.3V or 5V.
 *
 * @return
 * float voltage ( 0V - 3.3V ) or ( 0V - 5.0V ).
 *
 * @description Convert 10-bit ADC value to volatage.
 */
float digipot2_convert_output ( digipot2_t *ctx, uint16_t value_adc, float v_ref );

#ifdef __cplusplus
}
#endif
#endif  // _DIGIPOT2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
