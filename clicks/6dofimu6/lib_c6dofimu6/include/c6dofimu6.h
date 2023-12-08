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
 * \brief This file contains API for 6DOF IMU 6 Click driver.
 *
 * \addtogroup c6dofimu6 6DOF IMU 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU6_H
#define C6DOFIMU6_H

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

#define C6DOFIMU6_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C6DOFIMU6_MASTER_I2C                             0
#define C6DOFIMU6_MASTER_SPI                             1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU6_RETVAL  uint8_t

#define C6DOFIMU6_OK                                     0x00
#define C6DOFIMU6_INIT_ERROR                             0xFF
/** \} */

/**
 * \defgroup i2c_address I2C Address
 * \{
 */
#define C6DOFIMU6_I2C_SLAVE_ADR_GND                      0x68
#define C6DOFIMU6_I2C_SLAVE_ADR_VCC                      0x69
/** \} */

/**
 * \defgroup spi_masks SPI Masks
 * \{
 */
#define C6DOFIMU6_READ_BIT_MASK                          0x80
#define C6DOFIMU6_WRITE_BIT_MASK                         0x7F
/** \} */

/**
 * \defgroup register_map Register Map
 * \{
 */
#define C6DOFIMU6_SELF_TEST_X_GYRO                       0x00
#define C6DOFIMU6_SELF_TEST_Y_GYRO                       0x01
#define C6DOFIMU6_SELF_TEST_Z_GYRO                       0x02
#define C6DOFIMU6_SELF_TEST_X_ACCEL                      0x0D
#define C6DOFIMU6_SELF_TEST_Y_ACCEL                      0x0E
#define C6DOFIMU6_SELF_TEST_Z_ACCEL                      0x0F
#define C6DOFIMU6_XG_OFFS_USR_H                          0x13
#define C6DOFIMU6_XG_OFFS_USR_L                          0x14
#define C6DOFIMU6_YG_OFFS_USR_H                          0x15
#define C6DOFIMU6_YG_OFFS_USR_L                          0x16
#define C6DOFIMU6_ZG_OFFS_USR_H                          0x17
#define C6DOFIMU6_ZG_OFFS_USR_L                          0x18
#define C6DOFIMU6_SMPL_RT_DIV                            0x19
#define C6DOFIMU6_CFG                                    0x1A
#define C6DOFIMU6_GYRO_CFG                               0x1B
#define C6DOFIMU6_ACCEL_CFG                              0x1C
#define C6DOFIMU6_ACCEL_CFG_2                            0x1D
#define C6DOFIMU6_LP_MODE_CTL                            0x1E
#define C6DOFIMU6_ACCEL_WOM_X_THR                        0x20
#define C6DOFIMU6_ACCEL_WOM_Y_THR                        0x21
#define C6DOFIMU6_ACCEL_WOM_Z_THR                        0x22
#define C6DOFIMU6_FIFO_EN                                0x23
#define C6DOFIMU6_INT_PIN_CFG                            0x37
#define C6DOFIMU6_INT_ENABLE                             0x38
#define C6DOFIMU6_DMP_INT_STAT                           0x39
#define C6DOFIMU6_INT_STAT                               0x3A
#define C6DOFIMU6_ACCEL_XOUT_H                           0x3B
#define C6DOFIMU6_ACCEL_XOUT_L                           0x3C
#define C6DOFIMU6_ACCEL_YOUT_H                           0x3D
#define C6DOFIMU6_ACCEL_YOUT_L                           0x3E
#define C6DOFIMU6_ACCEL_ZOUT_H                           0x3F
#define C6DOFIMU6_ACCEL_ZOUT_L                           0x40
#define C6DOFIMU6_TEMP_OUT_H                             0x41
#define C6DOFIMU6_TEMP_OUT_L                             0x42
#define C6DOFIMU6_GYRO_XOUT_H                            0x43
#define C6DOFIMU6_GYRO_XOUT_L                            0x44
#define C6DOFIMU6_GYRO_YOUT_H                            0x45
#define C6DOFIMU6_GYRO_YOUT_L                            0x46
#define C6DOFIMU6_GYRO_ZOUT_H                            0x47
#define C6DOFIMU6_GYRO_ZOUT_L                            0x48
#define C6DOFIMU6_SIGNAL_PATH_RST                        0x68
#define C6DOFIMU6_ACCEL_INTEL_CTL                        0x69
#define C6DOFIMU6_USER_CTL                               0x6A
#define C6DOFIMU6_PWR_MGMT_1                             0x6B
#define C6DOFIMU6_PWR_MGMT_2                             0x6C
#define C6DOFIMU6_FIFO_CNT_H                             0x72
#define C6DOFIMU6_FIFO_CNT_L                             0x73
#define C6DOFIMU6_FIFO_R_W                               0x74
#define C6DOFIMU6_WHO_AM_I                               0x75
#define C6DOFIMU6_XA_OFFS_H                              0x77
#define C6DOFIMU6_XA_OFFS_L                              0x78
#define C6DOFIMU6_YA_OFFS_H                              0x7A
#define C6DOFIMU6_YA_OFFS_L                              0x7B
#define C6DOFIMU6_ZA_OFFS_H                              0x7D
#define C6DOFIMU6_ZA_OFFS_L                              0x7E
/** \} */

