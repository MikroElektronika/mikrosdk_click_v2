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
 * \brief This file contains API for Magneto 7 Click driver.
 *
 * \addtogroup magneto7 Magneto 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MAGNETO7_H
#define MAGNETO7_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define MAGNETO7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MAGNETO7_RETVAL  uint8_t

#define MAGNETO7_OK                     0x00
#define MAGNETO7_INIT_ERROR             0xFF
/** \} */

/**
 * \defgroup device_addresses Device Addresses
 * \{
 */
#define MAGNETO7_DEV_ADDR_L             0x0E
#define MAGNETO7_DEV_ADDR_H             0x0F
/** \} */

/**
 * \defgroup register_addresses Register Addresses
 * \{
 */
#define MAGNETO7_INFO_L                 0x0D
#define MAGNETO7_INFO_H                 0x0E
#define MAGNETO7_WIA                    0x0F
#define MAGNETO7_DATA_X_L               0x10
#define MAGNETO7_DATA_X_H               0x11
#define MAGNETO7_DATA_Y_L               0x12
#define MAGNETO7_DATA_Y_H               0x13
#define MAGNETO7_DATA_Z_L               0x14
#define MAGNETO7_DATA_Z_H               0x15
#define MAGNETO7_STA1                   0x18
#define MAGNETO7_CNTL_1                 0x1B
#define MAGNETO7_CNTL_2                 0x1C
#define MAGNETO7_CNTL_3                 0x1D
#define MAGNETO7_AVE_A                  0x40
#define MAGNETO7_CNTL_4_L               0x5C
#define MAGNETO7_CNTL_4_H               0x5D
#define MAGNETO7_TEMP_L                 0x60
#define MAGNETO7_TEMP_H                 0x61
#define MAGNETO7_OFF_X_L                0x6C
#define MAGNETO7_OFF_X_H                0x6D
#define MAGNETO7_OFF_Y_L                0x72
#define MAGNETO7_OFF_Y_H                0x73
#define MAGNETO7_OFF_Z_L                0x78
#define MAGNETO7_OFF_Z_H                0x79
#define MAGNETO7_FINEOUTPUTX_L          0x90
#define MAGNETO7_FINEOUTPUTX_H          0x91
#define MAGNETO7_FINEOUTPUTY_L          0x92
#define MAGNETO7_FINEOUTPUTY_H          0x93
#define MAGNETO7_FINEOUTPUTZ_L          0x94
#define MAGNETO7_FINEOUTPUTZ_H          0x95
#define MAGNETO7_GAIN_PARA_X_L          0x9C
#define MAGNETO7_GAIN_PARA_X_H          0x9D
#define MAGNETO7_GAIN_PARA_Y_L          0x9E
#define MAGNETO7_GAIN_PARA_Y_H          0x9F
#define MAGNETO7_GAIN_PARA_Z_L          0xA0
#define MAGNETO7_GAIN_PARA_Z_H          0xA1
/** \} */

/**
 * \defgroup device_axes Device Axes
 * \{
 */
#define MAGNETO7_X_AXIS                 0x00
#define MAGNETO7_Y_AXIS                 0x01
#define MAGNETO7_Z_AXIS                 0x02
/** \} */

/**
 * \defgroup sensor_resolutions Sensor Resolutions
 * \{
 */
#define MAGNETO7_SENSOR_RES_12_BIT      0x00
#define MAGNETO7_SENSOR_RES_14_BIT      0x01
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

    float sensor_res;

} magneto7_t;

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

} magneto7_cfg_t;

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
void magneto7_cfg_setup ( magneto7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param magneto7 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MAGNETO7_RETVAL magneto7_init ( magneto7_t *ctx, magneto7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Magneto7 click.
 */
uint8_t magneto7_default_cfg ( magneto7_t *ctx );

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
void magneto7_generic_write ( magneto7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void magneto7_generic_read ( magneto7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Getting INT pin state function.
 *
 * @param ctx          Click object.
 *
 * @description This function returns INT pin state.
 */
uint8_t magneto7_int_get ( magneto7_t *ctx );

/**
 * @brief Getting register value(s) function.
 *
 * @param ctx                 Click object.
 * @param register_address    Register address.
 * @param data_buffer         Data buffer.
 * @param n_data              Number of the bytes to be read
 *
 * @description This function gets register value(s).
 */
uint8_t magneto7_get_register ( magneto7_t *ctx, uint8_t register_address, uint8_t * data_buffer, uint8_t n_data );

/**
 * @brief Setting register value(s) function.
 *
 * @param ctx                 Click object.
 * @param register_address    Register address.
 * @param data_buffer         Data buffer.
 * @param n_data              Number of the bytes to be read
 *
 * @description This function sets register value(s).
 */
uint8_t magneto7_set_register ( magneto7_t *ctx, uint8_t register_address, uint8_t *data_buffer, uint8_t n_data );

/**
 * @brief Setting offset values function.
 *
 * @param ctx                 Click object.
 * @param offset_axis         Offset axis.
 * @param offset_value        Offset value.
 *
 * @description This function sets offset values.
 */
uint8_t magneto7_set_offset ( magneto7_t *ctx, uint8_t offset_axis, uint8_t offset_value );

/**
 * @brief Getting raw device temperature value function.
 *
 * @param ctx                 Click object.
 * @param device_temperature  Address of a variable to store raw device temperature value.
 *
 * @description This function gets raw device temperature value.
 */
void magneto7_get_temperature ( magneto7_t *ctx, uint16_t *device_temperature );

/**
 * @brief Getting data function.
 *
 * @param ctx                 Click object.
 * @param x_axis              Address of a variable to store x-axis data.
 * @param y_axis              Address of a variable to store y-axis data.
 * @param z_axis              Address of a variable to store z-axis data.
 *
 * @description This function gets data register values and sorts thair content into signed 16bit values.
 */
void magneto7_get_data ( magneto7_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis );

/**
 * @brief Getting fine data function.
 *
 * @param ctx                 Click object.
 * @param x_axis              Address of a variable to store x-axis data.
 * @param y_axis              Address of a variable to store y-axis data.
 * @param z_axis              Address of a variable to store z-axis data.
 *
 * @description This function gets fine data register values and sorts thair content into unsigned 16bit values.
 */
void magneto7_get_fine_data ( magneto7_t *ctx, uint16_t *x_axis, uint16_t *y_axis, uint16_t *z_axis );

/**
 * @brief Getting fine data function.
 *
 * @param ctx                   Click object.
 * @param raw_data              Raw data.
 * @param sensor_resolutions    Sensor resolution.
 *
 * @description This function converts raw data by dividing raw data with 6 or 24 for 12bit or 14bit data.
 */
float magneto7_convert_to_ut ( magneto7_t *ctx, int16_t raw_data, uint8_t sensor_resolution );

/**
 * @brief Getting gain data function.
 *
 * @param ctx                 Click object.
 * @param x_axis              Address of a variable to store x-axis data.
 * @param y_axis              Address of a variable to store y-axis data.
 * @param z_axis              Address of a variable to store z-axis data.
 *
 * @description This function gets gain data.
 */
void magneto7_get_gain_para ( magneto7_t *ctx, uint16_t *x_axis, uint16_t *y_axis, uint16_t *z_axis );

#ifdef __cplusplus
}
#endif
#endif  // _MAGNETO7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
