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
 * \brief This file contains API for Accel 12 Click driver.
 *
 * \addtogroup accel12 Accel 12 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL12_H
#define ACCEL12_H

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
#define ACCEL12_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL12_RETVAL  uint8_t

#define ACCEL12_OK           0x00
#define ACCEL12_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define ACCEL12_REG_GENERAL_STATUS       0x03 
#define ACCEL12_REG_DEVICE_STATUS        0x04 
#define ACCEL12_REG_INTERRUPT_ENABLE     0x06 
#define ACCEL12_REG_MODE_CONTROL         0x07 
#define ACCEL12_REG_SAMPLE_RATE_AND_TAP  0x08 
#define ACCEL12_REG_TAP_CONTROL          0x09 
#define ACCEL12_REG_TAP_X_DURATION       0x0A 
#define ACCEL12_REG_TAP_Y_DURATION       0x0B 
#define ACCEL12_REG_TAP_Z_DURATION       0x0C 
#define ACCEL12_REG_TAP_X_THRESHOLD      0x0A 
#define ACCEL12_REG_TAP_Y_THRESHOLD      0x0B 
#define ACCEL12_REG_TAP_Z_THRESHOLD      0x0C 
#define ACCEL12_REG_X_AXIS_LSB           0x0D 
#define ACCEL12_REG_X_AXIS_MSB           0x0E 
#define ACCEL12_REG_Y_AXIS_LSB           0x0F 
#define ACCEL12_REG_Y_AXIS_MSB           0x10 
#define ACCEL12_REG_Z_AXIS_LSB           0x11 
#define ACCEL12_REG_Z_AXIS_MSB           0x12 
#define ACCEL12_REG_OUTPUT_CONFIG        0x20 
#define ACCEL12_REG_X_OFFSET_LSB         0x21 
#define ACCEL12_REG_X_OFFSET_MSB         0x22 
#define ACCEL12_REG_Y_OFFSET_LSB         0x23 
#define ACCEL12_REG_Y_OFFSET_MSB         0x24 
#define ACCEL12_REG_Z_OFFSET_LSB         0x25 
#define ACCEL12_REG_Z_OFFSET_MSB         0x26 
#define ACCEL12_REG_X_GAIN               0x27 
#define ACCEL12_REG_Y_GAIN               0x28 
#define ACCEL12_REG_Z_GAIN               0x29 
#define ACCEL12_REG_PRODUCT_CODE         0x3B 
/** \} */
 
/**
 * \defgroup general_status  General status
 * \{
 */
#define ACCEL12_GS_TAP_X_POSITIVE  0x01
#define ACCEL12_GS_TAP_X_NEGATIVE  0x02
#define ACCEL12_GS_TAP_Y_POSITIVE  0x04
#define ACCEL12_GS_TAP_Y_NEGATIVE  0x08
#define ACCEL12_GS_TAP_Z_POSITIVE  0x10
#define ACCEL12_GS_TAP_Z_NEGATIVE  0x20
#define ACCEL12_GS_ACQ_INTERRUPT   0x80
/** \} */
 
/**
 * \defgroup device_status  Device status
 * \{
 */
#define ACCEL12_DS_STANDBY_STATE           0x00
#define ACCEL12_DS_WAKE_STATE              0x01
#define ACCEL12_DS_I2C_WDT_NO_EVENT        0x00
#define ACCEL12_DS_I2C_WDT_EVENT_DCT       0x10
#define ACCEL12_DS_INTERNAL_MEMORY_NO_USE  0x00
#define ACCEL12_DS_INTERNAL_MEMORY_USE     0x80
/** \} */
 
/**
 * \defgroup interrup_enable  Interrupt enable
 * \{
 */
#define ACCEL12_EINT_TAP_XP_ENABLE    0x01
#define ACCEL12_EINT_TAP_XP_DISABLE   0x00
#define ACCEL12_EINT_TAP_XN_ENABLE    0x02
#define ACCEL12_EINT_TAP_XN_DISABLE   0x00
#define ACCEL12_EINT_TAP_YP_ENABLE    0x04
#define ACCEL12_EINT_TAP_YP_DISABLE   0x00
#define ACCEL12_EINT_TAP_YN_ENABLE    0x08
#define ACCEL12_EINT_TAP_YN_DISABLE   0x00
#define ACCEL12_EINT_TAP_ZP_ENABLE    0x10
#define ACCEL12_EINT_TAP_ZP_DISABLE   0x00
#define ACCEL12_EINT_TAP_ZN_ENABLE    0x20
#define ACCEL12_EINT_TAP_ZN_DISABLE   0x00
#define ACCEL12_EINT_ACQ_INT_ENABLE   0x80
#define ACCEL12_EINT_ACQ_INT_DISABLE  0x00
/** \} */
 
