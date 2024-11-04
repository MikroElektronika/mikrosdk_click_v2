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
 * \brief This file contains API for 10DOF Click driver.
 *
 * \addtogroup c10dof 10DOF Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C10DOF_H
#define C10DOF_H

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


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define C10DOF_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C10DOF_RETVAL  uint8_t

#define C10DOF_OK           0x00
#define C10DOF_INIT_ERROR   0xFF
/** \} */
/**
 * \defgroup BNO055 REGISTER MAP
 * \{
 */
#define C10DOF_BNO055_ADDRESS_A                                0x28
#define C10DOF_BNO055_ADDRESS_B                                0x29
#define C10DOF_BNO055_ID                                       0xA0
/** \} */

/**
 * \defgroup Page 0 id register definition
 * \{
 */ 
#define C10DOF_BNO055_PAGE_ID_ADDR                             0x07
#define C10DOF_BNO055_CHIP_ID_ADDR                             0x00
#define C10DOF_BNO055_ACCEL_REV_ID_ADDR                        0x01
#define C10DOF_BNO055_MAG_REV_ID_ADDR                          0x02
#define C10DOF_BNO055_GYRO_REV_ID_ADDR                         0x03
#define C10DOF_BNO055_SW_REV_ID_LSB_ADDR                       0x04
#define C10DOF_BNO055_SW_REV_ID_MSB_ADDR                       0x05
#define C10DOF_BNO055_BL_REV_ID_ADDR                           0X06
/** \} */

/**
 * \defgroup Accel data register
 * \{
 */  
#define C10DOF_BNO055_ACCEL_DATA_X_LSB_ADDR                    0x08
#define C10DOF_BNO055_ACCEL_DATA_X_MSB_ADDR                    0x09
#define C10DOF_BNO055_ACCEL_DATA_Y_LSB_ADDR                    0x0A
#define C10DOF_BNO055_ACCEL_DATA_Y_MSB_ADDR                    0x0B
#define C10DOF_BNO055_ACCEL_DATA_Z_LSB_ADDR                    0x0C
#define C10DOF_BNO055_ACCEL_DATA_Z_MSB_ADDR                    0x0D
/** \} */

/**
 * \defgroup Mag data register
 * \{
 */    
#define C10DOF_BNO055_MAG_DATA_X_LSB_ADDR                      0x0E
#define C10DOF_BNO055_MAG_DATA_X_MSB_ADDR                      0x0F
#define C10DOF_BNO055_MAG_DATA_Y_LSB_ADDR                      0x10
#define C10DOF_BNO055_MAG_DATA_Y_MSB_ADDR                      0x11
#define C10DOF_BNO055_MAG_DATA_Z_LSB_ADDR                      0x12
#define C10DOF_BNO055_MAG_DATA_Z_MSB_ADDR                      0x13
/** \} */

/**
 * \defgroup gyro_data_registers 
 * \{
 */ 
#define C10DOF_BNO055_GYRO_DATA_X_LSB_ADDR                     0x14
#define C10DOF_BNO055_GYRO_DATA_X_MSB_ADDR                     0x15
#define C10DOF_BNO055_GYRO_DATA_Y_LSB_ADDR                     0x16
#define C10DOF_BNO055_GYRO_DATA_Y_MSB_ADDR                     0x17
#define C10DOF_BNO055_GYRO_DATA_Z_LSB_ADDR                     0x18
#define C10DOF_BNO055_GYRO_DATA_Z_MSB_ADDR                     0x19
/** \} */

/**
 * \defgroup euler_data_registers Euler data registers
 * \{
 */ 
#define C10DOF_BNO055_EULER_H_LSB_ADDR                         0x1A
#define C10DOF_BNO055_EULER_H_MSB_ADDR                         0x1B
#define C10DOF_BNO055_EULER_R_LSB_ADDR                         0x1C
#define C10DOF_BNO055_EULER_R_MSB_ADDR                         0x1D
#define C10DOF_BNO055_EULER_P_LSB_ADDR                         0x1E
#define C10DOF_BNO055_EULER_P_MSB_ADDR                         0x1F
/** \} */

/**
 * \defgroup quaternion_data_registers Quaternion data registers
 * \{
 */
