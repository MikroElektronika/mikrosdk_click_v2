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
 * \brief This file contains API for Voltmeter Click driver.
 *
 * \addtogroup voltmeter Voltmeter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef VOLTMETER_H
#define VOLTMETER_H

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

#define VOLTMETER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VOLTMETER_RETVAL  uint8_t

#define VOLTMETER_OK           0x00
#define VOLTMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VOLTMETER_VALUE_5_BIT                                   0x001F
#define VOLTMETER_VALUE_12_BIT                                  0x0FFF
#define VOLTMETER_VCC_5V_COEFF_0                                0
#define VOLTMETER_VCC_5V_COEFF_1                                1
#define VOLTMETER_VCC_5V_COEFF_2                                2
#define VOLTMETER_VCC_5V_COEFF_VAL                              5.6487
#define VOLTMETER_VCC_5V_COEFFICIENT_VAL                        6.1576
#define VOLTMETER_VCC_5V_COEFF_PIC32_VAL                        10.6857
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

    // Input pins 

    digital_in_t an;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} voltmeter_t;

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

    pin_name_t an;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} voltmeter_cfg_t;

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
void voltmeter_cfg_setup ( voltmeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param voltmeter Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
VOLTMETER_RETVAL voltmeter_init ( voltmeter_t *ctx, voltmeter_cfg_t *cfg );

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
void voltmeter_generic_transfer 
( 
    voltmeter_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic write the byte of the data function.
 *
 * @param ctx          Click object.
 * @param write_data   Byte of data to write.
 *
 * @description Function write the 8-bit of data to the
 * register of MCP3201 chip on Voltmeter click board.
 */void voltmeter_write_data ( voltmeter_t *ctx, uint16_t write_data );

 /**
 * @brief Generic read the byte of the data function.
 *
 * @param ctx          Click object.
 *
 * @description Function read the byte of the data from the
 * register of MCP3201 chip on Voltmeter click board.
 */uint8_t voltmeter_read_byte ( voltmeter_t *ctx );

 /**
 * @brief Generic reading 16-bit data function.
 *
 * @param ctx          Click object.
 * @param block        Transfer block structure.
 *
 * @description Function reading 16-bit data from the
 * register of MCP3201 chip on Voltmeter click board.
 */uint16_t voltmeter_read_data ( voltmeter_t *ctx );

 /**
 * @brief Calibration reading function.
 *
 * @param ctx          Click object.
 *
 * @description Function reading calibration parameter from the
 * register of MCP3201 chip on Voltmeter click board.
 */void voltmeter_calibration ( voltmeter_t *ctx );

 /**
 * @brief Voltage reading function.
 *
 * @param ctx          Click object.
 * @param coefficient  Value depends on the selected development system.
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */float voltmeter_get_voltage ( voltmeter_t *ctx, uint8_t coefficient );

 
#ifdef __cplusplus
}
#endif
#endif  // _VOLTMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
