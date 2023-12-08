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
 * \brief This file contains API for 6 Dof imu 3 Click driver.
 *
 * \addtogroup c6dofimu3 6 Dof imu 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU3_H
#define C6DOFIMU3_H
#define c6dofimu3_obj_t       const uint8_t*
#define C6DOFIMU3_RETVAL_T     uint8_t

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

#define C6DOFIMU3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C6DOFIMU3_MASTER_I2C                             0
#define C6DOFIMU3_MASTER_SPI                             1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU3_RETVAL  uint8_t

#define C6DOFIMU3_OK                                     0x00
#define C6DOFIMU3_INIT_ERROR                             0xFF
/** \} */

/**
 * \defgroup I2C_slv_addr I2C slave address
 * \{
 */
#define C6DOFIMU3_REG_I2C_ADDR_0                         0x1E
#define C6DOFIMU3_REG_I2C_ADDR_1                         0x1D
#define C6DOFIMU3_REG_I2C_ADDR_2                         0x1C
#define C6DOFIMU3_REG_I2C_ADDR_3                         0x1F
/** \} */

/**
 * \defgroup reg_addr Register addresses
 * \{
 */
#define C6DOFIMU3_STATUS                                 0x00
#define C6DOFIMU3_DR_STATUS                              0x00
#define C6DOFIMU3_F_STATUS                               0x00
#define C6DOFIMU3_OUT_X_MSB                              0x01
#define C6DOFIMU3_OUT_X_LSB                              0x02
#define C6DOFIMU3_OUT_Y_MSB                              0x03
#define C6DOFIMU3_OUT_Y_LSB                              0x04
#define C6DOFIMU3_OUT_Z_MSB                              0x05
#define C6DOFIMU3_OUT_Z_LSB                              0x06
#define C6DOFIMU3_F_SETUP                                0x09
#define C6DOFIMU3_TRIG_CFG                               0x0A
#define C6DOFIMU3_SYSMOD                                 0x0B
#define C6DOFIMU3_INT_SOURCE                             0x0C
#define C6DOFIMU3_WHO_AM_I                               0x0D
#define C6DOFIMU3_XYZ_DATA_CFG                           0x0E
#define C6DOFIMU3_HP_FILTER_CUTOFF                       0x0F
#define C6DOFIMU3_PL_STATUS                              0x10
#define C6DOFIMU3_PL_CFG                                 0x11
#define C6DOFIMU3_PL_COUNT                               0x12
#define C6DOFIMU3_PL_BF_ZCOMP                            0x13
#define C6DOFIMU3_P_L_THS_REG                            0x14
#define C6DOFIMU3_A_FFMT_CFG                             0x15
#define C6DOFIMU3_A_FFMT_SRC                             0x16
#define C6DOFIMU3_A_FFMT_THS                             0x17
#define C6DOFIMU3_A_FFMT_COUNT                           0x18
#define C6DOFIMU3_TRANSIENT_CFG                          0x1D
#define C6DOFIMU3_TRANSIENT_SRC                          0x1E
#define C6DOFIMU3_TRANSIENT_THS                          0x1F
#define C6DOFIMU3_TRANSIENT_COUNT                        0x20
#define C6DOFIMU3_PULSE_CFG                              0x21
#define C6DOFIMU3_PULSE_SRC                              0x22
#define C6DOFIMU3_PULSE_THSX                             0x23
#define C6DOFIMU3_PULSE_THSY                             0x24
#define C6DOFIMU3_PULSE_THSZ                             0x25
#define C6DOFIMU3_PULSE_TMLT                             0x26
#define C6DOFIMU3_PULSE_LTCY                             0x27
#define C6DOFIMU3_PULSE_WIND                             0x28
#define C6DOFIMU3_ASLP_COUNT                             0x29
#define C6DOFIMU3_CTRL_REG1                              0x2A
#define C6DOFIMU3_CTRL_REG2                              0x2B
#define C6DOFIMU3_CTRL_REG3                              0x2C
#define C6DOFIMU3_CTRL_REG4                              0x2D
#define C6DOFIMU3_CTRL_REG5                              0x2E
#define C6DOFIMU3_OFF_X                                  0x2F
#define C6DOFIMU3_OFF_Y                                  0x30
#define C6DOFIMU3_OFF_Z                                  0x31
#define C6DOFIMU3_M_DR_STATUS                            0x32
#define C6DOFIMU3_M_OUT_X_MSB                            0x33
#define C6DOFIMU3_M_OUT_X_LSB                            0x34
#define C6DOFIMU3_M_OUT_Y_MSB                            0x35
#define C6DOFIMU3_M_OUT_Y_LSB                            0x36
#define C6DOFIMU3_M_OUT_Z_MSB                            0x37
#define C6DOFIMU3_M_OUT_Z_LSB                            0x38
#define C6DOFIMU3_CMP_OUT_X_MSB                          0x39
#define C6DOFIMU3_CMP_OUT_X_LSB                          0x3A
#define C6DOFIMU3_CMP_OUT_Y_MSB                          0x3B
#define C6DOFIMU3_CMP_OUT_Y_LSB                          0x3C
#define C6DOFIMU3_CMP_OUT_Z_MSB                          0x3D
#define C6DOFIMU3_CMP_OUT_Z_LSB                          0x3E
#define C6DOFIMU3_M_OFF_X_MSB                            0x3F
#define C6DOFIMU3_M_OFF_X_LSB                            0x40
#define C6DOFIMU3_M_OFF_Y_MSB                            0x41
#define C6DOFIMU3_M_OFF_Y_LSB                            0x42
#define C6DOFIMU3_M_OFF_Z_MSB                            0x43
#define C6DOFIMU3_M_OFF_Z_LSB                            0x44
#define C6DOFIMU3_MAX_X_MSB                              0x45
#define C6DOFIMU3_MAX_X_LSB                              0x46
#define C6DOFIMU3_MAX_Y_MSB                              0x47
#define C6DOFIMU3_MAX_Y_LSB                              0x48
#define C6DOFIMU3_MAX_Z_MSB                              0x49
#define C6DOFIMU3_MAX_Z_LSB                              0x4A
#define C6DOFIMU3_MIN_X_MSB                              0x4B
#define C6DOFIMU3_MIN_X_LSB                              0x4C
#define C6DOFIMU3_MIN_Y_MSB                              0x4D
#define C6DOFIMU3_MIN_Y_LSB                              0x4E
#define C6DOFIMU3_MIN_Z_MSB                              0x4F
#define C6DOFIMU3_MIN_Z_LSB                              0x50
#define C6DOFIMU3_TEMP                                   0x51
#define C6DOFIMU3_M_THS_CFG                              0x52
#define C6DOFIMU3_M_THS_SRC                              0x53
#define C6DOFIMU3_M_THS_X_MSB                            0x54
#define C6DOFIMU3_M_THS_X_LSB                            0x55
#define C6DOFIMU3_M_THS_Y_MSB                            0x56
#define C6DOFIMU3_M_THS_Y_LSB                            0x57
#define C6DOFIMU3_M_THS_Z_MSB                            0x58
#define C6DOFIMU3_M_THS_Z_LSB                            0x59
#define C6DOFIMU3_M_THS_COUNT                            0x5A
#define C6DOFIMU3_M_CTRL_REG1                            0x5B
#define C6DOFIMU3_M_CTRL_REG2                            0x5C
#define C6DOFIMU3_M_CTRL_REG3                            0x5D
#define C6DOFIMU3_M_INT_SRC                              0x5E
#define C6DOFIMU3_A_VECM_CFG                             0x5F
#define C6DOFIMU3_A_VECM_THS_MSB                         0x60
#define C6DOFIMU3_A_VECM_THS_LSB                         0x61
#define C6DOFIMU3_A_VECM_CNT                             0x62
#define C6DOFIMU3_A_VECM_INITX_MSB                       0x63
#define C6DOFIMU3_A_VECM_INITX_LSB                       0x64
#define C6DOFIMU3_A_VECM_INITY_MSB                       0x65
#define C6DOFIMU3_A_VECM_INITY_LSB                       0x66
#define C6DOFIMU3_A_VECM_INITZ_MSB                       0x67
#define C6DOFIMU3_A_VECM_INITZ_LSB                       0x68
#define C6DOFIMU3_M_VECM_CFG                             0x69
#define C6DOFIMU3_M_VECM_THS_MSB                         0x6A
#define C6DOFIMU3_M_VECM_THS_LSB                         0x6B
#define C6DOFIMU3_M_VECM_CNT                             0x6C
#define C6DOFIMU3_M_VECM_INITX_MSB                       0x6D
#define C6DOFIMU3_M_VECM_INITX_LSB                       0x6E
#define C6DOFIMU3_M_VECM_INITY_MSB                       0x6F
#define C6DOFIMU3_M_VECM_INITY_LSB                       0x70
#define C6DOFIMU3_M_VECM_INITZ_MSB                       0x71
#define C6DOFIMU3_M_VECM_INITZ_LSB                       0x72
#define C6DOFIMU3_A_FFMT_THS_X_MSB                       0x73
#define C6DOFIMU3_A_FFMT_THS_X_LSB                       0x74
#define C6DOFIMU3_A_FFMT_THS_Y_MSB                       0x75
#define C6DOFIMU3_A_FFMT_THS_Y_LSB                       0x76
#define C6DOFIMU3_A_FFMT_THS_Z_MSB                       0x77
#define C6DOFIMU3_A_FFMT_THS_Z_LSB                       0x78
/** \} */