#define C10DOF_BNO055_QUATERNION_DATA_W_LSB_ADDR               0x20
#define C10DOF_BNO055_QUATERNION_DATA_W_MSB_ADDR               0x21
#define C10DOF_BNO055_QUATERNION_DATA_X_LSB_ADDR               0x22
#define C10DOF_BNO055_QUATERNION_DATA_X_MSB_ADDR               0x23
#define C10DOF_BNO055_QUATERNION_DATA_Y_LSB_ADDR               0x24
#define C10DOF_BNO055_QUATERNION_DATA_Y_MSB_ADDR               0x25
#define C10DOF_BNO055_QUATERNION_DATA_Z_LSB_ADDR               0x26
#define C10DOF_BNO055_QUATERNION_DATA_Z_MSB_ADDR               0x27
/** \} */

/**
 * \defgroup linear_acceleration_data_registers Linear acceleration data registers
 * \{
 */
#define C10DOF_BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR             0x28
#define C10DOF_BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR             0x29
#define C10DOF_BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR             0x2A
#define C10DOF_BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR             0x2B
#define C10DOF_BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR             0x2C
#define C10DOF_BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR             0x2D
/** \} */

/**
 * \defgroup gravity_data_registers Gravity data registers
 * \{
 */
#define C10DOF_BNO055_GRAVITY_DATA_X_LSB_ADDR                  0x2E
#define C10DOF_BNO055_GRAVITY_DATA_X_MSB_ADDR                  0x2F
#define C10DOF_BNO055_GRAVITY_DATA_Y_LSB_ADDR                  0x30
#define C10DOF_BNO055_GRAVITY_DATA_Y_MSB_ADDR                  0x31
#define C10DOF_BNO055_GRAVITY_DATA_Z_LSB_ADDR                  0x32
#define C10DOF_BNO055_GRAVITY_DATA_Z_MSB_ADDR                  0x33
/** \} */

/**
 * \defgroup temperature_data_registers Temperature data registers
 * \{
 */
#define C10DOF_BNO055_TEMP_ADDR                                0x34
/** \} */

/**
 * \defgroup status_registers Status registers
 * \{
 */
#define C10DOF_BNO055_CALIB_STAT_ADDR                          0x35
#define C10DOF_BNO055_SELFTEST_RESULT_ADDR                     0x36
#define C10DOF_BNO055_INTR_STAT_ADDR                           0x37
#define C10DOF_BNO055_SYS_CLK_STAT_ADDR                        0x38
#define C10DOF_BNO055_SYS_STAT_ADDR                            0x39
#define C10DOF_BNO055_SYS_ERR_ADDR                             0x3A
/** \} */

/**
 * \defgroup unit_seleciton_registers Unit selection registers
 * \{
 */
#define C10DOF_BNO055_UNIT_SEL_ADDR                            0x3B
#define C10DOF_BNO055_DATA_SELECT_ADDR                         0x3C
/** \} */

/**
 * \defgroup mode_registers Mode registers
 * \{
 */
#define C10DOF_BNO055_OPR_MODE_ADDR                            0x3D
#define C10DOF_BNO055_PWR_MODE_ADDR                            0x3E
#define C10DOF_BNO055_SYS_TRIGGER_ADDR                         0x3F
#define C10DOF_BNO055_TEMP_SOURCE_ADDR                         0x40
/** \} */

/**
 * \defgroup axis_remap_registers Axis remap registers
 * \{
 */
#define C10DOF_BNO055_AXIS_MAP_CONFIG_ADDR                     0x41
#define C10DOF_BNO055_AXIS_MAP_SIGN_ADDR                       0x42
/** \} */

/**
 * \defgroup sic_registers SIC registers
 * \{
 */
