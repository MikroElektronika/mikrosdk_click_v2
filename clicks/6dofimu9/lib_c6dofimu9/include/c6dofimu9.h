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
 * \brief This file contains API for 6DOF IMU 9 Click driver.
 *
 * \addtogroup c6dofimu9 6DOF IMU 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU9_H
#define C6DOFIMU9_H

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

#define C6DOFIMU9_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.syn = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C6DOFIMU9_MASTER_I2C 0
#define C6DOFIMU9_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU9_RETVAL  uint8_t


#define C6DOFIMU9_OK           0x00
#define C6DOFIMU9_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define C6DOFIMU9_I2C_SLAVE_ADDRESS_0                               0x68
#define C6DOFIMU9_I2C_SLAVE_ADDRESS_1                               0x69
/** \} */

/**
 * \defgroup spi_command Spi command
 * \{
 */
#define C6DOFIMU9_SPI_WRITE_CMD                                     0x00
#define C6DOFIMU9_SPI_READ_CMD                                      0x80
/** \} */

/**
 * \defgroup Register Map
 * \{
 */
#define C6DOFIMU9_REG_SELF_TEST_X_GYRO                              0x00
#define C6DOFIMU9_REG_SELF_TEST_Y_GYRO                              0x01
#define C6DOFIMU9_REG_SELF_TEST_Z_GYRO                              0x02
#define C6DOFIMU9_REG_SELF_TEST_X_ACCEL                             0x0D
#define C6DOFIMU9_REG_SELF_TEST_Y_ACCEL                             0x0E
#define C6DOFIMU9_REG_SELF_TEST_Z_ACCEL                             0x0F
#define C6DOFIMU9_REG_XG_OFFS_USRH                                  0x13
#define C6DOFIMU9_REG_XG_OFFS_USRL                                  0x14
#define C6DOFIMU9_REG_YG_OFFS_USRH                                  0x15
#define C6DOFIMU9_REG_YG_OFFS_USRL                                  0x16
#define C6DOFIMU9_REG_ZG_OFFS_USRH                                  0x17
#define C6DOFIMU9_REG_ZG_OFFS_USRL                                  0x18
#define C6DOFIMU9_REG_SMPLRT_DIV                                    0x19
#define C6DOFIMU9_REG_CONFIG                                        0x1A
#define C6DOFIMU9_REG_GYRO_CONFIG                                   0x1B
#define C6DOFIMU9_REG_ACCEL_CONFIG                                  0x1C
#define C6DOFIMU9_REG_ACCEL_CONFIG_2                                0x1D
#define C6DOFIMU9_REG_LP_MODE_CFG                                   0x1E
#define C6DOFIMU9_REG_ACCEL_WOM_THR                                 0x1F
#define C6DOFIMU9_REG_FIFO_EN                                       0x23
#define C6DOFIMU9_REG_FSYNC_INT                                     0x36
#define C6DOFIMU9_REG_INT_PIN_CFG                                   0x37
#define C6DOFIMU9_REG_INT_ENABLE                                    0x38
#define C6DOFIMU9_REG_INT_STATUS                                    0x3A
#define C6DOFIMU9_REG_ACCEL_XOUT_H                                  0x3B
#define C6DOFIMU9_REG_ACCEL_XOUT_L                                  0x3C
#define C6DOFIMU9_REG_ACCEL_YOUT_H                                  0x3D
#define C6DOFIMU9_REG_ACCEL_YOUT_L                                  0x3E
#define C6DOFIMU9_REG_ACCEL_ZOUT_H                                  0x3F
#define C6DOFIMU9_REG_ACCEL_ZOUT_L                                  0x40
#define C6DOFIMU9_REG_TEMP_OUT_H                                    0x41
#define C6DOFIMU9_REG_TEMP_OUT_L                                    0x42
#define C6DOFIMU9_REG_GYRO_XOUT_H                                   0x43
#define C6DOFIMU9_REG_GYRO_XOUT_L                                   0x44
#define C6DOFIMU9_REG_GYRO_YOUT_H                                   0x45
#define C6DOFIMU9_REG_GYRO_YOUT_L                                   0x46
#define C6DOFIMU9_REG_GYRO_ZOUT_H                                   0x47
#define C6DOFIMU9_REG_GYRO_ZOUT_L                                   0x48
#define C6DOFIMU9_REG_SIGNAL_PATH_RESET                             0x68
#define C6DOFIMU9_REG_ACCEL_INTEL_CTRL                              0x69
#define C6DOFIMU9_REG_USER_CTRL                                     0x6A
#define C6DOFIMU9_REG_PWR_MGMT_1                                    0x6B
#define C6DOFIMU9_REG_PWR_MGMT_2                                    0x6C
#define C6DOFIMU9_REG_FIFO_COUNTH                                   0x72
#define C6DOFIMU9_REG_FIFO_COUNTL                                   0x73
#define C6DOFIMU9_REG_FIFO_R_W                                      0x74
#define C6DOFIMU9_REG_WHO_AM_I                                      0x75
#define C6DOFIMU9_REG_XA_OFFSET_H                                   0x77
#define C6DOFIMU9_REG_XA_OFFSET_L                                   0x78
#define C6DOFIMU9_REG_YA_OFFSET_H                                   0x7A
#define C6DOFIMU9_REG_YA_OFFSET_L                                   0x7B
#define C6DOFIMU9_REG_ZA_OFFSET_H                                   0x7D
#define C6DOFIMU9_REG_ZA_OFFSET_L                                   0x7E
/** \} */

