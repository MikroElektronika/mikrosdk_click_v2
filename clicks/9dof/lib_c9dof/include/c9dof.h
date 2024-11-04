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
 * \brief This file contains API for 9 DOF Click driver.
 *
 * \addtogroup c9dof 9 DOF Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C9DOF_H
#define C9DOF_H

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
#define C9DOF_MAP_MIKROBUS( cfg, mikrobus )         \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL );    \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );    \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );      \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C9DOF_RETVAL  uint8_t

#define C9DOF_OK           0x00
#define C9DOF_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address I2C slave address
 * \{
 */
#define C9DOF_SLAVE_ADDRESS_ACCEL_GYRO_0       0x6A  
#define C9DOF_SLAVE_ADDRESS_MAG_0              0x1C  
#define C9DOF_SLAVE_ADDRESS_ACCEL_GYRO_1       0x6B   
#define C9DOF_SLAVE_ADDRESS_MAG_1              0x1E 
/** \} */

/**
 * \defgroup reg Accel & Gyro register address
 * \{
 */
#define C9DOF_REG_ACT_THS                      0x04
#define C9DOF_REG_ACT_DUR                      0x05
#define C9DOF_REG_INT_GEN_CFG_XL               0x06
#define C9DOF_REG_INT_GEN_THS_X_XL             0x07
#define C9DOF_REG_INT_GEN_THS_Y_XL             0x08
#define C9DOF_REG_INT_GEN_THS_Z_XL             0x09
#define C9DOF_REG_INT_GEN_DUR_XL               0x0A
#define C9DOF_REG_REFERENCE_G                  0x0B
#define C9DOF_REG_INT1_CTRL                    0x0C
#define C9DOF_REG_INT2_CTRL                    0x0D
#define C9DOF_REG_WHO_AM_I                     0x0F
#define C9DOF_REG_CTRL_REG1_G                  0x10
#define C9DOF_REG_CTRL_REG2_G                  0x11
#define C9DOF_REG_CTRL_REG3_G                  0x12
#define C9DOF_REG_ORIENT_CFG_G                 0x13
#define C9DOF_REG_INT_GEN_SRC_G                0x14
#define C9DOF_REG_OUT_TEMP_L                   0x15
#define C9DOF_REG_OUT_TEMP_H                   0x16
#define C9DOF_REG_STATUS_REG                   0x17
#define C9DOF_REG_OUT_X_L_G                    0x18
#define C9DOF_REG_OUT_X_H_G                    0x19
#define C9DOF_REG_OUT_Y_L_G                    0x1A
#define C9DOF_REG_OUT_Y_H_G                    0x1B
#define C9DOF_REG_OUT_Z_L_G                    0x1C
#define C9DOF_REG_OUT_Z_H_G                    0x1D
#define C9DOF_REG_CTRL_REG4                    0x1E
#define C9DOF_REG_CTRL_REG5_XL                 0x1F
#define C9DOF_REG_CTRL_REG6_XL                 0x20
#define C9DOF_REG_CTRL_REG7_XL                 0x21
#define C9DOF_REG_CTRL_REG8                    0x22
#define C9DOF_REG_CTRL_REG9                    0x23
#define C9DOF_REG_CTRL_REG10                   0x24
#define C9DOF_REG_INT_GEN_SRC_XL               0x26
#define C9DOF_REG_OUT_X_L_XL                   0x28
#define C9DOF_REG_OUT_X_H_XL                   0x29
#define C9DOF_REG_OUT_Y_L_XL                   0x2A
#define C9DOF_REG_OUT_Y_H_XL                   0x2B
#define C9DOF_REG_OUT_Z_L_XL                   0x2C
#define C9DOF_REG_OUT_Z_H_XL                   0x2D
#define C9DOF_REG_FIFO_CTRL                    0x2E
#define C9DOF_REG_FIFO_SRC                     0x2F
#define C9DOF_REG_INT_GEN_CFG_G                0x30
#define C9DOF_REG_INT_GEN_THS_XH_G             0x31
#define C9DOF_REG_INT_GEN_THS_XL_G             0x32
#define C9DOF_REG_INT_GEN_THS_YH_G             0x33
#define C9DOF_REG_INT_GEN_THS_YL_G             0x34
#define C9DOF_REG_INT_GEN_THS_ZH_G             0x35
#define C9DOF_REG_INT_GEN_THS_ZL_G             0x36
#define C9DOF_REG_INT_GEN_DUR_G                0x37
/** \} */

/**
 * \defgroup reg Magn register address
 * \{
 */
#define C9DOF_REG_OFFSET_X_REG_L_M             0x05
#define C9DOF_REG_OFFSET_X_REG_H_M             0x06
#define C9DOF_REG_OFFSET_Y_REG_L_M             0x07
#define C9DOF_REG_OFFSET_Y_REG_H_M             0x08
#define C9DOF_REG_OFFSET_Z_REG_L_M             0x09
#define C9DOF_REG_OFFSET_Z_REG_H_M             0x0A
#define C9DOF_REG_CTRL_REG1_M                  0x20
#define C9DOF_REG_CTRL_REG2_M                  0x21
#define C9DOF_REG_CTRL_REG3_M                  0x22
#define C9DOF_REG_CTRL_REG4_M                  0x23
#define C9DOF_REG_CTRL_REG5_M                  0x24
#define C9DOF_REG_STATUS_REG_M                 0x27
#define C9DOF_REG_OUT_X_L_M                    0x28
#define C9DOF_REG_OUT_X_H_M                    0x29
#define C9DOF_REG_OUT_Y_L_M                    0x2A
#define C9DOF_REG_OUT_Y_H_M                    0x2B
#define C9DOF_REG_OUT_Z_L_M                    0x2C
#define C9DOF_REG_OUT_Z_H_M                    0x2D
#define C9DOF_REG_INT_CFG_M                    0x30
#define C9DOF_REG_INT_SRC_M                    0x31
#define C9DOF_REG_INT_THS_L_M                  0x32
#define C9DOF_REG_INT_THS_H_M                  0x33
/** \} */

/**
 * \defgroup reg Who am I default value
 * \{
 */
#define C9DOF_REG_XG_ID                        0x68
#define C9DOF_REG_MAG_ID                       0x3D
/** \} */

/**
 * \defgroup def_p_t Define pressure and temperature
 * \{
 */
#define C9DOF_CTRL_REG4_CONFIG                 0x38
#define C9DOF_CTRL_REG1_G_CONFIG               0x82
#define C9DOF_CTRL_REG5_XL_CONFIG              0x38
#define C9DOF_CTRL_REG6_XL_CONFIG              0x83
#define C9DOF_CTRL_REG8_CONFIG                 0x44
#define C9DOF_CTRL_REG1_M_CONFIG               0xD0
#define C9DOF_CTRL_REG2_M_CONFIG               0x00
#define C9DOF_CTRL_REG3_M_CONFIG               0x00
#define C9DOF_CTRL_REG4_M_CONFIG               0x08
#define C9DOF_CTRL_REG5_M_CONFIG               0x40
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

    digital_out_t en;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address_ag;
    uint8_t slave_address_m;

} c9dof_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address_ag;
    uint8_t i2c_address_m;

} c9dof_cfg_t;

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
    int16_t x;
    int16_t y;
    int16_t z;

} c9dof_accel_data_t;

