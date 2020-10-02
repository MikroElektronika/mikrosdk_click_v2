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
 * \brief This file contains API for 6DOF IMU 2 Click driver.
 *
 * \addtogroup c6dofimu2 6DOF IMU 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU2_H
#define C6DOFIMU2_H

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

#define C6DOFIMU2_MAP_MIKROBUS( cfg, mikrobus )        \
    cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C6DOFIMU2_MASTER_I2C                      0
#define C6DOFIMU2_MASTER_SPI                      1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU2_RETVAL  uint8_t

#define C6DOFIMU2_OK                              0x00
#define C6DOFIMU2_INIT_ERROR                      0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define C6DOFIMU2_I2C_ADDR                        0x68
/** \} */

/**
 * \defgroup register Register Address
 * \{
 */
#define C6DOFIMU2_REG_CHIP_ID                     0x00
#define C6DOFIMU2_REG_ERROR                       0x02
#define C6DOFIMU2_REG_PMU_STATUS                  0x03
#define C6DOFIMU2_REG_AUX_DATA                    0x04
#define C6DOFIMU2_REG_GYRO_DATA                   0x0C
#define C6DOFIMU2_REG_ACCEL_DATA                  0x12
#define C6DOFIMU2_REG_STATUS                      0x1B
#define C6DOFIMU2_REG_INT_STATUS                  0x1C
#define C6DOFIMU2_REG_FIFO_LENGTH                 0x22
#define C6DOFIMU2_REG_FIFO_DATA                   0x24
#define C6DOFIMU2_REG_ACCEL_CONFIG                0x40
#define C6DOFIMU2_REG_ACCEL_RANGE                 0x41
#define C6DOFIMU2_REG_GYRO_CONFIG                 0x42
#define C6DOFIMU2_REG_GYRO_RANGE                  0x43
#define C6DOFIMU2_REG_AUX_ODR                     0x44
#define C6DOFIMU2_REG_FIFO_DOWN                   0x45
#define C6DOFIMU2_REG_FIFO_CONFIG_0               0x46
#define C6DOFIMU2_REG_FIFO_CONFIG_1               0x47
#define C6DOFIMU2_REG_AUX_IF_0                    0x4B
#define C6DOFIMU2_REG_AUX_IF_1                    0x4C
#define C6DOFIMU2_REG_AUX_IF_2                    0x4D
#define C6DOFIMU2_REG_AUX_IF_3                    0x4E
#define C6DOFIMU2_REG_AUX_IF_4                    0x4F
#define C6DOFIMU2_REG_INT_ENABLE_0                0x50
#define C6DOFIMU2_REG_INT_ENABLE_1                0x51
#define C6DOFIMU2_REG_INT_ENABLE_2                0x52
#define C6DOFIMU2_REG_INT_OUT_CTRL                0x53
#define C6DOFIMU2_REG_INT_LATCH                   0x54
#define C6DOFIMU2_REG_INT_MAP_0                   0x55
#define C6DOFIMU2_REG_INT_MAP_1                   0x56
#define C6DOFIMU2_REG_INT_MAP_2                   0x57
#define C6DOFIMU2_REG_INT_DATA_0                  0x58
#define C6DOFIMU2_REG_INT_DATA_1                  0x59
#define C6DOFIMU2_REG_INT_LOWHIGH_0               0x5A
#define C6DOFIMU2_REG_INT_LOWHIGH_1               0x5B
#define C6DOFIMU2_REG_INT_LOWHIGH_2               0x5C
#define C6DOFIMU2_REG_INT_LOWHIGH_3               0x5D
#define C6DOFIMU2_REG_INT_LOWHIGH_4               0x5E
#define C6DOFIMU2_REG_INT_MOTION_0                0x5F
#define C6DOFIMU2_REG_INT_MOTION_1                0x60
#define C6DOFIMU2_REG_INT_MOTION_2                0x61
#define C6DOFIMU2_REG_INT_MOTION_3                0x62
#define C6DOFIMU2_REG_INT_TAP_0                   0x63
#define C6DOFIMU2_REG_INT_TAP_1                   0x64
#define C6DOFIMU2_REG_INT_ORIENT_0                0x65
#define C6DOFIMU2_REG_INT_ORIENT_1                0x66
#define C6DOFIMU2_REG_INT_FLAT_0                  0x67
#define C6DOFIMU2_REG_INT_FLAT_1                  0x68
#define C6DOFIMU2_REG_FOC_CONF                    0x69
#define C6DOFIMU2_REG_CONF                        0x6A
#define C6DOFIMU2_REG_NV_CONF                     0x70
/** \} */

/**
 * \defgroup cfg_reg Config registers
 * \{
 */