/**
 * \defgroup cfg_reg_commands Configuration Register commands
 * \{
 */
#define C6DOFIMU6_CFG_FIFO_MODE                          0x40
#define C6DOFIMU6_CFG_EXT_SYNC_SET_1                     0x08
#define C6DOFIMU6_CFG_EXT_SYNC_SET_2                     0x10
#define C6DOFIMU6_CFG_EXT_SYNC_SET_3                     0x18
#define C6DOFIMU6_CFG_EXT_SYNC_SET_4                     0x20
#define C6DOFIMU6_CFG_EXT_SYNC_SET_5                     0x28
#define C6DOFIMU6_CFG_EXT_SYNC_SET_6                     0x30
#define C6DOFIMU6_CFG_EXT_SYNC_SET_7                     0x38
#define C6DOFIMU6_CFG_DLPF_CFG_0                         0x00
#define C6DOFIMU6_CFG_DLPF_CFG_1                         0x01
#define C6DOFIMU6_CFG_DLPF_CFG_2                         0x02
#define C6DOFIMU6_CFG_DLPF_CFG_3                         0x03
#define C6DOFIMU6_CFG_DLPF_CFG_4                         0x04
#define C6DOFIMU6_CFG_DLPF_CFG_5                         0x05
#define C6DOFIMU6_CFG_DLPF_CFG_6                         0x06
#define C6DOFIMU6_CFG_DLPF_CFG_7                         0x07
/** \} */

/**
 * \defgroup gyroscope_cfg_reg_commands Gyroscope Configuration Register commands
 * \{
 */
#define C6DOFIMU6_GYRO_CFG_XGYRO_STEN                    0x80
#define C6DOFIMU6_GYRO_CFG_YGYRO_STEN                    0x40
#define C6DOFIMU6_GYRO_CFG_ZGYRO_STEN                    0x20
#define C6DOFIMU6_GYRO_CFG_FS_SEL_2000                   0x18
#define C6DOFIMU6_GYRO_CFG_FS_SEL_1000                   0x10
#define C6DOFIMU6_GYRO_CFG_FS_SEL_500                    0x08
#define C6DOFIMU6_GYRO_CFG_FS_SEL_250                    0x00
#define C6DOFIMU6_GYRO_CFG_FCHOICE_B_2                   0x02
#define C6DOFIMU6_GYRO_CFG_FCHOICE_B_1                   0x01
#define C6DOFIMU6_GYRO_CFG_FCHOICE_B_0                   0x00
/** \} */
 
/**
 * \defgroup accelerometer_cfg_reg_commands Accelerometer Configuration Register commands
 * \{
 */
