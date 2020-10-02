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
 * \brief This file contains API for Compass 3 Click driver.
 *
 * \addtogroup compass3 Compass 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COMPASS3_H
#define COMPASS3_H

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
#define COMPASS3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COMPASS3_RETVAL  uint8_t

#define COMPASS3_OK           0x00
#define COMPASS3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_adr Device Slave Address
 * \{
 */
#define COMPASS3_SLAVE_ADR           0x30
/** \} */

/**
 * \defgroup reg_map Register map
 * \{
 */
#define COMPASS3_XOUT_LSB            0x00
#define COMPASS3_XOUT_MSB            0x01
#define COMPASS3_YOUT_LSB            0x02
#define COMPASS3_YOUT_MSB            0x03
#define COMPASS3_ZOUT_LSB            0x04
#define COMPASS3_ZOUT_MSB            0x05
#define COMPASS3_TEMP                0x06
#define COMPASS3_STAT                0x07
#define COMPASS3_INTERNAL_CTRL_0     0x08
#define COMPASS3_INTERNAL_CTRL_1     0x09
#define COMPASS3_INTERNAL_CTRL_2     0x0A
#define COMPASS3_X_TRSH              0x0B
#define COMPASS3_Y_TRSH              0x0C
#define COMPASS3_Z_TRSH              0x0D
#define COMPASS3_DEVICE_ID           0x2F
/** \} */

/**
 * \defgroup stat_reg Status register
 * \{
 */
#define COMPASS3_MEAS_M_DONE         0x01
#define COMPASS3_MEAS_T_DONE         0x02
#define COMPASS3_MOTION_DCT          0x04
#define COMPASS3_PUMP_ON             0x08
#define COMPASS3_OTP_RD_DONE         0x10
/** \} */

/**
 * \defgroup inter_ctrl_0 Internal Control 0 register
 * \{
 */
#define COMPASS3_TEST_PIN_SEL        0x80
#define COMPASS3_OTP_RD              0x40
#define COMPASS3_RSRVD               0x20
#define COMPASS3_RESET               0x10
#define COMPASS3_SET                 0x08
#define COMPASS3_START_MD_T          0x04
#define COMPASS3_TM_T                0x02
#define COMPASS3_TM_M                0x01
/** \} */

/**
 * \defgroup inter_ctrl_1 Internal Control 1 register
 * \{
 */
#define COMPASS3_SW_RST              0x80
#define COMPASS3_OTP_BL_SEL1         0x40
#define COMPASS3_OTP_BL_SEL0         0x20
#define COMPASS3_Z_INH               0x10
#define COMPASS3_Y_INH               0x08
#define COMPASS3_X_INH               0x04
#define COMPASS3_BW_ODR_600          0x03
#define COMPASS3_BW_ODR_400          0x02
#define COMPASS3_BW_ODR_200          0x01
#define COMPASS3_BW_ODR_100          0x00
/** \} */

/**
 * \defgroup inter_ctrl_2 Internal Control 2 register
 * \{
 */
#define COMPASS3_ULP_SEL             0x80
#define COMPASS3_INT_MEAS_DONE_EN    0x40
#define COMPASS3_INT_MDT_EN          0x20
#define COMPASS3_Force_VDDL_STBY     0x10
#define COMPASS3_CM_FREQ_0_015625HZ  0x0A
#define COMPASS3_CM_FREQ_0_03125HZ   0x09
#define COMPASS3_CM_FREQ_0_0625HZ    0x08
#define COMPASS3_CM_FREQ_0_125HZ     0x07
#define COMPASS3_CM_FREQ_0_25HZ      0x06
#define COMPASS3_CM_FREQ_0_5HZ       0x05
#define COMPASS3_CM_FREQ_1HZ         0x04
#define COMPASS3_CM_FREQ_2_2HZ       0x03
#define COMPASS3_CM_FREQ_5HZ         0x02
#define COMPASS3_CM_FREQ_14HZ        0x01
#define COMPASS3_CM_FREQ_CONT        0x00
/** \} */

/**
 * \defgroup range_res Range and resolution
 * \{
 */
#define COMPASS3_DYNAMIC_RANGE       16
#define COMPASS3_MAG_LSB_VALUE       0.25
#define COMPASS3_TEMP_LSB_VALUE      0.7
#define COMPASS3_MAG_RANGE_VALUE     8000
#define COMPASS3_TEMP_RANGE_VALUE    75
#define COMPASS3_RESOLUTION          65536
/** \} */

/**
 * \defgroup int_val Interrupt values
 * \{
 */
#define COMPASS3_INTERRUPT           0x01
#define COMPASS3_NO_INTERRUPT        0x00
/** \} */

/**
 * \defgroup dev_id Device ID number
 * \{
 */
#define COMPASS3_DEVICE_ID_NUM       0x0C
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

} compass3_t;

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

} compass3_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group
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
 * @description This function initializes click configuration structure to 
 * init state.
 * @note All used pins will be set to unconnected state.
 */
void compass3_cfg_setup ( compass3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param compass3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals 
 * used for this click.
 */
COMPASS3_RETVAL compass3_init ( compass3_t *ctx, compass3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Compass3 click.
 */
void compass3_default_cfg ( compass3_t *ctx );

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
void compass3_generic_write ( compass3_t *ctx, uint8_t reg, uint8_t *data_buf, 
                              uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void compass3_generic_read ( compass3_t *ctx, uint8_t reg, uint8_t *data_buf, 
                             uint8_t len );

/**
 * @brief Full measurement function
 *
 * @param ctx          Click object.
 * @param x_val  float value of magnetic field across X-axis
 * @param y_val  float value of magnetic field across Y-axis
 * @param z_val  float value of magnetic field across Z-axis
 *
 * @description Measures magnetic field surrounding the device.
**/
void compass3_full_measurement ( compass3_t *ctx, float *x_val, float *y_val, 
                                 float *z_val );

/**
 * @brief Read temperature function
 *
 * @param ctx          Click object.
 * 
 * @returns float  temperature value.
 *
 * @description Function is used to measure temperature.
**/
float compass3_read_temp ( compass3_t *ctx );

/**
 * @brief Check interrupt function
 *
 * @param ctx          Click object.
 * 
 * @returns 1 - Interrupt has occured / 0 - Interrupt has not occured
 *
 * @description Function checks interrupt occurence.
**/
uint8_t compass3_check_int ( compass3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _COMPASS3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
