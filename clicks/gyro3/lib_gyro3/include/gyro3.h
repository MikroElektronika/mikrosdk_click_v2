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
 * \brief This file contains API for Gyro 3 Click driver.
 *
 * \addtogroup gyro3 Gyro 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GYRO3_H
#define GYRO3_H

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

#define GYRO3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.di2   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define GYRO3_MASTER_I2C 0
#define GYRO3_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GYRO3_RETVAL  uint8_t

#define GYRO3_OK           0x00
#define GYRO3_INIT_ERROR   0xFF
/** \} */

 /**
 * \defgroup slave_address Slave Address 
 * \{
 */
#define GYRO3_DEVICE_ADDR_SA0                         0x68
#define GYRO3_DEVICE_ADDR_SA1                         0x69
/** \} */

 /**
 * \defgroup mode Mode
 * \{
 */
#define GYRO3_MODE_POWER_DOWN                         0x00
#define GYRO3_MODE_SLEEP                              0x08
#define GYRO3_MODE_NORMAL                             0x0F
/** \} */

 /**
 * \defgroup control_registers Control Registers
 * \{
 */
#define GYRO3_CTRL_REG1                               0x20
#define GYRO3_CTRL_REG2                               0x21
#define GYRO3_CTRL_REG3                               0x22
#define GYRO3_CTRL_REG4                               0x23
#define GYRO3_CTRL_REG5                               0x24
/** \} */

 /**
 * \defgroup odr ODR
 * \{
 */
#define GYRO3_ODR_100_CUTOFF_12p5                     0x00
#define GYRO3_ODR_100_CUTOFF_25                       0x10
#define GYRO3_ODR_200_CUTOFF_12p5                     0x40
#define GYRO3_ODR_200_CUTOFF_25                       0x50
#define GYRO3_ODR_200_CUTOFF_50                       0x60
#define GYRO3_ODR_200_CUTOFF_70                       0x70
#define GYRO3_ODR_400_CUTOFF_20                       0x80
#define GYRO3_ODR_400_CUTOFF_25                       0x90
#define GYRO3_ODR_400_CUTOFF_50                       0xa0
#define GYRO3_ODR_400_CUTOFF_110                      0xb0
#define GYRO3_ODR_800_CUTOFF_30                       0xc0
#define GYRO3_ODR_800_CUTOFF_35                       0xd0
#define GYRO3_ODR_800_CUTOFF_50                       0xe0
#define GYRO3_ODR_800_CUTOFF_110                      0xf0
/** \} */

/**
 * \defgroup fifo FIFO 
 * \{
 */
#define GYRO3_FIFO_MODE_BYPASS                        0x00
#define GYRO3_FIFO_EMPTY_INT_ON_INT2                  0x01
#define GYRO3_FIFO_OVERRUN_INT_ON_INT2                0x02
#define GYRO3_FIFO_WATERMARK_INT_ON_INT2              0x04
#define GYRO3_FIFO_MODE_FIFO                          0x20
#define GYRO3_FIFO_MODE_STREAM                        0x40
#define GYRO3_FIFO_WTM_STATUS_MASK                    0x80
#define GYRO3_FIFO_OVERRUN_MASK                       0x40
#define GYRO3_FIFO_EMPTY_STATUS                       0x20
/** \} */

/**
 * \defgroup other_macros Other Macros 
 * \{
 */