/**
 * \defgroup accel_resolution  Accel resolution values (mg/LSB)
 * \{
 */
#define C6DOFIMU3_ACCEL_RES_2G                           0.244
#define C6DOFIMU3_ACCEL_RES_4G                           0.488
#define C6DOFIMU3_ACCEL_RES_8G                           0.976
/** \} */

/**
 * \defgroup magnetometer_resolution  Magnetometer resolution values (uT/LSB)
 * \{
 */
#define C6DOFIMU3_MAGNETOMETER_RES                       0.1
/** \} */

/**
 * \defgroup dev_id_val  Device ID value
 * \{
 */
#define C6DOFIMU3_DEVICE_ID_VAL                          0xC7
/** \} */

/**
 * \defgroup check_err  Check error
 * \{
 */
#define C6DOFIMU3_ERROR                                  0x00
#define C6DOFIMU3_SUCCESS                                0x01
/** \} */

/**
 * \defgroup spi SPI
 * \{
 */
#define C6DOFIMU3_BIT_MASK_SPI_CMD_WRITE                 0x80
#define C6DOFIMU3_BIT_MASK_SPI_CMD_READ                  0x7F
#define C6DOFIMU3_BIT_MASK_BIT_7                         0x80
/** \} */

/**
 * \defgroup data_rdy  Data ready
 * \{
 */
