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
 * \brief This file contains API for Compass 2 Click driver.
 *
 * \addtogroup compass2 Compass 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COMPASS2_H
#define COMPASS2_H

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

#define COMPASS2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define COMPASS2_MASTER_I2C 0
#define COMPASS2_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COMPASS2_RETVAL  uint8_t

#define COMPASS2_OK           0x00
#define COMPASS2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define COMPASS2_REG_DEVICE_ID         0x00 
#define COMPASS2_REG_INFORMATION       0x01 
#define COMPASS2_REG_STATUS_1          0x02 
#define COMPASS2_REG_AXIS_X_LOW        0x03 
#define COMPASS2_REG_AXIS_X_HIGH       0x04 
#define COMPASS2_REG_AXIS_Y_LOW        0x05 
#define COMPASS2_REG_AXIS_Y_HIGH       0x06 
#define COMPASS2_REG_AXIS_Z_LOW        0x07 
#define COMPASS2_REG_AXIS_Z_HIGH       0x08 
#define COMPASS2_REG_STATUS_2          0x09 
#define COMPASS2_REG_CNTRL1            0x0A 
#define COMPASS2_REG_CNTRL2            0x0B 
#define COMPASS2_REG_SELF_TEST         0x0C 
#define COMPASS2_REG_TEST_1            0x0D 
#define COMPASS2_REG_TEST_2            0x0E 
#define COMPASS2_REG_I2C_DISABLE       0x0F 
#define COMPASS2_REG_X_AXIS_SENS       0x10 
#define COMPASS2_REG_Y_AXIS_SENS       0x11 
#define COMPASS2_REG_Z_AXIS_SENS       0x12 

#define COMPASS2_MODE_POWER_DOWN       0x00
#define COMPASS2_MODE_SINGL_MEASUR     0x01
#define COMPASS2_MODE_CONT_MEAS_1      0x02
#define COMPASS2_MODE_CONT_MEAS_2      0x06
#define COMPASS2_MODE_EXT_TRIG         0x04
#define COMPASS2_MODE_SELF_TEST        0x08
#define COMPASS2_MODE_FUSE_ROM         0x0F

#define COMPASS2_SET_RESOLUTION_14bit  0x00
#define COMPASS2_SET_RESOLUTION_16bit  0x10

#define COMPASS2_MODE_SPI              0x00
#define COMPASS2_MODE_I2C              0x01

#define COMPASS2_X_AXIS                0x00
#define COMPASS2_Y_AXIS                0x01
#define COMPASS2_Z_AXIS                0x02
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
typedef uint8_t  compass2_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *compass2_master_io_t )( struct compass2_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct compass2_s
{
    // Output pins 

    digital_out_t rst;
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
   compass2_master_io_t  write_f;
   compass2_master_io_t  read_f;
   compass2_select_t master_sel;

   uint16_t output_resolution;

} compass2_t;

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

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

    compass2_select_t sel;

} compass2_cfg_t;

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
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * 
 * @note All used pins will be set to unconnected state.
 */
void compass2_cfg_setup ( compass2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param compass2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COMPASS2_RETVAL compass2_init ( compass2_t *ctx, compass2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Compass 2 click.
 */
void compass2_default_cfg ( compass2_t *ctx );

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
void compass2_generic_write ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx       Click object.
 * @param reg       Register address.
 * @param data_buf  Data buf to be written.
 * @param len       Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void compass2_generic_read ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write byte function.
 *
 * @param ctx       Click object.
 * @param reg       Register address.
 * @param data_buf  Data buf to be written.
 *
 * @description This function writes one byte to the desired register.
 */
void compass2_write_byte ( compass2_t *ctx, uint8_t reg, uint8_t data_buf ); 

/**
 * @brief Read byte function.
 *
 * @param ctx       Click object.
 * @param reg       Register address.
 *
 * @description This function reads one byte from the desired register.
 */
uint8_t compass2_read_byte ( compass2_t *ctx, uint8_t reg ); 

/**
 * @brief Hardware reset function.
 * 
 * @param ctx       Click object.
 *
 * @description This function does a hardware reset of the device.
 */
void compass2_reset ( compass2_t *ctx ); 

/**
 * @brief Switch from I2C to SPI mode function.
 *
 * @param ctx       Click object.
 *
 * @description This function reads one byte from the desired register.
 */
void compass2_i2c_disable ( compass2_t *ctx );

/**
 * @brief Software reset function.
 *
 * @param ctx       Click object.
 *
 * @description This function does a software reset of the module.
 */
void compass2_software_reset ( compass2_t *ctx ); 

/**
 * @brief Get resolution function.
 *
 * @param res       Resolution mode selector.
 *
 * @description This function returns a 14 or 16 bit resolution transformation coefficient.
 */
float compass2_get_resolution_parameter ( uint8_t res );

/**
 * @brief Get ready function.
 *
 * @param ctx       Click object.
 *
 * @description This function returns the ready status.
 */
uint8_t compass2_get_rdy ( compass2_t *ctx );

/**
 * @brief Get data overrun function.
 *
 * @param ctx       Click object.
 *
 * @description This function returns the data overrun status.
 */
uint8_t compass2_get_data_overrun ( compass2_t *ctx ); 

/**
 * @brief Get axis adjustment function.
 *
 * @param ctx       Click object.
 * @param *x        Pointer fox x.
 * @param *y        Pointer for y.
 * @param *z        Pointer for z.
 *
 * @description This function does adjustments to the axes.
 */
void compass2_get_adjustment( compass2_t *ctx, uint8_t *x, uint8_t *y, uint8_t *z );

/**
 * @brief Set output resolution function.
 *
 * @param ctx       Click object.
 * @param res       Resolution value.
 *
 * @description This function sets the output resolution.
 */
void compass2_set_out_resolution ( compass2_t *ctx, uint8_t res ); 

/**
 * @brief Set output resolution function.
 *
 * @param ctx       Click object.
 * @param mode      Mode value.
 *
 * @description This function sets the output resolution mode.
 */
void compass2_set_mode ( compass2_t *ctx, uint8_t mode );

/**
 * @brief Get all data function.
 *
 * @param ctx       Click object.
 * @param x         X axis.
 * @param y         Y axis.
 * @param z         Z axis.
 * 
 * @description This function gets the data from all axes.
 */
void compass2_get_all_data ( compass2_t *ctx, int16_t *x, int16_t *y, int16_t *z );

/**
 * @brief Get one axis data function.
 *
 * @param ctx       Click object.
 * @param axis      Axis selector.
 * 
 * @description This function gets the data from one specified axis.
 */
int16_t compass2_get_axis_data ( compass2_t *ctx, uint8_t axis ); 

/**
 * @brief New measurement function.
 *
 * @param ctx       Click object.
 *
 * @description This function prepares the device for a new measurement.
 */
void compass2_new_measurement ( compass2_t *ctx ); 

#ifdef __cplusplus
}
#endif
#endif  // _COMPASS2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