/**
 * \defgroup configuration Configuration
 * \{
 */
#define C6DOFIMU9_BM_FIFO_MODE_FULL_REPLACE_OLD_DATA                0x00
#define C6DOFIMU9_BM_FIFO_MODE_FULL_NO_WRITE_DATA                   0x40
#define C6DOFIMU9_BM_DISABLE_FSYNC_PIN                              0x00
#define C6DOFIMU9_BM_ENABLE_FSYNC_PIN_TEMP_OUT_L                    0x08
#define C6DOFIMU9_BM_ENABLE_FSYNC_PIN_GYRO_XOUT_L                   0x10
#define C6DOFIMU9_BM_ENABLE_FSYNC_PIN_GYRO_YOUT_L                   0x18
#define C6DOFIMU9_BM_ENABLE_FSYNC_PIN_GYRO_ZOUT_L                   0x20
#define C6DOFIMU9_BM_ENABLE_FSYNC_PIN_ACCEL_XOUT_L                  0x28
#define C6DOFIMU9_BM_ENABLE_FSYNC_PIN_ACCEL_YOUT_L                  0x30
#define C6DOFIMU9_BM_ENABLE_FSYNC_PIN_ACCEL_ZOUT_L                  0x38
/** \} */

/**
 * \defgroup gyro_configuration  Gyro configuration
 * \{
 */
/* Gyro configuration */
#define C6DOFIMU9_GYRO_FULL_SCALE_250dps                           0x00FA
#define C6DOFIMU9_GYRO_FULL_SCALE_500dps                           0x01F4
#define C6DOFIMU9_GYRO_FULL_SCALE_1000dps                          0x03E8
#define C6DOFIMU9_GYRO_FULL_SCALE_2000dps                          0x07D0
/** \} */

/**
 * \defgroup accel_configuration  Accel configuration
 * \{
 */
#define C6DOFIMU9_ACCEL_FULL_SCALE_2g                               0x02
#define C6DOFIMU9_ACCEL_FULL_SCALE_4g                               0x04
#define C6DOFIMU9_ACCEL_FULL_SCALE_8g                               0x08
#define C6DOFIMU9_ACCEL_FULL_SCALE_16g                              0x10
#define C6DOFIMU9_ACCEL_AVERAGE_4_SAMPLES                           0x04
#define C6DOFIMU9_ACCEL_AVERAGE_8_SAMPLES                           0x08
#define C6DOFIMU9_ACCEL_AVERAGE_16_SAMPLES                          0x10
#define C6DOFIMU9_ACCEL_AVERAGE_32_SAMPLES                          0x20
/** \} */

/**
 * \defgroup low_power_mode_configuration  Low power mode configuration
 * \{
 */
#define C6DOFIMU9_GYRO_AVERAGE_1x                                   0x01
#define C6DOFIMU9_GYRO_AVERAGE_2x                                   0x02
#define C6DOFIMU9_GYRO_AVERAGE_4x                                   0x04
#define C6DOFIMU9_GYRO_AVERAGE_8x                                   0x08
#define C6DOFIMU9_GYRO_AVERAGE_16x                                  0x10
#define C6DOFIMU9_GYRO_AVERAGE_32x                                  0x20
#define C6DOFIMU9_GYRO_AVERAGE_64x                                  0x40
#define C6DOFIMU9_GYRO_AVERAGE_128x                                 0x80
/** \} */