#define GYRO3_WHO_AM_I                                0x0f
#define GYRO3_REF_DATACAP                             0x25
#define GYRO3_OUT_TEMP                                0x26
#define GYRO3_STATUS_REG                              0x27
#define GYRO3_OUT_X_L                                 0x28
#define GYRO3_OUT_X_H                                 0x29
#define GYRO3_OUT_Y_L                                 0x2a
#define GYRO3_OUT_Y_H                                 0x2b
#define GYRO3_OUT_Z_L                                 0x2c
#define GYRO3_OUT_Z_H                                 0x2d
#define GYRO3_FIFO_CTRL                               0x2e
#define GYRO3_FIFO_SRC                                0x2f
#define GYRO3_INT1_CFG                                0x30
#define GYRO3_INT1_SRC                                0x31
#define GYRO3_INT1_THS_XH                             0x32
#define GYRO3_INT1_THS_XL                             0x33
#define GYRO3_INT1_THS_YH                             0x34
#define GYRO3_INT1_THS_YL                             0x35
#define GYRO3_INT1_THS_ZH                             0x36
#define GYRO3_INT1_THS_ZL                             0x37
#define GYRO3_INT1_DURATION                           0x38
#define GYRO3_HPF_MODE_NORMAL                         0x00
#define GYRO3_HPF_MODE_REF_SIGNAL                     0x10
#define GYRO3_HPF_MODE_AUTO_RESET_ON_INT              0x30
#define GYRO3_HPF_CUTOFF_FREQ_8                       0x00
#define GYRO3_HPF_CUTOFF_FREQ_4                       0x01
#define GYRO3_HPF_CUTOFF_FREQ_2                       0x02
#define GYRO3_HPF_CUTOFF_FREQ_1                       0x03
#define GYRO3_HPF_CUTOFF_FREQ_0p5                     0x04
#define GYRO3_HPF_CUTOFF_FREQ_0p2                     0x05
#define GYRO3_HPF_CUTOFF_FREQ_0p1                     0x06
#define GYRO3_HPF_CUTOFF_FREQ_0p05                    0x07
#define GYRO3_HPF_CUTOFF_FREQ_0p02                    0x08
#define GYRO3_HPF_CUTOFF_FREQ_0p01                    0x09
#define GYRO3_INT_ON_INT1                             0x80
#define GYRO3_BOOT_STATUS_ON_INT1                     0x40
#define GYRO3_INT_ACTIVE_CFG_ON_INT1                  0x20
#define GYRO3_PUSH_PULL                               0x00
#define GYRO3_OPEN_DRAIN                              0x10
#define GYRO3_DRDY_ON_INT2                            0x08
#define GYRO3_BIG_ENDIAN                              0x40
#define GYRO3_LITTLE_ENDIAN                           0x00
#define GYRO3_FULL_SCACLE_245                         0x00
#define GYRO3_FULL_SCACLE_500                         0x10
#define GYRO3_FULL_SCACLE_1000                        0x20
#define GYRO3_FULL_SCACLE_2000                        0x30
#define GYRO3_SELF_TEST_NORMAL                        0x00
#define GYRO3_SELF_TEST_0                             0x02
#define GYRO3_SELF_TEST_1                             0x06
#define GYRO3_SPI_MODE_4_WIRE                         0x00
#define GYRO3_SPI_MODE_3_WIRE                         0x01
#define GYRO3_REBOOT_MEMORY                           0x80
#define GYRO3_FIFO_EN                                 0x40
#define GYRO3_HPF_EN                                  0x10
#define GYRO3_INT_SEL_00                              0x00
#define GYRO3_INT_SEL_01                              0x40
#define GYRO3_INT_SEL_10                              0x80
#define GYRO3_OUT_SEL_00                              0x00
#define GYRO3_OUT_SEL_01                              0x01
#define GYRO3_OUT_SEL_10                              0x02
#define GYRO3_ZYX_OVERRUN_MASK                        0x80
#define GYRO3_Z_MASK                                  0x40
#define GYRO3_Y_MASK                                  0x20
#define GYRO3_X_MASK                                  0x10
#define GYRO3_ZYX_NEW_DATA_MASK                       0x08
#define GYRO3_Z_NEW_DATA_MASK                         0x04
#define GYRO3_Y_NEW_DATA_MASK                         0x02
#define GYRO3_X_NEW_DATA_MASK                         0x01
#define GYRO3_INT1_AND_OR                             0x80
#define GYRO3_INT1_LATCH                              0x40
#define GYRO3_INT1_ON_HIGH_Z                          0x20
#define GYRO3_INT1_ON_LOW_Z                           0x10
#define GYRO3_INT1_ON_HIGH_Y                          0x08
#define GYRO3_INT1_ON_LOW_Y                           0x04
#define GYRO3_INT1_ON_HIGH_X                          0x02
#define GYRO3_INT1_ON_LOW_X                           0x01
#define GYRO3_INT1_INT_ACTIVE_MASK                    0x40
#define GYRO3_INT1_Z_HIGH_INT_MASK                    0x20
#define GYRO3_INT1_Z_LOW_INT_MASK                     0x10
#define GYRO3_INT1_Y_HIGH_INT_MASK                    0x08
#define GYRO3_INT1_Y_LOW_INT_MASK                     0x04
#define GYRO3_INT1_X_HIGH_INT_MASK                    0x02
#define GYRO3_INT1_X_LOW_INT_MASK                     0x01
#define GYRO3_WAIT_ENABLE                             0x80
#define GYRO3_WAIT_DISABLE                            0x00
#define GYRO3_MEAS_RANGE_245                          0x01
#define GYRO3_MEAS_RANGE_500                          0x02
#define GYRO3_MEAS_RANGE_2000                         0x03
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
typedef uint8_t  gyro3_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *gyro3_master_io_t )( struct gyro3_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct gyro3_s
{
    // Output pins

    digital_out_t cs;

    // Input pins 

    digital_in_t di2;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    gyro3_master_io_t  write_f;
    gyro3_master_io_t  read_f;
    gyro3_select_t master_sel;
} gyro3_t;

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

    pin_name_t di2;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    gyro3_select_t sel;

} gyro3_cfg_t;

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
void gyro3_cfg_setup ( gyro3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
GYRO3_RETVAL gyro3_init ( gyro3_t *ctx, gyro3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Gyro 3 Click.
 */
void gyro3_default_cfg ( gyro3_t *ctx );

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
void gyro3_generic_write ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void gyro3_generic_read ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get INT pin state
 *
 * @param ctx    Click object.
 *
 * @returns 0 for LOW and 1 for HIGH INT pin state.
 *
 * @description This function gets INT pin state.
 */
uint8_t gyro3_int_get ( gyro3_t *ctx );

/**
 * @brief Get di2 (AN) pin state
 *
 * @param ctx    Click object.
 *
 * @returns      0 for LOW and 1 for HIGH pin di2 state.
 *
 * @description This function gets AN i.e di2 pin state.
 */
uint8_t gyro3_di2_get( gyro3_t *ctx );

/**
 * @brief Reading register(s)
 *
 * @param ctx    Click object.
 * @param register_address - Address of the first register to be read.
 * @param read_buffer - Buffer for storing read register values.
 * @param n_bytes - Number of bytes to read.
 *
 * @description This function reads specified number of registers starting from 
 * specified address and stores their values to output buffer.
 */
void gyro3_read ( gyro3_t *ctx, uint8_t register_address, uint8_t * read_buffer, uint8_t n_bytes );

/**
 * @brief Write byte to regiter
 *
 * @param ctx    Click object.
 * @param register_address - Address of the register to write to.
 * @param register_value - Value to write to specified register.
 *
 * @description This function writes specified value to specified register.
 */
void gyro3_write ( gyro3_t *ctx, uint8_t register_address, uint8_t value );

/**
 * @brief Read value from temperature register
 *
 * @param ctx    Click object.
 * @param temperature_value - Value stored to temperature register (26h).
 *
 * @description This function reads value stored in temperature register (26h).
 */
void gyro3_get_temp ( gyro3_t *ctx, uint8_t *temperature_value );

/**
 * @brief Get XYZ axes dps values
 *
 * @param ctx    Click object.
 * @param x_axis - Value stored in x axis register multiplied by sensitivity.
 * @param y_axis - Value stored in y axis register multiplied by sensitivity.
 * @param z_axis - Value stored in z axis register multiplied by sensitivity.
 * @param measurement_range - Measurement range set by user (by default measurement range is 2000 dps).
 *
 * @description This function reads values from XYZ axes registers and converts them to degrees per
 * second value based on measurement range setting.
 */
void gyro3_get_axes ( gyro3_t *ctx, float *x_axis, float *y_axis, float *z_axis, uint8_t measurement_range );

/**
 * @brief Getting status register content
 *
 * @param ctx    Click object.
 * @param status_register - Status register value.
 *
 * @description This function gets value of status register (27h)
 */
void gyro3_get_status ( gyro3_t *ctx, uint8_t * status_register );

/**
 * @brief Get FIFO data level
 *
 * @param ctx    Click object.
 * @param fifo_data_level - Data level in FIFO register.
 *
 * @description This function reads data level value in FIFO register from FIFO SRC register (2Fh)
 * and stores result in fifo_data_level
 */
void gyro3_get_fifo_data_level ( gyro3_t *ctx, uint8_t * fifo_data_level );

/**
 * @brief Setting values for interrupt thresholds
 *
 * @param ctx    Click object.
 * @param x_threshold - X-Axis threshold value.
 * @param y_threshold - Y-Axis threshold value.
 * @param z_threshold - Z-Axis threshold value.
 *
 * @description This function sets threshold values for interrupt generation on XYZ-Axes
 */
void gyro3_set_int1_thresholds ( gyro3_t *ctx, int16_t x_threshold, int16_t y_threshold, int16_t z_threshold );

/**
 * @brief Setting interrupt duration time on INT1 pin
 *
 * @param ctx    Click object.
 * @param wait_enable_bit - WAKE bit value
 * @param duration_value - Duration steps and maximum values depend on the ODR chosen
 *
 * @returns 0-success, 1-error
 *
 * @description This function sets the minimum duration of the interrupt event to be recognized.
 */
uint8_t gyro3_set_int1_duration ( gyro3_t *ctx, uint8_t wait_enable_bit, uint8_t duration_value );


#ifdef __cplusplus
}
#endif
#endif  // _GYRO3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
