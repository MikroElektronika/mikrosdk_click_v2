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
 * \brief This file contains API for MIC33153 Click driver.
 *
 * \addtogroup mic33153 MIC33153 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MIC33153_H
#define MIC33153_H

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

#define MIC33153_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.en    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.pg    = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MIC33153_RETVAL  uint8_t

#define MIC33153_OK           0x00
#define MIC33153_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup out_mode Out Mode
 * \{
 */
#define MIC33153_OUT_ENABLE   1
#define MIC33153_OUT_DISABLE  0
/** \} */

/**
 * \defgroup voltage Voltage
 * \{
 */
#define MIC33153_MIN_VOLTAGE_800MV   0x0FFF
#define MIC33153_VOLTAGE_1000MV      0x0EC0
#define MIC33153_VOLTAGE_1500MV      0x0BE0
#define MIC33153_VOLTAGE_2000MV      0x08F0
#define MIC33153_VOLTAGE_2500MV      0x060F
#define MIC33153_VOLTAGE_3000MV      0x0330
#define MIC33153_VOLTAGE_3200MV      0x0210
#define MIC33153_MAX_VOLTAGE_3550MV  0x0000
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

    // Input pins 

    digital_in_t an;
    digital_in_t pg;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} mic33153_t;

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
    pin_name_t en;
    pin_name_t pg;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} mic33153_cfg_t;

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
void mic33153_cfg_setup ( mic33153_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mic33153 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MIC33153_RETVAL mic33153_init ( mic33153_t *ctx, mic33153_cfg_t *cfg );

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
void mic33153_generic_transfer 
( 
    mic33153_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Write DAC function.
 *
 * @param ctx          Click object.
 * @param value_dac    Value of DAC to be writen.
 *
 * @description This function writes 12-bit value to DAC and that causes that output voltage be seted on determined value.
 */
void mic33153_write_dac ( mic33153_t *ctx, const uint16_t value_dac );

/**
 * @brief Out enable function.
 *
 * @param ctx          Click object.
 * @param state        0 - disable output voltage, 1 - enable output voltage.
 *
 * @description This function enables or disables output voltage depending on the state value.
 */
void mic33153_enable_out ( mic33153_t *ctx, uint8_t state );

/**
 * @brief Power Good check function.
 *
 * @param ctx          Click object.
 * @param state        0 - disable output voltage, 1 - enable output voltage.
 *
 * @description This function hecks state of PG (INT) pin. If state is 1 that means that output voltage is above 92% of its steady
 * state voltage. If state is 0 that means that output voltage is below 86% of its steady state voltage.
 */
uint8_t mic33153_check_power_good ( mic33153_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MIC33153_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
