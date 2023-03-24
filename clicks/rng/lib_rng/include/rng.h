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
 * \brief This file contains API for RNG Click driver.
 *
 * \addtogroup rng RNG Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RNG_H
#define RNG_H

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
#define RNG_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RNG_RETVAL  uint8_t

#define RNG_OK           0x00
#define RNG_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr  Slave address
 * \{
 */
#define RNG_DEVICE_SLAVE_ADDRESS_GND               0x48
#define RNG_DEVICE_SLAVE_ADDRESS_VDD               0x49
#define RNG_DEVICE_SLAVE_ADDRESS_SDA               0x4A
#define RNG_DEVICE_SLAVE_ADDRESS_SCL               0x4B
/** \} */
 
/**
 * \defgroup reset_device  Reset Device
 * \{
 */
#define RNG_RESET_DEVICE                           0x06
/** \} */
 
/**
 * \defgroup reg_addr  Rregisters address
 * \{
 */
#define RNG_CONVERSION_REG                         0x00
#define RNG_CONFIG_REG                             0x01
#define RNG_LO_THRESH_REG                          0x02
#define RNG_HI_THRESH_REG                          0x03
/** \} */
 
/**
 * \defgroup cfg_reg  configuration registers
 * \{
 */
#define  RNG_CONFIG_REG_COMP_QUEUE_DISABLE         0x0003
#define  RNG_CONFIG_REG_COMP_QUEUE_4_CONV          0x0002
#define  RNG_CONFIG_REG_COMP_QUEUE_2_CONV          0x0001
#define  RNG_CONFIG_REG_COMP_QUEUE_1_CONV          0x0000
#define  RNG_CONFIG_REG_COMP_LAT_NON               0x0000
#define  RNG_CONFIG_REG_COMP_LAT                   0x0004
#define  RNG_CONFIG_REG_COMP_POL_LOW               0x0000
#define  RNG_CONFIG_REG_COMP_POL_HIGH              0x0008
#define  RNG_CONFIG_REG_COMP_MODE_TRAD             0x0000
#define  RNG_CONFIG_REG_COMP_MODE_WINDOW           0x0010
#define  RNG_CONFIG_REG_DATA_RATE_8_SPS            0x0000
#define  RNG_CONFIG_REG_DATA_RATE_16_SPS           0x0020
#define  RNG_CONFIG_REG_DATA_RATE_32_SPS           0x0040
#define  RNG_CONFIG_REG_DATA_RATE_64_SPS           0x0060
#define  RNG_CONFIG_REG_DATA_RATE_128_SPS          0x0080
#define  RNG_CONFIG_REG_DATA_RATE_250_SPS          0x00A0
#define  RNG_CONFIG_REG_DATA_RATE_475_SPS          0x00C0
#define  RNG_CONFIG_REG_DATA_RATE_860_SPS          0x00E0
#define  RNG_CONFIG_REG_DEV_MODE_SINGLE            0x0100
#define  RNG_CONFIG_REG_DEV_MODE_CONTIN            0x0000
#define  RNG_CONFIG_REG_PGA_6144                   0x0000
#define  RNG_CONFIG_REG_PGA_4096                   0x0200
#define  RNG_CONFIG_REG_PGA_2048                   0x0400
#define  RNG_CONFIG_REG_PGA_1024                   0x0600
#define  RNG_CONFIG_REG_PGA_512                    0x0800
#define  RNG_CONFIG_REG_PGA_256_1                  0x0A00
#define  RNG_CONFIG_REG_PGA_256_2                  0x0C00
#define  RNG_CONFIG_REG_PGA_256_3                  0x0E00
#define  RNG_CONFIG_REG_MUX_AINP_AINN_0_1          0x0000
#define  RNG_CONFIG_REG_MUX_AINP_AINN_0_3          0x1000
#define  RNG_CONFIG_REG_MUX_AINP_AINN_1_3          0x2000
#define  RNG_CONFIG_REG_MUX_AINP_AINN_2_3          0x3000
#define  RNG_CONFIG_REG_MUX_AINP_AINN_0_GND        0x4000
#define  RNG_CONFIG_REG_MUX_AINP_AINN_1_GND        0x5000
#define  RNG_CONFIG_REG_MUX_AINP_AINN_2_GND        0x6000
#define  RNG_CONFIG_REG_MUX_AINP_AINN_3_GND        0x7000
#define  RNG_CONFIG_REG_OS_SINGLE_CONV             0x8000
#define  RNG_CONFIG_REG_OS_NO_EFFECT               0x0000
/** \} */
 
/**
 * \defgroup tresh_hold Treshhold
 * \{
 */
#define RNG_REG_LOWTHRES_HOLD                      0x8000
#define RNG_REG_HIGH_THRESH_HOLD                   0x7FFF
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

    // static variable 
    
    uint16_t dev_vref;

} rng_t;

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

    uint16_t dev_vref_cfg;

} rng_cfg_t;

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
void rng_cfg_setup ( rng_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RNG_RETVAL rng_init ( rng_t *ctx, rng_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Rng click.
 */
void rng_default_cfg ( rng_t *ctx );

/**
 * @brief Write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param reg_data     Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void rng_write_function ( rng_t *ctx, uint8_t reg, uint16_t reg_data );

/**
 * @brief Read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @returns read 16 byte data 
 *
 * @description This function reads data from the desired register.
 */
uint16_t rng_read_function ( rng_t *ctx, uint8_t reg );

/**
 * @brief Function used for reset device.
 * 
 * @param ctx          Click object.
 *
 * @description This function resets device.
 */
void rng_reset_device ( rng_t *ctx );

/**
 * @brief Function used for set configuration.
 *
 * @param ctx          Click object.
 * @param conf_data    Configuration data.
 *
 * @description This function sets configuration.
 */
void rng_set_config ( rng_t *ctx, uint16_t conf_data );

/**
 * @brief Function used for set vref in millivolts
 *
 * @param ctx          Click object.
 * @param vref_mv      Sets reference voltage in millivolts.
 *
 * @description This function sets desired vref.
 */
void rng_set_vref ( rng_t *ctx, uint16_t vref_mv );

/**
 * @brief Function used for get voltage
 *
 * @param ctx          Click object.
 * 
 * @returns  Voltage in millivolts.
 *
 * @description This function gets voltage in millivolts.
 */
float rng_get_voltage ( rng_t *ctx );

/**
 * @brief Function used for set threshold values.
 *
 * @param ctx          Click object.
 * @param thresh_reg   Register adress.
 * @param thresh_data  Data to be write.
 *
 * @description Used by the comparator stored in two 16-bit registers.
 */
void rng_set_threshold ( rng_t *ctx, uint8_t thresh_reg, uint16_t thresh_data );


#ifdef __cplusplus
}
#endif
#endif  // _RNG_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