/**
 * @brief Gyro data object definition.
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;

} c9dof_gyro_data_t;

/**
 * @brief Magnetometer data object definition.
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;

} c9dof_mag_data_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void c9dof_cfg_setup ( c9dof_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
C9DOF_RETVAL c9dof_init ( c9dof_t *ctx, c9dof_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 9Dof Click.
 * @note
 *    Click default configuration:
 * -------------------------------------------------
 * 
 * <pre>
 *    Enable accel and gyro sensors.
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG4
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG4_CONFIG
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG1_G
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG1_G_CONFIG
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG5_XL
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG5_XL_CONFIG
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG6_XL
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG6_XL_CONFIG
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG8
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG8_CONFIG
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG1_M
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG1_M_CONFIG
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG2_M
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG2_M_CONFIG
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG3_M
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG3_M_CONFIG
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG4_M
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG4_M_CONFIG
 * </pre>
 * 
 * <pre>
 *    reg     : C9DOF_REG_CTRL_REG5_M
 * -------------------------------------------------
 *    tx_data : C9DOF_CTRL_REG5_M_CONFIG
 * </pre>
 */
void c9dof_default_cfg ( c9dof_t *ctx );

/**
 * @brief Set accel and gyro power mode function.
 *
 * @param ctx        Click object.
 * @param pwr_mode   Power mode.
 * <pre>
 * 0 ( C9DOF_ACCEL_GYRO_POWER_MODE_OFF ) : Disable accel and gyro sensors.
 * </pre>
 * 
 * <pre>
 * 1 ( C9DOF_ACCEL_GYRO_POWER_MODE_ON )  : Enable accel and gyro sensors.
 * </pre> 
 *
 * @description This function sets power mode of the 9Dof Click.
 */
