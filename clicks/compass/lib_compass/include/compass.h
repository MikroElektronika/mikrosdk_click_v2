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
 * \brief This file contains API for Compass Click driver.
 *
 * \addtogroup compass Compass Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COMPASS_H
#define COMPASS_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup control_regs Control Registers
 * \{
 */
#define COMPASS_CTRL_REG1           0x20
#define COMPASS_CTRL_REG2           0x21
#define COMPASS_CTRL_REG3           0x22
#define COMPASS_CTRL_REG4           0x23
#define COMPASS_CTRL_REG5           0x24
#define COMPASS_CTRL_REG6           0x25
#define COMPASS_FIFO_CTRL_REG       0x2E
#define COMPASS_STATUS_REG          0x27
#define COMPASS_INT1_CFG            0x30
#define COMPASS_INT2_CFG            0x34

/**
 * \defgroup magnetic_field_sensing_registers Magnetic Field Sensing Registers
 * \{
 */
#define COMPASS_CRA_REG             0x00
#define COMPASS_CRB_REG             0x01
#define COMPASS_MR_REG              0x02
#define COMPASS_SR_REG              0x09

#define COMPASS_IRA_REG             0x0A
#define COMPASS_IRB_REG             0x0B
#define COMPASS_IRC_REG             0x0C

#define COMPASS_OUT_MAGNET_X_HIGH   0x03
#define COMPASS_OUT_MAGNET_X_LOW    0x04
#define COMPASS_OUT_MAGNET_Z_HIGH   0x05
#define COMPASS_OUT_MAGNET_Z_LOW    0x06
#define COMPASS_OUT_MAGNET_Y_HIGH   0x07
#define COMPASS_OUT_MAGNET_Y_LOW    0x08

#define COMPASS_TEMP_OUT_HIGH       0x31
#define COMPASS_TEMP_OUT_LOW        0x32

/**
 * \defgroup linear_acceleration_registers Linear acceleration registers
 * \{
 */
#define COMPASS_OUT_ACCEL_X_LOW     0x28
#define COMPASS_OUT_ACCEL_X_HIGH    0x29
#define COMPASS_OUT_ACCEL_Y_LOW     0x2A
#define COMPASS_OUT_ACCEL_Y_HIGH    0x2B
#define COMPASS_OUT_ACCEL_Z_LOW     0x2C
#define COMPASS_OUT_ACCEL_Z_HIGH    0x2D

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define COMPASS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COMPASS_RETVAL  uint8_t

#define COMPASS_OK           0x00
#define COMPASS_INIT_ERROR   0xFF
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
    // Input pins 

    digital_in_t rdy;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t  accel_slave_address;
    uint8_t  magnet_slave_address;

} compass_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rdy;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_accel_address;
    uint8_t i2c_magnet_address;

} compass_cfg_t;

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
void compass_cfg_setup ( compass_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COMPASS_RETVAL compass_init ( compass_t *ctx, compass_cfg_t *cfg );

/**
 * @brief Generic accel write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes accelerometer data to the desired register.
 */
void compass_accel_generic_write ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic magnet write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes magnet data to the desired register.
 */
void compass_magnet_generic_write ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic accel read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired accelerometer register.
 */
void compass_accel_generic_read ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic magnet read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired magnetic register.
 */
void compass_magnet_generic_read ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Default config function.
 * 
 * @param ctx          Click object.
 *
 * @description This function does default configuration for the chip.
 */
void compass_default_config ( compass_t *ctx );

/**
 * @brief Accel axes read function.
 * 
 * @param ctx          Click object.
 * @param x_axis       X axis value.
 * @param y_axis       Y axis value.
 * @param z_axis       Z axis value.
 *
 * @description This function reads data for accelerometer axes.
 */
void compass_read_accel_axis ( compass_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );

/**
 * @brief Magnet axes read function.
 * 
 * @param ctx          Click object.
 * @param x_axis       X axis value.
 * @param y_axis       Y axis value.
 * @param z_axis       Z axis value.
 *
 * @description This function reads data for megnetic axes.
 */
void compass_read_magnet_axis ( compass_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );

#ifdef __cplusplus
}
#endif
#endif  // _COMPASS_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
