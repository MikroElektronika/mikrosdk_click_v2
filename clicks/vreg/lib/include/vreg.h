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
 * \brief This file contains API for VREG Click driver.
 *
 * \addtogroup vreg VREG Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef VREG_H
#define VREG_H

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

#define VREG_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   //cfg.cs2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   //cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   //cfg.sw = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   //cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VREG_RETVAL  uint8_t

#define VREG_OK           0x00
#define VREG_INIT_ERROR   0xFF
/** \} */

#define VREG_CHANNEL_0                                             0x00
#define VREG_CHANNEL_1                                             0x01
#define VREG_CHANNEL_2                                             0x02
#define VREG_CHANNEL_3                                             0x03
#define VREG_SINGLE_DIFFERENTIAL                                   0x00
#define VREG_SINGLE_ENDED                                          0x02
#define VREG_START_BIT                                             0x04

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
    digital_out_t cs2;
    digital_out_t sw;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} vreg_t;

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

    pin_name_t cs2;
    pin_name_t sw;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} vreg_cfg_t;

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
void vreg_cfg_setup ( vreg_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param vreg Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
VREG_RETVAL vreg_init ( vreg_t *ctx, vreg_cfg_t *cfg );

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
void vreg_generic_transfer 
( 
    vreg_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Get ADC value function.
 *
 * @param ctx          Click object.
 * @param channel  designated channel 
 *
 * @returns 
 * 12-bit ADC value reading from designated channel
 *
 * @description This function reads 2-bit ADC value from designated channel
 * of MCP3204 4-Channel 12-Bit A/D Converters on VREG click board.
**/
uint16_t vreg_get_adc ( vreg_t *ctx, uint8_t channel );

/**
 * @brief Set output voltage function.
 *
 * @param ctx          Click object.
 * @param value_dac 12-bit DAC value
 *
 * @description This function set DAC increments 12-bit data ( 0..4095 ) --> output voltage ( 0..Vref [mV] )
 * of 12-Bit Voltage Output Digital-to-Analog Converter on VREG click board.
**/
void vreg_set_out_voltage ( vreg_t *ctx, uint16_t value_dac );

/**
 * @brief Set output voltage procentage function.
 *
 * @param ctx          Click object.
 * @param value_dac_pct 8-bit data procentage value ( 0..100 [%] ) 
 *
 * @description This function set DAC increments procentage ( 0..100 [%] ) --> output voltage ( 0..Vref [mV] )
 * of 12-Bit Voltage Output Digital-to-Analog Converter on VREG click board.
**/
void vreg_set_output_voltage_procentage ( vreg_t *ctx, uint8_t value_dac_pct );

/**
 * @brief Start the measuring function
 *
 * @description This function start the measuring by
 * set state of PWM pin of VREG click board.
**/
void vreg_start_measuring ( vreg_t *ctx );

/**
 * @brief Stop the measuring function
 *
 * @param ctx          Click object.
 * 
 * @description This function Function stop the measuring by
 * clear state of PWM pin of VREG click board.
**/
void vreg_stop_measuring ( vreg_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _VREG_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