/**
 * \defgroup mode_control  Mode control
 * \{
 */
#define ACCEL12_MODE_STANDBY_STATE           0x00
#define ACCEL12_MODE_WAKE_STATE              0x01
#define ACCEL12_MODE_I2C_WDT_NEG_DISABLE     0x00
#define ACCEL12_MODE_I2C_WDT_NEG_ENABLE      0x10
#define ACCEL12_MODE_I2C_WDT_POS_DISABLE     0x00
#define ACCEL12_MODE_I2C_WDT_POS_ENABLE      0x20
#define ACCEL12_MODE_IPP_OPEN_DRAIN          0x00
#define ACCEL12_MODE_IPP_PUSH_PULL           0x40
#define ACCEL12_MODE_IAH_ACTIVE_LOW          0x00
#define ACCEL12_MODE_IAH_ACTIVE_HIGH         0x80
/** \} */
 
/**
 * \defgroup sample_rate_and_tap_feature  Sample rate and tap feature
 * \{
 */
#define ACCEL12_SRTFR_RATE_32Hz            0x00
#define ACCEL12_SRTFR_RATE_16Hz            0x01
#define ACCEL12_SRTFR_RATE_8Hz             0x02
#define ACCEL12_SRTFR_RATE_4Hz             0x03
#define ACCEL12_SRTFR_RATE_2Hz             0x04
#define ACCEL12_SRTFR_RATE_1Hz             0x05
#define ACCEL12_SRTFR_RATE_0p5Hz           0x06
#define ACCEL12_SRTFR_RATE_0p25Hz          0x07
#define ACCEL12_SRTFR_RATE_64Hz            0x08
#define ACCEL12_SRTFR_RATE_128Hz           0x09
#define ACCEL12_SRTFR_RATE_256Hz           0x0A
#define ACCEL12_SRTFR_FLIP_TAPX_DISABLE    0x00
#define ACCEL12_SRTFR_FLIP_TAPX_ENABLE     0x10
#define ACCEL12_SRTFR_FLIP_TAPY_DISABLE    0x00
#define ACCEL12_SRTFR_FLIP_TAPY_ENABLE     0x20
#define ACCEL12_SRTFR_FLIP_TAPZ_DISABLE    0x00
#define ACCEL12_SRTFR_FLIP_TAPZ_ENABLE     0x40
#define ACCEL12_SRTFR_TAP_LATCH_ENABLE     0x00
#define ACCEL12_SRTFR_TAP_LATCH_DISABLE    0x80
/** \} */
 
/**
 * \defgroup tap_control  Tap control
 * \{
 */
#define ACCEL12_TAPEN_TAP_X_POS_DISABLE   0x00
#define ACCEL12_TAPEN_TAP_X_POS_ENABLE    0x01
#define ACCEL12_TAPEN_TAP_X_NEG_DISABLE   0x00
#define ACCEL12_TAPEN_TAP_X_NEG_ENABLE    0x02
#define ACCEL12_TAPEN_TAP_Y_POS_DISABLE   0x00
#define ACCEL12_TAPEN_TAP_Y_POS_ENABLE    0x04
#define ACCEL12_TAPEN_TAP_Y_NEG_DISABLE   0x00
#define ACCEL12_TAPEN_TAP_Y_NEG_ENABLE    0x08
#define ACCEL12_TAPEN_TAP_Z_POS_DISABLE   0x00
#define ACCEL12_TAPEN_TAP_Z_POS_ENABLE    0x10
#define ACCEL12_TAPEN_TAP_Z_NEG_DISABLE   0x00
#define ACCEL12_TAPEN_TAP_Z_NEG_ENABLE    0x20
#define ACCEL12_TAPEN_TAP_DURATION        0x00
#define ACCEL12_TAPEN_TAP_THRESHOLD       0x40
#define ACCEL12_TAPEN_ALL_TAP_ENABLE      0x00
#define ACCEL12_TAPEN_ALL_TAP_DISABLE     0x80
/** \} */
 
/**
 * \defgroup output_configuration  Output configuration
 * \{
 */
