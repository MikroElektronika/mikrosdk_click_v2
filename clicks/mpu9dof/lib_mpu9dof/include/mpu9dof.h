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
 * \brief This file contains API for MPU 9DOF Click driver.
 *
 * \addtogroup mpu9dof MPU 9DOF Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MPU9DOF_H
#define MPU9DOF_H

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
#define MPU9DOF_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.fsy = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MPU9DOF_RETVAL  uint8_t

#define MPU9DOF_OK           0x00
#define MPU9DOF_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address MPU9150A I2C address
 * \{
 */
#define MPU9DOF_XLG_I2C_ADDR_1                    0x69  //Device address jumper pos 1 (0xD2 >> 1)
#define MPU9DOF_XLG_I2C_ADDR_0                    0x68  //Device address jumper pos 0
#define MPU9DOF_M_I2C_ADDR_0                      0x0C  // Address of the magnetometer in bypass mode
#define MPU9DOF_M_I2C_ADDR_1                      0x0D
/** \} */

/**
 * \defgroup magnetometer_registers Magnetometer Registers
 * \{
 */
#define MPU9DOF_WHO_AM_I_MAG                      0x00  // should return = 0x48
#define MPU9DOF_INFO                              0x01
#define MPU9DOF_MAG_ST1                           0x02  // data ready status bit 0
#define MPU9DOF_MAG_ADDRESS                       0x0C
#define MPU9DOF_MAG_XOUT_L                        0x03  // data
#define MPU9DOF_MAG_XOUT_H                        0x04
#define MPU9DOF_MAG_YOUT_L                        0x05
#define MPU9DOF_MAG_YOUT_H                        0x06
#define MPU9DOF_MAG_ZOUT_L                        0x07
#define MPU9DOF_MAG_ZOUT_H                        0x08
#define MPU9DOF_MAG_ST2                           0x09  // Data overflow bit 3 and data read error status bit 2
#define MPU9DOF_MAG_CNTL                          0x0A  // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define MPU9DOF_MAG_ASTC                          0x0C  // Self test control
#define MPU9DOF_MAG_ASAX                          0x10  // Fuse ROM x-axis sensitivity adjustment value
#define MPU9DOF_MAG_ASAY                          0x11  // Fuse ROM y-axis sensitivity adjustment value
#define MPU9DOF_MAG_ASAZ                          0x12  // Fuse ROM z-axis sensitivity adjustment value

#define MPU9DOF_XGOFFS_TC                         0x00  // Bit 7 PWR_MODE, bits 6:1 XG_OFFS_TC, bit 0 OTP_BNK_VLD
#define MPU9DOF_YGOFFS_TC                         0x01
#define MPU9DOF_ZGOFFS_TC                         0x02
#define MPU9DOF_X_FINE_GAIN                       0x03  // [7:0] fine gain
#define MPU9DOF_Y_FINE_GAIN                       0x04
#define MPU9DOF_Z_FINE_GAIN                       0x05
#define MPU9DOF_XA_OFFSET_H                       0x06  // User-defined trim values for accelerometer
#define MPU9DOF_XA_OFFSET_L_TC                    0x07
#define MPU9DOF_YA_OFFSET_H                       0x08
#define MPU9DOF_YA_OFFSET_L_TC                    0x09
#define MPU9DOF_ZA_OFFSET_H                       0x0A
#define MPU9DOF_ZA_OFFSET_L_TC                    0x0B
#define MPU9DOF_SELF_TEST_X                       0x0D
#define MPU9DOF_SELF_TEST_Y                       0x0E
#define MPU9DOF_SELF_TEST_Z                       0x0F
#define MPU9DOF_SELF_TEST_A                       0x10
#define MPU9DOF_XG_OFFS_USRH                      0x13  // User-defined trim values for gyroscope, populate with calibration routine
#define MPU9DOF_XG_OFFS_USRL                      0x14
#define MPU9DOF_YG_OFFS_USRH                      0x15
#define MPU9DOF_YG_OFFS_USRL                      0x16
#define MPU9DOF_ZG_OFFS_USRH                      0x17
#define MPU9DOF_ZG_OFFS_USRL                      0x18
#define MPU9DOF_SMPLRT_DIV                        0x19
#define MPU9DOF_CONFIG                            0x1A
#define MPU9DOF_GYRO_CONFIG                       0x1B
#define MPU9DOF_ACCEL_CONFIG                      0x1C
#define MPU9DOF_FF_THR                            0x1D  // Free-fall
#define MPU9DOF_FF_DUR                            0x1E  // Free-fall
#define MPU9DOF_MOT_THR                           0x1F  // Motion detection threshold bits [7:0]
#define MPU9DOF_MOT_DUR                           0x20  // Duration counter threshold for motion interrupt generation, 1 kHz rate, LSB = 1 ms
#define MPU9DOF_ZMOT_THR                          0x21  // Zero-motion detection threshold bits [7:0]
#define MPU9DOF_ZRMOT_DUR                         0x22  // Duration counter threshold for zero motion interrupt generation, 16 Hz rate, LSB = 64 ms
#define MPU9DOF_FIFO_EN                           0x23
#define MPU9DOF_I2C_MST_CTRL                      0x24
#define MPU9DOF_I2C_SLV0_ADDR                     0x25
#define MPU9DOF_I2C_SLV0_REG                      0x26
#define MPU9DOF_I2C_SLV0_CTRL                     0x27
#define MPU9DOF_I2C_SLV1_ADDR                     0x28
#define MPU9DOF_I2C_SLV1_REG                      0x29
#define MPU9DOF_I2C_SLV1_CTRL                     0x2A
#define MPU9DOF_I2C_SLV2_ADDR                     0x2B
#define MPU9DOF_I2C_SLV2_REG                      0x2C
#define MPU9DOF_I2C_SLV2_CTRL                     0x2D
#define MPU9DOF_I2C_SLV3_ADDR                     0x2E
#define MPU9DOF_I2C_SLV3_REG                      0x2F
#define MPU9DOF_I2C_SLV3_CTRL                     0x30
#define MPU9DOF_I2C_SLV4_ADDR                     0x31
#define MPU9DOF_I2C_SLV4_REG                      0x32
#define MPU9DOF_I2C_SLV4_DO                       0x33
#define MPU9DOF_I2C_SLV4_CTRL                     0x34
#define MPU9DOF_I2C_SLV4_DI                       0x35
#define MPU9DOF_I2C_MST_STATUS                    0x36
#define MPU9DOF_INT_PIN_CFG                       0x37
#define MPU9DOF_INT_ENABLE                        0x38
#define MPU9DOF_DMP_INT_STATUS                    0x39  // Check DMP interrupt
#define MPU9DOF_INT_STATUS                        0x3A
#define MPU9DOF_ACCEL_XOUT_H                      0x3B
#define MPU9DOF_ACCEL_XOUT_L                      0x3C
#define MPU9DOF_ACCEL_YOUT_H                      0x3D
#define MPU9DOF_ACCEL_YOUT_L                      0x3E
#define MPU9DOF_ACCEL_ZOUT_H                      0x3F
#define MPU9DOF_ACCEL_ZOUT_L                      0x40
#define MPU9DOF_TEMP_OUT_H                        0x41
#define MPU9DOF_TEMP_OUT_L                        0x42
#define MPU9DOF_GYRO_XOUT_H                       0x43
#define MPU9DOF_GYRO_XOUT_L                       0x44
#define MPU9DOF_GYRO_YOUT_H                       0x45
#define MPU9DOF_GYRO_YOUT_L                       0x46
#define MPU9DOF_GYRO_ZOUT_H                       0x47
#define MPU9DOF_GYRO_ZOUT_L                       0x48
#define MPU9DOF_EXT_SENS_DATA_00                  0x49
#define MPU9DOF_EXT_SENS_DATA_01                  0x4A
#define MPU9DOF_EXT_SENS_DATA_02                  0x4B
#define MPU9DOF_EXT_SENS_DATA_03                  0x4C
#define MPU9DOF_EXT_SENS_DATA_04                  0x4D
#define MPU9DOF_EXT_SENS_DATA_05                  0x4E
#define MPU9DOF_EXT_SENS_DATA_06                  0x4F
#define MPU9DOF_EXT_SENS_DATA_07                  0x50
#define MPU9DOF_EXT_SENS_DATA_08                  0x51
#define MPU9DOF_EXT_SENS_DATA_09                  0x52
#define MPU9DOF_EXT_SENS_DATA_10                  0x53
#define MPU9DOF_EXT_SENS_DATA_11                  0x54
#define MPU9DOF_EXT_SENS_DATA_12                  0x55
#define MPU9DOF_EXT_SENS_DATA_13                  0x56
#define MPU9DOF_EXT_SENS_DATA_14                  0x57
#define MPU9DOF_EXT_SENS_DATA_15                  0x58
#define MPU9DOF_EXT_SENS_DATA_16                  0x59
#define MPU9DOF_EXT_SENS_DATA_17                  0x5A
#define MPU9DOF_EXT_SENS_DATA_18                  0x5B
#define MPU9DOF_EXT_SENS_DATA_19                  0x5C
#define MPU9DOF_EXT_SENS_DATA_20                  0x5D
#define MPU9DOF_EXT_SENS_DATA_21                  0x5E
#define MPU9DOF_EXT_SENS_DATA_22                  0x5F
#define MPU9DOF_EXT_SENS_DATA_23                  0x60
#define MPU9DOF_MOT_DETECT_STATUS                 0x61
#define MPU9DOF_I2C_SLV0_DO                       0x63
#define MPU9DOF_I2C_SLV1_DO                       0x64
#define MPU9DOF_I2C_SLV2_DO                       0x65
#define MPU9DOF_I2C_SLV3_DO                       0x66
#define MPU9DOF_I2C_MST_DELAY_CTRL                0x67
#define MPU9DOF_SIGNAL_PATH_RESET                 0x68
#define MPU9DOF_MOT_DETECT_CTRL                   0x69
#define MPU9DOF_USER_CTRL                         0x6A  // Bit 7 enable DMP, bit 3 reset DMP
#define MPU9DOF_PWR_MGMT_1                        0x6B  // Device defaults to the SLEEP mode
#define MPU9DOF_PWR_MGMT_2                        0x6C
#define MPU9DOF_DMP_BANK                          0x6D  // Activates a specific bank in the DMP
#define MPU9DOF_DMP_RW_PNT                        0x6E  // Set read/write pointer to a specific start address in specified DMP bank
#define MPU9DOF_DMP_REG                           0x6F  // Register in DMP from which to read or to which to write
#define MPU9DOF_DMP_REG_1                         0x70
#define MPU9DOF_DMP_REG_2                         0x71
#define MPU9DOF_FIFO_COUNTH                       0x72
#define MPU9DOF_FIFO_COUNTL                       0x73
#define MPU9DOF_FIFO_R_W                          0x74
#define MPU9DOF_WHO_AM_I_XLG                      0x75  // Should return = 0x68
/** \} */

/**
 * \defgroup cfg_bits Configuration bits
 * \{
 */
#define MPU9DOF_BIT_SLEEP                         0x40
#define MPU9DOF_BIT_H_RESET                       0x80
#define MPU9DOF_BITS_CLKSEL                       0x07
#define MPU9DOF_MPU_CLK_SEL_PLLGYROX              0x01
#define MPU9DOF_MPU_CLK_SEL_PLLGYROZ              0x03
#define MPU9DOF_MPU_EXT_SYNC_GYROX                0x02
#define MPU9DOF_BITS_AFSL_SEL_2G                  0x00
#define MPU9DOF_BITS_AFSL_SEL_4G                  0x08
#define MPU9DOF_BITS_AFSL_SEL_8G                  0x10
#define MPU9DOF_BITS_AFSL_SEL_16G                 0x18
#define MPU9DOF_BITS_FS_250DPS                    0x00
#define MPU9DOF_BITS_FS_500DPS                    0x08
#define MPU9DOF_BITS_FS_1000DPS                   0x10
#define MPU9DOF_BITS_FS_2000DPS                   0x18
#define MPU9DOF_BITS_FS_MASK                      0x18
#define MPU9DOF_BITS_DLPF_CFG_256HZ_NOLPF2        0x00
#define MPU9DOF_BITS_DLPF_CFG_188HZ               0x01
#define MPU9DOF_BITS_DLPF_CFG_98HZ                0x02
#define MPU9DOF_BITS_DLPF_CFG_42HZ                0x03
#define MPU9DOF_BITS_DLPF_CFG_20HZ                0x04
#define MPU9DOF_BITS_DLPF_CFG_10HZ                0x05
#define MPU9DOF_BITS_DLPF_CFG_5HZ                 0x06
#define MPU9DOF_BITS_DLPF_CFG_2100HZ_NOLPF        0x07
#define MPU9DOF_BITS_DLPF_CFG_MASK                0x07
#define MPU9DOF_BIT_INT_ANYRD_2CLEAR              0x10
#define MPU9DOF_BIT_RAW_RDY_EN                    0x01
#define MPU9DOF_BIT_I2C_IF_DIS                    0x10
#define MPU9DOF_BIT_INT_PIN_CFG                   0x02
#define MPU9DOF_BIT_FIFO_EN                       0x78
#define MPU9DOF_BIT_FIFO_DIS                      0x00
#define MPU9DOF_DEFAULT                           0x00
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

    digital_out_t fsy;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    uint8_t magnetometer_address;

} mpu9dof_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t fsy;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint8_t i2c_mag_address;

} mpu9dof_cfg_t;

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
void mpu9dof_cfg_setup ( mpu9dof_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mpu9dof Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MPU9DOF_RETVAL mpu9dof_init ( mpu9dof_t *ctx, mpu9dof_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Mpu9Dof click.
 */
void mpu9dof_default_cfg ( mpu9dof_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void mpu9dof_generic_write ( mpu9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void mpu9dof_generic_read ( mpu9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write data function
 *
 * @param ctx             Click object.
 * @param address         Register address.
 * @param write_command   Command to write.
 *
 * @description Function write byte of data to MPU-9150 MAG
 */
void mpu9dof_write_data_mag ( mpu9dof_t *ctx, uint8_t address, uint8_t write_command );

/**
 * @brief Generic read data function
 *
 * @param ctx             Click object.
 * @param address         Register address.
 *
 * @returns    Data from addressed register in MPU-9150 MAG
 *
 * @description Function read byte of data from register address of MPU-9150 MAG
 */
uint8_t mpu9dof_read_data_mag ( mpu9dof_t *ctx, uint8_t address );

/**
 * @brief Function get low and high register data
 *
 * @param ctx             Click object.
 * @param adr_reg_high    High data register address.
 *
 * @returns         16-bit value ( low and high data )
 *
 * @description Function get data from two MPU-9150 XL G register
 */
int16_t mpu9dof_get_axis ( mpu9dof_t *ctx, uint8_t adr_reg_high );

/**
 * @brief Function get low and high register data
 *
 * @param ctx             Click object.
 * @param adr_reg_low     Low data register address.
 *
 * @returns         16-bit value ( low and high data )
 *
 * @description Function get data from two MPU-9150 MAG register
 */
int16_t mpu9dof_get_axis_mag ( mpu9dof_t *ctx, uint8_t adr_reg_low );

/**
 * @brief Function read axis
 *
 * @param ctx             Click object.
 * @param gyroX           Pointer to read Gyro X-axis data
 * @param gyroY           Pointer to read Gyro Y-axis data
 * @param gyroZ           Pointer to read Gyro Z-axis data
 *
 * @description Function read Gyro X-axis, Y-axis and Z-axis axis.
 */
void mpu9dof_read_gyro ( mpu9dof_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );

/**
 * @brief Function read axis
 *
 * @param ctx             Click object.
 * @param gyroX           Pointer to read Gyro X-axis data
 * @param gyroY           Pointer to read Gyro Y-axis data
 * @param gyroZ           Pointer to read Gyro Z-axis data
 *
 * @description Function read Gyro X-axis, Y-axis and Z-axis axis.
 */
void mpu9dof_read_accel ( mpu9dof_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );

/**
 * @brief Function read axis
 *
 * @param ctx             Click object.
 * @param magX            Pointer to read Accel X-axis data
 * @param magY            Pointer to read Accel Y-axis data
 * @param magZ            Pointer to read Accel Z-axis data
 *
 * @description Function read Magnetometar X-axis, Y-axis and Z-axis axis.
 */
void mpu9dof_read_mag ( mpu9dof_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z );

/**
 * @brief Function read temperature data in degrees [ �C ]
 *
 * @param ctx             Click object.
 *
 * @returns               Temperature in degrees [ �C ]
 *
 * @description Function read temperature data
 */
float mpu9dof_read_temperature ( mpu9dof_t *ctx );

/**
 * @brief Get int pin state
 *
 * @param ctx             Click object.
 *
 * @returns               Int_pin state
 *
 * @description Function read int_pin state.
 */
uint8_t get_int_pin_state ( mpu9dof_t *ctx );

/**
 * @brief Turn FSY on function
 *
 * @param ctx             Click object.
 *
 * @description Function is used to set FSY pin to 1.
**/
void adapter_turn_fsy_on ( mpu9dof_t *ctx );

/**
 * @brief Turn FSY off function
 *
 * @param ctx             Click object.
 *
 * @description Function is used to set FSY pin to 0.
**/
void adapter_turn_fsy_off ( mpu9dof_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MPU9DOF_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