#define C6DOFIMU6_ACCEL_CFG_AX_ST_EN                     0x80
#define C6DOFIMU6_ACCEL_CFG_AY_ST_EN                     0x40
#define C6DOFIMU6_ACCEL_CFG_AZ_ST_EN                     0x20
#define C6DOFIMU6_ACCEL_CFG_FS_SEL_16G                   0x18
#define C6DOFIMU6_ACCEL_CFG_FS_SEL_8G                    0x10
#define C6DOFIMU6_ACCEL_CFG_FS_SEL_4G                    0x08
#define C6DOFIMU6_ACCEL_CFG_FS_SEL_2G                    0x00
/** \} */

/**
 * \defgroup accelerometer_cfg_2_reg_commands Accelerometer Configuration 2 Register commands
 * \{
 */
#define C6DOFIMU6_ACCEL2_CFG_FIFO_SIZE_4KB               0x40
#define C6DOFIMU6_ACCEL2_CFG_FIFO_SIZE_2KB               0x08
#define C6DOFIMU6_ACCEL2_CFG_FIFO_SIZE_1KB               0x10
#define C6DOFIMU6_ACCEL2_CFG_FIFO_SIZE_512B              0x18
#define C6DOFIMU6_ACCEL2_CFG_DEC2_CFG_32                 0x30
#define C6DOFIMU6_ACCEL2_CFG_DEC2_CFG_16                 0x20
#define C6DOFIMU6_ACCEL2_CFG_DEC2_CFG_8                  0x10
#define C6DOFIMU6_ACCEL2_CFG_DEC2_CFG_4                  0x00
#define C6DOFIMU6_ACCEL2_CFG_FCHOICE_B                   0x00
#define C6DOFIMU6_ACCEL2_CFG_A_DLPF_CFG_0                0x00
#define C6DOFIMU6_ACCEL2_CFG_A_DLPF_CFG_1                0x01
#define C6DOFIMU6_ACCEL2_CFG_A_DLPF_CFG_2                0x02
#define C6DOFIMU6_ACCEL2_CFG_A_DLPF_CFG_3                0x03
#define C6DOFIMU6_ACCEL2_CFG_A_DLPF_CFG_4                0x04
#define C6DOFIMU6_ACCEL2_CFG_A_DLPF_CFG_5                0x05
#define C6DOFIMU6_ACCEL2_CFG_A_DLPF_CFG_6                0x06
#define C6DOFIMU6_ACCEL2_CFG_A_DLPF_CFG_7                0x07
/** \} */

/**
 * \defgroup fifo_enable_register_commands FIFO Enable Register Commands
 * \{
 */
#define C6DOFIMU6_FIFO_EN_TEMP_OUT                       0x80
#define C6DOFIMU6_FIFO_EN_GYRO_XOUT                      0x40
#define C6DOFIMU6_FIFO_EN_GYRO_YOUT                      0x20
#define C6DOFIMU6_FIFO_EN_GYRO_ZOUT                      0x10
#define C6DOFIMU6_FIFO_EN_ACCEL_XYZ_OUT                  0x08
/** \} */

/**
 * \defgroup interrupt_bypass_pin_cfg_reg_commands Interrupt/Bypass Pin Configuration Register Commands
 * \{
 */
#define C6DOFIMU6_INT_PIN_CFG_ACTL                       0x80
#define C6DOFIMU6_INT_PIN_CFG_OPEN                       0x40
#define C6DOFIMU6_INT_PIN_CFG_LATCH_INT_EN               0x20
#define C6DOFIMU6_INT_PIN_CFG_INT_ANYRD_2CLR             0x10
#define C6DOFIMU6_INT_PIN_CFG_ACTL_FSYNC                 0x08
#define C6DOFIMU6_INT_PIN_CFG_FSYNC_INT_MODE_EN          0x04
#define C6DOFIMU6_INT_PIN_CFG_BYPASS_EN                  0x02
/** \} */

