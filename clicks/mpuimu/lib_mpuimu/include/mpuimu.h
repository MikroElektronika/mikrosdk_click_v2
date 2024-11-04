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
 * \brief This file contains API for MPU IMU Click driver.
 *
 * \addtogroup mpuimu MPU IMU Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MPUIMU_H
#define MPUIMU_H

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

#define MPUIMU_MAP_MIKROBUS( cfg, mikrobus )          \
   cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
   cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS );   \
   cfg.fsy     = MIKROBUS( mikrobus, MIKROBUS_RST );  \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define MPUIMU_MASTER_I2C                      0
#define MPUIMU_MASTER_SPI                      1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MPUIMU_RETVAL  uint8_t

#define MPUIMU_OK                              0x00
#define MPUIMU_INIT_ERROR                      0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define MPUIMU_I2C_ADDR_0                      0xD2
#define MPUIMU_I2C_ADDR_1                      0x69
/** \} */

/**
 * \defgroup register Register Address
 * \{
 */
#define MPUIMU_REG_SELF_TEST_X                 0x0D
#define MPUIMU_REG_SELF_TEST_Y                 0x0E
#define MPUIMU_REG_SELF_TEST_Z                 0x0F
#define MPUIMU_REG_SELF_TEST_A                 0x10
#define MPUIMU_REG_SMPLRT_DIV                  0x19
#define MPUIMU_REG_MOT_THR                     0x1F
#define MPUIMU_REG_I2C_MST_CTRL                0x24
#define MPUIMU_REG_I2C_SLV0_ADDR               0x25
#define MPUIMU_REG_I2C_SLV0                    0x26
#define MPUIMU_REG_I2C_SLV0_CTRL               0x27
#define MPUIMU_REG_I2C_SLV1_ADDR               0x28
#define MPUIMU_REG_I2C_SLV1                    0x29
#define MPUIMU_REG_I2C_SLV1_CTRL               0x2A
#define MPUIMU_REG_I2C_SLV2_ADDR               0x2B
#define MPUIMU_REG_I2C_SLV2                    0x2C
#define MPUIMU_REG_I2C_SLV2_CTRL               0x2D
#define MPUIMU_REG_I2C_SLV3_ADDR               0x2E
#define MPUIMU_REG_I2C_SLV3                    0x2F
#define MPUIMU_REG_I2C_SLV3_CTRL               0x30
#define MPUIMU_REG_I2C_SLV4_ADDR               0x31
#define MPUIMU_REG_I2C_SLV4                    0x32
#define MPUIMU_REG_I2C_SLV4_DO                 0x33
#define MPUIMU_REG_I2C_SLV4_CTRL               0x34
#define MPUIMU_REG_I2C_SLV4_DI                 0x35
#define MPUIMU_REG_I2C_MST_STATUS              0x36
#define MPUIMU_REG_I2C_SLV0_DO                 0x63
#define MPUIMU_REG_I2C_SLV1_DO                 0x64
#define MPUIMU_REG_I2C_SLV2_DO                 0x65
#define MPUIMU_REG_I2C_SLV3_DO                 0x66
#define MPUIMU_REG_I2C_MST_DELAY_CT            0x67
#define MPUIMU_REG_INT_PIN_CFG                 0x37
#define MPUIMU_REG_INT_ENABLE                  0x38
#define MPUIMU_REG_INT_STATUS                  0x3A
#define MPUIMU_REG_SIGNAL_PATH_RES             0x68
#define MPUIMU_REG_MOT_DETECT_CTRL             0x69
#define MPUIMU_REG_USER_CTRL                   0x6A
#define MPUIMU_REG_PWR_MGMT_1                  0x6B
#define MPUIMU_REG_PWR_MGMT_2                  0x6C
#define MPUIMU_REG_FIFO_EN                     0x23
#define MPUIMU_REG_FIFO_COUNTH                 0x72
#define MPUIMU_REG_FIFO_COUNTL                 0x73
#define MPUIMU_REG_FIFO_R_W                    0x74
#define MPUIMU_REG_WHO_AM_I                    0x75 
/** \} */

/**
 * \defgroup cfg_reg Config registers
 * \{
 */
#define MPUIMU_CFG_CONFIG                      0x1A
#define MPUIMU_CFG_RAW_ACCEL                   0x3B
#define MPUIMU_CFG_RAW_GYRO                    0x43
#define MPUIMU_CFG_STANDARD_GYRO               0x1B
#define MPUIMU_CFG_STANDARD_ACCEL              0x1C
#define MPUIMU_CFG_PWR                         0x80
#define MPUIMU_CFG_PWR_SET                     0x00
#define MPUIMU_CFG_FIFO_ENABLE                 0x78
#define MPUIMU_CFG_INT_ENABLE                  0x10
/** \} */

/**
 * \defgroup ext_data Data registers
 * \{
 */
