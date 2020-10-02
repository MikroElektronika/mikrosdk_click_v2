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
 * \brief This file contains API for Proximity 11 Click driver.
 *
 * \addtogroup proximity11 Proximity 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PROXIMITY11_H
#define PROXIMITY11_H

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
#define PROXIMITY11_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PROXIMITY11_RETVAL  uint8_t

#define PROXIMITY11_OK           0x00
#define PROXIMITY11_INIT_ERROR   0xFF
/** \} */

/** DEVICE ADDRESS */
/**
 * \defgroup dev_addr Device Address
 * \{
 */
#define PROXIMITY11_DEVICE_ADDRESS     0x38
/** \} */

/** REGISTERS */
/**
 * \defgroup registers Registers
 * \{
 */
#define PROXIMITY11_SYS_CTRL           0x40
#define PROXIMITY11_MODE_CTRL          0x41
#define PROXIMITY11_ALS_PS_CTRL        0x42
#define PROXIMITY11_PS_CTRL            0x43
#define PROXIMITY11_PS_DATA_LSB        0x44
#define PROXIMITY11_PS_DATA_MSB        0x45
#define PROXIMITY11_ALS_DATA0_LSB      0x46
#define PROXIMITY11_ALS_DATA0_MSB      0x47
#define PROXIMITY11_ALS_DATA1_LSB      0x48
#define PROXIMITY11_ALS_DATA1_MSB      0x49
#define PROXIMITY11_INTERRUPT          0x4A
#define PROXIMITY11_PS_TH_LSB          0x4B
#define PROXIMITY11_PS_TH_MSB          0x4C
#define PROXIMITY11_PS_TL_LSB          0x4D
#define PROXIMITY11_PS_TL_MSB          0x4E
#define PROXIMITY11_ALS_DATA0_TH_LSB   0x4F
#define PROXIMITY11_ALS_DATA0_TH_MSB   0x50
#define PROXIMITY11_ALS_DATA0_TL_LSB   0x51
#define PROXIMITY11_ALS_DATA0_TL_MSB   0x52
#define PROXIMITY11_PS_OFFSET_LSB      0x53
#define PROXIMITY11_PS_OFFSET_MSB      0x54
#define PROXIMITY11_MANUFACT_ID        0x92
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */


typedef struct
{
  uint8_t als_data0_gain;
  uint8_t als_data1_gain;
  uint16_t als_measure_time;

} als_data_t;

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

    //als data object

    als_data_t als;

} proximity11_t;

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
    
    // als_data default values

    uint8_t als_data0_gain_cfg;
    uint8_t als_data1_gain_cfg;
    uint16_t als_measure_time_cfg;

} proximity11_cfg_t;



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
void proximity11_cfg_setup ( proximity11_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PROXIMITY11_RETVAL proximity11_init ( proximity11_t *ctx, proximity11_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Proximity11 click.
 */
uint8_t proximity11_default_cfg ( proximity11_t *ctx );

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
void proximity11_generic_write ( proximity11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void proximity11_generic_read ( proximity11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Int pin get functuin.
 * 
 * @param ctx          Click object.
 * 
 * @return int_pin state.
 *
 * @description This function reads and returns int_pin state.
 */
uint8_t proximity11_int_get ( proximity11_t *ctx );

/**
 * @brief Proximity value get function.
 * 
 * @param ctx                           Click object.
 * @param register_address              Register address.
 * @param output_buffer                 Output data buf
 * @param n_bytes                       Number of the bytes to be read
 *
 * @description This function reads proximity values from the desired registers.
 */
uint8_t proximity11_get ( proximity11_t *ctx, uint8_t register_address, uint8_t *output_buffer, uint8_t n_bytes );

/**
 * @brief Proximity value set function.
 * 
 * @param ctx                           Click object.
 * @param register_address              Register address.
 * @param input_buffer                  Output data buf
 * @param n_bytes                       Number of the bytes to be written
 *
 * @description This function writes proximity values to the desired registers.
 */
uint8_t proximity11_set ( proximity11_t *ctx, uint8_t register_address, uint8_t *input_buffer, uint8_t n_bytes );

/**
 * @brief Updating data for Lux calculation
 *
 * @param ctx                           Click object.
 *
 * @description This function updates data used to calculate Lux. This function should be called if changing als measurement time and als gain.
 */
void proximity11_update ( proximity11_t *ctx );

/**
 * @brief Converting raw data to Lux
 *
 * @param ctx                           Click object.
 * @param input_data                    buffer that holds ALS data0 and ALS data1
 *
 * @returns Lux data
 *
 * @description This function takes ALS data 0 and ALS data 1 values and converts them to Lux value
 */
float proximity11_convert_lx ( proximity11_t *ctx, uint16_t *input_data );

/**
 * @brief Getting raw ALS and PS data
 *
 * @param ctx                           Click object.
 * @param data_buffer                   data buffer
 *
 * @description This function gets raw ALS and PS data and stores them into data buffer
 */
void proximity11_get_raw_ps_als_values ( proximity11_t *ctx, uint8_t *data_buffer );

/**
 * @brief Getting ALS and PS values
 *
 * @param ctx                          Click object.
 * @param ps_value                     PS value
 * @param als_value                    ALS value
 *
 * @description This function gets raw ALS and PS data and converts raw ALS data to Lux value
 */
void proximity11_get_ps_als_values ( proximity11_t *ctx, uint16_t *ps_value, float *als_value );

/**
 * @brief Setting High PS threshold value
 *
 * @param ctx                         Click object.
 * @param threshold_value             threshold value
 *
 * @returns 0 for correct threshold value (i.e. if threshold value does not exceed 4095)
 * @returns 1 for incorrect threshold value (i.e. if threshold value exceeds 4095)
 *
 * @description This function sets High PS threshold value
 */
uint8_t proximity11_set_ps_threshold_high ( proximity11_t *ctx, uint16_t threshold_value );

/**
 * @brief Setting Low PS threshold value
 *
 * @param ctx                         Click object.
 * @param threshold_value             threshold value
 *
 * @returns 0 for correct threshold value (i.e. if threshold value does not exceed 4095)
 * @returns 1 for incorrect threshold value (i.e. if threshold value exceeds 4095)
 *
 * @description This function sets Low PS threshold value
 */
uint8_t proximity11_set_ps_threshold_low ( proximity11_t *ctx, uint16_t threshold_value );

/**
 * @brief Setting High Als threshold value
 *
 * @param ctx                           Click object.
 * @param threshold_value               threshold value
 *
 * @description This function sets High ALS threshold value
 */
void proximity11_set_als_threshold_high ( proximity11_t *ctx, uint16_t threshold_value );

/**
 * @brief Setting Low Als threshold value
 *
 * @param ctx                           Click object.
 * @param threshold_value               threshold value
 *
 * @description This function sets Low ALS threshold value
 */
void proximity11_set_als_threshold_low ( proximity11_t *ctx, uint16_t threshold_value );

/**
 * @brief Setting PS offset value
 *
 * @param ctx                           Click object.
 * @param offset_value                  offset value
 *
 * @returns 0 for correct threshold value (i.e. if threshold value does not exceed 1023)
 * @returns 1 for incorrect threshold value (i.e. if threshold value exceeds 1023)
 *
 * @description This function sets PS offset value
 */
uint8_t proximity11_set_ps_offset ( proximity11_t *ctx, uint16_t offset_value );

#ifdef __cplusplus
}
#endif
#endif  // _PROXIMITY11_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
