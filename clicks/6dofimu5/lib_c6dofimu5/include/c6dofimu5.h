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
 * \brief This file contains API for C6DOF IMU 5 Click driver.
 *
 * \addtogroup c6dofimu5 C6DOF IMU 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU5_H
#define C6DOFIMU5_H

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

#define C6DOFIMU5_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU5_RETVAL  uint8_t

#define C6DOFIMU5_OK           0x00
#define C6DOFIMU5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address I2C Address
 * \{
 */
#define C6DOFIMU5_I2C_SLAVE_ADR         0x63
/** \} */

/**
 * \defgroup spi_masks SPI Masks
 * \{
 */
#define C6DOFIMU5_READ_BIT_MASK         0x80
#define C6DOFIMU5_WRITE_BIT_MASK        0x7F
/** \} */

/**
 * \defgroup register_map Register Map
 * \{
 */
#define C6DOFIMU5_SELF_TEST_X_GYRO      0x00
#define C6DOFIMU5_SELF_TEST_Y_GYRO      0x01
#define C6DOFIMU5_SELF_TEST_Z_GYRO      0x02
#define C6DOFIMU5_SELF_TEST_X_ACCEL     0x0D
#define C6DOFIMU5_SELF_TEST_Y_ACCEL     0x0E
#define C6DOFIMU5_SELF_TEST_Z_ACCEL     0x0F
#define C6DOFIMU5_XG_OFFS_USR_H         0x13
#define C6DOFIMU5_XG_OFFS_USR_L         0x14
#define C6DOFIMU5_YG_OFFS_USR_H         0x15
#define C6DOFIMU5_YG_OFFS_USR_L         0x16
#define C6DOFIMU5_ZG_OFFS_USR_H         0x17
#define C6DOFIMU5_ZG_OFFS_USR_L         0x18
#define C6DOFIMU5_SMPL_RT_DIV           0x19
#define C6DOFIMU5_CFG                   0x1A
#define C6DOFIMU5_GYRO_CFG              0x1B
#define C6DOFIMU5_ACCEL_CFG             0x1C
#define C6DOFIMU5_ACCEL_CFG_2           0x1D
#define C6DOFIMU5_LP_MODE_CTL           0x1E
#define C6DOFIMU5_ACCEL_WOM_X_THR       0x20
#define C6DOFIMU5_ACCEL_WOM_Y_THR       0x21
#define C6DOFIMU5_ACCEL_WOM_Z_THR       0x22
#define C6DOFIMU5_FIFO_EN               0x23
#define C6DOFIMU5_INT_PIN_CFG           0x37
#define C6DOFIMU5_INT_ENABLE            0x38
#define C6DOFIMU5_DMP_INT_STAT          0x39
#define C6DOFIMU5_INT_STAT              0x3A
#define C6DOFIMU5_ACCEL_XOUT_H          0x3B
#define C6DOFIMU5_ACCEL_XOUT_L          0x3C
#define C6DOFIMU5_ACCEL_YOUT_H          0x3D
#define C6DOFIMU5_ACCEL_YOUT_L          0x3E
#define C6DOFIMU5_ACCEL_ZOUT_H          0x3F
#define C6DOFIMU5_ACCEL_ZOUT_L          0x40
#define C6DOFIMU5_TEMP_OUT_H            0x41
#define C6DOFIMU5_TEMP_OUT_L            0x42
#define C6DOFIMU5_GYRO_XOUT_H           0x43
#define C6DOFIMU5_GYRO_XOUT_L           0x44
#define C6DOFIMU5_GYRO_YOUT_H           0x45
#define C6DOFIMU5_GYRO_YOUT_L           0x46
#define C6DOFIMU5_GYRO_ZOUT_H           0x47
#define C6DOFIMU5_GYRO_ZOUT_L           0x48
#define C6DOFIMU5_SIGNAL_PATH_RST       0x68
#define C6DOFIMU5_ACCEL_INTEL_CTL       0x69
#define C6DOFIMU5_USER_CTL              0x6A
#define C6DOFIMU5_PWR_MGMT_1            0x6B
#define C6DOFIMU5_PWR_MGMT_2            0x6C
#define C6DOFIMU5_FIFO_CNT_H            0x72
#define C6DOFIMU5_FIFO_CNT_L            0x73
#define C6DOFIMU5_FIFO_R_W              0x74
#define C6DOFIMU5_WHO_AM_I              0x75
#define C6DOFIMU5_XA_OFFS_H             0x77
#define C6DOFIMU5_XA_OFFS_L             0x78
#define C6DOFIMU5_YA_OFFS_H             0x7A
#define C6DOFIMU5_YA_OFFS_L             0x7B
#define C6DOFIMU5_ZA_OFFS_H             0x7D
#define C6DOFIMU5_ZA_OFFS_L             0x7E
/** \} */

/**
 * \defgroup configuration_register_commands Configuration Register Commands
 * \{
 */
#define C6DOFIMU5_CFG_FIFO_MODE             0x40
#define C6DOFIMU5_CFG_EXT_SYNC_SET_1        0x08
#define C6DOFIMU5_CFG_EXT_SYNC_SET_2        0x10
#define C6DOFIMU5_CFG_EXT_SYNC_SET_3        0x18
#define C6DOFIMU5_CFG_EXT_SYNC_SET_4        0x20
#define C6DOFIMU5_CFG_EXT_SYNC_SET_5        0x28
#define C6DOFIMU5_CFG_EXT_SYNC_SET_6        0x30
#define C6DOFIMU5_CFG_EXT_SYNC_SET_7        0x38
#define C6DOFIMU5_CFG_DLPF_CFG_0            0x00
#define C6DOFIMU5_CFG_DLPF_CFG_1            0x01
#define C6DOFIMU5_CFG_DLPF_CFG_2            0x02
#define C6DOFIMU5_CFG_DLPF_CFG_3            0x03
#define C6DOFIMU5_CFG_DLPF_CFG_4            0x04
#define C6DOFIMU5_CFG_DLPF_CFG_5            0x05
#define C6DOFIMU5_CFG_DLPF_CFG_6            0x06
#define C6DOFIMU5_CFG_DLPF_CFG_7            0x07
/** \} */

/**
 * \defgroup gyroscope_configuration_register_commands Gyroscope Configuration Register Commands
 * \{
 */
#define C6DOFIMU5_GYRO_CFG_XGYRO_STEN       0x80
#define C6DOFIMU5_GYRO_CFG_YGYRO_STEN       0x40
#define C6DOFIMU5_GYRO_CFG_ZGYRO_STEN       0x20
#define C6DOFIMU5_GYRO_CFG_FS_SEL_2000      0x18
#define C6DOFIMU5_GYRO_CFG_FS_SEL_1000      0x10
#define C6DOFIMU5_GYRO_CFG_FS_SEL_500       0x08
#define C6DOFIMU5_GYRO_CFG_FS_SEL_250       0x00
#define C6DOFIMU5_GYRO_CFG_FCHOICE_B_2      0x02
#define C6DOFIMU5_GYRO_CFG_FCHOICE_B_1      0x01
#define C6DOFIMU5_GYRO_CFG_FCHOICE_B_0      0x00
/** \} */

/**
 * \defgroup accelerometer_configuration_register_commands Accelerometer Configuration Register Commands
 * \{
 */
#define C6DOFIMU5_ACCEL_CFG_AX_ST_EN        0x80
#define C6DOFIMU5_ACCEL_CFG_AY_ST_EN        0x40
#define C6DOFIMU5_ACCEL_CFG_AZ_ST_EN        0x20
#define C6DOFIMU5_ACCEL_CFG_FS_SEL_16G      0x18
#define C6DOFIMU5_ACCEL_CFG_FS_SEL_8G       0x10
#define C6DOFIMU5_ACCEL_CFG_FS_SEL_4G       0x08
#define C6DOFIMU5_ACCEL_CFG_FS_SEL_2G       0x00
/** \} */

/**
 * \defgroup accelerometer_configuration_2_register_commands Accelerometer Configuration 2 Register Commands
 * \{
 */
#define C6DOFIMU5_ACCEL2_CFG_FIFO_SIZE_4KB      0x40
#define C6DOFIMU5_ACCEL2_CFG_FIFO_SIZE_2KB      0x08
#define C6DOFIMU5_ACCEL2_CFG_FIFO_SIZE_1KB      0x10
#define C6DOFIMU5_ACCEL2_CFG_FIFO_SIZE_512B     0x18
#define C6DOFIMU5_ACCEL2_CFG_DEC2_CFG_32        0x30
#define C6DOFIMU5_ACCEL2_CFG_DEC2_CFG_16        0x20
#define C6DOFIMU5_ACCEL2_CFG_DEC2_CFG_8         0x10
#define C6DOFIMU5_ACCEL2_CFG_DEC2_CFG_4         0x00
#define C6DOFIMU5_ACCEL2_CFG_FCHOICE_B          0x00
#define C6DOFIMU5_ACCEL2_CFG_A_DLPF_CFG_0       0x00
#define C6DOFIMU5_ACCEL2_CFG_A_DLPF_CFG_1       0x01
#define C6DOFIMU5_ACCEL2_CFG_A_DLPF_CFG_2       0x02
#define C6DOFIMU5_ACCEL2_CFG_A_DLPF_CFG_3       0x03
#define C6DOFIMU5_ACCEL2_CFG_A_DLPF_CFG_4       0x04
#define C6DOFIMU5_ACCEL2_CFG_A_DLPF_CFG_5       0x05
#define C6DOFIMU5_ACCEL2_CFG_A_DLPF_CFG_6       0x06
#define C6DOFIMU5_ACCEL2_CFG_A_DLPF_CFG_7       0x07
/** \} */

/**
 * \defgroup fifo_enable_register_commands FIFO Enable Register Commands
 * \{
 */
#define C6DOFIMU5_FIFO_EN_TEMP_OUT              0x80
#define C6DOFIMU5_FIFO_EN_GYRO_XOUT             0x40
#define C6DOFIMU5_FIFO_EN_GYRO_YOUT             0x20
#define C6DOFIMU5_FIFO_EN_GYRO_ZOUT             0x10
#define C6DOFIMU5_FIFO_EN_ACCEL_XYZ_OUT         0x08
/** \} */

/**
 * \defgroup interrupt/bypass_pin_configuration Interrupt/Bypass Pin Configuration 
 * \{
 */
#define C6DOFIMU5_INT_PIN_CFG_ACTL                  0x80
#define C6DOFIMU5_INT_PIN_CFG_OPEN                  0x40
#define C6DOFIMU5_INT_PIN_CFG_LATCH_INT_EN          0x20
#define C6DOFIMU5_INT_PIN_CFG_INT_ANYRD_2CLR        0x10
#define C6DOFIMU5_INT_PIN_CFG_ACTL_FSYNC            0x08
#define C6DOFIMU5_INT_PIN_CFG_FSYNC_INT_MODE_EN     0x04
#define C6DOFIMU5_INT_PIN_CFG_BYPASS_EN             0x02
/** \} */

/**
 * \defgroup interrupt_enable_register_commands Interrupt Enable Register Commands 
 * \{
 */
#define C6DOFIMU5_INT_ENABLE_WOM_X_INT_EN           0x80
#define C6DOFIMU5_INT_ENABLE_WOM_Y_INT_EN           0x40
#define C6DOFIMU5_INT_ENABLE_WOM_Z_INT_EN           0x20
#define C6DOFIMU5_INT_ENABLE_FIFO_OVF_EN            0x10
#define C6DOFIMU5_INT_ENABLE_GDRIVE_RDY_EN          0x04
#define C6DOFIMU5_INT_ENABLE_DMP_INT_EN             0x02
#define C6DOFIMU5_INT_ENABLE_RAW_RDY_EN             0x01
/** \} */

/**
 * \defgroup interrupt_status_register_commands Interrupt Status Register Commands 
 * \{
 */
#define C6DOFIMU5_INT_STAT_WOM_X_INT                0x80
#define C6DOFIMU5_INT_STAT_WOM_Y_INT                0x40
#define C6DOFIMU5_INT_STAT_WOM_Z_INT                0x20
#define C6DOFIMU5_INT_STAT_FIFO_OVF_INT             0x10
#define C6DOFIMU5_INT_STAT_GDRIVE_RDY_INT           0x04
#define C6DOFIMU5_INT_STAT_DMP_INT                  0x02
#define C6DOFIMU5_INT_STAT_RAW_RDY_INT              0x01
/** \} */

/**
 * \defgroup signal_path_reset_commands Signal Path Reset Commands
 * \{
 */
#define C6DOFIMU5_SIGNAL_PATH_RST_GYRO_RST          0x80
#define C6DOFIMU5_SIGNAL_PATH_RST_ACCEL_RST         0x40
#define C6DOFIMU5_SIGNAL_PATH_RST_TEMP_RST          0x20
/** \} */

/**
 * \defgroup accelerometer_intelligence_control_commands Accelerometer Intelligence Control Commands
 * \{
 */
#define C6DOFIMU5_ACCEL_INTEL_CTL_INTEL_EN                  0x80
#define C6DOFIMU5_ACCEL_INTEL_CTL_INTEL_MODE_PREV_SAMP      0x40
#define C6DOFIMU5_ACCEL_INTEL_CTL_INTEL_MODE_FIRST_SAMP     0x00
/** \} */

/**
 * \defgroup user_control_register_commands User Control Register Commands
 * \{
 */
#define C6DOFIMU5_USER_CTL_DMP_EN           0x80
#define C6DOFIMU5_USER_CTL_FIFO_EN          0x40
#define C6DOFIMU5_USER_CTL_I2C_IF_DIS       0x10
#define C6DOFIMU5_USER_CTL_DMP_RST          0x08
#define C6DOFIMU5_USER_CTL_FIFO_RST         0x04
#define C6DOFIMU5_USER_CTL_SIG_COND_RST     0x01
/** \} */

/**
 * \defgroup power_management_1_register_commands Power Management 1 Register Commands
 * \{
 */
#define C6DOFIMU5_PWR_MGMT_1_DEV_RST        0x80
#define C6DOFIMU5_PWR_MGMT_1_SLEEP          0x40
#define C6DOFIMU5_PWR_MGMT_1_ACCEL_CYC      0x20
#define C6DOFIMU5_PWR_MGMT_1_GYRO_STDBY     0x10
#define C6DOFIMU5_PWR_MGMT_1_TEMP_DIS       0x08
#define C6DOFIMU5_PWR_MGMT_1_CLKSEL_7       0x07
#define C6DOFIMU5_PWR_MGMT_1_CLKSEL_6       0x06
#define C6DOFIMU5_PWR_MGMT_1_CLKSEL_5       0x05
#define C6DOFIMU5_PWR_MGMT_1_CLKSEL_4       0x04
#define C6DOFIMU5_PWR_MGMT_1_CLKSEL_3       0x03
#define C6DOFIMU5_PWR_MGMT_1_CLKSEL_2       0x02
#define C6DOFIMU5_PWR_MGMT_1_CLKSEL_1       0x01
#define C6DOFIMU5_PWR_MGMT_1_CLKSEL_0       0x00
/** \} */

/**
 * \defgroup power_management_2_register_commands Power Management 2 Register Commands
 * \{
 */
#define C6DOFIMU5_PWR_MGMT_2_LP_DIS         0x80
#define C6DOFIMU5_PWR_MGMT_2_DMP_LP_DIS     0x40
#define C6DOFIMU5_PWR_MGMT_2_DISABLE_XA     0x20
#define C6DOFIMU5_PWR_MGMT_2_DISABLE_YA     0x10
#define C6DOFIMU5_PWR_MGMT_2_DISABLE_ZA     0x08
#define C6DOFIMU5_PWR_MGMT_2_DISABLE_XG     0x04
#define C6DOFIMU5_PWR_MGMT_2_DISABLE_YG     0x02
#define C6DOFIMU5_PWR_MGMT_2_DISABLE_ZG     0x01
/** \} */

/**
 * \defgroup who_am_i_register_value Who Am I Register Value
 * \{
 */
#define C6DOFIMU5_WHO_AM_I_VAL              0x03
/** \} */

/**
 * \defgroup i2c_temperature_and_pressure_commands I2C Temperature and Pressure commands
 * \{
 */
#define C6DOFIMU5_MEAS_CMD_LP_TRANS_T_FIRST     0x609C
#define C6DOFIMU5_MEAS_CMD_N_TRANS_T_FIRST      0x6825
#define C6DOFIMU5_MEAS_CMD_LN_TRANS_T_FIRST     0x70DF
#define C6DOFIMU5_MEAS_CMD_ULN_TRANS_T_FIRST    0x7866
#define C6DOFIMU5_MEAS_CMD_LP_TRANS_P_FIRST     0x401A
#define C6DOFIMU5_MEAS_CMD_N_TRANS_P_FIRST      0x48A3
#define C6DOFIMU5_MEAS_CMD_LN_TRANS_P_FIRST     0x5059
#define C6DOFIMU5_MEAS_CMD_ULN_TRANS_P_FIRST    0x58E0
#define C6DOFIMU5_DEVICE_SOFT_RESET_CMD         0x805D
#define C6DOFIMU5_READ_ID_REGISTER              0xEFC8
#define C6DOFIMU5_INCREMENTAL_READ              0xC7F7
#define C6DOFIMU5_ADR_REG_MOVE_POINTER          0xC595
/** \} */

/**
 * \defgroup power_states Power States
 * \{
 */
#define C6DOFIMU5_POWER_ON      0x01
#define C6DOFIMU5_POWER_OFF     0x00
/** \} */

/**
 * \defgroup sensor_sensitivity_values Sensor Sensitivity values
 * \{
 */
#define C6DOFIMU5_GYRO_SENS_FS_SEL_2000         16.4
#define C6DOFIMU5_GYRO_SENS_FS_SEL_1000         32.8
#define C6DOFIMU5_GYRO_SENS_FS_SEL_500          65.5
#define C6DOFIMU5_GYRO_SENS_FS_SEL_250          131.0
#define C6DOFIMU5_ACCEL_SENS_FS_SEL_16G         2048.0
#define C6DOFIMU5_ACCEL_SENS_FS_SEL_8G          4096.0
#define C6DOFIMU5_ACCEL_SENS_FS_SEL_4G          8192.0
#define C6DOFIMU5_ACCEL_SENS_FS_SEL_2G          16384.0
/** \} */

/**
 * \defgroup constant_values Constant Values
 * \{
 */
#define C6DOFIMU5_LUT_LOWER      3670016.0
#define C6DOFIMU5_LUT_UPPER      12058624.0
#define C6DOFIMU5_QUADR_FACTOR   0.000000059604644775390625
#define C6DOFIMU5_OFFST_FACTOR   2048.0
#define C6DOFIMU5_P_PA_CALIB_0   45000.0
#define C6DOFIMU5_P_PA_CALIB_1   80000.0
#define C6DOFIMU5_P_PA_CALIB_2   105000.0
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
    uint32_t p_raw;
    uint16_t t_raw;
    float pressure;
    float temperature;
} c6dofimu5_process_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu5_s
{
    // Input pins 

    digital_out_t cs;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;

   float sens_const_0;
   float sens_const_1;
   float sens_const_2;
   float sens_const_3;

} c6dofimu5_t;

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

} c6dofimu5_cfg_t;

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
void c6dofimu5_cfg_setup ( c6dofimu5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU5_RETVAL c6dofimu5_init ( c6dofimu5_t *ctx, c6dofimu5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for C6DOF IMU 5 click.
 */
void c6dofimu5_default_cfg ( c6dofimu5_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx       Click object.
 * @param reg       8-bit register address.
 * @param wr_data   8-bit write data.
 * @param n_bytes   16-bit number of bytes.
 *
 * @description This function writes user defined number of bytes into registers defined by 8-bit register 
 * address.
 */
void c6dofimu5_write_bytes ( c6dofimu5_t *ctx, uint8_t reg, uint8_t *wr_data, uint16_t n_bytes );

/**
 * @brief Generic read function.
 *
 * @param ctx       Click object.
 * @param reg       8-bit register address.
 * @param rd_data   8-bit read data.
 * @param n_bytes   16-bit number of bytes.
 *
 * @description This function reads user defined number of bytes from registers defined by 8-bit register 
 * address.
 */
void c6dofimu5_read_bytes ( c6dofimu5_t *ctx, uint8_t reg, uint8_t *rd_data, uint16_t n_bytes );

/**
 * @brief Power up function.
 *
 * @param ctx       Click object.
 * @param on_off    Value defines power state of the device.
 *
 * @description This function turns the device on or off.
 * @note It is advisable to use predefined values.
 */
void c6dofimu5_power ( c6dofimu5_t *ctx, uint8_t on_off );

/**
 * @brief Read Gyroscope X-axis data function.
 *
 * @param ctx       Click object.
 *
 * @description This function is used to read gyroscope X-axis data.
 */
int16_t c6dofimu5_read_gyro_x ( c6dofimu5_t *ctx );

/**
 * @brief Read Gyroscope Y-axis data function.
 *
 * @param ctx       Click object.
 *
 * @description This function is used to read gyroscope Y-axis data.
 */
int16_t c6dofimu5_read_gyro_y ( c6dofimu5_t *ctx );

/**
 * @brief Read Gyroscope Z-axis data function.
 *
 * @param ctx       Click object.
 *
 * @description This function is used to read gyroscope Z-axis data.
 */
int16_t c6dofimu5_read_gyro_z ( c6dofimu5_t *ctx );

/**
 * @brief Read gyroscope data function.
 *
 * @param ctx     Click object.
 * @param gyro_x  16-bit gyroscope X-axis data.
 * @param gyro_y  16-bit gyroscope Y-axis data.
 * @param gyro_z  16-bit gyroscope Z-axis data. 
 *
 * @description This function is used to read gyroscope data.
 */
void c6dofimu5_read_gyroscope ( c6dofimu5_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );

/**
 * @brief Read Angular Rate function.
 *
 * @param ctx        Click object.
 * @param x_ang_rte  float X-axis angular rate.
 * @param y_ang_rte  float Y-axis angular rate.
 * @param z_ang_rte  float Z-axis angular rate.
 *
 * @description This function is used to calculate angular rate.
 */
void c6dofimu5_angular_rate ( c6dofimu5_t *ctx, float *x_ang_rte, float *y_ang_rte, float *z_ang_rte );

/**
 * @brief Read Accelerometer X-axis data function.
 *
 * @param ctx        Click object.
 *
 * @description This function is used to read accelerometer X-axis data.
 */
int16_t c6dofimu5_read_accel_x ( c6dofimu5_t *ctx );

/**
 * @brief Read Accelerometer Y-axis data function.
 *
 * @param ctx        Click object.
 *
 * @description This function is used to read accelerometer Y-axis data.
 */
int16_t c6dofimu5_read_accel_y ( c6dofimu5_t *ctx );

/**
 * @brief Read Accelerometer Z-axis data function.
 *
 * @param ctx        Click object.
 *
 * @description This function is used to read accelerometer Z-axis data.
 */
int16_t c6dofimu5_read_accel_z ( c6dofimu5_t *ctx );

/**
 * @brief Read accelerometer data function.
 *
 * @param ctx      Click object.
 * @param accel_x  16-bit accelerometer X-axis data.
 * @param accel_y  16-bit accelerometer Y-axis data.
 * @param accel_z  16-bit accelerometer Z-axis data.
 *
 * @description This function is used to read accelerometer data.
 */
void c6dofimu5_read_accelerometer ( c6dofimu5_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );

/**
 * @brief Read acceleration Rate function.
 *
 * @param ctx          Click object.
 * @param x_accel_rte  float X-axis acceleration rate.
 * @param y_accel_rte  float Y-axis acceleration rate.
 * @param z_accel_rte  float Z-axis acceleration rate.
 *
 * @description This function is used to calculate acceleration rate.
 */
void c6dofimu5_acceleration_rate ( c6dofimu5_t *ctx, float *x_accel_rte, float *y_accel_rte, float *z_accel_rte );

/**
 * @brief Read temperture function.
 *
 * @param ctx          Click object.
 *
 * @description This function is used to read temperture in degree Centigrade.
 */
float c6dofimu5_read_temp_out ( c6dofimu5_t *ctx );

/**
 * @brief Barometer Read function.
 *
 * @param ctx      Click object.
 * @param cmd      16-bit command.
 * @param rd_data  8-bit read data.
 * @param n_bytes  16-bit number of bytes.
 *
 * @description This function reads response to the command given by user.
 */
void c6dofimu5_baro_read ( c6dofimu5_t *ctx, uint16_t cmd, uint8_t *data_out, uint16_t n_bytes );

/**
 * @brief Barometer Write function.
 *
 * @param ctx      Click object.
 * @param data_in  8-bit write data.
 * @param n_bytes  16-bit number of bytes.
 *
 * @description This function writes user defined number of bytes.
 */
void c6dofimu5_baro_write ( c6dofimu5_t *ctx, uint8_t *data_in, uint16_t n_bytes );

/**
 * @brief I2C Barometer Settings function.
 *
 * @param ctx      Click object.
 *
 * @description This function is used to apply barometer settings.
 * @note Should be used in order to get temperature and pressure readings 
 * from the device.
 */
void c6dofimu5_baro_settings ( c6dofimu5_t *ctx );

/**
 * @brief Barometer ID Readout function.
 *
 * @param ctx      Click object.
 *
 * @description This function is used to read  barometer ID number.
 */
uint8_t c6dofimu5_baro_id_read ( c6dofimu5_t *ctx );

/**
 * @brief Soft Reset Command function.
 *
 * @param ctx      Click object.
 *
 * @description This function is used to perform soft rest.
 */
void c6dofimu5_baro_soft_rst ( c6dofimu5_t *ctx );

/**
 * @brief Process data function.
 *
 * @param ctx           Click object.
 * @param process_d     Process data structure.
 *
 * @description This function processes raw data in order to get presure(in Pascals) and 
 * temperature(in degree Centigrade).
 */
void c6dofimu5_process_data ( c6dofimu5_t *ctx, c6dofimu5_process_data_t *process_d );

/**
 * @brief Read raw data function.
 *
 * @param ctx   Click object.
 * @param pres  32-bit raw pressure data.
 * @param temp  16-bit raw temperature data.
 *
 * @description This function is used to get raw temperature and pressure values.
 */
void c6dofimu5_read_raw_data ( c6dofimu5_t *ctx, uint32_t *pres, uint16_t *temp );

/**
 * @brief Check Interrupt state function.
 *
 * @param ctx   Click object.
 *
 * @description This function is used to check if an interrupt has occured.
 */
uint8_t c6dofimu5_check_int_pin ( c6dofimu5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