/**
 * \defgroup interrupt_enable_register_commands Interrupt Enable Register Commands
 * \{
 */
#define C6DOFIMU6_INT_ENABLE_WOM_X_INT_EN                0x80
#define C6DOFIMU6_INT_ENABLE_WOM_Y_INT_EN                0x40
#define C6DOFIMU6_INT_ENABLE_WOM_Z_INT_EN                0x20
#define C6DOFIMU6_INT_ENABLE_FIFO_OVF_EN                 0x10
#define C6DOFIMU6_INT_ENABLE_GDRIVE_RDY_EN               0x04
#define C6DOFIMU6_INT_ENABLE_DMP_INT_EN                  0x02
#define C6DOFIMU6_INT_ENABLE_RAW_RDY_EN                  0x01
/** \} */

/**
 * \defgroup interrupt_status_register_commands Interrupt Status Register Commands
 * \{
 */
#define C6DOFIMU6_INT_STAT_WOM_X_INT                     0x80
#define C6DOFIMU6_INT_STAT_WOM_Y_INT                     0x40
#define C6DOFIMU6_INT_STAT_WOM_Z_INT                     0x20
#define C6DOFIMU6_INT_STAT_FIFO_OVF_INT                  0x10
#define C6DOFIMU6_INT_STAT_GDRIVE_RDY_INT                0x04
#define C6DOFIMU6_INT_STAT_DMP_INT                       0x02
#define C6DOFIMU6_INT_STAT_RAW_RDY_INT                   0x01
/** \} */

/**
 * \defgroup signal_path_reset_commands Signal Path Reset Commands
 * \{
 */
#define C6DOFIMU6_SIGNAL_PATH_RST_GYRO_RST               0x80
#define C6DOFIMU6_SIGNAL_PATH_RST_ACCEL_RST              0x40
#define C6DOFIMU6_SIGNAL_PATH_RST_TEMP_RST               0x20
/** \} */

/**
 * \defgroup  accelerometer_intelligence_ctrl_commands  Accelerometer Intelligence Control Commands
 * \{
 */
#define C6DOFIMU6_ACCEL_INTEL_CTL_INTEL_EN               0x80
#define C6DOFIMU6_ACCEL_INTEL_CTL_INTEL_MODE_PREV_SAMP   0x40
#define C6DOFIMU6_ACCEL_INTEL_CTL_INTEL_MODE_FIRST_SAMP  0x00
/** \} */

/**
 * \defgroup user_control_register_commands User Control Register Commands
 * \{
 */
#define C6DOFIMU6_USER_CTL_DMP_EN                        0x80
#define C6DOFIMU6_USER_CTL_FIFO_EN                       0x40
#define C6DOFIMU6_USER_CTL_I2C_IF_DIS                    0x10
#define C6DOFIMU6_USER_CTL_DMP_RST                       0x08
#define C6DOFIMU6_USER_CTL_FIFO_RST                      0x04
#define C6DOFIMU6_USER_CTL_SIG_COND_RST                  0x01
/** \} */

/**
 * \defgroup power_management_1_register_commands Power Management 1 Register Commands
 * \{
 */
#define C6DOFIMU6_PWR_MGMT_1_DEV_RST                     0x80
#define C6DOFIMU6_PWR_MGMT_1_SLEEP                       0x40
#define C6DOFIMU6_PWR_MGMT_1_ACCEL_CYC                   0x20
#define C6DOFIMU6_PWR_MGMT_1_GYRO_STDBY                  0x10
#define C6DOFIMU6_PWR_MGMT_1_TEMP_DIS                    0x08
#define C6DOFIMU6_PWR_MGMT_1_CLKSEL_7                    0x07
#define C6DOFIMU6_PWR_MGMT_1_CLKSEL_6                    0x06
#define C6DOFIMU6_PWR_MGMT_1_CLKSEL_5                    0x05
#define C6DOFIMU6_PWR_MGMT_1_CLKSEL_4                    0x04
#define C6DOFIMU6_PWR_MGMT_1_CLKSEL_3                    0x03
#define C6DOFIMU6_PWR_MGMT_1_CLKSEL_2                    0x02
#define C6DOFIMU6_PWR_MGMT_1_CLKSEL_1                    0x01
#define C6DOFIMU6_PWR_MGMT_1_CLKSEL_0                    0x00
/** \} */

