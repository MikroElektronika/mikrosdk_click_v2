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
 * \brief This file contains API for Buck 5 Click driver.
 *
 * \addtogroup buck5 Buck 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK5_H
#define BUCK5_H

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

#define BUCK5_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.en    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.syn   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK5_RETVAL  uint8_t

#define BUCK5_OK           0x00
#define BUCK5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup variables Variables
 * \{
 */
#define BUCK5_VOLTAGE_1000mV    0x00
#define BUCK5_VOLTAGE_1500mV    0x11
#define BUCK5_VOLTAGE_2000mV    0x24
#define BUCK5_VOLTAGE_2500mV    0x39
#define BUCK5_VOLTAGE_3000mV    0x50
#define BUCK5_VOLTAGE_3500mV    0x6E
#define BUCK5_VOLTAGE_4000mV    0x8C
#define BUCK5_VOLTAGE_4500mV    0xB7
#define BUCK5_VOLTAGE_5000mV    0xE1

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

    // Output pins 

    digital_out_t en;
    digital_out_t rst;

    // Input pins 

    digital_in_t syn;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} buck5_t;

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
    pin_name_t rst;
    pin_name_t syn;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} buck5_cfg_t;

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
void buck5_cfg_setup ( buck5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK5_RETVAL buck5_init ( buck5_t *ctx, buck5_cfg_t *cfg );

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
void buck5_generic_transfer 
( 
    buck5_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Functions for power ON chip
 *
 * @param ctx          Click object.
 *
 * @description This function wake up the chip.
 */
void buck5_power_on ( buck5_t *ctx );

/**
 * @brief Functions for reset chip
 *
 * @param ctx          Click object.
 *
 * @description This function reset the chip.
 */
void buck5_reset ( buck5_t *ctx );

/**
 * @brief Functions for settings maximum output voltage
 *
 * @param ctx          Click object. 
 * @param voltage      Maximum output voltages to be sets
 *
 * @description Maximum output voltage is 5.5V (255 set value), 
 *              and minimum output voltage is 1V (0 set value).
 */
void buck5_set_output_voltage ( buck5_t *ctx, uint8_t voltage );

#ifdef __cplusplus
}
#endif
#endif  // _BUCK5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
