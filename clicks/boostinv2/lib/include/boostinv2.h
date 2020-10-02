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
 * \brief This file contains API for Boost-inv 2 Click driver.
 *
 * \addtogroup boostinv2 Boost-inv 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BOOSTONV2_H
#define BOOSTONV2_H

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

#define BOOSTONV2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.en = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.csn = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.psm = MIKROBUS( mikrobus, MIKROBUS_PWM ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BOOSTONV2_RETVAL  uint8_t

#define BOOSTONV2_OK           0x00
#define BOOSTONV2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup positive_output_voltage Positive Output Voltage
 */
#define BOOSTINV2_POS_VOUT_5V   0x7FFF
#define BOOSTINV2_POS_VOUT_6V   0x7B00
#define BOOSTINV2_POS_VOUT_7V   0x7A20
#define BOOSTINV2_POS_VOUT_8V   0x7950
#define BOOSTINV2_POS_VOUT_9V   0x7870
#define BOOSTINV2_POS_VOUT_10V  0x7790
#define BOOSTINV2_POS_VOUT_11V  0x76B0
#define BOOSTINV2_POS_VOUT_12V  0x75E0
#define BOOSTINV2_POS_VOUT_13V  0x7500
#define BOOSTINV2_POS_VOUT_14V  0x7420
#define BOOSTINV2_POS_VOUT_15V  0x7340
/** \} */

/**
 * \defgroup negative_output_voltage Negative Output Voltage
 * \{
 */
#define BOOSTINV2_NEG_VOUT_5V    0x79A2
#define BOOSTINV2_NEG_VOUT_6V    0x7900
#define BOOSTINV2_NEG_VOUT_7V    0x786A
#define BOOSTINV2_NEG_VOUT_8V    0x77D0
#define BOOSTINV2_NEG_VOUT_9V    0x7744
#define BOOSTINV2_NEG_VOUT_10V   0x76B0
#define BOOSTINV2_NEG_VOUT_11V   0x7630
#define BOOSTINV2_NEG_VOUT_12V   0x75B2
#define BOOSTINV2_NEG_VOUT_13V   0x7530
#define BOOSTINV2_NEG_VOUT_14V   0x74B0
#define BOOSTINV2_NEG_VOUT_15V   0x7474
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
    digital_out_t csn;
    digital_out_t psm;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} boostinv2_t;

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
    pin_name_t csn;
    pin_name_t psm;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} boostinv2_cfg_t;

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
void boostinv2_cfg_setup ( boostinv2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param boostinv2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BOOSTONV2_RETVAL boostinv2_init ( boostinv2_t *ctx, boostinv2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Boost-inv 2 click.
 */
void boostinv2_default_cfg ( boostinv2_t *ctx );

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
void boostinv2_generic_transfer 
( 
    boostinv2_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Enable analog pin.
 *
 * @param ctx          Click object.
 *
 * @description Enables analog pin for 200ms.
 */
void boostinv2_enable ( boostinv2_t *ctx );

/**
 * @brief Sets postive voltage.
 *
 * @param ctx          Click object.
 * @param volatage     uint16_t
 *
 * @description Sets positive voltage via SPI communication..
 */
void boostinv2_set_positive_voltage ( boostinv2_t *ctx, uint16_t voltage );

/**
 * @brief Sets negative voltage.
 *
 * @param ctx          Click object.
 * @param volatage     uint16_t.
 *
 * @description Sets negative voltage via SPI communication..
 */
void boostinv2_set_negative_voltage ( boostinv2_t *ctx, uint16_t voltage );

/**
 * @brief Sets PSN depending on input state.
 *
 * @param ctx          Click object.
 * @param state        uint8_t.
 *
 * @description Sets psn pin on high or low depending on input.
 */
void boostinv2_set_psn (  boostinv2_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _BOOSTONV2_H_


/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
