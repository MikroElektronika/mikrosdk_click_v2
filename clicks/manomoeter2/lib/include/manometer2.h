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
 * \brief This file contains API for Manometer 2 Click driver.
 *
 * \addtogroup manometer2 Manometer 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MANOMETER2_H
#define MANOMETER2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
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

#define MANOMETER2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define MANOMETER2_MASTER_I2C 0
#define MANOMETER2_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MANOMETER2_RETVAL  uint8_t

#define MANOMETER2_OK           0x00
#define MANOMETER2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address  Slave address
 * \{
 */
#define MANOMETER2_I2C_ADDRESS_0     0x76
#define MANOMETER2_I2C_ADDRESS_1     0x77
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define MANOMETER2_RESET             0x1E
#define MANOMETER2_RESET_CMD         0xA6
#define MANOMETER2_ADC_READ          0x00
#define MANOMETER2_D1_CONVERT_256    0x40
#define MANOMETER2_D1_CONVERT_512    0x42
#define MANOMETER2_D1_CONVERT_1024   0x44
#define MANOMETER2_D1_CONVERT_2048   0x46
#define MANOMETER2_D1_CONVERT_4096   0x48
#define MANOMETER2_D2_CONVERT_256    0x50
#define MANOMETER2_D2_CONVERT_512    0x52
#define MANOMETER2_D2_CONVERT_1024   0x54
#define MANOMETER2_D2_CONVERT_2048   0x56
#define MANOMETER2_D2_CONVERT_4096   0x58
#define MANOMETER2_C1_READ           0xA2
#define MANOMETER2_C2_READ           0xA4
#define MANOMETER2_C3_READ           0xA6
#define MANOMETER2_C4_READ           0xA8
#define MANOMETER2_C5_READ           0xAA
#define MANOMETER2_C6_READ           0xAC
#define MANOMETER2_CONVERT_256          0
#define MANOMETER2_CONVERT_512          1
#define MANOMETER2_CONVERT_1024         2
#define MANOMETER2_CONVERT_2048         3
#define MANOMETER2_CONVERT_4096         4
/** \} */

/**
 * \defgroup q_value  Q value
 * \{
 */
#define MANOMETER2_Q1                  14
#define MANOMETER2_Q2                  16
#define MANOMETER2_Q3                   7
#define MANOMETER2_Q4                   5
#define MANOMETER2_Q5                   7
#define MANOMETER2_Q6                  21
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  manometer2_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *manometer2_master_io_t )( struct manometer2_s*, uint8_t, uint8_t*, uint8_t );

typedef struct 
{
    uint16_t coef1;
    uint16_t coef2;
    uint16_t coef3;
    uint16_t coef4;
    uint16_t coef5;
    uint16_t coef6;

} manometer2_coef_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct manometer2_s
{
    // Output pins 

    digital_out_t cs;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    manometer2_master_io_t  write_f;
    manometer2_master_io_t  read_f;
    manometer2_select_t master_sel;

    manometer2_coef_t coef;

} manometer2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   manometer2_select_t sel;

} manometer2_cfg_t;

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
void manometer2_cfg_setup ( manometer2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MANOMETER2_RETVAL manometer2_init ( manometer2_t *ctx, manometer2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Manometer 2 click.
 */
void manometer2_default_cfg ( manometer2_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void manometer2_generic_write ( manometer2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void manometer2_generic_read ( manometer2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write data function
 *
 * @param ctx                 Click object.
 * @param reg_address         Register address
 * @param write_command       Command to write
 *
 * @description Function write byte of data
 */
void manometer2_write_data ( manometer2_t *ctx, uint8_t reg_address, uint8_t write_command );

/**
 * @brief Generic read data function
 *
 * @param ctx                 Click object.
 * @param reg_address         Register address
 *
 * @return
 * Data from addressed register
 *
 * @description Generic read 16-bit data function
 */
uint16_t manometer2_read_data ( manometer2_t *ctx, uint8_t reg_address );

/**
 * @brief Generic read data function
 *
 * @param ctx                 Click object.
 * @param reg_address         Register address
 *
 * @return
 * Data from addressed register
 *
 * @description Generic read 24-bit data function
 */
uint32_t manometer2_read_command ( manometer2_t *ctx, uint8_t reg_address );

/**
 * @brief Reset
 *
 * @param ctx                 Click object.
 *
 * @description Function command reset
 */
void manometer2_reset ( manometer2_t *ctx );

/**
 * @brief Function read coeffitient
 *
 * @param ctx                 Click object.
 * 
 * @description Function resets communication with the register and read coeffitient value
 */
void manometer2_read_coef ( manometer2_t *ctx );

/**
 * @brief Get temperature data function
 *
 * @param ctx                        Click object.
 * @param oversampling_ratio         Oversampling ratio
 *
 * @return
 * float temperature value [ �C ]
 *
 * @description Function read temperature data
 */
float manometer2_get_temperature ( manometer2_t *ctx, uint8_t oversampling_ratio );

/**
 * @brief Get pressure data function
 *
 * @param ctx                        Click object.
 * @param oversampling_ratio         Oversampling ratio
 *
 * @return
 * float pressure value [ PSI ]
 *
 * @description Function read pressure data
 */
float manometer2_get_pressure ( manometer2_t *ctx, uint8_t oversampling_ratio );

#ifdef __cplusplus
}
#endif
#endif  // _MANOMETER2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
