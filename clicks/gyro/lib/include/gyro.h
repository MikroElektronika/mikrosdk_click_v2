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
 * \brief This file contains API for Gyro Click driver.
 *
 * \addtogroup gyro Gyro Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GYRO_H
#define GYRO_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define GYRO_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GYRO_RETVAL  uint8_t

#define GYRO_OK           0x00
#define GYRO_INIT_ERROR   0xFF
/** \} */

 /**
 * \defgroup device_ident_reg Device identification register
 * \{
 */
#define GYRO_L3GD20_I2C_ADDRESS                         0x6B
#define GYRO_L3GD20_REGISTER_WHO_AM_I                   0x0F
#define GYRO_L3GD20_REGISTER_CTRL_REG1                  0x20
#define GYRO_L3GD20_REGISTER_CTRL_REG2                  0x21
#define GYRO_L3GD20_REGISTER_CTRL_REG3                  0x22
#define GYRO_L3GD20_REGISTER_CTRL_REG4                  0x23
#define GYRO_L3GD20_REGISTER_CTRL_REG5                  0x24
#define GYRO_L3GD20_REGISTER_REFERENCE                  0x25
#define GYRO_L3GD20_REGISTER_OUT_TEMP                   0x26
#define GYRO_L3GD20_REGISTER_STATUS_REG                 0x27
#define GYRO_L3GD20_REGISTER_OUT_X_L                    0x28
#define GYRO_L3GD20_REGISTER_OUT_X_H                    0x29
#define GYRO_L3GD20_REGISTER_OUT_Y_L                    0x2A
#define GYRO_L3GD20_REGISTER_OUT_Y_H                    0x2B
#define GYRO_L3GD20_REGISTER_OUT_Z_L                    0x2C
#define GYRO_L3GD20_REGISTER_OUT_Z_H                    0x2D
#define GYRO_L3GD20_REGISTER_FIFO_CTRL_REG              0x2E
#define GYRO_L3GD20_REGISTER_FIFO_SRC_REG               0x2F
/** \} */

/**
 * \defgroup interrupt_reg Interrupt register
 * \{
 */
#define GYRO_L3GD20_REGISTER_INT1_CFG                   0x30
#define GYRO_L3GD20_REGISTER_INT1_SRC                   0x31
#define GYRO_L3GD20_REGISTER_TSH_XH                     0x32
#define GYRO_L3GD20_REGISTER_TSH_XL                     0x33
#define GYRO_L3GD20_REGISTER_TSH_YH                     0x34
#define GYRO_L3GD20_REGISTER_TSH_YL                     0x35
#define GYRO_L3GD20_REGISTER_TSH_ZH                     0x36
#define GYRO_L3GD20_REGISTER_TSH_ZL                     0x37
#define GYRO_L3GD20_REGISTER_INT1_DURATION              0x38
/** \} */

/**
 * \defgroup configuration_bits Configuration bits
 * \{
 */
#define GYRO_L3GD20_REG1_NORMAL_MODE                    0x0F
#define GYRO_L3GD20_REG4_250DPS                         0x00
#define GYRO_L3GD20_REG5_FIFO_ENABLE_INT1               0x50
#define GYRO_L3GD20_FIFO_CTRL_REG_CONFIG                0x40
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

    digital_out_t rst;

    // Input pins 

    digital_in_t int_pin;

    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} gyro_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} gyro_cfg_t;

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
void gyro_cfg_setup ( gyro_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param gyro Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GYRO_RETVAL gyro_init ( gyro_t *ctx, gyro_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Gyro click.
 */
void gyro_default_cfg ( gyro_t *ctx );

/**
 * @brief Generic write data function
 *
 *
 * @param ctx  Click object.
 *
 * @param address         Register address
 *
 * @param write_command    Command to write
 *
 * @description Function write byte of data to L3GD20.
 */
void gyro_write_data ( gyro_t *ctx, uint8_t address, uint8_t write_command );

/**
 * @brief Generic read data function
 *
 *
 * @param ctx             Click object.
 * @param address         Register address
 *
 * @returns                Data from addressed register in L3GD20
 *
 * @description             Function read byte of data from register address of L3GD20.
 */
uint8_t gyro_read_data ( gyro_t *ctx, uint8_t address );

/**
 * @brief Function get low and high register data
 *
 *
 * @param ctx                  Click object.
 * @param adr_reg_low         low data register address
 *
 *
 * @returns         16-bit value ( low and high data )
 *
 * @description Function get data from two L3GD20 register.
 */
int16_t gyro_get_axis ( gyro_t *ctx, uint8_t adr_reg_low );

/**
 * @brief Function read axis
 *
 *
 * @param ctx  Click object.
 * @param gyro_x             pointer to read Gyro X-axis data
 * @param gyro_y             pointer to read Gyro Y-axis data
 * @param gyro_z             pointer to read Gyro Z-axis data
 *
 * @description Function read Gyro X-axis, Y-axis and Z-axis axis.
 *
 */
void gyro_read_gyro ( gyro_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );


#ifdef __cplusplus
}
#endif
#endif  // GYRO_H

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------ END
