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
 * \brief This file contains API for BOOST Click driver.
 *
 * \addtogroup boost BOOST Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BOOST_H
#define BOOST_H

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

#define BOOST_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.cs2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST )
 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BOOST_RETVAL  uint8_t

#define BOOST_OK           0x00
#define BOOST_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup adc_voltage_devider    ADC Voltage Devider
 * \{
 */
#define BOOST_ADC_R7                                           15000.0
#define BOOST_ADC_R8                                           470.0
/** \} */

/**
 * \defgroup boost_click_limits     Boost Click Limits 
 * \{
 */
#define BOOST_HI_LIMIT                                         38000
#define BOOST_LO_INT_LIMIT                                     12000
#define BOOST_LO_EXT_LIMIT                                     15000
/** \} */

/**
 * \defgroup boost_power_source      Boost Power Source  
 * \{
 */
#define BOOST_INT_POWER                                        0
#define BOOST_EXT_POWER                                        1
/** \} */

/**
 * \defgroup start_command_bit      Start Command Bit 
 * \{
 */
#define BOOST_START_COMMAND                                    0x30
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

    // Output pins 

    digital_out_t cs2;
    digital_out_t en;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;
    pin_name_t an_chip_select;

} boost_t;

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
    pin_name_t en;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} boost_cfg_t;

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
void boost_cfg_setup ( boost_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BOOST_RETVAL boost_init ( boost_t *ctx, boost_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for BOOST click.
 */
void boost_default_cfg ( boost_t *ctx );

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
void boost_generic_transfer ( boost_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Generic write 14-bit data function.
 *
 * @param ctx          Click object.
 * @param write_data   12-bit write data.
 *
 * @description This function set DAC value by writing 12-bit data to the MCP4921 chip.
 */
void boost_write_byte ( boost_t *ctx, uint16_t write_data );

/**
 * @brief Generic read 22-bit of data function.
 *
 * @param ctx  Click object.
 *
 * @description This function get 22-bit data by reading ADC value from MCP3551 chip.
 */
uint32_t boost_read_byte ( boost_t *ctx );

/**
 * @brief Set configuration function.
 *
 * @param ctx          Click object.
 * @param pwr_src   * - Power Source:
 * - 0 : internal power supply;
 * - 1 : external power supply;
 *
 * @description This function set configuration of Boost click byset power source and write max DAC value of 4095 to the MCP4921 chip.
 */
void boost_set_configuration ( boost_t *ctx, uint8_t pwr_src );

/**
 * @brief Get output voltage function.
 *
 * @param ctx  Click object.
 *
 * @description This function get output voltage value from MCP3551 chip and calculate output value [ mV ].
 */
float boost_get_voltage ( boost_t *ctx );

/**
 * @brief Set desired voltage on output function.
 *
 * @param ctx  Click object.
 * @param value  12-bit desired voltage data [ mV ].
 *
 * @description This function set desired voltage on output value by write 12-bit data to the MCP4921 chip.
 */
void boost_set_voltage ( boost_t *ctx, uint16_t value );

/**
 * @brief Enable regulator function.
 *
 * @param ctx  Click object.
 *
 * @description This function enable regulator on the MIC2606 chip by set RST pin high of Boost click.
 */
void boost_enable ( boost_t *ctx );

/**
 * @brief Disable regulator function.
 *
 * @param ctx  Click object.
 *
 * @description This function disable regulator on the MIC2606 chip by set RST pin low of Boost click.
 */
void boost_disable ( boost_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BOOST_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