/**
 * \defgroup power_management_2_register_commands Power Management 2 Register Commands
 * \{
 */
#define C6DOFIMU6_PWR_MGMT_2_LP_DIS                      0x80
#define C6DOFIMU6_PWR_MGMT_2_DMP_LP_DIS                  0x40
#define C6DOFIMU6_PWR_MGMT_2_DISABLE_XA                  0x20
#define C6DOFIMU6_PWR_MGMT_2_DISABLE_YA                  0x10
#define C6DOFIMU6_PWR_MGMT_2_DISABLE_ZA                  0x08
#define C6DOFIMU6_PWR_MGMT_2_DISABLE_XG                  0x04
#define C6DOFIMU6_PWR_MGMT_2_DISABLE_YG                  0x02
#define C6DOFIMU6_PWR_MGMT_2_DISABLE_ZG                  0x01
/** \} */

/**
 * \defgroup who_am_i_register_value Who Am I Register Value
 * \{
 */
#define C6DOFIMU6_WHO_AM_I_VAL                           0x98
/** \} */

/**
 * \defgroup power_states Power states
 * \{
 */
#define C6DOFIMU6_POWER_ON                               0x01
#define C6DOFIMU6_POWER_OFF                              0x00
/** \} */

/**
 * \defgroup  sensor_sensitivity_values  Sensor Sensitivity values
 * \{
 */
