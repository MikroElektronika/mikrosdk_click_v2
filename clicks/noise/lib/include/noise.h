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
 * \brief This file contains API for Noise Click driver.
 *
 * \addtogroup noise Noise Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NOISE_H
#define NOISE_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

#include "drv_analog_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define NOISE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NOISE_RETVAL  uint8_t

#define NOISE_OK                          0x00
#define NOISE_INIT_ERROR                  0xFF
/** \} */

/**
 * \defgroup noise_var NOISE_VAR Variables
 * \{
 */
#define NOISE_DEFAULT_COMMAND             0x01
#define NOISE_DEFAULT_THRESHOLD         0x0064
#define NOISE_DAC_A                       0x00
#define NOISE_DAC_B                       0x08
#define NOISE_VREF_UNBUFFERED             0x00
#define NOISE_VREF_BUFFERED               0x04
#define NOISE_GAIN_2X                     0x00
#define NOISE_GAIN_1X                     0x02
#define NOISE_SHDN_ENABLE                 0x00
#define NOISE_SHDN_DISABLE                0x01
/** \} */


/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Analog data type
 */
//typedef  analog_in_data_t noise_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t cs;

    // Input pins 

    digital_in_t an;
    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    // dodato
    
    analog_in_t adc;

} noise_t;

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
    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    // dodato

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef 

} noise_cfg_t;

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
void noise_cfg_setup ( noise_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param noise                         Click object.
 * @param cfg                           Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NOISE_RETVAL noise_init ( noise_t *ctx, noise_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx                          Click object.
 *
 * @description This function performs default configuration for Noise click.
 * Typically, it's setting threshold to default value. 
 */
void noise_default_cfg ( noise_t *ctx );

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
void noise_generic_transfer 
( 
    noise_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Write to Command Register
 *
 * @param ctx                          Click object.
 * @param command_and_data_bits        Command and data to send.
 *
 * @description This function writes data to click's command register.
 */
void noise_write_command_register ( noise_t *ctx, uint16_t command_and_data_bits );

/**
 * @brief Set Command Register
 *
 * @param ctx                          Click object.
 * @param configuration                Configuration.
 * @param threshold                    Threshold.
 *
 * @description This function sets command register.
 *
 * @returns 0 - success ; 1 - ( threshold value ) error
 *
 * @note
 * <pre>
 * Threshold is integer from [0, 4095] segment.
 * When measured noise level is above threshold, alarm is triggered. 
 * </pre>
 */
uint8_t noise_set_command_register ( noise_t *ctx, uint8_t configuration,
                                     uint16_t threshold );

/**
 * @brief Enable/disable click 
 *
 * @param ctx                          Click object.
 * @param state                        State to set click on.
 *
 * @description This function switches click on or off.
 */
void noise_set_state ( noise_t *ctx, uint8_t state );

/**
 * @brief Reset Click 
 *
 * @param ctx                          Click object.
 *
 * @description This function performs click reset.
 */
void noise_reset ( noise_t *ctx );

/**
 * @brief Get INT pin state 
 *
 * @param ctx                          Click object.
 *
 * @returns State of INT pin ( eighter 0 or 1 )
 *
 * @description This function gets int pin state.
 */
uint8_t noise_check_int_pin ( noise_t *ctx );

/**
 * @brief Read ADC Value
 *
 * @param ctx                          Click object.
 *
 * @returns Read ADC value
 *
 * @description This function reads value from adc.
 */
uint16_t noise_generic_read ( noise_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _NOISE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