#define C10DOF_BNO055_SIC_MATRIX_0_LSB_ADDR                    0x43
#define C10DOF_BNO055_SIC_MATRIX_0_MSB_ADDR                    0x44
#define C10DOF_BNO055_SIC_MATRIX_1_LSB_ADDR                    0x45
#define C10DOF_BNO055_SIC_MATRIX_1_MSB_ADDR                    0x46
#define C10DOF_BNO055_SIC_MATRIX_2_LSB_ADDR                    0x47
#define C10DOF_BNO055_SIC_MATRIX_2_MSB_ADDR                    0x48
#define C10DOF_BNO055_SIC_MATRIX_3_LSB_ADDR                    0x49
#define C10DOF_BNO055_SIC_MATRIX_3_MSB_ADDR                    0x4A
#define C10DOF_BNO055_SIC_MATRIX_4_LSB_ADDR                    0x4B
#define C10DOF_BNO055_SIC_MATRIX_4_MSB_ADDR                    0x4C
#define C10DOF_BNO055_SIC_MATRIX_5_LSB_ADDR                    0x4D
#define C10DOF_BNO055_SIC_MATRIX_5_MSB_ADDR                    0x4E
#define C10DOF_BNO055_SIC_MATRIX_6_LSB_ADDR                    0x4F
#define C10DOF_BNO055_SIC_MATRIX_6_MSB_ADDR                    0x50
#define C10DOF_BNO055_SIC_MATRIX_7_LSB_ADDR                    0x51
#define C10DOF_BNO055_SIC_MATRIX_7_MSB_ADDR                    0x52
#define C10DOF_BNO055_SIC_MATRIX_8_LSB_ADDR                    0x53
#define C10DOF_BNO055_SIC_MATRIX_8_MSB_ADDR                    0x54
/** \} */

/**
 * \defgroup accelerometer_offset_registers Accelerometer Offset registers
 * \{
 */
#define C10DOF_ACCEL_OFFSET_X_LSB_ADDR                         0x55
#define C10DOF_ACCEL_OFFSET_X_MSB_ADDR                         0x56
#define C10DOF_ACCEL_OFFSET_Y_LSB_ADDR                         0x57
#define C10DOF_ACCEL_OFFSET_Y_MSB_ADDR                         0x58
#define C10DOF_ACCEL_OFFSET_Z_LSB_ADDR                         0x59
#define C10DOF_ACCEL_OFFSET_Z_MSB_ADDR                         0x5A
/** \} */

/**
 * \defgroup magnetometer_offset_registers Magnetometer Offset registers
 * \{
 */
#define C10DOF_MAG_OFFSET_X_LSB_ADDR                           0x5B
#define C10DOF_MAG_OFFSET_X_MSB_ADDR                           0x5C
#define C10DOF_MAG_OFFSET_Y_LSB_ADDR                           0x5D
#define C10DOF_MAG_OFFSET_Y_MSB_ADDR                           0x5E
#define C10DOF_MAG_OFFSET_Z_LSB_ADDR                           0x5F
#define C10DOF_MAG_OFFSET_Z_MSB_ADDR                           0x60
/** \} */

/**
 * \defgroup gyroscope_offset_registers Gyroscope Offset registers
 * \{
 */
#define C10DOF_GYRO_OFFSET_X_LSB_ADDR                          0x61
#define C10DOF_GYRO_OFFSET_X_MSB_ADDR                          0x62
#define C10DOF_GYRO_OFFSET_Y_LSB_ADDR                          0x63
#define C10DOF_GYRO_OFFSET_Y_MSB_ADDR                          0x64
#define C10DOF_GYRO_OFFSET_Z_LSB_ADDR                          0x65
#define C10DOF_GYRO_OFFSET_Z_MSB_ADDR                          0x66
/** \} */

/**
 * \defgroup radius_registers Radius registers
 * \{
 */
#define C10DOF_ACCEL_RADIUS_LSB_ADDR                           0x67
#define C10DOF_ACCEL_RADIUS_MSB_ADDR                           0x68
#define C10DOF_MAG_RADIUS_LSB_ADDR                             0x69
#define C10DOF_MAG_RADIUS_MSB_ADDR                             0x6A
/** \} */

/**
 * \defgroup BN0180_register_map BNO180 REGISTER MAP
 * \{
 */