#define MPUIMU_EXT_SENS_DATA_00                0x49
#define MPUIMU_EXT_SENS_DATA_01                0x4A
#define MPUIMU_EXT_SENS_DATA_02                0x4B
#define MPUIMU_EXT_SENS_DATA_03                0x4C
#define MPUIMU_EXT_SENS_DATA_04                0x4D
#define MPUIMU_EXT_SENS_DATA_05                0x4E
#define MPUIMU_EXT_SENS_DATA_06                0x4F
#define MPUIMU_EXT_SENS_DATA_07                0x50
#define MPUIMU_EXT_SENS_DATA_08                0x51
#define MPUIMU_EXT_SENS_DATA_11                0x54
#define MPUIMU_EXT_SENS_DATA_09                0x52
#define MPUIMU_EXT_SENS_DATA_10                0x53
#define MPUIMU_EXT_SENS_DATA_12                0x55
#define MPUIMU_EXT_SENS_DATA_13                0x56
#define MPUIMU_EXT_SENS_DATA_14                0x57
#define MPUIMU_EXT_SENS_DATA_15                0x58
#define MPUIMU_EXT_SENS_DATA_16                0x59
#define MPUIMU_EXT_SENS_DATA_17                0x5A
#define MPUIMU_EXT_SENS_DATA_18                0x5B
#define MPUIMU_EXT_SENS_DATA_19                0x5C
#define MPUIMU_EXT_SENS_DATA_20                0x5D
#define MPUIMU_EXT_SENS_DATA_21                0x5E
#define MPUIMU_EXT_SENS_DATA_22                0x5F
#define MPUIMU_EXT_SENS_DATA_23                0x60
/** \} */

/**
 * \defgroup output Output registers
 * \{
 */

// GYRO

#define MPUIMU_GYRO_XOUT_H                     0x43
#define MPUIMU_GYRO_XOUT_L                     0x44
#define MPUIMU_GYRO_YOUT_H                     0x45
#define MPUIMU_GYRO_YOUT_L                     0x46
#define MPUIMU_GYRO_ZOUT_H                     0x47
#define MPUIMU_GYRO_ZOUT_L                     0x48

// ACCEL

#define MPUIMU_ACCEL_XOUT_H                    0x3B
#define MPUIMU_ACCEL_XOUT_L                    0x3C
#define MPUIMU_ACCEL_YOUT_H                    0x3D
#define MPUIMU_ACCEL_YOUT_L                    0x3E
#define MPUIMU_ACCEL_ZOUT_H                    0x3F
#define MPUIMU_ACCEL_ZOUT_L                    0x40

// TEMP

#define MPUIMU_TEMP_OUT_H                      0x41
#define MPUIMU_TEMP_OUT_L                      0x42
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
typedef uint8_t  mpuimu_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *mpuimu_master_io_t )( struct mpuimu_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct mpuimu_s
{
    // Output pins 

    digital_out_t cs;
    digital_out_t fsy;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    mpuimu_master_io_t  write_f;
    mpuimu_master_io_t  read_f;
    mpuimu_select_t master_sel;

} mpuimu_t;

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

    pin_name_t fsy;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    mpuimu_select_t sel;

} mpuimu_cfg_t;

/**
 * \defgroup data_measure Measurement data
 * \{
 */
typedef struct
{
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    
} mpuimu_accel_data_t;

/**
 * @brief Gyro data object definition.
 */
typedef struct
{
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;

} mpuimu_gyro_data_t;

/** \} */ // Measurement data

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
 * @param cfg    Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void mpuimu_cfg_setup ( mpuimu_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx    Click object.
 * @param cfg    Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MPUIMU_RETVAL mpuimu_init ( mpuimu_t *ctx, mpuimu_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx    Click object.
 *
 * @description This function executes default configuration for MPU IMU Click.
 * @note
 *    Click default configuration:
 * -------------------------------
 * <pre>
 *    Enables Accel and Gyro data registers to be written into the FIFO buffer.
 * </pre>
 * 
 * <pre>
 *    Enables that FIFO buffer overflow will generate an interrupt.
 * </pre>
 */
void mpuimu_default_cfg ( mpuimu_t *ctx );

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
void mpuimu_generic_write ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx         Click object.
 * @param reg         Register address.
 * @param data_buf    Data buf to be written.
 * @param len         Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void mpuimu_generic_read ( mpuimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief High register data function.
 *
 * @param ctx            Click object.
 * @param adr_reg_high   High data register address.
 *
 * @return
 * 16-bit value ( high data )
 *
 * @description This function get data from MPU-6000 register.
 */
int16_t mpuimu_get_axis ( mpuimu_t *ctx, uint8_t adr_reg_high );

/**
 * @brief Read Axis function.
 *
 * @param ctx            Click object.
 * @param accel_data     Pointer to structure where Accel data be stored.
 *
 * @description This function read Accel X-axis, Y-axis and Z-axis.
 */
void mpuimu_read_accel ( mpuimu_t *ctx, mpuimu_accel_data_t *accel_data );

/**
 * @brief Read Axis function.
 *
 * @param ctx            Click object.
 * @param gyro_data      Pointer to structure where Gyro data be stored.
 *
 * @description This function read Gyro X-axis, Y-axis and Z-axis.
 */
void mpuimu_read_gyro ( mpuimu_t *ctx, mpuimu_gyro_data_t *gyro_data );

/**
 * @brief Temperature read function.
 *
 * @param ctx            Click object.
 *
 * @return
 * Temperature in degrees [ C ]
 *
 * @description This function reads temperature data.
 */
float mpuimu_read_temperature ( mpuimu_t *ctx );

/**
 * @brief Software reset function.
 *
 * @param ctx            Click object.
 *
 * @description This function performs software reset.
 */
void software_reset ( mpuimu_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MPUIMU_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
