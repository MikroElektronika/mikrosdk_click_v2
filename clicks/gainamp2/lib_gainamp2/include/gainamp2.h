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
 * \brief This file contains API for GainAMP 2 Click driver.
 *
 * \addtogroup gainamp2 GainAMP 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GAINAMP2_H
#define GAINAMP2_H

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

#define GAINAMP2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.vout    = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GAINAMP2_RETVAL  uint8_t

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GAINAMP2_OK           0x00
#define GAINAMP2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup shutdown  Shutdown
 * \{
 */
#define  GAINAMP2_NOP_INS        0x00 
#define  GAINAMP2_SHUTDOWN_INS   0x20 
#define  GAINAMP2_WRITE_INS      0x40 
/** \} */

/**
 * \defgroup gainamp_ch  Gainamp Ch
 * \{
 */
#define  GAINAMP2_CH             0x01
#define  GAINAMP2_GAIN           0x00
/** \} */

/**
 * \defgroup gainamp_gain  Gainamp Gain
 * \{
 */  
#define  GAINAMP2_GAIN_1X        0x00
#define  GAINAMP2_GAIN_2X        0x01
#define  GAINAMP2_GAIN_4X        0x02
#define  GAINAMP2_GAIN_5X        0x03
#define  GAINAMP2_GAIN_8X        0x04
#define  GAINAMP2_GAIN_10X       0x05
#define  GAINAMP2_GAIN_16X       0x06
#define  GAINAMP2_GAIN_32X       0x07
/** \} */

/**
 * \defgroup gainamp2  Gainamp2
 * \{
 */
#define  GAINAMP2_CH0            0x00
#define  GAINAMP2_CH1            0x01
#define  GAINAMP2_CH2            0x02
#define  GAINAMP2_CH3            0x03
#define  GAINAMP2_CH4            0x04
#define  GAINAMP2_CH5            0x05
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
    analog_in_t  adc;  
    
    float vref; 

} gainamp2_t;

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

    pin_name_t vout;

    // static variable 

    analog_in_resolution_t  resolution;    
    float  vref;                          
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} gainamp2_cfg_t;

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
void gainamp2_cfg_setup ( gainamp2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gainamp2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GAINAMP2_RETVAL gainamp2_init ( gainamp2_t *ctx, gainamp2_cfg_t *cfg );

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
void gainamp2_generic_transfer ( gainamp2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Send Command
 *
 * @param ctx          Click object.
 * @param instruction 
 * @param input 
 *
 * Function setup amplifier according to provided command.
 */
void gainamp2_write_command( gainamp2_t *ctx, uint8_t instruction, uint8_t input );

/**
 * @brief Set the channel gain.
 *
 * @param ctx  Click object.
 * @param channel
 * @param gain
 *
 * @description This function sets the channel gain.
 */
void gainamp2_set_channel_gain ( gainamp2_t *ctx, uint8_t channel, uint8_t gain );

/**
 * @brief Return voltage measured from OUT pin.
 *
 * @param ctx  Click object.
 *
 * @description This function returns voltage measured from OUT pin.
 */
float gainamp2_get_voltage ( gainamp2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _GAINAMP2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
