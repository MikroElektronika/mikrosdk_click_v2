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
 * \brief This file contains API for Buck 12 Click driver.
 *
 * \addtogroup buck12 Buck 12 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK12_H
#define BUCK12_H

#include "drv_digital_out.h"
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

#define BUCK12_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.en    = MIKROBUS( mikrobus, MIKROBUS_RST ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK12_RETVAL  uint8_t

#define BUCK12_OK               0x00
#define BUCK12_INIT_ERROR       0xFF
/** \} */

/**
 * \defgroup buck control Buck Control
 * \{
 */
#define BUCK12_ENABLE           0x01
#define BUCK12_DISABLE          0x00
/** \} */

/**
 * \defgroup voltage Voltage
 * \{
 */
#define BUCK12_INPUT_VOLTAGE    0x02
#define BUCK12_OUTPUT_VOLTAGE   0x03
/** \} */

/**
 * \defgroup channels Channels
 * \{
 */
#define BUCK12_CHANNEL_0        0xA0
#define BUCK12_CHANNEL_1        0xE0
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

    spi_master_t spi;
    pin_name_t chip_select;

} buck12_t;

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

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} buck12_cfg_t;

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
void buck12_cfg_setup ( buck12_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buck12 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK12_RETVAL buck12_init ( buck12_t *ctx, buck12_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Buck 12 click.
 */
void buck12_default_cfg ( buck12_t *ctx );

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
void buck12_generic_transfer 
( 
    buck12_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Function for enable or disable device.
 *
 * @param ctx          Click object.
 * @param ctrl         Disable or enable device.
 *
 * @description This function for enable or disable device.
 */
void buck12_control ( buck12_t *ctx, uint8_t ctrl );

/**
 * @brief Function for read ADC on the channel.
 *
 * @param ctx          Click object.
 * @param channel      Select channel (0 or 1).
 *
 * @description This function reads ADC on the channel.
 */
uint16_t buck12_get_channel_adc ( buck12_t *ctx, uint8_t channel );

/**
 * @brief Function for get Voltage.
 *
 * @param ctx            Click object.
 * @param select_volt    Select voltage.
 *
 * @description This function gets Voltage.
 */
float buck12_get_voltage ( buck12_t *ctx, uint8_t select_volt );

#ifdef __cplusplus
}
#endif
#endif  // _BUCK12_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