#define C10DOF_BMP180_ADDRESS                                 0x77
#define C10DOF_BMP180_PROM_START__ADDR                        0xAA
#define C10DOF_BMP180_CHIP_ID_REG                             0xD0
#define C10DOF_BMP180_VERSION_REG                             0xD1
#define C10DOF_BMP180_CTRL_MEAS_REG                           0xF4
#define C10DOF_BMP180_ADC_OUT_MSB_REG                         0xF6
#define C10DOF_BMP180_ADC_OUT_LSB_REG                         0xF7
#define C10DOF_BMP180_SOFT_RESET_REG                          0xE0
#define C10DOF_BMP180_REG_CALIB_PARAM_AC1_MSB                 0xAA
#define C10DOF_BMP180_REG_CALIB_PARAM_AC1_LSB                 0xAB
#define C10DOF_BMP180_REG_CALIB_PARAM_AC2_MSB                 0xAC
#define C10DOF_BMP180_REG_CALIB_PARAM_AC2_LSB                 0xAD
#define C10DOF_BMP180_REG_CALIB_PARAM_AC3_MSB                 0xAE
#define C10DOF_BMP180_REG_CALIB_PARAM_AC3_LSB                 0xAF
#define C10DOF_BMP180_REG_CALIB_PARAM_AC4_MSB                 0xB0
#define C10DOF_BMP180_REG_CALIB_PARAM_AC4_LSB                 0xB1
#define C10DOF_BMP180_REG_CALIB_PARAM_AC5_MSB                 0xB2
#define C10DOF_BMP180_REG_CALIB_PARAM_AC5_LSB                 0xB3
#define C10DOF_BMP180_REG_CALIB_PARAM_AC6_MSB                 0xB4
#define C10DOF_BMP180_REG_CALIB_PARAM_AC6_LSB                 0xB5
#define C10DOF_BMP180_REG_CALIB_PARAM_B1_MSB                  0xB6
#define C10DOF_BMP180_REG_CALIB_PARAM_B1_LSB                  0xB7
#define C10DOF_BMP180_REG_CALIB_PARAM_B2_MSB                  0xB8
#define C10DOF_BMP180_REG_CALIB_PARAM_B2_LSB                  0xB9
#define C10DOF_BMP180_REG_CALIB_PARAM_MB_MSB                  0xBA
#define C10DOF_BMP180_REG_CALIB_PARAM_MB_LSB                  0xBB
#define C10DOF_BMP180_REG_CALIB_PARAM_MC_MSB                  0xBC
#define C10DOF_BMP180_REG_CALIB_PARAM_MC_LSB                  0xBD
#define C10DOF_BMP180_REG_CALIB_PARAM_MD_MSB                  0xBE
#define C10DOF_BMP180_REG_CALIB_PARAM_MD_LSB                  0xBF
#define C10DOF_BMP180_REG_CONF_ADDR                           0x07
#define C10DOF_BMP180_PWR_MODE_ADDR                           0x3E
#define C10DOF_BMP180_OPR_MODE_ADDR                           0x3D
#define C10DOF_BMP180_T_MEASURE                               0x2E
#define C10DOF_BMP180_P_MEASURE                               0x34
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

} c10dof_t;

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

} c10dof_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void c10dof_cfg_setup ( c10dof_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
C10DOF_RETVAL c10dof_init ( c10dof_t *ctx, c10dof_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for C10Dof Click.
 */
void c10dof_default_cfg ( c10dof_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_in      Data to be written.
 * @param slave_addr   Address of the chip we're using.
 *
 * @description This function writes data to the desired register.
 */
void c10dof_write_byte ( c10dof_t *ctx, uint8_t reg, uint8_t data_in, uint8_t slave_addr );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param slave_addr   Address of the chip we're using.
 *
 * @returns result    Output data.
 *
 * @description This function reads data from the desired register.
 */
uint8_t c10dof_read_byte ( c10dof_t *ctx, uint8_t reg, uint8_t slave_addr );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param msb_reg          Register address.
 * @param slave_addr   Address of the chip we're using.
 *
 * @returns result    Output data.
 *
 * @description This function reads data from the desired register.
 */
uint16_t c10dof_read_data ( c10dof_t *ctx, uint8_t msb_reg, uint8_t slave_addr );

/**
 * @brief Reset function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function resets the program.
 */
void c10dof_hw_reset ( c10dof_t *ctx );

/**
 * @brief ID function.
 *
 * 
 * @param ctx          Click object.
 *
 * @returns id_value   BNO180 ID value.
 *
 * @description This function reads the ID value od the BMP180 chip.
 */
uint8_t c10dof_bmp180_chip_ID ( c10dof_t *ctx );

/**
 * @brief ID function.
 *
 * 
 * @param ctx          Click object.
 *
 * @returns id_value   BNO055 ID value.
 *
 * @description This function reads the ID value od the BNO055 chip.
 */
uint8_t c10dof_bno055_chip_ID ( c10dof_t *ctx );

/**
 * @brief ID function.
 *
 * 
 * @param ctx          Click object.
 *
 * @returns id_value   BNO055 Accel ID value.
 *
 * @description This function reads the Accel ID value od the BNO055 chip.
 */
uint8_t c10dof_get_accel_ID ( c10dof_t *ctx );

/**
 * @brief ID function.
 *
 * 
 * @param ctx          Click object.
 *
 * @returns id_value   BNO055 Mag ID value.
 *
 * @description This function reads the Mag ID value od the BNO055 chip.
 */
uint8_t c10dof_get_mag_ID ( c10dof_t *ctx );

/**
 * @brief ID function.
 *
 * 
 * @param ctx          Click object.
 *
 * @returns id_value   BNO055 Gyro ID value.
 *
 * @description This function reads the Gyro ID value od the BNO055 chip.
 */
uint8_t c10dof_get_gyro_ID ( c10dof_t *ctx );

/**
 * @brief ID function.
 *
 * 
 * @param ctx          Click object.
 *
 * @returns id_value   BNO055 Software ID value. 
 *
 * @description This function reads the software ID value od the BNO055 chip.
 */
uint16_t c10dof_get_soft_ID ( c10dof_t *ctx );

/**
 * @brief ID function.
 *
 * 
 * @param ctx          Click object.
 *
 * @returns id_value   BNO055 Page ID value.
 *
 * @description This function reads the page ID value od the BNO055 chip.
 */
uint8_t c10dof_get_page_ID ( c10dof_t *ctx );

/**
 * @brief Configuration function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function sets default configuration for the BMP180 sensor function.
 */
 void c10dof_default_configuration_BMP180 ( c10dof_t *ctx );

 /**
 * @brief Configuration function.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function sets default configuration for the BNO055 sensor function.
 */
 void c10dof_default_configuration_BNO055 ( c10dof_t *ctx );

 /**
 * @brief Configuration function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @param config_mode  Configuration mode.
 *
 * @description        Set configuration mode function.
 */
void c10dof_set_config_mode ( c10dof_t *ctx, uint8_t config_mode );

 /**
 * @brief Page selection function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @param page_number  Page number.
 *
 * @description        Select page number function.
 */
void c10dof_select_page ( c10dof_t *ctx, uint8_t page_number );

 /**
 * @brief Accel configuration function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @param acc_cnfg     Accel configuration register.
 *
 * @description        Set Accel configuration function.
 */
void c10dof_config_accel ( c10dof_t *ctx, uint8_t acc_cnfg );

 /**
 * @brief Gyro configuration function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @param gyro_cnfg    Gyro configuration register.
 *
 * @description        Set Gyro configuration function.
 */
void c10dof_config_gyro ( c10dof_t *ctx, uint8_t gyro_cnfg );

 /**
 * @brief Mag configuration function.
 *
 * 
 * @param ctx          Click object.
 * 
 * @param mag_cnfg     Mag configuration register.
 *
 * @description        Set Mag configuration function.
 */
void c10dof_config_mag ( c10dof_t *ctx, uint8_t mag_cnfg );

 /**
 * @brief Sensor units function.
 *
 * 
 * @param ctx           Click object.
 * 
 * @param sensor_units  Sensor units.
 *
 * @description        Configurate sensor units function.
 */
void c10dof_set_sensor_units ( c10dof_t *ctx, uint8_t sensor_units );

  /**
 * @brief System status code.
 *
 * 
 * @param ctx            Click object.
 *
 * @returns error_code   Error Code.
 * 
 * @description        Get the system status code of BNO055  function.
 */
uint8_t c10dof_get_system_status ( c10dof_t *ctx );

  /**
 * @brief System error code.
 *
 * 
 * @param ctx          Click object.
 *
 * @returns error_code
 * 
 * @description       Get the system error code of BNO055  function.
 */
uint8_t c10dof_get_system_error ( c10dof_t *ctx );

  /**
 * @brief Mode.
 *
 * 
 * @param ctx          Click object.
 * @param mode_value   Mode value.
 * 
 * @description       Set mode mode function.
 */
void c10dof_set_mode( c10dof_t *ctx, uint8_t mode_val );

  /**
 * @brief Normal mode.
 *
 * 
 * @param ctx          Click object.
 * 
 * @description        Set normal mode mode function.
 */
void c10dof_set_normal_mode ( c10dof_t *ctx );

  /**
 * @brief Temperature reading start.
 *
 * 
 * @param ctx          Click object.
 *  
 * @description        Begin a temperature reading function.
 */
void c10dof_start_temperature_measure ( c10dof_t *ctx );

  /**
 * @brief Pressure reading start.
 *
 * 
 * @param ctx          Click object.
 * 
 * @description        Begin a pressure reading function.
 */
void c10dof_start_pressure_measure ( c10dof_t *ctx );

  /**
 * @brief Raw temperature reading.
 *
 * 
 * @param ctx          Click object.
 * @param msb_reg      Register.
 * 
 * @description  Function read the raw temperature data from the two target register address of BMP180 chip on 10DOF Click board.
 */
int16_t c10dof_read_raw_temperature ( c10dof_t *ctx, uint8_t msb_reg );

  /**
 * @brief Raw pressure reading.
 *
 * 
 * @param ctx          Click object.
 * @param msb_addr      Register.
 * 
 * @description  Function read the raw temperature data from the three target register address of BMP180 chip on 10DOF Click board.
 */
int32_t c10dof_read_raw_pressure ( c10dof_t *ctx, uint8_t msb_addr );

/**
 * @brief Read the calibration parameter function
 *
 * @param ctx         Click object.
 *
 * @description Function get the calibration parameter values from the target register address of BMP180 chip on 10DOF Click board.
 */
void c10dof_get_calib_param ( c10dof_t *ctx );

/**
 * @brief Get measurements value - temperature and pressure data function
 *
 * @param temperature                     pointer to measurements temperature value
 * @param pressure                        pointer to measurements pressure value
 *
 * @description Function measurements the temperature and pressure value of BMP180 chip on 10DOF Click board.
 */
void c10dof_get_measurements ( c10dof_t *ctx, float *temperature, float *pressure );

/**
 * @brief Get temperature value function
 *
 * @param ctx   Click object.
 *
 * @returns     float measurements temperature value
 *
 * @description Function measurements the temperature value of BMP180 chip on 10DOF Click board.
 */
float c10dof_get_temperature ( c10dof_t *ctx );

/**
 * @brief Get pressure value function
 *
 * @param ctx    Click object.
 *
 * @returns      float measurements pressure value
 *
 * @description Function measurements the pressure value of BMP180 chip on 10DOF Click board.
 */
float c10dof_get_pressure ( c10dof_t *ctx );

/**
 * @brief Function get axis data of BNO055 register
 *
 * @param addr_reg_low         low data register address
 * @param ctx                   Click object.
 *
 * @returns         16-bit ( signed ) target axis value
 *
 * @description Function get axis data by read two target register address of BNO055 chip on 10DOF Click board.
 */
int16_t c10dof_get_axis( c10dof_t *ctx, uint8_t addr_reg_low );

/**
 * @brief Function read Accel X-axis, Y-axis and Z-axis
 *
 * @param ctx                 Click object.
 * @param accelX             pointer to read Accel X-axis data
 * @param accelY             pointer to read Accel Y-axis data
 * @param accelZ             pointer to read Accel Z-axis data
 *
 * @description Function read Accel X-axis, Y-axis and Z-axis axis of BNO055 chip on 10DOF Click board.
 */
void c10dof_read_accel ( c10dof_t *ctx, int16_t *accelX, int16_t *accelY, int16_t *accelZ );

/**
 * @brief Function read Magnetometar X-axis, Y-axis and Z-axis
 *
 * @param ctx                Click object.
 * @param magX               pointer to read Mag X-axis data
 * @param magY               pointer to read Mag Y-axis data
 * @param magZ               pointer to read Mag Z-axis data
 *
 * @description Function read Mag X-axis, Y-axis and Z-axis axis of BNO055 chip on 10DOF Click board.
 */
void c10dof_read_mag ( c10dof_t *ctx, int16_t *magX, int16_t *magY, int16_t *magZ );

/**
 * @brief Function read Gyro X-axis, Y-axis and Z-axis axis
 *
 * @param ctx                Click object.
 * 
 * @param gyroX              pointer to read Gyro X-axis data
 * 
 * @param gyroY              pointer to read Gyro Y-axis data
 * 
 * @param gyroZ              pointer to read Gyro Z-axis data
 *
 * @description Function read Gyro X-axis, Y-axis and Z-axis axis of BNO055 chip on 10DOF Click board.
 */
void c10dof_read_gyro ( c10dof_t *ctx, int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ );

/**
 * @brief Check the state of interrupt function
 *
 * @param ctx      Click object
 * 
 * @returns        State of the INT pin: - ( 0 : inactive - 1 : active )
 *
 * @description Function check the state of interrupt by gets states of INT pin of 10DOF Click board.
 */
uint8_t c10dof_check_interrupt ( c10dof_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C10DOF_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