#define C6DOFIMU2_CFG_IF_CONF                     0x6B
#define C6DOFIMU2_CFG_SELF_TEST                   0x6D
#define C6DOFIMU2_CFG_OFFSET                      0x71
#define C6DOFIMU2_CFG_OFFSET_CONF                 0x77
#define C6DOFIMU2_CFG_INT_STEP_CNT_0              0x78
#define C6DOFIMU2_CFG_INT_STEP_CONFIG_0           0x7A
#define C6DOFIMU2_CFG_INT_STEP_CONFIG_1           0x7B
#define C6DOFIMU2_CFG_COMMAND                     0x7E
#define C6DOFIMU2_CFG_SPI_COMM_TEST               0x7F
#define C6DOFIMU2_CFG_INTL_PULLUP_CONF            0x85
/** \} */

/**
 * \defgroup cmd_reg Command registers
 * \{
 */
#define C6DOFIMU2_CMD_ACCEL_NORMAL                0x11
#define C6DOFIMU2_CMD_ACCEL_LOW_PWR               0x12
#define C6DOFIMU2_CMD_GYRO_NORMAL                 0x15
#define C6DOFIMU2_CMD_GYRO_FAST                   0x7E
#define C6DOFIMU2_CMD_SEL_I2C                     0x00
#define C6DOFIMU2_CMD_SEL_SPI                     0x01
/** \} */

/**
 * \defgroup output Output registers
 * \{
 */

// GYRO

#define C6DOFIMU2_GYRO_X_L                        0x0C
#define C6DOFIMU2_GYRO_X_H                        0x0D
#define C6DOFIMU2_GYRO_Y_L                        0x0E
#define C6DOFIMU2_GYRO_Y_H                        0x0F
#define C6DOFIMU2_GYRO_Z_L                        0x10
#define C6DOFIMU2_GYRO_Z_H                        0x11

// ACCEL

#define C6DOFIMU2_ACCEL_X_L                       0x12
#define C6DOFIMU2_ACCEL_X_H                       0x13
#define C6DOFIMU2_ACCEL_Y_L                       0x14
#define C6DOFIMU2_ACCEL_Y_H                       0x15
#define C6DOFIMU2_ACCEL_Z_L                       0x16
#define C6DOFIMU2_ACCEL_Z_H                       0x17
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
typedef uint8_t c6dofimu2_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c6dofimu2_master_io_t )( struct c6dofimu2_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu2_s
{
    // Output pins 

    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    c6dofimu2_master_io_t  write_f;
    c6dofimu2_master_io_t  read_f;
    c6dofimu2_select_t master_sel;

} c6dofimu2_t;

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

    c6dofimu2_select_t sel;

} c6dofimu2_cfg_t;

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
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    
} c6dofimu2_accel_data_t;

/**
 * @brief Gyro data object definition.
 */
typedef struct
{
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;

} c6dofimu2_gyro_data_t;

/** \} */ // Measurement data
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
void c6dofimu2_cfg_setup ( c6dofimu2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param c6dofimu2   Click object.
 * @param cfg         Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU2_RETVAL c6dofimu2_init ( c6dofimu2_t *ctx, c6dofimu2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @description This function executes default configuration for 6DOF IMU 2 click.
 * @note
 *      Click default configuration:
 * First recognizes type of communication and then sets both 
 * accelerometer and gyroscope in their normal state of performance.
 * --------------------------------------
 * <pre>
 *     C6DOFIMU2_CFG_COMMAND
 * --------------------------------------
 *     C6DOFIMU2_ACCEL_NORMAL 
 *   | C6DOFIMU2_GYRO_NORMAL
 * </pre>
 */
void c6dofimu2_default_cfg ( c6dofimu2_t *ctx, c6dofimu2_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx         Click object.
 * @param reg         Register address.
 * @param data_buf    Output data buf
 * @param len         Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void c6dofimu2_generic_write ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void c6dofimu2_generic_read ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Low and high register data function.
 *
 * @param ctx              Click object.
 * @param adr_reg_low      Low data register address.
 * @param adr_reg_high     High data register address.
 * 
 * @return
 * 16-bit value ( low and high data )
 *
 * @description This function get data from two BMI160 registers.
 */
int16_t c6dofimu2_get_axis ( c6dofimu2_t *ctx, uint8_t adr_reg_low, uint8_t adr_reg_high );

/**
 * @brief Read axis function.
 *
 * @param ctx          Click object.
 * @param accel_data   Pointer to structure where Accel data be stored.
 *
 * @description This function read Accel X-axis, Y-axis and Z-axis.
 */
void c6dofimu2_read_accel ( c6dofimu2_t *ctx, c6dofimu2_accel_data_t *accel_data );

/**
 * @brief Read axis function.
 *
 * @param ctx          Click object.
 * @param gyro_data    Pointer to structure where Gyro data be stored.
 *
 * @description This function read Gyro X-axis, Y-axis and Z-axis.
 */
void c6dofimu2_read_gyro ( c6dofimu2_t *ctx, c6dofimu2_gyro_data_t *gyro_data );

#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
