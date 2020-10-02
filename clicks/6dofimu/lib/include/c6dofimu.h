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
 * \brief This file contains API for 6DOF IMU Click driver.
 *
 * \addtogroup c6dofimu 6DOF IMU Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU_H
#define C6DOFIMU_H

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

#define C6DOFIMU_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C6DOFIMU_MASTER_I2C 0
#define C6DOFIMU_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU_RETVAL  uint8_t

#define C6DOFIMU_OK           0x00
#define C6DOFIMU_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define C6DOFIMU_SLAVE_ADDRESS   0x6B;
/** \} */

/**
 * \defgroup configuration_registers Configuration Registers
 * \{
 */
#define C6DOFIMU_FUNC_CFG_ACCESS   0x01

#define C6DOFIMU_FIFO_CTRL1        0x06
#define C6DOFIMU_FIFO_CTRL2        0x07
#define C6DOFIMU_FIFO_CTRL3        0x08
#define C6DOFIMU_FIFO_CTRL4        0x09
#define C6DOFIMU_FIFO_CTRL5        0x0A

#define C6DOFIMU_ORIENT_CFG_G      0x0B

#define C6DOFIMU_INT1_CTRL         0x0D
#define C6DOFIMU_INT2_CTRL         0x0E

#define C6DOFIMU_CTRL1_XL          0x10
#define C6DOFIMU_CTRL2_G           0x11
#define C6DOFIMU_CTRL3_C           0x12
#define C6DOFIMU_CTRL4_C           0x13
#define C6DOFIMU_CTRL5_C           0x14
#define C6DOFIMU_CTRL6_C           0x15
#define C6DOFIMU_CTRL7_G           0x16
#define C6DOFIMU_CTRL8_XL          0x17
#define C6DOFIMU_CTRL9_XL          0x18
#define C6DOFIMU_CTRL10_C          0x19
/** \} */

/**
 * \defgroup output_data_registers Output Data Registers
 * \{
 */
#define C6DOFIMU_OUT_TEMP_L        0x20
#define C6DOFIMU_OUT_TEMP_H        0x21
     
#define C6DOFIMU_OUTX_L_G          0x22
#define C6DOFIMU_OUTX_H_G          0x23
#define C6DOFIMU_OUTY_L_G          0x24
#define C6DOFIMU_OUTY_H_G          0x25
#define C6DOFIMU_OUTZ_L_G          0x26
#define C6DOFIMU_OUTZ_H_G          0x27
     
#define C6DOFIMU_OUTX_L_XL         0x28
#define C6DOFIMU_OUTX_H_XL         0x29
#define C6DOFIMU_OUTY_L_XL         0x2A
#define C6DOFIMU_OUTY_H_XL         0x2B
#define C6DOFIMU_OUTZ_L_XL         0x2C
#define C6DOFIMU_OUTZ_H_XL         0x2D

#define C6DOFIMU_FIFO_DATA_OUT_L   0x3E
#define C6DOFIMU_FIFO_DATA_OUT_H   0x3F

#define C6DOFIMU_TIMESTAMP0_REG    0x40
#define C6DOFIMU_TIMESTAMP1_REG    0x41
#define C6DOFIMU_TIMESTAMP2_REG    0x42

#define C6DOFIMU_STEP_COUNTER_L    0x4B
#define C6DOFIMU_STEP_COUNTER_H    0x4C
/** \} */

/**
 * \defgroup status_registers Status Registers
 * \{
 */
#define C6DOFIMU_STATUS_REG     0x1E

#define C6DOFIMU_FIFO_STATUS1   0x3A
#define C6DOFIMU_FIFO_STATUS2   0x3B
#define C6DOFIMU_FIFO_STATUS3   0x3C
#define C6DOFIMU_FIFO_STATUS4   0x3D

#define C6DOFIMU_TIMESTAMP_L    0x49
#define C6DOFIMU_TIMESTAMP_H    0x4A

#define C6DOFIMU_WHO_AM_I       0x0F
/** \} */

/**
 * \defgroup interrupt_registers Interrupt Registers
 * \{
 */
#define C6DOFIMU_WAKE_UP_SRC       0x1B
#define C6DOFIMU_TAP_SRC           0x1C
#define C6DOFIMU_D6D_SRC           0x1D

#define C6DOFIMU_FUN_SRC           0x53

#define C6DOFIMU_TAP_CFG           0x58
#define C6DOFIMU_TAP_THS_6D        0x59
#define C6DOFIMU_INT_DUR2          0x5A
#define C6DOFIMU_WAKE_UP_THS       0x5B
#define C6DOFIMU_WAKE_UP_DUR       0x5C
#define C6DOFIMU_FREE_FALL         0x5D
#define C6DOFIMU_MD1_CFG           0x5E
#define C6DOFIMU_MD2_CFG           0x5F
/** \} */

/**
 * \defgroup configuration_bits Configuration Bits
 * \{
 */
#define C6DOFIMU_CFG_BIT_0   0x01  
#define C6DOFIMU_CFG_BIT_1   0x02
#define C6DOFIMU_CFG_BIT_2   0x04
#define C6DOFIMU_CFG_BIT_3   0x08
#define C6DOFIMU_CFG_BIT_4   0x10
#define C6DOFIMU_CFG_BIT_5   0x20
#define C6DOFIMU_CFG_BIT_6   0x40
#define C6DOFIMU_CFG_BIT_7   0x80
/** \} */

/**
 * \defgroup read_mode Read Mode
 * \{
 */
#define C6DOFIMU_ACCEL_READ_MODE   0x00
#define C6DOFIMU_GYRO_READ_MODE    0x01
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
typedef uint8_t  c6dofimu_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c6dofimu_master_io_t )( struct c6dofimu_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Gyro/Accel Axis structure.
 */
typedef struct
{
   int16_t x;
   int16_t y;
   int16_t z;

} c6dofimu_axis_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu_s
{

   digital_out_t cs;

    // Input pins 

   digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   c6dofimu_master_io_t  write_f;
   c6dofimu_master_io_t  read_f;
   c6dofimu_select_t master_sel;
   
   c6dofimu_axis_t accel_axis;
   c6dofimu_axis_t gyro_axis;

} c6dofimu_t;

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
    uint8_t i2c_address;
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   c6dofimu_select_t sel;

} c6dofimu_cfg_t;

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
void c6dofimu_cfg_setup ( c6dofimu_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c6dofimu Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU_RETVAL c6dofimu_init ( c6dofimu_t *ctx, c6dofimu_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 6DOF IMU click.
 */
void c6dofimu_default_cfg ( c6dofimu_t *ctx );

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
void c6dofimu_generic_write ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void c6dofimu_generic_read ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read axis data function.
 *
 * @param ctx        Click object.
 * @param read_mode  Read mode: { Accelerometer | Gyroscope }.
 *
 * @description This function reads axis data for the gyroscope or the accelerometer from
 *              predefined data register addresses.
 */
void c6dofimu_read_axis_data ( c6dofimu_t *ctx, uint8_t read_mode );

/**
 * @brief Read temperature data function.
 *
 * @param ctx        Click object.
 *
 * @description This function reads temperature data from predefined data registers.
 */
float c6dofimu_read_temperature ( c6dofimu_t *ctx );

/**
 * @brief Digital read interrupt function.
 *
 * @param ctx        Click object.
 *
 * @description This function reads the digital signal from the INT pin.
 */
uint8_t c6dofimu_digital_read_int ( c6dofimu_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
