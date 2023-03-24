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
 * \brief This file contains API for Accel3 Click driver.
 *
 * \addtogroup accel3 Accel3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL3_H
#define ACCEL3_H

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
#define ACCEL3_MAP_MIKROBUS( cfg, mikrobus )          \
   cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
   cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS );   \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define ACCEL3_MASTER_I2C                  0
#define ACCEL3_MASTER_SPI                  1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL3_RETVAL  uint8_t

#define ACCEL3_OK                          0x00
#define ACCEL3_INIT_ERROR                  0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define ACCEL3_I2C_ADDRESS                 0x18
/** \} */

/**
 * \defgroup register Register Address
 * \{
 */
#define ACCEL3_REG_WHO_AM_I                0x0F
#define ACCEL3_REG_HP_FILTER_RESET         0x25
#define ACCEL3_REG_REFERENCE               0x26
#define ACCEL3_REG_STATUS                  0x27
/** \} */

/**
 * \defgroup ctrl_reg Control Registers
 * \{
 */
#define ACCEL3_CTRL_REG1                   0x20
#define ACCEL3_CTRL_REG2                   0x21
#define ACCEL3_CTRL_REG3                   0x22
#define ACCEL3_CTRL_REG4                   0x23
#define ACCEL3_CTRL_REG5                   0x24
/** \} */

/**
 * \defgroup out Output Registers
 * \{
 */
#define ACCEL3_OUT_X_L                     0x28
#define ACCEL3_OUT_X_H                     0x29
#define ACCEL3_OUT_Y_L                     0x2A
#define ACCEL3_OUT_Y_H                     0x2B
#define ACCEL3_OUT_Z_L                     0x2C
#define ACCEL3_OUT_Z_H                     0x2D
/** \} */

/**
 * \defgroup accel_data Accelerometer Data
 * \{
 */
#define ACCEL3_ENABLE_AXIS                 0x27
#define ACCEL3_FULL_SCALE                  0x00
#define ACCEL3_DATA_MASK                   0x80
#define ACCEL3_DEVICE_IDENTIFIER           0x32
#define ACCEL3_TRUE                        0x00
#define ACCEL3_FALSE                       0x01
#define ACCEL3_START_VALUE                 0x00
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
typedef uint8_t  accel3_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *accel3_master_io_t )( struct accel3_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct accel3_s
{
    // Output pins 

    digital_out_t int_pin;
    digital_out_t cs;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    accel3_master_io_t  write_f;
    accel3_master_io_t  read_f;
    accel3_select_t master_sel;

} accel3_t;

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
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;
    uint32_t spi_speed;
    uint8_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   accel3_select_t sel;

} accel3_cfg_t;

/** \} */ // End types group

/**
 * \defgroup data_measure Measurement data
 * \{
 */

/**
 * @brief Accel data object definition.
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;

} accel3_data_t;

/** \} */ // Measurement data

// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 
/** \} */ // End constants group

// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group

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
 * @param cfg           Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void accel3_cfg_setup ( accel3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param accel3        Click object.
 * @param cfg           Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ACCEL3_RETVAL accel3_init ( accel3_t *ctx, accel3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 *
 * @description This function executes default configuration for Accel3 click.
 */
void accel3_default_cfg ( accel3_t *ctx, accel3_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx           Click object.
 * @param reg           Register address.
 * @param data_buf      Output data buf
 * @param len           Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void accel3_generic_write ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx           Click object.
 * @param reg           Register address.
 * @param data_buf      Data buf to be written.
 * @param len           Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void accel3_generic_read ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Check Accel 3 ID function.
 *
 * @param ctx           Click object.
 *
 * @description This function checks Accel 3 ID.
 */
uint8_t accel3_check_id ( accel3_t *ctx );

/**
 * @brief Get accelerometer data function.
 * 
 * @param ctx           Click object.
 * @param accel3_data   Pointer to structure where Accel data be stored.
 *
 * @description This function reads Accel data ( X, Y and Z axis ) 
 * from the desired Accel registers of the H3LIS331DL module.
 */
void accel3_read_data ( accel3_t *ctx, accel3_data_t *accel3_data );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