#define C6DOFIMU6_GYRO_SENS_FS_SEL_2000                  16.4
#define C6DOFIMU6_GYRO_SENS_FS_SEL_1000                  32.8
#define C6DOFIMU6_GYRO_SENS_FS_SEL_500                   65.5
#define C6DOFIMU6_GYRO_SENS_FS_SEL_250                   131.0
#define C6DOFIMU6_ACCEL_SENS_FS_SEL_16G                  2048.0
#define C6DOFIMU6_ACCEL_SENS_FS_SEL_8G                   4096.0
#define C6DOFIMU6_ACCEL_SENS_FS_SEL_4G                   8192.0
#define C6DOFIMU6_ACCEL_SENS_FS_SEL_2G                   16384.0
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
typedef uint8_t  c6dofimu6_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c6dofimu6_master_io_t )( struct c6dofimu6_s*, uint8_t, uint8_t*, uint16_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu6_s
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
   c6dofimu6_master_io_t  write_f;
   c6dofimu6_master_io_t  read_f;
   c6dofimu6_select_t master_sel;

} c6dofimu6_t;

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
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   c6dofimu6_select_t sel;

} c6dofimu6_cfg_t;

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
void c6dofimu6_cfg_setup ( c6dofimu6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU6_RETVAL c6dofimu6_init ( c6dofimu6_t *ctx, c6dofimu6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 6DOF IMU 6 click.
 */
void c6dofimu6_default_cfg ( c6dofimu6_t *ctx );

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
void c6dofimu6_generic_write ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

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
void c6dofimu6_generic_read ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

/**
 * @brief Power up function
 *
 * @param ctx      Click object. 
 * @param on_off   Value defines power state of the device
 *
 * @description Turns the device on or off.
 * @note It is advisable to use predefined values.
**/
void c6dofimu6_power ( c6dofimu6_t *ctx, uint8_t on_off );

/**
 * @brief Read Gyroscope X-axis data function
 *
 * @param ctx      Click object. 
 * 
 * @returns result 16-bit gyroscope X-axis data
 *
 * @description Function is used to read gyroscope X-axis data.
**/
int16_t c6dofimu6_read_gyro_x ( c6dofimu6_t *ctx );

/**
 * @brief Read Gyroscope Y-axis data function
 *
 * @param ctx      Click object. 
 * 
 * @returns result 16-bit gyroscope Y-axis data
 *
 * @description Function is used to read gyroscope Y-axis data.
**/
int16_t c6dofimu6_read_gyro_y ( c6dofimu6_t *ctx );

/**
 * @brief Read Gyroscope Z-axis data function
 *
 * @param ctx      Click object. 
 * 
 * @returns result 16-bit gyroscope Z-axis data
 *
 * @description Function is used to read gyroscope Z-axis data.
**/
int16_t c6dofimu6_read_gyro_z ( c6dofimu6_t *ctx );

/**
 * @brief Read gyroscope data function
 *
 * @param ctx     Click object.  
 * @param gyro_x  16-bit gyroscope X-axis data
 * @param gyro_y  16-bit gyroscope Y-axis data
 * @param gyro_z  16-bit gyroscope Z-axis data
 *
 * @description Function is used to read gyroscope data.
**/
void c6dofimu6_read_gyroscope ( c6dofimu6_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );

/**
 * @brief Read Angular Rate function
 *
 * @param ctx        Click object.  
 * @param x_ang_rte  float X-axis angular rate
 * @param y_ang_rte  float Y-axis angular rate
 * @param z_ang_rte  float Z-axis angular rate
 *
 * @description Function is used to calculate angular rate.
**/
void c6dofimu6_angular_rate ( c6dofimu6_t *ctx, float *x_ang_rte, float *y_ang_rte, float *z_ang_rte );

/**
 * @brief Read Accelerometer X-axis data function
 *
 * @param ctx      Click object. 
 * 
 * @returns result 16-bit accelerometer X-axis data
 *
 * @description Function is used to read accelerometer X-axis data.
**/
int16_t c6dofimu6_read_accel_x ( c6dofimu6_t *ctx );

/**
 * @brief Read Accelerometer Y-axis data function
 *
 * @param ctx      Click object. 
 * 
 * @returns result 16-bit accelerometer Y-axis data
 *
 * @description Function is used to read accelerometer Y-axis data.
**/
int16_t c6dofimu6_read_accel_y( c6dofimu6_t *ctx );

/**
 * @brief Read Accelerometer Z-axis data function
 *
 * @param ctx      Click object. 
 * 
 * @returns result 16-bit accelerometer Z-axis data
 *
 * @description Function is used to read accelerometer Z-axis data.
**/
int16_t c6dofimu6_read_accel_z( c6dofimu6_t *ctx );

/**
 * @brief Read accelerometer data function
 *
 * @param ctx      Click object.  
 * @param accel_x  16-bit accelerometer X-axis data
 * @param accel_y  16-bit accelerometer Y-axis data
 * @param accel_z  16-bit accelerometer Z-axis data
 *
 * @description Function is used to read accelerometer data.
**/
void c6dofimu6_read_accelerometer ( c6dofimu6_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );

/**
 * @brief Read acceleration Rate function
 *
 * @param ctx          Click object.  
 * @param x_accel_rte  float X-axis acceleration rate
 * @param y_accel_rte  float Y-axis acceleration rate
 * @param z_accel_rte  float Z-axis acceleration rate
 *
 * @description Function is used to calculate acceleration rate.
**/
void c6dofimu6_acceleration_rate ( c6dofimu6_t *ctx, float *x_accel_rte, float *y_accel_rte, float *z_accel_rte );

/**
 * @brief Read temperture function
 *
 * @param ctx      Click object. 
 * 
 * @returns result float temperture data
 *
 * @description Function is used to read temperture in degree Centigrade.
**/
float c6dofimu6_read_temp_out ( c6dofimu6_t *ctx );

/**
 * @brief Check Interrupt state function
 *
 * @param ctx      Click object. 
 * 
 * @returns 0 - Interrupt has not occured;  1 - Interrupt has occured
 *
 * @description Function is used to check if an interrupt has occured.
**/
uint8_t c6dofimu6_check_int_pin ( c6dofimu6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