/**
 * \defgroup bit_mask_fifo_enable  Bit mask FIFO enable
 * \{
 */
#define C6DOFIMU9_BM_DISABLE_TEMP_FIFO                              0x00
#define C6DOFIMU9_BM_ENABLE_TEMP_FIFO                               0x80
#define C6DOFIMU9_BM_DISABLE_XGYRO_FIFO                             0x00
#define C6DOFIMU9_BM_ENABLE_XGYRO_FIFO                              0x40
#define C6DOFIMU9_BM_DISABLE_YGYRO_FIFO                             0x00
#define C6DOFIMU9_BM_ENABLE_YGYRO_FIFO                              0x20
#define C6DOFIMU9_BM_DISABLE_ZGYRO_FIFO                             0x00
#define C6DOFIMU9_BM_ENABLE_ZGYRO_FIFO                              0x10
#define C6DOFIMU9_BM_DISABLE_ACCEL_FIFO                             0x00
#define C6DOFIMU9_BM_ENABLE_ACCEL_FIFO                              0x08
/** \} */

/**
 * \defgroup device_id  Device ID
 * \{
 */
#define C6DOFIMU9_DEVICE_ID                                         0xA9
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
typedef uint8_t  c6dofimu9_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c6dofimu9_master_io_t )( struct c6dofimu9_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu9_s
{
    // Output pins 

    digital_out_t syn;
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    c6dofimu9_master_io_t  write_f;
    c6dofimu9_master_io_t  read_f;
    c6dofimu9_select_t master_sel;

} c6dofimu9_t;

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

    pin_name_t syn;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

   c6dofimu9_select_t sel;

} c6dofimu9_cfg_t;

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
void c6dofimu9_cfg_setup ( c6dofimu9_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c6dofimu9 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU9_RETVAL c6dofimu9_init ( c6dofimu9_t *ctx, c6dofimu9_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 6DOF IMU 9 click.
 */
void c6dofimu9_default_cfg ( c6dofimu9_t *ctx );

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
void c6dofimu9_generic_write ( c6dofimu9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void c6dofimu9_generic_read ( c6dofimu9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Check interrupt state function
 *
 * @param ctx      Click object.
 *
 * @return
 * Interrupt state:
 * - 0 : No active;
 * - 1 : Active; 
 * @description  Function check interrupt state by return state of the INT pin of 6DOF IMU 9 Click board.
 */
uint8_t c6dofimu9_check_interrupt ( c6dofimu9_t *ctx );

/**
 * @brief Set configuration function
 *
 * @param ctx      Click object.
 * @param config_data          Register address.
 *
 * @note
 *<pre>
 * - [ bit 7 ]     : Always set to 0;
 * - [ bit 6 ]     : FIFO is full:
 *                   - 0 : Additional writes will be written to the FIFO, replacing the oldest data;
 *                   - 1 : Additional writes will not be written to FIFO;
 * - [ bit 5 : 3 ] : Enables the FSYNC pin data to be sampled:
 *                   - 0 : Function disabled;
 *                   - 1 : TEMP_OUT_L;
 *                   - 2 : GYRO_XOUT_L;
 *                   - 3 : GYRO_YOUT_L;
 *                   - 4 : GYRO_ZOUT_L;
 *                   - 5 : ACCEL_XOUT_L;
 *                   - 6 : ACCEL_YOUT_L;
 *                   - 7 : ACCEL_ZOUT_L;
 * - [ bit 2 : 0 ] : For the DLPF to be used;
 *</pre>
 *
 * @description Function set configuration data to the targeted C6DOFIMU9_REG_CONFIG register address of
 * IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_set_config ( c6dofimu9_t *ctx, uint8_t config_data );

/**
 * @brief Set Gyro configuration function
 *
 * @param ctx      Click object.
 * @param gyro_config_data
 *
 * @note
 *<pre>
 * - [ bit 7 ]     : X Gyro self-test;
 * - [ bit 6 ]     : Y Gyro self-test;
 * - [ bit 5 ]     : Z Gyro self-test;
 * - [ bit 4 : 3 ] : Gyro Full Scale Select:
 *                   - 0 : � 250 dps;
 *                   - 1 : � 500 dps;
 *                   - 2 : �1000 dps;
 *                   - 3 : �2000 dps;
 * - [ bit 2 ]     : Reserved;
 * - [ bit 1 : 0 ] : Used to bypass DLPF as shown in Table 16 above;
 *</pre>
 *
 * @description Function set Gyro configuration data to the targeted C6DOFIMU9_REG_GYRO_CONFIG register address of
 * IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_set_gyro_config ( c6dofimu9_t *ctx, uint8_t gyro_config_data );

/**
 * @brief Set Gyro measurement range configuration function
 *
 * @param ctx      Click object.
 * @param gyro_full_scale_range
 * @note
 *<pre>
 * -  250 : Gyro Full Scale Select � 250 dps;
 * -  500 : Gyro Full Scale Select � 500 dps;
 * - 1000 : Gyro Full Scale Select �1000 dps;
 * - 2000 : Gyro Full Scale Select �2000 dps;
 *</pre>
 *
 * @description Function set Gyro configuration data to the targeted C6DOFIMU9_REG_GYRO_CONFIG register address of
 * IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_set_gyro_measurement_range ( c6dofimu9_t *ctx, uint16_t gyro_full_scale_range );

/**
 * @brief Set Accel configuration function
 *
 * @param ctx      Click object.
 * @param accel_config_data          
 *
 * @note
 *<pre>
 * - [ bit 15 ]      : X Accel self-test;
 * - [ bit 14 ]      : Y Accel self-test;
 * - [ bit 13 ]      : Z Accel self-test;
 * - [ bit 12 : 11 ] : Accel Full Scale Select:
 *                     - 0 : � 2g;
 *                     - 1 : � 4g;
 *                     - 2 : � 8g;
 *                     - 3 : �16g;
 * - [ bit 10 : 6 ]  : Reserved;
 * - [ bit  5 : 4 ]  : Averaging filter settings for Low Power Accelerometer mode:
 *                     - 0 : Average  4 samples;
 *                     - 1 : Average  8 samples;
 *                     - 2 : Average 16 samples;
 *                     - 3 : Average 32 samples;
 * - [ bit  3 ]      : Used to bypass DLPF as shown;
 * - [ bit  2 : 0 ]  : Accelerometer 3-dB BW:
 *                     - 0 : 1046.0 Hz;
 *                     - 1 :  218.1 Hz;
 *                     - 2 :  218.1 Hz;
 *                     - 3 :   99.0 Hz;
 *                     - 4 :   44.8 Hz;
 *                     - 5 :   21.2 Hz;
 *                     - 6 :   10.2 Hz;
 *                     - 7 :  420.0 Hz;
 *</pre>
 *
 * @description Function set Accel configuration data to the targeted C6DOFIMU9_REG_ACCEL_CONFIG and C6DOFIMU9_REG_ACCEL_CONFIG_2
 * register address of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_set_accel_config ( c6dofimu9_t *ctx, uint16_t accel_config_data );

/**
 * @brief Set Accel measurement range configuration function
 *
 * @param ctx      Click object.
 * @param accel_full_scale_range          
 *
 * @note 
 *<pre>
 * -  2 : Accel Full Scale Select � 2g;
 * -  4 : Accel Full Scale Select � 4g;
 * -  8 : Accel Full Scale Select � 8g;
 * - 16 : Accel Full Scale Select �16g;
 *</pre>
 * @description Function set Accel measurement range configuration data to the targeted C6DOFIMU9_REG_ACCEL_CONFIG
 * register address of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_set_accel_measurement_range ( c6dofimu9_t *ctx, uint8_t accel_full_scale_range );

/**
 * @brief Set Accel averaging filter settings for Low Power mode function
 *
 * @param ctx      Click object.
 * @param accel_avg_samples          Register address.
 * @note
 *<pre>
 * -  4 : Average  4 samples;
 * -  8 : Average  8 samples;
 * - 16 : Average 16 samples;
 * - 32 : Average 32 samples;
 *</pre>
 * @description Function set Accel averaging filter settings for Low Power mode data to the targeted C6DOFIMU9_REG_ACCEL_CONFIG_2
 * register address of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_set_accel_avg_filter_mode ( c6dofimu9_t *ctx, uint8_t accel_avg_samples );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param gyro_averages          Register address.
 * @note
 *<pre> 
 * - [ bit 7 ]     : Low-power gyroscope mode:
 *                   - 0 : Disabled ( Default );
 *                   - 1 : Enabled;
 * - [ bit 6 : 4 ] : Averaging filter configuration for low-power gyroscope mode:
 *                   - 0 : Averages   1x; Ton (ms)  1.73; Noise BW (Hz) 650.8;
 *                   - 1 : Averages   2x; Ton (ms)  2.23; Noise BW (Hz) 407.1;
 *                   - 2 : Averages   4x; Ton (ms)  3.23; Noise BW (Hz) 224.2;
 *                   - 3 : Averages   8x; Ton (ms)  5.23; Noise BW (Hz) 117.4;
 *                   - 4 : Averages  16x; Ton (ms)  9.23; Noise BW (Hz)  60.2;
 *                   - 5 : Averages  32x; Ton (ms) 17.23; Noise BW (Hz)  30.6;
 *                   - 6 : Averages  64x; Ton (ms) 33.23; Noise BW (Hz)  15.6;
 *                   - 7 : Averages 128x; Ton (ms) 65.23; Noise BW (Hz)   8.0;
 * - [ bit 3 : 0 ] : Reserved;
 *</pre>
 *
 * @description Function set Gyro Low-Power mode configuration data to the targeted C6DOFIMU9_REG_LP_MODE_CFG
 * register address of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_set_gyro_config_lp_mode ( c6dofimu9_t *ctx, uint8_t gyro_averages );

/**
 * @brief Get Accel wake-on motion threshold function
 *
 * @param ctx      Click object.
 *
 * @description Function get Accel wake-on motion threshold data from the targeted C6DOFIMU9_REG_ACCEL_WOM_THR
 * register address of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
uint8_t c6dofimu9_get_accel_wake_on_motion_trsh ( c6dofimu9_t *ctx );

/**
 * @brief Enable FIFO configuration function
 *
 * @param ctx      Click object.
 * @param en_fifo_data          
 * @note
 * <pre>
 * - [ bit 7 ]     : Write TEMP_OUT_H and TEMP_OUT_L to the FIFO at the sample rate:
 *                   - 0 : Disabled;
 *                   - 1 : Enabled;
 * - [ bit 6 ]     : Write GYRO_XOUT_H and GYRO_XOUT_L to the FIFO at the sample rate:
 *                   - 0 : Disabled;
 *                   - 1 : Enabled;
 * - [ bit 5 ]     : Write GYRO_YOUT_H and GYRO_YOUT_L to the FIFO at the sample rate:
 *                   - 0 : Disabled;
 *                   - 1 : Enabled;
 * - [ bit 4 ]     : Write GYRO_ZOUT_H and GYRO_ZOUT_L to the FIFO at the sample rate:
 *                   - 0 : Disabled;
 *                   - 1 : Enabled;
 * - [ bit 3 ]     : Write ACCEL_XOUT_H, ACCEL_XOUT_L, ACCEL_YOUT_H, ACCEL_YOUT_L, ACCEL_ZOUT_H and ACCEL_ZOUT_L to the FIFO at the sample rate:
 *                   - 0 : Disabled;
 *                   - 1 : Enabled;
 * - [ bit 2 : 0 ] : Reserved;
 * </pre>
 * @description Function enable FIFO configuration by written the byte of data to the targeted C6DOFIMU9_REG_FIFO_EN
 * register address of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_enable_fifo ( c6dofimu9_t *ctx, uint8_t en_fifo_data );

/**
 * @brief Enable Accel interrupt function
 *
 * @param ctx      Click object.
 *
 * @description Function enable Accel interrupt of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device
 * on 6DOF IMU 9 Click board.
 */
void c6dofimu9_enable_accel_interrupt ( c6dofimu9_t *ctx );

/**
 * @brief Enable Gyro interrupt function
 *
 * @param ctx      Click object.
 *
 * @description Function enable Gyro interrupt of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device
 * on 6DOF IMU 9 Click board.
 */
void c6dofimu9_enable_gyro_interrupt ( c6dofimu9_t *ctx );

/**
 * @brief Enable data ready interrupt function
 *
 * @param ctx      Click object.
 *
 * @description Function enable data ready interrupt of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device
 * on 6DOF IMU 9 Click board.
 */
void c6dofimu9_enable_data_ready_interrupt ( c6dofimu9_t *ctx );

/**
 * @brief Get interrupt status function
 *
 * @param ctx      Click object.
 * 
 * @return interrupt status
 * @note
 *<pre>
 * - [ bit 7 : 5 ] : Accelerometer WoM interrupt status. Cleared on Read;
 * - [ bit 4 ]     : This bit automatically sets to 1 when a FIFO buffer overflow has been generated. The bit clears to 0 after the register has been read;
 * - [ bit 3 ]     : Reserved;
 * - [ bit 2 ]     : Gyroscope Drive System Ready interrupt;
 * - [ bit 1 ]     : Reserved;
 * - [ bit 0 ]     : This bit automatically sets to 1 when a Data Ready interrupt is generated. The bit clears to 0 after the register has been read;
 *</pre>
 *
 * @description Function Get interrupt status of the targeted C6DOFIMU9_REG_INT_STATUS
 * register address of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
uint8_t c6dofimu9_get_interrupt_status ( c6dofimu9_t *ctx );

/**
 * @brief Reset Accel signal path function
 *
 * @param ctx      Click object.
 *
 * @description Function reset Accel signal path of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device
 * on 6DOF IMU 9 Click board.
 */
void c6dofimu9_reset_accel_signal ( c6dofimu9_t *ctx );

/**
 * @brief Reset Gyro signal path function
 *
 * @param ctx      Click object.
 *
 * @description Function reset Gyro signal path of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device
 * on 6DOF IMU 9 Click board.
 */
void c6dofimu9_reset_gyro_signal ( c6dofimu9_t *ctx );

/**
 * @brief Enable the Wake-on-Motion detection function
 *
 * @param ctx      Click object.
 *
 * @description Function enable the Wake-on-Motion detection of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device
 * on 6DOF IMU 9 Click board.
 */
void c6dofimu9_enable_accel_wake_on_motion ( c6dofimu9_t *ctx );

/**
 * @brief Reset the internal registers and restores the default settings function
 *
 * @param ctx      Click object.
 *
 * @description Function reset the internal registers and restores the default settings of
 * IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_reset_default ( c6dofimu9_t *ctx );

/**
 * @brief Set the device to sleep mode function
 *
 * @param ctx      Click object.
 *
 * @description Function set the device to sleep mode of
 * IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_set_sleep_mode ( c6dofimu9_t *ctx );

/**
 * @brief Set the device to standby mode function
 *
 * @param ctx      Click object.
 *
 * @description Function set the device to standby mode of
 * IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_set_standby_mode ( c6dofimu9_t *ctx );

/**
 * @brief Get device ID function
 *
 * @param ctx      Click object.
 *
 * @return
 * 8-bit device ID value ( default 0xA9 ); 
 * @description This function reads data from the desired register.
 */
uint8_t c6dofimu9_get_device_id ( c6dofimu9_t *ctx );

/**
 * @brief Get axis data function
 *
 * @param ctx           Click object.
 * @param addr_reg_msb  least significant bit register address
 * @param addr_reg_lsb  most significant bit register address
 *
 * @description Function get axis data by read data from the two targeted register address
 * of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
int16_t c6dofimu9_get_axis ( c6dofimu9_t *ctx, uint8_t addr_reg_msb, uint8_t addr_reg_lsb );

/**
 * @brief Read Accel X-axis, Y-axis and Z-axis axis function
 *
 * @param ctx           Click object.
 * @param p_accel_x     pointer to memory location where Accel X-axis data be stored
 * @param p_accel_y     pointer to memory location where Accel Y-axis data be stored
 * @param p_accel_z     pointer to memory location where Accel Z-axis data be stored
 *
 * @description Function reads 16-bit ( signed ) Accel X-axis, Y-axis data and Z-axis data from the
 * targeted starts from C6DOFIMU9_REG_ACCEL_XOUT_H to the C6DOFIMU9_REG_ACCEL_ZOUT_L register address
 * of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_get_accel_data ( c6dofimu9_t *ctx, int16_t *p_accel_x, int16_t *p_accel_y, int16_t *p_accel_z );

/**
 * @brief Read Gyro X-axis, Y-axis and Z-axis axis function
 *
 * @param ctx          Click object.
 * @param p_gyro_x     pointer to memory location where Accel X-axis data be stored
 * @param p_gyro_y     pointer to memory location where Accel Y-axis data be stored
 * @param p_gyro_z     pointer to memory location where Accel Z-axis data be stored
 *
 * @description Function reads 16-bit ( signed ) Gyro X-axis, Y-axis data and Z-axis data from the
 * targeted starts from C6DOFIMU9_REG_GYRO_XOUT_H to the C6DOFIMU9_REG_GYRO_ZOUT_L register address
 * of IAM-20680 High Performance Automotive 6-Axis MotionTracking Device on 6DOF IMU 9 Click board.
 */
void c6dofimu9_get_gyro_data ( c6dofimu9_t *ctx, int16_t *p_gyro_x, int16_t *p_gyro_y, int16_t *p_gyro_z );


#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