void c9dof_set_power_mode ( c9dof_t *ctx, uint8_t pwr_mode );

/**
 * @brief Generic accel and gyro write function.
 *
 * @param ctx          Click object.
 * @param reg          Accel and gyro register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes accel and gyro write data 
 * to the desired accel and gyro register of the LSM9DS1 module.
 */
void c9dof_generic_write_accel_gyro ( c9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic accel and gyro read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Accel and gyro register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads accel and gyro data 
 * from the desired accel and gyro register of the LSM9DS1 module.
 */
void c9dof_generic_read_accel_gyro ( c9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic mag write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes mag data 
 * to the desired mag register of the LSM9DS1 module.
 */
void c9dof_generic_write_mag ( c9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic mag read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Mag register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads mag data 
 * from the desired mag register of the LSM9DS1 module.
 */
void c9dof_generic_read_mag ( c9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get accelerometer data function.
 * 
 * @param ctx          Click object.
 * @param accel_data   Pointer to structure where Accel data be stored.
 *
 * @description This function reads Accel data ( X, Y and Z axis ) 
 * from the desired Accel registers of the LSM9DS1 module.
 */
void c9dof_read_accel ( c9dof_t *ctx, c9dof_accel_data_t *accel_data );

/**
 * @brief Get gyroscope data function.
 * 
 * @param ctx          Click object.
 * @param accel_data   Pointer to structure where Gyro data be stored.
 *
 * @description This function reads Gyro data ( X, Y and Z axis ) 
 * from the desired Gyro registers of the LSM9DS1 module.
 */
void c9dof_read_gyro ( c9dof_t *ctx, c9dof_gyro_data_t *gyro_data );

/**
 * @brief Get magnetometer data function.
 * 
 * @param ctx          Click object.
 * @param accel_data   Pointer to structure where Mag data be stored.
 *
 * @description This function reads Mag data ( X, Y and Z axis ) 
 * from the desired Mag registers of the LSM9DS1 module.
 */
void c9dof_read_mag ( c9dof_t *ctx, c9dof_mag_data_t *mag_data );

/**
 * @brief Get state of the Magnetic sensor interrupt function.
 *
 * @param ctx          Click object.
 *
 * @return
 * Magnetic sensor interrupt state:
 * <pre>
 *    0 : Not active.
 * </pre>
 * 
 * <pre>
 *    1 : Active.
 * </pre>
 * 
 * @description This function gets states of the 
 * Magnetic sensor interrupt of the LSM9DS1 module.
 */
uint8_t c9dof_get_interrupt ( c9dof_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C9DOF_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
