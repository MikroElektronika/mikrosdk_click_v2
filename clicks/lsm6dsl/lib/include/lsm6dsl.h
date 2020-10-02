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
 * \brief This file contains API for LSM6DSL Click driver.
 *
 * \addtogroup lsm6dsl LSM6DSL Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LSM6DSL_H
#define LSM6DSL_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
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

#define LSM6DSL_MAP_MIKROBUS( cfg, mikrobus ) \
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
#define LSM6DSL_RETVAL  uint8_t

#define LSM6DSL_OK           0x00
#define LSM6DSL_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_register Device Register
 * \{
 */
#define LSM6DSL_FUNC_CFG_ACCESS                                    0x01
#define LSM6DSL_SENSOR_SYNC_TIME                                   0x04
#define LSM6DSL_SENSOR_RES_RATIO                                   0x05
#define LSM6DSL_FIFO_CTRL1                                         0x06
#define LSM6DSL_FIFO_CTRL2                                         0x07
#define LSM6DSL_FIFO_CTRL3                                         0x08
#define LSM6DSL_FIFO_CTRL4                                         0x09
#define LSM6DSL_FIFO_CTRL5                                         0x0A
#define LSM6DSL_DRDY_PULSE_CFG_G                                   0x0B
#define LSM6DSL_INT1_CTRL                                          0x0D
#define LSM6DSL_INT2_CTRL                                          0x0E
#define LSM6DSL_WHO_AM_I_REG                                       0x0F
#define LSM6DSL_CTRL1_XL                                           0x10
#define LSM6DSL_CTRL2_G                                            0x11
#define LSM6DSL_CTRL3_C                                            0x12
#define LSM6DSL_CTRL4_C                                            0x13
#define LSM6DSL_CTRL5_C                                            0x14
#define LSM6DSL_CTRL6_G                                            0x15
#define LSM6DSL_CTRL7_G                                            0x16
#define LSM6DSL_CTRL8_XL                                           0x17
#define LSM6DSL_CTRL9_XL                                           0x18
#define LSM6DSL_CTRL10_C                                           0x19
#define LSM6DSL_MASTER_CONFIG                                      0x1A
#define LSM6DSL_WAKE_UP_SRC                                        0x1B
#define LSM6DSL_TAP_SRC                                            0x1C
#define LSM6DSL_D6D_SRC                                            0x1D
#define LSM6DSL_STATUS_REG                                         0x1E
#define LSM6DSL_OUT_TEMP_L                                         0x20
#define LSM6DSL_OUT_TEMP_H                                         0x21
#define LSM6DSL_OUTX_L_G                                           0x22
#define LSM6DSL_OUTX_H_G                                           0x23
#define LSM6DSL_OUTY_L_G                                           0x24
#define LSM6DSL_OUTY_H_G                                           0x25
#define LSM6DSL_OUTZ_L_G                                           0x26
#define LSM6DSL_OUTZ_H_G                                           0x27
#define LSM6DSL_OUTX_L_XL                                          0x28
#define LSM6DSL_OUTX_H_XL                                          0x29
#define LSM6DSL_OUTY_L_XL                                          0x2A
#define LSM6DSL_OUTY_H_XL                                          0x2B
#define LSM6DSL_OUTZ_L_XL                                          0x2C
#define LSM6DSL_OUTZ_H_XL                                          0x2D
#define LSM6DSL_SENSORHUB1_REG                                     0x2E
#define LSM6DSL_SENSORHUB2_REG                                     0x2F
#define LSM6DSL_SENSORHUB3_REG                                     0x30
#define LSM6DSL_SENSORHUB4_REG                                     0x31
#define LSM6DSL_SENSORHUB5_REG                                     0x32
#define LSM6DSL_SENSORHUB6_REG                                     0x33
#define LSM6DSL_SENSORHUB7_REG                                     0x34
#define LSM6DSL_SENSORHUB8_REG                                     0x35
#define LSM6DSL_SENSORHUB9_REG                                     0x36
#define LSM6DSL_SENSORHUB10_REG                                    0x37
#define LSM6DSL_SENSORHUB11_REG                                    0x38
#define LSM6DSL_SENSORHUB12_REG                                    0x39
#define LSM6DSL_FIFO_STATUS1                                       0x3A
#define LSM6DSL_FIFO_STATUS2                                       0x3B
#define LSM6DSL_FIFO_STATUS3                                       0x3C
#define LSM6DSL_FIFO_STATUS4                                       0x3D
#define LSM6DSL_FIFO_DATA_OUT_L                                    0x3E
#define LSM6DSL_FIFO_DATA_OUT_H                                    0x3F
#define LSM6DSL_TIMESTAMP0_REG                                     0x40
#define LSM6DSL_TIMESTAMP1_REG                                     0x41
#define LSM6DSL_TIMESTAMP2_REG                                     0x42
#define LSM6DSL_TIMESTAMP_L                                        0x49
#define LSM6DSL_TIMESTAMP_H                                        0x4A
#define LSM6DSL_STEP_COUNTER_L                                     0x4B
#define LSM6DSL_STEP_COUNTER_H                                     0x4C
#define LSM6DSL_SENSORHUB13_REG                                    0x4D
#define LSM6DSL_SENSORHUB14_REG                                    0x4E
#define LSM6DSL_SENSORHUB15_REG                                    0x4F
#define LSM6DSL_SENSORHUB16_REG                                    0x50
#define LSM6DSL_SENSORHUB17_REG                                    0x51
#define LSM6DSL_SENSORHUB18_REG                                    0x52
#define LSM6DSL_FUNC_SRC                                           0x53
#define LSM6DSL_TAP_CFG1                                           0x58
#define LSM6DSL_TAP_THS_6D                                         0x59
#define LSM6DSL_INT_DUR2                                           0x5A
#define LSM6DSL_WAKE_UP_THS                                        0x5B
#define LSM6DSL_WAKE_UP_DUR                                        0x5C
#define LSM6DSL_FREE_FALL                                          0x5D
#define LSM6DSL_MD1_CFG                                            0x5E
#define LSM6DSL_MD2_CFG                                            0x5F
#define LSM6DSL_OUT_MAG_RAW_X_L                                    0x66
#define LSM6DSL_OUT_MAG_RAW_X_H                                    0x67
#define LSM6DSL_OUT_MAG_RAW_Y_L                                    0x68
#define LSM6DSL_OUT_MAG_RAW_Y_H                                    0x69
#define LSM6DSL_OUT_MAG_RAW_Z_L                                    0x6A
#define LSM6DSL_OUT_MAG_RAW_Z_H                                    0x6B
#define LSM6DSL_X_OFS_USR                                          0x73
#define LSM6DSL_Y_OFS_USR                                          0x74
#define LSM6DSL_Z_OFS_USR                                          0x75
/** \} */

/**
 * \defgroup embedded_functions_register_mapping Embedded functions register mapping
 * \{
 */
#define LSM6DSL_SLV0_ADD                                           0x02
#define LSM6DSL_SLV0_SUBADD                                        0x03
#define LSM6DSL_SLAVE0_CONFIG                                      0x04
#define LSM6DSL_SLV1_ADD                                           0x05
#define LSM6DSL_SLV1_SUBADD                                        0x06
#define LSM6DSL_SLAVE1_CONFIG                                      0x07
#define LSM6DSL_SLV2_ADD                                           0x08
#define LSM6DSL_SLV2_SUBADD                                        0x09
#define LSM6DSL_SLAVE2_CONFIG                                      0x0A
#define LSM6DSL_SLV3_ADD                                           0x0B
#define LSM6DSL_SLV3_SUBADD                                        0x0C
#define LSM6DSL_SLAVE3_CONFIG                                      0x0D
#define LSM6DSL_DATAWRITE_SRC_MODE_SUB_SLV0                        0x0E
#define LSM6DSL_CONFIG_PEDO_THS_MIN                                0x0F
#define LSM6DSL_SM_STEP_THS                                        0x13
#define LSM6DSL_PEDO_DEB_REG                                       0x14
#define LSM6DSL_STEP_COUNT_DELTA                                   0x15
#define LSM6DSL_MAG_SI_XX                                          0x24
#define LSM6DSL_MAG_SI_XY                                          0x25
#define LSM6DSL_MAG_SI_XZ                                          0x26
#define LSM6DSL_MAG_SI_YX                                          0x27
#define LSM6DSL_MAG_SI_YY                                          0x28
#define LSM6DSL_MAG_SI_YZ                                          0x29
#define LSM6DSL_MAG_SI_ZX                                          0x2A
#define LSM6DSL_MAG_SI_ZY                                          0x2B
#define LSM6DSL_MAG_SI_ZZ                                          0x2C
#define LSM6DSL_MAG_OFFX_L                                         0x2D
#define LSM6DSL_MAG_OFFX_H                                         0x2E
#define LSM6DSL_MAG_OFFY_L                                         0x2F
#define LSM6DSL_MAG_OFFY_H                                         0x30
#define LSM6DSL_MAG_OFFZ_L                                         0x31
#define LSM6DSL_MAG_OFFZ_H                                         0x32
/** \} */

/**
 * \defgroup check_id Check LSM6DSL Click ID
 * \{
 */
#define LSM6DSL_CHECK_ID                                           0x6A
/** \} */

/**
 * \defgroup output_data_rates LSM6DSL Click Output Data Rates
 * \{
 */
#define LSM6DSL_DISABLE_MEASUREMENT                                0x00
#define LSM6DSL_ODR_6660_HZ                                        0xA0
#define LSM6DSL_ODR_3330_HZ                                        0x90
#define LSM6DSL_ODR_1660_HZ                                        0x80
#define LSM6DSL_ODR_833_HZ                                         0x70
#define LSM6DSL_ODR_416_HZ                                         0x60
#define LSM6DSL_ODR_208_HZ                                         0x50
#define LSM6DSL_ODR_104_HZ                                         0x40
#define LSM6DSL_ODR_52_HZ                                          0x30
#define LSM6DSL_ODR_26_HZ                                          0x20
#define LSM6DSL_ODR_12_5_HZ                                        0x10
#define LSM6DSL_ODR_XL_1_6_HZ                                      0xB0
/** \} */

/**
 * \defgroup full_scale_selections Full Scale Selections
 * \{
 */
#define LSM6DSL_FULLSCALE_XL_2                                     0x00
#define LSM6DSL_FULLSCALE_XL_4                                     0x04
#define LSM6DSL_FULLSCALE_XL_8                                     0x08
#define LSM6DSL_FULLSCALE_XL_16                                    0x0C
#define LSM6DSL_FULLSCALE_G_125                                    0x02
#define LSM6DSL_FULLSCALE_G_245                                    0x00
#define LSM6DSL_FULLSCALE_G_500                                    0x04
#define LSM6DSL_FULLSCALE_G_1000                                   0x08
#define LSM6DSL_FULLSCALE_G_2000                                   0x0C
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Accel object definition.
 */
typedef struct
{
    float accel_x;
    float accel_y;
    float accel_z;

} lsm6dsl_accel_t;

/**
 * @brief Gyro object definition.
 */
typedef struct
{
    float gyro_x;
    float gyro_y;
    float gyro_z;
    
} lsm6dsl_gyro_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} lsm6dsl_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} lsm6dsl_cfg_t;

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
void lsm6dsl_cfg_setup ( lsm6dsl_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param lsm6dsl Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LSM6DSL_RETVAL lsm6dsl_init ( lsm6dsl_t *ctx, lsm6dsl_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for LSM6DSL click.
 */
void lsm6dsl_default_cfg ( lsm6dsl_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void lsm6dsl_generic_transfer 
( 
    lsm6dsl_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Read byte of data function.
 *
 * @param ctx           Click object.
 * @param reg_address   Register address.
 *
 * @description This function read the 8-bit of data from the
 * target 8-bit register address of LSM6DSL sensor.
 */
uint8_t lsm6dsl_read_byte ( lsm6dsl_t *ctx, uint8_t reg_address );

/**
 * @brief Write byte of data function.
 *
 * @param ctx           Click object.
 * @param reg_address   Register address.
 * @param write_data    Byte of data to write.
 *
 * @description This function write the 8-bit of data to the
 * target 8-bit register address of LSM6DSL sensor.
 */
void lsm6dsl_write_byte ( lsm6dsl_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Function check LSM6DSL ID.
 *
 * @param ctx           Click object.
 *
 * @description This function check ID by read WHO_AM_I register
 * of LSM6DSL sensor.
 */
uint8_t lsm6dsl_check_id ( lsm6dsl_t *ctx );

/**
 * @brief Set accel configuration function.
 *
 * @param ctx           Click object.
 * @param odr_sel       Output data rate.
 * @param full_scale    Full-scale.
 *
 * @description This function set accel configuration to the
 * target LSM6DSL_CTRL1_XL register of LSM6DSL sensor.
 */
void lsm6dsl_set_accel_config ( lsm6dsl_t *ctx, uint8_t odr_sel, uint8_t full_scale );

/**
 * @brief Set gyro configuration function.
 *
 * @param ctx           Click object.
 * @param odr_sel       Output data rate.
 * @param full_scale    Full-scale.
 *
 * @description This function set gyro configuration to the
 * target LSM6DSL_CTRL1_XL register of LSM6DSL sensor.
 */
void lsm6dsl_set_gyro_config ( lsm6dsl_t *ctx, uint8_t odr_sel, uint8_t full_scale );

/**
 * @brief Set soft reset function.
 *
 * @param ctx           Click object.
 *
 * @description This function set soft reset by set soft reset bit high to the
 * target LSM6DSL_CTRL3_C register of LSM6DSL sensor.
 */
void lsm6dsl_soft_reset ( lsm6dsl_t *ctx );

/**
 * @brief Set gyroscope sleep mode function.
 *
 * @param ctx           Click object.
 *
 * @description This function set gyroscope sleep mode by set high sleep bit to the
 * target LSM6DSL_CTRL3_C register of LSM6DSL sensor.
 */
void lsm6dsl_sleep_gyro ( lsm6dsl_t *ctx );

/**
 * @brief Set gyroscope wake up mode function.
 *
 * @param ctx           Click object.
 *
 * @description This function set gyroscope wake up mode by set low sleep bit to the
 * target LSM6DSL_CTRL3_C register of LSM6DSL sensor.
 */
void lsm6dsl_wake_up_gyro ( lsm6dsl_t *ctx );

/**
 * @brief Set circular burst mode function.
 *
 * @param ctx           Click object.
 * @param burst_mode    Burst mode.
 *
 * @description This function set circular burst mode of LSM6DSL sensor.
 */
void lsm6dsl_circular_burst_mode ( lsm6dsl_t *ctx, uint8_t burst_mode );

/**
 * @brief Set self-test mode function.
 *
 * @param ctx               Click object.
 * @param gyro_self_test    Gyroscope self-test mode data.
 * @param accel_self_test   Acceleration self-test mode data.
 *
 * @description This function set gyro and accel self-test mode by set data to the
 * LSM6DSL_CTRL5_C register of LSM6DSL sensor.
 */
void lsm6dsl_set_self_test_mode ( lsm6dsl_t *ctx, uint8_t gyro_self_test, uint8_t accel_self_test );

/**
 * @brief Get status function.
 *
 * @param ctx           Click object.
 *
 * @description This function get status from the
 * LSM6DSL_STATUS_REG register of LSM6DSL sensor.
 */
uint8_t lsm6dsl_get_status_reg ( lsm6dsl_t *ctx );

/**
 * @brief Get axis value function.
 *
 * @param ctx                Click object.
 * @param reg_address_low    Register address of low data output.
 *
 * @description This function get axis value from the two
 * target 8-bit register address of LSM6DSL sensor.
 */
uint16_t lsm6dsl_get_axis ( lsm6dsl_t *ctx, uint8_t reg_address_low );

/**
 * @briefGet temperature function.
 *
 * @param ctx           Click object.
 *
 * @description This function read temperature data from the two:
 * - LSM6DSL_OUT_TEMP_L,
 * - LSM6DSL_OUT_TEMP_H,
 * register address of LSM6DSL sensor.
 */
float lsm6dsl_get_temperature ( lsm6dsl_t *ctx );

/**
 * @brief Get acceleration function.
 *
 * @param ctx           Click object.
 * @param accel         Pointer to accel structure ( accel_x, accel_y, accel_z ) .
 * @param full_scale    Full scale value.
 *
 * @description This function get accel x-axis, y-axis and z-axis from the six:
 * - LSM6DSL_OUTX_L_XL,
 * - LSM6DSL_OUTX_H_XL,
 * - LSM6DSL_OUTY_L_XL,
 * - LSM6DSL_OUTY_H_XL,
 * - LSM6DSL_OUTZ_L_XL,
 * - LSM6DSL_OUTZ_H_XL,
 * register address of LSM6DSL sensor.
 */
void lsm6dsl_get_accel ( lsm6dsl_t *ctx, lsm6dsl_accel_t *accel, uint8_t full_scale );

/**
 * @brief Get gyroscope function.
 *
 * @param ctx           Click object.
 * @param gyro          Pointer to gyro structure ( gyro_x, gyro_y, gyro_z ) .
 * @param full_scale    Full scale value.
 *
 * @description This function get gyroscope X-axis, Y-axis and Z-axis from the six:
 * - LSM6DSL_OUTX_L_G,
 * - LSM6DSL_OUTX_H_G,
 * - LSM6DSL_OUTY_L_G,
 * - LSM6DSL_OUTY_H_G,
 * - LSM6DSL_OUTZ_L_G,
 * - LSM6DSL_OUTZ_H_G,
 * register address of LSM6DSL sensor.
 */
void lsm6dsl_get_gyro ( lsm6dsl_t *ctx, lsm6dsl_gyro_t *gyro, uint8_t full_scale );

#ifdef __cplusplus
}
#endif
#endif  // _LSM6DSL_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
