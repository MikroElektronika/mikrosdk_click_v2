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
 * \brief This file contains API for Pressure 2 Click driver.
 *
 * \addtogroup pressure2 Pressure 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE2_H
#define PRESSURE2_H

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

#define PRESSURE2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE2_OK                0
#define PRESSURE2_ERROR            -1
/** \} */

/**
 * \defgroup command_registers Command registers
 * \{
 */
#define PRESSURE2_CMD_RESET         0x1E     // ADC reset command
#define PRESSURE2_CMD_ADC_READ      0x00     // ADC read command
#define PRESSURE2_CMD_ADC_CONV      0x40     // ADC conversion command
#define PRESSURE2_CMD_ADC_D1        0x00     // ADC D1 conversion
#define PRESSURE2_CMD_ADC_D2        0x10     // ADC D2 conversion
#define PRESSURE2_CMD_ADC_256       0x00     // ADC OSR=256
#define PRESSURE2_CMD_ADC_512       0x02     // ADC OSR=512
#define PRESSURE2_CMD_ADC_1024      0x04     // ADC OSR=1024
#define PRESSURE2_CMD_ADC_2048      0x06     // ADC OSR=2056
#define PRESSURE2_CMD_ADC_4096      0x08     // ADC OSR=4096
#define PRESSURE2_CMD_PROM_RD       0xA0     // Prom read command
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

    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;

    uint16_t sensor_coefficients[ 8 ];
    uint32_t pressure;   
    uint32_t temperature;
    uint32_t delta_temp;
    float sensor_offset; 
    float sensitivity;   

} pressure2_t;

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

    // Static variable 
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} pressure2_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void pressure2_cfg_setup ( pressure2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param pressure2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t pressure2_init ( pressure2_t *ctx, pressure2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @details This function executes default configuration for Pressure 2 click.
 */
err_t pressure2_default_cfg ( pressure2_t *ctx );

/**
 * @brief Functions for reset chip.
 *
 * @param ctx          Click object.
 *
 * @details Functions for reset chip.
 */
void pressure2_reset ( pressure2_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Address which from data be read.
 * @param buffer       Memory where data be stored.
 * @param n_bytes      Number of bytes to be read.
 *
 * @details Reads multiple registries depending on the specified number of bytes.
 */
void pressure2_read_data ( pressure2_t *ctx, uint8_t cmd, uint8_t *buffer, uint8_t n_bytes );

/**
 * @brief Sends command.
 *
 * @param ctx          Click object.
 * @param cmd          Command to be written.
 *
 * @details Sends command using SPI protocol.
 */
void pressure2_write_bytes ( pressure2_t *ctx, uint8_t cmd );

/**
 * @brief Read calibration coefficients and return coefficient.
 *
 * @param ctx          Click object.
 * @param index        
 * @returns            Coefficient.       
 *
 * @details This function read calibration coefficients and return coefficient.
 */ 
uint16_t pressure2_read_coefficient ( pressure2_t *ctx, uint8_t index );

/**
 * @brief ADC conversion and return 24bit result.
 *
 * @param ctx          Click object.
 * @param cmd          Command to be send.
 * 
 * @returns            24bit result. 
 * @details This function preforms ADC conversion and return 24bit result.
 */
uint32_t pressure2_send_cmd_adc ( pressure2_t *ctx, uint8_t cmd );

/**
 * @brief Read sensor.
 *
 * @param ctx          Click object.
 * @param press        Pressure to be calculate;
 * @param temp         Pressure to be calculate;
 *
 * @details Functions for readding sensor.
 */
void pressure2_read_sensor ( pressure2_t *ctx, float *press, float *temp );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