#define ACCEL12_OUTCFG_RESOLUTION_6_bit    0x00
#define ACCEL12_OUTCFG_RESOLUTION_7_bit    0x01
#define ACCEL12_OUTCFG_RESOLUTION_8_bit    0x02
#define ACCEL12_OUTCFG_RESOLUTION_10_bit   0x03
#define ACCEL12_OUTCFG_RESOLUTION_12_bit   0x04
#define ACCEL12_OUTCFG_RESOLUTION_14_bit   0x05
#define ACCEL12_OUTCFG_RANGE_2g            0x00
#define ACCEL12_OUTCFG_RANGE_4g            0x10
#define ACCEL12_OUTCFG_RANGE_8g            0x20
#define ACCEL12_OUTCFG_RANGE_16g           0x30
#define ACCEL12_OUTCFG_RANGE_12g           0x40
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
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} accel12_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} accel12_cfg_t;

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
void accel12_cfg_setup ( accel12_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ACCEL12_RETVAL accel12_init ( accel12_t *ctx, accel12_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @note
 * <pre>
 *      Accel configuration:
 *         ACCEL12_REG_OUTPUT_CONFIG:
 *           - ACCEL12_OUTCFG_RESOLUTION_14_bit
 *           - ACCEL12_OUTCFG_RANGE_2g
 *         ACCEL12_REG_SAMPLE_RATE_AND_TAP:
 *           - ACCEL12_SRTFR_RATE_256Hz 
 *           - ACCEL12_SRTFR_TAP_LATCH_DISABLE
 *      TAP configuration :
 *         ACCEL12_REG_INTERRUPT_ENABLE:
 *           - ACCEL12_EINT_TAP_XP_ENABLE  
 *           - ACCEL12_EINT_TAP_YP_ENABLE  
 *           - ACCEL12_EINT_TAP_ZP_ENABLE 
 *           - ACCEL12_EINT_TAP_XN_ENABLE  
 *           - ACCEL12_EINT_TAP_YN_ENABLE  
 *           - ACCEL12_EINT_TAP_ZN_ENABLE 
 *           - ACCEL12_EINT_ACQ_INT_ENABLE
 *         ACCEL12_REG_TAP_CONTROL:
 *           - ACCEL12_TAPEN_TAP_X_POS_ENABLE  
 *           - ACCEL12_TAPEN_TAP_Y_POS_ENABLE  
 *           - ACCEL12_TAPEN_TAP_Z_POS_ENABLE 
 *           - ACCEL12_TAPEN_TAP_X_NEG_ENABLE  
 *           - ACCEL12_TAPEN_TAP_Y_NEG_ENABLE  
 *           - ACCEL12_TAPEN_TAP_Z_NEG_ENABLE 
 *           - ACCEL12_TAPEN_TAP_THRESHOLD  
 *           - ACCEL12_TAPEN_ALL_TAP_DISABLE
 *      Go to wake-up mode:
 *         ACCEL12_REG_MODE_CONTROL:
 *           - ACCEL12_MODE_WAKE_STATE  
 *           - ACCEL12_MODE_I2C_WDT_POS_DISABLE 
 *           - ACCEL12_MODE_I2C_WDT_NEG_DISABLE 
 *           - ACCEL12_MODE_IPP_PUSH_PULL 
 *           - ACCEL12_MODE_IAH_ACTIVE_HIGH
 * </pre> 
 *
 * @description This function executes default configuration for Accel12 click.
 */
void accel12_default_cfg ( accel12_t *ctx );

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
void accel12_generic_write ( accel12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void accel12_generic_read ( accel12_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for configuration one register
 * 
 * @param ctx          Click object.
 * @param reg          Register in which the data will be written
 * @param data_in      Data which be written in the register
 *
 * @description This function include going to stand by mode and entering data into the register.
 * Use this function, if you want to set up a register.
 */
void accel12_configuration ( accel12_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Functions for read one Accel axis data
 * 
 * @param ctx          Click object.
 * @param axis         Accel axis data (X, Y or Z)
 *
 * @return Accel axis data
 *
 * @description This function read one Accel axis data
 */
int16_t accel12_get_one_axis ( accel12_t *ctx, uint8_t axis );

/**
 * @brief Functions for read Accel axis data
 * 
 * @param ctx          Click object.
 * @param x_axis       Accel X axis data
 * @param y_axis       Accel Y axis data
 * @param z_axis       Accel Z axis data 
 *
 * @description This function read Accel axis data 
 */
void accel12_get_axis_data ( accel12_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis);

/**
 * @brief TAP detection
 * 
 * @param ctx          Click object.
 * @retval [1]  X axis - Positive
 * @retval [2]  Y axis - Positive
 * @retval [3]  Z axis - Positive
 * @retval [4]  X axis - Negative
 * @retval [5]  Y axis - Negative
 * @retval [6]  Z axis - Negative
 * @return The axis on which the TAP is detected 
 *
 * @description This function is for TAP detection.
 */
uint8_t accel12_get_tap_detection ( accel12_t *ctx );

/**
 * @brief Functions for read INT pin state
 * 
 * @param ctx          Click object.
 * @retval Interrupt state 
 *
 * @description This function read INT pin state.
 */
uint8_t accel12_get_interrupt_state ( accel12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL12_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