#define C6DOFIMU3_DR_STATUS_XYZ_DATA_ERROR               0x00
/** \} */

/**
 * \defgroup rst_pin_state  RST pin state
 * \{
 */
#define C6DOFIMU3_RST_PIN_STATE_LOW                      0x00
#define C6DOFIMU3_RST_PIN_STATE_HIGH                     0x01
/** \} */

/**
 * \defgroup dummy Dummy
 * \{
 */
#define C6DOFIMU3_SPI_COMMUNICATION_DUMMY                0x00
/** \} */

/**
 * \defgroup communication Communication
 * \{
 */
#define SPI_COMMUNICATION                                1
#define I2C_COMMUNICATION                                2
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
typedef struct
{
    float x;
    float y;
    float z;
}
c6dofimu3_accel_t;

typedef struct
{
    float x;
    float y;
    float z;
}
c6dofimu3_mag_t;

/**
 * @brief Communication type.
 */
typedef uint8_t  c6dofimu3_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c6dofimu3_master_io_t )( struct c6dofimu3_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu3_s
{
    // Output pins 

    digital_out_t cs;
    digital_out_t rst;
   
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;

    c6dofimu3_master_io_t  write_f;
    c6dofimu3_master_io_t  read_f;
    c6dofimu3_select_t master_sel;

   uint8_t communication_interface;

} c6dofimu3_t;

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

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;
    
    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    c6dofimu3_select_t sel;

} c6dofimu3_cfg_t;

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
void c6dofimu3_cfg_setup ( c6dofimu3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU3_RETVAL c6dofimu3_init ( c6dofimu3_t *ctx, c6dofimu3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 6 Dof imu 3 click.
 */
void c6dofimu3_default_cfg ( c6dofimu3_t *ctx );

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
void c6dofimu3_generic_write ( c6dofimu3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Data buf to be written.
 * @param len        Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void c6dofimu3_generic_read ( c6dofimu3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set RST pin state function
 *
 * @param ctx        Click object.
 * @param rst_state
 * - 0 : RST pin state low.
 * - 1 : RST pin state high.
 *
 * @description Function set state of RST pin on 6DOF IMU 3 Click board.
 */
void c6dofimu3_set_rst ( c6dofimu3_t *ctx, uint8_t rst_state );

/**
 * @brief Multi data write function
 *
 * @param ctx              Click object.
 * @param reg              8-bit register address
 * @param p_tx_data        pointer to the data to be written
 * @param n_bytes          number of bytes to be written
 *
 * @description Function writes a sequential data starting
 * from the targeted 8-bit register address of
 * of FXOS8700CQ 6-axis sensor with integrated linear
 * accelerometer and magnetometer on 6DOF IMU 3 Click board.
 */
void c6dofimu3_multi_write ( c6dofimu3_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief Multi data read function
 *
 * @param ctx               Click object.
 * @param reg               8-bit register address
 * @param p_tx_data         pointer to the memory location where data be stored
 * @param n_bytes           number of bytes to be written
 *
 * @description Function read a sequential data starting
 * from the targeted 8-bit register address of
 * of FXOS8700CQ 6-axis sensor with integrated linear
 * accelerometer and magnetometer on 6DOF IMU 3 Click board.
 */
void c6dofimu3_multi_read ( c6dofimu3_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

/**
 * @brief Check ID function
 *
 * @param ctx        Click object.
 * 
 * @returns ID status: 0 - Check ID Error; 1 - Check ID Success;
 *
 * @description Function check device ID by read ID value from the sensor ID register address
 * of FXOS8700CQ 6-axis sensor with integrated linear
 * accelerometer and magnetometer on 6DOF IMU 3 Click board.
 */
C6DOFIMU3_RETVAL_T c6dofimu3_check_id ( c6dofimu3_t *ctx );

/**
 * @brief Check data ready function
 *
 * @param ctx        Click object.
 * 
 * @returns Init status: 0 - Check ID Error; 1 - Check ID Success;
 *
 * @description Function check status if new data ready
 * of FXOS8700CQ 6-axis sensor with integrated linear
 * accelerometer and magnetometer on 6DOF IMU 3 Click board.
 */
C6DOFIMU3_RETVAL_T c6dofimu3_check_data_ready ( c6dofimu3_t *ctx);

/**
 * @brief Set standby mode function
 *
 * @param ctx        Click object.
 * 
 * @description Function set standby mode ( configuration mode )
 * of FXOS8700CQ 6-axis sensor with integrated linear
 * accelerometer and magnetometer on 6DOF IMU 3 Click board.
 */
void c6dofimu3_standby ( c6dofimu3_t *ctx );

/**
 * @brief Set active mode function
 *
 * @param ctx        Click object.
 * @description Function set active mode ( read mode )
 * of FXOS8700CQ 6-axis sensor with integrated linear
 * accelerometer and magnetometer on 6DOF IMU 3 Click board.
 */
void c6dofimu3_active ( c6dofimu3_t *ctx );

/**
 * @brief Read Accel data function
 * 
 * @param ctx        Click object.
 * @param accel_data pointer to memory location where Accel data be stored
 *
 * @description Function read 14-bit ( signed ) Accel
 *  X-axis, Y-axis data and Z-axis data from the 6
 * targeted starts from C6DOFIMU3_OUT_X_MSB register address
 * of FXOS8700CQ 6-axis sensor with integrated linear
 * accelerometer and magnetometer on 6DOF IMU 3 Click board.
 */
void c6dofimu3_read_accel_data ( c6dofimu3_t *ctx, c6dofimu3_accel_t *accel_data );

/**
 * @brief Read Magnetometer data function
 *
 * @param ctx        Click object.
 * @param mag_data   pointer to memory location where Magnetometer data be stored
 *
 * @description Function read 16-bit ( signed ) Magnetometer
 *  X-axis, Y-axis data and Z-axis data from the 6
 * targeted starts from C6DOFIMU3_M_OUT_X_MSB register address
 * of FXOS8700CQ 6-axis sensor with integrated linear
 * accelerometer and magnetometer on 6DOF IMU 3 Click board.
 */
void c6dofimu3_read_mag_data ( c6dofimu3_t *ctx, c6dofimu3_mag_t *mag_data );

/**
 * @brief Read Accel and Magnetometer data function
 *
 * @param ctx        Click object.
 * @param accel_data pointer to memory location where Accel data be stored
 * @param gyro_data pointer to memory location where Magnetometer data be stored
 *
 * @description Function read Accel and Magnetometer
 *  X-axis, Y-axis data and Z-axis data from
 * of FXOS8700CQ 6-axis sensor with integrated linear
 * accelerometer and magnetometer on 6DOF IMU 3 Click board.
 */
void c6dofimu3_get_data ( c6dofimu3_t *ctx, c6dofimu3_accel_t *accel_data, c6dofimu3_mag_t *mag_data );

/**
 * @brief Get interrupt ststus function
 *
 * @param ctx        Click object.
 * 
 * @return Interrupt state
 * <pre>
 * Interrupt posible state:
 * - 0 : No active;
 * - 1 : Active;
 * </pre>
 * @description Function check interrupt state by return state
 * of the INT pin of 6DOF IMU 3 Click board.
*/
uint8_t c6dofimu3_check_int1 ( c6dofimu3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
