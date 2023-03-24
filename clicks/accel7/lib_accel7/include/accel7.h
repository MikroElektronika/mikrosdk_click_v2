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
 * \brief This file contains API for Accel 7 Click driver.
 *
 * \addtogroup accel7 Accel 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ACCEL7_H
#define ACCEL7_H

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
#define ACCEL7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ACCEL7_RETVAL  uint8_t

#define ACCEL7_OK           0x00
#define ACCEL7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup accel_macros Accel Macros
 * \{
 */
#define ACCEL7_AXIS_X             0x06 
#define ACCEL7_AXIS_Y             0x08 
#define ACCEL7_AXIS_Z             0x0A 
#define ACCEL7_DATA_RESP_8bit     0x10 
#define ACCEL7_DATA_RESP_12bit    0x20 
#define ACCEL7_DATA_RESP_14bit    0x30 
#define ACCEL7_RANGE_2g           0x01 
#define ACCEL7_RANGE_4g           0x02 
#define ACCEL7_RANGE_8g           0x03 
#define ACCEL7_RANGE_16g          0x04       
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define ACCEL7_REG_AXIS_X_LSB             0x06
#define ACCEL7_REG_AXIS_X_MSB             0x07
#define ACCEL7_REG_AXIS_Y_LSB             0x08
#define ACCEL7_REG_AXIS_Y_MSB             0x09
#define ACCEL7_REG_AXIS_Z_LSB             0x0A
#define ACCEL7_REG_AXIS_Z_MSB             0x0B
#define ACCEL7_REG_DCST_RESP              0x0C
#define ACCEL7_REG_WHO_AM_I               0x0F
#define ACCEL7_REG_INT_SOURCE1            0x16
#define ACCEL7_REG_INT_SOURCE2            0x17
#define ACCEL7_REG_STATUS                 0x18
#define ACCEL7_REG_INT_REL                0x1A
#define ACCEL7_REG_CTRL_REG1              0x1B
#define ACCEL7_REG_CTRL_REG2              0x1D
#define ACCEL7_REG_INT_CTRL_REG1          0x1E
#define ACCEL7_REG_INT_CTRL_REG2          0x1F
#define ACCEL7_REG_DATA_CTRL_REG          0x21
#define ACCEL7_REG_WAKEUP_COUNTER         0x29
#define ACCEL7_REG_NA_CAUNTER             0x2A
#define ACCEL7_REG_SELF_TEST              0x3A
#define ACCEL7_REG_WAKEUP_THRESHOLD_MSB   0x6A
#define ACCEL7_REG_WAKEUP_THRESHOLD_LSB   0x6B
/** \} */

/**
 * \defgroup control_register_1 Control Register 1
 * \{
 */
#define ACCEL7_CTRL_REG1_MODE_OPERATING        0x80
#define ACCEL7_CTRL_REG1_MODE_STANDBY          0x00
#define ACCEL7_CTRL_REG1_RES_LOW_CURRENT       0x00
#define ACCEL7_CTRL_REG1_RES_HIGH_RESOLUTION   0x40
#define ACCEL7_CTRL_REG1_DRDYE_ENABLE          0x20
#define ACCEL7_CTRL_REG1_DRDYE_DISABLE         0x00
#define ACCEL7_CTRL_REG1_RANGE_2g              0x00
#define ACCEL7_CTRL_REG1_RANGE_4g              0x08
#define ACCEL7_CTRL_REG1_RANGE_8g              0x10
#define ACCEL7_CTRL_REG1_RANGE_16g             0x04
#define ACCEL7_CTRL_REG1_RANGE_HIGH_RES_8g     0x18
#define ACCEL7_CTRL_REG1_RANGE_HIGH_RES_16g    0x1C
#define ACCEL7_CTRL_REG1_WAKEUP_DISABLE        0x00
#define ACCEL7_CTRL_REG1_WAKEUP_ENABLE         0x02
/** \} */

/**
 * \defgroup control_register_1 Control Register 2
 * \{
 */
#define ACCEL7_CTRL_REG2_START_RAM_REBOOT         0x80
#define ACCEL7_CTRL_REG2_DCST_ENABLE              0x10
#define ACCEL7_CTRL_REG2_DCST_DISABLE             0x00
#define ACCEL7_CTRL_REG2_OUT_DATA_RATE_0_781Hz    0x00
#define ACCEL7_CTRL_REG2_OUT_DATA_RATE_1_563Hz    0x01
#define ACCEL7_CTRL_REG2_OUT_DATA_RATE_3_125Hz    0x02
#define ACCEL7_CTRL_REG2_OUT_DATA_RATE_6_25Hz     0x03
#define ACCEL7_CTRL_REG2_OUT_DATA_RATE_12_5Hz     0x04
#define ACCEL7_CTRL_REG2_OUT_DATA_RATE_25Hz       0x05
#define ACCEL7_CTRL_REG2_OUT_DATA_RATE_50Hz       0x06
#define ACCEL7_CTRL_REG2_OUT_DATA_RATE_100Hz      0x07
/** \} */

/**
 * \defgroup interrupt_control_register_1 Interrupt Control Register 1
 * \{
 */
#define ACCEL7_INT_CTRL_REG1_IEN_DISABLE               0x00 
#define ACCEL7_INT_CTRL_REG1_IEN_ENABLE                0x20 
#define ACCEL7_INT_CTRL_REG1_IEA_DISABLE               0x00 
#define ACCEL7_INT_CTRL_REG1_IEA_ENABLE                0x10 
#define ACCEL7_INT_CTRL_REG1_IEL_DISABLE               0x00 
#define ACCEL7_INT_CTRL_REG1_IEL_ENABLE                0x08 
#define ACCEL7_INT_CTRL_REG1_SELF_TEST_POL_NEGATIVE    0x00
#define ACCEL7_INT_CTRL_REG1_SELF_TEST_POL_POSITIVE    0x02
/** \} */

/**
 * \defgroup interrupt_control_register_2 Interrupt Control Register 2
 * \{
 */
#define ACCEL7_INT_CTRL_REG2_ULMODE_ENABLE         0x80
#define ACCEL7_INT_CTRL_REG2_ULMODE_DISABLE        0x00
#define ACCEL7_INT_CTRL_REG2_X_NEGATIVE_ENABLE     0x20
#define ACCEL7_INT_CTRL_REG2_X_NEGATIVE_DISABLE    0x00
#define ACCEL7_INT_CTRL_REG2_Y_NEGATIVE_ENABLE     0x08
#define ACCEL7_INT_CTRL_REG2_Y_NEGATIVE_DISABLE    0x00
#define ACCEL7_INT_CTRL_REG2_Z_NEGATIVE_ENABLE     0x02
#define ACCEL7_INT_CTRL_REG2_Z_NEGATIVE_DISABLE    0x00
#define ACCEL7_INT_CTRL_REG2_X_POSITIVE_ENABLE     0x10
#define ACCEL7_INT_CTRL_REG2_X_POSITIVE_DISABLE    0x00
#define ACCEL7_INT_CTRL_REG2_Y_POSITIVE_ENABLE     0x04
#define ACCEL7_INT_CTRL_REG2_Y_POSITIVE_DISABLE    0x00
#define ACCEL7_INT_CTRL_REG2_Z_POSITIVE_ENABLE     0x01
#define ACCEL7_INT_CTRL_REG2_Z_POSITIVE_DISABLE    0x00
/** \} */

/**
 * \defgroup data_control_register Data Control Register
 * \{
 */
#define ACCEL7_DATA_CTRL_REG_ODR_0_781Hz     0x08
#define ACCEL7_DATA_CTRL_REG_ODR_1_563Hz     0x09
#define ACCEL7_DATA_CTRL_REG_ODR_3_125Hz     0x0A
#define ACCEL7_DATA_CTRL_REG_ODR_6_25Hz      0x0B
#define ACCEL7_DATA_CTRL_REG_ODR_12_5Hz      0x00
#define ACCEL7_DATA_CTRL_REG_ODR_25Hz        0x01
#define ACCEL7_DATA_CTRL_REG_ODR_50Hz        0x02
#define ACCEL7_DATA_CTRL_REG_ODR_100Hz       0x03
#define ACCEL7_DATA_CTRL_REG_ODR_200Hz       0x04
#define ACCEL7_DATA_CTRL_REG_ODR_400Hz       0x05
#define ACCEL7_DATA_CTRL_REG_ODR_800Hz       0x06
#define ACCEL7_DATA_CTRL_REG_ODR_1600Hz      0x07
/** \} */

/**
 * \defgroup i2c_address Device Slave Address
 * \{
 */
#define ACCEL7_DEVICE_ADDRESS        0x0F
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
    uint8_t data_resolution;

} accel7_t;

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
    uint8_t dev_data_resolution;

} accel7_cfg_t;

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
void accel7_cfg_setup ( accel7_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ACCEL7_RETVAL accel7_init ( accel7_t *ctx, accel7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * @param resolution Resolution variable.
 * @param range Range variable.
 * 
 * @description This function executes default configuration for Accel7 click.
 */
void accel7_default_cfg ( accel7_t *ctx, uint8_t resolution, uint8_t range );

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
void accel7_generic_write ( accel7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void accel7_generic_read ( accel7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write byte function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param input_data   Byte to be written.
 *
 * @description This function writes one byte of data to the desired register.
 */
void accel7_write_byte ( accel7_t *ctx, uint8_t reg, uint8_t input_data );

/**
 * @brief Read byte function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads one byte of data from the desired register.
 */
uint8_t accel7_read_byte( accel7_t *ctx, uint8_t reg );

/**
 * @brief Get axi function.
 *
 * @param ctx          Click object.
 * @param axis         Axis register address.
 *
 * @description This function reads two bytes of data from the desired axis register.
 */
int16_t accel7_get_axis ( accel7_t *ctx, uint8_t axis );

/**
 * @brief Resolution/range configuration function.
 *
 * @param ctx  Click object.
 * @param resolution Resolution pointer.
 * @param range Range pointer.
 * 
 * @description This function calculates the resolution and range values which are used
 *              in the default_cfg() function.
 */
void accel7_res_range_cfg ( accel7_t *ctx, uint8_t *resolution, uint8_t *range );

/**
 * @brief Get interrupt state function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads the state of the interrupt pin.
 */
uint8_t accel7_get_interrupt_state ( accel7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ACCEL7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
